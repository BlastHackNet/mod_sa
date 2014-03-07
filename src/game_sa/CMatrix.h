/*****************************************************************************
*
*  PROJECT:		Multi Theft Auto v1.0
*  LICENSE:		See LICENSE in the top level directory
*  FILE:		sdk/CMatrix.h
*  PURPOSE:		4x3 GTA matrix class
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CMatrix_H
#define __CMatrix_H

#include "CVector.h"

/**
 * Contains full positional data for a point
 */
class CMatrix
{
public:
	CVector vRight;
	CVector vFront;
	CVector vUp;
	CVector vPos;

    CMatrix ( )
    {
        // Load the identity matrix
        vRight = CVector ( 1.0f, 0.0f, 0.0f );
        vFront = CVector ( 0.0f, 1.0f, 0.0f );
        vUp    = CVector ( 0.0f, 0.0f, 1.0f );
        vPos   = CVector ( 0.0f, 0.0f, 0.0f );
    }

    CMatrix operator+ ( const CMatrix& other ) const
    {
        CMatrix matResult;
        matResult.vRight = vRight + other.vRight;
        matResult.vFront = vFront + other.vFront;
        matResult.vUp    = vUp    + other.vUp;
        matResult.vPos   = vPos   + other.vPos;
        return matResult;
    }

    CMatrix operator- ( const CMatrix& other ) const
    {
        CMatrix matResult;
        matResult.vRight = vRight - other.vRight;
        matResult.vFront = vFront - other.vFront;
        matResult.vUp    = vUp    - other.vUp;
        matResult.vPos   = vPos   - other.vPos;
        return matResult;
    }

    CMatrix operator* ( const CMatrix& other ) const
    {
        CMatrix matResult;
        matResult.vRight = (*this) * other.vRight;
        matResult.vFront = (*this) * other.vFront;
        matResult.vUp    = (*this) * other.vUp;
        matResult.vPos   = (*this) * other.vPos;
        return matResult;
    }

    CMatrix operator/ ( CMatrix other ) const
    {
        other.Invert ();
        return (*this) * other;
    }

    CVector operator* ( const CVector& vec ) const
    {
        return CVector (
            vRight.fX*vec.fX + vFront.fX*vec.fY + vUp.fX*vec.fZ,
            vRight.fY*vec.fX + vFront.fY*vec.fY + vUp.fY*vec.fZ,
            vRight.fZ*vec.fX + vFront.fZ*vec.fY + vUp.fZ*vec.fZ
        );
    }

    void Invert ()
    {
        // Transpose the rotation matrix and negate the position
        CVector vOldRight = vRight, vOldFront = vFront, vOldUp = vUp;
        vRight = CVector ( vOldRight.fX, vOldFront.fX, vOldUp.fX );
        vFront = CVector ( vOldRight.fY, vOldFront.fY, vOldUp.fY );
        vUp    = CVector ( vOldRight.fZ, vOldFront.fZ, vOldUp.fZ );
        vPos  *= -1.0f;
    }

	CMatrix Rotate ( const CVector * param, float theta )
	{
		// Rotate the rotation matrix
		double sin_t = sinf( theta ), cos_t = cosf( theta );
		CMatrix mRotateMult;
		// rotate X
		mRotateMult.vRight.fX = (double) cos_t + ( 1.0f - cos_t ) * param->fX * param->fX;
		mRotateMult.vRight.fY = (double) ( 1.0f - cos_t ) * param->fX * param->fY - sin_t * param->fZ;
		mRotateMult.vRight.fZ = (double) ( 1.0f - cos_t ) * param->fX * param->fZ + sin_t * param->fY;
		// rotate Y
		mRotateMult.vFront.fX = (double) ( 1.0f - cos_t ) * param->fY * param->fX + sin_t * param->fZ;
		mRotateMult.vFront.fY = (double) cos_t + ( 1.0f - cos_t ) * param->fY * param->fY;
		mRotateMult.vFront.fZ = (double) ( 1.0f - cos_t ) * param->fY * param->fZ - sin_t * param->fX;
		// rotate Z
		mRotateMult.vUp.fX = (double) ( 1.0f - cos_t ) * param->fZ * param->fX - sin_t * param->fY;
		mRotateMult.vUp.fY = (double) ( 1.0f - cos_t ) * param->fZ * param->fY + sin_t * param->fX;
		mRotateMult.vUp.fZ = (double) cos_t + ( 1.0f - cos_t ) * param->fZ * param->fZ;
		// multiply matrix
		mRotateMult = mRotateMult * (*this);
		// set vectors
		mRotateMult.vPos = vPos;
		// return
		return mRotateMult;
	}

	void Normalize ( bool bNormalizePosition=0 )
	{
		// normalize vectors
		vRight.Normalize();
		vFront.Normalize();
		vUp.Normalize();

		// if you want the position matric to also be normalized, defaults to no.
		if (bNormalizePosition)
			vPos.Normalize();
	}

};

#endif