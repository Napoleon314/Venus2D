////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLua.cpp
//  Version:     v1.00
//  Created:     26/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeLua.inl"
#endif

extern "C"
{
#	include <lua.h>
#	include <lauxlib.h>
#	include <lualib.h>
}

//--------------------------------------------------------------------------
#define LUA_CALL(func)												\
	if(func)														\
	{																\
		VE_LOG_E("lua", "error: %s", lua_tostring(m_pkLua, -1));	\
		lua_pop(m_pkLua, 1);										\
	}
//--------------------------------------------------------------------------
VeLua::VeLua(bool bDebug) : m_bDebug(bDebug ? VE_TRUE : VE_FALSE)
	, m_pkLua(NULL)
{
	m_pkLua = luaL_newstate();
	VE_ASSERT(m_pkLua);
	luaL_openlibs(m_pkLua);
	
	const VeChar8* pcInit =
		"VeNet = {}\n" \
		"function VeSyncTask(task,signal)\n" \
		"	task()\n" \
		"	signal.EndTask()\n" \
		"end\n" \
		"function VeFullCall(func,event,...)\n" \
		"	event(func(...))\n" \
		"end\n";
	_DoBuffer(pcInit, (VeInt32)VeStrlen(pcInit), "VeLuaInit");

	g_pLua->SetValue("pi", VE_MATH_PI_F);
	m_i32FullCall = Ref("VeFullCall");

	lua_settop(m_pkLua, 0);
	VeLuaBind::Init();
	if(!bDebug)
	{
		lua_pushcfunction(m_pkLua, &VeLua::Print);
		lua_setglobal(m_pkLua, "print");
	}
}
//--------------------------------------------------------------------------
VeLua::~VeLua()
{
	VE_ASSERT(m_pkLua);
	lua_close(m_pkLua);
	m_pkLua = NULL;
	VeLuaBind::Term();
	m_kCallbackList.BeginIterator();
	while(!m_kCallbackList.IsEnd())
	{
		VeRefObject* pkObj = m_kCallbackList.GetIterNode()->m_tContent;
		m_kCallbackList.Next();
		pkObj->DecRefCount();
	}
}
//--------------------------------------------------------------------------
void VeLua::DoFileSync(const VeChar8* pcPath)
{
	VE_ASSERT(pcPath);
	if(m_bDebug && VeStrncmp(pcPath, "file#", 5) == 0)
	{
		_DoFile(VeStrchr(pcPath, '#') + 1);
	}
	else
	{
		const VeChar8* pcFile = VeStrrchr(pcPath, '/') + 1;
		VE_ASSERT(pcFile && pcFile != pcPath);
		VeChar8 acPath[256];
		VeStrncpy(acPath, 256, pcPath, pcFile - pcPath - 1);
		VeDirectory* pkDir = g_pResourceManager->CreateDir(acPath);
		VE_ASSERT(pkDir);
		VeBinaryIStreamPtr spStream = pkDir->OpenSync(pcFile);
		VE_ASSERT(spStream);
		VeInt32 i32Length = spStream->RemainingLength();
		VeChar8* pcData = VeAlloc(VeChar8, i32Length);
		spStream->Read(pcData, i32Length);
		_DoBuffer(pcData, i32Length, pcFile);
		VeFree(pcData);
		g_pResourceManager->DestoryDir(pkDir);
	}
}
//--------------------------------------------------------------------------
void VeLua::Require(const VeChar8* pcPath, LoadTaskDelegate* pkDelegate)
{
	VE_ASSERT(pcPath);
	LoadTask* pkTask = VE_NEW LoadTask(pcPath, pkDelegate);
	pkTask->IncRefCount();
	m_kTaskList.AttachBack(pkTask->m_kNode);
}
//--------------------------------------------------------------------------
void VeLua::CallFunction(const VeChar8* pcDesc, ...)
{
	VE_ASSERT(pcDesc);
	va_list kArgs;
	va_start(kArgs, pcDesc);
	VeInt32 i32Top = lua_gettop(m_pkLua);
	VeChar8 acBuffer[256];
	VeStrcpy(acBuffer, pcDesc);
	VeChar8* pcContent;
	const VeChar8* pcTemp = VeStrtok(acBuffer, "(", &pcContent);
	if(VeLuaBind::RetParam(m_pkLua, pcTemp) == 1)
	{
		VE_ASSERT((i32Top + 1) == lua_gettop(m_pkLua));
		VeInt32 i32ArgCount(0), i32ResCount(0);
		pcTemp = VeStrtok(NULL, ")", &pcContent);
		while(pcTemp && *pcTemp)
		{
			switch(*(pcTemp++))
			{
			case 'i':
				lua_pushinteger(m_pkLua, va_arg(kArgs, VeInt32));
				break;
			case 'u':
				lua_pushunsigned(m_pkLua, va_arg(kArgs, VeUInt32));
				break;
			case 'd':
				lua_pushnumber(m_pkLua, va_arg(kArgs, VeFloat64));
				break;
			case 's':
				lua_pushstring(m_pkLua, va_arg(kArgs, const VeChar8*));
				break;
			case 'b':
				lua_pushboolean(m_pkLua, va_arg(kArgs, VE_BOOL));
				break;
			default:
				VE_ASSERT(!"Unknown lua type");
				break;
			}
			++i32ArgCount;
		}
		i32ResCount = pcContent ? VeInt32(VeStrlen(pcContent)) : 0;
		LUA_CALL(lua_pcall(m_pkLua, i32ArgCount, i32ResCount, 0));
		VeInt32 i32Iter(-i32ResCount);
		while(pcContent && *pcContent)
		{
			switch(*(pcContent++))
			{
			case 'i':
				*va_arg(kArgs, VeInt32*) = (VeInt32)lua_tointeger(m_pkLua, i32Iter);
				break;
			case 'u':
				*va_arg(kArgs, VeUInt32*) = (VeUInt32)lua_tounsigned(m_pkLua, i32Iter);
				break;
			case 'd':
				*va_arg(kArgs, VeFloat64*) = lua_tonumber(m_pkLua, i32Iter);
				break;
			case 's':
				*va_arg(kArgs, VeString*) = lua_tostring(m_pkLua, i32Iter);
				break;
			case 'b':
				*va_arg(kArgs, VE_BOOL*) = lua_toboolean(m_pkLua, i32Iter);
				break;
			default:
				VE_ASSERT(!"Unknown type");
				break;
			}
			++i32Iter;
		}
	}
	else
	{
		VE_LOG_E("lua", "call wrong function");
	}
	lua_settop(m_pkLua, i32Top);
	va_end(kArgs);
}
//--------------------------------------------------------------------------
void VeLua::SetValue(const VeChar8* pcName, VeFloat32 f32Value)
{
	VE_ASSERT(pcName);
	lua_pushnumber(m_pkLua, f32Value);
	lua_setglobal(m_pkLua, pcName);
}
//--------------------------------------------------------------------------
VeFloat32 VeLua::GetValue(const VeChar8* pcName)
{
	VE_ASSERT(pcName);
	VeInt32 i32Top = lua_gettop(m_pkLua);
	VeFloat32 f32Res(0);
	lua_getglobal(m_pkLua, pcName);
	if(lua_isnumber(m_pkLua, -1))
	{
		f32Res = (VeFloat32)lua_tonumber(m_pkLua, -1);
	}
	lua_settop(m_pkLua, i32Top);
	return f32Res;
}
//--------------------------------------------------------------------------
void VeLua::SetString(const VeChar8* pcName, const VeChar8* pcStr)
{
	VE_ASSERT(pcName);
	lua_pushstring(m_pkLua, pcStr);
	lua_setglobal(m_pkLua, pcName);
}
//--------------------------------------------------------------------------
const VeChar8* VeLua::GetString(const VeChar8* pcName)
{
	VE_ASSERT(pcName);
	VeInt32 i32Top = lua_gettop(m_pkLua);
	const VeChar8* pcRes = "";
	lua_getglobal(m_pkLua, pcName);
	if(lua_isstring(m_pkLua, -1))
	{
		pcRes = lua_tostring(m_pkLua, -1);
	}
	lua_settop(m_pkLua, i32Top);
	return pcRes;
}
//--------------------------------------------------------------------------
bool VeLua::GetExpression(const VeChar8* pcExpression, VeFloat64& f64Out)
{
	if(pcExpression && *pcExpression)
	{
		VeInt32 i32Top = lua_gettop(m_pkLua);
		bool bRes(true);
		VeChar8 acBuffer[2048];
		VeInt32 iLen = VeSprintf(acBuffer, "expression_temp=%s", pcExpression);
		if(luaL_loadbuffer(m_pkLua, acBuffer, iLen, "get_expression") || lua_pcall(m_pkLua, 0, LUA_MULTRET, 0))
		{
			f64Out = 0.0;
			VE_LOG_E("Venus3D", "Lua: %s", lua_tostring(m_pkLua, -1));
			bRes = false;
		}
		else
		{
			lua_getglobal(m_pkLua, "expression_temp");
			f64Out = lua_tonumber(m_pkLua, -1);
		}
		lua_settop(m_pkLua, i32Top);
		return bRes;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
VeFloat32 VeLua::GetExpression(const VeChar8* pcExp, VeFloat32 f32Defult)
{
	VeFloat64 f64Num;
	if(GetExpression(pcExp, f64Num))
	{
		return (VeFloat32)f64Num;
	}
	else
	{
		return f32Defult;
	}
}
//--------------------------------------------------------------------------
void VeLua::AddCallbackObj(VeRefNode<VeRefObject*>& kNode)
{
	kNode.m_tContent->IncRefCount();
	m_kCallbackList.AttachBack(kNode);
}
//--------------------------------------------------------------------------
void VeLua::DelCallbackObj(VeRefNode<VeRefObject*>& kNode)
{
	if(kNode.IsAttach(m_kCallbackList))
	{
		kNode.Detach();
		kNode.m_tContent->DecRefCount();
	}
}
//--------------------------------------------------------------------------
VeInt32 VeLua::Ref(const VeChar8* pcFuncName)
{
	if(VeLuaBind::RetParam(m_pkLua, VeLuaBind::FunctionName(pcFuncName)) == 1)
	{
		return luaL_ref(m_pkLua, LUA_REGISTRYINDEX);
	}
	return 0;
}
//--------------------------------------------------------------------------
void VeLua::UnRef(VeInt32 i32Ref)
{
	luaL_unref(m_pkLua, LUA_REGISTRYINDEX, i32Ref);
}
//--------------------------------------------------------------------------
lua_State* VeLua::MakeFullCallThread()
{
	return VeLuaBind::MakeFuncThread(m_pkLua, m_i32FullCall);
}
//--------------------------------------------------------------------------
VeInt32 VeLua::GetFullCall()
{
	return m_i32FullCall;
}
//--------------------------------------------------------------------------
void VeLua::_DoFile(const VeChar8* pcName)
{
	LUA_CALL(luaL_dofile(m_pkLua, pcName));
}
//--------------------------------------------------------------------------
void VeLua::_DoBuffer(const VeChar8* pcData, VeInt32 i32Length, const VeChar8* pcName)
{
	LUA_CALL(luaL_loadbuffer(m_pkLua, pcData, i32Length, pcName)
		|| lua_pcall(m_pkLua, 0, LUA_MULTRET, 0));
}
//--------------------------------------------------------------------------
void VeLua::_DoBuffer(const VeBlobPtr& spBlob, const VeChar8* pcName)
{
	_DoBuffer((const VeChar8*)spBlob->GetBuffer(), spBlob->GetSize(), pcName);
}
//--------------------------------------------------------------------------
VeInt32 VeLua::GetTop(lua_State* pkState)
{
	return lua_gettop(pkState);
}
//--------------------------------------------------------------------------
void VeLua::SetTop(lua_State* pkState, VeInt32 i32Value)
{
	return lua_settop(pkState, i32Value);
}
//--------------------------------------------------------------------------
VeInt32 VeLua::Print(lua_State* pkLua)
{
	VeInt32 n = lua_gettop(pkLua);  /* number of arguments */
	VeInt32 i;
	lua_getglobal(pkLua, "tostring");
	VeString kLog;
	for(i=1; i<=n; ++i)
	{
		const char* pcStr;
		size_t stLen;
		lua_pushvalue(pkLua, -1);  /* function to be called */
		lua_pushvalue(pkLua, i);   /* value to print */
		lua_call(pkLua, 1, 1);
		pcStr = lua_tolstring(pkLua, -1, &stLen);  /* get result */
		if(!pcStr) return luaL_error(pkLua, LUA_QL("tostring") " must return a string to " LUA_QL("print"));
		if(i > 1) kLog += "\t";
		kLog += pcStr;
		lua_pop(pkLua, 1);
	}
	VE_LOG_I("lua", kLog);
	return 0;
}
//--------------------------------------------------------------------------
VeLua::LoadTask::LoadTask(const VeChar8* pcPath, LoadTaskDelegate* pkDele)
{
	m_kNode.m_tContent = this;
	m_kPath = pcPath;
	VeChar8 acBuffer[256];
	VeStrcpy(acBuffer, pcPath);
	VeChar8* pcContext;
	VeChar8* pcTemp = VeStrtok(acBuffer, ";", &pcContext);
	while(pcTemp)
	{
		m_kDescList.PushBack(pcTemp);
		pcTemp = VeStrtok(NULL, ";", &pcContext);
	}
	if(pkDele) m_kEvent.AddDelegate(*pkDele);
	g_pResourceManager->AddBGTask(VeResourceManager::BG_QUEUE_PROCESS, this);
}
//--------------------------------------------------------------------------
void VeLua::LoadTask::DoBackgroundTask(VeBackgroundTaskQueue& kMgr)
{
	VeChar8 acPath[256];
	VeChar8 acFullPath[256];
	VeVector<VeFixedString> kFileList;
	for(VeUInt32 i(0); i < m_kDescList.Size(); ++i)
	{
		const VeChar8* pcDesc = m_kDescList[i];
		const VeChar8* pcFile = VeStrrchr(pcDesc, '/') + 1;
		VE_ASSERT(pcFile);
		VeStrncpy(acPath, 256, pcDesc, pcFile - pcDesc - 1);
		VeDirectory* pkDir = g_pResourceManager->CreateDir(acPath);
		VE_ASSERT(pkDir);
		pkDir->FindFileList(pcFile, kFileList);
		for(VeVector<VeFixedString>::iterator it = kFileList.Begin();
			it != kFileList.End(); ++it)
		{
			bool bNeedLoad(false);
			{
				VE_AUTO_LOCK_MUTEX_NAME(g_pLua->m_kMutex, kMutex);
				VeFixedString* pkIter = g_pLua->m_kPathMap.Find(*it);
				if(!pkIter)
				{
					VeSprintf(acFullPath, "%s/%s", acPath, (const VeChar8*)(*it));
					g_pLua->m_kPathMap[*it] = acFullPath;
					bNeedLoad = true;
				}
			}
			if(bNeedLoad)
			{
				if(g_pLua->m_bDebug && pkDir->GetType() == VeDirectory::TYPE_FILE)
				{
					m_kData.PushBack(VePair<VeFixedString,VeBlobPtr>(*it, NULL));
				}
				else
				{
					VeBinaryIStreamPtr spStream = pkDir->OpenSync(*it);
					VE_ASSERT(spStream);
					VeInt32 i32Length = spStream->RemainingLength();
					VeBlobPtr spBlob = VE_NEW VeBlob(i32Length);
					spStream->Read(*spBlob, i32Length);
					m_kData.PushBack(VePair<VeFixedString,VeBlobPtr>(*it, spBlob));
				}
			}
		}
		g_pResourceManager->DestoryDir(pkDir);
		kFileList.Clear();
	}
	kMgr.AddMainThreadTask(this);
}
//--------------------------------------------------------------------------
void VeLua::LoadTask::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	if(m_kData.Size())
	{
		VeList< VePair<VeFixedString,VeBlobPtr> >::iterator it = m_kData.Begin();
		VeFixedString kPath;
		{
			VE_AUTO_LOCK_MUTEX_NAME(g_pLua->m_kMutex, kMutex);
			VeFixedString* pkIter = g_pLua->m_kPathMap.Find(it->m_tFirst);
			VE_ASSERT(pkIter);
			kPath = *pkIter;
		}
		if(it->m_tSecond)
		{
			g_pLua->_DoBuffer(it->m_tSecond, it->m_tFirst);
		}
		else
		{
			VE_ASSERT(g_pLua->m_bDebug);
			g_pLua->_DoFile(VeStrchr(kPath, '#') + 1);
		}
		m_kEvent.Callback(kPath, false);
		m_kData.PopFront();
	}

	if(m_kData.Size())
	{
		kMgr.AddMainThreadTask(this);
	}
	else
	{
		m_kNode.Detach();
		m_kEvent.Callback(m_kPath, true);
		DecRefCount();
	}
}
//--------------------------------------------------------------------------
class LuaRequireEvent_S : public VeRefObject
{
public:
	LuaRequireEvent_S(lua_State* pkThread, VeInt32 i32Ref);

	VeDeclRunLuaDelegate(LuaRequireEvent_S, OnEvent);
	lua_State* m_pkThread;
	VeInt32 m_i32Ref;
	VeRefNode<VeRefObject*> m_kNode;
	VeUInt32 m_u32Count;

};
//--------------------------------------------------------------------------
LuaRequireEvent_S::LuaRequireEvent_S(lua_State* pkThread, VeInt32 i32Ref)
	: m_pkThread(pkThread), m_i32Ref(i32Ref), m_u32Count(0)
{
	VeInitDelegate(LuaRequireEvent_S, OnEvent);
	m_kNode.m_tContent = this;
	g_pLua->AddCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
VeImplRunLuaDelegate(LuaRequireEvent_S, OnEvent, pcDesc, bIsEnd)
{
	if(bIsEnd)
	{
		VeLuaBind::RetParam(m_pkThread, m_u32Count);
		VeLuaBind::Resume(m_pkThread, m_i32Ref, g_pLua->GetLua(), 1);
		g_pLua->DelCallbackObj(m_kNode);
	}
	else
	{
		++m_u32Count;
	}
}
//--------------------------------------------------------------------------
static void Require_S(lua_State* pkState, const VeChar8* pcPath)
{
	VeInt32 i32Ref = VeLuaBind::Pause(pkState);
	LuaRequireEvent_S* pkEvent = VE_NEW LuaRequireEvent_S(pkState, i32Ref);
	g_pLua->Require(pcPath, &(pkEvent->m_kOnEvent));
}
//--------------------------------------------------------------------------
class LuaRequireEvent_A : public VeRefObject
{
public:
	LuaRequireEvent_A(const VeLuaSyncHolderPtr& spHolder);

	VeDeclRunLuaDelegate(LuaRequireEvent_A, OnEvent);
	VeLuaSyncHolderPtr m_spHolder;
	VeRefNode<VeRefObject*> m_kNode;

};
//--------------------------------------------------------------------------
LuaRequireEvent_A::LuaRequireEvent_A(const VeLuaSyncHolderPtr& spHolder)
	: m_spHolder(spHolder)
{
	VeInitDelegate(LuaRequireEvent_A, OnEvent);
	m_kNode.m_tContent = this;
	g_pLua->AddCallbackObj(m_kNode);
}
//--------------------------------------------------------------------------
VeImplRunLuaDelegate(LuaRequireEvent_A, OnEvent, pcDesc, bIsEnd)
{
	if(bIsEnd)
	{
		m_spHolder->DecRef();
		m_spHolder = NULL;
		g_pLua->DelCallbackObj(m_kNode);
	}
}
//--------------------------------------------------------------------------
static VeLuaSyncHolder* Require_A(lua_State* pkState, const VeChar8* pcPath)
{
	VeLuaSyncHolderPtr spHolder = VE_NEW VeLuaSyncHolder();
	spHolder->IncRef();
	LuaRequireEvent_A* pkEvent = VE_NEW LuaRequireEvent_A(spHolder);
	g_pLua->Require(pcPath, &(pkEvent->m_kOnEvent));
	return spHolder;
}
//--------------------------------------------------------------------------
static VeInt32 Sync_S(lua_State* pkState)
{
	VeInt32 i32ParamNum = VeLua::GetTop(pkState);
	if(i32ParamNum)
	{
		VeLuaSyncSlotPtr spSlot = VE_NEW VeLuaSyncSlot(pkState);
		for(VeInt32 i(1); i <= i32ParamNum; ++i)
		{
			if(VeLuaBind::TestParam(VeLuaBind::ParamType<VeLuaSyncHolder*>(), pkState, i) != 1) break;
			VeLuaSyncHolder* pkHolder = VeLuaBind::GetParam(VeLuaBind::ParamType<VeLuaSyncHolder*>(), pkState, i);
			spSlot->AddHolder(pkHolder);
		}
		spSlot->Run();
	}
	return 0;
}
//--------------------------------------------------------------------------
static VeInt32 Parallel_S(lua_State* pkState)
{
	VeInt32 i32ParamNum = lua_gettop(pkState);
	if(i32ParamNum)
	{
		VeLuaSyncSignalPtr spSignal = VE_NEW VeLuaSyncSignal(pkState);
		for(VeInt32 i(1); i <= i32ParamNum; ++i)
		{
			if(lua_type(pkState, i) == LUA_TFUNCTION)
			{
				lua_pushvalue(pkState, i);
				spSignal->AddTask(luaL_ref(pkState, LUA_REGISTRYINDEX));
			}
		}
		spSignal->Run();
	}
	return 0;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeLua)
{
	Module() [
		Class<VeLua>() [
			DefSingletonFunc("GetLoadTaskNum", VeLua::ms_pSingleton, &VeLua::GetLoadTaskNum),
			Def("Require_S", &Require_S),
			Def("Require_A", &Require_A),
			DefManualFunc("Sync_S", &Sync_S),
			DefManualFunc("Parallel_S", &Parallel_S)
		]
	];
}
//--------------------------------------------------------------------------
VeLuaSyncSignal::VeLuaSyncSignal(lua_State* pkThread)
	: m_pkThread(pkThread), m_i32Ref(-1), m_u32Count(0)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
void VeLuaSyncSignal::AddTask(VeInt32 i32Task)
{
	m_kTaskList.PushBack(i32Task);
}
//--------------------------------------------------------------------------
void VeLuaSyncSignal::EndTask()
{
	VE_ASSERT(m_u32Count);
	if(!(--m_u32Count))
	{
		if(m_kNode.IsAttach())
		{
			VeLuaBind::Resume(m_pkThread, m_i32Ref, g_pLua->GetLua(), 0);
			g_pLua->DelCallbackObj(m_kNode);
		}
	}
}
//--------------------------------------------------------------------------
void VeLuaSyncSignal::Run()
{
	if(m_kTaskList.Size())
	{
		m_i32Ref = VeLuaBind::Pause(m_pkThread);
		g_pResourceManager->AddFGTask(VeResourceManager::BG_QUEUE_PROCESS, this);
	}
}
//--------------------------------------------------------------------------
void VeLuaSyncSignal::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	lua_State* pkState = g_pLua->GetLua();
	m_u32Count = 1;
	for(VeVector<VeInt32>::iterator it = m_kTaskList.Begin();
		it != m_kTaskList.End(); ++it)
	{
		lua_State* pkThread = MakeFuncThread(pkState, "VeSyncTask");
		if(!pkThread) continue;
		StackHolder kHoldMain(pkState);
		StackHolder kHoldThread(pkThread);
		lua_rawgeti(pkThread, LUA_REGISTRYINDEX, *it);
		if(lua_type(pkThread, -1) != LUA_TFUNCTION) continue;
		if(RetParam(pkThread, this) < 0) continue;
		if(CallFuncThread(pkState, pkThread, 2) != 1) continue;
		++m_u32Count;
	}
	if(m_u32Count > 1)
	{
		--m_u32Count;
		g_pLua->AddCallbackObj(m_kNode);
	}
	else
	{
		VeLuaBind::Resume(m_pkThread, m_i32Ref, g_pLua->GetLua(), 0);
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeLuaSyncSignal)
{
	Module() [
		Class<VeLuaSyncSignal>().
			Def("EndTask", &VeLuaSyncSignal::EndTask)
	];
}
//--------------------------------------------------------------------------
VeLuaSyncHolder::VeLuaSyncHolder() : m_u32TaskCount(0), m_pkSlot(NULL)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeLuaSyncHolder::~VeLuaSyncHolder()
{
	VE_ASSERT(!m_pkSlot);
}
//--------------------------------------------------------------------------
void VeLuaSyncHolder::IncRef()
{
	++m_u32TaskCount;
}
//--------------------------------------------------------------------------
void VeLuaSyncHolder::DecRef()
{
	if(m_u32TaskCount)
	{
		if(!(--m_u32TaskCount))
		{
			if(m_pkSlot) m_pkSlot->DelHolder(this);
		}
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeLuaSyncHolder)
{
	Module() [
		Class<VeLuaSyncHolder>()
	];
}
//--------------------------------------------------------------------------
VeLuaSyncSlot::VeLuaSyncSlot(lua_State* pkThread)
	: m_pkThread(pkThread), m_i32Ref(-1)
{
	m_kNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeLuaSyncSlot::~VeLuaSyncSlot()
{
	m_kHolderList.BeginIterator();
	while(!m_kHolderList.IsEnd())
	{
		VeLuaSyncHolder* pkHolder = m_kHolderList.GetIterNode()->m_tContent;
		m_kHolderList.Next();
		pkHolder->m_kNode.Detach();
		pkHolder->m_pkSlot = NULL;
		pkHolder->DecRefCount();
	}
	VE_ASSERT(m_kHolderList.Empty());
}
//--------------------------------------------------------------------------
void VeLuaSyncSlot::AddHolder(VeLuaSyncHolder* pkHolder)
{
	if(pkHolder && (!pkHolder->m_kNode.IsAttach()) && pkHolder->m_u32TaskCount)
	{
		pkHolder->IncRefCount();
		m_kHolderList.AttachBack(pkHolder->m_kNode);
		pkHolder->m_pkSlot = this;
	}
}
//--------------------------------------------------------------------------
void VeLuaSyncSlot::DelHolder(VeLuaSyncHolder* pkHolder)
{
	VE_ASSERT(pkHolder && pkHolder->m_kNode.IsAttach(m_kHolderList));
	pkHolder->m_kNode.Detach();
	pkHolder->m_pkSlot = NULL;
	pkHolder->DecRefCount();
	if(m_kHolderList.Empty())
	{
		VeLuaBind::Resume(m_pkThread, m_i32Ref, g_pLua->GetLua(), 0);
		g_pLua->DelCallbackObj(m_kNode);
	}
}
//--------------------------------------------------------------------------
void VeLuaSyncSlot::Run()
{
	if(m_kHolderList.Size())
	{
		g_pLua->AddCallbackObj(m_kNode);
		m_i32Ref = VeLuaBind::Pause(m_pkThread);
	}
}
//--------------------------------------------------------------------------
