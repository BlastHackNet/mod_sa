/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, FYP

	mod_sa is available from http://code.google.com/p/m0d-s0beit-sa/

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

#define SAMP_PLAYER_MAX				1004
#define SAMP_VEHICLE_MAX			2000
#define SAMP_PICKUP_MAX				4096
#define SAMP_OBJECTS_MAX			1000
#define SAMP_GANGZONE_MAX			1024
#define MAX_3DTEXT					2048
#define MAX_TEXTDRAW				2048
#define MAX_GANGZONES				1024
#define MAX_PLAYER_NAME				24
#define ALLOWED_PLAYER_NAME_LENGTH	20
#define MAX_CLIENTCMDS				144
#define SAMP_MENUS_MAX				128

#define SAMP_CHAT_INFO_OFFSET			0x212A6C
#define SAMP_CHAT_INPUT_INFO_OFFSET		0x212A70
#define SAMP_KILL_INFO_OFFSET			0x212A74
#define SAMP_INFO_OFFSET				0x212A80
#define SAMP_MISC_INFO					0x212A94

#define SAMP_COLOR_OFFSET				0x1FA378
#define VALUE_DRAWING_DISTANCE			0xCECF0

// used in proxyIDirect3DDevice9.cpp
#define SAMP_SCOREBOARD_INFO			0x212A3C
#define SAMP_FUNCUPDATESCOREBOARDDATA	0x7D10
#define SAMP_PATCH_NOCARCOLORRESETTING	0x776F0
#define SAMP_DRAWTEXTLABELS				0x86EA1

enum Gamestate
{
	GAMESTATE_WAIT_CONNECT = 10,
	GAMESTATE_CONNECTING,
	GAMESTATE_AWAIT_JOIN,
	GAMESTATE_CONNECTED,
	GAMESTATE_DISCONNECTED,
	GAMESTATE_RESTARTING = 17
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
struct stSAMPPools
{
#pragma pack( 1 )
	struct stTextdrawPool	*pPool_Textdraw;
	struct stObjectPool		*pPool_Object;
	struct stGangzonePool	*pPool_Gangzone;
	struct stTextLabelPool	*pPool_Text3D;
	void					*pPool_PlayerLabels;
	struct stPlayerPool		*pPool_Player;
	struct stVehiclePool	*pPool_Vehicle;
	struct stPickupPool		*pPool_Pickup;
};

struct stSAMP
{
#pragma pack( 1 )
	uint32_t				ulMapIcons[100];
	int						iGameState;
	uint32_t				ulConnectTick; // not tested
	byte					byteSpace[44];
	char					szIP[258];
	char					szHostname[258];
	uint8_t					byteUnk1;
	uint32_t				ulPort;
	int						iLanMode; // not tested
	void					*pRakClientInterface;
	struct stSampSettings	*pSettings;
	struct stSAMPPools		*pPools;
};

struct stSampSettings
{
#pragma pack( 1 )
	uint8_t byteCJWalk;
	uint8_t byteUnk0[4];
	float	fWorldBoundaries[4];
	uint8_t byteUnk1;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint8_t byteVehicleFriendlyFire;
	uint8_t byteUnk2[7];
	int		iClassesAvailable;
	float	fNameTagsDistance;
	uint8_t byteUnk3;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t	byteNoNametagsBehindWalls;
	uint8_t bytePlayerMarkersMode;
	uint8_t byteUnk4[3];
	float fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
};

struct stTextdraw
{
#pragma pack( 1 )
	char szText[1024];
	uint8_t unk_1025;
	char szString[2048];
	uint8_t unk_3073[2];  // always = 00 00  (?)
	float fLetterWidth;
	float fLetterHeight;
	DWORD dwLetterColor;
	uint8_t byte_unk; // always = 01 (?)
	BYTE byteCenter;
	BYTE byteBox;
	float fBoxSizeX;
	float fBoxSizeY;
	DWORD dwBoxColor;
	BYTE byteProportional;
	DWORD dwShadowColor;
	BYTE byteShadowSize;
	BYTE byteOutline;
	BYTE byteLeft;
	BYTE byteRight;
	BYTE byteStyle; // font style/texture
	uint8_t unk[3]; // 00 00 00
	float fX;
	float fY;
};

struct stTextdrawPool
{
#pragma pack( 1 )
	int					iIsListed[MAX_TEXTDRAW];
	uint8_t				unk0[1024];
	struct stTextdraw	*textdraw[MAX_TEXTDRAW];
	uint8_t				unk1[1024];
};

struct stPickup
{
#pragma pack( 1 )
	int		iModelID;
	int		iType;
	float	fPosition[3];
};

struct stPickupPool
{
#pragma pack( 1 )
	int					iPickupsCount;
	uint32_t			ul_GTA_PickupID[SAMP_PICKUP_MAX];
	int					iPickupID[SAMP_PICKUP_MAX];
	int					iTimePickup[SAMP_PICKUP_MAX];
	uint8_t				unk[SAMP_PICKUP_MAX * 3];
	struct stPickup		pickup[SAMP_PICKUP_MAX];
};

struct stPlayerPool
{
#pragma pack( 1 )
	uint32_t				ulUnk0;
	uint16_t				sLocalPlayerID;
	void					*pVTBL_txtHandler;
	union
	{
		char	szLocalPlayerName[16];
		char	*pszLocalPlayerName;
	};
	int						iStrlen_LocalPlayerName;
	int						iScoreboard_something;
	struct stLocalPlayer	*pLocalPlayer;
	int						iLocalPlayerPing;
	int						iLocalPlayerScore;
	struct stRemotePlayer	*pRemotePlayer[SAMP_PLAYER_MAX];
	int						iIsListed[SAMP_PLAYER_MAX];
	uint32_t				ulUnk1[SAMP_PLAYER_MAX];
};

struct stSAMPKeys
{
#pragma pack( 1 )
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
#pragma pack( 1 )
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
	uint16_t	sCurrentAnimationID;
	uint16_t	sAnimFlags;
};

struct stInCarData
{
#pragma pack( 1 )
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
	};
};

