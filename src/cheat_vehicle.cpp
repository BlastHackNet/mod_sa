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

// new function to jump into vehicles without jacking (also for single player)
bool vehicleJumper ( int iVehicleID )
{
	// can't touch this
	if ( iVehicleID == VEHICLE_SELF )
		return false;

	// get vehicle_info
	struct vehicle_info *pVehicle = vehicle_info_get( iVehicleID, 0 );

	// check that the vehicle is legit
	if ( isBadPtr_GTA_pVehicle(pVehicle) )
		return false;

	traceLastFunc( "vehicleJumper()" );

	// if SAMP is loaded, check if the vehicle is streamed in
	if ( g_SAMP != NULL )
	{
		int iVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle( pVehicle );
		if ( isBadSAMPVehicleID(iVehicleSAMPID) )
			return false;
	}

	if ( pVehicle->hitpoints == 0.0f )
	{
		cheat_state_text( "Vehicle is destroyed" );
		return false;
	}

	if ( cheat_state->actor.air_brake )
	{
		cheat_state_text( "On foot airbrake must be disabled" );
		return false;
	}

	if ( cheat_state->actor.stick )
	{
		cheat_state_text( "On foot stick must be disabled" );
		return false;
	}

	if ( !pVehicle->base.bIsVisible )
	{
		cheat_state_text( "Vehicle is not visible." );
		return false;
	}

	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	if ( self != NULL && pVehicle->base.interior_id != self->base.interior_id )
	{
		cheat_state_text( "Vehicle is in another interior." );
		return false;
	}

	int iGTAVehicleID;
	iGTAVehicleID = ScriptCarId( pVehicle );

	if ( pVehicle->passengers[0] == self )
		return false;
	
	if ( !pVehicle->base.bUsesCollision )
		pVehicle->base.bUsesCollision = 1;
	
	// put into first available seat
	if ( pVehicle->passengers[0] == NULL )
	{
		GTAfunc_PutActorInCar(GetVehicleByGtaId(iGTAVehicleID));
		pGameInterface->GetCamera()->RestoreWithJumpCut();
		return true;
	}

	const int	seat_count = gta_vehicle_get_by_id( pVehicle->base.model_alt_id )->passengers;
	if ( seat_count > 0 )
	{
		for ( int seat = 1; seat <= seat_count; seat++ )
		{
			if ( pVehicle->passengers[seat] == NULL )
			{
				GTAfunc_PutActorInCarAsPassenger(GetVehicleByGtaId((iGTAVehicleID)), seat - 1);
				pGameInterface->GetCamera()->RestoreWithJumpCut();
				return true;
			}
		}
	}

	// no seats left, oh well
	cheat_state_text( "No seats left to teleport into." );
	return false;
}

void cheat_vehicle_teleport ( struct vehicle_info *info, const float pos[3], int interior_id, bool keepSpeed )
{
	if ( info == NULL )
		return;

	traceLastFunc( "cheat_vehicle_teleport()" );

	float				diff[3];
	float				new_pos[3];
	struct vehicle_info *temp;

	vect3_vect3_sub( pos, &info->base.matrix[4 * 3], diff );

	for ( temp = info; temp != NULL; temp = temp->trailer )
	{
		if(temp == NULL) return;

		vect3_vect3_add( &temp->base.matrix[4 * 3], diff, new_pos );

		vehicle_detachables_teleport( temp, &temp->base.matrix[4 * 3], new_pos );
		vect3_copy( new_pos, &temp->base.matrix[4 * 3] );

		if (!keepSpeed)
		{
			vect3_zero(temp->speed);
			vect3_zero(temp->spin);
		}

		gta_interior_id_set( interior_id );
		temp->base.interior_id = ( uint8_t ) interior_id;

		if ( !set.trailer_support )
			break;
	}
}

void cheat_handle_vehicle_unflip ( struct vehicle_info *info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_unflip()" );

	/* Unflip */
	//if ( KEY_PRESSED(set.key_unflip) )
	//{ }
	/* Rotate vehicle while the unflip key is held down */
	if ( KEYCOMBO_DOWN(set.key_unflip) )
	{
		traceLastFunc( "cheat_handle_vehicle_unflip()" );

		// inter-frame timing info from the game
		float		fTimeStep = *(float *)0xB7CB5C;

		// get our vehicle, gravity, and matrix
		CVehicle	*cveh = getSelfCVehicle();
		CVector		cvehGrav;
		CMatrix		cvehMatrix;
		cveh->GetGravity( &cvehGrav );
		cveh->GetMatrix( &cvehMatrix );

		// get "down" from vehicle model
		CVector rotationAxis = cheat_vehicle_getPositionUnder( cveh );

		// normalize our vectors
		cvehGrav.Normalize();
		rotationAxis.Normalize();

		// axis and rotation for gravity
		float	theta = acos( rotationAxis.DotProduct(&cvehGrav) );
		if ( !near_zero(theta) )
		{
			rotationAxis.CrossProduct( &cvehGrav );
			rotationAxis.Normalize();
			rotationAxis.ZeroNearZero();
			cvehMatrix = cvehMatrix.Rotate( &rotationAxis, -theta );
		}

		// slow turn to the right
		theta = M_PI / ( 75.0f / fTimeStep );

		CVector slowTurnAxis = cvehMatrix.vUp;
		slowTurnAxis.Normalize();
		slowTurnAxis.ZeroNearZero();
		cvehMatrix = cvehMatrix.Rotate( &cvehMatrix.vUp, theta );

		// set the new matrix
		cveh->SetMatrix( &cvehMatrix );

		// no more spin cycle for you
		CVector vZero ( 0.0f, 0.0f, 0.0f );
		cveh->SetTurnSpeed( &vZero );
	}
}

void cheat_vehicle_air_brake_set ( int enabled )
{
	cheat_state->vehicle.air_brake = enabled;
	cheat_handle_vehicle_air_brake( NULL, 0.0f );
}

