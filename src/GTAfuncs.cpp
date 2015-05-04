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

int GTAfunc_isModelLoaded ( int iModelID )
{
	int *ModelsLoadStateArray = (int *)0x8E4CD0;
	return ModelsLoadStateArray[5 * iModelID];
}

void GTAfunc_requestModelLoad ( int iModelID )
{
	if ( iModelID < 0 )
		return;
	__asm
	{
		push 2
		push iModelID
		mov edx, FUNC_RequestModel
		call edx
		pop edx
		pop edx
	}
}

void GTAfunc_loadRequestedModels ( void )
{
	uint32_t	func_load = FUNC_LoadAllRequestedModels;
	__asm
	{
		push 0
		call func_load
		add esp, 4
	}
}

bool GTAfunc_IsUpgradeAvailable ( int m_dwModelID, eVehicleUpgradePosn posn )
{
	bool	bRet = false;
	DWORD	ModelID = m_dwModelID;
	__asm
	{
		mov eax, ModelID
		lea ecx, ARRAY_ModelInfo[eax * 4]

		mov eax, posn
		mov ecx, [ecx + 0x5C]
		shl eax, 5
		push esi
		mov esi, [ecx + eax + 0x0D0]
		xor edx, edx
		test esi, esi
		setnl dl
		mov al, dl
		pop esi

		mov bRet, al
	}

	return bRet;
}

void GTAfunc_requestAnyVehicleUpgrade ( vehicle_info *vinfo, int iModelID )
{
	if ( vinfo == NULL )
		return;

	DWORD	dwFunction = FUNC_RequestAnyVehicleUpgrade;
	__asm
	{
		mov ecx, vinfo
		push iModelID
		call dwFunction
	}
}

void GTAfunc_removeVehicleUpgrade ( vehicle_info *vinfo, int iModelID )
{
	if ( vinfo == NULL )
		return;

	uint32_t	func_upgrade = 0x6DF930;
	__asm
	{
		mov ecx, vinfo
		push iModelID
		call func_upgrade
	}
}

// turn off annoying performance warning
#pragma warning( disable : 4800 )
bool GTAfunc_vehicle_iModelID_IsCar ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsCarModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsBike ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsBikeModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsPlane ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsPlaneModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsHeli ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsHeliModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsBoat ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsBoatModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsQuadBike ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsQuadBikeModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsBmx ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsBmxModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsMonsterTruck ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsMonsterTruckModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsTrailer ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsTrailerModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

bool GTAfunc_vehicle_iModelID_IsTrain ( int m_dwModelID )
{
	DWORD	dwFunction = FUNC_IsTrainModel;
	DWORD	ModelID = m_dwModelID;
	BYTE	bReturn = 0;
	__asm
	{
		push ModelID
		call dwFunction
		mov bReturn, al
		add esp, 4
	}

	return ( bool ) bReturn;
}

// re-enable annoying performance warning
#pragma warning( default : 4800 )

// get paintjob
int GTAfunc_vehicle_getRemapIndex ( vehicle_info *vinfo )
{
	DWORD	dwFunc = FUNC_CVehicle__GetRemapIndex;
	int		iReturn = 0;
	__asm
	{
		mov ecx, vinfo
		call dwFunc
		mov iReturn, eax
	}

	return iReturn;
}

// set paintjob
void GTAfunc_vehicle_setRemap ( vehicle_info *vinfo, int iRemap )
{
	DWORD	dwFunc = FUNC_CVehicle__SetRemap;
	__asm
	{
		mov ecx, vinfo
		push iRemap
		call dwFunc
	}
}

int GTAfunc_getNumVideoModes ( void )
{
	int		uiReturn = 0;
	DWORD	dwFunc = GFUNC_GetNumVideoModes;
	__asm
	{
		call dwFunc
		mov uiReturn, eax
	}

	return uiReturn;
}

VideoMode *GTAfunc_getVideoModeInfo ( VideoMode *modeInfo, int modeIndex )
{
	DWORD	dwFunc = GFUNC_GetVideoModeInfo;
	__asm
	{
		push modeIndex
		push modeInfo
		call dwFunc
		add esp, 8
	}

	return modeInfo;
}

int GTAfunc_getCurrentVideoMode ( void )
{
	int		uiReturn = 0;
	DWORD	dwFunc = GFUNC_GetCurrentVideoMode;
	__asm
	{
		call dwFunc
		mov uiReturn, eax
	}

	return uiReturn;
}

void GTAfunc_setCurrentVideoMode ( int modeIndex )
{
	DWORD	dwFunc = GFUNC_SetCurrentVideoMode;
	__asm
	{
		push modeIndex
		call dwFunc
		add esp, 4
	}
}

