////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMap.h
//  Version:     v1.00
//  Created:     27/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class TKEY>
class VeCompareFunctor
{
public:
	static VeInt32 Compare(TKEY tKeyL, TKEY tKeyR)
	{
		return tKeyL < tKeyR ? 1 : (tKeyL > tKeyR ? -1 : 0);
	}

};

template < class TKEY, class TVAL, class TFUNC = VeCompareFunctor<TKEY> >
class VeMap : public VeMemObject
{
public:
	struct Node;

	struct Level
	{
		Level() : m_pkPre(NULL), m_pkNext(NULL), m_u32Span(0) {}
		Node* m_pkPre;
		Node* m_pkNext;
		VeUInt32 m_u32Span;
	};

	struct Node
	{
		Node() : m_pkPre(NULL), m_pkNext(NULL) {}

		Node(TKEY& tKey, TVAL& tVal) : m_kData(tKey, tVal), m_pkPre(NULL), m_pkNext(NULL) {}

		VePair<const TKEY,TVAL> m_kData;
		Node* m_pkPre;
		Node* m_pkNext;
		VeVector<Level> m_kLevels;
	};

	struct Region
	{
		Region()
			: m_pkBegin(NULL), m_pkEnd(NULL), m_u32Index(VE_INFINITE) {}
		Region(Node* pkBegin, Node* pkEnd, VeUInt32 u32Level)
			: m_pkBegin(pkBegin), m_pkEnd(pkEnd), m_u32Index(u32Level) {}
		Node* m_pkBegin;
		Node* m_pkEnd;
		VeUInt32 m_u32Index;
	};

	class const_iterator
	{
	public:
		const_iterator()
		{
			m_pkNode = NULL;
		}

		const_iterator(Node* pkNode)
		{
			m_pkNode = pkNode;
		}

		bool operator == (const const_iterator& iter) const
		{
			return iter.m_pkNode == m_pkNode;
		}

		bool operator != (const const_iterator& iter) const
		{
			return iter.m_pkNode != m_pkNode;
		}

		const VePair<const TKEY,TVAL>& operator * () const
		{
			VE_ASSERT(m_pkNode);
			return m_pkNode->m_kData;
		}

		const VePair<const TKEY,TVAL>* operator -> () const
		{
			VE_ASSERT(m_pkNode);
			return &(m_pkNode->m_kData);
		}

		const_iterator& operator ++ ()
		{
			VE_ASSERT(m_pkNode);
			m_pkNode = m_pkNode->m_pkNext;
			return *this;
		}

		const_iterator operator ++ (int)
		{
			VE_ASSERT(m_pkNode);
			const_iterator itRes(m_pkNode);
			m_pkNode = m_pkNode->m_pkNext;
			return itRes;
		}

		const_iterator& operator -- ()
		{
			VE_ASSERT(m_pkNode);
			m_pkNode = m_pkNode->m_pkPre;
			return *this;
		}

		const_iterator operator -- (int)
		{
			VE_ASSERT(m_pkNode);
			const_iterator itRes(m_pkNode);
			m_pkNode = m_pkNode->m_pkPre;
			return itRes;
		}

		bool IsFirst() const
		{
			VE_ASSERT(m_pkNode);
			return m_pkNode->m_pkPre == NULL;
		}

		bool IsLast()
		{
			VE_ASSERT(m_pkNode);
			return m_pkNode->m_pkNext == NULL;
		}

	protected:
		friend class VeMap<TKEY,TVAL>;

		Node* m_pkNode;
	};

	class iterator : public const_iterator
	{
	public:
		iterator()
		{
		
		}

		iterator(Node* pkNode) : const_iterator(pkNode)
		{

		}

		VePair<const TKEY,TVAL>& operator * ()
		{
			VE_ASSERT(this->m_pkNode);
			return this->m_pkNode->m_kData;
		}

		VePair<const TKEY,TVAL>* operator -> ()
		{
			VE_ASSERT(this->m_pkNode);
			return &(this->m_pkNode->m_kData);
		}

		iterator& operator ++ ()
		{
			VE_ASSERT(this->m_pkNode);
			this->m_pkNode = this->m_pkNode->m_pkNext;
			return *this;
		}

		iterator operator ++ (int)
		{
			VE_ASSERT(this->m_pkNode);
			iterator itRes(this->m_pkNode);
			this->m_pkNode = this->m_pkNode->m_pkNext;
			return itRes;
		}

