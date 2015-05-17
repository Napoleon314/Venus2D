////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeFile.h
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)

#include <direct.h>
#include <io.h>

#define VeGetCurrentDirectory _getcwd
#define VeChangeDirectory _chdir
#define VeMakeDirectory _mkdir
#define VeRemoveDirectory _rmdir
#define VeAccess _access

#else

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define VeGetCurrentDirectory getcwd
#define VeChangeDirectory chdir
#define VeMakeDirectory(name) mkdir(name,S_IRWXU)
#define VeRemoveDirectory rmdir
#define VeAccess access

#endif

class VE_POWER_API VeFileIStream : public VeBinaryIStream
{
public:
	VeFileIStream(const VeChar8* pcFileName, VeInt32 i32Cache = 32768);

	virtual ~VeFileIStream();

	virtual VeInt32 Read(void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Seek(VeInt32 i32Offset, VeWhence eWhence);

	virtual VeInt32 Tell();

	virtual void* Skip(VeInt32 i32Bytes);

	virtual void Restart();

	virtual VeInt32 RemainingLength() const;

	virtual VeChar8 Peek();

	virtual void Finish();

	void CacheReload();

protected:
	void UpdateLenth();

	bool IsCached();

	VeInt32 Cached();

	FILE* m_pkFile;
	VeByte* m_pbyCache;
	VeInt32 m_i32FileSize;
	const VeInt32 m_i32CacheSize;
	VeInt32 m_i32Pointer;
	VeInt32 m_i32CachePointer;
	VeInt32 m_i32CacheUse;
};

VeSmartPointer(VeFileIStream);

class VE_POWER_API VeFileOStream : public VeBinaryOStream
{
public:
	VeFileOStream(const VeChar8* pcFileName, VeInt32 i32Cache = 32768, VeDirectory::WriteType eType = VeDirectory::WRITE_CREATE_COVER);

	virtual ~VeFileOStream();

	virtual VeInt32 Write(const void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Size() const;

protected:
	bool HasCacheUse();

	VeInt32 CacheUse();

	VeInt32 CacheCanUse();

	VeByte* Cache();

	void WriteBackCache();

	FILE* m_pkFile;
	VeByte* m_pbyCache;
	VeInt32 m_i32FileSize;
	const VeInt32 m_i32CacheSize;
	VeInt32 m_i32CachePointer;
};

VeSmartPointer(VeFileOStream);

class VE_POWER_API VeFileDir : public VeDirectory
{
public:
	class VE_POWER_API ReadTask : public VeBackgroundTask
	{
	public:
		ReadTask(const VeChar8* pcFullPath, ReadDelegate& kDelegate);

		virtual ~ReadTask();

		virtual void DoBackgroundTask(VeBackgroundTaskQueue& kMgr);

		virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

	protected:
		VeFixedString m_kFileFullPath;
		ReadEvent m_kEvent;
		VeMemoryIStreamPtr m_spData;

	};

	class VE_POWER_API WriteTask : public VeBackgroundTask
	{
	public:
		WriteTask(const VeChar8* pcFullPath, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, VeDirectory::WriteType eType);

		virtual ~WriteTask();

		virtual void DoBackgroundTask(VeBackgroundTaskQueue& kMgr);

		virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

	protected:
		VeFixedString m_kFileFullPath;
		WriteEvent m_kEvent;
		VeMemoryOStreamPtr m_spData;
		VeDirectory::WriteType m_eType;
		VeResult m_eResult;
	};

	VeFileDir(const VeChar8* pcName);

	virtual ~VeFileDir();

	virtual bool Access(VeUInt32 u32Flag) const;

	virtual bool HasFile(const VeChar8* pcFileName) const;

	virtual bool HasDirectory(const VeChar8* pcDirName) const;

	virtual bool Change(const VeChar8* pcDirName, bool bCreate = true);

	virtual Type GetType() const;

	virtual VeBinaryIStreamPtr OpenSync(const VeChar8* pcFileName) const;

	virtual void ReadAsync(const VeChar8* pcFileName, ReadDelegate& kDelegate) const;

	virtual void WriteAsync(const VeChar8* pcFileName, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, WriteType eType = WRITE_CREATE_COVER) const;

	virtual void FindFileList(const VeChar8* pcDesc, VeVector<VeFixedString>& kList);

};