int GTAfunc_RwD3D9ChangeVideoMode ( int modeIndex )
{
	DWORD	dwFunc = FUNC_RwD3D9ChangeVideoMode;
	__asm
	{
		push modeIndex
		call dwFunc
		add esp, 4
	}
}

CVector GTAfunc_GetMoveSpeed ( object_base *entity )
{
	CVector vecMoveSpeed;
	DWORD	dwFunc = FUNC_GetMoveSpeed;
	DWORD	dwThis = ( DWORD ) entity;
	DWORD	dwReturn = 0;
	__asm
	{
		mov ecx, dwThis
		call dwFunc
		mov dwReturn, eax
	}

	memcpy_safe( &vecMoveSpeed, (void *)dwReturn, sizeof(CVector) );
	return vecMoveSpeed;
}

VOID GTAfunc_SetMoveSpeed ( object_base *entity, CVector vecMoveSpeed )
{
	DWORD	dwFunc = FUNC_GetMoveSpeed;
	DWORD	dwThis = ( DWORD ) entity;
	DWORD	dwReturn = 0;
	__asm
	{
		mov ecx, dwThis
		call dwFunc
		mov dwReturn, eax
	}

	memcpy_safe( (void *)dwReturn, &vecMoveSpeed, sizeof(CVector) );
}

bool GTAfunc_IsUpsideDown ( vehicle_info *vinfo )
{
	DWORD	dwThis = ( DWORD ) vinfo;
	DWORD	dwFunc = FUNC_CVehicle_IsUpsideDown;
	bool	bReturn = false;
	__asm
	{
		mov ecx, dwThis
		call dwFunc
		mov bReturn, al
	}

	return bReturn;
}

bool GTAfunc_IsOnItsSide ( vehicle_info *vinfo )
{
	DWORD	dwThis = ( DWORD ) vinfo;
	DWORD	dwFunc = FUNC_CVehicle_IsOnItsSide;
	bool	bReturn = false;
	__asm
	{
		mov ecx, dwThis
		call dwFunc
		mov bReturn, al
	}

	return bReturn;
}

bool GTAfunc_IsLineOfSightClear ( CVector *vecStart, CVector *vecEnd, bool bCheckBuildings, bool bCheckVehicles,
								  bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
								  bool bIgnoreSomeObjectsForCamera )
{
	DWORD	dwFunc = FUNC_IsLineOfSightClear;
	bool	bReturn = false;
	__asm
	{
		push bIgnoreSomeObjectsForCamera
		push bSeeThroughStuff
		push bCheckDummies
		push bCheckObjects
		push bCheckPeds
		push bCheckVehicles
		push bCheckBuildings
		push vecEnd
		push vecStart
		call dwFunc
		mov bReturn, al
		add esp, 0x24
	}

	return bReturn;
}

bool GTAfunc_ProcessLineOfSight ( CVector *vecStart, CVector *vecEnd, CColPoint **colCollision,
								  CEntitySAInterface **CollisionEntity, bool bCheckBuildings, bool bCheckVehicles,
								  bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
								  bool bIgnoreSomeObjectsForCamera, bool bShootThroughStuff )
{
	DWORD	dwPadding[100]; // stops the function missbehaving and overwriting the return address
	dwPadding[0] = 0;		// prevent the warning and eventual compiler optimizations from removing it
	CColPointSA				*pColPointSA = new CColPointSA();
	CColPointSAInterface	*pColPointSAInterface = pColPointSA->GetInterface();

	//DWORD targetEntity;
	CEntitySAInterface		*targetEntity = NULL;
	bool					bReturn = false;

	DWORD					dwFunc = FUNC_ProcessLineOfSight;
	__asm
	{
		push bShootThroughStuff
		push bIgnoreSomeObjectsForCamera
		push bSeeThroughStuff
		push bCheckDummies
		push bCheckObjects
		push bCheckPeds
		push bCheckVehicles
		push bCheckBuildings
		lea eax, targetEntity
		push eax
		push pColPointSAInterface
		push vecEnd
		push vecStart
		call dwFunc
		mov bReturn, al
		add esp, 0x30
	}

	// hacky method to point to CEntitySA instead of the above
	*CollisionEntity = targetEntity;
	if ( colCollision )
		*colCollision = pColPointSA;
	else
		pColPointSA->Destroy();

	return bReturn;
}

void GTAfunc_TogglePlayerControllable(bool bToggle)
{
	DWORD func = FUNC_MakePlayerSafe;
	float fTen = 10.0f;
	_asm
	{
		mov ecx,	ACTOR_POINTER_SELF
		push		fTen
		push		bToggle
		call		func
	}
}