void cheat_handle_vehicle_air_brake ( struct vehicle_info *info, double time_diff )
{
	static float		orig_matrix[16];
	static int			orig_matrix_set;
	struct vehicle_info *temp;

	if ( info == NULL )
	{
		orig_matrix_set = 0;
		return;
	}

	traceLastFunc( "cheat_handle_vehicle_air_brake()" );

	// handle key presses
	if ( set.air_brake_toggle )
	{
		if ( KEYCOMBO_PRESSED(set.key_air_brake_mod) )
			cheat_state->vehicle.air_brake ^= 1;

		if ( KEYCOMBO_PRESSED(set.key_air_brake_mod2) && cheat_state->vehicle.air_brake )
			cheat_state->vehicle.air_brake_slowmo ^= 1;
	}
	else
	{
		if ( KEYCOMBO_PRESSED(set.key_air_brake_mod) )
			cheat_state->vehicle.air_brake = 1;
		else if ( KEYCOMBO_RELEASED(set.key_air_brake_mod) )
			cheat_state->vehicle.air_brake = 0;

		if ( KEYCOMBO_PRESSED(set.key_air_brake_mod2) && cheat_state->vehicle.air_brake )
			cheat_state->vehicle.air_brake_slowmo = 1;
		else if ( KEYCOMBO_RELEASED(set.key_air_brake_mod2) && cheat_state->vehicle.air_brake )
			cheat_state->vehicle.air_brake_slowmo = 0;
	}

	// do airbrake
	if ( !cheat_state->vehicle.air_brake )
	{
		orig_matrix_set = 0;
		cheat_state->vehicle.air_brake_slowmo = 0;
	}
	else
	{
		if ( !orig_matrix_set )
		{
			matrix_copy( info->base.matrix, orig_matrix );
			orig_matrix_set = 1;
		}

		if ( !KEYCOMBO_DOWN(set.key_unflip) )	/* allow the unflip rotation feature to work */
			matrix_copy( orig_matrix, info->base.matrix );

		/* XXX allow some movement */
		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			/* prevent all kinds of movement */
			vect3_zero( temp->speed );
			vect3_zero( temp->spin );

			if ( !set.trailer_support )
				break;
		}

		static uint32_t time_start;
		float			*matrix = info->base.matrix;
		float			d[4] = { 0.0f, 0.0f, 0.0f, (float) time_diff * set.air_brake_speed };
		float			xyvect[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; /* rotation vector */
		float			zvect[4] = { 0.0f, 0.0f, 0.0f, 0.0f };	/* rotation vector */
		float			theta = set.air_brake_rot_speed * (float) time_diff * M_PI * 2.0f;

		if ( cheat_state->vehicle.air_brake_slowmo )
		{
			d[3] /= 10.0f;
			theta /= 2.0f;
		}

		if ( KEYCOMBO_DOWN(set.key_air_brake_forward) )
			d[0] += 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_backward) )
			d[0] -= 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_left) )
			d[1] += 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_right) )
			d[1] -= 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_up) )
			d[2] += 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_down) )
			d[2] -= 1.0f;

		if ( !near_zero(set.air_brake_accel_time) )
		{
			if ( !vect3_near_zero(d) )
				time_start = ( time_start == 0 ) ? time_get() : time_start;
			else
				time_start = 0; /* no keys pressed */

			/* acceleration */
			if ( time_start != 0 )
			{
				float	t = TIME_TO_FLOAT( time_get() - time_start );
				if ( t < set.air_brake_accel_time )
					d[3] *= t / set.air_brake_accel_time;
			}
		}

		/* pitch (x-axis) */
		if ( KEYCOMBO_DOWN(set.key_air_brake_rot_pitch1) )
			xyvect[0] += 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_rot_pitch2) )
			xyvect[0] -= 1.0f;

		/* roll (y-axis) */
		if ( KEYCOMBO_DOWN(set.key_air_brake_rot_roll1) )
			xyvect[1] += 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_rot_roll2) )
			xyvect[1] -= 1.0f;

		/* yaw (z-axis) */
		if ( KEYCOMBO_DOWN(set.key_air_brake_rot_yaw1) )
			zvect[2] -= 1.0f;
		if ( KEYCOMBO_DOWN(set.key_air_brake_rot_yaw2) )
			zvect[2] += 1.0f;

		if ( !vect3_near_zero(xyvect) )
		{
			vect3_normalize( xyvect, xyvect );

			matrix_vect4_mult( matrix, xyvect, xyvect );
			matrix_vect3_rotate( matrix, xyvect, theta, matrix );
		}

		if ( !vect3_near_zero(zvect) )
		{
			vect3_normalize( zvect, zvect );

			matrix_vect3_rotate( matrix, zvect, theta, matrix );
		}

		switch ( set.air_brake_behaviour )
		{
		case 0:
			matrix[4 * 1 + 0] += d[0] * d[3];
			matrix[4 * 1 + 1] += d[1] * d[3];
			matrix[4 * 1 + 2] += d[2] * d[3];
			break;

		case 1: /* mixed 2d/3d mode */
			{
				/* convert the vehicle's 3d rotation vector to a 2d angle */
				float	a = atan2f( matrix[4 * 1 + 0], matrix[4 * 1 + 1] );

				/* calculate new position */
				matrix[4 * 3 + 0] += ( d[0] * sinf(a) - d[1] * cosf(a) ) * d[3];
				matrix[4 * 3 + 1] += ( d[0] * cosf(a) + d[1] * sinf(a) ) * d[3];
				matrix[4 * 3 + 2] += d[2] * d[3];
			}
			break;

		case 2: /* full 3d movement */
			if ( !vect3_near_zero(d) )
			{
				float	vect[4] = { -d[1], d[0], d[2], 0.0f };	/* swap x & y + invert y */
				float	out[4];

				/* out = matrix * norm(d) */
				vect3_normalize( vect, vect );
				matrix_vect4_mult( matrix, vect, out );

				matrix[4 * 3 + 0] += out[0] * d[3];
				matrix[4 * 3 + 1] += out[1] * d[3];
				matrix[4 * 3 + 2] += out[2] * d[3];
			}
			break;
		}

		matrix_copy( matrix, orig_matrix );

		// heh
		int		gonadsMult = 1000;
		float	strifeMult = 0.000001f;
		int		gonads = rand() % gonadsMult;
		float	strife = (double)gonads * strifeMult;
		if ( strife < strifeMult * gonadsMult / 2 )
			strife -= strifeMult * gonadsMult;
		info->m_SpeedVec.fX = strife;
		gonads = rand() % gonadsMult;
		strife = (double)gonads * strifeMult;
		if ( strife < strifeMult * gonadsMult / 2 )
			strife -= strifeMult * gonadsMult;
		info->m_SpeedVec.fY = strife;
		strifeMult = 0.000000001f;
		gonads = rand() % gonadsMult;
		strife = (double)gonads * strifeMult;
		if ( strife < strifeMult * gonadsMult / 2 )
			strife -= strifeMult * gonadsMult;
		info->m_SpeedVec.fZ = strife;
	}
}

/*
Causing loading screen way too regulary.

void cheat_handle_vehicle_slowTeleport ( struct vehicle_info *vehicle_info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_slowTeleport()" );

	if ( vehicle_info == NULL )
		return;

	if ( !set.teleport_slow || !cheat_state->vehicle.tele_on
		|| KEY_PRESSED(set.key_slowTeleport_stop) )
	{
		cheat_state->vehicle.tele_on = 0;
		return;
	}

	// inveh cross-map-teleport-alike-flying
	if ( set.teleport_slow && cheat_state->vehicle.tele_on &&
		cheat_state->state == CHEAT_STATE_VEHICLE && vehicle_info != NULL )
	{
		if ( vect3_dist(cheat_state->vehicle.tele_coords, 
			&vehicle_info->base.matrix[4*3]) < 5.0 )
		{
			cheat_state->vehicle.tele_on = 0;
			vect3_zero( cheat_state->vehicle.tele_coords );
		}

		CVehicle	*cveh = pPools->GetVehicle( (DWORD *)vehicle_info );
		CMatrix		cvehMatrix;
		cveh->GetMatrix( &cvehMatrix );

		CVector *veh_vect = cveh->GetPosition();
		CVector LocationVect;
		CVector vectToLocation;
		LocationVect.fX = cheat_state->vehicle.tele_coords[0];
		LocationVect.fY = cheat_state->vehicle.tele_coords[1];
		LocationVect.fZ = cheat_state->vehicle.tele_coords[2];
		vectToLocation = *veh_vect - LocationVect;

		// direction
		CVector up = cvehMatrix.vUp;
		up.CrossProduct( &vectToLocation );
		up.Normalize();

		CVector down = up;
		down.CrossProduct( &cvehMatrix.vUp );
		down.Normalize();

		CVector moredown = down;
		moredown.CrossProduct( &up );
		cvehMatrix.vRight = up;
		cvehMatrix.vUp = moredown;
		cvehMatrix.vFront = -down;
		cveh->SetMatrix( &cvehMatrix );
			
		// height
		CVector front = cvehMatrix.vFront;
		front.CrossProduct( &vectToLocation );
		front.Normalize();

		CVector back = front;
		back.CrossProduct( &cvehMatrix.vFront );
		back.Normalize();
		CVector moreback = back;
		moreback.CrossProduct( &front );
		moreback.Normalize();
		cvehMatrix.vRight = -back;
		cvehMatrix.vUp = front;
		cvehMatrix.vFront = moreback;
		cveh->SetMatrix( &cvehMatrix );

		// set speed into direction car is facing
		float	dir[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
		float	vect[4];
		matrix_vect4_mult( vehicle_info->base.matrix, dir, vect );
		if ( !vect3_near_zero(vect) && !vect3_near_zero(vehicle_info->speed) )
		{
			float	speed = vect3_length( vehicle_info->speed );
			vect3_mult( vect, speed, vehicle_info->speed );
		}
		//set speed end
	}
}
*/

