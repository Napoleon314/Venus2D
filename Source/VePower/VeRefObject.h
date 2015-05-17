////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRefObject.h
//  Version:     v1.00
//  Created:     7/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeRefObject : public VeMemObject
{
public:
	VeRefObject();

	virtual ~VeRefObject();

	virtual void IncRefCount();

	virtual void DecRefCount();

	VE_INLINE VeUInt32 GetRefCount() const;

	VE_INLINE static VeUInt32 GetTotalObjectCount();

protected:
	void DeleteThis();

private:
	volatile VeUInt32 m_u32RefCount;
	static volatile VeUInt32 ms_u32Objects;
};

#ifndef VE_NO_INLINE
#	include "VeRefObject.inl"
#endif
