////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeDragonBones.h
//  Version:     v1.00
//  Created:     17/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeDragonBones : public VeResource
{
	VeDeclareRTTI;
public:
	enum DisplayType
	{
		DIS_IMAGE,
		DIS_ARMATURE,
		DIS_MAX
	};

	struct Transform
	{
		VeVector2D m_kPos;
		VeVector2D m_kSkew;
		VeVector2D m_kScale;
	};

	struct Bone
	{
		VeFixedString m_kName;
		Transform m_kTransform;
	};

	struct Display
	{
		DisplayType m_eType;
		VeFixedString m_kName;
		Transform m_kTransform;
	};

	struct Slot
	{
		VeFixedString m_kName;
		VeUInt32 m_u32Bone;
		VeFloat32 m_f32ZOrder;
		VeVector<Display> m_kDisplayList;
	};

	struct Skin
	{
		VeFixedString m_kName;
		VeVector<Slot> m_kSlotList;
	};

	struct FrameAnimation
	{
		VeFloat32 m_f32Until;
		VeString m_kEvent;
	};

	struct Frame
	{
		VeUInt16 m_u16Display;
		VeUInt16 m_u16Hide;
		VeFloat32 m_f32ZOrder;
		VeTweenEasing::Type m_eTweenEasing;
		VeFloat32 m_f32TweenRotate;
		VeFloat32 m_f32Until;
		VeString m_kEvent;
		Transform m_kTransform;
		VeColor m_kMulColor;
		VeColor m_kAddColor;
	};

	struct Timeline
	{
		VeUInt32 m_u32Bone;
		VeFloat32 m_f32Scale;
		VeFloat32 m_f32Offset;
		VeVector<Frame> m_kFrameList;
	};

	struct Animation
	{
		VeFixedString m_kName;
		VeFloat32 m_f32FadeInTime;
		VeFloat32 m_f32Duration;
		VeFloat32 m_f32Scale;
		VeUInt32 m_u32Loop;
		VeTweenEasing::Type m_eTweenEasing;
		VeVector<FrameAnimation> m_kFrameList;
		VeVector<Timeline> m_kTimelineList;
	};

	struct Armature
	{
		VeFixedString m_kName;
		VeVector<Bone> m_kBoneList;
		VeStringMap<VeUInt32> m_kBoneMap;
		VeVector<Skin> m_kSkinList;
		VeStringMap<VeUInt32> m_kSkinMap;
		VeVector<Animation> m_kAnimationList;
		VeStringMap<VeUInt32> m_kAnimationMap;
	};

	VeDragonBones(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeDragonBones();

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

	static void SetTexScale(VeFloat32 f32Scale);

	static VeFloat32 GetTexScale();

protected:
	friend class VeDragonBonesAnimation;
	friend class VeDragonBonesEntity;

	virtual void UnloadImpl();

	virtual bool HasProcess();

	virtual void LoadProcess(const VeMemoryIStreamPtr& spStream);

	void ParseArmature(Armature& kOut, VeXMLElement* pkArmature);

	void ParseBone(Bone& kOut, VeXMLElement* pkBone);

	void ParseTransform(Transform& kOut, VeXMLElement* pkTransform, VeFloat32 f32Rate);

	void ParseSkin(Skin& kOut, VeXMLElement* pkSkin, const Armature& kArmature);

	void ParseSlot(Slot& kOut, VeXMLElement* pkSlot, const Armature& kArmature);

	void ParseDisplay(Display&kOut, VeXMLElement* pkDisplay);

	void ParseAnimation(Animation& kOut, VeXMLElement* pkAni, const Armature& kArmature);

	void ParseFrameAnimation(VeFloat32& f32PassTime, FrameAnimation& kOut, VeXMLElement* pkFrame);

	void ParseTimeline(Timeline& kOut, VeXMLElement* pkTimeline, const Armature& kArmature, VeTweenEasing::Type eEasing);

	void ParseFrame(VeFloat32& f32PassTime, Frame& kOut, VeXMLElement* pkFrame, VeTweenEasing::Type eEasing);

	void ParseColor(VeColor& kMulOut, VeColor& kAddOut, VeXMLElement* pkColor);

	VeFloat32 m_f32InvFrameRate;
	VeVector<Armature> m_kArmatureList;
	VeStringMap<VeUInt32> m_kArmatureMap;

	static VeFloat32 ms_f32TexScale;

};

VeSmartPointer(VeDragonBones);

#define VeGetDragonBones(name,group) VeDynamicCast(VeDragonBones,VeGetResource(VeResource::DRAGON_BONES,name,group))

#define VeLoadDragonBones(name,group,async) VeDynamicCast(VeDragonBones,VeLoadResource(VeResource::DRAGON_BONES,name,group,async))

#define VeLoadDragonBonesSync(name,group) VeLoadDragonBones(name,group,false)

#define VeLoadDragonBonesAsync(name,group) VeLoadDragonBones(name,group,true)

VeSmartPointer(VeDragonBonesEntity);

class VE_MAIN_API VeDragonBonesEntity : public VeSceneNode2D
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeDragonBonesEntity);
public:
	enum EventType
	{
		EVT_BEGIN,
		EVT_END,
		EVT_END_LOOP,
		EVT_KEY,
		EVT_MAX
	};

	typedef VeEvent<const VeDragonBonesEntityPtr&,EventType,const VeChar8*> Event;

	typedef VeAbstractDelegate<const VeDragonBonesEntityPtr&,EventType,const VeChar8*> Delegate;

	struct Armature;

	struct Display
	{
		Display() : m_pkArmature(NULL) {}
		Armature* m_pkArmature;
		VeSceneNode2DPtr m_spNode;
	};

	struct Bone
	{
		VeVector2D m_kPos;
		VeVector2D m_kSkew;
		VeVector2D m_kScale;
		VeColor m_kMul;
		VeColor m_kAdd;
		VeUInt32 m_u32Display;
		VeSceneNode2DPtr m_spNode;
		VeVector<Display> m_kDisplayList;

		void SetVisibleMask(VeUInt32 u32Mask);

		void SetZOrder(VeFloat32 f32ZOrder);

		void Set(VeUInt32 u32Display, VeVector< VePair<EventType,const VeChar8*> >& kEvents);

		void Dump();

		void SetPosition(const VeVector2D& kPos);

		void SetSkew(const VeVector2D& kSkew);

		void SetScale(const VeVector2D& kScale);

		void SetMulColor(const VeColor& kColor);

		void SetAddColor(const VeColor& kColor);
	};

	struct AniTick
	{
		VeDragonBones::Animation* m_pkAniRes;
		VeFloat32 m_f32Blend;
		VeFloat32 m_f32Scale;
	};

	struct PlayAni;

	struct AniLevel
	{
		AniLevel() : m_pkCurAni(NULL), m_f32Blend(0), m_f32Scale(0), m_f32PassTime(0), m_u16Frame(0), m_u16Loop(0) {}

		AniLevel(VeFloat32 f32Pass) : m_pkCurAni(NULL), m_f32Blend(0), m_f32Scale(0), m_f32PassTime(f32Pass), m_u16Frame(0), m_u16Loop(0) {}

		void EventAfterMain(VeVector< VePair<EventType,const VeChar8*> >& kEvents);

		void EventAfterTimeline(VeVector< VePair<EventType,const VeChar8*> >& kEvents);

		void EventMain(VeVector< VePair<EventType,const VeChar8*> >& kEvents);

		void EventTimeline(VeVector< VePair<EventType,const VeChar8*> >& kEvents);
		
		void Update(VeFloat32 f32Delta, PlayAni& kAni, VeVector<Bone>& kBones, VeVector< VePair<EventType,const VeChar8*> >& kEvents);

		void Update(VeFloat32 f32Delta, VeVector< VePair<EventType,const VeChar8*> >& kEvents);

		VeDragonBones::Animation* m_pkCurAni;
		VeFloat32 m_f32Blend;
		VeFloat32 m_f32Scale;
		VeFloat32 m_f32PassTime;
		VeVector<VeUInt16> m_kFrame;
		VeUInt16 m_u16Frame;
		VeUInt16 m_u16Loop;
		VeList<AniTick> m_kAniList;
	};

	struct PlayAni
	{
		PlayAni() : m_f32FadeInTime(0), m_f32PassTime(0) {}

		void Update(VeFloat32 f32Delta, VeVector<Bone>& kBones, VeVector< VePair<EventType,const VeChar8*> >& kEvents);

		VeFloat32 m_f32FadeInTime;
		VeFloat32 m_f32InvFadeInTime;
		VeFloat32 m_f32PassTime;
		VeMap<VeFloat32,AniLevel> m_kAniMap;
	};

	struct Armature : public VeRefObject
	{
		Armature() : m_pkRes(NULL), m_bAuto(false) {}

		void Play(VeUInt32 u32Ani, VeFloat32 f32Priority, VeFloat32 f32Blend, VeFloat32 f32Scale, bool bBreak, VeVector< VePair<EventType,const VeChar8*> >& kEvent);

		VeString m_kName;
		VeDragonBones::Armature* m_pkRes;
		VeSceneNode2DPtr m_spNode;
		VeVector<Bone> m_kBoneList;
		PlayAni m_kPlayAni;
		bool m_bAuto;
	};

	typedef VePointer<Armature> ArmaturePtr;

	class EventTask : public VeBackgroundTask
	{
	public:
		EventTask() {}

		virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

		VeVector< VePair<EventType,const VeChar8*> > m_kEvent;
		VeDragonBonesEntityPtr m_spEntity;
	};

	VeDragonBonesEntity(const VeChar8* pcName);

	VeDragonBonesEntity(const VeDragonBonesPtr& spRes);

	virtual ~VeDragonBonesEntity();

	VE_INLINE VeUInt32 GetArmatureIndex(const VeChar8* pcName);

	VE_INLINE VeUInt32 GetArmatureSize();

	VE_INLINE VeUInt32 GetAnimationIndex(const VeChar8* pcName, VeUInt32 u32Armature = 0);

	VE_INLINE VeUInt32 GetAnimationSize(VeUInt32 u32Armature = 0);

	VE_INLINE void RegisterListener(Delegate& kDelegate);

	VE_INLINE void UnregisterListener(Delegate& kDelegate);

	void Play(VeUInt32 u32Animation, VeUInt32 u32Armature = 0, VeFloat32 f32Priority = 0.0f, VeFloat32 f32Blend = -1.0f, VeFloat32 f32Scale = 1.0f, bool bBreak = false);

	void Play(const VeChar8* pcAnimation, VeFloat32 f32Priority = 0.0f, VeFloat32 f32Blend = -1.0f, VeFloat32 f32Scale = 1.0f, bool bBreak = false);

	void Play(const VeChar8* pcArmature, const VeChar8* pcAnimation, VeFloat32 f32Priority = 0.0f, VeFloat32 f32Blend = -1.0f, VeFloat32 f32Scale = 1.0f, bool bBreak = false);

	void Stop(VeUInt32 u32Armature);

	void Stop();

	virtual void Visit(VeRenderQueue& kQueue);

	VeSceneNode2DPtr GetBone(const VeChar8* pcBone, VeUInt32 u32Armature = 0);

	const VeTransform2D* GetBoneTransform(const VeChar8* pcBone, VeUInt32 u32Armature = 0);

