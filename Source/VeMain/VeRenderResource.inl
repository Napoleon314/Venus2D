////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderResource.inl
//  Version:     v1.00
//  Created:     8/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeBlobPtr& VeShaderResource::GetBlob()
{
	return m_spBlob;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VeTextureResource::GetWidth()
{
	return m_u16Width;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt16 VeTextureResource::GetHeight()
{
	return m_u16Height;
}
//--------------------------------------------------------------------------
VE_INLINE const VeTextureResourcePtr& TextureAtlas::GetTexture()
{
	return m_spTexture;
}
//--------------------------------------------------------------------------
VE_INLINE
const VeVector<TextureAtlas::SpriteFrame>& TextureAtlas::GetFrameArray()
{
	return m_kFrameArray;
}
//--------------------------------------------------------------------------
