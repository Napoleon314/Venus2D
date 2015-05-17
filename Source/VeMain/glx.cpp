////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   glX.cpp
//  Version:     v1.00
//  Created:     by GlSpecLoader
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeGlLoader.h"

#ifdef VE_GLX

#ifdef glXGetFBConfigs
glXGetFBConfigsFunc _glXGetFBConfigs = NULL;
#endif
#ifdef glXChooseFBConfig
glXChooseFBConfigFunc _glXChooseFBConfig = NULL;
#endif
#ifdef glXGetFBConfigAttrib
glXGetFBConfigAttribFunc _glXGetFBConfigAttrib = NULL;
#endif
#ifdef glXGetVisualFromFBConfig
glXGetVisualFromFBConfigFunc _glXGetVisualFromFBConfig = NULL;
#endif
#ifdef glXCreateWindow
glXCreateWindowFunc _glXCreateWindow = NULL;
#endif
#ifdef glXDestroyWindow
glXDestroyWindowFunc _glXDestroyWindow = NULL;
#endif
#ifdef glXCreatePixmap
glXCreatePixmapFunc _glXCreatePixmap = NULL;
#endif
#ifdef glXDestroyPixmap
glXDestroyPixmapFunc _glXDestroyPixmap = NULL;
#endif
#ifdef glXCreatePbuffer
glXCreatePbufferFunc _glXCreatePbuffer = NULL;
#endif
#ifdef glXDestroyPbuffer
glXDestroyPbufferFunc _glXDestroyPbuffer = NULL;
#endif
#ifdef glXQueryDrawable
glXQueryDrawableFunc _glXQueryDrawable = NULL;
#endif
#ifdef glXCreateNewContext
glXCreateNewContextFunc _glXCreateNewContext = NULL;
#endif
#ifdef glXMakeContextCurrent
glXMakeContextCurrentFunc _glXMakeContextCurrent = NULL;
#endif
#ifdef glXGetCurrentReadDrawable
glXGetCurrentReadDrawableFunc _glXGetCurrentReadDrawable = NULL;
#endif
#ifdef glXGetCurrentDisplay
glXGetCurrentDisplayFunc _glXGetCurrentDisplay = NULL;
#endif
#ifdef glXQueryContext
glXQueryContextFunc _glXQueryContext = NULL;
#endif
#ifdef glXSelectEvent
glXSelectEventFunc _glXSelectEvent = NULL;
#endif
#ifdef glXGetSelectedEvent
glXGetSelectedEventFunc _glXGetSelectedEvent = NULL;
#endif
#ifdef glXGetProcAddress
glXGetProcAddressFunc _glXGetProcAddress = NULL;
#endif
#ifdef glXCreateContextAttribsARB
glXCreateContextAttribsARBFunc _glXCreateContextAttribsARB = NULL;
#endif
#ifdef glXSwapIntervalSGI
glXSwapIntervalSGIFunc _glXSwapIntervalSGI = NULL;
#endif
#ifdef glXGetVideoSyncSGI
glXGetVideoSyncSGIFunc _glXGetVideoSyncSGI = NULL;
#endif
#ifdef glXWaitVideoSyncSGI
glXWaitVideoSyncSGIFunc _glXWaitVideoSyncSGI = NULL;
#endif
#ifdef glXMakeCurrentReadSGI
glXMakeCurrentReadSGIFunc _glXMakeCurrentReadSGI = NULL;
#endif
#ifdef glXGetCurrentReadDrawableSGI
glXGetCurrentReadDrawableSGIFunc _glXGetCurrentReadDrawableSGI = NULL;
#endif
#ifdef glXCreateGLXVideoSourceSGIX
glXCreateGLXVideoSourceSGIXFunc _glXCreateGLXVideoSourceSGIX = NULL;
#endif
#ifdef glXDestroyGLXVideoSourceSGIX
glXDestroyGLXVideoSourceSGIXFunc _glXDestroyGLXVideoSourceSGIX = NULL;
#endif
#ifdef glXGetCurrentDisplayEXT
glXGetCurrentDisplayEXTFunc _glXGetCurrentDisplayEXT = NULL;
#endif
#ifdef glXQueryContextInfoEXT
glXQueryContextInfoEXTFunc _glXQueryContextInfoEXT = NULL;
#endif
#ifdef glXGetContextIDEXT
glXGetContextIDEXTFunc _glXGetContextIDEXT = NULL;
#endif
#ifdef glXImportContextEXT
glXImportContextEXTFunc _glXImportContextEXT = NULL;
#endif
#ifdef glXFreeContextEXT
glXFreeContextEXTFunc _glXFreeContextEXT = NULL;
#endif
#ifdef glXGetFBConfigAttribSGIX
glXGetFBConfigAttribSGIXFunc _glXGetFBConfigAttribSGIX = NULL;
#endif
#ifdef glXChooseFBConfigSGIX
glXChooseFBConfigSGIXFunc _glXChooseFBConfigSGIX = NULL;
#endif
#ifdef glXCreateGLXPixmapWithConfigSGIX
glXCreateGLXPixmapWithConfigSGIXFunc _glXCreateGLXPixmapWithConfigSGIX = NULL;
#endif
#ifdef glXCreateContextWithConfigSGIX
glXCreateContextWithConfigSGIXFunc _glXCreateContextWithConfigSGIX = NULL;
#endif
#ifdef glXGetVisualFromFBConfigSGIX
glXGetVisualFromFBConfigSGIXFunc _glXGetVisualFromFBConfigSGIX = NULL;
#endif
#ifdef glXGetFBConfigFromVisualSGIX
glXGetFBConfigFromVisualSGIXFunc _glXGetFBConfigFromVisualSGIX = NULL;
#endif
#ifdef glXCreateGLXPbufferSGIX
glXCreateGLXPbufferSGIXFunc _glXCreateGLXPbufferSGIX = NULL;
#endif
#ifdef glXDestroyGLXPbufferSGIX
glXDestroyGLXPbufferSGIXFunc _glXDestroyGLXPbufferSGIX = NULL;
#endif
#ifdef glXQueryGLXPbufferSGIX
glXQueryGLXPbufferSGIXFunc _glXQueryGLXPbufferSGIX = NULL;
#endif
#ifdef glXSelectEventSGIX
glXSelectEventSGIXFunc _glXSelectEventSGIX = NULL;
#endif
#ifdef glXGetSelectedEventSGIX
glXGetSelectedEventSGIXFunc _glXGetSelectedEventSGIX = NULL;
#endif
#ifdef glXCushionSGI
glXCushionSGIFunc _glXCushionSGI = NULL;
#endif
#ifdef glXBindChannelToWindowSGIX
glXBindChannelToWindowSGIXFunc _glXBindChannelToWindowSGIX = NULL;
#endif
#ifdef glXChannelRectSGIX
glXChannelRectSGIXFunc _glXChannelRectSGIX = NULL;
#endif
#ifdef glXQueryChannelRectSGIX
glXQueryChannelRectSGIXFunc _glXQueryChannelRectSGIX = NULL;
#endif
#ifdef glXQueryChannelDeltasSGIX
glXQueryChannelDeltasSGIXFunc _glXQueryChannelDeltasSGIX = NULL;
#endif
#ifdef glXChannelRectSyncSGIX
glXChannelRectSyncSGIXFunc _glXChannelRectSyncSGIX = NULL;
#endif
#ifdef glXAssociateDMPbufferSGIX
glXAssociateDMPbufferSGIXFunc _glXAssociateDMPbufferSGIX = NULL;
#endif
#ifdef glXJoinSwapGroupSGIX
glXJoinSwapGroupSGIXFunc _glXJoinSwapGroupSGIX = NULL;
#endif
#ifdef glXBindSwapBarrierSGIX
glXBindSwapBarrierSGIXFunc _glXBindSwapBarrierSGIX = NULL;
#endif
#ifdef glXQueryMaxSwapBarriersSGIX
glXQueryMaxSwapBarriersSGIXFunc _glXQueryMaxSwapBarriersSGIX = NULL;
#endif
#ifdef glXGetTransparentIndexSUN
glXGetTransparentIndexSUNFunc _glXGetTransparentIndexSUN = NULL;
#endif
#ifdef glXCopySubBufferMESA
glXCopySubBufferMESAFunc _glXCopySubBufferMESA = NULL;
#endif
#ifdef glXCreateGLXPixmapMESA
glXCreateGLXPixmapMESAFunc _glXCreateGLXPixmapMESA = NULL;
#endif
#ifdef glXReleaseBuffersMESA
glXReleaseBuffersMESAFunc _glXReleaseBuffersMESA = NULL;
#endif
#ifdef glXSet3DfxModeMESA
glXSet3DfxModeMESAFunc _glXSet3DfxModeMESA = NULL;
#endif
#ifdef glXGetSyncValuesOML
glXGetSyncValuesOMLFunc _glXGetSyncValuesOML = NULL;
#endif
#ifdef glXGetMscRateOML
glXGetMscRateOMLFunc _glXGetMscRateOML = NULL;
#endif
#ifdef glXSwapBuffersMscOML
glXSwapBuffersMscOMLFunc _glXSwapBuffersMscOML = NULL;
#endif
#ifdef glXWaitForMscOML
glXWaitForMscOMLFunc _glXWaitForMscOML = NULL;
#endif
#ifdef glXWaitForSbcOML
glXWaitForSbcOMLFunc _glXWaitForSbcOML = NULL;
#endif
#ifdef glXQueryHyperpipeNetworkSGIX
glXQueryHyperpipeNetworkSGIXFunc _glXQueryHyperpipeNetworkSGIX = NULL;
#endif
#ifdef glXHyperpipeConfigSGIX
glXHyperpipeConfigSGIXFunc _glXHyperpipeConfigSGIX = NULL;
#endif
#ifdef glXQueryHyperpipeConfigSGIX
glXQueryHyperpipeConfigSGIXFunc _glXQueryHyperpipeConfigSGIX = NULL;
#endif
#ifdef glXDestroyHyperpipeConfigSGIX
glXDestroyHyperpipeConfigSGIXFunc _glXDestroyHyperpipeConfigSGIX = NULL;
#endif
#ifdef glXBindHyperpipeSGIX
glXBindHyperpipeSGIXFunc _glXBindHyperpipeSGIX = NULL;
#endif
#ifdef glXQueryHyperpipeBestAttribSGIX
glXQueryHyperpipeBestAttribSGIXFunc _glXQueryHyperpipeBestAttribSGIX = NULL;
#endif
#ifdef glXHyperpipeAttribSGIX
glXHyperpipeAttribSGIXFunc _glXHyperpipeAttribSGIX = NULL;
#endif
#ifdef glXQueryHyperpipeAttribSGIX
glXQueryHyperpipeAttribSGIXFunc _glXQueryHyperpipeAttribSGIX = NULL;
#endif
#ifdef glXGetAGPOffsetMESA
glXGetAGPOffsetMESAFunc _glXGetAGPOffsetMESA = NULL;
#endif
#ifdef glXBindTexImageEXT
glXBindTexImageEXTFunc _glXBindTexImageEXT = NULL;
#endif
#ifdef glXReleaseTexImageEXT
glXReleaseTexImageEXTFunc _glXReleaseTexImageEXT = NULL;
#endif
#ifdef glXEnumerateVideoDevicesNV
glXEnumerateVideoDevicesNVFunc _glXEnumerateVideoDevicesNV = NULL;
#endif
#ifdef glXBindVideoDeviceNV
glXBindVideoDeviceNVFunc _glXBindVideoDeviceNV = NULL;
#endif
#ifdef glXGetVideoDeviceNV
glXGetVideoDeviceNVFunc _glXGetVideoDeviceNV = NULL;
#endif
#ifdef glXReleaseVideoDeviceNV
glXReleaseVideoDeviceNVFunc _glXReleaseVideoDeviceNV = NULL;
#endif
#ifdef glXBindVideoImageNV
glXBindVideoImageNVFunc _glXBindVideoImageNV = NULL;
#endif
#ifdef glXReleaseVideoImageNV
glXReleaseVideoImageNVFunc _glXReleaseVideoImageNV = NULL;
#endif
#ifdef glXSendPbufferToVideoNV
glXSendPbufferToVideoNVFunc _glXSendPbufferToVideoNV = NULL;
#endif
#ifdef glXGetVideoInfoNV
glXGetVideoInfoNVFunc _glXGetVideoInfoNV = NULL;
#endif
#ifdef glXJoinSwapGroupNV
glXJoinSwapGroupNVFunc _glXJoinSwapGroupNV = NULL;
#endif
#ifdef glXBindSwapBarrierNV
glXBindSwapBarrierNVFunc _glXBindSwapBarrierNV = NULL;
#endif
#ifdef glXQuerySwapGroupNV
glXQuerySwapGroupNVFunc _glXQuerySwapGroupNV = NULL;
#endif
#ifdef glXQueryMaxSwapGroupsNV
glXQueryMaxSwapGroupsNVFunc _glXQueryMaxSwapGroupsNV = NULL;
#endif
#ifdef glXQueryFrameCountNV
glXQueryFrameCountNVFunc _glXQueryFrameCountNV = NULL;
#endif
#ifdef glXResetFrameCountNV
glXResetFrameCountNVFunc _glXResetFrameCountNV = NULL;
#endif
#ifdef glXBindVideoCaptureDeviceNV
glXBindVideoCaptureDeviceNVFunc _glXBindVideoCaptureDeviceNV = NULL;
#endif
#ifdef glXEnumerateVideoCaptureDevicesNV
glXEnumerateVideoCaptureDevicesNVFunc _glXEnumerateVideoCaptureDevicesNV = NULL;
#endif
#ifdef glXLockVideoCaptureDeviceNV
glXLockVideoCaptureDeviceNVFunc _glXLockVideoCaptureDeviceNV = NULL;
#endif
#ifdef glXQueryVideoCaptureDeviceNV
glXQueryVideoCaptureDeviceNVFunc _glXQueryVideoCaptureDeviceNV = NULL;
#endif
#ifdef glXReleaseVideoCaptureDeviceNV
glXReleaseVideoCaptureDeviceNVFunc _glXReleaseVideoCaptureDeviceNV = NULL;
#endif
#ifdef glXSwapIntervalEXT
glXSwapIntervalEXTFunc _glXSwapIntervalEXT = NULL;
#endif
#ifdef glXCopyImageSubDataNV
glXCopyImageSubDataNVFunc _glXCopyImageSubDataNV = NULL;
#endif
#ifdef glXRender
glXRenderFunc _glXRender = NULL;
#endif
#ifdef glXRenderLarge
glXRenderLargeFunc _glXRenderLarge = NULL;
#endif
#ifdef glXDestroyContext
glXDestroyContextFunc _glXDestroyContext = NULL;
#endif
#ifdef glXIsDirect
glXIsDirectFunc _glXIsDirect = NULL;
#endif
#ifdef glXQueryVersion
glXQueryVersionFunc _glXQueryVersion = NULL;
#endif
#ifdef glXWaitGL
glXWaitGLFunc _glXWaitGL = NULL;
#endif
#ifdef glXWaitX
glXWaitXFunc _glXWaitX = NULL;
#endif
#ifdef glXCopyContext
glXCopyContextFunc _glXCopyContext = NULL;
#endif
#ifdef glXUseXFont
glXUseXFontFunc _glXUseXFont = NULL;
#endif
#ifdef glXCreateGLXPixmap
glXCreateGLXPixmapFunc _glXCreateGLXPixmap = NULL;
#endif
#ifdef glXGetVisualConfigs
glXGetVisualConfigsFunc _glXGetVisualConfigs = NULL;
#endif
#ifdef glXDestroyGLXPixmap
glXDestroyGLXPixmapFunc _glXDestroyGLXPixmap = NULL;
#endif
#ifdef glXVendorPrivate
glXVendorPrivateFunc _glXVendorPrivate = NULL;
#endif
#ifdef glXVendorPrivateWithReply
glXVendorPrivateWithReplyFunc _glXVendorPrivateWithReply = NULL;
#endif
#ifdef glXQueryExtensionsString
glXQueryExtensionsStringFunc _glXQueryExtensionsString = NULL;
#endif
#ifdef glXQueryServerString
glXQueryServerStringFunc _glXQueryServerString = NULL;
#endif
#ifdef glXClientInfo
glXClientInfoFunc _glXClientInfo = NULL;
#endif
#ifdef glXGetDrawableAttributes
glXGetDrawableAttributesFunc _glXGetDrawableAttributes = NULL;
#endif
#ifdef glXChangeDrawableAttributes
glXChangeDrawableAttributesFunc _glXChangeDrawableAttributes = NULL;
#endif
#ifdef glXGetFBConfigsSGIX
glXGetFBConfigsSGIXFunc _glXGetFBConfigsSGIX = NULL;
#endif
#ifdef glXChangeDrawableAttributesSGIX
glXChangeDrawableAttributesSGIXFunc _glXChangeDrawableAttributesSGIX = NULL;
#endif
#ifdef glXGetDrawableAttributesSGIX
glXGetDrawableAttributesSGIXFunc _glXGetDrawableAttributesSGIX = NULL;
#endif

