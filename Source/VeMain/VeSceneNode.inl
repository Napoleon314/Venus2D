////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneNode.inl
//  Version:     v1.00
//  Created:     11/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode::SetVisibleMask(VeUInt32 u32Mask)
{
	m_u32VisibleMask = u32Mask;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeSceneNode::GetVisibleMask()
{
	return m_u32VisibleMask;
}
//--------------------------------------------------------------------------
VE_INLINE VeSceneNode* VeSceneNode::GetParent()
{
	return m_pkParent;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetPosition(VeFloat32 x, VeFloat32 y)
{
	SetPosition(VeVector2D(x, y));
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetPosition(const VeVector2D& kPos)
{
	if(kPos != m_kPosition)
	{
		m_kPosition = kPos;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetPositionX(VeFloat32 x)
{
	if(x != m_kPosition.x)
	{
		m_kPosition.x = x;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetPositionY(VeFloat32 y)
{
	if(y != m_kPosition.y)
	{
		m_kPosition.y = y;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector2D& VeSceneNode2D::GetPosition()
{
	return m_kPosition;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeSceneNode2D::GetPositionX()
{
	return m_kPosition.x;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeSceneNode2D::GetPositionY()
{
	return m_kPosition.y;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetScale(VeFloat32 f32Scale)
{
	SetScale(f32Scale, f32Scale);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetScale(VeFloat32 x, VeFloat32 y)
{
	SetScale(VeVector2D(x, y));
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetScale(const VeVector2D& kScale)
{
	if(kScale != m_kScale)
	{
		m_kScale = kScale;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetScaleX(VeFloat32 f32ScaleX)
{
	if(m_kScale.x != f32ScaleX)
	{
		m_kScale.x = f32ScaleX;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetScaleY(VeFloat32 f32ScaleY)
{
	if(m_kScale.y != f32ScaleY)
	{
		m_kScale.y = f32ScaleY;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector2D& VeSceneNode2D::GetScale()
{
	return m_kScale;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetRotate(VeFloat32 f32Rotate)
{
	SetSkew(f32Rotate, f32Rotate);
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetSkew(VeFloat32 x, VeFloat32 y)
{
	SetSkew(VeVector2D(x,y));
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetSkew(const VeVector2D& kSkew)
{
	if(kSkew != m_kSkew)
	{
		m_kSkew = kSkew;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeSceneNode2D::GetRotate()
{
	return m_kSkew.x * 0.5f + m_kSkew.y * 0.5f;
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector2D& VeSceneNode2D::GetSkew()
{
	return m_kSkew;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetMulColor(
	VeFloat32 r, VeFloat32 g, VeFloat32 b, VeFloat32 a)
{
	SetMulColor(VeColor(r, g, b, a));
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetMulColor(const VeColor& kColor)
{
	if(kColor != m_kMulColor)
	{
		m_kMulColor = kColor;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeColor& VeSceneNode2D::GetMulColor()
{
	return m_kMulColor;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetAddColor(VeFloat32 r, VeFloat32 g,
	VeFloat32 b, VeFloat32 a)
{
	SetAddColor(VeColor(r, g, b, a));
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetAddColor(const VeColor& kColor)
{
	if(kColor != m_kAddColor)
	{
		m_kAddColor = kColor;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeColor& VeSceneNode2D::GetAddColor()
{
	return m_kAddColor;
}
//--------------------------------------------------------------------------
VE_INLINE void VeSceneNode2D::SetZOrder(VeFloat32 f32ZOrder)
{
	if(m_f32ZOrder != f32ZOrder)
	{
		UpdateZOrder(f32ZOrder);
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeSceneNode2D::GetZOrder()
{
	return m_f32ZOrder;
}
//--------------------------------------------------------------------------
