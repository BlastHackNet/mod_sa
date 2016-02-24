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

int			g_iSpectateEnabled = 0, g_iSpectateLock = 0, g_iSpectatePlayerID = -1;
int			g_iJoiningServer = 0;
int			iClickWarpEnabled = 0;
int			g_iNumPlayersMuted = 0;
bool		g_bPlayerMuted[SAMP_MAX_PLAYERS];

void sampMainCheat(void)
{
	traceLastFunc("sampMainCheat()");

	// g_Vehicles & g_Players pointers need to be refreshed or nulled
	if (isBadPtr_writeAny(g_SAMP->pPools, sizeof(stSAMPPools)))
	{
		g_Vehicles = NULL;
		g_Players = NULL;
	}
	else if (g_Vehicles != g_SAMP->pPools->pVehicle || g_Players != g_SAMP->pPools->pPlayer)
	{
		if (isBadPtr_writeAny(g_SAMP->pPools->pVehicle, sizeof(stVehiclePool)))
			g_Vehicles = NULL;
		else
			g_Vehicles = g_SAMP->pPools->pVehicle;
		if (isBadPtr_writeAny(g_SAMP->pPools->pPlayer, sizeof(stPlayerPool)))
			g_Players = NULL;
		else
			g_Players = g_SAMP->pPools->pPlayer;
	}

	// update GTA to SAMP translation structures
	update_translateGTASAMP_vehiclePool();
	update_translateGTASAMP_pedPool();

	spectateHandle();
	sampAntiHijack();

	// start chatbox logging
	if (set.chatbox_logging)
	{
		static int	chatbox_init;
		if (!chatbox_init)
		{
			SYSTEMTIME	time;
			GetLocalTime(&time);
			LogChatbox(false, "Session started at %02d/%02d/%02d", time.wDay, time.wMonth, time.wYear);
			chatbox_init = 1;
		}
	}

	if (KEYCOMBO_PRESSED(set.key_player_info_list))
		cheat_state->player_info_list ^= 1;

	if (KEYCOMBO_PRESSED(set.key_rejoin))
	{
		restartGame();
		disconnect(500);
		cheat_state_text("Rejoining in %d seconds...", set.rejoin_delay / 1000);
		cheat_state->_generic.rejoinTick = GetTickCount();
	}

	if (KEYCOMBO_PRESSED(set.key_respawn))
		playerSpawn();
	
	if (KEYCOMBO_DOWN(set.chat_secondary_key))
	{
		int			i, key, spam;
		const char	*msg;
		for (i = 0; i < INI_CHATMSGS_MAX; i++)
		{
			struct chat_msg *msg_item = &set.chat[i];
			if (msg_item->key == NULL)
				continue;
			if (msg_item->msg == NULL)
				continue;
			if (msg_item->key != key_being_pressed)
				continue;
			key = msg_item->key;
			msg = msg_item->msg;
			spam = msg_item->spam;
			if (spam)
			{
				if (msg)
					if (KEY_DOWN(key))
						say("%s", msg);
			}
			else
			{
				if (msg)
					if (KEY_PRESSED(key))
						say("%s", msg);
			}
		}
	}
	if (set.clickwarp_enabled && iIsSAMPSupported)
	{
		if (KEYCOMBO_PRESSED(set.key_clickwarp_enable))
		{
			g_iCursorEnabled ^= 1;
			toggleSAMPCursor(g_iCursorEnabled);
		}
		if (g_iCursorEnabled && KEYCOMBO_PRESSED(set.key_clickwarp_click))
		{
			iClickWarpEnabled = 1;
		}
	}

	static int	iSAMPHooksInstalled;
	if (!iSAMPHooksInstalled)
	{
		installSAMPHooks();
		iSAMPHooksInstalled = 1;
	}

	if (cheat_state->_generic.rejoinTick && cheat_state->_generic.rejoinTick < (GetTickCount() - set.rejoin_delay))
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		cheat_state->_generic.rejoinTick = 0;
	}

	if (g_iJoiningServer == 1)
	{
		restartGame();
		disconnect(500);
		cheat_state_text("Joining server in %d seconds...", set.rejoin_delay / 1000);
		cheat_state->_generic.join_serverTick = GetTickCount();
		g_iJoiningServer = 2;
	}

	if (g_iJoiningServer == 2
		&& cheat_state->_generic.join_serverTick
		&&	 cheat_state->_generic.join_serverTick < (GetTickCount() - set.rejoin_delay))
	{
		g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
		g_iJoiningServer = 0;
		cheat_state->_generic.join_serverTick = 0;
	}
}

