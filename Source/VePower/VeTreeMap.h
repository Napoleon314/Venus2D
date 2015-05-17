////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTreeMap.h
//  Version:     v1.00
//  Created:     29/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class TKEY, class TVAL>
class VeTreeMap : public VeMemObject
{
public:
	enum NodeColor
	{
		BLACK,
		RED
	};

	struct Node
	{
		Node* m_pkParent;
		Node* m_pkLeft;
		Node* m_pkRight;
		NodeColor m_eColor;
		TKEY m_tKey;
		TVAL m_tVal;
	};

	class const_iterator
	{
	public:
		const_iterator(Node* pkNode, TKEY& tKey, TVAL& tVal) : m_pkNode(pkNode), m_kValue(tKey, tVal)
		{
			if(pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}
		}

		bool operator == (const const_iterator& iter) const
		{
			return iter.m_pkNode == m_pkNode;
		}

		bool operator != (const const_iterator& iter) const
		{
			return iter.m_pkNode != m_pkNode;
		}

		const VePair<TKEY&, TVAL&>& operator * () const
		{
			VE_ASSERT(m_pkNode);
			return m_kValue;
		}

		const VePair<TKEY&, TVAL&>* operator -> () const
		{
			return m_pkNode ? &m_kValue : NULL;
		}

		const_iterator& operator ++ ()
		{
			VE_ASSERT(m_pkNode);
			if(m_pkNode->m_pkRight)
			{
				m_pkNode = m_pkNode->m_pkRight;
				while(m_pkNode->m_pkLeft)
				{
					m_pkNode = m_pkNode->m_pkLeft;
				}
				
			}
			else if(m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!m_pkNode->m_pkParent)
					{
						m_pkNode = NULL;
						break;
					}
					if(m_pkNode->m_pkParent->m_pkLeft == m_pkNode)
					{
						m_pkNode = m_pkNode->m_pkParent;
						break;
					}
					else
					{
						m_pkNode = m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				m_pkNode = NULL;
			}

			if(m_pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}

			return *this;
		}

		const_iterator operator ++ (int)
		{
			VE_ASSERT(m_pkNode);
			const_iterator itRes(m_pkNode, m_pkNode->m_tKey, m_pkNode->m_tVal);
			if(m_pkNode->m_pkRight)
			{
				m_pkNode = m_pkNode->m_pkRight;
				while(m_pkNode->m_pkLeft)
				{
					m_pkNode = m_pkNode->m_pkLeft;
				}

			}
			else if(m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!m_pkNode->m_pkParent)
					{
						m_pkNode = NULL;
						break;
					}
					if(m_pkNode->m_pkParent->m_pkLeft == m_pkNode)
					{
						m_pkNode = m_pkNode->m_pkParent;
						break;
					}
					else
					{
						m_pkNode = m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				m_pkNode = NULL;
			}

			if(m_pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}
			return itRes;
		}

		const_iterator& operator -- ()
		{
			VE_ASSERT(m_pkNode);
			if(m_pkNode->m_pkLeft)
			{
				m_pkNode = m_pkNode->m_pkLeft;
				while(m_pkNode->m_pkRight)
				{
					m_pkNode = m_pkNode->m_pkRight;
				}

			}
			else if(m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!m_pkNode->m_pkParent)
					{
						m_pkNode = NULL;
						break;
					}
					if(m_pkNode->m_pkParent->m_pkRight == m_pkNode)
					{
						m_pkNode = m_pkNode->m_pkParent;
						break;
					}
					else
					{
						m_pkNode = m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				m_pkNode = NULL;
			}

			if(m_pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}

			return *this;
		}

		const_iterator operator -- (int)
		{
			VE_ASSERT(m_pkNode);
			const_iterator itRes(m_pkNode, m_pkNode->m_tKey, m_pkNode->m_tVal);
			if(m_pkNode->m_pkLeft)
			{
				m_pkNode = m_pkNode->m_pkLeft;
				while(m_pkNode->m_pkRight)
				{
					m_pkNode = m_pkNode->m_pkRight;
				}

			}
			else if(m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!m_pkNode->m_pkParent)
					{
						m_pkNode = NULL;
						break;
					}
					if(m_pkNode->m_pkParent->m_pkRight == m_pkNode)
					{
						m_pkNode = m_pkNode->m_pkParent;
						break;
					}
					else
					{
						m_pkNode = m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				m_pkNode = NULL;
			}

			if(m_pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}
			return itRes;
		}

