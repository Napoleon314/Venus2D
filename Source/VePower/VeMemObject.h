////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemObject.h
//  Version:     v1.00
//  Created:     5/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeMemObject
{
public:

#ifdef VE_MEM_DEBUG

	static void* operator new (VeSizeT stSize, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	static void* operator new [] (VeSizeT stSize, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	static void operator delete (void* pvMem, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	static void operator delete [] (void* pvMem, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	static void PushDeleteCallParams(const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	static void PopDeleteCallParams();

	static void ReleaseDeleteCallStack();

#endif

	static void* operator new (VeSizeT stSize);

	static void* operator new [] (VeSizeT stSize);

	static void* operator new (VeSizeT stSize, void* pvMemory);

	static void operator delete (void* pvMem);

	static void operator delete [] (void* pvMem);

};
