////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAllocatorManager.h
//  Version:     v1.00
//  Created:     18/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeAllocatorManager : public VeSingleton<VeAllocatorManager>
{
public:
	VeAllocatorManager();

	~VeAllocatorManager();

	const VePoolAllocatorPtr& GetPoolAllocator(VeUInt32 u32Size);

protected:
	VeHashMap<VeUInt32,VePoolAllocatorPtr> m_kPoolAllocatorMap;


};

#define g_pAllocatorManager VeAllocatorManager::GetSingletonPtr()
