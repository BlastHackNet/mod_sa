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

#define SAMP_DLL		"samp.dll"
#define SAMP_CMP		"F8036A004050518D4C24"


//randomStuff
extern int						iViewingInfoPlayer;
int								g_iCursorEnabled = 0;
char							g_m0dCmdlist[(SAMP_MAX_CLIENTCMDS - 22)][30];
int								g_m0dCmdNum = 0;
bool							g_m0dCommands = false;

// global samp pointers
int								iIsSAMPSupported = 0;
int								g_renderSAMP_initSAMPstructs = 0;
stSAMP							*g_SAMP = nullptr;
stPlayerPool					*g_Players = nullptr;
stVehiclePool					*g_Vehicles = nullptr;
stChatInfo						*g_Chat = nullptr;
stInputInfo						*g_Input = nullptr;
stKillInfo						*g_DeathList = nullptr;
stScoreboardInfo				*g_Scoreboard = nullptr;

// global managed support variables
stTranslateGTASAMP_vehiclePool	translateGTASAMP_vehiclePool;
stTranslateGTASAMP_pedPool		translateGTASAMP_pedPool;

stStreamedOutPlayerInfo			g_stStreamedOutInfo;



//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// FUNCTIONS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// update SAMPGTA vehicle translation structure
void update_translateGTASAMP_vehiclePool(void)
{
	traceLastFunc("update_translateGTASAMP_vehiclePool()");
	if (!g_Vehicles)
		return;

	int iGTAID;
	for (int i = 0; i <= SAMP_MAX_VEHICLES; i++)
	{
		if (g_Vehicles->iIsListed[i] != 1)
			continue;
		if (isBadPtr_writeAny(g_Vehicles->pSAMP_Vehicle[i], sizeof(stSAMPVehicle)))
			continue;
		iGTAID = getVehicleGTAIDFromInterface((DWORD *) g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle);
		if (iGTAID <= SAMP_MAX_VEHICLES && iGTAID >= 0)
		{
			translateGTASAMP_vehiclePool.iSAMPID[iGTAID] = i;
		}
	}
}

// update SAMPGTA ped translation structure
void update_translateGTASAMP_pedPool(void)
{
	traceLastFunc("update_translateGTASAMP_pedPool()");
	if (!g_Players)
		return;

	int iGTAID, i;
	for (i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (i == g_Players->sLocalPlayerID)
		{
			translateGTASAMP_pedPool.iSAMPID[0] = i;
			continue;
		}

		if (isBadPtr_writeAny(g_Players->pRemotePlayer[i], sizeof(stRemotePlayer)))
			continue;
		if (isBadPtr_writeAny(g_Players->pRemotePlayer[i]->pPlayerData, sizeof(stRemotePlayerData)))
			continue;
		if (isBadPtr_writeAny(g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor, sizeof(stSAMPPed)))
			continue;

		iGTAID = getPedGTAIDFromInterface((DWORD *) g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped);
		if (iGTAID <= SAMP_MAX_PLAYERS && iGTAID >= 0)
		{
			translateGTASAMP_pedPool.iSAMPID[iGTAID] = i;
		}
	}
}

void getSamp()
{
	if (set.basic_mode)
		return;

	uint32_t	samp_dll = getSampAddress();

	if (samp_dll != NULL)
	{
		g_dwSAMP_Addr = (uint32_t) samp_dll;

		if (g_dwSAMP_Addr != NULL)
		{
			if (memcmp_safe((uint8_t *) g_dwSAMP_Addr + 0xBABE, hex_to_bin(SAMP_CMP), 10))
			{
				strcpy(g_szSAMPVer, "SA:MP 0.3.7");
				Log("%s was detected. g_dwSAMP_Addr: 0x%p", g_szSAMPVer, g_dwSAMP_Addr);
				sampPatchDisableAnticheat();
				iIsSAMPSupported = 1;
			}
			else
			{
				Log("Unknown SA:MP version. Running in basic mode.");
				iIsSAMPSupported = 0;
				set.basic_mode = true;
				g_dwSAMP_Addr = NULL;
			}
		}
	}
	else
	{
		iIsSAMPSupported = 0;
		set.basic_mode = true;
		Log("samp.dll not found. Running in basic mode.");
	}

	return;
}

