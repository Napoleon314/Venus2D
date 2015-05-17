////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeColor.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////


//--------------------------------------------------------------------------
VE_INLINE VeColor::operator VeRGBA () const
{
	VeRGBA kRes;
	GetAs(kRes);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor& VeColor::operator = (VeFloat32 f32Scalar)
{
	VeSet4f1(VE_FLOAT_POINT_THIS, f32Scalar);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor::operator VeFloat32* ()
{
	return VE_FLOAT_POINT_THIS;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeColor::operator == (const VeColor& c) const
{
	return (r == c.r && g == c.g && b == c.b && a == c.a);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeColor::operator != (const VeColor& c) const
{
	return (r != c.r || g != c.g || b != c.b || a != c.a);
}
//--------------------------------------------------------------------------
VE_INLINE VeColor VeColor::operator + (const VeColor& c) const
{
	VeColor kRes;
	VeAdd4f((VeFloat32*)&kRes, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor VeColor::operator - (const VeColor& c) const
{
	VeColor kRes;
	VeSub4f((VeFloat32*)&kRes, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor VeColor::operator * (VeFloat32 f32Scalar) const
{
	VeColor kRes;
	VeScale4f((VeFloat32*)&kRes, VE_FLOAT_POINT_THIS, f32Scalar);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor VeColor::operator * (const VeColor& c) const
{
	VeColor kRes;
	VeMul4f((VeFloat32*)&kRes, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor VeColor::operator / (VeFloat32 f32Scalar) const
{
	return (*this) * (1.0f / f32Scalar);
}
//--------------------------------------------------------------------------
VE_INLINE VeColor VeColor::operator / (const VeColor& c) const
{
	VeColor kRes;
	VeDiv4f((VeFloat32*)&kRes, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor VeColor::operator - () const
{
	return VeColor(-r, -g, -b, -a);
}
//--------------------------------------------------------------------------
VE_INLINE VeColor operator * (VeFloat32 f32Scalar, const VeColor& c)
{
	return c * f32Scalar;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor& VeColor::operator += (const VeColor& c)
{
	VeAdd4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor& VeColor::operator -= (const VeColor& c)
{
	VeSub4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor& VeColor::operator *= (VeFloat32 f32Scalar)
{
	VeScale4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, f32Scalar);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor& VeColor::operator *= (const VeColor& c)
{
	VeMul4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor& VeColor::operator /= (VeFloat32 f32Scalar)
{
	*this *= 1.0f / f32Scalar;
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeColor& VeColor::operator /= (const VeColor& c)
{
	VeDiv4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, (VeFloat32*)&c);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE void VeColor::Clamp()
{
#	if defined(VE_ENABLE_SSE)
	__m128 temp = _mm_max_ps(_mm_loadu_ps(VE_FLOAT_POINT_THIS), _mm_setzero_ps());
	_mm_storeu_ps(VE_FLOAT_POINT_THIS, _mm_min_ps(temp, _mm_set_ps1(1.0f)));
#	else
	r = VeClampEx(0, r, 1);
	g = VeClampEx(0, g, 1);
	b = VeClampEx(0, b, 1);
	a = VeClampEx(0, a, 1);
#	endif
}
//--------------------------------------------------------------------------
VE_INLINE void VeColor::Scale()
{
	VeFloat32 f32Max = VE_MAX(VE_MAX(r, g), b);
	if(f32Max > 1.0f)
	{
		VeScale3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_THIS, 1.0f / f32Max);
	}

	if(a > 1.0f)
		a = 1.0f;
}
//--------------------------------------------------------------------------
VE_INLINE void VeColor::GetAs(VeRGBA& kColor) const
{
	kColor.r() = (VeUInt8)(VE_SAT(r) * 255.0f);
	kColor.g() = (VeUInt8)(VE_SAT(g) * 255.0f);
	kColor.b() = (VeUInt8)(VE_SAT(b) * 255.0f);
	kColor.a() = (VeUInt8)(VE_SAT(a) * 255.0f);
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA::operator VeColor ()
{
	VeColor kRes;
	GetAs(kRes);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt8& VeRGBA::r()
{
	return m_kColor.r;
}
//--------------------------------------------------------------------------
VE_INLINE const VeUInt8& VeRGBA::r() const
{
	return m_kColor.r;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt8& VeRGBA::g()
{
	return m_kColor.g;
}
//--------------------------------------------------------------------------
VE_INLINE const VeUInt8& VeRGBA::g() const
{
	return m_kColor.g;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt8& VeRGBA::b()
{
	return m_kColor.b;
}
//--------------------------------------------------------------------------
VE_INLINE const VeUInt8& VeRGBA::b() const
{
	return m_kColor.b;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt8& VeRGBA::a()
{
	return m_kColor.a;
}
//--------------------------------------------------------------------------
VE_INLINE const VeUInt8& VeRGBA::a() const
{
	return m_kColor.a;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA& VeRGBA::operator = (VeUInt8 uiValue)
{
	r() = uiValue;
	g() = uiValue;
	b() = uiValue;
	a() = uiValue;
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeRGBA::operator == (const VeRGBA& c) const
{
	return (r() == c.r() && g() == c.g() && b() == c.b() && a() == c.a());
}
//--------------------------------------------------------------------------
VE_INLINE bool VeRGBA::operator!= (const VeRGBA& c) const
{
	return !(*this == c);
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA VeRGBA::operator + (const VeRGBA& c) const
{
	VeRGBA kRes;
	kRes.r() = (VeUInt8)VE_MIN(255, r() + c.r());
	kRes.g() = (VeUInt8)VE_MIN(255, g() + c.g());
	kRes.b() = (VeUInt8)VE_MIN(255, b() + c.b());
	kRes.a() = (VeUInt8)VE_MIN(255, a() + c.a());
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA VeRGBA::operator - (const VeRGBA& c) const
{
	VeRGBA kRes;
	kRes.r() = (VeUInt8)VE_MAX(0, r() - c.r());
	kRes.g() = (VeUInt8)VE_MAX(0, g() - c.g());
	kRes.b() = (VeUInt8)VE_MAX(0, b() - c.b());
	kRes.a() = (VeUInt8)VE_MAX(0, a() - c.a());
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA VeRGBA::operator * (VeFloat32 f32Scalar) const
{
	VeRGBA kRes;
	kRes.r() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)r() * f32Scalar);
	kRes.g() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)g() * f32Scalar);
	kRes.b() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)b() * f32Scalar);
	kRes.a() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)a() * f32Scalar);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA VeRGBA::operator * (const VeRGBA& c) const
{
	VeRGBA kRes;
	kRes.r() = (VeUInt8)VE_MIN(255, r() * c.r());
	kRes.g() = (VeUInt8)VE_MIN(255, g() * c.g());
	kRes.b() = (VeUInt8)VE_MIN(255, b() * c.b());
	kRes.a() = (VeUInt8)VE_MIN(255, a() * c.a());
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA VeRGBA::operator / (VeFloat32 f32Scalar) const
{
	VeFloat32 f32InvScalar = 1.0f / f32Scalar;
	VeRGBA kRes;
	kRes.r() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)r() * f32InvScalar);
	kRes.g() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)g() * f32InvScalar);
	kRes.b() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)b() * f32InvScalar);
	kRes.a() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)a() * f32InvScalar);
	return kRes;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA VeRGBA::operator / (const VeRGBA& c) const
{
	VeRGBA kResult;
	kResult.r() = r() / c.r();
	kResult.g() = g() / c.g();
	kResult.b() = b() / c.b();
	kResult.a() = a() / c.a();
	return kResult;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA VeRGBA::operator - () const
{
	return VeRGBA(-r(), -g(), -b(), -a());
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA operator * (VeFloat32 f32Scalar, const VeRGBA& c)
{
	return c * f32Scalar;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA& VeRGBA::operator += (const VeRGBA& c)
{
	r() = (VeUInt8)VE_MIN(255, r() + c.r());
	g() = (VeUInt8)VE_MIN(255, g() + c.g());
	b() = (VeUInt8)VE_MIN(255, b() + c.b());
	a() = (VeUInt8)VE_MIN(255, a() + c.a());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA& VeRGBA::operator -= (const VeRGBA& c)
{
	r() = (VeUInt8)VE_MAX(0, r() - c.r());
	g() = (VeUInt8)VE_MAX(0, g() - c.g());
	b() = (VeUInt8)VE_MAX(0, b() - c.b());
	a() = (VeUInt8)VE_MAX(0, a() - c.a());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA& VeRGBA::operator *= (VeFloat32 f32Scalar)
{
	r() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)r() * f32Scalar);
	g() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)g() * f32Scalar);
	b() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)b() * f32Scalar);
	a() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)a() * f32Scalar);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA& VeRGBA::operator *= (const VeRGBA& c)
{
	r() = (VeUInt8)VE_MIN(255, r() * c.r());
	g() = (VeUInt8)VE_MIN(255, g() * c.g());
	b() = (VeUInt8)VE_MIN(255, b() * c.b());
	a() = (VeUInt8)VE_MIN(255, a() * c.a());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA& VeRGBA::operator /= (VeFloat32 f32Scalar)
{
	VeFloat32 f32InvScalar = 1.0f / f32Scalar;
	r() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)r() * f32InvScalar);
	g() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)g() * f32InvScalar);
	b() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)b() * f32InvScalar);
	a() = (VeUInt8)VE_MIN(255.0f, (VeFloat32)a() * f32InvScalar);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeRGBA& VeRGBA::operator /= (const VeRGBA& c)
{
	r() = (VeUInt8)(r() / c.r());
	g() = (VeUInt8)(g() / c.g());
	b() = (VeUInt8)(b() / c.b());
	a() = (VeUInt8)(a() / c.a());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE void VeRGBA::GetAs(VeUInt32& u32Color) const
{
	u32Color = m_u32Color;
}
//--------------------------------------------------------------------------
VE_INLINE void VeRGBA::GetAsBGRA(VeUInt32& u32Color) const
{
	VeRGBA kRes(b(), g(), r(), a());
	u32Color = kRes.m_u32Color;
}
//--------------------------------------------------------------------------
VE_INLINE void VeRGBA::GetAs(VeColor& kColor) const
{
	kColor.r = ((VeFloat32)r() / 255.0f);
	kColor.g = ((VeFloat32)g() / 255.0f);
	kColor.b = ((VeFloat32)b() / 255.0f);
	kColor.a = ((VeFloat32)a() / 255.0f);
}
//--------------------------------------------------------------------------
