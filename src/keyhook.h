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

/*
   Some voodoo here.

   Whenever a button is pressed or released, we increment count by 1.

   After every cheat_hook() call, and if count is > 0, we decrement
   count by one, and invert the flip bit.

   This gives us a very simple key queue, which can be used to
   emulate the old KEY_DOWN/UP/PRESSED/RELEASED macros.
*/
struct key_state
{
	uint8_t count : 5;
	uint8_t flip : 1;
	uint8_t pstate : 1;		/* previous state (1 down, 0 up) */
	uint8_t consume : 1;	/* KEY_CONSUME(vkey) */
};

#define KEY_DOWN			keyhook_key_down
#define KEY_UP				keyhook_key_up
#define KEY_PRESSED			keyhook_key_pressed
#define KEY_RELEASED		keyhook_key_released
#define KEY_CONSUME			keyhook_key_consume

#define KEYCOMBO_DOWN		keyhook_keycombo_down
#define KEYCOMBO_UP			keyhook_keycombo_up
#define KEYCOMBO_PRESSED	keyhook_keycombo_pressed
#define KEYCOMBO_RELEASED	keyhook_keycombo_released

void					keyhook_maybe_install ( HWND wnd );
void					keyhook_uninstall ( void );

void					keyhook_run ( void );

int						keyhook_key_down ( int v );
int						keyhook_key_up ( int v );
int						keyhook_key_pressed ( int v );
int						keyhook_key_released ( int v );
void					keyhook_key_consume ( int v );
void					keyhook_clear_states ( void );

bool					keyhook_keycombo_down(const keycombo &comb);
bool					keyhook_keycombo_up(const keycombo &comb);
bool					keyhook_keycombo_pressed(const keycombo &comb);
bool					keyhook_keycombo_released(const keycombo &comb);

extern struct key_state key_table[256];
extern int				key_being_pressed;
