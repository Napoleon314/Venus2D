////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeDevice.cpp
//  Version:     v1.00
//  Created:     17/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeDevice.inl"
#endif
#if defined(VE_PLATFORM_WIN)
#   include "Windows/_VeWindows.h"
#	elif defined(VE_PLATFORM_MOBILE_SIM)
#	include "MobileSim/_VeMobileSim.h"
#elif defined(VE_PLATFORM_IOS)
#   include "IOS/_VeIOS.h"
#elif defined(VE_PLATFORM_ANDROID)
#	include "Android/_VeAndroid.h"
#endif

//--------------------------------------------------------------------------
VeDevice::VeDevice(Type eType, VeStartParams& kParams)
	: m_eType(eType), m_kParams(kParams), m_pkWindow(NULL)
	, m_eLanguage(ZH_CN), m_bInited(false), m_bLuaDebug(false)
{
	VePowerExport();
	VeMainExport();
	VeInitDelegate(VeDevice, OnConfigSaved);
#	if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
	{
		VeChar8 acBuffer[64];
		VeChar8 acVolumelabel[20];
		DWORD dwSerialNumber;
		DWORD dwMaxCLength;
		DWORD dwFileSysFlag;
		VeChar8 acFileSysName[10];
		GetVolumeInformation( "C:\\",acVolumelabel,255,&dwSerialNumber,&dwMaxCLength,&dwFileSysFlag,acFileSysName,255);
		VeSprintf(acBuffer, "0x%x", dwSerialNumber);
		m_kDeviceID = acBuffer;
	}
	{
		VeChar16 acBuffer[64];
		DWORD dwLen;
		VE_ASSERT_EQ(GetUserNameW(acBuffer, &dwLen), TRUE);
		VeVector<VeChar8> kBuffer;
		for(VeUInt32 i(0); i < dwLen; ++i)
		{
			VeTextTable::AddUnicode16(kBuffer, acBuffer[i]);
		}
		kBuffer.PushBack('\0');
		m_kDeviceName = &kBuffer[0];
	}
	switch(GetSystemDefaultUILanguage())
	{
	case 0x0804:
	case 0x0c04:
	case 0x1404:
	case 0x1004:
		m_eLanguage = ZH_CN;
		break;
	case 0x0404:
		m_eLanguage = ZH_TW;
		break;
	default:
		m_eLanguage = EN_US;
		break;
	}
#	endif
}
//--------------------------------------------------------------------------
VeDevice::~VeDevice()
{

}
//--------------------------------------------------------------------------
const VeChar8* VeDevice::Translate(const VeChar8* pcKey)
{
	return VeTextTable::GetStr(m_kTransField, pcKey, LanguageLua::ToAlias(m_eLanguage));
}
//--------------------------------------------------------------------------
void VeDevice::CreateDevice(VeStartParams& kParams)
{
#	if defined(VE_PLATFORM_WIN)
	VE_NEW VeWindows(kParams);
#	elif defined(VE_PLATFORM_MOBILE_SIM)
	VE_NEW VeMobileSim(kParams);
#   elif defined(VE_PLATFORM_IOS)
    VE_NEW VeIOS(kParams);
#	elif defined(VE_PLATFORM_ANDROID)
    VE_NEW VeAndroid(kParams);
#	endif
}
//--------------------------------------------------------------------------
VeString& VeDevice::GetConfig(const VeChar8* pcGroup, const VeChar8* pcName)
{
	VE_ASSERT(pcGroup && pcName);
	return m_kConfigMap[pcGroup][pcName];
}
//--------------------------------------------------------------------------
void VeDevice::SaveConfig()
{
	VeString kConfig;
	for(VeMap<VeString, VeMap<VeString,VeString> >::iterator it = m_kConfigMap.Begin();
		it != m_kConfigMap.End(); ++it)
	{
		if(it != m_kConfigMap.Begin())
		{
			kConfig += "\r\n";
		}
		kConfig += "[" + it->m_tFirst + "]";
		for(VeMap<VeString,VeString>::iterator iter = it->m_tSecond.Begin();
			iter != it->m_tSecond.End(); ++iter)
		{
			kConfig += "\r\n";
			kConfig += iter->m_tFirst + "=" + iter->m_tSecond;
		}
	}
	VeDirectory* pkDir(NULL);
	if((!pkDir) && m_kParams.m_pcConfigCustomDir)
	{
		pkDir = g_pResourceManager->CreateDir(m_kParams.m_pcConfigCustomDir);
		if(pkDir && (!pkDir->Access(VeDirectory::ACCESS_W_OK)))
		{
			g_pResourceManager->DestoryDir(pkDir);
			pkDir = NULL;
		}
	}
	if(pkDir)
	{
        if(kConfig.Length())
        {
            VeMemoryOStreamPtr spStream = VE_NEW VeMemoryOStream();
            spStream->AddBlob((const VeChar8*)kConfig, kConfig.Length());
            pkDir->WriteAsync(m_kParams.m_pcConfigName, spStream, VeDelegate(OnConfigSaved));
        }
		g_pResourceManager->DestoryDir(pkDir);
		pkDir = NULL;
	}
}
//--------------------------------------------------------------------------
void VeDevice::Start()
{
	Init();
	g_pLua->DoFileSync(m_kParams.m_pcStartupLua);
	CreateRenderWindowConfig();
	g_pRenderer->Init();
	g_pRenderer->LoadInitResource();
	g_pRenderer->CreateDefaultData();
	g_pInputManager->Init();
	g_pSceneManager->Init();
	g_pUIManager->Init();
	g_pClientManager->Start();
	VE_ASSERT(g_pApplication);
	g_pApplication->Init();

	while(!g_pApplication->IsAppQuit())
	{
		_PumpEvents();
		g_pApplication->Update();
		//g_pRenderer->Render();
		//g_pRenderer->Present();
	}

	g_pApplication->Term();
	g_pClientManager->End();
	g_pUIManager->Term();
	g_pSceneManager->Term();
	g_pInputManager->Term();
	g_pResourceManager->TermRender();
	g_pRenderer->Term();
	DestoryRenderWindowConfig();
	Term();
}
//--------------------------------------------------------------------------
void VeDevice::Init()
{
	if(!m_bInited)
	{
		ParseCmdLine();
		VeLogger::SetLog(m_bLuaDebug
			? VeLogger::OUTPUT_LUASTUDIO
			: VeLogger::OUTPUT_DEBUGOUTPUT);
		VE_NEW VeLua(m_bLuaDebug);
		_Init();
		VE_NEW VeTime();
		VE_NEW VeResourceManager();
		VE_NEW VeURL();
		LoadConfig();
		VE_NEW VeInputManager();
		VeRenderer::CreateRenderer(VeRenderer::API_MASK);
		VE_NEW VeRenderFrameManager();
		VE_NEW VeTweenEasing();
		VE_NEW VeUIManager();
		VE_NEW VeSceneManager();
		VE_NEW VeAudioSystem();
		VE_NEW VeClientManager();
		m_bInited = true;
	}
}
//--------------------------------------------------------------------------
void VeDevice::Term()
{
	if(m_bInited)
	{
		VeApplication::Destory();
		SaveConfig();
		VeLua::Destory();
		VeClientManager::Destory();
		VeAudioSystem::Destory();
		VeSceneManager::Destory();
		VeUIManager::Destory();
		VeTweenEasing::Destory();
		VeRenderFrameManager::Destory();
		VeRenderer::Destory();
		VeInputManager::Destory();
		VeURL::Destory();
		VeResourceManager::Destory();
		VeTime::Destory();
		_Term();
		VeLogger::SetLog(VeLogger::OUTPUT_MAX);
		m_bInited = false;
	}
}
//--------------------------------------------------------------------------
void VeDevice::CreateRenderWindowConfig()
{
	VE_ASSERT(!m_pkWindow);
	VeInt32 x = VE_WINDOWPOS_UNDEFINED;//ReadConfig("video", "window_left", VE_WINDOWPOS_UNDEFINED, false);
	VeInt32 y = VE_WINDOWPOS_UNDEFINED;//ReadConfig("video", "window_top", VE_WINDOWPOS_UNDEFINED, false);
	VeInt32 w = ReadConfig("video", "window_width", 640, false);
	VeInt32 h = ReadConfig("video", "window_height", 480, false);
	VeUInt32 u32Flags(0);
	if(ReadConfig("video", "borderless", false)) u32Flags |= WINDOW_BORDERLESS;
	if(ReadConfig("video", "resizable", false)) u32Flags |= WINDOW_RESIZABLE;
	if(ReadConfig("video", "fullscreen", false)) u32Flags |= WINDOW_FULLSCREEN;
	CreateRenderWindow(m_kParams.m_pcAppName, x, y, w, h, u32Flags);
}
//--------------------------------------------------------------------------
void VeDevice::DestoryRenderWindowConfig()
{
	VE_ASSERT(m_pkWindow);
	//WriteConfig("video", "window_left", m_pkWindow->x);
	//WriteConfig("video", "window_top", m_pkWindow->y);
	WriteConfig("video", "window_width", m_pkWindow->w);
	WriteConfig("video", "window_height", m_pkWindow->h);
	WriteConfig("video", "borderless", VE_MASK_HAS_ANY(m_pkWindow->m_u32Flags, WINDOW_BORDERLESS));
	WriteConfig("video", "borderless", VE_MASK_HAS_ANY(m_pkWindow->m_u32Flags, WINDOW_BORDERLESS));
	WriteConfig("video", "fullscreen", VE_MASK_HAS_ANY(m_pkWindow->m_u32Flags, WINDOW_BORDERLESS));
	DestoryRenderWindow();
}
//--------------------------------------------------------------------------
#define CREATE_FLAGS \
	(WINDOW_OPENGL | WINDOW_BORDERLESS | WINDOW_RESIZABLE | WINDOW_ALLOW_HIGHDPI)