		iterator& operator -- ()
		{
			VE_ASSERT(this->m_pkNode);
			this->m_pkNode = this->m_pkNode->m_pkPre;
			return *this;
		}

		iterator operator -- (int)
		{
			VE_ASSERT(this->m_pkNode);
			iterator itRes(this->m_pkNode);
			this->m_pkNode = this->m_pkNode->m_pkPre;
			return itRes;
		}
	};

	VeMap(VePoolAllocatorPtr spAllocator = NULL)
		: m_u32Size(0), m_pkHead(NULL), m_pkTail(NULL)
	{
		SetAllocator(spAllocator);
		m_kLevels.Resize(1);
		m_kLevels[0].m_u32Span = 0;
	}

	~VeMap()
	{
		Clear();
	}

	VeUInt32 Size() const
	{
		return m_u32Size;
	}

	bool Empty() const
	{
		return m_u32Size == 0;
	}

	void Clear()
	{
		m_u32Size = 0;
		m_kLevels.Resize(1);
		m_kLevels[0].m_pkPre = NULL;
		m_kLevels[0].m_pkNext = NULL;
		m_kLevels[0].m_u32Span = 0;
		Node* pkIter(m_pkHead);
		while(pkIter)
		{
			Node* pkCurrent = pkIter;
			pkIter = pkIter->m_pkNext;
			DestoryNode(pkCurrent);
		}
		m_pkHead = NULL;
		m_pkTail = NULL;
	}

	VePair<TKEY,TVAL>& Front()
	{
		VE_ASSERT(m_u32Size);
		return m_pkHead->m_kData;
	}

	const VePair<TKEY,TVAL>& Front() const
	{
		VE_ASSERT(m_u32Size);
		return m_pkHead->m_kData;
	}

	VePair<TKEY,TVAL>& Back()
	{
		VE_ASSERT(m_u32Size);
		return m_pkTail->m_kData;
	}

	const VePair<TKEY,TVAL>& Back() const
	{
		VE_ASSERT(m_u32Size);
		return m_pkTail->m_kData;
	}

	iterator Begin()
	{
		return iterator(m_pkHead);
	}

	const_iterator Begin() const
	{
		return const_iterator(m_pkHead);
	}

	iterator Last()
	{
		return iterator(m_pkTail);
	}

	const_iterator Last() const
	{
		return const_iterator(m_pkTail);
	}

	iterator End()
	{
		return iterator(NULL);
	}

	const_iterator End() const
	{
		return const_iterator(NULL);
	}

	iterator Find(TKEY tKey)
	{
		return iterator(FindNode(tKey));
	}
	
	const_iterator Find(TKEY tKey) const
	{
		return const_iterator(FindNode(tKey));
	}

	TVAL& operator [] (TKEY tKey)
	{
		Node* pkNode = FindNode(tKey);
		if(pkNode)
		{
			return pkNode->m_kData.m_tSecond;
		}
		else
		{
			TVAL kInit;
			VeInitType(kInit);
			iterator it = Insert(tKey, kInit);
			return it->m_tSecond;
		}
	}

