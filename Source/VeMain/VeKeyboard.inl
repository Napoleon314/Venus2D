////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeKeyboard.inl
//  Version:     v1.00
//  Created:     7/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeKeyboard::OnKeyDown(InputKey eKey)
{
	if(m_abyKeyState[eKey] != 0x80)
	{
		m_abyKeyState[eKey] = 0x80;
		if(eKey == KEY_LCONTROL || eKey == KEY_RCONTROL)
			VE_MASK_ADD(m_u32Modifiers, CTRL);
		else if(eKey == KEY_LSHIFT || eKey == KEY_RSHIFT)
			VE_MASK_ADD(m_u32Modifiers, SHIFT);
		else if(eKey == KEY_LMENU || eKey == KEY_RMENU)
			VE_MASK_ADD(m_u32Modifiers, ALT);
		g_pInputManager->AppendMessage(VeInputMessage::DT_KEYBOARD,
			VeInputMessage::KIT_KEY_PRESSED, g_pTime->GetTimeUInt(), eKey);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeKeyboard::OnKeyUp(InputKey eKey)
{
	if(m_abyKeyState[eKey] == 0x80)
	{
		m_abyKeyState[eKey] = 0x0;
		if(eKey == KEY_LCONTROL || eKey == KEY_RCONTROL)
			VE_MASK_DEL(m_u32Modifiers, CTRL);
		else if(eKey == KEY_LSHIFT || eKey == KEY_RSHIFT)
			VE_MASK_DEL(m_u32Modifiers, SHIFT);
		else if(eKey == KEY_LMENU || eKey == KEY_RMENU)
			VE_MASK_DEL(m_u32Modifiers, ALT);
		g_pInputManager->AppendMessage(VeInputMessage::DT_KEYBOARD,
			VeInputMessage::KIT_KEY_RELEASED, g_pTime->GetTimeUInt(), eKey);
	}
}
//--------------------------------------------------------------------------
VE_INLINE bool VeKeyboard::IsKeyDown(InputKey eKey)
{
	return (m_abyKeyState[eKey] & 0x80) ? true : false;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeKeyboard::GetModifiers()
{
	return m_u32Modifiers;
}
//--------------------------------------------------------------------------
