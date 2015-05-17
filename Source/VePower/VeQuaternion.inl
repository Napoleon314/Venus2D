////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeQuaternion.inl
//  Version:     v1.00
//  Created:     8/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeQuaternion::operator VeFloat32* ()
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion::operator const VeFloat32* () const
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion& VeQuaternion::operator += (
	const VeQuaternion& kQuat)
{
	VeAdd4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kQuat);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion& VeQuaternion::operator -= (
	const VeQuaternion& kQuat)
{
	VeSub4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kQuat);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion& VeQuaternion::operator *= (
	const VeQuaternion& kQuat)
{
	VeQuaternionMultiplyf(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kQuat);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion& VeQuaternion::operator *= (VeFloat32 f32Scale)
{
	VeScale4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion& VeQuaternion::operator /= (VeFloat32 f32Scale)
{
	VeScale4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion VeQuaternion::operator + () const
{
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion VeQuaternion::operator - () const
{
	return *this * -1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion VeQuaternion::operator + (
	const VeQuaternion& kQuat) const
{
	VeQuaternion kRes;
	VeAdd4f(kRes, VE_FLOAT_POINT_THIS, kQuat);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion VeQuaternion::operator - (
	const VeQuaternion& kQuat) const
{
	VeQuaternion kRes;
	VeSub4f(kRes, VE_FLOAT_POINT_THIS, kQuat);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion VeQuaternion::operator * (
	const VeQuaternion& kQuat) const
{
	VeQuaternion kRes;
	VeQuaternionMultiplyf(kRes, VE_FLOAT_POINT_THIS, kQuat);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion VeQuaternion::operator * (VeFloat32 f32Scale) const
{
	VeQuaternion kRes;
	VeScale4f(kRes, VE_FLOAT_POINT_THIS, f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion VeQuaternion::operator / (VeFloat32 f32Scale) const
{
	VeQuaternion kRes;
	VeScale4f(kRes, VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeQuaternion operator * (VeFloat32 f32Scale,
	const VeQuaternion& kQuat)
{
	VeQuaternion kRes;
	VeScale4f(kRes, kQuat, f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeQuaternion::operator * (const VeVector3D& kVec) const
{
	VeVector3D uv, uuv;
	VeVector3D qvec(x, y, z);
	uv = qvec.CrossProduct(kVec);
	uuv = qvec.CrossProduct(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;
	return kVec + uv + uuv;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeQuaternion::operator == (const VeQuaternion& kQuat) const
{
	return (x == kQuat.x) && (y == kQuat.y) &&
		(z == kQuat.z) && (w == kQuat.w);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeQuaternion::operator != (const VeQuaternion& kQuat) const
{
	return (x != kQuat.x) || (y != kQuat.y) ||
		(z != kQuat.z) || (w != kQuat.w);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::SetZero()
{
	VeZero4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::Set(VeFloat32 fX, VeFloat32 fY,
	VeFloat32 fZ, VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fX, fY, fZ, fW);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::Set(const VeVector3D& kVec, VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, kVec.x, kVec.y, kVec.z, fW);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::FromAngleAxis(VeFloat32 f32Angle,
	const VeVector3D& kAxis)
{
	VeQuaternionRotationAxisf(VE_FLOAT_POINT_THIS, kAxis, f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::FromMatrix(const VeMatrix& kMat)
{
	VeQuaternionRotationMatrixf(VE_FLOAT_POINT_THIS, (VeFloat32*)&kMat);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::Normalise()
{
	VeNormalize4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::Invert()
{
	VeQuaternionInversef(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::Minimise()
{
	if(w < 0)
	{
		*this = -(*this);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::Slerp(const VeQuaternion& kStart,
	const VeQuaternion &kEnd, VeFloat32 t)
{
	VeLerp4f(VE_FLOAT_POINT_THIS, kStart, kEnd, t);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::Multiply(const VeQuaternion& kQuat0,
	const VeQuaternion& kQuat1)
{
	VeQuaternionMultiplyf(VE_FLOAT_POINT_THIS, kQuat0, kQuat1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::PreMultiply(const VeQuaternion& kQuat)
{
	Multiply(kQuat, *this);
}
//--------------------------------------------------------------------------
VE_INLINE void VeQuaternion::PostMultiply(const VeQuaternion& kQuat)
{
	Multiply(*this, kQuat);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeQuaternion::DotProduct(
	const VeQuaternion& kQuat) const
{
	return VeDot4f(VE_FLOAT_POINT_THIS, kQuat);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeQuaternion::Length() const
{
	return VeLength4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeQuaternion::LengthSquared() const
{
	return VeLengthSqr4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
