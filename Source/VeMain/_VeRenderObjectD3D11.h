////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRenderObjectD3D11.h
//  Version:     v1.00
//  Created:     31/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VE_ENABLE_D3D11

#include <d3d11.h>

class VeROBlendStateD3D11 : public VeROBlendState
{
	VeDeclareRTTI;
public:
	VeROBlendStateD3D11(const VeChar8* pcName);

	virtual ~VeROBlendStateD3D11();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11BlendState* m_pkBlendState;

};

VeSmartPointer(VeROBlendStateD3D11);

class VeRODepthStencilStateD3D11 : public VeRODepthStencilState
{
	VeDeclareRTTI;
public:
	VeRODepthStencilStateD3D11(const VeChar8* pcName);

	virtual ~VeRODepthStencilStateD3D11();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11DepthStencilState* m_pkDepthStencilState;

};

VeSmartPointer(VeRODepthStencilStateD3D11);

class VeROInputLayoutD3D11 : public VeROInputLayout
{
	VeDeclareRTTI;
public:
	VeROInputLayoutD3D11(const VeChar8* pcName);

	virtual ~VeROInputLayoutD3D11();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11InputLayout* m_pkInputLayout;

};

VeSmartPointer(VeROInputLayoutD3D11);

class VeRORasterizeStateD3D11 : public VeRORasterizeState
{
	VeDeclareRTTI;
public:
	VeRORasterizeStateD3D11(const VeChar8* pcName);

	virtual ~VeRORasterizeStateD3D11();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11RasterizerState* m_pkRasterizerState;

};

VeSmartPointer(VeRORasterizeStateD3D11);

class VeROSamplerStateD3D11 : public VeROSamplerState
{
	VeDeclareRTTI;
public:
	VeROSamplerStateD3D11(const VeChar8* pcName);

	virtual ~VeROSamplerStateD3D11();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11SamplerState* m_pkSamplerState;

};

VeSmartPointer(VeROSamplerStateD3D11);

class VeROBufferD3D11 : public VeROBuffer
{
	VeDeclareRTTI;
public:
	VeROBufferD3D11(const VeChar8* pcName);

	virtual ~VeROBufferD3D11();

	virtual VeUInt32 GetBindFlag();

	virtual VeUInt32 GetCpuAccessFlag();

	virtual VeUInt32 GetResourceMiscFlag();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11Buffer* m_pkBuffer;

};

VeSmartPointer(VeROBufferD3D11);

VeSmartPointer(VeROShaderResourceViewD3D11);
VeSmartPointer(VeRORenderTargetViewD3D11);
VeSmartPointer(VeRODepthStencilViewD3D11);

class VeRODepthStencilViewD3D11 : public VeRODepthStencilView
{
	VeDeclareRTTI;
public:
	VeRODepthStencilViewD3D11(const VeChar8* pcName);

	virtual ~VeRODepthStencilViewD3D11();

	virtual void OnDel();

	virtual void OnClear();

	ID3D11DepthStencilView* m_pkDepthStencilView;
	VeROShaderResourceViewD3D11Ptr m_spShaderResourceView;

};

class VeRORenderTargetViewD3D11 : public VeRORenderTargetView
{
	VeDeclareRTTI;
public:
	VeRORenderTargetViewD3D11(const VeChar8* pcName);

	virtual ~VeRORenderTargetViewD3D11();

	virtual void OnDel();

	virtual void OnClear();

	ID3D11RenderTargetView* m_pkRenderTargetView;
	VeUInt32 m_u32Active;
	VeROShaderResourceViewD3D11Ptr m_spShaderResourceView;

};

class VeROShaderResourceViewD3D11 : public VeROShaderResourceView
{
	VeDeclareRTTI;
public:
	VeROShaderResourceViewD3D11(const VeChar8* pcName);

	virtual ~VeROShaderResourceViewD3D11();

	virtual void OnDel();

	virtual void OnClear();

	ID3D11ShaderResourceView* m_pkShaderResourceView;
	union
	{
		VeUInt64 m_u64Active;
		VeUInt8 m_au8Active[8];
	};
	VeRORenderTargetViewD3D11Ptr m_spRenderTargetView;
	VeRODepthStencilViewD3D11Ptr m_spDepthStencilView;

};

class VeROTexture1DD3D11 : public VeROTexture1D
{
	VeDeclareRTTI;
public:
	VeROTexture1DD3D11(const VeChar8* pcName, ID3D11Texture1D* pkObj);

