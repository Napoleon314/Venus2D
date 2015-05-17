////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
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

#include "VePowerPCH.h"

extern "C"
{
#	include <lua.h>
#	include <lauxlib.h>
#	include <lualib.h>
}

VeVector<void (*)()> g_kClassInitList;
VeVector<void (*)()> g_kClassTermList;

namespace VeLuaBind
{
//--------------------------------------------------------------------------
StackHolder::StackHolder(lua_State* pkState)
	: m_pkState(pkState), m_i32Stack(lua_gettop(pkState))
{

}
//--------------------------------------------------------------------------
StackHolder::~StackHolder()
{
	lua_settop(m_pkState, m_i32Stack);
}
//--------------------------------------------------------------------------
#ifdef VE_DEBUG
//--------------------------------------------------------------------------
class StackChecker
{
public:
	StackChecker(lua_State* pkState)
		: m_pkState(pkState), m_i32Stack(lua_gettop(pkState)) {}

	~StackChecker()
	{
		VE_ASSERT(m_i32Stack == lua_gettop(m_pkState));
	}

private:
	lua_State* m_pkState;
	VeInt32 m_i32Stack;
};
//--------------------------------------------------------------------------
#define CHECK_STACK(L) StackChecker kStackChecker(L)
//--------------------------------------------------------------------------
#else
//--------------------------------------------------------------------------
#define CHECK_STACK(L)
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
static VeHashMap<lua_State*,VeUInt32>* s_pkContentMap(NULL);
//--------------------------------------------------------------------------
static VeVector<ContentPtr>* s_pkContentVec(NULL);
//--------------------------------------------------------------------------
static ContentPtr s_spContent;
//--------------------------------------------------------------------------
VeChar8 g_acPrintBuffer[1024];
//--------------------------------------------------------------------------
static VeUInt32 s_u32ManualReturn = 0;
static bool s_bPauseFlag = false;
static VeInt32 s_i32CTX = 0;
static lua_CFunction s_pfuncCall = NULL;
static void ClearPase()
{
	s_u32ManualReturn = 0;
	s_bPauseFlag = false;
	s_i32CTX = 0;
	s_pfuncCall = NULL;
}
//--------------------------------------------------------------------------
void Init()
{
	s_pkContentMap = VE_NEW VeHashMap<lua_State*,VeUInt32>;
	s_pkContentVec = VE_NEW VeVector<ContentPtr>;
	if(g_kClassInitList.Size())
	{
		for(VeVector<void (*)()>::iterator it = g_kClassInitList.Begin();
			it != g_kClassInitList.End(); ++it)
		{
			(*it)();
		}
	}
}
//--------------------------------------------------------------------------
void Term()
{
	if(g_kClassTermList.Size())
	{
		for(VeVector<void (*)()>::iterator it = g_kClassTermList.Last();
			it >= g_kClassTermList.Begin(); --it)
		{
			(*it)();
		}
	}
	s_spContent = NULL;
	VE_SAFE_DELETE(s_pkContentMap);
	VE_SAFE_DELETE(s_pkContentVec);
}
//--------------------------------------------------------------------------
void Export(void (*pfuncInit)(), void (*pfuncTerm)())
{
	g_kClassInitList.PushBack(pfuncInit);
	g_kClassTermList.PushBack(pfuncTerm);
}
//--------------------------------------------------------------------------
bool IsBoolean(lua_State* pkState, VeInt32 i32Index)
{
	return lua_type(pkState, i32Index) == LUA_TBOOLEAN;
}
//--------------------------------------------------------------------------
bool ToBoolean(lua_State* pkState, VeInt32 i32Index)
{
	return lua_toboolean(pkState, i32Index) ? true : false;
}
//--------------------------------------------------------------------------
void RetBoolean(lua_State* pkState, bool bVal)
{
	lua_pushboolean(pkState, bVal);
}
//--------------------------------------------------------------------------
bool IsLightData(lua_State* pkState, VeInt32 i32Index)
{
	return lua_type(pkState, i32Index) == LUA_TLIGHTUSERDATA;
}
//--------------------------------------------------------------------------
void* ToLightData(lua_State* pkState, VeInt32 i32Index)
{
	return lua_touserdata(pkState, i32Index);
}
//--------------------------------------------------------------------------
void RetLightData(lua_State* pkState, void* pvData)
{
	lua_pushlightuserdata(pkState, pvData);
}
//--------------------------------------------------------------------------
bool IsNumber(lua_State* pkState, VeInt32 i32Index)
{
	return lua_type(pkState, i32Index) == LUA_TNUMBER;
}
//--------------------------------------------------------------------------
VeFloat64 ToNumber(lua_State* pkState, VeInt32 i32Index)
{
	return lua_tonumber(pkState, i32Index);
}
//--------------------------------------------------------------------------
void RetNumber(lua_State* pkState, VeFloat64 f64Value)
{
	lua_pushnumber(pkState, f64Value);
}
//--------------------------------------------------------------------------
bool IsString(lua_State* pkState, VeInt32 i32Index)
{
	return lua_type(pkState, i32Index) == LUA_TSTRING;
}
//--------------------------------------------------------------------------
const VeChar8* ToString(lua_State* pkState, VeInt32 i32Index)
{
	return lua_tostring(pkState, i32Index);
}
//--------------------------------------------------------------------------
void RetString(lua_State* pkState, const VeChar8* pcStr)
{
	lua_pushstring(pkState, pcStr);
}
//--------------------------------------------------------------------------
bool IsUserdata(lua_State* pkState, VeInt32 i32Index)
{
	return lua_type(pkState, i32Index) == LUA_TUSERDATA;
}
//--------------------------------------------------------------------------
void* ToUserdata(lua_State* pkState, VeInt32 iIndex)
{
	return lua_touserdata(pkState, iIndex);
}
//--------------------------------------------------------------------------
bool IsThread(lua_State* pkState, VeInt32 i32Index)
{
	return lua_type(pkState, i32Index) == LUA_TTHREAD;
}
//--------------------------------------------------------------------------
lua_State* ToThread(lua_State* pkState, VeInt32 i32Index)
{
	return lua_tothread(pkState, i32Index);
}
//--------------------------------------------------------------------------
bool IsTable(lua_State* pkState, VeInt32 i32Index)
{
	return lua_type(pkState, i32Index) == LUA_TTABLE;
}
//--------------------------------------------------------------------------
void NewTable(lua_State* pkState)
{
	lua_newtable(pkState);
}
//--------------------------------------------------------------------------
void RawGet(lua_State* pkState, VeInt32 i32Index, VeInt32 n)
{
	lua_rawgeti(pkState, i32Index, n);
}
//--------------------------------------------------------------------------
void RawSet(lua_State* pkState, VeInt32 i32Index, VeInt32 n)
{
	lua_rawseti(pkState, i32Index, n);
}
//--------------------------------------------------------------------------
VeInt32 Pause(lua_State* pkState, VeInt32 i32CTX, VeInt32 (*pfuncCall)(lua_State*))
{
	s_bPauseFlag = true;
	s_i32CTX = i32CTX;
	s_pfuncCall = pfuncCall;
	lua_pushthread(pkState);
	VE_ASSERT(lua_tothread(pkState, -1) == pkState);
	return luaL_ref(pkState, LUA_REGISTRYINDEX);
}
//--------------------------------------------------------------------------
void Resume(lua_State* pkThread, VeInt32 i32Ref, lua_State* pkState, VeInt32 i32NumArgs)
{
	luaL_unref(pkState, LUA_REGISTRYINDEX, i32Ref);
	lua_resume(pkThread, pkState, i32NumArgs);
}
//--------------------------------------------------------------------------
void ManualReturn(VeUInt32 u32RetNum)
{
	s_u32ManualReturn = u32RetNum;
}
//--------------------------------------------------------------------------
VeInt32 RetParam(lua_State* pkState, const FunctionName& kName)
{
	VeChar8 acBuffer[1024];
	VeStrcpy(acBuffer, kName.m_pcName);
	VeChar8* pcContext;
	VeInt32 i32Top = lua_gettop(pkState);
	lua_pushglobaltable(pkState);
	VeChar8* pcTemp = VeStrtok(acBuffer, ".", &pcContext);
	while(pcTemp)
	{
		lua_pushstring(pkState, pcTemp);
		lua_gettable(pkState, -2);
		pcTemp = VeStrtok(NULL, ".", &pcContext);
	}
	lua_replace(pkState, i32Top + 1);
	lua_settop(pkState, i32Top + 1);
	return (lua_type(pkState, -1) == LUA_TFUNCTION) ? 1 : 0;
}
//--------------------------------------------------------------------------
VeInt32 RetParamFunc(lua_State* pkState, VeInt32 i32Ref)
{
	lua_rawgeti(pkState, LUA_REGISTRYINDEX, i32Ref);
	VE_ASSERT(lua_type(pkState, -1) == LUA_TFUNCTION);
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 RetParamFunc(lua_State* pkState, VeInt32 (*pfuncCall)(lua_State*),
	VeInt32 i32Num)
{
	lua_pushcclosure(pkState, pfuncCall, i32Num);
	VE_ASSERT(lua_type(pkState, -1) == LUA_TFUNCTION);
	return 1 - i32Num;
}
//--------------------------------------------------------------------------
VeInt32 CallFunc(lua_State* pkState, VeInt32 i32ArgNum)
{
	if(lua_pcall(pkState, i32ArgNum, LUA_MULTRET, 0))
	{
		VE_LOG_E("lua", "call func error: %s", lua_tostring(pkState, -1));
		return 0;
	}
	return 1;
}
//--------------------------------------------------------------------------
lua_State* MakeFuncThread(lua_State* pkState, const FunctionName& kName)
{
	VE_LUA_HOLD_STACK(pkState);
	if(RetParam(pkState, kName) != 1) return NULL;
	lua_State* pkThread = lua_newthread(pkState);
	lua_pushvalue(pkState, -2);
	lua_xmove(pkState, pkThread, 1);
	VE_ASSERT(lua_gettop(pkThread) == 1);
	return pkThread;
}
//--------------------------------------------------------------------------
lua_State* MakeFuncThread(lua_State* pkState, VeInt32 i32Func)
{
	VE_LUA_HOLD_STACK(pkState);
	VE_ASSERT(i32Func > 0);
	lua_rawgeti(pkState, LUA_REGISTRYINDEX, i32Func);
	VE_ASSERT(lua_type(pkState, -1) == LUA_TFUNCTION);
	lua_State* pkThread = lua_newthread(pkState);
	lua_pushvalue(pkState, -2);
	lua_xmove(pkState, pkThread, 1);
	VE_ASSERT(lua_gettop(pkThread) == 1);
	return pkThread;
}
//--------------------------------------------------------------------------
VeInt32 CallFuncThread(lua_State* pkState, lua_State* pkThread,
	VeInt32 i32ArgNum)
{
	VeInt32 i32Status = lua_resume(pkThread, pkState, i32ArgNum);
	if(i32Status == LUA_OK || i32Status == LUA_YIELD)
	{
		return 1;
	}
	else
	{
		VE_LOG_E("lua", "call func error: %s", lua_tostring(pkThread, -1));
		lua_settop(pkThread, 0);
		return 0;
	}
}
//--------------------------------------------------------------------------
VeInt32 CallValue(lua_State* pkState)
{
	VE_ASSERT(lua_islightuserdata(pkState, lua_upvalueindex(1)));
	Content* pkContent = (Content*)lua_touserdata(pkState, lua_upvalueindex(1));
	return pkContent->Index(pkState);
}
//--------------------------------------------------------------------------
VeInt32 ClassOperator(lua_State* pkState)
{
	FunctionObject* pkFunc = (FunctionObject*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkFunc)
	{
		return pkFunc->Call(pkState);
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------------------------------
VeInt32 ClassMemberIndex(lua_State* pkState)
{
	if(lua_type(pkState, 2) == LUA_TSTRING)
	{
		void* pvData = lua_touserdata(pkState, 1);
		if(pvData)
		{
			return UserDataClass(pvData)->MemberIndex(pkState);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return ClassOperator(pkState);
	}
}
//--------------------------------------------------------------------------
VeInt32 ClassMemberNewIndex(lua_State* pkState)
{
	if(lua_type(pkState, 2) == LUA_TSTRING)
	{
		void* pvData = lua_touserdata(pkState, 1);
		if(pvData)
		{
			return UserDataClass(pvData)->MemberNewIndex(pkState);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return ClassOperator(pkState);
	}
}
//--------------------------------------------------------------------------
static const VeChar8* s_apcOperatorName[OP_MAX] =
{
	"__add","__sub","__mul","__div","__mod","__pow","__unm",
	"__concat","__len","__eq","__lt","__le","__call","__tostring",
	"__index", "__newindex"
};
//--------------------------------------------------------------------------
const VeChar8* GetOperatorName(Operator eOp)
{
	VE_ASSERT(eOp < OP_MAX);
	return s_apcOperatorName[eOp];
}
//--------------------------------------------------------------------------
void* CreateObject(lua_State* pkState, ObjectPolicyType eType,
	VeSizeT stSize, EntryFunc pfuncDestructor, ClassContent* pkClassContent)
{
	VeSizeT stMem(sizeof(VeUInt32) + sizeof(void*));
	if(eType == OBJ_LUA_MEM)
	{
		stMem += stSize;
	}
	else
	{
		stMem += sizeof(void*);
	}
	void* pvRes = lua_newuserdata(pkState, stMem);
	VE_ASSERT(pvRes);
	lua_newtable(pkState);
	lua_pushstring(pkState, "__gc");
	lua_pushcfunction(pkState, pfuncDestructor);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, GetOperatorName(OP_INDEX));
	lua_pushlightuserdata(pkState, pkClassContent->m_aspOperators[OP_INDEX]);
	lua_pushcclosure(pkState, ClassMemberIndex, 1);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, GetOperatorName(OP_NEWINDEX));
	lua_pushlightuserdata(pkState, pkClassContent->m_aspOperators[OP_NEWINDEX]);
	lua_pushcclosure(pkState, ClassMemberNewIndex, 1);
	lua_rawset(pkState, -3);
	for(VeUInt32 i(0); i < OP_INDEX; ++i)
	{
		lua_pushstring(pkState, GetOperatorName((Operator)i));
		lua_pushlightuserdata(pkState, pkClassContent->m_aspOperators[i]);
		lua_pushcclosure(pkState, ClassOperator, 1);
		lua_rawset(pkState, -3);
	}
	lua_setmetatable(pkState, -2);
	UserDataFlag(pvRes) = eType;
	UserDataClass(pvRes) = pkClassContent;
	return UserDataObject(pvRes);
}
//--------------------------------------------------------------------------
static VeInt32 KeyProtection(lua_State* pkState)
{
	CHECK_STACK(pkState);
	VE_ASSERT(lua_islightuserdata(pkState, lua_upvalueindex(1)));
	Content* pkContent = (Content*)lua_touserdata(pkState, lua_upvalueindex(1));
	return pkContent->NewIndex(pkState);
}
//--------------------------------------------------------------------------
VeImplementRootRTTI(Object);
VeImplementRTTI(Content, Object);
VeImplementRTTI(ModuleContent, Content);
VeImplementRTTI(NameSpaceContent, Content);
VeImplementRTTI(ClassContent, Content);
VeImplementRTTI(FunctionObject, Object);
VeImplementRTTI(ValueObject, Object);
VeImplementRTTI(ConstructorObject, Object);
VeImplementRTTI(MemberObject, Object);
VeImplementRTTI(MemberFunctionObject, MemberObject);
//--------------------------------------------------------------------------
VeInt32 Content::Index(lua_State* pkState)
{
	const VeChar8* pcKey = lua_tostring(pkState, -1);
	VeUInt32* pu32Iter = m_kReadMap.Find(pcKey);
	if(pu32Iter)
	{
		return m_kReadArray[*pu32Iter]->Call(pkState);
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------------------------------
VeInt32 Content::NewIndex(lua_State* pkState)
{
	CHECK_STACK(pkState);
	const VeChar8* pcKey = lua_tostring(pkState, -2);
	VeUInt32* pu32Iter = m_kWriteMap.Find(pcKey);
	if(pu32Iter)
	{
		return m_kWriteArray[*pu32Iter]->Call(pkState);
	}
	else
	{
		pu32Iter = m_kObjMap.Find(pcKey);
		if(pu32Iter)
		{
			VE_LOG_E("lua", "write protection key[%s]", pcKey);
			return 0;
		}
		else
		{
			lua_pushvalue(pkState, -2);
			lua_pushvalue(pkState, -2);
			lua_rawset(pkState, 1);
			return 0;
		}
	}
}
//--------------------------------------------------------------------------
const Content& Content::GetCurrent()
{
	VE_ASSERT(s_spContent);
	return *s_spContent;
}
//--------------------------------------------------------------------------
void FunctionObject::Register(lua_State* pkState)
{
	CHECK_STACK(pkState);
	VeUInt32* pu32Iter = s_spContent->m_kObjMap.Find(m_kName);
	if(pu32Iter)
	{
		VE_ASSERT((*pu32Iter) < s_spContent->m_kObjVector.Size());
		FunctionObject* pkObj = VeSmartPointerCast(FunctionObject, s_spContent->m_kObjVector[*pu32Iter]);
		if(pkObj)
		{
			m_spNext = pkObj->m_spNext;
			pkObj->m_spNext = this;
		}
		else
		{
			VE_LOG_E("lua", "wrong function register");
		}
	}
	else
	{
		s_spContent->m_kObjMap[m_kName] = s_spContent->m_kObjVector.Size();
		s_spContent->m_kObjVector.PushBack(this);
		lua_pushstring(pkState, m_kName);
		lua_pushlightuserdata(pkState, this);
		lua_pushcclosure(pkState, FunctionObject::EntryPoint, 1);
		lua_rawset(pkState, -3);
	}
}
//--------------------------------------------------------------------------
void FunctionObject::RegisterOperator(lua_State* pkState, Operator eOp)
{
	CHECK_STACK(pkState);
	ClassContent* pkClass = VeDynamicCast(ClassContent, s_spContent);
	if(pkClass)
	{
		if(eOp < OP_MAX)
		{
			if(pkClass->m_aspOperators[eOp])
			{
				m_spNext = pkClass->m_aspOperators[eOp]->m_spNext;
				pkClass->m_aspOperators[eOp]->m_spNext = this;
			}
			else
			{
				pkClass->m_aspOperators[eOp] = this;
			}
		}
		else
		{
			VE_LOG_E("lua", "regist wrong operator type");
		}
	}
	else
	{
		VE_LOG_E("lua", "regist operator is not in a class");
	}
}
//--------------------------------------------------------------------------
VeInt32 FunctionObject::EntryPoint(lua_State* pkState)
{
	VE_ASSERT(lua_type(pkState, lua_upvalueindex(1)) == LUA_TLIGHTUSERDATA);
	FunctionObject* pkObj = (FunctionObject*)lua_touserdata(pkState, lua_upvalueindex(1));
	VeInt32 i32Res = pkObj->Call(pkState);
	if(i32Res < 0)
	{
		VE_LOG_I("lua", "no matched call %s", (const VeChar8*)pkObj->m_kFullName);
		ClearPase();
		return 0;
	}
	else if(i32Res == 0 && s_bPauseFlag)
	{
		VeInt32 i32CTX = s_i32CTX;
		lua_CFunction pfuncCall = s_pfuncCall;
		ClearPase();
		return lua_yieldk(pkState, 0, i32CTX, pfuncCall);
	}
	else if(i32Res == 0 && s_u32ManualReturn)
	{
		i32Res = s_u32ManualReturn;
		ClearPase();
		return i32Res;
	}
	else
	{
		ClearPase();
		return i32Res;
	}
}
//--------------------------------------------------------------------------
void ValueObject::Register(lua_State* pkState)
{
	CHECK_STACK(pkState);
	if(m_eType == TYPE_READ)
	{
		VeUInt32* pu32Iter = s_spContent->m_kReadMap.Find(m_kName);
		if(pu32Iter)
		{
			VE_LOG_E("lua", "content %s already has %s", (const VeChar8*)s_spContent->m_kFullName, (const VeChar8*)m_kName);
		}
		else
		{
			s_spContent->m_kReadMap[m_kName] = s_spContent->m_kReadArray.Size();
			s_spContent->m_kReadArray.PushBack(this);
		}
	}
	else if(m_eType == TYPE_WRITE)
	{
		VeUInt32* pu32Iter = s_spContent->m_kWriteMap.Find(m_kName);
		if(pu32Iter)
		{
			VE_LOG_E("lua", "content %s already has %s", (const VeChar8*)s_spContent->m_kFullName, (const VeChar8*)m_kName);
		}
		else
		{
			s_spContent->m_kWriteMap[m_kName] = s_spContent->m_kWriteArray.Size();
			s_spContent->m_kWriteArray.PushBack(this);
		}
	}
}
//--------------------------------------------------------------------------
void* ClassContent::AdjustPointer(void* pvPointer, ClassContent* pkClass)
{
	if(this == pkClass)
	{
		return pvPointer;
	}
	else
	{
		for(VeUInt32 i(0); i < m_kBaseList.Size(); ++i)
		{
			VePair<const ClassContentPointer*,VeSizeT>& kBase = m_kBaseList[i];
			void* pvBase = (void*)((VeSizeT)pvPointer + kBase.m_tSecond);
			pvBase = (*kBase.m_tFirst)->AdjustPointer(pvBase, pkClass);
			if(pvBase) return pvBase;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
void* AdjustPointer(void* pvPointer, ClassContent* pvSrc, ClassContent* pvDst)
{
	return pvSrc->AdjustPointer(pvPointer, pvDst);
}
//--------------------------------------------------------------------------
VeInt32 ClassContent::NewIndex(lua_State* pkState)
{
	CHECK_STACK(pkState);
	const VeChar8* pcKey = lua_tostring(pkState, -2);
	VeUInt32* pu32Iter = m_kWriteMap.Find(pcKey);
	if(pu32Iter)
	{
		return m_kWriteArray[*pu32Iter]->Call(pkState);
	}
	else
	{
		VeUInt32* pu32Iter = m_kObjMap.Find(pcKey);
		if(pu32Iter)
		{
			VE_LOG_E("lua", "write protection key[%s]", pcKey);
		}
		else
		{
			VE_LOG_E("lua", "new key[%s] in a class", pcKey);
		}
		return 0;
	}
}
//--------------------------------------------------------------------------
VeInt32 ClassContent::MemberIndex(lua_State* pkState)
{
	const VeChar8* pcKey = lua_tostring(pkState, 2);
	VeUInt32* pu32Iter = m_kReadMemberMap.Find(pcKey);
	if(pu32Iter)
	{
		return m_kReadMemberArray[*pu32Iter]->Call(pkState);
	}
	else
	{
		VeInt32 i32Res(0);
		for(VeUInt32 i(0); i < m_kBaseList.Size(); ++i)
		{
			i32Res = (*m_kBaseList[i].m_tFirst)->MemberIndex(pkState);
			if(i32Res)
			{
				break;
			}
		}
		return i32Res;
	}
}
//--------------------------------------------------------------------------
VeInt32 ClassContent::MemberNewIndex(lua_State* pkState)
{
	const VeChar8* pcKey = lua_tostring(pkState, 2);
	VeUInt32* pu32Iter = m_kWriteMemberMap.Find(pcKey);
	if(pu32Iter)
	{
		return m_kWriteMemberArray[*pu32Iter]->Call(pkState);
	}
	else
	{
		VeInt32 i32Res(0);
		for(VeUInt32 i(0); i < m_kBaseList.Size(); ++i)
		{
			i32Res = (*m_kBaseList[i].m_tFirst)->MemberNewIndex(pkState);
			if(i32Res)
			{
				break;
			}
		}
		return i32Res;
	}
}
//--------------------------------------------------------------------------
void ConstructorObject::Register(lua_State* pkState)
{
	CHECK_STACK(pkState);
	ClassContent* pkClass = VeDynamicCast(ClassContent, s_spContent);
	if(pkClass)
	{
		ConstructorObject* pkObj = pkClass->m_spConstructor;
		if(pkObj)
		{
			m_spNext = pkObj->m_spNext;
			pkObj->m_spNext = this;
		}
		else
		{
			pkClass->m_spConstructor = this;
			lua_pushstring(pkState, "__call");
			lua_pushlightuserdata(pkState, pkClass);
			lua_pushlightuserdata(pkState, this);
			lua_pushcclosure(pkState, ConstructorObject::EntryPoint, 2);
			lua_rawset(pkState, -4);
		}
	}
	else
	{
		VE_LOG_E("lua", "regist constructor is not in a class");
	}
}
//--------------------------------------------------------------------------
VeInt32 ConstructorObject::EntryPoint(lua_State* pkState)
{
	VE_ASSERT(lua_type(pkState, lua_upvalueindex(2)) == LUA_TLIGHTUSERDATA);
	ConstructorObject* pkObj = (ConstructorObject*)lua_touserdata(pkState, lua_upvalueindex(2));
	VeInt32 i32Res = pkObj->Call(pkState);
	if(i32Res < 0)
	{
		VE_LOG_I("lua", "no matched call %s", (const VeChar8*)pkObj->m_kFullName);
		ClearPase();
		return 0;
	}
	else if(i32Res == 0 && s_bPauseFlag)
	{
		VeInt32 i32CTX = s_i32CTX;
		lua_CFunction pfuncCall = s_pfuncCall;
		ClearPase();
		return lua_yieldk(pkState, 0, i32CTX, pfuncCall);
	}
	else if(i32Res == 0 && s_u32ManualReturn)
	{
		i32Res = s_u32ManualReturn;
		ClearPase();
		return i32Res;
	}
	else
	{
		ClearPase();
		return i32Res;
	}
}
//--------------------------------------------------------------------------
void MemberObject::Register(lua_State* pkState)
{
	CHECK_STACK(pkState);
	ClassContent* pkClass = VeDynamicCast(ClassContent, s_spContent);
	if(pkClass)
	{
		if(m_eType == TYPE_READ)
		{
			VeUInt32* pu32Iter = pkClass->m_kReadMemberMap.Find(m_kName);
			if(pu32Iter)
			{
				VE_LOG_E("lua", "class %s already has member %s", (const VeChar8*)pkClass->m_kFullName, (const VeChar8*)m_kName);
			}
			else
			{
				pkClass->m_kReadMemberMap[m_kName] = pkClass->m_kReadMemberArray.Size();
				pkClass->m_kReadMemberArray.PushBack(this);
			}
		}
		else if(m_eType == TYPE_WRITE)
		{
			VeUInt32* pu32Iter = pkClass->m_kWriteMemberMap.Find(m_kName);
			if(pu32Iter)
			{
				VE_LOG_E("lua", "class %s already has member %s", (const VeChar8*)pkClass->m_kFullName, (const VeChar8*)m_kName);
			}
			else
			{
				pkClass->m_kWriteMemberMap[m_kName] = pkClass->m_kWriteMemberArray.Size();
				pkClass->m_kWriteMemberArray.PushBack(this);
			}
		}
	}
	else
	{
		VE_LOG_E("lua", "regist memberobject is not in a class");
	}
}
//--------------------------------------------------------------------------
void MemberFunctionObject::Register(lua_State* pkState)
{
	CHECK_STACK(pkState);
	ClassContent* pkClass = VeDynamicCast(ClassContent, s_spContent);
	if(pkClass)
	{
		VE_ASSERT(m_eType == TYPE_READ);
		VeUInt32* pu32Iter = pkClass->m_kReadMemberMap.Find(m_kName);
		if(pu32Iter)
		{
			MemberFunctionObject* pkStart = VeDynamicCast(MemberFunctionObject, pkClass->m_kReadMemberArray[*pu32Iter]);
			if(pkStart)
			{
				m_spNext = pkStart->m_spNext;
				pkStart->m_spNext = this;
			}
			else
			{
				VE_LOG_E("lua", "class %s already has member %s", (const VeChar8*)pkClass->m_kFullName, (const VeChar8*)m_kName);
			}
		}
		else
		{
			pkClass->m_kReadMemberMap[m_kName] = pkClass->m_kReadMemberArray.Size();
			pkClass->m_kReadMemberArray.PushBack(this);
		}
	}
	else
	{
		VE_LOG_E("lua", "regist memberobject is not in a class");
	}
}
//--------------------------------------------------------------------------
VeInt32 MemberFunctionObject::Call(lua_State* pkState)
{
	lua_pushlightuserdata(pkState, this);
	lua_pushvalue(pkState, -3);
	lua_pushcclosure(pkState, MemberFunctionObject::EntryPoint, 2);
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 MemberFunctionObject::EntryPoint(lua_State* pkState)
{
	VE_ASSERT(lua_type(pkState, lua_upvalueindex(1)) == LUA_TLIGHTUSERDATA
		&& lua_type(pkState, lua_upvalueindex(2)) == LUA_TUSERDATA);
	MemberFunctionObject* pkFuncObject = (MemberFunctionObject*)lua_touserdata(pkState, lua_upvalueindex(1));
	void* pvSelf = lua_touserdata(pkState, lua_upvalueindex(2));
	VeInt32 i32Bias = (pvSelf == lua_touserdata(pkState, 1)) ? 2 : 1;
	if(UserDataFlag(pvSelf) == OBJ_LUA_MEM)
	{
		pvSelf = UserDataObject(pvSelf);
	}
	else
	{
		pvSelf = *(void**)UserDataObject(pvSelf);
	}
	VeInt32 i32Res = pkFuncObject->CallFunction(pkState, pvSelf, i32Bias);
	if(i32Res == 0 && s_bPauseFlag)
	{
		VeInt32 i32CTX = s_i32CTX;
		lua_CFunction pfuncCall = s_pfuncCall;
		ClearPase();
		return lua_yieldk(pkState, 0, i32CTX, pfuncCall);
	}
	else if(i32Res == 0 && s_u32ManualReturn)
	{
		i32Res = s_u32ManualReturn;
		ClearPase();
		return i32Res;
	}
	else
	{
		ClearPase();
		return i32Res;
	}
}
//--------------------------------------------------------------------------
Regist::Regist()
{

}
//--------------------------------------------------------------------------
Regist::~Regist()
{

}
//--------------------------------------------------------------------------
Scope::Scope()
{

}
//--------------------------------------------------------------------------
Scope::Scope(RegistPtr& spRegist)
{
	m_spChain = spRegist;
	spRegist = NULL;
}
//--------------------------------------------------------------------------
Scope::Scope(const Scope& kOther)
{
	m_spChain = kOther.m_spChain;
	const_cast<Scope&>(kOther).m_spChain = NULL;
}
//--------------------------------------------------------------------------
Scope::~Scope()
{

}
//--------------------------------------------------------------------------
Scope& Scope::operator = (const Scope& kOther)
{
	m_spChain = kOther.m_spChain;
	const_cast<Scope&>(kOther).m_spChain = NULL;
	return *this;
}
//--------------------------------------------------------------------------
Scope& Scope::operator , (Scope kScope)
{
	if(m_spChain)
	{
		for(Regist* pkIter = m_spChain; ; pkIter = pkIter->m_spNext)
		{
			if(!pkIter->m_spNext)
			{
				pkIter->m_spNext = kScope.m_spChain;
				kScope.m_spChain = NULL;
				break;
			}
		}
	}
	else
	{
		m_spChain = kScope.m_spChain;
		kScope.m_spChain = NULL;
	}
	return *this;
}
//--------------------------------------------------------------------------
void Scope::Register(lua_State* pkState) const
{
	CHECK_STACK(pkState);
	for(Regist* pkIter = m_spChain; pkIter; pkIter = pkIter->m_spNext)
	{
		pkIter->Register(pkState);
	}
}
//--------------------------------------------------------------------------
NameSpace::NameSpace(const VeChar8* pcName)
{
	m_spChain = VE_NEW Regist(pcName);
}
//--------------------------------------------------------------------------
NameSpace& NameSpace::operator [] (Scope kScope)
{
	VeSmartPointerCast(Regist, m_spChain)->m_kScope.operator , (kScope);
	return *this;
}
//--------------------------------------------------------------------------
NameSpace::Regist::Regist(const VeChar8* pcName)
	: m_pcName(pcName)
{
	VE_ASSERT(m_pcName);
}
//--------------------------------------------------------------------------
void NameSpace::Regist::Register(lua_State* pkState)
{
	CHECK_STACK(pkState);
	VeInt32 i32Top = lua_gettop(pkState);

	ContentPtr spNamespace;
	VeUInt32* pu32Iter = s_spContent->m_kObjMap.Find(m_pcName);
	if(!pu32Iter)
	{
		lua_pushstring(pkState, m_pcName);
		lua_rawget(pkState, -2);
		if(lua_isnil(pkState, -1))
		{
			spNamespace = VE_NEW NameSpaceContent(m_pcName);
			s_spContent->m_kObjMap[m_pcName] = s_spContent->m_kObjVector.Size();
			s_spContent->m_kObjVector.PushBack(spNamespace);
			lua_pop(pkState, 1);
			lua_newtable(pkState);
			lua_pushstring(pkState, m_pcName);
			lua_pushvalue(pkState, -2);
			lua_rawset(pkState, -4);
			lua_newtable(pkState);
			lua_newtable(pkState);
			lua_pushstring(pkState, "__index");
			lua_pushvalue(pkState, -2);
			lua_rawset(pkState, -4);
			lua_newtable(pkState);
			lua_pushstring(pkState, "__index");
			lua_pushlightuserdata(pkState, spNamespace);
			lua_pushcclosure(pkState, CallValue, 1);
			lua_rawset(pkState, -3);
			lua_setmetatable(pkState, -2);
			lua_pushstring(pkState, "__newindex");
			lua_pushlightuserdata(pkState, spNamespace);
			lua_pushcclosure(pkState, KeyProtection, 1);
			lua_rawset(pkState, -4);
			lua_pushstring(pkState, "__luabind_content");
			lua_pushlightuserdata(pkState, spNamespace);
			lua_rawset(pkState, -4);
			lua_pushvalue(pkState, -2);
			lua_setmetatable(pkState, -4);
		}
	}
	else
	{
		lua_pushstring(pkState, m_pcName);
		lua_rawget(pkState, -2);
		if(lua_istable(pkState, -1))
		{
			if(lua_getmetatable(pkState, -1))
			{
				lua_pushstring(pkState, "__luabind_content");
				lua_rawget(pkState, -2);
				if(lua_islightuserdata(pkState, -1) && ((Content*)lua_touserdata(pkState, -1) == s_spContent->m_kObjVector[*pu32Iter]))
				{
					spNamespace = s_spContent->m_kObjVector[*pu32Iter];
					lua_pop(pkState, 1);
					lua_pushstring(pkState, "__index");
					lua_rawget(pkState, -2);
				}
			}
		}
	}
	if(spNamespace)
	{
		s_spContent = spNamespace;
		m_kScope.Register(pkState);
	}
	else
	{
		VE_LOG_E("lua", "wrong namespace for regist");
	}
	lua_settop(pkState, i32Top);
}
//--------------------------------------------------------------------------
ClassRegist::ClassRegist(const VeChar8* pcName, ClassContentPointer& pkContent)
	: m_pcName(pcName), m_pkClassContent(pkContent)
{
	VE_ASSERT(m_pcName);
	if(!m_pkClassContent)
	{
		m_pkClassContent = VE_NEW ClassContent(m_pcName);
		m_pkClassContent->IncRefCount();
	}
}
//--------------------------------------------------------------------------
void ClassRegist::Register(lua_State* pkState)
{
	CHECK_STACK(pkState);
	VeInt32 i32Top = lua_gettop(pkState);
	ContentPtr spClass;
	VeUInt32* pu32Iter = s_spContent->m_kObjMap.Find(m_pcName);
	if(!pu32Iter)
	{
		lua_pushstring(pkState, m_pcName);
		lua_rawget(pkState, -2);
		if(lua_isnil(pkState, -1))
		{
			m_pkClassContent->m_kFullName = s_spContent->m_kFullName + "." + m_pcName;
			spClass = m_pkClassContent;
			s_spContent->m_kObjMap[m_pcName] = s_spContent->m_kObjVector.Size();
			s_spContent->m_kObjVector.PushBack(spClass);
			lua_pop(pkState, 1);
			lua_newtable(pkState);
			lua_pushstring(pkState, m_pcName);
			lua_pushvalue(pkState, -2);
			lua_rawset(pkState, -4);
			lua_newtable(pkState);
			lua_newtable(pkState);
			lua_pushstring(pkState, "__index");
			lua_pushvalue(pkState, -2);
			lua_rawset(pkState, -4);
			lua_newtable(pkState);
			lua_pushstring(pkState, "__index");
			lua_pushlightuserdata(pkState, spClass);
			lua_pushcclosure(pkState, CallValue, 1);
			lua_rawset(pkState, -3);
			lua_setmetatable(pkState, -2);
			lua_pushstring(pkState, "__newindex");
			lua_pushlightuserdata(pkState, spClass);
			lua_pushcclosure(pkState, KeyProtection, 1);
			lua_rawset(pkState, -4);
			lua_pushstring(pkState, "__luabind_content");
			lua_pushlightuserdata(pkState, spClass);
			lua_rawset(pkState, -4);
			lua_pushvalue(pkState, -2);
			lua_setmetatable(pkState, -4);
		}
	}
	else
	{
		lua_pushstring(pkState, m_pcName);
		lua_rawget(pkState, -2);
		if(lua_istable(pkState, -1))
		{
			if(lua_getmetatable(pkState, -1))
			{
				lua_pushstring(pkState, "__luabind_content");
				lua_rawget(pkState, -2);
				if(lua_islightuserdata(pkState, -1) && ((Content*)lua_touserdata(pkState, -1) == s_spContent->m_kObjVector[*pu32Iter]))
				{
					spClass = s_spContent->m_kObjVector[*pu32Iter];
					VE_ASSERT(m_pkClassContent == spClass);
					lua_pop(pkState, 1);
					lua_pushstring(pkState, "__index");
					lua_rawget(pkState, -2);
				}
			}
		}
	}
	if(spClass)
	{
		s_spContent = spClass;
		m_kScope.Register(pkState);
	}
	else
	{
		VE_LOG_E("lua", "wrong class for regist");
	}
	lua_settop(pkState, i32Top);
}
//--------------------------------------------------------------------------
Module::Module(const VeChar8* pcName, lua_State* pkState)
	: m_pkState(pkState), m_pcName(pcName)
{

}
//--------------------------------------------------------------------------
void Module::operator [] (Scope kScope)
{
	CHECK_STACK(m_pkState);
	s_spContent = NULL;
	VeInt32 i32Top = lua_gettop(m_pkState);
	{
		lua_pushglobaltable(m_pkState);
		VeUInt32* pu32Iter = s_pkContentMap->Find(m_pkState);
		if(!pu32Iter)
		{
			if(!lua_getmetatable(m_pkState, -1))
			{
				s_spContent = VE_NEW ModuleContent;
				(*s_pkContentMap)[m_pkState] = s_pkContentVec->Size();
				s_pkContentVec->PushBack(s_spContent);
				lua_newtable(m_pkState);
				lua_newtable(m_pkState);
				lua_pushstring(m_pkState, "__index");
				lua_pushvalue(m_pkState, -2);
				lua_rawset(m_pkState, -4);
				lua_newtable(m_pkState);
				lua_pushstring(m_pkState, "__index");
				lua_pushlightuserdata(m_pkState, s_spContent);
				lua_pushcclosure(m_pkState, CallValue, 1);
				lua_rawset(m_pkState, -3);
				lua_setmetatable(m_pkState, -2);
				lua_pushstring(m_pkState, "__newindex");
				lua_pushlightuserdata(m_pkState, s_spContent);
				lua_pushcclosure(m_pkState, KeyProtection, 1);
				lua_rawset(m_pkState, -4);
				lua_pushstring(m_pkState, "__luabind_content");
				lua_pushlightuserdata(m_pkState, s_spContent);
				lua_rawset(m_pkState, -4);
				lua_pushvalue(m_pkState, -2);
				lua_setmetatable(m_pkState, -4);
			}
		}
		else
		{
			if(lua_getmetatable(m_pkState, -1))
			{
				lua_pushstring(m_pkState, "__luabind_content");
				lua_rawget(m_pkState, -2);
				if(lua_islightuserdata(m_pkState, -1) && ((Content*)lua_touserdata(m_pkState, -1) == (*s_pkContentVec)[*pu32Iter]))
				{
					lua_pop(m_pkState, 1);
					lua_pushstring(m_pkState, "__index");
					lua_rawget(m_pkState, -2);
					s_spContent = (*s_pkContentVec)[*pu32Iter];
				}
			}
		}
	}
	if(!s_spContent)
	{
		VE_LOG_E("lua", "wrong module for regist");
		lua_settop(m_pkState, i32Top);
		return;
	}
	if(m_pcName)
	{
		ContentPtr spNamespace;
		VeUInt32* pu32Iter = s_spContent->m_kObjMap.Find(m_pcName);
		if(!pu32Iter)
		{
			lua_pushstring(m_pkState, m_pcName);
			lua_rawget(m_pkState, -2);
			if(lua_isnil(m_pkState, -1))
			{
				spNamespace = VE_NEW NameSpaceContent(m_pcName);
				s_spContent->m_kObjMap[m_pcName] = s_spContent->m_kObjVector.Size();
				s_spContent->m_kObjVector.PushBack(spNamespace);
				lua_pop(m_pkState, 1);
				lua_newtable(m_pkState);
				lua_pushstring(m_pkState, m_pcName);
				lua_pushvalue(m_pkState, -2);
				lua_rawset(m_pkState, -4);
				lua_newtable(m_pkState);
				lua_newtable(m_pkState);
				lua_pushstring(m_pkState, "__index");
				lua_pushvalue(m_pkState, -2);
				lua_rawset(m_pkState, -4);
				lua_newtable(m_pkState);
				lua_pushstring(m_pkState, "__index");
				lua_pushlightuserdata(m_pkState, spNamespace);
				lua_pushcclosure(m_pkState, CallValue, 1);
				lua_rawset(m_pkState, -3);
				lua_setmetatable(m_pkState, -2);
				lua_pushstring(m_pkState, "__newindex");
				lua_pushlightuserdata(m_pkState, spNamespace);
				lua_pushcclosure(m_pkState, KeyProtection, 1);
				lua_rawset(m_pkState, -4);
				lua_pushstring(m_pkState, "__luabind_content");
				lua_pushlightuserdata(m_pkState, spNamespace);
				lua_rawset(m_pkState, -4);
				lua_pushvalue(m_pkState, -2);
				lua_setmetatable(m_pkState, -4);
			}
		}
		else
		{
			lua_pushstring(m_pkState, m_pcName);
			lua_rawget(m_pkState, -2);
			if(lua_istable(m_pkState, -1))
			{
				if(lua_getmetatable(m_pkState, -1))
				{
					lua_pushstring(m_pkState, "__luabind_content");
					lua_rawget(m_pkState, -2);
					if(lua_islightuserdata(m_pkState, -1) && ((Content*)lua_touserdata(m_pkState, -1) == s_spContent->m_kObjVector[*pu32Iter]))
					{
						spNamespace = s_spContent->m_kObjVector[*pu32Iter];
						lua_pop(m_pkState, 1);
						lua_pushstring(m_pkState, "__index");
						lua_rawget(m_pkState, -2);
					}
				}
			}
		}
		if(!spNamespace)
		{
			VE_LOG_E("lua", "wrong namespace for regist");
			lua_settop(m_pkState, i32Top);
			return;
		}
		s_spContent = spNamespace;
	}
	kScope.Register(m_pkState);
	lua_settop(m_pkState, i32Top);
}
//--------------------------------------------------------------------------
}
