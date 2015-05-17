////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLua.h
//  Version:     v1.00
//  Created:     26/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

struct lua_State;
VeSmartPointer(VeBlob);

class VE_POWER_API VeLua : public VeSingleton<VeLua>
{
	VeDeclareLuaExport(VeLua);
public:
	typedef VeEvent<const VeChar8*,bool> LoadTaskEvent;
	typedef VeAbstractDelegate<const VeChar8*,bool> LoadTaskDelegate;

	struct LoadTask : public VeBackgroundTask
	{
		LoadTask(const VeChar8* pcPath, LoadTaskDelegate* pkDele);

		virtual void DoBackgroundTask(VeBackgroundTaskQueue& kMgr);

		virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

		VeRefNode<LoadTask*> m_kNode;
		VeString m_kPath;
		VeVector<VeFixedString> m_kDescList;
		VeList< VePair<VeFixedString,VeBlobPtr> > m_kData;
		LoadTaskEvent m_kEvent;
	};

	VeLua(bool bDebug);

	~VeLua();

	VE_INLINE bool IsDebug();

	VE_INLINE lua_State* GetLua();

	VE_INLINE VeInt32 GetTop();

	VE_INLINE void SetTop(VeInt32 i32Value);

	VE_INLINE VeUInt32 GetLoadTaskNum();

	void DoFileSync(const VeChar8* pcPath);

	void Require(const VeChar8* pcPath, LoadTaskDelegate* pkDelegate = NULL);

	void CallFunction(const VeChar8* pcDesc, ...);

	void SetValue(const VeChar8* pcName, VeFloat32 f32Value);

	VeFloat32 GetValue(const VeChar8* pcName);

	void SetString(const VeChar8* pcName, const VeChar8* pcStr);

	const VeChar8* GetString(const VeChar8* pcName);

	bool GetExpression(const VeChar8* pcExp, VeFloat64& f64Out);

	VeFloat32 GetExpression(const VeChar8* pcExp, VeFloat32 f32Defult = 0.0f);

	void AddCallbackObj(VeRefNode<VeRefObject*>& kNode);

	void DelCallbackObj(VeRefNode<VeRefObject*>& kNode);

	VeInt32 Ref(const VeChar8* pcFuncName);

	void UnRef(VeInt32 i32Ref);

	lua_State* MakeFullCallThread();

	VeInt32 GetFullCall();

	static VeInt32 GetTop(lua_State* pkState);

	static void SetTop(lua_State* pkState, VeInt32 i32Value);

protected:
	void _DoFile(const VeChar8* pcName);

	void _DoBuffer(const VeChar8* pcData, VeInt32 i32Length, const VeChar8* pcName);

	void _DoBuffer(const VeBlobPtr& spBlob, const VeChar8* pcName);

	static VeInt32 Print(lua_State* pkLua);

	const VE_BOOL m_bDebug;
	lua_State* m_pkLua;
	VeRefList<LoadTask*> m_kTaskList;
	VeStringMap<VeFixedString> m_kPathMap;
	VeRefList<VeRefObject*> m_kCallbackList;
	VeThread::Mutex m_kMutex;
	VeInt32 m_i32FullCall;

};

class VE_POWER_API VeLuaSyncSignal : public VeBackgroundTask
{
	VeDeclareLuaRttiExport(VeLuaSyncSignal);
public:
	VeLuaSyncSignal(lua_State* pkThread);

	void AddTask(VeInt32 i32Task);

	void EndTask();

	void Run();

	virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

protected:
	lua_State* m_pkThread;
	VeInt32 m_i32Ref;
	VeRefNode<VeRefObject*> m_kNode;
	VeVector<VeInt32> m_kTaskList;
	VeUInt32 m_u32Count;

};

VeSmartPointer(VeLuaSyncSignal);
VeSmartPointer(VeLuaSyncSlot);
VeSmartPointer(VeLuaSyncHolder);

class VE_POWER_API VeLuaSyncHolder : public VeRefObject
{
	VeDeclareLuaRttiExport(VeLuaSyncHolder);
public:
	VeLuaSyncHolder();

	virtual ~VeLuaSyncHolder();

	void IncRef();

	void DecRef();

protected:
	friend class VeLuaSyncSlot;
	VeUInt32 m_u32TaskCount;
	VeLuaSyncSlot* m_pkSlot;
	VeRefNode<VeLuaSyncHolder*> m_kNode;

};

class VE_POWER_API VeLuaSyncSlot : public VeRefObject
{
public:
	VeLuaSyncSlot(lua_State* pkThread);

	virtual ~VeLuaSyncSlot();

	void AddHolder(VeLuaSyncHolder* pkHolder);

	void DelHolder(VeLuaSyncHolder* pkHolder);

	void Run();

protected:
	lua_State* m_pkThread;
	VeInt32 m_i32Ref;
	VeRefNode<VeRefObject*> m_kNode;
	VeRefList<VeLuaSyncHolder*> m_kHolderList;

};

#define VeDeclRunLuaDelegate(class,name) \
	void name(const VeChar8*,bool); \
	VeMemberDelegate<class,const VeChar8*,bool> m_k##name

#define VeImplRunLuaDelegate(class,name,file,end) \
	void class::name(const VeChar8* file, bool end)

#define g_pLua VeLua::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeLua.inl"
#endif
