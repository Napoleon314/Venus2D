////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeFloat16.cpp
//  Version:     v1.00
//  Created:     12/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeFloat16.inl"
#endif

//--------------------------------------------------------------------------
VeFloat16::VeFloat16() : m_u16Data(0)
{

}
//--------------------------------------------------------------------------
VeFloat16::VeFloat16(const VeFloat16& f16Value)
	: m_u16Data(f16Value.m_u16Data)
{

}
//--------------------------------------------------------------------------
VeFloat16::VeFloat16(VeFloat32 f32Value)
{
	Set(f32Value);
}
//--------------------------------------------------------------------------
void VeFloat16::Set(VeFloat32 f32Value)
{
	VE_ASSERT(f32Value <= VE_MAXFLOAT_H && f32Value >= -VE_MAXFLOAT_H);

	if(f32Value >= VE_MINFLOAT_H || f32Value <= -VE_MINFLOAT_H)
	{
		union
		{
			VeFloat32 f;
			VeUInt32 ui;
		} v;
		v.f = f32Value;
		VeUInt32 u32Data = v.ui;
		m_u16Data = VeUInt16(((u32Data >> 16) & 0x8000) | (((((u32Data >> 23) & 0xFF) - 127) + 15) << 10) | ((u32Data >> (23-10)) & 0x3FF));
	}
	else
	{
		m_u16Data = 0;
	}
}
//--------------------------------------------------------------------------
VeFloat32 VeFloat16::Get() const
{
	if(m_u16Data)
	{
		union 
		{
			VeFloat32 f;
			VeUInt32 ui;
		} v;
		VeUInt32 u32Data = m_u16Data;
		v.ui = ((u32Data & 0x8000) << 16) | ((((u32Data >> 10) & 0x1F) + (127-15)) << 23) | ((u32Data & 0x3FF) << (23-10));
		return v.f;
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------------------------------
