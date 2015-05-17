////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeJoyStick.h
//  Version:     v1.00
//  Created:     24/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeJoyStick : public VeSingleton<VeJoyStick>
{
public:
	enum PovDirection
	{
		POV_CENTERED,
		POV_NORTH,
		POV_SOUTH,
		POV_EAST,
		POV_WEST,
		POV_NORTH_EAST,
		POV_SOUTH_EAST,
		POV_NORTH_WEST,
		POV_SOUTH_WEST
	};

	struct Slider
	{
		VE_INLINE Slider();
		VeInt32 x;
		VeInt32 y;
	};

	struct Device
	{
		Device();

		~Device();

		void Reset();

		void Update();

		VeVector<bool> m_kButtons;
		VeVector<VeInt32> m_kAxes;
		VeVector<PovDirection> m_kPovDirections;
		VeVector<Slider> m_kSliders;
	};

	VE_INLINE VeJoyStick();

	VE_INLINE ~VeJoyStick();

	void Init();

	void Term();

	void Update();

	VE_INLINE bool IsButtonDown(VeUInt32 u32Device, VeUInt32 u32Index);

	VE_INLINE VeInt32 GetAxisValue(VeUInt32 u32Device, VeUInt32 u32Index);

	VE_INLINE PovDirection GetPovDirection(VeUInt32 u32Device, VeUInt32 u32Index);

	VE_INLINE Slider GetSlider(VeUInt32 u32Device, VeUInt32 u32Index);

#ifndef VE_USER
	VeVector<Device>& GetDeviceArray();
#endif

protected:
	VeVector<Device> m_kJoyStickArray;

};

#define g_pJoyStick VeJoyStick::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeJoyStick.inl"
#endif
