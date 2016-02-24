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
#define VEHICLE_LIST_ID_START		400
#define VEHICLE_LIST_SIZE			212

#define VEHICLE_CLASS_CAR			0
#define VEHICLE_CLASS_CAR_FAST		1
#define VEHICLE_CLASS_HEAVY			2
#define VEHICLE_CLASS_HELI			3
#define VEHICLE_CLASS_AIRPLANE		4
#define VEHICLE_CLASS_BIKE			5
#define VEHICLE_CLASS_BOAT			6
#define VEHICLE_CLASS_MINI			7
#define VEHICLE_CLASS_TRAILER		8
#define VEHICLE_CLASS_COUNT			9	/* # of classes */

#define VEHICLE_UPGRADES_COUNT		194

#define ACTOR_IS_DEAD( a )			( (a)->state == ACTOR_STATE_DYING || (a)->state == ACTOR_STATE_DEAD )
#define ACTOR_ALIVE					0x01
#define ACTOR_NOT_SAME_VEHICLE		0x02

#define VEHICLE_ALIVE				0x01
#define VEHICLE_EMPTY				0x02
#define VEHICLE_OCCUPIED			0x04
#define VEHICLE_NOTBURNING			0x08

#define FUNC_GET_CAR_ID				0x424160
#define FUNC_GET_CAR_STRUCT			0x4048E0
#define FUNC_GET_ACTOR_ID			0x4442D0
#define FUNC_GET_ACTOR_STRUCT		0x404910
#define FUNC_GET_OBJECT_ID			0x465070
#define FUNC_GET_OBJECT_STRUCT		0x465040
#define FUNC_GET_COL_MODEL_STRUCT	0x40FB80
#define FUNC_GET_BUILDING_STRUCT	0x403FA0

struct weapon_entry
{
	int			id;
	int			slot;
	int			model_id;
	const char	*name;
};

struct vehicle_entry
{
	int			id;			// model id
	int			class_id;	// class id
	const char	*name;		// vehicle name
	int			passengers; // total passenger seats, 0-10
};

struct interiors
{
	int			interior_id;
	float		pos[3];
	float		rotation;
	const char	*interior_name;
};

struct vehicle_upgrade_info
{
	int			iModelID;	// iModelID
	const char	*upgradeCategoryName;	// upgrade name
	const char	*upgradeName;			// upgrade name
};

struct move_animation_info
{
	eMoveAnim		moveStyleId;  // CPed.h
	const char*		moveStyleName;
};

struct str_split
{
	char	*str;
	char	**argv;
	int		argc;
};

