////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLine2D.inl
//  Version:     v1.00
//  Created:     18/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeLine2D::Set(const VeVector2D& kNormal, VeFloat32 f32Dist,
	bool bNormalise)
{
	m_kNormal = kNormal;
	m_f32Distance = f32Dist;
	if(bNormalise) m_kNormal.Normalise();
}
//--------------------------------------------------------------------------
VE_INLINE void VeLine2D::Set(const VeVector2D& kVec0,
	const VeVector2D& kVec1, bool bNormalise)
{
	m_kNormal.x = kVec0.y - kVec1.y;
	m_kNormal.y = kVec1.x - kVec0.x;
	if(bNormalise) m_kNormal.Normalise();
	m_f32Distance = m_kNormal.DotProduct(kVec0);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLine2D::Intersect(const VeLine2D& kOther) const
{
	return (kOther.m_f32Distance - m_f32Distance * kOther.m_kNormal.DotProduct(m_kNormal))
		/ kOther.m_kNormal.CrossProduct(m_kNormal);
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeLine2D::Param(VeFloat32 t) const
{
	return VeVector2D(m_kNormal.x * m_f32Distance + m_kNormal.y * t,
		m_kNormal.y * m_f32Distance - m_kNormal.x * t );
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLine2D::Project(const VeVector2D& kPoint) const
{
	VeVector2D kDir(m_kNormal.y, -m_kNormal.x);
	return kDir.DotProduct(kPoint - m_kNormal * m_f32Distance);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeLine2D::IsMinCutter(const VeLine2D& kCutter) const
{
	return m_kNormal.CrossProduct(kCutter.m_kNormal) > 0.0f;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeLine2D::IsParallel(const VeLine2D& kOther) const
{
	return VeFabsf(m_kNormal.CrossProduct(kOther.m_kNormal)) < 0.001f;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeLine2D::IsInFrontOf(const VeVector2D& kPoint) const
{
	return m_kNormal.DotProduct(kPoint) > m_f32Distance;
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector2D& VeLine2D::GetNormal() const
{
	return m_kNormal;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeLine2D::GetDistance()
{
	return m_f32Distance;
}
//--------------------------------------------------------------------------
