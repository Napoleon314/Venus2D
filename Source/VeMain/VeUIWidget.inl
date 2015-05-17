////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIWidget.inl
//  Version:     v1.00
//  Created:     8/2/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeUIWidget::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE VeString VeUIWidget::GetFullName()
{
	return m_pkParent ? (m_pkParent->GetFullName() + "/" + m_kName) : m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetEnable()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_ENABLE));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetVisible()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_VISIBLE));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetActive()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_ACTIVE));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetProcessInput()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_INPUT));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetClipByRange()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_CLIP));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetChecked()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_CHECKED));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetEatEvent()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_EAT_EVENT));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetShow()
{
	return VE_MASK_HAS_ANY(m_u32Flags, VE_MASK(STATE_SHOW));
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::GetDisplay()
{
	return GetShow() && GetVisible();
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUIWidget::IsRoot()
{
	return GetParent() ? true : false;
}
//--------------------------------------------------------------------------
VE_INLINE VeUIWidget* VeUIWidget::GetParent()
{
	return VeDynamicCast(VeUIWidget, m_pkParent);
}
//--------------------------------------------------------------------------
VE_INLINE void VeUIWidget::RegisterListener(Delegate& kDelegate)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VE_INLINE void VeUIWidget::UnregisterListener(Delegate& kDelegate)
{
	m_kEvent.DelDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeUIWidget::GetCurUpdateRangeFrame()
{
	return m_u32CurUpdateRangeFrame;
}
//--------------------------------------------------------------------------
VE_INLINE const VeBoundingBox2D& VeUIWidget::GetRange()
{
	return m_kRange;
}
//--------------------------------------------------------------------------
VE_INLINE const VeBoundingBox2D& VeUIWidget::GetDerivedRange()
{
	return m_kDerivedRange;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeUIWidget::GetIndex()
{
	return m_u32Index;
}
//--------------------------------------------------------------------------
VE_INLINE void VeUIWidget::SetTag(VeInt32 i32Tag)
{
	m_i32Tag = i32Tag;
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeUIWidget::GetTag()
{
	return m_i32Tag;
}
//--------------------------------------------------------------------------
VE_INLINE void VeUILayout::SetModal(bool bEnable)
{
	m_bModal = bEnable;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeUILayout::IsModal()
{
	return m_bModal;
}
//--------------------------------------------------------------------------
VE_INLINE VeSquare* VeUISquare::GetSquare()
{
	return m_spSquare;
}
//--------------------------------------------------------------------------
VE_INLINE VeSprite2D* VeUIImage::GetImage()
{
	return m_spImage;
}
//--------------------------------------------------------------------------
VE_INLINE VeDragonBonesEntity* VeUIDragonBones::GetEntity()
{
	return m_spEntity;
}
//--------------------------------------------------------------------------
VE_INLINE VeUIFrame* VeUIAlertFrame::GetEntity()
{
	return m_spFrame;
}
//--------------------------------------------------------------------------
VE_INLINE VeUIBarHoriz* VeUIAlertBarHoriz::GetEntity()
{
	return m_spBar;
}
//--------------------------------------------------------------------------
VE_INLINE VeSimpleText* VeUITextLabel::GetText()
{
	return m_spText;
}
//--------------------------------------------------------------------------
VE_INLINE VeUIWidget* VeUIRadioArea::GetCheckedWidget()
{
	return m_spChecked;
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeUIRadioArea::GetCheckedIndex()
{
	return m_spChecked ? VeInt32(m_spChecked->GetIndex()) : -1;
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeUIPageView::GetPageIndex()
{
	return m_i32PageIndex;
}
//--------------------------------------------------------------------------
VE_INLINE void VeUITextField::SetText(const VeChar8* pcText)
{
	m_kContent = pcText;
	CacheString();
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeUITextField::GetText()
{
	return m_kContent;
}
//--------------------------------------------------------------------------
