////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeFile.cpp
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
VeFileIStream::VeFileIStream(const VeChar8* pcFileName, VeInt32 i32Cache)
	: m_pkFile(NULL), m_pbyCache(NULL), m_i32FileSize(0), m_i32CacheSize(i32Cache)
	, m_i32Pointer(0), m_i32CachePointer(0), m_i32CacheUse(0)
{
	if(VE_SUCCEEDED(VeAccess(pcFileName, VeDirectory::ACCESS_F_OK)))
	{
#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
		fopen_s(&m_pkFile, pcFileName, "rb");
#else
		m_pkFile = fopen(pcFileName, "rb");
#endif
		if(m_pkFile)
		{
			UpdateLenth();
			VE_ASSERT(m_i32CacheSize > 0);
			m_pbyCache = VeAlloc(VeByte, m_i32CacheSize);
			VE_ASSERT(m_pbyCache);
			return;
		}
	}
	SetError(true);
}
//--------------------------------------------------------------------------
VeFileIStream::~VeFileIStream()
{
	Finish();
}
//--------------------------------------------------------------------------
VeInt32 VeFileIStream::Read(void* pvBuffer, VeInt32 i32Bytes)
{
	if(i32Bytes)
	{
		VE_ASSERT(pvBuffer && (i32Bytes > 0));
		VeInt32 i32Cached = Cached();
		VeInt32 i32Res(0);
		{
			VeInt32 i32Space = m_i32Pointer < m_i32FileSize ? m_i32FileSize - m_i32Pointer : 0;
			i32Bytes = (i32Space >= i32Bytes) ? i32Bytes : i32Space;
		}
		while(i32Bytes)
		{
			if(i32Cached <= 0)
			{
				CacheReload();
				i32Cached = m_i32CacheUse;
			}
			if(i32Bytes <= i32Cached)
			{
				VeCrazyCopy((VeChar8*)pvBuffer + i32Res, (VeChar8*)m_pbyCache + m_i32Pointer - m_i32CachePointer, i32Bytes);
				i32Res += i32Bytes;
				m_i32Pointer += i32Bytes;
				i32Bytes = 0;
				break;
			}
			else
			{
				VeCrazyCopy((VeChar8*)pvBuffer + i32Res, (VeChar8*)m_pbyCache + m_i32Pointer - m_i32CachePointer, i32Cached);
				i32Res += i32Cached;
				m_i32Pointer += i32Cached;
				i32Bytes -= i32Cached;
				i32Cached = 0;
			}
		}
		return i32Res;
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------------------------------
VeInt32 VeFileIStream::Seek(VeInt32 i32Offset, VeWhence eWhence)
{
	switch(eWhence)
	{
	case VE_SEEK_SET:
		if(i32Offset >= 0 && i32Offset <= m_i32FileSize)
		{
			m_i32Pointer = i32Offset;
			return VE_S_OK;
		}
		break;
	case SEEK_CUR:
		{
			VeInt32 i32After = m_i32Pointer + i32Offset;
			if(i32After >= 0 && i32After <= m_i32FileSize)
			{
				m_i32Pointer = i32After;
				return VE_S_OK;
			}
		}
		break;
	case SEEK_END:
		if(i32Offset >= 0 && i32Offset <= m_i32FileSize)
		{
			m_i32Pointer = m_i32FileSize - i32Offset;
			return VE_S_OK;
		}
		break;
	default:
		break;
	}
	return VE_E_FAIL;
}
//--------------------------------------------------------------------------
VeInt32 VeFileIStream::Tell()
{
	return m_i32Pointer;
}
//--------------------------------------------------------------------------
void* VeFileIStream::Skip(VeInt32 i32Bytes)
{
	VeInt32 i32Skip = VE_MIN(i32Bytes, RemainingLength());
	m_i32Pointer += i32Skip;
	return NULL;
}
//--------------------------------------------------------------------------
void VeFileIStream::Restart()
{
	m_i32Pointer = 0;
}
//--------------------------------------------------------------------------
VeInt32 VeFileIStream::RemainingLength() const
{
	return m_i32FileSize - m_i32Pointer;
}
//--------------------------------------------------------------------------
VeChar8 VeFileIStream::Peek()
{
	if(m_i32Pointer >= m_i32FileSize)
	{
		m_bError = true;
		return -1;
	}

	if(!Cached())
	{
		CacheReload();
	}

	return *((VeChar8*)m_pbyCache + m_i32Pointer - m_i32CachePointer);
}
//--------------------------------------------------------------------------
void VeFileIStream::Finish()
{
	m_i32Pointer = m_i32FileSize;
	if(m_pkFile)
	{
		fclose(m_pkFile);
		m_pkFile = NULL;
	}
	if(m_pbyCache)
	{
		VeFree(m_pbyCache);
		m_pbyCache = NULL;
	}
}
//--------------------------------------------------------------------------
void VeFileIStream::CacheReload()
{
	fseek(m_pkFile, m_i32Pointer, SEEK_SET);
	m_i32CacheUse = (VeInt32)fread(m_pbyCache, 1, m_i32CacheSize, m_pkFile);
	m_i32CachePointer = m_i32Pointer;
}
//--------------------------------------------------------------------------
void VeFileIStream::UpdateLenth()
{
	fseek(m_pkFile, 0, SEEK_END);
	m_i32FileSize = (VeInt32)ftell(m_pkFile);
}
//--------------------------------------------------------------------------
bool VeFileIStream::IsCached()
{
	return (m_i32Pointer >= m_i32CachePointer) && (m_i32Pointer < (m_i32CachePointer + m_i32CacheUse));
}
//--------------------------------------------------------------------------
VeInt32 VeFileIStream::Cached()
{
	return IsCached() ? VeInt32(m_i32CacheUse + m_i32CachePointer - m_i32Pointer) : 0;
}
//--------------------------------------------------------------------------
VeFileOStream::VeFileOStream(const VeChar8* pcFileName, VeInt32 i32Cache, VeDirectory::WriteType eType)
	: m_pkFile(NULL), m_pbyCache(NULL), m_i32FileSize(0), m_i32CacheSize(i32Cache), m_i32CachePointer(0)
{
	const VeChar8* pcMode = (eType == VeDirectory::WRITE_CREATE_COVER) ? "wb" : "ab";
#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
	fopen_s(&m_pkFile, pcFileName, pcMode);
#else
	m_pkFile = fopen(pcFileName, pcMode);
#endif

	VE_ASSERT(m_pkFile);
	VE_ASSERT(m_i32CacheSize > 0);
	m_pbyCache = VeAlloc(VeByte, m_i32CacheSize);
	VE_ASSERT(m_pbyCache);
}
//--------------------------------------------------------------------------
VeFileOStream::~VeFileOStream()
{
	if(m_pkFile)
	{
		WriteBackCache();
		fclose(m_pkFile);
		m_pkFile = NULL;
	}
	if(m_pbyCache)
	{
		VeFree(m_pbyCache);
		m_pbyCache = NULL;
	}
}
//--------------------------------------------------------------------------
VeInt32 VeFileOStream::Write(const void* pvBuffer, VeInt32 i32Bytes)
{
	VE_ASSERT(pvBuffer && (i32Bytes > 0));
	const VeInt32 i32Res = i32Bytes;
	const VeChar8* pcBuffer = (const VeChar8*)pvBuffer;
	if(HasCacheUse())
	{
		VeInt32 i32Cache = VE_MIN(CacheCanUse(), i32Bytes);
		VeCrazyCopy(Cache(), pcBuffer, i32Cache);
		pcBuffer += i32Cache;
		m_i32FileSize += i32Cache;
		i32Bytes -= i32Cache;
		WriteBackCache();
	}
	if(i32Bytes >= m_i32CacheSize)
	{
		fwrite(pcBuffer, 1, i32Bytes, m_pkFile);
		m_i32FileSize += i32Bytes;
		m_i32CachePointer = m_i32FileSize;
	}
	else
	{
		VeCrazyCopy(Cache(), pcBuffer, i32Bytes);
		m_i32FileSize += i32Bytes;
	}
	return i32Res;
}
//--------------------------------------------------------------------------
VeInt32 VeFileOStream::Size() const
{
	return m_i32FileSize;
}
//--------------------------------------------------------------------------
bool VeFileOStream::HasCacheUse()
{
	VE_ASSERT(m_i32FileSize >= m_i32CachePointer);
	return m_i32FileSize > m_i32CachePointer;
}
//--------------------------------------------------------------------------
VeInt32 VeFileOStream::CacheUse()
{
	return m_i32FileSize - m_i32CachePointer;
}
//--------------------------------------------------------------------------
VeInt32 VeFileOStream::CacheCanUse()
{
	return m_i32CacheSize - CacheUse();
}
//--------------------------------------------------------------------------
VeByte* VeFileOStream::Cache()
{
	return m_pbyCache + CacheUse();
}
//--------------------------------------------------------------------------
void VeFileOStream::WriteBackCache()
{
	fwrite(m_pbyCache, 1, CacheUse(), m_pkFile);
	m_i32CachePointer = m_i32FileSize;
}
//--------------------------------------------------------------------------
VeFileDir::VeFileDir(const VeChar8* pcName)
	: VeDirectory((*pcName) ? pcName : ".")
{
	VE_ASSERT(VE_SUCCEEDED(VeAccess(m_kName, ACCESS_F_OK)));
}
//--------------------------------------------------------------------------
VeFileDir::~VeFileDir()
{

}
//--------------------------------------------------------------------------
bool VeFileDir::Access(VeUInt32 u32Flag) const
{
	return VE_SUCCEEDED(VeAccess(m_kName, u32Flag));
}
//--------------------------------------------------------------------------
bool VeFileDir::HasFile(const VeChar8* pcFileName) const
{
	VeString kFilePath = m_kName + "/" + pcFileName;
	bool bRes = false;

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)

	_finddata_t kData;
	VeSizeT stHandle = _findfirst(kFilePath, &kData);
	if((stHandle != VE_ELF) && ((kData.attrib & 0xf0) == _A_ARCH))
	{
		bRes = true;
	}

#else

	struct stat kBuf;
	if(VE_SUCCEEDED(lstat(kFilePath, &kBuf)))
	{
		bRes = S_ISREG(kBuf.st_mode);
	}

#endif

	return bRes;
}
//--------------------------------------------------------------------------
bool VeFileDir::HasDirectory(const VeChar8* pcDirName) const
{
	VeString kFilePath = m_kName + "/" + pcDirName;
	bool bRes = false;

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)

	_finddata_t kData;
	VeSizeT stHandle = _findfirst(kFilePath, &kData);
	if((stHandle != VE_ELF) && ((kData.attrib & 0xf0) == _A_SUBDIR))
	{
		bRes = true;
	}

#else

	struct stat kBuf;
	if(VE_SUCCEEDED(lstat(kFilePath, &kBuf)))
	{
		bRes = S_ISDIR(kBuf.st_mode);
	}

#endif

	return bRes;
}
//--------------------------------------------------------------------------
bool VeFileDir::Change(const VeChar8* pcDirName, bool bCreate)
{
	if(HasDirectory(pcDirName))
	{
		m_kName += "/";
		m_kName += pcDirName;
		return true;
	}
	else if(bCreate && Access(ACCESS_W_OK))
	{
		VeString kDirName = m_kName + "/" + pcDirName;
		if(VE_SUCCEEDED(VeMakeDirectory(kDirName)))
		{
			m_kName = kDirName;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
VeDirectory::Type VeFileDir::GetType() const
{
	return VeDirectory::TYPE_FILE;
}
//--------------------------------------------------------------------------
VeBinaryIStreamPtr VeFileDir::OpenSync(const VeChar8* pcFileName) const
{
	if(HasFile(pcFileName))
	{
		VeString kFilePath = m_kName + "/" + pcFileName;
		return VE_NEW VeFileIStream(kFilePath);
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
void VeFileDir::ReadAsync(const VeChar8* pcFileName, ReadDelegate& kDelegate) const
{
	VeString kFilePath = m_kName + "/" + pcFileName;
	ReadTask* pkTask = VE_NEW ReadTask(kFilePath, kDelegate);
	g_pResourceManager->AddBGTask(VeResourceManager::BG_QUEUE_FILE, pkTask);
}
//--------------------------------------------------------------------------
void VeFileDir::WriteAsync(const VeChar8* pcFileName, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, WriteType eType) const
{
	VeString kFilePath = m_kName + "/" + pcFileName;
	WriteTask* pkTask = VE_NEW WriteTask(kFilePath, spContent, kDelegate, eType);
	g_pResourceManager->AddBGTask(VeResourceManager::BG_QUEUE_FILE, pkTask);
}
//--------------------------------------------------------------------------
void VeFileDir::FindFileList(const VeChar8* pcDesc,
	VeVector<VeFixedString>& kList)
{
#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)

	_finddata_t kData;
	VeSizeT stHandle = _findfirst(m_kName + "/" + pcDesc, &kData);
	if(stHandle != VE_ELF)
	{
		do 
		{
			if((kData.attrib & 0xf0) == _A_ARCH)
			{
				kList.PushBack(kData.name);
			}
		}
		while(VE_SUCCEEDED(_findnext(stHandle, &kData)));
		VE_ASSERT_EQ(_findclose(stHandle), VE_S_OK);
	}

#else
    
    const VeChar8* pcFile = VeStrrchr(pcDesc, '/');
	pcFile = pcFile ? (pcFile + 1) : pcDesc;
    DIR* pkDir(NULL);
	if(pcFile == pcDesc)
	{
		pkDir = opendir(m_kName);
	}
	else
	{
		VeChar8 acPath[256];
		VeStrncpy(acPath, 256, pcDesc, pcFile - pcDesc - 1);
		pkDir = opendir(m_kName + "/" + acPath);
	}
    if(pkDir)
    {
        struct dirent* pkEntry;
        while((pkEntry = readdir(pkDir)))
        {
            if(pkEntry->d_type != DT_DIR)
            {
                if(VeWildNameMatch(pkEntry->d_name, pcFile))
                {
                    kList.PushBack(pkEntry->d_name);
                }
                
            }
        }
        VE_ASSERT_EQ(closedir(pkDir), VE_S_OK);
    }

#endif
}
//--------------------------------------------------------------------------
VeFileDir::ReadTask::ReadTask(const VeChar8* pcFullPath, ReadDelegate& kDelegate) : m_kFileFullPath(pcFullPath)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VeFileDir::ReadTask::~ReadTask()
{

}
//--------------------------------------------------------------------------
void VeFileDir::ReadTask::DoBackgroundTask(VeBackgroundTaskQueue& kMgr)
{
	if(VE_SUCCEEDED(VeAccess(m_kFileFullPath, ACCESS_R_OK)))
	{
		FILE* pkFile(NULL);
#		if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
		fopen_s(&pkFile, m_kFileFullPath, "rb");
#		else
		pkFile = fopen(m_kFileFullPath, "rb");
#		endif
		if(pkFile)
		{
			fseek(pkFile, 0, SEEK_END);
			VeInt32 i32Len = (VeInt32)ftell(pkFile);
			fseek(pkFile, 0, SEEK_SET);
			VeBlobPtr spBlob = VE_NEW VeBlob(i32Len);
			VeSizeT stRead = fread(spBlob->GetBuffer(), 1, i32Len, pkFile);
			fclose(pkFile);
			if(VeInt32(stRead) == i32Len)
			{
				m_spData = VE_NEW VeMemoryIStream(spBlob);
			}
		}
	}
	kMgr.AddMainThreadTask(this);
}
//--------------------------------------------------------------------------
void VeFileDir::ReadTask::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	m_kEvent.Callback(m_spData);
	m_spData = NULL;
}
//--------------------------------------------------------------------------
VeFileDir::WriteTask::WriteTask(const VeChar8* pcFullPath, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, VeDirectory::WriteType eType)
	: m_kFileFullPath(pcFullPath), m_spData(spContent), m_eType(eType), m_eResult(VE_S_OK)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VeFileDir::WriteTask::~WriteTask()
{

}
//--------------------------------------------------------------------------
void VeFileDir::WriteTask::DoBackgroundTask(VeBackgroundTaskQueue& kMgr)
{
	FILE* pkFile(NULL);
	const VeChar8* pcMode = (m_eType == VeDirectory::WRITE_CREATE_COVER) ? "wb" : "ab";
#	if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
	fopen_s(&pkFile, m_kFileFullPath, pcMode);
#	else
	pkFile = fopen(m_kFileFullPath, pcMode);
#	endif
	if(pkFile)
	{
		VeSizeT stWrite = fwrite(m_spData->GetDataForRead(), 1, m_spData->RemainingLength(), pkFile);
		fclose(pkFile);
		if(VeInt32(stWrite) == m_spData->RemainingLength())
		{
			m_eResult = VE_S_OK;
		}
		else
		{
			m_eResult = VE_E_FILE_WRITE;
		}
		m_spData->AfterReadData(VeInt32(stWrite));
	}
	else
	{
		m_eResult = VE_E_FILE_CREATE;
	}
	
	kMgr.AddMainThreadTask(this);
}
//--------------------------------------------------------------------------
void VeFileDir::WriteTask::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	m_spData = NULL;
	m_kEvent.Callback(m_eResult);
}
//--------------------------------------------------------------------------
