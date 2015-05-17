////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeFont.cpp
//  Version:     v1.00
//  Created:     25/4/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include <lzmalib/LzmaLib.h>

struct VeFontHeader
{
	VeUInt32 m_u32Fourcc;
	VeUInt32 m_u32Version;
	VeUInt32 m_u32StartPointer;
	VeUInt32 m_u32ValidateChars;
	VeUInt32 m_u32NonemptyChars;
	VeUInt32 m_u32CharSize;
	VeInt16 m_i16Base;
	VeInt16 m_i16Scale;
};
//--------------------------------------------------------------------------
VeImplementRTTI(VeFont, VeResource);
//--------------------------------------------------------------------------
VeFont::VeFont(const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(FONT, pcName, pcGroup), m_u32CharSize(0), m_u32CharNum(0)
	, m_i16DistBase(0), m_i16DistScale(0), m_kCharIndexAdvance(1024)
{

}
//--------------------------------------------------------------------------
VeFont::~VeFont()
{
	Unload();
}
//--------------------------------------------------------------------------
VeUInt32 VeFont::GetWidth(VeChar16 c16Char)
{
	VePair<VeInt32, VeUInt32>* pkIter = m_kCharIndexAdvance.Find(c16Char);
	return pkIter ? pkIter->m_tSecond : 0;
}
//--------------------------------------------------------------------------
VePair<VeInt32, VeUInt32>* VeFont::IncChar(VeChar16 c16Char)
{
	VePair<VeInt32, VeUInt32>* pkIter = m_kCharIndexAdvance.Find(c16Char);
	if(pkIter && pkIter->m_tFirst >= 0
		&& pkIter->m_tFirst < VeInt32(m_kCharInfo.Size()))
	{
		CacheInfo& kInfo = m_kCharCacheInfo[pkIter->m_tFirst];
		if(!kInfo.m_u32Ref)
		{
			if(!(kInfo.m_kNode.IsAttach()))
			{
				VeUInt8 u8Buffer[VE_FONT_BUFFER];
				GetDistData(u8Buffer, pkIter->m_tFirst);
				if(m_kFreeList.Size())
				{
					CacheInfo* pkInfo = m_kFreeList.GetHeadNode()->m_tContent;
					kInfo.m_i16Page = pkInfo->m_i16Page;
					kInfo.x = pkInfo->x;
					kInfo.y = pkInfo->y;
					pkInfo->m_i16Page = -1;
					pkInfo->m_kNode.Detach();
					m_kTexutreCache[kInfo.m_i16Page].m_tFirst->CopyRect(0, kInfo.x * m_u32CharSize, kInfo.y * m_u32CharSize, m_u32CharSize, m_u32CharSize, VeRenderer::FMT_R8_UNORM, u8Buffer);
				}
				else
				{
					if(m_kTexutreCache.Empty() || m_kTexutreCache.Back().m_tSecond == (m_u32CharNum * m_u32CharNum))
					{
						m_kTexutreCache.Increase();
						VeMemoryOStream kStream;
						kStream << VeUInt16(VE_FONT_CACHE_SIZE);
						kStream << VeUInt16(VE_FONT_CACHE_SIZE);
						kStream << VeUInt16(1);
						kStream << VeUInt16(1);
						kStream << VeUInt8(VeRenderer::FMT_R8_UNORM);
						kStream << VeUInt8(1);
						kStream << VeUInt8(0);
						kStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
						kStream << VeUInt8(VeRenderer::BIND_SHADER_RESOURCE);
						kStream << VeUInt8(0);
						kStream << VeUInt16(0);
						kStream << VeUInt16(1);
						kStream << VeUInt16(0);
						VeChar8 acBuffer[256];
						VeSprintf(acBuffer, "%s_%d", (const VeChar8*)m_kName, m_kTexutreCache.Size() - 1);
						g_pRenderer->CreateTexture2D(acBuffer, kStream, &m_kTexutreCache.Back().m_tFirst);
						m_kTexutreCache.Back().m_tSecond = 0;
					}
					kInfo.m_i16Page = m_kTexutreCache.Size() - 1;
					kInfo.x = m_kTexutreCache.Back().m_tSecond % m_u32CharSize;
					kInfo.y = m_kTexutreCache.Back().m_tSecond / m_u32CharSize;
					m_kTexutreCache.Back().m_tFirst->CopyRect(0, kInfo.x * m_u32CharSize, kInfo.y * m_u32CharSize, m_u32CharSize, m_u32CharSize, VeRenderer::FMT_R8_UNORM, u8Buffer);
					m_kTexutreCache.Back().m_tSecond += 1;
				}
			}
			m_kUseList.AttachBack(kInfo.m_kNode);
		}
		++kInfo.m_u32Ref;
	}
	return pkIter;
}
//--------------------------------------------------------------------------
void VeFont::DecChar(VeInt32 i32Index)
{
	if(i32Index >= 0 && i32Index < VeInt32(m_kCharCacheInfo.Size()))
	{
		CacheInfo& kInfo = m_kCharCacheInfo[i32Index];
		if(kInfo.m_u32Ref)
		{
			if(!(--kInfo.m_u32Ref))
			{
				m_kFreeList.AttachBack(kInfo.m_kNode);
			}
		}
	}
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeFont::OnLost()
{

}
//--------------------------------------------------------------------------
void VeFont::OnRestore()
{
	VeChar8 acBuffer[256];
	for(VeUInt32 i(0); i < m_kTexutreCache.Size(); ++i)
	{
		VePair<VeROTexture2DPtr,VeUInt32>& kPair = m_kTexutreCache[i];
		VeMemoryOStream kStream;
		kStream << VeUInt16(VE_FONT_CACHE_SIZE);
		kStream << VeUInt16(VE_FONT_CACHE_SIZE);
		kStream << VeUInt16(1);
		kStream << VeUInt16(1);
		kStream << VeUInt8(VeRenderer::FMT_R8_UNORM);
		kStream << VeUInt8(1);
		kStream << VeUInt8(0);
		kStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
		kStream << VeUInt8(VeRenderer::BIND_SHADER_RESOURCE);
		kStream << VeUInt8(0);
		kStream << VeUInt16(0);
		kStream << VeUInt16(1);
		kStream << VeUInt16(0);
		VeSprintf(acBuffer, "%s_%d", (const VeChar8*)m_kName, m_kTexutreCache.Size() - 1);
		g_pRenderer->CreateTexture2D(acBuffer, kStream, &kPair.m_tFirst);
	}
	VeUInt8 u8Buffer[VE_FONT_BUFFER];
	m_kUseList.BeginIterator();
	while(!m_kUseList.IsEnd())
	{
		CacheInfo* pkInfo = m_kUseList.GetIterNode()->m_tContent;
		m_kUseList.Next();
		GetDistData(u8Buffer, pkInfo->m_u32Index);
		m_kTexutreCache[pkInfo->m_i16Page].m_tFirst->CopyRect(0, pkInfo->x * m_u32CharSize, pkInfo->y * m_u32CharSize, m_u32CharSize, m_u32CharSize, VeRenderer::FMT_R8_UNORM, u8Buffer);
	}
	m_kFreeList.BeginIterator();
	while(!m_kFreeList.IsEnd())
	{
		CacheInfo* pkInfo = m_kFreeList.GetIterNode()->m_tContent;
		m_kFreeList.Next();
		GetDistData(u8Buffer, pkInfo->m_u32Index);
		m_kTexutreCache[pkInfo->m_i16Page].m_tFirst->CopyRect(0, pkInfo->x * m_u32CharSize, pkInfo->y * m_u32CharSize, m_u32CharSize, m_u32CharSize, VeRenderer::FMT_R8_UNORM, u8Buffer);
	}
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeResource* VeFont::CreateResource(const VeChar8* pcName,
	const VeChar8* pcGroup)
{
	return VE_NEW VeFont(pcName, pcGroup);
}
//--------------------------------------------------------------------------
VeResource::State VeFont::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	return m_u32CharSize ? LOADED : UNLOADED;
}
//--------------------------------------------------------------------------
void VeFont::UnloadImpl()
{
	m_u32CharSize = 0;
	m_i16DistBase = 0;
	m_i16DistScale = 0;
	m_kCharIndexAdvance.Clear();
	m_kCharInfo.Clear();
	m_kDistAddr.Clear();
	m_kDistLzma.Clear();
	m_kCharCacheInfo.Clear();
}
//--------------------------------------------------------------------------
bool VeFont::HasProcess()
{
	return true;
}
//--------------------------------------------------------------------------
void VeFont::LoadProcess(const VeMemoryIStreamPtr& spStream)
{
	VeFontHeader kHeader;
	(*spStream) >> kHeader;
	if(kHeader.m_u32Fourcc == VE_MAKE_ID('K', 'F', 'N', 'T')
		&& kHeader.m_u32Version == 2
		&& kHeader.m_u32StartPointer >= sizeof(VeFontHeader))
	{
		m_u32CharSize = kHeader.m_u32CharSize;
		m_i16DistBase = kHeader.m_i16Base;
		m_i16DistScale = kHeader.m_i16Scale;
		m_u32CharNum = VE_FONT_CACHE_SIZE / m_u32CharSize;
		{
			VeInt32 i32DataSkip = kHeader.m_u32StartPointer - sizeof(VeFontHeader);
			if(i32DataSkip > 0) spStream->Skip(i32DataSkip);
		}
		VeVector< VePair<VeInt32, VeInt32> > kTempCharIndex;
		kTempCharIndex.Resize(kHeader.m_u32NonemptyChars);
		VE_ASSERT_EQ(spStream->Read((void*)&kTempCharIndex[0], kTempCharIndex.Size() * sizeof(VePair<VeInt32, VeInt32>)), VeInt32(kTempCharIndex.Size() * sizeof(VePair<VeInt32, VeInt32>)));

		VeVector< VePair<VeInt32, VeUInt32> > kTempCharAdvance;
		kTempCharAdvance.Resize(kHeader.m_u32ValidateChars);
		VE_ASSERT_EQ(spStream->Read((void*)&kTempCharAdvance[0], kTempCharAdvance.Size() * sizeof(VePair<VeInt32, VeUInt32>)), VeInt32(kTempCharAdvance.Size() * sizeof(VePair<VeInt32, VeUInt32>)));

		for(VeVector< VePair<VeInt32, VeInt32> >::iterator it = kTempCharIndex.Begin();
			it != kTempCharIndex.End(); ++it)
		{
			m_kCharIndexAdvance.Insert(it->m_tFirst, VeMakePair(it->m_tSecond, 0));
		}

		for(VeVector< VePair<VeInt32, VeUInt32> >::iterator it = kTempCharAdvance.Begin();
			it != kTempCharAdvance.End(); ++it)
		{
			VePair<VeInt32, VeUInt32>* pkIter = m_kCharIndexAdvance.Find(it->m_tFirst);
			if(pkIter)
			{
				pkIter->m_tSecond = it->m_tSecond;
			}
			else
			{
				m_kCharIndexAdvance[it->m_tFirst] = VeMakePair(-1, it->m_tSecond);
			}
		}
		
		m_kCharInfo.Resize(kHeader.m_u32NonemptyChars);
		VE_ASSERT_EQ(spStream->Read((void*)&m_kCharInfo[0], m_kCharInfo.Size() * sizeof(Info)), VeInt32(m_kCharInfo.Size() * sizeof(Info)));
		
		m_kDistAddr.Resize(kHeader.m_u32NonemptyChars + 1);

		for(VeUInt32 i(0); i < kHeader.m_u32NonemptyChars; ++ i)
		{
			m_kDistAddr[i] = m_kDistLzma.Size();
			VeUInt64 u64Len;
			(*spStream) >> u64Len;
			m_kDistLzma.Increase(VeUInt32(u64Len));
			spStream->Read((void*)&m_kDistLzma[m_kDistAddr[i]], VeUInt32(u64Len));
		}
		m_kDistAddr[kHeader.m_u32NonemptyChars] = m_kDistLzma.Size();
		m_kCharCacheInfo.Resize(kHeader.m_u32NonemptyChars);
		for(VeUInt32 i(0); i < m_kCharCacheInfo.Size(); ++i)
		{
			m_kCharCacheInfo[i].m_u32Index = i;
		}
	}
}
//--------------------------------------------------------------------------
VeResource::State VeFont::AllWaitResLoaded()
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
	kStream << VeFloat32(m_i16DistBase) / 32768.0f * 32.0f + 1.0f;
	kStream << (VeFloat32(m_i16DistScale) / 32768.0f + 1.0f) * 32.0f;
	kStream << 0.0f;
	kStream << 0.0f;
	g_pRenderer->CreateBuffer(GetName(), kStream);
	return LOADED;
}
//--------------------------------------------------------------------------
void VeFont::TermRender()
{
	m_kUseList.Clear();
	m_kFreeList.Clear();
	m_kTexutreCache.Clear();
}
//--------------------------------------------------------------------------
void VeFont::GetDistData(VeUInt8* pu8Buffer, VeInt32 i32Index)
{
	VePair<VeUInt8*,VeUInt32> kLzma = GetLzmaDistData(i32Index);
	VeSizeT stOutLen = m_u32CharSize * m_u32CharSize;
	VeSizeT stSrcLen = kLzma.m_tSecond - LZMA_PROPS_SIZE;
	VE_ASSERT_EQ(LzmaUncompress(pu8Buffer, &stOutLen,
		kLzma.m_tFirst + LZMA_PROPS_SIZE, &stSrcLen,
		kLzma.m_tFirst, LZMA_PROPS_SIZE), SZ_OK);
}
//--------------------------------------------------------------------------
VePair<VeUInt8*,VeUInt32> VeFont::GetLzmaDistData(VeInt32 i32Index)
{
	VePair<VeUInt8*,VeUInt32> kRes;
	kRes.m_tFirst = &(m_kDistLzma[m_kDistAddr[i32Index]]);
	kRes.m_tSecond = m_kDistAddr[i32Index + 1] - m_kDistAddr[i32Index];
	return kRes;
}
//--------------------------------------------------------------------------