void spectateHandle(void)
{
	if (g_iSpectateEnabled)
	{
		if (g_iSpectateLock) return;

		if (g_iSpectatePlayerID != -1)
		{
			if (g_Players->iIsListed[g_iSpectatePlayerID] != 0)
			{
				if (g_Players->pRemotePlayer[g_iSpectatePlayerID] != NULL)
				{
					int iState = getPlayerState(g_iSpectatePlayerID);

					if (iState == PLAYER_STATE_ONFOOT)
					{
						struct actor_info *pPlayer = getGTAPedFromSAMPPlayerID(g_iSpectatePlayerID);
						if (pPlayer == NULL) return;
						GTAfunc_CameraOnActor(pPlayer);
						g_iSpectateLock = 1;
					}
					else if (iState == PLAYER_STATE_DRIVER)
					{
						struct vehicle_info *pPlayerVehicleID = g_Players->pRemotePlayer[g_iSpectatePlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;
						if (pPlayerVehicleID == NULL) return;
						GTAfunc_CameraOnVehicle(pPlayerVehicleID);
						g_iSpectateLock = 1;
					}
					else if (iState == PLAYER_STATE_PASSENGER)
					{
						struct vehicle_info *pPlayerVehicleID = g_Players->pRemotePlayer[g_iSpectatePlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;
						if (pPlayerVehicleID == NULL) return;
						GTAfunc_CameraOnVehicle(pPlayerVehicleID);
						g_iSpectateLock = 1;
					}
				}
				else
				{
					cheat_state_text("Player is not streamed in");
					g_iSpectateEnabled = 0;
				}
			}
		}
	}
}

void spectatePlayer(int iPlayerID)
{
	if (iPlayerID == -1)
	{
		GTAfunc_TogglePlayerControllable(0);
		GTAfunc_LockActor(0);
		pGameInterface->GetCamera()->RestoreWithJumpCut();

		g_iSpectateEnabled = 0;
		g_iSpectateLock = 0;
		g_iSpectatePlayerID = -1;
		return;
	}

	g_iSpectatePlayerID = iPlayerID;
	g_iSpectateLock = 0;
	g_iSpectateEnabled = 1;
}

void sampAntiHijack(void)
{
	if (g_SAMP == NULL) return;
	traceLastFunc("sampAntiHijack()");

	vehicle_info *veh = vehicle_info_get(VEHICLE_SELF, VEHICLE_ALIVE);
	if (set.anti_carjacking && veh == NULL)
	{
		if (cheat_state->_generic.got_vehicle_id)
			cheat_state->_generic.got_vehicle_id = false;
		if (cheat_state->_generic.anti_carjackTick
			&&	 cheat_state->_generic.anti_carjackTick < (GetTickCount() - 500)
			&& cheat_state->_generic.car_jacked)
		{
			if (cheat_state->_generic.car_jacked_last_vehicle_id == 0)
			{
				GTAfunc_showStyledText("~r~Unable To Unjack~w~!", 1000, 5);
				cheat_state->_generic.anti_carjackTick = 0;
				cheat_state->_generic.car_jacked = false;
				return;
			}

			cheat_state->_generic.anti_carjackTick = 0;
			cheat_state->_generic.car_jacked = false;
			GTAfunc_PutActorInCar(GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id));

			struct vehicle_info *veh = GetVehicleByGtaId(cheat_state->_generic.car_jacked_last_vehicle_id);
			//if ( veh != NULL )
			//	vect3_copy( cheat_state->_generic.car_jacked_lastPos, &veh->base.matrix[4 * 3] );
			GTAfunc_showStyledText("~r~Car Unjacked~w~!", 1000, 5);
			return;
		}
	}
	else if (set.anti_carjacking)
	{
		if (veh->passengers[0] == actor_info_get(ACTOR_SELF, 0))
		{
			if (!cheat_state->_generic.got_vehicle_id)
			{
				cheat_state->_generic.car_jacked_last_vehicle_id = getPlayerVehicleGTAScriptingID(ACTOR_SELF);
				if (cheat_state->_generic.car_jacked_last_vehicle_id > 0)
					cheat_state->_generic.got_vehicle_id = true;
			}
		}
	}
}

void HandleRPCPacketFunc(unsigned char id, RPCParameters *rpcParams, void(*callback) (RPCParameters *))
{
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[id][INCOMING_RPC] != nullptr && set.netPatchAssoc[id][INCOMING_RPC]->enabled)
			return;
	}
	if (rpcParams != nullptr && rpcParams->numberOfBitsOfData >= 8)
	{
		switch (id)
		{
			case RPC_SetPlayerHealth:
			{
				if (isCheatPanicEnabled() || !set.enable_extra_godmode || !cheat_state->_generic.hp_cheat) break;

				actor_info *self = actor_info_get(ACTOR_SELF, NULL);
				if (self)
				{
					BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
					float fHealth;
					bsData.Read(fHealth);
					if (fHealth < self->hitpoints)
					{
						cheat_state_text("Warning: Server tried change your health to %0.1f", fHealth);
						return; // exit from the function without processing RPC
					}
				}
				break;
			}
			case RPC_SetVehicleHealth:
			{
				if (isCheatPanicEnabled() || !set.enable_extra_godmode || !cheat_state->_generic.hp_cheat) break;

				vehicle_info *vself = vehicle_info_get(VEHICLE_SELF, NULL);
				if (vself)
				{
					BitStream bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
					short sId;
					float fHealth;
					bsData.Read(sId);
					bsData.Read(fHealth);
					if (sId == g_Players->pLocalPlayer->sCurrentVehicleID && fHealth < vself->hitpoints)
					{
						cheat_state_text("Warning: Server tried change your vehicle health to %0.1f", fHealth);
						return; // exit from the function without processing RPC
					}
				}
				break;
			}
			case RPC_ClientMessage:
			{
				if (isCheatPanicEnabled() || !set.anti_spam && !set.chatbox_logging) break;

				BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				uint32_t		dwStrLen, dwColor;
				char			szMsg[256];
				static char		last_servermsg[256];
				static DWORD	allow_show_again = 0;

				if (cheat_state->_generic.cheat_panic_enabled)
					break;

				bsData.Read(dwColor);
				bsData.Read(dwStrLen);
				if (dwStrLen >= sizeof(szMsg)) dwStrLen = sizeof(szMsg) - 1;
				bsData.Read(szMsg, dwStrLen);
				szMsg[dwStrLen] = '\0';

				if (set.anti_spam && (strcmp(last_servermsg, szMsg) == 0 && GetTickCount() < allow_show_again))
					return; // exit without processing rpc

				// might be a personal message by muted player - look for name in server message
				// ignore message, if name was found
				if (set.anti_spam && g_iNumPlayersMuted > 0)
				{
					int i, j;
					char *playerName = NULL;
					for (i = 0, j = 0; i < SAMP_MAX_PLAYERS && j < g_iNumPlayersMuted; i++)
					{
						if (g_bPlayerMuted[i])
						{
							playerName = (char *)getPlayerName(i);

							if (playerName == NULL)
							{
								// Player not connected anymore - remove player from muted list
								g_bPlayerMuted[i] = false;
								g_iNumPlayersMuted--;
								continue;
							}
							else if (strstr(szMsg, playerName) != NULL)
							{
								return;
							}
							j++;
						}
					}
				}
				if (set.chatbox_logging)
					LogChatbox(false, "%s", szMsg);
				strncpy_s(last_servermsg, szMsg, sizeof(last_servermsg) - 1);
				allow_show_again = GetTickCount() + 5000;
				break;
			}
			case RPC_Chat:
			{
				if (isCheatPanicEnabled() || !set.anti_spam && !set.chatbox_logging) break;

				BitStream		bsData(rpcParams->input, rpcParams->numberOfBitsOfData / 8, false);
				static char		last_clientmsg[SAMP_MAX_PLAYERS][256];
				static DWORD	allow_show_again = 0;
				uint16_t		playerId = uint16_t(-1);
				uint8_t			byteTextLen;
				char			szText[256];

				if (cheat_state->_generic.cheat_panic_enabled)
					break;

				bsData.Read(playerId);
				if (isBadSAMPPlayerID(playerId))
					break;

				bsData.Read(byteTextLen);
				bsData.Read(szText, byteTextLen);
				szText[byteTextLen] = '\0';

				if (set.anti_spam && ((strcmp(last_clientmsg[playerId], szText) == 0 && GetTickCount() < allow_show_again) || (g_iNumPlayersMuted > 0 && g_bPlayerMuted[playerId])))
					return; // exit without processing rpc

				// nothing to copy anymore, after chatbox_logging, so copy this before
				strncpy_s(last_clientmsg[playerId], szText, sizeof(last_clientmsg[playerId]) - 1);

				if (set.chatbox_logging)
					LogChatbox(false, "%s: %s", getPlayerName(playerId), szText);
				allow_show_again = GetTickCount() + 5000;
				break;
			}
		} // switch
	}
	callback(rpcParams);
}

