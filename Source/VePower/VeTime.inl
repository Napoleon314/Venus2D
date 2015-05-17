////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTime.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeTime::GetDeltaTime()
{
	return (VeFloat32)m_f64DeltaTime;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat64 VeTime::GetDeltaTime64()
{
	return m_f64DeltaTime;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat64 VeTime::GetTime()
{
	return m_f64Time;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeTime::GetTimeUInt()
{
	return (VeUInt32)(m_f64Time * 100);
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt64 VeTime::GetCurrentCount()
{
	return m_u64CurrentCount;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTime::Pause()
{
	m_bPaused = true;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTime::Resume()
{
	m_bPaused = false;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeTime::GetPaused()
{
	return m_bPaused;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTime::SetInvert(bool bInv)
{
	m_bInvert = bInv;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeTime::GetInvert()
{
	return m_bInvert;
}
//--------------------------------------------------------------------------
VE_INLINE VeTimer& VeTime::GetTimer()
{
	return m_kTimer;
}
//--------------------------------------------------------------------------
VE_INLINE void VeTime::Attach(VeTimeEvent* pkEvent, VeFloat64 f64Delay)
{
	m_kTimer.Attach(pkEvent, VeUInt64((m_f64Time + f64Delay) * 1000.0));
}
//--------------------------------------------------------------------------
