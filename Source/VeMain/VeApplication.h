////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeApplication.h
//  Version:     v1.00
//  Created:     27/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_INACTIVE_SLEEP (30)

class VE_MAIN_API VeApplication : public VeSingleton<VeApplication>
{
public:
	virtual ~VeApplication();

	VE_INLINE void Init();

	VE_INLINE void Term();

	VE_INLINE void SetProcessInput(bool bEnable);

	VE_INLINE bool GetProcessInput();

	VE_INLINE void QuitApp();

	VE_INLINE bool IsAppQuit();

	VE_INLINE VeUInt32 GetFPS();

	virtual void Update();

	virtual void OnInit() {};

	virtual void OnTerm() {};

	virtual void OnRendererReleaseData() {};

	virtual void OnRendererRestoreData() {};

	virtual void OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height) {};

	virtual void OnHide() {};

	virtual void OnShow() {};

	virtual void OnUpdate() {};

	virtual void OnActive() {};

	virtual void OnInactive() {};

	virtual bool OnClose() { return true; }

	virtual void OnKeyPressed(VeKeyboard::InputKey eKey) {};

	virtual void OnKeyReleased(VeKeyboard::InputKey eKey) {};

	virtual void OnMousePressed(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y) {};

	virtual void OnMouseReleased(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y) {};

	virtual void OnCursorMove(VeUInt16 x, VeUInt16 y) {};

	virtual void OnMouseMove(VeUInt32 u32OffsetX, VeUInt32 u32OffsetY, VeUInt32 u32OffsetZ) {};

	virtual void OnJoyStickPressed(VeUInt32 u32Button) {};

	virtual void OnJoyStickReleased(VeUInt32 u32Button) {};

	virtual void OnJoyStickAxisChanged(VeUInt32 u32Axis, VeUInt32 u32Value) {};
    
    virtual void OnTouchBegan(VeUInt32 u32Time, VeUInt32 id, VeFloat32 x, VeFloat32 y) {}
    
    virtual void OnTouchEnded(VeUInt32 u32Time, VeUInt32 id, VeFloat32 x, VeFloat32 y) {}
    
    virtual void OnTouchMoved(VeUInt32 u32Time, VeVector<VeInputMessage::TouchPointParam>& kParams) {}
    
    virtual void OnTouchCancelled(VeUInt32 u32Time, VeVector<VeInputMessage::TouchPointParam>& kParams) {}

protected:
	friend class VeDevice;

	VeApplication();

	VE_INLINE void Hide();

	VE_INLINE void Show();

	VE_INLINE void Inactive();

	VE_INLINE void Active();

	VeDeclInputDelegate(VeApplication, InputCallback);

	VeUInt32 m_u32FPS;
	bool m_bQuit;
	bool m_bProcessInput;
	bool m_bActive;
	bool m_bShow;
	
};

#define g_pApplication VeApplication::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeApplication.inl"
#endif
