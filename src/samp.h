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

#define SAMP_CHAT_INFO_OFFSET						0x26EB80
#define SAMP_CHAT_INPUT_INFO_OFFSET					0x26EB84
#define SAMP_KILL_INFO_OFFSET						0x26EB88
#define SAMP_INFO_OFFSET							0x26EB94
#define SAMP_MISC_INFO								0x26EBAC
#define SAMP_SCOREBOARD_INFO						0x26EB4C
#define SAMP_COLOR_OFFSET							0x151828
#define SAMP_DRAWING_DISTANCE						0xE60A0

#define SAMP_DRAWTEXTLABELS							0x75A70
#define SAMP_ONFOOTSENDRATE							0xFE0A8
#define SAMP_INCARSENDRATE							0xFE0AC
#define SAMP_AIMSENDRATE							0xFE0B0

#define SAMP_FUNC_ADDTOCHATWND						0x67BE0
#define SAMP_FUNC_SPAWN								0x3C20
#define SAMP_FUNC_REQUEST_SPAWN						0x4060
#define SAMP_FUNC_REQUEST_CLASS						0x58D0
#define SAMP_FUNC_DEATH								0x5810
#define SAMP_FUNC_SETSPECIALACTION					0x30F0
#define SAMP_FUNC_SAY								0x5A10
#define SAMP_FUNC_SENDCMD							0x69900
#define SAMP_FUNC_ADDCLIENTCMD						0x69770
#define SAMP_FUNC_NAMECHANGE						0xB6C0
#define SAMP_FUNC_RESTARTGAME						0xA540
#define SAMP_FUNC_ENCRYPT_PORT						0x1F710
#define SAMP_FUNC_TOGGLECURSOR						0xA06F0
#define SAMP_FUNC_CURSORUNLOCKACTORCAM				0xA05D0
#define SAMP_FUNC_UPDATESCOREBOARDDATA				0x8F10
#define SAMP_FUNC_CNETGAMEDESTRUCTOR				0x9880
#define SAMP_FUNC_SENDINTERIOR						0x5970
#define SAMP_FUNC_DISABLE_SCOREBOARD				0x6E9E0

#define SAMP_HOOKENTER_STATECHANGE					0x1630D
#define SAMP_HOOKENTER_HANDLE_RPC					0x3AF2D
#define SAMP_HOOKENTER_HANDLE_RPC2					0x3AEB9
#define SAMP_HOOKENTER_CNETGAME_DESTR				0xC3E63
#define SAMP_HOOKENTER_CNETGAME_DESTR2				0xC5076
#define SAMP_HOOKEXIT_ANTICARJACK					0x1631E
#define SAMP_HOOKEXIT_HANDLE_RPC					0x3AF33
#define SAMP_HOOKEXIT_HANDLE_RPC2					0x3AF41

#define SAMP_PATCH_DISABLE_NAMETAGS					0x75330
#define SAMP_PATCH_DISABLE_NAMETAGS_HP				0x74210
#define SAMP_PATCH_SKIPSENDINTERIOR					0x797F
#define SAMP_PATCH_SCOREBOARDTOGGLEON				0x6F0B0
#define SAMP_PATCH_SCOREBOARDTOGGLEONKEYLOCK		0x6F3D0
#define SAMP_PATCH_CHATINPUTADJUST_Y				0x67BB6
#define SAMP_PATCH_CHATINPUTADJUST_X				0x694F5

enum DialogStyle
{
	DIALOG_STYLE_MSGBOX,
	DIALOG_STYLE_INPUT,
	DIALOG_STYLE_LIST,
	DIALOG_STYLE_PASSWORD,
	DIALOG_STYLE_TABLIST,
	DIALOG_STYLE_TABLIST_HEADERS
};

enum Limits
{
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 1000,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
	SAMP_MAX_MAPICONS = 100,
};

enum ChatMessageType
{
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 2,
	CHAT_TYPE_INFO = 4,
	CHAT_TYPE_DEBUG = 8
};

