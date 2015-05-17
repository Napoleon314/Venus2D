////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBackgroundTaskQueue.h
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeBackgroundTask;
class VeBackgroundTaskQueue;

class VE_POWER_API VeBackgroundTask : public VeRefObject
{
public:
	VeBackgroundTask();

	virtual void DoBackgroundTask(VeBackgroundTaskQueue& kMgr) {}

	virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr) {}

protected:
	virtual ~VeBackgroundTask();

private:
	friend class VeBackgroundTaskQueue;
	VeRefNode<VeBackgroundTask*> m_kNode;

};

VeSmartPointer(VeBackgroundTask);

class VE_POWER_API VeBackgroundTaskQueue : public VeThread
{
public:
	VeBackgroundTaskQueue(VeUInt32 u32Priority = VE_THREAD_PRIORITY_NORMAL, VeSizeT stStackSize = 32768);

	~VeBackgroundTaskQueue();

	VE_INLINE void SetTickOnce(bool bEnable);

	VE_INLINE bool IsTickOnce();

	void AddBackgroundTask(const VeBackgroundTaskPtr& spTask);

	void AddMainThreadTask(const VeBackgroundTaskPtr& spTask);

	virtual void Run();

	void Update();

	bool HasTask();

protected:
	VeThread::Mutex m_kMutex;
	VeRefList<VeBackgroundTask*> m_kBGTaskList;
	VeRefList<VeBackgroundTask*> m_kFGTaskList;

	VeThread::Mutex m_kBGMutex;
	VeThread::Mutex m_kFGMutex;
	VeRefList<VeBackgroundTask*> m_kBackgroundTasks[2];
	VeRefList<VeBackgroundTask*> m_kForegroundTasks[2];
	volatile VeUInt32 m_u32ActiveBackgroundTask;
	volatile VeUInt32 m_u32ActiveForegroundTask;
	bool m_bTickOnce;

};

#ifndef VE_NO_INLINE
#	include "VeBackgroundTaskQueue.inl"
#endif
