////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMain.h
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#if (defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)) && defined(VE_DYNAMIC_LIB)
#	ifdef VE_MAIN_EXPORT
#		define VE_MAIN_API __declspec (dllexport)
#	else
#		define VE_MAIN_API __declspec (dllimport)
#	endif
#else
#	define VE_MAIN_API
#endif

#ifndef VE_NO_INLINE
#	define VE_MAIN_INLINE inline
#else
#	define VE_MAIN_INLINE VE_MAIN_API
#endif

struct VeStartParams
{
	const VeChar8* m_pcAppName;
	const VeChar8* m_pcCmdLine;
	const VeChar8* m_pcConfigName;
	const VeChar8* m_pcConfigCustomDir;
	const VeChar8* m_pcConfigDefaultDir;
	const VeChar8* m_pcStartupLua;
#	if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
	HINSTANCE m_hInstance;
#	elif defined(VE_PLATFORM_ANDROID)
	android_app* m_pkAppState;
#	else
#	endif
};

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
#	define VE_ENTRY_FUNCTION \
	extern void VeMain(VeStartParams& kParams); \
	INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow) \
	{ \
		VeStartParams kParams = { "Venus3D", lpCmdLine, "startup.cfg", "file#", NULL, "file#Lua/startup.lua", hInstance }; \
		VeMain(kParams); \
		return 0; \
	}
#elif defined(VE_PLATFORM_IOS)
#   define VE_ENTRY_FUNCTION
#elif defined(VE_PLATFORM_LINUX) || defined(VE_PLATFORM_OSX)
#	define VE_ENTRY_FUNCTION \
    extern void VeMain(VeStartParams& kParams); \
    int main(int iArgc, char* apcArgv[]) \
    { \
        VeChar8 acCmd[256]; \
        VeZeroMemory(acCmd, 256); \
        VeUInt32 u32Pos(0); \
        for(VeUInt32 i(1); i < iArgc; ++i) \
        { \
            u32Pos += VeSprintf(acCmd + u32Pos, 256 - u32Pos, u32Pos ? " %s" : "%s", apcArgv[i]); \
        } \
        VeStartParams kParams = { "Venus3D", acCmd, "startup.cfg", "file#", NULL, "file#Lua/startup.lua" }; \
        VeMain(kParams); \
        return 0; \
    }
#elif defined(VE_PLATFORM_ANDROID)
#   define VE_ENTRY_FUNCTION \
	extern void VeMain(VeStartParams& kParams); \
	void android_main(struct android_app* state) \
	{ \
		/*VeChar8 acDataPath[256]; \VeSprintf(acDataPath, "file#%s", state->activity->internalDataPath); */\
		app_dummy(); \
		VeStartParams kParams = { "Venus3D", "", "startup.cfg", NULL, "asset#", "asset#Lua/startup.lua", state }; \
		VeMain(kParams); \
	}
#endif

VE_MAIN_API void VeStartEngine(VeStartParams& kParams);

VE_MAIN_API void VeMainExport();
