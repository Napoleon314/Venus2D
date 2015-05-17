////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLuaBindDef.h
//  Version:     v1.00
//  Created:     26/2/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_LUA_PARAM(t,type_name,type_main) \
	VE_FORCE_INLINE VeInt32 TestParam(ParamType<t>, lua_State* pkState, VeInt32 i32Index) \
	{ \
		return Is##type_name(pkState, i32Index) ? 1 : -1; \
	} \
	VE_FORCE_INLINE t GetParam(ParamType<t>, lua_State* pkState, VeInt32 i32Index) \
	{ \
		return (t)To##type_name(pkState, i32Index); \
	} \
	VE_FORCE_INLINE VeInt32 RetParam(lua_State* pkState, t tVal) \
	{ \
		Ret##type_name(pkState, (type_main)tVal); \
		return 1; \
	}

#define VE_LUA_DEFAULT(t,val) \
	template<> VE_FORCE_INLINE t Default(ParamType<t>) { return val; }

#define VE_LUA_HOLD_STACK(L) StackHolder kHolder(L)

#define VE_LUA_OP(op,OP) \
	template<class F, class Policies> \
	ClassBase& op(F pfunCall, Policies kPolicies) \
	{ \
		RegistPtr spReg = MakeOperatorRegist(OP, pfunCall, kPolicies); \
		VeSmartPointerCast(ClassRegist, m_spChain)->m_kScope.operator , (Scope(spReg)); \
		return *this; \
	} \
	template<class F> \
	ClassBase& op(F pfunCall) \
	{ \
		return op<F,NullType>(pfunCall, NullType()); \
	}

namespace VeLuaBind
{
	class VE_POWER_API StackHolder
	{
	public:
		StackHolder(lua_State* pkState);

		~StackHolder();
	private:
		lua_State* m_pkState;
		VeInt32 m_i32Stack;

	};

	VeSmartPointer(Regist);

	class ClassContent;

	template<class C, class B>
	VeSizeT BaseClassBias()
	{
		B* pkBase = (C*)1;
		return VeSizeT(pkBase) - 1;
	}

	typedef VeInt32 (*EntryFunc) (lua_State *L);

