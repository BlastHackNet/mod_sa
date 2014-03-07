/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        game_sa/CSettingsSA.h
*  PURPOSE:     Header file for game settings class
*  DEVELOPERS:  Ed Lyons <eai@opencoding.net>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CGAMESA_SETTINGS
#define __CGAMESA_SETTINGS

// R* have this info inside CMenuManager but I can't believe that makes much sense

#include <game/CSettings.h>
#include "Common.h"

#define CLASS_CMenuManager      0xBA6748

#define FUNC_CMenuManager_Save  0x57C660

#define VAR_bMouseSteering      0xC1CC02
#define VAR_bMouseFlying        0xC1CC03

#define CLASS_CAudioEngine 0xB6BC90
#define FUNC_CAudioEngine_SetEffectsMasterVolume 0x506E10
#define FUNC_CAudioEngine_SetMusicMasterVolume 0x506DE0

struct CSettingsSAInterface // see code around 0x57CE9A for where these are
{
	uint8_t		__unknown_h0[0x4];		// 0x0
	float		fStatsScrollSpeed;		// 0x4
	uint8_t		__unknown_h8[0x1C];		// 0x8
	uint8_t		drawRadar;				// 0x24 // 1 - only player blip and north, 2 - no radar
	uint8_t		__unknown_h25[0xE];		// 0x25
	uint8_t		activateMenu;			// 0x33
	uint8_t		menuAccessWidescreen;	// 0x34
	uint8_t		__unknown_h35[0x7];		// 0x35
	float		fBrightness;			// 0x3C
	float		fDrawDistance;			// 0x40
	bool		bSubtitles;				// 0x44
	bool		__boolPad_h45[5];		// 0x45
	bool		bLegend;				// 0x4A
	bool		bUseWideScreen;			// 0x4B
	bool		bFrameLimiter;			// 0x4C
	bool		bAutoRetune;			// 0x4D
	bool		__boolPad_h4E;			// 0x4E
	uint8_t		ucSfxVolume;			// 0x4F
	uint8_t		ucRadioVolume;			// 0x50
	uint8_t		ucRadioEq;				// 0x51
	uint8_t		ucRadioStation;			// 0x52
	uint8_t		__unknown_h53[0x6];		// 0x53
	uint8_t		drawRadarOrMap;			// 0x59
	uint8_t		__unknown_h5A[0x57];	// 0x5A
	bool		bInvertPadX1;			// 0xB1
	bool		bInvertPadY1;			// 0xB2
	bool		bInvertPadX2;			// 0xB3
	bool		bInvertPadY2;			// 0xB4
	bool		bSwapPadAxis1;			// 0xB5
	bool		bSwapPadAxis2;			// 0xB6
	uint8_t		__unknown_hB7[0x11];	// 0xB7
	int			dwAntiAliasing;			// 0xC8
	int			dwFrontendAA;			// 0xCC
	bool		bUseKeyboardAndMouse;	// 0xD0
	uint8_t		__unknown_hD1[3];		// 0xD1
	int			dwVideoMode;			// 0xD4
	int			dwPrevVideoMode;		// 0xD8
///////////////////////
// added by m0d Team //
///////////////////////
	uint8_t		__unknown_hDC[4];		// 0xDC
	int			mousePosLeftA;			// 0xE0
	int			mousePosTopA;			// 0xE4
	// nothing else mapped till the end
	uint8_t		__unknown_hE8[0x1A90];	// 0xE8
	// the end							// 0x1B78
};

class CSettingsSA : public CGameSettings
{
    friend class            COffsets;

private:
    CSettingsSAInterface*   m_pInterface;

public:
                            CSettingsSA                 ( void );

    bool                    IsFrameLimiterEnabled       ( void );
    void                    SetFrameLimiterEnabled      ( bool bEnabled );
    bool                    IsWideScreenEnabled         ( void );
    void                    SetWideScreenEnabled        ( bool bEnabled );
    unsigned int            GetNumVideoModes            ( void );
    VideoMode *             GetVideoModeInfo            ( VideoMode * modeInfo, unsigned int modeIndex );
    unsigned int            GetCurrentVideoMode         ( void );
    void                    SetCurrentVideoMode         ( unsigned int modeIndex, bool bOnRestart );
    unsigned char           GetRadioVolume              ( void );
    void                    SetRadioVolume              ( unsigned char ucVolume );
    unsigned char           GetSFXVolume                ( void );
    void                    SetSFXVolume                ( unsigned char ucVolume );
    float                   GetDrawDistance             ( void );

    void                    Save                        ( void );

private:
    static unsigned long    FUNC_GetNumVideoModes;
    static unsigned long    FUNC_GetVideoModeInfo;
    static unsigned long    FUNC_GetCurrentVideoMode;
    static unsigned long    FUNC_SetCurrentVideoMode;
    static unsigned long    FUNC_SetRadioVolume;
};

#endif