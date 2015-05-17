////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector2D.h
//  Version:     v1.00
//  Created:     12/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeVector2D : public VeMemObject
{
	VeDeclareLuaExport(VeVector2D);
public:
	VeFloat32 x, y;

	enum Coord
	{
		X = 0,
		Y = 1
	};

	VeVector2D();

	VeVector2D(VeFloat32 x, VeFloat32 y);

	VeVector2D(const VeFloat32* pf32Vector);

	VeVector2D(const VeVector2D& kVector);

	VE_INLINE operator VeFloat32* ();

	VE_INLINE operator const VeFloat32* () const;

	VE_INLINE VeFloat32& operator [] (Coord eCoord);

	VE_INLINE VeFloat32 operator [] (Coord eCoord) const;

	VE_INLINE VeFloat32& operator () (VeUInt32 i);

	VE_INLINE VeFloat32 operator () (VeUInt32 i) const;

	VE_INLINE VeVector2D& operator = (const VeVector2D& kVector);

	VE_INLINE VeVector2D& operator += (const VeVector2D& kVector);

	VE_INLINE VeVector2D& operator -= (const VeVector2D& kVector);

	VE_INLINE VeVector2D& operator *= (VeFloat32 f32Scale);

	VE_INLINE VeVector2D& operator /= (VeFloat32 f32Scale);

	VE_INLINE VeVector2D operator + () const;

	VE_INLINE VeVector2D operator - () const;

	VE_INLINE VeVector2D operator + (const VeVector2D& kVector) const;

	VE_INLINE VeVector2D operator - (const VeVector2D& kVector) const;

	VE_INLINE VeVector2D operator * (VeFloat32 f32Scale) const;

	VE_INLINE VeVector2D operator / (VeFloat32 f32Scale) const;

	friend VE_POWER_INLINE VeVector2D operator * (VeFloat32 f32Scale, const VeVector2D& kVector);

	friend VE_POWER_INLINE VeVector2D operator / (VeFloat32 f32Scale, const VeVector2D& kVector);

	VE_INLINE bool operator == (const VeVector2D& kVector) const;

	VE_INLINE bool operator != (const VeVector2D& kVector) const;

	VE_INLINE void SetZero();

	VE_INLINE void Set(VeFloat32 x, VeFloat32 y);

	VE_INLINE void Scale(const VeVector2D& kVector, VeFloat32 f32Scale);

	VE_INLINE VeFloat32 Length() const;

	VE_INLINE VeFloat32 LengthSquared() const;

	VE_INLINE void Normalise();

	VE_INLINE void ParallelMultiply(const VeVector2D& kVector);

	VE_INLINE void ParallelMultiply(const VeVector2D& kVector0, const VeVector2D& kVector1);

	VE_INLINE void Lerp(const VeVector2D& kVector0, const VeVector2D& kVector1, VeFloat32 f32Alpha);

	VE_INLINE void Clamp(const VeVector2D& kLower, const VeVector2D& kUpper);

	VE_INLINE VeVector2D UnitVector() const;

	VE_INLINE VeFloat32 DotProduct(const VeVector2D& kVector) const;

	VE_INLINE VeFloat32 CrossProduct(const VeVector2D& kVector) const;

	VE_INLINE void ProjectOnto(const VeVector2D& kVector0, const VeVector2D& kVector1);

	VE_INLINE VeVector2D ProjectOnto(const VeVector2D& kVector) const;

	static const VeChar8* ToString(const VeVector2D& kVector);

	static const VeVector2D ZERO;

	static const VeVector2D UNIT_X;

	static const VeVector2D UNIT_Y;
};

VE_POWER_INLINE bool VeAlmostEqual(const VeVector2D& kVector0, const VeVector2D& kVector1, const VeFloat32 f32Epsilon = VE_MATH_EPSILON_F);

VE_POWER_INLINE VeFloat32 VeDistance(const VeVector2D& kVector0, const VeVector2D& kVector1);

VE_POWER_INLINE VeFloat32 VeDistanceSquared(const VeVector2D& kVector0, const VeVector2D& kVector1);

#ifndef VE_NO_INLINE
#	include "VeVector2D.inl"
#endif
