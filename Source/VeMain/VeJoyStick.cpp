////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeJoyStick.cpp
//  Version:     v1.00
//  Created:     24/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeJoyStick.inl"
#endif


//--------------------------------------------------------------------------
VeJoyStick::VeJoyStick()
{

}
//--------------------------------------------------------------------------
VeJoyStick::~VeJoyStick()
{

}
//--------------------------------------------------------------------------
void VeJoyStick::Init()
{

}
//--------------------------------------------------------------------------
void VeJoyStick::Term()
{

}
//--------------------------------------------------------------------------
void VeJoyStick::Update()
{
	for(VeVector<Device>::iterator it = m_kJoyStickArray.Begin(); it != m_kJoyStickArray.End(); ++it)
	{
		it->Update();
	}
}
//--------------------------------------------------------------------------
VeVector<VeJoyStick::Device>& VeJoyStick::GetDeviceArray()
{
	return m_kJoyStickArray;
}
//--------------------------------------------------------------------------
VeJoyStick::Device::Device()
{

}
//--------------------------------------------------------------------------
VeJoyStick::Device::~Device()
{

}
//--------------------------------------------------------------------------
void VeJoyStick::Device::Reset()
{
	for(VeVector<bool>::iterator it = m_kButtons.Begin(); it != m_kButtons.End(); ++it)
	{
		*it = false;
	}
	for(VeVector<VeInt32>::iterator it = m_kAxes.Begin(); it != m_kAxes.End(); ++it)
	{
		*it = 0;
	}
	for(VeVector<PovDirection>::iterator it = m_kPovDirections.Begin(); it != m_kPovDirections.End(); ++it)
	{
		*it = POV_CENTERED;
	}
	for(VeVector<Slider>::iterator it = m_kSliders.Begin(); it != m_kSliders.End(); ++it)
	{
		it->x = 0;
		it->y = 0;
	}
}
//--------------------------------------------------------------------------
void VeJoyStick::Device::Update()
{

}
//--------------------------------------------------------------------------
