////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAsset.h
//  Version:     v1.00
//  Created:     29/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#if defined(VE_PLATFORM_ANDROID)

VE_POWER_API void SetAssetManager(AAssetManager* pkManager);

class VE_POWER_API VeAssetIStream : public VeBinaryIStream
{
public:
	VeAssetIStream(const VeChar8* pcAssetName);

	virtual ~VeAssetIStream();

	virtual VeInt32 Read(void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Seek(VeInt32 i32Offset, VeWhence eWhence);

	virtual VeInt32 Tell();

	virtual void* Skip(VeInt32 i32Bytes);

	virtual void Restart();

	virtual VeInt32 RemainingLength() const;

	virtual VeChar8 Peek();

	virtual void Finish();

protected:
	AAsset* m_pkAsset;

};

class VE_POWER_API VeAssetDir : public VeDirectory
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

	VeAssetDir(const VeChar8* pcName);

	virtual ~VeAssetDir();

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

#endif
