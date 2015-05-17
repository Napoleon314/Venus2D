////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VePowerDefines.h
//  Version:     v1.00
//  Created:     5/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#if (defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)) && defined(VE_DYNAMIC_LIB)
#	ifdef VE_POWER_EXPORT
#		define VE_POWER_API __declspec (dllexport)
#	else
#		define VE_POWER_API __declspec (dllimport)
#	endif
#else
#	define VE_POWER_API
#endif

#ifndef VE_NO_INLINE
#	define VE_POWER_INLINE inline
#else
#	define VE_POWER_INLINE VE_POWER_API
#endif

#ifndef VE_NO_INLINE
#	define VE_INLINE inline
#else
#	define VE_INLINE
#endif

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
#	define VE_ALIGNED(n) __declspec(align(n))
#	define VE_FORCE_INLINE __forceinline
#else
#	define VE_ALIGNED(n) __attribute__((aligned(n)))
#	define VE_FORCE_INLINE inline
#endif

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_LINUX) || defined(VE_PLATFORM_OSX)
#	define VE_PLATFORM_PC
#elif defined(VE_PLATFORM_IOS) || defined(VE_PLATFORM_ANDROID) || defined(VE_PLATFORM_MOBILE_SIM)
#	define VE_PLATFORM_MOBILE
#endif

#if defined(VE_PLATFORM_OSX) || defined(VE_PLATFORM_IOS)
#   define VE_PLATFORM_APPLE
#endif

#if defined(VE_PLATFORM_WIN)
#	define VE_PLATFORM_NAME "Windows"
#	define VE_PLATFORM_NAME_LITE "win"
#	define VE_PLATFORM_MASK (0x1)
#elif defined(VE_PLATFORM_MOBILE_SIM)
#	define VE_PLATFORM_NAME "MobSim"
#	define VE_PLATFORM_NAME_LITE "sim"
#	define VE_PLATFORM_MASK (0x8)
#elif defined(VE_PLATFORM_LINUX)
#	define VE_PLATFORM_NAME "Linux"
#	define VE_PLATFORM_NAME_LITE "lin"
#	define VE_PLATFORM_MASK (0x2)
#elif defined(VE_PLATFORM_OSX)
#	define VE_PLATFORM_NAME "Macosx"
#	define VE_PLATFORM_NAME_LITE "osx"
#	define VE_PLATFORM_MASK (0x4)
#elif defined(VE_PLATFORM_IOS)
#	define VE_PLATFORM_NAME "IOS"
#	define VE_PLATFORM_NAME_LITE "ios"
#	define VE_PLATFORM_MASK (0x10)
#elif defined(VE_PLATFORM_ANDROID)
#	define VE_PLATFORM_NAME "Android"
#	define VE_PLATFORM_NAME_LITE "and"
#	define VE_PLATFORM_MASK (0x20)
#endif

#if defined(VE_PLATFORM_PC)
#   define VE_ENABLE_GL
#	define VE_ENABLE_SSE
#elif defined(VE_PLATFORM_MOBILE)
#   define VE_ENABLE_GLES2
#	define VE_NEON
#endif

#if defined(VE_PLATFORM_MOBILE_SIM) || defined(VE_PLATFORM_ANDROID)
#	define VE_ENABLE_DEVICE_LOST
#endif

#ifdef VE_PLATFORM_WIN
#	define VE_ENABLE_D3D11
#endif

#ifdef VE_PLATFORM_ANDROID
#	define VE_USE_SLES
#else
#	define VE_USE_OAL
#endif

#ifndef NULL
#	define NULL (0)
#endif

#define VE_NULL (0)
#define VE_OK (0)
#define VE_ELF (-1)
#define VE_INFINITE 0xFFFFFFFF

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	include <process.h>
#endif

#ifdef VE_PLATFORM_LINUX
#	include <X11/Xlib.h>
#	include <X11/Xutil.h>
#	include <X11/extensions/Xrandr.h>
#	include <pthread.h>
#	include <errno.h>
#	include <signal.h>
#	include <sys/time.h>
#	include <ctype.h>
#endif

#ifdef VE_PLATFORM_OSX
#	include <Carbon/Carbon.h>
#   include <pthread.h>
#   include <errno.h>
#   include <sys/time.h>
#endif

#ifdef VE_PLATFORM_IOS
#   include <pthread.h>
#   include <errno.h>
#   include <sys/time.h>
#endif

