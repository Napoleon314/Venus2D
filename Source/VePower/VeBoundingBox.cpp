////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBoundingBox.cpp
//  Version:     v1.00
//  Created:     22/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeBoundingBox.inl"
#endif

//--------------------------------------------------------------------------
VeBoundingBox2D::VeBoundingBox2D() : m_kMin(-VE_MAXFLOAT_F, -VE_MAXFLOAT_F)
	, m_kMax(VE_MAXFLOAT_F, VE_MAXFLOAT_F)
{

}
//--------------------------------------------------------------------------
VeBoundingBox2D::VeBoundingBox2D(VeFloat32 f32MinX, VeFloat32 f32MinY,
	VeFloat32 f32MaxX, VeFloat32 f32MaxY) : m_kMin(f32MinX, f32MinY)
	, m_kMax(f32MaxX, f32MaxY)
{

}
//--------------------------------------------------------------------------
VeBoundingBox2D::VeBoundingBox2D(const VeVector2D& kMin,
	const VeVector2D& kMax)
{
	SetBounds(kMin, kMax);
}
//--------------------------------------------------------------------------
bool VeBoundingBox2D::RayCast(RayCastOutput& kOut,
	const RayCastInput& kIn) const
{
	VeFloat32 tmin = -VE_MAXFLOAT_F;
	VeFloat32 tmax = VE_MAXFLOAT_F;

	VeVector2D p = kIn.m_kVec0;
	VeVector2D d = kIn.m_kVec1 - p;
	VeVector2D absD = VeVector2D(VeFabsf(d.x), VeFabsf(d.y));

	VeVector2D normal;

	for(VeUInt32 i = 0; i < 2; ++i)
	{
		if (absD(i) < VE_MATH_EPSILON_F)
		{
			if (p(i) < m_kMin(i) || m_kMax(i) < p(i))
			{
				return false;
			}
		}
		else
		{
			VeFloat32 inv_d = 1.0f / d(i);
			VeFloat32 t1 = (m_kMin(i) - p(i)) * inv_d;
			VeFloat32 t2 = (m_kMax(i) - p(i)) * inv_d;
			VeFloat32 s = -1.0f;
			if (t1 > t2)
			{
				VeSwap(t1, t2);
				s = 1.0f;
			}
			if (t1 > tmin)
			{
				normal.SetZero();
				normal(i) = s;
				tmin = t1;
			}
			tmax = VE_MIN(tmax, t2);

			if (tmin > tmax)
			{
				return false;
			}
		}
	}

	if (tmin < 0.0f || kIn.m_f32MaxFrac < tmin)
	{
		return false;
	}

	kOut.m_f32Frac = tmin;
	kOut.m_kNormal = normal;
	return true;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeBoundingBox2D)
{
	Module() [
		Class<VeBoundingBox2D>().
			Def(Constructor<void>()).
			Def(Constructor<VeFloat32,VeFloat32,VeFloat32,VeFloat32>()).
			Def(Constructor<const VeVector2D&,const VeVector2D&>()).
			Def("MinBounds", &VeBoundingBox2D::MinBounds).
			Def("MaxBounds", &VeBoundingBox2D::MaxBounds).
			Def("SetBounds", &VeBoundingBox2D::SetBounds).
			Def("Width", &VeBoundingBox2D::Width).
			Def("Height", &VeBoundingBox2D::Height).
			Def("InsideOut", &VeBoundingBox2D::InsideOut).
			Def("AddBounds", (void (VeBoundingBox2D::*)(const VeVector2D&))&VeBoundingBox2D::AddBounds).
			Def("AddBounds", (void (VeBoundingBox2D::*)(const VeBoundingBox2D&))&VeBoundingBox2D::AddBounds).
			Def("ExpandSymmetrically", (void (VeBoundingBox2D::*)(const VeVector2D&))&VeBoundingBox2D::ExpandSymmetrically).
			Def("ExpandSymmetrically", (void (VeBoundingBox2D::*)(VeFloat32,VeFloat32))&VeBoundingBox2D::ExpandSymmetrically).
			Def("Intersects", (bool (VeBoundingBox2D::*)(const VeVector2D&) const)&VeBoundingBox2D::Intersects).
			Def("Intersects", (bool (VeBoundingBox2D::*)(const VeBoundingBox2D&) const)&VeBoundingBox2D::Intersects).
			Def("Intersects", (bool (VeBoundingBox2D::*)(const VeVector2D&,VeFloat32) const)&VeBoundingBox2D::Intersects).
			Def("Centre", &VeBoundingBox2D::Centre).
			OpToStr(&VeBoundingBox2D::ToString) [
				Def("Eq", &OpFuncEq<const VeBoundingBox2D&,const VeBoundingBox2D&>)
			]
	];
}
//--------------------------------------------------------------------------
const VeChar8* VeBoundingBox2D::ToString(const VeBoundingBox2D& kBox)
{
	VeSprintf(g_acPrintBuffer, "box2(%.2f,%.2f,%.2f,%.2f)",
		kBox.MinBounds().x, kBox.MinBounds().y, kBox.MaxBounds().x, kBox.MaxBounds().y);
	return g_acPrintBuffer;
}
//--------------------------------------------------------------------------
