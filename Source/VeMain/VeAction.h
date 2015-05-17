////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAction.h
//  Version:     v1.00
//  Created:     8/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

VeSmartPointer(VeAction);

class VE_MAIN_API VeAction : public VeRefObject
{
	VeDeclareRootRTTI(VeAction);
	VeDeclareLuaRttiExport(VeAction);
public:
	VeAction();

	virtual ~VeAction();

	VE_INLINE void SetTag(VeInt32 i32Tag);

	VE_INLINE VeInt32 GetTag();

	VE_INLINE VeFloat64 GetStartTime();

	virtual bool IsDone();

    virtual void Stop();

	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

    virtual void Update(VeFloat64 f64Time) = 0;

	virtual void SetPos(VeFloat32 f32Pos) = 0;

protected:
	friend class VeSceneNode;
	VeRefNode<VeAction*> m_kNode;
	VeSceneNode* m_pkTarget;
	VeFloat64 m_f64StartTime;
	VeInt32 m_i32Tag;

};

VeSmartPointer(VeFiniteTimeAction);

class VE_MAIN_API VeFiniteTimeAction : public VeAction
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeFiniteTimeAction);
public:
	VeFiniteTimeAction();

	VE_INLINE void SetDuration(VeFloat32 f32Duration);

	VE_INLINE VeFloat32 GetDuration();

	virtual VeFiniteTimeAction* Reverse();

	template<class T>
	T* Reverse()
	{
		return VeDynamicCast(T, Reverse());
	}

protected:
	VeFloat32 m_f32Duration;
	VeFloat32 m_f32InvDuration;

};

VeSmartPointer(VeActionInterval);

class VE_MAIN_API VeActionInterval : public VeFiniteTimeAction
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeActionInterval);
public:
	VeActionInterval();

	VE_INLINE VeFloat64 GetCurTime();

	virtual bool IsDone();

	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void Update(VeFloat64 f64Time);

	void InitWithDuration(VeFloat32 f32Duration);

protected:
	VeFloat64 m_f64CurTime;

};

VeSmartPointer(VeSequence);

class VE_MAIN_API VeSequence : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSequence);
public:
	VeSequence();

	virtual void Stop();

	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithTwoActions(VeFiniteTimeAction* pkAction0, VeFiniteTimeAction* pkAction1);

	static VeSequence* Create(VeFiniteTimeAction* pkAction, ...);

	static VeSequence* CreateWithVariableList(VeFiniteTimeAction* pkAction, va_list kArgs);

	static VeSequence* CreateWithTwoActions(VeFiniteTimeAction* pkAction0, VeFiniteTimeAction* pkAction1);

protected:
	VeFiniteTimeActionPtr m_aspActions[2];
	VeFloat32 m_f32Split;
	VeInt32 m_i32Last;

};

VeSmartPointer(VeRepeat);

class VE_MAIN_API VeRepeat : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeRepeat);
public:
	virtual bool IsDone();

	virtual void Stop();

	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithAction(VeFiniteTimeAction* pkAction, VeUInt32 u32Times);

	static VeRepeat* Create(VeFiniteTimeAction* pkAction, VeUInt32 u32Times);

protected:
	VeUInt32 m_u32Times;
	VeUInt32 m_u32Total;
	VeFloat32 m_f32Next;
	VeFiniteTimeActionPtr m_spInnerAction;
	bool m_bActionInstant;

};

VeSmartPointer(VeRepeatForever);

class VE_MAIN_API VeRepeatForever : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeRepeatForever);
public:
	virtual bool IsDone();

	virtual void Stop();

	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void Update(VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos) {}

	virtual VeFiniteTimeAction* Reverse();

	void InitWithAction(VeFiniteTimeAction* pkAction);

	static VeRepeatForever* Create(VeFiniteTimeAction* pkAction);

protected:
	VeFiniteTimeActionPtr m_spInnerAction;

};

VeSmartPointer(VeSpawn);

class VE_MAIN_API VeSpawn : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSpawn);
public:
	virtual void Stop();

	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithTwoActions(VeFiniteTimeAction* pkAction0, VeFiniteTimeAction* pkAction1);

	static VeSpawn* Create(VeFiniteTimeAction* pkAction, ...);
    
	static VeSpawn* CreateWithVariableList(VeFiniteTimeAction* pkAction, va_list kArgs);

	static VeSpawn* CreateWithTwoActions(VeFiniteTimeAction* pkAction0, VeFiniteTimeAction* pkAction1);

