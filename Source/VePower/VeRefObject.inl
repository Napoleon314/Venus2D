////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRefObject.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeRefObject::GetRefCount() const
{
	return m_u32RefCount;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeRefObject::GetTotalObjectCount()
{
	return ms_u32Objects;
}
//--------------------------------------------------------------------------