void cheat_handle_vehicle_warp ( struct vehicle_info *info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_warp()" );

	static struct vehicle_state state;
	static float				raildist;
	static uint32_t				warp_time = 0;
	static int					warping = 0;

	if ( warp_time != 0 )
	{
		if ( time_get() - warp_time > MSEC_TO_TIME(100) )
		{
			warp_time = 0;
		}
		else
		{
			vehicle_state_restore( info, &state );
			if ( info->vehicle_type == VEHICLE_TYPE_TRAIN )
				info->m_fTrainRailDistance = raildist;
		}
	}

	/* warp factor: fuck you */
	if ( KEYCOMBO_PRESSED(set.key_warp_mod) )
	{
		struct vehicle_info *temp;
		float				dir[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
		float				vect[4];

		if ( set.warp_use_speed && !vect3_near_zero(info->speed) && vect3_length(info->speed) >= 0.01f )
		{
			/* use normalized speed vector */
			vect3_copy( info->speed, dir );
			vect3_normalize( dir, vect );
		}
		else
		{
			/* use vehicle direction matrix */
			matrix_vect4_mult( info->base.matrix, dir, vect );
			if ( vect3_near_zero(vect) )
				return; /* shouldn't happen */
		}

		vehicle_state_store( info, &state );
		if ( info->vehicle_type == VEHICLE_TYPE_TRAIN )
			raildist = info->m_fTrainRailDistance;
		warp_time = 0;
		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			vect3_mult( vect, set.warp_speed, temp->speed );

			if ( !set.trailer_support )
				break;
		}
	}

	if ( KEYCOMBO_DOWN(set.key_warp_mod) && info->vehicle_type == VEHICLE_TYPE_TRAIN )
		info->m_fTrainSpeed = set.warp_speed;

	if ( KEYCOMBO_RELEASED(set.key_warp_mod) )
	{
		struct vehicle_info *temp;

		warp_time = time_get();
		vehicle_state_restore( info, &state );
		if ( info->vehicle_type == VEHICLE_TYPE_TRAIN )
			info->m_fTrainRailDistance = raildist;
		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			temp->collision_something = 0.0f;

			if ( !set.trailer_support )
				break;
		}
	}
}

void cheat_handle_vehicle_hop ( struct vehicle_info *info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_hop()" );

	if ( KEYCOMBO_DOWN(set.key_vehicle_hop) )
	{
		CVehicle	*cveh = pGameInterface->GetPools()->GetVehicle( (DWORD *)info );
		CVector		vecSpeedAdd, vecMoveSpeed;
		float		theDotProduct;
		bool		isBigHop = false;
		bool		isHopThisFrame = false;
		cveh->GetGravity( &vecSpeedAdd );
		vecSpeedAdd = -vecSpeedAdd;

		cveh->GetMoveSpeed( &vecMoveSpeed );
		theDotProduct = vecMoveSpeed.DotProduct( &vecSpeedAdd );
		if ( theDotProduct < set.vehicle_hop_speed / 2.0f )
			isHopThisFrame = true;
		if ( theDotProduct < -0.1f )
			isBigHop = true;

		for ( ; cveh != NULL; cveh = cveh->GetTowedVehicle() )
		{
			cveh->GetMoveSpeed( &vecMoveSpeed );
			if ( isHopThisFrame )
			{
				if ( isBigHop )
					vecMoveSpeed += ( vecSpeedAdd * (set.vehicle_hop_speed * 2.0f) );
				else
					vecMoveSpeed += ( vecSpeedAdd * (set.vehicle_hop_speed / 2.0f) );
				cveh->SetMoveSpeed( &vecMoveSpeed );
			}

			//set.vehicle_hop_speed;
			if ( !set.trailer_support )
				break;
		}
	}
}

void cheat_handle_vehicle_brake ( struct vehicle_info *info, double time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_brake()" );

	float				speed;
	struct vehicle_info *temp;

	if ( KEYCOMBO_DOWN(set.key_brake_mod) && !cheat_state->vehicle.air_brake )
	{
		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			speed = vect3_length( temp->speed );
			vect3_normalize( temp->speed, temp->speed );
			speed -= time_diff * set.brake_mult / 1.3f;

			if ( speed < 0.0f )
				speed = 0.0f;

			if ( vect3_near_zero(temp->speed) )
			{
				vect3_zero( temp->speed );
			}
			else
			{
				if ( temp->vehicle_type == VEHICLE_TYPE_TRAIN )
				{
					if ( temp->m_fTrainSpeed <= 0.05f && temp->m_fTrainSpeed >= -0.05f )
						temp->m_fTrainSpeed = 0.0f;
					else if ( temp->m_fTrainSpeed < 0.0f )
						temp->m_fTrainSpeed += time_diff * set.brake_mult;
					else
						temp->m_fTrainSpeed -= time_diff * set.brake_mult;
				}

				vect3_mult( temp->speed, speed, temp->speed );

				// heh
				int		gonadsMult = 1000;
				float	strifeMult = 0.0000001f;
				int		gonads = rand() % gonadsMult;
				float	strife = (double)gonads * strifeMult;
				if ( strife < strifeMult * gonadsMult / 2 )
					strife -= strifeMult * gonadsMult;
				info->m_SpeedVec.fX += strife;
				gonads = rand() % gonadsMult;
				strife = (double)gonads * strifeMult;
				if ( strife < strifeMult * gonadsMult / 2 )
					strife -= strifeMult * gonadsMult;
				info->m_SpeedVec.fY += strife;
			}

			if ( !set.trailer_support )
				break;
		}
	}
}

