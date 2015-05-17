////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeFloat16.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VeFloat16::GetData() const
{
	return m_u16Data;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16::operator VeFloat32() const
{
	return Get();
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16 VeFloat16::operator + () const
{
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16 VeFloat16::operator - () const
{
	VeFloat16 f16Res;
	f16Res.m_u16Data = m_u16Data ^ 0x8000;
	return f16Res;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator = (VeFloat16 f16Value)
{
	m_u16Data = f16Value.m_u16Data;
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator = (VeFloat32 f32Value)
{
	Set(f32Value);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator += (VeFloat16 f16Value)
{
	Set(Get() + f16Value.Get());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator += (VeFloat32 f32Value)
{
	Set(Get() + f32Value);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator -= (VeFloat16 f16Value)
{
	Set(Get() - f16Value.Get());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator -= (VeFloat32 f32Value)
{
	Set(Get() - f32Value);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator *= (VeFloat16 f16Value)
{
	Set(Get() * f16Value.Get());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator *= (VeFloat32 f32Value)
{
	Set(Get() * f32Value);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator /= (VeFloat16 f16Value)
{
	Set(Get() / f16Value.Get());
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16& VeFloat16::operator /= (VeFloat32 f32Value)
{
	Set(Get() / f32Value);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16 VeFloat16::operator + (VeFloat16 f16Value) const
{
	return VeFloat16(Get() + f16Value.Get());
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16 VeFloat16::operator - (VeFloat16 f16Value) const
{
	return VeFloat16(Get() - f16Value.Get());
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16 VeFloat16::operator * (VeFloat16 f16Value) const
{
	return VeFloat16(Get() * f16Value.Get());
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat16 VeFloat16::operator / (VeFloat16 f16Value) const
{
	return VeFloat16(Get() / f16Value.Get());
}
//--------------------------------------------------------------------------
VE_INLINE bool VeFloat16::operator == (VeFloat16 f16Value) const
{
	return (m_u16Data == f16Value.m_u16Data);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeFloat16::operator == (VeFloat32 f32Value) const
{
	VeFloat16 f16Value(f32Value);
	return (m_u16Data == f16Value.m_u16Data);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeFloat16::operator == (VeFloat64 f64Value) const
{
	VeFloat16 f16Value((VeFloat32)f64Value);
	return (m_u16Data == f16Value.m_u16Data);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeFloat16::operator != (VeFloat16 f16Value) const
{
	return (m_u16Data != f16Value.m_u16Data);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeFloat16::operator != (VeFloat32 f32Value) const
{
	VeFloat16 f16Value(f32Value);
	return (m_u16Data != f16Value.m_u16Data);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeFloat16::operator != (VeFloat64 f64Value) const
{
	VeFloat16 f16Value((VeFloat32)f64Value);
	return (m_u16Data != f16Value.m_u16Data);
}
//--------------------------------------------------------------------------
