////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeNetEntity.inl
//  Version:     v1.00
//  Created:     6/11/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeNetEntityManager::Type VeNetEntityManager::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeNetEntityManager::GetEntityNum()
{
	return m_kEntityArray.Size();
}
//--------------------------------------------------------------------------
