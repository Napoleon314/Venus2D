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

class VE_MAIN_API VeRenderQueueChannel : public VeRefObject
{
public:
	VeRenderQueueChannel();

	virtual ~VeRenderQueueChannel();

	void Queue(VeSceneRenderable* pkRenderable, VeUInt32 u32Mask);

	void Clear();

	void LinkRenderables(VeUInt32 u32Mask);

protected:
	VeUInt32 m_u32CurrentFrame;
	VeVector< VePair<VeUInt32,VeSceneRenderable*> > m_kQueue;

};

VeSmartPointer(VeRenderQueueChannel);

class VE_MAIN_API VeRenderQueue : public VeMemObject
{
public:
	VeRenderQueue();

	~VeRenderQueue();

	void QueueRenderable(VeSceneRenderable* pkRenderable, VeUInt32 u32Mask);

	void LinkRenderable(VeUInt32 u32Mask, VeUInt16 u16Start, VeUInt16 u16End);

protected:
	VeMap<VeUInt32,VeRenderQueueChannelPtr> m_kRenderQueueMap;

};


class VeAnimation;
class VeActionCall;

class VE_MAIN_API VeSceneManager : public VeSingleton<VeSceneManager>
{
	VeDeclareLuaExport(VeSceneManager);
public:
	enum RenderQueue
	{
		QUEUE_OVERLAYS = 90,
		QUEUE_SPRITES = 92,
		QUEUE_SUPPORT_SHAPES = 97,
		QUEUE_FINALLY = 99,
		QUEUE_MAX = 100
	};

	VeSceneManager();

	~VeSceneManager();

	void Init();

	void Term();

	void Update();

	VE_INLINE const VeSceneNode2DPtr& GetRootNode2D();

	VE_INLINE void AddSceneNode2D(VeSceneNode2D* pkNode);

	VE_INLINE void RemoveAllSceneNode2D();

	void LinkRenderable(VeRenderNode* pkRoot, VeUInt32 u32Mask, VeUInt16 u16Start, VeUInt16 u16End);

protected:
	friend class VeSceneNode2D;
	friend class VeActionCall;	

	VeRenderNode* m_pkDraw2DRoot;
	VeRenderQueue m_kRenderQueue;
	VeSceneNode2DPtr m_spRootNode2D;
	VeRefList<VeActionCall*> m_kActionCallList;

};

#define g_pSceneManager VeSceneManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeSceneManager.inl"
#endif
