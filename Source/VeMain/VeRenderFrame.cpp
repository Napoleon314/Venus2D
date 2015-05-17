////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderFrame.cpp
//  Version:     v1.00
//  Created:     5/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeRenderFrame.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFramePass, VeObject);
//--------------------------------------------------------------------------
VeRenderFramePass::VeRenderFramePass(Type eType)
	: m_eType(eType), m_pkNode(NULL)
{
	m_pkNode = VE_NEW VeRenderNode;
}
//--------------------------------------------------------------------------
VeRenderFramePass::~VeRenderFramePass()
{
	VE_SAFE_DELETE(m_pkNode);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameClear, VeRenderFramePass);
//--------------------------------------------------------------------------
VeRenderFrameClear::VeRenderFrameClear() : VeRenderFramePass(TYPE_CLEAR)
	, m_bClearColor(false), m_bClearDepth(false), m_bClearStencil(false)
	, m_u8Stencil(0), m_f32Depth(0.0f)
{
	m_kColorArray.PushBack(VeColor::BLACK);
}
//--------------------------------------------------------------------------
VeRenderFrameClear::~VeRenderFrameClear()
{

}
//--------------------------------------------------------------------------
void VeRenderFrameClear::NoitfyDirty()
{
	if(m_spData)
	{
		VeRenderCall* pkCall = m_spData->m_kCallList.GetHeadNode()->m_tContent;
		VE_ASSERT(pkCall->GetType() == VeRenderCall::CLEAR);
		((VeClearCall*)pkCall)->m_bClearColor = m_bClearColor;
		((VeClearCall*)pkCall)->m_bClearDepth = m_bClearDepth;
		((VeClearCall*)pkCall)->m_bClearStencil = m_bClearStencil;
		((VeClearCall*)pkCall)->m_u8Stencil = m_u8Stencil;
		((VeClearCall*)pkCall)->m_f32Depth = m_f32Depth;
		((VeClearCall*)pkCall)->m_kColorArray = m_kColorArray;
	}
	else
	{
		VeMemoryOStream kStream;
		kStream << 0;
		kStream << VeUInt32(1);
		kStream << VeRenderCall::CLEAR;
		kStream << m_bClearColor;
		kStream << m_bClearDepth;
		kStream << m_bClearStencil;
		kStream << m_u8Stencil;
		kStream << m_f32Depth;
		kStream << m_kColorArray;
		g_pRenderer->CreateRenderNodeData("", kStream, &m_spData);
		m_pkNode->SetData(m_spData);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameClear::From(VeBinaryIStream& kIn)
{
	kIn >> m_bClearColor;
	kIn >> m_bClearDepth;
	kIn >> m_bClearStencil;
	kIn >> m_u8Stencil;
	kIn >> m_f32Depth;
	kIn >> m_kColorArray;
	NoitfyDirty();
}
//--------------------------------------------------------------------------
void VeRenderFrameClear::To(VeBinaryOStream& kOut) const
{
	kOut << m_bClearColor;
	kOut << m_bClearDepth;
	kOut << m_bClearStencil;
	kOut << m_u8Stencil;
	kOut << m_f32Depth;
	kOut << m_kColorArray;
}
//--------------------------------------------------------------------------
void VeRenderFrameClear::From(VeXMLElement* pkElement)
{
	m_bClearColor = false;
	m_bClearDepth = false;
	m_bClearStencil = false;
	m_kColorArray.Clear();
	{
		const VeChar8* pcValue = pkElement->Attribute("buffer");
		for(VeUInt32 i(0); i < VeStrlen(pcValue); ++i)
		{
			switch(pcValue[i])
			{
			case 'c':
				m_bClearColor = true;
				break;
			case 'd':
				m_bClearDepth = true;
				break;
			case 's':
				m_bClearStencil = true;
				break;
			default:
				break;
			}
		}
	}
	m_u8Stencil = pkElement->Attribute("stencil", 255);
	m_f32Depth = pkElement->Attribute("depth", 1.0f);
	VeXMLElement* pkColor = pkElement->FirstChildElement("Color");
	while(pkColor)
	{
		m_kColorArray.Resize(m_kColorArray.Size() + 1);
		m_kColorArray.Back() = pkColor->Attribute("value", VeColor::BLACK);
		pkColor = pkColor->NextSiblingElement("Color");
	}
	NoitfyDirty();
}
//--------------------------------------------------------------------------
void VeRenderFrameClear::LinkToClick(VeRenderFrameClick* pkParent)
{
	m_pkNode->LinkToParent();
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameDraw, VeRenderFramePass);
//--------------------------------------------------------------------------
VeRenderFrameDraw::VeRenderFrameDraw() : VeRenderFramePass(TYPE_DRAW_2D)
	, m_u16Start(0), m_u16End(0)
{

}
//--------------------------------------------------------------------------
VeRenderFrameDraw::~VeRenderFrameDraw()
{

}
//--------------------------------------------------------------------------
void VeRenderFrameDraw::From(VeBinaryIStream& kIn)
{
	kIn >> m_u16Start;
	kIn >> m_u16End;
}
//--------------------------------------------------------------------------
void VeRenderFrameDraw::To(VeBinaryOStream& kOut) const
{
	kOut << m_u16Start;
	kOut << m_u16End;
}
//--------------------------------------------------------------------------
void VeRenderFrameDraw::From(VeXMLElement* pkElement)
{
	m_u16Start = pkElement->Attribute("start", 0);
	m_u16End = pkElement->Attribute("end", 0);
}
//--------------------------------------------------------------------------
void VeRenderFrameDraw::LinkToClick(VeRenderFrameClick* pkParent)
{
	g_pSceneManager->LinkRenderable(m_pkNode, pkParent->GetVisibilityMask(), m_u16Start, m_u16End);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameClick, VeObject);
//--------------------------------------------------------------------------
VeRenderFrameClick::VeRenderFrameClick()
	: m_u32VisibilityMask(VE_INFINITE), m_f32LodBias(0.0f)
{
	m_pkNode = VE_NEW VeRenderNode;
}
//--------------------------------------------------------------------------
VeRenderFrameClick::~VeRenderFrameClick()
{
	VE_SAFE_DELETE(m_pkNode);
}
//--------------------------------------------------------------------------
void VeRenderFrameClick::From(VeBinaryIStream& kIn)
{
	kIn >> m_kTarget;
	kIn >> m_kMaterialScheme;
	kIn >> m_u32VisibilityMask;
	kIn >> m_f32LodBias;
	m_kPassArray.Clear();
	VeUInt32 u32PassNumber;
	kIn >> u32PassNumber;
	for(VeUInt32 i(0); i < u32PassNumber; ++i)
	{
		VeRenderFramePass::Type eType;
		kIn >> eType;
		VeRenderFramePass* pkPass(NULL);
		switch(eType)
		{
		case VeRenderFramePass::TYPE_CLEAR:
			pkPass = VE_NEW VeRenderFrameClear;
			break;
		default:
			break;
		}
		VE_ASSERT(pkPass);
		kIn >> (*pkPass);
		m_kPassArray.PushBack(pkPass);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameClick::To(VeBinaryOStream& kOut) const
{
	kOut << m_kTarget;
	kOut << m_kMaterialScheme;
	kOut << m_u32VisibilityMask;
	kOut << m_f32LodBias;
	kOut << m_kPassArray.Size();
	for(VeUInt32 i(0); i < m_kPassArray.Size(); ++i)
	{
		kOut << VeUInt32(m_kPassArray[i]->GetType());
		kOut << (*m_kPassArray[i]);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameClick::From(VeXMLElement* pkElement)
{
	m_kPassArray.Clear();
	m_kTarget = pkElement->Attribute("target");
	m_kMaterialScheme = pkElement->Attribute("mat_scheme");
	m_u32VisibilityMask = pkElement->Attribute("visible", 0xffffffffu);
	m_f32LodBias  = pkElement->Attribute("lod_bias", 1.0f);
	VeXMLElement* pkPass = pkElement->FirstChildElement("Pass");
	while(pkPass)
	{
		const VeChar8* pcType = pkPass->GetAttribute("type");
		if(pcType)
		{
			VeRenderFramePassPtr spPass;
			if(VE_SUCCEEDED(VeStricmp(pcType, "clear")))
			{
				spPass = VE_NEW VeRenderFrameClear;
			}
			else if(VE_SUCCEEDED(VeStricmp(pcType, "draw")))
			{
				spPass = VE_NEW VeRenderFrameDraw;
			}
			if(spPass)
			{
				spPass->From(pkPass);
				spPass->GetNode()->SetParent(m_pkNode);
				m_kPassArray.PushBack(spPass);
			}
		}
		pkPass = pkPass->NextSiblingElement("Pass");
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameClick::Render()
{
	for(VeVector<VeRenderFramePassPtr>::iterator it = m_kPassArray.Begin();
		it != m_kPassArray.End(); ++it)
	{
		(*it)->LinkToClick(this);
		g_pRenderer->Render(m_pkNode);
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameTarget, VeObject);
//--------------------------------------------------------------------------
VeRenderFrameTarget::VeRenderFrameTarget(Type eType) : m_eType(eType)
{

}
//--------------------------------------------------------------------------
VeRenderFrameTarget::~VeRenderFrameTarget()
{

}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameTargetOutput, VeRenderFrameTarget);
//--------------------------------------------------------------------------
VeRenderFrameTargetOutput::VeRenderFrameTargetOutput()
	: VeRenderFrameTarget(TYPE_OUTPUT)
{

}
//--------------------------------------------------------------------------
VeRenderFrameTargetOutput::~VeRenderFrameTargetOutput()
{

}
//--------------------------------------------------------------------------
void VeRenderFrameTargetOutput::From(VeBinaryIStream& kIn)
{
	kIn >> m_kName;
	kIn >> m_kInput;
}
//--------------------------------------------------------------------------
void VeRenderFrameTargetOutput::To(VeBinaryOStream& kOut) const
{
	kOut << m_kName;
	kOut << m_kInput;
}
//--------------------------------------------------------------------------
void VeRenderFrameTargetOutput::From(VeXMLElement* pkElement)
{
	m_kName = pkElement->Attribute("name");
	m_kInput = pkElement->Attribute("input");
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameTargetRTT, VeRenderFrameTarget);
//--------------------------------------------------------------------------
VeRenderFrameTargetRTT::VeRenderFrameTargetRTT()
	: VeRenderFrameTarget(TYPE_RTT), m_u16Pool(POOL_GENERAL)
	, m_u16Format(VeRenderer::FMT_UNKNOWN)
{

}
//--------------------------------------------------------------------------
VeRenderFrameTargetRTT::~VeRenderFrameTargetRTT()
{

}
//--------------------------------------------------------------------------
void VeRenderFrameTargetRTT::From(VeBinaryIStream& kIn)
{
	kIn >> m_kName;
	kIn >> m_kInput;
	kIn >> m_u16Pool;
	kIn >> m_u16Format;
	kIn >> m_kWidth;
	kIn >> m_kHeight;
}
//--------------------------------------------------------------------------
void VeRenderFrameTargetRTT::To(VeBinaryOStream& kOut) const
{
	kOut << m_kName;
	kOut << m_kInput;
	kOut << m_u16Pool;
	kOut << m_u16Format;
	kOut << m_kWidth;
	kOut << m_kHeight;
}
//--------------------------------------------------------------------------
void VeRenderFrameTargetRTT::From(VeXMLElement* pkElement)
{

}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameTechnique, VeObject);
//--------------------------------------------------------------------------
VeRenderFrameTechnique::VeRenderFrameTechnique()
{

}
//--------------------------------------------------------------------------
VeRenderFrameTechnique::~VeRenderFrameTechnique()
{

}
//--------------------------------------------------------------------------
void VeRenderFrameTechnique::From(VeBinaryIStream& kIn)
{
	kIn >> m_kScheme;
	VeUInt32 u32Temp;
	kIn >> u32Temp;
	m_kTargetArray.Clear();
	m_kTargetMap.Clear();
	for(VeUInt32 i(0); i < u32Temp; ++i)
	{
		VeRenderFrameTarget::Type eType;
		kIn >> eType;
		VeRenderFrameTarget* pkTarget(NULL);
		switch(eType)
		{
		case VeRenderFrameTarget::TYPE_OUTPUT:
			pkTarget = VE_NEW VeRenderFrameTargetOutput;
			break;
		case VeRenderFrameTarget::TYPE_RTT:
			pkTarget = VE_NEW VeRenderFrameTargetRTT;
			break;
		default:
			break;
		}
		VE_ASSERT(pkTarget);
		kIn >> (*pkTarget);
		m_kTargetMap[pkTarget->GetName()] = m_kTargetArray.Size();
		m_kTargetArray.PushBack(pkTarget);
	}
	kIn >> u32Temp;
	m_kClickArray.Clear();
	for(VeUInt32 i(0); i < u32Temp; ++i)
	{
		VeRenderFrameClick* pkClick = VE_NEW VeRenderFrameClick;
		kIn >> (*pkClick);
		m_kClickArray.PushBack(pkClick);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameTechnique::To(VeBinaryOStream& kOut) const
{
	kOut << m_kScheme;
	kOut << m_kTargetArray.Size();
	for(VeUInt32 i(0); i < m_kTargetArray.Size(); ++i)
	{
		kOut << (m_kTargetArray[i]->GetType());
		kOut << (*m_kTargetArray[i]);
	}
	kOut << m_kClickArray.Size();
	for(VeUInt32 i(0); i < m_kClickArray.Size(); ++i)
	{
		kOut << (*m_kClickArray[i]);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameTechnique::From(VeXMLElement* pkElement)
{
	m_kTargetArray.Clear();
	m_kTargetMap.Clear();
	m_kClickArray.Clear();
	m_kScheme = pkElement->Attribute("scheme");
	{
		VeXMLElement* pkTarget = pkElement->FirstChildElement("Target");
		while(pkTarget)
		{
			const VeChar8* pcType = pkTarget->GetAttribute("type");
			if(pcType)
			{
				VeRenderFrameTargetPtr spTarget;
				if(VE_SUCCEEDED(VeStricmp(pcType, "output")))
				{
					spTarget = VE_NEW VeRenderFrameTargetOutput;
				}
				else if(VE_SUCCEEDED(VeStricmp(pcType, "rtt")))
				{
					spTarget = VE_NEW VeRenderFrameTargetRTT;
				}
				if(spTarget)
				{
					spTarget->From(pkTarget);
					m_kTargetMap[spTarget->GetName()] = m_kTargetArray.Size();
					m_kTargetArray.PushBack(spTarget);
				}
			}
			pkTarget = pkTarget->NextSiblingElement("Target");
		}
	}
	{
		VeXMLElement* pkClick = pkElement->FirstChildElement("Click");
		while(pkClick)
		{
			VeRenderFrameClickPtr spClick = VE_NEW VeRenderFrameClick;
			spClick->From(pkClick);
			m_kClickArray.PushBack(spClick);
			pkClick = pkClick->NextSiblingElement("Click");
		}
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrameUnit, VeObject);
//--------------------------------------------------------------------------
VeRenderFrameUnit::VeRenderFrameUnit()
{

}
//--------------------------------------------------------------------------
VeRenderFrameUnit::~VeRenderFrameUnit()
{

}
//--------------------------------------------------------------------------
void VeRenderFrameUnit::From(VeBinaryIStream& kIn)
{
	kIn >> m_kName;
	VeUInt32 u32Temp;
	kIn >> u32Temp;
	m_kTechArray.Clear();
	m_kTechSchemeMap.Clear();
	for(VeUInt32 i(0); i < u32Temp; ++i)
	{
		VeRenderFrameTechnique* pkTech = VE_NEW VeRenderFrameTechnique;
		kIn >> (*pkTech);
		m_kTechSchemeMap[pkTech->GetSchemeName()] = m_kTechArray.Size();
		m_kTechArray.PushBack(pkTech);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameUnit::To(VeBinaryOStream& kOut) const
{
	kOut << m_kName;
	kOut << m_kTechArray.Size();
	for(VeUInt32 i(0); i < m_kTechArray.Size(); ++i)
	{
		kOut << (*m_kTechArray[i]);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameUnit::From(VeXMLElement* pkElement)
{
	m_kTechArray.Clear();
	m_kTechSchemeMap.Clear();
	m_kName = pkElement->Attribute("name");
	VeXMLElement* pkTech = pkElement->FirstChildElement("Technique");
	while(pkTech)
	{
		VeRenderFrameTechniquePtr spTech = VE_NEW VeRenderFrameTechnique;
		spTech->From(pkTech);
		m_kTechSchemeMap[spTech->GetSchemeName()] = m_kTechArray.Size();
		m_kTechArray.PushBack(spTech);
		pkTech = pkTech->NextSiblingElement("Technique");
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderFrame, VeResource);
//--------------------------------------------------------------------------
VeRenderFrame::VeRenderFrame(
	const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(VeResource::RENDER_FRAME, pcName, pcGroup)
{

}
//--------------------------------------------------------------------------
VeRenderFrame::~VeRenderFrame()
{

}
//--------------------------------------------------------------------------
VeResource::State VeRenderFrame::LoadImpl(
	const VeMemoryIStreamPtr& spStream)
{
	*spStream >> m_kDocument;
	UpdateFrameUnit();
	return VeResource::LOADED;
}
//--------------------------------------------------------------------------
void VeRenderFrame::UnloadImpl()
{

}
//--------------------------------------------------------------------------
VeResource* VeRenderFrame::CreateResource(
	const VeChar8* pcName, const VeChar8* pcGroup)
{
	return VE_NEW VeRenderFrame(pcName, pcGroup);
}
//--------------------------------------------------------------------------
void VeRenderFrame::UpdateFrameUnit()
{
	VeVector<VeRenderFrameUnitPtr> kUnitArray;
	VeXMLElement* pkPlatform = m_kDocument.RootElement()->FirstChildElement("Platform");
	while(pkPlatform)
	{
		const VeChar8* pcValue = pkPlatform->GetAttribute("value");
		VeChar8 acBuffer[256];
		VeStrToLower(acBuffer, 256, pcValue);
		VeChar8* pcContent;
		VeChar8* pcTemp = VeStrtok(acBuffer, "|", &pcContent);
		VeUInt32 u32Platform(0);
		while(pcTemp)
		{
			VeDevice::Type eType = VeDevice::TypeLua::ToEnum(pcTemp, VeDevice::TYPE_NONE);
			if(eType < VeDevice::TYPE_NONE)
			{
				u32Platform |= VE_MASK(eType);
			}
			else if(eType == VeDevice::TYPE_ALL)
			{
				u32Platform |= VE_INFINITE;
			}
			pcTemp = VeStrtok(NULL, "|", &pcContent);
		}
		if(VE_MASK_HAS_ANY(u32Platform, VE_PLATFORM_MASK))
		{
			VeXMLElement* pkUnit = pkPlatform->FirstChildElement("Unit");
			while(pkUnit)
			{
				VeRenderFrameUnitPtr spUnit = VE_NEW VeRenderFrameUnit;
				spUnit->From(pkUnit);
				kUnitArray.PushBack(spUnit);
				pkUnit = pkUnit->NextSiblingElement("Unit");
			}
		}
		pkPlatform = pkPlatform->NextSiblingElement("Platform");
	}
	g_pRenderFrameManager->UpdateFrameUnit(kUnitArray);
}
//--------------------------------------------------------------------------
VeRenderFrameManager::VeRenderFrameManager() : m_u32FrameCount(1)
{
	g_pResourceManager->SetResourceCreateFunction(VeResource::RENDER_FRAME,
		VeRenderFrame::CreateResource);
}
//--------------------------------------------------------------------------
VeRenderFrameManager::~VeRenderFrameManager()
{

}
//--------------------------------------------------------------------------
void VeRenderFrameManager::AddPreRenderTask(VeRefNode<RenderTask*>& kNode)
{
	m_kPreRenderTaskList.AttachBack(kNode);
}
//--------------------------------------------------------------------------
void VeRenderFrameManager::OnScreenSizeChanged()
{
	VeFloat32 f32Width = g_pRenderer->GetWidthF();
	VeFloat32 f32Height = g_pRenderer->GetHeightF();
	if(m_spScreenTarget)
	{
		VeRenderTick* pkViewport = m_spScreenTarget->m_kTickList.GetHeadNode()->m_tContent;
		VE_ASSERT(pkViewport->GetType() == VeRenderTick::RS_VIEWPORT);
		((VeRSViewportTick*)pkViewport)->m_kViewport.z = f32Width;
		((VeRSViewportTick*)pkViewport)->m_kViewport.w = f32Height;
	}
	else
	{
		VeMemoryOStream kStream;
		kStream << 2;
		kStream << VeRenderTick::RS_VIEWPORT;
		kStream << VeUInt32(0);
		kStream << VeVector4D(0,0,f32Width, f32Height);
		kStream << VeRenderTick::OM_RENDER_TARGET_VIEW;
		VeFixedString kName = "back_buffer";
		kStream.AppendStringAligned4(kName, kName.GetLength());
		kStream << VeUInt32(0);
		kStream << VeUInt32(0);
		g_pRenderer->CreateRenderNodeData("", kStream, &m_spScreenTarget);
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameManager::Update(const VeChar8* pcScheme,
	VeVector<const VeChar8*> kUnitNameArray)
{
	m_kCurrentFrame.Clear();
	for(VeVector<const VeChar8*>::iterator it = kUnitNameArray.Begin();
		it != kUnitNameArray.End(); ++it)
	{
		VeUInt32* pu32Iter = m_kPartNameMap.Find(*it);
		if(pu32Iter)
		{
			VeRenderFrameUnitPtr spUnit = m_kPartArray[*pu32Iter];
			VE_ASSERT(spUnit);
			VeUInt32* pu32TechIter = spUnit->m_kTechSchemeMap.Find(pcScheme);
			if(pu32TechIter)
			{
				m_kCurrentFrame.PushBack(spUnit->m_kTechArray[*pu32TechIter]);
			}
		}
	}
	UpdateTargets();
	UpdateNode();
}
//--------------------------------------------------------------------------
void VeRenderFrameManager::Render()
{
	m_kPreRenderTaskList.BeginIterator();
	while(!m_kPreRenderTaskList.IsEnd())
	{
		RenderTask* pkRenderTask = m_kPreRenderTaskList.GetIterNode()->m_tContent;
		m_kPreRenderTaskList.Next();
		pkRenderTask->Render();
	}
	for(VeVector<VeRenderFrameTechniquePtr>::iterator it = m_kCurrentFrame.Begin();
		it != m_kCurrentFrame.End(); ++it)
	{
		VeRenderFrameTechnique& kTech = **it;
		for(VeVector<VeRenderFrameClickPtr>::iterator itClick = kTech.m_kClickArray.Begin();
			itClick != kTech.m_kClickArray.End(); ++itClick)
		{
			(*itClick)->Render();
		}
	}
	++m_u32FrameCount;
}
//--------------------------------------------------------------------------
void VeRenderFrameManager::UpdateFrameUnit(
	const VeVector<VeRenderFrameUnitPtr>& kVector)
{
	for(VeVector<VeRenderFrameUnitPtr>::const_iterator it
		= kVector.Begin(); it != kVector.End(); ++it)
	{
		VE_ASSERT(*it);
		VeUInt32* pu32Iter = m_kPartNameMap.Find((*it)->GetName());
		if(pu32Iter)
		{
			m_kPartArray[*pu32Iter] = *it;
		}
		else
		{
			m_kPartNameMap[(*it)->GetName()] = m_kPartArray.Size();
			m_kPartArray.PushBack(*it);
		}
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameManager::UpdateTargets()
{
	VE_ASSERT(m_spScreenTarget);
	VeRenderFrameTechniquePtr spTech = m_kCurrentFrame.Back();
	for(VeVector<VeRenderFrameTargetPtr>::iterator it = spTech->m_kTargetArray.Begin();
		it != spTech->m_kTargetArray.End(); ++it)
	{
		if((*it)->GetType() == VeRenderFrameTarget::TYPE_OUTPUT)
		{
			(*it)->m_spData = m_spScreenTarget;
		}
	}
}
//--------------------------------------------------------------------------
void VeRenderFrameManager::UpdateNode()
{
	for(VeVector<VeRenderFrameTechniquePtr>::iterator it = m_kCurrentFrame.Begin();
		it != m_kCurrentFrame.End(); ++it)
	{
		VeRenderFrameTechnique& kTech = **it;
		for(VeVector<VeRenderFrameClickPtr>::iterator itClick = kTech.m_kClickArray.Begin();
			itClick != kTech.m_kClickArray.End(); ++itClick)
		{
			VeRenderFrameClick& kClick = **itClick;
			VeUInt32* ppu32ItTarget = kTech.m_kTargetMap.Find(kClick.m_kTarget);
			VE_ASSERT(ppu32ItTarget);
			kClick.m_pkNode->SetData(kTech.m_kTargetArray[*ppu32ItTarget]->m_spData);
			for(VeVector<VeRenderFramePassPtr>::iterator itPass = kClick.m_kPassArray.Begin();
				itPass != kClick.m_kPassArray.End(); ++itPass)
			{
				(*itPass)->GetNode()->SetParent(kClick.m_pkNode);
			}
		}
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeRenderFrameManager)
{
	Module() [
		Class<VeRenderFrameManager>() [
			DefSingletonFunc("Update", VeRenderFrameManager::ms_pSingleton, &VeRenderFrameManager::Update)
		]
	];
}
//--------------------------------------------------------------------------
