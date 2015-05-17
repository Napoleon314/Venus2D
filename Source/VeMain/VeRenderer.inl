////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderer.inl
//  Version:     v1.00
//  Created:     8/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeRenderer::GetWidth()
{
	return m_u32Width;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeRenderer::GetHeight()
{
	return m_u32Height;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeRenderer::GetWidthF()
{
	return m_f32Width;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeRenderer::GetHeightF()
{
	return m_f32Height;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeRenderer::GetInvWidthF()
{
	return m_f32InvWidth;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeRenderer::GetInvHeightF()
{
	return m_f32InvHeight;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeRenderer::IsInited()
{
	return m_bInited;
}
//--------------------------------------------------------------------------
