////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderNode.h
//  Version:     v1.00
//  Created:     9/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeRenderTick : public VeRefNode<VeRenderTick*>
{
public:
	enum Type
	{
		IA_INDEX_BUFFER,
		IA_INPUT_LAYOUT,
		IA_PRIMITIVE_TOPOLOGY,
		IA_VERTEX_BUFFER,

		VS_CONSTANT_BUFFER,
		VS_SAMPLER,
		VS_SHADER,
		VS_SHADER_RESOURCE,

		HS_CONSTANT_BUFFER,
		HS_SAMPLER,
		HS_SHADER,
		HS_SHADER_RESOURCE,

		DS_CONSTANT_BUFFER,
		DS_SAMPLER,
		DS_SHADER,
		DS_SHADER_RESOURCE,

		GS_CONSTANT_BUFFER,
		GS_SAMPLER,
		GS_SHADER,
		GS_SHADER_RESOURCE,

		SO_TARGET,

		RS_SCISSOR_RECT,
		RS_STATE,
		RS_VIEWPORT,

		PS_CONSTANT_BUFFER,
		PS_SAMPLER,
		PS_SHADER,
		PS_SHADER_RESOURCE,

		OM_BLEND_STATE,
		OM_DEPTH_STENCIL_STATE,
		OM_RENDER_TARGET_VIEW,
		OM_DEPTH_STENCIL_VIEW,
		OM_UNORDERED_ACCESS_VIEW,

		TYPE_MAX
	};

	VeRenderTick(Type eType);

	virtual ~VeRenderTick();

	VE_INLINE Type GetType();

protected:
	const Type m_eType;
};

class VE_MAIN_API VeVSCBuffer : public VeRenderTick
{
public:
	VeVSCBuffer(const VeChar8* pcName, VeUInt32 u32Slot);

	virtual ~VeVSCBuffer();

	VeROBufferPtr m_spBuffer;
	VeUInt32 m_u32Slot;
};

class VE_MAIN_API VeVSShader : public VeRenderTick
{
public:
	VeVSShader(const VeChar8* pcName);

	virtual ~VeVSShader();

	VeROVertexShaderPtr m_spShader;
};

class VE_MAIN_API VePSSampler : public VeRenderTick
{
public:
	VePSSampler(const VeChar8* pcName, VeUInt32 u32Slot);

	virtual ~VePSSampler();

	VeROSamplerStatePtr m_spSampler;
	VeUInt32 m_u32Slot;
};

class VE_MAIN_API VePSShader : public VeRenderTick
{
public:
	VePSShader(const VeChar8* pcName);

	virtual ~VePSShader();

	VeROPixelShaderPtr m_spShader;
};

class VE_MAIN_API VePSShaderResource : public VeRenderTick
{
public:
	VePSShaderResource(const VeChar8* pcName, VeUInt32 u32Slot);

	virtual ~VePSShaderResource();

	VeROShaderResourceViewPtr m_spShaderResourceView;
	VeUInt32 m_u32Slot;
};

class VE_MAIN_API VeOMBlendStateTick : public VeRenderTick
{
public:
	VeOMBlendStateTick(const VeChar8* pcName);

	virtual ~VeOMBlendStateTick();

	VeROBlendStatePtr m_spBlendState;
	VeFloat32 m_af32Factor[4];
	VeUInt32 m_u32SampleMask;
};

class VE_MAIN_API VeOMDepthStencilStateTick : public VeRenderTick
{
public:
	VeOMDepthStencilStateTick(const VeChar8* pcName, VeUInt32 u32StencilRef);

	virtual ~VeOMDepthStencilStateTick();

	VeRODepthStencilStatePtr m_spDepthStencilState;
	VeUInt32 m_u32StencilRef;

};

class VE_MAIN_API VeOMDepthStencilViewTick : public VeRenderTick
{
public:
	VeOMDepthStencilViewTick(const VeChar8* pcName);

	virtual ~VeOMDepthStencilViewTick();

	VeRODepthStencilViewPtr m_spDepthStencil;
};

class VE_MAIN_API VeOMRenderTargetViewTick : public VeRenderTick
{
public:
	VeOMRenderTargetViewTick(const VeChar8* pcName, VeUInt32 u32Slot);

	virtual ~VeOMRenderTargetViewTick();

	VeRORenderTargetViewPtr m_spRenderTarget;
	VeUInt32 m_u32Slot;
};

class VE_MAIN_API VeRSScissorRectTick : public VeRenderTick
{
public:
	VeRSScissorRectTick(VeInt16 x, VeInt16 y, VeInt16 w, VeInt16 h, VeUInt32 u32Slot);

	virtual ~VeRSScissorRectTick();

	VeInt16 m_i16Left;
	VeInt16 m_i16Top;
	VeInt16 m_i16Width;
	VeInt16 m_i16Height;
	VeUInt32 m_u32Slot;
};

