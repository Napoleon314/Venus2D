////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   wgl.cpp
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

#ifdef VE_WGL

#ifdef wglGetCurrentContext
wglGetCurrentContextFunc _wglGetCurrentContext = NULL;
#endif
#ifdef wglCopyContext
wglCopyContextFunc _wglCopyContext = NULL;
#endif
#ifdef wglChoosePixelFormat
wglChoosePixelFormatFunc _wglChoosePixelFormat = NULL;
#endif
#ifdef wglDescribePixelFormat
wglDescribePixelFormatFunc _wglDescribePixelFormat = NULL;
#endif
#ifdef wglGetCurrentDC
wglGetCurrentDCFunc _wglGetCurrentDC = NULL;
#endif
#ifdef wglGetDefaultProcAddress
wglGetDefaultProcAddressFunc _wglGetDefaultProcAddress = NULL;
#endif
#ifdef wglGetPixelFormat
wglGetPixelFormatFunc _wglGetPixelFormat = NULL;
#endif
#ifdef wglSetPixelFormat
wglSetPixelFormatFunc _wglSetPixelFormat = NULL;
#endif
#ifdef wglSwapBuffers
wglSwapBuffersFunc _wglSwapBuffers = NULL;
#endif
#ifdef wglShareLists
wglShareListsFunc _wglShareLists = NULL;
#endif
#ifdef wglCreateLayerContext
wglCreateLayerContextFunc _wglCreateLayerContext = NULL;
#endif
#ifdef wglDescribeLayerPlane
wglDescribeLayerPlaneFunc _wglDescribeLayerPlane = NULL;
#endif
#ifdef wglSetLayerPaletteEntries
wglSetLayerPaletteEntriesFunc _wglSetLayerPaletteEntries = NULL;
#endif
#ifdef wglGetLayerPaletteEntries
wglGetLayerPaletteEntriesFunc _wglGetLayerPaletteEntries = NULL;
#endif
#ifdef wglRealizeLayerPalette
wglRealizeLayerPaletteFunc _wglRealizeLayerPalette = NULL;
#endif
#ifdef wglSwapLayerBuffers
wglSwapLayerBuffersFunc _wglSwapLayerBuffers = NULL;
#endif
#ifdef wglUseFontBitmapsA
wglUseFontBitmapsAFunc _wglUseFontBitmapsA = NULL;
#endif
#ifdef wglUseFontBitmapsW
wglUseFontBitmapsWFunc _wglUseFontBitmapsW = NULL;
#endif
#ifdef wglCreateBufferRegionARB
wglCreateBufferRegionARBFunc _wglCreateBufferRegionARB = NULL;
#endif
#ifdef wglDeleteBufferRegionARB
wglDeleteBufferRegionARBFunc _wglDeleteBufferRegionARB = NULL;
#endif
#ifdef wglSaveBufferRegionARB
wglSaveBufferRegionARBFunc _wglSaveBufferRegionARB = NULL;
#endif
#ifdef wglRestoreBufferRegionARB
wglRestoreBufferRegionARBFunc _wglRestoreBufferRegionARB = NULL;
#endif
#ifdef wglGetExtensionsStringARB
wglGetExtensionsStringARBFunc _wglGetExtensionsStringARB = NULL;
#endif
#ifdef wglGetPixelFormatAttribivARB
wglGetPixelFormatAttribivARBFunc _wglGetPixelFormatAttribivARB = NULL;
#endif
#ifdef wglGetPixelFormatAttribfvARB
wglGetPixelFormatAttribfvARBFunc _wglGetPixelFormatAttribfvARB = NULL;
#endif
#ifdef wglChoosePixelFormatARB
wglChoosePixelFormatARBFunc _wglChoosePixelFormatARB = NULL;
#endif
#ifdef wglMakeContextCurrentARB
wglMakeContextCurrentARBFunc _wglMakeContextCurrentARB = NULL;
#endif
#ifdef wglGetCurrentReadDCARB
wglGetCurrentReadDCARBFunc _wglGetCurrentReadDCARB = NULL;
#endif
#ifdef wglCreatePbufferARB
wglCreatePbufferARBFunc _wglCreatePbufferARB = NULL;
#endif
#ifdef wglGetPbufferDCARB
wglGetPbufferDCARBFunc _wglGetPbufferDCARB = NULL;
#endif
#ifdef wglReleasePbufferDCARB
wglReleasePbufferDCARBFunc _wglReleasePbufferDCARB = NULL;
#endif
#ifdef wglDestroyPbufferARB
wglDestroyPbufferARBFunc _wglDestroyPbufferARB = NULL;
#endif
#ifdef wglQueryPbufferARB
wglQueryPbufferARBFunc _wglQueryPbufferARB = NULL;
#endif
#ifdef wglBindTexImageARB
wglBindTexImageARBFunc _wglBindTexImageARB = NULL;
#endif
#ifdef wglReleaseTexImageARB
wglReleaseTexImageARBFunc _wglReleaseTexImageARB = NULL;
#endif
#ifdef wglSetPbufferAttribARB
wglSetPbufferAttribARBFunc _wglSetPbufferAttribARB = NULL;
#endif
#ifdef wglCreateContextAttribsARB
wglCreateContextAttribsARBFunc _wglCreateContextAttribsARB = NULL;
#endif
#ifdef wglCreateDisplayColorTableEXT
wglCreateDisplayColorTableEXTFunc _wglCreateDisplayColorTableEXT = NULL;
#endif
#ifdef wglLoadDisplayColorTableEXT
wglLoadDisplayColorTableEXTFunc _wglLoadDisplayColorTableEXT = NULL;
#endif
#ifdef wglBindDisplayColorTableEXT
wglBindDisplayColorTableEXTFunc _wglBindDisplayColorTableEXT = NULL;
#endif
#ifdef wglDestroyDisplayColorTableEXT
wglDestroyDisplayColorTableEXTFunc _wglDestroyDisplayColorTableEXT = NULL;
#endif
#ifdef wglGetExtensionsStringEXT
wglGetExtensionsStringEXTFunc _wglGetExtensionsStringEXT = NULL;
#endif
#ifdef wglMakeContextCurrentEXT
wglMakeContextCurrentEXTFunc _wglMakeContextCurrentEXT = NULL;
#endif
#ifdef wglGetCurrentReadDCEXT
wglGetCurrentReadDCEXTFunc _wglGetCurrentReadDCEXT = NULL;
#endif
#ifdef wglCreatePbufferEXT
wglCreatePbufferEXTFunc _wglCreatePbufferEXT = NULL;
#endif
#ifdef wglGetPbufferDCEXT
wglGetPbufferDCEXTFunc _wglGetPbufferDCEXT = NULL;
#endif
#ifdef wglReleasePbufferDCEXT
wglReleasePbufferDCEXTFunc _wglReleasePbufferDCEXT = NULL;
#endif
#ifdef wglDestroyPbufferEXT
wglDestroyPbufferEXTFunc _wglDestroyPbufferEXT = NULL;
#endif
#ifdef wglQueryPbufferEXT
wglQueryPbufferEXTFunc _wglQueryPbufferEXT = NULL;
#endif
#ifdef wglGetPixelFormatAttribivEXT
wglGetPixelFormatAttribivEXTFunc _wglGetPixelFormatAttribivEXT = NULL;
#endif
#ifdef wglGetPixelFormatAttribfvEXT
wglGetPixelFormatAttribfvEXTFunc _wglGetPixelFormatAttribfvEXT = NULL;
#endif
#ifdef wglChoosePixelFormatEXT
wglChoosePixelFormatEXTFunc _wglChoosePixelFormatEXT = NULL;
#endif
#ifdef wglSwapIntervalEXT
wglSwapIntervalEXTFunc _wglSwapIntervalEXT = NULL;
#endif
#ifdef wglGetSwapIntervalEXT
wglGetSwapIntervalEXTFunc _wglGetSwapIntervalEXT = NULL;
#endif
#ifdef wglAllocateMemoryNV
wglAllocateMemoryNVFunc _wglAllocateMemoryNV = NULL;
#endif
#ifdef wglFreeMemoryNV
wglFreeMemoryNVFunc _wglFreeMemoryNV = NULL;
#endif
#ifdef wglGetSyncValuesOML
wglGetSyncValuesOMLFunc _wglGetSyncValuesOML = NULL;
#endif
#ifdef wglGetMscRateOML
wglGetMscRateOMLFunc _wglGetMscRateOML = NULL;
#endif
#ifdef wglSwapBuffersMscOML
wglSwapBuffersMscOMLFunc _wglSwapBuffersMscOML = NULL;
#endif
#ifdef wglSwapLayerBuffersMscOML
wglSwapLayerBuffersMscOMLFunc _wglSwapLayerBuffersMscOML = NULL;
#endif
#ifdef wglWaitForMscOML
wglWaitForMscOMLFunc _wglWaitForMscOML = NULL;
#endif
#ifdef wglWaitForSbcOML
wglWaitForSbcOMLFunc _wglWaitForSbcOML = NULL;
#endif
#ifdef wglGetDigitalVideoParametersI3D
wglGetDigitalVideoParametersI3DFunc _wglGetDigitalVideoParametersI3D = NULL;
#endif
#ifdef wglSetDigitalVideoParametersI3D
wglSetDigitalVideoParametersI3DFunc _wglSetDigitalVideoParametersI3D = NULL;
#endif
#ifdef wglGetGammaTableParametersI3D
wglGetGammaTableParametersI3DFunc _wglGetGammaTableParametersI3D = NULL;
#endif
#ifdef wglSetGammaTableParametersI3D
wglSetGammaTableParametersI3DFunc _wglSetGammaTableParametersI3D = NULL;
#endif
#ifdef wglGetGammaTableI3D
wglGetGammaTableI3DFunc _wglGetGammaTableI3D = NULL;
#endif
#ifdef wglSetGammaTableI3D
wglSetGammaTableI3DFunc _wglSetGammaTableI3D = NULL;
#endif
#ifdef wglEnableGenlockI3D
wglEnableGenlockI3DFunc _wglEnableGenlockI3D = NULL;
#endif
#ifdef wglDisableGenlockI3D
wglDisableGenlockI3DFunc _wglDisableGenlockI3D = NULL;
#endif
#ifdef wglIsEnabledGenlockI3D
wglIsEnabledGenlockI3DFunc _wglIsEnabledGenlockI3D = NULL;
#endif
#ifdef wglGenlockSourceI3D
wglGenlockSourceI3DFunc _wglGenlockSourceI3D = NULL;
#endif
#ifdef wglGetGenlockSourceI3D
wglGetGenlockSourceI3DFunc _wglGetGenlockSourceI3D = NULL;
#endif
#ifdef wglGenlockSourceEdgeI3D
wglGenlockSourceEdgeI3DFunc _wglGenlockSourceEdgeI3D = NULL;
#endif
#ifdef wglGetGenlockSourceEdgeI3D
wglGetGenlockSourceEdgeI3DFunc _wglGetGenlockSourceEdgeI3D = NULL;
#endif
#ifdef wglGenlockSampleRateI3D
wglGenlockSampleRateI3DFunc _wglGenlockSampleRateI3D = NULL;
#endif
#ifdef wglGetGenlockSampleRateI3D
wglGetGenlockSampleRateI3DFunc _wglGetGenlockSampleRateI3D = NULL;
#endif
#ifdef wglGenlockSourceDelayI3D
wglGenlockSourceDelayI3DFunc _wglGenlockSourceDelayI3D = NULL;
#endif
#ifdef wglGetGenlockSourceDelayI3D
wglGetGenlockSourceDelayI3DFunc _wglGetGenlockSourceDelayI3D = NULL;
#endif
#ifdef wglQueryGenlockMaxSourceDelayI3D
wglQueryGenlockMaxSourceDelayI3DFunc _wglQueryGenlockMaxSourceDelayI3D = NULL;
#endif
#ifdef wglCreateImageBufferI3D
wglCreateImageBufferI3DFunc _wglCreateImageBufferI3D = NULL;
#endif
#ifdef wglDestroyImageBufferI3D
wglDestroyImageBufferI3DFunc _wglDestroyImageBufferI3D = NULL;
#endif
#ifdef wglAssociateImageBufferEventsI3D
wglAssociateImageBufferEventsI3DFunc _wglAssociateImageBufferEventsI3D = NULL;
#endif
#ifdef wglReleaseImageBufferEventsI3D
wglReleaseImageBufferEventsI3DFunc _wglReleaseImageBufferEventsI3D = NULL;
#endif
#ifdef wglEnableFrameLockI3D
wglEnableFrameLockI3DFunc _wglEnableFrameLockI3D = NULL;
#endif
#ifdef wglDisableFrameLockI3D
wglDisableFrameLockI3DFunc _wglDisableFrameLockI3D = NULL;
#endif
#ifdef wglIsEnabledFrameLockI3D
wglIsEnabledFrameLockI3DFunc _wglIsEnabledFrameLockI3D = NULL;
#endif
#ifdef wglQueryFrameLockMasterI3D
wglQueryFrameLockMasterI3DFunc _wglQueryFrameLockMasterI3D = NULL;
#endif
#ifdef wglGetFrameUsageI3D
wglGetFrameUsageI3DFunc _wglGetFrameUsageI3D = NULL;
#endif
#ifdef wglBeginFrameTrackingI3D
wglBeginFrameTrackingI3DFunc _wglBeginFrameTrackingI3D = NULL;
#endif
#ifdef wglEndFrameTrackingI3D
wglEndFrameTrackingI3DFunc _wglEndFrameTrackingI3D = NULL;
#endif
#ifdef wglQueryFrameTrackingI3D
wglQueryFrameTrackingI3DFunc _wglQueryFrameTrackingI3D = NULL;
#endif
#ifdef wglSetStereoEmitterState3DL
wglSetStereoEmitterState3DLFunc _wglSetStereoEmitterState3DL = NULL;
#endif
#ifdef wglEnumerateVideoDevicesNV
wglEnumerateVideoDevicesNVFunc _wglEnumerateVideoDevicesNV = NULL;
#endif
#ifdef wglBindVideoDeviceNV
wglBindVideoDeviceNVFunc _wglBindVideoDeviceNV = NULL;
#endif
#ifdef wglQueryCurrentContextNV
wglQueryCurrentContextNVFunc _wglQueryCurrentContextNV = NULL;
#endif
#ifdef wglGetVideoDeviceNV
wglGetVideoDeviceNVFunc _wglGetVideoDeviceNV = NULL;
#endif
#ifdef wglReleaseVideoDeviceNV
wglReleaseVideoDeviceNVFunc _wglReleaseVideoDeviceNV = NULL;
#endif
#ifdef wglBindVideoImageNV
wglBindVideoImageNVFunc _wglBindVideoImageNV = NULL;
#endif
#ifdef wglReleaseVideoImageNV
wglReleaseVideoImageNVFunc _wglReleaseVideoImageNV = NULL;
#endif
#ifdef wglSendPbufferToVideoNV
wglSendPbufferToVideoNVFunc _wglSendPbufferToVideoNV = NULL;
#endif
#ifdef wglGetVideoInfoNV
wglGetVideoInfoNVFunc _wglGetVideoInfoNV = NULL;
#endif
#ifdef wglJoinSwapGroupNV
wglJoinSwapGroupNVFunc _wglJoinSwapGroupNV = NULL;
#endif
#ifdef wglBindSwapBarrierNV
wglBindSwapBarrierNVFunc _wglBindSwapBarrierNV = NULL;
#endif
#ifdef wglQuerySwapGroupNV
wglQuerySwapGroupNVFunc _wglQuerySwapGroupNV = NULL;
#endif
#ifdef wglQueryMaxSwapGroupsNV
wglQueryMaxSwapGroupsNVFunc _wglQueryMaxSwapGroupsNV = NULL;
#endif
#ifdef wglQueryFrameCountNV
wglQueryFrameCountNVFunc _wglQueryFrameCountNV = NULL;
#endif
#ifdef wglResetFrameCountNV
wglResetFrameCountNVFunc _wglResetFrameCountNV = NULL;
#endif
#ifdef wglEnumGpusNV
wglEnumGpusNVFunc _wglEnumGpusNV = NULL;
#endif
#ifdef wglEnumGpuDevicesNV
wglEnumGpuDevicesNVFunc _wglEnumGpuDevicesNV = NULL;
#endif
#ifdef wglCreateAffinityDCNV
wglCreateAffinityDCNVFunc _wglCreateAffinityDCNV = NULL;
#endif
#ifdef wglEnumGpusFromAffinityDCNV
wglEnumGpusFromAffinityDCNVFunc _wglEnumGpusFromAffinityDCNV = NULL;
#endif
#ifdef wglDeleteDCNV
wglDeleteDCNVFunc _wglDeleteDCNV = NULL;
#endif
#ifdef wglGetGPUIDsAMD
wglGetGPUIDsAMDFunc _wglGetGPUIDsAMD = NULL;
#endif
#ifdef wglGetGPUInfoAMD
wglGetGPUInfoAMDFunc _wglGetGPUInfoAMD = NULL;
#endif
#ifdef wglGetContextGPUIDAMD
wglGetContextGPUIDAMDFunc _wglGetContextGPUIDAMD = NULL;
#endif
#ifdef wglCreateAssociatedContextAMD
wglCreateAssociatedContextAMDFunc _wglCreateAssociatedContextAMD = NULL;
#endif
#ifdef wglCreateAssociatedContextAttribsAMD
wglCreateAssociatedContextAttribsAMDFunc _wglCreateAssociatedContextAttribsAMD = NULL;
#endif
#ifdef wglDeleteAssociatedContextAMD
wglDeleteAssociatedContextAMDFunc _wglDeleteAssociatedContextAMD = NULL;
#endif
#ifdef wglMakeAssociatedContextCurrentAMD
wglMakeAssociatedContextCurrentAMDFunc _wglMakeAssociatedContextCurrentAMD = NULL;
#endif
#ifdef wglGetCurrentAssociatedContextAMD
wglGetCurrentAssociatedContextAMDFunc _wglGetCurrentAssociatedContextAMD = NULL;
#endif
#ifdef wglBlitContextFramebufferAMD
wglBlitContextFramebufferAMDFunc _wglBlitContextFramebufferAMD = NULL;
#endif
#ifdef wglBindVideoCaptureDeviceNV
wglBindVideoCaptureDeviceNVFunc _wglBindVideoCaptureDeviceNV = NULL;
#endif
#ifdef wglEnumerateVideoCaptureDevicesNV
wglEnumerateVideoCaptureDevicesNVFunc _wglEnumerateVideoCaptureDevicesNV = NULL;
#endif
#ifdef wglLockVideoCaptureDeviceNV
wglLockVideoCaptureDeviceNVFunc _wglLockVideoCaptureDeviceNV = NULL;
#endif
#ifdef wglQueryVideoCaptureDeviceNV
wglQueryVideoCaptureDeviceNVFunc _wglQueryVideoCaptureDeviceNV = NULL;
#endif
#ifdef wglReleaseVideoCaptureDeviceNV
wglReleaseVideoCaptureDeviceNVFunc _wglReleaseVideoCaptureDeviceNV = NULL;
#endif
#ifdef wglCopyImageSubDataNV
wglCopyImageSubDataNVFunc _wglCopyImageSubDataNV = NULL;
#endif
#ifdef wglDXSetResourceShareHandleNV
wglDXSetResourceShareHandleNVFunc _wglDXSetResourceShareHandleNV = NULL;
#endif
#ifdef wglDXOpenDeviceNV
wglDXOpenDeviceNVFunc _wglDXOpenDeviceNV = NULL;
#endif
#ifdef wglDXCloseDeviceNV
wglDXCloseDeviceNVFunc _wglDXCloseDeviceNV = NULL;
#endif
#ifdef wglDXRegisterObjectNV
wglDXRegisterObjectNVFunc _wglDXRegisterObjectNV = NULL;
#endif
#ifdef wglDXUnregisterObjectNV
wglDXUnregisterObjectNVFunc _wglDXUnregisterObjectNV = NULL;
#endif
#ifdef wglDXObjectAccessNV
wglDXObjectAccessNVFunc _wglDXObjectAccessNV = NULL;
#endif
#ifdef wglDXLockObjectsNV
wglDXLockObjectsNVFunc _wglDXLockObjectsNV = NULL;
#endif
#ifdef wglDXUnlockObjectsNV
wglDXUnlockObjectsNVFunc _wglDXUnlockObjectsNV = NULL;
#endif

