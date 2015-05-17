////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLog.h
//  Version:     v1.00
//  Created:     9/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

enum VeLogType
{
	VE_LOG_TYPE_DEBUG,
	VE_LOG_TYPE_INFO,
	VE_LOG_TYPE_WARN,
	VE_LOG_TYPE_ERROR,
	VE_LOG_TYPE_MAX
};

#define VE_LOG_BUFFER_SIZE (1024)

VeSmartPointer(VeLogger);

class VE_POWER_API VeLogger : public VeRefObject
{
public:
	enum LogOutput
	{
		OUTPUT_CONSOLE,
		OUTPUT_DEBUGOUTPUT,
		OUTPUT_LUASTUDIO,
		OUTPUT_MAX
	};

	virtual ~VeLogger() {}

	virtual void AppendLog(VeLogType eType, const VeChar8* pcTag, const VeChar8* pcFormat, va_list kArgs) = 0;

	static void AppendLog(VeLogType eType, const VeChar8* pcTag, const VeChar8* pcFormat, ...);

	static void SetLog(LogOutput eOutput);

	static void SetLog(const VeLoggerPtr& spLog);
};

#ifdef VE_DEBUG
#	define VE_LOG_D(tag,...) VeLogger::AppendLog(VE_LOG_TYPE_DEBUG,tag,__VA_ARGS__)
#else
#	define VE_LOG_D(tag,...)
#endif

#define VeDebugOutput(...) VE_LOG_D("Venus3D",__VA_ARGS__)

#define VE_LOG_I(tag,...) VeLogger::AppendLog(VE_LOG_TYPE_INFO,tag,__VA_ARGS__)
#define VE_LOG_W(tag,...) VeLogger::AppendLog(VE_LOG_TYPE_WARN,tag,__VA_ARGS__)
#define VE_LOG_E(tag,...) VeLogger::AppendLog(VE_LOG_TYPE_ERROR,tag,__VA_ARGS__)