void cheat_handle_vehicle_nitro ( struct vehicle_info *info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_nitro()" );

	static uint32_t		timer;
	static int			decelerating;
	static float		speed_off;
	float				pre_speed[3];
	struct vehicle_info *temp;

	if ( KEYCOMBO_DOWN(set.key_warp_mod) )
		vect3_copy( info->speed, pre_speed );

	if ( KEYCOMBO_PRESSED(set.key_nitro_mod) )
	{
		speed_off = vect3_length( info->speed );
		decelerating = 0;
		timer = time_get();
	}

	/* "nitro" acceleration mod */
	if ( KEYCOMBO_DOWN(set.key_nitro_mod) && !vect3_near_zero(info->speed) )
	{
		float	etime = TIME_TO_FLOAT( time_get() - timer ) / set.nitro_accel_time;
		float	speed = set.nitro_high;

		if ( !near_zero(set.nitro_accel_time) )
		{
			etime += 1.0f - ( set.nitro_high - speed_off ) / set.nitro_high;

			if ( etime < 1.0f )
				speed *= etime;
		}

		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			if ( !vect3_near_zero(temp->speed) )
			{
				if ( temp->vehicle_type == VEHICLE_TYPE_TRAIN )
				{
					if ( temp->m_fTrainSpeed < 0.0f && temp->m_fTrainSpeed > -set.nitro_high )
						temp->m_fTrainSpeed -= speed;
					else if ( temp->m_fTrainSpeed < set.nitro_high )
						temp->m_fTrainSpeed += speed;
				}

				vect3_normalize( temp->speed, temp->speed );
				vect3_mult( temp->speed, speed, temp->speed );
				if ( vect3_near_zero(temp->speed) )
					vect3_zero( temp->speed );
			}

			if ( !set.trailer_support )
				break;
		}

		// heh
		int		gonadsMult = 1000;
		float	strifeMult = 0.0000001f;
		int		gonads = rand() % gonadsMult;
		float	strife = (double)gonads * strifeMult;
		if ( strife < strifeMult * gonadsMult / 2 )
			strife -= strifeMult * gonadsMult;
		info->m_SpeedVec.fX += strife;
		gonads = rand() % gonadsMult;
		strife = (double)gonads * strifeMult;
		if ( strife < strifeMult * gonadsMult / 2 )
			strife -= strifeMult * gonadsMult;
		info->m_SpeedVec.fY += strife;
	}

	if ( KEYCOMBO_RELEASED(set.key_nitro_mod) )
	{
		if ( vect3_length(info->speed) > set.nitro_low )
		{
			speed_off = vect3_length( info->speed );
			decelerating = 1;
			timer = time_get();
		}
	}

	if ( decelerating )
	{
		float	speed = set.nitro_low;
		float	etime = TIME_TO_FLOAT( time_get() - timer );

		if ( etime < set.nitro_decel_time )
			speed = speed_off - ( speed_off - speed ) * ( etime / set.nitro_decel_time );
		else
			decelerating = 0;

		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			if ( vect3_length(temp->speed) > speed )
			{
				vect3_normalize( temp->speed, temp->speed );
				vect3_mult( temp->speed, speed, temp->speed );
			}

			/* // first fix trains before uncommenting this..
			if ( temp->vehicle_type == VEHICLE_TYPE_TRAIN )
			{
				if ( temp->m_fTrainSpeed > speed )
					temp->m_fTrainSpeed = vect3_length( temp->speed );
				else if ( temp->m_fTrainSpeed < -speed )
					temp->m_fTrainSpeed = -vect3_length( temp->speed );
			}
			*/
			if ( !set.trailer_support )
				break;
		}
	}

	/* actual NOS of the game, toggle infinite NOS, w00t! */
	if ( KEYCOMBO_PRESSED(set.key_nitro) )
	{
		if ( !cheat_state->vehicle.infNOS_toggle_on )
		{
			cheat_state->vehicle.infNOS_toggle_on = true;
			patcher_install( &patch_vehicle_inf_NOS );
			vehicle_addUpgrade( info, 1010 );
		}
		else
		{
			cheat_state->vehicle.infNOS_toggle_on = false;
			patcher_remove( &patch_vehicle_inf_NOS );
			GTAfunc_removeVehicleUpgrade( info, 1010 );
		}
	}
}

//MATRIX4X4
//	VECTOR right			
//		float X [4*0+0]
//		float Y [4*0+1]
//		float Z [4*0+2]		Roll
// DWORD  flags;
// VECTOR up;
//		float X [4*1+0]
//		float Y [4*1+1]
//		float Z [4*1+2]		Pitch
// float  pad_u;
// VECTOR at;				Front
//		float X [4*2+0]
//		float Y [4*2+1]
//		float Z [4*2+2]		Yaw

//
void cheat_handle_vehicle_quick_turn ( struct vehicle_info *info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_quick_turn()" );

	if ( KEYCOMBO_PRESSED(set.key_quick_turn_180) )
	{
		/* simply invert the X and Y axis.. */
		for ( struct vehicle_info * temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			vect3_invert( &temp->base.matrix[4 * 0], &temp->base.matrix[4 * 0] );
			vect3_invert( &temp->base.matrix[4 * 1], &temp->base.matrix[4 * 1] );
			vect3_invert( temp->speed, temp->speed );
			if ( !cheat_state->vehicle.keep_trailer_attached || !set.trailer_support )
				break;
		}

		if ( info->vehicle_type == VEHICLE_TYPE_TRAIN )
		{
			for ( struct vehicle_info * temp = info; temp != NULL; temp = temp->m_train_next_carriage )
			{
				if(temp == NULL) return;

				if ( !g_SAMP )
				{
					temp->m_trainFlags.bDirection ^= 1;
					if ( info->m_train_next_carriage == temp && info->base.model_alt_id == 538 )
					{	//avoid brown streak bug
						if ( temp->m_fDistanceToNextCarriage == 16.5f )
							temp->m_fDistanceToNextCarriage = 20.8718f;
						else
							temp->m_fDistanceToNextCarriage = -16.5f;
					}

					temp->m_fDistanceToNextCarriage *= -1;
				}

				temp->m_fTrainSpeed = -info->m_fTrainSpeed;
			}
		}
	}

	if ( KEYCOMBO_PRESSED(set.key_quick_turn_left) )
	{
		struct vehicle_info *temp;
		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			// do new heading
			float		*heading_matrix = temp->base.matrix;
			MATRIX4X4	*heading_matrix4x4 = temp->base.matrixStruct;

			// rotate on z axis
			CVehicle	*cveh = pGameInterface->GetPools()->GetVehicle( (DWORD *)temp );
			CVector		posUnder = cheat_vehicle_getPositionUnder( cveh );
			float		heading_vector_zrotate[3] = { posUnder.fX, posUnder.fY, posUnder.fZ };
			float		heading_theta = M_PI / 2.0f;
			vect3_normalize( heading_vector_zrotate, heading_vector_zrotate );
			matrix_vect3_rotate( heading_matrix, heading_vector_zrotate, heading_theta, heading_matrix );

			// do new speed
			if ( !temp->m_SpeedVec.IsNearZero() )
			{
				temp->m_SpeedVec.CrossProduct( &posUnder );
			}

			if ( !cheat_state->vehicle.keep_trailer_attached || !set.trailer_support )
				break;
		}
	}

	if ( KEYCOMBO_PRESSED(set.key_quick_turn_right) )
	{
		struct vehicle_info *temp;
		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			// do new heading
			float		*heading_matrix = temp->base.matrix;
			MATRIX4X4	*heading_matrix4x4 = temp->base.matrixStruct;

			// rotate on z axis
			CVehicle	*cveh = pGameInterface->GetPools()->GetVehicle( (DWORD *)temp );
			CVector		posUnder = cheat_vehicle_getPositionUnder( cveh );
			posUnder = -posUnder;

			float	heading_zvectrotate[4] = { posUnder.fX, posUnder.fY, posUnder.fZ };
			float	heading_theta = M_PI / 2.0f;
			vect3_normalize( heading_zvectrotate, heading_zvectrotate );
			matrix_vect3_rotate( heading_matrix, heading_zvectrotate, heading_theta, heading_matrix );

			// do new speed
			if ( !temp->m_SpeedVec.IsNearZero() )
			{
				temp->m_SpeedVec.CrossProduct( &posUnder );
			}

			if ( !cheat_state->vehicle.keep_trailer_attached || !set.trailer_support )
				break;
		}
	}
}

void cheat_handle_vehicle_protection ( struct vehicle_info *info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_protection()" );

	static float		last_spin[3];
	struct vehicle_info *temp;

	if ( KEYCOMBO_PRESSED(set.key_protection) )
		cheat_state->vehicle.protection ^= 1;

	if ( KEYCOMBO_DOWN(set.key_warp_mod) )
		return;

	if ( cheat_state->vehicle.protection )
	{
		for ( temp = info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			if ( !vect3_near_zero(temp->spin) && vect3_length(temp->spin) > set.protection_spin_cap )
			{
				vect3_normalize( temp->spin, temp->spin );
				vect3_mult( temp->spin, set.protection_spin_cap, temp->spin );
			}

			if ( !vect3_near_zero(temp->speed) && vect3_length(temp->speed) > set.protection_speed_cap )
			{
				vect3_normalize( temp->speed, temp->speed );
				vect3_mult( temp->speed, set.protection_speed_cap, temp->speed );
			}

			if ( temp->base.matrix[4 * 2 + 2] < 0.0f )
			{
				if ( !vect3_near_zero(last_spin) && !vect3_near_zero(temp->spin) && vect3_length(temp->spin) < 0.10f )
				{
					vect3_normalize( temp->spin, temp->spin );
					vect3_mult( temp->spin, 0.10f, temp->spin );
				}
			}
			else if ( temp == info )	/* only copy the first vehicle's spin info */
			{
				vect3_copy( temp->spin, last_spin );
			}

			vehicle_prevent_below_height( temp, set.protection_min_height );

			if ( !set.trailer_support )
				break;
		}
	}
}

