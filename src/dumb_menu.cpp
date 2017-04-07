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

#define ID_NONE					- 1

#define ID_MENU_MAIN			0
#define ID_MENU_CHEATS			1
#define ID_MENU_CHEATS_INVULN	1
#define ID_MENU_CHEATS_MONEY	2
#define ID_MENU_CHEATS_MODS		135
#define ID_MENU_CHEATS_WEATHER	5
#define ID_MENU_CHEATS_TIME		6
#define ID_MENU_CHEATS_HANDLING 111
#define ID_MENU_PATCHES			7
#define ID_MENU_WEAPONS			8
#define ID_MENU_VEHICLES		9
#define ID_MENU_TELEPORTS		11
#define ID_MENU_MISC			12
#define ID_MENU_DEBUG			13
#define ID_MENU_PLAYERS			14
#define ID_MENU_PLAYERS_WARP	100
#define ID_MENU_PLAYERS_VEHWARP 101
#define ID_MENU_PLAYERS_SPEC	102
#define ID_MENU_PLAYERS_INFO	113
#define ID_MENU_PLAYERS_MUTE	114
#define ID_MENU_PLAYERS_VMUTE	115
#define ID_MENU_SAMPPATCHES		20
#define ID_MENU_SERVER_LIST		21
#define ID_MENU_HUDINDICATORS	22
#define ID_MENU_INTERIORS		23

#ifdef __CHEAT_VEHRECORDING_H__
#define ID_MENU_ROUTES			26
#define ID_MENU_ROUTES_LOAD		27
#define ID_MENU_ROUTES_DROP		28
#endif

#define ID_CHEAT_INVULN						10
#define ID_CHEAT_WEAPONS					20
#define ID_CHEAT_MONEY						30
#define ID_CHEAT_MODS						40
#define ID_CHEAT_PROT						50
#define ID_CHEAT_WARP_NEAR					60
#define ID_CHEAT_JETPACK					70
#define ID_CHEAT_UNLOCK						80
#define ID_CHEAT_WEATHER					90
#define ID_CHEAT_TIME						100
#define ID_CHEAT_HP							110
#define ID_CHEAT_ARMOR						120
#define ID_CHEAT_GRAVITY					130
#define ID_CHEAT_MAP						140
#define ID_CHEAT_TELETEXTS					150
#define ID_CHEAT_GAME_SPEED					160
#define ID_CHEAT_HANDLING					170
#define ID_CHEAT_KEEP_TRAILER				180
#define ID_CHEAT_NOCOLS						190
#define ID_CHEAT_CHAMS						200
#define ID_CHEAT_CUSTOM_RUNSTYLE			210
#define ID_CHEAT_FLY_SPEED					220
#define ID_CHEAT_DISABLE_WAVES				230
#define ID_CHEAT_MAP_DRAW_LINES				231
#define ID_CHEAT_SURF						232
#define ID_CHEAT_FREEZEROT					233

#define ID_CHEAT_INVULN_ACTOR				0
#define ID_CHEAT_INVULN_VEHICLE				1
#define ID_CHEAT_INVULN_TIRES				2
#define ID_CHEAT_INVULN_MIN_HP				3
#define ID_CHEAT_INVULN_REGEN				5
#define ID_CHEAT_INVULN_REGEN_ONFOOT		6
#define ID_CHEAT_INVULN_DISABLE_EXTRA_INV	7
#define ID_CHEAT_INVULN_ACT_EXPL_INV		8
#define ID_CHEAT_INVULN_ACT_FALL_INV		9
#define ID_CHEAT_INVULN_ACT_FIRE_INV		10

#define ID_CHEAT_MONEY_GIVE_500				0
#define ID_CHEAT_MONEY_GIVE_1000			1
#define ID_CHEAT_MONEY_GIVE_5000			2
#define ID_CHEAT_MONEY_GIVE_10000			3
#define ID_CHEAT_MONEY_GIVE_20000			4
#define ID_CHEAT_MONEY_GIVE_99999999		5
#define ID_CHEAT_MONEY_GIVE_CUSTOM			6
#define ID_CHEAT_MONEY_MAX					7
#define ID_CHEAT_MONEY_RAND_MIN				8
#define ID_CHEAT_MONEY_RAND_MAX				9
#define ID_CHEAT_MONEY_IVAL_MIN				10
#define ID_CHEAT_MONEY_IVAL_MAX				11

#define ID_CHEAT_MODS_COLOR1				10
#define ID_CHEAT_MODS_COLOR2				20
#define ID_CHEAT_MODS_PAINTJOB				30

#define ID_CHEAT_HANDLING_MASS				0
#define ID_CHEAT_HANDLING_TURNMASS			1
#define ID_CHEAT_HANDLING_DRAGCOEFF			2
#define ID_CHEAT_HANDLING_TRACMULT			3
#define ID_CHEAT_HANDLING_ENGNACCEL			4
#define ID_CHEAT_HANDLING_MAXVEL			5
#define ID_CHEAT_HANDLING_BRAKEDECEL		6
#define ID_CHEAT_HANDLING_SUSPFORCELVL		7
#define ID_CHEAT_HANDLING_COLDMGMULT		8
#define ID_CHEAT_HANDLING_MULTIPLIER		9
#define ID_CHEAT_HANDLING_TRACTIONLOSS		10
#define ID_CHEAT_HANDLING_TRACTIONBIAS		11
#define ID_CHEAT_HANDLING_SUSPANTIDIVEMULT	12

#define ID_WEAPON_ENABLE					0
#define ID_WEAPON_RANDOM					1
#define ID_WEAPON_ITEM						2

#define ID_VEHICLES_IWARP					0
#define ID_VEHICLES_FREEZE					1
#define ID_MENU_VEHICLES_SUB				106

#define ID_MISC_COORDS						0
#define ID_MISC_RELOAD						1
#define ID_MISC_HUDTEXT						2
#define ID_MISC_BAD_WEAPONS					3
#define ID_MISC_TRAILERS					4
#define ID_MISC_FPSLIMIT					5
#define ID_MISC_TOGGLEWINDOWED				6

#define ID_DEBUG_ENABLE						0
#define ID_DEBUG_SELF_ACTOR					1
#define ID_DEBUG_SAMP_DLL					2
#define ID_DEBUG_SELF_VEHICLE				3
#define ID_DEBUG_SAMP_INFO					4
#define ID_DEBUG_SAMP_PLAYER_LIST			5
#define ID_DEBUG_SAMP_LOCAL_INFO			6
#define ID_DEBUG_SAMP_CHAT_INFO				7
#define ID_DEBUG_SAMP_CHAT_IPT_INFO			8
#define ID_DEBUG_SAMP_KILL_INFO				9
#define ID_DEBUG_SAMP_VEHICLE_LIST			10
#define ID_DEBUG_SAMP_LOCAL_SAMPPED			11

#ifdef __CHEAT_VEHRECORDING_H__
#define ID_ROUTES_ACTIVATED					0
#define ID_ROUTES_WRITE						1
#define ID_ROUTES_OPTIMIZE					2
#endif

#define ID_HUDIND_BAR						0
#define ID_HUDIND_TSHADOWS					1
#define ID_HUDIND_INV						2
#define ID_HUDIND_WEAPON					3
#define ID_HUDIND_MONEY						4
#define ID_HUDIND_FREEZE					5
#define ID_HUDIND_INVEH_AIRBRK				6
#define ID_HUDIND_INVEH_STICK				7
#define ID_HUDIND_INVEH_BRKDANCE			8
#define ID_HUDIND_ONFOOT_AIRBRK				9
#define ID_HUDIND_ONFOOT_STICK				10
#define ID_HUDIND_ONFOOT_AIM				11
#define ID_HUDIND_POS						12
#define ID_HUDIND_FPS						13
#define ID_HUDIND_LB_BARS					14
#define ID_HUDIND_INVEH_SPIDER				15
#define ID_HUDIND_INVEH_FLY					16
#define ID_HUDIND_ONFOOT_FLY				17
#define ID_HUDIND_SURF						18
#define ID_HUDIND_FREEZEROT					19

#define ID_MENU_SAMPMISC					0
#define ID_MENU_SAMPMISC_VEHICLES_INSTANT	108
#define ID_MENU_SAMPMISC_FAKE_KILL			105
#define ID_MENU_SAMPMISC_SPOOF_WEAPON		3
#define ID_MENU_SAMPMISC_SAMP_INFO_LIST		4
#define ID_MENU_SAMPMISC_CHAT_TEXT			6
#define ID_MENU_SAMPMISC_CHAT_TEXTLINES		7
#define ID_MENU_SAMPMISC_GAMESTATE			9
#define ID_MENU_SAMPMISC_SPECIALACTION		12
#define ID_MENU_SAMPMISC_SAMP_DRUNK			13
#define ID_MENU_SAMPMISC_TELEOBJECT			109
#define ID_MENU_SAMPMISC_TELEPICKUP			110
#define ID_MENU_SAMPMISC_RENDEROBJTXT		15
#define ID_MENU_SAMPMISC_RENDERPCKTXT		16
#define ID_MENU_SAMPMISC_M0DCOMMANDS		17
#define ID_MENU_SAMPMISC_EXTRAGM			18

#define ID_MENU_SPECIAL_ACTION_NONE				0
#define ID_MENU_SPECIAL_ACTION_USEJETPACK		2
#define ID_MENU_SPECIAL_ACTION_DANCE1			5
#define ID_MENU_SPECIAL_ACTION_DANCE2			6
#define ID_MENU_SPECIAL_ACTION_DANCE3			7
#define ID_MENU_SPECIAL_ACTION_DANCE4			8
#define ID_MENU_SPECIAL_ACTION_HANDSUP			10
#define ID_MENU_SPECIAL_ACTION_USECELLPHONE		11
#define ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE 13
#define ID_MENU_SPECIAL_ACTION_DRINK_BEER		20
#define ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY		21
#define ID_MENU_SPECIAL_ACTION_DRINK_WINE		22
#define ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK		23
#define ID_MENU_SPECIAL_ACTION_CUFFED			24
#define ID_MENU_SPECIAL_ACTION_CARRY			25
#define ID_MENU_SPECIAL_ACTION_URINATE			68

#define ID_MENU_NETPATCHES_INRPC				10024
#define ID_MENU_NETPATCHES_OUTRPC				10025
#define ID_MENU_NETPATCHES_INPACKET				10026
#define ID_MENU_NETPATCHES_OUTPACKET			10027
#define ID_MENU_NETPATCHES_TOGGLE_ALL			INI_NETPATCHES_MAX

struct menu *menu_active = NULL;
int	menu_init = 0, menu_mouseover = -1;
extern int	iGTAPatchesCount, iSAMPPatchesCount, iNetPatchesCount, iServersCount;

static struct menu *menu_new ( struct menu *parent, int id, menu_callback callback )
{
	struct menu *menu = (struct menu *)calloc( 1, sizeof(struct menu) );

	if ( menu == NULL )
		return NULL;

	menu->id = id;
	menu->parent = parent;
	menu->callback = callback;

	return menu;
}

static struct menu_item *menu_item_add ( struct menu *menu, struct menu *submenu, const char *name, int id,
										 D3DCOLOR color, void *data )
{
	struct menu_item	*item;
	int					i;

	i = menu->count++;
	menu->item = (struct menu_item *)realloc( menu->item, sizeof(struct menu_item) * menu->count );
	item = &menu->item[i];

	memset( item, 0, sizeof(menu_item) );
	item->submenu = submenu;
	item->menu = menu;
	item->name = _strdup( name );
	item->id = id;
	item->color = color;
	item->data = data;

	return item;
}

static void menu_item_name_set ( struct menu_item *item, const char *fmt, ... )
{
	const char	*name_new;
	char		name[64];
	va_list		ap;

	memset( name, 0, sizeof(name) );
	va_start( ap, fmt );
	vsnprintf( name, sizeof(name)-1, fmt, ap );
	va_end( ap );

	if ( (name_new = _strdup(name)) != NULL )
	{
		free( (void *)item->name );
		item->name = name_new;
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//menu_callback_cheats_mods
static void menu_cheats_mods_populate ( struct menu *menu )
{
	// clear menu
	menu_items_free( menu );

	// get vehicle_info
	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo == NULL )
		return;

	struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
	if ( vinfo->passengers[0] != ainfo )
		return;

	// some variables
	int		iModelID = vinfo->base.model_alt_id;
	char	name[64];

	/* i... like... colors & paint
	#define ID_CHEAT_MODS_COLOR1	10
	#define ID_CHEAT_MODS_COLOR2	20
	#define ID_CHEAT_MODS_PAINTJOB	30
	*/
	snprintf( name, sizeof(name), "Color 1: %d", vinfo->color[0] );
	menu_item_add( menu, NULL, name, ID_CHEAT_MODS_COLOR1, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Color 2: %d", vinfo->color[1] );
	menu_item_add( menu, NULL, name, ID_CHEAT_MODS_COLOR2, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Paintjob: %d", vehicle_getPaintJob(vinfo) );
	menu_item_add( menu, NULL, name, ID_CHEAT_MODS_PAINTJOB, MENU_COLOR_DEFAULT, NULL );

	// No upgrades for these types
	eClientVehicleType	vehicleType = GetVehicleType( iModelID );
	if ( vehicleType == CLIENTVEHICLE_BOAT
	 ||	 vehicleType == CLIENTVEHICLE_TRAIN
	 ||	 vehicleType == CLIENTVEHICLE_HELI
	 ||	 vehicleType == CLIENTVEHICLE_PLANE
	 ||	 vehicleType == CLIENTVEHICLE_BIKE
	 ||	 vehicleType == CLIENTVEHICLE_BMX ) return;

	for ( int iUpgradeInfo = 0; iUpgradeInfo < VEHICLE_UPGRADES_COUNT; iUpgradeInfo++ )
	{
		if ( isUpgradeCompatible(cveh_upgrade_info[iUpgradeInfo].iModelID, vinfo) )
		{
			snprintf( name, sizeof(name), "%s %s", cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName,
					  cveh_upgrade_info[iUpgradeInfo].upgradeName );
			menu_item_add( menu, NULL, name, cveh_upgrade_info[iUpgradeInfo].iModelID, MENU_COLOR_DEFAULT, NULL );

			// skip matching sideskirt
			if ( cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Sideskirt"
			 ||	 cveh_upgrade_info[iUpgradeInfo].upgradeCategoryName == "Vents" ) iUpgradeInfo++;
		}
	}
}

static void menu_cheats_spoof_kill_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;

	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
			continue;

		if ( g_Players->pRemotePlayer[i] != NULL )
			color = samp_color_get( i );

		snprintf( text, sizeof(text), "Fake killed by %s (ID: %d)", getPlayerName(i), i );

		menu_item_add( menu, NULL, text, ID_MENU_SAMPMISC_FAKE_KILL, color, (void *)(UINT_PTR) i );
	}
}

static void menu_vehicles_populate ( struct menu *menu, int class_id )
{
	const struct actor_info *actor_self = actor_info_get( ACTOR_SELF, 0 );
	char					name[64];
	int						i;

	menu_items_free( menu );

	if ( pool_vehicle != NULL )
	{
		for ( i = 0; i < pool_vehicle->size; i++ )
		{
			static const struct vehicle_entry	unknown = { 0, VEHICLE_CLASS_CAR, "[Unknown vehicle]" };
			const struct vehicle_info			*info = vehicle_info_get( i, VEHICLE_ALIVE );
			const struct vehicle_entry			*vehicle;
			float								dist[3] = { 0.0f, 0.0f, 0.0f };

			if ( info == NULL )
				continue;

			vehicle = gta_vehicle_get_by_id( info->base.model_alt_id );
			if ( vehicle == NULL )
				vehicle = &unknown;

			if ( vehicle->class_id != class_id )
				continue;

			if ( actor_self != NULL )
				vect3_vect3_sub( &info->base.matrix[4 * 3], &actor_self->base.matrix[4 * 3], dist );

			if ( vect3_near_zero( &info->base.matrix[4 * 3] ) )
				continue;

			snprintf( name, sizeof(name), "%s (%.2fm%s)", vehicle->name, vect3_length(dist),
					  (info->passengers[0] == NULL) ? "" : ", Occupied" );

			menu_item_add( menu, NULL, name, i, MENU_COLOR_DEFAULT, NULL );
		}
	}
}

static void menu_players_warp_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if(g_Players->pRemotePlayer[i] == NULL)
			continue;

		// can obtain position data?
		if(	vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[i]) 
			&& (g_Players->pRemotePlayer[i]->pPlayerData == NULL || 
			g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL) ) 
			continue;

		color = samp_color_get( i );
		snprintf( text, sizeof(text), "%s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static void menu_players_vehwarp_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
			continue;

		//if(vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[i])) continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->bytePlayerState != PLAYER_STATE_DRIVER
		 &&	 g_Players->pRemotePlayer[i]->pPlayerData->bytePlayerState != PLAYER_STATE_PASSENGER ) continue;

		if ( g_Players->pRemotePlayer[i] != NULL )
			color = samp_color_get( i );

		snprintf( text, sizeof(text), "%s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static void menu_vehicles_instant_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL && g_Vehicles == NULL )
		return;

	const struct vehicle_entry	*vehicle;
	char						text[64];
	int							v;
	for ( v = 0; v < SAMP_MAX_VEHICLES; v++ )
	{
		if ( g_Vehicles->iIsListed[v] != 1 )
			continue;
		if ( g_Vehicles->pSAMP_Vehicle[v] == NULL )
			continue;
		if ( g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle == NULL )
			continue;

		vehicle = gta_vehicle_get_by_id( g_Vehicles->pSAMP_Vehicle[v]->pGTA_Vehicle->base.model_alt_id );
		snprintf( text, sizeof(text), "%s (ID: %d)", vehicle->name, v );
		menu_item_add( menu, NULL, text, v, D3DCOLOR_XRGB(150, 150, 150), NULL );
	}
}

