////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLine2D.h
//  Version:     v1.00
//  Created:     18/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeLine2D : public VeMemObject
{
	VeDeclareLuaExport(VeLine2D);
public:
	VeLine2D();

	VeLine2D(const VeVector2D& kNormal, VeFloat32 f32Dist, bool bNormalise = false);

	VeLine2D(const VeVector2D& kVec0, const VeVector2D& kVec1, bool bNormalise = true);

	VE_INLINE void Set(const VeVector2D& kNormal, VeFloat32 f32Dist, bool bNormalise = false);

	VE_INLINE void Set(const VeVector2D& kVec0, const VeVector2D& kVec1, bool bNormalise = true);

	VE_INLINE VeFloat32 Intersect(const VeLine2D& kOther) const;
	
	VE_INLINE VeVector2D Param(VeFloat32 t) const;

	VE_INLINE VeFloat32 Project(const VeVector2D& kPoint) const;

	VE_INLINE bool IsMinCutter(const VeLine2D& kCutter) const;

	VE_INLINE bool IsParallel(const VeLine2D& kOther) const;

	VE_INLINE bool IsInFrontOf(const VeVector2D& kPoint) const;

	VE_INLINE const VeVector2D& GetNormal() const;

	VE_INLINE VeFloat32 GetDistance();

private:
	VeVector2D m_kNormal;
	VeFloat32 m_f32Distance;

};

#ifndef VE_NO_INLINE
#	include "VeLine2D.inl"
#endif
