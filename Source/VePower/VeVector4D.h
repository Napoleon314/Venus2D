////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector4D.h
//  Version:     v1.00
//  Created:     14/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeVector4D : public VeMemObject
{
	VeDeclareLuaExport(VeVector4D);
public:
	VeFloat32 x, y, z, w;

	enum Coord
	{
		X = 0,
		Y = 1,
		Z = 2,
		W = 3
	};

	VeVector4D();

	VeVector4D(VeFloat32 x, VeFloat32 y, VeFloat32 z, VeFloat32 w);

	VeVector4D(const VeFloat32* pf32Vector);

	VeVector4D(const VeVector4D& kVector);

	VeVector4D(const VeVector2D& kVector, VeFloat32 z, VeFloat32 w);

	VeVector4D(VeFloat32 x, const VeVector2D& kVector, VeFloat32 w);

	VeVector4D(VeFloat32 x, VeFloat32 y, const VeVector2D& kVector);
	
	VeVector4D(const VeVector2D& kVector0, const VeVector2D& kVector1);

	VeVector4D(const VeVector3D& kVector, VeFloat32 w);

	VeVector4D(VeFloat32 x, const VeVector3D& kVector);

	VE_INLINE operator VeFloat32* ();

	VE_INLINE operator const VeFloat32* () const;

	VE_INLINE VeFloat32& operator [] (Coord eCoord);

	VE_INLINE VeFloat32 operator [] (Coord eCoord) const;

	VE_INLINE VeVector4D& operator = (const VeVector4D& kVector);

	VE_INLINE VeVector4D& operator += (const VeVector4D& kVector);

	VE_INLINE VeVector4D& operator -= (const VeVector4D& kVector);

	VE_INLINE VeVector4D& operator *= (VeFloat32 f32Scale);

	VE_INLINE VeVector4D& operator /= (VeFloat32 f32Scale);

	VE_INLINE VeVector4D operator + () const;

	VE_INLINE VeVector4D operator - () const;

	VE_INLINE VeVector4D operator + (const VeVector4D& kVector) const;

	VE_INLINE VeVector4D operator - (const VeVector4D& kVector) const;

	VE_INLINE VeVector4D operator * (VeFloat32 f32Scale) const;
	
	VE_INLINE VeVector4D operator / (VeFloat32 f32Scale) const;

	friend VE_POWER_INLINE VeVector4D operator * (VeFloat32 f32Scale, const VeVector4D& kVector);

	friend VE_POWER_INLINE VeVector4D operator / (VeFloat32 f32Scale, const VeVector4D& kVector);

	VE_INLINE bool operator == (const VeVector4D& kVector) const;

	VE_INLINE bool operator != (const VeVector4D& kVector) const;

	VE_INLINE void SetZero();

	VE_INLINE void Set(VeFloat32 x, VeFloat32 y, VeFloat32 z, VeFloat32 w);

	VE_INLINE void Scale(const VeVector4D& kVector, VeFloat32 f32Scale);

	VE_INLINE void Scale(VeFloat32 f32Scale);

	VE_INLINE VeFloat32 Length() const;

	VE_INLINE VeFloat32 LengthSquared() const;

	VE_INLINE void Normalise();

	VE_INLINE void ParallelMultiply(const VeVector4D& kVector);

	VE_INLINE void ParallelMultiply(const VeVector4D& kVector0, const VeVector4D& kVector1);

	VE_INLINE VeFloat32 DotProduct(const VeVector4D& kVector) const;

	VE_INLINE VeVector4D UnitVector() const;
	
	VE_INLINE void Lerp(const VeVector4D& kVector0, const VeVector4D& kVector1, VeFloat32 f32Alpha);

	VE_INLINE void Clamp(const VeVector4D& kLower, const VeVector4D& kUpper);

	static const VeChar8* ToString(const VeVector4D& kVector);
	
	static const VeVector4D ZERO;

	static const VeVector4D UNIT_X;
	
	static const VeVector4D UNIT_Y;
	
	static const VeVector4D UNIT_Z;
	
	static const VeVector4D ZERO_POINT;
	
	static const VeVector4D UNIT_X_POINT;
	
	static const VeVector4D UNIT_Y_POINT;
	
	static const VeVector4D UNIT_Z_POINT;
};

VE_POWER_INLINE bool VeAlmostEqual(const VeVector4D& kVector0, const VeVector4D& kVector1, const VeFloat32 f32Epsilon = VE_MATH_EPSILON_F);

#ifndef VE_NO_INLINE
#	include "VeVector4D.inl"
#endif
