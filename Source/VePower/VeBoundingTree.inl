////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBoundingTree.inl
//  Version:     v1.00
//  Created:     29/1/2015 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void* VeBoundingTree2D::GetUserData(VeInt32 proxyId) const
{
	VE_ASSERT(0 <= proxyId && proxyId < m_i32NodeCapacity);
	return m_pkNodes[proxyId].m_pvUserData;
}
//--------------------------------------------------------------------------
VE_INLINE const VeBoundingBox2D& VeBoundingTree2D::GetFatAABB(
	VeInt32 proxyId) const
{
	VE_ASSERT(0 <= proxyId && proxyId < m_i32NodeCapacity);
	return m_pkNodes[proxyId].m_kBox;
}
//--------------------------------------------------------------------------
