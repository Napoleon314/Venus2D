////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBinaryStream.cpp
//  Version:     v1.00
//  Created:     28/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeBinaryStream.inl"
#endif

//--------------------------------------------------------------------------
VeBinaryOStream::VeBinaryOStream()
{

}
//--------------------------------------------------------------------------
VeBinaryOStream::~VeBinaryOStream()
{

}
//--------------------------------------------------------------------------
VeBinaryIStream* VeBinaryOStream::ToBinaryIStream()
{
	return NULL;
}
//--------------------------------------------------------------------------
const VeBinaryIStream* VeBinaryOStream::ToBinaryIStream() const
{
	return NULL;
}
//--------------------------------------------------------------------------
VeInt32 VeBinaryOStream::Size() const
{
	return VE_ELF;
}
//--------------------------------------------------------------------------
void VeBinaryOStream::AppendString(const VeChar8* pcData, VeInt32 i32Length)
{
	VE_ASSERT(i32Length > 0);
	WritePackedInt(i32Length);
	AddBlob(pcData, i32Length);
}
//--------------------------------------------------------------------------
void VeBinaryOStream::AppendStringAligned4(const VeChar8* pcData, VeInt32 i32Length)
{
	VE_ASSERT(i32Length > 0);
	WritePackedInt(i32Length);
	AddBlob(pcData, i32Length);
	VeUInt32 u32Temp = (i32Length >= 255) ? 4 : 1;
	u32Temp += i32Length;
	u32Temp = ((u32Temp + 3) & 0xfffffffc) - u32Temp;
	if(u32Temp)
	{
		VeUInt32 u32Zero = 0;
		AddBlob(&u32Zero, u32Temp);
	}
}
//--------------------------------------------------------------------------
void VeBinaryOStream::Transfer(VeBinaryIStream& kFrom, VeInt32 i32Length)
{
	VE_ASSERT(i32Length > 0);
	void* pvBuffer = VeMalloc(i32Length);
	VE_ASSERT_EQ(kFrom.Read(pvBuffer, i32Length), i32Length);
	AddBlob(pvBuffer, i32Length);
	VeFree(pvBuffer);
}
//--------------------------------------------------------------------------
void VeBinaryOStream::AddBlob(const void* pvBlob, VeInt32 i32Size)
{
	VE_ASSERT(i32Size > 0);
	VE_ASSERT_EQ(Write(pvBlob, i32Size), i32Size);
}
//--------------------------------------------------------------------------
void VeBinaryOStream::WritePackedInt(VeInt32 i32Value)
{
	VE_ASSERT(((VeUInt32)i32Value) <= VE_MAX_LENGTH);
	if(i32Value >= 255)
	{
		(*this) << (VeUInt8)0xFF;
		VeChar8 acValue[3];
		VE_PACK3(acValue, i32Value);
		VE_ASSERT_EQ(Write(acValue, sizeof(acValue)), sizeof(acValue));
	}
	else
	{
		(*this) << (VeUInt8)i32Value;
	}
}
//--------------------------------------------------------------------------
void VeBinaryOStream::WriteStringLength(VeInt32 i32Length)
{
	WritePackedInt(i32Length);
}
//--------------------------------------------------------------------------
VeBinaryIStream::VeBinaryIStream() : m_bError(false)
{

}
//--------------------------------------------------------------------------
VeBinaryIStream::~VeBinaryIStream()
{

}
//--------------------------------------------------------------------------
VeBinaryOStream* VeBinaryIStream::ToBinaryOStream()
{
	return NULL;
}
//--------------------------------------------------------------------------
const VeBinaryOStream* VeBinaryIStream::ToBinaryOStream() const
{
	return NULL;
}
//--------------------------------------------------------------------------
void VeBinaryIStream::Finish()
{

}
//--------------------------------------------------------------------------
void VeBinaryIStream::GetStringAligned4(VeString& kStr)
{
	VeInt32	i32Length = ReadPackedInt();
	if(i32Length)
	{
		kStr = VeString('0', i32Length);
		VE_ASSERT_EQ(Read(kStr.GetString(), i32Length), i32Length);
	}
	else
	{
		kStr = "";
	}
	VeUInt32 u32Temp = (i32Length >= 255) ? 4 : 1;
	u32Temp += i32Length;
	u32Temp = ((u32Temp + 3) & 0xfffffffc) - u32Temp;
	if(u32Temp)
	{
		VeUInt32 u32Zero = 0;
		Read(&u32Zero, u32Temp);
	}
}
//--------------------------------------------------------------------------
VeString VeBinaryIStream::GetStringAligned4()
{
	VeString kRes;
	GetStringAligned4(kRes);
	return kRes;
}
//--------------------------------------------------------------------------
VeInt32 VeBinaryIStream::ReadPackedInt()
{
	VeUInt8 u8Len;
	VE_ASSERT_EQ(Read(&u8Len, 1), 1);

	VeInt32 i32Value = u8Len;

	if(i32Value == 0xFF)
	{
		VeChar8 acBuffer[3];
		VE_ASSERT_EQ(Read(acBuffer, 3), 3);
		i32Value = VE_UNPACK3(acBuffer);
	}

	return i32Value;
}
//--------------------------------------------------------------------------
