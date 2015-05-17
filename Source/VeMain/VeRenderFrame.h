////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderFrame.h
//  Version:     v1.00
//  Created:     5/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VeRenderFrameClick;

class VE_MAIN_API VeRenderFramePass : public VeObject
{
	VeDeclareRTTI;
public:
	enum Type
	{
		TYPE_CLEAR,
		TYPE_QUAD,
		TYPE_DRAW_2D,
		TYPE_DRAW_3D,
		TYPE_MAX
	};

	virtual ~VeRenderFramePass();

	VE_INLINE Type GetType();

	VE_INLINE VeRenderNode* GetNode();

	virtual void LinkToClick(VeRenderFrameClick* pkParent) = 0;

protected:
	VeRenderFramePass(Type eType);

	const Type m_eType;
	VeRenderNode* m_pkNode;

};

VeSerializableObject(VeRenderFramePass);
VeSmartPointer(VeRenderFramePass);

class VE_MAIN_API VeRenderFrameClear : public VeRenderFramePass
{
	VeDeclareRTTI;
public:
	VeRenderFrameClear();

	virtual ~VeRenderFrameClear();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	virtual void LinkToClick(VeRenderFrameClick* pkParent);

protected:
	void NoitfyDirty();

	friend class VeRenderFrameManager;
	bool m_bClearColor;
	bool m_bClearDepth;
	bool m_bClearStencil;
	VeUInt8 m_u8Stencil;
	VeFloat32 m_f32Depth;
	VeVector<VeColor> m_kColorArray;
	VeRenderNodeDataPtr m_spData;

};

VeSerializableObject(VeRenderFrameClear);
VeSmartPointer(VeRenderFrameClear);

class VE_MAIN_API VeRenderFrameDraw : public VeRenderFramePass
{
	VeDeclareRTTI;
public:
	VeRenderFrameDraw();

	virtual ~VeRenderFrameDraw();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	virtual void LinkToClick(VeRenderFrameClick* pkParent);

protected:
	VeUInt16 m_u16Start;
	VeUInt16 m_u16End;

};

class VE_MAIN_API VeRenderFrameClick : public VeObject
{
	VeDeclareRTTI;
public:
	VeRenderFrameClick();

	virtual ~VeRenderFrameClick();

	VE_INLINE VeUInt32 GetVisibilityMask();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	void Render();

protected:
	friend class VeRenderFrameManager;
	VeRenderNode* m_pkNode;
	VeFixedString m_kTarget;
	VeFixedString m_kMaterialScheme;
	VeUInt32 m_u32VisibilityMask;
	VeFloat32 m_f32LodBias;
	VeVector<VeRenderFramePassPtr> m_kPassArray;

};

VeSerializableObject(VeRenderFrameClick);
VeSmartPointer(VeRenderFrameClick);

class VE_MAIN_API VeRenderFrameTarget : public VeObject
{
	VeDeclareRTTI;
public:
	enum Type
	{
		TYPE_OUTPUT,
		TYPE_RTT,
		TYPE_MAX
	};

	enum Pool
	{
		POOL_GENERAL,
		POOL_TEMPORARY,
		POOL_MAX
	};

	virtual ~VeRenderFrameTarget();

	VE_INLINE Type GetType();

	VE_INLINE const VeChar8* GetName();

	VE_INLINE const VeRenderNodeDataPtr& GetNode();

protected:
	friend class VeRenderFrameManager;
	VeRenderFrameTarget(Type eType);

	const Type m_eType;
	VeFixedString m_kName;
	VeFixedString m_kInput;
	VeRenderNodeDataPtr m_spData;

};

VeSerializableObject(VeRenderFrameTarget);
VeSmartPointer(VeRenderFrameTarget);

class VE_MAIN_API VeRenderFrameTargetOutput : public VeRenderFrameTarget
{
	VeDeclareRTTI;
public:
	VeRenderFrameTargetOutput();

	virtual ~VeRenderFrameTargetOutput();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

};

VeSerializableObject(VeRenderFrameTargetOutput);
VeSmartPointer(VeRenderFrameTargetOutput);

