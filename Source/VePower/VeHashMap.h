////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VePowerDefines.h
//  Version:     v1.00
//  Created:     5/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class TKEY>
class VeHashFunctor
{
public:
	static VeUInt32 KeyToHashCode(TKEY tKey, VeUInt32 u32TableSize)
	{
		return (VeUInt32)(((VeSizeT)tKey) % u32TableSize);
	}
};

template < class TVAL, class THASH = VeHashFunctor<TVAL> >
class VeHashSet : public VeMemObject
{
public:
	struct Node
	{
		Node* m_pkNext;
		VeUInt32 m_u32HashCode;
		TVAL m_tVal;
#		ifdef VE_DEBUG
		Node()
		{
			m_kDebugNode.m_tContent = this;
		}
		VeRefNode<Node*> m_kDebugNode;
#		endif
	};

	VeHashSet(VeUInt32 u32TableSize = 32, VePoolAllocatorPtr spAllocator = NULL) : m_u32Size(0)
	{
		SetAllocator(spAllocator);
		m_kHashTable.Resize(u32TableSize);
		for(VeUInt32 i(0); i < m_kHashTable.Size(); ++i)
		{
			m_kHashTable[i] = NULL;
		}
	}

	~VeHashSet()
	{
		Clear();
	}

	bool Insert(TVAL tVal)
	{
		VeUInt32 u32HashCode = THASH::KeyToHashCode(tVal, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tVal == tVal)
			{
				return false;
			}
			else
			{
				pkLastSlot = pkSlot;
				pkSlot = pkSlot->m_pkNext;
			}
		}
		pkSlot = new(VePoolMalloc(m_spAllocator)) Node;
		++m_u32Size;
		pkSlot->m_pkNext = NULL;
		pkSlot->m_u32HashCode = u32HashCode;
		pkSlot->m_tVal = tVal;
		if(pkLastSlot)
		{
			pkLastSlot->m_pkNext = pkSlot;
		}
		else
		{
			m_kHashTable[u32HashCode] = pkSlot;
		}
#		ifdef VE_DEBUG
		m_kDebugList.AttachBack(pkSlot->m_kDebugNode);
#		endif
		return true;
	}

	bool Find(TVAL tVal) const
	{
		Node* pkNode = FindNode(tVal);
		return pkNode != NULL;
	}

	bool Remove(TVAL tVal)
	{
		VeUInt32 u32HashCode = THASH::KeyToHashCode(tVal, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tVal == tVal)
			{
				if(pkLastSlot)
				{
					pkLastSlot->m_pkNext = pkSlot->m_pkNext;
				}
				else
				{
					m_kHashTable[u32HashCode] = pkSlot->m_pkNext;
				}
				pkSlot->~Node();
				VePoolFree(m_spAllocator, pkSlot);
				--m_u32Size;
				return true;
			}
			else
			{
				pkLastSlot = pkSlot;
				pkSlot = pkSlot->m_pkNext;
			}
		}
		return false;
	}

	void Clear()
	{
		for(VeUInt32 i(0); i < m_kHashTable.Size(); ++i)
		{
			Node* pkSlot = m_kHashTable[i];
			while(pkSlot)
			{
				Node* pkCurrent = pkSlot;
				pkSlot = pkCurrent->m_pkNext;
				pkCurrent->~Node();
				VePoolFree(m_spAllocator, pkCurrent);
				--m_u32Size;
			}
			m_kHashTable[i] = NULL;
		}
		VE_ASSERT(m_u32Size == 0);
	}

	bool Empty() const
	{
		return m_u32Size == 0;
	}

	VeUInt32 Size() const
	{
		return m_u32Size;
	}

	const VePoolAllocatorPtr& GetAllocator()
	{
		return m_spAllocator;
	}

private:
	Node* FindNode(TVAL tVal) const
	{
		VeUInt32 u32HashCode = THASH::KeyToHashCode(tVal, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		while(pkSlot)
		{
			if(pkSlot->m_tVal == tVal)
			{
				return pkSlot;
			}
			else
			{
				pkSlot = pkSlot->m_pkNext;
			}
		}
		return NULL;
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
			m_spAllocator = VE_NEW VePoolAllocator(sizeof(Node), 32);
		}
	}

	VeVector<Node*> m_kHashTable;
	VeUInt32 m_u32Size;
#	ifdef VE_DEBUG
	VeRefList<Node*> m_kDebugList;
#	endif

	VePoolAllocatorPtr m_spAllocator;
};

template < class TKEY, class TVAL, class THASH = VeHashFunctor<TKEY> >
class VeHashMap : public VeMemObject
{
public:
	struct Node
	{
		Node* m_pkNext;
		VeUInt32 m_u32HashCode;
		TKEY m_tKey;
		TVAL m_tVal;
#		ifdef VE_DEBUG
		Node() : m_kPair(m_tKey, m_tVal)
		{
			m_kDebugNode.m_tContent = this;
		}
		VeRefNode<Node*> m_kDebugNode;
		VePair<TKEY&, TVAL&> m_kPair;
#		endif
	};

