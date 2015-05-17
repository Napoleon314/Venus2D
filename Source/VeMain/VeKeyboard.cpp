////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeKeyboard.cpp
//  Version:     v1.00
//  Created:     22/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeKeyboard.inl"
#endif

//--------------------------------------------------------------------------
#ifdef VE_DIRECT_INPUT
#	define DIRECTINPUT_VERSION DIRECTINPUT_HEADER_VERSION
#	include <dinput.h>
#endif
//--------------------------------------------------------------------------
VeKeyboard::VeKeyboard()
	: m_u32Modifiers(0)
#	if defined(VE_DIRECT_INPUT)
	, m_pkKeyboard(NULL)
#	endif
{
	VeZeroMemory(m_abyKeyState, sizeof(m_abyKeyState));
}
//--------------------------------------------------------------------------
VeKeyboard::~VeKeyboard()
{

}
//--------------------------------------------------------------------------
void VeKeyboard::Init()
{
#	if defined(VE_DIRECT_INPUT)
	VE_ASSERT_EQ(g_pInputManager->m_pkDirectInput->CreateDevice(GUID_SysKeyboard, &m_pkKeyboard, NULL), S_OK);
	VE_ASSERT_EQ(m_pkKeyboard->SetDataFormat(&c_dfDIKeyboard), S_OK);
	VE_ASSERT_EQ(m_pkKeyboard->SetCooperativeLevel(g_hWindow, DISCL_FOREGROUND|DISCL_EXCLUSIVE), S_OK);
	DIPROPDWORD kDipdw;
	kDipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	kDipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	kDipdw.diph.dwObj        = 0;
	kDipdw.diph.dwHow        = DIPH_DEVICE;
	kDipdw.dwData            = VE_KEYBOARD_DX_BUFFERSIZE;
	VE_ASSERT_EQ(m_pkKeyboard->SetProperty(DIPROP_BUFFERSIZE, &kDipdw.diph), S_OK);
	m_pkKeyboard->Acquire();
#	endif
}
//--------------------------------------------------------------------------
void VeKeyboard::Term()
{
#	if defined(VE_DIRECT_INPUT)
	VE_SAFE_RELEASE(m_pkKeyboard);
#	endif
}
//--------------------------------------------------------------------------
void VeKeyboard::Update()
{
#	if defined(VE_DIRECT_INPUT)
	DIDEVICEOBJECTDATA akData[VE_KEYBOARD_DX_BUFFERSIZE];
	DWORD dwEntries = VE_KEYBOARD_DX_BUFFERSIZE;
	HRESULT hRes = m_pkKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), akData, &dwEntries, 0);
	if(hRes != DI_OK)
	{
		hRes = m_pkKeyboard->Acquire();
		while(hRes == DIERR_INPUTLOST)
			hRes = m_pkKeyboard->Acquire();
		hRes = m_pkKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), akData, &dwEntries, 0);
		if(FAILED(hRes)) return;
	}
	for(VeUInt32 i(0); i < dwEntries; ++i)
	{
		InputKey eKey = (InputKey)akData[i].dwOfs;
		VeByte byData = (VeByte)(akData[i].dwData);
		m_abyKeyState[eKey] = byData;
		if(byData & 0x80)
		{
			if(eKey == KEY_LCONTROL || eKey == KEY_RCONTROL)
				VE_MASK_ADD(m_u32Modifiers, CTRL);
			else if(eKey == KEY_LSHIFT || eKey == KEY_RSHIFT)
				VE_MASK_ADD(m_u32Modifiers, SHIFT);
			else if(eKey == KEY_LMENU || eKey == KEY_RMENU)
				VE_MASK_ADD(m_u32Modifiers, ALT);
			g_pInputManager->AppendMessage(VeInputMessage::DT_KEYBOARD, VeInputMessage::KIT_KEY_PRESSED, g_pTime->GetTimeUInt(), eKey);
		}
		else
		{
			if(eKey == KEY_LCONTROL || eKey == KEY_RCONTROL)
				VE_MASK_DEL(m_u32Modifiers, CTRL);
			else if(eKey == KEY_LSHIFT || eKey == KEY_RSHIFT)
				VE_MASK_DEL(m_u32Modifiers, SHIFT);
			else if(eKey == KEY_LMENU || eKey == KEY_RMENU)
				VE_MASK_DEL(m_u32Modifiers, ALT);
			g_pInputManager->AppendMessage(VeInputMessage::DT_KEYBOARD, VeInputMessage::KIT_KEY_RELEASED, g_pTime->GetTimeUInt(), eKey);
		}
	}
