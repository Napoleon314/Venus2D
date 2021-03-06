////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeImage.inl
//  Version:     v1.00
//  Created:     18/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeImage::Type VeImage::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE VeImage::Tex VeImage::GetTex()
{
	return m_eTex;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VeImage::GetWidth()
{
	return m_u16Width;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VeImage::GetHeight()
{
	return m_u16Height;
}
//--------------------------------------------------------------------------
