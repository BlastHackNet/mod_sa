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

// time for time
#define MSEC_TO_TIME( v )	( (uint64_t) (v) * 10 )
#define TIME_TO_FLOAT( v )	( (float)((double)(v) / (double)MSEC_TO_TIME(1000)) )
#define TIME_TO_DOUBLE( v ) ( (double)((double)(v) / (double)MSEC_TO_TIME(1000)) )

// main pool addresses
#define ACTOR_POOL_POINTER		0x00B74490
#define ACTOR_POINTER_SELF		0x00B7CD98
#define ACTOR_SELF				- 1
#define VEHICLE_POOL_POINTER	0x00B74494
#define VEHICLE_POINTER_SELF	0x00B6F980
#define VEHICLE_SELF			- 1
#define OBJECT_POOL_POINTER		0x00B7449C
#define BUILDING_POOL_POINTER	0x00B74498

// other addresses
#define GTA_KEYS	0xB73458

// CPed actor states
#define ACTOR_STATE_DRIVING		50
#define ACTOR_STATE_DYING		54
#define ACTOR_STATE_DEAD		55

#define ACTOR_MSTATE_STILL		1
#define ACTOR_MSTATE_RUN		6
#define ACTOR_MSTATE_RUN_FAST	7

// predefined vehicle & actor invulnerability flags
#define VEHICLE_FLAGS_INVULNERABLE	( 4 | 8 | 16 | 128 )
#define ACTOR_FLAGS_INVULNERABLE	( 4 | 8 | 64 | 128 )

// old vehicle_info vehicle types
#define VEHICLE_TYPE_CAR	0	/* + helicopters and planes */
#define VEHICLE_TYPE_BOAT	5
#define VEHICLE_TYPE_TRAIN	6
#define VEHICLE_TYPE_BIKE	9

// new vehicle types
enum eClientVehicleType
{
	CLIENTVEHICLE_NONE,
	CLIENTVEHICLE_CAR,
	CLIENTVEHICLE_BOAT,
	CLIENTVEHICLE_TRAIN,
	CLIENTVEHICLE_HELI,
	CLIENTVEHICLE_PLANE,
	CLIENTVEHICLE_BIKE,
	CLIENTVEHICLE_MONSTERTRUCK,
	CLIENTVEHICLE_QUADBIKE,
	CLIENTVEHICLE_BMX,
	CLIENTVEHICLE_TRAILER
};

// upgrade model ids
#define VEHICLEUPGRADE_NITRO_5X		1008
#define VEHICLEUPGRADE_NITRO_2X		1009
#define VEHICLEUPGRADE_NITRO_10X	1010
#define VEHICLEUPGRADE_HYDRAULICS	1087

// maximum passengers including driver
#define VEHICLE_MAX_PASSENGERS	9

// main cheat states
#define CHEAT_STATE_NONE	0
#define CHEAT_STATE_ACTOR	1
#define CHEAT_STATE_VEHICLE 2

// teleport pool sizes
#define TELEPORT_MAX		10
#define TELEPORT_HIST_MAX	10
#define STATIC_TELEPORT_MAX 200

/////////////////////////////
// MTA/R* Specific Defines //
/////////////////////////////
#define CPOOLS_PED_SELF_REF 1

/////////////////////////////////////
// RenderWare Variables & Pointers //
/////////////////////////////////////
#define __rwD3D9CPUSupportsMMX		0xC980A0	// int
#define __rwD3D9CPUSupportsSSE		0xC980A4	// int
#define __rwD3D9CPUSupportsSSE2		0xC980A8	// int
#define __rwD3D9CPUSupports3DNow	0xC980AC	// int
#define __RwD3DDevice				0xC97C28	// IDirect3DDevice9*

/*
#define		__RwD3D9D3D9ViewTransform	0xC9BC80 // D3DMATRIX
#define		__RwD3D9D3D9ProjTransform	0x8E2458 // VECTOR
#define		__RwD3D9ActiveViewProjTransform 0xC97C64 // D3DMATRIX*
#define		_D3D9Transform				0x8D7390 // D3DMATRIX
#define		_D3D9ActiveTransform		0xC94C70 // D3DMATRIX*
#define		_D3D9ActiveInverseTransform	0xC94C74 // D3DMATRIX*
#define		_D3D9ActiveInverseNormalizedTransform 0xC94C78 // D3DMATRIX*
#define		_D3D9ActiveNormalizedTransform 0xC94C7C // D3DMATRIX*
*/
//////////////////////////////
// GTA Variables & Pointers //
//////////////////////////////
#define GTAvar__windowsVersion	0xC8CF68		// int or VersionInformation struct
#define GTAvar__D3D9UseVersion	0xC94C00		// int
#define GTAvar__DXVersion		0xC8CF6C		// int
#define GTAvar__gameState		0xC8D4C0		// int
#define GTAvar_osPlatform		0xC9AC08		// int
#define GTAvar_osVer			0xC9AC0C		// int
#define GTAvar_winVer			0xC9AC10		// int
#define GTAvar_winMajor			0xC9AC14		// int
typedef struct _VECTOR
{
#pragma pack( 1 )
	float	X, Y, Z;
} VECTOR, *PVECTOR;

