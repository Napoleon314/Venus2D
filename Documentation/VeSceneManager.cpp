////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneManager.cpp
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeSceneManager.inl"
#endif

//--------------------------------------------------------------------------
VeSceneManager::VeSceneManager() : m_kRootNode(NULL)
{

}
//--------------------------------------------------------------------------
VeSceneManager::~VeSceneManager()
{

}
//--------------------------------------------------------------------------
void VeSceneManager::CullScene()
{

}
//--------------------------------------------------------------------------
void VeSceneManager::LinkRender(VeUInt32 u32CullIndex, VeUInt32 u32MaterialScheme)
{
	m_kLinkRenderEvent.Callback(u32CullIndex, u32MaterialScheme);
}
//--------------------------------------------------------------------------