// vehicle upgrade model IDs & names etc
const struct vehicle_upgrade_info	cveh_upgrade_info[VEHICLE_UPGRADES_COUNT] =
{
	{ 1087, "Hydraulics", "System" },
	{ 1009, "Nitro", "2X" },
	{ 1008, "Nitro", "5X" },
	{ 1010, "Nitro", "10X" },
	{ 1086, "Stereo", "Subwoofer" },

	// used for Slamvan, but not in compatible list
	{ 1111, "Emblem", "#1" },
	{ 1112, "Emblem", "#2" },
	{ 1000, "Spoiler", "Pro" },
	{ 1001, "Spoiler", "Win" },
	{ 1002, "Spoiler", "Drag" },
	{ 1003, "Spoiler", "Alpha" },
	{ 1014, "Spoiler", "Champ" },
	{ 1015, "Spoiler", "Race" },
	{ 1016, "Spoiler", "Worx" },
	{ 1023, "Spoiler", "Fury" },
	{ 1049, "Spoiler", "Alien" },
	{ 1050, "Spoiler", "X-Flow" },
	{ 1058, "Spoiler", "Alien" },
	{ 1060, "Spoiler", "X-Flow" },
	{ 1138, "Spoiler", "Alien" },
	{ 1139, "Spoiler", "X-Flow" },
	{ 1147, "Spoiler", "Alien" },
	{ 1146, "Spoiler", "X-Flow" },
	{ 1162, "Spoiler", "Alien" },
	{ 1158, "Spoiler", "X-Flow" },
	{ 1164, "Spoiler", "Alien" },
	{ 1163, "Spoiler", "X-Flow" },
	{ 1004, "Hood", "Champ Scoop" },
	{ 1005, "Hood", "Fury Scoop" },
	{ 1011, "Hood", "Race Scoop" },
	{ 1012, "Hood", "Worx Scoop" },
	{ 1142, "Vents", "Oval Vents" },
	{ 1143, "Vents", "Oval Vents" },
	{ 1144, "Vents", "Square Vents" },
	{ 1145, "Vents", "Square Vents" },
	{ 1006, "Roof", "Roof Scoop" },
	{ 1032, "Roof", "Alien Roof Vent" },
	{ 1033, "Roof", "X-Flow Roof Vent" },
	{ 1038, "Roof", "Alien Roof Vent" },
	{ 1035, "Roof", "X-Flow Roof Vent" },
	{ 1054, "Roof", "Alien" },
	{ 1053, "Roof", "X-Flow" },
	{ 1055, "Roof", "Alien" },
	{ 1061, "Roof", "X-Flow" },
	{ 1067, "Roof", "Alien" },
	{ 1068, "Roof", "X-Flow" },
	{ 1088, "Roof", "Alien" },
	{ 1091, "Roof", "X-Flow" },
	{ 1103, "Roof", "Covertible" },
	{ 1128, "Roof", "Vinyl Hardtop" },
	{ 1130, "Roof", "Hardtop" },
	{ 1131, "Roof", "Softtop" },

	// Sultan
	{ 1169, "Front Bumper", "Alien" },
	{ 1170, "Front Bumper", "X-Flow" },
	{ 1141, "Rear Bumper", "Alien" },
	{ 1140, "Rear Bumper", "X-Flow" },

	// Elegy
	{ 1171, "Front Bumper", "Alien" },
	{ 1172, "Front Bumper", "X-Flow" },
	{ 1149, "Rear Bumper", "Alien" },
	{ 1148, "Rear Bumper", "X-Flow" },

	// Flash
	{ 1153, "Front Bumper", "Alien" },
	{ 1152, "Front Bumper", "X-Flow" },
	{ 1150, "Rear Bumper", "Alien" },
	{ 1151, "Rear Bumper", "X-Flow" },

	// Stratum
	{ 1155, "Front Bumper", "Alien" },
	{ 1157, "Front Bumper", "X-Flow" },
	{ 1154, "Rear Bumper", "Alien" },
	{ 1156, "Rear Bumper", "X-Flow" },

	// Jester
	{ 1160, "Front Bumper", "Alien" },
	{ 1173, "Front Bumper", "X-Flow" },
	{ 1159, "Rear Bumper", "Alien" },
	{ 1161, "Rear Bumper", "X-Flow" },

	// Uranus
	{ 1166, "Front Bumper", "Alien" },
	{ 1165, "Front Bumper", "X-Flow" },
	{ 1168, "Rear Bumper", "Alien" },
	{ 1167, "Rear Bumper", "X-Flow" },

	// Broadway
	{ 1174, "Front Bumper", "Chrome" },
	{ 1175, "Front Bumper", "Slamin" },
	{ 1176, "Rear Bumper", "Chrome" },
	{ 1177, "Rear Bumper", "Slamin" },

	// Remington
	{ 1179, "Front Bumper", "Chrome" },
	{ 1185, "Front Bumper", "Slamin" },
	{ 1180, "Rear Bumper", "Chrome" },
	{ 1178, "Rear Bumper", "Slamin" },

	// Blade
	{ 1182, "Front Bumper", "Chrome" },
	{ 1181, "Front Bumper", "Slamin" },
	{ 1184, "Rear Bumper", "Chrome" },
	{ 1183, "Rear Bumper", "Slamin" },

	// Savanna
	{ 1189, "Front Bumper", "Chrome" },
	{ 1188, "Front Bumper", "Slamin" },
	{ 1187, "Rear Bumper", "Chrome" },
	{ 1186, "Rear Bumper", "Slamin" },

	// Tornado
	{ 1191, "Front Bumper", "Chrome" },
	{ 1190, "Front Bumper", "Slamin" },
	{ 1192, "Rear Bumper", "Chrome" },
	{ 1193, "Rear Bumper", "Slamin" },

	// stock sideskirts
	{ 1017, "Sideskirt", "Standard" },
	{ 1007, "Sideskirt", "Standard" },

	// Sultan
	{ 1027, "Sideskirt", "Alien" },
	{ 1026, "Sideskirt", "Alien" },
	{ 1030, "Sideskirt", "X-Flow" },
	{ 1031, "Sideskirt", "X-Flow" },

	// Elgy
	{ 1040, "Sideskirt", "Alien" },
	{ 1036, "Sideskirt", "Alien" },
	{ 1039, "Sideskirt", "X-Flow" },
	{ 1041, "Sideskirt", "X-Flow" },

	// Broadway
	{ 1042, "Sideskirt", "Chrome" },
	{ 1099, "Sideskirt", "Chrome" },

	// Flash
	{ 1051, "Sideskirt", "Alien" },
	{ 1047, "Sideskirt", "Alien" },
	{ 1052, "Sideskirt", "X-Flow" },
	{ 1048, "Sideskirt", "X-Flow" },

	// Statum
	{ 1062, "Sideskirt", "Alien" },
	{ 1056, "Sideskirt", "Alien" },
	{ 1063, "Sideskirt", "X-Flow" },
	{ 1057, "Sideskirt", "X-Flow" },

	// Jester
	{ 1071, "Sideskirt", "Alien" },
	{ 1069, "Sideskirt", "Alien" },
	{ 1072, "Sideskirt", "X-Flow" },
	{ 1070, "Sideskirt", "X-Flow" },

	// Uranus
	{ 1094, "Sideskirt", "Alien" },
	{ 1090, "Sideskirt", "Alien" },
	{ 1093, "Sideskirt", "X-Flow" },
	{ 1095, "Sideskirt", "X-Flow" },

	// Remington
	{ 1101, "Sideskirt", "`Chrome Flames`" },
	{ 1122, "Sideskirt", "`Chrome Flames`" },
	{ 1124, "Sideskirt", "`Chrome Arches`" },
	{ 1106, "Sideskirt", "`Chrome Arches`" },

	// Savanna
	{ 1102, "Sideskirt", "`Chrome Strip`" },
	{ 1133, "Sideskirt", "`Chrome Strip`" },

	// Blade
	{ 1107, "Sideskirt", "`Chrome Strip`" },
	{ 1108, "Sideskirt", "`Chrome Strip`" },

	// Slamvan
	{ 1120, "Sideskirt", "`Chrome Trim`" },
	{ 1118, "Sideskirt", "`Chrome Trim`" },
	{ 1121, "Sideskirt", "`Wheelcovers`" },
	{ 1119, "Sideskirt", "`Wheelcovers`" },

	// Tornado
	{ 1137, "Sideskirt", "`Chrome Strip`" },
	{ 1134, "Sideskirt", "`Chrome Strip`" },
	{ 1018, "Exhaust", "Upswept" },
	{ 1019, "Exhaust", "Twin" },
	{ 1020, "Exhaust", "Large" },
	{ 1021, "Exhaust", "Medium" },
	{ 1022, "Exhaust", "Small" },
	{ 1028, "Exhaust", "Alien" },
	{ 1029, "Exhaust", "X-Flow" },
	{ 1034, "Exhaust", "Alien" },
	{ 1037, "Exhaust", "X-Flow" },
	{ 1043, "Exhaust", "Slamin" },
	{ 1044, "Exhaust", "Chrome" },
	{ 1045, "Exhaust", "X-Flow" },
	{ 1046, "Exhaust", "Alien" },
	{ 1059, "Exhaust", "X-Flow" },
	{ 1064, "Exhaust", "Alien" },
	{ 1065, "Exhaust", "Alien" },
	{ 1066, "Exhaust", "X-Flow" },
	{ 1089, "Exhaust", "X-Flow" },
	{ 1092, "Exhaust", "Alien" },
	{ 1104, "Exhaust", "Chrome" },
	{ 1105, "Exhaust", "Slamin" },
	{ 1113, "Exhaust", "Chrome" },
	{ 1114, "Exhaust", "Slamin" },
	{ 1126, "Exhaust", "Chrome Exhaust" },
	{ 1127, "Exhaust", "Slamin Exhaust" },
	{ 1129, "Exhaust", "Chrome" },
	{ 1132, "Exhaust", "Slamin" },
	{ 1135, "Exhaust", "Slamin" },
	{ 1136, "Exhaust", "Chrome" },
	{ 1100, "Bullbar", "Chrome Grill" },
	{ 1109, "Rear Bullbars", "Chrome" },
	{ 1110, "Rear Bullbars", "Slamin" },
	{ 1115, "Front Bullbars", "Chrome" },
	{ 1116, "Front Bullbars", "Slamin" },
	{ 1117, "Front Bumper", "Chrome" },
	{ 1123, "Bullbars", "Bullbar Chrome Bars" },
	{ 1125, "Bullbars", "Bullbar Chrome Lights" },
	{ 1013, "Lamps", "Round Fog" },
	{ 1024, "Lamps", "Square Fog" },
	{ 1025, "Wheels", "Offroad" },
	{ 1073, "Wheels", "Shadow" },
	{ 1074, "Wheels", "Mega" },
	{ 1075, "Wheels", "Rimshine" },
	{ 1076, "Wheels", "Wires" },
	{ 1077, "Wheels", "Classic" },
	{ 1078, "Wheels", "Twist" },
	{ 1079, "Wheels", "Cutter" },
	{ 1080, "Wheels", "Switch" },
	{ 1081, "Wheels", "Grove" },
	{ 1082, "Wheels", "Import" },
	{ 1083, "Wheels", "Dollar" },
	{ 1084, "Wheels", "Trance" },
	{ 1085, "Wheels", "Atomic" },
	{ 1096, "Wheels", "Ahab" },
	{ 1097, "Wheels", "Virtual" },
	{ 1098, "Wheels", "Access" }
};

