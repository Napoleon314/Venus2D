////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioResource.h
//  Version:     v1.00
//  Created:     29/7/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeAudioChannel;

class VE_MAIN_API VeAudio
{
public:
	enum Type
	{
		TYPE_SIMPLE_SOUND,
		TYPE_MUSIC_PLAYER,
		TYPE_MAX
	};

	virtual void Play(VeAudioChannel* pkChannel, VeUInt32 u32LoopNum = 1) = 0;

	virtual void Stop(VeAudioChannel* pkChannel) = 0;

	virtual void Stop() = 0;

	virtual void Pause(VeAudioChannel* pkChannel) = 0;

	virtual void Pause() = 0;

	virtual void Resume(VeAudioChannel* pkChannel) = 0;

	virtual void Resume() = 0;

	virtual void Update() = 0;

	virtual void UpdateAsync() = 0;

	virtual Type GetType() = 0;

	VE_INLINE void SetVolume(VeFloat32 f32Volume);

	VE_INLINE VeFloat32 GetVolume();

protected:
	friend class VeAudioSystem;

	VeAudio();

	virtual ~VeAudio() {}

	VeFloat32 m_f32Volume;
	VeRefNode<VeAudio*> m_kUpdateNode;

};

class VE_MAIN_API VeSimpleSound : public VeResource, public VeAudio
{
	VeDeclareRTTI;
public:
	VeSimpleSound(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeSimpleSound();

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual void Play(VeAudioChannel* pkChannel, VeUInt32 u32LoopNum = 1);

	virtual void Stop(VeAudioChannel* pkChannel);

	virtual void Stop();

	virtual void Pause(VeAudioChannel* pkChannel);

	virtual void Pause();

	virtual void Resume(VeAudioChannel* pkChannel);

	virtual void Resume();

	virtual void Update();

	virtual void UpdateAsync();

	virtual VeAudio::Type GetType();

protected:
	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	VeAudioSampleDataPtr m_spData;
	VeRefList<VeAudioChannel*> m_kPlayingChannelList;

};

VeSmartPointer(VeSimpleSound);

#define VeGetSimpleSound(name,group) VeDynamicCast(VeSimpleSound,VeGetResource(VeResource::SIMPLE_SOUND,name,group))

#define VeLoadSimpleSound(name,group,async) VeDynamicCast(VeSimpleSound,VeLoadResource(VeResource::SIMPLE_SOUND,name,group,async))

#define VeLoadSimpleSoundSync(name,group) VeLoadSimpleSound(name,group,false)

#define VeLoadSimpleSoundAsync(name,group) VeLoadSimpleSound(name,group,true)

class VE_MAIN_API VeMusicPlayer : public VeRefObject, public VeAudio
{
	VeDeclareLuaRttiExport(VeMusicPlayer);
public:
	VeMusicPlayer(const VeChar8* pcName, const VeChar8* pcPath);

	virtual ~VeMusicPlayer();

	virtual void Play(VeAudioChannel* pkChannel, VeUInt32 u32LoopNum = 1);

	virtual void Stop(VeAudioChannel* pkChannel);

	virtual void Stop();

	virtual void Pause(VeAudioChannel* pkChannel);

	virtual void Pause();

	virtual void Resume(VeAudioChannel* pkChannel);

	virtual void Resume();

	virtual void Update();

	virtual void UpdateAsync();

	virtual Type GetType();

	void Play();

	void Play(VeUInt32 u32LoopNum);

protected:
	VeAudioStreamPtr m_spStream;
	VeRefNode<VeAudio*> m_kAsyncNode;
	VeAudioChannel* m_pkChannel;
	VeThread::Mutex m_kMutex;
#	ifdef VE_USE_OAL
	VeUInt32 m_au32Buffer[VE_MAX_QUEUE_NUM];
	VeList<VeUInt32> m_kFreeBufferList;
	VeList<VeUInt32> m_kWaitBufferList;
#	endif
#	ifdef VE_USE_SLES
	VeByte m_abyBuffer[44100 * VE_MAX_QUEUE_NUM];
	VeList<VeByte*> m_kFreeBufferList;
	VeList< VePair<VeByte*,VeUInt32> > m_kWaitBufferList;
	VeList<VeByte*> m_kBufferInPlayList;
#	endif
	bool m_bPlayFlag;

};

VeSmartPointer(VeMusicPlayer);

#ifndef VE_NO_INLINE
#	include "VeAudioResource.inl"
#endif
