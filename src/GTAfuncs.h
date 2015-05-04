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
// model functions
#define ARRAY_ModelLoaded				0x8E4CD0
#define ARRAY_ModelInfo					0xA9B0C8
#define FUNC_CStreaming__HasModelLoaded 0x4044C0
#define FUNC_GetModelFlags				0x4044E0
#define FUNC_GetBoundingBox				0x4082F0
#define FUNC_RequestModel				0x4087e0
#define FUNC_RemoveModel				0x4089a0
#define FUNC_LoadAllRequestedModels		0x40ea10
#define FUNC_FlushRequestList			0x40E4E0

// vehicle functions
#define FUNC_IsBoatModel				0x4c5a70
#define FUNC_IsCarModel					0x4c5aa0
#define FUNC_IsTrainModel				0x4c5ad0
#define FUNC_IsHeliModel				0x4c5b00
#define FUNC_IsPlaneModel				0x4c5b30
#define FUNC_IsBikeModel				0x4c5b60
#define FUNC_IsFakePlaneModel			0x4c5b90
#define FUNC_IsMonsterTruckModel		0x4c5bc0
#define FUNC_IsQuadBikeModel			0x4c5bf0
#define FUNC_IsBmxModel					0x4c5c20
#define FUNC_IsTrailerModel				0x4c5c50
#define FUNC_IsVehicleModelType			0x4c5c80
#define FUNC_HasVehicleUpgradeLoaded	0x407820
#define FUNC_RequestMyVehicleUpgrade	0x408C70
#define FUNC_RequestAnyVehicleUpgrade	0x6E3290

//#define		FUNC_CVehicle__SetRemapTexDictionary 0x6D0BC0
#define FUNC_CVehicle__GetRemapIndex	0x6D0B70
#define FUNC_CVehicle__SetRemap			0x6D0C00

// new vehicle functions
#define FUNC_CVehicle_IsUpsideDown			0x6D1D90
#define FUNC_CVehicle_IsOnItsSide			0x6D1DD0
#define FUNC_CVehicle_RecalcOnRailDistance	0x6F6CC0

// VideoMode functions
#define GFUNC_SetCurrentVideoMode	0x745C70
#define GFUNC_GetCurrentVideoMode	0x7F2D20
#define GFUNC_GetNumVideoModes		0x7F2CC0
#define GFUNC_GetVideoModeInfo		0x7F2CF0
#define FUNC_RwD3D9ChangeVideoMode	0x7F8640

// entity gravity/movement functions
#define FUNC_GetMoveSpeed	0x404460

// CWorld functions
#define FUNC_IsLineOfSightClear 0x56A490	// ##SA##
#define FUNC_ProcessLineOfSight 0x56BA00	// ##SA##

// gta class addresses
#define CLASS_CMenuManager	0xBA6748

////////////////////////

// structures & enums //
////////////////////////
struct RsInputDevice
{
	DWORD	inputDeviceType;
	DWORD	used;
	DWORD	*inputEventHandler;		// typedef RsEventStatus (*RsInputEventHandler)(RsEvent event, void *param);
};

struct PsGlobalType
{
	DWORD	window;
	DWORD	instance;
	int		fullscreen;
	DWORD	lastMousePos_X;
	DWORD	lastMousePos_Y;
	DWORD	__unknown_h14;
	DWORD	diInterface;
	DWORD	diMouse;
	DWORD	diDevice1;
	DWORD	diDevice2;
};

struct RsGlobalType
{
	DWORD			AppName;		// 0x0
	int				MaximumWidth;	// 0x4
	int				MaximumHeight;	// 0x8
	int				frameLimit;		// 0xC // (use with WM_ACTIVATE?)
	DWORD			quit;			// 0x10
	PsGlobalType	*ps;			// 0x14
	RsInputDevice	keyboard;		// 0x18
	RsInputDevice	mouse;			// 0x24
	RsInputDevice	pad;			// 0x30
};

