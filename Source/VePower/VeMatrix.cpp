////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMatrix.cpp
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
#	include "VeMatrix.inl"
#endif

//--------------------------------------------------------------------------
const VeMatrix VeMatrix::ZERO(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
//--------------------------------------------------------------------------
const VeMatrix VeMatrix::IDENTITY(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
//--------------------------------------------------------------------------
VeMatrix::VeMatrix()
{
	VeZero16f(VE_FLOAT_POINT_THIS);
}
//--------------------------------------------------------------------------
VeMatrix::VeMatrix(const VeFloat32* pf32Matrix)
{
	VeCopy16f(VE_FLOAT_POINT_THIS, pf32Matrix);
}
//--------------------------------------------------------------------------
VeMatrix::VeMatrix(const VeMatrix& kMatrix)
{
	VeCopy16f(VE_FLOAT_POINT_THIS, (const VeFloat32*)&kMatrix);
}
//--------------------------------------------------------------------------
VeMatrix::VeMatrix(
	VeFloat32 _11, VeFloat32 _12, VeFloat32 _13, VeFloat32 _14,
	VeFloat32 _21, VeFloat32 _22, VeFloat32 _23, VeFloat32 _24,
	VeFloat32 _31, VeFloat32 _32, VeFloat32 _33, VeFloat32 _34,
	VeFloat32 _41, VeFloat32 _42, VeFloat32 _43, VeFloat32 _44)
{
	VeSet16f(VE_FLOAT_POINT_THIS
		, _11, _12, _13, _14, _21, _22, _23, _24
		, _31, _32, _33, _34, _41, _42, _43, _44);
}
//--------------------------------------------------------------------------
VeMatrix::VeMatrix(
	const VeVector4D& kRow0, const VeVector4D& kRow1,
	const VeVector4D& kRow2, const VeVector4D& kRow3)
{
	VeCopy4f(VE_FLOAT_POINT_THIS, (const VeFloat32*)&kRow0);
	VeCopy4f(VE_FLOAT_POINT_THIS + 4, (const VeFloat32*)&kRow1);
	VeCopy4f(VE_FLOAT_POINT_THIS + 8, (const VeFloat32*)&kRow2);
	VeCopy4f(VE_FLOAT_POINT_THIS + 12, (const VeFloat32*)&kRow3);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeMatrix)
{
	Module() [
		Class<VeMatrix>().
			Def(Constructor<void>()).
			Def(Constructor<const VeMatrix&>()).
			Def(Constructor<const VeVector4D&,const VeVector4D&,const VeVector4D&,const VeVector4D&>()).
			Def("Row", (const VeVector4D& (VeMatrix::*)(VeUInt32) const)&VeMatrix::Row).
			Def("Row", (void (VeMatrix::*)(VeUInt32, const VeVector4D&))&VeMatrix::Row).
			Def("Col", (VeVector4D (VeMatrix::*)(VeUInt32) const)&VeMatrix::Col).
			Def("Col", (void (VeMatrix::*)(VeUInt32, const VeVector4D&))&VeMatrix::Col).
			Def("SetZero", &VeMatrix::SetZero).
			Def("SetIdentity", &VeMatrix::SetIdentity).
			Def("SetScale", (void (VeMatrix::*)(VeFloat32,VeFloat32,VeFloat32))&VeMatrix::SetScale).
			Def("SetScale", (void (VeMatrix::*)(const VeVector3D&))&VeMatrix::SetScale).
			Def("SetTranslate", (void (VeMatrix::*)(VeFloat32,VeFloat32,VeFloat32))&VeMatrix::SetTranslate).
			Def("SetTranslate", (void (VeMatrix::*)(const VeVector3D&))&VeMatrix::SetTranslate).
			Def("SetRotateX", &VeMatrix::SetRotateX).
			Def("SetRotateY", &VeMatrix::SetRotateY).
			Def("SetRotateZ", &VeMatrix::SetRotateZ).
			Def("SetRotate", (void (VeMatrix::*)(VeFloat32,VeFloat32,VeFloat32))&VeMatrix::SetRotate).
			Def("SetRotate", (void (VeMatrix::*)(const VeQuaternion&))&VeMatrix::SetRotate).
			Def("SetRotateInverse", &VeMatrix::SetRotateInverse).
			Def("Multiply", &VeMatrix::Multiply).
			Def("PreMultiply", &VeMatrix::PreMultiply).
			Def("PostMultiply", &VeMatrix::PostMultiply).
			Def("InvertOrthonormal", (void (VeMatrix::*)(const VeMatrix&))&VeMatrix::InvertOrthonormal).
			Def("InvertOrthonormal", (void (VeMatrix::*)())&VeMatrix::InvertOrthonormal).
			Def("Invert", (bool (VeMatrix::*)(const VeMatrix&))&VeMatrix::Invert).
			Def("Invert", (bool (VeMatrix::*)())&VeMatrix::Invert).
			Def("GetDeterminant", &VeMatrix::GetDeterminant).
			Def("Transpose", (void (VeMatrix::*)(const VeMatrix&))&VeMatrix::Transpose).
			Def("Transpose", (void (VeMatrix::*)())&VeMatrix::Transpose).
			Def("LookAt", &VeMatrix::LookAt).
			Def("ApplyPoint", (VeVector3D (VeMatrix::*)(const VeVector3D&) const)&VeMatrix::ApplyPoint).
			Def("ApplyVector", (VeVector3D (VeMatrix::*)(const VeVector3D&) const)&VeMatrix::ApplyVector).
			Def("ApplyToUnitAxisVector", &VeMatrix::ApplyToUnitAxisVector).
			OpAdd(&OpFuncAdd<VeMatrix,const VeMatrix&,const VeMatrix&>).
			OpSub(&OpFuncSub<VeMatrix,const VeMatrix&,const VeMatrix&>).
			OpMul(&OpFuncMul<VeMatrix,const VeMatrix&,const VeMatrix&>).
			OpUnm(&OpFuncUnm<VeMatrix,const VeMatrix&>).
			DefReadWrite("11", &VeMatrix::_11).
			DefReadWrite("12", &VeMatrix::_12).
			DefReadWrite("13", &VeMatrix::_13).
			DefReadWrite("14", &VeMatrix::_14).
			DefReadWrite("21", &VeMatrix::_21).
			DefReadWrite("22", &VeMatrix::_22).
			DefReadWrite("23", &VeMatrix::_23).
			DefReadWrite("24", &VeMatrix::_24).
			DefReadWrite("31", &VeMatrix::_31).
			DefReadWrite("32", &VeMatrix::_32).
			DefReadWrite("33", &VeMatrix::_33).
			DefReadWrite("34", &VeMatrix::_34).
			DefReadWrite("41", &VeMatrix::_41).
			DefReadWrite("42", &VeMatrix::_42).
			DefReadWrite("43", &VeMatrix::_43).
			DefReadWrite("44", &VeMatrix::_44).
			OpToStr(&VeMatrix::ToString) [
				Def("Add", &OpFuncAdd<VeMatrix,const VeMatrix&,const VeMatrix&>),
				Def("Sub", &OpFuncSub<VeMatrix,const VeMatrix&,const VeMatrix&>),
				Def("Mul", &OpFuncMul<VeMatrix,const VeMatrix&,const VeMatrix&>),
				Def("Mul", &OpFuncMul<VeMatrix,const VeMatrix&,VeFloat32>),
				Def("Mul", &OpFuncMul<VeMatrix,VeFloat32,const VeMatrix&>),
				Def("Div", &OpFuncDiv<VeMatrix,const VeMatrix&,VeFloat32>),
				Def("Eq", &OpFuncEq<const VeMatrix&,const VeMatrix&>),
				DefRead("ZERO", VeMatrix::ZERO),
				DefRead("IDENTITY", VeMatrix::IDENTITY)
			],
			Def("VeTLerp", (VeQuaternion (*)(VeFloat32,const VeQuaternion&,const VeQuaternion&))&VeTLerp)
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeMatrix::ToString(const VeMatrix& kMat)
{
	VeSprintf(g_acPrintBuffer, "\nrow0(%.2f,%.2f,%.2f,%.2f)\nrow1(%.2f,%.2f,%.2f,%.2f)\nrow2(%.2f,%.2f,%.2f,%.2f)\nrow3(%.2f,%.2f,%.2f,%.2f)\n",
		kMat._11, kMat._12, kMat._13, kMat._14,
		kMat._21, kMat._22, kMat._23, kMat._24,
		kMat._31, kMat._32, kMat._33, kMat._34,
		kMat._41, kMat._42, kMat._43, kMat._44);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
