////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeVector.h
//  Version:     v1.00
//  Created:     9/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class T>
class VeVector : public VeMemObject
{
public:
	typedef T* iterator;

	struct Shell
	{
		T m_kData;
	};

	typedef const T* const_iterator;

	VeVector()
	{
		m_pVector = NULL;
		m_u32Size = 0;
		m_u32MaxSize = 0;
	}

	VeVector(VeUInt32 u32Size)
	{
		m_pVector = NULL;
		m_u32Size = 0;
		m_u32MaxSize = 0;
		Resize(u32Size);
	}

	VeVector(VeUInt32 u32Size, const T& tInit)
	{
		m_pVector = NULL;
		m_u32Size = 0;
		m_u32MaxSize = 0;
		Resize(u32Size, tInit);
	}

	VeVector(const VeVector<T>& kVec)
	{
		m_pVector = NULL;
		m_u32Size = 0;
		m_u32MaxSize = 0;
		CopyFrom(kVec);
	}

	VeVector(const_iterator itStart, const_iterator itLast)
	{
		m_pVector = NULL;
		m_u32Size = 0;
		m_u32MaxSize = 0;
		CopyFrom(itStart, itLast);
	}

	~VeVector()
	{
		Clear();
		if(m_pVector)
		{
			VeFree(m_pVector);
			m_pVector = NULL;
		}
		m_u32Size = 0;
		m_u32MaxSize = 0;
	}

	T& operator [] (VeUInt32 u32Pos)
	{
		VE_ASSERT(u32Pos < m_u32Size);
		return m_pVector[u32Pos];
	}

	const T& operator [] (VeUInt32 u32Pos) const
	{
		VE_ASSERT(u32Pos < m_u32Size);
		return m_pVector[u32Pos];
	}

	VeVector<T>& operator = (const VeVector<T>& kVec)
	{
		CopyFrom(kVec);
		return *this;
	}

	void Reserve(VeUInt32 u32Count)
	{
		u32Count = ((u32Count + 0xF) >> 4) << 4;

		if(m_u32MaxSize < u32Count)
		{
			if(m_pVector)
			{
				m_pVector = (T*)VeRealloc(m_pVector, u32Count * sizeof(T));
			}
			else
			{
				m_pVector = (T*)VeMalloc(u32Count * sizeof(T));
			}

			m_u32MaxSize = u32Count;
		}
	}

	VeUInt32 Capacity() const
	{
		return m_u32MaxSize;
	}

	VeUInt32 Size() const
	{
		return m_u32Size;
	}

	bool Empty() const
	{
		return m_u32Size == 0;
	}

	void Resize(VeUInt32 u32NewSize)
	{
		if(u32NewSize > m_u32Size)
		{
			if(u32NewSize > m_u32MaxSize)
			{
				Reserve(VE_MAX(m_u32Size + (m_u32Size >> 1), u32NewSize));
			}

			for(VeUInt32 i(m_u32Size); i < u32NewSize; ++i)
			{
				new(m_pVector + i) T;
			}
		}
		else if(u32NewSize < m_u32Size)
		{
			for(VeUInt32 i(u32NewSize); i < m_u32Size; ++i)
			{
				((Shell*)(m_pVector + i))->~Shell();
			}
		}

		m_u32Size = u32NewSize;
	}

	void Resize(VeUInt32 u32NewSize, const T& tVal)
	{
		if(u32NewSize > m_u32Size)
		{
			if(u32NewSize > m_u32MaxSize)
			{
				Reserve(VE_MAX(m_u32Size + (m_u32Size >> 1), u32NewSize));
			}

			for(VeUInt32 i(m_u32Size); i < u32NewSize; ++i)
			{
				new(m_pVector + i) T(tVal);
			}
		}
		else if(u32NewSize < m_u32Size)
		{
			for(VeUInt32 i(u32NewSize); i < m_u32Size; ++i)
			{
				((Shell*)(m_pVector + i))->~Shell();
			}
		}

		m_u32Size = u32NewSize;
	}

	void Increase(VeUInt32 u32Inc = 1)
	{
		Resize(Size() + u32Inc);
	}

	void Decrease(VeUInt32 u32Dec = 1)
	{
		Resize(Size() - VE_MIN(u32Dec, Size()));
	}

	void Clear()
	{
		Resize(0);
	}

	T& At(VeUInt32 u32Pos)
	{
		VE_ASSERT(u32Pos < m_u32Size);
		return m_pVector[u32Pos];
	}

	const T& At(VeUInt32 u32Pos) const
	{
		VE_ASSERT(u32Pos < m_u32Size);
		return m_pVector[u32Pos];
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
		return m_pVector;
	}

