/*****************************************************************************
*
*  PROJECT:		Multi Theft Auto v1.0
*  LICENSE:		See LICENSE in the top level directory
*  FILE:		game_sa/CCamSA.h
*  PURPOSE:		Header file for camera entity class
*  DEVELOPERS:	Ed Lyons <eai@opencoding.net>
*               Christian Myhre Lundheim <>
*               Jax <>
*               Cecill Etheredge <ijsf@gmx.net>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CGAMESA_CAM
#define __CGAMESA_CAM

#include <game/CCam.h>
#include "CEntitySA.h"
#include "CAutomobileSA.h"
#include "CPedSA.h"

const int NUMBER_OF_VECTORS_FOR_AVERAGE=2;
#define CAM_NUM_TARGET_HISTORY			4

class CCamSAInterface // [568 bytes?]  NOPE.  620 bytes.
{
public:

	bool	bBelowMinDist; // 0 - used for follow ped mode
	bool	bBehindPlayerDesired; // 4 - used for follow ped mode
	bool 	m_bCamLookingAtVector; // 8
	bool 	m_bCollisionChecksOn; // 12
	bool	m_bFixingBeta; // 16 - used for camera on a string
	bool 	m_bTheHeightFixerVehicleIsATrain; // 20
	bool 	LookBehindCamWasInFront; // 24
	bool 	LookingBehind; // 28
	bool 	LookingLeft; // 32
	bool 	LookingRight; // 36
	bool 	ResetStatics; // 40 - for interpolation type stuff to work
	bool 	Rotating; // 44

	short	Mode; // 48 - CameraMode
	unsigned int m_uiFinishTime; // 52

	int 	m_iDoCollisionChecksOnFrameNum; // 56
	int 	m_iDoCollisionCheckEveryNumOfFrames; // 60
	int 	m_iFrameNumWereAt;	// 64
	int 	m_iRunningVectorArrayPos; // 68
	int 	m_iRunningVectorCounter; // 72
	int 	DirectionWasLooking; // 76

	float 	f_max_role_angle; // 80 - =DEGTORAD(5.0f);	
	float 	f_Roll; // 84 - used for adding a slight roll to the camera in the
	float 	f_rollSpeed; // 88 - camera on a string mode
	float 	m_fSyphonModeTargetZOffSet; // 92
	float 	m_fAmountFractionObscured; // 96
	float 	m_fAlphaSpeedOverOneFrame; // 100
	float 	m_fBetaSpeedOverOneFrame; // 104
	float 	m_fBufferedTargetBeta; // 108
	float 	m_fBufferedTargetOrientation; // 112
	float	m_fBufferedTargetOrientationSpeed; // 116
	float 	m_fCamBufferedHeight; // 120
	float 	m_fCamBufferedHeightSpeed; // 124
	float 	m_fCloseInPedHeightOffset; // 128
	float 	m_fCloseInPedHeightOffsetSpeed; // 132
	float 	m_fCloseInCarHeightOffset; // 136
	float 	m_fCloseInCarHeightOffsetSpeed; // 140
	float 	m_fDimensionOfHighestNearCar; // 144
	float	m_fDistanceBeforeChanges; // 148
	float 	m_fFovSpeedOverOneFrame; // 152
	float 	m_fMinDistAwayFromCamWhenInterPolating; // 156
	float 	m_fPedBetweenCameraHeightOffset; // 160
	float 	m_fPlayerInFrontSyphonAngleOffSet; // 164
	float	m_fRadiusForDead; // 168
	float	m_fRealGroundDist; // 172 - used for follow ped mode

	float 	m_fTargetBeta; // 176
	float 	m_fTimeElapsedFloat; // 180	
	float 	m_fTilt; // 184
	float 	m_fTiltSpeed; // 188

	float   m_fTransitionBeta; // 192
	float 	m_fTrueBeta; // 196
	float 	m_fTrueAlpha; // 200
	float	m_fInitialPlayerOrientation; // 204 - used for first person

	float	Alpha; // 208
	float	AlphaSpeed; // 212
	float	FOV; // 216
	float	FOVSpeed; // 220
	float	Beta; // 224
	float	BetaSpeed; // 228
	float	Distance; // 232
	float	DistanceSpeed; // 236
	float 	CA_MIN_DISTANCE; // 240
	float 	CA_MAX_DISTANCE; // 244
	float	SpeedVar; // 248
	float	m_fCameraHeightMultiplier; // 252 - used by TwoPlayer_Separate_Cars_TopDown

	// ped onfoot zoom distance
	float	m_fTargetZoomGroundOne; // 256
	float	m_fTargetZoomGroundTwo; // 260
	float	m_fTargetZoomGroundThree; // 264
	// ped onfoot alpha angle offset
	float	m_fTargetZoomOneZExtra; // 268
	float	m_fTargetZoomTwoZExtra; // 272
	float	m_fTargetZoomTwoInteriorZExtra; // 276 - extra one for interior
	float	m_fTargetZoomThreeZExtra; // 280

	float	m_fTargetZoomZCloseIn; // 284
	float	m_fMinRealGroundDist; // 288
	float	m_fTargetCloseInDist; // 292

	// For targetting in cooperative mode.
	float	Beta_Targeting; // 296
	float	X_Targetting; // 300
	float	Y_Targetting; // 304
	int		CarWeAreFocussingOn; // 308 - which car is closer to the camera in 2 player cooperative mode with separate cars.
	float	CarWeAreFocussingOnI; // 312 - interpolated version

	float	m_fCamBumpedHorz; // 316
	float	m_fCamBumpedVert; // 320
	int		m_nCamBumpedTime; // 324
	static int CAM_BUMPED_SWING_PERIOD; // 328
	static int CAM_BUMPED_END_TIME; // 332
	static float CAM_BUMPED_DAMP_RATE; // 336
	static float CAM_BUMPED_MOVE_MULT; // 340

	CVector m_cvecSourceSpeedOverOneFrame; // 344
	CVector m_cvecTargetSpeedOverOneFrame; // 356
	CVector m_cvecUpOverOneFrame; // 368

	CVector m_cvecTargetCoorsForFudgeInter; // 380
	CVector m_cvecCamFixedModeVector; // 392
	CVector m_cvecCamFixedModeSource; // 404
  	CVector m_cvecCamFixedModeUpOffSet; // 416
	CVector m_vecLastAboveWaterCamPosition; // 428 - helper for when the player has gone under the water

	CVector m_vecBufferedPlayerBodyOffset; // 440

	// The three vectors that determine this camera for this frame
	CVector	Front;	// 452 - Direction of looking in
	CVector	Source;	// 464 - Coors in world space
	CVector	SourceBeforeLookBehind; // 476
	CVector	Up; // 488 - Just that
	CVector	m_arrPreviousVectors[NUMBER_OF_VECTORS_FOR_AVERAGE]; // 500 - used to average stuff

	CVector m_aTargetHistoryPos[CAM_NUM_TARGET_HISTORY]; // 524
	DWORD	m_nTargetHistoryTime[CAM_NUM_TARGET_HISTORY]; // 572
	DWORD	m_nCurrentHistoryPoints; // 588

	CEntitySAInterface *CamTargetEntity; // 592
protected:
	float 	m_fCameraDistance; // 596
	float 	m_fIdealAlpha; // 600
	float 	m_fPlayerVelocity; // 604
	//CVector TempRight; // ??
	CAutomobileSAInterface	*m_pLastCarEntered; // 608 - So interpolation works
	CPedSAInterface			*m_pLastPedLookedAt; // 612 - So interpolation works 
	bool	m_bFirstPersonRunAboutActive; // 616
	// with alignment, 620 = end
};

class CCamSA : public CCam
{
private:
	CCamSAInterface*    m_pInterface;

public:
	                    CCamSA                      ( CCamSAInterface* pInterface )     { m_pInterface = pInterface; }
	CCamSAInterface*    GetInterface                ()              { return m_pInterface; }

    CVector*            GetFront                    () const        { return &m_pInterface->Front; }
    CVector*            GetUp                       () const        { return &m_pInterface->Up; }
    CVector*            GetSource                   () const        { return &m_pInterface->Source; }
    unsigned int        GetMode                     () const        { return m_pInterface->Mode; }
    float               GetFOV                      () const        { return m_pInterface->FOV; }
    void                SetFOV                      ( float fFOV )  { m_pInterface->FOV = fFOV; }

    CVector*            GetFixedModeSource          () const        { return &m_pInterface->m_cvecCamFixedModeSource; }
    CVector*            GetFixedModeVector          () const        { return &m_pInterface->m_cvecCamFixedModeVector; }
    CVector*            GetTargetHistoryPos         () const        { return m_pInterface->m_aTargetHistoryPos; }

    CEntity*            GetTargetEntity             () const;
};

#endif
