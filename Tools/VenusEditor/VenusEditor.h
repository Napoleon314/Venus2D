////////////////////////////////////////////////////////////////////////////
//
//  Venus Editor Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VenusEditor.h
//  Version:     v1.00
//  Created:     12/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#if (defined(VE_PLATFORM_WIN) && defined(VE_DYNAMIC_LIB))
#	ifdef VENUSEDITOR_EXPORTS
#		define VENUSEDITOR_API __declspec (dllexport)
#	else
#		define VENUSEDITOR_API __declspec (dllimport)
#	endif
#else
#	define VENUSEDITOR_API
#endif

#ifdef VE_PLATFORM_WIN

#include <Windows.h>

#endif

extern "C"
{

typedef void (*VeEditorFPSFunc)(const char*);
    
typedef void (*VeEditorLogFunc)(const char*);
    
VENUSEDITOR_API void VeEditorInit();

VENUSEDITOR_API void VeEditorTerm();

VENUSEDITOR_API void VeEditorRendererInit();

VENUSEDITOR_API void VeEditorRendererTerm();

#ifdef VE_PLATFORM_WIN

VENUSEDITOR_API void VeEditorInitD3D11(HWND hWnd);

VENUSEDITOR_API void VeEditorTermD3D11();

#endif

VENUSEDITOR_API bool VeEditorHasRenderer();

VENUSEDITOR_API void VeEditorUpdateFrame();

VENUSEDITOR_API void VeEditorResize(int iWidth, int iHeight);

VENUSEDITOR_API void VeEditorSetFPSFunc(VeEditorFPSFunc pfuncSetFPS);

VENUSEDITOR_API void VeEditorSetLogFunc(VeEditorLogFunc pfuncLogger);

}
