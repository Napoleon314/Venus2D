////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRendererGL.cpp
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeRendererGL.h"
#if defined(VE_PLATFORM_WIN)
#	include "Windows/_VeWindows.h"
#endif

//--------------------------------------------------------------------------
#ifdef VE_ENABLE_GL
//--------------------------------------------------------------------------
void VeRendererGL::Create()
{
	if(!GetSingletonPtr())
	{
		VE_NEW VeRendererGL();
	}
}
//--------------------------------------------------------------------------
VeRendererGL::VeRendererGL()
    : m_u32RefreshRate(0)
    , m_bFullScreen(false)
#if defined(VE_PLATFORM_WIN)
	, m_hDeviceContext(NULL)
	, m_hRenderContext(NULL)
	, m_i32DeviceHorzers(0)
#elif defined(VE_PLATFORM_LINUX)
	, m_hContext(NULL)
	, m_hAtomDeleteWindow(0)
	, m_hAtomFullScreen(0)
	, m_hAtomState(0)
#endif
{
	VeInitOpenGL();
}
//--------------------------------------------------------------------------
VeRendererGL::~VeRendererGL()
{
	VeTermOpenGL();
}
//--------------------------------------------------------------------------
VeRenderer::API VeRendererGL::GetAPI()
{
	return API_OGL;
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererGL::CheckCapability(Capability eCap)
{
	switch(eCap)
	{
	case CAP_DEPTH_TEX:
		return VE_TRUE;
	case CAP_ANISOTROPIC:
		return VE_TRUE;
	case CAP_MULTI_SAMPLE:
		return VE_TRUE;
	case CAP_DRAW_INSTANCE:
		return VE_TRUE;
	default:
		return 0;
	}
}
//--------------------------------------------------------------------------
void VeRendererGL::Init()
{
	VE_ASSERT(!m_bInited);

#if defined(VE_PLATFORM_WIN)

	m_hDeviceContext = GetDC(((VeWindows*)g_pDevice)->GetWindowHandle());
	m_i32DeviceHorzers = GetDeviceCaps(m_hDeviceContext, HORZRES);
	PIXELFORMATDESCRIPTOR kPFD;
	VeZeroMemory(&kPFD, sizeof(PIXELFORMATDESCRIPTOR));
	kPFD.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	kPFD.nVersion   = 1;
	kPFD.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DEPTH_DONTCARE;
	kPFD.iPixelType = PFD_TYPE_RGBA;
	kPFD.cColorBits = 24;
	kPFD.cAlphaBits = 8;
	GLuint iPixelFormat = ChoosePixelFormat(m_hDeviceContext, &kPFD);
	VE_ASSERT(iPixelFormat);
	DescribePixelFormat(m_hDeviceContext, iPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &kPFD);
	VE_ASSERT_EQ(SetPixelFormat(m_hDeviceContext, iPixelFormat, &kPFD), VE_TRUE);
	m_hRenderContext = wglCreateContext(m_hDeviceContext);
	wglMakeCurrent(m_hDeviceContext, m_hRenderContext);
	VeLoadOpenGL();
	wglSwapIntervalEXT(g_pDevice->ReadConfig("video", "sync", true) ? 1 : 0);
	UpdateBufferSize();
	VeUInt32 u32WidthBak = GetWidth();
	VeUInt32 u32HeightBak = GetHeight();
	/*if(!g_bMaximized)
	{
		UpdateFullScreen();
	}*/
	if(u32WidthBak == GetWidth() && u32HeightBak == GetHeight())
	{
		OnBufferResized(GetWidth(), GetHeight());
	}

#elif defined(VE_PLATFORM_LINUX)

	g_pkDisplay = XOpenDisplay(NULL);
	VE_ASSERT(g_pkDisplay);
	int iErrorBase, iEventBase;
	VE_ASSERT_EQ(glXQueryExtension(g_pkDisplay, &iErrorBase, &iEventBase), true);

	m_hAtomDeleteWindow = XInternAtom(g_pkDisplay, "WM_DELETE_WINDOW", True);
	m_hAtomFullScreen = XInternAtom(g_pkDisplay, "_NET_WM_STATE_FULLSCREEN", True);
	m_hAtomState = XInternAtom(g_pkDisplay, "_NET_WM_STATE", True);
	VeInt32 i32Dummy;
	if(XQueryExtension(g_pkDisplay, "RANDR", &i32Dummy, &i32Dummy, &i32Dummy))
	{
		XRRScreenConfiguration* pkScreenConfig;
		pkScreenConfig = XRRGetScreenInfo(g_pkDisplay, DefaultRootWindow(g_pkDisplay));
		VE_ASSERT(pkScreenConfig);
		XRRScreenSize* pkScreenSizes;
		VeInt32 i32SizesNum(0);
		Rotation kCurrentRotation;
		VeInt32 i32CurrentSizeID = XRRConfigCurrentConfiguration(pkScreenConfig, &kCurrentRotation);
		pkScreenSizes = XRRConfigSizes(pkScreenConfig, &i32SizesNum);
		m_kOriginMode.m_u32Width = pkScreenSizes[i32CurrentSizeID].width;
		m_kOriginMode.m_u32Height = pkScreenSizes[i32CurrentSizeID].height;
		m_kOriginMode.m_u32Rate = XRRConfigCurrentRate(pkScreenConfig);
		for(VeInt32 iSizeID(0); iSizeID < i32SizesNum; ++iSizeID)
		{
			VeInt16* pi16Rates;
			VeInt32 i32RatesNum(0);
			pi16Rates = XRRConfigRates(pkScreenConfig, iSizeID, &i32RatesNum);
			for(VeInt32 iRate(0); iRate < i32RatesNum; ++iRate)
			{
				VideoMode kMode;
				kMode.m_u32Width = pkScreenSizes[iSizeID].width;
				kMode.m_u32Height = pkScreenSizes[iSizeID].height;
				kMode.m_u32Rate = pi16Rates[iRate];
				m_kModeList.PushBack(kMode);
			}
		}
		XRRFreeScreenConfigInfo(pkScreenConfig);
	}
	else
	{
		m_kOriginMode.m_u32Width = DisplayWidth(g_pkDisplay, DefaultScreen(g_pkDisplay));
		m_kOriginMode.m_u32Height = DisplayHeight(g_pkDisplay, DefaultScreen(g_pkDisplay));
		m_kOriginMode.m_u32Rate = 0;
		m_kModeList.PushBack(m_kOriginMode);
	}

	int aiVisual[] =
	{
		GLX_RGBA,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, 24,
		GLX_STENCIL_SIZE, 8,
		GLX_DOUBLEBUFFER,
		None
	};
	XVisualInfo* pkVisualInfo = glXChooseVisual(g_pkDisplay, DefaultScreen(g_pkDisplay), aiVisual);
	VE_ASSERT(pkVisualInfo);

	m_hContext = glXCreateContext(g_pkDisplay, pkVisualInfo, NULL, GL_TRUE);
	VE_ASSERT(m_hContext);

	g_kWindowAttr.colormap = XCreateColormap(g_pkDisplay, RootWindow(g_pkDisplay, pkVisualInfo->screen), pkVisualInfo->visual, AllocNone);
	g_kWindowAttr.border_pixel = 0;
	g_kWindowAttr.background_pixel = 0;
	g_kWindowAttr.event_mask = StructureNotifyMask | VisibilityChangeMask | FocusChangeMask;

#	ifdef VE_INPUT_KEYBOARD
	g_kWindowAttr.event_mask |= KeyPressMask;
	g_kWindowAttr.event_mask |= KeyReleaseMask;
#	endif

#	ifdef VE_INPUT_MOUSE
	g_kWindowAttr.event_mask |= ButtonPressMask;
	g_kWindowAttr.event_mask |= ButtonReleaseMask;
	g_kWindowAttr.event_mask |= PointerMotionMask;
#	endif

	VeUInt32 u32Mask = CWBorderPixel | CWColormap | CWEventMask;

	VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
	switch(eStyle)
	{
	case VeStringParser::STYLE_POPUP:
		g_kWindowAttr.backing_store = NotUseful;
		g_kWindowAttr.save_under = False;
		g_kWindowAttr.override_redirect = True;
		u32Mask |= CWSaveUnder | CWBackingStore | CWOverrideRedirect;
		break;
	default:
		break;
	}
	VeInt32 i32Left(0), i32Top(0);
	VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
	VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
	switch(eDock)
	{
	case VeStringParser::DOCK_CENTER:
		{
			Screen& kScreen = ((_XPrivDisplay)g_pkDisplay)->screens[pkVisualInfo->screen];
			VeInt32 i32ScreenW = kScreen.width;
			VeInt32 i32ScreenH = kScreen.height;
			i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1);
			i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1);
		}
		break;
	default:
		break;
	}

	g_hWindow = XCreateWindow(g_pkDisplay,
		RootWindow(g_pkDisplay, pkVisualInfo->screen),
		i32Left, i32Top,
		kResolution.m_u32Width, kResolution.m_u32Height,
		0,
		pkVisualInfo->depth,
		InputOutput,
		pkVisualInfo->visual,
		u32Mask,
		&g_kWindowAttr);

	VE_ASSERT(g_hWindow);

	XSetStandardProperties(g_pkDisplay, g_hWindow, g_kParams.m_ptcApplicationName, NULL, None, g_kParams.m_ppcArgv, g_kParams.m_iArgc, NULL);

	glXMakeCurrent(g_pkDisplay, g_hWindow, m_hContext);

	VeLoadOpenGL();

	XMapWindow(g_pkDisplay, g_hWindow);

	XMoveWindow(g_pkDisplay, g_hWindow, i32Left, i32Top);

	glXSwapIntervalSGI(g_pStartConfig->IsSync() ? 1 : 0);

	g_bHasShowWindow = true;
	UpdateBufferSize();
	VeUInt32 u32WidthBak = GetWidth();
	VeUInt32 u32HeightBak = GetHeight();
	UpdateFullScreen();
	if(u32WidthBak == GetWidth() && u32HeightBak == GetHeight())
	{
		OnBufferResized(GetWidth(), GetHeight());
	}
    
