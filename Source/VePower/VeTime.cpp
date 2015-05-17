////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTime.cpp
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeTime.inl"
#endif

//--------------------------------------------------------------------------
#if (!defined(VE_PLATFORM_WIN)) && (!defined(VE_PLATFORM_MOBILE_SIM))
//--------------------------------------------------------------------------
#include <sys/time.h>
//--------------------------------------------------------------------------
void VeTimeOfDay(VeUInt64& u64Time);
//--------------------------------------------------------------------------
void VeTimeOfDay(VeUInt64& u64Time)
{
	timeval kTime;
	gettimeofday(&kTime, NULL);
	u64Time = kTime.tv_sec * 1000000ull + kTime.tv_usec;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeTime::VeTime()
{
	Reset();
}
//--------------------------------------------------------------------------
VeTime::~VeTime()
{

}
//--------------------------------------------------------------------------
void VeTime::Reset()
{
#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_u64Frequency);
	QueryPerformanceCounter((LARGE_INTEGER *)&m_u64CurrentCount);
#else
	m_u64Frequency = 1000000;
	VeTimeOfDay(m_u64CurrentCount);
#endif
	m_f64InvFrequency = 1.0 / VeFloat64(m_u64Frequency);

	m_u64StartRecordCount = m_u64CurrentCount;
	m_u64LastRecordCount = m_u64CurrentCount;
	m_f64Time = 0;
	m_f64DeltaTime = 0;
	m_bNeedSkip = true;
	m_bPaused = false;
	m_bInvert = false;
}
//--------------------------------------------------------------------------
void VeTime::Update()
{
	m_u64LastRecordCount = m_u64CurrentCount;

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
	QueryPerformanceCounter((LARGE_INTEGER*)&m_u64CurrentCount);
#else
	VeTimeOfDay(m_u64CurrentCount);
#endif

	VeUInt64 u64DeltaCount = m_u64CurrentCount - m_u64LastRecordCount;

	if(m_bPaused)
	{
		m_u64StartRecordCount += u64DeltaCount;
	}
	else if(m_bInvert)
	{
		m_u64StartRecordCount += u64DeltaCount << 1;
		if(m_u64StartRecordCount > m_u64CurrentCount)
		{
			m_u64StartRecordCount = m_u64CurrentCount;
		}
	}

	VeFloat64 f64LastTime = m_f64Time;

	VeUInt64 u64Elapsed = m_u64CurrentCount - m_u64StartRecordCount;
	m_f64Time = VeFloat64(u64Elapsed) * m_f64InvFrequency;
	m_f64DeltaTime = m_f64Time - f64LastTime;
	if(m_bNeedSkip)
	{
		if(m_f64DeltaTime < 0.04)
		{
			m_bNeedSkip = false;
		}
		else
		{
			m_f64DeltaTime = 0.0;
		}
	}

	m_kTimer.Tick(VeUInt64(m_f64Time * 1000.0));
}
//--------------------------------------------------------------------------
class LuaTimeEvent_S : public VeTimeEvent
{
public:
	LuaTimeEvent_S(lua_State* pkThread, VeInt32 i32Ref);

	VeDeclTimeDelegate(LuaTimeEvent_S, OnEvent);
	lua_State* m_pkThread;
	VeInt32 m_i32Ref;

};
//--------------------------------------------------------------------------
LuaTimeEvent_S::LuaTimeEvent_S(lua_State* pkThread, VeInt32 i32Ref)
	: m_pkThread(pkThread), m_i32Ref(i32Ref)
{
	VeInitDelegate(LuaTimeEvent_S, OnEvent);
	AddDelegate(VeDelegate(OnEvent));
}
//--------------------------------------------------------------------------
VeImplTimeDelegate(LuaTimeEvent_S, OnEvent, spEvent)
{
	VeLuaBind::RetParam(m_pkThread, g_pTime->GetTime());
	VeLuaBind::Resume(m_pkThread, m_i32Ref, g_pLua->GetLua(), 1);
}
//--------------------------------------------------------------------------
static void VeSleep_S(lua_State* pkState, VeFloat64 f64Time)
{
	VeInt32 i32Ref = VeLuaBind::Pause(pkState, 0, NULL);
	g_pTime->Attach(VE_NEW LuaTimeEvent_S(pkState, i32Ref), f64Time);
}
//--------------------------------------------------------------------------
class LuaTimeEvent_A : public VeTimeEvent
{
public:
	LuaTimeEvent_A(const VeLuaSyncHolderPtr& spHolder);

	VeDeclTimeDelegate(LuaTimeEvent_A, OnEvent);
	VeLuaSyncHolderPtr m_spHolder;

};
//--------------------------------------------------------------------------
LuaTimeEvent_A::LuaTimeEvent_A(const VeLuaSyncHolderPtr& spHolder)
	: m_spHolder(spHolder)
{
	VeInitDelegate(LuaTimeEvent_A, OnEvent);
	AddDelegate(VeDelegate(OnEvent));
}
//--------------------------------------------------------------------------
VeImplTimeDelegate(LuaTimeEvent_A, OnEvent, spEvent)
{
	m_spHolder->DecRef();
	m_spHolder = NULL;
}
//--------------------------------------------------------------------------
static VeLuaSyncHolder* VeSleep_A(lua_State* pkState, VeFloat64 f64Time)
{
	VeLuaSyncHolderPtr spHolder = VE_NEW VeLuaSyncHolder();
	spHolder->IncRef();
	g_pTime->Attach(VE_NEW LuaTimeEvent_A(spHolder), f64Time);
	return spHolder;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeTime)
{
	Module() [
		Class<VeTime>() [
			DefSingletonFunc("GetDeltaTime", VeTime::ms_pSingleton, &VeTime::GetDeltaTime64),
			DefSingletonFunc("GetTime", VeTime::ms_pSingleton, &VeTime::GetTime)
		],
		Def("VeSleep_S", &VeSleep_S),
		Def("VeSleep_A", &VeSleep_A)
	];
}
//--------------------------------------------------------------------------
