////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderResource.h
//  Version:     v1.00
//  Created:     8/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeShaderResource : public VeResource
{
	VeDeclareRTTI;
public:
	VeShaderResource(Type eType, const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeShaderResource();

	virtual const VeChar8* GetLoadName();

	VE_INLINE const VeBlobPtr& GetBlob();

#ifdef VE_ENABLE_DEVICE_LOST

	virtual void OnLost();

	virtual void OnRestore();

#endif

	static VeResource* CreateVertexShaderResource(const VeChar8* pcName, const VeChar8* pcGroup);

	static VeResource* CreatePixelShaderResource(const VeChar8* pcName, const VeChar8* pcGroup);

protected:
	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	VeString m_kLoadName;
	VeBlobPtr m_spBlob;

};

VeSmartPointer(VeShaderResource);

#define VeGetVertexShader(name,group) VeDynamicCast(VeShaderResource,VeGetResource(VeResource::VERTEX_SHADER,name,group))

#define VeLoadVertexShader(name,group,async) VeDynamicCast(VeShaderResource,VeLoadResource(VeResource::VERTEX_SHADER,name,group,async))

#define VeLoadVertexShaderSync(name,group) VeLoadVertexShader(name,group,false)

#define VeLoadVertexShaderAsync(name,group) VeLoadVertexShader(name,group,true)

#define VeGetPixelShader(name,group) VeDynamicCast(VeShaderResource,VeGetResource(VeResource::PIXEL_SHADER,name,group))

#define VeLoadPixelShader(name,group,async) VeDynamicCast(VeShaderResource,VeLoadResource(VeResource::PIXEL_SHADER,name,group,async))

#define VeLoadPixelShaderSync(name,group) VeLoadPixelShader(name,group,false)

#define VeLoadPixelShaderAsync(name,group) VeLoadPixelShader(name,group,true)

class VE_MAIN_API VeTextureResource : public VeResource
{
	VeDeclareRTTI;
public:
	VeTextureResource(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeTextureResource();

	VE_INLINE VeUInt16 GetWidth();

	VE_INLINE VeUInt16 GetHeight();

#ifdef VE_ENABLE_DEVICE_LOST

	virtual void OnLost();

	virtual void OnRestore();

#endif

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

protected:
	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	virtual bool HasProcess();

	virtual void LoadProcess(const VeMemoryIStreamPtr& spStream);

	VeImagePtr m_spImage;
	VeUInt16 m_u16Width;
	VeUInt16 m_u16Height;

};

VeSmartPointer(VeTextureResource);

#define VeGetTexture(name,group) VeDynamicCast(VeTextureResource,VeGetResource(VeResource::TEXTURE,name,group))

#define VeLoadTexture(name,group,async) VeDynamicCast(VeTextureResource,VeLoadResource(VeResource::TEXTURE,name,group,async))

#define VeLoadTextureSync(name,group) VeLoadTexture(name,group,false)

#define VeLoadTextureAsync(name,group) VeLoadTexture(name,group,true)

class VE_MAIN_API TextureAtlas : public VeResource
{
	VeDeclareRTTI;
public:
	enum Orientation
	{
		FRAME_ZERO,
		FRAME_QUARTER
	};

	struct SpriteFrame
	{
		VeFixedString m_kName;
		VeUInt16 m_u16PosX;
		VeUInt16 m_u16PosY;
		VeUInt16 m_u16TrimW;
		VeUInt16 m_u16TrimH;
		VeUInt16 m_u16OffsetX;
		VeUInt16 m_u16OffsetY;
		VeUInt16 m_u16OriginW;
		VeUInt16 m_u16OriginH;
		Orientation m_eOrient;
	};

	TextureAtlas(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~TextureAtlas();

	VE_INLINE const VeTextureResourcePtr& GetTexture();

	VE_INLINE const VeVector<SpriteFrame>& GetFrameArray();

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

protected:
	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	virtual bool HasProcess();

	virtual void LoadProcess(const VeMemoryIStreamPtr& spStream);

	virtual State AllWaitResLoaded();

	void AddFrames();

	void DelFrames();

	VeTextureResourcePtr m_spTexture;
	VeFixedString m_kTexName;
	VeUInt16 m_u16Width;
	VeUInt16 m_u16Height;
	VeVector<SpriteFrame> m_kFrameArray;

};

VeSmartPointer(TextureAtlas);

#define VeGetTextureAtlas(name,group) VeDynamicCast(TextureAtlas,VeGetResource(VeResource::TEXTURE_ATLAS,name,group))

#define VeLoadTextureAtlas(name,group,async) VeDynamicCast(TextureAtlas,VeLoadResource(VeResource::TEXTURE_ATLAS,name,group,async))

#define VeLoadTextureAtlasSync(name,group) VeLoadTextureAtlas(name,group,false)

#define VeLoadTextureAtlasAsync(name,group) VeLoadTextureAtlas(name,group,true)

#ifndef VE_NO_INLINE
#	include "VeRenderResource.inl"
#endif
