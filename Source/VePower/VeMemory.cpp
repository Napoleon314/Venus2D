////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemory.cpp
//  Version:     v1.00
//  Created:     5/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeMemory.inl"
#endif

//--------------------------------------------------------------------------
#ifdef VE_PLATFORM_APPLE
void* memalign(VeSizeT stAlignment, VeSizeT stByteSize)
{
	void* pvPointer(NULL);
	if(VE_SUCCEEDED(posix_memalign(&pvPointer, stAlignment, stByteSize)))
	{
		return pvPointer;
	}
	else
	{
		return NULL;
	}
}
#endif
//--------------------------------------------------------------------------
#ifdef VE_MEM_DEBUG
//--------------------------------------------------------------------------
#ifdef VE_MEM_TRACK
#	include <map>
struct VeMallocInfo
{
	VeSizeT m_stSize;
	const VeChar8* m_pcFile;
	VeInt32 m_i32Line;
	const VeChar8* m_pcFunc;
};
static std::map<VeSizeT,VeMallocInfo> s_kMallocMap;
static VeThread::Mutex s_kMutex;
#endif
//--------------------------------------------------------------------------
static volatile VeSizeT s_stMallocCount(0);
static volatile VeSizeT s_stAlignedMallocCount(0);
//--------------------------------------------------------------------------
extern VeVector<void (*)()> g_kClassInitList;
//--------------------------------------------------------------------------
extern VeVector<void (*)()> g_kClassTermList;
//--------------------------------------------------------------------------
void _VeMemoryExit()
{
	g_kClassInitList.~VeVector<void (*)()>();
	g_kClassTermList.~VeVector<void (*)()>();
	VeMemObject::ReleaseDeleteCallStack();
	VE_ASSERT(!s_stMallocCount);
	VE_ASSERT(!s_stAlignedMallocCount);
}
//--------------------------------------------------------------------------
void* _VeMalloc(VeSizeT stSizeInBytes, const VeChar8* pcSourceFile,
	VeInt32 iSourceLine, const VeChar8* pcFunction)
{
#	ifdef VE_MEM_TRACK
	VE_AUTO_LOCK_MUTEX(s_kMutex);
	VeAtomicIncrement32(s_stMallocCount);
	void* pvRes = VeExternalMalloc(stSizeInBytes);
	VeMallocInfo& kInfo = s_kMallocMap[(VeSizeT)pvRes];
	kInfo.m_stSize = stSizeInBytes;
	kInfo.m_pcFile = pcSourceFile;
	kInfo.m_i32Line = iSourceLine;
	kInfo.m_pcFunc = pcFunction;
	return pvRes;
#	else
	VeAtomicIncrement32(s_stMallocCount);
	return VeExternalMalloc(stSizeInBytes);
#	endif
}
//--------------------------------------------------------------------------
void* _VeAlignedMalloc(VeSizeT stSizeInBytes, VeSizeT stAlignment,
	const VeChar8* pcSourceFile, VeInt32 iSourceLine,
	const VeChar8* pcFunction)
{
	VeAtomicIncrement32(s_stAlignedMallocCount);
	return VeExternalAlignedMalloc(stSizeInBytes, stAlignment);
}
//--------------------------------------------------------------------------
void* _VeRealloc(void* pvMemblock, VeSizeT stSizeInBytes,
	const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction)
{
#	ifdef VE_MEM_TRACK
	VE_AUTO_LOCK_MUTEX(s_kMutex);
	void* pvRes = VeExternalRealloc(pvMemblock, stSizeInBytes);
	std::map<VeSizeT, VeMallocInfo>::iterator it = s_kMallocMap.find((VeSizeT)pvMemblock);
	VE_ASSERT(it != s_kMallocMap.end());
	VeMallocInfo kInfo = it->second;
	s_kMallocMap.erase(it);
	VE_ASSERT(s_kMallocMap.find((VeSizeT)pvRes) == s_kMallocMap.end());
	s_kMallocMap[(VeSizeT)pvRes] = kInfo;
	return pvRes;
#	else
	return VeExternalRealloc(pvMemblock, stSizeInBytes);
#	endif
}
//--------------------------------------------------------------------------
void _VeFree(void* pvMemory, const VeChar8* pcSourceFile,
	VeInt32 iSourceLine, const VeChar8* pcFunction)
{
#	ifdef VE_MEM_TRACK
	VE_AUTO_LOCK_MUTEX(s_kMutex);
	VeAtomicDecrement32(s_stMallocCount);
	VeExternalFree(pvMemory);
	std::map<VeSizeT, VeMallocInfo>::iterator it = s_kMallocMap.find((VeSizeT)pvMemory);
	VE_ASSERT(it != s_kMallocMap.end());
	s_kMallocMap.erase(it);
#	else
	VeAtomicDecrement32(s_stMallocCount);
	VeExternalFree(pvMemory);
#	endif
}
//--------------------------------------------------------------------------
void _VeAlignedFree(void* pvMemory, const VeChar8* pcSourceFile,
	VeInt32 iSourceLine, const VeChar8* pcFunction)
{
	VeAtomicDecrement32(s_stAlignedMallocCount);
	return VeExternalAlignedFree(pvMemory);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
