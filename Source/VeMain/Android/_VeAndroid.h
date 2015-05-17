////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeWindows.h
//  Version:     v1.00
//  Created:     17/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeAndroid : public VeDevice
{
public:
	VeAndroid(VeStartParams& kParams);

	virtual ~VeAndroid();

	virtual void _Init();

	virtual void _Term();

	virtual void _GetDisplayBounds(VideoDisplay& kDisplay, VeRect& kRect) {}

	virtual void _GetDisplayModes(VideoDisplay& kDisplay) {}

	virtual void _CreateWindow(Window* pkWindow);

	virtual void _DestoryWindow(Window* pkWindow);

	virtual void _SetWindowTitle(Window* pkWindow) {}

	virtual void _SetWindowPosition(Window* pkWindow) {}

	virtual void _SetWindowSize(Window* pkWindow) {}

	virtual void _SetWindowMinimumSize(Window* pkWindow) {}

	virtual void _SetWindowMaximumSize(Window* pkWindow) {}

	virtual void _ShowWindow(Window* pkWindow) {}

	virtual void _HideWindow(Window* pkWindow) {}

	virtual void _RaiseWindow(Window* pkWindow) {}

	virtual void _MaximizeWindow(Window* pkWindow) {}

	virtual void _MinimizeWindow(Window* pkWindow) {}

	virtual void _RestoreWindow(Window* pkWindow) {}

	virtual void _SetWindowBordered(Window* pkWindow, bool bBordered) {}

	virtual void _SetWindowFullscreen(Window* pkWindow, VideoDisplay* pkDisplay, bool bFullscreen) {}

	virtual bool _SetWindowGammaRamp(Window* pkWindow, const VeUInt16* pu16Ramp) { return false; }

	virtual bool _GetWindowGammaRamp(Window* pkWindow, VeUInt16* pu16Ramp) { return false; }

	virtual void _SetWindowGrab(Window* pkWindow, bool bGrabbed) {}

	virtual void _PumpEvents();

	virtual void _EnableIME(Window* pkWindow);

	virtual void _DisableIME(Window* pkWindow);

	ANativeWindow* GetWindow();

	virtual JavaVM* GetJavaVM();

	virtual JNIEnv* GetJNIEnv();

	virtual void ClearJNIEnv();

	virtual VeString GetString(jstring jstrContent);

	virtual void GetStaticMethodInfo(JniMethodInfo& kOut, const VeChar8* pcClass,
		const VeChar8* pcMethod, const VeChar8* pcParamCode);

	virtual void GetMethodInfo(JniMethodInfo& kOut, const VeChar8* pcClass,
		const VeChar8* pcMethod, const VeChar8* pcParamCode);

protected:
	JNIEnv* CacheJNIEnv();

	jclass GetClassID(const VeChar8* pcClass);

	jobject m_joClassLoader;
	jmethodID m_jfuncLoadClass;

	bool m_bWindowInit;

	static void HandleCommand(struct android_app* pkAppState, int32_t i32Command);

	static int32_t HandleInput(struct android_app* pkAppState, AInputEvent* pkEvent);

};
