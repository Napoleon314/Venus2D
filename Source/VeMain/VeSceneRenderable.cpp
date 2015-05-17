////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneRenderable.cpp
//  Version:     v1.00
//  Created:     20/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeSceneRenderable.inl"
#endif
#include "_VeRendererGLES2.h"
#include "_VeRendererD3D11.h"

//--------------------------------------------------------------------------
VeImplementRootRTTI(VeSceneRenderable);
//--------------------------------------------------------------------------
VeSceneRenderable::VeSceneRenderable(VeUInt32 u32Group) : m_u32Group(0)
{
	SetGroup(u32Group);
	m_kNode.m_tContent = this;
	m_pkRenderNode = VE_NEW VeRenderNode;
}
//--------------------------------------------------------------------------
VeSceneRenderable::~VeSceneRenderable()
{
	VE_SAFE_DELETE(m_pkRenderNode);
}
//--------------------------------------------------------------------------
void VeSceneRenderable::SetGroup(VeUInt32 u32Group)
{
	m_u32Group = VE_MIN(u32Group, VeSceneManager::QUEUE_FINALLY);
}
//--------------------------------------------------------------------------
void VeSceneRenderable::Detach()
{
	if(m_kNode.IsAttach())
	{
		m_kNode.Detach();
		DecRefCount();
	}
}
//--------------------------------------------------------------------------
void VeSceneRenderable::Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask)
{
	kQueue.QueueRenderable(this, u32Mask);
}
//--------------------------------------------------------------------------
bool VeSceneRenderable::Combine(VeSceneRenderable* pkRenderable)
{
	return m_pkRenderNode->m_pkParent->m_spData == pkRenderable->m_pkRenderNode->m_pkParent->m_spData;
}
//--------------------------------------------------------------------------
void VeSceneRenderable::LinkNodeToParent()
{
	m_pkRenderNode->LinkToParent();
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSceneRenderable)
{
	Module() [
		Class<VeSceneRenderable>().
			Def("SetGroup", &VeSceneRenderable::SetGroup).
			Def("GetGroup", &VeSceneRenderable::GetGroup).
			Def("Detach", &VeSceneRenderable::Detach)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSceneRenderable2D, VeSceneRenderable);
//--------------------------------------------------------------------------
VeSceneRenderable2D::VeSceneRenderable2D(VeUInt32 u32Group)
	: VeSceneRenderable(u32Group)
{

}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSceneRenderable2D)
{
	Module() [
		Class< VeSceneRenderable2D, Base<VeSceneRenderable> >()
	];
}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeSceneRenderable2D, BlendFunc);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeSceneRenderable2D, BlendFunc)
{
	VeLuaClassEnumBase(VeSceneRenderable2D, BlendFunc);
	VeLuaClassEnumSlot(VeSceneRenderable2D, BlendFunc, REPLACE, "replace");
	VeLuaClassEnumSlot(VeSceneRenderable2D, BlendFunc, ALPHA_BLEND, "blend");
	VeLuaClassEnumSlot(VeSceneRenderable2D, BlendFunc, ALPHA_BLEND_MUL, "blend_mul");
	VeLuaClassEnumSlot(VeSceneRenderable2D, BlendFunc, ADD, "add");
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSprite2D, VeSceneRenderable2D);
//--------------------------------------------------------------------------
VeSprite2D::VeSprite2D()
	: VeSceneRenderable2D(VeSceneManager::QUEUE_SPRITES)
	, m_pkSpriteNode(NULL), m_eBlend(ALPHA_BLEND)
{
	Init();
}
//--------------------------------------------------------------------------
VeSprite2D::VeSprite2D(const VeChar8* pcName)
	: VeSceneRenderable2D(VeSceneManager::QUEUE_SPRITES)
	, m_pkSpriteNode(NULL), m_eBlend(ALPHA_BLEND)
{
	Init();
	SetTexture(pcName);
}
//--------------------------------------------------------------------------
VeSprite2D::VeSprite2D(const VeTextureResourcePtr& spTex)
	: VeSceneRenderable2D(VeSceneManager::QUEUE_SPRITES)
	, m_pkSpriteNode(NULL), m_eBlend(ALPHA_BLEND)
{
	Init();
	SetTexture(spTex);
}
//--------------------------------------------------------------------------
VeSprite2D::~VeSprite2D()
{
	VE_SAFE_DELETE(m_pkSpriteNode);
}
//--------------------------------------------------------------------------
void VeSprite2D::Init()
{
	m_pkRenderNode->SetData("draw_2d_sprite");
	m_pkSpriteNode = VE_NEW VeRenderNode;
	m_pkSpriteNode->SetParent(m_pkRenderNode);
	m_pkSpriteNode->m_pkRenderable = this;
	m_kAnchor = VeVector2D::ZERO;
	m_u32UpdateFrame = 0;
	m_bEnable = false;
	m_bDirty = false;
	m_bTransparency = false;
#	ifdef VE_ENABLE_GLES2
	m_pkBlendTick = NULL;
	m_pkBufferTick = NULL;
	m_pkDrawCall = NULL;
	m_u32CombineCount = 0;
#	else
	VeMemoryOStream kStream;
	kStream << VeUInt32(sizeof(Params));
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(0);
	g_pRenderer->CreateBuffer("", kStream, &m_spSingleBuffer);
	g_pRenderer->GetRenderObject("quad_cb", m_spInstanceBuffer);
	m_pkBlendTick = NULL;
#	endif
	m_kFrame.m_u16OriginW = 0;
	m_kFrame.m_u16OriginH = 0;
}
//--------------------------------------------------------------------------
void VeSprite2D::SetTexture(const VeChar8* pcName, VeFloat32 x, VeFloat32 y)
{
	VeTextureResourcePtr spTex = VeGetTexture(pcName, NULL);
	if(spTex)
	{
		if(spTex->GetState() == VeResource::LOADED)
		{
			SetTexture(spTex, x, y);
		}
	}
	else
	{
		const VeRenderer::RenderTarget* pkTarget = g_pRenderer->GetRenderTarget2D(pcName);
		if(pkTarget)
		{
			m_kFrame.m_kName = pcName;
			m_kFrame.m_u16PosX = 0;
			m_kFrame.m_u16PosY = 0;
			m_kFrame.m_u16TrimW = pkTarget->m_u16Width;
			m_kFrame.m_u16TrimH = pkTarget->m_u16Height;
			m_kFrame.m_u16OffsetX = 0;
			m_kFrame.m_u16OffsetY = 0;
			m_kFrame.m_u16OriginW = pkTarget->m_u16Width;
			m_kFrame.m_u16OriginH = pkTarget->m_u16Height;
			m_kFrame.m_eOrient = TextureAtlas::FRAME_ZERO;
			UpdateData();
			UpdateRenderNodeData(pcName);
			UpdateBlend();
			SetAnchor(x, y);
			m_bEnable = true;
			m_bDirty = true;
		}
		else
		{
			SetFrameName(pcName, x, y);
		}
	}
}
//--------------------------------------------------------------------------
void VeSprite2D::SetTexture(const VeTextureResourcePtr& spTex,
	VeFloat32 x, VeFloat32 y)
{
	VE_ASSERT(spTex && spTex->GetState() == VeResource::LOADED);
	m_spResource = VeSmartPointerCast(VeResource, spTex);
	m_kFrame.m_kName = spTex->GetName();
	m_kFrame.m_u16PosX = 0;
	m_kFrame.m_u16PosY = 0;
	m_kFrame.m_u16TrimW = spTex->GetWidth();
	m_kFrame.m_u16TrimH = spTex->GetHeight();
	m_kFrame.m_u16OffsetX = 0;
	m_kFrame.m_u16OffsetY = 0;
	m_kFrame.m_u16OriginW = spTex->GetWidth();
	m_kFrame.m_u16OriginH = spTex->GetHeight();
	m_kFrame.m_eOrient = TextureAtlas::FRAME_ZERO;
	UpdateData();
	UpdateRenderNodeData(spTex->GetName());
	UpdateBlend();
	SetAnchor(x, y);
	m_bEnable = true;
	m_bDirty = true;
}
//--------------------------------------------------------------------------
void VeSprite2D::SetFrameName(const VeChar8* pcName,
	VeFloat32 x, VeFloat32 y)
{
	VeRenderer::SpriteFrame kFrame;
	g_pRenderer->GetSpriteFrame(pcName, kFrame);
	m_spResource = kFrame.m_pkResource;
	VE_ASSERT(kFrame.m_pkResource);
	TextureAtlas* pkAtlas = VeDynamicCast(TextureAtlas, &*kFrame.m_pkResource);
	VE_ASSERT(pkAtlas && pkAtlas->GetState() == VeResource::LOADED);
	m_kFrame = pkAtlas->GetFrameArray()[kFrame.m_u32Index];
	UpdateData();
	UpdateRenderNodeData(pkAtlas->GetTexture()->GetName());
	UpdateBlend();
	SetAnchor(x, y);
	m_bEnable = true;
	m_bDirty = true;
}
//--------------------------------------------------------------------------
void VeSprite2D::SetAnchor(VeFloat32 x, VeFloat32 y,
	VeFloat32 f32OffsetX, VeFloat32 f32OffsetY, bool bFloor)
{
	if(bFloor)
	{
		SetAnchor(VeVector2D(
			VeFloorf(x * VeFloat32(m_kFrame.m_u16OriginW) + f32OffsetX),
			VeFloorf(y * VeFloat32(m_kFrame.m_u16OriginH) + f32OffsetY)));
	}
	else
	{
		SetAnchor(VeVector2D(
			x * VeFloat32(m_kFrame.m_u16OriginW) + f32OffsetX,
			y * VeFloat32(m_kFrame.m_u16OriginH) + f32OffsetY));
	}
}
//--------------------------------------------------------------------------
bool VeSprite2D::Combine(VeSceneRenderable* pkRenderable)
{
	if(VeSceneRenderable2D::Combine(pkRenderable) && m_spResource)
	{
#		ifdef VE_ENABLE_GLES2
		if(!m_u32CombineCount)
		{
			void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
			VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
			++m_u32CombineCount;
		}
		VeSprite2D* pkSprite = VeDynamicCast(VeSprite2D, pkRenderable);
		if(pkSprite && m_u32CombineCount < VE_MAX_COMBINED_SPRITE)
		{
			if((pkSprite->GetBlendFunc() == GetBlendFunc()) && (pkSprite->m_spResource == m_spResource))
			{
				VeCrazyCopy(((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex)),
					pkSprite->m_kVertex, sizeof(m_kVertex));
				++m_u32CombineCount;
				return true;
			}
		}
#		else
		VeSprite2D* pkSprite = VeDynamicCast(VeSprite2D, pkRenderable);
		if(pkSprite && m_kCombineList.Size() < (VE_MAX_COMBINED_SPRITE - 1))
		{
			if((pkSprite->GetBlendFunc() == GetBlendFunc()) && (pkSprite->m_spResource == m_spResource))
			{
				m_kCombineList.PushBack(pkSprite);
				return true;
			}
		}
#		endif
	}
	return false;
}
//--------------------------------------------------------------------------
void VeSprite2D::LinkNodeToParent()
{
#	ifdef VE_ENABLE_GLES2
	if(!m_u32CombineCount)
	{
		void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
		VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
		++m_u32CombineCount;
	}
	m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 6 * m_u32CombineCount;
	m_u32CombineCount = 0;
#	else
	m_pkCBufferTick->m_spBuffer = m_kCombineList.Size() ? m_spInstanceBuffer : m_spSingleBuffer;
#	endif
	m_pkSpriteNode->LinkToParent();
}
//--------------------------------------------------------------------------
void VeSprite2D::Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask)
{
	if(m_bEnable && (!m_bTransparency))
	{
		VeSceneRenderable2D::Visit(kQueue, u32Mask);
	}
}
//--------------------------------------------------------------------------
void VeSprite2D::UpdateNodeData(const VeTransform2D& kTransform,
	const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame)
{
	if(m_bDirty || u32UpdateFrame > m_u32UpdateFrame)
	{
		VeColor kMulAdjust = kMul;
		if(GetBlendFunc() == ALPHA_BLEND_MUL)
		{
			kMulAdjust.r *= kMulAdjust.a;
			kMulAdjust.g *= kMulAdjust.a;
			kMulAdjust.b *= kMulAdjust.a;
		}
		VeVector2D kOffset(m_kAnchor.x - m_kFrame.m_u16OffsetX, m_kAnchor.y - m_kFrame.m_u16OffsetY);
#		ifdef VE_ENABLE_GLES2
		if(m_kFrame.m_eOrient == TextureAtlas::FRAME_ZERO)
		{
			m_kVertex[0].m_kPosition = -kOffset;
			m_kVertex[1].m_kPosition = VeVector2D(VeFloat32(m_kFrame.m_u16TrimW), 0) - kOffset;
			m_kVertex[2].m_kPosition = VeVector2D(0, VeFloat32(m_kFrame.m_u16TrimH)) - kOffset;
			m_kVertex[3].m_kPosition = VeVector2D(VeFloat32(m_kFrame.m_u16TrimW), VeFloat32(m_kFrame.m_u16TrimH)) - kOffset;
		}
		else
		{
			m_kVertex[0].m_kPosition = VeVector2D(0, VeFloat32(m_kFrame.m_u16TrimW)) - kOffset;
			m_kVertex[1].m_kPosition = -kOffset;
			m_kVertex[2].m_kPosition = VeVector2D(VeFloat32(m_kFrame.m_u16TrimH), VeFloat32(m_kFrame.m_u16TrimW)) - kOffset;
			m_kVertex[3].m_kPosition = VeVector2D(VeFloat32(m_kFrame.m_u16TrimH), 0) - kOffset;
		}
		for(VeUInt32 i(0); i < 4; ++i)
		{
			Vertex& kVertex = m_kVertex[i];
			kTransform.ApplyPoint(kVertex.m_kPosition, kVertex.m_kPosition);
			kVertex.m_kMulColor = kMulAdjust;
			kVertex.m_kAddColor = kAdd;
		}
#		else
		VeTransform2D kTrans;
		if(m_kFrame.m_eOrient == TextureAtlas::FRAME_ZERO)
		{
			kTrans.Set(1,0,0,1,0,0);
		}
		else
		{
			kTrans.Set(0,-1,1,0,0,m_kParams.m_kTexcoord.x);
		}
		kTrans.x -= kOffset.x;
		kTrans.y -= kOffset.y;
		((VeTransform2D*)&m_kParams.m_kTransform0)->Concat(kTrans, kTransform);
		m_kParams.m_kMulColor = kMulAdjust;
		m_kParams.m_kAddColor = kAdd;
		VeRenderer::MappedSubresource kMapped;
		VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
		VeCrazyCopy(kMapped.m_pvData, &m_kParams, sizeof(m_kParams));
		VeRenderer::MapWriteRange kRange;
		kRange.m_u32Offset = 0;
		kRange.m_u32Size = sizeof(m_kParams);
		g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, kRange);
#		endif
		m_u32UpdateFrame = g_pRenderFrameManager->GetFrameCount();
		m_bDirty = false;
		m_bTransparency = (kMulAdjust.a + kAdd.a) == 0;
	}
}
//--------------------------------------------------------------------------
void VeSprite2D::UpdateData()
{
#	ifdef VE_ENABLE_GLES2
	VeUInt16 u16Right = m_kFrame.m_u16PosX + m_kFrame.m_u16TrimW;
	VeUInt16 u16Bottom = m_kFrame.m_u16PosY + m_kFrame.m_u16TrimH;
	if(m_spResource)
	{
		m_kVertex[0].m_u16TexX = m_kFrame.m_u16PosX;
		m_kVertex[0].m_u16TexY = m_kFrame.m_u16PosY;
		m_kVertex[1].m_u16TexX = u16Right;
		m_kVertex[1].m_u16TexY = m_kFrame.m_u16PosY;
		m_kVertex[2].m_u16TexX = m_kFrame.m_u16PosX;
		m_kVertex[2].m_u16TexY = u16Bottom;
		m_kVertex[3].m_u16TexX = u16Right;
		m_kVertex[3].m_u16TexY = u16Bottom;
		m_kVertex[0].m_u16TexZ = u16Right;
		m_kVertex[0].m_u16TexW = u16Bottom;
		m_kVertex[1].m_u16TexZ = m_kFrame.m_u16PosX;
		m_kVertex[1].m_u16TexW = u16Bottom;
		m_kVertex[2].m_u16TexZ = u16Right;
		m_kVertex[2].m_u16TexW = m_kFrame.m_u16PosY;
		m_kVertex[3].m_u16TexZ = m_kFrame.m_u16PosX;
		m_kVertex[3].m_u16TexW = m_kFrame.m_u16PosY;
	}
	else
	{
		m_kVertex[2].m_u16TexX = m_kFrame.m_u16PosX;
		m_kVertex[2].m_u16TexY = m_kFrame.m_u16PosY;
		m_kVertex[3].m_u16TexX = u16Right;
		m_kVertex[3].m_u16TexY = m_kFrame.m_u16PosY;
		m_kVertex[0].m_u16TexX = m_kFrame.m_u16PosX;
		m_kVertex[0].m_u16TexY = u16Bottom;
		m_kVertex[1].m_u16TexX = u16Right;
		m_kVertex[1].m_u16TexY = u16Bottom;
		m_kVertex[2].m_u16TexZ = u16Right;
		m_kVertex[2].m_u16TexW = u16Bottom;
		m_kVertex[3].m_u16TexZ = m_kFrame.m_u16PosX;
		m_kVertex[3].m_u16TexW = u16Bottom;
		m_kVertex[0].m_u16TexZ = u16Right;
		m_kVertex[0].m_u16TexW = m_kFrame.m_u16PosY;
		m_kVertex[1].m_u16TexZ = m_kFrame.m_u16PosX;
		m_kVertex[1].m_u16TexW = m_kFrame.m_u16PosY;
	}
	
#	else
	m_kParams.m_kTexcoord.x = VeFloat32(m_kFrame.m_u16TrimW);
	m_kParams.m_kTexcoord.y = VeFloat32(m_kFrame.m_u16TrimH);
	m_kParams.m_kTexcoord.z = VeFloat32(m_kFrame.m_u16PosX);
	m_kParams.m_kTexcoord.w = VeFloat32(m_kFrame.m_u16PosY);
#	endif
}
//--------------------------------------------------------------------------
void VeSprite2D::UpdateRenderNodeData(const VeChar8* pcTexName)
{
	VeFixedString kName;
	VeRenderNodeDataPtr spData;
#	ifdef VE_ENABLE_GLES2
	VeMemoryOStream kStream;
	kStream << VeUInt32(4);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(24);
	kStream << VeUInt32(0);
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = pcTexName;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeRenderTick::PS_SHADER_RESOURCE;
	kName = pcTexName;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(6);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkBlendTick = (VeOMBlendStateTick*)(spData->m_kTickList.GetHeadNode());
	m_pkBufferTick = (VeIAVertexBuffer*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
#	else
	VeMemoryOStream kStream;
	kStream << VeUInt32(4);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(2);
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = pcTexName;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeRenderTick::PS_SHADER_RESOURCE;
	kName = pcTexName;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(6);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkBlendTick = (VeOMBlendStateTick*)(spData->m_kTickList.GetHeadNode());
	m_pkCBufferTick = (VeVSCBuffer*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
#	endif
	m_pkSpriteNode->SetData(spData);
}
//--------------------------------------------------------------------------
void VeSprite2D::UpdateBlend()
{
	if(m_pkSpriteNode->m_spData)
	{
		switch(m_eBlend)
		{
		case ALPHA_BLEND:
			g_pRenderer->GetRenderObject("blend_alpha", m_pkBlendTick->m_spBlendState);
			break;
		case ALPHA_BLEND_MUL:
			g_pRenderer->GetRenderObject("blend_alpha_mul", m_pkBlendTick->m_spBlendState);
			break;
		case ADD:
			g_pRenderer->GetRenderObject("blend_add", m_pkBlendTick->m_spBlendState);
			break;
		default:
			m_pkBlendTick->m_spBlendState = NULL;
			break;
		}
	}
}
//--------------------------------------------------------------------------
void VeSprite2D::BeforeRender()
{
#	ifndef VE_ENABLE_GLES2
	if(m_kCombineList.Size())
	{
		VeRenderer::MappedSubresource kMapped;
		VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
		VeChar8* pcTemp = (VeChar8*)kMapped.m_pvData;
		VeCrazyCopy(pcTemp, &m_kParams, sizeof(m_kParams));
		pcTemp += sizeof(m_kParams);
		for(VeVector<VeSprite2D*>::iterator it = m_kCombineList.Begin();
			it != m_kCombineList.End(); ++it)
		{
			VeCrazyCopy(pcTemp, &((*it)->m_kParams), sizeof(m_kParams));
			pcTemp += sizeof(m_kParams);
		}
		VeUInt32 u32PrimCount = 1 + m_kCombineList.Size();
		VeRenderer::MapWriteRange kRange;
		kRange.m_u32Offset = 0;
		kRange.m_u32Size = u32PrimCount * sizeof(m_kParams);
		g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, kRange);
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED_INSTANCED);
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32IndexCountPerInstance = 6;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32InstanceCount = u32PrimCount;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_i32BaseVertexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartInstanceLocation = 0;
		m_kCombineList.Clear();
	}
	else
	{
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED);
		m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 6;
		m_pkDrawCall->m_kDrawIndexed.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexed.m_i32BaseVertexLocation = 0;
	}