bool OnSendRPC(int uniqueID, BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[uniqueID][OUTCOMING_RPC] != nullptr && set.netPatchAssoc[uniqueID][OUTCOMING_RPC]->enabled)
			return false;
	}
	if (uniqueID == RPC_Chat && g_Players != nullptr)
	{
		uint8_t byteTextLen;
		char szText[256];

		parameters->Read(byteTextLen);
		parameters->Read(szText, byteTextLen);
		szText[byteTextLen] = '\0';

		if (set.chatbox_logging)
			LogChatbox(false, "%s: %s", getPlayerName(g_Players->sLocalPlayerID), szText);
	}

	// prevent invulnerability detection
	if (uniqueID == RPC_ClientCheck && cheat_state && cheat_state->_generic.hp_cheat)
	{
		uint8_t type = 0;
		parameters->Read(type);
		if (type == 2)
		{
			uint32_t arg = 0;
			uint8_t response = 0;
			parameters->Read(arg);
			parameters->Read(response);

			// remove invulnerability flags from our real flags
			uint32_t fakeFlags = arg & (0xFF00FFFF | ((~ACTOR_FLAGS_INVULNERABLE) << 16));

			// reform packet data
			parameters->SetWriteOffset(0);
			parameters->Write(type);
			parameters->Write(fakeFlags);
			parameters->Write(response);
		}
	}
	return true;
}

