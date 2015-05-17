////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBoundingBox.inl
//  Version:     v1.00
//  Created:     22/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::operator == (
	const VeBoundingBox2D& kBox) const
{
	return (m_kMin == kBox.m_kMin) && (m_kMax == kBox.m_kMax);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::operator != (
	const VeBoundingBox2D& kBox) const
{
	return (m_kMin != kBox.m_kMin) || (m_kMax != kBox.m_kMax);
}
//--------------------------------------------------------------------------
VE_INLINE VeBoundingBox2D& VeBoundingBox2D::operator = (
	const VeBoundingBox2D& kBox)
{
	m_kMin = kBox.m_kMin;
	m_kMax = kBox.m_kMax;
	return *this;
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector2D& VeBoundingBox2D::MinBounds() const
{
	return m_kMin;
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector2D& VeBoundingBox2D::MaxBounds() const
{
	return m_kMax;
}
//--------------------------------------------------------------------------
VE_INLINE void VeBoundingBox2D::SetBounds(const VeVector2D& kMin,
	const VeVector2D& kMax)
{
	m_kMin = kMin;
	m_kMax = kMax;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeBoundingBox2D::Width() const
{
	return InsideOut() ? 0.0f : m_kMax.x - m_kMin.x;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeBoundingBox2D::Height() const
{
	return InsideOut() ? 0.0f : m_kMax.y - m_kMin.y;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::InsideOut() const
{
	return m_kMin.x > m_kMax.x || m_kMin.y > m_kMax.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeBoundingBox2D::AddBounds(const VeVector2D& kVec)
{
	if(InsideOut())
	{
		m_kMin = kVec;
		m_kMax = kVec;
	}
	else
	{
		m_kMin.x = VE_MIN(m_kMin.x, kVec.x);
		m_kMin.y = VE_MIN(m_kMin.y, kVec.y);
		m_kMax.x = VE_MAX(m_kMax.x, kVec.x);
		m_kMax.y = VE_MAX(m_kMax.y, kVec.y);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeBoundingBox2D::AddBounds(const VeBoundingBox2D& kBox)
{
	if(InsideOut())
	{
		m_kMin = kBox.m_kMin;
		m_kMax = kBox.m_kMax;
	}
	else
	{
		m_kMin.x = VE_MIN(m_kMin.x, kBox.m_kMin.x);
		m_kMin.y = VE_MIN(m_kMin.y, kBox.m_kMin.y);
		m_kMax.x = VE_MAX(m_kMax.x, kBox.m_kMax.x);
		m_kMax.y = VE_MAX(m_kMax.y, kBox.m_kMax.y);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeBoundingBox2D::Combine(const VeBoundingBox2D& kBox0,
	const VeBoundingBox2D& kBox1)
{
	*this = kBox0;
	AddBounds(kBox1);
}
//--------------------------------------------------------------------------
VE_INLINE void VeBoundingBox2D::ExpandSymmetrically(VeFloat32 f32DeltaX,
	VeFloat32 f32DeltaY)
{
	ExpandSymmetrically(VeVector2D(f32DeltaX, f32DeltaY));
}
//--------------------------------------------------------------------------
VE_INLINE void VeBoundingBox2D::ExpandSymmetrically(
	const VeVector2D& kDelta)
{
	if(!InsideOut())
	{
		m_kMin -= kDelta;
		m_kMax += kDelta;
	}
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::Intersects(
	const VeBoundingBox2D& kBox) const
{
	return VE_INTERSECT(m_kMin.x, m_kMax.x, kBox.m_kMin.x, kBox.m_kMax.x)
		&& VE_INTERSECT(m_kMin.y, m_kMax.y, kBox.m_kMin.y, kBox.m_kMax.y);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::Intersects(const VeVector2D& kPos) const
{
	return (kPos.x >= m_kMin.x) && (kPos.y >= m_kMin.y)
		&& (kPos.x < m_kMax.x) && (kPos.y < m_kMax.y);
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::Intersects(
	const VeVector2D& kPos, VeFloat32 f32Bias) const
{
	return (kPos.x >= (m_kMin.x - f32Bias)) && (kPos.y >= (m_kMin.y - f32Bias))
		&& (kPos.x < (m_kMax.x + f32Bias)) && (kPos.y < (m_kMax.y + f32Bias));
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeBoundingBox2D::Centre() const
{
	VE_ASSERT(!InsideOut());
	return (m_kMin + m_kMax) * 0.5f;
}
//--------------------------------------------------------------------------
VE_INLINE VeVector2D VeBoundingBox2D::Extents() const
{
	VE_ASSERT(!InsideOut());
	return 0.5f * (m_kMax - m_kMin);
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeBoundingBox2D::GetPerimeter() const
{
	VE_ASSERT(!InsideOut());
	return 2.0f * ((m_kMax.x - m_kMin.x) + (m_kMax.y - m_kMin.y));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::Contains(const VeBoundingBox2D& kBox) const
{
	bool bRes = true;
	bRes = bRes && m_kMin.x <= kBox.m_kMin.x;
	bRes = bRes && m_kMin.y <= kBox.m_kMin.y;
	bRes = bRes && kBox.m_kMax.x <= m_kMax.x;
	bRes = bRes && kBox.m_kMax.y <= m_kMax.y;
	return bRes;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBoundingBox2D::TestOverlap(const VeBoundingBox2D& kBox0,
	const VeBoundingBox2D& kBox1)
{
	VeVector2D kDist0, kDist1;
	kDist0 = kBox1.m_kMin - kBox0.m_kMax;
	kDist1 = kBox0.m_kMin - kBox1.m_kMax;

	if (kDist0.x > 0.0f || kDist0.y > 0.0f)
		return false;

	if (kDist1.x > 0.0f || kDist1.y > 0.0f)
		return false;

	return true;
}
//--------------------------------------------------------------------------
