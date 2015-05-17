////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRenderObjectD3D11.cpp
//  Version:     v1.00
//  Created:     31/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeRendererD3D11.h"

//--------------------------------------------------------------------------
#ifdef VE_ENABLE_D3D11
//--------------------------------------------------------------------------
DXGI_FORMAT GetGeneralTextureFormat(DXGI_FORMAT eFormat)
{
	switch(eFormat)
	{
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		return DXGI_FORMAT_R24G8_TYPELESS;
	default:
		break;
	}
	return eFormat;
}
//--------------------------------------------------------------------------
DXGI_FORMAT GetGeneralSRVFormat(DXGI_FORMAT eFormat)
{
	switch(eFormat)
	{
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	default:
		break;
	}
	return eFormat;
}
//--------------------------------------------------------------------------
DXGI_FORMAT GetGeneralRTVFormat(DXGI_FORMAT eFormat)
{
	switch(eFormat)
	{
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	default:
		break;
	}
	return eFormat;
}
//--------------------------------------------------------------------------
DXGI_FORMAT GetGeneralDSVFormat(DXGI_FORMAT eFormat)
{
	switch(eFormat)
	{
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		return DXGI_FORMAT_D24_UNORM_S8_UINT;
	default:
		break;
	}
	return eFormat;
}
//--------------------------------------------------------------------------
bool CheckFormat(VeRenderer::Format eFormat, VeUInt32& u32PixelPerUnit,
	VeUInt32& u32BytePerUnit)
{
	switch(eFormat)
	{
	case VeRenderer::FMT_R8G8B8A8_UNORM:
		u32PixelPerUnit = 1;
		u32BytePerUnit = 4;
		return true;
	case VeRenderer::FMT_D24_UNORM_S8_UINT:
		u32PixelPerUnit = 1;
		u32BytePerUnit = 4;
		return true;
	case VeRenderer::FMT_R8_UNORM:
		u32PixelPerUnit = 1;
		u32BytePerUnit = 1;
		return true;
	default:
		return false;
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROBlendStateD3D11, VeROBlendState);
//--------------------------------------------------------------------------
VeROBlendStateD3D11::VeROBlendStateD3D11(const VeChar8* pcName)
	: VeROBlendState(pcName), m_pkBlendState(NULL)
{

}
//--------------------------------------------------------------------------
VeROBlendStateD3D11::~VeROBlendStateD3D11()
{
	VE_SAFE_RELEASE(m_pkBlendState);
}
//--------------------------------------------------------------------------
void VeROBlendStateD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkBlendState);
	D3D11_BLEND_DESC kDesc;
	VeUInt16 u16Temp;
	kIn >> u16Temp;
	kDesc.AlphaToCoverageEnable = u16Temp;
	kIn >> u16Temp;
	VeUInt32 u32NumRTDesc = u16Temp;
	kDesc.IndependentBlendEnable = u32NumRTDesc > 1 ? TRUE : FALSE;
	for(VeUInt32 i(0); i < u32NumRTDesc; ++i)
	{
		D3D11_RENDER_TARGET_BLEND_DESC& kRTDesc = kDesc.RenderTarget[i];
		VeUInt8 u8Temp;
		kIn >> u8Temp;
		kRTDesc.BlendEnable = u8Temp;
		kIn >> u8Temp;
		kRTDesc.SrcBlend = (D3D11_BLEND)u8Temp;
		kIn >> u8Temp;
		kRTDesc.DestBlend = (D3D11_BLEND)u8Temp;
		kIn >> u8Temp;
		kRTDesc.BlendOp = (D3D11_BLEND_OP)u8Temp;
		kIn >> u8Temp;
		kRTDesc.SrcBlendAlpha = (D3D11_BLEND)u8Temp;
		kIn >> u8Temp;
		kRTDesc.DestBlendAlpha = (D3D11_BLEND)u8Temp;
		kIn >> u8Temp;
		kRTDesc.BlendOpAlpha = (D3D11_BLEND_OP)u8Temp;
		kIn >> u8Temp;
		kRTDesc.RenderTargetWriteMask = u8Temp;
	}
	for(VeUInt32 i(u32NumRTDesc); i < 8; ++i)
	{
		D3D11_RENDER_TARGET_BLEND_DESC& kRTDesc = kDesc.RenderTarget[i];
		VeZeroMemory(&kRTDesc, sizeof(kRTDesc));
	}
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateBlendState(&kDesc, &m_pkBlendState), S_OK);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODepthStencilStateD3D11, VeRODepthStencilState);
//--------------------------------------------------------------------------
VeRODepthStencilStateD3D11::VeRODepthStencilStateD3D11(const VeChar8* pcName)
	: VeRODepthStencilState(pcName), m_pkDepthStencilState(NULL)
{

}
//--------------------------------------------------------------------------
VeRODepthStencilStateD3D11::~VeRODepthStencilStateD3D11()
{
	VE_SAFE_RELEASE(m_pkDepthStencilState);
}
//--------------------------------------------------------------------------
void VeRODepthStencilStateD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkDepthStencilState);
	D3D11_DEPTH_STENCIL_DESC kDesc;
	VeByte byTemp;
	kIn >> byTemp;
	kDesc.DepthEnable = byTemp ? TRUE : FALSE;
	kIn >> byTemp;
	kDesc.DepthWriteMask = byTemp ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	kIn >> byTemp;
	kDesc.DepthFunc = (D3D11_COMPARISON_FUNC)byTemp;
	kIn >> byTemp;
	kDesc.StencilEnable = byTemp ? TRUE : FALSE;
	if(kDesc.StencilEnable)
	{
		kIn >> kDesc.StencilReadMask;
		kIn >> kDesc.StencilWriteMask;
		kIn >> byTemp;
		kDesc.FrontFace.StencilFailOp = (D3D11_STENCIL_OP)byTemp;
		kIn >> byTemp;
		kDesc.FrontFace.StencilDepthFailOp = (D3D11_STENCIL_OP)byTemp;
		kIn >> byTemp;
		kDesc.FrontFace.StencilPassOp = (D3D11_STENCIL_OP)byTemp;
		kIn >> byTemp;
		kDesc.FrontFace.StencilFunc = (D3D11_COMPARISON_FUNC)byTemp;
		kIn >> byTemp;
		kDesc.BackFace.StencilFailOp = (D3D11_STENCIL_OP)byTemp;
		kIn >> byTemp;
		kDesc.BackFace.StencilDepthFailOp = (D3D11_STENCIL_OP)byTemp;
		kIn >> byTemp;
		kDesc.BackFace.StencilPassOp = (D3D11_STENCIL_OP)byTemp;
		kIn >> byTemp;
		kDesc.BackFace.StencilFunc = (D3D11_COMPARISON_FUNC)byTemp;
		VeUInt16 u16Align;
		kIn >> u16Align;
	}
	else
	{
		kDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		kDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		kDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		kDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		kDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		kDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		kDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		kDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		kDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		kDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	}
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateDepthStencilState(&kDesc, &m_pkDepthStencilState), S_OK);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROInputLayoutD3D11, VeROInputLayout);
//--------------------------------------------------------------------------
VeROInputLayoutD3D11::VeROInputLayoutD3D11(const VeChar8* pcName)
	: VeROInputLayout(pcName), m_pkInputLayout(NULL)
{

}
//--------------------------------------------------------------------------
VeROInputLayoutD3D11::~VeROInputLayoutD3D11()
{
	VE_SAFE_RELEASE(m_pkInputLayout);
}
//--------------------------------------------------------------------------
void VeROInputLayoutD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkInputLayout);
	VeString kShaderName;
	kIn.GetStringAligned4(kShaderName);
	VeUInt32 u32DescNum;
	kIn >> u32DescNum;
	VeVector<D3D11_INPUT_ELEMENT_DESC> kDescList;
	kDescList.Resize(u32DescNum);
	for(VeUInt32 i(0); i < kDescList.Size(); ++i)
	{
		VeByte byTemp;
		kIn >> byTemp;
		kDescList[i].SemanticName = VeRendererD3D11::GetSemanticName((VeRenderer::Semantic)byTemp);
		kIn >> byTemp;
		kDescList[i].SemanticIndex = byTemp;
		kIn >> byTemp;
		kDescList[i].Format = (DXGI_FORMAT)byTemp;
		kIn >> byTemp;
		kDescList[i].InputSlot = byTemp;
		kIn >> byTemp;
		kDescList[i].AlignedByteOffset = byTemp;
		kIn >> byTemp;
		kDescList[i].InputSlotClass = (D3D11_INPUT_CLASSIFICATION)byTemp;
		VeUInt16 u16InstanceDataRate;
		kIn >> u16InstanceDataRate;
		kDescList[i].InstanceDataStepRate = u16InstanceDataRate;
	}
	VeShaderResourcePtr spVertexShader = VeGetVertexShader(kShaderName, NULL);
	VE_ASSERT(spVertexShader && spVertexShader->GetType() == VeResource::VERTEX_SHADER
		&& spVertexShader->GetState() == VeResource::LOADED);
	VeBlobPtr spBlob = spVertexShader->GetBlob();
	VE_ASSERT(spBlob);
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateInputLayout(kDescList.Begin(), kDescList.Size(), spBlob->GetBuffer(), spBlob->GetSize(), &m_pkInputLayout), S_OK);
}
//--------------------------------------------------------------------------
void FillDepthBiasMode(VeRenderer::DepthBiasMode eMode, D3D11_RASTERIZER_DESC& kDesc)
{
	kDesc.DepthBias = 0;
	kDesc.SlopeScaledDepthBias = 0;
	kDesc.DepthBiasClamp = 0;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRORasterizeStateD3D11, VeRORasterizeState);
