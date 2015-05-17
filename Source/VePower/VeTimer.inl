////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTimer.inl
//  Version:     v1.00
//  Created:     15/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeTimeEvent::AddDelegate(Delegate& kDelegate)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt64 VeTimeEvent::GetExecuteTime()
{
	return m_u64ExecuteTime;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTimeEvent::Detach()
{
	if(m_pkParent)
	{
		m_pkParent->Detach(this);
	}
}
//--------------------------------------------------------------------------
VE_INLINE bool VeTimeEvent::IsAttach()const
{
	return m_pkParent ? true : false;
}
//--------------------------------------------------------------------------
VE_INLINE VeTimer* VeTimeEvent::GetParent()
{
	return m_pkParent;
}
//--------------------------------------------------------------------------
