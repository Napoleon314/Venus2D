////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMobileSim.h
//  Version:     v1.00
//  Created:     12/6/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeMobileSim : public VeDevice
{
public:
	VeMobileSim(VeStartParams& kParams);

	virtual ~VeMobileSim();

	HWND GetWindowHandle();

	virtual void _Init();

	virtual void _Term();

	virtual void _GetDisplayBounds(VideoDisplay& kDisplay, VeRect& kRect);

	virtual void _GetDisplayModes(VideoDisplay& kDisplay);

	virtual void _CreateWindow(Window* pkWindow);

	virtual void _DestoryWindow(Window* pkWindow);

	virtual void _SetWindowTitle(Window* pkWindow);

	virtual void _SetWindowPosition(Window* pkWindow);

	virtual void _SetWindowSize(Window* pkWindow);

	virtual void _SetWindowMinimumSize(Window* pkWindow) {}

	virtual void _SetWindowMaximumSize(Window* pkWindow) {}

	virtual void _ShowWindow(Window* pkWindow);

	virtual void _HideWindow(Window* pkWindow);

	virtual void _RaiseWindow(Window* pkWindow);

	virtual void _MaximizeWindow(Window* pkWindow);

	virtual void _MinimizeWindow(Window* pkWindow);

	virtual void _RestoreWindow(Window* pkWindow);

	virtual void _SetWindowBordered(Window* pkWindow, bool bBordered);

	virtual void _SetWindowFullscreen(Window* pkWindow, VideoDisplay* pkDisplay, bool bFullscreen);

	virtual bool _SetWindowGammaRamp(Window* pkWindow, const VeUInt16* pu16Ramp);

	virtual bool _GetWindowGammaRamp(Window* pkWindow, VeUInt16* pu16Ramp);

	virtual void _SetWindowGrab(Window* pkWindow, bool bGrabbed);

	virtual void _PumpEvents();

	virtual void _EnableIME(Window* pkWindow);

	virtual void _DisableIME(Window* pkWindow);

protected:
	void InitDisplayModes();

	void TermDisplayModes();

	static VE_BOOL GetDisplayMode(LPCSTR deviceName, DWORD index, VeDevice::DisplayMode* pkMode);

	VE_BOOL AddDisplay(LPSTR DeviceName);

	static VeDWord GetWindowStyle(Window* pkWindow);

	void SetupWindowData(Window* pkWindow, HWND hWnd, VE_BOOL bCreated);

	void SetWindowPositionInternal(Window* pkWindow, VeUInt32 u32Flags);

	void UpdateClipCursor(Window* pkWindow);

	bool IMEHandleMessage(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM& lParam);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

};
