////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderer.h
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeRenderer : public VeSingleton<VeRenderer>
{
public:
	enum API
	{
		API_D3D9 = 0x1,
		API_D3D11 = 0x2,
		API_OGL = 0x4,
		API_OGLES2 = 0x8,
		API_OGLES3 = 0x10,
		API_MASK = 0xFF
	};

	enum Capability
	{
		CAP_DEPTH_TEX,
		CAP_ANISOTROPIC,
		CAP_MULTI_SAMPLE,
		CAP_DRAW_INSTANCE
	};

	enum Shader
	{
		VERTEX_SHADER,
		HULL_SHADER,
		DOMAIN_SHADER,
		GEOMETRY_SHADER,
		PIXEL_SHADER,
		SHADER_MAX
	};

	enum Blend
	{
		BLEND_ZERO               = 1,
		BLEND_ONE                = 2,
		BLEND_SRC_COLOR          = 3,
		BLEND_INV_SRC_COLOR      = 4,
		BLEND_SRC_ALPHA          = 5,
		BLEND_INV_SRC_ALPHA      = 6,
		BLEND_DEST_ALPHA         = 7,
		BLEND_INV_DEST_ALPHA     = 8,
		BLEND_DEST_COLOR         = 9,
		BLEND_INV_DEST_COLOR     = 10,
		BLEND_SRC_ALPHA_SAT      = 11,
		BLEND_BLEND_FACTOR       = 14,
		BLEND_INV_BLEND_FACTOR   = 15,
		BLEND_SRC1_COLOR         = 16,
		BLEND_INV_SRC1_COLOR     = 17,
		BLEND_SRC1_ALPHA         = 18,
		BLEND_INV_SRC1_ALPHA     = 19 
	};

	enum BlendOp
	{
		BLEND_OP_ADD            = 1,
		BLEND_OP_SUBTRACT       = 2,
		BLEND_OP_REV_SUBTRACT   = 3,
		BLEND_OP_MIN            = 4,
		BLEND_OP_MAX            = 5 
	};

	enum ColorWriteEnable
	{
		COLOR_WRITE_ENABLE_NULL    = 0,
		COLOR_WRITE_ENABLE_RED     = 1,
		COLOR_WRITE_ENABLE_GREEN   = 2,
		COLOR_WRITE_ENABLE_BLUE    = 4,
		COLOR_WRITE_ENABLE_ALPHA   = 8,
		COLOR_WRITE_ENABLE_ALL     = (COLOR_WRITE_ENABLE_RED | COLOR_WRITE_ENABLE_GREEN |  COLOR_WRITE_ENABLE_BLUE | COLOR_WRITE_ENABLE_ALPHA) 
	};

	enum ComparisonFunc
	{
		COMPARISON_NEVER           = 1,
		COMPARISON_LESS            = 2,
		COMPARISON_EQUAL           = 3,
		COMPARISON_LESS_EQUAL      = 4,
		COMPARISON_GREATER         = 5,
		COMPARISON_NOT_EQUAL       = 6,
		COMPARISON_GREATER_EQUAL   = 7,
		COMPARISON_ALWAYS          = 8 
	};

	enum StencilOp
	{
		STENCIL_OP_KEEP       = 1,
		STENCIL_OP_ZERO       = 2,
		STENCIL_OP_REPLACE    = 3,
		STENCIL_OP_INCR_SAT   = 4,
		STENCIL_OP_DECR_SAT   = 5,
		STENCIL_OP_INVERT     = 6,
		STENCIL_OP_INCR       = 7,
		STENCIL_OP_DECR       = 8 
	};

	enum Semantic
	{
		SE_POSITION,
		SE_NORMAL,
		SE_COLOR,
		SE_TEXCOORD,
		SE_TANGENT,
		SE_BINORMAL,
		SE_BLENDINDICES,
		SE_BLENDWEIGHT,
		SEMANTIC_NUM
	};

	enum Format
	{
		FMT_UNKNOWN                      = 0,
		FMT_R32G32B32A32_TYPELESS        = 1,
		FMT_R32G32B32A32_FLOAT           = 2,
		FMT_R32G32B32A32_UINT            = 3,
		FMT_R32G32B32A32_SINT            = 4,
		FMT_R32G32B32_TYPELESS           = 5,
		FMT_R32G32B32_FLOAT              = 6,
		FMT_R32G32B32_UINT               = 7,
		FMT_R32G32B32_SINT               = 8,
		FMT_R16G16B16A16_TYPELESS        = 9,
		FMT_R16G16B16A16_FLOAT           = 10,
		FMT_R16G16B16A16_UNORM           = 11,
		FMT_R16G16B16A16_UINT            = 12,
		FMT_R16G16B16A16_SNORM           = 13,
		FMT_R16G16B16A16_SINT            = 14,
		FMT_R32G32_TYPELESS              = 15,
		FMT_R32G32_FLOAT                 = 16,
		FMT_R32G32_UINT                  = 17,
		FMT_R32G32_SINT                  = 18,
		FMT_R32G8X24_TYPELESS            = 19,
		FMT_D32_FLOAT_S8X24_UINT         = 20,
		FMT_R32_FLOAT_X8X24_TYPELESS     = 21,
		FMT_X32_TYPELESS_G8X24_UINT      = 22,
		FMT_R10G10B10A2_TYPELESS         = 23,
		FMT_R10G10B10A2_UNORM            = 24,
		FMT_R10G10B10A2_UINT             = 25,
		FMT_R11G11B10_FLOAT              = 26,
		FMT_R8G8B8A8_TYPELESS            = 27,
		FMT_R8G8B8A8_UNORM               = 28,
		FMT_R8G8B8A8_UNORM_SRGB          = 29,
		FMT_R8G8B8A8_UINT                = 30,
		FMT_R8G8B8A8_SNORM               = 31,
		FMT_R8G8B8A8_SINT                = 32,
		FMT_R16G16_TYPELESS              = 33,
		FMT_R16G16_FLOAT                 = 34,
		FMT_R16G16_UNORM                 = 35,
		FMT_R16G16_UINT                  = 36,
		FMT_R16G16_SNORM                 = 37,
		FMT_R16G16_SINT                  = 38,
		FMT_R32_TYPELESS                 = 39,
		FMT_D32_FLOAT                    = 40,
		FMT_R32_FLOAT                    = 41,
		FMT_R32_UINT                     = 42,
		FMT_R32_SINT                     = 43,
		FMT_R24G8_TYPELESS               = 44,
		FMT_D24_UNORM_S8_UINT            = 45,
		FMT_R24_UNORM_X8_TYPELESS        = 46,
		FMT_X24_TYPELESS_G8_UINT         = 47,
		FMT_R8G8_TYPELESS                = 48,
		FMT_R8G8_UNORM                   = 49,
		FMT_R8G8_UINT                    = 50,
		FMT_R8G8_SNORM                   = 51,
		FMT_R8G8_SINT                    = 52,
		FMT_R16_TYPELESS                 = 53,
		FMT_R16_FLOAT                    = 54,
		FMT_D16_UNORM                    = 55,
		FMT_R16_UNORM                    = 56,
		FMT_R16_UINT                     = 57,
		FMT_R16_SNORM                    = 58,
		FMT_R16_SINT                     = 59,
		FMT_R8_TYPELESS                  = 60,
		FMT_R8_UNORM                     = 61,
		FMT_R8_UINT                      = 62,
		FMT_R8_SNORM                     = 63,
		FMT_R8_SINT                      = 64,
		FMT_A8_UNORM                     = 65,
		FMT_R1_UNORM                     = 66,
		FMT_R9G9B9E5_SHAREDEXP           = 67,
		FMT_R8G8_B8G8_UNORM              = 68,
		FMT_G8R8_G8B8_UNORM              = 69,
		FMT_BC1_TYPELESS                 = 70,
		FMT_BC1_UNORM                    = 71,
		FMT_BC1_UNORM_SRGB               = 72,
		FMT_BC2_TYPELESS                 = 73,
		FMT_BC2_UNORM                    = 74,
		FMT_BC2_UNORM_SRGB               = 75,
		FMT_BC3_TYPELESS                 = 76,
		FMT_BC3_UNORM                    = 77,
		FMT_BC3_UNORM_SRGB               = 78,
		FMT_BC4_TYPELESS                 = 79,
		FMT_BC4_UNORM                    = 80,
		FMT_BC4_SNORM                    = 81,
		FMT_BC5_TYPELESS                 = 82,
		FMT_BC5_UNORM                    = 83,
		FMT_BC5_SNORM                    = 84,
		FMT_B5G6R5_UNORM                 = 85,
		FMT_B5G5R5A1_UNORM               = 86,
		FMT_B8G8R8A8_UNORM               = 87,
		FMT_B8G8R8X8_UNORM               = 88,
		FMT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
		FMT_B8G8R8A8_TYPELESS            = 90,
		FMT_B8G8R8A8_UNORM_SRGB          = 91,
		FMT_B8G8R8X8_TYPELESS            = 92,
		FMT_B8G8R8X8_UNORM_SRGB          = 93,
		FMT_BC6H_TYPELESS                = 94,
		FMT_BC6H_UF16                    = 95,
		FMT_BC6H_SF16                    = 96,
		FMT_BC7_TYPELESS                 = 97,
		FMT_BC7_UNORM                    = 98,
		FMT_BC7_UNORM_SRGB               = 99
	};

	enum InputClassification
	{
		PER_VERTEX_DATA     = 0,
		PER_INSTANCE_DATA   = 1
	};

	enum Usage
	{
		USAGE_DEFAULT     = 0,
		USAGE_IMMUTABLE   = 1,
		USAGE_DYNAMIC     = 2,
		USAGE_STAGING     = 3,
		USAGE_STREAM      = 4
	};

	enum BindFlag
	{
		BIND_VERTEX_BUFFER      = 0x1L,
		BIND_INDEX_BUFFER       = 0x2L,
		BIND_CONSTANT_BUFFER    = 0x4L,
		BIND_SHADER_RESOURCE    = 0x8L,
		BIND_STREAM_OUTPUT      = 0x10L,
		BIND_RENDER_TARGET      = 0x20L,
		BIND_DEPTH_STENCIL      = 0x40L,
		BIND_UNORDERED_ACCESS   = 0x80L
	};

	enum CpuAccessFlag
	{
		CPU_ACCESS_WRITE   = 0x1L,
		CPU_ACCESS_READ    = 0x2L
	};

	enum ResourceMiscFlag
	{
		RESOURCE_MISC_GENERATE_MIPS            = 0x1L,
		RESOURCE_MISC_SHARED                   = 0x2L,
		RESOURCE_MISC_TEXTURECUBE              = 0x4L,
		RESOURCE_MISC_DRAWINDIRECT_ARGS        = 0x10L,
		RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS   = 0x20L,
		RESOURCE_MISC_BUFFER_STRUCTURED        = 0x40L,
		RESOURCE_MISC_RESOURCE_CLAMP           = 0x80L,
		RESOURCE_MISC_SHARED_KEYEDMUTEX        = 0x100L,
		RESOURCE_MISC_GDI_COMPATIBLE           = 0x200L
	};

	enum FillMode
	{
		FILL_WIREFRAME   = 2,
		FILL_SOLID       = 3 
	};

	enum CullMode
	{
		CULL_NONE    = 1,
		CULL_FRONT   = 2,
		CULL_BACK    = 3 
	};

	enum DepthBiasMode
	{
		DBIAS_NONE
	};

	enum Filter
	{
		FILTER_MIN_MAG_MIP_POINT                            = 0,
		FILTER_MIN_MAG_POINT_MIP_LINEAR                     = 0x1,
		FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT               = 0x4,
		FILTER_MIN_POINT_MAG_MIP_LINEAR                     = 0x5,
		FILTER_MIN_LINEAR_MAG_MIP_POINT                     = 0x10,
		FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR              = 0x11,
		FILTER_MIN_MAG_LINEAR_MIP_POINT                     = 0x14,
		FILTER_MIN_MAG_MIP_LINEAR                           = 0x15,
		FILTER_ANISOTROPIC                                  = 0x55,
		FILTER_COMPARISON_MIN_MAG_MIP_POINT                 = 0x80,
		FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR          = 0x81,
		FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT    = 0x84,
		FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR          = 0x85,
		FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT          = 0x90,
		FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR   = 0x91,
		FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT          = 0x94,
		FILTER_COMPARISON_MIN_MAG_MIP_LINEAR                = 0x95,
		FILTER_COMPARISON_ANISOTROPIC                       = 0xd5,
	};

	enum TextureAddressMode 
	{
		TEXTURE_ADDRESS_WRAP          = 1,
		TEXTURE_ADDRESS_MIRROR        = 2,
		TEXTURE_ADDRESS_CLAMP         = 3,
		TEXTURE_ADDRESS_BORDER        = 4,
		TEXTURE_ADDRESS_MIRROR_ONCE   = 5 
	};

	enum Map
	{
		MAP_READ                 = 1,
		MAP_WRITE                = 2,
		MAP_READ_WRITE           = 3,
		MAP_WRITE_DISCARD        = 4,
		MAP_WRITE_NO_OVERWRITE   = 5 
	};

	struct MappedSubresource
	{
		void* m_pvData;
		VeUInt32 m_u32RowPitch;
		VeUInt32 m_u32DepthPitch;
	};

	union MapWriteRange
	{
		struct
		{
			VeUInt32 m_u32Offset;
			VeUInt32 m_u32Size;
		};
		VeUInt64 m_u64Range;
	};

	struct SpriteFrame
	{
		VeResource* m_pkResource;
		VeUInt32 m_u32Index;
	};

	struct RenderTarget
	{
		VeROTexture2DPtr m_spTex;
		VeROBufferPtr m_spBuf;
		Format m_eFormat;
		VeUInt16 m_u16Width;
		VeUInt16 m_u16Height;
	};

	virtual ~VeRenderer();

	virtual API GetAPI() = 0;

	virtual VeUInt32 CheckCapability(Capability eCap) = 0;

	virtual void Init() = 0;

	virtual void Term() = 0;

#ifdef VE_ENABLE_DEVICE_LOST

	typedef VeEvent<void> RestoreEvent;
	typedef VeAbstractDelegate<void> RestoreDelegate;

	virtual void AddRestoreDelegate(RestoreDelegate& kDelegate) = 0;

	virtual void Lost() = 0;

	virtual void Restore() = 0;

#endif

	virtual void Render() = 0;

	virtual void Present() = 0;

	virtual void LoadInitResource();

	virtual void CreateRenderObjects() {}

	virtual void CreateNodeDatas() {}

	virtual void CreateDefaultData();

#if defined(VE_PLATFORM_PC)

	/*struct Display
	{
		typedef VeStringParser::WinStyle WinStyle;
		typedef VeStringParser::BackBufferFormat Format;
		WinStyle m_eWinStyle;
		VeUInt32 m_u32Width;
		VeUInt32 m_u32Height;
		Format m_eFormat;
		VE_BOOL m_bFullscreen;
		VeUInt32 m_u32Output;
		VeUInt32 m_u32RefreshRate;
	};*/

	virtual void SetFullScreen(bool bEnable) = 0;

	//virtual void SetDisplay(Display& kDisplay) = 0;

	virtual void ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height) = 0;

	virtual void ResizeBuffer(VeUInt32 u32Width, VeUInt32 u32Height) = 0;

	virtual void OnActive() = 0;

	virtual void OnInactive() = 0;

