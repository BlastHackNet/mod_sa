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

int cheat_panic ( void )
{
	traceLastFunc( "cheat_panic()" );

	static int	pstate_map = 0, // m0d's map
		pstate_d3dtext_hud = 0, // hud bar
		pstate_actor_hp_nSP = 0, // "Extra actor invincibility" patch (invulnerable single player enemies)
		pstate_actor_hp_SP = 0, // "Extra actor invincibility2" patch (no problems in SP)
		pstate_vehicle_hp = 0, // vehicle hp patch
		pstate_generic_menu = 0, // m0d's menu
		pstate_infnos = 0, // infinite NOS
		pstate_ini[INI_PATCHES_MAX],
		pstate_dummy_aligner; // this should all be a structure, static = DOING IT WRONG
	int			i;

	// sa-mp related
	static int	pstate_chat = 0, // chat
		pstate_deathlist = 0, // deathlist
		pstate_extragm = 0; // extra godmode

	if ( KEYCOMBO_PRESSED(set.key_panic) )
	{
		// toggle panic
		cheat_state->_generic.cheat_panic_enabled ^= 1;

		if ( cheat_state->_generic.cheat_panic_enabled )
		{
			struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );

			if ( actor_info )
			{
				if (cheat_state->_generic.hp_cheat)
					actor_info->flags &= ~ACTOR_FLAGS_INVULNERABLE;
				actor_info->weapon_slot = 0;
			}

			// remove infinite NOS
			pstate_infnos = cheat_state->vehicle.infNOS_toggle_on;
			cheat_state->vehicle.infNOS_toggle_on = false;
			patcher_remove( &patch_vehicle_inf_NOS );

			if ( pPedSelf->GetVehicle() )
			{
				CVehicle	*pVehicleSelf = pPedSelf->GetVehicle();
				CVehicle	*pVehicleTemp = NULL;

				for ( pVehicleTemp = pVehicleSelf; pVehicleTemp != NULL; pVehicleTemp = pVehicleTemp->GetTowedVehicle() )
				{
					pVehicleTemp->SetGravity( &CVector(0.0, 0.0, -1.0) );
					pVehicleTemp->SetCanBeDamaged( true );

					if ( !set.trailer_support )
						break;
				}

				// remove inf NOS
				if ( pstate_infnos )
				{
					pVehicleSelf->RemoveVehicleUpgrade( 1010 );
					//pVehicleSelf->AddVehicleUpgrade( 1010 );
				}

				// reset overrideLights, pstate not needed, will be reactivated on demand
				if ( set.enable_car_lights_at_day_time )
					pVehicleSelf->SetOverrideLights( 0 );
			}

			// hud bar, this should probably become a cheat_state
			pstate_d3dtext_hud = set.d3dtext_hud;
			set.d3dtext_hud = 0;

			// m0d's map
			pstate_map = cheat_state->_generic.map;
			cheat_state->_generic.map = 0;

			// m0d's menu
			pstate_generic_menu = cheat_state->_generic.menu;
			menu_toggle(false);

			// remove "Extra actor invincibility" patch
			pstate_actor_hp_nSP = patch_actor_hp_extraInv.installed;
			patcher_remove( &patch_actor_hp_extraInv );
			pstate_actor_hp_SP = patch_actor_hp.installed;
			patcher_remove( &patch_actor_hp );

			// remove vehicle hp patch
			pstate_vehicle_hp = patch_vehicle_hp.installed;
			patcher_remove( &patch_vehicle_hp );

			// just call with null vehicle info to disable
			cheat_handle_vehicle_fly( NULL, 0.0f );

			for ( i = 0; i < INI_PATCHES_MAX; i++ )
			{
				// added to not remove volatile patches
				if ( !set.patch[i].has_volatile )
				{
					pstate_ini[i] = set.patch[i].installed;
					patcher_remove( &set.patch[i] );
				}
			}

			// turn off kill & chat
			if ( g_DeathList != NULL )
			{
				pstate_deathlist = g_DeathList->iEnabled;
				g_DeathList->iEnabled = 1;
			}
			if ( g_Chat != NULL )
			{
				pstate_chat = g_Chat->iChatWindowMode;
				g_Chat->iChatWindowMode = 2;
			}
			pstate_extragm = set.enable_extra_godmode;
			set.enable_extra_godmode = 0;
		}
		else
		{
			// restore infinite NOS
			if ( pstate_infnos )
			{
				cheat_state->vehicle.infNOS_toggle_on = true;
				patcher_install( &patch_vehicle_inf_NOS );
			}

			// vehicle stuff
			CPed	*pPedSelf = pPools->GetPedFromRef( CPOOLS_PED_SELF_REF );
			if ( pPedSelf->GetVehicle() )
			{
				CVehicle	*pVehicleSelf = pPedSelf->GetVehicle();
				// restore inf NOS
				if ( pstate_infnos )
				{
					pVehicleSelf->AddVehicleUpgrade( 1010 );
				}
			}


			// restore "Extra actor invincibility" patch
			if ( pstate_actor_hp_nSP )
				patcher_install( &patch_actor_hp_extraInv );
			if ( pstate_actor_hp_SP )
				patcher_install( &patch_actor_hp );

			// restore vehicle hp patch
			if ( pstate_vehicle_hp )
				patcher_install( &patch_vehicle_hp );

			// restore some cheat_states
			set.d3dtext_hud = pstate_d3dtext_hud;
			cheat_state->_generic.map = pstate_map;
			menu_toggle(pstate_generic_menu != 0);

			// restore patches
			for ( i = 0; i < INI_PATCHES_MAX; i++ )
			{
				if ( pstate_ini[i] )
					patcher_install( &set.patch[i] );
			}

			// restore kill & chat
			if ( g_DeathList != NULL )
			{
				g_DeathList->iEnabled = pstate_deathlist;
			}
			if ( g_Chat != NULL )
			{
				g_Chat->iChatWindowMode = pstate_chat;
			}

			// restore extra invincibility mode state
			set.enable_extra_godmode = pstate_extragm;

			// clear cheat state text
			cheat_state_text( NULL );
		}
	}

	return cheat_state->_generic.cheat_panic_enabled;
}

