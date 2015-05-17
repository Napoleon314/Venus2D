////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIWidget.h
//  Version:     v1.00
//  Created:     8/2/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

VeSmartPointer(VeUIWidget);
VeSmartPointer(VeUILayout);

class VE_MAIN_API VeUIWidget : public VeSceneNode2D
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIWidget);
public:
	enum EventType
	{
		EVT_MOUSE_PRESSED,
		EVT_MOUSE_RELEASED,
		EVT_MOUSE_MOVE,

		EVT_TOUCH_BEGAN,
		EVT_TOUCH_MOVED,
		EVT_TOUCH_ENDED,
		EVT_TOUCH_CANCELLED,

		EVT_RELEASE_FOCUS,

		EVT_ENABLE,
		EVT_DISABLE,
		EVT_SHOW,
		EVT_HIDE,
		EVT_ACTIVE,
		EVT_INACTIVE,
		EVT_CHECK,
		EVT_UNCHECK,

		EVT_CLICK,
		EVT_PRESSED,
		EVT_CHANGE_INDEX,
		EVT_MOVE,
		EVT_STOP,

		EVT_VALUE_CHANGE,
		EVT_VALUE_CHANGED,

		EVT_MASK = 0xFFFF00FF,
		EVT_USER = 0x10000
	};
	VeLuaClassEnumDef(EventType);

	enum NodeType
	{
		NODE_TEX,
		NODE_FRAME,
		NODE_BAR,
		NODE_TEXT,
		NODE_MAX
	};
	VeLuaClassEnumDef(NodeType);

	enum State
	{
		STATE_ENABLE,
		STATE_VISIBLE,
		STATE_ACTIVE,
		STATE_INPUT,
		STATE_CLIP,
		STATE_CHECKED,
		STATE_EAT_EVENT,
		STATE_SHOW,
		STATE_USER = 0x10
	};

	class Repainter : public VeRefObject
	{
	public:
		virtual void Notify() = 0;

	};

	typedef VePointer<Repainter> RepainterPtr;

	typedef VeEvent<const VeUIWidgetPtr&,VeUInt32> Event;

	typedef VeAbstractDelegate<const VeUIWidgetPtr&,VeUInt32> Delegate;

	typedef VeMemberDelegate<VeUIWidget,const VeUIWidgetPtr&,VeUInt32> MemberDelegate;

	VeUIWidget();

	virtual ~VeUIWidget();

	VE_INLINE const VeChar8* GetName();

	VE_INLINE VeString GetFullName();

	VE_INLINE bool GetEnable();

	VE_INLINE bool GetVisible();

	VE_INLINE bool GetActive();

	VE_INLINE bool GetProcessInput();

	VE_INLINE bool GetClipByRange();

	VE_INLINE bool GetChecked();

	VE_INLINE bool GetEatEvent();

	VE_INLINE bool GetShow();

	VE_INLINE bool GetDisplay();

	VE_INLINE bool IsRoot();

	VE_INLINE VeUIWidget* GetParent();

	VE_INLINE void RegisterListener(Delegate& kDelegate);

	VE_INLINE void UnregisterListener(Delegate& kDelegate);

	VE_INLINE VeUInt32 GetCurUpdateRangeFrame();

	VE_INLINE const VeBoundingBox2D& GetRange();

	VE_INLINE const VeBoundingBox2D& GetDerivedRange();

	VE_INLINE VeUInt32 GetIndex();

	VE_INLINE void SetTag(VeInt32 i32Tag);

	VE_INLINE VeInt32 GetTag();

	virtual void SetEnable(bool bEnable);

	virtual void SetVisible(bool bVisible);

	virtual void SetActive(bool bActive);

	virtual void SetProcessInput(bool bProcess);

	virtual void SetClipByRange(bool bClip);

	virtual void SetChecked(bool bChecked);

	virtual void SetEatEvent(bool bEat);

	virtual bool IsIn(const VeVector2D& kPos);

	virtual VeUIWidget* PressEvent(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual VeUIWidget* ReleaseEvent(VeUIWidgetPtr& spHold, VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual VeUIWidget* CurMoveEvent(VeUIWidgetPtr& spCursor, VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual VeUIWidget* PressEvent(VeUInt32 u32Time, VeKeyboard::InputKey eKey);

	virtual bool OnPress(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) { return true; }

	virtual bool OnProcessCurMove(VeUInt32 u32Time, const VeVector2D& kPos) { return true; }

	virtual void OnRelease(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) {}

	virtual void OnCancel(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) {}

	virtual void OnCurMove(VeUInt32 u32Time, const VeVector2D& kPos) {}

	virtual void OnDragEnter(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) {}

	virtual void OnDragLeave(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) {}

	virtual void OnDragMove(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) {}

	virtual void OnHoldDragMove(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) {}

	virtual void OnDrop(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) {}

	virtual bool OnPress(VeUInt32 u32Time, VeKeyboard::InputKey eKey) { return false; }

	virtual void OnRelease(VeUInt32 u32Time, VeKeyboard::InputKey eKey) {}

	virtual void OnCancel(VeUInt32 u32Time, VeKeyboard::InputKey eKey) {}

	virtual void UpdateRange(VeFloat32 x, VeFloat32 y, VeFloat32 w, VeFloat32 h);

	virtual void UpdateState() {}

	virtual void UpdateBounding();

	virtual void UpdateChildren();

	virtual void Visit(VeRenderQueue& kQueue);

	virtual void OnShow();

	virtual void OnHide();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	void SetRepainter(const RepainterPtr& spRepainter);

	static VeUIWidgetPtr Create();

	static void Parse(const VeSceneNode2DPtr& spNode, VeXMLElement* pkElement);

protected:
	friend class VeUIManager;

	void GetChildrenWidget(lua_State* pkState);

	void EventCallback(const VeUIWidgetPtr& spWidget, VeUInt32 u32Event);

	virtual void OnEvent(const VeUIWidgetPtr& spWidget, VeUInt32 u32Event);

	void NotifyRepaint();

	static VeUInt32 GetCurUpdateRangeFrame(const VeUIWidget& kWidget);

	VeRefNode<VeUIWidget*> m_kNode;
	VeFixedString m_kName;
	VeUILayout* m_pkParent;
	VeUInt32 m_u32Flags;
	VeUInt32 m_u32CurUpdateRangeFrame;
	VeBoundingBox2D m_kRange;
	VeBoundingBox2D m_kDerivedRange;
	VeUInt32 m_u32Index;
	VeUInt32 m_u32MaxIndex;
	VeInt32 m_i32Tag;
	Event m_kEvent;
	MemberDelegate m_kSelfDelegate;
	VeStringMap< VePair<VeString,VeInt32> > m_kLuaEventMap;
	RepainterPtr m_spRepainter;

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_MAIN_API, VeUIWidget, EventType);
	VeLuaClassEnumFuncDef(VE_MAIN_API, VeUIWidget, NodeType);
}

#define VeDeclWidgetDelegate(class,name) \
	void name(const VeUIWidgetPtr&,VeUInt32); \
	VeMemberDelegate<class,const VeUIWidgetPtr&,VeUInt32> m_k##name

#define VeImplWidgetDelegate(class,name,ptr,evt) \
	void class::name(const VeUIWidgetPtr& ptr, VeUInt32 evt)

class VE_MAIN_API VeUILayout : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUILayout);
public:
	VeUILayout();

	virtual ~VeUILayout();

	VE_INLINE void SetModal(bool bEnable);

	VE_INLINE bool IsModal();

	virtual bool Process(const VeInputMessage& kMessage);

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	virtual void OnShow();

	virtual void OnHide();

	void UpdateActive(const VeUIWidgetPtr& spWidget);

	static VeUIWidgetPtr Create();

