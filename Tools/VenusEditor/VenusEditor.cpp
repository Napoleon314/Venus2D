////////////////////////////////////////////////////////////////////////////
//
//  Venus Editor Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VenusEditor.cpp
//  Version:     v1.00
//  Created:     12/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VenusEditor.h"
#undef VE_USER
#include <VeMainPCH.h>

//--------------------------------------------------------------------------
VeEditorApplication* g_pkEditor = NULL;
VeEditorLoggerPtr g_spLogger = NULL;
VeEditorLogFunc g_pfuncLog = NULL;
//--------------------------------------------------------------------------
void VeEditorInit()
{
    g_pkEditor = VE_NEW VeEditorApplication();
    VeGlobalStringTableA::Create();
    VE_NEW VeAllocatorManager();
    VE_NEW VeStringParser();
    VE_NEW VeTime();
    g_spLogger = VE_NEW VeEditorLogger(g_pfuncLog);
    VeLogger::SetLog(VeSmartPointerCast(VeLogger, g_spLogger));
	VE_NEW VeResourceManager();
    VE_NEW VeURL();
    VE_NEW VeInputManager();
    VeRenderer::CreateRenderer(VeRenderer::API_OGL);
}
//--------------------------------------------------------------------------
void VeEditorTerm()
{
    g_spLogger = NULL;
    g_pkEditor = NULL;
    VeApplication::Destory();
    VeRenderer::DestoryRenderer();
    VeInputManager::Destory();
    VeURL::Destory();
    VeResourceManager::Destory();
    VeLogger::SetLog(VeLogger::OUTPUT_MAX);
    VeTime::Destory();
    VeStringParser::Destory();
    VeAllocatorManager::Destory();
    VeGlobalStringTableA::Destory();
#   ifdef VE_MEM_DEBUG
    _VeMemoryExit();
#   endif
    g_pfuncLog = NULL;
}
//--------------------------------------------------------------------------
void VeEditorRendererInit()
{
	VE_ASSERT(g_pRenderer);
	g_pRenderer->InitEditor();
	VE_ASSERT(g_pApplication);
	g_pApplication->Init();
}
//--------------------------------------------------------------------------
void VeEditorRendererTerm()
{
	VE_ASSERT(g_pApplication);
	g_pApplication->Term();
	VE_ASSERT(g_pRenderer);
	g_pRenderer->TermEditor();
}
//--------------------------------------------------------------------------
#ifdef VE_PLATFORM_WIN
//--------------------------------------------------------------------------
void VeEditorInitD3D11(HWND hWnd)
{
	g_pkEditor = VE_NEW VeEditorApplication();
	VeGlobalStringTableA::Create();
	VE_NEW VeAllocatorManager();
	VE_NEW VeStringParser();
	VE_NEW VeTime();
	g_spLogger = VE_NEW VeEditorLogger(g_pfuncLog);
	VeLogger::SetLog(VeSmartPointerCast(VeLogger, g_spLogger));
	VE_NEW VeResourceManager();
	VE_NEW VeURL();
	VE_NEW VeInputManager();
	VeRenderer::CreateRenderer(VeRenderer::API_D3D11);
	g_hInstance = GetModuleHandle(NULL);
	g_hWindow = hWnd;
}
//--------------------------------------------------------------------------
void VeEditorTermD3D11()
{
	g_hInstance = NULL;
	g_hWindow = NULL;
	g_spLogger = NULL;
	g_pkEditor = NULL;
	VeApplication::Destory();
	VeRenderer::DestoryRenderer();
	VeInputManager::Destory();
	VeURL::Destory();
	VeResourceManager::Destory();
	VeLogger::SetLog(VeLogger::OUTPUT_MAX);
	VeTime::Destory();
	VeStringParser::Destory();
	VeAllocatorManager::Destory();
	VeGlobalStringTableA::Destory();
#ifdef VE_MEM_DEBUG
	_VeMemoryExit();
#endif
	g_pfuncLog = NULL;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
bool VeEditorHasRenderer()
{
    return g_pRenderer ? true : false;
}
//--------------------------------------------------------------------------
void VeEditorUpdateFrame()
{
    g_pApplication->Update();
	g_pApplication->Render();
}
//--------------------------------------------------------------------------
void VeEditorResize(int iWidth, int iHeight)
{
    if(g_pRenderer && g_pRenderer->IsInited())
    {
        g_pRenderer->ResizeBuffer(iWidth, iHeight);
        VE_LOG_I("VenusEditor", "OnBufferResized: %dx%d", iWidth, iHeight);
    }
}
//--------------------------------------------------------------------------
void VeEditorSetFPSFunc(VeEditorFPSFunc pfuncSetFPS)
{
    if(g_pkEditor)
    {
        g_pkEditor->SetFPSFunc(pfuncSetFPS);
    }
}
//--------------------------------------------------------------------------
void VeEditorSetLogFunc(VeEditorLogFunc pfuncLogger)
{
    g_pfuncLog = pfuncLogger;
    if(g_spLogger)
    {
        g_spLogger->SetLogFunc(g_pfuncLog);
    }
}
//--------------------------------------------------------------------------