typedef struct _MATRIX4X4
{
#pragma pack( 1 )
	VECTOR	right;
	DWORD	flags;
	VECTOR	up;
	float	pad_u;
	VECTOR	at; // front
	float	pad_a;
	VECTOR	pos;
	float	pad_p;
} MATRIX4X4, *PMATRIX4X4;

struct cheat_state_actor
{
	float	coords[3];
	int		invulnerable;
	int		air_brake;
	int		air_brake_slowmo;
	int		stick;
	int		autoaim;
	int		hp_regen_on;
	int		SpiderFeet_on;
	int		SpiderFeet_Enabled;
	bool	fly_on;
	bool	fly_enabled;
	bool	fly_active;
	bool	surf;
};

struct cheat_state_vehicle
{
	float	coords[3];
	int		invulnerable;
	int		air_brake;
	int		air_brake_slowmo;
	int		stick;
	int		protection;
	int		hp_tire_support;
	int		hp_minimum_on;
	int		hp_regen_on;
	int		keep_trailer_attached;
	int		brkdance;
	int		is_engine_on;
	int		infNOS_toggle_on;
	int		spiderWheels_Enabled;
	int		spiderWheels_on;
	int		blinking_carlights_state;
	int		blinking_carlights_turnstate;
	DWORD	blinking_carlights_lastblink;
	int		fly;
	bool	freezerot;
};

struct cheat_state_teleport
{
	int		set;
	float	matrix[16];
	int		interior_id;
};

struct cheat_state_generic
{
	int		hp_cheat;
	int		money;
	int		weapon;
	int		map;
	int		map_vehicles;
	int		menu;
	int		menu_mousecontrol;
	int		spoof_weapon;	/* set to the weapon type id */
	int		vehicles_unlock;
	int		vehicles_warp_invert;
	int		vehicles_freeze;
	int		vehicles_warpinside;
	int		weapon_disable;

	int		onfoot_data;
	int		aim_data;
	int		vehicle_data;
	int		passenger_data;
	int		statsupd;
	int		spec_data;

	int		teletext;

	DWORD	rejoinTick;
	DWORD	join_serverTick;

	int		pickuptexts;
	int		objecttexts;

	bool	car_jacked;
	DWORD	anti_carjackTick;
	short	car_jacked_last_vehicle_id;
	bool	got_vehicle_id;
	float	car_jacked_lastPos[3];

	struct vehicle_info * pVehicleExit_Last;

	int		interior_patch_enabled;

	int		nocols_enabled;			/* vehicle collision */
	int		nocols_walls_enabled;	/* wall/object collision */

	int		cheat_panic_enabled;

	int		unrelatedToAnything;
};

struct cheat_state_hooks
{
	// i'm a dummy
	bool	dummy;
};

#define DEBUG_DATA_SIZE 320
#define DEBUG_HIST_LEN	100

struct debug_info
{
	int			data_type;	/* 0 byte, 1 word, 2 dword, 3 float */

	int			hist_pos;
	uint8_t		*ptr[DEBUG_HIST_LEN];
	int			offset[DEBUG_HIST_LEN];

	uint8_t		data[DEBUG_DATA_SIZE];
	uint8_t		data_prev[DEBUG_DATA_SIZE];
	uint32_t	modify_time[DEBUG_DATA_SIZE];

	int			data_prev_clear;

	uint8_t		cursor_data[sizeof( void * )];
	char		ptr_hist_str[64];
};

struct cheat_state
{
	int							state;	/* CHEAT_STATE_* */
	struct cheat_state_actor	actor;
	struct cheat_state_vehicle	vehicle;
	struct cheat_state_generic	_generic;
	struct cheat_state_hooks	hooks;
	struct cheat_state_teleport teleport[TELEPORT_MAX];
	struct cheat_state_teleport teleport_hist[TELEPORT_HIST_MAX];
	int							teleport_hist_count;
	int							debug_enabled;
	struct debug_info			debug;
	float						game_speed;
	int							text_time;
	char						text[128];
	int							player_info_list;
	int							render_player_tags;
	int							render_vehicle_tags;
};

struct pool
{
#pragma pack( 1 )
	void	*start;		/* pointer to start of pool */
	void	*__end;		/* end of this structure? (not the pool) */
	int32_t size;		/* max number of items in the pool */
	/* there's some more junk after this */
};