	iterator Insert(TKEY tKey, TVAL tVal, bool bOverWrite = true)
	{
		VeVector<Region> kPathStack;
		Node* pkIter(NULL);
		VeUInt32 u32Level = m_kLevels.Size();
		while(u32Level)
		{
			VeUInt32 u32Index = u32Level - 1;
			if(u32Level == m_kLevels.Size())
			{
				VE_ASSERT(kPathStack.Empty());
				pkIter = m_kLevels[u32Index].m_pkNext;
			}
			while(pkIter)
			{
				VE_ASSERT(pkIter->m_kLevels.Size() >= u32Level);
				VeInt32 i32ResComp = TFUNC::Compare(tKey, pkIter->m_kData.m_tFirst);
				if(i32ResComp > 0)
				{
					break;
				}
				else if(i32ResComp < 0)
				{
					pkIter = pkIter->m_kLevels[u32Index].m_pkNext;
					continue;
				}
				else
				{
					if(bOverWrite)
					{
						pkIter->m_kData.m_tSecond = tVal;
					}
					return iterator(pkIter);
				}
			}
			Node* pkBefore(pkIter ? pkIter->m_kLevels[u32Index].m_pkPre : m_kLevels[u32Index].m_pkPre);
			Node* pkAfter(pkIter);
			kPathStack.PushBack(Region(pkBefore, pkAfter, u32Index));
			if(pkBefore)
			{
				pkIter = pkBefore;
			}
			else if(u32Index)
			{
				pkIter = m_kLevels[u32Index - 1].m_pkNext;
			}
			else
			{
				pkIter = pkBefore;
			}
			--u32Level;
		}
		if(!pkIter)
		{
			pkIter = m_pkHead;
		}
		while(pkIter)
		{
			VeInt32 i32ResComp = TFUNC::Compare(tKey, pkIter->m_kData.m_tFirst);
			if(i32ResComp > 0)
			{
				break;
			}
			else if(i32ResComp < 0)
			{
				pkIter = pkIter->m_pkNext;
				continue;
			}
			else
			{
				if(bOverWrite)
				{
					pkIter->m_kData.m_tSecond = tVal;
				}
				return iterator(pkIter);
			}
		}
		Node* pkNode = CreateNode(tKey, tVal);
		AttachBefore(pkNode, pkIter);
		if(kPathStack.Size())
		{
			for(VeUInt32 i(kPathStack.Size() - 1); i < kPathStack.Size(); --i)
			{
				Region& kRegion = kPathStack[i];
				Level& kEndLevel = kRegion.m_pkEnd ? kRegion.m_pkEnd->m_kLevels[kRegion.m_u32Index] : m_kLevels[kRegion.m_u32Index];
				if(kEndLevel.m_u32Span == 2)
				{
					Node* pkSkipKey(NULL);
					if(kRegion.m_pkBegin)
					{
						if(kRegion.m_u32Index)
						{
							pkSkipKey = kRegion.m_pkBegin->m_kLevels[kRegion.m_u32Index - 1].m_pkNext->m_kLevels[kRegion.m_u32Index - 1].m_pkNext;
						}
						else
						{
							pkSkipKey = kRegion.m_pkBegin->m_pkNext->m_pkNext;
						}
					}
					else if(kRegion.m_u32Index)
					{
						pkSkipKey = m_kLevels[kRegion.m_u32Index - 1].m_pkNext->m_kLevels[kRegion.m_u32Index - 1].m_pkNext;
					}
					else
					{
						pkSkipKey = m_pkHead->m_pkNext;
					}
					VE_ASSERT(pkSkipKey && pkSkipKey->m_kLevels.Size() == kRegion.m_u32Index);
					pkSkipKey->m_kLevels.Increase();
					Level& kKeyLevel = pkSkipKey->m_kLevels.Back();
					kKeyLevel.m_u32Span = 1;
					kEndLevel.m_u32Span = 1;
					kKeyLevel.m_pkPre = kRegion.m_pkBegin;
					kKeyLevel.m_pkNext = kRegion.m_pkEnd;
					if(kKeyLevel.m_pkPre)
					{
						kKeyLevel.m_pkPre->m_kLevels[kRegion.m_u32Index].m_pkNext = pkSkipKey;
					}
					else
					{
						m_kLevels[kRegion.m_u32Index].m_pkNext = pkSkipKey;
					}
					if(kKeyLevel.m_pkNext)
					{
						kKeyLevel.m_pkNext->m_kLevels[kRegion.m_u32Index].m_pkPre = pkSkipKey;
					}
					else
					{
						m_kLevels[kRegion.m_u32Index].m_pkPre = pkSkipKey;
					}
					if(pkSkipKey->m_kLevels.Size() == m_kLevels.Size())
					{
						m_kLevels.Increase();
						m_kLevels.Back().m_u32Span = 1;
						break;
					}
				}
				else
				{
					VE_ASSERT(kEndLevel.m_u32Span < 2);
					++kEndLevel.m_u32Span;
					break;
				}
			}
		}
		return iterator(pkNode);
	}

	iterator Erase(const_iterator itLoc)
	{
		return iterator(Erase(itLoc.m_pkNode));
	}

