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
VE_INLINE VeRenderNode* VeSceneManager::GetRootRenderNode()
{
	return &m_kRootNode;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneManager::AddLinkRenderDelegate(
	LinkRenderDelegate& kDelegate)
{
	m_kLinkRenderEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneManager::DelLinkRenderDelegate(
	LinkRenderDelegate& kDelegate)
{
	m_kLinkRenderEvent.DelDelegate(kDelegate);
}
//--------------------------------------------------------------------------
