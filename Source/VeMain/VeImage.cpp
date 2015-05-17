////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeImage.cpp
//  Version:     v1.00
//  Created:     18/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeImage.inl"
#endif
#include <png.h>

//--------------------------------------------------------------------------
VeImplementRTTI(VeImage, VeObject);
//--------------------------------------------------------------------------
VeImage::VeImage(Type eType) : m_eType(eType), m_eTex(TEX_MAX)
	, m_u16Width(0), m_u16Height(0)
{

}
//--------------------------------------------------------------------------
VeImage::~VeImage()
{

}
//--------------------------------------------------------------------------
VeImagePtr VeImage::CreateImage(VeUInt64 u64CheckHead,
	VeBinaryIStream& kStream)
{
	VeImagePtr spRes;
	if(VE_SUCCEEDED(png_sig_cmp((png_const_bytep)&u64CheckHead, 0, 8)))
	{
		spRes = VE_NEW VePNGImage;
	}
	else
	{

	}
	if(spRes)
	{
		kStream >> (*spRes);
	}
	return spRes;
}
//--------------------------------------------------------------------------
static void VePngRead(png_structp pkPngPtr, png_bytep pbyData, png_size_t stLength)
{
	VeBinaryIStream& kStream = *(VeBinaryIStream*)png_get_io_ptr(pkPngPtr);
	VE_ASSERT_EQ(kStream.Read(pbyData, VeInt32(stLength)), VeInt32(stLength));
}
//--------------------------------------------------------------------------
VeImplementRTTI(VePNGImage, VeImage);
//--------------------------------------------------------------------------
VePNGImage::VePNGImage() : VeImage(TYPE_PNG)
{

}
//--------------------------------------------------------------------------
VePNGImage::~VePNGImage()
{

}
//--------------------------------------------------------------------------
VeBinaryIStream& VePNGImage::GetCreateData()
{
	m_kStream.Restart();
	return m_kStream;
}
//--------------------------------------------------------------------------
void VePNGImage::From(VeBinaryIStream& kIn)
{
	png_structp pkPngPtr;
	png_infop pkInfoPtr;
	pkPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING,(void *)NULL,NULL,NULL);
	VE_ASSERT(pkPngPtr);
	pkInfoPtr = png_create_info_struct(pkPngPtr);
	VE_ASSERT(pkInfoPtr);
	VE_ASSERT_EQ(setjmp(png_jmpbuf(pkPngPtr)), VE_S_OK);
	png_set_read_fn(pkPngPtr, &kIn, VePngRead);
	png_read_png(pkPngPtr, pkInfoPtr, PNG_TRANSFORM_EXPAND, 0);
	m_u16Width = png_get_image_width(pkPngPtr, pkInfoPtr);
	m_u16Height = png_get_image_height(pkPngPtr, pkInfoPtr);
	VeByte byType = png_get_color_type(pkPngPtr, pkInfoPtr);
	VeByte byDepth = png_get_bit_depth(pkPngPtr, pkInfoPtr);
	VeByte byUnitSize(0), byPixelSize(0);
	VeRenderer::Format eFormat = VeRenderer::FMT_UNKNOWN;
	switch(byType)
	{
	case PNG_COLOR_TYPE_GRAY:
	case PNG_COLOR_TYPE_PALETTE:
		if(byDepth == 8)
		{
			eFormat = VeRenderer::FMT_R8_UNORM;
		}
		else if(byDepth == 16)
		{
			eFormat = VeRenderer::FMT_R16_UNORM;
		}
		byUnitSize = byDepth;
		byPixelSize = byDepth;
		break;
	case PNG_COLOR_TYPE_RGB:
		if(byDepth == 8)
		{
			eFormat = VeRenderer::FMT_R8G8B8A8_UNORM;
		}
		else if(byDepth == 16)
		{
			eFormat = VeRenderer::FMT_R16G16B16A16_UNORM;
		}
		byUnitSize = byDepth * 3;
		byPixelSize = byDepth * 4;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		if(byDepth == 8)
		{
			eFormat = VeRenderer::FMT_R8G8B8A8_UNORM;
		}
		else if(byDepth == 16)
		{
			eFormat = VeRenderer::FMT_R16G16B16A16_UNORM;
		}
		byUnitSize = byDepth * 4;
		byPixelSize = byDepth * 4;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		if(byDepth == 8)
		{
			eFormat = VeRenderer::FMT_R8G8_UNORM;
		}
		else if(byDepth == 16)
		{
			eFormat = VeRenderer::FMT_R16G16_UNORM;
		}
		byUnitSize = byDepth * 2;
		byPixelSize = byDepth * 2;
		break;
	}
	VE_ASSERT(eFormat != VeRenderer::FMT_UNKNOWN);
	byPixelSize >>= 3;
	byUnitSize >>= 3;
	png_bytep* row_pointers = png_get_rows(pkPngPtr, pkInfoPtr);
	m_kStream.Reset();
	m_kStream << m_u16Width;
	m_kStream << m_u16Height;
	m_kStream << VeUInt16(1);
	m_kStream << VeUInt16(1);
	m_kStream << VeUInt8(eFormat);
	m_kStream << VeUInt8(1);
	m_kStream << VeUInt8(0);
	m_kStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
	m_kStream << VeUInt8(VeRenderer::BIND_SHADER_RESOURCE);
	m_kStream << VeUInt8(0);
	m_kStream << VeUInt16(0);
	m_kStream << VeUInt16(1);
	m_kStream << VeUInt16(1);
	VeUInt32 u32PixelPitch = byPixelSize * m_u16Width;
	VeUInt32 u32PixelByteWidth = u32PixelPitch * m_u16Height;
	m_kStream << u32PixelPitch;
	m_kStream << u32PixelByteWidth;
	m_kStream << u32PixelByteWidth;
	if(byUnitSize == byPixelSize)
	{
		for(VeUInt32 i(0); i < m_u16Height; ++i)
		{
			m_kStream.Write(row_pointers[i], u32PixelPitch);
		}
	}
	else
	{
		for(VeUInt32 i(0); i < m_u16Height; ++i)
		{
			for(VeUInt32 j(0); j < m_u16Width; ++j)
			{
				m_kStream.Write(row_pointers[i] + (j * byUnitSize), byUnitSize);
				for(VeInt32 k(0); k < (byPixelSize - byUnitSize); ++k)
				{
					m_kStream << VeUInt8(0xff);
				}
			}
		}
	}
	png_destroy_read_struct(&pkPngPtr, &pkInfoPtr, NULL);
}
//--------------------------------------------------------------------------
void VePNGImage::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