void cheat_handle_vehicle_engine ( struct vehicle_info *vehicle_info, float time_diff )
{
	if ( vehicle_info == NULL )
		return;

	traceLastFunc( "cheat_handle_vehicle_engine()" );

	struct vehicle_info *veh_self = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( veh_self == NULL )
		return;

	if ( KEYCOMBO_PRESSED(set.key_engine) )
	{
		if ( veh_self->m_nVehicleFlags.bEngineOn )
		{
			veh_self->m_nVehicleFlags.bEngineOn = 0;
			cheat_state->vehicle.is_engine_on = 0;
		}
		else
		{
			veh_self->m_nVehicleFlags.bEngineOn = 1;
			cheat_state->vehicle.is_engine_on = 1;
		}
	}
}

void cheat_handle_vehicle_brakedance ( struct vehicle_info *vehicle_info, float time_diff )
{
	if ( cheat_state->vehicle.air_brake )
		return;
	if ( cheat_state->vehicle.stick )
		return;

	traceLastFunc( "cheat_handle_vehicle_brakedance()" );

	static float	velpos, velneg;

	if ( KEYCOMBO_PRESSED(set.key_brkd_toggle) )
	{
		cheat_state->vehicle.brkdance ^= 1;
	}

	if ( cheat_state->vehicle.brkdance )
	{
		// we should probably actually be driving the vehicle
		struct actor_info	*actor = actor_info_get( ACTOR_SELF, 0 );
		if ( actor == NULL )
			return; // we're not an actor? lulz
		if ( actor->state != ACTOR_STATE_DRIVING )
			return; // we're not driving?
		if ( actor->vehicle->passengers[1] == actor )
			return; // we're not passenger in an airplane?
		int		iVehicleID = ScriptCarId( vehicle_info );

		float	fTimeStep = *(float *)0xB7CB5C;

		velpos = set.brkdance_velocity * fTimeStep;
		velneg = -set.brkdance_velocity * fTimeStep;

		if ( KEYCOMBO_DOWN(set.key_brkd_forward) )
		{
			GTAfunc_ApplyRotoryPulseAboutAnAxis(velneg, 0.0f, 0.0f);
		}
		else if ( KEYCOMBO_DOWN(set.key_brkd_backward) )
		{
			GTAfunc_ApplyRotoryPulseAboutAnAxis(velpos, 0.0f, 0.0f);
		}
		else if ( KEYCOMBO_DOWN(set.key_brkd_right) )
		{
			GTAfunc_ApplyRotoryPulseAboutAnAxis(0.0f, velpos, 0.0f);
		}
		else if ( KEYCOMBO_DOWN(set.key_brkd_left) )
		{
			GTAfunc_ApplyRotoryPulseAboutAnAxis(0.0f, velneg, 0.0f);
		}
		else if ( KEYCOMBO_DOWN(set.key_brkd_rightward) )
		{
			GTAfunc_ApplyRotoryPulseAboutAnAxis(0.0f, 0.0f, velneg);
		}
		else if ( KEYCOMBO_DOWN(set.key_brkd_leftward) )
		{
			GTAfunc_ApplyRotoryPulseAboutAnAxis(0.0f, 0.0f, velpos);
		}
		else
			iVehicleID = -1;

		if ( set.trailer_support && iVehicleID != -1 )
		{
			for ( struct vehicle_info * temp = vehicle_info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;
					
				vect3_copy( vehicle_info->spin, temp->spin );
			}
		}
	}
}

void cheat_handle_vehicle_blinking_carlights ( struct vehicle_info *vinfo, float time_diff )
{
	traceLastFunc( "cheat_handle_blinking_carlights()" );

	int class_id = gta_vehicle_get_by_id( vinfo->base.model_alt_id )->class_id;
	if ( vinfo->vehicle_type != VEHICLE_TYPE_CAR
	 ||	 class_id == VEHICLE_CLASS_TRAILER
	 ||	 class_id == VEHICLE_CLASS_AIRPLANE
	 ||	 class_id == VEHICLE_CLASS_HELI
	 ||	 class_id == VEHICLE_CLASS_BIKE ) return;

	if ( KEYCOMBO_PRESSED(set.key_blinking_car_lights) )
	{
		// reset lights damage
		vinfo->lights_status_rear = false;
		vinfo->lights_status_frontLeft = false;
		vinfo->lights_status_frontRight = false;

		// increment lights state
		cheat_state->vehicle.blinking_carlights_state++;

		// set it back down to zero if over the max
		if ( cheat_state->vehicle.blinking_carlights_state > 3 )
			cheat_state->vehicle.blinking_carlights_state = 0;

		// reset turn state
		cheat_state->vehicle.blinking_carlights_turnstate = 0;
	}

	// return if lights state is 0/off
	if ( !cheat_state->vehicle.blinking_carlights_state )
		return;

	// return if we arn't driving the vehicle
	struct actor_info	*actor_self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( vinfo->passengers[0] != actor_self )
		return;

	// enables car lights any time of day, not synced
	if ( set.enable_car_lights_at_day_time )
		vinfo->OverrideLights = 2;

	// switch is faster than multiple if/else statements
	switch ( cheat_state->vehicle.blinking_carlights_state )
	{
	case 1:
		// turn lights
		// blink rate limiter
		if ( (GetTickCount() - 250) < cheat_state->vehicle.blinking_carlights_lastblink )
			return;
		if ( cheat_state->vehicle.blinking_carlights_turnstate == 0 )
		{
			if ( vinfo->steer_angles[0] <= -0.01f )
			{
				vinfo->lights_status_frontLeft = false;
				vinfo->lights_status_frontRight = true;
			}
			else if ( vinfo->steer_angles[0] >= 0.01f )
			{
				vinfo->lights_status_frontLeft = true;
				vinfo->lights_status_frontRight = false;
			}

			cheat_state->vehicle.blinking_carlights_turnstate = 1;
		}
		else
		{
			vinfo->lights_status_frontLeft = false;
			vinfo->lights_status_frontRight = false;
			cheat_state->vehicle.blinking_carlights_turnstate = 0;
		}
		break;

	case 2:
		// police style lights
		// blink rate limiter
		if ( (GetTickCount() - 150) < cheat_state->vehicle.blinking_carlights_lastblink )
			return;

		// rear lights
		if ( vinfo->lights_status_rear )
			vinfo->lights_status_rear = false;
		else
			vinfo->lights_status_rear = true;

		// front lights
		switch ( cheat_state->vehicle.blinking_carlights_turnstate )
		{
		case 0:
			vinfo->lights_status_frontLeft = true;
			vinfo->lights_status_frontRight = false;
			break;

		case 1:
			vinfo->lights_status_frontLeft = false;
			vinfo->lights_status_frontRight = true;
			break;

		case 2:
			vinfo->lights_status_frontLeft = true;
			vinfo->lights_status_frontRight = true;
			break;

		case 3:
			vinfo->lights_status_frontLeft = false;
			vinfo->lights_status_frontRight = true;
			break;

		case 4:
			vinfo->lights_status_frontLeft = true;
			vinfo->lights_status_frontRight = false;
			break;

		case 5:
			vinfo->lights_status_frontLeft = true;
			vinfo->lights_status_frontRight = true;
			break;
		}

		// increment/reset turnstate
		cheat_state->vehicle.blinking_carlights_turnstate++;
		if ( cheat_state->vehicle.blinking_carlights_turnstate > 5 )
			cheat_state->vehicle.blinking_carlights_turnstate = 0;
		break;

	case 3:
		// stroboscope
		// blink rate limiter
		if ( (GetTickCount() - 25) < cheat_state->vehicle.blinking_carlights_lastblink )
			return;

		// rear lights
		if ( vinfo->lights_status_rear )
		{
			vinfo->lights_status_rear = false;
			vinfo->lights_status_frontLeft = true;
			vinfo->lights_status_frontRight = true;
		}
		else
		{
			vinfo->lights_status_rear = true;
			vinfo->lights_status_frontLeft = false;
			vinfo->lights_status_frontRight = false;
		}
		break;
	}

	// reset counter
	cheat_state->vehicle.blinking_carlights_lastblink = GetTickCount();
}

