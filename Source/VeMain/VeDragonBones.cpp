////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeDragonBones.cpp
//  Version:     v1.00
//  Created:     17/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeDragonBones.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeDragonBones, VeResource);
//--------------------------------------------------------------------------
VeFloat32 VeDragonBones::ms_f32TexScale = 1.0f;
//--------------------------------------------------------------------------
VeDragonBones::VeDragonBones(const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(VeResource::DRAGON_BONES, pcName, pcGroup)
{

}
//--------------------------------------------------------------------------
VeDragonBones::~VeDragonBones()
{
	Unload();
}
//--------------------------------------------------------------------------
void VeDragonBones::UnloadImpl()
{

}
//--------------------------------------------------------------------------
bool VeDragonBones::HasProcess()
{
	return true;
}
//--------------------------------------------------------------------------
void VeDragonBones::LoadProcess(const VeMemoryIStreamPtr& spStream)
{
	VeXMLDocument kDoc;
	*spStream >> kDoc;
	VeXMLElement* pkTemp = kDoc.RootElement();
	VE_ASSERT(pkTemp->ValueToStr() == "dragonBones");
	m_f32InvFrameRate = 1.0f / pkTemp->Attribute("frameRate", 30.0f);
	pkTemp = pkTemp->FirstChildElement("armature");
	while(pkTemp)
	{
		m_kArmatureList.Increase();
		ParseArmature(m_kArmatureList.Back(), pkTemp);
		m_kArmatureMap[m_kArmatureList.Back().m_kName] = m_kArmatureList.Size() - 1;
		pkTemp = pkTemp->NextSiblingElement("armature");
	}
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseArmature(Armature& kOut, VeXMLElement* pkArmature)
{
	VE_ASSERT(pkArmature && pkArmature->ValueToStr() == "armature");
	kOut.m_kName = pkArmature->Attribute("name");
	VeXMLElement* pkTemp = pkArmature->FirstChildElement();
	while(pkTemp)
	{
		if(pkTemp->ValueToStr() == "bone")
		{
			kOut.m_kBoneList.Increase();
			ParseBone(kOut.m_kBoneList.Back(), pkTemp);
			kOut.m_kBoneMap[kOut.m_kBoneList.Back().m_kName] = kOut.m_kBoneList.Size() - 1;
		}
		else if(pkTemp->ValueToStr() == "skin")
		{
			kOut.m_kSkinList.Increase();
			ParseSkin(kOut.m_kSkinList.Back(), pkTemp, kOut);
			kOut.m_kSkinMap[kOut.m_kSkinList.Back().m_kName] = kOut.m_kSkinList.Size() - 1;
		}
		else if(pkTemp->ValueToStr() == "animation")
		{
			kOut.m_kAnimationList.Increase();
			ParseAnimation(kOut.m_kAnimationList.Back(), pkTemp, kOut);
			kOut.m_kAnimationMap[kOut.m_kAnimationList.Back().m_kName] = kOut.m_kAnimationList.Size() - 1;
		}
		pkTemp = pkTemp->NextSiblingElement();
	}
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseBone(Bone& kOut, VeXMLElement* pkBone)
{
	VE_ASSERT(pkBone && pkBone->ValueToStr() == "bone");
	kOut.m_kName = pkBone->Attribute("name");
	ParseTransform(kOut.m_kTransform, pkBone->FirstChildElement(), 0.0f);
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseTransform(Transform& kOut,
	VeXMLElement* pkTransform, VeFloat32 f32Rate)
{
	if(pkTransform)
	{
		VE_ASSERT(pkTransform->ValueToStr() == "transform");
		kOut.m_kPos.x = pkTransform->Attribute("pX", 0.0f) * f32Rate;
		kOut.m_kPos.y = pkTransform->Attribute("pY", 0.0f) * f32Rate;
		kOut.m_kSkew.x = VeDegreeToRadiantf(pkTransform->Attribute("skX", 0.0f));
		kOut.m_kSkew.y = VeDegreeToRadiantf(pkTransform->Attribute("skY", 0.0f));
		kOut.m_kScale.x = pkTransform->Attribute("scX", 0.0f);
		kOut.m_kScale.y = pkTransform->Attribute("scY", 0.0f);
		VeTransform2D kTrans;
		kTrans.Set(VeVector2D::ZERO, kOut.m_kSkew, kOut.m_kScale);
		kTrans.ApplyVector(kOut.m_kPos, kOut.m_kPos);
		kOut.m_kPos.x += pkTransform->Attribute("x", 0.0f);
		kOut.m_kPos.y += pkTransform->Attribute("y", 0.0f);
		kOut.m_kPos *= ms_f32TexScale;
	}
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseSkin(Skin& kOut, VeXMLElement* pkSkin,
	const Armature& kArmature)
{
	VE_ASSERT(pkSkin && pkSkin->ValueToStr() == "skin");
	kOut.m_kName = pkSkin->Attribute("name");
	VeXMLElement* pkTemp = pkSkin->FirstChildElement("slot");
	while(pkTemp)
	{
		kOut.m_kSlotList.Increase();
		ParseSlot(kOut.m_kSlotList.Back(), pkTemp, kArmature);
		pkTemp = pkTemp->NextSiblingElement("slot");
	}
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseSlot(Slot& kOut, VeXMLElement* pkSlot,
	const Armature& kArmature)
{
	VE_ASSERT(pkSlot && pkSlot->ValueToStr() == "slot");
	kOut.m_kName = pkSlot->Attribute("name");
	const VeChar8* pcParent = pkSlot->Attribute("parent");
	const VeUInt32* pu32BoneIndex = kArmature.m_kBoneMap.Find(pcParent);
	VE_ASSERT(pu32BoneIndex);
	kOut.m_u32Bone = *pu32BoneIndex;
	kOut.m_f32ZOrder = pkSlot->Attribute("z", 0.0f);
	VeXMLElement* pkTemp = pkSlot->FirstChildElement("display");
	while(pkTemp)
	{
		kOut.m_kDisplayList.Increase();
		ParseDisplay(kOut.m_kDisplayList.Back(), pkTemp);
		pkTemp = pkTemp->NextSiblingElement("display");
	}
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseDisplay(Display&kOut, VeXMLElement* pkDisplay)
{
	VE_ASSERT(pkDisplay && pkDisplay->ValueToStr() == "display");
	kOut.m_eType = pkDisplay->Attribute("type") == VeString("armature") ? DIS_ARMATURE : DIS_IMAGE;
	kOut.m_kName = pkDisplay->Attribute("name");
	ParseTransform(kOut.m_kTransform, pkDisplay->FirstChildElement(), -1.0f);
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseAnimation(Animation& kOut, VeXMLElement* pkAni,
	const Armature& kArmature)
{
	VE_ASSERT(pkAni && pkAni->ValueToStr() == "animation");
	kOut.m_kName = pkAni->Attribute("name");
	kOut.m_f32FadeInTime = pkAni->Attribute("fadeInTime", 0.0f);
	kOut.m_f32Duration = pkAni->Attribute("duration", 0.0f) * m_f32InvFrameRate;
	kOut.m_f32Scale = pkAni->Attribute("scale", 1.0f);
	kOut.m_u32Loop = pkAni->Attribute("loop", 0);
	VeString kEasing = pkAni->Attribute("tweenEasing", "NaN");
	if(kEasing == "NaN")
	{
		kOut.m_eTweenEasing = VeTweenEasing::TYPE_NONE;
	}
	else
	{
		kOut.m_eTweenEasing = VeTweenEasing::TYPE_LINEAR;
	}
	VeXMLElement* pkTemp = pkAni->FirstChildElement();
	VeFloat32 f32PassTime(0);
	while(pkTemp)
	{
		if(pkTemp->ValueToStr() == "frame")
		{
			kOut.m_kFrameList.Increase();
			ParseFrameAnimation(f32PassTime, kOut.m_kFrameList.Back(), pkTemp);
		}
		else if(pkTemp->ValueToStr() == "timeline")
		{
			kOut.m_kTimelineList.Increase();
			ParseTimeline(kOut.m_kTimelineList.Back(), pkTemp, kArmature, kOut.m_eTweenEasing);
		}
		pkTemp = pkTemp->NextSiblingElement();
	}
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseFrameAnimation(VeFloat32& f32PassTime,
	FrameAnimation& kOut, VeXMLElement* pkFrame)
{
	VE_ASSERT(pkFrame && pkFrame->ValueToStr() == "frame");
	f32PassTime += pkFrame->Attribute("duration", 0.0f) * m_f32InvFrameRate;
	kOut.m_f32Until = f32PassTime;
	kOut.m_kEvent = pkFrame->Attribute("event");
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseTimeline(Timeline& kOut, VeXMLElement* pkTimeline,
	const Armature& kArmature, VeTweenEasing::Type eEasing)
{
	VE_ASSERT(pkTimeline && pkTimeline->ValueToStr() == "timeline");
	const VeChar8* pcName = pkTimeline->Attribute("name");
	const VeUInt32* pu32BoneIndex = kArmature.m_kBoneMap.Find(pcName);
	VE_ASSERT(pu32BoneIndex);
	kOut.m_u32Bone = *pu32BoneIndex;
	kOut.m_f32Scale = pkTimeline->Attribute("scale", 1.0f);
	kOut.m_f32Offset = pkTimeline->Attribute("offset", 0.0f);
	VeXMLElement* pkTemp = pkTimeline->FirstChildElement("frame");
	VeFloat32 f32PassTime(0);
	while(pkTemp)
	{
		kOut.m_kFrameList.Increase();
		ParseFrame(f32PassTime, kOut.m_kFrameList.Back(), pkTemp, eEasing);
		pkTemp = pkTemp->NextSiblingElement();
	}
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseFrame(VeFloat32& f32PassTime, Frame& kOut,
	VeXMLElement* pkFrame, VeTweenEasing::Type eEasing)
{
	VE_ASSERT(pkFrame && pkFrame->ValueToStr() == "frame");
	kOut.m_u16Display = pkFrame->Attribute("displayIndex", 0);
	kOut.m_u16Hide = pkFrame->Attribute("hide", 0);
	kOut.m_f32ZOrder = pkFrame->Attribute("z", 0.0f);
	VeString kEasing = pkFrame->Attribute("tweenEasing", "NaN");
	if(kEasing == "NaN")
	{
		kOut.m_eTweenEasing = VeTweenEasing::TYPE_NONE;
	}
	else
	{
		kOut.m_eTweenEasing = VeTweenEasing::TYPE_LINEAR;
	}
	kOut.m_f32TweenRotate = pkFrame->Attribute("tweenRotate", 0.0f);
	f32PassTime += pkFrame->Attribute("duration", 0.0f) * m_f32InvFrameRate;
	kOut.m_f32Until = f32PassTime;
	kOut.m_kEvent = pkFrame->Attribute("event");
	ParseTransform(kOut.m_kTransform, pkFrame->FirstChildElement("transform"), 1.0f);
	ParseColor(kOut.m_kMulColor, kOut.m_kAddColor, pkFrame->FirstChildElement("colorTransform"));
}
//--------------------------------------------------------------------------
void VeDragonBones::ParseColor(VeColor& kMulOut, VeColor& kAddOut,
	VeXMLElement* pkColor)
{
	if(pkColor)
	{
		VE_ASSERT(pkColor && pkColor->ValueToStr() == "colorTransform");
		kMulOut.r = pkColor->Attribute("rM", 100.0f) * 0.01f;
		kMulOut.g = pkColor->Attribute("gM", 100.0f) * 0.01f;
		kMulOut.b = pkColor->Attribute("bM", 100.0f) * 0.01f;
		kMulOut.a = pkColor->Attribute("aM", 100.0f) * 0.01f;
		kAddOut.r = pkColor->Attribute("rO", 0.0f) / 255.0f;
		kAddOut.g = pkColor->Attribute("gO", 0.0f) / 255.0f;
		kAddOut.b = pkColor->Attribute("bO", 0.0f) / 255.0f;
		kAddOut.a = pkColor->Attribute("aO", 0.0f) / 255.0f;
	}
	else
	{
		kMulOut = VeColor::WHITE;
		kAddOut = VeColor::ZERO;
	}
}
//--------------------------------------------------------------------------
VeResource* VeDragonBones::CreateResource(const VeChar8* pcName,
	const VeChar8* pcGroup)
{
	return VE_NEW VeDragonBones(pcName, pcGroup);
}
//--------------------------------------------------------------------------
void VeDragonBones::SetTexScale(VeFloat32 f32Scale)
{
	ms_f32TexScale = f32Scale;
}
//--------------------------------------------------------------------------
VeFloat32 VeDragonBones::GetTexScale()
{
	return ms_f32TexScale;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeDragonBonesEntity, VeSceneNode2D);
//--------------------------------------------------------------------------
VeDragonBonesEntity::VeDragonBonesEntity(const VeChar8* pcName)
{
	m_spResource = VeGetDragonBones(pcName, NULL);
	VE_ASSERT(m_spResource);
	Init();
}
//--------------------------------------------------------------------------
VeDragonBonesEntity::VeDragonBonesEntity(const VeDragonBonesPtr& spRes)
{
	m_spResource = spRes;
	VE_ASSERT(m_spResource);
	Init();
}
//--------------------------------------------------------------------------
VeDragonBonesEntity::~VeDragonBonesEntity()
{
	Stop();
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Init()
{
	VE_ASSERT(m_spResource && m_spResource->GetState() == VeResource::LOADED);
	m_kArmatureMap["root"] = m_kArmatureList.Size();
	m_kArmatureList.PushBack(VE_NEW Armature());
	InitArmature(*m_kArmatureList.Back(), m_spResource->m_kArmatureList.Front());
	AttachChild(m_kArmatureList.Front()->m_spNode);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::InitArmature(Armature& kOut,
	VeDragonBones::Armature& kRes)
{
	kOut.m_pkRes = &kRes;
	kOut.m_spNode = VE_NEW VeSceneNode2D;
	kOut.m_kBoneList.Resize(kRes.m_kBoneList.Size());
	for(VeUInt32 i(0); i < kOut.m_kBoneList.Size(); ++i)
	{
		const VeDragonBones::Bone& kBone = kRes.m_kBoneList[i];
		
		VeSceneNode2DPtr& spBoneNode = kOut.m_kBoneList[i].m_spNode;
		spBoneNode = VE_NEW VeSceneNode2D;
		spBoneNode->SetPosition(kBone.m_kTransform.m_kPos);
		spBoneNode->SetSkew(kBone.m_kTransform.m_kSkew);
		spBoneNode->SetScale(kBone.m_kTransform.m_kScale);
		kOut.m_spNode->AttachChild(spBoneNode);

	}
	UseSkin(kOut, kRes, 0);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::UseSkin(Armature& kOut,
	const VeDragonBones::Armature& kRes, VeUInt32 u32Skin)
{
	VeChar8 acBuffer[64];
	const VeDragonBones::Skin& kSkin = kRes.m_kSkinList[u32Skin];
	for(VeUInt32 i(0); i < kSkin.m_kSlotList.Size(); ++i)
	{
		const VeDragonBones::Slot& kResSlot = kSkin.m_kSlotList[i];
		Bone& kSlot = kOut.m_kBoneList[kResSlot.m_u32Bone];
		kSlot.m_spNode->SetZOrder(kResSlot.m_f32ZOrder);
		kSlot.m_kDisplayList.Resize(kResSlot.m_kDisplayList.Size());
		for(VeUInt32 k(0); k < kSlot.m_kDisplayList.Size(); ++k)
		{
			const VeDragonBones::Display& kDisplay = kResSlot.m_kDisplayList[k];
			Display& kDisplayNode = kSlot.m_kDisplayList[k];
			kDisplayNode.m_spNode = VE_NEW VeSceneNode2D;
			kDisplayNode.m_spNode->SetPosition(kDisplay.m_kTransform.m_kPos);
			kDisplayNode.m_spNode->SetSkew(kDisplay.m_kTransform.m_kSkew);
			kDisplayNode.m_spNode->SetScale(kDisplay.m_kTransform.m_kScale);
			if(kDisplay.m_eType == VeDragonBones::DIS_IMAGE)
			{
				{
					const VeChar8* pcName = kDisplay.m_kName;
					if(VeStricmp(pcName + kDisplay.m_kName.GetLength() - 4, ".png") == 0)
					{
						VeSprintf(acBuffer, "%s", pcName);
					}
					else
					{
						VeSprintf(acBuffer, "%s.png", pcName);
					}
				}
				VeSprite2DPtr spImage = VE_NEW VeSprite2D(acBuffer);
				spImage->SetAnchor(0.0f, 0.0f);
				kDisplayNode.m_spNode->AttachRenderable(spImage);
			}
			else if(kDisplay.m_eType == VeDragonBones::DIS_ARMATURE)
			{
				VeString kCurName = kOut.m_kName.Length() ? (kOut.m_kName + "/" + kResSlot.m_kName) : kResSlot.m_kName;
				VE_ASSERT(!m_kArmatureMap.Find(kCurName));
				m_kArmatureMap[kCurName] = m_kArmatureList.Size();
				m_kArmatureList.PushBack(VE_NEW Armature());
				m_kArmatureList.Back()->m_kName = kCurName;
				kDisplayNode.m_pkArmature = m_kArmatureList.Back();
				VeUInt32* pu32Index = m_spResource->m_kArmatureMap.Find(kDisplay.m_kName);
				VE_ASSERT(pu32Index/* && (&m_kArmatureList[*pu32Index]) != &kOut*/);
				Armature& kNew = *m_kArmatureList.Back();
				InitArmature(kNew, m_spResource->m_kArmatureList[*pu32Index]);
				kDisplayNode.m_spNode->AttachChild(kNew.m_spNode);
				{
					const VeChar8* pcFlag = VeStrrchr(kResSlot.m_kName, '_');
					if(pcFlag && (!VeStricmp(pcFlag, "_auto")))
					{
						kDisplayNode.m_pkArmature->m_bAuto = true;
					}
				}
			}
		}
		kSlot.m_spNode->AttachChild(kSlot.m_kDisplayList.Front().m_spNode);
		kOut.m_kBoneList[i].m_u32Display = VE_INFINITE;
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Play(VeUInt32 u32Animation, VeUInt32 u32Armature,
	VeFloat32 f32Priority, VeFloat32 f32Blend, VeFloat32 f32Scale, bool bBreak)
{
	if(u32Armature < m_kArmatureList.Size() && m_kArmatureList[u32Armature]->m_bAuto == false)
	{
		VeVector< VePair<EventType,const VeChar8*> > kEventList;
		m_kArmatureList[u32Armature]->Play(u32Animation, f32Priority, f32Blend, f32Scale, bBreak, kEventList);
		if(kEventList.Size()) ProcessEvent(kEventList);
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Play(const VeChar8* pcAnimation, VeFloat32 f32Priority,
	VeFloat32 f32Blend, VeFloat32 f32Scale, bool bBreak)
{
	VeVector< VePair<EventType,const VeChar8*> > kEventList;
	for(VeUInt32 i(0); i < m_kArmatureList.Size(); ++i)
	{
		Armature& kArmature = *m_kArmatureList[i];
		if(kArmature.m_bAuto == false)
		{
			VeUInt32* pu32Iter = kArmature.m_pkRes->m_kAnimationMap.Find(pcAnimation);
			if(pu32Iter)
			{
				kArmature.Play(*pu32Iter, f32Priority, f32Blend, f32Scale, bBreak, kEventList);
			}
		}
	}
	if(kEventList.Size()) ProcessEvent(kEventList);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Play(const VeChar8* pcArmature,
	const VeChar8* pcAnimation, VeFloat32 f32Priority, VeFloat32 f32Blend,
	VeFloat32 f32Scale, bool bBreak)
{
	VeUInt32 u32Arm = GetArmatureIndex(pcArmature);
	VeUInt32 u32Ani = GetAnimationIndex(pcAnimation, u32Arm);
	Play(u32Ani, u32Arm, f32Priority, f32Blend, f32Scale, bBreak);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Stop(VeUInt32 u32Armature)
{
	//m_kArmatureList[u32Armature].m_kPlayAni.m_pkShowAni = NULL;
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Stop()
{
	/*for(VeUInt32 i(0); i < m_kArmatureList.Size(); ++i)
	{
		m_kArmatureList[i].m_kPlayAni.m_pkShowAni = NULL;
	}
	m_spAnimation->Detach();*/
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Visit(VeRenderQueue& kQueue)
{
	Update(g_pTime->GetDeltaTime());
	VeSceneNode2D::Visit(kQueue);
}
//--------------------------------------------------------------------------
VeSceneNode2DPtr VeDragonBonesEntity::GetBone(const VeChar8* pcBone,
	VeUInt32 u32Armature)
{
	if(u32Armature < m_kArmatureList.Size())
	{
		Armature& kArmature = *m_kArmatureList[u32Armature];
		VeUInt32* pu32Iter = kArmature.m_pkRes->m_kBoneMap.Find(pcBone);
		if(pu32Iter)
		{
			return kArmature.m_kBoneList[*pu32Iter].m_spNode;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
const VeTransform2D* VeDragonBonesEntity::GetBoneTransform(
	const VeChar8* pcBone, VeUInt32 u32Armature)
{
	VeSceneNode2DPtr spNode = GetBone(pcBone, u32Armature);
	return spNode ? &(spNode->GetDerivedTransform()) : NULL;
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Update(VeFloat32 f32Delta)
{
	EventTask* pkTask = VE_NEW EventTask;
	pkTask->m_spEntity = this;
	for(VeUInt32 i(0); i < m_kArmatureList.Size(); ++i)
	{
		PlayAni& kAni = m_kArmatureList[i]->m_kPlayAni;
		kAni.Update(f32Delta, m_kArmatureList[i]->m_kBoneList, pkTask->m_kEvent);
	}
	g_pResourceManager->AddFGTask(VeResourceManager::BG_QUEUE_EVENT, pkTask);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::ProcessEvent(
	VeVector< VePair<EventType,const VeChar8*> >& kEventList)
{
	for(VeVector< VePair<EventType,const VeChar8*> >::iterator it = kEventList.Begin();
		it != kEventList.End(); ++it)
	{
		ProcessEvent(*it);
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::ProcessEvent(
	VePair<EventType,const VeChar8*>& kEvent)
{
	if(kEvent.m_tFirst == EVT_KEY)
	{
		VeChar8 acBuffer[256];
		VeStrcpy(acBuffer, kEvent.m_tSecond);
		VeChar8* pcContent;
		const VeChar8* pcTemp = VeStrtok(acBuffer, "[", &pcContent);
		if(!VeStrcmp(pcTemp, "key"))
		{
			m_kEvent.Callback(this, EVT_KEY, VeStrtok(NULL, "]", &pcContent));
		}
	}
	else
	{
		m_kEvent.Callback(this, kEvent.m_tFirst, kEvent.m_tSecond);
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::AniLevel::EventAfterMain(
	VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	if(m_pkCurAni->m_kFrameList.Size())
	{
		for(VeUInt32 i(m_u16Frame + 1); i < m_pkCurAni->m_kFrameList.Size(); ++i)
		{
			VeString& kEvent = m_pkCurAni->m_kFrameList[i].m_kEvent;
			if(kEvent.Length())
			{
				kEvents.PushBack(VePair<EventType,const VeChar8*>(EVT_KEY, kEvent));
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::AniLevel::EventAfterTimeline(
	VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	for(VeUInt32 i(0); i < m_kFrame.Size(); ++i)
	{
		VeDragonBones::Timeline& kTimeline = m_pkCurAni->m_kTimelineList[i];
		for(VeUInt32 j(m_kFrame[i] + 1); j < kTimeline.m_kFrameList.Size(); ++j)
		{
			VeString& kEvent = kTimeline.m_kFrameList[j].m_kEvent;
			if(kEvent.Length())
			{
				kEvents.PushBack(VePair<EventType,const VeChar8*>(EVT_KEY, kEvent));
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::AniLevel::EventMain(
	VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	if(m_pkCurAni->m_kFrameList.Size())
	{
		VeString& kEvent = m_pkCurAni->m_kFrameList[m_u16Frame].m_kEvent;
		if(kEvent.Length())
		{
			kEvents.PushBack(VePair<EventType,const VeChar8*>(EVT_KEY, kEvent));
		}
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::AniLevel::EventTimeline(
	VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	for(VeUInt32 i(0); i < m_kFrame.Size(); ++i)
	{
		VeDragonBones::Timeline& kTimeline = m_pkCurAni->m_kTimelineList[i];
		VeString& kEvent = kTimeline.m_kFrameList[m_kFrame[i]].m_kEvent;
		if(kEvent.Length())
		{
			kEvents.PushBack(VePair<EventType,const VeChar8*>(EVT_KEY, kEvent));
		}
	}
}
//--------------------------------------------------------------------------
VeFloat32 LerpAngle(VeFloat32 f32Blend, VeFloat32 f32Angle0,
	VeFloat32 f32Angle1)
{
	f32Angle0 = VeNormaliseAnglef(f32Angle0);
	f32Angle1 = VeNormaliseAnglef(f32Angle1);
	if(VeFabsf(f32Angle0 - f32Angle1) < VE_MATH_PI_F)
	{
		return VeLerp(f32Blend, f32Angle0, f32Angle1);
	}
	else if(f32Angle0 < f32Angle1)
	{
		return VeLerp(f32Blend, f32Angle0 + VE_MATH_2PI_F, f32Angle1) - VE_MATH_2PI_F;
	}
	else
	{
		return VeLerp(f32Blend, f32Angle0, f32Angle1 + VE_MATH_2PI_F) - VE_MATH_2PI_F;
	}
}
//--------------------------------------------------------------------------
VeVector2D LerpSkew(VeFloat32 f32Blend, const VeVector2D& kSkew0,
	const VeVector2D& kSkew1)
{
	return VeVector2D(LerpAngle(f32Blend, kSkew0.x, kSkew1.x), LerpAngle(f32Blend, kSkew0.y, kSkew1.y));
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::AniLevel::Update(VeFloat32 f32Delta, PlayAni& kAni,
	VeVector<Bone>& kBones, VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	VeFloat32 f32Blend(1.0f);
	if(kAni.m_f32FadeInTime)
	{
		f32Blend = kAni.m_f32InvFadeInTime * kAni.m_f32PassTime;
	}
	m_f32PassTime += f32Delta * m_f32Scale * m_pkCurAni->m_f32Scale;
	while(m_f32PassTime > m_pkCurAni->m_f32Duration)
	{
		EventAfterMain(kEvents);
		EventAfterTimeline(kEvents);
		m_f32PassTime -= m_pkCurAni->m_f32Duration;
		if((!m_pkCurAni->m_u32Loop) || m_u16Loop < (m_pkCurAni->m_u32Loop - 1))
		{
			kEvents.PushBack(VeMakePair(EVT_END_LOOP, m_pkCurAni->m_kName));
			VeZeroMemory(m_kFrame.Begin(), m_kFrame.Size() * sizeof(VeUInt16));
			m_u16Frame = 0;
			++m_u16Loop;
			kEvents.PushBack(VeMakePair(EVT_BEGIN, m_pkCurAni->m_kName));
			EventMain(kEvents);
			EventTimeline(kEvents);
		}
		else
		{
			kEvents.PushBack(VeMakePair(EVT_END, m_pkCurAni->m_kName));
			for(VeUInt32 i(0); i < m_kFrame.Size(); ++i)
			{
				VeDragonBones::Timeline& kTimeline = m_pkCurAni->m_kTimelineList[i];
				if(kTimeline.m_kFrameList.Size())
				{
					VeDragonBones::Frame& kCur = kTimeline.m_kFrameList.Back();
					Bone& kBone = kBones[kTimeline.m_u32Bone];
					if(kCur.m_u16Hide)
					{
						kBone.SetVisibleMask(0);
					}
					else
					{
						kBone.SetVisibleMask(VE_INFINITE);
						VeVector2D kPos, kSkew, kScale;
						VeColor kMul, kAdd;
						kPos = kCur.m_kTransform.m_kPos;
						kSkew = kCur.m_kTransform.m_kSkew;
						kScale = kCur.m_kTransform.m_kScale;
						kMul = kCur.m_kMulColor;
						kAdd = kCur.m_kAddColor;
						if(f32Blend < 1.0f)
						{
							kBone.SetPosition(VeLerp(f32Blend, kBone.m_kPos, kPos));
							kBone.SetSkew(LerpSkew(f32Blend, kBone.m_kSkew, kSkew));
							kBone.SetScale(VeLerp(f32Blend, kBone.m_kScale, kScale));
							kBone.SetMulColor(VeLerp(f32Blend, kBone.m_kMul, kMul));
							kBone.SetAddColor(VeLerp(f32Blend, kBone.m_kAdd, kAdd));
						}
						else
						{
							kBone.SetPosition(kPos);
							kBone.SetSkew(kSkew);
							kBone.SetScale(kScale);
							kBone.SetMulColor(kMul);
							kBone.SetAddColor(kAdd);
						}
						kBone.SetZOrder(kCur.m_f32ZOrder);
						kBone.Set(kCur.m_u16Display, kEvents);
					}
				}
			}
			if(m_kAniList.Size())
			{
				AniTick& kTick = m_kAniList.Front();
				m_f32PassTime *= (kTick.m_f32Scale * kTick.m_pkAniRes->m_f32Scale) / (m_f32Scale * m_pkCurAni->m_f32Scale);
				m_pkCurAni = kTick.m_pkAniRes;
				m_f32Scale = kTick.m_f32Scale;
				m_f32Blend = kTick.m_f32Blend;
				m_kFrame.Resize(m_pkCurAni->m_kTimelineList.Size());
				if(m_kFrame.Size())
				{
					VeZeroMemory(m_kFrame.Begin(), m_kFrame.Size() * sizeof(VeUInt16));
				}
				m_u16Frame = 0;
				m_u16Loop = 0;
				m_kAniList.PopFront();
				for(VeUInt32 i(0); i < kBones.Size(); ++i)
				{
					kBones[i].Dump();
					kBones[i].SetVisibleMask(0);
				}
				for(VeUInt32 i(0); i < m_pkCurAni->m_kTimelineList.Size(); ++i)
				{
					VeDragonBones::Timeline& kTimeline = m_pkCurAni->m_kTimelineList[i];
					kBones[kTimeline.m_u32Bone].SetVisibleMask(VE_INFINITE);
				}
				kEvents.PushBack(VeMakePair(EVT_BEGIN, m_pkCurAni->m_kName));
				EventMain(kEvents);
				EventTimeline(kEvents);
				kAni.m_f32FadeInTime = m_f32Blend;
				kAni.m_f32InvFadeInTime = 1.0f / m_f32Blend;
				kAni.m_f32PassTime = m_f32PassTime;
			}
			else
			{
				m_pkCurAni = NULL;
				return;
			}
		}
	}
	if(m_pkCurAni->m_kFrameList.Size())
	{
		while(m_u16Frame < (m_pkCurAni->m_kFrameList.Size() - 1)
			&& m_f32PassTime >= m_pkCurAni->m_kFrameList[m_u16Frame].m_f32Until)
		{
			++m_u16Frame;
			VeString& kEvent = m_pkCurAni->m_kFrameList[m_u16Frame].m_kEvent;
			if(kEvent.Length())
			{
				kEvents.PushBack(VePair<EventType,const VeChar8*>(EVT_KEY, kEvent));
			}
		}
	}
	for(VeUInt32 i(0); i < m_kFrame.Size(); ++i)
	{
		VeDragonBones::Timeline& kTimeline = m_pkCurAni->m_kTimelineList[i];
		VeUInt16& u16Frame = m_kFrame[i];
		if(kTimeline.m_kFrameList.Size())
		{
			while(u16Frame < (kTimeline.m_kFrameList.Size() - 1)
				&& m_f32PassTime >= kTimeline.m_kFrameList[u16Frame].m_f32Until)
			{
				++u16Frame;
				VeString& kEvent = kTimeline.m_kFrameList[u16Frame].m_kEvent;
				if(kEvent.Length())
				{
					kEvents.PushBack(VePair<EventType,const VeChar8*>(EVT_KEY, kEvent));
				}
			}
			VeUInt16 u16Next = u16Frame + 1;
			if(u16Next >= kTimeline.m_kFrameList.Size())
			{
				if((!m_pkCurAni->m_u32Loop) || m_u16Loop < (m_pkCurAni->m_u32Loop - 1))
				{
					u16Next = 0;
				}
				else
				{
					u16Next = u16Frame;
				}
			}
			if(kTimeline.m_kFrameList[u16Next].m_u16Display >= kBones[kTimeline.m_u32Bone].m_kDisplayList.Size()
				|| kTimeline.m_kFrameList[u16Next].m_u16Hide)
			{
				u16Next = u16Frame;
			}
			VeDragonBones::Frame& kCur = kTimeline.m_kFrameList[u16Frame];
			VeDragonBones::Frame& kNxt = kTimeline.m_kFrameList[u16Next];
			Bone& kBone = kBones[kTimeline.m_u32Bone];
			if(kCur.m_u16Hide)
			{
				kBone.SetVisibleMask(0);
			}
			else
			{
				kBone.SetVisibleMask(VE_INFINITE);
				VeVector2D kPos, kSkew, kScale;
				VeColor kMul, kAdd;
				if(kCur.m_eTweenEasing || kNxt.m_eTweenEasing)
				{
					VeFloat32 f32Rate;
					if(u16Frame)
					{
						VeFloat32 f32LastUtil = kTimeline.m_kFrameList[u16Frame - 1].m_f32Until;
						VE_ASSERT(f32LastUtil <= m_f32PassTime);
						f32Rate = g_pTweenEasing->Ease(kCur.m_eTweenEasing, m_f32PassTime - f32LastUtil, kCur.m_f32Until - f32LastUtil);
					}
					else
					{
						f32Rate = g_pTweenEasing->Ease(kCur.m_eTweenEasing, m_f32PassTime, kCur.m_f32Until);
					}
					kPos = VeLerp(f32Rate, kCur.m_kTransform.m_kPos, kNxt.m_kTransform.m_kPos);
					kSkew = LerpSkew(f32Rate, kCur.m_kTransform.m_kSkew, kNxt.m_kTransform.m_kSkew);
					kScale = VeLerp(f32Rate, kCur.m_kTransform.m_kScale, kNxt.m_kTransform.m_kScale);
					kMul = VeLerp(f32Rate, kCur.m_kMulColor, kNxt.m_kMulColor);
					kAdd = VeLerp(f32Rate, kCur.m_kAddColor, kNxt.m_kAddColor);
				}
				else
				{
					kPos = kCur.m_kTransform.m_kPos;
					kSkew = kCur.m_kTransform.m_kSkew;
					kScale = kCur.m_kTransform.m_kScale;
					kMul = kCur.m_kMulColor;
					kAdd = kCur.m_kAddColor;
				}
				if(f32Blend < 1.0f)
				{
					kBone.SetPosition(VeLerp(f32Blend, kBone.m_kPos, kPos));
					kBone.SetSkew(LerpSkew(f32Blend, kBone.m_kSkew, kSkew));
					kBone.SetScale(VeLerp(f32Blend, kBone.m_kScale, kScale));
					kBone.SetMulColor(VeLerp(f32Blend, kBone.m_kMul, kMul));
					kBone.SetAddColor(VeLerp(f32Blend, kBone.m_kAdd, kAdd));
				}
				else
				{
					kBone.SetPosition(kPos);
					kBone.SetSkew(kSkew);
					kBone.SetScale(kScale);
					kBone.SetMulColor(kMul);
					kBone.SetAddColor(kAdd);
				}
				kBone.SetZOrder(kCur.m_f32ZOrder);
				kBone.Set(kCur.m_u16Display, kEvents);
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::AniLevel::Update(VeFloat32 f32Delta,
	VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	m_f32PassTime += f32Delta * m_f32Scale * m_pkCurAni->m_f32Scale;
	while(m_f32PassTime > m_pkCurAni->m_f32Duration)
	{
		EventAfterMain(kEvents);
		kEvents.PushBack(VeMakePair(EVT_BEGIN, m_pkCurAni->m_kName));
		m_f32PassTime -= m_pkCurAni->m_f32Duration;
		if((!m_pkCurAni->m_u32Loop) || m_u16Loop < (m_pkCurAni->m_u32Loop - 1))
		{
			kEvents.PushBack(VeMakePair(EVT_END_LOOP, m_pkCurAni->m_kName));
			VeZeroMemory(m_kFrame.Begin(), m_kFrame.Size() * sizeof(VeUInt16));
			m_u16Frame = 0;
			++m_u16Loop;
			kEvents.PushBack(VeMakePair(EVT_BEGIN, m_pkCurAni->m_kName));
			EventMain(kEvents);
		}
		else if(m_kAniList.Size())
		{
			kEvents.PushBack(VeMakePair(EVT_END, m_pkCurAni->m_kName));
			AniTick& kTick = m_kAniList.Front();
			m_f32PassTime *= (kTick.m_f32Scale * kTick.m_pkAniRes->m_f32Scale) / (m_f32Scale * m_pkCurAni->m_f32Scale);
			m_pkCurAni = kTick.m_pkAniRes;
			m_f32Scale = kTick.m_f32Scale;
			m_f32Blend = kTick.m_f32Blend;
			m_kFrame.Resize(m_pkCurAni->m_kTimelineList.Size());
			if(m_kFrame.Size())
			{
				VeZeroMemory(m_kFrame.Begin(), m_kFrame.Size() * sizeof(VeUInt16));
			}
			m_u16Frame = 0;
			m_u16Loop = 0;
			m_kAniList.PopFront();
			kEvents.PushBack(VeMakePair(EVT_BEGIN, m_pkCurAni->m_kName));
			EventMain(kEvents);
		}
		else
		{
			m_pkCurAni = NULL;
			return;
		}
	}
	if(m_pkCurAni)
	{
		if(m_pkCurAni->m_kFrameList.Size())
		{
			while(m_u16Frame < (m_pkCurAni->m_kFrameList.Size() - 1)
				&& m_f32PassTime >= m_pkCurAni->m_kFrameList[m_u16Frame].m_f32Until)
			{
				++m_u16Frame;
				VeString& kEvent = m_pkCurAni->m_kFrameList[m_u16Frame].m_kEvent;
				if(kEvent.Length())
				{
					kEvents.PushBack(VePair<EventType,const VeChar8*>(EVT_KEY, kEvent));
				}
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::PlayAni::Update(VeFloat32 f32Delta,
	VeVector<Bone>& kBones, VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	if(m_kAniMap.Size())
	{
		if(m_f32FadeInTime)
		{
			m_f32PassTime += f32Delta;
			if(m_f32PassTime >= m_f32FadeInTime)
			{
				m_f32FadeInTime = 0.0f;
				m_f32InvFadeInTime = 0.0f;
				m_f32PassTime = 0.0f;
			}
		}
		VeMap<VeFloat32,AniLevel>::iterator it = m_kAniMap.Last();
		while(true)
		{
			it->m_tSecond.Update(f32Delta, *this, kBones, kEvents);
			if(it->m_tSecond.m_pkCurAni)
			{
				--it;
				break;
			}
			else
			{
				VE_ASSERT(it->m_tSecond.m_kAniList.Empty());
				VeMap<VeFloat32,AniLevel>::iterator itDelete = it--;
				m_kAniMap.Erase(itDelete);
				if(it == m_kAniMap.End())
				{
					break;
				}
				else
				{
					for(VeUInt32 i(0); i < kBones.Size(); ++i)
					{
						kBones[i].Dump();
						kBones[i].SetVisibleMask(0);
					}
					for(VeUInt32 i(0); i < it->m_tSecond.m_pkCurAni->m_kTimelineList.Size(); ++i)
					{
						VeDragonBones::Timeline& kTimeline = it->m_tSecond.m_pkCurAni->m_kTimelineList[i];
						kBones[kTimeline.m_u32Bone].SetVisibleMask(VE_INFINITE);
					}
					m_f32FadeInTime = it->m_tSecond.m_f32Blend;
					m_f32InvFadeInTime = 1.0f / m_f32FadeInTime;
					m_f32PassTime = 0.0f;
				}
			}
		}
		while(it != m_kAniMap.End())
		{
			it->m_tSecond.Update(f32Delta, kEvents);
			if(it->m_tSecond.m_pkCurAni)
			{
				--it;
			}
			else
			{
				VE_ASSERT(it->m_tSecond.m_kAniList.Empty());
				VeMap<VeFloat32,AniLevel>::iterator itDelete = it--;
				m_kAniMap.Erase(itDelete);
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::SetVisibleMask(VeUInt32 u32Mask)
{
	m_spNode->SetVisibleMask(u32Mask);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::SetZOrder(VeFloat32 f32ZOrder)
{
	m_spNode->SetZOrder(f32ZOrder);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::Set(VeUInt32 u32Display,
	VeVector< VePair<EventType,const VeChar8*> >& kEvents)
{
	if(u32Display != m_u32Display)
	{
		if(m_u32Display < m_kDisplayList.Size())
		{
			m_kDisplayList[m_u32Display].m_spNode->DetachFromParent();
		}
		if(u32Display < m_kDisplayList.Size())
		{
			Display& kDisplay = m_kDisplayList[u32Display];
			m_spNode->AttachChild(kDisplay.m_spNode);
			if(m_u32Display >= m_kDisplayList.Size() && kDisplay.m_pkArmature && kDisplay.m_pkArmature->m_bAuto)
			{
				kDisplay.m_pkArmature->Play(0, 0.0f, 0.0f, 1.0f, true, kEvents);
			}
		}
		m_u32Display = u32Display;
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::Dump()
{
	m_kPos = m_spNode->GetPosition();
	m_kSkew = m_spNode->GetSkew();
	m_kScale = m_spNode->GetScale();
	m_kMul = m_spNode->GetMulColor();
	m_kAdd = m_spNode->GetAddColor();
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::SetPosition(const VeVector2D& kPos)
{
	m_spNode->SetPosition(kPos);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::SetSkew(const VeVector2D& kSkew)
{
	m_spNode->SetSkew(kSkew);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::SetScale(const VeVector2D& kScale)
{
	m_spNode->SetScale(kScale);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::SetMulColor(const VeColor& kColor)
{
	m_spNode->SetMulColor(kColor);
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Bone::SetAddColor(const VeColor& kColor)
{
	m_spNode->SetAddColor(kColor);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeDragonBonesEntity)
{
	Module() [
		Class< VeDragonBonesEntity, Base<VeSceneNode2D> >().
			Def(ConstructorNew<const VeChar8*>()).
			Def("Play", (void (VeDragonBonesEntity::*)(const VeChar8*,VeFloat32,VeFloat32,VeFloat32,bool))&VeDragonBonesEntity::Play).
			Def("Play", (void (VeDragonBonesEntity::*)(const VeChar8*,const VeChar8*,VeFloat32,VeFloat32,VeFloat32,bool))&VeDragonBonesEntity::Play)
	];
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::Armature::Play(VeUInt32 u32Ani,
	VeFloat32 f32Priority, VeFloat32 f32Blend, VeFloat32 f32Scale,
	bool bBreak, VeVector< VePair<EventType,const VeChar8*> >& kEvent)
{
	VE_ASSERT(m_pkRes);
	if(u32Ani < m_pkRes->m_kAnimationList.Size())
	{
		VeDragonBones::Animation* pkAniRes = &(m_pkRes->m_kAnimationList[u32Ani]);
		f32Blend = f32Blend >= 0.0f ? f32Blend : pkAniRes->m_f32FadeInTime;
		AniLevel* pkLevel = &(m_kPlayAni.m_kAniMap[f32Priority]);
		bool bPlay(false);
		if((!pkLevel->m_pkCurAni) || bBreak)
		{
			pkLevel->m_pkCurAni = pkAniRes;
			pkLevel->m_f32Scale = f32Scale;
			pkLevel->m_f32Blend = f32Blend;
			pkLevel->m_f32PassTime = 0.0f;
			pkLevel->m_kFrame.Resize(pkAniRes->m_kTimelineList.Size());
			if(pkLevel->m_kFrame.Size())
			{
				VeZeroMemory(pkLevel->m_kFrame.Begin(), pkLevel->m_kFrame.Size() * sizeof(VeUInt16));
			}
			pkLevel->m_u16Frame = 0;
			pkLevel->m_u16Loop = 0;
			pkLevel->m_kAniList.Clear();
			kEvent.PushBack(VeMakePair(EVT_BEGIN, pkLevel->m_pkCurAni->m_kName));
			pkLevel->EventMain(kEvent);
			pkLevel->EventTimeline(kEvent);
			bPlay = true;
		}
		else
		{
			AniTick kTick = { pkAniRes, f32Blend, f32Scale };
			pkLevel->m_kAniList.PushBack(kTick);
		}
		if(bPlay)
		{
			VE_ASSERT(m_kPlayAni.m_kAniMap.Size());
			VeMap<VeFloat32,AniLevel>::iterator it = m_kPlayAni.m_kAniMap.Last();
			VE_ASSERT(it->m_tFirst >= f32Priority);
			if(it->m_tFirst == f32Priority)
			{
				for(VeUInt32 i(0); i < m_kBoneList.Size(); ++i)
				{
					m_kBoneList[i].Dump();
					m_kBoneList[i].SetVisibleMask(0);
				}
				for(VeUInt32 i(0); i < it->m_tSecond.m_pkCurAni->m_kTimelineList.Size(); ++i)
				{
					VeDragonBones::Timeline& kTimeline = it->m_tSecond.m_pkCurAni->m_kTimelineList[i];
					m_kBoneList[kTimeline.m_u32Bone].SetVisibleMask(VE_INFINITE);
				}
				m_kPlayAni.m_f32FadeInTime = f32Blend;
				m_kPlayAni.m_f32InvFadeInTime = 1.0f / f32Blend;
				m_kPlayAni.m_f32PassTime = 0.0f;
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeDragonBonesEntity::EventTask::DoMainThreadTask(VeBackgroundTaskQueue& kMgr)
{
	m_spEntity->ProcessEvent(m_kEvent);
}
//--------------------------------------------------------------------------
