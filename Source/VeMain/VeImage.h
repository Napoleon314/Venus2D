////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeImage.h
//  Version:     v1.00
//  Created:     18/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

VeSmartPointer(VeImage);

class VE_MAIN_API VeImage : public VeObject
{
	VeDeclareRTTI;
public:
	enum Type
	{
		TYPE_PNG,
		TYPE_MAX
	};

	enum Tex
	{
		TEX_1D,
		TEX_2D,
		TEX_3D,
		TEX_MAX
	};

	VeImage(Type eType);

	virtual ~VeImage();

	VE_INLINE Type GetType();

	VE_INLINE Tex GetTex();

	VE_INLINE VeUInt16 GetWidth();

	VE_INLINE VeUInt16 GetHeight();

	virtual VeBinaryIStream& GetCreateData() = 0;

	static VeImagePtr CreateImage(VeUInt64 u64CheckHead, VeBinaryIStream& kStream);

protected:
	const Type m_eType;
	Tex m_eTex;
	VeUInt16 m_u16Width;
	VeUInt16 m_u16Height;

};

VeSerializableObject(VeImage);

class VE_MAIN_API VePNGImage : public VeImage
{
	VeDeclareRTTI;
public:
	
	VePNGImage();

	virtual ~VePNGImage();

	virtual VeBinaryIStream& GetCreateData();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

protected:
	VeMemoryOStream m_kStream;

};

VeSerializableObject(VePNGImage);

VeSmartPointer(VePNGImage);

#ifndef VE_NO_INLINE
#	include "VeImage.inl"
#endif
