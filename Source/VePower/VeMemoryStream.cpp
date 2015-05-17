////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemoryStream.cpp
//  Version:     v1.00
//  Created:     29/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeMemoryStream.inl"
#endif

//--------------------------------------------------------------------------
void VeBlob::AddSize(VeUInt32 u32Size)
{
	VE_ASSERT((m_u32BufferSize & 0x80000000) == 0);
	VE_ASSERT(u32Size);
	if(m_pvBuffer)
	{
		m_u32BufferSize += u32Size;
		m_pvBuffer = VeRealloc(m_pvBuffer, m_u32BufferSize + 1);
	}
	else
	{
		m_u32BufferSize = u32Size;
		m_pvBuffer = VeMalloc(m_u32BufferSize + 1);
	}
	((VeChar8*)m_pvBuffer)[m_u32BufferSize] = 0;
}
//--------------------------------------------------------------------------
VeMemoryOStream::VeMemoryOStream(const VeMemoryOStream& kStream)
{
	
}
//--------------------------------------------------------------------------
VeMemoryOStream& VeMemoryOStream::operator = (const VeMemoryOStream& kStream)
{
	return *this;
}
//--------------------------------------------------------------------------
VeMemoryOStream::~VeMemoryOStream()
{
	m_spBlob = NULL;
	m_u32Curr = 0;
	m_u32Read = 0;
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryOStream::Write(const void* pvBuffer, VeInt32 i32Bytes)
{
	if(i32Bytes > 0)
	{
		VeUInt32 u32NewCurr = m_u32Curr + (VeUInt32)i32Bytes;
		if(u32NewCurr > m_spBlob->GetSize())
		{
			VeUInt32 u32AddSize = (u32NewCurr / m_spBlob->GetSize()) * m_spBlob->GetSize();
			m_spBlob->AddSize(u32AddSize);
		}
		VeMemcpy(m_spBlob->GetBuffer(m_u32Curr), pvBuffer, i32Bytes);
		m_u32Curr = u32NewCurr;
		return i32Bytes;
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryOStream::Size() const
{
	return m_u32Curr;
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryOStream::Read(void* pvBuffer, VeInt32 i32Bytes)
{
	if(i32Bytes > 0)
	{
		VeInt32 i32ReadBytes = VE_MIN(RemainingLength(), i32Bytes);
		if(i32ReadBytes > 0)
		{
			VeMemcpy(pvBuffer, GetDataForRead(), i32ReadBytes);
			m_u32Read += i32ReadBytes;
			return i32ReadBytes;
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryOStream::Seek(VeInt32 i32Offset, VeWhence eWhence)
{
	switch(eWhence)
	{
	case VE_SEEK_SET:
		if(i32Offset >= 0 && i32Offset <= VeInt64(m_u32Curr))
		{
			m_u32Read = i32Offset;
			return VE_S_OK;
		}
		break;
	case SEEK_CUR:
		{
			VeInt64 i64After = VeInt64(m_u32Read) + i32Offset;
			if(i64After >= 0 && i64After <= VeInt64(m_u32Curr))
			{
				m_u32Read = VeUInt32(i64After);
				return VE_S_OK;
			}
		}
		break;
	case SEEK_END:
		if(i32Offset >= 0 && i32Offset <= VeInt64(m_u32Curr))
		{
			m_u32Read = (m_u32Curr - i32Offset);
			return VE_S_OK;
		}
		break;
	default:
		break;
	}
	return VE_E_FAIL;
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryOStream::Tell()
{
	return m_u32Read;
}
//--------------------------------------------------------------------------
void* VeMemoryOStream::Skip(VeInt32 i32Bytes)
{
	if(i32Bytes > 0)
	{
		VeInt32 i32ReadBytes = VE_MIN(RemainingLength(), i32Bytes);
		if(i32ReadBytes > 0)
		{
			void* pvBuffer = GetDataForRead();
			m_u32Read += i32ReadBytes;
			return pvBuffer;
		}
		
	}
	return NULL;
}
//--------------------------------------------------------------------------
void VeMemoryOStream::Restart()
{
	Rewind();
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryOStream::RemainingLength() const
{
	return VeInt32(m_u32Curr) - VeInt32(m_u32Read);
}
//--------------------------------------------------------------------------
VeChar8 VeMemoryOStream::Peek()
{
	if(m_u32Read >= m_u32Curr)
	{
		m_bError = true;
		return -1;
	}
	return *(VeChar8*)m_spBlob->GetBuffer(m_u32Read);
}
//--------------------------------------------------------------------------
VeBinaryIStream* VeMemoryOStream::ToBinaryIStream()
{
	return static_cast<VeBinaryIStream*>(this);
}
//--------------------------------------------------------------------------
const VeBinaryIStream* VeMemoryOStream::ToBinaryIStream() const
{
	return static_cast<const VeBinaryIStream*>(this);
}
//--------------------------------------------------------------------------
VeBinaryOStream* VeMemoryOStream::ToBinaryOStream()
{
	return static_cast<VeBinaryOStream*>(this);
}
//--------------------------------------------------------------------------
const VeBinaryOStream* VeMemoryOStream::ToBinaryOStream() const
{
	return static_cast<const VeBinaryOStream*>(this);
}
//--------------------------------------------------------------------------
VeMemoryIStream::~VeMemoryIStream()
{
	VE_ASSERT(m_u32Curr == m_spBlob->GetSize());
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryIStream::Read(void* pvBuffer, VeInt32 i32Bytes)
{
	if(i32Bytes > 0)
	{
		VeInt32 i32ReadBytes = VE_MIN((VeInt32)m_spBlob->GetSize()
			- (VeInt32)m_u32Curr, i32Bytes);
		if(i32ReadBytes > 0)
		{
			VeMemcpy(pvBuffer, m_spBlob->GetBuffer(m_u32Curr), i32ReadBytes);
			m_u32Curr += i32ReadBytes;
			return i32ReadBytes;
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryIStream::Seek(VeInt32 i32Offset, VeWhence eWhence)
{
	switch(eWhence)
	{
	case VE_SEEK_SET:
		if(i32Offset >= 0 && i32Offset <= VeInt64(m_spBlob->GetSize()))
		{
			m_u32Curr = i32Offset;
			return VE_S_OK;
		}
		break;
	case SEEK_CUR:
		{
			VeInt64 i64After = VeInt64(m_u32Curr) + i32Offset;
			if(i64After >= 0 && i64After <= VeInt64(m_spBlob->GetSize()))
			{
				m_u32Curr = VeUInt32(i64After);
				return VE_S_OK;
			}
		}
		break;
	case SEEK_END:
		if(i32Offset >= 0 && i32Offset <= VeInt64(m_spBlob->GetSize()))
		{
			m_u32Curr = m_spBlob->GetSize() - i32Offset;
			return VE_S_OK;
		}
		break;
	default:
		break;
	}
	return VE_E_FAIL;
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryIStream::Tell()
{
	return m_u32Curr;
}
//--------------------------------------------------------------------------
void* VeMemoryIStream::Skip(VeInt32 i32Bytes)
{
	if(i32Bytes > 0)
	{
		VeInt32 i32ReadBytes = VE_MIN((VeInt32)m_spBlob->GetSize()
			- (VeInt32)m_u32Curr, i32Bytes);
		if(i32ReadBytes > 0)
		{
			void* pvBuffer = m_spBlob->GetBuffer(m_u32Curr);
			m_u32Curr += i32ReadBytes;
			return pvBuffer;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
void VeMemoryIStream::Restart()
{
	Reset();
}
//--------------------------------------------------------------------------
VeInt32 VeMemoryIStream::RemainingLength() const
{
	return m_spBlob->GetSize() - m_u32Curr;
}
//--------------------------------------------------------------------------
VeChar8 VeMemoryIStream::Peek()
{
	if (m_u32Curr >= m_spBlob->GetSize())
	{
		m_bError = true;
		return -1;
	}

	return *(VeChar8*)m_spBlob->GetBuffer(m_u32Curr);
}
//--------------------------------------------------------------------------
void VeMemoryIStream::Finish()
{
	m_u32Curr = m_spBlob->GetSize();
}
//--------------------------------------------------------------------------
VeMessageStream::~VeMessageStream()
{

}
//--------------------------------------------------------------------------
bool VeMessageStream::AddToStream(VeBinaryOStream& kStream,
	VeUInt8 u8MessageID)
{
	VeInt32 i32Size = Size();
	VE_ASSERT(i32Size >= 0);

	if(i32Size >= 256)
	{
		return false;
	}

	kStream << u8MessageID << (VeUInt8)i32Size;

	if(i32Size > 0)
	{
		VeChar8 acBuffer[256];
		VE_ASSERT_EQ(Read(acBuffer, i32Size), i32Size);
		VE_ASSERT_EQ(kStream.Write(acBuffer, i32Size), i32Size);
	}	

	Reset();

	return true;
}
//--------------------------------------------------------------------------
bool VeMessageStream::GetMessage(VeBinaryIStream& kStream,
	VeUInt32& u32MessageID, VeInt32& i32Length)
{
	Reset();

	if(i32Length < 2)
	{
		return false;
	}

	VeUInt8 u8Size;
	VeUInt8 u8ID;

	kStream >> u8ID >> u8Size;
	i32Length -= sizeof(u8ID) + sizeof(u8Size);

	u32MessageID = u8ID;

	if(i32Length < (VeInt32)u8Size)
	{
		return false;
	}

	i32Length -= u8Size;

	VeChar8 acBuffer[256];
	VE_ASSERT_EQ(kStream.Read(acBuffer, u8Size), u8Size);
	VE_ASSERT_EQ(Write(acBuffer, u8Size), u8Size);

	return true;
}
//--------------------------------------------------------------------------
