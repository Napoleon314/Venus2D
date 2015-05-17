////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeResource.cpp
//  Version:     v1.00
//  Created:     8/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeResource.inl"
#endif

//--------------------------------------------------------------------------
VeResourceGroup::VeResourceGroup(const VeChar8* pcName)
	: m_kName(pcName), m_pkWriteDirectory(NULL)
{
	g_pResourceManager->m_kGroups[pcName] = this;
}
//--------------------------------------------------------------------------
VeResourceGroup::~VeResourceGroup()
{
	Clear();
}
//--------------------------------------------------------------------------
const VeChar8* VeResourceGroup::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
bool VeResourceGroup::SetWriteDirectory(const VeChar8* pcName)
{
	VeDirectory* pkDir = g_pResourceManager->CreateDir(pcName);
	if(pkDir && pkDir->Access(VeDirectory::ACCESS_W_OK))
	{
		if(m_pkWriteDirectory)
		{
			g_pResourceManager->DestoryDir(m_pkWriteDirectory);
		}
		m_pkWriteDirectory = pkDir;
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
bool VeResourceGroup::PushReadDirectoryBack(const VeChar8* pcName)
{
	VeDirectory* pkDir = g_pResourceManager->CreateDir(pcName);
	if(pkDir)
	{
		m_kReadDirectories.PushBack(pkDir);
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
bool VeResourceGroup::PushReadDirectoryFront(const VeChar8* pcName)
{
	VeDirectory* pkDir = g_pResourceManager->CreateDir(pcName);
	if(pkDir)
	{
		m_kReadDirectories.PushFront(pkDir);
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
void VeResourceGroup::PopBackReadDirectory()
{
	g_pResourceManager->DestoryDir(m_kReadDirectories.Back());
	m_kReadDirectories.PopBack();
}
//--------------------------------------------------------------------------
void VeResourceGroup::PopFrontReadDirectory()
{
	g_pResourceManager->DestoryDir(m_kReadDirectories.Front());
	m_kReadDirectories.PopFront();
}
//--------------------------------------------------------------------------
void VeResourceGroup::Clear()
{
	for(VeList<VeDirectory*>::iterator it = m_kReadDirectories.Begin(); it != m_kReadDirectories.End(); ++it)
	{
		g_pResourceManager->DestoryDir(*it);
	}
	m_kReadDirectories.Clear();
	if(m_pkWriteDirectory)
	{
		g_pResourceManager->DestoryDir(m_pkWriteDirectory);
		m_pkWriteDirectory = NULL;
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeResourceGroup::ReadDirNum()
{
	return m_kReadDirectories.Size();
}
//--------------------------------------------------------------------------
bool VeResourceGroup::CanWrite()
{
	return m_pkWriteDirectory ? true : false;
}
//--------------------------------------------------------------------------
VeImplementRootRTTI(VeResource);
//--------------------------------------------------------------------------
VeResource::VeResource(Type eType, const VeChar8* pcName, const VeChar8* pcGroup)
	: m_eType(eType), m_kName(pcName), m_eState(UNLOADED), m_u32WaitNumber(0)
	, m_f32FreeTime(0)
{
	m_kReadDelegate.Set(this, &VeResource::AsyncReadCallback);
	m_spGroup = g_pResourceManager->m_kGroups[pcGroup];
	if(!m_spGroup)
	{
		m_eState = INVALID;
	}
	m_kFreeNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeResource::~VeResource()
{

}
//--------------------------------------------------------------------------
void VeResource::IncRefCount()
{
	VeRefObject::IncRefCount();
	if(m_eState == LOADED && GetRefCount() == 2)
	{
		m_kFreeNode.Detach();
		m_f32FreeTime = 0;
	}
}
//--------------------------------------------------------------------------
void VeResource::DecRefCount()
{
	if(m_eState == LOADED && GetRefCount() == 2 && m_kFreeNode.m_tContent)
	{
		m_f32FreeTime = (VeFloat32)g_pTime->GetTime();
		g_pResourceManager->m_akResourcePools[GetType()].m_kFreeList.AttachBack(m_kFreeNode);
	}
	VeRefObject::DecRefCount();
}
//--------------------------------------------------------------------------
void VeResource::SetFreeListEnable(bool bEnable)
{
	if(bEnable != IsFreeListEnable())
	{
		if(bEnable)
		{
			m_kFreeNode.m_tContent = this;
			if(m_eState == LOADED && GetRefCount() == 2 && m_kFreeNode.m_tContent)
			{
				m_f32FreeTime = (VeFloat32)g_pTime->GetTime();
				g_pResourceManager->m_akResourcePools[GetType()].m_kFreeList.AttachBack(m_kFreeNode);
			}
		}
		else
		{
			m_kFreeNode.m_tContent = NULL;
			m_kFreeNode.Detach();
			m_f32FreeTime = 0;
		}
	}
}
//--------------------------------------------------------------------------
bool VeResource::LoadNow()
{
	if(m_eState == UNLOADED)
	{
		VE_ASSERT(m_spGroup);
		const VeChar8* pcLoadName = GetLoadName();
		VeDirectory* pcTarget(NULL);
		VeList<VeDirectory*>& kDirList = m_spGroup->m_kReadDirectories;
		for(VeList<VeDirectory*>::iterator it = kDirList.Begin(); it != kDirList.End(); ++it)
		{
			if((*it)->HasFile(pcLoadName))
			{
				pcTarget = *it;
				break;
			}
		}
		if(pcTarget)
		{
			VeBinaryIStreamPtr spStream = pcTarget->OpenSync(pcLoadName);
			if(spStream)
			{
				VeUInt32 u32Len = spStream->RemainingLength();
				VeBlobPtr spBlob = VE_NEW VeBlob(u32Len);
				VE_ASSERT_EQ(spStream->Read(spBlob->GetBuffer(), u32Len), VeInt32(u32Len));
				m_spData = VE_NEW VeMemoryIStream(spBlob);
				if(HasProcess()) LoadProcess(m_spData);
				AfterProcess();
				return true;
			}
		}
		m_eState = INVALID;
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeResource::Load()
{
	if(m_eState == UNLOADED)
	{
		VE_ASSERT(m_spGroup);
		const VeChar8* pcLoadName = GetLoadName();
		VeDirectory* pkTarget(NULL);
		VeList<VeDirectory*>& kDirList = m_spGroup->m_kReadDirectories;
		if(kDirList.Size() > 1)
		{
			for(VeList<VeDirectory*>::iterator it = kDirList.Begin(); it != kDirList.End(); ++it)
			{
				if((*it)->HasFile(pcLoadName))
				{
					pkTarget = *it;
					break;
				}
			}
		}
		else if(kDirList.Size() == 1)
		{
			pkTarget = kDirList.Front();
		}
		if(pkTarget)
		{
			m_eState = LOADING;
			pkTarget->ReadAsync(pcLoadName, m_kReadDelegate);
			return true;
		}
		m_eState = INVALID;
	}
	return false;
}
//--------------------------------------------------------------------------
void VeResource::Unload()
{
	if(m_eState == LOADED)
	{
		UnloadImpl();
		m_kFreeNode.Detach();
		m_f32FreeTime = 0;
		m_eState = UNLOADED;
		VeDebugOutput("Resource[%s] get free", (const VeChar8*)m_kName);
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeResource::GetLoadName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
void VeResource::SetGroup(const VeChar8* pcGroup)
{
	VeResourceGroupPtr* pkIter = g_pResourceManager->m_kGroups.Find(pcGroup);
	if(pkIter)
	{
		m_spGroup = *pkIter;
		if(m_eState == INVALID)
		{
			m_eState = UNLOADED;
		}
	}
}
//--------------------------------------------------------------------------
void VeResource::AsyncReadCallback(const VeMemoryIStreamPtr& spData)
{
	m_spData = spData;
	if(m_spData)
	{
		if(HasProcess())
		{
			g_pResourceManager->AddBGTask(VeResourceManager::BG_QUEUE_PROCESS, this);
		}
		else
		{
			AfterProcess();
		}
	}
	else
	{
		m_eState = INVALID;
	}
}
//--------------------------------------------------------------------------
void VeResource::Wait(VeResource* pkRes)
{
	if(pkRes != this && pkRes->m_eState == LOADING)
	{
		pkRes->m_kTickWaitList.PushBack(this);
		++m_u32WaitNumber;
	}
}
//--------------------------------------------------------------------------
void VeResource::WaitResLoaded(VeResource* pkRes)
{
	--m_u32WaitNumber;
	if(m_u32WaitNumber == 0)
	{
		ProcessEnd();
	}
}
//--------------------------------------------------------------------------
void VeResource::DoBackgroundTask(VeBackgroundTaskQueue& kMgr)
{
	LoadProcess(m_spData);
	kMgr.AddMainThreadTask(this);
}
//--------------------------------------------------------------------------
void VeResource::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	AfterProcess();
}
//--------------------------------------------------------------------------
void VeResource::AfterProcess()
{
	VE_ASSERT(m_spData);
	m_u32WaitNumber = 0;
	State eState = LoadImpl(m_spData);
	m_spData = NULL;
	if(eState == LOADED && m_u32WaitNumber)
	{
		m_eState = LOADING;
	}
	else
	{
		m_eState = eState;
	}
	if(m_eState == LOADED)
	{
		ProcessEnd();
	}
}
//--------------------------------------------------------------------------
void VeResource::ProcessEnd()
{
	m_eState = AllWaitResLoaded();
	if(m_eState == LOADED)
	{
		m_kLoadEvent.Callback(this);
		m_kLoadEvent.Clear();
		for(VeList<VeResource*>::iterator it = m_kTickWaitList.Begin();
			it != m_kTickWaitList.End(); ++it)
		{
			(*it)->WaitResLoaded(this);
		}
		if(m_eState == LOADED && GetRefCount() == 2 && m_kFreeNode.m_tContent)
		{
			m_f32FreeTime = (VeFloat32)g_pTime->GetTime();
			g_pResourceManager->m_akResourcePools[GetType()].m_kFreeList.AttachBack(m_kFreeNode);
		}
		VeDebugOutput("Resource[%s] loaded", (const VeChar8*)m_kName);
	}
}
//--------------------------------------------------------------------------
VeResource::Type VeResource::StrToType(const VeChar8* pcName, Type eDefault)
{
	return TypeLua::ToEnum(pcName, eDefault);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeResource)
{

}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeResource, Type);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeResource, Type)
{
	VeLuaClassEnumBase(VeResource, Type);
	VeLuaClassEnumSlot(VeResource, Type, TEXT_TABLE, "table");
	VeLuaClassEnumSlot(VeResource, Type, VERTEX_SHADER, "vs");
	VeLuaClassEnumSlot(VeResource, Type, PIXEL_SHADER, "ps");
	VeLuaClassEnumSlot(VeResource, Type, TEXTURE, "tex");
	VeLuaClassEnumSlot(VeResource, Type, TEXTURE_ATLAS, "atlas");
	VeLuaClassEnumSlot(VeResource, Type, RENDER_FRAME, "frame");
	VeLuaClassEnumSlot(VeResource, Type, MATERIAL, "mat");
	VeLuaClassEnumSlot(VeResource, Type, DRAGON_BONES, "dbones");
	VeLuaClassEnumSlot(VeResource, Type, FONT, "font");
	VeLuaClassEnumSlot(VeResource, Type, UI_SCENE, "ui");
	VeLuaClassEnumSlot(VeResource, Type, SIMPLE_SOUND, "sound");
}
//--------------------------------------------------------------------------
