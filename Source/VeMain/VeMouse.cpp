////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMouse.cpp
//  Version:     v1.00
//  Created:     23/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeMouse.inl"
#endif

//--------------------------------------------------------------------------
#ifdef VE_DIRECT_INPUT
#	define DIRECTINPUT_VERSION DIRECTINPUT_HEADER_VERSION
#	include <dinput.h>
#endif
//--------------------------------------------------------------------------
VeMouse::VeMouse()
	: m_u32State(0)
	, m_stLastCursorMove(VE_INFINITE)
{

}
//--------------------------------------------------------------------------
VeMouse::~VeMouse()
{

}
//--------------------------------------------------------------------------
void VeMouse::Init()
{

}
//--------------------------------------------------------------------------
void VeMouse::Term()
{

}
//--------------------------------------------------------------------------
void VeMouse::ProcessButtonDown(State eBtn, VeSizeT stData)
{
	VE_ASSERT(eBtn <= BTN_BUTTON2);
	if(!VE_MASK_HAS_ANY(m_u32State, eBtn))
	{
		VE_MASK_ADD(m_u32State, eBtn);
		switch(eBtn)
		{
		case BTN_BUTTON0:
			g_pInputManager->AppendMessage(VeInputMessage::DT_MOUSE, VeInputMessage::MIT_LBTN_PRESSED, g_pTime->GetTimeUInt(), stData);
			break;
		case BTN_BUTTON1:
			g_pInputManager->AppendMessage(VeInputMessage::DT_MOUSE, VeInputMessage::MIT_RBTN_PRESSED, g_pTime->GetTimeUInt(), stData);
			break;
		case BTN_BUTTON2:
			g_pInputManager->AppendMessage(VeInputMessage::DT_MOUSE, VeInputMessage::MIT_MBTN_PRESSED, g_pTime->GetTimeUInt(), stData);
			break;
		default:
			break;
		}
	}
}
//--------------------------------------------------------------------------
void VeMouse::ProcessButtonUp(State eBtn, VeSizeT stData)
{
	VE_ASSERT(eBtn <= BTN_BUTTON2);
	if(VE_MASK_HAS_ANY(m_u32State, eBtn))
	{
		VE_MASK_DEL(m_u32State, eBtn);
		switch(eBtn)
		{
		case BTN_BUTTON0:
			g_pInputManager->AppendMessage(VeInputMessage::DT_MOUSE, VeInputMessage::MIT_LBTN_RELEASED, g_pTime->GetTimeUInt(), stData);
			break;
		case BTN_BUTTON1:
			g_pInputManager->AppendMessage(VeInputMessage::DT_MOUSE, VeInputMessage::MIT_RBTN_RELEASED, g_pTime->GetTimeUInt(), stData);
			break;
		case BTN_BUTTON2:
			g_pInputManager->AppendMessage(VeInputMessage::DT_MOUSE, VeInputMessage::MIT_MBTN_RELEASED, g_pTime->GetTimeUInt(), stData);
			break;
		default:
			break;
		}
	}
}
//--------------------------------------------------------------------------
void VeMouse::ProcessCursorMove(VeSizeT stData)
{
	if(m_stLastCursorMove != stData)
	{
		g_pInputManager->AppendMessage(VeInputMessage::DT_MOUSE,
			VeInputMessage::MIT_CURSOR_MOVED, g_pTime->GetTimeUInt(), stData);
		m_stLastCursorMove = stData;
	}
}
//--------------------------------------------------------------------------
void VeMouse::Update()
{

}
//--------------------------------------------------------------------------
void VeMouse::SetCursorPos(VeUInt16 x, VeUInt16 y)
{

}
//--------------------------------------------------------------------------
void VeMouse::SetCursorPosF(VeFloat32 x, VeFloat32 y)
{

}
//--------------------------------------------------------------------------
void VeMouse::SetHide(bool bHide)
{
//	if(VE_MASK_HAS_ANY(m_u32State, CUR_HIDE) != bHide)
//	{
//		if(bHide)
//		{
//#			if defined(VE_PLATFORM_WIN)
//			::ShowCursor(FALSE);
//#			elif defined(VE_PLATFORM_LINUX)
//			XDefineCursor(g_pkDisplay, g_hWindow, m_hCursor);
//#			endif
//			VE_MASK_ADD(m_u32State, CUR_HIDE);
//		}
//		else
//		{
//#			if defined(VE_PLATFORM_WIN)
//			::ShowCursor(TRUE);
//#			elif defined(VE_PLATFORM_LINUX)
//			XUndefineCursor(g_pkDisplay, g_hWindow);
//#			endif
//			VE_MASK_DEL(m_u32State, CUR_HIDE);
//		}
//	}
}
//--------------------------------------------------------------------------
void VeMouse::SetLock(bool bLock)
{
	/*if(VE_MASK_HAS_ANY(m_u32State, CUR_LOCK) != bLock)
	{
		if(bLock)
		{
#			if defined(VE_PLATFORM_WIN)
			POINT kPoint = {g_pRenderer->GetWidth() >> 1, g_pRenderer->GetHeight() >> 1};
			ClientToScreen(g_hWindow, &kPoint);
			RECT kRect;
			kRect.left = kPoint.x;
			kRect.top = kPoint.y;
			kRect.right = kPoint.x;
			kRect.bottom = kPoint.y;
			ClipCursor(&kRect);
#			endif
			VE_MASK_ADD(m_u32State, CUR_LOCK);
		}
		else
		{
#			if defined(VE_PLATFORM_WIN)
			ClipCursor(NULL);
#			endif
			VE_MASK_DEL(m_u32State, CUR_LOCK);
		}
	}*/
}
//--------------------------------------------------------------------------
