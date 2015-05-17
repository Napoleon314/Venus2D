////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneManager.inl
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeSceneNode2DPtr& VeSceneManager::GetRootNode2D()
{
	return m_spRootNode2D;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneManager::AddSceneNode2D(VeSceneNode2D* pkNode)
{
	m_spRootNode2D->AttachChild(pkNode);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneManager::RemoveAllSceneNode2D()
{
	m_spRootNode2D->DetachAllChildren();
}
//--------------------------------------------------------------------------