struct stAimData
{
#pragma pack( 1 )
	BYTE byteCamMode;
	float vecAimf1[3];
	float vecAimPos[3];
	float fAimZ;
	BYTE byteCamExtZoom : 6;	// 0-63 normalized
	BYTE byteWeaponState : 2;	// see eWeaponState
	BYTE bUnk;
};

struct stTrailerData
{
#pragma pack( 1 )
	uint16_t	sTrailerID;
	float		fDirection[3];
	float		fRoll[3];
	float		fPosition[3];
	float		fSpeed[3];
	uint32_t	pad; // fix alignment
};

struct stPassengerData
{
#pragma pack( 1 )
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
	float		fPosition[3];
};

struct stDamageData
{
#pragma pack( 1 )
	uint16_t	sVehicleID_lastDamageProcessed;
	int			iBumperDamage;
	int			iDoorDamage;
	uint8_t		byteLightDamage;
	uint8_t		byteWheelDamage;
};

struct stSurfData
{
#pragma pack( 1 )
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnknown;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	// int			iunknown_[2];
	int			iunknown_;
	int			iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};

struct stHeadSync
{
#pragma pack( 1 )
	float	fHeadSync[3];
	int		iHeadSyncUpdateTick;
	int		iHeadSyncLookTick;
};

struct stLocalPlayer
{
#pragma pack( 1 )
	int						iIsActive;
	int						iIsWasted;
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	uint16_t				sCurrentAnimID;
	uint16_t				sAnimFlags;
	uint32_t				ulUnk0;
	struct stSAMPPed		*pSAMP_Actor;
	struct stAimData		aimData;
	struct stOnFootData		onFootData;
	struct stPassengerData	passengerData;
	struct stTrailerData	trailerData;
	struct stInCarData		inCarData;
	struct stHeadSync		headSyncData;
	uint32_t				ulHeadSyncTick;
	uint8_t					byteTeamID;
	int						iSpawnSkin;
	uint8_t					byteUnk1;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID2;
	uint16_t				shortUnk2;
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint16_t				sAimingAtPid;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	struct stSurfData		surfData;
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	BYTE					byteUnk4[260];
	struct stDamageData		vehicleDamageData;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	uint32_t 				ulUnk5;
	uint8_t					byteSpectateMode; // 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t					byteSpectateType; // 0 = none, 1 = player, 2 = vehicle
	int						iSpectateID;
	int						iInitiatedSpectating;
};

