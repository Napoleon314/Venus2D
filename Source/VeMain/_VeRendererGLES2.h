////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRendererGLES2.h
//  Version:     v1.00
//  Created:     21/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VE_ENABLE_GLES2

#if defined(VE_PLATFORM_IOS)

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#else

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif

#include "_VeRenderObjectGLES2.h"

#define VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT 4
#define VE_GLES2_IA_VERTEX_ATTRIB_ARRAY_NUM 32
#define VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT 4

#define VE_GLES2_PS_TEX_NUM 4
#define VE_GLES2_VS_TEX_NUM 2
#define VE_GLES2_QUAD_BUFFER_SIZE 1572864

class VeRendererGLES2 : public VeRenderer
{
public:
	VeRendererGLES2();

	virtual ~VeRendererGLES2();

	virtual API GetAPI();

	virtual VeUInt32 CheckCapability(Capability eCap);

	virtual void Init();

	virtual void Term();

#ifdef VE_ENABLE_DEVICE_LOST

	virtual void AddRestoreDelegate(RestoreDelegate& kDelegate);

	virtual void Lost();

	virtual void Restore();

private:
	RestoreEvent m_kRestoreEvent;

public:

#endif

	void ApiInit();

	void ApiTerm();	

	virtual void Render();

	virtual void Present();

	virtual void OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height);

#	ifdef VE_PLATFORM_MOBILE_SIM
	virtual void ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height);
#   else
	void OnBufferRestorage();
#	endif

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

	VeUInt32 GetFrameBuffer(VeRORenderTargetViewGLES2* pkRTV, VeRODepthStencilViewGLES2* pkDSV);

	VeUInt32 GetMaxAnisotropy();

	void* UseQuadBuffer(VeUInt32 u32Size, VeUInt32* pu32Offset = NULL);
    
    static void Create();

protected:
#	if defined(VE_PLATFORM_MOBILE_SIM)
	HDC m_hDeviceContext;
	EGLDisplay m_eglDisplay;
	EGLConfig m_eglConfig;
	EGLSurface m_eglSurface;
	EGLContext m_eglContext;
#	elif defined(VE_PLATFORM_ANDROID)
	EGLDisplay m_eglDisplay;
	EGLConfig m_eglConfig;
	EGLSurface m_eglSurface;
	EGLContext m_eglContext;
#	endif

protected:
	virtual void CreateRenderObjects();

	virtual void CreateNodeDatas();

	void* m_pvQuadBuffer;
	VeUInt32 m_u32QuadPointer;