//--------------------------------------------------------------------------
VeRORasterizeStateD3D11::VeRORasterizeStateD3D11(const VeChar8* pcName)
	: VeRORasterizeState(pcName), m_pkRasterizerState(NULL)
{

}
//--------------------------------------------------------------------------
VeRORasterizeStateD3D11::~VeRORasterizeStateD3D11()
{
	VE_SAFE_RELEASE(m_pkRasterizerState);
}
//--------------------------------------------------------------------------
void VeRORasterizeStateD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkRasterizerState);
	D3D11_RASTERIZER_DESC kDesc;
	VeByte byTemp;
	kIn >> byTemp;
	kDesc.FillMode = (D3D11_FILL_MODE)byTemp;
	kIn >> byTemp;
	kDesc.CullMode = (D3D11_CULL_MODE)byTemp;
	kIn >> byTemp;
	kDesc.FrontCounterClockwise = byTemp ? TRUE : FALSE;
	kIn >> byTemp;
	FillDepthBiasMode((VeRenderer::DepthBiasMode)byTemp, kDesc);
	kIn >> byTemp;
	kDesc.DepthClipEnable = byTemp ? TRUE : FALSE;
	kIn >> byTemp;
	kDesc.ScissorEnable = byTemp ? TRUE : FALSE;
	kIn >> byTemp;
	kDesc.MultisampleEnable = byTemp ? TRUE : FALSE;
	kIn >> byTemp;
	kDesc.AntialiasedLineEnable = byTemp ? TRUE : FALSE;
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateRasterizerState(&kDesc, &m_pkRasterizerState), S_OK);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROSamplerStateD3D11, VeROSamplerState);
//--------------------------------------------------------------------------
VeROSamplerStateD3D11::VeROSamplerStateD3D11(const VeChar8* pcName)
	: VeROSamplerState(pcName), m_pkSamplerState(NULL)
{

}
//--------------------------------------------------------------------------
VeROSamplerStateD3D11::~VeROSamplerStateD3D11()
{
	VE_SAFE_RELEASE(m_pkSamplerState);
}
//--------------------------------------------------------------------------
void VeROSamplerStateD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkSamplerState);
	D3D11_SAMPLER_DESC kDesc;
	VeByte byTemp;
	kIn >> byTemp;
	kDesc.Filter = (D3D11_FILTER)byTemp;
	kIn >> byTemp;
	kDesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)byTemp;
	kIn >> byTemp;
	kDesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)byTemp;
	kIn >> byTemp;
	kDesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)byTemp;
	VeUInt16 u16Temp;
	kIn >> u16Temp;
	kDesc.MaxAnisotropy = VE_MIN(u16Temp, 16);
	kIn >> u16Temp;
	kDesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)u16Temp;
	kIn >> kDesc.MipLODBias;
	kIn >> kDesc.MinLOD;
	kIn >> kDesc.MaxLOD;
	for(VeUInt32 i(0); i < 4; ++i)
	{
		kIn >> kDesc.BorderColor[i];
	}
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateSamplerState(&kDesc, &m_pkSamplerState), S_OK);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROBufferD3D11, VeROBuffer);
//--------------------------------------------------------------------------
VeROBufferD3D11::VeROBufferD3D11(const VeChar8* pcName)
	: VeROBuffer(pcName), m_pkBuffer(NULL)
{

}
//--------------------------------------------------------------------------
VeROBufferD3D11::~VeROBufferD3D11()
{
	VE_SAFE_RELEASE(m_pkBuffer);
}
//--------------------------------------------------------------------------
VeUInt32 VeROBufferD3D11::GetBindFlag()
{
	VE_ASSERT(m_pkBuffer);
	D3D11_BUFFER_DESC kDesc;
	m_pkBuffer->GetDesc(&kDesc);
	return kDesc.BindFlags;
}
//--------------------------------------------------------------------------
VeUInt32 VeROBufferD3D11::GetCpuAccessFlag()
{
	VE_ASSERT(m_pkBuffer);
	D3D11_BUFFER_DESC kDesc;
	m_pkBuffer->GetDesc(&kDesc);
	return kDesc.CPUAccessFlags;
}
//--------------------------------------------------------------------------
VeUInt32 VeROBufferD3D11::GetResourceMiscFlag()
{
	VE_ASSERT(m_pkBuffer);
	D3D11_BUFFER_DESC kDesc;
	m_pkBuffer->GetDesc(&kDesc);
	return kDesc.MiscFlags;
}
//--------------------------------------------------------------------------
void VeROBufferD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkBuffer);
	D3D11_BUFFER_DESC kDesc;
	kIn >> kDesc.ByteWidth;
	VeUInt16 u16Temp;
	kIn >> u16Temp;
	kDesc.MiscFlags = u16Temp;
	kIn >> u16Temp;
	kDesc.StructureByteStride = u16Temp;
	VeByte byTemp;
	kIn >> byTemp;
	if(byTemp == VeRenderer::USAGE_STREAM) byTemp = VeRenderer::USAGE_DYNAMIC;
	kDesc.Usage = (D3D11_USAGE)byTemp;
	kIn >> byTemp;
	kDesc.BindFlags = byTemp;
	kIn >> byTemp;
	kDesc.CPUAccessFlags = byTemp << 16;
	kIn >> byTemp;
	if(byTemp)
	{
		D3D11_SUBRESOURCE_DATA kInitData;
		kIn >> kInitData.SysMemPitch;
		kIn >> kInitData.SysMemSlicePitch;
		VE_ASSERT(((kDesc.ByteWidth) & 3) == 0);
		kInitData.pSysMem = kIn.Skip(kDesc.ByteWidth);
		VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateBuffer(&kDesc, &kInitData, &m_pkBuffer), S_OK);
	}
	else
	{
		VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateBuffer(&kDesc, NULL, &m_pkBuffer), S_OK);
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODepthStencilViewD3D11, VeRODepthStencilView);
//--------------------------------------------------------------------------
VeRODepthStencilViewD3D11::VeRODepthStencilViewD3D11(const VeChar8* pcName)
	: VeRODepthStencilView(pcName), m_pkDepthStencilView(NULL)
{

}
//--------------------------------------------------------------------------
VeRODepthStencilViewD3D11::~VeRODepthStencilViewD3D11()
{
	VE_SAFE_RELEASE(m_pkDepthStencilView);
}
//--------------------------------------------------------------------------
void VeRODepthStencilViewD3D11::OnDel()
{
	m_spShaderResourceView = NULL;
}
//--------------------------------------------------------------------------
void VeRODepthStencilViewD3D11::OnClear()
{
	m_spShaderResourceView = NULL;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRORenderTargetViewD3D11, VeRORenderTargetView);
