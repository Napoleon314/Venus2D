////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTransform.inl
//  Version:     v1.00
//  Created:     16/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeTransform2D::operator VeFloat32* ()
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeTransform2D::operator const VeFloat32* () const
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE VeTransform2D& VeTransform2D::operator = (
	const VeTransform2D& kTransform)
{
	VeCopy6f(VE_FLOAT_POINT_THIS, kTransform);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeTransform2D::operator == (
	const VeTransform2D& kTransform) const
{
	return a == kTransform.a && b == kTransform.b && c == kTransform.c
		&& d == kTransform.d && x == kTransform.x && y == kTransform.y;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeTransform2D::operator != (
	const VeTransform2D& kTransform) const
{
	return a != kTransform.a || b != kTransform.b || c != kTransform.c
		|| d != kTransform.d || x != kTransform.x || y != kTransform.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::Set(VeFloat32 a, VeFloat32 b,
	VeFloat32 c, VeFloat32 d, VeFloat32 x, VeFloat32 y)
{
	VeSet6f(VE_FLOAT_POINT_THIS, a, b, c, d, x, y);
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::Set(const VeVector2D& kTrans,
	const VeVector2D& kSkew, const VeVector2D& kScale)
{
	VeFloat32 f32SinX, f32CosX, f32SinY, f32CosY;
	VeSinCosf(&f32SinX, &f32CosX, kSkew.y);
	VeSinCosf(&f32SinY, &f32CosY, kSkew.x);
	a = kScale.x * f32CosX;
	b = kScale.x * f32SinX;
	c = -kScale.y * f32SinY;
	d = kScale.y * f32CosY;
	x = kTrans.x;
	y = kTrans.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::Translate(const VeTransform2D& kTransform,
	VeFloat32 x, VeFloat32 y)
{
	a = kTransform.a;
	b = kTransform.b;
	c = kTransform.c;
	d = kTransform.d;
	x = kTransform.x + kTransform.a * x + kTransform.c * y;
	y = kTransform.y + kTransform.b * x + kTransform.d * y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::Rotate(const VeTransform2D& kTransform,
	VeAngle kAngle)
{
	VeFloat32 f32Sin, f32Cos;
	VeSinCosf(&f32Sin, &f32Cos, kAngle);
	a = kTransform.a * f32Cos + kTransform.c * f32Sin;
	b = kTransform.b * f32Cos + kTransform.d * f32Sin;
	c = kTransform.c * f32Cos - kTransform.a * f32Sin;
	d = kTransform.d * f32Cos - kTransform.b * f32Sin;
	x = kTransform.x;
	y = kTransform.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::Scale(const VeTransform2D& kTransform,
	VeFloat32 x, VeFloat32 y)
{
	a = kTransform.a * x;
	b = kTransform.b * x;
	c = kTransform.c * y;
	d = kTransform.d * y;
	x = kTransform.x;
	y = kTransform.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::ApplyPoint(VeVector2D& kOut,
	const VeVector2D& kIn) const
{
	VeVector2D kCopy(kIn);
	kOut.x = _11 * kCopy.x + _21 * kCopy.y + _31;
	kOut.y = _12 * kCopy.x + _22 * kCopy.y + _32;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::ApplyVector(VeVector2D& kOut,
	const VeVector2D& kIn) const
{
	VeVector2D kCopy(kIn);
	kOut.x = _11 * kCopy.x + _21 * kCopy.y;
	kOut.y = _12 * kCopy.x + _22 * kCopy.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::ApplyBounding(VeBoundingBox2D& kOut,
	const VeBoundingBox2D& kIn) const
{
	VeVector2D kLeftTop(kIn.MinBounds());
	VeVector2D kRightTop(kIn.MaxBounds().x, kIn.MinBounds().y);
	VeVector2D kLeftBottom(kIn.MinBounds().x, kIn.MaxBounds().y);
	VeVector2D kRightBottom(kIn.MaxBounds());
	ApplyPoint(kLeftTop, kLeftTop);
	ApplyPoint(kRightTop, kRightTop);
	ApplyPoint(kLeftBottom, kLeftBottom);
	ApplyPoint(kRightBottom, kRightBottom);
	kOut.SetBounds(kLeftTop, kLeftTop);
	kOut.AddBounds(kRightTop);
	kOut.AddBounds(kLeftBottom);
	kOut.AddBounds(kRightBottom);
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::Concat(const VeTransform2D& kTrans0,
	const VeTransform2D& kTrans1)
{
	a = kTrans0.a * kTrans1.a + kTrans0.b * kTrans1.c;
	b = kTrans0.a * kTrans1.b + kTrans0.b * kTrans1.d;
	c = kTrans0.c * kTrans1.a + kTrans0.d * kTrans1.c;
	d = kTrans0.c * kTrans1.b + kTrans0.d * kTrans1.d;
	x = kTrans0.x * kTrans1.a + kTrans0.y * kTrans1.c + kTrans1.x;
	y = kTrans0.x * kTrans1.b + kTrans0.y * kTrans1.d + kTrans1.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTransform2D::Invert(const VeTransform2D& kTransform)
{
	VeFloat32 f32Determinant = 1.0f / (kTransform.a * kTransform.d - kTransform.b * kTransform.c);
	a = f32Determinant * kTransform.d;
	b = -f32Determinant * kTransform.b;
	c = -f32Determinant * kTransform.c;
	d = f32Determinant * kTransform.a;
	x = f32Determinant * (kTransform.c * kTransform.y - kTransform.d * kTransform.x);
	y = f32Determinant * (kTransform.b * kTransform.x - kTransform.a * kTransform.y);
}
//--------------------------------------------------------------------------
