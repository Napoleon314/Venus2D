////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRendererGL.h
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VE_ENABLE_GL

#include "_VeGlLoader.h"
#include "_VeRenderObjectGL.h"

#define VE_GL_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT 32
#define VE_GL_IA_VERTEX_ATTRIB_ARRAY_NUM 32

class VeRendererGL : public VeRenderer
{
public:
	VeRendererGL();

	virtual ~VeRendererGL();

	virtual API GetAPI();

	virtual VeUInt32 CheckCapability(Capability eCap);

	virtual void Init();

	virtual void Term();

	virtual void Render();

	virtual void Present();

	virtual void OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height);

	virtual void SetFullScreen(bool bEnable);

	//virtual void SetDisplay(Display& kDisplay);

	virtual void ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height);

	virtual void ResizeBuffer(VeUInt32 u32Width, VeUInt32 u32Height);

	virtual void OnActive();

	virtual void OnInactive();

	virtual void InitEditor();

	virtual void TermEditor();

	virtual void GetMatrixPerspectiveFov(VeFloat32* pf32OutMat4x4, VeFloat32 fov, VeFloat32 znear, VeFloat32 zfar) {}

	virtual const VeChar8* GetShaderName() {return NULL;}

	virtual const VeChar8* GetShaderProfile() {return NULL;}

	virtual void Render(VeRenderNode* pkNode) {}

	virtual void Process(const VeRenderProcessPtr& spProcess) {}

	void UpdateBufferSize();

	void UpdateFullScreen();

	static void Create();

protected:
	VeUInt32 m_u32RefreshRate;
	bool m_bFullScreen;
#	if defined(VE_PLATFORM_WIN)
	HDC m_hDeviceContext;
	HGLRC m_hRenderContext;
	VeInt32 m_i32DeviceHorzers;
#	elif defined(VE_PLATFORM_LINUX)
	GLXContext m_hContext;
	Atom m_hAtomDeleteWindow;
	Atom m_hAtomFullScreen;
	Atom m_hAtomState;
	struct VideoMode : public VeMemObject
	{
		VeUInt32 m_u32Width;
		VeUInt32 m_u32Height;
		VeUInt32 m_u32Rate;
	};
	VeVector<VideoMode> m_kModeList;
	VideoMode m_kOriginMode;
#	endif

	void GLInitGlobal();

	void GLTermGlobal();

	struct Description
	{
		VeString m_kVendor;
		VeString m_kRenderer;
		VeString m_kVersion;
		VeString m_kGLSLVersion;
		VeUInt16 m_u16VersionMajoy;
		VeUInt16 m_u16VersionMinor;
		VeUInt16 m_u16GLSLVersionMajoy;
		VeUInt16 m_u16GLSLVersionMinor;
		VeStringMap<VeUInt32> m_kExtensionMap;
		VeVector<VeFixedString> m_kExtensionArray;
	};

	Description m_kDescription;

	void GLCacheInit();

	void BindBuffer(VeUInt32 u32Target, VeUInt32 u32Buffer);

	void BindRenderBuffer(VeUInt32 u32Buffer);

	void UseProgram(VeUInt32 u32Program);

	void EnableVertexAttribArray(VeUInt32 u32Array);

	void DisableVertexAttribArray(VeUInt32 u32Array);

	enum Target
	{
		TARGET_ARRAY_BUFFER,
		TARGET_ELEMENT_ARRAY_BUFFER,
		TARGET_NUM
	};

	VeUInt32 m_au32BindBuffers[TARGET_NUM];
	VeUInt32 m_u32BindRenderBuffer;
	VeUInt32 m_u32UsedProgram;
	bool m_abVertexAttribArrayState[VE_GL_IA_VERTEX_ATTRIB_ARRAY_NUM];

};

#endif