static void menu_players_spectator_mode_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_Players == NULL )
		return;

	menu_item_add( menu, NULL, "Disable", ID_NONE, MENU_COLOR_DEFAULT, NULL );

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL )
			continue;
		if ( g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
			continue;

		color = samp_color_get( (int)g_Players->pRemotePlayer[i]->pPlayerData->sPlayerID );

		snprintf( text, sizeof(text), "Spectate %s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, color, (void *)(UINT_PTR) i );
	}
}

static void menu_telepickup_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_SAMP->pPools->pPickup == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PICKUPS; i++ )
	{
		if ( g_SAMP->pPools->pPickup->pickup[i].iModelID == 0 )
			continue;
		if ( g_SAMP->pPools->pPickup->pickup[i].iType == 0 )
			continue;

		D3DCOLOR	color = MENU_COLOR_DEFAULT;
		snprintf( text, sizeof(text), "Pickup (%d, ModelID: %d)", i, g_SAMP->pPools->pPickup->pickup[i].iModelID );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static int menu_callback_telepickup ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		int id = item->id;

		if ( g_SAMP->pPools->pPickup == NULL )
			return 0;
		if ( g_SAMP->pPools->pPickup->pickup[id].iType == 0 )
			return 0;
		if ( g_SAMP->pPools->pPickup->pickup[id].iModelID == 0 )
			return 0;
		if ( item->id == ID_NONE )
			return 0;

		float	pos[3];

		vect3_copy( g_SAMP->pPools->pPickup->pickup[id].fPosition, pos );
		pos[1] += 2.0f;
		cheat_teleport( pos, 0 );

		return 1;
	}

	return 0;
}

static void menu_teleobject_populate ( struct menu *menu )
{
	menu_items_free( menu );

	if ( g_SAMP->pPools->pObject == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_OBJECTS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;

		if ( g_SAMP->pPools->pObject->iIsListed[i] != 1 )
			continue;
		if ( g_SAMP->pPools->pObject->object[i] == NULL )
			continue;
		if ( g_SAMP->pPools->pObject->object[i]->pGTAEntity == NULL )
			continue;

		float	pos[3];
		vect3_copy( &g_SAMP->pPools->pObject->object[i]->pGTAEntity->base.matrix[4 * 3], pos );
		if ( vect3_near_zero(pos) )
			continue;

		snprintf( text, sizeof(text), "Object (%d, ModelID %d)", i,
				  g_SAMP->pPools->pObject->object[i]->pGTAEntity->base.model_alt_id );
		menu_item_add( menu, NULL, text, i, color, NULL );
	}
}

static int menu_callback_teleobject ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( g_SAMP->pPools->pObject == NULL )
			return 0;
		if ( item->id == ID_NONE )
			return 0;

		int		id = item->id;
		float	pos[3];

		if ( g_SAMP->pPools->pObject->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Object does not exist." );
			return 0;
		}

		if ( g_SAMP->pPools->pObject->object[id]->pGTAEntity == NULL )
		{
			addMessageToChatWindow( "Invalid object info." );
			return 0;
		}

		vect3_copy( &g_SAMP->pPools->pObject->object[id]->pGTAEntity->base.matrix[4 * 3], pos );
		pos[2] += 2.0f;
		cheat_teleport( pos, 0 );

		return 1;
	}

	return 0;
}

static void menu_handling_populate ( struct menu *menu )
{
	CVehicle	*cveh = getSelfCVehicle();
	if ( cveh == NULL )
		return;
	if ( cveh->GetHandlingData() == NULL )
		return;

	traceLastFunc( "menu_handling_populate()" );

	char	text[64];

	menu_items_free( menu );

	snprintf( text, sizeof(text), "Multiplier: %0.2f", set.handling_multiplier );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_MULTIPLIER, MENU_COLOR_DEFAULT, NULL );

	menu_item_add( menu, NULL, "\tHandling", ID_NONE, MENU_COLOR_SEPARATOR, NULL );

	snprintf( text, sizeof(text), "Engine acceleration: %0.2f", cveh->GetHandlingData()->GetEngineAccelleration() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_ENGNACCEL, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Brake decelleration: %0.2f", cveh->GetHandlingData()->GetBrakeDecelleration() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_BRAKEDECEL, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Drag coefficient: %0.2f", cveh->GetHandlingData()->GetDragCoeff() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_DRAGCOEFF, MENU_COLOR_DEFAULT, NULL );

	snprintf( text, sizeof(text), "Max velocity: %0.2f", cveh->GetHandlingData()->GetMaxVelocity() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_MAXVEL, MENU_COLOR_DEFAULT, NULL );

	// these can't be used because they don't always show up right etc... possibly mapped wrong
	snprintf( text, sizeof(text), "Traction multiplier: %0.2f", cveh->GetHandlingData()->GetTractionMultiplier() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TRACMULT, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Traction loss: %0.2f", cveh->GetHandlingData()->GetTractionLoss() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TRACTIONLOSS, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Traction bias: %0.2f", cveh->GetHandlingData()->GetTractionBias() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TRACTIONBIAS, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Suspension force level: %0.2f", cveh->GetHandlingData()->GetSuspensionForceLevel() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_SUSPFORCELVL, MENU_COLOR_DEFAULT, NULL );

	//snprintf( text, sizeof(text), "Suspension anti-dive multiplier: %0.2f", cveh->GetHandlingData()->GetSuspensionAntidiveMultiplier() );
	//menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_SUSPANTIDIVEMULT, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Mass: %0.2f", cveh->GetHandlingData()->GetMass() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_MASS, MENU_COLOR_DEFAULT, NULL );
	snprintf( text, sizeof(text), "Turn mass: %0.2f", cveh->GetHandlingData()->GetTurnMass() );
	menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_TURNMASS, MENU_COLOR_DEFAULT, NULL );

	//snprintf( text, sizeof(text), "Collision damage multiplier: %0.2f",
	//		  cveh->GetHandlingData()->GetCollisionDamageMultiplier() );
	//menu_item_add( menu, NULL, text, ID_CHEAT_HANDLING_COLDMGMULT, MENU_COLOR_DEFAULT, NULL );
}

static void menu_playerinfo_populate ( struct menu *menu )
{
	menu_items_free( menu );
	if ( g_Players == NULL )
		return;

	menu_item_add( menu, NULL, "Disable", SAMP_MAX_PLAYERS + 1, MENU_COLOR_DEFAULT, NULL );

	menu_item_add( menu, NULL, "Local Player", -2, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) - 2 );

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		if ( g_Players->iIsListed[i] != 1 )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;

		snprintf( text, sizeof(text), "View %s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}
}

static void menu_playermute_populate ( struct menu *menu )
{
	menu_items_free( menu );
	if ( g_Players == NULL )
		return;

	char	text[64];
	int		i;
	for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
	{
		if ( g_Players->iIsListed[i] != 1 || g_Players->pRemotePlayer[i] == NULL )
		{
			g_bPlayerMuted[i] = false;
			continue;
		}

		snprintf( text, sizeof(text), "Mute %s (ID: %d)", getPlayerName(i), i );
		menu_item_add( menu, NULL, text, i, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}
}

#ifdef __CHEAT_VEHRECORDING_H__
static void menu_routes_drop_populate ( struct menu *menu )
{
	menu_items_free( menu );

	// now get me some data from the database
	char table_name_[64];
	char *table_name;
	int num_tables = rec_sqlite_getNumTables();

	if ( num_tables <= 0 )
	{
		menu_item_add( menu, NULL, (num_tables < 0) ? "Error Reading Database" : "No Saved Routes", ID_NONE, 
			MENU_COLOR_DEFAULT, NULL );
		return;
	}

	for ( int i = 0; i < num_tables; i++ )
	{
		table_name = rec_sqlite_getTableName(i);
		if ( table_name == NULL )
			continue;

		// remember to change menu_callback_routes_drop, if you change the "Delete" text
		_snprintf_s( table_name_, sizeof(table_name_)-1, "Delete '%s'", table_name );
		menu_item_add( menu, NULL, table_name_, i, MENU_COLOR_DEFAULT, NULL );
	}
}

static void menu_routes_load_populate ( struct menu *menu )
{
	menu_items_free( menu );

	// now get me some data from the database
	int num_tables = rec_sqlite_getNumTables();
	char *table_name;

	if ( num_tables <= 0 )
	{
		menu_item_add( menu, NULL, (num_tables < 0) ? "Error Reading Database" : "No Saved Routes", ID_NONE, 
			MENU_COLOR_DEFAULT, NULL );
		return;
	}

	for ( int i = 0; i < num_tables; i++ )
	{
		table_name = rec_sqlite_getTableName(i);
		if ( table_name == NULL )
			continue;
		menu_item_add( menu, NULL, table_name, i, MENU_COLOR_DEFAULT, NULL );
	}
}
#endif

// called when a menu is going to be displayed
static void menu_event_activate ( struct menu *menu )
{
	if ( menu == NULL )
		return;

	switch ( menu->id )
	{
	case ID_MENU_CHEATS_MODS:
		menu_cheats_mods_populate( menu );
		break;

	case ID_MENU_PLAYERS_WARP:
		menu_players_warp_populate( menu );
		break;

	case ID_MENU_PLAYERS_VEHWARP:
		menu_players_vehwarp_populate( menu );
		break;

	case ID_MENU_PLAYERS_SPEC:
		menu_players_spectator_mode_populate( menu );
		break;

	case ID_MENU_SAMPMISC_FAKE_KILL:
		menu_cheats_spoof_kill_populate( menu );
		break;

	case ID_MENU_VEHICLES_SUB:
		menu_vehicles_populate( menu, (int)(UINT_PTR) menu->parent->item[menu->parent->pos].data );
		break;

	case ID_MENU_SAMPMISC_VEHICLES_INSTANT:
		menu_vehicles_instant_populate( menu );
		break;

	case ID_MENU_SAMPMISC_TELEOBJECT:
		menu_teleobject_populate( menu );
		break;

	case ID_MENU_SAMPMISC_TELEPICKUP:
		menu_telepickup_populate( menu );
		break;

	case ID_MENU_CHEATS_HANDLING:
		menu_handling_populate( menu );
		break;

	case ID_MENU_PLAYERS_INFO:
		menu_playerinfo_populate( menu );
		break;

	case ID_MENU_PLAYERS_MUTE:
		menu_playermute_populate( menu );
		break;

#ifdef __CHEAT_VEHRECORDING_H__
	case ID_MENU_ROUTES_DROP:
		menu_routes_drop_populate( menu );
		break;

	case ID_MENU_ROUTES_LOAD:
		menu_routes_load_populate( menu );
		break;
#endif
	}
}

/* run every frame */
void menu_run ( void )
{
	struct menu_item	*item;
	static uint32_t		key_time_updown, key_time_incdec;

	if ( menu_active == NULL )
		return;

	if ( KEYCOMBO_PRESSED(set.key_menu) )
	{
		menu_toggle((cheat_state->_generic.menu ^= 1) != 0);
	}

	if ( cheat_state->_generic.menu )
	{
		if ( KEY_PRESSED(set.key_menu_up) || KEY_PRESSED(set.key_menu_down) )
		{
			menu_active->pos += KEY_PRESSED( set.key_menu_up ) ? -1 : 1;
			key_time_updown = time_get() + MSEC_TO_TIME( MENU_SCROLL_DELAY );
		}

		if ( KEY_DOWN(set.key_menu_up) || KEY_DOWN(set.key_menu_down) )
		{
			if ( time_get() > key_time_updown )
			{
				int diff = time_get() - key_time_updown;
				int overruns = diff / MENU_SCROLL_TIME;
				int dir = KEY_DOWN( set.key_menu_up ) ? -1 : 1;

				menu_active->pos += dir * ( overruns + 1 );

				key_time_updown = time_get() + MENU_SCROLL_TIME - ( diff % MENU_SCROLL_TIME );
			}
		}

		if ( menu_active->pos < 0 )
			menu_active->pos = menu_active->count - 1;
		if ( menu_active->pos >= menu_active->count )
			menu_active->pos = 0;

		if ( menu_active->count <= 0 )
			item = NULL;
		else
			item = &menu_active->item[menu_active->pos];

		if ( KEY_PRESSED(set.key_menu_left) )
		{
			/* pressing left in the main menu, exits the menu */
			if ( menu_active->parent == NULL )
			{
				menu_toggle(false);
				return;
			}

			menu_active = menu_active->parent;
			menu_event_activate( menu_active );
		}

		if ( KEY_PRESSED(set.key_menu_right) || KEY_PRESSED(set.key_menu_select) )
		{
			int was_selected = 0;

			if ( KEY_PRESSED(set.key_menu_select) && menu_active->callback != NULL && item != NULL )
			{
				if ( menu_active->callback(MENU_OP_SELECT, item) )
					was_selected = 1;
			}

			if ( !was_selected && item != NULL && item->submenu != NULL )
			{
				menu_active = item->submenu;
				menu_event_activate( menu_active );
			}
		}

		if ( KEY_PRESSED(set.key_menu_dec) || KEY_PRESSED(set.key_menu_inc) )
		{
			int op = KEY_PRESSED( set.key_menu_dec ) ? MENU_OP_DEC : MENU_OP_INC;
			if ( item != NULL )
				menu_active->callback( op, item );
			key_time_incdec = time_get() + MSEC_TO_TIME( MENU_SCROLL_DELAY );
		}

		if ( KEY_DOWN(set.key_menu_dec) || KEY_DOWN(set.key_menu_inc) )
		{
			if ( time_get() > key_time_incdec )
			{
				int diff = time_get() - key_time_incdec;
				int overruns = diff / MENU_SCROLL_TIME;

				int op = KEY_DOWN( set.key_menu_dec ) ? MENU_OP_DEC : MENU_OP_INC;
				menu_active->callback( op, item );

				key_time_incdec = time_get() + MENU_SCROLL_TIME - ( diff % MENU_SCROLL_TIME );
			}
		}

		KEY_CONSUME( set.key_menu_up );
		KEY_CONSUME( set.key_menu_right );
		KEY_CONSUME( set.key_menu_down );
		KEY_CONSUME( set.key_menu_left );
		KEY_CONSUME( set.key_menu_select );
		KEY_CONSUME( set.key_menu_dec );
		KEY_CONSUME( set.key_menu_inc );
	}
}

bool menu_wndproc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MOUSEWHEEL:
		{
			if (menu_active == NULL || !cheat_state->_generic.menu || !cheat_state->_generic.menu_mousecontrol)
				break;
			
			POINT				point = { LOWORD(lParam), HIWORD(lParam) };
			const int			ROW_HEIGHT = (int)ceilf(pD3DFont->DrawHeight());
			const int			MENU_HEIGHT = (int)ceilf(pD3DFont->DrawHeight() * (float)MENU_ROWS) + 2;
			int					left = pPresentParam.BackBufferWidth / 2 - MENU_WIDTH / 2;
			int					top = pPresentParam.BackBufferHeight - MENU_HEIGHT - 20;
			int					pos = 0;

			if (uMsg == WM_MOUSEWHEEL)
			{
				// WM_MOUSEWHEEL has global cursor coords
				ScreenToClient(pPresentParam.hDeviceWindow, &point);

				if (LOWORD(wParam) == MK_SHIFT)
				{
					menu_item *item = nullptr;
					if (menu_active->count > 0)
						item = &menu_active->item[menu_active->pos];

					int op = short(HIWORD(wParam)) > 0 ? MENU_OP_INC : MENU_OP_DEC;
					menu_active->callback(op, item);
				}
				else
				{
					int dir = short(HIWORD(wParam)) > 0 ? -1 : 1;
					menu_active->pos += dir;
				}
			}

			if (point.x > left && point.x < left + MENU_WIDTH && point.y > top && point.y < top + MENU_HEIGHT)
			{
				pos = (point.y - top) / ROW_HEIGHT;
				if (pos > menu_active->count - 1) pos = menu_active->count - 1;
				if (pos > MENU_ROWS - 1) pos = MENU_ROWS - 1;
				menu_mouseover = menu_active->top_pos + pos;

				if (uMsg == WM_LBUTTONDOWN)
				{
					if (menu_mouseover != -1)
						menu_active->pos = menu_mouseover;
					menu_item *item = nullptr;
					if (menu_active->count > 0)
						item = &menu_active->item[menu_active->pos];

					if (item != nullptr && item->submenu != nullptr)
					{
						menu_active = item->submenu;
						menu_event_activate(menu_active);
					}
					else if (menu_active->callback != nullptr && item != nullptr)
					{
						menu_active->callback(MENU_OP_SELECT, item);
					}
				}
			}
			else
			{
				menu_mouseover = -1;
			}
			if (uMsg == WM_RBUTTONDOWN)
			{
				if (menu_active->parent == NULL)
				{
					menu_toggle(false);
					break;
				}
				menu_active = menu_active->parent;
				menu_event_activate(menu_active);
			}
			break;
		}
	}
	return false;
}