//////////////
// GTAfuncs //
//////////////
// model funcs
int			GTAfunc_isModelLoaded ( int iModelID );
void		GTAfunc_requestModelLoad ( int iModelID );
void		GTAfunc_loadRequestedModels ( void );
bool		GTAfunc_vehicle_iModelID_IsValid ( int iModelID );
bool		GTAfunc_vehicle_iModelID_IsCar ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsBike ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsPlane ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsHeli ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsBoat ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsQuadBike ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsBmx ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsMonsterTruck ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsTrailer ( int m_dwModelID );
bool		GTAfunc_vehicle_iModelID_IsTrain ( int m_dwModelID );

// vehicle mod funcs
bool		GTAfunc_IsUpgradeAvailable ( int m_dwModelID, eVehicleUpgradePosn posn );
void		GTAfunc_requestAnyVehicleUpgrade ( vehicle_info *vinfo, int iModelID );
void		GTAfunc_removeVehicleUpgrade ( vehicle_info *vinfo, int iModelID );
int			GTAfunc_vehicle_getRemapIndex ( vehicle_info *vinfo );
void		GTAfunc_vehicle_setRemap ( vehicle_info *vinfo, int iRemap );

// vehicle position functions
bool		GTAfunc_IsUpsideDown ( vehicle_info *vinfo );
bool		GTAfunc_IsOnItsSide ( vehicle_info *vinfo );

// game core funcs
int			GTAfunc_getNumVideoModes ( void );
VideoMode	*GTAfunc_getVideoModeInfo ( VideoMode *modeInfo, int modeIndex );
int			GTAfunc_getCurrentVideoMode ( void );
void		GTAfunc_setCurrentVideoMode ( int modeIndex );
int			GTAfunc_RwD3D9ChangeVideoMode ( int modeIndex );

// gravity functions
CVector		GTAfunc_GetMoveSpeed ( object_base *entity );
VOID		GTAfunc_SetMoveSpeed ( object_base *vinfo, CVector vecMoveSpeed );

// CWorld functions
bool		GTAfunc_IsLineOfSightClear ( CVector *vecStart, CVector *vecEnd, bool bCheckBuildings, bool bCheckVehicles,
										 bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
										 bool bIgnoreSomeObjectsForCamera );
bool		GTAfunc_ProcessLineOfSight ( CVector *vecStart, CVector *vecEnd, CColPoint **colCollision,
										 CEntitySAInterface **CollisionEntity, bool bCheckBuildings, bool bCheckVehicles,
										 bool bCheckPeds, bool bCheckObjects, bool bCheckDummies, bool bSeeThroughStuff,
										 bool bIgnoreSomeObjectsForCamera, bool bShootThroughStuff );
void GTAfunc_TogglePlayerControllable(bool boolSafe);
void GTAfunc_LockActor(bool boolLock);
void GTAfunc_PutActorInCar(vehicle_info *vehicle);
void GTAfunc_PutActorInCarAsPassenger(vehicle_info *vehicle, int iSeat);
void GTAfunc_RemoveActorFromCarAndPutAt(float fPos[3]);
void GTAfunc_EnterCarAsDriver(vehicle_info *vehicle);
void GTAfunc_RepairVehicle(vehicle_info *vehicle);
void GTAfunc_CameraOnActor(actor_info *actor);
void GTAfunc_CameraOnVehicle(vehicle_info *vehicle);
void GTAfunc_PerformAnimation(const char *szBlockName, const char *szAnimName, int iTime, bool bLoop,
							  bool bUpdatePosition, bool bInterruptable, bool bFreezeLastFrame, bool bRunInSequence, bool bOffsetPed, bool bHoldLastFrame);
void GTAfunc_DisembarkInstantly();
void GTAfunc_ApplyRotoryPulseAboutAnAxis(float fX, float fY, float fZ);
void GTAfunc_showStyledText( const char *text, int time, int style );
int GTAfunc_gtaKeyToVirtualKey(int key);