#define MOVE_ANIMATIONS_COUNT		27
const struct move_animation_info	move_animations[MOVE_ANIMATIONS_COUNT] =
{
	// ordered by eMoveAnim-ids (ascending)
	{ MOVE_PLAYER, "CJ" },
//	{ MOVE_PLAYER_F, "Player (F)" },
//	{ MOVE_PLAYER_M, "Player (M)" },
	{ MOVE_ROCKET, "Rocket" },
//	{ MOVE_ROCKET_F, "Rocket (F)" },
//	{ MOVE_ROCKET_M, "Rocket (M)" },
	{ MOVE_ARMED, "Armed" },
//	{ MOVE_ARMED_F, "Armed (F)" },
//	{ MOVE_ARMED_M, "Armed (M)" },
	{ MOVE_BBBAT, "Baseball" },
//	{ MOVE_BBBAT_F, "Baseball (F)" },
//	{ MOVE_BBBAT_M, "Baseball (M)" },
	{ MOVE_CSAW, "Chainsaw" },
//	{ MOVE_CSAW_F, "Chainsaw (F)" },
//	{ MOVE_CSAW_M, "Chainsaw (M)" },
	{ MOVE_SNEAK, "Sneak" },
	{ MOVE_JETPACK, "Jetpack" },
	{ MOVE_MAN, "Man" },
	{ MOVE_SHUFFLE, "Shuffle" },
	{ MOVE_OLDMAN, "Old (M)" },
	{ MOVE_GANG1, "Gang1" },
	{ MOVE_GANG2, "Gang2" },
	{ MOVE_OLDFATMAN, "Old fat (M)" },
	{ MOVE_FATMAN, "Fat (M)" },
	{ MOVE_JOGGER, "Jogger (M)" },
	{ MOVE_DRUNKMAN, "Drunk" },
	{ MOVE_BLINDMAN, "Woozie" },
	{ MOVE_SWAT, "SWAT" },
	{ MOVE_WOMAN, "Woman" },
	{ MOVE_SHOPPING, "Shopping" },
	{ MOVE_BUSYWOMAN, "Busy (F)" },
	{ MOVE_SEXYWOMAN, "Sexy (F)" },
	{ MOVE_PRO, "Pro" },
	{ MOVE_OLDWOMAN, "Old (F)" },
	{ MOVE_FATWOMAN, "Fat (F)" },
	{ MOVE_JOGWOMAN, "Jogger (F)" },
	{ MOVE_OLDFATWOMAN, "Old fat (F)" },
//	{ MOVE_SKATE, "Skate" }, /needs to be loaded from some not always loaded file?
};