/* XXX move to cheat_funcs.cpp? */
extern bool GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport;
void cheat_teleport ( const float pos[3], int interior_id )
{
	if ( cheat_state->state == CHEAT_STATE_ACTOR
		|| GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport )
	{
		GTAfunc_RemoveActorFromCarAndPutAt_requestingTeleport = false;
		cheat_actor_teleport( actor_info_get(ACTOR_SELF, 0), pos, interior_id );
	}
	else if ( cheat_state->state == CHEAT_STATE_VEHICLE ) //&& !set.teleport_slow )
		cheat_vehicle_teleport( vehicle_info_get(VEHICLE_SELF, 0), pos, interior_id );
	/*else if ( cheat_state->state == CHEAT_STATE_VEHICLE && set.teleport_slow )
	{
		vect3_copy(pos, cheat_state->vehicle.tele_coords);
		cheat_state->vehicle.tele_on = 1;
	}*/
}

void cheat_teleport_nearest_car ( void )
{
	int					id = vehicle_find_nearest( VEHICLE_ALIVE | VEHICLE_EMPTY );
	struct vehicle_info *info = vehicle_info_get( id, VEHICLE_ALIVE | VEHICLE_EMPTY );

	if ( id == -1 || info == NULL )
		return;

	cheat_teleport( &info->base.matrix[4 * 3], info->base.interior_id );
}

void cheat_handle_quickwarp(struct vehicle_info *vehicle_info, struct actor_info *actor_info)
{
	if (KEYCOMBO_PRESSED(set.key_quickwarp))
	{
		CCam *pCam = pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam());
		CVector camsrc(*pCam->GetSource()), src, target, tppos;
		CColPoint *pCollision = nullptr;
		CEntitySAInterface *pEntity = nullptr;

		if (pCam->GetMode() == MODE_AIMWEAPON || pCam->GetMode() == MODE_AIMWEAPON_ATTACHED || pCam->GetMode() == MODE_AIMWEAPON_FROMCAR)
		{
			// calculate target position by aim vector
			pGame->GetCamera()->Find3rdPersonCamTargetVector(700.0f, &camsrc, &src, &target);
		}
		else
		{
			// else by camera vector
			target = camsrc + *pCam->GetFront() * 700.0f;
		}

		// ignore self vehicle
		if (vehicle_info != nullptr)
		{
			*(::vehicle_info **)VAR_IgnoredEntity = vehicle_info;
		}

		if (GTAfunc_ProcessLineOfSight(&camsrc, &target, &pCollision, &pEntity, true, true, false, true, true, false, false, false))
		{
			tppos = *pCollision->GetPosition();
			tppos -= (*pCollision->GetNormal()) * 0.5f;
			
			if (pCollision->GetNormal()->fZ >= 0.5f || pPedSelf->GetAreaCode() != 0)
			{
				tppos.fZ += 1.0f;
				tppos.fZ = pGameInterface->GetWorld()->FindGroundZFor3DPosition(&tppos);
			}
			else
			{
				tppos.fZ = pGameInterface->GetWorld()->FindGroundZForPosition(tppos.fX, tppos.fY);
			}

			if (vehicle_info != nullptr)
			{
				// check for collision
				CVehicle *vehSelf = pPedSelf->GetVehicle();
				if (vehSelf)
				{
					pCollision->Destroy();
					// check for collision
					CVector vecVehicleGravity;
					vehSelf->GetGravity(&vecVehicleGravity);
					CVector vecVehicleAbove = (-vecVehicleGravity * 5.0f) + tppos;
					CVector vecVehicleBelow = (vecVehicleGravity * 5.0f) + tppos;
					bool bCollision = GTAfunc_ProcessLineOfSight(&vecVehicleAbove, &vecVehicleBelow, &pCollision, &pEntity,
																 true, false, false, true, true, false, false, false); // not checking for vehicle collisions
					if (bCollision && pCollision)
					{
						// set vehicle to same Up position has surface normal
						CMatrix matVehicleSelf;
						vehSelf->GetMatrix(&matVehicleSelf);
						CVector vecCollisionNormal = *pCollision->GetNormal();

						// get "down" from vehicle model
						CVector rotationAxis = matVehicleSelf.vUp;

						// normalize our vectors
						vecCollisionNormal.Normalize();
						rotationAxis.Normalize();

						// axis and rotation for gravity
						float	theta = acos(rotationAxis.DotProduct(&vecCollisionNormal));
						if (!near_zero(theta))
						{
							rotationAxis.CrossProduct(&vecCollisionNormal);
							rotationAxis.Normalize();
							rotationAxis.ZeroNearZero();
							matVehicleSelf = matVehicleSelf.Rotate(&rotationAxis, -theta);
						}

						// set the new matrix
						vehSelf->SetMatrix(&matVehicleSelf);

						// set pos floats for actual teleporting
						tppos.fX = pCollision->GetPosition()->fX;
						tppos.fY = pCollision->GetPosition()->fY;
						tppos.fZ = pCollision->GetPosition()->fZ + 1.0f; // should be enough to stay above the ground properly
					}
					else
					{
						tppos.fZ += 0.5f;
					}
					cheat_vehicle_teleport(vehicle_info, &tppos.fX, gta_interior_id_get(), true);
				}
			}
			else if (actor_info != nullptr)
			{
				tppos.fZ += 1.0f;
				cheat_actor_teleport(actor_info, &tppos.fX, gta_interior_id_get());
			}
			GTAfunc_TogglePlayerControllable(0);
			GTAfunc_LockActor(0);
		}
		if (pCollision != nullptr)
		{
			pCollision->Destroy();
		}
	}
}