bool OnSendPacket(BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	if (!isCheatPanicEnabled())
	{
		uint8_t packetId;
		parameters->Read(packetId);
		if (set.netPatchAssoc[packetId][OUTCOMING_PACKET] != nullptr && set.netPatchAssoc[packetId][OUTCOMING_PACKET]->enabled)
			return false;
	}
	return true;
}

bool OnReceivePacket(Packet *p)
{
	if (p->data == nullptr || p->length == 0)
		return true;
	if (!isCheatPanicEnabled())
	{
		if (set.netPatchAssoc[p->data[0]][INCOMING_PACKET] != nullptr && set.netPatchAssoc[p->data[0]][INCOMING_PACKET]->enabled)
			return false;
	}
	if (p->data[0] == ID_MARKERS_SYNC) // packetId
	{
		BitStream	bs(p->data, p->length, false);
		int			iNumberOfPlayers = 0;
		uint16_t	playerID = uint16_t(-1);
		short		sPos[3] = { 0, 0, 0 };
		bool		bIsPlayerActive = false;

		bs.IgnoreBits(8);
		bs.Read(iNumberOfPlayers);
		if (iNumberOfPlayers < 0 || iNumberOfPlayers > SAMP_MAX_PLAYERS)
			return true;

		for (int i = 0; i < iNumberOfPlayers; i++)
		{
			bs.Read(playerID);
			bs.ReadCompressed(bIsPlayerActive);
			if (bIsPlayerActive == 0 || isBadSAMPPlayerID(playerID))
				continue;
			bs.Read(sPos);
			g_stStreamedOutInfo.iPlayerID[playerID] = playerID;
			g_stStreamedOutInfo.fPlayerPos[playerID][0] = sPos[0];
			g_stStreamedOutInfo.fPlayerPos[playerID][1] = sPos[1];
			g_stStreamedOutInfo.fPlayerPos[playerID][2] = sPos[2];
		}
	}
	return true;
}

