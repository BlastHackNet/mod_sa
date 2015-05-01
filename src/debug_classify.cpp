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

struct classify_table
{
	int			offset;
	int			len;
	const char	*descr;
};

struct classify_pool
{
	void						*pool_ptr;
	int							item_size;
	const char					*name;
	const struct classify_table *table;
};

static const struct classify_table	classify_table_actor[] =
{
	0,
	4,
	"Virtual method table",
	4,
	12,
	"Unknown coordinates",
	20,
	4,
	"Pointer to transformation matrix",
	30,
	2,
	"Model ID",
	44,
	2,
	"Timer",
	47,
	1,
	"Interior ID",
	66,
	1,
	"Flags",
	68,
	12,
	"Speed vector",
	80,
	12,
	"Spin vector",
	92,
	12,
	"Speed vector for collisions",
	104,
	12,
	"Spin vector for collisions",
	216,
	4,
	"Collision Timer (?)",
	220,
	4,
	"Pointer to current collision object",
	236,
	12,
	"Last Collision Coords",
	356,
	12,
	"Step vector (last foot step)",
	368,
	12,
	"Step vector (before last foot step",
	1148,
	4,
	"Pointer to ped intelligence struct",
	1244,
	4,
	"runspeed",
	1300,
	4,
	"X angle",
	1328,
	4,
	"State",
	1332,
	4,
	"Movement state",
	1344,
	4,
	"Hitpoints",
	1348,
	4,
	"Max hitpoints (?)",
	1368,
	4,
	"Z angle",
	1372,
	4,
	"Z angle (again)",
	1384,
	4,
	"Pointer to vehicle (if on top)",
	1412,
	4,
	"Pointer to building (on contact)",
	1420,
	4,
	"Pointer to vehicle (if driving)",
	1440,
	364,
	"Weapon data",
	1816,
	1,
	"Active weapon slot",
	1856,
	4,
	"Active weapon model",
	1888,
	4,
	"Last hit by weapon type",
	1892,
	4,
	"Pointer to last hit by actor",
	-1,
	-1,
	NULL
};

static const struct classify_table	classify_table_vehicle[] =
{
	0,
	4,
	"Virtual method table",
	4,
	12,
	"Unknown coordinates",
	20,
	4,
	"Pointer to transformation matrix",
	34,
	2,
	"Model ID",
	44,
	2,
	"Timer",
	47,
	1,
	"Interior ID",
	66,
	1,
	"Flags",
	68,
	12,
	"Speed vector",
	80,
	12,
	"Spin vector",
	92,
	12,
	"Speed vector for collisions",
	104,
	12,
	"Spin vector for collisions",
	140,
	4,
	"Mass",
	144,
	4,
	"Turn mass",
	148,
	4,
	"Grip divider",
	152,
	4,
	"Mass to grip multiplier",
	152,
	4,
	"Mass to grip multiplier",
	160,
	4,
	"Grip level (normalized)",
	164,
	12,
	"Center of mass vector",
	188,
	4,
	"Last TOUCHED object",
	192,
	4,
	"Last collided object",
	216,
	4,
	"Collision timer (?)",
	220,
	4,
	"Pointer to current collision object",
	224,
	12,
	"Collision Something",
	236,
	12,
	"Last collision coordinates",
	304,
	3,
	"Light reflection related (?)",
	477,
	1,
	"In vehicle",
	502,
	1,
	"Car horn",
	503,
	1,
	"Siren",
	504,
	1,
	"Fast siren",
	528,
	4,
	"Engine sound level",
	534,
	6,
	"Engine sound IDs (?)",
	1064,
	1,
	"Engine State",
	1076,
	4,
	"Car colors",
	1080,
	4 * 8,
	"Modding data",
	1112,
	4,
	"Wheel size",
	1116,
	4,
	"Alarm timer",
	1120,
	4,
	"Pointer to driver actor/ped",
	1124,
	4,
	"Pointer to passenger actor/ped",
	1162,
	1,
	"Nitro count",
	1172,
	4 * 2,
	"Steer angle",
	1180,
	4,
	"Gas pedal",
	1184,
	4,
	"Break pedal",
	1216,
	4,
	"Hitpoints",
	1220,
	4,
	"Pointer to pulling truck",
	1272,
	4,
	"Door status",
	1300,
	1,
	"Car horn (writeable)",
	1420,
	4,
	"Steering",
	1424,
	4,
	"Vehicle class",
	1444,
	1,
	"Boat sound level",
	1445,
	4,
	"Car tire status",
	1449,
	6,
	"Door status",
	1456,
	1,
	"Light status",
	1532,
	44 * 1,
	"Detachables (bike, car, boat)",
	1628,
	2,
	"Bike tire status",
	1632,
	44 * 4,
	"Detachables (bike, boat)",
	1828,
	44 * 4,
	"Detachables (car, heli, plane)",
	2020,
	4 * 4,
	"Suspension height",
	2404,
	4,
	"Gas pedal",
	-1,
	-1,
	NULL
};

static const struct classify_table	classify_table_building[] =
{
	0,
	4,
	"Virtual method table",
	4,
	12,
	"Unknown coordinates",
	20,
	4,
	"Pointer to transformation matrix",
	44,
	2,
	"Timer",
	47,
	1,
	"Interior ID",
	-1,
	-1,
	NULL
};