		bool IsRoot() const
		{
			VE_ASSERT(m_pkNode);
			return m_pkNode->m_pkParent == NULL;
		}

		bool IsLeft() const
		{
			if(m_pkNode->m_pkParent)
			{
				return m_pkNode->m_pkParent->m_pkLeft == m_pkNode;
			}
			return false;
		}

		bool IsRight() const
		{
			if(m_pkNode->m_pkParent)
			{
				return m_pkNode->m_pkParent->m_pkRight == m_pkNode;
			}
			return false;
		}

		bool HasLeft()
		{
			return m_pkNode->m_pkLeft ? true : false;
		}

		bool HasRight()
		{
			return m_pkNode->m_pkRight ? true :false;
		}

		void TurnUp()
		{
			if(!m_pkNode) return;
			m_pkNode = m_pkNode->m_pkParent;
			if(m_pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}
		}

		void TurnLeft()
		{
			if(!m_pkNode) return;
			m_pkNode = m_pkNode->m_pkLeft;
			if(m_pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}
		}

		void TurnRight()
		{
			if(!m_pkNode) return;
			m_pkNode = m_pkNode->m_pkRight;
			if(m_pkNode)
			{
				new (&m_kValue) VePair<TKEY&, TVAL&>(m_pkNode->m_tKey, m_pkNode->m_tVal);
			}
		}

	protected:
		friend class VeTreeMap<TKEY, TVAL>;

		void* GetValuePointer() const
		{
			return (void*)&m_kValue;
		}

		Node* m_pkNode;
		VePair<TKEY&, TVAL&> m_kValue;
	};

	class iterator : public const_iterator
	{
	public:
		iterator(Node* pkNode, TKEY& tKey, TVAL& tVal) : const_iterator(pkNode, tKey, tVal)
		{

		}

		VePair<TKEY&, TVAL&>& operator * () const
		{
			VE_ASSERT(const_iterator::m_pkNode);
			return const_iterator::m_kValue;
		}

		VePair<TKEY&, TVAL&>* operator -> () const
		{
			return const_iterator::m_pkNode ? (VePair<TKEY&, TVAL&>*)(const_iterator::GetValuePointer()) : NULL;
		}

		iterator& operator ++ ()
		{
			VE_ASSERT(const_iterator::m_pkNode);
			if((const_iterator::m_pkNode)->m_pkRight)
			{
				const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkRight;
				while(const_iterator::m_pkNode->m_pkLeft)
				{
					const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkLeft;
				}

			}
			else if(const_iterator::m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!const_iterator::m_pkNode->m_pkParent)
					{
						const_iterator::m_pkNode = NULL;
						break;
					}
					if(const_iterator::m_pkNode->m_pkParent->m_pkLeft == const_iterator::m_pkNode)
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						break;
					}
					else
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				const_iterator::m_pkNode = NULL;
			}

			if(const_iterator::m_pkNode)
			{
				new (const_iterator::GetValuePointer()) VePair<TKEY&, TVAL&>(const_iterator::m_pkNode->m_tKey, const_iterator::m_pkNode->m_tVal);
			}