void cheat_handle_misc ( void )
{
	if ( KEYCOMBO_PRESSED(set.key_map) )
	{
		cheat_state->_generic.map ^= 1; /* toggle minimap */
	}

	if ( KEYCOMBO_PRESSED(set.key_map_show_vehicles) )
	{
		cheat_state->_generic.map_vehicles ^= 1;
	}

	if ( KEYCOMBO_PRESSED(set.key_render_player_tags) )
		cheat_state->render_player_tags ^= 1;

	if ( KEYCOMBO_PRESSED(set.key_render_vehicle_tags) )
		cheat_state->render_vehicle_tags ^= 1;

	/* time */
	if ( set.force_hour >= 0 )
		gta_time_hour_set( set.force_hour );

	/* weather */
	if ( set.force_weather >= 0 )
		gta_weather_state_set( set.force_weather );

	SetCloudsEnabled( set.enable_clouds );
}

void cheat_handle_debug ( HWND wnd )
{
	static const int	data_size[4] = { 1, 2, 4, 4 };
	struct debug_info	*debug = &cheat_state->debug;
	int					move = 0, hist_chng = 0;

	if ( !cheat_state->debug_enabled )
		return;

	/* go to pointer */
	if ( KEY_PRESSED(VK_NUMPAD1) )
	{
		setDebugPointer( *(void **)debug->cursor_data );
		hist_chng = 1;
	}

	/* go back */
	if ( KEY_PRESSED(VK_NUMPAD7) )
	{
		if ( debug->hist_pos > 0 )
		{
			debug->hist_pos--;
			hist_chng = 1;
		}
		else if ( debug->hist_pos == 0 )
			setDebugPointer( (void *)NULL );
	}

	/* change data type */
	if ( KEY_PRESSED(VK_DIVIDE) )
		debug->data_type = ( debug->data_type + 1 ) % 4;

	/* inc/dec value */
	if ( KEY_DOWN(VK_ADD) || KEY_DOWN(VK_SUBTRACT) )
	{
		const int	value = KEY_DOWN( VK_ADD ) ? 1 : -1;
		uint8_t		data[4] = { 0, 0, 0, 0 };

		if ( memcpy_safe(data, debug->ptr[debug->hist_pos] + debug->offset[debug->hist_pos], data_size[debug->data_type]) )
		{
			switch ( debug->data_type )
			{
#pragma warning( disable : 4244 )

			case 0:
				( *(uint8_t *)data ) += ( uint8_t ) value;
				break;

			case 1:
				( *(uint16_t *)data ) += ( uint16_t ) value;
				break;

			case 2:
				( *(uint32_t *)data ) += ( uint32_t ) value;
				break;

			case 3:
				( *(float *)data ) += (float)value / 10.0f;
				break;
			}

			memcpy_safe( debug->ptr[debug->hist_pos] + debug->offset[debug->hist_pos], data, data_size[debug->data_type] );
		}
	}

	/* copy info to clipboard */
	if ( KEY_PRESSED(VK_MULTIPLY) )
	{
		if ( OpenClipboard(wnd) )
		{
			HGLOBAL mem = GlobalAlloc( GMEM_MOVEABLE, sizeof(debug->ptr_hist_str) );

			if ( mem != NULL )
			{
				char	*str = (char *)GlobalLock( mem );

				strlcpy( str, debug->ptr_hist_str, sizeof(debug->ptr_hist_str) );
				Log( "%s", str );
				GlobalUnlock( str );

				EmptyClipboard();

				if ( !SetClipboardData(CF_TEXT, mem) )
					Log( "SetClipboardData() %d", GetLastError() );

				/*SetClipboardData(CF_TEXT, mem);*/
			}

			CloseClipboard();
		}
		else
		{
			Log( "OpenClipboard() %d", GetLastError() );
		}
	}

	if ( KEY_PRESSED(VK_NUMPAD4) )
		move -= data_size[debug->data_type];
	if ( KEY_PRESSED(VK_NUMPAD6) )
		move += data_size[debug->data_type];
	if ( KEY_PRESSED(VK_NUMPAD8) )
		move += -16;
	if ( KEY_PRESSED(VK_NUMPAD2) )
		move += 16;
	if ( KEY_PRESSED(VK_NUMPAD9) )
		move += -160;
	if ( KEY_PRESSED(VK_NUMPAD3) )
		move += 160;

	debug->offset[debug->hist_pos] += move;

	if ( move != 0 || hist_chng )
	{
		memset( debug->modify_time, 0, DEBUG_DATA_SIZE * sizeof(uint32_t) );
		debug->data_prev_clear = 1;
	}

	for ( int i = 0; i < 9; i++ )
		KEY_CONSUME( VK_NUMPAD1 + i );
	KEY_CONSUME( VK_MULTIPLY );
	KEY_CONSUME( VK_DIVIDE );
	KEY_CONSUME( VK_ADD );
	KEY_CONSUME( VK_SUBTRACT );
}

