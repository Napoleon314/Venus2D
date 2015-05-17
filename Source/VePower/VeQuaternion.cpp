////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeQuaternion.cpp
//  Version:     v1.00
//  Created:     8/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeQuaternion.inl"
#endif

//--------------------------------------------------------------------------
VeQuaternion VeTLerp(VeFloat32 t, const VeQuaternion& a, const VeQuaternion& b)
{
	VeQuaternion kRes;
	kRes.Slerp(a, b, t);
	kRes.Normalise();
	return kRes;
}
//--------------------------------------------------------------------------
const VeQuaternion VeQuaternion::IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);
//--------------------------------------------------------------------------
VeQuaternion::VeQuaternion()
{
	VeZero4f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VeQuaternion::VeQuaternion(VeFloat32 fX, VeFloat32 fY,
	VeFloat32 fZ, VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, fX, fY, fZ, fW);
}
//--------------------------------------------------------------------------
VeQuaternion::VeQuaternion(const VeFloat32* pf32Quat)
{
	VeCopy4f(VE_FLOAT_POINT_THIS, pf32Quat);
}
//--------------------------------------------------------------------------
VeQuaternion::VeQuaternion(const VeQuaternion& kQuat)
{
	VeCopy4f(VE_FLOAT_POINT_THIS, kQuat);
}
//--------------------------------------------------------------------------
VeQuaternion::VeQuaternion(const VeVector3D& kVec, VeFloat32 fW)
{
	VeSet4f(VE_FLOAT_POINT_THIS, kVec.x, kVec.y, kVec.z, fW);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeQuaternion)
{
	Module() [
		Class<VeQuaternion>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32,VeFloat32,VeFloat32,VeFloat32>()).
			Def(Constructor<const VeQuaternion&>()).
			Def(Constructor<const VeVector3D&,VeFloat32>()).
			Def("SetZero", &VeQuaternion::SetZero).
			Def("Set", (void (VeQuaternion::*)(VeFloat32,VeFloat32,VeFloat32,VeFloat32))&VeQuaternion::Set).
			Def("Set", (void (VeQuaternion::*)(const VeVector3D&,VeFloat32))&VeQuaternion::Set).
			Def("FromAngleAxis", &VeQuaternion::FromAngleAxis).
			Def("FromMatrix", &VeQuaternion::FromMatrix).
			Def("Normalise", &VeQuaternion::Normalise).
			Def("Invert", &VeQuaternion::Invert).
			Def("Minimise", &VeQuaternion::Minimise).
			Def("Slerp", &VeQuaternion::Slerp).
			Def("Multiply", &VeQuaternion::Multiply).
			Def("PreMultiply", &VeQuaternion::PreMultiply).
			Def("PostMultiply", &VeQuaternion::PostMultiply).
			Def("DotProduct", &VeQuaternion::DotProduct).
			Def("Length", &VeQuaternion::Length).
			Def("LengthSquared", &VeQuaternion::LengthSquared).
			OpAdd(&OpFuncAdd<VeQuaternion,const VeQuaternion&,const VeQuaternion&>).
			OpSub(&OpFuncSub<VeQuaternion,const VeQuaternion&,const VeQuaternion&>).
			OpMul(&OpFuncMul<VeQuaternion,const VeQuaternion&,const VeQuaternion&>).
			OpUnm(&OpFuncUnm<VeQuaternion,const VeQuaternion&>).
			DefReadWrite("x", &VeQuaternion::x).
			DefReadWrite("y", &VeQuaternion::y).
			DefReadWrite("z", &VeQuaternion::z).
			DefReadWrite("w", &VeQuaternion::w).
			OpToStr(&VeVector4D::ToString) [
				Def("Add", &OpFuncAdd<VeQuaternion,const VeQuaternion&,const VeQuaternion&>),
				Def("Sub", &OpFuncSub<VeQuaternion,const VeQuaternion&,const VeQuaternion&>),
				Def("Mul", &OpFuncMul<VeQuaternion,const VeQuaternion&,const VeQuaternion&>),
				Def("Mul", &OpFuncMul<VeQuaternion,const VeQuaternion&,VeFloat32>),
				Def("Mul", &OpFuncMul<VeQuaternion,VeFloat32,const VeQuaternion&>),
				Def("Mul", &OpFuncMul<VeVector3D,const VeQuaternion&,const VeVector3D&>),
				Def("Div", &OpFuncDiv<VeQuaternion,const VeQuaternion&,VeFloat32>),
				Def("Eq", &OpFuncEq<const VeQuaternion&,const VeQuaternion&>),
				DefRead("IDENTITY", VeQuaternion::IDENTITY)
			],
			Def("VeTLerp", (VeQuaternion (*)(VeFloat32,const VeQuaternion&,const VeQuaternion&))&VeTLerp)
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeQuaternion::ToString(const VeQuaternion& kQuat)
{
	VeSprintf(g_acPrintBuffer, "quat(%.2f,%.2f,%.2f,%.2f)", kQuat.x, kQuat.y, kQuat.z, kQuat.w);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