void GTAfunc_LockActor(bool boolLock)
{
	DWORD *actor = (DWORD *)pPedSelfSA;

	if(actor)
	{
		if(boolLock)
		{
			_asm
			{
				mov ebx, dword ptr [actor]
				add ebx, 64
				or dword ptr [ebx], 0x2000
			}
		}
		else
		{
			_asm
			{
				mov ebx, dword ptr [actor]
				add ebx, 64
				and dword ptr [ebx], 0xFFFFDFFF
			}
		}
	}
}

void GTAfunc_PutActorInCar(vehicle_info *vehicle)
{
	CVehicle *pCurrentVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle_info_get(VEHICLE_SELF, 0));
	if(pCurrentVehicle)
	{
		CTaskSimpleCarSetPedOut* pOutTask = pGameInterface->GetTasks()->CreateTaskSimpleCarSetPedOut(pCurrentVehicle, 1, false);
		if(pOutTask)
		{
			// May seem illogical, but it'll crash without this
			pOutTask->SetKnockedOffBike(); 

			pOutTask->ProcessPed(pPedSelf);
			pOutTask->SetIsWarpingPedOutOfCar ();
			pOutTask->Destroy();
		}
	}

	CVehicle *pVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle);
	if(pVehicle)
	{
		CTaskSimpleCarSetPedInAsDriver* pInTask = pGameInterface->GetTasks()->CreateTaskSimpleCarSetPedInAsDriver(pVehicle);
		if(pInTask)
		{
			pInTask->SetIsWarpingPedIntoCar();
			pInTask->ProcessPed(pPedSelf);
			pInTask->Destroy();
		}
	}
}

void GTAfunc_PutActorInCarAsPassenger(vehicle_info *vehicle, int iSeat)
{
	CVehicle *pCurrentVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle_info_get(VEHICLE_SELF, 0));
	if(pCurrentVehicle)
	{
		CTaskSimpleCarSetPedOut* pOutTask = pGameInterface->GetTasks()->CreateTaskSimpleCarSetPedOut(pCurrentVehicle, 1, false);
		if(pOutTask)
		{
			// May seem illogical, but it'll crash without this
			pOutTask->SetKnockedOffBike(); 

			pOutTask->ProcessPed(pPedSelf);
			pOutTask->SetIsWarpingPedOutOfCar ();
			pOutTask->Destroy();
		}
	}

	CVehicle *pVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle);
	if(pVehicle)
	{
		CTaskSimpleCarSetPedInAsPassenger* pInTask = pGameInterface->GetTasks()->CreateTaskSimpleCarSetPedInAsPassenger(pVehicle, iSeat);
		if(pInTask)
		{
			pInTask->SetIsWarpingPedIntoCar();
			pInTask->ProcessPed(pPedSelf);
			pInTask->Destroy();
		}
	}
}

bool GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport = false;
void GTAfunc_RemoveActorFromCarAndPutAt(float fPos[3])
{
	CVehicle *pCurrentVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle_info_get(VEHICLE_SELF, 0));
	if(pCurrentVehicle)
	{
		CTaskSimpleCarSetPedOut* pOutTask = pGameInterface->GetTasks()->CreateTaskSimpleCarSetPedOut(pCurrentVehicle, 1, false);
		if(pOutTask)
		{
			// May seem illogical, but it'll crash without this
			pOutTask->SetKnockedOffBike(); 

			pOutTask->ProcessPed(pPedSelf);
			pOutTask->SetIsWarpingPedOutOfCar ();
			pOutTask->Destroy();

			GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport = true;
			cheat_teleport(fPos, 0);
		}
	}
}

void GTAfunc_EnterCarAsDriver(vehicle_info *vehicle)
{
	CVehicle *pVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle);
	if(pVehicle)
	{
		CTaskComplexEnterCarAsDriver* pInTask = pGameInterface->GetTasks()->CreateTaskComplexEnterCarAsDriver(pVehicle);
		if(pInTask)
			pInTask->SetAsPedTask(pPedSelf, TASK_PRIORITY_PRIMARY, true);
	}
}

void GTAfunc_RepairVehicle(vehicle_info *vehicle)
{
	CVehicle *pVehicle = pGameInterface->GetPools()->GetVehicle((DWORD *)vehicle);
	if(pVehicle)
	{
		pVehicle->Fix();
		pVehicle->SetHealth(1000.0f);
	}
}