struct stRemotePlayerData
{
#pragma pack( 1 )
	uint16_t				sPlayerID;
	uint16_t				sVehicleID;
	uint8_t					byteTeamID;
	uint8_t					bytePlayerState;
	uint8_t					byteSeatID;
	uint32_t				ulUnk0;
	int						iPassengerDriveBy;
	struct stSAMPVehicle	*pSAMP_Vehicle;
	struct stSAMPPed		*pSAMP_Actor;
	uint8_t					byteUnk1[40];
	float					fOnFootPos[3];
	float					fOnFootMoveSpeed[3];
	float					fVehiclePosition[3];
	float					fVehicleMoveSpeed[3];
	float					fVehicleRoll[4];
	int						iShowNameTag;
	int						iHasJetPack;
	uint8_t					byteSpecialAction;
	struct stTrailerData	trailerData;
	struct stPassengerData	passengerData;
	struct stAimData		aimData;
	struct stInCarData		inCarData;
	struct stOnFootData		onFootData;
	uint8_t					byteUnk2;
	uint32_t				dwLastStreamedInTick; // is 0 when currently streamed in
	uint32_t				dwTick;
	uint32_t				ulUnk3;
	float					fActorHealth;
	float					fActorArmor;
	int						iUnk4;
	int						iAFKState;
	struct stHeadSync		headSyncData;
	int						iGlobalMarkerLoaded;
	int						iGlobalMarkerLocation[3];
	uint32_t				ulGlobalMarker_GTAID;
};

struct stRemotePlayer
{
#pragma pack( 1 )
	int					iIsNPC;
	int					iScore;
	stRemotePlayerData	*pPlayerData;
	int					iPing;
	void				*pVTBL_txtHandler;
	union
	{
		char	szPlayerName[16];
		char	*pszPlayerName;
	};
	int					iStrlenName__; // ?
	int					iStrlenName; // iStrlenNameMax, numByteReserved?
};

struct stSAMPPed
{
#pragma pack( 1 )
	void				*pVTBL_sampPed;
	uint8_t				byteUnknown1[60];
	struct actor_info	*pGTA_Ped_;
	uint32_t			ulGTA_Ped_ID;
	int					usingCellPhone;
	uint8_t				byteUnknown2[600];
	struct actor_info	*pGTA_Ped;
	uint8_t				byteUnknown3[22];
	uint8_t				byteKeysId;
	uint16_t			ulGTA_UrinateParticle_ID;
	int					DrinkingOrSmoking;
	int					object_in_hand;
	int					drunkLevel;
	uint8_t				byteUnknown4[5];
	int					isDancing;
	int					danceStyle;
	int					danceMove;
	uint8_t				byteUnknown5[20];
	int					isUrinating;
};

struct stVehiclePool
{
#pragma pack( 1 )
	struct stSAMPVehicle	*pSAMP_Vehicle[SAMP_VEHICLE_MAX];
	int						iIsListed[SAMP_VEHICLE_MAX];
	struct vehicle_info		*pGTA_Vehicle[SAMP_VEHICLE_MAX];
	uint8_t					byteUnknown[0xBCAC];
	float					fSpawnPos[SAMP_VEHICLE_MAX][3];
	int						iInitiated; // not tested
};

struct stSAMPVehicle
{
#pragma pack( 1 )
	void				*pVTBL_Vehicle;
	uint8_t				byteUnknown1[60];
	struct vehicle_info *pGTA_Vehicle_;
	uint32_t			ulGTA_Vehicle_ID;
	uint32_t			ulUnk;
	struct vehicle_info *pGTA_Vehicle;
	uint8_t				byteUnknown2[8];
	int					iIsMotorOn;
	int					iIsLightsOn;
	int					iIsLocked;
	uint8_t				byteIsObjective;
	int					iObjectiveBlipCreated;
	uint8_t				byteUnknown3[20];
	uint8_t				byteColor[2];
	int					iColorSync;
	int					iColor_something;
};

