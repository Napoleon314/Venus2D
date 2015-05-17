////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeResourceManager.h
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_MAX_UNLOAD_PER_FRAME (5)

class VE_POWER_API VeResourceManager : public VeSingleton<VeResourceManager>
{
	VeDeclareLuaExport(VeResourceManager);
public:
	enum BGQueue
	{
		BG_QUEUE_FILE,
		BG_QUEUE_PROCESS,
		BG_QUEUE_EVENT,
		BG_QUEUE_NUM
	};

	struct VE_POWER_API LoadInfo
	{
		LoadInfo();

		LoadInfo(VeResource::Type eType, const VeChar8* pcName);

		LoadInfo(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup);

		VeResource::Type m_eType;
		VeFixedString m_kName;
		VeFixedString m_kGroup;
	};

	typedef VeStringMap<VeUInt32> ResourceMap;
	typedef VeVector<VeResourcePtr> ResourceVec;

	typedef VeEvent<const ResourceVec&> LoadTaskEvent;
	typedef VeAbstractDelegate<const ResourceVec&> LoadTaskDelegate;

	typedef VeResource* (*ResourceCreateFunc)(const VeChar8* pcName, const VeChar8* pcGroup);

	struct LoadTask : public VeBackgroundTask
	{
		LoadTask();

		virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

		VeRefNode<LoadTask*> m_kNode;
		VeUInt32 m_u32Pointer;
		ResourceVec m_kResArray;
		LoadTaskEvent m_kEvent;
		VeDeclLoadResDelegate(VeResourceManager::LoadTask, OnLoadTick);
	};

	VeResourceManager();

	~VeResourceManager();

	VE_INLINE const VeChar8* GetDir();

	VE_INLINE void SetDefaultGroupName(const VeChar8* pcGroup);

	VE_INLINE const VeChar8* GetDefaultGroupName();

	void SetResourceCreateFunction(VeResource::Type eType, ResourceCreateFunc pfuncCreate);

#ifdef VE_MEM_DEBUG
	VeResourcePtr GetResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);
#else
	VeResourcePtr GetResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup);
#endif

#ifdef VE_MEM_DEBUG
	VeResourcePtr LoadResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup, bool bBackground, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);
#else
	VeResourcePtr LoadResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup, bool bBackground);
#endif

#ifdef VE_MEM_DEBUG
	void LoadResourceTask(const VeVector<LoadInfo>& kInfoList, LoadTaskDelegate& kDelegate, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);
#else
	void LoadResourceTask(const VeVector<LoadInfo>& kInfoList, LoadTaskDelegate& kDelegate);
#endif

	void CreateGroup(const VeChar8* pcGroup, const VeVector<VeString>& kList);

	void CreateGroup(const VeChar8* pcGroup, VeVector<const VeChar8*> kList);

	VeResourceGroupPtr GetGroup(const VeChar8* pcGroup, bool bCreate = true);

	void SetFreeListEnable(VeResource::Type eType, const VeChar8* pcName, bool bEnable);

	void EnableGC(VeResource::Type eType, VeFloat32 f32Time);

	void DisableGC(VeResource::Type eType);

	void AddBGTask(BGQueue eQueue, const VeBackgroundTaskPtr& spTask);

	void AddFGTask(BGQueue eQueue, const VeBackgroundTaskPtr& spTask);

	void Update();

	VeDirectory* CreateDir(const VeChar8* pcName);

	void DestoryDir(VeDirectory* pkDir);

	VeZipPtr GetZip(const VeChar8* pcName, bool bLoad = true);

	bool HasTask();

	ResourceVec& GetResourceList(VeResource::Type eType);

	void TermRender();

protected:
	friend class VeResourceGroup;
	friend class VeResource;
	friend class VeZip;
	friend class VeURL;

	VeStringMap<VeResourceGroupPtr> m_kGroups;
	struct ResourcePool
	{
		ResourcePool();
		ResourceMap m_kMap;
		ResourceVec m_kVec;
		ResourceCreateFunc m_pfuncCreateFunc;
		VeRefList<VeResource*> m_kFreeList;
	} m_akResourcePools[VeResource::TYPE_NUM];

	VeMap<VeResource::Type,VeFloat32> m_kGCMap;
	
	VeString m_kDir;
	VeStringMap<VeZip*> m_kActiveZipMap;
	VeThread::Mutex m_kZipMutex;
	VeBackgroundTaskQueue m_kBGQueue[BG_QUEUE_NUM];
	VeFixedString m_kDefaultGroupName;

	VeRefList<LoadTask*> m_kLoadTaskList;

};

#define g_pResourceManager VeResourceManager::GetSingletonPtr()

#ifdef VE_MEM_DEBUG

#define VeGetResource(type,name,group) (g_pResourceManager->GetResource(type,name,group,__FILE__, __LINE__, __FUNCTION__))

#define VeLoadResource(type,name,group,async) (g_pResourceManager->LoadResource(type,name,group,async,__FILE__, __LINE__, __FUNCTION__))

#define VeLoadResourceTask(info,dele) (g_pResourceManager->LoadResourceTask(info,dele,__FILE__, __LINE__, __FUNCTION__))

#define VeLoadResourceSync(type,name,group) VeLoadResource(type,name,group,false)

#define VeLoadResourceAsync(type,name,group) VeLoadResource(type,name,group,true)

#else

#define VeGetResource(type,name,group) (g_pResourceManager->GetResource(type,name,group))

#define VeLoadResource(type,name,group,async) (g_pResourceManager->LoadResource(type,name,group,async))

#define VeLoadResourceTask(info,dele) (g_pResourceManager->LoadResourceTask(info,dele))

#define VeLoadResourceSync(type,name,group) VeLoadResource(type,name,group,false)

#define VeLoadResourceAsync(type,name,group) VeLoadResource(type,name,group,true)

#endif

#define VeDeclLoadResTaskDelegate(class,name) \
	void name(const VeResourceManager::ResourceVec&); \
	VeMemberDelegate<class,const VeResourceManager::ResourceVec&> m_k##name

#define VeImplLoadResTaskDelegate(class,name,vec) \
	void class::name(const VeResourceManager::ResourceVec& vec)

#ifndef VE_NO_INLINE
#	include "VeResourceManager.inl"
#endif
