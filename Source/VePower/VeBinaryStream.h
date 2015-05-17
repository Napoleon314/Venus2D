////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeBinaryStream.h
//  Version:     v1.00
//  Created:     28/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_BS_BUFF_MAX_SIZE (2048)
#define VE_MAX_LENGTH (0xFFFFFF)

class VeBinaryIStream;

#define VE_ISTREAM_FRIEND_DECLARE														\
	template<class T>																	\
	friend VeBinaryIStream& operator >> (VeBinaryIStream&, T&)
#define VE_OSTREAM_FRIEND_DECLARE														\
	template<class T>																	\
	friend VeBinaryOStream& operator << (VeBinaryOStream&, const T&)
#define VE_IOSTREAM_FRIEND_DECLARE														\
	VE_ISTREAM_FRIEND_DECLARE;															\
	VE_OSTREAM_FRIEND_DECLARE

#define VE_ISTREAM_DECLARE(_PREFIX, _TYPE)												\
	template<>																			\
	_PREFIX VeBinaryIStream& operator >> (VeBinaryIStream&, _TYPE&)
#define VE_OSTREAM_DECLARE(_PREFIX, _TYPE)												\
	template<>																			\
	_PREFIX VeBinaryOStream& operator << (VeBinaryOStream&, const _TYPE&)
#define VE_IOSTREAM_DECLARE(_PREFIX, _TYPE)												\
	VE_ISTREAM_DECLARE(_PREFIX, _TYPE);													\
	VE_OSTREAM_DECLARE(_PREFIX, _TYPE)

#define VE_ISTREAM_IMP_BY_MEMCPY(_PREFIX, _TYPE)										\
	template<>																			\
	_PREFIX VeBinaryIStream& operator >> (VeBinaryIStream& kIS, _TYPE& kDes)			\
	{																					\
		VE_ASSERT_EQ(kIS.Read(&kDes, sizeof(_TYPE)), sizeof(_TYPE));					\
		return kIS;																		\
	}
#define VE_OSTREAM_IMP_BY_MEMCPY(_PREFIX, _TYPE)										\
	template<>																			\
	_PREFIX VeBinaryOStream& operator << (VeBinaryOStream& kOS, const _TYPE& kSrc)		\
	{																					\
		VE_ASSERT_EQ(kOut.Write(&kSrc, sizeof(_TYPE)), sizeof(_TYPE));					\
		return kOS;																		\
	}
#define VE_IOSTREAM_IMP_BY_MEMCPY(_PREFIX, _TYPE)										\
	VE_ISTREAM_IMP_BY_MEMCPY(_PREFIX, _TYPE)											\
	VE_OSTREAM_IMP_BY_MEMCPY(_PREFIX, _TYPE)

enum VeWhence
{
	VE_SEEK_SET = 0,
	VE_SEEK_CUR = 1,
	VE_SEEK_END = 2
};

class VE_POWER_API VeBinaryOStream : virtual public VeRefObject
{
public:
	VeBinaryOStream();

	virtual ~VeBinaryOStream();

	virtual VeBinaryIStream* ToBinaryIStream();

	virtual const VeBinaryIStream* ToBinaryIStream() const;

	virtual VeInt32 Write(const void* pvBuffer, VeInt32 i32Bytes) = 0;

	virtual VeInt32 Size() const;
	
	void AppendString(const VeChar8* pcData, VeInt32 i32Length);

	void AppendStringAligned4(const VeChar8* pcData, VeInt32 i32Length);

	void Transfer(VeBinaryIStream& kFrom, VeInt32 i32Length);

	virtual void AddBlob(const void* pvBlob, VeInt32 i32Size);

	template <class T>
	void InsertRaw(const T& t)
	{
		VE_ASSERT_EQ(Write(&t, sizeof(T)), sizeof(T));
	}

	void WritePackedInt(VeInt32 i32Value);

	void WriteStringLength(VeInt32 i32Length);

	VE_INLINE static VeInt32 CalculatePackedIntSize(VeInt32 i32Value);

};

VeSmartPointer(VeBinaryOStream);

class VE_POWER_API VeBinaryIStream : virtual public VeRefObject
{
public:
	VeBinaryIStream();

	virtual ~VeBinaryIStream();

	virtual VeBinaryOStream* ToBinaryOStream();

	virtual const VeBinaryOStream* ToBinaryOStream() const;

	virtual VeInt32 Read(void* pvBuffer, VeInt32 i32Bytes) = 0;

	virtual VeInt32 Seek(VeInt32 i32Offset, VeWhence eWhence) = 0;

	virtual VeInt32 Tell() = 0;

	virtual void* Skip(VeInt32 i32Bytes) = 0;

	virtual void Restart() = 0;

	virtual VeInt32 RemainingLength() const = 0;

	virtual void Finish();

	virtual VeChar8 Peek() = 0;

	void GetStringAligned4(VeString& kStr);

