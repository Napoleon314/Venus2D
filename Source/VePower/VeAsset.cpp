////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAsset.cpp
//  Version:     v1.00
//  Created:     29/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
#if defined(VE_PLATFORM_ANDROID)
//--------------------------------------------------------------------------
static AAssetManager* s_pkAssetManager = NULL;
//--------------------------------------------------------------------------
void SetAssetManager(AAssetManager* pkManager)
{
	s_pkAssetManager = pkManager;
}
//--------------------------------------------------------------------------
VeAssetIStream::VeAssetIStream(const VeChar8* pcAssetName)
	: m_pkAsset(NULL)
{
	VE_ASSERT(s_pkAssetManager);
	m_pkAsset = AAssetManager_open(s_pkAssetManager, pcAssetName, AASSET_MODE_UNKNOWN);
	VE_ASSERT(m_pkAsset);
}
//--------------------------------------------------------------------------
VeAssetIStream::~VeAssetIStream()
{
	Finish();
}
//--------------------------------------------------------------------------
VeInt32 VeAssetIStream::Read(void* pvBuffer, VeInt32 i32Bytes)
{
	return AAsset_read(m_pkAsset, pvBuffer, i32Bytes);
}
//--------------------------------------------------------------------------
VeInt32 VeAssetIStream::Seek(VeInt32 i32Offset, VeWhence eWhence)
{
	return AAsset_seek(m_pkAsset, i32Offset, eWhence);
}
//--------------------------------------------------------------------------
VeInt32 VeAssetIStream::Tell()
{
	return AAsset_getLength(m_pkAsset) - AAsset_getRemainingLength(m_pkAsset);
}
//--------------------------------------------------------------------------
void* VeAssetIStream::Skip(VeInt32 i32Bytes)
{
	VE_ASSERT(m_pkAsset);
	i32Bytes = VE_MIN(i32Bytes, RemainingLength());
	AAsset_seek(m_pkAsset, i32Bytes, SEEK_CUR);
	return NULL;
}
//--------------------------------------------------------------------------
void VeAssetIStream::Restart()
{
	VE_ASSERT(m_pkAsset);
	AAsset_seek(m_pkAsset, 0, SEEK_SET);
}
//--------------------------------------------------------------------------
VeInt32 VeAssetIStream::RemainingLength() const
{
	VE_ASSERT(m_pkAsset);
	return (VeInt32)AAsset_getRemainingLength(m_pkAsset);
}
//--------------------------------------------------------------------------
VeChar8 VeAssetIStream::Peek()
{
	if(RemainingLength() <= 0)
	{
		SetError(true);
		return -1;
	}

	VeChar8 c8Res(-1);
	VE_ASSERT_EQ(AAsset_read(m_pkAsset, &c8Res, 1), 1);
	AAsset_seek(m_pkAsset, -1, SEEK_CUR);
	return c8Res;
}
//--------------------------------------------------------------------------
void VeAssetIStream::Finish()
{
	if(m_pkAsset)
	{
		AAsset_close(m_pkAsset);
		m_pkAsset = NULL;
	}
}
//--------------------------------------------------------------------------
VeAssetDir::VeAssetDir(const VeChar8* pcName)
	: VeDirectory(pcName)
{
	if(m_kName == ".")
	{
		m_kName = "";
	}
}
//--------------------------------------------------------------------------
VeAssetDir::~VeAssetDir()
{

}
//--------------------------------------------------------------------------
bool VeAssetDir::Access(VeUInt32 u32Flag) const
{
	return !VE_MASK_HAS_ANY(u32Flag, VeDirectory::ACCESS_W_OK);
}
//--------------------------------------------------------------------------
bool VeAssetDir::HasFile(const VeChar8* pcFileName) const
{
	VeString kFilePath;
	if(m_kName.Length())
	{
		kFilePath = m_kName + "/" + pcFileName;
	}
	else
	{
		kFilePath = pcFileName;
	}
	AAsset* pkAsset = AAssetManager_open(s_pkAssetManager, kFilePath, AASSET_MODE_UNKNOWN);
	if(pkAsset)
	{
		AAsset_close(pkAsset);
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
bool VeAssetDir::HasDirectory(const VeChar8* pcDirName) const
{
	VeString kDirPath;
	if(m_kName.Length())
	{
		kDirPath = m_kName + "/" + pcDirName;
	}
	else
	{
		kDirPath = pcDirName;
	}
	AAssetDir* pkDir = AAssetManager_openDir(s_pkAssetManager, kDirPath);
	if(pkDir)
	{
		AAssetDir_close(pkDir);
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
bool VeAssetDir::Change(const VeChar8* pcDirName, bool bCreate)
{
	m_kName += "/";
	m_kName += pcDirName;
	return true;
}
//--------------------------------------------------------------------------
VeDirectory::Type VeAssetDir::GetType() const
{
	return VeDirectory::TYPE_ASSET;
}
//--------------------------------------------------------------------------
VeBinaryIStreamPtr VeAssetDir::OpenSync(const VeChar8* pcFileName) const
{
	VeString kFilePath;
	if(m_kName == "")
	{
		kFilePath = pcFileName;
	}
	else
	{
		kFilePath = m_kName + "/" + pcFileName;
	}
	return VE_NEW VeAssetIStream(kFilePath);
}
//--------------------------------------------------------------------------
void VeAssetDir::ReadAsync(const VeChar8* pcFileName, ReadDelegate& kDelegate) const
{
	VeString kFilePath;
	if(m_kName == "")
	{
		kFilePath = pcFileName;
	}
	else
	{
		kFilePath = m_kName + "/" + pcFileName;
	}
	ReadTask* pkTask = VE_NEW ReadTask(kFilePath, kDelegate);
	g_pResourceManager->AddBGTask(VeResourceManager::BG_QUEUE_FILE, pkTask);
}
//--------------------------------------------------------------------------
void VeAssetDir::WriteAsync(const VeChar8* pcFileName, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, WriteType eType) const
{
	kDelegate.Callback(VE_E_FILE_ACCESS);
}
//--------------------------------------------------------------------------
void VeAssetDir::FindFileList(const VeChar8* pcDesc, VeVector<VeFixedString>& kList)
{
	const VeChar8* pcFile = VeStrrchr(pcDesc, '/');
	pcFile = pcFile ? (pcFile + 1) : pcDesc;
	AAssetDir* pkDir(NULL);
	if(pcFile == pcDesc)
	{
		pkDir = AAssetManager_openDir(s_pkAssetManager, m_kName);
	}
	else
	{
		VeChar8 acPath[256];
		VeStrncpy(acPath, 256, pcDesc, pcFile - pcDesc - 1);
		pkDir = AAssetManager_openDir(s_pkAssetManager, m_kName + "/" + acPath);
	}
	if(pkDir)
	{
		const VeChar8* pcEntry;
		while((pcEntry = AAssetDir_getNextFileName(pkDir)))
		{
			if(VeWildNameMatch(pcEntry, pcFile))
			{
				kList.PushBack(pcEntry);
			}
		}
		AAssetDir_close(pkDir);
	}
}
//--------------------------------------------------------------------------
VeAssetDir::ReadTask::ReadTask(const VeChar8* pcFullPath, ReadDelegate& kDelegate)
	: m_kFileFullPath(pcFullPath)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VeAssetDir::ReadTask::~ReadTask()
{

}
//--------------------------------------------------------------------------
void VeAssetDir::ReadTask::DoBackgroundTask(VeBackgroundTaskQueue& kMgr)
{
	AAsset* pkAsset = AAssetManager_open(s_pkAssetManager, m_kFileFullPath, AASSET_MODE_UNKNOWN);
	if(pkAsset)
	{
		VeInt32 i32Len = (VeInt32)AAsset_getLength(pkAsset);
		if(i32Len)
		{
			VeBlobPtr spBlob = VE_NEW VeBlob(i32Len);
			VeInt32 i32Read = AAsset_read(pkAsset, spBlob->GetBuffer(), i32Len);
			if(i32Read == i32Len)
			{
				m_spData = VE_NEW VeMemoryIStream(spBlob);
			}
		}
		AAsset_close(pkAsset);
	}
	kMgr.AddMainThreadTask(this);
}
//--------------------------------------------------------------------------
void VeAssetDir::ReadTask::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	m_kEvent.Callback(m_spData);
	m_spData = NULL;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
