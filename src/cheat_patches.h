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


/////////////////////
// RUNTIME PATCHES //
/////////////////////

static struct patch_set patch_EnableResolutions =
{
	"Enable All Supported Resolutions",
	0,
	0,
	{
		{ 2, (void *)0x00745BC9, NULL, NULL, (uint8_t *)"\x7A\x6D" },
		{ 2, (void *)0x007459E1, NULL, NULL, (uint8_t *)"\x7A\x71" }
	}
};

// thanks to MTA for this patch
static struct patch_set patch_DisableLoadingScreen =
{
	"Disable Loading Screen",
	0,
	0,
	{
		{ 5, (void *)0x00748CF6, NULL, NULL, (uint8_t *)"\xE8\x15\xE7\xDB\xFF" },
		{ 5, (void *)0x00590D7C, NULL, NULL, (uint8_t *)"\xE8\x3F\xFD\xFF\xFF" },
		{ 5, (void *)0x00590DB3, NULL, NULL, (uint8_t *)"\xE8\x08\xFD\xFF\xFF" },
		{ 5, (void *)0x00590D9F, NULL, (uint8_t *)"\xC3\x90\x90\x90\x90", (uint8_t *)"\xE9\xCC\xF7\xFF\xFF" }
	}
};
//
//patch[] = "Disable Loading Screen (thanks MTA)	" &0 1 "" 0x00748CF6 "" "9090909090" \
//	"" 0x00590D7C "" "9090909090" \
//	"" 0x00590DB3 "" "9090909090" \
//	"" 0x00590D9F "" "C390909090"
//


//////////////////////
// FUNCTION PATCHES //
//////////////////////

static struct patch_set patch_vehicle_inf_NOS =
{
	"Vehicle Infinite NOS",
	0,
	0,
	{
		{ 1, (void *)0x006A3FFA, (uint8_t *)"\x7A", (uint8_t *)"\xEB", (uint8_t *)"\x7A" },
		{ 2, (void *)0x006A3FB9, (uint8_t *)"\xFE\xC8", (uint8_t *)"\x90\x90", (uint8_t *)"\xFE\xC8" }
	}
};

static struct patch_set patch_NotAPlane =
{
	"Its Not A Plane", //aka deactivate flying for planes
	0,
	0,
	{ 17, (void *)0x006CC46F, (uint8_t *)"\x51\x8B\x4C\x24\x20\x52\x50\x51\x6A\x03\x8B\xCE\xE8\x70\xC1\x00\x00", NULL, NULL }
};

static struct patch_set patch_NoColsWalls =
{
	"No collision walls", // Disable the wall-jump (jumping into air infront of walls)
	0,
	0,
	{ 1, (void *)((uint8_t *)0x00679D3A), (uint8_t *)"\x74", (uint8_t *)"\xEB", (uint8_t *)"\x74" }
};

// Patch will make SP enemies invulnerable
static struct patch_set patch_actor_hp_extraInv =
{
	"Extra actor invincibility",
	0,
	0,
	{ { 10, (void *)0x00637590, (uint8_t *)"\xC7\x87\x40\x05\x00\x00\x00\x00\x00\x00", NULL, NULL }, { 10,
	(void *)0x0063070C, (uint8_t *)"\xC7\x86\x40\x05\x00\x00\x00\x00\x00\x00", NULL, NULL }, { 6,
	(void *)0x004B331F, (uint8_t *)"\x89\x96\x40\x05\x00\x00", NULL, NULL }, { 6, (void *)0x004B3395,
	(uint8_t *)"\x89\x9e\x40\x05\x00\x00", NULL, NULL }, { 6, (void *)0x0064159F,
	NULL, (uint8_t *)"\xE9\x36\x04\x00\x00\x90", NULL } }
};

// Patch won't make SP enemies invulnerable
static struct patch_set patch_actor_hp =
{
	"Extra actor invincibility2",
	0,
	0,
	// Parachute Death
	{ { 7, (void *)0x00635DA0, NULL, (uint8_t *)"\xB8\x00\x00\x00\x00\xC3\x90", NULL } }
};

