////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderFrame.inl
//  Version:     v1.00
//  Created:     5/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeRenderFramePass::Type VeRenderFramePass::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE VeRenderNode* VeRenderFramePass::GetNode()
{
	return m_pkNode;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeRenderFrameClick::GetVisibilityMask()
{
	return m_u32VisibilityMask;
}
//--------------------------------------------------------------------------
VE_INLINE VeRenderFrameTarget::Type VeRenderFrameTarget::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeRenderFrameTarget::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE const VeRenderNodeDataPtr& VeRenderFrameTarget::GetNode()
{
	return m_spData;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeRenderFrameTechnique::GetSchemeName()
{
	return m_kScheme;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeRenderFrameUnit::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeRenderFrameManager::GetFrameCount()
{
	return m_u32FrameCount;
}
//--------------------------------------------------------------------------
