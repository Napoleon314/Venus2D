////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector3D.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeVector3D::operator VeFloat32* ()
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D::operator const VeFloat32* () const
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32& VeVector3D::operator [] (Coord eCoord)
{
	return VE_FLOAT_POINT_THIS[eCoord];
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3D::operator [] (Coord eCoord) const
{
	return VE_FLOAT_POINT_THIS[eCoord];
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D& VeVector3D::operator = (const VeVector3D& kVector)
{
	VeCopy3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D& VeVector3D::operator += (const VeVector3D& kVector)
{
	VeAdd3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D& VeVector3D::operator -= (const VeVector3D& kVector)
{
	VeSub3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D& VeVector3D::operator *= (VeFloat32 f32Scale)
{
	VeScale3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D& VeVector3D::operator /= (VeFloat32 f32Scale)
{
	VeScale3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::operator + () const
{
	return VeVector3D(*this);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::operator - () const
{
	return VeVector3D(-x, -y, -z);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::operator + (
	const VeVector3D& kVector) const
{
	VeVector3D kRes;
	VeAdd3f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::operator - (
	const VeVector3D& kVector) const
{
	VeVector3D kRes;
	VeSub3f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::operator * (VeFloat32 f32Scale) const
{
	VeVector3D kRes;
	VeScale3f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS, f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::operator / (VeFloat32 f32Scale) const
{
	VeVector3D kRes;
	VeScale3f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D operator * (VeFloat32 f32Scale,
	const VeVector3D& kVector)
{
	VeVector3D kRes;
	VeScale3f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_CONST(&kVector),
		f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D operator / (VeFloat32 f32Scale,
	const VeVector3D& kVector)
{
	VeVector3D kRes;
	VeScale3f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_CONST(&kVector),
		1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeVector3D::operator == (const VeVector3D& kVector) const
{
	return (x == kVector.x) && (y == kVector.y) && (z == kVector.z);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeVector3D::operator != (const VeVector3D& kVector) const
{
	return (x != kVector.x) || (y != kVector.y) || (z != kVector.z);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::SetZero()
{
	VeZero3f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::Set(VeFloat32 fX, VeFloat32 fY, VeFloat32 fZ)
{
	VeSet3f(VE_FLOAT_POINT_THIS, fX, fY, fZ);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::Scale(const VeVector3D& kVector,
	VeFloat32 f32Scale)
{
	VeScale3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector),
		f32Scale);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3D::Length() const
{
	return VeSqrtf(LengthSquared());
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3D::LengthSquared() const
{
	return VeLengthSqr3f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::Normalise()
{
	VeFloat32 f32LengthSquared = LengthSquared();
	if(f32LengthSquared) *this *= VeInvSqrtf(f32LengthSquared);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::ParallelMultiply(const VeVector3D& kVector)
{
	VeMul3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kVector);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::ParallelMultiply(const VeVector3D& kVector0,
	const VeVector3D& kVector1)
{
	VeMul3f(VE_FLOAT_POINT_THIS, kVector0, kVector1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::Lerp(const VeVector3D& kVector0,
	const VeVector3D& kVector1, VeFloat32 f32Alpha)
{
	*this = VeLerp(f32Alpha, kVector0, kVector1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::Clamp(const VeVector3D& kLower,
	const VeVector3D& kUpper)
{
	*this = VeClampEx(kLower, *this, kUpper);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::UnitVector() const
{
	VeVector3D kResVector(*this);
	kResVector.Normalise();
	return kResVector;
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::SetPitchYaw(VeFloat32 f32PitchInRadians,
	VeFloat32 f32YawInRadians)
{
	VeVector3SetPitchYawf(VE_FLOAT_POINT_THIS, f32PitchInRadians,
		f32YawInRadians);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3D::GetYaw() const
{
	return VeVector3GetYawf(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3D::GetPitch() const
{
	return VeVector3GetPitchf(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector3D::DotProduct(const VeVector3D& kVector) const
{
	return VeDot3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::CrossProduct(const VeVector3D& kVector0,
	const VeVector3D& kVector1)
{
	VeVector3Crossf(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector0),
		VE_FLOAT_POINT_CONST(&kVector1));
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::CrossProduct(
	const VeVector3D& kVector) const
{
	VeVector3D kRes;
	VeVector3Crossf(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector3D::ProjectOnto(const VeVector3D& kVector0,
	const VeVector3D& kVector1)
{
	*this = kVector1 * (kVector0.DotProduct(kVector1)
		/ kVector1.LengthSquared());
}
//--------------------------------------------------------------------------
VE_INLINE VeVector3D VeVector3D::ProjectOnto(
	const VeVector3D& kVector) const
{
	VeVector3D kRes;
	kRes.ProjectOnto(*this, kVector);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAlmostEqual(const VeVector3D& kVector0,
	const VeVector3D& kVector1, const VeFloat32 f32Epsilon)
{
	return VeAlmostEqual(kVector0.x, kVector1.x, f32Epsilon) &&
		VeAlmostEqual(kVector0.y, kVector1.y, f32Epsilon) &&
		VeAlmostEqual(kVector0.z, kVector1.z, f32Epsilon);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDistance(const VeVector3D& kVector0,
	const VeVector3D& kVector1)
{
	VeVector3D kDelta = kVector0 - kVector1;
	return kDelta.Length();
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDistanceSquared(const VeVector3D& kVector0,
	const VeVector3D& kVector1)
{
	VeVector3D kDelta = kVector0 - kVector1;
	return kDelta.LengthSquared();
}
//--------------------------------------------------------------------------
