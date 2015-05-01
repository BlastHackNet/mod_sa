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
#define PATCHER_CHUNKS_MAX	16

struct patch_chunk
{
	uint32_t	len;			/* length of data @ ptr */
	void		*ptr;			/* ptr to data */
	uint8_t		*data_cmp;		/* compare data against this */
	uint8_t		*data_rep;		/* replacement data @ ptr, if NULL NOPs are used */
	uint8_t		*data_orig;		/* original data @ ptr */
	int			is_volatile;
};

struct patch_set
{
	const char			*name;
	int					initialized;
	int					installed;
	struct patch_chunk	chunk[PATCHER_CHUNKS_MAX];
	int					failed; /* set if patcher_installed() failed to initialize; reset on patcher_remove() */
	int					has_volatile;

	/* these don't really belong here... but oh well. */
	int					ini_auto;	/* automatically enable patch; only used by the ini parser */
	int					ini_hotkey; /* hotkey for this patch; only used by the ini parser */
};

char	*dumb_hex_dump ( void *data, uint32_t len );
int		patcher_install ( struct patch_set *set );
int		patcher_remove ( struct patch_set *set );
int		is_patch_installed ( struct patch_set *patch );
void	patcher_free ( struct patch_set *set );
int		GTAPatchIDFinder ( DWORD patchChunk0Ptr );