	VeString GetStringAligned4();

	template <class T>
	void ExtractRaw(T& t)
	{
		VE_ASSERT_EQ(Read(&t, sizeof(T)), sizeof(T));
	}

	VeInt32 ReadPackedInt();

	VE_INLINE VeInt32 ReadStringLength();

	VE_INLINE bool IsError() const;

	static VeChar8 ms_abErrBuf[VE_BS_BUFF_MAX_SIZE];

protected:
	VE_INLINE void SetError(bool bError);

	bool m_bError;

};

VeSmartPointer(VeBinaryIStream);

typedef union
{
	VeUInt8 u8;
	VeInt8 i8;
	VeChar8 c8;
	bool b;
} VeNetByte;

typedef union
{
	VeUInt16 u16;
	VeInt16 i16;
} VeNetShort;


typedef union
{
	VeUInt32 u32;
	VeInt32 i32;
	VeFloat32 f32;
} VeNetLong;


typedef union
{
	VeUInt64 u64;
	VeInt64 i64;
	VeFloat64 f64;
} VeNetLongLong;

#ifdef VE_BIG_ENDIAN

VeUInt16 VE_HTONS(VeUInt16 x);

VeUInt32 VE_HTONL(VeUInt32 x);

VeUInt64 VE_HTONLL(VeUInt64 x);

VeFloat32 VE_HTONF(VeFloat32 f);

void VE_HTONF_ASSIGN(VeFloat32& dest, VeFloat32 f);

void VE_HTON3_ASSIGN(VeChar8* pcDest, const VeChar8* pcData);

void VE_PACK3(VeChar8* pcDest, VeUInt32 u32Src);

VeUInt32 VE_UNPACK3(const VeChar8* pcData);

#else

#define VE_HTONS(x) (x)
#define VE_HTONL(x) (x)
#define VE_HTONLL(x) (x)
#define VE_HTONF(x) (x)
#define VE_HTONF_ASSIGN(dest,x) (dest=x)

void VE_HTON3_ASSIGN(VeChar8* pcDest, const VeChar8* pcData);

void VE_PACK3(VeChar8* pcDest, VeUInt32 u32Src);

VeUInt32 VE_UNPACK3(const VeChar8* pcData);

#endif

#define VE_NTOHS(x) VE_HTONS(x)
#define VE_NTOHL(x) VE_HTONL(x)
#define VE_NTOHLL(x) VE_HTONLL(x)
#define VE_NTOHF(x) VE_HTONF(x)
#define VE_NTOHF_ASSIGN(dest,x) VE_HTONF_ASSIGN(dest,x)
#define VE_NTOH3_ASSIGN(dest,data) VE_HTON3_ASSIGN(dest,data)

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeNetByte kData)
{
	VE_ASSERT(sizeof(VeNetByte) == 1);
	VE_ASSERT_EQ(kOut.Write(&kData, sizeof(kData)), sizeof(kData));
	return kOut;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeNetShort kData)
{
	VE_ASSERT(sizeof(VeNetShort) == 2);
	kData.u16 = VE_HTONS(kData.u16);
	VE_ASSERT_EQ(kOut.Write(&kData, sizeof(kData)), sizeof(kData));
	return kOut;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeNetLong kData)
{
	VE_ASSERT(sizeof(VeNetLong) == 4);
	kData.u32 = VE_HTONL(kData.u32);
	VE_ASSERT_EQ(kOut.Write(&kData, sizeof(kData)), sizeof(kData));
	return kOut;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeNetLongLong kData)
{
	VE_ASSERT(sizeof(VeNetLongLong) == 8);
	kData.u64 = VE_HTONLL(kData.u64);
	VE_ASSERT_EQ(kOut.Write(&kData, sizeof(kData)), sizeof(kData));
	return kOut;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeUInt8 x)
{
	VeNetByte n;
	n.u8 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeUInt16 x)
{
	VeNetShort n;
	n.u16 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeUInt32 x)
{
	VeNetLong n;
	n.u32 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeUInt64 x)
{
	VeNetLongLong n;
	n.u64 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeInt8 x)
{
	VeNetByte n;
	n.i8 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeInt16 x)
{
	VeNetShort n;
	n.i16 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeInt32 x)
{
	VeNetLong n;
	n.i32 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeInt64 x)
{
	VeNetLongLong n;
	n.i64 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, bool x)
{
	VeNetByte n;
	n.b = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeFloat32 x)
{
	VeNetLong n;
	n.f32 = x;
	return kOut << n;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeFloat64 x)
{
	VeNetLongLong n;
	n.f64 = x;
	return kOut << n;
}

#ifndef VE_BIG_ENDIAN

template <class T>
VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, const T& t)
{
	kOut.InsertRaw(t);
	return kOut;
}