static struct patch_set patch_vehicle_hp =
{
	"Additional vehicle HP invincibility",
	0,
	0,
	{
		// Invincible Boats (no matching invulnerable flags)
		{ 6, (void *)0x006F1B5C, (uint8_t *)"\x0F\x85\x10\x01\x00\x00", (uint8_t *)"\xE9\x11\x01\x00\x00\x90", NULL } 
	}
};

static struct patch_set patch_gta_auto_aim =
{
	"GTA: Autoaim",
	0,
	0,
	{
		{ 1, (void *)0x00B6EC2E, (uint8_t *)"\x01", (uint8_t *)"\x00", NULL },
		{ 1, (void *)0x00BA6818, (uint8_t *)"\x00", (uint8_t *)"\x01", NULL },
		{ 5, (void *)0x00524013, (uint8_t *)"\xA0\x2E\xEC\xB6\x00", NULL, NULL },
		{ 5, (void *)0x00523F3E, (uint8_t *)"\xA0\x2E\xEC\xB6\x00", NULL, NULL },
		{ 5, (void *)0x00525615, (uint8_t *)"\xA0\x2E\xEC\xB6\x00", NULL, NULL },
		{ 5, (void *)0x005221FC, (uint8_t *)"\xA0\x2E\xEC\xB6\x00", NULL, NULL },
		{ 6, (void *)0x0060E08E, (uint8_t *)"\x0F\x85\x79\x02\x00\x00", NULL, NULL },
		{ 6, (void *)0x0060E6B1, (uint8_t *)"\x0F\x85\xAC\x00\x00\x00", NULL, NULL },
		{ 3, (void *)0x0050AC20, NULL, (uint8_t *)"\xE9\x48\x65", NULL },
		{ 1, (void *)0x005A82C0, NULL, (uint8_t *)"\x56", NULL },
		{ 1, (void *)0x0060DC50, NULL, (uint8_t *)"\x81", NULL },
		{ 3, (void *)0x0060E530, NULL, (uint8_t *)"\x6A\xFF\xE9", NULL }
	}
};

static struct patch_set patch_RemoveFlyUpSpeedLimit =
{
	"Remove Fly Up Hard Limit", // removes the up speed hard limiter when "falling", for Player Fly
	0,
	0,
	{ 7, (void *)((uint8_t *)0x005E91CE), (uint8_t *)"\xC7\x46\x4C\x00\x00\x80\x3E", NULL, (uint8_t *)"\xC7\x46\x4C\x00\x00\x80\x3E" }
};

static struct patch_set patch_RemoveFlyWindSpeedLimit =
{
	"Remove Fly Soft Limits", // removes all speed and spin limiters when "falling", for Player Fly
	0,
	0,
	{ 79, (void *)((uint8_t *)0x00544CFE),
		(uint8_t *)"\xD9\x05\x24\x86\x85\x00\xD8\x64\x24\x04\xD9\x05\x5C\xCB\xB7\x00\xE8\x1D\xD4\x2D\x00\xD9\xC0\xD8\x4E\x44\xD9\x5E\x44\xD9\xC0\xD8\x4E\x48\xD9\x5E\x48\xD8\x4E\x4C\xD9\x5E\x4C\xD9\x46\x50\xD8\x0D\xD0\x2C\x86\x00\xD9\x5E\x50\xD9\x46\x54\xD8\x0D\xD0\x2C\x86\x00\xD9\x5E\x54\xD9\x46\x58\xD8\x0D\xD0\x2C\x86\x00\xD9\x5E\x58",
		NULL,
		(uint8_t *)"\xD9\x05\x24\x86\x85\x00\xD8\x64\x24\x04\xD9\x05\x5C\xCB\xB7\x00\xE8\x1D\xD4\x2D\x00\xD9\xC0\xD8\x4E\x44\xD9\x5E\x44\xD9\xC0\xD8\x4E\x48\xD9\x5E\x48\xD8\x4E\x4C\xD9\x5E\x4C\xD9\x46\x50\xD8\x0D\xD0\x2C\x86\x00\xD9\x5E\x50\xD9\x46\x54\xD8\x0D\xD0\x2C\x86\x00\xD9\x5E\x54\xD9\x46\x58\xD8\x0D\xD0\x2C\x86\x00\xD9\x5E\x58" }
};


// function declarations
void cheat_patches_installRuntimePatches(void);
