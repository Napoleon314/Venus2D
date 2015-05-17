////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemoryStream.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeBlob::VeBlob() : m_pvBuffer(NULL), m_u32BufferSize(0)
{

}
//--------------------------------------------------------------------------
VE_INLINE VeBlob::VeBlob(VeUInt32 u32Size) : m_pvBuffer(NULL),
	m_u32BufferSize(u32Size)
{
	VE_ASSERT(VeInt32(u32Size) >= 0);
	if(m_u32BufferSize)
	{
		m_pvBuffer = VeMalloc(m_u32BufferSize + 1);
		((VeChar8*)m_pvBuffer)[m_u32BufferSize] = 0;
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeBlob::VeBlob(void* pvBuffer, VeUInt32 u32Size) : m_pvBuffer(pvBuffer),
	m_u32BufferSize(u32Size)
{
	VE_ASSERT(VeInt32(u32Size) > 0);
	m_u32BufferSize |= 0x80000000;
}
//--------------------------------------------------------------------------
VE_INLINE VeBlob::~VeBlob()
{
	if(m_pvBuffer && ((m_u32BufferSize & 0x80000000) == 0))
	{
		VeFree(m_pvBuffer);
		m_pvBuffer = NULL;
	}
	m_u32BufferSize = 0;
}
//--------------------------------------------------------------------------
VE_INLINE VeBlob::operator void* ()
{
	return m_pvBuffer;
}
//--------------------------------------------------------------------------
VE_INLINE void* VeBlob::GetBuffer()
{
	return m_pvBuffer;
}
//--------------------------------------------------------------------------
VE_INLINE void* VeBlob::GetBuffer(VeUInt32 u32Pointer)
{
	VE_ASSERT(u32Pointer < m_u32BufferSize);
	return (VeByte*)(m_pvBuffer) + u32Pointer;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeBlob::GetSize()
{
	return m_u32BufferSize & 0x7FFFFFFF;
}
//--------------------------------------------------------------------------
VE_INLINE VeMemoryOStream::VeMemoryOStream(VeUInt32 u32Size)
	: m_u32Curr(0), m_u32Read(0)
{
	m_spBlob = VE_NEW VeBlob(u32Size);
}
//--------------------------------------------------------------------------
VE_INLINE VeMemoryOStream::VeMemoryOStream(const VeBlobPtr& spBlob)
	: m_u32Curr(0), m_u32Read(0)
{
	m_spBlob = spBlob;
}
//--------------------------------------------------------------------------
VE_INLINE void* VeMemoryOStream::GetData()
{
	return m_spBlob->GetBuffer();
}
//--------------------------------------------------------------------------
VE_INLINE void* VeMemoryOStream::GetDataForRead()
{
	return m_spBlob->GetBuffer(m_u32Read);
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeMemoryOStream::AfterReadData(VeInt32 i32Bytes)
{
	i32Bytes = i32Bytes > 0 ? i32Bytes : 0;
	i32Bytes = VE_MIN(RemainingLength(), i32Bytes);
	m_u32Read += i32Bytes;
	return i32Bytes;
}
//--------------------------------------------------------------------------
VE_INLINE const VeBlobPtr& VeMemoryOStream::GetBlob()
{
	return m_spBlob;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMemoryOStream::Reset()
{
	m_u32Curr = m_u32Read = 0;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMemoryOStream::Rewind()
{
	m_u32Read = 0;
}
//--------------------------------------------------------------------------
VE_INLINE VeMemoryIStream::VeMemoryIStream(const VeBlobPtr& spBlob)
	: m_spBlob(spBlob), m_u32Curr(0)
{

}
//--------------------------------------------------------------------------
VE_INLINE const void* VeMemoryIStream::GetData() const
{
	return m_spBlob->GetBuffer(m_u32Curr);
}
//--------------------------------------------------------------------------
VE_INLINE const VeBlobPtr& VeMemoryIStream::GetBlob()
{
	return m_spBlob;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMemoryIStream::Reset()
{
	m_u32Curr = 0;
}
//--------------------------------------------------------------------------
VE_INLINE VeMessageStream::VeMessageStream(VeUInt32 u32Size)
	: VeMemoryOStream(u32Size)
{

}
//--------------------------------------------------------------------------
