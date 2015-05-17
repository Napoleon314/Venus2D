////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIScrollView.cpp
//  Version:     v1.00
//  Created:     14/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"

//--------------------------------------------------------------------------
VeImplementRTTI(VeUIScrollView, VeUIWidget);
//--------------------------------------------------------------------------
VeUIScrollView::VeUIScrollView() : m_f32Threshold(0), m_f32Rate(0)
	, m_f32VelMax(0), m_f32Friction(0), m_f32Damping(0), m_f32MoveBottom(0)
	, m_f32MoveTop(0), m_f32ScrollBarLen(0), m_f32Velocity(0)
	, m_f32InnerNodeStart(0), m_bTouched(false), m_bScroll(false)
	, m_bRollBack(false)
{
	SetEatEvent(true);
	m_spInner = VE_NEW VeSceneNode2D();
	m_spInner->SetZOrder(-1.0f);
	AttachChild(m_spInner);
}
//--------------------------------------------------------------------------
VeUIScrollView::~VeUIScrollView()
{

}
//--------------------------------------------------------------------------
void VeUIScrollView::SetTop()
{
	m_spInner->SetPositionY(m_f32MoveBottom);
	UpdateInnerVisible();
	m_bTouched = false;
	m_bRollBack = false;
	m_bScroll = false;
}
//--------------------------------------------------------------------------
void VeUIScrollView::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIScrollView::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	m_f32Threshold = g_pLua->GetExpression(pkElement->Attribute("threshold"), 0.0f);
	m_f32Rate = g_pLua->GetExpression(pkElement->Attribute("rate"), 0.0f);
	m_f32VelMax = g_pLua->GetExpression(pkElement->Attribute("vmax"), 0.0f);
	m_f32Friction = g_pLua->GetExpression(pkElement->Attribute("friction"), 0.0f);
	m_f32Damping = g_pLua->GetExpression(pkElement->Attribute("damping"), 0.0f);
	SetClipByRange(true);
	m_spInner->DetachAllChildren();
	VeXMLElement* pkProp = pkElement->FirstChildElement("properties");
	if(pkProp)
	{
		VeXMLElement* pkTemp = pkProp->FirstChildElement();
		while(pkTemp)
		{
			m_spInner->AttachChild(g_pUIManager->CreateWidget(pkTemp, m_pkParent));
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
	UpdateInnerBounding();
}
//--------------------------------------------------------------------------
void VeUIScrollView::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
bool VeUIScrollView::OnPress(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	m_spInner->BeginChildR();
	VeUIWidget* pkIter = m_spInner->NextChildByTypeR<VeUIWidget>();
	while(pkIter)
	{
		VeUIWidget* pkSubRes = pkIter->PressEvent(u32Time, u32Type, kPos);
		if(pkSubRes)
		{
			m_spHoldWidget = pkSubRes;
			break;
		}
		pkIter = m_spInner->NextChildByTypeR<VeUIWidget>();
	}
	m_spInner->EndChild();
	OnStart(kPos);
	return true;
}
//--------------------------------------------------------------------------
void VeUIScrollView::OnHoldDragMove(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	if(m_f32MoveTop < m_f32MoveBottom)
	{
		if(m_bScroll)
		{
			VeFloat32 f32Delta = kPos.y - m_kPre.y;
			if((m_f32InnerNodeStart > m_f32MoveBottom && (f32Delta > 0))
				|| (m_f32InnerNodeStart < m_f32MoveTop && (f32Delta < 0)))
			{
				f32Delta *= 0.3f;
				m_f32Velocity = 0;
			}
			else
			{
				m_f32Velocity = f32Delta * m_f32Rate;
				m_f32Velocity = VE_MIN(m_f32Velocity, m_f32VelMax);
				m_f32Velocity = VE_MAX(m_f32Velocity, -m_f32VelMax);
			}
			m_f32InnerNodeStart += f32Delta;
			m_spInner->SetPositionY(VeFloorf(m_f32InnerNodeStart));
			UpdateInnerVisible();
			UpdateScrollBar();
		}
		else
		{
			if(VeFabsf(kPos.y - m_kStart.y) > m_f32Threshold)
			{
				if(m_spHoldWidget)
				{
					m_spHoldWidget->OnCancel(u32Time, u32Type, kPos);
					m_spHoldWidget = NULL;
				}
				m_bScroll = true;
				m_f32InnerNodeStart = m_spInner->GetPositionY();
				OnBarShow();
			}
		}
		m_kPre = kPos;
	}
	if(!m_bScroll)
	{
		if(m_spHoldWidget)
		{
			m_spHoldWidget->OnHoldDragMove(u32Time, u32Type, kPos);
		}
	}
}
//--------------------------------------------------------------------------
void VeUIScrollView::OnRelease(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	if(!m_bScroll)
	{
		m_spInner->BeginChildR();
		VeUIWidget* pkIter = m_spInner->NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->ReleaseEvent(m_spHoldWidget, u32Time, u32Type, kPos);
			if(pkSubRes)
			{
				if(pkSubRes != m_spHoldWidget && m_spHoldWidget)
				{
					m_spHoldWidget->OnCancel(u32Time, u32Type, kPos);
				}
				m_spHoldWidget = NULL;
				break;
			}
			pkIter = m_spInner->NextChildByTypeR<VeUIWidget>();
		}
		m_spInner->EndChild();
	}
	OnEnd();
}
//--------------------------------------------------------------------------
void VeUIScrollView::OnCancel(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	if((!m_bScroll) && m_spHoldWidget)
	{
		m_spHoldWidget->OnCancel(u32Time, u32Type, kPos);
		m_spHoldWidget = NULL;
	}
	OnEnd();
}
//--------------------------------------------------------------------------
#define ROLLBACK_TIME 0.5f
//--------------------------------------------------------------------------
void VeUIScrollView::Visit(VeRenderQueue& kQueue)
{
	if(!m_bTouched)
	{
		VeFloat32 f32Delta = g_pTime->GetDeltaTime();
		if(m_f32Velocity > 0)
		{
			VeFloat32 f32PosY = m_spInner->GetPositionY();
			VeFloat32 f32Acce = m_f32Friction;
			if(f32PosY > m_f32MoveBottom)
			{
				f32Acce += (f32PosY - m_f32MoveBottom) * m_f32Damping;
			}
			m_f32Velocity = VE_MAX(m_f32Velocity - f32Acce * f32Delta, 0);
			if(m_f32Velocity > 0)
			{
				m_spInner->SetPositionY(VeFloorf(f32PosY + m_f32Velocity * f32Delta));
				UpdateInnerVisible();
			}
			else
			{
				m_bRollBack = true;
				m_f32RollBackTime = ROLLBACK_TIME;
				m_f32RollBackPosY = f32PosY;
			}
			UpdateScrollBar();
		}
		else if(m_f32Velocity < 0)
		{
			VeFloat32 f32PosY = m_spInner->GetPositionY();
			VeFloat32 f32Acce = -m_f32Friction;
			if(f32PosY < m_f32MoveTop)
			{
				f32Acce += (f32PosY - m_f32MoveTop) * m_f32Damping;
			}
			m_f32Velocity = VE_MIN(m_f32Velocity - f32Acce * f32Delta, 0);
			if(m_f32Velocity < 0)
			{
				m_spInner->SetPositionY(VeFloorf(f32PosY + m_f32Velocity * f32Delta));
				UpdateInnerVisible();
			}
			else
			{
				m_bRollBack = true;
				m_f32RollBackTime = ROLLBACK_TIME;
				m_f32RollBackPosY = f32PosY;
			}
			UpdateScrollBar();
		}
		else if(m_bRollBack)
		{
			if(m_f32RollBackTime <= 0)
			{
				m_bRollBack = false;
				m_f32RollBackTime = 0;
				m_f32RollBackPosY = 0;
			}
			else if(m_f32RollBackPosY > m_f32MoveBottom)
			{
				m_f32RollBackTime -= f32Delta;
				if(m_f32RollBackTime > 0)
				{
					VeFloat32 f32Offset = VeCosf((m_f32RollBackTime / ROLLBACK_TIME) * VE_MATH_PI_2_F);
					m_spInner->SetPositionY(VeFloorf(VeLerp(f32Offset, m_f32RollBackPosY, m_f32MoveBottom)));
					UpdateInnerVisible();
				}
				else
				{
					m_f32RollBackTime = 0;
					m_bRollBack = false;
					m_spInner->SetPositionY(VeFloorf(m_f32MoveBottom));
					UpdateInnerVisible();
				}
			}
			else if(m_f32RollBackPosY < m_f32MoveTop)
			{
				m_f32RollBackTime -= f32Delta;
				if(m_f32RollBackTime > 0)
				{
					VeFloat32 f32Offset = VeCosf((m_f32RollBackTime / ROLLBACK_TIME) * VE_MATH_PI_2_F);
					m_spInner->SetPositionY(VeFloorf(VeLerp(f32Offset, m_f32RollBackPosY, m_f32MoveTop)));
					UpdateInnerVisible();
				}
				else
				{
					m_f32RollBackTime = 0;
					m_bRollBack = false;
					m_spInner->SetPositionY(VeFloorf(m_f32MoveTop));
					UpdateInnerVisible();
				}
			}
			else
			{
				m_bRollBack = false;
				m_f32RollBackTime = 0;
				m_f32RollBackPosY = 0;
			}
			UpdateScrollBar();
			if(!m_bRollBack)
			{
				OnBarHide();
			}
		}
	}
	
	VeUIWidget::Visit(kQueue);
}
//--------------------------------------------------------------------------
void VeUIScrollView::UpdateInnerBounding()
{
	VeFloat32 f32Pos = m_spInner->GetPositionY();

	m_spInner->SetPositionY(0);
	VeBoundingBox2D kBound(1,1,0,0);
	m_spInner->BeginChild();
	VeUIWidget* pkIter = m_spInner->NextChildByType<VeUIWidget>();
	
	while(pkIter)
	{
		pkIter->UpdateBounding();
		kBound.AddBounds(pkIter->GetDerivedRange());
		pkIter = m_spInner->NextChildByType<VeUIWidget>();
	}
	m_spInner->EndChild();
	VeTransform2D kTransform;
	kTransform.Invert(m_spInner->GetDerivedTransform());
	kTransform.ApplyBounding(kBound, kBound);

	m_f32MoveBottom = m_kRange.MinBounds().y - kBound.MinBounds().y;
	m_f32MoveTop = m_kRange.MaxBounds().y - kBound.MaxBounds().y;

	if(m_f32MoveTop > m_f32MoveBottom)
	{
		m_f32MoveTop = m_f32MoveBottom;
	}

	f32Pos = VE_MAX(f32Pos, m_f32MoveTop);
	f32Pos = VE_MIN(f32Pos, m_f32MoveBottom);

	m_spInner->SetPositionY(f32Pos);
	UpdateInnerVisible();

	VeFloat32 f32FrameH = m_kRange.Height();
	VeFloat32 f32ContentH = VE_MAX(kBound.Height(), f32FrameH);
	m_f32ScrollBarLen = VeFloorf(f32FrameH * f32FrameH / f32ContentH);
	UpdateScrollBar();
}
//--------------------------------------------------------------------------
void VeUIScrollView::UpdateInnerVisible()
{
	UpdateBounding();
	m_spInner->BeginChild();
	VeUIWidget* pkIter = m_spInner->NextChildByType<VeUIWidget>();
	while(pkIter)
	{
		pkIter->UpdateBounding();
		const VeBoundingBox2D& kRange = pkIter->GetDerivedRange();
		if(m_kDerivedRange.Intersects(kRange))
		{
			pkIter->SetVisible(true);
		}
		else
		{
			pkIter->SetVisible(false);
		}
		pkIter = m_spInner->NextChildByType<VeUIWidget>();
	}
	m_spInner->EndChild();
}
//--------------------------------------------------------------------------
void VeUIScrollView::UpdateScrollBar()
{
	if(m_spBar)
	{
		m_spBar->SetPositionX(VeFloorf(m_kRange.MaxBounds().x) - m_spBar->GetWidth() * 0.5f - 2.0f);
		VeFloat32 f32Len = m_f32ScrollBarLen;
		VeFloat32 f32PosY = m_spInner->GetPositionY();
		if(f32PosY < m_f32MoveTop)
		{
			f32Len -= m_f32MoveTop - f32PosY;
			f32PosY = m_f32MoveTop;
		}
		else if(f32PosY > m_f32MoveBottom)
		{
			f32Len -= f32PosY - m_f32MoveBottom;
			f32PosY = m_f32MoveBottom;
		}
		m_spBar->SetHeight(f32Len);
		f32Len = m_spBar->GetHeight();
		VeFloat32 f32Rate = (m_f32MoveBottom - f32PosY)
			/ (m_f32MoveBottom - m_f32MoveTop);
		VeFloat32 f32Min = m_kRange.MinBounds().y + f32Len * 0.5f;
		VeFloat32 f32Max = m_kRange.MaxBounds().y - f32Len * 0.5f;
		m_spBar->SetPositionY(VeLerp(f32Rate, f32Min, f32Max));
	}
}
//--------------------------------------------------------------------------
void VeUIScrollView::Reset()
{
	m_f32Velocity = 0;
	m_f32InnerNodeStart = 0;
	m_bTouched = false;
	m_bScroll = false;
}
//--------------------------------------------------------------------------
void VeUIScrollView::OnStart(const VeVector2D& kPos)
{
	m_kStart = kPos;
	m_kPre = kPos;
	m_f32Velocity = 0;
	m_f32InnerNodeStart = 0;
	m_bTouched = true;
	m_bScroll = false;
	m_bRollBack = false;
}
//--------------------------------------------------------------------------
void VeUIScrollView::OnEnd()
{
	m_bTouched = false;
	m_bRollBack = false;
	VeFloat32 f32PosY = m_spInner->GetPositionY();
	if((f32PosY > m_f32MoveBottom) || (f32PosY < m_f32MoveTop))
	{
		m_bRollBack = true;
		m_f32RollBackTime = ROLLBACK_TIME;
		m_f32RollBackPosY = f32PosY;
		m_f32Velocity = 0;
	}
	else if(m_bScroll && m_f32Velocity == 0)
	{
		OnBarHide();
	}
	m_bScroll = false;
}
//--------------------------------------------------------------------------
void VeUIScrollView::OnBarShow()
{
	if(m_spBar)
	{
		m_spBar->StopAllActions();
		m_spBar->RunAction(VeMulColorTo2D::Create(0.1f, VeColor(1,1,1,1)));
	}
}
//--------------------------------------------------------------------------
void VeUIScrollView::OnBarHide()
{
	if(m_spBar)
	{
		m_spBar->StopAllActions();
		VeColor kColor = m_spBar->GetMulColor();
		if(kColor.a == 1.0f)
		{
			m_spBar->RunAction(VeSequence::Create(VeDelayTime::Create(0.3f),
				VeMulColorTo2D::Create(0.1f, VeColor(1,1,1,0)), NULL));
		}
		else
		{
			m_spBar->RunAction(VeSequence::Create(
				VeMulColorTo2D::Create(0.1f * (1.0f - kColor.a), VeColor(1,1,1,1)),
				VeDelayTime::Create(0.3f),
				VeMulColorTo2D::Create(0.1f, VeColor(1,1,1,0)), NULL));
		}		
	}
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIScrollView::Create()
{
	return VE_NEW VeUIScrollView;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIScrollView)
{
	Module() [
		Class< VeUIScrollView, Base<VeUIWidget> >()
	];
}
//--------------------------------------------------------------------------
