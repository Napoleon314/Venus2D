////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMatrix.h
//  Version:     v1.00
//  Created:     8/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeMatrix : public VeMemObject
{
	VeDeclareLuaExport(VeMatrix);
public:
	union
	{
		struct
		{
			VeFloat32 _11, _12, _13, _14;
			VeFloat32 _21, _22, _23, _24;
			VeFloat32 _31, _32, _33, _34;
			VeFloat32 _41, _42, _43, _44;
		};
		VeFloat32 m[4][4];
	};

	VeMatrix();

	VeMatrix(const VeFloat32* pf32Matrix);

	VeMatrix(const VeMatrix& kMatrix);

	VeMatrix(
		VeFloat32 _11, VeFloat32 _12, VeFloat32 _13, VeFloat32 _14,
		VeFloat32 _21, VeFloat32 _22, VeFloat32 _23, VeFloat32 _24,
		VeFloat32 _31, VeFloat32 _32, VeFloat32 _33, VeFloat32 _34,
		VeFloat32 _41, VeFloat32 _42, VeFloat32 _43, VeFloat32 _44);

	VeMatrix(const VeVector4D& kRow0, const VeVector4D& kRow1, const VeVector4D& kRow2, const VeVector4D& kRow3);

	VE_INLINE operator VeFloat32* ();

	VE_INLINE operator const VeFloat32* () const;

	VE_INLINE VeFloat32& operator () (VeUInt32 u32Row, VeUInt32 u32Col);

	VE_INLINE const VeFloat32& operator () (VeUInt32 u32Row, VeUInt32 u32Col) const;

	VE_INLINE VeMatrix& operator *= (const VeMatrix& kMatrix);

	VE_INLINE VeMatrix& operator += (const VeMatrix& kMatrix);

	VE_INLINE VeMatrix& operator -= (const VeMatrix& kMatrix);

	VE_INLINE VeMatrix& operator *= (VeFloat32 f32Scale);

	VE_INLINE VeMatrix& operator /= (VeFloat32 f32Scale);

	VE_INLINE VeMatrix operator + () const;

	VE_INLINE VeMatrix operator - () const;

	VE_INLINE VeMatrix operator * (const VeMatrix& kMatrix) const;

	VE_INLINE VeMatrix operator + (const VeMatrix& kMatrix) const;

	VE_INLINE VeMatrix operator - (const VeMatrix& kMatrix) const;

	VE_INLINE VeMatrix operator * (VeFloat32 f32Scale) const;

	VE_INLINE VeMatrix operator / (VeFloat32 f32Scale) const;

	friend VeMatrix operator * (VeFloat32 f32Scale, const VeMatrix& kMatrix);

	VE_INLINE bool operator == (const VeMatrix& kMatrix) const;

	VE_INLINE bool operator != (const VeMatrix& kMatrix) const;

	VE_INLINE VeVector4D& operator [] (VeUInt32 i);

	VE_INLINE const VeVector4D& operator [] (VeUInt32 i) const;

	VE_INLINE VeVector4D& Row(VeUInt32 i);

	VE_INLINE const VeVector4D& Row(VeUInt32 i) const;

	VE_INLINE void Row(VeUInt32 i, const VeVector4D& kVec);

	VE_INLINE VeVector4D Col(VeUInt32 i) const;

	VE_INLINE void Col(VeUInt32 i, const VeVector4D& kVec);

	VE_INLINE void SetZero();

	VE_INLINE void SetIdentity();

	VE_INLINE void SetScale(VeFloat32 x, VeFloat32 y, VeFloat32 z);

	VE_INLINE void SetScale(const VeVector3D& kScale);

	VE_INLINE void SetTranslate(VeFloat32 x, VeFloat32 y, VeFloat32 z);

	VE_INLINE void SetTranslate(const VeVector3D& kPos);

	VE_INLINE void SetRotateX(VeFloat32 f32Angle);

	VE_INLINE void SetRotateY(VeFloat32 f32Angle);

	VE_INLINE void SetRotateZ(VeFloat32 f32Angle);

	VE_INLINE void SetRotate(const VeQuaternion& kQuat);

	VE_INLINE void SetRotate(VeFloat32 f32Yaw, VeFloat32 f32Pitch, VeFloat32 f32Roll);

	VE_INLINE void SetRotateInverse(VeFloat32 f32Yaw, VeFloat32 f32Pitch, VeFloat32 f32Roll);

	VE_INLINE void Multiply(const VeMatrix& kMat0, const VeMatrix& kMat1);

	VE_INLINE void PreMultiply(const VeMatrix& kMat);

	VE_INLINE void PostMultiply(const VeMatrix& kMat);

	VE_INLINE void InvertOrthonormal(const VeMatrix& kMat);

	VE_INLINE void InvertOrthonormal();

	VE_INLINE bool Invert(const VeMatrix& kMat);

	VE_INLINE bool Invert();

	VE_INLINE VeFloat32 GetDeterminant() const;

	VE_INLINE void Transpose(const VeMatrix& kMat);

	VE_INLINE void Transpose();

	VE_INLINE void LookAt(const VeVector3D& kPosition, const VeVector3D& kDirection, const VeVector3D& kUp);

	VE_INLINE VeVector3D ApplyPoint(const VeVector3D& kVec) const;

	VE_INLINE void ApplyPoint(VeVector3D& kVec0, const VeVector3D& kVec1) const;

	VE_INLINE void ApplyPoint(VeVector4D& kVec0, const VeVector3D& kVec1) const;

	VE_INLINE void ApplyPoint(VeVector4D& kVec0, const VeVector4D& kVec1) const;

	VE_INLINE VeVector3D ApplyVector(const VeVector3D& kVec) const;

	VE_INLINE void ApplyVector(VeVector3D& kVec0, const VeVector3D& kVec1) const;

	VE_INLINE const VeVector3D& ApplyToUnitAxisVector(VeUInt32 u32Axis) const;

	/*VE_INLINE const VeVector3D& ApplyToOrigin() const;

	VE_INLINE void PreRotateX(VeFloat32 f32Angle);

	VE_INLINE void PreRotateY(VeFloat32 f32Angle);

	VE_INLINE void PreRotateZ(VeFloat32 f32Angle);

	VE_INLINE void PreTranslateBy(const VeVector3D& kVec);

	void PostRotateX(VeFloat32 f32Angle);

	void PostRotateY(VeFloat32 f32Angle);

	void PostRotateZ(VeFloat32 f32Angle);

	void PostTranslateBy(const VeVector3D& kVec);

	bool IsMirrored() const;

	void OrthogonalProjection(VeFloat32 w, VeFloat32 h, VeFloat32 zn, VeFloat32 zf);

	void PerspectiveProjection(VeFloat32 fov, VeFloat32 aspectRatio, VeFloat32 nearPlane, VeFloat32 farPlane);

	VeFloat32 Yaw() const;

	VeFloat32 Pitch() const;

	VeFloat32 Roll() const;*/

	static const VeChar8* ToString(const VeMatrix& kMat);

	static const VeMatrix ZERO;
	static const VeMatrix IDENTITY;
};

#ifndef VE_NO_INLINE
#	include "VeMatrix.inl"
#endif
