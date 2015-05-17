////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemory.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
 #ifndef VE_MEM_DEBUG
//--------------------------------------------------------------------------
VE_INLINE void* _VeMalloc(VeSizeT stSizeInBytes)
{
	return VeExternalMalloc(stSizeInBytes);
}

VE_INLINE void* _VeAlignedMalloc(VeSizeT stSizeInBytes, VeSizeT stAlignment)
{
	return VeExternalAlignedMalloc(stSizeInBytes, stAlignment);
}

VE_INLINE void* _VeRealloc(void* pvMemblock, VeSizeT stSizeInBytes)
{
	return VeExternalRealloc(pvMemblock, stSizeInBytes);
}

VE_INLINE void _VeFree(void* pvMemory)
{
	return VeExternalFree(pvMemory);
}

VE_INLINE void _VeAlignedFree(void* pvMemory)
{
	return VeExternalAlignedFree(pvMemory);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
