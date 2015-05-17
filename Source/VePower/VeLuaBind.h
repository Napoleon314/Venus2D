////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLuaBind.h
//  Version:     v1.00
//  Created:     26/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "VeLuaBindDef.h"
#include "VeLuaBindCall.h"

namespace VeLuaBind
{
	VeSmartPointer(Object);

	class VE_POWER_API Object : public VeRefObject
	{
		VeDeclareRootRTTI(Object);
	public:
		virtual ~Object() {}

		VeString m_kFullName;

	};

	VeSmartPointer(Content);
	VeSmartPointer(ValueObject);

	class VE_POWER_API Content : public Object
	{
		VeDeclareRTTI;
	public:
		Content() {}

		virtual VeInt32 Index(lua_State* pkState);

		virtual VeInt32 NewIndex(lua_State* pkState);

		static const Content& GetCurrent();

		VeStringMap<VeUInt32> m_kObjMap;
		VeVector<ObjectPtr> m_kObjVector;
		VeStringMap<VeUInt32> m_kReadMap;
		VeVector<ValueObjectPtr> m_kReadArray;
		VeStringMap<VeUInt32> m_kWriteMap;
		VeVector<ValueObjectPtr> m_kWriteArray;

	};

	VeSmartPointer(ModuleContent);

	class VE_POWER_API ModuleContent : public Content
	{
		VeDeclareRTTI;
	public:
		ModuleContent() { m_kFullName = "_G"; }
	};

	class VE_POWER_API NameSpaceContent : public Content
	{
		VeDeclareRTTI;
	public:
		NameSpaceContent(const VeChar8* pcName) : m_kName(pcName)
		{
			m_kFullName = Content::GetCurrent().m_kFullName + "." + pcName;
		}

		VeFixedString m_kName;

	};

	enum Operator
	{
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_MOD,
		OP_POW,
		OP_UNM,
		OP_CONCAT,
		OP_LEN,
		OP_EQ,
		OP_LT,
		OP_LE,
		OP_CALL,
		OP_TO_STR,
		OP_INDEX,
		OP_NEWINDEX,
		OP_MAX
	};

	VE_POWER_API const VeChar8* GetOperatorName(Operator eOp);

	VeSmartPointer(FunctionObject);

	class VE_POWER_API FunctionObject : public Object
	{
		VeDeclareRTTI;
	public:
		FunctionObject(const VeChar8* pcName) : m_kName(pcName)
		{
			m_kFullName = Content::GetCurrent().m_kFullName + "." + pcName;
		}

		virtual ~FunctionObject() {}

		const VeChar8* GetName()
		{
			return m_kName;
		}

		void Register(lua_State* pkState);

		void RegisterOperator(lua_State* pkState, Operator eOp);

		virtual VeInt32 Call(lua_State* pkState) = 0;

		static VeInt32 EntryPoint(lua_State* pkState);

	protected:
		VeFixedString m_kName;
		FunctionObjectPtr m_spNext;

	};

	template <class F, class Policies>
	class FunctionObjectImpl : public FunctionObject
	{
	public:
		FunctionObjectImpl(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
			: FunctionObject(pcName), m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			VeInt32 i32Ret = Invoke(pkState, 1, m_kPolicies, m_pfuncCall);
			if(i32Ret < 0 && m_spNext)
			{
				return m_spNext->Call(pkState);
			}
			else
			{
				return i32Ret;
			}
		}

		F m_pfuncCall;
		Policies m_kPolicies;

	};

	template <class F, class Policies>
	FunctionObjectPtr MakeFunction(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
	{
		return VE_NEW FunctionObjectImpl<F,Policies>(pcName, pfuncCall, kPolicies);
	}

	template <class T, class F, class Policies>
	class SingletonFunctionObject : public FunctionObject
	{
	public:
		SingletonFunctionObject(const VeChar8* pcName, T*& pkObj, F pfuncCall, Policies kPolicies)
			: FunctionObject(pcName), m_pkSingleton(pkObj), m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			if(m_pkSingleton)
			{
				VeInt32 i32Ret = Invoke(pkState, m_kPolicies, (void*)m_pkSingleton, 1, m_pfuncCall);
				if(i32Ret < 0 && m_spNext)
				{
					return m_spNext->Call(pkState);
				}
				else
				{
					return i32Ret;
				}
			}
			else
			{
				return 0;
			}
		}

		T*& m_pkSingleton;
		F m_pfuncCall;
		Policies m_kPolicies;

	};

	template <class T, class F, class Policies>
	FunctionObjectPtr MakeFunction(const VeChar8* pcName, T*& pkObj, F pfuncCall, Policies kPolicies)
	{
		return VE_NEW SingletonFunctionObject<T,F,Policies>(pcName, pkObj, pfuncCall, kPolicies);
	}

	class ManualFunctionObject : public FunctionObject
	{
	public:
		typedef VeInt32 (*Func)(lua_State* pkState);

		ManualFunctionObject(const VeChar8* pcName, Func pfuncCall)
			: FunctionObject(pcName), m_pfuncCall(pfuncCall) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			return m_pfuncCall(pkState);
		}

