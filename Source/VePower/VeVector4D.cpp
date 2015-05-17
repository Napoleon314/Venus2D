////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector3D.cpp
//  Version:     v1.00
//  Created:     13/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeVector4D.inl"
#endif

//--------------------------------------------------------------------------
const VeVector4D VeVector4D::ZERO = VeVector4D(0, 0, 0, 0);
//--------------------------------------------------------------------------
const VeVector4D VeVector4D::UNIT_X = VeVector4D(1, 0, 0, 0);
//--------------------------------------------------------------------------
const VeVector4D VeVector4D::UNIT_Y = VeVector4D(0, 1, 0, 0);
//--------------------------------------------------------------------------
const VeVector4D VeVector4D::UNIT_Z = VeVector4D(0, 0, 1, 0);
//--------------------------------------------------------------------------
const VeVector4D VeVector4D::ZERO_POINT = VeVector4D(0, 0, 0, 1);
//--------------------------------------------------------------------------
const VeVector4D VeVector4D::UNIT_X_POINT = VeVector4D(1, 0, 0, 1);
//--------------------------------------------------------------------------
const VeVector4D VeVector4D::UNIT_Y_POINT = VeVector4D(0, 1, 0, 1);
//--------------------------------------------------------------------------
const VeVector4D VeVector4D::UNIT_Z_POINT = VeVector4D(0, 0, 1, 1);
//--------------------------------------------------------------------------
VeVector4D::VeVector4D()
{
	VeZero4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(VeFloat32 fX, VeFloat32 fY, VeFloat32 fZ,
	VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fX, fY, fZ, fW);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(const VeFloat32* pf32Vector)
{
	VeCopy4f(VE_FLOAT_POINT_THIS, pf32Vector);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(const VeVector4D& kVector)
{
	VeCopy4f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(const VeVector2D& kVector, VeFloat32 fZ,
	VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, kVector.x, kVector.y, fZ, fW);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(VeFloat32 fX, const VeVector2D& kVector,
	VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fX, kVector.x, kVector.y, fW);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(VeFloat32 fX, VeFloat32 fY,
	const VeVector2D& kVector)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fX, fY, kVector.x, kVector.y);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(const VeVector2D& kVector0,
	const VeVector2D& kVector1)
{
	VeSet4f(VE_FLOAT_POINT_THIS, kVector0.x, kVector0.y, kVector1.x,
		kVector1.y);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(const VeVector3D& kVector, VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, kVector.x, kVector.y, kVector.z, fW);
}
//--------------------------------------------------------------------------
VeVector4D::VeVector4D(VeFloat32 fX, const VeVector3D& kVector)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fX, kVector.x, kVector.y, kVector.z);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeVector4D)
{
	Module() [
		Class<VeVector4D>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32,VeFloat32,VeFloat32,VeFloat32>()).
			Def(Constructor<const VeVector4D&>()).
			Def(Constructor<const VeVector2D&,VeFloat32,VeFloat32>()).
			Def(Constructor<VeFloat32,const VeVector2D&,VeFloat32>()).
			Def(Constructor<VeFloat32,VeFloat32,const VeVector2D&>()).
			Def(Constructor<const VeVector2D&,const VeVector2D&>()).
			Def(Constructor<const VeVector3D&,VeFloat32>()).
			Def(Constructor<VeFloat32,const VeVector3D&>()).
			Def("SetZero", &VeVector4D::SetZero).
			Def("Set", &VeVector4D::Set).
			Def("Scale", (void (VeVector4D::*)(const VeVector4D&,VeFloat32))&VeVector4D::Scale).
			Def("Scale", (void (VeVector4D::*)(VeFloat32))&VeVector4D::Scale).
			Def("Length", &VeVector4D::Length).
			Def("LengthSquared", &VeVector4D::LengthSquared).
			Def("Normalise", &VeVector4D::Normalise).
			Def("ParallelMultiply", (void (VeVector4D::*)(const VeVector4D&))&VeVector4D::ParallelMultiply).
			Def("ParallelMultiply", (void (VeVector4D::*)(const VeVector4D&,const VeVector4D&))&VeVector4D::ParallelMultiply).
			Def("DotProduct", &VeVector4D::DotProduct).
			Def("UnitVector", &VeVector4D::UnitVector).
			Def("Lerp", &VeVector4D::Lerp).
			Def("Clamp", &VeVector4D::Clamp).
			OpAdd(&OpFuncAdd<VeVector4D,const VeVector4D&,const VeVector4D&>).
			OpSub(&OpFuncSub<VeVector4D,const VeVector4D&,const VeVector4D&>).
			OpUnm(&OpFuncUnm<VeVector4D,const VeVector4D&>).
			DefReadWrite("x", &VeVector4D::x).
			DefReadWrite("y", &VeVector4D::y).
			DefReadWrite("z", &VeVector4D::z).
			DefReadWrite("w", &VeVector4D::w).
			OpToStr(&VeVector4D::ToString) [
				Def("Add", &OpFuncAdd<VeVector4D,const VeVector4D&,const VeVector4D&>),
				Def("Sub", &OpFuncSub<VeVector4D,const VeVector4D&,const VeVector4D&>),
				Def("Mul", &OpFuncMul<VeVector4D,const VeVector4D&,VeFloat32>),
				Def("Mul", &OpFuncMul<VeVector4D,VeFloat32,const VeVector4D&>),
				Def("Div", &OpFuncDiv<VeVector4D,const VeVector4D&,VeFloat32>),
				Def("Eq", &OpFuncEq<const VeVector4D&,const VeVector4D&>),
				DefRead("ZERO", VeVector4D::ZERO),
				DefRead("UNIT_X", VeVector4D::UNIT_X),
				DefRead("UNIT_Y", VeVector4D::UNIT_Y),
				DefRead("UNIT_Z", VeVector4D::UNIT_Z),
				DefRead("ZERO_POINT", VeVector4D::ZERO_POINT),
				DefRead("UNIT_X_POINT", VeVector4D::UNIT_X_POINT),
				DefRead("UNIT_Y_POINT", VeVector4D::UNIT_Y_POINT),
				DefRead("UNIT_Z_POINT", VeVector4D::UNIT_Z_POINT)
			],
			Def("VeAlmostEqual", (bool (*)(const VeVector4D&,const VeVector4D&,const VeFloat32))&VeAlmostEqual)
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeVector4D::ToString(const VeVector4D& kVector)
{
	VeSprintf(g_acPrintBuffer, "vec4(%.2f,%.2f,%.2f,%.2f)", kVector.x, kVector.y, kVector.z, kVector.w);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