void wglFuncload()
{
#	ifdef wglGetCurrentContext
	_wglGetCurrentContext = (wglGetCurrentContextFunc)wglGetFunction("wglGetCurrentContext");
#	endif
#	ifdef wglCopyContext
	_wglCopyContext = (wglCopyContextFunc)wglGetFunction("wglCopyContext");
#	endif
#	ifdef wglChoosePixelFormat
	_wglChoosePixelFormat = (wglChoosePixelFormatFunc)wglGetFunction("wglChoosePixelFormat");
#	endif
#	ifdef wglDescribePixelFormat
	_wglDescribePixelFormat = (wglDescribePixelFormatFunc)wglGetFunction("wglDescribePixelFormat");
#	endif
#	ifdef wglGetCurrentDC
	_wglGetCurrentDC = (wglGetCurrentDCFunc)wglGetFunction("wglGetCurrentDC");
#	endif
#	ifdef wglGetDefaultProcAddress
	_wglGetDefaultProcAddress = (wglGetDefaultProcAddressFunc)wglGetFunction("wglGetDefaultProcAddress");
#	endif
#	ifdef wglGetPixelFormat
	_wglGetPixelFormat = (wglGetPixelFormatFunc)wglGetFunction("wglGetPixelFormat");
#	endif
#	ifdef wglSetPixelFormat
	_wglSetPixelFormat = (wglSetPixelFormatFunc)wglGetFunction("wglSetPixelFormat");
#	endif
#	ifdef wglSwapBuffers
	_wglSwapBuffers = (wglSwapBuffersFunc)wglGetFunction("wglSwapBuffers");
#	endif
#	ifdef wglShareLists
	_wglShareLists = (wglShareListsFunc)wglGetFunction("wglShareLists");
#	endif
#	ifdef wglCreateLayerContext
	_wglCreateLayerContext = (wglCreateLayerContextFunc)wglGetFunction("wglCreateLayerContext");
#	endif
#	ifdef wglDescribeLayerPlane
	_wglDescribeLayerPlane = (wglDescribeLayerPlaneFunc)wglGetFunction("wglDescribeLayerPlane");
#	endif
#	ifdef wglSetLayerPaletteEntries
	_wglSetLayerPaletteEntries = (wglSetLayerPaletteEntriesFunc)wglGetFunction("wglSetLayerPaletteEntries");
#	endif
#	ifdef wglGetLayerPaletteEntries
	_wglGetLayerPaletteEntries = (wglGetLayerPaletteEntriesFunc)wglGetFunction("wglGetLayerPaletteEntries");
#	endif
#	ifdef wglRealizeLayerPalette
	_wglRealizeLayerPalette = (wglRealizeLayerPaletteFunc)wglGetFunction("wglRealizeLayerPalette");
#	endif
#	ifdef wglSwapLayerBuffers
	_wglSwapLayerBuffers = (wglSwapLayerBuffersFunc)wglGetFunction("wglSwapLayerBuffers");
#	endif
#	ifdef wglUseFontBitmapsA
	_wglUseFontBitmapsA = (wglUseFontBitmapsAFunc)wglGetFunction("wglUseFontBitmapsA");
#	endif
#	ifdef wglUseFontBitmapsW
	_wglUseFontBitmapsW = (wglUseFontBitmapsWFunc)wglGetFunction("wglUseFontBitmapsW");
#	endif
#	ifdef wglCreateBufferRegionARB
	_wglCreateBufferRegionARB = (wglCreateBufferRegionARBFunc)wglGetFunction("wglCreateBufferRegionARB");
#	endif
#	ifdef wglDeleteBufferRegionARB
	_wglDeleteBufferRegionARB = (wglDeleteBufferRegionARBFunc)wglGetFunction("wglDeleteBufferRegionARB");
#	endif
#	ifdef wglSaveBufferRegionARB
	_wglSaveBufferRegionARB = (wglSaveBufferRegionARBFunc)wglGetFunction("wglSaveBufferRegionARB");
#	endif
#	ifdef wglRestoreBufferRegionARB
	_wglRestoreBufferRegionARB = (wglRestoreBufferRegionARBFunc)wglGetFunction("wglRestoreBufferRegionARB");
#	endif
#	ifdef wglGetExtensionsStringARB
	_wglGetExtensionsStringARB = (wglGetExtensionsStringARBFunc)wglGetFunction("wglGetExtensionsStringARB");
#	endif
#	ifdef wglGetPixelFormatAttribivARB
	_wglGetPixelFormatAttribivARB = (wglGetPixelFormatAttribivARBFunc)wglGetFunction("wglGetPixelFormatAttribivARB");
#	endif
#	ifdef wglGetPixelFormatAttribfvARB
	_wglGetPixelFormatAttribfvARB = (wglGetPixelFormatAttribfvARBFunc)wglGetFunction("wglGetPixelFormatAttribfvARB");
#	endif
#	ifdef wglChoosePixelFormatARB
	_wglChoosePixelFormatARB = (wglChoosePixelFormatARBFunc)wglGetFunction("wglChoosePixelFormatARB");
#	endif
#	ifdef wglMakeContextCurrentARB
	_wglMakeContextCurrentARB = (wglMakeContextCurrentARBFunc)wglGetFunction("wglMakeContextCurrentARB");
#	endif
#	ifdef wglGetCurrentReadDCARB
	_wglGetCurrentReadDCARB = (wglGetCurrentReadDCARBFunc)wglGetFunction("wglGetCurrentReadDCARB");
#	endif
#	ifdef wglCreatePbufferARB
	_wglCreatePbufferARB = (wglCreatePbufferARBFunc)wglGetFunction("wglCreatePbufferARB");
#	endif
#	ifdef wglGetPbufferDCARB
	_wglGetPbufferDCARB = (wglGetPbufferDCARBFunc)wglGetFunction("wglGetPbufferDCARB");
#	endif
#	ifdef wglReleasePbufferDCARB
	_wglReleasePbufferDCARB = (wglReleasePbufferDCARBFunc)wglGetFunction("wglReleasePbufferDCARB");
#	endif
#	ifdef wglDestroyPbufferARB
	_wglDestroyPbufferARB = (wglDestroyPbufferARBFunc)wglGetFunction("wglDestroyPbufferARB");
#	endif
#	ifdef wglQueryPbufferARB
	_wglQueryPbufferARB = (wglQueryPbufferARBFunc)wglGetFunction("wglQueryPbufferARB");
#	endif
#	ifdef wglBindTexImageARB
	_wglBindTexImageARB = (wglBindTexImageARBFunc)wglGetFunction("wglBindTexImageARB");
#	endif
#	ifdef wglReleaseTexImageARB
	_wglReleaseTexImageARB = (wglReleaseTexImageARBFunc)wglGetFunction("wglReleaseTexImageARB");
#	endif
#	ifdef wglSetPbufferAttribARB
	_wglSetPbufferAttribARB = (wglSetPbufferAttribARBFunc)wglGetFunction("wglSetPbufferAttribARB");
#	endif
#	ifdef wglCreateContextAttribsARB
	_wglCreateContextAttribsARB = (wglCreateContextAttribsARBFunc)wglGetFunction("wglCreateContextAttribsARB");
#	endif
#	ifdef wglCreateDisplayColorTableEXT
	_wglCreateDisplayColorTableEXT = (wglCreateDisplayColorTableEXTFunc)wglGetFunction("wglCreateDisplayColorTableEXT");
#	endif
#	ifdef wglLoadDisplayColorTableEXT
	_wglLoadDisplayColorTableEXT = (wglLoadDisplayColorTableEXTFunc)wglGetFunction("wglLoadDisplayColorTableEXT");
#	endif
#	ifdef wglBindDisplayColorTableEXT
	_wglBindDisplayColorTableEXT = (wglBindDisplayColorTableEXTFunc)wglGetFunction("wglBindDisplayColorTableEXT");
#	endif
#	ifdef wglDestroyDisplayColorTableEXT
	_wglDestroyDisplayColorTableEXT = (wglDestroyDisplayColorTableEXTFunc)wglGetFunction("wglDestroyDisplayColorTableEXT");
#	endif
#	ifdef wglGetExtensionsStringEXT
	_wglGetExtensionsStringEXT = (wglGetExtensionsStringEXTFunc)wglGetFunction("wglGetExtensionsStringEXT");
#	endif
#	ifdef wglMakeContextCurrentEXT
	_wglMakeContextCurrentEXT = (wglMakeContextCurrentEXTFunc)wglGetFunction("wglMakeContextCurrentEXT");
#	endif
#	ifdef wglGetCurrentReadDCEXT
	_wglGetCurrentReadDCEXT = (wglGetCurrentReadDCEXTFunc)wglGetFunction("wglGetCurrentReadDCEXT");
#	endif
#	ifdef wglCreatePbufferEXT
	_wglCreatePbufferEXT = (wglCreatePbufferEXTFunc)wglGetFunction("wglCreatePbufferEXT");
#	endif
#	ifdef wglGetPbufferDCEXT
	_wglGetPbufferDCEXT = (wglGetPbufferDCEXTFunc)wglGetFunction("wglGetPbufferDCEXT");
#	endif
#	ifdef wglReleasePbufferDCEXT
	_wglReleasePbufferDCEXT = (wglReleasePbufferDCEXTFunc)wglGetFunction("wglReleasePbufferDCEXT");
#	endif
#	ifdef wglDestroyPbufferEXT
	_wglDestroyPbufferEXT = (wglDestroyPbufferEXTFunc)wglGetFunction("wglDestroyPbufferEXT");
#	endif
#	ifdef wglQueryPbufferEXT
	_wglQueryPbufferEXT = (wglQueryPbufferEXTFunc)wglGetFunction("wglQueryPbufferEXT");
#	endif
#	ifdef wglGetPixelFormatAttribivEXT
	_wglGetPixelFormatAttribivEXT = (wglGetPixelFormatAttribivEXTFunc)wglGetFunction("wglGetPixelFormatAttribivEXT");
#	endif
#	ifdef wglGetPixelFormatAttribfvEXT
	_wglGetPixelFormatAttribfvEXT = (wglGetPixelFormatAttribfvEXTFunc)wglGetFunction("wglGetPixelFormatAttribfvEXT");
#	endif
#	ifdef wglChoosePixelFormatEXT
	_wglChoosePixelFormatEXT = (wglChoosePixelFormatEXTFunc)wglGetFunction("wglChoosePixelFormatEXT");
#	endif
#	ifdef wglSwapIntervalEXT
	_wglSwapIntervalEXT = (wglSwapIntervalEXTFunc)wglGetFunction("wglSwapIntervalEXT");
#	endif
#	ifdef wglGetSwapIntervalEXT
	_wglGetSwapIntervalEXT = (wglGetSwapIntervalEXTFunc)wglGetFunction("wglGetSwapIntervalEXT");
#	endif
#	ifdef wglAllocateMemoryNV
	_wglAllocateMemoryNV = (wglAllocateMemoryNVFunc)wglGetFunction("wglAllocateMemoryNV");
#	endif
#	ifdef wglFreeMemoryNV
	_wglFreeMemoryNV = (wglFreeMemoryNVFunc)wglGetFunction("wglFreeMemoryNV");
#	endif
#	ifdef wglGetSyncValuesOML
	_wglGetSyncValuesOML = (wglGetSyncValuesOMLFunc)wglGetFunction("wglGetSyncValuesOML");
#	endif
#	ifdef wglGetMscRateOML
	_wglGetMscRateOML = (wglGetMscRateOMLFunc)wglGetFunction("wglGetMscRateOML");
#	endif
#	ifdef wglSwapBuffersMscOML
	_wglSwapBuffersMscOML = (wglSwapBuffersMscOMLFunc)wglGetFunction("wglSwapBuffersMscOML");
#	endif
#	ifdef wglSwapLayerBuffersMscOML
	_wglSwapLayerBuffersMscOML = (wglSwapLayerBuffersMscOMLFunc)wglGetFunction("wglSwapLayerBuffersMscOML");
#	endif
#	ifdef wglWaitForMscOML
	_wglWaitForMscOML = (wglWaitForMscOMLFunc)wglGetFunction("wglWaitForMscOML");
#	endif
#	ifdef wglWaitForSbcOML
	_wglWaitForSbcOML = (wglWaitForSbcOMLFunc)wglGetFunction("wglWaitForSbcOML");
#	endif
#	ifdef wglGetDigitalVideoParametersI3D
	_wglGetDigitalVideoParametersI3D = (wglGetDigitalVideoParametersI3DFunc)wglGetFunction("wglGetDigitalVideoParametersI3D");
#	endif
#	ifdef wglSetDigitalVideoParametersI3D
	_wglSetDigitalVideoParametersI3D = (wglSetDigitalVideoParametersI3DFunc)wglGetFunction("wglSetDigitalVideoParametersI3D");
#	endif
#	ifdef wglGetGammaTableParametersI3D
	_wglGetGammaTableParametersI3D = (wglGetGammaTableParametersI3DFunc)wglGetFunction("wglGetGammaTableParametersI3D");
#	endif
#	ifdef wglSetGammaTableParametersI3D
	_wglSetGammaTableParametersI3D = (wglSetGammaTableParametersI3DFunc)wglGetFunction("wglSetGammaTableParametersI3D");
#	endif
#	ifdef wglGetGammaTableI3D
	_wglGetGammaTableI3D = (wglGetGammaTableI3DFunc)wglGetFunction("wglGetGammaTableI3D");
#	endif
#	ifdef wglSetGammaTableI3D
	_wglSetGammaTableI3D = (wglSetGammaTableI3DFunc)wglGetFunction("wglSetGammaTableI3D");
#	endif
#	ifdef wglEnableGenlockI3D
	_wglEnableGenlockI3D = (wglEnableGenlockI3DFunc)wglGetFunction("wglEnableGenlockI3D");
#	endif
#	ifdef wglDisableGenlockI3D
	_wglDisableGenlockI3D = (wglDisableGenlockI3DFunc)wglGetFunction("wglDisableGenlockI3D");
#	endif
#	ifdef wglIsEnabledGenlockI3D
	_wglIsEnabledGenlockI3D = (wglIsEnabledGenlockI3DFunc)wglGetFunction("wglIsEnabledGenlockI3D");
#	endif
#	ifdef wglGenlockSourceI3D
	_wglGenlockSourceI3D = (wglGenlockSourceI3DFunc)wglGetFunction("wglGenlockSourceI3D");
#	endif
#	ifdef wglGetGenlockSourceI3D
	_wglGetGenlockSourceI3D = (wglGetGenlockSourceI3DFunc)wglGetFunction("wglGetGenlockSourceI3D");
#	endif
#	ifdef wglGenlockSourceEdgeI3D
	_wglGenlockSourceEdgeI3D = (wglGenlockSourceEdgeI3DFunc)wglGetFunction("wglGenlockSourceEdgeI3D");
#	endif
#	ifdef wglGetGenlockSourceEdgeI3D
	_wglGetGenlockSourceEdgeI3D = (wglGetGenlockSourceEdgeI3DFunc)wglGetFunction("wglGetGenlockSourceEdgeI3D");
#	endif
#	ifdef wglGenlockSampleRateI3D
	_wglGenlockSampleRateI3D = (wglGenlockSampleRateI3DFunc)wglGetFunction("wglGenlockSampleRateI3D");
#	endif
#	ifdef wglGetGenlockSampleRateI3D
	_wglGetGenlockSampleRateI3D = (wglGetGenlockSampleRateI3DFunc)wglGetFunction("wglGetGenlockSampleRateI3D");
#	endif
#	ifdef wglGenlockSourceDelayI3D
	_wglGenlockSourceDelayI3D = (wglGenlockSourceDelayI3DFunc)wglGetFunction("wglGenlockSourceDelayI3D");
#	endif
#	ifdef wglGetGenlockSourceDelayI3D
	_wglGetGenlockSourceDelayI3D = (wglGetGenlockSourceDelayI3DFunc)wglGetFunction("wglGetGenlockSourceDelayI3D");
#	endif
#	ifdef wglQueryGenlockMaxSourceDelayI3D
	_wglQueryGenlockMaxSourceDelayI3D = (wglQueryGenlockMaxSourceDelayI3DFunc)wglGetFunction("wglQueryGenlockMaxSourceDelayI3D");
#	endif
#	ifdef wglCreateImageBufferI3D
	_wglCreateImageBufferI3D = (wglCreateImageBufferI3DFunc)wglGetFunction("wglCreateImageBufferI3D");
#	endif
#	ifdef wglDestroyImageBufferI3D
	_wglDestroyImageBufferI3D = (wglDestroyImageBufferI3DFunc)wglGetFunction("wglDestroyImageBufferI3D");
#	endif
#	ifdef wglAssociateImageBufferEventsI3D
	_wglAssociateImageBufferEventsI3D = (wglAssociateImageBufferEventsI3DFunc)wglGetFunction("wglAssociateImageBufferEventsI3D");
#	endif
#	ifdef wglReleaseImageBufferEventsI3D
	_wglReleaseImageBufferEventsI3D = (wglReleaseImageBufferEventsI3DFunc)wglGetFunction("wglReleaseImageBufferEventsI3D");
#	endif
#	ifdef wglEnableFrameLockI3D
	_wglEnableFrameLockI3D = (wglEnableFrameLockI3DFunc)wglGetFunction("wglEnableFrameLockI3D");
#	endif
#	ifdef wglDisableFrameLockI3D
	_wglDisableFrameLockI3D = (wglDisableFrameLockI3DFunc)wglGetFunction("wglDisableFrameLockI3D");
#	endif
#	ifdef wglIsEnabledFrameLockI3D
	_wglIsEnabledFrameLockI3D = (wglIsEnabledFrameLockI3DFunc)wglGetFunction("wglIsEnabledFrameLockI3D");
#	endif
#	ifdef wglQueryFrameLockMasterI3D
	_wglQueryFrameLockMasterI3D = (wglQueryFrameLockMasterI3DFunc)wglGetFunction("wglQueryFrameLockMasterI3D");
#	endif
#	ifdef wglGetFrameUsageI3D
	_wglGetFrameUsageI3D = (wglGetFrameUsageI3DFunc)wglGetFunction("wglGetFrameUsageI3D");
#	endif
#	ifdef wglBeginFrameTrackingI3D
	_wglBeginFrameTrackingI3D = (wglBeginFrameTrackingI3DFunc)wglGetFunction("wglBeginFrameTrackingI3D");
#	endif
#	ifdef wglEndFrameTrackingI3D
	_wglEndFrameTrackingI3D = (wglEndFrameTrackingI3DFunc)wglGetFunction("wglEndFrameTrackingI3D");
#	endif
#	ifdef wglQueryFrameTrackingI3D
	_wglQueryFrameTrackingI3D = (wglQueryFrameTrackingI3DFunc)wglGetFunction("wglQueryFrameTrackingI3D");
#	endif
#	ifdef wglSetStereoEmitterState3DL
	_wglSetStereoEmitterState3DL = (wglSetStereoEmitterState3DLFunc)wglGetFunction("wglSetStereoEmitterState3DL");
#	endif
#	ifdef wglEnumerateVideoDevicesNV
	_wglEnumerateVideoDevicesNV = (wglEnumerateVideoDevicesNVFunc)wglGetFunction("wglEnumerateVideoDevicesNV");
#	endif
#	ifdef wglBindVideoDeviceNV
	_wglBindVideoDeviceNV = (wglBindVideoDeviceNVFunc)wglGetFunction("wglBindVideoDeviceNV");
#	endif
#	ifdef wglQueryCurrentContextNV
	_wglQueryCurrentContextNV = (wglQueryCurrentContextNVFunc)wglGetFunction("wglQueryCurrentContextNV");
#	endif
#	ifdef wglGetVideoDeviceNV
	_wglGetVideoDeviceNV = (wglGetVideoDeviceNVFunc)wglGetFunction("wglGetVideoDeviceNV");
#	endif
#	ifdef wglReleaseVideoDeviceNV
	_wglReleaseVideoDeviceNV = (wglReleaseVideoDeviceNVFunc)wglGetFunction("wglReleaseVideoDeviceNV");
#	endif
#	ifdef wglBindVideoImageNV
	_wglBindVideoImageNV = (wglBindVideoImageNVFunc)wglGetFunction("wglBindVideoImageNV");
#	endif
#	ifdef wglReleaseVideoImageNV
	_wglReleaseVideoImageNV = (wglReleaseVideoImageNVFunc)wglGetFunction("wglReleaseVideoImageNV");
#	endif
#	ifdef wglSendPbufferToVideoNV
	_wglSendPbufferToVideoNV = (wglSendPbufferToVideoNVFunc)wglGetFunction("wglSendPbufferToVideoNV");
#	endif
#	ifdef wglGetVideoInfoNV
	_wglGetVideoInfoNV = (wglGetVideoInfoNVFunc)wglGetFunction("wglGetVideoInfoNV");
#	endif
#	ifdef wglJoinSwapGroupNV
	_wglJoinSwapGroupNV = (wglJoinSwapGroupNVFunc)wglGetFunction("wglJoinSwapGroupNV");
#	endif
#	ifdef wglBindSwapBarrierNV
	_wglBindSwapBarrierNV = (wglBindSwapBarrierNVFunc)wglGetFunction("wglBindSwapBarrierNV");
#	endif
#	ifdef wglQuerySwapGroupNV
	_wglQuerySwapGroupNV = (wglQuerySwapGroupNVFunc)wglGetFunction("wglQuerySwapGroupNV");
#	endif
#	ifdef wglQueryMaxSwapGroupsNV
	_wglQueryMaxSwapGroupsNV = (wglQueryMaxSwapGroupsNVFunc)wglGetFunction("wglQueryMaxSwapGroupsNV");
#	endif
#	ifdef wglQueryFrameCountNV
	_wglQueryFrameCountNV = (wglQueryFrameCountNVFunc)wglGetFunction("wglQueryFrameCountNV");
#	endif
#	ifdef wglResetFrameCountNV
	_wglResetFrameCountNV = (wglResetFrameCountNVFunc)wglGetFunction("wglResetFrameCountNV");
#	endif
#	ifdef wglEnumGpusNV
	_wglEnumGpusNV = (wglEnumGpusNVFunc)wglGetFunction("wglEnumGpusNV");
#	endif
#	ifdef wglEnumGpuDevicesNV
	_wglEnumGpuDevicesNV = (wglEnumGpuDevicesNVFunc)wglGetFunction("wglEnumGpuDevicesNV");
#	endif
#	ifdef wglCreateAffinityDCNV
	_wglCreateAffinityDCNV = (wglCreateAffinityDCNVFunc)wglGetFunction("wglCreateAffinityDCNV");
#	endif
#	ifdef wglEnumGpusFromAffinityDCNV
	_wglEnumGpusFromAffinityDCNV = (wglEnumGpusFromAffinityDCNVFunc)wglGetFunction("wglEnumGpusFromAffinityDCNV");
#	endif
#	ifdef wglDeleteDCNV
	_wglDeleteDCNV = (wglDeleteDCNVFunc)wglGetFunction("wglDeleteDCNV");
#	endif
#	ifdef wglGetGPUIDsAMD
	_wglGetGPUIDsAMD = (wglGetGPUIDsAMDFunc)wglGetFunction("wglGetGPUIDsAMD");
#	endif
#	ifdef wglGetGPUInfoAMD
	_wglGetGPUInfoAMD = (wglGetGPUInfoAMDFunc)wglGetFunction("wglGetGPUInfoAMD");
#	endif
#	ifdef wglGetContextGPUIDAMD
	_wglGetContextGPUIDAMD = (wglGetContextGPUIDAMDFunc)wglGetFunction("wglGetContextGPUIDAMD");
#	endif
#	ifdef wglCreateAssociatedContextAMD
	_wglCreateAssociatedContextAMD = (wglCreateAssociatedContextAMDFunc)wglGetFunction("wglCreateAssociatedContextAMD");
#	endif
#	ifdef wglCreateAssociatedContextAttribsAMD
	_wglCreateAssociatedContextAttribsAMD = (wglCreateAssociatedContextAttribsAMDFunc)wglGetFunction("wglCreateAssociatedContextAttribsAMD");
#	endif
#	ifdef wglDeleteAssociatedContextAMD
	_wglDeleteAssociatedContextAMD = (wglDeleteAssociatedContextAMDFunc)wglGetFunction("wglDeleteAssociatedContextAMD");
#	endif
#	ifdef wglMakeAssociatedContextCurrentAMD
	_wglMakeAssociatedContextCurrentAMD = (wglMakeAssociatedContextCurrentAMDFunc)wglGetFunction("wglMakeAssociatedContextCurrentAMD");
#	endif
#	ifdef wglGetCurrentAssociatedContextAMD
	_wglGetCurrentAssociatedContextAMD = (wglGetCurrentAssociatedContextAMDFunc)wglGetFunction("wglGetCurrentAssociatedContextAMD");
#	endif
#	ifdef wglBlitContextFramebufferAMD
	_wglBlitContextFramebufferAMD = (wglBlitContextFramebufferAMDFunc)wglGetFunction("wglBlitContextFramebufferAMD");
#	endif
#	ifdef wglBindVideoCaptureDeviceNV
	_wglBindVideoCaptureDeviceNV = (wglBindVideoCaptureDeviceNVFunc)wglGetFunction("wglBindVideoCaptureDeviceNV");
#	endif
#	ifdef wglEnumerateVideoCaptureDevicesNV
	_wglEnumerateVideoCaptureDevicesNV = (wglEnumerateVideoCaptureDevicesNVFunc)wglGetFunction("wglEnumerateVideoCaptureDevicesNV");
#	endif
#	ifdef wglLockVideoCaptureDeviceNV
	_wglLockVideoCaptureDeviceNV = (wglLockVideoCaptureDeviceNVFunc)wglGetFunction("wglLockVideoCaptureDeviceNV");
#	endif
#	ifdef wglQueryVideoCaptureDeviceNV
	_wglQueryVideoCaptureDeviceNV = (wglQueryVideoCaptureDeviceNVFunc)wglGetFunction("wglQueryVideoCaptureDeviceNV");
#	endif
#	ifdef wglReleaseVideoCaptureDeviceNV
	_wglReleaseVideoCaptureDeviceNV = (wglReleaseVideoCaptureDeviceNVFunc)wglGetFunction("wglReleaseVideoCaptureDeviceNV");
#	endif
#	ifdef wglCopyImageSubDataNV
	_wglCopyImageSubDataNV = (wglCopyImageSubDataNVFunc)wglGetFunction("wglCopyImageSubDataNV");
#	endif
#	ifdef wglDXSetResourceShareHandleNV
	_wglDXSetResourceShareHandleNV = (wglDXSetResourceShareHandleNVFunc)wglGetFunction("wglDXSetResourceShareHandleNV");
#	endif
#	ifdef wglDXOpenDeviceNV
	_wglDXOpenDeviceNV = (wglDXOpenDeviceNVFunc)wglGetFunction("wglDXOpenDeviceNV");
#	endif
#	ifdef wglDXCloseDeviceNV
	_wglDXCloseDeviceNV = (wglDXCloseDeviceNVFunc)wglGetFunction("wglDXCloseDeviceNV");
#	endif
#	ifdef wglDXRegisterObjectNV
	_wglDXRegisterObjectNV = (wglDXRegisterObjectNVFunc)wglGetFunction("wglDXRegisterObjectNV");
#	endif
#	ifdef wglDXUnregisterObjectNV
	_wglDXUnregisterObjectNV = (wglDXUnregisterObjectNVFunc)wglGetFunction("wglDXUnregisterObjectNV");
#	endif
#	ifdef wglDXObjectAccessNV
	_wglDXObjectAccessNV = (wglDXObjectAccessNVFunc)wglGetFunction("wglDXObjectAccessNV");
#	endif
#	ifdef wglDXLockObjectsNV
	_wglDXLockObjectsNV = (wglDXLockObjectsNVFunc)wglGetFunction("wglDXLockObjectsNV");
#	endif
#	ifdef wglDXUnlockObjectsNV
	_wglDXUnlockObjectsNV = (wglDXUnlockObjectsNVFunc)wglGetFunction("wglDXUnlockObjectsNV");
#	endif
}

