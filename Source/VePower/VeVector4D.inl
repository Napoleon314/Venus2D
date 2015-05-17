////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector4D.inl
//  Version:     v1.00
//  Created:     7/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeVector4D::operator VeFloat32* ()
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D::operator const VeFloat32* () const
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32& VeVector4D::operator [] (Coord eCoord)
{
	return VE_FLOAT_POINT_THIS[eCoord];
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector4D::operator [] (Coord eCoord) const
{
	return VE_FLOAT_POINT_THIS[eCoord];
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D& VeVector4D::operator = (const VeVector4D& kVector)
{
	VeCopy4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D& VeVector4D::operator += (const VeVector4D& kVector)
{
	VeAdd4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D& VeVector4D::operator -= (const VeVector4D& kVector)
{
	VeSub4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D& VeVector4D::operator *= (VeFloat32 f32Scale)
{
	VeScale4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D& VeVector4D::operator /= (VeFloat32 f32Scale)
{
	VeScale4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeVector4D::operator + () const
{
	return VeVector4D(*this);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeVector4D::operator - () const
{
	return VeVector4D(-x, -y, -z, -w);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeVector4D::operator + (
	const VeVector4D& kVector) const
{
	VeVector4D kRes;
	VeAdd4f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeVector4D::operator - (
	const VeVector4D& kVector) const
{
	VeVector4D kRes;
	VeSub4f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeVector4D::operator * (VeFloat32 f32Scale) const
{
	VeVector4D kRes;
	VeScale4f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS, f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeVector4D::operator / (VeFloat32 f32Scale) const
{
	VeVector4D kRes;
	VeScale4f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_THIS, 1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D operator * (VeFloat32 f32Scale,
	const VeVector4D& kVector)
{
	VeVector4D kRes;
	VeScale4f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_CONST(&kVector),
		f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D operator / (VeFloat32 f32Scale,
	const VeVector4D& kVector)
{
	VeVector4D kRes;
	VeScale4f(VE_FLOAT_POINT(kRes), VE_FLOAT_POINT_CONST(&kVector),
		1.0f / f32Scale);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeVector4D::operator == (const VeVector4D& kVector) const
{
	return (x == kVector.x) && (y == kVector.y) && (z == kVector.z)
		&& (w == kVector.w);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeVector4D::operator != (const VeVector4D& kVector) const
{
	return (x != kVector.x) || (y != kVector.y) || (z != kVector.z)
		|| (w != kVector.w);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::SetZero()
{
	VeZero4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::Set(VeFloat32 fX, VeFloat32 fY, VeFloat32 fZ,
	VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fX, fY, fZ, fW);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::Scale(const VeVector4D& kVector,
	VeFloat32 f32Scale)
{
	VeScale4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector),
		f32Scale);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::Scale(VeFloat32 f32Scale)
{
	VeScale4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, f32Scale);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector4D::Length() const
{
	return VeSqrtf(LengthSquared());
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector4D::LengthSquared() const
{
	return VeLengthSqr4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::Normalise()
{
	VeFloat32 f32LengthSquared = LengthSquared();
	if(f32LengthSquared) *this *= VeInvSqrtf(f32LengthSquared);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::ParallelMultiply(const VeVector4D& kVector)
{
	VeMul4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS,
		VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::ParallelMultiply(const VeVector4D& kVector0,
	const VeVector4D& kVector1)
{
	VeMul4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector0),
		VE_FLOAT_POINT_CONST(&kVector1));
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeVector4D::DotProduct(const VeVector4D& kVector) const
{
	return VeDot4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VE_INLINE VeVector4D VeVector4D::UnitVector() const
{
	VeVector4D kResVector(*this);
	kResVector.Normalise();
	return kResVector;
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::Lerp(const VeVector4D& kVector0,
	const VeVector4D& kVector1, VeFloat32 f32Alpha)
{
	*this = VeLerp(f32Alpha, kVector0, kVector1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeVector4D::Clamp(const VeVector4D& kLower,
	const VeVector4D& kUpper)
{
	*this = VeClampEx(kLower, *this, kUpper);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAlmostEqual(const VeVector4D& kVector0,
	const VeVector4D& kVector1, const VeFloat32 f32Epsilon)
{
	return VeAlmostEqual(kVector0.x, kVector1.x, f32Epsilon) &&
		VeAlmostEqual(kVector0.y, kVector1.y, f32Epsilon) &&
		VeAlmostEqual(kVector0.z, kVector1.z, f32Epsilon) &&
		VeAlmostEqual(kVector0.w, kVector1.w, f32Epsilon);
}
//--------------------------------------------------------------------------
