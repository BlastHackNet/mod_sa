/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "main.h"

// ---------------------------------------------------
CVector *GravityNormal = new CVector( 0.0f, 0.0f, -1.0f );

// ---------------------------------------------------
// new gravity hook
#define HOOKPOS_CPhysical_ApplyGravity	0x543081
DWORD	RETURN_CPhysical_ApplyGravity = 0x543093;

void _cdecl CPhysical_ApplyGravity ( DWORD dwThis )
{
	traceLastFunc( "CPhysical_ApplyGravity(): start" );

	// dwThis should be coming from HOOK_CPhysical_ApplyGravity
	DWORD	dwType;
	__asm
	{
		mov ecx, dwThis
		mov eax, 0x46A2C0	// CEntity::GetType
		call eax
		mov dwType, eax
	}

	traceLastFunc( "CPhysical_ApplyGravity(): after CEntity::GetType" );

	float	fTimeStep = *(float *)0xB7CB5C;
	float	fGravity = *(float *)0x863984;

	if ( cheat_state->_generic.cheat_panic_enabled )
	{
		// apply regular downward gravity
		*(float *)( dwThis + 0x4C ) -= fTimeStep * fGravity;
	}
	else if ( dwType == 2 )
	{
		// It's a vehicle
		CVehicle	*pVehicle = pPools->GetVehicle( (DWORD *)dwThis );
		if ( !pVehicle )
		{
			// apply regular downward gravity
			*(float *)( dwThis + 0x4C ) -= fTimeStep * fGravity;
			traceLastFunc( "CPhysical_ApplyGravity(): returning after non-pool vehicle" );
			return;
		}

		if ( pVehicle->GetDriver() == pPedSelf || pVehicle->IsPassenger(pPedSelf) )
		{
			// we're in the vehicle
			if ( !cheat_state->vehicle.air_brake )
			{
				traceLastFunc( "CPhysical_ApplyGravity(): setting vehicle grav" );
				// use our gravity vector
				CVector vecGravity, vecMoveSpeed;
				pVehicle->GetGravity( &vecGravity );
				pVehicle->GetMoveSpeed( &vecMoveSpeed );
				vecMoveSpeed += vecGravity * fTimeStep * fGravity;
				pVehicle->SetMoveSpeed( &vecMoveSpeed );
			}
		}
		else if ( pVehicle->GetTowedByVehicle() )
		{
			if ( pVehicle->GetTowedByVehicle()->GetDriver() == pPedSelf
			 ||	 pVehicle->GetTowedByVehicle()->IsPassenger(pPedSelf) )
			{
				traceLastFunc( "CPhysical_ApplyGravity(): setting trailer grav" );
				// It's our trailer, use our gravity vector
				CVector vecGravity, vecMoveSpeed;
				pVehicle->GetGravity( &vecGravity );
				pVehicle->GetMoveSpeed( &vecMoveSpeed );
				vecMoveSpeed += vecGravity * fTimeStep * fGravity;
				pVehicle->SetMoveSpeed( &vecMoveSpeed );
			}
			else
			{
				// apply regular downward gravity
				*(float *)( dwThis + 0x4C ) -= fTimeStep * fGravity;
			}
		}
		else
		{
			// apply regular downward gravity
			*(float *)( dwThis + 0x4C ) -= fTimeStep * fGravity;
		}
	}
	else if ( dwType == 3 )
	{
		// It's a ped
		CPed	*pPed = pPools->GetPed( (DWORD *)dwThis );

		if ( pPed == pPedSelf )
		{
			if ( cheat_state->actor.air_brake
				|| cheat_state->actor.fly_active )
			{
				// don't apply gravity
			}
			else if ( cheat_state->actor.SpiderFeet_on )
			{
				// use our gravity vector
				CVector vecGravity, vecMoveSpeed;
				pPed->GetGravity( &vecGravity );
				pPed->GetMoveSpeed( &vecMoveSpeed );
				vecMoveSpeed += vecGravity * fTimeStep * fGravity;
				pPed->SetMoveSpeed( &vecMoveSpeed );
			}
			else
			{
				// apply regular downward gravity
				*(float *)( dwThis + 0x4C ) -= fTimeStep * fGravity;
			}
		}
		else
		{
			// apply regular downward gravity
			*(float *)( dwThis + 0x4C ) -= fTimeStep * fGravity;
		}
	}
	else
	{
		// apply regular downward gravity (+0x4C == m_vecMoveSpeed.fZ)
		*(float *)( dwThis + 0x4C ) -= fTimeStep * fGravity;
	}
	traceLastFunc( "CPhysical_ApplyGravity(): end, returning" );
	return;
}

uint8_t _declspec ( naked ) HOOK_CPhysical_ApplyGravity ( void )
{
	__asm
	{
		push esi
		call CPhysical_ApplyGravity
		add esp, 4
		jmp RETURN_CPhysical_ApplyGravity
	}
}

// ---------------------------------------------------
CMatrix gravcam_matGravity;
CMatrix gravcam_matInvertGravity;
CMatrix gravcam_matVehicleTransform;
CVector gravcam_vecVehicleVelocity;
#define HOOKPOS_VehicleCamStart 0x5245ED
DWORD	RETURN_VehicleCamStart_success = 0x5245F3;
DWORD	RETURN_VehicleCamStart_failure = 0x525E43;
#define HOOKPOS_VehicleCamTargetZTweak	0x524A68
DWORD	RETURN_VehicleCamTargetZTweak = 0x524AA4;
#define HOOKPOS_VehicleCamLookDir1	0x524DF1
DWORD	RETURN_VehicleCamLookDir1 = 0x524DF6;
#define HOOKPOS_VehicleCamLookDir2	0x525B0E
DWORD	RETURN_VehicleCamLookDir2 = 0x525B73;
#define HOOKPOS_VehicleCamHistory	0x525C56
DWORD	RETURN_VehicleCamHistory = 0x525D4A;
#define HOOKPOS_VehicleCamColDetect 0x525D8D
DWORD	RETURN_VehicleCamColDetect = 0x525D92;
#define CALL_VehicleCamUp		0x525E1F
#define HOOKPOS_VehicleCamEnd	0x525E3C
DWORD	RETURN_VehicleCamEnd = 0x525E42;
#define HOOKPOS_VehicleLookBehind	0x5207E3
DWORD	RETURN_VehicleLookBehind = 0x520891;
#define CALL_VehicleLookBehindUp	0x520E2A
#define HOOKPOS_VehicleLookAside	0x520F70
DWORD	RETURN_VehicleLookAside = 0x520FDC;
#define CALL_VehicleLookAsideUp 0x5211E0

bool _cdecl VehicleCamStart ( DWORD dwCam, DWORD pVehicleInterface )
{
	traceLastFunc( "VehicleCamStart()" );

	// Inverse transform some things so that they match a downward pointing gravity.
	// This way SA's gravity-goes-downward assumptive code can calculate the camera
	// spherical coords correctly. Of course we restore these after the camera function
	// completes.
	CVehicle	*pVehicle = pPools->GetVehicle( (DWORD *)pVehicleInterface );

	if ( !pVehicle )
		return false;

	CVector vecGravity;
	pVehicle->GetGravity( &vecGravity );

	GetMatrixForGravity( vecGravity, gravcam_matGravity );
	gravcam_matInvertGravity = gravcam_matGravity;
	gravcam_matInvertGravity.Invert();

	pVehicle->GetMatrix( &gravcam_matVehicleTransform );

	CMatrix matVehicleInverted = gravcam_matInvertGravity * gravcam_matVehicleTransform;
	matVehicleInverted.vPos = gravcam_matVehicleTransform.vPos;
	pVehicle->SetMatrix( &matVehicleInverted );

	pVehicle->GetMoveSpeed( &gravcam_vecVehicleVelocity );

	CVector vecVelocityInverted = gravcam_matInvertGravity * gravcam_vecVehicleVelocity;
	pVehicle->SetMoveSpeed( &vecVelocityInverted );
	return true;
}

void _declspec ( naked ) HOOK_VehicleCamStart ()
{
	_asm
	{
		push edi
		push esi
		call VehicleCamStart
		add esp, 8

		test eax, eax
		jz fail
		mov eax, [edi + 0x460]
		jmp RETURN_VehicleCamStart_success

		fail :
		add esp, 4
		jmp RETURN_VehicleCamStart_failure
	}
}

// ---------------------------------------------------
void _cdecl VehicleCamTargetZTweak ( CVector *pvecCamTarget, float fTargetZTweak )
{
	traceLastFunc( "VehicleCamTargetZTweak()" );

	// Replacement for "vecCamTarget = vecCarPosition + (0, 0, 1)*fZTweak"
	*pvecCamTarget += gravcam_matGravity.vUp * fTargetZTweak;
}

void _declspec ( naked ) HOOK_VehicleCamTargetZTweak ()
{
	_asm
	{
		fstp st

		lea eax, [esp + 0x48]
		push[esp + 0x30]
		push eax
		call VehicleCamTargetZTweak
		add esp, 8

		fld[esp + 0x30]
		fadd[esp + 0x7C]
		fstp[esp + 0x7C]
		fld ds : [0x8CCEDC]
		fdiv[esp + 0x7C]
		fmul[esp + 0x30]
		fadd[esp + 0x1C]
		fstp[esp + 0x1C]

		mov eax, ds : [0xB6F0DC]
		cmp eax, 1
		jmp RETURN_VehicleCamTargetZTweak
	}
}

// ---------------------------------------------------
void _cdecl VehicleCamLookDir1 ( DWORD dwCam, DWORD pVehicleInterface )
{
	traceLastFunc( "VehicleCamLookDir1()" );

	// For the same reason as in VehicleCamStart, inverse transform the camera's lookdir
	// at this point
	CVector *pvecLookDir = ( CVector * ) ( dwCam + 0x190 );
	*pvecLookDir = gravcam_matInvertGravity * ( *pvecLookDir );
}

void _declspec ( naked ) HOOK_VehicleCamLookDir1 ()
{
	_asm
	{
		mov eax, 0x59C910	// CVector::Normalise
		call eax

		push edi
		push esi
		call VehicleCamLookDir1
		add esp, 8

		jmp RETURN_VehicleCamLookDir1
	}
}

// ---------------------------------------------------
bool _cdecl VehicleCamLookDir2 ( DWORD dwCam )
{
	traceLastFunc( "VehicleCamLookDir2()" );

	// Calculates the look direction vector for the vehicle camera. This vector
	// is later multiplied by a factor and added to the vehicle position by SA
	// to obtain the final camera position.
	float	fPhi = *(float *)( dwCam + 0xBC );
	float	fTheta = *(float *)( dwCam + 0xAC );

	*( CVector * ) ( dwCam + 0x190 ) = -gravcam_matGravity.vRight *
		cos( fPhi ) *
		cos( fTheta ) -
		gravcam_matGravity.vFront *
		sin( fPhi ) *
		cos( fTheta ) +
		gravcam_matGravity.vUp *
		sin( fTheta );

	*(float *)0x8CCEA8 = fPhi;
	return true;
}

void _declspec ( naked ) HOOK_VehicleCamLookDir2 ()
{
	_asm
	{
		push esi
		call VehicleCamLookDir2
		add esp, 4

		lea ebx, [esi + 0x190]
		lea ebp, [esi + 0x19C]
		push 4
		jmp RETURN_VehicleCamLookDir2
	}
}