void cheat_handle_spoof_weapon ( void )
{
	struct actor_info	*info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );

	/*struct samp_info *spl = samp_info_get();*/
	if ( info != NULL )
	{
		if ( cheat_state->_generic.spoof_weapon != -1 )
			info->weapon_hit_type = ( uint8_t ) cheat_state->_generic.spoof_weapon;
	}
}

void cheat_handle_weapon_disable ( void )
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	struct actor_info	*info;
	int					bad_weapon_ids[] =
	{
		16, /* Grenade */
		17, /* Teargas */
		18, /* Molotov Cocktail */
		35, /* Rocket Launcher */
		36, /* Heat Seeking RPG */
		39, /* Remote Explosives */
		40, /* Detonator */
		-1
	};
	int					i, j;

	if ( !cheat_state->_generic.weapon_disable )
		return;

	for ( i = 0; i < pool_actor->size; i++ )
	{
		if ( (info = actor_info_get(i, ACTOR_ALIVE)) == NULL )
			continue;

		if ( info == self )
			continue;

		if ( info->weapon_slot > 12 )
			continue;

		if ( (int)info->weapon[info->weapon_slot].id > 46 ) /* invalid weapon ID */
			goto bad_weapon;

		/* filter disallowed weapons */
		for ( j = 0; bad_weapon_ids[j] != -1; j++ )
		{
			if ( (int)info->weapon[info->weapon_slot].id == bad_weapon_ids[j] )
				goto bad_weapon;
		}

		continue;
bad_weapon: ;
		info->weapon_slot = 0;
	}
}

struct freeze_info
{
	int		set;
	float	matrix[16];
};

void cheat_handle_freeze_vehicles ( struct vehicle_info *vehicle_info, struct actor_info *actor_info )
{
	traceLastFunc( "cheat_handle_freeze_vehicles()" );

	static struct freeze_info	*freeze;
	struct vehicle_info			*info;
	float						*pos;
	int							i;

	if ( KEYCOMBO_PRESSED(set.key_vehicles_freeze) )
	{
		cheat_state->_generic.vehicles_freeze ^= 1;
		if ( !cheat_state->_generic.vehicles_freeze && freeze != NULL )
			memset( freeze, 0, pool_vehicle->size * sizeof(struct freeze_info) );
	}

	if ( vehicle_info != NULL )
		pos = &vehicle_info->base.matrix[4 * 3];
	else if ( actor_info != NULL )
		pos = &actor_info->base.matrix[4 * 3];
	else
		return;

	if ( freeze == NULL )	/* XXX free on exit */
	{
		freeze = (struct freeze_info *)malloc( pool_vehicle->size * sizeof(struct freeze_info) );
		if ( freeze == NULL )
			return;
		memset( freeze, 0, pool_vehicle->size * sizeof(struct freeze_info) );
	}

	if ( cheat_state->_generic.vehicles_freeze )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			if ( (info = vehicle_info_get(i, VEHICLE_ALIVE)) == NULL || info == vehicle_info )
			{
				if ( info == vehicle_info && freeze[i].set )
					cheat_vehicle_air_brake_set( 1 );	/* entered a frozen vehicle */
				freeze[i].set = 0;
				continue;
			}

			if ( freeze[i].set )
			{
				matrix_copy( freeze[i].matrix, info->base.matrix );
				vect3_mult( info->speed, 0.0f, info->speed );
				vect3_mult( info->spin, 0.0f, info->spin );
			}

			if ( vehicle_contains_trailer(vehicle_info, info) )
			{
				freeze[i].set = 0;
				continue;
			}

			if ( vect3_dist(pos, &info->base.matrix[4 * 3]) >= 80.0f )
			{
				freeze[i].set = 0;
				continue;
			}

			if ( freeze[i].set )
			{
				continue;
			}

			matrix_copy( info->base.matrix, freeze[i].matrix );
			freeze[i].set = 1;
		}
	}
}

