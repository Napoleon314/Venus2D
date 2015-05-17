////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeList.h
//  Version:     v1.00
//  Created:     28/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class T>
class VeList : public VeMemObject
{
public:
	struct Node
	{
		Node* m_pkPre;
		Node* m_pkNext;
		T m_tValue;
	};

	class const_iterator
	{
	public:
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

		const T& operator * () const
		{
			VE_ASSERT(m_pkNode);
			return m_pkNode->m_tValue;
		}

		const T* operator -> () const
		{
			VE_ASSERT(m_pkNode);
			return &(m_pkNode->m_tValue);
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
		friend class VeList<T>;

		Node* m_pkNode;
	};

	class iterator : public const_iterator
	{
	public:
		iterator(Node* pkNode) : const_iterator(pkNode)
		{

		}

		T& operator * ()
		{
			VE_ASSERT(this->m_pkNode);
			return this->m_pkNode->m_tValue;
		}

		T* operator -> ()
		{
			VE_ASSERT(this->m_pkNode);
			return &(this->m_pkNode->m_tValue);
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

	VeList(VePoolAllocatorPtr spAlloc = NULL)
	{
		SetAllocator(spAlloc);
		m_pkHead = NULL;
		m_pkLast = NULL;
		m_u32Size = 0;
	}

	VeList(const VeList<T>& kList, VePoolAllocatorPtr spAlloc = NULL)
	{
		SetAllocator(spAlloc);
		m_pkHead = NULL;
		m_pkLast = NULL;
		m_u32Size = 0;
		CopyFrom(kList);
	}

	VeList(const_iterator itStart, const_iterator itLast, VePoolAllocatorPtr spAlloc = NULL)
	{
		SetAllocator(spAlloc);
		m_pkHead = NULL;
		m_pkLast = NULL;
		m_u32Size = 0;
		CopyFrom(itStart, itLast);
	}

	~VeList()
	{
		Clear();
	}

	VeList<T>& operator = (const VeList<T>& kList)
	{
		CopyFrom(kList);
		return *this;
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
		Node* pkNode = m_pkHead;
		while(pkNode)
		{
			Node* pkNext = pkNode->m_pkNext;
			pkNode->~Node();
			VePoolFree(m_spAllocator,pkNode);
			pkNode = pkNext;
		}
		m_pkHead = NULL;
		m_pkLast = NULL;
		m_u32Size = 0;
	}

	T& Front()
	{
		VE_ASSERT(m_u32Size);
		return *Begin();
	}

	const T& Front() const
	{
		VE_ASSERT(m_u32Size);
		return *Begin();
	}

	T& Back()
	{
		VE_ASSERT(m_u32Size);
		return *Last();
	}

	const T& Back() const
	{
		VE_ASSERT(m_u32Size);
		return *Last();
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
		return iterator(m_pkLast);
	}

	const_iterator Last() const
	{
		return const_iterator(m_pkLast);
	}

	iterator End()
	{
		return iterator(NULL);
	}

	const_iterator End() const
	{
		return const_iterator(NULL);
	}

	void PushBack(const T& tVal)
	{
		Node* pkNode = new(VePoolMalloc(m_spAllocator)) Node;
		pkNode->m_tValue = tVal;
		pkNode->m_pkNext = NULL;
		pkNode->m_pkPre = m_pkLast;
		if(m_pkLast)
		{
			m_pkLast->m_pkNext = pkNode;
		}
		else
		{
			VE_ASSERT(!m_pkHead);
			VE_ASSERT(!m_u32Size);
			m_pkHead = pkNode;
		}
		m_pkLast = pkNode;
		++m_u32Size;
	}

	void PopBack()
	{
		if(m_u32Size)
		{
			Node* pkNode = m_pkLast;
			m_pkLast = pkNode->m_pkPre;
			if(m_pkLast)
			{
				m_pkLast->m_pkNext = NULL;
			}
			else
			{
				VE_ASSERT(m_u32Size == 1);
				m_pkHead = NULL;
			}
			pkNode->~Node();
			VePoolFree(m_spAllocator,pkNode);
			--m_u32Size;
		}
	}

	void PushFront(const T& tVal)
	{
		Node* pkNode = new(VePoolMalloc(m_spAllocator)) Node;
		pkNode->m_tValue = tVal;
		pkNode->m_pkNext = m_pkHead;
		pkNode->m_pkPre = NULL;
		if(m_pkHead)
		{
			m_pkHead->m_pkPre = pkNode;
		}
		else
		{
			VE_ASSERT(!m_pkLast);
			VE_ASSERT(!m_u32Size);
			m_pkLast = pkNode;
		}
		m_pkHead = pkNode;
		++m_u32Size;
	}

	void PopFront()
	{
		if(m_u32Size)
		{
			Node* pkNode = m_pkHead;
			m_pkHead = pkNode->m_pkNext;
			if(m_pkHead)
			{
				m_pkHead->m_pkPre = NULL;
			}
			else
			{
				VE_ASSERT(m_u32Size == 1);
				m_pkLast = NULL;
			}
			pkNode->~Node();
			VePoolFree(m_spAllocator,pkNode);
			--m_u32Size;
		}
	}

	iterator Erase(const_iterator itLoc)
	{
		Node* pkNode = itLoc.m_pkNode;
		VE_ASSERT(pkNode);
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
			m_pkLast = pkNode->m_pkPre;
		}
		iterator itRes(pkNode->m_pkNext);
		pkNode->~Node();
		VePoolFree(m_spAllocator,pkNode);
		--m_u32Size;
		return itRes;
	}