void menu_toggle(bool toggle)
{
	cheat_state->_generic.menu = toggle;
	menu_mouseover = -1;
	if (toggle)
	{
		menu_event_activate(menu_active);
		if (g_SAMP)
		{
			if (cheat_state->_generic.menu_mousecontrol = KEYCOMBO_DOWN(set.key_menu_mousecontrol))
				toggleSAMPCursor(true);
		}
	}
	else if (cheat_state->_generic.menu_mousecontrol && g_SAMP)
	{
		toggleSAMPCursor(false);
	}
}

static int menu_callback_main ( int op, struct menu_item *item )
{
	return 0;
}

static int menu_callback_cheats_mods ( int op, struct menu_item *item )
{
	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	if ( vinfo == NULL )
		return 0;
	switch ( op )
	{
	case MENU_OP_DEC:
	case MENU_OP_INC:
		int mod, color_temp, paintjob_temp;
		switch ( item->id )
		{
		case ID_CHEAT_MODS_COLOR1:
			color_temp = vehicle_getColor0( vinfo );
			mod = ( op == MENU_OP_DEC ) ? -1 : 1;
			if ( mod > 0 )
				color_temp++;
			if ( mod < 0 )
				color_temp--;
			if ( color_temp < 0 )
				color_temp = 0;
			vehicle_setColor0( vinfo, color_temp );
			menu_item_name_set( item, "Color 1: %d", color_temp );
			return 1;

		case ID_CHEAT_MODS_COLOR2:
			color_temp = vehicle_getColor1( vinfo );
			mod = ( op == MENU_OP_DEC ) ? -1 : 1;
			if ( mod > 0 )
				color_temp++;
			if ( mod < 0 )
				color_temp--;
			if ( color_temp < 0 )
				color_temp = 0;
			vehicle_setColor1( vinfo, color_temp );
			menu_item_name_set( item, "Color 2: %d", color_temp );
			return 1;

		case ID_CHEAT_MODS_PAINTJOB:
			paintjob_temp = vehicle_getPaintJob( vinfo );
			mod = ( op == MENU_OP_DEC ) ? -1 : 1;
			if ( mod > 0 )
				paintjob_temp++;
			if ( mod < 0 )
				paintjob_temp--;
			if ( paintjob_temp < 0 )
				paintjob_temp = 0;
			if ( paintjob_temp > 4 )
				paintjob_temp = 4;
			vehicle_setPaintJob( vinfo, paintjob_temp );
			menu_item_name_set( item, "Paintjob: %d", paintjob_temp );
			return 1;
		}

	case MENU_OP_SELECT:
		if ( item->id >= 1000 && item->id <= 1193 )
		{
			struct actor_info	*ainfo = actor_info_get( ACTOR_SELF, 0 );
			if ( vinfo->passengers[0] != ainfo )
				return 0;

			int						iModelID = item->id;
			int						iUpgradeInfoID;
			vehicle_upgrade_info	upgrade_info = get_cveh_upgrade_info( iModelID, iUpgradeInfoID );
			int						iModelIDplusOne = cveh_upgrade_info[iUpgradeInfoID + 1].iModelID;
			if ( upgrade_info.upgradeCategoryName == "Sideskirt" || upgrade_info.upgradeCategoryName == "Vents" )
			{
				loadSpecificModel( iModelID );
				loadSpecificModel( iModelIDplusOne );
				vehicle_addUpgrade( vinfo, iModelID );
				vehicle_addUpgrade( vinfo, iModelIDplusOne );
			}
			else
			{
				loadSpecificModel( iModelID );
				vehicle_addUpgrade( vinfo, iModelID );
			}

			return 1;
		}
	}

	return 0;
}

static int menu_callback_cheats ( int op, struct menu_item *item )
{
	struct actor_info	*info;
	int					mod;

	switch ( op )
	{
	case MENU_OP_ENABLED:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN:
			return cheat_state->_generic.hp_cheat;

		case ID_CHEAT_WEAPONS:
			return 0;

		case ID_CHEAT_MONEY:
			return cheat_state->_generic.money;

		case ID_CHEAT_MODS:
			return 0;

		case ID_CHEAT_PROT:
			return cheat_state->vehicle.protection;

		case ID_CHEAT_WARP_NEAR:
			return 0;

		case ID_CHEAT_JETPACK:
			return 0;

		case ID_CHEAT_UNLOCK:
			return cheat_state->_generic.vehicles_unlock;

		case ID_CHEAT_WEATHER:
			return set.force_weather == (int)( UINT_PTR ) item->data;

		case ID_CHEAT_TIME:
			return set.force_hour == (int)( UINT_PTR ) item->data;

		case ID_CHEAT_HP:
			return 0;

		case ID_CHEAT_ARMOR:
			return 0;

		case ID_CHEAT_GRAVITY:
			return 0;

		case ID_CHEAT_MAP:
			return cheat_state->_generic.map;

		case ID_CHEAT_TELETEXTS:
			return cheat_state->_generic.teletext;

		case ID_CHEAT_GAME_SPEED:
			return 0;

		case ID_CHEAT_KEEP_TRAILER:
			return cheat_state->vehicle.keep_trailer_attached;

		case ID_CHEAT_NOCOLS:
			return cheat_state->_generic.nocols_enabled;

		case ID_CHEAT_CHAMS:
			return set.chams_on;

		case ID_CHEAT_CUSTOM_RUNSTYLE:
			return set.custom_runanimation_enabled;

		case ID_CHEAT_FLY_SPEED:
			return cheat_state->actor.fly_on;

		case ID_CHEAT_DISABLE_WAVES:
			return pGameInterface->GetWaterManager()->GetWaveLevel() == 0.0f;

		case ID_CHEAT_MAP_DRAW_LINES:
			return set.map_draw_lines;

		case ID_CHEAT_SURF:
			return cheat_state->actor.surf;

		case ID_CHEAT_FREEZEROT:
			return cheat_state->vehicle.freezerot;
		}
		break;

	case MENU_OP_SELECT:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN:
			cheat_state->_generic.hp_cheat ^= 1;
			if( !cheat_state->_generic.hp_cheat )
			{
				struct actor_info *self = actor_info_get( ACTOR_SELF, 0 );
				self->flags &= ~ACTOR_FLAGS_INVULNERABLE;
			}
			break;

		case ID_CHEAT_MONEY:
			cheat_state->_generic.money ^= 1;
			break;

		case ID_CHEAT_PROT:
			cheat_state->vehicle.protection ^= 1;
			break;

		case ID_CHEAT_WARP_NEAR:
			cheat_teleport_nearest_car();
			break;

		case ID_CHEAT_JETPACK:
			gta_jetpack_give();
			break;

		case ID_CHEAT_UNLOCK:
			cheat_state->_generic.vehicles_unlock ^= 1;
			break;

		case ID_CHEAT_WEATHER:
			if ( set.force_weather == (int)(UINT_PTR) item->data )
				set.force_weather = -1;
			else
				set.force_weather = (int)( UINT_PTR ) item->data;
			break;

		case ID_CHEAT_TIME:
			if ( set.force_hour == (int)(UINT_PTR) item->data )
				set.force_hour = -1;
			else
				set.force_hour = (int)( UINT_PTR ) item->data;
			break;

		case ID_CHEAT_MAP:
			cheat_state->_generic.map ^= 1;
			break;

		case ID_CHEAT_TELETEXTS:
			cheat_state->_generic.teletext ^= 1;
			break;

		case ID_CHEAT_HP:
		case ID_CHEAT_ARMOR:
			if ( (info = actor_info_get(ACTOR_SELF, ACTOR_ALIVE)) != NULL )
			{
				if ( item->id == ID_CHEAT_HP )
					info->hitpoints = 100.0f;
				else
					info->armor = 100.0f;
			}
			break;

		case ID_CHEAT_KEEP_TRAILER:
			cheat_state->vehicle.keep_trailer_attached ^= 1;
			break;

		case ID_CHEAT_NOCOLS:
			cheat_state->_generic.nocols_enabled ^= 1;
			break;

		case ID_CHEAT_CHAMS:
			set.chams_on ^= 1;
			break;

		case ID_CHEAT_CUSTOM_RUNSTYLE:
			set.custom_runanimation_enabled ^= 1;
			break;

		case ID_CHEAT_FLY_SPEED:
			cheat_state->actor.fly_on ^= 1;
			break;

		case ID_CHEAT_DISABLE_WAVES:
			if ( pGameInterface->GetWaterManager()->GetWaveLevel() == 0.0f )
				pGameInterface->GetWaterManager()->SetWaveLevel( -1.0f );
			else
				pGameInterface->GetWaterManager()->SetWaveLevel( 0.0f );
			break;

		case ID_CHEAT_MAP_DRAW_LINES:
			set.map_draw_lines ^= 1;
			break;

		case ID_CHEAT_SURF:
			cheat_state->actor.surf ^= 1;
			break;

		case ID_CHEAT_FREEZEROT:
			cheat_state->vehicle.freezerot ^= 1;
			break;

		default:
			return 0;
		}

		return 1;

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_CHEAT_GRAVITY:
			if ( mod > 0 && gta_gravity_get() < 0.1f )
				gta_gravity_set( gta_gravity_get() + 0.001f );
			if ( mod < 0 && gta_gravity_get() > -0.1f )
				gta_gravity_set( gta_gravity_get() - 0.001f );
			menu_item_name_set( item, "Gravity: %.04f", gta_gravity_get() );
			return 1;

		case ID_CHEAT_GAME_SPEED:
			cheat_state->game_speed += (float)mod * 0.05f;
			menu_item_name_set( item, "Game speed: %d%%", (int)roundf(cheat_state->game_speed * 100.0f) );
			return 1;

		case ID_CHEAT_CUSTOM_RUNSTYLE:
			set.custom_runanimation_id += mod;
			if ( set.custom_runanimation_id >= MOVE_ANIMATIONS_COUNT )
				set.custom_runanimation_id = 0;
			else if ( set.custom_runanimation_id < 0 )
				set.custom_runanimation_id = (MOVE_ANIMATIONS_COUNT-1);
			menu_item_name_set( item, "Custom running style: %i, %s", set.custom_runanimation_id,
										move_animations[set.custom_runanimation_id].moveStyleName );
			return 1;

		case ID_CHEAT_FLY_SPEED:
			if ( set.fly_player_speed <= 4.95f )
			{
				set.fly_player_speed += mod * 0.1f;
			}
			else if ( set.fly_player_speed <= 5.05f
				&& mod < 0 )
			{
				set.fly_player_speed += mod * 0.1f;
			}
			else
			{
				set.fly_player_speed += mod * 1.0f;
			}
			// don't allow it to go under 0.1f
			if ( set.fly_player_speed < 0.1f )
			{
				set.fly_player_speed = 0.1f;
			}

			menu_item_name_set( item, "Player Fly Speed: %0.01f", set.fly_player_speed );
			return 1;

		} // end of INC/DEC
	}

	return 0;
}