#	endif
}
//--------------------------------------------------------------------------
void VeSprite2D::SetAnchorLua(VeFloat32 x, VeFloat32 y)
{
	SetAnchor(x, y);
}
//--------------------------------------------------------------------------
void VeSprite2D::SetAnchorLua(VeFloat32 x, VeFloat32 y,
	VeFloat32 f32OffsetX, VeFloat32 f32OffsetY)
{
	SetAnchor(x, y, f32OffsetX, f32OffsetY);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSprite2D)
{
	Module() [
		Class< VeSprite2D, Base<VeSceneRenderable2D> >().
			Def(ConstructorNew<void>()).
			Def(ConstructorNew<const VeChar8*>()).
			Def("SetAnchor", (void (VeSprite2D::*)(const VeVector2D&))&VeSprite2D::SetAnchor).
			Def("GetAnchor", &VeSprite2D::GetAnchor).
			Def("GetFrameName", &VeSprite2D::GetFrameName).
			Def("SetBlendFunc", &VeSprite2D::SetBlendFunc).
			Def("SetTexture", (void (VeSprite2D::*)(const VeChar8*,VeFloat32,VeFloat32))&VeSprite2D::SetTexture).
			Def("SetFrameName", &VeSprite2D::SetFrameName).
			Def("SetAnchor", (void (VeSprite2D::*)(VeFloat32,VeFloat32,VeFloat32,VeFloat32,bool))&VeSprite2D::SetAnchor).
			Def("SetAnchor", (void (VeSprite2D::*)(VeFloat32,VeFloat32,VeFloat32,VeFloat32))&VeSprite2D::SetAnchorLua).
			Def("SetAnchor", (void (VeSprite2D::*)(VeFloat32,VeFloat32))&VeSprite2D::SetAnchorLua).
			Def("GetWidth", &VeSprite2D::GetWidth).
			Def("GetHeight", &VeSprite2D::GetHeight)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSquareFrame, VeSceneRenderable2D);
//--------------------------------------------------------------------------
VeSquareFrame::VeSquareFrame(const VeBoundingBox2D& kRange)
	: VeSceneRenderable2D(VeSceneManager::QUEUE_SUPPORT_SHAPES)
	, m_kRange(kRange), m_eBlend(ALPHA_BLEND), m_pkBlendTick(NULL)
{
	m_pkRenderNode->SetData("draw_2d_square_frame");
	m_pkSpriteNode = VE_NEW VeRenderNode;
	m_pkSpriteNode->SetParent(m_pkRenderNode);
	m_pkSpriteNode->m_pkRenderable = this;
	m_u32UpdateFrame = 0;
	m_bDirty = false;
	m_bTransparency = false;
	VeFixedString kName;
	VeRenderNodeDataPtr spData;
#	ifdef VE_ENABLE_GLES2
	VeMemoryOStream kStream;
	kStream << VeUInt32(2);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(12);
	kStream << VeUInt32(0);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(8);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkBlendTick = (VeOMBlendStateTick*)(spData->m_kTickList.GetHeadNode());
	m_pkBufferTick = (VeIAVertexBuffer*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
	m_u32CombineCount = 0;
#	else
	VeMemoryOStream kStream;
	kStream << VeUInt32(sizeof(Params));
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(0);
	g_pRenderer->CreateBuffer("", kStream, &m_spSingleBuffer);
	kStream.Reset();
	g_pRenderer->GetRenderObject("quad_cb", m_spInstanceBuffer);
	kStream << VeUInt32(2);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(8);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkBlendTick = (VeOMBlendStateTick*)(spData->m_kTickList.GetHeadNode());
	m_pkCBufferTick = (VeVSCBuffer*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
#	endif
	m_pkSpriteNode->SetData(spData);
	UpdateBlend();
	m_bDirty = true;
}
//--------------------------------------------------------------------------
VeSquareFrame::~VeSquareFrame()
{
	VE_SAFE_DELETE(m_pkSpriteNode);
}
//--------------------------------------------------------------------------
bool VeSquareFrame::Combine(VeSceneRenderable* pkRenderable)
{
	if(VeSceneRenderable2D::Combine(pkRenderable))
	{
#		ifdef VE_ENABLE_GLES2
		if(!m_u32CombineCount)
		{
			void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
			VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
			++m_u32CombineCount;

		}
		VeSquareFrame* pkSquare = VeDynamicCast(VeSquareFrame, pkRenderable);
		if(pkSquare && m_u32CombineCount < VE_MAX_COMBINED_SPRITE)
		{
			if((pkSquare->GetBlendFunc() == GetBlendFunc()))
			{
				VeCrazyCopy(((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex)),
					pkSquare->m_kVertex, sizeof(m_kVertex));
				++m_u32CombineCount;
				return true;
			}
		}
#		else
		VeSquareFrame* pkSquare = VeDynamicCast(VeSquareFrame, pkRenderable);
		if(pkSquare && m_kCombineList.Size() < (VE_MAX_COMBINED_SPRITE - 1))
		{
			if((pkSquare->GetBlendFunc() == GetBlendFunc()))
			{
				m_kCombineList.PushBack(pkSquare);
				return true;
			}
		}
#		endif
	}
	return false;
}
//--------------------------------------------------------------------------
void VeSquareFrame::LinkNodeToParent()
{
#	ifdef VE_ENABLE_GLES2
	if(!m_u32CombineCount)
	{

		void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
		VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
		++m_u32CombineCount;
	}
	m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 8 * m_u32CombineCount;
	m_u32CombineCount = 0;
#	else
	m_pkCBufferTick->m_spBuffer = m_kCombineList.Size() ? m_spInstanceBuffer : m_spSingleBuffer;
#	endif
	m_pkSpriteNode->LinkToParent();
}
//--------------------------------------------------------------------------
void VeSquareFrame::Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask)
{
	if((!m_bTransparency))
	{
		VeSceneRenderable2D::Visit(kQueue, u32Mask);
	}
}
//--------------------------------------------------------------------------
void VeSquareFrame::UpdateNodeData(const VeTransform2D& kTransform,
	const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame)
{
	if(m_bDirty || u32UpdateFrame > m_u32UpdateFrame)
	{
#		ifdef VE_ENABLE_GLES2
		m_kVertex[0].m_kPosition = m_kRange.MinBounds();
		m_kVertex[1].m_kPosition = VeVector2D(m_kRange.MaxBounds().x, m_kRange.MinBounds().y);
		m_kVertex[2].m_kPosition = VeVector2D(m_kRange.MinBounds().x, m_kRange.MaxBounds().y);
		m_kVertex[3].m_kPosition = m_kRange.MaxBounds();
		for(VeUInt32 i(0); i < 4; ++i)
		{
			Vertex& kVertex = m_kVertex[i];
			kTransform.ApplyPoint(kVertex.m_kPosition, kVertex.m_kPosition);
			kVertex.m_kColor = kMul + kAdd;
		}
#		else
		VeTransform2D kTrans(1,0,0,1,m_kRange.MinBounds().x,m_kRange.MinBounds().y);
		((VeTransform2D*)&m_kParams.m_kTransform0)->Concat(kTrans, kTransform);
		m_kParams.m_kTransform1.z = m_kRange.Width();
		m_kParams.m_kTransform1.w = m_kRange.Height();
		m_kParams.m_kColor = kMul + kAdd;
		VeRenderer::MappedSubresource kMapped;
		VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
		VeCrazyCopy(kMapped.m_pvData, &m_kParams, sizeof(m_kParams));
		VeRenderer::MapWriteRange kRange;
		kRange.m_u32Offset = 0;
		kRange.m_u32Size = sizeof(m_kParams);
		g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, kRange);
#		endif
		m_u32UpdateFrame = g_pRenderFrameManager->GetFrameCount();
		m_bDirty = false;
		m_bTransparency = (kMul.a + kAdd.a) == 0;
	}
}
//--------------------------------------------------------------------------
void VeSquareFrame::UpdateBlend()
{
	if(m_pkSpriteNode->m_spData)
	{
		switch(m_eBlend)
		{
		case ALPHA_BLEND:
			g_pRenderer->GetRenderObject("blend_alpha", m_pkBlendTick->m_spBlendState);
			break;
		case ALPHA_BLEND_MUL:
			g_pRenderer->GetRenderObject("blend_alpha_mul", m_pkBlendTick->m_spBlendState);
			break;
		case ADD:
			g_pRenderer->GetRenderObject("blend_add", m_pkBlendTick->m_spBlendState);
			break;
		default:
			m_pkBlendTick->m_spBlendState = NULL;
			break;
		}
	}
}
//--------------------------------------------------------------------------
void VeSquareFrame::BeforeRender()
{
#	ifndef VE_ENABLE_GLES2
	if(m_kCombineList.Size())
	{
		VeRenderer::MappedSubresource kMapped;
		VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
		VeChar8* pcTemp = (VeChar8*)kMapped.m_pvData;
		VeCrazyCopy(pcTemp, &m_kParams, sizeof(m_kParams));
		pcTemp += sizeof(m_kParams);
		for(VeVector<VeSquareFrame*>::iterator it = m_kCombineList.Begin();
			it != m_kCombineList.End(); ++it)
		{
			VeCrazyCopy(pcTemp, &((*it)->m_kParams), sizeof(m_kParams));
			pcTemp += sizeof(m_kParams);
		}
		VeUInt32 u32PrimCount = 1 + m_kCombineList.Size();
		VeRenderer::MapWriteRange kRange;
		kRange.m_u32Offset = 0;
		kRange.m_u32Size = u32PrimCount * sizeof(m_kParams);
		g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, kRange);
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED_INSTANCED);
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32IndexCountPerInstance = 8;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32InstanceCount = u32PrimCount;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_i32BaseVertexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartInstanceLocation = 0;
		m_kCombineList.Clear();
	}
	else
	{
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED);
		m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 8;
		m_pkDrawCall->m_kDrawIndexed.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexed.m_i32BaseVertexLocation = 0;
	}