#ifdef VE_PLATFORM_ANDROID
#	include <android/log.h>
#	include <android/window.h>
#	include <android_native_app_glue.h>
#   include <pthread.h>
#   include <errno.h>
#	include <ctype.h>
#endif

enum VeResult
{
	VE_S_OK             = 0x0,
	VE_E_FAIL			= 0x80004005,

	VE_E_FILE_ACCESS,
	VE_E_FILE_CREATE,
	VE_E_FILE_WRITE
};

#define VE_SUCCEEDED(hr) ((hr)==0)
#define VE_FAILED(hr) ((hr)!=0)

typedef float VeFloat32;
typedef double VeFloat64;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)

typedef __int8 VeInt8;
typedef unsigned __int8 VeUInt8;
typedef __int16 VeInt16;
typedef unsigned __int16 VeUInt16;
typedef __int32 VeInt32;
typedef unsigned __int32 VeUInt32;
typedef __int64 VeInt64;
typedef unsigned __int64 VeUInt64;

#define VE_CALLBACK __stdcall

#elif defined(VE_PLATFORM_LINUX) || defined(VE_PLATFORM_OSX)

#include <stdint.h>
#include <stdarg.h>
#include <wchar.h>
#include <dlfcn.h>

typedef int8_t VeInt8;
typedef uint8_t VeUInt8;
typedef int16_t VeInt16;
typedef uint16_t VeUInt16;
typedef int32_t VeInt32;
typedef uint32_t VeUInt32;
typedef int64_t VeInt64;
typedef uint64_t VeUInt64;

#define VE_CALLBACK

#else

#include <stdint.h>
#ifdef VE_PLATFORM_IOS
#include <stdarg.h>
#endif
#include <wchar.h>

typedef __int8_t VeInt8;
typedef __uint8_t VeUInt8;
typedef __int16_t VeInt16;
typedef __uint16_t VeUInt16;
typedef __int32_t VeInt32;
typedef __uint32_t VeUInt32;
typedef __int64_t VeInt64;
typedef __uint64_t VeUInt64;

#define VE_CALLBACK

#endif

typedef size_t VeSizeT;
typedef long VeLong;
typedef unsigned long VeULong;
typedef volatile VeUInt32 VeAtomic32;
typedef volatile VeUInt64 VeAtomic64;
typedef char VeChar8;
typedef wchar_t VeChar16;

#ifdef VE_UNICODE

typedef VeChar16 VeTChar;
#define VE_TEXT(str) L##str

#else

typedef VeChar8 VeTChar;
#define VE_TEXT(str) str

#endif

typedef VeUInt8 VeByte;
typedef VeUInt16 VeWord;
typedef VeUInt32 VeDWord;

enum VeEncode
{
	VE_ENCODE_ANSI,
	VE_ENCODE_UTF8,
	VE_ENCODE_UNICODE16,
	VE_ENCODE_UNICODE32,
	VE_ENCODE_MAX
};

struct VePoint
{
	VeInt32 x, y;
};

struct VeRect
{
	VeInt32 x, y;
	VeInt32 w, h;
};

VE_FORCE_INLINE bool VeRectEmpty(const VeRect* pkRect)
{
	return ((!pkRect) || (pkRect->w <= 0) || (pkRect->h <= 0)) ? true : false;
}

VE_POWER_API bool VeEnclosePoints(const VePoint* pkPoints,
	VeInt32 i32Count, const VeRect* pkClip, VeRect* pkResult);

#define VE_MAX(a,b) (((a)>(b))?(a):(b))
#define VE_MIN(a,b) (((a)<(b))?(a):(b))
#define VE_CLAMP(a,l,h) ((a < l) ? l : ((a > h) ? h : a))
#define VE_SAT(a) VE_CLAMP(a,0.0f,1.0f)

#define VE_TRUE (1)
#define VE_FALSE (0)
#define VE_BOOL VeUInt32

#define VE_INT8_MIN (-128)
#define VE_INT8_MAX (127)
#define VE_UINT8_MAX (0xff)
#define VE_CHAR_MIN VE_INT8_MIN
#define VE_CHAR_MAX VE_INT8_MAX
#define VE_INT16_MIN (-32768)
#define VE_INT16_MAX (32767)
#define VE_UINT16_MAX (0xffff)
#define VE_INT32_MIN (-2147483648)
#define VE_INT32_MAX (2147483647)
#define VE_UINT32_MAX (0xffffffff)
#define VE_INT64_MAX (9223372036854775807i64)
#define VE_INT64_MIN (-9223372036854775808i64)
#define VE_UINT64_MAX (0xffffffffffffffffui64)
#define VE_SIZET_MAX ((VeSizeT)-1)

