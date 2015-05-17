////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRendererD3D11.h
//  Version:     v1.00
//  Created:     17/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VE_ENABLE_D3D11

#include <d3d11.h>
#include "_VeRenderObjectD3D11.h"

#define VE_D3D11_BUFFER_COUNT 1
#define VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT 32

class VeRendererD3D11 : public VeRenderer
{
public:
	enum StateType
	{
		IA_VERTEX_BUFFER,
		IA_INDEX_BUFFER,
		IA_INPUT_LAYOUT,
		IA_PRIMITIVE_TOPOLOGY
	};

	VeRendererD3D11();

	virtual ~VeRendererD3D11();

	virtual API GetAPI();

	virtual VeUInt32 CheckCapability(Capability eCap);

	virtual void Init();

	virtual void Term();

	virtual void Render();

	virtual void Present();

	virtual void SetFullScreen(bool bEnable);

	//virtual void SetDisplay(Display& kDisplay);

	virtual void ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height);

	virtual void ResizeBuffer(VeUInt32 u32Width, VeUInt32 u32Height);

	virtual void OnActive();

	virtual void OnInactive();

	virtual void GetMatrixPerspectiveFov(VeFloat32* pf32OutMat4x4, VeFloat32 fov, VeFloat32 znear, VeFloat32 zfar);

	virtual const VeChar8* GetShaderName();

	virtual const VeChar8* GetShaderProfile();

	virtual VeUInt32 GetMultisampleLevelCount();

	virtual void EnumMultisampleLevel(VeUInt32 u32Index, VeUInt32& u32Count, VeUInt32& u32Quality);

	virtual void CreateVertexShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROVertexShaderPtr* pspShader);

	virtual void CreatePixelShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROPixelShaderPtr* pspShader);

	virtual void CreateBlendState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBlendStatePtr* pspBlendState);

	virtual void CreateDepthStencilState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRODepthStencilStatePtr* pspDepthStencilState);

	virtual void CreateInputLayout(const VeChar8* pcName, VeBinaryIStream& kStream, VeROInputLayoutPtr* pspLayout);

	virtual void CreateRasterizerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRORasterizeStatePtr* pspRasterizeState);

	virtual void CreateBuffer(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBufferPtr* pspBuffer);

	virtual void CreateSamplerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROSamplerStatePtr* pspSamplerState);

	virtual void CreateTexture2D(const VeChar8* pcName, VeBinaryIStream& kStream, VeROTexture2DPtr* pspTexture);

	virtual bool CreateProcessByType(VeRenderProcess::Type eType, const VeChar8* pcName, VeBinaryIStream& kStream, VeRenderProcessPtr* pspProcess);

	virtual bool MapRes(const VeRenderObjectPtr& spObject, VeUInt32 u32SubResource, Map eType, VE_BOOL bSync, MappedSubresource* pkMapped);

	virtual void UnMapRes(const VeRenderObjectPtr& spObject, VeUInt32 u32SubResource, MapWriteRange kRange);

	virtual void Render(VeRenderNode* pkNode);

	virtual void Process(const VeRenderProcessPtr& spProcess);

	void PushTick(VeRenderTick* pkTick);

	void PopTick(VeRenderTick* pkTick);

	void Call(VeRenderCall* pkCall);

	void FlushRenderTarget();

	void FlushStates();

	void UpdateBufferSize();

	void UpdateFullScreen();

	ID3D11Device* GetDevice();

	ID3D11DeviceContext* GetImmediateContext();

	static const VeChar8* GetSemanticName(Semantic eSemantic);

	static void Create();

