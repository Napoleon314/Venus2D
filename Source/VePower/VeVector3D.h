////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector3D.h
//  Version:     v1.00
//  Created:     13/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeVector3D : public VeMemObject
{
	VeDeclareLuaExport(VeVector3D);
public:
	VeFloat32 x, y, z;

	enum Coord
	{
		X = 0,
		Y = 1,
		Z = 2
	};

	VeVector3D();

	VeVector3D(VeFloat32 x, VeFloat32 y, VeFloat32 z);

	VeVector3D(const VeFloat32* pf32Vector);

	VeVector3D(const VeVector3D& kVector);

	VeVector3D(const VeVector2D& kVector, VeFloat32 z);

	VeVector3D(VeFloat32 x, const VeVector2D& kVector);

	VE_INLINE operator VeFloat32* ();

	VE_INLINE operator const VeFloat32* () const;

	VE_INLINE VeFloat32& operator [] (Coord eCoord);

	VE_INLINE VeFloat32 operator [] (Coord eCoord) const;

	VE_INLINE VeVector3D& operator = (const VeVector3D& kVector);

	VE_INLINE VeVector3D& operator += (const VeVector3D& kVector);

	VE_INLINE VeVector3D& operator -= (const VeVector3D& kVector);

	VE_INLINE VeVector3D& operator *= (VeFloat32 f32Scale);

	VE_INLINE VeVector3D& operator /= (VeFloat32 f32Scale);

	VE_INLINE VeVector3D operator + () const;

	VE_INLINE VeVector3D operator - () const;

	VE_INLINE VeVector3D operator + (const VeVector3D& kVector) const;

	VE_INLINE VeVector3D operator - (const VeVector3D& kVector) const;

	VE_INLINE VeVector3D operator * (VeFloat32 f32Scale) const;

	VE_INLINE VeVector3D operator / (VeFloat32 f32Scale) const;

	friend VE_POWER_INLINE VeVector3D operator * (VeFloat32 f32Scale, const VeVector3D& kVector);

	friend VE_POWER_INLINE VeVector3D operator / (VeFloat32 f32Scale, const VeVector3D& kVector);

	VE_INLINE bool operator == (const VeVector3D& kVector) const;

	VE_INLINE bool operator != (const VeVector3D& kVector) const;

	VE_INLINE void SetZero();

	VE_INLINE void Set(VeFloat32 x, VeFloat32 y, VeFloat32 z);

	VE_INLINE void Scale(const VeVector3D& kVector, VeFloat32 f32Scale);

	VE_INLINE VeFloat32 Length() const;

	VE_INLINE VeFloat32 LengthSquared() const;

	VE_INLINE void Normalise();

	VE_INLINE void ParallelMultiply(const VeVector3D& kVector);

	VE_INLINE void ParallelMultiply(const VeVector3D& kVector0, const VeVector3D& kVector1);
	
	VE_INLINE void Lerp(const VeVector3D& kVector0, const VeVector3D& kVector1, VeFloat32 f32Alpha);
	
	VE_INLINE void Clamp(const VeVector3D& kLower, const VeVector3D& kUpper);
	
	VE_INLINE VeVector3D UnitVector() const;

	VE_INLINE void SetPitchYaw(VeFloat32 f32PitchInRadians, VeFloat32 f32YawInRadians);

	VE_INLINE VeFloat32 GetYaw() const;

	VE_INLINE VeFloat32 GetPitch() const;

	VE_INLINE VeFloat32 DotProduct(const VeVector3D& kVector) const;

	VE_INLINE void CrossProduct(const VeVector3D& kVector0, const VeVector3D& kVector1);

	VE_INLINE VeVector3D CrossProduct(const VeVector3D& kVector) const;

	VE_INLINE void ProjectOnto(const VeVector3D& kVector0, const VeVector3D& kVector1);

	VE_INLINE VeVector3D ProjectOnto(const VeVector3D& kVector) const;

	static const VeChar8* ToString(const VeVector3D& kVector);

	static const VeVector3D ZERO;

	static const VeVector3D UNIT_X;

	static const VeVector3D UNIT_Y;

	static const VeVector3D UNIT_Z;

};

VE_POWER_INLINE bool VeAlmostEqual(const VeVector3D& kVector0, const VeVector3D& kVector1, const VeFloat32 f32Epsilon = VE_MATH_EPSILON_F);

VE_POWER_INLINE VeFloat32 VeDistance(const VeVector3D& kVector0, const VeVector3D& kVector1);

VE_POWER_INLINE VeFloat32 VeDistanceSquared(const VeVector3D& kVector0, const VeVector3D& kVector1);

#ifndef VE_NO_INLINE
#	include "VeVector3D.inl"
#endif