// ---------------------------------------------------
void _cdecl VehicleCamHistory ( DWORD dwCam, CVector *pvecTarget, float fTargetTheta, float fRadius, float fZoom )
{
	traceLastFunc( "VehicleCamHistory()" );

	float	fPhi = *(float *)( dwCam + 0xBC );
	CVector vecDir = -gravcam_matGravity.vRight * cos( fPhi ) * cos( fTargetTheta ) - gravcam_matGravity.vFront * sin( fPhi ) * cos( fTargetTheta ) + gravcam_matGravity.vUp * sin( fTargetTheta );
	( (CVector *) (dwCam + 0x1D8) )[0] = *pvecTarget - vecDir * fRadius;
	( (CVector *) (dwCam + 0x1D8) )[1] = *pvecTarget - vecDir * fZoom;
}

void _declspec ( naked ) HOOK_VehicleCamHistory ()
{
	_asm
	{
		push[esp + 0x0 + 0x7C]	// zoom
		push[esp + 0x4 + 0x2C]	// radius
		push[esp + 0x8 + 0x14]	// targetTheta
		lea eax, [esp + 0xC + 0x48]
		push eax	// pvecTarget
		push esi	// pCam
		call VehicleCamHistory
		add esp, 0x14

		mov eax, [esp + 0x24]
		jmp RETURN_VehicleCamHistory
	}
}

// ---------------------------------------------------
void _cdecl VehicleCamUp ( DWORD dwCam )
{
	traceLastFunc( "VehicleCamUp()" );

	// Calculates the up vector for the vehicle camera.
	CVector *pvecUp = ( CVector * ) ( dwCam + 0x1B4 );
	CVector *pvecLookDir = ( CVector * ) ( dwCam + 0x190 );

	pvecLookDir->Normalize();
	*pvecUp = *pvecLookDir;
	pvecUp->CrossProduct( &gravcam_matGravity.vUp );
	pvecUp->CrossProduct( pvecLookDir );
}

void _declspec ( naked ) HOOK_VehicleCamUp ()
{
	_asm
	{
		mov edx, ecx
		mov ecx, [ecx + 0x21C]	// CCam::pTargetEntity
		mov eax, 0x46A2C0		// CEntity::GetType
		call eax

		cmp al, 2			// Is it a vehicle?
		jz docustom

		mov ecx, edx
		mov eax, 0x509CE0	// CCam::GetVectorsReadyForRW
		jmp eax

		docustom :
		push edx
		call VehicleCamUp
		add esp, 4
		ret
	}
}

// ---------------------------------------------------
void _cdecl VehicleCamEnd ( DWORD pVehicleInterface )
{
	traceLastFunc( "VehicleCamEnd()" );

	// Restore the things that we inverse transformed in VehicleCamStart
	CVehicle	*pVehicle = pPools->GetVehicle( (DWORD *)pVehicleInterface );
	if ( !pVehicle )
		return;
	traceLastFunc( "VehicleCamEnd() has CVehicle*" );
	pVehicle->SetMatrix( &gravcam_matVehicleTransform );
	traceLastFunc( "VehicleCamEnd() matrix has been set" );
	pVehicle->SetMoveSpeed( &gravcam_vecVehicleVelocity );
	traceLastFunc( "VehicleCamEnd() move speed has been set, returning" );
}

void _declspec ( naked ) HOOK_VehicleCamEnd ()
{
	_asm
	{
		mov ds : [0xB6F020], edx

		push edi
		call VehicleCamEnd
		add esp, 4

		jmp RETURN_VehicleCamEnd
	}
}

// ---------------------------------------------------
void _cdecl VehicleLookBehind ( DWORD dwCam, CVector *pvecEntityPos, float fDistance )
{
	traceLastFunc( "VehicleLookBehind()" );

	// Custom calculation of the camera position when looking behind while in
	// vehicle cam mode, taking in account custom gravity
	*( CVector * ) ( dwCam + 0x19C ) = *pvecEntityPos + ( gravcam_matVehicleTransform.vFront + gravcam_matGravity.vUp * 0.2f ) * fDistance;
}

void _declspec ( naked ) HOOK_VehicleLookBehind ()
{
	_asm
	{
		push[esp + 0x14]
		lea eax, [esp + 4 + 0x1C]
		push eax
		push edi
		call VehicleLookBehind
		add esp, 0xC

		mov eax, [esp + 0x1C]		// vecTemp = vecEntityPos
		mov ecx, [esp + 0x1C + 4]
		mov edx, [esp + 0x1C + 8]
		mov[esp + 0x34], eax
		mov[esp + 0x34 + 4], ecx
		mov[esp + 0x34 + 8], edx

		mov ds : [0xB7CD68], ebx	// IgnoreEntity
		mov ds : [0xB6FC70], 0		// NumExtraIgnoreEntities
		mov eax, ebx	// pEntity
		jmp RETURN_VehicleLookBehind
	}
}

// ---------------------------------------------------
void _cdecl VehicleLookAside ( DWORD dwCam, CVector *pvecEntityPos, float fDirectionFactor, float fDistance )
{
	traceLastFunc( "VehicleLookAside" );

	// Custom calculation of the camera position when looking left/right while in
	// vehicle cam mode, taking in account custom gravity
	if ( !cheat_state->vehicle.fly )
	{
		*( CVector * ) ( dwCam + 0x19C ) = *pvecEntityPos + ( -gravcam_matVehicleTransform.vRight * fDirectionFactor + gravcam_matGravity.vUp * 0.2f ) * fDistance;
	}
}

void _declspec ( naked ) HOOK_VehicleLookAside ()
{
	_asm
	{
		push[esp + 0x14]
		push[esp + 4 + 0x1C]
		lea eax, [esp + 8 + 0x20]
		push eax
		push esi
		call VehicleLookAside
		add esp, 0x10

		lea ebp, [esi + 0x19C]
		mov ecx, [esi + 0x21C]
		jmp RETURN_VehicleLookAside
	}
}

// ---------------------------------------------------
void _cdecl CVehicle_constructor_hook ( CVehicleSAInterface *vehicle )
{
	// create & add new CVehicle to CPools
	CVehicle	*CVeh = pPools->AddVehicle( (DWORD *)vehicle );
	CVeh->SetGravity( GravityNormal );
}

#define HOOKPOS_CVehicle_constructor	0x6D6259
DWORD	RETURN_CVehicle_constructor = 0x6D6263;
void _declspec ( naked ) HOOK_CVehicle_constructor ()
{
	__asm
	{
		// perform over-written asm
		mov fs : 0, ecx
		add esp, 0x10

		// call handler
		push eax
		call CVehicle_constructor_hook
		add esp, 0x4

		// return
		jmp RETURN_CVehicle_constructor
	}
}

void _cdecl CVehicle_destructor_hook ( CVehicleSAInterface *vehicle )
{
	// remove CVehicle from CPools and delete
	CVehicle	*CVeh_toDelete = pPools->GetVehicle( (DWORD *)vehicle );
	pPools->RemoveVehicle( CVeh_toDelete, false );
}

#define HOOKPOS_CVehicle_destructor 0x6E2B40
DWORD	RETURN_CVehicle_destructor = 0x6E2B47;
void _declspec ( naked ) HOOK_CVehicle_destructor ()
{
	__asm
	{
		// call handler
		push ecx
		call CVehicle_destructor_hook
		pop ecx

		// perform over-written asm
		push 0x0FFFFFFFF
		push 0x848826

		// return
		jmp RETURN_CVehicle_destructor
	}
}

// ---------------------------------------------------
void _cdecl CPed_constructor_hook ( CPedSAInterface *ped )
{
	// create & add new CPed to CPools
	pPools->AddPed( (DWORD *)ped );
	
	// use this if the player ped ever becomes deleted, this will reset the pointer
	// this only works if there's no other peds since the pool will resize automatically
	//if ( pPools->GetPedRef( pPools->AddPed( (DWORD *)ped ) ) == CPOOLS_PED_SELF_REF )
	//	pPedSelf = pPools->GetPedFromRef( CPOOLS_PED_SELF_REF );
}

#define HOOKPOS_CPed_constructor	0x5E8606
DWORD	RETURN_CPed_constructor = 0x5E8610;
void _declspec ( naked ) HOOK_CPed_constructor ()
{
	__asm
	{
		// perform over-written asm
		mov fs : 0, ecx
		add esp, 0x28

		// call handler
		push eax
		call CPed_constructor_hook

		//pop eax
		add esp, 0x4

		// return
		jmp RETURN_CPed_constructor
	}
}

void _cdecl CPed_destructor_hook ( CPedSAInterface *ped )
{
	// remove CPed from CPools and delete
	CPed	*CPed_toDelete = pPools->GetPed( (DWORD *)ped );
	pPools->RemovePed( CPed_toDelete, false );
}

#define HOOKPOS_CPed_destructor 0x5E8620
DWORD	RETURN_CPed_destructor = 0x5E8627;
void _declspec ( naked ) HOOK_CPed_destructor ()
{
	__asm
	{
		// call handler
		push ecx
		call CPed_destructor_hook
		pop ecx

		// perform over-written asm
		push 0x0FFFFFFFF
		push 0x83DA5A

		// return
		jmp RETURN_CPed_destructor
	}
}

// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------
#define COLLISION_IGNORE_NUM 1828
int	collision_ignore_array[COLLISION_IGNORE_NUM] = {
// levelXREF
2885, 2890, 2892, 2893, 2899, 2900, 2903, 2904, 2909, 2911, 2912, 2918, 2920, 2954, 2955, 
2956, 2957, 2959, 2960, 2963, 2964, 2965, 2968, 2969, 2970, 2971, 2972, 2973, 2974, 2975, 
2990, 2991, 2994, 3005, 3006, 3013, 3014, 3015, 3016, 3029, 3030, 3031, 3032, 3033, 3035, 
3036, 3037, 3038, 3039, 3040, 3041, 3042, 3043, 3046, 3049, 3050, 3052, 3053, 3054, 3055, 
3057, 3058, 3061, 3062, 3066, 3067, 3073, 3075, 3077, 3078, 3080, 3083, 3084, 3089, 3091, 
3093, 3094, 3095, 3107, 3109, 3110, 3113, 3114, 3115, 3117, 3134, 
// countryXREF
3294, 3295, 3296, 3297, 3298, 3299, 3300, 3301, 3302, 3352, 
// VEGASxref
3447, 3451, 3465, 
// LAxref
3603, 3604, 3605, 3606, 3607, 3610, 3611, 3612, 3613, 3615, 3616, 3617, 
// Levelmap
3898, 3921, 3922, 3926, 3927, 3929, 3930, 3931, 3932, 3935, 3936, 3937, 3939, 3940, 3941, 
3944, 3945, 3946, 3948, 
// LAn
3979, 3980, 3986, 3988, 4002, 4003, 4004, 4006, 4011, 4015, 4016, 4019, 4021, 4022, 4023, 
4034, 4048, 4060, 4102, 4106, 4112, 4113, 4114, 4117, 4120, 4121, 4123, 4141, 4170, 4171, 
4183, 4185, 4188, 4189, 4190, 4193, 4195, 4196, 4201, 4202, 4205, 4227, 4231, 
// LAn2
4560, 4563, 4564, 4574, 4594, 4602, 4605, 4609, 4638, 4639, 4640, 4641, 4642, 4711, 4714, 
4718, 4724, 
// LAs
4826, 4828, 4832, 4848, 4850, 4853, 4857, 4882, 4886, 4981, 4982, 4983, 4984, 4987, 4990, 
5001, 5005, 5006, 5007, 5010, 5011, 5017, 5024, 5030, 5032, 5043, 5044, 5051, 5056, 5060, 
5061, 5062, 5063, 
// LAs2
5126, 5129, 5132, 5148, 5152, 5153, 5154, 5155, 5158, 5160, 5166, 5167, 5170, 5171, 5175, 
5190, 5243, 5244, 5259, 5260, 5261, 5262, 5266, 5268, 5269, 5291, 5298, 5299, 5300, 5302, 
5304, 5305, 5306, 5309, 5310, 5312, 5338, 5340, 5358, 5359, 5360, 5363, 5364, 
// LAe
5394, 5400, 5401, 5405, 5409, 5410, 5414, 5415, 5416, 5417, 5421, 5422, 5463, 5464, 5465, 
5469, 5470, 5473, 5475, 5476, 5520, 5565, 5626, 5627, 5630, 5631, 5632, 5633, 5634, 5635, 
5636, 5637, 5638, 5641, 5644, 5654, 5659, 5660, 5676, 5677, 5678, 5681, 
// LAwn
5710, 5711, 5712, 5713, 5714, 5715, 5727, 5737, 5742, 5762, 5770, 5776, 5779, 5792, 5811, 
5814, 5816, 5817, 5820, 5821, 5822, 5837, 5838, 5839, 5840, 5848, 5849, 5855, 5856, 5873, 
5874, 5877, 5882, 5884, 5885, 5888, 5893, 5926, 5935, 5971, 5983, 5986, 5989, 5993, 6002, 
6005, 
// LAw
6046, 6049, 6051, 6052, 6056, 6062, 6066, 6068, 6110, 6189, 6191, 6223, 6228, 6230, 6243, 
6247, 6264, 
// LAw2
6283, 6287, 6288, 6289, 6295, 6298, 6299, 6342, 6344, 6370, 6400, 6405, 6407, 6413, 6415, 
6422, 6451, 6456, 6457, 6458, 6459, 6460, 6461, 6462, 6463, 6465, 6466, 6475, 6489, 6516, 
6517, 6522, 6523, 6524, 6829, 
// VEGASn
6867, 6868, 6871, 6874, 6875, 6907, 6908, 6909, 6910, 6946, 6954, 6955, 6957, 6958, 6960, 
6961, 6962, 6963, 6967, 6968, 6969, 6970, 6977, 6994, 7027, 7033, 7034, 7038, 7039, 7040, 
7089, 7093, 7094, 7095, 7102, 7103, 7104, 7105, 7153, 7172, 7186, 7187, 7188, 7189, 7190, 
7191, 7192, 7196, 7197, 7198, 7200, 7201, 7202, 7204, 7205, 7209, 7210, 7212, 7213, 7223, 
7224, 7227, 7228, 7229, 7231, 7234, 7236, 7238, 7243, 7269, 7273, 7276, 7277, 7287, 7291, 
7292, 7295, 7296, 7297, 7298, 7299, 7311, 7312, 7317, 7319, 7344, 7347, 7349, 7350, 7351, 
7352, 7361, 7367, 7368, 7369, 7370, 7371, 7377, 7378, 7379, 7380, 7381, 
// VEGASw
7415, 7418, 7423, 7424, 7425, 7426, 7488, 7489, 7492, 7493, 7494, 7495, 7497, 7504, 7505, 
7518, 7520, 7521, 7522, 7524, 7525, 7526, 7527, 7528, 7529, 7531, 7532, 7538, 7539, 7540, 
7554, 7560, 7561, 7583, 7584, 7586, 7592, 7593, 7595, 7596, 7597, 7599, 7606, 7610, 7617, 
7618, 7619, 7620, 7621, 7622, 7623, 7624, 7625, 7627, 7628, 7650, 7651, 7657, 7658, 7659, 
7662, 7663, 7664, 7665, 7666, 7692, 7707, 7708, 7709, 7832, 7834, 7836, 7837, 7838, 7839, 
7840, 7841, 7842, 7891, 7893, 7894, 7917, 7918, 7919, 7920, 7921, 7922, 7923, 7924, 7926, 
7927, 7930, 7931, 7933, 7939, 7947, 7948, 7949, 7950, 7952, 7953, 7954, 
// VEGASs
7979, 7980, 7981, 7982, 8034, 8038, 8041, 8042, 8044, 8057, 8058, 8059, 8060, 8061, 8062, 
8063, 8064, 8073, 8074, 8075, 8076, 8077, 8078, 8128, 8130, 8131, 8132, 8147, 8148, 8149, 
8150, 8151, 8152, 8153, 8154, 8155, 8163, 8165, 8167, 8169, 8170, 8206, 8207, 8208, 8209, 
8210, 8229, 8237, 8240, 8247, 8249, 8251, 8253, 8254, 8255, 8260, 8262, 8263, 8300, 8311, 
8313, 8314, 8315, 8320, 8335, 8337, 8339, 8341, 8342, 8345, 8369, 8375, 8378, 8391, 8394, 
8396, 8397, 8399, 8400, 8406, 8407, 8408, 8410, 8412, 8416, 8421, 8424, 8426, 8429, 8430, 
8431, 8434, 8435, 8436, 8437, 8481, 8489, 8491, 8492, 8494, 8498, 8499, 8501, 8503, 8504, 
8505, 8506, 8507, 8508, 8509, 8516, 8526, 8527, 8528, 8530, 8534, 8535, 8536, 8537, 8545, 
8546, 8549, 8550, 8551, 8556, 8557, 8558, 8559, 8563, 8591, 8597, 8618, 8620, 8635, 8636, 
8639, 8640, 8641, 8642, 8645, 8646, 8647, 8648, 8649, 8650, 8651, 8652, 8653, 8656, 8657, 
8658, 8659, 8662, 8668, 8669, 8670, 8673, 8674, 8675, 8676, 8680, 8681, 8682, 8683, 8684, 
8685, 8686, 8687, 8825, 8826, 8827, 8828, 8833, 8834, 8838, 8839, 8841, 8842, 8849, 8870, 
8871, 8872, 8873, 8875, 8877, 8879, 8881, 8882, 8883, 8884, 8885, 8886, 8889, 8947, 8948, 
8952, 8953, 8957, 8979, 8980, 8982, 8984, 8985, 8986, 8987, 8988, 8992, 8993, 8994, 8995, 
8996, 8997, 8998, 8999, 9029, 9030, 9031, 9032, 9033, 9041, 9043, 9054, 9055, 9070, 9071, 
9072, 9093, 9099, 9106, 9108, 9109, 9110, 9111, 9112, 9113, 9114, 9132, 9134, 9164, 9165, 
9166, 9167, 9168, 9169, 9171, 
// SFn
9237, 9238, 9245, 9258, 9270, 9271, 9272, 9273, 9274, 9275, 9278, 9279, 9280, 9281, 9282, 
9283, 9292, 9293, 9294, 9295, 9296, 9297, 9298, 9302, 9303, 9310, 9317, 9318, 9321, 9322, 
9323, 9325, 9326, 9330, 9331, 9332, 9333, 9334, 9335, 9336, 9337, 9339, 9340, 9343, 9344, 
9347, 9348, 9349, 9350, 9361, 9362, 9390, 
// SFw
9482, 9526, 9528, 9587, 9588, 9589, 9604, 9623, 9625, 9690, 9694, 9761, 9818, 9819, 9820, 
9821, 9822, 9837, 9838, 
// SFe
9949, 9950, 9951, 9958, 10024, 10029, 10145, 10166, 10182, 10226, 10227, 10229, 10246, 10248, 10270, 
10309, 
// SFs
10357, 10369, 10379, 10380, 10381, 10388, 10390, 10391, 10392, 10396, 10397, 10398, 10401, 10402, 10437, 
10442, 10445, 10558, 10575, 10610, 10611, 10624, 10626, 10630, 10631, 10633, 10634, 10671, 10675, 10683, 
10716, 
// SFse
10757, 10762, 10764, 10773, 10774, 10775, 10776, 10777, 10789, 10806, 10807, 10808, 10809, 10810, 10811, 
10814, 10825, 10828, 10829, 10830, 10831, 10832, 10835, 10836, 10837, 10838, 10839, 10840, 10843, 10844, 
10845, 10847, 10873, 10874, 10875, 10885, 10889, 10890, 10932, 10947, 10954, 10955, 10982, 10984, 10985, 
10986, 10987, 10992, 10994, 10999, 11008, 11009, 11010, 11011, 11014, 11015, 11081, 11087, 11089, 11090, 
11091, 11092, 11093, 11101, 11102, 11103, 11147, 11148, 11225, 11244, 11246, 11247, 11290, 11292, 11293, 
11295, 11313, 11314, 11319, 11327, 11334, 11352, 11353, 11359, 11360, 11383, 11390, 11391, 11393, 11395, 
11416, 
// countryN
11422, 11423, 11424, 11425, 11426, 11427, 11428, 11449, 11450, 11452, 11453, 11454, 11455, 11456, 11457, 
11458, 11459, 11461, 11462, 11463, 11469, 11470, 11471, 11472, 11473, 11474, 11475, 11479, 11480, 11481, 
11482, 11483, 11489, 11490, 11491, 11492, 11494, 11497, 11498, 11499, 11500, 11501, 11502, 11503, 11504, 
11505, 11543, 11544, 11546, 11547, 11551, 11556, 11558, 11566, 11567, 11568, 11572, 11609, 11611, 11623, 
11631, 11664, 11665, 11666, 11674, 
// countryE
12805, 12807, 12808, 12821, 12839, 12840, 12842, 12845, 12846, 12848, 12854, 12858, 12859, 12860, 12861, 
12911, 12912, 12913, 12914, 12915, 12917, 12918, 12921, 12922, 12927, 12929, 12930, 12932, 12933, 12934, 
12935, 12936, 12937, 12938, 12940, 12943, 12950, 12954, 12955, 12956, 12957, 12958, 12961, 12972, 12977, 
12985, 12986, 12987, 12992, 13002, 13003, 13004, 13005, 13011, 13016, 13018, 13024, 13025, 13028, 13029, 
13033, 13034, 13045, 13053, 13054, 13057, 13060, 13061, 13097, 13098, 13108, 13109, 13118, 13132, 13140, 
13141, 13143, 13153, 13187, 13188, 13190, 13198, 13206, 13296, 13360, 13367, 13369, 13435, 13436, 13438, 
13445, 13450, 13489, 
// STADINT
13590, 13591, 13592, 13593, 13594, 13596, 13597, 13598, 13599, 13600, 13601, 13604, 13605, 13606, 13609, 
13623, 13625, 13628, 13629, 13630, 13631, 13632, 13653, 13656, 13666, 13667, 
// LAhills
13681, 13694, 13695, 13696, 13697, 13699, 13705, 13712, 13714, 13722, 13725, 13728, 13729, 13731, 13743, 
13744, 13747, 13748, 13754, 13755, 13758, 13759, 13817, 13831, 13855, 13861, 13862, 13863, 13864, 13865, 
13866, 
// int_LA
14386, 14391, 14392, 14396, 14397, 14398, 14399, 14401, 14403, 14405, 14413, 14433, 14434, 14435, 14436, 
14437, 14440, 14445, 14446, 14448, 14449, 14450, 14451, 14452, 14454, 14455, 14458, 14459, 14463, 14464, 
14467, 14477, 14480, 14481, 14482, 14483, 14486, 14490, 14491, 14493, 14494, 14497, 14502, 14503, 14504, 
14505, 14507, 14508, 14509, 14510, 14513, 14516, 14517, 14518, 14519, 14524, 
// int_SF
14532, 14535, 14540, 14543, 14544, 14547, 14549, 14550, 14551, 14552, 14556, 14558, 
// int_VEGAS
14560, 14562, 14565, 14566, 14567, 14568, 14569, 14571, 14573, 14574, 14575, 14578, 14582, 14583, 14584, 
14585, 14586, 14587, 14589, 14599, 14600, 14604, 14608, 14613, 14616, 14617, 14618, 14619, 14620, 14622, 
14632, 14633, 14635, 14638, 14640, 
// int_country
14651, 14653, 14657, 
// GEN_INT1
14660, 14666, 14673, 14676, 14678, 14679, 14683, 14685, 14693, 
// GEN_INT2
14704, 14705, 14715, 14716, 
// GEN_INTb
14739, 14741, 14745, 14757, 14764, 
// GEN_INT3
14770, 14772, 14780, 14781, 14782, 14786, 14790, 14791, 14792, 14796, 14797, 14799, 14800, 14802, 14804, 
14805, 14806, 14807, 14809, 14810, 14811, 14813, 14816, 14817, 14819, 14820, 14826, 14828, 14830, 14831, 
14832, 14835, 14836, 14837, 14839, 14840, 
// GEN_INT4
14843, 14844, 14850, 14854, 14855, 14856, 14861, 14866, 14867, 14869, 14870, 14872, 14873, 14875, 14878, 
14880, 14883, 14888, 14891, 14895, 
// SAVEHOUSE
15025, 15026, 15032, 15035, 15036, 15037, 15039, 15050, 15052, 15064, 
// countryN2
16000, 16001, 16002, 16003, 16004, 16005, 16006, 16010, 16011, 16012, 16016, 16017, 16018, 16019, 16020, 
16021, 16023, 16051, 16052, 16053, 16054, 16060, 16061, 16062, 16064, 16065, 16066, 16067, 16081, 16083, 
16086, 16087, 16088, 16089, 16090, 16091, 16092, 16094, 16095, 16096, 16098, 16100, 16101, 16104, 16105, 
16106, 16107, 16108, 16121, 16123, 16125, 16126, 16129, 16130, 16131, 16132, 16134, 16135, 16136, 16138, 
16139, 16140, 16141, 16142, 16143, 16144, 16145, 16146, 16151, 16152, 16154, 16281, 16285, 16287, 16308, 
16313, 16314, 16315, 16320, 16321, 16322, 16324, 16327, 16328, 16329, 16335, 16340, 16341, 16342, 16343, 
16345, 16346, 16347, 16349, 16351, 16353, 16359, 16360, 16362, 16365, 16366, 16367, 16369, 16370, 16377, 
16378, 16385, 16386, 16387, 16396, 16398, 16399, 16400, 16401, 16402, 16404, 16405, 16406, 16410, 16411, 
16434, 16436, 16437, 16438, 16439, 16442, 16446, 16475, 16477, 16479, 16480, 16481, 16500, 16501, 16503, 
16530, 16531, 16532, 16533, 16534, 16535, 16562, 16563, 16564, 16568, 16599, 16601, 16602, 16605, 16613, 
16641, 16646, 16650, 16662, 16664, 16666, 16667, 16668, 16669, 16670, 16671, 16673, 16675, 16689, 16690, 
16732, 16766, 16767, 16769, 16770, 16773, 16774, 16775, 
// countryW
17026, 17027, 17028, 17029, 17030, 17034, 17035, 17036, 17037, 17038, 17039, 17040, 17041, 17042, 17044, 
17045, 17049, 17050, 17051, 17052, 17053, 17054, 17055, 17057, 17059, 17060, 17063, 17064, 17065, 17066, 
17067, 17069, 17071, 17072, 17074, 17076, 17110, 17111, 17112, 17120, 17293, 17294, 17295, 17298, 17299, 
17307, 17309, 17323, 17324, 17335, 17454, 17457, 17472, 
// LAe2
17501, 17502, 17510, 17514, 17516, 17522, 17523, 17525, 17527, 17528, 17532, 17539, 17540, 17542, 17543, 
17544, 17550, 17551, 17565, 17566, 17573, 17575, 17576, 17583, 17585, 17699, 17804, 17805, 17840, 17851, 
17857, 17860, 17863, 17872, 17874, 17875, 17876, 17886, 17887, 17898, 17911, 17912, 17913, 17924, 17936, 
17937, 17938, 17939, 17940, 17941, 17942, 17947, 17949, 17951, 17968, 
// GEN_INT5
18003, 18005, 18012, 18014, 18016, 18017, 18019, 18032, 18034, 18035, 18040, 18041, 18042, 18043, 18044, 
18047, 18050, 18051, 18055, 18057, 18059, 18060, 18061, 18064, 18067, 18069, 18070, 18074, 18077, 18081, 
18083, 18089, 18090, 18092, 18104, 18105, 18109, 
// countryS
18201, 18202, 18230, 18232, 18233, 18234, 18235, 18236, 18238, 18257, 18258, 18259, 18260, 18263, 18264, 
18283, 18284, 18286, 18287, 18288, 18289, 18290, 18291, 18292, 18365, 18366, 18367, 18368, 18451, 18452, 
18551, 18552, 18561, 18563, 18565, 18566, 18567, 18568, 18569, 18608, 18609, 
};

