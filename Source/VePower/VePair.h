////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VePair.h
//  Version:     v1.00
//  Created:     7/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class T>
void VeInitType(T& tVal) {}

template <>
VE_FORCE_INLINE void VeInitType<VeUInt32>(VeUInt32& u32Num)
{
	u32Num = 0;
}

template<class type1, class type2>
struct VePair : public VeMemObject
{
	typedef VePair<type1, type2> Pair;
	typedef type1 FirstType;
	typedef type2 SecondType;

	VePair() : m_tFirst(type1()), m_tSecond(type2())
	{

	}

	VePair(const type1& kVal1, const type2& kVal2) : m_tFirst(kVal1), m_tSecond(kVal2)
	{

	}

	template<class other1, class other2>
	VePair(const VePair<other1, other2>& kRight) : m_tFirst(kRight.m_tFirst), m_tSecond(kRight.m_tSecond)
	{

	}

	VePair& operator = (const VePair& kPair)
	{
		m_tFirst = kPair.m_tFirst;
		m_tSecond = kPair.m_tSecond;
		return *this;
	}

	bool operator == (const VePair& kPair) const
	{
		return m_tFirst == kPair.m_tFirst && m_tSecond == kPair.m_tSecond;
	}

	bool operator != (const VePair& kPair) const
	{
		return m_tFirst != kPair.m_tFirst || m_tSecond != kPair.m_tSecond;
	}

	void Swap(Pair& kRight)
	{
		if(this != &kRight)
		{
			VeSwap(m_tFirst, kRight.m_tFirst);
			VeSwap(m_tSecond, kRight.m_tSecond);
		}
	}

	FirstType m_tFirst;
	SecondType m_tSecond;
};

template<class type1, class type2>
VePair<type1,type2> VeMakePair(type1 t1, type2 t2)
{
	return VePair<type1,type2>(t1, t2);
}
