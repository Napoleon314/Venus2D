////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioSystem.inl
//  Version:     v1.00
//  Created:     28/7/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioChannel::GetIndex()
{
	return m_u32Index;
}
//--------------------------------------------------------------------------
VE_INLINE VeAudioChannel::State VeAudioChannel::GetState()
{
	return m_eState;
}
//--------------------------------------------------------------------------
VE_INLINE void VeAudioChannel::SetVolume(VeFloat32 f32Volume)
{
	m_f32Volume = f32Volume;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeAudioChannel::GetVolume()
{
	return m_f32Volume;
}
//--------------------------------------------------------------------------
VE_INLINE void VeAudioChannel::Stop()
{
	if(m_pkTouchAudio)
	{
		m_pkTouchAudio->Stop(this);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeAudioChannel::Pause()
{
	if(m_pkTouchAudio)
	{
		m_pkTouchAudio->Pause(this);
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeAudioChannel::Resume()
{
	if(m_pkTouchAudio)
	{
		m_pkTouchAudio->Stop(this);
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeThread::Mutex& VeAudioSystem::GetMutex()
{
	return m_kMutex;
}
//--------------------------------------------------------------------------