	VeHashMap(VeUInt32 u32TableSize = 32, VePoolAllocatorPtr spAllocator = NULL) : m_u32Size(0)
	{
		SetAllocator(spAllocator);
		m_kHashTable.Resize(u32TableSize);
		for(VeUInt32 i(0); i < m_kHashTable.Size(); ++i)
		{
			m_kHashTable[i] = NULL;
		}
	}

	~VeHashMap()
	{
		Clear();
	}

	bool Insert(TKEY tKey, TVAL tVal, bool bOverWrite = true)
	{
		VeUInt32 u32HashCode = THASH::KeyToHashCode(tKey, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tKey == tKey)
			{
				if(bOverWrite)
				{
					pkSlot->m_tVal = tVal;
				}
				return false;
			}
			else
			{
				pkLastSlot = pkSlot;
				pkSlot = pkSlot->m_pkNext;
			}
		}
		pkSlot = new(VePoolMalloc(m_spAllocator)) Node;
		++m_u32Size;
		pkSlot->m_pkNext = NULL;
		pkSlot->m_u32HashCode = u32HashCode;
		pkSlot->m_tKey = tKey;
		pkSlot->m_tVal = tVal;
		if(pkLastSlot)
		{
			pkLastSlot->m_pkNext = pkSlot;
		}
		else
		{
			m_kHashTable[u32HashCode] = pkSlot;
		}
#		ifdef VE_DEBUG
		m_kDebugList.AttachBack(pkSlot->m_kDebugNode);
#		endif
		return true;
	}

	TVAL* Find(TKEY tKey)
	{
		Node* pkNode = FindNode(tKey);
		return pkNode ? &(pkNode->m_tVal) : NULL;
	}

	const TVAL* Find(TKEY tKey) const
	{
		Node* pkNode = FindNode(tKey);
		return pkNode ? &(pkNode->m_tVal) : NULL;
	}

	bool Remove(TKEY tKey)
	{
		VeUInt32 u32HashCode = THASH::KeyToHashCode(tKey, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tKey == tKey)
			{
				if(pkLastSlot)
				{
					pkLastSlot->m_pkNext = pkSlot->m_pkNext;
				}
				else
				{
					m_kHashTable[u32HashCode] = pkSlot->m_pkNext;
				}
				pkSlot->~Node();
				VePoolFree(m_spAllocator, pkSlot);
				--m_u32Size;
				return true;
			}
			else
			{
				pkLastSlot = pkSlot;
				pkSlot = pkSlot->m_pkNext;
			}
		}
		return false;
	}

	void Clear()
	{
		for(VeUInt32 i(0); i < m_kHashTable.Size(); ++i)
		{
			Node* pkSlot = m_kHashTable[i];
			while(pkSlot)
			{
				Node* pkCurrent = pkSlot;
				pkSlot = pkCurrent->m_pkNext;
				pkCurrent->~Node();
				VePoolFree(m_spAllocator, pkCurrent);
				--m_u32Size;
			}
			m_kHashTable[i] = NULL;
		}
		VE_ASSERT(m_u32Size == 0);
	}

	bool Empty() const
	{
		return m_u32Size == 0;
	}

	VeUInt32 Size() const
	{
		return m_u32Size;
	}

	TVAL& operator [] (TKEY tKey)
	{
		VeUInt32 u32HashCode = THASH::KeyToHashCode(tKey, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tKey == tKey)
			{
				return pkSlot->m_tVal;
			}
			else
			{
				pkLastSlot = pkSlot;
				pkSlot = pkSlot->m_pkNext;
			}
		}
		pkSlot = new(VePoolMalloc(m_spAllocator)) Node;
		++m_u32Size;
		pkSlot->m_pkNext = NULL;
		pkSlot->m_u32HashCode = u32HashCode;
		pkSlot->m_tKey = tKey;
		pkSlot->m_tVal = TVAL();
		if(pkLastSlot)
		{
			pkLastSlot->m_pkNext = pkSlot;
		}
		else
		{
			m_kHashTable[u32HashCode] = pkSlot;
		}
#		ifdef VE_DEBUG
		m_kDebugList.AttachBack(pkSlot->m_kDebugNode);
#		endif
		return pkSlot->m_tVal;
	}

	const VePoolAllocatorPtr& GetAllocator()
	{
		return m_spAllocator;
	}

private:
	Node* FindNode(TKEY tKey)
	{
		VeUInt32 u32HashCode = THASH::KeyToHashCode(tKey, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		while(pkSlot)
		{
			if(pkSlot->m_tKey == tKey)
			{
				return pkSlot;
			}
			else
			{
				pkSlot = pkSlot->m_pkNext;
			}
		}
		return NULL;
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

	VeVector<Node*> m_kHashTable;
	VeUInt32 m_u32Size;
#	ifdef VE_DEBUG
	VeRefList<Node*> m_kDebugList;
#	endif

	VePoolAllocatorPtr m_spAllocator;
};
