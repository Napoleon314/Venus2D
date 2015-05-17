////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRefObject.cpp
//  Version:     v1.00
//  Created:     7/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeRefObject.inl"
#endif

//--------------------------------------------------------------------------
volatile VeUInt32 VeRefObject::ms_u32Objects = 0;
//--------------------------------------------------------------------------
VeRefObject::VeRefObject()
{
	m_u32RefCount = 0;
	++ms_u32Objects;
}
//--------------------------------------------------------------------------
VeRefObject::~VeRefObject()
{
	VeAtomicDecrement32(ms_u32Objects);
}
//--------------------------------------------------------------------------
void VeRefObject::DeleteThis()
{
	VE_DELETE(this);
}
//--------------------------------------------------------------------------
void VeRefObject::IncRefCount()
{
	VeAtomicIncrement32(m_u32RefCount);
}
//--------------------------------------------------------------------------
void VeRefObject::DecRefCount()
{
	if(VeAtomicDecrement32(m_u32RefCount) == 0)
		DeleteThis();
}
//--------------------------------------------------------------------------
