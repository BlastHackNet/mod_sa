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

#define TYPE_KEY		0
#define TYPE_BOOL		1			/* int */
#define TYPE_INT		2
#define TYPE_FLOAT		3
#define TYPE_VECTOR		4
#define TYPE_COORD		5
#define TYPE_STRING		6
#define TYPE_WEAPON		7
#define TYPE_PATCH		8
#define TYPE_SAMPPATCH	9
#define TYPE_UMPPATCH	10
#define TYPE_DWORD		11
#define TYPE_SERVER		12
#define TYPE_CHATMSG	13
#define TYPE_GUI		14
#define TYPE_KEYCOMBO	15
#define TYPE_NETPATCH	16

#define LTRIM( str ) \
	while ( *(str) == '\t' || *(str) == ' ' ) \
		( str )++

	struct key_alias
{
	int		key;
	char	*name;
};

struct ini_entry_data
{
	int			count;				/* number of times it has been set */
	void		*data;				/* teh value */
	const char	*def;				/* default */
};

struct ini_entry
{
	const char				*name;
	int						type;
	int						size;	/* number of data items (1 for non-arrays) */
	struct ini_entry_data	*data;	/* size # of ini_entry_data */
};

struct settings			set;

static struct key_alias key_alias[] =
{
	{ VK_LBUTTON, "lbutton" },
	{ VK_RBUTTON, "rbutton" },
	{ VK_MBUTTON, "mbutton" },
	{ VK_XBUTTON1, "mouse_4" },
	{ VK_XBUTTON2, "mouse_5" },
	{ VK_BACK, "backspace" },
	{ VK_TAB, "tab" },
	{ VK_RETURN, "return" },
	{ VK_LSHIFT, "lshift" },
	{ VK_RSHIFT, "rshift" },
	{ VK_LCONTROL, "lctrl" },
	{ VK_RCONTROL, "rctrl" },
	{ VK_LMENU, "lalt" },
	{ VK_RMENU, "ralt" },
	{ VK_SPACE, "space" },
	{ VK_PRIOR, "pageup" },
	{ VK_NEXT, "pagedn" },
	{ VK_END, "end" },
	{ VK_HOME, "home" },
	{ VK_LEFT, "left" },
	{ VK_UP, "up" },
	{ VK_RIGHT, "right" },
	{ VK_DOWN, "down" },
	{ VK_INSERT, "insert" },
	{ VK_DELETE, "delete" },
	{ VK_PAUSE, "pause" },
	{ VK_NUMPAD0, "np0" },
	{ VK_NUMPAD1, "np1" },
	{ VK_NUMPAD2, "np2" },
	{ VK_NUMPAD3, "np3" },
	{ VK_NUMPAD4, "np4" },
	{ VK_NUMPAD5, "np5" },
	{ VK_NUMPAD6, "np6" },
	{ VK_NUMPAD7, "np7" },
	{ VK_NUMPAD8, "np8" },
	{ VK_NUMPAD9, "np9" },
	{ VK_MULTIPLY, "multiply" },
	{ VK_ADD, "add" },
	{ VK_SEPARATOR, "separator" },
	{ VK_SUBTRACT, "subtract" },
	{ VK_DECIMAL, "decimal" },
	{ VK_DIVIDE, "divide" },
	{ VK_F1, "f1" },
	{ VK_F2, "f2" },
	{ VK_F3, "f3" },
	{ VK_F4, "f4" },
	{ VK_F5, "f5" },
	{ VK_F6, "f6" },
	{ VK_F7, "f7" },
	{ VK_F8, "f8" },
	{ VK_F9, "f9" },
	{ VK_F10, "f10" },
	{ VK_F11, "f11" },
	{ VK_F12, "f12" },
	{ VK_F13, "f13" },
	{ VK_F14, "f14" },
	{ VK_F15, "f15" },
	{ VK_F16, "f16" },
	{ VK_F17, "f17" },
	{ VK_F18, "f18" },
	{ VK_F19, "f19" },
	{ VK_F20, "f20" },
	{ VK_F21, "f21" },
	{ VK_F22, "f22" },
	{ VK_F23, "f23" },
	{ VK_F24, "f24" },
	{ VK_OEM_PLUS, "oem_plus" },
	{ VK_OEM_COMMA, "oem_comma" },
	{ VK_OEM_MINUS, "oem_minus" },
	{ VK_OEM_PERIOD, "oem_period" },
	{ VK_OEM_1, "oem_1" },
	{ VK_OEM_2, "oem_2" },
	{ VK_OEM_3, "oem_3" },
	{ VK_OEM_4, "oem_4" },
	{ VK_OEM_5, "oem_5" },
	{ VK_OEM_6, "oem_6" },
	{ VK_OEM_7, "oem_7" },
	{ VK_OEM_8, "oem_8" },
	{ -1, NULL }
};

static struct ini_entry *ini_entry;
static int				ini_entry_count;

static const char *ini_entry_name ( const struct ini_entry *ent, int idx )
{
	static char str[64];

	if ( ent->size == 1 )
		return ent->name;

	if ( idx == -1 )
		snprintf( str, sizeof(str), "%s[]", ent->name );
	else
		snprintf( str, sizeof(str), "%s[%d]", ent->name, idx );

	return str;
}

static int parse_int ( const char *str )
{
	return strtol( str, NULL, 0 );
}

static int key_lookup ( const char *name )
{
	if ( name[0] && !name[1] )
	{
		if ( name[0] >= 'a' && name[0] <= 'z' )
			return 'A' + ( name[0] - 'a' );
		if ( name[0] >= '0' && name[0] <= '9' )
			return name[0];
	}

	if ( name[0] == '&' )
		return parse_int( name + 1 );

	int i = 0;
	while ( key_alias[i].name != NULL )
	{
		if ( strcmp(key_alias[i].name, name) == 0 )
			return key_alias[i].key;
		i++;
	}

	Log( "Unknown key: %s", name );

	return -1;
}

static struct ini_entry_data *ini_register_data ( struct ini_entry *ent, void *data, const char *def )
{
	struct ini_entry_data	*d;
	void					*tmp;

	ent->size++;
	tmp = realloc( ent->data, ent->size * sizeof(struct ini_entry_data) );
	if ( tmp == NULL )
		goto out;
	ent->data = (struct ini_entry_data *)tmp;

	d = &ent->data[ent->size - 1];
	d->count = 0;
	d->data = data;
	d->def = _strdup( def );

	return d;
out: ;
	ent->size--;
	return NULL;
}

static struct ini_entry *ini_register_entry ( const char *name, int type )
{
	struct ini_entry	*ent = NULL;
	void				*tmp;

	ini_entry_count++;

	tmp = realloc( ini_entry, ini_entry_count * sizeof(struct ini_entry) );
	if ( tmp == NULL )
		goto out;
	ini_entry = (struct ini_entry *)tmp;

	ent = &ini_entry[ini_entry_count - 1];

	ent->name = _strdup( name );
	ent->type = type;
	ent->size = 0;
	ent->data = NULL;

	return ent;

out: ;
	ini_entry_count--;
	return NULL;
}

