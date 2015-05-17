////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBinaryStream.inl
//  Version:     v1.00
//  Created:     6/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
#ifdef VE_BIG_ENDIAN
//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VE_HTONS(VeUInt16 x)
{
	VeUInt16 res = ((x & 0x00ff) << 8) | ((x & 0xff00) >> 8);
	return res;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VE_HTONL(VeUInt32 x)
{
	VeUInt32 res = ((x & 0x000000ff) << 24) | ((x & 0x0000ff00) << 8)
		| ((x & 0x00ff0000) >> 8) | ((x & 0xff000000) >> 24);
	return res;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt64 VE_HTONLL(VeUInt64 x)
{
	VeUInt64 res =
		((x & 0x00000000000000ffULL) << 56) |
		((x & 0x000000000000ff00ULL) << 40) |
		((x & 0x0000000000ff0000ULL) << 24) |
		((x & 0x00000000ff000000ULL) << 8) |
		((x & 0x000000ff00000000ULL) >> 8) |
		((x & 0x0000ff0000000000ULL) >> 24) |
		((x & 0x00ff000000000000ULL) >> 40) |
		((x & 0xff00000000000000ULL) >> 56);
	return res;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VE_HTONF(VeFloat32 f)
{
	VeNetLong n;
	n.f32 = f;
	n.u32 = VE_HTONL(n.u32);
	return n.f32;
}
//--------------------------------------------------------------------------
VE_INLINE void VE_HTONF_ASSIGN(VeFloat32& dest, VeFloat32 f)
{
	VeNetLong temp;
	temp.f32 = f;
	temp.u32 = VE_HTONL(temp.u32);
	dest = temp.f32;
}
//--------------------------------------------------------------------------
VE_INLINE void VE_HTON3_ASSIGN(VeChar8* pcDest, const VeChar8* pcData)
{
	pcDest[0] = pcData[2];
	pcDest[1] = pcData[1];
	pcDest[2] = pcData[0];
}
//--------------------------------------------------------------------------
VE_INLINE void VE_PACK3(VeChar8* pcDest, VeUInt32 u32Src)
{
	pcDest[0] = (VeChar8)(u32Src >> 16);
	pcDest[1] = (VeChar8)(u32Src >> 8);
	pcDest[2] = (VeChar8)u32Src;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VE_UNPACK3(const VeChar8* pcData)
{
	const VeUInt8* pu8Data = (const VeUInt8*)pcData;
	return (pu8Data[0] << 16) | (pu8Data[1] << 8) | pu8Data[2];
}
//--------------------------------------------------------------------------
#else
//--------------------------------------------------------------------------
VE_INLINE void VE_HTON3_ASSIGN(VeChar8* pcDest, const VeChar8* pcData)
{
	pcDest[0] = pcData[0];
	pcDest[1] = pcData[1];
	pcDest[2] = pcData[2];
}
//--------------------------------------------------------------------------
VE_INLINE void VE_PACK3(VeChar8* pcDest, VeUInt32 u32Src)
{
	pcDest[0] = (VeChar8)u32Src;
	pcDest[1] = (VeChar8)(u32Src >> 8);
	pcDest[2] = (VeChar8)(u32Src >> 16);
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VE_UNPACK3(const VeChar8* pcData)
{
	const VeUInt8* pu8Data = (const VeUInt8*)pcData;
	return pu8Data[0] | (pu8Data[1] << 8) | (pu8Data[2] << 16);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeBinaryOStream::CalculatePackedIntSize(VeInt32 i32Value)
{
	return (i32Value >= 0xFF) ? 4 : 1;
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeBinaryIStream::ReadStringLength()
{
	return ReadPackedInt();
}
//--------------------------------------------------------------------------
VE_INLINE bool VeBinaryIStream::IsError() const
{
	return m_bError;
}
//--------------------------------------------------------------------------
VE_INLINE void VeBinaryIStream::SetError(bool bError)
{
	m_bError = bError;
}
//--------------------------------------------------------------------------