void cheat_handle_unlock ( void )
{
	struct vehicle_info *info;
	int					i;

	if ( cheat_state->_generic.vehicles_unlock )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			info = vehicle_info_get( i, 0 );
			if ( info != NULL )
				info->door_status = 1;			/* unlocked */
		}
	}
}

void cheat_handle_hp ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_hp()" );

	static float	prev_pos[3];

	if (KEYCOMBO_PRESSED(set.key_hp_cheat))
	{
		cheat_state->_generic.hp_cheat ^= 1;	/* toggle hp cheat */
		if (!cheat_state->_generic.hp_cheat)
		{
			struct actor_info *self = actor_info_get(ACTOR_SELF, 0);
			self->flags &= ~ACTOR_FLAGS_INVULNERABLE;
		}
	}

	// this will make SP enemies invulnerable
	// now checking for a valid SAMP game
	if (g_SAMP)
	{
		if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable && !set.hp_disable_inv_sp_enemies )
			patcher_install( &patch_actor_hp_extraInv );
		else
			patcher_remove( &patch_actor_hp_extraInv );
	}
	
	if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable )
		patcher_install( &patch_actor_hp );
	else
		patcher_remove( &patch_actor_hp );

	if ( cheat_state->_generic.hp_cheat && cheat_state->vehicle.invulnerable )
		patcher_install( &patch_vehicle_hp );
	else
		patcher_remove( &patch_vehicle_hp );

	if ( vehicle_info != NULL )
	{
		struct vehicle_info *info = vehicle_info;
		struct vehicle_info *temp;

		// actor_info is NULL, if vehicle_info is not ( we need the actor though )
		actor_info = actor_info_get( ACTOR_SELF, 0 );

		if ( cheat_state->_generic.hp_cheat )
		{

			for ( temp = info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;

				/* minimum hp */
				if ( cheat_state->vehicle.hp_minimum_on && temp->hitpoints < set.hp_minimum )
					temp->hitpoints = set.hp_minimum;

				if ( set.hp_keep_vehicleHPsane )
				{
					// actor_info was NULL duh
					if ( temp->passengers[0] == actor_info && temp->hitpoints > 1000.0f )
					{
						if ( set.hp_minimum <= 1000.0f )
							temp->hitpoints = 1000.0f;
						else if ( temp->hitpoints > set.hp_minimum )
							temp->hitpoints = set.hp_minimum;
					}
				}

				/* regen */
				if ( temp->hitpoints < 1000.0f )
					temp->hitpoints += time_diff * set.hp_regen;

				if ( cheat_state->vehicle.invulnerable )
				{
					temp->m_nVehicleFlags.bCanBeDamaged = false;
					//temp->flags |= VEHICLE_FLAGS_INVULNERABLE;	/* invulnerable to most things */
					temp->flags &= ~2; /* make sure we're not frozen :p */
					//if ( temp->pulling_truck != NULL )
					//	temp->hitpoints = 1000.0f;
				}
				else
				{
					temp->m_nVehicleFlags.bCanBeDamaged = true;
					//temp->flags &= ~VEHICLE_FLAGS_INVULNERABLE;
				}

				if ( cheat_state->vehicle.hp_tire_support )
					cheat_vehicle_tires_set( temp, 0 );

				/*
				if(cheat_state->vehicle.is_engine_on == 1)
					temp->m_nVehicleFlags.bEngineOn = 1;
				else if((cheat_state->vehicle.is_engine_on == 0))
					temp->m_nVehicleFlags.bEngineOn = 0;
				*/
				// temp->engine_state |= 16; // protect against engine stalls
				if ( !set.trailer_support )
					break;
			}
		}
		else
		{
			for ( temp = info; temp != NULL; temp = temp->trailer )
			{
				if(temp == NULL) return;

				// HP cheat disabled - keep HP value sane
				if ( set.hp_keep_vehicleHPsane )
				{
					if ( temp->hitpoints > 1000.0f )
						temp->hitpoints = 1000.0f;
				}

				temp->m_nVehicleFlags.bCanBeDamaged = true;
				//temp->flags &= ~VEHICLE_FLAGS_INVULNERABLE;

				if ( !set.trailer_support )
					break;
			}
		}
	}

	if ( actor_info != NULL )
	{
		struct actor_info	*info = actor_info;

		if ( cheat_state->_generic.hp_cheat )
		{
			if ( info->hitpoints < 100.0f )
				info->hitpoints += time_diff * set.hp_regen_onfoot;
		}

		if ( cheat_state->_generic.hp_cheat && cheat_state->actor.invulnerable )
		{
			// invulnerability is on - at least be
			//  invulnerable against non explosive projectiles
			info->flags |= 4;
			if ( set.hp_actor_explosion_inv )
				info->flags |= 8;
			if ( set.hp_actor_fall_inv )
				info->flags |= 64;
			if ( set.hp_actor_fire_inv )
				info->flags |= 128;
			//info->flags |= ACTOR_FLAGS_INVULNERABLE;
		}
	}
}