#	endif
}
//--------------------------------------------------------------------------
VeKeyboard::InputKey VeKeyboard::TranslateKey(VeSizeT stKey)
{
#	if defined(VE_PLATFORM_WIN) || defined(VE_PLATFORM_MOBILE_SIM)
	switch(stKey)
	{
	case VK_BACK:
		return KEY_BACK;
	case VK_TAB:
		return KEY_TAB;
	case VK_RETURN:
		return KEY_RETURN;
	case VK_SHIFT:
		return KEY_LSHIFT;
	case VK_CONTROL:
		return KEY_LCONTROL;
	case VK_MENU:
		return KEY_LMENU;
	case VK_PAUSE:
		return KEY_PAUSE;
	case VK_CAPITAL:
		return KEY_CAPITAL;
	case VK_ESCAPE:
		return KEY_ESCAPE;
	case VK_SPACE:
		return KEY_SPACE;
	case VK_PRIOR:
		return KEY_PGUP;
	case VK_NEXT:
		return KEY_PGDOWN;
	case VK_END:
		return KEY_END;
	case VK_HOME:
		return KEY_HOME;
	case VK_LEFT:
		return KEY_LEFT;
	case VK_UP:
		return KEY_UP;
	case VK_RIGHT:
		return KEY_RIGHT;
	case VK_DOWN:
		return KEY_DOWN;
	case VK_SELECT:
		return KEY_MEDIASELECT;
	case VK_SNAPSHOT:
		return KEY_UNKNOWNN;
	case VK_INSERT:
		return KEY_INSERT;
	case VK_DELETE:
		return KEY_DELETE;
	case '0':
		return KEY_0;
	case '1':
		return KEY_1;
	case '2':
		return KEY_2;
	case '3':
		return KEY_3;
	case '4':
		return KEY_4;
	case '5':
		return KEY_5;
	case '6':
		return KEY_6;
	case '7':
		return KEY_7;
	case '8':
		return KEY_8;
	case '9':
		return KEY_9;
	case 'A':
		return KEY_A;
	case 'B':
		return KEY_B;
	case 'C':
		return KEY_C;
	case 'D':
		return KEY_D;
	case 'E':
		return KEY_E;
	case 'F':
		return KEY_F;
	case 'G':
		return KEY_G;
	case 'H':
		return KEY_H;
	case 'I':
		return KEY_I;
	case 'J':
		return KEY_J;
	case 'K':
		return KEY_K;
	case 'L':
		return KEY_L;
	case 'M':
		return KEY_M;
	case 'N':
		return KEY_N;
	case 'O':
		return KEY_O;
	case 'P':
		return KEY_P;
	case 'Q':
		return KEY_Q;
	case 'R':
		return KEY_R;
	case 'S':
		return KEY_S;
	case 'T':
		return KEY_T;
	case 'U':
		return KEY_U;
	case 'V':
		return KEY_V;
	case 'W':
		return KEY_W;
	case 'X':
		return KEY_X;
	case 'Y':
		return KEY_Y;
	case 'Z':
		return KEY_Z;
	case VK_LWIN:
		return KEY_LWIN;
	case VK_RWIN:
		return KEY_RWIN;
	case VK_APPS:
		return KEY_APPS;
	case VK_NUMPAD0:
		return KEY_NUMPAD0;
	case VK_NUMPAD1:
		return KEY_NUMPAD1;
	case VK_NUMPAD2:
		return KEY_NUMPAD2;
	case VK_NUMPAD3:
		return KEY_NUMPAD3;
	case VK_NUMPAD4:
		return KEY_NUMPAD4;
	case VK_NUMPAD5:
		return KEY_NUMPAD5;
	case VK_NUMPAD6:
		return KEY_NUMPAD6;
	case VK_NUMPAD7:
		return KEY_NUMPAD7;
	case VK_NUMPAD8:
		return KEY_NUMPAD8;
	case VK_NUMPAD9:
		return KEY_NUMPAD9;
	case VK_MULTIPLY:
		return KEY_MULTIPLY;
	case VK_ADD:
		return KEY_ADD;
	case VK_SUBTRACT:
		return KEY_SUBTRACT;
	case VK_DECIMAL:
		return KEY_DECIMAL;
	case VK_DIVIDE:
		return KEY_DIVIDE;
	case VK_F1:
		return KEY_F1;
	case VK_F2:
		return KEY_F2;
	case VK_F3:
		return KEY_F3;
	case VK_F4:
		return KEY_F4;
	case VK_F5:
		return KEY_F5;
	case VK_F6:
		return KEY_F6;
	case VK_F7:
		return KEY_F7;
	case VK_F8:
		return KEY_F8;
	case VK_F9:
		return KEY_F9;
	case VK_F10:
		return KEY_F10;
	case VK_F11:
		return KEY_F11;
	case VK_F12:
		return KEY_F12;
	case VK_F13:
		return KEY_F13;
	case VK_F14:
		return KEY_F14;
	case VK_F15:
		return KEY_F15;
	case VK_NUMLOCK:
		return KEY_NUMLOCK;
	case VK_SCROLL:
		return KEY_SCROLL;
	default:
		break;
	}
#	elif defined(VE_PLATFORM_LINUX)
	switch(stKey)
	{
	case XK_1:
		return KEY_1;
	case XK_2:
		return KEY_2;
	case XK_3:
		return KEY_3;
	case XK_4:
		return KEY_4;
	case XK_5:
		return KEY_5;
	case XK_6:
		return KEY_6;
	case XK_7:
		return KEY_7;
	case XK_8:
		return KEY_8;
	case XK_9:
		return KEY_9;
	case XK_0:
		return KEY_0;
	case XK_BackSpace:
		return KEY_BACK;
	case XK_minus:
		return KEY_MINUS;
	case XK_equal:
		return KEY_EQUALS;
	case XK_space:
		return KEY_SPACE;
	case XK_comma:
		return KEY_COMMA;
	case XK_period:
		return KEY_PERIOD;
	case XK_backslash:
		return KEY_BACKSLASH;
	case XK_slash:
		return KEY_SLASH;
	case XK_bracketleft:
		return KEY_LBRACKET;
	case XK_bracketright:
		return KEY_RBRACKET;
	case XK_Escape:
		return KEY_ESCAPE;
	case XK_Caps_Lock:
		return KEY_CAPITAL;
	case XK_Tab:
		return KEY_TAB;
	case XK_Return:
		return KEY_RETURN;
	case XK_Control_L:
		return KEY_LCONTROL;
	case XK_Control_R:
		return KEY_RCONTROL;
	case XK_colon:
		return KEY_COLON;
	case XK_semicolon:
		return KEY_SEMICOLON;
	case XK_apostrophe:
		return KEY_APOSTROPHE;
	case XK_grave:
		return KEY_GRAVE;
	case XK_b:
		return KEY_B;
	case XK_a:
		return KEY_A;
	case XK_c:
		return KEY_C;
	case XK_d:
		return KEY_D;
	case XK_e:
		return KEY_E;
	case XK_f:
		return KEY_F;
	case XK_g:
		return KEY_G;
	case XK_h:
		return KEY_H;
	case XK_i:
		return KEY_I;
	case XK_j:
		return KEY_J;
	case XK_k:
		return KEY_K;
	case XK_l:
		return KEY_L;
	case XK_m:
		return KEY_M;
	case XK_n:
		return KEY_N;
	case XK_o:
		return KEY_O;
	case XK_p:
		return KEY_P;
	case XK_q:
		return KEY_Q;
	case XK_r:
		return KEY_R;
	case XK_s:
		return KEY_S;
	case XK_t:
		return KEY_T;
	case XK_u:
		return KEY_U;
	case XK_v:
		return KEY_V;
	case XK_w:
		return KEY_W;
	case XK_x:
		return KEY_X;
	case XK_y:
		return KEY_Y;
	case XK_z:
		return KEY_Z;
	case XK_F1:
		return KEY_F1;
	case XK_F2:
		return KEY_F2;
	case XK_F3:
		return KEY_F3;
	case XK_F4:
		return KEY_F4;
	case XK_F5:
		return KEY_F5;
	case XK_F6:
		return KEY_F6;
	case XK_F7:
		return KEY_F7;
	case XK_F8:
		return KEY_F8;
	case XK_F9:
		return KEY_F9;
	case XK_F10:
		return KEY_F10;
	case XK_F11:
		return KEY_F11;
	case XK_F12:
		return KEY_F12;
	case XK_F13:
		return KEY_F13;
	case XK_F14:
		return KEY_F14;
	case XK_F15:
		return KEY_F15;
	case XK_KP_0:
		return KEY_NUMPAD0;
	case XK_KP_1:
		return KEY_NUMPAD1;
	case XK_KP_2:
		return KEY_NUMPAD2;
	case XK_KP_3:
		return KEY_NUMPAD3;
	case XK_KP_4:
		return KEY_NUMPAD4;
	case XK_KP_5:
		return KEY_NUMPAD5;
	case XK_KP_6:
		return KEY_NUMPAD6;
	case XK_KP_7:
		return KEY_NUMPAD7;
	case XK_KP_8:
		return KEY_NUMPAD8;
	case XK_KP_9:
		return KEY_NUMPAD9;
	case XK_KP_Add:
		return KEY_ADD;
	case XK_KP_Subtract:
		return KEY_SUBTRACT;
	case XK_KP_Decimal:
		return KEY_DECIMAL;
	case XK_KP_Equal:
		return KEY_NUMPADEQUALS;
	case XK_KP_Divide:
		return KEY_DIVIDE;
	case XK_KP_Multiply:
		return KEY_MULTIPLY;
	case XK_KP_Enter:
		return KEY_NUMPADENTER;
	case XK_KP_Home:
		return KEY_NUMPAD7;
	case XK_KP_Up:
		return KEY_NUMPAD8;
	case XK_KP_Page_Up:
		return KEY_NUMPAD9;
	case XK_KP_Left:
		return KEY_NUMPAD4;
	case XK_KP_Begin:
		return KEY_NUMPAD5;
	case XK_KP_Right:
		return KEY_NUMPAD6;
	case XK_KP_End:
		return KEY_NUMPAD1;
	case XK_KP_Down:
		return KEY_NUMPAD2;
	case XK_KP_Page_Down:
		return KEY_NUMPAD3;
	case XK_KP_Insert:
		return KEY_NUMPAD0;
	case XK_KP_Delete:
		return KEY_DECIMAL;
	case XK_Up:
		return KEY_UP;
	case XK_Down:
		return KEY_DOWN;
	case XK_Left:
		return KEY_LEFT;
	case XK_Right:
		return KEY_RIGHT;
	case XK_Page_Up:
		return KEY_PGUP;
	case XK_Page_Down:
		return KEY_PGDOWN;
	case XK_Home:
		return KEY_HOME;
	case XK_End:
		return KEY_END;
	case XK_Num_Lock:
		return KEY_NUMLOCK;
	case XK_Print:
		return KEY_SYSRQ;
	case XK_Scroll_Lock:
		return KEY_SCROLL;
	case XK_Pause:
		return KEY_PAUSE;
	case XK_Shift_R:
		return KEY_RSHIFT;
	case XK_Shift_L:
		return KEY_LSHIFT;
	case XK_Alt_R:
		return KEY_RMENU;
	case XK_Alt_L:
		return KEY_LMENU;
	case XK_Insert:
		return KEY_INSERT;
	case XK_Delete:
		return KEY_DELETE;
	case XK_Super_L:
		return KEY_LWIN;
	case XK_Super_R:
		return KEY_RWIN;
	case XK_Menu:
		return KEY_APPS;
	default:
		break;
	}
#	endif
	return KEY_UNKNOWNN;
}
//--------------------------------------------------------------------------
