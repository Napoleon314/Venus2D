////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTweenEasing.h
//  Version:     v1.00
//  Created:     6/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeTweenEasing : public VeSingleton<VeTweenEasing>
{
	VeDeclareLuaExport(VeTweenEasing);
public:
	enum Type
	{
		TYPE_NONE,
		TYPE_LINEAR,
		TYPE_SINE_IN,
		TYPE_SINE_OUT,
		TYPE_SINE_IN_OUT,
		TYPE_QUAD_IN,
		TYPE_QUAD_OUT,
		TYPE_QUAD_IN_OUT,
		TYPE_CUBIC_IN,
		TYPE_CUBIC_OUT,
		TYPE_CUBIC_IN_OUT,
		TYPE_MAX
	};
	VeLuaClassEnumDef(Type);

	typedef VeFloat32 (*Function)(VeFloat32 f32Pass, VeFloat32 f32During);

	VeTweenEasing();

	~VeTweenEasing();

	VeFloat32 Ease(Type eType, VeFloat32 f32Pass, VeFloat32 f32During);

public:
	static VeFloat32 None(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 Linear(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 SineIn(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 SineOut(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 SineInOut(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 QuadIn(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 QuadOut(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 QuadInOut(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 CubicIn(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 CubicOut(VeFloat32 f32Pass, VeFloat32 f32During);

	static VeFloat32 CubicInOut(VeFloat32 f32Pass, VeFloat32 f32During);

protected:
	Function m_afuncFunctionArray[TYPE_MAX];

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_MAIN_API, VeTweenEasing, Type);
}

#define g_pTweenEasing VeTweenEasing::GetSingletonPtr()