protected:
	void Init();

	void InitArmature(Armature& kOut, VeDragonBones::Armature& kRes);

	void UseSkin(Armature& kOut, const VeDragonBones::Armature& kRes, VeUInt32 u32Skin);

	void Update(VeFloat32 f32Delta);

	void ProcessEvent(VeVector< VePair<EventType,const VeChar8*> >& kEventList);

	void ProcessEvent(VePair<EventType,const VeChar8*>& kEvent);

	VeDragonBonesPtr m_spResource;
	VeStringMap<VeUInt32> m_kArmatureMap;
	VeVector<ArmaturePtr> m_kArmatureList;
	Event m_kEvent;

};

#define VeDeclAniEntityDelegate(class,name) \
	void name(const VeDragonBonesEntityPtr&,VeDragonBonesEntity::EventType,const VeChar8*); \
	VeMemberDelegate<class,const VeDragonBonesEntityPtr&,VeDragonBonesEntity::EventType,const VeChar8*> m_k##name

#define VeImplAniEntityDelegate(class,name,ptr,evt,info) \
	void class::name(const VeDragonBonesEntityPtr& ptr,VeDragonBonesEntity::EventType evt,const VeChar8* info)

#ifndef VE_NO_INLINE
#	include "VeDragonBones.inl"
#endif