void GTAfunc_CameraOnActor(actor_info *actor)
{
	if(actor == NULL) return;

	CEntity *pEntity = pGameInterface->GetPools()->GetEntity((DWORD *)actor);
	CCamera *pCamera = pGameInterface->GetCamera();
	if(pCamera && pEntity)
		pCamera->TakeControl(pEntity, MODE_FOLLOWPED, 1);
}

void GTAfunc_CameraOnVehicle(vehicle_info *vehicle)
{
	if(vehicle == NULL) return;

	CEntity *pEntity = pGameInterface->GetPools()->GetEntity((DWORD *)vehicle);
	CCamera *pCamera = pGameInterface->GetCamera();
	if(pCamera && pEntity)
		pCamera->TakeControl(pEntity, MODE_BEHINDCAR, 1);
}

void GTAfunc_PerformAnimation(const char *szBlockName, const char *szAnimName, int iTime, bool bLoop,
							  bool bUpdatePosition, bool bInterruptable, bool bFreezeLastFrame, bool bRunInSequence, bool bOffsetPed, bool bHoldLastFrame)
{
	CAnimBlock *pBlock = pGameInterface->GetAnimManager()->GetAnimationBlock(szBlockName);
	if(pBlock)
	{
		bool bLoaded = true;

		if(!pBlock->IsLoaded())
		{
			int iTimeToWait = 50;

			// load animations
			pGameInterface->GetStreaming()->RequestAnimations(pBlock->GetIndex(), 4);
			pGameInterface->GetStreaming()->LoadAllRequestedModels();

			while(!pBlock->IsLoaded() && iTimeToWait != 0)
			{
				iTimeToWait--;
				Sleep(10);
			}

			if(iTimeToWait == 0)
				bLoaded = false;
		}

		if(bLoaded)
		{
			// allow tasks to be removed
			pPedSelf->GetPedIntelligence()->GetTaskManager()->Flush(TASK_PRIORITY_PRIMARY);

			// removes temporary tasks caused by events like falling
			pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_EVENT_RESPONSE_TEMP);

			// remove jumping task
			CTask *jumpTask = pPedSelf->GetPedIntelligence()->GetTaskManager()->FindActiveTaskByType(211);
			if (jumpTask)
			{
				pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);
			}

			// more removals if needed ever
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_PHYSICAL_RESPONSE);
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_MAX);
			//pPedSelf->GetPedIntelligence()->GetTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);

			// set flags
			int flags = 0x10; // // Stops jaw fucking up, some speaking flag maybe   
			if(bLoop) flags |= 0x2; // flag that triggers the loop (Maccer)
			if(bUpdatePosition) 
			{
				// 0x40 enables position updating on Y-coord, 0x80 on X. (Maccer)
				flags |= 0x40; 
				flags |= 0x80;
			}
			if(!bFreezeLastFrame) flags |= 0x08; // flag determines whether to freeze player when anim ends. Really annoying (Maccer)

			// create a new task
			CTask *pTask = pGameInterface->GetTasks()->CreateTaskSimpleRunNamedAnim(
				szAnimName, pBlock->GetName(), flags, 4.0f, iTime, !bInterruptable, bRunInSequence, bOffsetPed, bHoldLastFrame);

			if(pTask)
			{
				pTask->SetAsPedTask(pPedSelf, TASK_PRIORITY_PRIMARY);
			}
		}
		else
		{
			// TODO: unload unreferenced blocks later on
			pGameInterface->GetStreaming()->RequestAnimations(pBlock->GetIndex(), 8);
		}
	}
}

void GTAfunc_DisembarkInstantly()
{
	CTaskManager *taskManager = pPedSelf->GetPedIntelligence()->GetTaskManager();
	for ( int i = 0 ; i < TASK_PRIORITY_MAX ; i++ )
	{
		CTask * pTask = taskManager->GetTask ( i );
		if ( pTask )
		{
			pTask->MakeAbortable ( pPedSelf, ABORT_PRIORITY_IMMEDIATE, NULL );
			taskManager->RemoveTask(i);
		}
	}
	for ( int i = 0 ; i < TASK_SECONDARY_MAX ; i++ )
	{
		CTask * pTask = taskManager->GetTaskSecondary ( i );
		if ( pTask )
		{
			pTask->MakeAbortable ( pPedSelf, ABORT_PRIORITY_IMMEDIATE, NULL );
			if (i != TASK_SECONDARY_FACIAL_COMPLEX)
				taskManager->RemoveTaskSecondary(i);
		}
	}

// the following causes crashes sometimes, usually related with flying and collisions
/*
	DWORD *actor = (DWORD *)pPedSelfSA;
	if(actor)
	{
		DWORD dwFunc = 0x601640;
		_asm
		{
			mov ecx, dword ptr [actor]
			add ecx, 1148
			mov ecx, dword ptr [ecx]
			call dwFunc
		}
	}
*/
}

