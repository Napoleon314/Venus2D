////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeZip.h
//  Version:     v1.00
//  Created:     8/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

struct zzip_dir;
struct zzip_file;
typedef struct zzip_dir ZZIP_DIR;
typedef struct zzip_file ZZIP_FILE;
typedef struct zzip_dirent ZZIP_DIRENT;
typedef struct zzip_dirent ZZIP_STAT;

VeSmartPointer(VeZip);

class VE_POWER_API VeZip : public VeRefObject
{
public:
	struct VE_POWER_API FileInfo : public VeMemObject
	{
		VeFixedString m_kName;
		VeInt32 m_i32CSize;
		VeInt32 m_i32Size;
	};

	struct VE_POWER_API PathInfo : public VeMemObject
	{
		PathInfo();

		PathInfo(const PathInfo& kInfo);

		PathInfo& operator = (PathInfo& kInfo);

		PathInfo* m_pkParent;
		VeFixedString m_kName;
		VeStringMap<VeUInt32> m_kPathNameMap;
		VeVector<PathInfo> m_kPathList;
		VeStringMap<VeUInt32> m_kFileNameMap;
		VeVector<FileInfo> m_kFileList;
	};

	typedef VeStringMap<PathInfo*> PathMap;

	~VeZip();

	const VeChar8* GetName();

	ZZIP_DIR* GetDirRoot();

	VeThread::Mutex& GetMutex();

	static VeZipPtr LoadZip(const VeChar8* pcName);

protected:
	friend class VeZipDir;
	VeZip(const VeChar8* pcName, ZZIP_DIR* pkZzipRoot);

	VeFixedString m_kName;
	ZZIP_DIR* m_pkZzipRoot;
	PathInfo m_kPathCache;
	PathMap m_kPathMap;
	VeThread::Mutex m_kMutex;

};

class VE_POWER_API VeZipFileIStream : public VeBinaryIStream
{
public:
	VeZipFileIStream(const VeChar8* pcFileName, const VeZipPtr& spZip, ZZIP_FILE* pkZipFile, VeInt32 i32Size);

	virtual ~VeZipFileIStream();

	virtual VeInt32 Read(void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Seek(VeInt32 i32Offset, VeWhence eWhence);

	virtual VeInt32 Tell();

	virtual void* Skip(VeInt32 i32Bytes);

	virtual void Restart();

	virtual VeInt32 RemainingLength() const;

	virtual VeChar8 Peek();

	virtual void Finish();

protected:
	VeZipPtr m_spZip;
	ZZIP_FILE* m_pkZzipFile;
	VeInt32 m_i32RemainingLength;
	const VeInt32 m_i32Size;

};

class VE_POWER_API VeZipDir : public VeDirectory
{
public:
	class VE_POWER_API ReadTask : public VeBackgroundTask
	{
	public:
		ReadTask(const VeChar8* pcFullPath, ReadDelegate& kDelegate, const VeZipPtr& spZip, VeInt32 i32Size);

		virtual ~ReadTask();

		virtual void DoBackgroundTask(VeBackgroundTaskQueue& kMgr);

		virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

	protected:
		VeFixedString m_kFileFullPath;
		ReadEvent m_kEvent;
		VeZipPtr m_spZip;
		VeInt32 m_i32Size;
		VeMemoryIStreamPtr m_spData;

	};

	VeZipDir(const VeChar8* pcName, const VeZipPtr& spZip);

	virtual ~VeZipDir();

	virtual bool Access(VeUInt32 u32Flag) const;

	virtual bool HasFile(const VeChar8* pcFileName) const;

	virtual bool HasDirectory(const VeChar8* pcDirName) const;

	virtual bool Change(const VeChar8* pcDirName, bool bCreate = true);

	virtual Type GetType() const;

	virtual VeBinaryIStreamPtr OpenSync(const VeChar8* pcFileName) const;

	virtual void ReadAsync(const VeChar8* pcFileName, ReadDelegate& kDelegate) const;

	virtual void WriteAsync(const VeChar8* pcFileName, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, WriteType eType = WRITE_CREATE_COVER) const;

	virtual void FindFileList(const VeChar8* pcDesc, VeVector<VeFixedString>& kList) { VE_ASSERT(!"FindFileList Error!"); }

protected:
	VeZipPtr m_spZip;
	VeZip::PathInfo* m_pkPath;

};
