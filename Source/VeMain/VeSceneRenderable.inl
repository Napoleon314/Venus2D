////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneRenderable.inl
//  Version:     v1.00
//  Created:     20/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeSceneRenderable::GetGroup()
{
	return m_u32Group;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSprite2D::SetAnchor(const VeVector2D& kAnchor)
{
	if(kAnchor != m_kAnchor)
	{
		m_kAnchor = kAnchor;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector2D& VeSprite2D::GetAnchor()
{
	return m_kAnchor;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeSprite2D::GetFrameName()
{
	return m_kFrame.m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSprite2D::SetBlendFunc(BlendFunc eBlend)
{
	if(m_eBlend != eBlend)
	{
		if(m_eBlend == VeSceneRenderable2D::ALPHA_BLEND_MUL || eBlend == VeSceneRenderable2D::ALPHA_BLEND_MUL)
		{
			m_bDirty = true;
		}
		m_eBlend = eBlend;
		UpdateBlend();
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeSceneRenderable2D::BlendFunc VeSprite2D::GetBlendFunc()
{
	return m_eBlend;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeSprite2D::GetWidth()
{
	return m_kFrame.m_u16OriginW;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeSprite2D::GetHeight()
{
	return m_kFrame.m_u16OriginH;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeSingleChar::GetPixelWidth()
{
	return m_pkChar ? (m_pkChar->m_tSecond & 0xFFFF) : 0;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSingleChar::SetBias(VeFloat32 f32Bias)
{
	m_f32Bias = f32Bias;
	m_bDirty = true;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeSingleChar::GetBias()
{
	return m_f32Bias;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSquareFrame::SetRange(const VeBoundingBox2D& kRange)
{
	if(m_kRange != kRange)
	{
		m_kRange = kRange;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeBoundingBox2D& VeSquareFrame::GetRange()
{
	return m_kRange;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSquareFrame::SetBlendFunc(BlendFunc eBlend)
{
	if(m_eBlend != eBlend)
	{
		m_eBlend = eBlend;
		UpdateBlend();
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeSceneRenderable2D::BlendFunc VeSquareFrame::GetBlendFunc()
{
	return m_eBlend;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSquare::SetRange(const VeBoundingBox2D& kRange)
{
	if(m_kRange != kRange)
	{
		m_kRange = kRange;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeBoundingBox2D& VeSquare::GetRange()
{
	return m_kRange;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSquare::SetBlendFunc(BlendFunc eBlend)
{
	if(m_eBlend != eBlend)
	{
		m_eBlend = eBlend;
		UpdateBlend();
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeSceneRenderable2D::BlendFunc VeSquare::GetBlendFunc()
{
	return m_eBlend;
}
//--------------------------------------------------------------------------
