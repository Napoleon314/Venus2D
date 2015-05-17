////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeColor.h
//  Version:     v1.00
//  Created:     14/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeRGBA;

class VE_POWER_API VeColor : public VeMemObject
{
	VeDeclareLuaExport(VeColor);
public:
	VeFloat32 r, g, b, a;

	VeColor(VeFloat32 r = 0.0f, VeFloat32 g = 0.0f, VeFloat32 b = 0.0f, VeFloat32 a = 0.0f);

	VE_INLINE operator VeRGBA () const;

	VE_INLINE operator VeFloat32* ();

	VE_INLINE VeColor& operator = (VeFloat32 f32Scalar);

	VE_INLINE bool operator == (const VeColor& c) const;

	VE_INLINE bool operator != (const VeColor& c) const;

	VE_INLINE VeColor operator + (const VeColor& c) const;

	VE_INLINE VeColor operator - (const VeColor& c) const;

	VE_INLINE VeColor operator * (VeFloat32 f32Scalar) const;

	VE_INLINE VeColor operator * (const VeColor& c) const;

	VE_INLINE VeColor operator / (VeFloat32 f32Scalar) const;

	VE_INLINE VeColor operator / (const VeColor& c) const;

	VE_INLINE VeColor operator - () const;

	friend VE_POWER_INLINE VeColor operator * (VeFloat32 f32Scalar, const VeColor& c);

	VE_INLINE VeColor& operator += (const VeColor& c);

	VE_INLINE VeColor& operator -= (const VeColor& c);

	VE_INLINE VeColor& operator *= (VeFloat32 f32Scalar);

	VE_INLINE VeColor& operator *= (const VeColor& c);

	VE_INLINE VeColor& operator /= (VeFloat32 f32Scalar);

	VE_INLINE VeColor& operator /= (const VeColor& c);

	VE_INLINE void Clamp();

	VE_INLINE void Scale();

	VE_INLINE void GetAs(VeRGBA& kColor) const;

	static const VeChar8* ToString(const VeColor& kColor);

	static const VeColor ZERO;
	static const VeColor WHITE;
	static const VeColor BLACK;
};

class VE_POWER_API VeRGBA : public VeMemObject
{
public:
	VeRGBA(VeUInt8 r = 0, VeUInt8 g = 0, VeUInt8 b = 0, VeUInt8 a = 0);

	VE_INLINE operator VeColor ();

	VE_INLINE VeUInt8& r();

	VE_INLINE const VeUInt8& r() const;

	VE_INLINE VeUInt8& g();

	VE_INLINE const VeUInt8& g() const;

	VE_INLINE VeUInt8& b();

	VE_INLINE const VeUInt8& b() const;

	VE_INLINE VeUInt8& a();

	VE_INLINE const VeUInt8& a() const;

	VE_INLINE VeRGBA& operator = (VeUInt8 uiValue);

	VE_INLINE bool operator == (const VeRGBA& c) const;

	VE_INLINE bool operator!= (const VeRGBA& c) const;

	VE_INLINE VeRGBA operator + (const VeRGBA& c) const;

	VE_INLINE VeRGBA operator - (const VeRGBA& c) const;

	VE_INLINE VeRGBA operator * (VeFloat32 fScalar) const;

	VE_INLINE VeRGBA operator * (const VeRGBA& c) const;

	VE_INLINE VeRGBA operator / (VeFloat32 fScalar) const;

	VE_INLINE VeRGBA operator / (const VeRGBA& c) const;

	VE_INLINE VeRGBA operator - () const;

	friend VE_POWER_INLINE VeRGBA operator * (VeFloat32 fScalar, const VeRGBA& c);

	VE_INLINE VeRGBA& operator += (const VeRGBA& c);

	VE_INLINE VeRGBA& operator -= (const VeRGBA& c);

	VE_INLINE VeRGBA& operator *= (VeFloat32 fScalar);

	VE_INLINE VeRGBA& operator *= (const VeRGBA& c);

	VE_INLINE VeRGBA& operator /= (VeFloat32 fScalar);

	VE_INLINE VeRGBA& operator /= (const VeRGBA& c);

	VE_INLINE void GetAs(VeUInt32& uiColor) const;

	VE_INLINE void GetAsBGRA(VeUInt32& uiColor) const;

	VE_INLINE void GetAs(VeColor& kColor) const;

	static const VeRGBA ZERO;
	static const VeRGBA WHITE;
	static const VeRGBA BLACK;

private:
	struct Color
	{
		VeUInt8 r, g, b, a;
	};

	union 
	{
		Color m_kColor;
		VeUInt32 m_u32Color;
	}; 
};

#ifndef VE_NO_INLINE
#	include "VeColor.inl"
#endif
