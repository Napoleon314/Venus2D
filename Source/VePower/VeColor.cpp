////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeColor.cpp
//  Version:     v1.00
//  Created:     14/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeColor.inl"
#endif

//--------------------------------------------------------------------------
const VeColor VeColor::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
//--------------------------------------------------------------------------
const VeColor VeColor::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
//--------------------------------------------------------------------------
const VeColor VeColor::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
//--------------------------------------------------------------------------
VeColor::VeColor(VeFloat32 fR, VeFloat32 fG, VeFloat32 fB, VeFloat32 fA)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fR, fG, fB, fA);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeColor)
{
	Module() [
		Class<VeColor>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32>()).
			Def(Constructor<VeFloat32,VeFloat32>()).
			Def(Constructor<VeFloat32,VeFloat32,VeFloat32>()).
			Def(Constructor<VeFloat32,VeFloat32,VeFloat32,VeFloat32>()).
			Def(Constructor<const VeColor&>()).
			Def("Clamp", &VeColor::Clamp).
			Def("Scale", &VeColor::Scale).
			OpAdd(&OpFuncAdd<VeColor,const VeColor&,const VeColor&>).
			OpSub(&OpFuncSub<VeColor,const VeColor&,const VeColor&>).
			OpMul(&OpFuncMul<VeColor,const VeColor&,const VeColor&>).
			OpDiv(&OpFuncDiv<VeColor,const VeColor&,const VeColor&>).
			OpUnm(&OpFuncUnm<VeColor,const VeColor&>).
			DefReadWrite("r", &VeColor::r).
			DefReadWrite("g", &VeColor::g).
			DefReadWrite("b", &VeColor::b).
			DefReadWrite("a", &VeColor::a).
			OpToStr(&VeColor::ToString) [
				Def("Add", &OpFuncAdd<VeColor,const VeColor&,const VeColor&>),
				Def("Sub", &OpFuncSub<VeColor,const VeColor&,const VeColor&>),
				Def("Mul", &OpFuncMul<VeColor,const VeColor&,const VeColor&>),
				Def("Div", &OpFuncDiv<VeColor,const VeColor&,const VeColor&>),
				Def("Mul", &OpFuncMul<VeColor,const VeColor&,VeFloat32>),
				Def("Mul", &OpFuncMul<VeColor,VeFloat32,const VeColor&>),
				Def("Div", &OpFuncDiv<VeColor,const VeColor&,VeFloat32>),
				Def("Eq", &OpFuncEq<const VeColor&,const VeColor&>),
				DefRead("ZERO", VeColor::ZERO),
				DefRead("WHITE", VeColor::WHITE),
				DefRead("BLACK", VeColor::BLACK)
			]
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeColor::ToString(const VeColor& kColor)
{
	VeSprintf(g_acPrintBuffer, "color(%.1f,%.1f,%.1f,%.1f)", kColor.r, kColor.g, kColor.b, kColor.a);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
const VeRGBA VeRGBA::ZERO(0, 0, 0, 0);
//--------------------------------------------------------------------------
const VeRGBA VeRGBA::WHITE(255, 255, 255, 255);
//--------------------------------------------------------------------------
const VeRGBA VeRGBA::BLACK(0, 0, 0, 255);
//--------------------------------------------------------------------------
VeRGBA::VeRGBA(VeUInt8 u8R, VeUInt8 u8G, VeUInt8 u8B, VeUInt8 u8A)
	: m_u32Color(0)
{
	r() = u8R;
	g() = u8G;
	b() = u8B;
	a() = u8A;
}
//--------------------------------------------------------------------------
