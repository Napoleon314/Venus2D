////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeSceneRenderable.h
//  Version:     v1.00
//  Created:     20/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_MAX_COMBINED_SPRITE (50)

class VeRenderQueue;

class VE_MAIN_API VeSceneRenderable : public VeRefObject
{
	VeDeclareRootRTTI(VeSceneRenderable);
	VeDeclareLuaRttiExport(VeSceneRenderable);
public:
	VE_INLINE VeUInt32 GetGroup();

	void SetGroup(VeUInt32 u32Group);

	virtual void Detach();

	virtual void Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask);

	virtual bool Combine(VeSceneRenderable* pkRenderable);

	virtual void LinkNodeToParent();

	virtual void BeforeRender() {}

protected:
	friend class VeSceneNode;
	VeSceneRenderable(VeUInt32 u32Group);

	virtual ~VeSceneRenderable();

	VeUInt32 m_u32Group;
	VeRefNode<VeSceneRenderable*> m_kNode;
	VeRenderNode* m_pkRenderNode;

};

VeSmartPointer(VeSceneRenderable);

class VE_MAIN_API VeSceneRenderable2D : public VeSceneRenderable
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSceneRenderable2D);
public:
	enum BlendFunc
	{
		REPLACE,
		ALPHA_BLEND,
		ALPHA_BLEND_MUL,
		ADD
	};
	VeLuaClassEnumDef(BlendFunc);

	virtual void UpdateNodeData(const VeTransform2D& kTransform, const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame) = 0;

protected:
	friend class VeSceneNode2D;
	VeSceneRenderable2D(VeUInt32 u32Group);

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_MAIN_API, VeSceneRenderable2D, BlendFunc);
}

class VE_MAIN_API VeSprite2D : public VeSceneRenderable2D
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSprite2D);
public:
	struct Vertex
	{
		VeVector2D m_kPosition;
		VeUInt16 m_u16TexX;
		VeUInt16 m_u16TexY;
		VeUInt16 m_u16TexZ;
		VeUInt16 m_u16TexW;
		VeRGBA m_kMulColor;
		VeRGBA m_kAddColor;
	};

	struct Params
	{
		VeVector4D m_kTexcoord;
		VeVector4D m_kTransform0;
		VeVector4D m_kTransform1;
		VeColor m_kMulColor;
		VeColor m_kAddColor;
	};

	VeSprite2D();

	VeSprite2D(const VeChar8* pcName);

	VeSprite2D(const VeTextureResourcePtr& spTex);

	virtual ~VeSprite2D();

	VE_INLINE void SetAnchor(const VeVector2D& kAnchor);

	VE_INLINE const VeVector2D& GetAnchor();

	VE_INLINE const VeChar8* GetFrameName();

	VE_INLINE void SetBlendFunc(BlendFunc eBlend);

	VE_INLINE BlendFunc GetBlendFunc();

	VE_INLINE VeUInt32 GetWidth();

	VE_INLINE VeUInt32 GetHeight();

	void SetTexture(const VeChar8* pcName, VeFloat32 x = 0.5f, VeFloat32 y = 0.5f);

	void SetTexture(const VeTextureResourcePtr& spTex, VeFloat32 x = 0.5f, VeFloat32 y = 0.5f);

	void SetFrameName(const VeChar8* pcName, VeFloat32 x = 0.5f, VeFloat32 y = 0.5f);

	void SetAnchor(VeFloat32 x, VeFloat32 y, VeFloat32 f32OffsetX = 0.0f, VeFloat32 f32OffsetY = 0.0f, bool bFloor = true);

	virtual bool Combine(VeSceneRenderable* pkRenderable);

	virtual void LinkNodeToParent();

	virtual void Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask);

protected:
	void Init();

	virtual void UpdateNodeData(const VeTransform2D& kTransform, const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame);

	void UpdateData();

	void UpdateRenderNodeData(const VeChar8* pcTexName);

	void UpdateBlend();

	virtual void BeforeRender();

	void SetAnchorLua(VeFloat32 x, VeFloat32 y);

	void SetAnchorLua(VeFloat32 x, VeFloat32 y, VeFloat32 f32OffsetX, VeFloat32 f32OffsetY);
	
	VeResourcePtr m_spResource;
	VeRenderNode* m_pkSpriteNode;
	BlendFunc m_eBlend;
	VeVector2D m_kAnchor;
	TextureAtlas::SpriteFrame m_kFrame;
