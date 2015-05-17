////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeApplication.inl
//  Version:     v1.00
//  Created:     7/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeApplication::Init()
{
	g_pInputManager->RegisterListener(VeDelegate(InputCallback));
	OnInit();
}
//--------------------------------------------------------------------------
VE_INLINE void VeApplication::Term()
{
	while(g_pResourceManager->HasTask())
	{
		g_pResourceManager->Update();
	}
	OnTerm();
	g_pInputManager->UnregisterListener(VeDelegate(InputCallback));
}
//--------------------------------------------------------------------------
VE_INLINE void VeApplication::SetProcessInput(bool bEnable)
{
	m_bProcessInput = bEnable;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeApplication::GetProcessInput()
{
	return m_bProcessInput;
}
//--------------------------------------------------------------------------
VE_INLINE void VeApplication::QuitApp()
{
	if(!m_bQuit)
	{
		m_bQuit = OnClose();
	}
	m_bQuit = true;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeApplication::IsAppQuit()
{
	return m_bQuit;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeApplication::GetFPS()
{
	return m_u32FPS;
}
//--------------------------------------------------------------------------
VE_INLINE void VeApplication::Hide()
{
	if(m_bShow)
	{
		m_bShow = false; 
		OnHide();
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeApplication::Show()
{
	if(!m_bShow)
	{
		m_bShow = true;
		OnShow();
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeApplication::Inactive()
{
	if(m_bActive)
	{
		m_bActive = false; 
		OnInactive();
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeApplication::Active()
{
	if(!m_bActive)
	{
		m_bActive = true; 
		OnActive();
	}
}
//--------------------------------------------------------------------------