struct detachable
{
#pragma pack( 1 )
	float	position[3];
	uint8_t __unknown_12[4];
	float	vector[3];
	uint8_t __unknown_28[16];
};

struct weapon
{
#pragma pack( 1 )
	uint32_t	id;
	uint32_t	state;
	int32_t		ammo_clip;
	int32_t		ammo;
	uint32_t	__unknown_count;
	uint32_t	__goggle;	/* 0 off, 256 on */
	uint32_t	__unknown;
};

// object_base is now unioned with a CEntity pointer where applicable
struct object_base
{
#pragma pack( 1 )
	CEntitySAInterfaceVTBL	*vtbl;	// 0

	// this is now in CEntity
	//	CPlaceableSAInterface	Placeable;	// 4
	// but the following variables exist for compatability till we remove object_base completely
	float					coords[3];			// 4
	union
	{
		// is MTA right?
		float			m_heading;				// 16

		// and are we wrong?
		CMatrix_Padded	*m_CMatrixPre;			// 16, a part of CPlaceable
		float			*preMatrix;				// 16, a part of CPlaceable
		MATRIX4X4		*preMatrixStruct;		// 16, a part of CPlaceable
	};
	union
	{
		CMatrix_Padded	*m_CMatrix;				// 20
		float			*matrix;				// 20
		MATRIX4X4		*matrixStruct;			// 20
	};

	RpClump			*m_pRwObject;				// 24

	/********** BEGIN CFLAGS **************/
	unsigned long	bUsesCollision : 1;			// does entity use collision
	unsigned long	bCollisionProcessed : 1;	// has object been processed by a ProcessEntityCollision function
	unsigned long	bIsStatic : 1;			// is entity static
	unsigned long	bHasContacted : 1;		// has entity processed some contact forces
	unsigned long	bIsStuck : 1;			// is entity stuck
	unsigned long	bIsInSafePosition : 1;	// is entity in a collision free safe position
	unsigned long	bWasPostponed : 1;		// was entity control processing postponed
	unsigned long	bIsVisible : 1;			//is the entity visible
	unsigned long	bIsBIGBuilding : 1;		// Set if this entity is a big building
	unsigned long	bRenderDamaged : 1;		// use damaged LOD models for objects with applicable damage
	unsigned long	bStreamingDontDelete : 1;	// Dont let the streaming remove this
	unsigned long	bRemoveFromWorld : 1;		// remove this entity next time it should be processed
	unsigned long	bHasHitWall : 1;			// has collided with a building (changes subsequent collisions)
	unsigned long	bImBeingRendered : 1;		// don't delete me because I'm being rendered
	unsigned long	bDrawLast : 1;			// draw object last
	unsigned long	bDistanceFade : 1;		// Fade entity because it is far away
	unsigned long	bDontCastShadowsOn : 1; // Dont cast shadows on this object
	unsigned long	bOffscreen : 1;			// offscreen flag. This can only be trusted when it is set to true
	unsigned long	bIsStaticWaitingForCollision : 1;	// this is used by script created entities - they are static until the collision is loaded below them
	unsigned long	bDontStream : 1;			// tell the streaming not to stream me
	unsigned long	bUnderwater : 1;			// this object is underwater change drawing order
	unsigned long	bHasPreRenderEffects : 1;	// Object has a prerender effects attached to it
	unsigned long	bIsTempBuilding : 1;		// whether or not the building is temporary (i.e. can be created and deleted more than once)
	unsigned long	bDontUpdateHierarchy : 1;	// Don't update the aniamtion hierarchy this frame
	unsigned long	bHasRoadsignText : 1;		// entity is roadsign and has some 2deffect text stuff to be rendered
	unsigned long	bDisplayedSuperLowLOD : 1;
	unsigned long	bIsProcObject : 1;			// set object has been generate by procedural object generator
	unsigned long	bBackfaceCulled : 1;		// has backface culling on
	unsigned long	bLightObject : 1;			// light object with directional lights
	unsigned long	bUnimportantStream : 1;		// set that this object is unimportant, if streaming is having problems
	unsigned long	bTunnel : 1;			// Is this model part of a tunnel
	unsigned long	bTunnelTransition : 1;	// This model should be rendered from within and outside of the tunnel

	/********** END CFLAGS **************/
	uint8_t			wSeedColFlags;			// 32
	uint8_t			wSeedVisibleFlags;		// 33
	uint16_t		model_alt_id;			// 34 - model index
	uint8_t			__unknown_36[4];		// 36 - collision related (objects only?)