//--------------------------------------------------------------------------
VeRORenderTargetViewD3D11::VeRORenderTargetViewD3D11(const VeChar8* pcName)
	: VeRORenderTargetView(pcName), m_pkRenderTargetView(NULL)
	, m_u32Active(VeUInt32(-1))
{

}
//--------------------------------------------------------------------------
VeRORenderTargetViewD3D11::~VeRORenderTargetViewD3D11()
{
	VE_SAFE_RELEASE(m_pkRenderTargetView);
}
//--------------------------------------------------------------------------
void VeRORenderTargetViewD3D11::OnDel()
{
	m_spShaderResourceView = NULL;
}
//--------------------------------------------------------------------------
void VeRORenderTargetViewD3D11::OnClear()
{
	m_spShaderResourceView = NULL;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROShaderResourceViewD3D11, VeROShaderResourceView);
//--------------------------------------------------------------------------
VeROShaderResourceViewD3D11::VeROShaderResourceViewD3D11(const VeChar8* pcName)
	: VeROShaderResourceView(pcName), m_pkShaderResourceView(NULL), m_u64Active(VeUInt64(-1))
{

}
//--------------------------------------------------------------------------
VeROShaderResourceViewD3D11::~VeROShaderResourceViewD3D11()
{
	VE_SAFE_RELEASE(m_pkShaderResourceView);
}
//--------------------------------------------------------------------------
void VeROShaderResourceViewD3D11::OnDel()
{
	m_spRenderTargetView = NULL;
	m_spDepthStencilView = NULL;
}
//--------------------------------------------------------------------------
void VeROShaderResourceViewD3D11::OnClear()
{
	m_spRenderTargetView = NULL;
	m_spDepthStencilView = NULL;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROTexture1DD3D11, VeROTexture1D);
