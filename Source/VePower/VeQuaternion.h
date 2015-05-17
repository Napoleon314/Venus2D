////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeQuaternion.h
//  Version:     v1.00
//  Created:     8/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeMatrix;

class VE_POWER_API VeQuaternion : public VeMemObject
{
	VeDeclareLuaExport(VeQuaternion);
public:
	VeFloat32 x, y, z, w;

	enum Coord
	{
		X = 0,
		Y = 1,
		Z = 2,
		W = 3
	};

	VeQuaternion();

	VeQuaternion(VeFloat32 fX, VeFloat32 fY, VeFloat32 fZ, VeFloat32 fW);

	VeQuaternion(const VeFloat32* pf32Quat);

	VeQuaternion(const VeQuaternion& kQuat);

	VeQuaternion(const VeVector3D& kVec, VeFloat32 fW);

	VE_INLINE operator VeFloat32* ();

	VE_INLINE operator const VeFloat32* () const;

	VE_INLINE VeQuaternion& operator += (const VeQuaternion& kQuat);

	VE_INLINE VeQuaternion& operator -= (const VeQuaternion& kQuat);

	VE_INLINE VeQuaternion& operator *= (const VeQuaternion& kQuat);

	VE_INLINE VeQuaternion& operator *= (VeFloat32 f32Scale);

	VE_INLINE VeQuaternion& operator /= (VeFloat32 f32Scale);

	VE_INLINE VeQuaternion operator + () const;

	VE_INLINE VeQuaternion operator - () const;

	VE_INLINE VeQuaternion operator + (const VeQuaternion& kQuat) const;

	VE_INLINE VeQuaternion operator - (const VeQuaternion& kQuat) const;

	VE_INLINE VeQuaternion operator * (const VeQuaternion& kQuat) const;

	VE_INLINE VeQuaternion operator * (VeFloat32 f32Scale) const;

	VE_INLINE VeQuaternion operator / (VeFloat32 f32Scale) const;

	friend VeQuaternion operator * (VeFloat32 f32Scale, const VeQuaternion& kQuat);

	VE_INLINE VeVector3D operator * (const VeVector3D& kVec) const;

	VE_INLINE bool operator == (const VeQuaternion& kQuat) const;

	VE_INLINE bool operator != (const VeQuaternion& kQuat) const;

	VE_INLINE void SetZero();

	VE_INLINE void Set(VeFloat32 fX, VeFloat32 fY, VeFloat32 fZ, VeFloat32 fW);

	VE_INLINE void Set(const VeVector3D& kVec, VeFloat32 fW);

	VE_INLINE void FromAngleAxis(VeFloat32 f32Angle, const VeVector3D& kAxis);

	VE_INLINE void FromMatrix(const VeMatrix& kMat);

	VE_INLINE void Normalise();

	VE_INLINE void Invert();

	VE_INLINE void Minimise();

	VE_INLINE void Slerp(const VeQuaternion& kStart, const VeQuaternion &kEnd, VeFloat32 t);

	VE_INLINE void Multiply(const VeQuaternion& kQuat0, const VeQuaternion& kQuat1);

	VE_INLINE void PreMultiply(const VeQuaternion& kQuat);

	VE_INLINE void PostMultiply(const VeQuaternion& kQuat);

	VE_INLINE VeFloat32 DotProduct(const VeQuaternion& kQuat) const;

	VE_INLINE VeFloat32 Length() const;

	VE_INLINE VeFloat32 LengthSquared() const;

	static const VeChar8* ToString(const VeQuaternion& kQuat);

	static const VeQuaternion IDENTITY;

};

VE_POWER_API VeQuaternion VeTLerp(VeFloat32 t, const VeQuaternion& a, const VeQuaternion& b);

#ifndef VE_NO_INLINE
#	include "VeQuaternion.inl"
#endif