class VE_MAIN_API VeRenderFrameTargetRTT : public VeRenderFrameTarget
{
	VeDeclareRTTI;
public:
	VeRenderFrameTargetRTT();

	virtual ~VeRenderFrameTargetRTT();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

protected:
	friend class VeRenderFrameManager;
	VeUInt16 m_u16Pool;
	VeUInt16 m_u16Format;
	VeString m_kWidth;
	VeString m_kHeight;

};

VeSerializableObject(VeRenderFrameTargetRTT);
VeSmartPointer(VeRenderFrameTargetRTT);

class VE_MAIN_API VeRenderFrameTechnique : public VeObject
{
	VeDeclareRTTI;
public:
	VeRenderFrameTechnique();

	virtual ~VeRenderFrameTechnique();

	VE_INLINE VeRenderNode* GetNode();

	VE_INLINE const VeChar8* GetSchemeName();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

protected:
	friend class VeRenderFrameManager;
	VeFixedString m_kScheme;
	VeVector<VeRenderFrameTargetPtr> m_kTargetArray;
	VeStringMap<VeUInt32> m_kTargetMap;
	VeVector<VeRenderFrameClickPtr> m_kClickArray;

};

VeSerializableObject(VeRenderFrameTechnique);
VeSmartPointer(VeRenderFrameTechnique);

class VE_MAIN_API VeRenderFrameUnit : public VeObject
{
	VeDeclareRTTI;
public:
	VeRenderFrameUnit();

	virtual ~VeRenderFrameUnit();

	VE_INLINE const VeChar8* GetName();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

protected:
	friend class VeRenderFrameManager;
	VeFixedString m_kName;
	VeVector<VeRenderFrameTechniquePtr> m_kTechArray;
	VeStringMap<VeUInt32> m_kTechSchemeMap;

};

VeSerializableObject(VeRenderFrameUnit);
VeSmartPointer(VeRenderFrameUnit);

class VE_MAIN_API VeRenderFrame : public VeResource
{
	VeDeclareRTTI;
public:
	VeRenderFrame(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeRenderFrame();

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

protected:
	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	void UpdateFrameUnit();

	VeXMLDocument m_kDocument;

};

VeSmartPointer(VeRenderFrame);

#define VeGetRenderFrame(name,group) VeDynamicCast(VeRenderFrame,VeGetResource(VeResource::RENDER_FRAME,name,group))

#define VeLoadRenderFrame(name,group,async) VeDynamicCast(VeRenderFrame,VeLoadResource(VeResource::RENDER_FRAME,name,group,async))

#define VeLoadRenderFrameSync(name,group) VeLoadRenderFrame(name,group,false)

#define VeLoadRenderFrameAsync(name,group) VeLoadRenderFrame(name,group,true)

class VE_MAIN_API VeRenderFrameManager : public VeSingleton<VeRenderFrameManager>
{
	VeDeclareLuaExport(VeRenderFrameManager);
public:
	class RenderTask
	{
	public:
		virtual void Render() = 0;
	};

	VeRenderFrameManager();

	~VeRenderFrameManager();

	VE_INLINE VeUInt32 GetFrameCount();

	void AddPreRenderTask(VeRefNode<RenderTask*>& kNode);

	void OnScreenSizeChanged();

	void Update(const VeChar8* pcScheme, VeVector<const VeChar8*> kUnitNameArray);

	void Render();	

protected:
	friend class VeRenderFrame;
	void UpdateFrameUnit(const VeVector<VeRenderFrameUnitPtr>& kVector);

	void UpdateTargets();

	void UpdateNode();

	VeUInt32 m_u32FrameCount;
	VeVector<VeRenderFrameUnitPtr> m_kPartArray;
	VeStringMap<VeUInt32> m_kPartNameMap;
	VeRefList<RenderTask*> m_kPreRenderTaskList;
	VeVector<VeRenderFrameTechniquePtr> m_kCurrentFrame;
	VeRenderNodeDataPtr m_spScreenTarget;

};

#define g_pRenderFrameManager VeRenderFrameManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeRenderFrame.inl"
#endif