#endif

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, const VeString& kStr)
{
	kOut.AppendString(kStr, (VeInt32)(kStr.Length()));
	return kOut;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, const VeFixedString& kStr)
{
	kOut.AppendString(kStr, (VeInt32)(kStr.GetLength()));
	return kOut;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, VeChar8* pcStr)
{
	kOut.AppendString(pcStr, (VeInt32)(VeStrlen(pcStr)));
	return kOut;
}

VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, const VeChar8* pcStr)
{
	kOut.AppendString(pcStr, (VeInt32)(VeStrlen(pcStr)));
	return kOut;
}

template<class type1, class type2>
VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, const VePair<type1,type2>& kData)
{
	kOut << kData.m_tFirst;
	kOut << kData.m_tSecond;
	return kOut;
}

template <class T>
VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, const VeVector<T>& kData)
{
    kOut << kData.Size();
	for(VeUInt32 i(0); i < kData.Size(); ++i)
		kOut << kData[i];
	return kOut;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeNetByte& kData)
{
	VE_ASSERT(sizeof(VeNetByte) == 1);
	VE_ASSERT_EQ(kIn.Read(&kData, sizeof(kData)), sizeof(kData));
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeNetShort& kData)
{
	VE_ASSERT(sizeof(VeNetShort) == 2);
	VE_ASSERT_EQ(kIn.Read(&kData, sizeof(kData)), sizeof(kData));
	kData.u16 = VE_NTOHS(kData.u16);
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeNetLong& kData)
{
	VE_ASSERT(sizeof(VeNetLong) == 4);
	VE_ASSERT_EQ(kIn.Read(&kData, sizeof(kData)), sizeof(kData));
	kData.u32 = VE_NTOHL(kData.u32);
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeNetLongLong& kData)
{
	VE_ASSERT(sizeof(VeNetLongLong) == 8);
	VE_ASSERT_EQ(kIn.Read(&kData, sizeof(kData)), sizeof(kData));
	kData.u64 = VE_NTOHLL(kData.u64);
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeUInt8& x)
{
	VeNetByte n;
	kIn >> n;
	x = n.u8;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeUInt16& x)
{
	VeNetShort n;
	kIn >> n;
	x = n.u16;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeUInt32& x)
{
	VeNetLong n;
	kIn >> n;
	x = n.u32;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeUInt64& x)
{
	VeNetLongLong n;
	kIn >> n;
	x = n.u64;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeInt8& x)
{
	VeNetByte n;
	kIn >> n;
	x = n.i8;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeInt16& x)
{
	VeNetShort n;
	kIn >> n;
	x = n.i16;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeInt32& x)
{
	VeNetLong n;
	kIn >> n;
	x = n.i32;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeInt64& x)
{
	VeNetLongLong n;
	kIn >> n;
	x = n.i64;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, bool& x)
{
	VeNetByte n;
	kIn >> n;
	x = n.b;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeFloat32& x)
{
	VeNetLong n;
	kIn >> n;
	x = n.f32;
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeFloat64& x)
{
	VeNetLongLong n;
	kIn >> n;
	x = n.f64;
	return kIn;
}

#ifndef VE_BIG_ENDIAN

template <class T>
VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, T& t)
{
	kIn.ExtractRaw(t);
	return kIn;
}

#endif

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeString& kStr)
{
	VeInt32	i32Length = kIn.ReadPackedInt();
	if(i32Length)
	{
		kStr = VeString('0', i32Length);
		VE_ASSERT_EQ(kIn.Read(kStr.GetString(), i32Length), i32Length);
	}
	else
	{
		kStr = "";
	}
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeFixedString& kStr)
{
	VeInt32	i32Length = kIn.ReadPackedInt();
	if(i32Length)
	{
		VeChar8* pcBuffer = VeAlloc(VeChar8, i32Length + 1);
		VE_ASSERT_EQ(kIn.Read(pcBuffer, i32Length), i32Length);
		pcBuffer[i32Length] = '\0';
		kStr = pcBuffer;
        VeFree(pcBuffer);
	}
	else
	{
		kStr = "";
	}
	return kIn;
}

VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeChar8* pcStr)
{
	VeInt32	i32Length = kIn.ReadPackedInt();
	if(i32Length)
	{
		VE_ASSERT_EQ(kIn.Read(pcStr, i32Length), i32Length);
	}
	else
	{
		pcStr[0] = '\0';
	}
	return kIn;
}

template<class type1, class type2>
VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VePair<type1,type2>& kData)
{
	kIn >> kData.m_tFirst;
	kIn >> kData.m_tSecond;
	return kIn;
}

template <class T>
VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, VeVector<T>& kData)
{
	VeUInt32 u32Size;
	kIn >> u32Size;
	kData.Resize(u32Size);
	for(VeUInt32 i(0); i < u32Size; ++i)
	{
		kIn >> kData[i];
	}
	return kIn;
}

#ifndef VE_NO_INLINE
#	include "VeBinaryStream.inl"
#endif
