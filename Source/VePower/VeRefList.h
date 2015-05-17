////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRefList.h
//  Version:     v1.00
//  Created:     10/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template<class> class VeRefList;

template <class T> 
class VeRefNode : public VeMemObject
{
public:
	VeRefNode()
	{
		m_pkPre = NULL;
		m_pkNext = NULL;
		m_pkList = NULL;
	}

	~VeRefNode()
	{
		Detach();
	}

	bool IsAttach() const
	{
		return (m_pkList != NULL);
	}

	bool IsAttach(const VeRefList<T>& kList) const
	{
		return (m_pkList == &kList);
	}

	void InsertBefore(VeRefNode<T>& kNode)
	{
		m_pkList->AttachBefore(*this, kNode);
	}

	void InsertAfter(VeRefNode<T>& kNode)
	{
		m_pkList->AttachAfter(*this, kNode);
	}

	VeRefNode* Next() const
	{
		return m_pkNext;
	}

	VeRefNode* Pre() const
	{
		return m_pkPre;
	}

	VeRefNode* NextCyc() const
	{
		return m_pkNext ? m_pkNext : (m_pkList ? m_pkList->GetHeadNode() : NULL);
	}

	VeRefNode* PreCyc() const
	{
		return m_pkPre ? m_pkPre : (m_pkList ? m_pkList->GetLastNode() : NULL);
	}

	VeRefList<T>* GetRefList() const
	{
		return m_pkList;
	}

	void Detach()
	{
		if(m_pkList)
		{
			if(m_pkList->m_pkIter == this)
			{
				m_pkList->m_pkIter = Next();
			}

			if(m_pkPre)
			{
				m_pkPre->m_pkNext = m_pkNext;
			}
			else
			{
				m_pkList->m_pkHead = m_pkNext;
			}
			if(m_pkNext)
			{
				m_pkNext->m_pkPre = m_pkPre;
			}
			else
			{
				m_pkList->m_pkLast = m_pkPre;
			}

			--(m_pkList->m_u32Size);

			m_pkList = NULL;
			m_pkPre = NULL;
			m_pkNext = NULL;
		}
	}

	const T& GetNextContent(const T& kDefaultValue) const
	{
		if(m_pkList == NULL)
		{
			return kDefaultValue;
		}
		if(m_pkNext == NULL)
		{
			return kDefaultValue;
		}
		else
		{
			return m_pkNext->m_tContent;
		}
	}

	T& GetNextContent(T& kDefaultValue)
	{
		if(m_pkList == NULL)
		{
			return kDefaultValue;
		}
		if(m_pkNext == NULL)
		{
			return kDefaultValue;
		}
		else
		{
			return m_pkNext->m_tContent;
		}
	}

	T m_tContent;

private:
	friend class VeRefList<T>;
	VeRefNode* m_pkPre;
	VeRefNode* m_pkNext;
	VeRefList<T>* m_pkList;
};

template <class T> 
class VeRefList : public VeMemObject
{
public:
	typedef VeRefNode<T> Node;
	typedef Node* iterator;

	VeRefList()
	{
		m_pkIter = NULL;
		m_pkHead = NULL;
		m_pkLast = NULL;
		m_u32Size = 0;
	}

	~VeRefList()
	{
		Clear();
	}

	void operator = (const VeRefList<T>&)
	{

	}

	bool operator == (const VeRefList<T>&)
	{
		return false;
	}

	void AttachBack(Node& kNode)
	{
		kNode.Detach();
		kNode.m_pkList = this;
		if(m_pkLast)
		{
			m_pkLast->m_pkNext = &kNode;
			kNode.m_pkPre = m_pkLast;
		}
		else
		{
			m_pkHead = &kNode;
		}
		m_pkLast = &kNode;
		++m_u32Size;
	}

	void AttachFront(Node& kNode)
	{
		kNode.Detach();
		kNode.m_pkList = this;
		if(m_pkHead)
		{
			m_pkHead->m_pkPre = &kNode;
			kNode.m_pkNext = m_pkHead;
		}
		else
		{
			m_pkLast = &kNode;
		}
		m_pkHead = &kNode;
		++m_u32Size;
	}

	void AttachAfter(Node& kFront, Node& kNew)
	{
		VE_ASSERT(kFront.IsAttach(*this));
		kNew.Detach();
		kNew.m_pkList = this;
		kNew.m_pkPre = &kFront;
		kNew.m_pkNext = kFront.m_pkNext;
		kFront.m_pkNext = &kNew;
		if(kNew.m_pkNext)
		{
			kNew.m_pkNext->m_pkPre = &kNew;
		}
		else
		{
			m_pkLast = &kNew;
		}
		++m_u32Size;
	}

	void AttachBefore(Node& kAfter, Node& kNew)
	{
		VE_ASSERT(kAfter.IsAttach(*this));
		kNew.Detach();
		kNew.m_pkList = this;
		kNew.m_pkPre = kAfter.m_pkPre;
		kNew.m_pkNext = &kAfter;
		kAfter.m_pkPre = &kNew;
		if(kNew.m_pkPre)
		{
			kNew.m_pkPre->m_pkNext = &kNew;
		}
		else
		{
			m_pkHead = &kNew;
		}
		++m_u32Size;
	}

	void BeginIterator() const
	{
		m_pkIter = m_pkHead;
	}

	void BeginIteratorFromLast() const
	{
		m_pkIter = m_pkLast;
	}

	void Pre() const
	{
		VE_ASSERT(m_pkIter);
		m_pkIter = m_pkIter->m_pkPre;
	}

	void Next() const
	{
		VE_ASSERT(m_pkIter);
		m_pkIter = m_pkIter->m_pkNext;
	}

	void EndIterator() const
	{
		m_pkIter = NULL;
	}

	bool IsEnd()const
	{
		return m_pkIter ? false : true;
	}

	VeRefNode<T>* GetIterNode() const
	{
		return m_pkIter;
	}

	VeRefNode<T>* GetHeadNode() const
	{
		return m_pkHead;
	}

	VeRefNode<T>* GetLastNode() const
	{
		return m_pkLast;
	}

	void Clear()
	{
		Node* pkNode = m_pkHead;
		while(pkNode)
		{
			Node* pkNext = pkNode->m_pkNext;
			pkNode->m_pkList = NULL;
			pkNode->m_pkPre = NULL;
			pkNode->m_pkNext = NULL;
			pkNode = pkNext;
		}
		m_pkIter = NULL; 
		m_pkHead = NULL;
		m_pkLast = NULL;
		m_u32Size = 0;
	}

	VeUInt32 Size() const
	{
		return m_u32Size;
	}

	bool Empty() const
	{
		return m_u32Size == 0;
	}

	static iterator Next(iterator& iter)
	{
		VE_ASSERT(iter);
		return iter->Next();
	}

	static iterator Pre(iterator& iter)
	{
		VE_ASSERT(iter);
		return iter->Pre();
	}

	static bool IsEnd(iterator& iter)
	{
		return iter ? false : true;
	}

private:
	friend class VeRefNode<T>;

	VeRefList(const VeRefList<T>&)
	{
		m_pkIter = NULL;
		m_pkHead = NULL;
		m_pkLast = NULL;
		m_u32Size = 0;
	}

	mutable iterator m_pkIter;
	Node* m_pkHead;
	Node* m_pkLast;
	VeUInt32 m_u32Size;

};