	void Print()
	{
		if(m_u32Size)
		{
			{
				VeString kLog = VeString::From(m_pkHead->m_kData.m_tFirst);
				Node* pkIter = m_pkHead->m_pkNext;
				while(pkIter)
				{
					kLog += ",";
					kLog += VeString::From(pkIter->m_kData.m_tFirst);
					pkIter = pkIter->m_pkNext;
				}
				VeDebugOutput(kLog);
			}
			for(VeUInt32 i(0); i < m_kLevels.Size(); ++i)
			{
				VeString kLog;
				Node* pkIter = m_kLevels[i].m_pkNext;
				while(pkIter)
				{
					kLog += "(" + VeString::From(pkIter->m_kData.m_tFirst) + "," + VeString::From(pkIter->m_kLevels[i].m_u32Span) + "),";
					pkIter = pkIter->m_kLevels[i].m_pkNext;
				}
				kLog += "(end," + VeString::From(m_kLevels[i].m_u32Span) + ")";
				VeDebugOutput(kLog);
			}
		}
	}

private:
	void RemoveLevel(Node* pkNode, VeUInt32 u32Max)
	{
		VeVector<Node*> kPathList;
		VeVector< VePair<Node*,VeUInt32> > kNodeList;
		for(VeInt32 i(pkNode->m_kLevels.Size()); i >= VeInt32(u32Max); --i)
		{
			Node* pkNextHighLevelNode(NULL);
			if(i)
			{
				VeUInt32 u32Level = i - 1;
				Node* pkNextLevelNode = pkNode->m_kLevels[u32Level].m_pkNext;
				Level& kNextLevel = pkNextLevelNode ? pkNextLevelNode->m_kLevels[u32Level] : m_kLevels[u32Level];
				kNextLevel.m_u32Span += pkNode->m_kLevels[u32Level].m_u32Span + 1;
				pkNextHighLevelNode = pkNextLevelNode;
				while(pkNextHighLevelNode)
				{
					if(pkNextHighLevelNode->m_kLevels.Size() > VeUInt32(i))
					{
						break;
					}
					else
					{
						pkNextHighLevelNode = pkNextHighLevelNode->m_kLevels[u32Level].m_pkNext;
					}
				}
				if(pkNode->m_kLevels[u32Level].m_pkPre)
				{
					pkNode->m_kLevels[u32Level].m_pkPre->m_kLevels[u32Level].m_pkNext = pkNode->m_kLevels[u32Level].m_pkNext;
				}
				else
				{
					m_kLevels[u32Level].m_pkNext = pkNode->m_kLevels[u32Level].m_pkNext;
				}
				if(pkNode->m_kLevels[u32Level].m_pkNext)
				{
					pkNode->m_kLevels[u32Level].m_pkNext->m_kLevels[u32Level].m_pkPre = pkNode->m_kLevels[u32Level].m_pkPre;
				}
				else
				{
					m_kLevels[u32Level].m_pkPre = pkNode->m_kLevels[u32Level].m_pkPre;
				}
				Level& kNextHighLevel = pkNextHighLevelNode ? pkNextHighLevelNode->m_kLevels[i] : m_kLevels[i];
				--kNextHighLevel.m_u32Span;
				kPathList.PushBack(pkNextHighLevelNode);
				if(kNextLevel.m_u32Span > 2)
				{
					kNodeList.PushBack(VePair<Node*,VeUInt32>(pkNextLevelNode, u32Level));
				}
			}
			else
			{
				pkNextHighLevelNode = pkNode->m_pkNext;
				while(pkNextHighLevelNode)
				{
					if(pkNextHighLevelNode->m_kLevels.Size())
					{
						break;
					}
					else
					{
						pkNextHighLevelNode = pkNextHighLevelNode->m_pkNext;
					}
				}
				if(pkNode->m_pkPre)
				{
					pkNode->m_pkPre->m_pkNext = pkNode->m_pkNext;
				}
				else
				{
					m_pkHead = pkNode->m_pkNext;
				}
				if(pkNode->m_pkNext)
				{
					pkNode->m_pkNext->m_pkPre = pkNode->m_pkPre;
				}
				else
				{
					m_pkTail = pkNode->m_pkPre;
				}
				Level& kNextHighLevel = pkNextHighLevelNode ? pkNextHighLevelNode->m_kLevels[i] : m_kLevels[i];
				--kNextHighLevel.m_u32Span;
				kPathList.PushBack(pkNextHighLevelNode);
			}
		}
		if(u32Max)
		{
			pkNode->m_kLevels.Resize(u32Max - 1);
		}
		else
		{
			pkNode->m_kLevels.Clear();
		}
        for(VeUInt32 i(0); i < kNodeList.Size(); ++i)
        {
            VePair<Node*,VeUInt32>& kPair = kNodeList[i];
            Level& kNextLevel = kPair.m_tFirst ? kPair.m_tFirst->m_kLevels[kPair.m_tSecond] : m_kLevels[kPair.m_tSecond];
			if(kNextLevel.m_u32Span > 2)
			{
				RaiseLevel(kPair.m_tFirst, kPair.m_tSecond);
			}
        }
		for(VeUInt32 i(0); i < kPathList.Size(); ++i)
		{	
			VeUInt32 u32Index = kPathList.Size() - 1 - i;
			VeUInt32 u32Level = u32Max + i;
			Node* pkNextHighLevelNode = kPathList[u32Index];
			Level& kNextHighLevel = pkNextHighLevelNode ? pkNextHighLevelNode->m_kLevels[u32Level] : m_kLevels[u32Level];
			if(kNextHighLevel.m_u32Span == 0)
			{
				if(pkNextHighLevelNode)
				{
					RemoveLevel(pkNextHighLevelNode, u32Level + 1);
				}
				else if(kNextHighLevel.m_pkPre)
				{
					RemoveLevel(kNextHighLevel.m_pkPre, u32Level + 1);
				}
				else
				{
					m_kLevels.Resize(u32Level + 1);
				}
			}
			else if(kNextHighLevel.m_u32Span > 2)
			{
				VE_ASSERT(kNextHighLevel.m_u32Span <= 5);
				RaiseLevel(pkNextHighLevelNode, u32Level);
			}
		}
	}

