////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTimer.h
//  Version:     v1.00
//  Created:     15/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeTimer;

VeSmartPointer(VeTimeEvent);

class VE_POWER_API VeTimeEvent : public VeRefObject
{
public:
	typedef VeEvent<const VeTimeEventPtr&> Event;
	typedef VeAbstractDelegate<const VeTimeEventPtr&> Delegate;

	VeTimeEvent();

	virtual ~VeTimeEvent();

	VE_INLINE void AddDelegate(Delegate& kDelegate);

	VE_INLINE VeUInt64 GetExecuteTime();

	VE_INLINE void Detach();

	VE_INLINE bool IsAttach()const;

	VE_INLINE VeTimer* GetParent();

protected:
	friend class VeTimer;
	VeRefNode<VeTimeEvent*> m_kNode;
	VeTimer* m_pkParent;
	Event m_kEvent;

private:
	VeUInt64 m_u64ExecuteTime;

};

#define VeDeclTimeDelegate(class,name) \
	void name(const VeTimeEventPtr&); \
	VeMemberDelegate<class,const VeTimeEventPtr&> m_k##name

#define VeImplTimeDelegate(class,name,evt) \
	void class::name(const VeTimeEventPtr& evt)

class VE_POWER_API VeTimer : public VeMemObject
{
public:
	VeTimer();

	~VeTimer();

	void Attach(VeTimeEvent* pkEvent, VeUInt64 u64Expire);

	void Detach(VeTimeEvent* pkEvent);

	void Tick(VeUInt64 u64Current);

protected:
	friend class VeTimeEvent;

	static VeRefList<VeTimeEvent*>* CreateNodeList();

	static void DestoryNodeList(VeRefList<VeTimeEvent*>* pkList);

	VeMap<VeUInt64,VeUInt32> m_kSortMap;
	VeVector< VeRefList<VeTimeEvent*>* > m_kEventSlotArray;

};

#ifndef VE_NO_INLINE
#	include "VeTimer.inl"
#endif
