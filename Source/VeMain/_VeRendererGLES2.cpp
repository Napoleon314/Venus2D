////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRendererGLES2.cpp
//  Version:     v1.00
//  Created:     21/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeRendererGLES2.h"

#if defined(VE_PLATFORM_MOBILE_SIM)
#	include "MobileSim/_VeMobileSim.h"
#elif defined(VE_PLATFORM_ANDROID)
#	include "Android/_VeAndroid.h"
#endif

//--------------------------------------------------------------------------
#ifdef VE_ENABLE_GLES2
//--------------------------------------------------------------------------
#if defined(VE_PLATFORM_MOBILE_SIM) || defined(VE_PLATFORM_ANDROID)
//--------------------------------------------------------------------------
bool VeTestEGLError(const VeChar8* pcLocation)
{
	EGLint iErr = eglGetError();
	if(iErr != EGL_SUCCESS)
	{
		VeDebugOutput("%s failed (%d).\n", pcLocation, iErr);
		return false;
	}
	return true;
}
//--------------------------------------------------------------------------
#elif defined(VE_PLATFORM_IOS)
//--------------------------------------------------------------------------
void VeRenderbufferStorageLayer();
//--------------------------------------------------------------------------
void VeGLESPresent();
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
void VeRendererGLES2::Create()
{
    if(!GetSingletonPtr())
	{
		VE_NEW VeRendererGLES2();
	}
}
//--------------------------------------------------------------------------
VeRendererGLES2::VeRendererGLES2()
#if defined(VE_PLATFORM_MOBILE_SIM)
	: m_hDeviceContext(NULL)
	, m_eglDisplay(NULL)
	, m_eglConfig(NULL)
	, m_eglSurface(NULL)
	, m_eglContext(NULL)
#elif defined(VE_PLATFORM_ANDROID)
	: m_eglDisplay(NULL)
	, m_eglConfig(NULL)
	, m_eglSurface(NULL)
	, m_eglContext(NULL)
#elif defined(VE_PLATFORM_IOS)
	: m_u32BackFrameBuffer(0)
	, m_u32BackRenderBuffer(0)
#endif
	, m_pvQuadBuffer(NULL)
	, m_u32QuadPointer(0)
{
	m_pvQuadBuffer = VeMalloc(VE_GLES2_QUAD_BUFFER_SIZE);
	m_i32MaxAnisotropy = 0;
	m_bSupportDepthTexute = false;
	m_bSupportAnisotropic = false;
	m_bSupportMSAA = false;
	m_u8MaxAASamples = 1;
	m_bApiInit = false;
	GLCacheInit();
}
//--------------------------------------------------------------------------
VeRendererGLES2::~VeRendererGLES2()
{
	VeFree(m_pvQuadBuffer);
	m_pvQuadBuffer = NULL;
}
//--------------------------------------------------------------------------
VeRenderer::API VeRendererGLES2::GetAPI()
{
	return API_OGLES2;
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererGLES2::CheckCapability(Capability eCap)
{
	switch(eCap)
	{
	case CAP_DEPTH_TEX:
		return m_bSupportDepthTexute ? VE_TRUE : VE_FALSE;
	case CAP_ANISOTROPIC:
		return m_bSupportAnisotropic ? VE_TRUE : VE_FALSE;
	case CAP_MULTI_SAMPLE:
		return m_bSupportMSAA ? VE_TRUE : VE_FALSE;
	case CAP_DRAW_INSTANCE:
		return VE_FALSE;
	default:
		return 0;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Init()
{
	if(m_bInited) return;

	ApiInit();
	
	m_bInited = true;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Term()
{
	if(!m_bInited) return;

	for(VeVector<VeRenderObjectPtr>::iterator it = m_kObjectArray.Begin(); it != m_kObjectArray.End(); ++it)
	{
		(*it)->OnClear();
	}
	m_kObjectArray.Clear();
	for(VeUInt32 i(0); i < VeRenderObject::TYPE_MAX; ++i)
	{
		m_akObjectMap[i].Clear();
	}
	for(VeVector<VeRenderProcessPtr>::iterator it = m_kProcessArray.Begin(); it != m_kProcessArray.End(); ++it)
	{
		(*it)->OnDel();
	}
	m_kProcessMap.Clear();
	m_kProcessArray.Clear();
	m_kNodeDataMap.Clear();
	m_kNodeDataArray.Clear();

	ApiTerm();

	m_bInited = false;
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeRendererGLES2::AddRestoreDelegate(RestoreDelegate& kDelegate)
{
	m_kRestoreEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Lost()
{
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::VERTEX_SHADER);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeShaderResource, kVec[i])->OnLost();
		}
	}
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::PIXEL_SHADER);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeShaderResource, kVec[i])->OnLost();
		}
	}
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::TEXTURE);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeTextureResource, kVec[i])->OnLost();
		}
	}
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::FONT);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeTextureResource, kVec[i])->OnLost();
		}
	}
	for(VeVector<VeRenderObjectPtr>::iterator it = m_kObjectArray.Begin(); it != m_kObjectArray.End(); ++it)
	{
		(*it)->OnLost();
	}
	ApiTerm();
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Restore()
{
	ApiInit();
	for(VeVector<VeRenderObjectPtr>::iterator it = m_kObjectArray.Begin(); it != m_kObjectArray.End(); ++it)
	{
		(*it)->OnRestore();
	}
	for(VeVector<RenderTarget>::iterator it = m_kRenderTargetArray.Begin(); it != m_kRenderTargetArray.End(); ++it)
	{
		VeMemoryOStream kStream;
		kStream << VeUInt16(it->m_u16Width);
		kStream << VeUInt16(it->m_u16Height);
		kStream << VeUInt16(1);
		kStream << VeUInt16(1);
		kStream << VeUInt8(it->m_eFormat);
		kStream << VeUInt8(1);
		kStream << VeUInt8(0);
		kStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
		kStream << VeUInt8(VeRenderer::BIND_SHADER_RESOURCE | VeRenderer::BIND_RENDER_TARGET);
		kStream << VeUInt8(0);
		kStream << VeUInt16(0);
		kStream << VeUInt16(1);
		kStream << VeUInt16(0);
		kStream >> (*it->m_spTex);
	}
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::VERTEX_SHADER);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeShaderResource, kVec[i])->OnRestore();
		}
	}
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::PIXEL_SHADER);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeShaderResource, kVec[i])->OnRestore();
		}
	}
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::TEXTURE);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeTextureResource, kVec[i])->OnRestore();
		}
	}
	{
		VeResourceManager::ResourceVec& kVec = g_pResourceManager->GetResourceList(VeResource::FONT);
		for(VeUInt32 i(0); i < kVec.Size(); ++i)
		{
			VeSmartPointerCast(VeTextureResource, kVec[i])->OnRestore();
		}
	}
	m_kRestoreEvent.Callback();
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
void VeRendererGLES2::ApiInit()
{
	if(m_bApiInit) return;
	GLCacheInit();
#if defined(VE_PLATFORM_MOBILE_SIM)

	m_hDeviceContext = GetDC(((VeMobileSim*)g_pDevice)->GetWindowHandle());
	m_eglDisplay = eglGetDisplay(m_hDeviceContext);
	if(m_eglDisplay == EGL_NO_DISPLAY) m_eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
	EGLint iMajorVersion, iMinorVersion;
	VE_ASSERT_EQ(eglInitialize(m_eglDisplay, &iMajorVersion, &iMinorVersion), VE_TRUE);
	eglBindAPI(EGL_OPENGL_ES_API);
	VE_ASSERT_EQ(VeTestEGLError("eglBindAPI"), VE_TRUE);
	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,				0,
		EGL_RED_SIZE,			8,
		EGL_GREEN_SIZE,			8,
		EGL_BLUE_SIZE,			8,
		EGL_ALPHA_SIZE,			8,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		EGL_DEPTH_SIZE,			EGL_DONT_CARE,
		EGL_NONE
	};
	VeInt32 i32Configs;
	VE_ASSERT_EQ(eglChooseConfig(m_eglDisplay, pi32ConfigAttribs, &m_eglConfig, 1, &i32Configs) || (i32Configs != 1), VE_TRUE);
	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, ((VeMobileSim*)g_pDevice)->GetWindowHandle(), NULL);
	if(m_eglConfig == EGL_NO_SURFACE)
	{
		eglGetError();
		m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, NULL, NULL);
	}
	VE_ASSERT_EQ(VeTestEGLError("eglCreateWindowSurface"), VE_TRUE);
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, NULL, ai32ContextAttribs);
	VE_ASSERT_EQ(VeTestEGLError("eglCreateContext"), VE_TRUE);
	eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
	VE_ASSERT_EQ(VeTestEGLError("eglMakeCurrent"), VE_TRUE);

#elif defined(VE_PLATFORM_ANDROID)

	m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	VE_ASSERT_EQ(eglInitialize(m_eglDisplay, NULL, NULL), VE_TRUE);
	eglBindAPI(EGL_OPENGL_ES_API);
	VE_ASSERT_EQ(VeTestEGLError("eglBindAPI"), VE_TRUE);

	const EGLint pi32ConfigAttribs[] =
	{
		EGL_RED_SIZE,			8,
		EGL_GREEN_SIZE,			8,
		EGL_BLUE_SIZE,			8,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_DEPTH_SIZE,			EGL_DONT_CARE,
		EGL_NONE
	};

	VeInt32 i32Configs;
	VE_ASSERT_EQ(eglChooseConfig(m_eglDisplay, pi32ConfigAttribs, &m_eglConfig, 1, &i32Configs), VE_TRUE);
	VE_ASSERT(i32Configs == 1);

	VeInt32 i32VisualID;
	eglGetConfigAttrib(m_eglDisplay, m_eglConfig, EGL_NATIVE_VISUAL_ID, &i32VisualID);
	ANativeWindow_setBuffersGeometry(((VeAndroid*)g_pDevice)->GetWindow(), 0, 0, i32VisualID);

	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, ((VeAndroid*)g_pDevice)->GetWindow(), NULL);
	VE_ASSERT_EQ(VeTestEGLError("eglCreateWindowSurface"), VE_TRUE);

	VeInt32 ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, NULL, ai32ContextAttribs);
	VE_ASSERT_EQ(VeTestEGLError("eglCreateContext"), VE_TRUE);

	eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);

#elif defined(VE_PLATFORM_IOS)

	glGenFramebuffers(1, &m_u32BackFrameBuffer);
	BindFrameBuffer(m_u32BackFrameBuffer);
	glGenRenderbuffers(1, &m_u32BackRenderBuffer);
	BindRenderBuffer(m_u32BackRenderBuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_u32BackRenderBuffer);
	VeRenderbufferStorageLayer();
	VE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