	void RaiseLevel(Node* pkNode, VeUInt32 u32Level)
	{
		Level& kLevel = pkNode ? pkNode->m_kLevels[u32Level] : m_kLevels[u32Level];
		VeUInt32 u32Span = kLevel.m_u32Span;
		VE_ASSERT(u32Span > 2 && u32Span <= 5);
		Node* pkSkipKey(NULL);
		if(u32Span >= 5)
		{
			if(u32Level)
			{
				Level& kDown = pkNode ? pkNode->m_kLevels[u32Level - 1] : m_kLevels[u32Level - 1];
				pkSkipKey = kDown.m_pkPre->m_kLevels[u32Level - 1].m_pkPre->m_kLevels[u32Level - 1].m_pkPre;
			}
			else
			{
				pkSkipKey = pkNode ? pkNode->m_pkPre->m_pkPre->m_pkPre : m_pkTail->m_pkPre->m_pkPre;
			}
			kLevel.m_u32Span = 2;
		}
		else
		{
			if(u32Level)
			{
				Level& kDown = pkNode ? pkNode->m_kLevels[u32Level - 1] : m_kLevels[u32Level - 1];
				pkSkipKey = kDown.m_pkPre->m_kLevels[u32Level - 1].m_pkPre;
			}
			else
			{
				pkSkipKey = pkNode ? pkNode->m_pkPre->m_pkPre : m_pkTail->m_pkPre;
			}
			kLevel.m_u32Span = 1;
		}
		VE_ASSERT(pkSkipKey && pkSkipKey->m_kLevels.Size() == u32Level);
		pkSkipKey->m_kLevels.Increase();
		Level& kKeyLevel = pkSkipKey->m_kLevels.Back();
		kKeyLevel.m_u32Span = u32Span == 3 ? 1 : 2;
		kKeyLevel.m_pkPre = kLevel.m_pkPre;
		kKeyLevel.m_pkNext = pkNode;
		if(kKeyLevel.m_pkPre)
		{
			kKeyLevel.m_pkPre->m_kLevels[u32Level].m_pkNext = pkSkipKey;
		}
		else
		{
			m_kLevels[u32Level].m_pkNext = pkSkipKey;
		}
		if(kKeyLevel.m_pkNext)
		{
			kKeyLevel.m_pkNext->m_kLevels[u32Level].m_pkPre = pkSkipKey;
		}
		else
		{
			m_kLevels[u32Level].m_pkPre = pkSkipKey;
		}
		if(pkSkipKey->m_kLevels.Size() == m_kLevels.Size())
		{
			m_kLevels.Increase();
			m_kLevels.Back().m_u32Span = 1;
		}
		Node* pkNextHighLevelNode = pkNode;
		while(pkNextHighLevelNode)
		{
			if(pkNextHighLevelNode->m_kLevels.Size() > pkSkipKey->m_kLevels.Size())
			{
				break;
			}
			else
			{
				pkNextHighLevelNode = pkNextHighLevelNode->m_kLevels[u32Level].m_pkNext;
			}
		}
		Level& kNextHighLevel = pkNextHighLevelNode ? pkNextHighLevelNode->m_kLevels[u32Level + 1] : m_kLevels[u32Level + 1];
		if((++kNextHighLevel.m_u32Span) > 2)
		{
			RaiseLevel(pkNextHighLevelNode, u32Level + 1);
		}
	}

