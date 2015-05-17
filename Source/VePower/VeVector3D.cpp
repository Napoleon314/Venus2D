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
#	include "VeVector3D.inl"
#endif

//--------------------------------------------------------------------------
const VeVector3D VeVector3D::ZERO = VeVector3D(0, 0, 0);
//--------------------------------------------------------------------------
const VeVector3D VeVector3D::UNIT_X = VeVector3D(1, 0, 0);
//--------------------------------------------------------------------------
const VeVector3D VeVector3D::UNIT_Y = VeVector3D(0, 1, 0);
//--------------------------------------------------------------------------
const VeVector3D VeVector3D::UNIT_Z = VeVector3D(0, 0, 1);
//--------------------------------------------------------------------------
VeVector3D::VeVector3D()
{
	VeZero3f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VeVector3D::VeVector3D(VeFloat32 fX, VeFloat32 fY, VeFloat32 fZ)
{
	VeSet3f(VE_FLOAT_POINT_THIS, fX, fY, fZ);
}
//--------------------------------------------------------------------------
VeVector3D::VeVector3D(const VeFloat32* pf32Vector)
{
	VeCopy3f(VE_FLOAT_POINT_THIS, pf32Vector);
}
//--------------------------------------------------------------------------
VeVector3D::VeVector3D(const VeVector3D& kVector)
{
	VeCopy3f(VE_FLOAT_POINT_THIS, VE_FLOAT_POINT_CONST(&kVector));
}
//--------------------------------------------------------------------------
VeVector3D::VeVector3D(const VeVector2D& kVector, VeFloat32 fZ)
{
	VeSet3f(VE_FLOAT_POINT_THIS, kVector.x, kVector.y, fZ);
}
//--------------------------------------------------------------------------
VeVector3D::VeVector3D(VeFloat32 fX, const VeVector2D& kVector)
{
	VeSet3f(VE_FLOAT_POINT_THIS, fX, kVector.x, kVector.y);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeVector3D)
{
	Module() [
		Class<VeVector3D>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32,VeFloat32,VeFloat32>()).
			Def(Constructor<const VeVector3D&>()).
			Def(Constructor<const VeVector2D&,VeFloat32>()).
			Def(Constructor<VeFloat32,const VeVector2D&>()).
			Def("SetZero", &VeVector3D::SetZero).
			Def("Set", &VeVector3D::Set).
			Def("Scale", &VeVector3D::Scale).
			Def("Length", &VeVector3D::Length).
			Def("LengthSquared", &VeVector3D::LengthSquared).
			Def("Normalise", &VeVector3D::Normalise).
			Def("ParallelMultiply", (void (VeVector3D::*)(const VeVector3D&))&VeVector3D::ParallelMultiply).
			Def("ParallelMultiply", (void (VeVector3D::*)(const VeVector3D&,const VeVector3D&))&VeVector3D::ParallelMultiply).
			Def("Lerp", &VeVector3D::Lerp).
			Def("Clamp", &VeVector3D::Clamp).
			Def("UnitVector", &VeVector3D::UnitVector).
			Def("SetPitchYaw", &VeVector3D::SetPitchYaw).
			Def("GetYaw", &VeVector3D::GetYaw).
			Def("GetPitch", &VeVector3D::GetPitch).
			Def("DotProduct", &VeVector3D::DotProduct).
			Def("CrossProduct", (void (VeVector3D::*)(const VeVector3D&,const VeVector3D&))&VeVector3D::CrossProduct).
			Def("CrossProduct", (VeVector3D (VeVector3D::*)(const VeVector3D&) const)&VeVector3D::CrossProduct).
			Def("ProjectOnto", (void (VeVector3D::*)(const VeVector3D&,const VeVector3D&))&VeVector3D::ProjectOnto).
			Def("ProjectOnto", (VeVector3D (VeVector3D::*)(const VeVector3D&) const)&VeVector3D::ProjectOnto).
			OpAdd(&OpFuncAdd<VeVector3D,const VeVector3D&,const VeVector3D&>).
			OpSub(&OpFuncSub<VeVector3D,const VeVector3D&,const VeVector3D&>).
			OpUnm(&OpFuncUnm<VeVector3D,const VeVector3D&>).
			DefReadWrite("x", &VeVector3D::x).
			DefReadWrite("y", &VeVector3D::y).
			DefReadWrite("z", &VeVector3D::z).
			OpToStr(&VeVector3D::ToString) [
				Def("Add", &OpFuncAdd<VeVector3D,const VeVector3D&,const VeVector3D&>),
				Def("Sub", &OpFuncSub<VeVector3D,const VeVector3D&,const VeVector3D&>),
				Def("Mul", &OpFuncMul<VeVector3D,const VeVector3D&,VeFloat32>),
				Def("Mul", &OpFuncMul<VeVector3D,VeFloat32,const VeVector3D&>),
				Def("Div", &OpFuncDiv<VeVector3D,const VeVector3D&,VeFloat32>),
				Def("Eq", &OpFuncEq<const VeVector3D&,const VeVector3D&>),
				DefRead("ZERO", VeVector3D::ZERO),
				DefRead("UNIT_X", VeVector3D::UNIT_X),
				DefRead("UNIT_Y", VeVector3D::UNIT_Y),
				DefRead("UNIT_Z", VeVector3D::UNIT_Z)
			],
			Def("VeAlmostEqual", (bool (*)(const VeVector3D&,const VeVector3D&,const VeFloat32))&VeAlmostEqual),
			Def("VeDistance", (VeFloat32 (*)(const VeVector3D&,const VeVector3D&))&VeDistance),
			Def("VeDistanceSquared", (VeFloat32 (*)(const VeVector3D&,const VeVector3D&))&VeDistanceSquared)
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeVector3D::ToString(const VeVector3D& kVector)
{
	VeSprintf(g_acPrintBuffer, "vec3(%.2f,%.2f,%.2f)", kVector.x, kVector.y, kVector.z);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