bool ignoreColWithObjectID ( int iModelID )
{
	if ( iModelID <= 9500 )
	{
		// Vegepart
		if ( iModelID <= 792 && iModelID >= 615 )
			return true;

		// ProcObj
		if ( iModelID <= 906 && iModelID >= 800 )
			return true;

		// propExt
		if ( iModelID <= 964 && iModelID >= 910 )
			return true;

		// Barriers
		if ( iModelID <= 998 && iModelID >= 966 )
			return true;

		// Dynamic
		if ( iModelID <= 1325 && iModelID >= 1207 )
			return true;

		// Dynamic2
		if ( iModelID <= 1572 && iModelID >= 1327 )
			return true;

		// MultiObj
		if ( iModelID <= 1698 && iModelID >= 1574 )
			return true;

		// props & props2
		if ( iModelID <= 2882 && iModelID >= 1700 )
			return true;

		// levelXREF
		if ( iModelID <= 2938 && iModelID >= 2923 )
			return true;

		if ( iModelID <= 2952 && iModelID >= 2941 )
			return true;

		if ( iModelID <= 2988 && iModelID >= 2977 )
			return true;

		// countryXREF
		if ( iModelID <= 3279 && iModelID >= 3167 )
			return true;

		if ( iModelID <= 3291 && iModelID >= 3281 )
			return true;

		if ( iModelID <= 3350 && iModelID >= 3330 )
			return true;

		if ( iModelID <= 3374 && iModelID >= 3354 )
			return true;

		if ( iModelID <= 3398 && iModelID >= 3376 )
			return true;

		if ( iModelID <= 3424 && iModelID >= 3403 )
			return true;

		// VEGASxref
		if ( iModelID <= 3441 && iModelID >= 3430 )
			return true;

		if ( iModelID <= 3463 && iModelID >= 3454 )
			return true;

		if ( iModelID <= 3482 && iModelID >= 3467 )
			return true;

		if ( iModelID <= 3500 && iModelID >= 3489 )
			return true;

		// LAxref
		if ( iModelID <= 3598 && iModelID >= 3502 )
			return true;

		if ( iModelID <= 3740 && iModelID >= 3619 )
			return true;

		if ( iModelID <= 3763 && iModelID >= 3742 )
			return true;

		if ( iModelID <= 3783 && iModelID >= 3765 )
			return true;

		// SFxref
		if ( iModelID <= 3819 && iModelID >= 3785 )
			return true;

		if ( iModelID <= 3888 && iModelID >= 3850 )
			return true;

		// LAn
		if ( iModelID <= 4100 && iModelID >= 4084 )
			return true;

		// seabed
		if ( iModelID <= 4527 && iModelID >= 4504 )
			return true;

		// LAs
		if ( iModelID <= 5082 && iModelID >= 5066 )
			return true;

		// VEGASn
		if ( iModelID <= 6934 && iModelID >= 6919 )
			return true;

		if ( iModelID <= 7025 && iModelID >= 7014 )
			return true;

		// VEGASw
		if ( iModelID <= 7516 && iModelID >= 7507 )
			return true;

		// VEGASs
		if ( iModelID <= 8196 && iModelID >= 8173 )
			return true;

	}else{
		// SFse
		if ( iModelID <= 11242 && iModelID >= 11233 )
			return true;

		// countryN
		if ( iModelID <= 11447 && iModelID >= 11431 )
			return true;

		// STADINT
		if ( iModelID <= 13650 && iModelID >= 13634 )
			return true;

		// GEN_INT2
		if ( iModelID <= 14728 && iModelID >= 14719 )
			return true;

		// countryN2
		if ( iModelID <= 16079 && iModelID >= 16069 )
			return true;

		if ( iModelID <= 16119 && iModelID >= 16110 )
			return true;

		if ( iModelID <= 16279 && iModelID >= 16267 )
			return true;

		if ( iModelID <= 16305 && iModelID >= 16293 )
			return true;

		if ( iModelID <= 16637 && iModelID >= 16627 )
			return true;

		// countryW
		if ( iModelID <= 17011 && iModelID >= 17000 )
			return true;

		if ( iModelID <= 17024 && iModelID >= 17013 )
			return true;

		// countryS
		if ( iModelID <= 18228 && iModelID >= 18216 )
			return true;

		if ( iModelID <= 18255 && iModelID >= 18240 )
			return true;

		if ( iModelID <= 18281 && iModelID >= 18267 )
			return true;

		if ( iModelID <= 18446 && iModelID >= 18432 )
			return true;

	}

	int i = (iModelID >= 9500) ? 908 : 0;
	int maxNum = (i == 0) ? 908 : COLLISION_IGNORE_NUM;
	for ( ; i < maxNum; i++ )
	{
		if ( collision_ignore_array[i] == iModelID )
			return true;
	}
	return false;
}