#	ifdef VE_ENABLE_GLES2
	Vertex m_kVertex[4];
	VeOMBlendStateTick* m_pkBlendTick;
	VeIAVertexBuffer* m_pkBufferTick;
	VeDrawCall* m_pkDrawCall;
	VeUInt32 m_u32CombineCount;
#	else
	Params m_kParams;
	VeROBufferPtr m_spSingleBuffer;
	VeROBufferPtr m_spInstanceBuffer;
	VeOMBlendStateTick* m_pkBlendTick;
	VeVSCBuffer* m_pkCBufferTick;
	VeDrawCall* m_pkDrawCall;
	VeVector<VeSprite2D*> m_kCombineList;
#	endif
	VeUInt32 m_u32UpdateFrame;
	bool m_bEnable;
	bool m_bDirty;
	bool m_bTransparency;

};

VeSmartPointer(VeSprite2D);

class VE_MAIN_API VeSquareFrame : public VeSceneRenderable2D
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSquareFrame);
public:
	struct Vertex
	{
		VeVector2D m_kPosition;
		VeRGBA m_kColor;
	};

	struct Params
	{
		VeVector4D m_kTransform0;
		VeVector4D m_kTransform1;
		VeColor m_kColor;
	};

	VeSquareFrame(const VeBoundingBox2D& kRange);

	virtual ~VeSquareFrame();

	VE_INLINE void SetRange(const VeBoundingBox2D& kRange);

	VE_INLINE const VeBoundingBox2D& GetRange();

	VE_INLINE void SetBlendFunc(BlendFunc eBlend);

	VE_INLINE BlendFunc GetBlendFunc();

	virtual bool Combine(VeSceneRenderable* pkRenderable);

	virtual void LinkNodeToParent();

	virtual void Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask);

protected:
	virtual void UpdateNodeData(const VeTransform2D& kTransform, const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame);

	void UpdateBlend();

	virtual void BeforeRender();

	VeBoundingBox2D m_kRange;
	VeRenderNode* m_pkSpriteNode;
	BlendFunc m_eBlend;
#	ifdef VE_ENABLE_GLES2
	Vertex m_kVertex[4];
	VeOMBlendStateTick* m_pkBlendTick;
	VeIAVertexBuffer* m_pkBufferTick;
	VeDrawCall* m_pkDrawCall;
	VeUInt32 m_u32CombineCount;
#	else
	Params m_kParams;
	VeROBufferPtr m_spSingleBuffer;
	VeROBufferPtr m_spInstanceBuffer;
	VeOMBlendStateTick* m_pkBlendTick;
	VeVSCBuffer* m_pkCBufferTick;
	VeDrawCall* m_pkDrawCall;
	VeVector<VeSquareFrame*> m_kCombineList;
#	endif

	VeUInt32 m_u32UpdateFrame;
	bool m_bDirty;
	bool m_bTransparency;

};

VeSmartPointer(VeSquareFrame);

class VE_MAIN_API VeSquare : public VeSceneRenderable2D
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSquare);
public:
	struct Vertex
	{
		VeVector2D m_kPosition;
		VeRGBA m_kColor;
	};

	struct Params
	{
		VeVector4D m_kTransform0;
		VeVector4D m_kTransform1;
		VeColor m_kColor;
	};

	VeSquare(const VeBoundingBox2D& kRange);

	virtual ~VeSquare();

	VE_INLINE void SetRange(const VeBoundingBox2D& kRange);

	VE_INLINE const VeBoundingBox2D& GetRange();

	VE_INLINE void SetBlendFunc(BlendFunc eBlend);

	VE_INLINE BlendFunc GetBlendFunc();

	virtual bool Combine(VeSceneRenderable* pkRenderable);

	virtual void LinkNodeToParent();

	virtual void Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask);