enum ChatDisplayMode
{
	CHAT_WINDOW_MODE_OFF = 0,
	CHAT_WINDOW_MODE_LIGHT = 1,
	CHAT_WINDOW_MODE_FULL = 2
};

enum Gamestate
{
	GAMESTATE_WAIT_CONNECT = 9,
	GAMESTATE_CONNECTING = 13,
	GAMESTATE_AWAIT_JOIN = 15,
	GAMESTATE_CONNECTED = 14,
	GAMESTATE_RESTARTING = 18
};

enum PlayerState
{
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_ONFOOT = 17,
	PLAYER_STATE_PASSENGER,
	PLAYER_STATE_DRIVER,
	PLAYER_STATE_WASTED = 32,
	PLAYER_STATE_SPAWNED
};

enum MarkersMode
{
	PLAYER_MARKERS_MODE_OFF,
	PLAYER_MARKERS_MODE_GLOBAL,
	PLAYER_MARKERS_MODE_STREAMED,
};

enum SpecialAction
{
	SPECIAL_ACTION_NONE,
	SPECIAL_ACTION_DUCK,
	SPECIAL_ACTION_USEJETPACK,
	SPECIAL_ACTION_ENTER_VEHICLE,
	SPECIAL_ACTION_EXIT_VEHICLE,
	SPECIAL_ACTION_DANCE1,
	SPECIAL_ACTION_DANCE2,
	SPECIAL_ACTION_DANCE3,
	SPECIAL_ACTION_DANCE4,
	SPECIAL_ACTION_HANDSUP,
	SPECIAL_ACTION_USECELLPHONE,
	SPECIAL_ACTION_SITTING,
	SPECIAL_ACTION_STOPUSECELLPHONE,
	SPECIAL_ACTION_DRINK_BEER = 20,
	SPECIAL_ACTION_SMOKE_CIGGY,
	SPECIAL_ACTION_DRINK_WINE,
	SPECIAL_ACTION_DRINK_SPRUNK,
	SPECIAL_ACTION_CUFFED,
	SPECIAL_ACTION_CARRY,
};


//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// SAMP STRUCTURES ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)
struct stSAMPPools
{
	struct stVehiclePool* pVehicle;
	struct stPlayerPool* pPlayer;
	struct stPickupPool* pPickup;
	struct stObjectPool* pObject;
	struct stActorPool* pActor;
	struct stGangzonePool* pGangzone;
	struct stTextLabelPool* pText3D;
	struct stTextdrawPool* pTextdraw;
	void* pMenu;
};

struct stSAMP
{
	void* pRakClientInterface;
	uint8_t                  	_pad0[20];
	void* pUnk0;
	struct stServerInfo* pServerInfo;
	uint8_t				_pad1[16];
	char				szIP[256 + 1];
	char				szHostname[256 + 1];
	uint8_t                 	_pad2;
	bool                    	m_bUpdateCameraTarget;
	bool				m_bNoNameTagStatus;
	uint32_t			ulPort;
	BOOL				m_bLanMode;
	uint32_t			ulMapIcons[SAMP_MAX_MAPICONS];
	Gamestate			iGameState;
	uint32_t			ulConnectTick;
	struct stServerPresets* pSettings;
	uint8_t                 	_pad3[5];
	struct stSAMPPools* pPools;
};

struct stServerInfo {
	uint32_t 			uiIP;
	uint16_t 			usPort;

	// ...

};

struct stServerPresets
{
	uint8_t byteCJWalk;
	int m_iDeathDropMoney;
	float	fWorldBoundaries[4];
	bool m_bAllowWeapons;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint32_t ulVehicleFriendlyFire;
	bool m_byteHoldTime;
	bool m_bInstagib;
	bool m_bZoneNames;
	bool m_byteFriendlyFire;
	int		iClassesAvailable;
	float	fNameTagsDistance;
	bool m_bManualVehicleEngineAndLight;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t byteNoNametagsBehindWalls;
	int iPlayerMarkersMode;
	float	fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
	bool m_bLimitGlobalChatRadius;
};



