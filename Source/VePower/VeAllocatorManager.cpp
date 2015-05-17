////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAllocatorManager.cpp
//  Version:     v1.00
//  Created:     18/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
VeAllocatorManager::VeAllocatorManager()
	: m_kPoolAllocatorMap(32, VE_NEW VePoolAllocator(
	sizeof(VeHashMap<VeUInt32,VePoolAllocatorPtr>::Node), 32))
{
	m_kPoolAllocatorMap[
		sizeof(VeHashMap<VeUInt32,VePoolAllocatorPtr>::Node)
	] = m_kPoolAllocatorMap.GetAllocator();
}
//--------------------------------------------------------------------------
VeAllocatorManager::~VeAllocatorManager()
{

}
//--------------------------------------------------------------------------
const VePoolAllocatorPtr& VeAllocatorManager::GetPoolAllocator(
	VeUInt32 u32Size)
{
	VePoolAllocatorPtr* pkIter = m_kPoolAllocatorMap.Find(u32Size);
	if(pkIter)
	{
		return *pkIter;
	}
	else
	{
		return m_kPoolAllocatorMap[u32Size] =
			VE_NEW VePoolAllocator(u32Size, 32);
	}
}
//--------------------------------------------------------------------------