static int menu_callback_handling ( int op, struct menu_item *item )
{
	CVehicle	*cveh = getSelfCVehicle();
	if ( cveh == NULL )
		return NULL;

	int		mod;
	float	hlng;

	switch ( op )
	{
	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;

		switch ( item->id )
		{
		case ID_CHEAT_HANDLING_MULTIPLIER:
			if ( mod > 0 )
				set.handling_multiplier += 0.050f;
			if ( mod < 0 )
				set.handling_multiplier -= 0.050f;
			menu_item_name_set( item, "Multiplier: %0.2f", set.handling_multiplier );
			return 1;

		case ID_CHEAT_HANDLING_ENGNACCEL:
			hlng = cveh->GetHandlingData()->GetEngineAccelleration();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetEngineAccelleration( hlng );

			//cveh->GetHandlingData()->Recalculate();
			menu_item_name_set( item, "Engine acceleration: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_BRAKEDECEL:
			hlng = cveh->GetHandlingData()->GetBrakeDecelleration();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetBrakeDecelleration( hlng );

			//cveh->GetHandlingData()->Recalculate();
			menu_item_name_set( item, "Brake decelleration: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_MAXVEL:
			hlng = cveh->GetHandlingData()->GetMaxVelocity();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetMaxVelocity( hlng );

			//cveh->GetHandlingData()->Recalculate();
			menu_item_name_set( item, "Max velocity: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_TRACMULT:
			hlng = cveh->GetHandlingData()->GetTractionMultiplier();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTractionMultiplier( hlng );
			menu_item_name_set( item, "Traction multiplier: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_TRACTIONLOSS:
			hlng = cveh->GetHandlingData()->GetTractionLoss();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTractionLoss( hlng );
			menu_item_name_set( item, "Traction loss: %0.2f", hlng );
			return 1;

		/*case ID_CHEAT_HANDLING_TRACTIONBIAS:
			if(mod > 0) info->pHandlingData->fTractionBias += set.handling_multiplier;
			if(mod < 0) info->pHandlingData->fTractionBias -= set.handling_multiplier;
			menu_item_name_set(item, "Traction bias: %0.2f", info->pHandlingData->fTractionBias);
			return 1;*/
		case ID_CHEAT_HANDLING_TRACTIONBIAS:
			hlng = cveh->GetHandlingData()->GetTractionBias();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTractionBias( hlng );
			menu_item_name_set( item, "Traction bias: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_SUSPFORCELVL:
			hlng = cveh->GetHandlingData()->GetSuspensionForceLevel();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetSuspensionForceLevel( hlng );
			menu_item_name_set( item, "Suspension force level: %0.2f", hlng );
			return 1;

		// this one really makes the vehicle go nuttahs with tilt
		// you might lose the wheels using it, lol
		/*case ID_CHEAT_HANDLING_SUSPANTIDIVEMULT:
			if(mod > 0) info->pHandlingData->fSuspensionAntidiveMultiplier += set.handling_multiplier;
			if(mod < 0) info->pHandlingData->fSuspensionAntidiveMultiplier -= set.handling_multiplier;
			menu_item_name_set(item, "Suspension anti-dive multiplier: %0.2f", info->pHandlingData->fSuspensionAntidiveMultiplier);
			return 1;*/
		case ID_CHEAT_HANDLING_MASS:
			hlng = cveh->GetHandlingData()->GetMass();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetMass( hlng );
			menu_item_name_set( item, "Mass: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_TURNMASS:
			hlng = cveh->GetHandlingData()->GetTurnMass();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetTurnMass( hlng );
			menu_item_name_set( item, "Turn mass: %0.2f", hlng );
			return 1;

		case ID_CHEAT_HANDLING_DRAGCOEFF:
			hlng = cveh->GetHandlingData()->GetDragCoeff();
			if ( mod > 0 )
				hlng += set.handling_multiplier;
			if ( mod < 0 )
				hlng -= set.handling_multiplier;
			cveh->GetHandlingData()->SetDragCoeff( hlng );
			menu_item_name_set( item, "Drag coeffiecient: %0.2f", hlng );
			return 1;

			/*case ID_CHEAT_HANDLING_COLDMGMULT:
			if(mod > 0) info->pHandlingData->fCollisionDamageMultiplier += set.handling_multiplier;
			if(mod < 0) info->pHandlingData->fCollisionDamageMultiplier -= set.handling_multiplier;
			menu_item_name_set(item, "Collision damage multiplier: %0.2f", info->pHandlingData->fCollisionDamageMultiplier);
			return 1;*/
		}
	}

	return 0;
}

static int menu_callback_cheats_invuln ( int op, struct menu_item *item )
{
	int mod;

	switch ( op )
	{
	case MENU_OP_ENABLED:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN_ACTOR:
			return cheat_state->actor.invulnerable;

		case ID_CHEAT_INVULN_VEHICLE:
			return cheat_state->vehicle.invulnerable;

		case ID_CHEAT_INVULN_TIRES:
			return cheat_state->vehicle.hp_tire_support;

		case ID_CHEAT_INVULN_MIN_HP:
			return cheat_state->vehicle.hp_minimum_on;

		case ID_CHEAT_INVULN_REGEN:
			return cheat_state->vehicle.hp_regen_on;

		case ID_CHEAT_INVULN_REGEN_ONFOOT:
			return cheat_state->actor.hp_regen_on;

		case ID_CHEAT_INVULN_DISABLE_EXTRA_INV:
			return set.hp_disable_inv_sp_enemies;

		case ID_CHEAT_INVULN_ACT_EXPL_INV:
			return set.hp_actor_explosion_inv;

		case ID_CHEAT_INVULN_ACT_FALL_INV:
			return set.hp_actor_fall_inv;

		case ID_CHEAT_INVULN_ACT_FIRE_INV:
			return set.hp_actor_fire_inv;
		}
		break;

	case MENU_OP_SELECT:
		switch ( item->id )
		{
		case ID_CHEAT_INVULN_ACTOR:
			cheat_state->actor.invulnerable ^= 1;
			break;

		case ID_CHEAT_INVULN_VEHICLE:
			cheat_state->vehicle.invulnerable ^= 1;
			break;

		case ID_CHEAT_INVULN_TIRES:
			cheat_state->vehicle.hp_tire_support ^= 1;
			break;

		case ID_CHEAT_INVULN_MIN_HP:
			cheat_state->vehicle.hp_minimum_on ^= 1;
			break;

		case ID_CHEAT_INVULN_REGEN:
			cheat_state->vehicle.hp_regen_on ^= 1;
			break;

		case ID_CHEAT_INVULN_REGEN_ONFOOT:
			cheat_state->actor.hp_regen_on ^= 1;
			break;

		case ID_CHEAT_INVULN_DISABLE_EXTRA_INV:
			set.hp_disable_inv_sp_enemies ^= 1;
			break;

		case ID_CHEAT_INVULN_ACT_EXPL_INV:
			set.hp_actor_explosion_inv ^= 1;
			break;

		case ID_CHEAT_INVULN_ACT_FALL_INV:
			set.hp_actor_fall_inv ^= 1;
			break;

		case ID_CHEAT_INVULN_ACT_FIRE_INV:
			set.hp_actor_fire_inv ^= 1;
			break;

		default:
			return 0;
		}

		return 1;
		break;

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_CHEAT_INVULN_MIN_HP:
			if ( set.hp_minimum > 1000.0f )
			{
				set.hp_minimum = ( mod == 1 ) ? ( set.hp_minimum * 2.0f ) : ( set.hp_minimum / 2.0f );
				if ( set.hp_minimum < 1000.0f )
					set.hp_minimum = 1000.0f;
			}
			else if ( set.hp_minimum > 250.0f )
			{
				set.hp_minimum += (float)mod * 50.0f;
			}
			else
			{
				set.hp_minimum += (float)mod * 10.0f;
			}

			if ( set.hp_minimum <= 0.0f )
				set.hp_minimum = 0.0f;
			else if ( set.hp_minimum > 1000000.0f )
				set.hp_minimum = 1000000.0f;
			else
				set.hp_minimum = roundf( set.hp_minimum );

			menu_item_name_set( item, "Vehicle minimum HP: %d", (int)set.hp_minimum );
			break;

		case ID_CHEAT_INVULN_REGEN:
			set.hp_regen += (float)mod;
			menu_item_name_set( item, "Vehicle HP regeneration: %dhp/sec", (int)set.hp_regen );
			break;

		case ID_CHEAT_INVULN_REGEN_ONFOOT:
			set.hp_regen_onfoot += (float)mod;
			menu_item_name_set( item, "Onfoot HP regeneration: %dhp/sec", (int)set.hp_regen_onfoot );
			break;
		}
		break;
	}

	return 0;
}

static int menu_callback_cheats_money ( int op, struct menu_item *item )
{
	uint32_t	money;
	int			mod;

	switch ( op )
	{
	case MENU_OP_SELECT:
		money = gta_money_get();
		switch ( item->id )
		{
		case ID_CHEAT_MONEY_GIVE_500:
			money += 500;
			break;

		case ID_CHEAT_MONEY_GIVE_1000:
			money += 1000;
			break;

		case ID_CHEAT_MONEY_GIVE_5000:
			money += 5000;
			break;

		case ID_CHEAT_MONEY_GIVE_10000:
			money += 10000;
			break;

		case ID_CHEAT_MONEY_GIVE_20000:
			money += 20000;
			break;

		case ID_CHEAT_MONEY_GIVE_99999999:
			money += 99999999;
			break;

		case ID_CHEAT_MONEY_GIVE_CUSTOM:
			money += set.money_value;
			break;
		}

		gta_money_set( money );
		break;

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_CHEAT_MONEY_MAX:
			set.money_amount_max += 50000 * mod;
			break;

		case ID_CHEAT_MONEY_RAND_MIN:
			set.money_amount_rand_min += 500 * mod;
			break;

		case ID_CHEAT_MONEY_RAND_MAX:
			set.money_amount_rand_max += 500 * mod;
			break;

		case ID_CHEAT_MONEY_IVAL_MIN:
			set.money_interval_rand_min += 1 * mod;
			break;

		case ID_CHEAT_MONEY_IVAL_MAX:
			set.money_interval_rand_max += 1 * mod;
			break;
		}

		switch ( item->id )
		{
		case ID_CHEAT_MONEY_MAX:
			menu_item_name_set( item, "Max money: %d", (int)set.money_amount_max );
			break;

		case ID_CHEAT_MONEY_RAND_MIN:
			menu_item_name_set( item, "Random min: %d", (int)set.money_amount_rand_min );
			break;

		case ID_CHEAT_MONEY_RAND_MAX:
			menu_item_name_set( item, "Random max: %d", (int)set.money_amount_rand_max );
			break;

		case ID_CHEAT_MONEY_IVAL_MIN:
			menu_item_name_set( item, "Interval min: %dsec", (int)set.money_interval_rand_min );
			break;

		case ID_CHEAT_MONEY_IVAL_MAX:
			menu_item_name_set( item, "Interval max: %dsec", (int)set.money_interval_rand_max );
			break;

		default:
			return 0;
		}
	}

	return 0;
}

int randammo, randammoclip;
static int menu_callback_weapons ( int op, struct menu_item *item )
{
	struct weapon_entry *weapon = (struct weapon_entry *)item->data;
	struct actor_info	*actor_info = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( actor_info == NULL )
		return 0;

	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_NONE:
			return 0;

		case ID_WEAPON_ENABLE:
			return cheat_state->_generic.weapon;

		case ID_WEAPON_RANDOM:
			return set.ammo_random;
		}

		if ( weapon == NULL )
			return 0;

		if ( set.weapon[weapon->slot] == weapon )
			return 1;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_WEAPON_ENABLE )
		{
			cheat_state->_generic.weapon ^= 1;
			return 1;
		}

		if ( item->id == ID_WEAPON_RANDOM )
		{
			set.ammo_random ^= 1;
			return 1;
		}

		if ( weapon == NULL )
			return 0;

		if ( set.weapon[weapon->slot] == weapon )
		{
			set.weapon[weapon->slot] = NULL;
			return 1;
		}

		set.weapon[weapon->slot] = weapon;

		if ( !cheat_state->_generic.weapon )
			return 1;

		randammo = ( rand() % set.ammo ) + 1;
		randammoclip = ( rand() % set.ammo_clip ) + 1;
		gta_weapon_set( actor_info, set.weapon[weapon->slot]->slot, set.weapon[weapon->slot]->id, randammo, randammoclip );
		return 1;
	}

	return 0;
}

static int menu_callback_patches ( int op, struct menu_item *item )
{
	struct patch_set	*patch = &set.patch[item->id];

	if ( op == MENU_OP_ENABLED )
	{
		return patch->installed;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( patch->installed || patch->failed )
			patcher_remove( patch );
		else
			patcher_install( patch );

		return 1;
	}

	return 0;
}

static int menu_callback_samppatches ( int op, struct menu_item *item )
{
	if (item->id == ID_MENU_NETPATCHES_INPACKET || item->id == ID_MENU_NETPATCHES_INRPC ||
		item->id == ID_MENU_NETPATCHES_OUTPACKET || item->id == ID_MENU_NETPATCHES_OUTRPC)
		return 0;

	struct patch_set	*patch = &set.sampPatch[item->id];
	if ( op == MENU_OP_ENABLED )
	{
		return patch->installed;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( patch->installed || patch->failed )
			patcher_remove( patch );
		else
			patcher_install( patch );

		return 1;
	}

	return 0;
}