struct stObject
{
#pragma pack( 1 )
	void				*pVTBL_Object;
	uint8_t				unk[60];
	struct object_info	*pGTAObject;
	uint32_t			ulGTA_Object_ID;
};

struct stObjectPool
{
#pragma pack( 1 )
	int				iIsListed[SAMP_OBJECTS_MAX];
	struct stObject *object[SAMP_OBJECTS_MAX];
};

struct stGangzone
{
	float	fPosition[4];
	DWORD	dwColor;
	DWORD	dwAltColor;
};

struct stGangzonePool
{
	struct stGangzone	*pGangzone[SAMP_GANGZONE_MAX];
	int					iIsListed[SAMP_GANGZONE_MAX];
};

struct stTextLabel
{
#pragma pack( 1 )
	char		*pText;
	DWORD		color;
	float		fPosition[3];
	float		fMaxViewDistance;
	uint8_t		byteShowBehindWalls;
	uint16_t	sAttachedToPlayerID;
	uint16_t	sAttachedToVehicleID;
};

struct stTextLabelPool
{
#pragma pack( 1 )
	struct stTextLabel	textLabel[MAX_3DTEXT];
	int					iIsListed[MAX_3DTEXT];
};

struct stChatEntry
{
#pragma pack( 1 )
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct stChatInfo
{
#pragma pack( 1 )
	int					pagesize;
	void				*pUnk;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			iUnk;
	char				logFilePathChatLog[MAX_PATH+1];
	void				*pChatbox_unknown[3]; // probably classes that handle fonts/sprites
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				dwChatboxOffset;
	struct stChatEntry	chatEntry[100];
	DWORD				dwChatLinesHeight;
	DWORD				dwDistanceTextToTimestamp;
};

struct stInputBox
{
#pragma pack( 1 )
	void	*pUnknown;
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

typedef void ( __cdecl *CMDPROC ) ( PCHAR );
struct stInputInfo
{
#pragma pack( 1 )
	void		*pD3DDevice;
	void		*pDXUTDialog;
	stInputBox	*pDXUTEditBox;
	CMDPROC 	pCMDs[MAX_CLIENTCMDS];
	char		szCMDNames[MAX_CLIENTCMDS][33];
	int			iCMDCount;
	int			iInputEnabled;
	char		szInputBuffer[129];
	char		szRecallBufffer[10][129];
	char		szCurrentBuffer[129];
	int			iCurrentRecall;
	int			iTotalRecalls;
	CMDPROC 	pszDefaultCMD;
};

struct stKillEntry
{
#pragma pack( 1 )
	char		szKiller[25];
	char		szVictim[25];
	D3DCOLOR	clKillerColor;
	D3DCOLOR	clVictimColor;
	uint8_t		byteType;
};

struct stKillInfo
{
#pragma pack( 1 )
	int					iEnabled;
	struct stKillEntry	killEntry[5];
};

struct stChatPlayer
{
#pragma pack( 1 )
	int			iCreated;
	char		probablyTheText[256]; // text max length = 144
	DWORD		dwTickCreated;
	DWORD		dwLiveLength;
	DWORD		dwColor;
	float		fDrawDistance;
	DWORD		dwUnknown;
};

struct stChatBubbleInfo
{
#pragma pack( 1 )
	struct stChatPlayer	chatBubble[SAMP_PLAYER_MAX];
};

struct stStreamedOutPlayerInfo
{
	int		iPlayerID[SAMP_PLAYER_MAX];
	float	fPlayerPos[SAMP_PLAYER_MAX][3];
};

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// SUPPORT VARIABLES //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
struct stTranslateGTASAMP_vehiclePool
{
#pragma pack( 1 )
	// the index is the position in the vehicle pool
	//
	// translation data
	int iSAMPID[SAMP_VEHICLE_MAX];
};

struct stTranslateGTASAMP_pedPool
{
#pragma pack( 1 )
	// the index is the position in the ped pool
	//
	// translation data
	int iSAMPID[SAMP_PLAYER_MAX];
};

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// FUNCTIONS //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void											update_translateGTASAMP_vehiclePool ( void );
void											update_translateGTASAMP_pedPool ( void );

bool											findstrinstr ( char *text, char *find );

int												isBadPtr_SAMP_iVehicleID ( int iVehicleID );
int												isBadPtr_SAMP_iPlayerID ( int iPlayerID );

void											getSamp ();
uint32_t										getSampAddress ();

struct stSAMP									*stGetSampInfo ( void );
struct stChatInfo								*stGetSampChatInfo ( void );
struct stInputInfo								*stGetInputInfo ( void );
struct stKillInfo								*stGetKillInfo ( void );
D3DCOLOR										samp_color_get ( int id, DWORD trans = 0xFF000000 );

void											sampMainCheat ();

int												getNthPlayerID ( int n );
int												getPlayerCount ( void );
int												getVehicleCount ( void );

int												setLocalPlayerName ( const char *name );
int												getPlayerPos ( int iPlayerID, float fPos[3] );
const char										*getPlayerName ( int iPlayerID );
int												getPlayerState ( int iPlayerID );
int												getPlayerVehicleGTAScriptingID ( int iPlayerID );
int												getPlayerSAMPVehicleID ( int iPlayerID );
void											spectatePlayer(int iPlayerID);
void											spectateHandle();

struct actor_info								*getGTAPedFromSAMPPlayerID ( int iPlayerID );
struct vehicle_info								*getGTAVehicleFromSAMPVehicleID ( int iPlayerID );
int												getSAMPPlayerIDFromGTAPed ( struct actor_info *info );
int												getSAMPVehicleIDFromGTAVehicle ( struct vehicle_info *pVehicle );
uint32_t										getPedGTAScriptingIDFromPlayerID ( int iPlayerID );
uint32_t										getVehicleGTAScriptingIDFromVehicleID ( int iVehicleID );

int												samp_vehicle_find_nearest ( int flags );

bool											get_isModCommandsActive ();
void											init_samp_chat_cmds ();
void											addClientCommand ( char *text, int function );
void											addToChatWindow ( char *text, D3DCOLOR textColor, int playerID = -1 );
void											addMessageToChatWindow ( const char *text, ... );
void											addMessageToChatWindowSS ( const char *text, ... );
void											restartGame ();
void											addSayToChatWindow ( char *msg );
void											say ( char *text, ... );
void											showGameText ( char *text, int time, int textsize );
void											playerSpawn ( void );
void											disconnect ( int reason );
void											setPassword ( char *password );
void											sendSetInterior ( uint8_t interiorID );
void											setSpecialAction ( uint8_t byteSpecialAction );
void											sendSCMEvent ( int iEvent, int iVehicleID, int iParam1, int iParam2 );
void											toggleSAMPCursor(int iToggle);

void											installSAMPHooks ();
void											setSAMPCustomSendRates ( int iOnFoot, int iInCar, int iAim, int iHeadSync );
int												sampPatchDisableNameTags ( int iEnabled );
int												sampPatchDisableInteriorUpdate ( int iEnabled );
int												sampPatchDisableScoreboardToggleOn ( int iEnabled );
int												sampPatchDisableChatInputAdjust ( int iEnabled );
void											sendDeath ( void );
void											changeServer( const char *pszIp, unsigned ulPort, const char *pszPassword );

// global pointer externals
extern int										iIsSAMPSupported;
extern int										g_renderSAMP_initSAMPstructs;
extern struct stSAMP							*g_SAMP;
extern struct stPlayerPool						*g_Players;
extern struct stVehiclePool						*g_Vehicles;
extern struct stChatInfo						*g_Chat;
extern struct stInputInfo						*g_Input;
extern struct stKillInfo						*g_DeathList;
extern struct stStreamedOutPlayerInfo			g_stStreamedOutInfo;

// global support variables externals
extern struct stTranslateGTASAMP_vehiclePool	translateGTASAMP_vehiclePool;
extern struct stTranslateGTASAMP_pedPool		translateGTASAMP_pedPool;

extern int										g_iSpectateEnabled;
extern int										g_iCursorEnabled;
extern int										g_iNumPlayersMuted;
extern bool										g_bPlayerMuted[SAMP_PLAYER_MAX];
