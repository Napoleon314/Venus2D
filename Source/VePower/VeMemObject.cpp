////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemObject.cpp
//  Version:     v1.00
//  Created:     5/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
#ifdef VE_MEM_DEBUG
//--------------------------------------------------------------------------
struct VeDeleteCallParams
{
	const VeChar8* m_pcSourceFile;
	VeInt32 m_i32SourceLine;
	const VeChar8* m_pcFunction;
};
//--------------------------------------------------------------------------
static VeVector<VeDeleteCallParams> s_kDeleteCallParamsStack;
//--------------------------------------------------------------------------
static volatile VeThreadID s_hDeleteThreadID = 0;
//--------------------------------------------------------------------------
static VeThread::Mutex s_kDeleteMutex;
//--------------------------------------------------------------------------
void VeMemObject::PushDeleteCallParams(const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	if(s_hDeleteThreadID == 0)
	{
		VE_ASSERT(s_kDeleteCallParamsStack.Empty());
		s_kDeleteMutex.Lock();
		s_hDeleteThreadID = VeGetLocalThread();
	}
	else if(s_hDeleteThreadID != VeGetLocalThread())
	{
		s_kDeleteMutex.Lock();
		VE_ASSERT(s_kDeleteCallParamsStack.Empty());
		VE_ASSERT(s_hDeleteThreadID == 0);
		s_hDeleteThreadID = VeGetLocalThread();
	}
	else
	{
		VE_ASSERT(s_kDeleteCallParamsStack.Size());
	}
	VeDeleteCallParams kCurrent = { pcSourceFile, i32SourceLine, pcFunction };
	s_kDeleteCallParamsStack.PushBack(kCurrent);
}
//--------------------------------------------------------------------------
void VeMemObject::PopDeleteCallParams()
{
	VE_ASSERT(s_hDeleteThreadID == VeGetLocalThread());
	s_kDeleteCallParamsStack.PopBack();
	if(s_kDeleteCallParamsStack.Empty())
	{
		s_hDeleteThreadID = 0;
		s_kDeleteMutex.Unlock();
	}
}
//--------------------------------------------------------------------------
void VeMemObject::ReleaseDeleteCallStack()
{
	VeSleep(200);
	s_kDeleteCallParamsStack.~VeVector<VeDeleteCallParams>();
}
//--------------------------------------------------------------------------
void* VeMemObject::operator new(VeSizeT stSize, const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	return _VeMalloc(stSize, pcSourceFile, i32SourceLine, pcFunction);
}
//--------------------------------------------------------------------------
void* VeMemObject::operator new [](VeSizeT stSize, const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	return _VeMalloc(stSize, pcSourceFile, i32SourceLine, pcFunction);
}
//--------------------------------------------------------------------------
void VeMemObject::operator delete []( void* pvMem, const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	_VeFree(pvMem, pcSourceFile, i32SourceLine, pcFunction);
}
//--------------------------------------------------------------------------
void VeMemObject::operator delete( void* pvMem, const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	_VeFree(pvMem, pcSourceFile, i32SourceLine, pcFunction);
}
//--------------------------------------------------------------------------
void VeMemObject::operator delete (void* pvMem)
{
	VeDeleteCallParams& kParams = s_kDeleteCallParamsStack.Back();
	_VeFree(pvMem, kParams.m_pcSourceFile, kParams.m_i32SourceLine, kParams.m_pcFunction);
}
//--------------------------------------------------------------------------
void VeMemObject::operator delete [] (void* pvMem)
{
	VeDeleteCallParams& kParams = s_kDeleteCallParamsStack.Back();
	_VeFree(pvMem, kParams.m_pcSourceFile, kParams.m_i32SourceLine, kParams.m_pcFunction);
}
//--------------------------------------------------------------------------
#else
//--------------------------------------------------------------------------
void VeMemObject::operator delete (void* pvMem)
{
	_VeFree(pvMem);
}
//--------------------------------------------------------------------------
void VeMemObject::operator delete [] (void* pvMem)
{
	_VeFree(pvMem);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
void* VeMemObject::operator new (VeSizeT stSize)
{
	return VeMalloc(stSize);
}
//--------------------------------------------------------------------------
void* VeMemObject::operator new (VeSizeT stSize, void* pvMemory)
{
	return pvMemory;
}
//--------------------------------------------------------------------------
void* VeMemObject::operator new [] (VeSizeT stSize)
{
	return VeMalloc(stSize);
}
//--------------------------------------------------------------------------
