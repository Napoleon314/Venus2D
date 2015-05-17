////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneManager.h
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeSceneManager : public VeSingleton<VeSceneManager>
{
public:
	typedef VeAbstractDelegate<VeUInt32,VeUInt32> LinkRenderDelegate;

	typedef VeEvent<VeUInt32,VeUInt32> LinkRenderEvent;

	VeSceneManager();

	~VeSceneManager();

	VE_INLINE VeRenderNode* GetRootRenderNode();

	VE_INLINE void AddLinkRenderDelegate(LinkRenderDelegate& kDelegate);

	VE_INLINE void DelLinkRenderDelegate(LinkRenderDelegate& kDelegate);

	void CullScene();

	void LinkRender(VeUInt32 u32CullIndex, VeUInt32 u32MaterialScheme);

protected:
	VeRenderNode m_kRootNode;
	LinkRenderEvent m_kLinkRenderEvent;

};

#define g_pSceneManager VeSceneManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeSceneManager.inl"
#endif
