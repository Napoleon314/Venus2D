////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Test Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeGraphicsTest.cpp
//  Version:     v1.00
//  Created:     27/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeGraphicsTest.h"

VeGraphicsTest::VeGraphicsTest()
	: m_pkNode(NULL), m_pkNode1(NULL)
{

}

VeGraphicsTest::~VeGraphicsTest()
{

}

void VeGraphicsTest::Render()
{
	g_pRenderer->Render();
	//g_pRenderer->Render(m_pkNode);
 //   if(m_spResolve)
 //   {
 //       g_pRenderer->Process(m_spResolve);
 //   }
	//g_pRenderer->Render(m_pkNode1);
	g_pRenderer->Present();
}

void VeGraphicsTest::OnInit()
{
	VeResourceGroupPtr spMaterialGroup = VE_NEW VeResourceGroup("Scripts");
#if defined(VE_PLATFORM_ANDROID)
	g_pMaterialManager->LoadShaderList("asset#Shaders");
	spMaterialGroup->PushReadDirectoryBack("asset#Scripts");
#else
	g_pMaterialManager->LoadShaderList("file#Shaders");
	spMaterialGroup->PushReadDirectoryBack("file#Scripts");
#endif

	VE_ASSERT_NOT_EQ(VeLoadMaterialSync("startup.[mat]", "Scripts"), NULL);
	//spMaterial->Unload();
	

//	VeResourceGroupPtr spShaderGroup = VE_NEW VeResourceGroup("Shader");
//	VeResourceGroupPtr spMaterialGroup = VE_NEW VeResourceGroup("Material");
//#if defined(VE_PLATFORM_ANDROID)
//	spShaderGroup->PushReadDirectoryBack("asset#Shader");
//	spMaterialGroup->PushReadDirectoryBack("asset#Material");
//#else
//	spShaderGroup->PushReadDirectoryBack("file#Shader");
//	spMaterialGroup->PushReadDirectoryBack("file#Material");
//#endif
//
//	VeShaderResourcePtr spVertexShader = VeLoadVertexShaderSync("Sample", "Shader");
//	VeShaderResourcePtr spPixelShader = VeLoadPixelShaderSync("Sample", "Shader");
//
//	/*VeMemoryOStream kBlendStateStream;
//	kBlendStateStream << VeUInt16(VE_FALSE);
//	kBlendStateStream << VeUInt16(1);
//	kBlendStateStream << VeUInt8(VE_TRUE);
//	kBlendStateStream << VeUInt8(VeRenderer::BLEND_SRC_ALPHA);
//	kBlendStateStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
//	kBlendStateStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
//	kBlendStateStream << VeUInt8(VeRenderer::BLEND_SRC_ALPHA);
//	kBlendStateStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
//	kBlendStateStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
//	kBlendStateStream << VeUInt8(VeRenderer::COLOR_WRITE_ENABLE_ALL);
//	g_pRenderer->CreateBlendState("alpha_blend", kBlendStateStream);*/
//
//	/*VeMemoryOStream kInputLayoutStream;
//	kInputLayoutStream.AppendStringAligned4("Sample", (VeInt32)VeStrlen("Sample"));
//	kInputLayoutStream << VeUInt32(2);
//	kInputLayoutStream << VeByte(VeRenderer::SE_COLOR);
//	kInputLayoutStream << VeByte(0);
//	kInputLayoutStream << VeByte(VeRenderer::FMT_R8G8B8A8_UNORM);
//	kInputLayoutStream << VeByte(0);
//	kInputLayoutStream << VeByte(0);
//	kInputLayoutStream << VeByte(VeRenderer::PER_VERTEX_DATA);
//	kInputLayoutStream << VeUInt16(0);
//	kInputLayoutStream << VeByte(VeRenderer::SE_POSITION);
//	kInputLayoutStream << VeByte(0);
//	kInputLayoutStream << VeByte(VeRenderer::FMT_R32G32B32_FLOAT);
//	kInputLayoutStream << VeByte(1);
//	kInputLayoutStream << VeByte(0);
//	kInputLayoutStream << VeByte(VeRenderer::PER_VERTEX_DATA);
//	kInputLayoutStream << VeUInt16(0);
//
//	VE_ASSERT_EQ(g_pRenderer->CreateInputLayout("Sample", kInputLayoutStream), true);*/
//
	VeFloat32 af32Vertex[] =
	{
		-30.0f, 30.0f, -30.0f,
		30.0f, 30.0f, -30.0f,
		-30.0f, -30.0f, -30.0f,
		30.0f, -30.0f, -30.0f,

		-30.0f, 30.0f, -30.0f,
		30.0f, 30.0f, -30.0f,
		-30.0f, 30.0f, 30.0f,
		30.0f, 30.0f, 30.0f,

		30.0f, 30.0f, -30.0f,
		30.0f, -30.0f, -30.0f,
		30.0f, 30.0f, 30.0f,
		30.0f, -30.0f, 30.0f,

		-30.0f, 30.0f, -30.0f,
		-30.0f, -30.0f, -30.0f,
		-30.0f, 30.0f, 30.0f,
		-30.0f, -30.0f, 30.0f,

		-30.0f, 30.0f, 30.0f,
		30.0f, 30.0f, 30.0f,
		-30.0f, -30.0f, 30.0f,
		30.0f, -30.0f, 30.0f,

		-200.0f, -30.0f, 200.0f,
		200.0f, -30.0f, 200.0f,
		-200.0f, -30.0f, -200.0f,
		200.0f, -30.0f, -200.0f,
	};

	VeMemoryOStream kVertexBufferStream;
	kVertexBufferStream << VeUInt32(sizeof(af32Vertex));
	kVertexBufferStream << VeUInt16(0);
	kVertexBufferStream << VeUInt16(0);
	kVertexBufferStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kVertexBufferStream << VeByte(VeRenderer::BIND_VERTEX_BUFFER);
	kVertexBufferStream << VeByte(0);
	kVertexBufferStream << VeByte(1);
	kVertexBufferStream << VeUInt32(0);
	kVertexBufferStream << VeUInt32(0);
	kVertexBufferStream.AddBlob(af32Vertex, VeInt32(sizeof(af32Vertex)));

	VE_ASSERT_EQ(g_pRenderer->CreateBuffer("Triangle", kVertexBufferStream), true);

	VeRGBA akColors[] =
	{
		VeRGBA(255,0,0,128),
		VeRGBA(255,0,0,128),
		VeRGBA(255,0,0,128),
		VeRGBA(255,0,0,128),

		VeRGBA(0,255,0,128),
		VeRGBA(0,255,0,128),
		VeRGBA(0,255,0,128),
		VeRGBA(0,255,0,128),

		VeRGBA(255,255,0,128),
		VeRGBA(255,255,0,128),
		VeRGBA(255,255,0,128),
		VeRGBA(255,255,0,128),

		VeRGBA(0,255,255,128),
		VeRGBA(0,255,255,128),
		VeRGBA(0,255,255,128),
		VeRGBA(0,255,255,128),

		VeRGBA(255,0,255,128),
		VeRGBA(255,0,255,128),
		VeRGBA(255,0,255,128),
		VeRGBA(255,0,255,128),

		VeRGBA(255,128,0,128),
		VeRGBA(255,128,0,128),
		VeRGBA(255,128,0,128),
		VeRGBA(255,128,0,128),
	};
	VeMemoryOStream kColorVertexBufferStream;
	kColorVertexBufferStream << VeUInt32(sizeof(akColors));
	kColorVertexBufferStream << VeUInt16(0);
	kColorVertexBufferStream << VeUInt16(0);
	kColorVertexBufferStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kColorVertexBufferStream << VeByte(VeRenderer::BIND_VERTEX_BUFFER);
	kColorVertexBufferStream << VeByte(0);
	kColorVertexBufferStream << VeByte(1);
	kColorVertexBufferStream << VeUInt32(0);
	kColorVertexBufferStream << VeUInt32(0);
	kColorVertexBufferStream.AddBlob(akColors, VeInt32(sizeof(akColors)));
	VE_ASSERT_EQ(g_pRenderer->CreateBuffer("TriangleColor", kColorVertexBufferStream), true);

	VeUInt16 au16Indexes[] =
	{
		0,1,2,1,3,2, 5,4,6,5,6,7, 9,8,10,9,10,11, 12,13,14,13,15,14, 18,17,16,18,19,17, 20,21,22,22,21,23
	};
	VeMemoryOStream kIndexBufferStream;
	kIndexBufferStream << VeUInt32(sizeof(au16Indexes));
	kIndexBufferStream << VeUInt16(0);
	kIndexBufferStream << VeUInt16(0);
	kIndexBufferStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kIndexBufferStream << VeByte(VeRenderer::BIND_INDEX_BUFFER);
	kIndexBufferStream << VeByte(0);
	kIndexBufferStream << VeByte(1);
	kIndexBufferStream << VeUInt32(0);
	kIndexBufferStream << VeUInt32(0);
	kIndexBufferStream.AddBlob(au16Indexes, VeInt32(sizeof(au16Indexes)));
	g_pRenderer->CreateBuffer("TriangleIndex", kIndexBufferStream);
//
//	/*VeMemoryOStream kDepthTestStream;
//	kDepthTestStream << VeUInt8(VE_TRUE);
//	kDepthTestStream << VeUInt8(VE_TRUE);
//	kDepthTestStream << VeUInt8(VeRenderer::COMPARISON_LESS);
//	kDepthTestStream << VeUInt8(VE_FALSE);
//	g_pRenderer->CreateDepthStencilState("DepthTest", kDepthTestStream);*/
//
	VeUInt32 u32LevelCount = g_pRenderer->GetMultisampleLevelCount();
//
//	/*VeMemoryOStream kRasterizerStream;
//	kRasterizerStream << VeUInt8(VeRenderer::FILL_SOLID);
//	kRasterizerStream << VeUInt8(VeRenderer::CULL_BACK);
//	kRasterizerStream << VeUInt8(VE_FALSE);
//	kRasterizerStream << VeUInt8(VeRenderer::DBIAS_NONE);
//	kRasterizerStream << VeUInt8(VE_TRUE);
//	kRasterizerStream << VeUInt8(VE_FALSE);
//	kRasterizerStream << VeUInt8(u32LevelCount ? VE_TRUE : VE_FALSE);
//	kRasterizerStream << VeUInt8(VE_FALSE);
//	g_pRenderer->CreateRasterizerState("RasterizerNormal", kRasterizerStream);*/
//
	VeFloat32 m4Camera[16];
	g_pRenderer->GetMatrixPerspectiveFov(m4Camera, VE_MATH_PI_4_F, 0.25f, 8192.0f);

	VeMemoryOStream kConstantBufferStream;
	kConstantBufferStream << VeUInt32(64);
	kConstantBufferStream << VeUInt16(0);
	kConstantBufferStream << VeUInt16(0);
	kConstantBufferStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kConstantBufferStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kConstantBufferStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kConstantBufferStream << VeByte(1);
	kConstantBufferStream << VeUInt32(0);
	kConstantBufferStream << VeUInt32(0);
	kConstantBufferStream.AddBlob(m4Camera, sizeof(VeMatrix));

	VE_ASSERT_EQ(g_pRenderer->CreateBuffer("ConstantBuffer", kConstantBufferStream), true);

	VeMemoryOStream kTransformBufferStream;
	kTransformBufferStream << VeUInt32(32);
	kTransformBufferStream << VeUInt16(0);
	kTransformBufferStream << VeUInt16(0);
	kTransformBufferStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kTransformBufferStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kTransformBufferStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kTransformBufferStream << VeByte(0);
	VE_ASSERT_EQ(g_pRenderer->CreateBuffer("TransformBuffer", kTransformBufferStream, &m_spTransformBuffer), true);

	{
		VeMemoryOStream kColorTextureStream;
		kColorTextureStream << VeUInt16(g_pRenderer->GetWidth());
		kColorTextureStream << VeUInt16(g_pRenderer->GetHeight());
		kColorTextureStream << VeUInt16(1);
		kColorTextureStream << VeUInt16(1);
		kColorTextureStream << VeUInt8(VeRenderer::FMT_R8G8B8A8_UNORM);
		kColorTextureStream << VeUInt8(1);
		kColorTextureStream << VeUInt8(0);
		kColorTextureStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
		kColorTextureStream << VeUInt8(VeRenderer::BIND_RENDER_TARGET | VeRenderer::BIND_SHADER_RESOURCE);
		kColorTextureStream << VeUInt8(0);
		kColorTextureStream << VeUInt16(0);
		kColorTextureStream << VeUInt16(1);
		kColorTextureStream << VeUInt16(1);
		kColorTextureStream << VeUInt32(sizeof(VeRGBA) * g_pRenderer->GetWidth());
		kColorTextureStream << VeUInt32(sizeof(VeRGBA) * g_pRenderer->GetWidth() * g_pRenderer->GetHeight());
		kColorTextureStream << VeUInt32(sizeof(VeRGBA) * g_pRenderer->GetWidth() * g_pRenderer->GetHeight());
		for(VeUInt32 i(0); i < g_pRenderer->GetHeight(); ++i)
		{
			for(VeUInt32 j(0); j < g_pRenderer->GetWidth(); ++j)
			{
				kColorTextureStream << VeRGBA(255, 0, 255, 255);
			}
		}
		g_pRenderer->CreateTexture2D("color_buffer", kColorTextureStream);

		if(!u32LevelCount)
		{
			VeMemoryOStream kDepthTextureStream;
			kDepthTextureStream << VeUInt16(g_pRenderer->GetWidth());
			kDepthTextureStream << VeUInt16(g_pRenderer->GetHeight());
			kDepthTextureStream << VeUInt16(1);
			kDepthTextureStream << VeUInt16(1);
			kDepthTextureStream << VeUInt8(VeRenderer::FMT_D24_UNORM_S8_UINT);
			kDepthTextureStream << VeUInt8(1);
			kDepthTextureStream << VeUInt8(0);
			kDepthTextureStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
			kDepthTextureStream << VeUInt8(VeRenderer::BIND_DEPTH_STENCIL | VeRenderer::BIND_SHADER_RESOURCE);
			kDepthTextureStream << VeUInt8(0);
			kDepthTextureStream << VeUInt16(0);
			kDepthTextureStream << VeUInt16(1);
			kDepthTextureStream << VeUInt16(0);
			g_pRenderer->CreateTexture2D("depth_buffer", kDepthTextureStream);
		}
	}

	if(u32LevelCount)
	{
		VeUInt32 u32SampleCount, u32SampleQuality;
		g_pRenderer->EnumMultisampleLevel(u32LevelCount - 1, u32SampleCount, u32SampleQuality);
		VeMemoryOStream kColorTextureMSAAStream;
		kColorTextureMSAAStream << VeUInt16(g_pRenderer->GetWidth());
		kColorTextureMSAAStream << VeUInt16(g_pRenderer->GetHeight());
		kColorTextureMSAAStream << VeUInt16(1);
		kColorTextureMSAAStream << VeUInt16(1);
		kColorTextureMSAAStream << VeUInt8(VeRenderer::FMT_R8G8B8A8_UNORM);
		kColorTextureMSAAStream << VeUInt8(u32SampleCount);
		kColorTextureMSAAStream << VeUInt8(u32SampleQuality);
		kColorTextureMSAAStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
		kColorTextureMSAAStream << VeUInt8(VeRenderer::BIND_RENDER_TARGET);
		kColorTextureMSAAStream << VeUInt8(0);
		kColorTextureMSAAStream << VeUInt16(0);
		kColorTextureMSAAStream << VeUInt16(1);
		kColorTextureMSAAStream << VeUInt16(0);
		g_pRenderer->CreateTexture2D("color_buffer_msaa", kColorTextureMSAAStream);

		VeMemoryOStream kDepthTextureMSAAStream;
		kDepthTextureMSAAStream << VeUInt16(g_pRenderer->GetWidth());
		kDepthTextureMSAAStream << VeUInt16(g_pRenderer->GetHeight());
		kDepthTextureMSAAStream << VeUInt16(1);
		kDepthTextureMSAAStream << VeUInt16(1);
		kDepthTextureMSAAStream << VeUInt8(VeRenderer::FMT_D24_UNORM_S8_UINT);
		kDepthTextureMSAAStream << VeUInt8(u32SampleCount);
		kDepthTextureMSAAStream << VeUInt8(u32SampleQuality);
		kDepthTextureMSAAStream << VeUInt8(VeRenderer::USAGE_DEFAULT);
		kDepthTextureMSAAStream << VeUInt8(VeRenderer::BIND_DEPTH_STENCIL);
		kDepthTextureMSAAStream << VeUInt8(0);
		kDepthTextureMSAAStream << VeUInt16(0);
		kDepthTextureMSAAStream << VeUInt16(1);
		kDepthTextureMSAAStream << VeUInt16(0);
		g_pRenderer->CreateTexture2D("depth_buffer_msaa", kDepthTextureMSAAStream);

		VeMemoryOStream kResolveStream;
		kResolveStream << VeUInt16(1);
		kResolveStream << VeUInt16(1);
		VeFixedStringA kName = "color_buffer";
		kResolveStream.AppendStringAligned4(kName, kName.GetLength());
		kName = "color_buffer_msaa";
		kResolveStream.AppendStringAligned4(kName, kName.GetLength());
		kName = "depth_buffer";
		kResolveStream.AppendStringAligned4(kName, kName.GetLength());
		kName = "depth_buffer_msaa";
		kResolveStream.AppendStringAligned4(kName, kName.GetLength());
		g_pRenderer->CreateProcessByType(VeRenderProcess::TYPE_MSAA_RESOLVE, "msaa_resolve", kResolveStream, &m_spResolve);
	}

	VeMemoryOStream kNodeDataStream;
	kNodeDataStream << VeUInt32(16);
	kNodeDataStream << VeRenderTick::VS_SHADER;
	VeFixedStringA kName = "Sample";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeRenderTick::PS_SHADER;
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeRenderTick::IA_INPUT_LAYOUT;
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kNodeDataStream << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	kNodeDataStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "Triangle";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeUInt16(1);
	kNodeDataStream << VeUInt16(12);
	kNodeDataStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "TriangleColor";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeUInt16(0);
	kNodeDataStream << VeUInt16(4);
	kNodeDataStream << VeRenderTick::RS_VIEWPORT;
	kNodeDataStream << VeUInt32(0);
	VeVector4D kViewport(0,0,g_pRenderer->GetWidthF(),g_pRenderer->GetHeightF());
	kNodeDataStream << kViewport;
	kNodeDataStream << VeRenderTick::OM_RENDER_TARGET_VIEW;
	kName = u32LevelCount ? "color_buffer_msaa" : "color_buffer";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeUInt32(0);
	kNodeDataStream << VeRenderTick::OM_DEPTH_STENCIL_VIEW;
	kName = u32LevelCount ? "depth_buffer_msaa" : "depth_buffer";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeRenderTick::OM_BLEND_STATE;
	kName = "replace";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << 0;
	kNodeDataStream << 0;
	kNodeDataStream << 0;
	kNodeDataStream << 0;
	kNodeDataStream << 0xffffffff;
	kNodeDataStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "TriangleIndex";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeRenderer::FMT_R16_UINT;
	kNodeDataStream << VeRenderTick::OM_DEPTH_STENCIL_STATE;
	kName = "depth_test";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeUInt32(0);
	kNodeDataStream << VeRenderTick::RS_STATE;
	kName = u32LevelCount ? "normal_msaa" : "normal";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeRenderTick::RS_SCISSOR_RECT;
	kNodeDataStream << VeUInt32(0);
	kNodeDataStream << VeUInt16(0);
	kNodeDataStream << VeUInt16(0);
	kNodeDataStream << VeUInt16(400);
	kNodeDataStream << VeUInt16(600);
	kNodeDataStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "ConstantBuffer";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeUInt32(0);
	kNodeDataStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "TransformBuffer";
	kNodeDataStream.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream << VeUInt32(1);

	kNodeDataStream << VeUInt32(2);
	kNodeDataStream << VeRenderCall::CLEAR;
	kNodeDataStream << true;
	kNodeDataStream << true;
	kNodeDataStream << true;
	kNodeDataStream << VeUInt8(0);
	kNodeDataStream << 1.0f;
	kNodeDataStream << VeUInt32(1);
	kNodeDataStream << VeColorA(0.0f, 0.125f, 0.3f, 1.0f);
	kNodeDataStream << VeRenderCall::DRAW_INDEXED;
	kNodeDataStream << VeUInt32(36);
	kNodeDataStream << VeUInt32(0);

	VeRenderNodeDataPtr spData;
	g_pRenderer->CreateRenderNodeData("Sample", kNodeDataStream, &spData);

	m_pkNode = VE_NEW VeRenderNode(spData);
//
//
//
//	/*VeMemoryOStream kSamplerStream;
//	kSamplerStream << VeUInt8(VeRenderer::FILTER_MIN_MAG_MIP_POINT);
//	kSamplerStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
//	kSamplerStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
//	kSamplerStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
//	kSamplerStream << VeUInt16(16);
//	kSamplerStream << VeUInt16(VeRenderer::COMPARISON_NEVER);
//	kSamplerStream << 0.0f;
//	kSamplerStream << -VE_MAXFLOAT_F;
//	kSamplerStream << VE_MAXFLOAT_F;
//	kSamplerStream << VeColorA::BLACK;
//
//	VE_ASSERT_EQ(g_pRenderer->CreateSamplerState("Point", kSamplerStream), true);*/
//
//    spVertexShader = VeLoadVertexShaderSync("Quad", "Shader");
//	spPixelShader = VeLoadPixelShaderSync("Quad", "Shader");
//
//	VeMemoryOStream kQuadInputLayoutStream;
//	kQuadInputLayoutStream.AppendStringAligned4("Quad", (VeInt32)VeStrlen("Quad"));
//	kQuadInputLayoutStream << VeUInt32(1);
//	kQuadInputLayoutStream << VeByte(VeRenderer::SE_POSITION);
//	kQuadInputLayoutStream << VeByte(0);
//	kQuadInputLayoutStream << VeByte(VeRenderer::FMT_R32G32B32_FLOAT);
//	kQuadInputLayoutStream << VeByte(0);
//	kQuadInputLayoutStream << VeByte(0);
//	kQuadInputLayoutStream << VeByte(VeRenderer::PER_VERTEX_DATA);
//	kQuadInputLayoutStream << VeUInt16(0);
//
//	VE_ASSERT_EQ(g_pRenderer->CreateInputLayout("Quad", kQuadInputLayoutStream), true);
//
	VeFloat32 af32VertexQuad[12] =
	{
		-1.0f, 1.0f, 0.5f,
		1.0f, 1.0f, 0.5f,
		-1.0f, -1.0f, 0.5f,
		1.0f, -1.0f, 0.5f,
	};

	VeMemoryOStream kQuadVertexBufferStream;
	kQuadVertexBufferStream << VeUInt32(sizeof(af32VertexQuad));
	kQuadVertexBufferStream << VeUInt16(0);
	kQuadVertexBufferStream << VeUInt16(0);
	kQuadVertexBufferStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kQuadVertexBufferStream << VeByte(VeRenderer::BIND_VERTEX_BUFFER);
	kQuadVertexBufferStream << VeByte(0);
	kQuadVertexBufferStream << VeByte(1);
	kQuadVertexBufferStream << VeUInt32(0);
	kQuadVertexBufferStream << VeUInt32(0);
	kQuadVertexBufferStream.AddBlob(af32VertexQuad, VeInt32(sizeof(af32VertexQuad)));

	VE_ASSERT_EQ(g_pRenderer->CreateBuffer("Quad", kQuadVertexBufferStream), true);

	VeMemoryOStream kNodeDataStream1;
	kNodeDataStream1 << VeUInt32(12);
	kNodeDataStream1 << VeRenderTick::VS_SHADER;
	kName = "Quad";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeRenderTick::PS_SHADER;
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeRenderTick::IA_INPUT_LAYOUT;
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kNodeDataStream1 << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLESTRIP;
	kNodeDataStream1 << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "Quad";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeUInt16(0);
	kNodeDataStream1 << VeUInt16(12);
	kNodeDataStream1 << VeRenderTick::RS_VIEWPORT;
	kNodeDataStream1 << VeUInt32(0);
	kViewport = VeVector4D(0,0,g_pRenderer->GetWidthF(),g_pRenderer->GetHeightF());
	kNodeDataStream1 << kViewport;
	kNodeDataStream1 << VeRenderTick::OM_RENDER_TARGET_VIEW;
	kName = "back_buffer";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeUInt32(0);
	kNodeDataStream1 << VeRenderTick::OM_BLEND_STATE;
	kName = "null";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << 0;
	kNodeDataStream1 << 0;
	kNodeDataStream1 << 0;
	kNodeDataStream1 << 0;
	kNodeDataStream1 << 0xffffffff;
	kNodeDataStream1 << VeRenderTick::PS_SHADER_RESOURCE;
	kName = "color_buffer";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeUInt32(0);
	kNodeDataStream1 << VeRenderTick::PS_SAMPLER;
	kName = "point_clamp";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeUInt32(0);
	kNodeDataStream1 << VeRenderTick::OM_DEPTH_STENCIL_STATE;
	kName = "null";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());
	kNodeDataStream1 << VeUInt32(0);
	kNodeDataStream1 << VeRenderTick::RS_STATE;
	kName = "null";
	kNodeDataStream1.AppendStringAligned4(kName, kName.GetLength());

	kNodeDataStream1 << VeUInt32(1);
	kNodeDataStream1 << VeRenderCall::DRAW;
	kNodeDataStream1 << VeUInt32(4);
	kNodeDataStream1 << VeUInt32(0);

	VeRenderNodeDataPtr spData1;
	g_pRenderer->CreateRenderNodeData("Quad", kNodeDataStream1, &spData1);

	m_pkNode1 = VE_NEW VeRenderNode(spData1);

	//VeMaterialResourcePtr spSample = VeLoadMaterialSync("sample.[mat]", "Scripts");
	//spSample->Unload();
}

