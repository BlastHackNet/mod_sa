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
#define INI_STRLEN_MAX		64	/* including null */
#define INI_PATCHES_MAX		96
#define INI_SAMPPATCHES_MAX 128 /*64*/
#define INI_SERVERS_MAX		64
#define INI_CHATMSGS_MAX	64
#define INI_GUI_MAX			8

struct settings_coord
{
	float	pos[3];
	int		interior_id;
	int		iMenuID;
};

struct fav_server
{
	const char	*nickname;
	const char	*server_name;
	const char	*ip;
	uint16_t	port;
	char		*password;
};

struct chat_msg
{
	int			key;
	const char	*msg;
	int			spam;
};

struct gui
{
	const char	*element;
	int			alpha;
	int			red;
	int			green;
	int			blue;
};

// set structure
// DO NOT use bool types in here, it screws up the alignment even with pragma pack directive
struct settings
{
	int						run_mode;
	int						wine_compatibility;
	int						i_have_edited_the_ini_file;
	int						basic_mode;
	int						fps_limit;

	int						key_hp_cheat;
	float					hp_minimum;
	float					hp_regen;
	float					hp_regen_onfoot;
	int						hp_actor_explosion_inv;
	int						hp_actor_fall_inv;
	int						hp_actor_fire_inv;
	int						hp_keep_vehicleHPsane;
	int						hp_disable_inv_sp_enemies;

	int						secondary_key;

	int						mod_commands_activated;

	int						key_anti_freeze;

	int						hp_indestructible;
	int						hp_tire_support;

	int						key_autoaim_toggle;
	int						use_gta_autoaim;

	int						key_map;
	int						key_map_show_vehicles;

	int						key_air_brake_mod;
	int						key_air_brake_foot_mod;
	int						key_air_brake_mod2;
	int						key_air_brake_forward;
	int						key_air_brake_backward;
	int						key_air_brake_left;
	int						key_air_brake_right;
	int						key_air_brake_up;
	int						key_air_brake_down;
	int						key_air_brake_rot_yaw1;
	int						key_air_brake_rot_yaw2;
	int						key_air_brake_rot_roll1;
	int						key_air_brake_rot_roll2;
	int						key_air_brake_rot_pitch1;
	int						key_air_brake_rot_pitch2;
	int						air_brake_toggle;
	int						air_brake_behaviour;
	float					air_brake_speed;
	float					air_brake_rot_speed;
	float					air_brake_accel_time;

	int						key_warp_mod;
	float					warp_speed;
	int						warp_use_speed;

	int						key_blinking_car_lights;
	int						enable_car_lights_at_day_time;

	int						key_keep_trailer;
	int						key_disable_Wall_Collisions;
	int						wall_collisions_disableObjects;
	int						wall_collisions_disableRender;

	int						key_repair_car;

	int						key_nitro;

#ifdef __CHEAT_VEHRECORDING_H__
	int						recording_activated;
	float					recording_maxDistToEntryPoint;
	float					recording_play_customSpeed;
	int						key_recording_record;
	int						key_recording_continueAfterFinish;
	int						key_recording_play;
	int						key_recording_customSpeed;
	int						key_recording_rev;
	int						key_recording_rev_customSpeed;
#endif

	//int					teleport_slow;
	//int					key_slowTeleport_stop;
	int						key_teleport_hist;
	int						key_teleport[TELEPORT_MAX];
	int						key_teleport_set[TELEPORT_MAX];
	struct settings_coord	teleport[TELEPORT_MAX];

	char					static_teleport_name[STATIC_TELEPORT_MAX][INI_STRLEN_MAX];
	struct settings_coord	static_teleport[STATIC_TELEPORT_MAX];

	int						hb_color;

	int						key_unflip;
	int						key_quick_turn_180;
	int						key_quick_turn_left;
	int						key_quick_turn_right;

	int						key_stick;
	int						key_stick_prev;
	int						key_stick_next;
	int						key_stick_nearest;
	int						key_stick_forward;
	int						key_stick_backward;
	int						key_stick_left;
	int						key_stick_right;
	int						key_stick_up;
	int						key_stick_down;
	int						key_stick_in;
	int						key_stick_out;
	float					stick_min_height;
	float					stick_vect[4];	/* must be 4d! */
	float					stick_vect_dist;
	float					stick_accel_time;

	int						key_checkpoint_1;
	int						key_checkpoint_2;
	float					checkpoint_min_height;

	int						key_nitro_mod;
	float					nitro_high;
	float					nitro_low;
	float					nitro_accel_time;
	float					nitro_decel_time;

	int						key_brake_mod;
	float					brake_mult;

	int						key_protection;
	float					protection_spin_cap;
	float					protection_speed_cap;
	float					protection_min_height;

	int						key_self_destruct;
	int						key_engine;
	int						key_vehicle_jumper;
	int						key_vehicle_occupied_jumper;

	int						key_weapon;
	int						weapon_enabled;
	int						restore_weapons_after_death;

	int						ammo_random;
	int						ammo;
	int						ammo_clip;

