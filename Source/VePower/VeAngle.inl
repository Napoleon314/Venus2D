////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAngle.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeAngle& VeAngle::operator = (VeAngle kAngle)
{
	m_f32Angle = kAngle.m_f32Angle;
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE const VeAngle& VeAngle::operator = (VeFloat32 f32ValueInRadians)
{
	m_f32Angle = f32ValueInRadians;
	Normalise();
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE const VeAngle& VeAngle::operator += (VeAngle kAngle)
{
	m_f32Angle = VeNormaliseAnglef(m_f32Angle + kAngle.m_f32Angle);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE const VeAngle& VeAngle::operator += (VeFloat32 f32ValueInRadians)
{
	m_f32Angle = VeNormaliseAnglef(m_f32Angle + f32ValueInRadians);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE const VeAngle& VeAngle::operator -= (VeAngle kAngle)
{
	m_f32Angle = VeNormaliseAnglef(m_f32Angle - kAngle.m_f32Angle);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE const VeAngle& VeAngle::operator -= (VeFloat32 f32ValueInRadians)
{
	m_f32Angle = VeNormaliseAnglef(m_f32Angle - f32ValueInRadians);
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeAngle VeAngle::operator + (VeAngle kAngle) const
{
	return VeAngle(m_f32Angle + kAngle.m_f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE VeAngle VeAngle::operator - (VeAngle kAngle) const
{
	return VeAngle(m_f32Angle - kAngle.m_f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::operator == (VeAngle kAngle) const
{
	return m_f32Angle == kAngle.m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::operator != (VeAngle kAngle) const
{
	return m_f32Angle != kAngle.m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::operator > (VeAngle kAngle) const
{
	return m_f32Angle > kAngle.m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::operator >= (VeAngle kAngle) const
{
	return m_f32Angle >= kAngle.m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::operator < (VeAngle kAngle) const
{
	return m_f32Angle < kAngle.m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::operator <= (VeAngle kAngle) const
{
	return m_f32Angle <= kAngle.m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE VeAngle VeAngle::operator + () const
{
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE VeAngle VeAngle::operator - () const
{
	return VeAngle(-m_f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE VeAngle::operator VeFloat32 () const
{
	return m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeAngle::GetAngle()const
{
	return m_f32Angle;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeAngle::Normalise(VeFloat32 f32Angle)
{
	return VeNormaliseAnglef(f32Angle);
}
//--------------------------------------------------------------------------
VE_INLINE VeAngle VeAngle::Decay(VeAngle kSrc, VeAngle kDst,
	VeFloat32 f32HalfLife, VeFloat32 f32DeltaTime)
{
	VeFloat32 f32Dst = SameSignAngle(kSrc, kDst);
	return VeDecayf(kSrc, f32Dst, f32HalfLife, f32DeltaTime);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeAngle::SameSignAngle(VeAngle kAngle, VeAngle kClosest)
{
	return VeSameSignAnglef(kAngle, kClosest);
}
//--------------------------------------------------------------------------
VE_INLINE VeAngle VeAngle::TurnRange(VeAngle kFrom, VeAngle kTo)
{
	return VeTurnRangeAnglef(kFrom, kTo);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::ClampBetween(VeAngle kMin, VeAngle kMax)
{
	VeFloat32 f32Diff  = TurnRange(kMin, *this);
	VeFloat32 f32Range = TurnRange(kMin, kMax);
	if (f32Diff > f32Range)
	{
		m_f32Angle = (f32Diff - f32Range * 0.5f < VE_MATH_PI_F) ? kMax : kMin;
		Normalise();
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAngle::IsBetween(VeAngle kMin, VeAngle kMax) const
{
	VeFloat32 f32Diff  = TurnRange(kMin, *this);
	VeFloat32 f32Range = TurnRange(kMin, kMax);
	return (f32Diff <= f32Range);
}
//--------------------------------------------------------------------------
VE_INLINE void VeAngle::Lerp(VeAngle a, VeAngle b, VeFloat32 t)
{
	*this = VeLerp(t, (VeFloat32)a, SameSignAngle(a, b));
	Normalise();
}
//--------------------------------------------------------------------------
VE_INLINE void VeAngle::Normalise()
{
	m_f32Angle = VeNormaliseAnglef(m_f32Angle);
}
//--------------------------------------------------------------------------
