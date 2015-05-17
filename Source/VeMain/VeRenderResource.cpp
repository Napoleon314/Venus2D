////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderResource.cpp
//  Version:     v1.00
//  Created:     8/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeRenderResource.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeShaderResource, VeResource);
//--------------------------------------------------------------------------
VeShaderResource::VeShaderResource(Type eType, const VeChar8* pcName,
	const VeChar8* pcGroup)
	: VeResource(eType, pcName, pcGroup)
{
	m_kLoadName = g_pRenderer->GetShaderName();
	m_kLoadName += '/';
	m_kLoadName += m_kName;
	m_kLoadName += '.';
	switch(m_eType)
	{
	case VERTEX_SHADER:
		m_kLoadName += "vs_";
		break;
	case PIXEL_SHADER:
		m_kLoadName += "ps_";
		break;
	default:
		break;
	}
	m_kLoadName += g_pRenderer->GetShaderProfile();
}
//--------------------------------------------------------------------------
VeShaderResource::~VeShaderResource()
{
	Unload();
}
//--------------------------------------------------------------------------
const VeChar8* VeShaderResource::GetLoadName()
{
	return m_kLoadName;	
}
//--------------------------------------------------------------------------
VeResource::State VeShaderResource::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	VE_ASSERT(spStream);
	m_spBlob = spStream->GetBlob();
	switch(m_eType)
	{
	case VERTEX_SHADER:
		{
			VeROVertexShaderPtr spShader;
			g_pRenderer->GetRenderObject(m_kName, spShader);
			if(spShader)
			{
				(*spStream) >> (*spShader);
			}
			else
			{
				g_pRenderer->CreateVertexShader(m_kName, *spStream, &spShader);
			}
		}
		break;
	case PIXEL_SHADER:
		{
			VeROPixelShaderPtr spShader;
			g_pRenderer->GetRenderObject(m_kName, spShader);
			if(spShader)
			{
				(*spStream) >> (*spShader);
			}
			else
			{
				g_pRenderer->CreatePixelShader(m_kName, *spStream, &spShader);
			}
		}
		break;
	default:
		break;
	}
	return VeResource::LOADED;
}
//--------------------------------------------------------------------------
void VeShaderResource::UnloadImpl()
{
	m_spBlob = NULL;
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeShaderResource::OnLost()
{
	
}
//--------------------------------------------------------------------------
void VeShaderResource::OnRestore()
{
	VeMemoryIStream kStream(m_spBlob);
	switch(m_eType)
	{
	case VERTEX_SHADER:
		{
			VeROVertexShaderPtr spShader;
			g_pRenderer->GetRenderObject(m_kName, spShader);
			if(spShader)
			{
				kStream >> (*spShader);
			}
		}
		break;
	case PIXEL_SHADER:
		{
			VeROPixelShaderPtr spShader;
			g_pRenderer->GetRenderObject(m_kName, spShader);
			if(spShader)
			{
				kStream >> (*spShader);
			}
		}
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeResource* VeShaderResource::CreateVertexShaderResource(
	const VeChar8* pcName, const VeChar8* pcGroup)
{
	return VE_NEW VeShaderResource(VERTEX_SHADER, pcName, pcGroup);
}
//--------------------------------------------------------------------------
VeResource* VeShaderResource::CreatePixelShaderResource(
	const VeChar8* pcName, const VeChar8* pcGroup)
{
	return VE_NEW VeShaderResource(PIXEL_SHADER, pcName, pcGroup);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeTextureResource, VeResource);
//--------------------------------------------------------------------------
VeTextureResource::VeTextureResource(const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(VeResource::TEXTURE, pcName, pcGroup)
{

}
//--------------------------------------------------------------------------
VeTextureResource::~VeTextureResource()
{
	Unload();
}
//--------------------------------------------------------------------------
VeResource::State VeTextureResource::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	VE_ASSERT(m_spImage);
	if(g_pRenderer) g_pRenderer->CreateTexture2D(GetName(), m_spImage->GetCreateData());
	m_u16Width = m_spImage->GetWidth();
	m_u16Height = m_spImage->GetHeight();
#	ifndef VE_ENABLE_DEVICE_LOST
	m_spImage = NULL;
#	endif
	if(g_pRenderer)
	{
		VeMemoryOStream kStream;
		kStream << VeUInt32(16);
		kStream << VeUInt16(0);
		kStream << VeUInt16(0);
		kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
		kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
		kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
		kStream << VeByte(1);
		kStream << VeUInt32(16);
		kStream << VeUInt32(16);
		kStream << (1.0f / VeFloat32(m_u16Width));
		kStream << (1.0f / VeFloat32(m_u16Height));
		kStream << VeFloat32(m_u16Width);
		kStream << VeFloat32(m_u16Height);
		g_pRenderer->CreateBuffer(GetName(), kStream);
	}
	return VeResource::LOADED;
}
//--------------------------------------------------------------------------
void VeTextureResource::UnloadImpl()
{
	m_spImage = NULL;
	if(g_pRenderer)
	{
		g_pRenderer->DestroyRenderObject(VeRenderObject::TYPE_TEXTURE_2D, GetName());
		g_pRenderer->DestroyRenderObject(VeRenderObject::TYPE_BUFFER, GetName());
	}
}
//--------------------------------------------------------------------------
bool VeTextureResource::HasProcess()
{
	return true;
}
//--------------------------------------------------------------------------
void VeTextureResource::LoadProcess(const VeMemoryIStreamPtr& spStream)
{
	VeUInt64 u64ImageCheckHead = *(const VeUInt64*)spStream->GetData();
	m_spImage = VeImage::CreateImage(u64ImageCheckHead, *spStream);
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeTextureResource::OnLost()
{

}
//--------------------------------------------------------------------------
void VeTextureResource::OnRestore()
{
	if(GetState() == LOADED)
	{
		VE_ASSERT(m_spImage);
		g_pRenderer->CreateTexture2D(GetName(), m_spImage->GetCreateData());
	}
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeResource* VeTextureResource::CreateResource(const VeChar8* pcName,
	const VeChar8* pcGroup)
{
	return VE_NEW VeTextureResource(pcName, pcGroup);
}
//--------------------------------------------------------------------------
VeImplementRTTI(TextureAtlas, VeResource);
//--------------------------------------------------------------------------
TextureAtlas::TextureAtlas(const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(VeResource::TEXTURE_ATLAS, pcName, pcGroup)
{
	
}
//--------------------------------------------------------------------------
TextureAtlas::~TextureAtlas()
{
	Unload();
}
//--------------------------------------------------------------------------
VeResource::State TextureAtlas::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	m_spTexture = VeLoadTexture(m_kTexName, m_spGroup->GetName(), m_eState == LOADING);
	Wait(m_spTexture);
	return LOADED;
}
//--------------------------------------------------------------------------
void TextureAtlas::UnloadImpl()
{
	DelFrames();
	m_kFrameArray.Clear();
	VE_ASSERT(m_spTexture);
	m_spTexture->Unload();
	m_spTexture = NULL;
	m_kTexName = "";
	m_u16Width = 0;
	m_u16Height = 0;
}
//--------------------------------------------------------------------------
bool TextureAtlas::HasProcess()
{
	return true;
}
//--------------------------------------------------------------------------
void TextureAtlas::LoadProcess(const VeMemoryIStreamPtr& spStream)
{
	VeXMLDocument kDoc;
	(*spStream) >> kDoc;
	m_kTexName = kDoc.RootElement()->Attribute("imagePath");
	m_u16Width = kDoc.RootElement()->Attribute("width", 1);
	m_u16Height = kDoc.RootElement()->Attribute("height", 1);
	VeXMLElement* pkIter = kDoc.RootElement()->FirstChildElement("sprite");
	while(pkIter)
	{
		const VeChar8* pcName = pkIter->Attribute("n");
		m_kFrameArray.Resize(m_kFrameArray.Size() + 1);
		SpriteFrame& kFrame = m_kFrameArray.Back();
		kFrame.m_kName = pcName;
		kFrame.m_u16PosX = pkIter->Attribute("x", 0);
		kFrame.m_u16PosY = pkIter->Attribute("y", 0);
		kFrame.m_u16TrimW = pkIter->Attribute("w", 0);
		kFrame.m_u16TrimH = pkIter->Attribute("h", 0);
		kFrame.m_u16OffsetX = pkIter->Attribute("oX", 0);
		kFrame.m_u16OffsetY = pkIter->Attribute("oY", 0);
		
		if(VE_SUCCEEDED(VeStricmp(pkIter->Attribute("r"), "y")))
		{
			kFrame.m_eOrient = FRAME_QUARTER;
			kFrame.m_u16OriginW = pkIter->Attribute("oW", kFrame.m_u16TrimH);
			kFrame.m_u16OriginH = pkIter->Attribute("oH", kFrame.m_u16TrimW);
		}
		else
		{
			kFrame.m_eOrient = FRAME_ZERO;
			kFrame.m_u16OriginW = pkIter->Attribute("oW", kFrame.m_u16TrimW);
			kFrame.m_u16OriginH = pkIter->Attribute("oH", kFrame.m_u16TrimH);
		}
		pkIter = pkIter->NextSiblingElement("sprite");
	}
}
//--------------------------------------------------------------------------
VeResource::State TextureAtlas::AllWaitResLoaded()
{
	AddFrames();
	return LOADED;
}
//--------------------------------------------------------------------------
void TextureAtlas::AddFrames()
{
	if(g_pRenderer)
	{
		VeVector<VeRenderer::SpriteFrame>& kArray = g_pRenderer->m_kSpriteFrameArray;
		VeStringMap<VeUInt32>& kMap = g_pRenderer->m_kSpriteFrameMap;
		for(VeUInt32 i(0); i < m_kFrameArray.Size(); ++i)
		{
			SpriteFrame& kFrame = m_kFrameArray[i];
			VeUInt32* pu32Iter = kMap.Find(kFrame.m_kName);
			if(!pu32Iter)
			{
				kMap[kFrame.m_kName] = kArray.Size();
				kArray.Resize(kArray.Size() + 1);
				kArray.Back().m_pkResource = this;
				kArray.Back().m_u32Index = i;
			}
		}
	}
}
//--------------------------------------------------------------------------
void TextureAtlas::DelFrames()
{
	if(g_pRenderer)
	{
		VeVector<VeRenderer::SpriteFrame>& kArray = g_pRenderer->m_kSpriteFrameArray;
		VeStringMap<VeUInt32>& kMap = g_pRenderer->m_kSpriteFrameMap;
		for(VeUInt32 i(0); i < m_kFrameArray.Size(); ++i)
		{
			SpriteFrame& kFrame = m_kFrameArray[i];
			VeUInt32* pu32Iter = kMap.Find(kFrame.m_kName);
			if(pu32Iter)
			{
				if((*pu32Iter) < (kArray.Size() - 1))
				{
					VeRenderer::SpriteFrame& kBack = kArray.Back();
					VE_ASSERT(kBack.m_pkResource);
					const VeChar8* pcBackName = VeDynamicCast(TextureAtlas, &(*kBack.m_pkResource))->m_kFrameArray[kBack.m_u32Index].m_kName;
					VeUInt32* pu32Back = kMap.Find(pcBackName);
					VE_ASSERT(pu32Back);
					*pu32Back = *pu32Iter;
					kArray[*pu32Iter].m_pkResource = kBack.m_pkResource;
					kArray[*pu32Iter].m_u32Index = kBack.m_u32Index;
				}
				kMap.Remove(kFrame.m_kName);
				kArray.PopBack();
			}
		}
	}
}
//--------------------------------------------------------------------------
VeResource* TextureAtlas::CreateResource(const VeChar8* pcName,
	const VeChar8* pcGroup)
{
	return VE_NEW TextureAtlas(pcName, pcGroup);
}
//--------------------------------------------------------------------------