// this blows the doors off Microsoft's version, mmmmkay
int									isBadPtr_GTA_pVehicle ( vehicle_info *p_VehicleInfo );
int									isBadPtr_GTA_pVehicle ( CVehicle *p_CVehicle );
int									isBadPtr_GTA_pVehicle ( CVehicleSA *p_CVehicleSA );
int									isBadPtr_GTA_pVehicle ( CVehicleSAInterface *p_CVehicleSAInterface );
int									isBadPtr_GTA_pPed ( actor_info *p_ActorInfo );
int									isBadPtr_GTA_pPed ( CPed *pCPed );
int									isBadPtr_GTA_pPed ( CPedSAInterface *pCPedSAInterface );
int									isBadPtr_GTA_pBuildingInfo ( DWORD p_BuildingInfo );
int									isBadPtr_GTA_pObjectInfo ( DWORD p_ObjectInfo );
bool								isBadPtr_handlerAny ( void *pointer, ULONG size, DWORD dwFlags );
bool								isBadPtr_readAny ( void *pointer, ULONG size );
bool								isBadPtr_writeAny ( void *pointer, ULONG size );

// oldschool pool
uint32_t							GetFromPool ( DWORD value, DWORD Pool, DWORD function );

// gta SCM stuff
extern inline int					ScriptCarId ( struct vehicle_info *mecar );
extern inline int					ScriptActorId ( struct actor_info *meactor );
extern inline int					ScriptObjectId ( struct object_info *object );
extern inline struct vehicle_info	*GetVehicleByGtaId ( int car_id );
extern inline struct actor_info		*GetActorByGtaId ( int actor_id );
extern inline struct object_info	*GetObjectByGtaId ( int object_id );

