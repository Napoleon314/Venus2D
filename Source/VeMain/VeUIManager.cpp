////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIManager.cpp
//  Version:     v1.00
//  Created:     6/2/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeUIManager.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeUIScene, VeResource);
//--------------------------------------------------------------------------
VeUIScene::VeUIScene(const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(UI_SCENE, pcName, pcGroup)
{

}
//--------------------------------------------------------------------------
VeUIScene::~VeUIScene()
{
	Unload();
}
//--------------------------------------------------------------------------
VeResource::State VeUIScene::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	VeXMLElement* pkTemp = m_kDoc.RootElement()->FirstChildElement("res");
	while(pkTemp)
	{
		Type eType = VeResource::StrToType(pkTemp->Attribute("type"), TYPE_NUM);
		if(eType < TYPE_NUM)
		{
			m_kResArray.Increase();
			m_kResArray.Back() = VeLoadResource(eType, pkTemp->Attribute("name"), m_spGroup->GetName(), m_eState == LOADING);
			Wait(m_kResArray.Back());
		}
		pkTemp = pkTemp->NextSiblingElement("res");
	}
	return LOADED;
}
//--------------------------------------------------------------------------
void VeUIScene::UnloadImpl()
{
	m_kResArray.Clear();
}
//--------------------------------------------------------------------------
bool VeUIScene::HasProcess()
{
	return true;
}
//--------------------------------------------------------------------------
void VeUIScene::LoadProcess(const VeMemoryIStreamPtr& spStream)
{
	(*spStream) >> m_kDoc;
}
//--------------------------------------------------------------------------
VeResource::State VeUIScene::AllWaitResLoaded()
{
	g_pUIManager->AddScene(this);
	return LOADED;
}
//--------------------------------------------------------------------------
VeResource* VeUIScene::CreateResource(
	const VeChar8* pcName, const VeChar8* pcGroup)
{
	return VE_NEW VeUIScene(pcName, pcGroup);
}
//--------------------------------------------------------------------------
VeUIManager::VeUIManager()
{
	VeInitDelegate(VeUIManager, InputCallback);
}
//--------------------------------------------------------------------------
VeUIManager::~VeUIManager()
{
	m_kWidgetFactory.Clear();
	m_kWidgetMap.Clear();
	for(VeUInt32 i(0); i < m_kWidgetArray.Size(); ++i)
	{
		m_kWidgetArray[i]->DetachFromParent();
	}
	m_kWidgetArray.Clear();
}
//--------------------------------------------------------------------------
void VeUIManager::Init()
{
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::UI_SCENE, VeUIScene::CreateResource);
	g_pInputManager->RegisterListener(VeDelegate(InputCallback));

	RegisterCreate<VeUIWidget>();
	RegisterCreate<VeUILayout>();
	RegisterCreate<VeUISquare>();
	RegisterCreate<VeUIImage>();
	RegisterCreate<VeUIDragonBones>();
	RegisterCreate<VeUIAlertFrame>();
	RegisterCreate<VeUIAlertBarHoriz>();
	RegisterCreate<VeUITextLabel>();
	RegisterCreate<VeUIButton>();
	RegisterCreate<VeUICheckButton>();
	RegisterCreate<VeUIRadioArea>();
	RegisterCreate<VeUIPageView>();
	RegisterCreate<VeUITextField>();
	RegisterCreate<VeUIScrollView>();
	RegisterCreate<VeUICachedPanel>();
}
//--------------------------------------------------------------------------
void VeUIManager::Term()
{
	g_pInputManager->UnregisterListener(VeDelegate(InputCallback));
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::UI_SCENE, NULL);
	PopAllLayouts();
	SetMainLayout((VeUILayout*)NULL);
}
//--------------------------------------------------------------------------
void VeUIManager::SetMainLayout(const VeChar8* pcName)
{
	SetMainLayout(VeDynamicCast(VeUILayout, FindWidget(pcName)));
}
//--------------------------------------------------------------------------
void VeUIManager::SetMainLayout(VeUILayout* pkLayout)
{
	if(pkLayout && pkLayout->GetParent()) return;
	if(pkLayout != m_spMainLayout)
	{
		if(m_spMainLayout)
		{
			if(m_spActive == m_spMainLayout)
			{
				m_spActive = NULL;
			}
			m_spMainLayout->OnHide();
			m_spMainLayout->DetachFromParent();
		}
		m_spMainLayout = pkLayout;
		if(m_spMainLayout)
		{
			g_pSceneManager->GetRootNode2D()->AttachChild(m_spMainLayout);
			m_spMainLayout->OnShow();
		}
	}
}
//--------------------------------------------------------------------------
void VeUIManager::PushLayout(const VeChar8* pcName, VeFloat32 f32ZOrder)
{
	PushLayout(VeDynamicCast(VeUILayout, FindWidget(pcName)), f32ZOrder);
}
//--------------------------------------------------------------------------
void VeUIManager::PushLayout(VeUILayout* pkLayout, VeFloat32 f32ZOrder)
{
	if(pkLayout && (!pkLayout->VeSceneNode::GetParent()))
	{
		pkLayout->SetZOrder(f32ZOrder);
		g_pSceneManager->GetRootNode2D()->AttachChild(pkLayout);
		pkLayout->OnShow();
	}
}
//--------------------------------------------------------------------------
void VeUIManager::PopLayout()
{
	g_pSceneManager->GetRootNode2D()->BeginChildR();
	VeUILayout* pkIter = g_pSceneManager->GetRootNode2D()->NextChildByTypeR<VeUILayout>();
	while(pkIter)
	{
		VeUILayout* pkLayout = pkIter != m_spMainLayout ? pkIter : NULL;
		pkIter = g_pSceneManager->GetRootNode2D()->NextChildByTypeR<VeUILayout>();
		if(pkLayout)
		{
			if(m_spActive == pkLayout)
			{
				m_spActive = NULL;
			}
			pkLayout->OnHide();
			pkLayout->DetachFromParent();
			break;
		}
	}
	g_pSceneManager->GetRootNode2D()->EndChild();
}
//--------------------------------------------------------------------------
void VeUIManager::PopLayout(VeFloat32 f32ZOrder)
{
	VeRefList<VeSceneNode*>* pkList(NULL);
	if(f32ZOrder)
	{
		VeMap<VeFloat32, VeUInt32>::iterator it = g_pSceneManager->GetRootNode2D()->m_kZOrderMap.Find(f32ZOrder);
		if(it != g_pSceneManager->GetRootNode2D()->m_kZOrderMap.End())
		{
			pkList = g_pSceneManager->GetRootNode2D()->m_kZOrderChildren[it->m_tSecond];
		}
	}
	else
	{
		pkList = &(g_pSceneManager->GetRootNode2D()->m_kChildren);
	}
	if(pkList)
	{
		pkList->BeginIteratorFromLast();
		while(!pkList->IsEnd())
		{
			VeUILayout* pkLayout = VeDynamicCast(VeUILayout, pkList->GetIterNode()->m_tContent);
			pkList->Pre();
			if(pkLayout && pkLayout!= m_spMainLayout)
			{
				if(m_spActive == pkLayout)
				{
					m_spActive = NULL;
				}
				pkLayout->OnHide();
				pkLayout->DetachFromParent();
				break;
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeUIManager::PopAllLayouts()
{
	g_pSceneManager->GetRootNode2D()->BeginChildR();
	VeUILayout* pkIter = g_pSceneManager->GetRootNode2D()->NextChildByTypeR<VeUILayout>();
	while(pkIter)
	{
		VeUILayout* pkLayout = pkIter != m_spMainLayout ? pkIter : NULL;
		pkIter = g_pSceneManager->GetRootNode2D()->NextChildByTypeR<VeUILayout>();
		if(pkLayout)
		{
			if(m_spActive == pkLayout)
			{
				m_spActive = NULL;
			}
			pkLayout->OnHide();
			pkLayout->DetachFromParent();
		}
	}
	g_pSceneManager->GetRootNode2D()->EndChild();
}
//--------------------------------------------------------------------------
void VeUIManager::PopAllLayouts(VeFloat32 f32ZOrder)
{
	VeRefList<VeSceneNode*>* pkList(NULL);
	if(f32ZOrder)
	{
		VeMap<VeFloat32, VeUInt32>::iterator it = g_pSceneManager->GetRootNode2D()->m_kZOrderMap.Find(f32ZOrder);
		if(it != g_pSceneManager->GetRootNode2D()->m_kZOrderMap.End())
		{
			pkList = g_pSceneManager->GetRootNode2D()->m_kZOrderChildren[it->m_tSecond];
		}
	}
	else
	{
		pkList = &(g_pSceneManager->GetRootNode2D()->m_kChildren);
	}
	if(pkList)
	{
		pkList->BeginIteratorFromLast();
		while(!pkList->IsEnd())
		{
			VeUILayout* pkLayout = VeDynamicCast(VeUILayout, pkList->GetIterNode()->m_tContent);
			pkList->Pre();
			if(pkLayout && pkLayout!= m_spMainLayout)
			{
				if(m_spActive == pkLayout)
				{
					m_spActive = NULL;
				}
				pkLayout->OnHide();
				pkLayout->DetachFromParent();
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeUIManager::AddWidget(const VeUIWidgetPtr& spWidget)
{
	VE_ASSERT(spWidget);
	if(*(spWidget->GetName()) != 0)
	{
		VE_ASSERT(!m_kWidgetMap.Find(spWidget->GetFullName()));
		m_kWidgetMap[spWidget->GetFullName()] = m_kWidgetArray.Size();
		m_kWidgetArray.Increase();
		m_kWidgetArray.Back() = spWidget;
	}
}
//--------------------------------------------------------------------------
void VeUIManager::DelWidget(const VeChar8* pcName)
{
	VE_ASSERT(pcName);
	VeUInt32* pu32Iter = m_kWidgetMap.Find(pcName);
	if(pu32Iter)
	{
		VE_ASSERT((*pu32Iter) < m_kWidgetArray.Size());
		{
			VE_ASSERT(m_kWidgetArray[*pu32Iter]);
			VeUIWidget& kWidget = *m_kWidgetArray[*pu32Iter];
			VeUILayout* pkLayout = VeDynamicCast(VeUILayout, &kWidget);
			if(pkLayout)
			{
				if(pkLayout->VeSceneNode::GetParent())
				{
					if(pkLayout == m_spMainLayout)
					{
						m_spMainLayout = NULL;
					}
					if(pkLayout == m_spActive)
					{
						m_spActive = NULL;
					}
					pkLayout->OnHide();
					pkLayout->DetachFromParent();
				}
			}
			DelName(kWidget);
		}		
		if((*pu32Iter) < (m_kWidgetArray.Size() - 1))
		{
			m_kWidgetMap[m_kWidgetArray.Back()->GetFullName()] = *pu32Iter;
			m_kWidgetArray[*pu32Iter] = m_kWidgetArray.Back();
		}
		m_kWidgetMap.Remove(pcName);
		m_kWidgetArray.PopBack();
	}
}
//--------------------------------------------------------------------------
void VeUIManager::DelName(VeUIWidget& kWidget)
{
	kWidget.BeginChild();
	VeUIWidget* pkIter = kWidget.NextChildByType<VeUIWidget>();
	while(pkIter)
	{
		VeUIWidget& kCur = *pkIter;
		pkIter = kWidget.NextChildByType<VeUIWidget>();
		if(kCur.m_kName == "")
		{
			DelName(kCur);
		}
		else
		{
			DelWidget(kCur.GetFullName());
		}
	}
	kWidget.EndChild();
}
//--------------------------------------------------------------------------
VeUIWidget* VeUIManager::FindWidget(const VeChar8* pcName)
{
	VE_ASSERT(pcName);
	VeUInt32* pu32Iter = m_kWidgetMap.Find(pcName);
	return pu32Iter ? m_kWidgetArray[*pu32Iter] : NULL;
}
//--------------------------------------------------------------------------
void VeUIManager::AddScene(const VeUIScenePtr& spScene)
{
	VE_ASSERT(spScene);
	const VeChar8* pcName = spScene->GetName();
	VE_ASSERT(!m_kUISceneMap.Find(pcName));
	m_kUISceneMap[pcName] = spScene;
	Load(spScene->m_kDoc.RootElement());
}
//--------------------------------------------------------------------------
void VeUIManager::DelScene(const VeChar8* pcName)
{
	VeUIScenePtr* pspIter = m_kUISceneMap.Find(pcName);
	VE_ASSERT(pspIter);
	Unload((*pspIter)->m_kDoc.RootElement());
	m_kUISceneMap.Remove(pcName);
	(*pspIter)->Unload();
}
//--------------------------------------------------------------------------
void VeUIManager::Load(VeXMLElement* pkUIScene)
{
	VE_ASSERT(pkUIScene);
	VeXMLElement* pkTemplate = pkUIScene->FirstChildElement("template");
	if(pkTemplate) pkTemplate = pkTemplate->FirstChildElement();
	while(pkTemplate)
	{
		LoadTemplate(pkTemplate);
		pkTemplate = pkTemplate->NextSiblingElement();
	}
	VeXMLElement* pkUI = pkUIScene->FirstChildElement("ui");
	if(pkUI)
	{
		VeXMLElement* pkTemp = pkUI->FirstChildElement();
		while(pkTemp)
		{
			CreateWidget(pkTemp);
			pkTemp = pkTemp->NextSiblingElement();
		}
	}	
}
//--------------------------------------------------------------------------
void VeUIManager::Unload(VeXMLElement* pkUIScene)
{
	VE_ASSERT(pkUIScene);
	VeXMLElement* pkTemplate = pkUIScene->FirstChildElement("template");
	if(pkTemplate) pkTemplate = pkTemplate->FirstChildElement();
	while(pkTemplate)
	{
		UnloadTemplate(pkTemplate);
		pkTemplate = pkTemplate->NextSiblingElement();
	}
	VeXMLElement* pkUI = pkUIScene->FirstChildElement("ui");
	if(pkUI)
	{
		VeXMLElement* pkTemp = pkUI->FirstChildElement();
		while(pkTemp)
		{
			DelWidget(pkTemp->Attribute("name"));
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
}
//--------------------------------------------------------------------------
void VeUIManager::LoadTemplate(VeXMLElement* pkTemplate)
{
	const VeChar8* pcName = pkTemplate->GetAttribute("name");
	VE_ASSERT(pcName && (!m_kTemplateMap.Find(pcName)));
	m_kTemplateMap[pcName] = VE_NEW Template(VeDynamicCast(VeXMLElement, pkTemplate->Clone()));
}
//--------------------------------------------------------------------------
void VeUIManager::UnloadTemplate(VeXMLElement* pkTemplate)
{
	const VeChar8* pcName = pkTemplate->GetAttribute("name");
	VE_ASSERT(pcName);
	m_kTemplateMap.Remove(pcName);
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIManager::CreateWidget(VeXMLElement* pkWidget,
	VeUILayout* pkLayout)
{
	VeUIWidgetPtr spRes;
	const VeChar8* pcValue = pkWidget->Value();
	if(!VeStrcmp(pcValue, "template"))
	{
		spRes = CreateTemplate(pkWidget, pkLayout);
	}
	else
	{
		CreateFunc* ppfuncCreate = m_kWidgetFactory.Find(pcValue);
		if(ppfuncCreate)
		{
			spRes = (*ppfuncCreate)();
		}
		else
		{
			spRes = VE_NEW VeUIWidget();
		}
		if(pkLayout)
		{
			VE_ASSERT(!VeIsKindOf(VeUILayout, spRes));
			spRes->m_pkParent = pkLayout;
			pkLayout->m_kChildren.AttachBack(spRes->m_kNode);
		}
		else
		{
			pkLayout = VeDynamicCast(VeUILayout, spRes);
		}
		spRes->From(pkWidget);
		AddWidget(spRes);
		VeXMLElement* pkTemp = pkWidget->FirstChildElement();
		while(pkTemp)
		{
			if(pkTemp->ValueToStr() != "properties" && pkTemp->ValueToStr() != "events" && pkTemp->ValueToStr() != "overrides")
				spRes->AttachChild(CreateWidget(pkTemp, pkLayout));
			pkTemp = pkTemp->NextSiblingElement();
		}
		spRes->UpdateChildren();
	}
	return spRes;
}
//--------------------------------------------------------------------------
void InitTemplate(VeXMLElement* pkTemplate,
	VeStringMap<VeXMLElement*>& kMap)
{
	const VeChar8* pcName = pkTemplate->GetAttribute("name");
	if(pcName)
	{
		kMap[pcName] = pkTemplate;
		pkTemplate->RemoveAttribute("name");
	}
	VeXMLElement* pkTemp = pkTemplate->FirstChildElement();
	while(pkTemp)
	{
		InitTemplate(pkTemp, kMap);
		pkTemp = pkTemp->NextSiblingElement();
	}
}
//--------------------------------------------------------------------------
void Override(VeXMLElement* pkDst, VeXMLElement* pkSrc, bool bValue = true)
{
	if(bValue) pkDst->SetValue(pkSrc->Value());
	VeXMLAttribute* pkAttr = pkSrc->FirstAttribute();
	while(pkAttr)
	{
		if(VeStrcmp(pkAttr->Name(), "parent") != 0)
		{
			pkDst->SetAttribute(pkAttr->Name(), pkAttr->Value());
		}
		pkAttr = pkAttr->Next();
	}
	VeXMLElement* pkProperties = pkSrc->FirstChildElement("properties");
	if(pkProperties)
	{
		pkDst->RemoveChild(pkDst->FirstChildElement("properties"));
		pkDst->InsertEndChild(*pkProperties);
	}
	VeXMLElement* pkEvents = pkSrc->FirstChildElement("events");
	if(pkEvents)
	{
		pkDst->RemoveChild(pkDst->FirstChildElement("events"));
		pkDst->InsertEndChild(*pkEvents);
	}
	VeXMLElement* pkOverrides = pkSrc->FirstChildElement("overrides");
	if(pkOverrides)
	{
		pkDst->RemoveChild(pkDst->FirstChildElement("overrides"));
		pkDst->InsertEndChild(*pkOverrides);
	}
}
//--------------------------------------------------------------------------
VeUIWidgetPtr VeUIManager::CreateTemplate(VeXMLElement* pkWidget,
	VeUILayout* pkLayout)
{
	TemplatePtr* pspIter = m_kTemplateMap.Find(pkWidget->Attribute("parent"));
	VE_ASSERT(pspIter);
	VeXMLElement* pkTemplate = VeDynamicCast(VeXMLElement, (*pspIter)->m_pkElement->Clone());
	VE_ASSERT(pkTemplate);
	VeStringMap<VeXMLElement*> kMap;
	InitTemplate(pkTemplate, kMap);
	Override(pkTemplate, pkWidget, false);
	VeXMLElement* pkTemp = pkWidget->FirstChildElement("overrides");
	if(pkTemp) pkTemp = pkTemp->FirstChildElement();
	while(pkTemp)
	{
		VeXMLElement** ppkIter = kMap.Find(pkTemp->Value());
		Override(ppkIter ? (*ppkIter) : pkTemplate, pkTemp);
		pkTemp = pkTemp->NextSiblingElement();
	}
	VeUIWidgetPtr spRes = CreateWidget(pkTemplate, pkLayout);
	pkTemp = pkWidget->FirstChildElement();
	while(pkTemp)
	{
		if(pkTemp->ValueToStr() != "properties" && pkTemp->ValueToStr() != "events" && pkTemp->ValueToStr() != "overrides")
			spRes->AttachChild(CreateWidget(pkTemp, pkLayout));
		pkTemp = pkTemp->NextSiblingElement();
	}
	spRes->UpdateChildren();
	VE_DELETE(pkTemplate);
	return spRes;
}
//--------------------------------------------------------------------------
VeImplInputDelegate(VeUIManager, InputCallback, kMessage)
{
	bool bHook(false);
	g_pSceneManager->GetRootNode2D()->BeginChildR();
	VeUILayout* pkIter = g_pSceneManager->GetRootNode2D()->NextChildByTypeR<VeUILayout>();
	while(pkIter)
	{
		if(pkIter->Process(kMessage))
		{
			if(pkIter != m_spActive)
			{
				if(m_spActive) m_spActive->UpdateActive(NULL);
				m_spActive = pkIter;
			}
			bHook = true;
			break;
		}
		pkIter = g_pSceneManager->GetRootNode2D()->NextChildByTypeR<VeUILayout>();
	}
	g_pSceneManager->GetRootNode2D()->EndChild();
	if(bHook)
	{
		g_pInputManager->HookCurrentMessage();
	}
	else if(kMessage.m_eDeviceType == VeInputMessage::DT_MOUSE
		&& kMessage.m_u32InputType == VeInputMessage::MIT_LBTN_PRESSED)
	{
		if(m_spActive) m_spActive->UpdateActive(NULL);
		m_spActive = NULL;
	}
	else if(kMessage.m_eDeviceType == VeInputMessage::DT_KEYBOARD
		&& kMessage.m_u32InputType == VeInputMessage::KIT_KEY_PRESSED)
	{
		if(m_spActive) m_spActive->UpdateActive(NULL);
		m_spActive = NULL;
	}
	else if(kMessage.m_eDeviceType == VeInputMessage::DT_TOUCH
		&& kMessage.m_u32InputType == VeInputMessage::TIT_BEGAN)
	{
		if(m_spActive) m_spActive->UpdateActive(NULL);
		m_spActive = NULL;
	}
}
//--------------------------------------------------------------------------
void VeUIManager::RegisterCreateFunc(
	const VeChar8* pcName, CreateFunc pfuncCreate)
{
	VE_ASSERT(pcName && pfuncCreate);
	VeChar8 acBuffer[64];
	{
		const VeChar8* pcTemp = VeStrstr(pcName, "VeUI");
		pcName = pcTemp ? pcTemp + 4 : pcName;
	}
	VeUInt32 i(0);
	while(*pcName)
	{
		if(*pcName >= 'A' && *pcName <= 'Z')
		{
			if(i)
			{
				acBuffer[i++] = '_';
			}
			acBuffer[i++] = *pcName + 0x20;
		}
		else
		{
			acBuffer[i++] = *pcName;
		}
		++pcName;
	}
	acBuffer[i] = 0;
	m_kWidgetFactory[acBuffer] = pfuncCreate;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIManager)
{
	Module() [
		Class<VeUIManager>() [
			DefSingletonFunc("SetMainLayout", VeUIManager::ms_pSingleton, (void (VeUIManager::*)(const VeChar8*))&VeUIManager::SetMainLayout),
			DefSingletonFunc("SetMainLayout", VeUIManager::ms_pSingleton, (void (VeUIManager::*)(VeUILayout*))&VeUIManager::SetMainLayout),
			DefSingletonFunc("GetMainLayout", VeUIManager::ms_pSingleton, &VeUIManager::GetMainLayout),

			DefSingletonFunc("PushLayout", VeUIManager::ms_pSingleton, (void (VeUIManager::*)(const VeChar8*,VeFloat32))&VeUIManager::PushLayout),
			DefSingletonFunc("PushLayout", VeUIManager::ms_pSingleton, (void (VeUIManager::*)(VeUILayout*,VeFloat32))&VeUIManager::PushLayout),

			DefSingletonFunc("PopLayout", VeUIManager::ms_pSingleton, (void (VeUIManager::*)())&VeUIManager::PopLayout),
			DefSingletonFunc("PopLayout", VeUIManager::ms_pSingleton, (void (VeUIManager::*)(VeFloat32))&VeUIManager::PopLayout),

			DefSingletonFunc("PopAllLayouts", VeUIManager::ms_pSingleton, (void (VeUIManager::*)())&VeUIManager::PopAllLayouts),
			DefSingletonFunc("PopAllLayouts", VeUIManager::ms_pSingleton, (void (VeUIManager::*)(VeFloat32))&VeUIManager::PopAllLayouts),

			DefSingletonFunc("FindWidget", VeUIManager::ms_pSingleton, &VeUIManager::FindWidget),
			DefSingletonFunc("DelScene", VeUIManager::ms_pSingleton, &VeUIManager::DelScene)
		]
	];
}
//--------------------------------------------------------------------------