	//CReferences *pReferences; //36
	uint32_t		*m_pLastRenderedLink;	// 40 CLink<CEntity*>* m_pLastRenderedLink;
	uint16_t		timer;			// 44
	uint8_t			m_iplIndex;		// 46 used to define which IPL file object is in
	uint8_t			interior_id;	// 47
	uint8_t			__unknown_48[6];		// 48

	//********* BEGIN CEntityInfo **********//
	uint8_t			nType : 3;				// 54 what type is the entity (2 == Vehicle)
	uint8_t			nStatus : 5;			// 54 control status

	// 55 alignment
	//********* END CEntityInfo **********//
	uint8_t			__unknown_56[8];		// 56
	uint8_t			quantumPhysics;			// 64 // this really needs to be figured out cos it's probably a bit field
	uint8_t			nImmunities;			// 65
	uint8_t			__unknown_66;			// 66
};

struct actor_info
{
#pragma pack( 1 )
	struct object_base	base;				/* 0-65 */
	uint8_t				flags;				/* 66 immunities */
	uint8_t				__unknown_67[1];	/* 67 */
	union	/* 68 */
	{
		struct
		{
			CVector m_SpeedVec;
		};
		float	speed[3];
		struct
		{
			D3DXVECTOR3 m_SpeedD3DVec;
		};
	};
	float				spin[3];			/* 80 */
	float				speed_rammed[3];	/* 92 */
	float				spin_rammed[3];		/* 104 */
	uint8_t				__unknown_116[60];	/* 116 */
	void				*__unknown_176;		/* 176 - pointer to a "entry node info" pool item */
	void				*__unknown_180;		/* 180 - pointer to a "ptr node Double" pool item */

	//collision data
	DWORD				collision_flags;	/* 184 - 2nd byte = currently colliding 1/0, or actively
										  running against (0x2), 3rd byte = type colliding with
										  (1 = road, 4=pavement, 35 = object, 3f=car).. unsure about 3rd byte

										  nuck notes: 186 is used to tell if a surface is "steep" too,
										  actually any slight angle at all
										  */
	void				*last_touched_object;	/* 188 - You can touch roads - those are considered buildings */
	void				*last_collided_object;	/* 192 - pointer to object last collided with (on foot, not jetpack) */
	uint8_t				__unknown_196[16];		/* 196 */
	float				speed_z;			/* 212 */
	float				collision_time_216; /* 216 - collision timer? */
	void				*collision_current_obj;		/* 220 - pointer to current thing colliding with */
	uint8_t				collision_something[12];	/* 224 - related to collision */
	float				collision_last_coord[3];	/* 236 - coordination of last collision */

	//end of collision data
	uint8_t				__unknown_248[100];			/* 248 */
	// 252 - animation related
	uint8_t				animation_state;			/* 348 */
	uint8_t				__unknown_349[7];			/* 349 */
	float				step_pos[3];		/* 356 - coordinates, last foot step */
	float				step_pos_before[3]; /* 368 - coordinates, foot step before last one */
	uint8_t				__unknown_380[752]; /* 380 */

	CPedFlags			pedFlags;			/* 1132 */
	CPedIntelligenceSAInterface *pPedIntelligence; /* 1148 */
	CPlayerPedDataSAInterface *pPlayerData; /* 1152 */

	uint8_t				__unknown_1156[8]; /* 1156 */

	// relative body-part-positions
	void				*pNeck;				/* 1164 - void* pNeck
	  (pChest?)
	   - 4 unknown
	   - float height
	   - float front/back
	   - float left/right
	   - void* pObject
	   (same struct for the following body-part-pointers [except pLeft/RightArm])
	*/
	void				*pHead;				/* 1168 */
	void				*pLeftArm;			/* 1172 */
	void				*pRightArm;			/* 1176 */
	void				*pLeftLowArm;		/* 1180 */
	void				*pRightLowArm;		/* 1184 */
	void				*pLeftLeg;			/* 1188 */
	void				*pRightLeg;			/* 1192 */
	void				*pLeftLowLeg;		/* 1196 */
	void				*pRightLowLeg;		/* 1200 */
	void				*pRightMidLeg;		/* 1204 */
	void				*pLeftMidLeg;		/* 1208 */
	void				*pLeftMidArm;		/* 1212 */
	void				*pRightMidArm;		/* 1216 */
	void				*pLeftShoulder;		/* 1220 */
	void				*pRightShoulder;	/* 1224 */
	void				*pChest;			/* 1228 */
	void				*pMouth;			/* 1232 */
	// end of body-part-positions

	uint8_t				runningStyle;		/* 1236 - 0x36 = cj, 0x8A = rollerskate,
									0x7F = woozie, 0x75 = crash.. etc. */
	uint8_t				__unknown_1237[7];	/* 1237 */
	float				runspeed;			/* 1244 */
	uint8_t				__unknown_1248[36]; /* 1248 */
	uint16_t			muzzle_flash;		/* 1284 */
	uint8_t				__unknown_1286[6];	/* 1286 */