void glXFuncload()
{
#	ifdef glXGetFBConfigs
	_glXGetFBConfigs = (glXGetFBConfigsFunc)glXGetFunction("glXGetFBConfigs");
#	endif
#	ifdef glXChooseFBConfig
	_glXChooseFBConfig = (glXChooseFBConfigFunc)glXGetFunction("glXChooseFBConfig");
#	endif
#	ifdef glXGetFBConfigAttrib
	_glXGetFBConfigAttrib = (glXGetFBConfigAttribFunc)glXGetFunction("glXGetFBConfigAttrib");
#	endif
#	ifdef glXGetVisualFromFBConfig
	_glXGetVisualFromFBConfig = (glXGetVisualFromFBConfigFunc)glXGetFunction("glXGetVisualFromFBConfig");
#	endif
#	ifdef glXCreateWindow
	_glXCreateWindow = (glXCreateWindowFunc)glXGetFunction("glXCreateWindow");
#	endif
#	ifdef glXDestroyWindow
	_glXDestroyWindow = (glXDestroyWindowFunc)glXGetFunction("glXDestroyWindow");
#	endif
#	ifdef glXCreatePixmap
	_glXCreatePixmap = (glXCreatePixmapFunc)glXGetFunction("glXCreatePixmap");
#	endif
#	ifdef glXDestroyPixmap
	_glXDestroyPixmap = (glXDestroyPixmapFunc)glXGetFunction("glXDestroyPixmap");
#	endif
#	ifdef glXCreatePbuffer
	_glXCreatePbuffer = (glXCreatePbufferFunc)glXGetFunction("glXCreatePbuffer");
#	endif
#	ifdef glXDestroyPbuffer
	_glXDestroyPbuffer = (glXDestroyPbufferFunc)glXGetFunction("glXDestroyPbuffer");
#	endif
#	ifdef glXQueryDrawable
	_glXQueryDrawable = (glXQueryDrawableFunc)glXGetFunction("glXQueryDrawable");
#	endif
#	ifdef glXCreateNewContext
	_glXCreateNewContext = (glXCreateNewContextFunc)glXGetFunction("glXCreateNewContext");
#	endif
#	ifdef glXMakeContextCurrent
	_glXMakeContextCurrent = (glXMakeContextCurrentFunc)glXGetFunction("glXMakeContextCurrent");
#	endif
#	ifdef glXGetCurrentReadDrawable
	_glXGetCurrentReadDrawable = (glXGetCurrentReadDrawableFunc)glXGetFunction("glXGetCurrentReadDrawable");
#	endif
#	ifdef glXGetCurrentDisplay
	_glXGetCurrentDisplay = (glXGetCurrentDisplayFunc)glXGetFunction("glXGetCurrentDisplay");
#	endif
#	ifdef glXQueryContext
	_glXQueryContext = (glXQueryContextFunc)glXGetFunction("glXQueryContext");
#	endif
#	ifdef glXSelectEvent
	_glXSelectEvent = (glXSelectEventFunc)glXGetFunction("glXSelectEvent");
#	endif
#	ifdef glXGetSelectedEvent
	_glXGetSelectedEvent = (glXGetSelectedEventFunc)glXGetFunction("glXGetSelectedEvent");
#	endif
#	ifdef glXGetProcAddress
	_glXGetProcAddress = (glXGetProcAddressFunc)glXGetFunction("glXGetProcAddress");
#	endif
#	ifdef glXCreateContextAttribsARB
	_glXCreateContextAttribsARB = (glXCreateContextAttribsARBFunc)glXGetFunction("glXCreateContextAttribsARB");
#	endif
#	ifdef glXSwapIntervalSGI
	_glXSwapIntervalSGI = (glXSwapIntervalSGIFunc)glXGetFunction("glXSwapIntervalSGI");
#	endif
#	ifdef glXGetVideoSyncSGI
	_glXGetVideoSyncSGI = (glXGetVideoSyncSGIFunc)glXGetFunction("glXGetVideoSyncSGI");
#	endif
#	ifdef glXWaitVideoSyncSGI
	_glXWaitVideoSyncSGI = (glXWaitVideoSyncSGIFunc)glXGetFunction("glXWaitVideoSyncSGI");
#	endif
#	ifdef glXMakeCurrentReadSGI
	_glXMakeCurrentReadSGI = (glXMakeCurrentReadSGIFunc)glXGetFunction("glXMakeCurrentReadSGI");
#	endif
#	ifdef glXGetCurrentReadDrawableSGI
	_glXGetCurrentReadDrawableSGI = (glXGetCurrentReadDrawableSGIFunc)glXGetFunction("glXGetCurrentReadDrawableSGI");
#	endif
#	ifdef glXCreateGLXVideoSourceSGIX
	_glXCreateGLXVideoSourceSGIX = (glXCreateGLXVideoSourceSGIXFunc)glXGetFunction("glXCreateGLXVideoSourceSGIX");
#	endif
#	ifdef glXDestroyGLXVideoSourceSGIX
	_glXDestroyGLXVideoSourceSGIX = (glXDestroyGLXVideoSourceSGIXFunc)glXGetFunction("glXDestroyGLXVideoSourceSGIX");
#	endif
#	ifdef glXGetCurrentDisplayEXT
	_glXGetCurrentDisplayEXT = (glXGetCurrentDisplayEXTFunc)glXGetFunction("glXGetCurrentDisplayEXT");
#	endif
#	ifdef glXQueryContextInfoEXT
	_glXQueryContextInfoEXT = (glXQueryContextInfoEXTFunc)glXGetFunction("glXQueryContextInfoEXT");
#	endif
#	ifdef glXGetContextIDEXT
	_glXGetContextIDEXT = (glXGetContextIDEXTFunc)glXGetFunction("glXGetContextIDEXT");
#	endif
#	ifdef glXImportContextEXT
	_glXImportContextEXT = (glXImportContextEXTFunc)glXGetFunction("glXImportContextEXT");
#	endif
#	ifdef glXFreeContextEXT
	_glXFreeContextEXT = (glXFreeContextEXTFunc)glXGetFunction("glXFreeContextEXT");
#	endif
#	ifdef glXGetFBConfigAttribSGIX
	_glXGetFBConfigAttribSGIX = (glXGetFBConfigAttribSGIXFunc)glXGetFunction("glXGetFBConfigAttribSGIX");
#	endif
#	ifdef glXChooseFBConfigSGIX
	_glXChooseFBConfigSGIX = (glXChooseFBConfigSGIXFunc)glXGetFunction("glXChooseFBConfigSGIX");
#	endif
#	ifdef glXCreateGLXPixmapWithConfigSGIX
	_glXCreateGLXPixmapWithConfigSGIX = (glXCreateGLXPixmapWithConfigSGIXFunc)glXGetFunction("glXCreateGLXPixmapWithConfigSGIX");
#	endif
#	ifdef glXCreateContextWithConfigSGIX
	_glXCreateContextWithConfigSGIX = (glXCreateContextWithConfigSGIXFunc)glXGetFunction("glXCreateContextWithConfigSGIX");
#	endif
#	ifdef glXGetVisualFromFBConfigSGIX
	_glXGetVisualFromFBConfigSGIX = (glXGetVisualFromFBConfigSGIXFunc)glXGetFunction("glXGetVisualFromFBConfigSGIX");
#	endif
#	ifdef glXGetFBConfigFromVisualSGIX
	_glXGetFBConfigFromVisualSGIX = (glXGetFBConfigFromVisualSGIXFunc)glXGetFunction("glXGetFBConfigFromVisualSGIX");
#	endif
#	ifdef glXCreateGLXPbufferSGIX
	_glXCreateGLXPbufferSGIX = (glXCreateGLXPbufferSGIXFunc)glXGetFunction("glXCreateGLXPbufferSGIX");
#	endif
#	ifdef glXDestroyGLXPbufferSGIX
	_glXDestroyGLXPbufferSGIX = (glXDestroyGLXPbufferSGIXFunc)glXGetFunction("glXDestroyGLXPbufferSGIX");
#	endif
#	ifdef glXQueryGLXPbufferSGIX
	_glXQueryGLXPbufferSGIX = (glXQueryGLXPbufferSGIXFunc)glXGetFunction("glXQueryGLXPbufferSGIX");
#	endif
#	ifdef glXSelectEventSGIX
	_glXSelectEventSGIX = (glXSelectEventSGIXFunc)glXGetFunction("glXSelectEventSGIX");
#	endif
#	ifdef glXGetSelectedEventSGIX
	_glXGetSelectedEventSGIX = (glXGetSelectedEventSGIXFunc)glXGetFunction("glXGetSelectedEventSGIX");
#	endif
#	ifdef glXCushionSGI
	_glXCushionSGI = (glXCushionSGIFunc)glXGetFunction("glXCushionSGI");
#	endif
#	ifdef glXBindChannelToWindowSGIX
	_glXBindChannelToWindowSGIX = (glXBindChannelToWindowSGIXFunc)glXGetFunction("glXBindChannelToWindowSGIX");
#	endif
#	ifdef glXChannelRectSGIX
	_glXChannelRectSGIX = (glXChannelRectSGIXFunc)glXGetFunction("glXChannelRectSGIX");
#	endif
#	ifdef glXQueryChannelRectSGIX
	_glXQueryChannelRectSGIX = (glXQueryChannelRectSGIXFunc)glXGetFunction("glXQueryChannelRectSGIX");
#	endif
#	ifdef glXQueryChannelDeltasSGIX
	_glXQueryChannelDeltasSGIX = (glXQueryChannelDeltasSGIXFunc)glXGetFunction("glXQueryChannelDeltasSGIX");
#	endif
#	ifdef glXChannelRectSyncSGIX
	_glXChannelRectSyncSGIX = (glXChannelRectSyncSGIXFunc)glXGetFunction("glXChannelRectSyncSGIX");
#	endif
#	ifdef glXAssociateDMPbufferSGIX
	_glXAssociateDMPbufferSGIX = (glXAssociateDMPbufferSGIXFunc)glXGetFunction("glXAssociateDMPbufferSGIX");
#	endif
#	ifdef glXJoinSwapGroupSGIX
	_glXJoinSwapGroupSGIX = (glXJoinSwapGroupSGIXFunc)glXGetFunction("glXJoinSwapGroupSGIX");
#	endif
#	ifdef glXBindSwapBarrierSGIX
	_glXBindSwapBarrierSGIX = (glXBindSwapBarrierSGIXFunc)glXGetFunction("glXBindSwapBarrierSGIX");
#	endif
#	ifdef glXQueryMaxSwapBarriersSGIX
	_glXQueryMaxSwapBarriersSGIX = (glXQueryMaxSwapBarriersSGIXFunc)glXGetFunction("glXQueryMaxSwapBarriersSGIX");
#	endif
#	ifdef glXGetTransparentIndexSUN
	_glXGetTransparentIndexSUN = (glXGetTransparentIndexSUNFunc)glXGetFunction("glXGetTransparentIndexSUN");
#	endif
#	ifdef glXCopySubBufferMESA
	_glXCopySubBufferMESA = (glXCopySubBufferMESAFunc)glXGetFunction("glXCopySubBufferMESA");
#	endif
#	ifdef glXCreateGLXPixmapMESA
	_glXCreateGLXPixmapMESA = (glXCreateGLXPixmapMESAFunc)glXGetFunction("glXCreateGLXPixmapMESA");
#	endif
#	ifdef glXReleaseBuffersMESA
	_glXReleaseBuffersMESA = (glXReleaseBuffersMESAFunc)glXGetFunction("glXReleaseBuffersMESA");
#	endif
#	ifdef glXSet3DfxModeMESA
	_glXSet3DfxModeMESA = (glXSet3DfxModeMESAFunc)glXGetFunction("glXSet3DfxModeMESA");
#	endif
#	ifdef glXGetSyncValuesOML
	_glXGetSyncValuesOML = (glXGetSyncValuesOMLFunc)glXGetFunction("glXGetSyncValuesOML");
#	endif
#	ifdef glXGetMscRateOML
	_glXGetMscRateOML = (glXGetMscRateOMLFunc)glXGetFunction("glXGetMscRateOML");
#	endif
#	ifdef glXSwapBuffersMscOML
	_glXSwapBuffersMscOML = (glXSwapBuffersMscOMLFunc)glXGetFunction("glXSwapBuffersMscOML");
#	endif
#	ifdef glXWaitForMscOML
	_glXWaitForMscOML = (glXWaitForMscOMLFunc)glXGetFunction("glXWaitForMscOML");
#	endif
#	ifdef glXWaitForSbcOML
	_glXWaitForSbcOML = (glXWaitForSbcOMLFunc)glXGetFunction("glXWaitForSbcOML");
#	endif
#	ifdef glXQueryHyperpipeNetworkSGIX
	_glXQueryHyperpipeNetworkSGIX = (glXQueryHyperpipeNetworkSGIXFunc)glXGetFunction("glXQueryHyperpipeNetworkSGIX");
#	endif
#	ifdef glXHyperpipeConfigSGIX
	_glXHyperpipeConfigSGIX = (glXHyperpipeConfigSGIXFunc)glXGetFunction("glXHyperpipeConfigSGIX");
#	endif
#	ifdef glXQueryHyperpipeConfigSGIX
	_glXQueryHyperpipeConfigSGIX = (glXQueryHyperpipeConfigSGIXFunc)glXGetFunction("glXQueryHyperpipeConfigSGIX");
#	endif
#	ifdef glXDestroyHyperpipeConfigSGIX
	_glXDestroyHyperpipeConfigSGIX = (glXDestroyHyperpipeConfigSGIXFunc)glXGetFunction("glXDestroyHyperpipeConfigSGIX");
#	endif
#	ifdef glXBindHyperpipeSGIX
	_glXBindHyperpipeSGIX = (glXBindHyperpipeSGIXFunc)glXGetFunction("glXBindHyperpipeSGIX");
#	endif
#	ifdef glXQueryHyperpipeBestAttribSGIX
	_glXQueryHyperpipeBestAttribSGIX = (glXQueryHyperpipeBestAttribSGIXFunc)glXGetFunction("glXQueryHyperpipeBestAttribSGIX");
#	endif
#	ifdef glXHyperpipeAttribSGIX
	_glXHyperpipeAttribSGIX = (glXHyperpipeAttribSGIXFunc)glXGetFunction("glXHyperpipeAttribSGIX");
#	endif
#	ifdef glXQueryHyperpipeAttribSGIX
	_glXQueryHyperpipeAttribSGIX = (glXQueryHyperpipeAttribSGIXFunc)glXGetFunction("glXQueryHyperpipeAttribSGIX");
#	endif
#	ifdef glXGetAGPOffsetMESA
	_glXGetAGPOffsetMESA = (glXGetAGPOffsetMESAFunc)glXGetFunction("glXGetAGPOffsetMESA");
#	endif
#	ifdef glXBindTexImageEXT
	_glXBindTexImageEXT = (glXBindTexImageEXTFunc)glXGetFunction("glXBindTexImageEXT");
#	endif
#	ifdef glXReleaseTexImageEXT
	_glXReleaseTexImageEXT = (glXReleaseTexImageEXTFunc)glXGetFunction("glXReleaseTexImageEXT");
#	endif
#	ifdef glXEnumerateVideoDevicesNV
	_glXEnumerateVideoDevicesNV = (glXEnumerateVideoDevicesNVFunc)glXGetFunction("glXEnumerateVideoDevicesNV");
#	endif
#	ifdef glXBindVideoDeviceNV
	_glXBindVideoDeviceNV = (glXBindVideoDeviceNVFunc)glXGetFunction("glXBindVideoDeviceNV");
#	endif
#	ifdef glXGetVideoDeviceNV
	_glXGetVideoDeviceNV = (glXGetVideoDeviceNVFunc)glXGetFunction("glXGetVideoDeviceNV");
#	endif
#	ifdef glXReleaseVideoDeviceNV
	_glXReleaseVideoDeviceNV = (glXReleaseVideoDeviceNVFunc)glXGetFunction("glXReleaseVideoDeviceNV");
#	endif
#	ifdef glXBindVideoImageNV
	_glXBindVideoImageNV = (glXBindVideoImageNVFunc)glXGetFunction("glXBindVideoImageNV");
#	endif
#	ifdef glXReleaseVideoImageNV
	_glXReleaseVideoImageNV = (glXReleaseVideoImageNVFunc)glXGetFunction("glXReleaseVideoImageNV");
#	endif
#	ifdef glXSendPbufferToVideoNV
	_glXSendPbufferToVideoNV = (glXSendPbufferToVideoNVFunc)glXGetFunction("glXSendPbufferToVideoNV");
#	endif
#	ifdef glXGetVideoInfoNV
	_glXGetVideoInfoNV = (glXGetVideoInfoNVFunc)glXGetFunction("glXGetVideoInfoNV");
#	endif
#	ifdef glXJoinSwapGroupNV
	_glXJoinSwapGroupNV = (glXJoinSwapGroupNVFunc)glXGetFunction("glXJoinSwapGroupNV");
#	endif
#	ifdef glXBindSwapBarrierNV
	_glXBindSwapBarrierNV = (glXBindSwapBarrierNVFunc)glXGetFunction("glXBindSwapBarrierNV");
#	endif
#	ifdef glXQuerySwapGroupNV
	_glXQuerySwapGroupNV = (glXQuerySwapGroupNVFunc)glXGetFunction("glXQuerySwapGroupNV");
#	endif
#	ifdef glXQueryMaxSwapGroupsNV
	_glXQueryMaxSwapGroupsNV = (glXQueryMaxSwapGroupsNVFunc)glXGetFunction("glXQueryMaxSwapGroupsNV");
#	endif
#	ifdef glXQueryFrameCountNV
	_glXQueryFrameCountNV = (glXQueryFrameCountNVFunc)glXGetFunction("glXQueryFrameCountNV");
#	endif
#	ifdef glXResetFrameCountNV
	_glXResetFrameCountNV = (glXResetFrameCountNVFunc)glXGetFunction("glXResetFrameCountNV");
#	endif
#	ifdef glXBindVideoCaptureDeviceNV
	_glXBindVideoCaptureDeviceNV = (glXBindVideoCaptureDeviceNVFunc)glXGetFunction("glXBindVideoCaptureDeviceNV");
#	endif
#	ifdef glXEnumerateVideoCaptureDevicesNV
	_glXEnumerateVideoCaptureDevicesNV = (glXEnumerateVideoCaptureDevicesNVFunc)glXGetFunction("glXEnumerateVideoCaptureDevicesNV");
#	endif
#	ifdef glXLockVideoCaptureDeviceNV
	_glXLockVideoCaptureDeviceNV = (glXLockVideoCaptureDeviceNVFunc)glXGetFunction("glXLockVideoCaptureDeviceNV");
#	endif
#	ifdef glXQueryVideoCaptureDeviceNV
	_glXQueryVideoCaptureDeviceNV = (glXQueryVideoCaptureDeviceNVFunc)glXGetFunction("glXQueryVideoCaptureDeviceNV");
#	endif
#	ifdef glXReleaseVideoCaptureDeviceNV
	_glXReleaseVideoCaptureDeviceNV = (glXReleaseVideoCaptureDeviceNVFunc)glXGetFunction("glXReleaseVideoCaptureDeviceNV");
#	endif
#	ifdef glXSwapIntervalEXT
	_glXSwapIntervalEXT = (glXSwapIntervalEXTFunc)glXGetFunction("glXSwapIntervalEXT");
#	endif
#	ifdef glXCopyImageSubDataNV
	_glXCopyImageSubDataNV = (glXCopyImageSubDataNVFunc)glXGetFunction("glXCopyImageSubDataNV");
#	endif
#	ifdef glXRender
	_glXRender = (glXRenderFunc)glXGetFunction("glXRender");
#	endif
#	ifdef glXRenderLarge
	_glXRenderLarge = (glXRenderLargeFunc)glXGetFunction("glXRenderLarge");
#	endif
#	ifdef glXDestroyContext
	_glXDestroyContext = (glXDestroyContextFunc)glXGetFunction("glXDestroyContext");
#	endif
#	ifdef glXIsDirect
	_glXIsDirect = (glXIsDirectFunc)glXGetFunction("glXIsDirect");
#	endif
#	ifdef glXQueryVersion
	_glXQueryVersion = (glXQueryVersionFunc)glXGetFunction("glXQueryVersion");
#	endif
#	ifdef glXWaitGL
	_glXWaitGL = (glXWaitGLFunc)glXGetFunction("glXWaitGL");
#	endif
#	ifdef glXWaitX
	_glXWaitX = (glXWaitXFunc)glXGetFunction("glXWaitX");
#	endif
#	ifdef glXCopyContext
	_glXCopyContext = (glXCopyContextFunc)glXGetFunction("glXCopyContext");
#	endif
#	ifdef glXUseXFont
	_glXUseXFont = (glXUseXFontFunc)glXGetFunction("glXUseXFont");
#	endif
#	ifdef glXCreateGLXPixmap
	_glXCreateGLXPixmap = (glXCreateGLXPixmapFunc)glXGetFunction("glXCreateGLXPixmap");
#	endif
#	ifdef glXGetVisualConfigs
	_glXGetVisualConfigs = (glXGetVisualConfigsFunc)glXGetFunction("glXGetVisualConfigs");
#	endif
#	ifdef glXDestroyGLXPixmap
	_glXDestroyGLXPixmap = (glXDestroyGLXPixmapFunc)glXGetFunction("glXDestroyGLXPixmap");
#	endif
#	ifdef glXVendorPrivate
	_glXVendorPrivate = (glXVendorPrivateFunc)glXGetFunction("glXVendorPrivate");
#	endif
#	ifdef glXVendorPrivateWithReply
	_glXVendorPrivateWithReply = (glXVendorPrivateWithReplyFunc)glXGetFunction("glXVendorPrivateWithReply");
#	endif
#	ifdef glXQueryExtensionsString
	_glXQueryExtensionsString = (glXQueryExtensionsStringFunc)glXGetFunction("glXQueryExtensionsString");
#	endif
#	ifdef glXQueryServerString
	_glXQueryServerString = (glXQueryServerStringFunc)glXGetFunction("glXQueryServerString");
#	endif
#	ifdef glXClientInfo
	_glXClientInfo = (glXClientInfoFunc)glXGetFunction("glXClientInfo");
#	endif
#	ifdef glXGetDrawableAttributes
	_glXGetDrawableAttributes = (glXGetDrawableAttributesFunc)glXGetFunction("glXGetDrawableAttributes");
#	endif
#	ifdef glXChangeDrawableAttributes
	_glXChangeDrawableAttributes = (glXChangeDrawableAttributesFunc)glXGetFunction("glXChangeDrawableAttributes");
#	endif
#	ifdef glXGetFBConfigsSGIX
	_glXGetFBConfigsSGIX = (glXGetFBConfigsSGIXFunc)glXGetFunction("glXGetFBConfigsSGIX");
#	endif
#	ifdef glXChangeDrawableAttributesSGIX
	_glXChangeDrawableAttributesSGIX = (glXChangeDrawableAttributesSGIXFunc)glXGetFunction("glXChangeDrawableAttributesSGIX");
#	endif
#	ifdef glXGetDrawableAttributesSGIX
	_glXGetDrawableAttributesSGIX = (glXGetDrawableAttributesSGIXFunc)glXGetFunction("glXGetDrawableAttributesSGIX");
#	endif
}

