////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIWidget.cpp
//  Version:     v1.00
//  Created:     8/2/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeUIWidget.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeUIWidget, VeSceneNode2D);
//--------------------------------------------------------------------------
VeUIWidget::VeUIWidget() : m_pkParent(NULL)
	, m_u32Flags(VE_MASK(STATE_ENABLE) | VE_MASK(STATE_VISIBLE) | VE_MASK(STATE_INPUT))
	, m_u32CurUpdateRangeFrame(0), m_u32Index(0), m_u32MaxIndex(0), m_i32Tag(0)
{
	m_kNode.m_tContent = this;
	m_kSelfDelegate.Set(this, &VeUIWidget::EventCallback);
	RegisterListener(m_kSelfDelegate);
}
//--------------------------------------------------------------------------
VeUIWidget::~VeUIWidget()
{
	
}
//--------------------------------------------------------------------------
void VeUIWidget::GetChildrenWidget(lua_State* pkState)
{
	VeLuaBind::NewTable(pkState);
	VeUInt32 i(0);
	BeginChild();
	VeUIWidget* pkIter = NextChildByType<VeUIWidget>();
	while(pkIter)
	{
		VeLuaBind::RetParam(pkState, pkIter);
		VeLuaBind::RawSet(pkState, -2, ++i);
		pkIter = NextChildByType<VeUIWidget>();
	}
	EndChild();
	VeLuaBind::ManualReturn(1);
}
//--------------------------------------------------------------------------
void VeUIWidget::SetEnable(bool bEnable)
{
	bool bCur = GetEnable();
	if(bCur != bEnable)
	{
		if(bEnable)
		{
			VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_ENABLE));
		}
		else
		{
			VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_ENABLE));
		}
		UpdateState();
		m_kEvent.Callback(this, bEnable ? EVT_ENABLE : EVT_DISABLE);
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::SetVisible(bool bVisible)
{
	bool bCur = GetVisible();
	if(bCur != bVisible)
	{
		if(bVisible)
		{
			VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_VISIBLE));
		}
		else
		{
			VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_VISIBLE));
		}
		UpdateState();
		if(GetShow())
		{
			m_kEvent.Callback(this, bVisible ? EVT_SHOW : EVT_HIDE);
		}
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::SetActive(bool bActive)
{
	bool bCur = GetActive();
	if(bCur != bActive)
	{
		if(bActive)
		{
			VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_ACTIVE));
		}
		else
		{
			VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_ACTIVE));
		}
		UpdateState();
		m_kEvent.Callback(this, bActive ? EVT_ACTIVE : EVT_INACTIVE);
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::SetProcessInput(bool bProcess)
{
	bool bCur = GetProcessInput();
	if(bCur != bProcess)
	{
		if(bProcess)
		{
			VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_INPUT));
		}
		else
		{
			VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_INPUT));
		}
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::SetClipByRange(bool bClip)
{
	bool bCur = GetClipByRange();
	if(bCur != bClip)
	{
		if(bClip)
		{
			VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_CLIP));
			VE_ASSERT(!m_pkRenderNode);
			m_pkRenderNode = VE_NEW VeRenderNode;
			m_pkRenderNode->SetParent(GetDraw2DRoot());
			VeMemoryOStream kStream;
			kStream << VeUInt32(2);
			kStream << VeRenderTick::RS_SCISSOR_RECT;
			kStream << VeUInt32(0);
			kStream << VeUInt16(0);
			kStream << VeUInt16(0);
			kStream << VeUInt16(0);
			kStream << VeUInt16(0);
			kStream << VeRenderTick::RS_STATE;
			VeFixedString kName = "draw_2d_clip";
			kStream.AppendStringAligned4(kName, kName.GetLength());
			kStream << VeUInt32(0);
			VeRenderNodeDataPtr spData;
			g_pRenderer->CreateRenderNodeData("", kStream, &spData);
			m_pkRenderNode->SetData(spData);
			UpdateContext();
		}
		else
		{
			VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_CLIP));
			VE_SAFE_DELETE(m_pkRenderNode);
			UpdateContext();
		}
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::SetChecked(bool bChecked)
{
	bool bCur = GetChecked();
	if(bCur != bChecked)
	{
		if(bChecked)
		{
			VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_CHECKED));
		}
		else
		{
			VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_CHECKED));
		}
		UpdateState();
		m_kEvent.Callback(this, bChecked ? EVT_CHECK : EVT_UNCHECK);
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::SetEatEvent(bool bEat)
{
	bool bCur = GetEatEvent();
	if(bCur != bEat)
	{
		if(bEat)
		{
			VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_EAT_EVENT));
		}
		else
		{
			VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_EAT_EVENT));
		}
		UpdateState();
	}
}
//--------------------------------------------------------------------------
bool VeUIWidget::IsIn(const VeVector2D& kPos)
{
	UpdateBounding();
	return m_kDerivedRange.Intersects(kPos);
}
//--------------------------------------------------------------------------
VeUIWidget* VeUIWidget::PressEvent(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	VeUIWidget* pkRes(NULL);
	if(GetVisible() && GetProcessInput() && IsIn(kPos))
	{
		BeginChildR();
		VeUIWidget* pkIter = NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->PressEvent(u32Time, u32Type, kPos);
			if(pkSubRes)
			{
				pkRes = pkSubRes;
				break;
			}
			pkIter = NextChildByTypeR<VeUIWidget>();
		}
		EndChild();
		if((!pkRes) && OnPress(u32Time, u32Type, kPos))
		{
			if(GetEatEvent()) pkRes = this;
		}
	}
	return pkRes;
}
//--------------------------------------------------------------------------
VeUIWidget* VeUIWidget::ReleaseEvent(VeUIWidgetPtr& spHold,
	VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos)
{
	VeUIWidget* pkRes(NULL);
	if(GetVisible() && GetProcessInput() && IsIn(kPos))
	{
		BeginChildR();
		VeUIWidget* pkIter = NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->ReleaseEvent(spHold, u32Time, u32Type, kPos);
			if(pkSubRes)
			{
				pkRes = pkSubRes;
				break;
			}
			pkIter = NextChildByTypeR<VeUIWidget>();
		}
		EndChild();
		if((!pkRes) && GetEatEvent())
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
VeUIWidget* VeUIWidget::CurMoveEvent(VeUIWidgetPtr& spCursor,
	VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos)
{
	VeUIWidget* pkRes(NULL);
	if(GetVisible() && GetProcessInput() && IsIn(kPos))
	{
		BeginChildR();
		VeUIWidget* pkIter = NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->CurMoveEvent(spCursor, u32Time, u32Type, kPos);
			if(pkSubRes)
			{
				pkRes = pkSubRes;
				break;
			}
			pkIter = NextChildByTypeR<VeUIWidget>();
		}
		EndChild();
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
VeUIWidget* VeUIWidget::PressEvent(VeUInt32 u32Time,
	VeKeyboard::InputKey eKey)
{
	VeUIWidget* pkRes(NULL);
	if(GetVisible() && GetProcessInput())
	{
		BeginChildR();
		VeUIWidget* pkIter = NextChildByTypeR<VeUIWidget>();
		while(pkIter)
		{
			VeUIWidget* pkSubRes = pkIter->PressEvent(u32Time, eKey);
			if(pkSubRes)
			{
				pkRes = pkSubRes;
				break;
			}
			pkIter = NextChildByTypeR<VeUIWidget>();
		}
		EndChild();
		if((!pkRes) && OnPress(u32Time, eKey))
		{
			if(GetEatEvent()) pkRes = this;
		}
	}
	return pkRes;
}
//--------------------------------------------------------------------------
void VeUIWidget::UpdateRange(VeFloat32 x, VeFloat32 y,
	VeFloat32 w, VeFloat32 h)
{
	m_kRange.SetBounds(VeVector2D(x,y), VeVector2D(x + w, y + h));
}
//--------------------------------------------------------------------------
void VeUIWidget::UpdateBounding()
{
	UpdateFromParent();
	bool bUpdate = m_u32UpdateFrame > m_u32CurUpdateRangeFrame;
	if(bUpdate)
	{
		m_kDerivedTransform.ApplyBounding(m_kDerivedRange, m_kRange);
	}
	bool bChange(false);
	BeginChild();
    VeUIWidget* pkIter = NextChildByType<VeUIWidget>();
	while(pkIter)
	{
		pkIter->UpdateBounding();
		if(bUpdate || (pkIter->m_u32CurUpdateRangeFrame > m_u32CurUpdateRangeFrame))
		{
			m_kDerivedRange.AddBounds(pkIter->GetDerivedRange());
			bChange = true;
		}
        pkIter = NextChildByType<VeUIWidget>();
	}
	EndChild();
	if(bUpdate || bChange)
	{
		m_u32CurUpdateRangeFrame = g_pRenderFrameManager->GetFrameCount();
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::UpdateChildren()
{
	m_u32MaxIndex = 0;
	BeginChild();
    VeUIWidget* pkIter = NextChildByType<VeUIWidget>();
	while(pkIter)
	{
		pkIter->m_u32Index = m_u32MaxIndex++;
        pkIter = NextChildByType<VeUIWidget>();
	}
	EndChild();
}
//--------------------------------------------------------------------------
void VeUIWidget::EventCallback(const VeUIWidgetPtr& spWidget,
	VeUInt32 u32Event)
{
	OnEvent(spWidget, u32Event);
}
//--------------------------------------------------------------------------
void VeUIWidget::Visit(VeRenderQueue& kQueue)
{
	if(GetVisible())
	{
		if(m_pkRenderNode)
		{
			UpdateBounding();
			VeRSScissorRectTick* pkScissor = (VeRSScissorRectTick*)m_pkRenderNode->m_spData->m_kTickList.GetHeadNode()->m_tContent;
			pkScissor->m_i16Left = VeInt16(m_kDerivedRange.MinBounds().x);
			pkScissor->m_i16Top = VeInt16(m_kDerivedRange.MinBounds().y);
			pkScissor->m_i16Width = VeInt16(m_kDerivedRange.Width());
			pkScissor->m_i16Height = VeInt16(m_kDerivedRange.Height());
		}
		VeSceneNode2D::Visit(kQueue);
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::OnShow()
{
	VE_MASK_ADD(m_u32Flags, VE_MASK(STATE_SHOW));
	if(GetVisible())
	{
		m_kEvent.Callback(this, EVT_SHOW);
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::OnHide()
{
	VE_MASK_DEL(m_u32Flags, VE_MASK(STATE_SHOW));
	if(GetVisible())
	{
		m_kEvent.Callback(this, EVT_HIDE);
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIWidget::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUIWidget::From(VeXMLElement* pkElement)
{
	VeSceneNode2D::From(pkElement);
	m_kName = pkElement->Attribute("name");
	VeFloat32 ox = g_pLua->GetExpression(pkElement->Attribute("ox"), 0.0f);
	VeFloat32 oy = g_pLua->GetExpression(pkElement->Attribute("oy"), 0.0f);
	VeFloat32 w = g_pLua->GetExpression(pkElement->Attribute("w"), 0.0f);
	VeFloat32 h = g_pLua->GetExpression(pkElement->Attribute("h"), 0.0f);
	UpdateRange(ox, oy, w, h);
	SetEnable(pkElement->Attribute("enable", true));
	SetVisible(pkElement->Attribute("visible", true));
	SetProcessInput(pkElement->Attribute("input", true));
	SetClipByRange(pkElement->Attribute("clip", false));
	SetChecked(pkElement->Attribute("check", false));
	SetEatEvent(pkElement->Attribute("eat", GetEatEvent()));
	VeXMLElement* pkEvents = pkElement->FirstChildElement("events");
	if(pkEvents)
	{
		VeXMLElement* pkTemp = pkEvents->FirstChildElement();
		while(pkTemp)
		{
			const VeChar8* pcValue = pkTemp->Value();
			const VeChar8* pcEvent = pkTemp->GetAttribute("event");
			if(pcValue && pcEvent)
			{
				VePair<VeString,VeInt32>& kEvent = m_kLuaEventMap[pcValue];
				kEvent.m_tFirst = pcEvent;
				kEvent.m_tSecond = 0;
			}
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIWidget::Create()
{
	return VE_NEW VeUIWidget;
}
//--------------------------------------------------------------------------
void VeUIWidget::Parse(const VeSceneNode2DPtr& spNode,
	VeXMLElement* pkElement)
{
	NodeType eType = NodeTypeLua::ToEnum(pkElement->Attribute("type", "atlas"), NODE_MAX);
	switch(eType)
	{
	case NODE_TEX:
		{
			VeSprite2DPtr spEnt = VE_NEW VeSprite2D(pkElement->Attribute("res", ""));
			VeFloat32 ax = g_pLua->GetExpression(pkElement->Attribute("ax"), 0.5f);
			VeFloat32 ay = g_pLua->GetExpression(pkElement->Attribute("ay"), 0.5f);
			VeFloat32 aox = g_pLua->GetExpression(pkElement->Attribute("aox"), 0.0f);
			VeFloat32 aoy = g_pLua->GetExpression(pkElement->Attribute("aoy"), 0.0f);
			spEnt->SetAnchor(ax, ay, aox, aoy, pkElement->Attribute("afloor", true));
			VeSceneNode2DPtr spNewNode = VE_NEW VeSceneNode2D;
			spNewNode->AttachRenderable(spEnt);
			spNewNode->From(pkElement);
			spNode->AttachChild(spNewNode);
		}
		break;
	case NODE_FRAME:
		{
			VeFloat32 fw = g_pLua->GetExpression(pkElement->Attribute("fw"), 0.0f);
			VeFloat32 fh = g_pLua->GetExpression(pkElement->Attribute("fh"), 0.0f);
			const VeChar8* apcSlot[VeUIFrame::POS_NUM] =
			{
				pkElement->GetAttribute("lt"),
				pkElement->GetAttribute("rt"),
				pkElement->GetAttribute("lb"),
				pkElement->GetAttribute("rb"),
				pkElement->GetAttribute("t"),
				pkElement->GetAttribute("l"),
				pkElement->GetAttribute("r"),
				pkElement->GetAttribute("b"),
				pkElement->GetAttribute("c")
			};
			VeUIFramePtr spFrame = VE_NEW VeUIFrame;
			spFrame->SetFrame(apcSlot);
			spFrame->SetSize(fw, fh);
			spNode->AttachChild(spFrame);
		}
		break;
	case NODE_BAR:
		{
			VeFloat32 bw = g_pLua->GetExpression(pkElement->Attribute("bw"), 0.0f);
			const VeChar8* apcSlot[VeUIBarHoriz::POS_NUM] =
			{
				pkElement->GetAttribute("l"),
				pkElement->GetAttribute("r"),
				pkElement->GetAttribute("c")
			};
			VeUIBarHorizPtr spBar = VE_NEW VeUIBarHoriz;
			spBar->SetFrame(apcSlot);
			spBar->SetWidth(bw);
			spNode->AttachChild(spBar);
		}
		break;
	case NODE_TEXT:
		{
			const VeChar8* pcName = pkElement->GetAttribute("font");
			if(pcName)
			{
				VeSimpleTextPtr spText = VE_NEW VeSimpleText(pcName);
				bool bTranslate = pkElement->Attribute("translate", true);
				if(bTranslate)
				{
					spText->SetText(g_pDevice->Translate(pkElement->Attribute("text", "")));
				}
				else
				{
					spText->SetText(pkElement->Attribute("text", ""));
				}
				VeFloat32 f32LineWidth = g_pLua->GetExpression(pkElement->Attribute("line_width"), 0.0f);
				VeFloat32 f32LineSpace = g_pLua->GetExpression(pkElement->Attribute("line_space"), 0.0f);
				VeSimpleText::AlignType eType = VeSimpleText::AlignTypeLua::ToEnum(pkElement->Attribute("align", "cc"), VeSimpleText::CENTER_CENTER);
				VeColor kColor = pkElement->Attribute("color", VeColor::WHITE);
				VeFloat32 f32Bias = g_pLua->GetExpression(pkElement->Attribute("bias"), 0.0f);
				VeFloat32 f32Offset = g_pLua->GetExpression(pkElement->Attribute("off"), 0.0f);
				VeColor kShadowColor = pkElement->Attribute("shadow_color", VeColor::BLACK);
				VeFloat32 f32ShadowBias = g_pLua->GetExpression(pkElement->Attribute("shadow_bais"), 0.0f);
				VeFloat32 soffx = g_pLua->GetExpression(pkElement->Attribute("soffx"), 0.0f);
				VeFloat32 soffy = g_pLua->GetExpression(pkElement->Attribute("soffy"), 0.0f);
				spText->SetLine(f32LineWidth, f32LineSpace);
				spText->SetType(eType, kColor, f32Bias, f32Offset);
				spText->SetShadowType(kShadowColor, f32ShadowBias, VeVector2D(soffx, soffy));
				spText->From(pkElement);
				spNode->AttachChild(spText);
			}
		}
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::OnEvent(const VeUIWidgetPtr& spWidget, VeUInt32 u32Event)
{
	if(spWidget == this)
	{
		const VeChar8* pcAlias = EventTypeLua::ToAlias((EventType)u32Event);
		VePair<VeString,VeInt32>* pkIter = m_kLuaEventMap.Find(pcAlias);
		if(pkIter)
		{
			if(!pkIter->m_tSecond)
			{
				pkIter->m_tSecond = g_pLua->Ref(pkIter->m_tFirst);
			}
			if(pkIter->m_tSecond)
			{
				lua_State* pkThread = VeLuaBind::MakeFuncThread(g_pLua->GetLua(), pkIter->m_tSecond);
				if(!pkThread) return;
				VeLuaBind::StackHolder kHoldMain(g_pLua->GetLua());
				VeLuaBind::StackHolder kHoldThread(pkThread);
				if(VeLuaBind::RetParam(pkThread, this) != 1) return;
				if(VeLuaBind::CallFuncThread(g_pLua->GetLua(), pkThread, 1) != 1)
				{
					VeDebugOutput("Error widget event call");
				}
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeUIWidget::SetRepainter(const RepainterPtr& spRepainter)
{
	m_spRepainter = spRepainter;
	BeginChild();
	VeUIWidget* pkIter = NextChildByType<VeUIWidget>();
	while(pkIter)
	{
		pkIter->SetRepainter(spRepainter);
		pkIter = NextChildByType<VeUIWidget>();
	}
	EndChild();
}
//--------------------------------------------------------------------------
void VeUIWidget::NotifyRepaint()
{
	if(m_spRepainter)
	{
		m_spRepainter->Notify();
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeUIWidget::GetCurUpdateRangeFrame(const VeUIWidget& kWidget)
{
	return kWidget.m_u32CurUpdateRangeFrame;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIWidget)
{
	Module() [
		Class< VeUIWidget, Base<VeSceneNode2D> >().
			Def("GetChildrenWidget", &VeUIWidget::GetChildrenWidget).
			Def("GetName", &VeUIWidget::GetName).
			Def("GetEnable", &VeUIWidget::GetEnable).
			Def("GetVisible", &VeUIWidget::GetVisible).
			Def("GetActive", &VeUIWidget::GetActive).
			Def("GetProcessInput", &VeUIWidget::GetProcessInput).
			Def("GetClipByRange", &VeUIWidget::GetClipByRange).
			Def("GetChecked", &VeUIWidget::GetChecked).
			Def("GetShow", &VeUIWidget::GetShow).
			Def("IsRoot", &VeUIWidget::IsRoot).
			Def("GetParent", &VeUIWidget::GetParent).
			Def("GetRange", &VeUIWidget::GetRange).
			Def("GetDerivedRange", &VeUIWidget::GetDerivedRange).
			Def("GetIndex", &VeUIWidget::GetIndex).
			Def("SetEnable", &VeUIWidget::SetEnable).
			Def("SetVisible", &VeUIWidget::SetVisible).
			Def("SetActive", &VeUIWidget::SetActive).
			Def("SetProcessInput", &VeUIWidget::SetProcessInput).
			Def("SetClipByRange", &VeUIWidget::SetClipByRange).
			Def("SetChecked", &VeUIWidget::SetChecked).
			Def("SetTag", &VeUIWidget::SetTag).
			Def("GetTag", &VeUIWidget::GetTag)
	];
}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeUIWidget, EventType);
	VeLuaClassEnumFuncImpl(VeUIWidget, NodeType);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeUIWidget, EventType)
{
	VeLuaClassEnumBase(VeUIWidget, EventType);

	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_MOUSE_PRESSED, "mouse_pressed");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_MOUSE_RELEASED, "mouse_released");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_MOUSE_MOVE, "mouse_move");

	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_TOUCH_BEGAN, "touch_began");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_TOUCH_MOVED, "touch_moved");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_TOUCH_ENDED, "touch_ended");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_TOUCH_CANCELLED, "touch_cancelled");

	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_RELEASE_FOCUS, "release_focus");

	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_ENABLE, "enable");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_DISABLE, "disable");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_SHOW, "show");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_HIDE, "hide");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_ACTIVE, "active");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_INACTIVE, "inactive");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_CHECK, "check");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_UNCHECK, "uncheck");

	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_CLICK, "click");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_PRESSED, "pressed");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_CHANGE_INDEX, "change_index");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_MOVE, "move");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_STOP, "stop");

	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_VALUE_CHANGE, "value_change");
	VeLuaClassEnumSlot(VeUIWidget, EventType, EVT_VALUE_CHANGED, "value_changed");
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeUIWidget, NodeType)
{
	VeLuaClassEnumBase(VeUIWidget, NodeType);
	VeLuaClassEnumSlot(VeUIWidget, NodeType, NODE_TEX, "tex");
	VeLuaClassEnumSlot(VeUIWidget, NodeType, NODE_FRAME, "frame");
	VeLuaClassEnumSlot(VeUIWidget, NodeType, NODE_BAR, "bar");
	VeLuaClassEnumSlot(VeUIWidget, NodeType, NODE_TEXT, "text");
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUILayout, VeUIWidget);
//--------------------------------------------------------------------------
VeUILayout::VeUILayout() : m_bModal(false)
{

}
//--------------------------------------------------------------------------
VeUILayout::~VeUILayout()
{

}
//--------------------------------------------------------------------------
bool VeUILayout::Process(const VeInputMessage& kMessage)
{
	if(kMessage.m_eDeviceType == VeInputMessage::DT_MOUSE)
	{
		VeUIWidget* pkHoldWidget(NULL);
		switch(kMessage.m_u32InputType)
		{
		case VeInputMessage::MIT_LBTN_PRESSED:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_MOUSE << 24) | 1;
				pkHoldWidget = PressEvent(kMessage.m_u32InputCode, u32Type,
					VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
				if(pkHoldWidget)
				{
					m_kHoldMap[u32Type] = pkHoldWidget;
				}
				UpdateActive(pkHoldWidget);
			}
			break;
		case VeInputMessage::MIT_RBTN_PRESSED:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_MOUSE << 24) | 2;
				pkHoldWidget = PressEvent(kMessage.m_u32InputCode, u32Type,
					VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
				if(pkHoldWidget)
				{
					m_kHoldMap[u32Type] = pkHoldWidget;
				}
				UpdateActive(pkHoldWidget);
			}
			break;
		case VeInputMessage::MIT_MBTN_PRESSED:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_MOUSE << 24) | 3;
				pkHoldWidget = PressEvent(kMessage.m_u32InputCode, u32Type,
					VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
				if(pkHoldWidget)
				{
					m_kHoldMap[u32Type] = pkHoldWidget;
				}
				UpdateActive(pkHoldWidget);
			}
			break;
		case VeInputMessage::MIT_LBTN_RELEASED:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_MOUSE << 24) | 1;
				VeUIWidgetPtr& spHold = m_kHoldMap[u32Type];
				if(spHold)
				{
					pkHoldWidget = ReleaseEvent(spHold, kMessage.m_u32InputCode, u32Type,
						VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
					if(spHold != pkHoldWidget)
					{
						spHold->OnCancel(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
					}
					spHold = NULL;
				}
			}
			break;
		case VeInputMessage::MIT_RBTN_RELEASED:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_MOUSE << 24) | 2;
				VeUIWidgetPtr& spHold = m_kHoldMap[u32Type];
				if(spHold)
				{
					pkHoldWidget = ReleaseEvent(spHold, kMessage.m_u32InputCode, u32Type,
						VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
					if(spHold != pkHoldWidget)
					{
						spHold->OnCancel(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
					}
					spHold = NULL;
				}
			}
			break;
		case VeInputMessage::MIT_MBTN_RELEASED:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_MOUSE << 24) | 3;
				VeUIWidgetPtr& spHold = m_kHoldMap[u32Type];
				if(spHold)
				{
					pkHoldWidget = ReleaseEvent(spHold, kMessage.m_u32InputCode, u32Type,
						VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
					if(spHold != pkHoldWidget)
					{
						spHold->OnCancel(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
					}
					spHold = NULL;
				}
			}
			break;
		case VeInputMessage::MIT_CURSOR_MOVED:
			{
				VE_ASSERT(g_pMouse);
				VeUInt32 u32Type(0);
				if(g_pMouse->GetStateFlag(VeMouse::BTN_BUTTON0)) u32Type = 1;
				else if(g_pMouse->GetStateFlag(VeMouse::BTN_BUTTON1)) u32Type = 2;
				else if(g_pMouse->GetStateFlag(VeMouse::BTN_BUTTON2)) u32Type = 3;
				if(u32Type) u32Type |= (VeInputMessage::DT_MOUSE << 24);
				VeUIWidgetPtr& spCursor = m_kCursorMap[VE_INFINITE];
				pkHoldWidget = CurMoveEvent(spCursor, kMessage.m_u32InputCode, u32Type,
					VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
				if(u32Type)
				{
					if((!pkHoldWidget) && spCursor)
					{
						spCursor->OnDragLeave(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
						spCursor = NULL;
					}
					pkHoldWidget = m_kHoldMap[u32Type];
					if(pkHoldWidget)
					{
						pkHoldWidget->OnHoldDragMove(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
					}
				}
			}
			break;
		default:
			break;
		}
		return m_bModal || (pkHoldWidget != NULL);
	}
	else if(kMessage.m_eDeviceType == VeInputMessage::DT_KEYBOARD)
	{
		VeUIWidget* pkHoldWidget(NULL);
		switch(kMessage.m_u32InputType)
		{
		case VeInputMessage::KIT_KEY_PRESSED:
			pkHoldWidget = PressEvent(kMessage.m_u32InputCode, (VeKeyboard::InputKey)kMessage.m_stMessageInfo);
			if(pkHoldWidget)
			{
				m_kKeyHoldMap[(VeUInt32)kMessage.m_stMessageInfo] = pkHoldWidget;
			}
			UpdateActive(pkHoldWidget);
			break;
		case VeInputMessage::KIT_KEY_RELEASED:
			{
				VeUIWidgetPtr& spHold = m_kKeyHoldMap[(VeUInt32)kMessage.m_stMessageInfo];
				if(spHold)
				{
					spHold->OnRelease(kMessage.m_u32InputCode, (VeKeyboard::InputKey)kMessage.m_stMessageInfo);
					spHold = NULL;
				}
			}
			break;
		default:
			break;
		}
		return m_bModal || (pkHoldWidget != NULL);
	}
	else if(kMessage.m_eDeviceType == VeInputMessage::DT_TOUCH)
	{
		VeUIWidget* pkHoldWidget(NULL);
		switch(kMessage.m_u32InputType)
		{
		case VeInputMessage::TIT_BEGAN:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_TOUCH << 24) | kMessage.m_pkTouchPointParam->id;
				pkHoldWidget = PressEvent(kMessage.m_u32InputCode, u32Type,
					VeVector2D(VeFloat32(kMessage.m_pkTouchPointParam->x), VeFloat32(kMessage.m_pkTouchPointParam->y)));
				if(pkHoldWidget)
				{
					m_kHoldMap[u32Type] = pkHoldWidget;
				}
				UpdateActive(pkHoldWidget);
			}
			break;
		case VeInputMessage::TIT_ENDED:
			{
				VeUInt32 u32Type = (VeInputMessage::DT_TOUCH << 24) | kMessage.m_pkTouchPointParam->id;
				VeUIWidgetPtr& spHold = m_kHoldMap[u32Type];
				if(spHold)
				{
					pkHoldWidget = ReleaseEvent(spHold, kMessage.m_u32InputCode, u32Type,
						VeVector2D(VeFloat32(kMessage.m_pkTouchPointParam->x), VeFloat32(kMessage.m_pkTouchPointParam->y)));
					if(spHold != pkHoldWidget)
					{
						spHold->OnCancel(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(kMessage.m_pkTouchPointParam->x), VeFloat32(kMessage.m_pkTouchPointParam->y)));
					}
					spHold = NULL;
				}
			}
			break;
		case VeInputMessage::TIT_CANCELLED:
			{
				VeVector<VeInputMessage::TouchPointParam>& kParams = *(kMessage.m_pkTouchPointParams);
				VeVector<VeInputMessage::TouchPointParam>::iterator it = kParams.Begin();
				while(it != kParams.End())
				{
					VeUInt32 u32Type = (VeInputMessage::DT_TOUCH << 24) | it->id;
					VeUIWidgetPtr& spHold = m_kHoldMap[u32Type];
					if(spHold)
					{
						pkHoldWidget = ReleaseEvent(spHold, kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(it->x), VeFloat32(it->y)));
						if(spHold != pkHoldWidget)
						{
							spHold->OnCancel(kMessage.m_u32InputCode, u32Type,
								VeVector2D(VeFloat32(it->x), VeFloat32(it->y)));
						}
						spHold = NULL;
					}
					else
					{
						pkHoldWidget = NULL;
					}
					if(pkHoldWidget)
					{
						it = kParams.Erase(it);
					}
					else
					{
						++it;
					}
				}
				pkHoldWidget = kParams.Size() ? NULL : this;
			}
			break;
		case VeInputMessage::TIT_MOVED:
			{
				VeVector<VeInputMessage::TouchPointParam>& kParams = *(kMessage.m_pkTouchPointParams);
				VeVector<VeInputMessage::TouchPointParam>::iterator it = kParams.Begin();
				while(it != kParams.End())
				{
					VeUInt32 u32Type = (VeInputMessage::DT_TOUCH << 24) | it->id;
					VeUIWidgetPtr& spCursor = m_kCursorMap[it->id];
					pkHoldWidget = CurMoveEvent(spCursor, kMessage.m_u32InputCode, u32Type,
						VeVector2D(VeFloat32(it->x), VeFloat32(it->y)));
					if((!pkHoldWidget) && spCursor)
					{
						spCursor->OnDragLeave(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(kMessage.m_kMouseCursorPos.x), VeFloat32(kMessage.m_kMouseCursorPos.y)));
						spCursor = NULL;
					}
					pkHoldWidget = m_kHoldMap[u32Type];
					if(pkHoldWidget)
					{
						pkHoldWidget->OnHoldDragMove(kMessage.m_u32InputCode, u32Type,
							VeVector2D(VeFloat32(it->x), VeFloat32(it->y)));
						it = kParams.Erase(it);
					}
					else
					{
						++it;
					}
				}
				pkHoldWidget = kParams.Size() ? NULL : this;
			}
			break;
		default:
			break;

		}
		return m_bModal || (pkHoldWidget != NULL);
	}
	else
	{
		return m_bModal;
	}
}
//--------------------------------------------------------------------------
void VeUILayout::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUILayout::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUILayout::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	m_bModal = pkElement->Attribute("modal", false);
}
//--------------------------------------------------------------------------
void VeUILayout::OnShow()
{
	VeUIWidget::OnShow();
	m_kChildren.BeginIterator();
	while(!m_kChildren.IsEnd())
	{
		VeUIWidget* pkWidget = m_kChildren.GetIterNode()->m_tContent;
		m_kChildren.Next();
		VE_ASSERT(pkWidget);
		pkWidget->OnShow();
	}
}
//--------------------------------------------------------------------------
void VeUILayout::OnHide()
{
	VeUIWidget::OnHide();
	UpdateActive(NULL);
	for(VeMap<VeUInt32,VeUIWidgetPtr>::iterator it = m_kHoldMap.Begin(); it != m_kHoldMap.End(); ++it)
	{
		if(it->m_tSecond)
		{
			it->m_tSecond->OnCancel(g_pTime->GetTimeUInt(), it->m_tFirst, VeVector2D::ZERO);
			it->m_tSecond = NULL;
		}
	}
	for(VeMap<VeUInt32,VeUIWidgetPtr>::iterator it = m_kCursorMap.Begin(); it != m_kCursorMap.End(); ++it)
	{
		it->m_tSecond = NULL;
	}
	for(VeMap<VeUInt32,VeUIWidgetPtr>::iterator it = m_kKeyHoldMap.Begin(); it != m_kKeyHoldMap.End(); ++it)
	{
		if(it->m_tSecond)
		{
			it->m_tSecond->OnCancel(g_pTime->GetTimeUInt(), VeKeyboard::InputKey(it->m_tFirst));
			it->m_tSecond = NULL;
		}
	}
	m_kHoldMap.Clear();
	m_kCursorMap.Clear();
	m_kKeyHoldMap.Clear();
	m_kChildren.BeginIterator();
	while(!m_kChildren.IsEnd())
	{
		VeUIWidget* pkWidget = m_kChildren.GetIterNode()->m_tContent;
		m_kChildren.Next();
		VE_ASSERT(pkWidget);
		pkWidget->OnHide();
	}
}
//--------------------------------------------------------------------------
void VeUILayout::UpdateActive(const VeUIWidgetPtr& spWidget)
{
	if(m_spActive != spWidget)
	{
		if(m_spActive) m_spActive->SetActive(false);
		m_spActive = spWidget;
		if(m_spActive) m_spActive->SetActive(true);
	}
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUILayout::Create()
{
	return VE_NEW VeUILayout;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUILayout)
{
	Module() [
		Class< VeUILayout, Base<VeUIWidget> >().
			Def("SetModal", &VeUILayout::SetModal).
			Def("IsModal", &VeUILayout::IsModal)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUISquare, VeUIWidget);
//--------------------------------------------------------------------------
VeUISquare::VeUISquare()
{

}
//--------------------------------------------------------------------------
VeUISquare::~VeUISquare()
{

}
//--------------------------------------------------------------------------
void VeUISquare::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUISquare::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUISquare::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	SetProcessInput(false);
	VeColor kColor = pkElement->Attribute("color", VeColor::WHITE);
	SetMulColor(kColor);
	VeFloat32 f32MinX = g_pLua->GetExpression(pkElement->Attribute("min_x"), 0.0f);
	VeFloat32 f32MinY = g_pLua->GetExpression(pkElement->Attribute("min_y"), 0.0f);
	VeFloat32 f32MaxX = g_pLua->GetExpression(pkElement->Attribute("max_x"), 0.0f);
	VeFloat32 f32MaxY = g_pLua->GetExpression(pkElement->Attribute("max_y"), 0.0f);
	m_spSquare = VE_NEW VeSquare(VeBoundingBox2D(f32MinX, f32MinY, f32MaxX, f32MaxY));
	AttachRenderable(m_spSquare);
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUISquare::Create()
{
	return VE_NEW VeUISquare;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUISquare)
{
	Module() [
		Class< VeUISquare, Base<VeUIWidget> >().
			Def("GetSquare", &VeUISquare::GetSquare)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIImage, VeUIWidget);
//--------------------------------------------------------------------------
VeUIImage::VeUIImage()
{

}
//--------------------------------------------------------------------------
VeUIImage::~VeUIImage()
{

}
//--------------------------------------------------------------------------
void VeUIImage::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIImage::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUIImage::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	SetProcessInput(false);
	const VeChar8* pcName = pkElement->GetAttribute("res");
	if(pcName)
	{
		m_spImage = VE_NEW VeSprite2D(pcName);
		VeFloat32 ax = g_pLua->GetExpression(pkElement->Attribute("ax"), 0.5f);
		VeFloat32 ay = g_pLua->GetExpression(pkElement->Attribute("ay"), 0.5f);
		VeFloat32 aox = g_pLua->GetExpression(pkElement->Attribute("aox"), 0.0f);
		VeFloat32 aoy = g_pLua->GetExpression(pkElement->Attribute("aoy"), 0.0f);
		m_spImage->SetAnchor(ax, ay, aox, aoy, pkElement->Attribute("afloor", true));
		AttachRenderable(m_spImage);
	}
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIImage::Create()
{
	return VE_NEW VeUIImage;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIImage)
{
	Module() [
		Class< VeUIImage, Base<VeUIWidget> >().
			Def("GetImage", &VeUIImage::GetImage)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIDragonBones, VeUIWidget);
//--------------------------------------------------------------------------
VeUIDragonBones::VeUIDragonBones()
{

}
//--------------------------------------------------------------------------
VeUIDragonBones::~VeUIDragonBones()
{

}
//--------------------------------------------------------------------------
void VeUIDragonBones::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIDragonBones::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUIDragonBones::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	SetProcessInput(false);
	const VeChar8* pcName = pkElement->GetAttribute("res");
	if(pcName)
	{
		m_spEntity = VE_NEW VeDragonBonesEntity(pcName);
		VeXMLElement* pkProp = pkElement->FirstChildElement("properties");
		if(pkProp)
		{
			VeXMLElement* pkTemp = pkProp->FirstChildElement("play");
			while(pkTemp)
			{
				const VeChar8* pcArm = pkTemp->GetAttribute("arm");
				const VeChar8* pcAni = pkTemp->GetAttribute("ani");
				if(pcAni)
				{
					if(pcArm) m_spEntity->Play(pcArm, pcAni, 0.0f, 0.0f);
					else m_spEntity->Play(pcAni, 0.0f, 0.0f);
				}
				pkTemp = pkTemp->NextSiblingElement("play");
			}

			pkTemp = pkProp->FirstChildElement("link");
			while(pkTemp)
			{
				const VeChar8* pcBone = pkTemp->Attribute("bone");
				const VeChar8* pcArm = pkTemp->GetAttribute("arm");
				VeUInt32 u32Arm = pcArm ? m_spEntity->GetArmatureIndex(pcArm) : 0;
				VeSceneNode2DPtr spBone = m_spEntity->GetBone(pcBone, u32Arm);
				if(spBone)
				{
					VeUIWidget::Parse(spBone, pkTemp);
				}
				pkTemp = pkTemp->NextSiblingElement("link");
			}
		}
		AttachChild(m_spEntity);
	}
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIDragonBones::Create()
{
	return VE_NEW VeUIDragonBones;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIDragonBones)
{
	Module() [
		Class< VeUIDragonBones, Base<VeUIWidget> >().
			Def("GetEntity", &VeUIDragonBones::GetEntity)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIAlertFrame, VeUIWidget);
//--------------------------------------------------------------------------
VeUIAlertFrame::VeUIAlertFrame()
{

}
//--------------------------------------------------------------------------
VeUIAlertFrame::~VeUIAlertFrame()
{

}
//--------------------------------------------------------------------------
void VeUIAlertFrame::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIAlertFrame::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUIAlertFrame::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	SetProcessInput(false);
	VeFloat32 fw = g_pLua->GetExpression(pkElement->Attribute("fw"), 0.0f);
	VeFloat32 fh = g_pLua->GetExpression(pkElement->Attribute("fh"), 0.0f);
	const VeChar8* apcSlot[VeUIFrame::POS_NUM] =
	{
		pkElement->GetAttribute("lt"),
		pkElement->GetAttribute("rt"),
		pkElement->GetAttribute("lb"),
		pkElement->GetAttribute("rb"),
		pkElement->GetAttribute("t"),
		pkElement->GetAttribute("l"),
		pkElement->GetAttribute("r"),
		pkElement->GetAttribute("b"),
		pkElement->GetAttribute("c")
	};
	m_spFrame = VE_NEW VeUIFrame;
	m_spFrame->SetFrame(apcSlot);
	m_spFrame->SetSize(fw, fh);
	AttachChild(m_spFrame);
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIAlertFrame::Create()
{
	return VE_NEW VeUIAlertFrame;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIAlertFrame)
{
	Module() [
		Class< VeUIAlertFrame, Base<VeUIWidget> >().
			Def("GetEntity", &VeUIAlertFrame::GetEntity)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIAlertBarHoriz, VeUIWidget);
//--------------------------------------------------------------------------
VeUIAlertBarHoriz::VeUIAlertBarHoriz()
{

}
//--------------------------------------------------------------------------
VeUIAlertBarHoriz::~VeUIAlertBarHoriz()
{

}
//--------------------------------------------------------------------------
void VeUIAlertBarHoriz::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIAlertBarHoriz::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUIAlertBarHoriz::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	SetProcessInput(false);
	VeFloat32 bw = g_pLua->GetExpression(pkElement->Attribute("bw"), 0.0f);
	const VeChar8* apcSlot[VeUIBarHoriz::POS_NUM] =
	{
		pkElement->GetAttribute("l"),
		pkElement->GetAttribute("r"),
		pkElement->GetAttribute("c")
	};
	m_spBar = VE_NEW VeUIBarHoriz;
	m_spBar->SetFrame(apcSlot);
	m_spBar->SetWidth(bw);
	AttachChild(m_spBar);
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIAlertBarHoriz::Create()
{
	return VE_NEW VeUIAlertBarHoriz;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIAlertBarHoriz)
{
	Module() [
		Class< VeUIAlertBarHoriz, Base<VeUIWidget> >().
			Def("GetEntity", &VeUIAlertBarHoriz::GetEntity)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUITextLabel, VeUIWidget);
//--------------------------------------------------------------------------
VeUITextLabel::VeUITextLabel()
{

}
//--------------------------------------------------------------------------
VeUITextLabel::~VeUITextLabel()
{

}
//--------------------------------------------------------------------------
void VeUITextLabel::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUITextLabel::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUITextLabel::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	SetProcessInput(false);
	const VeChar8* pcName = pkElement->GetAttribute("font");
	if(pcName)
	{
		m_spText = VE_NEW VeSimpleText(pcName);
		bool bTranslate = pkElement->Attribute("translate", true);
		if(bTranslate)
		{
			m_spText->SetText(g_pDevice->Translate(pkElement->Attribute("text", "")));
		}
		else
		{
			m_spText->SetText(pkElement->Attribute("text", ""));
		}
		VeFloat32 f32LineWidth = g_pLua->GetExpression(pkElement->Attribute("line_width"), 0.0f);
		VeFloat32 f32LineSpace = g_pLua->GetExpression(pkElement->Attribute("line_space"), 0.0f);
		VeSimpleText::AlignType eType = VeSimpleText::AlignTypeLua::ToEnum(pkElement->Attribute("align", "cc"), VeSimpleText::CENTER_CENTER);
		VeColor kColor = pkElement->Attribute("color", VeColor::WHITE);
		VeFloat32 f32Bias = g_pLua->GetExpression(pkElement->Attribute("bias"), 0.0f);
		VeFloat32 f32Offset = g_pLua->GetExpression(pkElement->Attribute("off"), 0.0f);
		VeColor kShadowColor = pkElement->Attribute("shadow_color", VeColor::BLACK);
		VeFloat32 f32ShadowBias = g_pLua->GetExpression(pkElement->Attribute("shadow_bais"), 0.0f);
		VeFloat32 soffx = g_pLua->GetExpression(pkElement->Attribute("soffx"), 0.0f);
		VeFloat32 soffy = g_pLua->GetExpression(pkElement->Attribute("soffy"), 0.0f);
		m_spText->SetLine(f32LineWidth, f32LineSpace);
		m_spText->SetType(eType, kColor, f32Bias, f32Offset);
		m_spText->SetShadowType(kShadowColor, f32ShadowBias, VeVector2D(soffx, soffy));
		AttachChild(m_spText);
	}
}
//--------------------------------------------------------------------------
void VeUITextLabel::SetText(const VeChar8* pcText)
{
	m_spText->SetText(pcText);
}
//--------------------------------------------------------------------------
void VeUITextLabel::SetTextTrans(const VeChar8* pcText)
{
	m_spText->SetText(g_pDevice->Translate(pcText));
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUITextLabel::Create()
{
	return VE_NEW VeUITextLabel;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUITextLabel)
{
	Module() [
		Class< VeUITextLabel, Base<VeUIWidget> >().
			Def("GetText", &VeUITextLabel::GetText).
			Def("SetText", &VeUITextLabel::SetText).
			Def("SetTextTrans", &VeUITextLabel::SetTextTrans)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIButton, VeUIWidget);
//--------------------------------------------------------------------------
VeUIButton::VeUIButton() : m_eDisplay(DIS_NORMAL)
{
	for(VeUInt32 i(0); i < DIS_NUM; ++i)
	{
		m_aspNode[i] = VE_NEW VeSceneNode2D;
		m_aspNode[i]->SetZOrder(-1.0f);
	}
	AttachChild(m_aspNode[DIS_NORMAL]);
	SetEatEvent(true);
}
//--------------------------------------------------------------------------
VeUIButton::~VeUIButton()
{

}
//--------------------------------------------------------------------------
void VeUIButton::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIButton::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUIButton::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	VeXMLElement* pkProp = pkElement->FirstChildElement("properties");
	if(pkProp)
	{
		VeXMLElement* pkTemp = pkProp->FirstChildElement();
		while(pkTemp)
		{
			const VeChar8* pcValue = pkTemp->Value();
			if(!VeStrcmp(pcValue, "normal"))
			{
				Parse(m_aspNode[DIS_NORMAL], pkTemp);
			}
			else if(!VeStrcmp(pcValue, "pressed"))
			{
				Parse(m_aspNode[DIS_PRESSED], pkTemp);
			}
			else if(!VeStrcmp(pcValue, "disabled"))
			{
				Parse(m_aspNode[DIS_DISABLED], pkTemp);
			}
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
	SetDisplay(GetEnable() ? DIS_NORMAL : DIS_DISABLED);
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIButton::Create()
{
	return VE_NEW VeUIButton;
}
//--------------------------------------------------------------------------
bool VeUIButton::OnPress(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	if(GetEnable())
	{
		if(((u32Type >> 24) == VeInputMessage::DT_TOUCH)
			|| (((u32Type >> 24) == VeInputMessage::DT_MOUSE) && ((u32Type & 0xf) == 1)))
		{
			SetDisplay(DIS_PRESSED);
			m_kEvent.Callback(this, EVT_PRESSED);
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
void VeUIButton::OnRelease(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	SetDisplay(DIS_NORMAL);
	m_kEvent.Callback(this, EVT_CLICK);
}
//--------------------------------------------------------------------------
void VeUIButton::OnCancel(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	SetDisplay(DIS_NORMAL);
}
//--------------------------------------------------------------------------
void VeUIButton::OnHoldDragMove(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	SetDisplay(IsIn(kPos) ? DIS_PRESSED : DIS_NORMAL);
}
//--------------------------------------------------------------------------
void VeUIButton::SetDisplay(Display eDisplay)
{
	if(eDisplay < DIS_NUM)
	{
		if(m_eDisplay != eDisplay)
		{
			m_aspNode[m_eDisplay]->DetachFromParent();
			AttachChild(m_aspNode[eDisplay]);
			m_eDisplay = eDisplay;
			NotifyRepaint();
		}
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIButton)
{
	Module() [
		Class< VeUIButton, Base<VeUIWidget> >()
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUICheckButton, VeUIButton);
//--------------------------------------------------------------------------
VeUICheckButton::VeUICheckButton()
{

}
//--------------------------------------------------------------------------
VeUICheckButton::~VeUICheckButton()
{

}
//--------------------------------------------------------------------------
void VeUICheckButton::From(VeBinaryIStream& kIn)
{
	
}
//--------------------------------------------------------------------------
void VeUICheckButton::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUICheckButton::From(VeXMLElement* pkElement)
{
	VeUIButton::From(pkElement);
	m_bEnableCancel = pkElement->Attribute("cancel", false);
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUICheckButton::Create()
{
	return VE_NEW VeUICheckButton;
}
//--------------------------------------------------------------------------
bool VeUICheckButton::OnPress(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	if(GetEnable())
	{
		if(((u32Type >> 24) == VeInputMessage::DT_TOUCH)
			|| (((u32Type >> 24) == VeInputMessage::DT_MOUSE) && ((u32Type & 0xf) == 1)))
		{
			if(!GetChecked())
			{
				SetChecked(true);
			}
			else if(m_bEnableCancel)
			{
				SetChecked(false);
			}
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
void VeUICheckButton::OnRelease(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{

}
//--------------------------------------------------------------------------
void VeUICheckButton::OnCancel(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{

}
//--------------------------------------------------------------------------
void VeUICheckButton::OnHoldDragMove(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{

}
//--------------------------------------------------------------------------
void VeUICheckButton::OnEvent(const VeUIWidgetPtr& spWidget,
	VeUInt32 u32Event)
{
	switch(u32Event)
	{
	case EVT_CHECK:
		SetDisplay(GetEnable() ? DIS_PRESSED : DIS_DISABLED);
		break;
	case EVT_UNCHECK:
		SetDisplay(GetEnable() ? DIS_NORMAL : DIS_DISABLED);
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUICheckButton)
{
	Module() [
		Class< VeUICheckButton, Base<VeUIButton> >()
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIRadioArea, VeUIWidget);
//--------------------------------------------------------------------------
VeUIRadioArea::VeUIRadioArea()
{

}
//--------------------------------------------------------------------------
VeUIRadioArea::~VeUIRadioArea()
{

}
//--------------------------------------------------------------------------
void VeUIRadioArea::UpdateChildren()
{
	VeUIWidget::UpdateChildren();
	m_kDelegateArray.Clear();
	BeginChild();
    VeUIWidget* pkIter = NextChildByType<VeUIWidget>();
	while(pkIter)
	{
		m_kDelegateArray.Increase();
		m_kDelegateArray.Back().Set(this, &VeUIRadioArea::OnEvent);
		pkIter->RegisterListener(m_kDelegateArray.Back());
        pkIter = NextChildByType<VeUIWidget>();
	}
	EndChild();
}
//--------------------------------------------------------------------------
void VeUIRadioArea::OnEvent(const VeUIWidgetPtr& spWidget, VeUInt32 u32Event)
{
	if(spWidget == this)
	{
		VeUIWidget::OnEvent(spWidget, u32Event);
	}
	else
	{
		static bool s_bSkipEvent(false);
		if(!s_bSkipEvent)
		{
			if(u32Event == EVT_CHECK)
			{
				if(m_spChecked != spWidget)
				{
					if(m_spChecked)
					{
						s_bSkipEvent = true;
						m_spChecked->SetChecked(false);
						s_bSkipEvent = false;
					}
					m_spChecked = spWidget;
					m_kEvent.Callback(this, EVT_CHANGE_INDEX);
				}
			}
			else if(u32Event == EVT_UNCHECK)
			{
				if(spWidget == m_spChecked)
				{
					m_spChecked = NULL;
					m_kEvent.Callback(this, EVT_CHANGE_INDEX);
				}
			}
		}
	}
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIRadioArea::Create()
{
	return VE_NEW VeUIRadioArea;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIRadioArea)
{
	Module() [
		Class< VeUIRadioArea, Base<VeUIWidget> >().
			Def("GetCheckedWidget", &VeUIRadioArea::GetCheckedWidget).
			Def("GetCheckedIndex", &VeUIRadioArea::GetCheckedIndex)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIPageView, VeUIWidget);
//--------------------------------------------------------------------------
VeUIPageView::VeUIPageView() : m_i32PageIndex(-1)
{

}
//--------------------------------------------------------------------------
VeUIPageView::~VeUIPageView()
{

}
//--------------------------------------------------------------------------
void VeUIPageView::SetPageIndex(VeInt32 i32Index)
{
	if(i32Index < 0 || i32Index >= VeInt32(m_kPageArray.Size()))
		i32Index = -1;
	if(m_i32PageIndex != i32Index)
	{
		if(m_i32PageIndex >= 0) m_kPageArray[m_i32PageIndex]->DetachFromParent();
		if(i32Index >= 0) AttachChild(m_kPageArray[i32Index]);
		m_i32PageIndex = i32Index;
	}
}
//--------------------------------------------------------------------------
void VeUIPageView::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUIPageView::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUIPageView::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	VeXMLElement* pkProp = pkElement->FirstChildElement("properties");
	if(pkProp)
	{
		VeXMLElement* pkTemp = pkProp->FirstChildElement();
		while(pkTemp)
		{
			m_kPageArray.PushBack(g_pUIManager->CreateWidget(pkTemp, m_pkParent));
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
	VeInt32 i32Page = pkElement->Attribute("page", -1);
	SetPageIndex(i32Page);
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIPageView::Create()
{
	return VE_NEW VeUIPageView;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIPageView)
{
	Module() [
		Class< VeUIPageView, Base<VeUIWidget> >().
			Def("SetPageIndex", &VeUIPageView::SetPageIndex).
			Def("GetPageIndex", &VeUIPageView::GetPageIndex)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUITextField, VeUIWidget);
//--------------------------------------------------------------------------
VeUITextField::VeUITextField() : m_i32MoveStep(0), m_f32Bias(0)
	, m_f32Offset(0), m_f32ShadowBias(0), m_u32CurserPoint(0)
	, m_bEdit(false)
{
	m_kDelegate.Set(this, &VeUITextField::OnInsertText);
	SetEatEvent(true);
	VeInitDelegate(VeUITextField, OnMoveEvent);
	m_spTimeEvent = VE_NEW VeTimeEvent;
	m_spTimeEvent->AddDelegate(VeDelegate(OnMoveEvent));
}
//--------------------------------------------------------------------------
VeUITextField::~VeUITextField()
{

}
//--------------------------------------------------------------------------
void VeUITextField::From(VeBinaryIStream& kIn)
{

}
//--------------------------------------------------------------------------
void VeUITextField::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeUITextField::From(VeXMLElement* pkElement)
{
	VeUIWidget::From(pkElement);
	SetClipByRange(true);
	m_spSquare = VE_NEW VeSceneNode2D;
	m_spSquare->SetZOrder(1.0f);
	m_kCursorRect = pkElement->Attribute("cursor", VeBoundingBox2D(VeVector2D(0,-16), VeVector2D(3,16)));
	m_spSquare->AttachRenderable(VE_NEW VeSquare(m_kCursorRect));
	m_kCursorColor = pkElement->Attribute("cursor_color", VeColor::WHITE);
	m_spText = VE_NEW VeSimpleText(pkElement->GetAttribute("font"));
	AttachChild(m_spText);
	m_kColor = pkElement->Attribute("color", VeColor::WHITE);
	m_kEmptyColor = pkElement->Attribute("empty_color", VeColor::WHITE);
	m_f32Bias = g_pLua->GetExpression(pkElement->Attribute("bias"), 0.0f);
	m_f32Offset = g_pLua->GetExpression(pkElement->Attribute("off"), 0.0f);
	m_kShadowColor = pkElement->Attribute("shadow_color", VeColor::BLACK);
	m_kEmptyShadowColor = pkElement->Attribute("empty_shadow_color", VeColor::BLACK);
	m_f32ShadowBias = g_pLua->GetExpression(pkElement->Attribute("shadow_bais"), 0.0f);
	m_kShadowOffset.x = g_pLua->GetExpression(pkElement->Attribute("soffx"), 0.0f);
	m_kShadowOffset.y = g_pLua->GetExpression(pkElement->Attribute("soffy"), 0.0f);
	m_u32MaxLen = pkElement->Attribute("max_len", 18);
	bool bTranslate = pkElement->Attribute("translate", true);
	if(bTranslate)
	{
		m_kEmpty = g_pDevice->Translate(pkElement->Attribute("empty_text"));
		SetText(g_pDevice->Translate(pkElement->Attribute("text")));
	}
	else
	{
		m_kEmpty = pkElement->Attribute("empty_text");
		SetText(pkElement->Attribute("text"));
	}
}
//--------------------------------------------------------------------------
bool VeUITextField::OnPress(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{
	if(GetEnable())
	{
		if(((u32Type >> 24) == VeInputMessage::DT_TOUCH)
			|| (((u32Type >> 24) == VeInputMessage::DT_MOUSE) && ((u32Type & 0xf) == 1)))
		{
			SetEdit(true);
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
void VeUITextField::OnRelease(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{

}
//--------------------------------------------------------------------------
void VeUITextField::OnCancel(VeUInt32 u32Time, VeUInt32 u32Type,
	const VeVector2D& kPos)
{

}
//--------------------------------------------------------------------------
bool VeUITextField::OnPress(VeUInt32 u32Time, VeKeyboard::InputKey eKey)
{
	switch(eKey)
	{
	case VeKeyboard::KEY_LEFT:
		if(m_u32CurserPoint)
		{
			--m_u32CurserPoint;
			UpdateText();
		}
		--m_i32MoveStep;
		if(!m_spTimeEvent->IsAttach())
		{
			g_pTime->Attach(m_spTimeEvent, 0.5f);
		}
		break;
	case VeKeyboard::KEY_RIGHT:
		if(m_u32CurserPoint < m_kContentCache.Size())
		{
			++m_u32CurserPoint;
			UpdateText();
		}
		++m_i32MoveStep;
		if(!m_spTimeEvent->IsAttach())
		{
			g_pTime->Attach(m_spTimeEvent, 0.5f);
		}
		break;
	default:
		break;
	}
	return true;
}
//--------------------------------------------------------------------------
void VeUITextField::OnRelease(VeUInt32 u32Time, VeKeyboard::InputKey eKey)
{
	switch(eKey)
	{
	case VeKeyboard::KEY_LEFT:
		++m_i32MoveStep;
		break;
	case VeKeyboard::KEY_RIGHT:
		--m_i32MoveStep;
		break;
	default:
		break;
	}
	if(!m_i32MoveStep)
	{
		m_spTimeEvent->Detach();
	}
}
//--------------------------------------------------------------------------
void VeUITextField::OnCancel(VeUInt32 u32Time, VeKeyboard::InputKey eKey)
{
	switch(eKey)
	{
	case VeKeyboard::KEY_LEFT:
		++m_i32MoveStep;
		break;
	case VeKeyboard::KEY_RIGHT:
		--m_i32MoveStep;
		break;
	default:
		break;
	}
	if(!m_i32MoveStep)
	{
		m_spTimeEvent->Detach();
	}
}
//--------------------------------------------------------------------------
VeImplTimeDelegate(VeUITextField, OnMoveEvent, spEvent)
{
	VeInt32 i32Point = (VeInt32)m_u32CurserPoint;
	i32Point += m_i32MoveStep;
	i32Point = VE_MAX(i32Point, 0);
	i32Point = VE_MIN(i32Point, VeInt32(m_kContentCache.Size()));
	m_u32CurserPoint = VeUInt32(i32Point);
	UpdateText();
	g_pTime->Attach(spEvent, 0.1f);
}
//--------------------------------------------------------------------------
void VeUITextField::UpdateState()
{
	if((!GetActive()) || (!GetEnable()) || (!GetVisible()))
	{
		SetEdit(false);
	}
}
//--------------------------------------------------------------------------
void VeUITextField::SetEdit(bool bEdit)
{
	if(m_bEdit != bEdit)
	{
		if(!bEdit)
		{
			m_u32CurserPoint = m_kContentCache.Size();
		}
		m_bEdit = bEdit;
		UpdateText();
	}
}
//--------------------------------------------------------------------------
void VeUITextField::CacheString()
{
	if(m_kContent.Length() > m_u32MaxLen)
	{
		m_kContent = VeString(m_kContent, m_u32MaxLen);
	}
	m_kContentCache.Clear();
	const VeChar8* pcTemp = m_kContent;
	while(pcTemp)
	{
		VeInt32 i32Char;
		VeInt32 i32Count = VeUTF8ToUnicode(pcTemp, i32Char);
		if(i32Count > 0 && i32Count < 4)
		{
			m_kContentCache.PushBack(VeChar16(i32Char));
		}
		else if(!i32Count)
		{
			break;
		}
		pcTemp += i32Count;
	}
	m_u32CurserPoint = VE_MIN(m_kContentCache.Size(), m_u32CurserPoint);
	UpdateText();
}
//--------------------------------------------------------------------------
void VeUITextField::RefreshString(bool bUpdate)
{
	VeVector<VeChar8> kDst;
	for(VeUInt32 i(0); i < m_kContentCache.Size(); ++i)
	{
		VeUInt32 u32LenPre = kDst.Size();
		VeTextTable::AddUnicode16(kDst, m_kContentCache[i]);
		if(kDst.Size() > m_u32MaxLen)
		{
			kDst.Resize(u32LenPre);
			m_kContentCache.Resize(i);
		}
	}
	kDst.PushBack('\0');
	m_kContent = &kDst[0];
	m_u32CurserPoint = VE_MIN(m_kContentCache.Size(), m_u32CurserPoint);
	if(bUpdate)
	{
		UpdateText();
	}
}
//--------------------------------------------------------------------------
VeFloat32 VeUITextField::GetCursorOffset()
{
	VeFloat32 f32Cursor(0);
	const VeFontPtr& spFont = m_spText->GetFont();
	if(spFont)
	{
		VE_ASSERT(m_u32CurserPoint <= m_kContentCache.Size());
		for(VeUInt32 i(0); i< m_u32CurserPoint; ++i)
		{
			f32Cursor += VeFloat32(spFont->GetWidth(m_kContentCache[i]));
			f32Cursor += m_f32Offset;
		}
	}
	return f32Cursor;
}
//--------------------------------------------------------------------------
void VeUITextField::UpdateText()
{
	if(m_bEdit)
	{
		AttachChild(m_spSquare);
		m_spSquare->StopAllActions();
		m_spSquare->SetMulColor(m_kCursorColor);
		m_spSquare->RunAction(VeRepeatForever::Create(VeSequence::Create(
			VeDelayTime::Create(0.8f),
			VeMulColorTo2D::Create(0.1f, VeColor(m_kCursorColor.r,m_kCursorColor.g,m_kCursorColor.b,0)),
			VeDelayTime::Create(0.4f),
			VeMulColorTo2D::Create(0.1f, m_kCursorColor),
			NULL)));
		VeFloat32 f32Cursor = GetCursorOffset();
		VeFloat32 f32Align = VE_MAX((f32Cursor + m_kCursorRect.m_kMax.x) - m_kRange.Width(), 0);
		m_spSquare->SetPositionX(m_kRange.m_kMin.x + GetCursorOffset() - f32Align);
		m_spText->SetPositionX(m_kRange.m_kMin.x - f32Align);
		if(m_kContent.IsEmpty())
		{
			m_spText->SetText(m_kEmpty);
			m_spText->SetType(VeSimpleText::LEFT_CENTER, m_kEmptyColor, m_f32Bias, m_f32Offset);
			m_spText->SetShadowType(m_kEmptyShadowColor, m_f32ShadowBias, m_kShadowOffset);
		}
		else
		{
			m_spText->SetText(m_kContent);
			m_spText->SetType(VeSimpleText::LEFT_CENTER, m_kColor, m_f32Bias, m_f32Offset);
			m_spText->SetShadowType(m_kShadowColor, m_f32ShadowBias, m_kShadowOffset);
		}
        g_pDevice->EnableIME(m_kDelegate);
	}
	else
	{
		m_spSquare->DetachFromParent();
		m_spText->SetPositionX(0);
		if(m_kContent.IsEmpty())
		{
			m_spText->SetText(m_kEmpty);
			m_spText->SetType(VeSimpleText::CENTER_CENTER, m_kEmptyColor, m_f32Bias, m_f32Offset);
			m_spText->SetShadowType(m_kEmptyShadowColor, m_f32ShadowBias, m_kShadowOffset);
		}
		else
		{
			m_spText->SetText(m_kContent);
			m_spText->SetType(VeSimpleText::CENTER_CENTER, m_kColor, m_f32Bias, m_f32Offset);
			m_spText->SetShadowType(m_kShadowColor, m_f32ShadowBias, m_kShadowOffset);
		}
		 g_pDevice->DisableIME();
	}
}
//--------------------------------------------------------------------------
void VeUITextField::OnInsertText(const VeChar16* pcText, VeUInt32 u32Num)
{
	for(VeUInt32 i(0); i < u32Num; ++i)
	{
		VeChar16 cChar = pcText[i];
		switch(cChar)
		{
		case L'\t':
		case L'\r':
		case L'\n':
		case L'\f':
			RefreshString(false);
			SetEdit(false);
			return;
		case L'\b':
			if(m_u32CurserPoint)
			{
				m_kContentCache.Erase(&m_kContentCache[--m_u32CurserPoint]);
			}
			break;
		default:
			{
				VE_ASSERT(m_u32CurserPoint <= m_kContentCache.Size());
				VeVector<VeChar16>::iterator itCur = m_u32CurserPoint < m_kContentCache.Size()
					? &m_kContentCache[m_u32CurserPoint] : NULL;
				m_kContentCache.Insert(itCur, cChar);
				++m_u32CurserPoint;
				VE_ASSERT(m_u32CurserPoint <= m_kContentCache.Size());
			}
			break;
		}
	}
	RefreshString();
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUITextField::Create()
{
	return VE_NEW VeUITextField;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUITextField)
{
	Module() [
		Class< VeUITextField, Base<VeUIWidget> >()
	];
}
//--------------------------------------------------------------------------
