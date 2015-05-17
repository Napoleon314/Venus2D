////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAngle.h
//  Version:     v1.00
//  Created:     12/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeAngle : public VeMemObject
{
	VeDeclareLuaExport(VeAngle);
public:
	VeAngle();

	VeAngle(const VeAngle& kAngle);
	
	VeAngle(VeFloat32 f32ValueInRadians);

	VE_INLINE const VeAngle& operator = (VeAngle kAngle);

	VE_INLINE const VeAngle& operator = (VeFloat32 f32ValueInRadians);

	VE_INLINE const VeAngle& operator += (VeAngle kAngle);

	VE_INLINE const VeAngle& operator += (VeFloat32 f32ValueInRadians);

	VE_INLINE const VeAngle& operator -= (VeAngle kAngle);

	VE_INLINE const VeAngle& operator -= (VeFloat32 f32ValueInRadians);

	VE_INLINE VeAngle operator + (VeAngle kAngle) const;

	VE_INLINE VeAngle operator - (VeAngle kAngle) const;

	VE_INLINE VeAngle operator + () const;

	VE_INLINE VeAngle operator - () const;

	VE_INLINE bool operator == (VeAngle kAngle) const;

	VE_INLINE bool operator != (VeAngle kAngle) const;

	VE_INLINE bool operator > (VeAngle kAngle) const;

	VE_INLINE bool operator >= (VeAngle kAngle) const;

	VE_INLINE bool operator < (VeAngle kAngle) const;

	VE_INLINE bool operator <= (VeAngle kAngle) const;

	VE_INLINE operator VeFloat32 () const;

	VE_INLINE VeFloat32 GetAngle() const;

	VE_INLINE static VeFloat32 Normalise(VeFloat32 f32Angle);

	VE_INLINE static VeAngle Decay(VeAngle kSrc, VeAngle kDst, VeFloat32 f32HalfLife, VeFloat32 f32DeltaTime);

	VE_INLINE static VeFloat32 SameSignAngle(VeAngle kAngle, VeAngle kClosest);

	VE_INLINE static VeAngle TurnRange(VeAngle kFrom, VeAngle kTo);

	VE_INLINE bool ClampBetween(VeAngle kMin, VeAngle kMax);

	VE_INLINE bool IsBetween(VeAngle kMin, VeAngle kMax) const;

	VE_INLINE void Lerp(VeAngle a, VeAngle b, VeFloat32 t);

	VE_INLINE void Normalise();

	static const VeChar8* ToString(VeAngle kAngle);

	static const VeAngle ZERO;
	static const VeAngle HALF_CYCLE;

private:
	VeFloat32 m_f32Angle;

};

#ifndef VE_NO_INLINE
#	include "VeAngle.inl"
#endif
