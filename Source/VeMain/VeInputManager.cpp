////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeInputManager.cpp
//  Version:     v1.00
//  Created:     21/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeInputManager.inl"
#endif

//--------------------------------------------------------------------------
VeInputMessage::VeInputMessage() : m_eDeviceType(DT_UNASSIGNED)
	, m_u32InputType(0), m_u32InputCode(0), m_pvMessageInfo(NULL)
{

}
//--------------------------------------------------------------------------
VeInputMessage::VeInputMessage(DeviceType eDeviceType,
	VeUInt32 u32InputType, VeUInt32 u32InputCode)
	: m_eDeviceType(eDeviceType), m_u32InputType(u32InputType)
	, m_u32InputCode(u32InputCode), m_pvMessageInfo(NULL)
{

}
//--------------------------------------------------------------------------
VeInputMessage::VeInputMessage(DeviceType eDeviceType,
	VeUInt32 u32InputType, VeUInt32 u32InputCode, void* pvMessageInfo)
	: m_eDeviceType(eDeviceType), m_u32InputType(u32InputType)
	, m_u32InputCode(u32InputCode), m_pvMessageInfo(pvMessageInfo)
{

}
//--------------------------------------------------------------------------
VeInputMessage::VeInputMessage(DeviceType eDeviceType,
	VeUInt32 u32InputType, VeUInt32 u32InputCode, VeSizeT stMessageInfo)
	: m_eDeviceType(eDeviceType), m_u32InputType(u32InputType)
	, m_u32InputCode(u32InputCode), m_stMessageInfo(stMessageInfo)
{

}
//--------------------------------------------------------------------------
VeInputManager::VeInputManager()
	: m_u32VectorUse(0)
	, m_u32VectorArrayUse(0)
	, m_bMessageHooked(false)
	, m_bInputProcess(true)
{
	VE_NEW VeKeyboard();
	VE_NEW VeMouse();
	//VE_NEW VeJoyStick();
}
//--------------------------------------------------------------------------
VeInputManager::~VeInputManager()
{
	//VeJoyStick::Destory();
	VeMouse::Destory();
	VeKeyboard::Destory();
}
//--------------------------------------------------------------------------
void VeInputManager::Init()
{

}
//--------------------------------------------------------------------------
void VeInputManager::Term()
{

}
//--------------------------------------------------------------------------
void VeInputManager::Update()
{
	if(m_bInputProcess)
	{
		while(m_kMessageQueue.Size())
		{
			ProcessMessage(m_kMessageQueue.Front());
			PopMessage();
		}
	}
	else
	{
		m_kMessageQueue.Clear();
	}
	
	VE_ASSERT(m_kMessageQueue.Empty());
	m_u32VectorUse = 0;
	m_u32VectorArrayUse = 0;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeInputManager)
{
	Module() [
		Class<VeInputManager>() [
			DefSingletonFunc("SetEnable", VeInputManager::ms_pSingleton, &VeInputManager::SetEnable),
			DefSingletonFunc("GetEnable", VeInputManager::ms_pSingleton, &VeInputManager::GetEnable)
		]
	];
}
//--------------------------------------------------------------------------