uint32_t getSampAddress()
{
	if (set.run_mode == RUNMODE_SINGLEPLAYER)
		return 0x0;

	uint32_t	samp_dll;
	if (set.run_mode == RUNMODE_SAMP)
	{
		if (set.wine_compatibility)
		{
			samp_dll = (uint32_t) LoadLibrary(SAMP_DLL);
		}
		else
		{
			samp_dll = (uint32_t) dll_baseptr_get(SAMP_DLL);
		}
	}
	return samp_dll;
}

template<typename T>
T GetSAMPPtrInfo(uint32_t offset)
{
	if (g_dwSAMP_Addr == NULL)
		return NULL;
	return *(T *)(g_dwSAMP_Addr + offset);
}

struct stSAMP *stGetSampInfo(void)
{
	return GetSAMPPtrInfo<stSAMP *>(SAMP_INFO_OFFSET);
}

struct stChatInfo *stGetSampChatInfo(void)
{
	return GetSAMPPtrInfo<stChatInfo *>(SAMP_CHAT_INFO_OFFSET);
}

struct stInputInfo *stGetInputInfo(void)
{
	return GetSAMPPtrInfo<stInputInfo *>(SAMP_CHAT_INPUT_INFO_OFFSET);
}

struct stKillInfo *stGetKillInfo(void)
{
	return GetSAMPPtrInfo<stKillInfo *>(SAMP_KILL_INFO_OFFSET);
}

struct stScoreboardInfo *stGetScoreboardInfo(void)
{
	return GetSAMPPtrInfo<stScoreboardInfo *>(SAMP_SCOREBOARD_INFO);
}

int isBadSAMPVehicleID(int iVehicleID)
{
	if (g_Vehicles == NULL || iVehicleID == (uint16_t) -1 || iVehicleID >= SAMP_MAX_VEHICLES)
		return 1;
	return !g_Vehicles->iIsListed[iVehicleID];
}

int isBadSAMPPlayerID(int iPlayerID)
{
	if (g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return 1;
	return !g_Players->iIsListed[iPlayerID];
}

D3DCOLOR samp_color_get(int id, DWORD trans)
{
	if (g_dwSAMP_Addr == NULL)
		return NULL;

	D3DCOLOR	*color_table;
	if (id < 0 || id >= (SAMP_MAX_PLAYERS + 3))
		return D3DCOLOR_ARGB(0xFF, 0x99, 0x99, 0x99);

	switch (id)
	{
		case (SAMP_MAX_PLAYERS) :
			return 0xFF888888;

		case (SAMP_MAX_PLAYERS + 1) :
			return 0xFF0000AA;

		case (SAMP_MAX_PLAYERS + 2) :
			return 0xFF63C0E2;
	}

	color_table = (D3DCOLOR *) ((uint8_t *) g_dwSAMP_Addr + SAMP_COLOR_OFFSET);
	return (color_table[id] >> 8) | trans;
}

int getNthPlayerID(int n)
{
	if (g_Players == NULL)
		return -1;

	int thisplayer = 0;
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (g_Players->iIsListed[i] != 1)
			continue;
		if (g_Players->sLocalPlayerID == i)
			continue;
		if (thisplayer < n)
		{
			thisplayer++;
			continue;
		}

		return i;
	}

	//shouldnt happen
	return -1;
}

int getPlayerCount(void)
{
	if (g_Players == NULL)
		return NULL;

	int iCount = 0;
	int i;

	for (i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (g_Players->iIsListed[i] != 1)
			continue;
		iCount++;
	}

	return iCount + 1;
}

int setLocalPlayerName(const char *name)
{
	if (g_Players == NULL || g_Players->pLocalPlayer == NULL)
		return 0;
	traceLastFunc("setLocalPlayerName()");

	int strlen_name = strlen(name);
	if (strlen_name == 0 || strlen_name > SAMP_ALLOWED_PLAYER_NAME_LENGTH)
		return 0;

	((void(__thiscall *) (void *, const char *name, int len)) (g_dwSAMP_Addr + SAMP_FUNC_NAMECHANGE)) (&g_Players->pVTBL_txtHandler, name, strlen_name);
	return 1;
}

int getVehicleCount(void)
{
	if (g_Vehicles == NULL)
		return NULL;

	int iCount = 0;
	int i;

	for (i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (g_Vehicles->iIsListed[i] != 1)
			continue;
		iCount++;
	}

	return iCount;
}

