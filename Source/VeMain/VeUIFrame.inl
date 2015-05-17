////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIFrame.inl
//  Version:     v1.00
//  Created:     7/7/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeUIFrame::GetWidth()
{
	return m_f32Width;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeUIFrame::GetHeight()
{
	return m_f32Height;
}
//--------------------------------------------------------------------------
VE_INLINE void VeUIFrame::SetSize(VeFloat32 f32Width, VeFloat32 f32Height)
{
	m_f32Width = f32Width;
	m_f32Height = f32Height;
	UpdateSize();
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeUIBarHoriz::GetWidth()
{
	return m_f32Width;
}
//--------------------------------------------------------------------------
VE_INLINE void VeUIBarHoriz::SetWidth(VeFloat32 f32Width)
{
	m_f32Width = f32Width;
	UpdateSize();
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeUIBarVert::GetWidth()
{
	return VeFloat32(m_akPos[POS_CENTER].m_spSprite->GetWidth());
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeUIBarVert::GetHeight()
{
	return m_f32Height;
}
//--------------------------------------------------------------------------
VE_INLINE void VeUIBarVert::SetHeight(VeFloat32 f32Height)
{
	m_f32Height = f32Height;
	UpdateSize();
}
//--------------------------------------------------------------------------