	CPedIKSAInterface	pedIK;	/* 1292 - Inverse Kinematics */
	uint8_t				__unknown_1324[4];	/* 1324 */

	uint32_t			state;	/* 1328 - ACTOR_STATE_* */
	uint32_t			mstate; /* 1332 - ACTOR_MSTATE_* */
	uint8_t				__unknown_1336[8];	/* 1336 */
	float				hitpoints;			/* 1344 */
	float				hitpoints_max;		/* 1348 - hmm, does not seem to be right.. it's set to "100.1318519" or something like that */
	float				armor;	/* 1352 */
	uint8_t				__unknown_1356[12];		/* 1356 */

	// 1360 and 1364 are using in resetting on-foot position when re-standing up

	float				fCurrentRotation;		/* 1368 */
	float				fTargetRotation;		/* 1372 */
	float				fRotationSpeed;			/* 1376 */
	float				fRotationCalculation;	/* 1380 - is 0.1 when target rotation reached */

	union
	{
		CEntitySAInterface	*pContactEntity;	/* 1384 - touching a CEntitySAInterface */
		struct vehicle_info *vehicle_contact;	/* 1384 - standing on top of vehicle */
	};

	float	vehicle_contact_dist[3];			/* 1388 - distance to the middle of the car standing on */
	float	fPlaneAnglesContactEntity[3];		/* 1400 - Angles of the plane of the contact entity the actor is
													standing on (?) */
	void	*item_contact;						/* 1412 - standing on top of vehicle/object/building/...*/
	float	fUnknown_1416;						/* 1416 - only changing when slightly under map */

	union
	{
		//CEntitySAInterface	*CurrentObjective;	/* 1420 - usually current vehicle's entity */
		struct vehicle_info *vehicle;
	};

	uint8_t				__unknown_1424[8];	/* 1424 */
	uint8_t				actor_lock;			/* 1432 */
	uint8_t				__unknown_1433[7];	/* 1433 */
	struct weapon		weapon[13];			/* 1440 */
	uint8_t				__unknown_1804[12]; /* 1804 */
	uint8_t				weapon_slot;		/* 1816 */
	uint8_t				__unknown_1817[3];	/* 1817 */
	void				*ptr_autoAimTarget;	/* 1820 - weapon target */
	float				fImpactPos_close[3];/* 1824 - last impact point of close range weapon [fist/knife/csaw/etc.] */
	uint8_t				__unknown_1836[20]; /* 1836 */
	uint32_t			weapon_model;		/* 1856 */
	uint8_t				__unknown_1860[28]; /* 1860 */
	uint32_t			weapon_hit_type;	/* 1888 - last hit by this weapon */
	struct actor_info	*weapon_hit_by;		/* 1892 - last hit by this object (usually an actor) */
	uint8_t				__unknown_1889[92]; /* 1896 */
};	/* 1988 */

struct vehicle_info
{
#pragma pack( 1 )
	struct object_base	base;
	uint8_t				flags;			/* 66 - flags */
	uint8_t				__unknown_67;	/* 67 */
	union	/* 68 */
	{
		struct
		{
			CVector m_SpeedVec;
		};
		float	speed[3];
	};
	union	/* 80 */
	{
		struct
		{
			CVector m_SpinVec;
		};
		float	spin[3];
	};
	float						speed_rammed[3];	/* 92 - speed from collision, will be added to speed[3] */
	float						spin_rammed[3];		/* 104 - spin from collision, will be added to spin[3] */

	uint8_t						__unknown_116[20];	/* 116 */

	// handling should start here
	uint8_t						__unknown_136[4];	/* 136 */
	float						mass;		/* 140 - vehicle mass from handling.cfg */
	float						turn_mass;	/* 144 - turn mass */
	float						grip_div;	/* 148 - grip divisor */
	float						mass_to_grip_mult;		/* 152 - mass to grip multiplier */
	float						fTurnMass;				/* 156 - 0.05 or 0.1 */
	float						grip_level_norm;		/* 160 - normalized grip level */
	float						center_of_mass[3];		/* 164 - center of mass */
	void						*__unknown_176;			/* 176 - pointer to a "entry node info" pool item */
	void						*__unknown_180;			/* 180 - pointer to a "ptr node Double" pool item */

	//collision data
	DWORD						collision_flags;		/* 184 - 2nd byte = currently colliding 1/0, or actively
										  running against (0x02), being moved/rammed (0x03), 1st byte = 0, if noone inside and colliding
										  with actor, else ever 0x0a*/
	void						*last_touched_object;	/* 188 - You can touch roads - those are considered buildings */
	void						*last_collided_object;	/* 192 - pointer to last collided object.. not for ALL collisions?!? */
	uint8_t						__unknown_196[20];		/* 196 */
	float						collision_something;	/* 216 - collision timer?*/
	void						*collision_current_obj; /* 220 - pointer to current thing colliding with */

