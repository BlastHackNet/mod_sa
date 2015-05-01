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

char *dumb_hex_dump ( void *data, uint32_t len )
{
	static char buf[1024];
	int			i;

	if ( len > 500 )
		len = 500;

	for ( i = 0; i < (int)len; i++ )
		snprintf( buf + i * 2, sizeof(buf) - i * 2, "%02X", *((uint8_t *)data + i) );

	return buf;
}

int patcher_install ( struct patch_set *patch )
{
	traceLastFunc( "patcher_install()" );

	int i;

	/* previous initialization failed; always return error. */
	if ( !patch->initialized && patch->failed )
		return 0;

	if ( !patch->initialized )
	{
		patch->failed = 1;

		for ( i = 0; i < PATCHER_CHUNKS_MAX; i++ )
		{
			if ( patch->chunk[i].ptr == NULL )
				break;

			if ( patch->chunk[i].data_cmp != NULL
			 &&	 !memcmp_safe((uint8_t *)patch->chunk[i].ptr, patch->chunk[i].data_cmp, patch->chunk[i].len) )
			{
				void	*mem = malloc( patch->chunk[i].len );

				Log( "Data mismatch for patch '%s'.", patch->name );
				if ( mem != NULL )
				{
					if ( memcpy_safe(mem, patch->chunk[i].ptr, patch->chunk[i].len) )
						Log( "Data @ 0x%p is: %s", patch->chunk[i].ptr, dumb_hex_dump(mem, patch->chunk[i].len) );
					Log( "Should be: %s", dumb_hex_dump(patch->chunk[i].data_cmp, patch->chunk[i].len) );
					free( mem );
				}

				return 0;
			}

			if ( patch->chunk[i].data_orig == NULL )
				patch->chunk[i].data_orig = (uint8_t *)malloc( patch->chunk[i].len );
			if ( patch->chunk[i].data_orig == NULL )
				continue;

			if ( !memcpy_safe(patch->chunk[i].data_orig, patch->chunk[i].ptr, patch->chunk[i].len) )
			{
				Log( "Failed to copy original data for patch '%s' chunk %d @ 0x%p", patch->name, i, patch->chunk[i].ptr );
			}
		}

		patch->initialized = 1;
		patch->failed = 0;

		//Log("Initialized patch '%s'.", patch->name);
	}

	if ( !patch->installed || patch->has_volatile )
	{
		for ( i = 0; i < PATCHER_CHUNKS_MAX; i++ )
		{
			if ( patch->chunk[i].ptr == NULL )
				break;

			if ( patch->installed && !patch->chunk[i].is_volatile )
				break;

			if ( patch->chunk[i].data_rep == NULL )
			{
				if ( !memset_safe((uint8_t *)patch->chunk[i].ptr, 0x90, patch->chunk[i].len) )
					Log( "Failed to install patch '%s' chunk %d", patch->name, i );
			}
			else
			{
				if ( !memcpy_safe((uint8_t *)patch->chunk[i].ptr, patch->chunk[i].data_rep, patch->chunk[i].len) )
					Log( "Failed to install patch '%s' chunk %d", patch->name, i );
			}
		}

		if ( !patch->installed )
		{
			patch->installed = 1;

			//Log("Installed patch '%s'.", patch->name);
		}
	}

	return 1;
}

int patcher_remove ( struct patch_set *patch )
{
	traceLastFunc( "patcher_remove()" );

	int i;

	if ( patch->failed )
	{
		patch->failed = 0;
		return 1;
	}

	if ( patch->installed )
	{
		for ( i = 0; i < PATCHER_CHUNKS_MAX; i++ )
		{
			if ( patch->chunk[i].ptr == NULL )
				break;

			if ( !memcpy_safe((uint8_t *)patch->chunk[i].ptr, patch->chunk[i].data_orig, patch->chunk[i].len) )
				Log( "Failed to restore patch '%s' chunk %d", patch->name, i );
		}

		patch->installed = 0;

		//Log("Removed patch '%s'.", patch->name);
	}

	return 1;
}

int is_patch_installed ( struct patch_set *patch )
{
	if ( patch->installed )
		return 1;
	else
		return 0;
}

void patcher_free ( struct patch_set *patch )
{
	int i;

	for ( i = 0; i < PATCHER_CHUNKS_MAX; i++ )
	{
		if ( patch->chunk[i].ptr == NULL )
			break;

		if ( patch->chunk[i].data_orig != NULL )
			free( patch->chunk[i].data_orig );
	}
}

int GTAPatchIDFinder ( DWORD patchChunk0Ptr )
{
	struct patch_set	*patch; // = &set.patch[item->id];
	int					foundPatchID = -1;

	for ( int i = 0; i < INI_PATCHES_MAX; i++ )
	{
		patch = &set.patch[i];
		if ( (DWORD) patch->chunk[0].ptr == patchChunk0Ptr )
		{
			foundPatchID = i;
			break;
		}
	}

	return foundPatchID;
}
