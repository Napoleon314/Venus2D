////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSharedLib.h
//  Version:     v1.00
//  Created:     14/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
#	define VE_SHARED_LIB HMODULE
#	define VE_SHARED_LIB_NAME(name) (name##".dll")
#	define VE_SHARED_LIB_LOAD(name) LoadLibrary(name)
#	define VE_SHARED_LIB_GET_PROC(lib,proc) GetProcAddress(lib,proc)
#	define VE_SHARED_LIB_UNLOAD(lib) (FreeLibrary(lib) ? VE_OK : VE_ELF)
#elif defined(VE_PLATFORM_LINUX)
#	define VE_SHARED_LIB void*
#	define VE_SHARED_LIB_NAME(name) (name##".so")
#	define VE_SHARED_LIB_LOAD(name) dlopen(name, RTLD_LAZY | RTLD_GLOBAL)
#	define VE_SHARED_LIB_GET_PROC(lib,proc) dlsym(lib,proc)
#	define VE_SHARED_LIB_UNLOAD(lib) dlclose(lib)
#elif defined(VE_PLATFORM_OSX)
#	define VE_SHARED_LIB CFBundleRef
#	define VE_SHARED_LIB_NAME(name) (name##".framework")
	CFBundleRef VE_SHARED_LIB_LOAD(const VeChar8* pcName);
	void* VE_SHARED_LIB_GET_PROC(CFBundleRef hLib,const VeChar8* pcProc);
	VeUInt32 VE_SHARED_LIB_UNLOAD(CFBundleRef hLib);
#endif

#ifdef VE_PLATFORM_PC

class VE_POWER_API VeSharedLib : public VeMemObject
{
public:
	VeSharedLib(const VeTChar* ptcLibName);

	~VeSharedLib();

	bool Load();

	void Unload();

	const VeTChar* GetName();

	void* GetProc(const VeChar8* pcProcName);

protected:
	const VeTChar* const m_ptcLibName;
	VE_SHARED_LIB m_hSharedLib;

};

#endif