static const struct classify_table	classify_table_object[] =
{
	0,
	4,
	"Virtual method table",
	20,
	4,
	"Pointer to transformation matrix for Model",
	24,
	4,
	"Pointer to transformation matrix?",
	34,
	2,
	"Model ID",
	36,
	4,
	"Collision related",
	44,
	2,
	"Timer",
	47,
	1,
	"Interior ID",
	60,
	2,
	"Collision Timer",
	64,
	1,
	"Flags",
	67,
	1,
	"Flags",
	75,
	4,
	"Physical Height (not model/texture height)",
	176,
	2,
	"Position related",
	252,
	4,
	"Pointer to actor object is attached to",
	264,
	4,
	"Height Difference to actor attached to",
	272,
	4,
	"Rotation/pitch - Attached Objects",
	276,
	4,
	"Rotation/roll - Attached Objects",
	348,
	4,
	"Texture scale",
	-1,
	-1,
	NULL
};

static const struct classify_table	classify_table_ped_intelligence[] =
{
	0,
	4,
	"Actor",
	8,
	4,
	"Task falling",
	16,
	4,
	"Active animation task",
	20,
	4,
	"Unknown task",
	24,
	4,
	"Animation task",
	40,
	4,
	"Passive task",
	44,
	4,
	"Unknown task",
	48,
	8,
	"Actor",
	64,
	4,
	"Event fall",
	108,
	4,
	"Actor",
	116,
	4,
	"Pointer to Event",
	-1,
	-1,
	NULL
};

static const struct classify_pool	classify_pool[] =
{
	{ (void *)0x00B74484, 8, "ptr node single", NULL },
	{ (void *)0x00B74488, 12, "ptr node double", NULL },
	{ (void *)0x00B7448C, 20, "entry info node", NULL },
	{ (void *)0x00B74490, 1988, "peds", classify_table_actor },
	{ (void *)0x00B74494, 2584, "vehicles", classify_table_vehicle },
	{ (void *)0x00B74498, 56, "buildings", classify_table_building },
	{ (void *)0x00B7449C, 412, "objects", classify_table_object },
	{ (void *)0x00B744A0, 56, "dummys", NULL },
	{ (void *)0x00B744A4, 48, "col model", NULL },
	{ (void *)0x00B744A8, 128, "task", NULL },
	{ (void *)0x00B744AC, 68, "event", NULL },
	{ (void *)0x00B744B0, 100, "point route", NULL },
	{ (void *)0x00B744B4, 420, "patrol route", NULL },
	{ (void *)0x00B744B8, 36, "node route", NULL },
	{ (void *)0x00B744BC, 32, "task allocator", NULL },
	{ (void *)0x00B744C0, 660, "ped intelligence", classify_table_ped_intelligence },
	{ (void *)0x00B744C4, 196, "ped attractors", NULL },
	{ NULL, 0, NULL, NULL }
};

const char *debug_classify_pointer ( const void *ptr )
{
	const struct classify_pool	*pools = classify_pool;
	static char					str[4][64];
	static int					idx = -1;
	int							i;

	idx = ( idx + 1 ) % 4;

	strcpy( str[idx], "" );

	for ( i = 0; pools[i].pool_ptr != NULL; i++ )
	{
		struct pool					*pool = (struct pool *)( UINT_PTR ) * (uint32_t *)pools[i].pool_ptr;
		const struct classify_table *table = pools[i].table;
		int							item_size = pools[i].item_size;
		const char					*pool_name = pools[i].name;
		void						*pool_end;

		if ( pool == NULL )
			continue;

		if ( pool->size <= 0 || pool->start == NULL )
			continue;

		pool_end = (void *)( (uint8_t *)pool->start + item_size * pool->size );

		if ( ptr >= pool->start && ptr < pool_end )
		{
			int offset = (int)( (uint8_t *)ptr - (uint8_t *)pool->start );
			int item_offset = offset % item_size;
			int id = offset / item_size;

			snprintf( str[idx], sizeof(str[0]), "pool(%s)[%d]+%d", pool_name, id, item_offset );

			// actor (peds) pool
			if( g_SAMP != NULL )
			{
				if ( pools[i].pool_ptr == (void *)ACTOR_POOL_POINTER )
				{
					int			samp_id = getSAMPPlayerIDFromGTAPed( actor_info_get(id, 0) );
					const char	*samp_name = getPlayerName( samp_id );

					if ( samp_name != NULL )
					{
						snprintf( str[idx] + strlen(str[idx]), sizeof(str[0]) - strlen(str[idx]), " %d:\"%s\"", samp_id,
								  samp_name );
					}
				}
			}

			if ( table != NULL )
			{
				strlcat( str[idx], ": ", sizeof(str[0]) );
				while ( table->descr != NULL )
				{
					if ( item_offset >= table->offset && item_offset < table->offset + table->len )
					{
						strlcat( str[idx], table->descr, sizeof(str[0]) );
						break;
					}

					table++;
				}

				if ( table->descr == NULL )
					strlcat( str[idx], "Unknown", sizeof(str[0]) );
			}

			return str[idx];
		}
	}

	if ( g_SAMP != NULL && (void *)g_SAMP >= ptr && (uint8_t *) (g_SAMP + 1) < ptr )
		return "SPL (SA:MP Player List)";

	if ( g_Players != NULL )
	{
		for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
		{
			if ( g_Players->iIsListed[i] != 1 )
				continue;

			if ( (void *)g_Players->pRemotePlayer >= ptr && (void *)(g_Players->pRemotePlayer + 1) < ptr )
			{
				snprintf( str[idx], sizeof(str[0]), "SPL %d:\"%s\"", i, getPlayerName(i) );
				return str[idx];
			}
		}
	}

	return "-";
}