void VeGraphicsTest::OnTerm()
{
	VE_SAFE_DELETE(m_pkNode);
	VE_SAFE_DELETE(m_pkNode1);
	m_spTransformBuffer = NULL;
	m_spResolve = NULL;
}

void VeGraphicsTest::OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height)
{
	VeDebugOutput("OnBufferResized: %dx%d", u32Width, u32Height);
}

void VeGraphicsTest::OnUpdate()
{
	struct
	{
		VeQuaternion m_kRotate;
		VeVector4D m_kTranslateScale;
	} kWorldTransform;

	static VeAngle s_kAngle;
	s_kAngle += g_pTime->GetDeltaTime() * VE_MATH_PI_4_F;

	kWorldTransform.m_kRotate.FromAngleAxis(s_kAngle, VeVector3D::UNIT_Y);
	kWorldTransform.m_kTranslateScale.Set(0, -80, 400, 1);

	VeRenderer::MappedSubresource kMapped;
	VE_ASSERT_EQ(g_pRenderer->MapRes(VeSmartPointerCast(VeRenderObject, m_spTransformBuffer), 0, VeRenderer::MAP_WRITE_DISCARD, VE_TRUE, &kMapped), true);
	VeCrazyCopy(kMapped.m_pvData, &kWorldTransform, sizeof(kWorldTransform));
	g_pRenderer->UnMapRes(VeSmartPointerCast(VeRenderObject, m_spTransformBuffer), 0);
}

