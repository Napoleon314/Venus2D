////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTimer.cpp
//  Version:     v1.00
//  Created:     15/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeTimer.inl"
#endif

//--------------------------------------------------------------------------
VeTimeEvent::VeTimeEvent()
{
	m_kNode.m_tContent = this;
	m_pkParent = NULL;
	m_u64ExecuteTime = 0;
}
//--------------------------------------------------------------------------
VeTimeEvent::~VeTimeEvent()
{

}
//--------------------------------------------------------------------------
VeTimer::VeTimer()
{

}
//--------------------------------------------------------------------------
VeTimer::~VeTimer()
{
	m_kSortMap.Clear();
	for(VeUInt32 i(0); i < m_kEventSlotArray.Size(); ++i)
	{
		VeRefList<VeTimeEvent*>* pkList = m_kEventSlotArray[i];
		VE_ASSERT(pkList);
		pkList->BeginIterator();
		while(!pkList->IsEnd())
		{
			VeTimeEvent* pkEvent = pkList->GetIterNode()->m_tContent;
			pkList->Next();
			pkEvent->m_kNode.Detach();
			pkEvent->m_pkParent = NULL;
			pkEvent->DecRefCount();
		}
		VE_ASSERT(pkList->Empty());
		DestoryNodeList(pkList);
	}
	m_kEventSlotArray.Clear();
}
//--------------------------------------------------------------------------
void VeTimer::Attach(VeTimeEvent* pkEvent, VeUInt64 u64Expire)
{
	VE_ASSERT(pkEvent);
	pkEvent->IncRefCount();
	pkEvent->Detach();
	pkEvent->m_pkParent = this;
	pkEvent->m_u64ExecuteTime = u64Expire;
	VeMap<VeUInt64,VeUInt32>::iterator it = m_kSortMap.Find(u64Expire);
	if(it != m_kSortMap.End())
	{
		VE_ASSERT(it->m_tSecond < m_kEventSlotArray.Size());
		m_kEventSlotArray[it->m_tSecond]->AttachBack(pkEvent->m_kNode);
	}
	else
	{
		m_kSortMap[u64Expire] = m_kEventSlotArray.Size();
		m_kEventSlotArray.Increase();
		m_kEventSlotArray.Back() = CreateNodeList();
		m_kEventSlotArray.Back()->AttachBack(pkEvent->m_kNode);
	}
}
//--------------------------------------------------------------------------
void VeTimer::Detach(VeTimeEvent* pkEvent)
{
	VE_ASSERT(pkEvent && pkEvent->m_pkParent == this);
	VeRefList<VeTimeEvent*>* pkNodeList = pkEvent->m_kNode.GetRefList();
	VE_ASSERT(pkNodeList);
	pkEvent->m_kNode.Detach();
	if(pkNodeList->Empty())
	{
		VeMap<VeUInt64,VeUInt32>::iterator itFind = m_kSortMap.Find(pkEvent->m_u64ExecuteTime);
		VE_ASSERT(itFind != m_kSortMap.End() && itFind->m_tSecond < m_kEventSlotArray.Size());
		VeUInt32 u32Index(itFind->m_tSecond);
		VeRefList<VeTimeEvent*>* pkList = m_kEventSlotArray[u32Index];
		VE_ASSERT(pkNodeList == pkList);
		m_kSortMap.Erase(itFind);
		DestoryNodeList(pkList);
		if(u32Index < (m_kEventSlotArray.Size() - 1))
		{
			VE_ASSERT(m_kEventSlotArray.Back()->Size());
			m_kEventSlotArray[u32Index] = m_kEventSlotArray.Back();
			VeTimeEvent* pkEvent = m_kEventSlotArray.Back()->GetHeadNode()->m_tContent;
			m_kSortMap[pkEvent->m_u64ExecuteTime] = u32Index;
		}
		m_kEventSlotArray.PopBack();
		VE_ASSERT(m_kSortMap.Size() == m_kEventSlotArray.Size());
	}
	pkEvent->m_pkParent = NULL;
	pkEvent->DecRefCount();
}
//--------------------------------------------------------------------------
void VeTimer::Tick(VeUInt64 u64Current)
{
	while(m_kSortMap.Size())
	{
		VeMap<VeUInt64,VeUInt32>::iterator it = m_kSortMap.Begin();
		if(it->m_tFirst <= u64Current)
		{
			VeUInt32 u32Index(it->m_tSecond);
			VeRefList<VeTimeEvent*>* pkList = m_kEventSlotArray[u32Index];
			while(pkList->Size())
			{
				VeTimeEvent* pkEvent = pkList->GetHeadNode()->m_tContent;
				pkEvent->m_kNode.Detach();
				pkEvent->m_pkParent = NULL;
				pkEvent->m_kEvent.Callback(pkEvent);
				pkEvent->DecRefCount();
			}
			m_kSortMap.Erase(it);
			DestoryNodeList(pkList);
			if(u32Index < (m_kEventSlotArray.Size() - 1))
			{
				VE_ASSERT(m_kEventSlotArray.Back()->Size());
				m_kEventSlotArray[u32Index] = m_kEventSlotArray.Back();
				VeTimeEvent* pkEvent = m_kEventSlotArray.Back()->GetHeadNode()->m_tContent;
				m_kSortMap[pkEvent->m_u64ExecuteTime] = u32Index;
			}
			m_kEventSlotArray.PopBack();
			VE_ASSERT(m_kSortMap.Size() == m_kEventSlotArray.Size());
		}
		else
		{
			break;
		}
	}
}
//--------------------------------------------------------------------------
VeRefList<VeTimeEvent*>* VeTimer::CreateNodeList()
{
	return new(VePoolMalloc(VePoolAllocator::GetPoolAllocator(sizeof(VeRefList<VeTimeEvent*>))))
		VeRefList<VeTimeEvent*>();
}
//--------------------------------------------------------------------------
void VeTimer::DestoryNodeList(VeRefList<VeTimeEvent*>* pkList)
{
	VE_ASSERT(pkList);
	pkList->~VeRefList<VeTimeEvent*>();
	VePoolFree(VePoolAllocator::GetPoolAllocator(sizeof(VeRefList<VeTimeEvent*>)), pkList);
}
//--------------------------------------------------------------------------