void ini_free ( void )
{
	struct ini_entry	*ent;
	int					i, j, c;

	for ( i = 0; i < ini_entry_count; i++ )
	{
		ent = &ini_entry[i];
		for ( j = 0; j < ent->size; j++ )
		{
			if ( ent->data[j].def != NULL )
				free( (void *)ent->data[j].def );

			if ( ent->type == TYPE_PATCH )
			{
				struct patch_set	*patch = (struct patch_set *)ent->data[j].data;
				if ( patch->name != NULL )
				{
					free( (void *)patch->name );
					for ( c = 0; c < PATCHER_CHUNKS_MAX; c++ )
					{
						if ( patch->chunk[c].ptr == NULL )
							break;

						free( (void *)patch->chunk[c].data_cmp );
						free( (void *)patch->chunk[c].data_rep );
					}

					patcher_free( patch );
				}
			}
		}

		if ( ent->name != NULL )
			free( (void *)ent->name );
	}

	free( ini_entry );
	ini_entry_count = 0;
}

static void ini_init ( void )
{
	struct ini_entry	*ent;
	int					i;

	if ( (ent = ini_register_entry("run_mode", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.run_mode, "1" );
	if ( (ent = ini_register_entry("wine_compatibility", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.wine_compatibility, "false" );

	if ( (ent = ini_register_entry("i_have_edited_the_ini_file", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.i_have_edited_the_ini_file, "false" );

	if ( (ent = ini_register_entry("fps_limit", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.fps_limit, "60" );

	// basic mode
	if ( (ent = ini_register_entry("basic_mode", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.basic_mode, "true" );

	/* hp cheat */
	if ( (ent = ini_register_entry("key_hp_cheat", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_hp_cheat, "insert" );
	if ( (ent = ini_register_entry("hp_minimum", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.hp_minimum, "0.0" );
	if ( (ent = ini_register_entry("hp_regen", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.hp_regen, "1.0" );
	if ( (ent = ini_register_entry("hp_regen_onfoot", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.hp_regen_onfoot, "1.0" );
	if ( (ent = ini_register_entry("hp_actor_explosion_inv", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hp_actor_explosion_inv, "true" );
	if ( (ent = ini_register_entry("hp_actor_fall_inv", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hp_actor_fall_inv, "true" );
	if ( (ent = ini_register_entry("hp_actor_fire_inv", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hp_actor_fire_inv, "true" );
	if ( (ent = ini_register_entry("hp_keep_vehicleHPsane", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hp_keep_vehicleHPsane, "false" );
	if ( (ent = ini_register_entry("hp_disable_inv_sp_enemies", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hp_disable_inv_sp_enemies, "false" );

	/* key anti freeze */
	if ( (ent = ini_register_entry("key_anti_freeze", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_anti_freeze, "b" );

	/* air brake */
	if ( (ent = ini_register_entry("key_air_brake_mod", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_mod, "rshift" );
	if ( (ent = ini_register_entry("key_air_brake_foot_mod", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_foot_mod, "rshift" );
	if ( (ent = ini_register_entry("key_air_brake_mod2", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_mod2, "&0" );

	/* movement */
	if ( (ent = ini_register_entry("key_air_brake_forward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_forward, "w" );
	if ( (ent = ini_register_entry("key_air_brake_backward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_backward, "s" );
	if ( (ent = ini_register_entry("key_air_brake_left", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_left, "a" );
	if ( (ent = ini_register_entry("key_air_brake_right", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_right, "d" );
	if ( (ent = ini_register_entry("key_air_brake_up", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_up, "up" );
	if ( (ent = ini_register_entry("key_air_brake_down", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_down, "down" );

	/* rotation */
	if ( (ent = ini_register_entry("key_air_brake_rot_yaw1", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_rot_yaw1, "h" );
	if ( (ent = ini_register_entry("key_air_brake_rot_yaw2", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_rot_yaw2, "k" );
	if ( (ent = ini_register_entry("key_air_brake_rot_roll1", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_rot_roll1, "n" );
	if ( (ent = ini_register_entry("key_air_brake_rot_roll2", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_rot_roll2, "m" );
	if ( (ent = ini_register_entry("key_air_brake_rot_pitch1", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_rot_pitch1, "u" );
	if ( (ent = ini_register_entry("key_air_brake_rot_pitch2", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_air_brake_rot_pitch2, "j" );

	/* misc */
	if ( (ent = ini_register_entry("air_brake_toggle", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.air_brake_toggle, "true" );
	if ( (ent = ini_register_entry("air_brake_behaviour", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.air_brake_behaviour, "2" );

	/* speed */
	if ( (ent = ini_register_entry("air_brake_speed", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.air_brake_speed, "100.0" );
	if ( (ent = ini_register_entry("air_brake_rot_speed", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.air_brake_rot_speed, "0.4" );
	if ( (ent = ini_register_entry("air_brake_accel_time", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.air_brake_accel_time, "0.5" );

	/* warp */
	if ( (ent = ini_register_entry("key_warp_mod", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_warp_mod, "lshift r" );
	if ( (ent = ini_register_entry("warp_speed", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.warp_speed, "7.0" );
	if ( (ent = ini_register_entry("warp_use_speed", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.warp_use_speed, "true" );

	//blinking car lights
	if ( (ent = ini_register_entry("key_blinking_car_lights", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_blinking_car_lights, "f2" );
	if ( (ent = ini_register_entry("enable_car_lights_at_day_time", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.enable_car_lights_at_day_time, "false" );

	//keep trailer, wall collision
	if ( (ent = ini_register_entry("key_keep_trailer", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_keep_trailer, "f1" );
	if ( (ent = ini_register_entry("key_disable_Wall_Collisions", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_disable_Wall_Collisions, "&0" );
	if ( (ent = ini_register_entry("wall_collisions_disableObjects", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.wall_collisions_disableObjects, "false" );
	if ( (ent = ini_register_entry("wall_collisions_disableRender", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.wall_collisions_disableRender, "true" );

	// repair car
	if ( (ent = ini_register_entry("key_repair_car", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_repair_car, "1" );

	// real nitro
	if ( (ent = ini_register_entry("key_nitro", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_nitro, "np0" );

#ifdef __CHEAT_VEHRECORDING_H__
	/* (vehicle) recording mod */
	if ( (ent = ini_register_entry("recording_activated", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.recording_activated, "false" );
	if ( (ent = ini_register_entry("recording_maxDistToEntryPoint", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.recording_maxDistToEntryPoint, "0.0" );
	if ( (ent = ini_register_entry("recording_play_customSpeed", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.recording_play_customSpeed, "2.0" );
	if ( (ent = ini_register_entry("key_recording_record", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_recording_record, "&0" );
	if ( (ent = ini_register_entry("key_recording_continueAfterFinish", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_recording_continueAfterFinish, "&0" );
	if ( (ent = ini_register_entry("key_recording_play", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_recording_play, "&0" );
	if ( (ent = ini_register_entry("key_recording_customSpeed", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_recording_customSpeed, "&0" );
	if ( (ent = ini_register_entry("key_recording_rev", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_recording_rev, "&0" );
	if ( (ent = ini_register_entry("key_recording_rev_customSpeed", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_recording_rev_customSpeed, "&0" );
#endif

	/* nitro mod */
	if ( (ent = ini_register_entry("key_nitro_mod", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_nitro_mod, "lalt" );
	if ( (ent = ini_register_entry("nitro_high", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.nitro_high, "1.3" );
	if ( (ent = ini_register_entry("nitro_low", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.nitro_low, "0.75" );
	if ( (ent = ini_register_entry("nitro_accel_time", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.nitro_accel_time, "0.5" );
	if ( (ent = ini_register_entry("nitro_decel_time", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.nitro_decel_time, "0.1" );

	/* brake */
	if ( (ent = ini_register_entry("key_brake_mod", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brake_mod, "oem_2" );
	if ( (ent = ini_register_entry("brake_mult", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.brake_mult, "1.0" );

	/* unflip */
	if ( (ent = ini_register_entry("key_unflip", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_unflip, "delete" );

	/* quick turn */
	if ( (ent = ini_register_entry("key_quick_turn_180", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_quick_turn_180, "backspace" );
	if ( (ent = ini_register_entry("key_quick_turn_left", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_quick_turn_left, "oem_4" );
	if ( (ent = ini_register_entry("key_quick_turn_right", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_quick_turn_right, "oem_6" );

	/* hop hop */
	if ( (ent = ini_register_entry("key_vehicle_hop", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_vehicle_hop, "oem_3" );
	if ( (ent = ini_register_entry("vehicle_hop_speed", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.vehicle_hop_speed, "0.2" );

	/* Spiders and Ninjas */
	if ( (ent = ini_register_entry("key_spiderwheels", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_spiderwheels, "np5" );
	/*
	if ( (ent = ini_register_entry("key_spiderfeet", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_spiderfeet, "np5" );
	if ( (ent = ini_register_entry("key_ninjaflipfront", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_ninjaflipfront, "r" );
	if ( (ent = ini_register_entry("key_ninjaflipback", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_ninjaflipback, "f" );
	*/

	/* OnFoot Fly */
	if ( (ent = ini_register_entry("key_fly_player", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_fly_player, "oem_period" );
	if ( (ent = ini_register_entry("key_fly_player_accelerate", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_fly_player_accelerate, "w" );
	if ( (ent = ini_register_entry("key_fly_player_decelerate", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_fly_player_decelerate, "s" );
	if ( (ent = ini_register_entry("key_fly_player_strafeLeft", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_fly_player_strafeLeft, "a" );
	if ( (ent = ini_register_entry("key_fly_player_strafeRight", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_fly_player_strafeRight, "d" );
	if ( (ent = ini_register_entry("key_fly_player_strafeUp", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_fly_player_strafeUp, "space" );
	if ( (ent = ini_register_entry("fly_player_speed", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.fly_player_speed, "1.0" );
	if ( (ent = ini_register_entry("fly_player_accel_multiplier", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.fly_player_accel_multiplier, "1.0" );
	if ( (ent = ini_register_entry("fly_player_decel_multiplier", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.fly_player_decel_multiplier, "1.0" );


	if ( (ent = ini_register_entry("handling_multiplier", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.handling_multiplier, "0.5" );

	/* misc protections */
	if ( (ent = ini_register_entry("key_protection", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_protection, "decimal" );
	if ( (ent = ini_register_entry("protection_spin_cap", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.protection_spin_cap, "0.25f" );
	if ( (ent = ini_register_entry("protection_speed_cap", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.protection_speed_cap, "1.3" );
	if ( (ent = ini_register_entry("protection_min_height", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.protection_min_height, "-100.0f" );

	/* stick */
	if ( (ent = ini_register_entry("key_stick", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick, "&0" );
	if ( (ent = ini_register_entry("key_stick_prev", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_prev, "&0" );
	if ( (ent = ini_register_entry("key_stick_next", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_next, "&0" );
	if ( (ent = ini_register_entry("key_stick_nearest", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_stick_nearest, "&0" );

	/* movement */
	if ( (ent = ini_register_entry("key_stick_forward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_forward, "w" );
	if ( (ent = ini_register_entry("key_stick_backward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_backward, "s" );
	if ( (ent = ini_register_entry("key_stick_left", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_left, "a" );
	if ( (ent = ini_register_entry("key_stick_right", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_right, "d" );
	if ( (ent = ini_register_entry("key_stick_up", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_up, "up" );
	if ( (ent = ini_register_entry("key_stick_down", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_down, "down" );
	if ( (ent = ini_register_entry("key_stick_in", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_in, "u" );
	if ( (ent = ini_register_entry("key_stick_out", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_stick_out, "j" );

	/* misc */
	if ( (ent = ini_register_entry("stick_min_height", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.stick_min_height, "-100.0" );
	if ( (ent = ini_register_entry("stick_vect", TYPE_VECTOR)) != NULL )
		ini_register_data( ent, &set.stick_vect, "0.0 0.0 1.0" );
	if ( (ent = ini_register_entry("stick_vect_dist", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.stick_vect_dist, "3.0" );
	if ( (ent = ini_register_entry("stick_accel_time", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.stick_accel_time, "1.0" );

	/* teleport */
	/*if ( (ent = ini_register_entry("teleport_slow", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.teleport_slow, "false" );
	if ( (ent = ini_register_entry("key_slowTeleport_stop", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_slowTeleport_stop, "&0" );
	*/
	if ( (ent = ini_register_entry("key_teleport_hist", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_teleport_hist, "p" );
	if ( (ent = ini_register_entry("key_teleport", TYPE_KEYCOMBO)) != NULL )
	{
		for ( i = 0; i < TELEPORT_MAX; i++ )
			ini_register_data( ent, &set.key_teleport[i], "&0" );
	}

	if ( (ent = ini_register_entry("key_teleport_set", TYPE_KEYCOMBO)) != NULL )
	{
		for ( i = 0; i < TELEPORT_MAX; i++ )
			ini_register_data( ent, &set.key_teleport_set[i], "&0" );
	}

	if ( (ent = ini_register_entry("teleport_pos", TYPE_COORD)) != NULL )
	{
		for ( i = 0; i < TELEPORT_MAX; i++ )
			ini_register_data( ent, set.teleport + i, "0.0 0.0 0.0 0" );
	}

	/* static teleport */
	if ( (ent = ini_register_entry("static_teleport_name", TYPE_STRING)) != NULL )
	{
		for ( i = 0; i < STATIC_TELEPORT_MAX; i++ )
			ini_register_data( ent, set.static_teleport_name + i, "" );
	}

	if ( (ent = ini_register_entry("static_teleport_pos", TYPE_COORD)) != NULL )
	{
		for ( i = 0; i < STATIC_TELEPORT_MAX; i++ )
			ini_register_data( ent, set.static_teleport + i, "0.0 0.0 0.0 0" );
	}

	/* checkpoint */
	if ( (ent = ini_register_entry("key_checkpoint_1", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_checkpoint_1, "np1" );
	if ( (ent = ini_register_entry("key_checkpoint_2", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_checkpoint_2, "np3" );
	if ( (ent = ini_register_entry("checkpoint_min_height", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.checkpoint_min_height, "-100.0" );

	/* self destruct */
	if ( (ent = ini_register_entry("key_self_destruct", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_self_destruct, "f3" );

	/* vehicle jumper */
	if ( (ent = ini_register_entry("key_vehicle_jumper", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_vehicle_jumper, "home" );
	if ( (ent = ini_register_entry("key_vehicle_occupied_jumper", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_vehicle_occupied_jumper, "end" );

	/* engine toggle */
	if ( (ent = ini_register_entry("key_engine", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_engine, "oem_1" );

	/* auto aim */
	if ( (ent = ini_register_entry("key_autoaim_toggle", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_autoaim_toggle, "z" );
	if ( (ent = ini_register_entry("use_gta_autoaim", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.use_gta_autoaim, "false" );

	/* map */
	if ( (ent = ini_register_entry("key_map", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_map, "m" );
	if ( (ent = ini_register_entry("key_map_show_vehicles", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_map_show_vehicles, "x" );

	/* weapons */
	if ( (ent = ini_register_entry("key_weapon", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_weapon, "f5" );
	if ( (ent = ini_register_entry("weapon_enabled", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.weapon_enabled, "false" );
	if ( (ent = ini_register_entry("restore_weapons_after_death", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.restore_weapons_after_death, "false" );

	if ( (ent = ini_register_entry("ammo_random", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.ammo_random, "false" );
	if ( (ent = ini_register_entry("ammo", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.ammo, "198" );
	if ( (ent = ini_register_entry("ammo_clip", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.ammo_clip, "99" );

	if ( (ent = ini_register_entry("weapon_slot", TYPE_WEAPON)) != NULL )
	{
		for ( i = 0; i < 13; i++ )
			ini_register_data( ent, set.weapon + i, "" );
	}

	/* money */
	if ( (ent = ini_register_entry("key_money", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_money, "f2" );
	if ( (ent = ini_register_entry("money_value", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.money_value, "69" );
	if ( (ent = ini_register_entry("money_enabled", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.money_enabled, "false" );
	if ( (ent = ini_register_entry("money_amount_max", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.money_amount_max, "250000" );
	if ( (ent = ini_register_entry("money_amount_rand_min", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.money_amount_rand_min, "1500" );
	if ( (ent = ini_register_entry("money_amount_rand_max", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.money_amount_rand_max, "5000" );
	if ( (ent = ini_register_entry("money_interval_rand_min", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.money_interval_rand_min, "10" );
	if ( (ent = ini_register_entry("money_interval_rand_max", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.money_interval_rand_max, "30" );

	/* menu */
	if ( (ent = ini_register_entry("key_menu", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_menu, "f11" );
	if ( (ent = ini_register_entry("key_menu_up", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_menu_up, "up" );
	if ( (ent = ini_register_entry("key_menu_right", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_menu_right, "right" );
	if ( (ent = ini_register_entry("key_menu_down", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_menu_down, "down" );
	if ( (ent = ini_register_entry("key_menu_left", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_menu_left, "left" );
	if ( (ent = ini_register_entry("key_menu_select", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_menu_select, "return" );
	if ( (ent = ini_register_entry("key_menu_dec", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_menu_dec, "subtract" );
	if ( (ent = ini_register_entry("key_menu_inc", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_menu_inc, "add" );
	if ( (ent = ini_register_entry("key_menu_mousecontrol", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_menu_mousecontrol, "lshift" );

	// custom GUI settings
	if ( (ent = ini_register_entry("hud_draw_bar", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_draw_bar, "true" );
	if ( (ent = ini_register_entry("render_text_shadows", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.render_text_shadows, "true" );
	if ( (ent = ini_register_entry("left_bottom_bars_enable", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.left_bottom_bars_enable, "true" );

	if ( (ent = ini_register_entry("gui", TYPE_GUI)) != NULL )
	{
		for ( i = 0; i < INI_GUI_MAX; i++ )
			ini_register_data( ent, set.guiset + i, "" );
	}

	// hud indicators
	if ( (ent = ini_register_entry("hud_indicator_inv", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_inv, "true" );
	if ( (ent = ini_register_entry("hud_indicator_weapon", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_weapon, "true" );
	if ( (ent = ini_register_entry("hud_indicator_money", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_money, "true" );
	if ( (ent = ini_register_entry("hud_indicator_freeze", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_freeze, "true" );

	if ( (ent = ini_register_entry("hud_indicator_inveh_airbrk", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_inveh_airbrk, "true" );
	if ( (ent = ini_register_entry("hud_indicator_inveh_stick", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_inveh_stick, "true" );
	if ( (ent = ini_register_entry("hud_indicator_inveh_brkdance", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_inveh_brkdance, "true" );
	if ( (ent = ini_register_entry("hud_indicator_inveh_spider", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_inveh_spider, "true" );
	if ( (ent = ini_register_entry("hud_indicator_inveh_fly", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_inveh_fly, "true" );

	if ( (ent = ini_register_entry("hud_indicator_onfoot_airbrk", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_onfoot_airbrk, "true" );
	if ( (ent = ini_register_entry("hud_indicator_onfoot_stick", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_onfoot_stick, "true" );
	if ( (ent = ini_register_entry("hud_indicator_onfoot_aim", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_onfoot_aim, "true" );
	if ( (ent = ini_register_entry("hud_indicator_onfoot_fly", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_onfoot_fly, "true" );

	if ( (ent = ini_register_entry("hud_indicator_pos", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_pos, "false" );
	if ( (ent = ini_register_entry("hud_fps_draw", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_fps_draw, "true" );

	/* misc junk */
	if ( (ent = ini_register_entry("trailer_support", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.trailer_support, "true" );
	if ( (ent = ini_register_entry("force_hour", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.force_hour, "-1" );
	if ( (ent = ini_register_entry("force_weather", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.force_weather, "-1" );

	/* d3d stuff */
	if ( (ent = ini_register_entry("d3dtext_hud", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.d3dtext_hud, "true" );

	// speedometer
	if ( (ent = ini_register_entry("speedometer_enable", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.speedometer_enable, "true" );
	if ( (ent = ini_register_entry("speedometer_old_enable", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.speedometer_old_enable, "false" );
	if ( (ent = ini_register_entry("speedometer_multiplier", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.speedometer_multiplier, "170.00" );
	if ( (ent = ini_register_entry("speedometer_speedo_png_filename", TYPE_STRING)) != NULL )
		ini_register_data( ent, set.speedometer_speedo_png_filename, "speedo.png" );
	if ( (ent = ini_register_entry("speedometer_needle_png_filename", TYPE_STRING)) != NULL )
		ini_register_data( ent, set.speedometer_needle_png_filename, "needle.png" );

	if ( (ent = ini_register_entry("chams_on", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.chams_on, "false" );
	if ( (ent = ini_register_entry("chams_wireframe", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.chams_wireframe, "true" );

	/* samp stuff */
	if ( (ent = ini_register_entry("d3dtext_chat", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.d3dtext_chat, "false" );
	if ( (ent = ini_register_entry("d3dtext_chat_lines", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.d3dtext_chat_lines, "20" );

	if ( (ent = ini_register_entry("d3dtext_kill", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.d3dtext_kill, "true" );
	if ( (ent = ini_register_entry("d3dtext_score", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.d3dtext_score, "true" );
	if ( (ent = ini_register_entry("d3dtext_labels", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.d3dtext_labels, "false" );
	if ( (ent = ini_register_entry("d3dtext_labels_maxDist", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.d3dtext_labels_maxDist, "100.0" );

	if ( (ent = ini_register_entry("anti_spam", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.anti_spam, "false" );
	if ( (ent = ini_register_entry("chatbox_logging", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.chatbox_logging, "false" );

	if ( (ent = ini_register_entry("nametags_show", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.nametags_show, "false" );
	if ( (ent = ini_register_entry("disable_line_of_sight", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.disable_line_of_sight, "false" );
	if ( (ent = ini_register_entry("line_of_sight_dist", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.line_of_sight_dist, "70.0" );
	if ( (ent = ini_register_entry("markers_show", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.markers_show, "false" );

	if ( (ent = ini_register_entry("samp_custom_sendrates_enable", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.samp_custom_sendrates_enable, "false" );
	if ( (ent = ini_register_entry("onfoot_sendrate", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.onfoot_sendrate, "40" );
	if ( (ent = ini_register_entry("incar_sendrate", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.incar_sendrate, "40" );
	if ( (ent = ini_register_entry("aim_sendrate", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.aim_sendrate, "40" );
	if ( (ent = ini_register_entry("headsync_sendrate", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.headsync_sendrate, "1000" );

	if ( (ent = ini_register_entry("clickwarp_enabled", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.clickwarp_enabled, "false" );
	if ( (ent = ini_register_entry("key_clickwarp_enable", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_clickwarp_enable, "mbutton" );
	if ( (ent = ini_register_entry("key_clickwarp_click", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_clickwarp_click, "lbutton" );

	if ( (ent = ini_register_entry("key_player_info_list", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_player_info_list, "i" );

	/* fast exit */
	if ( (ent = ini_register_entry("key_fast_exit", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_fast_exit, "n" );

	// anti car-jacking
	if ( (ent = ini_register_entry("anti_carjacking", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.anti_carjacking, "true" );

	/* brakedance keys */
	if ( (ent = ini_register_entry("key_brkd_toggle", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brkd_toggle, "p" );
	if ( (ent = ini_register_entry("key_brkd_forward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brkd_forward, "i" );
	if ( (ent = ini_register_entry("key_brkd_left", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brkd_left, "j" );
	if ( (ent = ini_register_entry("key_brkd_backward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brkd_backward, "k" );
	if ( (ent = ini_register_entry("key_brkd_right", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brkd_right, "l" );
	if ( (ent = ini_register_entry("key_brkd_rightward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brkd_rightward, "o" );
	if ( (ent = ini_register_entry("key_brkd_leftward", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_brkd_leftward, "u" );
	if ( (ent = ini_register_entry("brkdance_velocity", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.brkdance_velocity, "1.0" );

	if ( (ent = ini_register_entry("key_fly_vehicle", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_fly_vehicle, "oem_period" );
	if ( (ent = ini_register_entry("key_fly_vehicle_modeChange", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_fly_vehicle_modeChange, "oem_comma" );
	if ( (ent = ini_register_entry("fly_vehicle_heliMode", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.fly_vehicle_heliMode, "false" );

	if ( (ent = ini_register_entry("key_rejoin", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_rejoin, "b" );
	if ( (ent = ini_register_entry("rejoin_delay", TYPE_INT)) != NULL )
		ini_register_data( ent, &set.rejoin_delay, "5000" );

	if ( (ent = ini_register_entry("key_vehicles_freeze", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_vehicles_freeze, "pause" );

	if ( (ent = ini_register_entry("key_respawn", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_respawn, "7" );

	if ( (ent = ini_register_entry("key_render_player_tags", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_render_player_tags, "g" );
	if ( (ent = ini_register_entry("player_tags_dist", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.player_tags_dist, "225.0" );
	if ( (ent = ini_register_entry("key_render_vehicle_tags", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_render_vehicle_tags, "h" );
	if ( (ent = ini_register_entry("vehicle_tags_dist", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.vehicle_tags_dist, "100.0" );

	/* window mode */
	if ( (ent = ini_register_entry("window_mode", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.window_mode, "false" );
	if ( (ent = ini_register_entry("window_mode_titlebar", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.window_mode_titlebar, "true" );

	if ( (ent = ini_register_entry("flickering_problem", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.flickering_problem, "false" );

	// favorite server list
	if ( (ent = ini_register_entry("use_current_name", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.use_current_name, "false" );
	if ( (ent = ini_register_entry("server", TYPE_SERVER)) != NULL )
	{
		for ( i = 0; i < INI_SERVERS_MAX; i++ )
			ini_register_data( ent, set.server + i, "" );
	}

	if ( (ent = ini_register_entry("mod_commands_activated", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.mod_commands_activated, "false" );

	// keybinder
	if ( (ent = ini_register_entry("chat_secondary_key", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.chat_secondary_key, "oem_comma" );
	if ( (ent = ini_register_entry("chat", TYPE_CHATMSG)) != NULL )
	{
		for ( i = 0; i < INI_CHATMSGS_MAX; i++ )
			ini_register_data( ent, set.chat + i, "" );
	}

	/* patches */
	if ( (ent = ini_register_entry("patch", TYPE_PATCH)) != NULL )
	{
		for ( i = 0; i < INI_PATCHES_MAX; i++ )
			ini_register_data( ent, set.patch + i, "" );
	}

	if ( (ent = ini_register_entry("sampPatch", TYPE_SAMPPATCH)) != NULL )
	{
		for ( i = 0; i < INI_SAMPPATCHES_MAX; i++ )
			ini_register_data( ent, set.sampPatch + i, "" );
	}

	if ( (ent = ini_register_entry("netPatch", TYPE_NETPATCH)) != NULL )
	{
		for ( i = 0; i < INI_NETPATCHES_MAX; i++ )
			ini_register_data( ent, &set.netPatch[i], "" );
	}

	if ( (ent = ini_register_entry("key_panic", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_panic, "f12" );

	if ( (ent = ini_register_entry("custom_runanimation_enabled", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.custom_runanimation_enabled, "true" );
	// Due to crashes with some move animations, for example MOVE_PLAYER_F
	//  it is currently not supported to set the walk anim id by ini.
	//  (see move_animations[] in cheat_funcs.h shows which ones are crashing)
	set.custom_runanimation_id = 0;
	//if ( (ent = ini_register_entry("custom_runanimation_id", TYPE_INT)) != NULL )
	//	ini_register_data( ent, &set.custom_runanimation_id, "0" );

	// new ESP ish
	if ( (ent = ini_register_entry("esp_vehicles_defaulton", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.esp_vehicles_defaulton, "true" );

	if ( (ent = ini_register_entry("esp_players_defaulton", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.esp_players_defaulton, "true" );

	//
	if ( (ent = ini_register_entry("render_teleport_texts", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.render_teleport_texts, "true" );
	if ( (ent = ini_register_entry("render_pickup_texts", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.render_pickup_texts, "false" );
	if ( (ent = ini_register_entry("pickup_tags_dist", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.pickup_tags_dist, "100.0" );
	if ( (ent = ini_register_entry("render_object_texts", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.render_object_texts, "false" );
	if ( (ent = ini_register_entry("object_tags_dist", TYPE_FLOAT)) != NULL )
		ini_register_data( ent, &set.object_tags_dist, "100.0" );

	//
	//	if ( (ent = ini_register_entry("esp_players_airride", TYPE_BOOL)) != NULL )
	//		ini_register_data( ent, &set.esp_players_airride, "true" );

	// end new ESP ish

	if ( (ent = ini_register_entry("enable_clouds", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.enable_clouds, "true" );
	if ( (ent = ini_register_entry("enable_extra_godmode", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.enable_extra_godmode, "true" );
	if ( (ent = ini_register_entry("key_map_teleport", TYPE_KEY)) != NULL )
		ini_register_data( ent, &set.key_map_teleport, "rbutton" );
	if ( (ent = ini_register_entry("map_must_be_open", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.map_must_be_open, "true" );
	if ( (ent = ini_register_entry("key_quickwarp", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_quickwarp, "rbutton r" );
	if ( (ent = ini_register_entry("key_surf", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_surf, "k" );
	if ( (ent = ini_register_entry("key_freezerot", TYPE_KEYCOMBO)) != NULL )
		ini_register_data( ent, &set.key_freezerot, "&0" );
	if ( (ent = ini_register_entry("map_draw_lines", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.map_draw_lines, "true" );
	if ( (ent = ini_register_entry("hud_indicator_surf", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_surf, "true" );
	if ( (ent = ini_register_entry("hud_indicator_freezerot", TYPE_BOOL)) != NULL )
		ini_register_data( ent, &set.hud_indicator_freezerot, "true" );
}

int iGTAPatchesCount = 0, iSAMPPatchesCount = 0, iNetPatchesCount = 0, iServersCount = 0;
static void ini_entry_parse_type ( struct ini_entry *ent, int idx, const char *val )
{
	struct ini_entry_data	*ent_data = ent->data + idx;
	struct str_split		*split = str_split( val, "\t " );
	int						ok = 0, i;

	if ( split == NULL )
	{
		Log( "Out of memory" );
		return;
	}

	if ( split->argc <= 0 )
	{
		Log( "Missing value for %s", ini_entry_name(ent, idx) );
		return;
	}

	switch ( ent->type )
	{
	case TYPE_KEY:
		if ( split->argc != 1 )
			goto wrong_argc;

		if ( key_lookup(split->argv[0]) == -1 )
		{
			Log( "Invalid key name '%s' in %s", split->argv[0], ini_entry_name(ent, idx) );
			break;
		}

		* (int *)ent_data->data = key_lookup( split->argv[0] );

		ok = 1;
		break;

	case TYPE_BOOL:
		if ( split->argc != 1 )
			goto wrong_argc;
		if ( _stricmp(split->argv[0], "true") == 0 )
			* (int *)ent_data->data = 1;
		else if ( _stricmp(split->argv[0], "false") == 0 )
			* (int *)ent_data->data = 0;
		else
		{
			Log( "Invalid value '%s' in %s", split->argv[0], ini_entry_name(ent, idx) );
			break;
		}

		ok = 1;
		break;

	case TYPE_INT:
		if ( split->argc != 1 )
			goto wrong_argc;
		*(int *)ent_data->data = parse_int( split->argv[0] );
		ok = 1;
		break;

	case TYPE_FLOAT:
		if ( split->argc != 1 )
			goto wrong_argc;
		*(float *)ent_data->data = (float)atof( val );
		ok = 1;
		break;

	case TYPE_VECTOR:
		{
			float	v[3];

			if ( split->argc != 3 )
				goto wrong_argc;

			for ( i = 0; i < 3; i++ )
				v[i] = (float)atof( split->argv[i] );
			vect3_normalize( v, (float *)ent_data->data );

			/* some math functions require 4d vectors.. but we never use the 4th value
            so just set it to 0.0 */
			( (float *)ent_data->data )[3] = 0.0f;
			ok = 1;
		}
		break;

	case TYPE_COORD:
		{
			struct settings_coord	*coord = (struct settings_coord *)ent_data->data;
			float					v[3];

			if ( split->argc != 4 )
				goto wrong_argc;

			for ( i = 0; i < 3; i++ )
				v[i] = (float)atof( split->argv[i] );

			vect3_copy( v, coord->pos );
			coord->interior_id = parse_int( split->argv[3] );
			ok = 1;
		}
		break;

	case TYPE_STRING:
		if ( split->argc != 1 )
			goto wrong_argc;
		strlcpy( (char *)ent_data->data, split->argv[0], INI_STRLEN_MAX );
		ok = 1;
		break;

	case TYPE_WEAPON:
		{
			const struct weapon_entry	*weapon = gta_weapon_get_by_name( split->argv[0] );

			if ( split->argc != 1 )
				goto wrong_argc;

			if ( weapon == NULL || strlen(split->argv[0]) == 0 )
			{
				if ( strlen(split->argv[0]) > 0 )
					Log( "Unknown weapon '%s' in %s", split->argv[0], ini_entry_name(ent, idx) );
				break;
			}

			* (struct weapon_entry **)ent_data->data = (struct weapon_entry *)weapon;
			ok = 1;
		}
		break;

	case TYPE_PATCH:
		if ( split->argc <= 1 )
			break;
		if ( split->argc >= 7 && ((split->argc - 7) % 4) == 0 )
		{
			struct patch_set	*patch = (struct patch_set *)ent_data->data;

			if ( patch->name != NULL )
			{
				Log( "%s already assigned.", ini_entry_name(ent, idx) );
				break;
			}

			patch->name = _strdup( split->argv[0] );		/* XXX null.. */
			patch->ini_hotkey = key_lookup( split->argv[1] );
			patch->ini_auto = parse_int( split->argv[2] );

			iGTAPatchesCount++;

			for ( i = 3; i < split->argc; i += 4 )
			{
				void		*base_addr = ( strlen(split->argv[i + 0]) != 0 ) ? dll_baseptr_get( split->argv[i + 0] ) : NULL;
				uint32_t	offset = ( uint32_t ) parse_int( split->argv[i + 1] );
				const char	*orig_hex = split->argv[i + 2];
				const char	*repl_hex = split->argv[i + 3];
				int			chunk = ( i - 3 ) / 4;

				if ( repl_hex[0] == '!' )
				{
					patch->has_volatile = 1;
					patch->chunk[chunk].is_volatile = 1;
					repl_hex++;
				}

				if ( strlen(orig_hex) % 2 != 0 )
				{
					Log( "Invalid original data length in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( strlen(repl_hex) % 2 != 0 )
				{
					Log( "Invalid replacement data length in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( strlen(orig_hex) != 0 && strlen(orig_hex) != strlen(repl_hex) )
				{
					Log( "Original and replacement data must be of equal length in %s", ini_entry_name(ent, idx) );
					break;
				}

				patch->chunk[chunk].len = ( uint32_t ) strlen( repl_hex ) / 2;
				patch->chunk[chunk].ptr = (void *)( (uint8_t *)base_addr + offset );
				if ( (patch->chunk[chunk].data_rep = hex_to_bin(repl_hex)) == NULL )
				{
					free( (void *)patch->name );
					patch->name = NULL;

					/* XXX free more stuff */
					Log( "Invalid hex data for replacement data in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( strlen(orig_hex) > 0 && (patch->chunk[chunk].data_cmp = hex_to_bin(orig_hex)) == NULL )
				{
					free( (void *)patch->name );
					patch->name = NULL;
					free( patch->chunk[chunk].data_rep );
					patch->chunk[chunk].data_rep = NULL;

					/* XXX free more stuff */
					Log( "Invalid hex data for original data in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( chunk == PATCHER_CHUNKS_MAX - 1 )
					break;
			}

			ok = 1;
		}
		else
		{
			goto wrong_argc;
		}
		break;

	case TYPE_SAMPPATCH:
		if ( split->argc <= 1 )
			break;

		if ( split->argc >= 6 && ((split->argc - 6) % 3) == 0 )
		{
			struct patch_set	*sampPatch = (struct patch_set *)ent_data->data;

			if ( sampPatch->name != NULL )
			{
				Log( "%s already assigned.", ini_entry_name(ent, idx) );
				break;
			}

			sampPatch->name = _strdup( split->argv[0] );	/* XXX null.. */
			sampPatch->ini_hotkey = key_lookup( split->argv[1] );
			sampPatch->ini_auto = parse_int( split->argv[2] );

			iSAMPPatchesCount++;

			for ( i = 3; i < split->argc; i += 3 )
			{
				uint32_t	offset = ( uint32_t ) parse_int( split->argv[i + 0] );
				const char	*orig_hex = split->argv[i + 1];
				const char	*repl_hex = split->argv[i + 2];
				int			chunk = ( i - 2 ) / 3;

				if ( repl_hex[0] == '!' )
				{
					sampPatch->has_volatile = 1;
					sampPatch->chunk[chunk].is_volatile = 1;
					repl_hex++;
				}

				if ( strlen(orig_hex) % 2 != 0 )
				{
					Log( "Invalid original data length in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( strlen(repl_hex) % 2 != 0 )
				{
					Log( "Invalid replacement data length in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( strlen(orig_hex) != 0 && strlen(orig_hex) != strlen(repl_hex) )
				{
					Log( "Original and replacement data must be of equal length in %s", ini_entry_name(ent, idx) );
					break;
				}

				sampPatch->chunk[chunk].len = ( uint32_t ) strlen( repl_hex ) / 2;
				sampPatch->chunk[chunk].ptr = (void *)( getSampAddress() + offset );
				if ( (sampPatch->chunk[chunk].data_rep = hex_to_bin(repl_hex)) == NULL )
				{
					free( (void *)sampPatch->name );
					sampPatch->name = NULL;

					/* XXX free more stuff */
					Log( "Invalid hex data for replacement data in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( strlen(orig_hex) > 0 && (sampPatch->chunk[chunk].data_cmp = hex_to_bin(orig_hex)) == NULL )
				{
					free( (void *)sampPatch->name );
					sampPatch->name = NULL;
					free( sampPatch->chunk[chunk].data_rep );
					sampPatch->chunk[chunk].data_rep = NULL;

					/* XXX free more stuff */
					Log( "Invalid hex data for original data in %s", ini_entry_name(ent, idx) );
					break;
				}

				if ( chunk == PATCHER_CHUNKS_MAX - 1 )
					break;
			}

			ok = 1;
		}
		else
		{
			goto wrong_argc;
		}
		break;

	case TYPE_DWORD:
		if ( split->argc != 1 )
			goto wrong_argc;
		*(DWORD *)ent_data->data = parse_int( split->argv[0] );
		ok = 1;
		break;

	case TYPE_SERVER:
		if ( split->argc <= 1 )
			break;

		if ( split->argc == 5 )
		{
			struct fav_server	*server = (struct fav_server *)ent_data->data;

			server->nickname = _strdup( split->argv[0] );
			server->server_name = _strdup( split->argv[1] );
			server->ip = _strdup( split->argv[2] );
			server->port = ( uint16_t ) parse_int( split->argv[3] );
			server->password = _strdup( split->argv[4] );

			iServersCount++;
		}
		else
		{
			goto wrong_argc;
		}

		ok = 1;
		break;

	case TYPE_CHATMSG:
		if ( split->argc <= 1 )
			break;

		if ( split->argc == 3 )
		{
			struct chat_msg *chat_msg = (struct chat_msg *)ent_data->data;

			chat_msg->key = key_lookup( split->argv[0] );
			chat_msg->msg = _strdup( split->argv[1] );
			chat_msg->spam = parse_int( split->argv[2] );
		}
		else
		{
			goto wrong_argc;
		}

		ok = 1;
		break;

	case TYPE_GUI:
		if ( split->argc <= 1 )
			break;

		if ( split->argc == 5 )
		{
			struct gui	*gui_set = (struct gui *)ent_data->data;

			gui_set->element = _strdup( split->argv[0] );
			gui_set->alpha = parse_int( split->argv[1] );
			gui_set->red = parse_int( split->argv[2] );
			gui_set->green = parse_int( split->argv[3] );
			gui_set->blue = parse_int( split->argv[4] );
		}
		else
		{
			goto wrong_argc;
		}

		ok = 1;
		break;

	case TYPE_KEYCOMBO:
	{
		if (split->argc < 1 || split->argc > INI_KEYCOMBO_MAX)
			goto wrong_argc;

		keycombo *kc = (keycombo *)ent_data->data;
		kc->count = 0;
		for (i = 0; i < split->argc; ++i)
		{
			int key = key_lookup(split->argv[i]);
			if (key == -1)
			{
				Log("Invalid key name '%s' in %s", split->argv[i], ini_entry_name(ent, idx));
				break;
			}
			kc->key[i] = key;
			++kc->count;
		}
		ok = 1;
		break;
	}

	case TYPE_NETPATCH:
	{
		if ( split->argc <= 1 )
			break;

		if ( split->argc != 5 )
			goto wrong_argc;

		stNetPatch *netPatch = (stNetPatch *)ent_data->data;

		netPatch->name = _strdup( split->argv[0] );
		if (_stricmp(split->argv[1], "incoming RPC") == 0)
			netPatch->type = INCOMING_RPC;
		else if (_stricmp(split->argv[1], "outcoming RPC") == 0)
			netPatch->type = OUTCOMING_RPC;
		else if (_stricmp(split->argv[1], "incoming packet") == 0)
			netPatch->type = INCOMING_PACKET;
		else if (_stricmp(split->argv[1], "outcoming packet") == 0)
			netPatch->type = OUTCOMING_PACKET;
		else
		{
			Log("Invalid type '%s' in %s", split->argv[1], ini_entry_name(ent, idx));
			break;
		}
		int id = parse_int( split->argv[2] );
		if (id >= RAKNET_MAX_PACKET)
		{
			Log("Invalid packet id '%d' in %s", id, ini_entry_name(ent, idx));
			break;
		}
		netPatch->id = id;
		netPatch->hotkey = key_lookup( split->argv[3] );
		netPatch->enabled = parse_int( split->argv[4] ) != 0;
		set.netPatchAssoc[netPatch->id][netPatch->type] = netPatch; // for higher performance
		++iNetPatchesCount;

		ok = 1;
		break;
	}

	default:
		Log( "BUG: %s has invalid data type", ini_entry_name(ent, idx) );
	}

	str_split_free( split );

	if ( ok )
		ent_data->count++;

	return;

wrong_argc: ;
	Log( "Wrong number of arguments (%d) for %s", split->argc, ini_entry_name(ent, idx) );
	str_split_free( split );
}

static void ini_entry_parse ( struct ini_entry *ent, int idx, const char *val )
{
	if ( ent->size <= 0 )
	{
		Log( "BUG: %s has no data entries", ini_entry_name(ent, idx) );
		return;
	}

	if ( ent->size > 1 )
	{
		/* array */
		if ( idx == -1 )
		{
			/* foo[], find first unused data entry */
			for ( idx = 0; idx < ent->size; idx++ )
			{
				if ( ent->data[idx].count == 0 )
					break;
			}
		}

		if ( idx >= ent->size )
			Log( "Array index for %s out of bounds", ini_entry_name(ent, idx) );
		else
		{
			ini_entry_parse_type( ent, idx, val );
		}
	}
	else
	{
		if ( idx != -1 )
			Log( "Setting %s is not an array", ini_entry_name(ent, idx) );
		else
			ini_entry_parse_type( ent, 0, val );
	}
}

void ini_load ( void )
{
	static int	first_load = 1;
	char		filename[512];
	char		line[512], line_copy[4096], *opt, *str, *val;
	FILE		*fd;
	int			len, i, j, match;
	int			array_idx;

	/* init & load defaults */
	if ( first_load )
	{
		memset( &set, 0, sizeof(set) );
		ini_init();

		/* read defaults */
		for ( i = 0; i < ini_entry_count; i++ )
		{
			for ( j = 0; j < ini_entry[i].size; j++ )
			{
				ini_entry_parse( &ini_entry[i], -1, ini_entry[i].data[j].def );
			}
		}
	}

	for ( i = 0; i < ini_entry_count; i++ )
	{
		for ( j = 0; j < ini_entry[i].size; j++ )
		{
			ini_entry[i].data[j].count = 0;
		}
	}

	snprintf( filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, INI_FILE );

	//Log("Loading %s...", filename);
	fd = fopen( filename, "r" );
	if ( fd == NULL )
	{
		Log( "Could not open %s, using default (or previous) settings.", filename );
		return;
	}

	strcpy( line_copy, "" );
	while ( (fgets(line, sizeof(line), fd) != NULL) )
	{
		len = (int)strlen( line );

		/* strip trailing newlines, spaces, and tabs */
		while ( len > 0 && strchr("\t\n\r ", line[len - 1]) )
			line[--len] = 0;

		/* skip comments and empty lines */
		if ( line[0] == '#' || line[0] == ';' || line[0] == 0 )
			continue;

		if ( len > 0 && line[len - 1] == '\\' )
		{
			line[len - 1] = ' ';
			strlcat( line_copy, line, sizeof(line_copy) );
			continue;
		}

		strlcat( line_copy, line, sizeof(line_copy) );

		str = line_copy;
		array_idx = -1;

		/* strip leading spaces */
		LTRIM( str );

		/* extract setting name
         foo[123] = bar
         ^^^ */
		while
		(
			(*str >= '0' && *str <= '9')
		||	(*str >= 'A' && *str <= 'Z')
		||	(*str >= 'a' && *str <= 'z')
		||	*str == '_'
		||	*str == '-'
		)
		{
			str++;
		}

		/* parse array index
         foo[123] = bar
            ^^^^ */
		if ( *str == '[' )
		{
			*str++ = 0;
			LTRIM( str );
			if ( *str != ']' )	/* foo[] uses the next free array index; leave array_idx set to -1 */
			{
				array_idx = parse_int( str );
				if ( array_idx < 0 )
				{
					Log( "Parse error: %s (Negative array index)", line );
					goto parse_continue;
				}

				if ( (str = strchr(str, ']')) == NULL )
				{
					Log( "Parse error: %s (missing ']')", line );
					goto parse_continue;
				}
			}

			/* we're at the ']' here */
			str++;
		}

		/* find start of value
         foo[123] = bar
                 ^^ */
		if ( *str == '=' )
		{
			*str = 0;
		}
		else
		{
			*str++ = 0;
			LTRIM( str );
			if ( *str != '=' )
			{
				Log( "Parse error: %s (expected '=')", line );
				goto parse_continue;
			}
		}

		/* we're at the '=' here */
		opt = line_copy;
		val = str + 1;

		match = 0;

		for ( i = 0; i < ini_entry_count; i++ )
		{
			struct ini_entry	*ent = &ini_entry[i];

			if ( strcmp(opt, ent->name) != 0 )
				continue;

			/* don't reload patches (cause this would fuck things up...) */
			if (!first_load && (ent->type == TYPE_PATCH || ent->type == TYPE_SAMPPATCH || ent->type == TYPE_NETPATCH))
			{
				match = 1;
				break;
			}

			ini_entry_parse( ent, array_idx, val );
			match = 1;

			break;
		}

		if ( !match )
			Log( "Unknown setting '%s'", opt );

parse_continue: ;
		strcpy( line_copy, "" );
	}

	fclose( fd );

	for ( i = 0; i < ini_entry_count; i++ )
	{
		struct ini_entry	*ent = &ini_entry[i];
		int					isset = 0;

		for ( j = 0; j < ent->size; j++ )
		{
			if ( ent->data[j].count == 0 )
				continue;

			if ( ent->data[j].count > 1 )
			{
				Log( "Warning: setting '%s' was set multiple times in the .ini file", ini_entry_name(ent, j) );
			}

			isset = 1;
		}

		if ( !isset )
			Log( "Warning: setting '%s%s' was not present in the .ini file", ent->name, (ent->size > 1) ? "[]" : "" );
	}

	//Log("Done.");
	first_load = 0;

	// refreshes any cheat_state stuff set from the INI
	ini_load_setSettings();
}

void ini_load_setSettings ( void )
{
	if ( cheat_state != NULL )
	{
		// updatable fly settings
		if ( set.fly_player_speed < 0.1f )
			set.fly_player_speed = 0.1f;

		// esp states
		cheat_state->render_player_tags = set.esp_players_defaulton;
		cheat_state->render_vehicle_tags = set.esp_vehicles_defaulton;
		cheat_state->_generic.teletext = set.render_teleport_texts;
		cheat_state->_generic.pickuptexts = set.render_pickup_texts;
		cheat_state->_generic.objecttexts = set.render_object_texts;
	}
}

void ini_reload ( void )
{
	ini_load();
	menu_free_all();
	menu_maybe_init();
	cheat_state_text( "Settings reloaded." );
}