class VE_MAIN_API VeRSViewportTick : public VeRenderTick
{
public:
	VeRSViewportTick(const VeVector4D& kViewport, VeUInt32 u32Slot);

	virtual ~VeRSViewportTick();

	VeVector4D m_kViewport;
	VeUInt32 m_u32Slot;
};

class VE_MAIN_API VeIAInputLayout : public VeRenderTick
{
public:
	VeIAInputLayout(const VeChar8* pcName);

	virtual ~VeIAInputLayout();

	VeROInputLayoutPtr m_spInputLayout;
};

class VE_MAIN_API VeIAVertexBuffer : public VeRenderTick
{
public:
	VeIAVertexBuffer(const VeChar8* pcName, VeUInt32 u32Slot, VeUInt32 u32Stride, VeUInt32 u32Offset);

	virtual ~VeIAVertexBuffer();

	VeROBufferPtr m_spBuffer;
	VeUInt32 m_u32Slot;
	VeUInt32 m_u32Stride;
	VeUInt32 m_u32Offset;
	
};

class VE_MAIN_API VeIAIndexBuffer : public VeRenderTick
{
public:
	VeIAIndexBuffer(const VeChar8* pcName, VeUInt32 u32Format);

	virtual ~VeIAIndexBuffer();

	VeROBufferPtr m_spBuffer;
	VeUInt32 m_u32Format;
};

class VE_MAIN_API VeIAPrimitiveTopology : public VeRenderTick
{
public:
	enum Topology
	{
		TOPOLOGY_UNDEFINED                    = 0,
		TOPOLOGY_POINTLIST                    = 1,
		TOPOLOGY_LINELIST                     = 2,
		TOPOLOGY_LINESTRIP                    = 3,
		TOPOLOGY_TRIANGLELIST                 = 4,
		TOPOLOGY_TRIANGLESTRIP                = 5,
		TOPOLOGY_LINELIST_ADJ                 = 10,
		TOPOLOGY_LINESTRIP_ADJ                = 11,
		TOPOLOGY_TRIANGLELIST_ADJ             = 12,
		TOPOLOGY_TRIANGLESTRIP_ADJ            = 13,
		TOPOLOGY_1_CONTROL_POINT_PATCHLIST    = 33,
		TOPOLOGY_2_CONTROL_POINT_PATCHLIST    = 34,
		TOPOLOGY_3_CONTROL_POINT_PATCHLIST    = 35,
		TOPOLOGY_4_CONTROL_POINT_PATCHLIST    = 36,
		TOPOLOGY_5_CONTROL_POINT_PATCHLIST    = 37,
		TOPOLOGY_6_CONTROL_POINT_PATCHLIST    = 38,
		TOPOLOGY_7_CONTROL_POINT_PATCHLIST    = 39,
		TOPOLOGY_8_CONTROL_POINT_PATCHLIST    = 40,
		TOPOLOGY_9_CONTROL_POINT_PATCHLIST    = 41,
		TOPOLOGY_10_CONTROL_POINT_PATCHLIST   = 42,
		TOPOLOGY_11_CONTROL_POINT_PATCHLIST   = 43,
		TOPOLOGY_12_CONTROL_POINT_PATCHLIST   = 44,
		TOPOLOGY_13_CONTROL_POINT_PATCHLIST   = 45,
		TOPOLOGY_14_CONTROL_POINT_PATCHLIST   = 46,
		TOPOLOGY_15_CONTROL_POINT_PATCHLIST   = 47,
		TOPOLOGY_16_CONTROL_POINT_PATCHLIST   = 48,
		TOPOLOGY_17_CONTROL_POINT_PATCHLIST   = 49,
		TOPOLOGY_18_CONTROL_POINT_PATCHLIST   = 50,
		TOPOLOGY_19_CONTROL_POINT_PATCHLIST   = 51,
		TOPOLOGY_20_CONTROL_POINT_PATCHLIST   = 52,
		TOPOLOGY_21_CONTROL_POINT_PATCHLIST   = 53,
		TOPOLOGY_22_CONTROL_POINT_PATCHLIST   = 54,
		TOPOLOGY_23_CONTROL_POINT_PATCHLIST   = 55,
		TOPOLOGY_24_CONTROL_POINT_PATCHLIST   = 56,
		TOPOLOGY_25_CONTROL_POINT_PATCHLIST   = 57,
		TOPOLOGY_26_CONTROL_POINT_PATCHLIST   = 58,
		TOPOLOGY_27_CONTROL_POINT_PATCHLIST   = 59,
		TOPOLOGY_28_CONTROL_POINT_PATCHLIST   = 60,
		TOPOLOGY_29_CONTROL_POINT_PATCHLIST   = 61,
		TOPOLOGY_30_CONTROL_POINT_PATCHLIST   = 62,
		TOPOLOGY_31_CONTROL_POINT_PATCHLIST   = 63,
		TOPOLOGY_32_CONTROL_POINT_PATCHLIST   = 64
	};