struct stDialogInfo
{
	IDirect3DDevice9* m_pD3DDevice;
	int	iTextPoxX;
	int	iTextPoxY;
	uint32_t	uiDialogSizeX;
	uint32_t	uiDialogSizeY;
	int	iBtnOffsetX;
	int	iBtnOffsetY;
	class _CDXUTDialog* pDialog;
	class _CDXUTListBox* pList;
	class _CDXUTIMEEditBox* pEditBox;
	int	iIsActive;
	int	iType;
	uint32_t	DialogID;
	char* pText;
	uint32_t	uiTextWidth;
	uint32_t	uiTextHeight;
	char		szCaption[65];
	int		bServerside;
};

struct stTextDrawTransmit
{
	union
	{
		BYTE byteFlags;
		struct
		{
			BYTE byteBox : 1;
			BYTE byteLeft : 1;
			BYTE byteRight : 1;
			BYTE byteCenter : 1;
			BYTE byteProportional : 1;
			BYTE bytePadding : 3;
		};
	};
	float fLetterWidth;
	float fLetterHeight;
	DWORD dwLetterColor;
	float fBoxWidth;
	float fBoxHeight;
	DWORD dwBoxColor;
	BYTE byteShadow;
	BYTE byteOutline;
	DWORD dwBackgroundColor;
	BYTE byteStyle;
	BYTE byteUNK;
	float fX;
	float fY;
	uint16_t sModel;
	float fRot[3];
	float fZoom;
	WORD sColor[2];
};

struct stTextdraw
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct stTextdrawPool
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw* textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw* playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};

struct stPickup
{
	int		iModelID;
	int		iType;
	float	fPosition[3];
};

struct stPickupPool
{
	int				iPickupsCount;
	uint32_t		ul_GTA_PickupID[SAMP_MAX_PICKUPS];
	int				iPickupID[SAMP_MAX_PICKUPS];
	int				iTimePickup[SAMP_MAX_PICKUPS];
	uint8_t			unk[SAMP_MAX_PICKUPS * 3];
	struct stPickup pickup[SAMP_MAX_PICKUPS];
};

struct stPlayerPool
{
	//uint32_t				ulMaxPlayerID;
	int						iLocalPlayerScore;
	uint16_t				sLocalPlayerID;
	void* pVTBL_txtHandler;
	std::string				strLocalPlayerName;
	int						iLocalPlayerPing;
	struct stLocalPlayer* pLocalPlayer;
	int						iIsListed[SAMP_MAX_PLAYERS];
	BOOL					bSavedCheckCollision[SAMP_MAX_PLAYERS];
	struct stRemotePlayer* pRemotePlayer[SAMP_MAX_PLAYERS];
	int						largestID;
};

struct stSAMPKeys
{
	uint8_t keys_primaryFire : 1;
	uint8_t keys_horn__crouch : 1;
	uint8_t keys_secondaryFire__shoot : 1;
	uint8_t keys_accel__zoomOut : 1;
	uint8_t keys_enterExitCar : 1;
	uint8_t keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t keys_circleRight : 1;
	uint8_t keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t keys_circleLeft : 1;
	uint8_t keys_landingGear__lookback : 1;
	uint8_t keys_unknown__walkSlow : 1;
	uint8_t keys_specialCtrlUp : 1;
	uint8_t keys_specialCtrlDown : 1;
	uint8_t keys_specialCtrlLeft : 1;
	uint8_t keys_specialCtrlRight : 1;
	uint8_t keys__unused : 1;
};

struct stOnFootData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fPosition[3];
	float		fQuaternion[4];
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSpecialAction;
	float		fMoveSpeed[3];
	float		fSurfingOffsets[3];
	uint16_t	sSurfingVehicleID;
	short		sCurrentAnimationID;
	short		sAnimFlags;
};