void cheat_handle_stick ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_stick()" );

	struct object_base	*base_stick, *base_self;
	struct actor_info	*actor_stick;
	struct vehicle_info *vehicle_stick;
	float				*speed_stick, *speed_self;
	float				*spin_stick, *spin_self;
	static int			id = -1;
	int					i;

	if ( KEYCOMBO_PRESSED(set.key_stick) )
	{
		if ( vehicle_info != NULL )
			cheat_state->vehicle.stick ^= 1;
		else
			cheat_state->actor.stick ^= 1;
		id = actor_find( id - 1, 1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
	}

	if ( KEYCOMBO_PRESSED(set.key_stick_nearest) )
	{
		if ( vehicle_info != NULL )
			cheat_state->vehicle.stick ^= 1;
		else
			cheat_state->actor.stick ^= 1;
		id = actor_find_nearest( ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
	}

	if ( (vehicle_info != NULL && cheat_state->vehicle.stick) || (actor_info != NULL && cheat_state->actor.stick) )
	{
		// remove any bad vehicle or actor stuffs
		if ( isBadPtr_GTA_pVehicle(vehicle_info) )
			vehicle_info = NULL;
		if ( isBadPtr_GTA_pPed(actor_info) )
			actor_info = NULL;

		/* check if actor has disappeared.. and if it has, switch to teh nearest */
		if ( id != -1 && actor_info_get(id, ACTOR_ALIVE) == NULL )
			id = actor_find_nearest( ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		if ( KEYCOMBO_PRESSED(set.key_stick_prev) )
			id = actor_find( id, -1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		if ( KEYCOMBO_PRESSED(set.key_stick_next) )
			id = actor_find( id, 1, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );

		/* no actors to stick to */
		if ( id == -1 )
		{
			cheat_state_text( "No players found; stick disabled." );
			cheat_state->vehicle.stick = 0;
			cheat_state->actor.stick = 0;
			return;
		}

		/* get actor struct for the actor we're sticking to */
		actor_stick = actor_info_get( id, ACTOR_ALIVE | ACTOR_NOT_SAME_VEHICLE );
		if ( actor_stick == NULL )
			return;

		/* is this actor in a vehicle? */
		vehicle_stick = actor_vehicle_get( actor_stick );

		base_stick = vehicle_stick ? &vehicle_stick->base : &actor_stick->base;
		base_self = vehicle_info ? &vehicle_info->base : &actor_info->base;

		speed_stick = vehicle_stick ? vehicle_stick->speed : actor_stick->speed;
		speed_self = vehicle_info ? vehicle_info->speed : actor_info->speed;

		spin_stick = vehicle_stick ? vehicle_stick->spin : actor_stick->spin;
		spin_self = vehicle_info ? vehicle_info->spin : actor_info->spin;

		/* allow warping to work + always warp towards whatever we're sticking to...
         but only when we're in a vehicle */
		if ( KEYCOMBO_PRESSED(set.key_warp_mod) && vehicle_info != NULL )
		{
			float	out[4];

			/* multiply the matrix of whatever we're sticking to with the user supplied vector */
			matrix_vect4_mult( base_stick->matrix, set.stick_vect, out );

			/* multiply the result with the negative warp-speed value, and put it in the speed vector
            (negative because we want to warp towards teh target, not away from it */
			vect3_mult( out, -set.warp_speed, speed_self );
		}

		if ( !KEYCOMBO_DOWN(set.key_warp_mod) )
		{
			float	d[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			float	accel_mult = 1.0f;
			float	out[4];

			/* handle stick movement keys */
			if ( KEYCOMBO_DOWN(set.key_stick_forward) )
				d[1] += 1.0f;
			if ( KEYCOMBO_DOWN(set.key_stick_backward) )
				d[1] -= 1.0f;
			if ( KEYCOMBO_DOWN(set.key_stick_left) )
				d[0] -= 1.0f;
			if ( KEYCOMBO_DOWN(set.key_stick_right) )
				d[0] += 1.0f;
			if ( KEYCOMBO_DOWN(set.key_stick_up) )
				d[2] += 1.0f;
			if ( KEYCOMBO_DOWN(set.key_stick_down) )
				d[2] -= 1.0f;
			if ( KEYCOMBO_DOWN(set.key_stick_in) )
				d[3] -= 1.0f;
			if ( KEYCOMBO_DOWN(set.key_stick_out) )
				d[3] += 1.0f;

			if ( !near_zero(set.stick_accel_time) )
			{
				static uint32_t time_start;

				if ( !vect4_near_zero(d) )
					time_start = ( time_start == 0 ) ? time_get() : time_start;
				else
					time_start = 0;			/* no keys pressed */

				/* acceleration */
				if ( time_start != 0 )
				{
					float	t = TIME_TO_FLOAT( time_get() - time_start );
					if ( t < set.stick_accel_time )
						accel_mult *= t / set.stick_accel_time;
				}
			}

			/* calculate new vector + dist */
			if ( !vect3_near_zero(d) && !vect3_near_zero(set.stick_vect) )
			{
				for ( i = 0; i < 3; i++ )
				{
					d[i] = set.stick_vect[i] * set.stick_vect_dist + d[i] * time_diff * 8.0f * accel_mult;
				}

				set.stick_vect_dist = vect3_length( d );
				vect3_normalize( d, set.stick_vect );
			}

			/* move towards/away from the center */
			if ( !near_zero(d[3]) )
				set.stick_vect_dist += d[3] * time_diff * 40.0f * accel_mult;

			/* Teleport vehicle detachables */
			if ( vehicle_info != NULL )
				vehicle_detachables_teleport( vehicle_info, &base_self->matrix[4 * 3], &base_stick->matrix[4 * 3] );

			matrix_copy( base_stick->matrix, base_self->matrix );
			vect3_copy( speed_stick, speed_self );
			vect3_copy( spin_stick, spin_self );

			/*base_self->interior_id = base_stick->interior_id;
         gta_interior_id_set(base_stick->interior_id);*/
			/* multiply the matrix of the target with the user supplied vector */
			matrix_vect4_mult( base_stick->matrix, set.stick_vect, out );

			/* multiply the result with the user supplied vector distance */
			vect3_mult( out, set.stick_vect_dist, out );

			/* and add it to our position */
			vect3_vect3_add( &base_self->matrix[4 * 3], out, &base_self->matrix[4 * 3] );

			if ( vehicle_info != NULL )
			{
				/* Teleport detachables again :p */
				vehicle_detachables_teleport( vehicle_info, &base_stick->matrix[4 * 3], &base_self->matrix[4 * 3] );
				vehicle_prevent_below_height( vehicle_info, set.stick_min_height );
			}
			else if ( actor_info != NULL )
			{
				// new pedFlags
				actor_info->pedFlags.bIsStanding = true;
				actor_info->pedFlags.bWasStanding = true;
				actor_info->pedFlags.bStayInSamePlace = true;
			}
		}
	}
}

static int __money_interval_rand_time ( void )
{
	const int	min = set.money_interval_rand_min;
	const int	max = set.money_interval_rand_max + 1;

	return MSEC_TO_TIME( (min + (rand() % (max - min))) * 1000 );
}

void cheat_handle_money ( void )
{
	static uint32_t next_time;

	if ( !cheat_state->_generic.money )
		next_time = time_get();

	if ( KEYCOMBO_PRESSED(set.key_money) )
		cheat_state->_generic.money ^= 1;

	if ( cheat_state->_generic.money && time_get() >= next_time )
	{
		const int	min = set.money_amount_rand_min;
		const int	max = set.money_amount_rand_max;
		uint32_t	money = gta_money_get();
		int			add;

		if ( money < (uint32_t) set.money_amount_max )
		{
			add = ( (max - min) > 0 ) ? ( rand() % (max - min) ) : 0;
			add = ( (add + 50) / 100 ) * 100;
			money += min + add;
			gta_money_set( money );
		}

		next_time = time_get() + __money_interval_rand_time();
	}
}

void cheat_handle_weapon ( void )
{
	struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	int					i;

	if ( KEYCOMBO_PRESSED(set.key_weapon) )
		cheat_state->_generic.weapon ^= 1;	/* toggle weapon cheat */

	if ( cheat_state->_generic.weapon )
	{
		if ( actor_info != NULL )
		{
			for ( i = 0; i < 13; i++ )
			{
				if ( set.weapon[i] == NULL )
					continue;

				if ( set.ammo_random )
				{
					if ( actor_info->weapon[set.weapon[i]->slot].id != set.weapon[i]->id
					 ||	 (
							 actor_info->weapon[set.weapon[i]->slot].ammo == 0
					 &&	 actor_info->weapon[set.weapon[i]->slot].ammo_clip == 0
					 ) )
					{
						int randammo = ( rand() % set.ammo ) + 1;
						int randammoclip = ( rand() % set.ammo_clip ) + 1;
						gta_weapon_set( actor_info, set.weapon[i]->slot, set.weapon[i]->id, randammo, randammoclip );
					}
				}
				else
				{
					gta_weapon_set( actor_info, set.weapon[i]->slot, set.weapon[i]->id, set.ammo, set.ammo_clip );
				}
			}
		}
		else if ( !set.restore_weapons_after_death )
		{
			cheat_state->_generic.weapon = 0;
		}
	}
}

void cheat_handle_teleport ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_teleport()" );

	struct object_base	*base = ( vehicle_info != NULL ) ? &vehicle_info->base : &actor_info->base;
	int					i;

	// Set teleport coordinates
	for ( i = 0; i < TELEPORT_MAX; i++ )
	{
		if ( set.key_teleport_set[i].count == 0 )
			continue;
		if ( KEYCOMBO_PRESSED(set.key_teleport_set[i]) )
		{
			cheat_state->teleport[i].set = 1;
			matrix_copy( base->matrix, cheat_state->teleport[i].matrix );
			cheat_state->teleport[i].interior_id = gta_interior_id_get();
			cheat_state_text( "Teleport coordinates set." );
		}
	}

	// Teleport to stored coordinates
	for ( i = 0; i < TELEPORT_MAX; i++ )
	{
		if ( set.key_teleport[i].count == 0 )
			continue;
		if ( KEYCOMBO_PRESSED(set.key_teleport[i]) )
		{
			if ( cheat_state->teleport[i].set )
			{
				cheat_teleport_history_save();
				cheat_teleport( &cheat_state->teleport[i].matrix[4 * 3], cheat_state->teleport[i].interior_id );

				// when teleports are stored in-game, we have a copy of the matrix to preserve rotation, etc..
				matrix_copy( cheat_state->teleport[i].matrix, base->matrix );
			}
			else if ( !vect3_near_zero(set.teleport[i].pos) )
			{
				cheat_teleport_history_save();
				cheat_teleport( set.teleport[i].pos, set.teleport[i].interior_id );
			}
			else
			{
				cheat_state_text( "Teleport coordinates not set." );
				break;
			}
			break;
		}
	}

	if ( KEYCOMBO_PRESSED(set.key_teleport_hist) )
	{
		struct cheat_state_teleport *teleport = NULL;

		cheat_state->teleport_hist_count--;
		if ( cheat_state->teleport_hist_count < 0 )
			cheat_state->teleport_hist_count = 0;
		else
			teleport = &cheat_state->teleport_hist[cheat_state->teleport_hist_count];

		if ( teleport != NULL && teleport->set )
		{
			cheat_teleport( &teleport->matrix[4 * 3], teleport->interior_id );
			matrix_copy( teleport->matrix, base->matrix );
			teleport->set = 0;
		}
		else
		{
			cheat_state_text( "Teleport history list is empty." );
		}
	}
}

void cheat_handle_checkpoint ( void )
{
	if ( KEYCOMBO_PRESSED(set.key_checkpoint_1) || KEYCOMBO_PRESSED(set.key_checkpoint_2) )
	{
		int					n = KEYCOMBO_PRESSED( set.key_checkpoint_1 ) ? 0 : 1;
		struct checkpoint	*cp = gta_checkpoint_info_get( n );
		float				pos[3];

		if ( cp != NULL )
		{
			struct vehicle_info *vehicle_info = vehicle_info_get( VEHICLE_SELF, 0 );

			vect3_copy( cp->position, pos );
			pos[2] += 1.0f;
			cheat_teleport( pos, 0 );		/* XXX interior id? */

			if ( vehicle_info != NULL )
				vehicle_prevent_below_height( vehicle_info, set.checkpoint_min_height );
		}
		else
		{
			cheat_state_text( "Checkpoint does not exist." );
		}
	}
}

void cheat_handle_unfreeze ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_unfreeze()" );

	if ( KEYCOMBO_PRESSED(set.key_anti_freeze) )
	{
		GTAfunc_TogglePlayerControllable(0);
		GTAfunc_LockActor(0);
		pGameInterface->GetCamera()->RestoreWithJumpCut();
		
		// stop all animations
		if ( actor_info != NULL && !actor_info->pedFlags.bInVehicle )
			GTAfunc_DisembarkInstantly();
	}
}

void cheat_handle_emo ( struct vehicle_info *vehicle_info, struct actor_info *actor_info, float time_diff )
{
	traceLastFunc( "cheat_handle_emo()" );

	struct vehicle_info *vtemp;

	if ( !isBadPtr_GTA_pPed(actor_info) )
	{
		if ( KEYCOMBO_PRESSED(set.key_self_destruct) )
			actor_info->hitpoints = 0.0f;
	}
	else if ( !isBadPtr_GTA_pVehicle(vehicle_info) )
	{
		actor_info = actor_info_get(ACTOR_SELF, 0);
		if ( actor_info->state == ACTOR_STATE_DRIVING && actor_info->vehicle->passengers[0] == actor_info )
		{
			if ( KEYCOMBO_PRESSED(set.key_self_destruct) )
			{
				for ( vtemp = vehicle_info; vtemp != NULL; vtemp = vtemp->trailer )
				{
					if(vtemp == NULL) return;

					vtemp->hitpoints = 1.0f;
					cheat_vehicle_tires_set( vtemp, 1 );
					if ( !set.trailer_support )
						break;
				}
			}
		}
	}
}

void cheat_handle_exit_vehicle ( struct vehicle_info *vehicle_info, struct actor_info *actor_info )
{
	if (!isBadPtr_GTA_pVehicle(vehicle_info))
	{
		if (vehicle_info != cheat_state->_generic.pVehicleExit_Last)
		{
			if (!isBadPtr_GTA_pVehicle(cheat_state->_generic.pVehicleExit_Last))
			{
				cheat_state->_generic.pVehicleExit_Last->m_nVehicleFlags.bCanBeDamaged = true;
			}
			cheat_state->_generic.pVehicleExit_Last = vehicle_info;
		}
	}
	if (!isBadPtr_GTA_pPed(actor_info))
	{
		if (!isBadPtr_GTA_pVehicle(cheat_state->_generic.pVehicleExit_Last))
		{
			cheat_state->_generic.pVehicleExit_Last->m_nVehicleFlags.bCanBeDamaged = true;
			cheat_state->_generic.pVehicleExit_Last = NULL;
		}
	}
}