int getPlayerPos(int iPlayerID, float fPos[3])
{
	traceLastFunc("getPlayerPos()");

	struct actor_info	*pActor = NULL;
	struct vehicle_info *pVehicle = NULL;

	struct actor_info	*pSelfActor = actor_info_get(ACTOR_SELF, 0);

	if (g_Players == NULL)
		return 0;
	if (g_Players->iIsListed[iPlayerID] != 1)
		return 0;
	if (g_Players->pRemotePlayer[iPlayerID] == NULL)
		return 0;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return 0;

	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		return 0;	// not streamed
	else
	{
		pActor = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle != NULL)
			pVehicle = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle;

		if (pVehicle != NULL && pActor->vehicle == pVehicle && pVehicle->passengers[0] == pActor)
		{
			// driver of a vehicle
			vect3_copy(&pActor->vehicle->base.matrix[4 * 3], fPos);

			//vect3_copy(g_Players->pRemotePlayer[iPlayerID]->fVehiclePosition, fPos);
		}
		else if (pVehicle != NULL)
		{
			// passenger of a vehicle
			vect3_copy(&pActor->base.matrix[4 * 3], fPos);

			//vect3_copy(g_Players->pRemotePlayer[iPlayerID]->fActorPosition, fPos);
		}
		else
		{
			// on foot
			vect3_copy(&pActor->base.matrix[4 * 3], fPos);

			//vect3_copy(g_Players->pRemotePlayer[iPlayerID]->fActorPosition, fPos);
		}
	}

	if (pSelfActor != NULL)
	{
		if (vect3_dist(&pSelfActor->base.matrix[4 * 3], fPos) < 100.0f)
			vect3_copy(&pActor->base.matrix[4 * 3], fPos);
	}

	// detect zombies
	if (vect3_near_zero(fPos))
		vect3_copy(&pActor->base.matrix[4 * 3], fPos);

	return !vect3_near_zero(fPos);
}