#define HOOKPOS_PlayerCollision 0x54BCD2
DWORD	RETURN_PlayerCollision_ovrwr = 0x54CEFC;
DWORD	RETURN_PlayerCollision_process = 0x54BCDC;
DWORD	RETURN_PlayerCollision_noProcessing = 0x54CF8D;
DWORD	PlayerCollision_eax_back, PlayerCollision_ebx_back, PlayerCollision_ecx_back;
DWORD	PlayerCollision_edi_back, PlayerCollision_esi_back, PlayerCollision_edx_back;
DWORD	PlayerCollision_esp_back;
DWORD	PlayerCollision_tmp;
void _declspec ( naked ) HOOK_PlayerCollision ()
{
	__asm test byte ptr [esi+0x1c], 1
	__asm jne hk_PlCol_process
	__asm jmp RETURN_PlayerCollision_ovrwr

hk_PlCol_process:
	// processing collision of *_info (esi)
	__asm mov PlayerCollision_esi_back, esi
	// with *_info (edi)
	__asm mov PlayerCollision_edi_back, edi

	__asm mov PlayerCollision_eax_back, eax
	__asm mov PlayerCollision_ebx_back, ebx
	__asm mov PlayerCollision_ecx_back, ecx
	__asm mov PlayerCollision_edx_back, edx
	__asm mov PlayerCollision_esp_back, esp

	__asm pushad
	traceLastFunc( "HOOK_PlayerCollision()" );

	// process collision if panic enabled
	if ( cheat_state->_generic.cheat_panic_enabled )
		goto hk_PlCol_processCol;

	// already crashed, if true
	if ( PlayerCollision_edi_back == NULL || PlayerCollision_esi_back == NULL )
		goto hk_PlCol_noCol;

	// No vehicle collisions
	if ( cheat_state->_generic.nocols_enabled )
	{
		// Vehicle (edi) -> vehicle(esi)/actor(esi)
		if ( !isBadPtr_GTA_pVehicle((vehicle_info *)PlayerCollision_edi_back) &&
			(!isBadPtr_GTA_pVehicle((vehicle_info *)PlayerCollision_esi_back) ||
			!isBadPtr_GTA_pPed((actor_info *)PlayerCollision_esi_back) ) )
			goto hk_PlCol_noCol;

		// Vehicle (esi) -> Actor (edi)
		if ( !isBadPtr_GTA_pVehicle((vehicle_info *)PlayerCollision_esi_back) &&
			!isBadPtr_GTA_pPed((actor_info *)PlayerCollision_edi_back) )
			goto hk_PlCol_noCol;
	}

	// get own vehicle
	PlayerCollision_tmp = (DWORD)vehicle_info_get( VEHICLE_SELF, 0 );
	if ( PlayerCollision_tmp )
		goto hk_PlCol_proceed_w_Veh;

	// get actor
	PlayerCollision_tmp = (DWORD)actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( PlayerCollision_tmp )
		goto hk_PlCol_proceed_noveh;
	__asm jmp hk_PlCol_processCol

hk_PlCol_proceed_w_Veh:
	// check if it is our vehicle or trailer colliding
	// do not collide with trailer (if trailer_support)
	if ( PlayerCollision_esi_back == PlayerCollision_tmp )
	{
		if ( set.trailer_support && PlayerCollision_edi_back == (DWORD)((vehicle_info *)PlayerCollision_tmp)->trailer )
			goto hk_PlCol_noCol;
	}
	else if ( PlayerCollision_edi_back == PlayerCollision_tmp )
	{
		if ( set.trailer_support && PlayerCollision_esi_back == (DWORD)((vehicle_info *)PlayerCollision_tmp)->trailer )
			goto hk_PlCol_noCol;
	}
	else if ( set.trailer_support && ((DWORD)((vehicle_info*)PlayerCollision_tmp)->trailer == PlayerCollision_esi_back
		|| (DWORD)((vehicle_info*)PlayerCollision_tmp)->trailer == PlayerCollision_edi_back) ) 
	{
		// process same way as our car/actor
	}
	else
	{
		// not our car/trailer colliding
		goto hk_PlCol_processCol;
	}

	// actual anti wall collision after this
	if ( !cheat_state->_generic.nocols_walls_enabled )
		goto hk_PlCol_processCol;
	
	/*
	- planes/helis wouldn't be able to land at all while anti-collision activated
	- (using the vehicle.fly as indicator if user doesn't want collisions at all)
	if ( gta_vehicle_get_by_id(((vehicle_info *)PlayerCollision_tmp)->base.model_alt_id)->class_id == VEHICLE_CLASS_AIRPLANE
	 ||	 gta_vehicle_get_by_id(((vehicle_info *)PlayerCollision_tmp)->base.model_alt_id)->class_id == VEHICLE_CLASS_HELI )
	{
		goto forceout;
	}
	*/

	// no collisions while flying with fly mode (better control of plane/heli collision)
	if ( cheat_state->vehicle.fly )
		goto hk_PlCol_noCol;
	__asm jmp hk_PlCol_proceed_generic

hk_PlCol_proceed_noveh:
	// check if we are colliding
	if ( PlayerCollision_esi_back != PlayerCollision_tmp && PlayerCollision_edi_back != PlayerCollision_tmp )
		goto hk_PlCol_processCol;

	// actual anti wall collision after this
	if ( !cheat_state->_generic.nocols_walls_enabled )
		goto hk_PlCol_processCol;

	// we are flying
	//if ( cheat_state->actor.fly_active )
	//	goto hk_PlCol_noCol;

hk_PlCol_proceed_generic:
	if ( set.wall_collisions_disableObjects && !isBadPtr_GTA_pObjectInfo(PlayerCollision_edi_back) )
		goto hk_PlCol_noCol;

	if ( ignoreColWithObjectID(((object_info*)PlayerCollision_edi_back)->base.model_alt_id) )
		goto hk_PlCol_noCol;

hk_PlCol_processCol:
	__asm popad
	__asm mov eax, PlayerCollision_eax_back
	__asm mov ebx, PlayerCollision_ebx_back
	__asm mov ecx, PlayerCollision_ecx_back
	__asm mov edx, PlayerCollision_edx_back
	__asm mov edi, PlayerCollision_edi_back
	__asm mov esi, PlayerCollision_esi_back
	__asm mov esp, PlayerCollision_esp_back
	__asm jmp RETURN_PlayerCollision_process

hk_PlCol_noCol:
	__asm popad
	__asm mov esi, PlayerCollision_esi_back
	__asm mov edi, PlayerCollision_edi_back
	__asm mov ebx, PlayerCollision_ebx_back
	__asm mov eax, PlayerCollision_eax_back
	__asm mov esp, PlayerCollision_esp_back
	__asm jmp RETURN_PlayerCollision_noProcessing
}

#define HOOKPOS_CEntity_Render 0x534319
DWORD RETURN_RenderEntity = 0x53431F;
DWORD RETURN_RenderEntityNoRender = 0x5343EB;
DWORD hook_renderEnt_esi;
DWORD hook_renderEnt_eax;
void _declspec ( naked ) HOOK_RenderEntity ()
{
	__asm
	{
		test eax, eax
		jz hk_RE_checkFail
		mov hook_renderEnt_eax, eax
		mov hook_renderEnt_esi, esi
		pushad
	}

	if ( !set.wall_collisions_disableRender )
		goto hk_RE_draw;

	if ( !cheat_state->_generic.nocols_walls_enabled || cheat_state->_generic.cheat_panic_enabled 
		|| cheat_state->vehicle.fly )
		goto hk_RE_draw;

	if ( set.wall_collisions_disableObjects && !isBadPtr_GTA_pObjectInfo(hook_renderEnt_esi) )
		goto hk_RE_nodraw;

	if ( ignoreColWithObjectID(((object_base*)hook_renderEnt_esi)->model_alt_id) )
		goto hk_RE_nodraw;

hk_RE_draw:
	__asm popad
	__asm mov eax, hook_renderEnt_eax
	__asm jmp RETURN_RenderEntity

hk_RE_nodraw:
	__asm popad
hk_RE_checkFail:
	__asm jmp RETURN_RenderEntityNoRender
}

#define HOOKPOS_Player_Climb	0x67E0EF
DWORD	dwHk_PlCl_esiBckp;
void _declspec ( naked ) HOOK_PlayerClimb ()
{
	__asm mov dwHk_PlCl_esiBckp, esi
	__asm pushad

	if ( !cheat_state->_generic.nocols_walls_enabled || cheat_state->_generic.cheat_panic_enabled )
		goto hkPlCl_normalFlow;

	__asm
	{
		mov eax, dwHk_PlCl_esiBckp
		mov ax, [eax+0x22]
		movzx eax, ax
		push eax
		call ignoreColWithObjectID
		add esp, 0x4
		movzx eax, al
		test eax, eax
		jnz hkPlCl_noClimb
	
hkPlCl_normalFlow:
		popad
		cmp cl, 1
		je hkPlCl_cmpCL
		mov eax, 0x67E0F8
		jmp eax

hkPlCl_cmpCL:
		mov eax, 0x67E53E
		jmp eax

hkPlCl_noClimb:
		popad
		mov eax, 0x67E59A
		jmp eax
	}
}


// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------

#define HOOKPOS_RwFrame_childless	0x7F0BF7
DWORD RwFrame_childless_abortPregnancy = 0x7F0CB5;
DWORD RwFrame_childless_haveAChild = 0x7F0BFD;
void _declspec ( naked ) HOOK_RwFrame_childless ()
{
	__asm
	{
		cmp esi, 0
		jz damn_hooker_got_pregnant_again
		mov eax, [esi+0x98]
		jmp RwFrame_childless_haveAChild

		// do not want killer-babies killing our game
damn_hooker_got_pregnant_again:
		pushad
	}
	//addMessageToChatWindow( "Unwanted pregnancy" );
	__asm{
		popad
		jmp RwFrame_childless_abortPregnancy
	}
}

