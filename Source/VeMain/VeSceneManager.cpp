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
VeRenderQueueChannel::VeRenderQueueChannel()
	: m_u32CurrentFrame(0)
{

}
//--------------------------------------------------------------------------
VeRenderQueueChannel::~VeRenderQueueChannel()
{

}
//--------------------------------------------------------------------------
void VeRenderQueueChannel::Queue(VeSceneRenderable* pkRenderable, VeUInt32 u32Mask)
{
	VE_ASSERT(pkRenderable);
	if(m_u32CurrentFrame != g_pRenderFrameManager->GetFrameCount())
	{
		m_u32CurrentFrame = g_pRenderFrameManager->GetFrameCount();
		m_kQueue.Clear();
	}
	m_kQueue.PushBack(VePair<VeUInt32,VeSceneRenderable*>(u32Mask, pkRenderable));
}
//--------------------------------------------------------------------------
void VeRenderQueueChannel::Clear()
{
	m_kQueue.Clear();
}
//--------------------------------------------------------------------------
void VeRenderQueueChannel::LinkRenderables(VeUInt32 u32Mask)
{
	if(m_u32CurrentFrame == g_pRenderFrameManager->GetFrameCount())
	{
		VeVector< VePair<VeUInt32,VeSceneRenderable*> >::iterator it = m_kQueue.Begin();
		while(it != m_kQueue.End())
		{
			if(VE_MASK_HAS_ANY(it->m_tFirst, u32Mask))
			{
				VeVector< VePair<VeUInt32,VeSceneRenderable*> >::iterator itCombine = it + 1;
				while(itCombine != m_kQueue.End())
				{
					if((!VE_MASK_HAS_ANY(itCombine->m_tFirst, u32Mask))
						|| (it->m_tSecond)->Combine(itCombine->m_tSecond))
					{
						++itCombine;
					}
					else
					{
						break;
					}
				}
				it->m_tSecond->LinkNodeToParent();
				it = itCombine;
			}
			else
			{
				++it;
			}
		}
	}
	else
	{
		m_u32CurrentFrame = g_pRenderFrameManager->GetFrameCount();
		m_kQueue.Clear();
	}
}
//--------------------------------------------------------------------------
VeRenderQueue::VeRenderQueue()
{

}
//--------------------------------------------------------------------------
VeRenderQueue::~VeRenderQueue()
{

}
//--------------------------------------------------------------------------
void VeRenderQueue::QueueRenderable(VeSceneRenderable* pkRenderable,
	VeUInt32 u32Mask)
{
	VE_ASSERT(pkRenderable);
	VeRenderQueueChannelPtr& spQueue = m_kRenderQueueMap[pkRenderable->GetGroup()];
	if(!spQueue) spQueue = VE_NEW VeRenderQueueChannel();
	spQueue->Queue(pkRenderable, u32Mask);
}
//--------------------------------------------------------------------------
void VeRenderQueue::LinkRenderable(VeUInt32 u32Mask,
	VeUInt16 u16Start, VeUInt16 u16End)
{
	VeMap<VeUInt32,VeRenderQueueChannelPtr>::iterator it = m_kRenderQueueMap.Begin();
	while(it != m_kRenderQueueMap.End())
	{
		if(it->m_tFirst >= u16Start)
		{
			if(it->m_tFirst <= u16End)
			{
				VE_ASSERT(it->m_tSecond);
				it->m_tSecond->LinkRenderables(u32Mask);
			}
			else
			{
				break;
			}
		}
		++it;
	}
}
//--------------------------------------------------------------------------
VeSceneManager::VeSceneManager()
{
	g_pResourceManager->SetResourceCreateFunction(VeResource::DRAGON_BONES,
		VeDragonBones::CreateResource);

	m_pkDraw2DRoot = NULL;
}
//--------------------------------------------------------------------------
VeSceneManager::~VeSceneManager()
{

}
//--------------------------------------------------------------------------
void VeSceneManager::Init()
{
	m_pkDraw2DRoot = VE_NEW VeRenderNode("draw_2d_root");
	m_spRootNode2D = VE_NEW VeSceneNode2D();
	m_spRootNode2D->UpdateContext(m_pkDraw2DRoot);
}
//--------------------------------------------------------------------------
void VeSceneManager::Term()
{
	VE_SAFE_DELETE(m_pkDraw2DRoot);
	m_spRootNode2D = NULL;
}
//--------------------------------------------------------------------------
void VeSceneManager::Update()
{
	VE_ASSERT(m_spRootNode2D);
	m_kActionCallList.BeginIterator();
	while(!m_kActionCallList.IsEnd())
	{
		VeActionCall* pkCall = m_kActionCallList.GetIterNode()->m_tContent;
		m_kActionCallList.Next();
		pkCall->m_kNode.Detach();
		pkCall->m_kEvent.Callback(pkCall);
		pkCall->DecRefCount();
	}
	m_kActionCallList.Clear();
	m_spRootNode2D->Visit(m_kRenderQueue);
}
//--------------------------------------------------------------------------
void VeSceneManager::LinkRenderable(VeRenderNode* pkRoot, VeUInt32 u32Mask,
	VeUInt16 u16Start, VeUInt16 u16End)
{
	m_pkDraw2DRoot->SetParent(pkRoot);
	m_kRenderQueue.LinkRenderable(u32Mask, u16Start, u16End);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSceneManager)
{
	Module() [
		Class<VeSceneManager>() [
			DefSingletonFunc("GetRootNode2D", VeSceneManager::ms_pSingleton, &VeSceneManager::GetRootNode2D),
			DefSingletonFunc("AddSceneNode2D", VeSceneManager::ms_pSingleton, &VeSceneManager::AddSceneNode2D),
			DefSingletonFunc("RemoveAllSceneNode2D", VeSceneManager::ms_pSingleton, &VeSceneManager::RemoveAllSceneNode2D)
		]
	];
}
//--------------------------------------------------------------------------