void cheat_handle_vehicle_fly ( struct vehicle_info *vehicle_info, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_fly()" );
	static bool orig_cheat = false;
	static bool checked_for_orig_cheat = false;

	// Disable this function, if "Vehicles can fly"-patch is listed in GTA Patches.
	// Not disabling this function may result in a conflict with the original built in cheat.
	if ( (!checked_for_orig_cheat && GTAPatchIDFinder( 0x00969160 ) != -1) || orig_cheat )
	{
		if ( !checked_for_orig_cheat )
		{
			// user wants to use the original GTA cheat
			// lets not screw this up for them by changing stuff (no-fly patch)
			checked_for_orig_cheat = true;
			orig_cheat = true;
			set.hud_indicator_inveh_fly = false;
			//Log( "Found gta patch \"Vehicles can fly\". Deactivating \"key_fly_vehicle\" and relating mod_sa functions." );
		}		
		return;
	}
	else
	{
		checked_for_orig_cheat = true;
	}

	static bool					needRestorePphys = false;
	static float				plane_orig_data[3];			// pitch, roll, circle
	static struct vehicle_info	*last_plane;

	// getting passed a NULL pointer from cheat_panic, so we can remove the patch and reapply airplane physics
	if ( vehicle_info == NULL )
	{
		if ( !cheat_state->_generic.cheat_panic_enabled )
			return;

		if ( patch_NotAPlane.installed )
			patcher_remove( &patch_NotAPlane );

		struct vehicle_info *veh_self = vehicle_info_get( VEHICLE_SELF, NULL );

		if ( veh_self == NULL )
			return;

		if ( needRestorePphys && last_plane == veh_self )
		{
			veh_self->pFlyData->pitch = plane_orig_data[0];
			veh_self->pFlyData->roll_lr = plane_orig_data[1];
			veh_self->pFlyData->circleAround = plane_orig_data[2];
			needRestorePphys = false;
		}

		return;
	}

	// this should never happen
	if ( pGameInterface == NULL )
		return;

	if ( KEYCOMBO_PRESSED(set.key_fly_vehicle_modeChange) )
		set.fly_vehicle_heliMode = !set.fly_vehicle_heliMode;

	if ( KEYCOMBO_PRESSED(set.key_fly_vehicle) )
		cheat_state->vehicle.fly ^= 1;

	// ignore hydra, RC Baron and RC Goblin (they seem to use some special functions to fly)
	if ( vehicle_info->base.model_alt_id == 520
	 ||	 vehicle_info->base.model_alt_id == 464
	 ||	 vehicle_info->base.model_alt_id == 501 )
	{
		if ( patch_NotAPlane.installed )
			patcher_remove( &patch_NotAPlane );
		return;
	}

	if ( patch_NotAPlane.installed && !cheat_state->vehicle.fly )
		patcher_remove( &patch_NotAPlane );

	int class_id = gta_vehicle_get_by_id( vehicle_info->base.model_alt_id )->class_id;
	if ( cheat_state->vehicle.fly )
	{
		if ( class_id == VEHICLE_CLASS_HELI )
			return;

		if ( class_id == VEHICLE_CLASS_AIRPLANE )
		{
			if ( last_plane != vehicle_info )
			{
				plane_orig_data[0] = vehicle_info->pFlyData->pitch;
				plane_orig_data[1] = vehicle_info->pFlyData->roll_lr;
				plane_orig_data[2] = vehicle_info->pFlyData->circleAround;
				last_plane = vehicle_info;
			}

			if ( !patch_NotAPlane.installed )
				patcher_install( &patch_NotAPlane );
			needRestorePphys = true;
		}
		else if ( patch_NotAPlane.installed )
		{
			patcher_remove( &patch_NotAPlane );
		}

		struct vehicle_info *temp;
		for ( temp = vehicle_info; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			class_id = gta_vehicle_get_by_id( temp->base.model_alt_id )->class_id;

			// fly physics heli Mode / Bike
			if ( set.fly_vehicle_heliMode || class_id == VEHICLE_CLASS_BIKE )
			{
				temp->pFlyData->pitch = 0.0035f;

				if ( class_id == VEHICLE_CLASS_BIKE )
				{
					temp->pFlyData->roll_lr = -0.01f;			// rolling isn't working with motorized bikes yet
					temp->pFlyData->circleAround = -0.0006f;
				}
				else
				{
					temp->pFlyData->roll_lr = -0.004f;
					temp->pFlyData->circleAround = -0.0003f;
				}
			}

			// fly physics plane Mode
			else
			{
				// use original physics for planes
				if ( class_id == VEHICLE_CLASS_AIRPLANE )
				{
					temp->pFlyData->pitch = plane_orig_data[0];
					temp->pFlyData->roll_lr = plane_orig_data[1];
					temp->pFlyData->circleAround = plane_orig_data[2];
				}
				else
				{
					temp->pFlyData->pitch = 0.0005f;
					temp->pFlyData->roll_lr = 0.005f;
					temp->pFlyData->circleAround = -0.001f;
				}
			}

			// check speed and fTimeStep for valid values
			if ( vect3_length( temp->speed ) < 0.0f || *(float *)0xB7CB5C <= 0.0f )
			{
				if ( !set.trailer_support )
					return;
				continue;
			}

			//  steering  //
			float	one = 0.9997f;
			float	min = -0.9997f;
			float	f[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			uint8_t	*gtakeys = (uint8_t *)GTA_KEYS;

			if (gtakeys[0xE] == 0xFF)		//look left
				f[0] = one;
			else if (gtakeys[0xA] == 0xFF)	//Look right
				f[0] = min;

			if (gtakeys[3] == 0xFF)		//steer forward
				f[1] = min;
			else if (gtakeys[2] == 0x80)	//steer down
				f[1] = one;
			
			if (gtakeys[1] == 0xFF)		//left
				f[2] = min;
			else if (gtakeys[0] == 0x80)	//right
				f[2] = one;

			if (gtakeys[0x1C] == 0xFF)		//accel
				f[3] = min;
			else if (gtakeys[0x20] == 0xFF)	//brake
				f[3] = one;

			//   steering end    //

			// mode = 1 fast plane, 2 heli, 6 heli, 8 airbreak alike
			((void(__thiscall *)(void *, int mode, float, float, float, float))(0x006D85F0))(temp, set.fly_vehicle_heliMode ? 6 : 1, f[0], f[1], f[2], f[3]);

			// no trailer support
			if ( !set.trailer_support )
				return;

			// sorta fix trailer spin
			if ( temp != vehicle_info )
				vect3_copy( vehicle_info->spin, temp->spin );
		}
	}

	// change airplane physics back to normal
	else if ( class_id == VEHICLE_CLASS_AIRPLANE && needRestorePphys )
	{
		vehicle_info->pFlyData->pitch = plane_orig_data[0];
		vehicle_info->pFlyData->roll_lr = plane_orig_data[1];
		vehicle_info->pFlyData->circleAround = plane_orig_data[2];
		needRestorePphys = false;
	}
}

void cheat_handle_vehicle_keepTrailer ( struct vehicle_info *vinfo, float time_diff )
{
	traceLastFunc( "cheat_handle_vehicle_keepTrailer()" );

	// toggle state from key press
	if ( KEYCOMBO_PRESSED(set.key_keep_trailer) )
		cheat_state->vehicle.keep_trailer_attached ^= 1;

	// return if disabled or not driving
	if ( !cheat_state->vehicle.keep_trailer_attached )
		return;

	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( self == NULL || vinfo->passengers[0] != self )
		return;

	// static vars to store trailer info
	static struct vehicle_info	*myveh_old;
	static struct vehicle_info	*mytrailer_old;

	if ( vinfo == myveh_old )
	{
		if ( vinfo->trailer != NULL )
		{
			mytrailer_old = vinfo->trailer;
			return;
		}
		else if ( mytrailer_old != NULL )
		{
			DWORD	trailer_id = ScriptCarId( mytrailer_old );
			if ( trailer_id == NULL )
				return;

			CVector distance = vinfo->base.m_CMatrix->vPos - mytrailer_old->base.m_CMatrix->vPos;
			if ( distance.Length() <= 40.0f )
			{
				// new variables to be used with R* classes
				CVehicle	*cveh, *cvehtrailer;
				CVector		cvehGrav, rotationAxis, vecVehTowBarPos, vecTrailerHitchPos, vecTrailerPos;
				CVector		vZero ( 0.0f, 0.0f, 0.0f );
				CMatrix		cvehMatrix;
				float		theta;

				if ( !cheat_state->vehicle.air_brake )
				{
					// unflip
					// get this vehicle, gravity, and matrix
					cveh = pPools->GetVehicle( (DWORD *)vinfo );
					cveh->GetGravity( &cvehGrav );
					cveh->GetMatrix( &cvehMatrix );

					// get trailer
					cvehtrailer = pPools->GetVehicle( (DWORD *)mytrailer_old );

					// get "down" from vehicle model
					rotationAxis = cheat_vehicle_getPositionUnder( cveh );

					// normalize our vectors
					cvehGrav.Normalize();
					rotationAxis.Normalize();

					// axis and rotation for gravity
					theta = acos( rotationAxis.DotProduct(&cvehGrav) );
					if ( !near_zero(theta) )
					{
						rotationAxis.CrossProduct( &cvehGrav );
						rotationAxis.Normalize();
						rotationAxis.ZeroNearZero();
						cvehMatrix = cvehMatrix.Rotate( &rotationAxis, -theta );

						// set the new matrix
						cveh->SetMatrix( &cvehMatrix );
					}

					// re-attach trailer
					cvehtrailer->SetTowLink( cveh );

					// fix trailer orientation
					rotationAxis = cheat_vehicle_getPositionUnder( cvehtrailer );
					cvehtrailer->GetMatrix( &cvehMatrix );
					theta = acos( rotationAxis.DotProduct(&cvehGrav) );
					if ( !near_zero(theta) )
					{
						rotationAxis.CrossProduct( &cvehGrav );
						rotationAxis.Normalize();
						rotationAxis.ZeroNearZero();
						cvehMatrix = cvehMatrix.Rotate( &rotationAxis, -theta );
						cvehMatrix = cvehMatrix.Rotate( &cvehMatrix.vRight, 0.15f );
						cvehtrailer->SetMatrix( &cvehMatrix );
					}

					// fix trailer position
					cveh->GetTowBarPos( &vecVehTowBarPos );
					cvehtrailer->GetTowHitchPos( &vecTrailerHitchPos );
					vecTrailerPos = cvehtrailer->GetInterface()->Placeable.matrix->vPos;
					vecTrailerPos += vecVehTowBarPos - vecTrailerHitchPos;
					cvehtrailer->SetPosition( &vecTrailerPos );

					// prevent collision from altering speed/spin
					cveh->GetVehicleInterface()->vecVelocityCollision = &vZero;
					cveh->GetVehicleInterface()->vecSpinCollision = &vZero;
					cvehtrailer->GetVehicleInterface()->vecVelocityCollision = &vZero;
					cvehtrailer->GetVehicleInterface()->vecSpinCollision = &vZero;
				}
				else
				{
					// get vehicle pointers
					cveh = pPools->GetVehicle( (DWORD *)vinfo );
					cvehtrailer = pPools->GetVehicle( (DWORD *)mytrailer_old );

					// re-attach trailer
					cvehtrailer->SetTowLink( cveh );
				}
			}
			else
			{
				mytrailer_old = NULL;
			}
		}
	}
	else if ( vinfo->trailer != NULL )
	{
		myveh_old = vinfo;
		mytrailer_old = vinfo->trailer;
	}
	else
	{
		myveh_old = vinfo;
		mytrailer_old = NULL;
	}
}

// remove vehicle_info variable + move into cheat_generic (?)
void cheat_handle_vehicle_fast_exit ( struct vehicle_info *vehicle_info, float time_diff )
{
	traceLastFunc( "cheat_handle_fast_exit()" );

	if ( KEYCOMBO_PRESSED(set.key_fast_exit) )
	{
		float *coord = new float[3];

		// check for collision
		CVehicle *pVehicle = pPedSelf->GetVehicle();
		if (pVehicle)
		{
			CColPoint			*pCollision = nullptr;
			CEntitySAInterface	*pCollisionEntity = nullptr;
			CVector vecPedAbove = (g_vecUpNormal * 15.0f) + *pVehicle->GetPosition(); // up multiplier should be enough to get above most vehicles, but not enough to jump above things over it
			bool bCollision = GTAfunc_ProcessLineOfSight( &vecPedAbove, pVehicle->GetPosition(), &pCollision, &pCollisionEntity,
				0, 1, 0, 1, 0, 0, 0, 0 );
			if (bCollision && pCollision)
			{
				// set pos floats for actual teleporting
				coord[0] = pCollision->GetPosition()->fX;
				coord[1] = pCollision->GetPosition()->fY;
				coord[2] = pCollision->GetPosition()->fZ + 0.5f; // should be enough so we're surfing properly
			}
			if (pCollision != nullptr)
			{
				// destroy the collision object
				pCollision->Destroy();
			}
		}
		else
		{
			// set pos floats for actual teleporting
			coord[0] = pPedSelf->GetPosition()->fX;
			coord[1] = pPedSelf->GetPosition()->fY;
			coord[2] = pPedSelf->GetPosition()->fZ + 5.0f;
		}

		GTAfunc_RemoveActorFromCarAndPutAt(coord);
	}
}

void cheat_handle_vehicle_repair_car ( struct vehicle_info *vehicle_info, float time_diff )
{
	traceLastFunc( "cheat_handle_repair_car()" );

	if ( KEYCOMBO_PRESSED(set.key_repair_car) )
	{
		// get info
		struct vehicle_info *veh_self = vehicle_info_get( VEHICLE_SELF, 0 );
		if ( veh_self == NULL )
			return;

		struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
		if ( self == NULL )
			return;

		// make sure we are driving our own vehicle
		if ( self->state == ACTOR_STATE_DRIVING && self->vehicle->passengers[0] == self )
		{
			struct vehicle_info *temp;

			//fix the vehicle
			for ( temp = vehicle_info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;

				GTAfunc_RepairVehicle(temp);

				if ( !set.trailer_support )
					break;
			}
		}
	}
}

// ---------------------------------------------------------
// ---------------------------------------------------------

/*
CMatrix
	vRight = CVector ( 1.0f, 0.0f, 0.0f );
	vFront = CVector ( 0.0f, 1.0f, 0.0f );
	vUp    = CVector ( 0.0f, 0.0f, 1.0f );
	vPos   = CVector ( 0.0f, 0.0f, 0.0f );
MATRIX4X4
	VECTOR right;	// vRight
	VECTOR up;		// vFront
	VECTOR at;		// vUp
	VECTOR pos;		// vPos
*/
CVector cheat_vehicle_getPositionUnder ( CVehicle *cveh )
{
	traceLastFunc( "cheat_vehicle_getPositionUnder()" );

	CVector offsetVector;
	CMatrix matrix;
	cveh->GetMatrix( &matrix );

	CMatrix_Padded	matrixPad ( matrix );
	offsetVector.fX = 0 * matrixPad.vRight.fX + 0 * matrixPad.vFront.fX - 1 * matrixPad.vUp.fX;
	offsetVector.fY = 0 * matrixPad.vRight.fY + 0 * matrixPad.vFront.fY - 1 * matrixPad.vUp.fY;
	offsetVector.fZ = 0 * matrixPad.vRight.fZ + 0 * matrixPad.vFront.fZ - 1 * matrixPad.vUp.fZ;
	return offsetVector;
}

void cheat_vehicle_setGravity ( CVehicle *cveh, CVector pvecGravity )
{
	traceLastFunc( "cheat_vehicle_setGravity()" );

	// set the d-dang gravity
	cveh->SetGravity( &pvecGravity );

	//5:08:18 PM lol cool
}

struct patch_set	*patchBikeFalloff_set = NULL;
bool				m_SpiderWheels_falloffFound = false;
bool				m_SpiderWheels_falloffEnabled = false;
bool init_patchBikeFalloff ( void )
{
	traceLastFunc( "init_patchBikeFalloff()" );

	if ( !m_SpiderWheels_falloffFound )
	{
		int patchBikeFalloff_ID = GTAPatchIDFinder( 0x004BA3B9 );
		if ( patchBikeFalloff_ID != -1 )
		{
			patchBikeFalloff_set = &set.patch[patchBikeFalloff_ID];
			m_SpiderWheels_falloffFound = true;
		}
		else
		{
			Log( "Couldn't init_patchBikeFalloff." );
			Log( "You may fall off bikes while using SpiderWheels." );
			Log( "Put the 'Anti bike fall off' patch back into your INI to fix this problem." );
		}
	}

	return m_SpiderWheels_falloffFound;
}

void cheat_handle_vehicle_spiderWheels ( struct vehicle_info *vinfo, float time_diff )
{
	traceLastFunc( "cheat_handle_spiderWheels()" );

	// 3:07:16 PM how you going
	if ( KEYCOMBO_PRESSED(set.key_spiderwheels) )
	{
		// init variables used to toggle patch
		init_patchBikeFalloff();

		// toggle the d-dang spiderz
		cheat_state->vehicle.spiderWheels_on ^= 1;
	}

	if ( cheat_state->vehicle.spiderWheels_on )
	{
		// init SpiderWheels
		if ( !cheat_state->vehicle.spiderWheels_Enabled )
		{
			// install anti bike falloff patch if needed
			if ( m_SpiderWheels_falloffFound && !m_SpiderWheels_falloffEnabled && !patchBikeFalloff_set->installed )
			{
				patcher_install( patchBikeFalloff_set );
				m_SpiderWheels_falloffEnabled = true;
			}

			// set spider wheels enabled
			cheat_state->vehicle.spiderWheels_Enabled = true;
		}

		// loop through the vehicle and any trailers
		for ( vehicle_info * temp = vinfo; temp != nullptr; temp = temp->trailer )
		{
			if(temp == nullptr) return;

			// get CVehicle
			CVehicle			*cveh = pGameInterface->GetPools()->GetVehicle( (DWORD *)temp );

			// update spider wheels
			CVector				offsetVector = cheat_vehicle_getPositionUnder( cveh );

			// setup variables
			CVector				vecOrigin, vecTarget;
			CColPoint			*pCollision = nullptr;
			CEntitySAInterface	*pCollisionEntity = nullptr;
			int					checkDistanceMeters = 20;

			// get CEntitySAInterface pointer
			CEntitySAInterface	*cveh_interface = cveh->GetInterface();

			// origin = our vehicle
			vecOrigin = cveh_interface->Placeable.matrix->vPos;
			vecTarget = offsetVector * checkDistanceMeters;
			vecTarget = vecTarget + vecOrigin;

			// check for collision
			bool	bCollision = GTAfunc_ProcessLineOfSight( &vecOrigin, &vecTarget, &pCollision, &pCollisionEntity, 1,
															 0, 0, 1, 1, 0, 0, 0 );

			if ( bCollision )
			{
				// set altered gravity vector
				float	fTimeStep = *(float *)0xB7CB5C;
				CVector colGravTemp = -pCollision->GetInterface()->Normal;
				CVector vehGravTemp;	//= cheat_state->vehicle.gravityVector;
				cveh->GetGravity( &vehGravTemp );

				CVector newRotVector;
				newRotVector = colGravTemp - vehGravTemp;
				newRotVector *= 0.05f * fTimeStep;
				offsetVector = vehGravTemp + newRotVector;

			}
			else
			{
				// set normal gravity vector
				float	fTimeStep = *(float *)0xB7CB5C;
				CVector colGravTemp ( 0.0, 0.0, -1.0 );
				CVector vehGravTemp;
				cveh->GetGravity( &vehGravTemp );

				CVector newRotVector;
				newRotVector = colGravTemp - vehGravTemp;
				newRotVector *= 0.05f * fTimeStep;
				offsetVector = vehGravTemp + newRotVector;
			}
			if (pCollision != nullptr)
			{
				// destroy the collision object
				pCollision->Destroy();
			}
			// set the gravity/camera
			offsetVector.ZeroNearZero();
			cheat_vehicle_setGravity( cveh, offsetVector );
		}
	}
	else if ( cheat_state->vehicle.spiderWheels_Enabled )
	{
		// remove anti bike falloff patch if needed
		if ( m_SpiderWheels_falloffFound && m_SpiderWheels_falloffEnabled )
		{
			if ( patchBikeFalloff_set->installed || patchBikeFalloff_set->failed )
			{
				patcher_remove( patchBikeFalloff_set );
			}

			m_SpiderWheels_falloffEnabled = false;
		}

		// loop through the vehicle and any trailers
		for ( vehicle_info * temp = vinfo; temp != NULL; temp = temp->trailer )
		{
			if(temp == NULL) return;

			// get vehicle
			CVehicle	*cveh = pGameInterface->GetPools()->GetVehicle( (DWORD *)temp );

			// disable spider wheels with normal gravity vector
			CVector		offsetVector ( 0.0, 0.0, -1.0 );

			// set the gravity/camera
			cheat_vehicle_setGravity( cveh, offsetVector );
		}

		// set spider wheels disabled
		cheat_state->vehicle.spiderWheels_Enabled = false;
	}
}

void cheat_handle_freezerot(vehicle_info *vinfo, float time_diff)
{
	if (KEYCOMBO_PRESSED(set.key_freezerot))
	{
		cheat_state->vehicle.freezerot ^= true;
	}
	if (cheat_state->vehicle.freezerot)
	{
		for (vehicle_info * temp = vinfo; temp != NULL; temp = temp->trailer)
		{
			if (temp == NULL) return;

			if ((temp->collision_flags & 0x0000FF00) >> 8 == 0)
			{
				vect3_zero(temp->spin);
			}

			if (!set.trailer_support)
				break;
		}
	}
}