protected:
	friend class VeUIManager;

	VeRefList<VeUIWidget*> m_kChildren;
	VeMap<VeUInt32,VeUIWidgetPtr> m_kHoldMap;
	VeMap<VeUInt32,VeUIWidgetPtr> m_kCursorMap;
	VeMap<VeUInt32,VeUIWidgetPtr> m_kKeyHoldMap;
	VeUIWidgetPtr m_spActive;
	bool m_bModal;

};

VeSmartPointer(VeUILayout);

class VE_MAIN_API VeUISquare : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUISquare);
public:
	VeUISquare();

	virtual ~VeUISquare();

	VE_INLINE VeSquare* GetSquare();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

protected:
	VeSquarePtr m_spSquare;

};

class VE_MAIN_API VeUIImage : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIImage);
public:
	VeUIImage();

	virtual ~VeUIImage();

	VE_INLINE VeSprite2D* GetImage();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

protected:
	VeSprite2DPtr m_spImage;

};

VeSmartPointer(VeUIImage);

class VE_MAIN_API VeUIDragonBones : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIDragonBones);
public:
	VeUIDragonBones();

	virtual ~VeUIDragonBones();

	VE_INLINE VeDragonBonesEntity* GetEntity();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

protected:
	VeDragonBonesEntityPtr m_spEntity;

};

VeSmartPointer(VeUIDragonBones);

class VE_MAIN_API VeUIAlertFrame : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIAlertFrame);
public:
	VeUIAlertFrame();

	virtual ~VeUIAlertFrame();

	VE_INLINE VeUIFrame* GetEntity();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

protected:
	VeUIFramePtr m_spFrame;

};

class VE_MAIN_API VeUIAlertBarHoriz : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIAlertBarHoriz);
public:
	VeUIAlertBarHoriz();

	virtual ~VeUIAlertBarHoriz();

	VE_INLINE VeUIBarHoriz* GetEntity();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

protected:
	VeUIBarHorizPtr m_spBar;

};