	struct weapon_entry		*weapon[13];

	int						key_money;
	int						money_value;
	int						money_enabled;
	int						money_amount_max;
	int						money_amount_rand_min;
	int						money_amount_rand_max;
	int						money_interval_rand_min;
	int						money_interval_rand_max;

	int						key_menu;
	int						key_menu_up;
	int						key_menu_right;
	int						key_menu_down;
	int						key_menu_left;
	int						key_menu_select;
	int						key_menu_dec;
	int						key_menu_inc;

	int						hud_draw_bar;
	int						render_text_shadows;
	int						left_bottom_bars_enable;
	struct gui				guiset[INI_GUI_MAX];

	int						hud_indicator_inv;
	int						hud_indicator_weapon;
	int						hud_indicator_money;
	int						hud_indicator_freeze;

	int						hud_indicator_inveh_airbrk;
	int						hud_indicator_inveh_stick;
	int						hud_indicator_inveh_brkdance;
	int						hud_indicator_inveh_spider;
	int						hud_indicator_inveh_fly;

	int						hud_indicator_onfoot_airbrk;
	int						hud_indicator_onfoot_stick;
	int						hud_indicator_onfoot_aim;
	int						hud_indicator_onfoot_fly;

	int						hud_indicator_pos;
	int						hud_fps_draw;

	int						trailer_support;
	int						force_hour;
	int						force_weather;

	int						d3dtext_hud;

	int						speedometer_enable;
	int						speedometer_old_enable;
	float					speedometer_multiplier;
	char					speedometer_speedo_png_filename[32];
	char					speedometer_needle_png_filename[32];

	int						logo_enable;

	int						chams_on;
	int						chams_wireframe;

	int						d3dtext_chat;
	int						d3dtext_chat_lines;

	int						d3dtext_kill;
	int						d3dtext_score;
	int						d3dtext_labels;
	float					d3dtext_labels_maxDist;

	int						anti_spam;
	int						chatbox_logging;

	int						nametags_show;
	int						disable_line_of_sight;
	float					line_of_sight_dist;
	int						markers_show;

	int						samp_custom_sendrates_enable;
	int						onfoot_sendrate;
	int						incar_sendrate;
	int						aim_sendrate;
	int						headsync_sendrate;

	int						clickwarp_enabled;
	int						key_clickwarp_enable;
	int						key_clickwarp_click;

	int						key_player_info_list;
	int						key_fast_exit;

	int						anti_carjacking;

	// ignored because of the function being removed
	int						window_mode;
	int						window_mode_titlebar;

	int						flickering_problem;

	int						walk_under_water;
	int						vehicles_unlock;
	int						vehicles_warp_invert;
	int						key_vehicles_freeze;

	int						key_respawn;

	int						key_render_player_tags;
	float					player_tags_dist;
	int						key_render_vehicle_tags;
	float					vehicle_tags_dist;

	int						key_vehicle_hop;
	float					vehicle_hop_speed;

	int						key_spiderwheels;
	/*
	int						key_spiderfeet;
	int						key_ninjaflipfront;
	int						key_ninjaflipback;
	*/

	int						key_fly_player;
	int						key_fly_player_accelerate;
	int						key_fly_player_decelerate;
	int						key_fly_player_strafeLeft;
	int						key_fly_player_strafeRight;
	int						key_fly_player_strafeUp;
	float					fly_player_speed;
	float					fly_player_accel_multiplier;
	float					fly_player_decel_multiplier;

	float					handling_multiplier;

	int						use_current_name;
	struct fav_server		server[INI_SERVERS_MAX];

	int						chat_secondary_key;
	struct chat_msg			chat[INI_CHATMSGS_MAX];

	struct patch_set		patch[INI_PATCHES_MAX];
	struct patch_set		sampPatch[INI_SAMPPATCHES_MAX];

	int						key_panic;

	int						custom_runanimation_enabled;
	int						custom_runanimation_id;

	int						key_brkd_toggle;
	int						key_brkd_forward;
	int						key_brkd_left;
	int						key_brkd_backward;
	int						key_brkd_right;
	int						key_brkd_rightward;
	int						key_brkd_leftward;
	float					brkdance_velocity;

	int						key_fly_vehicle;
	int						key_fly_vehicle_modeChange;
	int						fly_vehicle_heliMode;

	int						key_rejoin;
	int						rejoin_delay;

	int						send_spec_data;

	// new ESP ish
	int						esp_vehicles_defaulton;
	int						esp_players_defaulton;
	int						render_teleport_texts;
	int						render_pickup_texts;
	float					pickup_tags_dist;
	int						render_object_texts;
	float					object_tags_dist;
	int						enable_clouds;
	int						enable_extra_godmode;

	///////////////////////////////////////////////
	// DO NOT PUT ANYTHING AFTER THIS, DUMB FUCK //
	int						__DUMMYFUCKER_DONOTDELETE;
};


///////////////////////////////////////////////
extern struct settings	set;

void					ini_load ( void );
void					ini_reload ( void );
void					ini_free ( void );
void					ini_load_setSettings( void );
