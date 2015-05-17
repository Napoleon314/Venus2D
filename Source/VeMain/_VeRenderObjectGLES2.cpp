////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRenderObjectGLES2.cpp
//  Version:     v1.00
//  Created:     14/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeRenderObjectGLES2.h"
#include "_VeRendererGLES2.h"

//--------------------------------------------------------------------------
#ifdef VE_ENABLE_GLES2
//--------------------------------------------------------------------------
VeUInt16 GetGLBlend(VeRenderer::Blend eBlend, bool bAlpha)
{
	switch(eBlend)
	{
	case VeRenderer::BLEND_ZERO:
		return GL_ZERO;
	case VeRenderer::BLEND_ONE:
		return GL_ONE;
	case VeRenderer::BLEND_SRC_COLOR:
		return GL_SRC_COLOR;
	case VeRenderer::BLEND_INV_SRC_COLOR:
		return GL_ONE_MINUS_SRC_COLOR;
	case VeRenderer::BLEND_SRC_ALPHA:
		return GL_SRC_ALPHA;
	case VeRenderer::BLEND_INV_SRC_ALPHA:
		return GL_ONE_MINUS_SRC_ALPHA;
	case VeRenderer::BLEND_DEST_ALPHA:
		return GL_DST_ALPHA;
	case VeRenderer::BLEND_INV_DEST_ALPHA:
		return GL_ONE_MINUS_DST_ALPHA;
	case VeRenderer::BLEND_DEST_COLOR:
		return GL_DST_COLOR;
	case VeRenderer::BLEND_INV_DEST_COLOR:
		return GL_ONE_MINUS_DST_COLOR;
	case VeRenderer::BLEND_SRC_ALPHA_SAT:
		return GL_SRC_ALPHA_SATURATE;
	case VeRenderer::BLEND_BLEND_FACTOR:
		if(bAlpha)
		{
			return GL_CONSTANT_ALPHA;
		}
		else
		{
			return GL_CONSTANT_COLOR;
		}
	case VeRenderer::BLEND_INV_BLEND_FACTOR:
		if(bAlpha)
		{
			return GL_ONE_MINUS_CONSTANT_ALPHA;
		}
		else
		{
			return GL_ONE_MINUS_CONSTANT_COLOR;
		} 
	default:
		return GL_ZERO;
	}
}
//--------------------------------------------------------------------------
VeRenderer::Blend GetBlend(VeUInt16 u16Blend)
{
	switch(u16Blend)
	{
	case GL_ZERO:
		return VeRenderer::BLEND_ZERO;
	case GL_ONE:
		return VeRenderer::BLEND_ONE;
	case GL_SRC_COLOR:
		return VeRenderer::BLEND_SRC_COLOR;
	case GL_ONE_MINUS_SRC_COLOR:
		return VeRenderer::BLEND_INV_SRC_COLOR;
	case GL_SRC_ALPHA:
		return VeRenderer::BLEND_SRC_ALPHA;
	case GL_ONE_MINUS_SRC_ALPHA:
		return VeRenderer::BLEND_INV_SRC_ALPHA;
	case GL_DST_ALPHA:
		return VeRenderer::BLEND_DEST_ALPHA;
	case GL_ONE_MINUS_DST_ALPHA:
		return VeRenderer::BLEND_INV_DEST_ALPHA;
	case GL_DST_COLOR:
		return VeRenderer::BLEND_DEST_COLOR;
	case GL_ONE_MINUS_DST_COLOR:
		return VeRenderer::BLEND_INV_DEST_COLOR;
	case GL_SRC_ALPHA_SATURATE:
		return VeRenderer::BLEND_SRC_ALPHA_SAT;
	case GL_CONSTANT_ALPHA:
		return VeRenderer::BLEND_BLEND_FACTOR;
	case GL_CONSTANT_COLOR:
		return VeRenderer::BLEND_BLEND_FACTOR;
	case GL_ONE_MINUS_CONSTANT_ALPHA:
		return VeRenderer::BLEND_INV_BLEND_FACTOR;
	case GL_ONE_MINUS_CONSTANT_COLOR:
		return VeRenderer::BLEND_INV_BLEND_FACTOR;
	default:
		return VeRenderer::BLEND_ZERO;
	}
}
//--------------------------------------------------------------------------
VeUInt16 GetGLBlendOp(VeRenderer::BlendOp eBlendOp)
{
	switch(eBlendOp)
	{
	case VeRenderer::BLEND_OP_ADD:
		return GL_FUNC_ADD;
	case VeRenderer::BLEND_OP_SUBTRACT:
		return GL_FUNC_SUBTRACT;
	case VeRenderer::BLEND_OP_REV_SUBTRACT:
		return GL_FUNC_REVERSE_SUBTRACT;
	default:
		return GL_FUNC_ADD;
	}
}
//--------------------------------------------------------------------------
VeRenderer::BlendOp GetBlendOp(VeUInt16 u16BlendOp)
{
	switch(u16BlendOp)
	{
	case GL_FUNC_ADD:
		return VeRenderer::BLEND_OP_ADD;
	case GL_FUNC_SUBTRACT:
		return VeRenderer::BLEND_OP_SUBTRACT;
	case GL_FUNC_REVERSE_SUBTRACT:
		return VeRenderer::BLEND_OP_REV_SUBTRACT;
	default:
		return VeRenderer::BLEND_OP_ADD; 
	}
}
//--------------------------------------------------------------------------
VeUInt16 GetGLComparisonFunc(VeRenderer::ComparisonFunc eFunc)
{
	switch(eFunc)
	{
	case VeRenderer::COMPARISON_NEVER:
		return GL_NEVER;
	case VeRenderer::COMPARISON_LESS:
		return GL_LESS;
	case VeRenderer::COMPARISON_EQUAL:
		return GL_EQUAL;
	case VeRenderer::COMPARISON_LESS_EQUAL:
		return GL_LEQUAL;
	case VeRenderer::COMPARISON_GREATER:
		return GL_GREATER;
	case VeRenderer::COMPARISON_NOT_EQUAL:
		return GL_NOTEQUAL;
	case VeRenderer::COMPARISON_GREATER_EQUAL:
		return GL_GEQUAL;
	case VeRenderer::COMPARISON_ALWAYS:
		return GL_ALWAYS;
	default:
		return GL_NEVER;
	}
}
//--------------------------------------------------------------------------
VeUInt16 GetGLStencilOp(VeRenderer::StencilOp eStencilOp)
{
	switch(eStencilOp)
	{
	case VeRenderer::STENCIL_OP_KEEP:
		return GL_KEEP;
	case VeRenderer::STENCIL_OP_ZERO:
		return GL_ZERO;
	case VeRenderer::STENCIL_OP_REPLACE:
		return GL_REPLACE;
	case VeRenderer::STENCIL_OP_INCR_SAT:
		return GL_INCR;
	case VeRenderer::STENCIL_OP_DECR_SAT:
		return GL_DECR;
	case VeRenderer::STENCIL_OP_INVERT:
		return GL_INVERT;
	case VeRenderer::STENCIL_OP_INCR:
		return GL_INCR_WRAP;
	case VeRenderer::STENCIL_OP_DECR:
		return GL_DECR_WRAP;
	default:
		return GL_KEEP;
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROBlendStateGLES2, VeROBlendState);
//--------------------------------------------------------------------------
VeROBlendStateGLES2::VeROBlendStateGLES2(const VeChar8* pcName)
	: VeROBlendState(pcName), m_bAlphaToCoverageEnable(false), m_bBlendEnable(false)
	, m_u16WriteMask(VeRenderer::COLOR_WRITE_ENABLE_ALL)
{

}
//--------------------------------------------------------------------------
VeROBlendStateGLES2::~VeROBlendStateGLES2()
{

}
//--------------------------------------------------------------------------
void VeROBlendStateGLES2::From(VeBinaryIStream& kIn)
{
	VeUInt16 u16AlphaToCoverage, u16NumRTDesc;
	kIn >> u16AlphaToCoverage;
	m_bAlphaToCoverageEnable = u16AlphaToCoverage ? true : false;
	kIn >> u16NumRTDesc;
	VE_ASSERT(u16NumRTDesc == 1);
	VeUInt8 u8Temp;
	kIn >> u8Temp;
	m_bBlendEnable = u8Temp ? true : false;
	kIn >> u8Temp;
	m_u16SrcBlend = GetGLBlend((VeRenderer::Blend)u8Temp, false);
	kIn >> u8Temp;
	m_u16DstBlend = GetGLBlend((VeRenderer::Blend)u8Temp, false);
	kIn >> u8Temp;
	m_u16BlendOp = GetGLBlendOp((VeRenderer::BlendOp)u8Temp);
	kIn >> u8Temp;
	m_u16SrcBlendAlpha = GetGLBlend((VeRenderer::Blend)u8Temp, true);
	kIn >> u8Temp;
	m_u16DstBlendAlpha = GetGLBlend((VeRenderer::Blend)u8Temp, true);
	kIn >> u8Temp;
	m_u16BlendOpAlpha = GetGLBlendOp((VeRenderer::BlendOp)u8Temp);
	kIn >> u8Temp;
	m_u16WriteMask = u8Temp;
}
//--------------------------------------------------------------------------
void VeROBlendStateGLES2::To(VeBinaryOStream& kOut) const
{
	kOut << VeUInt16(m_bAlphaToCoverageEnable ? 1 : 0);
	kOut << VeUInt16(1);
	kOut << VeUInt8(m_bBlendEnable ? 1 : 0);
	kOut << VeUInt8(GetBlend(m_u16SrcBlend));
	kOut << VeUInt8(GetBlend(m_u16DstBlend));
	kOut << VeUInt8(GetBlendOp(m_u16BlendOp));
	kOut << VeUInt8(GetBlend(m_u16SrcBlendAlpha));
	kOut << VeUInt8(GetBlend(m_u16DstBlendAlpha));
	kOut << VeUInt8(GetBlendOp(m_u16BlendOpAlpha));
	kOut << VeUInt8(m_u16WriteMask);
}
//--------------------------------------------------------------------------
void VeROBlendStateGLES2::From(VeXMLElement* pkElement)
{

}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODepthStencilStateGLES2, VeRODepthStencilState);
//--------------------------------------------------------------------------
VeRODepthStencilStateGLES2::VeRODepthStencilStateGLES2(const VeChar8* pcName)
	: VeRODepthStencilState(pcName), m_bDepthEnable(false), m_bStencilEnable(false)
{


}
//--------------------------------------------------------------------------
VeRODepthStencilStateGLES2::~VeRODepthStencilStateGLES2()
{

}
//--------------------------------------------------------------------------
void VeRODepthStencilStateGLES2::From(VeBinaryIStream& kIn)
{
	VeByte byTemp;
	kIn >> byTemp;
	m_bDepthEnable = byTemp ? true : false;
	kIn >> byTemp;
	m_bDepthWrite = byTemp ? true : false;
	kIn >> byTemp;
	m_u16DepthFunc = GetGLComparisonFunc((VeRenderer::ComparisonFunc)byTemp);
	kIn >> byTemp;
	m_bStencilEnable = byTemp ? true : false;
	if(m_bStencilEnable)
	{
		kIn >> m_u8StencilReadMask;
		kIn >> m_u8StencilWriteMask;
		kIn >> byTemp;
		m_u16FrontFailOp = GetGLStencilOp((VeRenderer::StencilOp)byTemp);
		kIn >> byTemp;
		m_u16FrontDepthFailOp = GetGLStencilOp((VeRenderer::StencilOp)byTemp);
		kIn >> byTemp;
		m_u16FrontPassOp = GetGLStencilOp((VeRenderer::StencilOp)byTemp);
		kIn >> byTemp;
		m_u16FrontFunc = GetGLComparisonFunc((VeRenderer::ComparisonFunc)byTemp);
		kIn >> byTemp;
		m_u16BackFailOp = GetGLStencilOp((VeRenderer::StencilOp)byTemp);
		kIn >> byTemp;
		m_u16BackDepthFailOp = GetGLStencilOp((VeRenderer::StencilOp)byTemp);
		kIn >> byTemp;
		m_u16BackPassOp = GetGLStencilOp((VeRenderer::StencilOp)byTemp);
		kIn >> byTemp;
		m_u16BackFunc = GetGLComparisonFunc((VeRenderer::ComparisonFunc)byTemp);
	}
	else
	{
		m_u8StencilReadMask = 0xff;
		m_u8StencilWriteMask = 0xff;
		m_u16FrontFailOp = GL_KEEP;
		m_u16FrontDepthFailOp = GL_KEEP;
		m_u16FrontPassOp = GL_KEEP;
		m_u16FrontFunc = GL_ALWAYS;
		m_u16BackFailOp = GL_KEEP;
		m_u16BackDepthFailOp = GL_KEEP;
		m_u16BackPassOp = GL_KEEP;
		m_u16BackFunc = GL_ALWAYS;
	}
}
//--------------------------------------------------------------------------
void VeRODepthStencilStateGLES2::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeRODepthStencilStateGLES2::From(VeXMLElement* pkElement)
{

}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROInputLayoutGLES2, VeROInputLayout);
//--------------------------------------------------------------------------
VeROInputLayoutGLES2::VeROInputLayoutGLES2(const VeChar8* pcName)
	: VeROInputLayout(pcName)
{

}
//--------------------------------------------------------------------------
VeROInputLayoutGLES2::~VeROInputLayoutGLES2()
{

}
//--------------------------------------------------------------------------
void VeROInputLayoutGLES2::From(VeBinaryIStream& kIn)
{
	VeString kLayoutName;
	kIn.GetStringAligned4(kLayoutName);
	VeUInt32 u32DescNum;
	kIn >> u32DescNum;
	m_kElementDescArray.Resize(u32DescNum);
	for(VeUInt32 i(0); i < m_kElementDescArray.Size(); ++i)
	{
		VeByte byTemp;
		kIn >> byTemp;
		m_kElementDescArray[i].m_eSemanticType = (VeRenderer::Semantic)byTemp;
		kIn >> byTemp;
		m_kElementDescArray[i].m_u32SemanticIndex = byTemp;
		kIn >> byTemp;
		m_kElementDescArray[i].SetFormat((VeRenderer::Format)byTemp);
		kIn >> byTemp;
		m_kElementDescArray[i].m_u16InputSlot = byTemp;
		kIn >> byTemp;
		m_kElementDescArray[i].m_u16AlignedByteOffset = byTemp;
		kIn >> byTemp;
		VE_ASSERT(!byTemp);
		VeUInt16 u16InstanceDataRate;
		kIn >> u16InstanceDataRate;
		VE_ASSERT(!u16InstanceDataRate);
	}
}
//--------------------------------------------------------------------------
void VeROInputLayoutGLES2::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeROInputLayoutGLES2::From(VeXMLElement* pkElement)
{

}
//--------------------------------------------------------------------------
void VeROInputLayoutGLES2::InputElementDesc::SetFormat(VeRenderer::Format eFormat)
{
	switch(eFormat)
	{
	case VeRenderer::FMT_R32_FLOAT:
		m_u16Type = GL_FLOAT;
		m_u8Size = 1;
		m_u8Normalized = GL_FALSE;
		break;
	case VeRenderer::FMT_R32G32_FLOAT:
		m_u16Type = GL_FLOAT;
		m_u8Size = 2;
		m_u8Normalized = GL_FALSE;
		break;
	case VeRenderer::FMT_R32G32B32_FLOAT:
		m_u16Type = GL_FLOAT;
		m_u8Size = 3;
		m_u8Normalized = GL_FALSE;
		break;
	case VeRenderer::FMT_R32G32B32A32_FLOAT:
		m_u16Type = GL_FLOAT;
		m_u8Size = 4;
		m_u8Normalized = GL_FALSE;
		break;
	case VeRenderer::FMT_R16_UINT:
		m_u16Type = GL_UNSIGNED_SHORT;
		m_u8Size = 1;
		m_u8Normalized = GL_FALSE;
		break;
	case VeRenderer::FMT_R16G16_UINT:
		m_u16Type = GL_UNSIGNED_SHORT;
		m_u8Size = 2;
		m_u8Normalized = GL_FALSE;
		break;
	case VeRenderer::FMT_R16G16B16A16_UINT:
		m_u16Type = GL_UNSIGNED_SHORT;
		m_u8Size = 4;
		m_u8Normalized = GL_FALSE;
		break;
	case VeRenderer::FMT_R8G8B8A8_UNORM:
		m_u16Type = GL_UNSIGNED_BYTE;
		m_u8Size = 4;
		m_u8Normalized = GL_TRUE;
		break;
	case VeRenderer::FMT_R8_UINT:
		m_u16Type = GL_UNSIGNED_BYTE;
		m_u8Size = 1;
		m_u8Normalized = GL_FALSE;
		break;
	default:
		VE_ASSERT(!"Wrong input type");
		break;
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRORasterizeStateGLES2, VeRORasterizeState);
//--------------------------------------------------------------------------
VeRORasterizeStateGLES2::VeRORasterizeStateGLES2(const VeChar8* pcName)
	: VeRORasterizeState(pcName)
{

}
//--------------------------------------------------------------------------
VeRORasterizeStateGLES2::~VeRORasterizeStateGLES2()
{

}
//--------------------------------------------------------------------------
void VeRORasterizeStateGLES2::From(VeBinaryIStream& kIn)
{
	VeUInt8 u8FillMode, u8CullMode, u8FrontCCW, u8DepthBiasMode, u8DepthClip, u8Scissor, u8Multisample, u8AntialiasedLine;
	kIn >> u8FillMode;
	kIn >> u8CullMode;
	kIn >> u8FrontCCW;
	kIn >> u8DepthBiasMode;
	kIn >> u8DepthClip;
	kIn >> u8Scissor;
	kIn >> u8Multisample;
	kIn >> u8AntialiasedLine;
	VE_ASSERT(u8FillMode == VeRenderer::FILL_SOLID && u8DepthClip);
	switch(u8CullMode)
	{
	case VeRenderer::CULL_FRONT:
		m_bCullEnable = true;
		m_u16CullFace = GL_FRONT;
		break;
	case VeRenderer::CULL_BACK:
		m_bCullEnable = true;
		m_u16CullFace = GL_BACK;
		break;
	default:
		m_bCullEnable = false;
		m_u16CullFace = GL_BACK;
		break;
	}
	m_u16FrontFace = u8FrontCCW ? GL_CCW : GL_CW;
	switch(u8DepthBiasMode)
	{
	case VeRenderer::DBIAS_NONE:
	default:
		m_bDepthBiasEnable = false;
		m_f32PolyFactor = 0;
		m_f32PolyUnits = 0;
		break;
	}
	m_bMultisampleEnable = u8Multisample ? true : false;
	m_bScissorEnable = u8Scissor ? true : false;
}
//--------------------------------------------------------------------------
void VeRORasterizeStateGLES2::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeRORasterizeStateGLES2::From(VeXMLElement* pkElement)
{

}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROSamplerStateGLES2, VeROSamplerState);
//--------------------------------------------------------------------------
VeROSamplerStateGLES2::VeROSamplerStateGLES2(const VeChar8* pcName)
	: VeROSamplerState(pcName), m_eFilter(VeRenderer::FILTER_MIN_MAG_MIP_POINT)
	, m_eAddressU(VeRenderer::TEXTURE_ADDRESS_CLAMP)
	, m_eAddressV(VeRenderer::TEXTURE_ADDRESS_CLAMP)
	, m_u32MaxAnisotropy(0)
{

}
//--------------------------------------------------------------------------
VeROSamplerStateGLES2::~VeROSamplerStateGLES2()
{

}
//--------------------------------------------------------------------------
void VeROSamplerStateGLES2::From(VeBinaryIStream& kIn)
{
	VeByte byTemp;
	kIn >> byTemp;
	VeRenderer::Filter eFilter = (VeRenderer::Filter)byTemp;
	kIn >> byTemp;
	VeRenderer::TextureAddressMode eAddressU = (VeRenderer::TextureAddressMode)byTemp;
	kIn >> byTemp;
	VeRenderer::TextureAddressMode eAddressV = (VeRenderer::TextureAddressMode)byTemp;
	kIn >> byTemp;
	VeUInt16 u16Temp;
	kIn >> u16Temp;
	VeUInt32 u32MaxAnisotropy = VE_MIN(u16Temp, ((VeRendererGLES2*)g_pRenderer)->GetMaxAnisotropy());
	kIn >> u16Temp;
	kIn.Skip(28);
	VE_ASSERT(eFilter <= VeRenderer::FILTER_ANISOTROPIC);
	VE_ASSERT(eAddressU <= VeRenderer::TEXTURE_ADDRESS_CLAMP && eAddressV <= VeRenderer::TEXTURE_ADDRESS_CLAMP);
	m_eFilter = eFilter;
	m_eAddressU = eAddressU;
	m_eAddressV = eAddressV;
	m_u32MaxAnisotropy = u32MaxAnisotropy;
}
//--------------------------------------------------------------------------
void VeROSamplerStateGLES2::To(VeBinaryOStream& kOut) const
{

}
//--------------------------------------------------------------------------
void VeROSamplerStateGLES2::From(VeXMLElement* pkElement)
{

}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROBufferGLES2, VeROBuffer);
//--------------------------------------------------------------------------
VeROBufferGLES2::VeROBufferGLES2(const VeChar8* pcName)
	: VeROBuffer(pcName), m_u32Target(0), m_u32Params(0)
	, m_u32ByteWidth(0), m_u32Buffer(0), m_pvBuffer(NULL)
	, m_pvMemoryBuffer(NULL)
{

}
//--------------------------------------------------------------------------
VeROBufferGLES2::~VeROBufferGLES2()
{
	Clear();
}
//--------------------------------------------------------------------------
void VeROBufferGLES2::From(VeBinaryIStream& kIn)
{
	VeUInt32 u32ByteWidth;
	kIn >> u32ByteWidth;
	VeUInt16 u16Temp;
	kIn >> u16Temp;
	kIn >> u16Temp;
	VeByte byTemp;
	kIn >> byTemp;
	VeRenderer::Usage eUsage = (VeRenderer::Usage)byTemp;
	kIn >> byTemp;
	VeRenderer::BindFlag eBindFlag = (VeRenderer::BindFlag)byTemp;
	kIn >> byTemp;
	kIn >> byTemp;
	VeUInt32 u32SysMemPitch;
	VeUInt32 u32SysMemSlicePitch;
	void* pvInitBuffer(NULL);
	if(byTemp)
	{
		VE_ASSERT(u32ByteWidth);
		kIn >> u32SysMemPitch;
		kIn >> u32SysMemSlicePitch;
		VE_ASSERT((u32ByteWidth & 3) == 0);
		pvInitBuffer = VeMalloc(u32ByteWidth);
		kIn.Read(pvInitBuffer, u32ByteWidth);
	}

	GLenum eTarget(0);
	switch(eBindFlag)
	{
	case VeRenderer::BIND_VERTEX_BUFFER:
		eTarget = GL_ARRAY_BUFFER;
		break;
	case VeRenderer::BIND_INDEX_BUFFER:
		eTarget = GL_ELEMENT_ARRAY_BUFFER;
		break;
	case VeRenderer::BIND_CONSTANT_BUFFER:
		eTarget = VeRenderer::BIND_CONSTANT_BUFFER;
		break;
	default:
		VE_ASSERT(!"Unknown target");
		break;
	}
	GLenum eParams(0);
	switch(eUsage)
	{
	case VeRenderer::USAGE_IMMUTABLE:
		eParams = GL_STATIC_DRAW;
		break;
	case VeRenderer::USAGE_DYNAMIC:
		eParams = GL_DYNAMIC_DRAW;
		break;
	case VeRenderer::USAGE_STAGING:
		eParams = GL_STREAM_DRAW;
		break;
	default:
		eParams = GL_STATIC_DRAW;
		break;
	}
	Update(eTarget, eParams, u32ByteWidth, pvInitBuffer);
	VE_ASSERT(glGetError() == GL_NO_ERROR);
}
//--------------------------------------------------------------------------
VeUInt32 VeROBufferGLES2::GetBindFlag()
{
	switch(m_u32Target)
	{
	case VeRenderer::BIND_CONSTANT_BUFFER:
		return VeRenderer::BIND_CONSTANT_BUFFER;
	case GL_ARRAY_BUFFER:
		return VeRenderer::BIND_VERTEX_BUFFER;
	case GL_ELEMENT_ARRAY_BUFFER:
		return VeRenderer::BIND_INDEX_BUFFER;
	default:
		return 0;
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeROBufferGLES2::GetCpuAccessFlag()
{
	return VeRenderer::CPU_ACCESS_WRITE & VeRenderer::CPU_ACCESS_READ;
}
//--------------------------------------------------------------------------
VeUInt32 VeROBufferGLES2::GetResourceMiscFlag()
{
	return 0;
}
//--------------------------------------------------------------------------
void VeROBufferGLES2::Update(VeUInt32 u32Target, VeUInt32 u32Params,
	VeUInt32 u32ByteWidth, void* pvInitBuffer)
{
	if(u32Target != m_u32Target || u32Params != m_u32Params || u32ByteWidth != m_u32ByteWidth)
	{
		Clear();
		VE_ASSERT((!m_u32Buffer) && (!m_pvBuffer));
		if(u32ByteWidth)
		{
			m_pvBuffer = pvInitBuffer ? pvInitBuffer : VeMalloc(u32ByteWidth);
		}
		VE_ASSERT(m_pvBuffer || u32ByteWidth == 0);
		if(m_pvBuffer && u32Target != VeRenderer::BIND_CONSTANT_BUFFER)
		{
			glGenBuffers(1, &m_u32Buffer);
			((VeRendererGLES2*)g_pRenderer)->BindBuffer(u32Target, m_u32Buffer);
			glBufferData(u32Target, u32ByteWidth, pvInitBuffer, u32Params);
		}
		m_u32Target = u32Target;
		m_u32Params = u32Params;
		m_u32ByteWidth = u32ByteWidth;
	}
	else if(pvInitBuffer)
	{
		VE_ASSERT(m_pvBuffer);
		VeFree(m_pvBuffer);
		m_pvBuffer = pvInitBuffer;
		if(u32Target != VeRenderer::BIND_CONSTANT_BUFFER)
		{
			((VeRendererGLES2*)g_pRenderer)->BindBuffer(u32Target, m_u32Buffer);
			glBufferSubData(u32Target, 0, u32ByteWidth, m_pvBuffer);
		}
	}
}
//--------------------------------------------------------------------------
void VeROBufferGLES2::Clear()
{
	if(m_u32Buffer)
	{
		glDeleteBuffers(1, &m_u32Buffer);
		m_u32Buffer = 0;
	}
	if(m_pvBuffer)
	{
		VeFree(m_pvBuffer);
		m_pvBuffer = NULL;
	}
	m_u32Target = 0;
	m_u32Params = 0;
	m_u32ByteWidth = 0;
	m_pvMemoryBuffer = NULL;
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeROBufferGLES2::OnLost()
{
	if(m_u32Buffer)
	{
		glDeleteBuffers(1, &m_u32Buffer);
		m_u32Buffer = 0;
	}
}
//--------------------------------------------------------------------------
void VeROBufferGLES2::OnRestore()
{
	if(m_u32Target != VeRenderer::BIND_CONSTANT_BUFFER)
	{
		glGenBuffers(1, &m_u32Buffer);
		((VeRendererGLES2*)g_pRenderer)->BindBuffer(m_u32Target, m_u32Buffer);
		glBufferData(m_u32Target, m_u32ByteWidth, m_pvBuffer, m_u32Params);
	}
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODepthStencilViewGLES2, VeRODepthStencilView);
//--------------------------------------------------------------------------
VeRODepthStencilViewGLES2::VeRODepthStencilViewGLES2(const VeChar8* pcName)
	: VeRODepthStencilView(pcName), m_u32Level(0)
{

}
//--------------------------------------------------------------------------
VeRODepthStencilViewGLES2::~VeRODepthStencilViewGLES2()
{

}
//--------------------------------------------------------------------------
void VeRODepthStencilViewGLES2::OnDel()
{
	m_spTexture = NULL;
}
//--------------------------------------------------------------------------
void VeRODepthStencilViewGLES2::OnClear()
{
	m_spTexture = NULL;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRORenderTargetViewGLES2, VeRORenderTargetView);
//--------------------------------------------------------------------------
VeRORenderTargetViewGLES2::VeRORenderTargetViewGLES2(const VeChar8* pcName)
	: VeRORenderTargetView(pcName), m_u32Level(0)
{

}
//--------------------------------------------------------------------------
VeRORenderTargetViewGLES2::~VeRORenderTargetViewGLES2()
{

}
//--------------------------------------------------------------------------
void VeRORenderTargetViewGLES2::OnDel()
{
	m_spTexture = NULL;
}
//--------------------------------------------------------------------------
void VeRORenderTargetViewGLES2::OnClear()
{
	m_spTexture = NULL;
}
//--------------------------------------------------------------------------
bool GetFilter(VeRenderer::Filter eFilter, VeUInt32 u32MipLevels,
	VeUInt32& u32MinFilter, VeUInt32& u32MagFilter)
{
	bool bAnisotropic(false);
	switch(eFilter)
	{
	case VeRenderer::FILTER_MIN_MAG_MIP_POINT:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_NEAREST_MIPMAP_NEAREST;
			u32MagFilter = GL_NEAREST_MIPMAP_NEAREST;
		}
		else
		{
			u32MinFilter = GL_NEAREST;
			u32MagFilter = GL_NEAREST;
		}
		break;
	case VeRenderer::FILTER_MIN_MAG_POINT_MIP_LINEAR:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_NEAREST_MIPMAP_LINEAR;
			u32MagFilter = GL_NEAREST_MIPMAP_LINEAR;
		}
		else
		{
			u32MinFilter = GL_NEAREST;
			u32MagFilter = GL_NEAREST;
		}
		break;
	case VeRenderer::FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_NEAREST_MIPMAP_NEAREST;
			u32MagFilter = GL_LINEAR_MIPMAP_NEAREST;
		}
		else
		{
			u32MinFilter = GL_NEAREST;
			u32MagFilter = GL_LINEAR;
		}
		break;
	case VeRenderer::FILTER_MIN_POINT_MAG_MIP_LINEAR:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_NEAREST_MIPMAP_LINEAR;
			u32MagFilter = GL_LINEAR_MIPMAP_LINEAR;
		}
		else
		{
			u32MinFilter = GL_NEAREST;
			u32MagFilter = GL_LINEAR;
		}
		break;
	case VeRenderer::FILTER_MIN_LINEAR_MAG_MIP_POINT:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_LINEAR_MIPMAP_NEAREST;
			u32MagFilter = GL_NEAREST_MIPMAP_NEAREST;
		}
		else
		{
			u32MinFilter = GL_LINEAR;
			u32MagFilter = GL_NEAREST;
		}
		break;
	case VeRenderer::FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_LINEAR_MIPMAP_LINEAR;
			u32MagFilter = GL_NEAREST_MIPMAP_LINEAR;
		}
		else
		{
			u32MinFilter = GL_LINEAR;
			u32MagFilter = GL_NEAREST;
		}
		break;
	case VeRenderer::FILTER_MIN_MAG_LINEAR_MIP_POINT:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_LINEAR_MIPMAP_NEAREST;
			u32MagFilter = GL_LINEAR_MIPMAP_NEAREST;
		}
		else
		{
			u32MinFilter = GL_LINEAR;
			u32MagFilter = GL_LINEAR;
		}
		break;
	case VeRenderer::FILTER_MIN_MAG_MIP_LINEAR:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_LINEAR_MIPMAP_LINEAR;
			u32MagFilter = GL_LINEAR_MIPMAP_LINEAR;
		}
		else
		{
			u32MinFilter = GL_LINEAR;
			u32MagFilter = GL_LINEAR;
		}
		break;
	case VeRenderer::FILTER_ANISOTROPIC:
		if(u32MipLevels > 1)
		{
			u32MinFilter = GL_LINEAR_MIPMAP_LINEAR;
			u32MagFilter = GL_LINEAR_MIPMAP_LINEAR;
		}
		else
		{
			u32MinFilter = GL_LINEAR;
			u32MagFilter = GL_LINEAR;
		}
		bAnisotropic = true;
		break;
	default:
		VE_ASSERT(!"Wrong filter");
		break;
	}
	return bAnisotropic;
}
//--------------------------------------------------------------------------
VeUInt32 GetTexAddress(VeRenderer::TextureAddressMode eMode)
{
	switch(eMode)
	{
	case VeRenderer::TEXTURE_ADDRESS_WRAP:
		return GL_REPEAT;
	case VeRenderer::TEXTURE_ADDRESS_MIRROR:
		return GL_MIRRORED_REPEAT;
	case VeRenderer::TEXTURE_ADDRESS_CLAMP:
		return GL_CLAMP_TO_EDGE;
	default:
		VE_ASSERT(!"Wrong tex address");
		return 0;
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROShaderResourceViewGLES2, VeROShaderResourceView);
//--------------------------------------------------------------------------
VeROShaderResourceViewGLES2::VeROShaderResourceViewGLES2(const VeChar8* pcName)
	: VeROShaderResourceView(pcName)
{
	m_u32MinFilter = GL_NEAREST;
	m_u32MagFilter = GL_NEAREST;
	m_u32WrapS = GL_CLAMP_TO_EDGE;
	m_u32WrapT = GL_CLAMP_TO_EDGE;
	m_u32MaxAnisotropy = 1;
}
//--------------------------------------------------------------------------
VeROShaderResourceViewGLES2::~VeROShaderResourceViewGLES2()
{

}
//--------------------------------------------------------------------------
void VeROShaderResourceViewGLES2::OnDel()
{
	m_spTexture = NULL;
	m_spSampler = NULL;
}
//--------------------------------------------------------------------------
void VeROShaderResourceViewGLES2::OnClear()
{
	m_spTexture = NULL;
	m_spSampler = NULL;
}
//--------------------------------------------------------------------------
void VeROShaderResourceViewGLES2::SetSampler(VeROSamplerStateGLES2* pkSampler)
{
	if(pkSampler != m_spSampler)
	{
		VeUInt32 u32MinFilter(m_u32MinFilter);
		VeUInt32 u32MagFilter(m_u32MagFilter);
		bool bAni = GetFilter(pkSampler->m_eFilter, m_spTexture->m_u32MipLevels, u32MinFilter, u32MagFilter);
		VeUInt32 u32MaxAnisotropy = bAni ? pkSampler->m_u32MaxAnisotropy : 1;
		VeUInt32 u32WrapS = GetTexAddress(pkSampler->m_eAddressU);
		VeUInt32 u32WrapT = GetTexAddress(pkSampler->m_eAddressV);
		if(m_u32MinFilter != u32MinFilter)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, u32MinFilter);
			m_u32MinFilter = u32MinFilter;
		}
		if(m_u32MagFilter != u32MagFilter)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, u32MagFilter);
			m_u32MagFilter = u32MagFilter;
		}
		if(m_u32WrapS != u32WrapS)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, u32WrapS);
			m_u32WrapS = u32WrapS;
		}
		if(m_u32WrapT != u32WrapT)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, u32WrapT);
			m_u32WrapT = u32WrapT;
		}
		if(m_u32MaxAnisotropy != u32MaxAnisotropy)
		{
			VE_ASSERT(u32MaxAnisotropy <= ((VeRendererGLES2*)g_pRenderer)->GetMaxAnisotropy());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, u32MaxAnisotropy);
			m_u32MaxAnisotropy =  u32MaxAnisotropy;
		}
		m_spSampler = pkSampler;
	}
}
//--------------------------------------------------------------------------
struct VeTexInit
{
	VeUInt32 m_u32SysMemPitch;
	VeUInt32 m_u32SysMemSlicePitch;
	void* m_pvSysMem;
};
//--------------------------------------------------------------------------
bool CheckFormat(VeRenderer::Format eFormat, GLenum& eTexFormat, GLenum& eTexInternalFormat, GLenum& eTexType, GLenum& eRBOType, VeUInt32& u32BitPerPixel, bool& bIsCompressed)
{
	switch(eFormat)
	{
	case VeRenderer::FMT_R8G8B8A8_UNORM:
		eTexFormat = eTexInternalFormat = GL_RGBA;
		eTexType = GL_UNSIGNED_BYTE;
		eRBOType = GL_RGBA8_OES;
		u32BitPerPixel = 32;
		bIsCompressed = false;
		return true;
	case VeRenderer::FMT_D24_UNORM_S8_UINT:
		eTexFormat = eTexInternalFormat = GL_DEPTH_STENCIL_OES;
		eTexType = GL_UNSIGNED_INT_24_8_OES;
		eRBOType = GL_DEPTH24_STENCIL8_OES;
		u32BitPerPixel = 32;
		bIsCompressed = false;
		return true;
    case VeRenderer::FMT_R8_UNORM:
        eTexFormat = eTexInternalFormat = GL_LUMINANCE;
        eTexType = GL_UNSIGNED_BYTE;
        eRBOType = 0;
        u32BitPerPixel = 8;
        bIsCompressed = false;
        return true;
	default:
		return false;
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROTexture2DGLES2, VeROTexture2D);
//--------------------------------------------------------------------------
VeROTexture2DGLES2::VeROTexture2DGLES2(const VeChar8* pcName)
	: VeROTexture2D(pcName), m_u32Target(0), m_u32Texture(0)
	, m_u32Width(0), m_u32Height(0), m_u32MipLevels(1)
	, m_eFormat(VeRenderer::FMT_UNKNOWN)
{

}
//--------------------------------------------------------------------------
VeROTexture2DGLES2::~VeROTexture2DGLES2()
{
	if(m_u32Texture)
	{
		if(m_u32Target == GL_TEXTURE_2D)
		{
			glDeleteTextures(1, &m_u32Texture);
		}
		else if(m_u32Target == GL_RENDERBUFFER)
		{
			glDeleteRenderbuffers(1, &m_u32Texture);
		}
		else
		{
			VE_ASSERT(!"Unknown texture type");
		}
		m_u32Texture = 0;
	}
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::OnDel()
{
	if(m_spSRV)
	{
		((VeRendererGLES2*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spSRV));
		m_spSRV = NULL;
	}
	if(m_spRTV)
	{
		((VeRendererGLES2*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spRTV));
		m_spRTV = NULL;
	}
	if(m_spDSV)
	{
		((VeRendererGLES2*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spDSV));
		m_spDSV = NULL;
	}
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::OnClear()
{
	m_spSRV = NULL;
	m_spRTV = NULL;
	m_spDSV = NULL;
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::UpdateData(VeUInt32 u32Mip, VeUInt32 u32Array,
	void* pvData)
{
	VE_ASSERT(u32Mip < m_u32MipLevels && (!u32Array) && m_u32Target == GL_TEXTURE_2D && m_u32Texture);
	GLenum eTexFormat, eTexInternalFormat, eTexType, eRBOType;
	VeUInt32 u32BitPerPixel;
	bool bIsCompressed;
	VE_ASSERT_EQ(CheckFormat(m_eFormat, eTexFormat, eTexInternalFormat, eTexType, eRBOType, u32BitPerPixel, bIsCompressed), true);
	((VeRendererGLES2*)g_pRenderer)->SetPSTexture(0, m_u32Texture);
	if(bIsCompressed)
	{
		VE_ASSERT(!bIsCompressed);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, u32Mip, eTexInternalFormat, m_u32Width, m_u32Height, 0, eTexFormat, eTexType, pvData);
	}
	VE_ASSERT(glGetError() == GL_NO_ERROR);
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::CopyRect(VeUInt32 u32Mip, VeUInt32 x, VeUInt32 y,
	VeUInt32 w, VeUInt32 h, VeUInt32 u32Format, void* pvData)
{
	VE_ASSERT(u32Mip < m_u32MipLevels && m_u32Target == GL_TEXTURE_2D && m_u32Texture);
	GLenum eTexFormat, eTexInternalFormat, eTexType, eRBOType;
	VeUInt32 u32BitPerPixel;
	bool bIsCompressed;
	VE_ASSERT_EQ(CheckFormat(m_eFormat, eTexFormat, eTexInternalFormat, eTexType, eRBOType, u32BitPerPixel, bIsCompressed), true);
	((VeRendererGLES2*)g_pRenderer)->SetPSTexture(0, m_u32Texture);
	glTexSubImage2D(GL_TEXTURE_2D, u32Mip, x, y, w, h, eTexFormat, eTexType, pvData);
	VE_ASSERT(glGetError() == GL_NO_ERROR);
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::From(VeBinaryIStream& kIn)
{
	VeUInt16 u16Width, u16Height, u16MipLevels, u16ArraySize;
	kIn >> u16Width;
	kIn >> u16Height;
	kIn >> u16MipLevels;
	kIn >> u16ArraySize;
	VeByte byTemp;
	kIn >> byTemp;
	m_eFormat = (VeRenderer::Format)byTemp;
	VeUInt8 u8Conut, u8Quality;
	kIn >> u8Conut;
	kIn >> u8Quality;
	kIn >> byTemp;
	VeUInt8 u8BindFlags;
	kIn >> u8BindFlags;
	kIn >> byTemp;
	VeUInt16 u16Temp;
	kIn >> u16Temp;
	bool bCreateViews;
	kIn >> u16Temp;
	bCreateViews = u16Temp ? true : false;
	kIn >> u16Temp;
	VeVector<VeTexInit> kInitData;
	kInitData.Resize(u16Temp);
	for(VeUInt16 i(0); i < u16Temp; ++i)
	{
		kIn >> kInitData[i].m_u32SysMemPitch;
		kIn >> kInitData[i].m_u32SysMemSlicePitch;
		VeUInt32 u32ByteWidth;
		kIn >> u32ByteWidth;
		VE_ASSERT((u32ByteWidth & 3) == 0);
		kInitData[i].m_pvSysMem = kIn.Skip(u32ByteWidth);
	}
	VE_ASSERT(u16ArraySize == 1);
	bool bSRV = VE_MASK_HAS_ANY(u8BindFlags, VeRenderer::BIND_SHADER_RESOURCE);
	bool bRTV = VE_MASK_HAS_ANY(u8BindFlags, VeRenderer::BIND_RENDER_TARGET);
	bool bDSV = VE_MASK_HAS_ANY(u8BindFlags, VeRenderer::BIND_DEPTH_STENCIL);
	VE_ASSERT(u8Conut == 1 || (u8Conut == ((VeRendererGLES2*)g_pRenderer)->m_u8MaxAASamples && bSRV));
	VE_ASSERT(bSRV || kInitData.Empty());
	VE_ASSERT(!(bRTV && bDSV));
	if((!(((VeRendererGLES2*)g_pRenderer)->m_bSupportDepthTexute)) && bDSV && bSRV)
	{
		bSRV = false;
	}
	VE_ASSERT((!bDSV) || (m_eFormat != VeRenderer::FMT_D24_UNORM_S8_UINT));
	GLenum eTexFormat, eTexInternalFormat, eTexType, eRBOType;
	VeUInt32 u32BitPerPixel;
	bool bIsCompressed;
	VE_ASSERT_EQ(CheckFormat(m_eFormat, eTexFormat, eTexInternalFormat, eTexType, eRBOType, u32BitPerPixel, bIsCompressed), true);
	m_u32Width = u16Width;
	m_u32Height = u16Height;
	m_u32MipLevels = u16MipLevels;
	if(bSRV)
	{
		VeUInt32 u32LastState = ((VeRendererGLES2*)g_pRenderer)->m_au32PSTexture[0];
		Update(GL_TEXTURE_2D);
		((VeRendererGLES2*)g_pRenderer)->SetPSTexture(0, m_u32Texture);
		VeUInt32 u32SizeX = u16Width, u32SizeY = u16Height;
		if(bIsCompressed)
		{
			VE_ASSERT(!bIsCompressed);
		}
		else
		{
			if(u16MipLevels)
			{
				for(VeUInt32 i(0); i < u16MipLevels; u32SizeX = VE_MAX(u32SizeX >> 1, 1), u32SizeY = VE_MAX(u32SizeY >> 1, 1), ++i)
				{
					void* pvData = NULL;
					if(kInitData.Size() > i) pvData = kInitData[i].m_pvSysMem;
					glTexImage2D(GL_TEXTURE_2D, i, eTexInternalFormat, u32SizeX, u32SizeY, 0, eTexFormat, eTexType, pvData);
					VE_ASSERT(glGetError() == GL_NO_ERROR);
				}
			}
			else
			{
				for(VeUInt32 i(0); (u32SizeX > 1 || u32SizeY > 1); u32SizeX = VE_MAX(u32SizeX >> 1, 1), u32SizeY = VE_MAX(u32SizeY >> 1, 1), ++i)
				{
					void* pvData = NULL;
					if(kInitData.Size() > i) pvData = kInitData[i].m_pvSysMem;
					glTexImage2D(GL_TEXTURE_2D, i, eTexInternalFormat, u32SizeX, u32SizeY, 0, eTexFormat, eTexType, pvData);
					VE_ASSERT(glGetError() == GL_NO_ERROR);
				}
			}
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		if(((VeRendererGLES2*)g_pRenderer)->m_bSupportAnisotropic)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
			if(glGetError() != GL_NO_ERROR)
			{
				((VeRendererGLES2*)g_pRenderer)->m_bSupportAnisotropic = false;
			}
		}
		((VeRendererGLES2*)g_pRenderer)->SetPSTexture(0, u32LastState);
		VE_ASSERT(glGetError() == GL_NO_ERROR);
	}
	else
	{
		Update(GL_RENDERBUFFER);
		VeUInt32 u32LastState = ((VeRendererGLES2*)g_pRenderer)->m_u32BindRenderBuffer;
		((VeRendererGLES2*)g_pRenderer)->BindRenderBuffer(m_u32Texture);
		if(u8Conut == 1)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, eRBOType, u16Width, u16Height);
		}
		else
		{
#			if defined(VE_PLATFORM_IOS)
			glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, u8Conut, eRBOType, u16Width, u16Height);
#			endif
		}
		((VeRendererGLES2*)g_pRenderer)->BindRenderBuffer(u32LastState);
		VE_ASSERT(glGetError() == GL_NO_ERROR);
	}
	if(bCreateViews)
	{
		if(bSRV)
		{
			g_pRenderer->GetRenderObject(GetName(), m_spSRV);
			if(!m_spSRV)
			{
				m_spSRV = VE_NEW VeROShaderResourceViewGLES2(GetName());
				((VeRendererGLES2*)g_pRenderer)->AddObject(m_spSRV);
			}
			m_spSRV->m_spTexture = this;
			m_spSRV->m_spSampler = NULL;
			m_spSRV->m_u32MinFilter = GL_NEAREST;
			m_spSRV->m_u32MagFilter = GL_NEAREST;
			m_spSRV->m_u32WrapS = GL_CLAMP_TO_EDGE;
			m_spSRV->m_u32WrapT = GL_CLAMP_TO_EDGE;
			m_spSRV->m_u32MaxAnisotropy = 1;
		}
		if(bRTV)
		{
			g_pRenderer->GetRenderObject(GetName(), m_spRTV);
			if(!m_spRTV)
			{
				m_spRTV = VE_NEW VeRORenderTargetViewGLES2(GetName());
				((VeRendererGLES2*)g_pRenderer)->AddObject(m_spRTV);
			}
			m_spRTV->m_spTexture = this;
			m_spRTV->m_u32Level = 0;
		}
		if(bDSV)
		{
			g_pRenderer->GetRenderObject(GetName(), m_spDSV);
			if(!m_spDSV)
			{
				m_spDSV = VE_NEW VeRODepthStencilViewGLES2(GetName());
				((VeRendererGLES2*)g_pRenderer)->AddObject(m_spDSV);
			}
			m_spDSV->m_spTexture = this;
			m_spDSV->m_u32Level = 0;
		}
	}
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::Update(VeUInt32 u32Target)
{
	if(u32Target != m_u32Target)
	{
		Clear();
		if(u32Target == GL_TEXTURE_2D)
		{
			glGenTextures(1, &m_u32Texture);
		}
		else if(u32Target == GL_RENDERBUFFER)
		{
			glGenRenderbuffers(1, &m_u32Texture);
		}
		else
		{
			u32Target = 0;
		}
		m_u32Target = u32Target;
	}
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::Clear()
{
	if(m_u32Texture)
	{
		if(m_u32Target == GL_TEXTURE_2D)
		{
			glDeleteTextures(1, &m_u32Texture);
		}
		else if(m_u32Target == GL_RENDERBUFFER)
		{
			glDeleteRenderbuffers(1, &m_u32Texture);
		}
		else
		{
			VE_ASSERT(!"Unknown texture type");
		}
		m_u32Texture = 0;
	}
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::OnLost()
{
	if(m_u32Target == GL_TEXTURE_2D)
	{
		VE_ASSERT(m_u32Texture);
		glDeleteTextures(1, &m_u32Texture);
	}
	else if(m_u32Target == GL_RENDERBUFFER)
	{
		VE_ASSERT(m_u32Texture);
		glDeleteRenderbuffers(1, &m_u32Texture);
	}
}
//--------------------------------------------------------------------------
void VeROTexture2DGLES2::OnRestore()
{
	if(m_u32Target == GL_TEXTURE_2D)
	{
		glGenTextures(1, &m_u32Texture);
	}
	else if(m_u32Target == GL_RENDERBUFFER)
	{
		glGenRenderbuffers(1, &m_u32Texture);
	}
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeImplementRTTI(VeROPixelShaderGLES2, VeROPixelShader);
//--------------------------------------------------------------------------
VeROPixelShaderGLES2::VeROPixelShaderGLES2(const VeChar8* pcName)
	: VeROPixelShader(pcName)
{
	m_u32Shader = glCreateShader(GL_FRAGMENT_SHADER);
}
//--------------------------------------------------------------------------
VeROPixelShaderGLES2::~VeROPixelShaderGLES2()
{
	if(m_u32Shader)
	{
		glDeleteShader(m_u32Shader);
		m_u32Shader = 0;
	}
}
//--------------------------------------------------------------------------
void VeROPixelShaderGLES2::From(VeBinaryIStream& kIn)
{
	GLint iLen = kIn.RemainingLength();
	const GLchar* pcShader = (const VeChar8*)kIn.Skip(iLen);
	kIn.Finish();
	glShaderSource(m_u32Shader, 1, &pcShader, &iLen);
	glCompileShader(m_u32Shader);
#	ifdef VE_DEBUG
	GLint iShaderCompiled(0);
	glGetShaderiv(m_u32Shader, GL_COMPILE_STATUS, &iShaderCompiled);
	VE_ASSERT(iShaderCompiled);
#	endif
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeROPixelShaderGLES2::OnLost()
{
	VE_ASSERT(m_u32Shader);
	glDeleteShader(m_u32Shader);
	m_u32Shader = 0;
}
//--------------------------------------------------------------------------
void VeROPixelShaderGLES2::OnRestore()
{
	m_u32Shader = glCreateShader(GL_FRAGMENT_SHADER);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
VeImplementRTTI(VeROVertexShaderGLES2, VeROVertexShader);
//--------------------------------------------------------------------------
VeROVertexShaderGLES2::VeROVertexShaderGLES2(const VeChar8* pcName)
	: VeROVertexShader(pcName)
{
	m_u32Shader = glCreateShader(GL_VERTEX_SHADER);
}
//--------------------------------------------------------------------------
VeROVertexShaderGLES2::~VeROVertexShaderGLES2()
{
	if(m_u32Shader)
	{
		glDeleteShader(m_u32Shader);
		m_u32Shader = 0;
	}
}
//--------------------------------------------------------------------------
void VeROVertexShaderGLES2::From(VeBinaryIStream& kIn)
{
	GLint iLen = kIn.RemainingLength();
	const GLchar* pcShader = (const VeChar8*)kIn.Skip(iLen);
	kIn.Finish();
	glShaderSource(m_u32Shader, 1, &pcShader, &iLen);
	glCompileShader(m_u32Shader);
#	ifdef VE_DEBUG
	GLint iShaderCompiled(0);
	glGetShaderiv(m_u32Shader, GL_COMPILE_STATUS, &iShaderCompiled);
	VE_ASSERT(iShaderCompiled);
#	endif
}
//--------------------------------------------------------------------------
#ifdef VE_ENABLE_DEVICE_LOST
//--------------------------------------------------------------------------
void VeROVertexShaderGLES2::OnLost()
{
	VE_ASSERT(m_u32Shader);
	glDeleteShader(m_u32Shader);
	m_u32Shader = 0;
}
//--------------------------------------------------------------------------
void VeROVertexShaderGLES2::OnRestore()
{
	m_u32Shader = glCreateShader(GL_VERTEX_SHADER);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#ifdef VE_PLATFORM_IOS
//--------------------------------------------------------------------------
VeMSAAResolveGLES2APPLE::VeMSAAResolveGLES2APPLE(const VeChar8* pcName)
	: VeRenderProcess(TYPE_MSAA_RESOLVE, pcName)
{

}
//--------------------------------------------------------------------------
VeMSAAResolveGLES2APPLE::~VeMSAAResolveGLES2APPLE()
{

}
//--------------------------------------------------------------------------
bool VeMSAAResolveGLES2APPLE::Update(VeBinaryIStream& kStream)
{
    VeUInt16 u16RenderTargetNum, u16DepthStencilTargetNum;
    kStream >> u16RenderTargetNum;
    kStream >> u16DepthStencilTargetNum;
    if(u16RenderTargetNum == 1)
    {
        if(u16DepthStencilTargetNum)
        {
            VeRORenderTargetViewPtr spColor;
            VeRODepthStencilViewPtr spDepth;
            VeRORenderTargetViewPtr spColorAA;
            VeRODepthStencilViewPtr spDepthAA;
            VeString kName;
            kStream.GetStringAligned4(kName);
            g_pRenderer->GetRenderObject(kName, spColor);
            VE_ASSERT(spColor);
            kStream.GetStringAligned4(kName);
            g_pRenderer->GetRenderObject(kName, spColorAA);
            VE_ASSERT(spColorAA);
			kStream.GetStringAligned4(kName);
			g_pRenderer->GetRenderObject(kName, spDepth);
            kStream.GetStringAligned4(kName);
            g_pRenderer->GetRenderObject(kName, spDepthAA);
            m_u32DrawBuffer = ((VeRendererGLES2*)g_pRenderer)->GetFrameBuffer(VeSmartPointerCast(VeRORenderTargetViewGLES2, spColor), VeSmartPointerCast(VeRODepthStencilViewGLES2, spDepth));
            m_u32ReadBuffer = ((VeRendererGLES2*)g_pRenderer)->GetFrameBuffer(VeSmartPointerCast(VeRORenderTargetViewGLES2, spColorAA), VeSmartPointerCast(VeRODepthStencilViewGLES2, spDepthAA));
            
        }
        else
        {
            VeRORenderTargetViewPtr spColor;
            VeRORenderTargetViewPtr spColorAA;
            VeString kName;
            kStream.GetStringAligned4(kName);
            g_pRenderer->GetRenderObject(kName, spColor);
            VE_ASSERT(spColor);
            kStream.GetStringAligned4(kName);
            g_pRenderer->GetRenderObject(kName, spColorAA);
            VE_ASSERT(spColorAA);
            m_u32DrawBuffer = ((VeRendererGLES2*)g_pRenderer)->GetFrameBuffer(VeSmartPointerCast(VeRORenderTargetViewGLES2, spColor), NULL);
            m_u32ReadBuffer = ((VeRendererGLES2*)g_pRenderer)->GetFrameBuffer(VeSmartPointerCast(VeRORenderTargetViewGLES2, spColorAA), NULL);
        }
        return true;
    }
    else
    {
        VeString kTemp;
        for(VeUInt32 i(0); i < VeUInt32((u16RenderTargetNum + u16DepthStencilTargetNum) * 2); ++i)
        {
            kStream.GetStringAligned4(kTemp);
        }
        return false;
    }
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
