////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeJoyStick.inl
//  Version:     v1.00
//  Created:     7/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE bool VeJoyStick::IsButtonDown(VeUInt32 u32Device,
	VeUInt32 u32Index)
{
	VE_ASSERT(u32Device < m_kJoyStickArray.Size()
		&& u32Index < m_kJoyStickArray[u32Device].m_kButtons.Size());
	return m_kJoyStickArray[u32Device].m_kButtons[u32Index];
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeJoyStick::GetAxisValue(VeUInt32 u32Device,
	VeUInt32 u32Index)
{
	VE_ASSERT(u32Device < m_kJoyStickArray.Size()
		&& u32Index < m_kJoyStickArray[u32Device].m_kAxes.Size());
	return m_kJoyStickArray[u32Device].m_kAxes[u32Index];
}
//--------------------------------------------------------------------------
VE_INLINE VeJoyStick::PovDirection VeJoyStick::GetPovDirection(
	VeUInt32 u32Device, VeUInt32 u32Index)
{
	VE_ASSERT(u32Device < m_kJoyStickArray.Size()
		&& u32Index < m_kJoyStickArray[u32Device].m_kPovDirections.Size());
	return m_kJoyStickArray[u32Device].m_kPovDirections[u32Index];
}
//--------------------------------------------------------------------------
VE_INLINE VeJoyStick::Slider VeJoyStick::GetSlider(VeUInt32 u32Device,
	VeUInt32 u32Index)
{
	VE_ASSERT(u32Device < m_kJoyStickArray.Size()
		&& u32Index < m_kJoyStickArray[u32Device].m_kSliders.Size());
	return m_kJoyStickArray[u32Device].m_kSliders[u32Index];
}
//--------------------------------------------------------------------------
VE_INLINE VeJoyStick::Slider::Slider() : x(0), y(0)
{

}
//--------------------------------------------------------------------------