// ---------------------------------------------------
// Handle SpiderFeet standing
/*
#define CALL_CMatrix__rotateAroundZ 0x5E1BBA

float CMatrix__rotateAroundZ_zAngle;
float CMatrix__rotateAroundZ_zAngleLast;
float CMatrix__rotateAroundZ_zAngleCosine;
float CMatrix__rotateAroundZ_zAngleSine;
const float fZero = 0.0f;
const float fOne = 1.0f;
CMatrix_Padded *CMatrix__rotateAroundZ_matrix;
CMatrix CMatrix__rotateAroundZ_transformMatrix;
CVector vecStraightUp( 0.0f, 0.0f, 1.0f );
CVector CMatrix__rotateAroundZ_gravityNormal;
float CMatrix__rotateAroundZ_theta;
CVector CMatrix__rotateAroundZ_rotationAxis;

void _cdecl CMatrix__rotateAroundZ_hook ()
{
	CMatrix__rotateAroundZ_matrix->ConvertToMatrix( CMatrix__rotateAroundZ_transformMatrix );
	CMatrix__rotateAroundZ_gravityNormal = -cheat_state->actor.gravityVector;
	//CMatrix__rotateAroundZ_transformMatrix.vUp.Normalize();
	//CMatrix__rotateAroundZ_gravityNormal.Normalize();

	//
	// first we need to rotate the matrix fully up to set heading
	//

	// axis
	CMatrix__rotateAroundZ_rotationAxis = CMatrix__rotateAroundZ_transformMatrix.vUp;
	CMatrix__rotateAroundZ_rotationAxis.CrossProduct( &vecStraightUp );
	// theta
	CMatrix__rotateAroundZ_theta = CMatrix__rotateAroundZ_transformMatrix.vUp.DotProduct( &vecStraightUp );
	if ( !near_zero(CMatrix__rotateAroundZ_theta) )
	{
		// rotate
		CMatrix__rotateAroundZ_transformMatrix = CMatrix__rotateAroundZ_transformMatrix.Rotate( &CMatrix__rotateAroundZ_rotationAxis, -cos(CMatrix__rotateAroundZ_theta) );
	}

	// set heading
	CMatrix__rotateAroundZ_zAngleCosine = cos(CMatrix__rotateAroundZ_zAngle);
	CMatrix__rotateAroundZ_zAngleSine = sin(CMatrix__rotateAroundZ_zAngle);
	CMatrix__rotateAroundZ_transformMatrix.vRight.fX = CMatrix__rotateAroundZ_zAngleCosine;
	CMatrix__rotateAroundZ_transformMatrix.vRight.fY = CMatrix__rotateAroundZ_zAngleSine;
	CMatrix__rotateAroundZ_transformMatrix.vFront.fX = -CMatrix__rotateAroundZ_zAngleSine;
	CMatrix__rotateAroundZ_transformMatrix.vFront.fY = CMatrix__rotateAroundZ_zAngleCosine;


	//
	// now we need to rotate it back to be at the correct angle for the gravity
	//

	// axis
	CMatrix__rotateAroundZ_rotationAxis = CMatrix__rotateAroundZ_transformMatrix.vUp;
	CMatrix__rotateAroundZ_rotationAxis.CrossProduct( &CMatrix__rotateAroundZ_gravityNormal );
	// theta
	CMatrix__rotateAroundZ_theta = CMatrix__rotateAroundZ_transformMatrix.vUp.DotProduct( &CMatrix__rotateAroundZ_gravityNormal );
	if ( !near_zero(CMatrix__rotateAroundZ_theta) )
	{
		// rotate
		CMatrix__rotateAroundZ_transformMatrix = CMatrix__rotateAroundZ_transformMatrix.Rotate( &CMatrix__rotateAroundZ_rotationAxis, -cos(CMatrix__rotateAroundZ_theta) );
	}

	// apply matrix
	CMatrix__rotateAroundZ_matrix->SetFromMatrix( CMatrix__rotateAroundZ_transformMatrix );
	CMatrix__rotateAroundZ_zAngleLast = CMatrix__rotateAroundZ_zAngle;
}

void _declspec ( naked ) HOOK_CMatrix__rotateAroundZ ()
{
	// input variables
	__asm
	{
		mov eax, dword ptr [esp+4]
		mov CMatrix__rotateAroundZ_zAngle, eax
		mov CMatrix__rotateAroundZ_matrix, ecx
		pushad
	}

	if ( cheat_state->actor.SpiderFeet_on && pPedSelfSA
		&& CMatrix__rotateAroundZ_matrix == pPedSelfSA->Placeable.matrix )
	{
		// it's our matrix, so call our handler
		CMatrix__rotateAroundZ_hook();
	}
	else
	{
		// zero out matrix
		CMatrix__rotateAroundZ_matrix->vRight.fZ = fZero;
		CMatrix__rotateAroundZ_matrix->vFront.fZ = fZero;
		CMatrix__rotateAroundZ_matrix->vUp.fX = fZero;
		CMatrix__rotateAroundZ_matrix->vUp.fY = fZero;
		CMatrix__rotateAroundZ_matrix->vUp.fZ = fOne;

		//zAngle
		CMatrix__rotateAroundZ_zAngleCosine = cos(CMatrix__rotateAroundZ_zAngle);
		CMatrix__rotateAroundZ_zAngleSine = sin(CMatrix__rotateAroundZ_zAngle);
		CMatrix__rotateAroundZ_matrix->vRight.fX = CMatrix__rotateAroundZ_zAngleCosine;
		CMatrix__rotateAroundZ_matrix->vRight.fY = CMatrix__rotateAroundZ_zAngleSine;
		CMatrix__rotateAroundZ_matrix->vFront.fX = -CMatrix__rotateAroundZ_zAngleSine;
		CMatrix__rotateAroundZ_matrix->vFront.fY = CMatrix__rotateAroundZ_zAngleCosine;
	}

	__asm
	{
		popad
		retn 4
	}
}
*/


// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------

CMatrix gravCamPed_matGravity;
CMatrix gravCamPed_matInvertGravity;
CMatrix gravCamPed_matPedTransform;
CVector gravCamPed_vecPedVelocity;


CVector gravCamPed_vecCameraFrontTarget = g_vecFrontNormal;
CVector gravCamPed_vecCameraFrontOffset;
CVector gravCamPed_vecCameraFrontLastSet = g_vecFrontNormal;

CVector gravCamPed_vecCameraUpTarget = g_vecUpNormal;
CVector gravCamPed_vecCameraUpLastSet = g_vecUpNormal;

CVector gravCamPed_vecCameraRightTarget = g_vecRightNormal;
CVector gravCamPed_vecCameraRightLastSet = g_vecRightNormal;

CVector gravCamPed_vecCameraPosLastSet;

CVector gravCamPed_vecCameraPanSource;

// ---------------------------------------------------

#define HOOKPOS_PedCamStart 0x522D78
DWORD	RETURN_PedCamStart_success = 0x522D7E;
DWORD	RETURN_PedCamStart_failure = 0x5245A2;

bool _cdecl PedCamStart ( DWORD dwCam, DWORD pPedInterface )
{
	traceLastFunc( "PedCamStart()" );

	// Inverse transform some things so that they match a downward pointing gravity.
	// This way SA's gravity-goes-downward assumptive code can calculate the camera
	// spherical coords correctly. Of course we restore these after the camera function
	// completes.
	CPed	*pPed = pPools->GetPed( (DWORD *)pPedInterface );

	if ( !pPed )
		return false;

	// get cam
	CCamSAInterface* cam = (CCamSAInterface*)dwCam;

	CVector vecGravity;
	pPed->GetGravity( &vecGravity );

	GetMatrixForGravity( vecGravity, gravCamPed_matGravity );
	gravCamPed_matInvertGravity = gravCamPed_matGravity;
	gravCamPed_matInvertGravity.Invert();

	pPed->GetMatrix( &gravCamPed_matPedTransform );

	//CMatrix matPedInverted = gravCamPed_matInvertGravity * gravCamPed_matPedTransform;
	//matPedInverted.vPos = gravCamPed_matPedTransform.vPos;
	//pPed->SetMatrix( &matPedInverted );

	pPed->GetMoveSpeed( &gravCamPed_vecPedVelocity );

	CVector vecVelocityInverted = gravCamPed_matInvertGravity * gravCamPed_vecPedVelocity;
	//pPed->SetMoveSpeed( &vecVelocityInverted );



	
	// get speed to effect camera
	CVector vecSpeed;
	pPedSelf->GetMoveSpeed(&vecSpeed);

	// this works because CCameraSAInterface pointer is the first thing in CCamera
	CCameraSAInterface *cameraInterface = (CCameraSAInterface*)pGame->GetCamera();

	if (cameraInterface != NULL)
	{
		// testing grounds to try to make the camera smoother,
		// but i'll probably have to create a new hook for it. -nf

		//cameraInterface->m_bCamDirectlyBehind = false;
		//cameraInterface->m_bItsOkToLookJustAtThePlayer = false;
		//cameraInterface->m_bResetOldMatrix = false;
		//cameraInterface->m_bUseTransitionBeta = false;
		//cameraInterface->m_bWaitForInterpolToFinish = false;
/*
*/
		cameraInterface->m_vecAttachedCamLookAt = gravCamPed_vecCameraFrontLastSet;
		cameraInterface->m_vecAttachedCamOffset = cam->Source - gravCamPed_vecCameraPanSource;
		cameraInterface->m_vecBottomFrustumNormal = -gravCamPed_vecCameraUpLastSet;
		cameraInterface->m_vecTopFrustumNormal = gravCamPed_vecCameraUpLastSet;

		CMatrix setCamera;
		//setCamera.vFront = gravCamPed_vecCameraFrontLastSet;
		//setCamera.vUp = gravCamPed_vecCameraUpLastSet;
		setCamera.vRight = gravCamPed_vecCameraFrontLastSet;
		setCamera.vRight.CrossProduct(&gravCamPed_vecCameraUpLastSet);
		//setCamera.vPos = cam->Source;
		//cameraInterface->m_cameraMatrixOld.SetFromMatrix(setCamera);
		cameraInterface->m_vecRightFrustumNormal = setCamera.vRight;

		// disabled to test more stably, none of this really fixes it anyways, only makes it "less"
		//cameraInterface->SourceDuringInter = cam->Source - gravCamPed_vecCameraPanSource;
		//cameraInterface->TargetDuringInter = gravCamPed_vecCameraFrontLastSet;
		//cameraInterface->UpDuringInter = gravCamPed_vecCameraUpLastSet;
		//

		//gravCamPed_vecCameraPosLastSet

		// somehow this is causing exceptions, sometimes about vehicle type 406 not being created?!?
		//cameraInterface->m_vecSourceWhenInterPol = cam->Source - gravCamPed_vecCameraPanSource;
		//cameraInterface->m_vecTargetWhenInterPol = gravCamPed_vecCameraFrontTarget;
		//cameraInterface->m_vecUpWhenInterPol = gravCamPed_vecCameraUpTarget;

		//cameraInterface->m_iWorkOutSpeedThisNumFrames = 4; // probably crashes

		//cameraInterface->m_cvecStartingSourceForInterPol = cam->Source; // crashes
		//cameraInterface->m_cvecStartingTargetForInterPol = gravCamPed_vecCameraFrontLastSet; // crashes
		//cameraInterface->m_PreviousCameraPosition = cam->Source; // samp exceptions
		//cameraInterface->m_RealPreviousCameraPosition = cam->Source; // samp exceptions
		//cameraInterface->m_vecOldFrontForInter = gravCamPed_vecCameraFrontLastSet; // crashes
		//cameraInterface->m_cvecStartingUpForInterPol = gravCamPed_vecCameraUpLastSet; // crashes
		//cameraInterface->m_cvecSourceSpeedAtStartInter = vecSpeed; // samp exceptions
		//cameraInterface->m_vecOldUpForInter = gravCamPed_vecCameraUpLastSet; // samp exceptions
		//cameraInterface->m_vecOldSourceForInter = gravCamPed_vecCameraPosLastSet; // samp exceptions
	}
	

	return true;
}

void _declspec ( naked ) HOOK_PedCamStart ()
{
	_asm
	{
		push ebp;
		push edi;
		call PedCamStart;
		add esp, 8;

		test eax, eax;
		jz fail;
		mov eax, [ebp + 0x598];
		jmp RETURN_PedCamStart_success;

fail:
		add esp, 4;
		jmp RETURN_PedCamStart_failure;
	}
}

// ---------------------------------------------------

#define HOOKPOS_PedCamLookDir1	0x52346C
DWORD	RETURN_PedCamLookDir1 = 0x523471;

void _cdecl PedCamLookDir1 ( DWORD dwCam, DWORD pPedInterface )
{
	traceLastFunc( "PedCamLookDir1()" );

	// For the same reason as in PedCamStart, inverse transform the camera's lookdir
	// at this point
	CVector *pvecLookDir = ( CVector * ) ( dwCam + 0x190 );
	//*pvecLookDir = gravCamPed_matInvertGravity * ( *pvecLookDir );
	//*pvecLookDir = gravCamPed_matGravity * ( *pvecLookDir );
	*pvecLookDir = gravCamPed_vecCameraFrontLastSet;
}

void _declspec ( naked ) HOOK_PedCamLookDir1 ()
{
	_asm
	{
		mov eax, 0x59C910;	// CVector::Normalise
		call eax;

		push ebp;
		push edi;
		call PedCamLookDir1;
		add esp, 8;

		jmp RETURN_PedCamLookDir1;
	}
}

// ---------------------------------------------------

