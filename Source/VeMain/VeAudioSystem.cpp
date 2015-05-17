////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioSystem.cpp
//  Version:     v1.00
//  Created:     28/7/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeAudioSystem.inl"
#endif

#ifdef VE_USE_OAL
#	include <OpenAL/al.h>
#	include <OpenAL/alc.h>
#endif

//--------------------------------------------------------------------------
VeAudioChannel::VeAudioChannel() : m_u32Index(0), m_eState(STOPPED)
	, m_f32Volume(1.0f), m_u32LoopNum(0), m_pkTouchAudio(NULL)
{
	m_kNode.m_tContent = this;
#	ifdef VE_USE_SLES
	m_pkPlayerObj = NULL;
	m_pkPlayerPlay = NULL;
	m_pkPlayerBufferQueue = NULL;
	m_pkPlayerEffectSend = NULL;
	m_pkPlayerVolume = NULL;
	m_u32ChannelNum = 0;
	m_u32SampleRate = 0;
	m_u32BitsPerSample = 0;
#	endif
}
//--------------------------------------------------------------------------
VeAudioChannel::~VeAudioChannel()
{
	m_u32Index = 0;
	m_eState = STOPPED;
	m_f32Volume = 1.0f;
	m_pkTouchAudio = NULL;
}
//--------------------------------------------------------------------------
void VeAudioChannel::Init()
{
#	ifdef VE_USE_OAL
	m_u32ChannelSource = NULL;
	alGenSources(1, &m_u32ChannelSource);
	VE_ASSERT(alGetError() == AL_NO_ERROR && m_u32ChannelSource);
#	endif
}
//--------------------------------------------------------------------------
void VeAudioChannel::Term()
{
#	ifdef VE_USE_OAL
	alDeleteSources(1, &m_u32ChannelSource);
	m_u32ChannelSource = NULL;
	VE_ASSERT(alGetError() == AL_NO_ERROR);
#	endif
#	ifdef VE_USE_SLES
	UpdateSLData(0, 0, 0);
#	endif
}
//--------------------------------------------------------------------------
#ifdef VE_USE_SLES
//--------------------------------------------------------------------------
void VeAudioChannel::UpdateSLData(VeUInt32 u32Channel,
	VeUInt32 u32Rate, VeUInt32 u32Bits)
{
	if(!u32Channel)
	{
		if(m_pkPlayerObj)
		{
			(*m_pkPlayerObj)->Destroy(m_pkPlayerObj);
			m_pkPlayerObj = NULL;
			m_pkPlayerPlay = NULL;
			m_pkPlayerBufferQueue = NULL;
			m_pkPlayerEffectSend = NULL;
			m_pkPlayerVolume = NULL;
		}
	}
	else if(u32Channel != m_u32ChannelNum
		|| u32Rate != m_u32SampleRate
		|| u32Bits != m_u32BitsPerSample)
	{
		if(m_pkPlayerObj)
		{
			(*m_pkPlayerObj)->Destroy(m_pkPlayerObj);
			m_pkPlayerObj = NULL;
			m_pkPlayerPlay = NULL;
			m_pkPlayerBufferQueue = NULL;
			m_pkPlayerEffectSend = NULL;
			m_pkPlayerVolume = NULL;
		}
		VeUInt32 u32Mask = (u32Channel > 1)
			? (SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT)
			: SL_SPEAKER_FRONT_CENTER;
		SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, VE_MAX_QUEUE_NUM};
		SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, u32Channel, u32Rate,
			u32Bits, u32Bits, u32Mask, SL_BYTEORDER_LITTLEENDIAN};
		SLDataSource audioSrc = {&loc_bufq, &format_pcm};
		SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, g_pAudioSystem->m_pkOutputMixObject};
		SLDataSink audioSnk = {&loc_outmix, NULL};
		const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME};
		const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
		VE_ASSERT_EQ((*g_pAudioSystem->m_pkEngine)->CreateAudioPlayer(g_pAudioSystem->m_pkEngine,
			&m_pkPlayerObj, &audioSrc, &audioSnk, 3, ids, req), SL_RESULT_SUCCESS);
		VE_ASSERT_EQ((*m_pkPlayerObj)->Realize(m_pkPlayerObj, SL_BOOLEAN_FALSE), SL_RESULT_SUCCESS);
		VE_ASSERT_EQ((*m_pkPlayerObj)->GetInterface(m_pkPlayerObj, SL_IID_PLAY, &m_pkPlayerPlay), SL_RESULT_SUCCESS);
		VE_ASSERT_EQ((*m_pkPlayerObj)->GetInterface(m_pkPlayerObj, SL_IID_BUFFERQUEUE, &m_pkPlayerBufferQueue), SL_RESULT_SUCCESS);
		VE_ASSERT_EQ((*m_pkPlayerObj)->GetInterface(m_pkPlayerObj, SL_IID_EFFECTSEND, &m_pkPlayerEffectSend), SL_RESULT_SUCCESS);
		VE_ASSERT_EQ((*m_pkPlayerObj)->GetInterface(m_pkPlayerObj, SL_IID_VOLUME, &m_pkPlayerVolume), SL_RESULT_SUCCESS);
	}
}
//--------------------------------------------------------------------------
const SLEnvironmentalReverbSettings VeAudioSystem::ms_kReverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#ifdef VE_PLATFORM_IOS
//--------------------------------------------------------------------------
void VeInitAudio();
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeAudioSystem::VeAudioSystem()
{
#   ifdef VE_PLATFORM_IOS
    VeInitAudio();
#   endif
#	ifdef VE_USE_OAL
	m_pvDevice = alcOpenDevice(NULL);
	VE_ASSERT(m_pvDevice);
	m_pvContext = alcCreateContext((ALCdevice*)m_pvDevice, NULL);
	VE_ASSERT(m_pvContext);
	alcMakeContextCurrent((ALCcontext*)m_pvContext);
	VE_ASSERT(alGetError() == AL_NO_ERROR);
#	endif
#	ifdef VE_USE_SLES
	VE_ASSERT_EQ(slCreateEngine(&m_pkEngineObj, 0, NULL, 0, NULL, NULL), SL_RESULT_SUCCESS);
	VE_ASSERT_EQ((*m_pkEngineObj)->Realize(m_pkEngineObj, SL_BOOLEAN_FALSE), SL_RESULT_SUCCESS);
	VE_ASSERT_EQ((*m_pkEngineObj)->GetInterface(m_pkEngineObj, SL_IID_ENGINE, &m_pkEngine), SL_RESULT_SUCCESS);
	const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
	const SLboolean req[1] = {SL_BOOLEAN_FALSE};
	VE_ASSERT_EQ((*m_pkEngine)->CreateOutputMix(m_pkEngine, &m_pkOutputMixObject, 1, ids, req), SL_RESULT_SUCCESS);
	VE_ASSERT_EQ((*m_pkOutputMixObject)->Realize(m_pkOutputMixObject, SL_BOOLEAN_FALSE), SL_RESULT_SUCCESS);
	if((*m_pkOutputMixObject)->GetInterface(m_pkOutputMixObject, SL_IID_ENVIRONMENTALREVERB, &m_pkOutputMixEnvironmentalReverb) == SL_RESULT_SUCCESS)
	{
		VE_ASSERT_EQ((*m_pkOutputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(m_pkOutputMixEnvironmentalReverb, &ms_kReverbSettings), SL_RESULT_SUCCESS);
	}
#	endif
	InitGlobal();
	m_bLoopFlag = true;
	Start();
}
//--------------------------------------------------------------------------
VeAudioSystem::~VeAudioSystem()
{
	m_bLoopFlag = false;
	while(IsRunning()) {}
	TermGlobal();
#	ifdef VE_USE_OAL
	VE_ASSERT(m_pvContext);
	alcDestroyContext((ALCcontext*)m_pvContext);
	m_pvContext = NULL;
	VE_ASSERT(m_pvDevice);
	alcCloseDevice((ALCdevice*)m_pvDevice);
	VE_ASSERT(alGetError() == AL_NO_ERROR);
	m_pvDevice = NULL;
#	endif
#	ifdef VE_USE_SLES
	if(m_pkOutputMixObject)
	{
		(*m_pkOutputMixObject)->Destroy(m_pkOutputMixObject);
		m_pkOutputMixObject = NULL;
		m_pkOutputMixEnvironmentalReverb = NULL;
	}

	if(m_pkEngineObj != NULL)
	{
		(*m_pkEngineObj)->Destroy(m_pkEngineObj);
		m_pkEngineObj = NULL;
		m_pkEngine = NULL;
	}
#	endif
}
//--------------------------------------------------------------------------
void VeAudioSystem::InitGlobal()
{
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::SIMPLE_SOUND, VeSimpleSound::CreateResource);
	for(VeUInt32 i(0); i < VE_MAX_CHANNEL_NUM; ++i)
	{
		VeAudioChannel& kChannel = m_akChannels[i];
		kChannel.Init();
		kChannel.m_u32Index = i;
		m_kFreeChannelList.AttachBack(kChannel.m_kNode);
	}
}
//--------------------------------------------------------------------------
void VeAudioSystem::TermGlobal()
{
	for(VeUInt32 i(0); i < VE_MAX_CHANNEL_NUM; ++i)
	{
		VeAudioChannel& kChannel = m_akChannels[i];
		kChannel.Stop();
		kChannel.Term();
	}
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::SIMPLE_SOUND, NULL);
}
//--------------------------------------------------------------------------
void VeAudioSystem::AddBackgroundAudio(VeRefNode<VeAudio*>& kAudio)
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	m_kBackgroundTick.AttachBack(kAudio);
}
//--------------------------------------------------------------------------
void VeAudioSystem::RemoveBackgroundAudio(VeRefNode<VeAudio*>& kAudio)
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	if(kAudio.IsAttach(m_kBackgroundTick))
	{
		kAudio.Detach();
	}
}
//--------------------------------------------------------------------------
void VeAudioSystem::Run()
{
	while(m_bLoopFlag)
	{
		{
			VE_AUTO_LOCK_MUTEX(m_kMutex);
			m_kBackgroundTick.BeginIterator();
			while(!m_kBackgroundTick.IsEnd())
			{
				VeAudio* pkAudio = m_kBackgroundTick.GetIterNode()->m_tContent;
				m_kBackgroundTick.Next();
				pkAudio->UpdateAsync();
			}
		}
		VeSleep(50);
	}
}
//--------------------------------------------------------------------------
void VeAudioSystem::Update()
{
	m_kPlayingAudioList.BeginIterator();
	while(!m_kPlayingAudioList.IsEnd())
	{
		VeAudio* pkAudio = m_kPlayingAudioList.GetIterNode()->m_tContent;
		m_kPlayingAudioList.Next();
		pkAudio->Update();
	}
}
//--------------------------------------------------------------------------
void VeAudioSystem::OnStartInterruption()
{
#	ifdef VE_USE_OAL
    alcMakeContextCurrent(NULL);
#	endif
}
//--------------------------------------------------------------------------
void VeAudioSystem::OnEndInterruption()
{
#	ifdef VE_USE_OAL
    alcMakeContextCurrent((ALCcontext*)m_pvContext);
#	endif
}
//--------------------------------------------------------------------------
VeAudioChannel* VeAudioSystem::GetChannel(VeUInt32 u32Index)
{
	VE_ASSERT(u32Index < VE_MAX_CHANNEL_NUM);
	return m_akChannels + u32Index;
}
//--------------------------------------------------------------------------
VeAudioChannel* VeAudioSystem::GetFreeChannel()
{
	return m_kFreeChannelList.Size() ?
		m_kFreeChannelList.GetHeadNode()->m_tContent : NULL;
}
//--------------------------------------------------------------------------
VeAudioChannel* VeAudioSystem::Play(VeAudio* pkAudio, VeUInt32 u32LoopNum)
{
	VeAudioChannel* pkTarget = GetFreeChannel();
	if(pkTarget)
	{
		pkAudio->Play(pkTarget, u32LoopNum);
		m_kPlayingAudioList.AttachBack(pkAudio->m_kUpdateNode);
	}
	return pkTarget;
}
//--------------------------------------------------------------------------
void VeAudioSystem::PlayEffect(const VeChar8* pcName)
{
	PlayEffect(pcName, 1);
}
//--------------------------------------------------------------------------
void VeAudioSystem::PlayEffect(const VeChar8* pcName, VeUInt32 u32LoopNum)
{
	VeSimpleSoundPtr spSound = VeGetSimpleSound(pcName, g_pResourceManager->GetDefaultGroupName());
	if(spSound && spSound->GetState() == VeResource::LOADED)
	{
		Play(spSound, u32LoopNum);
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeAudioSystem)
{
	Module() [
		Class<VeAudioSystem>() [
			DefSingletonFunc("PlayEffect", VeAudioSystem::ms_pSingleton, (void (VeAudioSystem::*)(const VeChar8*))&VeAudioSystem::PlayEffect),
			DefSingletonFunc("PlayEffect", VeAudioSystem::ms_pSingleton, (void (VeAudioSystem::*)(const VeChar8*,VeUInt32))&VeAudioSystem::PlayEffect)
		]
	];
}
//--------------------------------------------------------------------------
