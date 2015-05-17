////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBackgroundTaskQueue.cpp
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeBackgroundTaskQueue.inl"
#endif

//--------------------------------------------------------------------------
VeBackgroundTask::VeBackgroundTask()
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeBackgroundTask::~VeBackgroundTask()
{

}
//--------------------------------------------------------------------------
VeBackgroundTaskQueue::VeBackgroundTaskQueue(VeUInt32 u32Priority
	, VeSizeT stStackSize) : VeThread(u32Priority, stStackSize)
	, m_u32ActiveBackgroundTask(0), m_u32ActiveForegroundTask(1)
	, m_bTickOnce(false)
{

}
//--------------------------------------------------------------------------
VeBackgroundTaskQueue::~VeBackgroundTaskQueue()
{
	VE_ASSERT(!IsRunning());
	VE_ASSERT(m_kBGTaskList.Empty() && m_kFGTaskList.Empty());
}
//--------------------------------------------------------------------------
void VeBackgroundTaskQueue::AddBackgroundTask(const VeBackgroundTaskPtr& spTask)
{
	spTask->IncRefCount();
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		m_kBGTaskList.AttachBack(spTask->m_kNode);
	}
}
//--------------------------------------------------------------------------
void VeBackgroundTaskQueue::AddMainThreadTask(const VeBackgroundTaskPtr& spTask)
{
	spTask->IncRefCount();
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		m_kFGTaskList.AttachBack(spTask->m_kNode);
	}
}
//--------------------------------------------------------------------------
void VeBackgroundTaskQueue::Run()
{
	while(true)
	{
		VeBackgroundTask* pkTask(NULL);
		{
			VE_AUTO_LOCK_MUTEX(m_kMutex);
			if(m_kBGTaskList.Size())
			{
				pkTask = m_kBGTaskList.GetHeadNode()->m_tContent;
				pkTask->m_kNode.Detach();
			}
		}
		if(pkTask)
		{
			pkTask->DoBackgroundTask(*this);
			pkTask->DecRefCount();
		}
		else
		{
			break;
		}
	}
}
//--------------------------------------------------------------------------
void VeBackgroundTaskQueue::Update()
{
	if(!IsRunning())
	{
		if(m_kBGTaskList.Size()) Start();
	}
	if(m_bTickOnce)
	{
		VeBackgroundTask* pkTask(NULL);
		{
			VE_AUTO_LOCK_MUTEX(m_kMutex);
			if(m_kFGTaskList.Size())
			{
				pkTask = m_kFGTaskList.GetHeadNode()->m_tContent;
				pkTask->m_kNode.Detach();
			}
		}
		if(pkTask)
		{
			pkTask->DoMainThreadTask(*this);
			pkTask->DecRefCount();
		}
	}
	else
	{
		while(true)
		{
			VeBackgroundTask* pkTask(NULL);
			{
				VE_AUTO_LOCK_MUTEX(m_kMutex);
				if(m_kFGTaskList.Size())
				{
					pkTask = m_kFGTaskList.GetHeadNode()->m_tContent;
					pkTask->m_kNode.Detach();
				}
			}
			if(pkTask)
			{
				pkTask->DoMainThreadTask(*this);
				pkTask->DecRefCount();
			}
			else
			{
				break;
			}
		}
	}
}
//--------------------------------------------------------------------------
bool VeBackgroundTaskQueue::HasTask()
{
	if(IsRunning())
	{
		return true;
	}
	else
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		return m_kBGTaskList.Size() || m_kFGTaskList.Size();
	}
}
//--------------------------------------------------------------------------
