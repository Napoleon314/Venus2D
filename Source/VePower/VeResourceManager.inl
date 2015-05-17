////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeResourceManager.inl
//  Version:     v1.00
//  Created:     8/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeResourceManager::GetDir()
{
	return m_kDir;
}
//--------------------------------------------------------------------------
VE_INLINE void VeResourceManager::SetDefaultGroupName(const VeChar8* pcGroup)
{
	m_kDefaultGroupName = pcGroup;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeResourceManager::GetDefaultGroupName()
{
	return m_kDefaultGroupName;
}
//--------------------------------------------------------------------------
