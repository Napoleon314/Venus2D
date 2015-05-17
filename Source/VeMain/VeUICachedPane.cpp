////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUICachedPane.cpp
//  Version:     v1.00
//  Created:     5/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"

//--------------------------------------------------------------------------
VeImplementRTTI(VeUICachedPanel, VeUIWidget);
//--------------------------------------------------------------------------
VeUICachedPanel::VeUICachedPanel() : m_pcRenderTarget(NULL)
	, m_pkRenderTarget(NULL), m_pkClear(NULL)
{
	m_kNode.m_tContent = this;
	m_pkDraw2DRoot = VE_NEW VeRenderNode();
	m_spRootNode2D = VE_NEW VeSceneNode2D();
	m_spRootNode2D->UpdateContext(m_pkDraw2DRoot);
	m_spRtRepainter = VE_NEW RtRepainter(this);
#	ifdef VE_ENABLE_DEVICE_LOST
	m_kRestoreDelegate.Set(this, &VeUICachedPanel::OnRestore);
#	endif
}
//--------------------------------------------------------------------------
VeUICachedPanel::~VeUICachedPanel()
{
	VE_ASSERT((!m_pcRenderTarget) && (!m_pkRenderTarget) && (!m_pkClear));
	m_spRootNode2D = NULL;
	VE_SAFE_DELETE(m_pkDraw2DRoot);
	m_spRtRepainter->m_pkParent = NULL;
	m_spRtRepainter = NULL;
}
//--------------------------------------------------------------------------
void VeUICachedPanel::AttachChild(VeSceneNode* pkChild)
{
	VeUIWidget* pkWidget = VeDynamicCast(VeUIWidget, pkChild);
	if(pkWidget)
	{
		m_spRootNode2D->AttachChild(pkWidget);
		pkWidget->SetRepainter(m_spRtRepainter);
	}
	else
	{
		VeUIWidget::AttachChild(pkChild);
	}
}
//--------------------------------------------------------------------------
void VeUICachedPanel::OnShow()
{
	VeUIWidget::OnShow();
	if(!m_pcRenderTarget)
	{
		VeUInt16 u16Width = VeUInt16(VeCeilf(m_kRange.Width()));
		VeUInt16 u16Height = VeUInt16(VeCeilf(m_kRange.Height()));

		m_pcRenderTarget = g_pRenderer->CreateRenderTarget2D(
			VeRenderer::FMT_R8G8B8A8_UNORM, u16Width, u16Height);
		VE_ASSERT(m_pcRenderTarget);
		VeMemoryOStream kStream;
		
		kStream << VeUInt32(2);
		kStream << VeRenderTick::RS_VIEWPORT;
		kStream << VeUInt32(0);
		kStream << VeVector4D(0, 0, VeFloat32(u16Width), VeFloat32(u16Height));
		kStream << VeRenderTick::OM_RENDER_TARGET_VIEW;
		kStream.AppendStringAligned4(m_pcRenderTarget, (VeInt32)VeStrlen(m_pcRenderTarget));
		kStream << VeUInt32(0);
		kStream << VeUInt32(0);
		VE_ASSERT(!m_pkRenderTarget);
		m_pkRenderTarget = VE_NEW VeRenderNode;
		g_pRenderer->CreateRenderNodeData("", kStream, &m_pkRenderTarget->m_spData);
		kStream.Reset();

		kStream << VeUInt32(0);
		kStream << VeUInt32(1);
		kStream << VeRenderCall::CLEAR;
		kStream << true;
		kStream << false;
		kStream << false;
		kStream << VeUInt8(0);
		kStream << 1.0f;
		VeVector<VeColor> kColorArray;
		kColorArray.PushBack(VeColor::ZERO);
		kStream << kColorArray;
		VE_ASSERT(!m_pkClear);
		m_pkClear = VE_NEW VeRenderNode;
		g_pRenderer->CreateRenderNodeData("", kStream, &m_pkClear->m_spData);
		kStream.Reset();
		
		m_pkClear->SetParent(m_pkRenderTarget);

		VeSprite2DPtr spQuad = VE_NEW VeSprite2D();
		spQuad->SetTexture(m_pcRenderTarget);
		spQuad->SetBlendFunc(VeSceneRenderable2D::ALPHA_BLEND_MUL);
		spQuad->SetAnchor(0.0f, 0.0f, -m_kRange.m_kMin.x, -m_kRange.m_kMin.y);
		AttachRenderable(spQuad);

		g_pRenderFrameManager->AddPreRenderTask(m_kNode);

		VeFixedString kName;
		kStream << VeUInt32(3);
		kStream << VeRenderTick::VS_CONSTANT_BUFFER;
		kName = m_pcRenderTarget;
		kStream.AppendStringAligned4(kName, kName.GetLength());
		kStream << VeUInt32(0);
		kStream << VeRenderTick::OM_DEPTH_STENCIL_STATE;
		kName = "no_depth";
		kStream.AppendStringAligned4(kName, kName.GetLength());
		kStream << VeUInt32(0);
		kStream << VeRenderTick::RS_STATE;
		kName = "draw_2d";
		kStream.AppendStringAligned4(kName, kName.GetLength());
		kStream << VeUInt32(0);
		g_pRenderer->CreateRenderNodeData("", kStream, &m_pkDraw2DRoot->m_spData);
		kStream.Reset();

		m_spRootNode2D->SetPosition(-m_kRange.m_kMin);

#		ifdef VE_ENABLE_DEVICE_LOST
		g_pRenderer->AddRestoreDelegate(m_kRestoreDelegate);
#		endif
	}
}
//--------------------------------------------------------------------------
void VeUICachedPanel::OnHide()
{
	VeUIWidget::OnHide();
	if(m_pcRenderTarget)
	{
#		ifdef VE_ENABLE_DEVICE_LOST
		m_kRestoreDelegate.Detach();
#		endif
		m_kNode.Detach();
		DetachAllRenderables();
		g_pRenderer->DestoryRenderTarget2D(m_pcRenderTarget);
		m_pcRenderTarget = NULL;
		VE_SAFE_DELETE(m_pkRenderTarget);
		VE_SAFE_DELETE(m_pkClear);
	}
}
//--------------------------------------------------------------------------
void VeUICachedPanel::Render()
{
	VE_ASSERT(m_spRootNode2D);
	m_pkClear->LinkToParent();
	g_pRenderer->Render(m_pkRenderTarget);
	m_pkDraw2DRoot->SetParent(m_pkRenderTarget);
	m_spRootNode2D->Visit(m_kRenderQueue);
	m_kRenderQueue.LinkRenderable(VE_INFINITE, 0, VE_UINT16_MAX);
	g_pRenderer->Render(m_pkRenderTarget);
	m_kNode.Detach();
}
//--------------------------------------------------------------------------
VeUIWidget* VeUICachedPanel::PressEvent(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	VeUIWidget* pkRes(NULL);
	if(GetVisible() && GetProcessInput() && IsIn(kPos))
	{
		m_spRootNode2D->SetDerivedTransform(GetDerivedTransform());
		m_spRootNode2D->BeginChildR();
		VeUIWidget* pkIter = m_spRootNode2D->NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->PressEvent(u32Time, u32Type, kPos);
			if(pkSubRes)
			{
				pkRes = pkSubRes;
				break;
			}
			pkIter = m_spRootNode2D->NextChildByTypeR<VeUIWidget>();
		}
		m_spRootNode2D->EndChild();
		m_spRootNode2D->NotifyRefresh();
		if((!pkRes) && OnPress(u32Time, u32Type, kPos))
		{
			if(GetEatEvent()) pkRes = this;
		}
	}
	return pkRes;
}
//--------------------------------------------------------------------------
VeUIWidget* VeUICachedPanel::ReleaseEvent(VeUIWidgetPtr& spHold,
	VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos)
{
	VeUIWidget* pkRes(NULL);
	if(GetVisible() && GetProcessInput() && IsIn(kPos))
	{
		m_spRootNode2D->SetDerivedTransform(GetDerivedTransform());
		m_spRootNode2D->BeginChildR();
		VeUIWidget* pkIter = m_spRootNode2D->NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->ReleaseEvent(spHold, u32Time, u32Type, kPos);
			if(pkSubRes)
			{
				pkRes = pkSubRes;
				break;
			}
			pkIter = m_spRootNode2D->NextChildByTypeR<VeUIWidget>();
		}
		m_spRootNode2D->EndChild();
		m_spRootNode2D->NotifyRefresh();
		if(!pkRes)
		{
			if(spHold == this)
			{
				OnRelease(u32Time, u32Type, kPos);
			}
			else
			{
				OnDrop(u32Time, u32Type, kPos);
				if(spHold) spHold->OnCancel(u32Time, u32Type, kPos);
			}
			pkRes = spHold;
		}
	}
	return pkRes;
}
//--------------------------------------------------------------------------
VeUIWidget* VeUICachedPanel::CurMoveEvent(VeUIWidgetPtr& spCursor,
	VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos)
{
	VeUIWidget* pkRes(NULL);
	if(GetVisible() && GetProcessInput() && IsIn(kPos))
	{
		m_spRootNode2D->SetDerivedTransform(GetDerivedTransform());
		m_spRootNode2D->BeginChildR();
		VeUIWidget* pkIter = m_spRootNode2D->NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->CurMoveEvent(spCursor, u32Time, u32Type, kPos);
			if(pkSubRes)
			{
				pkRes = pkSubRes;
				break;
			}
			pkIter = m_spRootNode2D->NextChildByTypeR<VeUIWidget>();
		}
		m_spRootNode2D->EndChild();
		m_spRootNode2D->NotifyRefresh();
		if(!pkRes && OnProcessCurMove(u32Time, kPos))
		{
			if(u32Type)
			{
				if(spCursor != this)
				{
					if(spCursor) spCursor->OnDragLeave(u32Time, u32Type, kPos);
					OnDragEnter(u32Time, u32Type, kPos);
					spCursor = this;
				}
				else
				{
					OnDragMove(u32Time, u32Type, kPos);
				}
			}
			else
			{
				OnCurMove(u32Time, kPos);
				spCursor = this;
			}
			if(GetEatEvent()) pkRes = this;
		}
	}
	return pkRes;
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUICachedPanel::Create()
{
	return VE_NEW VeUICachedPanel;
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeUICachedPanel::OnRestore()
{
	if(!m_kNode.IsAttach())
	{
		g_pRenderFrameManager->AddPreRenderTask(m_kNode);
	}
	NotifyRepaint();
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUICachedPanel)
{
	Module() [
		Class< VeUICachedPanel, Base<VeUIWidget> >()
	];
}
//--------------------------------------------------------------------------
VeUICachedPanel::RtRepainter::RtRepainter(VeUICachedPanel* pkParent)
	: m_pkParent(pkParent)
{

}
//--------------------------------------------------------------------------
void VeUICachedPanel::RtRepainter::Notify()
{
	if(m_pkParent)
	{
		if(!m_pkParent->m_kNode.IsAttach())
		{
			g_pRenderFrameManager->AddPreRenderTask(m_pkParent->m_kNode);
		}
		m_pkParent->NotifyRepaint();
	}
}
//--------------------------------------------------------------------------