	VeIAPrimitiveTopology(Topology eTopology);

	virtual ~VeIAPrimitiveTopology();

	Topology m_eTopology;
};

class VE_MAIN_API VeRSState : public VeRenderTick
{
public:
	VeRSState(const VeChar8* pcName);

	virtual ~VeRSState();

	VeRORasterizeStatePtr m_spState;
};

class VE_MAIN_API VeRenderCall : public VeRefNode<VeRenderCall*>
{
public:
	enum Type
	{
		CLEAR,
		DRAW,
		DRAW_INDEXED,
		DRAW_INSTANCED,
		DRAW_INDEXED_INSTANCED,
		DRAW_INSTANCED_INDIRECT,
		DRAW_INDEXED_INSTANCED_INDIRECT,
		DRAW_AUTO
	};

	VeRenderCall(Type eType);

	virtual ~VeRenderCall();

	VE_INLINE Type GetType();

protected:
	Type m_eType;
};

class VE_MAIN_API VeClearCall : public VeRenderCall
{
public:
	VeClearCall();

	virtual ~VeClearCall();

	bool m_bClearColor;
	bool m_bClearDepth;
	bool m_bClearStencil;
	VeUInt8 m_u8Stencil;
	VeFloat32 m_f32Depth;
	VeVector<VeColor> m_kColorArray;
};

class VE_MAIN_API VeDrawCall : public VeRenderCall
{
public:
	VeDrawCall(Type eType);

	VE_INLINE void SetType(Type eType);

	union
	{
		struct
		{
			VeUInt32 m_u32VertexCount;
			VeUInt32 m_u32StartVertexLocation;
		} m_kDraw;
		struct
		{
			VeUInt32 m_u32IndexCount;
			VeUInt32 m_u32StartIndexLocation;
			VeInt32 m_i32BaseVertexLocation;
		} m_kDrawIndexed;
		struct
		{
			VeUInt32 m_u32VertexCountPerInstance;
			VeUInt32 m_u32InstanceCount;
			VeUInt32 m_u32StartVertexLocation;
			VeUInt32 m_u32StartInstanceLocation;
		} m_kDrawInstanced;
		struct
		{
			VeUInt32 m_u32IndexCountPerInstance;
			VeUInt32 m_u32InstanceCount;
			VeUInt32 m_u32StartIndexLocation;
			VeInt32 m_i32BaseVertexLocation;
			VeUInt32 m_u32StartInstanceLocation;
		} m_kDrawIndexedInstanced;
	};
	
};

class VE_MAIN_API VeRenderNodeData : public VeRefObject
{
public:
	VeRenderNodeData(const VeChar8* pcName);

	~VeRenderNodeData();

	VE_INLINE void AddRenderTick(VeRenderTick& kTick);

	VE_INLINE void AddRenderCall(VeRenderCall& kCall);

	VeFixedString m_kName;
	VeRefList<VeRenderTick*> m_kTickList;
	VeRefList<VeRenderCall*> m_kCallList;
};

VeSmartPointer(VeRenderNodeData);

class VeSceneRenderable;
 
class VE_MAIN_API VeRenderNode : public VeRefNode<VeRenderNode*>
{
public:
	VeRenderNode(const VeChar8* pcDataName = NULL);

	VeRenderNode(const VeRenderNodeDataPtr& spData);

	~VeRenderNode();

	VE_INLINE void SetName(const VeChar8* pcName);

	VE_INLINE const VeChar8* GetName();

	void SetData(const VeChar8* pcName);

	VE_INLINE void SetData(const VeRenderNodeDataPtr& spData);

	VE_INLINE const VeRenderNodeDataPtr& GetData();

	VE_INLINE void SetParent(VeRenderNode* pkParent);

	VE_INLINE VeRenderNode* GetParent();

	VE_INLINE void SetPriority(VeUInt32 u32Priority);

	VE_INLINE VeUInt32 GetPriority();

	void LinkToParent();

	VeFixedString m_kName;
	VeRenderNodeDataPtr m_spData;
	VeRenderNode* m_pkParent;
	VeUInt32 m_u32Priority;
	VeRefList<VeRenderNode*> m_kRenderChildren;
	VeSceneRenderable* m_pkRenderable;

};

class VE_MAIN_API VeRenderProcess : public VeRefObject
{
public:
	enum Type
	{
		TYPE_MSAA_RESOLVE,
		TYPE_MAX
	};

	VE_INLINE Type GetType();

	VE_INLINE const VeChar8* GetName();

	virtual bool Update(VeBinaryIStream& kStream);

	virtual void OnAdd() {}

	virtual void OnDel() {}

protected:
	VeRenderProcess(Type eType, const VeChar8* pcName);

	virtual ~VeRenderProcess();

	const Type m_eType;
	VeFixedString m_kName;

};

VeSmartPointer(VeRenderProcess);

#ifndef VE_NO_INLINE
#	include "VeRenderNode.inl"
#endif