protected:
	VeFiniteTimeActionPtr m_spFirst;
	VeFiniteTimeActionPtr m_spSecond;

};

VeSmartPointer(VeRotateTo2D);

class VE_MAIN_API VeRotateTo2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeRotateTo2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32DstAngle);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32DstAngle, VeTweenEasing::Type eType);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType);

	static VeRotateTo2D* Create(VeFloat32 f32Duration, VeFloat32 f32DstAngle);

	static VeRotateTo2D* Create(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY);

	static VeRotateTo2D* Create(VeFloat32 f32Duration, VeFloat32 f32DstAngle, VeTweenEasing::Type eType);

	static VeRotateTo2D* Create(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType);

protected:
	VeVector2D m_kDstSkew;
	VeVector2D m_kStartSkew;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeRotateBy2D);

class VE_MAIN_API VeRotateBy2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeRotateBy2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32Angle);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32Angle, VeTweenEasing::Type eType);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType);

	static VeRotateBy2D* Create(VeFloat32 f32Duration, VeFloat32 f32Angle);

	static VeRotateBy2D* Create(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY);

	static VeRotateBy2D* Create(VeFloat32 f32Duration, VeFloat32 f32Angle, VeTweenEasing::Type eType);

	static VeRotateBy2D* Create(VeFloat32 f32Duration, VeFloat32 f32SkewX, VeFloat32 f32SkewY, VeTweenEasing::Type eType);

protected:
	VeVector2D m_kAddSkew;
	VeVector2D m_kStartSkew;
	VeVector2D m_kPreSkew;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeMoveTo2D);

class VE_MAIN_API VeMoveTo2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeMoveTo2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y, VeTweenEasing::Type eType);

	static VeMoveTo2D* Create(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y);

	static VeMoveTo2D* Create(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y, VeTweenEasing::Type eType);

protected:
	VeVector2D m_kDstPos;
	VeVector2D m_kStartPos;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeMoveBy2D);

class VE_MAIN_API VeMoveBy2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeMoveBy2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y, VeTweenEasing::Type eType);

	static VeMoveBy2D* Create(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y);

	static VeMoveBy2D* Create(VeFloat32 f32Duration, VeFloat32 x, VeFloat32 y, VeTweenEasing::Type eType);

protected:
	VeVector2D m_kAddPos;
	VeVector2D m_kStartPos;
	VeVector2D m_kPrePos;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeScaleTo2D);

class VE_MAIN_API VeScaleTo2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeScaleTo2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32Scale);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32Scale, VeTweenEasing::Type eType);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy, VeTweenEasing::Type eType);

	static VeScaleTo2D* Create(VeFloat32 f32Duration, VeFloat32 f32Scale);

	static VeScaleTo2D* Create(VeFloat32 f32Duration, VeFloat32 f32Scale, VeTweenEasing::Type eType);

	static VeScaleTo2D* Create(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy);

	static VeScaleTo2D* Create(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy, VeTweenEasing::Type eType);

protected:
	VeVector2D m_kDstScale;
	VeVector2D m_kStartScale;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeScaleBy2D);

class VE_MAIN_API VeScaleBy2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeScaleBy2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32Scale);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 f32Scale, VeTweenEasing::Type eType);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy);

	void InitWithDuration(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy, VeTweenEasing::Type eType);

	static VeScaleBy2D* Create(VeFloat32 f32Duration, VeFloat32 f32Scale);

	static VeScaleBy2D* Create(VeFloat32 f32Duration, VeFloat32 f32Scale, VeTweenEasing::Type eType);

	static VeScaleBy2D* Create(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy);

	static VeScaleBy2D* Create(VeFloat32 f32Duration, VeFloat32 sx, VeFloat32 sy, VeTweenEasing::Type eType);

protected:
	VeVector2D m_kAddScale;
	VeVector2D m_kStartScale;
	VeVector2D m_kPreScale;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeMulColorTo2D);

