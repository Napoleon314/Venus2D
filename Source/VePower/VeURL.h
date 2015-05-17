////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeURL.h
//  Version:     v1.00
//  Created:     11/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once
#include "VePower.h"

typedef void CURLM;
typedef void CURL;

#define VE_URL_MAX_TASK_NUM (5)

class VE_POWER_API VeURL : public VeSingleton<VeURL>, VeThread
{
public:
	class VE_POWER_API Processor : public VeMemObject
	{
	public:
		Processor(const VeChar8* pcURL, VeInt32 i32FileSize = 0);

		virtual ~Processor();

		virtual void OnReceived(void* pvBuffer, VeInt32 i32Size) {};

		virtual void OnEnd() {};

		bool IsProcess();

	protected:
		friend class VeURL;

		VeFixedString m_kURL;
		volatile VeInt32 m_i32FileSize;
		volatile VeInt32 m_i32Received;
		
	private:
		VeRefNode<Processor*> m_kNode;
		CURL* m_pkHandle;

	};

	VeURL();

	virtual ~VeURL();

	virtual void Run();

	void Update();

	void AddProcessor(Processor* pkProcessor);

	void DelProcessor(Processor* pkProcessor);

protected:
	void CacheProcessors();

	static VeSizeT Receive(VeChar8* pcBuffer, VeSizeT stSize, VeSizeT stNum, void* pvProcessor);

	CURLM* m_pkMultiHandle;
	VeVector<CURL*> m_kHandlePool;
	VeHashMap<CURL*,Processor*> m_kProcessorMap;
	VeRefList<Processor*> m_kProcessList;

	VeRefList<Processor*> m_kPrepareList;
	VeRefList<Processor*> m_kEndList;

	VeVector<CURL*> m_kHandlesNeedRemove;

	VeThread::Mutex m_kMutex;

};

#define g_pURL VeURL::GetSingletonPtr()

#define VE_URL_ISTREAM_SLEEP (50)

class VE_POWER_API VeURLIStream : public VeBinaryIStream, public VeURL::Processor
{
public:
	VeURLIStream(const VeChar8* pcURL, VeInt32 i32FileSize = 0);

	virtual ~VeURLIStream();

	virtual VeInt32 Read(void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Seek(VeInt32 i32Offset, VeWhence eWhence);

	virtual VeInt32 Tell();

	virtual void* Skip(VeInt32 i32Bytes);

	virtual void Restart();

	virtual VeInt32 RemainingLength() const;

	virtual VeChar8 Peek();

	virtual void Finish();

	virtual void OnReceived(void* pvBuffer, VeInt32 i32Size);

	void Reset();

	const VeBlobPtr& GetBlob();

protected:
	volatile void* m_pvBuffer;
	VeInt32 m_i32Readed;

};

class VE_POWER_API VeURLDir : public VeDirectory
{
public:
	class VE_POWER_API ReadAsyncProcessor : public VeURL::Processor
	{
	public:
		ReadAsyncProcessor(const VeChar8* pcURL, ReadDelegate& kDelegate);

		virtual ~ReadAsyncProcessor();

		virtual void OnReceived(void* pvBuffer, VeInt32 i32Size);

		virtual void OnEnd();

	protected:
		ReadEvent m_kEvent;
		VeBlobPtr m_spData;

	};

	VeURLDir(const VeChar8* pcName);

	virtual ~VeURLDir();

	virtual bool Access(VeUInt32 u32Flag) const;

	virtual bool HasFile(const VeChar8* pcFileName) const;

	virtual bool HasDirectory(const VeChar8* pcDirName) const;

	virtual bool Change(const VeChar8* pcDirName, bool bCreate = true);

	virtual Type GetType() const;

	virtual VeBinaryIStreamPtr OpenSync(const VeChar8* pcFileName) const;

	virtual void ReadAsync(const VeChar8* pcFileName, ReadDelegate& kDelegate) const;

	virtual void WriteAsync(const VeChar8* pcFileName, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, WriteType eType = WRITE_CREATE_COVER) const;

	virtual void FindFileList(const VeChar8* pcDesc, VeVector<VeFixedString>& kList) { VE_ASSERT(!"FindFileList Error!"); }

};
