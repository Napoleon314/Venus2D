////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBoundingBox.h
//  Version:     v1.00
//  Created:     22/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_INTERSECT(min0,max0,min1,max1) ((min1) <= (max0) && (min0) <= (max1))

class VE_POWER_API VeBoundingBox2D : public VeMemObject
{
	VeDeclareLuaExport(VeBoundingBox2D);
public:
	struct RayCastInput
	{
		VeVector2D m_kVec0, m_kVec1;
		VeFloat32 m_f32MaxFrac;
	};

	struct RayCastOutput
	{
		VeVector2D m_kNormal;
		VeFloat32 m_f32Frac;
	};

	VeBoundingBox2D();

	VeBoundingBox2D(VeFloat32 f32MinX, VeFloat32 f32MinY, VeFloat32 f32MaxX, VeFloat32 f32MaxY);

	VeBoundingBox2D(const VeVector2D& kMin, const VeVector2D& kMax);

	VE_INLINE bool operator == (const VeBoundingBox2D& kBox) const;

	VE_INLINE bool operator != (const VeBoundingBox2D& kBox) const;

	VE_INLINE VeBoundingBox2D& operator = (const VeBoundingBox2D& kBox);

	VE_INLINE const VeVector2D& MinBounds() const;

	VE_INLINE const VeVector2D& MaxBounds() const;

	VE_INLINE void SetBounds(const VeVector2D& kMin, const VeVector2D& kMax);

	VE_INLINE VeFloat32 Width() const;

	VE_INLINE VeFloat32 Height() const;

	VE_INLINE bool InsideOut() const;

	VE_INLINE void AddBounds(const VeVector2D& kVec);

	VE_INLINE void AddBounds(const VeBoundingBox2D& kBox);

	VE_INLINE void Combine(const VeBoundingBox2D& kBox0, const VeBoundingBox2D& kBox1);

	VE_INLINE void ExpandSymmetrically(VeFloat32 f32DeltaX, VeFloat32 f32DeltaY);

	VE_INLINE void ExpandSymmetrically(const VeVector2D& kDelta);

	VE_INLINE bool Intersects(const VeBoundingBox2D& kBox) const;

	VE_INLINE bool Intersects(const VeVector2D& kPos) const;

	VE_INLINE bool Intersects(const VeVector2D& kPos, VeFloat32 f32Bias) const;

	VE_INLINE VeVector2D Centre() const;

	VE_INLINE VeVector2D Extents() const;

	VE_INLINE VeFloat32 GetPerimeter() const;

	VE_INLINE bool Contains(const VeBoundingBox2D& kBox) const;

	static VE_INLINE bool TestOverlap(const VeBoundingBox2D& kBox0, const VeBoundingBox2D& kBox1);

	bool RayCast(RayCastOutput& kOut, const RayCastInput& kIn) const;

	static const VeChar8* ToString(const VeBoundingBox2D& kBox);

	VeVector2D m_kMin;
	VeVector2D m_kMax;

};

#ifndef VE_NO_INLINE
#	include "VeBoundingBox.inl"
#endif
