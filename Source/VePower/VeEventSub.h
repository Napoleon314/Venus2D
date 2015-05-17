////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeEventSub.h
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

VE_TEMPLATE
class VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_SPECIALIZATION : public VeRefNode<void*>
{
public:
	virtual void Callback(VE_FUNCTION_PARAM) const = 0;

	virtual ~VE_DEFINE(VeAbstractDelegate)() {}
protected:
	VE_DEFINE(VeAbstractDelegate)()
	{
		m_tContent = this;
	}
};

VE_TEMPLATE_T
class VE_DEFINE(VeMemberDelegate)VE_TEMPLATE_T_SPECIALIZATION : public VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM
{
public:
	typedef void(T::*VE_EVENT_CALLBACK)(VE_FUNCTION_PARAM);

	VE_DEFINE(VeMemberDelegate)() : m_pfnCallback(NULL), m_pObject(NULL)
	{

	}

	VE_DEFINE(VeMemberDelegate)(T* pObject, VE_EVENT_CALLBACK pfnCallback) : m_pObject(pObject), m_pfnCallback(pfnCallback)
	{

	}

	void Set(T* pObject, VE_EVENT_CALLBACK pfnCallback)
	{
		m_pObject = pObject;
		m_pfnCallback = pfnCallback;
	}

	virtual void Callback(VE_FUNCTION_PARAM) const
	{
		if(m_pObject && m_pfnCallback)
			(m_pObject->*m_pfnCallback)(VE_FUNCTION_VALUE);
	}
private:
	VE_EVENT_CALLBACK m_pfnCallback;
	T * m_pObject;
};

VE_TEMPLATE
class VE_DEFINE(VeFunctionDelegate)VE_TEMPLATE_SPECIALIZATION : public VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM
{
public:
	typedef void(*VE_EVENT_CALLBACK)(VE_FUNCTION_PARAM);

	VE_DEFINE(VeFunctionDelegate)() : m_pfnCallback(NULL)
	{

	}

	VE_DEFINE(VeFunctionDelegate)(VE_EVENT_CALLBACK pfnCallback) : m_pfnCallback(pfnCallback)
	{

	}

	void Set(VE_EVENT_CALLBACK pfnCallback)
	{
		m_pfnCallback = pfnCallback;
	}

	virtual void Callback(VE_FUNCTION_PARAM) const
	{
		if(m_pfnCallback)
			(*m_pfnCallback)(VE_FUNCTION_VALUE);
	}
private:
	VE_EVENT_CALLBACK m_pfnCallback;
};

VE_TEMPLATE
class VE_DEFINE(VeEvent)VE_TEMPLATE_SPECIALIZATION : public VeMemObject
{
public:
	~VE_DEFINE(VeEvent)()
	{
		Clear();
	}

	void AddDelegate(VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM& kDelegate)
	{
		m_kDelegateList.AttachBack(kDelegate);
	}

	void DelDelegate(VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM& kDelegate)
	{
		VE_ASSERT(kDelegate.IsAttach(m_kDelegateList));
		kDelegate.Detach();
	}

	void Callback(VE_FUNCTION_PARAM)
	{
		m_kDelegateList.BeginIterator();
		while(!m_kDelegateList.IsEnd())
		{
			VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM* pDelegate = (VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM*)(m_kDelegateList.GetIterNode());
			m_kDelegateList.Next();
			pDelegate->Callback(VE_FUNCTION_VALUE);
		}
	}

	void Callback(VE_FUNCTION_PARAM_CUSTOM(bool&,bHook))
	{
		m_kDelegateList.BeginIterator();
		while(!m_kDelegateList.IsEnd())
		{
			VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM* pDelegate = (VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM*)(m_kDelegateList.GetIterNode());
			m_kDelegateList.Next();
			pDelegate->Callback(VE_FUNCTION_VALUE);
			if(bHook)
			{
				m_kDelegateList.EndIterator();
				break;
			}
		}
	}

	void Clear(void)
	{
		m_kDelegateList.BeginIterator();
		while(!m_kDelegateList.IsEnd())
		{
			VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM* pDelegate = (VE_DEFINE(VeAbstractDelegate)VE_TEMPLATE_PARAM*)(m_kDelegateList.GetIterNode());
			m_kDelegateList.Next();
			pDelegate->Detach();
		}
		VE_ASSERT(m_kDelegateList.Size() == 0);
	}

	void MoveTo(VE_DEFINE(VeEvent)VE_TEMPLATE_PARAM& kEvent)
	{
		while(m_kDelegateList.Size())
		{
			kEvent.m_kDelegateList.AttachBack(*m_kDelegateList.GetHeadNode());
		}
	}

private:
	VeRefList<void*> m_kDelegateList;
};

#undef VE_DEFINE
#undef VE_TEMPLATE
#undef VE_TEMPLATE_T
#undef VE_TEMPLATE_NO_DEFAULT
#undef VE_TEMPLATE_T_NO_DEFAULT
#undef VE_TEMPLATE_PARAM
#undef VE_TEMPLATE_T_PARAM
#undef VE_TEMPLATE_SPECIALIZATION
#undef VE_TEMPLATE_T_SPECIALIZATION
#undef VE_FUNCTION_PARAM
#undef VE_FUNCTION_PARAM_CUSTOM
#undef VE_FUNCTION_VALUE