	const_iterator Begin() const
	{
		return m_pVector;
	}

	iterator Last()
	{
		return m_pVector + (m_u32Size ? (m_u32Size - 1) : 0);
	}

	const_iterator Last() const
	{
		return m_pVector + (m_u32Size ? (m_u32Size - 1) : 0);
	}

	iterator End()
	{
		return m_pVector + m_u32Size;
	}

	const_iterator End() const
	{
		return m_pVector + m_u32Size;
	}

	iterator Erase(const_iterator itLoc)
	{
		VE_ASSERT(itLoc >= Begin() && itLoc < End());

		iterator itLocal = (iterator)itLoc;

		for(T* pVal = itLocal; pVal < Last(); ++pVal)
		{
			*pVal = *(pVal + 1);
		}
		Resize(m_u32Size - 1);

		return itLocal;
	}

	iterator Erase(const_iterator itFirst, const_iterator itLast)
	{
		VE_ASSERT(itFirst >= Begin() && itFirst <= itLast && itLast < End());

		iterator itFst = (iterator)itFirst;
		iterator itLst = (iterator)itLast;

		for(VeInt32 i(0); i < (Last() - itLst); ++i)
		{
			*(itFst + i) = *(itLst + i + 1);
		}
		Resize(m_u32Size - VeUInt32(itLst - itFst + 1));

		return itFst;
	}

	void PushBack(const T& tVal)
	{
		Resize(m_u32Size + 1, tVal);
	}

	void PopBack()
	{
		Resize(m_u32Size - 1);
	}

	iterator Insert(const_iterator itLoc, const T& tVal)
	{
		if((!itLoc) || itLoc == End())
		{
			PushBack(tVal);
			return Last();
		}
		else
		{
			VE_ASSERT(itLoc >= Begin() && itLoc < End());
			VeSizeT stLoc = itLoc - Begin();
			Resize(m_u32Size + 1);
			iterator itLocal = Begin() + stLoc;
			for(iterator it = Last(); it > itLocal; --it)
			{
				*it = *(it - 1);
			}
			*itLocal = tVal;
			return itLocal;
		}
	}

	void Insert(const_iterator itLoc, VeUInt32 u32Num, const T& tVal)
	{
		if(itLoc  == End())
		{
			VeUInt32 u32Start = Size();
			Resize(u32Start + u32Num);
			for(VeUInt32 i(0); i < u32Num; ++i)
			{
				*(m_pVector + u32Start + i) = tVal;
			}
		}
		else
		{
			VE_ASSERT(itLoc >= Begin() && itLoc < End());
			Resize(m_u32Size + u32Num);

			iterator itLocal = (iterator)itLoc;

			for(iterator it = Last(); it >= (itLocal + u32Num); --it)
			{
				*it = *(it - u32Num);
			}

			for(VeUInt32 i(0); i < u32Num; ++i)
			{
				*(itLocal + i) = tVal;
			}
		}
	}

	void Insert(const_iterator itLoc, const_iterator itStart, const_iterator itLast)
	{
		VE_ASSERT(itLast >= itStart);
		VeUInt32 u32Num = VeUInt32(itLast - itStart) + 1;

		if(itLoc == End())
		{
			VeUInt32 u32Start = Size();
			Resize(m_u32Size + u32Num);
			for(VeUInt32 i(0); i < u32Num; ++i)
			{
				*(m_pVector + u32Start + i) = itStart[i];
			}
		}
		else
		{
			VE_ASSERT(itLoc >= Begin() && itLoc < End());
			Resize(m_u32Size + u32Num);
			iterator itLocal = (iterator)itLoc;

			for(iterator it = Last(); it >= (itLocal + u32Num); --it)
			{
				*it = *(it - u32Num);
			}

			for(const_iterator it = itStart; it <= itLast; ++it)
			{
				*(itLocal++) = *it;
			}
		}
	}

	void CopyFrom(const VeVector<T>& kVec)
	{
		Resize(kVec.Size());
		for(VeUInt32 i(0); i < Size(); ++i)
		{
			At(i) = kVec.At(i);
		}
	}

	void CopyFrom(const_iterator itStart, const_iterator itLast)
	{
		VE_ASSERT(itLast >= itStart);
		VeUInt32 u32Num = (VeUInt32)((itLast - itStart) + 1);
		Resize(u32Num);
		for(VeUInt32 i(0); i < Size(); ++i)
		{
			At(i) = itStart[i];
		}
	}

private:
	T* m_pVector;
	VeUInt32 m_u32Size;
	VeUInt32 m_u32MaxSize;
};
