////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeApplication.cpp
//  Version:     v1.00
//  Created:     27/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeApplication.inl"
#endif

//--------------------------------------------------------------------------
VeApplication::VeApplication() : m_u32FPS(0), m_bQuit(false)
	, m_bProcessInput(true), m_bActive(true), m_bShow(true)
{
	VeInitDelegate(VeApplication, InputCallback);
}
//--------------------------------------------------------------------------
VeApplication::~VeApplication()
{

}
//--------------------------------------------------------------------------
void VeApplication::Update()
{
	if(m_bShow)
	{
		g_pTime->Update();
		g_pURL->Update();
		g_pResourceManager->Update();
		g_pAudioSystem->Update();

		if(!m_bActive)
		{
			VeSleep(30);
		}

		{
			static VeFloat32 s_f32TimeCount(0);
			static VeUInt32 s_u32FrameCount(0);

			s_f32TimeCount += g_pTime->GetDeltaTime();
			++s_u32FrameCount;

			if(s_f32TimeCount > 1.0f)
			{
				m_u32FPS = s_u32FrameCount;
				/*static VeChar8 s_acFPS[64];
				VeSprintf(s_acFPS, "FPS:%d", s_u32FrameCount);
				g_pDevice->SetWindowTitle(s_acFPS);*/
				s_f32TimeCount -= VeFloorf(s_f32TimeCount);
				s_u32FrameCount = 0;
			}
		}
		g_pClientManager->Update();
		g_pInputManager->Update();
		OnUpdate();
		g_pSceneManager->Update();
		g_pRenderFrameManager->Render();
		g_pRenderer->Present();
	}
}
//--------------------------------------------------------------------------
VeImplInputDelegate(VeApplication, InputCallback, kMessage)
{
	if(m_bProcessInput)
	{
		switch(kMessage.m_eDeviceType)
		{
		case VeInputMessage::DT_KEYBOARD:
			switch(kMessage.m_u32InputType)
			{
			case VeInputMessage::KIT_KEY_PRESSED:
				OnKeyPressed((VeKeyboard::InputKey)kMessage.m_stMessageInfo);
				break;
			case VeInputMessage::KIT_KEY_RELEASED:
				OnKeyReleased((VeKeyboard::InputKey)kMessage.m_stMessageInfo);
				break;
			default:
				break;
			}
			break;
		case VeInputMessage::DT_MOUSE:
			switch(kMessage.m_u32InputType)
			{
			case VeInputMessage::MIT_LBTN_PRESSED:
				OnMousePressed(VeMouse::BTN_BUTTON0, kMessage.m_kMouseCursorPos.x, kMessage.m_kMouseCursorPos.y);
				break;
			case VeInputMessage::MIT_RBTN_PRESSED:
				OnMousePressed(VeMouse::BTN_BUTTON1, kMessage.m_kMouseCursorPos.x, kMessage.m_kMouseCursorPos.y);
				break;
			case VeInputMessage::MIT_MBTN_PRESSED:
				OnMousePressed(VeMouse::BTN_BUTTON2, kMessage.m_kMouseCursorPos.x, kMessage.m_kMouseCursorPos.y);
				break;
			case VeInputMessage::MIT_LBTN_RELEASED:
				OnMouseReleased(VeMouse::BTN_BUTTON0, kMessage.m_kMouseCursorPos.x, kMessage.m_kMouseCursorPos.y);
				break;
			case VeInputMessage::MIT_RBTN_RELEASED:
				OnMouseReleased(VeMouse::BTN_BUTTON1, kMessage.m_kMouseCursorPos.x, kMessage.m_kMouseCursorPos.y);
				break;
			case VeInputMessage::MIT_MBTN_RELEASED:
				OnMouseReleased(VeMouse::BTN_BUTTON2, kMessage.m_kMouseCursorPos.x, kMessage.m_kMouseCursorPos.y);
				break;
			case VeInputMessage::MIT_CURSOR_MOVED:
				OnCursorMove(kMessage.m_kMouseCursorPos.x, kMessage.m_kMouseCursorPos.y);
				break;
			case VeInputMessage::MIT_MOUSE_MOVED:
				OnMouseMove(kMessage.m_pkMouseMoveParam->x, kMessage.m_pkMouseMoveParam->y, kMessage.m_pkMouseMoveParam->z);
				break;
			default:
				break;
			}
			break;
		case VeInputMessage::DT_JOYSTICK:
			switch(kMessage.m_u32InputType)
			{
			case VeInputMessage::JIT_BTN_PRESSED:
				OnJoyStickPressed(VeUInt32(kMessage.m_stMessageInfo));
				break;
			case VeInputMessage::JIT_BTN_RELEASED:
				OnJoyStickReleased(VeUInt32(kMessage.m_stMessageInfo));
				break;
			default:
				if(kMessage.m_u32InputType >= VeInputMessage::JIT_AXIS_MOVED)
				{
					OnJoyStickAxisChanged(kMessage.m_u32InputType - VeInputMessage::JIT_AXIS_MOVED, VeUInt32(kMessage.m_stMessageInfo));
				}
				break;
			}
			break;
		case VeInputMessage::DT_TOUCH:
            switch(kMessage.m_u32InputType)
            {
            case VeInputMessage::TIT_BEGAN:
                OnTouchBegan(kMessage.m_u32InputCode, kMessage.m_pkTouchPointParam->id, kMessage.m_pkTouchPointParam->x, kMessage.m_pkTouchPointParam->y);
                break;
            case VeInputMessage::TIT_MOVED:
                OnTouchMoved(kMessage.m_u32InputCode, *(kMessage.m_pkTouchPointParams));
                break;
            case VeInputMessage::TIT_ENDED:
                OnTouchEnded(kMessage.m_u32InputCode, kMessage.m_pkTouchPointParam->id, kMessage.m_pkTouchPointParam->x, kMessage.m_pkTouchPointParam->y);
                break;
            case VeInputMessage::TIT_CANCELLED:
                OnTouchCancelled(kMessage.m_u32InputCode, *(kMessage.m_pkTouchPointParams));
                break;
            default:
                break;
            }
			break;
		default:
			break;
		}
	}
}
//--------------------------------------------------------------------------
