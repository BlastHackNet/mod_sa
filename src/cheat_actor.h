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
void				cheat_actor_teleport ( struct actor_info *info, const float pos[3], int interior_id );
void				cheat_handle_actor_autoaim ( struct actor_info *info, double time_diff );
void				cheat_handle_actor_air_brake ( struct actor_info *info, double time_diff );
//void				cheat_handle_SpiderFeet ( struct actor_info *ainfo, double time_diff );
void				cheat_handle_actor_fly ( struct actor_info *ainfo, double time_diff );
void				cheat_handle_actor_surf(struct actor_info *ainfo);

CEntitySAInterface	*cheat_actor_GetCEntitySAInterface ( actor_info *ainfo );
