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

#pragma once

#ifdef __CHEAT_VEHRECORDING_H__
#pragma comment (lib, "sqlite3/sqlite3.lib")

enum eRecordingState
{
	RECORDING_OFF = 0,
	RECORDING_RECORD,

	// All play states
	RECORDING_PLAY,
	RECORDING_PLAY_CUSTOMSPEED,

	// All reverse play states [rev states need to be after other play states]
	RECORDING_PLAY_REV,
	RECORDING_PLAY_REV_CUSTOMSPEED,
};

// generic sqlite functions
int sqliteDB_checkTableExists ( sqlite3 *db, char *tableName );
int sqliteDB_getNumTables ( sqlite3 *db, bool filter_sqlite_tables );
bool sqliteDB_dropTable ( sqlite3 *db, char *tableName );
// end of generic sqlite functions

// recording functions
int rec_sqlite_getNumTables ();
char *rec_sqlite_getTableName( int RouteNum );
bool rec_sqlite_loadTable ( char *tableName );
bool rec_sqlite_dropTable ( char *tableName );
bool rec_sqlite_writeTable ();
bool rec_sqlite_optimizeDatabase ();
void cheat_handle_vehicle_recording ( struct vehicle_info *info, float time_diff );
#endif