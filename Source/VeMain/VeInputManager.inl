////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeInputManager.inl
//  Version:     v1.00
//  Created:     7/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE bool VeInputMessage::operator == (
	const VeInputMessage& kTarget) const
{
	return m_eDeviceType == kTarget.m_eDeviceType && m_u32InputType
		== kTarget.m_u32InputType && m_u32InputCode
		== kTarget.m_u32InputCode;
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::SetEnable(bool bEnable)
{
	m_bInputProcess = bEnable;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeInputManager::GetEnable()
{
	return m_bInputProcess;
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::RegisterListener(MessageDelegate& kDelegate)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::UnregisterListener(
	MessageDelegate& kDelegate)
{
	m_kEvent.DelDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::AppendMessage(DeviceType eDeviceType,
	VeUInt32 u32InputType, VeUInt32 u32InputCode, void* pvMessageInfo)
{
	m_kMessageQueue.PushBack(VeInputMessage(eDeviceType,
		u32InputType, u32InputCode, pvMessageInfo));
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::AppendMessage(DeviceType eDeviceType,
	VeUInt32 u32InputType, VeUInt32 u32InputCode, VeSizeT stMessageInfo)
{
	m_kMessageQueue.PushBack(VeInputMessage(eDeviceType, u32InputType,
		u32InputCode, stMessageInfo));
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::PopMessage()
{
	m_kMessageQueue.PopFront();
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::HookCurrentMessage()
{
	m_bMessageHooked = true;
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::PerformCallBack(
	const VeInputMessage& kMessage)
{
	m_kEvent.Callback(kMessage, m_bMessageHooked);
}
//--------------------------------------------------------------------------
VE_INLINE void VeInputManager::ProcessMessage(VeInputMessage& kMessage)
{
	PerformCallBack(kMessage);
	m_bMessageHooked = false;
}
//--------------------------------------------------------------------------
