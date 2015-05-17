////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioResource.cpp
//  Version:     v1.00
//  Created:     29/7/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeAudioResource.inl"
#endif

#include <vorbislib/vorbisfile.h>

#ifdef VE_USE_OAL
#	include <OpenAL/al.h>
#	include <OpenAL/alc.h>
#endif

//--------------------------------------------------------------------------
VeAudio::VeAudio() : m_f32Volume(1.0f)
{
	m_kUpdateNode.m_tContent = this;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSimpleSound, VeResource);
//--------------------------------------------------------------------------
VeSimpleSound::VeSimpleSound(const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(SIMPLE_SOUND, pcName, pcGroup)
{

}
//--------------------------------------------------------------------------
VeSimpleSound::~VeSimpleSound()
{
	Unload();
}
//--------------------------------------------------------------------------
VeResource::State VeSimpleSound::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	const VeChar8* pcExt = VeStrrchr(GetName(), '.');
	if(VeStricmp(pcExt, ".wav") == 0)
	{
		m_spData = VE_NEW VeAudioSampleData;
		m_spData->ParseWave(*spStream);
	}
	else if(VeStricmp(pcExt, ".ogg") == 0)
	{
		m_spData = VE_NEW VeAudioSampleData;
		m_spData->ParseOgg(*spStream);
	}
	else
	{
		m_spData = NULL;
	}
	return m_spData ? LOADED : UNLOADED;
}
//--------------------------------------------------------------------------
void VeSimpleSound::UnloadImpl()
{
	Stop();
	m_spData = NULL;
}
//--------------------------------------------------------------------------
VeResource* VeSimpleSound::CreateResource(
	const VeChar8* pcName, const VeChar8* pcGroup)
{
	return VE_NEW VeSimpleSound(pcName, pcGroup);
}
//--------------------------------------------------------------------------
void VeSimpleSound::Play(VeAudioChannel* pkChannel, VeUInt32 u32LoopNum)
{
	if(GetState() == LOADED)
	{
		VE_ASSERT(!(pkChannel->m_pkTouchAudio));
		VE_ASSERT(pkChannel->m_kNode.IsAttach(g_pAudioSystem->m_kFreeChannelList));
		pkChannel->m_pkTouchAudio = this;
		pkChannel->m_eState = VeAudioChannel::PLAYING;
		pkChannel->m_f32Volume = m_f32Volume;
		pkChannel->m_u32LoopNum = u32LoopNum ? u32LoopNum : VE_INFINITE;
		m_kPlayingChannelList.AttachBack(pkChannel->m_kNode);
		VE_ASSERT(m_spData);
#		ifdef VE_USE_OAL
		alSourceQueueBuffers(pkChannel->m_u32ChannelSource, 1, (const ALuint*)(m_spData->GetBuffer()));
		alSourcePlay(pkChannel->m_u32ChannelSource);
#		endif
#		ifdef VE_USE_SLES
		pkChannel->UpdateSLData(m_spData->GetChannelNum(), m_spData->GetSampleRate()*1000, m_spData->GetBitsPerSample());
		VE_ASSERT_EQ((*pkChannel->m_pkPlayerPlay)->SetPlayState(pkChannel->m_pkPlayerPlay, SL_PLAYSTATE_PLAYING), SL_RESULT_SUCCESS);
		VE_ASSERT_EQ((*pkChannel->m_pkPlayerBufferQueue)->Enqueue(pkChannel->m_pkPlayerBufferQueue, *(m_spData->GetData()), m_spData->GetData()->GetSize()), SL_RESULT_SUCCESS);
#		endif
	}
}
//--------------------------------------------------------------------------
void VeSimpleSound::Stop(VeAudioChannel* pkChannel)
{
	if(pkChannel->m_kNode.IsAttach(m_kPlayingChannelList))
	{
		VE_ASSERT(static_cast<VeAudio*>(this) == pkChannel->m_pkTouchAudio);
		VE_ASSERT(pkChannel->m_eState != VeAudioChannel::STOPPED);
		pkChannel->m_pkTouchAudio = NULL;
		pkChannel->m_eState = VeAudioChannel::STOPPED;
		pkChannel->m_f32Volume = 1.0f;
		pkChannel->m_u32LoopNum = 0;
		g_pAudioSystem->m_kFreeChannelList.AttachBack(pkChannel->m_kNode);
#		ifdef VE_USE_OAL
		alSourceStop(pkChannel->m_u32ChannelSource);
		alSourcei(pkChannel->m_u32ChannelSource, AL_BUFFER, NULL);
#		endif
#		ifdef VE_USE_SLES
		VE_ASSERT_EQ((*pkChannel->m_pkPlayerPlay)->SetPlayState(pkChannel->m_pkPlayerPlay, SL_PLAYSTATE_STOPPED), SL_RESULT_SUCCESS);
		VE_ASSERT_EQ((*pkChannel->m_pkPlayerBufferQueue)->Clear(pkChannel->m_pkPlayerBufferQueue), SL_RESULT_SUCCESS);
#		endif
		if(m_kPlayingChannelList.Empty())
		{
			m_kUpdateNode.Detach();
		}
	}
}
//--------------------------------------------------------------------------
void VeSimpleSound::Stop()
{
	m_kPlayingChannelList.BeginIterator();
	while(!m_kPlayingChannelList.IsEnd())
	{
		VeAudioChannel* pkChannel = m_kPlayingChannelList.GetIterNode()->m_tContent;
		m_kPlayingChannelList.Next();
		Stop(pkChannel);
	}
}
//--------------------------------------------------------------------------
void VeSimpleSound::Pause(VeAudioChannel* pkChannel)
{
#	ifdef VE_USE_OAL
	if(pkChannel->m_eState == VeAudioChannel::PLAYING)
	{
		VeInt32 i32Temp = AL_PLAYING;
		alGetSourcei(pkChannel->m_u32ChannelSource, AL_SOURCE_STATE, &i32Temp);
		if(i32Temp == AL_PLAYING)
		{
			alSourcePause(pkChannel->m_u32ChannelSource);
			pkChannel->m_eState = VeAudioChannel::PAUSED;
		}
	}
#	endif
#	ifdef VE_USE_SLES
	if(pkChannel->m_eState == VeAudioChannel::PLAYING)
	{
		VE_ASSERT_EQ((*pkChannel->m_pkPlayerPlay)->SetPlayState(pkChannel->m_pkPlayerPlay, SL_PLAYSTATE_PAUSED), SL_RESULT_SUCCESS);
		pkChannel->m_eState = VeAudioChannel::PAUSED;
	}
#	endif
}
//--------------------------------------------------------------------------
void VeSimpleSound::Pause()
{
	m_kPlayingChannelList.BeginIterator();
	while(!m_kPlayingChannelList.IsEnd())
	{
		VeAudioChannel* pkChannel = m_kPlayingChannelList.GetIterNode()->m_tContent;
		m_kPlayingChannelList.Next();
		Pause(pkChannel);
	}
}
//--------------------------------------------------------------------------
void VeSimpleSound::Resume(VeAudioChannel* pkChannel)
{
#	ifdef VE_USE_OAL
	if(pkChannel->m_eState == VeAudioChannel::PAUSED)
	{
		alSourcePlay(pkChannel->m_u32ChannelSource);
		pkChannel->m_eState = VeAudioChannel::PLAYING;
	}
#	endif
#	ifdef VE_USE_SLES
	if(pkChannel->m_eState == VeAudioChannel::PAUSED)
	{
		VE_ASSERT_EQ((*pkChannel->m_pkPlayerPlay)->SetPlayState(pkChannel->m_pkPlayerPlay, SL_PLAYSTATE_PLAYING), SL_RESULT_SUCCESS);
		pkChannel->m_eState = VeAudioChannel::PLAYING;
	}
#	endif
}
//--------------------------------------------------------------------------
void VeSimpleSound::Resume()
{
	m_kPlayingChannelList.BeginIterator();
	while(!m_kPlayingChannelList.IsEnd())
	{
		VeAudioChannel* pkChannel = m_kPlayingChannelList.GetIterNode()->m_tContent;
		m_kPlayingChannelList.Next();
		Resume(pkChannel);
	}
}
//--------------------------------------------------------------------------
void VeSimpleSound::Update()
{
	m_kPlayingChannelList.BeginIterator();
	while(!m_kPlayingChannelList.IsEnd())
	{
		VeAudioChannel* pkChannel = m_kPlayingChannelList.GetIterNode()->m_tContent;
		m_kPlayingChannelList.Next();
		if(pkChannel->m_eState == VeAudioChannel::PLAYING)
		{
#			ifdef VE_USE_OAL
			VeInt32 i32Temp = AL_PLAYING;
			alGetSourcei(pkChannel->m_u32ChannelSource, AL_SOURCE_STATE, &i32Temp);
			if(i32Temp == AL_PLAYING)
			{
				VeInt32 i32Queued(0);
				alGetSourcei(pkChannel->m_u32ChannelSource, AL_BUFFERS_QUEUED, &i32Queued);
				VE_ASSERT(i32Queued >= 0);
				if(i32Queued < VE_MAX_QUEUE_NUM && pkChannel->m_u32LoopNum > VeUInt32(i32Queued))
				{
					alSourceQueueBuffers(pkChannel->m_u32ChannelSource, 1, (const ALuint*)(m_spData->GetBuffer()));
				}
				VeInt32 i32Processed(0);
				alGetSourcei(pkChannel->m_u32ChannelSource, AL_BUFFERS_PROCESSED, &i32Processed);
				if(i32Processed)
				{
					alSourceUnqueueBuffers(pkChannel->m_u32ChannelSource, 1, (ALuint*)&i32Processed);
					if(pkChannel->m_u32LoopNum || pkChannel->m_u32LoopNum < VE_INFINITE)
						--pkChannel->m_u32LoopNum;
				}
			}
			else
			{
				pkChannel->Stop();
			}
#			endif
#			ifdef VE_USE_SLES
			SLAndroidSimpleBufferQueueState kState;
			(*pkChannel->m_pkPlayerBufferQueue)->GetState(pkChannel->m_pkPlayerBufferQueue, &kState);
			if(kState.count > 0)
			{
				if(kState.count < VE_MAX_QUEUE_NUM && pkChannel->m_u32LoopNum > (kState.count + kState.index))
				{
					VE_ASSERT_EQ((*pkChannel->m_pkPlayerBufferQueue)->Enqueue(pkChannel->m_pkPlayerBufferQueue, *(m_spData->GetData()), m_spData->GetData()->GetSize()), SL_RESULT_SUCCESS);
				}
			}
			else
			{
				pkChannel->Stop();
			}
#			endif
		}
	}
}
//--------------------------------------------------------------------------
void VeSimpleSound::UpdateAsync()
{

}
//--------------------------------------------------------------------------
VeAudio::Type VeSimpleSound::GetType()
{
	return TYPE_SIMPLE_SOUND;
}
//--------------------------------------------------------------------------
VeMusicPlayer::VeMusicPlayer(const VeChar8* pcName, const VeChar8* pcPath)
{
	m_spStream = VeAudioStream::Create(pcName, pcPath);
	VE_ASSERT(m_spStream);
	m_kAsyncNode.m_tContent = this;
	m_pkChannel = NULL;
#	ifdef VE_USE_OAL
	alGenBuffers(VE_MAX_QUEUE_NUM, m_au32Buffer);
#	endif
	m_bPlayFlag = false;
}
//--------------------------------------------------------------------------
VeMusicPlayer::~VeMusicPlayer()
{
	Stop();
#	ifdef VE_USE_OAL
	alDeleteBuffers(VE_MAX_QUEUE_NUM, m_au32Buffer);
#	endif
}
//--------------------------------------------------------------------------
void VeMusicPlayer::Play(VeAudioChannel* pkChannel, VeUInt32 u32LoopNum)
{
	if(!m_pkChannel)
	{
		VE_ASSERT(!(pkChannel->m_pkTouchAudio));
		VE_ASSERT(pkChannel->m_kNode.IsAttach(g_pAudioSystem->m_kFreeChannelList));
		pkChannel->m_pkTouchAudio = this;
		pkChannel->m_eState = VeAudioChannel::PLAYING;
		pkChannel->m_f32Volume = m_f32Volume;
		pkChannel->m_u32LoopNum = u32LoopNum ? u32LoopNum : VE_INFINITE;
		pkChannel->m_kNode.Detach();
		m_pkChannel = pkChannel;
#		ifdef VE_USE_OAL
		for(VeUInt32 i(0); i < VE_MAX_QUEUE_NUM; ++i)
		{
			m_kFreeBufferList.PushBack(m_au32Buffer[i]);
		}
		m_bPlayFlag = true;
#		endif
#		ifdef VE_USE_SLES
		m_kFreeBufferList.Clear();
		m_kWaitBufferList.Clear();
		for(VeUInt32 i(0); i < VE_MAX_QUEUE_NUM; ++i)
		{
			m_kFreeBufferList.PushBack(m_abyBuffer + 44100 * i);
		}
#		endif
		m_bPlayFlag = true;
		g_pAudioSystem->AddBackgroundAudio(m_kAsyncNode);
	}
}
//--------------------------------------------------------------------------
void VeMusicPlayer::Play()
{
	g_pAudioSystem->Play(this);
}
//--------------------------------------------------------------------------
void VeMusicPlayer::Play(VeUInt32 u32LoopNum)
{
	g_pAudioSystem->Play(this, u32LoopNum);
}
//--------------------------------------------------------------------------
void VeMusicPlayer::Stop(VeAudioChannel* pkChannel)
{
	if(m_pkChannel == pkChannel)
	{
		Stop();
	}
}
//--------------------------------------------------------------------------
void VeMusicPlayer::Stop()
{
	if(m_pkChannel)
	{
		g_pAudioSystem->RemoveBackgroundAudio(m_kAsyncNode);
		VE_ASSERT(static_cast<VeAudio*>(this) == m_pkChannel->m_pkTouchAudio);
		VE_ASSERT(m_pkChannel->m_eState != VeAudioChannel::STOPPED);
		m_pkChannel->m_pkTouchAudio = NULL;
		m_pkChannel->m_eState = VeAudioChannel::STOPPED;
		m_pkChannel->m_f32Volume = 1.0f;
		m_pkChannel->m_u32LoopNum = 0;
		g_pAudioSystem->m_kFreeChannelList.AttachBack(m_pkChannel->m_kNode);
		m_kUpdateNode.Detach();
#		ifdef VE_USE_OAL
		alSourceStop(m_pkChannel->m_u32ChannelSource);
		alSourcei(m_pkChannel->m_u32ChannelSource, AL_BUFFER, NULL);
#		endif
#		ifdef VE_USE_SLES
		if(m_pkChannel->m_pkPlayerObj)
		{
			VE_ASSERT_EQ((*m_pkChannel->m_pkPlayerPlay)->SetPlayState(m_pkChannel->m_pkPlayerPlay, SL_PLAYSTATE_STOPPED), SL_RESULT_SUCCESS);
			VE_ASSERT_EQ((*m_pkChannel->m_pkPlayerBufferQueue)->Clear(m_pkChannel->m_pkPlayerBufferQueue), SL_RESULT_SUCCESS);
		}
		m_kBufferInPlayList.Clear();
#		endif
		m_kFreeBufferList.Clear();
		m_kWaitBufferList.Clear();
		m_bPlayFlag = false;
		m_pkChannel = NULL;
	}
}
//--------------------------------------------------------------------------
void VeMusicPlayer::Pause(VeAudioChannel* pkChannel)
{

}
//--------------------------------------------------------------------------
void VeMusicPlayer::Pause()
{

}
//--------------------------------------------------------------------------
void VeMusicPlayer::Resume(VeAudioChannel* pkChannel)
{

}
//--------------------------------------------------------------------------
void VeMusicPlayer::Resume()
{

}
//--------------------------------------------------------------------------
void VeMusicPlayer::Update()
{
	if(m_pkChannel && m_pkChannel->m_eState == VeAudioChannel::PLAYING)
	{
#		ifdef VE_USE_OAL
		if(m_kWaitBufferList.Size())
		{
			VE_AUTO_LOCK_MUTEX(m_kMutex);
			VeUInt32 u32Buffer = m_kWaitBufferList.Front();
			m_kWaitBufferList.PopFront();
			alSourceQueueBuffers(m_pkChannel->m_u32ChannelSource, 1, (const ALuint*)&u32Buffer);
			if(m_bPlayFlag)
			{
				alSourcePlay(m_pkChannel->m_u32ChannelSource);
				m_bPlayFlag = false;
			}
		}
		if(!m_bPlayFlag)
		{
			VeInt32 i32Temp = AL_PLAYING;
			alGetSourcei(m_pkChannel->m_u32ChannelSource, AL_SOURCE_STATE, &i32Temp);
			if(i32Temp == AL_PLAYING)
			{
				alGetSourcei(m_pkChannel->m_u32ChannelSource, AL_BUFFERS_PROCESSED, &i32Temp);
				if(i32Temp)
				{
					alSourceUnqueueBuffers(m_pkChannel->m_u32ChannelSource, 1, (ALuint*)&i32Temp);
					m_kFreeBufferList.PushBack(i32Temp);
				}
			}
			else
			{
				Stop();
			}
		}
#		endif
#		ifdef VE_USE_SLES
		if(m_kWaitBufferList.Size())
		{
			if(m_bPlayFlag)
			{
				m_pkChannel->UpdateSLData(m_spStream->GetChannelNum(), m_spStream->GetSampleRate() * 1000, m_spStream->GetBitsPerSample());
				VE_ASSERT_EQ((*m_pkChannel->m_pkPlayerPlay)->SetPlayState(m_pkChannel->m_pkPlayerPlay, SL_PLAYSTATE_PLAYING), SL_RESULT_SUCCESS);
				m_bPlayFlag = false;
			}
			VE_AUTO_LOCK_MUTEX(m_kMutex);
			VeByte* pbyBuffer = m_kWaitBufferList.Front().m_tFirst;
			VeUInt32 u32Size = m_kWaitBufferList.Front().m_tSecond;
			m_kWaitBufferList.PopFront();
			VE_ASSERT_EQ((*m_pkChannel->m_pkPlayerBufferQueue)->Enqueue(m_pkChannel->m_pkPlayerBufferQueue, pbyBuffer, u32Size), SL_RESULT_SUCCESS);
			m_kBufferInPlayList.PushBack(pbyBuffer);
		}
		if(!m_bPlayFlag)
		{
			SLAndroidSimpleBufferQueueState kState;
			VE_ASSERT_EQ((*m_pkChannel->m_pkPlayerBufferQueue)->GetState(m_pkChannel->m_pkPlayerBufferQueue, &kState), SL_RESULT_SUCCESS);
			if(kState.count > 0)
			{
				if(kState.count < m_kBufferInPlayList.Size())
				{
					VE_AUTO_LOCK_MUTEX(m_kMutex);
					m_kFreeBufferList.PushBack(m_kBufferInPlayList.Front());
					m_kBufferInPlayList.PopFront();
				}
			}
			else
			{
				Stop();
			}
		}
#		endif
	}
}
//--------------------------------------------------------------------------
void VeMusicPlayer::UpdateAsync()
{
    if(m_pkChannel && m_pkChannel->m_eState == VeAudioChannel::PLAYING)
    {
        if(m_kFreeBufferList.Size())
        {
            VeUInt32 u32Size(0);
            void* pvDecodeBuffer = m_spStream->Tick(u32Size, true);
            if(u32Size && pvDecodeBuffer)
            {
				VE_AUTO_LOCK_MUTEX(m_kMutex);
#				ifdef VE_USE_OAL
                VeUInt32 u32Buffer = m_kFreeBufferList.Front();
                m_kFreeBufferList.PopFront();
                VeUInt32 u32Format = (m_spStream->GetChannelNum() == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
                alBufferData(u32Buffer, u32Format, pvDecodeBuffer, u32Size, m_spStream->GetSampleRate());
                m_kWaitBufferList.PushBack(u32Buffer);
#				endif
#				ifdef VE_USE_SLES
                VeByte* pbyBuffer = m_kFreeBufferList.Front();
                m_kFreeBufferList.PopFront();
                VE_ASSERT(44100 >= u32Size);
                VeMemoryCopy(pbyBuffer, pvDecodeBuffer, u32Size);
                m_kWaitBufferList.PushBack(VePair<VeByte*,VeUInt32>(pbyBuffer, u32Size));
#				endif
            }
        }
    }
}
//--------------------------------------------------------------------------
VeAudio::Type VeMusicPlayer::GetType()
{
	return TYPE_MUSIC_PLAYER;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeMusicPlayer)
{
	Module() [
		Class<VeMusicPlayer>().
			Def(ConstructorNew<const VeChar8*, const VeChar8*>()).
			Def("Play", (void (VeMusicPlayer::*)())&VeMusicPlayer::Play).
			Def("Play", (void (VeMusicPlayer::*)(VeUInt32))&VeMusicPlayer::Play).
			Def("Stop", (void (VeMusicPlayer::*)())&VeMusicPlayer::Stop).
			Def("Pause", (void (VeMusicPlayer::*)())&VeMusicPlayer::Pause).
			Def("Resume", (void (VeMusicPlayer::*)())&VeMusicPlayer::Resume).
			Def("SetVolume", &VeMusicPlayer::SetVolume).
			Def("GetVolume", &VeMusicPlayer::GetVolume)
	];
}
//--------------------------------------------------------------------------
