////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeGlLoader.h
//  Version:     v1.00
//  Created:     14/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VE_ENABLE_GL

void VeInitOpenGL();

void VeTermOpenGL();

void VeLoadOpenGL();

void VeUnloadOpenGL();

bool VeIsOpenGLLoaded();

#ifdef VE_PLATFORM_WIN
#	ifndef APIENTRY
#		define APIENTRY __stdcall
#	endif
#else
#	ifndef APIENTRY
#		define APIENTRY
#	endif
#endif

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef char GLchar;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

extern VeSharedLib* g_pkOpenGL;

#define VE_GL
#ifdef VE_PLATFORM_WIN
#	define VE_WGL
#endif
#ifdef VE_PLATFORM_LINUX
#	define VE_GLX
#endif

#ifdef VE_GL

void* glGetFunction(const VeChar8* pcName);

#endif

#ifdef VE_WGL

void* wglGetFunction(const VeChar8* pcName);

#endif

#ifdef VE_GLX

typedef struct __GLXcontextRec *GLXContext;
typedef XID GLXPixmap;
typedef XID GLXDrawable;
/* GLX 1.3 and later */
typedef struct __GLXFBConfigRec *GLXFBConfig;
typedef XID GLXFBConfigID;
typedef XID GLXContextID;
typedef XID GLXWindow;
typedef XID GLXPbuffer;

typedef XID GLXFBConfigIDSGIX;
typedef struct __GLXFBConfigRec *GLXFBConfigSGIX;
typedef XID GLXPbufferSGIX;

typedef Bool (APIENTRY *glXQueryExtensionFunc)(Display* dpy, int* errorBase, int* eventBase);
extern glXQueryExtensionFunc _glXQueryExtension;
#define glXQueryExtension _glXQueryExtension

typedef XVisualInfo* (APIENTRY *glXChooseVisualFunc)(Display* dpy, int screen, int* attribList);
extern glXChooseVisualFunc _glXChooseVisual;
#define glXChooseVisual _glXChooseVisual

typedef GLXContext (APIENTRY *glXCreateContextFunc)(Display* dpy, XVisualInfo* vis, GLXContext shareList, Bool direct);
extern glXCreateContextFunc _glXCreateContext;
#define glXCreateContext _glXCreateContext

typedef Bool (APIENTRY *glXMakeCurrentFunc)(Display* dpy, GLXDrawable drawable, GLXContext ctx);
extern glXMakeCurrentFunc _glXMakeCurrent;
#define glXMakeCurrent _glXMakeCurrent

typedef void (APIENTRY *glXSwapBuffersFunc)(Display* dpy, GLXDrawable drawable);
extern glXSwapBuffersFunc _glXSwapBuffers;
#define glXSwapBuffers _glXSwapBuffers

typedef void (*__GLXextFuncPtr)(void);
typedef __GLXextFuncPtr (APIENTRY *glXGetProcAddressARBFunc)(const GLubyte* procName);
extern glXGetProcAddressARBFunc _glXGetProcAddressARB;
#define glXGetProcAddressARB _glXGetProcAddressARB

void* glXGetFunction(const VeChar8* pcName);

#endif

#include "gl.h"
#include "glx.h"
#include "wgl.h"

#endif