void VeGraphicsTest::OnKeyPressed(VeKeyboard::InputKey eKey)
{
	if(eKey == VeKeyboard::KEY_F4)
	{
		QuitApp();
	}
}

void VeGraphicsTest::OnKeyReleased(VeKeyboard::InputKey eKey)
{
	if(eKey == VeKeyboard::KEY_C)
	{
		g_pMouse->SetCursorPosF(0.5f, 0.5f);
	}
	else if(eKey == VeKeyboard::KEY_H)
	{
		g_pMouse->SetHide(!g_pMouse->GetStateFlag(VeMouse::CUR_HIDE));
	}
	else if(eKey == VeKeyboard::KEY_L)
	{
		g_pMouse->SetLock(!g_pMouse->GetStateFlag(VeMouse::CUR_LOCK));
	}
#if defined(VE_PLATFORM_PC)
	else if(eKey == VeKeyboard::KEY_U)
	{
		g_pRenderer->ResizeWindow(1024, 768);
	}
	else if(eKey == VeKeyboard::KEY_I)
	{
		g_pRenderer->ResizeWindow(800, 600);
	}
	else if(VE_MASK_HAS_ALL(g_pKeyboard->GetModifiers(), VeKeyboard::CTRL) && eKey == VeKeyboard::KEY_F)
	{
		g_pRenderer->SetFullScreen(!g_pStartConfig->IsFullScreen());
	}
#elif defined(VE_PLATFORM_MOBILE_SIM)
	else if(eKey == VeKeyboard::KEY_U)
	{
		g_pRenderer->ResizeWindow(1024, 768);
	}
	else if(eKey == VeKeyboard::KEY_I)
	{
		g_pRenderer->ResizeWindow(960, 640);
	}
#endif
}

void VeGraphicsTest::OnMousePressed(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y)
{
	VeDebugOutput("MouseButton%d:Pressed Pos:%d,%d", eBtn, x, y);
}

void VeGraphicsTest::OnMouseReleased(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y)
{
	VeDebugOutput("MouseButton%d:Released Pos:%d,%d", eBtn, x, y);
}

void VeGraphicsTest::OnCursorMove(VeUInt16 x, VeUInt16 y)
{
	//VeDebugOutput("CursorMove:%d,%d", x, y);
}

void VeGraphicsTest::OnMouseMove(VeUInt32 u32OffsetX, VeUInt32 u32OffsetY, VeUInt32 u32OffsetZ)
{

}

void VeGraphicsTest::OnJoyStickPressed(VeUInt32 u32Button)
{
	VeDebugOutput("OnJoyStickPressed: %d", u32Button);
}

void VeGraphicsTest::OnJoyStickReleased(VeUInt32 u32Button)
{
	VeDebugOutput("OnJoyStickReleased: %d", u32Button);
}

void VeGraphicsTest::OnJoyStickAxisChanged( VeUInt32 u32Axis, VeUInt32 u32Value )
{
	VeDebugOutput("Axis%dChanged: %d", u32Axis, u32Value);
}
