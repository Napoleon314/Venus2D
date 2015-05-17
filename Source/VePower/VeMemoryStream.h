////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMemoryStream.h
//  Version:     v1.00
//  Created:     29/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeBlob : public VeRefObject
{
public:
	VE_INLINE VeBlob();

	VE_INLINE VeBlob(VeUInt32 u32Size);

	VE_INLINE VeBlob(void* pvBuffer, VeUInt32 u32Size);

	VE_INLINE ~VeBlob();

	VE_INLINE operator void* ();

	VE_INLINE void* GetBuffer();

	VE_INLINE void* GetBuffer(VeUInt32 u32Pointer);

	VE_INLINE VeUInt32 GetSize();

	void AddSize(VeUInt32 u32Size);

protected:
	void* m_pvBuffer;
	VeUInt32 m_u32BufferSize;
};

VeSmartPointer(VeBlob);

class VE_POWER_API VeMemoryOStream : public VeBinaryOStream, public VeBinaryIStream
{
public:
	VE_INLINE VeMemoryOStream(VeUInt32 u32Size = 64);

	VE_INLINE VeMemoryOStream(const VeBlobPtr& spBlob);

	virtual ~VeMemoryOStream();

	virtual VeInt32 Write(const void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Size() const;

	virtual VeInt32 Read(void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Seek(VeInt32 i32Offset, VeWhence eWhence);

	virtual VeInt32 Tell();

	virtual void* Skip(VeInt32 i32Bytes);

	virtual void Restart();

	virtual VeInt32 RemainingLength() const;

	virtual VeChar8 Peek();

	VE_INLINE void* GetData();

	VE_INLINE void* GetDataForRead();

	VE_INLINE VeInt32 AfterReadData(VeInt32 i32Bytes);

	VE_INLINE const VeBlobPtr& GetBlob();

	VE_INLINE void Reset();

	VE_INLINE void Rewind();

	virtual VeBinaryIStream* ToBinaryIStream();

	virtual const VeBinaryIStream* ToBinaryIStream() const;

	virtual VeBinaryOStream* ToBinaryOStream();

	virtual const VeBinaryOStream* ToBinaryOStream() const;

protected:

	VeMemoryOStream(const VeMemoryOStream& kStream);

	VeMemoryOStream& operator = (const VeMemoryOStream& kStream);

	VeBlobPtr m_spBlob;
	VeUInt32 m_u32Curr;
	VeUInt32 m_u32Read;
};

VeSmartPointer(VeMemoryOStream);

class VE_POWER_API VeMemoryIStream : public VeBinaryIStream
{
public:
	VE_INLINE VeMemoryIStream(const VeBlobPtr& spBlob);

	virtual ~VeMemoryIStream();

	virtual VeInt32 Read(void* pvBuffer, VeInt32 i32Bytes);

	virtual VeInt32 Seek(VeInt32 i32Offset, VeWhence eWhence);

	virtual VeInt32 Tell();

	virtual void* Skip(VeInt32 i32Bytes);

	virtual void Restart();

	virtual VeInt32 RemainingLength() const;

	virtual VeChar8 Peek();

	virtual void Finish();

	VE_INLINE const void* GetData() const;

	VE_INLINE const VeBlobPtr& GetBlob();

	VE_INLINE void Reset();

protected:
	VeBlobPtr m_spBlob;
	VeUInt32 m_u32Curr;

};

VeSmartPointer(VeMemoryIStream);

class VE_POWER_API VeMessageStream : public VeMemoryOStream
{
public:
	VE_INLINE VeMessageStream(VeUInt32 u32Size = 64);

	virtual ~VeMessageStream();

	bool AddToStream(VeBinaryOStream& kStream, VeUInt8 u8MessageID);

	bool GetMessage(VeBinaryIStream& kStream, VeUInt32& u32MessageID, VeInt32& i32Length);
};

VeSmartPointer(VeMessageStream);

#ifndef VE_NO_INLINE
#	include "VeMemoryStream.inl"
#endif
