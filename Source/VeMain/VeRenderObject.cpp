////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderObject.cpp
//  Version:     v1.00
//  Created:     30/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeRenderObject.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeRenderObject, VeObject);
//--------------------------------------------------------------------------
VeRenderObject::VeRenderObject(Type eType, const VeChar8* pcName)
	: m_eType(eType), m_kName(pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::~VeRenderObject()
{

}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROBlendState, VeRenderObject);
//--------------------------------------------------------------------------
VeROBlendState::VeROBlendState(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROBlendState::ROType()
{
	return TYPE_BLEND_STATE;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODepthStencilState, VeRenderObject);
//--------------------------------------------------------------------------
VeRODepthStencilState::VeRODepthStencilState(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeRODepthStencilState::ROType()
{
	return TYPE_DEPTH_STENCIL_STATE;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROInputLayout, VeRenderObject);
//--------------------------------------------------------------------------
VeROInputLayout::VeROInputLayout(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROInputLayout::ROType()
{
	return TYPE_INPUT_LAYOUT;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRORasterizeState, VeRenderObject);
//--------------------------------------------------------------------------
VeRORasterizeState::VeRORasterizeState(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeRORasterizeState::ROType()
{
	return TYPE_RASTERIZER_STATE;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROSamplerState, VeRenderObject);
//--------------------------------------------------------------------------
VeROSamplerState::VeROSamplerState(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROSamplerState::ROType()
{
	return TYPE_SAMPLER_STATE;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROBuffer, VeRenderObject);
//--------------------------------------------------------------------------
VeROBuffer::VeROBuffer(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROBuffer::ROType()
{
	return TYPE_BUFFER;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODepthStencilView, VeRenderObject);
//--------------------------------------------------------------------------
VeRODepthStencilView::VeRODepthStencilView(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeRODepthStencilView::ROType()
{
	return TYPE_DEPTH_STENCIL_VIEW;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRORenderTargetView, VeRenderObject);
//--------------------------------------------------------------------------
VeRORenderTargetView::VeRORenderTargetView(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeRORenderTargetView::ROType()
{
	return TYPE_RENDER_TARGET_VIEW;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROShaderResourceView, VeRenderObject);
//--------------------------------------------------------------------------
VeROShaderResourceView::VeROShaderResourceView(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROShaderResourceView::ROType()
{
	return TYPE_SHADER_RESOURCE_VIEW;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROTexture1D, VeRenderObject);
//--------------------------------------------------------------------------
VeROTexture1D::VeROTexture1D(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROTexture1D::ROType()
{
	return TYPE_TEXTURE_1D;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROTexture2D, VeRenderObject);
//--------------------------------------------------------------------------
VeROTexture2D::VeROTexture2D(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROTexture2D::ROType()
{
	return TYPE_TEXTURE_2D;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROTexture3D, VeRenderObject);
//--------------------------------------------------------------------------
VeROTexture3D::VeROTexture3D(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROTexture3D::ROType()
{
	return TYPE_TEXTURE_3D;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROComputeShader, VeRenderObject);
//--------------------------------------------------------------------------
VeROComputeShader::VeROComputeShader(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROComputeShader::ROType()
{
	return TYPE_COMPUTE_SHADER;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODomainShader, VeRenderObject);
//--------------------------------------------------------------------------
VeRODomainShader::VeRODomainShader(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeRODomainShader::ROType()
{
	return TYPE_DOMAIN_SHADER;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROGeometryShader, VeRenderObject);
//--------------------------------------------------------------------------
VeROGeometryShader::VeROGeometryShader(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROGeometryShader::ROType()
{
	return TYPE_GEOMETRY_SHADER;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROHullShader, VeRenderObject);
//--------------------------------------------------------------------------
VeROHullShader::VeROHullShader(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROHullShader::ROType()
{
	return TYPE_HULL_SHADER;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROPixelShader, VeRenderObject);
//--------------------------------------------------------------------------
VeROPixelShader::VeROPixelShader(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROPixelShader::ROType()
{
	return TYPE_PIXEL_SHADER;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROVertexShader, VeRenderObject);
//--------------------------------------------------------------------------
VeROVertexShader::VeROVertexShader(const VeChar8* pcName)
	: VeRenderObject(ROType(), pcName)
{

}
//--------------------------------------------------------------------------
VeRenderObject::Type VeROVertexShader::ROType()
{
	return TYPE_VERTEX_SHADER;
}
//--------------------------------------------------------------------------