	iterator Erase(const_iterator itFirst, const_iterator itLast)
	{
		Node* pkFst = itFirst.m_pkNode;
		Node* pkLst = itLast.m_pkNode;
		VE_ASSERT(pkFst && pkLst);
		if(pkFst->m_pkPre)
		{
			pkFst->m_pkPre->m_pkNext = pkLst->m_pkNext;
		}
		else
		{
			m_pkHead = pkLst->m_pkNext;
		}
		if(pkLst->m_pkNext)
		{
			pkLst->m_pkNext->m_pkPre = pkFst->m_pkPre;
		}
		else
		{
			m_pkLast = pkFst->m_pkPre;
		}
		iterator itRes(pkLst->m_pkNext);

		{
			Node* pkNode = pkFst;
			do 
			{
				Node* pkNext = pkNode->m_pkNext;
				pkNode->~Node();
				VePoolFree(m_spAllocator,pkNode);
				--m_u32Size;
				pkNode = pkNext;
			}
			while(pkNode != pkLst->m_pkNext);
		}

		return itRes;
	}

	iterator Insert(const_iterator itLoc, const T& tVal)
	{
		if(itLoc == End())
		{
			PushBack(tVal);
			return Last();
		}
		else
		{
			Node* pkNode = new(VePoolMalloc(m_spAllocator)) Node;
			pkNode->m_tValue = tVal;
			pkNode->m_pkNext = itLoc.m_pkNode;
			pkNode->m_pkPre = itLoc.m_pkNode->m_pkPre;
			itLoc.m_pkNode->m_pkPre = pkNode;
			if(pkNode->m_pkPre)
			{
				pkNode->m_pkPre->m_pkNext = pkNode;
			}
			else
			{
				m_pkHead = pkNode;
			}
			++m_u32Size;
			return iterator(pkNode);
		}
	}

	void Insert(const_iterator itLoc, VeUInt32 u32Num, const T& tVal)
	{
		for(VeUInt32 i(0); i < u32Num; ++i)
		{
			Insert(itLoc, tVal);
		}
	}

	void Insert(const_iterator itLoc, const_iterator itStart, const_iterator itLast)
	{
		while(true)
		{
			Insert(itLoc, itStart);
			if(itStart == itLast)
			{
				break;
			}
			else
			{
				++itStart;
			}
		}
	}

	void CopyFrom(const VeList<T>& kList)
	{
		Clear();
		if(kList.Size())
		{
			for(const_iterator it = kList.Begin(); it != kList.End(); ++it)
			{
				PushBack(*it);
			}
		}
	}

	void CopyFrom(const_iterator itStart, const_iterator itLast)
	{
		Clear();
		while(true)
		{
			PushBack(*itStart);
			if(itStart == itLast)
			{
				break;
			}
			else
			{
				++itStart;
			}
		}
	}

	const VePoolAllocatorPtr& GetAllocator()
	{
		return m_spAllocator;
	}

private:
	void SetAllocator(const VePoolAllocatorPtr& spAlloc)
	{
		if(spAlloc)
		{
			VE_ASSERT(spAlloc->GetObjectSize() == sizeof(Node));
			m_spAllocator = spAlloc;
		}
		else
		{
			m_spAllocator = VE_NEW VePoolAllocator(sizeof(Node), 32);
		}
	}

	Node* m_pkHead;
	Node* m_pkLast;
	VeUInt32 m_u32Size;
	VePoolAllocatorPtr m_spAllocator;

};