static int menu_callback_vehicles ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_VEHICLES_IWARP:
			return cheat_state->_generic.vehicles_warp_invert;

		case ID_VEHICLES_FREEZE:
			return cheat_state->_generic.vehicles_freeze;
		}
	}
	else if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_VEHICLES_IWARP:
			cheat_state->_generic.vehicles_warp_invert ^= 1;
			break;

		case ID_VEHICLES_FREEZE:
			cheat_state->_generic.vehicles_freeze ^= 1;
			break;

		default:
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_vehicles_sub ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT && item->id != ID_NONE )
	{
		struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
		struct vehicle_info *info = vehicle_info_get( item->id, VEHICLE_ALIVE | ((cheat_state->_generic.vehicles_freeze || !cheat_state->_generic.vehicles_warp_invert) ? 0 : VEHICLE_EMPTY) );
		float				pos[3];

		if ( vect3_near_zero( &info->base.matrix[4 * 3]) )
		{
			cheat_state_text( "Vehicle does not exist." );
			return 1;
		}


		if ( info != NULL && self != NULL )
		{
			if ( cheat_state->_generic.vehicles_warp_invert )
			{
				vect3_copy( &self->base.matrix[4 * 3], pos );
				pos[0] += sinf( -self->fCurrentRotation ) * 5.0f;
				pos[1] += cosf( -self->fCurrentRotation ) * 5.0f;
				pos[2] += 0.5f;
				cheat_vehicle_teleport( info, pos, gta_interior_id_get() );

				matrix_identity( info->base.matrix );
				vect3_copy( pos, &info->base.matrix[4 * 3] );
				vect3_mult( info->speed, 0.0f, info->speed );
				info->speed[2] = 0.05f;
				vect3_mult( info->spin, 0.0f, info->spin );
			}
			else
			{
				vect3_copy( &info->base.matrix[4 * 3], pos );
				pos[2] += 1.5f;
				cheat_teleport( pos, info->base.interior_id );
			}
		}
		else
		{
			if ( self == NULL )
			{
				cheat_state_text( "You are dead." );
			}
			else
			{
				if ( vehicle_info_get(item->id, 0) == NULL )
					cheat_state_text( "Vehicle not found." );
				else if ( vehicle_info_get(item->id, VEHICLE_ALIVE) == NULL )
					cheat_state_text( "Vehicle is destroyed." );
			}
		}

		return 1;
	}

	return 0;
}

static int menu_callback_misc ( int op, struct menu_item *item )
{
	int mod;

	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_MISC_HUDTEXT:
			return set.d3dtext_hud;

		case ID_MISC_BAD_WEAPONS:
			return cheat_state->_generic.weapon_disable;

		case ID_MISC_TRAILERS:
			return set.trailer_support;

		case ID_MISC_FPSLIMIT:
			return 0;

		case ID_MISC_TOGGLEWINDOWED:
			return set.window_mode;
		}
	}
	else if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_MISC_COORDS:
			{
				float	*pos =
					( cheat_state->state == CHEAT_STATE_VEHICLE )
						? cheat_state->vehicle.coords : cheat_state->actor.coords;
				Log( "static_teleport_name[] = \"\"" );
				Log( "static_teleport_pos[] = %.2f %.2f %.2f   %d", pos[0], pos[1], pos[2], gta_interior_id_get() );
				cheat_state_text( "Current coordinates written to log file." );
			}
			break;

		case ID_MISC_RELOAD:
			ini_reload();
			break;

		case ID_MISC_HUDTEXT:
			set.d3dtext_hud ^= 1;
			break;

		case ID_MISC_BAD_WEAPONS:
			cheat_state->_generic.weapon_disable ^= 1;
			break;

		case ID_MISC_TRAILERS:
			set.trailer_support ^= 1;
			break;

		case ID_MISC_TOGGLEWINDOWED:
			toggleWindowedMode();
			break;

		default:
			return 0;
		}

		return 1;
	}
	else if ( op == MENU_OP_DEC || MENU_OP_INC )
	{
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		if ( item->id == ID_MISC_FPSLIMIT )
		{
			set.fps_limit += (int)mod;
			menu_item_name_set( item, "FPS Limit: %d", set.fps_limit );
		}
	}

	return 0;
}

#ifdef __CHEAT_VEHRECORDING_H__
static int menu_callback_routes_drop ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_NONE )
			return 1;

		// > 9, because "Delete '.'"
		if ( item->name != NULL && strlen(item->name) > 9 )
		{
			// Remove "Delete '%s'"
			char tableName[64];
			_snprintf_s( tableName, sizeof(tableName)-1, "%s", (item->name+8) );
			tableName[ (strlen(item->name)-9) ] = NULL; // remove the last '
			rec_sqlite_dropTable( tableName );

			// reload menu
			if ( item->menu != NULL )
				menu_routes_drop_populate( item->menu );
			return 1;
		}
	}
	return 0;
}

static int menu_callback_routes_load ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_NONE )
			return 1;

		if ( item->name != NULL && strlen(item->name) > 0 )
		{
			rec_sqlite_loadTable( (char*)item->name );
			return 1;
		}
	}
	return 0;
}

static int menu_callback_routes ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == ID_ROUTES_ACTIVATED )
			return set.recording_activated;
		return 0;
	}
	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_ROUTES_ACTIVATED:
			set.recording_activated ^= 1;
			break;
		case ID_ROUTES_WRITE:
			rec_sqlite_writeTable();
			break;
		case ID_ROUTES_OPTIMIZE:
			rec_sqlite_optimizeDatabase();
			break;
		default:
			return 0;
		}
		return 1;
	}
	return 0;
}
#endif

static int menu_callback_sampmisc ( int op, struct menu_item *item )
{
	if ( g_SAMP == NULL )
		return 0;

	int mod;

	switch ( op )
	{
	case MENU_OP_ENABLED:
		{
			switch ( item->id )
			{
			case ID_MENU_SAMPMISC_FAKE_KILL:
				return 0;

			case ID_MENU_SAMPMISC_SPOOF_WEAPON:
				return cheat_state->_generic.spoof_weapon == (int)( UINT_PTR ) item->data;

			case ID_MENU_SAMPMISC_SAMP_INFO_LIST:
				return cheat_state->player_info_list;

			case ID_MENU_SAMPMISC_CHAT_TEXT:
				return ( g_Chat == NULL ) ? 0 : !g_Chat->iChatWindowMode;

			case ID_MENU_SAMPMISC_CHAT_TEXTLINES:
				return 0;

			case ID_MENU_SAMPMISC_SAMP_DRUNK:
				return ( g_Players != NULL && g_Players->pLocalPlayer != NULL && 
					g_Players->pLocalPlayer->pSAMP_Actor != NULL && 
					g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel > 2300 ) ? 1 : 0;

			case ID_MENU_SAMPMISC_RENDEROBJTXT:
				return cheat_state->_generic.objecttexts;

			case ID_MENU_SAMPMISC_RENDERPCKTXT:
				return cheat_state->_generic.pickuptexts;

			case ID_MENU_SAMPMISC_M0DCOMMANDS:
				return g_m0dCommands;

			case ID_MENU_SAMPMISC_EXTRAGM:
				return set.enable_extra_godmode;
			}
		}

	case MENU_OP_SELECT:
		{
			switch ( item->id )
			{
			case ID_MENU_SAMPMISC_SAMP_INFO_LIST:
				cheat_state->player_info_list ^= 1;
				break;

			case ID_MENU_SAMPMISC_CHAT_TEXT:
				if ( g_Chat != NULL )
					g_Chat->iChatWindowMode ^= 1;
				break;

			case ID_MENU_SAMPMISC_SAMP_DRUNK:
				if ( g_Players != NULL && g_Players->pLocalPlayer != NULL && 
					g_Players->pLocalPlayer->pSAMP_Actor != NULL )
				{
					if ( g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel > 0 )
						g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 0;
					else
						g_Players->pLocalPlayer->pSAMP_Actor->drunkLevel = 30000 + (rand()%2000);
				}
				break;

			case ID_MENU_SAMPMISC_SPOOF_WEAPON:
				if ( cheat_state->_generic.spoof_weapon == (int)(UINT_PTR) item->data )
					cheat_state->_generic.spoof_weapon = -1;
				else
					cheat_state->_generic.spoof_weapon = (int)( UINT_PTR ) item->data;
				break;

			case ID_MENU_SAMPMISC_FAKE_KILL:
				{
					struct actor_info	*info = getGTAPedFromSAMPPlayerID( (int)(UINT_PTR) item->data );
					struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
					const char			*errmsg = NULL;

					if ( g_Players == NULL )
						return 0;
					if ( g_Players->pRemotePlayer[(int)(UINT_PTR) item->data] == NULL )
						return 0;

					if ( info == NULL )
						errmsg = "Player does not exist.";
					else if ( ACTOR_IS_DEAD(info) )
						errmsg = "The player is dead.";
					if ( self == NULL )
						errmsg = "You are dead.";
					if ( g_iSpectateEnabled == 1 )
						errmsg = "You are spectating";

					if ( errmsg == NULL )
					{
						if ( cheat_state->_generic.spoof_weapon == -1 )
						{
							self->weapon_hit_type = info->weapon[info->weapon_slot].id;
						}
						else
						{
							self->weapon_hit_type = cheat_state->_generic.spoof_weapon;
						}
						self->weapon_hit_by = info;
						// self->hitpoints = 0.0f;
						sendDeath();
					}
					else
					{
						addMessageToChatWindow( errmsg );
					}
				}
				break;

			case ID_MENU_SAMPMISC_RENDEROBJTXT:
				cheat_state->_generic.objecttexts ^= 1;
				break;

			case ID_MENU_SAMPMISC_RENDERPCKTXT:
				cheat_state->_generic.pickuptexts ^= 1;
				break;

			case ID_MENU_SAMPMISC_M0DCOMMANDS:
				initChatCmds();
				break;

			case ID_MENU_SAMPMISC_EXTRAGM:
				set.enable_extra_godmode ^= 1;
				break;
			}
		}

	case MENU_OP_DEC:
	case MENU_OP_INC:
		mod = ( op == MENU_OP_DEC ) ? -1 : 1;
		switch ( item->id )
		{
		case ID_MENU_SAMPMISC_CHAT_TEXTLINES:
			set.d3dtext_chat_lines += mod;
			menu_item_name_set( item, "Display chat lines: %d", set.d3dtext_chat_lines );
			break;
		}
		break;
	}

	/*
	return 1;
}*/
	return 0;
}

static int menu_callback_players ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == ID_MENU_PLAYERS_MUTE )
			return set.anti_spam;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_MENU_PLAYERS_MUTE )
		{
			set.anti_spam ^= 1;
			// don't open submenu via select button
			return 1;
		}
	}
	return 0;
}

static int menu_callback_players_warp ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		struct actor_info	*actor = NULL;
		int					id = item->id;
		float				pos[3];

		if ( g_Players == NULL )
			return 0;

		if ( id == ID_NONE )
			return 0;

		if ( g_Players->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Player does not exist." );
			return 0;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData == NULL
		 ||	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor == NULL )
		{
			if ( vect3_near_zero(g_stStreamedOutInfo.fPlayerPos[id]) )
			{
				addMessageToChatWindow( "Player is not streamed in." );
				return 0;
			}

			g_stStreamedOutInfo.fPlayerPos[id][1] += 1.0f;
			cheat_teleport( g_stStreamedOutInfo.fPlayerPos[id], 0 );
			return 0;
		}

		if ( !getPlayerPos(id, pos) )
		{
			addMessageToChatWindow( "Bad player info." );
			return 0;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData != NULL
		 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor != NULL )
			actor = g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor->pGTA_Ped;

		if ( actor != NULL && ACTOR_IS_DEAD(actor) )
		{
			addMessageToChatWindow( "Player is dead." );
			return 0;
		}

		pos[1] += 1.0f;
		cheat_teleport( pos, actor->base.interior_id );

		return 1;
	}

	return 0;
}

static int menu_callback_players_vehwarp ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		struct actor_info	*actor = NULL;
		int					id = item->id;

		// safety checking
		if ( g_Players == NULL )
			return 0;
		if ( id == ID_NONE )
			return 0;

		if ( g_Players->pRemotePlayer[id]->pPlayerData != NULL
		 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor != NULL )
			actor = g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor->pGTA_Ped;
		if ( actor == NULL )
			return 0;
		if ( actor->vehicle == NULL )
			return 0;

		if ( g_Players->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Player does not exist." );
			return 0;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData == NULL
		 ||	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor == NULL )
		{
			addMessageToChatWindow( "Player is not streamed in." );
			return 0;
		}

		if ( actor->vehicle->hitpoints == 0.0f )
		{
			addMessageToChatWindow( "Vehicle is destroyed" );
			return 0;
		}

		if ( cheat_state->actor.air_brake )
		{
			addMessageToChatWindow( "On foot airbrake must be disabled" );
			return 0;
		}

		// if they are in a vehicle, let's GOOOO
		if ( g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_DRIVER
		 ||	 g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_PASSENGER )
		{
			//need car id in memory for vehicleJumper
			if ( g_Players->pRemotePlayer[id] != NULL
			 &&	 g_Players->pRemotePlayer[id]->pPlayerData != NULL
			 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Vehicle != NULL
			 &&	 g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle != NULL )
			{
				vehicleJumper( (int)(((DWORD) g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle) -
							   (DWORD) pool_vehicle->start) / 2584 );
			}
		}
		else
		{
			addMessageToChatWindow( "The player is not in a vehicle" );
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_vehicles_instant ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		int id = item->id;

		if ( g_Vehicles == NULL )
			return 0;

		if ( id == ID_NONE )
			return 0;

		if ( g_Vehicles->iIsListed[id] != 1 )
		{
			addMessageToChatWindow( "Vehicle does not exist." );
			return 0;
		}

		if ( g_Vehicles->pGTA_Vehicle[id] == NULL )
		{
			addMessageToChatWindow( "Vehicle is unstreamed" );
			return 0;
		}

		if ( g_Vehicles->pGTA_Vehicle[id]->hitpoints == 0.0f )
		{
			addMessageToChatWindow( "Vehicle is destroyed" );
			return 0;
		}

		if ( cheat_state->actor.stick )
		{
			addMessageToChatWindow( "On foot stick must be disabled" );
			return 0;
		}

		if ( cheat_state->actor.air_brake )
		{
			addMessageToChatWindow( "On foot airbrake must be disabled" );
			return 0;
		}

		int jump_id = (int)( ((DWORD) g_Vehicles->pGTA_Vehicle[id]) - (DWORD) pool_vehicle->start ) / 2584;
		vehicleJumper( jump_id );

		return 1;
	}

	return 0;
}

static int menu_callback_teleports ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		cheat_teleport_history_save();
		cheat_state_text( "Teleported to: %s.", set.static_teleport_name[item->id] );
		cheat_teleport( set.static_teleport[item->id].pos, set.static_teleport[item->id].interior_id );
		return 1;
	}

	return 0;
}