#elif defined(VE_PLATFORM_OSX)
    
    VeLoadOpenGL();

#endif

	GLInitGlobal();

	m_bInited = true;
}
//--------------------------------------------------------------------------
void VeRendererGL::Term()
{
	VE_ASSERT(m_bInited);

	GLTermGlobal();

	VeUnloadOpenGL();

#if defined(VE_PLATFORM_WIN)
	
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRenderContext);
	m_hRenderContext = NULL;
	ReleaseDC(((VeWindows*)g_pDevice)->GetWindowHandle(), m_hDeviceContext);
	m_hDeviceContext = NULL;

#endif

	/*if(g_bFullscreenInactive)
	{
		g_pStartConfig->SetFullScreen(true);
		g_bFullscreenInactive = false;
	}*/

	m_bInited = false;
}
//--------------------------------------------------------------------------
void VeRendererGL::InitEditor()
{
	VE_ASSERT(!m_bInited);
	VeLoadOpenGL();
#if defined(VE_PLATFORM_WIN)
	if(wglSwapIntervalEXT)
	{
		wglSwapIntervalEXT(1);
	}
#elif defined(VE_PLATFORM_LINUX)
	if(glXSwapIntervalSGI)
	{
		glXSwapIntervalSGI(1);
	}
#endif

	GLInitGlobal();

	m_bInited = true;
}
//--------------------------------------------------------------------------
void VeRendererGL::TermEditor()
{
	VE_ASSERT(m_bInited);

	GLTermGlobal();

	VeUnloadOpenGL();

	m_bInited = false;
}
//--------------------------------------------------------------------------
void VeRendererGL::Render()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//--------------------------------------------------------------------------
void VeRendererGL::Present()
{
#if defined(VE_PLATFORM_WIN)
	SwapBuffers(m_hDeviceContext);
#elif defined(VE_PLATFORM_LINUX)
	glXSwapBuffers(g_pkDisplay, g_hWindow);
#endif
}
//--------------------------------------------------------------------------
void VeRendererGL::OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height)
{
	/*if(g_pStartConfig && (!g_bMaximized) && (!g_bFullscreen))
	{
		g_pStartConfig->SetResolution(u32Width, u32Height);
	}
	g_pApplication->OnBufferResized(u32Width, u32Height);*/
}
//--------------------------------------------------------------------------
void VeRendererGL::SetFullScreen(bool bEnable)
{
	/*bool bFullscreen = g_pStartConfig->IsFullScreen();
	if(bFullscreen != bEnable)
	{
		g_pStartConfig->SetFullScreen(bEnable);
		UpdateFullScreen();
	}*/
}
//--------------------------------------------------------------------------
//void VeRendererGL::SetDisplay(Display& kDisplay)
//{
	/*g_pStartConfig->SetWinStyle(kDisplay.m_eWinStyle);
	g_pStartConfig->SetResolution(kDisplay.m_u32Width, kDisplay.m_u32Height);
	g_pStartConfig->SetFormat(kDisplay.m_eFormat);
	g_pStartConfig->SetFullScreen(kDisplay.m_bFullscreen ? true : false);
	g_pStartConfig->SetOutput(kDisplay.m_u32Output);
	g_pStartConfig->SetRefreshRate(kDisplay.m_u32RefreshRate);
	UpdateFullScreen();*/