class VE_MAIN_API VeMulColorTo2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeMulColorTo2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor);

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

	static VeMulColorTo2D* Create(VeFloat32 f32Duration, const VeColor& kColor);

	static VeMulColorTo2D* Create(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

protected:
	VeColor m_kDstColor;
	VeColor m_kStartColor;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeMulColorBy2D);

class VE_MAIN_API VeMulColorBy2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeMulColorBy2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor);

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

	static VeMulColorBy2D* Create(VeFloat32 f32Duration, const VeColor& kColor);

	static VeMulColorBy2D* Create(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

protected:
	VeColor m_kAddColor;
	VeColor m_kStartColor;
	VeColor m_kPreColor;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeAddColorTo2D);

class VE_MAIN_API VeAddColorTo2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeAddColorTo2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor);

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

	static VeAddColorTo2D* Create(VeFloat32 f32Duration, const VeColor& kColor);

	static VeAddColorTo2D* Create(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

protected:
	VeColor m_kDstColor;
	VeColor m_kStartColor;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeAddColorBy2D);

class VE_MAIN_API VeAddColorBy2D : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeAddColorBy2D);
public:
	virtual void Start(VeSceneNode* pkTarget, VeFloat64 f64Time);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor);

	void InitWithDuration(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

	static VeAddColorBy2D* Create(VeFloat32 f32Duration, const VeColor& kColor);

	static VeAddColorBy2D* Create(VeFloat32 f32Duration, const VeColor& kColor, VeTweenEasing::Type eType);

protected:
	VeColor m_kAddColor;
	VeColor m_kStartColor;
	VeColor m_kPreColor;
	VeTweenEasing::Type m_eType;

};

VeSmartPointer(VeDelayTime);

class VE_MAIN_API VeDelayTime : public VeActionInterval
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeDelayTime);
public:
	virtual void Update(VeFloat64 f64Time) {}

	virtual void SetPos(VeFloat32 f32Pos) {}

	virtual VeFiniteTimeAction* Reverse();

	static VeDelayTime* Create(VeFloat32 f32Duration);

};

VeSmartPointer(VeActionInstant);

class VE_MAIN_API VeActionInstant : public VeFiniteTimeAction
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeActionInstant);
public:
	virtual bool IsDone();

	virtual void Update(VeFloat64 f64Time);

};

VeSmartPointer(VeChangeVisibleMask);

class VE_MAIN_API VeChangeVisibleMask : public VeActionInstant
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeChangeVisibleMask);
public:
	VeChangeVisibleMask(VeUInt32 u32Mask);

	virtual void SetPos(VeFloat32 f32Pos);

	virtual VeFiniteTimeAction* Reverse();

	static VeChangeVisibleMask* Create(VeUInt32 u32Mask);

protected:
	VeUInt32 m_u32VisibleMask;

};

VeSmartPointer(VeToggleVisibility);

class VE_MAIN_API VeToggleVisibility : public VeActionInstant
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeToggleVisibility);
public:
	virtual void SetPos(VeFloat32 f32Pos);

	static VeToggleVisibility* Create();

};

VeSmartPointer(VeActionCall);

class VE_MAIN_API VeActionCall : public VeActionInstant
{
	VeDeclareRTTI;
public:
	typedef VeAbstractDelegate<const VeActionCallPtr&> Delegate;

	typedef VeEvent<const VeActionCallPtr&> Event;

	VeActionCall();

	virtual void SetPos(VeFloat32 f32Pos);

	static VeActionCall* Create()
	{
		VeActionCall* pkAction = VE_NEW VeActionCall;
		/*pkAction->m_kEvent.AddDelegate(kDelegate);*/
		return pkAction;
	}

	static VeActionCall* Create(Delegate& kDelegate);

protected:
	friend class VeSceneManager;
	VeRefNode<VeActionCall*> m_kNode;
	Event m_kEvent;

};

#define VeDeclActDelegate(class,name) \
	void name(const VeActionCallPtr&); \
	VeMemberDelegate<class,const VeActionCallPtr&> m_k##name

#define VeImplActDelegate(class,name,act) \
	void class::name(const VeActionCallPtr& act)

#ifndef VE_NO_INLINE
#	include "VeAction.inl"
#endif