#elif defined(VE_PLATFORM_MOBILE_SIM)

	virtual void ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height) = 0;

#endif

	virtual void GetMatrixPerspectiveFov(VeFloat32* pf32OutMat4x4, VeFloat32 fov, VeFloat32 znear, VeFloat32 zfar) = 0;

	VE_INLINE VeUInt32 GetWidth();

	VE_INLINE VeUInt32 GetHeight();

	VE_INLINE VeFloat32 GetWidthF();

	VE_INLINE VeFloat32 GetHeightF();

	VE_INLINE VeFloat32 GetInvWidthF();

	VE_INLINE VeFloat32 GetInvHeightF();

	const VeRenderObjectPtr& GetRenderObject(VeRenderObject::Type eType, const VeChar8* pcName);

	template <typename T>
	void GetRenderObject(const VeChar8* pcName, T& spObj)
	{
		VeRenderObjectPtr spRenderObj = GetRenderObject(T::TypeClass::ROType(), pcName);
		spObj = (T)spRenderObj;
	}

	const VeRenderNodeDataPtr& GetRenderNodeData(const VeChar8* pcName);

	virtual const VeChar8* GetShaderName() = 0;

	virtual const VeChar8* GetShaderProfile() = 0;

	virtual VeUInt32 GetMultisampleLevelCount();

	virtual void EnumMultisampleLevel(VeUInt32 u32Index, VeUInt32& u32Count, VeUInt32& u32Quality);

	virtual void CreateVertexShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROVertexShaderPtr* pspShader = NULL) {}

	virtual void CreatePixelShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROPixelShaderPtr* pspShader = NULL) {}

	virtual void CreateBlendState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBlendStatePtr* pspBlendState = NULL) {}

	virtual void CreateDepthStencilState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRODepthStencilStatePtr* pspDepthStencilState = NULL) {}

	virtual void CreateInputLayout(const VeChar8* pcName, VeBinaryIStream& kStream, VeROInputLayoutPtr* pspLayout = NULL) {}

	virtual void CreateRasterizerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRORasterizeStatePtr* pspRasterizeState = NULL) {}

	virtual void CreateBuffer(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBufferPtr* pspBuffer = NULL) {}

	virtual void CreateSamplerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROSamplerStatePtr* pspSamplerState = NULL) {}

	virtual void CreateTexture2D(const VeChar8* pcName, VeBinaryIStream& kStream, VeROTexture2DPtr* pspTexture = NULL) {}

	virtual bool CreateProcessByType(VeRenderProcess::Type eType, const VeChar8* pcName, VeBinaryIStream& kStream, VeRenderProcessPtr* pspProcess = NULL);

	bool CreateRenderNodeData(const VeChar8* pcName, VeBinaryIStream& kStream, VeRenderNodeDataPtr* pspNodeData = NULL);

	VeRenderTick* CreateRenderTick(VeBinaryIStream& kStream);

	VeRenderCall* CreateRenderCall(VeBinaryIStream& kStream);

	void CreateRenderObject(VeBinaryIStream& kStream, VeRenderObjectPtr* pspRenderObject = NULL);

	void DestroyRenderObject(VeRenderObject::Type eType, const VeChar8* pcName);

	virtual bool MapRes(const VeRenderObjectPtr& spObject, VeUInt32 u32SubResource, Map eType, VE_BOOL bSync, MappedSubresource* pkMapped);

	virtual void UnMapRes(const VeRenderObjectPtr& spObject, VeUInt32 u32SubResource, MapWriteRange kRange);

	virtual void Render(VeRenderNode* pkNode) = 0;

	virtual void Process(const VeRenderProcessPtr& spProcess) = 0;

	VE_INLINE bool IsInited();

	static void CreateRenderer(VeUInt32 u32Flag);

	void GetSpriteFrame(const VeChar8* pcName, SpriteFrame& kFrame);

	const VeChar8* CreateRenderTarget2D(Format eFormat, VeUInt16 u16Width, VeUInt16 u16Height);

	void DestoryRenderTarget2D(const VeChar8* pcName);

	const RenderTarget* GetRenderTarget2D(const VeChar8* pcName);

