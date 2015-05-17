////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioData.inl
//  Version:     v1.00
//  Created:     28/7/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioSampleData::GetChannelNum()
{
	return m_u32ChannelNum;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioSampleData::GetSampleRate()
{
	return m_u32SampleRate;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioSampleData::GetBitsPerSample()
{
	return m_u32BitsPerSample;
}
//--------------------------------------------------------------------------
VE_INLINE const VeBlobPtr& VeAudioSampleData::GetData()
{
	return m_spData;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioStream::GetChannelNum()
{
	return m_u32ChannelNum;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioStream::GetSampleRate()
{
	return m_u32SampleRate;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioStream::GetBitsPerSample()
{
	return m_u32BitsPerSample;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeAudioStream::GetFixedBufferSize()
{
	return m_u32FixedBufferSize;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeAudioStream::IsPrepared()
{
	return m_u32ChannelNum ? true :false;
}
//--------------------------------------------------------------------------