#define VE_MAX_PATH_LEN (1024)

#define VE_MASK(location) (VeUInt32(0x01<<(location)))
#define VE_MASK_HAS_ANY(flag,mask) (((flag)&(mask))!=0)
#define VE_MASK_HAS_ALL(flag,mask) (((flag)&(mask))==(mask))
#define VE_MASK_ADD(flag,mask) ((flag)|=(mask))
#define VE_MASK_DEL(flag,mask) ((flag)&=(~(mask)))
#define VE_MASK_REMOVE(flag,mask) ((flag)&(~(mask)))
#define VE_MASK_CHANGE(location,flag)									\
	if(VE_MASK_HAS_ANY(flag,VE_MASK(location)))							\
		VE_MASK_DEL(flag,VE_MASK(location));							\
	else																\
		VE_MASK_ADD(flag,VE_MASK(location));

#define VE_MAKE_ID(ch0, ch1, ch2, ch3)									\
	((VeDWord)(VeByte)(ch0) | ((VeDWord)(VeByte)(ch1) << 8) |			\
	((VeDWord)(VeByte)(ch2) << 16) | ((VeDWord)(VeByte)(ch3) << 24 ))

template<class T>
void VeSwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

#define VeAbort abort

#define VeMemorySet(dst,val,len) (memset(dst,val,len))
#define VeZeroMemory(dst,len) (memset((dst),0,(len)))
#define VeZeroMemoryEx(dst,size,count) (VeZeroMemory((dst),(size)*(count)))
#define VeMemoryCopy(dst,src,len) (memcpy((dst),(src),(len)))
#define VeCrazyCopy(dst,src,len) (memcpy((dst),(src),(len)))
#define VeCrazyCopyEx(dst,src,size,count) (VeCrazyCopy((dst),(src),(size)*(count)))

#ifdef VE_DEBUG
#	if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
#		include <assert.h>
#		define VE_ASSERT assert
#	else
		VE_POWER_API void VeAssert(const VeChar8* pcMessage, const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction);
#		define VE_ASSERT(exp) (void)((!!(exp))||(VeAssert(#exp,__FILE__,__LINE__,__FUNCTION__),0))
#	endif
#	define VE_ASSERT_EQ(exp,val) VE_ASSERT(exp==val)
#	define VE_ASSERT_NOT_EQ(exp,val) VE_ASSERT(exp!=val)
#else
#	define VE_ASSERT(x)
#	define VE_ASSERT_EQ(exp,val) (exp)
#	define VE_ASSERT_NOT_EQ(exp,val) (exp)
#endif

void VE_POWER_API VeConsoleInit(bool bLuaDebug);

void VE_POWER_API VeConsoleTerm();

namespace VeLuaBind
{
	class ClassContent;
	typedef ClassContent* ClassContentPointer;
	template<class T> class ClassBase;

	template<class T>
	struct ParamType
	{

	};
}

struct lua_State;

VE_POWER_API void VePowerExport();

#define VeDeclareLuaExport(classname) \
	public: \
		static const VeLuaBind::ClassContentPointer& GetLuaBindClass() { return ms_pkLuaBindClass; } \
		static const VeChar8* GetClassName() { return #classname; } \
		static void LuaBindInit(); \
		static void LuaBindTerm(); \
	private: \
		friend class VeLuaBind::ClassBase<classname>; \
		static VeLuaBind::ClassContent* ms_pkLuaBindClass

#define VeDeclareLuaRttiExport(classname) \
	public: \
		static const VeLuaBind::ClassContentPointer& GetLuaBindClass() { return ms_pkLuaBindClass; } \
		static const VeChar8* GetClassName() { return #classname; } \
		static void LuaBindInit(); \
		static void LuaBindTerm(); \
		virtual VeLuaBind::ClassContent* GetLuaClassContent() { return classname::ms_pkLuaBindClass; } \
	private: \
		friend class VeLuaBind::ClassBase<classname>; \
		static VeLuaBind::ClassContent* ms_pkLuaBindClass

#define VeImplementLuaExport(classname) \
	using namespace VeLuaBind; \
	ClassContent* classname::ms_pkLuaBindClass = NULL; \
	void classname::LuaBindTerm() \
	{ \
		if(ms_pkLuaBindClass) \
		{ \
			ms_pkLuaBindClass->DecRefCount(); \
			ms_pkLuaBindClass = NULL; \
		} \
	} \
	void classname::LuaBindInit()
