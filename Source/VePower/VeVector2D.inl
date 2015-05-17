////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector2D.inl
//  Version:     v1.00
//  Created:     7/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeVector2D::operator VeFloat32* ()
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D::operator const VeFloat32* () const
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32& VeVector2D::operator [] (Coord eCoord)
{
	return VE_FLOAT_POINT_THIS[eCoord];
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector2D::operator [] (Coord eCoord) const
{
	return VE_FLOAT_POINT_THIS[eCoord];
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32& VeVector2D::operator () (VeUInt32 i)
{
	return VE_FLOAT_POINT_THIS[i];
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector2D::operator () (VeUInt32 i) const
{
	return VE_FLOAT_POINT_THIS[i];
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D& VeVector2D::operator = (const VeVector2D& kVector)
{
	VeCopy2f(VE_FLOAT_POINT_THIS,  VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D& VeVector2D::operator += (const VeVector2D& kVector)
{
	VeAdd2f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D& VeVector2D::operator -= (const VeVector2D& kVector)
{
	VeSub2f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D& VeVector2D::operator *= (VeFloat32 f32Scale)
{
	VeScale2f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D& VeVector2D::operator /= (VeFloat32 f32Scale)
{
	VeScale2f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::operator + () const
{
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::operator - () const
{
	return VeVector2D(-x, -y);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::operator + (
	const VeVector2D& kVector) const
{
	VeVector2D kRes;
	VeAdd2f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::operator - (
	const VeVector2D& kVector) const
{
	VeVector2D kRes;
	VeSub2f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::operator * (VeFloat32 f32Scale) const
{
	VeVector2D kRes;
	VeScale2f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS, f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::operator / (VeFloat32 f32Scale) const
{
	VeVector2D kRes;
	VeScale2f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D operator * (VeFloat32 f32Scale,
	const VeVector2D& kVector)
{
	VeVector2D kRes;
	VeScale2f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_CONST(&kVector),
		f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D operator / (VeFloat32 f32Scale,
	const VeVector2D& kVector)
{
	VeVector2D kRes;
	VeScale2f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_CONST(&kVector),
		1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeVector2D::operator == (const VeVector2D& kVector) const
{
	return (x == kVector.x) && (y == kVector.y);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeVector2D::operator != (const VeVector2D& kVector) const
{
	return (x != kVector.x) || (y != kVector.y);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::SetZero()
{
	VeZero2f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::Set(VeFloat32 fX, VeFloat32 fY)
{
	x = fX;
	y = fY;
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::Scale(const VeVector2D& kVector,
	VeFloat32 f32Scale)
{
	VeScale2f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector),
		f32Scale);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector2D::Length() const
{
	return VeSqrtf(LengthSquared());
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector2D::LengthSquared() const
{
	return VeLengthSqr2f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::Normalise()
{
	VeFloat32 f32LengthSquared = LengthSquared();
	if(f32LengthSquared)
	{
		*this *= VeInvSqrtf(f32LengthSquared);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::ParallelMultiply(const VeVector2D& kVector)
{
	VeMul3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, kVector);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::ParallelMultiply(const VeVector2D& kVector0,
	const VeVector2D& kVector1)
{
	VeMul2f(VE_FLOAT_POINT_THIS, kVector0, kVector1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::Lerp(const VeVector2D& kVector0,
	const VeVector2D& kVector1, VeFloat32 f32Alpha)
{
	*this = VeLerp(f32Alpha, kVector0, kVector1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::Clamp(const VeVector2D& kLower,
	const VeVector2D& kUpper)
{
	*this = VeClampEx(kLower, *this, kUpper);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::UnitVector() const
{
	VeVector2D kResVector(*this);
	kResVector.Normalise();
	return kResVector;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector2D::DotProduct(const VeVector2D& kVector) const
{
	return VeDot2f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector2D::CrossProduct(
	const VeVector2D& kVector) const
{
	return VeVector2Crossf(VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector2D::ProjectOnto(const VeVector2D& kVector0,
	const VeVector2D& kVector1)
{
	*this = kVector1 * (kVector0.DotProduct(kVector1)
		/ kVector1.LengthSquared());
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeVector2D::ProjectOnto(
	const VeVector2D& kVector) const
{
	VeVector2D kRes;
	kRes.ProjectOnto(*this, kVector);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAlmostEqual(const VeVector2D& kVector0,
	const VeVector2D& kVector1, const VeFloat32 f32Epsilon)
{
	return VeAlmostEqual(kVector0.x, kVector1.x, f32Epsilon)
		&& VeAlmostEqual(kVector0.y, kVector1.y, f32Epsilon);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDistance(const VeVector2D& kVector0,
	const VeVector2D& kVector1)
{
	VeVector2D kDelta = kVector0 - kVector1;
	return kDelta.Length();
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeDistanceSquared(const VeVector2D& kVector0,
	const VeVector2D& kVector1)
{
	VeVector2D kDelta = kVector0 - kVector1;
	return kDelta.LengthSquared();
}
//--------------------------------------------------------------------------
