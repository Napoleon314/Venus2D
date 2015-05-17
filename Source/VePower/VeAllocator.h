////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAllocator.h
//  Version:     v1.00
//  Created:     28/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

VeSmartPointer(VePoolAllocator);

class VE_POWER_API VePoolAllocator : public VeRefObject
{
public:
	VePoolAllocator(VeUInt32 u32ObjectSize, VeUInt32 u32PoolObjectCount = 256, bool bInc = false);

	~VePoolAllocator();

#ifdef VE_MEM_DEBUG

	VE_INLINE void* Malloc(const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	VE_INLINE void Free(void* pvMemory, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

#else

	VE_INLINE void* Malloc();

	VE_INLINE void Free(void* pvMemory);

#endif

	VE_INLINE VeUInt32 GetObjectSize();

	VE_INLINE VeUInt32 GetPoolObjectCount();

	static const VePoolAllocatorPtr& GetPoolAllocator(VeUInt32 u32Size);

protected:

#ifdef VE_MEM_DEBUG

	void AddPool(const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	void* MallocInternal(const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

	void FreeInternal(void* pvMemory, const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction);

#else

	void AddPool();

	void* MallocInternal();

	void FreeInternal(void* pvMemory);

#endif

	struct Pool
	{
		void* m_pvBuffer;
		void* m_pvFreeStart;
		Pool* m_pvPre;
	};

	const VeUInt32 m_u32ObjectSize;
	const VeUInt32 m_u32PoolObjectCount;
	Pool* m_pkPoolList;
	void* m_pvFreeMemHead;
#	ifdef VE_MEM_DEBUG
	volatile VeUInt32 m_u32MallocCount;
	volatile VeUInt32 m_u32PoolCount;
#	endif

};

#ifdef VE_MEM_DEBUG
#	define VePoolMalloc(pool) (pool->Malloc(__FILE__,__LINE__,__FUNCTION__))
#	define VePoolFree(pool,mem) pool->Free(mem,__FILE__,__LINE__,__FUNCTION__)
#else
#	define VePoolMalloc(pool) (pool->Malloc())
#	define VePoolFree(pool,mem) pool->Free(mem)
#endif

#ifndef VE_NO_INLINE
#	include "VeAllocator.inl"
#endif
