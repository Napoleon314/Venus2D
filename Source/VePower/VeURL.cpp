////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeURL.cpp
//  Version:     v1.00
//  Created:     11/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#include <curllib/curl.h>

//--------------------------------------------------------------------------
VeURL::VeURL()
{
	m_pkMultiHandle = curl_multi_init();
	VE_ASSERT(m_pkMultiHandle);
	m_kHandlePool.Resize(VE_URL_MAX_TASK_NUM);
	for(VeVector<CURL*>::iterator it = m_kHandlePool.Begin(); it != m_kHandlePool.End(); ++it)
	{
		*it = curl_easy_init();
		VE_ASSERT(*it);
	}
}
//--------------------------------------------------------------------------
VeURL::~VeURL()
{
	while(IsRunning())
	{
		Update();
	}
	Update();
	VE_ASSERT(m_kProcessorMap.Empty());
	VE_ASSERT(m_kProcessList.Empty());
	VE_ASSERT(m_kPrepareList.Empty());
	VE_ASSERT(m_kEndList.Empty());
	VE_ASSERT(m_kHandlesNeedRemove.Empty());
	VE_ASSERT(m_kHandlePool.Size() == VE_URL_MAX_TASK_NUM);
	for(VeVector<CURL*>::iterator it = m_kHandlePool.Begin(); it != m_kHandlePool.End(); ++it)
	{
		VE_ASSERT(*it);
		curl_easy_cleanup(*it);		
	}
	m_kHandlePool.Clear();
	VE_ASSERT(m_pkMultiHandle);
	curl_multi_cleanup(m_pkMultiHandle);
	m_pkMultiHandle = NULL;
	

}
//--------------------------------------------------------------------------
void VeURL::Run()
{
	CacheProcessors();
	VeInt32 i32StillRunning(0);
	while(CURLM_CALL_MULTI_PERFORM == curl_multi_perform(m_pkMultiHandle, &i32StillRunning)) ;

	while(i32StillRunning)
	{
		struct timeval kTimeout;
		long lCurlTimeo = -1;
		kTimeout.tv_sec = 1;
		kTimeout.tv_usec = 0;
		curl_multi_timeout(m_pkMultiHandle, &lCurlTimeo);
		if(lCurlTimeo >= 0)
		{
			kTimeout.tv_sec = lCurlTimeo / 1000;
			if(kTimeout.tv_sec > 1) kTimeout.tv_sec = 1;
			else kTimeout.tv_usec = (lCurlTimeo % 1000) * 1000;
		}

		fd_set kFdread;
		fd_set kFdwrite;
		fd_set kFdexcep;
		int iMaxfd = -1;
		FD_ZERO(&kFdread);
		FD_ZERO(&kFdwrite);
		FD_ZERO(&kFdexcep);
		curl_multi_fdset(m_pkMultiHandle, &kFdread, &kFdwrite, &kFdexcep, &iMaxfd);

		int iResCode = select(iMaxfd + 1, &kFdread, &kFdwrite, &kFdexcep, &kTimeout);
		switch(iResCode)
		{
		case -1:
			break;
		case 0:
		default:
			curl_multi_perform(m_pkMultiHandle, &i32StillRunning);
			break;
		}

		m_kMutex.Lock();
		for(VeVector<CURL*>::iterator it = m_kHandlesNeedRemove.Begin(); it != m_kHandlesNeedRemove.End(); ++it)
		{
			curl_multi_remove_handle(m_pkMultiHandle, *it);
			m_kHandlePool.PushBack(*it);
		}
		m_kHandlesNeedRemove.Clear();

		CURLMsg* pkMsg;
		int iMsgsLeft;
		while((pkMsg = curl_multi_info_read(m_pkMultiHandle, &iMsgsLeft)))
		{
			if(pkMsg->msg == CURLMSG_DONE)
			{
				m_kHandlePool.PushBack(pkMsg->easy_handle);
				Processor** ppkProcessor = m_kProcessorMap.Find(pkMsg->easy_handle);
				VE_ASSERT(*ppkProcessor);
				m_kProcessorMap.Remove(pkMsg->easy_handle);
				(*ppkProcessor)->m_pkHandle = NULL;
				curl_multi_remove_handle(m_pkMultiHandle, pkMsg->easy_handle);
				if(((*ppkProcessor)->m_i32Received) && ((*ppkProcessor)->m_i32FileSize > (*ppkProcessor)->m_i32Received))
				{
					m_kPrepareList.AttachBack((*ppkProcessor)->m_kNode);
				}
				else
				{
					m_kEndList.AttachBack((*ppkProcessor)->m_kNode);
				}
			}
		}
		m_kMutex.Unlock();

		CacheProcessors();
	}
}
//--------------------------------------------------------------------------
void VeURL::Update()
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	if(m_kPrepareList.Size() && (!IsRunning()))
	{
		Start();
	}

	m_kEndList.BeginIterator();
	while(!m_kEndList.IsEnd())
	{
		Processor* pkProcessor = m_kEndList.GetIterNode()->m_tContent;
		VE_ASSERT(pkProcessor->m_pkHandle == NULL);
		m_kEndList.Next();
		pkProcessor->m_kNode.Detach();
		pkProcessor->OnEnd();
	}
	VE_ASSERT(m_kEndList.Size() == 0);
}
//--------------------------------------------------------------------------
void VeURL::AddProcessor(Processor* pkProcessor)
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	m_kPrepareList.AttachBack(pkProcessor->m_kNode);
}
//--------------------------------------------------------------------------
void VeURL::DelProcessor(Processor* pkProcessor)
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	pkProcessor->m_kNode.Detach();
	if(pkProcessor->m_pkHandle)
	{
		m_kProcessorMap.Remove(pkProcessor->m_pkHandle);
		m_kHandlesNeedRemove.PushBack(pkProcessor->m_pkHandle);
		pkProcessor->m_pkHandle = NULL;
	}
}
//--------------------------------------------------------------------------
void VeURL::CacheProcessors()
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	while(m_kPrepareList.Size() && m_kHandlePool.Size())
	{
		Processor* pkProcessor = m_kPrepareList.GetHeadNode()->m_tContent;
		VE_ASSERT(pkProcessor);
		m_kProcessList.AttachBack(pkProcessor->m_kNode);
		CURL* pkHandle = m_kHandlePool.Back();
		m_kHandlePool.PopBack();
		m_kProcessorMap[pkHandle] = pkProcessor;
		pkProcessor->m_pkHandle = pkHandle;
		curl_easy_setopt(pkHandle, CURLOPT_URL, (const VeChar8*)(pkProcessor->m_kURL));
		curl_easy_setopt(pkHandle, CURLOPT_WRITEFUNCTION, Receive);
		curl_easy_setopt(pkHandle, CURLOPT_WRITEDATA, pkProcessor);
		if(pkProcessor->m_i32Received > 0)
		{
			VeChar8 acBuffer[128];
			VeSprintf(acBuffer, "%d-", pkProcessor->m_i32Received);
			curl_easy_setopt(pkHandle, CURLOPT_RANGE, acBuffer);
		}
		curl_easy_setopt(pkHandle, CURLOPT_HEADER, pkProcessor->m_i32FileSize > 0 ? 0 : 1);
		curl_multi_add_handle(m_pkMultiHandle, pkHandle);
	}
}
//--------------------------------------------------------------------------
VeSizeT VeURL::Receive(VeChar8* pcBuffer, VeSizeT stSize, VeSizeT stNum, void* pvProcessor)
{
	VE_AUTO_LOCK_MUTEX_NAME(g_pURL->m_kMutex, kURLMutex);
	VeSizeT stReceived = stSize * stNum;
	VE_ASSERT(stReceived <= VE_INT32_MAX);
	Processor* pkProcessor = (Processor*)pvProcessor;
	if(pkProcessor->m_i32FileSize > 0)
	{
		pkProcessor->OnReceived(pcBuffer, VeInt32(stReceived));
		pkProcessor->m_i32Received += VeInt32(stReceived);
	}
	else if(pkProcessor->m_i32FileSize < 0)
	{
		if(*pcBuffer == '\r')
		{
			VE_ASSERT(stReceived == 2);
			pkProcessor->m_i32FileSize = -pkProcessor->m_i32FileSize;
		}
	}
	else
	{
		VeChar8* pcContent = VeStrstr(pcBuffer, "Content-Length:");
		if(pcContent)
		{
			pkProcessor->m_i32FileSize = -VeAtoi(pcContent + 15);

		}
	}
	return stReceived;
}
//--------------------------------------------------------------------------
VeURL::Processor::Processor(const VeChar8* pcURL, VeInt32 i32FileSize)
	: m_kURL(pcURL), m_i32FileSize(i32FileSize), m_i32Received(0), m_pkHandle(NULL)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeURL::Processor::~Processor()
{
	g_pURL->DelProcessor(this);
}
//--------------------------------------------------------------------------
bool VeURL::Processor::IsProcess()
{
	VE_AUTO_LOCK_MUTEX_NAME(g_pURL->m_kMutex, kURLMutex);
	return m_kNode.IsAttach();
}
//--------------------------------------------------------------------------
VeURLIStream::VeURLIStream(const VeChar8* pcURL, VeInt32 i32FileSize)
	: VeURL::Processor(pcURL, i32FileSize), m_pvBuffer(NULL), m_i32Readed(0)
{

}
//--------------------------------------------------------------------------
VeURLIStream::~VeURLIStream()
{
	VE_ASSERT(!m_pvBuffer);
	VE_ASSERT(m_i32Received == m_i32FileSize);
	VE_ASSERT(m_i32Readed == m_i32FileSize);
}
//--------------------------------------------------------------------------
VeInt32 VeURLIStream::Read(void* pvBuffer, VeInt32 i32Bytes)
{
	while(m_i32FileSize <= 0)
	{
		g_pURL->Update();
		VeSleep(VE_URL_ISTREAM_SLEEP);
	}
	VeInt32 i32Read = VE_MIN(m_i32FileSize - m_i32Readed, i32Bytes);
	VE_ASSERT(i32Read >= 0);
	while(((m_i32Received - m_i32Readed) < i32Read) && IsProcess())
	{
		g_pURL->Update();
		VeSleep(VE_URL_ISTREAM_SLEEP);
	}
	i32Read = VE_MIN(m_i32Received - m_i32Readed, i32Read);
	VE_ASSERT(i32Read >= 0);
	VE_ASSERT(m_pvBuffer);
	VeCrazyCopy(pvBuffer, (const VeChar8*)m_pvBuffer + m_i32Readed, i32Read);
	m_i32Readed += i32Read;
	return i32Read;
}
//--------------------------------------------------------------------------
VeInt32 VeURLIStream::Seek(VeInt32 i32Offset, VeWhence eWhence)
{
	return VE_E_FAIL;
}
//--------------------------------------------------------------------------
VeInt32 VeURLIStream::Tell()
{
	return VE_E_FAIL;
}
//--------------------------------------------------------------------------
void* VeURLIStream::Skip(VeInt32 i32Bytes)
{
	while(m_i32FileSize <= 0)
	{
		g_pURL->Update();
		VeSleep(VE_URL_ISTREAM_SLEEP);
	}
	VeInt32 i32Read = VE_MIN(m_i32FileSize - m_i32Readed, i32Bytes);
	VE_ASSERT(i32Read >= 0);
	while(((m_i32Received - m_i32Readed) < i32Read) && IsProcess())
	{
		g_pURL->Update();
		VeSleep(VE_URL_ISTREAM_SLEEP);
	}
	i32Read = VE_MIN(m_i32Received - m_i32Readed, i32Read);
	VE_ASSERT(i32Read >= 0);
	VE_ASSERT(m_pvBuffer);
	void* pvBuffer = (VeChar8*)m_pvBuffer + m_i32Readed;
	m_i32Readed += i32Read;
	return pvBuffer;
}
//--------------------------------------------------------------------------
void VeURLIStream::Restart()
{
	m_i32Readed = 0;
}
//--------------------------------------------------------------------------
VeInt32 VeURLIStream::RemainingLength() const
{
	while(m_i32FileSize <= 0)
	{
		g_pURL->Update();
		VeSleep(VE_URL_ISTREAM_SLEEP);
	}
	return m_i32FileSize - m_i32Readed;
}
//--------------------------------------------------------------------------
VeChar8 VeURLIStream::Peek()
{
	if((m_i32Received - m_i32Readed) > 0)
	{
		return *((VeChar8*)m_pvBuffer + m_i32Readed);
	}
	else
	{
		return -1;
	}
}
//--------------------------------------------------------------------------
void VeURLIStream::Finish()
{
	m_i32Received = m_i32Readed = m_i32FileSize;
	g_pURL->DelProcessor(this);
	if(m_pvBuffer)
	{
		VeFree((void*)m_pvBuffer);
		m_pvBuffer = NULL;
	}
}
//--------------------------------------------------------------------------
void VeURLIStream::OnReceived(void* pvBuffer, VeInt32 i32Size)
{
	if(!m_pvBuffer)
	{
		VE_ASSERT(m_i32FileSize > 0);
		m_pvBuffer = VeMalloc(m_i32FileSize);
	}
	VE_ASSERT((m_i32FileSize - m_i32Received) >= i32Size);
	VeCrazyCopy((VeChar8*)m_pvBuffer + m_i32Received, pvBuffer, i32Size);
}
//--------------------------------------------------------------------------
void VeURLIStream::Reset()
{
	VE_ASSERT(m_pvBuffer);
	m_i32Readed = 0;
}
//--------------------------------------------------------------------------
VeURLDir::VeURLDir(const VeChar8* pcName)
	: VeDirectory(pcName)
{

}
//--------------------------------------------------------------------------
VeURLDir::~VeURLDir()
{

}
//--------------------------------------------------------------------------
bool VeURLDir::Access(VeUInt32 u32Flag) const
{
	return true;
}
//--------------------------------------------------------------------------
bool VeURLDir::HasFile(const VeChar8* pcFileName) const
{
	return true;
}
//--------------------------------------------------------------------------
bool VeURLDir::HasDirectory(const VeChar8* pcDirName) const
{
	return true;
}
//--------------------------------------------------------------------------
bool VeURLDir::Change(const VeChar8* pcDirName, bool bCreate)
{
	m_kName += "/";
	m_kName += pcDirName;
	return true;
}
//--------------------------------------------------------------------------
VeDirectory::Type VeURLDir::GetType() const
{
	return TYPE_URL;
}
//--------------------------------------------------------------------------
VeBinaryIStreamPtr VeURLDir::OpenSync(const VeChar8* pcFileName) const
{
	VeURLIStream* pkStream = VE_NEW VeURLIStream(m_kName + "/" + pcFileName);
	VE_ASSERT(pkStream);
	g_pURL->AddProcessor(pkStream);
	return pkStream;
}
//--------------------------------------------------------------------------
void VeURLDir::ReadAsync(const VeChar8* pcFileName, ReadDelegate& kDelegate) const
{
	ReadAsyncProcessor* pkProcessor = VE_NEW ReadAsyncProcessor(m_kName + "/" + pcFileName, kDelegate);
	VE_ASSERT(pkProcessor);
	g_pURL->AddProcessor(pkProcessor);
}
//--------------------------------------------------------------------------
void VeURLDir::WriteAsync(const VeChar8* pcFileName, const VeMemoryOStreamPtr& spContent, WriteDelegate& kDelegate, WriteType eType) const
{
	kDelegate.Callback(VE_E_FILE_ACCESS);
}
//--------------------------------------------------------------------------
VeURLDir::ReadAsyncProcessor::ReadAsyncProcessor(const VeChar8* pcURL, ReadDelegate& kDelegate)
	: VeURL::Processor(pcURL, 0)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VeURLDir::ReadAsyncProcessor::~ReadAsyncProcessor()
{

}
//--------------------------------------------------------------------------
void VeURLDir::ReadAsyncProcessor::OnReceived(void* pvBuffer, VeInt32 i32Size)
{
	if(!m_spData)
	{
		VE_ASSERT(m_i32FileSize > 0);
		m_spData = VE_NEW VeBlob(m_i32FileSize);
	}
	VE_ASSERT((m_i32FileSize - m_i32Received) >= i32Size);
	VeCrazyCopy(m_spData->GetBuffer(m_i32Received), pvBuffer, i32Size);
}
//--------------------------------------------------------------------------
void VeURLDir::ReadAsyncProcessor::OnEnd()
{
	m_kEvent.Callback(VE_NEW VeMemoryIStream(m_spData));
	m_spData = NULL;
	VE_DELETE(this);
}
//--------------------------------------------------------------------------
