////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioData.cpp
//  Version:     v1.00
//  Created:     28/7/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeAudioData.inl"
#endif

#include <vorbislib/vorbisfile.h>

#ifdef VE_USE_OAL
#	include <OpenAL/al.h>
#	include <OpenAL/alc.h>
#endif

//--------------------------------------------------------------------------
struct VeWaveFileHeader
{
	VeChar8 m_ac8Riff[4];
	VeUInt32 m_u32RiffSize;
	VeChar8 m_ac8Wave[4];
};
//--------------------------------------------------------------------------
struct VeRiffChunk
{
	VeChar8 m_ac8ChunkName[4];
	VeUInt32 m_u32ChunkSize;
};
//--------------------------------------------------------------------------
struct VeWaveFormat
{
	VeUInt16 m_u16FormatTag;
	VeUInt16 m_u16Channels;
	VeUInt32 m_u32SamplesPerSec;
	VeUInt32 m_u32AvgBytesPerSec;
	VeUInt16 m_u16BlockAlign;
	VeUInt16 m_u16BitsPerSample;
	VeUInt16 m_u16Extra; 
};
//--------------------------------------------------------------------------
VeSizeT VeOggVorbisRead(void* pvPointer, VeSizeT stSize,
	VeSizeT stCount, void* pvData)
{
	VeBinaryIStream* pkStream = (VeBinaryIStream*)pvData;
	return pkStream->Read(pvPointer, VeInt32(stSize * stCount));
}
//--------------------------------------------------------------------------
VeInt32 VeOggVorbisSeek(void* pvData, VeInt64 i64Offset, VeInt32 i32Whence)
{
	VeBinaryIStream* pkStream = (VeBinaryIStream*)pvData;
	return pkStream->Seek((VeInt32)i64Offset, (VeWhence)i32Whence);
}
//--------------------------------------------------------------------------
VeInt32 VeOggVorbisClose(void* pvData)
{
	return VE_S_OK;
}
//--------------------------------------------------------------------------
VeLong VeOggVorbisTell(void* pvData)
{
	VeBinaryIStream* pkStream = (VeBinaryIStream*)pvData;
	return pkStream->Tell();
}
//--------------------------------------------------------------------------
const ov_callbacks s_kVorbisCallback =
{
	VeOggVorbisRead,
	VeOggVorbisSeek,
	VeOggVorbisClose,
	VeOggVorbisTell
};
//--------------------------------------------------------------------------
VeAudioSampleData::VeAudioSampleData()
	: m_u32ChannelNum(0), m_u32SampleRate(0), m_u32BitsPerSample(0)
{
#	ifdef VE_USE_OAL
	m_u32Buffer = NULL;
	alGenBuffers(1, &m_u32Buffer);
	VE_ASSERT(alGetError() == AL_NO_ERROR && m_u32Buffer);
#	endif
}
//--------------------------------------------------------------------------
VeAudioSampleData::~VeAudioSampleData()
{
#	ifdef VE_USE_OAL
	alDeleteBuffers(1, &m_u32Buffer);
	m_u32Buffer = NULL;
	VE_ASSERT(alGetError() == AL_NO_ERROR);
#	endif
}
//--------------------------------------------------------------------------
void VeAudioSampleData::ParseWave(VeBinaryIStream& kInput)
{
	VeWaveFileHeader kHeader;
	VE_ASSERT_EQ(kInput.Read(&kHeader, 12), 12);
	VE_ASSERT((!VeStrnicmp(kHeader.m_ac8Riff, "RIFF", 4)) && (!VeStrnicmp(kHeader.m_ac8Wave, "WAVE", 4)));
	VeRiffChunk kChunk;
	while(kInput.Read(&kChunk, 8) == 8)
	{
		if(!VeStrnicmp(kChunk.m_ac8ChunkName, "fmt ", 4))
		{
			VeWaveFormat kFormat;
			VE_ASSERT_EQ(kInput.Read(&kFormat, kChunk.m_u32ChunkSize), VeInt32(kChunk.m_u32ChunkSize));
			VE_ASSERT(kFormat.m_u16FormatTag == 1);
			m_u32ChannelNum = kFormat.m_u16Channels;
			m_u32SampleRate = kFormat.m_u32SamplesPerSec;
			m_u32BitsPerSample = kFormat.m_u16BitsPerSample;
		}
		else if(!VeStrnicmp(kChunk.m_ac8ChunkName, "data", 4))
		{
			m_spData = VE_NEW VeBlob(kChunk.m_u32ChunkSize);
			VE_ASSERT_EQ(kInput.Read(*m_spData, kChunk.m_u32ChunkSize), VeInt32(kChunk.m_u32ChunkSize));
		}
		else
		{
			kInput.Skip(kChunk.m_u32ChunkSize);
		}
		if (kChunk.m_u32ChunkSize & 1)
		{
			kInput.Skip(1);
		}
	}
#	ifdef VE_USE_OAL
	UpdateBuffer();
#	endif
}
//--------------------------------------------------------------------------
void VeAudioSampleData::ParseOgg(VeBinaryIStream& kInput)
{
	OggVorbis_File kVorbisFile;
	if(ov_open_callbacks(&kInput, &kVorbisFile, NULL, 0, s_kVorbisCallback) == 0)
	{
		vorbis_info* pkVorbisInfo = ov_info(&kVorbisFile, -1);
		VE_ASSERT(pkVorbisInfo);
		VE_ASSERT(pkVorbisInfo->channels == 1 || pkVorbisInfo->channels == 2);
		const VeSizeT stSampleSize = (pkVorbisInfo->channels) << 1;
		VeSizeT stBufferSize = VeSizeT(ov_pcm_total(&kVorbisFile, -1)) * stSampleSize;
		m_spData = VE_NEW VeBlob(VeUInt32(stBufferSize));
		VeUInt32 u32BytesDone(0);
		VeInt32 i32CurrentSection;
		while(u32BytesDone < stBufferSize)
		{
			long lBytes = ov_read(&kVorbisFile, (VeChar8*)m_spData->GetBuffer() + u32BytesDone, int(stBufferSize - u32BytesDone), 0, 2, 1, &i32CurrentSection);
			if(lBytes > 0)
			{
				u32BytesDone += lBytes;
			}
			else
			{
				break;
			}
		}
		VE_ASSERT(u32BytesDone == stBufferSize);
		if (pkVorbisInfo->channels == 6)
		{
			VeInt16* pi16Samples = (VeInt16*)m_spData->GetBuffer();
			for(VeUInt32 i(0); i < (stBufferSize >> 1); i += 6)
			{
				VeSwap(pi16Samples[i+1], pi16Samples[i+2]);
				VeSwap(pi16Samples[i+3], pi16Samples[i+5]);
				VeSwap(pi16Samples[i+4], pi16Samples[i+5]);
			}
		}
		m_u32ChannelNum = pkVorbisInfo->channels;
		m_u32SampleRate = VeUInt32(pkVorbisInfo->rate);
		m_u32BitsPerSample = 16;
		ov_clear(&kVorbisFile);
#		ifdef VE_USE_OAL
		UpdateBuffer();
#		endif
	}
	else
	{
		VE_ASSERT(!"Ogg file error!");
	}
}
//--------------------------------------------------------------------------
#ifdef VE_USE_OAL
//--------------------------------------------------------------------------
void VeAudioSampleData::UpdateBuffer()
{
	VE_ASSERT(m_spData);
	VeUInt32 u32Format(NULL);
	switch(m_u32BitsPerSample)
	{
	case 4:
		u32Format = (m_u32ChannelNum == 1) ? alGetEnumValue("AL_FORMAT_MONO_IMA4") : alGetEnumValue("AL_FORMAT_STEREO_IMA4");
		break;
	case 8:
		u32Format = (m_u32ChannelNum == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
		break;
	case 16:
		u32Format = (m_u32ChannelNum == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		break;
	default:
		break;
	}
	VE_ASSERT(u32Format);
	alBufferData(m_u32Buffer, u32Format, m_spData->GetBuffer(), m_spData->GetSize(), m_u32SampleRate);
	VE_ASSERT(alGetError() == AL_NO_ERROR);
	m_spData = NULL;
}
//--------------------------------------------------------------------------
const VeUInt32* VeAudioSampleData::GetBuffer()
{
	return &m_u32Buffer;
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeUInt32 VeDecodeOggVorbis(OggVorbis_File* pkFile, VeChar8* pcBuffer,
	VeUInt32 u32Size)
{
	VeUInt32 u32BytesDone(0);
	while(true)
	{
		VeInt32 i32CurrentSection;
		VeInt32 i32DecodeSize = VeInt32(ov_read(pkFile, pcBuffer + u32BytesDone,
			u32Size - u32BytesDone, 0, 2, 1, &i32CurrentSection));
		if(i32DecodeSize > 0)
		{
			u32BytesDone += i32DecodeSize;
			if (u32BytesDone >= u32Size)
				break;
		}
		else
		{
			break;
		}
	}
	return u32BytesDone;
}
//--------------------------------------------------------------------------
class VeAudioStreamOgg : public VeAudioStream
{
public:
	VeAudioStreamOgg(const VeBinaryIStreamPtr& spStream)
		: VeAudioStream(spStream), m_pcBuffer(NULL)
		, m_u32StartSize(0), m_u32Pointer(0)
		, m_u32CurrentSize(0)
	{

	}

	virtual ~VeAudioStreamOgg()
	{
		if(IsPrepared())
		{
			VE_ASSERT(m_pcBuffer);
			VeFree(m_pcBuffer);
			m_pcBuffer = NULL;
			ov_clear(&m_kFile);
			m_u32ChannelNum = 0;
		}
	}

	void _Prepare()
	{
		if(ov_open_callbacks(m_spStream, &m_kFile, NULL, 0, s_kVorbisCallback) == 0)
		{
			vorbis_info* pkVorbisInfo = ov_info(&m_kFile, -1);
			VE_ASSERT(pkVorbisInfo);
			VE_ASSERT(pkVorbisInfo->channels == 1 || pkVorbisInfo->channels == 2);
			m_u32ChannelNum = pkVorbisInfo->channels;
			m_u32SampleRate = VeUInt32(pkVorbisInfo->rate);
			m_u32BitsPerSample = 16;
			m_u32FixedBufferSize = (m_u32ChannelNum == 1)
				? ((m_u32SampleRate >> 1) & 0xFFFFFFFE)
				: (m_u32SampleRate & 0xFFFFFFFC);
			m_pcBuffer = VeAlloc(VeChar8, m_u32FixedBufferSize * (VE_MAX_QUEUE_NUM + 1));
			m_u32StartSize = VeDecodeOggVorbis(&m_kFile, m_pcBuffer, m_u32FixedBufferSize * VE_MAX_QUEUE_NUM);
			m_u32Pointer = 0;
			m_u32CurrentSize = 0;
		}
	}

	void _Tick(bool bLoop)
	{
		if(m_u32Pointer >= VE_MAX_QUEUE_NUM)
		{
			m_u32CurrentSize = VeDecodeOggVorbis(&m_kFile, m_pcBuffer + m_u32FixedBufferSize * VE_MAX_QUEUE_NUM, m_u32FixedBufferSize);
			if((!m_u32CurrentSize) && bLoop)
			{
				ov_pcm_seek(&m_kFile, m_u32FixedBufferSize * VE_MAX_QUEUE_NUM / (m_u32ChannelNum << 1));
				m_u32Pointer = 0;
			}
		}
	}

	virtual void Prepare()
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		if(!IsPrepared())
		{
			_Prepare();
		}
	}

	virtual void* Tick(VeUInt32& u32BufferSize, bool bLoop)
	{
		VE_AUTO_LOCK_MUTEX(m_kMutex);
		if(IsPrepared())
		{
			_Tick(bLoop);
		}
		else
		{
			_Prepare();
		}
		if(IsPrepared())
		{
			if(m_u32Pointer < VE_MAX_QUEUE_NUM)
			{
				VeUInt32 u32Offset = m_u32FixedBufferSize * (m_u32Pointer++);
				if(m_u32StartSize >= (m_u32FixedBufferSize + u32Offset))
				{
					u32BufferSize = m_u32FixedBufferSize;
				}
				else if(m_u32StartSize >= u32Offset)
				{
					u32BufferSize = m_u32StartSize - u32Offset;
				}
				else
				{
					VE_ASSERT(!"Unknown error");
				}
				if(m_u32Pointer < VE_MAX_QUEUE_NUM)
				{
					if(m_u32StartSize <= (m_u32FixedBufferSize * m_u32Pointer))
					{
						m_u32Pointer = 0;
					}
				}
				return m_pcBuffer + u32Offset;
			}
			else
			{
				u32BufferSize = m_u32CurrentSize;
				return m_pcBuffer + m_u32FixedBufferSize * VE_MAX_QUEUE_NUM;
			}
		}
		else
		{
			u32BufferSize = 0;
			return NULL;
		}
	}

protected:
	VeThread::Mutex m_kMutex;
	OggVorbis_File m_kFile;
	VeChar8* m_pcBuffer;
	VeUInt32 m_u32StartSize;
	VeUInt32 m_u32Pointer;
	VeUInt32 m_u32CurrentSize;

};
//--------------------------------------------------------------------------
VeAudioStream::VeAudioStream(const VeBinaryIStreamPtr& spStream)
	: m_u32ChannelNum(0), m_u32SampleRate(0), m_u32BitsPerSample(0)
	, m_u32FixedBufferSize(0), m_spStream(spStream)
{

}
//--------------------------------------------------------------------------
VeAudioStream::~VeAudioStream()
{

}
//--------------------------------------------------------------------------
VeAudioStreamPtr VeAudioStream::Create(const VeChar8* pcName,
	const VeChar8* pcPath)
{
	const VeChar8* pcExt = VeStrrchr(pcName, '.');
	if(VeStricmp(pcExt, ".ogg") == 0)
	{
		VeDirectory* pkDir = g_pResourceManager->CreateDir(pcPath);
		VE_ASSERT(pkDir && pkDir->HasFile(pcName));
		VeBinaryIStreamPtr spStream = pkDir->OpenSync(pcName);
		g_pResourceManager->DestoryDir(pkDir);
		return VE_NEW VeAudioStreamOgg(spStream);
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