	Node* Erase(Node* pkNode)
	{
		Node* pkRes(NULL);
		if(pkNode)
		{
			pkRes = pkNode->m_pkNext;
			RemoveLevel(pkNode, 0);
			DestoryNode(pkNode);
			--m_u32Size;
		}
		return pkRes;
	}

	Node* FindNode(TKEY tKey)
	{
		Node* pkIter(NULL);
		VeUInt32 u32Level = m_kLevels.Size();
		while(u32Level)
		{
			VeUInt32 u32Index = u32Level - 1;
			if(u32Level == m_kLevels.Size())
			{
				pkIter = m_kLevels[u32Index].m_pkNext;
			}
			while(pkIter)
			{
				VE_ASSERT(pkIter->m_kLevels.Size() >= u32Level);
				VeInt32 i32ResComp = TFUNC::Compare(tKey, pkIter->m_kData.m_tFirst);
				if(i32ResComp > 0)
				{
					break;
				}
				else if(i32ResComp < 0)
				{
					pkIter = pkIter->m_kLevels[u32Index].m_pkNext;
					continue;
				}
				else
				{
					return pkIter;
				}
			}
			Node* pkBefore(pkIter ? pkIter->m_kLevels[u32Index].m_pkPre : m_kLevels[u32Index].m_pkPre);
			if(pkBefore)
			{
				pkIter = pkBefore;
			}
			else if(u32Index)
			{
				pkIter = m_kLevels[u32Index - 1].m_pkNext;
			}
			else
			{
				pkIter = pkBefore;
			}
			--u32Level;
		}
		if(!pkIter)
		{
			pkIter = m_pkHead;
		}
		while(pkIter)
		{
			VeInt32 i32ResComp = TFUNC::Compare(tKey, pkIter->m_kData.m_tFirst);
			if(i32ResComp > 0)
			{
				break;
			}
			else if(i32ResComp < 0)
			{
				pkIter = pkIter->m_pkNext;
				continue;
			}
			else
			{
				return pkIter;
			}
		}
		return NULL;
	}

	void AttachBefore(Node* pkNode, Node* pkAfter)
	{
		VE_ASSERT(pkNode);
		if(pkAfter)
		{
			pkNode->m_pkPre = pkAfter->m_pkPre;
			pkNode->m_pkNext = pkAfter;
		}
		else
		{
			pkNode->m_pkPre = m_pkTail;
			pkNode->m_pkNext = NULL;
		}
		if(pkNode->m_pkNext)
		{
			pkNode->m_pkNext->m_pkPre = pkNode;
		}
		else
		{
			m_pkTail = pkNode;
		}
		if(pkNode->m_pkPre)
		{
			pkNode->m_pkPre->m_pkNext = pkNode;
		}
		else
		{
			m_pkHead = pkNode;
		}
		++m_u32Size;
	}

	Node* CreateNode(TKEY tKey, TVAL tVal)
	{
		return new(VePoolMalloc(m_spAllocator)) Node(tKey, tVal);
	}

	void DestoryNode(Node* pkNode)
	{
		VE_ASSERT(pkNode);
		pkNode->~Node();
		VePoolFree(m_spAllocator,pkNode);
	}

	void SetAllocator(const VePoolAllocatorPtr& spAlloc)
	{
		if(spAlloc)
		{
			VE_ASSERT(spAlloc->GetObjectSize() == sizeof(Node));
			m_spAllocator = spAlloc;
		}
		else
		{
			m_spAllocator = VePoolAllocator::GetPoolAllocator(sizeof(Node));
		}
	}

	VeUInt32 m_u32Size;
	Node* m_pkHead;
	Node* m_pkTail;
	VeVector<Level> m_kLevels;
	VePoolAllocatorPtr m_spAllocator;

};
