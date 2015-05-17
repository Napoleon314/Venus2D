////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeDevice.inl
//  Version:     v1.00
//  Created:     17/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeDevice::Type VeDevice::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeDevice::GetMask()
{
	return VE_MASK(m_eType);
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeDevice::GetName()
{
	return VeDevice::TypeLua::ToAlias(m_eType);
}
//--------------------------------------------------------------------------
VE_INLINE const VeStartParams& VeDevice::GetStartParams()
{
	return m_kParams;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeDevice::IsInited()
{
	return m_bInited;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeDevice::IsLuaDebug()
{
	return m_bLuaDebug;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeDevice::GetDeviceID()
{
	return m_kDeviceID;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeDevice::GetDeviceName()
{
	return m_kDeviceName;
}
//--------------------------------------------------------------------------
VE_INLINE void VeDevice::SetLanguage(Language eLan)
{
	m_eLanguage = eLan;
}
//--------------------------------------------------------------------------
VE_INLINE VeDevice::Language VeDevice::GetLanguage()
{
	return m_eLanguage;
}
//--------------------------------------------------------------------------
VE_INLINE void VeDevice::SetTransField(const VeChar8* pcName)
{
	m_kTransField = pcName;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeDevice::GetTransField()
{
	return m_kTransField;
}
//--------------------------------------------------------------------------