void glXFuncUnload()
{
#	ifdef glXGetFBConfigs
	_glXGetFBConfigs = NULL;
#	endif
#	ifdef glXChooseFBConfig
	_glXChooseFBConfig = NULL;
#	endif
#	ifdef glXGetFBConfigAttrib
	_glXGetFBConfigAttrib = NULL;
#	endif
#	ifdef glXGetVisualFromFBConfig
	_glXGetVisualFromFBConfig = NULL;
#	endif
#	ifdef glXCreateWindow
	_glXCreateWindow = NULL;
#	endif
#	ifdef glXDestroyWindow
	_glXDestroyWindow = NULL;
#	endif
#	ifdef glXCreatePixmap
	_glXCreatePixmap = NULL;
#	endif
#	ifdef glXDestroyPixmap
	_glXDestroyPixmap = NULL;
#	endif
#	ifdef glXCreatePbuffer
	_glXCreatePbuffer = NULL;
#	endif
#	ifdef glXDestroyPbuffer
	_glXDestroyPbuffer = NULL;
#	endif
#	ifdef glXQueryDrawable
	_glXQueryDrawable = NULL;
#	endif
#	ifdef glXCreateNewContext
	_glXCreateNewContext = NULL;
#	endif
#	ifdef glXMakeContextCurrent
	_glXMakeContextCurrent = NULL;
#	endif
#	ifdef glXGetCurrentReadDrawable
	_glXGetCurrentReadDrawable = NULL;
#	endif
#	ifdef glXGetCurrentDisplay
	_glXGetCurrentDisplay = NULL;
#	endif
#	ifdef glXQueryContext
	_glXQueryContext = NULL;
#	endif
#	ifdef glXSelectEvent
	_glXSelectEvent = NULL;
#	endif
#	ifdef glXGetSelectedEvent
	_glXGetSelectedEvent = NULL;
#	endif
#	ifdef glXGetProcAddress
	_glXGetProcAddress = NULL;
#	endif
#	ifdef glXCreateContextAttribsARB
	_glXCreateContextAttribsARB = NULL;
#	endif
#	ifdef glXSwapIntervalSGI
	_glXSwapIntervalSGI = NULL;
#	endif
#	ifdef glXGetVideoSyncSGI
	_glXGetVideoSyncSGI = NULL;
#	endif
#	ifdef glXWaitVideoSyncSGI
	_glXWaitVideoSyncSGI = NULL;
#	endif
#	ifdef glXMakeCurrentReadSGI
	_glXMakeCurrentReadSGI = NULL;
#	endif
#	ifdef glXGetCurrentReadDrawableSGI
	_glXGetCurrentReadDrawableSGI = NULL;
#	endif
#	ifdef glXCreateGLXVideoSourceSGIX
	_glXCreateGLXVideoSourceSGIX = NULL;
#	endif
#	ifdef glXDestroyGLXVideoSourceSGIX
	_glXDestroyGLXVideoSourceSGIX = NULL;
#	endif
#	ifdef glXGetCurrentDisplayEXT
	_glXGetCurrentDisplayEXT = NULL;
#	endif
#	ifdef glXQueryContextInfoEXT
	_glXQueryContextInfoEXT = NULL;
#	endif
#	ifdef glXGetContextIDEXT
	_glXGetContextIDEXT = NULL;
#	endif
#	ifdef glXImportContextEXT
	_glXImportContextEXT = NULL;
#	endif
#	ifdef glXFreeContextEXT
	_glXFreeContextEXT = NULL;
#	endif
#	ifdef glXGetFBConfigAttribSGIX
	_glXGetFBConfigAttribSGIX = NULL;
#	endif
#	ifdef glXChooseFBConfigSGIX
	_glXChooseFBConfigSGIX = NULL;
#	endif
#	ifdef glXCreateGLXPixmapWithConfigSGIX
	_glXCreateGLXPixmapWithConfigSGIX = NULL;
#	endif
#	ifdef glXCreateContextWithConfigSGIX
	_glXCreateContextWithConfigSGIX = NULL;
#	endif
#	ifdef glXGetVisualFromFBConfigSGIX
	_glXGetVisualFromFBConfigSGIX = NULL;
#	endif
#	ifdef glXGetFBConfigFromVisualSGIX
	_glXGetFBConfigFromVisualSGIX = NULL;
#	endif
#	ifdef glXCreateGLXPbufferSGIX
	_glXCreateGLXPbufferSGIX = NULL;
#	endif
#	ifdef glXDestroyGLXPbufferSGIX
	_glXDestroyGLXPbufferSGIX = NULL;
#	endif
#	ifdef glXQueryGLXPbufferSGIX
	_glXQueryGLXPbufferSGIX = NULL;
#	endif
#	ifdef glXSelectEventSGIX
	_glXSelectEventSGIX = NULL;
#	endif
#	ifdef glXGetSelectedEventSGIX
	_glXGetSelectedEventSGIX = NULL;
#	endif
#	ifdef glXCushionSGI
	_glXCushionSGI = NULL;
#	endif
#	ifdef glXBindChannelToWindowSGIX
	_glXBindChannelToWindowSGIX = NULL;
#	endif
#	ifdef glXChannelRectSGIX
	_glXChannelRectSGIX = NULL;
#	endif
#	ifdef glXQueryChannelRectSGIX
	_glXQueryChannelRectSGIX = NULL;
#	endif
#	ifdef glXQueryChannelDeltasSGIX
	_glXQueryChannelDeltasSGIX = NULL;
#	endif
#	ifdef glXChannelRectSyncSGIX
	_glXChannelRectSyncSGIX = NULL;
#	endif
#	ifdef glXAssociateDMPbufferSGIX
	_glXAssociateDMPbufferSGIX = NULL;
#	endif
#	ifdef glXJoinSwapGroupSGIX
	_glXJoinSwapGroupSGIX = NULL;
#	endif
#	ifdef glXBindSwapBarrierSGIX
	_glXBindSwapBarrierSGIX = NULL;
#	endif
#	ifdef glXQueryMaxSwapBarriersSGIX
	_glXQueryMaxSwapBarriersSGIX = NULL;
#	endif
#	ifdef glXGetTransparentIndexSUN
	_glXGetTransparentIndexSUN = NULL;
#	endif
#	ifdef glXCopySubBufferMESA
	_glXCopySubBufferMESA = NULL;
#	endif
#	ifdef glXCreateGLXPixmapMESA
	_glXCreateGLXPixmapMESA = NULL;
#	endif
#	ifdef glXReleaseBuffersMESA
	_glXReleaseBuffersMESA = NULL;
#	endif
#	ifdef glXSet3DfxModeMESA
	_glXSet3DfxModeMESA = NULL;
#	endif
#	ifdef glXGetSyncValuesOML
	_glXGetSyncValuesOML = NULL;
#	endif
#	ifdef glXGetMscRateOML
	_glXGetMscRateOML = NULL;
#	endif
#	ifdef glXSwapBuffersMscOML
	_glXSwapBuffersMscOML = NULL;
#	endif
#	ifdef glXWaitForMscOML
	_glXWaitForMscOML = NULL;
#	endif
#	ifdef glXWaitForSbcOML
	_glXWaitForSbcOML = NULL;
#	endif
#	ifdef glXQueryHyperpipeNetworkSGIX
	_glXQueryHyperpipeNetworkSGIX = NULL;
#	endif
#	ifdef glXHyperpipeConfigSGIX
	_glXHyperpipeConfigSGIX = NULL;
#	endif
#	ifdef glXQueryHyperpipeConfigSGIX
	_glXQueryHyperpipeConfigSGIX = NULL;
#	endif
#	ifdef glXDestroyHyperpipeConfigSGIX
	_glXDestroyHyperpipeConfigSGIX = NULL;
#	endif
#	ifdef glXBindHyperpipeSGIX
	_glXBindHyperpipeSGIX = NULL;
#	endif
#	ifdef glXQueryHyperpipeBestAttribSGIX
	_glXQueryHyperpipeBestAttribSGIX = NULL;
#	endif
#	ifdef glXHyperpipeAttribSGIX
	_glXHyperpipeAttribSGIX = NULL;
#	endif
#	ifdef glXQueryHyperpipeAttribSGIX
	_glXQueryHyperpipeAttribSGIX = NULL;
#	endif
#	ifdef glXGetAGPOffsetMESA
	_glXGetAGPOffsetMESA = NULL;
#	endif
#	ifdef glXBindTexImageEXT
	_glXBindTexImageEXT = NULL;
#	endif
#	ifdef glXReleaseTexImageEXT
	_glXReleaseTexImageEXT = NULL;
#	endif
#	ifdef glXEnumerateVideoDevicesNV
	_glXEnumerateVideoDevicesNV = NULL;
#	endif
#	ifdef glXBindVideoDeviceNV
	_glXBindVideoDeviceNV = NULL;
#	endif
#	ifdef glXGetVideoDeviceNV
	_glXGetVideoDeviceNV = NULL;
#	endif
#	ifdef glXReleaseVideoDeviceNV
	_glXReleaseVideoDeviceNV = NULL;
#	endif
#	ifdef glXBindVideoImageNV
	_glXBindVideoImageNV = NULL;
#	endif
#	ifdef glXReleaseVideoImageNV
	_glXReleaseVideoImageNV = NULL;
#	endif
#	ifdef glXSendPbufferToVideoNV
	_glXSendPbufferToVideoNV = NULL;
#	endif
#	ifdef glXGetVideoInfoNV
	_glXGetVideoInfoNV = NULL;
#	endif
#	ifdef glXJoinSwapGroupNV
	_glXJoinSwapGroupNV = NULL;
#	endif
#	ifdef glXBindSwapBarrierNV
	_glXBindSwapBarrierNV = NULL;
#	endif
#	ifdef glXQuerySwapGroupNV
	_glXQuerySwapGroupNV = NULL;
#	endif
#	ifdef glXQueryMaxSwapGroupsNV
	_glXQueryMaxSwapGroupsNV = NULL;
#	endif
#	ifdef glXQueryFrameCountNV
	_glXQueryFrameCountNV = NULL;
#	endif
#	ifdef glXResetFrameCountNV
	_glXResetFrameCountNV = NULL;
#	endif
#	ifdef glXBindVideoCaptureDeviceNV
	_glXBindVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef glXEnumerateVideoCaptureDevicesNV
	_glXEnumerateVideoCaptureDevicesNV = NULL;
#	endif
#	ifdef glXLockVideoCaptureDeviceNV
	_glXLockVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef glXQueryVideoCaptureDeviceNV
	_glXQueryVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef glXReleaseVideoCaptureDeviceNV
	_glXReleaseVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef glXSwapIntervalEXT
	_glXSwapIntervalEXT = NULL;
#	endif
#	ifdef glXCopyImageSubDataNV
	_glXCopyImageSubDataNV = NULL;
#	endif
#	ifdef glXRender
	_glXRender = NULL;
#	endif
#	ifdef glXRenderLarge
	_glXRenderLarge = NULL;
#	endif
#	ifdef glXDestroyContext
	_glXDestroyContext = NULL;
#	endif
#	ifdef glXIsDirect
	_glXIsDirect = NULL;
#	endif
#	ifdef glXQueryVersion
	_glXQueryVersion = NULL;
#	endif
#	ifdef glXWaitGL
	_glXWaitGL = NULL;
#	endif
#	ifdef glXWaitX
	_glXWaitX = NULL;
#	endif
#	ifdef glXCopyContext
	_glXCopyContext = NULL;
#	endif
#	ifdef glXUseXFont
	_glXUseXFont = NULL;
#	endif
#	ifdef glXCreateGLXPixmap
	_glXCreateGLXPixmap = NULL;
#	endif
#	ifdef glXGetVisualConfigs
	_glXGetVisualConfigs = NULL;
#	endif
#	ifdef glXDestroyGLXPixmap
	_glXDestroyGLXPixmap = NULL;
#	endif
#	ifdef glXVendorPrivate
	_glXVendorPrivate = NULL;
#	endif
#	ifdef glXVendorPrivateWithReply
	_glXVendorPrivateWithReply = NULL;
#	endif
#	ifdef glXQueryExtensionsString
	_glXQueryExtensionsString = NULL;
#	endif
#	ifdef glXQueryServerString
	_glXQueryServerString = NULL;
#	endif
#	ifdef glXClientInfo
	_glXClientInfo = NULL;
#	endif
#	ifdef glXGetDrawableAttributes
	_glXGetDrawableAttributes = NULL;
#	endif
#	ifdef glXChangeDrawableAttributes
	_glXChangeDrawableAttributes = NULL;
#	endif
#	ifdef glXGetFBConfigsSGIX
	_glXGetFBConfigsSGIX = NULL;
#	endif
#	ifdef glXChangeDrawableAttributesSGIX
	_glXChangeDrawableAttributesSGIX = NULL;
#	endif
#	ifdef glXGetDrawableAttributesSGIX
	_glXGetDrawableAttributesSGIX = NULL;
#	endif
}

#endif
