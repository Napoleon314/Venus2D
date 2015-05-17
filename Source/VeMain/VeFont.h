////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeFont.h
//  Version:     v1.00
//  Created:     25/4/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_FONT_CACHE_SIZE 1024
#define VE_FONT_BUFFER 1024

VeSmartPointer(VeROTexture2D);

class VE_MAIN_API VeFont : public VeResource
{
	VeDeclareRTTI;
public:
	struct Info
	{
		VeInt16 m_i16Top;
		VeInt16 m_i16Left;
		VeInt16 m_i16Width;
		VeInt16 m_i16Height;
	};

	struct CacheInfo
	{
		CacheInfo() : m_i16Page(-1), x(0), y(0), m_u32Ref(0)
		{
			m_kNode.m_tContent = this;
		}
		VeUInt32 m_u32Index;
		VeInt16 m_i16Page;
		VeUInt8 x, y;
		VeUInt32 m_u32Ref;
		VeRefNode<CacheInfo*> m_kNode;
	};

	struct TextureCache
	{
		TextureCache() : m_u32Pointer(0) {}

		VeROTexture2DPtr m_spTex;
		VeUInt32 m_u32Pointer;
	};

	VeFont(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeFont();

	VeUInt32 GetWidth(VeChar16 c16Char);

	VePair<VeInt32, VeUInt32>* IncChar(VeChar16 c16Char);	

	void DecChar(VeInt32 i32Index);

#ifdef VE_ENABLE_DEVICE_LOST

	virtual void OnLost();

	virtual void OnRestore();

#endif

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

protected:
	friend class VeSingleChar;
	friend class VeSimpleText;

	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	virtual bool HasProcess();

	virtual void LoadProcess(const VeMemoryIStreamPtr& spStream);

	virtual State AllWaitResLoaded();

	virtual void TermRender();

	void GetDistData(VeUInt8* pu8Buffer, VeInt32 i32Index);

	VePair<VeUInt8*,VeUInt32> GetLzmaDistData(VeInt32 i32Index);

	VeUInt32 m_u32CharSize;
	VeUInt32 m_u32CharNum;
	VeInt16 m_i16DistBase;
	VeInt16 m_i16DistScale;
	VeHashMap< VeChar16, VePair<VeInt32, VeUInt32> > m_kCharIndexAdvance;
	VeVector<Info> m_kCharInfo;
	VeVector<VeUInt32> m_kDistAddr;
	VeVector<VeUInt8> m_kDistLzma;
	VeVector<CacheInfo> m_kCharCacheInfo;
	VeRefList<CacheInfo*> m_kUseList;
	VeRefList<CacheInfo*> m_kFreeList;
	VeVector< VePair<VeROTexture2DPtr,VeUInt32> > m_kTexutreCache;

};

VeSmartPointer(VeFont);

#define VeGetFont(name,group) VeDynamicCast(VeFont,VeGetResource(VeResource::FONT,name,group))

#define VeLoadFont(name,group,async) VeDynamicCast(VeFont,VeLoadResource(VeResource::FONT,name,group,async))

#define VeLoadFontSync(name,group) VeLoadFont(name,group,false)

#define VeLoadFontAsync(name,group) VeLoadFont(name,group,true)