			return *this;
		}

		iterator operator ++ (int)
		{
			VE_ASSERT(const_iterator::m_pkNode);
			iterator itRes(const_iterator::m_pkNode, const_iterator::m_pkNode->m_tKey, const_iterator::m_pkNode->m_tVal);
			if(const_iterator::m_pkNode->m_pkRight)
			{
				const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkRight;
				while(const_iterator::m_pkNode->m_pkLeft)
				{
					const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkLeft;
				}

			}
			else if(const_iterator::m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!const_iterator::m_pkNode->m_pkParent)
					{
						const_iterator::m_pkNode = NULL;
						break;
					}
					if(const_iterator::m_pkNode->m_pkParent->m_pkLeft == const_iterator::m_pkNode)
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						break;
					}
					else
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				const_iterator::m_pkNode = NULL;
			}

			if(const_iterator::m_pkNode)
			{
				new (&const_iterator::m_kValue) VePair<TKEY&, TVAL&>(const_iterator::m_pkNode->m_tKey, const_iterator::m_pkNode->m_tVal);
			}
			return itRes;
		}

		iterator& operator -- ()
		{
			VE_ASSERT(const_iterator::m_pkNode);
			if(const_iterator::m_pkNode->m_pkLeft)
			{
				const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkLeft;
				while(const_iterator::m_pkNode->m_pkRight)
				{
					const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkRight;
				}

			}
			else if(const_iterator::m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!const_iterator::m_pkNode->m_pkParent)
					{
						const_iterator::m_pkNode = NULL;
						break;
					}
					if(const_iterator::m_pkNode->m_pkParent->m_pkRight == const_iterator::m_pkNode)
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						break;
					}
					else
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				const_iterator::m_pkNode = NULL;
			}

			if(const_iterator::m_pkNode)
			{
				new (&const_iterator::m_kValue) VePair<TKEY&, TVAL&>(const_iterator::m_pkNode->m_tKey, const_iterator::m_pkNode->m_tVal);
			}

			return *this;
		}

		iterator operator -- (int)
		{
			VE_ASSERT(const_iterator::m_pkNode);
			iterator itRes(const_iterator::m_pkNode, const_iterator::m_pkNode->m_tKey, const_iterator::m_pkNode->m_tVal);
			if(const_iterator::m_pkNode->m_pkLeft)
			{
				const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkLeft;
				while(const_iterator::m_pkNode->m_pkRight)
				{
					const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkRight;
				}

			}
			else if(const_iterator::m_pkNode->m_pkParent)
			{
				while(true)
				{
					if(!const_iterator::m_pkNode->m_pkParent)
					{
						const_iterator::m_pkNode = NULL;
						break;
					}
					if(const_iterator::m_pkNode->m_pkParent->m_pkRight == const_iterator::m_pkNode)
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						break;
					}
					else
					{
						const_iterator::m_pkNode = const_iterator::m_pkNode->m_pkParent;
						continue;
					}
				}
			}
			else
			{
				const_iterator::m_pkNode = NULL;
			}

			if(const_iterator::m_pkNode)
			{
				new (&const_iterator::m_kValue) VePair<TKEY&, TVAL&>(const_iterator::m_pkNode->m_tKey, const_iterator::m_pkNode->m_tVal);
			}
			return itRes;
		}
	};

	VeTreeMap(VePoolAllocatorPtr spAllocator = NULL) : m_pkRoot(NULL), m_u32Size(0)
	{
		SetAllocator(spAllocator);
	}

	~VeTreeMap()
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
		if(m_pkRoot)
		{
			Clear(m_pkRoot);
			m_pkRoot = NULL;
		}
		m_u32Size = 0;
	}

	iterator Insert(TKEY tKey, TVAL tVal, bool bOverWrite = true)
	{
		if(m_pkRoot)
		{
			Node* pkIter = m_pkRoot;
			while(true)
			{
				if(tKey == pkIter->m_tKey)
				{
					if(bOverWrite)
					{
						pkIter->m_tVal = tVal;
					}
					return iterator(pkIter, pkIter->m_tKey, pkIter->m_tVal);
				}
				else if(tKey < pkIter->m_tKey)
				{
					if(pkIter->m_pkLeft)
					{
						pkIter = pkIter->m_pkLeft;
						continue;
					}
					else
					{
						pkIter->m_pkLeft = new(VePoolMalloc(m_spAllocator)) Node;
						++m_u32Size;
						pkIter->m_pkLeft->m_pkParent = pkIter;
						pkIter->m_pkLeft->m_pkLeft = NULL;
						pkIter->m_pkLeft->m_pkRight = NULL;
						pkIter->m_pkLeft->m_eColor = RED;
						pkIter->m_pkLeft->m_tKey = tKey;
						pkIter->m_pkLeft->m_tVal = tVal;
						pkIter = pkIter->m_pkLeft;
						UpdateColorInsert(pkIter);
						return iterator(pkIter, pkIter->m_tKey, pkIter->m_tVal);
					}
				}
				else
				{
					if(pkIter->m_pkRight)
					{
						pkIter = pkIter->m_pkRight;
						continue;
					}
					else
					{
						pkIter->m_pkRight = new(VePoolMalloc(m_spAllocator)) Node;
						++m_u32Size;
						pkIter->m_pkRight->m_pkParent = pkIter;
						pkIter->m_pkRight->m_pkLeft = NULL;
						pkIter->m_pkRight->m_pkRight = NULL;
						pkIter->m_pkRight->m_eColor = RED;
						pkIter->m_pkRight->m_tKey = tKey;
						pkIter->m_pkRight->m_tVal = tVal;
						pkIter = pkIter->m_pkRight;
						UpdateColorInsert(pkIter);
						return iterator(pkIter, pkIter->m_tKey, pkIter->m_tVal);
					}
				}
			}
		}
		else
		{
			m_pkRoot = new(VePoolMalloc(m_spAllocator)) Node;
			++m_u32Size;
			m_pkRoot->m_pkParent = NULL;
			m_pkRoot->m_pkLeft = NULL;
			m_pkRoot->m_pkRight = NULL;
			m_pkRoot->m_eColor = BLACK;
			m_pkRoot->m_tKey = tKey;
			m_pkRoot->m_tVal = tVal;
			return iterator(m_pkRoot, m_pkRoot->m_tKey, m_pkRoot->m_tVal);
		}
	}

	const_iterator Find(TKEY tKey) const
	{
		Node* pkNode = m_pkRoot;
		while(pkNode)
		{
			if(pkNode->m_tKey == tKey)
			{
				return const_iterator(pkNode, pkNode->m_tKey, pkNode->m_tVal);
			}
			else if(pkNode->m_tKey > tKey)
			{
				pkNode = pkNode->m_pkLeft;
			}
			else
			{
				pkNode = pkNode->m_pkRight;
			}
		}
		void* pkNull(NULL);
		return const_iterator(NULL, *(TKEY*)pkNull, *(TVAL*)pkNull);
	}

	iterator Find(TKEY tKey)
	{
		Node* pkNode = m_pkRoot;
		while(pkNode)
		{
			if(pkNode->m_tKey == tKey)
			{
				return iterator(pkNode, pkNode->m_tKey, pkNode->m_tVal);
			}
			else if(pkNode->m_tKey > tKey)
			{
				pkNode = pkNode->m_pkLeft;
			}
			else
			{
				pkNode = pkNode->m_pkRight;
			}
		}
		void* pkNull(NULL);
		return iterator(NULL, *(TKEY*)pkNull, *(TVAL*)pkNull);
	}

	void Erase(const_iterator itLoc)
	{
		Remove(itLoc.m_pkNode);
	}

	TVAL& operator [] (TKEY tKey)
	{
		iterator it = Insert(tKey, TVAL(), false);
		return it->m_tSecond;
	}

	iterator Begin()
	{
		Node* pkBeginNode = m_pkRoot;
		while(pkBeginNode)
		{
			if(pkBeginNode->m_pkLeft)
			{
				pkBeginNode = pkBeginNode->m_pkLeft;
			}
			else
			{
				break;
			}
		}
		if(pkBeginNode)
		{
			return iterator(pkBeginNode, pkBeginNode->m_tKey, pkBeginNode->m_tVal);
		}
		else
		{
			void* pkNull(NULL);
			return iterator(pkBeginNode, *(TKEY*)pkNull, *(TVAL*)pkNull);
		}
	}

	const_iterator Begin() const
	{
		Node* pkBeginNode = m_pkRoot;
		while(pkBeginNode)
		{
			if(pkBeginNode->m_pkLeft)
			{
				pkBeginNode = pkBeginNode->m_pkLeft;
			}
			else
			{
				break;
			}
		}
		if(pkBeginNode)
		{
			return const_iterator(pkBeginNode, pkBeginNode->m_tKey, pkBeginNode->m_tVal);
		}
		else
		{
			void* pkNull(0);
			return const_iterator(pkBeginNode, *(TKEY*)pkNull, *(TVAL*)pkNull);
		}
	}

	iterator Last()
	{
		Node* pkBeginNode = m_pkRoot;
		while(pkBeginNode)
		{
			if(pkBeginNode->m_pkRight)
			{
				pkBeginNode = pkBeginNode->m_pkRight;
			}
			else
			{
				break;
			}
		}
		if(pkBeginNode)
		{
			return iterator(pkBeginNode, pkBeginNode->m_tKey, pkBeginNode->m_tVal);
		}
		else
		{
			void* pkNull(NULL);
			return iterator(pkBeginNode, *(TKEY*)pkNull, *(TVAL*)pkNull);
		}
	}

	const_iterator Last() const
	{
		Node* pkBeginNode = m_pkRoot;
		while(pkBeginNode)
		{
			if(pkBeginNode->m_pkRight)
			{
				pkBeginNode = pkBeginNode->m_pkRight;
			}
			else
			{
				break;
			}
		}
		if(pkBeginNode)
		{
			return const_iterator(pkBeginNode, pkBeginNode->m_tKey, pkBeginNode->m_tVal);
		}
		else
		{
			void* pkNull(NULL);
			return const_iterator(pkBeginNode, *(TKEY*)pkNull, *(TVAL*)pkNull);
		}
	}

	iterator End()
	{
		void* pkNull(NULL);
		return iterator(NULL, *(TKEY*)pkNull, *(TVAL*)pkNull);
	}

	const_iterator End() const
	{
		void* pkNull(NULL);
		return const_iterator(NULL, *(TKEY*)pkNull, *(TVAL*)pkNull);
	}

	//void Dump(VeVector<VePair<>>)

	const VePoolAllocatorPtr& GetAllocator()
	{
		return m_spAllocator;
	}