#define HOOKPOS_PedCamLookDir2	0x5241CC
DWORD	RETURN_PedCamLookDir2 = 0x524213;
CEntitySA* gravCamPed_panEntity;

bool _cdecl PedCamLookDir2 ( DWORD dwCam )
{
	traceLastFunc( "PedCamLookDir2()" );

	if ( cheat_state
		&& cheat_state->actor.fly_active )
	{

		CCamSAInterface* cam = (CCamSAInterface*)dwCam;
		//CCameraSA* camera = (CCameraSA*)pGame->GetCamera();
		//CCameraSAInterface* camerasa = (CCameraSAInterface*)camera->GetInterface();

		// get speed to effect camera
		CVector vecSpeed;
		pPedSelf->GetMoveSpeed(&vecSpeed);

		// get originally intended camera direction, controlled directly by mouse/gamepad
		float	fPhi = cam->Beta;
		float	fTheta = cam->Alpha;


		CMatrix matGravityNormal;
		// change not needed if the actual gravity downforce doesn't change
		//matGravityNormal.vFront = gravCamPed_matGravity.vFront;
		//GetMatrixForGravity( -g_vecUpNormal, matGravityNormal );

		gravCamPed_vecCameraFrontTarget =
			-matGravityNormal.vRight *
			cos( fPhi ) *
			cos( fTheta ) -
			matGravityNormal.vFront *
			sin( fPhi ) *
			cos( fTheta ) +
			matGravityNormal.vUp *
			sin( fTheta );
		gravCamPed_vecCameraFrontTarget.Normalize();

		// populate a matrix for rotation
		CMatrix camRotate = CMatrix();
		CMatrix matCamera;
		pGame->GetCamera()->GetMatrix(&matCamera);
		camRotate.vRight = matCamera.vRight;
		camRotate.vFront = gravCamPed_vecCameraFrontLastSet;
		camRotate.vUp = gravCamPed_vecCameraUpLastSet;

		// rotate the camera front
		CVector rotationAxis = gravCamPed_vecCameraFrontLastSet;
		rotationAxis.CrossProduct( &gravCamPed_vecCameraFrontTarget );

		float thetaBase = gravCamPed_vecCameraFrontLastSet.DotProduct(&gravCamPed_vecCameraFrontTarget);
		float thetaCorrection = 0.0f;
		if (thetaBase < 0.3f)
		{
			thetaCorrection = 0.3f - thetaBase;
		}

		// smooth camera rotation
		float rotationMultiplier = (g_timeDiff * 69.0f) / ( 14.0f + (vecSpeed.Length() * 3.0f) - (thetaCorrection * 14.0f) );
		float theta = -cos(thetaBase) * rotationMultiplier;

		if ( !near_zero(theta) )
		{
			// rotate the camera
			camRotate = camRotate.Rotate(&rotationAxis, theta);
			gravCamPed_vecCameraFrontLastSet = camRotate.vFront;
			gravCamPed_vecCameraUpLastSet = camRotate.vUp;
			gravCamPed_vecCameraRightLastSet = camRotate.vRight;
			gravCamPed_vecCameraFrontLastSet.Normalize();
			gravCamPed_vecCameraUpLastSet.Normalize();
			gravCamPed_vecCameraRightLastSet.Normalize();
			cam->Front = gravCamPed_vecCameraFrontLastSet;
			cam->Up = gravCamPed_vecCameraUpLastSet;
			// maybe fix the glitching?




			//cam->m_cvecSourceSpeedOverOneFrame = vecSpeed;
			//cam->m_cvecTargetSpeedOverOneFrame = vecSpeed;
			cam->SpeedVar = vecSpeed.Length();
			cam->Rotating = true;
			cam->bBehindPlayerDesired = false;
			cam->m_nCurrentHistoryPoints = 0;
			//cam->
			/*
			*/

			// rotate the reference
			gravCamPed_matGravity = gravCamPed_matGravity.Rotate(&rotationAxis, -theta);
		}


		// set this value that gets used for other calculations when we return
		//*(float *)0x8CCE6C = cos(gravCamPed_vecCameraFrontLastSet.GetAngleDegrees());
		//*(float *)0x8CCE6C = gravCamPed_vecCameraUpLastSet.GetAngleDegrees();
		*(float *)0x8CCE6C = fPhi;

		// set offset so we can use it in other things like Player Fly
		gravCamPed_vecCameraFrontOffset = gravCamPed_vecCameraFrontTarget - gravCamPed_vecCameraFrontLastSet;
		g_f_debugDisplay[1] = gravCamPed_vecCameraFrontOffset.Length();




		// helps center some movements of the camera around the ped
		cam->m_fBufferedTargetBeta = 0.0f;



	}
	else
	{
		// Calculates the look direction vector for the ped camera. This vector
		// is later multiplied by a factor and added to the ped position by SA
		// to obtain the final camera position.watching

		float	fPhi = *(float *)( dwCam + 0xBC );
		float	fTheta = *(float *)( dwCam + 0xAC );

		// old raw gravity based movement
		gravCamPed_vecCameraFrontLastSet =
			-gravCamPed_matGravity.vRight *
			cos( fPhi ) *
			cos( fTheta ) -
			gravCamPed_matGravity.vFront *
			sin( fPhi ) *
			cos( fTheta ) +
			gravCamPed_matGravity.vUp *
			sin( fTheta );
		gravCamPed_vecCameraFrontLastSet.Normalize();
		*( CVector * ) ( dwCam + 0x190 ) = gravCamPed_vecCameraFrontLastSet;
		*(float *)0x8CCE6C = fPhi;
		gravCamPed_vecCameraFrontOffset = CVector(0.0f, 0.0f, 0.0f);
	}

	traceLastFunc( "PedCamLookDir2() End" );
	return true;
}

void _declspec ( naked ) HOOK_PedCamLookDir2 ()
{
	_asm
	{
		push edi; // pCam
		call PedCamLookDir2;
		add esp, 4;

		lea eax, [edi + 0x190];
		jmp RETURN_PedCamLookDir2;
	}
}

// ---------------------------------------------------

#define HOOKPOS_PedCamHistory	0x5242CD
DWORD	RETURN_PedCamHistory = 0x5243B1;

void _cdecl PedCamHistory ( DWORD dwCam, CVector *pvecTarget, float fTargetTheta, float fRadius, float fZoom )
{
	traceLastFunc( "PedCamHistory()" );

	if ( cheat_state
		&& cheat_state->actor.fly_active )
	{
		CVector vecDir = gravCamPed_vecCameraFrontLastSet;
		( (CVector *) (dwCam + 0x1D8) )[0] = *pvecTarget - vecDir * fRadius;
		( (CVector *) (dwCam + 0x1D8) )[1] = *pvecTarget - vecDir * fZoom;
	}
	else
	{
		float	fPhi = *(float *)( dwCam + 0xBC );
		CVector vecDir = -gravCamPed_matGravity.vRight * cos( fPhi ) * cos( fTargetTheta ) - gravCamPed_matGravity.vFront * sin( fPhi ) * cos( fTargetTheta ) + gravCamPed_matGravity.vUp * sin( fTargetTheta );
		( (CVector *) (dwCam + 0x1D8) )[0] = *pvecTarget - vecDir * fRadius;
		( (CVector *) (dwCam + 0x1D8) )[1] = *pvecTarget - vecDir * fZoom;
	}
}

void _declspec ( naked ) HOOK_PedCamHistory ()
{
	_asm
	{
		push[esp + 0x0 + 0x7C]; // zoom
		push[esp + 0x4 + 0x2C]; // radius
		push[esp + 0x8 + 0x14]; // targetTheta
		lea ecx, [esp + 0xC + 0x48]; // pushed on the next line
		push ecx; // pvecTarget - ecx?
		push ebx; // pCam
		call PedCamHistory;
		add esp, 0x14;

		mov edx, [esp + 0x24];
		jmp RETURN_PedCamHistory;
	}
}

// ---------------------------------------------------