const char *getPlayerName(int iPlayerID)
{
	if (g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return NULL;

	if (iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return NULL;

	if (iPlayerID == g_Players->sLocalPlayerID)
	{
		if (g_Players->iLocalPlayerNameAllocated <= 0xF)
			return g_Players->szLocalPlayerName;
		return g_Players->pszLocalPlayerName;
	}

	if (g_Players->pRemotePlayer[iPlayerID] == NULL)
		return NULL;

	if (g_Players->pRemotePlayer[iPlayerID]->iNameAllocated <= 0xF)
		return g_Players->pRemotePlayer[iPlayerID]->szPlayerName;

	return g_Players->pRemotePlayer[iPlayerID]->pszPlayerName;
}

int getPlayerState(int iPlayerID)
{
	if (g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return NULL;
	if (iPlayerID == g_Players->sLocalPlayerID)
		return NULL;
	if (g_Players->iIsListed[iPlayerID] != 1)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return NULL;

	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->bytePlayerState;
}

int getPlayerVehicleGTAScriptingID(int iPlayerID)
{
	if (g_Players == NULL)
		return 0;

	// fix to always return our own vehicle always if that's what's being asked for
	if (iPlayerID == ACTOR_SELF)
	{
		if (g_Players->pLocalPlayer->sCurrentVehicleID == (uint16_t) -1) return 0;

		stSAMPVehicle	*sampveh = g_Vehicles->pSAMP_Vehicle[g_Players->pLocalPlayer->sCurrentVehicleID];
		if (sampveh)
		{
			return ScriptCarId(sampveh->pGTA_Vehicle);
			//return (int)( ((DWORD) sampveh->pGTA_Vehicle) - (DWORD) pool_vehicle->start ) / 2584;
		}
		else
			return 0;
	}

	// make sure remote player is legit
	if (g_Players->pRemotePlayer[iPlayerID] == NULL || g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL ||
		g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle == NULL ||
		g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle == NULL)
		return 0;

	// make sure samp knows the vehicle exists
	if (g_Vehicles->pSAMP_Vehicle[g_Players->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID] == NULL)
		return 0;

	// return the remote player's vehicle
	return ScriptCarId(g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle);
}

int getPlayerSAMPVehicleID(int iPlayerID)
{
	if (g_Players == NULL && g_Vehicles == NULL) return 0;
	if (g_Players->pRemotePlayer[iPlayerID] == NULL) return 0;
	if (g_Vehicles->pSAMP_Vehicle[g_Players->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID] == NULL) return 0;
	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID;
}

struct actor_info *getGTAPedFromSAMPPlayerID(int iPlayerID)
{
	if (g_Players == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return NULL;
	if (iPlayerID == g_Players->sLocalPlayerID)
		return actor_info_get(ACTOR_SELF, 0);
	if (g_Players->iIsListed[iPlayerID] != 1)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID] == NULL)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
		return NULL;

	// return actor_info, null or otherwise
	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
}

struct vehicle_info *getGTAVehicleFromSAMPVehicleID(int iVehicleID)
{
	if (g_Vehicles == NULL || iVehicleID < 0 || iVehicleID >= SAMP_MAX_VEHICLES)
		return NULL;
	if (iVehicleID == g_Players->pLocalPlayer->sCurrentVehicleID)
		return vehicle_info_get(VEHICLE_SELF, 0);
	if (g_Vehicles->iIsListed[iVehicleID] != 1)
		return NULL;

	// return vehicle_info, null or otherwise
	return g_Vehicles->pGTA_Vehicle[iVehicleID];
}

int getSAMPPlayerIDFromGTAPed(struct actor_info *pGTAPed)
{
	if (g_Players == NULL)
		return 0;
	if (actor_info_get(ACTOR_SELF, 0) == pGTAPed)
		return g_Players->sLocalPlayerID;

	int i;
	for (i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (g_Players->iIsListed[i] != 1)
			continue;
		if (g_Players->pRemotePlayer[i] == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
			continue;
		if (g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped == pGTAPed)
			return i;
	}

	return ACTOR_SELF;
}

int getSAMPVehicleIDFromGTAVehicle(struct vehicle_info *pVehicle)
{
	if (g_Vehicles == NULL)
		return NULL;
	if (vehicle_info_get(VEHICLE_SELF, 0) == pVehicle && g_Players != NULL)
		return g_Players->pLocalPlayer->sCurrentVehicleID;

	int i, iReturn = 0;
	for (i = 0; i < SAMP_MAX_VEHICLES; i++)
	{
		if (g_Vehicles->iIsListed[i] != 1)
			continue;
		if (g_Vehicles->pGTA_Vehicle[i] == pVehicle)
			return i;
	}

	return VEHICLE_SELF;
}

uint32_t getPedGTAScriptingIDFromPlayerID(int iPlayerID)
{
	if (g_Players == NULL)
		return NULL;

	if (g_Players->iIsListed[iPlayerID] != 1)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID] == NULL)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return NULL;
	if (g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		return NULL;

	return g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->ulGTAEntityHandle;
}

uint32_t getVehicleGTAScriptingIDFromVehicleID(int iVehicleID)
{
	if (g_Vehicles == NULL)
		return NULL;

	if (g_Vehicles->iIsListed[iVehicleID] != 1)
		return NULL;
	if (g_Vehicles->pSAMP_Vehicle[iVehicleID] == NULL)
		return NULL;

	return g_Vehicles->pSAMP_Vehicle[iVehicleID]->ulGTAEntityHandle;
}

void addClientCommand(char *name, CMDPROC function)
{
	if (name == NULL || function == NULL || g_Input == NULL)
		return;

	if (g_Input->iCMDCount == (SAMP_MAX_CLIENTCMDS - 1))
	{
		Log("Error: couldn't initialize '%s'. Maximum command amount reached.", name);
		return;
	}

	if (strlen(name) > 30)
	{
		Log("Error: command name '%s' was too long.", name);
		return;
	}

	if (g_m0dCmdNum < (SAMP_MAX_CLIENTCMDS - 22))
	{
		strncpy_s(g_m0dCmdlist[g_m0dCmdNum], name, sizeof(g_m0dCmdlist[g_m0dCmdNum]) - 1);
		g_m0dCmdNum++;
	}
	else
		Log("m0d_cmd_list[] too short.");

	((void(__thiscall *) (void *_this, char *command, CMDPROC function)) (g_dwSAMP_Addr + SAMP_FUNC_ADDCLIENTCMD)) (g_Input, name, function);
}

struct gui	*gui_samp_cheat_state_text = &set.guiset[1];
void addMessageToChatWindow(const char *text, ...)
{
	if (g_SAMP != NULL)
	{
		va_list ap;
		if (text == NULL)
			return;

		char	tmp[512];
		memset(tmp, 0, 512);

		va_start(ap, text);
		vsnprintf(tmp, sizeof(tmp) - 1, text, ap);
		va_end(ap);

		addToChatWindow(tmp, D3DCOLOR_XRGB(gui_samp_cheat_state_text->red, gui_samp_cheat_state_text->green,
			gui_samp_cheat_state_text->blue));
	}
	else
	{
		va_list ap;
		if (text == NULL)
			return;

		char	tmp[512];
		memset(tmp, 0, 512);

		va_start(ap, text);
		vsnprintf(tmp, sizeof(tmp) - 1, text, ap);
		va_end(ap);

		cheat_state_text(tmp, D3DCOLOR_ARGB(255, 0, 200, 200));
	}
}

void addMessageToChatWindowSS(const char *text, ...)
{
	if (g_SAMP != NULL)
	{
		va_list ap;
		if (text == NULL)
			return;

		char	tmp[512];
		memset(tmp, 0, 512);

		va_start(ap, text);
		vsprintf(tmp, text, ap);
		va_end(ap);

		addMessageToChatWindow(tmp, D3DCOLOR_ARGB(255, 0, 200, 200));
	}
	else
	{
		va_list ap;
		if (text == NULL)
			return;

		char	tmp[512];
		memset(tmp, 0, 512);

		va_start(ap, text);
		vsprintf(tmp, text, ap);
		va_end(ap);

		cheat_state_text(tmp, D3DCOLOR_ARGB(255, 0, 200, 200));
	}
}

void addToChatWindow(char *text, D3DCOLOR textColor, int playerID)
{
	if (g_SAMP == NULL || g_Chat == NULL)
		return;

	if (text == NULL)
		return;

	if (playerID < -1)
		playerID = -1;

	void(__thiscall *AddToChatWindowBuffer) (void *, ChatMessageType, const char *, const char *, D3DCOLOR, D3DCOLOR) =
		(void(__thiscall *) (void *_this, ChatMessageType Type, const char *szString, const char *szPrefix, D3DCOLOR TextColor, D3DCOLOR PrefixColor))
		(g_dwSAMP_Addr + SAMP_FUNC_ADDTOCHATWND);

	if (playerID != -1)
	{
		// getPlayerName does the needed validity checks, no need for doubles
		char *playerName = (char*) getPlayerName(playerID);
		if (playerName == NULL)
			return;
		AddToChatWindowBuffer(g_Chat, CHAT_TYPE_CHAT, text, playerName, textColor, samp_color_get(playerID));
	}
	else
	{
		AddToChatWindowBuffer(g_Chat, CHAT_TYPE_DEBUG, text, nullptr, textColor, 0);
	}
}

void restartGame()
{
	if (g_SAMP == NULL)
		return;

	((void(__thiscall *) (void *)) (g_dwSAMP_Addr + SAMP_FUNC_RESTARTGAME)) (g_SAMP);
}

void say(char *text, ...)
{
	if (g_SAMP == NULL)
		return;

	if (text == NULL)
		return;
	if (isBadPtr_readAny(text, 128))
		return;
	traceLastFunc("say()");

	va_list ap;
	char	tmp[128];
	memset(tmp, 0, 128);

	va_start(ap, text);
	vsprintf(tmp, text, ap);
	va_end(ap);

	addSayToChatWindow(tmp);
}

void addSayToChatWindow(char *msg)
{
	if (g_SAMP == NULL)
		return;

	if (msg == NULL)
		return;
	if (isBadPtr_readAny(msg, 128))
		return;
	traceLastFunc("addSayToChatWindow()");

	if (msg == NULL)
		return;

	if (msg[0] == '/')
	{
		((void(__thiscall *) (void *_this, char *message)) (g_dwSAMP_Addr + SAMP_FUNC_SENDCMD))(g_Input, msg);
	}
	else
	{
		((void(__thiscall *) (void *_this, char *message)) (g_dwSAMP_Addr + SAMP_FUNC_SAY)) (g_Players->pLocalPlayer, msg);
	}
}

void playerSpawn(void)
{
	if (g_SAMP == NULL)
		return;

	((void(__thiscall *) (void *_this)) (g_dwSAMP_Addr + SAMP_FUNC_REQUEST_SPAWN)) (g_Players->pLocalPlayer);
	((void(__thiscall *) (void *_this)) (g_dwSAMP_Addr + SAMP_FUNC_SPAWN)) (g_Players->pLocalPlayer);
}

void disconnect(int reason /*0=timeout, 500=quit*/)
{
	if (g_SAMP == NULL)
		return;

	g_RakClient->GetInterface()->Disconnect(reason);
}

void setPassword(const char *password)
{
	if (g_SAMP == NULL)
		return;

	g_RakClient->GetInterface()->SetPassword(password);
}

void sendSetInterior(uint8_t interiorID)
{
	if (g_SAMP == NULL)
		return;

	((void(__thiscall *) (void *_this, byte interiorID)) (g_dwSAMP_Addr + SAMP_FUNC_SENDINTERIOR)) (g_Players->pLocalPlayer, interiorID);
}

void setSpecialAction(uint8_t byteSpecialAction)
{
	if (g_SAMP == NULL)
		return;

	if (g_Players->pLocalPlayer == NULL)
		return;

	((void(__thiscall *) (void *_this, byte specialActionId)) (g_dwSAMP_Addr + SAMP_FUNC_SETSPECIALACTION)) (g_Players->pLocalPlayer, byteSpecialAction);
}

void sendSCMEvent(int iEvent, int iVehicleID, int iParam1, int iParam2)
{
	g_RakClient->SendSCMEvent(iVehicleID, iEvent, iParam1, iParam2);
}

void toggleSAMPCursor(int iToggle)
{
	if (g_SAMP == NULL) return;
	if (g_Input->iInputEnabled) return;

	void		*obj = *(void **) (g_dwSAMP_Addr + SAMP_MISC_INFO);
	((void(__thiscall *) (void *, int, bool)) (g_dwSAMP_Addr + SAMP_FUNC_TOGGLECURSOR))(obj, iToggle ? 3 : 0, !iToggle);
	if (!iToggle)
		((void(__thiscall *) (void *)) (g_dwSAMP_Addr + SAMP_FUNC_CURSORUNLOCKACTORCAM))(obj);
	// g_iCursorEnabled = iToggle;
}

void sendDeath(void)
{
	if (g_SAMP == NULL)
		return;
	((void(__thiscall *) (void *)) (g_dwSAMP_Addr + SAMP_FUNC_DEATH))
		(g_Players->pLocalPlayer);
}

void changeServer(const char *pszIp, unsigned ulPort, const char *pszPassword)
{
	if (!g_SAMP)
		return;

	((void(__cdecl *)(unsigned))(g_dwSAMP_Addr + SAMP_FUNC_ENCRYPT_PORT))(ulPort);

	disconnect(500);
	strcpy(g_SAMP->szIP, pszIp);
	g_SAMP->ulPort = ulPort;
	setPassword(pszPassword);
	g_iJoiningServer = 1;
}

void updateScoreboardData(void)
{
	((void(__thiscall *) (void *_this)) (g_dwSAMP_Addr + SAMP_FUNC_UPDATESCOREBOARDDATA)) (g_SAMP);
}

void setSAMPCustomSendRates(int iOnFoot, int iInCar, int iAim, int iHeadSync)
{
	if (!set.samp_custom_sendrates_enable)
		return;
	if (g_dwSAMP_Addr == NULL)
		return;
	if (g_SAMP == NULL)
		return;

	memcpy_safe((void *) (g_dwSAMP_Addr + SAMP_ONFOOTSENDRATE), &iOnFoot, sizeof(int));
	memcpy_safe((void *) (g_dwSAMP_Addr + SAMP_INCARSENDRATE), &iInCar, sizeof(int));
	memcpy_safe((void *) (g_dwSAMP_Addr + SAMP_AIMSENDRATE), &iAim, sizeof(int));
}

int sampPatchDisableNameTags(int iEnabled)
{
	static struct patch_set sampPatchEnableNameTags_patch =
	{
		"Remove player status",
		0,
		0,
		{
			{ 1, (void *) ((uint8_t *) g_dwSAMP_Addr + SAMP_PATCH_DISABLE_NAMETAGS), NULL, (uint8_t *)"\xC3", NULL },
			{ 1, (void *) ((uint8_t *) g_dwSAMP_Addr + SAMP_PATCH_DISABLE_NAMETAGS_HP), NULL, (uint8_t *)"\xC3", NULL }
		}
	};
	if (iEnabled && !sampPatchEnableNameTags_patch.installed)
		return patcher_install(&sampPatchEnableNameTags_patch);
	else if (!iEnabled && sampPatchEnableNameTags_patch.installed)
		return patcher_remove(&sampPatchEnableNameTags_patch);
	return NULL;
}

int sampPatchDisableInteriorUpdate(int iEnabled)
{
	static struct patch_set sampPatchDisableInteriorUpdate_patch =
	{
		"NOP sendinterior",
		0,
		0,
		{
			{ 1, (void *) ((uint8_t *) g_dwSAMP_Addr + SAMP_PATCH_SKIPSENDINTERIOR), NULL, (uint8_t *)"\xEB", NULL }
		}
	};

	if (iEnabled && !sampPatchDisableInteriorUpdate_patch.installed)
		return patcher_install(&sampPatchDisableInteriorUpdate_patch);
	else if (!iEnabled && sampPatchDisableInteriorUpdate_patch.installed)
		return patcher_remove(&sampPatchDisableInteriorUpdate_patch);
	return NULL;
}

int sampPatchDisableScoreboardToggleOn(int iEnabled)
{
	static struct patch_set sampPatchDisableScoreboard_patch =
	{
		"NOP Scoreboard Functions",
		0,
		0,
		{
			{ 1, (void *) ((uint8_t *) g_dwSAMP_Addr + SAMP_PATCH_SCOREBOARDTOGGLEON), NULL, (uint8_t *)"\xC3", NULL },
			{ 1, (void *) ((uint8_t *) g_dwSAMP_Addr + SAMP_PATCH_SCOREBOARDTOGGLEONKEYLOCK), NULL, (uint8_t *)"\xC3", NULL }
		}
	};
	if (iEnabled && !sampPatchDisableScoreboard_patch.installed)
		return patcher_install(&sampPatchDisableScoreboard_patch);
	else if (!iEnabled && sampPatchDisableScoreboard_patch.installed)
		return patcher_remove(&sampPatchDisableScoreboard_patch);
	return NULL;
}

int sampPatchDisableChatInputAdjust(int iEnabled)
{
	static struct patch_set sampPatchDisableChatInputAdj_patch =
	{
		"NOP Adjust Chat input box",
		0,
		0,
		{
			{ 6, (void *) ((uint8_t *) g_dwSAMP_Addr + SAMP_PATCH_CHATINPUTADJUST_Y), NULL, (uint8_t *)"\x90\x90\x90\x90\x90\x90", NULL },
			{ 7, (void *) ((uint8_t *) g_dwSAMP_Addr + SAMP_PATCH_CHATINPUTADJUST_X), NULL, (uint8_t *)"\x90\x90\x90\x90\x90\x90\x90", NULL }
		}
	};
	if (iEnabled && !sampPatchDisableChatInputAdj_patch.installed)
		return patcher_install(&sampPatchDisableChatInputAdj_patch);
	else if (!iEnabled && sampPatchDisableChatInputAdj_patch.installed)
		return patcher_remove(&sampPatchDisableChatInputAdj_patch);
	return NULL;
}

void sampPatchDisableAnticheat(void)
{
	struct patch_set fuckAC =
	{
		"kyenub patch", 0, 0,
		{
			{ 1, (void *) (g_dwSAMP_Addr + 0x99250), NULL, (uint8_t *)"\xC3", 0 },
			{ 8, (void *) (g_dwSAMP_Addr + 0xB2F70), NULL, (uint8_t *)"\xB8\x45\x00\x00\x00\xC2\x1C\x00", 0 },
			{ 6, (void *) (g_dwSAMP_Addr + 0xB30F0), NULL, (uint8_t *)"\xB8\x01\x00\x00\x00\xC3", 0 }
		}
	};
	patcher_install(&fuckAC);
}

uint16_t	anticarjacked_vehid;
DWORD		anticarjacked_ebx_backup;
DWORD		anticarjacked_jmp;
uint8_t _declspec (naked) carjacked_hook(void)
{
	__asm mov anticarjacked_ebx_backup, ebx
	__asm mov ebx, [ebx + 7]
		__asm mov anticarjacked_vehid, bx
	__asm pushad
	cheat_state->_generic.anti_carjackTick = GetTickCount();
	cheat_state->_generic.car_jacked = true;

	if (g_Vehicles != NULL && g_Vehicles->pGTA_Vehicle[anticarjacked_vehid] != NULL)
		vect3_copy(&g_Vehicles->pGTA_Vehicle[anticarjacked_vehid]->base.matrix[4 * 3],
		cheat_state->_generic.car_jacked_lastPos);

	__asm popad
	__asm mov ebx, g_dwSAMP_Addr
	__asm add ebx, SAMP_HOOKEXIT_ANTICARJACK
	__asm mov anticarjacked_jmp, ebx
	__asm xor ebx, ebx
	__asm mov ebx, anticarjacked_ebx_backup
	__asm jmp anticarjacked_jmp
}

uint8_t _declspec (naked) hook_handle_rpc_packet(void)
{
	static RPCParameters *pRPCParams = nullptr;
	static RPCNode *pRPCNode = nullptr;
	static DWORD dwTmp = 0;

	__asm pushad;
	__asm mov pRPCParams, eax;
	__asm mov pRPCNode, edi;

	HandleRPCPacketFunc(pRPCNode->uniqueIdentifier, pRPCParams, pRPCNode->staticFunctionPointer);
	dwTmp = g_dwSAMP_Addr + SAMP_HOOKEXIT_HANDLE_RPC;

	__asm popad;
	__asm add esp, 4 // overwritten code
	__asm jmp dwTmp;
}

uint8_t _declspec (naked) hook_handle_rpc_packet2(void)
{
	static RPCParameters *pRPCParams = nullptr;
	static RPCNode *pRPCNode = nullptr;
	static DWORD dwTmp = 0;

	__asm pushad;
	__asm mov pRPCParams, ecx;
	__asm mov pRPCNode, edi;

	HandleRPCPacketFunc(pRPCNode->uniqueIdentifier, pRPCParams, pRPCNode->staticFunctionPointer);
	dwTmp = g_dwSAMP_Addr + SAMP_HOOKEXIT_HANDLE_RPC2;

	__asm popad;
	__asm jmp dwTmp;
}

void __stdcall CNetGame__destructor(void)
{
	// release hooked rakclientinterface, restore original rakclientinterface address and call CNetGame destructor
	if (g_SAMP->pRakClientInterface != NULL)
		delete g_SAMP->pRakClientInterface;
	g_SAMP->pRakClientInterface = g_RakClient->GetInterface();
	return ((void(__thiscall *) (void *)) (g_dwSAMP_Addr + SAMP_FUNC_CNETGAMEDESTRUCTOR))(g_SAMP);
}

void SetupSAMPHook(char *szName, DWORD dwFuncOffset, void *Func, int iType, int iSize, char *szCompareBytes)
{
	CDetour api;
	int strl = strlen(szCompareBytes);
	uint8_t *bytes = hex_to_bin(szCompareBytes);

	if (!strl || !bytes || memcmp_safe((uint8_t *) g_dwSAMP_Addr + dwFuncOffset, bytes, strl / 2))
	{
		if (api.Create((uint8_t *) ((uint32_t) g_dwSAMP_Addr) + dwFuncOffset, (uint8_t *) Func, iType, iSize) == 0)
			Log("Failed to hook %s.", szName);
	}
	else
	{
		Log("Failed to hook %s (memcmp)", szName);
	}

	if (bytes)
		free(bytes);
}

void installSAMPHooks()
{
	if (g_SAMP == NULL)
		return;

	if (set.anti_carjacking)
		SetupSAMPHook("AntiCarJack", SAMP_HOOKENTER_STATECHANGE, carjacked_hook, DETOUR_TYPE_JMP, 5, "6A0568E8");
	SetupSAMPHook("HandleRPCPacket", SAMP_HOOKENTER_HANDLE_RPC, hook_handle_rpc_packet, DETOUR_TYPE_JMP, 6, "FF5701");
	SetupSAMPHook("HandleRPCPacket2", SAMP_HOOKENTER_HANDLE_RPC2, hook_handle_rpc_packet2, DETOUR_TYPE_JMP, 8, "FF5701");
	SetupSAMPHook("CNETGAMEDESTR1", SAMP_HOOKENTER_CNETGAME_DESTR, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
	SetupSAMPHook("CNETGAMEDESTR2", SAMP_HOOKENTER_CNETGAME_DESTR2, CNetGame__destructor, DETOUR_TYPE_CALL_FUNC, 5, "E8");
}