static int menu_callback_interiors ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_SELECT )
	{
		if ( g_SAMP != NULL )
		{
			sampPatchDisableInteriorUpdate( 1 );
			sendSetInterior( interiors_list[item->id].interior_id );
		}

		cheat_state_text( "Teleported to: %s.", interiors_list[item->id].interior_name );
		cheat_teleport( interiors_list[item->id].pos, interiors_list[item->id].interior_id );
		if ( g_SAMP != NULL )
			sampPatchDisableInteriorUpdate( 0 );
		return 1;
	}

	return 0;
}

static int menu_callback_specialaction ( int op, struct menu_item *item )
{
	if ( g_Players->pLocalPlayer == NULL )
		return 0;

	int		id = item->id;
	uint8_t specialaction = g_Players->pLocalPlayer->onFootData.byteSpecialAction;

	if ( op == MENU_OP_ENABLED )
	{
		switch ( id )
		{
		case ID_MENU_SPECIAL_ACTION_NONE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_NONE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_USEJETPACK:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_USEJETPACK )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE1:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE1 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE2:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE2 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE3:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE3 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DANCE4:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DANCE4 )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_HANDSUP:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_HANDSUP )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_USECELLPHONE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_USECELLPHONE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DRINK_BEER:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DRINK_BEER )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DRINK_WINE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DRINK_WINE )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_CUFFED:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_CUFFED )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_CARRY:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_CARRY )
				return 1;
			break;

		case ID_MENU_SPECIAL_ACTION_URINATE:
			if ( specialaction == ID_MENU_SPECIAL_ACTION_URINATE )
				return 1;
			break;
		}

		return 0;
	}

	if ( op == MENU_OP_SELECT )
	{
		setSpecialAction( id );
		return 1;
	}

	return 0;
}

static int menu_callback_debug ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == ID_DEBUG_ENABLE )
			return cheat_state->debug_enabled;
		return 0;
	}

	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_DEBUG_ENABLE:
			cheat_state->debug_enabled ^= 1;
			break;

		case ID_DEBUG_SELF_ACTOR:
			setDebugPointer( (void *)actor_info_get(ACTOR_SELF, 0) );
			break;

		case ID_DEBUG_SELF_VEHICLE:
			setDebugPointer( (void *)vehicle_info_get(VEHICLE_SELF, 0) );
			break;

		case ID_DEBUG_SAMP_DLL:
			setDebugPointer( (void *)g_dwSAMP_Addr );
			break;

		case ID_DEBUG_SAMP_INFO:
			setDebugPointer( (void *)g_SAMP );
			break;

		case ID_DEBUG_SAMP_PLAYER_LIST:
			setDebugPointer( (void *)g_Players );
			break;

		case ID_DEBUG_SAMP_LOCAL_INFO:
			setDebugPointer( (void *)g_Players->pLocalPlayer );
			break;

		case ID_DEBUG_SAMP_CHAT_INFO:
			setDebugPointer( (void *)g_Chat );
			break;

		case ID_DEBUG_SAMP_CHAT_IPT_INFO:
			setDebugPointer( (void *)g_Input );
			break;

		case ID_DEBUG_SAMP_KILL_INFO:
			setDebugPointer( (void *)g_DeathList );
			break;

		case ID_DEBUG_SAMP_VEHICLE_LIST:
			setDebugPointer( (void *)g_Vehicles );
			break;

		case ID_DEBUG_SAMP_LOCAL_SAMPPED:
			setDebugPointer( (void *)g_Players->pLocalPlayer->pSAMP_Actor );
			break;

		default:
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_hudindicators ( int op, struct menu_item *item )
{
	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case ID_HUDIND_BAR:
			return set.hud_draw_bar;

		case ID_HUDIND_TSHADOWS:
			return set.render_text_shadows;

		case ID_HUDIND_INV:
			return set.hud_indicator_inv;

		case ID_HUDIND_WEAPON:
			return set.hud_indicator_weapon;

		case ID_HUDIND_MONEY:
			return set.hud_indicator_money;

		case ID_HUDIND_FREEZE:
			return set.hud_indicator_freeze;

		case ID_HUDIND_INVEH_AIRBRK:
			return set.hud_indicator_inveh_airbrk;

		case ID_HUDIND_INVEH_STICK:
			return set.hud_indicator_inveh_stick;

		case ID_HUDIND_INVEH_BRKDANCE:
			return set.hud_indicator_inveh_brkdance;

		case ID_HUDIND_INVEH_SPIDER:
			return set.hud_indicator_inveh_spider;

		case ID_HUDIND_ONFOOT_FLY:
			return set.hud_indicator_onfoot_fly;

		case ID_HUDIND_INVEH_FLY:
			return set.hud_indicator_inveh_fly;

		case ID_HUDIND_ONFOOT_AIRBRK:
			return set.hud_indicator_onfoot_airbrk;

		case ID_HUDIND_ONFOOT_STICK:
			return set.hud_indicator_onfoot_stick;

		case ID_HUDIND_ONFOOT_AIM:
			return set.hud_indicator_onfoot_aim;

		case ID_HUDIND_POS:
			return set.hud_indicator_pos;

		case ID_HUDIND_FPS:
			return set.hud_fps_draw;

		case ID_HUDIND_LB_BARS:
			return set.left_bottom_bars_enable;

		case ID_HUDIND_SURF:
			return set.hud_indicator_surf;

		case ID_HUDIND_FREEZEROT:
			return set.hud_indicator_freezerot;
		}

		return 0;
	}

	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case ID_HUDIND_BAR:
			set.hud_draw_bar ^= 1;
			break;

		case ID_HUDIND_TSHADOWS:
			set.render_text_shadows ^= 1;
			break;

		case ID_HUDIND_INV:
			set.hud_indicator_inv ^= 1;
			break;

		case ID_HUDIND_WEAPON:
			set.hud_indicator_weapon ^= 1;
			break;

		case ID_HUDIND_MONEY:
			set.hud_indicator_money ^= 1;
			break;

		case ID_HUDIND_FREEZE:
			set.hud_indicator_freeze ^= 1;
			break;

		case ID_HUDIND_INVEH_AIRBRK:
			set.hud_indicator_inveh_airbrk ^= 1;
			break;

		case ID_HUDIND_INVEH_STICK:
			set.hud_indicator_inveh_stick ^= 1;
			break;

		case ID_HUDIND_INVEH_BRKDANCE:
			set.hud_indicator_inveh_brkdance ^= 1;
			break;

		case ID_HUDIND_INVEH_SPIDER:
			set.hud_indicator_inveh_spider ^= 1;
			break;

		case ID_HUDIND_ONFOOT_FLY:
			set.hud_indicator_onfoot_fly ^= 1;
			break;

		case ID_HUDIND_INVEH_FLY:
			set.hud_indicator_inveh_fly ^= 1;
			break;

		case ID_HUDIND_ONFOOT_AIRBRK:
			set.hud_indicator_onfoot_airbrk ^= 1;
			break;

		case ID_HUDIND_ONFOOT_STICK:
			set.hud_indicator_onfoot_stick ^= 1;
			break;

		case ID_HUDIND_ONFOOT_AIM:
			set.hud_indicator_onfoot_aim ^= 1;
			break;

		case ID_HUDIND_POS:
			set.hud_indicator_pos ^= 1;
			break;

		case ID_HUDIND_FPS:
			set.hud_fps_draw ^= 1;
			break;

		case ID_HUDIND_LB_BARS:
			set.left_bottom_bars_enable ^= 1;
			break;

		case ID_HUDIND_SURF:
			set.hud_indicator_surf ^= 1;
			break;

		case ID_HUDIND_FREEZEROT:
			set.hud_indicator_freezerot ^= 1;
			break;

		default:
			return 0;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_spec ( int op, struct menu_item *item )
{
	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( g_Players == NULL )
		return 0;
	if ( self == NULL )
		return 0;

	if ( op == MENU_OP_SELECT )
	{
		int id = item->id;
		if ( self == NULL )
		{
			addMessageToChatWindow( "You are dead." );
			return 1;
		}
		if ( id == -1 )
		{
			spectatePlayer( id );
			return 1;
		}

		if ( g_Players->pRemotePlayer[id] == NULL )
		{
			addMessageToChatWindow( "Player doesn't exist." );
			return 1;
		}

		if ( g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_WASTED
			|| ( g_Players->pRemotePlayer[id]->pPlayerData->bytePlayerState == PLAYER_STATE_NONE ) )
		{
			addMessageToChatWindow( "Could not spectate player" );
			return 1;
		}

		spectatePlayer( id );

		return 1;
	}

	return 0;
}

void	renderPlayerPoolStructure ( int iPlayerID );
int		iViewingInfoPlayer = -1;
static int menu_callback_playerinfo ( int op, struct menu_item *item )
{
	if ( g_Players == NULL )
		return 0;

	int id = item->id;
	if ( op == MENU_OP_SELECT )
	{
		if ( id == SAMP_MAX_PLAYERS + 1 )
		{
			iViewingInfoPlayer = -1;
			return 1;
		}

		iViewingInfoPlayer = id;

		return 1;
	}

	return 0;
}