struct stInCarData
{
	uint16_t	sVehicleID;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float		fQuaternion[4];
	float		fPosition[3];
	float		fMoveSpeed[3];
	float		fVehicleHealth;
	uint8_t		bytePlayerHealth;
	uint8_t		byteArmor;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteSiren;
	uint8_t		byteLandingGearState;
	uint16_t	sTrailerID;
	union
	{
		uint16_t	HydraThrustAngle[2];	//nearly same value
		float		fTrainSpeed;
		float       fBikeSideAngle;
	};
};

struct stAimData
{
	BYTE	byteCamMode;
	float	vecAimf1[3];
	float	vecAimPos[3];
	float	fAimZ;
	BYTE	byteCamExtZoom : 6;		// 0-63 normalized
	BYTE	byteWeaponState : 2;	// see eWeaponState
	BYTE	byteAspectRatio;
};

struct stTrailerData
{
	uint16_t	sTrailerID;
	float		fPosition[3];
	float		fQuaternion[4];
	float		fSpeed[3];
	float		fSpin[3];
};

struct stPassengerData
{
	uint16_t	sVehicleID;
	uint8_t		byteSeatID;
	uint8_t		byteCurrentWeapon;
	uint8_t		byteHealth;
	uint8_t		byteArmor;
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

struct stDamageData
{
	uint16_t	sVehicleID_lastDamageProcessed;
	int			iBumperDamage;
	int			iDoorDamage;
	uint8_t		byteLightDamage;
	uint8_t		byteWheelDamage;
};

struct stSurfData
{
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnk0;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	struct stSAMPVehicle* pSurfingVehicle;
	int			iUnk1;
	int			iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};

struct stUnoccupiedData
{
	int16_t sVehicleID;
	uint8_t byteSeatID;
	float	fRoll[3];
	float	fDirection[3];
	float	fPosition[3];
	float	fMoveSpeed[3];
	float	fTurnSpeed[3];
	float	fHealth;
};

struct stBulletData
{
	uint8_t		byteType;
	uint16_t	sTargetID;
	float		fOrigin[3];
	float		fTarget[3];
	float		fCenter[3];
	uint8_t		byteWeaponID;
};

struct stSpectatorData
{
	uint16_t	sLeftRightKeys;
	uint16_t	sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct stSAMPKeys	stSampKeys;
	};
	float	fPosition[3];
};

struct stStatsData
{
	int iMoney;
	int iAmmo;	// ?
};

struct stHeadSync
{
	CVector	fHeadSync;
	unsigned long		iHeadSyncUpdateTick;
	unsigned long		iHeadSyncLookTick;
};

struct CAMERA_TARGET_AIM
{
	uint16_t ObjectID;
	uint16_t VehicleID;
	uint16_t PlayerID;
	uint16_t ActorID;
};

struct PLAYER_SPAWN_INFO
{
	BYTE byteTeam;
	int iSkin;
	int iCustomModel;
	BYTE unk;
	VECTOR vecPos;
	float fRotation;
	int iSpawnWeapons[3];
	int iSpawnWeaponsAmmo[3];
};

struct stLocalPlayer
{
	struct stInCarData		inCarData;
	struct stAimData		aimData;
	struct stTrailerData		trailerData;
	struct stOnFootData		onFootData;
	struct stPassengerData		passengerData;
	int				iIsActive;
	int				iIsWasted;
	uint16_t			sCurrentVehicleID;
	uint16_t			sLastVehicleID;
	uint16_t			sCurrentAnimID;
	uint16_t			sAnimFlags;
	uint32_t			ulUnk0;
	struct stSAMPPed* pSAMP_Actor;
	int				iIsSpectating;
	uint8_t				byteTeamID;
	int				iSpawnClassID;
	CAMERA_TARGET_AIM       	cameraTarget;
	uint32_t			ulCameraTargetTick;
	struct stHeadSync		headSyncData;
	uint32_t			ulHeadSyncTick;
	uint16_t			usUnk2;
	uint32_t			ulSendTick;
	uint32_t			ulSpectateTick;
	uint32_t			ulAimTick;
	uint32_t			ulStatsUpdateTick;
	int				iSpawnClassLoaded;
	uint32_t			ulSpawnSelectionTick;
	uint32_t			ulSpawnSelectionStart;
	PLAYER_SPAWN_INFO      		spawnInfo;
	int				iIsActorAlive;
	uint32_t			ulWeapUpdateTick;
	uint16_t			sAimingAtPlayerID;
	uint16_t			sAimingAtActorID;
	uint8_t				byteCurrentWeapon;
	uint8_t				byteWeaponInventory[13];
	int				iWeaponAmmo[13];
	int				iPassengerDriveBy;
	uint8_t				byteCurrentInterior;
	int				iIsInRCVehicle;
	char                    	szPlayerName[256];
	struct stSurfData		surfData;
	int				iClassSelectionOnDeath;
	int				iRequestToSpawn;
	int				iIsInSpawnScreen;
	uint32_t			ulDisplayZoneTick;
	uint8_t				byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t				byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int				iSpectateID;
	int				iInitiatedSpectating;
	struct stDamageData		vehicleDamageData;
};

