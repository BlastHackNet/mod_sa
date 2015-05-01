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
	CDetour 2.0 by Sinner, don't forget to credit me!

	Credits:
	LanceVorgin (his CDetour class) + z0mbie (ADE32)
*/
/*
Type:						Opcodes needed:
DETOUR_TYPE_JMP:			5
DETOUR_TYPE_PUSH_RET		6
DETOUR_TYPE_NOP_JMP			6
DETOUR_TYPE_NOP_NOP_JMP		7
DETOUR_TYPE_STC_JC			7
DETOUR_TYPE_CLC_JNC			7
DETOUR_TYPE_OBS_ADD			12
DETOUR_TYPE_OBS_STACKADD	13
DETOUR_TYPE_OBS_ROR			13
DETOUR_TYPE_OBS_XOR			14
DETOUR_TYPE_OBS_ADDNOT		14
*/
#pragma once
#pragma warning( disable : 4311 )
#pragma warning( disable : 4312 )
#include "ADE32.h"

typedef enum detour_types_s
{
	DETOUR_TYPE_NOT_SET		= -1,
	DETOUR_TYPE_JMP,
	DETOUR_TYPE_PUSH_RET,
	DETOUR_TYPE_PUSH_FUNC,
	DETOUR_TYPE_CALL_FUNC,
} detour_types_t;

#define DetourRandTypeLow	DETOUR_TYPE_OBS_ADD
#define DetourRandTypeHigh	DETOUR_TYPE_OBS_ADDNOT

class	CDetour
{
public:
	void	*memcpy_s ( void *pvAddress, const void *pvBuffer, size_t stLen );
	void	*Create ( BYTE *orig, const BYTE *det, int iPatchType, int len = 0 );
	void	*Create ( char *dllName, char *apiName, const BYTE *det, int iPatchType, int len = 0 );
	bool	Remove ( BYTE *orig, BYTE *jmp, int iPatchType, int len = 0 );
	bool	Remove ( char *dllName, char *apiName, BYTE *jmp, int iPatchType, int len = 0 );
	bool	BackupFunction ( BYTE *func, int len );
	bool	RestoreFunction ( BYTE *func, int len );
	BYTE	bBackup[20];
private:
	bool	Detour ( BYTE * &jmp, BYTE * &orig, const BYTE * &det, int iPatchType, int len );
	int		GetDetourLen ( int iPatchType );
	int		GetDetourLenAuto ( BYTE * &orig, int iMinLen );
private:
	HMODULE m_hModule;
	DWORD	m_dwAddress;
};