	// end of handling should be here
	uint8_t						__unknown_224[12];		/* 224 */
	float						collision_position[3];	/* 236 - last collision coordinates */
	uint8_t						__unknown_248[68];		/* 248 */
	void						*__unknown_316;			/* 316 - pointer to this something in this structure */
	uint8_t						__unknown_320[157];		/* 320 */
	uint8_t						in_vehicle;			/* 477 */
	uint8_t						__unknown_478[422]; /* 478 */

	tHandlingDataSA				*pHandlingData;		/* 900 */
	struct physicalFlyParams	*pFlyData;			/* 904 */
	uint8_t						__unknown_908[96];	/* 908 */
	uint32_t					hFlagsLocal;		/* 1004 */
	uint8_t						__unknown_1008[56]; /* 1008 - AutoPilot */
	CVehicleFlags				m_nVehicleFlags;	/* 1064 - 60 bits/flags */
	uint32_t					m_TimeOfCreation;	/* 1072 - GetTimeInMilliseconds when this vehicle was created. */

	uint8_t						color[4];			/* 1076 - as in carcolors.dat - body, stripe, body2, stripe2 */
	uint8_t						modding[2];			/* 1080 - modding data */
	unsigned short				UpgradeModelID[15];	/* 1082 - attached upgrades */
	float						wheel_size;			/* 1112 */
	unsigned short				CarAlarmState;		/* 1116 - time left for car alarm to sound in ms */
	unsigned short				ForcedRandomSeed;	/* 1118 - if this is non-zero the random wander gets deterministic */
	struct actor_info			*passengers[9];		/* 1120 (pointer to the passenger player structs) */

	unsigned char				m_nNumPassengers;	/* 1156 */
	unsigned char				m_nNumGettingIn;	/* 1157 */
	unsigned char				m_nGettingInFlags;	/* 1158 */
	unsigned char				m_nGettingOutFlags; /* 1159 */
	unsigned char				m_nMaxPassengers;	/* 1160 */
	unsigned char				m_windowsOpenFlags; /* 1161 */
	char						m_nNitroBoosts;		/* 1162 */
	char						m_nSpecialColModel; /* 1163 */
	DWORD						*pEntityWeAreOnForVisibilityCheck;	/* 1164 - we need a CEntity */
	DWORD						*m_pFire;			/* 1168 - CFire*/

	float						steer_angles[2];	/* 1172 - steer angles */
	float						gas_pedal;			/* 1180 - gas pedal */
	float						break_pedal;		/* 1184 - break pedal */

	// 1188
	unsigned char				VehicleCreatedBy;	// Contains information on whether this vehicle can be deleted or not. Probably only need this or IsLocked.
	short						ExtendedRemovalRange;

	// this padding probably isn't in the right place.
	uint8_t						__unknown_1191;

	//1192
	unsigned char				car_bomb : 3;		// 0 = None. 1 = Timed. 2 = On ignition, 3 = remotely set ? 4 = Timed Bomb has been activated. 5 = On ignition has been activated.
	unsigned char				OverrideLights : 2; // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
	unsigned char				WinchType : 2;		// Does this vehicle use a winch?

	// this padding probably isn't in the right place.
	uint8_t						__unknown_1193;

	//1194
	unsigned char				m_GunsCycleIndex : 2;		// Cycle through alternate gun hardpoints on planes/helis
	unsigned char				m_OrdnanceCycleIndex : 2;	// Cycle through alternate ordnance hardpoints on planes/helis

	// 1195
	unsigned char				nUsedForCover;			// Has n number of cops hiding/attempting to hid behind it
	unsigned char				AmmoInClip;				// Used to make the guns on boat do a reload.
	unsigned char				PacMansCollected;
	unsigned char				PedsPositionForRoadBlock;
	unsigned char				NumPedsForRoadBlock;

	//1200
	float						nBodyDirtLevel;			// Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible, it may be altered at any time while vehicle's cycle of lige

	// values used by transmission
	unsigned char				m_nCurrentGear;			/* 1204 */
	float						m_fGearChangeCount;		/* 1205 */
	float						m_fWheelSpinForAudio;	/* 1209 */
	uint8_t						__unknown_1213[3];		/* 1213 */