struct stRemotePlayerData
{
	int							field_1;
	BOOL                    	iShowNameTag;
	BOOL                   	 	bUsingJetPack;
	uint8_t						byteSpecialAction;
	char						pad_2[12];
	struct stInCarData			inCarData;
	struct stTrailerData		trailerData;
	struct stAimData			aimData;
	struct stPassengerData		passengerData;
	struct stOnFootData			onFootData;
	uint8_t						byteTeamID;
	uint8_t						bytePlayerState;
	uint8_t						byteSeatID;
	int							field_3;
	int							iPassengerDriveBy;
	char						pad_1[76];
	CVector						m_positionDifference;
	float						real;
	CVector						imag;
	CVector						fOnFootPos;
	CVector						fOnFootMoveSpeed;
	CVector						fVehiclePosition;
	CVector						fVehicleMoveSpeed;
	float						fActorArmor;
	float						fActorHealth;
	int							iLastAnimationID;
	unsigned char						byteUpdateFromNetwork;
	unsigned long					dwTick;
	unsigned long					dwLastStreamedInTick;	// is 0 when currently streamed in
	BOOL                	ulUnk2;
	int							iAFKState;
	struct stHeadSync			headSyncData;
	struct stSAMPPed* pSAMP_Actor;
	struct stSAMPVehicle* pSAMP_Vehicle;
	uint16_t					sPlayerID;
	uint16_t					sVehicleID;
	int							iGlobalMarkerLoaded;
	int							iGlobalMarkerLocation[3];
	uint32_t					ulGlobalMarker_GTAID;
};

struct stRemotePlayer
{
	int				pad0;
	int				iScore;
	int				iIsNPC;
	int				iPing;
	stRemotePlayerData* pPlayerData;
	void* pVTBL_txtHandler;
	std::string			strPlayerName;
};

template <typename T>
struct stSAMPEntity
{
	void* pVTBL;
	uint8_t		byteUnk0[60]; // game CEntity object maybe. always empty.
	T* pGTAEntity;
	uint32_t	ulGTAEntityHandle;
};

struct stSAMPPed : public stSAMPEntity < actor_info >
{
	int					usingCellPhone;
	uint8_t				byteUnk0[600]; // attached objects info - (state + info + ptr) * 10
	struct actor_info* pGTA_Ped;
	uint8_t				byteUnk1[22];
	uint8_t				byteKeysId;
	uint16_t			ulGTA_UrinateParticle_ID;
	int					DrinkingOrSmoking;
	int					object_in_hand;
	int					drunkLevel;
	uint8_t				byteUnk2[5];
	int					isDancing;
	int					danceStyle;
	int					danceMove;
	uint8_t				byteUnk3[20];
	int					isUrinating;
};

struct stVehiclePool
{
	int						iVehicleCount;
	void* pUnk0;
	uint8_t					byteSpace1[0x112C];
	struct stSAMPVehicle* pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	struct vehicle_info* pGTA_Vehicle[SAMP_MAX_VEHICLES];
	uint8_t					byteSpace2[SAMP_MAX_VEHICLES * 6];
	uint32_t				ulShit[SAMP_MAX_VEHICLES];
	int						iIsListed2[SAMP_MAX_VEHICLES];
	uint32_t				byteSpace3[SAMP_MAX_VEHICLES * 2];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated;
};