void wglFuncUnload()
{
#	ifdef wglGetCurrentContext
	_wglGetCurrentContext = NULL;
#	endif
#	ifdef wglCopyContext
	_wglCopyContext = NULL;
#	endif
#	ifdef wglChoosePixelFormat
	_wglChoosePixelFormat = NULL;
#	endif
#	ifdef wglDescribePixelFormat
	_wglDescribePixelFormat = NULL;
#	endif
#	ifdef wglGetCurrentDC
	_wglGetCurrentDC = NULL;
#	endif
#	ifdef wglGetDefaultProcAddress
	_wglGetDefaultProcAddress = NULL;
#	endif
#	ifdef wglGetPixelFormat
	_wglGetPixelFormat = NULL;
#	endif
#	ifdef wglSetPixelFormat
	_wglSetPixelFormat = NULL;
#	endif
#	ifdef wglSwapBuffers
	_wglSwapBuffers = NULL;
#	endif
#	ifdef wglShareLists
	_wglShareLists = NULL;
#	endif
#	ifdef wglCreateLayerContext
	_wglCreateLayerContext = NULL;
#	endif
#	ifdef wglDescribeLayerPlane
	_wglDescribeLayerPlane = NULL;
#	endif
#	ifdef wglSetLayerPaletteEntries
	_wglSetLayerPaletteEntries = NULL;
#	endif
#	ifdef wglGetLayerPaletteEntries
	_wglGetLayerPaletteEntries = NULL;
#	endif
#	ifdef wglRealizeLayerPalette
	_wglRealizeLayerPalette = NULL;
#	endif
#	ifdef wglSwapLayerBuffers
	_wglSwapLayerBuffers = NULL;
#	endif
#	ifdef wglUseFontBitmapsA
	_wglUseFontBitmapsA = NULL;
#	endif
#	ifdef wglUseFontBitmapsW
	_wglUseFontBitmapsW = NULL;
#	endif
#	ifdef wglCreateBufferRegionARB
	_wglCreateBufferRegionARB = NULL;
#	endif
#	ifdef wglDeleteBufferRegionARB
	_wglDeleteBufferRegionARB = NULL;
#	endif
#	ifdef wglSaveBufferRegionARB
	_wglSaveBufferRegionARB = NULL;
#	endif
#	ifdef wglRestoreBufferRegionARB
	_wglRestoreBufferRegionARB = NULL;
#	endif
#	ifdef wglGetExtensionsStringARB
	_wglGetExtensionsStringARB = NULL;
#	endif
#	ifdef wglGetPixelFormatAttribivARB
	_wglGetPixelFormatAttribivARB = NULL;
#	endif
#	ifdef wglGetPixelFormatAttribfvARB
	_wglGetPixelFormatAttribfvARB = NULL;
#	endif
#	ifdef wglChoosePixelFormatARB
	_wglChoosePixelFormatARB = NULL;
#	endif
#	ifdef wglMakeContextCurrentARB
	_wglMakeContextCurrentARB = NULL;
#	endif
#	ifdef wglGetCurrentReadDCARB
	_wglGetCurrentReadDCARB = NULL;
#	endif
#	ifdef wglCreatePbufferARB
	_wglCreatePbufferARB = NULL;
#	endif
#	ifdef wglGetPbufferDCARB
	_wglGetPbufferDCARB = NULL;
#	endif
#	ifdef wglReleasePbufferDCARB
	_wglReleasePbufferDCARB = NULL;
#	endif
#	ifdef wglDestroyPbufferARB
	_wglDestroyPbufferARB = NULL;
#	endif
#	ifdef wglQueryPbufferARB
	_wglQueryPbufferARB = NULL;
#	endif
#	ifdef wglBindTexImageARB
	_wglBindTexImageARB = NULL;
#	endif
#	ifdef wglReleaseTexImageARB
	_wglReleaseTexImageARB = NULL;
#	endif
#	ifdef wglSetPbufferAttribARB
	_wglSetPbufferAttribARB = NULL;
#	endif
#	ifdef wglCreateContextAttribsARB
	_wglCreateContextAttribsARB = NULL;
#	endif
#	ifdef wglCreateDisplayColorTableEXT
	_wglCreateDisplayColorTableEXT = NULL;
#	endif
#	ifdef wglLoadDisplayColorTableEXT
	_wglLoadDisplayColorTableEXT = NULL;
#	endif
#	ifdef wglBindDisplayColorTableEXT
	_wglBindDisplayColorTableEXT = NULL;
#	endif
#	ifdef wglDestroyDisplayColorTableEXT
	_wglDestroyDisplayColorTableEXT = NULL;
#	endif
#	ifdef wglGetExtensionsStringEXT
	_wglGetExtensionsStringEXT = NULL;
#	endif
#	ifdef wglMakeContextCurrentEXT
	_wglMakeContextCurrentEXT = NULL;
#	endif
#	ifdef wglGetCurrentReadDCEXT
	_wglGetCurrentReadDCEXT = NULL;
#	endif
#	ifdef wglCreatePbufferEXT
	_wglCreatePbufferEXT = NULL;
#	endif
#	ifdef wglGetPbufferDCEXT
	_wglGetPbufferDCEXT = NULL;
#	endif
#	ifdef wglReleasePbufferDCEXT
	_wglReleasePbufferDCEXT = NULL;
#	endif
#	ifdef wglDestroyPbufferEXT
	_wglDestroyPbufferEXT = NULL;
#	endif
#	ifdef wglQueryPbufferEXT
	_wglQueryPbufferEXT = NULL;
#	endif
#	ifdef wglGetPixelFormatAttribivEXT
	_wglGetPixelFormatAttribivEXT = NULL;
#	endif
#	ifdef wglGetPixelFormatAttribfvEXT
	_wglGetPixelFormatAttribfvEXT = NULL;
#	endif
#	ifdef wglChoosePixelFormatEXT
	_wglChoosePixelFormatEXT = NULL;
#	endif
#	ifdef wglSwapIntervalEXT
	_wglSwapIntervalEXT = NULL;
#	endif
#	ifdef wglGetSwapIntervalEXT
	_wglGetSwapIntervalEXT = NULL;
#	endif
#	ifdef wglAllocateMemoryNV
	_wglAllocateMemoryNV = NULL;
#	endif
#	ifdef wglFreeMemoryNV
	_wglFreeMemoryNV = NULL;
#	endif
#	ifdef wglGetSyncValuesOML
	_wglGetSyncValuesOML = NULL;
#	endif
#	ifdef wglGetMscRateOML
	_wglGetMscRateOML = NULL;
#	endif
#	ifdef wglSwapBuffersMscOML
	_wglSwapBuffersMscOML = NULL;
#	endif
#	ifdef wglSwapLayerBuffersMscOML
	_wglSwapLayerBuffersMscOML = NULL;
#	endif
#	ifdef wglWaitForMscOML
	_wglWaitForMscOML = NULL;
#	endif
#	ifdef wglWaitForSbcOML
	_wglWaitForSbcOML = NULL;
#	endif
#	ifdef wglGetDigitalVideoParametersI3D
	_wglGetDigitalVideoParametersI3D = NULL;
#	endif
#	ifdef wglSetDigitalVideoParametersI3D
	_wglSetDigitalVideoParametersI3D = NULL;
#	endif
#	ifdef wglGetGammaTableParametersI3D
	_wglGetGammaTableParametersI3D = NULL;
#	endif
#	ifdef wglSetGammaTableParametersI3D
	_wglSetGammaTableParametersI3D = NULL;
#	endif
#	ifdef wglGetGammaTableI3D
	_wglGetGammaTableI3D = NULL;
#	endif
#	ifdef wglSetGammaTableI3D
	_wglSetGammaTableI3D = NULL;
#	endif
#	ifdef wglEnableGenlockI3D
	_wglEnableGenlockI3D = NULL;
#	endif
#	ifdef wglDisableGenlockI3D
	_wglDisableGenlockI3D = NULL;
#	endif
#	ifdef wglIsEnabledGenlockI3D
	_wglIsEnabledGenlockI3D = NULL;
#	endif
#	ifdef wglGenlockSourceI3D
	_wglGenlockSourceI3D = NULL;
#	endif
#	ifdef wglGetGenlockSourceI3D
	_wglGetGenlockSourceI3D = NULL;
#	endif
#	ifdef wglGenlockSourceEdgeI3D
	_wglGenlockSourceEdgeI3D = NULL;
#	endif
#	ifdef wglGetGenlockSourceEdgeI3D
	_wglGetGenlockSourceEdgeI3D = NULL;
#	endif
#	ifdef wglGenlockSampleRateI3D
	_wglGenlockSampleRateI3D = NULL;
#	endif
#	ifdef wglGetGenlockSampleRateI3D
	_wglGetGenlockSampleRateI3D = NULL;
#	endif
#	ifdef wglGenlockSourceDelayI3D
	_wglGenlockSourceDelayI3D = NULL;
#	endif
#	ifdef wglGetGenlockSourceDelayI3D
	_wglGetGenlockSourceDelayI3D = NULL;
#	endif
#	ifdef wglQueryGenlockMaxSourceDelayI3D
	_wglQueryGenlockMaxSourceDelayI3D = NULL;
#	endif
#	ifdef wglCreateImageBufferI3D
	_wglCreateImageBufferI3D = NULL;
#	endif
#	ifdef wglDestroyImageBufferI3D
	_wglDestroyImageBufferI3D = NULL;
#	endif
#	ifdef wglAssociateImageBufferEventsI3D
	_wglAssociateImageBufferEventsI3D = NULL;
#	endif
#	ifdef wglReleaseImageBufferEventsI3D
	_wglReleaseImageBufferEventsI3D = NULL;
#	endif
#	ifdef wglEnableFrameLockI3D
	_wglEnableFrameLockI3D = NULL;
#	endif
#	ifdef wglDisableFrameLockI3D
	_wglDisableFrameLockI3D = NULL;
#	endif
#	ifdef wglIsEnabledFrameLockI3D
	_wglIsEnabledFrameLockI3D = NULL;
#	endif
#	ifdef wglQueryFrameLockMasterI3D
	_wglQueryFrameLockMasterI3D = NULL;
#	endif
#	ifdef wglGetFrameUsageI3D
	_wglGetFrameUsageI3D = NULL;
#	endif
#	ifdef wglBeginFrameTrackingI3D
	_wglBeginFrameTrackingI3D = NULL;
#	endif
#	ifdef wglEndFrameTrackingI3D
	_wglEndFrameTrackingI3D = NULL;
#	endif
#	ifdef wglQueryFrameTrackingI3D
	_wglQueryFrameTrackingI3D = NULL;
#	endif
#	ifdef wglSetStereoEmitterState3DL
	_wglSetStereoEmitterState3DL = NULL;
#	endif
#	ifdef wglEnumerateVideoDevicesNV
	_wglEnumerateVideoDevicesNV = NULL;
#	endif
#	ifdef wglBindVideoDeviceNV
	_wglBindVideoDeviceNV = NULL;
#	endif
#	ifdef wglQueryCurrentContextNV
	_wglQueryCurrentContextNV = NULL;
#	endif
#	ifdef wglGetVideoDeviceNV
	_wglGetVideoDeviceNV = NULL;
#	endif
#	ifdef wglReleaseVideoDeviceNV
	_wglReleaseVideoDeviceNV = NULL;
#	endif
#	ifdef wglBindVideoImageNV
	_wglBindVideoImageNV = NULL;
#	endif
#	ifdef wglReleaseVideoImageNV
	_wglReleaseVideoImageNV = NULL;
#	endif
#	ifdef wglSendPbufferToVideoNV
	_wglSendPbufferToVideoNV = NULL;
#	endif
#	ifdef wglGetVideoInfoNV
	_wglGetVideoInfoNV = NULL;
#	endif
#	ifdef wglJoinSwapGroupNV
	_wglJoinSwapGroupNV = NULL;
#	endif
#	ifdef wglBindSwapBarrierNV
	_wglBindSwapBarrierNV = NULL;
#	endif
#	ifdef wglQuerySwapGroupNV
	_wglQuerySwapGroupNV = NULL;
#	endif
#	ifdef wglQueryMaxSwapGroupsNV
	_wglQueryMaxSwapGroupsNV = NULL;
#	endif
#	ifdef wglQueryFrameCountNV
	_wglQueryFrameCountNV = NULL;
#	endif
#	ifdef wglResetFrameCountNV
	_wglResetFrameCountNV = NULL;
#	endif
#	ifdef wglEnumGpusNV
	_wglEnumGpusNV = NULL;
#	endif
#	ifdef wglEnumGpuDevicesNV
	_wglEnumGpuDevicesNV = NULL;
#	endif
#	ifdef wglCreateAffinityDCNV
	_wglCreateAffinityDCNV = NULL;
#	endif
#	ifdef wglEnumGpusFromAffinityDCNV
	_wglEnumGpusFromAffinityDCNV = NULL;
#	endif
#	ifdef wglDeleteDCNV
	_wglDeleteDCNV = NULL;
#	endif
#	ifdef wglGetGPUIDsAMD
	_wglGetGPUIDsAMD = NULL;
#	endif
#	ifdef wglGetGPUInfoAMD
	_wglGetGPUInfoAMD = NULL;
#	endif
#	ifdef wglGetContextGPUIDAMD
	_wglGetContextGPUIDAMD = NULL;
#	endif
#	ifdef wglCreateAssociatedContextAMD
	_wglCreateAssociatedContextAMD = NULL;
#	endif
#	ifdef wglCreateAssociatedContextAttribsAMD
	_wglCreateAssociatedContextAttribsAMD = NULL;
#	endif
#	ifdef wglDeleteAssociatedContextAMD
	_wglDeleteAssociatedContextAMD = NULL;
#	endif
#	ifdef wglMakeAssociatedContextCurrentAMD
	_wglMakeAssociatedContextCurrentAMD = NULL;
#	endif
#	ifdef wglGetCurrentAssociatedContextAMD
	_wglGetCurrentAssociatedContextAMD = NULL;
#	endif
#	ifdef wglBlitContextFramebufferAMD
	_wglBlitContextFramebufferAMD = NULL;
#	endif
#	ifdef wglBindVideoCaptureDeviceNV
	_wglBindVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef wglEnumerateVideoCaptureDevicesNV
	_wglEnumerateVideoCaptureDevicesNV = NULL;
#	endif
#	ifdef wglLockVideoCaptureDeviceNV
	_wglLockVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef wglQueryVideoCaptureDeviceNV
	_wglQueryVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef wglReleaseVideoCaptureDeviceNV
	_wglReleaseVideoCaptureDeviceNV = NULL;
#	endif
#	ifdef wglCopyImageSubDataNV
	_wglCopyImageSubDataNV = NULL;
#	endif
#	ifdef wglDXSetResourceShareHandleNV
	_wglDXSetResourceShareHandleNV = NULL;
#	endif
#	ifdef wglDXOpenDeviceNV
	_wglDXOpenDeviceNV = NULL;
#	endif
#	ifdef wglDXCloseDeviceNV
	_wglDXCloseDeviceNV = NULL;
#	endif
#	ifdef wglDXRegisterObjectNV
	_wglDXRegisterObjectNV = NULL;
#	endif
#	ifdef wglDXUnregisterObjectNV
	_wglDXUnregisterObjectNV = NULL;
#	endif
#	ifdef wglDXObjectAccessNV
	_wglDXObjectAccessNV = NULL;
#	endif
#	ifdef wglDXLockObjectsNV
	_wglDXLockObjectsNV = NULL;
#	endif
#	ifdef wglDXUnlockObjectsNV
	_wglDXUnlockObjectsNV = NULL;
#	endif
}

#endif