static int menu_callback_playermute ( int op, struct menu_item *item )
{
	if ( g_Players == NULL )
		return 0;

	int id = item->id;
	if ( op == MENU_OP_ENABLED )
	{
		if ( id < SAMP_MAX_PLAYERS && id >= 0 )
			return g_bPlayerMuted[id];
		return 0;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( id < SAMP_MAX_PLAYERS && id >= 0 )
		{
			if ( g_bPlayerMuted[id] )
				g_iNumPlayersMuted--;
			else
				g_iNumPlayersMuted++;
			
			g_bPlayerMuted[id] ^= 1;
			return 1;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_server_list ( int op, struct menu_item *item )
{
	if ( g_SAMP == NULL && g_Players == NULL )
		return 0;

	struct fav_server	*server = &set.server[item->id];

	if ( op == MENU_OP_ENABLED )
	{
		if ( item->id == INI_SERVERS_MAX + 1 )
			return set.use_current_name;
		return 0;
	}
	else if ( op == MENU_OP_SELECT )
	{
		if ( item->id == ID_NONE )
			return 1;

		if ( item->id == INI_SERVERS_MAX + 1 )
		{
			set.use_current_name ^= 1;
			return 1;
		}
		else
		{
			if ( !set.use_current_name )
				setLocalPlayerName( server->nickname );
			changeServer( server->ip, server->port, server->password );

			return 1;
		}

		return 1;
	}

	return 0;
}

static int menu_callback_gamestate ( int op, struct menu_item *item )
{
	if ( g_SAMP == NULL )
		return 0;

	if ( op == MENU_OP_SELECT )
	{
		switch ( item->id )
		{
		case GAMESTATE_CONNECTING:
			g_SAMP->iGameState = GAMESTATE_CONNECTING;
			break;

		case GAMESTATE_CONNECTED:
			g_SAMP->iGameState = GAMESTATE_CONNECTED;
			break;

		case GAMESTATE_AWAIT_JOIN:
			g_SAMP->iGameState = GAMESTATE_AWAIT_JOIN;
			break;

		case GAMESTATE_RESTARTING:
			g_SAMP->iGameState = GAMESTATE_RESTARTING;
			break;

		case GAMESTATE_WAIT_CONNECT:
			g_SAMP->iGameState = GAMESTATE_WAIT_CONNECT;
			break;
		}

		return 1;
	}

	if ( op == MENU_OP_ENABLED )
	{
		switch ( item->id )
		{
		case GAMESTATE_CONNECTING:
			return g_SAMP->iGameState == GAMESTATE_CONNECTING;

		case GAMESTATE_CONNECTED:
			return g_SAMP->iGameState == GAMESTATE_CONNECTED;

		case GAMESTATE_AWAIT_JOIN:
			return g_SAMP->iGameState == GAMESTATE_AWAIT_JOIN;

		case GAMESTATE_RESTARTING:
			return g_SAMP->iGameState == GAMESTATE_RESTARTING;

		case GAMESTATE_WAIT_CONNECT:
			return g_SAMP->iGameState == GAMESTATE_WAIT_CONNECT;
		}
	}

	return 0;
}

static int menu_callback_netpatches(int op, struct menu_item *item)
{
	if ( g_SAMP == NULL )
		return 0;

	if (op == MENU_OP_SELECT)
	{
		if (item->id == ID_MENU_NETPATCHES_TOGGLE_ALL)
		{
			if (item->menu->count > 1)
			{
				// hacky method to get patch type of this menu
				NetPatchType type = set.netPatch[item->menu->item[1].id].type; // omg omg omg
				
				// count enabled and disabled patches
				int enabled = 0, disabled = 0;
				for (int i = 0; i < iNetPatchesCount; ++i)
				{
					if (set.netPatch[i].type != type) continue;
					if (set.netPatch[i].enabled) ++enabled;
					else ++disabled;
				}

				for (int i = 0; i < iNetPatchesCount; ++i)
				{
					if (set.netPatch[i].type != type) continue;
					set.netPatch[i].enabled = disabled > enabled ? true : false;
				}
			}
		}
		else
		{
			set.netPatch[item->id].enabled ^= true;
		}
	}
	if (op == MENU_OP_ENABLED)
	{
		if (item->id != ID_MENU_NETPATCHES_TOGGLE_ALL)
		{
			return set.netPatch[item->id].enabled;
		}
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////// FUNCTIONS DONE ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////////////////// START MENU LAYOUT /////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void menu_maybe_init ( void )
{
	traceLastFunc( "menu_maybe_init()" );
	if ( menu_init )
		return;

	struct menu *menu_main, *menu_cheats, *menu_cheats_mods, *menu_cheats_inv, *menu_cheats_money, *
		menu_cheats_weather, *menu_cheats_time, *menu_weapons, *menu_vehicles, *menu_teleports, *menu_interiors, *
			menu_misc, *menu_debug, *menu_hudindicators, *menu_patches, *menu_players, *menu_servers, *
				menu_players_warp, *menu_players_vehwarp, *menu_players_spec,
#ifdef __CHEAT_VEHRECORDING_H__
	*menu_routes, *menu_routes_load, *menu_routes_drop, 
#endif

	//*menu_cheats_handling,
	*menu_player_info, *menu_players_mute, *menu_sampmisc, *menu_spoof_weapon, *menu_fake_kill, *menu_vehicles_instant, 
	*menu_gamestate, *menu_specialaction, *menu_teleobject, *menu_telepickup, *menu_samppatches,
	*menu_netpatches_inrpc, *menu_netpatches_outrpc, *menu_netpatches_inpacket, *menu_netpatches_outpacket;

	char		name[128];
	int			i, slot;

	menu_init = 1;

	/* main menu */
	menu_main = menu_new( NULL, ID_MENU_MAIN, menu_callback_main );
	menu_cheats = menu_new( menu_main, ID_MENU_CHEATS, menu_callback_cheats );
	menu_patches = menu_new( menu_main, ID_MENU_PATCHES, menu_callback_patches );
	menu_weapons = menu_new( menu_main, ID_MENU_WEAPONS, menu_callback_weapons );
	menu_vehicles = menu_new( menu_main, ID_MENU_VEHICLES, menu_callback_vehicles );
	menu_teleports = menu_new( menu_main, ID_MENU_TELEPORTS, menu_callback_teleports );
	menu_misc = menu_new( menu_main, ID_MENU_MISC, menu_callback_misc );

	/* main menu -> cheats */
	menu_cheats_inv = menu_new( menu_cheats, ID_MENU_CHEATS_INVULN, menu_callback_cheats_invuln );
	menu_cheats_money = menu_new( menu_cheats, ID_MENU_CHEATS_MONEY, menu_callback_cheats_money );
	menu_cheats_mods = menu_new( menu_cheats, ID_MENU_CHEATS_MODS, menu_callback_cheats_mods );
	menu_cheats_weather = menu_new( menu_cheats, ID_MENU_CHEATS_WEATHER, menu_callback_cheats );
	// disabled for now until we/mta rework CHandlingEntrySA
	//menu_cheats_handling = menu_new( menu_cheats, ID_MENU_CHEATS_HANDLING, menu_callback_handling );
	menu_cheats_time = menu_new( menu_cheats, ID_MENU_CHEATS_TIME, menu_callback_cheats );
	
	/* main menu -> teleports */
	menu_interiors = menu_new( menu_teleports, ID_MENU_INTERIORS, menu_callback_interiors );
	
	/* main menu -> misc */
	menu_debug = menu_new( menu_misc, ID_MENU_DEBUG, menu_callback_debug );
	menu_hudindicators = menu_new( menu_misc, ID_MENU_HUDINDICATORS, menu_callback_hudindicators );
#ifdef __CHEAT_VEHRECORDING_H__
	menu_routes = menu_new( menu_misc, ID_MENU_ROUTES, menu_callback_routes );

	/* main menu -> misc -> routes */
	menu_routes_load = menu_new( menu_routes, ID_MENU_ROUTES_LOAD, menu_callback_routes_load );
	menu_routes_drop = menu_new( menu_routes, ID_MENU_ROUTES_DROP, menu_callback_routes_drop );
#endif

	/* samp specific */
	if ( g_dwSAMP_Addr != NULL )
	{
		// main menu
		menu_players = menu_new( menu_main, ID_MENU_PLAYERS, menu_callback_players );
		menu_servers = menu_new( menu_main, ID_MENU_SERVER_LIST, menu_callback_server_list );
		menu_sampmisc = menu_new( menu_main, ID_MENU_SAMPMISC, menu_callback_sampmisc );
		menu_samppatches = menu_new( menu_main, ID_MENU_SAMPPATCHES, menu_callback_samppatches );
		// main menu -> players
		menu_players_warp = menu_new( menu_players, ID_MENU_PLAYERS_WARP, menu_callback_players_warp );
		menu_players_vehwarp = menu_new( menu_players, ID_MENU_PLAYERS_VEHWARP, menu_callback_players_vehwarp );
		menu_players_spec = menu_new( menu_players, ID_MENU_PLAYERS_SPEC, menu_callback_spec );
		menu_player_info = menu_new( menu_players, ID_MENU_PLAYERS_INFO, menu_callback_playerinfo );
		menu_players_mute = menu_new( menu_players, ID_MENU_PLAYERS_MUTE, menu_callback_playermute );
		// main menu -> sampmisc
		menu_spoof_weapon = menu_new( menu_sampmisc, ID_MENU_SAMPMISC_SPOOF_WEAPON, menu_callback_sampmisc );
		menu_fake_kill = menu_new( menu_sampmisc, ID_MENU_SAMPMISC_FAKE_KILL, menu_callback_sampmisc );
		menu_vehicles_instant = menu_new( menu_sampmisc, ID_MENU_SAMPMISC_VEHICLES_INSTANT, menu_callback_vehicles_instant );
		menu_gamestate = menu_new( menu_sampmisc, ID_MENU_SAMPMISC_GAMESTATE, menu_callback_gamestate );
		menu_specialaction = menu_new( menu_sampmisc, ID_MENU_SAMPMISC_SPECIALACTION, menu_callback_specialaction );
		menu_teleobject = menu_new( menu_sampmisc, ID_MENU_SAMPMISC_TELEOBJECT, menu_callback_teleobject );
		menu_telepickup = menu_new( menu_sampmisc, ID_MENU_SAMPMISC_TELEPICKUP, menu_callback_telepickup );
		// main menu -> samp patches
		menu_netpatches_inrpc = menu_new( menu_samppatches, ID_MENU_NETPATCHES_INRPC, menu_callback_netpatches );
		menu_netpatches_outrpc = menu_new( menu_samppatches, ID_MENU_NETPATCHES_OUTRPC, menu_callback_netpatches );
		menu_netpatches_inpacket = menu_new( menu_samppatches, ID_MENU_NETPATCHES_INPACKET, menu_callback_netpatches );
		menu_netpatches_outpacket = menu_new( menu_samppatches, ID_MENU_NETPATCHES_OUTPACKET, menu_callback_netpatches );
	}

	/** Menu Items **/
	/* main menu */
	menu_item_add( menu_main, NULL, "\tGTA", ID_NONE, MENU_COLOR_SEPARATOR, NULL );
	menu_item_add( menu_main, menu_cheats, "Cheats", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_main, menu_weapons, "Weapons", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_main, menu_vehicles, "Vehicles", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_main, menu_teleports, "Teleports", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_main, menu_misc, "Misc.", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "GTA Patches (%d/%d)", iGTAPatchesCount, INI_PATCHES_MAX );
	menu_item_add( menu_main, menu_patches, name, ID_NONE, MENU_COLOR_DEFAULT, NULL );

	/* main menu (samp specific) */
	if ( g_dwSAMP_Addr != NULL )
	{
		menu_item_add( menu_main, NULL, "\tSA-MP", ID_NONE, MENU_COLOR_SEPARATOR, NULL );
		menu_item_add( menu_main, menu_players, "Players", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		snprintf( name, sizeof(name), "Fav. server list (%d/%d)", iServersCount, INI_SERVERS_MAX );
		menu_item_add( menu_main, menu_servers, name, ID_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_main, menu_sampmisc, "SA:MP Misc.", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		snprintf( name, sizeof(name), "SA:MP Patches (%d/%d)", iSAMPPatchesCount, INI_SAMPPATCHES_MAX );
		menu_item_add( menu_main, menu_samppatches, name, ID_NONE, MENU_COLOR_DEFAULT, NULL );
	}

	/* main menu -> cheats - menu items */
	menu_item_add( menu_cheats, menu_cheats_mods, "Vehicle upgrades", ID_CHEAT_MODS, MENU_COLOR_DEFAULT, NULL );

	//menu_item_add( menu_cheats, menu_cheats_handling, "Change vehicle handling", ID_CHEAT_HANDLING, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, menu_cheats_money, "Money", ID_CHEAT_MONEY, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, menu_cheats_inv, "Invulnerable", ID_CHEAT_INVULN, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Restore health", ID_CHEAT_HP, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Restore armor", ID_CHEAT_ARMOR, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, menu_cheats_weather, "Freeze weather", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, menu_cheats_time, "Freeze time", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Gravity: 0.0080", ID_CHEAT_GRAVITY, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Game speed: 100%", ID_CHEAT_GAME_SPEED, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Map", ID_CHEAT_MAP, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Render teleport texts", ID_CHEAT_TELETEXTS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Misc. protections", ID_CHEAT_PROT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Go to nearest empty car", ID_CHEAT_WARP_NEAR, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Give Jetpack", ID_CHEAT_JETPACK, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Unlock vehicles", ID_CHEAT_UNLOCK, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Keep trailers attached", ID_CHEAT_KEEP_TRAILER, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Toggle vehicle collisions", ID_CHEAT_NOCOLS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Chams", ID_CHEAT_CHAMS, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Custom running style: %i, ", set.custom_runanimation_id );
	menu_item_add( menu_cheats, NULL, name, ID_CHEAT_CUSTOM_RUNSTYLE, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Player Fly Speed: %0.01f", set.fly_player_speed );
	menu_item_add( menu_cheats, NULL, name, ID_CHEAT_FLY_SPEED, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Disable Water Waves", ID_CHEAT_DISABLE_WAVES, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Surf", ID_CHEAT_SURF, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Freeze vehicle spin", ID_CHEAT_FREEZEROT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats, NULL, "Draw map lines", ID_CHEAT_MAP_DRAW_LINES, MENU_COLOR_DEFAULT, NULL );

	/* main menu -> cheats -> invulnerable */
	menu_item_add( menu_cheats_inv, NULL, "Actor invulnerability", ID_CHEAT_INVULN_ACTOR, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_inv, NULL, "Vehicle invulnerability", ID_CHEAT_INVULN_VEHICLE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_inv, NULL, "Vehicle tire protections", ID_CHEAT_INVULN_TIRES, MENU_COLOR_DEFAULT, NULL );

	/*menu_item_add(menu_cheats_inv, NULL, "\t", ID_NONE, MENU_COLOR_SEPARATOR, NULL);*/
	snprintf( name, sizeof(name), "Vehicle minimum HP: %d", (int)set.hp_minimum );
	menu_item_add( menu_cheats_inv, NULL, name, ID_CHEAT_INVULN_MIN_HP, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Vehicle HP regeneration: %dhp/sec", (int)set.hp_regen );
	menu_item_add( menu_cheats_inv, NULL, name, ID_CHEAT_INVULN_REGEN, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Onfoot HP regeneration: %dhp/sec", (int)set.hp_regen );
	menu_item_add( menu_cheats_inv, NULL, name, ID_CHEAT_INVULN_REGEN_ONFOOT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_inv, NULL, "Single Player Enemies vulnerable", 
		ID_CHEAT_INVULN_DISABLE_EXTRA_INV, MENU_COLOR_DEFAULT, NULL );
	// actor invulnerability additional values
	menu_item_add(menu_cheats_inv, NULL, "Additional actor inv.:", ID_NONE, MENU_COLOR_SEPARATOR, NULL);
	menu_item_add( menu_cheats_inv, NULL, "Explosion invulnerability", ID_CHEAT_INVULN_ACT_EXPL_INV, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_inv, NULL, "Fall invulnerability", ID_CHEAT_INVULN_ACT_FALL_INV, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_inv, NULL, "Fire invulnerability", ID_CHEAT_INVULN_ACT_FIRE_INV, MENU_COLOR_DEFAULT, NULL );

	/* main menu -> cheats -> money */
	menu_item_add( menu_cheats_money, NULL, "Give $500", ID_CHEAT_MONEY_GIVE_500, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $1000", ID_CHEAT_MONEY_GIVE_1000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $5000", ID_CHEAT_MONEY_GIVE_5000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $10000", ID_CHEAT_MONEY_GIVE_10000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $20000", ID_CHEAT_MONEY_GIVE_20000, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_cheats_money, NULL, "Give $99999999", ID_CHEAT_MONEY_GIVE_99999999, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Give custom .ini value ($%d)", (int)set.money_value );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_GIVE_CUSTOM, MENU_COLOR_DEFAULT, NULL );

	menu_item_add( menu_cheats_money, NULL, "\tSettings", ID_NONE, MENU_COLOR_SEPARATOR, NULL );
	snprintf( name, sizeof(name), "Max money: %d", (int)set.money_amount_max );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_MAX, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Random min: %d", (int)set.money_amount_rand_min );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_RAND_MIN, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Random max: %d", (int)set.money_amount_rand_max );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_RAND_MAX, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Interval min: %dsec", (int)set.money_interval_rand_min );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_IVAL_MIN, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "Interval max: %dsec", (int)set.money_interval_rand_max );
	menu_item_add( menu_cheats_money, NULL, name, ID_CHEAT_MONEY_IVAL_MAX, MENU_COLOR_DEFAULT, NULL );

	/* main menu -> cheats -> weather */
	const struct
	{
		int		id;
		char	*name;
	}

	weather_map[] =
	{
		0,
		"Blue sky",
		8,
		"Stormy",
		9,
		"Cloudy and foggy",
		10,
		"Clear blue sky",
		11,
		"Scorching hot (heat waves)",
		12,
		"Very dull, colorless, hazy",
		16,
		"Dull, cloudy, rainy",
		17,
		"Scorching hot",
		19,
		"Sandstorm",
		20,
		"Greenish fog",
		21,
		"Very dark, gradiented skyline, purple",
		22,
		"Very dark, gradiented skyline, green",
		23,
		"Variations of pale orange",
		27,
		"Variations of fresh blue",
		30,
		"Variations of dark, cloudy, teal",
		33,
		"Dark, cloudy, brown",
		34,
		"Blue, purple, regular",
		35,
		"Dull brown",
		36,
		"Extremely bright",
		40,
		"Blue, purple, cloudy",
		43,
		"Dark toxic clouds",
		44,
		"Black, white sky",
		45,
		"Black, purple sky",
		-1,
		NULL
	};
	for ( i = 0;; i++ )
	{
		if ( weather_map[i].name == NULL )
			break;
		menu_item_add( menu_cheats_weather, NULL, weather_map[i].name, ID_CHEAT_WEATHER, MENU_COLOR_DEFAULT,
					   (void *)(UINT_PTR) weather_map[i].id );
	}

	/* main menu -> cheats -> time */
	for ( i = 0; i < 24; i++ )
	{
		snprintf( name, sizeof(name), "%02d:00", i );
		menu_item_add( menu_cheats_time, NULL, name, ID_CHEAT_TIME, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}

	/* main menu -> weapons */
	menu_item_add( menu_weapons, NULL, "Enable weapon cheat", ID_WEAPON_ENABLE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_weapons, NULL, "Randomize ammo values", ID_WEAPON_RANDOM, MENU_COLOR_DEFAULT, NULL );
	for ( slot = 0; slot < 13; slot++ )
	{
		const struct weapon_entry	*weapon = weapon_list;

		snprintf( name, sizeof(name), "\tSlot %d", slot );
		menu_item_add( menu_weapons, NULL, name, ID_NONE, MENU_COLOR_SEPARATOR, NULL );

		while ( weapon->name != NULL )
		{
			if ( weapon->slot == slot )
				menu_item_add( menu_weapons, NULL, weapon->name, ID_WEAPON_ITEM, MENU_COLOR_DEFAULT, (void *)weapon );
			weapon++;
		}
	}

	/* main menu -> vehicles */
	for ( i = 0; i < VEHICLE_CLASS_COUNT; i++ )
	{
		struct menu *menu = menu_new( menu_vehicles, ID_MENU_VEHICLES_SUB, menu_callback_vehicles_sub );

		snprintf( name, sizeof(name), "%s", gta_vehicle_class_name(i) );
		menu_item_add( menu_vehicles, menu, name, ID_NONE, MENU_COLOR_DEFAULT, (void *)(UINT_PTR) i );
	}

	menu_item_add( menu_vehicles, NULL, "Freeze nearby vehicles", ID_VEHICLES_FREEZE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_vehicles, NULL, "Warp vehicles to you", ID_VEHICLES_IWARP, MENU_COLOR_DEFAULT, NULL );


	/* main menu -> patches */
	for ( i = 0; i < INI_PATCHES_MAX; i++ )
	{
		if ( set.patch[i].name == NULL )
			continue;

		menu_item_add( menu_patches, NULL, set.patch[i].name, i, MENU_COLOR_DEFAULT, NULL );
	}

	if ( g_dwSAMP_Addr != NULL )
	{
		/* main menu -> players */
		menu_item_add( menu_players, menu_players_warp, "Warp to player", ID_MENU_PLAYERS_WARP, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_players, menu_players_vehwarp, "Warp instantly to player's vehicle", ID_MENU_PLAYERS_VEHWARP, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_players, menu_players_spec, "Spectate player", ID_MENU_PLAYERS_SPEC, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_players, menu_player_info, "Show infos on player", ID_MENU_PLAYERS_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_players, menu_players_mute, "Mute player chat (Anti-spam)", ID_MENU_PLAYERS_MUTE, MENU_COLOR_DEFAULT, NULL );

		// net patches
		menu_item_add( menu_samppatches, menu_netpatches_inrpc, "Disable incoming RPC", ID_MENU_NETPATCHES_INRPC, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_samppatches, menu_netpatches_outrpc, "Disable outcoming RPC", ID_MENU_NETPATCHES_OUTRPC, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_samppatches, menu_netpatches_inpacket, "Disable incoming packet", ID_MENU_NETPATCHES_INPACKET, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_samppatches, menu_netpatches_outpacket, "Disable outcoming packet", ID_MENU_NETPATCHES_OUTPACKET, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_inrpc, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_outrpc, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_inpacket, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_netpatches_outpacket, NULL, "Toggle all", ID_MENU_NETPATCHES_TOGGLE_ALL, MENU_COLOR_DEFAULT, NULL );

		int netPatchNumber[4] = { 1, 1, 1, 1 };
		for (i = 0; i < iNetPatchesCount; ++i)
		{
			menu *pmenu = nullptr;
			stNetPatch &patch = set.netPatch[i];
			sprintf_s(name, "%d. %s", netPatchNumber[patch.type]++, patch.name);
			switch (patch.type)
			{
			case INCOMING_RPC: pmenu = menu_netpatches_inrpc; break;
			case OUTCOMING_RPC: pmenu = menu_netpatches_outrpc; break;
			case INCOMING_PACKET: pmenu = menu_netpatches_inpacket; break;
			case OUTCOMING_PACKET: pmenu = menu_netpatches_outpacket; break;
			}
			if (pmenu != nullptr)
				menu_item_add(pmenu, NULL, name, i, MENU_COLOR_DEFAULT, NULL);
		}

		// samp patches
		for ( i = 0; i < INI_SAMPPATCHES_MAX; i++ )
		{
			if ( set.sampPatch[i].name == NULL )
				continue;

			menu_item_add( menu_samppatches, NULL, set.sampPatch[i].name, i, MENU_COLOR_DEFAULT, NULL );
		}

		// server list
		menu_item_add( menu_servers, NULL, "Keep your current nickname", INI_SERVERS_MAX + 1, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_servers, NULL, "\tServers", ID_NONE, MENU_COLOR_SEPARATOR, NULL );
		for ( i = 0; i < INI_SERVERS_MAX; i++ )
		{
			if ( set.server[i].server_name == NULL )
				continue;

			menu_item_add( menu_servers, NULL, set.server[i].server_name, i, MENU_COLOR_DEFAULT, NULL );
		}
	}

	/* teleports */
	menu_item_add( menu_teleports, menu_interiors, "Teleport to interiors", STATIC_TELEPORT_MAX + 1, MENU_COLOR_DEFAULT,
				   NULL );
	for ( i = 0; i < 146; i++ )
	{
		menu_item_add( menu_interiors, NULL, interiors_list[i].interior_name, i, MENU_COLOR_DEFAULT, NULL );
	}

	for ( i = 0; i < STATIC_TELEPORT_MAX; i++ )
	{
		if ( strlen(set.static_teleport_name[i]) == 0 )
			continue;

		if ( vect3_near_zero(set.static_teleport[i].pos) )
			continue;

		menu_item_add( menu_teleports, NULL, set.static_teleport_name[i], i, MENU_COLOR_DEFAULT, NULL );
	}

	/* misc */
	menu_item_add( menu_misc, menu_debug, "Debug", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Write coordinates to log file", ID_MISC_COORDS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Reload settings", ID_MISC_RELOAD, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Enable HUD text", ID_MISC_HUDTEXT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Disable bad weapons", ID_MISC_BAD_WEAPONS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Trailer support", ID_MISC_TRAILERS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, menu_hudindicators, "Toggle HUD indicators", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	snprintf( name, sizeof(name), "FPS limit: %d", set.fps_limit );
	menu_item_add( menu_misc, NULL, name, ID_MISC_FPSLIMIT, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_misc, NULL, "Toggle windowed mode", ID_MISC_TOGGLEWINDOWED, MENU_COLOR_DEFAULT, NULL );
#ifdef __CHEAT_VEHRECORDING_H__
	menu_item_add( menu_misc, menu_routes, "Routes", ID_NONE, MENU_COLOR_DEFAULT, NULL );
#endif

	/* misc -> debug */
	menu_item_add( menu_debug, NULL, "Enable", ID_DEBUG_ENABLE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_debug, NULL, "Self actor", ID_DEBUG_SELF_ACTOR, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_debug, NULL, "Self vehicle", ID_DEBUG_SELF_VEHICLE, MENU_COLOR_DEFAULT, NULL );

	if ( g_dwSAMP_Addr != NULL )
	{
		menu_item_add( menu_debug, NULL, "SA:MP DLL", ID_DEBUG_SAMP_DLL, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Info", ID_DEBUG_SAMP_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Player List", ID_DEBUG_SAMP_PLAYER_LIST, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Local info", ID_DEBUG_SAMP_LOCAL_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Vehicle List", ID_DEBUG_SAMP_VEHICLE_LIST, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Chat info", ID_DEBUG_SAMP_CHAT_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Input info", ID_DEBUG_SAMP_CHAT_IPT_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Kill info", ID_DEBUG_SAMP_KILL_INFO, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_debug, NULL, "SA:MP Local SAMP-PED", ID_DEBUG_SAMP_LOCAL_SAMPPED, MENU_COLOR_DEFAULT, NULL );
	}

#ifdef __CHEAT_VEHRECORDING_H__
	/* misc -> routes */
	menu_item_add( menu_routes, NULL, "Enable Routes function", ID_ROUTES_ACTIVATED, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, menu_routes_load, "Load Route", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, menu_routes_drop, "Delete Route", ID_NONE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, NULL, "Save current Route", ID_ROUTES_WRITE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_routes, NULL, "Optimize Database (Rebuild)", ID_ROUTES_OPTIMIZE, MENU_COLOR_DEFAULT, NULL );
#endif

	// misc -> HUD indicators
	menu_item_add( menu_hudindicators, NULL, "Draw bottom bar", ID_HUDIND_BAR, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Render text shadows", ID_HUDIND_TSHADOWS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Inv", ID_HUDIND_INV, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Weapon", ID_HUDIND_WEAPON, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Money", ID_HUDIND_MONEY, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Freeze", ID_HUDIND_FREEZE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "In vehicle AirBrk", ID_HUDIND_INVEH_AIRBRK, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "In vehicle Stick", ID_HUDIND_INVEH_STICK, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "In vehicle BrkDance", ID_HUDIND_INVEH_BRKDANCE, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "In vehicle SpiderWheels", ID_HUDIND_INVEH_SPIDER, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "In vehicle Fly", ID_HUDIND_INVEH_FLY, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "On foot AirBrk", ID_HUDIND_ONFOOT_AIRBRK, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "On foot Stick", ID_HUDIND_ONFOOT_STICK, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "On foot Fly", ID_HUDIND_ONFOOT_FLY, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Aim", ID_HUDIND_ONFOOT_AIM, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Surf", ID_HUDIND_SURF, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "FreezeRot", ID_HUDIND_FREEZEROT, MENU_COLOR_DEFAULT, NULL );

	menu_item_add( menu_hudindicators, NULL, "Position", ID_HUDIND_POS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "FPS", ID_HUDIND_FPS, MENU_COLOR_DEFAULT, NULL );
	menu_item_add( menu_hudindicators, NULL, "Toggle left bottom bars", ID_HUDIND_LB_BARS, MENU_COLOR_DEFAULT, NULL );

	if ( g_dwSAMP_Addr != NULL )
	{
		// main menu -> sampmisc
		menu_item_add( menu_sampmisc, menu_vehicles_instant, "Warp instantly to vehicle", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, menu_fake_kill, "Fake kill", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, menu_spoof_weapon, "Spoof weapon", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Player info list", ID_MENU_SAMPMISC_SAMP_INFO_LIST, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Replace chat text rendering", ID_MENU_SAMPMISC_CHAT_TEXT, MENU_COLOR_DEFAULT, NULL );
		snprintf( name, sizeof(name), "Display chat lines: %d", set.d3dtext_chat_lines );
		menu_item_add( menu_sampmisc, NULL, name, ID_MENU_SAMPMISC_CHAT_TEXTLINES, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, menu_gamestate, "Change game state", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, menu_specialaction, "Special action", ID_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Drunk", ID_MENU_SAMPMISC_SAMP_DRUNK, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, menu_teleobject, "Teleport to object", ID_MENU_SAMPMISC_TELEOBJECT, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Render object texts", ID_MENU_SAMPMISC_RENDEROBJTXT, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, menu_telepickup, "Teleport to pickup", ID_MENU_SAMPMISC_TELEPICKUP, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Render pickup texts", ID_MENU_SAMPMISC_RENDERPCKTXT, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Load M0D-Commands", ID_MENU_SAMPMISC_M0DCOMMANDS, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_sampmisc, NULL, "Extra godmode", ID_MENU_SAMPMISC_EXTRAGM, MENU_COLOR_DEFAULT, NULL );

		/* main menu -> sampmisc -> change game state */
		menu_item_add( menu_gamestate, NULL, "Connecting", GAMESTATE_CONNECTING, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Connected", GAMESTATE_CONNECTED, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Await join", GAMESTATE_AWAIT_JOIN, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Game mode restarting", GAMESTATE_RESTARTING, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_gamestate, NULL, "Wait connect", GAMESTATE_WAIT_CONNECT, MENU_COLOR_DEFAULT, NULL );

		/* main menu -> sampmisc -> special action */
		menu_item_add( menu_specialaction, NULL, "None", ID_MENU_SPECIAL_ACTION_NONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Smoke Blunt", ID_MENU_SPECIAL_ACTION_SMOKE_CIGGY, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Drink Beer", ID_MENU_SPECIAL_ACTION_DRINK_BEER, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Drink Wine", ID_MENU_SPECIAL_ACTION_DRINK_WINE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Drink Sprunk", ID_MENU_SPECIAL_ACTION_DRINK_SPRUNK, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Use Jetpack", ID_MENU_SPECIAL_ACTION_USEJETPACK, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance1", ID_MENU_SPECIAL_ACTION_DANCE1, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance2", ID_MENU_SPECIAL_ACTION_DANCE2, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance3", ID_MENU_SPECIAL_ACTION_DANCE3, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Dance4", ID_MENU_SPECIAL_ACTION_DANCE4, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Hands Up", ID_MENU_SPECIAL_ACTION_HANDSUP, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Use Cellphone", ID_MENU_SPECIAL_ACTION_USECELLPHONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Stop Use Cellphone", ID_MENU_SPECIAL_ACTION_STOPUSECELLPHONE, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Cuffed", ID_MENU_SPECIAL_ACTION_CUFFED, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Carry", ID_MENU_SPECIAL_ACTION_CARRY, MENU_COLOR_DEFAULT, NULL );
		menu_item_add( menu_specialaction, NULL, "Urinate", ID_MENU_SPECIAL_ACTION_URINATE, MENU_COLOR_DEFAULT, NULL );

		/* main menu -> sampmisc -> fake weapon */
		for ( i = 0; weapon_list[i].name != NULL; i++ )
		{
			const struct weapon_entry	*weapon = &weapon_list[i];

			if ( strcmp(weapon->name, "Camera") == 0
			 ||	 strcmp(weapon->name, "NV Goggles") == 0
			 ||	 strcmp(weapon->name, "IR Goggles") == 0
			 ||	 strcmp(weapon->name, "Parachute") == 0
			 ||	 strcmp(weapon->name, "Detonator") == 0 ) continue;

			snprintf( name, sizeof(name), "Fake killed by %s", weapon->name );
			menu_item_add( menu_spoof_weapon, NULL, name, ID_MENU_SAMPMISC_SPOOF_WEAPON, MENU_COLOR_DEFAULT,
						   (void *)(UINT_PTR) weapon->id );
		}

		menu_item_add( menu_spoof_weapon, NULL, "Fake death by fall", ID_MENU_SAMPMISC_SPOOF_WEAPON, MENU_COLOR_DEFAULT,
					   (void *)(UINT_PTR) 20 );
		menu_item_add( menu_spoof_weapon, NULL, "Fake begin run over", ID_MENU_SAMPMISC_SPOOF_WEAPON, MENU_COLOR_DEFAULT,
					   (void *)(UINT_PTR) 21 );
	}

	menu_active = menu_main;
}

static void menu_free ( struct menu *menu )
{
	int i;

	for ( i = 0; i < menu->count; i++ )
	{
		if ( menu->item[i].submenu != NULL )
		{
			menu_free( menu->item[i].submenu );
			if ( menu->item[i].name != NULL )
				free( (void *)menu->item[i].name );
		}
	}

	/*if(menu->parent != NULL)
   {
      struct menu *parent = menu->parent;
      for(i=0; i<parent->count; i++)
      {
         if(menu->item[i].submenu == menu)
            menu->item[i].submenu = NULL;
      }
   }*/
	free( menu->item );
	free( menu );
}

void menu_items_free ( struct menu *menu )
{
	int i;

	if ( menu == NULL )
		return;

	for ( i = 0; i < menu->count; i++ )
	{
		if ( menu->item[i].submenu != NULL )
		{
			menu_free( menu->item[i].submenu );
			if ( menu->item[i].name != NULL )
				free( (void *)menu->item[i].name );
		}
	}

	free( menu->item );
	menu->item = NULL;
	menu->count = 0;
	menu->pos = 0;
	menu->top_pos = 0;
}

void menu_free_all ( void )
{
	struct menu *menu;

	if ( menu_active == NULL )
		return;

	/* find root menu */
	for ( menu = menu_active; menu->parent != NULL; menu = menu->parent );

	menu_free( menu );
	menu_active = NULL;
	menu_init = 0;
}
