////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemory.h
//  Version:     v1.00
//  Created:     5/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef VE_PLATFORM_APPLE
#	include <malloc.h>
#endif

#define VeExternalNew new
#define VeExternalDelete delete
#define VeExternalAlloc(T, count) ((T*)malloc(sizeof(T)*(count)))
#define VeExternalMalloc malloc
#define VeExternalRealloc realloc
#define VeExternalFree free
#define VeExternalCalloc calloc

#ifdef VE_PLATFORM_APPLE
void* memalign(VeSizeT stAlignment, VeSizeT stByteSize);
#endif

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
#	define VeExternalAlignedMalloc _aligned_malloc
#	define VeExternalAlignedFree _aligned_free
#else
#	define VeExternalAlignedMalloc memalign
#	define VeExternalAlignedFree free
#endif

#include <new>

#ifdef VE_MEM_DEBUG

VE_POWER_API void _VeMemoryExit();

VE_POWER_API void* _VeMalloc(VeSizeT stSizeInBytes, const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction);

VE_POWER_API void* _VeAlignedMalloc(VeSizeT stSizeInBytes, VeSizeT stAlignment, const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction);

VE_POWER_API void* _VeRealloc(void* pvMemblock, VeSizeT stSizeInBytes, const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction); 

VE_POWER_API void _VeFree(void* pvMemory, const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction);

VE_POWER_API void _VeAlignedFree(void* pvMemory, const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction);

#define VeAlloc(T, count) ((T*)_VeMalloc(sizeof(T)*(count), __FILE__, __LINE__, __FUNCTION__))

#define VeMalloc(size) _VeMalloc(size, __FILE__, __LINE__, __FUNCTION__)

#define VeAlignedMalloc(size,align) _VeAlignedMalloc(size, align, __FILE__, __LINE__, __FUNCTION__)

#define VeRealloc(mem,size) _VeRealloc(mem, size, __FILE__, __LINE__, __FUNCTION__)

#define VeFree(mem) _VeFree(mem, __FILE__, __LINE__, __FUNCTION__)

#define VeAlignedFree(mem) _VeAlignedFree(mem, __FILE__, __LINE__, __FUNCTION__)

#define VE_NEW new(__FILE__, __LINE__, __FUNCTION__)

#define VE_DELETE(p) VeMemObject::PushDeleteCallParams(__FILE__, __LINE__, __FUNCTION__); delete p; VeMemObject::PopDeleteCallParams()

#define VE_DELETE_ARRAY(p) VeMemObject::PushDeleteCallParams(__FILE__, __LINE__, __FUNCTION__); delete [] p; VeMemObject::PopDeleteCallParams()

#else

VE_POWER_INLINE void* _VeMalloc(VeSizeT stSizeInBytes);

VE_POWER_INLINE void* _VeAlignedMalloc(VeSizeT stSizeInBytes, VeSizeT stAlignment);

VE_POWER_INLINE void* _VeRealloc(void* pvMemblock, VeSizeT stSizeInBytes); 

VE_POWER_INLINE void _VeFree(void* pvMemory);

VE_POWER_INLINE void _VeAlignedFree(void* pvMemory);

#define VeAlloc(T, count) ((T*)_VeMalloc(sizeof(T)*(count)))

#define VeMalloc(size) _VeMalloc(size)

#define VeAlignedMalloc(size,align) _VeAlignedMalloc(size, align)

#define VeRealloc(mem,size) _VeRealloc(mem, size)

#define VeFree(mem) _VeFree(mem)

#define VeAlignedFree(mem) _VeAlignedFree(mem)

#define VE_NEW new

#define VE_DELETE delete

#define VE_DELETE_ARRAY VE_DELETE []

#endif

#define VE_SAFE_DELETE(p)			{ if(p) { VE_DELETE (p); (p) = NULL; } }

#define VE_SAFE_DELETE_ARRAY(p)		{ if(p) { VE_DELETE_ARRAY(p); (p) = NULL; } }

#define VE_SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }

#ifndef VE_NO_INLINE
#	include "VeMemory.inl"
#endif