struct stSAMPVehicle : public stSAMPEntity < vehicle_info >
{
	uint32_t			bUnk0;
	struct vehicle_info* pGTA_Vehicle;
	uint8_t				byteUnk1[8];
	int					bIsMotorOn;
	int					iIsLightsOn;
	int					iIsLocked;
	uint8_t				byteIsObjective;
	int					iObjectiveBlipCreated;
	uint8_t				byteUnk2[16];
	uint8_t				byteColor[2];
	int					iColorSync;
	int					iColor_something;
};

struct stObject : public stSAMPEntity < object_info >
{
	uint8_t				byteUnk0[2];
	uint32_t			ulUnk1;
	int					iModel;
	uint16_t			byteUnk2;
	float				fDrawDistance;
	float				fUnk;
	float				fPos[3];
	uint8_t				byteUnk3[68];
	uint8_t				byteUnk4;
	float				fRot[3];
	// ...
};

struct stObjectPool
{
	int				iObjectCount;
	int				iIsListed[SAMP_MAX_OBJECTS];
	struct stObject* object[SAMP_MAX_OBJECTS];
};

struct stGangzone
{
	float	fPosition[4];
	DWORD	dwColor;
	DWORD	dwAltColor;
};

struct stGangzonePool
{
	struct stGangzone* pGangzone[SAMP_MAX_GANGZONES];
	int					iIsListed[SAMP_MAX_GANGZONES];
};

struct stTextLabel
{
	char* pText;
	DWORD		color;
	float		fPosition[3];
	float		fMaxViewDistance;
	uint8_t		byteShowBehindWalls;
	uint16_t	sAttachedToPlayerID;
	uint16_t	sAttachedToVehicleID;
};

struct stTextLabelPool
{
	struct stTextLabel	textLabel[SAMP_MAX_3DTEXTS];
	int					iIsListed[SAMP_MAX_3DTEXTS];
};

struct stChatEntry
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct stFontRenderer
{
	ID3DXFont* m_pChatFont;
	ID3DXFont* m_pLittleFont;
	ID3DXFont* m_pChatShadowFont;
	ID3DXFont* m_pLittleShadowFont;
	ID3DXFont* m_pCarNumberFont;
	ID3DXSprite* m_pTempSprite;
	IDirect3DDevice9* m_pD3DDevice;
	char* m_pszTextBuffer;
};

struct stChatInfo
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	struct stChatEntry	chatEntry[100];
	stFontRenderer* m_pFontRenderer;
	ID3DXSprite* m_pChatTextSprite;
	ID3DXSprite* m_pSprite;
	IDirect3DDevice9* m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	ID3DXRenderToSurface* pID3DXRenderToSurface;
	IDirect3DTexture9* m_pTexture;
	IDirect3DSurface9* pSurface;
	D3DDISPLAYMODE* pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
	int					m_iTimeStampTextOffset;
};

struct stInputBox
{
	void* pUnknown;
	uint8_t	bIsChatboxOpen;
	uint8_t	bIsMouseInChatbox;
	uint8_t	bMouseClick_related;
	uint8_t	unk;
	DWORD	dwPosChatInput[2];
	uint8_t	unk2[263];
	int		iCursorPosition;
	uint8_t	unk3;
	int		iMarkedText_startPos; // Highlighted text between this and iCursorPosition
	uint8_t	unk4[20];
	int		iMouseLeftButton;
};

typedef void(__cdecl* CMDPROC) (PCHAR);
struct stInputInfo
{
	void* pD3DDevice;
	void* pDXUTDialog;
	stInputBox* pDXUTEditBox;
	CMDPROC				pCMDs[SAMP_MAX_CLIENTCMDS];
	char				szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int					iCMDCount;
	int					iInputEnabled;
	char				szInputBuffer[129];
	char				szRecallBufffer[10][129];
	char				szCurrentBuffer[129];
	int					iCurrentRecall;
	int					iTotalRecalls;
	CMDPROC				pszDefaultCMD;
};