//--------------------------------------------------------------------------
VeROTexture1DD3D11::VeROTexture1DD3D11(const VeChar8* pcName, ID3D11Texture1D* pkObj)
	: VeROTexture1D(pcName), m_pkTexture1D(pkObj)
{

}
//--------------------------------------------------------------------------
VeROTexture1DD3D11::~VeROTexture1DD3D11()
{
	VE_SAFE_RELEASE(m_pkTexture1D);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROTexture2DD3D11, VeROTexture2D);
//--------------------------------------------------------------------------
VeROTexture2DD3D11::VeROTexture2DD3D11(const VeChar8* pcName)
	: VeROTexture2D(pcName), m_pkTexture2D(NULL), m_pkCopyRect(NULL)
{

}
//--------------------------------------------------------------------------
VeROTexture2DD3D11::~VeROTexture2DD3D11()
{
	VE_SAFE_RELEASE(m_pkTexture2D);
	VE_SAFE_RELEASE(m_pkCopyRect);
}
//--------------------------------------------------------------------------
void VeROTexture2DD3D11::OnDel()
{
	if(m_spSRV)
	{
		((VeRendererD3D11*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spSRV));
		m_spSRV = NULL;
	}
	if(m_spRTV)
	{
		((VeRendererD3D11*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spRTV));
		m_spRTV = NULL;
	}
	if(m_spDSV)
	{
		((VeRendererD3D11*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spDSV));
		m_spDSV = NULL;
	}
}
//--------------------------------------------------------------------------
void VeROTexture2DD3D11::UpdateData(VeUInt32 u32Mip, VeUInt32 u32Array, void* pvData)
{
	/*VE_ASSERT(m_pkTexture2D);
	D3D11_TEXTURE2D_DESC kDesc;
	m_pkTexture2D->GetDesc(&kDesc);
	VE_ASSERT(VE_MASK_HAS_ANY(kDesc.CPUAccessFlags, D3D11_CPU_ACCESS_WRITE));
	VE_ASSERT(u32Mip < kDesc.MipLevels && u32Array < kDesc.ArraySize);
	D3D11_MAPPED_SUBRESOURCE kSubRes;
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetImmediateContext()->Map(m_pkTexture2D, u32Mip + u32Array * kDesc.MipLevels, D3D11_MAP_WRITE, 0, &kSubRes), S_OK);*/
}
//--------------------------------------------------------------------------
void VeROTexture2DD3D11::CopyRect(VeUInt32 u32Mip, VeUInt32 x, VeUInt32 y,
	VeUInt32 w, VeUInt32 h, VeUInt32 u32Format, void* pvData)
{
	VE_ASSERT(m_pkTexture2D);
	if(m_pkCopyRect)
	{
		D3D11_TEXTURE2D_DESC kDesc;
		m_pkCopyRect->GetDesc(&kDesc);
		if(kDesc.Width != w || kDesc.Height != h || kDesc.Format != u32Format)
			VE_SAFE_RELEASE(m_pkCopyRect);
	}
	if(!m_pkCopyRect)
	{
		D3D11_TEXTURE2D_DESC kDesc;
		kDesc.Width = w;
		kDesc.Height = h;
		kDesc.MipLevels = 1;
		kDesc.ArraySize = 1;
		DXGI_FORMAT eFormat = (DXGI_FORMAT)u32Format;
		kDesc.Format = GetGeneralTextureFormat(eFormat);
		kDesc.SampleDesc.Count = 1;
		kDesc.SampleDesc.Quality = 0;
		kDesc.Usage = D3D11_USAGE_STAGING;
		kDesc.BindFlags = 0;
		kDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		kDesc.MiscFlags = 0;
		VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateTexture2D(&kDesc, NULL, &m_pkCopyRect), S_OK);
	}
	VeUInt32 u32PixelPerUnit(0);
	VeUInt32 u32BytePerUnit(0);
	VE_ASSERT_EQ(CheckFormat((VeRenderer::Format)u32Format, u32PixelPerUnit, u32BytePerUnit), true);
	D3D11_MAPPED_SUBRESOURCE kSubRes;
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetImmediateContext()->Map(m_pkCopyRect, 0, D3D11_MAP_WRITE, 0, &kSubRes), S_OK);
	VeByte* pbyDes = (VeByte*)kSubRes.pData;
	VeByte* pbySrc = (VeByte*)pvData;
	VeUInt32 u32Pitch = w / u32PixelPerUnit * u32BytePerUnit;
	for(VeUInt32 i(0); i < h; ++i)
	{
		VeCrazyCopy(pbyDes, pbySrc, u32Pitch);
		pbySrc += u32Pitch;
		pbyDes += kSubRes.RowPitch;
	}
	((VeRendererD3D11*)g_pRenderer)->GetImmediateContext()->Unmap(m_pkCopyRect, 0);
	((VeRendererD3D11*)g_pRenderer)->GetImmediateContext()->CopySubresourceRegion(m_pkTexture2D, 0, x, y, 0, m_pkCopyRect, 0, NULL);
}
//--------------------------------------------------------------------------
void VeROTexture2DD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkTexture2D);
	if(m_spSRV)
	{
		((VeRendererD3D11*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spSRV));
		m_spSRV = NULL;
	}
	if(m_spRTV)
	{
		((VeRendererD3D11*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spRTV));
		m_spRTV = NULL;
	}
	if(m_spDSV)
	{
		((VeRendererD3D11*)g_pRenderer)->DelObject(VeSmartPointerCast(VeRenderObject, m_spDSV));
		m_spDSV = NULL;
	}
	D3D11_TEXTURE2D_DESC kDesc;
	VeUInt16 u16Temp;
	kIn >> u16Temp;
	kDesc.Width = u16Temp;
	kIn >> u16Temp;
	kDesc.Height = u16Temp;
	kIn >> u16Temp;
	kDesc.MipLevels = u16Temp;
	kIn >> u16Temp;
	kDesc.ArraySize = u16Temp;
	VeByte byTemp;
	kIn >> byTemp;
	DXGI_FORMAT eFormat = (DXGI_FORMAT)byTemp;
	kDesc.Format = GetGeneralTextureFormat(eFormat);
	kIn >> byTemp;
	kDesc.SampleDesc.Count = byTemp;
	kIn >> byTemp;
	kDesc.SampleDesc.Quality = byTemp;
	kIn >> byTemp;
	kDesc.Usage = (D3D11_USAGE)byTemp;
	kIn >> byTemp;
	kDesc.BindFlags = byTemp;
	kIn >> byTemp;
	kDesc.CPUAccessFlags = byTemp << 16;
	kIn >> u16Temp;
	kDesc.MiscFlags = u16Temp;
	bool bCreateViews;
	kIn >> u16Temp;
	bCreateViews = u16Temp ? true : false;
	kIn >> u16Temp;
	if(u16Temp)
	{
		VeVector<D3D11_SUBRESOURCE_DATA> kDataArray;
		kDataArray.Resize(u16Temp);
		for(VeUInt16 i(0); i < u16Temp; ++i)
		{
			kIn >> kDataArray[i].SysMemPitch;
			kIn >> kDataArray[i].SysMemSlicePitch;
			VeUInt32 u32ByteWidth;
			kIn >> u32ByteWidth;
			VE_ASSERT((u32ByteWidth & 3) == 0);
			kDataArray[i].pSysMem = kIn.Skip(u32ByteWidth);
		}
		VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateTexture2D(&kDesc, kDataArray.Begin(), &m_pkTexture2D), S_OK);
	}
	else
	{
		VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateTexture2D(&kDesc, NULL, &m_pkTexture2D), S_OK);
	}
	if(bCreateViews)
	{
		if(VE_MASK_HAS_ANY(kDesc.BindFlags, D3D11_BIND_RENDER_TARGET))
		{
			ID3D11RenderTargetView* pkView;
			D3D11_RENDER_TARGET_VIEW_DESC kViewDesc =
			{
				GetGeneralRTVFormat(eFormat),
				D3D11_RTV_DIMENSION_TEXTURE2D,
				0
			};
			if(kDesc.SampleDesc.Count > 1)
			{
				kViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			}
			VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateRenderTargetView(m_pkTexture2D, &kViewDesc, &pkView), S_OK);
			m_spRTV = VE_NEW VeRORenderTargetViewD3D11(GetName());
			m_spRTV->m_pkRenderTargetView = pkView;
			((VeRendererD3D11*)g_pRenderer)->AddObject(VeSmartPointerCast(VeRenderObject, m_spRTV));
		}
		if(VE_MASK_HAS_ANY(kDesc.BindFlags, D3D11_BIND_DEPTH_STENCIL))
		{
			ID3D11DepthStencilView* pkView;
			D3D11_DEPTH_STENCIL_VIEW_DESC kViewDesc =
			{
				GetGeneralDSVFormat(eFormat),
				D3D11_DSV_DIMENSION_TEXTURE2D,
				0
			};
			if(kDesc.SampleDesc.Count > 1)
			{
				kViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			}
			VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateDepthStencilView(m_pkTexture2D, &kViewDesc, &pkView), S_OK);
			m_spDSV = VE_NEW VeRODepthStencilViewD3D11(GetName());
			m_spDSV->m_pkDepthStencilView = pkView;
			((VeRendererD3D11*)g_pRenderer)->AddObject(VeSmartPointerCast(VeRenderObject, m_spDSV));
		}
		if(VE_MASK_HAS_ANY(kDesc.BindFlags, D3D11_BIND_SHADER_RESOURCE))
		{
			ID3D11ShaderResourceView* pkView;
			D3D11_SHADER_RESOURCE_VIEW_DESC kViewDesc =
			{
				GetGeneralSRVFormat(eFormat),
				D3D11_SRV_DIMENSION_TEXTURE2D,
				0,
				1,
			};
			if(kDesc.SampleDesc.Count > 1)
			{
				kViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
			}
			VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateShaderResourceView(m_pkTexture2D, &kViewDesc, &pkView), S_OK);
			m_spSRV = VE_NEW VeROShaderResourceViewD3D11(GetName());
			m_spSRV->m_pkShaderResourceView = pkView;
			((VeRendererD3D11*)g_pRenderer)->AddObject(VeSmartPointerCast(VeRenderObject, m_spSRV));
		}
		if(m_spSRV)
		{
			m_spSRV->m_spRenderTargetView = m_spRTV;
			m_spSRV->m_spDepthStencilView = m_spDSV;
		}
		if(m_spRTV)
		{
			m_spRTV->m_spShaderResourceView = m_spSRV;
		}
		if(m_spDSV)
		{
			m_spDSV->m_spShaderResourceView = m_spSRV;
		}
	}
}
//--------------------------------------------------------------------------
void VeROTexture2DD3D11::OnClear()
{
	m_spSRV = NULL;
	m_spRTV = NULL;
	m_spDSV = NULL;
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROTexture3DD3D11, VeROTexture3D);
//--------------------------------------------------------------------------
VeROTexture3DD3D11::VeROTexture3DD3D11(const VeChar8* pcName, ID3D11Texture3D* pkObj)
	: VeROTexture3D(pcName), m_pkTexture3D(pkObj)
{

}
//--------------------------------------------------------------------------
VeROTexture3DD3D11::~VeROTexture3DD3D11()
{
	VE_SAFE_RELEASE(m_pkTexture3D);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROComputeShaderD3D11, VeROComputeShader);