	VE_POWER_API bool IsBoolean(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API bool ToBoolean(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API void RetBoolean(lua_State* pkState, bool bVal);

	VE_POWER_API bool IsLightData(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API void* ToLightData(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API void RetLightData(lua_State* pkState, void* pvData);

	VE_POWER_API bool IsNumber(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API VeFloat64 ToNumber(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API void RetNumber(lua_State* pkState, VeFloat64 f64Value);

	VE_POWER_API bool IsString(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API const VeChar8* ToString(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API void RetString(lua_State* pkState, const VeChar8* pcStr);

	VE_POWER_API bool IsUserdata(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API void* ToUserdata(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API bool IsThread(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API lua_State* ToThread(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API bool IsTable(lua_State* pkState, VeInt32 i32Index);

	VE_POWER_API void NewTable(lua_State* pkState);

	VE_POWER_API void RawGet(lua_State* pkState, VeInt32 i32Index, VeInt32 n);

	VE_POWER_API void RawSet(lua_State* pkState, VeInt32 i32Index, VeInt32 n);

	VE_POWER_API VeInt32 Pause(lua_State* pkState, VeInt32 i32CTX = 0, VeInt32 (*pfuncCall)(lua_State*) = NULL);

	VE_POWER_API void Resume(lua_State* pkThread, VeInt32 i32Ref, lua_State* pkState, VeInt32 i32NumArgs);

	VE_POWER_API void ManualReturn(VeUInt32 u32RetNum);

	VE_LUA_PARAM(bool,Boolean,bool);
	VE_LUA_PARAM(void*,LightData,void*);
	VE_LUA_PARAM(const void*,LightData,void*);
	VE_LUA_PARAM(VeInt8,Number,VeFloat64);
	VE_LUA_PARAM(VeInt16,Number,VeFloat64);
	VE_LUA_PARAM(VeInt32,Number,VeFloat64);
	VE_LUA_PARAM(VeInt64,Number,VeFloat64);
	VE_LUA_PARAM(VeUInt8,Number,VeFloat64);
	VE_LUA_PARAM(VeUInt16,Number,VeFloat64);
	VE_LUA_PARAM(VeUInt32,Number,VeFloat64);
	VE_LUA_PARAM(VeUInt64,Number,VeFloat64);
	VE_LUA_PARAM(VeFloat32,Number,VeFloat64);
	VE_LUA_PARAM(VeFloat64,Number,VeFloat64);
	VE_LUA_PARAM(const VeChar8*,String,const VeChar8*);
	VE_LUA_PARAM(VeChar8*,String,const VeChar8*);
	VE_LUA_PARAM(VeFixedString,String,const VeChar8*);
	VE_LUA_PARAM(VeString,String,const VeChar8*);

	enum ObjectPolicyType
	{
		OBJ_LUA_MEM,
		OBJ_LUA_ADOPT,
		OBJ_LUA_REF,
		OBJ_LUA_WEAK_REF
	};

	VE_POWER_API void* CreateObject(lua_State* pkState, ObjectPolicyType eType, VeSizeT stSize, EntryFunc pfuncDestructor, ClassContent* pkClassContent);

	VE_FORCE_INLINE VeUInt32& UserDataFlag(void* pvData)
	{
		return *(VeUInt32*)pvData;
	}

	class ClassContent;

	VE_FORCE_INLINE ClassContent*& UserDataClass(void* pvData)
	{
		return *(ClassContent**)((VeSizeT)pvData + sizeof(VeUInt32));
	}

	VE_FORCE_INLINE void* UserDataObject(void* pvData)
	{
		return (void*)((VeSizeT)pvData + sizeof(VeUInt32) + sizeof(void*));
	}

	template<class T>
	VeInt32 DestructorPointer(lua_State* pkState)
	{
		void* pvData = ToUserdata(pkState, -1);
		switch(UserDataFlag(pvData))
		{
		case OBJ_LUA_MEM:
			((T*)UserDataObject(pvData))->~T();
			break;
		case OBJ_LUA_ADOPT:
			VE_DELETE(*(T**)UserDataObject(pvData));
			break;
		}
		return 0;
	}

	template<class T>
	VeInt32 DestructorRefPointer(lua_State* pkState)
	{
		void* pvData = ToUserdata(pkState, -1);
		switch(UserDataFlag(pvData))
		{
		case OBJ_LUA_MEM:
			((T*)UserDataObject(pvData))->~T();
			break;
		case OBJ_LUA_ADOPT:
			VE_DELETE(*(T**)UserDataObject(pvData));
			break;
		case OBJ_LUA_REF:
			(*(T**)UserDataObject(pvData))->DecRefCount();
			break;
		}
		return 0;
	}

	VE_POWER_API void* AdjustPointer(void* pvPointer, ClassContent* pvSrc, ClassContent* pvDst);

	template<class T>
	void* CreateLuaMemObject(lua_State* pkState)
	{
		return CreateObject(pkState, OBJ_LUA_MEM, sizeof(T), DestructorPointer<T>, T::GetLuaBindClass());
	}

	struct FunctionName
	{
		FunctionName(const VeChar8* pcName) : m_pcName(pcName) {}
		const VeChar8* m_pcName;
	};

	VE_POWER_API VeInt32 RetParam(lua_State* pkState, const FunctionName& kName);

	VE_POWER_API VeInt32 RetParamFunc(lua_State* pkState, VeInt32 i32Ref);

	VE_POWER_API VeInt32 RetParamFunc(lua_State* pkState, VeInt32 (*pfuncCall)(lua_State*), VeInt32 i32Num);

	VE_POWER_API VeInt32 CallFunc(lua_State* pkState, VeInt32 i32ArgNum);

	VE_POWER_API lua_State* MakeFuncThread(lua_State* pkState, const FunctionName& kName);

	VE_POWER_API lua_State* MakeFuncThread(lua_State* pkState, VeInt32 i32Func);

	VE_POWER_API VeInt32 CallFuncThread(lua_State* pkState, lua_State* pkThread, VeInt32 i32ArgNum);

	template<class T>
	T* Default(ParamType<T*>)
	{
		return NULL;
	}

	template<class T>
	T Default(ParamType<T>)
	{
		return T();
	}

	VE_LUA_DEFAULT(bool,false);
	VE_LUA_DEFAULT(VeInt8,0);
	VE_LUA_DEFAULT(VeInt16,0);
	VE_LUA_DEFAULT(VeInt32,0);
	VE_LUA_DEFAULT(VeInt64,0);
	VE_LUA_DEFAULT(VeUInt8,0);
	VE_LUA_DEFAULT(VeUInt16,0);
	VE_LUA_DEFAULT(VeUInt32,0);
	VE_LUA_DEFAULT(VeUInt64,0);
	VE_LUA_DEFAULT(VeFloat32,0);
	VE_LUA_DEFAULT(VeFloat64,0);
	VE_LUA_DEFAULT(const VeChar8*,"");
	VE_LUA_DEFAULT(VeString,"");
	VE_LUA_DEFAULT(VeFixedString,"");

	VE_FORCE_INLINE VeInt32 TestParam(ParamType<lua_State*>, lua_State* pkState, VeInt32 i32Index)
	{
		if(IsThread(pkState, i32Index))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	VE_FORCE_INLINE lua_State* GetParam(ParamType<lua_State*>, lua_State* pkState, VeInt32 i32Index)
	{
		if(IsThread(pkState, i32Index))
		{
			return ToThread(pkState, i32Index);
		}
		else
		{
			return pkState;
		}
	}

	VE_FORCE_INLINE VeInt32 RetParam(lua_State* pkState, lua_State* pkRet)
	{
		return 1;
	}

	VE_FORCE_INLINE VeInt32 TestParam(ParamType<void>, lua_State* pkState, VeInt32 i32Index)
	{
		return 0;
	}

	VE_FORCE_INLINE void GetParam(ParamType<void>, lua_State* pkState, VeInt32 i32Index)
	{

	}

	template<class T>
	VeInt32 TestParam(ParamType<T*>, lua_State* pkState, VeInt32 i32Index)
	{
		if(IsUserdata(pkState, i32Index))
		{
			void* pvData = ToUserdata(pkState, i32Index);
			if(pvData)
			{
				void* pvPointer(NULL);
				if(UserDataFlag(pvData) == OBJ_LUA_MEM)
				{
					pvPointer = UserDataObject(pvData);
				}
				else
				{
					pvPointer = *(void**)UserDataObject(pvData);
				}
				pvPointer = AdjustPointer(pvPointer, UserDataClass(pvData), T::GetLuaBindClass());
				if(pvPointer)
				{
					return 1;
				}
			}
		}
		return -1;
	}

	template<class T>
	T* GetParam(ParamType<T*>, lua_State* pkState, VeInt32 i32Index)
	{
		void* pvData = ToUserdata(pkState, i32Index);
		VE_ASSERT(pvData);
		void* pvPointer(NULL);
		if(UserDataFlag(pvData) == OBJ_LUA_MEM)
		{
			pvPointer = UserDataObject(pvData);
		}
		else
		{
			pvPointer = *(void**)UserDataObject(pvData);
		}
		pvPointer = AdjustPointer(pvPointer, UserDataClass(pvData), T::GetLuaBindClass());
		VE_ASSERT(pvPointer);
		return (T*)pvPointer;
	}

	template<class T>
	VeInt32 RetParam(lua_State* pkState, T* tRet)
	{
		if(tRet)
		{
			tRet->IncRefCount();
			T** pptData = (T**)CreateObject(pkState, OBJ_LUA_REF, sizeof(T), DestructorRefPointer<T>, tRet->GetLuaClassContent());
			*pptData = tRet;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	template<class T>
	VeInt32 TestParam(ParamType<T&>, lua_State* pkState, VeInt32 i32Index)
	{
		return TestParam(ParamType<T*>(), pkState, i32Index);
	}

	template<class T>
	T& GetParam(ParamType<T&>, lua_State* pkState, VeInt32 i32Index)
	{
		return *GetParam(ParamType<T*>(), pkState, i32Index);
	}

	template<class T>
	VeInt32 RetParam(lua_State* pkState, T& tRet)
	{
		new (CreateLuaMemObject<T>(pkState)) T(tRet);
		return 1;
	}

	template<class T>
	VeInt32 TestParam(ParamType<T>, lua_State* pkState, VeInt32 i32Index)
	{
		return TestParam(ParamType<T*>(), pkState, i32Index);
	}

	template<class T>
	T GetParam(ParamType<T>, lua_State* pkState, VeInt32 i32Index)
	{
		return *GetParam(ParamType<T*>(), pkState, i32Index);
	}

	template<class T>
	VeInt32 TestParam(ParamType< VePointer<T> >, lua_State* pkState, VeInt32 i32Index)
	{
		if(IsUserdata(pkState, i32Index))
		{
			void* pvData = ToUserdata(pkState, i32Index);
			if(pvData)
			{
				void* pvPointer(NULL);
				if(UserDataFlag(pvData) == OBJ_LUA_REF)
				{
					pvPointer = *(void**)UserDataObject(pvData);
					pvPointer = AdjustPointer(pvPointer, UserDataClass(pvData), T::GetLuaBindClass());
					if(pvPointer)
					{
						return 1;
					}
				}
			}
		}
		return -1;
	}

	template<class T>
	VePointer<T> GetParam(ParamType< VePointer<T> >, lua_State* pkState, VeInt32 i32Index)
	{
		void* pvData = ToUserdata(pkState, i32Index);
		VE_ASSERT(pvData);
		void* pvPointer(NULL);
		pvPointer = *(void**)UserDataObject(pvData);
		pvPointer = AdjustPointer(pvPointer, UserDataClass(pvData), T::GetLuaBindClass());
		VE_ASSERT(pvPointer);
		return (T*)pvPointer;
	}

	template<class T>
	VeInt32 RetParam(lua_State* pkState, const VePointer<T>& tRet)
	{
		if(tRet)
		{
			tRet->IncRefCount();
			T** pptData = (T**)CreateObject(pkState, OBJ_LUA_REF, sizeof(T), DestructorRefPointer<T>, tRet->GetLuaClassContent());
			*pptData = tRet;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	template<class T>
	void FillParam(lua_State* pkState, VeInt32 i32Index, T& tRet)
	{

	}

	template<class T>
	VeInt32 TestParam(ParamType< VeVector<T> >, lua_State* pkState, VeInt32 i32Index)
	{
		if(IsTable(pkState, i32Index))
		{
			return 1;
		}
		return -1;
	}

	template<class T>
	VeVector<T> GetParam(ParamType< VeVector<T> >, lua_State* pkState, VeInt32 i32Index)
	{
		VE_LUA_HOLD_STACK(pkState);
		VeVector<T> kRet;
		VeInt32 n(1);
		while(true)
		{
			RawGet(pkState, i32Index, n);
			if(TestParam(ParamType<T>(), pkState, -1) == 1)
			{
				kRet.PushBack(GetParam(ParamType<T>(), pkState, -1));
				FillParam(pkState, -1, kRet.Back());
				++n;
			}
			else
			{
				break;
			}
		}
		return kRet;
	}

	template<class T>
	VeInt32 RetParam(lua_State* pkState, VeVector<T> tRet)
	{
		NewTable(pkState);
		for(VeUInt32 i(0); i < tRet.Size(); ++i)
		{
			{
				VE_LUA_HOLD_STACK(pkState);
				if(RetParam(pkState, tRet[i]) == 1)
				{
					RawSet(pkState, -2, i + 1);
				}
			}
		}
		return 1;
	}

	class DefaultPolicy;

	class NullType
	{
	public:
		typedef DefaultPolicy TYPE;
		typedef NullType NEXT;

	};

	template<class H, class T>
	class PolicyCons
	{
	public:
		typedef H TYPE;
		typedef T NEXT;

		template<class U>
		PolicyCons< U, PolicyCons<H,T> > operator , (PolicyCons<U,NullType>)
		{
			return PolicyCons< U, PolicyCons<H,T> > ();
		}

		template<class U>
		PolicyCons< U, PolicyCons<H,T> > operator + (PolicyCons<U,NullType>)
		{
			return PolicyCons< U, PolicyCons<H,T> > ();
		}

		template<class U>
		PolicyCons< U, PolicyCons<H,T> > operator | (PolicyCons<U,NullType>)
		{
			return PolicyCons< U, PolicyCons<H,T> > ();
		}

	};

	class DefaultPolicy
	{
	public:
		template <class T>
		static VeInt32 TestCall(ParamType<T> kType, lua_State* pkState, VeInt32 i32Index)
		{
			return TestParam(kType, pkState, i32Index);
		}

		template <class T>
		static T GetCall(ParamType<T> kType, lua_State* pkState, VeInt32 i32Index)
		{
			return GetParam(kType, pkState, i32Index);
		}

		template <class T>
		static void FillCall(lua_State* pkState, VeInt32 i32Index, T& tVal)
		{
			FillParam(pkState, i32Index, tVal);
		}

		template <class T>
		static VeInt32 PostCall(lua_State* pkState, T& tVal)
		{
			return 0;
		}

		template <class T>
		static VeInt32 RetCall(lua_State* pkState, T& tVal)
		{
			return RetParam(pkState, tVal);
		}

		static PolicyCons<DefaultPolicy,NullType> Policy()
		{
			return PolicyCons<DefaultPolicy,NullType>();
		}

	};
}