#endif
	GLInitGlobal();
	UpdateBufferSize();
	m_bApiInit = true;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::ApiTerm()
{
	if(!m_bApiInit) return;
	GLTermGlobal();
#if defined(VE_PLATFORM_MOBILE_SIM)

	eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(m_eglDisplay);
	if(m_hDeviceContext) ReleaseDC(((VeMobileSim*)g_pDevice)->GetWindowHandle(), m_hDeviceContext);

#elif defined(VE_PLATFORM_ANDROID)

	eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(m_eglDisplay, m_eglContext);
	eglDestroySurface(m_eglDisplay, m_eglSurface);
	eglTerminate(m_eglDisplay);

	m_eglDisplay = NULL;
	m_eglConfig = NULL;
	m_eglSurface = NULL;
	m_eglContext = NULL;

#elif defined(VE_PLATFORM_IOS)

	if(m_u32BackFrameBuffer)
	{
		glDeleteRenderbuffers(1, &m_u32BackRenderBuffer);
		glDeleteFramebuffers(1, &m_u32BackFrameBuffer);
		m_u32BackRenderBuffer = 0;
		m_u32BackFrameBuffer = 0;
	}

#endif
	m_bApiInit = false;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Render()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Present()
{
#	if defined(VE_PLATFORM_MOBILE_SIM)
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
#	elif defined(VE_PLATFORM_ANDROID)
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
#   elif defined(VE_PLATFORM_IOS)
    BindRenderBuffer(m_u32BackRenderBuffer);
	VeGLESPresent();
#	endif
	m_u32QuadPointer = 0;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height)
{
	g_pApplication->OnBufferResized(u32Width, u32Height);
}
//--------------------------------------------------------------------------
#ifdef VE_PLATFORM_MOBILE_SIM
//--------------------------------------------------------------------------
void VeRendererGLES2::ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height)
{
	/*VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
	if(kResolution.m_u32Width != u32Width || kResolution.m_u32Height != u32Height)
	{
		g_pStartConfig->SetResolution(u32Width, u32Height);
		kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
		DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
		AdjustWindowRect(&kRect, dwStyle, FALSE);
		VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
		VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
		VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
		i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
		i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
		SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
			SWP_NOZORDER | SWP_NOACTIVATE);
		Lost();
		Restore();
		UpdateBufferSize();
	}*/
}
//--------------------------------------------------------------------------
#else
//--------------------------------------------------------------------------
void VeRendererGLES2::OnBufferRestorage()
{
#   if defined(VE_PLATFORM_IOS)
	BindFrameBuffer(m_u32BackFrameBuffer);
	BindRenderBuffer(m_u32BackRenderBuffer);
	VeRenderbufferStorageLayer();
	VE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
#   endif
	UpdateBufferSize();
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
void VeRendererGLES2::GetMatrixPerspectiveFov(VeFloat32* pf32OutMat4x4,
	VeFloat32 fov, VeFloat32 znear, VeFloat32 zfar)
{
	VeMatrixPerspectiveFovLH_GL(pf32OutMat4x4, fov,
		GetHeightF() * GetInvWidthF(), znear, zfar);
}
//--------------------------------------------------------------------------
const VeChar8* VeRendererGLES2::GetShaderName()
{
	return "glsl_es";
}
//--------------------------------------------------------------------------
const VeChar8* VeRendererGLES2::GetShaderProfile()
{
	return "1_0";
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererGLES2::GetMultisampleLevelCount()
{
	return m_bSupportMSAA ? 1 : 0;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::EnumMultisampleLevel(VeUInt32 u32Index, VeUInt32& u32Count, VeUInt32& u32Quality)
{
	VE_ASSERT(u32Index < GetMultisampleLevelCount());
	u32Count = m_u8MaxAASamples;
	u32Quality = 0;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateVertexShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROVertexShaderPtr* pspShader)
{
	VeROVertexShaderPtr spShader;
	GetRenderObject(pcName, spShader);
	if(!spShader)
	{
		spShader = VE_NEW VeROVertexShaderGLES2(pcName);
		AddObject(spShader);
	}
	kStream >> (*spShader);
	if(pspShader)
	{
		*pspShader = spShader;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreatePixelShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROPixelShaderPtr* pspShader)
{
	VeROPixelShaderPtr spShader;
	GetRenderObject(pcName, spShader);
	if(!spShader)
	{
		spShader = VE_NEW VeROPixelShaderGLES2(pcName);
		AddObject(spShader);
	}
	kStream >> (*spShader);
	if(pspShader)
	{
		*pspShader = spShader;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateBlendState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBlendStatePtr* pspBlendState)
{
	VeROBlendStatePtr spBlendState;
	GetRenderObject(pcName, spBlendState);
	if(!spBlendState)
	{
		spBlendState = VE_NEW VeROBlendStateGLES2(pcName);
		AddObject(spBlendState);
	}
	kStream >> (*spBlendState);
	if(pspBlendState)
	{
		*pspBlendState = spBlendState;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateDepthStencilState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRODepthStencilStatePtr* pspDepthStencilState)
{
	VeRODepthStencilStatePtr spDepthStencilState;
	GetRenderObject(pcName, spDepthStencilState);
	if(!spDepthStencilState)
	{
		spDepthStencilState = VE_NEW VeRODepthStencilStateGLES2(pcName);
		AddObject(spDepthStencilState);
	}
	kStream >> (*spDepthStencilState);
	if(pspDepthStencilState)
	{
		*pspDepthStencilState = spDepthStencilState;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateInputLayout(const VeChar8* pcName, VeBinaryIStream& kStream, VeROInputLayoutPtr* pspLayout)
{
	VeROInputLayoutPtr spLayout;
	GetRenderObject(pcName, spLayout);
	if(!spLayout)
	{
		spLayout = VE_NEW VeROInputLayoutGLES2(pcName);
		AddObject(spLayout);
	}
	kStream >> (*spLayout);
	if(pspLayout)
	{
		*pspLayout = spLayout;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateRasterizerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRORasterizeStatePtr* pspRasterizeState)
{
	VeRORasterizeStatePtr spRSState;
	GetRenderObject(pcName, spRSState);
	if(!spRSState)
	{
		spRSState = VE_NEW VeRORasterizeStateGLES2(pcName);
		AddObject(spRSState);
	}
	kStream >> (*spRSState);
	if(pspRasterizeState)
	{
		*pspRasterizeState = spRSState;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateBuffer(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBufferPtr* pspBuffer)
{
	VeROBufferPtr spBuffer;
	GetRenderObject(pcName, spBuffer);
	if(!spBuffer)
	{
		spBuffer = VE_NEW VeROBufferGLES2(pcName);
		AddObject(spBuffer);
	}
	kStream >> (*spBuffer);
	if(pspBuffer)
	{
		*pspBuffer = spBuffer;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateSamplerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROSamplerStatePtr* pspSamplerState)
{
	VeROSamplerStatePtr spSampler;
	GetRenderObject(pcName, spSampler);
	if(!spSampler)
	{
		spSampler = VE_NEW VeROSamplerStateGLES2(pcName);
		AddObject(spSampler);
	}
	kStream >> (*spSampler);
	if(pspSamplerState)
	{
		*pspSamplerState = spSampler;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateTexture2D(const VeChar8* pcName, VeBinaryIStream& kStream, VeROTexture2DPtr* pspTexture)
{
	VeROTexture2DPtr spTexture;
	GetRenderObject(pcName, spTexture);
	if(!spTexture)
	{
		spTexture = VE_NEW VeROTexture2DGLES2(pcName);
		AddObject(spTexture);
	}
	kStream >> (*spTexture);
	if(pspTexture)
	{
		*pspTexture = spTexture;
	}
}
//--------------------------------------------------------------------------
bool VeRendererGLES2::CreateProcessByType(VeRenderProcess::Type eType, const VeChar8* pcName, VeBinaryIStream& kStream, VeRenderProcessPtr* pspProcess)
{
	switch(eType)
	{
	case VeRenderProcess::TYPE_MSAA_RESOLVE:
#		if defined(VE_PLATFORM_IOS)
		{
			VeMSAAResolveGLES2APPLEPtr spMSAAProcess = VE_NEW VeMSAAResolveGLES2APPLE(pcName);
			bool bRes = spMSAAProcess->Update(kStream);
            if(bRes)
            {
                AddProcess(VeSmartPointerCast(VeMSAAResolveGLES2APPLE, spMSAAProcess));
                if(pspProcess)
                {
                    *pspProcess = VeSmartPointerCast(VeMSAAResolveGLES2APPLE, spMSAAProcess);
                }
            }
			
			return bRes;
		}
#		else
		break;
#		endif
	default:
		break;
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeRendererGLES2::MapRes(const VeRenderObjectPtr& spObject,
	VeUInt32 u32SubResource, Map eType, VE_BOOL bSync,
	MappedSubresource* pkMapped)
{
	VE_ASSERT(spObject && pkMapped);
	switch(spObject->GetType())
	{
	case VeRenderObject::TYPE_BUFFER:
		if(eType != MAP_WRITE_NO_OVERWRITE && u32SubResource == 0 && bSync)
		{
			VeROBufferGLES2* pkBuffer = VeDynamicCast(VeROBufferGLES2, VeSmartPointerCast(VeRenderObject, spObject));
			VE_ASSERT(pkBuffer->m_pvBuffer);
			pkMapped->m_pvData = pkBuffer->m_pvBuffer;
			pkMapped->m_u32RowPitch = pkBuffer->m_u32ByteWidth;
			pkMapped->m_u32DepthPitch = pkBuffer->m_u32ByteWidth;
			return true;
		}
		break;
	default:
		break;
	}
	return VeRenderer::MapRes(spObject, u32SubResource, eType, bSync,
		pkMapped);
}
//--------------------------------------------------------------------------
void VeRendererGLES2::UnMapRes(const VeRenderObjectPtr& spObject,
	VeUInt32 u32SubResource, MapWriteRange kRange)
{
	VE_ASSERT(spObject);
	switch(spObject->GetType())
	{
	case VeRenderObject::TYPE_BUFFER:
		if(u32SubResource == 0)
		{
			VeROBufferGLES2* pkBuffer = VeDynamicCast(VeROBufferGLES2, VeSmartPointerCast(VeRenderObject, spObject));
			if(pkBuffer->GetBindFlag() != VeRenderer::BIND_CONSTANT_BUFFER)
			{
				((VeRendererGLES2*)g_pRenderer)->BindBuffer(pkBuffer->m_u32Target, pkBuffer->m_u32Buffer);
				glBufferSubData(pkBuffer->m_u32Target, kRange.m_u32Offset, kRange.m_u32Size, (VeByte*)pkBuffer->m_pvBuffer + kRange.m_u32Offset);
			}
		}
		break;
	default:
		break;
	}
	VE_ASSERT(glGetError() == GL_NO_ERROR);
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Render(VeRenderNode* pkNode)
{
	VE_ASSERT(pkNode);
	if(pkNode->m_pkRenderable)
	{
		pkNode->m_pkRenderable->BeforeRender();
	}
	if(pkNode->m_spData)
	{
		VeRefList<VeRenderTick*>& kTickList = pkNode->m_spData->m_kTickList;
		kTickList.BeginIterator();
		while(!kTickList.IsEnd())
		{
			VeRenderTick* pkTick = kTickList.GetIterNode()->m_tContent;
			kTickList.Next();
			PushTick(pkTick);
		}

		VeRefList<VeRenderCall*>& kCallList = pkNode->m_spData->m_kCallList;
		if(kCallList.Size())
		{
			bool bNeedFlush(true);
			FlushRenderTarget();
			kCallList.BeginIterator();
			while(!kCallList.IsEnd())
			{
				VeRenderCall* pkCall = kCallList.GetIterNode()->m_tContent;
				kCallList.Next();
				if(bNeedFlush && pkCall->GetType())
				{
					FlushStates();
					bNeedFlush = false;
				}
				Call(pkCall);
			}
		}

		pkNode->m_kRenderChildren.BeginIterator();
		while(!pkNode->m_kRenderChildren.IsEnd())
		{
			VeRenderNode* pkNodeIter = pkNode->m_kRenderChildren.GetIterNode()->m_tContent;
			pkNode->m_kRenderChildren.Next();
			Render(pkNodeIter);
			pkNodeIter->Detach();
		}

		kTickList.BeginIterator();
		while(!kTickList.IsEnd())
		{
			VeRenderTick* pkTick = kTickList.GetIterNode()->m_tContent;
			kTickList.Next();
			PopTick(pkTick);
		}
	}
	else
	{
		pkNode->m_kRenderChildren.BeginIterator();
		while(!pkNode->m_kRenderChildren.IsEnd())
		{
			VeRenderNode* pkNodeIter = pkNode->m_kRenderChildren.GetIterNode()->m_tContent;
			pkNode->m_kRenderChildren.Next();
			Render(pkNodeIter);
			pkNodeIter->Detach();
		}
	}
	VE_ASSERT(pkNode->m_kRenderChildren.Empty());
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Process(const VeRenderProcessPtr& spProcess)
{
	VE_ASSERT(spProcess);
	switch(spProcess->GetType())
	{
	case VeRenderProcess::TYPE_MSAA_RESOLVE:
#		if defined(VE_PLATFORM_IOS)
		{
			VeMSAAResolveGLES2APPLE* pkProcess = (VeMSAAResolveGLES2APPLE*)(VeRenderProcess*)spProcess;
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, pkProcess->m_u32DrawBuffer);
            glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, pkProcess->m_u32ReadBuffer);
            glResolveMultisampleFramebufferAPPLE();
		}
#		endif
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::PushTick(VeRenderTick* pkTick)
{
	VE_ASSERT(pkTick);
	switch(pkTick->GetType())
	{
	case VeRenderTick::IA_INDEX_BUFFER:
		m_kIndexBufferStack.PushBack((VeROBufferGLES2*)(VeROBuffer*)(((VeIAIndexBuffer*)pkTick)->m_spBuffer));
		VE_ASSERT((((VeIAIndexBuffer*)pkTick)->m_u32Format) == VeRenderer::FMT_R16_UINT || (!(((VeIAIndexBuffer*)pkTick)->m_spBuffer)));
		break;
	case VeRenderTick::IA_INPUT_LAYOUT:
		m_kInputLayoutStack.PushBack((VeROInputLayoutGLES2*)(VeROInputLayout*)(((VeIAInputLayout*)pkTick)->m_spInputLayout));
		break;
	case VeRenderTick::IA_PRIMITIVE_TOPOLOGY:
		m_kTopologyStack.PushBack(GetGLTopology(((VeIAPrimitiveTopology*)pkTick)->m_eTopology));
		break;
	case VeRenderTick::IA_VERTEX_BUFFER:
		{
			VeIAVertexBuffer* pkBuffer = (VeIAVertexBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_VERTEX_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			VeVector<VertexBufferForSet>& kStack = m_akVertexBufferStack[u32Slot];
			kStack.Resize(kStack.Size() + 1);
			kStack.Back().m_pkBuffer = (VeROBufferGLES2*)(VeROBuffer*)(pkBuffer->m_spBuffer);
			kStack.Back().m_u32Stride = pkBuffer->m_u32Stride;
			kStack.Back().m_u32Offset = pkBuffer->m_u32Offset;
			m_u32VertexBufferChangeMin = VE_MIN(m_u32VertexBufferChangeMin, u32Slot);
			m_u32VertexBufferChangeMax = (m_u32VertexBufferChangeMax == VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32VertexBufferChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::VS_CONSTANT_BUFFER:
		{
			VeVSCBuffer* pkBuffer = (VeVSCBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_CONSTANT_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			VE_ASSERT(u32Slot < VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
			VeVector<VeROBufferGLES2*>& kStack = m_akVSCBufferStack[u32Slot];
			kStack.PushBack((VeROBufferGLES2*)(VeROBuffer*)(pkBuffer->m_spBuffer));
		}
		break;
	case VeRenderTick::VS_SAMPLER:
		break;
	case VeRenderTick::VS_SHADER:
		m_kVertexShaderStack.PushBack((VeROVertexShaderGLES2*)(VeROVertexShader*)(((VeVSShader*)pkTick)->m_spShader));
		break;
	case VeRenderTick::VS_SHADER_RESOURCE:
		break;
	case VeRenderTick::HS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::HS_SAMPLER:
		break;
	case VeRenderTick::HS_SHADER:
		break;
	case VeRenderTick::HS_SHADER_RESOURCE:
		break;
	case VeRenderTick::DS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::DS_SAMPLER:
		break;
	case VeRenderTick::DS_SHADER:
		break;
	case VeRenderTick::DS_SHADER_RESOURCE:
		break;
	case VeRenderTick::GS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::GS_SAMPLER:
		break;
	case VeRenderTick::GS_SHADER:
		break;
	case VeRenderTick::GS_SHADER_RESOURCE:
		break;
	case VeRenderTick::SO_TARGET:
		break;
	case VeRenderTick::RS_SCISSOR_RECT:
		{
			VeRSScissorRectTick* pkScissorTick = ((VeRSScissorRectTick*)pkTick);
			VE_ASSERT(pkScissorTick->m_u32Slot == 0);
			m_kScissorRectStack.Resize(m_kScissorRectStack.Size() + 1);
			m_kScissorRectStack.Back().x = pkScissorTick->m_i16Left;
			m_kScissorRectStack.Back().y = pkScissorTick->m_i16Top;
			m_kScissorRectStack.Back().w = pkScissorTick->m_i16Width;
			m_kScissorRectStack.Back().h = pkScissorTick->m_i16Height;
		}
		break;
	case VeRenderTick::RS_STATE:
		{
			VeRSState* pkRSStateTick = ((VeRSState*)pkTick);
			if(pkRSStateTick->m_spState)
			{
				m_kRasterizeStateStack.PushBack((VeRORasterizeStateGLES2*)(VeRORasterizeState*)(pkRSStateTick->m_spState));
			}
			else
			{
				m_kRasterizeStateStack.PushBack(NULL);
			}
		}
		break;
	case VeRenderTick::RS_VIEWPORT:
		{
			VeRSViewportTick* pkViewportTick = ((VeRSViewportTick*)pkTick);
			VE_ASSERT(pkViewportTick->m_u32Slot == 0);
			m_kViewportStack.PushBack(pkViewportTick->m_kViewport);
		}
		break;
	case VeRenderTick::PS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::PS_SAMPLER:
		{
			VePSSampler* pkSampler = (VePSSampler*)pkTick;
			VeUInt32 u32Slot = pkSampler->m_u32Slot;
			m_akPSSamplerStack[u32Slot].PushBack((VeROSamplerStateGLES2*)(VeROSamplerState*)(pkSampler->m_spSampler));
		}
		break;
	case VeRenderTick::PS_SHADER:
		m_kPixelShaderStack.PushBack((VeROPixelShaderGLES2*)(VeROPixelShader*)(((VePSShader*)pkTick)->m_spShader));
		break;
	case VeRenderTick::PS_SHADER_RESOURCE:
		{
			VePSShaderResource* pkShaderResource = (VePSShaderResource*)pkTick;
			VeUInt32 u32Slot = pkShaderResource->m_u32Slot;
			m_akPSShaderResourceViewStack[u32Slot].PushBack((VeROShaderResourceViewGLES2*)(VeROShaderResourceView*)(pkShaderResource->m_spShaderResourceView));
		}
		break;
	case VeRenderTick::OM_BLEND_STATE:
		{
			VeOMBlendStateTick* pkBlendStateTick = (VeOMBlendStateTick*)pkTick;
			m_kBlendStateStack.Resize(m_kBlendStateStack.Size() + 1);
			m_kBlendStateStack.Back().m_pkBlendState = pkBlendStateTick->m_spBlendState ? (VeROBlendStateGLES2*)(VeROBlendState*)(pkBlendStateTick->m_spBlendState) : NULL;
			VeCrazyCopy(&(m_kBlendStateStack.Back().m_kFactor), pkBlendStateTick->m_af32Factor, sizeof(m_kBlendStateStack.Back().m_kFactor));
			m_bBlendStateChange = VE_TRUE;
		}
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_STATE:
		{
			VeOMDepthStencilStateTick* pkDepthStencilStateTick = (VeOMDepthStencilStateTick*)pkTick;
			m_kDepthStencilStateStack.Resize(m_kDepthStencilStateStack.Size() + 1);
			m_kDepthStencilStateStack.Back().m_pkDepthStencilState = pkDepthStencilStateTick->m_spDepthStencilState ? (VeRODepthStencilStateGLES2*)(VeRODepthStencilState*)(pkDepthStencilStateTick->m_spDepthStencilState) : NULL;
			m_kDepthStencilStateStack.Back().m_u32StencilRef = pkDepthStencilStateTick->m_u32StencilRef;
			m_bDepthStencilStateChange = VE_TRUE;
		}
		break;
	case VeRenderTick::OM_RENDER_TARGET_VIEW:
		{
			VE_ASSERT(((VeOMRenderTargetViewTick*)pkTick)->m_u32Slot == 0);
			m_kRenderTargetViewStack.PushBack((VeRORenderTargetViewGLES2*)(VeRORenderTargetView*)(((VeOMRenderTargetViewTick*)pkTick)->m_spRenderTarget));
		}
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_VIEW:
		m_kDepthStencilViewStack.PushBack((VeRODepthStencilViewGLES2*)(VeRODepthStencilView*)(((VeOMDepthStencilViewTick*)pkTick)->m_spDepthStencil));
		break;
	case VeRenderTick::OM_UNORDERED_ACCESS_VIEW:
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::PopTick(VeRenderTick* pkTick)
{
	VE_ASSERT(pkTick);
	switch(pkTick->GetType())
	{
	case VeRenderTick::IA_INDEX_BUFFER:
		m_kIndexBufferStack.PopBack();
		break;
	case VeRenderTick::IA_INPUT_LAYOUT:
		m_kInputLayoutStack.PopBack();
		break;
	case VeRenderTick::IA_PRIMITIVE_TOPOLOGY:
		m_kTopologyStack.PopBack();
		break;
	case VeRenderTick::IA_VERTEX_BUFFER:
		{
			VeIAVertexBuffer* pkBuffer = (VeIAVertexBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_VERTEX_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			m_akVertexBufferStack[u32Slot].PopBack();
			m_u32VertexBufferChangeMin = VE_MIN(m_u32VertexBufferChangeMin, u32Slot);
			m_u32VertexBufferChangeMax = (m_u32VertexBufferChangeMax == VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32VertexBufferChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::VS_CONSTANT_BUFFER:
		{
			VeVSCBuffer* pkBuffer = (VeVSCBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_CONSTANT_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			VE_ASSERT(u32Slot < VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT);
			m_akVSCBufferStack[u32Slot].PopBack();
		}
		break;
	case VeRenderTick::VS_SAMPLER:
		break;
	case VeRenderTick::VS_SHADER:
		m_kVertexShaderStack.PopBack();
		break;
	case VeRenderTick::VS_SHADER_RESOURCE:
		break;
	case VeRenderTick::HS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::HS_SAMPLER:
		break;
	case VeRenderTick::HS_SHADER:
		break;
	case VeRenderTick::HS_SHADER_RESOURCE:
		break;
	case VeRenderTick::DS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::DS_SAMPLER:
		break;
	case VeRenderTick::DS_SHADER:
		break;
	case VeRenderTick::DS_SHADER_RESOURCE:
		break;
	case VeRenderTick::GS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::GS_SAMPLER:
		break;
	case VeRenderTick::GS_SHADER:
		break;
	case VeRenderTick::GS_SHADER_RESOURCE:
		break;
	case VeRenderTick::SO_TARGET:
		break;
	case VeRenderTick::RS_SCISSOR_RECT:
		m_kScissorRectStack.PopBack();
		break;
	case VeRenderTick::RS_STATE:
		m_kRasterizeStateStack.PopBack();
		break;
	case VeRenderTick::RS_VIEWPORT:
		m_kViewportStack.PopBack();
		break;
	case VeRenderTick::PS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::PS_SAMPLER:
		{
			VePSSampler* pkSampler = (VePSSampler*)pkTick;
			VeUInt32 u32Slot = pkSampler->m_u32Slot;
			m_akPSSamplerStack[u32Slot].PopBack();
		}
		break;
	case VeRenderTick::PS_SHADER:
		m_kPixelShaderStack.PopBack();
		break;
	case VeRenderTick::PS_SHADER_RESOURCE:
		{
			VePSShaderResource* pkShaderResource = (VePSShaderResource*)pkTick;
			VeUInt32 u32Slot = pkShaderResource->m_u32Slot;
			m_akPSShaderResourceViewStack[u32Slot].PopBack();
		}
		break;
	case VeRenderTick::OM_BLEND_STATE:
		m_kBlendStateStack.PopBack();
		m_bBlendStateChange = VE_TRUE;
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_STATE:
		m_kDepthStencilStateStack.PopBack();
		m_bDepthStencilStateChange = VE_TRUE;
		break;
	case VeRenderTick::OM_RENDER_TARGET_VIEW:
		m_kRenderTargetViewStack.PopBack();
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_VIEW:
		m_kDepthStencilViewStack.PopBack();
		break;
	case VeRenderTick::OM_UNORDERED_ACCESS_VIEW:
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::Call(VeRenderCall* pkCall)
{
	switch(pkCall->GetType())
	{
	case VeRenderCall::CLEAR:
		{
			VeClearCall* pkClearCall = (VeClearCall*)pkCall;
			VeUInt32 u32Flag(0);
			if(pkClearCall->m_bClearColor)
			{
				u32Flag |= GL_COLOR_BUFFER_BIT;
				ClearColor(pkClearCall->m_kColorArray[0]);
			}
			if(pkClearCall->m_bClearDepth)
			{
				u32Flag |= GL_DEPTH_BUFFER_BIT;
				ClearDepth(pkClearCall->m_bClearDepth);
			}
			if(pkClearCall->m_bClearStencil)
			{
				u32Flag |= GL_STENCIL_BUFFER_BIT;
				ClearStencil(pkClearCall->m_bClearStencil);
			}
			glClear(u32Flag);
		}
		break;
	case VeRenderCall::DRAW:
		VE_ASSERT(m_kTopologyStack.Size());
		glDrawArrays(m_kTopologyStack.Back(), ((VeDrawCall*)pkCall)->m_kDraw.m_u32StartVertexLocation, ((VeDrawCall*)pkCall)->m_kDraw.m_u32VertexCount);
		break;
	case VeRenderCall::DRAW_INDEXED:
		VE_ASSERT(m_kTopologyStack.Size() && ((VeDrawCall*)pkCall)->m_kDrawIndexed.m_i32BaseVertexLocation == 0);
		glDrawElements(m_kTopologyStack.Back(), ((VeDrawCall*)pkCall)->m_kDrawIndexed.m_u32IndexCount, GL_UNSIGNED_SHORT, (void*)(VeSizeT)((((VeDrawCall*)pkCall)->m_kDrawIndexed.m_u32StartIndexLocation) << 1));
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::FlushRenderTarget()
{
	bool bRenderTargetChanged = false;
	VE_ASSERT(m_kRenderTargetViewStack.Size());
	if(m_kRenderTargetViewStack.Back() != m_pkCurRenderTargetView)
	{
		m_pkCurRenderTargetView = m_kRenderTargetViewStack.Back();
		bRenderTargetChanged = true;
	}
	if((m_kDepthStencilViewStack.Size() ? m_kDepthStencilViewStack.Back() : NULL) != m_pkCurDepthStencilView)
	{
		m_pkCurDepthStencilView = (m_kDepthStencilViewStack.Size() ? m_kDepthStencilViewStack.Back() : NULL);
		bRenderTargetChanged = true;
	}
	if(bRenderTargetChanged)
	{
		m_kCurViewport = VeVector4D::ZERO;
		BindFrameBuffer(GetFrameBuffer(m_pkCurRenderTargetView, m_pkCurDepthStencilView));
		VE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::FlushStates()
{
	bool bProgramUpdate = false;

	if(m_kVertexShaderStack.Size() && m_kVertexShaderStack.Back() != m_pkCurVertexShader)
	{
		m_pkCurVertexShader = m_kVertexShaderStack.Back();
		bProgramUpdate = true;
	}

	if(m_kPixelShaderStack.Size() && m_kPixelShaderStack.Back() != m_pkCurPixelShader)
	{
		m_pkCurPixelShader = m_kPixelShaderStack.Back();
		bProgramUpdate = true;
	}

	if(m_bBlendStateChange && m_kBlendStateStack.Size())
	{
		BlendStateForSet& kLast = m_kBlendStateStack.Back();
		if(kLast.m_pkBlendState)
		{
			if(kLast.m_pkBlendState != m_kCurBlendState.m_pkBlendState)
			{
				m_kCurBlendState.m_pkBlendState = kLast.m_pkBlendState;
				SetAlphaToCoverageEnable(m_kCurBlendState.m_pkBlendState->m_bAlphaToCoverageEnable);
				SetBlendEnable(m_kCurBlendState.m_pkBlendState->m_bBlendEnable);
				SetBlendFunc(m_kCurBlendState.m_pkBlendState->m_u16SrcBlend,
					m_kCurBlendState.m_pkBlendState->m_u16DstBlend,
					m_kCurBlendState.m_pkBlendState->m_u16SrcBlendAlpha,
					m_kCurBlendState.m_pkBlendState->m_u16DstBlendAlpha);
				SetBlendOp(m_kCurBlendState.m_pkBlendState->m_u16BlendOp, m_kCurBlendState.m_pkBlendState->m_u16BlendOpAlpha);
				SetWriteMask(m_kCurBlendState.m_pkBlendState->m_u16WriteMask);
			}
			if(kLast.m_kFactor != m_kCurBlendState.m_kFactor)
			{
				m_kCurBlendState.m_kFactor = kLast.m_kFactor;
				glBlendColor(m_kCurBlendState.m_kFactor.r, m_kCurBlendState.m_kFactor.g, m_kCurBlendState.m_kFactor.b, m_kCurBlendState.m_kFactor.a);
			}
		}
		else
		{
			SetAlphaToCoverageEnable(false);
			SetBlendEnable(false);
			SetWriteMask(VeRenderer::COLOR_WRITE_ENABLE_ALL);
			m_kCurBlendState.m_pkBlendState = NULL;
		}		
		m_bBlendStateChange = VE_FALSE;
	}

	if(m_bDepthStencilStateChange && m_kDepthStencilStateStack.Size())
	{
		VE_ASSERT(m_kDepthStencilStateStack.Size());
		DepthStencilStateForSet& kLast = m_kDepthStencilStateStack.Back();
		if(kLast.m_pkDepthStencilState)
		{
			bool bChange = false;
			if(kLast.m_pkDepthStencilState != m_kCurDepthStencilState.m_pkDepthStencilState)
			{
				m_kCurDepthStencilState.m_pkDepthStencilState = kLast.m_pkDepthStencilState;
				bChange = true;
			}
			if(kLast.m_u32StencilRef != m_kCurDepthStencilState.m_u32StencilRef)
			{
				m_kCurDepthStencilState.m_u32StencilRef = kLast.m_u32StencilRef;
				bChange = true;
			}
			if(bChange)
			{
				VeRODepthStencilStateGLES2* pkObject = m_kCurDepthStencilState.m_pkDepthStencilState;
				SetDepthEnable(pkObject->m_bDepthEnable);
				if(pkObject->m_bDepthEnable)
				{
					SetDepthWrite(pkObject->m_bDepthWrite);
					SetDepthFunc(pkObject->m_u16DepthFunc);
				}
				SetStencilEnable(pkObject->m_bStencilEnable);
				if(pkObject->m_bStencilEnable)
				{
					SetStencilWriteMask(pkObject->m_u8StencilWriteMask);
					SetStencilFunc(pkObject->m_u16FrontFunc, pkObject->m_u16BackFunc, m_kCurDepthStencilState.m_u32StencilRef, pkObject->m_u8StencilReadMask);
					SetStencilFrontOp(pkObject->m_u16FrontFailOp, pkObject->m_u16FrontDepthFailOp, pkObject->m_u16FrontPassOp);
					SetStencilBackOp(pkObject->m_u16BackFailOp, pkObject->m_u16BackDepthFailOp, pkObject->m_u16BackPassOp);
				}
			}
		}
		else
		{
			SetDepthEnable(false);
			SetStencilEnable(false);
			m_kCurDepthStencilState.m_pkDepthStencilState = NULL;
		}
	}

	VeRORasterizeStateGLES2* pkRSState = m_kRasterizeStateStack.Size() ? m_kRasterizeStateStack.Back() : NULL;
	if(pkRSState != m_pkCurRasterizeState)
	{
		if(pkRSState)
		{
			SetCullEnable(pkRSState->m_bCullEnable);
			SetDepthBiasEnable(pkRSState->m_bDepthBiasEnable);
			SetScissorEnable(pkRSState->m_bScissorEnable);
			if(pkRSState->m_bCullEnable)
			{
				SetCullFace(pkRSState->m_u16CullFace);
				SetFrontFace(pkRSState->m_u16FrontFace);
			}
			if(pkRSState->m_bDepthBiasEnable)
			{
				SetPolyOffset(pkRSState->m_f32PolyFactor, pkRSState->m_f32PolyUnits);
			}
		}
		else
		{
			SetCullEnable(true);
			SetDepthBiasEnable(false);
			SetScissorEnable(false);
			SetCullFace(GL_BACK);
			SetFrontFace(GL_CW);
		}
		m_pkCurRasterizeState = pkRSState;
	}

	bool bInputLayoutUpdate = false;
	if(m_kInputLayoutStack.Size() && m_kInputLayoutStack.Back() != m_pkCurInputLayout)
	{
		m_pkCurInputLayout = m_kInputLayoutStack.Back();
		bInputLayoutUpdate = true;
	}

	if(bProgramUpdate || bInputLayoutUpdate)
	{
		static VeChar8 acBuffer[256];
		{
			VeUInt32 u32Pointer(0);
			u32Pointer += VeSprintf(acBuffer + u32Pointer, 256 - u32Pointer, "i:");
			for(VeUInt32 i(0); i < m_pkCurInputLayout->m_kElementDescArray.Size(); ++i)
			{
				VeROInputLayoutGLES2::InputElementDesc& kDesc = m_pkCurInputLayout->m_kElementDescArray[i];
				if(i)
				{
					u32Pointer += VeSprintf(acBuffer + u32Pointer, 256 - u32Pointer, ",%d_%d", kDesc.m_eSemanticType, kDesc.m_u32SemanticIndex);
				}
				else
				{
					u32Pointer += VeSprintf(acBuffer + u32Pointer, 256 - u32Pointer, "%d_%d", kDesc.m_eSemanticType, kDesc.m_u32SemanticIndex);
				}
			}
			VeSprintf(acBuffer + u32Pointer, 256 - u32Pointer, ";v:%s;p:%s", m_pkCurVertexShader->GetName(), m_pkCurPixelShader->GetName());
		}
		VeFixedString kProgramName = acBuffer;
		VeUInt32* pu32Iter = m_kProgramMap.Find(kProgramName);
		if(!pu32Iter)
		{
			pu32Iter = &(m_kProgramMap[kProgramName]);
			*pu32Iter = m_kProgramArray.Size();
			m_kProgramArray.Resize(m_kProgramArray.Size() + 1);
			Program& kProgram = m_kProgramArray.Back();
			kProgram.m_u32Program = glCreateProgram();
			glAttachShader(kProgram.m_u32Program, m_pkCurVertexShader->m_u32Shader);
			glAttachShader(kProgram.m_u32Program, m_pkCurPixelShader->m_u32Shader);
			for(VeUInt32 i(0); i < m_pkCurInputLayout->m_kElementDescArray.Size(); ++i)
			{
				VeROInputLayoutGLES2::InputElementDesc& kDesc = m_pkCurInputLayout->m_kElementDescArray[i];
				switch(kDesc.m_eSemanticType)
				{
				case VeRenderer::SE_POSITION:
					VeSprintf(acBuffer, "aPosition%d", kDesc.m_u32SemanticIndex);
					break;
				case VeRenderer::SE_NORMAL:
					VeSprintf(acBuffer, "aNormal%d", kDesc.m_u32SemanticIndex);
					break;
				case VeRenderer::SE_COLOR:
					VeSprintf(acBuffer, "aColor%d", kDesc.m_u32SemanticIndex);
					break;
				case VeRenderer::SE_TEXCOORD:
					VeSprintf(acBuffer, "aTexcoord%d", kDesc.m_u32SemanticIndex);
					break;
				case VeRenderer::SE_TANGENT:
					VeSprintf(acBuffer, "aTangent%d", kDesc.m_u32SemanticIndex);
					break;
				case VeRenderer::SE_BINORMAL:
					VeSprintf(acBuffer, "aBinormal%d", kDesc.m_u32SemanticIndex);
					break;
				case VeRenderer::SE_BLENDINDICES:
					VeSprintf(acBuffer, "aBlendIndices%d", kDesc.m_u32SemanticIndex);
				case VeRenderer::SE_BLENDWEIGHT:
					VeSprintf(acBuffer, "aBlendWeight%d", kDesc.m_u32SemanticIndex);
					break;
				default:
					VE_ASSERT(!"Wrong semantic");
					break;
				}
				glBindAttribLocation(kProgram.m_u32Program, i, acBuffer);
			}
			glLinkProgram(kProgram.m_u32Program);
#			ifdef VE_DEBUG
			GLint bLinked;
			glGetProgramiv(kProgram.m_u32Program, GL_LINK_STATUS, &bLinked);
			VE_ASSERT(bLinked);
#			endif
			for(VeUInt32 i(0); i < VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
			{
				kProgram.m_ai32VSSlot[i] = glGetUniformLocation(kProgram.m_u32Program, "uVSSlot" + VeString::From(i));
				kProgram.m_ai32PSSlot[i] = glGetUniformLocation(kProgram.m_u32Program, "uPSSlot" + VeString::From(i));
			}

			kProgram.m_u32VSTexture = glGetUniformLocation(kProgram.m_u32Program, "uVSTexture");
			kProgram.m_u32PSTexture = glGetUniformLocation(kProgram.m_u32Program, "uPSTexture");
		}
		UseProgram(*pu32Iter);
	}

	bool bVertexBufferUpdate = false;
	if(m_u32VertexBufferChangeMax < VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT)
	{
		VE_ASSERT(m_u32VertexBufferChangeMin <= m_u32VertexBufferChangeMax);
		for(VeUInt32 i(m_u32VertexBufferChangeMin); i <= m_u32VertexBufferChangeMax; ++i)
		{
			VeVector<VertexBufferForSet>& kStack = m_akVertexBufferStack[i];
			if(kStack.Size())
			{
				VertexBufferForSet& kVertexBuffer = kStack.Back();
				if(kVertexBuffer.m_pkBuffer != m_akCurVertexBuffers[i].m_pkBuffer)
				{
					m_akCurVertexBuffers[i].m_pkBuffer = kVertexBuffer.m_pkBuffer;
					bVertexBufferUpdate = true;
				}
				if(kVertexBuffer.m_u32Stride != m_akCurVertexBuffers[i].m_u32Stride)
				{
					m_akCurVertexBuffers[i].m_u32Stride = kVertexBuffer.m_u32Stride;
					bVertexBufferUpdate = true;
				}
				if(kVertexBuffer.m_u32Offset != m_akCurVertexBuffers[i].m_u32Offset)
				{
					m_akCurVertexBuffers[i].m_u32Offset = kVertexBuffer.m_u32Offset;
					bVertexBufferUpdate = true;
				}
			}
			else if(m_akCurVertexBuffers[i].m_pkBuffer)
			{
				m_akCurVertexBuffers[i].m_pkBuffer = NULL;
				bVertexBufferUpdate = true;
			}

		}
		m_u32VertexBufferChangeMin = VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
		m_u32VertexBufferChangeMax = VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	}

	if(bVertexBufferUpdate || bInputLayoutUpdate)
	{
		EnableVertexAttribArray(m_pkCurInputLayout->m_kElementDescArray.Size());
		for(VeUInt32 i(0); i < m_pkCurInputLayout->m_kElementDescArray.Size(); ++i)
		{
			VeROInputLayoutGLES2::InputElementDesc& kDesc = m_pkCurInputLayout->m_kElementDescArray[i];
			VertexBufferForSet& kVBForSet = m_akCurVertexBuffers[kDesc.m_u16InputSlot];
			if(kVBForSet.m_pkBuffer)
			{
				VE_ASSERT(kVBForSet.m_pkBuffer->m_u32Target == GL_ARRAY_BUFFER);
				if(kVBForSet.m_pkBuffer->m_pvMemoryBuffer)
				{
					BindBuffer(GL_ARRAY_BUFFER, 0);
					SetVertexAttribArray(i, kDesc.m_u8Size, kDesc.m_u8Normalized,
						kDesc.m_u16Type, VeUInt16(kVBForSet.m_u32Stride), (void*)((VeSizeT)(kVBForSet.m_pkBuffer->m_pvMemoryBuffer) + kDesc.m_u16AlignedByteOffset + kVBForSet.m_u32Offset));
				}
				else if(kVBForSet.m_pkBuffer->m_u32Buffer)
				{
					BindBuffer(GL_ARRAY_BUFFER, kVBForSet.m_pkBuffer->m_u32Buffer);
					SetVertexAttribArray(i, kDesc.m_u8Size, kDesc.m_u8Normalized,
						kDesc.m_u16Type, VeUInt16(kVBForSet.m_u32Stride), (void*)((VeSizeT)kDesc.m_u16AlignedByteOffset + kVBForSet.m_u32Offset));
				}
			}
		}
	}

	bool bIndexBufferUpdate = false;
	VeROBufferGLES2* pkCurrentIB = m_kIndexBufferStack.Size() ? m_kIndexBufferStack.Back() : NULL;
	if(pkCurrentIB != m_pkCurIndexBuffer)
	{
		m_pkCurIndexBuffer = pkCurrentIB;
		bIndexBufferUpdate = true;
	}

	if(bIndexBufferUpdate)
	{
		if(m_pkCurIndexBuffer)
		{
			VE_ASSERT(m_pkCurIndexBuffer->m_u32Target == GL_ELEMENT_ARRAY_BUFFER);
			BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pkCurIndexBuffer->m_u32Buffer);
		}
		else
		{
			BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}

	for(VeUInt32 i(0); i < VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
	{
		if(m_ai32VSSlotLoc[i] >= 0 && m_akVSCBufferStack[i].Size())
		{
			bool bNeedSet = m_abVSSlotNeedUpdate[i];
			if(m_apkCurVSCBuffers[i] != m_akVSCBufferStack[i].Back())
			{
				m_apkCurVSCBuffers[i] = m_akVSCBufferStack[i].Back();
				bNeedSet = true;
			}
			if(bNeedSet)
			{
				m_abVSSlotNeedUpdate[i] = false;
				glUniform4fv(m_ai32VSSlotLoc[i], m_apkCurVSCBuffers[i]->m_u32ByteWidth >> 4, (const GLfloat*)m_apkCurVSCBuffers[i]->m_pvBuffer);
			}
		}
	}

	for(VeUInt32 i(0); i < VE_GLES2_PS_TEX_NUM; ++i)
	{
		VeROShaderResourceViewGLES2* pkNew = m_akPSShaderResourceViewStack[i].Size() ? m_akPSShaderResourceViewStack[i].Back() : NULL;
		if(pkNew != m_apkCurPSShaderResourceViews[i])
		{
			if(pkNew)
			{
				SetPSTexture(i, pkNew->m_spTexture->m_u32Texture);
				pkNew->SetSampler(m_akPSSamplerStack[i].Size() ? m_akPSSamplerStack[i].Back() : NULL);
			}
			else
			{
				SetPSTexture(i, 0);
			}			
			m_apkCurPSShaderResourceViews[i] = pkNew;
		}
	}

	bool bRenderTargetChanged = false;
	VE_ASSERT(m_kRenderTargetViewStack.Size());
	if(m_kRenderTargetViewStack.Back() != m_pkCurRenderTargetView)
	{
		m_pkCurRenderTargetView = m_kRenderTargetViewStack.Back();
		bRenderTargetChanged = true;
	}
	if((m_kDepthStencilViewStack.Size() ? m_kDepthStencilViewStack.Back() : NULL) != m_pkCurDepthStencilView)
	{
		m_pkCurDepthStencilView = (m_kDepthStencilViewStack.Size() ? m_kDepthStencilViewStack.Back() : NULL);
		bRenderTargetChanged = true;
	}
	if(bRenderTargetChanged)
	{
		m_kCurViewport = VeVector4D::ZERO;
		BindFrameBuffer(GetFrameBuffer(m_pkCurRenderTargetView, m_pkCurDepthStencilView));
		VE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	}

	GLint iHeight = (GLint)GetHeight();
	VE_ASSERT(m_pkCurRenderTargetView);
	if(m_pkCurRenderTargetView->m_spTexture)
	{
		iHeight = m_pkCurRenderTargetView->m_spTexture->m_u32Height;
	}

	if(m_kViewportStack.Size() && m_kViewportStack.Back() != m_kCurViewport)
	{
		m_kCurViewport = m_kViewportStack.Back();
		glViewport(GLint(m_kCurViewport.x), iHeight - GLint(m_kCurViewport.y) - GLint(m_kCurViewport.w), GLint(m_kCurViewport.z), GLint(m_kCurViewport.w));
	}

	if(m_kScissorRectStack.Size())
	{
		if(m_kCurScissorRect != m_kScissorRectStack.Back())
		{
			m_kCurScissorRect = m_kScissorRectStack.Back();
			glScissor(m_kCurScissorRect.x, iHeight - m_kCurScissorRect.y - m_kCurScissorRect.h, m_kCurScissorRect.w, m_kCurScissorRect.h);
		}
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererGLES2::GetGLTopology(VeIAPrimitiveTopology::Topology eTopology)
{
	switch(eTopology)
	{
	case VeIAPrimitiveTopology::TOPOLOGY_POINTLIST:
		return GL_POINTS;
	case VeIAPrimitiveTopology::TOPOLOGY_LINELIST:
		return GL_LINES;
	case VeIAPrimitiveTopology::TOPOLOGY_LINESTRIP:
		return GL_LINE_STRIP;
	case VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST:
		return GL_TRIANGLES;
	case VeIAPrimitiveTopology::TOPOLOGY_TRIANGLESTRIP:
		return GL_TRIANGLE_STRIP;
	default:
		return VE_INFINITE;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::ResetStateCache()
{
	m_kVertexShaderStack.Clear();
	m_pkCurVertexShader = NULL;
	m_kPixelShaderStack.Clear();
	m_pkCurPixelShader = NULL;
	m_kBlendStateStack.Clear();
	m_kCurBlendState.m_pkBlendState = NULL;
	m_kCurBlendState.m_kFactor = VeColor::WHITE;
	m_bBlendStateChange = VE_FALSE;
	m_kDepthStencilStateStack.Clear();
	m_kCurDepthStencilState.m_pkDepthStencilState = NULL;
	m_kCurDepthStencilState.m_u32StencilRef = 0;
	m_bDepthStencilStateChange = VE_FALSE;
	m_kInputLayoutStack.Clear();
	m_pkCurInputLayout = NULL;
	m_kRasterizeStateStack.Clear();
	m_pkCurRasterizeState = NULL;
	m_kTopologyStack.Clear();
	m_kIndexBufferStack.Clear();
	m_pkCurIndexBuffer = NULL;

	for(VeUInt32 i(0); i < VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT; ++i)
	{
		m_akVertexBufferStack[i].Clear();
	}
	VeZeroMemory(m_akCurVertexBuffers, sizeof(m_akCurVertexBuffers));
	m_u32VertexBufferChangeMin = VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	m_u32VertexBufferChangeMax = VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;

	for(VeUInt32 i(0); i < VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
	{
		m_akVSCBufferStack[i].Clear();
	}
	VeZeroMemory(m_apkCurVSCBuffers, sizeof(m_apkCurVSCBuffers));

	for(VeUInt32 i(0); i < VE_GLES2_PS_TEX_NUM; ++i)
	{
		m_akPSSamplerStack[i].Clear();
		m_akPSShaderResourceViewStack[i].Clear();
		m_apkCurPSShaderResourceViews[i] = NULL;
	}

	m_kViewportStack.Clear();
	m_kCurViewport = VeVector4D::ZERO;

	m_kScissorRectStack.Clear();
	VeZeroMemory(&m_kCurScissorRect, sizeof(m_kCurScissorRect));

	m_kRenderTargetViewStack.Clear();
	m_kDepthStencilViewStack.Clear();
	m_pkCurRenderTargetView = NULL;
	m_pkCurDepthStencilView = NULL;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::UpdateBufferSize()
{
	ResetStateCache();
#	if defined(VE_PLATFORM_MOBILE_SIM) || defined(VE_PLATFORM_ANDROID)
	EGLint iWidth, iHeight;
	eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_WIDTH, &iWidth);
	eglQuerySurface(m_eglDisplay, m_eglSurface, EGL_HEIGHT, &iHeight);
	if(GetWidth() != (VeUInt32)iWidth || GetHeight() != (VeUInt32)iHeight)
	{
		SetScreenSize(iWidth, iHeight);
		OnBufferResized(GetWidth(), GetHeight());
	}
#   elif defined(VE_PLATFORM_IOS)
	BindRenderBuffer(m_u32BackRenderBuffer);
	VeUInt32 u32Width, u32Height;
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, (GLint*)&u32Width);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, (GLint*)&u32Height);
	if(GetWidth() != u32Width || GetHeight() != u32Height)
	{
		SetScreenSize(u32Width, u32Height);
		OnBufferResized(GetWidth(), GetHeight());
	}
#	endif
}
//--------------------------------------------------------------------------
void VeRendererGLES2::GLInitGlobal()
{
	m_kDescription.m_kVendor = (const VeChar8*)glGetString(GL_VENDOR);
	m_kDescription.m_kRenderer = (const VeChar8*)glGetString(GL_RENDERER);
	m_kDescription.m_kVersion = (const VeChar8*)glGetString(GL_VERSION);
	m_kDescription.m_kGLSLVersion = (const VeChar8*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	VE_LOG_D("Venus3D", "GL_VENDOR: %s", (const VeChar8*)m_kDescription.m_kVendor);
	VE_LOG_D("Venus3D", "GL_RENDERER: %s", (const VeChar8*)m_kDescription.m_kRenderer);
	VE_LOG_D("Venus3D", "GL_VERSION: %s", (const VeChar8*)m_kDescription.m_kVersion);
	VE_LOG_D("Venus3D", "GL_SHADING_LANGUAGE_VERSION: %s", (const VeChar8*)m_kDescription.m_kGLSLVersion);
	VeChar8 acExtensions[2048];
	VeStrcpy(acExtensions, (const VeChar8*)glGetString(GL_EXTENSIONS));
	VeChar8* pcContent;
	VeChar8* pcTemp = VeStrtok(acExtensions, " ", &pcContent);
	while(pcTemp)
	{
		m_kDescription.m_kExtensionMap[pcTemp] = m_kDescription.m_kExtensionArray.Size();
		m_kDescription.m_kExtensionArray.PushBack(pcTemp);
		VE_LOG_D("Venus3D", "GL_EXTENSION: %s", (const VeChar8*)m_kDescription.m_kExtensionArray.Back());
		pcTemp = VeStrtok(NULL, " ", &pcContent);
	}

#   ifdef VE_PLATFORM_MOBILE_SIM
	m_bSupportDepthTexute = false;
#	else
	m_bSupportDepthTexute = m_kDescription.m_kExtensionMap.Find("GL_OES_depth_texture") ? true : false;
#	endif
	VeDebugOutput("Depth texture support: %s", (const VeChar8*)(VeString::From(m_bSupportDepthTexute)));

#   ifdef VE_PLATFORM_MOBILE_SIM
	m_bSupportAnisotropic = true;
#	else
	m_bSupportAnisotropic = m_kDescription.m_kExtensionMap.Find("GL_EXT_texture_filter_anisotropic") ? true : false;
#	endif
	VeDebugOutput("Anisotropic filter support: %s", (const VeChar8*)(VeString::From(m_bSupportAnisotropic)));
	if(m_bSupportAnisotropic)
	{
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_i32MaxAnisotropy);
		VeDebugOutput("Max Anisotropic is: %d", m_i32MaxAnisotropy);
	}

#	if defined(VE_PLATFORM_IOS)
    m_bSupportMSAA = m_kDescription.m_kExtensionMap.Find("GL_APPLE_framebuffer_multisample") ? true : false;
    if(m_bSupportMSAA)
    {
        GLint iTemp;
        glGetIntegerv(GL_MAX_SAMPLES_APPLE, &iTemp);
        m_u8MaxAASamples = iTemp;
    }
#	endif
	VeDebugOutput("Multisample Anti-Aliasing support: %s", (const VeChar8*)(VeString::From(m_bSupportMSAA)));
	if(m_bSupportMSAA)
	{
		VeDebugOutput("Max samples is: %d", (VeUInt32)m_u8MaxAASamples);
	}
    
    VE_ASSERT(m_kFrameBufferObjectMap.Empty() && m_kFrameBufferObjectArray.Empty());
	VE_ASSERT(m_kProgramMap.Empty() && m_kProgramArray.Empty());
#	if defined(VE_PLATFORM_IOS)
    m_kFrameBufferObjectMap["back_buffer"] = m_u32BackFrameBuffer;
#   else
	GLint iOriginalFramebuffer(0);
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &iOriginalFramebuffer);
	m_kFrameBufferObjectMap["back_buffer"] = iOriginalFramebuffer;
#   endif

	m_spBackBuffer = VE_NEW VeRORenderTargetViewGLES2("back_buffer");
	AddObject(m_spBackBuffer);

	SetCullEnable(true);
	SetFrontFace(GL_CW);

	glClearColor(0, 0, 0, 0);
	glClearDepthf(1.0f);
	glClearStencil(0);

	m_kClearColor = VeColor::BLACK;
	m_f32ClearDepth = 1.0f;
	m_u8ClearStencil = 0;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::GLTermGlobal()
{
	if(m_spBackBuffer)
	{
		DelObject(m_spBackBuffer);
	}
	m_spBackBuffer = NULL;
	m_kFrameBufferObjectMap.Clear();
	if(m_kFrameBufferObjectArray.Size())
	{
		glDeleteFramebuffers(m_kFrameBufferObjectArray.Size(), m_kFrameBufferObjectArray.Begin());
	}
	m_kFrameBufferObjectArray.Clear();
	m_kProgramMap.Clear();
	for(VeUInt32 i(0); i < m_kProgramArray.Size(); ++i)
	{
		glDeleteProgram(m_kProgramArray[i].m_u32Program);
	}
	m_kProgramArray.Clear();
}
//--------------------------------------------------------------------------
void VeRendererGLES2::GLCacheInit()
{
	VeZeroMemory(m_au32BindBuffers, sizeof(m_au32BindBuffers));
	m_u32BindRenderBuffer = 0;
	m_u32BindFrameBuffer = 0;
	m_u32UsedProgram = VE_INFINITE;
	for(VeUInt32 i(0); i < VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
	{
		m_ai32VSSlotLoc[i] = -1;
		m_ai32PSSlotLoc[i] = -1;
		m_abVSSlotNeedUpdate[i] = false;
		m_abPSSlotNeedUpdate[i] = false;
	}
	m_kVertexAttribArrayState.Clear();
	m_kVertexAttribArrayState.Reserve(VE_GLES2_IA_VERTEX_ATTRIB_ARRAY_NUM);

	m_bAlphaToCoverageEnable = false;
	m_bBlendEnable = false;
	m_u16SrcBlend = GL_ONE;
	m_u16DstBlend = GL_ZERO;
	m_u16SrcBlendAlpha = GL_ONE;
	m_u16DstBlendAlpha = GL_ZERO;
	m_u16BlendOp = GL_FUNC_ADD;
	m_u16BlendOpAlpha = GL_FUNC_ADD;
	m_u16WriteMask = VeRenderer::COLOR_WRITE_ENABLE_ALL;

	m_bDepthEnable = false;
	m_bDepthWrite = true;
	m_u16DepthFunc = 0;
	m_bStencilEnable = false;
	m_u8StencilReadMask = 0xff;
	m_u8StencilWriteMask = 0xff;
	m_u16StencilFrontFailOp = 0;
	m_u16StencilFrontDepthFailOp = 0;
	m_u16StencilFrontPassOp = 0;
	m_u16StencilFrontFunc = 0;
	m_u16StencilBackFailOp = 0;
	m_u16StencilBackDepthFailOp = 0;
	m_u16StencilBackPassOp = 0;
	m_u16StencilBackFunc = 0;
	m_u32StencilRef = 0;

	m_bCullEnable = false;
	m_bDepthBiasEnable = false;
	m_bMultisampleEnable = false;
	m_bScissorEnable = false;
	m_u16CullFace = GL_BACK;
	m_u16FrontFace = GL_CCW;
	m_f32PolyFactor = 0;
	m_f32PolyUnits = 0;

	VeZeroMemory(m_au32PSTexture, sizeof(m_au32PSTexture));
	VeZeroMemory(m_au32VSTexture, sizeof(m_au32VSTexture));
	m_u32CurrentActiveTexture = VE_INFINITE;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::BindBuffer(VeUInt32 u32Target, VeUInt32 u32Buffer)
{
	VeUInt32 u32Index(TARGET_NUM);
	switch(u32Target)
	{
	case GL_ARRAY_BUFFER:
		u32Index = TARGET_ARRAY_BUFFER;
		break;
	case GL_ELEMENT_ARRAY_BUFFER:
		u32Index = TARGET_ELEMENT_ARRAY_BUFFER;
		break;
	default:
		break;
	}
	VE_ASSERT(u32Index < TARGET_NUM);
	if(m_au32BindBuffers[u32Index] != u32Buffer)
	{
		glBindBuffer(u32Target, u32Buffer);
		m_au32BindBuffers[u32Index] = u32Buffer;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::BindRenderBuffer(VeUInt32 u32Buffer)
{
	if(m_u32BindRenderBuffer != u32Buffer)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, u32Buffer);
		m_u32BindRenderBuffer = u32Buffer;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::BindFrameBuffer(VeUInt32 u32Buffer)
{
	if(m_u32BindFrameBuffer != u32Buffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, u32Buffer);
		m_u32BindFrameBuffer = u32Buffer;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::UseProgram(VeUInt32 u32Program)
{
	if(u32Program != m_u32UsedProgram && u32Program < m_kProgramArray.Size())
	{
		Program& kCurrent = m_kProgramArray[u32Program];
		glUseProgram(kCurrent.m_u32Program);
		for(VeUInt32 i(0); i < VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
		{
			m_ai32VSSlotLoc[i] = kCurrent.m_ai32VSSlot[i];
			m_abVSSlotNeedUpdate[i] = m_ai32VSSlotLoc[i] >= 0;
			m_ai32PSSlotLoc[i] = kCurrent.m_ai32PSSlot[i];
			m_abPSSlotNeedUpdate[i] = m_ai32PSSlotLoc[i] >= 0;
		}
		if(kCurrent.m_u32VSTexture < VE_GLES2_VS_TEX_NUM)
			glUniform1i(kCurrent.m_u32VSTexture, VE_GLES2_PS_TEX_NUM);
		if(kCurrent.m_u32PSTexture < VE_GLES2_PS_TEX_NUM)
			glUniform1i(kCurrent.m_u32PSTexture, 0);
		m_u32UsedProgram = u32Program;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::EnableVertexAttribArray(VeUInt32 u32Count)
{
	VeUInt32 u32CurrentCount = m_kVertexAttribArrayState.Size();
	if(u32CurrentCount < u32Count)
	{
		for(VeUInt32 i(u32CurrentCount); i < u32Count; ++i)
		{
			glEnableVertexAttribArray(i);
		}
	}
	else
	{
		for(VeUInt32 i(u32Count); i < u32CurrentCount; ++i)
		{
			glDisableVertexAttribArray(i);
		}
	}
	m_kVertexAttribArrayState.Resize(u32Count);
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetVertexAttribArray(VeUInt32 u32Index,
	VeUInt8 u8Size, VeUInt8 u8Normalized, VeUInt16 u16Type,
	VeUInt16 u16Stride, void* pvAlignedByteOffset)
{
	VE_ASSERT(u32Index < m_kVertexAttribArrayState.Size());
	VertexAttrib& kCurrent = m_kVertexAttribArrayState[u32Index];
	if(kCurrent.m_u8Size != u8Size
		|| kCurrent.m_u8Size != u8Size
		|| kCurrent.m_u8Normalized != u8Normalized
		|| kCurrent.m_u16Type != u16Type
		|| kCurrent.m_u16Stride != u16Stride
		|| kCurrent.m_pvAlignedByteOffset != pvAlignedByteOffset)
	{
		glVertexAttribPointer(u32Index, u8Size, u16Type, u8Normalized, u16Stride, pvAlignedByteOffset);
		kCurrent.m_u8Size = u8Size;
		kCurrent.m_u8Normalized = u8Normalized;
		kCurrent.m_u16Type = u16Type;
		kCurrent.m_u16Stride = u16Stride;
		kCurrent.m_pvAlignedByteOffset = pvAlignedByteOffset;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetAlphaToCoverageEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bAlphaToCoverageEnable)
		{
			glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			m_bAlphaToCoverageEnable = true;
		}
	}
	else if(m_bAlphaToCoverageEnable)
	{
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		m_bAlphaToCoverageEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetBlendEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bBlendEnable)
		{
			glEnable(GL_BLEND);
			m_bBlendEnable = true;
		}
	}
	else if(m_bBlendEnable)
	{
		glDisable(GL_BLEND);
		m_bBlendEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetBlendFunc(VeUInt16 u16SrcColor, VeUInt16 u16DstColor, VeUInt16 u16SrcAlpha, VeUInt16 u16DstAlpha)
{
	if(u16SrcColor != m_u16SrcBlend || u16DstColor != m_u16DstBlend || u16SrcAlpha != m_u16SrcBlendAlpha || u16DstAlpha != m_u16DstBlendAlpha)
	{
		glBlendFuncSeparate(u16SrcColor, u16DstColor, u16SrcAlpha, u16DstAlpha);
		m_u16SrcBlend = u16SrcColor;
		m_u16DstBlend = u16DstColor;
		m_u16SrcBlendAlpha = u16SrcAlpha;
		m_u16DstBlendAlpha = u16DstAlpha;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetBlendOp(VeUInt16 u16ColorOp, VeUInt16 u16AlphaOp)
{
	if(u16ColorOp != m_u16BlendOp || u16AlphaOp != m_u16BlendOpAlpha)
	{
		glBlendEquationSeparate(u16ColorOp, u16AlphaOp);
		m_u16BlendOp = u16ColorOp;
		m_u16BlendOpAlpha = u16AlphaOp;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetWriteMask(VeUInt16 u16Mask)
{
	if(m_u16WriteMask != u16Mask)
	{
		glColorMask(VE_MASK_HAS_ANY(u16Mask, VeRenderer::COLOR_WRITE_ENABLE_RED) ? GL_TRUE : GL_FALSE,
			VE_MASK_HAS_ANY(u16Mask, VeRenderer::COLOR_WRITE_ENABLE_GREEN) ? GL_TRUE : GL_FALSE,
			VE_MASK_HAS_ANY(u16Mask, VeRenderer::COLOR_WRITE_ENABLE_BLUE) ? GL_TRUE : GL_FALSE,
			VE_MASK_HAS_ANY(u16Mask, VeRenderer::COLOR_WRITE_ENABLE_ALPHA) ? GL_TRUE : GL_FALSE);
		m_u16WriteMask = u16Mask;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetDepthEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bDepthEnable)
		{
			glEnable(GL_DEPTH_TEST);
			m_bDepthEnable = true;
		}
	}
	else if(m_bDepthEnable)
	{
		glDisable(GL_DEPTH_TEST);
		m_bDepthEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetDepthWrite(bool bWrite)
{
	if(bWrite)
	{
		if(!m_bDepthWrite)
		{
			glDepthMask(GL_FALSE);
			m_bDepthWrite = true;
		}
	}
	else if(m_bDepthWrite)
	{
		glDepthMask(GL_TRUE);
		m_bDepthWrite = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetDepthFunc(VeUInt16 u16Func)
{
	if(m_u16DepthFunc != u16Func)
	{
		glDepthFunc(u16Func);
		m_u16DepthFunc = u16Func;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetStencilEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bStencilEnable)
		{
			glEnable(GL_STENCIL_TEST);
			m_bStencilEnable = true;
		}
	}
	else if(m_bStencilEnable)
	{
		glDisable(GL_STENCIL_TEST);
		m_bStencilEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetStencilWriteMask(VeUInt8 u8Mask)
{
	if(m_u8StencilWriteMask != u8Mask)
	{
		glStencilMask(VE_INFINITE & u8Mask);
		m_u8StencilWriteMask = u8Mask;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetStencilFunc(VeUInt16 u16FrontFunc, VeUInt16 u16BackFunc, VeUInt32 u32Ref, VeUInt8 u8ReadMask)
{
	bool bFrontChange = false;
	bool bBackChange = false;
	if(u16FrontFunc != m_u16StencilFrontFunc)
	{
		m_u16StencilFrontFunc = u16FrontFunc;
		bFrontChange = true;
	}
	if(u16BackFunc != m_u16StencilBackFunc)
	{
		m_u16StencilBackFunc = u16BackFunc;
		bBackChange = true;
	}
	if(u32Ref != m_u32StencilRef)
	{
		m_u32StencilRef = u32Ref;
		bFrontChange = true;
		bBackChange = true;
	}
	if(u8ReadMask != m_u8StencilReadMask)
	{
		m_u8StencilReadMask = u8ReadMask;
		bFrontChange = true;
		bBackChange = true;
	}
	if(bFrontChange)
	{
		glStencilFuncSeparate(GL_FRONT, m_u16StencilFrontFunc, m_u32StencilRef, VE_INFINITE & m_u8StencilReadMask);
	}
	if(bBackChange)
	{
		glStencilFuncSeparate(GL_BACK, m_u16StencilBackFunc, m_u32StencilRef, VE_INFINITE & m_u8StencilReadMask);
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetStencilFrontOp(VeUInt16 u16Fail, VeUInt16 u16DepthFail, VeUInt16 u16Pass)
{
	bool bChange = false;
	if(m_u16StencilFrontFailOp != u16Fail)
	{
		m_u16StencilFrontFailOp = u16Fail;
		bChange = true;
	}
	if(m_u16StencilFrontDepthFailOp != u16DepthFail)
	{
		m_u16StencilFrontDepthFailOp = u16DepthFail;
		bChange = true;
	}
	if(m_u16StencilFrontPassOp != u16Pass)
	{
		m_u16StencilFrontPassOp = u16Pass;
		bChange = true;
	}
	if(bChange)
	{
		glStencilOpSeparate(GL_FRONT, m_u16StencilFrontFailOp, m_u16StencilFrontDepthFailOp, m_u16StencilFrontPassOp);
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetStencilBackOp(VeUInt16 u16Fail, VeUInt16 u16DepthFail, VeUInt16 u16Pass)
{
	bool bChange = false;
	if(m_u16StencilBackFailOp != u16Fail)
	{
		m_u16StencilBackFailOp = u16Fail;
		bChange = true;
	}
	if(m_u16StencilBackDepthFailOp != u16DepthFail)
	{
		m_u16StencilBackDepthFailOp = u16DepthFail;
		bChange = true;
	}
	if(m_u16StencilBackPassOp != u16Pass)
	{
		m_u16StencilBackPassOp = u16Pass;
		bChange = true;
	}
	if(bChange)
	{
		glStencilOpSeparate(GL_BACK, m_u16StencilBackFailOp, m_u16StencilBackDepthFailOp, m_u16StencilBackPassOp);
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetCullEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bCullEnable)
		{
			glEnable(GL_CULL_FACE);
			m_bCullEnable = true;
		}
	}
	else if(m_bCullEnable)
	{
		glDisable(GL_CULL_FACE);
		m_bCullEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetDepthBiasEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bDepthBiasEnable)
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
			m_bDepthBiasEnable = true;
		}
	}
	else if(m_bDepthBiasEnable)
	{
		glDisable(GL_POLYGON_OFFSET_FILL);
		m_bDepthBiasEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetMultisampleEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bMultisampleEnable)
		{
			glEnable(GL_SAMPLE_COVERAGE);
			m_bMultisampleEnable = true;
		}
	}
	else if(m_bMultisampleEnable)
	{
		glDisable(GL_SAMPLE_COVERAGE);
		m_bMultisampleEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetScissorEnable(bool bEnable)
{
	if(bEnable)
	{
		if(!m_bScissorEnable)
		{
			glEnable(GL_SCISSOR_TEST);
			m_bScissorEnable = true;
		}
	}
	else if(m_bScissorEnable)
	{
		glDisable(GL_SCISSOR_TEST);
		m_bScissorEnable = false;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetCullFace(VeUInt16 u16Cull)
{
	if(m_u16CullFace != u16Cull)
	{
		glCullFace(u16Cull);
		m_u16CullFace = u16Cull;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetFrontFace(VeUInt16 u16Front)
{
	if(m_u16FrontFace != u16Front)
	{
		glFrontFace(u16Front);
		m_u16FrontFace = u16Front;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetPolyOffset(VeFloat32 f32Factor, VeFloat32 f32Units)
{
	bool bChange = false;
	if(m_f32PolyFactor != f32Factor)
	{
		m_f32PolyFactor = f32Factor;
		bChange = true;
	}
	if(m_f32PolyUnits != f32Units)
	{
		m_f32PolyUnits = f32Units;
		bChange = true;
	}
	if(bChange)
	{
		glPolygonOffset(m_f32PolyFactor, m_f32PolyUnits);
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetPSTexture(VeUInt32 u32Slot, VeUInt32 u32Texture)
{
	if(m_au32PSTexture[u32Slot] != u32Texture)
	{
		ActiveTexture(u32Slot);
		glBindTexture(GL_TEXTURE_2D, u32Texture);
		m_au32PSTexture[u32Slot] = u32Texture;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::SetVSTexture(VeUInt32 u32Slot, VeUInt32 u32Texture)
{
	if(m_au32VSTexture[u32Slot] != u32Texture)
	{
		ActiveTexture(VE_GLES2_PS_TEX_NUM + u32Slot);
		glBindTexture(GL_TEXTURE_2D, u32Texture);
		m_au32VSTexture[u32Slot] = u32Texture;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::ClearColor(const VeColor& kColor)
{
	if(kColor != m_kClearColor)
	{
		glClearColor(kColor.r, kColor.g, kColor.b, kColor.a);
		m_kClearColor = kColor;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::ClearDepth(VeFloat32 f32Depth)
{
	if(f32Depth != m_f32ClearDepth)
	{
		glClearDepthf(f32Depth);
		m_f32ClearDepth = f32Depth;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::ClearStencil(VeUInt8 u8Stencil)
{
	if(u8Stencil != m_u8ClearStencil)
	{
		glClearStencil(u8Stencil);
		m_u8ClearStencil = u8Stencil;
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererGLES2::GetFrameBuffer(VeRORenderTargetViewGLES2* pkRTV, VeRODepthStencilViewGLES2* pkDSV)
{
	static VeChar8 acBuffer[256];
	if(pkDSV)
	{
		VeSprintf(acBuffer, "%s#%s", pkRTV->GetName(), pkDSV->GetName());
	}
	else
	{
		VeSprintf(acBuffer, "%s", pkRTV->GetName());
	}
	VeUInt32* pu32Iter = m_kFrameBufferObjectMap.Find(acBuffer);
	if(!pu32Iter)
	{
		VeUInt32 u32FrameBufferObject(0);
		glGenFramebuffers(1, &u32FrameBufferObject);
		BindFrameBuffer(u32FrameBufferObject);
		VE_ASSERT(pkRTV && pkRTV->m_spTexture);
		if(pkRTV->m_spTexture->m_u32Target == GL_TEXTURE_2D)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pkRTV->m_spTexture->m_u32Texture, pkRTV->m_u32Level);
		}
		else
		{
			VE_ASSERT(pkRTV->m_spTexture->m_u32Target == GL_RENDERBUFFER);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, pkRTV->m_spTexture->m_u32Texture);
		}
		if(pkDSV)
		{
			if(pkDSV->m_spTexture->m_u32Target == GL_TEXTURE_2D)
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, pkDSV->m_spTexture->m_u32Texture, pkDSV->m_u32Level);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, pkDSV->m_spTexture->m_u32Texture, pkDSV->m_u32Level);
			}
			else
			{
				VE_ASSERT(pkDSV->m_spTexture->m_u32Target == GL_RENDERBUFFER);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pkDSV->m_spTexture->m_u32Texture);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, pkDSV->m_spTexture->m_u32Texture);
			}
		}
		m_kFrameBufferObjectArray.PushBack(u32FrameBufferObject);
		pu32Iter = &(m_kFrameBufferObjectMap[acBuffer]);
		*pu32Iter = u32FrameBufferObject;
	}
	return *pu32Iter;
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererGLES2::GetMaxAnisotropy()
{
	return m_i32MaxAnisotropy;
}
//--------------------------------------------------------------------------
void VeRendererGLES2::ActiveTexture(VeUInt32 u32Slot)
{
	if(m_u32CurrentActiveTexture != u32Slot)
	{
		glActiveTexture(GL_TEXTURE0 + u32Slot);
		m_u32CurrentActiveTexture = u32Slot;
	}
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateRenderObjects()
{
	VeMemoryOStream kStream;
	VeFixedString kName;

	kStream << VeUInt16(VE_FALSE);
	kStream << VeUInt16(1);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VeRenderer::BLEND_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::COLOR_WRITE_ENABLE_ALL);
	g_pRenderer->CreateBlendState("blend_alpha", kStream);
	kStream.Reset();

	kStream << VeUInt16(VE_FALSE);
	kStream << VeUInt16(1);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::COLOR_WRITE_ENABLE_ALL);
	g_pRenderer->CreateBlendState("blend_add", kStream);
	kStream.Reset();

	kStream << VeUInt16(VE_FALSE);
	kStream << VeUInt16(1);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::COLOR_WRITE_ENABLE_ALL);
	g_pRenderer->CreateBlendState("blend_alpha_mul", kStream);
	kStream.Reset();

	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VeRenderer::COMPARISON_ALWAYS);
	kStream << VeUInt8(VE_FALSE);
	g_pRenderer->CreateDepthStencilState("no_depth", kStream);
	kStream.Reset();

	kStream << VeUInt8(VeRenderer::FILL_SOLID);
	kStream << VeUInt8(VeRenderer::CULL_NONE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VeRenderer::DBIAS_NONE);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	g_pRenderer->CreateRasterizerState("draw_2d", kStream);
	kStream.Reset();

	kStream << VeUInt8(VeRenderer::FILL_SOLID);
	kStream << VeUInt8(VeRenderer::CULL_NONE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VeRenderer::DBIAS_NONE);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	g_pRenderer->CreateRasterizerState("draw_2d_clip", kStream);
	kStream.Reset();

	kStream << VeUInt8(VeRenderer::FILTER_MIN_MAG_LINEAR_MIP_POINT);
	kStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
	kStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
	kStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
	kStream << VeUInt16(16);
	kStream << VeUInt16(VeRenderer::COMPARISON_NEVER);
	kStream << 0.0f;
	kStream << -VE_MAXFLOAT_F;
	kStream << VE_MAXFLOAT_F;
	kStream << VeColor::BLACK;
	g_pRenderer->CreateSamplerState("tri_linear", kStream);
	kStream.Reset();

	kStream << VeUInt32(16);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(1);
	kStream << VeUInt32(16);
	kStream << VeUInt32(16);
	kStream << GetInvWidthF();
	kStream << GetInvHeightF();
	kStream << 1000.0f;
	kStream << (GetHeightF() * GetInvWidthF());
	g_pRenderer->CreateBuffer("screen_params", kStream);
	kStream.Reset();

	kName = "draw_sprite_base";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(4);
	kStream << VeByte(VeRenderer::SE_POSITION);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R32G32_FLOAT);
	kStream << VeByte(0);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::SE_TEXCOORD);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R16G16B16A16_UINT);
	kStream << VeByte(0);
	kStream << VeByte(8);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::SE_COLOR);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R8G8B8A8_UNORM);
	kStream << VeByte(0);
	kStream << VeByte(16);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::SE_COLOR);
	kStream << VeByte(1);
	kStream << VeByte(VeRenderer::FMT_R8G8B8A8_UNORM);
	kStream << VeByte(0);
	kStream << VeByte(20);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	g_pRenderer->CreateInputLayout("draw_sprite_base", kStream);
	kStream.Reset();

	kName = "draw_color_shape";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(2);
	kStream << VeByte(VeRenderer::SE_POSITION);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R32G32_FLOAT);
	kStream << VeByte(0);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::SE_COLOR);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R8G8B8A8_UNORM);
	kStream << VeByte(0);
	kStream << VeByte(8);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	g_pRenderer->CreateInputLayout("draw_color_shape", kStream);
	kStream.Reset();

	kName = "draw_text";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(3);
	kStream << VeByte(VeRenderer::SE_POSITION);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R32G32B32_FLOAT);
	kStream << VeByte(0);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::SE_TEXCOORD);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R16G16B16A16_UINT);
	kStream << VeByte(0);
	kStream << VeByte(12);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::SE_COLOR);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R8G8B8A8_UNORM);
	kStream << VeByte(0);
	kStream << VeByte(20);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	g_pRenderer->CreateInputLayout("draw_text", kStream);
	kStream.Reset();

	kStream << VeUInt32(0);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kStream << VeByte(VeRenderer::BIND_VERTEX_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(0);
	{
		VeROBufferPtr spBuffer;
		g_pRenderer->CreateBuffer("quad_vb", kStream, &spBuffer);
		VeDynamicCast(VeROBufferGLES2, spBuffer)->m_pvMemoryBuffer = m_pvQuadBuffer;
	}
	kStream.Reset();

	kStream << VeUInt32(VE_MAX_COMBINED_SPRITE * sizeof(VeUInt16) * 6);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kStream << VeByte(VeRenderer::BIND_INDEX_BUFFER);
	kStream << VeByte(0);
	kStream << VeByte(1);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	for(VeUInt32 i(0); i < VE_MAX_COMBINED_SPRITE; ++i)
	{
		VeUInt16 u16Start = i * 4;
		VeUInt16 au16Quad[6] =
		{
			VeUInt16(0 + u16Start),
			VeUInt16(1 + u16Start),
			VeUInt16(2 + u16Start),
			VeUInt16(2 + u16Start),
			VeUInt16(1 + u16Start),
			VeUInt16(3 + u16Start)
		};
		kStream.AddBlob(au16Quad, VeInt32(sizeof(au16Quad)));
	}
	g_pRenderer->CreateBuffer("quad_ib", kStream);
	kStream.Reset();

	kStream << VeUInt32(VE_MAX_COMBINED_SPRITE * sizeof(VeUInt16) * 8);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kStream << VeByte(VeRenderer::BIND_INDEX_BUFFER);
	kStream << VeByte(0);
	kStream << VeByte(1);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	for(VeUInt32 i(0); i < VE_MAX_COMBINED_SPRITE; ++i)
	{
		VeUInt16 u16Start = i * 4;
		VeUInt16 au16Quad[8] =
		{
			VeUInt16(0 + u16Start),
			VeUInt16(1 + u16Start),
			VeUInt16(1 + u16Start),
			VeUInt16(3 + u16Start),
			VeUInt16(3 + u16Start),
			VeUInt16(2 + u16Start),
			VeUInt16(2 + u16Start),
			VeUInt16(0 + u16Start)
		};
		kStream.AddBlob(au16Quad, VeInt32(sizeof(au16Quad)));
	}
	g_pRenderer->CreateBuffer("square_frame_ib", kStream);
	kStream.Reset();

	kStream << VeUInt32(80 * VE_MAX_COMBINED_SPRITE);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(0);
	g_pRenderer->CreateBuffer("quad_cb", kStream);
}
//--------------------------------------------------------------------------
void VeRendererGLES2::CreateNodeDatas()
{
	VeMemoryOStream kStream;
	VeFixedString kName;

	kStream << VeUInt32(3);
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "screen_params";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeRenderTick::OM_DEPTH_STENCIL_STATE;
	kName = "no_depth";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeRenderTick::RS_STATE;
	kName = "draw_2d";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_root", kStream);
	kStream.Reset();

	kStream << VeUInt32(6);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_sprite_base";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "quad_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeRenderTick::PS_SAMPLER;
	kName = "tri_linear";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_sprite", kStream);
	kStream.Reset();

	kStream << VeUInt32(5);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_color_shape";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_LINELIST;
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "square_frame_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_square_frame", kStream);
	kStream.Reset();

	kStream << VeUInt32(5);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_color_shape";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "quad_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_square", kStream);
	kStream.Reset();

	kStream << VeUInt32(7);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_text";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "quad_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeRenderTick::PS_SAMPLER;
	kName = "tri_linear";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "blend_alpha";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_text", kStream);
	kStream.Reset();
}
//--------------------------------------------------------------------------
void* VeRendererGLES2::UseQuadBuffer(VeUInt32 u32Size, VeUInt32* pu32Offset)
{
	VE_ASSERT((m_u32QuadPointer + u32Size) <= VE_GLES2_QUAD_BUFFER_SIZE);
	void* pvRes = (void*)((VeSizeT)m_pvQuadBuffer + m_u32QuadPointer);
	if(pu32Offset) *pu32Offset = m_u32QuadPointer;
	m_u32QuadPointer += u32Size;
	return pvRes;
}
//--------------------------------------------------------------------------
VeRendererGLES2::VertexAttrib::VertexAttrib()
{
	m_u8Size = 0;
	m_u8Normalized = 0;
	m_u16Type = 0;
	m_u16Stride = 0;
	m_pvAlignedByteOffset = NULL;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