//}
//--------------------------------------------------------------------------
void VeRendererGL::ResizeBuffer(VeUInt32 u32Width, VeUInt32 u32Height)
{
	if(GetWidth() != u32Width || GetHeight() != u32Height)
	{
		SetScreenSize(u32Width, u32Height);
		OnBufferResized(u32Width, u32Height);
	}
}
//--------------------------------------------------------------------------
void VeRendererGL::GLInitGlobal()
{
	m_kDescription.m_kVendor = (const VeChar8*)glGetString(GL_VENDOR);
	m_kDescription.m_kRenderer = (const VeChar8*)glGetString(GL_RENDERER);
	m_kDescription.m_kVersion = (const VeChar8*)glGetString(GL_VERSION);
	m_kDescription.m_kGLSLVersion = (const VeChar8*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	VeUInt32 u32Pos = m_kDescription.m_kVersion.Find(".");
	m_kDescription.m_u16VersionMajoy = m_kDescription.m_kVersion.GetAt(u32Pos - 1) - '0';
	m_kDescription.m_u16VersionMinor = m_kDescription.m_kVersion.GetAt(u32Pos + 1) - '0';
	u32Pos = m_kDescription.m_kGLSLVersion.Find(".");
	m_kDescription.m_u16GLSLVersionMajoy = m_kDescription.m_kGLSLVersion.GetAt(u32Pos - 1) - '0';
	m_kDescription.m_u16GLSLVersionMinor = m_kDescription.m_kGLSLVersion.GetAt(u32Pos + 1) - '0';

	VE_LOG_D("Venus3D", "GL_VENDOR: %s", (const VeChar8*)m_kDescription.m_kVendor);
	VE_LOG_D("Venus3D", "GL_RENDERER: %s", (const VeChar8*)m_kDescription.m_kRenderer);
	VE_LOG_D("Venus3D", "GL_VERSION: %s", (const VeChar8*)m_kDescription.m_kVersion);
	VE_LOG_D("Venus3D", "GL_SHADING_LANGUAGE_VERSION: %s", (const VeChar8*)m_kDescription.m_kGLSLVersion);

	VeChar8* pcExtensions = (VeChar8*)glGetString(GL_EXTENSIONS);
	VeChar8* pcContent;
	VeChar8* pcTemp = VeStrtok(pcExtensions, " ", &pcContent);
	while(pcTemp)
	{
		m_kDescription.m_kExtensionMap[pcTemp] = m_kDescription.m_kExtensionArray.Size();
		m_kDescription.m_kExtensionArray.PushBack(pcTemp);
		VE_LOG_D("Venus3D", "GL_EXTENSION: %s", (const VeChar8*)m_kDescription.m_kExtensionArray.Back());
		pcTemp = VeStrtok(NULL, " ", &pcContent);
	}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}
//--------------------------------------------------------------------------
void VeRendererGL::GLTermGlobal()
{
	m_kDescription.m_kVendor = "";
	m_kDescription.m_kRenderer = "";
	m_kDescription.m_kVersion = "";
	m_kDescription.m_kGLSLVersion = "";
	m_kDescription.m_u16VersionMajoy = 0;
	m_kDescription.m_u16VersionMinor = 0;
	m_kDescription.m_u16GLSLVersionMajoy = 0;
	m_kDescription.m_u16GLSLVersionMinor = 0;
	m_kDescription.m_kExtensionMap.Clear();
	m_kDescription.m_kExtensionArray.Clear();
}
//--------------------------------------------------------------------------
void VeRendererGL::GLCacheInit()
{
	VeZeroMemory(m_au32BindBuffers, sizeof(m_au32BindBuffers));
	m_u32BindRenderBuffer = 0;
	m_u32UsedProgram = 0;
	VeZeroMemory(m_abVertexAttribArrayState, sizeof(m_abVertexAttribArrayState));
}
//--------------------------------------------------------------------------
void VeRendererGL::BindBuffer(VeUInt32 u32Target, VeUInt32 u32Buffer)
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
void VeRendererGL::BindRenderBuffer(VeUInt32 u32Buffer)
{
	if(m_u32BindRenderBuffer != u32Buffer)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, u32Buffer);
		m_u32BindRenderBuffer = u32Buffer;
	}
}
//--------------------------------------------------------------------------
void VeRendererGL::UseProgram(VeUInt32 u32Program)
{
	if(u32Program != m_u32UsedProgram)
	{
		glUseProgram(u32Program);
		m_u32UsedProgram = u32Program;
	}
}
//--------------------------------------------------------------------------
void VeRendererGL::EnableVertexAttribArray(VeUInt32 u32Array)
{
	VE_ASSERT(u32Array < VE_GL_IA_VERTEX_ATTRIB_ARRAY_NUM);
	if(!m_abVertexAttribArrayState[u32Array])
	{
		glEnableVertexAttribArray(u32Array);
		m_abVertexAttribArrayState[u32Array] = true;
	}
}
//--------------------------------------------------------------------------
void VeRendererGL::DisableVertexAttribArray(VeUInt32 u32Array)
{
	VE_ASSERT(u32Array < VE_GL_IA_VERTEX_ATTRIB_ARRAY_NUM);
	if(m_abVertexAttribArrayState[u32Array])
	{
		glDisableVertexAttribArray(u32Array);
		m_abVertexAttribArrayState[u32Array] = false;
	}
}
//--------------------------------------------------------------------------
#if defined(VE_PLATFORM_WIN)
//--------------------------------------------------------------------------
void VeRendererGL::ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height)
{
	/*if(!m_bFullScreen)
	{
		VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
		if(kResolution.m_u32Width != u32Width || kResolution.m_u32Height != u32Height)
		{
			g_pStartConfig->SetResolution(u32Width, u32Height);
			kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
			DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
			VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
			switch(eStyle)
			{
			case VeStringParser::STYLE_FIXED:
				dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
				break;
			case VeStringParser::STYLE_VARIBLE:
				dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
				break;
			case VeStringParser::STYLE_POPUP:
				dwStyle |= WS_POPUP;
				break;
			}
			RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
			AdjustWindowRect(&kRect, dwStyle, FALSE);
			VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
			VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
			switch(eDock)
			{
			case VeStringParser::DOCK_DEFAULT:
				break;
			case VeStringParser::DOCK_CORNER:
				i32Left = 0;
				i32Top = 0;
				break;
			case VeStringParser::DOCK_CENTER:
				{
					VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
					VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
					i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
					i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
				}
				break;
			}
			SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
			SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
				SWP_NOZORDER | SWP_NOACTIVATE);
			ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
		}
	}*/
}
//--------------------------------------------------------------------------
void VeRendererGL::UpdateBufferSize()
{
	/*RECT kRect;
	GetClientRect(((VeWindows*)g_pDevice)->GetWindowHandle(), &kRect);
	SetScreenSize(kRect.right, kRect.bottom);*/
}
//--------------------------------------------------------------------------
void VeRendererGL::UpdateFullScreen()
{
	/*VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
	VeUInt32 u32RefreshRate = g_pStartConfig->GetRefreshRate();
	bool bRefreshRateChanged(false), bResolutionChanged(false);

	if(g_pStartConfig->IsFullScreen())
	{
		Output::Mode kMode(u32RefreshRate, VePair<VeUInt32,VeUInt32>(kResolution.m_u32Width, kResolution.m_u32Height));
		VeUInt32 u32Adapter = g_pStartConfig->GetAdapter();
		VeUInt32 u32Output = g_pStartConfig->GetOutput();
		Adapter& kAdapterForUse = (m_kAdapterList.Size() > u32Adapter) ? m_kAdapterList[u32Adapter] : m_kAdapterList.Back();
		Output& kOutput = (kAdapterForUse.m_kOutputList.Size() > u32Output) ? kAdapterForUse.m_kOutputList[u32Output] : kAdapterForUse.m_kOutputList.Back();
		bool bNeedChangeMode(true);
		if(!g_pStartConfig->IsMaxScreen())
		{	
			if(kOutput.m_kModeMap.Find(kMode))
				bNeedChangeMode = false;
		}
		if(bNeedChangeMode)
		{
			kResolution.m_u32Width = kOutput.m_kDefault.dmPelsWidth;
			kResolution.m_u32Height = kOutput.m_kDefault.dmPelsHeight;
			u32RefreshRate = kOutput.m_kDefault.dmDisplayFrequency;
		}
	}

	if(u32RefreshRate != m_u32RefreshRate)
	{
		bRefreshRateChanged = true;
	}
	if(kResolution.m_u32Width != GetWidth() || kResolution.m_u32Height != GetHeight())
	{
		bResolutionChanged = true;
	}

	if(g_pStartConfig->IsFullScreen())
	{
		if(m_bFullScreen)
		{
			if(bResolutionChanged)
			{
				ChangeDisplaySettings(NULL, 0);
				SetWindowPos(g_hWindow, HWND_TOPMOST, 0, 0, kResolution.m_u32Width, kResolution.m_u32Height, SWP_NOACTIVATE);
				ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
			}
			if(bResolutionChanged || bRefreshRateChanged)
			{
				VeUInt32 u32Adapter = g_pStartConfig->GetAdapter();
				VeUInt32 u32Output = g_pStartConfig->GetOutput();
				Adapter& kAdapterForUse = (m_kAdapterList.Size() > u32Adapter) ? m_kAdapterList[u32Adapter] : m_kAdapterList.Back();
				Output& kOutput = (kAdapterForUse.m_kOutputList.Size() > u32Output) ? kAdapterForUse.m_kOutputList[u32Output] : kAdapterForUse.m_kOutputList.Back();
				Output::Mode kMode(u32RefreshRate, VePair<VeUInt32,VeUInt32>(kResolution.m_u32Width, kResolution.m_u32Height));
				VeUInt32* pu32ModeIndex = kOutput.m_kModeMap.Find(kMode);
				VE_ASSERT(pu32ModeIndex);
				DEVMODE kDevMode = kOutput.m_kModeList[*pu32ModeIndex];
				if(!(kOutput.m_kDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
				{
					kDevMode.dmPosition.x += m_i32DeviceHorzers;
					kDevMode.dmFields = DM_POSITION;
					ChangeDisplaySettingsEx((LPSTR)kOutput.m_kDevice.DeviceName, &kDevMode, NULL, CDS_NORESET|CDS_UPDATEREGISTRY, NULL);
					ChangeDisplaySettings(NULL, 0);  
				}
				ChangeDisplaySettingsEx((LPSTR)kOutput.m_kDevice.DeviceName, &kDevMode, g_hWindow, CDS_FULLSCREEN, NULL);
			}
		}
		else
		{
			g_bFullscreen = true;
			DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_POPUP;
			SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
			SetWindowPos(g_hWindow, HWND_TOPMOST, 0, 0, kResolution.m_u32Width, kResolution.m_u32Height, SWP_NOACTIVATE);
			SetWindowPos(g_hWindow, 0, 0,0, 0,0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
			if(bResolutionChanged)
			{
				ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
			}
			VeUInt32 u32Adapter = g_pStartConfig->GetAdapter();
			VeUInt32 u32Output = g_pStartConfig->GetOutput();
			Adapter& kAdapterForUse = (m_kAdapterList.Size() > u32Adapter) ? m_kAdapterList[u32Adapter] : m_kAdapterList.Back();
			Output& kOutput = (kAdapterForUse.m_kOutputList.Size() > u32Output) ? kAdapterForUse.m_kOutputList[u32Output] : kAdapterForUse.m_kOutputList.Back();
			Output::Mode kMode(u32RefreshRate, VePair<VeUInt32,VeUInt32>(kResolution.m_u32Width, kResolution.m_u32Height));
			VeUInt32* pu32ModeIndex = kOutput.m_kModeMap.Find(kMode);
			VE_ASSERT(pu32ModeIndex);
			DEVMODE kDevMode = kOutput.m_kModeList[*pu32ModeIndex];
			if(!(kOutput.m_kDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
			{
				kDevMode.dmPosition.x += m_i32DeviceHorzers;
				kDevMode.dmFields = DM_POSITION;
				ChangeDisplaySettingsEx((LPSTR)kOutput.m_kDevice.DeviceName, &kDevMode, NULL, CDS_NORESET|CDS_UPDATEREGISTRY, NULL);
				ChangeDisplaySettings(NULL, 0);  
			}
			ChangeDisplaySettingsEx((LPSTR)kOutput.m_kDevice.DeviceName, &kDevMode, g_hWindow, CDS_FULLSCREEN, NULL);
			m_bFullScreen = true;
		}
	}
	else if(m_bFullScreen)
	{
		g_bFullscreen = false;
		ChangeDisplaySettings(NULL, 0);
		DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
		VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
		switch(eStyle)
		{
		case VeStringParser::STYLE_FIXED:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			break;
		case VeStringParser::STYLE_VARIBLE:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
			break;
		case VeStringParser::STYLE_POPUP:
			dwStyle |= WS_POPUP;
			break;
		}
		RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
		AdjustWindowRect(&kRect, dwStyle, FALSE);
		VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
		VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
		switch(eDock)
		{
		case VeStringParser::DOCK_DEFAULT:
			break;
		case VeStringParser::DOCK_CORNER:
			i32Left = 0;
			i32Top = 0;
			break;
		case VeStringParser::DOCK_CENTER:
			{
				VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
				VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
				i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
				i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
			}
			break;
		}
		SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
		SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
			SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
		m_bFullScreen = false;
	}
	else if(bResolutionChanged)
	{
		DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
		VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
		switch(eStyle)
		{
		case VeStringParser::STYLE_FIXED:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			break;
		case VeStringParser::STYLE_VARIBLE:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
			break;
		case VeStringParser::STYLE_POPUP:
			dwStyle |= WS_POPUP;
			break;
		}
		RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
		AdjustWindowRect(&kRect, dwStyle, FALSE);
		VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
		VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
		switch(eDock)
		{
		case VeStringParser::DOCK_DEFAULT:
			break;
		case VeStringParser::DOCK_CORNER:
			i32Left = 0;
			i32Top = 0;
			break;
		case VeStringParser::DOCK_CENTER:
			{
				VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
				VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
				i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
				i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
			}
			break;
		}
		SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
		SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
	}
	else
	{
		DWORD dwPreStyle = GetWindowLong(g_hWindow, GWL_STYLE);
		DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
		VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
		switch(eStyle)
		{
		case VeStringParser::STYLE_FIXED:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			break;
		case VeStringParser::STYLE_VARIBLE:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
			break;
		case VeStringParser::STYLE_POPUP:
			dwStyle |= WS_POPUP;
			break;
		}
		if(dwStyle != dwPreStyle)
		{
			RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
			AdjustWindowRect(&kRect, dwStyle, FALSE);
			VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
			VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
			switch(eDock)
			{
			case VeStringParser::DOCK_DEFAULT:
				break;
			case VeStringParser::DOCK_CORNER:
				i32Left = 0;
				i32Top = 0;
				break;
			case VeStringParser::DOCK_CENTER:
				{
					VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
					VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
					i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
					i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
				}
				break;
			}
			SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
			SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
				SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}*/
}
//--------------------------------------------------------------------------
//VeUInt32 VeRendererGL::Output::KeyToHashCode( const Mode& kKey, VeUInt32 u32TableSize )
//{
//	return (kKey.m_tFirst * kKey.m_tSecond.m_tFirst * kKey.m_tSecond.m_tSecond) % u32TableSize;
//}
//--------------------------------------------------------------------------
void VeRendererGL::OnActive()
{
	/*if(g_bFullscreenInactive)
	{
		SetFullScreen(true);
		g_bFullscreenInactive = false;
	}*/
}
//--------------------------------------------------------------------------
void VeRendererGL::OnInactive()
{
	/*if(m_bFullScreen)
	{
		g_bFullscreenInactive = true;
		SetFullScreen(false);
	}*/
}
//--------------------------------------------------------------------------
#elif defined(VE_PLATFORM_LINUX)
//--------------------------------------------------------------------------
void VeRendererGL::ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height)
{
	if(!m_bFullScreen)
	{
		VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
		if(kResolution.m_u32Width != u32Width || kResolution.m_u32Height != u32Height)
		{
			g_bHasShowWindow = false;
			g_pStartConfig->SetResolution(u32Width, u32Height);
			kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
			VeInt32 i32Left(0), i32Top(0);
			VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
			switch(eDock)
			{
			case VeStringParser::DOCK_CENTER:
				{
					VeInt32 i32ScreenW = DisplayWidth(g_pkDisplay, DefaultScreen(g_pkDisplay));
					VeInt32 i32ScreenH = DisplayHeight(g_pkDisplay, DefaultScreen(g_pkDisplay));
					i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1);
					i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1);
				}
				break;
			default:
				break;
			}
			XMoveWindow(g_pkDisplay, g_hWindow, i32Left, i32Top);
			XResizeWindow(g_pkDisplay, g_hWindow, kResolution.m_u32Width, kResolution.m_u32Height);
			ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
			g_bHasShowWindow = true;
		}
	}

}
//--------------------------------------------------------------------------
void VeRendererGL::UpdateBufferSize()
{
	XWindowAttributes kWindowAttrib;
	XGetWindowAttributes(g_pkDisplay, g_hWindow, &kWindowAttrib);
	SetScreenSize(kWindowAttrib.width, kWindowAttrib.height);
}
//--------------------------------------------------------------------------
void VeRendererGL::UpdateFullScreen()
{
	VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
	VeUInt32 u32RefreshRate = g_pStartConfig->GetRefreshRate();
	bool bRefreshRateChanged(false), bResolutionChanged(false);

	if(g_pStartConfig->IsFullScreen())
	{
		VideoMode kMode;
		kMode.m_u32Width = kResolution.m_u32Width;
		kMode.m_u32Height = kResolution.m_u32Height;
		kMode.m_u32Rate = u32RefreshRate;
		bool bNeedChangeMode(true);
		if(!g_pStartConfig->IsMaxScreen())
		{
			for(VeVector<VideoMode>::iterator it = m_kModeList.Begin(); it != m_kModeList.End(); ++it)
			{
				if(it->m_u32Width == kMode.m_u32Width
					&& it->m_u32Height == kMode.m_u32Height
					&& it->m_u32Rate == kMode.m_u32Rate)
				{
					bNeedChangeMode = false;
					break;
				}
			}
		}
		if(bNeedChangeMode)
		{
			kResolution.m_u32Width = m_kOriginMode.m_u32Width;
			kResolution.m_u32Height = m_kOriginMode.m_u32Height;
			u32RefreshRate = m_kOriginMode.m_u32Rate;
		}
	}

	if(u32RefreshRate != m_u32RefreshRate)
	{
		bRefreshRateChanged = true;
	}
	if(kResolution.m_u32Width != GetWidth() || kResolution.m_u32Height != GetHeight())
	{
		bResolutionChanged = true;
	}

	if(g_pStartConfig->IsFullScreen())
	{
		VE_ASSERT(m_hAtomFullScreen);
		if(bRefreshRateChanged || bResolutionChanged)
		{
			VeInt32 i32Size(0), i32NewSize(-1);
			VideoMode* pkNewMode(NULL);
			for(VeUInt32 i(0); i < m_kModeList.Size(); ++i)
			{
				VideoMode& kIterMode = m_kModeList[i];
				if(kIterMode.m_u32Width == kResolution.m_u32Width && kIterMode.m_u32Height == kResolution.m_u32Height)
				{
					i32NewSize = i32Size;
					pkNewMode = &kIterMode;
				}

				VideoMode* pkLastMode = &kIterMode;
				while((++i) < m_kModeList.Size()
					&& m_kModeList[i].m_u32Width == pkLastMode->m_u32Width
					&& m_kModeList[i].m_u32Height == pkLastMode->m_u32Height)
				{
					if(pkLastMode == pkNewMode && m_kModeList[i].m_u32Rate == u32RefreshRate)
					{
						pkNewMode = &m_kModeList[i];
					}
				}
				++i32Size;
			}

			XRRScreenConfiguration* pkScreenConfig = XRRGetScreenInfo(g_pkDisplay, DefaultRootWindow(g_pkDisplay));
			if(pkScreenConfig)
			{
				Rotation kCurrentRotation;
				XRRConfigCurrentConfiguration(pkScreenConfig, &kCurrentRotation);
				XRRSetScreenConfigAndRate(g_pkDisplay, pkScreenConfig, DefaultRootWindow(g_pkDisplay)
					, i32NewSize, kCurrentRotation, pkNewMode->m_u32Rate, CurrentTime);
				XRRFreeScreenConfigInfo(pkScreenConfig);
			}
		}

		if(!m_bFullScreen)
		{
			g_bFullscreen = true;
			XClientMessageEvent kMessage;
			kMessage.type = ClientMessage;
			kMessage.serial = 0;
			kMessage.send_event = True;
			kMessage.window = g_hWindow;
			kMessage.message_type = m_hAtomState;
			kMessage.format = 32;
			kMessage.data.l[0] = 1;
			kMessage.data.l[1] = m_hAtomFullScreen;
			kMessage.data.l[2] = 0;
			XSendEvent(g_pkDisplay, DefaultRootWindow(g_pkDisplay), False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent*)&kMessage);
			if(bResolutionChanged)
			{
				ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
			}
			m_bFullScreen = true;
		}
	}
	else if(m_bFullScreen)
	{
		XRRScreenConfiguration* pkScreenConfig = XRRGetScreenInfo(g_pkDisplay, DefaultRootWindow(g_pkDisplay));
		if(pkScreenConfig)
		{
			Rotation kCurrentRotation;
			XRRConfigCurrentConfiguration(pkScreenConfig, &kCurrentRotation);
			XRRSetScreenConfigAndRate(g_pkDisplay, pkScreenConfig, DefaultRootWindow(g_pkDisplay)
				, 0, kCurrentRotation, m_kOriginMode.m_u32Rate, CurrentTime);
			XRRFreeScreenConfigInfo(pkScreenConfig);
		}
		XClientMessageEvent kMessage;
		kMessage.type = ClientMessage;
		kMessage.serial = 0;
		kMessage.send_event = True;
		kMessage.window = g_hWindow;
		kMessage.message_type = m_hAtomState;
		kMessage.format = 32;
		kMessage.data.l[0] = 0;
		kMessage.data.l[1] = m_hAtomFullScreen;
		kMessage.data.l[2] = 0;
		XSendEvent(g_pkDisplay, DefaultRootWindow(g_pkDisplay), False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent*)&kMessage);
		if(bResolutionChanged)
		{
			ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
		}
		g_bFullscreen = false;
		m_bFullScreen = false;
	}
	else if(bResolutionChanged)
	{
		g_bHasShowWindow = false;
		VeInt32 i32Left(0), i32Top(0);
		VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
		switch(eDock)
		{
		case VeStringParser::DOCK_CENTER:
			{
				VeInt32 i32ScreenW = DisplayWidth(g_pkDisplay, DefaultScreen(g_pkDisplay));
				VeInt32 i32ScreenH = DisplayHeight(g_pkDisplay, DefaultScreen(g_pkDisplay));
				i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1);
				i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1);
			}
			break;
		default:
			break;
		}
		XMoveWindow(g_pkDisplay, g_hWindow, i32Left, i32Top);
		XResizeWindow(g_pkDisplay, g_hWindow, kResolution.m_u32Width, kResolution.m_u32Height);
		ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
		g_bHasShowWindow = true;
	}
}
//--------------------------------------------------------------------------
void VeRendererGL::OnActive()
{

}
//--------------------------------------------------------------------------
void VeRendererGL::OnInactive()
{

}
//--------------------------------------------------------------------------
#elif defined(VE_PLATFORM_OSX)
//--------------------------------------------------------------------------
void VeRendererGL::ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height)
{
    
}
//--------------------------------------------------------------------------
void VeRendererGL::UpdateBufferSize()
{
    
}
//--------------------------------------------------------------------------
void VeRendererGL::UpdateFullScreen()
{
    
}
//--------------------------------------------------------------------------
void VeRendererGL::OnActive()
{

}
//--------------------------------------------------------------------------
void VeRendererGL::OnInactive()
{

}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
