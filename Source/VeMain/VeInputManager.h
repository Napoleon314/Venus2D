////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeInputManager.h
//  Version:     v1.00
//  Created:     21/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_INPUT_MAX_MESSAGE_NUM (32)

class VE_MAIN_API VeInputMessage : public VeMemObject
{
public:
	enum DeviceType
	{
		DT_UNASSIGNED = 0x0,
		DT_KEYBOARD = 0x1,
		DT_MOUSE = 0x2,
		DT_JOYSTICK = 0x4,
		DT_TOUCH = 0x8
	};

	enum KeyboardInputType
	{
		KIT_UNASSIGNED,
		KIT_KEY_PRESSED,
		KIT_KEY_RELEASED
	};

	enum MouseInputType
	{
		MIT_UNASSIGNED,
		MIT_LBTN_PRESSED,
		MIT_LBTN_RELEASED,
		MIT_RBTN_PRESSED,
		MIT_RBTN_RELEASED,
		MIT_MBTN_PRESSED,
		MIT_MBTN_RELEASED,
		MIT_CURSOR_MOVED,
		MIT_MOUSE_MOVED
	};

	enum JoyStickInputType
	{
		JIT_UNASSIGNED,
		JIT_SLIDER0_MOVED_X,
		JIT_SLIDER0_MOVED_Y,
		JIT_SLIDER1_MOVED_X,
		JIT_SLIDER1_MOVED_Y,
		JIT_SLIDER2_MOVED_X,
		JIT_SLIDER2_MOVED_Y,
		JIT_SLIDER3_MOVED_X,
		JIT_SLIDER3_MOVED_Y,
		JIT_POV0_CHANGED,
		JIT_POV1_CHANGED,
		JIT_POV2_CHANGED,
		JIT_POV3_CHANGED,
		JIT_BTN_PRESSED,
		JIT_BTN_RELEASED,
		JIT_AXIS_MOVED,
	};

	struct MouseCursorPos
	{
		VeUInt16 x;
		VeUInt16 y;
	};

	struct MouseMoveParam
	{
		VeInt32 x;
		VeInt32 y;
		VeInt32 z;
		VeUInt32 none;
	};

	enum TouchInputType
	{
		TIT_UNASSIGNED = 0x0,
		TIT_BEGAN = 0x1,
		TIT_MOVED = 0x2,
		TIT_ENDED = 0x4,
		TIT_CANCELLED = 0x8,
	};

	struct TouchPointParam
	{
		VeFloat32 x,y;
		VeUInt32 id;
		VeUInt32 none;
	};

	VeInputMessage();

	VeInputMessage(DeviceType eDeviceType, VeUInt32 u32InputType, VeUInt32 u32InputCode);

	VeInputMessage(DeviceType eDeviceType, VeUInt32 u32InputType, VeUInt32 u32InputCode, void* pvMessageInfo);

	VeInputMessage(DeviceType eDeviceType, VeUInt32 u32InputType, VeUInt32 u32InputCode, VeSizeT stMessageInfo);

	VE_INLINE bool operator == (const VeInputMessage& kTarget) const;

	DeviceType m_eDeviceType;
	VeUInt32 m_u32InputType;
	VeUInt32 m_u32InputCode;

	union
	{
		void* m_pvMessageInfo;
		VeSizeT m_stMessageInfo;
		MouseCursorPos m_kMouseCursorPos;
		MouseMoveParam* m_pkMouseMoveParam;
        TouchPointParam* m_pkTouchPointParam;
        VeVector<TouchPointParam>* m_pkTouchPointParams;
	};
};

class VE_MAIN_API VeInputManager : public VeSingleton<VeInputManager>
{
	VeDeclareLuaExport(VeInputManager);
public:
	typedef VeInputMessage::DeviceType DeviceType;

	typedef VeEvent<const VeInputMessage&> MessageEvent;

	typedef VeAbstractDelegate<const VeInputMessage&> MessageDelegate;

	typedef VeInputMessage::TouchPointParam TouchPointParam;

	VeInputManager();

	~VeInputManager();

	void Init();

	void Term();

	void Update();

	VE_INLINE void SetEnable(bool bEnable);

	VE_INLINE bool GetEnable();

	VE_INLINE void RegisterListener(MessageDelegate& kDelegate);

	VE_INLINE void UnregisterListener(MessageDelegate& kDelegate);

	VE_INLINE void AppendMessage(DeviceType eDeviceType, VeUInt32 u32InputType, VeUInt32 u32InputCode, void* pvMessageInfo);

	VE_INLINE void AppendMessage(DeviceType eDeviceType, VeUInt32 u32InputType, VeUInt32 u32InputCode, VeSizeT stMessageInfo);

	VE_INLINE void PopMessage();

	VE_INLINE void HookCurrentMessage();

	template <typename T>
	void GetSingle(T*& ptOut)
	{
		VE_ASSERT(sizeof(T) == sizeof(VeVector4D));
		if(m_u32VectorUse < VE_INPUT_MAX_MESSAGE_NUM)
			ptOut = (T*)&(m_akVectorPool[m_u32VectorUse++]);
		else
			ptOut = NULL;
	}

	template <typename T>
	VeVector<T>* GetList()
	{
		VE_ASSERT(sizeof(T) == sizeof(VeVector4D));
		return (VeVector<T>*)&(m_akVectorArrayPool[m_u32VectorArrayUse++]);
	}

protected:
	VE_INLINE void PerformCallBack(const VeInputMessage& kMessage);

	VE_INLINE void ProcessMessage(VeInputMessage& kMessage);

	friend class VeKeyboard;
	friend class VeMouse;
	friend class VeJoyStick;

	VeVector4D m_akVectorPool[VE_INPUT_MAX_MESSAGE_NUM];
	VeUInt32 m_u32VectorUse;
	VeVector<VeVector4D> m_akVectorArrayPool[VE_INPUT_MAX_MESSAGE_NUM];
	VeUInt32 m_u32VectorArrayUse;
	VeList<VeInputMessage> m_kMessageQueue;
	MessageEvent m_kEvent;
	bool m_bMessageHooked;
	bool m_bInputProcess;

};

#define VeDeclInputDelegate(class,name) \
	void name(const VeInputMessage&); \
	VeMemberDelegate<class,const VeInputMessage&> m_k##name

#define VeImplInputDelegate(class,name,msg) \
	void class::name(const VeInputMessage& msg)

#define g_pInputManager VeInputManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeInputManager.inl"
#endif