//--------------------------------------------------------------------------
VeROComputeShaderD3D11::VeROComputeShaderD3D11(const VeChar8* pcName, ID3D11ComputeShader* pkObj)
	: VeROComputeShader(pcName), m_pkShader(pkObj)
{

}
//--------------------------------------------------------------------------
VeROComputeShaderD3D11::~VeROComputeShaderD3D11()
{
	VE_SAFE_RELEASE(m_pkShader);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeRODomainShaderD3D11, VeRODomainShader);
//--------------------------------------------------------------------------
VeRODomainShaderD3D11::VeRODomainShaderD3D11(const VeChar8* pcName, ID3D11DomainShader* pkObj)
	: VeRODomainShader(pcName), m_pkShader(pkObj)
{

}
//--------------------------------------------------------------------------
VeRODomainShaderD3D11::~VeRODomainShaderD3D11()
{
	VE_SAFE_RELEASE(m_pkShader);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROGeometryShaderD3D11, VeROGeometryShader);
//--------------------------------------------------------------------------
VeROGeometryShaderD3D11::VeROGeometryShaderD3D11(const VeChar8* pcName, ID3D11GeometryShader* pkObj)
	: VeROGeometryShader(pcName), m_pkShader(pkObj)
{

}
//--------------------------------------------------------------------------
VeROGeometryShaderD3D11::~VeROGeometryShaderD3D11()
{
	VE_SAFE_RELEASE(m_pkShader);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROHullShaderD3D11, VeROHullShader);
