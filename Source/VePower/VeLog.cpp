////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLog.cpp
//  Version:     v1.00
//  Created:     9/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
VeLoggerPtr s_spMainLog = NULL;
//--------------------------------------------------------------------------
void VeLogger::AppendLog(VeLogType eType, const VeChar8* pcTag, const VeChar8* pcFormat, ...)
{
	VE_ASSERT(s_spMainLog);
	va_list kArgs;
	va_start(kArgs, pcFormat);
	s_spMainLog->AppendLog(eType, pcTag, pcFormat, kArgs);
	va_end(kArgs);
}
//--------------------------------------------------------------------------
class VeLogConsole : public VeLogger
{
public:
	virtual void AppendLog(VeLogType eType, const VeChar8* pcTag, const VeChar8* pcFormat, va_list kArgs)
	{
#ifndef VE_DEBUG
		if(eType == VE_LOG_TYPE_DEBUG) return;
#endif
		VE_ASSERT(eType < VE_LOG_TYPE_MAX);
		VE_ASSERT(pcFormat);

		VeChar8 s_acLogBuffer[VE_LOG_BUFFER_SIZE];

#ifdef VE_PLATFORM_ANDROID

		const android_LogPriority aeLogTypeMap[VE_LOG_TYPE_MAX] =
		{
			ANDROID_LOG_DEBUG,
			ANDROID_LOG_INFO,
			ANDROID_LOG_WARN,
			ANDROID_LOG_ERROR
		};

		VeVsprintf(s_acLogBuffer, VE_LOG_BUFFER_SIZE, pcFormat, kArgs);
		__android_log_print(aeLogTypeMap[eType], pcTag, "%s", s_acLogBuffer);

#else

		const VeChar8* apcLogTypes[VE_LOG_TYPE_MAX] =
		{
			"DEBUG",
			"INFO",
			"WARN",
			"ERROR"
		};

		VeInt32 i32Pointer(0);

		i32Pointer += VeSprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, "VE_LOG|TYPE:%s|TAG:%s|LOG:", apcLogTypes[eType], pcTag);
		i32Pointer += VeVsprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, pcFormat, kArgs);
		i32Pointer += VeSprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, "\n");

		printf("%s", s_acLogBuffer);

#endif
	}
};
//--------------------------------------------------------------------------
class VeLogDebugOutput : public VeLogger
{
public:
	virtual void AppendLog(VeLogType eType, const VeChar8* pcTag, const VeChar8* pcFormat, va_list kArgs)
	{
#ifndef VE_DEBUG
		if(eType == VE_LOG_TYPE_DEBUG) return;
#endif
		VE_ASSERT(eType < VE_LOG_TYPE_MAX);
		VE_ASSERT(pcFormat);

		VeChar8 s_acLogBuffer[VE_LOG_BUFFER_SIZE];

#ifdef VE_PLATFORM_ANDROID

		const android_LogPriority aeLogTypeMap[VE_LOG_TYPE_MAX] =
		{
			ANDROID_LOG_DEBUG,
			ANDROID_LOG_INFO,
			ANDROID_LOG_WARN,
			ANDROID_LOG_ERROR
		};

		VeVsprintf(s_acLogBuffer, VE_LOG_BUFFER_SIZE, pcFormat, kArgs);
		__android_log_print(aeLogTypeMap[eType], pcTag, "%s", s_acLogBuffer);

#else

		const VeChar8* apcLogTypes[VE_LOG_TYPE_MAX] =
		{
			"DEBUG",
			"INFO",
			"WARN",
			"ERROR"
		};

		VeInt32 i32Pointer(0);

		i32Pointer += VeSprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, "VE_LOG|TYPE:%s|TAG:%s|LOG:", apcLogTypes[eType], pcTag);
		i32Pointer += VeVsprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, pcFormat, kArgs);
		i32Pointer += VeSprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, "\n");

#		if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
		OutputDebugStringA(s_acLogBuffer);
#		else
		printf("%s", s_acLogBuffer);
#		endif

#endif
	}
};
//--------------------------------------------------------------------------
class VeLogLuaStudio : public VeLogger
{
public:
	virtual void AppendLog(VeLogType eType, const VeChar8* pcTag, const VeChar8* pcFormat, va_list kArgs)
	{
#ifndef VE_DEBUG
		if(eType == VE_LOG_TYPE_DEBUG) return;
#endif
		VE_ASSERT(eType < VE_LOG_TYPE_MAX);
		VE_ASSERT(pcFormat);

		VeChar8 s_acLogBuffer[VE_LOG_BUFFER_SIZE];

		const VeChar8* apcLogTypes[VE_LOG_TYPE_MAX] =
		{
			"DEBUG",
			"INFO",
			"WARN",
			"ERROR"
		};

		VeInt32 i32Pointer(0);

		i32Pointer += VeSprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, "VE_LOG|TYPE:%s|TAG:%s|LOG:", apcLogTypes[eType], pcTag);
		i32Pointer += VeVsprintf(s_acLogBuffer + i32Pointer, VE_LOG_BUFFER_SIZE - i32Pointer, pcFormat, kArgs);

		if(g_pLua)
		{
			VeLuaCall<void>("print", s_acLogBuffer);
		}
	}

};
//--------------------------------------------------------------------------
void VeLogger::SetLog(LogOutput eOutput)
{
	switch(eOutput)
	{
	case OUTPUT_CONSOLE:
		s_spMainLog = VE_NEW VeLogConsole;
		break;
	case OUTPUT_DEBUGOUTPUT:
		s_spMainLog = VE_NEW VeLogDebugOutput;
		break;
	case OUTPUT_LUASTUDIO:
		s_spMainLog = VE_NEW VeLogLuaStudio;
		break;
	default:
		s_spMainLog = NULL;
		break;
	}
}
//--------------------------------------------------------------------------
void VeLogger::SetLog(const VeLoggerPtr& spLog)
{
	s_spMainLog = spLog;
}
//--------------------------------------------------------------------------
