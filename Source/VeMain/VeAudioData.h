////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioData.h
//  Version:     v1.00
//  Created:     28/7/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_MAX_CHANNEL_NUM (16)
#define VE_MAX_QUEUE_NUM (3)

class VE_MAIN_API VeAudioSampleData : public VeRefObject
{
public:
	VeAudioSampleData();

	~VeAudioSampleData();

	void ParseWave(VeBinaryIStream& kInput);

	void ParseOgg(VeBinaryIStream& kInput);

	VE_INLINE VeUInt32 GetChannelNum();

	VE_INLINE VeUInt32 GetSampleRate();

	VE_INLINE VeUInt32 GetBitsPerSample();

	VE_INLINE const VeBlobPtr& GetData();

protected:
	VeUInt32 m_u32ChannelNum;
	VeUInt32 m_u32SampleRate;
	VeUInt32 m_u32BitsPerSample;
	VeBlobPtr m_spData;
#	ifdef VE_USE_OAL
	void UpdateBuffer();
	VeUInt32 m_u32Buffer;
public:
	const VeUInt32* GetBuffer();
#	endif

};

VeSmartPointer(VeAudioSampleData);

VeSmartPointer(VeAudioStream);

class VE_MAIN_API VeAudioStream : public VeRefObject
{
public:
	virtual void Prepare() = 0;

	virtual void* Tick(VeUInt32& u32BufferSize, bool bLoop) = 0;

	VE_INLINE VeUInt32 GetChannelNum();

	VE_INLINE VeUInt32 GetSampleRate();

	VE_INLINE VeUInt32 GetBitsPerSample();

	VE_INLINE VeUInt32 GetFixedBufferSize();

	VE_INLINE bool IsPrepared();

	static VeAudioStreamPtr Create(const VeChar8* pcName, const VeChar8* pcPath);

protected:
	VeAudioStream(const VeBinaryIStreamPtr& spStream);

	virtual ~VeAudioStream();

	VeUInt32 m_u32ChannelNum;
	VeUInt32 m_u32SampleRate;
	VeUInt32 m_u32BitsPerSample;
	VeUInt32 m_u32FixedBufferSize;
	VeBinaryIStreamPtr m_spStream;

};

#ifndef VE_NO_INLINE
#	include "VeAudioData.inl"
#endif
