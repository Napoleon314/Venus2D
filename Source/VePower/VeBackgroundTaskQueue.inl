////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBackgroundTaskQueue.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeBackgroundTaskQueue::SetTickOnce(bool bEnable)
{
	m_bTickOnce = bEnable;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBackgroundTaskQueue::IsTickOnce()
{
	return m_bTickOnce;
}
//--------------------------------------------------------------------------
