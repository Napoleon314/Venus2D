////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTweenEasing.cpp
//  Version:     v1.00
//  Created:     6/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"

//--------------------------------------------------------------------------
VeTweenEasing::VeTweenEasing()
{
	m_afuncFunctionArray[TYPE_NONE] = None;
	m_afuncFunctionArray[TYPE_LINEAR] = Linear;
	m_afuncFunctionArray[TYPE_SINE_IN] = SineIn;
	m_afuncFunctionArray[TYPE_SINE_OUT] = SineOut;
	m_afuncFunctionArray[TYPE_SINE_IN_OUT] = SineInOut;
	m_afuncFunctionArray[TYPE_QUAD_IN] = QuadIn;
	m_afuncFunctionArray[TYPE_QUAD_OUT] = QuadOut;
	m_afuncFunctionArray[TYPE_QUAD_IN_OUT] = QuadInOut;
	m_afuncFunctionArray[TYPE_CUBIC_IN] = CubicIn;
	m_afuncFunctionArray[TYPE_CUBIC_OUT] = CubicOut;
	m_afuncFunctionArray[TYPE_CUBIC_IN_OUT] = CubicInOut;
}
//--------------------------------------------------------------------------
VeTweenEasing::~VeTweenEasing()
{

}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::Ease(Type eType, VeFloat32 f32Pass,
	VeFloat32 f32During)
{
	VE_ASSERT(eType < TYPE_MAX);
	return m_afuncFunctionArray[eType](f32Pass, f32During);
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::None(VeFloat32 f32Pass, VeFloat32 f32During)
{
	return 0.0;
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::Linear(VeFloat32 f32Pass, VeFloat32 f32During)
{
	return f32Pass / f32During;
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::SineIn(VeFloat32 f32Pass, VeFloat32 f32During)
{
	return 1.0f - VeCosf((f32Pass / f32During) * VE_MATH_PI_2_F);
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::SineOut(VeFloat32 f32Pass, VeFloat32 f32During)
{
	return VeSinf((f32Pass / f32During) * VE_MATH_PI_2_F);
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::SineInOut(VeFloat32 f32Pass, VeFloat32 f32During)
{
	return -0.5f * (VeCosf((f32Pass/f32During) * VE_MATH_PI_F) - 1.0f);
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::QuadIn(VeFloat32 f32Pass, VeFloat32 f32During)
{
	f32Pass /= f32During;
	return f32Pass * f32Pass;
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::QuadOut(VeFloat32 f32Pass, VeFloat32 f32During)
{
	f32Pass /= f32During;
	return -f32Pass * (f32Pass - 2.0f);
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::QuadInOut(VeFloat32 f32Pass, VeFloat32 f32During)
{
	f32Pass /= f32During * 0.5f;
	if(f32Pass < 1.0f) return 0.5f * f32Pass * f32Pass;
    f32Pass -= 1.0f;
	return -0.5f * (f32Pass * (f32Pass - 2.0f) - 1.0f);
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::CubicIn(VeFloat32 f32Pass, VeFloat32 f32During)
{
	f32Pass /= f32During;
	return f32Pass * f32Pass *f32Pass;
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::CubicOut(VeFloat32 f32Pass, VeFloat32 f32During)
{
	f32Pass = f32Pass / f32During - 1;
	return (f32Pass * f32Pass * f32Pass + 1);
}
//--------------------------------------------------------------------------
VeFloat32 VeTweenEasing::CubicInOut(VeFloat32 f32Pass, VeFloat32 f32During)
{
	f32Pass /= f32During * 0.5f;
	if (f32Pass < 1.0f) return 0.5f * f32Pass * f32Pass * f32Pass;
	f32Pass -= 2;
	return 0.5f * (f32Pass * f32Pass * f32Pass + 2.0f);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeTweenEasing)
{
	Module() [
		Class<VeTweenEasing> ()
	];
}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeTweenEasing, Type);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeTweenEasing, Type)
{
	VeLuaClassEnumBase(VeTweenEasing, Type);
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_NONE, "none");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_LINEAR, "linear");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_SINE_IN, "sine_in");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_SINE_OUT, "sine_out");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_SINE_IN_OUT, "sine_in_out");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_QUAD_IN, "quad_in");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_QUAD_OUT, "quad_out");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_QUAD_IN_OUT, "quad_in_out");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_CUBIC_IN, "cubic_in");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_CUBIC_OUT, "cubic_out");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_CUBIC_IN_OUT, "cubic_in_out");
	VeLuaClassEnumSlot(VeTweenEasing, Type, TYPE_MAX, "max");
}
//--------------------------------------------------------------------------
