////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector2D.cpp
//  Version:     v1.00
//  Created:     12/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeVector2D.inl"
#endif

//--------------------------------------------------------------------------
const VeVector2D VeVector2D::ZERO = VeVector2D(0, 0);
//--------------------------------------------------------------------------
const VeVector2D VeVector2D::UNIT_X = VeVector2D(1, 0);
//--------------------------------------------------------------------------
const VeVector2D VeVector2D::UNIT_Y = VeVector2D(0, 1);
//--------------------------------------------------------------------------
VeVector2D::VeVector2D()
{
	VeZero2f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VeVector2D::VeVector2D(VeFloat32 fX, VeFloat32 fY)
{
	VeSet2f(VE_FLOAT_POINT_THIS, fX, fY);
}
//--------------------------------------------------------------------------
VeVector2D::VeVector2D(const VeFloat32* pf32Vector)
{
	VeCopy2f(VE_FLOAT_POINT_THIS, pf32Vector);
}
//--------------------------------------------------------------------------
VeVector2D::VeVector2D(const VeVector2D& kVector)
{
	VeCopy2f(VE_FLOAT_POINT_THIS,  VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeVector2D)
{
	Module() [
		Class<VeVector2D>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32,VeFloat32>()).
			Def(Constructor<const VeVector2D&>()).
			Def("SetZero", &VeVector2D::SetZero).
			Def("Set", &VeVector2D::Set).
			Def("Scale", &VeVector2D::Scale).
			Def("Length", &VeVector2D::Length).
			Def("LengthSquared", &VeVector2D::LengthSquared).
			Def("Normalise", &VeVector2D::Normalise).
			Def("ParallelMultiply", (void (VeVector2D::*)(const VeVector2D&))&VeVector2D::ParallelMultiply).
			Def("ParallelMultiply", (void (VeVector2D::*)(const VeVector2D&,const VeVector2D&))&VeVector2D::ParallelMultiply).
			Def("Lerp", &VeVector2D::Lerp).
			Def("Clamp", &VeVector2D::Clamp).
			Def("UnitVector", &VeVector2D::UnitVector).
			Def("DotProduct", &VeVector2D::DotProduct).
			Def("CrossProduct", &VeVector2D::CrossProduct).
			Def("ProjectOnto", (void (VeVector2D::*)(const VeVector2D&,const VeVector2D&))&VeVector2D::ProjectOnto).
			Def("ProjectOnto", (VeVector2D (VeVector2D::*)(const VeVector2D&) const)&VeVector2D::ProjectOnto).
			OpAdd(&OpFuncAdd<VeVector2D,const VeVector2D&,const VeVector2D&>).
			OpSub(&OpFuncSub<VeVector2D,const VeVector2D&,const VeVector2D&>).
			OpUnm(&OpFuncUnm<VeVector2D,const VeVector2D&>).
			DefReadWrite("x", &VeVector2D::x).
			DefReadWrite("y", &VeVector2D::y).
			OpToStr(&VeVector2D::ToString) [
				Def("Add", &OpFuncAdd<VeVector2D,const VeVector2D&,const VeVector2D&>),
				Def("Sub", &OpFuncSub<VeVector2D,const VeVector2D&,const VeVector2D&>),
				Def("Mul", &OpFuncMul<VeVector2D,const VeVector2D&,VeFloat32>),
				Def("Mul", &OpFuncMul<VeVector2D,VeFloat32,const VeVector2D&>),
				Def("Div", &OpFuncDiv<VeVector2D,const VeVector2D&,VeFloat32>),
				Def("Eq", &OpFuncEq<const VeVector2D&,const VeVector2D&>),
				DefRead("ZERO", VeVector2D::ZERO),
				DefRead("UNIT_X", VeVector2D::UNIT_X),
				DefRead("UNIT_Y", VeVector2D::UNIT_Y)
			],
		Def("VeAlmostEqual", (bool (*)(const VeVector2D&,const VeVector2D&,const VeFloat32))&VeAlmostEqual),
		Def("VeDistance", (VeFloat32 (*)(const VeVector2D&,const VeVector2D&))&VeDistance),
		Def("VeDistanceSquared", (VeFloat32 (*)(const VeVector2D&,const VeVector2D&))&VeDistanceSquared)
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeVector2D::ToString(const VeVector2D& kVector)
{
	VeSprintf(g_acPrintBuffer, "vec2(%.2f,%.2f)", kVector.x, kVector.y);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