void GTAfunc_ApplyRotoryPulseAboutAnAxis(float fX, float fY, float fZ)
{
	struct vehicle_info *vinfo = vehicle_info_get(VEHICLE_SELF, 0);
	if(vinfo)
	{
		DWORD dwFunc = 0x59C790;

		float fRotPtr[3];
		float *fpVehMatrix = vinfo->base.matrix;
		float *fpVehSpin = &vinfo->spin[0];
		float fFuncRet[3];

		fX *= 0.02000000f;
		fY *= 0.02000000f;
		fZ *= 0.02000000f;
		fRotPtr[0] = fX;
		fRotPtr[1] = fY;
		fRotPtr[2] = fZ;

		_asm
		{
			lea ecx, fRotPtr
			push ecx
			push fpVehMatrix
			lea edx, fFuncRet
			push edx
			call dwFunc
		}

		fpVehSpin[0] += fFuncRet[0];
		fpVehSpin[1] += fFuncRet[1];
		fpVehSpin[2] += fFuncRet[2];

		vect3_copy(fpVehSpin, fFuncRet);
	}
}

void GTAfunc_showStyledText( const char *text, int time, int style )
{
	( ( void ( __cdecl * ) ( uint32_t something ) ) ( 0x0069DCD0 ) ) ( 0 );
	( ( void ( __cdecl * ) ( const char *text, int time, int style ) ) ( 0x0069F2B0 ) ) ( text, time, style );
}

int GTAfunc_gtaKeyToVirtualKey(int key)
{
	if (key >= GTA_KEY_COMMA && key <= GTA_KEY_RBRACKET)
		return key;
	if (key >= GTA_KEY_F1 && key <= GTA_KEY_F12)
		return VK_F1 + key - GTA_KEY_F1;
	if (key >= GTA_KEY_NUMPAD1 && key <= GTA_KEY_NUMPAD9)
		return VK_NUMPAD1 + key - GTA_KEY_NUMPAD1;
	switch (key)
	{
	case GTA_KEY_MMOUSE: return VK_MBUTTON;
	case GTA_KEY_RMOUSE: return VK_RBUTTON;
	case GTA_KEY_MXB1: return VK_XBUTTON1;
	case GTA_KEY_MXB2: return VK_XBUTTON2;
	case GTA_KEY_INSERT: return VK_INSERT;
	case GTA_KEY_DELETE: return VK_DELETE;
	case GTA_KEY_HOME: return VK_HOME;
	case GTA_KEY_END: return VK_END;
	case GTA_KEY_PGUP: return VK_PRIOR;
	case GTA_KEY_PGDN: return VK_NEXT;
	case GTA_KEY_UP: return VK_UP;
	case GTA_KEY_DOWN: return VK_DOWN;
	case GTA_KEY_LEFT: return VK_LEFT;
	case GTA_KEY_RIGHT: return VK_RIGHT;
	case GTA_KEY_DIVIDE: return VK_DIVIDE;
	case GTA_KEY_MULTIPLY: return VK_MULTIPLY;
	case GTA_KEY_ADD: return VK_ADD;
	case GTA_KEY_SUBTRACT: return VK_SUBTRACT;
	case GTA_KEY_DECIMAL: return VK_DECIMAL;
	case GTA_KEY_NUMPAD0: return VK_NUMPAD0;
	case GTA_KEY_SCROLL: return VK_SCROLL;
	case GTA_KEY_PAUSE: return VK_PAUSE;
	case GTA_KEY_BACK: return VK_BACK;
	case GTA_KEY_TAB: return VK_TAB;
	case GTA_KEY_CAPSLOCK: return VK_CAPITAL;
	case GTA_KEY_RETURN: return VK_RETURN;
	case GTA_KEY_LSHIFT: return VK_LSHIFT;
	case GTA_KEY_RSHIFT: return VK_RSHIFT;
	case GTA_KEY_LCONTROL: return VK_LCONTROL;
	case GTA_KEY_RCONTROL: return VK_RCONTROL;
	case GTA_KEY_LMENU: return VK_LMENU;
	case GTA_KEY_RMENU: return VK_RMENU;
	case GTA_KEY_LWIN: return VK_LWIN;
	case GTA_KEY_RWIN: return VK_RWIN;
	case GTA_KEY_LMOUSE:
	case GTA_KEY_SPACE:
	case GTA_KEY_HASH:
	case GTA_KEY_APOSTROPHE:
	case GTA_KEY_GRAVE: return key;
	}
	return 0;
}