// functions to get/set certain things
// this should be phased out in favor of MTA/R* classes
void								gta_weather_state_set ( int state );
void								gta_time_hour_set ( int hour );
void								gta_money_set ( uint32_t amount );
uint32_t							gta_money_get ( void );
void								gta_game_speed_set ( float value );
float								gta_game_speed_get ( void );
void								gta_gravity_set ( float value );
float								gta_gravity_get ( void );
struct checkpoint					*gta_checkpoint_info_get ( int n );
int									gta_menu_active ( void );
void								gta_menu_active_set ( int enabled );
const struct weapon_entry			*gta_weapon_get_by_name ( const char *name );
void								gta_weapon_set ( struct actor_info *info, int slot, int id, int ammo, int ammo_clip );
int									gta_weapon_ammo_set ( struct actor_info *info, int slot, int ammo );
int									gta_weapon_ammo_clip_set ( struct actor_info *info, int slot, int ammo_clip );
const char							*gta_vehicle_class_name ( int id );
const struct vehicle_entry			*gta_vehicle_get_by_id ( int id );
void								gta_vehicle_spawn ( int vehicle_id );
void								gta_jetpack_give ( void );
int									gta_interior_id_get ( void );
void								gta_interior_id_set ( int id );
void								gta_blow_all_cars ();
struct actor_info					*actor_info_get ( int id, int flags );
struct vehicle_info					*vehicle_info_get ( int id, int flags );

// called by TIME_GET macro
uint64_t							__time_get ( void );

// m0d functions, eventually some of this will become part of the m0d framework
void								cheat_state_text ( const char *fmt, ... );
void								cheat_teleport_history_save ( void );