	float						hitpoints;			/* 1216 */
	void						*pulling_truck;		/* 1220 - vehicle_info - pulling truck */
	struct vehicle_info			*trailer;			/* 1224 - pointer to the currently attached trailer; 0 if theres no trailer */
	uint8_t						__unknown_1228[44]; /* 1228 */
	uint32_t					door_status;		/* 1272 - car door status (1:Opened 2:Locked) */
	uint8_t						__unknown_1276[148];	/* 1276 */
	uint8_t						vehicle_type;			/* 1424 - VEHICLE_TYPE_* */
	uint8_t						__unknown_1425[19];		/* 1425 */

	union
	{
		struct
		{
			float	m_fTrainSpeed;			/* 1444 - Train speed along rails */
			float	m_fTrainRailDistance;	/* 1448 - Distance along rail starting from first rail node (determines train position when on rails) -max 18106 */
			float	m_fDistanceToNextCarriage;		/* 1452 - Distance to Carriage being infront of this */
		};
		struct
		{
			uint8_t boat_sound_level;				/* 1444 */
			uint8_t car_tire_status[4];				/* 1445 - LF, LR, RF, RR, 0 = ok, 1 = flat, 2 = landing gear up */
			uint8_t door_damage_status[6];			/* 1449 - damage status of doors, 0 = ok, 2 = damaged, 3 = open free, 4 = lost */
		};
	};

	// light damage states
	//uint8_t			lights;						/* 1456 - Light status, 0 = no dmg, 1 = front left dmg, 4 = front right dmg, 5 = front dmg, ...+0x40 = ...+back dmg */
	unsigned char		lights_status_frontLeft : 1;
	unsigned char		__unknown_lights_status_2 : 1;
	unsigned char		lights_status_frontRight : 1;
	unsigned char		__unknown_lights_status_4 : 3;
	unsigned char		lights_status_rear : 1;

	// end of light damage states
	uint8_t				__unknown_1457[3];			/* 1457 - 1475 related to doorHood (byte??)*/

	// misc damage states
	unsigned char		car_status_left : 4;		/* 1460 - 0 = ok, 1 = damaged, 2 = free movement, 3 = lost - same status codes for following bumper/windshield */
	unsigned char		car_status_right : 4;
	uint8_t				car_bumper_status;			/* 1461 - unknown */
	unsigned char		car_windshield_status : 4;
	unsigned char		car_bumper_status_front : 4;
	uint8_t				car_bumper_status_rear;
	// end of misc damage states

	CTrainFlags			m_trainFlags;				/* 1464 */
	uint8_t				__unknown_1468[8];			/* 1468 */
	float				doorHood_dist;				/* 1476 - positive = open */
	uint8_t				__unknown_1480[4];			/* 1480 - detachable related*/
	float				doorHood_dist_two;			/* 1484 - positive = open*/
	uint8_t				__unknown_1488[4];			/* 1488 */
	struct vehicle_info *m_train_next_carriage;		/* 1492 */
	uint8_t				__unknown_1496[4];			/* 1496 */
	float				doorTrunk_dist;				/* 1500 - negative = open */
	uint8_t				__unknown_1504[4];			/* 1504 */
	float				doorTrunk_dist_two;			/* 1508 - negative = open */
	uint8_t				__unknown_1512[12];			/* 1512 */
	float				doorOne_dist;				/* 1524 - also for movable part of boats (marquis)*/
	uint8_t				__unknown_1528[4];			/* 1528 */
	union
	{
		struct detachable	detachable_bike1[1];	/* 1532 - bike/motorcycle/car part */
		struct
		{
			float	doorOne_dist_two;			/* 1532 - negative = open */
			uint8_t __unknown_1536[12];			/* 1536 */
			float	doorTwo_dist;				/* 1548 - positive = open */
			uint8_t __unknown_1552[4];			/* 1552 */
			float	doorTwo_dist_two;			/* 1556  - positive = open */
			uint8_t __unknown_1560[12];			/* 1560 */
			float	doorThree_dist;				/* 1572 - negative = open */
			uint8_t __unknown_1576[4];			/* 1576 */
			float	doorThree_dist_two;			/* 1580 - negative = open */
			uint8_t __unknown_1584[12];			/* 1584 */
			float	doorFour_dist;				/* 1596 - positive = open */
			uint8_t __unknown_1600[6];			/* 1600 */
			float	doorFour_dist_two;			/* 1606 - positive = open */
		};
	};
	uint8_t				__unknown_1610[18];		/* 1610 */
	uint8_t				bike_tire_status[2];	/* 1628 Front, Rear, 0 = ok, 1 = flat */
	uint8_t				__unknown_1630[2];		/* 1630 */

