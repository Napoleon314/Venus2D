////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTransform.h
//  Version:     v1.00
//  Created:     16/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeTransform2D : public VeMemObject
{
	VeDeclareLuaExport(VeTransform2D);
public:
	union
	{
		struct
		{
			VeFloat32 _11, _12, _21, _22, _31, _32;
		};
		struct
		{
			VeFloat32 a, b, c, d, x, y;
		};
		VeFloat32 m[3][2];
	};

	VeTransform2D();

	VeTransform2D(const VeFloat32* pf32Transform);

	VeTransform2D(const VeTransform2D& kTransform);

	VeTransform2D(VeFloat32 a, VeFloat32 b, VeFloat32 c, VeFloat32 d, VeFloat32 x, VeFloat32 y);

	VeTransform2D(const VeVector2D& kTrans, const VeVector2D& kSkew, const VeVector2D& kScale);

	VE_INLINE operator VeFloat32* ();

	VE_INLINE operator const VeFloat32* () const;

	VE_INLINE VeTransform2D& operator = (const VeTransform2D& kTransform);

	VE_INLINE bool operator == (const VeTransform2D& kTransform) const;

	VE_INLINE bool operator != (const VeTransform2D& kTransform) const;

	VE_INLINE void Set(VeFloat32 a, VeFloat32 b, VeFloat32 c, VeFloat32 d, VeFloat32 x, VeFloat32 y);

	VE_INLINE void Set(const VeVector2D& kTrans, const VeVector2D& kSkew, const VeVector2D& kScale);

	VE_INLINE void Translate(const VeTransform2D& kTransform, VeFloat32 x, VeFloat32 y);

	VE_INLINE void Rotate(const VeTransform2D& kTransform, VeAngle kAngle);

	VE_INLINE void Scale(const VeTransform2D& kTransform, VeFloat32 x, VeFloat32 y);

	VE_INLINE void ApplyPoint(VeVector2D& kOut, const VeVector2D& kIn) const;

	VE_INLINE void ApplyVector(VeVector2D& kOut, const VeVector2D& kIn) const;

	VE_INLINE void ApplyBounding(VeBoundingBox2D& kOut, const VeBoundingBox2D& kIn) const;

	VE_INLINE void Concat(const VeTransform2D& kTrans0, const VeTransform2D& kTrans1);

	VE_INLINE void Invert(const VeTransform2D& kTransform);

	static const VeChar8* ToString(const VeTransform2D& kTrans);

	static const VeTransform2D ZERO;
	static const VeTransform2D IDENTITY;

};

#ifndef VE_NO_INLINE
#	include "VeTransform.inl"
#endif