// commands below

void cmd_change_server(char *param)	// 127.0.0.1 7777 Username Password
{
	traceLastFunc("cmd_change_server()");

	bool	success = false;

	char	IP[128], Nick[SAMP_MAX_PLAYER_NAME], Password[128] = "", Port[128];
	int		iPort;

	int ipc = sscanf(param, "%s%s%s%s", IP, Port, Nick, Password);
	if (ipc < 2)
	{
		addMessageToChatWindow("USAGE: /mod_change_server <ip> <port> <Username> <Server Password>");
		addMessageToChatWindow("Variables that are set to \"NULL\" (capitalized) will be ignored.");
		addMessageToChatWindow("If you set the Password to \"NULL\" it is set to <no server password>.");
		addMessageToChatWindow("Username and password can also be left out completely.");
		return;
	}
	if (stricmp(IP, "NULL") == NULL)
		strcpy(IP, g_SAMP->szIP);

	if (stricmp(Port, "NULL") == NULL)
		iPort = g_SAMP->ulPort;
	else
		iPort = atoi(Port);

	if (ipc > 2)
	{
		if (stricmp(Nick, "NULL") != NULL)
		{
			if (strlen(Nick) > SAMP_ALLOWED_PLAYER_NAME_LENGTH)
				Nick[SAMP_ALLOWED_PLAYER_NAME_LENGTH] = '\0';
			setLocalPlayerName(Nick);
		}
	}
	if (ipc > 3)
	{
		if (stricmp(Password, "NULL") == NULL)
			strcpy(Password, "");
	}

	changeServer(IP, iPort, Password);
}

void cmd_change_server_fav(char *param)
{
	traceLastFunc("cmd_change_server_fav()");

	if (strlen(param) == 0)
	{
		addMessageToChatWindow("/mod_fav_server <server name/part of server name>");
		addMessageToChatWindow("In order to see the favorite server list type: /mod_fav_server list");
		return;
	}

	if (strncmp(param, "list", 4) == 0)
	{
		int count = 0;
		for (int i = 0; i < INI_SERVERS_MAX; i++)
		{
			if (set.server[i].server_name == NULL)
				continue;

			count++;
			addMessageToChatWindow("%s", set.server[i].server_name);
		}
		if (count == 0)
			addMessageToChatWindow("No servers in favorite server list. Edit the ini file to add some.");
		return;
	}

	for (int i = 0; i < INI_SERVERS_MAX; i++)
	{
		if (set.server[i].server_name == NULL || set.server[i].ip == NULL
			|| strlen(set.server[i].ip) < 7 || set.server[i].port == 0)
			continue;

		if (!findstrinstr((char *)set.server[i].server_name, param))
			continue;

		if (!set.use_current_name)
			setLocalPlayerName(set.server[i].nickname);

		changeServer(set.server[i].ip, set.server[i].port, set.server[i].password);

		return;
	}

	addMessageToChatWindow("/mod_fav_server <server name/part of server name>");
	return;
}

void cmd_current_server(char *param)
{
	addMessageToChatWindow("Server Name: %s", g_SAMP->szHostname);
	addMessageToChatWindow("Server Address: %s:%i", g_SAMP->szIP, g_SAMP->ulPort);
	addMessageToChatWindow("Username: %s", getPlayerName(g_Players->sLocalPlayerID));
}

void cmd_tele_loc(char *param)
{
	if (strlen(param) == 0)
	{
		addMessageToChatWindow("USAGE: /mod_tele_loc <location name>");
		addMessageToChatWindow("Use /mod_tele_locations to show the location names.");
		addMessageToChatWindow("The more specific you are on location name the better the result.");
		return;
	}

	for (int i = 0; i < STATIC_TELEPORT_MAX; i++)
	{
		if (strlen(set.static_teleport_name[i]) == 0 || vect3_near_zero(set.static_teleport[i].pos))
			continue;

		if (!findstrinstr(set.static_teleport_name[i], param))
			continue;

		cheat_state_text("Teleported to: %s.", set.static_teleport_name[i]);
		cheat_teleport(set.static_teleport[i].pos, set.static_teleport[i].interior_id);
		return;
	}

	addMessageToChatWindow("USAGE: /mod_tele_loc <location name>");
	addMessageToChatWindow("Use /mod_tele_locations to show the location names.");
	addMessageToChatWindow("The more specific you are on location name the better the result.");
}