struct stKillEntry
{
	char		szKiller[25];
	char		szVictim[25];
	D3DCOLOR	clKillerColor;
	D3DCOLOR	clVictimColor;
	uint8_t		byteType;
};

struct stKillInfo
{
	int					iEnabled;
	struct stKillEntry	killEntry[5];
	int 			iLongestNickLength;
	int 			iOffsetX;
	int 			iOffsetY;

	ID3DXFont* pD3DFont;
	ID3DXFont* pWeaponFont1;
	ID3DXFont* pWeaponFont2;
	ID3DXSprite* pSprite;
	IDirect3DDevice9* pD3DDevice;
	int 			iAuxFontInited;
	ID3DXFont* pAuxFont1;
	ID3DXFont* pAuxFont2;
};

struct stChatPlayer
{
	int		iCreated;
	char	probablyTheText[256];
	DWORD	dwTickCreated;
	DWORD	dwLiveLength;
	DWORD	dwColor;
	float	fDrawDistance;
	DWORD	dwUnknown;
};

struct stAudio {
	int	iSoundState; // 0 - Finished, 1 - Loaded, 2 - Playing
	bool bStopInteriourAmbientSounds;
};

struct stGameInfo
{
	struct stCamera
	{
		void* pEntity; // attached entity
		class CMatrix_Padded* matrix;
	};

	stAudio* pAudio;
	stCamera* pCamera;
	stSAMPPed* pLocalPlayerPed;
	float		fRaceCheckpointPos[3];
	float		fRaceCheckpointNext[3];
	float		m_fRaceCheckpointSize;
	uint8_t		byteRaceType;
	int			bRaceCheckpointsEnabled;
	DWORD		dwRaceCheckpointMarker;
	DWORD		dwRaceCheckpointHandle;
	float		fCheckpointPos[3];
	float		fCheckpointExtent[3];
	int			bCheckpointsEnabled;
	DWORD		dwCheckpointMarker;
	uint32_t	ulUnk2;
	int			bHeadMove;
	uint32_t    ulFpsLimit;
	int			iCursorMode;
	uint32_t	ulUnk1;
	int			bClockEnabled;
	uint8_t		byteUnk3;
	uint8_t		byteVehicleModels[212];
};

struct stScoreboardInfo
{
	int					iIsEnabled;
	int					iPlayersCount;
	float				fTextOffset[2];
	float				fScalar;
	float				fSize[2];
	float				fUnk0[5];
	IDirect3DDevice9* pDirectDevice;
	class _CDXUTDialog* pDialog;
	class _CDXUTListBox* pList;
	int					iOffset;		// ?
	int					iIsSorted;		// ?
};

struct stActorPool
{
	int					iLastActorID;
	stSAMPEntity<void>* pActor[SAMP_MAX_ACTORS]; // ?
	int					iIsListed[SAMP_MAX_ACTORS];
	struct actor_info* pGTAPed[SAMP_MAX_ACTORS];
	uint32_t			ulUnk0[SAMP_MAX_ACTORS];
	uint32_t			ulUnk1[SAMP_MAX_ACTORS];
};

struct stChatBubbleInfo
{
	struct stChatPlayer	chatBubble[SAMP_MAX_PLAYERS];
};

struct stStreamedOutPlayerInfo
{
	int		iPlayerID[SAMP_MAX_PLAYERS];
	float	fPlayerPos[SAMP_MAX_PLAYERS][3];
};
#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// SUPPORT VARIABLES //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
struct stTranslateGTASAMP_vehiclePool
{
	// the index is the position in the vehicle pool
	//
	// translation data
	int iSAMPID[SAMP_MAX_VEHICLES];
};

struct stTranslateGTASAMP_pedPool
{
	// the index is the position in the ped pool
	//
	// translation data
	int iSAMPID[SAMP_MAX_PLAYERS];
};

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// FUNCTIONS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void											update_translateGTASAMP_vehiclePool(void);
void											update_translateGTASAMP_pedPool(void);