//--------------------------------------------------------------------------
VeROHullShaderD3D11::VeROHullShaderD3D11(const VeChar8* pcName, ID3D11HullShader* pkObj)
	: VeROHullShader(pcName), m_pkShader(pkObj)
{

}
//--------------------------------------------------------------------------
VeROHullShaderD3D11::~VeROHullShaderD3D11()
{
	VE_SAFE_RELEASE(m_pkShader);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROPixelShaderD3D11, VeROPixelShader);
//--------------------------------------------------------------------------
VeROPixelShaderD3D11::VeROPixelShaderD3D11(const VeChar8* pcName)
	: VeROPixelShader(pcName), m_pkShader(NULL)
{

}
//--------------------------------------------------------------------------
VeROPixelShaderD3D11::~VeROPixelShaderD3D11()
{
	VE_SAFE_RELEASE(m_pkShader);
}
//--------------------------------------------------------------------------
void VeROPixelShaderD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkShader);
	VeInt32 iLen = kIn.RemainingLength();
	void* pvShader = kIn.Skip(iLen);
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreatePixelShader(pvShader, iLen, NULL, &m_pkShader), S_OK);
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeROVertexShaderD3D11, VeROVertexShader);
//--------------------------------------------------------------------------
VeROVertexShaderD3D11::VeROVertexShaderD3D11(const VeChar8* pcName)
	: VeROVertexShader(pcName), m_pkShader(NULL)
{

}
//--------------------------------------------------------------------------
VeROVertexShaderD3D11::~VeROVertexShaderD3D11()
{
	VE_SAFE_RELEASE(m_pkShader);
}
//--------------------------------------------------------------------------
void VeROVertexShaderD3D11::From(VeBinaryIStream& kIn)
{
	VE_SAFE_RELEASE(m_pkShader);
	VeInt32 iLen = kIn.RemainingLength();
	void* pvShader = kIn.Skip(iLen);
	VE_ASSERT_EQ(((VeRendererD3D11*)g_pRenderer)->GetDevice()->CreateVertexShader(pvShader, iLen, NULL, &m_pkShader), S_OK);
}
//--------------------------------------------------------------------------
VeMSAAResolveD3D11::VeMSAAResolveD3D11(const VeChar8* pcName)
	: VeRenderProcess(TYPE_MSAA_RESOLVE, pcName)
{

}
//--------------------------------------------------------------------------
VeMSAAResolveD3D11::~VeMSAAResolveD3D11()
{
	Clear();
}
//--------------------------------------------------------------------------
bool VeMSAAResolveD3D11::Update(VeBinaryIStream& kStream)
{
	Clear();
	VeUInt16 u16RenderTargetNum, u16DepthStencilTargetNum;
	kStream >> u16RenderTargetNum;
	kStream >> u16DepthStencilTargetNum;
	VeString kTemp;
	for(VeUInt32 i(0); i < VeUInt32(u16RenderTargetNum + u16DepthStencilTargetNum); ++i)
	{
		VeROTexture2DPtr spTexture;
		kStream.GetStringAligned4(kTemp);
		g_pRenderer->GetRenderObject(kTemp, spTexture);
		VeROTexture2DD3D11* pkDst = (VeROTexture2DD3D11*)(VeROTexture2D*)spTexture;
		kStream.GetStringAligned4(kTemp);
		g_pRenderer->GetRenderObject(kTemp, spTexture);
		VeROTexture2DD3D11* pkSrc = (VeROTexture2DD3D11*)(VeROTexture2D*)spTexture;
		if(pkDst && pkSrc)
		{
			pkDst->m_pkTexture2D->AddRef();
			pkSrc->m_pkTexture2D->AddRef();
			m_kResolveLinks.PushBack(VePair<ID3D11Texture2D*,ID3D11Texture2D*>(pkDst->m_pkTexture2D, pkSrc->m_pkTexture2D));
		}
	}
	return m_kResolveLinks.Size() ? true : false;
}
//--------------------------------------------------------------------------
void VeMSAAResolveD3D11::Clear()
{
	for(VeUInt32 i(0); i < m_kResolveLinks.Size(); ++i)
	{
		m_kResolveLinks[i].m_tFirst->Release();
		m_kResolveLinks[i].m_tSecond->Release();
	}
	m_kResolveLinks.Clear();
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