protected:
	friend class VeROTexture2DD3D11;
	void InitGlobal();

	void TermGlobal();

	void ResetStateCache();

	void SetNull(const VeRODepthStencilViewD3D11Ptr& spDepthStencilView);

	void SetNull(const VeRORenderTargetViewD3D11Ptr& spRenderTargetView);

	void SetNull(const VeROShaderResourceViewD3D11Ptr& spShaderResourceView);

	virtual void CreateRenderObjects();

	virtual void CreateNodeDatas();

	VeSharedLib* m_pkLibDXGI;
	VeSharedLib* m_pkLibD3D11;
	D3D_FEATURE_LEVEL m_eCurrentLevel;
	IDXGIFactory1* m_pkDXGIFactory;
	ID3D11Device* m_pkDevice;
	ID3D11DeviceContext* m_pkImmediateContext;
	IDXGISwapChain* m_pkSwapChain;

	VeVector<DXGI_SAMPLE_DESC> m_kSampleDescArray;
	
	VeROTexture2DD3D11Ptr m_spBackBufferTEX;
	VeRORenderTargetViewD3D11Ptr m_spBackBufferRTV;

	struct Output : VeMemObject
	{
		typedef VePair<VeUInt32,VePair<VeUInt32,VeUInt32>> Mode;
		typedef VeHashSet<VePair<VeUInt32,VePair<VeUInt32,VeUInt32>>, Output> ModeSet;

		Output();
		~Output();

		static VeUInt32 KeyToHashCode(const Mode& kKey, VeUInt32 u32TableSize);

		IDXGIOutput* m_pkDXGIOutput;
		ModeSet m_kC8R8ModeSet;
		DXGI_MODE_DESC m_kC8R8ModeDefault;
		ModeSet m_kC10R2ModeSet;
		DXGI_MODE_DESC m_kC10R2ModeDefault;
	};

	struct Adapter : VeMemObject
	{
		Adapter();
		~Adapter();
		IDXGIAdapter1* m_pkDXGIAdapter;
		VeVector<Output> m_kOutputList;
	};
	VeVector<Adapter> m_kAdapterList;
	
	VE_BOOL m_bFullScreen;
	VeUInt32 m_u32Sync;

	VeVector<ID3D11VertexShader*> m_kVertexShaderStack;
	ID3D11VertexShader* m_pkCurVertexShader;
	
	VeVector<ID3D11PixelShader*> m_kPixelShaderStack;
	ID3D11PixelShader* m_pkCurPixelShader;

	struct BlendStateForSet
	{
		ID3D11BlendState* m_pkBlendState;
		FLOAT m_af32Factor[4];
		UINT m_uiSampleMask;
	};

	VeVector<BlendStateForSet> m_kBlendStateStack;
	BlendStateForSet m_kCurBlendState;
	VE_BOOL m_bBlendStateChange;

	struct DepthStencilStateForSet
	{
		ID3D11DepthStencilState* m_pkDepthStencilState;
		UINT m_uiStencilRef;
	};

	VeVector<DepthStencilStateForSet> m_kDepthStencilStateStack;
	DepthStencilStateForSet m_kCurDepthStencilState;
	VE_BOOL m_bDepthStencilStateChange;

	VeVector<ID3D11InputLayout*> m_kInputLayoutStack;
	ID3D11InputLayout* m_pkCurInputLayout;

	VeVector<ID3D11RasterizerState*> m_kRasterizerStateStack;
	ID3D11RasterizerState* m_pkCurRasterizerState;

	VeVector<D3D11_PRIMITIVE_TOPOLOGY> m_kTopologyStack;
	D3D11_PRIMITIVE_TOPOLOGY m_eCurTopology;

	struct IndexBufferForSet
	{
		ID3D11Buffer* m_pkBuffer;
		DXGI_FORMAT m_eFormat;
	};

	VeVector<IndexBufferForSet> m_kIndexBufferStack;
	ID3D11Buffer* m_pkCurIndexBuffer;
	DXGI_FORMAT m_eCurIndexBufferFormat;

	struct VertexBufferForSet
	{
		ID3D11Buffer* m_pkBuffer;
		UINT m_uiStride;
	};

	VeVector<VertexBufferForSet> m_akVertexBufferStack[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	ID3D11Buffer* m_apkCurVertexBuffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT m_auiCurVertexBufferStrides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	UINT m_auiCurVertexBufferOffsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	VeUInt32 m_u32VertexBufferChangeMin;
	VeUInt32 m_u32VertexBufferChangeMax;

	VeVector<ID3D11Buffer*> m_akVSCBufferStack[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	ID3D11Buffer* m_apkCurVSCBuffers[D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	VeUInt32 m_u32VSChangeCBufferMin;
	VeUInt32 m_u32VSChangeCBufferMax;

	VeVector<ID3D11SamplerState*> m_akPSSamplerStack[VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
	ID3D11SamplerState* m_apkCurPSSamplers[VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
	VeUInt32 m_u32PSChangeSamplerMin;
	VeUInt32 m_u32PSChangeSamplerMax;

	VeVector<VeROShaderResourceViewD3D11*> m_akPSShaderResourceViewStack[VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
	ID3D11ShaderResourceView* m_apkCurPSShaderResourceViews[VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
	VeUInt32 m_u32PSChangeSRVMin;
	VeUInt32 m_u32PSChangeSRVMax;

	VeVector<VeVector4D> m_akViewportStack[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	D3D11_VIEWPORT m_akCurViewports[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	VeUInt32 m_u32ActiveViewportCount;
	VeUInt32 m_u32ViewportChangeMax;

	VeVector<D3D11_RECT> m_akScissorRectStack[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	D3D11_RECT m_akCurScissorRects[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	VeUInt32 m_u32ActiveScissorRectCount;
	VeUInt32 m_u32ScissorRectChangeMax;

	VeVector<VeRORenderTargetViewD3D11*> m_akRenderTargetViewStack[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	VeVector<VeRODepthStencilViewD3D11*> m_kDepthStencilViewStack;
	ID3D11RenderTargetView* m_apkCurRenderTargetViews[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
	ID3D11DepthStencilView* m_pkCurDepthStencilView;
	VeUInt32 m_u32ActiveRenderTargetCount;
	VeUInt32 m_u32RenderTargetViewChangeMax;
};

#endif