	//maybe also door positions in here, like in 15xx?
	struct detachable	detachable_bike2[4];	/* 1632 - bike/motorcycle and boat parts */
	uint8_t				__unknown_1808[8];		/* 1808 */
	float				fPos_FireCarLadder[3];	/* 1816 - train ladder positioning (part of detachables?) */
	struct detachable	detachable_car[4];		/* 1828 - car/helicopter/airplane parts */
	uint8_t				__unknown_2004[12];		/* 2004 */
	float				suspension[4];			/* 2016 - FL, RL, FR, RR suspension height */
	uint8_t				__unknown_2032[244];	/* 2032 */
	float				burn_timer;				/* 2276 - burn timer counting up from 0.0f */
	uint8_t				__unknown_2280[100];	/* 2280 */
	float				fCannonAimX_Y[2];		/* 2380 - cannon offset (x/y) */
	uint8_t				__unknown_2388[48];		/* 2388 */
	float				fHeliDistanceToGround;	/* 2436 - (between 0.9 and 1 = touching ground) */
	uint8_t				__unknown_2440[24];		/* 2440 */
	float				fHeliMainRotorDistance;	/* 2464 - distance/rotation */
	float				fHeliSecRotorDistance;	/* 2468 - distance/rotation secondary rotor */
	uint8_t				__unknown_2472[88];		/* 2472 */
	uint8_t				SmokeTrailEnabled;		/* 2560 */
	uint8_t				__unknown_2561[23];		/* 2561 */
	/* 2584 */
};

struct object_info
{
#pragma pack( 1 )
	struct object_base	base;
	uint8_t				__unknown_66;			/* 66 */
	uint8_t				flags;	/* 67 - collision and ...? */
	uint8_t				__unknown_68[7];	/* 68 */
	float				physical_height;	/* 75 - normally max. 0.2 (bigger value = more 'ouch' when jumping), different results for different objects? */
	uint8_t				__unknown_79[173];	/* 79 - first value changing when last movement was going up or going down*/
	struct actor_info	*actor; /* 252 - pointer to Actor Object is attached to, 0 when not attached */
	uint8_t				__unknown_256[8];	/* 256 */
	float				height_to_actor;	/* 264 - when attached height difference to actor, else 0*/
	uint8_t				__unknown_268[4];	/* 268 */
	float				pitch;	/* 272 - rotation, pitch (attached) */
	float				roll;	/* 276 - rotation, roll (attached) */
	uint8_t				__unknown_280[68];	/* 280 */
	float				scale;	/* 348 - Scale */
	uint8_t				__unknown_352[59];	/* 352 */
};

//Only for flying
struct physicalFlyParams
{
#pragma pack( 1 )
	float	__itsNull;	/* 0 */
	float	heightIncreaseRel[2];	/* 4 - Related to (Heli only?) height */
	float	circleAround;			/* 12 - Heli/Plane */
	float	changeDir;		/* 16 - Speed changing Direction (negative = change against the speed vector) */
	float	changeDir_side; /* 20 */
	float	roll_lr;		/* 24 */
	float	__unknown_28;	/* 28 */
	float	pitch;			/* 32 */
	float	__unknown_36;	/* 36 */
	float	_multPitch;		/* 40 - pitch related */
	float	finalPitch_;	/* 44 */
	float	_unknownMultipliers_isOne[2];	/* 48 */
	float	_orientationMultiplier;			/* 56 - somehow orientation related */
	float	_SpeedMultiplier_isOne;			/* 60 */
	float	pitchMultiplier;	/* 64 - keep it >0 */
	float	rollMultiplier;		/* 68 */
	float	circleMultiplier;	/* 72 */
	//following values = global for all vehs (?)
};

struct checkpoint
{
#pragma pack( 1 )
	uint32_t	__unknown1;		/* Dunno, but I'm guessing the type of checkpoint is stored here */
	uint32_t	counter;		/* Some sort of counter. */
	uint32_t	color;			/* RGBA color value */
	uint32_t	__unknown2;		/* 1024 most of the time */
	float		position[3];
	float		rotation[3];	/* direction from this checkpoint to the next */
	float		zero_point_two;
	float		radius;			/* radius? */
	uint32_t	__unknown3;		/* always zero */
	uint32_t	__unknown4;		/* always zero */
};

struct vehicle_state
{
	float					matrix[16];
	float					speed[3];
	float					spin[3];
	struct vehicle_state	*trailer;
	struct vehicle_info		*trailerPtr;
};


// debug display function
extern float g_f_debugDisplay[10];
extern CVector g_vec_debugDisplay[10];
void cheat_main_display_debug_stuff ( double time_diff );


/* __time_current is set in cheat_hook(). the time is "cached".
   by doing this we save some CPU time, and we get a constant time */
#define time_get() __time_current
extern uint64_t __time_current;
extern double g_timeDiff;

extern struct pool			*pool_actor;
extern struct pool			*pool_vehicle;

extern struct cheat_state	*cheat_state;
extern float				*cam_matrix;

void						cheat_hook ( HWND wnd );
bool						isCheatPanicEnabled();