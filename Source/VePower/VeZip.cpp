////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeZip.cpp
//  Version:     v1.00
//  Created:     8/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#include <zziplib/lib.h>

//--------------------------------------------------------------------------
VeZip::VeZip(const VeChar8* pcName, ZZIP_DIR* pkZzipRoot)
	: m_kName(pcName), m_pkZzipRoot(pkZzipRoot)
{
	VE_ASSERT(pkZzipRoot);
	ZZIP_DIRENT zzipEntry;
	m_kPathCache.m_kName = m_kName;
	PathInfo* pkCurrentPath(&m_kPathCache);
	VeVector<VeFixedString> kCurrentPath;
	while (zzip_dir_read(m_pkZzipRoot, &zzipEntry))
	{
		const VeChar8* pcFileName = zzipEntry.d_name;
		while(kCurrentPath.Size())
		{
			const VeChar8* pcRes = VeStrstr(pcFileName, kCurrentPath.Back());
			if(pcRes)
			{
				pcFileName = pcRes + kCurrentPath.Back().GetLength();
				break;
			}
			else
			{
				VE_ASSERT(pkCurrentPath->m_pkParent);
				pkCurrentPath = pkCurrentPath->m_pkParent;
				kCurrentPath.PopBack();
			}
		}

		VeUInt32 u32DirNameLen = (VeUInt32)VeStrlen(pcFileName) - 1;

		if(pcFileName[u32DirNameLen] == '/')
		{
			VeString kFileName(pcFileName, u32DirNameLen);
			pkCurrentPath->m_kPathList.PushBack(PathInfo());
			PathInfo& kPath = pkCurrentPath->m_kPathList.Back();
			kPath.m_pkParent = pkCurrentPath;
			kPath.m_kName = kFileName;
			pkCurrentPath->m_kPathNameMap[kFileName] = pkCurrentPath->m_kPathList.Size() - 1;
			pkCurrentPath = &kPath;
			kCurrentPath.PushBack(pcFileName);
			m_kPathMap[kFileName] = pkCurrentPath;
		}
		else
		{
			pkCurrentPath->m_kFileList.PushBack(FileInfo());
			FileInfo& kFile = pkCurrentPath->m_kFileList.Back();
			kFile.m_kName = pcFileName;
			kFile.m_i32CSize = zzipEntry.d_csize;
			kFile.m_i32Size = zzipEntry.st_size;
			pkCurrentPath->m_kFileNameMap[pcFileName] = pkCurrentPath->m_kFileList.Size() - 1;
		}
	}
}
//--------------------------------------------------------------------------
VeZip::~VeZip()
{
	zzip_dir_close(m_pkZzipRoot);
	m_pkZzipRoot = NULL;

	g_pResourceManager->m_kZipMutex.Lock();
	g_pResourceManager->m_kActiveZipMap.Remove(m_kName);
	g_pResourceManager->m_kZipMutex.Unlock();
}
//--------------------------------------------------------------------------
const VeChar8* VeZip::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
ZZIP_DIR* VeZip::GetDirRoot()
{
	return m_pkZzipRoot;
}
//--------------------------------------------------------------------------
VeThread::Mutex& VeZip::GetMutex()
{
	return m_kMutex;
}
//--------------------------------------------------------------------------
VeZipPtr VeZip::LoadZip(const VeChar8* pcName)
{
	zzip_error_t zzipError;
	ZZIP_DIR* pkZzipRoot = zzip_dir_open(pcName, &zzipError);
	if(zzipError == ZZIP_NO_ERROR)
	{
		VE_ASSERT(pkZzipRoot);
		return VE_NEW VeZip(pcName, pkZzipRoot);
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
VeZip::PathInfo::PathInfo() : m_pkParent(NULL)
{

}
//--------------------------------------------------------------------------
VeZip::PathInfo::PathInfo(const PathInfo& kInfo)
{

}
//--------------------------------------------------------------------------
VeZip::PathInfo& VeZip::PathInfo::operator = (PathInfo& stringSrc)
{
	return *this;
}
//--------------------------------------------------------------------------
VeZipDir::VeZipDir(const VeChar8* pcName, const VeZipPtr& spZip)
	: VeDirectory(pcName), m_spZip(spZip), m_pkPath(NULL)
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	VE_ASSERT(m_spZip);
	VeZip::PathMap::iterator it = m_spZip->m_kPathMap.Find(pcName);
	VE_ASSERT(it);
	m_pkPath = *it;
}
//--------------------------------------------------------------------------
VeZipDir::~VeZipDir()
{

}
//--------------------------------------------------------------------------
bool VeZipDir::Access(VeUInt32 u32Flag) const
{
	return !VE_MASK_HAS_ANY(u32Flag, VeDirectory::ACCESS_W_OK);
}
//--------------------------------------------------------------------------
bool VeZipDir::HasFile(const VeChar8* pcFileName) const
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	return m_pkPath->m_kFileNameMap.Find(pcFileName) != NULL;
}
//--------------------------------------------------------------------------
bool VeZipDir::HasDirectory(const VeChar8* pcDirName) const
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	return m_pkPath->m_kPathNameMap.Find(pcDirName) != NULL;
}
//--------------------------------------------------------------------------
bool VeZipDir::Change(const VeChar8* pcDirName, bool bCreate)
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	VeString kPath = pcDirName;
	kPath += "/";
	VeStringMap<VeUInt32>::iterator it = m_pkPath->m_kPathNameMap.Find(kPath);
	if(it)
	{
		VE_ASSERT((*it) < m_pkPath->m_kPathList.Size());
		m_pkPath = &(m_pkPath->m_kPathList[*it]);
		m_kName += "/";
		m_kName += kPath;
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
VeDirectory::Type VeZipDir::GetType() const
{
	return TYPE_ZIP;
}
//--------------------------------------------------------------------------
VeBinaryIStreamPtr VeZipDir::OpenSync(const VeChar8* pcFileName) const
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	VeStringMap<VeUInt32>::iterator it = m_pkPath->m_kFileNameMap.Find(pcFileName);
	if(it)
	{
		VE_ASSERT((*it) < m_pkPath->m_kFileList.Size());
		VeZip::FileInfo& kFile = m_pkPath->m_kFileList[*it];
		VeString kFullPath = m_kName + "/" + pcFileName;
		ZZIP_FILE* pkZipFile = zzip_file_open(m_spZip->GetDirRoot(), kFullPath, ZZIP_NOPATHS);
		return VE_NEW VeZipFileIStream(kFullPath, m_spZip, pkZipFile, kFile.m_i32Size);
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
void VeZipDir::ReadAsync(const VeChar8* pcFileName, ReadDelegate& kDelegate) const
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	VeStringMap<VeUInt32>::iterator it = m_pkPath->m_kFileNameMap.Find(pcFileName);
	if(it)
	{
		VE_ASSERT((*it) < m_pkPath->m_kFileList.Size());
		VeZip::FileInfo& kFile = m_pkPath->m_kFileList[*it];
		VeString kFullPath = m_kName + "/" + pcFileName;
		ReadTask* pkTask = VE_NEW ReadTask(kFullPath, kDelegate, m_spZip, kFile.m_i32Size);
		g_pResourceManager->AddBGTask(VeResourceManager::BG_QUEUE_FILE, pkTask);
	}
	else
	{
		kDelegate.Callback(NULL);
	}
}
//--------------------------------------------------------------------------
void VeZipDir::WriteAsync(const VeChar8* pcFileName, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, WriteType eType) const
{
	kDelegate.Callback(VE_E_FILE_ACCESS);
}
//--------------------------------------------------------------------------
VeZipFileIStream::VeZipFileIStream(const VeChar8* pcFileName, const VeZipPtr& spZip, ZZIP_FILE* pkZipFile, VeInt32 i32Size)
	: m_spZip(spZip), m_pkZzipFile(pkZipFile), m_i32RemainingLength(i32Size), m_i32Size(i32Size)
{
	VE_ASSERT(m_spZip && m_pkZzipFile);
}
//--------------------------------------------------------------------------
VeZipFileIStream::~VeZipFileIStream()
{
	VE_ASSERT(!m_spZip);
}
//--------------------------------------------------------------------------
VeInt32 VeZipFileIStream::Read(void* pvBuffer, VeInt32 i32Bytes)
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	VE_ASSERT(i32Bytes > 0 && m_i32RemainingLength);
	VeInt32 i32Read = (VeInt32)zzip_file_read(m_pkZzipFile, pvBuffer, i32Bytes);
	if(i32Read >= 0)
	{
		m_i32RemainingLength -= i32Read;
		return i32Read;
	}
	else
	{
		SetError(true);
		return 0;
	}
}
//--------------------------------------------------------------------------
VeInt32 VeZipFileIStream::Seek(VeInt32 i32Offset, VeWhence eWhence)
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	switch(eWhence)
	{
	case VE_SEEK_SET:
		if(i32Offset >= 0 && i32Offset <= m_i32Size)
		{
			zzip_seek(m_pkZzipFile, i32Offset, SEEK_SET);
			m_i32RemainingLength = m_i32Size - i32Offset;
			return VE_S_OK;
		}
		break;
	case VE_SEEK_CUR:
		{
			VeInt32 i32After = (m_i32Size - m_i32RemainingLength) + i32Offset;
			if(i32After >= 0 && i32After <= m_i32Size)
			{
				zzip_seek(m_pkZzipFile, i32Offset, SEEK_CUR);
				m_i32RemainingLength = m_i32Size - i32After;
				return VE_S_OK;
			}
		}
		break;
	case VE_SEEK_END:
		if(i32Offset >= 0 && i32Offset <= m_i32Size)
		{
			zzip_seek(m_pkZzipFile, i32Offset, SEEK_END);
			m_i32RemainingLength = i32Offset;
			return VE_S_OK;
		}
		break;
	default:
		break;
	}
	return VE_E_FAIL;
}
//--------------------------------------------------------------------------
VeInt32 VeZipFileIStream::Tell()
{
	return m_i32Size - m_i32RemainingLength;
}
//--------------------------------------------------------------------------
void* VeZipFileIStream::Skip(VeInt32 i32Bytes)
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	VeInt32 i32Skip = VE_MIN(m_i32RemainingLength, i32Bytes);
	if(i32Skip >= 0)
	{
		zzip_seek(m_pkZzipFile, i32Skip, SEEK_CUR);
		m_i32RemainingLength -= i32Skip;
	}
	return NULL;
}
//--------------------------------------------------------------------------
void VeZipFileIStream::Restart()
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	zzip_seek(m_pkZzipFile, 0, SEEK_SET);
	m_i32RemainingLength = m_i32Size;
}
//--------------------------------------------------------------------------
VeInt32 VeZipFileIStream::RemainingLength() const
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	return m_i32RemainingLength;
}
//--------------------------------------------------------------------------
VeChar8 VeZipFileIStream::Peek()
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	if(m_i32RemainingLength <= 0)
	{
		SetError(true);
		return -1;
	}

	VeChar8 c8Res(-1);
	VE_ASSERT_EQ(zzip_file_read(m_pkZzipFile, &c8Res, 1), 1);
	zzip_seek(m_pkZzipFile, -1, SEEK_CUR);
	return c8Res;
}
//--------------------------------------------------------------------------
void VeZipFileIStream::Finish()
{
	if(m_spZip)
	{
		VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
		zzip_file_close(m_pkZzipFile);
		m_pkZzipFile = NULL;
		m_i32RemainingLength = 0;
	}
	m_spZip = NULL;
}
//--------------------------------------------------------------------------
VeZipDir::ReadTask::ReadTask(const VeChar8* pcFullPath, ReadDelegate& kDelegate, const VeZipPtr& spZip, VeInt32 i32Size)
	: m_kFileFullPath(pcFullPath), m_spZip(spZip), m_i32Size(i32Size)
{
	VE_ASSERT(m_spZip);
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VeZipDir::ReadTask::~ReadTask()
{

}
//--------------------------------------------------------------------------
void VeZipDir::ReadTask::DoBackgroundTask(VeBackgroundTaskQueue& kMgr)
{
	VE_AUTO_LOCK_MUTEX_NAME(m_spZip->GetMutex(), kZipMutex);
	ZZIP_FILE* pkZipFile = zzip_file_open(m_spZip->GetDirRoot(), m_kFileFullPath, ZZIP_NOPATHS);
	if(pkZipFile)
	{
		VeBlobPtr spBlob = VE_NEW VeBlob(m_i32Size);
		VeInt32 i32Read = (VeInt32)zzip_file_read(pkZipFile, spBlob->GetBuffer(), m_i32Size);
		zzip_file_close(pkZipFile);
		if(i32Read == m_i32Size)
		{
			m_spData = VE_NEW VeMemoryIStream(spBlob);
		}
	}
	kMgr.AddMainThreadTask(this);
}
//--------------------------------------------------------------------------
void VeZipDir::ReadTask::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	m_kEvent.Callback(m_spData);
	m_spData = NULL;
	m_spZip = NULL;
}
//--------------------------------------------------------------------------