protected:
	virtual void UpdateNodeData(const VeTransform2D& kTransform, const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame);

	void UpdateBlend();

	virtual void BeforeRender();

	VeBoundingBox2D m_kRange;
	VeRenderNode* m_pkSpriteNode;
	BlendFunc m_eBlend;
#	ifdef VE_ENABLE_GLES2
	Vertex m_kVertex[4];
	VeOMBlendStateTick* m_pkBlendTick;
	VeIAVertexBuffer* m_pkBufferTick;
	VeDrawCall* m_pkDrawCall;
	VeUInt32 m_u32CombineCount;
#	else
	Params m_kParams;
	VeROBufferPtr m_spSingleBuffer;
	VeROBufferPtr m_spInstanceBuffer;
	VeOMBlendStateTick* m_pkBlendTick;
	VeVSCBuffer* m_pkCBufferTick;
	VeDrawCall* m_pkDrawCall;
	VeVector<VeSquare*> m_kCombineList;
#	endif
	VeUInt32 m_u32UpdateFrame;
	bool m_bDirty;
	bool m_bTransparency;

};

VeSmartPointer(VeSquare);

class VE_MAIN_API VeSingleChar : public VeSceneRenderable2D
{
	VeDeclareRTTI;
public:
	struct Vertex
	{
		VeVector2D m_kPosition;
		VeFloat32 m_f32Bias;
		VeUInt16 m_u16TexX;
		VeUInt16 m_u16TexY;
		VeUInt16 m_u16TexZ;
		VeUInt16 m_u16TexW;
		VeRGBA m_kColor;
	};

	struct Params
	{
		VeVector4D m_kTransform0;
		VeVector4D m_kTransform1;
		VeVector4D m_kTransform2;
		VeColor m_kColor;
	};

	struct Pass
	{
		VeUInt32 m_u32CacheIndex;
#		ifdef VE_ENABLE_GLES2
#		else
		VeVector<Params> m_kParams;
		VeROBufferPtr m_spInstanceBuffer;
		VeVSCBuffer* m_pkCBufferTick;
		VeDrawCall* m_pkDrawCall;
#		endif
	};

	VeSingleChar();

	virtual ~VeSingleChar();

	void SetChar(VeChar16 c16Char, const VeChar8* pcFont);

	void SetChar(VeChar16 c16Char, const VeFontPtr& spFont);

	VE_INLINE VeUInt32 GetPixelWidth();

	VE_INLINE void SetBias(VeFloat32 f32Bias);

	VE_INLINE VeFloat32 GetBias();

	virtual bool Combine(VeSceneRenderable* pkRenderable);

	virtual void LinkNodeToParent();

	virtual void Visit(VeRenderQueue& kQueue, VeUInt32 u32Mask);

protected:
	void Init();

	void UpdateChar();

	virtual void UpdateNodeData(const VeTransform2D& kTransform, const VeColor& kMul, const VeColor& kAdd, VeUInt32 u32UpdateFrame);

	virtual void BeforeRender();

	VeChar16 m_c16Char;
	VeFontPtr m_spFont;
	VePair<VeInt32, VeUInt32>* m_pkChar;
	VeFloat32 m_f32Bias;
	VeRenderNode* m_pkSpriteNode;
#	ifdef VE_ENABLE_GLES2
	Vertex m_kVertex[4];
	VeIAVertexBuffer* m_pkBufferTick;
	VePSShaderResource* m_pkPSShaderResTick;
	VeVSCBuffer* m_pkCBufferTick;
	VeDrawCall* m_pkDrawCall;
	VeUInt32 m_u32CombineCount;
#	else
	Params m_kParams;
	VeROBufferPtr m_spSingleBuffer;
	VeROBufferPtr m_spInstanceBuffer;
	VeVSCBuffer* m_pkCBufferTick;
	VePSShaderResource* m_pkPSShaderResTick;
	VeDrawCall* m_pkDrawCall;
	VeVector<VeSingleChar*> m_kCombineList;
#	endif
	VeUInt32 m_u32UpdateFrame;
	bool m_bDirty;
	bool m_bTransparency;

};

VeSmartPointer(VeSingleChar);

#ifndef VE_NO_INLINE
#	include "VeSceneRenderable.inl"
#endif
