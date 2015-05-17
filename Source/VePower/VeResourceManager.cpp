////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeResourceManager.cpp
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeResourceManager.inl"
#endif

//--------------------------------------------------------------------------
VeResourceManager::VeResourceManager()
{
	m_kDir = VE_DIR("");
	m_kBGQueue[BG_QUEUE_FILE].SetTickOnce(true);
	m_kBGQueue[BG_QUEUE_PROCESS].SetTickOnce(true);
	SetResourceCreateFunction(VeResource::TEXT_TABLE, VeTextTable::CreateResource);
}
//--------------------------------------------------------------------------
VeResourceManager::~VeResourceManager()
{
	m_kGCMap.Clear();
	while(g_pResourceManager->HasTask())
	{
		g_pResourceManager->Update();
	}
	VE_ASSERT(m_kActiveZipMap.Empty());
	VE_ASSERT(m_kLoadTaskList.Empty());
}
//--------------------------------------------------------------------------
void VeResourceManager::AddBGTask(BGQueue eQueue, const VeBackgroundTaskPtr& spTask)
{
	VE_ASSERT(eQueue < BG_QUEUE_NUM);
	m_kBGQueue[eQueue].AddBackgroundTask(spTask);
}
//--------------------------------------------------------------------------
void VeResourceManager::AddFGTask(BGQueue eQueue, const VeBackgroundTaskPtr& spTask)
{
	VE_ASSERT(eQueue < BG_QUEUE_NUM);
	m_kBGQueue[eQueue].AddMainThreadTask(spTask);
}
//--------------------------------------------------------------------------
void VeResourceManager::Update()
{
	for(VeUInt32 i(0); i < BG_QUEUE_NUM; ++i)
	{
		m_kBGQueue[i].Update();
	}
	VeUInt32 u32Count(0);
	for(VeMap<VeResource::Type,VeFloat32>::iterator it = m_kGCMap.Begin();
		it != m_kGCMap.End(); ++it)
	{
		VeRefList<VeResource*>& kList = m_akResourcePools[it->m_tFirst].m_kFreeList;
		while(kList.Size())
		{
			VE_ASSERT(kList.GetHeadNode()->m_tContent);
			VeResource& kRes = *kList.GetHeadNode()->m_tContent;
			if(kRes.GetRefCount() > 1)
			{
				kList.GetHeadNode()->Detach();
			}
			if((VeFloat32(g_pTime->GetTime()) - kRes.m_f32FreeTime) > it->m_tSecond)
			{
				kRes.Unload();
				if((++u32Count) >= VE_MAX_UNLOAD_PER_FRAME)
				{
					return;
				}
			}
			else
			{
				break;
			}
		}
	}
}
//--------------------------------------------------------------------------
VeDirectory* VeResourceManager::CreateDir(const VeChar8* pcName)
{
	VeChar8 acBuffer[VE_MAX_PATH_LEN];
	VeStrcpy(acBuffer, pcName);
	VeChar8* pcContext;
	VeChar8* pcTemp = VeStrtok(acBuffer, "#", &pcContext);
	VeDirectory::Type eType = VeDirectory::TypeLua::ToEnum(pcTemp, VeDirectory::TYPE_NUM);
	VeDirectory* pkDir(NULL);
	switch(eType)
	{
	case VeDirectory::TYPE_FILE:
		{
			pcTemp = VeStrtok(NULL, "#", &pcContext);
			pkDir = VE_NEW VeFileDir(pcTemp ? pcTemp : "");
		}
		break;
	case VeDirectory::TYPE_ZIP:
		{
			pcTemp = VeStrtok(NULL, "#", &pcContext);
			VeZipPtr spZip = g_pResourceManager->GetZip(pcTemp);
			pcTemp = VeStrtok(NULL, "#", &pcContext);
			pkDir = VE_NEW VeZipDir(pcTemp ? pcTemp : "", spZip);
		}
		break;
#	if defined(VE_PLATFORM_ANDROID)
	case VeDirectory::TYPE_ASSET:
		{
			pcTemp = VeStrtok(NULL, "#", &pcContext);
			pkDir = VE_NEW VeAssetDir(pcTemp ? pcTemp : "");
		}
		break;
#	endif
	case VeDirectory::TYPE_URL:
		{
			pcTemp = VeStrtok(NULL, "#", &pcContext);
			pkDir = VE_NEW VeURLDir(pcTemp ? pcTemp : "");
		}
		break;
    default:
        break;
	}
	return pkDir;
}
//--------------------------------------------------------------------------
void VeResourceManager::DestoryDir(VeDirectory* pkDir)
{
	VE_ASSERT(pkDir);
	VE_DELETE(pkDir);
}
//--------------------------------------------------------------------------
VeZipPtr VeResourceManager::GetZip(const VeChar8* pcName, bool bLoad)
{
	VE_AUTO_LOCK_MUTEX(m_kZipMutex);
	VeStringMap<VeZip*>::iterator it = m_kActiveZipMap.Find(pcName);
	if(it)
	{
		return *it;
	}
	else if(!bLoad)
	{
		return NULL;
	}
	else
	{
		VeZipPtr spZip = VeZip::LoadZip(pcName);
		if(spZip)
		{
			m_kActiveZipMap.Insert(pcName, spZip);
		}
		return spZip;
	}
}
//--------------------------------------------------------------------------
bool VeResourceManager::HasTask()
{
	for(VeUInt32 i(0); i < BG_QUEUE_NUM; ++i)
	{
		if(m_kBGQueue[i].HasTask())
		{
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
void VeResourceManager::SetResourceCreateFunction(VeResource::Type eType, ResourceCreateFunc pfuncCreate)
{
	VE_ASSERT(eType < VeResource::TYPE_NUM);
	if(!pfuncCreate)
	{
		for(VeUInt32 i(0); i < m_akResourcePools[eType].m_kVec.Size(); ++i)
		{
			m_akResourcePools[eType].m_kVec[i]->Unload();
		}
		m_akResourcePools[eType].m_kMap.Clear();
		m_akResourcePools[eType].m_kVec.Clear();

	}
	m_akResourcePools[eType].m_pfuncCreateFunc = pfuncCreate;
	
}
//--------------------------------------------------------------------------
#ifdef VE_MEM_DEBUG
VeResourcePtr VeResourceManager::GetResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction)
#else
VeResourcePtr VeResourceManager::GetResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup)
#endif
{
	ResourcePool& kPool = m_akResourcePools[eType];
	VeUInt32* pu32Pos = kPool.m_kMap.Find(pcName);
	if(pu32Pos)
	{
		return kPool.m_kVec[*pu32Pos];
	}
	else if(pcGroup)
	{
		VE_ASSERT(kPool.m_pfuncCreateFunc);
		VeResourcePtr spRes = kPool.m_pfuncCreateFunc(pcName, pcGroup);
		if(spRes)
		{
			kPool.m_kMap.Insert(pcName, kPool.m_kVec.Size());
			kPool.m_kVec.PushBack(spRes);
		}
		return spRes;
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
#ifdef VE_MEM_DEBUG
VeResourcePtr VeResourceManager::LoadResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup, bool bBackground, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction)
#else
VeResourcePtr VeResourceManager::LoadResource(VeResource::Type eType, const VeChar8* pcName, const VeChar8* pcGroup, bool bBackground)
#endif
{
	VeResourcePtr spRes;
#	ifdef VE_MEM_DEBUG
	spRes = GetResource(eType, pcName, pcGroup, pcSourceFile, i32SourceLine, pcFunction);
#	else
	spRes = GetResource(eType, pcName, pcGroup);
#	endif
	if(spRes && spRes->GetState() == VeResource::UNLOADED)
	{
		if(bBackground)
		{
			VE_ASSERT_EQ(spRes->Load(), true);
		}
		else
		{
			VE_ASSERT_EQ(spRes->LoadNow(), true);
		}
	}
	return spRes;
}
//--------------------------------------------------------------------------
#ifdef VE_MEM_DEBUG
void VeResourceManager::LoadResourceTask(const VeVector<LoadInfo>& kInfoList, LoadTaskDelegate& kDelegate, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction)
#else
void VeResourceManager::LoadResourceTask(const VeVector<LoadInfo>& kInfoList, LoadTaskDelegate& kDelegate)
#endif
{
	VE_ASSERT(kInfoList.Size());
	LoadTask* pkTask = VE_NEW LoadTask;
	pkTask->m_kResArray.Reserve(kInfoList.Size());


	for(VeUInt32 i(0); i < kInfoList.Size(); ++i)
	{
		const LoadInfo& kInfo = kInfoList[i];
		VE_ASSERT(kInfo.m_eType < VeResource::TYPE_NUM);
		VE_ASSERT(kInfo.m_kName !="" && kInfo.m_kGroup != "");
#		ifdef VE_MEM_DEBUG
		VeResourcePtr spRes = LoadResource(kInfo.m_eType, kInfo.m_kName, kInfo.m_kGroup, true, pcSourceFile, i32SourceLine, pcFunction);
#		else
		VeResourcePtr spRes = LoadResource(kInfo.m_eType, kInfo.m_kName, kInfo.m_kGroup, true);
#		endif
		if(spRes && spRes->GetState() != VeResource::LOADED)
		{
			pkTask->m_kResArray.PushBack(spRes);
		}
	}
	pkTask->m_u32Pointer = 0;
	pkTask->m_kEvent.AddDelegate(kDelegate);
	if(pkTask->m_kResArray.Size())
		pkTask->m_kResArray.Front()->AddLoadDelegate(pkTask->m_kOnLoadTick);
	else
		g_pResourceManager->AddFGTask(BG_QUEUE_PROCESS, pkTask);
	m_kLoadTaskList.AttachBack(pkTask->m_kNode);
}
//--------------------------------------------------------------------------
void VeResourceManager::CreateGroup(const VeChar8* pcGroup,
	const VeVector<VeString>& kList)
{
	VeResourceGroupPtr spGroup = GetGroup(pcGroup);
	VE_ASSERT(spGroup);
	for(VeVector<VeString>::const_iterator it = kList.Begin();
		it != kList.End(); ++it)
	{
		spGroup->PushReadDirectoryBack(*it);
	}
}
//--------------------------------------------------------------------------
void VeResourceManager::CreateGroup(const VeChar8* pcGroup,
	VeVector<const VeChar8*> kList)
{
	VeResourceGroupPtr spGroup = GetGroup(pcGroup);
	VE_ASSERT(spGroup);
	for(VeVector<const VeChar8*>::iterator it = kList.Begin();
		it != kList.End(); ++it)
	{
		spGroup->PushReadDirectoryBack(*it);
	}
}
//--------------------------------------------------------------------------
VeResourceGroupPtr VeResourceManager::GetGroup(const VeChar8* pcGroup,
	bool bCreate)
{
	VeResourceGroupPtr* pspIter = m_kGroups.Find(pcGroup);
	if(pspIter)
	{
		return *pspIter;
	}
	else if(bCreate)
	{
		return VE_NEW VeResourceGroup(pcGroup);
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
void VeResourceManager::SetFreeListEnable(VeResource::Type eType,
	const VeChar8* pcName, bool bEnable)
{
	ResourcePool& kPool = m_akResourcePools[eType];
	VeUInt32* pu32Pos = kPool.m_kMap.Find(pcName);
	if(pu32Pos)
	{
		kPool.m_kVec[*pu32Pos]->SetFreeListEnable(bEnable);
	}
}
//--------------------------------------------------------------------------
VeResourceManager::ResourceVec& VeResourceManager::GetResourceList(
	VeResource::Type eType)
{
	VE_ASSERT(eType < VeResource::TYPE_NUM);
	return m_akResourcePools[eType].m_kVec;
}
//--------------------------------------------------------------------------
void VeResourceManager::EnableGC(VeResource::Type eType, VeFloat32 f32Time)
{
	m_kGCMap[eType] = f32Time;
}
//--------------------------------------------------------------------------
void VeResourceManager::DisableGC(VeResource::Type eType)
{
	VeMap<VeResource::Type,VeFloat32>::iterator it = m_kGCMap.Find(eType);
	if(it != m_kGCMap.End())
	{
		m_kGCMap.Erase(it);
	}
}
//--------------------------------------------------------------------------
void VeResourceManager::TermRender()
{
	for(VeUInt32 i(0); i < VeResource::TYPE_NUM; ++i)
	{
		ResourceVec& kVec = m_akResourcePools[i].m_kVec;
		for(ResourceVec::iterator it = kVec.Begin(); it != kVec.End(); ++it)
		{
			if(*it) (*it)->TermRender();
		}
	}
}
//--------------------------------------------------------------------------
VeResourceManager::ResourcePool::ResourcePool()
	: m_pfuncCreateFunc(NULL)
{

}
//-------------------------------------------------------------------------
VeResourceManager::LoadTask::LoadTask() : m_u32Pointer(0)
{
	IncRefCount();
	m_kNode.m_tContent = this;
	VeInitDelegate(VeResourceManager::LoadTask, OnLoadTick);
}
//--------------------------------------------------------------------------
void VeResourceManager::LoadTask::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	m_kEvent.Callback(m_kResArray);
	m_kNode.Detach();
	DecRefCount();
}
//-------------------------------------------------------------------------
VeImplLoadResDelegate(VeResourceManager::LoadTask, OnLoadTick, spCurrent)
{
	if((++m_u32Pointer) < m_kResArray.Size())
	{
		m_kResArray[m_u32Pointer]->AddLoadDelegate(VeDelegate(OnLoadTick));
	}
	else
	{
		g_pResourceManager->AddFGTask(BG_QUEUE_PROCESS, this);
	}
}
//--------------------------------------------------------------------------
VeResourceManager::LoadInfo::LoadInfo() : m_eType(VeResource::TYPE_NUM)
{

}
//--------------------------------------------------------------------------
VeResourceManager::LoadInfo::LoadInfo(VeResource::Type eType,
	const VeChar8* pcName) : m_eType(eType), m_kName(pcName)
{
	m_kGroup = g_pResourceManager->GetDefaultGroupName();
}
//--------------------------------------------------------------------------
VeResourceManager::LoadInfo::LoadInfo(VeResource::Type eType,
	const VeChar8* pcName, const VeChar8* pcGroup)
	: m_eType(eType), m_kName(pcName), m_kGroup(pcGroup)
{

}
//--------------------------------------------------------------------------
static void LoadTextTable(const VeChar8* pcName, const VeChar8* pcGroup)
{
	VeLoadResource(VeResource::TEXT_TABLE, pcName, pcGroup, false);
}
//--------------------------------------------------------------------------
static void LoadVertexShader(const VeChar8* pcName, const VeChar8* pcGroup)
{
	VeLoadResource(VeResource::VERTEX_SHADER, pcName, pcGroup, false);
}
//--------------------------------------------------------------------------
static void LoadPixelShader(const VeChar8* pcName, const VeChar8* pcGroup)
{
	VeLoadResource(VeResource::PIXEL_SHADER, pcName, pcGroup, false);
}
//--------------------------------------------------------------------------
static void LoadTexture(const VeChar8* pcName, const VeChar8* pcGroup)
{
	VeLoadResource(VeResource::TEXTURE, pcName, pcGroup, false);
}
//--------------------------------------------------------------------------
static void LoadTextureAtlas(const VeChar8* pcName, const VeChar8* pcGroup)
{
	VeLoadResource(VeResource::TEXTURE_ATLAS, pcName, pcGroup, false);
}
//--------------------------------------------------------------------------
static void LoadRenderFrame(const VeChar8* pcName, const VeChar8* pcGroup)
{
	VeLoadResource(VeResource::RENDER_FRAME, pcName, pcGroup, false);
}
//--------------------------------------------------------------------------
class LuaResLoadEvent_S : public VeRefObject
{
public:
	LuaResLoadEvent_S(lua_State* pkThread, VeInt32 i32Ref, VeVector<VeResourceManager::LoadInfo>& kTaskList);

	VeDeclLoadResTaskDelegate(LuaResLoadEvent_S, OnEvent);
	lua_State* m_pkThread;
	VeInt32 m_i32Ref;
	VeRefNode<VeRefObject*> m_kNode;

};
//--------------------------------------------------------------------------
LuaResLoadEvent_S::LuaResLoadEvent_S(lua_State* pkThread, VeInt32 i32Ref,
	VeVector<VeResourceManager::LoadInfo>& kTaskList)
	: m_pkThread(pkThread), m_i32Ref(i32Ref)
{
	m_kNode.m_tContent = this;
	g_pLua->AddCallbackObj(m_kNode);
	VeInitDelegate(LuaResLoadEvent_S, OnEvent);
	VeLoadResourceTask(kTaskList, VeDelegate(OnEvent));
}
//--------------------------------------------------------------------------
VeImplLoadResTaskDelegate(LuaResLoadEvent_S, OnEvent, kResArray)
{
	VeLuaBind::RetParam(m_pkThread, kResArray.Size());
	VeLuaBind::Resume(m_pkThread, m_i32Ref, g_pLua->GetLua(), 1);
	g_pLua->DelCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
static void Load_S(lua_State* pkState, VeVector<const VeChar8*> kTable)
{
	VeChar8 acBuffer[256];
	VeVector<VeResourceManager::LoadInfo> kTaskList;
	for(VeVector<const VeChar8*>::iterator it = kTable.Begin();
		it != kTable.End(); ++it)
	{
		VeStrcpy(acBuffer, *it);
		VeChar8* pcContent;
		const VeChar8* pcType = VeStrtok(acBuffer, ",", &pcContent);
		const VeChar8* pcPath = VeStrtok(NULL, ",", &pcContent);
		const VeChar8* pcGroup = VeStrtok(NULL, ",", &pcContent);
		pcGroup = pcGroup ? pcGroup : g_pResourceManager->GetDefaultGroupName();
		kTaskList.PushBack(VeResourceManager::LoadInfo(VeResource::TypeLua::ToEnum(pcType, VeResource::TYPE_NUM), pcPath, pcGroup));
	}
	VeInt32 i32Ref = VeLuaBind::Pause(pkState);
	VE_NEW LuaResLoadEvent_S(pkState, i32Ref, kTaskList);
}
//--------------------------------------------------------------------------
class LuaResLoadEvent_A : public VeRefObject
{
public:
	LuaResLoadEvent_A(const VeLuaSyncHolderPtr& spHolder,
		VeVector<VeResourceManager::LoadInfo>& kTaskList);

	VeDeclLoadResTaskDelegate(LuaResLoadEvent_A, OnEvent);
	VeLuaSyncHolderPtr m_spHolder;
	VeRefNode<VeRefObject*> m_kNode;

};
//--------------------------------------------------------------------------
LuaResLoadEvent_A::LuaResLoadEvent_A(const VeLuaSyncHolderPtr& spHolder,
	VeVector<VeResourceManager::LoadInfo>& kTaskList) : m_spHolder(spHolder)
{
	m_kNode.m_tContent = this;
	g_pLua->AddCallbackObj(m_kNode);
	VeInitDelegate(LuaResLoadEvent_A, OnEvent);
	VeLoadResourceTask(kTaskList, VeDelegate(OnEvent));
}
//--------------------------------------------------------------------------
VeImplLoadResTaskDelegate(LuaResLoadEvent_A, OnEvent, kResArray)
{
	m_spHolder->DecRef();
	m_spHolder = NULL;
	g_pLua->DelCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
static VeLuaSyncHolder* Load_A(lua_State* pkState, VeVector<const VeChar8*> kTable)
{
	VeChar8 acBuffer[256];
	VeVector<VeResourceManager::LoadInfo> kTaskList;
	for(VeVector<const VeChar8*>::iterator it = kTable.Begin();
		it != kTable.End(); ++it)
	{
		VeStrcpy(acBuffer, *it);
		VeChar8* pcContent;
		const VeChar8* pcType = VeStrtok(acBuffer, ",", &pcContent);
		const VeChar8* pcPath = VeStrtok(NULL, ",", &pcContent);
		const VeChar8* pcGroup = VeStrtok(NULL, ",", &pcContent);
		pcGroup = pcGroup ? pcGroup : g_pResourceManager->GetDefaultGroupName();
		kTaskList.PushBack(VeResourceManager::LoadInfo(VeResource::TypeLua::ToEnum(pcType, VeResource::TYPE_NUM), pcPath, pcGroup));
	}
	VeLuaSyncHolderPtr spHolder = VE_NEW VeLuaSyncHolder();
	spHolder->IncRef();
	VE_NEW LuaResLoadEvent_A(spHolder, kTaskList);
	return spHolder;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeResourceManager)
{
	Module() [
		Class<VeResourceManager>() [
			DefSingletonFunc("CreateGroup", VeResourceManager::ms_pSingleton, (void (VeResourceManager::*)(const VeChar8*,VeVector<const VeChar8*>))&VeResourceManager::CreateGroup),
			DefSingletonFunc("GetDir", VeResourceManager::ms_pSingleton, &VeResourceManager::GetDir),
			DefSingletonFunc("SetDefaultGroupName", VeResourceManager::ms_pSingleton, &VeResourceManager::SetDefaultGroupName),
			DefSingletonFunc("GetDefaultGroupName", VeResourceManager::ms_pSingleton, &VeResourceManager::GetDefaultGroupName),
			DefSingletonFunc("SetFreeListEnable", VeResourceManager::ms_pSingleton, &VeResourceManager::SetFreeListEnable),
			DefSingletonFunc("EnableGC", VeResourceManager::ms_pSingleton, &VeResourceManager::EnableGC),
			DefSingletonFunc("DisableGC", VeResourceManager::ms_pSingleton, &VeResourceManager::DisableGC),
			Def("Load_S", &Load_S),
			Def("Load_A", &Load_A),
			Def("LoadTextTable", &LoadTextTable),
			Def("LoadVertexShader", &LoadVertexShader),
			Def("LoadPixelShader", &LoadPixelShader),
			Def("LoadTexture", &LoadTexture),
			Def("LoadTextureAtlas", &LoadTextureAtlas),
			Def("LoadRenderFrame", &LoadRenderFrame)
		]
	];
}
//--------------------------------------------------------------------------