// more gta functions
void								vehicle_detachables_teleport ( struct vehicle_info *info, const float from[3],
																   const float to[3] );
void								cheat_vehicle_tires_set ( struct vehicle_info *info, uint8_t tire_status );
int									vehicle_contains_trailer ( struct vehicle_info *info,
															   const struct vehicle_info *trailer );
int									vehicle_contains_actor ( struct vehicle_info *vehicle, struct actor_info *actor );
void								vehicle_state_store ( const struct vehicle_info *info, struct vehicle_state *state );
void								vehicle_state_restore ( struct vehicle_info *info, const struct vehicle_state *state );
void								vehicle_prevent_below_height ( struct vehicle_info *info, float height );
int									vehicle_find ( int id, int dir, int flags );
int									actor_find ( int id, int dir, int flags );
int									vehicle_find_nearest ( int flags );
int									vehicle_filter_flags ( vehicle_info *info, int flags );
int									actor_find_nearest ( int flags );
int									actor_find_nearest_ex(int flags, std::function<bool(actor_info *)> pred);

struct vehicle_info					*actor_vehicle_get ( const struct actor_info *info );
void								SetCloudsEnabled ( int iEnabled );
void								loadAllWeaponModels ( void );
void								loadSpecificModel ( int iModelID );

// ped animations
bool								pPedSelf_setMoveAnimation__array ( int move_animations__arrayId );
bool								isMoveAnimationIdValid ( int iAnimationID );
bool								pPedSelf_setMoveAnimation ( int iAnimationID );

// new vehicle types and upgrades
bool								vehicle_iModelID_IsValid ( int iModelID );
bool								vehicle_upgrade_iModelID_IsValid ( int iModelID );
eClientVehicleType					GetVehicleType ( int iModelID );
bool								isUpgradeCompatible ( int iModelID, vehicle_info *vinfo );
bool								GetSlotFromUpgrade ( int us, int &ucSlot );
bool								vehicle_iModelID_IsValid ( int iModelID );
void								vehicle_addUpgrade ( vehicle_info *vinfo, int iModelID );
vehicle_upgrade_info				get_cveh_upgrade_info ( int iModelID, int &iUpgradeInfoID );
int									vehicle_getPaintJob ( vehicle_info *vinfo );
void								vehicle_setPaintJob ( vehicle_info *vinfo, unsigned char new_paintjob );
int									vehicle_getColor0 ( vehicle_info *vinfo );
int									vehicle_getColor1 ( vehicle_info *vinfo );
void								vehicle_setColor0 ( vehicle_info *vinfo, int new_color );
void								vehicle_setColor1 ( vehicle_info *vinfo, int new_color );
RwColor								getVehicleColorRGB(unsigned int index);

// --------------------------------------------------------------------------------------------
int									memcpy_safe ( void *dest, const void *src, uint32_t len, int check = NULL, const void *checkdata = NULL);
int									memset_safe ( void *_dest, int c, uint32_t len );
int									memcmp_safe ( const void *_s1, const void *_s2, uint32_t len );

void								*dll_baseptr_get ( const char *dll_name );

void								str_split_free ( struct str_split *split );
struct str_split					*str_split ( const char *str, const char *ch );

size_t								strlcpy ( char *dst, const char *src, size_t size );
size_t								strlcat ( char *dst, const char *src, size_t size );

bool								findstrinstr ( char *text, char *find );

void								*memdup ( const void *src, int len );
uint8_t								*hex_to_bin ( const char *str );
bool								hex_is_valid( const std::string& hex );

extern const struct weapon_entry	weapon_list[];
extern const struct vehicle_entry	vehicle_list[VEHICLE_LIST_SIZE];
extern const struct interiors		interiors_list[];

// new functions making use of MTA/R* classes
CVehicle							*getSelfCVehicle ( void );
int									getVehicleGTAIDFromInterface ( DWORD *vehicle );
int									getPedGTAIDFromInterface ( DWORD *ped );
D3DXVECTOR3							CVecToD3DXVEC ( CVector vec );
