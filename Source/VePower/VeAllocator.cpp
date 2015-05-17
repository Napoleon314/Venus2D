////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAllocator.cpp
//  Version:     v1.00
//  Created:     28/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeAllocator.inl"
#endif

//--------------------------------------------------------------------------
VePoolAllocator::VePoolAllocator(VeUInt32 u32ObjectSize
	, VeUInt32 u32PoolObjectCount, bool bInc)
	: m_u32ObjectSize(u32ObjectSize + sizeof(VeSizeT))
	, m_u32PoolObjectCount(u32PoolObjectCount)
	, m_pkPoolList(NULL)
	, m_pvFreeMemHead(NULL)
#	ifdef VE_MEM_DEBUG
	, m_u32MallocCount(0)
	, m_u32PoolCount(0)
#	endif
{
#	ifdef VE_MEM_DEBUG
	AddPool(__FILE__,__LINE__,__FUNCTION__);
#	else
	AddPool();
#	endif
	if(bInc)
	{
		IncRefCount();
	}
}
//--------------------------------------------------------------------------
VePoolAllocator::~VePoolAllocator()
{
	m_pvFreeMemHead = NULL;

	while(m_pkPoolList)
	{
		Pool* pkPre = m_pkPoolList->m_pvPre;
		VeFree(m_pkPoolList->m_pvBuffer);
		VeFree(m_pkPoolList);
		m_pkPoolList = pkPre;
	}
}
//--------------------------------------------------------------------------
#ifdef VE_MEM_DEBUG
//--------------------------------------------------------------------------
void VePoolAllocator::AddPool(const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	++m_u32PoolCount;
	Pool* pkNewPool = ((Pool*)_VeMalloc(sizeof(Pool)*(1), pcSourceFile, i32SourceLine, pcFunction));
	pkNewPool->m_pvBuffer
		= _VeMalloc(m_u32ObjectSize * m_u32PoolObjectCount, __FILE__,__LINE__,__FUNCTION__);
	pkNewPool->m_pvFreeStart = (void*)(((VeSizeT)pkNewPool->m_pvBuffer)
		+ m_u32ObjectSize * m_u32PoolObjectCount);
	pkNewPool->m_pvPre = m_pkPoolList;
	m_pkPoolList = pkNewPool;
}
//--------------------------------------------------------------------------
void* VePoolAllocator::MallocInternal(const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	VE_ASSERT(m_pkPoolList);
	if(m_pkPoolList->m_pvBuffer != m_pkPoolList->m_pvFreeStart)
	{
		m_pkPoolList->m_pvFreeStart =
			(void*)((VeSizeT)m_pkPoolList->m_pvFreeStart - m_u32ObjectSize);
		return m_pkPoolList->m_pvFreeStart;
	}

	if(m_pvFreeMemHead)
	{
		void* pvRes = m_pvFreeMemHead;
		m_pvFreeMemHead
			= (void*)(*(VeSizeT*)(((VeByte*)m_pvFreeMemHead)
			+ m_u32ObjectSize - sizeof(VeSizeT)));
		return pvRes;
	}

	AddPool(pcSourceFile, i32SourceLine, pcFunction);

	return MallocInternal(pcSourceFile, i32SourceLine, pcFunction);
}
//--------------------------------------------------------------------------
void VePoolAllocator::FreeInternal(void* pvMemory,
	const VeChar8* pcSourceFile, VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	*(VeSizeT*)((VeByte*)pvMemory + m_u32ObjectSize - sizeof(VeSizeT))
		= (VeSizeT)m_pvFreeMemHead;
	m_pvFreeMemHead = pvMemory;
}
//--------------------------------------------------------------------------
#else
//--------------------------------------------------------------------------
void VePoolAllocator::AddPool()
{
	Pool* pkNewPool = ((Pool*)_VeMalloc(sizeof(Pool)*(1)));
	pkNewPool->m_pvBuffer
		= _VeMalloc(m_u32ObjectSize * m_u32PoolObjectCount);
	pkNewPool->m_pvFreeStart = (void*)(((VeSizeT)pkNewPool->m_pvBuffer)
		+ m_u32ObjectSize * m_u32PoolObjectCount);
	pkNewPool->m_pvPre = m_pkPoolList;
	m_pkPoolList = pkNewPool;
}
//--------------------------------------------------------------------------
void* VePoolAllocator::MallocInternal()
{
	VE_ASSERT(m_pkPoolList);
	if(m_pkPoolList->m_pvBuffer != m_pkPoolList->m_pvFreeStart)
	{
		m_pkPoolList->m_pvFreeStart =
			(void*)((VeSizeT)m_pkPoolList->m_pvFreeStart - m_u32ObjectSize);
		return m_pkPoolList->m_pvFreeStart;
	}

	if(m_pvFreeMemHead)
	{
		void* pvRes = m_pvFreeMemHead;
		m_pvFreeMemHead
			= (void*)(*(VeSizeT*)(((VeByte*)m_pvFreeMemHead)
			+ m_u32ObjectSize - sizeof(VeSizeT)));
		return pvRes;
	}

	AddPool();

	return MallocInternal();
}
//--------------------------------------------------------------------------
void VePoolAllocator::FreeInternal(void* pvMemory)
{
	*(VeSizeT*)((VeByte*)pvMemory + m_u32ObjectSize - sizeof(VeSizeT))
		= (VeSizeT)m_pvFreeMemHead;
	m_pvFreeMemHead = pvMemory;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
const VePoolAllocatorPtr& VePoolAllocator::GetPoolAllocator(
	VeUInt32 u32Size)
{
	return g_pAllocatorManager->GetPoolAllocator(u32Size);
}
//--------------------------------------------------------------------------