private:
	VeUInt32 m_u32Width;
	VeUInt32 m_u32Height;
	VeFloat32 m_f32Width;
	VeFloat32 m_f32Height;
	VeFloat32 m_f32InvWidth;
	VeFloat32 m_f32InvHeight;
	
protected:
	friend class VeMaterial;

	VeRenderer();

	void SetScreenSize(VeUInt32 u32Width, VeUInt32 u32Height);

	void AddObject(const VeRenderObjectPtr& spObject);

	void DelObject(const VeRenderObjectPtr& spObject);

	void AddNodeData(const VeRenderNodeDataPtr& spNodeData);

	void DelNodeData(const VeRenderNodeDataPtr& spNodeData);

	void AddProcess(const VeRenderProcessPtr& spProcess);

	void DelProcess(const VeRenderProcessPtr& spProcess);

	VeStringMap<VeUInt32> m_akObjectMap[VeRenderObject::TYPE_MAX];
	VeVector<VeRenderObjectPtr> m_kObjectArray;

	VeStringMap<VeUInt32> m_kProcessMap;
	VeVector<VeRenderProcessPtr> m_kProcessArray;

	VeStringMap<VeUInt32> m_kNodeDataMap;
	VeVector<VeRenderNodeDataPtr> m_kNodeDataArray;

	VeUInt32 m_u32ObjectIndex;

	bool m_bInited;
	VeByte m_acAlign[3];

	VeStringMap<VeRenderObject::Type> m_kRenderObjectTypeParser;
	VeStringMap<Blend> m_kBlendParser;
	VeStringMap<BlendOp> m_kBlendOpParser;
	VeStringMap<ColorWriteEnable> m_kColorWriteParser;
	VeStringMap<ComparisonFunc> m_kComparisonFuncParser;
	VeStringMap<StencilOp> m_kStencilOpParser;
	VeStringMap<Semantic> m_kSemanticParser;
	VeStringMap<Format> m_kFormatParser;
	VeStringMap<InputClassification> m_kInputClassParser;
	VeStringMap<FillMode> m_kFillModeParser;
	VeStringMap<CullMode> m_kCullModeParser;
	VeStringMap<DepthBiasMode> m_kDepthBiasModeParser;
	VeStringMap<Filter> m_kFilterParser;
	VeStringMap<TextureAddressMode> m_kTexAddressModeParser;
	VeStringMap<VeRenderTick::Type> m_kRenderTickTypeParser;
	VeStringMap<VeIAPrimitiveTopology::Topology> m_kPrimitiveTopologyParser;

	friend class TextureAtlas;
	VeVector<SpriteFrame> m_kSpriteFrameArray;
	VeStringMap<VeUInt32> m_kSpriteFrameMap;

	VeVector<RenderTarget> m_kRenderTargetArray;
	VeStringMap<VeUInt32> m_kRenderTargetMap;

};

#define g_pRenderer VeRenderer::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeRenderer.inl"
#endif