VeSmartPointer(VeSimpleText);

class VE_MAIN_API VeUITextLabel : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUITextLabel);
public:
	VeUITextLabel();

	virtual ~VeUITextLabel();

	VE_INLINE VeSimpleText* GetText();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	void SetText(const VeChar8* pcText);

	void SetTextTrans(const VeChar8* pcText);

	static VeUIWidgetPtr Create();

protected:
	VeSimpleTextPtr m_spText;

};

VeSmartPointer(VeUITextLabel);

class VE_MAIN_API VeUIButton : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIButton);
public:
	enum Display
	{
		DIS_NORMAL,
		DIS_PRESSED,
		DIS_DISABLED,
		DIS_NUM
	};

	VeUIButton();

	virtual ~VeUIButton();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

	virtual bool OnPress(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnRelease(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnCancel(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnHoldDragMove(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

protected:
	void SetDisplay(Display eDisplay);

	Display m_eDisplay;
	VeSceneNode2DPtr m_aspNode[DIS_NUM];

};

class VE_MAIN_API VeUICheckButton : public VeUIButton
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUICheckButton);
public:
	VeUICheckButton();

	virtual ~VeUICheckButton();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

	virtual bool OnPress(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnRelease(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnCancel(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnHoldDragMove(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnEvent(const VeUIWidgetPtr& spWidget, VeUInt32 u32Event);

protected:
	bool m_bEnableCancel;

};

class VE_MAIN_API VeUIRadioArea : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIRadioArea);
public:
	typedef VeMemberDelegate<VeUIRadioArea,const VeUIWidgetPtr&,VeUInt32> Delegate;

	VeUIRadioArea();

	virtual ~VeUIRadioArea();

	VE_INLINE VeUIWidget* GetCheckedWidget();

	VE_INLINE VeInt32 GetCheckedIndex();

	virtual void UpdateChildren();

	virtual bool OnPress(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos) { return false; }

	virtual bool OnProcessCurMove(VeUInt32 u32Time, const VeVector2D& kPos) { return false; }

	static VeUIWidgetPtr Create();

protected:
	void OnEvent(const VeUIWidgetPtr& spWidget, VeUInt32 u32Event);

	VeVector<Delegate> m_kDelegateArray;
	VeUIWidgetPtr m_spChecked;

};

VeSmartPointer(VeUIRadioArea);

class VE_MAIN_API VeUIPageView : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIPageView);
public:
	VeUIPageView();

	virtual ~VeUIPageView();

	VE_INLINE VeInt32 GetPageIndex();

	void SetPageIndex(VeInt32 i32Index);

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	static VeUIWidgetPtr Create();

protected:
	VeInt32 m_i32PageIndex;
	VeVector<VeUIWidgetPtr> m_kPageArray;

};

class VE_MAIN_API VeUITextField : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUITextField);
public:
	typedef VeMemberDelegate<VeUITextField,const VeChar16*,VeUInt32> Delegate;

	VeUITextField();

	virtual ~VeUITextField();

	VE_INLINE void SetText(const VeChar8* pcText);

	VE_INLINE const VeChar8* GetText();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	virtual bool OnPress(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnRelease(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnCancel(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual bool OnPress(VeUInt32 u32Time, VeKeyboard::InputKey eKey);

	virtual void OnRelease(VeUInt32 u32Time, VeKeyboard::InputKey eKey);

	virtual void OnCancel(VeUInt32 u32Time, VeKeyboard::InputKey eKey);

	virtual void UpdateState();

	static VeUIWidgetPtr Create();

protected:
	void SetEdit(bool bEdit);

	void CacheString();

	void RefreshString(bool bUpdate = true);

	VeFloat32 GetCursorOffset();

	void UpdateText();

	void OnInsertText(const VeChar16* pcText, VeUInt32 u32Num);

	VeDeclTimeDelegate(VeUITextField, OnMoveEvent);
	VeTimeEventPtr m_spTimeEvent;
	VeInt32 m_i32MoveStep;
	Delegate m_kDelegate;
	VeSceneNode2DPtr m_spSquare;
	VeBoundingBox2D m_kCursorRect;
	VeColor m_kCursorColor;
	VeSimpleTextPtr m_spText;
	VeColor m_kColor;
	VeColor m_kEmptyColor;
	VeFloat32 m_f32Bias;
	VeFloat32 m_f32Offset;
	VeColor m_kShadowColor;
	VeColor m_kEmptyShadowColor;
	VeFloat32 m_f32ShadowBias;
	VeVector2D m_kShadowOffset;
	VeUInt32 m_u32MaxLen;
	VeString m_kEmpty;
	VeString m_kContent;
	VeVector<VeChar16> m_kContentCache;
	VeUInt32 m_u32CurserPoint;
	bool m_bEdit;

};

#ifndef VE_NO_INLINE
#	include "VeUIWidget.inl"
#endif
