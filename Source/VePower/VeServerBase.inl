////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeServerBase.inl
//  Version:     v1.00
//  Created:     16/10/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeServerBase::State VeServerBase::GetState()
{
	return m_eState;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeServerBase::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VeServerBase::GetPort()
{
	return m_u16Port;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VeServerBase::GetMaxConnections()
{
	return m_u16MaxConnections;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeServerBase::GetTimeOut()
{
	return m_u32TimeOut;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeServerBase::GetPassword()
{
	return m_kPassword;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeServerManager::GetServerNumber()
{
	return m_kServerBase.Size();
}
//--------------------------------------------------------------------------
