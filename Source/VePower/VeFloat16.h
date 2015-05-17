////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeFloat16.h
//  Version:     v1.00
//  Created:     12/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_MAXFLOAT_H 65504.0f
#define VE_MINFLOAT_H 6.1035156e-5f

class VE_POWER_API VeFloat16 : public VeMemObject
{
public:
	VeFloat16();

	VeFloat16(const VeFloat16& f16Value);

	VeFloat16(VeFloat32 f32Value);

	void Set(VeFloat32 f32Value);

	VeFloat32 Get() const;

	VE_INLINE VeUInt16 GetData() const;

	VE_INLINE operator VeFloat32 () const;

	VE_INLINE VeFloat16 operator + () const;

	VE_INLINE VeFloat16 operator - () const;

	VE_INLINE VeFloat16& operator = (VeFloat16 f16Value);

	VE_INLINE VeFloat16& operator = (VeFloat32 f32Value);

	VE_INLINE VeFloat16& operator += (VeFloat16 f16Value);
	
	VE_INLINE VeFloat16& operator += (VeFloat32 f32Value);

	VE_INLINE VeFloat16& operator -= (VeFloat16 f16Value);
	
	VE_INLINE VeFloat16& operator -= (VeFloat32 f32Value);

	VE_INLINE VeFloat16& operator *= (VeFloat16 f16Value);

	VE_INLINE VeFloat16& operator *= (VeFloat32 f32Value);

	VE_INLINE VeFloat16& operator /= (VeFloat16 f16Value);

	VE_INLINE VeFloat16& operator /= (VeFloat32 f32Value);

	VE_INLINE VeFloat16 operator + (VeFloat16 f16Value) const;

	VE_INLINE VeFloat16 operator - (VeFloat16 f16Value) const;

	VE_INLINE VeFloat16 operator * (VeFloat16 f16Value) const;

	VE_INLINE VeFloat16 operator / (VeFloat16 f16Value) const;

	VE_INLINE bool operator == (VeFloat16 f16Value) const;

	VE_INLINE bool operator == (VeFloat32 f32Value) const;

	VE_INLINE bool operator == (VeFloat64 f64Value) const;

	VE_INLINE bool operator != (VeFloat16 f16Value) const;

	VE_INLINE bool operator != (VeFloat32 f32Value) const;

	VE_INLINE bool operator != (VeFloat64 f64Value) const;

private:
	VeUInt16 m_u16Data;

};

#ifndef VE_NO_INLINE
#	include "VeFloat16.inl"
#endif
