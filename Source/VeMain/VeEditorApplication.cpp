////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeEditorApplication.cpp
//  Version:     v1.00
//  Created:     12/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"

//--------------------------------------------------------------------------
VeEditorLogger::VeEditorLogger(LogFunc pfuncLog) : m_pfuncLog(pfuncLog)
{
    
}
//--------------------------------------------------------------------------
void VeEditorLogger::SetLogFunc(LogFunc pfuncLog)
{
    m_pfuncLog = pfuncLog;
}
//--------------------------------------------------------------------------
void VeEditorLogger::AppendLog(VeLogType eType, const VeChar8* pcTag,
	const VeChar8* pcFormat, va_list kArgs)
{
    if(!m_pfuncLog) return;
    
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
    
    i32Pointer += VeSprintf(s_acLogBuffer + i32Pointer,
		VE_LOG_BUFFER_SIZE - i32Pointer, "VE_LOG|TYPE:%s|TAG:%s|LOG:",
		apcLogTypes[eType], pcTag);
    i32Pointer += VeVsprintf(s_acLogBuffer + i32Pointer,
		VE_LOG_BUFFER_SIZE - i32Pointer, pcFormat, kArgs);
    m_pfuncLog(s_acLogBuffer);
}
//--------------------------------------------------------------------------
VeEditorApplication::VeEditorApplication() : m_pfuncSetFPS(NULL)
{
    
}
//--------------------------------------------------------------------------
VeEditorApplication::~VeEditorApplication()
{
    
}
//--------------------------------------------------------------------------
void VeEditorApplication::OnInit()
{
    
}
//--------------------------------------------------------------------------
void VeEditorApplication::OnTerm()
{
    
}
//--------------------------------------------------------------------------
void VeEditorApplication::OnUpdate()
{
    
}
//--------------------------------------------------------------------------
void VeEditorApplication::Update()
{
    g_pTime->Update();
    g_pURL->Update();
    g_pResourceManager->Update();
    g_pInputManager->Update();
    OnUpdate();
    
    if(m_pfuncSetFPS)
    {
		static VeFloat32 s_f32TimeCount(0);
		static VeUInt32 s_u32FrameCount(0);

		s_f32TimeCount += g_pTime->GetDeltaTime();
		++s_u32FrameCount;

		if(s_f32TimeCount > 1.0f)
		{
			static VeChar8 s_acFPS[64];
			VeSprintf(s_acFPS, "FPS:%d", s_u32FrameCount);
			m_pfuncSetFPS(s_acFPS);
			s_f32TimeCount -= floorf(s_f32TimeCount);
			s_u32FrameCount = 0;
		}
    }
}
//--------------------------------------------------------------------------
void VeEditorApplication::Render()
{
    g_pRenderer->Render();
	if(g_pRenderer->GetAPI() == VeRenderer::API_D3D11)
	{
		g_pRenderer->Present();
	}
}
//--------------------------------------------------------------------------
void VeEditorApplication::SetFPSFunc(FPSFunc pfuncSetFPS)
{
    VE_ASSERT(pfuncSetFPS);
    m_pfuncSetFPS = pfuncSetFPS;
}
//--------------------------------------------------------------------------
