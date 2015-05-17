////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLine2D.cpp
//  Version:     v1.00
//  Created:     18/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeLine2D.inl"
#endif

//--------------------------------------------------------------------------
VeLine2D::VeLine2D() : m_f32Distance(0)
{
	Set(VeVector2D::UNIT_X, 0);
}
//--------------------------------------------------------------------------
VeLine2D::VeLine2D(const VeVector2D& kNormal, VeFloat32 f32Dist,
	bool bNormalise) : m_kNormal(kNormal), m_f32Distance(f32Dist)
{
	Set(kNormal, f32Dist, bNormalise);
}
//--------------------------------------------------------------------------
VeLine2D::VeLine2D(const VeVector2D& kVec0, const VeVector2D& kVec1,
	bool bNormalise)
{
	Set(kVec0, kVec1, bNormalise);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeLine2D)
{
	Module() [
		Class<VeLine2D>().
			Def(Constructor<void>()).
			Def(Constructor<const VeVector2D&,VeFloat32,bool>()).
			Def(Constructor<const VeVector2D&,const VeVector2D&,bool>()).
			Def("Set", (void (VeLine2D::*)(const VeVector2D&,VeFloat32,bool))&VeLine2D::Set).
			Def("Set", (void (VeLine2D::*)(const VeVector2D&,const VeVector2D&,bool))&VeLine2D::Set).
			Def("Intersect", &VeLine2D::Intersect).
			Def("Param", &VeLine2D::Param).
			Def("Project", &VeLine2D::Project).
			Def("IsMinCutter", &VeLine2D::IsMinCutter).
			Def("IsParallel", &VeLine2D::IsParallel).
			Def("IsInFrontOf", &VeLine2D::IsInFrontOf).
			Def("GetNormal", &VeLine2D::GetNormal).
			Def("GetDistance", &VeLine2D::GetDistance)
	];
}
//--------------------------------------------------------------------------