//--------------------------------------------------------------------------
void VeDevice::CreateRenderWindow(const VeChar8* pcTitle,
	VeInt32 x, VeInt32 y, VeInt32 w, VeInt32 h, VeUInt32 u32Flags)
{
	VE_ASSERT(m_bInited && (!m_pkWindow));
	w = w < 1 ? 1 : w;
	h = h < 1 ? 1 : h;
	m_pkWindow = VE_NEW Window();
	m_pkWindow->x = x;
	m_pkWindow->y = y;
	m_pkWindow->w = w;
	m_pkWindow->h = h;
	if(VE_WINDOWPOS_ISUNDEFINED(x) || VE_WINDOWPOS_ISUNDEFINED(y) ||
		VE_WINDOWPOS_ISCENTERED(x) || VE_WINDOWPOS_ISCENTERED(y))
	{
		VideoDisplay* pkDisplay = GetDisplayForWindow(m_pkWindow);
		if(pkDisplay)
		{
			VeRect kBounds;
			VeInt32 i32DisplayIndex = GetIndexOfDisplay(pkDisplay);
			GetDisplayBounds(i32DisplayIndex, kBounds);
			if(VE_WINDOWPOS_ISUNDEFINED(x) || VE_WINDOWPOS_ISCENTERED(x))
			{
				m_pkWindow->x = kBounds.x + (kBounds.w - w) / 2;
			}
			if(VE_WINDOWPOS_ISUNDEFINED(y) || VE_WINDOWPOS_ISCENTERED(y))
			{
				m_pkWindow->y = kBounds.y + (kBounds.h - h) / 2;
			}
		}
	}
	m_pkWindow->m_u32Flags = ((u32Flags & CREATE_FLAGS) | WINDOW_HIDDEN);
	m_pkWindow->m_u32LastFullscreenFlags = m_pkWindow->m_u32Flags;
	m_pkWindow->m_f32Brightness = 1.0f;
	_CreateWindow(m_pkWindow);
	if(pcTitle)
	{
		SetWindowTitle(pcTitle);
	}
	FinishWindowCreation(m_pkWindow, u32Flags);

	UpdateFullscreenMode(m_pkWindow, VE_FULLSCREEN_VISIBLE(m_pkWindow));
}
//--------------------------------------------------------------------------
void VeDevice::CreateRenderWindow(const void* pvData)
{
	VE_ASSERT(m_bInited && (!m_pkWindow));
}
//--------------------------------------------------------------------------
void VeDevice::DestoryRenderWindow()
{
	if(m_pkWindow)
	{
		_DestoryWindow(m_pkWindow);
		VE_SAFE_DELETE(m_pkWindow);
	}
}
//--------------------------------------------------------------------------
void VeDevice::SetWindowTitle(const VeChar8* pcTitle)
{
	VE_ASSERT(m_pkWindow);
	if(m_pkWindow->m_kTitle != pcTitle)
	{
		m_pkWindow->m_kTitle = pcTitle;
		_SetWindowTitle(m_pkWindow);
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeDevice::GetWindowTitle()
{
	VE_ASSERT(m_pkWindow);
	return m_pkWindow->m_kTitle;
}
//--------------------------------------------------------------------------
void VeDevice::SetWindowPosition(VeInt32 x, VeInt32 y)
{
	VE_ASSERT(m_pkWindow);
	if(VE_WINDOWPOS_ISCENTERED(x) || VE_WINDOWPOS_ISCENTERED(y))
	{
		VideoDisplay* pkDisplay = GetDisplayForWindow(m_pkWindow);
		VE_ASSERT(pkDisplay);
		VeRect kBounds;
		_GetDisplayBounds(*pkDisplay, kBounds);
		if(VE_WINDOWPOS_ISCENTERED(x))
		{
			x = kBounds.x + (kBounds.w - m_pkWindow->w) / 2;
		}
		if(VE_WINDOWPOS_ISCENTERED(y))
		{
			y = kBounds.y + (kBounds.h - m_pkWindow->h) / 2;
		}
	}
	if((m_pkWindow->m_u32Flags & WINDOW_FULLSCREEN))
	{
		if(!VE_WINDOWPOS_ISUNDEFINED(x))
		{
			m_pkWindow->m_kWindowed.x = x;
		}
		if(!VE_WINDOWPOS_ISUNDEFINED(y))
		{
			m_pkWindow->m_kWindowed.y = y;
		}
	}
	else
	{
		if(!VE_WINDOWPOS_ISUNDEFINED(x))
		{
			m_pkWindow->x = x;
		}
		if(!VE_WINDOWPOS_ISUNDEFINED(y))
		{
			m_pkWindow->y = y;
		}
		_SetWindowPosition(m_pkWindow);
		//SDL_SendWindowEvent(window, SDL_WINDOWEVENT_MOVED, x, y);
	}
}
//--------------------------------------------------------------------------
void VeDevice::GetWindowPosition(VeInt32& x, VeInt32& y)
{
	VE_ASSERT(m_pkWindow);
	if(m_pkWindow->m_u32Flags & WINDOW_FULLSCREEN)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x = m_pkWindow->x;
		y = m_pkWindow->y;
	}
}
//--------------------------------------------------------------------------
#define FULLSCREEN_MASK (WINDOW_FULLSCREEN_DESKTOP | WINDOW_FULLSCREEN)
//--------------------------------------------------------------------------
void VeDevice::SetWindowFullscreen(VeUInt32 u32Flags)
{
	VE_ASSERT(m_pkWindow);
	u32Flags &= FULLSCREEN_MASK;
	if(u32Flags != (m_pkWindow->m_u32Flags & FULLSCREEN_MASK))
	{
		m_pkWindow->m_u32Flags &= ~FULLSCREEN_MASK;
		m_pkWindow->m_u32Flags |= u32Flags;
		//UpdateFullscreenMode(window, FULLSCREEN_VISIBLE(window));
	}
}
//--------------------------------------------------------------------------
void VeDevice::ShowWindow()
{
	VE_ASSERT(m_pkWindow);

	if(m_pkWindow->m_u32Flags & WINDOW_SHOWN) return;
	_ShowWindow(m_pkWindow);
	//SDL_SendWindowEvent(window, SDL_WINDOWEVENT_SHOWN, 0, 0);
}
//--------------------------------------------------------------------------
void VeDevice::HideWindow()
{
	VE_ASSERT(m_pkWindow);

	if(!(m_pkWindow->m_u32Flags & WINDOW_SHOWN)) return;

	//UpdateFullscreenMode(window, SDL_FALSE);

	_HideWindow(m_pkWindow);

	//SDL_SendWindowEvent(window, SDL_WINDOWEVENT_HIDDEN, 0, 0);
}
//--------------------------------------------------------------------------
void VeDevice::MaximizeWindow()
{
	VE_ASSERT(m_pkWindow);
	if(m_pkWindow->m_u32Flags & WINDOW_MAXIMIZED) return;
	_MaximizeWindow(m_pkWindow);
}
//--------------------------------------------------------------------------
void VeDevice::MinimizeWindow()
{
	VE_ASSERT(m_pkWindow);
	if(m_pkWindow->m_u32Flags & WINDOW_MINIMIZED) return;
	//UpdateFullscreenMode(window, SDL_FALSE);

	_MinimizeWindow(m_pkWindow);
}
//--------------------------------------------------------------------------
VeInt32 VeDevice::GetWindowDisplayIndex(Window* pkWindow)
{
	VeInt32 i32DisplayIndex;
	VeInt32 i;
	VeInt32 i32Dist;
	VeInt32 i32Closest(-1);
	VeInt32 i32ClosestDist(0x7FFFFFFF);
	VePoint kCenter;
	VePoint kDelta;
	VeRect kRect;

	if(m_kDisplays.Empty()) return -1;

	if(VE_WINDOWPOS_ISUNDEFINED(pkWindow->x) || VE_WINDOWPOS_ISCENTERED(pkWindow->x))
	{
		i32DisplayIndex = (pkWindow->x & 0xFFFF);
		if(i32DisplayIndex >= VeInt32(m_kDisplays.Size()))
		{
			i32DisplayIndex = 0;
		}
		return i32DisplayIndex;
	}
	if(VE_WINDOWPOS_ISUNDEFINED(pkWindow->y) || VE_WINDOWPOS_ISCENTERED(pkWindow->y))
	{
		i32DisplayIndex = (pkWindow->y & 0xFFFF);
		if(i32DisplayIndex >= VeInt32(m_kDisplays.Size()))
		{
			i32DisplayIndex = 0;
		}
		return i32DisplayIndex;
	}
	for(VeInt32 i(0); i < VeInt32(m_kDisplays.Size()); ++i)
	{
		VideoDisplay* pkDisplay = &m_kDisplays[i];
		if (pkDisplay->m_pkFullscreenWindow == pkWindow)
		{
			return i;
		}
	}
	kCenter.x = pkWindow->x + pkWindow->w / 2;
	kCenter.y = pkWindow->y + pkWindow->h / 2;
	for(i = 0; i < VeInt32(m_kDisplays.Size()); ++i)
	{
		GetDisplayBounds(i, kRect);
		if(VeEnclosePoints(&kCenter, 1, &kRect, NULL))
		{
			return i;
		}
		kDelta.x = kCenter.x - (kRect.x + kRect.w / 2);
		kDelta.y = kCenter.y - (kRect.y + kRect.h / 2);
		i32Dist = (kDelta.x*kDelta.x + kDelta.y*kDelta.y);
		if(i32Dist < i32ClosestDist)
		{
			i32Closest = i;
			i32ClosestDist = i32Dist;
		}
	}
	return i32Closest;
}
//--------------------------------------------------------------------------
VeDevice::VideoDisplay* VeDevice::GetDisplayForWindow(Window* pkWindow)
{
	VeInt32 i32Index = GetWindowDisplayIndex(pkWindow);
	if(i32Index >= 0 && i32Index < VeInt32(m_kDisplays.Size()))
	{
		return &m_kDisplays[i32Index];
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
void VeDevice::EnableIME(InputMethodDelegate& kDelegate)
{
	m_kInputMethodEvent.AddDelegate(kDelegate);
	_EnableIME(m_pkWindow);
}
//--------------------------------------------------------------------------
void VeDevice::DisableIME()
{
	_DisableIME(m_pkWindow);
	m_kInputMethodEvent.Clear();
}
//--------------------------------------------------------------------------
VeInt32 VeDevice::GetIndexOfDisplay(VideoDisplay* pkDisplay)
{
	for(VeUInt32 i(0); i < m_kDisplays.Size(); ++i)
	{
		if(pkDisplay == (&m_kDisplays[i])) return i;
	}
	return 0;
}
//--------------------------------------------------------------------------
void VeDevice::GetDisplayBounds(VeInt32 i32Index, VeRect& kRect)
{
	if(i32Index >= VeInt32(m_kDisplays.Size()) || i32Index < 0) i32Index = 0;
	VideoDisplay& kDisplay = m_kDisplays[i32Index];
	_GetDisplayBounds(kDisplay, kRect);
}
//--------------------------------------------------------------------------
void VeDevice::_GetDisplayBounds(VideoDisplay& kDisplay, VeRect& kRect)
{
	VeInt32 i32Index = GetIndexOfDisplay(&kDisplay);
	if(!i32Index)
	{
		kRect.x = 0;
		kRect.y = 0;
	}
	else
	{
		GetDisplayBounds(i32Index - 1, kRect);
		kRect.x += kRect.w;
	}
	kRect.w = kDisplay.m_kCurrentMode.w;
	kRect.h = kDisplay.m_kCurrentMode.h;
}
//--------------------------------------------------------------------------
void VeDevice::UpdateFullscreenMode(Window* window, bool fullscreen)
{
//	VideoDisplay *display;
//	Window* other;
//
////#ifdef __MACOSX__
////	if (Cocoa_SetWindowFullscreenSpace(window, fullscreen)) {
////		window->last_fullscreen_flags = window->flags;
////		return;
////	}
////#endif
//
//	display = GetDisplayForWindow(window);
//
//	if((display->m_pkFullscreenWindow == window) == fullscreen)
//	{
//		if((window->m_u32LastFullscreenFlags & FULLSCREEN_MASK)
//			== (window->m_u32Flags & FULLSCREEN_MASK))
//			return;
//	}
//
//	for (other = _this->windows; other; other = other->next) {
//		SDL_bool setDisplayMode = SDL_FALSE;
//
//		if (other == window) {
//			setDisplayMode = fullscreen;
//		} else if (FULLSCREEN_VISIBLE(other) &&
//			SDL_GetDisplayForWindow(other) == display) {
//				setDisplayMode = SDL_TRUE;
//		}
//
//		if (setDisplayMode) {
//			SDL_DisplayMode fullscreen_mode;
//
//			if (SDL_GetWindowDisplayMode(other, &fullscreen_mode) == 0) {
//				SDL_bool resized = SDL_TRUE;
//
//				if (other->w == fullscreen_mode.w && other->h == fullscreen_mode.h) {
//					resized = SDL_FALSE;
//				}
//
//				/* only do the mode change if we want exclusive fullscreen */
//				if ((window->flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != SDL_WINDOW_FULLSCREEN_DESKTOP) {
//					SDL_SetDisplayModeForDisplay(display, &fullscreen_mode);
//				} else {
//					SDL_SetDisplayModeForDisplay(display, NULL);
//				}
//
//				if (_this->SetWindowFullscreen) {
//					_this->SetWindowFullscreen(_this, other, display, SDL_TRUE);
//				}
//				display->fullscreen_window = other;
//
//				/* Generate a mode change event here */
//				if (resized) {
//					SDL_SendWindowEvent(other, SDL_WINDOWEVENT_RESIZED,
//						fullscreen_mode.w, fullscreen_mode.h);
//				} else {
//					SDL_OnWindowResized(other);
//				}
//
//				SDL_RestoreMousePosition(other);
//
//				window->last_fullscreen_flags = window->flags;
//				return;
//			}
//		}
//	}
//
//	/* Nope, restore the desktop mode */
//	SDL_SetDisplayModeForDisplay(display, NULL);
//
//	if (_this->SetWindowFullscreen) {
//		_this->SetWindowFullscreen(_this, window, display, SDL_FALSE);
//	}
//	display->fullscreen_window = NULL;
//
//	/* Generate a mode change event here */
//	SDL_OnWindowResized(window);
//
//	/* Restore the cursor position */
//	SDL_RestoreMousePosition(window);
//
//	window->last_fullscreen_flags = window->flags;
}
//--------------------------------------------------------------------------
void VeDevice::FinishWindowCreation(Window* pkWindow, VeUInt32 u32Flags)
{
	pkWindow->m_kWindowed.x = pkWindow->x;
	pkWindow->m_kWindowed.y = pkWindow->y;
	pkWindow->m_kWindowed.w = pkWindow->w;
	pkWindow->m_kWindowed.h = pkWindow->h;

	if(u32Flags & WINDOW_MAXIMIZED)
	{
		MaximizeWindow();
	}
	if(u32Flags & WINDOW_MINIMIZED)
	{
		MinimizeWindow();
	}
	/*if (flags & SDL_WINDOW_FULLSCREEN) {
		SDL_SetWindowFullscreen(window, flags);
	}
	if (flags & SDL_WINDOW_INPUT_GRABBED) {
		SDL_SetWindowGrab(window, SDL_TRUE);
	}*/
	if(!(u32Flags & WINDOW_HIDDEN))
	{
		ShowWindow();
	}
}
//--------------------------------------------------------------------------
void VeDevice::ParseCmdLine()
{
	VeChar8 acCmd[256];
	VeStrcpy(acCmd, GetStartParams().m_pcCmdLine);
	VeChar8* pcContext;
	const VeChar8* pcParam = VeStrtok(acCmd, " ", &pcContext);
	while(pcParam)
	{
		if(VeStrnicmp(pcParam, "-d", 2) == 0)
		{
			if(VeStricmp(pcParam + 2, "lua") == 0)
			{
				m_bLuaDebug = true;
			}
		}
		pcParam = VeStrtok(NULL, " ", &pcContext);
	}
}
//--------------------------------------------------------------------------
void VeDevice::LoadConfig()
{
	VeDirectory* pkDir(NULL);
	if((!pkDir) && m_kParams.m_pcConfigCustomDir)
	{
		pkDir = g_pResourceManager->CreateDir(m_kParams.m_pcConfigCustomDir);
		if(!pkDir->HasFile(m_kParams.m_pcConfigName))
		{
			g_pResourceManager->DestoryDir(pkDir);
			pkDir = NULL;
		}
	}
	if((!pkDir) && m_kParams.m_pcConfigDefaultDir)
	{
		pkDir = g_pResourceManager->CreateDir(m_kParams.m_pcConfigDefaultDir);
		if(!pkDir->HasFile(m_kParams.m_pcConfigName))
		{
			g_pResourceManager->DestoryDir(pkDir);
			pkDir = NULL;
		}
	}
	if(pkDir)
	{
		VeChar8* pcConfig(NULL);
		{
			VeBinaryIStreamPtr spStream = pkDir->OpenSync(m_kParams.m_pcConfigName);
			VeInt32 i32Length = spStream->RemainingLength();
			if(i32Length > 0)
			{
				pcConfig = VeAlloc(VeChar8, i32Length + 1);
				pcConfig[i32Length] = '\0';
				VE_ASSERT_EQ(spStream->Read(pcConfig, i32Length), i32Length);
			}
			g_pResourceManager->DestoryDir(pkDir);
			pkDir = NULL;
		}
		if(pcConfig)
		{
			VeChar8* pcContext;
			VeChar8* pcLine = VeStrline(pcConfig, &pcContext);
			VeMap<VeString,VeString>* pkMap(NULL);
			while(pcLine)
			{
				if(*pcLine == '[')
				{
					pcLine = VeStrBetween(pcLine, "[", "]");
					pkMap = &m_kConfigMap[pcLine];
				}
				else if(pkMap)
				{
					VeChar8* pcContext;
					VeChar8* pcTag = VeStrtok(pcLine, "=", &pcContext);
					(*pkMap)[VeStrContent(pcTag)] = VeStrContent(pcContext);
				}
				pcLine = VeStrline(NULL, &pcContext);
			}
			VeFree(pcConfig);
		}
	}
	m_kVideoGroup = VeString("video_") + GetName();
}
//--------------------------------------------------------------------------
bool VeDevice::IsDesktop()
{
	switch(GetType())
	{
	case TYPE_WINDOWS:
	case TYPE_MOBSIM:
	case TYPE_LINUX:
	case TYPE_MACOSX:
		return true;
	default:
		return false;
	}
}
//--------------------------------------------------------------------------
void VeDevice::Active()
{
	g_pApplication->Active();
}
//--------------------------------------------------------------------------
void VeDevice::Inactive()
{
	g_pApplication->Inactive();
}
//--------------------------------------------------------------------------
void VeDevice::Show()
{
	g_pApplication->Show();
}
//--------------------------------------------------------------------------
void VeDevice::Hide()
{
	g_pApplication->Hide();
}
//--------------------------------------------------------------------------
VeImplWriteDelegate(VeDevice, OnConfigSaved, eResult)
{

}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeDevice)
{
	Module() [
		Class<VeDevice>() [
			DefSingletonFunc("GetDeviceID", VeDevice::ms_pSingleton, &VeDevice::GetDeviceID),
			DefSingletonFunc("GetDeviceName", VeDevice::ms_pSingleton, &VeDevice::GetDeviceName),
			DefSingletonFunc("SetTransField", VeDevice::ms_pSingleton, &VeDevice::SetTransField),
			DefSingletonFunc("GetTransField", VeDevice::ms_pSingleton, &VeDevice::GetTransField),
			DefSingletonFunc("Translate", VeDevice::ms_pSingleton, &VeDevice::Translate)
		]
	];
}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeDevice, Type);
	VeLuaClassEnumFuncImpl(VeDevice, Language);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeDevice, Type)
{
	VeLuaClassEnumBase(VeDevice, Type);
	VeLuaClassEnumSlot(VeDevice, Type, TYPE_WINDOWS, "win");
	VeLuaClassEnumSlot(VeDevice, Type, TYPE_MOBSIM, "sim");
	VeLuaClassEnumSlot(VeDevice, Type, TYPE_LINUX, "lin");
	VeLuaClassEnumSlot(VeDevice, Type, TYPE_MACOSX, "osx");
	VeLuaClassEnumSlot(VeDevice, Type, TYPE_IOS, "ios");
	VeLuaClassEnumSlot(VeDevice, Type, TYPE_ANDROID, "and");
	VeLuaClassEnumSlot(VeDevice, Type, TYPE_ALL, "all");
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeDevice, Language)
{
	VeLuaClassEnumBase(VeDevice, Language);
	VeLuaClassEnumSlot(VeDevice, Language, EN_US, "en_US");
	VeLuaClassEnumSlot(VeDevice, Language, ZH_CN, "zh_CN");
	VeLuaClassEnumSlot(VeDevice, Language, ZH_TW, "zh_TW");
}
//--------------------------------------------------------------------------
