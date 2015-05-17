////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTime.h
//  Version:     v1.00
//  Created:     8/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeTime : public VeSingleton<VeTime>
{
	VeDeclareLuaExport(VeTime);
public:
	VeTime();

	~VeTime();

	void Reset();

	void Update();

	VE_INLINE VeFloat32 GetDeltaTime();

	VE_INLINE VeFloat64 GetDeltaTime64();

	VE_INLINE VeFloat64 GetTime();

	VE_INLINE VeUInt32 GetTimeUInt();

	VE_INLINE VeUInt64 GetCurrentCount();

	VE_INLINE void Pause();

	VE_INLINE void Resume();

	VE_INLINE bool GetPaused();

	VE_INLINE void SetInvert(bool bInv = false);

	VE_INLINE bool GetInvert();

	VE_INLINE VeTimer& GetTimer();

	VE_INLINE void Attach(VeTimeEvent* pkEvent, VeFloat64 f64Delay);

protected:
	VeTimer m_kTimer;

	VeUInt64 m_u64Frequency;
	VeFloat64 m_f64InvFrequency;
	VeUInt64 m_u64StartRecordCount;
	VeUInt64 m_u64LastRecordCount;
	VeUInt64 m_u64CurrentCount;

	VeFloat64 m_f64Time;
	VeFloat64 m_f64DeltaTime;
	bool m_bNeedSkip;
	bool m_bPaused;
	bool m_bInvert;

};

#define g_pTime VeTime::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeTime.inl"
#endif