private:
	void Clear(Node* pkNode)
	{
		VE_ASSERT(pkNode);
		if(pkNode->m_pkLeft)
		{
			Clear(pkNode->m_pkLeft);
		}
		if(pkNode->m_pkRight)
		{
			Clear(pkNode->m_pkRight);
		}
		pkNode->~Node();
		VePoolFree(m_spAllocator, pkNode);
	}

	void UpdateColorInsert(Node* pkNode)
	{
		VE_ASSERT(pkNode->m_pkParent);
		VE_ASSERT(pkNode->m_eColor == RED);
		if(pkNode->m_pkParent->m_eColor == RED)
		{
			Node* pkParent = pkNode->m_pkParent;
			Node* pkGrand = pkParent->m_pkParent;
			VE_ASSERT(pkGrand);
			const bool bParentLeft = pkGrand->m_pkLeft == pkParent;
			Node* pkUncle = bParentLeft ? pkGrand->m_pkRight : pkGrand->m_pkLeft;
			if(pkUncle && pkUncle->m_eColor == RED)
			{
				pkParent->m_eColor = BLACK;
				pkUncle->m_eColor = BLACK;
				if(pkGrand->m_pkParent)
				{
					pkGrand->m_eColor = RED;
					UpdateColorInsert(pkGrand);
				}
				else
				{
					pkGrand->m_eColor = BLACK;
				}
			}
			else
			{
				Node *pkTwo(NULL), *pkThree(NULL);
				const bool bNodeLeft = pkParent->m_pkLeft == pkNode;
				if(bParentLeft == bNodeLeft)
				{
					if(bParentLeft)
					{
						pkParent->m_pkParent = pkGrand->m_pkParent;
						pkParent->m_eColor = BLACK;
						if(pkGrand->m_pkParent)
						{
							if(pkGrand->m_pkParent->m_pkLeft == pkGrand)
							{
								pkGrand->m_pkParent->m_pkLeft = pkParent;
							}
							else
							{
								pkGrand->m_pkParent->m_pkRight = pkParent;
							}
						}
						else
						{
							m_pkRoot = pkParent;
						}
						pkThree = pkParent->m_pkRight;
						pkParent->m_pkRight = pkGrand;
						pkGrand->m_eColor = RED;
						pkGrand->m_pkParent = pkParent;
						pkGrand->m_pkLeft = pkThree;
						if(pkThree)
						{
							pkThree->m_pkParent = pkGrand;
						}
					}
					else
					{
						pkParent->m_pkParent = pkGrand->m_pkParent;
						pkParent->m_eColor = BLACK;
						if(pkGrand->m_pkParent)
						{
							if(pkGrand->m_pkParent->m_pkLeft == pkGrand)
							{
								pkGrand->m_pkParent->m_pkLeft = pkParent;
							}
							else
							{
								pkGrand->m_pkParent->m_pkRight = pkParent;
							}
						}
						else
						{
							m_pkRoot = pkParent;
						}
						pkThree = pkParent->m_pkLeft;
						pkParent->m_pkLeft = pkGrand;
						pkGrand->m_eColor = RED;
						pkGrand->m_pkParent = pkParent;
						pkGrand->m_pkRight = pkThree;
						if(pkThree)
						{
							pkThree->m_pkParent = pkGrand;
						}
					}
				}
				else
				{
					if(bParentLeft)
					{
						pkTwo = pkNode->m_pkLeft;
						pkThree = pkNode->m_pkRight;
						pkNode->m_pkParent = pkGrand->m_pkParent;
						pkNode->m_eColor = BLACK;
						if(pkGrand->m_pkParent)
						{
							if(pkGrand->m_pkParent->m_pkLeft == pkGrand)
							{
								pkGrand->m_pkParent->m_pkLeft = pkNode;
							}
							else
							{
								pkGrand->m_pkParent->m_pkRight = pkNode;
							}
						}
						else
						{
							m_pkRoot = pkNode;
						}
						pkNode->m_pkLeft = pkParent;
						pkParent->m_pkParent = pkNode;
						pkParent->m_pkRight = pkTwo;
						if(pkTwo)
						{
							pkTwo->m_pkParent = pkParent;
						}
						pkNode->m_pkRight = pkGrand;
						pkGrand->m_pkParent = pkNode;
						pkGrand->m_eColor = RED;
						pkGrand->m_pkLeft = pkThree;
						if(pkThree)
						{
							pkThree->m_pkParent = pkGrand;
						}
					}
					else
					{
						pkTwo = pkNode->m_pkRight;
						pkThree = pkNode->m_pkLeft;
						pkNode->m_pkParent = pkGrand->m_pkParent;
						pkNode->m_eColor = BLACK;
						if(pkGrand->m_pkParent)
						{
							if(pkGrand->m_pkParent->m_pkLeft == pkGrand)
							{
								pkGrand->m_pkParent->m_pkLeft = pkNode;
							}
							else
							{
								pkGrand->m_pkParent->m_pkRight = pkNode;
							}
						}
						else
						{
							m_pkRoot = pkNode;
						}
						pkNode->m_pkRight = pkParent;
						pkParent->m_pkParent = pkNode;
						pkParent->m_pkLeft = pkTwo;
						if(pkTwo)
						{
							pkTwo->m_pkParent = pkParent;
						}
						pkNode->m_pkLeft = pkGrand;
						pkGrand->m_pkParent = pkNode;
						pkGrand->m_eColor = RED;
						pkGrand->m_pkRight = pkThree;
						if(pkThree)
						{
							pkThree->m_pkParent = pkGrand;
						}
					}
				}
			}
		}
	}

	void Remove(Node* pkNode)
	{
		/*if(!pkNode) return;
		if(pkNode->m_pkRight == NULL)
		{
			if(pkNode->m_pkParent == NULL)
			{
				m_pkRoot = pkNode->m_pkLeft;
				m_pkRoot->m_eColor = BLACK;
			}
			else if(pkNode->m_pkParent->m_pkLeft == pkNode)
			{
				pkNode->m_pkParent->m_pkLeft = pkNode->m_pkLeft;
			}
			else
			{
				pkNode->m_pkParent->m_pkRight = pkNode->m_pkLeft;
			}

			if(pkNode->m_pkLeft)
			{
				pkNode->m_pkLeft->m_pkParent = pkNode->m_pkParent;
			}
			VePoolFree(pkNode);
		}
		else
		{
			Node* pkSuc = GetSuccessor(pkNode);
			pkNode->m_tKey = pkSuc->m_tKey;
			pkNode->m_tVal = pkSuc->m_tVal;
			if(pkSuc->m_eColor == RED)
			{
				if(pkSuc->m_pkParent->m_pkRight == pkSuc)
					pkSuc->m_pkParent->m_pkRight = pkSuc->m_pkRight;
				else
					pkSuc->m_pkParent->m_pkLeft = pkSuc->m_pkRight;
			}
			else if(pkSuc->m_pkRight == NULL)
			{

			}
			VePoolFree(pkSuc);
		}*/
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

	static Node* GetSuccessor(Node* pkNode)
	{
		if(pkNode == NULL) return NULL;
		Node* pkRes(NULL);
		if(pkNode->m_pkRight == NULL)
			return pkNode;
		else
			pkRes = pkNode->m_pkRight;
		while(pkRes->m_pkLeft)
		{
			pkRes = pkRes->m_pkLeft;
		}
		return pkRes;
	}

	/*static void RotateLeft(Node** ppkNode)
	{
		VE_ASSERT((*ppkNode) && (*ppkNode)->m_pkRight);
		Node* pkRightTree = (*ppkNode)->m_pkRight;
		
		pkRightTree->m_pkParent = (*ppkNode)->m_pkParent;
		(*ppkNode)->m_pkParent = pkRightTree;
		pkRightTree->m_pkLeft->m_pkParent = (*ppkNode);

		(*ppkNode)->m_pkRight = pkRightTree->m_pkLeft;
		pkRightTree->m_pkLeft = (*ppkNode);
		(*ppkNode) = pkRightTree;
	}*/

	Node* m_pkRoot;
	VeUInt32 m_u32Size;

	VePoolAllocatorPtr m_spAllocator;

};
