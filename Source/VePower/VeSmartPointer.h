////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSmartPointer.h
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
class VePointer : public VeMemObject
{
public:
	typedef T TypeClass;

	VePointer(T* pObject = (T*)NULL)
	{
		m_pObject = pObject;
		if(m_pObject)
			m_pObject->IncRefCount();
	}

	VePointer(const VePointer& ptr)
	{
		m_pObject = ptr.m_pObject;
		if(m_pObject)
			m_pObject->IncRefCount();
	}

	~VePointer()
	{
		if(m_pObject)
			m_pObject->DecRefCount();
	}

	template <typename U>
	operator VePointer<U> () const
	{
		return static_cast<U*>(m_pObject);
	}

	operator T* () const
	{
		return m_pObject;
	}

	T& operator * () const
	{
		return *m_pObject;
	}

	T* operator -> () const
	{
		return m_pObject;
	}

	VePointer& operator = (const VePointer& ptr)
	{
		if(m_pObject != ptr.m_pObject)
		{
			if(m_pObject)
				m_pObject->DecRefCount();
			m_pObject = ptr.m_pObject;
			if(m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

	VePointer& operator = (T* pObject)
	{
		if(m_pObject != pObject)
		{
			if(m_pObject)
				m_pObject->DecRefCount();
			m_pObject = pObject;
			if(m_pObject)
				m_pObject->IncRefCount();
		}
		return *this;
	}

	bool operator == (T* pObject) const
	{
		return (m_pObject == pObject);
	}

	bool operator != (T* pObject) const
	{
		return (m_pObject != pObject);
	}

	bool operator == (const VePointer& ptr) const
	{
		return (m_pObject == ptr.m_pObject);
	}

	bool operator != (const VePointer& ptr) const
	{
		return (m_pObject != ptr.m_pObject);
	}

	T* p()
	{
		return m_pObject;
	}

	const T* p() const
	{
		return m_pObject;
	}

	T& r()
	{
		VE_ASSERT(m_pObject);
		return *m_pObject;
	}

	const T& r() const
	{
		VE_ASSERT(m_pObject);
		return *m_pObject;
	}

	static const VePointer ms_NULL;

protected:
	T* m_pObject;
};

template<class T> const VePointer<T> VePointer<T>::ms_NULL = NULL;

#define VeSmartPointer(classname)										\
	class classname;													\
	typedef VePointer<classname> classname##Ptr

#define VeSmartPointerCast(type, smartptr) ((type*)(void*) (smartptr))