#	endif
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSquareFrame)
{
	Module() [
		Class< VeSquareFrame, Base<VeSceneRenderable2D> >().
			Def(ConstructorNew<const VeBoundingBox2D&>()).
			Def("SetRange", &VeSquareFrame::SetRange).
			Def("GetRange", &VeSquareFrame::GetRange).
            Def("SetBlendFunc", &VeSquareFrame::SetBlendFunc)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSquare, VeSceneRenderable2D);
//--------------------------------------------------------------------------
VeSquare::VeSquare(const VeBoundingBox2D& kRange)
	: VeSceneRenderable2D(VeSceneManager::QUEUE_SPRITES)
	, m_kRange(kRange), m_eBlend(ALPHA_BLEND)
{
	m_pkRenderNode->SetData("draw_2d_square");
	m_pkSpriteNode = VE_NEW VeRenderNode;
	m_pkSpriteNode->SetParent(m_pkRenderNode);
	m_pkSpriteNode->m_pkRenderable = this;
	m_u32UpdateFrame = 0;
	m_bDirty = false;
	m_bTransparency = false;
	VeFixedString kName;
	VeRenderNodeDataPtr spData;
#	ifdef VE_ENABLE_GLES2
	VeMemoryOStream kStream;
	kStream << VeUInt32(2);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(12);
	kStream << VeUInt32(0);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(6);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkBlendTick = (VeOMBlendStateTick*)(spData->m_kTickList.GetHeadNode());
	m_pkBufferTick = (VeIAVertexBuffer*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
	m_u32CombineCount = 0;
#	else
	VeMemoryOStream kStream;
	kStream << VeUInt32(sizeof(Params));
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(0);
	g_pRenderer->CreateBuffer("", kStream, &m_spSingleBuffer);
	kStream.Reset();
	g_pRenderer->GetRenderObject("quad_cb", m_spInstanceBuffer);
	kStream << VeUInt32(2);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(8);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkBlendTick = (VeOMBlendStateTick*)(spData->m_kTickList.GetHeadNode());
	m_pkCBufferTick = (VeVSCBuffer*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
#	endif
	m_pkSpriteNode->SetData(spData);
	UpdateBlend();
	m_bDirty = true;
}
//--------------------------------------------------------------------------
VeSquare::~VeSquare()
{
	VE_SAFE_DELETE(m_pkSpriteNode);
}
//--------------------------------------------------------------------------
bool VeSquare::Combine(VeSceneRenderable* pkRenderable)
{
	if(VeSceneRenderable2D::Combine(pkRenderable))
	{
#		ifdef VE_ENABLE_GLES2
		if(!m_u32CombineCount)
		{
			void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
			VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
			++m_u32CombineCount;
		}
		VeSquare* pkSquare = VeDynamicCast(VeSquare, pkRenderable);
		if(pkSquare && m_u32CombineCount < VE_MAX_COMBINED_SPRITE)
		{
			if((pkSquare->GetBlendFunc() == GetBlendFunc()))
			{
				VeCrazyCopy(((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex)),
					pkSquare->m_kVertex, sizeof(m_kVertex));
				++m_u32CombineCount;
				return true;
			}
		}
#		else
		VeSquare* pkSquare = VeDynamicCast(VeSquare, pkRenderable);
		if(pkSquare && m_kCombineList.Size() < (VE_MAX_COMBINED_SPRITE - 1))
		{
			if((pkSquare->GetBlendFunc() == GetBlendFunc()))
			{
				m_kCombineList.PushBack(pkSquare);
				return true;
			}
		}
#		endif
	}
	return false;
}
//--------------------------------------------------------------------------
void VeSquare::LinkNodeToParent()
{
#	ifdef VE_ENABLE_GLES2
	if(!m_u32CombineCount)
	{
		void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
		VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
		++m_u32CombineCount;
	}
	m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 6 * m_u32CombineCount;
	m_u32CombineCount = 0;
#	else
	m_pkCBufferTick->m_spBuffer = m_kCombineList.Size() ? m_spInstanceBuffer : m_spSingleBuffer;
#	endif
	m_pkSpriteNode->LinkToParent();
}
//--------------------------------------------------------------------------
void VeSquare::Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask)
{
	if((!m_bTransparency))
	{
		VeSceneRenderable2D::Visit(kQueue, u32Mask);
	}
}
//--------------------------------------------------------------------------
void VeSquare::UpdateNodeData(const VeTransform2D& kTransform,
	const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame)
{
	if(m_bDirty || u32UpdateFrame > m_u32UpdateFrame)
	{
#		ifdef VE_ENABLE_GLES2
		m_kVertex[0].m_kPosition = m_kRange.MinBounds();
		m_kVertex[1].m_kPosition = VeVector2D(m_kRange.MaxBounds().x, m_kRange.MinBounds().y);
		m_kVertex[2].m_kPosition = VeVector2D(m_kRange.MinBounds().x, m_kRange.MaxBounds().y);
		m_kVertex[3].m_kPosition = m_kRange.MaxBounds();
		for(VeUInt32 i(0); i < 4; ++i)
		{
			Vertex& kVertex = m_kVertex[i];
			kTransform.ApplyPoint(kVertex.m_kPosition, kVertex.m_kPosition);
			kVertex.m_kColor = kMul + kAdd;
		}
#		else
		VeTransform2D kTrans(1,0,0,1,m_kRange.MinBounds().x,m_kRange.MinBounds().y);
		((VeTransform2D*)&m_kParams.m_kTransform0)->Concat(kTrans, kTransform);
		m_kParams.m_kTransform1.z = m_kRange.Width();
		m_kParams.m_kTransform1.w = m_kRange.Height();
		m_kParams.m_kColor = kMul + kAdd;
		VeRenderer::MappedSubresource kMapped;
		VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
		VeCrazyCopy(kMapped.m_pvData, &m_kParams, sizeof(m_kParams));
		VeRenderer::MapWriteRange kRange;
		kRange.m_u32Offset = 0;
		kRange.m_u32Size = sizeof(m_kParams);
		g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, kRange);
#		endif
		m_u32UpdateFrame = g_pRenderFrameManager->GetFrameCount();
		m_bDirty = false;
		m_bTransparency = (kMul.a + kAdd.a) == 0;
	}
}
//--------------------------------------------------------------------------
void VeSquare::UpdateBlend()
{
	if(m_pkSpriteNode->m_spData)
	{
		switch(m_eBlend)
		{
		case ALPHA_BLEND:
			g_pRenderer->GetRenderObject("blend_alpha", m_pkBlendTick->m_spBlendState);
			break;
		case ALPHA_BLEND_MUL:
			g_pRenderer->GetRenderObject("blend_alpha_mul", m_pkBlendTick->m_spBlendState);
			break;
		case ADD:
			g_pRenderer->GetRenderObject("blend_add", m_pkBlendTick->m_spBlendState);
			break;
		default:
			m_pkBlendTick->m_spBlendState = NULL;
			break;
		}
	}
}
//--------------------------------------------------------------------------
void VeSquare::BeforeRender()
{
#	ifndef VE_ENABLE_GLES2
	if(m_kCombineList.Size())
	{
		VeRenderer::MappedSubresource kMapped;
		VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
		VeChar8* pcTemp = (VeChar8*)kMapped.m_pvData;
		VeCrazyCopy(pcTemp, &m_kParams, sizeof(m_kParams));
		pcTemp += sizeof(m_kParams);
		for(VeVector<VeSquare*>::iterator it = m_kCombineList.Begin();
			it != m_kCombineList.End(); ++it)
		{
			VeCrazyCopy(pcTemp, &((*it)->m_kParams), sizeof(m_kParams));
			pcTemp += sizeof(m_kParams);
		}
		VeUInt32 u32PrimCount = 1 + m_kCombineList.Size();
		VeRenderer::MapWriteRange kRange;
		kRange.m_u32Offset = 0;
		kRange.m_u32Size = u32PrimCount * sizeof(m_kParams);
		g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, kRange);
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED_INSTANCED);
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32IndexCountPerInstance = 6;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32InstanceCount = u32PrimCount;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_i32BaseVertexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartInstanceLocation = 0;
		m_kCombineList.Clear();
	}
	else
	{
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED);
		m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 6;
		m_pkDrawCall->m_kDrawIndexed.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexed.m_i32BaseVertexLocation = 0;
	}
