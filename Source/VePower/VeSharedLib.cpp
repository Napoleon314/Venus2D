////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSharedLib.cpp
//  Version:     v1.00
//  Created:     14/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
#ifdef VE_PLATFORM_PC
//--------------------------------------------------------------------------
VeSharedLib::VeSharedLib(const VeTChar* ptcLibName)
	: m_ptcLibName(ptcLibName), m_hSharedLib(NULL)
{

}
//--------------------------------------------------------------------------
VeSharedLib::~VeSharedLib()
{
	if(m_hSharedLib)
	{
		Unload();
	}
	VE_ASSERT(!m_hSharedLib);
}
//--------------------------------------------------------------------------
bool VeSharedLib::Load()
{
	if(!m_hSharedLib)
	{
		m_hSharedLib = VE_SHARED_LIB_LOAD(m_ptcLibName);
	}
	return m_hSharedLib ? true : false;
}
//--------------------------------------------------------------------------
void VeSharedLib::Unload()
{
	if(m_hSharedLib)
	{
		VE_ASSERT_EQ(VE_SHARED_LIB_UNLOAD(m_hSharedLib), VE_OK);
		m_hSharedLib = NULL;
	}
}
//--------------------------------------------------------------------------
const VeTChar* VeSharedLib::GetName()
{
	return m_ptcLibName;
}
//--------------------------------------------------------------------------
void* VeSharedLib::GetProc(const VeChar8* pcProcName)
{
	return (void*)VE_SHARED_LIB_GET_PROC(m_hSharedLib, pcProcName);
}
//--------------------------------------------------------------------------
#ifdef VE_PLATFORM_OSX
//--------------------------------------------------------------------------
CFBundleRef VE_SHARED_LIB_LOAD(const VeChar8* pcName)
{
    CFStringRef hName = CFStringCreateWithCString(kCFAllocatorDefault, pcName, kCFStringEncodingASCII);
    CFURLRef hURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, hName, kCFURLPOSIXPathStyle, true);
    CFBundleRef hLib = CFBundleCreate(kCFAllocatorDefault, hURL);
    VE_ASSERT(hLib);
    CFRelease(hURL);
    CFRelease(hName);
    return hLib;
}
//--------------------------------------------------------------------------
void* VE_SHARED_LIB_GET_PROC(CFBundleRef hLib,const VeChar8* pcProc)
{
    CFStringRef hProc = CFStringCreateWithCString(kCFAllocatorDefault, pcProc, kCFStringEncodingASCII);
    void* pvRet = CFBundleGetFunctionPointerForName(hLib, hProc);
    CFRelease(hProc);
    return pvRet;
}
//--------------------------------------------------------------------------
VeUInt32 VE_SHARED_LIB_UNLOAD(CFBundleRef hLib)
{
    CFRelease(hLib);
    return VE_OK;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
