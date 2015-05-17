////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeIOS.h
//  Version:     v1.00
//  Created:     27/3/2014 by Napoleon
//  Compilers:   Xcode Obj-c
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeIOS : public VeDevice
{
public:
	VeIOS(VeStartParams& kParams);

	virtual ~VeIOS();
    
    virtual void _Init();
    
	virtual void _Term();
    
    virtual void _GetDisplayBounds(VideoDisplay& kDisplay, VeRect& kRect) {}
    
	virtual void _GetDisplayModes(VideoDisplay& kDisplay);

	virtual void _CreateWindow(Window* pkWindow);

	virtual void _DestoryWindow(Window* pkWindow);

	virtual void _SetWindowTitle(Window* pkWindow) {}

	virtual void _SetWindowPosition(Window* pkWindow) {}

	virtual void _SetWindowSize(Window* pkWindow) {}

	virtual void _SetWindowMinimumSize(Window* pkWindow) {}

	virtual void _SetWindowMaximumSize(Window* pkWindow) {}

	virtual void _ShowWindow(Window* pkWindow);

	virtual void _HideWindow(Window* pkWindow);

	virtual void _RaiseWindow(Window* pkWindow) {}

	virtual void _MaximizeWindow(Window* pkWindow) {}

	virtual void _MinimizeWindow(Window* pkWindow) {}

	virtual void _RestoreWindow(Window* pkWindow) {}

	virtual void _SetWindowBordered(Window* pkWindow, bool bBordered) {}

	virtual void _SetWindowFullscreen(Window* pkWindow, VideoDisplay* pkDisplay, bool bFullscreen) {}

	virtual bool _SetWindowGammaRamp(Window* pkWindow, const VeUInt16* pu16Ramp) {return false;}

	virtual bool _GetWindowGammaRamp(Window* pkWindow, VeUInt16* pu16Ramp) {return false;}

	virtual void _SetWindowGrab(Window* pkWindow, bool bGrabbed) {}

	virtual void _PumpEvents();
    
    void AddDisplay(VideoDisplay& kDisplay);
    
    void Show();
    
	void Hide();
    
    void Active();
    
    void Inactive();
    
    virtual void _EnableIME(Window* pkWindow);
    
    virtual void _DisableIME(Window* pkWindow);

protected:
    void InitDisplayModes();

    void TermDisplayModes();

};
