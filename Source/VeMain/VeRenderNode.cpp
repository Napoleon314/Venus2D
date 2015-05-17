////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderNode.cpp
//  Version:     v1.00
//  Created:     9/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeRenderNode.inl"
#endif

//--------------------------------------------------------------------------
VeRenderTick::VeRenderTick(Type eType) : m_eType(eType)
{
	m_tContent = this;
}
//--------------------------------------------------------------------------
VeRenderTick::~VeRenderTick()
{

}
//--------------------------------------------------------------------------
VeVSCBuffer::VeVSCBuffer(const VeChar8* pcName, VeUInt32 u32Slot)
	: VeRenderTick(VeRenderTick::VS_CONSTANT_BUFFER), m_u32Slot(u32Slot)
{
	g_pRenderer->GetRenderObject(pcName, m_spBuffer);
}
//--------------------------------------------------------------------------
VeVSCBuffer::~VeVSCBuffer()
{

}
//--------------------------------------------------------------------------
VeVSShader::VeVSShader(const VeChar8* pcName)
	: VeRenderTick(VeRenderTick::VS_SHADER)
{
	g_pRenderer->GetRenderObject(pcName, m_spShader);
	VE_ASSERT(m_spShader);
}
//--------------------------------------------------------------------------
VeVSShader::~VeVSShader()
{

}
//--------------------------------------------------------------------------
VePSSampler::VePSSampler(const VeChar8* pcName, VeUInt32 u32Slot)
	: VeRenderTick(VeRenderTick::PS_SAMPLER), m_u32Slot(u32Slot)
{
	g_pRenderer->GetRenderObject(pcName, m_spSampler);
	VE_ASSERT(m_spSampler);
}
//--------------------------------------------------------------------------
VePSSampler::~VePSSampler()
{

}
//--------------------------------------------------------------------------
VePSShader::VePSShader(const VeChar8* pcName)
	: VeRenderTick(VeRenderTick::PS_SHADER)
{
	g_pRenderer->GetRenderObject(pcName, m_spShader);
	VE_ASSERT(m_spShader);
}
//--------------------------------------------------------------------------
VePSShader::~VePSShader()
{

}
//--------------------------------------------------------------------------
VePSShaderResource::VePSShaderResource(const VeChar8* pcName,
	VeUInt32 u32Slot)
	: VeRenderTick(VeRenderTick::PS_SHADER_RESOURCE), m_u32Slot(u32Slot)
{
	g_pRenderer->GetRenderObject(pcName, m_spShaderResourceView);
}
//--------------------------------------------------------------------------
VePSShaderResource::~VePSShaderResource()
{

}
//--------------------------------------------------------------------------
VeOMBlendStateTick::VeOMBlendStateTick(const VeChar8* pcName)
	: VeRenderTick(VeRenderTick::OM_BLEND_STATE)
	, m_u32SampleMask(0xffffffff)
{
	VeZeroMemory(m_af32Factor, sizeof(m_af32Factor));
	g_pRenderer->GetRenderObject(pcName, m_spBlendState);
}
//--------------------------------------------------------------------------
VeOMBlendStateTick::~VeOMBlendStateTick()
{

}
//--------------------------------------------------------------------------
VeOMDepthStencilStateTick::VeOMDepthStencilStateTick(const VeChar8* pcName,
	VeUInt32 u32StencilRef)
	: VeRenderTick(VeRenderTick::OM_DEPTH_STENCIL_STATE)
	, m_u32StencilRef(u32StencilRef)
{
	g_pRenderer->GetRenderObject(pcName, m_spDepthStencilState);
}
//--------------------------------------------------------------------------
VeOMDepthStencilStateTick::~VeOMDepthStencilStateTick()
{

}
//--------------------------------------------------------------------------
VeOMDepthStencilViewTick::VeOMDepthStencilViewTick(const VeChar8* pcName)
	: VeRenderTick(VeRenderTick::OM_DEPTH_STENCIL_VIEW)
{
	g_pRenderer->GetRenderObject(pcName, m_spDepthStencil);
	VE_ASSERT(m_spDepthStencil);
}
//--------------------------------------------------------------------------
VeOMDepthStencilViewTick::~VeOMDepthStencilViewTick()
{
	
}
//--------------------------------------------------------------------------
VeOMRenderTargetViewTick::VeOMRenderTargetViewTick(const VeChar8* pcName,
	VeUInt32 u32Slot)
	: VeRenderTick(VeRenderTick::OM_RENDER_TARGET_VIEW), m_u32Slot(u32Slot)
{
	g_pRenderer->GetRenderObject(pcName, m_spRenderTarget);
	VE_ASSERT(m_spRenderTarget);
}
//--------------------------------------------------------------------------
VeOMRenderTargetViewTick::~VeOMRenderTargetViewTick()
{

}
//--------------------------------------------------------------------------
VeRSScissorRectTick::VeRSScissorRectTick(VeInt16 x, VeInt16 y, VeInt16 w,
	VeInt16 h, VeUInt32 u32Slot)
	: VeRenderTick(VeRenderTick::RS_SCISSOR_RECT), m_i16Left(x)
	, m_i16Top(y), m_i16Width(w), m_i16Height(h), m_u32Slot(u32Slot)
{

}
//--------------------------------------------------------------------------
VeRSScissorRectTick::~VeRSScissorRectTick()
{

}
//--------------------------------------------------------------------------
VeRSViewportTick::VeRSViewportTick(const VeVector4D& kViewport,
	VeUInt32 u32Slot)
	: VeRenderTick(VeRenderTick::RS_VIEWPORT), m_kViewport(kViewport)
	, m_u32Slot(u32Slot)
{

}
//--------------------------------------------------------------------------
VeRSViewportTick::~VeRSViewportTick()
{

}
//--------------------------------------------------------------------------
VeIAInputLayout::VeIAInputLayout(const VeChar8* pcName)
	: VeRenderTick(VeRenderTick::IA_INPUT_LAYOUT)
{
	g_pRenderer->GetRenderObject(pcName, m_spInputLayout);
	VE_ASSERT(m_spInputLayout);
}
//--------------------------------------------------------------------------
VeIAInputLayout::~VeIAInputLayout()
{

}
//--------------------------------------------------------------------------
VeIAVertexBuffer::VeIAVertexBuffer(const VeChar8* pcName,
	VeUInt32 u32Slot, VeUInt32 u32Stride, VeUInt32 u32Offset)
	: VeRenderTick(VeRenderTick::IA_VERTEX_BUFFER), m_u32Slot(u32Slot)
	, m_u32Stride(u32Stride), m_u32Offset(u32Offset)
{
	g_pRenderer->GetRenderObject(pcName, m_spBuffer);
	VE_ASSERT(m_spBuffer);
}
//--------------------------------------------------------------------------
VeIAVertexBuffer::~VeIAVertexBuffer()
{

}
//--------------------------------------------------------------------------
VeIAIndexBuffer::VeIAIndexBuffer(const VeChar8* pcName, VeUInt32 u32Format)
	: VeRenderTick(VeRenderTick::IA_INDEX_BUFFER), m_u32Format(u32Format)
{
	g_pRenderer->GetRenderObject(pcName, m_spBuffer);
	VE_ASSERT(m_u32Format == VeRenderer::FMT_R32_UINT
		|| m_u32Format == VeRenderer::FMT_R16_UINT);
}
//--------------------------------------------------------------------------
VeIAIndexBuffer::~VeIAIndexBuffer()
{

}
//--------------------------------------------------------------------------
VeIAPrimitiveTopology::VeIAPrimitiveTopology(Topology eTopology)
	: VeRenderTick(VeRenderTick::IA_PRIMITIVE_TOPOLOGY)
	, m_eTopology(eTopology)
{

}
//--------------------------------------------------------------------------
VeIAPrimitiveTopology::~VeIAPrimitiveTopology()
{

}
//--------------------------------------------------------------------------
VeRSState::VeRSState(const VeChar8* pcName)
	: VeRenderTick(VeRenderTick::RS_STATE)
{
	g_pRenderer->GetRenderObject(pcName, m_spState);
}
//--------------------------------------------------------------------------
VeRSState::~VeRSState()
{

}
//--------------------------------------------------------------------------
VeRenderCall::VeRenderCall(Type eType) : m_eType(eType)
{
	m_tContent = this;
}
//--------------------------------------------------------------------------
VeRenderCall::~VeRenderCall()
{

}
//--------------------------------------------------------------------------
VeClearCall::VeClearCall() : VeRenderCall(CLEAR)
	, m_bClearColor(false), m_bClearDepth(false), m_bClearStencil(false)
	, m_u8Stencil(0), m_f32Depth(1.0f)
{

}
//--------------------------------------------------------------------------
VeClearCall::~VeClearCall()
{

}
//--------------------------------------------------------------------------
VeDrawCall::VeDrawCall(Type eType)
	: VeRenderCall(eType)
{
	VE_ASSERT(eType != CLEAR);
}
//--------------------------------------------------------------------------
VeRenderNodeData::VeRenderNodeData(const VeChar8* pcName)
	: m_kName(pcName)
{

}
//--------------------------------------------------------------------------
VeRenderNodeData::~VeRenderNodeData()
{
	m_kTickList.BeginIterator();
	while(!m_kTickList.IsEnd())
	{
		VeRenderTick* pkTick = m_kTickList.GetIterNode()->m_tContent;
		m_kTickList.Next();
		VE_DELETE(pkTick);
	}
	VE_ASSERT(m_kTickList.Empty());

	m_kCallList.BeginIterator();
	while(!m_kCallList.IsEnd())
	{
		VeRenderCall* pkCall = m_kCallList.GetIterNode()->m_tContent;
		m_kCallList.Next();
		VE_DELETE(pkCall);
	}
	VE_ASSERT(m_kCallList.Empty());
}
//--------------------------------------------------------------------------
VeRenderNode::VeRenderNode(const VeChar8* pcDataName)
	: m_pkParent(NULL), m_u32Priority(VE_INFINITE), m_pkRenderable(NULL)
{
	m_tContent = this;
	SetData(pcDataName);
}
//--------------------------------------------------------------------------
VeRenderNode::VeRenderNode(const VeRenderNodeDataPtr& spData)
	: m_pkParent(NULL), m_u32Priority(VE_INFINITE), m_pkRenderable(NULL)
{
	m_tContent = this;
	SetData(spData);
}
//--------------------------------------------------------------------------
VeRenderNode::~VeRenderNode()
{
	
}
//--------------------------------------------------------------------------
void VeRenderNode::SetData(const VeChar8* pcName)
{
	m_spData = pcName ? g_pRenderer->GetRenderNodeData(pcName) : NULL;
}
//--------------------------------------------------------------------------
void VeRenderNode::LinkToParent()
{
	if((!IsAttach()) && m_pkParent)
	{
		VeRefList<VeRenderNode*>& kRenderList = m_pkParent->m_kRenderChildren;
		switch(m_u32Priority)
		{
		case 0:
			kRenderList.AttachFront(*this);
			break;
		case VE_INFINITE:
			kRenderList.AttachBack(*this);
			break;
		default:
			{
				VeRefList<VeRenderNode*>::iterator it = kRenderList.GetHeadNode();
				while(!kRenderList.IsEnd(it))
				{
					if(GetPriority() < it->m_tContent->GetPriority())
					{
						kRenderList.AttachBefore(*it, *this);
					}
					VeRefList<VeRenderNode*>::Next(it);
				}
				if(!IsAttach())
				{
					kRenderList.AttachBack(*this);
				}
			}
			break;
		}
		m_pkParent->LinkToParent();
	}
}
//--------------------------------------------------------------------------
VeRenderProcess::VeRenderProcess(Type eType, const VeChar8* pcName)
	: m_eType(eType), m_kName(pcName)
{

}
//--------------------------------------------------------------------------
VeRenderProcess::~VeRenderProcess()
{

}
//--------------------------------------------------------------------------
bool VeRenderProcess::Update(VeBinaryIStream& kStream)
{
	return false;
}
//--------------------------------------------------------------------------
