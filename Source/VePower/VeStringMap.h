////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeStringMap.h
//  Version:     v1.00
//  Created:     25/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class TVAL>
class VeStringMap : public VeMemObject
{
public:
	struct Node
	{
		Node* m_pkNext;
		VeUInt32 m_u32HashCode;
		VeFixedString m_tKey;
		TVAL m_tVal;
#		ifdef VE_DEBUG
		Node() : m_kPair(m_tKey, m_tVal)
		{
			m_kDebugNode.m_tContent = this;
		}
		VeRefNode<Node*> m_kDebugNode;
		VePair<VeFixedString&, TVAL&> m_kPair;
#		endif
	};

	typedef const TVAL* const_iterator;
	typedef TVAL* iterator;

	VeStringMap(VeUInt32 u32TableSize = 32, VePoolAllocatorPtr spAllocator = NULL) : m_u32Size(0)
	{
		SetAllocator(spAllocator);
		m_kHashTable.Resize(u32TableSize);
		for(VeUInt32 i(0); i < m_kHashTable.Size(); ++i)
		{
			m_kHashTable[i] = NULL;
		}
	}

	~VeStringMap()
	{
		Clear();
	}

	bool Insert(const VeChar8* pcKey, TVAL tVal, bool bOverWrite = true)
	{
		VeUInt32 u32HashCode = VeString::KeyToHashCode(pcKey, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tKey == pcKey)
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
		pkSlot->m_tKey = pcKey;
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

	TVAL* Find(const VeChar8* pcKey)
	{
		Node* pkNode = FindNode(pcKey);
		return pkNode ? &(pkNode->m_tVal) : NULL;
	}

	const TVAL* Find(const VeChar8* pcKey) const
	{
		const Node* pkNode = FindNode(pcKey);
		return pkNode ? &(pkNode->m_tVal) : NULL;
	}

	bool Remove(const VeChar8* pcKey)
	{
		VeUInt32 u32HashCode = VeString::KeyToHashCode(pcKey, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tKey == pcKey)
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

	TVAL& operator [] (const VeChar8* pcKey)
	{
		VeUInt32 u32HashCode = VeString::KeyToHashCode(pcKey, m_kHashTable.Size());
		VE_ASSERT(u32HashCode < m_kHashTable.Size());
		Node* pkSlot = m_kHashTable[u32HashCode];
		Node* pkLastSlot = NULL;
		while(pkSlot)
		{
			if(pkSlot->m_tKey == pcKey)
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
		pkSlot->m_tKey = pcKey;
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
	Node* FindNode(const VeChar8* pcKey)
	{
		if(m_kHashTable.Size())
		{
			VeUInt32 u32HashCode = VeString::KeyToHashCode(pcKey, m_kHashTable.Size());
			VE_ASSERT(u32HashCode < m_kHashTable.Size());
			Node* pkSlot = m_kHashTable[u32HashCode];
			while(pkSlot)
			{
				if(pkSlot->m_tKey == pcKey)
				{
					return pkSlot;
				}
				else
				{
					pkSlot = pkSlot->m_pkNext;
				}
			}
		}
		return NULL;
	}

	const Node* FindNode(const VeChar8* pcKey) const
	{
		if(m_kHashTable.Size())
		{
			VeUInt32 u32HashCode = VeString::KeyToHashCode(pcKey, m_kHashTable.Size());
			VE_ASSERT(u32HashCode < m_kHashTable.Size());
			Node* pkSlot = m_kHashTable[u32HashCode];
			while(pkSlot)
			{
				if(pkSlot->m_tKey == pcKey)
				{
					return pkSlot;
				}
				else
				{
					pkSlot = pkSlot->m_pkNext;
				}
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