		Func m_pfuncCall;

	};

	class VE_POWER_API ValueObject : public Object
	{
		VeDeclareRTTI;
	public:
		enum Type
		{
			TYPE_READ,
			TYPE_WRITE
		};

		ValueObject(Type eType, const VeChar8* pcName) : m_eType(eType), m_kName(pcName)
		{
			m_kFullName = Content::GetCurrent().m_kFullName + "." + pcName;
		}

		virtual ~ValueObject() {}

		const VeChar8* GetName()
		{
			return m_kName;
		}

		void Register(lua_State* pkState);

		virtual VeInt32 Call(lua_State* pkState) = 0;

	protected:
		const Type m_eType;
		VeFixedString m_kName;

	};

	template<class T, class Policies>
	class GetValueObject : public ValueObject
	{
	public:
		GetValueObject(const VeChar8* pcName, const T& tVal, Policies kPolicies)
			: ValueObject(TYPE_READ, pcName), m_tValue(tVal), m_kPolicies(kPolicies) {}
		
		virtual VeInt32 Call(lua_State* pkState)
		{
			return Policies::TYPE::RetCall(pkState, m_tValue);
		}

	protected:
		const T& m_tValue;
		Policies m_kPolicies;

	};

	template <class T, class Policies>
	ValueObjectPtr MakeGetValue(const VeChar8* pcName, const T& tVal, Policies kPolicies)
	{
		return VE_NEW GetValueObject<T,Policies>(pcName, tVal, kPolicies);
	}

	template <class T, class Policies>
	class ReadValueObject : public ValueObject
	{
	public:
		ReadValueObject(const VeChar8* pcName, const T& (*pfuncRead)(), Policies kPolicies)
			: ValueObject(TYPE_READ, pcName), m_pfuncRead(pfuncRead), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			return Policies::TYPE::RetCall(pkState, m_pfuncRead());
		}

		const T& (*m_pfuncRead)();
		Policies m_kPolicies;

	};

	template <class T, class Policies>
	ValueObjectPtr MakeReadValue(const VeChar8* pcName, const T& (*pfuncRead)(), Policies kPolicies)
	{
		return VE_NEW ReadValueObject<T,Policies>(pcName, pfuncRead, kPolicies);
	}

	template <class T, class Policies>
	class SetValueObject : public ValueObject
	{
	public:
		SetValueObject(const VeChar8* pcName, T& tVal, Policies kPolicies)
			: ValueObject(TYPE_WRITE, pcName), m_tValue(tVal), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			if(Policies::TYPE::TestCall(ParamType<T>(), pkState, 3) >= 0)
			{
				m_tValue = Policies::TYPE::GetCall(ParamType<T>(), pkState, 3);
				Policies::TYPE::FillCall(pkState, 3, m_tValue);
			}
			return 0;
		}

		T& m_tValue;
		Policies m_kPolicies;
	};

	template <class T, class Policies>
	ValueObjectPtr MakeSetValue(const VeChar8* pcName, T& tVal, Policies kPolicies)
	{
		return VE_NEW SetValueObject<T,Policies>(pcName, tVal, kPolicies);
	}

	template <class T, class Policies>
	class WriteValueObject : public ValueObject
	{
	public:
		WriteValueObject(const VeChar8* pcName, void (*pfuncWrite)(const T&), Policies kPolicies)
			: ValueObject(TYPE_WRITE, pcName), m_pfuncWrite(pfuncWrite), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			if(Policies::TYPE::TestCall(ParamType<T>(), pkState, 3) >= 0)
			{
				T tVal = Policies::TYPE::GetCall(ParamType<T>(), pkState, 3);
				Policies::TYPE::FillCall(pkState, 3, tVal);
				m_pfuncWrite(tVal);
			}
			return 0;
		}

		void (*m_pfuncWrite)(const T&);
		Policies m_kPolicies;
	};

	template <class T, class Policies>
	ValueObjectPtr MakeWriteValue(const VeChar8* pcName, void (*pfuncWrite)(const T&), Policies kPolicies)
	{
		return VE_NEW WriteValueObject<T,Policies>(pcName, pfuncWrite, kPolicies);
	}

	class ClassContent;

	VeSmartPointer(ConstructorObject);

	class VE_POWER_API ConstructorObject : public Object
	{
		VeDeclareRTTI;
	public:
		ConstructorObject()
		{
			m_kFullName = Content::GetCurrent().m_kFullName + ".Constructor";
		}

		virtual ~ConstructorObject() {}

		void Register(lua_State* pkState);

		virtual VeInt32 Call(lua_State* pkState) = 0;

		static VeInt32 EntryPoint(lua_State* pkState);

	protected:
		ConstructorObjectPtr m_spNext;

	};

	template <class F, class Policies>
	class ConstructorObjectImpl : public ConstructorObject
	{
	public:
		ConstructorObjectImpl(F pfuncCall, Policies kPolicies)
			: m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			VeInt32 i32Ret = Invoke(pkState, 2, m_kPolicies, m_pfuncCall);
			if(i32Ret < 0 && m_spNext)
			{
				return m_spNext->Call(pkState);
			}
			else
			{
				return i32Ret;
			}
		}

		F m_pfuncCall;
		Policies m_kPolicies;

	};

	template <class F, class Policies>
	ConstructorObjectPtr MakeConstructor(F pfuncCall, Policies kPolicies)
	{
		return VE_NEW ConstructorObjectImpl<F,Policies>(pfuncCall, kPolicies);
	}

	VeSmartPointer(MemberObject);

	class VE_POWER_API MemberObject : public Object
	{
		VeDeclareRTTI;
	public:
		enum Type
		{
			TYPE_READ,
			TYPE_WRITE
		};

		MemberObject(Type eType, const VeChar8* pcName) : m_eType(eType), m_kName(pcName)
		{
			m_kFullName = Content::GetCurrent().m_kFullName + "." + pcName;
		}

		virtual ~MemberObject() {}

		virtual void Register(lua_State* pkState);

		virtual VeInt32 Call(lua_State* pkState) = 0;

	protected:
		const Type m_eType;
		VeFixedString m_kName;

	};

	template <class C, class T, class Policies>
	class GetMemberPropertyObject : public MemberObject
	{
	public:
		GetMemberPropertyObject(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
			: MemberObject(TYPE_READ, pcName), m_pmVal(pmVal), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			if(TestParam(ParamType<C*>(), pkState, 1) == 1)
			{
				C* pkSelf = GetParam(ParamType<C*>(), pkState, 1);
				VE_ASSERT(pkSelf);
				return Policies::TYPE::RetCall(pkState, pkSelf->*m_pmVal);
			}
			else
			{
				return 0;
			}
		}

		T C::*m_pmVal;
		Policies m_kPolicies;

	};

	template <class C, class T, class Policies>
	MemberObjectPtr MakeGetMemberProperty(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
	{
		return VE_NEW GetMemberPropertyObject<C,T,Policies>(pcName, pmVal, kPolicies);
	}

	template <class C, class T, class Policies>
	class ReadMemberPropertyObject : public MemberObject
	{
	public:
		ReadMemberPropertyObject(const VeChar8* pcName, const T& (C::*pfuncRead)(), Policies kPolicies)
			: MemberObject(TYPE_READ, pcName), m_pfuncRead(pfuncRead), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			if(TestParam(ParamType<C*>(), pkState, 1) == 1)
			{
				C* pkSelf = GetParam(ParamType<C*>(), pkState, 1);
				VE_ASSERT(pkSelf);
				return Policies::TYPE::RetCall(pkState, (pkSelf->*m_pfuncRead)());
			}
			else
			{
				return 0;
			}
		}

		const T& (C::*m_pfuncRead)();
		Policies m_kPolicies;

	};

	template <class C, class T, class Policies>
	MemberObjectPtr MakeReadMemberProperty(const VeChar8* pcName, const T& (C::*pfuncRead)(), Policies kPolicies)
	{
		return VE_NEW ReadMemberPropertyObject<C,T,Policies>(pcName, pfuncRead, kPolicies);
	}

	template <class C, class T, class Policies>
	class SetMemberPropertyObject : public MemberObject
	{
	public:
		SetMemberPropertyObject(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
			: MemberObject(TYPE_WRITE, pcName), m_pmVal(pmVal), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			if(TestParam(ParamType<C*>(), pkState, 1) == 1 && Policies::TYPE::TestCall(ParamType<T>(), pkState, 3) >= 0)
			{
				C* pkSelf = GetParam(ParamType<C*>(), pkState, 1);
				VE_ASSERT(pkSelf);
				pkSelf->*m_pmVal = Policies::TYPE::GetCall(ParamType<T>(), pkState, 3);
				Policies::TYPE::FillCall(pkState, 3, pkSelf->*m_pmVal);
			}
			return 0;
		}

		T C::*m_pmVal;
		Policies m_kPolicies;

	};

	template <class C, class T, class Policies>
	MemberObjectPtr MakeSetMemberProperty(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
	{
		return VE_NEW SetMemberPropertyObject<C,T,Policies>(pcName, pmVal, kPolicies);
	}

	template <class C, class T, class Policies>
	class WriteMemberPropertyObject : public MemberObject
	{
	public:
		WriteMemberPropertyObject(const VeChar8* pcName, void (C::*pfuncWrite)(const T&), Policies kPolicies)
			: MemberObject(TYPE_WRITE, pcName), m_pfuncWrite(pfuncWrite), m_kPolicies(kPolicies) {}

		virtual VeInt32 Call(lua_State* pkState)
		{
			if(TestParam(ParamType<C*>(), pkState, 1) == 1 && Policies::TYPE::TestCall(ParamType<T>(), pkState, 3) >= 0)
			{
				C* pkSelf = GetParam(ParamType<C*>(), pkState, 1);
				VE_ASSERT(pkSelf);
				T tVal = Policies::TYPE::GetCall(ParamType<T>(), pkState, 3);
				Policies::TYPE::FillCall(pkState, 3, tVal);
				(pkSelf->*m_pfuncWrite)(tVal);
			}
			return 0;
		}

		void (C::*m_pfuncWrite)(const T&);
		Policies m_kPolicies;

	};

	template <class C, class T, class Policies>
	MemberObjectPtr MakeWriteMemberProperty(const VeChar8* pcName, void (C::*pfuncWrite)(const T&), Policies kPolicies)
	{
		return VE_NEW WriteMemberPropertyObject<C,T,Policies>(pcName, pfuncWrite, kPolicies);
	}

	VeSmartPointer(MemberFunctionObject);

	class VE_POWER_API MemberFunctionObject : public MemberObject
	{
		VeDeclareRTTI;
	public:
		MemberFunctionObject(const VeChar8* pcName)
			: MemberObject(TYPE_READ, pcName)
		{
			m_kFullName = Content::GetCurrent().m_kFullName + "." + pcName;
		}

		virtual void Register(lua_State* pkState);

		virtual VeInt32 Call(lua_State* pkState);

		virtual VeInt32 CallFunction(lua_State* pkState, void* pvSelf, VeInt32 i32Bias) = 0;

		static VeInt32 EntryPoint(lua_State* pkState);

	protected:
		MemberFunctionObjectPtr m_spNext;

	};

	template <class F, class Policies>
	class MemberFunctionObjectImpl : public MemberFunctionObject
	{
	public:
		MemberFunctionObjectImpl(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
			: MemberFunctionObject(pcName), m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual VeInt32 CallFunction(lua_State* pkState, void* pvSelf, VeInt32 i32Bias)
		{
			VeInt32 i32Ret = Invoke(pkState, m_kPolicies, pvSelf, i32Bias, m_pfuncCall);
			if(i32Ret < 0 && m_spNext)
			{
				return m_spNext->CallFunction(pkState, pvSelf, i32Bias);
			}
			else
			{
				return i32Ret;
			}
		}

		F m_pfuncCall;
		Policies m_kPolicies;

	};

	template <class F, class Policies>
	MemberObjectPtr MakeMemberFunction(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
	{
		return VE_NEW MemberFunctionObjectImpl<F,Policies>(pcName, pfuncCall, kPolicies);
	}

	class VE_POWER_API ClassContent : public Content
	{
		VeDeclareRTTI;
	public:
		ClassContent(const VeChar8* pcName) : m_kName(pcName) {}

		void* AdjustPointer(void* pvPointer, ClassContent* pkClass);

		virtual VeInt32 NewIndex(lua_State* pkState);

		VeInt32 MemberIndex(lua_State* pkState);

		VeInt32 MemberNewIndex(lua_State* pkState);

		VeFixedString m_kName;
		VeVector< VePair<const ClassContentPointer*,VeSizeT> > m_kBaseList;
		ConstructorObjectPtr m_spConstructor;
		VeStringMap<VeUInt32> m_kReadMemberMap;
		VeVector<MemberObjectPtr> m_kReadMemberArray;
		VeStringMap<VeUInt32> m_kWriteMemberMap;
		VeVector<MemberObjectPtr> m_kWriteMemberArray;
		FunctionObjectPtr m_aspOperators[OP_MAX];

	};

	class Scope;

	VeSmartPointer(Regist);

	class VE_POWER_API Regist : public VeRefObject
	{
	public:
		Regist();

		virtual ~Regist();

	protected:
		virtual void Register(lua_State* pkState) = 0;

	private:
		friend class Scope;
		RegistPtr m_spNext;

	};

	class VE_POWER_API Scope : public VeMemObject
	{
	public:
		Scope();

		explicit Scope(RegistPtr& spRegist);

		Scope(const Scope& kOther);

		~Scope();

		Scope& operator = (const Scope& kOther);

		Scope& operator , (Scope kScope);

		void Register(lua_State* pkState) const;

	protected:
		RegistPtr m_spChain;

	};

	class VE_POWER_API NameSpace : public Scope
	{
	public:
		class Regist : public VeLuaBind::Regist
		{
		public:
			Regist(const VeChar8* pcName);

			virtual void Register(lua_State* pkState);

			const VeChar8* m_pcName;
			Scope m_kScope;

		};

		NameSpace(const VeChar8* pcName);

		NameSpace& operator [] (Scope kScope);

	};

	class VE_POWER_API ClassRegist : public Regist
	{
	public:
		ClassRegist(const VeChar8* pcName, ClassContentPointer& pkContent);

		virtual void Register(lua_State* pkState);

		const VeChar8* m_pcName;
		ClassContentPointer& m_pkClassContent;
		Scope m_kScope;
		Scope m_kMembers;

	};

	VeSmartPointer(ClassRegist);

	template <class F, class Policies>
	class ConstructorRegist : public Regist
	{
	public:
		ConstructorRegist(F pfuncCall, Policies kPolicies)
			: m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeConstructor(m_pfuncCall, m_kPolicies)->Register(pkState);
		}

		F m_pfuncCall;
		Policies m_kPolicies;
	};

	template <class F, class Policies>
	RegistPtr MakeConstructorRegist(F pfuncCall, Policies kPolicies)
	{
		return VE_NEW ConstructorRegist<F,Policies>(pfuncCall, kPolicies);
	}

	template <class C, class T, class Policies>
	class GetMemberPropertyRegist : public Regist
	{
	public:
		GetMemberPropertyRegist(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
			: m_pcName(pcName), m_pmVal(pmVal), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeGetMemberProperty(m_pcName, m_pmVal, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		T C::*m_pmVal;
		Policies m_kPolicies;
	};

	template <class C, class T, class Policies>
	RegistPtr MakeGetMemberPropertyRegist(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
	{
		return VE_NEW GetMemberPropertyRegist<C,T,Policies>(pcName, pmVal, kPolicies);
	}

	template <class C, class T, class Policies>
	class ReadMemberPropertyRegist : public Regist
	{
	public:
		ReadMemberPropertyRegist(const VeChar8* pcName, const T& (C::*pfuncRead)(), Policies kPolicies)
			: m_pcName(pcName), m_pfuncRead(pfuncRead), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeReadMemberProperty(m_pcName, m_pfuncRead, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		const T& (C::*m_pfuncRead)();
		Policies m_kPolicies;
	};

	template <class C, class T, class Policies>
	RegistPtr MakeReadMemberPropertyRegist(const VeChar8* pcName, const T& (C::*pfuncRead)(), Policies kPolicies)
	{
		return VE_NEW ReadMemberPropertyRegist<C,T,Policies>(pcName, pfuncRead, kPolicies);
	}

	template <class C, class T, class Policies>
	class SetMemberPropertyRegist : public Regist
	{
	public:
		SetMemberPropertyRegist(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
			: m_pcName(pcName), m_pmVal(pmVal), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeSetMemberProperty(m_pcName, m_pmVal, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		T C::*m_pmVal;
		Policies m_kPolicies;
	};

	template <class C, class T, class Policies>
	RegistPtr MakeSetMemberPropertyRegist(const VeChar8* pcName, T C::*pmVal, Policies kPolicies)
	{
		return VE_NEW SetMemberPropertyRegist<C,T,Policies>(pcName, pmVal, kPolicies);
	}

	template <class C, class T, class Policies>
	class WriteMemberPropertyRegist : public Regist
	{
	public:
		WriteMemberPropertyRegist(const VeChar8* pcName, void (C::*pfuncWrite)(const T&), Policies kPolicies)
			: m_pcName(pcName), m_pfuncWrite(pfuncWrite), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeWriteMemberProperty(m_pcName, m_pfuncWrite, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		void (C::*m_pfuncWrite)(const T&);
		Policies m_kPolicies;
	};

	template <class C, class T, class Policies>
	RegistPtr MakeWriteMemberPropertyRegist(const VeChar8* pcName, void (C::*pfuncWrite)(const T&), Policies kPolicies)
	{
		return VE_NEW WriteMemberPropertyRegist<C,T,Policies>(pcName, pfuncWrite, kPolicies);
	}

	template <class F, class Policies>
	class MemberFunctionRegist : public Regist
	{
	public:
		MemberFunctionRegist(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
			: m_pcName(pcName), m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeMemberFunction(m_pcName, m_pfuncCall, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		F m_pfuncCall;
		Policies m_kPolicies;
	};

	template <class F, class Policies>
	RegistPtr MakeMemberFunctionRegist(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
	{
		return VE_NEW MemberFunctionRegist<F,Policies>(pcName, pfuncCall, kPolicies);
	}

	template <class F, class Policies>
	class OperatorRegist : public Regist
	{
	public:
		OperatorRegist(Operator eOperator, F pfuncCall, Policies kPolicies)
			: m_eOperator(eOperator), m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeFunction(GetOperatorName(m_eOperator), m_pfuncCall, m_kPolicies)->RegisterOperator(pkState, m_eOperator);
		}

		Operator m_eOperator;
		F m_pfuncCall;
		Policies m_kPolicies;
	};

	template <class F, class Policies>
	RegistPtr MakeOperatorRegist(Operator eOperator, F pfuncCall, Policies kPolicies)
	{
		return VE_NEW OperatorRegist<F,Policies>(eOperator, pfuncCall, kPolicies);
	}

	template<class T>
	class ClassBase : public Scope
	{
	public:
		ClassBase& operator [] (Scope kScope)
		{
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (kScope);
			return *this;
		}

		template<class Policies>
		ClassBase& Def(ConstructorNew<void> kCon, Policies kPolicies)
		{
			RegistPtr spReg = MakeConstructorRegist(&NewObject<T>, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this;
		}

		ClassBase& Def(ConstructorNew<void> kCon)
		{
			return Def<NullType>(kCon, NullType());
		}

		template<class Policies>
		ClassBase& Def(Constructor<void> kCon, Policies kPolicies)
		{
			RegistPtr spReg = MakeConstructorRegist(&ToObject<T>, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this;
		}

		ClassBase& Def(Constructor<void> kCon)
		{
			return Def<NullType>(kCon, NullType());
		}

		template<class Con, class Policies>
		ClassBase& Def(Con kCon, Policies kPolicies)
		{
			RegistPtr spReg = kCon.MakeRegist((T*)NULL, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this;
		}

		template<class Con>
		ClassBase& Def(Con kCon)
		{
			return Def<Con,NullType>(kCon, NullType());
		}

		template<class P, class Policies>
		ClassBase& DefRead(const VeChar8* pcName, P T::*pmVal, Policies kPolicies)
		{
			RegistPtr spReg = MakeGetMemberPropertyRegist(pcName, pmVal, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this; 
		}

		template<class P>
		ClassBase& DefRead(const VeChar8* pcName, P T::*pmVal)
		{
			return DefRead<P,NullType>(pcName, pmVal, NullType());
		}

		template<class P, class Policies>
		ClassBase& DefRead(const VeChar8* pcName, P& (T::*pfuncRead)(), Policies kPolicies)
		{
			RegistPtr spReg = MakeReadMemberPropertyRegist(pcName, pfuncRead, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this; 
		}

		template<class P>
		ClassBase& DefRead(const VeChar8* pcName, P& (T::*pfuncRead)())
		{
			return DefRead<P,NullType>(pcName, pfuncRead, NullType());
		}

		template<class P, class Policies>
		ClassBase& DefWrite(const VeChar8* pcName, P T::*pmVal, Policies kPolicies)
		{
			RegistPtr spReg = MakeSetMemberPropertyRegist(pcName, pmVal, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this; 
		}

		template<class P>
		ClassBase& DefWrite(const VeChar8* pcName, P T::*pmVal)
		{
			return DefWrite<P,NullType>(pcName, pmVal, NullType());
		}

		template<class P, class Policies>
		ClassBase& DefWrite(const VeChar8* pcName, void (T::*pfuncWrite)(const P&), Policies kPolicies)
		{
			RegistPtr spReg = MakeWriteMemberPropertyRegist(pcName, pfuncWrite, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this; 
		}

		template<class P>
		ClassBase& DefWrite(const VeChar8* pcName, void (T::*pfuncWrite)(const P&))
		{
			return DefWrite<P,NullType>(pcName, pfuncWrite, NullType());
		}

		template<class P, class Policies>
		ClassBase& DefReadWrite(const VeChar8* pcName, P T::*pmVal, Policies kPolicies)
		{
			return DefRead(pcName, pmVal, kPolicies).DefWrite(pcName, pmVal, kPolicies);
		}

		template<class P>
		ClassBase& DefReadWrite(const VeChar8* pcName, P T::*pmVal)
		{
			return DefReadWrite<P,NullType>(pcName, pmVal, NullType());
		}

		template<class F, class Policies>
		ClassBase& Def(const VeChar8* pcName, F pfunCall, Policies kPolicies)
		{
			RegistPtr spReg = MakeMemberFunctionRegist(pcName, pfunCall, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this;
		}

		template<class F>
		ClassBase& Def(const VeChar8* pcName, F pfunCall)
		{
			return Def<F,NullType>(pcName, pfunCall, NullType());
		}

		template<class F, class Policies>
		ClassBase& DefAdd(F pfunCall, Policies kPolicies)
		{
			RegistPtr spReg = MakeOperatorRegist(OP_ADD, pfunCall, kPolicies);
			VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg));
			return *this;
		}

		VE_LUA_OP(OpAdd, OP_ADD);
		VE_LUA_OP(OpSub, OP_SUB);
		VE_LUA_OP(OpMul, OP_MUL);
		VE_LUA_OP(OpDiv, OP_DIV);
		VE_LUA_OP(OpMod, OP_MOD);
		VE_LUA_OP(OpPow, OP_POW);
		VE_LUA_OP(OpUnm, OP_UNM);
		VE_LUA_OP(OpConcat, OP_CONCAT);
		VE_LUA_OP(OpLen, OP_LEN);
		VE_LUA_OP(OpEq, OP_EQ);
		VE_LUA_OP(OpLt, OP_LT);
		VE_LUA_OP(OpLe, OP_LE);
		VE_LUA_OP(OpCall, OP_CALL);
		VE_LUA_OP(OpToStr, OP_TO_STR);
		VE_LUA_OP(OpIndex, OP_INDEX);
		VE_LUA_OP(OpNewIndex, OP_NEWINDEX);

		static ClassContentPointer& GetClassContent()
		{
			return T::ms_pkLuaBindClass;
		}

	};

	template<class T, class B = void>
	class Class : public ClassBase<T>
	{
	public:
		Class(const VeChar8* pcName = T::GetClassName())
		{
			ClassRegistPtr spRegist = VE_NEW ClassRegist(pcName, ClassBase<T>::GetClassContent());
			B::GetClassContentList((T*)NULL, spRegist->m_pkClassContent->m_kBaseList);
			this->m_spChain = spRegist.p();
		}
        
	};

	template<class T>
	class Class<T,void> : public ClassBase<T>
	{
	public:
		Class(const VeChar8* pcName = T::GetClassName())
		{
			this->m_spChain = VE_NEW ClassRegist(pcName, ClassBase<T>::GetClassContent());
		}

	};

	template<class Ret,class P1,class P2>
	Ret OpFuncAdd(P1 p1, P2 p2)
	{
		return p1 + p2;
	}

	template<class Ret,class P1,class P2>
	Ret OpFuncSub(P1 p1, P2 p2)
	{
		return p1 - p2;
	}

	template<class Ret,class P1,class P2>
	Ret OpFuncMul(P1 p1, P2 p2)
	{
		return p1 * p2;
	}

	template<class Ret,class P1,class P2>
	Ret OpFuncDiv(P1 p1, P2 p2)
	{
		return p1 / p2;
	}

	template<class Ret,class P1,class P2>
	Ret OpFuncMod(P1 p1, P2 p2)
	{
		return p1 % p2;
	}

	template<class Ret,class P1,class P2>
	Ret OpFuncPow(P1 p1, P2 p2)
	{
		return p1 ^ p2;
	}

	template<class Ret,class P1>
	Ret OpFuncUnm(P1 p1)
	{
		return -p1;
	}

	template<class P1,class P2>
	bool OpFuncEq(P1 p1, P2 p2)
	{
		return p1 == p2;
	}

	template<class P1,class P2>
	bool OpFuncLt(P1 p1, P2 p2)
	{
		return p1 < p2;
	}

	template<class P1,class P2>
	bool OpFuncLe(P1 p1, P2 p2)
	{
		return p1 <= p2;
	}

	class VE_POWER_API Module : public VeMemObject
	{
	public:
		Module(const VeChar8* pcName = NULL, lua_State* pkState = g_pLua->GetLua());

		void operator [] (Scope kScope);

	private:
		lua_State* m_pkState;
		const VeChar8* m_pcName;

	};

	template <class F, class Policies>
	class FunctionRegist : public Regist
	{
	public:
		FunctionRegist(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
			: m_pcName(pcName), m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeFunction(m_pcName, m_pfuncCall, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		F m_pfuncCall;
		Policies m_kPolicies;
	};

	template <class T, class F, class Policies>
	class SingletonFunctionRegist : public Regist
	{
	public:
		SingletonFunctionRegist(const VeChar8* pcName, T*& pkObj, F pfuncCall, Policies kPolicies)
			: m_pcName(pcName), m_pkSingleton(pkObj), m_pfuncCall(pfuncCall), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeFunction(m_pcName, m_pkSingleton, m_pfuncCall, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		T*& m_pkSingleton;
		F m_pfuncCall;
		Policies m_kPolicies;
	};

	class ManualFunctionRegist : public Regist
	{
	public:
		ManualFunctionRegist(const VeChar8* pcName, ManualFunctionObject::Func pfuncCall)
			: m_pcName(pcName), m_pfuncCall(pfuncCall) {}

		virtual void Register(lua_State* pkState)
		{
			FunctionObjectPtr spObject = VE_NEW ManualFunctionObject(m_pcName, m_pfuncCall);
			spObject->Register(pkState);
		}

		const VeChar8* m_pcName;
		ManualFunctionObject::Func m_pfuncCall;

	};

	template <class T, class Policies>
	class GetValueRegist : public Regist
	{
	public:
		GetValueRegist(const VeChar8* pcName, const T& tVal, Policies kPolicies)
			: m_pcName(pcName), m_tValue(tVal), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeGetValue(m_pcName, m_tValue, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		const T& m_tValue;
		Policies m_kPolicies;
	};

	template <class T, class Policies>
	class ReadValueRegist : public Regist
	{
	public:
		ReadValueRegist(const VeChar8* pcName, const T& (*pfuncRead)(), Policies kPolicies)
			: m_pcName(pcName), m_pfuncRead(pfuncRead), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeReadValue(m_pcName, m_pfuncRead, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		const T& (*m_pfuncRead)();
		Policies m_kPolicies;
	};

	template <class T, class Policies>
	class SetValueRegist : public Regist
	{
	public:
		SetValueRegist(const VeChar8* pcName, T& tVal, Policies kPolicies)
			: m_pcName(pcName), m_tValue(tVal), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeSetValue(m_pcName, m_tValue, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		T& m_tValue;
		Policies m_kPolicies;
	};

	template <class T, class Policies>
	class WriteValueRegist : public Regist
	{
	public:
		WriteValueRegist(const VeChar8* pcName, void (*pfuncWrite)(const T&), Policies kPolicies)
			: m_pcName(pcName), m_pfuncWrite(pfuncWrite), m_kPolicies(kPolicies) {}

		virtual void Register(lua_State* pkState)
		{
			MakeWriteValue(m_pcName, m_pfuncWrite, m_kPolicies)->Register(pkState);
		}

		const VeChar8* m_pcName;
		void (*m_pfuncWrite)(const T&);
		Policies m_kPolicies;
	};

	template <class F, class Policies>
	Scope Def(const VeChar8* pcName, F pfuncCall, Policies kPolicies)
	{
		RegistPtr spRegist = VE_NEW FunctionRegist<F,Policies>(pcName, pfuncCall, kPolicies);
		return Scope(spRegist);
	}

	template <class F>
	Scope Def(const VeChar8* pcName, F pfuncCall)
	{
		return Def(pcName, pfuncCall, NullType());
	}

	template <class T, class F, class Policies>
	Scope DefSingletonFunc(const VeChar8* pcName, T*& pkObj, F pfuncCall, Policies kPolicies)
	{
		RegistPtr spRegist = VE_NEW SingletonFunctionRegist<T,F,Policies>(pcName, pkObj, pfuncCall, kPolicies);
		return Scope(spRegist);
	}

	template <class T, class F>
	Scope DefSingletonFunc(const VeChar8* pcName, T*& pkObj, F pfuncCall)
	{
		return DefSingletonFunc(pcName, pkObj, pfuncCall, NullType());
	}

	VE_INLINE Scope DefManualFunc(const VeChar8* pcName, ManualFunctionObject::Func pfuncCall)
	{
		RegistPtr spRegist = VE_NEW ManualFunctionRegist(pcName, pfuncCall);
		return Scope(spRegist);
	}

	template<class T, class Policies>
	Scope DefRead(const VeChar8* pcName, const T& tVal, Policies kPolicies)
	{
		RegistPtr spRegist = VE_NEW GetValueRegist<T, Policies>(pcName, tVal, kPolicies);
		return Scope(spRegist);
	}

	template<class T>
	Scope DefRead(const VeChar8* pcName, const T& tVal)
	{
		return DefRead<T,NullType>(pcName, tVal, NullType());
	}

	template<class T, class Policies>
	Scope DefRead(const VeChar8* pcName, const T& (*pfuncRead)(), Policies kPolicies)
	{
		RegistPtr spRegist = VE_NEW ReadValueRegist<T, Policies>(pcName, pfuncRead, kPolicies);
		return Scope(spRegist);
	}

	template<class T>
	Scope DefRead(const VeChar8* pcName, const T& (*pfuncRead)())
	{
		return DefRead<T,NullType>(pcName, pfuncRead, NullType());
	}

	template<class T, class Policies>
	Scope DefWrite(const VeChar8* pcName, T& tVal, Policies kPolicies)
	{
		RegistPtr spRegist = VE_NEW SetValueRegist<T, Policies>(pcName, tVal, kPolicies);
		return Scope(spRegist);
	}

	template<class T>
	Scope DefWrite(const VeChar8* pcName, T& tVal)
	{
		return DefWrite<T,NullType>(pcName, tVal, NullType());
	}

	template<class T, class Policies>
	Scope DefWrite(const VeChar8* pcName, void (*pfuncWrite)(const T&), Policies kPolicies)
	{
		RegistPtr spRegist = VE_NEW WriteValueRegist<T, Policies>(pcName, pfuncWrite, kPolicies);
		return Scope(spRegist);
	}

	template<class T>
	Scope DefWrite(const VeChar8* pcName, void (*pfuncWrite)(const T&))
	{
		return DefWrite<T,NullType>(pcName, pfuncWrite, NullType());
	}

	template<class T, class Policies>
	Scope DefReadWrite(const VeChar8* pcName, T& tVal, Policies kPolicies)
	{
		return DefRead(pcName, tVal, kPolicies), DefWrite(pcName, tVal, kPolicies);
	}

	template<class T>
	Scope DefReadWrite(const VeChar8* pcName, T& tVal)
	{
		return DefReadWrite<T,NullType>(pcName, tVal, NullType());
	}

	template<class T> struct EnumMap;
	
	template<class T>
	class EnumClass : public VeMemObject
	{
	public:
		typedef void (*RegistFunc) ();

		EnumClass() {}

		EnumClass(T eValue) : m_eValue(eValue) {}

		T GetValue()
		{
			return m_eValue;
		}

		const VeChar8* GetName()
		{
			return ToName(m_eValue);
		}

		const VeChar8* GetAlias()
		{
			return ToAlias(m_eValue);
		}

		static void InitValue(T eValue, const VeChar8* pcName, const VeChar8* pcAlias);

		static const VeChar8* ToName(T eValue);

		static const VeChar8* ToAlias(T eValue);

		static EnumClass<T>& ToEnumClass(T eValue);

		static EnumClass<T>& ToEnumClass(const VeChar8* pcName);

		static T ToEnum(const VeChar8* pcName, T eDefault);

	protected:
		T m_eValue;
		static EnumMap<T>* ms_pkEnumMap;

	public:
		static const VeLuaBind::ClassContentPointer& GetLuaBindClass() { return ms_pkLuaBindClass; }
		static const VeChar8* GetClassName() { return ms_pcName; }
		static void LuaBindInit();
		static void LuaBindTerm();

	private:
		friend class VeLuaBind::ClassBase<EnumClass>;
		static VeLuaBind::ClassContent* ms_pkLuaBindClass;
		static RegistFunc ms_pfuncRegist;
		static const VeChar8* ms_pcName;

	};

	template<class T>
	struct EnumMap : public VeMemObject
	{
		VeStringMap<VeUInt32> m_kNameMap;
		VeMap<T,VeUInt32> m_kValueMap;
		VeVector< VePair< EnumClass<T>, VePair<const VeChar8*, const VeChar8*> > > m_kList;
	};

	template<class T>
	void EnumClass<T>::LuaBindInit()
	{
		ms_pkEnumMap = VE_NEW EnumMap<T>();
		ms_pfuncRegist();
	}

	template<class T>
	void EnumClass<T>::LuaBindTerm()
	{
		if(ms_pkLuaBindClass)
		{
			((VeRefObject*)ms_pkLuaBindClass)->DecRefCount();
			ms_pkLuaBindClass = NULL;
		}
		VE_SAFE_DELETE(ms_pkEnumMap);
	}

	template<class T>
	void EnumClass<T>::InitValue(T eValue, const VeChar8* pcName, const VeChar8* pcAlias)
	{
		VE_ASSERT(ms_pkEnumMap);
		ms_pkEnumMap->m_kNameMap[pcName] = ms_pkEnumMap->m_kList.Size();
		ms_pkEnumMap->m_kNameMap[pcAlias] = ms_pkEnumMap->m_kList.Size();
		ms_pkEnumMap->m_kValueMap[eValue] = ms_pkEnumMap->m_kList.Size();
		ms_pkEnumMap->m_kList.Increase();
		ms_pkEnumMap->m_kList.Back().m_tFirst.m_eValue = eValue;
		ms_pkEnumMap->m_kList.Back().m_tSecond.m_tFirst = pcName;
		ms_pkEnumMap->m_kList.Back().m_tSecond.m_tSecond = pcAlias;
	}

	template<class T>
	const VeChar8* EnumClass<T>::ToName(T eValue)
	{
		VE_ASSERT(ms_pkEnumMap && ms_pkEnumMap->m_kValueMap.Find(eValue) != ms_pkEnumMap->m_kValueMap.End());
		return ms_pkEnumMap->m_kList[ms_pkEnumMap->m_kValueMap[eValue]].m_tSecond.m_tFirst;
	}

	template<class T>
	const VeChar8* EnumClass<T>::ToAlias(T eValue)
	{
		VE_ASSERT(ms_pkEnumMap && ms_pkEnumMap->m_kValueMap.Find(eValue) != ms_pkEnumMap->m_kValueMap.End());
		return ms_pkEnumMap->m_kList[ms_pkEnumMap->m_kValueMap[eValue]].m_tSecond.m_tSecond;
	}

	template<class T>
	EnumClass<T>& EnumClass<T>::ToEnumClass(T eValue)
	{
		VE_ASSERT(ms_pkEnumMap && ms_pkEnumMap->m_kValueMap.Find(eValue) != ms_pkEnumMap->m_kValueMap.End());
		return ms_pkEnumMap->m_kList[ms_pkEnumMap->m_kValueMap[eValue]].m_tFirst;
	}

	template<class T>
	EnumClass<T>& EnumClass<T>::ToEnumClass(const VeChar8* pcName)
	{
		VE_ASSERT(ms_pkEnumMap);
		VeUInt32* pu32Iter = ms_pkEnumMap->m_kNameMap.Find(pcName);
		VE_ASSERT(pu32Iter);
		return ms_pkEnumMap->m_kList[*pu32Iter].m_tFirst;
	}

	template<class T>
	T VeLuaBind::EnumClass<T>::ToEnum(const VeChar8* pcName, T eDefault)
	{
		VE_ASSERT(ms_pkEnumMap);
		VeUInt32* pu32Iter = ms_pkEnumMap->m_kNameMap.Find(pcName);
		if(pu32Iter)
		{
			return ms_pkEnumMap->m_kList[*pu32Iter].m_tFirst.m_eValue;
		}
		else
		{
			return eDefault;
		}
	}

	VE_POWER_API void Init();

	VE_POWER_API void Term();

	VE_POWER_API void Export(void (*pfuncInit)(), void (*pfuncTerm)());

	VE_POWER_API extern VeChar8 g_acPrintBuffer[1024];

}

#define _default_ VeLuaBind::DefaultPolicy::Policy()
#define VePolicy(...) (__VA_ARGS__)
#define VeLuaCall VeLuaBind::Call
#define VeLuaExport(classname) VeLuaBind::Export(classname::LuaBindInit,classname::LuaBindTerm)
#define VeLuaExportEnum(enumname) VeLuaExport(VeLuaBind::EnumClass<enumname>)
#define VeLuaEnumDef(enumname) \
	typedef VeLuaBind::EnumClass<enumname> enumname##Lua; \
	void enumname##Regist()
#define VeLuaEnumFuncDef(api,enumname) \
	api VeInt32 TestParam(ParamType<enumname>, lua_State* pkState, VeInt32 i32Index); \
	api enumname GetParam(ParamType<enumname>, lua_State* pkState, VeInt32 i32Index); \
	api VeInt32 RetParam(lua_State* pkState, enumname& tRet)
#define VeLuaEnumFuncImpl(enumname) \
	VeInt32 TestParam(ParamType<enumname>, lua_State* pkState, VeInt32 i32Index) \
	{ \
		return TestParam(ParamType<enumname##Lua>(), pkState, i32Index); \
	} \
	enumname GetParam(ParamType<enumname>, lua_State* pkState, VeInt32 i32Index) \
	{ \
		return GetParam(ParamType<enumname##Lua>(), pkState, i32Index).GetValue(); \
	} \
	VeInt32 RetParam(lua_State* pkState, enumname& tRet) \
	{ \
		new (CreateLuaMemObject<enumname##Lua>(pkState)) enumname##Lua(tRet); \
		return 1; \
	}
#define VeLuaEnumImpl(enumname) \
	using namespace VeLuaBind; \
	template <> EnumMap<enumname>* enumname##Lua::ms_pkEnumMap = NULL; \
	template <> ClassContent* enumname##Lua::ms_pkLuaBindClass = NULL; \
	template <> EnumClass<enumname>::RegistFunc enumname##Lua::ms_pfuncRegist = enumname##Regist; \
	template <> const VeChar8* enumname##Lua::ms_pcName = #enumname; \
	void enumname##Regist()
#define VeLuaEnumBase(enumname) \
	Module()[Class<enumname##Lua>().Def("GetName", &enumname##Lua::GetName).Def("GetAlias", &enumname##Lua::GetAlias).OpToStr(&enumname##Lua::ToName)]
#define VeLuaEnumSlot(enumname,slot,alias) \
	enumname##Lua::InitValue(slot, #slot, alias); \
	Module() [ \
		DefRead(#slot, enumname##Lua::ToEnumClass(slot)), \
		Class<enumname##Lua>() [ \
			DefRead(#slot, enumname##Lua::ToEnumClass(slot)), \
			DefRead(alias, enumname##Lua::ToEnumClass(slot)) \
		] \
	]
#define VeLuaClassEnumDef(enumname) \
	typedef VeLuaBind::EnumClass<enumname> enumname##Lua; \
	static void enumname##Regist()
#define VeLuaClassEnumFuncDef(api,classname,enumname) \
	api VeInt32 TestParam(ParamType<classname::enumname>, lua_State* pkState, VeInt32 i32Index); \
	api classname::enumname GetParam(ParamType<classname::enumname>, lua_State* pkState, VeInt32 i32Index); \
	api VeInt32 RetParam(lua_State* pkState, classname::enumname& tRet)
#define VeLuaClassEnumFuncImpl(classname,enumname) \
		VeInt32 TestParam(ParamType<classname::enumname>, lua_State* pkState, VeInt32 i32Index) \
		{ \
			return TestParam(ParamType<classname::enumname##Lua>(), pkState, i32Index); \
		} \
		classname::enumname GetParam(ParamType<classname::enumname>, lua_State* pkState, VeInt32 i32Index) \
		{ \
			return GetParam(ParamType<classname::enumname##Lua>(), pkState, i32Index).GetValue(); \
		} \
		VeInt32 RetParam(lua_State* pkState, classname::enumname& tRet) \
		{ \
            new (CreateLuaMemObject<classname::enumname##Lua>(pkState)) classname::enumname##Lua(tRet); \
            return 1; \
		}
#define VeLuaClassEnumImpl(classname,enumname) \
	using namespace VeLuaBind; \
	template <> EnumMap<classname::enumname>* classname::enumname##Lua::ms_pkEnumMap = NULL; \
	template <> ClassContent* classname::enumname##Lua::ms_pkLuaBindClass = NULL; \
	template <> EnumClass<classname::enumname>::RegistFunc classname::enumname##Lua::ms_pfuncRegist = classname::enumname##Regist; \
	template <> const VeChar8* classname::enumname##Lua::ms_pcName = #enumname; \
	void classname::enumname##Regist()
#define VeLuaClassEnumBase(classname,enumname) \
	Module()[Class<classname>()[Class<classname::enumname##Lua>().Def("GetName", &classname::enumname##Lua::GetName).Def("GetAlias", &classname::enumname##Lua::GetAlias).OpToStr(&classname::enumname##Lua::ToName)]]
#define VeLuaClassEnumSlot(classname,enumname,slot,alias) \
	classname::enumname##Lua::InitValue(slot, #slot, alias); \
	Module() [ \
		Class<classname>() [ \
			DefRead(#slot, classname::enumname##Lua::ToEnumClass(slot)), \
			Class<classname::enumname##Lua>() [ \
				DefRead(#slot, classname::enumname##Lua::ToEnumClass(slot)), \
				DefRead(alias, classname::enumname##Lua::ToEnumClass(slot)) \
			] \
		] \
	]