void cmd_tele_locations(char *)
{
	for (int i = 0; i < STATIC_TELEPORT_MAX; i++)
	{
		if (strlen(set.static_teleport_name[i]) == 0 || vect3_near_zero(set.static_teleport[i].pos))
			continue;
		addMessageToChatWindow("%s", set.static_teleport_name[i]);
	}

	addMessageToChatWindow("To teleport use the menu or: /mod_tele_loc <location name>");
}

void cmd_pickup(char *params)
{
	if (!strlen(params))
	{
		addMessageToChatWindow("USAGE: /mod_pickup <pickup id>");
		return;
	}

	g_RakClient->SendPickUp(atoi(params));
}

void cmd_setclass(char *params)
{
	if (!strlen(params))
	{
		addMessageToChatWindow("USAGE: /mod_setclass <class id>");
		return;
	}

	g_RakClient->RequestClass(atoi(params));
	g_RakClient->SendSpawn();
}

void cmd_fakekill(char *params)
{
	int killer, reason, amount;
	if (!strlen(params) || sscanf(params, "%d%d%d", &killer, &reason, &amount) < 3)
		return addMessageToChatWindow("USAGE: /mod_fakekill <killer id> <reason> <amount>");

	if (amount < 1 || killer < 0 || killer > SAMP_MAX_PLAYERS)
		return;

	for (int i = 0; i < amount; i++)
		g_RakClient->SendDeath(killer, reason);
}

void cmd_warp(char *params)
{
	if (params[0] == '\0')
		return addMessageToChatWindow("USAGE: /mod_warp <player id>");

	int playerid = atoi(params);
	if (isBadSAMPPlayerID(playerid) || g_Players->iIsListed[playerid] != 1)
		return addMessageToChatWindow("Player does not exist.");

	float pos[3];
	actor_info *actor = nullptr;
	if (g_Players->pRemotePlayer[playerid]->pPlayerData == nullptr
		|| g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == nullptr)
	{
		if (vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[playerid]))
			return addMessageToChatWindow("Player is not streamed in.");

		vect3_copy(g_stStreamedOutInfo.fPlayerPos[playerid], pos);
		pos[1] += 1.0f;
		cheat_teleport(pos, 0);
		return;
	}

	if (!getPlayerPos(playerid, pos) ||
		g_Players->pRemotePlayer[playerid]->pPlayerData == nullptr ||
		g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == nullptr ||
		(actor = g_Players->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTA_Ped) == nullptr)
	{
		return addMessageToChatWindow("Bad player info.");
	}

	pos[1] += 1.0f;
	cheat_teleport(pos, actor->base.interior_id);
}

void cmd_showCMDS(char *)
{
	for (int i = 0; i < g_m0dCmdNum; i++)
	{
		addMessageToChatWindow("%s", g_m0dCmdlist[i]);
	}
}

void initChatCmds(void)
{
	if (g_m0dCommands == true)
		return;

	cheat_state_text("initiated modcommands");
	g_m0dCommands = true;

	addClientCommand("mod_show_cmds", cmd_showCMDS);
	addClientCommand("mod_change_server", cmd_change_server);
	addClientCommand("mod_fav_server", cmd_change_server_fav);
	addClientCommand("mod_current_server", cmd_current_server);
	addClientCommand("mod_tele_loc", cmd_tele_loc);
	addClientCommand("mod_teleport_location", cmd_tele_loc);
	addClientCommand("mod_tele_locations", cmd_tele_locations);
	addClientCommand("mod_teleport_locations", cmd_tele_locations);
	addClientCommand("mod_pickup", cmd_pickup);
	addClientCommand("mod_setclass", cmd_setclass);
	addClientCommand("mod_fakekill", cmd_fakekill);
	addClientCommand("mod_warp", cmd_warp);
}