#	endif
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSquare)
{
	Module() [
		Class< VeSquare, Base<VeSceneRenderable2D> >().
			Def(ConstructorNew<const VeBoundingBox2D&>()).
			Def("SetRange", &VeSquare::SetRange).
			Def("GetRange", &VeSquare::GetRange).
            Def("SetBlendFunc", &VeSquareFrame::SetBlendFunc)
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeSingleChar, VeSceneRenderable2D);
//--------------------------------------------------------------------------
VeSingleChar::VeSingleChar()
	: VeSceneRenderable2D(VeSceneManager::QUEUE_SPRITES), m_c16Char(0)
	, m_pkChar(NULL), m_f32Bias(0)
{
	
	Init();
}
//--------------------------------------------------------------------------
VeSingleChar::~VeSingleChar()
{
	VE_SAFE_DELETE(m_pkSpriteNode);
}
//--------------------------------------------------------------------------
void VeSingleChar::SetChar(VeChar16 c16Char, const VeChar8* pcFont)
{
	VeFontPtr spFont = VeLoadFontSync(pcFont, g_pResourceManager->GetDefaultGroupName());
	SetChar(c16Char, spFont);
}
//--------------------------------------------------------------------------
void VeSingleChar::SetChar(VeChar16 c16Char, const VeFontPtr& spFont)
{
	if(c16Char != m_c16Char || m_spFont != spFont)
	{
		if(spFont && spFont->GetState() == VeResource::LOADED)
		{
			m_spFont = spFont;

			if(m_c16Char != c16Char && m_spFont)
			{
				if(m_c16Char)
				{
					m_spFont->DecChar(c16Char);
				}
				if(c16Char)
				{
					m_pkChar = m_spFont->IncChar(c16Char);
				}
				m_c16Char = c16Char;
			}
			UpdateChar();
			m_bDirty = true;
		}
		else
		{
			m_c16Char = 0;
			m_spFont = NULL;
		}
	}
}
//--------------------------------------------------------------------------
void VeSingleChar::Init()
{
	VeFixedString kName;
	VeRenderNodeDataPtr spData;
	m_pkRenderNode->SetData("draw_2d_text");
	m_pkSpriteNode = VE_NEW VeRenderNode;
	m_pkSpriteNode->SetParent(m_pkRenderNode);
	m_pkSpriteNode->m_pkRenderable = this;
	m_u32UpdateFrame = 0;
	m_bDirty = false;
	m_bTransparency = false;
#	ifdef VE_ENABLE_GLES2
	VeMemoryOStream kStream;
	kStream << VeUInt32(3);
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(24);
	kStream << VeUInt32(0);
	kStream << VeRenderTick::PS_SHADER_RESOURCE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(6);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkBufferTick = (VeIAVertexBuffer*)(spData->m_kTickList.GetHeadNode());
	m_pkPSShaderResTick = (VePSShaderResource*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkCBufferTick = (VeVSCBuffer*)(spData->m_kTickList.GetHeadNode()->Next()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
	m_u32CombineCount = 0;
#	else
	VeMemoryOStream kStream;
	kStream << VeUInt32(sizeof(Params));
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(0);
	g_pRenderer->CreateBuffer("", kStream, &m_spSingleBuffer);
	g_pRenderer->GetRenderObject("quad_cb", m_spInstanceBuffer);
	kStream.Reset();
	kStream << VeUInt32(2);
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeRenderTick::PS_SHADER_RESOURCE;
	kName = "null";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeUInt32(1);
	kStream << VeRenderCall::DRAW_INDEXED;
	kStream << VeUInt32(6);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("", kStream, &spData);
	m_pkCBufferTick = (VeVSCBuffer*)(spData->m_kTickList.GetHeadNode());
	m_pkPSShaderResTick = (VePSShaderResource*)(spData->m_kTickList.GetHeadNode()->Next());
	m_pkDrawCall = (VeDrawCall*)(spData->m_kCallList.GetHeadNode());
#	endif
	m_pkSpriteNode->SetData(spData);
}
//--------------------------------------------------------------------------
void VeSingleChar::UpdateChar()
{
	if(m_pkChar && m_pkChar->m_tFirst >= 0)
	{
		VeFont::CacheInfo& kInfo = m_spFont->m_kCharCacheInfo[m_pkChar->m_tFirst];
		VeChar8 acBuffer[256];
		VeSprintf(acBuffer, "%s_%d", (const VeChar8*)m_spFont->m_kName, kInfo.m_i16Page);
		g_pRenderer->GetRenderObject(acBuffer, m_pkPSShaderResTick->m_spShaderResourceView);
		g_pRenderer->GetRenderObject(m_spFont->GetName(), m_pkCBufferTick->m_spBuffer);
	}
}
//--------------------------------------------------------------------------
bool VeSingleChar::Combine(VeSceneRenderable* pkRenderable)
{
	if(VeSceneRenderable2D::Combine(pkRenderable))
	{
#		ifdef VE_ENABLE_GLES2
		if(!m_u32CombineCount)
		{
			void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
			VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
			++m_u32CombineCount;
		}
		VeSingleChar* pkSingleChar = VeDynamicCast(VeSingleChar, pkRenderable);
		if(pkSingleChar && m_u32CombineCount < VE_MAX_COMBINED_SPRITE)
		{
			if(pkSingleChar->m_spFont == m_spFont
				&& pkSingleChar->m_pkPSShaderResTick->m_spShaderResourceView == m_pkPSShaderResTick->m_spShaderResourceView)
			{
				VeCrazyCopy(((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex)),
					pkSingleChar->m_kVertex, sizeof(m_kVertex));
				++m_u32CombineCount;
				return true;
			}
		}
#		else
		VeSingleChar* pkSingleChar = VeDynamicCast(VeSingleChar, pkRenderable);
		if(pkSingleChar && m_kCombineList.Size() < (VE_MAX_COMBINED_SPRITE - 1))
		{
			if(pkSingleChar->m_spFont == m_spFont
				&& pkSingleChar->m_pkPSShaderResTick->m_spShaderResourceView == m_pkPSShaderResTick->m_spShaderResourceView)
			{
				m_kCombineList.PushBack(pkSingleChar);
				return true;
			}
		}
#		endif
	}
	return false;
}
//--------------------------------------------------------------------------
void VeSingleChar::LinkNodeToParent()
{
#	ifdef VE_ENABLE_GLES2
	if(!m_u32CombineCount)
	{
		void* pvData = ((VeRendererGLES2*)g_pRenderer)->UseQuadBuffer(sizeof(m_kVertex), &(m_pkBufferTick->m_u32Offset));
		VeCrazyCopy(pvData, m_kVertex, sizeof(m_kVertex));
		++m_u32CombineCount;
	}
	m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 6 * m_u32CombineCount;
	m_u32CombineCount = 0;
#	else
	m_pkCBufferTick->m_spBuffer = m_kCombineList.Size() ? m_spInstanceBuffer : m_spSingleBuffer;
#	endif
	m_pkSpriteNode->LinkToParent();
}
//--------------------------------------------------------------------------
void VeSingleChar::Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask)
{
	if(m_spFont && m_c16Char && m_pkChar && (!m_bTransparency) && m_pkChar->m_tFirst >= 0)
	{
		VeSceneRenderable2D::Visit(kQueue, u32Mask);
	}
}
//--------------------------------------------------------------------------
void VeSingleChar::UpdateNodeData(const VeTransform2D& kTransform,
	const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame)
{
	if(m_spFont && m_c16Char && m_pkChar && m_pkChar->m_tFirst >= 0)
	{
		if(m_bDirty || u32UpdateFrame > m_u32UpdateFrame)
		{
			VeFont::Info& kInfo = m_spFont->m_kCharInfo[m_pkChar->m_tFirst];
			VeFont::CacheInfo& kCacheInfo = m_spFont->m_kCharCacheInfo[m_pkChar->m_tFirst];
#		ifdef VE_ENABLE_GLES2
			m_kVertex[0].m_kPosition.x = VeFloat32(kInfo.m_i16Left);
			m_kVertex[0].m_kPosition.y = VeFloat32(kInfo.m_i16Top);
			m_kVertex[0].m_f32Bias = m_f32Bias;
			m_kVertex[0].m_u16TexX = kCacheInfo.x * m_spFont->m_u32CharSize;
			m_kVertex[0].m_u16TexY = kCacheInfo.y * m_spFont->m_u32CharSize;
			m_kVertex[0].m_u16TexZ = kCacheInfo.x * m_spFont->m_u32CharSize + kInfo.m_i16Width;
			m_kVertex[0].m_u16TexW = kCacheInfo.y * m_spFont->m_u32CharSize + kInfo.m_i16Height;

			m_kVertex[1].m_kPosition.x = VeFloat32(kInfo.m_i16Left + kInfo.m_i16Width);
			m_kVertex[1].m_kPosition.y = VeFloat32(kInfo.m_i16Top);
			m_kVertex[1].m_f32Bias = m_f32Bias;
			m_kVertex[1].m_u16TexX = kCacheInfo.x * m_spFont->m_u32CharSize + kInfo.m_i16Width;
			m_kVertex[1].m_u16TexY = kCacheInfo.y * m_spFont->m_u32CharSize;
			m_kVertex[1].m_u16TexZ = kCacheInfo.x * m_spFont->m_u32CharSize;
			m_kVertex[1].m_u16TexW = kCacheInfo.y * m_spFont->m_u32CharSize + kInfo.m_i16Height;

			m_kVertex[2].m_kPosition.x = VeFloat32(kInfo.m_i16Left);
			m_kVertex[2].m_kPosition.y = VeFloat32(kInfo.m_i16Top + kInfo.m_i16Height);
			m_kVertex[2].m_f32Bias = m_f32Bias;
			m_kVertex[2].m_u16TexX = kCacheInfo.x * m_spFont->m_u32CharSize;
			m_kVertex[2].m_u16TexY = kCacheInfo.y * m_spFont->m_u32CharSize + kInfo.m_i16Height;
			m_kVertex[2].m_u16TexZ = kCacheInfo.x * m_spFont->m_u32CharSize + kInfo.m_i16Width;
			m_kVertex[2].m_u16TexW = kCacheInfo.y * m_spFont->m_u32CharSize;

			m_kVertex[3].m_kPosition.x = VeFloat32(kInfo.m_i16Left + kInfo.m_i16Width);
			m_kVertex[3].m_kPosition.y = VeFloat32(kInfo.m_i16Top + kInfo.m_i16Height);
			m_kVertex[3].m_f32Bias = m_f32Bias;
			m_kVertex[3].m_u16TexX = kCacheInfo.x * m_spFont->m_u32CharSize + kInfo.m_i16Width;
			m_kVertex[3].m_u16TexY = kCacheInfo.y * m_spFont->m_u32CharSize + kInfo.m_i16Height;
			m_kVertex[3].m_u16TexZ = kCacheInfo.x * m_spFont->m_u32CharSize;
			m_kVertex[3].m_u16TexW = kCacheInfo.y * m_spFont->m_u32CharSize;

			for(VeUInt32 i(0); i < 4; ++i)
			{
				Vertex& kVertex = m_kVertex[i];
				kTransform.ApplyPoint(kVertex.m_kPosition, kVertex.m_kPosition);
				kVertex.m_kColor = kMul + kAdd;
			}
#		else
			VeTransform2D kTrans;
			kTrans.Set(1,0,0,1,0,0);
			kTrans.x = kInfo.m_i16Left;
			kTrans.y = kInfo.m_i16Top;
			((VeTransform2D*)&m_kParams.m_kTransform0)->Concat(kTrans, kTransform);
			m_kParams.m_kTransform1.z = kInfo.m_i16Width;
			m_kParams.m_kTransform1.w = kInfo.m_i16Height;
			m_kParams.m_kTransform2.x = kCacheInfo.x;
			m_kParams.m_kTransform2.y = kCacheInfo.y;
			m_kParams.m_kTransform2.z = VeFloat32(m_spFont->m_i16DistBase) / 32768.0f * 32.0f + 1.0f;
			m_kParams.m_kTransform2.w = (VeFloat32(m_spFont->m_i16DistScale) / 32768.0f + 1.0f) * 32.0f + m_f32Bias;
			m_kParams.m_kColor = kMul + kAdd;
			VeRenderer::MappedSubresource kMapped;
			VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
			VeCrazyCopy(kMapped.m_pvData, &m_kParams, sizeof(m_kParams));
			VeRenderer::MapWriteRange kRange;
			kRange.m_u32Offset = 0;
			kRange.m_u32Size = sizeof(m_kParams);
			g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spSingleBuffer), 0, kRange);
#		endif
			m_u32UpdateFrame = g_pRenderFrameManager->GetFrameCount();
			m_bDirty = false;
			m_bTransparency = (kMul.a + kAdd.a) == 0;
		}
	}
}
//--------------------------------------------------------------------------
void VeSingleChar::BeforeRender()
{
#	ifndef VE_ENABLE_GLES2
	if(m_kCombineList.Size())
	{
		VeRenderer::MappedSubresource kMapped;
		VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
		VeChar8* pcTemp = (VeChar8*)kMapped.m_pvData;
		VeCrazyCopy(pcTemp, &m_kParams, sizeof(m_kParams));
		pcTemp += sizeof(m_kParams);
		for(VeVector<VeSingleChar*>::iterator it = m_kCombineList.Begin();
			it != m_kCombineList.End(); ++it)
		{
			VeCrazyCopy(pcTemp, &((*it)->m_kParams), sizeof(m_kParams));
			pcTemp += sizeof(m_kParams);
		}
		VeUInt32 u32PrimCount = 1 + m_kCombineList.Size();
		VeRenderer::MapWriteRange kRange;
		kRange.m_u32Offset = 0;
		kRange.m_u32Size = u32PrimCount * sizeof(m_kParams);
		g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spInstanceBuffer), 0, kRange);
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED_INSTANCED);
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32IndexCountPerInstance = 6;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32InstanceCount = u32PrimCount;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_i32BaseVertexLocation = 0;
		m_pkDrawCall->m_kDrawIndexedInstanced.m_u32StartInstanceLocation = 0;
		m_kCombineList.Clear();
	}
	else
	{
		m_pkDrawCall->SetType(VeRenderCall::DRAW_INDEXED);
		m_pkDrawCall->m_kDrawIndexed.m_u32IndexCount = 6;
		m_pkDrawCall->m_kDrawIndexed.m_u32StartIndexLocation = 0;
		m_pkDrawCall->m_kDrawIndexed.m_i32BaseVertexLocation = 0;
	}
#	endif
}
//--------------------------------------------------------------------------