protected:
	VeUInt32 GetGLTopology(VeIAPrimitiveTopology::Topology eTopology);

	VeUInt32 GetGLIndexFormat(VeUInt32 u32Format);

	void ResetStateCache();

	VeVector<VeROVertexShaderGLES2*> m_kVertexShaderStack;
	VeROVertexShaderGLES2* m_pkCurVertexShader;

	VeVector<VeROPixelShaderGLES2*> m_kPixelShaderStack;
	VeROPixelShaderGLES2* m_pkCurPixelShader;

	struct BlendStateForSet
	{
		VeROBlendStateGLES2* m_pkBlendState;
		VeColor m_kFactor;
	};

	VeVector<BlendStateForSet> m_kBlendStateStack;
	BlendStateForSet m_kCurBlendState;
	VE_BOOL m_bBlendStateChange;

	struct DepthStencilStateForSet
	{
		VeRODepthStencilStateGLES2* m_pkDepthStencilState;
		VeUInt32 m_u32StencilRef;
	};

	VeVector<DepthStencilStateForSet> m_kDepthStencilStateStack;
	DepthStencilStateForSet m_kCurDepthStencilState;
	VE_BOOL m_bDepthStencilStateChange;

	VeVector<VeROInputLayoutGLES2*> m_kInputLayoutStack;
	VeROInputLayoutGLES2* m_pkCurInputLayout;

	VeVector<VeRORasterizeStateGLES2*> m_kRasterizeStateStack;
	VeRORasterizeStateGLES2* m_pkCurRasterizeState;

	VeVector<VeUInt32> m_kTopologyStack;

	VeVector<VeROBufferGLES2*> m_kIndexBufferStack;
	VeROBufferGLES2* m_pkCurIndexBuffer;

	struct VertexBufferForSet
	{
		VeROBufferGLES2* m_pkBuffer;
		VeUInt32 m_u32Stride;
		VeUInt32 m_u32Offset;
	};

	VeVector<VertexBufferForSet> m_akVertexBufferStack[VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	VertexBufferForSet m_akCurVertexBuffers[VE_GLES2_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
	VeUInt32 m_u32VertexBufferChangeMin;
	VeUInt32 m_u32VertexBufferChangeMax;

	VeVector<VeROBufferGLES2*> m_akVSCBufferStack[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	VeROBufferGLES2* m_apkCurVSCBuffers[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];

	VeVector<VeROSamplerStateGLES2*> m_akPSSamplerStack[VE_GLES2_PS_TEX_NUM];
	VeVector<VeROShaderResourceViewGLES2*> m_akPSShaderResourceViewStack[VE_GLES2_PS_TEX_NUM];
	VeROShaderResourceViewGLES2* m_apkCurPSShaderResourceViews[VE_GLES2_PS_TEX_NUM];

	VeVector<VeVector4D> m_kViewportStack;
	VeVector4D m_kCurViewport;

	struct Rect
	{
		VeUInt16 x, y, w, h;

		bool operator == (Rect& kRect)
		{
			return x == kRect.x && y == kRect.y && w == kRect.w && h == kRect.h;
		}

		bool operator != (Rect& kRect)
		{
			return (x != kRect.x || y != kRect.y || w != kRect.w || h != kRect.h);
		}
	};
	VeVector<Rect> m_kScissorRectStack;
	Rect m_kCurScissorRect;

	VeVector<VeRORenderTargetViewGLES2*> m_kRenderTargetViewStack;
	VeVector<VeRODepthStencilViewGLES2*> m_kDepthStencilViewStack;
	VeRORenderTargetViewGLES2* m_pkCurRenderTargetView;
	VeRODepthStencilViewGLES2* m_pkCurDepthStencilView;

	void GLInitGlobal();

	void GLTermGlobal();

	struct Description
	{
		VeString m_kVendor;
		VeString m_kRenderer;
		VeString m_kVersion;
		VeString m_kGLSLVersion;
		VeStringMap<VeUInt32> m_kExtensionMap;
		VeVector<VeFixedString> m_kExtensionArray;
	};

	Description m_kDescription;

	VeStringMap<VeUInt32> m_kFrameBufferObjectMap;
	VeVector<VeUInt32> m_kFrameBufferObjectArray;
	VeRenderObjectPtr m_spBackBuffer;

	struct Program
	{
		VeUInt32 m_u32Program;
		VeInt32 m_ai32VSSlot[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
		VeInt32 m_ai32PSSlot[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
		VeUInt32 m_u32VSTexture;
		VeUInt32 m_u32PSTexture;
	};
	VeStringMap<VeUInt32> m_kProgramMap;
	VeVector<Program> m_kProgramArray;

#	if defined(VE_PLATFORM_IOS)
	VeUInt32 m_u32BackFrameBuffer;
	VeUInt32 m_u32BackRenderBuffer;
#	endif

public:
	void GLCacheInit();

	void BindBuffer(VeUInt32 u32Target, VeUInt32 u32Buffer);

	void BindRenderBuffer(VeUInt32 u32Buffer);

	void BindFrameBuffer(VeUInt32 u32Buffer);

	void UseProgram(VeUInt32 u32Program);

	void EnableVertexAttribArray(VeUInt32 u32Count);

	void SetVertexAttribArray(VeUInt32 u32Index, VeUInt8 u8Size, VeUInt8 u8Normalized, VeUInt16 u16Type, VeUInt16 u16Stride, void* pvAlignedByteOffset);

	void SetAlphaToCoverageEnable(bool bEnable);

	void SetBlendEnable(bool bEnable);

	void SetBlendFunc(VeUInt16 u16SrcColor, VeUInt16 u16DstColor, VeUInt16 u16SrcAlpha, VeUInt16 u16DstAlpha);

	void SetBlendOp(VeUInt16 u16ColorOp, VeUInt16 u16AlphaOp);

	void SetWriteMask(VeUInt16 u16Mask);

	void SetDepthEnable(bool bEnable);

	void SetDepthWrite(bool bWrite);

	void SetDepthFunc(VeUInt16 u16Func);

	void SetStencilEnable(bool bEnable);

	void SetStencilWriteMask(VeUInt8 u8Mask);

	void SetStencilFunc(VeUInt16 u16FrontFunc, VeUInt16 u16BackFunc, VeUInt32 u32Ref, VeUInt8 u8ReadMask);

	void SetStencilFrontOp(VeUInt16 u16Fail, VeUInt16 u16DepthFail, VeUInt16 u16Pass);

	void SetStencilBackOp(VeUInt16 u16Fail, VeUInt16 u16DepthFail, VeUInt16 u16Pass);

	void SetCullEnable(bool bEnable);

	void SetDepthBiasEnable(bool bEnable);

	void SetMultisampleEnable(bool bEnable);

	void SetScissorEnable(bool bEnable);

	void SetCullFace(VeUInt16 u16Cull);

	void SetFrontFace(VeUInt16 u16Front);

	void SetPolyOffset(VeFloat32 f32Factor, VeFloat32 f32Units);

	void SetPSTexture(VeUInt32 u32Slot, VeUInt32 u32Texture);

	void SetVSTexture(VeUInt32 u32Slot, VeUInt32 u32Texture);

	void ClearColor(const VeColor& kColor);

	void ClearDepth(VeFloat32 f32Depth);

	void ClearStencil(VeUInt8 u8Stencil);

protected:
	friend class VeROTexture2DGLES2;
	enum Target
	{
		TARGET_ARRAY_BUFFER,
		TARGET_ELEMENT_ARRAY_BUFFER,
		TARGET_NUM
	};

	VeUInt32 m_au32BindBuffers[TARGET_NUM];
	VeUInt32 m_u32BindRenderBuffer;
	VeUInt32 m_u32BindFrameBuffer;
	VeUInt32 m_u32UsedProgram;
	VeInt32 m_ai32VSSlotLoc[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	VeInt32 m_ai32PSSlotLoc[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	bool m_abVSSlotNeedUpdate[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	bool m_abPSSlotNeedUpdate[VE_GLES2_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
	struct VertexAttrib
	{
		VertexAttrib();
		void* m_pvAlignedByteOffset;
		VeUInt16 m_u16Type;
		VeUInt16 m_u16Stride;
		VeUInt8 m_u8Size;
		VeUInt8 m_u8Normalized;
	};
	VeVector<VertexAttrib> m_kVertexAttribArrayState;

	bool m_bAlphaToCoverageEnable;
	bool m_bBlendEnable;
	VeUInt16 m_u16SrcBlend;
	VeUInt16 m_u16DstBlend;
	VeUInt16 m_u16BlendOp;
	VeUInt16 m_u16SrcBlendAlpha;
	VeUInt16 m_u16DstBlendAlpha;
	VeUInt16 m_u16BlendOpAlpha;
	VeUInt16 m_u16WriteMask;

	bool m_bDepthEnable;
	bool m_bDepthWrite;
	VeUInt16 m_u16DepthFunc;
	bool m_bStencilEnable;
	VeUInt8 m_u8StencilReadMask;
	VeUInt8 m_u8StencilWriteMask;
	VeUInt16 m_u16StencilFrontFailOp;
	VeUInt16 m_u16StencilFrontDepthFailOp;
	VeUInt16 m_u16StencilFrontPassOp;
	VeUInt16 m_u16StencilFrontFunc;
	VeUInt16 m_u16StencilBackFailOp;
	VeUInt16 m_u16StencilBackDepthFailOp;
	VeUInt16 m_u16StencilBackPassOp;
	VeUInt16 m_u16StencilBackFunc;
	VeUInt32 m_u32StencilRef;

	bool m_bCullEnable;
	bool m_bDepthBiasEnable;
	bool m_bMultisampleEnable;
	bool m_bScissorEnable;
	VeUInt16 m_u16CullFace;
	VeUInt16 m_u16FrontFace;
	VeFloat32 m_f32PolyFactor;
	VeFloat32 m_f32PolyUnits;

	VeUInt32 m_au32PSTexture[VE_GLES2_PS_TEX_NUM];
	VeUInt32 m_au32VSTexture[VE_GLES2_VS_TEX_NUM];

	VeInt32 m_i32MaxAnisotropy;

	VeColor m_kClearColor;
	VeFloat32 m_f32ClearDepth;
	VeUInt8 m_u8ClearStencil;

	bool m_bSupportDepthTexute;
	bool m_bSupportAnisotropic;
	bool m_bSupportMSAA;
	VeUInt8 m_u8MaxAASamples;

	void ActiveTexture(VeUInt32 u32Slot);
	VeUInt32 m_u32CurrentActiveTexture;

	bool m_bApiInit;

};

#endif
