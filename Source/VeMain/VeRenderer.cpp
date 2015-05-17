////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderer.cpp
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeRendererGL.h"
#include "_VeRendererGLES2.h"
#include "_VeRendererD3D11.h"
#ifdef VE_NO_INLINE
#	include "VeRenderer.inl"
#endif

//--------------------------------------------------------------------------
VeRenderer::VeRenderer()
	: m_u32Width(0), m_u32Height(0), m_f32Width(0), m_f32Height(0)
	, m_f32InvWidth(0), m_f32InvHeight(0), m_u32ObjectIndex(0)
	, m_bInited(false)
{
	g_pResourceManager->SetResourceCreateFunction(VeResource::VERTEX_SHADER,
		VeShaderResource::CreateVertexShaderResource);
	g_pResourceManager->SetResourceCreateFunction(VeResource::PIXEL_SHADER,
		VeShaderResource::CreatePixelShaderResource);
	g_pResourceManager->SetResourceCreateFunction(VeResource::TEXTURE,
		VeTextureResource::CreateResource);
	g_pResourceManager->SetResourceCreateFunction(VeResource::TEXTURE_ATLAS,
		TextureAtlas::CreateResource);
	g_pResourceManager->SetResourceCreateFunction(VeResource::FONT,
		VeFont::CreateResource);

	m_kRenderObjectTypeParser["blendstate"] = VeRenderObject::TYPE_BLEND_STATE;
	m_kRenderObjectTypeParser["counter"] = VeRenderObject::TYPE_COUNTER;
	m_kRenderObjectTypeParser["depthstencilstate"] = VeRenderObject::TYPE_DEPTH_STENCIL_STATE;
	m_kRenderObjectTypeParser["inputlayout"] = VeRenderObject::TYPE_INPUT_LAYOUT;
	m_kRenderObjectTypeParser["predicate"] = VeRenderObject::TYPE_PREDICATE;
	m_kRenderObjectTypeParser["query"] = VeRenderObject::TYPE_QUERY;
	m_kRenderObjectTypeParser["rasterizerstate"] = VeRenderObject::TYPE_RASTERIZER_STATE;
	m_kRenderObjectTypeParser["samplerstate"] = VeRenderObject::TYPE_SAMPLER_STATE;
	m_kRenderObjectTypeParser["buffer"] = VeRenderObject::TYPE_BUFFER;
	m_kRenderObjectTypeParser["depthstencilview"] = VeRenderObject::TYPE_DEPTH_STENCIL_VIEW;
	m_kRenderObjectTypeParser["rendertargetview"] = VeRenderObject::TYPE_RENDER_TARGET_VIEW;
	m_kRenderObjectTypeParser["shaderresourceview"] = VeRenderObject::TYPE_SHADER_RESOURCE_VIEW;
	m_kRenderObjectTypeParser["texture1d"] = VeRenderObject::TYPE_TEXTURE_1D;
	m_kRenderObjectTypeParser["texture2d"] = VeRenderObject::TYPE_TEXTURE_2D;
	m_kRenderObjectTypeParser["texture3d"] = VeRenderObject::TYPE_TEXTURE_3D;
	m_kRenderObjectTypeParser["unorderedaccessview"] = VeRenderObject::TYPE_UNORDERED_ACCESS_VIEW;
	m_kRenderObjectTypeParser["classlinkage"] = VeRenderObject::TYPE_CLASS_LINKAGE;
	m_kRenderObjectTypeParser["computeshader"] = VeRenderObject::TYPE_COMPUTE_SHADER;
	m_kRenderObjectTypeParser["domainshader"] = VeRenderObject::TYPE_DOMAIN_SHADER;
	m_kRenderObjectTypeParser["geometryshader"] = VeRenderObject::TYPE_GEOMETRY_SHADER;
	m_kRenderObjectTypeParser["hullshader"] = VeRenderObject::TYPE_HULL_SHADER;
	m_kRenderObjectTypeParser["pixelshader"] = VeRenderObject::TYPE_PIXEL_SHADER;
	m_kRenderObjectTypeParser["vertexshader"] = VeRenderObject::TYPE_VERTEX_SHADER;

	m_kBlendParser["zero"] = BLEND_ZERO;
	m_kBlendParser["one"] = BLEND_ONE;
	m_kBlendParser["src_color"] = BLEND_SRC_COLOR;
	m_kBlendParser["inv_src_color"] = BLEND_INV_SRC_COLOR;
	m_kBlendParser["src_alpha"] = BLEND_SRC_ALPHA;
	m_kBlendParser["inv_src_alpha"] = BLEND_INV_SRC_ALPHA;
	m_kBlendParser["dst_alpha"] = BLEND_DEST_ALPHA;
	m_kBlendParser["inv_dst_alpha"] = BLEND_INV_DEST_ALPHA;
	m_kBlendParser["dst_color"] = BLEND_DEST_COLOR;
	m_kBlendParser["inv_dst_color"] = BLEND_INV_DEST_COLOR;
	m_kBlendParser["src_alpha_sat"] = BLEND_SRC_ALPHA_SAT;
	m_kBlendParser["blend_factor"] = BLEND_BLEND_FACTOR;
	m_kBlendParser["inv_blend_factor"] = BLEND_INV_BLEND_FACTOR;
	m_kBlendParser["src1_color"] = BLEND_SRC1_COLOR;
	m_kBlendParser["inv_src1_color"] = BLEND_INV_SRC1_COLOR;
	m_kBlendParser["src1_alpha"] = BLEND_SRC1_ALPHA;
	m_kBlendParser["inv_src1_alpha"] = BLEND_INV_SRC1_ALPHA;

	m_kBlendOpParser["add"] = BLEND_OP_ADD;
	m_kBlendOpParser["sub"] = BLEND_OP_SUBTRACT;
	m_kBlendOpParser["rev_sub"] = BLEND_OP_REV_SUBTRACT;
	m_kBlendOpParser["min"] = BLEND_OP_MIN;
	m_kBlendOpParser["max"] = BLEND_OP_MAX;

	m_kColorWriteParser["r"] = COLOR_WRITE_ENABLE_RED;
	m_kColorWriteParser["g"] = COLOR_WRITE_ENABLE_GREEN;
	m_kColorWriteParser["b"] = COLOR_WRITE_ENABLE_BLUE;
	m_kColorWriteParser["a"] = COLOR_WRITE_ENABLE_ALPHA;
	m_kColorWriteParser["all"] = COLOR_WRITE_ENABLE_ALL;

	m_kComparisonFuncParser["never"] = COMPARISON_NEVER;
	m_kComparisonFuncParser["less"] = COMPARISON_LESS;
	m_kComparisonFuncParser["equal"] = COMPARISON_EQUAL;
	m_kComparisonFuncParser["less_equal"] = COMPARISON_LESS_EQUAL;
	m_kComparisonFuncParser["greater"] = COMPARISON_GREATER;
	m_kComparisonFuncParser["not_equal"] = COMPARISON_NOT_EQUAL;
	m_kComparisonFuncParser["greater_equal"] = COMPARISON_GREATER_EQUAL;
	m_kComparisonFuncParser["always"] = COMPARISON_ALWAYS;

	m_kStencilOpParser["keep"] = STENCIL_OP_KEEP;
	m_kStencilOpParser["zero"] = STENCIL_OP_ZERO;
	m_kStencilOpParser["replace"] = STENCIL_OP_REPLACE;
	m_kStencilOpParser["inc_sat"] = STENCIL_OP_INCR_SAT;
	m_kStencilOpParser["dec_sat"] = STENCIL_OP_DECR_SAT;
	m_kStencilOpParser["invert"] = STENCIL_OP_INVERT;
	m_kStencilOpParser["inc"] = STENCIL_OP_INCR;
	m_kStencilOpParser["dec"] = STENCIL_OP_DECR;

	m_kSemanticParser["position"] = SE_POSITION;
	m_kSemanticParser["normal"] = SE_NORMAL;
	m_kSemanticParser["color"] = SE_COLOR;
	m_kSemanticParser["texcoord"] = SE_TEXCOORD;
	m_kSemanticParser["tangent"] = SE_TANGENT;
	m_kSemanticParser["binormal"] = SE_BINORMAL;
	m_kSemanticParser["blendindices"] = SE_BLENDINDICES;
	m_kSemanticParser["blendweight"] = SE_BLENDWEIGHT;
	m_kSemanticParser["pos"] = SE_POSITION;
	m_kSemanticParser["nor"] = SE_NORMAL;
	m_kSemanticParser["col"] = SE_COLOR;
	m_kSemanticParser["tex"] = SE_TEXCOORD;
	m_kSemanticParser["tan"] = SE_TANGENT;
	m_kSemanticParser["bin"] = SE_BINORMAL;

	m_kFormatParser["unknown"] = FMT_UNKNOWN;
	m_kFormatParser["r32g32b32a32_typeless"] = FMT_R32G32B32A32_TYPELESS;
	m_kFormatParser["r32g32b32a32_float"] = FMT_R32G32B32A32_FLOAT;
	m_kFormatParser["r32g32b32a32_uint"] = FMT_R32G32B32A32_UINT;
	m_kFormatParser["r32g32b32a32_sint"] = FMT_R32G32B32A32_SINT;
	m_kFormatParser["r32g32b32_typeless"] = FMT_R32G32B32_TYPELESS;
	m_kFormatParser["r32g32b32_float"] = FMT_R32G32B32_FLOAT;
	m_kFormatParser["r32g32b32_uint"] = FMT_R32G32B32_UINT;
	m_kFormatParser["r32g32b32_sint"] = FMT_R32G32B32_SINT;
	m_kFormatParser["r16g16b16a16_typeless"] = FMT_R16G16B16A16_TYPELESS;
	m_kFormatParser["r16g16b16a16_float"] = FMT_R16G16B16A16_FLOAT;
	m_kFormatParser["r16g16b16a16_unorm"] = FMT_R16G16B16A16_UNORM;
	m_kFormatParser["r16g16b16a16_uint"] = FMT_R16G16B16A16_UINT;
	m_kFormatParser["r16g16b16a16_snorm"] = FMT_R16G16B16A16_SNORM;
	m_kFormatParser["r16g16b16a16_sint"] = FMT_R16G16B16A16_SINT;
	m_kFormatParser["r32g32_typeless"] = FMT_R32G32_TYPELESS;
	m_kFormatParser["r32g32_float"] = FMT_R32G32_FLOAT;
	m_kFormatParser["r32g32_uint"] = FMT_R32G32_UINT;
	m_kFormatParser["r32g32_sint"] = FMT_R32G32_SINT;
	m_kFormatParser["r32g8x24_typeless"] = FMT_R32G8X24_TYPELESS;
	m_kFormatParser["d32_float_s8x24_uint"] = FMT_D32_FLOAT_S8X24_UINT;
	m_kFormatParser["r32_float_x8x24_typeless"] = FMT_R32_FLOAT_X8X24_TYPELESS;
	m_kFormatParser["x32_typeless_g8x24_uint"] = FMT_X32_TYPELESS_G8X24_UINT;
	m_kFormatParser["r10g10b10a2_typeless"] = FMT_R10G10B10A2_TYPELESS;
	m_kFormatParser["r10g10b10a2_unorm"] = FMT_R10G10B10A2_UNORM;
	m_kFormatParser["r10g10b10a2_uint"] = FMT_R10G10B10A2_UINT;
	m_kFormatParser["r11g11b10_float"] = FMT_R11G11B10_FLOAT;
	m_kFormatParser["r8g8b8a8_typeless"] = FMT_R8G8B8A8_TYPELESS;
	m_kFormatParser["r8g8b8a8_unorm"] = FMT_R8G8B8A8_UNORM;
	m_kFormatParser["r8g8b8a8_unorm_srgb"] = FMT_R8G8B8A8_UNORM_SRGB;
	m_kFormatParser["r8g8b8a8_uint"] = FMT_R8G8B8A8_UINT;
	m_kFormatParser["r8g8b8a8_snorm"] = FMT_R8G8B8A8_SNORM;
	m_kFormatParser["r8g8b8a8_sint"] = FMT_R8G8B8A8_SINT;
	m_kFormatParser["r16g16_typeless"] = FMT_R16G16_TYPELESS;
	m_kFormatParser["r16g16_float"] = FMT_R16G16_FLOAT;
	m_kFormatParser["r16g16_unorm"] = FMT_R16G16_UNORM;
	m_kFormatParser["r16g16_uint"] = FMT_R16G16_UINT;
	m_kFormatParser["r16g16_snorm"] = FMT_R16G16_SNORM;
	m_kFormatParser["r16g16_sint"] = FMT_R16G16_SINT;
	m_kFormatParser["r32_typeless"] = FMT_R32_TYPELESS;
	m_kFormatParser["d32_float"] = FMT_D32_FLOAT;
	m_kFormatParser["r32_float"] = FMT_R32_FLOAT;
	m_kFormatParser["r32_uint"] = FMT_R32_UINT;
	m_kFormatParser["r32_sint"] = FMT_R32_SINT;
	m_kFormatParser["r24g8_typeless"] = FMT_R24G8_TYPELESS;
	m_kFormatParser["d24_unorm_s8_uint"] = FMT_D24_UNORM_S8_UINT;
	m_kFormatParser["r24_unorm_x8_typeless"] = FMT_R24_UNORM_X8_TYPELESS;
	m_kFormatParser["x24_typeless_g8_uint"] = FMT_X24_TYPELESS_G8_UINT;
	m_kFormatParser["r8g8_typeless"] = FMT_R8G8_TYPELESS;
	m_kFormatParser["r8g8_unorm"] = FMT_R8G8_UNORM;
	m_kFormatParser["r8g8_uint"] = FMT_R8G8_UINT;
	m_kFormatParser["r8g8_snorm"] = FMT_R8G8_SNORM;
	m_kFormatParser["r8g8_sint"] = FMT_R8G8_SINT;
	m_kFormatParser["r16_typeless"] = FMT_R16_TYPELESS;
	m_kFormatParser["r16_float"] = FMT_R16_FLOAT;
	m_kFormatParser["d16_unorm"] = FMT_D16_UNORM;
	m_kFormatParser["r16_unorm"] = FMT_R16_UNORM;
	m_kFormatParser["r16_uint"] = FMT_R16_UINT;
	m_kFormatParser["r16_snorm"] = FMT_R16_SNORM;
	m_kFormatParser["r16_sint"] = FMT_R16_SINT;
	m_kFormatParser["r8_typeless"] = FMT_R8_TYPELESS;
	m_kFormatParser["r8_unorm"] = FMT_R8_UNORM;
	m_kFormatParser["r8_uint"] = FMT_R8_UINT;
	m_kFormatParser["r8_snorm"] = FMT_R8_SNORM;
	m_kFormatParser["r8_sint"] = FMT_R8_SINT;
	m_kFormatParser["a8_unorm"] = FMT_A8_UNORM;
	m_kFormatParser["r1_unorm"] = FMT_R1_UNORM;
	m_kFormatParser["r9g9b9e5_sharedexp"] = FMT_R9G9B9E5_SHAREDEXP;
	m_kFormatParser["r8g8_b8g8_unorm"] = FMT_R8G8_B8G8_UNORM;
	m_kFormatParser["g8r8_g8b8_unorm"] = FMT_G8R8_G8B8_UNORM;
	m_kFormatParser["bc1_typeless"] = FMT_BC1_TYPELESS;
	m_kFormatParser["bc1_unorm"] = FMT_BC1_UNORM;
	m_kFormatParser["bc1_unorm_srgb"] = FMT_BC1_UNORM_SRGB;
	m_kFormatParser["bc2_typeless"] = FMT_BC2_TYPELESS;
	m_kFormatParser["bc2_unorm"] = FMT_BC2_UNORM;
	m_kFormatParser["bc2_unorm_srgb"] = FMT_BC2_UNORM_SRGB;
	m_kFormatParser["bc3_typeless"] = FMT_BC3_TYPELESS;
	m_kFormatParser["bc3_unorm"] = FMT_BC3_UNORM;
	m_kFormatParser["bc3_unorm_srgb"] = FMT_BC3_UNORM_SRGB;
	m_kFormatParser["bc4_typeless"] = FMT_BC4_TYPELESS;
	m_kFormatParser["bc4_unorm"] = FMT_BC4_UNORM;
	m_kFormatParser["bc4_snorm"] = FMT_BC4_SNORM;
	m_kFormatParser["bc5_typeless"] = FMT_BC5_TYPELESS;
	m_kFormatParser["bc5_unorm"] = FMT_BC5_UNORM;
	m_kFormatParser["bc5_snorm"] = FMT_BC5_SNORM;
	m_kFormatParser["b5g6r5_unorm"] = FMT_B5G6R5_UNORM;
	m_kFormatParser["b5g5r5a1_unorm"] = FMT_B5G5R5A1_UNORM;
	m_kFormatParser["b8g8r8a8_unorm"] = FMT_B8G8R8A8_UNORM;
	m_kFormatParser["b8g8r8x8_unorm"] = FMT_B8G8R8X8_UNORM;
	m_kFormatParser["r10g10b10_xr_bias_a2_unorm"] = FMT_R10G10B10_XR_BIAS_A2_UNORM;
	m_kFormatParser["b8g8r8a8_typeless"] = FMT_B8G8R8A8_TYPELESS;
	m_kFormatParser["b8g8r8a8_unorm_srgb"] = FMT_B8G8R8A8_UNORM_SRGB;
	m_kFormatParser["b8g8r8x8_typeless"] = FMT_B8G8R8X8_TYPELESS;
	m_kFormatParser["b8g8r8x8_unorm_srgb"] = FMT_B8G8R8X8_UNORM_SRGB;
	m_kFormatParser["bc6h_typeless"] = FMT_BC6H_TYPELESS;
	m_kFormatParser["bc6h_uf16"] = FMT_BC6H_UF16;
	m_kFormatParser["bc6h_sf16"] = FMT_BC6H_SF16;
	m_kFormatParser["bc7_typeless"] = FMT_BC7_TYPELESS;
	m_kFormatParser["bc7_unorm"] = FMT_BC7_UNORM;
	m_kFormatParser["bc7_unorm_srgb"] = FMT_BC7_UNORM_SRGB;

	m_kInputClassParser["vertex_data"] = PER_VERTEX_DATA;
	m_kInputClassParser["instance_data"] = PER_INSTANCE_DATA;

	m_kFillModeParser["wireframe"] = FILL_WIREFRAME;
	m_kFillModeParser["solid"] = FILL_SOLID;

	m_kCullModeParser["none"] = CULL_NONE;
	m_kCullModeParser["front"] = CULL_FRONT;
	m_kCullModeParser["back"] = CULL_BACK;

	m_kDepthBiasModeParser["none"] = DBIAS_NONE;

	m_kFilterParser["min_mag_mip_point"] = FILTER_MIN_MAG_MIP_POINT;
	m_kFilterParser["min_mag_point_mip_linear"] = FILTER_MIN_MAG_POINT_MIP_LINEAR;
	m_kFilterParser["min_point_mag_linear_mip_point"] = FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
	m_kFilterParser["min_point_mag_mip_linear"] = FILTER_MIN_POINT_MAG_MIP_LINEAR;
	m_kFilterParser["min_linear_mag_mip_point"] = FILTER_MIN_LINEAR_MAG_MIP_POINT;
	m_kFilterParser["min_linear_mag_point_mip_linear"] = FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	m_kFilterParser["min_mag_linear_mip_point"] = FILTER_MIN_MAG_LINEAR_MIP_POINT;
	m_kFilterParser["min_mag_mip_linear"] = FILTER_MIN_MAG_MIP_LINEAR;
	m_kFilterParser["anisotropic"] = FILTER_ANISOTROPIC;
	m_kFilterParser["comparison_min_mag_mip_point"] = FILTER_COMPARISON_MIN_MAG_MIP_POINT;
	m_kFilterParser["comparison_min_mag_point_mip_linear"] = FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR;
	m_kFilterParser["comparison_min_point_mag_linear_mip_point"] = FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT;
	m_kFilterParser["comparison_min_point_mag_mip_linear"] = FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR;
	m_kFilterParser["comparison_min_linear_mag_mip_point"] = FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
	m_kFilterParser["comparison_min_linear_mag_point_mip_linear"] = FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	m_kFilterParser["comparison_min_mag_linear_mip_point"] = FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	m_kFilterParser["comparison_min_mag_mip_linear"] = FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	m_kFilterParser["comparison_anisotropic"] = FILTER_COMPARISON_ANISOTROPIC;

	m_kTexAddressModeParser["wrap"] = TEXTURE_ADDRESS_WRAP;
	m_kTexAddressModeParser["mirror"] = TEXTURE_ADDRESS_MIRROR;
	m_kTexAddressModeParser["clamp"] = TEXTURE_ADDRESS_CLAMP;
	m_kTexAddressModeParser["border"] = TEXTURE_ADDRESS_BORDER;
	m_kTexAddressModeParser["mirror_once"] = TEXTURE_ADDRESS_MIRROR_ONCE;

	m_kRenderTickTypeParser["iaindexbuffer"] = VeRenderTick::IA_INDEX_BUFFER;
	m_kRenderTickTypeParser["iainputlayout"] = VeRenderTick::IA_INPUT_LAYOUT;
	m_kRenderTickTypeParser["iaprimitivetopology"] = VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	m_kRenderTickTypeParser["iavertexbuffer"] = VeRenderTick::IA_VERTEX_BUFFER;
	m_kRenderTickTypeParser["vscbuffer"] = VeRenderTick::VS_CONSTANT_BUFFER;
	m_kRenderTickTypeParser["vssampler"] = VeRenderTick::VS_SAMPLER;
	m_kRenderTickTypeParser["vsshader"] = VeRenderTick::VS_SHADER;
	m_kRenderTickTypeParser["vsshaderres"] = VeRenderTick::VS_SHADER_RESOURCE;
	m_kRenderTickTypeParser["hscbuffer"] = VeRenderTick::HS_CONSTANT_BUFFER;
	m_kRenderTickTypeParser["hssampler"] = VeRenderTick::HS_SAMPLER;
	m_kRenderTickTypeParser["hsshader"] = VeRenderTick::HS_SHADER;
	m_kRenderTickTypeParser["hsshaderres"] = VeRenderTick::HS_SHADER_RESOURCE;
	m_kRenderTickTypeParser["dscbuffer"] = VeRenderTick::DS_CONSTANT_BUFFER;
	m_kRenderTickTypeParser["dssampler"] = VeRenderTick::DS_SAMPLER;
	m_kRenderTickTypeParser["dsshader"] = VeRenderTick::DS_SHADER;
	m_kRenderTickTypeParser["dsshaderres"] = VeRenderTick::DS_SHADER_RESOURCE;
	m_kRenderTickTypeParser["gscbuffer"] = VeRenderTick::GS_CONSTANT_BUFFER;
	m_kRenderTickTypeParser["gssampler"] = VeRenderTick::GS_SAMPLER;
	m_kRenderTickTypeParser["gsshader"] = VeRenderTick::GS_SHADER;
	m_kRenderTickTypeParser["gsshaderres"] = VeRenderTick::GS_SHADER_RESOURCE;
	m_kRenderTickTypeParser["sotarget"] = VeRenderTick::SO_TARGET;
	m_kRenderTickTypeParser["rsscissor"] = VeRenderTick::RS_SCISSOR_RECT;
	m_kRenderTickTypeParser["rsstate"] = VeRenderTick::RS_STATE;
	m_kRenderTickTypeParser["rsviewport"] = VeRenderTick::RS_VIEWPORT;
	m_kRenderTickTypeParser["pscbuffer"] = VeRenderTick::PS_CONSTANT_BUFFER;
	m_kRenderTickTypeParser["pssampler"] = VeRenderTick::PS_SAMPLER;
	m_kRenderTickTypeParser["psshader"] = VeRenderTick::PS_SHADER;
	m_kRenderTickTypeParser["psshaderres"] = VeRenderTick::PS_SHADER_RESOURCE;
	m_kRenderTickTypeParser["omblendstate"] = VeRenderTick::OM_BLEND_STATE;
	m_kRenderTickTypeParser["omdepthstencilstate"] = VeRenderTick::OM_DEPTH_STENCIL_STATE;
	m_kRenderTickTypeParser["omrendertargetview"] = VeRenderTick::OM_RENDER_TARGET_VIEW;
	m_kRenderTickTypeParser["omdepthstencilview"] = VeRenderTick::OM_DEPTH_STENCIL_VIEW;
	m_kRenderTickTypeParser["omunorderedaccessview"] = VeRenderTick::OM_UNORDERED_ACCESS_VIEW;

	m_kPrimitiveTopologyParser["undefined"] = VeIAPrimitiveTopology::TOPOLOGY_UNDEFINED;
	m_kPrimitiveTopologyParser["point_list"] = VeIAPrimitiveTopology::TOPOLOGY_POINTLIST;
	m_kPrimitiveTopologyParser["line_list"] = VeIAPrimitiveTopology::TOPOLOGY_LINELIST;
	m_kPrimitiveTopologyParser["line_strip"] = VeIAPrimitiveTopology::TOPOLOGY_LINESTRIP;
	m_kPrimitiveTopologyParser["triangle_list"] = VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	m_kPrimitiveTopologyParser["triangle_strip"] = VeIAPrimitiveTopology::TOPOLOGY_TRIANGLESTRIP;
}
//--------------------------------------------------------------------------
VeRenderer::~VeRenderer()
{
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::VERTEX_SHADER, NULL);
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::PIXEL_SHADER, NULL);
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::TEXTURE, NULL);
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::TEXTURE_ATLAS, NULL);
	g_pResourceManager->SetResourceCreateFunction(
		VeResource::FONT, NULL);
}
//--------------------------------------------------------------------------
void VeRenderer::LoadInitResource()
{
	VeLuaCall<void>("LuaCall_LoadShaders");
}
//--------------------------------------------------------------------------
void VeRenderer::CreateDefaultData()
{
	CreateRenderObjects();
	CreateNodeDatas();
}
//--------------------------------------------------------------------------
void VeRenderer::CreateRenderer(VeUInt32 u32Flag)
{
#	ifdef VE_ENABLE_D3D11
	if(VE_MASK_HAS_ANY(u32Flag, API_D3D11)) VeRendererD3D11::Create();
#	endif

#	ifdef VE_ENABLE_GL
	if(VE_MASK_HAS_ANY(u32Flag, API_OGL)) VeRendererGL::Create();
#	endif
    
#	ifdef VE_ENABLE_GLES2
	if(VE_MASK_HAS_ANY(u32Flag, API_OGLES2)) VeRendererGLES2::Create();
#	endif

	VE_ASSERT(GetSingletonPtr());
}
//--------------------------------------------------------------------------
void VeRenderer::SetScreenSize(VeUInt32 u32Width, VeUInt32 u32Height)
{
	m_u32Width = u32Width;
	m_u32Height = u32Height;
	m_f32Width = (VeFloat32)m_u32Width;
	m_f32Height = (VeFloat32)m_u32Height;
	m_f32InvWidth = 1.0f / m_f32Width;
	m_f32InvHeight = 1.0f / m_f32Height;
	g_pLua->SetValue("screen_width", m_f32Width);
	g_pLua->SetValue("screen_height", m_f32Height);
	g_pLua->SetValue("inv_screen_width", m_f32InvWidth);
	g_pLua->SetValue("inv_screen_height", m_f32InvHeight);
    VeROBufferPtr spScreenParams;
    g_pRenderer->GetRenderObject("screen_params", spScreenParams);
    if(spScreenParams)
    {
        MappedSubresource kMaped;
        VE_ASSERT_EQ(g_pRenderer->MapRes(spScreenParams, 0, MAP_WRITE_DISCARD, VE_TRUE, &kMaped), true);
        VE_ASSERT(kMaped.m_pvData && kMaped.m_u32RowPitch == 16 && kMaped.m_u32DepthPitch == 16);
        VeVector4D kParams(m_f32InvWidth, m_f32InvHeight, m_f32Width, m_f32Height);
        VeCrazyCopy(kMaped.m_pvData, &kParams, 16);
        g_pRenderer->UnMapRes(spScreenParams, 0, MapWriteRange());
    }
	g_pRenderFrameManager->OnScreenSizeChanged();
}
//--------------------------------------------------------------------------
void VeRenderer::AddObject(const VeRenderObjectPtr& spObject)
{
	if(*spObject->GetName())
	{
		VeRenderObject::Type eType = spObject->GetType();
		VE_ASSERT(eType < VeRenderObject::TYPE_MAX);
		VE_ASSERT(m_akObjectMap[eType].Find(spObject->GetName()) == NULL);
		m_akObjectMap[eType][spObject->GetName()] = m_kObjectArray.Size();
		m_kObjectArray.PushBack(spObject);
		spObject->OnAdd();
	}
}
//--------------------------------------------------------------------------
void VeRenderer::DelObject(const VeRenderObjectPtr& spObject)
{
	VeRenderObject::Type eType = spObject->GetType();
	VE_ASSERT(eType < VeRenderObject::TYPE_MAX);
	VeStringMap<VeUInt32>& kMap = m_akObjectMap[eType];
	VeUInt32* pu32Index = kMap.Find(spObject->GetName());
	if(pu32Index)
	{
		VE_ASSERT(m_kObjectArray[*pu32Index] == spObject);
		if((*pu32Index) < (m_kObjectArray.Size() - 1))
		{
			VeStringMap<VeUInt32>& kBackMap =
				m_akObjectMap[m_kObjectArray.Back()->GetType()];
			kBackMap[m_kObjectArray.Back()->GetName()] = *pu32Index;
			m_kObjectArray[*pu32Index] = m_kObjectArray.Back();
		}
		kMap.Remove(spObject->GetName());
		m_kObjectArray.PopBack();
		spObject->OnDel();
	}
}
//--------------------------------------------------------------------------
void VeRenderer::AddNodeData(const VeRenderNodeDataPtr& spNodeData)
{
	if(spNodeData->m_kName != "")
	{
		VE_ASSERT(!m_kNodeDataMap.Find(spNodeData->m_kName));
		m_kNodeDataMap[spNodeData->m_kName] = m_kNodeDataArray.Size();
		m_kNodeDataArray.PushBack(spNodeData);
	}
}
//--------------------------------------------------------------------------
void VeRenderer::DelNodeData(const VeRenderNodeDataPtr& spNodeData)
{
	VeUInt32* pu32Index = m_kNodeDataMap.Find(spNodeData->m_kName);
	if(pu32Index)
	{
		VE_ASSERT(m_kNodeDataArray[*pu32Index] == spNodeData);
		if((*pu32Index) < (m_kNodeDataArray.Size() - 1))
		{
			m_kNodeDataMap[m_kNodeDataArray.Back()->m_kName] = *pu32Index;
			m_kNodeDataArray[*pu32Index] = m_kNodeDataArray.Back();
		}
		m_kNodeDataMap.Remove(spNodeData->m_kName);
		m_kNodeDataArray.PopBack();
	}
}
//--------------------------------------------------------------------------
void VeRenderer::AddProcess(const VeRenderProcessPtr& spProcess)
{
	m_kProcessMap[spProcess->GetName()] = m_kProcessArray.Size();
	m_kProcessArray.PushBack(spProcess);
	spProcess->OnAdd();
}
//--------------------------------------------------------------------------
void VeRenderer::DelProcess(const VeRenderProcessPtr& spProcess)
{
	VeUInt32* pu32Index = m_kProcessMap.Find(spProcess->GetName());
	VE_ASSERT(pu32Index);
	VE_ASSERT(m_kProcessArray[*pu32Index] == spProcess);
	if((*pu32Index) < (m_kProcessArray.Size() - 1))
	{
		m_kProcessMap[m_kProcessArray.Back()->GetName()] = *pu32Index;
		m_kProcessArray[*pu32Index] = m_kProcessArray.Back();
	}
	m_kProcessMap.Remove(spProcess->GetName());
	spProcess->OnDel();
	m_kProcessArray.PopBack();
}
//--------------------------------------------------------------------------
const VeRenderObjectPtr& VeRenderer::GetRenderObject(
	VeRenderObject::Type eType, const VeChar8* pcName)
{
	VE_ASSERT(eType < VeRenderObject::TYPE_MAX);
	VeStringMap<VeUInt32>& kMap = m_akObjectMap[eType];
	VeUInt32* pu32Index = kMap.Find(pcName);
	if(pu32Index)
	{
		return m_kObjectArray[*pu32Index];
	}
	else
	{
		return VeRenderObjectPtr::ms_NULL;
	}
}
//--------------------------------------------------------------------------
const VeRenderNodeDataPtr& VeRenderer::GetRenderNodeData(
	const VeChar8* pcName)
{
	VeUInt32* pu32Index = m_kNodeDataMap.Find(pcName);
	if(pu32Index)
	{
		return m_kNodeDataArray[*pu32Index];
	}
	else
	{
		return VeRenderNodeDataPtr::ms_NULL;
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeRenderer::GetMultisampleLevelCount()
{
	return 0;
}
//--------------------------------------------------------------------------
void VeRenderer::EnumMultisampleLevel(VeUInt32 u32Index,
	VeUInt32& u32Count, VeUInt32& u32Quality)
{
	VE_ASSERT(!"Unknown error!");
}
//--------------------------------------------------------------------------
bool VeRenderer::CreateProcessByType(VeRenderProcess::Type eType,
	const VeChar8* pcName, VeBinaryIStream& kStream,
	VeRenderProcessPtr* pspProcess)
{
	return false;
}
//--------------------------------------------------------------------------
bool VeRenderer::CreateRenderNodeData(const VeChar8* pcName,
	VeBinaryIStream& kStream, VeRenderNodeDataPtr* pspNodeData)
{
	VeRenderNodeDataPtr spData = VE_NEW VeRenderNodeData(pcName);
	VeUInt32 u32Num;
	kStream >> u32Num;
	for(VeUInt32 i(0); i < u32Num; ++i)
	{
		VeRenderTick* pkTick = CreateRenderTick(kStream);
		if(!pkTick)
		{
			return false;
		}
		spData->AddRenderTick(*pkTick);
	}
	kStream >> u32Num;
	for(VeUInt32 i(0); i < u32Num; ++i)
	{
		VeRenderCall* pkCall = CreateRenderCall(kStream);
		if(!pkCall)
		{
			return false;
		}
		spData->AddRenderCall(*pkCall);
	}
	AddNodeData(spData);
	if(pspNodeData)
	{
		*pspNodeData = spData;
	}
	return true;
}
//--------------------------------------------------------------------------
VeRenderTick* VeRenderer::CreateRenderTick(VeBinaryIStream& kStream)
{
	VeRenderTick::Type eType;
	kStream >> eType;
	switch(eType)
	{
	case VeRenderTick::IA_INDEX_BUFFER:
		{
			VeString kName;
			VeUInt32 u32Format;
			kStream.GetStringAligned4(kName);
			kStream >> u32Format;
			return VE_NEW VeIAIndexBuffer(kName, u32Format);
		}
		return NULL;
	case VeRenderTick::IA_INPUT_LAYOUT:
		{
			VeString kName;
			kStream.GetStringAligned4(kName);
			return VE_NEW VeIAInputLayout(kName);
		}
	case VeRenderTick::IA_PRIMITIVE_TOPOLOGY:
		{
			VeIAPrimitiveTopology::Topology eTopology;
			kStream >> eTopology;
			return VE_NEW VeIAPrimitiveTopology(eTopology);
		}
	case VeRenderTick::IA_VERTEX_BUFFER:
		{
			VeString kName;
			VeUInt16 u16Slot, u16Stride;
			VeUInt32 u32Offset;
			kStream.GetStringAligned4(kName);
			kStream >> u16Slot;
			kStream >> u16Stride;
			kStream >> u32Offset;
			return VE_NEW VeIAVertexBuffer(kName, u16Slot, u16Stride, u32Offset);
		}
	case VeRenderTick::VS_CONSTANT_BUFFER:
		{
			VeString kName;
			VeUInt32 u32Slot;
			kStream.GetStringAligned4(kName);
			kStream >> u32Slot;
			return VE_NEW VeVSCBuffer(kName, u32Slot);
		}
	case VeRenderTick::VS_SAMPLER:
		return NULL;
	case VeRenderTick::VS_SHADER:
		{
			VeString kName;
			kStream.GetStringAligned4(kName);
			return VE_NEW VeVSShader(kName);
		}
	case VeRenderTick::VS_SHADER_RESOURCE:
		return NULL;
	case VeRenderTick::HS_CONSTANT_BUFFER:
		return NULL;
	case VeRenderTick::HS_SAMPLER:
		return NULL;
	case VeRenderTick::HS_SHADER:
		return NULL;
	case VeRenderTick::HS_SHADER_RESOURCE:
		return NULL;
	case VeRenderTick::DS_CONSTANT_BUFFER:
		return NULL;
	case VeRenderTick::DS_SAMPLER:
		return NULL;
	case VeRenderTick::DS_SHADER:
		return NULL;
	case VeRenderTick::DS_SHADER_RESOURCE:
		return NULL;
	case VeRenderTick::GS_CONSTANT_BUFFER:
		return NULL;
	case VeRenderTick::GS_SAMPLER:
		return NULL;
	case VeRenderTick::GS_SHADER:
		return NULL;
	case VeRenderTick::GS_SHADER_RESOURCE:
		return NULL;
	case VeRenderTick::SO_TARGET:
		return NULL;
	case VeRenderTick::RS_SCISSOR_RECT:
		{
			VeUInt32 u32Slot;
			VeUInt16 x, y, w, h;
			kStream >> u32Slot;
			kStream >> x;
			kStream >> y;
			kStream >> w;
			kStream >> h;
			return VE_NEW VeRSScissorRectTick(x, y, w, h, u32Slot);
		}
		return NULL;
	case VeRenderTick::RS_STATE:
		{
			VeString kName;
			kStream.GetStringAligned4(kName);
			return VE_NEW VeRSState(kName);
		}
	case VeRenderTick::RS_VIEWPORT:
		{
			VeUInt32 u32Slot;
			kStream >> u32Slot;
			VeVector4D kViewport;
			kStream >> kViewport;
			return VE_NEW VeRSViewportTick(kViewport, u32Slot);
		}
	case VeRenderTick::PS_CONSTANT_BUFFER:
		return NULL;
	case VeRenderTick::PS_SAMPLER:
		{
			VeUInt32 u32Slot;
			VeString kName;
			kStream.GetStringAligned4(kName);
			kStream >> u32Slot;
			return VE_NEW VePSSampler(kName, u32Slot);
		}
	case VeRenderTick::PS_SHADER:
		{
			VeString kName;
			kStream.GetStringAligned4(kName);
			return VE_NEW VePSShader(kName);
		}
	case VeRenderTick::PS_SHADER_RESOURCE:
		{
			VeUInt32 u32Slot;
			VeString kName;
			kStream.GetStringAligned4(kName);
			kStream >> u32Slot;
			return VE_NEW VePSShaderResource(kName, u32Slot);
		}
	case VeRenderTick::OM_BLEND_STATE:
		{
			VeString kName;
			kStream.GetStringAligned4(kName);
			VeOMBlendStateTick* pkBlendState = VE_NEW VeOMBlendStateTick(kName);
			kStream >> (pkBlendState->m_af32Factor[0]);
			kStream >> (pkBlendState->m_af32Factor[1]);
			kStream >> (pkBlendState->m_af32Factor[2]);
			kStream >> (pkBlendState->m_af32Factor[3]);
			kStream >> (pkBlendState->m_u32SampleMask);
			return pkBlendState;
		}
	case VeRenderTick::OM_DEPTH_STENCIL_STATE:
		{
			VeString kName;
			kStream.GetStringAligned4(kName);
			VeUInt32 u32StencilRef;
			kStream >> u32StencilRef;
			return VE_NEW VeOMDepthStencilStateTick(kName, u32StencilRef);
		}

	case VeRenderTick::OM_RENDER_TARGET_VIEW:
		{
			VeUInt32 u32Slot;
			VeString kName;
			kStream.GetStringAligned4(kName);
			kStream >> u32Slot;
			return VE_NEW VeOMRenderTargetViewTick(kName, u32Slot);
		}
	case VeRenderTick::OM_DEPTH_STENCIL_VIEW:
		{
			VeString kName;
			kStream.GetStringAligned4(kName);
			return VE_NEW VeOMDepthStencilViewTick(kName);
		}
	case VeRenderTick::OM_UNORDERED_ACCESS_VIEW:
		return NULL;
	default:
		return NULL;
	}
}
//--------------------------------------------------------------------------
VeRenderCall* VeRenderer::CreateRenderCall(VeBinaryIStream& kStream)
{
	VeRenderCall::Type eType;
	kStream >> eType;
	switch(eType)
	{
	case VeRenderCall::CLEAR:
		{
			VeClearCall* pkCall = VE_NEW VeClearCall();
			kStream >> pkCall->m_bClearColor;
			kStream >> pkCall->m_bClearDepth;
			kStream >> pkCall->m_bClearStencil;
			kStream >> pkCall->m_u8Stencil;
			kStream >> pkCall->m_f32Depth;
			kStream >> pkCall->m_kColorArray;
			return pkCall;
		}
	case VeRenderCall::DRAW:
		{
			VeDrawCall* pkCall = VE_NEW VeDrawCall(eType);
			kStream >> pkCall->m_kDraw.m_u32VertexCount;
			kStream >> pkCall->m_kDraw.m_u32StartVertexLocation;
			return pkCall;
		}
	case VeRenderCall::DRAW_INDEXED:
		{
			VeDrawCall* pkCall = VE_NEW VeDrawCall(eType);
			kStream >> pkCall->m_kDrawIndexed.m_u32IndexCount;
			kStream >> pkCall->m_kDrawIndexed.m_u32StartIndexLocation;
			kStream >> pkCall->m_kDrawIndexed.m_i32BaseVertexLocation;
			return pkCall;
		}
	case VeRenderCall::DRAW_INSTANCED:
	case VeRenderCall::DRAW_INDEXED_INSTANCED:
	case VeRenderCall::DRAW_INSTANCED_INDIRECT:
	case VeRenderCall::DRAW_INDEXED_INSTANCED_INDIRECT:
	case VeRenderCall::DRAW_AUTO:
	default:
		return NULL;
	}
}
//--------------------------------------------------------------------------
bool VeRenderer::MapRes(const VeRenderObjectPtr& spObject,
	VeUInt32 u32SubResource, Map eType, VE_BOOL bSync,
	MappedSubresource* pkMapped)
{
	VE_ASSERT(pkMapped);
	VeZeroMemory(pkMapped, sizeof(MappedSubresource));
	return false;
}
//--------------------------------------------------------------------------
void VeRenderer::UnMapRes(const VeRenderObjectPtr& spObject,
	VeUInt32 u32SubResource, MapWriteRange kRange)
{

}
//--------------------------------------------------------------------------
void VeRenderer::CreateRenderObject(VeBinaryIStream& kStream,
	VeRenderObjectPtr* pspRenderObject)
{
	VeUInt32 u32Type;
	kStream >> u32Type;
	VeString kName;
	kStream.GetStringAligned4(kName);
	switch(u32Type)
	{
	case VeRenderObject::TYPE_BLEND_STATE:
		CreateBlendState(kName, kStream, (VeROBlendStatePtr*)pspRenderObject);
		break;
	case VeRenderObject::TYPE_DEPTH_STENCIL_STATE:
		CreateDepthStencilState(kName, kStream, (VeRODepthStencilStatePtr*)pspRenderObject);
		break;
	case VeRenderObject::TYPE_RASTERIZER_STATE:
		CreateRasterizerState(kName, kStream, (VeRORasterizeStatePtr*)pspRenderObject);
		break;
	case VeRenderObject::TYPE_SAMPLER_STATE:
		CreateSamplerState(kName, kStream, (VeROSamplerStatePtr*)pspRenderObject);
		break;
	case VeRenderObject::TYPE_INPUT_LAYOUT:
		CreateInputLayout(kName, kStream, (VeROInputLayoutPtr*)pspRenderObject);
		break;
	default:
		if(pspRenderObject)
		{
			*pspRenderObject = NULL;
		}
		break;
	}
}
//--------------------------------------------------------------------------
void VeRenderer::DestroyRenderObject(VeRenderObject::Type eType,
	const VeChar8* pcName)
{
	VE_ASSERT(eType < VeRenderObject::TYPE_MAX && pcName);
	VeStringMap<VeUInt32>& kMap = m_akObjectMap[eType];
	VeUInt32* pu32Index = kMap.Find(pcName);
	if(pu32Index)
	{
		VeRenderObjectPtr spObject = m_kObjectArray[*pu32Index];
		if((*pu32Index) < (m_kObjectArray.Size() - 1))
		{
			VeStringMap<VeUInt32>& kBackMap =
				m_akObjectMap[m_kObjectArray.Back()->GetType()];
			kBackMap[m_kObjectArray.Back()->GetName()] = *pu32Index;
			m_kObjectArray[*pu32Index] = m_kObjectArray.Back();
		}
		kMap.Remove(spObject->GetName());
		m_kObjectArray.PopBack();
		spObject->OnDel();
	}
}
//--------------------------------------------------------------------------
void VeRenderer::GetSpriteFrame(const VeChar8* pcName, SpriteFrame& kFrame)
{
	VeUInt32* pu32Iter = m_kSpriteFrameMap.Find(pcName);
	if(pu32Iter)
	{
		kFrame = m_kSpriteFrameArray[*pu32Iter];
	}
	else
	{
		kFrame.m_pkResource = NULL;
		kFrame.m_u32Index = 0;
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeRenderer::CreateRenderTarget2D(Format eFormat,
	VeUInt16 u16Width, VeUInt16 u16Height)
{
	VeChar8 acBuffer[256];
	VeSprintf(acBuffer, "rt2d_%u", m_u32ObjectIndex);
	VeMemoryOStream kStream;
	
	kStream << VeUInt16(u16Width);
	kStream << VeUInt16(u16Height);
	kStream << VeUInt16(1);
	kStream << VeUInt16(1);
	kStream << VeUInt8(eFormat);
	kStream << VeUInt8(1);
	kStream << VeUInt8(0);
	kStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
	kStream << VeUInt8(VeRenderer::BIND_SHADER_RESOURCE | VeRenderer::BIND_RENDER_TARGET);
	kStream << VeUInt8(0);
	kStream << VeUInt16(0);
	kStream << VeUInt16(1);
	kStream << VeUInt16(0);
	VeROTexture2DPtr spTex;
	CreateTexture2D(acBuffer, kStream, &spTex);
	kStream.Reset();
	if(!spTex) return NULL;

	kStream << VeUInt32(16);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(1);
	kStream << VeUInt32(16);
	kStream << VeUInt32(16);
	kStream << (1.0f / VeFloat32(u16Width));
	kStream << (1.0f / VeFloat32(u16Height));
	kStream << VeFloat32(u16Width);
	kStream << VeFloat32(u16Height);
	VeROBufferPtr spBuf;
	g_pRenderer->CreateBuffer(acBuffer, kStream, &spBuf);
	kStream.Reset();
	if(!spBuf) return NULL;

	m_kRenderTargetMap[spTex->GetName()] = m_kRenderTargetArray.Size();
	m_kRenderTargetArray.Increase();
	m_kRenderTargetArray.Back().m_spTex = spTex;
	m_kRenderTargetArray.Back().m_spBuf = spBuf;
	m_kRenderTargetArray.Back().m_eFormat = eFormat;
	m_kRenderTargetArray.Back().m_u16Width = u16Width;
	m_kRenderTargetArray.Back().m_u16Height = u16Height;
	++m_u32ObjectIndex;
	return spTex->GetName();
}
//--------------------------------------------------------------------------
void VeRenderer::DestoryRenderTarget2D(const VeChar8* pcName)
{
	VeUInt32* pu32Iter = m_kRenderTargetMap.Find(pcName);
	if(pu32Iter)
	{
		DelObject(m_kRenderTargetArray[*pu32Iter].m_spTex);
		DelObject(m_kRenderTargetArray[*pu32Iter].m_spBuf);
		if((*pu32Iter) < (m_kRenderTargetArray.Size() - 1))
		{
			m_kRenderTargetArray[*pu32Iter] = m_kRenderTargetArray.Back();
			m_kRenderTargetMap[m_kRenderTargetArray.Back().m_spTex->GetName()] = *pu32Iter;
		}
		m_kRenderTargetArray.PopBack();
		m_kRenderTargetMap.Remove(pcName);
	}
}
//--------------------------------------------------------------------------
const VeRenderer::RenderTarget* VeRenderer::GetRenderTarget2D(
	const VeChar8* pcName)
{
	VeUInt32* pu32Iter = m_kRenderTargetMap.Find(pcName);
	if(pu32Iter)
	{
		return &m_kRenderTargetArray[*pu32Iter];
	}
	return NULL;
}
//--------------------------------------------------------------------------
