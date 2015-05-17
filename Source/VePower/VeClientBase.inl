////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeClientBase.inl
//  Version:     v1.00
//  Created:     17/10/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeClientBase::GetName()
{
	return m_kName;	
}
//--------------------------------------------------------------------------
VE_INLINE VeClientBase::State VeClientBase::GetState()
{
	return m_eState;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeClientManager::GetClientNumber()
{
	return m_kClientMap.Size();
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeClientManager::GetAliveClientNumber()
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	return m_kFGList.Size() + m_kBGList.Size();
}
//--------------------------------------------------------------------------
