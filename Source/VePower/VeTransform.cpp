////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTransform.cpp
//  Version:     v1.00
//  Created:     16/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeTransform.inl"
#endif

//--------------------------------------------------------------------------
const VeTransform2D VeTransform2D::ZERO(0,0,0,0,0,0);
//--------------------------------------------------------------------------
const VeTransform2D VeTransform2D::IDENTITY(1,0,0,1,0,0);
//--------------------------------------------------------------------------
VeTransform2D::VeTransform2D()
{
	VeZero6f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VeTransform2D::VeTransform2D(const VeFloat32* pf32Transform)
{
	VeCopy6f(VE_FLOAT_POINT_THIS, pf32Transform);
}
//--------------------------------------------------------------------------
VeTransform2D::VeTransform2D(const VeTransform2D& kTransform)
{
	VeCopy6f(VE_FLOAT_POINT_THIS, kTransform);
}
//--------------------------------------------------------------------------
VeTransform2D::VeTransform2D(VeFloat32 a, VeFloat32 b,
	VeFloat32 c, VeFloat32 d, VeFloat32 x, VeFloat32 y)
{
	Set(a, b, c, d, x, y);
}
//--------------------------------------------------------------------------
VeTransform2D::VeTransform2D(const VeVector2D& kTrans,
	const VeVector2D& kSkew, const VeVector2D& kScale)
{
	Set(kTrans, kSkew, kScale);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeTransform2D)
{
	Module() [
		Class<VeTransform2D>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32,VeFloat32,VeFloat32,VeFloat32,VeFloat32,VeFloat32>()).
			Def(Constructor<const VeTransform2D&>()).
			Def(Constructor<const VeVector2D&,const VeVector2D&,const VeVector2D&>()).
			Def("Set", (void (VeTransform2D::*)(VeFloat32,VeFloat32,VeFloat32,VeFloat32,VeFloat32,VeFloat32))&VeTransform2D::Set).
			Def("Set", (void (VeTransform2D::*)(const VeVector2D&,const VeVector2D&,const VeVector2D&))&VeTransform2D::Set).
			Def("Translate", &VeTransform2D::Translate).
			Def("Rotate", &VeTransform2D::Rotate).
			Def("Scale", &VeTransform2D::Scale).
			Def("ApplyPoint", &VeTransform2D::ApplyPoint).
			Def("ApplyVector", &VeTransform2D::ApplyVector).
			Def("ApplyBounding", &VeTransform2D::ApplyBounding).
			Def("Concat", &VeTransform2D::Concat).
			Def("Invert", &VeTransform2D::Invert).
			DefReadWrite("a", &VeTransform2D::a).
			DefReadWrite("b", &VeTransform2D::b).
			DefReadWrite("c", &VeTransform2D::c).
			DefReadWrite("d", &VeTransform2D::d).
			DefReadWrite("x", &VeTransform2D::x).
			DefReadWrite("y", &VeTransform2D::y).
			OpToStr(&VeTransform2D::ToString) [
				Def("Eq", &OpFuncEq<const VeTransform2D&,const VeTransform2D&>),
				DefRead("ZERO", VeTransform2D::ZERO),
				DefRead("IDENTITY", VeTransform2D::IDENTITY)
			]
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeTransform2D::ToString(const VeTransform2D& kTrans)
{
	VeSprintf(g_acPrintBuffer, "trans2(%.2f,%.2f,%.2f,%.2f,%.2f,%.2f)",
		kTrans.a, kTrans.b, kTrans.c, kTrans.d, kTrans.x, kTrans.y);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