	virtual ~VeROTexture1DD3D11();

	ID3D11Texture1D* m_pkTexture1D;

};

VeSmartPointer(VeROTexture1DD3D11);

class VeROTexture2DD3D11 : public VeROTexture2D
{
	VeDeclareRTTI;
public:
	VeROTexture2DD3D11(const VeChar8* pcName);

	virtual ~VeROTexture2DD3D11();

	virtual void OnDel();

	virtual void OnClear();

	virtual void UpdateData(VeUInt32 u32Mip, VeUInt32 u32Array, void* pvData);

	virtual void CopyRect(VeUInt32 u32Mip, VeUInt32 x, VeUInt32 y, VeUInt32 w, VeUInt32 h, VeUInt32 u32Format, void* pvData);

	virtual void From(VeBinaryIStream& kIn);

	ID3D11Texture2D* m_pkTexture2D;
	ID3D11Texture2D* m_pkCopyRect;
	VeROShaderResourceViewD3D11Ptr m_spSRV;
	VeRORenderTargetViewD3D11Ptr m_spRTV;
	VeRODepthStencilViewD3D11Ptr m_spDSV;

};

VeSmartPointer(VeROTexture2DD3D11);

class VeROTexture3DD3D11 : public VeROTexture3D
{
	VeDeclareRTTI;
public:
	VeROTexture3DD3D11(const VeChar8* pcName, ID3D11Texture3D* pkObj);

	virtual ~VeROTexture3DD3D11();

	ID3D11Texture3D* m_pkTexture3D;

};

VeSmartPointer(VeROTexture3DD3D11);

class VeROComputeShaderD3D11 : public VeROComputeShader
{
	VeDeclareRTTI;
public:
	VeROComputeShaderD3D11(const VeChar8* pcName, ID3D11ComputeShader* pkObj);

	virtual ~VeROComputeShaderD3D11();

	ID3D11ComputeShader* m_pkShader;

};

VeSmartPointer(VeROComputeShaderD3D11);

class VeRODomainShaderD3D11 : public VeRODomainShader
{
	VeDeclareRTTI;
public:
	VeRODomainShaderD3D11(const VeChar8* pcName, ID3D11DomainShader* pkObj);

	virtual ~VeRODomainShaderD3D11();

	ID3D11DomainShader* m_pkShader;

};

VeSmartPointer(VeRODomainShaderD3D11);

class VeROGeometryShaderD3D11 : public VeROGeometryShader
{
	VeDeclareRTTI;
public:
	VeROGeometryShaderD3D11(const VeChar8* pcName, ID3D11GeometryShader* pkObj);

	virtual ~VeROGeometryShaderD3D11();

	ID3D11GeometryShader* m_pkShader;

};

VeSmartPointer(VeROGeometryShaderD3D11);

class VeROHullShaderD3D11 : public VeROHullShader
{
	VeDeclareRTTI;
public:
	VeROHullShaderD3D11(const VeChar8* pcName, ID3D11HullShader* pkObj);

	virtual ~VeROHullShaderD3D11();

	ID3D11HullShader* m_pkShader;

};

VeSmartPointer(VeROHullShaderD3D11);

class VeROPixelShaderD3D11 : public VeROPixelShader
{
	VeDeclareRTTI;
public:
	VeROPixelShaderD3D11(const VeChar8* pcName);

	virtual ~VeROPixelShaderD3D11();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11PixelShader* m_pkShader;

};

VeSmartPointer(VeROPixelShaderD3D11);

class VeROVertexShaderD3D11 : public VeROVertexShader
{
	VeDeclareRTTI;
public:
	VeROVertexShaderD3D11(const VeChar8* pcName);

	virtual ~VeROVertexShaderD3D11();

	virtual void From(VeBinaryIStream& kIn);

	ID3D11VertexShader* m_pkShader;

};

VeSmartPointer(VeROVertexShaderD3D11);

class VeMSAAResolveD3D11 : public VeRenderProcess
{
public:
	VeMSAAResolveD3D11(const VeChar8* pcName);

	virtual ~VeMSAAResolveD3D11();

	virtual bool Update(VeBinaryIStream& kStream);

	void Clear();

	VeVector<VePair<ID3D11Texture2D*,ID3D11Texture2D*>> m_kResolveLinks;

};

VeSmartPointer(VeMSAAResolveD3D11);

#endif
