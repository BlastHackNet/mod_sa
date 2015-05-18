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
#ifndef __MODMAIN_H
#define __MODMAIN_H

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS 1

#define M0D_FOLDER		"mod_sa\\"
#define M0D_NAME		"mod_sa"
#define M0D_VERSION		"4.4.0.2 by FYP // BlastHack.Net"
#define SAMP_VERSION	"SA:MP 0.3.7"
#define M0D_DEV_ADVANCEDINFO

// Use this to activate the SQLite Vehicle Recording.
// You'll need the SQLite libs. Check sqlite3/readme.txt for help.
//#define __CHEAT_VEHRECORDING_H__

#define BP _asm int 3
#define NAME ""M0D_NAME """ "M0D_VERSION ""

#define COMPILE_DT ""__DATE__" "__TIME__""
#define COMPILE_VERSION _MSC_VER

#define INI_FILE				"mod_sa.ini"
#define RAW_TEX_FILE			"mod_sa.raw"

#define RUNMODE_SINGLEPLAYER	0
#define RUNMODE_SAMP			1

// let's do a precompiled header, why not
#pragma message( "Compiling precompiled header.\n" )

// illegal instruction size
#pragma warning( disable : 4409 )

// 'class1' : inherits 'class2::member' via dominance
#pragma warning( disable : 4250 )

// unreferenced formal parameter
#pragma warning( disable : 4100 )

// handler not registered as safe handler
#pragma warning( disable : 4733 )

// API/SDK includes
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <shellapi.h>
#include <d3dx9.h>
#include <Gdiplus.h>
#include <assert.h>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <functional>

#include <intrin.h>
#pragma intrinsic(_ReturnAddress)

// typedefs/classes for legacy
#include "stddefs.h"
#include "stdtypes.h"
#include "CVector.h"
#include "CVector2D.h"
#include "CMatrix.h"
#include "CMatrix_Pad.h"

// public SA classes
// try to always include these in the private class's header
#include "SharedUtil.h"
#include <game/CGame.h>
#include <game/CWanted.h>

//#include <ijsify.h>
#include "SString.h"

// private SA classes
#include "CEntitySA.h"
#include "Common.h"
#include "CGameSA.h"
#include "CWorldSA.h"
#include "CPoolsSA.h"
#include "CClockSA.h"
#include "CFontSA.h"
#include "CRadarSA.h"
#include "CMenuManagerSA.h"
#include "CCameraSA.h"
#include "CCheckpointsSA.h"
#include "CRenderWareSA.h"
#include "CCoronasSA.h"
#include "CPickupsSA.h"
#include "CPathFindSA.h"
#include "CWeaponInfoSA.h"
#include "CExplosionManagerSA.h"
#include "CFireManagerSA.h"
#include "CHandlingManagerSA.h"
#include "CHudSA.h"
#include "C3DMarkersSA.h"
#include "CStatsSA.h"
#include "CTheCarGeneratorsSA.h"
#include "CPadSA.h"
#include "CAERadioTrackManagerSA.h"
#include "CWeatherSA.h"
#include "CTextSA.h"
#include "CPedSA.h"
#include "CPedSoundSA.h"
#include "CAudioSA.h"
#include "CPlayerInfoSA.h"
#include "CPopulationSA.h"
#include "CSettingsSA.h"
#include "CCarEnterExitSA.h"
#include "COffsets.h"
#include "CControllerConfigManagerSA.h"
#include "CProjectileInfoSA.h"
#include "CEventListSA.h"
#include "CGaragesSA.h"
#include "CTasksSA.h"
#include "CEventDamageSA.h"
#include "CEventGunShotSA.h"
#include "CEventGroupSA.h"
#include "CAnimManagerSA.h"
#include "CStreamingSA.h"
#include "CVisibilityPluginsSA.h"
#include "CKeyGenSA.h"
#include "CRopesSA.h"
#include "CFxSA.h"
#include "HookSystem.h"
#include "CModelInfoSA.h"
#include "CPedModelInfoSA.h"
#include "CColPointSA.h"
#include "CCivilianPedSA.h"
#include "CAnimBlendAssociationSA.h"
#include "CAnimBlendAssocGroupSA.h"
#include "CAnimBlendHierarchySA.h"
#include "CAnimBlendSequenceSA.h"
#include "CAnimBlendStaticAssociationSA.h"
#include "CAnimBlockSA.h"
#include "CAutomobileSA.h"
#include "CBikeSA.h"
#include "CBoatSA.h"
#include "CBmxSA.h"
#include "CQuadBikeSA.h"
#include "CMonsterTruckSA.h"
#include "CPlaneSA.h"
#include "CTrailerSA.h"
#include "CPlayerPedSA.h"
#include "CCivilianPedSA.h"
#include "CObjectSA.h"
#include "CBuildingSA.h"
#include "CRestartSA.h"
#include "CWaterManagerSA.h"
#include "CPedDamageResponseSA.h"
#include "CPedDamageResponseCalculatorSA.h"

// selected MTA class includes
#include "CDirect3DData.h"

// WDL includes
#include "mutex.h"

// RakNet stuff
#include "BitStream.h"
#include "RakClient.h"
#include "HookedRakClient.h"

// normal includes
#include "patcher.h"
#include "CDetour.h"
#include "cheat.h"
#include "ini.h"
#include "keyhook.h"
#include "math_stuff.h"
#include "cheat_patches.h"
#include "cheat_funcs.h"
#include "cheat_generic.h"
#include "cheat_actor.h"
#include "cheat_vehicle.h"
#include "cheat_hookers.h"
#ifdef __CHEAT_VEHRECORDING_H__
#include "sqlite3/sqlite3.h"
#include "cheat_vehRecording.h"
#endif
#include "dumb_menu.h"
#include "samp.h"
#include "cheat_samp.h"
#include "debug_classify.h"
#include "d3drender.h"
#include "GTAfuncs.h"
#include "proxyIDirect3D9.h"
#include "proxyIDirect3DDevice9.h"

// main.cpp functions
void							traceLastFunc ( const char *szFunc );
void							Log ( const char *fmt, ... );
void							LogChatbox ( bool bLast, const char *fmt, ... );
void							setDebugPointer ( void *ptr );

// externals
extern HMODULE					g_hDllModule;
extern char						g_szWorkingDirectory[MAX_PATH];
extern FILE						*g_flLog;
extern FILE						*g_flLogAll;
extern char						g_szLastFunc[256];
extern uint32_t					g_dwSAMP_Addr;
extern char						g_szSAMPVer[16];
extern CSettingsSAInterface		*g_pCSettingsSAInterface;
extern D3DPRESENT_PARAMETERS	*g_pGTAPresent;
extern RsGlobalType				*g_RsGlobal;
extern CCameraSA				g_CCamera;

// new MTA externals
extern CGameSA					*pGameInterface;
extern CPools					*pPools;
extern CPed						*pPedSelf;
extern CPedSAInterface			*pPedSelfSA;
extern CDirect3DData			*pD3DData;

// store info about Windows OS
extern t_WindowsInfo			WindowsInfo;

// externals
#endif
