////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAllocator.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
#ifdef VE_MEM_DEBUG
//--------------------------------------------------------------------------
VE_INLINE void* VePoolAllocator::Malloc(const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	++m_u32MallocCount;
	return MallocInternal(pcSourceFile, i32SourceLine, pcFunction);
}
//--------------------------------------------------------------------------
VE_INLINE void VePoolAllocator::Free(void* pvMemory, const VeChar8* pcSourceFile,
	VeInt32 i32SourceLine, const VeChar8* pcFunction)
{
	--m_u32MallocCount;
	FreeInternal(pvMemory, pcSourceFile, i32SourceLine, pcFunction);
}
//--------------------------------------------------------------------------
#else
//--------------------------------------------------------------------------
VE_INLINE void* VePoolAllocator::Malloc()
{
	return MallocInternal();
}
//--------------------------------------------------------------------------
VE_INLINE void VePoolAllocator::Free(void* pvMemory)
{
	FreeInternal(pvMemory);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VePoolAllocator::GetObjectSize()
{
	return m_u32ObjectSize - sizeof(VeSizeT);
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VePoolAllocator::GetPoolObjectCount()
{
	return m_u32PoolObjectCount;
}
//--------------------------------------------------------------------------
