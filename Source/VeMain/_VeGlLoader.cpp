////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeGlLoader.cpp
//  Version:     v1.00
//  Created:     14/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeGlLoader.h"

//--------------------------------------------------------------------------
#ifdef VE_ENABLE_GL
//--------------------------------------------------------------------------
VeSharedLib* g_pkOpenGL = NULL;
//--------------------------------------------------------------------------
#if defined(VE_PLATFORM_WIN)
#	pragma comment(lib,"opengl32.lib")
#	define OPENGL_LIB_NAME "opengl32.dll"
#elif defined(VE_PLATFORM_LINUX)
#	define OPENGL_LIB_NAME "libGL.so"
#elif defined(VE_PLATFORM_OSX)
#	define OPENGL_LIB_NAME "/System/Library/Frameworks/OpenGL.framework"
#endif
//--------------------------------------------------------------------------
#ifdef VE_GLX
glXQueryExtensionFunc _glXQueryExtension = NULL;
glXChooseVisualFunc _glXChooseVisual = NULL;
glXCreateContextFunc _glXCreateContext = NULL;
glXMakeCurrentFunc _glXMakeCurrent = NULL;
glXSwapBuffersFunc _glXSwapBuffers = NULL;
glXGetProcAddressARBFunc _glXGetProcAddressARB = NULL;
#endif
//--------------------------------------------------------------------------
void VeInitOpenGL()
{
	VE_ASSERT(!g_pkOpenGL);
	g_pkOpenGL = VE_NEW VeSharedLib(OPENGL_LIB_NAME);
	g_pkOpenGL->Load();

#	ifdef VE_GLX
	_glXQueryExtension = (glXQueryExtensionFunc)g_pkOpenGL->GetProc("glXQueryExtension");
	VE_ASSERT(_glXQueryExtension);
	_glXChooseVisual = (glXChooseVisualFunc)g_pkOpenGL->GetProc("glXChooseVisual");
	VE_ASSERT(_glXChooseVisual);
	_glXCreateContext = (glXCreateContextFunc)g_pkOpenGL->GetProc("glXCreateContext");
	VE_ASSERT(_glXCreateContext);
	_glXMakeCurrent = (glXMakeCurrentFunc)g_pkOpenGL->GetProc("glXMakeCurrent");
	VE_ASSERT(_glXMakeCurrent);
	_glXSwapBuffers = (glXSwapBuffersFunc)g_pkOpenGL->GetProc("glXSwapBuffers");
	VE_ASSERT(_glXSwapBuffers);
	_glXGetProcAddressARB = (glXGetProcAddressARBFunc)g_pkOpenGL->GetProc("glXGetProcAddressARB");
	VE_ASSERT(_glXGetProcAddressARB);
#	endif
}
//--------------------------------------------------------------------------
void VeTermOpenGL()
{
#	ifdef VE_GLX
	_glXQueryExtension = NULL;
	_glXChooseVisual = NULL;
	_glXCreateContext = NULL;
	_glXMakeCurrent = NULL;
	_glXSwapBuffers = NULL;
#	endif
	VE_ASSERT(g_pkOpenGL);
	g_pkOpenGL->Unload();
	VE_SAFE_DELETE(g_pkOpenGL);
}
//--------------------------------------------------------------------------
void VeLoadOpenGL()
{
	glFuncload();
#	ifdef VE_GLX
	glXFuncload();
#	endif
#	ifdef VE_WGL
	wglFuncload();
#	endif
}
//--------------------------------------------------------------------------
void VeUnloadOpenGL()
{
	glFuncUnload();
#	ifdef VE_GLX
	glXFuncUnload();
#	endif
#	ifdef VE_WGL
	wglFuncUnload();
#	endif
}
//--------------------------------------------------------------------------
bool VeIsOpenGLLoaded()
{
	return g_pkOpenGL ? true : false;
}
//--------------------------------------------------------------------------
#ifdef VE_GL
//--------------------------------------------------------------------------
void* glGetFunction(const VeChar8* pcName)
{
#	if defined(VE_WGL)
	return wglGetFunction(pcName);
#	elif defined(VE_GLX)
	return glXGetFunction(pcName);
#	else
	return g_pkOpenGL->GetProc(pcName);
#	endif
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#ifdef VE_WGL
//--------------------------------------------------------------------------
void* wglGetFunction(const VeChar8* pcName)
{
	void* pvRes = g_pkOpenGL->GetProc(pcName);
	if(!pvRes)
	{
		pvRes = wglGetProcAddress(pcName);
	}
	return pvRes;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#ifdef VE_GLX
//--------------------------------------------------------------------------
void* glXGetFunction(const VeChar8* pcName)
{
	void* pvRes = g_pkOpenGL->GetProc(pcName);
	if(!pvRes)
	{
		pvRes = (void*)glXGetProcAddressARB(reinterpret_cast<const GLubyte*>(pcName));
	}
	return pvRes;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