void											getSamp();
uint32_t										getSampAddress();

struct stSAMP* stGetSampInfo(void);
struct stChatInfo* stGetSampChatInfo(void);
struct stInputInfo* stGetInputInfo(void);
struct stKillInfo* stGetKillInfo(void);
struct stScoreboardInfo* stGetScoreboardInfo(void);
D3DCOLOR										samp_color_get(int id, DWORD trans = 0xFF000000);

int												getNthPlayerID(int n);
int												getPlayerCount(void);
int												getVehicleCount(void);

int												setLocalPlayerName(const char* name);
int												getPlayerPos(int iPlayerID, float fPos[3]);
const char* getPlayerName(int iPlayerID);
int												getPlayerState(int iPlayerID);
int												getPlayerVehicleGTAScriptingID(int iPlayerID);
int												getPlayerSAMPVehicleID(int iPlayerID);
int												isBadSAMPVehicleID(int iVehicleID);
int												isBadSAMPPlayerID(int iPlayerID);

struct actor_info* getGTAPedFromSAMPPlayerID(int iPlayerID);
struct vehicle_info* getGTAVehicleFromSAMPVehicleID(int iPlayerID);
int												getSAMPPlayerIDFromGTAPed(struct actor_info* info);
int												getSAMPVehicleIDFromGTAVehicle(struct vehicle_info* pVehicle);
uint32_t										getPedGTAScriptingIDFromPlayerID(int iPlayerID);
uint32_t										getVehicleGTAScriptingIDFromVehicleID(int iVehicleID);

int												samp_vehicle_find_nearest(int flags);

void											addClientCommand(char* text, CMDPROC function);
void											addToChatWindow(char* text, D3DCOLOR textColor, int playerID = -1);
void											addMessageToChatWindow(const char* text, ...);
void											addMessageToChatWindowSS(const char* text, ...);
void											restartGame();
void											addSayToChatWindow(char* msg);
void											say(char* text, ...);
void											playerSpawn(void);
void											disconnect(int reason);
void											setPassword(char* password);
void											sendSetInterior(uint8_t interiorID);
void											setSpecialAction(uint8_t byteSpecialAction);
void											sendSCMEvent(int iEvent, int iVehicleID, int iParam1, int iParam2);
void											toggleSAMPCursor(int iToggle);
void											sendDeath(void);
void											changeServer(const char* pszIp, unsigned ulPort, const char* pszPassword);
void											updateScoreboardData(void);
void											toggleOffScoreboard(void);

void											installSAMPHooks();
void											setSAMPCustomSendRates(int iOnFoot, int iInCar, int iAim, int iHeadSync);
int												sampPatchDisableNameTags(int iEnabled);
int												sampPatchDisableInteriorUpdate(int iEnabled);
int												sampPatchDisableScoreboardToggleOn(int iEnabled);
int												sampPatchDisableChatInputAdjust(int iEnabled);
void											sampPatchDisableAnticheat(void);

// global pointer externals
extern int										iIsSAMPSupported;
extern int										g_renderSAMP_initSAMPstructs;
extern struct stSAMP* g_SAMP;
extern struct stPlayerPool* g_Players;
extern struct stVehiclePool* g_Vehicles;
extern struct stChatInfo* g_Chat;
extern struct stInputInfo* g_Input;
extern struct stKillInfo* g_DeathList;
extern struct stScoreboardInfo* g_Scoreboard;
extern struct stStreamedOutPlayerInfo			g_stStreamedOutInfo;

// global support variables externals
extern struct stTranslateGTASAMP_vehiclePool	translateGTASAMP_vehiclePool;
extern struct stTranslateGTASAMP_pedPool		translateGTASAMP_pedPool;

extern char										g_m0dCmdlist[(SAMP_MAX_CLIENTCMDS - 23)][30];
extern int										g_m0dCmdNum;
extern bool										g_m0dCommands;
