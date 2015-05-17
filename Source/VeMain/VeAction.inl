////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAction.inl
//  Version:     v1.00
//  Created:     8/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeAction::SetTag(VeInt32 i32Tag)
{
	m_i32Tag = i32Tag;
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeAction::GetTag()
{
	return m_i32Tag;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat64 VeAction::GetStartTime()
{
	return m_f64StartTime;
}
//--------------------------------------------------------------------------
VE_INLINE void VeFiniteTimeAction::SetDuration(VeFloat32 f32Duration)
{
	m_f32Duration = f32Duration;
	m_f32InvDuration = (f32Duration == 0) ? 0 : (1.0f / f32Duration);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeFiniteTimeAction::GetDuration()
{
	return m_f32Duration;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat64 VeActionInterval::GetCurTime()
{
	return m_f64CurTime;
}
//--------------------------------------------------------------------------