#define CALL_PedCamUp		0x524527
void _cdecl PedCamUp ( DWORD dwCam )
{
	traceLastFunc( "PedCamUp()" );

	if (!dwCam)
		return;

	CCamSAInterface* cam = (CCamSAInterface*)dwCam;

	if ( cheat_state
		&& cheat_state->actor.fly_active )
	{
		
		// Calculates the up vector for the ped camera.
		CVector *pvecUp = ( CVector * ) ( dwCam + 0x1B4 );
		CVector *pvecLookDir = ( CVector * ) ( dwCam + 0x190 );

		if (!pvecUp || !pvecLookDir)
			return;

		// get speed to effect camera
		CVector vecSpeed;
		pPedSelf->GetMoveSpeed(&vecSpeed);

		// tone down the movement
		CVector smoothedGrav = gravCamPed_matGravity.vUp + (g_vecUpNormal * 1.445f);
		smoothedGrav.Normalize();

		CVector newVecUp = *pvecLookDir;
		newVecUp.fZ = 0.0f;
		//newVecUp.Normalize();
		newVecUp.CrossProduct( &smoothedGrav );
		newVecUp.CrossProduct( pvecLookDir );
		//newVecUp.Normalize();

		if (!newVecUp.IsNearZero())
		{
			*pvecUp = newVecUp;
			gravCamPed_matGravity.vUp = newVecUp;
			gravCamPed_vecCameraUpLastSet = newVecUp;
		}




		


		// set our target source position offset
		// this is a feedback system, so be careful with how it's tuned.
		// this is needed or you have to do a lot more heavy math
		// to properly handle a more complete rotation ability of
		// a camera.vFront  but it IS possible to fly around without
		// any limitations to the camera, and to make controls so you
		// can have elevators in any vehicle, or object. :)
		CVector vecCameraPanTargetSmoother = gravCamPed_vecCameraFrontOffset - gravCamPed_vecCameraPanSource;

		gravCamPed_vecCameraPanSource +=
			(vecCameraPanTargetSmoother / 3.0f ) // added to camera pan
			* (vecCameraPanTargetSmoother.Length() / 50.0f) // return to zero
			* (g_timeDiff * 69.0f); // fps/timing

		gravCamPed_vecCameraPosLastSet = cam->Source - gravCamPed_vecCameraPanSource;
		cam->Source = gravCamPed_vecCameraPosLastSet;














		// development stuff below here.
		// use the ideas in this and the player fly code to make
		// a car fly mode that just flies toward the mouse, but...
		// with air-craft physics of course. :)
		//
		// have fun. merry xmas, and hopefully many happy hookers for Kye's new year's.
		// -nf

		// p.s. someone do something with SpiderFeet.
		// it can be done, if the collision z placements are fixed.
		// then move the camera based on 5 collisions under the player when not on the
		// ground, and at least two to detect proximity in front on the player, to
		// make the player start running across the surfaces more accurately.
		// and to enable, of course, jumping around corners sideways and such.
		// nananananananananananananananana Kyebatman.












		//CVector newVecUp = gravCamPed_vecCameraFrontOffset;
		// gravCamPed_vecCameraFrontLastSet
		/*
		CVector upStrafeAxis = matCamera.vFront;
		upStrafeAxis.CrossProduct(&matPedTarget.vUp);
		theta = -1.5; // 1.57 = 90 degrees
		matPedTarget = matPedTarget.Rotate( &upStrafeAxis, theta );

		*/




		/*
		// populate a matrix for rotation
		CMatrix camRotate = CMatrix();
		camRotate.vFront = gravCamPed_vecCameraFrontOffset;
		camRotate.vFront.fZ = 0.0f;
		camRotate.vFront.Normalize();
		//camRotate.vUp = gravCamPed_vecCameraUpLastSet;
		CMatrix matCamera;
		pGame->GetCamera()->GetMatrix(&matCamera);
		camRotate.vRight = -matCamera.vRight;


		// flip front offset up
		float theta = -1.57; // 1.57 = 90 degrees
		camRotate = camRotate.Rotate( &camRotate.vRight, theta );


		*pvecUp = camRotate.vFront;
		gravCamPed_matGravity.vUp = camRotate.vFront;
		gravCamPed_vecCameraUpLastSet = camRotate.vFront;
		*/


		/*
		// rotate the camera vUp
		CVector rotationAxis = camRotate.vRight;
		//rotationAxis.CrossProduct( &gravCamPed_vecCameraFrontTarget );

		float thetaBase = gravCamPed_vecCameraFrontLastSet.DotProduct(&gravCamPed_vecCameraFrontTarget);
		float thetaCorrection = 0.0f;
		if (thetaBase < 0.3f)
		{
			thetaCorrection = 0.3f - thetaBase;
		}

		// smooth camera rotation
		float rotationMultiplier = (g_timeDiff * 69.0f) / ( 14.0f + (vecSpeed.Length() * 3.0f) - (thetaCorrection * 14.0f) );
		theta = -cos(thetaBase) * rotationMultiplier;

		if ( !near_zero(theta) )
		{
			// rotate the camera
			camRotate = camRotate.Rotate(&rotationAxis, theta);
			gravCamPed_vecCameraFrontLastSet = camRotate.vFront;
			gravCamPed_vecCameraUpLastSet = camRotate.vUp;
			gravCamPed_vecCameraFrontLastSet.Normalize();
			gravCamPed_vecCameraUpLastSet.Normalize();
			cam->Front = gravCamPed_vecCameraFrontLastSet;
			cam->Up = gravCamPed_vecCameraUpLastSet;
			// rotate the reference
			gravCamPed_matGravity = gravCamPed_matGravity.Rotate(&rotationAxis, -theta);
		}
		*/




		/*
		// get speed to effect camera
		CVector vecSpeed;
		pPedSelf->GetMoveSpeed(&vecSpeed);

		// populate a matrix for rotation
		CMatrix camRotate = CMatrix();
		camRotate.vUp = gravCamPed_vecCameraUpLastSet;

		// smooth camera rotation
		float rotationMultiplier = (g_timeDiff * 69.0f) / ( 14.0f + (vecSpeed.Length() * 4.0f) );

		// set Up vector target
		CVector smoothedGrav = gravCamPed_matGravity.vUp + (g_vecUpNormal * 2.0f);
		smoothedGrav.Normalize();

		gravCamPed_vecCameraUpTarget = cam->Front;
		gravCamPed_vecCameraUpTarget.CrossProduct( &smoothedGrav );
		gravCamPed_vecCameraUpTarget.CrossProduct( &cam->Front );
		gravCamPed_vecCameraUpTarget.Normalize();

		// rotate Up vector
		CVector rotationAxis = gravCamPed_vecCameraUpLastSet;
		rotationAxis.CrossProduct( &gravCamPed_vecCameraUpTarget );
		float thetaBase = gravCamPed_vecCameraUpLastSet.DotProduct(&gravCamPed_vecCameraUpTarget);
		float theta = -cos(thetaBase) * rotationMultiplier;
		if ( !near_zero(theta) )
		{
			camRotate = camRotate.Rotate( &rotationAxis, theta );
			gravCamPed_vecCameraUpLastSet = camRotate.vUp;
			gravCamPed_vecCameraUpLastSet.Normalize();
			cam->Up = gravCamPed_vecCameraUpLastSet;
		}
		*/


		//// set our target source position offset
		//CVector vecCameraPanTarget = gravCamPed_vecCameraPanOffset;
		//vecCameraPanTarget.Normalize();
		//float vecCameraPanSourceLength = gravCamPed_vecCameraPanSource.Length();
		//gravCamPed_vecCameraPanSource.Normalize();

		//// get speed to effect source
		//CVector vecSpeed;
		//pPedSelf->GetMoveSpeed(&vecSpeed);

		//// populate a matrix for rotation
		//CMatrix camSourceRotate = CMatrix();
		//camSourceRotate.vFront = gravCamPed_vecCameraPanSource;

		//// smooth source position offset
		//float rotationMultiplier = (g_timeDiff * 69.0f) / ( 2.0f + (vecSpeed.Length() * 4.0f) );

		//// rotate the source position offset in a front vector
		//CVector rotationAxis = gravCamPed_vecCameraPanSource;
		//rotationAxis.CrossProduct( &vecCameraPanTarget );
		//float thetaBase = gravCamPed_vecCameraPanSource.DotProduct(&vecCameraPanTarget);
		//float theta = -cos(thetaBase) * rotationMultiplier;
		//if ( !near_zero(theta) )
		//{
		//	camSourceRotate = camSourceRotate.Rotate( &rotationAxis, theta );
		//}

		//// set the source position offset
		//gravCamPed_vecCameraPanSource = camSourceRotate.vFront * vecCameraPanSourceLength;
		//cam->Source = cam->Source - gravCamPed_vecCameraPanSource;





		//cam->SourceBeforeLookBehind = cam->Source + gravCamPed_vecCameraPanSource;
		//cam->m_aTargetHistoryPos[3] = cam->m_aTargetHistoryPos[2];
		//cam->m_aTargetHistoryPos[2] = cam->m_aTargetHistoryPos[1];
		//cam->m_aTargetHistoryPos[1] = cam->m_aTargetHistoryPos[0];
		//cam->m_aTargetHistoryPos[0] = cam->Source;

		//cam->m_cvecSourceSpeedOverOneFrame = vecSpeed;
		//cam->m_cvecTargetSpeedOverOneFrame = vecSpeed;
		//cam->m_fBufferedTargetOrientationSpeed = gravCamPed_vecCameraPanSource.Length();






	}
	else
	{
		// Calculates the up vector for the ped camera.
		// 0x: Let, GTA:SA Calc it if there are any problems, there are numerous fixes.
	}
}

void _declspec ( naked ) HOOK_PedCamUp ()
{
	_asm
	{
		mov edx, ecx;
		mov ecx, [ecx + 0x21C]; // CCam::pTargetEntity
		mov eax, 0x46A2C0; // CEntity::GetType
		call eax;

		cmp al, 3; // Is it a ped?
		jz docustom;

		mov ecx, edx;
		mov eax, 0x509CE0; // CCam::GetVectorsReadyForRW
		jmp eax;

docustom:
		push edx;
		call PedCamUp;
		add esp, 4;
		ret;
	}
}

// ---------------------------------------------------

#define HOOKPOS_PedCamEnd	0x524527
DWORD	RETURN_PedCamEnd = 0x524530;

void _cdecl PedCamEnd ( DWORD pPedInterface )
{
	traceLastFunc( "PedCamEnd()" );

	// Restore the things that we inverse transformed in VehicleCamStart
	/*
	CPed	*pPed = pPools->GetPed( (DWORD *)pPedInterface );
	if ( !pPed )
		return;
	pPed->SetMatrix( &gravCamPed_matPedTransform );
	pPed->SetMoveSpeed( &gravCamPed_vecPedVelocity );
	*/
}

void _declspec ( naked ) HOOK_PedCamEnd ()
{
	_asm
	{
		mov		eax, 0x509CE0;
		call    eax;
		pop     esi;
		test    ebx, ebx;
		pop     ebx;

		push edi;
		call PedCamEnd;
		add esp, 4;

		jmp RETURN_PedCamEnd;
	}
}



// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------



// ---------------------------------------------------
// hook installers
void cheat_hookers_installhooks ( void )
{
	// ped cam
	/*HookInstall( HOOKPOS_PedCamStart, (DWORD) HOOK_PedCamStart, 6 );
	HookInstall( HOOKPOS_PedCamLookDir1, (DWORD) HOOK_PedCamLookDir1, 5 );
	HookInstall( HOOKPOS_PedCamLookDir2, (DWORD) HOOK_PedCamLookDir2, 6 );
	HookInstall( HOOKPOS_PedCamHistory, (DWORD) HOOK_PedCamHistory, 8 );
	HookInstallCall( CALL_PedCamUp, (DWORD) HOOK_PedCamUp );*/
	//HookInstall( HOOKPOS_PedCamEnd, (DWORD) HOOK_PedCamEnd, 9 );

	// vehicle cam
	HookInstall( HOOKPOS_VehicleCamStart, (DWORD) HOOK_VehicleCamStart, 6 );
	HookInstall( HOOKPOS_VehicleCamTargetZTweak, (DWORD) HOOK_VehicleCamTargetZTweak, 8 );
	HookInstall( HOOKPOS_VehicleCamLookDir1, (DWORD) HOOK_VehicleCamLookDir1, 5 );
	HookInstall( HOOKPOS_VehicleCamLookDir2, (DWORD) HOOK_VehicleCamLookDir2, 6 );
	HookInstall( HOOKPOS_VehicleCamHistory, (DWORD) HOOK_VehicleCamHistory, 6 );
	HookInstall( HOOKPOS_VehicleCamEnd, (DWORD) HOOK_VehicleCamEnd, 6 );
	HookInstall( HOOKPOS_VehicleLookBehind, (DWORD) HOOK_VehicleLookBehind, 6 );
	HookInstall( HOOKPOS_VehicleLookAside, (DWORD) HOOK_VehicleLookAside, 6 );
	HookInstallCall( CALL_VehicleCamUp, (DWORD) HOOK_VehicleCamUp );
	HookInstallCall( CALL_VehicleLookBehindUp, (DWORD) HOOK_VehicleCamUp );
	HookInstallCall( CALL_VehicleLookAsideUp, (DWORD) HOOK_VehicleCamUp );

	// CPhysical gravity
	HookInstall( HOOKPOS_CPhysical_ApplyGravity, (DWORD) HOOK_CPhysical_ApplyGravity, 6 );

	// pool population
	HookInstall( HOOKPOS_CVehicle_constructor, (DWORD) HOOK_CVehicle_constructor, 6 );
	HookInstall( HOOKPOS_CVehicle_destructor, (DWORD) HOOK_CVehicle_destructor, 6 );
	HookInstall( HOOKPOS_CPed_constructor, (DWORD) HOOK_CPed_constructor, 6 );
	HookInstall( HOOKPOS_CPed_destructor, (DWORD) HOOK_CPed_destructor, 6 );

	// collision removal
	HookInstall( HOOKPOS_PlayerCollision, (DWORD) HOOK_PlayerCollision, 6 );
	HookInstall( HOOKPOS_CEntity_Render, (DWORD) HOOK_RenderEntity, 6 );
	HookInstall( HOOKPOS_Player_Climb, (DWORD) HOOK_PlayerClimb, 9 );

	// Get rid of unwanted stuff (like killer babies)
	HookInstall( HOOKPOS_RwFrame_childless, (DWORD) HOOK_RwFrame_childless, 6 );

	// SpiderFeet
	//HookInstallCall( CALL_CMatrix__rotateAroundZ, (DWORD) HOOK_CMatrix__rotateAroundZ );
}
