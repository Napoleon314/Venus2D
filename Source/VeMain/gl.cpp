////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   gl.cpp
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

#ifdef VE_GL

#ifdef glCullFace
glCullFaceFunc _glCullFace = NULL;
#endif
#ifdef glFrontFace
glFrontFaceFunc _glFrontFace = NULL;
#endif
#ifdef glHint
glHintFunc _glHint = NULL;
#endif
#ifdef glLineWidth
glLineWidthFunc _glLineWidth = NULL;
#endif
#ifdef glPointSize
glPointSizeFunc _glPointSize = NULL;
#endif
#ifdef glPolygonMode
glPolygonModeFunc _glPolygonMode = NULL;
#endif
#ifdef glScissor
glScissorFunc _glScissor = NULL;
#endif
#ifdef glTexParameterf
glTexParameterfFunc _glTexParameterf = NULL;
#endif
#ifdef glTexParameterfv
glTexParameterfvFunc _glTexParameterfv = NULL;
#endif
#ifdef glTexParameteri
glTexParameteriFunc _glTexParameteri = NULL;
#endif
#ifdef glTexParameteriv
glTexParameterivFunc _glTexParameteriv = NULL;
#endif
#ifdef glTexImage1D
glTexImage1DFunc _glTexImage1D = NULL;
#endif
#ifdef glTexImage2D
glTexImage2DFunc _glTexImage2D = NULL;
#endif
#ifdef glDrawBuffer
glDrawBufferFunc _glDrawBuffer = NULL;
#endif
#ifdef glClear
glClearFunc _glClear = NULL;
#endif
#ifdef glClearColor
glClearColorFunc _glClearColor = NULL;
#endif
#ifdef glClearStencil
glClearStencilFunc _glClearStencil = NULL;
#endif
#ifdef glClearDepth
glClearDepthFunc _glClearDepth = NULL;
#endif
#ifdef glStencilMask
glStencilMaskFunc _glStencilMask = NULL;
#endif
#ifdef glColorMask
glColorMaskFunc _glColorMask = NULL;
#endif
#ifdef glDepthMask
glDepthMaskFunc _glDepthMask = NULL;
#endif
#ifdef glDisable
glDisableFunc _glDisable = NULL;
#endif
#ifdef glEnable
glEnableFunc _glEnable = NULL;
#endif
#ifdef glFinish
glFinishFunc _glFinish = NULL;
#endif
#ifdef glFlush
glFlushFunc _glFlush = NULL;
#endif
#ifdef glBlendFunc
glBlendFuncFunc _glBlendFunc = NULL;
#endif
#ifdef glLogicOp
glLogicOpFunc _glLogicOp = NULL;
#endif
#ifdef glStencilFunc
glStencilFuncFunc _glStencilFunc = NULL;
#endif
#ifdef glStencilOp
glStencilOpFunc _glStencilOp = NULL;
#endif
#ifdef glDepthFunc
glDepthFuncFunc _glDepthFunc = NULL;
#endif
#ifdef glPixelStoref
glPixelStorefFunc _glPixelStoref = NULL;
#endif
#ifdef glPixelStorei
glPixelStoreiFunc _glPixelStorei = NULL;
#endif
#ifdef glReadBuffer
glReadBufferFunc _glReadBuffer = NULL;
#endif
#ifdef glReadPixels
glReadPixelsFunc _glReadPixels = NULL;
#endif
#ifdef glGetBooleanv
glGetBooleanvFunc _glGetBooleanv = NULL;
#endif
#ifdef glGetDoublev
glGetDoublevFunc _glGetDoublev = NULL;
#endif
#ifdef glGetError
glGetErrorFunc _glGetError = NULL;
#endif
#ifdef glGetFloatv
glGetFloatvFunc _glGetFloatv = NULL;
#endif
#ifdef glGetIntegerv
glGetIntegervFunc _glGetIntegerv = NULL;
#endif
#ifdef glGetString
glGetStringFunc _glGetString = NULL;
#endif
#ifdef glGetTexImage
glGetTexImageFunc _glGetTexImage = NULL;
#endif
#ifdef glGetTexParameterfv
glGetTexParameterfvFunc _glGetTexParameterfv = NULL;
#endif
#ifdef glGetTexParameteriv
glGetTexParameterivFunc _glGetTexParameteriv = NULL;
#endif
#ifdef glGetTexLevelParameterfv
glGetTexLevelParameterfvFunc _glGetTexLevelParameterfv = NULL;
#endif
#ifdef glGetTexLevelParameteriv
glGetTexLevelParameterivFunc _glGetTexLevelParameteriv = NULL;
#endif
#ifdef glIsEnabled
glIsEnabledFunc _glIsEnabled = NULL;
#endif
#ifdef glDepthRange
glDepthRangeFunc _glDepthRange = NULL;
#endif
#ifdef glViewport
glViewportFunc _glViewport = NULL;
#endif
#ifdef glNewList
glNewListFunc _glNewList = NULL;
#endif
#ifdef glEndList
glEndListFunc _glEndList = NULL;
#endif
#ifdef glCallList
glCallListFunc _glCallList = NULL;
#endif
#ifdef glCallLists
glCallListsFunc _glCallLists = NULL;
#endif
#ifdef glDeleteLists
glDeleteListsFunc _glDeleteLists = NULL;
#endif
#ifdef glGenLists
glGenListsFunc _glGenLists = NULL;
#endif
#ifdef glListBase
glListBaseFunc _glListBase = NULL;
#endif
#ifdef glBegin
glBeginFunc _glBegin = NULL;
#endif
#ifdef glBitmap
glBitmapFunc _glBitmap = NULL;
#endif
#ifdef glColor3b
glColor3bFunc _glColor3b = NULL;
#endif
#ifdef glColor3bv
glColor3bvFunc _glColor3bv = NULL;
#endif
#ifdef glColor3d
glColor3dFunc _glColor3d = NULL;
#endif
#ifdef glColor3dv
glColor3dvFunc _glColor3dv = NULL;
#endif
#ifdef glColor3f
glColor3fFunc _glColor3f = NULL;
#endif
#ifdef glColor3fv
glColor3fvFunc _glColor3fv = NULL;
#endif
#ifdef glColor3i
glColor3iFunc _glColor3i = NULL;
#endif
#ifdef glColor3iv
glColor3ivFunc _glColor3iv = NULL;
#endif
#ifdef glColor3s
glColor3sFunc _glColor3s = NULL;
#endif
#ifdef glColor3sv
glColor3svFunc _glColor3sv = NULL;
#endif
#ifdef glColor3ub
glColor3ubFunc _glColor3ub = NULL;
#endif
#ifdef glColor3ubv
glColor3ubvFunc _glColor3ubv = NULL;
#endif
#ifdef glColor3ui
glColor3uiFunc _glColor3ui = NULL;
#endif
#ifdef glColor3uiv
glColor3uivFunc _glColor3uiv = NULL;
#endif
#ifdef glColor3us
glColor3usFunc _glColor3us = NULL;
#endif
#ifdef glColor3usv
glColor3usvFunc _glColor3usv = NULL;
#endif
#ifdef glColor4b
glColor4bFunc _glColor4b = NULL;
#endif
#ifdef glColor4bv
glColor4bvFunc _glColor4bv = NULL;
#endif
#ifdef glColor4d
glColor4dFunc _glColor4d = NULL;
#endif
#ifdef glColor4dv
glColor4dvFunc _glColor4dv = NULL;
#endif
#ifdef glColor4f
glColor4fFunc _glColor4f = NULL;
#endif
#ifdef glColor4fv
glColor4fvFunc _glColor4fv = NULL;
#endif
#ifdef glColor4i
glColor4iFunc _glColor4i = NULL;
#endif
#ifdef glColor4iv
glColor4ivFunc _glColor4iv = NULL;
#endif
#ifdef glColor4s
glColor4sFunc _glColor4s = NULL;
#endif
#ifdef glColor4sv
glColor4svFunc _glColor4sv = NULL;
#endif
#ifdef glColor4ub
glColor4ubFunc _glColor4ub = NULL;
#endif
#ifdef glColor4ubv
glColor4ubvFunc _glColor4ubv = NULL;
#endif
#ifdef glColor4ui
glColor4uiFunc _glColor4ui = NULL;
#endif
#ifdef glColor4uiv
glColor4uivFunc _glColor4uiv = NULL;
#endif
#ifdef glColor4us
glColor4usFunc _glColor4us = NULL;
#endif
#ifdef glColor4usv
glColor4usvFunc _glColor4usv = NULL;
#endif
#ifdef glEdgeFlag
glEdgeFlagFunc _glEdgeFlag = NULL;
#endif
#ifdef glEdgeFlagv
glEdgeFlagvFunc _glEdgeFlagv = NULL;
#endif
#ifdef glEnd
glEndFunc _glEnd = NULL;
#endif
#ifdef glIndexd
glIndexdFunc _glIndexd = NULL;
#endif
#ifdef glIndexdv
glIndexdvFunc _glIndexdv = NULL;
#endif
#ifdef glIndexf
glIndexfFunc _glIndexf = NULL;
#endif
#ifdef glIndexfv
glIndexfvFunc _glIndexfv = NULL;
#endif
#ifdef glIndexi
glIndexiFunc _glIndexi = NULL;
#endif
#ifdef glIndexiv
glIndexivFunc _glIndexiv = NULL;
#endif
#ifdef glIndexs
glIndexsFunc _glIndexs = NULL;
#endif
#ifdef glIndexsv
glIndexsvFunc _glIndexsv = NULL;
#endif
#ifdef glNormal3b
glNormal3bFunc _glNormal3b = NULL;
#endif
#ifdef glNormal3bv
glNormal3bvFunc _glNormal3bv = NULL;
#endif
#ifdef glNormal3d
glNormal3dFunc _glNormal3d = NULL;
#endif
#ifdef glNormal3dv
glNormal3dvFunc _glNormal3dv = NULL;
#endif
#ifdef glNormal3f
glNormal3fFunc _glNormal3f = NULL;
#endif
#ifdef glNormal3fv
glNormal3fvFunc _glNormal3fv = NULL;
#endif
#ifdef glNormal3i
glNormal3iFunc _glNormal3i = NULL;
#endif
#ifdef glNormal3iv
glNormal3ivFunc _glNormal3iv = NULL;
#endif
#ifdef glNormal3s
glNormal3sFunc _glNormal3s = NULL;
#endif
#ifdef glNormal3sv
glNormal3svFunc _glNormal3sv = NULL;
#endif
#ifdef glRasterPos2d
glRasterPos2dFunc _glRasterPos2d = NULL;
#endif
#ifdef glRasterPos2dv
glRasterPos2dvFunc _glRasterPos2dv = NULL;
#endif
#ifdef glRasterPos2f
glRasterPos2fFunc _glRasterPos2f = NULL;
#endif
#ifdef glRasterPos2fv
glRasterPos2fvFunc _glRasterPos2fv = NULL;
#endif
#ifdef glRasterPos2i
glRasterPos2iFunc _glRasterPos2i = NULL;
#endif
#ifdef glRasterPos2iv
glRasterPos2ivFunc _glRasterPos2iv = NULL;
#endif
#ifdef glRasterPos2s
glRasterPos2sFunc _glRasterPos2s = NULL;
#endif
#ifdef glRasterPos2sv
glRasterPos2svFunc _glRasterPos2sv = NULL;
#endif
#ifdef glRasterPos3d
glRasterPos3dFunc _glRasterPos3d = NULL;
#endif
#ifdef glRasterPos3dv
glRasterPos3dvFunc _glRasterPos3dv = NULL;
#endif
#ifdef glRasterPos3f
glRasterPos3fFunc _glRasterPos3f = NULL;
#endif
#ifdef glRasterPos3fv
glRasterPos3fvFunc _glRasterPos3fv = NULL;
#endif
#ifdef glRasterPos3i
glRasterPos3iFunc _glRasterPos3i = NULL;
#endif
#ifdef glRasterPos3iv
glRasterPos3ivFunc _glRasterPos3iv = NULL;
#endif
#ifdef glRasterPos3s
glRasterPos3sFunc _glRasterPos3s = NULL;
#endif
#ifdef glRasterPos3sv
glRasterPos3svFunc _glRasterPos3sv = NULL;
#endif
#ifdef glRasterPos4d
glRasterPos4dFunc _glRasterPos4d = NULL;
#endif
#ifdef glRasterPos4dv
glRasterPos4dvFunc _glRasterPos4dv = NULL;
#endif
#ifdef glRasterPos4f
glRasterPos4fFunc _glRasterPos4f = NULL;
#endif
#ifdef glRasterPos4fv
glRasterPos4fvFunc _glRasterPos4fv = NULL;
#endif
#ifdef glRasterPos4i
glRasterPos4iFunc _glRasterPos4i = NULL;
#endif
#ifdef glRasterPos4iv
glRasterPos4ivFunc _glRasterPos4iv = NULL;
#endif
#ifdef glRasterPos4s
glRasterPos4sFunc _glRasterPos4s = NULL;
#endif
#ifdef glRasterPos4sv
glRasterPos4svFunc _glRasterPos4sv = NULL;
#endif
#ifdef glRectd
glRectdFunc _glRectd = NULL;
#endif
#ifdef glRectdv
glRectdvFunc _glRectdv = NULL;
#endif
#ifdef glRectf
glRectfFunc _glRectf = NULL;
#endif
#ifdef glRectfv
glRectfvFunc _glRectfv = NULL;
#endif
#ifdef glRecti
glRectiFunc _glRecti = NULL;
#endif
#ifdef glRectiv
glRectivFunc _glRectiv = NULL;
#endif
#ifdef glRects
glRectsFunc _glRects = NULL;
#endif
#ifdef glRectsv
glRectsvFunc _glRectsv = NULL;
#endif
#ifdef glTexCoord1d
glTexCoord1dFunc _glTexCoord1d = NULL;
#endif
#ifdef glTexCoord1dv
glTexCoord1dvFunc _glTexCoord1dv = NULL;
#endif
#ifdef glTexCoord1f
glTexCoord1fFunc _glTexCoord1f = NULL;
#endif
#ifdef glTexCoord1fv
glTexCoord1fvFunc _glTexCoord1fv = NULL;
#endif
#ifdef glTexCoord1i
glTexCoord1iFunc _glTexCoord1i = NULL;
#endif
#ifdef glTexCoord1iv
glTexCoord1ivFunc _glTexCoord1iv = NULL;
#endif
#ifdef glTexCoord1s
glTexCoord1sFunc _glTexCoord1s = NULL;
#endif
#ifdef glTexCoord1sv
glTexCoord1svFunc _glTexCoord1sv = NULL;
#endif
#ifdef glTexCoord2d
glTexCoord2dFunc _glTexCoord2d = NULL;
#endif
#ifdef glTexCoord2dv
glTexCoord2dvFunc _glTexCoord2dv = NULL;
#endif
#ifdef glTexCoord2f
glTexCoord2fFunc _glTexCoord2f = NULL;
#endif
#ifdef glTexCoord2fv
glTexCoord2fvFunc _glTexCoord2fv = NULL;
#endif
#ifdef glTexCoord2i
glTexCoord2iFunc _glTexCoord2i = NULL;
#endif
#ifdef glTexCoord2iv
glTexCoord2ivFunc _glTexCoord2iv = NULL;
#endif
#ifdef glTexCoord2s
glTexCoord2sFunc _glTexCoord2s = NULL;
#endif
#ifdef glTexCoord2sv
glTexCoord2svFunc _glTexCoord2sv = NULL;
#endif
#ifdef glTexCoord3d
glTexCoord3dFunc _glTexCoord3d = NULL;
#endif
#ifdef glTexCoord3dv
glTexCoord3dvFunc _glTexCoord3dv = NULL;
#endif
#ifdef glTexCoord3f
glTexCoord3fFunc _glTexCoord3f = NULL;
#endif
#ifdef glTexCoord3fv
glTexCoord3fvFunc _glTexCoord3fv = NULL;
#endif
#ifdef glTexCoord3i
glTexCoord3iFunc _glTexCoord3i = NULL;
#endif
#ifdef glTexCoord3iv
glTexCoord3ivFunc _glTexCoord3iv = NULL;
#endif
#ifdef glTexCoord3s
glTexCoord3sFunc _glTexCoord3s = NULL;
#endif
#ifdef glTexCoord3sv
glTexCoord3svFunc _glTexCoord3sv = NULL;
#endif
#ifdef glTexCoord4d
glTexCoord4dFunc _glTexCoord4d = NULL;
#endif
#ifdef glTexCoord4dv
glTexCoord4dvFunc _glTexCoord4dv = NULL;
#endif
#ifdef glTexCoord4f
glTexCoord4fFunc _glTexCoord4f = NULL;
#endif
#ifdef glTexCoord4fv
glTexCoord4fvFunc _glTexCoord4fv = NULL;
#endif
#ifdef glTexCoord4i
glTexCoord4iFunc _glTexCoord4i = NULL;
#endif
#ifdef glTexCoord4iv
glTexCoord4ivFunc _glTexCoord4iv = NULL;
#endif
#ifdef glTexCoord4s
glTexCoord4sFunc _glTexCoord4s = NULL;
#endif
#ifdef glTexCoord4sv
glTexCoord4svFunc _glTexCoord4sv = NULL;
#endif
#ifdef glVertex2d
glVertex2dFunc _glVertex2d = NULL;
#endif
#ifdef glVertex2dv
glVertex2dvFunc _glVertex2dv = NULL;
#endif
#ifdef glVertex2f
glVertex2fFunc _glVertex2f = NULL;
#endif
#ifdef glVertex2fv
glVertex2fvFunc _glVertex2fv = NULL;
#endif
#ifdef glVertex2i
glVertex2iFunc _glVertex2i = NULL;
#endif
#ifdef glVertex2iv
glVertex2ivFunc _glVertex2iv = NULL;
#endif
#ifdef glVertex2s
glVertex2sFunc _glVertex2s = NULL;
#endif
#ifdef glVertex2sv
glVertex2svFunc _glVertex2sv = NULL;
#endif
#ifdef glVertex3d
glVertex3dFunc _glVertex3d = NULL;
#endif
#ifdef glVertex3dv
glVertex3dvFunc _glVertex3dv = NULL;
#endif
#ifdef glVertex3f
glVertex3fFunc _glVertex3f = NULL;
#endif
#ifdef glVertex3fv
glVertex3fvFunc _glVertex3fv = NULL;
#endif
#ifdef glVertex3i
glVertex3iFunc _glVertex3i = NULL;
#endif
#ifdef glVertex3iv
glVertex3ivFunc _glVertex3iv = NULL;
#endif
#ifdef glVertex3s
glVertex3sFunc _glVertex3s = NULL;
#endif
#ifdef glVertex3sv
glVertex3svFunc _glVertex3sv = NULL;
#endif
#ifdef glVertex4d
glVertex4dFunc _glVertex4d = NULL;
#endif
#ifdef glVertex4dv
glVertex4dvFunc _glVertex4dv = NULL;
#endif
#ifdef glVertex4f
glVertex4fFunc _glVertex4f = NULL;
#endif
#ifdef glVertex4fv
glVertex4fvFunc _glVertex4fv = NULL;
#endif
#ifdef glVertex4i
glVertex4iFunc _glVertex4i = NULL;
#endif
#ifdef glVertex4iv
glVertex4ivFunc _glVertex4iv = NULL;
#endif
#ifdef glVertex4s
glVertex4sFunc _glVertex4s = NULL;
#endif
#ifdef glVertex4sv
glVertex4svFunc _glVertex4sv = NULL;
#endif
#ifdef glClipPlane
glClipPlaneFunc _glClipPlane = NULL;
#endif
#ifdef glColorMaterial
glColorMaterialFunc _glColorMaterial = NULL;
#endif
#ifdef glFogf
glFogfFunc _glFogf = NULL;
#endif
#ifdef glFogfv
glFogfvFunc _glFogfv = NULL;
#endif
#ifdef glFogi
glFogiFunc _glFogi = NULL;
#endif
#ifdef glFogiv
glFogivFunc _glFogiv = NULL;
#endif
#ifdef glLightf
glLightfFunc _glLightf = NULL;
#endif
#ifdef glLightfv
glLightfvFunc _glLightfv = NULL;
#endif
#ifdef glLighti
glLightiFunc _glLighti = NULL;
#endif
#ifdef glLightiv
glLightivFunc _glLightiv = NULL;
#endif
#ifdef glLightModelf
glLightModelfFunc _glLightModelf = NULL;
#endif
#ifdef glLightModelfv
glLightModelfvFunc _glLightModelfv = NULL;
#endif
#ifdef glLightModeli
glLightModeliFunc _glLightModeli = NULL;
#endif
#ifdef glLightModeliv
glLightModelivFunc _glLightModeliv = NULL;
#endif
#ifdef glLineStipple
glLineStippleFunc _glLineStipple = NULL;
#endif
#ifdef glMaterialf
glMaterialfFunc _glMaterialf = NULL;
#endif
#ifdef glMaterialfv
glMaterialfvFunc _glMaterialfv = NULL;
#endif
#ifdef glMateriali
glMaterialiFunc _glMateriali = NULL;
#endif
#ifdef glMaterialiv
glMaterialivFunc _glMaterialiv = NULL;
#endif
#ifdef glPolygonStipple
glPolygonStippleFunc _glPolygonStipple = NULL;
#endif
#ifdef glShadeModel
glShadeModelFunc _glShadeModel = NULL;
#endif
#ifdef glTexEnvf
glTexEnvfFunc _glTexEnvf = NULL;
#endif
#ifdef glTexEnvfv
glTexEnvfvFunc _glTexEnvfv = NULL;
#endif
#ifdef glTexEnvi
glTexEnviFunc _glTexEnvi = NULL;
#endif
#ifdef glTexEnviv
glTexEnvivFunc _glTexEnviv = NULL;
#endif
#ifdef glTexGend
glTexGendFunc _glTexGend = NULL;
#endif
#ifdef glTexGendv
glTexGendvFunc _glTexGendv = NULL;
#endif
#ifdef glTexGenf
glTexGenfFunc _glTexGenf = NULL;
#endif
#ifdef glTexGenfv
glTexGenfvFunc _glTexGenfv = NULL;
#endif
#ifdef glTexGeni
glTexGeniFunc _glTexGeni = NULL;
#endif
#ifdef glTexGeniv
glTexGenivFunc _glTexGeniv = NULL;
#endif
#ifdef glFeedbackBuffer
glFeedbackBufferFunc _glFeedbackBuffer = NULL;
#endif
#ifdef glSelectBuffer
glSelectBufferFunc _glSelectBuffer = NULL;
#endif
#ifdef glRenderMode
glRenderModeFunc _glRenderMode = NULL;
#endif
#ifdef glInitNames
glInitNamesFunc _glInitNames = NULL;
#endif
#ifdef glLoadName
glLoadNameFunc _glLoadName = NULL;
#endif
#ifdef glPassThrough
glPassThroughFunc _glPassThrough = NULL;
#endif
#ifdef glPopName
glPopNameFunc _glPopName = NULL;
#endif
#ifdef glPushName
glPushNameFunc _glPushName = NULL;
#endif
#ifdef glClearAccum
glClearAccumFunc _glClearAccum = NULL;
#endif
#ifdef glClearIndex
glClearIndexFunc _glClearIndex = NULL;
#endif
#ifdef glIndexMask
glIndexMaskFunc _glIndexMask = NULL;
#endif
#ifdef glAccum
glAccumFunc _glAccum = NULL;
#endif
#ifdef glPopAttrib
glPopAttribFunc _glPopAttrib = NULL;
#endif
#ifdef glPushAttrib
glPushAttribFunc _glPushAttrib = NULL;
#endif
#ifdef glMap1d
glMap1dFunc _glMap1d = NULL;
#endif
#ifdef glMap1f
glMap1fFunc _glMap1f = NULL;
#endif
#ifdef glMap2d
glMap2dFunc _glMap2d = NULL;
#endif
#ifdef glMap2f
glMap2fFunc _glMap2f = NULL;
#endif
#ifdef glMapGrid1d
glMapGrid1dFunc _glMapGrid1d = NULL;
#endif
#ifdef glMapGrid1f
glMapGrid1fFunc _glMapGrid1f = NULL;
#endif
#ifdef glMapGrid2d
glMapGrid2dFunc _glMapGrid2d = NULL;
#endif
#ifdef glMapGrid2f
glMapGrid2fFunc _glMapGrid2f = NULL;
#endif
#ifdef glEvalCoord1d
glEvalCoord1dFunc _glEvalCoord1d = NULL;
#endif
#ifdef glEvalCoord1dv
glEvalCoord1dvFunc _glEvalCoord1dv = NULL;
#endif
#ifdef glEvalCoord1f
glEvalCoord1fFunc _glEvalCoord1f = NULL;
#endif
#ifdef glEvalCoord1fv
glEvalCoord1fvFunc _glEvalCoord1fv = NULL;
#endif
#ifdef glEvalCoord2d
glEvalCoord2dFunc _glEvalCoord2d = NULL;
#endif
#ifdef glEvalCoord2dv
glEvalCoord2dvFunc _glEvalCoord2dv = NULL;
#endif
#ifdef glEvalCoord2f
glEvalCoord2fFunc _glEvalCoord2f = NULL;
#endif
#ifdef glEvalCoord2fv
glEvalCoord2fvFunc _glEvalCoord2fv = NULL;
#endif
#ifdef glEvalMesh1
glEvalMesh1Func _glEvalMesh1 = NULL;
#endif
#ifdef glEvalPoint1
glEvalPoint1Func _glEvalPoint1 = NULL;
#endif
#ifdef glEvalMesh2
glEvalMesh2Func _glEvalMesh2 = NULL;
#endif
#ifdef glEvalPoint2
glEvalPoint2Func _glEvalPoint2 = NULL;
#endif
#ifdef glAlphaFunc
glAlphaFuncFunc _glAlphaFunc = NULL;
#endif
#ifdef glPixelZoom
glPixelZoomFunc _glPixelZoom = NULL;
#endif
#ifdef glPixelTransferf
glPixelTransferfFunc _glPixelTransferf = NULL;
#endif
#ifdef glPixelTransferi
glPixelTransferiFunc _glPixelTransferi = NULL;
#endif
#ifdef glPixelMapfv
glPixelMapfvFunc _glPixelMapfv = NULL;
#endif
#ifdef glPixelMapuiv
glPixelMapuivFunc _glPixelMapuiv = NULL;
#endif
#ifdef glPixelMapusv
glPixelMapusvFunc _glPixelMapusv = NULL;
#endif
#ifdef glCopyPixels
glCopyPixelsFunc _glCopyPixels = NULL;
#endif
#ifdef glDrawPixels
glDrawPixelsFunc _glDrawPixels = NULL;
#endif
#ifdef glGetClipPlane
glGetClipPlaneFunc _glGetClipPlane = NULL;
#endif
#ifdef glGetLightfv
glGetLightfvFunc _glGetLightfv = NULL;
#endif
#ifdef glGetLightiv
glGetLightivFunc _glGetLightiv = NULL;
#endif
#ifdef glGetMapdv
glGetMapdvFunc _glGetMapdv = NULL;
#endif
#ifdef glGetMapfv
glGetMapfvFunc _glGetMapfv = NULL;
#endif
#ifdef glGetMapiv
glGetMapivFunc _glGetMapiv = NULL;
#endif
#ifdef glGetMaterialfv
glGetMaterialfvFunc _glGetMaterialfv = NULL;
#endif
#ifdef glGetMaterialiv
glGetMaterialivFunc _glGetMaterialiv = NULL;
#endif
#ifdef glGetPixelMapfv
glGetPixelMapfvFunc _glGetPixelMapfv = NULL;
#endif
#ifdef glGetPixelMapuiv
glGetPixelMapuivFunc _glGetPixelMapuiv = NULL;
#endif
#ifdef glGetPixelMapusv
glGetPixelMapusvFunc _glGetPixelMapusv = NULL;
#endif
#ifdef glGetPolygonStipple
glGetPolygonStippleFunc _glGetPolygonStipple = NULL;
#endif
#ifdef glGetTexEnvfv
glGetTexEnvfvFunc _glGetTexEnvfv = NULL;
#endif
#ifdef glGetTexEnviv
glGetTexEnvivFunc _glGetTexEnviv = NULL;
#endif
#ifdef glGetTexGendv
glGetTexGendvFunc _glGetTexGendv = NULL;
#endif
#ifdef glGetTexGenfv
glGetTexGenfvFunc _glGetTexGenfv = NULL;
#endif
#ifdef glGetTexGeniv
glGetTexGenivFunc _glGetTexGeniv = NULL;
#endif
#ifdef glIsList
glIsListFunc _glIsList = NULL;
#endif
#ifdef glFrustum
glFrustumFunc _glFrustum = NULL;
#endif
#ifdef glLoadIdentity
glLoadIdentityFunc _glLoadIdentity = NULL;
#endif
#ifdef glLoadMatrixf
glLoadMatrixfFunc _glLoadMatrixf = NULL;
#endif
#ifdef glLoadMatrixd
glLoadMatrixdFunc _glLoadMatrixd = NULL;
#endif
#ifdef glMatrixMode
glMatrixModeFunc _glMatrixMode = NULL;
#endif
#ifdef glMultMatrixf
glMultMatrixfFunc _glMultMatrixf = NULL;
#endif
#ifdef glMultMatrixd
glMultMatrixdFunc _glMultMatrixd = NULL;
#endif
#ifdef glOrtho
glOrthoFunc _glOrtho = NULL;
#endif
#ifdef glPopMatrix
glPopMatrixFunc _glPopMatrix = NULL;
#endif
#ifdef glPushMatrix
glPushMatrixFunc _glPushMatrix = NULL;
#endif
#ifdef glRotated
glRotatedFunc _glRotated = NULL;
#endif
#ifdef glRotatef
glRotatefFunc _glRotatef = NULL;
#endif
#ifdef glScaled
glScaledFunc _glScaled = NULL;
#endif
#ifdef glScalef
glScalefFunc _glScalef = NULL;
#endif
#ifdef glTranslated
glTranslatedFunc _glTranslated = NULL;
#endif
#ifdef glTranslatef
glTranslatefFunc _glTranslatef = NULL;
#endif
#ifdef glDrawArrays
glDrawArraysFunc _glDrawArrays = NULL;
#endif
#ifdef glDrawElements
glDrawElementsFunc _glDrawElements = NULL;
#endif
#ifdef glGetPointerv
glGetPointervFunc _glGetPointerv = NULL;
#endif
#ifdef glPolygonOffset
glPolygonOffsetFunc _glPolygonOffset = NULL;
#endif
#ifdef glCopyTexImage1D
glCopyTexImage1DFunc _glCopyTexImage1D = NULL;
#endif
#ifdef glCopyTexImage2D
glCopyTexImage2DFunc _glCopyTexImage2D = NULL;
#endif
#ifdef glCopyTexSubImage1D
glCopyTexSubImage1DFunc _glCopyTexSubImage1D = NULL;
#endif
#ifdef glCopyTexSubImage2D
glCopyTexSubImage2DFunc _glCopyTexSubImage2D = NULL;
#endif
#ifdef glTexSubImage1D
glTexSubImage1DFunc _glTexSubImage1D = NULL;
#endif
#ifdef glTexSubImage2D
glTexSubImage2DFunc _glTexSubImage2D = NULL;
#endif
#ifdef glBindTexture
glBindTextureFunc _glBindTexture = NULL;
#endif
#ifdef glDeleteTextures
glDeleteTexturesFunc _glDeleteTextures = NULL;
#endif
#ifdef glGenTextures
glGenTexturesFunc _glGenTextures = NULL;
#endif
#ifdef glIsTexture
glIsTextureFunc _glIsTexture = NULL;
#endif
#ifdef glArrayElement
glArrayElementFunc _glArrayElement = NULL;
#endif
#ifdef glColorPointer
glColorPointerFunc _glColorPointer = NULL;
#endif
#ifdef glDisableClientState
glDisableClientStateFunc _glDisableClientState = NULL;
#endif
#ifdef glEdgeFlagPointer
glEdgeFlagPointerFunc _glEdgeFlagPointer = NULL;
#endif
#ifdef glEnableClientState
glEnableClientStateFunc _glEnableClientState = NULL;
#endif
#ifdef glIndexPointer
glIndexPointerFunc _glIndexPointer = NULL;
#endif
#ifdef glInterleavedArrays
glInterleavedArraysFunc _glInterleavedArrays = NULL;
#endif
#ifdef glNormalPointer
glNormalPointerFunc _glNormalPointer = NULL;
#endif
#ifdef glTexCoordPointer
glTexCoordPointerFunc _glTexCoordPointer = NULL;
#endif
#ifdef glVertexPointer
glVertexPointerFunc _glVertexPointer = NULL;
#endif
#ifdef glAreTexturesResident
glAreTexturesResidentFunc _glAreTexturesResident = NULL;
#endif
#ifdef glPrioritizeTextures
glPrioritizeTexturesFunc _glPrioritizeTextures = NULL;
#endif
#ifdef glIndexub
glIndexubFunc _glIndexub = NULL;
#endif
#ifdef glIndexubv
glIndexubvFunc _glIndexubv = NULL;
#endif
#ifdef glPopClientAttrib
glPopClientAttribFunc _glPopClientAttrib = NULL;
#endif
#ifdef glPushClientAttrib
glPushClientAttribFunc _glPushClientAttrib = NULL;
#endif
#ifdef glBlendColor
glBlendColorFunc _glBlendColor = NULL;
#endif
#ifdef glBlendEquation
glBlendEquationFunc _glBlendEquation = NULL;
#endif
#ifdef glDrawRangeElements
glDrawRangeElementsFunc _glDrawRangeElements = NULL;
#endif
#ifdef glTexImage3D
glTexImage3DFunc _glTexImage3D = NULL;
#endif
#ifdef glTexSubImage3D
glTexSubImage3DFunc _glTexSubImage3D = NULL;
#endif
#ifdef glCopyTexSubImage3D
glCopyTexSubImage3DFunc _glCopyTexSubImage3D = NULL;
#endif
#ifdef glColorTable
glColorTableFunc _glColorTable = NULL;
#endif
#ifdef glColorTableParameterfv
glColorTableParameterfvFunc _glColorTableParameterfv = NULL;
#endif
#ifdef glColorTableParameteriv
glColorTableParameterivFunc _glColorTableParameteriv = NULL;
#endif
#ifdef glCopyColorTable
glCopyColorTableFunc _glCopyColorTable = NULL;
#endif
#ifdef glGetColorTable
glGetColorTableFunc _glGetColorTable = NULL;
#endif
#ifdef glGetColorTableParameterfv
glGetColorTableParameterfvFunc _glGetColorTableParameterfv = NULL;
#endif
#ifdef glGetColorTableParameteriv
glGetColorTableParameterivFunc _glGetColorTableParameteriv = NULL;
#endif
#ifdef glColorSubTable
glColorSubTableFunc _glColorSubTable = NULL;
#endif
#ifdef glCopyColorSubTable
glCopyColorSubTableFunc _glCopyColorSubTable = NULL;
#endif
#ifdef glConvolutionFilter1D
glConvolutionFilter1DFunc _glConvolutionFilter1D = NULL;
#endif
#ifdef glConvolutionFilter2D
glConvolutionFilter2DFunc _glConvolutionFilter2D = NULL;
#endif
#ifdef glConvolutionParameterf
glConvolutionParameterfFunc _glConvolutionParameterf = NULL;
#endif
#ifdef glConvolutionParameterfv
glConvolutionParameterfvFunc _glConvolutionParameterfv = NULL;
#endif
#ifdef glConvolutionParameteri
glConvolutionParameteriFunc _glConvolutionParameteri = NULL;
#endif
#ifdef glConvolutionParameteriv
glConvolutionParameterivFunc _glConvolutionParameteriv = NULL;
#endif
#ifdef glCopyConvolutionFilter1D
glCopyConvolutionFilter1DFunc _glCopyConvolutionFilter1D = NULL;
#endif
#ifdef glCopyConvolutionFilter2D
glCopyConvolutionFilter2DFunc _glCopyConvolutionFilter2D = NULL;
#endif
#ifdef glGetConvolutionFilter
glGetConvolutionFilterFunc _glGetConvolutionFilter = NULL;
#endif
#ifdef glGetConvolutionParameterfv
glGetConvolutionParameterfvFunc _glGetConvolutionParameterfv = NULL;
#endif
#ifdef glGetConvolutionParameteriv
glGetConvolutionParameterivFunc _glGetConvolutionParameteriv = NULL;
#endif
#ifdef glGetSeparableFilter
glGetSeparableFilterFunc _glGetSeparableFilter = NULL;
#endif
#ifdef glSeparableFilter2D
glSeparableFilter2DFunc _glSeparableFilter2D = NULL;
#endif
#ifdef glGetHistogram
glGetHistogramFunc _glGetHistogram = NULL;
#endif
#ifdef glGetHistogramParameterfv
glGetHistogramParameterfvFunc _glGetHistogramParameterfv = NULL;
#endif
#ifdef glGetHistogramParameteriv
glGetHistogramParameterivFunc _glGetHistogramParameteriv = NULL;
#endif
#ifdef glGetMinmax
glGetMinmaxFunc _glGetMinmax = NULL;
#endif
#ifdef glGetMinmaxParameterfv
glGetMinmaxParameterfvFunc _glGetMinmaxParameterfv = NULL;
#endif
#ifdef glGetMinmaxParameteriv
glGetMinmaxParameterivFunc _glGetMinmaxParameteriv = NULL;
#endif
#ifdef glHistogram
glHistogramFunc _glHistogram = NULL;
#endif
#ifdef glMinmax
glMinmaxFunc _glMinmax = NULL;
#endif
#ifdef glResetHistogram
glResetHistogramFunc _glResetHistogram = NULL;
#endif
#ifdef glResetMinmax
glResetMinmaxFunc _glResetMinmax = NULL;
#endif
#ifdef glActiveTexture
glActiveTextureFunc _glActiveTexture = NULL;
#endif
#ifdef glSampleCoverage
glSampleCoverageFunc _glSampleCoverage = NULL;
#endif
#ifdef glCompressedTexImage3D
glCompressedTexImage3DFunc _glCompressedTexImage3D = NULL;
#endif
#ifdef glCompressedTexImage2D
glCompressedTexImage2DFunc _glCompressedTexImage2D = NULL;
#endif
#ifdef glCompressedTexImage1D
glCompressedTexImage1DFunc _glCompressedTexImage1D = NULL;
#endif
#ifdef glCompressedTexSubImage3D
glCompressedTexSubImage3DFunc _glCompressedTexSubImage3D = NULL;
#endif
#ifdef glCompressedTexSubImage2D
glCompressedTexSubImage2DFunc _glCompressedTexSubImage2D = NULL;
#endif
#ifdef glCompressedTexSubImage1D
glCompressedTexSubImage1DFunc _glCompressedTexSubImage1D = NULL;
#endif
#ifdef glGetCompressedTexImage
glGetCompressedTexImageFunc _glGetCompressedTexImage = NULL;
#endif
#ifdef glClientActiveTexture
glClientActiveTextureFunc _glClientActiveTexture = NULL;
#endif
#ifdef glMultiTexCoord1d
glMultiTexCoord1dFunc _glMultiTexCoord1d = NULL;
#endif
#ifdef glMultiTexCoord1dv
glMultiTexCoord1dvFunc _glMultiTexCoord1dv = NULL;
#endif
#ifdef glMultiTexCoord1f
glMultiTexCoord1fFunc _glMultiTexCoord1f = NULL;
#endif
#ifdef glMultiTexCoord1fv
glMultiTexCoord1fvFunc _glMultiTexCoord1fv = NULL;
#endif
#ifdef glMultiTexCoord1i
glMultiTexCoord1iFunc _glMultiTexCoord1i = NULL;
#endif
#ifdef glMultiTexCoord1iv
glMultiTexCoord1ivFunc _glMultiTexCoord1iv = NULL;
#endif
#ifdef glMultiTexCoord1s
glMultiTexCoord1sFunc _glMultiTexCoord1s = NULL;
#endif
#ifdef glMultiTexCoord1sv
glMultiTexCoord1svFunc _glMultiTexCoord1sv = NULL;
#endif
#ifdef glMultiTexCoord2d
glMultiTexCoord2dFunc _glMultiTexCoord2d = NULL;
#endif
#ifdef glMultiTexCoord2dv
glMultiTexCoord2dvFunc _glMultiTexCoord2dv = NULL;
#endif
#ifdef glMultiTexCoord2f
glMultiTexCoord2fFunc _glMultiTexCoord2f = NULL;
#endif
#ifdef glMultiTexCoord2fv
glMultiTexCoord2fvFunc _glMultiTexCoord2fv = NULL;
#endif
#ifdef glMultiTexCoord2i
glMultiTexCoord2iFunc _glMultiTexCoord2i = NULL;
#endif
#ifdef glMultiTexCoord2iv
glMultiTexCoord2ivFunc _glMultiTexCoord2iv = NULL;
#endif
#ifdef glMultiTexCoord2s
glMultiTexCoord2sFunc _glMultiTexCoord2s = NULL;
#endif
#ifdef glMultiTexCoord2sv
glMultiTexCoord2svFunc _glMultiTexCoord2sv = NULL;
#endif
#ifdef glMultiTexCoord3d
glMultiTexCoord3dFunc _glMultiTexCoord3d = NULL;
#endif
#ifdef glMultiTexCoord3dv
glMultiTexCoord3dvFunc _glMultiTexCoord3dv = NULL;
#endif
#ifdef glMultiTexCoord3f
glMultiTexCoord3fFunc _glMultiTexCoord3f = NULL;
#endif
#ifdef glMultiTexCoord3fv
glMultiTexCoord3fvFunc _glMultiTexCoord3fv = NULL;
#endif
#ifdef glMultiTexCoord3i
glMultiTexCoord3iFunc _glMultiTexCoord3i = NULL;
#endif
#ifdef glMultiTexCoord3iv
glMultiTexCoord3ivFunc _glMultiTexCoord3iv = NULL;
#endif
#ifdef glMultiTexCoord3s
glMultiTexCoord3sFunc _glMultiTexCoord3s = NULL;
#endif
#ifdef glMultiTexCoord3sv
glMultiTexCoord3svFunc _glMultiTexCoord3sv = NULL;
#endif
#ifdef glMultiTexCoord4d
glMultiTexCoord4dFunc _glMultiTexCoord4d = NULL;
#endif
#ifdef glMultiTexCoord4dv
glMultiTexCoord4dvFunc _glMultiTexCoord4dv = NULL;
#endif
#ifdef glMultiTexCoord4f
glMultiTexCoord4fFunc _glMultiTexCoord4f = NULL;
#endif
#ifdef glMultiTexCoord4fv
glMultiTexCoord4fvFunc _glMultiTexCoord4fv = NULL;
#endif
#ifdef glMultiTexCoord4i
glMultiTexCoord4iFunc _glMultiTexCoord4i = NULL;
#endif
#ifdef glMultiTexCoord4iv
glMultiTexCoord4ivFunc _glMultiTexCoord4iv = NULL;
#endif
#ifdef glMultiTexCoord4s
glMultiTexCoord4sFunc _glMultiTexCoord4s = NULL;
#endif
#ifdef glMultiTexCoord4sv
glMultiTexCoord4svFunc _glMultiTexCoord4sv = NULL;
#endif
#ifdef glLoadTransposeMatrixf
glLoadTransposeMatrixfFunc _glLoadTransposeMatrixf = NULL;
#endif
#ifdef glLoadTransposeMatrixd
glLoadTransposeMatrixdFunc _glLoadTransposeMatrixd = NULL;
#endif
#ifdef glMultTransposeMatrixf
glMultTransposeMatrixfFunc _glMultTransposeMatrixf = NULL;
#endif
#ifdef glMultTransposeMatrixd
glMultTransposeMatrixdFunc _glMultTransposeMatrixd = NULL;
#endif
#ifdef glBlendFuncSeparate
glBlendFuncSeparateFunc _glBlendFuncSeparate = NULL;
#endif
#ifdef glMultiDrawArrays
glMultiDrawArraysFunc _glMultiDrawArrays = NULL;
#endif
#ifdef glMultiDrawElements
glMultiDrawElementsFunc _glMultiDrawElements = NULL;
#endif
#ifdef glPointParameterf
glPointParameterfFunc _glPointParameterf = NULL;
#endif
#ifdef glPointParameterfv
glPointParameterfvFunc _glPointParameterfv = NULL;
#endif
#ifdef glPointParameteri
glPointParameteriFunc _glPointParameteri = NULL;
#endif
#ifdef glPointParameteriv
glPointParameterivFunc _glPointParameteriv = NULL;
#endif
#ifdef glFogCoordf
glFogCoordfFunc _glFogCoordf = NULL;
#endif
#ifdef glFogCoordfv
glFogCoordfvFunc _glFogCoordfv = NULL;
#endif
#ifdef glFogCoordd
glFogCoorddFunc _glFogCoordd = NULL;
#endif
#ifdef glFogCoorddv
glFogCoorddvFunc _glFogCoorddv = NULL;
#endif
#ifdef glFogCoordPointer
glFogCoordPointerFunc _glFogCoordPointer = NULL;
#endif
#ifdef glSecondaryColor3b
glSecondaryColor3bFunc _glSecondaryColor3b = NULL;
#endif
#ifdef glSecondaryColor3bv
glSecondaryColor3bvFunc _glSecondaryColor3bv = NULL;
#endif
#ifdef glSecondaryColor3d
glSecondaryColor3dFunc _glSecondaryColor3d = NULL;
#endif
#ifdef glSecondaryColor3dv
glSecondaryColor3dvFunc _glSecondaryColor3dv = NULL;
#endif
#ifdef glSecondaryColor3f
glSecondaryColor3fFunc _glSecondaryColor3f = NULL;
#endif
#ifdef glSecondaryColor3fv
glSecondaryColor3fvFunc _glSecondaryColor3fv = NULL;
#endif
#ifdef glSecondaryColor3i
glSecondaryColor3iFunc _glSecondaryColor3i = NULL;
#endif
#ifdef glSecondaryColor3iv
glSecondaryColor3ivFunc _glSecondaryColor3iv = NULL;
#endif
#ifdef glSecondaryColor3s
glSecondaryColor3sFunc _glSecondaryColor3s = NULL;
#endif
#ifdef glSecondaryColor3sv
glSecondaryColor3svFunc _glSecondaryColor3sv = NULL;
#endif
#ifdef glSecondaryColor3ub
glSecondaryColor3ubFunc _glSecondaryColor3ub = NULL;
#endif
#ifdef glSecondaryColor3ubv
glSecondaryColor3ubvFunc _glSecondaryColor3ubv = NULL;
#endif
#ifdef glSecondaryColor3ui
glSecondaryColor3uiFunc _glSecondaryColor3ui = NULL;
#endif
#ifdef glSecondaryColor3uiv
glSecondaryColor3uivFunc _glSecondaryColor3uiv = NULL;
#endif
#ifdef glSecondaryColor3us
glSecondaryColor3usFunc _glSecondaryColor3us = NULL;
#endif
#ifdef glSecondaryColor3usv
glSecondaryColor3usvFunc _glSecondaryColor3usv = NULL;
#endif
#ifdef glSecondaryColorPointer
glSecondaryColorPointerFunc _glSecondaryColorPointer = NULL;
#endif
#ifdef glWindowPos2d
glWindowPos2dFunc _glWindowPos2d = NULL;
#endif
#ifdef glWindowPos2dv
glWindowPos2dvFunc _glWindowPos2dv = NULL;
#endif
#ifdef glWindowPos2f
glWindowPos2fFunc _glWindowPos2f = NULL;
#endif
#ifdef glWindowPos2fv
glWindowPos2fvFunc _glWindowPos2fv = NULL;
#endif
#ifdef glWindowPos2i
glWindowPos2iFunc _glWindowPos2i = NULL;
#endif
#ifdef glWindowPos2iv
glWindowPos2ivFunc _glWindowPos2iv = NULL;
#endif
#ifdef glWindowPos2s
glWindowPos2sFunc _glWindowPos2s = NULL;
#endif
#ifdef glWindowPos2sv
glWindowPos2svFunc _glWindowPos2sv = NULL;
#endif
#ifdef glWindowPos3d
glWindowPos3dFunc _glWindowPos3d = NULL;
#endif
#ifdef glWindowPos3dv
glWindowPos3dvFunc _glWindowPos3dv = NULL;
#endif
#ifdef glWindowPos3f
glWindowPos3fFunc _glWindowPos3f = NULL;
#endif
#ifdef glWindowPos3fv
glWindowPos3fvFunc _glWindowPos3fv = NULL;
#endif
#ifdef glWindowPos3i
glWindowPos3iFunc _glWindowPos3i = NULL;
#endif
#ifdef glWindowPos3iv
glWindowPos3ivFunc _glWindowPos3iv = NULL;
#endif
#ifdef glWindowPos3s
glWindowPos3sFunc _glWindowPos3s = NULL;
#endif
#ifdef glWindowPos3sv
glWindowPos3svFunc _glWindowPos3sv = NULL;
#endif
#ifdef glGenQueries
glGenQueriesFunc _glGenQueries = NULL;
#endif
#ifdef glDeleteQueries
glDeleteQueriesFunc _glDeleteQueries = NULL;
#endif
#ifdef glIsQuery
glIsQueryFunc _glIsQuery = NULL;
#endif
#ifdef glBeginQuery
glBeginQueryFunc _glBeginQuery = NULL;
#endif
#ifdef glEndQuery
glEndQueryFunc _glEndQuery = NULL;
#endif
#ifdef glGetQueryiv
glGetQueryivFunc _glGetQueryiv = NULL;
#endif
#ifdef glGetQueryObjectiv
glGetQueryObjectivFunc _glGetQueryObjectiv = NULL;
#endif
#ifdef glGetQueryObjectuiv
glGetQueryObjectuivFunc _glGetQueryObjectuiv = NULL;
#endif
#ifdef glBindBuffer
glBindBufferFunc _glBindBuffer = NULL;
#endif
#ifdef glDeleteBuffers
glDeleteBuffersFunc _glDeleteBuffers = NULL;
#endif
#ifdef glGenBuffers
glGenBuffersFunc _glGenBuffers = NULL;
#endif
#ifdef glIsBuffer
glIsBufferFunc _glIsBuffer = NULL;
#endif
#ifdef glBufferData
glBufferDataFunc _glBufferData = NULL;
#endif
#ifdef glBufferSubData
glBufferSubDataFunc _glBufferSubData = NULL;
#endif
#ifdef glGetBufferSubData
glGetBufferSubDataFunc _glGetBufferSubData = NULL;
#endif
#ifdef glMapBuffer
glMapBufferFunc _glMapBuffer = NULL;
#endif
#ifdef glUnmapBuffer
glUnmapBufferFunc _glUnmapBuffer = NULL;
#endif
#ifdef glGetBufferParameteriv
glGetBufferParameterivFunc _glGetBufferParameteriv = NULL;
#endif
#ifdef glGetBufferPointerv
glGetBufferPointervFunc _glGetBufferPointerv = NULL;
#endif
#ifdef glBlendEquationSeparate
glBlendEquationSeparateFunc _glBlendEquationSeparate = NULL;
#endif
#ifdef glDrawBuffers
glDrawBuffersFunc _glDrawBuffers = NULL;
#endif
#ifdef glStencilOpSeparate
glStencilOpSeparateFunc _glStencilOpSeparate = NULL;
#endif
#ifdef glStencilFuncSeparate
glStencilFuncSeparateFunc _glStencilFuncSeparate = NULL;
#endif
#ifdef glStencilMaskSeparate
glStencilMaskSeparateFunc _glStencilMaskSeparate = NULL;
#endif
#ifdef glAttachShader
glAttachShaderFunc _glAttachShader = NULL;
#endif
#ifdef glBindAttribLocation
glBindAttribLocationFunc _glBindAttribLocation = NULL;
#endif
#ifdef glCompileShader
glCompileShaderFunc _glCompileShader = NULL;
#endif
#ifdef glCreateProgram
glCreateProgramFunc _glCreateProgram = NULL;
#endif
#ifdef glCreateShader
glCreateShaderFunc _glCreateShader = NULL;
#endif
#ifdef glDeleteProgram
glDeleteProgramFunc _glDeleteProgram = NULL;
#endif
#ifdef glDeleteShader
glDeleteShaderFunc _glDeleteShader = NULL;
#endif
#ifdef glDetachShader
glDetachShaderFunc _glDetachShader = NULL;
#endif
#ifdef glDisableVertexAttribArray
glDisableVertexAttribArrayFunc _glDisableVertexAttribArray = NULL;
#endif
#ifdef glEnableVertexAttribArray
glEnableVertexAttribArrayFunc _glEnableVertexAttribArray = NULL;
#endif
#ifdef glGetActiveAttrib
glGetActiveAttribFunc _glGetActiveAttrib = NULL;
#endif
#ifdef glGetActiveUniform
glGetActiveUniformFunc _glGetActiveUniform = NULL;
#endif
#ifdef glGetAttachedShaders
glGetAttachedShadersFunc _glGetAttachedShaders = NULL;
#endif
#ifdef glGetAttribLocation
glGetAttribLocationFunc _glGetAttribLocation = NULL;
#endif
#ifdef glGetProgramiv
glGetProgramivFunc _glGetProgramiv = NULL;
#endif
#ifdef glGetProgramInfoLog
glGetProgramInfoLogFunc _glGetProgramInfoLog = NULL;
#endif
#ifdef glGetShaderiv
glGetShaderivFunc _glGetShaderiv = NULL;
#endif
#ifdef glGetShaderInfoLog
glGetShaderInfoLogFunc _glGetShaderInfoLog = NULL;
#endif
#ifdef glGetShaderSource
glGetShaderSourceFunc _glGetShaderSource = NULL;
#endif
#ifdef glGetUniformLocation
glGetUniformLocationFunc _glGetUniformLocation = NULL;
#endif
#ifdef glGetUniformfv
glGetUniformfvFunc _glGetUniformfv = NULL;
#endif
#ifdef glGetUniformiv
glGetUniformivFunc _glGetUniformiv = NULL;
#endif
#ifdef glGetVertexAttribdv
glGetVertexAttribdvFunc _glGetVertexAttribdv = NULL;
#endif
#ifdef glGetVertexAttribfv
glGetVertexAttribfvFunc _glGetVertexAttribfv = NULL;
#endif
#ifdef glGetVertexAttribiv
glGetVertexAttribivFunc _glGetVertexAttribiv = NULL;
#endif
#ifdef glGetVertexAttribPointerv
glGetVertexAttribPointervFunc _glGetVertexAttribPointerv = NULL;
#endif
#ifdef glIsProgram
glIsProgramFunc _glIsProgram = NULL;
#endif
#ifdef glIsShader
glIsShaderFunc _glIsShader = NULL;
#endif
#ifdef glLinkProgram
glLinkProgramFunc _glLinkProgram = NULL;
#endif
#ifdef glShaderSource
glShaderSourceFunc _glShaderSource = NULL;
#endif
#ifdef glUseProgram
glUseProgramFunc _glUseProgram = NULL;
#endif
#ifdef glUniform1f
glUniform1fFunc _glUniform1f = NULL;
#endif
#ifdef glUniform2f
glUniform2fFunc _glUniform2f = NULL;
#endif
#ifdef glUniform3f
glUniform3fFunc _glUniform3f = NULL;
#endif
#ifdef glUniform4f
glUniform4fFunc _glUniform4f = NULL;
#endif
#ifdef glUniform1i
glUniform1iFunc _glUniform1i = NULL;
#endif
#ifdef glUniform2i
glUniform2iFunc _glUniform2i = NULL;
#endif
#ifdef glUniform3i
glUniform3iFunc _glUniform3i = NULL;
#endif
#ifdef glUniform4i
glUniform4iFunc _glUniform4i = NULL;
#endif
#ifdef glUniform1fv
glUniform1fvFunc _glUniform1fv = NULL;
#endif
#ifdef glUniform2fv
glUniform2fvFunc _glUniform2fv = NULL;
#endif
#ifdef glUniform3fv
glUniform3fvFunc _glUniform3fv = NULL;
#endif
#ifdef glUniform4fv
glUniform4fvFunc _glUniform4fv = NULL;
#endif
#ifdef glUniform1iv
glUniform1ivFunc _glUniform1iv = NULL;
#endif
#ifdef glUniform2iv
glUniform2ivFunc _glUniform2iv = NULL;
#endif
#ifdef glUniform3iv
glUniform3ivFunc _glUniform3iv = NULL;
#endif
#ifdef glUniform4iv
glUniform4ivFunc _glUniform4iv = NULL;
#endif
#ifdef glUniformMatrix2fv
glUniformMatrix2fvFunc _glUniformMatrix2fv = NULL;
#endif
#ifdef glUniformMatrix3fv
glUniformMatrix3fvFunc _glUniformMatrix3fv = NULL;
#endif
#ifdef glUniformMatrix4fv
glUniformMatrix4fvFunc _glUniformMatrix4fv = NULL;
#endif
#ifdef glValidateProgram
glValidateProgramFunc _glValidateProgram = NULL;
#endif
#ifdef glVertexAttrib1d
glVertexAttrib1dFunc _glVertexAttrib1d = NULL;
#endif
#ifdef glVertexAttrib1dv
glVertexAttrib1dvFunc _glVertexAttrib1dv = NULL;
#endif
#ifdef glVertexAttrib1f
glVertexAttrib1fFunc _glVertexAttrib1f = NULL;
#endif
#ifdef glVertexAttrib1fv
glVertexAttrib1fvFunc _glVertexAttrib1fv = NULL;
#endif
#ifdef glVertexAttrib1s
glVertexAttrib1sFunc _glVertexAttrib1s = NULL;
#endif
#ifdef glVertexAttrib1sv
glVertexAttrib1svFunc _glVertexAttrib1sv = NULL;
#endif
#ifdef glVertexAttrib2d
glVertexAttrib2dFunc _glVertexAttrib2d = NULL;
#endif
#ifdef glVertexAttrib2dv
glVertexAttrib2dvFunc _glVertexAttrib2dv = NULL;
#endif
#ifdef glVertexAttrib2f
glVertexAttrib2fFunc _glVertexAttrib2f = NULL;
#endif
#ifdef glVertexAttrib2fv
glVertexAttrib2fvFunc _glVertexAttrib2fv = NULL;
#endif
#ifdef glVertexAttrib2s
glVertexAttrib2sFunc _glVertexAttrib2s = NULL;
#endif
#ifdef glVertexAttrib2sv
glVertexAttrib2svFunc _glVertexAttrib2sv = NULL;
#endif
#ifdef glVertexAttrib3d
glVertexAttrib3dFunc _glVertexAttrib3d = NULL;
#endif
#ifdef glVertexAttrib3dv
glVertexAttrib3dvFunc _glVertexAttrib3dv = NULL;
#endif
#ifdef glVertexAttrib3f
glVertexAttrib3fFunc _glVertexAttrib3f = NULL;
#endif
#ifdef glVertexAttrib3fv
glVertexAttrib3fvFunc _glVertexAttrib3fv = NULL;
#endif
#ifdef glVertexAttrib3s
glVertexAttrib3sFunc _glVertexAttrib3s = NULL;
#endif
#ifdef glVertexAttrib3sv
glVertexAttrib3svFunc _glVertexAttrib3sv = NULL;
#endif
#ifdef glVertexAttrib4Nbv
glVertexAttrib4NbvFunc _glVertexAttrib4Nbv = NULL;
#endif
#ifdef glVertexAttrib4Niv
glVertexAttrib4NivFunc _glVertexAttrib4Niv = NULL;
#endif
#ifdef glVertexAttrib4Nsv
glVertexAttrib4NsvFunc _glVertexAttrib4Nsv = NULL;
#endif
#ifdef glVertexAttrib4Nub
glVertexAttrib4NubFunc _glVertexAttrib4Nub = NULL;
#endif
#ifdef glVertexAttrib4Nubv
glVertexAttrib4NubvFunc _glVertexAttrib4Nubv = NULL;
#endif
#ifdef glVertexAttrib4Nuiv
glVertexAttrib4NuivFunc _glVertexAttrib4Nuiv = NULL;
#endif
#ifdef glVertexAttrib4Nusv
glVertexAttrib4NusvFunc _glVertexAttrib4Nusv = NULL;
#endif
#ifdef glVertexAttrib4bv
glVertexAttrib4bvFunc _glVertexAttrib4bv = NULL;
#endif
#ifdef glVertexAttrib4d
glVertexAttrib4dFunc _glVertexAttrib4d = NULL;
#endif
#ifdef glVertexAttrib4dv
glVertexAttrib4dvFunc _glVertexAttrib4dv = NULL;
#endif
#ifdef glVertexAttrib4f
glVertexAttrib4fFunc _glVertexAttrib4f = NULL;
#endif
#ifdef glVertexAttrib4fv
glVertexAttrib4fvFunc _glVertexAttrib4fv = NULL;
#endif
#ifdef glVertexAttrib4iv
glVertexAttrib4ivFunc _glVertexAttrib4iv = NULL;
#endif
#ifdef glVertexAttrib4s
glVertexAttrib4sFunc _glVertexAttrib4s = NULL;
#endif
#ifdef glVertexAttrib4sv
glVertexAttrib4svFunc _glVertexAttrib4sv = NULL;
#endif
#ifdef glVertexAttrib4ubv
glVertexAttrib4ubvFunc _glVertexAttrib4ubv = NULL;
#endif
#ifdef glVertexAttrib4uiv
glVertexAttrib4uivFunc _glVertexAttrib4uiv = NULL;
#endif
#ifdef glVertexAttrib4usv
glVertexAttrib4usvFunc _glVertexAttrib4usv = NULL;
#endif
#ifdef glVertexAttribPointer
glVertexAttribPointerFunc _glVertexAttribPointer = NULL;
#endif
#ifdef glUniformMatrix2x3fv
glUniformMatrix2x3fvFunc _glUniformMatrix2x3fv = NULL;
#endif
#ifdef glUniformMatrix3x2fv
glUniformMatrix3x2fvFunc _glUniformMatrix3x2fv = NULL;
#endif
#ifdef glUniformMatrix2x4fv
glUniformMatrix2x4fvFunc _glUniformMatrix2x4fv = NULL;
#endif
#ifdef glUniformMatrix4x2fv
glUniformMatrix4x2fvFunc _glUniformMatrix4x2fv = NULL;
#endif
#ifdef glUniformMatrix3x4fv
glUniformMatrix3x4fvFunc _glUniformMatrix3x4fv = NULL;
#endif
#ifdef glUniformMatrix4x3fv
glUniformMatrix4x3fvFunc _glUniformMatrix4x3fv = NULL;
#endif
#ifdef glColorMaski
glColorMaskiFunc _glColorMaski = NULL;
#endif
#ifdef glGetBooleani_v
glGetBooleani_vFunc _glGetBooleani_v = NULL;
#endif
#ifdef glGetIntegeri_v
glGetIntegeri_vFunc _glGetIntegeri_v = NULL;
#endif
#ifdef glEnablei
glEnableiFunc _glEnablei = NULL;
#endif
#ifdef glDisablei
glDisableiFunc _glDisablei = NULL;
#endif
#ifdef glIsEnabledi
glIsEnablediFunc _glIsEnabledi = NULL;
#endif
#ifdef glBeginTransformFeedback
glBeginTransformFeedbackFunc _glBeginTransformFeedback = NULL;
#endif
#ifdef glEndTransformFeedback
glEndTransformFeedbackFunc _glEndTransformFeedback = NULL;
#endif
#ifdef glBindBufferRange
glBindBufferRangeFunc _glBindBufferRange = NULL;
#endif
#ifdef glBindBufferBase
glBindBufferBaseFunc _glBindBufferBase = NULL;
#endif
#ifdef glTransformFeedbackVaryings
glTransformFeedbackVaryingsFunc _glTransformFeedbackVaryings = NULL;
#endif
#ifdef glGetTransformFeedbackVarying
glGetTransformFeedbackVaryingFunc _glGetTransformFeedbackVarying = NULL;
#endif
#ifdef glClampColor
glClampColorFunc _glClampColor = NULL;
#endif
#ifdef glBeginConditionalRender
glBeginConditionalRenderFunc _glBeginConditionalRender = NULL;
#endif
#ifdef glEndConditionalRender
glEndConditionalRenderFunc _glEndConditionalRender = NULL;
#endif
#ifdef glVertexAttribIPointer
glVertexAttribIPointerFunc _glVertexAttribIPointer = NULL;
#endif
#ifdef glGetVertexAttribIiv
glGetVertexAttribIivFunc _glGetVertexAttribIiv = NULL;
#endif
#ifdef glGetVertexAttribIuiv
glGetVertexAttribIuivFunc _glGetVertexAttribIuiv = NULL;
#endif
#ifdef glVertexAttribI1i
glVertexAttribI1iFunc _glVertexAttribI1i = NULL;
#endif
#ifdef glVertexAttribI2i
glVertexAttribI2iFunc _glVertexAttribI2i = NULL;
#endif
#ifdef glVertexAttribI3i
glVertexAttribI3iFunc _glVertexAttribI3i = NULL;
#endif
#ifdef glVertexAttribI4i
glVertexAttribI4iFunc _glVertexAttribI4i = NULL;
#endif
#ifdef glVertexAttribI1ui
glVertexAttribI1uiFunc _glVertexAttribI1ui = NULL;
#endif
#ifdef glVertexAttribI2ui
glVertexAttribI2uiFunc _glVertexAttribI2ui = NULL;
#endif
#ifdef glVertexAttribI3ui
glVertexAttribI3uiFunc _glVertexAttribI3ui = NULL;
#endif
#ifdef glVertexAttribI4ui
glVertexAttribI4uiFunc _glVertexAttribI4ui = NULL;
#endif
#ifdef glVertexAttribI1iv
glVertexAttribI1ivFunc _glVertexAttribI1iv = NULL;
#endif
#ifdef glVertexAttribI2iv
glVertexAttribI2ivFunc _glVertexAttribI2iv = NULL;
#endif
#ifdef glVertexAttribI3iv
glVertexAttribI3ivFunc _glVertexAttribI3iv = NULL;
#endif
#ifdef glVertexAttribI4iv
glVertexAttribI4ivFunc _glVertexAttribI4iv = NULL;
#endif
#ifdef glVertexAttribI1uiv
glVertexAttribI1uivFunc _glVertexAttribI1uiv = NULL;
#endif
#ifdef glVertexAttribI2uiv
glVertexAttribI2uivFunc _glVertexAttribI2uiv = NULL;
#endif
#ifdef glVertexAttribI3uiv
glVertexAttribI3uivFunc _glVertexAttribI3uiv = NULL;
#endif
#ifdef glVertexAttribI4uiv
glVertexAttribI4uivFunc _glVertexAttribI4uiv = NULL;
#endif
#ifdef glVertexAttribI4bv
glVertexAttribI4bvFunc _glVertexAttribI4bv = NULL;
#endif
#ifdef glVertexAttribI4sv
glVertexAttribI4svFunc _glVertexAttribI4sv = NULL;
#endif
#ifdef glVertexAttribI4ubv
glVertexAttribI4ubvFunc _glVertexAttribI4ubv = NULL;
#endif
#ifdef glVertexAttribI4usv
glVertexAttribI4usvFunc _glVertexAttribI4usv = NULL;
#endif
#ifdef glGetUniformuiv
glGetUniformuivFunc _glGetUniformuiv = NULL;
#endif
#ifdef glBindFragDataLocation
glBindFragDataLocationFunc _glBindFragDataLocation = NULL;
#endif
#ifdef glGetFragDataLocation
glGetFragDataLocationFunc _glGetFragDataLocation = NULL;
#endif
#ifdef glUniform1ui
glUniform1uiFunc _glUniform1ui = NULL;
#endif
#ifdef glUniform2ui
glUniform2uiFunc _glUniform2ui = NULL;
#endif
#ifdef glUniform3ui
glUniform3uiFunc _glUniform3ui = NULL;
#endif
#ifdef glUniform4ui
glUniform4uiFunc _glUniform4ui = NULL;
#endif
#ifdef glUniform1uiv
glUniform1uivFunc _glUniform1uiv = NULL;
#endif
#ifdef glUniform2uiv
glUniform2uivFunc _glUniform2uiv = NULL;
#endif
#ifdef glUniform3uiv
glUniform3uivFunc _glUniform3uiv = NULL;
#endif
#ifdef glUniform4uiv
glUniform4uivFunc _glUniform4uiv = NULL;
#endif
#ifdef glTexParameterIiv
glTexParameterIivFunc _glTexParameterIiv = NULL;
#endif
#ifdef glTexParameterIuiv
glTexParameterIuivFunc _glTexParameterIuiv = NULL;
#endif
#ifdef glGetTexParameterIiv
glGetTexParameterIivFunc _glGetTexParameterIiv = NULL;
#endif
#ifdef glGetTexParameterIuiv
glGetTexParameterIuivFunc _glGetTexParameterIuiv = NULL;
#endif
#ifdef glClearBufferiv
glClearBufferivFunc _glClearBufferiv = NULL;
#endif
#ifdef glClearBufferuiv
glClearBufferuivFunc _glClearBufferuiv = NULL;
#endif
#ifdef glClearBufferfv
glClearBufferfvFunc _glClearBufferfv = NULL;
#endif
#ifdef glClearBufferfi
glClearBufferfiFunc _glClearBufferfi = NULL;
#endif
#ifdef glGetStringi
glGetStringiFunc _glGetStringi = NULL;
#endif
#ifdef glDrawArraysInstanced
glDrawArraysInstancedFunc _glDrawArraysInstanced = NULL;
#endif
#ifdef glDrawElementsInstanced
glDrawElementsInstancedFunc _glDrawElementsInstanced = NULL;
#endif
#ifdef glTexBuffer
glTexBufferFunc _glTexBuffer = NULL;
#endif
#ifdef glPrimitiveRestartIndex
glPrimitiveRestartIndexFunc _glPrimitiveRestartIndex = NULL;
#endif
#ifdef glGetInteger64i_v
glGetInteger64i_vFunc _glGetInteger64i_v = NULL;
#endif
#ifdef glGetBufferParameteri64v
glGetBufferParameteri64vFunc _glGetBufferParameteri64v = NULL;
#endif
#ifdef glFramebufferTexture
glFramebufferTextureFunc _glFramebufferTexture = NULL;
#endif
#ifdef glVertexAttribDivisor
glVertexAttribDivisorFunc _glVertexAttribDivisor = NULL;
#endif
#ifdef glMinSampleShading
glMinSampleShadingFunc _glMinSampleShading = NULL;
#endif
#ifdef glBlendEquationi
glBlendEquationiFunc _glBlendEquationi = NULL;
#endif
#ifdef glBlendEquationSeparatei
glBlendEquationSeparateiFunc _glBlendEquationSeparatei = NULL;
#endif
#ifdef glBlendFunci
glBlendFunciFunc _glBlendFunci = NULL;
#endif
#ifdef glBlendFuncSeparatei
glBlendFuncSeparateiFunc _glBlendFuncSeparatei = NULL;
#endif
#ifdef glActiveTextureARB
glActiveTextureARBFunc _glActiveTextureARB = NULL;
#endif
#ifdef glClientActiveTextureARB
glClientActiveTextureARBFunc _glClientActiveTextureARB = NULL;
#endif
#ifdef glMultiTexCoord1dARB
glMultiTexCoord1dARBFunc _glMultiTexCoord1dARB = NULL;
#endif
#ifdef glMultiTexCoord1dvARB
glMultiTexCoord1dvARBFunc _glMultiTexCoord1dvARB = NULL;
#endif
#ifdef glMultiTexCoord1fARB
glMultiTexCoord1fARBFunc _glMultiTexCoord1fARB = NULL;
#endif
#ifdef glMultiTexCoord1fvARB
glMultiTexCoord1fvARBFunc _glMultiTexCoord1fvARB = NULL;
#endif
#ifdef glMultiTexCoord1iARB
glMultiTexCoord1iARBFunc _glMultiTexCoord1iARB = NULL;
#endif
#ifdef glMultiTexCoord1ivARB
glMultiTexCoord1ivARBFunc _glMultiTexCoord1ivARB = NULL;
#endif
#ifdef glMultiTexCoord1sARB
glMultiTexCoord1sARBFunc _glMultiTexCoord1sARB = NULL;
#endif
#ifdef glMultiTexCoord1svARB
glMultiTexCoord1svARBFunc _glMultiTexCoord1svARB = NULL;
#endif
#ifdef glMultiTexCoord2dARB
glMultiTexCoord2dARBFunc _glMultiTexCoord2dARB = NULL;
#endif
#ifdef glMultiTexCoord2dvARB
glMultiTexCoord2dvARBFunc _glMultiTexCoord2dvARB = NULL;
#endif
#ifdef glMultiTexCoord2fARB
glMultiTexCoord2fARBFunc _glMultiTexCoord2fARB = NULL;
#endif
#ifdef glMultiTexCoord2fvARB
glMultiTexCoord2fvARBFunc _glMultiTexCoord2fvARB = NULL;
#endif
#ifdef glMultiTexCoord2iARB
glMultiTexCoord2iARBFunc _glMultiTexCoord2iARB = NULL;
#endif
#ifdef glMultiTexCoord2ivARB
glMultiTexCoord2ivARBFunc _glMultiTexCoord2ivARB = NULL;
#endif
#ifdef glMultiTexCoord2sARB
glMultiTexCoord2sARBFunc _glMultiTexCoord2sARB = NULL;
#endif
#ifdef glMultiTexCoord2svARB
glMultiTexCoord2svARBFunc _glMultiTexCoord2svARB = NULL;
#endif
#ifdef glMultiTexCoord3dARB
glMultiTexCoord3dARBFunc _glMultiTexCoord3dARB = NULL;
#endif
#ifdef glMultiTexCoord3dvARB
glMultiTexCoord3dvARBFunc _glMultiTexCoord3dvARB = NULL;
#endif
#ifdef glMultiTexCoord3fARB
glMultiTexCoord3fARBFunc _glMultiTexCoord3fARB = NULL;
#endif
#ifdef glMultiTexCoord3fvARB
glMultiTexCoord3fvARBFunc _glMultiTexCoord3fvARB = NULL;
#endif
#ifdef glMultiTexCoord3iARB
glMultiTexCoord3iARBFunc _glMultiTexCoord3iARB = NULL;
#endif
#ifdef glMultiTexCoord3ivARB
glMultiTexCoord3ivARBFunc _glMultiTexCoord3ivARB = NULL;
#endif
#ifdef glMultiTexCoord3sARB
glMultiTexCoord3sARBFunc _glMultiTexCoord3sARB = NULL;
#endif
#ifdef glMultiTexCoord3svARB
glMultiTexCoord3svARBFunc _glMultiTexCoord3svARB = NULL;
#endif
#ifdef glMultiTexCoord4dARB
glMultiTexCoord4dARBFunc _glMultiTexCoord4dARB = NULL;
#endif
#ifdef glMultiTexCoord4dvARB
glMultiTexCoord4dvARBFunc _glMultiTexCoord4dvARB = NULL;
#endif
#ifdef glMultiTexCoord4fARB
glMultiTexCoord4fARBFunc _glMultiTexCoord4fARB = NULL;
#endif
#ifdef glMultiTexCoord4fvARB
glMultiTexCoord4fvARBFunc _glMultiTexCoord4fvARB = NULL;
#endif
#ifdef glMultiTexCoord4iARB
glMultiTexCoord4iARBFunc _glMultiTexCoord4iARB = NULL;
#endif
#ifdef glMultiTexCoord4ivARB
glMultiTexCoord4ivARBFunc _glMultiTexCoord4ivARB = NULL;
#endif
#ifdef glMultiTexCoord4sARB
glMultiTexCoord4sARBFunc _glMultiTexCoord4sARB = NULL;
#endif
#ifdef glMultiTexCoord4svARB
glMultiTexCoord4svARBFunc _glMultiTexCoord4svARB = NULL;
#endif
#ifdef glLoadTransposeMatrixfARB
glLoadTransposeMatrixfARBFunc _glLoadTransposeMatrixfARB = NULL;
#endif
#ifdef glLoadTransposeMatrixdARB
glLoadTransposeMatrixdARBFunc _glLoadTransposeMatrixdARB = NULL;
#endif
#ifdef glMultTransposeMatrixfARB
glMultTransposeMatrixfARBFunc _glMultTransposeMatrixfARB = NULL;
#endif
#ifdef glMultTransposeMatrixdARB
glMultTransposeMatrixdARBFunc _glMultTransposeMatrixdARB = NULL;
#endif
#ifdef glSampleCoverageARB
glSampleCoverageARBFunc _glSampleCoverageARB = NULL;
#endif
#ifdef glCompressedTexImage3DARB
glCompressedTexImage3DARBFunc _glCompressedTexImage3DARB = NULL;
#endif
#ifdef glCompressedTexImage2DARB
glCompressedTexImage2DARBFunc _glCompressedTexImage2DARB = NULL;
#endif
#ifdef glCompressedTexImage1DARB
glCompressedTexImage1DARBFunc _glCompressedTexImage1DARB = NULL;
#endif
#ifdef glCompressedTexSubImage3DARB
glCompressedTexSubImage3DARBFunc _glCompressedTexSubImage3DARB = NULL;
#endif
#ifdef glCompressedTexSubImage2DARB
glCompressedTexSubImage2DARBFunc _glCompressedTexSubImage2DARB = NULL;
#endif
#ifdef glCompressedTexSubImage1DARB
glCompressedTexSubImage1DARBFunc _glCompressedTexSubImage1DARB = NULL;
#endif
#ifdef glGetCompressedTexImageARB
glGetCompressedTexImageARBFunc _glGetCompressedTexImageARB = NULL;
#endif
#ifdef glPointParameterfARB
glPointParameterfARBFunc _glPointParameterfARB = NULL;
#endif
#ifdef glPointParameterfvARB
glPointParameterfvARBFunc _glPointParameterfvARB = NULL;
#endif
#ifdef glWeightbvARB
glWeightbvARBFunc _glWeightbvARB = NULL;
#endif
#ifdef glWeightsvARB
glWeightsvARBFunc _glWeightsvARB = NULL;
#endif
#ifdef glWeightivARB
glWeightivARBFunc _glWeightivARB = NULL;
#endif
#ifdef glWeightfvARB
glWeightfvARBFunc _glWeightfvARB = NULL;
#endif
#ifdef glWeightdvARB
glWeightdvARBFunc _glWeightdvARB = NULL;
#endif
#ifdef glWeightubvARB
glWeightubvARBFunc _glWeightubvARB = NULL;
#endif
#ifdef glWeightusvARB
glWeightusvARBFunc _glWeightusvARB = NULL;
#endif
#ifdef glWeightuivARB
glWeightuivARBFunc _glWeightuivARB = NULL;
#endif
#ifdef glWeightPointerARB
glWeightPointerARBFunc _glWeightPointerARB = NULL;
#endif
#ifdef glVertexBlendARB
glVertexBlendARBFunc _glVertexBlendARB = NULL;
#endif
#ifdef glCurrentPaletteMatrixARB
glCurrentPaletteMatrixARBFunc _glCurrentPaletteMatrixARB = NULL;
#endif
#ifdef glMatrixIndexubvARB
glMatrixIndexubvARBFunc _glMatrixIndexubvARB = NULL;
#endif
#ifdef glMatrixIndexusvARB
glMatrixIndexusvARBFunc _glMatrixIndexusvARB = NULL;
#endif
#ifdef glMatrixIndexuivARB
glMatrixIndexuivARBFunc _glMatrixIndexuivARB = NULL;
#endif
#ifdef glMatrixIndexPointerARB
glMatrixIndexPointerARBFunc _glMatrixIndexPointerARB = NULL;
#endif
#ifdef glWindowPos2dARB
glWindowPos2dARBFunc _glWindowPos2dARB = NULL;
#endif
#ifdef glWindowPos2dvARB
glWindowPos2dvARBFunc _glWindowPos2dvARB = NULL;
#endif
#ifdef glWindowPos2fARB
glWindowPos2fARBFunc _glWindowPos2fARB = NULL;
#endif
#ifdef glWindowPos2fvARB
glWindowPos2fvARBFunc _glWindowPos2fvARB = NULL;
#endif
#ifdef glWindowPos2iARB
glWindowPos2iARBFunc _glWindowPos2iARB = NULL;
#endif
#ifdef glWindowPos2ivARB
glWindowPos2ivARBFunc _glWindowPos2ivARB = NULL;
#endif
#ifdef glWindowPos2sARB
glWindowPos2sARBFunc _glWindowPos2sARB = NULL;
#endif
#ifdef glWindowPos2svARB
glWindowPos2svARBFunc _glWindowPos2svARB = NULL;
#endif
#ifdef glWindowPos3dARB
glWindowPos3dARBFunc _glWindowPos3dARB = NULL;
#endif
#ifdef glWindowPos3dvARB
glWindowPos3dvARBFunc _glWindowPos3dvARB = NULL;
#endif
#ifdef glWindowPos3fARB
glWindowPos3fARBFunc _glWindowPos3fARB = NULL;
#endif
#ifdef glWindowPos3fvARB
glWindowPos3fvARBFunc _glWindowPos3fvARB = NULL;
#endif
#ifdef glWindowPos3iARB
glWindowPos3iARBFunc _glWindowPos3iARB = NULL;
#endif
#ifdef glWindowPos3ivARB
glWindowPos3ivARBFunc _glWindowPos3ivARB = NULL;
#endif
#ifdef glWindowPos3sARB
glWindowPos3sARBFunc _glWindowPos3sARB = NULL;
#endif
#ifdef glWindowPos3svARB
glWindowPos3svARBFunc _glWindowPos3svARB = NULL;
#endif
#ifdef glVertexAttrib1dARB
glVertexAttrib1dARBFunc _glVertexAttrib1dARB = NULL;
#endif
#ifdef glVertexAttrib1dvARB
glVertexAttrib1dvARBFunc _glVertexAttrib1dvARB = NULL;
#endif
#ifdef glVertexAttrib1fARB
glVertexAttrib1fARBFunc _glVertexAttrib1fARB = NULL;
#endif
#ifdef glVertexAttrib1fvARB
glVertexAttrib1fvARBFunc _glVertexAttrib1fvARB = NULL;
#endif
#ifdef glVertexAttrib1sARB
glVertexAttrib1sARBFunc _glVertexAttrib1sARB = NULL;
#endif
#ifdef glVertexAttrib1svARB
glVertexAttrib1svARBFunc _glVertexAttrib1svARB = NULL;
#endif
#ifdef glVertexAttrib2dARB
glVertexAttrib2dARBFunc _glVertexAttrib2dARB = NULL;
#endif
#ifdef glVertexAttrib2dvARB
glVertexAttrib2dvARBFunc _glVertexAttrib2dvARB = NULL;
#endif
#ifdef glVertexAttrib2fARB
glVertexAttrib2fARBFunc _glVertexAttrib2fARB = NULL;
#endif
#ifdef glVertexAttrib2fvARB
glVertexAttrib2fvARBFunc _glVertexAttrib2fvARB = NULL;
#endif
#ifdef glVertexAttrib2sARB
glVertexAttrib2sARBFunc _glVertexAttrib2sARB = NULL;
#endif
#ifdef glVertexAttrib2svARB
glVertexAttrib2svARBFunc _glVertexAttrib2svARB = NULL;
#endif
#ifdef glVertexAttrib3dARB
glVertexAttrib3dARBFunc _glVertexAttrib3dARB = NULL;
#endif
#ifdef glVertexAttrib3dvARB
glVertexAttrib3dvARBFunc _glVertexAttrib3dvARB = NULL;
#endif
#ifdef glVertexAttrib3fARB
glVertexAttrib3fARBFunc _glVertexAttrib3fARB = NULL;
#endif
#ifdef glVertexAttrib3fvARB
glVertexAttrib3fvARBFunc _glVertexAttrib3fvARB = NULL;
#endif
#ifdef glVertexAttrib3sARB
glVertexAttrib3sARBFunc _glVertexAttrib3sARB = NULL;
#endif
#ifdef glVertexAttrib3svARB
glVertexAttrib3svARBFunc _glVertexAttrib3svARB = NULL;
#endif
#ifdef glVertexAttrib4NbvARB
glVertexAttrib4NbvARBFunc _glVertexAttrib4NbvARB = NULL;
#endif
#ifdef glVertexAttrib4NivARB
glVertexAttrib4NivARBFunc _glVertexAttrib4NivARB = NULL;
#endif
#ifdef glVertexAttrib4NsvARB
glVertexAttrib4NsvARBFunc _glVertexAttrib4NsvARB = NULL;
#endif
#ifdef glVertexAttrib4NubARB
glVertexAttrib4NubARBFunc _glVertexAttrib4NubARB = NULL;
#endif
#ifdef glVertexAttrib4NubvARB
glVertexAttrib4NubvARBFunc _glVertexAttrib4NubvARB = NULL;
#endif
#ifdef glVertexAttrib4NuivARB
glVertexAttrib4NuivARBFunc _glVertexAttrib4NuivARB = NULL;
#endif
#ifdef glVertexAttrib4NusvARB
glVertexAttrib4NusvARBFunc _glVertexAttrib4NusvARB = NULL;
#endif
#ifdef glVertexAttrib4bvARB
glVertexAttrib4bvARBFunc _glVertexAttrib4bvARB = NULL;
#endif
#ifdef glVertexAttrib4dARB
glVertexAttrib4dARBFunc _glVertexAttrib4dARB = NULL;
#endif
#ifdef glVertexAttrib4dvARB
glVertexAttrib4dvARBFunc _glVertexAttrib4dvARB = NULL;
#endif
#ifdef glVertexAttrib4fARB
glVertexAttrib4fARBFunc _glVertexAttrib4fARB = NULL;
#endif
#ifdef glVertexAttrib4fvARB
glVertexAttrib4fvARBFunc _glVertexAttrib4fvARB = NULL;
#endif
#ifdef glVertexAttrib4ivARB
glVertexAttrib4ivARBFunc _glVertexAttrib4ivARB = NULL;
#endif
#ifdef glVertexAttrib4sARB
glVertexAttrib4sARBFunc _glVertexAttrib4sARB = NULL;
#endif
#ifdef glVertexAttrib4svARB
glVertexAttrib4svARBFunc _glVertexAttrib4svARB = NULL;
#endif
#ifdef glVertexAttrib4ubvARB
glVertexAttrib4ubvARBFunc _glVertexAttrib4ubvARB = NULL;
#endif
#ifdef glVertexAttrib4uivARB
glVertexAttrib4uivARBFunc _glVertexAttrib4uivARB = NULL;
#endif
#ifdef glVertexAttrib4usvARB
glVertexAttrib4usvARBFunc _glVertexAttrib4usvARB = NULL;
#endif
#ifdef glVertexAttribPointerARB
glVertexAttribPointerARBFunc _glVertexAttribPointerARB = NULL;
#endif
#ifdef glEnableVertexAttribArrayARB
glEnableVertexAttribArrayARBFunc _glEnableVertexAttribArrayARB = NULL;
#endif
#ifdef glDisableVertexAttribArrayARB
glDisableVertexAttribArrayARBFunc _glDisableVertexAttribArrayARB = NULL;
#endif
#ifdef glProgramStringARB
glProgramStringARBFunc _glProgramStringARB = NULL;
#endif
#ifdef glBindProgramARB
glBindProgramARBFunc _glBindProgramARB = NULL;
#endif
#ifdef glDeleteProgramsARB
glDeleteProgramsARBFunc _glDeleteProgramsARB = NULL;
#endif
#ifdef glGenProgramsARB
glGenProgramsARBFunc _glGenProgramsARB = NULL;
#endif
#ifdef glProgramEnvParameter4dARB
glProgramEnvParameter4dARBFunc _glProgramEnvParameter4dARB = NULL;
#endif
#ifdef glProgramEnvParameter4dvARB
glProgramEnvParameter4dvARBFunc _glProgramEnvParameter4dvARB = NULL;
#endif
#ifdef glProgramEnvParameter4fARB
glProgramEnvParameter4fARBFunc _glProgramEnvParameter4fARB = NULL;
#endif
#ifdef glProgramEnvParameter4fvARB
glProgramEnvParameter4fvARBFunc _glProgramEnvParameter4fvARB = NULL;
#endif
#ifdef glProgramLocalParameter4dARB
glProgramLocalParameter4dARBFunc _glProgramLocalParameter4dARB = NULL;
#endif
#ifdef glProgramLocalParameter4dvARB
glProgramLocalParameter4dvARBFunc _glProgramLocalParameter4dvARB = NULL;
#endif
#ifdef glProgramLocalParameter4fARB
glProgramLocalParameter4fARBFunc _glProgramLocalParameter4fARB = NULL;
#endif
#ifdef glProgramLocalParameter4fvARB
glProgramLocalParameter4fvARBFunc _glProgramLocalParameter4fvARB = NULL;
#endif
#ifdef glGetProgramEnvParameterdvARB
glGetProgramEnvParameterdvARBFunc _glGetProgramEnvParameterdvARB = NULL;
#endif
#ifdef glGetProgramEnvParameterfvARB
glGetProgramEnvParameterfvARBFunc _glGetProgramEnvParameterfvARB = NULL;
#endif
#ifdef glGetProgramLocalParameterdvARB
glGetProgramLocalParameterdvARBFunc _glGetProgramLocalParameterdvARB = NULL;
#endif
#ifdef glGetProgramLocalParameterfvARB
glGetProgramLocalParameterfvARBFunc _glGetProgramLocalParameterfvARB = NULL;
#endif
#ifdef glGetProgramivARB
glGetProgramivARBFunc _glGetProgramivARB = NULL;
#endif
#ifdef glGetProgramStringARB
glGetProgramStringARBFunc _glGetProgramStringARB = NULL;
#endif
#ifdef glGetVertexAttribdvARB
glGetVertexAttribdvARBFunc _glGetVertexAttribdvARB = NULL;
#endif
#ifdef glGetVertexAttribfvARB
glGetVertexAttribfvARBFunc _glGetVertexAttribfvARB = NULL;
#endif
#ifdef glGetVertexAttribivARB
glGetVertexAttribivARBFunc _glGetVertexAttribivARB = NULL;
#endif
#ifdef glGetVertexAttribPointervARB
glGetVertexAttribPointervARBFunc _glGetVertexAttribPointervARB = NULL;
#endif
#ifdef glIsProgramARB
glIsProgramARBFunc _glIsProgramARB = NULL;
#endif
#ifdef glBindBufferARB
glBindBufferARBFunc _glBindBufferARB = NULL;
#endif
#ifdef glDeleteBuffersARB
glDeleteBuffersARBFunc _glDeleteBuffersARB = NULL;
#endif
#ifdef glGenBuffersARB
glGenBuffersARBFunc _glGenBuffersARB = NULL;
#endif
#ifdef glIsBufferARB
glIsBufferARBFunc _glIsBufferARB = NULL;
#endif
#ifdef glBufferDataARB
glBufferDataARBFunc _glBufferDataARB = NULL;
#endif
#ifdef glBufferSubDataARB
glBufferSubDataARBFunc _glBufferSubDataARB = NULL;
#endif
#ifdef glGetBufferSubDataARB
glGetBufferSubDataARBFunc _glGetBufferSubDataARB = NULL;
#endif
#ifdef glMapBufferARB
glMapBufferARBFunc _glMapBufferARB = NULL;
#endif
#ifdef glUnmapBufferARB
glUnmapBufferARBFunc _glUnmapBufferARB = NULL;
#endif
#ifdef glGetBufferParameterivARB
glGetBufferParameterivARBFunc _glGetBufferParameterivARB = NULL;
#endif
#ifdef glGetBufferPointervARB
glGetBufferPointervARBFunc _glGetBufferPointervARB = NULL;
#endif
#ifdef glGenQueriesARB
glGenQueriesARBFunc _glGenQueriesARB = NULL;
#endif
#ifdef glDeleteQueriesARB
glDeleteQueriesARBFunc _glDeleteQueriesARB = NULL;
#endif
#ifdef glIsQueryARB
glIsQueryARBFunc _glIsQueryARB = NULL;
#endif
#ifdef glBeginQueryARB
glBeginQueryARBFunc _glBeginQueryARB = NULL;
#endif
#ifdef glEndQueryARB
glEndQueryARBFunc _glEndQueryARB = NULL;
#endif
#ifdef glGetQueryivARB
glGetQueryivARBFunc _glGetQueryivARB = NULL;
#endif
#ifdef glGetQueryObjectivARB
glGetQueryObjectivARBFunc _glGetQueryObjectivARB = NULL;
#endif
#ifdef glGetQueryObjectuivARB
glGetQueryObjectuivARBFunc _glGetQueryObjectuivARB = NULL;
#endif
#ifdef glDeleteObjectARB
glDeleteObjectARBFunc _glDeleteObjectARB = NULL;
#endif
#ifdef glGetHandleARB
glGetHandleARBFunc _glGetHandleARB = NULL;
#endif
#ifdef glDetachObjectARB
glDetachObjectARBFunc _glDetachObjectARB = NULL;
#endif
#ifdef glCreateShaderObjectARB
glCreateShaderObjectARBFunc _glCreateShaderObjectARB = NULL;
#endif
#ifdef glShaderSourceARB
glShaderSourceARBFunc _glShaderSourceARB = NULL;
#endif
#ifdef glCompileShaderARB
glCompileShaderARBFunc _glCompileShaderARB = NULL;
#endif
#ifdef glCreateProgramObjectARB
glCreateProgramObjectARBFunc _glCreateProgramObjectARB = NULL;
#endif
#ifdef glAttachObjectARB
glAttachObjectARBFunc _glAttachObjectARB = NULL;
#endif
#ifdef glLinkProgramARB
glLinkProgramARBFunc _glLinkProgramARB = NULL;
#endif
#ifdef glUseProgramObjectARB
glUseProgramObjectARBFunc _glUseProgramObjectARB = NULL;
#endif
#ifdef glValidateProgramARB
glValidateProgramARBFunc _glValidateProgramARB = NULL;
#endif
#ifdef glUniform1fARB
glUniform1fARBFunc _glUniform1fARB = NULL;
#endif
#ifdef glUniform2fARB
glUniform2fARBFunc _glUniform2fARB = NULL;
#endif
#ifdef glUniform3fARB
glUniform3fARBFunc _glUniform3fARB = NULL;
#endif
#ifdef glUniform4fARB
glUniform4fARBFunc _glUniform4fARB = NULL;
#endif
#ifdef glUniform1iARB
glUniform1iARBFunc _glUniform1iARB = NULL;
#endif
#ifdef glUniform2iARB
glUniform2iARBFunc _glUniform2iARB = NULL;
#endif
#ifdef glUniform3iARB
glUniform3iARBFunc _glUniform3iARB = NULL;
#endif
#ifdef glUniform4iARB
glUniform4iARBFunc _glUniform4iARB = NULL;
#endif
#ifdef glUniform1fvARB
glUniform1fvARBFunc _glUniform1fvARB = NULL;
#endif
#ifdef glUniform2fvARB
glUniform2fvARBFunc _glUniform2fvARB = NULL;
#endif
#ifdef glUniform3fvARB
glUniform3fvARBFunc _glUniform3fvARB = NULL;
#endif
#ifdef glUniform4fvARB
glUniform4fvARBFunc _glUniform4fvARB = NULL;
#endif
#ifdef glUniform1ivARB
glUniform1ivARBFunc _glUniform1ivARB = NULL;
#endif
#ifdef glUniform2ivARB
glUniform2ivARBFunc _glUniform2ivARB = NULL;
#endif
#ifdef glUniform3ivARB
glUniform3ivARBFunc _glUniform3ivARB = NULL;
#endif
#ifdef glUniform4ivARB
glUniform4ivARBFunc _glUniform4ivARB = NULL;
#endif
#ifdef glUniformMatrix2fvARB
glUniformMatrix2fvARBFunc _glUniformMatrix2fvARB = NULL;
#endif
#ifdef glUniformMatrix3fvARB
glUniformMatrix3fvARBFunc _glUniformMatrix3fvARB = NULL;
#endif
#ifdef glUniformMatrix4fvARB
glUniformMatrix4fvARBFunc _glUniformMatrix4fvARB = NULL;
#endif
#ifdef glGetObjectParameterfvARB
glGetObjectParameterfvARBFunc _glGetObjectParameterfvARB = NULL;
#endif
#ifdef glGetObjectParameterivARB
glGetObjectParameterivARBFunc _glGetObjectParameterivARB = NULL;
#endif
#ifdef glGetInfoLogARB
glGetInfoLogARBFunc _glGetInfoLogARB = NULL;
#endif
#ifdef glGetAttachedObjectsARB
glGetAttachedObjectsARBFunc _glGetAttachedObjectsARB = NULL;
#endif
#ifdef glGetUniformLocationARB
glGetUniformLocationARBFunc _glGetUniformLocationARB = NULL;
#endif
#ifdef glGetActiveUniformARB
glGetActiveUniformARBFunc _glGetActiveUniformARB = NULL;
#endif
#ifdef glGetUniformfvARB
glGetUniformfvARBFunc _glGetUniformfvARB = NULL;
#endif
#ifdef glGetUniformivARB
glGetUniformivARBFunc _glGetUniformivARB = NULL;
#endif
#ifdef glGetShaderSourceARB
glGetShaderSourceARBFunc _glGetShaderSourceARB = NULL;
#endif
#ifdef glBindAttribLocationARB
glBindAttribLocationARBFunc _glBindAttribLocationARB = NULL;
#endif
#ifdef glGetActiveAttribARB
glGetActiveAttribARBFunc _glGetActiveAttribARB = NULL;
#endif
#ifdef glGetAttribLocationARB
glGetAttribLocationARBFunc _glGetAttribLocationARB = NULL;
#endif
#ifdef glDrawBuffersARB
glDrawBuffersARBFunc _glDrawBuffersARB = NULL;
#endif
#ifdef glClampColorARB
glClampColorARBFunc _glClampColorARB = NULL;
#endif
#ifdef glDrawArraysInstancedARB
glDrawArraysInstancedARBFunc _glDrawArraysInstancedARB = NULL;
#endif
#ifdef glDrawElementsInstancedARB
glDrawElementsInstancedARBFunc _glDrawElementsInstancedARB = NULL;
#endif
#ifdef glIsRenderbuffer
glIsRenderbufferFunc _glIsRenderbuffer = NULL;
#endif
#ifdef glBindRenderbuffer
glBindRenderbufferFunc _glBindRenderbuffer = NULL;
#endif
#ifdef glDeleteRenderbuffers
glDeleteRenderbuffersFunc _glDeleteRenderbuffers = NULL;
#endif
#ifdef glGenRenderbuffers
glGenRenderbuffersFunc _glGenRenderbuffers = NULL;
#endif
#ifdef glRenderbufferStorage
glRenderbufferStorageFunc _glRenderbufferStorage = NULL;
#endif
#ifdef glGetRenderbufferParameteriv
glGetRenderbufferParameterivFunc _glGetRenderbufferParameteriv = NULL;
#endif
#ifdef glIsFramebuffer
glIsFramebufferFunc _glIsFramebuffer = NULL;
#endif
#ifdef glBindFramebuffer
glBindFramebufferFunc _glBindFramebuffer = NULL;
#endif
#ifdef glDeleteFramebuffers
glDeleteFramebuffersFunc _glDeleteFramebuffers = NULL;
#endif
#ifdef glGenFramebuffers
glGenFramebuffersFunc _glGenFramebuffers = NULL;
#endif
#ifdef glCheckFramebufferStatus
glCheckFramebufferStatusFunc _glCheckFramebufferStatus = NULL;
#endif
#ifdef glFramebufferTexture1D
glFramebufferTexture1DFunc _glFramebufferTexture1D = NULL;
#endif
#ifdef glFramebufferTexture2D
glFramebufferTexture2DFunc _glFramebufferTexture2D = NULL;
#endif
#ifdef glFramebufferTexture3D
glFramebufferTexture3DFunc _glFramebufferTexture3D = NULL;
#endif
#ifdef glFramebufferRenderbuffer
glFramebufferRenderbufferFunc _glFramebufferRenderbuffer = NULL;
#endif
#ifdef glGetFramebufferAttachmentParameteriv
glGetFramebufferAttachmentParameterivFunc _glGetFramebufferAttachmentParameteriv = NULL;
#endif
#ifdef glGenerateMipmap
glGenerateMipmapFunc _glGenerateMipmap = NULL;
#endif
#ifdef glBlitFramebuffer
glBlitFramebufferFunc _glBlitFramebuffer = NULL;
#endif
#ifdef glRenderbufferStorageMultisample
glRenderbufferStorageMultisampleFunc _glRenderbufferStorageMultisample = NULL;
#endif
#ifdef glFramebufferTextureLayer
glFramebufferTextureLayerFunc _glFramebufferTextureLayer = NULL;
#endif
#ifdef glProgramParameteriARB
glProgramParameteriARBFunc _glProgramParameteriARB = NULL;
#endif
#ifdef glFramebufferTextureARB
glFramebufferTextureARBFunc _glFramebufferTextureARB = NULL;
#endif
#ifdef glFramebufferTextureLayerARB
glFramebufferTextureLayerARBFunc _glFramebufferTextureLayerARB = NULL;
#endif
#ifdef glFramebufferTextureFaceARB
glFramebufferTextureFaceARBFunc _glFramebufferTextureFaceARB = NULL;
#endif
#ifdef glVertexAttribDivisorARB
glVertexAttribDivisorARBFunc _glVertexAttribDivisorARB = NULL;
#endif
#ifdef glMapBufferRange
glMapBufferRangeFunc _glMapBufferRange = NULL;
#endif
#ifdef glFlushMappedBufferRange
glFlushMappedBufferRangeFunc _glFlushMappedBufferRange = NULL;
#endif
#ifdef glTexBufferARB
glTexBufferARBFunc _glTexBufferARB = NULL;
#endif
#ifdef glBindVertexArray
glBindVertexArrayFunc _glBindVertexArray = NULL;
#endif
#ifdef glDeleteVertexArrays
glDeleteVertexArraysFunc _glDeleteVertexArrays = NULL;
#endif
#ifdef glGenVertexArrays
glGenVertexArraysFunc _glGenVertexArrays = NULL;
#endif
#ifdef glIsVertexArray
glIsVertexArrayFunc _glIsVertexArray = NULL;
#endif
#ifdef glGetUniformIndices
glGetUniformIndicesFunc _glGetUniformIndices = NULL;
#endif
#ifdef glGetActiveUniformsiv
glGetActiveUniformsivFunc _glGetActiveUniformsiv = NULL;
#endif
#ifdef glGetActiveUniformName
glGetActiveUniformNameFunc _glGetActiveUniformName = NULL;
#endif
#ifdef glGetUniformBlockIndex
glGetUniformBlockIndexFunc _glGetUniformBlockIndex = NULL;
#endif
#ifdef glGetActiveUniformBlockiv
glGetActiveUniformBlockivFunc _glGetActiveUniformBlockiv = NULL;
#endif
#ifdef glGetActiveUniformBlockName
glGetActiveUniformBlockNameFunc _glGetActiveUniformBlockName = NULL;
#endif
#ifdef glUniformBlockBinding
glUniformBlockBindingFunc _glUniformBlockBinding = NULL;
#endif
#ifdef glCopyBufferSubData
glCopyBufferSubDataFunc _glCopyBufferSubData = NULL;
#endif
#ifdef glDrawElementsBaseVertex
glDrawElementsBaseVertexFunc _glDrawElementsBaseVertex = NULL;
#endif
#ifdef glDrawRangeElementsBaseVertex
glDrawRangeElementsBaseVertexFunc _glDrawRangeElementsBaseVertex = NULL;
#endif
#ifdef glDrawElementsInstancedBaseVertex
glDrawElementsInstancedBaseVertexFunc _glDrawElementsInstancedBaseVertex = NULL;
#endif
#ifdef glMultiDrawElementsBaseVertex
glMultiDrawElementsBaseVertexFunc _glMultiDrawElementsBaseVertex = NULL;
#endif
#ifdef glProvokingVertex
glProvokingVertexFunc _glProvokingVertex = NULL;
#endif
#ifdef glFenceSync
glFenceSyncFunc _glFenceSync = NULL;
#endif
#ifdef glIsSync
glIsSyncFunc _glIsSync = NULL;
#endif
#ifdef glDeleteSync
glDeleteSyncFunc _glDeleteSync = NULL;
#endif
#ifdef glClientWaitSync
glClientWaitSyncFunc _glClientWaitSync = NULL;
#endif
#ifdef glWaitSync
glWaitSyncFunc _glWaitSync = NULL;
#endif
#ifdef glGetInteger64v
glGetInteger64vFunc _glGetInteger64v = NULL;
#endif
#ifdef glGetSynciv
glGetSyncivFunc _glGetSynciv = NULL;
#endif
#ifdef glTexImage2DMultisample
glTexImage2DMultisampleFunc _glTexImage2DMultisample = NULL;
#endif
#ifdef glTexImage3DMultisample
glTexImage3DMultisampleFunc _glTexImage3DMultisample = NULL;
#endif
#ifdef glGetMultisamplefv
glGetMultisamplefvFunc _glGetMultisamplefv = NULL;
#endif
#ifdef glSampleMaski
glSampleMaskiFunc _glSampleMaski = NULL;
#endif
#ifdef glBlendEquationiARB
glBlendEquationiARBFunc _glBlendEquationiARB = NULL;
#endif
#ifdef glBlendEquationSeparateiARB
glBlendEquationSeparateiARBFunc _glBlendEquationSeparateiARB = NULL;
#endif
#ifdef glBlendFunciARB
glBlendFunciARBFunc _glBlendFunciARB = NULL;
#endif
#ifdef glBlendFuncSeparateiARB
glBlendFuncSeparateiARBFunc _glBlendFuncSeparateiARB = NULL;
#endif
#ifdef glMinSampleShadingARB
glMinSampleShadingARBFunc _glMinSampleShadingARB = NULL;
#endif
#ifdef glNamedStringARB
glNamedStringARBFunc _glNamedStringARB = NULL;
#endif
#ifdef glDeleteNamedStringARB
glDeleteNamedStringARBFunc _glDeleteNamedStringARB = NULL;
#endif
#ifdef glCompileShaderIncludeARB
glCompileShaderIncludeARBFunc _glCompileShaderIncludeARB = NULL;
#endif
#ifdef glIsNamedStringARB
glIsNamedStringARBFunc _glIsNamedStringARB = NULL;
#endif
#ifdef glGetNamedStringARB
glGetNamedStringARBFunc _glGetNamedStringARB = NULL;
#endif
#ifdef glGetNamedStringivARB
glGetNamedStringivARBFunc _glGetNamedStringivARB = NULL;
#endif
#ifdef glBindFragDataLocationIndexed
glBindFragDataLocationIndexedFunc _glBindFragDataLocationIndexed = NULL;
#endif
#ifdef glGetFragDataIndex
glGetFragDataIndexFunc _glGetFragDataIndex = NULL;
#endif
#ifdef glGenSamplers
glGenSamplersFunc _glGenSamplers = NULL;
#endif
#ifdef glDeleteSamplers
glDeleteSamplersFunc _glDeleteSamplers = NULL;
#endif
#ifdef glIsSampler
glIsSamplerFunc _glIsSampler = NULL;
#endif
#ifdef glBindSampler
glBindSamplerFunc _glBindSampler = NULL;
#endif
#ifdef glSamplerParameteri
glSamplerParameteriFunc _glSamplerParameteri = NULL;
#endif
#ifdef glSamplerParameteriv
glSamplerParameterivFunc _glSamplerParameteriv = NULL;
#endif
#ifdef glSamplerParameterf
glSamplerParameterfFunc _glSamplerParameterf = NULL;
#endif
#ifdef glSamplerParameterfv
glSamplerParameterfvFunc _glSamplerParameterfv = NULL;
#endif
#ifdef glSamplerParameterIiv
glSamplerParameterIivFunc _glSamplerParameterIiv = NULL;
#endif
#ifdef glSamplerParameterIuiv
glSamplerParameterIuivFunc _glSamplerParameterIuiv = NULL;
#endif
#ifdef glGetSamplerParameteriv
glGetSamplerParameterivFunc _glGetSamplerParameteriv = NULL;
#endif
#ifdef glGetSamplerParameterIiv
glGetSamplerParameterIivFunc _glGetSamplerParameterIiv = NULL;
#endif
#ifdef glGetSamplerParameterfv
glGetSamplerParameterfvFunc _glGetSamplerParameterfv = NULL;
#endif
#ifdef glGetSamplerParameterIuiv
glGetSamplerParameterIuivFunc _glGetSamplerParameterIuiv = NULL;
#endif
#ifdef glQueryCounter
glQueryCounterFunc _glQueryCounter = NULL;
#endif
#ifdef glGetQueryObjecti64v
glGetQueryObjecti64vFunc _glGetQueryObjecti64v = NULL;
#endif
#ifdef glGetQueryObjectui64v
glGetQueryObjectui64vFunc _glGetQueryObjectui64v = NULL;
#endif
#ifdef glVertexP2ui
glVertexP2uiFunc _glVertexP2ui = NULL;
#endif
#ifdef glVertexP2uiv
glVertexP2uivFunc _glVertexP2uiv = NULL;
#endif
#ifdef glVertexP3ui
glVertexP3uiFunc _glVertexP3ui = NULL;
#endif
#ifdef glVertexP3uiv
glVertexP3uivFunc _glVertexP3uiv = NULL;
#endif
#ifdef glVertexP4ui
glVertexP4uiFunc _glVertexP4ui = NULL;
#endif
#ifdef glVertexP4uiv
glVertexP4uivFunc _glVertexP4uiv = NULL;
#endif
#ifdef glTexCoordP1ui
glTexCoordP1uiFunc _glTexCoordP1ui = NULL;
#endif
#ifdef glTexCoordP1uiv
glTexCoordP1uivFunc _glTexCoordP1uiv = NULL;
#endif
#ifdef glTexCoordP2ui
glTexCoordP2uiFunc _glTexCoordP2ui = NULL;
#endif
#ifdef glTexCoordP2uiv
glTexCoordP2uivFunc _glTexCoordP2uiv = NULL;
#endif
#ifdef glTexCoordP3ui
glTexCoordP3uiFunc _glTexCoordP3ui = NULL;
#endif
#ifdef glTexCoordP3uiv
glTexCoordP3uivFunc _glTexCoordP3uiv = NULL;
#endif
#ifdef glTexCoordP4ui
glTexCoordP4uiFunc _glTexCoordP4ui = NULL;
#endif
#ifdef glTexCoordP4uiv
glTexCoordP4uivFunc _glTexCoordP4uiv = NULL;
#endif
#ifdef glMultiTexCoordP1ui
glMultiTexCoordP1uiFunc _glMultiTexCoordP1ui = NULL;
#endif
#ifdef glMultiTexCoordP1uiv
glMultiTexCoordP1uivFunc _glMultiTexCoordP1uiv = NULL;
#endif
#ifdef glMultiTexCoordP2ui
glMultiTexCoordP2uiFunc _glMultiTexCoordP2ui = NULL;
#endif
#ifdef glMultiTexCoordP2uiv
glMultiTexCoordP2uivFunc _glMultiTexCoordP2uiv = NULL;
#endif
#ifdef glMultiTexCoordP3ui
glMultiTexCoordP3uiFunc _glMultiTexCoordP3ui = NULL;
#endif
#ifdef glMultiTexCoordP3uiv
glMultiTexCoordP3uivFunc _glMultiTexCoordP3uiv = NULL;
#endif
#ifdef glMultiTexCoordP4ui
glMultiTexCoordP4uiFunc _glMultiTexCoordP4ui = NULL;
#endif
#ifdef glMultiTexCoordP4uiv
glMultiTexCoordP4uivFunc _glMultiTexCoordP4uiv = NULL;
#endif
#ifdef glNormalP3ui
glNormalP3uiFunc _glNormalP3ui = NULL;
#endif
#ifdef glNormalP3uiv
glNormalP3uivFunc _glNormalP3uiv = NULL;
#endif
#ifdef glColorP3ui
glColorP3uiFunc _glColorP3ui = NULL;
#endif
#ifdef glColorP3uiv
glColorP3uivFunc _glColorP3uiv = NULL;
#endif
#ifdef glColorP4ui
glColorP4uiFunc _glColorP4ui = NULL;
#endif
#ifdef glColorP4uiv
glColorP4uivFunc _glColorP4uiv = NULL;
#endif
#ifdef glSecondaryColorP3ui
glSecondaryColorP3uiFunc _glSecondaryColorP3ui = NULL;
#endif
#ifdef glSecondaryColorP3uiv
glSecondaryColorP3uivFunc _glSecondaryColorP3uiv = NULL;
#endif
#ifdef glVertexAttribP1ui
glVertexAttribP1uiFunc _glVertexAttribP1ui = NULL;
#endif
#ifdef glVertexAttribP1uiv
glVertexAttribP1uivFunc _glVertexAttribP1uiv = NULL;
#endif
#ifdef glVertexAttribP2ui
glVertexAttribP2uiFunc _glVertexAttribP2ui = NULL;
#endif
#ifdef glVertexAttribP2uiv
glVertexAttribP2uivFunc _glVertexAttribP2uiv = NULL;
#endif
#ifdef glVertexAttribP3ui
glVertexAttribP3uiFunc _glVertexAttribP3ui = NULL;
#endif
#ifdef glVertexAttribP3uiv
glVertexAttribP3uivFunc _glVertexAttribP3uiv = NULL;
#endif
#ifdef glVertexAttribP4ui
glVertexAttribP4uiFunc _glVertexAttribP4ui = NULL;
#endif
#ifdef glVertexAttribP4uiv
glVertexAttribP4uivFunc _glVertexAttribP4uiv = NULL;
#endif
#ifdef glDrawArraysIndirect
glDrawArraysIndirectFunc _glDrawArraysIndirect = NULL;
#endif
#ifdef glDrawElementsIndirect
glDrawElementsIndirectFunc _glDrawElementsIndirect = NULL;
#endif
#ifdef glUniform1d
glUniform1dFunc _glUniform1d = NULL;
#endif
#ifdef glUniform2d
glUniform2dFunc _glUniform2d = NULL;
#endif
#ifdef glUniform3d
glUniform3dFunc _glUniform3d = NULL;
#endif
#ifdef glUniform4d
glUniform4dFunc _glUniform4d = NULL;
#endif
#ifdef glUniform1dv
glUniform1dvFunc _glUniform1dv = NULL;
#endif
#ifdef glUniform2dv
glUniform2dvFunc _glUniform2dv = NULL;
#endif
#ifdef glUniform3dv
glUniform3dvFunc _glUniform3dv = NULL;
#endif
#ifdef glUniform4dv
glUniform4dvFunc _glUniform4dv = NULL;
#endif
#ifdef glUniformMatrix2dv
glUniformMatrix2dvFunc _glUniformMatrix2dv = NULL;
#endif
#ifdef glUniformMatrix3dv
glUniformMatrix3dvFunc _glUniformMatrix3dv = NULL;
#endif
#ifdef glUniformMatrix4dv
glUniformMatrix4dvFunc _glUniformMatrix4dv = NULL;
#endif
#ifdef glUniformMatrix2x3dv
glUniformMatrix2x3dvFunc _glUniformMatrix2x3dv = NULL;
#endif
#ifdef glUniformMatrix2x4dv
glUniformMatrix2x4dvFunc _glUniformMatrix2x4dv = NULL;
#endif
#ifdef glUniformMatrix3x2dv
glUniformMatrix3x2dvFunc _glUniformMatrix3x2dv = NULL;
#endif
#ifdef glUniformMatrix3x4dv
glUniformMatrix3x4dvFunc _glUniformMatrix3x4dv = NULL;
#endif
#ifdef glUniformMatrix4x2dv
glUniformMatrix4x2dvFunc _glUniformMatrix4x2dv = NULL;
#endif
#ifdef glUniformMatrix4x3dv
glUniformMatrix4x3dvFunc _glUniformMatrix4x3dv = NULL;
#endif
#ifdef glGetUniformdv
glGetUniformdvFunc _glGetUniformdv = NULL;
#endif
#ifdef glGetSubroutineUniformLocation
glGetSubroutineUniformLocationFunc _glGetSubroutineUniformLocation = NULL;
#endif
#ifdef glGetSubroutineIndex
glGetSubroutineIndexFunc _glGetSubroutineIndex = NULL;
#endif
#ifdef glGetActiveSubroutineUniformiv
glGetActiveSubroutineUniformivFunc _glGetActiveSubroutineUniformiv = NULL;
#endif
#ifdef glGetActiveSubroutineUniformName
glGetActiveSubroutineUniformNameFunc _glGetActiveSubroutineUniformName = NULL;
#endif
#ifdef glGetActiveSubroutineName
glGetActiveSubroutineNameFunc _glGetActiveSubroutineName = NULL;
#endif
#ifdef glUniformSubroutinesuiv
glUniformSubroutinesuivFunc _glUniformSubroutinesuiv = NULL;
#endif
#ifdef glGetUniformSubroutineuiv
glGetUniformSubroutineuivFunc _glGetUniformSubroutineuiv = NULL;
#endif
#ifdef glGetProgramStageiv
glGetProgramStageivFunc _glGetProgramStageiv = NULL;
#endif
#ifdef glPatchParameteri
glPatchParameteriFunc _glPatchParameteri = NULL;
#endif
#ifdef glPatchParameterfv
glPatchParameterfvFunc _glPatchParameterfv = NULL;
#endif
#ifdef glBindTransformFeedback
glBindTransformFeedbackFunc _glBindTransformFeedback = NULL;
#endif
#ifdef glDeleteTransformFeedbacks
glDeleteTransformFeedbacksFunc _glDeleteTransformFeedbacks = NULL;
#endif
#ifdef glGenTransformFeedbacks
glGenTransformFeedbacksFunc _glGenTransformFeedbacks = NULL;
#endif
#ifdef glIsTransformFeedback
glIsTransformFeedbackFunc _glIsTransformFeedback = NULL;
#endif
#ifdef glPauseTransformFeedback
glPauseTransformFeedbackFunc _glPauseTransformFeedback = NULL;
#endif
#ifdef glResumeTransformFeedback
glResumeTransformFeedbackFunc _glResumeTransformFeedback = NULL;
#endif
#ifdef glDrawTransformFeedback
glDrawTransformFeedbackFunc _glDrawTransformFeedback = NULL;
#endif
#ifdef glDrawTransformFeedbackStream
glDrawTransformFeedbackStreamFunc _glDrawTransformFeedbackStream = NULL;
#endif
#ifdef glBeginQueryIndexed
glBeginQueryIndexedFunc _glBeginQueryIndexed = NULL;
#endif
#ifdef glEndQueryIndexed
glEndQueryIndexedFunc _glEndQueryIndexed = NULL;
#endif
#ifdef glGetQueryIndexediv
glGetQueryIndexedivFunc _glGetQueryIndexediv = NULL;
#endif
#ifdef glReleaseShaderCompiler
glReleaseShaderCompilerFunc _glReleaseShaderCompiler = NULL;
#endif
#ifdef glShaderBinary
glShaderBinaryFunc _glShaderBinary = NULL;
#endif
#ifdef glGetShaderPrecisionFormat
glGetShaderPrecisionFormatFunc _glGetShaderPrecisionFormat = NULL;
#endif
#ifdef glDepthRangef
glDepthRangefFunc _glDepthRangef = NULL;
#endif
#ifdef glClearDepthf
glClearDepthfFunc _glClearDepthf = NULL;
#endif
#ifdef glGetProgramBinary
glGetProgramBinaryFunc _glGetProgramBinary = NULL;
#endif
#ifdef glProgramBinary
glProgramBinaryFunc _glProgramBinary = NULL;
#endif
#ifdef glProgramParameteri
glProgramParameteriFunc _glProgramParameteri = NULL;
#endif
#ifdef glUseProgramStages
glUseProgramStagesFunc _glUseProgramStages = NULL;
#endif
#ifdef glActiveShaderProgram
glActiveShaderProgramFunc _glActiveShaderProgram = NULL;
#endif
#ifdef glCreateShaderProgramv
glCreateShaderProgramvFunc _glCreateShaderProgramv = NULL;
#endif
#ifdef glBindProgramPipeline
glBindProgramPipelineFunc _glBindProgramPipeline = NULL;
#endif
#ifdef glDeleteProgramPipelines
glDeleteProgramPipelinesFunc _glDeleteProgramPipelines = NULL;
#endif
#ifdef glGenProgramPipelines
glGenProgramPipelinesFunc _glGenProgramPipelines = NULL;
#endif
#ifdef glIsProgramPipeline
glIsProgramPipelineFunc _glIsProgramPipeline = NULL;
#endif
#ifdef glGetProgramPipelineiv
glGetProgramPipelineivFunc _glGetProgramPipelineiv = NULL;
#endif
#ifdef glProgramUniform1i
glProgramUniform1iFunc _glProgramUniform1i = NULL;
#endif
#ifdef glProgramUniform1iv
glProgramUniform1ivFunc _glProgramUniform1iv = NULL;
#endif
#ifdef glProgramUniform1f
glProgramUniform1fFunc _glProgramUniform1f = NULL;
#endif
#ifdef glProgramUniform1fv
glProgramUniform1fvFunc _glProgramUniform1fv = NULL;
#endif
#ifdef glProgramUniform1d
glProgramUniform1dFunc _glProgramUniform1d = NULL;
#endif
#ifdef glProgramUniform1dv
glProgramUniform1dvFunc _glProgramUniform1dv = NULL;
#endif
#ifdef glProgramUniform1ui
glProgramUniform1uiFunc _glProgramUniform1ui = NULL;
#endif
#ifdef glProgramUniform1uiv
glProgramUniform1uivFunc _glProgramUniform1uiv = NULL;
#endif
#ifdef glProgramUniform2i
glProgramUniform2iFunc _glProgramUniform2i = NULL;
#endif
#ifdef glProgramUniform2iv
glProgramUniform2ivFunc _glProgramUniform2iv = NULL;
#endif
#ifdef glProgramUniform2f
glProgramUniform2fFunc _glProgramUniform2f = NULL;
#endif
#ifdef glProgramUniform2fv
glProgramUniform2fvFunc _glProgramUniform2fv = NULL;
#endif
#ifdef glProgramUniform2d
glProgramUniform2dFunc _glProgramUniform2d = NULL;
#endif
#ifdef glProgramUniform2dv
glProgramUniform2dvFunc _glProgramUniform2dv = NULL;
#endif
#ifdef glProgramUniform2ui
glProgramUniform2uiFunc _glProgramUniform2ui = NULL;
#endif
#ifdef glProgramUniform2uiv
glProgramUniform2uivFunc _glProgramUniform2uiv = NULL;
#endif
#ifdef glProgramUniform3i
glProgramUniform3iFunc _glProgramUniform3i = NULL;
#endif
#ifdef glProgramUniform3iv
glProgramUniform3ivFunc _glProgramUniform3iv = NULL;
#endif
#ifdef glProgramUniform3f
glProgramUniform3fFunc _glProgramUniform3f = NULL;
#endif
#ifdef glProgramUniform3fv
glProgramUniform3fvFunc _glProgramUniform3fv = NULL;
#endif
#ifdef glProgramUniform3d
glProgramUniform3dFunc _glProgramUniform3d = NULL;
#endif
#ifdef glProgramUniform3dv
glProgramUniform3dvFunc _glProgramUniform3dv = NULL;
#endif
#ifdef glProgramUniform3ui
glProgramUniform3uiFunc _glProgramUniform3ui = NULL;
#endif
#ifdef glProgramUniform3uiv
glProgramUniform3uivFunc _glProgramUniform3uiv = NULL;
#endif
#ifdef glProgramUniform4i
glProgramUniform4iFunc _glProgramUniform4i = NULL;
#endif
#ifdef glProgramUniform4iv
glProgramUniform4ivFunc _glProgramUniform4iv = NULL;
#endif
#ifdef glProgramUniform4f
glProgramUniform4fFunc _glProgramUniform4f = NULL;
#endif
#ifdef glProgramUniform4fv
glProgramUniform4fvFunc _glProgramUniform4fv = NULL;
#endif
#ifdef glProgramUniform4d
glProgramUniform4dFunc _glProgramUniform4d = NULL;
#endif
#ifdef glProgramUniform4dv
glProgramUniform4dvFunc _glProgramUniform4dv = NULL;
#endif
#ifdef glProgramUniform4ui
glProgramUniform4uiFunc _glProgramUniform4ui = NULL;
#endif
#ifdef glProgramUniform4uiv
glProgramUniform4uivFunc _glProgramUniform4uiv = NULL;
#endif
#ifdef glProgramUniformMatrix2fv
glProgramUniformMatrix2fvFunc _glProgramUniformMatrix2fv = NULL;
#endif
#ifdef glProgramUniformMatrix3fv
glProgramUniformMatrix3fvFunc _glProgramUniformMatrix3fv = NULL;
#endif
#ifdef glProgramUniformMatrix4fv
glProgramUniformMatrix4fvFunc _glProgramUniformMatrix4fv = NULL;
#endif
#ifdef glProgramUniformMatrix2dv
glProgramUniformMatrix2dvFunc _glProgramUniformMatrix2dv = NULL;
#endif
#ifdef glProgramUniformMatrix3dv
glProgramUniformMatrix3dvFunc _glProgramUniformMatrix3dv = NULL;
#endif
#ifdef glProgramUniformMatrix4dv
glProgramUniformMatrix4dvFunc _glProgramUniformMatrix4dv = NULL;
#endif
#ifdef glProgramUniformMatrix2x3fv
glProgramUniformMatrix2x3fvFunc _glProgramUniformMatrix2x3fv = NULL;
#endif
#ifdef glProgramUniformMatrix3x2fv
glProgramUniformMatrix3x2fvFunc _glProgramUniformMatrix3x2fv = NULL;
#endif
#ifdef glProgramUniformMatrix2x4fv
glProgramUniformMatrix2x4fvFunc _glProgramUniformMatrix2x4fv = NULL;
#endif
#ifdef glProgramUniformMatrix4x2fv
glProgramUniformMatrix4x2fvFunc _glProgramUniformMatrix4x2fv = NULL;
#endif
#ifdef glProgramUniformMatrix3x4fv
glProgramUniformMatrix3x4fvFunc _glProgramUniformMatrix3x4fv = NULL;
#endif
#ifdef glProgramUniformMatrix4x3fv
glProgramUniformMatrix4x3fvFunc _glProgramUniformMatrix4x3fv = NULL;
#endif
#ifdef glProgramUniformMatrix2x3dv
glProgramUniformMatrix2x3dvFunc _glProgramUniformMatrix2x3dv = NULL;
#endif
#ifdef glProgramUniformMatrix3x2dv
glProgramUniformMatrix3x2dvFunc _glProgramUniformMatrix3x2dv = NULL;
#endif
#ifdef glProgramUniformMatrix2x4dv
glProgramUniformMatrix2x4dvFunc _glProgramUniformMatrix2x4dv = NULL;
#endif
#ifdef glProgramUniformMatrix4x2dv
glProgramUniformMatrix4x2dvFunc _glProgramUniformMatrix4x2dv = NULL;
#endif
#ifdef glProgramUniformMatrix3x4dv
glProgramUniformMatrix3x4dvFunc _glProgramUniformMatrix3x4dv = NULL;
#endif
#ifdef glProgramUniformMatrix4x3dv
glProgramUniformMatrix4x3dvFunc _glProgramUniformMatrix4x3dv = NULL;
#endif
#ifdef glValidateProgramPipeline
glValidateProgramPipelineFunc _glValidateProgramPipeline = NULL;
#endif
#ifdef glGetProgramPipelineInfoLog
glGetProgramPipelineInfoLogFunc _glGetProgramPipelineInfoLog = NULL;
#endif
#ifdef glVertexAttribL1d
glVertexAttribL1dFunc _glVertexAttribL1d = NULL;
#endif
#ifdef glVertexAttribL2d
glVertexAttribL2dFunc _glVertexAttribL2d = NULL;
#endif
#ifdef glVertexAttribL3d
glVertexAttribL3dFunc _glVertexAttribL3d = NULL;
#endif
#ifdef glVertexAttribL4d
glVertexAttribL4dFunc _glVertexAttribL4d = NULL;
#endif
#ifdef glVertexAttribL1dv
glVertexAttribL1dvFunc _glVertexAttribL1dv = NULL;
#endif
#ifdef glVertexAttribL2dv
glVertexAttribL2dvFunc _glVertexAttribL2dv = NULL;
#endif
#ifdef glVertexAttribL3dv
glVertexAttribL3dvFunc _glVertexAttribL3dv = NULL;
#endif
#ifdef glVertexAttribL4dv
glVertexAttribL4dvFunc _glVertexAttribL4dv = NULL;
#endif
#ifdef glVertexAttribLPointer
glVertexAttribLPointerFunc _glVertexAttribLPointer = NULL;
#endif
#ifdef glGetVertexAttribLdv
glGetVertexAttribLdvFunc _glGetVertexAttribLdv = NULL;
#endif
#ifdef glViewportArrayv
glViewportArrayvFunc _glViewportArrayv = NULL;
#endif
#ifdef glViewportIndexedf
glViewportIndexedfFunc _glViewportIndexedf = NULL;
#endif
#ifdef glViewportIndexedfv
glViewportIndexedfvFunc _glViewportIndexedfv = NULL;
#endif
#ifdef glScissorArrayv
glScissorArrayvFunc _glScissorArrayv = NULL;
#endif
#ifdef glScissorIndexed
glScissorIndexedFunc _glScissorIndexed = NULL;
#endif
#ifdef glScissorIndexedv
glScissorIndexedvFunc _glScissorIndexedv = NULL;
#endif
#ifdef glDepthRangeArrayv
glDepthRangeArrayvFunc _glDepthRangeArrayv = NULL;
#endif
#ifdef glDepthRangeIndexed
glDepthRangeIndexedFunc _glDepthRangeIndexed = NULL;
#endif
#ifdef glGetFloati_v
glGetFloati_vFunc _glGetFloati_v = NULL;
#endif
#ifdef glGetDoublei_v
glGetDoublei_vFunc _glGetDoublei_v = NULL;
#endif
#ifdef glCreateSyncFromCLeventARB
glCreateSyncFromCLeventARBFunc _glCreateSyncFromCLeventARB = NULL;
#endif
#ifdef glDebugMessageControlARB
glDebugMessageControlARBFunc _glDebugMessageControlARB = NULL;
#endif
#ifdef glDebugMessageInsertARB
glDebugMessageInsertARBFunc _glDebugMessageInsertARB = NULL;
#endif
#ifdef glDebugMessageCallbackARB
glDebugMessageCallbackARBFunc _glDebugMessageCallbackARB = NULL;
#endif
#ifdef glGetDebugMessageLogARB
glGetDebugMessageLogARBFunc _glGetDebugMessageLogARB = NULL;
#endif
#ifdef glGetGraphicsResetStatusARB
glGetGraphicsResetStatusARBFunc _glGetGraphicsResetStatusARB = NULL;
#endif
#ifdef glGetnMapdvARB
glGetnMapdvARBFunc _glGetnMapdvARB = NULL;
#endif
#ifdef glGetnMapfvARB
glGetnMapfvARBFunc _glGetnMapfvARB = NULL;
#endif
#ifdef glGetnMapivARB
glGetnMapivARBFunc _glGetnMapivARB = NULL;
#endif
#ifdef glGetnPixelMapfvARB
glGetnPixelMapfvARBFunc _glGetnPixelMapfvARB = NULL;
#endif
#ifdef glGetnPixelMapuivARB
glGetnPixelMapuivARBFunc _glGetnPixelMapuivARB = NULL;
#endif
#ifdef glGetnPixelMapusvARB
glGetnPixelMapusvARBFunc _glGetnPixelMapusvARB = NULL;
#endif
#ifdef glGetnPolygonStippleARB
glGetnPolygonStippleARBFunc _glGetnPolygonStippleARB = NULL;
#endif
#ifdef glGetnColorTableARB
glGetnColorTableARBFunc _glGetnColorTableARB = NULL;
#endif
#ifdef glGetnConvolutionFilterARB
glGetnConvolutionFilterARBFunc _glGetnConvolutionFilterARB = NULL;
#endif
#ifdef glGetnSeparableFilterARB
glGetnSeparableFilterARBFunc _glGetnSeparableFilterARB = NULL;
#endif
#ifdef glGetnHistogramARB
glGetnHistogramARBFunc _glGetnHistogramARB = NULL;
#endif
#ifdef glGetnMinmaxARB
glGetnMinmaxARBFunc _glGetnMinmaxARB = NULL;
#endif
#ifdef glGetnTexImageARB
glGetnTexImageARBFunc _glGetnTexImageARB = NULL;
#endif
#ifdef glReadnPixelsARB
glReadnPixelsARBFunc _glReadnPixelsARB = NULL;
#endif
#ifdef glGetnCompressedTexImageARB
glGetnCompressedTexImageARBFunc _glGetnCompressedTexImageARB = NULL;
#endif
#ifdef glGetnUniformfvARB
glGetnUniformfvARBFunc _glGetnUniformfvARB = NULL;
#endif
#ifdef glGetnUniformivARB
glGetnUniformivARBFunc _glGetnUniformivARB = NULL;
#endif
#ifdef glGetnUniformuivARB
glGetnUniformuivARBFunc _glGetnUniformuivARB = NULL;
#endif
#ifdef glGetnUniformdvARB
glGetnUniformdvARBFunc _glGetnUniformdvARB = NULL;
#endif
#ifdef glDrawArraysInstancedBaseInstance
glDrawArraysInstancedBaseInstanceFunc _glDrawArraysInstancedBaseInstance = NULL;
#endif
#ifdef glDrawElementsInstancedBaseInstance
glDrawElementsInstancedBaseInstanceFunc _glDrawElementsInstancedBaseInstance = NULL;
#endif
#ifdef glDrawElementsInstancedBaseVertexBaseInstance
glDrawElementsInstancedBaseVertexBaseInstanceFunc _glDrawElementsInstancedBaseVertexBaseInstance = NULL;
#endif
#ifdef glDrawTransformFeedbackInstanced
glDrawTransformFeedbackInstancedFunc _glDrawTransformFeedbackInstanced = NULL;
#endif
#ifdef glDrawTransformFeedbackStreamInstanced
glDrawTransformFeedbackStreamInstancedFunc _glDrawTransformFeedbackStreamInstanced = NULL;
#endif
#ifdef glGetInternalformativ
glGetInternalformativFunc _glGetInternalformativ = NULL;
#endif
#ifdef glGetActiveAtomicCounterBufferiv
glGetActiveAtomicCounterBufferivFunc _glGetActiveAtomicCounterBufferiv = NULL;
#endif
#ifdef glBindImageTexture
glBindImageTextureFunc _glBindImageTexture = NULL;
#endif
#ifdef glMemoryBarrier
glMemoryBarrierFunc _glMemoryBarrier = NULL;
#endif
#ifdef glTexStorage1D
glTexStorage1DFunc _glTexStorage1D = NULL;
#endif
#ifdef glTexStorage2D
glTexStorage2DFunc _glTexStorage2D = NULL;
#endif
#ifdef glTexStorage3D
glTexStorage3DFunc _glTexStorage3D = NULL;
#endif
#ifdef glTextureStorage1DEXT
glTextureStorage1DEXTFunc _glTextureStorage1DEXT = NULL;
#endif
#ifdef glTextureStorage2DEXT
glTextureStorage2DEXTFunc _glTextureStorage2DEXT = NULL;
#endif
#ifdef glTextureStorage3DEXT
glTextureStorage3DEXTFunc _glTextureStorage3DEXT = NULL;
#endif
#ifdef glDebugMessageControl
glDebugMessageControlFunc _glDebugMessageControl = NULL;
#endif
#ifdef glDebugMessageInsert
glDebugMessageInsertFunc _glDebugMessageInsert = NULL;
#endif
#ifdef glDebugMessageCallback
glDebugMessageCallbackFunc _glDebugMessageCallback = NULL;
#endif
#ifdef glGetDebugMessageLog
glGetDebugMessageLogFunc _glGetDebugMessageLog = NULL;
#endif
#ifdef glPushDebugGroup
glPushDebugGroupFunc _glPushDebugGroup = NULL;
#endif
#ifdef glPopDebugGroup
glPopDebugGroupFunc _glPopDebugGroup = NULL;
#endif
#ifdef glObjectLabel
glObjectLabelFunc _glObjectLabel = NULL;
#endif
#ifdef glGetObjectLabel
glGetObjectLabelFunc _glGetObjectLabel = NULL;
#endif
#ifdef glObjectPtrLabel
glObjectPtrLabelFunc _glObjectPtrLabel = NULL;
#endif
#ifdef glGetObjectPtrLabel
glGetObjectPtrLabelFunc _glGetObjectPtrLabel = NULL;
#endif
#ifdef glClearBufferData
glClearBufferDataFunc _glClearBufferData = NULL;
#endif
#ifdef glClearBufferSubData
glClearBufferSubDataFunc _glClearBufferSubData = NULL;
#endif
#ifdef glClearNamedBufferDataEXT
glClearNamedBufferDataEXTFunc _glClearNamedBufferDataEXT = NULL;
#endif
#ifdef glClearNamedBufferSubDataEXT
glClearNamedBufferSubDataEXTFunc _glClearNamedBufferSubDataEXT = NULL;
#endif
#ifdef glDispatchCompute
glDispatchComputeFunc _glDispatchCompute = NULL;
#endif
#ifdef glDispatchComputeIndirect
glDispatchComputeIndirectFunc _glDispatchComputeIndirect = NULL;
#endif
#ifdef glCopyImageSubData
glCopyImageSubDataFunc _glCopyImageSubData = NULL;
#endif
#ifdef glTextureView
glTextureViewFunc _glTextureView = NULL;
#endif
#ifdef glBindVertexBuffer
glBindVertexBufferFunc _glBindVertexBuffer = NULL;
#endif
#ifdef glVertexAttribFormat
glVertexAttribFormatFunc _glVertexAttribFormat = NULL;
#endif
#ifdef glVertexAttribIFormat
glVertexAttribIFormatFunc _glVertexAttribIFormat = NULL;
#endif
#ifdef glVertexAttribLFormat
glVertexAttribLFormatFunc _glVertexAttribLFormat = NULL;
#endif
#ifdef glVertexAttribBinding
glVertexAttribBindingFunc _glVertexAttribBinding = NULL;
#endif
#ifdef glVertexBindingDivisor
glVertexBindingDivisorFunc _glVertexBindingDivisor = NULL;
#endif
#ifdef glVertexArrayBindVertexBufferEXT
glVertexArrayBindVertexBufferEXTFunc _glVertexArrayBindVertexBufferEXT = NULL;
#endif
#ifdef glVertexArrayVertexAttribFormatEXT
glVertexArrayVertexAttribFormatEXTFunc _glVertexArrayVertexAttribFormatEXT = NULL;
#endif
#ifdef glVertexArrayVertexAttribIFormatEXT
glVertexArrayVertexAttribIFormatEXTFunc _glVertexArrayVertexAttribIFormatEXT = NULL;
#endif
#ifdef glVertexArrayVertexAttribLFormatEXT
glVertexArrayVertexAttribLFormatEXTFunc _glVertexArrayVertexAttribLFormatEXT = NULL;
#endif
#ifdef glVertexArrayVertexAttribBindingEXT
glVertexArrayVertexAttribBindingEXTFunc _glVertexArrayVertexAttribBindingEXT = NULL;
#endif
#ifdef glVertexArrayVertexBindingDivisorEXT
glVertexArrayVertexBindingDivisorEXTFunc _glVertexArrayVertexBindingDivisorEXT = NULL;
#endif
#ifdef glFramebufferParameteri
glFramebufferParameteriFunc _glFramebufferParameteri = NULL;
#endif
#ifdef glGetFramebufferParameteriv
glGetFramebufferParameterivFunc _glGetFramebufferParameteriv = NULL;
#endif
#ifdef glNamedFramebufferParameteriEXT
glNamedFramebufferParameteriEXTFunc _glNamedFramebufferParameteriEXT = NULL;
#endif
#ifdef glGetNamedFramebufferParameterivEXT
glGetNamedFramebufferParameterivEXTFunc _glGetNamedFramebufferParameterivEXT = NULL;
#endif
#ifdef glGetInternalformati64v
glGetInternalformati64vFunc _glGetInternalformati64v = NULL;
#endif
#ifdef glInvalidateTexSubImage
glInvalidateTexSubImageFunc _glInvalidateTexSubImage = NULL;
#endif
#ifdef glInvalidateTexImage
glInvalidateTexImageFunc _glInvalidateTexImage = NULL;
#endif
#ifdef glInvalidateBufferSubData
glInvalidateBufferSubDataFunc _glInvalidateBufferSubData = NULL;
#endif
#ifdef glInvalidateBufferData
glInvalidateBufferDataFunc _glInvalidateBufferData = NULL;
#endif
#ifdef glInvalidateFramebuffer
glInvalidateFramebufferFunc _glInvalidateFramebuffer = NULL;
#endif
#ifdef glInvalidateSubFramebuffer
glInvalidateSubFramebufferFunc _glInvalidateSubFramebuffer = NULL;
#endif
#ifdef glMultiDrawArraysIndirect
glMultiDrawArraysIndirectFunc _glMultiDrawArraysIndirect = NULL;
#endif
#ifdef glMultiDrawElementsIndirect
glMultiDrawElementsIndirectFunc _glMultiDrawElementsIndirect = NULL;
#endif
#ifdef glGetProgramInterfaceiv
glGetProgramInterfaceivFunc _glGetProgramInterfaceiv = NULL;
#endif
#ifdef glGetProgramResourceIndex
glGetProgramResourceIndexFunc _glGetProgramResourceIndex = NULL;
#endif
#ifdef glGetProgramResourceName
glGetProgramResourceNameFunc _glGetProgramResourceName = NULL;
#endif
#ifdef glGetProgramResourceiv
glGetProgramResourceivFunc _glGetProgramResourceiv = NULL;
#endif
#ifdef glGetProgramResourceLocation
glGetProgramResourceLocationFunc _glGetProgramResourceLocation = NULL;
#endif
#ifdef glGetProgramResourceLocationIndex
glGetProgramResourceLocationIndexFunc _glGetProgramResourceLocationIndex = NULL;
#endif
#ifdef glShaderStorageBlockBinding
glShaderStorageBlockBindingFunc _glShaderStorageBlockBinding = NULL;
#endif
#ifdef glTexBufferRange
glTexBufferRangeFunc _glTexBufferRange = NULL;
#endif
#ifdef glTextureBufferRangeEXT
glTextureBufferRangeEXTFunc _glTextureBufferRangeEXT = NULL;
#endif
#ifdef glTexStorage2DMultisample
glTexStorage2DMultisampleFunc _glTexStorage2DMultisample = NULL;
#endif
#ifdef glTexStorage3DMultisample
glTexStorage3DMultisampleFunc _glTexStorage3DMultisample = NULL;
#endif
#ifdef glTextureStorage2DMultisampleEXT
glTextureStorage2DMultisampleEXTFunc _glTextureStorage2DMultisampleEXT = NULL;
#endif
#ifdef glTextureStorage3DMultisampleEXT
glTextureStorage3DMultisampleEXTFunc _glTextureStorage3DMultisampleEXT = NULL;
#endif
#ifdef glBlendColorEXT
glBlendColorEXTFunc _glBlendColorEXT = NULL;
#endif
#ifdef glPolygonOffsetEXT
glPolygonOffsetEXTFunc _glPolygonOffsetEXT = NULL;
#endif
#ifdef glTexImage3DEXT
glTexImage3DEXTFunc _glTexImage3DEXT = NULL;
#endif
#ifdef glTexSubImage3DEXT
glTexSubImage3DEXTFunc _glTexSubImage3DEXT = NULL;
#endif
#ifdef glGetTexFilterFuncSGIS
glGetTexFilterFuncSGISFunc _glGetTexFilterFuncSGIS = NULL;
#endif
#ifdef glTexFilterFuncSGIS
glTexFilterFuncSGISFunc _glTexFilterFuncSGIS = NULL;
#endif
#ifdef glTexSubImage1DEXT
glTexSubImage1DEXTFunc _glTexSubImage1DEXT = NULL;
#endif
#ifdef glTexSubImage2DEXT
glTexSubImage2DEXTFunc _glTexSubImage2DEXT = NULL;
#endif
#ifdef glCopyTexImage1DEXT
glCopyTexImage1DEXTFunc _glCopyTexImage1DEXT = NULL;
#endif
#ifdef glCopyTexImage2DEXT
glCopyTexImage2DEXTFunc _glCopyTexImage2DEXT = NULL;
#endif
#ifdef glCopyTexSubImage1DEXT
glCopyTexSubImage1DEXTFunc _glCopyTexSubImage1DEXT = NULL;
#endif
#ifdef glCopyTexSubImage2DEXT
glCopyTexSubImage2DEXTFunc _glCopyTexSubImage2DEXT = NULL;
#endif
#ifdef glCopyTexSubImage3DEXT
glCopyTexSubImage3DEXTFunc _glCopyTexSubImage3DEXT = NULL;
#endif
#ifdef glGetHistogramEXT
glGetHistogramEXTFunc _glGetHistogramEXT = NULL;
#endif
#ifdef glGetHistogramParameterfvEXT
glGetHistogramParameterfvEXTFunc _glGetHistogramParameterfvEXT = NULL;
#endif
#ifdef glGetHistogramParameterivEXT
glGetHistogramParameterivEXTFunc _glGetHistogramParameterivEXT = NULL;
#endif
#ifdef glGetMinmaxEXT
glGetMinmaxEXTFunc _glGetMinmaxEXT = NULL;
#endif
#ifdef glGetMinmaxParameterfvEXT
glGetMinmaxParameterfvEXTFunc _glGetMinmaxParameterfvEXT = NULL;
#endif
#ifdef glGetMinmaxParameterivEXT
glGetMinmaxParameterivEXTFunc _glGetMinmaxParameterivEXT = NULL;
#endif
#ifdef glHistogramEXT
glHistogramEXTFunc _glHistogramEXT = NULL;
#endif
#ifdef glMinmaxEXT
glMinmaxEXTFunc _glMinmaxEXT = NULL;
#endif
#ifdef glResetHistogramEXT
glResetHistogramEXTFunc _glResetHistogramEXT = NULL;
#endif
#ifdef glResetMinmaxEXT
glResetMinmaxEXTFunc _glResetMinmaxEXT = NULL;
#endif
#ifdef glConvolutionFilter1DEXT
glConvolutionFilter1DEXTFunc _glConvolutionFilter1DEXT = NULL;
#endif
#ifdef glConvolutionFilter2DEXT
glConvolutionFilter2DEXTFunc _glConvolutionFilter2DEXT = NULL;
#endif
#ifdef glConvolutionParameterfEXT
glConvolutionParameterfEXTFunc _glConvolutionParameterfEXT = NULL;
#endif
#ifdef glConvolutionParameterfvEXT
glConvolutionParameterfvEXTFunc _glConvolutionParameterfvEXT = NULL;
#endif
#ifdef glConvolutionParameteriEXT
glConvolutionParameteriEXTFunc _glConvolutionParameteriEXT = NULL;
#endif
#ifdef glConvolutionParameterivEXT
glConvolutionParameterivEXTFunc _glConvolutionParameterivEXT = NULL;
#endif
#ifdef glCopyConvolutionFilter1DEXT
glCopyConvolutionFilter1DEXTFunc _glCopyConvolutionFilter1DEXT = NULL;
#endif
#ifdef glCopyConvolutionFilter2DEXT
glCopyConvolutionFilter2DEXTFunc _glCopyConvolutionFilter2DEXT = NULL;
#endif
#ifdef glGetConvolutionFilterEXT
glGetConvolutionFilterEXTFunc _glGetConvolutionFilterEXT = NULL;
#endif
#ifdef glGetConvolutionParameterfvEXT
glGetConvolutionParameterfvEXTFunc _glGetConvolutionParameterfvEXT = NULL;
#endif
#ifdef glGetConvolutionParameterivEXT
glGetConvolutionParameterivEXTFunc _glGetConvolutionParameterivEXT = NULL;
#endif
#ifdef glGetSeparableFilterEXT
glGetSeparableFilterEXTFunc _glGetSeparableFilterEXT = NULL;
#endif
#ifdef glSeparableFilter2DEXT
glSeparableFilter2DEXTFunc _glSeparableFilter2DEXT = NULL;
#endif
#ifdef glColorTableSGI
glColorTableSGIFunc _glColorTableSGI = NULL;
#endif
#ifdef glColorTableParameterfvSGI
glColorTableParameterfvSGIFunc _glColorTableParameterfvSGI = NULL;
#endif
#ifdef glColorTableParameterivSGI
glColorTableParameterivSGIFunc _glColorTableParameterivSGI = NULL;
#endif
#ifdef glCopyColorTableSGI
glCopyColorTableSGIFunc _glCopyColorTableSGI = NULL;
#endif
#ifdef glGetColorTableSGI
glGetColorTableSGIFunc _glGetColorTableSGI = NULL;
#endif
#ifdef glGetColorTableParameterfvSGI
glGetColorTableParameterfvSGIFunc _glGetColorTableParameterfvSGI = NULL;
#endif
#ifdef glGetColorTableParameterivSGI
glGetColorTableParameterivSGIFunc _glGetColorTableParameterivSGI = NULL;
#endif
#ifdef glPixelTexGenSGIX
glPixelTexGenSGIXFunc _glPixelTexGenSGIX = NULL;
#endif
#ifdef glPixelTexGenParameteriSGIS
glPixelTexGenParameteriSGISFunc _glPixelTexGenParameteriSGIS = NULL;
#endif
#ifdef glPixelTexGenParameterivSGIS
glPixelTexGenParameterivSGISFunc _glPixelTexGenParameterivSGIS = NULL;
#endif
#ifdef glPixelTexGenParameterfSGIS
glPixelTexGenParameterfSGISFunc _glPixelTexGenParameterfSGIS = NULL;
#endif
#ifdef glPixelTexGenParameterfvSGIS
glPixelTexGenParameterfvSGISFunc _glPixelTexGenParameterfvSGIS = NULL;
#endif
#ifdef glGetPixelTexGenParameterivSGIS
glGetPixelTexGenParameterivSGISFunc _glGetPixelTexGenParameterivSGIS = NULL;
#endif
#ifdef glGetPixelTexGenParameterfvSGIS
glGetPixelTexGenParameterfvSGISFunc _glGetPixelTexGenParameterfvSGIS = NULL;
#endif
#ifdef glTexImage4DSGIS
glTexImage4DSGISFunc _glTexImage4DSGIS = NULL;
#endif
#ifdef glTexSubImage4DSGIS
glTexSubImage4DSGISFunc _glTexSubImage4DSGIS = NULL;
#endif
#ifdef glAreTexturesResidentEXT
glAreTexturesResidentEXTFunc _glAreTexturesResidentEXT = NULL;
#endif
#ifdef glBindTextureEXT
glBindTextureEXTFunc _glBindTextureEXT = NULL;
#endif
#ifdef glDeleteTexturesEXT
glDeleteTexturesEXTFunc _glDeleteTexturesEXT = NULL;
#endif
#ifdef glGenTexturesEXT
glGenTexturesEXTFunc _glGenTexturesEXT = NULL;
#endif
#ifdef glIsTextureEXT
glIsTextureEXTFunc _glIsTextureEXT = NULL;
#endif
#ifdef glPrioritizeTexturesEXT
glPrioritizeTexturesEXTFunc _glPrioritizeTexturesEXT = NULL;
#endif
#ifdef glDetailTexFuncSGIS
glDetailTexFuncSGISFunc _glDetailTexFuncSGIS = NULL;
#endif
#ifdef glGetDetailTexFuncSGIS
glGetDetailTexFuncSGISFunc _glGetDetailTexFuncSGIS = NULL;
#endif
#ifdef glSharpenTexFuncSGIS
glSharpenTexFuncSGISFunc _glSharpenTexFuncSGIS = NULL;
#endif
#ifdef glGetSharpenTexFuncSGIS
glGetSharpenTexFuncSGISFunc _glGetSharpenTexFuncSGIS = NULL;
#endif
#ifdef glSampleMaskSGIS
glSampleMaskSGISFunc _glSampleMaskSGIS = NULL;
#endif
#ifdef glSamplePatternSGIS
glSamplePatternSGISFunc _glSamplePatternSGIS = NULL;
#endif
#ifdef glArrayElementEXT
glArrayElementEXTFunc _glArrayElementEXT = NULL;
#endif
#ifdef glColorPointerEXT
glColorPointerEXTFunc _glColorPointerEXT = NULL;
#endif
#ifdef glDrawArraysEXT
glDrawArraysEXTFunc _glDrawArraysEXT = NULL;
#endif
#ifdef glEdgeFlagPointerEXT
glEdgeFlagPointerEXTFunc _glEdgeFlagPointerEXT = NULL;
#endif
#ifdef glGetPointervEXT
glGetPointervEXTFunc _glGetPointervEXT = NULL;
#endif
#ifdef glIndexPointerEXT
glIndexPointerEXTFunc _glIndexPointerEXT = NULL;
#endif
#ifdef glNormalPointerEXT
glNormalPointerEXTFunc _glNormalPointerEXT = NULL;
#endif
#ifdef glTexCoordPointerEXT
glTexCoordPointerEXTFunc _glTexCoordPointerEXT = NULL;
#endif
#ifdef glVertexPointerEXT
glVertexPointerEXTFunc _glVertexPointerEXT = NULL;
#endif
#ifdef glBlendEquationEXT
glBlendEquationEXTFunc _glBlendEquationEXT = NULL;
#endif
#ifdef glSpriteParameterfSGIX
glSpriteParameterfSGIXFunc _glSpriteParameterfSGIX = NULL;
#endif
#ifdef glSpriteParameterfvSGIX
glSpriteParameterfvSGIXFunc _glSpriteParameterfvSGIX = NULL;
#endif
#ifdef glSpriteParameteriSGIX
glSpriteParameteriSGIXFunc _glSpriteParameteriSGIX = NULL;
#endif
#ifdef glSpriteParameterivSGIX
glSpriteParameterivSGIXFunc _glSpriteParameterivSGIX = NULL;
#endif
#ifdef glPointParameterfEXT
glPointParameterfEXTFunc _glPointParameterfEXT = NULL;
#endif
#ifdef glPointParameterfvEXT
glPointParameterfvEXTFunc _glPointParameterfvEXT = NULL;
#endif
#ifdef glPointParameterfSGIS
glPointParameterfSGISFunc _glPointParameterfSGIS = NULL;
#endif
#ifdef glPointParameterfvSGIS
glPointParameterfvSGISFunc _glPointParameterfvSGIS = NULL;
#endif
#ifdef glGetInstrumentsSGIX
glGetInstrumentsSGIXFunc _glGetInstrumentsSGIX = NULL;
#endif
#ifdef glInstrumentsBufferSGIX
glInstrumentsBufferSGIXFunc _glInstrumentsBufferSGIX = NULL;
#endif
#ifdef glPollInstrumentsSGIX
glPollInstrumentsSGIXFunc _glPollInstrumentsSGIX = NULL;
#endif
#ifdef glReadInstrumentsSGIX
glReadInstrumentsSGIXFunc _glReadInstrumentsSGIX = NULL;
#endif
#ifdef glStartInstrumentsSGIX
glStartInstrumentsSGIXFunc _glStartInstrumentsSGIX = NULL;
#endif
#ifdef glStopInstrumentsSGIX
glStopInstrumentsSGIXFunc _glStopInstrumentsSGIX = NULL;
#endif
#ifdef glFrameZoomSGIX
glFrameZoomSGIXFunc _glFrameZoomSGIX = NULL;
#endif
#ifdef glTagSampleBufferSGIX
glTagSampleBufferSGIXFunc _glTagSampleBufferSGIX = NULL;
#endif
#ifdef glDeformationMap3dSGIX
glDeformationMap3dSGIXFunc _glDeformationMap3dSGIX = NULL;
#endif
#ifdef glDeformationMap3fSGIX
glDeformationMap3fSGIXFunc _glDeformationMap3fSGIX = NULL;
#endif
#ifdef glDeformSGIX
glDeformSGIXFunc _glDeformSGIX = NULL;
#endif
#ifdef glLoadIdentityDeformationMapSGIX
glLoadIdentityDeformationMapSGIXFunc _glLoadIdentityDeformationMapSGIX = NULL;
#endif
#ifdef glReferencePlaneSGIX
glReferencePlaneSGIXFunc _glReferencePlaneSGIX = NULL;
#endif
#ifdef glFlushRasterSGIX
glFlushRasterSGIXFunc _glFlushRasterSGIX = NULL;
#endif
#ifdef glFogFuncSGIS
glFogFuncSGISFunc _glFogFuncSGIS = NULL;
#endif
#ifdef glGetFogFuncSGIS
glGetFogFuncSGISFunc _glGetFogFuncSGIS = NULL;
#endif
#ifdef glImageTransformParameteriHP
glImageTransformParameteriHPFunc _glImageTransformParameteriHP = NULL;
#endif
#ifdef glImageTransformParameterfHP
glImageTransformParameterfHPFunc _glImageTransformParameterfHP = NULL;
#endif
#ifdef glImageTransformParameterivHP
glImageTransformParameterivHPFunc _glImageTransformParameterivHP = NULL;
#endif
#ifdef glImageTransformParameterfvHP
glImageTransformParameterfvHPFunc _glImageTransformParameterfvHP = NULL;
#endif
#ifdef glGetImageTransformParameterivHP
glGetImageTransformParameterivHPFunc _glGetImageTransformParameterivHP = NULL;
#endif
#ifdef glGetImageTransformParameterfvHP
glGetImageTransformParameterfvHPFunc _glGetImageTransformParameterfvHP = NULL;
#endif
#ifdef glColorSubTableEXT
glColorSubTableEXTFunc _glColorSubTableEXT = NULL;
#endif
#ifdef glCopyColorSubTableEXT
glCopyColorSubTableEXTFunc _glCopyColorSubTableEXT = NULL;
#endif
#ifdef glHintPGI
glHintPGIFunc _glHintPGI = NULL;
#endif
#ifdef glColorTableEXT
glColorTableEXTFunc _glColorTableEXT = NULL;
#endif
#ifdef glGetColorTableEXT
glGetColorTableEXTFunc _glGetColorTableEXT = NULL;
#endif
#ifdef glGetColorTableParameterivEXT
glGetColorTableParameterivEXTFunc _glGetColorTableParameterivEXT = NULL;
#endif
#ifdef glGetColorTableParameterfvEXT
glGetColorTableParameterfvEXTFunc _glGetColorTableParameterfvEXT = NULL;
#endif
#ifdef glGetListParameterfvSGIX
glGetListParameterfvSGIXFunc _glGetListParameterfvSGIX = NULL;
#endif
#ifdef glGetListParameterivSGIX
glGetListParameterivSGIXFunc _glGetListParameterivSGIX = NULL;
#endif
#ifdef glListParameterfSGIX
glListParameterfSGIXFunc _glListParameterfSGIX = NULL;
#endif
#ifdef glListParameterfvSGIX
glListParameterfvSGIXFunc _glListParameterfvSGIX = NULL;
#endif
#ifdef glListParameteriSGIX
glListParameteriSGIXFunc _glListParameteriSGIX = NULL;
#endif
#ifdef glListParameterivSGIX
glListParameterivSGIXFunc _glListParameterivSGIX = NULL;
#endif
#ifdef glIndexMaterialEXT
glIndexMaterialEXTFunc _glIndexMaterialEXT = NULL;
#endif
#ifdef glIndexFuncEXT
glIndexFuncEXTFunc _glIndexFuncEXT = NULL;
#endif
#ifdef glLockArraysEXT
glLockArraysEXTFunc _glLockArraysEXT = NULL;
#endif
#ifdef glUnlockArraysEXT
glUnlockArraysEXTFunc _glUnlockArraysEXT = NULL;
#endif
#ifdef glCullParameterdvEXT
glCullParameterdvEXTFunc _glCullParameterdvEXT = NULL;
#endif
#ifdef glCullParameterfvEXT
glCullParameterfvEXTFunc _glCullParameterfvEXT = NULL;
#endif
#ifdef glFragmentColorMaterialSGIX
glFragmentColorMaterialSGIXFunc _glFragmentColorMaterialSGIX = NULL;
#endif
#ifdef glFragmentLightfSGIX
glFragmentLightfSGIXFunc _glFragmentLightfSGIX = NULL;
#endif
#ifdef glFragmentLightfvSGIX
glFragmentLightfvSGIXFunc _glFragmentLightfvSGIX = NULL;
#endif
#ifdef glFragmentLightiSGIX
glFragmentLightiSGIXFunc _glFragmentLightiSGIX = NULL;
#endif
#ifdef glFragmentLightivSGIX
glFragmentLightivSGIXFunc _glFragmentLightivSGIX = NULL;
#endif
#ifdef glFragmentLightModelfSGIX
glFragmentLightModelfSGIXFunc _glFragmentLightModelfSGIX = NULL;
#endif
#ifdef glFragmentLightModelfvSGIX
glFragmentLightModelfvSGIXFunc _glFragmentLightModelfvSGIX = NULL;
#endif
#ifdef glFragmentLightModeliSGIX
glFragmentLightModeliSGIXFunc _glFragmentLightModeliSGIX = NULL;
#endif
#ifdef glFragmentLightModelivSGIX
glFragmentLightModelivSGIXFunc _glFragmentLightModelivSGIX = NULL;
#endif
#ifdef glFragmentMaterialfSGIX
glFragmentMaterialfSGIXFunc _glFragmentMaterialfSGIX = NULL;
#endif
#ifdef glFragmentMaterialfvSGIX
glFragmentMaterialfvSGIXFunc _glFragmentMaterialfvSGIX = NULL;
#endif
#ifdef glFragmentMaterialiSGIX
glFragmentMaterialiSGIXFunc _glFragmentMaterialiSGIX = NULL;
#endif
#ifdef glFragmentMaterialivSGIX
glFragmentMaterialivSGIXFunc _glFragmentMaterialivSGIX = NULL;
#endif
#ifdef glGetFragmentLightfvSGIX
glGetFragmentLightfvSGIXFunc _glGetFragmentLightfvSGIX = NULL;
#endif
#ifdef glGetFragmentLightivSGIX
glGetFragmentLightivSGIXFunc _glGetFragmentLightivSGIX = NULL;
#endif
#ifdef glGetFragmentMaterialfvSGIX
glGetFragmentMaterialfvSGIXFunc _glGetFragmentMaterialfvSGIX = NULL;
#endif
#ifdef glGetFragmentMaterialivSGIX
glGetFragmentMaterialivSGIXFunc _glGetFragmentMaterialivSGIX = NULL;
#endif
#ifdef glLightEnviSGIX
glLightEnviSGIXFunc _glLightEnviSGIX = NULL;
#endif
#ifdef glDrawRangeElementsEXT
glDrawRangeElementsEXTFunc _glDrawRangeElementsEXT = NULL;
#endif
#ifdef glApplyTextureEXT
glApplyTextureEXTFunc _glApplyTextureEXT = NULL;
#endif
#ifdef glTextureLightEXT
glTextureLightEXTFunc _glTextureLightEXT = NULL;
#endif
#ifdef glTextureMaterialEXT
glTextureMaterialEXTFunc _glTextureMaterialEXT = NULL;
#endif
#ifdef glAsyncMarkerSGIX
glAsyncMarkerSGIXFunc _glAsyncMarkerSGIX = NULL;
#endif
#ifdef glFinishAsyncSGIX
glFinishAsyncSGIXFunc _glFinishAsyncSGIX = NULL;
#endif
#ifdef glPollAsyncSGIX
glPollAsyncSGIXFunc _glPollAsyncSGIX = NULL;
#endif
#ifdef glGenAsyncMarkersSGIX
glGenAsyncMarkersSGIXFunc _glGenAsyncMarkersSGIX = NULL;
#endif
#ifdef glDeleteAsyncMarkersSGIX
glDeleteAsyncMarkersSGIXFunc _glDeleteAsyncMarkersSGIX = NULL;
#endif
#ifdef glIsAsyncMarkerSGIX
glIsAsyncMarkerSGIXFunc _glIsAsyncMarkerSGIX = NULL;
#endif
#ifdef glVertexPointervINTEL
glVertexPointervINTELFunc _glVertexPointervINTEL = NULL;
#endif
#ifdef glNormalPointervINTEL
glNormalPointervINTELFunc _glNormalPointervINTEL = NULL;
#endif
#ifdef glColorPointervINTEL
glColorPointervINTELFunc _glColorPointervINTEL = NULL;
#endif
#ifdef glTexCoordPointervINTEL
glTexCoordPointervINTELFunc _glTexCoordPointervINTEL = NULL;
#endif
#ifdef glPixelTransformParameteriEXT
glPixelTransformParameteriEXTFunc _glPixelTransformParameteriEXT = NULL;
#endif
#ifdef glPixelTransformParameterfEXT
glPixelTransformParameterfEXTFunc _glPixelTransformParameterfEXT = NULL;
#endif
#ifdef glPixelTransformParameterivEXT
glPixelTransformParameterivEXTFunc _glPixelTransformParameterivEXT = NULL;
#endif
#ifdef glPixelTransformParameterfvEXT
glPixelTransformParameterfvEXTFunc _glPixelTransformParameterfvEXT = NULL;
#endif
#ifdef glGetPixelTransformParameterivEXT
glGetPixelTransformParameterivEXTFunc _glGetPixelTransformParameterivEXT = NULL;
#endif
#ifdef glGetPixelTransformParameterfvEXT
glGetPixelTransformParameterfvEXTFunc _glGetPixelTransformParameterfvEXT = NULL;
#endif
#ifdef glSecondaryColor3bEXT
glSecondaryColor3bEXTFunc _glSecondaryColor3bEXT = NULL;
#endif
#ifdef glSecondaryColor3bvEXT
glSecondaryColor3bvEXTFunc _glSecondaryColor3bvEXT = NULL;
#endif
#ifdef glSecondaryColor3dEXT
glSecondaryColor3dEXTFunc _glSecondaryColor3dEXT = NULL;
#endif
#ifdef glSecondaryColor3dvEXT
glSecondaryColor3dvEXTFunc _glSecondaryColor3dvEXT = NULL;
#endif
#ifdef glSecondaryColor3fEXT
glSecondaryColor3fEXTFunc _glSecondaryColor3fEXT = NULL;
#endif
#ifdef glSecondaryColor3fvEXT
glSecondaryColor3fvEXTFunc _glSecondaryColor3fvEXT = NULL;
#endif
#ifdef glSecondaryColor3iEXT
glSecondaryColor3iEXTFunc _glSecondaryColor3iEXT = NULL;
#endif
#ifdef glSecondaryColor3ivEXT
glSecondaryColor3ivEXTFunc _glSecondaryColor3ivEXT = NULL;
#endif
#ifdef glSecondaryColor3sEXT
glSecondaryColor3sEXTFunc _glSecondaryColor3sEXT = NULL;
#endif
#ifdef glSecondaryColor3svEXT
glSecondaryColor3svEXTFunc _glSecondaryColor3svEXT = NULL;
#endif
#ifdef glSecondaryColor3ubEXT
glSecondaryColor3ubEXTFunc _glSecondaryColor3ubEXT = NULL;
#endif
#ifdef glSecondaryColor3ubvEXT
glSecondaryColor3ubvEXTFunc _glSecondaryColor3ubvEXT = NULL;
#endif
#ifdef glSecondaryColor3uiEXT
glSecondaryColor3uiEXTFunc _glSecondaryColor3uiEXT = NULL;
#endif
#ifdef glSecondaryColor3uivEXT
glSecondaryColor3uivEXTFunc _glSecondaryColor3uivEXT = NULL;
#endif
#ifdef glSecondaryColor3usEXT
glSecondaryColor3usEXTFunc _glSecondaryColor3usEXT = NULL;
#endif
#ifdef glSecondaryColor3usvEXT
glSecondaryColor3usvEXTFunc _glSecondaryColor3usvEXT = NULL;
#endif
#ifdef glSecondaryColorPointerEXT
glSecondaryColorPointerEXTFunc _glSecondaryColorPointerEXT = NULL;
#endif
#ifdef glTextureNormalEXT
glTextureNormalEXTFunc _glTextureNormalEXT = NULL;
#endif
#ifdef glMultiDrawArraysEXT
glMultiDrawArraysEXTFunc _glMultiDrawArraysEXT = NULL;
#endif
#ifdef glMultiDrawElementsEXT
glMultiDrawElementsEXTFunc _glMultiDrawElementsEXT = NULL;
#endif
#ifdef glFogCoordfEXT
glFogCoordfEXTFunc _glFogCoordfEXT = NULL;
#endif
#ifdef glFogCoordfvEXT
glFogCoordfvEXTFunc _glFogCoordfvEXT = NULL;
#endif
#ifdef glFogCoorddEXT
glFogCoorddEXTFunc _glFogCoorddEXT = NULL;
#endif
#ifdef glFogCoorddvEXT
glFogCoorddvEXTFunc _glFogCoorddvEXT = NULL;
#endif
#ifdef glFogCoordPointerEXT
glFogCoordPointerEXTFunc _glFogCoordPointerEXT = NULL;
#endif
#ifdef glTangent3bEXT
glTangent3bEXTFunc _glTangent3bEXT = NULL;
#endif
#ifdef glTangent3bvEXT
glTangent3bvEXTFunc _glTangent3bvEXT = NULL;
#endif
#ifdef glTangent3dEXT
glTangent3dEXTFunc _glTangent3dEXT = NULL;
#endif
#ifdef glTangent3dvEXT
glTangent3dvEXTFunc _glTangent3dvEXT = NULL;
#endif
#ifdef glTangent3fEXT
glTangent3fEXTFunc _glTangent3fEXT = NULL;
#endif
#ifdef glTangent3fvEXT
glTangent3fvEXTFunc _glTangent3fvEXT = NULL;
#endif
#ifdef glTangent3iEXT
glTangent3iEXTFunc _glTangent3iEXT = NULL;
#endif
#ifdef glTangent3ivEXT
glTangent3ivEXTFunc _glTangent3ivEXT = NULL;
#endif
#ifdef glTangent3sEXT
glTangent3sEXTFunc _glTangent3sEXT = NULL;
#endif
#ifdef glTangent3svEXT
glTangent3svEXTFunc _glTangent3svEXT = NULL;
#endif
#ifdef glBinormal3bEXT
glBinormal3bEXTFunc _glBinormal3bEXT = NULL;
#endif
#ifdef glBinormal3bvEXT
glBinormal3bvEXTFunc _glBinormal3bvEXT = NULL;
#endif
#ifdef glBinormal3dEXT
glBinormal3dEXTFunc _glBinormal3dEXT = NULL;
#endif
#ifdef glBinormal3dvEXT
glBinormal3dvEXTFunc _glBinormal3dvEXT = NULL;
#endif
#ifdef glBinormal3fEXT
glBinormal3fEXTFunc _glBinormal3fEXT = NULL;
#endif
#ifdef glBinormal3fvEXT
glBinormal3fvEXTFunc _glBinormal3fvEXT = NULL;
#endif
#ifdef glBinormal3iEXT
glBinormal3iEXTFunc _glBinormal3iEXT = NULL;
#endif
#ifdef glBinormal3ivEXT
glBinormal3ivEXTFunc _glBinormal3ivEXT = NULL;
#endif
#ifdef glBinormal3sEXT
glBinormal3sEXTFunc _glBinormal3sEXT = NULL;
#endif
#ifdef glBinormal3svEXT
glBinormal3svEXTFunc _glBinormal3svEXT = NULL;
#endif
#ifdef glTangentPointerEXT
glTangentPointerEXTFunc _glTangentPointerEXT = NULL;
#endif
#ifdef glBinormalPointerEXT
glBinormalPointerEXTFunc _glBinormalPointerEXT = NULL;
#endif
#ifdef glFinishTextureSUNX
glFinishTextureSUNXFunc _glFinishTextureSUNX = NULL;
#endif
#ifdef glGlobalAlphaFactorbSUN
glGlobalAlphaFactorbSUNFunc _glGlobalAlphaFactorbSUN = NULL;
#endif
#ifdef glGlobalAlphaFactorsSUN
glGlobalAlphaFactorsSUNFunc _glGlobalAlphaFactorsSUN = NULL;
#endif
#ifdef glGlobalAlphaFactoriSUN
glGlobalAlphaFactoriSUNFunc _glGlobalAlphaFactoriSUN = NULL;
#endif
#ifdef glGlobalAlphaFactorfSUN
glGlobalAlphaFactorfSUNFunc _glGlobalAlphaFactorfSUN = NULL;
#endif
#ifdef glGlobalAlphaFactordSUN
glGlobalAlphaFactordSUNFunc _glGlobalAlphaFactordSUN = NULL;
#endif
#ifdef glGlobalAlphaFactorubSUN
glGlobalAlphaFactorubSUNFunc _glGlobalAlphaFactorubSUN = NULL;
#endif
#ifdef glGlobalAlphaFactorusSUN
glGlobalAlphaFactorusSUNFunc _glGlobalAlphaFactorusSUN = NULL;
#endif
#ifdef glGlobalAlphaFactoruiSUN
glGlobalAlphaFactoruiSUNFunc _glGlobalAlphaFactoruiSUN = NULL;
#endif
#ifdef glReplacementCodeuiSUN
glReplacementCodeuiSUNFunc _glReplacementCodeuiSUN = NULL;
#endif
#ifdef glReplacementCodeusSUN
glReplacementCodeusSUNFunc _glReplacementCodeusSUN = NULL;
#endif
#ifdef glReplacementCodeubSUN
glReplacementCodeubSUNFunc _glReplacementCodeubSUN = NULL;
#endif
#ifdef glReplacementCodeuivSUN
glReplacementCodeuivSUNFunc _glReplacementCodeuivSUN = NULL;
#endif
#ifdef glReplacementCodeusvSUN
glReplacementCodeusvSUNFunc _glReplacementCodeusvSUN = NULL;
#endif
#ifdef glReplacementCodeubvSUN
glReplacementCodeubvSUNFunc _glReplacementCodeubvSUN = NULL;
#endif
#ifdef glReplacementCodePointerSUN
glReplacementCodePointerSUNFunc _glReplacementCodePointerSUN = NULL;
#endif
#ifdef glColor4ubVertex2fSUN
glColor4ubVertex2fSUNFunc _glColor4ubVertex2fSUN = NULL;
#endif
#ifdef glColor4ubVertex2fvSUN
glColor4ubVertex2fvSUNFunc _glColor4ubVertex2fvSUN = NULL;
#endif
#ifdef glColor4ubVertex3fSUN
glColor4ubVertex3fSUNFunc _glColor4ubVertex3fSUN = NULL;
#endif
#ifdef glColor4ubVertex3fvSUN
glColor4ubVertex3fvSUNFunc _glColor4ubVertex3fvSUN = NULL;
#endif
#ifdef glColor3fVertex3fSUN
glColor3fVertex3fSUNFunc _glColor3fVertex3fSUN = NULL;
#endif
#ifdef glColor3fVertex3fvSUN
glColor3fVertex3fvSUNFunc _glColor3fVertex3fvSUN = NULL;
#endif
#ifdef glNormal3fVertex3fSUN
glNormal3fVertex3fSUNFunc _glNormal3fVertex3fSUN = NULL;
#endif
#ifdef glNormal3fVertex3fvSUN
glNormal3fVertex3fvSUNFunc _glNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glColor4fNormal3fVertex3fSUN
glColor4fNormal3fVertex3fSUNFunc _glColor4fNormal3fVertex3fSUN = NULL;
#endif
#ifdef glColor4fNormal3fVertex3fvSUN
glColor4fNormal3fVertex3fvSUNFunc _glColor4fNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glTexCoord2fVertex3fSUN
glTexCoord2fVertex3fSUNFunc _glTexCoord2fVertex3fSUN = NULL;
#endif
#ifdef glTexCoord2fVertex3fvSUN
glTexCoord2fVertex3fvSUNFunc _glTexCoord2fVertex3fvSUN = NULL;
#endif
#ifdef glTexCoord4fVertex4fSUN
glTexCoord4fVertex4fSUNFunc _glTexCoord4fVertex4fSUN = NULL;
#endif
#ifdef glTexCoord4fVertex4fvSUN
glTexCoord4fVertex4fvSUNFunc _glTexCoord4fVertex4fvSUN = NULL;
#endif
#ifdef glTexCoord2fColor4ubVertex3fSUN
glTexCoord2fColor4ubVertex3fSUNFunc _glTexCoord2fColor4ubVertex3fSUN = NULL;
#endif
#ifdef glTexCoord2fColor4ubVertex3fvSUN
glTexCoord2fColor4ubVertex3fvSUNFunc _glTexCoord2fColor4ubVertex3fvSUN = NULL;
#endif
#ifdef glTexCoord2fColor3fVertex3fSUN
glTexCoord2fColor3fVertex3fSUNFunc _glTexCoord2fColor3fVertex3fSUN = NULL;
#endif
#ifdef glTexCoord2fColor3fVertex3fvSUN
glTexCoord2fColor3fVertex3fvSUNFunc _glTexCoord2fColor3fVertex3fvSUN = NULL;
#endif
#ifdef glTexCoord2fNormal3fVertex3fSUN
glTexCoord2fNormal3fVertex3fSUNFunc _glTexCoord2fNormal3fVertex3fSUN = NULL;
#endif
#ifdef glTexCoord2fNormal3fVertex3fvSUN
glTexCoord2fNormal3fVertex3fvSUNFunc _glTexCoord2fNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glTexCoord2fColor4fNormal3fVertex3fSUN
glTexCoord2fColor4fNormal3fVertex3fSUNFunc _glTexCoord2fColor4fNormal3fVertex3fSUN = NULL;
#endif
#ifdef glTexCoord2fColor4fNormal3fVertex3fvSUN
glTexCoord2fColor4fNormal3fVertex3fvSUNFunc _glTexCoord2fColor4fNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glTexCoord4fColor4fNormal3fVertex4fSUN
glTexCoord4fColor4fNormal3fVertex4fSUNFunc _glTexCoord4fColor4fNormal3fVertex4fSUN = NULL;
#endif
#ifdef glTexCoord4fColor4fNormal3fVertex4fvSUN
glTexCoord4fColor4fNormal3fVertex4fvSUNFunc _glTexCoord4fColor4fNormal3fVertex4fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiVertex3fSUN
glReplacementCodeuiVertex3fSUNFunc _glReplacementCodeuiVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiVertex3fvSUN
glReplacementCodeuiVertex3fvSUNFunc _glReplacementCodeuiVertex3fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiColor4ubVertex3fSUN
glReplacementCodeuiColor4ubVertex3fSUNFunc _glReplacementCodeuiColor4ubVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiColor4ubVertex3fvSUN
glReplacementCodeuiColor4ubVertex3fvSUNFunc _glReplacementCodeuiColor4ubVertex3fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiColor3fVertex3fSUN
glReplacementCodeuiColor3fVertex3fSUNFunc _glReplacementCodeuiColor3fVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiColor3fVertex3fvSUN
glReplacementCodeuiColor3fVertex3fvSUNFunc _glReplacementCodeuiColor3fVertex3fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiNormal3fVertex3fSUN
glReplacementCodeuiNormal3fVertex3fSUNFunc _glReplacementCodeuiNormal3fVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiNormal3fVertex3fvSUN
glReplacementCodeuiNormal3fVertex3fvSUNFunc _glReplacementCodeuiNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiColor4fNormal3fVertex3fSUN
glReplacementCodeuiColor4fNormal3fVertex3fSUNFunc _glReplacementCodeuiColor4fNormal3fVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiColor4fNormal3fVertex3fvSUN
glReplacementCodeuiColor4fNormal3fVertex3fvSUNFunc _glReplacementCodeuiColor4fNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiTexCoord2fVertex3fSUN
glReplacementCodeuiTexCoord2fVertex3fSUNFunc _glReplacementCodeuiTexCoord2fVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiTexCoord2fVertex3fvSUN
glReplacementCodeuiTexCoord2fVertex3fvSUNFunc _glReplacementCodeuiTexCoord2fVertex3fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN
glReplacementCodeuiTexCoord2fNormal3fVertex3fSUNFunc _glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN
glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUNFunc _glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN
glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUNFunc _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN = NULL;
#endif
#ifdef glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN
glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUNFunc _glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN = NULL;
#endif
#ifdef glBlendFuncSeparateEXT
glBlendFuncSeparateEXTFunc _glBlendFuncSeparateEXT = NULL;
#endif
#ifdef glBlendFuncSeparateINGR
glBlendFuncSeparateINGRFunc _glBlendFuncSeparateINGR = NULL;
#endif
#ifdef glVertexWeightfEXT
glVertexWeightfEXTFunc _glVertexWeightfEXT = NULL;
#endif
#ifdef glVertexWeightfvEXT
glVertexWeightfvEXTFunc _glVertexWeightfvEXT = NULL;
#endif
#ifdef glVertexWeightPointerEXT
glVertexWeightPointerEXTFunc _glVertexWeightPointerEXT = NULL;
#endif
#ifdef glFlushVertexArrayRangeNV
glFlushVertexArrayRangeNVFunc _glFlushVertexArrayRangeNV = NULL;
#endif
#ifdef glVertexArrayRangeNV
glVertexArrayRangeNVFunc _glVertexArrayRangeNV = NULL;
#endif
#ifdef glCombinerParameterfvNV
glCombinerParameterfvNVFunc _glCombinerParameterfvNV = NULL;
#endif
#ifdef glCombinerParameterfNV
glCombinerParameterfNVFunc _glCombinerParameterfNV = NULL;
#endif
#ifdef glCombinerParameterivNV
glCombinerParameterivNVFunc _glCombinerParameterivNV = NULL;
#endif
#ifdef glCombinerParameteriNV
glCombinerParameteriNVFunc _glCombinerParameteriNV = NULL;
#endif
#ifdef glCombinerInputNV
glCombinerInputNVFunc _glCombinerInputNV = NULL;
#endif
#ifdef glCombinerOutputNV
glCombinerOutputNVFunc _glCombinerOutputNV = NULL;
#endif
#ifdef glFinalCombinerInputNV
glFinalCombinerInputNVFunc _glFinalCombinerInputNV = NULL;
#endif
#ifdef glGetCombinerInputParameterfvNV
glGetCombinerInputParameterfvNVFunc _glGetCombinerInputParameterfvNV = NULL;
#endif
#ifdef glGetCombinerInputParameterivNV
glGetCombinerInputParameterivNVFunc _glGetCombinerInputParameterivNV = NULL;
#endif
#ifdef glGetCombinerOutputParameterfvNV
glGetCombinerOutputParameterfvNVFunc _glGetCombinerOutputParameterfvNV = NULL;
#endif
#ifdef glGetCombinerOutputParameterivNV
glGetCombinerOutputParameterivNVFunc _glGetCombinerOutputParameterivNV = NULL;
#endif
#ifdef glGetFinalCombinerInputParameterfvNV
glGetFinalCombinerInputParameterfvNVFunc _glGetFinalCombinerInputParameterfvNV = NULL;
#endif
#ifdef glGetFinalCombinerInputParameterivNV
glGetFinalCombinerInputParameterivNVFunc _glGetFinalCombinerInputParameterivNV = NULL;
#endif
#ifdef glResizeBuffersMESA
glResizeBuffersMESAFunc _glResizeBuffersMESA = NULL;
#endif
#ifdef glWindowPos2dMESA
glWindowPos2dMESAFunc _glWindowPos2dMESA = NULL;
#endif
#ifdef glWindowPos2dvMESA
glWindowPos2dvMESAFunc _glWindowPos2dvMESA = NULL;
#endif
#ifdef glWindowPos2fMESA
glWindowPos2fMESAFunc _glWindowPos2fMESA = NULL;
#endif
#ifdef glWindowPos2fvMESA
glWindowPos2fvMESAFunc _glWindowPos2fvMESA = NULL;
#endif
#ifdef glWindowPos2iMESA
glWindowPos2iMESAFunc _glWindowPos2iMESA = NULL;
#endif
#ifdef glWindowPos2ivMESA
glWindowPos2ivMESAFunc _glWindowPos2ivMESA = NULL;
#endif
#ifdef glWindowPos2sMESA
glWindowPos2sMESAFunc _glWindowPos2sMESA = NULL;
#endif
#ifdef glWindowPos2svMESA
glWindowPos2svMESAFunc _glWindowPos2svMESA = NULL;
#endif
#ifdef glWindowPos3dMESA
glWindowPos3dMESAFunc _glWindowPos3dMESA = NULL;
#endif
#ifdef glWindowPos3dvMESA
glWindowPos3dvMESAFunc _glWindowPos3dvMESA = NULL;
#endif
#ifdef glWindowPos3fMESA
glWindowPos3fMESAFunc _glWindowPos3fMESA = NULL;
#endif
#ifdef glWindowPos3fvMESA
glWindowPos3fvMESAFunc _glWindowPos3fvMESA = NULL;
#endif
#ifdef glWindowPos3iMESA
glWindowPos3iMESAFunc _glWindowPos3iMESA = NULL;
#endif
#ifdef glWindowPos3ivMESA
glWindowPos3ivMESAFunc _glWindowPos3ivMESA = NULL;
#endif
#ifdef glWindowPos3sMESA
glWindowPos3sMESAFunc _glWindowPos3sMESA = NULL;
#endif
#ifdef glWindowPos3svMESA
glWindowPos3svMESAFunc _glWindowPos3svMESA = NULL;
#endif
#ifdef glWindowPos4dMESA
glWindowPos4dMESAFunc _glWindowPos4dMESA = NULL;
#endif
#ifdef glWindowPos4dvMESA
glWindowPos4dvMESAFunc _glWindowPos4dvMESA = NULL;
#endif
#ifdef glWindowPos4fMESA
glWindowPos4fMESAFunc _glWindowPos4fMESA = NULL;
#endif
#ifdef glWindowPos4fvMESA
glWindowPos4fvMESAFunc _glWindowPos4fvMESA = NULL;
#endif
#ifdef glWindowPos4iMESA
glWindowPos4iMESAFunc _glWindowPos4iMESA = NULL;
#endif
#ifdef glWindowPos4ivMESA
glWindowPos4ivMESAFunc _glWindowPos4ivMESA = NULL;
#endif
#ifdef glWindowPos4sMESA
glWindowPos4sMESAFunc _glWindowPos4sMESA = NULL;
#endif
#ifdef glWindowPos4svMESA
glWindowPos4svMESAFunc _glWindowPos4svMESA = NULL;
#endif
#ifdef glMultiModeDrawArraysIBM
glMultiModeDrawArraysIBMFunc _glMultiModeDrawArraysIBM = NULL;
#endif
#ifdef glMultiModeDrawElementsIBM
glMultiModeDrawElementsIBMFunc _glMultiModeDrawElementsIBM = NULL;
#endif
#ifdef glColorPointerListIBM
glColorPointerListIBMFunc _glColorPointerListIBM = NULL;
#endif
#ifdef glSecondaryColorPointerListIBM
glSecondaryColorPointerListIBMFunc _glSecondaryColorPointerListIBM = NULL;
#endif
#ifdef glEdgeFlagPointerListIBM
glEdgeFlagPointerListIBMFunc _glEdgeFlagPointerListIBM = NULL;
#endif
#ifdef glFogCoordPointerListIBM
glFogCoordPointerListIBMFunc _glFogCoordPointerListIBM = NULL;
#endif
#ifdef glIndexPointerListIBM
glIndexPointerListIBMFunc _glIndexPointerListIBM = NULL;
#endif
#ifdef glNormalPointerListIBM
glNormalPointerListIBMFunc _glNormalPointerListIBM = NULL;
#endif
#ifdef glTexCoordPointerListIBM
glTexCoordPointerListIBMFunc _glTexCoordPointerListIBM = NULL;
#endif
#ifdef glVertexPointerListIBM
glVertexPointerListIBMFunc _glVertexPointerListIBM = NULL;
#endif
#ifdef glTbufferMask3DFX
glTbufferMask3DFXFunc _glTbufferMask3DFX = NULL;
#endif
#ifdef glSampleMaskEXT
glSampleMaskEXTFunc _glSampleMaskEXT = NULL;
#endif
#ifdef glSamplePatternEXT
glSamplePatternEXTFunc _glSamplePatternEXT = NULL;
#endif
#ifdef glTextureColorMaskSGIS
glTextureColorMaskSGISFunc _glTextureColorMaskSGIS = NULL;
#endif
#ifdef glIglooInterfaceSGIX
glIglooInterfaceSGIXFunc _glIglooInterfaceSGIX = NULL;
#endif
#ifdef glDeleteFencesNV
glDeleteFencesNVFunc _glDeleteFencesNV = NULL;
#endif
#ifdef glGenFencesNV
glGenFencesNVFunc _glGenFencesNV = NULL;
#endif
#ifdef glIsFenceNV
glIsFenceNVFunc _glIsFenceNV = NULL;
#endif
#ifdef glTestFenceNV
glTestFenceNVFunc _glTestFenceNV = NULL;
#endif
#ifdef glGetFenceivNV
glGetFenceivNVFunc _glGetFenceivNV = NULL;
#endif
#ifdef glFinishFenceNV
glFinishFenceNVFunc _glFinishFenceNV = NULL;
#endif
#ifdef glSetFenceNV
glSetFenceNVFunc _glSetFenceNV = NULL;
#endif
#ifdef glMapControlPointsNV
glMapControlPointsNVFunc _glMapControlPointsNV = NULL;
#endif
#ifdef glMapParameterivNV
glMapParameterivNVFunc _glMapParameterivNV = NULL;
#endif
#ifdef glMapParameterfvNV
glMapParameterfvNVFunc _glMapParameterfvNV = NULL;
#endif
#ifdef glGetMapControlPointsNV
glGetMapControlPointsNVFunc _glGetMapControlPointsNV = NULL;
#endif
#ifdef glGetMapParameterivNV
glGetMapParameterivNVFunc _glGetMapParameterivNV = NULL;
#endif
#ifdef glGetMapParameterfvNV
glGetMapParameterfvNVFunc _glGetMapParameterfvNV = NULL;
#endif
#ifdef glGetMapAttribParameterivNV
glGetMapAttribParameterivNVFunc _glGetMapAttribParameterivNV = NULL;
#endif
#ifdef glGetMapAttribParameterfvNV
glGetMapAttribParameterfvNVFunc _glGetMapAttribParameterfvNV = NULL;
#endif
#ifdef glEvalMapsNV
glEvalMapsNVFunc _glEvalMapsNV = NULL;
#endif
#ifdef glCombinerStageParameterfvNV
glCombinerStageParameterfvNVFunc _glCombinerStageParameterfvNV = NULL;
#endif
#ifdef glGetCombinerStageParameterfvNV
glGetCombinerStageParameterfvNVFunc _glGetCombinerStageParameterfvNV = NULL;
#endif
#ifdef glAreProgramsResidentNV
glAreProgramsResidentNVFunc _glAreProgramsResidentNV = NULL;
#endif
#ifdef glBindProgramNV
glBindProgramNVFunc _glBindProgramNV = NULL;
#endif
#ifdef glDeleteProgramsNV
glDeleteProgramsNVFunc _glDeleteProgramsNV = NULL;
#endif
#ifdef glExecuteProgramNV
glExecuteProgramNVFunc _glExecuteProgramNV = NULL;
#endif
#ifdef glGenProgramsNV
glGenProgramsNVFunc _glGenProgramsNV = NULL;
#endif
#ifdef glGetProgramParameterdvNV
glGetProgramParameterdvNVFunc _glGetProgramParameterdvNV = NULL;
#endif
#ifdef glGetProgramParameterfvNV
glGetProgramParameterfvNVFunc _glGetProgramParameterfvNV = NULL;
#endif
#ifdef glGetProgramivNV
glGetProgramivNVFunc _glGetProgramivNV = NULL;
#endif
#ifdef glGetProgramStringNV
glGetProgramStringNVFunc _glGetProgramStringNV = NULL;
#endif
#ifdef glGetTrackMatrixivNV
glGetTrackMatrixivNVFunc _glGetTrackMatrixivNV = NULL;
#endif
#ifdef glGetVertexAttribdvNV
glGetVertexAttribdvNVFunc _glGetVertexAttribdvNV = NULL;
#endif
#ifdef glGetVertexAttribfvNV
glGetVertexAttribfvNVFunc _glGetVertexAttribfvNV = NULL;
#endif
#ifdef glGetVertexAttribivNV
glGetVertexAttribivNVFunc _glGetVertexAttribivNV = NULL;
#endif
#ifdef glGetVertexAttribPointervNV
glGetVertexAttribPointervNVFunc _glGetVertexAttribPointervNV = NULL;
#endif
#ifdef glIsProgramNV
glIsProgramNVFunc _glIsProgramNV = NULL;
#endif
#ifdef glLoadProgramNV
glLoadProgramNVFunc _glLoadProgramNV = NULL;
#endif
#ifdef glProgramParameter4dNV
glProgramParameter4dNVFunc _glProgramParameter4dNV = NULL;
#endif
#ifdef glProgramParameter4dvNV
glProgramParameter4dvNVFunc _glProgramParameter4dvNV = NULL;
#endif
#ifdef glProgramParameter4fNV
glProgramParameter4fNVFunc _glProgramParameter4fNV = NULL;
#endif
#ifdef glProgramParameter4fvNV
glProgramParameter4fvNVFunc _glProgramParameter4fvNV = NULL;
#endif
#ifdef glProgramParameters4dvNV
glProgramParameters4dvNVFunc _glProgramParameters4dvNV = NULL;
#endif
#ifdef glProgramParameters4fvNV
glProgramParameters4fvNVFunc _glProgramParameters4fvNV = NULL;
#endif
#ifdef glRequestResidentProgramsNV
glRequestResidentProgramsNVFunc _glRequestResidentProgramsNV = NULL;
#endif
#ifdef glTrackMatrixNV
glTrackMatrixNVFunc _glTrackMatrixNV = NULL;
#endif
#ifdef glVertexAttribPointerNV
glVertexAttribPointerNVFunc _glVertexAttribPointerNV = NULL;
#endif
#ifdef glVertexAttrib1dNV
glVertexAttrib1dNVFunc _glVertexAttrib1dNV = NULL;
#endif
#ifdef glVertexAttrib1dvNV
glVertexAttrib1dvNVFunc _glVertexAttrib1dvNV = NULL;
#endif
#ifdef glVertexAttrib1fNV
glVertexAttrib1fNVFunc _glVertexAttrib1fNV = NULL;
#endif
#ifdef glVertexAttrib1fvNV
glVertexAttrib1fvNVFunc _glVertexAttrib1fvNV = NULL;
#endif
#ifdef glVertexAttrib1sNV
glVertexAttrib1sNVFunc _glVertexAttrib1sNV = NULL;
#endif
#ifdef glVertexAttrib1svNV
glVertexAttrib1svNVFunc _glVertexAttrib1svNV = NULL;
#endif
#ifdef glVertexAttrib2dNV
glVertexAttrib2dNVFunc _glVertexAttrib2dNV = NULL;
#endif
#ifdef glVertexAttrib2dvNV
glVertexAttrib2dvNVFunc _glVertexAttrib2dvNV = NULL;
#endif
#ifdef glVertexAttrib2fNV
glVertexAttrib2fNVFunc _glVertexAttrib2fNV = NULL;
#endif
#ifdef glVertexAttrib2fvNV
glVertexAttrib2fvNVFunc _glVertexAttrib2fvNV = NULL;
#endif
#ifdef glVertexAttrib2sNV
glVertexAttrib2sNVFunc _glVertexAttrib2sNV = NULL;
#endif
#ifdef glVertexAttrib2svNV
glVertexAttrib2svNVFunc _glVertexAttrib2svNV = NULL;
#endif
#ifdef glVertexAttrib3dNV
glVertexAttrib3dNVFunc _glVertexAttrib3dNV = NULL;
#endif
#ifdef glVertexAttrib3dvNV
glVertexAttrib3dvNVFunc _glVertexAttrib3dvNV = NULL;
#endif
#ifdef glVertexAttrib3fNV
glVertexAttrib3fNVFunc _glVertexAttrib3fNV = NULL;
#endif
#ifdef glVertexAttrib3fvNV
glVertexAttrib3fvNVFunc _glVertexAttrib3fvNV = NULL;
#endif
#ifdef glVertexAttrib3sNV
glVertexAttrib3sNVFunc _glVertexAttrib3sNV = NULL;
#endif
#ifdef glVertexAttrib3svNV
glVertexAttrib3svNVFunc _glVertexAttrib3svNV = NULL;
#endif
#ifdef glVertexAttrib4dNV
glVertexAttrib4dNVFunc _glVertexAttrib4dNV = NULL;
#endif
#ifdef glVertexAttrib4dvNV
glVertexAttrib4dvNVFunc _glVertexAttrib4dvNV = NULL;
#endif
#ifdef glVertexAttrib4fNV
glVertexAttrib4fNVFunc _glVertexAttrib4fNV = NULL;
#endif
#ifdef glVertexAttrib4fvNV
glVertexAttrib4fvNVFunc _glVertexAttrib4fvNV = NULL;
#endif
#ifdef glVertexAttrib4sNV
glVertexAttrib4sNVFunc _glVertexAttrib4sNV = NULL;
#endif
#ifdef glVertexAttrib4svNV
glVertexAttrib4svNVFunc _glVertexAttrib4svNV = NULL;
#endif
#ifdef glVertexAttrib4ubNV
glVertexAttrib4ubNVFunc _glVertexAttrib4ubNV = NULL;
#endif
#ifdef glVertexAttrib4ubvNV
glVertexAttrib4ubvNVFunc _glVertexAttrib4ubvNV = NULL;
#endif
#ifdef glVertexAttribs1dvNV
glVertexAttribs1dvNVFunc _glVertexAttribs1dvNV = NULL;
#endif
#ifdef glVertexAttribs1fvNV
glVertexAttribs1fvNVFunc _glVertexAttribs1fvNV = NULL;
#endif
#ifdef glVertexAttribs1svNV
glVertexAttribs1svNVFunc _glVertexAttribs1svNV = NULL;
#endif
#ifdef glVertexAttribs2dvNV
glVertexAttribs2dvNVFunc _glVertexAttribs2dvNV = NULL;
#endif
#ifdef glVertexAttribs2fvNV
glVertexAttribs2fvNVFunc _glVertexAttribs2fvNV = NULL;
#endif
#ifdef glVertexAttribs2svNV
glVertexAttribs2svNVFunc _glVertexAttribs2svNV = NULL;
#endif
#ifdef glVertexAttribs3dvNV
glVertexAttribs3dvNVFunc _glVertexAttribs3dvNV = NULL;
#endif
#ifdef glVertexAttribs3fvNV
glVertexAttribs3fvNVFunc _glVertexAttribs3fvNV = NULL;
#endif
#ifdef glVertexAttribs3svNV
glVertexAttribs3svNVFunc _glVertexAttribs3svNV = NULL;
#endif
#ifdef glVertexAttribs4dvNV
glVertexAttribs4dvNVFunc _glVertexAttribs4dvNV = NULL;
#endif
#ifdef glVertexAttribs4fvNV
glVertexAttribs4fvNVFunc _glVertexAttribs4fvNV = NULL;
#endif
#ifdef glVertexAttribs4svNV
glVertexAttribs4svNVFunc _glVertexAttribs4svNV = NULL;
#endif
#ifdef glVertexAttribs4ubvNV
glVertexAttribs4ubvNVFunc _glVertexAttribs4ubvNV = NULL;
#endif
#ifdef glTexBumpParameterivATI
glTexBumpParameterivATIFunc _glTexBumpParameterivATI = NULL;
#endif
#ifdef glTexBumpParameterfvATI
glTexBumpParameterfvATIFunc _glTexBumpParameterfvATI = NULL;
#endif
#ifdef glGetTexBumpParameterivATI
glGetTexBumpParameterivATIFunc _glGetTexBumpParameterivATI = NULL;
#endif
#ifdef glGetTexBumpParameterfvATI
glGetTexBumpParameterfvATIFunc _glGetTexBumpParameterfvATI = NULL;
#endif
#ifdef glGenFragmentShadersATI
glGenFragmentShadersATIFunc _glGenFragmentShadersATI = NULL;
#endif
#ifdef glBindFragmentShaderATI
glBindFragmentShaderATIFunc _glBindFragmentShaderATI = NULL;
#endif
#ifdef glDeleteFragmentShaderATI
glDeleteFragmentShaderATIFunc _glDeleteFragmentShaderATI = NULL;
#endif
#ifdef glBeginFragmentShaderATI
glBeginFragmentShaderATIFunc _glBeginFragmentShaderATI = NULL;
#endif
#ifdef glEndFragmentShaderATI
glEndFragmentShaderATIFunc _glEndFragmentShaderATI = NULL;
#endif
#ifdef glPassTexCoordATI
glPassTexCoordATIFunc _glPassTexCoordATI = NULL;
#endif
#ifdef glSampleMapATI
glSampleMapATIFunc _glSampleMapATI = NULL;
#endif
#ifdef glColorFragmentOp1ATI
glColorFragmentOp1ATIFunc _glColorFragmentOp1ATI = NULL;
#endif
#ifdef glColorFragmentOp2ATI
glColorFragmentOp2ATIFunc _glColorFragmentOp2ATI = NULL;
#endif
#ifdef glColorFragmentOp3ATI
glColorFragmentOp3ATIFunc _glColorFragmentOp3ATI = NULL;
#endif
#ifdef glAlphaFragmentOp1ATI
glAlphaFragmentOp1ATIFunc _glAlphaFragmentOp1ATI = NULL;
#endif
#ifdef glAlphaFragmentOp2ATI
glAlphaFragmentOp2ATIFunc _glAlphaFragmentOp2ATI = NULL;
#endif
#ifdef glAlphaFragmentOp3ATI
glAlphaFragmentOp3ATIFunc _glAlphaFragmentOp3ATI = NULL;
#endif
#ifdef glSetFragmentShaderConstantATI
glSetFragmentShaderConstantATIFunc _glSetFragmentShaderConstantATI = NULL;
#endif
#ifdef glPNTrianglesiATI
glPNTrianglesiATIFunc _glPNTrianglesiATI = NULL;
#endif
#ifdef glPNTrianglesfATI
glPNTrianglesfATIFunc _glPNTrianglesfATI = NULL;
#endif
#ifdef glNewObjectBufferATI
glNewObjectBufferATIFunc _glNewObjectBufferATI = NULL;
#endif
#ifdef glIsObjectBufferATI
glIsObjectBufferATIFunc _glIsObjectBufferATI = NULL;
#endif
#ifdef glUpdateObjectBufferATI
glUpdateObjectBufferATIFunc _glUpdateObjectBufferATI = NULL;
#endif
#ifdef glGetObjectBufferfvATI
glGetObjectBufferfvATIFunc _glGetObjectBufferfvATI = NULL;
#endif
#ifdef glGetObjectBufferivATI
glGetObjectBufferivATIFunc _glGetObjectBufferivATI = NULL;
#endif
#ifdef glFreeObjectBufferATI
glFreeObjectBufferATIFunc _glFreeObjectBufferATI = NULL;
#endif
#ifdef glArrayObjectATI
glArrayObjectATIFunc _glArrayObjectATI = NULL;
#endif
#ifdef glGetArrayObjectfvATI
glGetArrayObjectfvATIFunc _glGetArrayObjectfvATI = NULL;
#endif
#ifdef glGetArrayObjectivATI
glGetArrayObjectivATIFunc _glGetArrayObjectivATI = NULL;
#endif
#ifdef glVariantArrayObjectATI
glVariantArrayObjectATIFunc _glVariantArrayObjectATI = NULL;
#endif
#ifdef glGetVariantArrayObjectfvATI
glGetVariantArrayObjectfvATIFunc _glGetVariantArrayObjectfvATI = NULL;
#endif
#ifdef glGetVariantArrayObjectivATI
glGetVariantArrayObjectivATIFunc _glGetVariantArrayObjectivATI = NULL;
#endif
#ifdef glBeginVertexShaderEXT
glBeginVertexShaderEXTFunc _glBeginVertexShaderEXT = NULL;
#endif
#ifdef glEndVertexShaderEXT
glEndVertexShaderEXTFunc _glEndVertexShaderEXT = NULL;
#endif
#ifdef glBindVertexShaderEXT
glBindVertexShaderEXTFunc _glBindVertexShaderEXT = NULL;
#endif
#ifdef glGenVertexShadersEXT
glGenVertexShadersEXTFunc _glGenVertexShadersEXT = NULL;
#endif
#ifdef glDeleteVertexShaderEXT
glDeleteVertexShaderEXTFunc _glDeleteVertexShaderEXT = NULL;
#endif
#ifdef glShaderOp1EXT
glShaderOp1EXTFunc _glShaderOp1EXT = NULL;
#endif
#ifdef glShaderOp2EXT
glShaderOp2EXTFunc _glShaderOp2EXT = NULL;
#endif
#ifdef glShaderOp3EXT
glShaderOp3EXTFunc _glShaderOp3EXT = NULL;
#endif
#ifdef glSwizzleEXT
glSwizzleEXTFunc _glSwizzleEXT = NULL;
#endif
#ifdef glWriteMaskEXT
glWriteMaskEXTFunc _glWriteMaskEXT = NULL;
#endif
#ifdef glInsertComponentEXT
glInsertComponentEXTFunc _glInsertComponentEXT = NULL;
#endif
#ifdef glExtractComponentEXT
glExtractComponentEXTFunc _glExtractComponentEXT = NULL;
#endif
#ifdef glGenSymbolsEXT
glGenSymbolsEXTFunc _glGenSymbolsEXT = NULL;
#endif
#ifdef glSetInvariantEXT
glSetInvariantEXTFunc _glSetInvariantEXT = NULL;
#endif
#ifdef glSetLocalConstantEXT
glSetLocalConstantEXTFunc _glSetLocalConstantEXT = NULL;
#endif
#ifdef glVariantbvEXT
glVariantbvEXTFunc _glVariantbvEXT = NULL;
#endif
#ifdef glVariantsvEXT
glVariantsvEXTFunc _glVariantsvEXT = NULL;
#endif
#ifdef glVariantivEXT
glVariantivEXTFunc _glVariantivEXT = NULL;
#endif
#ifdef glVariantfvEXT
glVariantfvEXTFunc _glVariantfvEXT = NULL;
#endif
#ifdef glVariantdvEXT
glVariantdvEXTFunc _glVariantdvEXT = NULL;
#endif
#ifdef glVariantubvEXT
glVariantubvEXTFunc _glVariantubvEXT = NULL;
#endif
#ifdef glVariantusvEXT
glVariantusvEXTFunc _glVariantusvEXT = NULL;
#endif
#ifdef glVariantuivEXT
glVariantuivEXTFunc _glVariantuivEXT = NULL;
#endif
#ifdef glVariantPointerEXT
glVariantPointerEXTFunc _glVariantPointerEXT = NULL;
#endif
#ifdef glEnableVariantClientStateEXT
glEnableVariantClientStateEXTFunc _glEnableVariantClientStateEXT = NULL;
#endif
#ifdef glDisableVariantClientStateEXT
glDisableVariantClientStateEXTFunc _glDisableVariantClientStateEXT = NULL;
#endif
#ifdef glBindLightParameterEXT
glBindLightParameterEXTFunc _glBindLightParameterEXT = NULL;
#endif
#ifdef glBindMaterialParameterEXT
glBindMaterialParameterEXTFunc _glBindMaterialParameterEXT = NULL;
#endif
#ifdef glBindTexGenParameterEXT
glBindTexGenParameterEXTFunc _glBindTexGenParameterEXT = NULL;
#endif
#ifdef glBindTextureUnitParameterEXT
glBindTextureUnitParameterEXTFunc _glBindTextureUnitParameterEXT = NULL;
#endif
#ifdef glBindParameterEXT
glBindParameterEXTFunc _glBindParameterEXT = NULL;
#endif
#ifdef glIsVariantEnabledEXT
glIsVariantEnabledEXTFunc _glIsVariantEnabledEXT = NULL;
#endif
#ifdef glGetVariantBooleanvEXT
glGetVariantBooleanvEXTFunc _glGetVariantBooleanvEXT = NULL;
#endif
#ifdef glGetVariantIntegervEXT
glGetVariantIntegervEXTFunc _glGetVariantIntegervEXT = NULL;
#endif
#ifdef glGetVariantFloatvEXT
glGetVariantFloatvEXTFunc _glGetVariantFloatvEXT = NULL;
#endif
#ifdef glGetVariantPointervEXT
glGetVariantPointervEXTFunc _glGetVariantPointervEXT = NULL;
#endif
#ifdef glGetInvariantBooleanvEXT
glGetInvariantBooleanvEXTFunc _glGetInvariantBooleanvEXT = NULL;
#endif
#ifdef glGetInvariantIntegervEXT
glGetInvariantIntegervEXTFunc _glGetInvariantIntegervEXT = NULL;
#endif
#ifdef glGetInvariantFloatvEXT
glGetInvariantFloatvEXTFunc _glGetInvariantFloatvEXT = NULL;
#endif
#ifdef glGetLocalConstantBooleanvEXT
glGetLocalConstantBooleanvEXTFunc _glGetLocalConstantBooleanvEXT = NULL;
#endif
#ifdef glGetLocalConstantIntegervEXT
glGetLocalConstantIntegervEXTFunc _glGetLocalConstantIntegervEXT = NULL;
#endif
#ifdef glGetLocalConstantFloatvEXT
glGetLocalConstantFloatvEXTFunc _glGetLocalConstantFloatvEXT = NULL;
#endif
#ifdef glVertexStream1sATI
glVertexStream1sATIFunc _glVertexStream1sATI = NULL;
#endif
#ifdef glVertexStream1svATI
glVertexStream1svATIFunc _glVertexStream1svATI = NULL;
#endif
#ifdef glVertexStream1iATI
glVertexStream1iATIFunc _glVertexStream1iATI = NULL;
#endif
#ifdef glVertexStream1ivATI
glVertexStream1ivATIFunc _glVertexStream1ivATI = NULL;
#endif
#ifdef glVertexStream1fATI
glVertexStream1fATIFunc _glVertexStream1fATI = NULL;
#endif
#ifdef glVertexStream1fvATI
glVertexStream1fvATIFunc _glVertexStream1fvATI = NULL;
#endif
#ifdef glVertexStream1dATI
glVertexStream1dATIFunc _glVertexStream1dATI = NULL;
#endif
#ifdef glVertexStream1dvATI
glVertexStream1dvATIFunc _glVertexStream1dvATI = NULL;
#endif
#ifdef glVertexStream2sATI
glVertexStream2sATIFunc _glVertexStream2sATI = NULL;
#endif
#ifdef glVertexStream2svATI
glVertexStream2svATIFunc _glVertexStream2svATI = NULL;
#endif
#ifdef glVertexStream2iATI
glVertexStream2iATIFunc _glVertexStream2iATI = NULL;
#endif
#ifdef glVertexStream2ivATI
glVertexStream2ivATIFunc _glVertexStream2ivATI = NULL;
#endif
#ifdef glVertexStream2fATI
glVertexStream2fATIFunc _glVertexStream2fATI = NULL;
#endif
#ifdef glVertexStream2fvATI
glVertexStream2fvATIFunc _glVertexStream2fvATI = NULL;
#endif
#ifdef glVertexStream2dATI
glVertexStream2dATIFunc _glVertexStream2dATI = NULL;
#endif
#ifdef glVertexStream2dvATI
glVertexStream2dvATIFunc _glVertexStream2dvATI = NULL;
#endif
#ifdef glVertexStream3sATI
glVertexStream3sATIFunc _glVertexStream3sATI = NULL;
#endif
#ifdef glVertexStream3svATI
glVertexStream3svATIFunc _glVertexStream3svATI = NULL;
#endif
#ifdef glVertexStream3iATI
glVertexStream3iATIFunc _glVertexStream3iATI = NULL;
#endif
#ifdef glVertexStream3ivATI
glVertexStream3ivATIFunc _glVertexStream3ivATI = NULL;
#endif
#ifdef glVertexStream3fATI
glVertexStream3fATIFunc _glVertexStream3fATI = NULL;
#endif
#ifdef glVertexStream3fvATI
glVertexStream3fvATIFunc _glVertexStream3fvATI = NULL;
#endif
#ifdef glVertexStream3dATI
glVertexStream3dATIFunc _glVertexStream3dATI = NULL;
#endif
#ifdef glVertexStream3dvATI
glVertexStream3dvATIFunc _glVertexStream3dvATI = NULL;
#endif
#ifdef glVertexStream4sATI
glVertexStream4sATIFunc _glVertexStream4sATI = NULL;
#endif
#ifdef glVertexStream4svATI
glVertexStream4svATIFunc _glVertexStream4svATI = NULL;
#endif
#ifdef glVertexStream4iATI
glVertexStream4iATIFunc _glVertexStream4iATI = NULL;
#endif
#ifdef glVertexStream4ivATI
glVertexStream4ivATIFunc _glVertexStream4ivATI = NULL;
#endif
#ifdef glVertexStream4fATI
glVertexStream4fATIFunc _glVertexStream4fATI = NULL;
#endif
#ifdef glVertexStream4fvATI
glVertexStream4fvATIFunc _glVertexStream4fvATI = NULL;
#endif
#ifdef glVertexStream4dATI
glVertexStream4dATIFunc _glVertexStream4dATI = NULL;
#endif
#ifdef glVertexStream4dvATI
glVertexStream4dvATIFunc _glVertexStream4dvATI = NULL;
#endif
#ifdef glNormalStream3bATI
glNormalStream3bATIFunc _glNormalStream3bATI = NULL;
#endif
#ifdef glNormalStream3bvATI
glNormalStream3bvATIFunc _glNormalStream3bvATI = NULL;
#endif
#ifdef glNormalStream3sATI
glNormalStream3sATIFunc _glNormalStream3sATI = NULL;
#endif
#ifdef glNormalStream3svATI
glNormalStream3svATIFunc _glNormalStream3svATI = NULL;
#endif
#ifdef glNormalStream3iATI
glNormalStream3iATIFunc _glNormalStream3iATI = NULL;
#endif
#ifdef glNormalStream3ivATI
glNormalStream3ivATIFunc _glNormalStream3ivATI = NULL;
#endif
#ifdef glNormalStream3fATI
glNormalStream3fATIFunc _glNormalStream3fATI = NULL;
#endif
#ifdef glNormalStream3fvATI
glNormalStream3fvATIFunc _glNormalStream3fvATI = NULL;
#endif
#ifdef glNormalStream3dATI
glNormalStream3dATIFunc _glNormalStream3dATI = NULL;
#endif
#ifdef glNormalStream3dvATI
glNormalStream3dvATIFunc _glNormalStream3dvATI = NULL;
#endif
#ifdef glClientActiveVertexStreamATI
glClientActiveVertexStreamATIFunc _glClientActiveVertexStreamATI = NULL;
#endif
#ifdef glVertexBlendEnviATI
glVertexBlendEnviATIFunc _glVertexBlendEnviATI = NULL;
#endif
#ifdef glVertexBlendEnvfATI
glVertexBlendEnvfATIFunc _glVertexBlendEnvfATI = NULL;
#endif
#ifdef glElementPointerATI
glElementPointerATIFunc _glElementPointerATI = NULL;
#endif
#ifdef glDrawElementArrayATI
glDrawElementArrayATIFunc _glDrawElementArrayATI = NULL;
#endif
#ifdef glDrawRangeElementArrayATI
glDrawRangeElementArrayATIFunc _glDrawRangeElementArrayATI = NULL;
#endif
#ifdef glDrawMeshArraysSUN
glDrawMeshArraysSUNFunc _glDrawMeshArraysSUN = NULL;
#endif
#ifdef glGenOcclusionQueriesNV
glGenOcclusionQueriesNVFunc _glGenOcclusionQueriesNV = NULL;
#endif
#ifdef glDeleteOcclusionQueriesNV
glDeleteOcclusionQueriesNVFunc _glDeleteOcclusionQueriesNV = NULL;
#endif
#ifdef glIsOcclusionQueryNV
glIsOcclusionQueryNVFunc _glIsOcclusionQueryNV = NULL;
#endif
#ifdef glBeginOcclusionQueryNV
glBeginOcclusionQueryNVFunc _glBeginOcclusionQueryNV = NULL;
#endif
#ifdef glEndOcclusionQueryNV
glEndOcclusionQueryNVFunc _glEndOcclusionQueryNV = NULL;
#endif
#ifdef glGetOcclusionQueryivNV
glGetOcclusionQueryivNVFunc _glGetOcclusionQueryivNV = NULL;
#endif
#ifdef glGetOcclusionQueryuivNV
glGetOcclusionQueryuivNVFunc _glGetOcclusionQueryuivNV = NULL;
#endif
#ifdef glPointParameteriNV
glPointParameteriNVFunc _glPointParameteriNV = NULL;
#endif
#ifdef glPointParameterivNV
glPointParameterivNVFunc _glPointParameterivNV = NULL;
#endif
#ifdef glActiveStencilFaceEXT
glActiveStencilFaceEXTFunc _glActiveStencilFaceEXT = NULL;
#endif
#ifdef glElementPointerAPPLE
glElementPointerAPPLEFunc _glElementPointerAPPLE = NULL;
#endif
#ifdef glDrawElementArrayAPPLE
glDrawElementArrayAPPLEFunc _glDrawElementArrayAPPLE = NULL;
#endif
#ifdef glDrawRangeElementArrayAPPLE
glDrawRangeElementArrayAPPLEFunc _glDrawRangeElementArrayAPPLE = NULL;
#endif
#ifdef glMultiDrawElementArrayAPPLE
glMultiDrawElementArrayAPPLEFunc _glMultiDrawElementArrayAPPLE = NULL;
#endif
#ifdef glMultiDrawRangeElementArrayAPPLE
glMultiDrawRangeElementArrayAPPLEFunc _glMultiDrawRangeElementArrayAPPLE = NULL;
#endif
#ifdef glGenFencesAPPLE
glGenFencesAPPLEFunc _glGenFencesAPPLE = NULL;
#endif
#ifdef glDeleteFencesAPPLE
glDeleteFencesAPPLEFunc _glDeleteFencesAPPLE = NULL;
#endif
#ifdef glSetFenceAPPLE
glSetFenceAPPLEFunc _glSetFenceAPPLE = NULL;
#endif
#ifdef glIsFenceAPPLE
glIsFenceAPPLEFunc _glIsFenceAPPLE = NULL;
#endif
#ifdef glTestFenceAPPLE
glTestFenceAPPLEFunc _glTestFenceAPPLE = NULL;
#endif
#ifdef glFinishFenceAPPLE
glFinishFenceAPPLEFunc _glFinishFenceAPPLE = NULL;
#endif
#ifdef glTestObjectAPPLE
glTestObjectAPPLEFunc _glTestObjectAPPLE = NULL;
#endif
#ifdef glFinishObjectAPPLE
glFinishObjectAPPLEFunc _glFinishObjectAPPLE = NULL;
#endif
#ifdef glBindVertexArrayAPPLE
glBindVertexArrayAPPLEFunc _glBindVertexArrayAPPLE = NULL;
#endif
#ifdef glDeleteVertexArraysAPPLE
glDeleteVertexArraysAPPLEFunc _glDeleteVertexArraysAPPLE = NULL;
#endif
#ifdef glGenVertexArraysAPPLE
glGenVertexArraysAPPLEFunc _glGenVertexArraysAPPLE = NULL;
#endif
#ifdef glIsVertexArrayAPPLE
glIsVertexArrayAPPLEFunc _glIsVertexArrayAPPLE = NULL;
#endif
#ifdef glVertexArrayRangeAPPLE
glVertexArrayRangeAPPLEFunc _glVertexArrayRangeAPPLE = NULL;
#endif
#ifdef glFlushVertexArrayRangeAPPLE
glFlushVertexArrayRangeAPPLEFunc _glFlushVertexArrayRangeAPPLE = NULL;
#endif
#ifdef glVertexArrayParameteriAPPLE
glVertexArrayParameteriAPPLEFunc _glVertexArrayParameteriAPPLE = NULL;
#endif
#ifdef glDrawBuffersATI
glDrawBuffersATIFunc _glDrawBuffersATI = NULL;
#endif
#ifdef glProgramNamedParameter4fNV
glProgramNamedParameter4fNVFunc _glProgramNamedParameter4fNV = NULL;
#endif
#ifdef glProgramNamedParameter4dNV
glProgramNamedParameter4dNVFunc _glProgramNamedParameter4dNV = NULL;
#endif
#ifdef glProgramNamedParameter4fvNV
glProgramNamedParameter4fvNVFunc _glProgramNamedParameter4fvNV = NULL;
#endif
#ifdef glProgramNamedParameter4dvNV
glProgramNamedParameter4dvNVFunc _glProgramNamedParameter4dvNV = NULL;
#endif
#ifdef glGetProgramNamedParameterfvNV
glGetProgramNamedParameterfvNVFunc _glGetProgramNamedParameterfvNV = NULL;
#endif
#ifdef glGetProgramNamedParameterdvNV
glGetProgramNamedParameterdvNVFunc _glGetProgramNamedParameterdvNV = NULL;
#endif
#ifdef glVertex2hNV
glVertex2hNVFunc _glVertex2hNV = NULL;
#endif
#ifdef glVertex2hvNV
glVertex2hvNVFunc _glVertex2hvNV = NULL;
#endif
#ifdef glVertex3hNV
glVertex3hNVFunc _glVertex3hNV = NULL;
#endif
#ifdef glVertex3hvNV
glVertex3hvNVFunc _glVertex3hvNV = NULL;
#endif
#ifdef glVertex4hNV
glVertex4hNVFunc _glVertex4hNV = NULL;
#endif
#ifdef glVertex4hvNV
glVertex4hvNVFunc _glVertex4hvNV = NULL;
#endif
#ifdef glNormal3hNV
glNormal3hNVFunc _glNormal3hNV = NULL;
#endif
#ifdef glNormal3hvNV
glNormal3hvNVFunc _glNormal3hvNV = NULL;
#endif
#ifdef glColor3hNV
glColor3hNVFunc _glColor3hNV = NULL;
#endif
#ifdef glColor3hvNV
glColor3hvNVFunc _glColor3hvNV = NULL;
#endif
#ifdef glColor4hNV
glColor4hNVFunc _glColor4hNV = NULL;
#endif
#ifdef glColor4hvNV
glColor4hvNVFunc _glColor4hvNV = NULL;
#endif
#ifdef glTexCoord1hNV
glTexCoord1hNVFunc _glTexCoord1hNV = NULL;
#endif
#ifdef glTexCoord1hvNV
glTexCoord1hvNVFunc _glTexCoord1hvNV = NULL;
#endif
#ifdef glTexCoord2hNV
glTexCoord2hNVFunc _glTexCoord2hNV = NULL;
#endif
#ifdef glTexCoord2hvNV
glTexCoord2hvNVFunc _glTexCoord2hvNV = NULL;
#endif
#ifdef glTexCoord3hNV
glTexCoord3hNVFunc _glTexCoord3hNV = NULL;
#endif
#ifdef glTexCoord3hvNV
glTexCoord3hvNVFunc _glTexCoord3hvNV = NULL;
#endif
#ifdef glTexCoord4hNV
glTexCoord4hNVFunc _glTexCoord4hNV = NULL;
#endif
#ifdef glTexCoord4hvNV
glTexCoord4hvNVFunc _glTexCoord4hvNV = NULL;
#endif
#ifdef glMultiTexCoord1hNV
glMultiTexCoord1hNVFunc _glMultiTexCoord1hNV = NULL;
#endif
#ifdef glMultiTexCoord1hvNV
glMultiTexCoord1hvNVFunc _glMultiTexCoord1hvNV = NULL;
#endif
#ifdef glMultiTexCoord2hNV
glMultiTexCoord2hNVFunc _glMultiTexCoord2hNV = NULL;
#endif
#ifdef glMultiTexCoord2hvNV
glMultiTexCoord2hvNVFunc _glMultiTexCoord2hvNV = NULL;
#endif
#ifdef glMultiTexCoord3hNV
glMultiTexCoord3hNVFunc _glMultiTexCoord3hNV = NULL;
#endif
#ifdef glMultiTexCoord3hvNV
glMultiTexCoord3hvNVFunc _glMultiTexCoord3hvNV = NULL;
#endif
#ifdef glMultiTexCoord4hNV
glMultiTexCoord4hNVFunc _glMultiTexCoord4hNV = NULL;
#endif
#ifdef glMultiTexCoord4hvNV
glMultiTexCoord4hvNVFunc _glMultiTexCoord4hvNV = NULL;
#endif
#ifdef glFogCoordhNV
glFogCoordhNVFunc _glFogCoordhNV = NULL;
#endif
#ifdef glFogCoordhvNV
glFogCoordhvNVFunc _glFogCoordhvNV = NULL;
#endif
#ifdef glSecondaryColor3hNV
glSecondaryColor3hNVFunc _glSecondaryColor3hNV = NULL;
#endif
#ifdef glSecondaryColor3hvNV
glSecondaryColor3hvNVFunc _glSecondaryColor3hvNV = NULL;
#endif
#ifdef glVertexWeighthNV
glVertexWeighthNVFunc _glVertexWeighthNV = NULL;
#endif
#ifdef glVertexWeighthvNV
glVertexWeighthvNVFunc _glVertexWeighthvNV = NULL;
#endif
#ifdef glVertexAttrib1hNV
glVertexAttrib1hNVFunc _glVertexAttrib1hNV = NULL;
#endif
#ifdef glVertexAttrib1hvNV
glVertexAttrib1hvNVFunc _glVertexAttrib1hvNV = NULL;
#endif
#ifdef glVertexAttrib2hNV
glVertexAttrib2hNVFunc _glVertexAttrib2hNV = NULL;
#endif
#ifdef glVertexAttrib2hvNV
glVertexAttrib2hvNVFunc _glVertexAttrib2hvNV = NULL;
#endif
#ifdef glVertexAttrib3hNV
glVertexAttrib3hNVFunc _glVertexAttrib3hNV = NULL;
#endif
#ifdef glVertexAttrib3hvNV
glVertexAttrib3hvNVFunc _glVertexAttrib3hvNV = NULL;
#endif
#ifdef glVertexAttrib4hNV
glVertexAttrib4hNVFunc _glVertexAttrib4hNV = NULL;
#endif
#ifdef glVertexAttrib4hvNV
glVertexAttrib4hvNVFunc _glVertexAttrib4hvNV = NULL;
#endif
#ifdef glVertexAttribs1hvNV
glVertexAttribs1hvNVFunc _glVertexAttribs1hvNV = NULL;
#endif
#ifdef glVertexAttribs2hvNV
glVertexAttribs2hvNVFunc _glVertexAttribs2hvNV = NULL;
#endif
#ifdef glVertexAttribs3hvNV
glVertexAttribs3hvNVFunc _glVertexAttribs3hvNV = NULL;
#endif
#ifdef glVertexAttribs4hvNV
glVertexAttribs4hvNVFunc _glVertexAttribs4hvNV = NULL;
#endif
#ifdef glPixelDataRangeNV
glPixelDataRangeNVFunc _glPixelDataRangeNV = NULL;
#endif
#ifdef glFlushPixelDataRangeNV
glFlushPixelDataRangeNVFunc _glFlushPixelDataRangeNV = NULL;
#endif
#ifdef glPrimitiveRestartNV
glPrimitiveRestartNVFunc _glPrimitiveRestartNV = NULL;
#endif
#ifdef glPrimitiveRestartIndexNV
glPrimitiveRestartIndexNVFunc _glPrimitiveRestartIndexNV = NULL;
#endif
#ifdef glMapObjectBufferATI
glMapObjectBufferATIFunc _glMapObjectBufferATI = NULL;
#endif
#ifdef glUnmapObjectBufferATI
glUnmapObjectBufferATIFunc _glUnmapObjectBufferATI = NULL;
#endif
#ifdef glStencilOpSeparateATI
glStencilOpSeparateATIFunc _glStencilOpSeparateATI = NULL;
#endif
#ifdef glStencilFuncSeparateATI
glStencilFuncSeparateATIFunc _glStencilFuncSeparateATI = NULL;
#endif
#ifdef glVertexAttribArrayObjectATI
glVertexAttribArrayObjectATIFunc _glVertexAttribArrayObjectATI = NULL;
#endif
#ifdef glGetVertexAttribArrayObjectfvATI
glGetVertexAttribArrayObjectfvATIFunc _glGetVertexAttribArrayObjectfvATI = NULL;
#endif
#ifdef glGetVertexAttribArrayObjectivATI
glGetVertexAttribArrayObjectivATIFunc _glGetVertexAttribArrayObjectivATI = NULL;
#endif
#ifdef glDepthBoundsEXT
glDepthBoundsEXTFunc _glDepthBoundsEXT = NULL;
#endif
#ifdef glBlendEquationSeparateEXT
glBlendEquationSeparateEXTFunc _glBlendEquationSeparateEXT = NULL;
#endif
#ifdef glIsRenderbufferEXT
glIsRenderbufferEXTFunc _glIsRenderbufferEXT = NULL;
#endif
#ifdef glBindRenderbufferEXT
glBindRenderbufferEXTFunc _glBindRenderbufferEXT = NULL;
#endif
#ifdef glDeleteRenderbuffersEXT
glDeleteRenderbuffersEXTFunc _glDeleteRenderbuffersEXT = NULL;
#endif
#ifdef glGenRenderbuffersEXT
glGenRenderbuffersEXTFunc _glGenRenderbuffersEXT = NULL;
#endif
#ifdef glRenderbufferStorageEXT
glRenderbufferStorageEXTFunc _glRenderbufferStorageEXT = NULL;
#endif
#ifdef glGetRenderbufferParameterivEXT
glGetRenderbufferParameterivEXTFunc _glGetRenderbufferParameterivEXT = NULL;
#endif
#ifdef glIsFramebufferEXT
glIsFramebufferEXTFunc _glIsFramebufferEXT = NULL;
#endif
#ifdef glBindFramebufferEXT
glBindFramebufferEXTFunc _glBindFramebufferEXT = NULL;
#endif
#ifdef glDeleteFramebuffersEXT
glDeleteFramebuffersEXTFunc _glDeleteFramebuffersEXT = NULL;
#endif
#ifdef glGenFramebuffersEXT
glGenFramebuffersEXTFunc _glGenFramebuffersEXT = NULL;
#endif
#ifdef glCheckFramebufferStatusEXT
glCheckFramebufferStatusEXTFunc _glCheckFramebufferStatusEXT = NULL;
#endif
#ifdef glFramebufferTexture1DEXT
glFramebufferTexture1DEXTFunc _glFramebufferTexture1DEXT = NULL;
#endif
#ifdef glFramebufferTexture2DEXT
glFramebufferTexture2DEXTFunc _glFramebufferTexture2DEXT = NULL;
#endif
#ifdef glFramebufferTexture3DEXT
glFramebufferTexture3DEXTFunc _glFramebufferTexture3DEXT = NULL;
#endif
#ifdef glFramebufferRenderbufferEXT
glFramebufferRenderbufferEXTFunc _glFramebufferRenderbufferEXT = NULL;
#endif
#ifdef glGetFramebufferAttachmentParameterivEXT
glGetFramebufferAttachmentParameterivEXTFunc _glGetFramebufferAttachmentParameterivEXT = NULL;
#endif
#ifdef glGenerateMipmapEXT
glGenerateMipmapEXTFunc _glGenerateMipmapEXT = NULL;
#endif
#ifdef glStringMarkerGREMEDY
glStringMarkerGREMEDYFunc _glStringMarkerGREMEDY = NULL;
#endif
#ifdef glStencilClearTagEXT
glStencilClearTagEXTFunc _glStencilClearTagEXT = NULL;
#endif
#ifdef glBlitFramebufferEXT
glBlitFramebufferEXTFunc _glBlitFramebufferEXT = NULL;
#endif
#ifdef glRenderbufferStorageMultisampleEXT
glRenderbufferStorageMultisampleEXTFunc _glRenderbufferStorageMultisampleEXT = NULL;
#endif
#ifdef glGetQueryObjecti64vEXT
glGetQueryObjecti64vEXTFunc _glGetQueryObjecti64vEXT = NULL;
#endif
#ifdef glGetQueryObjectui64vEXT
glGetQueryObjectui64vEXTFunc _glGetQueryObjectui64vEXT = NULL;
#endif
#ifdef glProgramEnvParameters4fvEXT
glProgramEnvParameters4fvEXTFunc _glProgramEnvParameters4fvEXT = NULL;
#endif
#ifdef glProgramLocalParameters4fvEXT
glProgramLocalParameters4fvEXTFunc _glProgramLocalParameters4fvEXT = NULL;
#endif
#ifdef glBufferParameteriAPPLE
glBufferParameteriAPPLEFunc _glBufferParameteriAPPLE = NULL;
#endif
#ifdef glFlushMappedBufferRangeAPPLE
glFlushMappedBufferRangeAPPLEFunc _glFlushMappedBufferRangeAPPLE = NULL;
#endif
#ifdef glProgramLocalParameterI4iNV
glProgramLocalParameterI4iNVFunc _glProgramLocalParameterI4iNV = NULL;
#endif
#ifdef glProgramLocalParameterI4ivNV
glProgramLocalParameterI4ivNVFunc _glProgramLocalParameterI4ivNV = NULL;
#endif
#ifdef glProgramLocalParametersI4ivNV
glProgramLocalParametersI4ivNVFunc _glProgramLocalParametersI4ivNV = NULL;
#endif
#ifdef glProgramLocalParameterI4uiNV
glProgramLocalParameterI4uiNVFunc _glProgramLocalParameterI4uiNV = NULL;
#endif
#ifdef glProgramLocalParameterI4uivNV
glProgramLocalParameterI4uivNVFunc _glProgramLocalParameterI4uivNV = NULL;
#endif
#ifdef glProgramLocalParametersI4uivNV
glProgramLocalParametersI4uivNVFunc _glProgramLocalParametersI4uivNV = NULL;
#endif
#ifdef glProgramEnvParameterI4iNV
glProgramEnvParameterI4iNVFunc _glProgramEnvParameterI4iNV = NULL;
#endif
#ifdef glProgramEnvParameterI4ivNV
glProgramEnvParameterI4ivNVFunc _glProgramEnvParameterI4ivNV = NULL;
#endif
#ifdef glProgramEnvParametersI4ivNV
glProgramEnvParametersI4ivNVFunc _glProgramEnvParametersI4ivNV = NULL;
#endif
#ifdef glProgramEnvParameterI4uiNV
glProgramEnvParameterI4uiNVFunc _glProgramEnvParameterI4uiNV = NULL;
#endif
#ifdef glProgramEnvParameterI4uivNV
glProgramEnvParameterI4uivNVFunc _glProgramEnvParameterI4uivNV = NULL;
#endif
#ifdef glProgramEnvParametersI4uivNV
glProgramEnvParametersI4uivNVFunc _glProgramEnvParametersI4uivNV = NULL;
#endif
#ifdef glGetProgramLocalParameterIivNV
glGetProgramLocalParameterIivNVFunc _glGetProgramLocalParameterIivNV = NULL;
#endif
#ifdef glGetProgramLocalParameterIuivNV
glGetProgramLocalParameterIuivNVFunc _glGetProgramLocalParameterIuivNV = NULL;
#endif
#ifdef glGetProgramEnvParameterIivNV
glGetProgramEnvParameterIivNVFunc _glGetProgramEnvParameterIivNV = NULL;
#endif
#ifdef glGetProgramEnvParameterIuivNV
glGetProgramEnvParameterIuivNVFunc _glGetProgramEnvParameterIuivNV = NULL;
#endif
#ifdef glProgramVertexLimitNV
glProgramVertexLimitNVFunc _glProgramVertexLimitNV = NULL;
#endif
#ifdef glFramebufferTextureEXT
glFramebufferTextureEXTFunc _glFramebufferTextureEXT = NULL;
#endif
#ifdef glFramebufferTextureLayerEXT
glFramebufferTextureLayerEXTFunc _glFramebufferTextureLayerEXT = NULL;
#endif
#ifdef glFramebufferTextureFaceEXT
glFramebufferTextureFaceEXTFunc _glFramebufferTextureFaceEXT = NULL;
#endif
#ifdef glProgramParameteriEXT
glProgramParameteriEXTFunc _glProgramParameteriEXT = NULL;
#endif
#ifdef glVertexAttribI1iEXT
glVertexAttribI1iEXTFunc _glVertexAttribI1iEXT = NULL;
#endif
#ifdef glVertexAttribI2iEXT
glVertexAttribI2iEXTFunc _glVertexAttribI2iEXT = NULL;
#endif
#ifdef glVertexAttribI3iEXT
glVertexAttribI3iEXTFunc _glVertexAttribI3iEXT = NULL;
#endif
#ifdef glVertexAttribI4iEXT
glVertexAttribI4iEXTFunc _glVertexAttribI4iEXT = NULL;
#endif
#ifdef glVertexAttribI1uiEXT
glVertexAttribI1uiEXTFunc _glVertexAttribI1uiEXT = NULL;
#endif
#ifdef glVertexAttribI2uiEXT
glVertexAttribI2uiEXTFunc _glVertexAttribI2uiEXT = NULL;
#endif
#ifdef glVertexAttribI3uiEXT
glVertexAttribI3uiEXTFunc _glVertexAttribI3uiEXT = NULL;
#endif
#ifdef glVertexAttribI4uiEXT
glVertexAttribI4uiEXTFunc _glVertexAttribI4uiEXT = NULL;
#endif
#ifdef glVertexAttribI1ivEXT
glVertexAttribI1ivEXTFunc _glVertexAttribI1ivEXT = NULL;
#endif
#ifdef glVertexAttribI2ivEXT
glVertexAttribI2ivEXTFunc _glVertexAttribI2ivEXT = NULL;
#endif
#ifdef glVertexAttribI3ivEXT
glVertexAttribI3ivEXTFunc _glVertexAttribI3ivEXT = NULL;
#endif
#ifdef glVertexAttribI4ivEXT
glVertexAttribI4ivEXTFunc _glVertexAttribI4ivEXT = NULL;
#endif
#ifdef glVertexAttribI1uivEXT
glVertexAttribI1uivEXTFunc _glVertexAttribI1uivEXT = NULL;
#endif
#ifdef glVertexAttribI2uivEXT
glVertexAttribI2uivEXTFunc _glVertexAttribI2uivEXT = NULL;
#endif
#ifdef glVertexAttribI3uivEXT
glVertexAttribI3uivEXTFunc _glVertexAttribI3uivEXT = NULL;
#endif
#ifdef glVertexAttribI4uivEXT
glVertexAttribI4uivEXTFunc _glVertexAttribI4uivEXT = NULL;
#endif
#ifdef glVertexAttribI4bvEXT
glVertexAttribI4bvEXTFunc _glVertexAttribI4bvEXT = NULL;
#endif
#ifdef glVertexAttribI4svEXT
glVertexAttribI4svEXTFunc _glVertexAttribI4svEXT = NULL;
#endif
#ifdef glVertexAttribI4ubvEXT
glVertexAttribI4ubvEXTFunc _glVertexAttribI4ubvEXT = NULL;
#endif
#ifdef glVertexAttribI4usvEXT
glVertexAttribI4usvEXTFunc _glVertexAttribI4usvEXT = NULL;
#endif
#ifdef glVertexAttribIPointerEXT
glVertexAttribIPointerEXTFunc _glVertexAttribIPointerEXT = NULL;
#endif
#ifdef glGetVertexAttribIivEXT
glGetVertexAttribIivEXTFunc _glGetVertexAttribIivEXT = NULL;
#endif
#ifdef glGetVertexAttribIuivEXT
glGetVertexAttribIuivEXTFunc _glGetVertexAttribIuivEXT = NULL;
#endif
#ifdef glGetUniformuivEXT
glGetUniformuivEXTFunc _glGetUniformuivEXT = NULL;
#endif
#ifdef glBindFragDataLocationEXT
glBindFragDataLocationEXTFunc _glBindFragDataLocationEXT = NULL;
#endif
#ifdef glGetFragDataLocationEXT
glGetFragDataLocationEXTFunc _glGetFragDataLocationEXT = NULL;
#endif
#ifdef glUniform1uiEXT
glUniform1uiEXTFunc _glUniform1uiEXT = NULL;
#endif
#ifdef glUniform2uiEXT
glUniform2uiEXTFunc _glUniform2uiEXT = NULL;
#endif
#ifdef glUniform3uiEXT
glUniform3uiEXTFunc _glUniform3uiEXT = NULL;
#endif
#ifdef glUniform4uiEXT
glUniform4uiEXTFunc _glUniform4uiEXT = NULL;
#endif
#ifdef glUniform1uivEXT
glUniform1uivEXTFunc _glUniform1uivEXT = NULL;
#endif
#ifdef glUniform2uivEXT
glUniform2uivEXTFunc _glUniform2uivEXT = NULL;
#endif
#ifdef glUniform3uivEXT
glUniform3uivEXTFunc _glUniform3uivEXT = NULL;
#endif
#ifdef glUniform4uivEXT
glUniform4uivEXTFunc _glUniform4uivEXT = NULL;
#endif
#ifdef glDrawArraysInstancedEXT
glDrawArraysInstancedEXTFunc _glDrawArraysInstancedEXT = NULL;
#endif
#ifdef glDrawElementsInstancedEXT
glDrawElementsInstancedEXTFunc _glDrawElementsInstancedEXT = NULL;
#endif
#ifdef glTexBufferEXT
glTexBufferEXTFunc _glTexBufferEXT = NULL;
#endif
#ifdef glDepthRangedNV
glDepthRangedNVFunc _glDepthRangedNV = NULL;
#endif
#ifdef glClearDepthdNV
glClearDepthdNVFunc _glClearDepthdNV = NULL;
#endif
#ifdef glDepthBoundsdNV
glDepthBoundsdNVFunc _glDepthBoundsdNV = NULL;
#endif
#ifdef glRenderbufferStorageMultisampleCoverageNV
glRenderbufferStorageMultisampleCoverageNVFunc _glRenderbufferStorageMultisampleCoverageNV = NULL;
#endif
#ifdef glProgramBufferParametersfvNV
glProgramBufferParametersfvNVFunc _glProgramBufferParametersfvNV = NULL;
#endif
#ifdef glProgramBufferParametersIivNV
glProgramBufferParametersIivNVFunc _glProgramBufferParametersIivNV = NULL;
#endif
#ifdef glProgramBufferParametersIuivNV
glProgramBufferParametersIuivNVFunc _glProgramBufferParametersIuivNV = NULL;
#endif
#ifdef glColorMaskIndexedEXT
glColorMaskIndexedEXTFunc _glColorMaskIndexedEXT = NULL;
#endif
#ifdef glGetBooleanIndexedvEXT
glGetBooleanIndexedvEXTFunc _glGetBooleanIndexedvEXT = NULL;
#endif
#ifdef glGetIntegerIndexedvEXT
glGetIntegerIndexedvEXTFunc _glGetIntegerIndexedvEXT = NULL;
#endif
#ifdef glEnableIndexedEXT
glEnableIndexedEXTFunc _glEnableIndexedEXT = NULL;
#endif
#ifdef glDisableIndexedEXT
glDisableIndexedEXTFunc _glDisableIndexedEXT = NULL;
#endif
#ifdef glIsEnabledIndexedEXT
glIsEnabledIndexedEXTFunc _glIsEnabledIndexedEXT = NULL;
#endif
#ifdef glBeginTransformFeedbackNV
glBeginTransformFeedbackNVFunc _glBeginTransformFeedbackNV = NULL;
#endif
#ifdef glEndTransformFeedbackNV
glEndTransformFeedbackNVFunc _glEndTransformFeedbackNV = NULL;
#endif
#ifdef glTransformFeedbackAttribsNV
glTransformFeedbackAttribsNVFunc _glTransformFeedbackAttribsNV = NULL;
#endif
#ifdef glBindBufferRangeNV
glBindBufferRangeNVFunc _glBindBufferRangeNV = NULL;
#endif
#ifdef glBindBufferOffsetNV
glBindBufferOffsetNVFunc _glBindBufferOffsetNV = NULL;
#endif
#ifdef glBindBufferBaseNV
glBindBufferBaseNVFunc _glBindBufferBaseNV = NULL;
#endif
#ifdef glTransformFeedbackVaryingsNV
glTransformFeedbackVaryingsNVFunc _glTransformFeedbackVaryingsNV = NULL;
#endif
#ifdef glActiveVaryingNV
glActiveVaryingNVFunc _glActiveVaryingNV = NULL;
#endif
#ifdef glGetVaryingLocationNV
glGetVaryingLocationNVFunc _glGetVaryingLocationNV = NULL;
#endif
#ifdef glGetActiveVaryingNV
glGetActiveVaryingNVFunc _glGetActiveVaryingNV = NULL;
#endif
#ifdef glGetTransformFeedbackVaryingNV
glGetTransformFeedbackVaryingNVFunc _glGetTransformFeedbackVaryingNV = NULL;
#endif
#ifdef glTransformFeedbackStreamAttribsNV
glTransformFeedbackStreamAttribsNVFunc _glTransformFeedbackStreamAttribsNV = NULL;
#endif
#ifdef glUniformBufferEXT
glUniformBufferEXTFunc _glUniformBufferEXT = NULL;
#endif
#ifdef glGetUniformBufferSizeEXT
glGetUniformBufferSizeEXTFunc _glGetUniformBufferSizeEXT = NULL;
#endif
#ifdef glGetUniformOffsetEXT
glGetUniformOffsetEXTFunc _glGetUniformOffsetEXT = NULL;
#endif
#ifdef glTexParameterIivEXT
glTexParameterIivEXTFunc _glTexParameterIivEXT = NULL;
#endif
#ifdef glTexParameterIuivEXT
glTexParameterIuivEXTFunc _glTexParameterIuivEXT = NULL;
#endif
#ifdef glGetTexParameterIivEXT
glGetTexParameterIivEXTFunc _glGetTexParameterIivEXT = NULL;
#endif
#ifdef glGetTexParameterIuivEXT
glGetTexParameterIuivEXTFunc _glGetTexParameterIuivEXT = NULL;
#endif
#ifdef glClearColorIiEXT
glClearColorIiEXTFunc _glClearColorIiEXT = NULL;
#endif
#ifdef glClearColorIuiEXT
glClearColorIuiEXTFunc _glClearColorIuiEXT = NULL;
#endif
#ifdef glFrameTerminatorGREMEDY
glFrameTerminatorGREMEDYFunc _glFrameTerminatorGREMEDY = NULL;
#endif
#ifdef glBeginConditionalRenderNV
glBeginConditionalRenderNVFunc _glBeginConditionalRenderNV = NULL;
#endif
#ifdef glEndConditionalRenderNV
glEndConditionalRenderNVFunc _glEndConditionalRenderNV = NULL;
#endif
#ifdef glPresentFrameKeyedNV
glPresentFrameKeyedNVFunc _glPresentFrameKeyedNV = NULL;
#endif
#ifdef glPresentFrameDualFillNV
glPresentFrameDualFillNVFunc _glPresentFrameDualFillNV = NULL;
#endif
#ifdef glGetVideoivNV
glGetVideoivNVFunc _glGetVideoivNV = NULL;
#endif
#ifdef glGetVideouivNV
glGetVideouivNVFunc _glGetVideouivNV = NULL;
#endif
#ifdef glGetVideoi64vNV
glGetVideoi64vNVFunc _glGetVideoi64vNV = NULL;
#endif
#ifdef glGetVideoui64vNV
glGetVideoui64vNVFunc _glGetVideoui64vNV = NULL;
#endif
#ifdef glBeginTransformFeedbackEXT
glBeginTransformFeedbackEXTFunc _glBeginTransformFeedbackEXT = NULL;
#endif
#ifdef glEndTransformFeedbackEXT
glEndTransformFeedbackEXTFunc _glEndTransformFeedbackEXT = NULL;
#endif
#ifdef glBindBufferRangeEXT
glBindBufferRangeEXTFunc _glBindBufferRangeEXT = NULL;
#endif
#ifdef glBindBufferOffsetEXT
glBindBufferOffsetEXTFunc _glBindBufferOffsetEXT = NULL;
#endif
#ifdef glBindBufferBaseEXT
glBindBufferBaseEXTFunc _glBindBufferBaseEXT = NULL;
#endif
#ifdef glTransformFeedbackVaryingsEXT
glTransformFeedbackVaryingsEXTFunc _glTransformFeedbackVaryingsEXT = NULL;
#endif
#ifdef glGetTransformFeedbackVaryingEXT
glGetTransformFeedbackVaryingEXTFunc _glGetTransformFeedbackVaryingEXT = NULL;
#endif
#ifdef glClientAttribDefaultEXT
glClientAttribDefaultEXTFunc _glClientAttribDefaultEXT = NULL;
#endif
#ifdef glPushClientAttribDefaultEXT
glPushClientAttribDefaultEXTFunc _glPushClientAttribDefaultEXT = NULL;
#endif
#ifdef glMatrixLoadfEXT
glMatrixLoadfEXTFunc _glMatrixLoadfEXT = NULL;
#endif
#ifdef glMatrixLoaddEXT
glMatrixLoaddEXTFunc _glMatrixLoaddEXT = NULL;
#endif
#ifdef glMatrixMultfEXT
glMatrixMultfEXTFunc _glMatrixMultfEXT = NULL;
#endif
#ifdef glMatrixMultdEXT
glMatrixMultdEXTFunc _glMatrixMultdEXT = NULL;
#endif
#ifdef glMatrixLoadIdentityEXT
glMatrixLoadIdentityEXTFunc _glMatrixLoadIdentityEXT = NULL;
#endif
#ifdef glMatrixRotatefEXT
glMatrixRotatefEXTFunc _glMatrixRotatefEXT = NULL;
#endif
#ifdef glMatrixRotatedEXT
glMatrixRotatedEXTFunc _glMatrixRotatedEXT = NULL;
#endif
#ifdef glMatrixScalefEXT
glMatrixScalefEXTFunc _glMatrixScalefEXT = NULL;
#endif
#ifdef glMatrixScaledEXT
glMatrixScaledEXTFunc _glMatrixScaledEXT = NULL;
#endif
#ifdef glMatrixTranslatefEXT
glMatrixTranslatefEXTFunc _glMatrixTranslatefEXT = NULL;
#endif
#ifdef glMatrixTranslatedEXT
glMatrixTranslatedEXTFunc _glMatrixTranslatedEXT = NULL;
#endif
#ifdef glMatrixFrustumEXT
glMatrixFrustumEXTFunc _glMatrixFrustumEXT = NULL;
#endif
#ifdef glMatrixOrthoEXT
glMatrixOrthoEXTFunc _glMatrixOrthoEXT = NULL;
#endif
#ifdef glMatrixPopEXT
glMatrixPopEXTFunc _glMatrixPopEXT = NULL;
#endif
#ifdef glMatrixPushEXT
glMatrixPushEXTFunc _glMatrixPushEXT = NULL;
#endif
#ifdef glMatrixLoadTransposefEXT
glMatrixLoadTransposefEXTFunc _glMatrixLoadTransposefEXT = NULL;
#endif
#ifdef glMatrixLoadTransposedEXT
glMatrixLoadTransposedEXTFunc _glMatrixLoadTransposedEXT = NULL;
#endif
#ifdef glMatrixMultTransposefEXT
glMatrixMultTransposefEXTFunc _glMatrixMultTransposefEXT = NULL;
#endif
#ifdef glMatrixMultTransposedEXT
glMatrixMultTransposedEXTFunc _glMatrixMultTransposedEXT = NULL;
#endif
#ifdef glTextureParameterfEXT
glTextureParameterfEXTFunc _glTextureParameterfEXT = NULL;
#endif
#ifdef glTextureParameterfvEXT
glTextureParameterfvEXTFunc _glTextureParameterfvEXT = NULL;
#endif
#ifdef glTextureParameteriEXT
glTextureParameteriEXTFunc _glTextureParameteriEXT = NULL;
#endif
#ifdef glTextureParameterivEXT
glTextureParameterivEXTFunc _glTextureParameterivEXT = NULL;
#endif
#ifdef glTextureImage1DEXT
glTextureImage1DEXTFunc _glTextureImage1DEXT = NULL;
#endif
#ifdef glTextureImage2DEXT
glTextureImage2DEXTFunc _glTextureImage2DEXT = NULL;
#endif
#ifdef glTextureSubImage1DEXT
glTextureSubImage1DEXTFunc _glTextureSubImage1DEXT = NULL;
#endif
#ifdef glTextureSubImage2DEXT
glTextureSubImage2DEXTFunc _glTextureSubImage2DEXT = NULL;
#endif
#ifdef glCopyTextureImage1DEXT
glCopyTextureImage1DEXTFunc _glCopyTextureImage1DEXT = NULL;
#endif
#ifdef glCopyTextureImage2DEXT
glCopyTextureImage2DEXTFunc _glCopyTextureImage2DEXT = NULL;
#endif
#ifdef glCopyTextureSubImage1DEXT
glCopyTextureSubImage1DEXTFunc _glCopyTextureSubImage1DEXT = NULL;
#endif
#ifdef glCopyTextureSubImage2DEXT
glCopyTextureSubImage2DEXTFunc _glCopyTextureSubImage2DEXT = NULL;
#endif
#ifdef glGetTextureImageEXT
glGetTextureImageEXTFunc _glGetTextureImageEXT = NULL;
#endif
#ifdef glGetTextureParameterfvEXT
glGetTextureParameterfvEXTFunc _glGetTextureParameterfvEXT = NULL;
#endif
#ifdef glGetTextureParameterivEXT
glGetTextureParameterivEXTFunc _glGetTextureParameterivEXT = NULL;
#endif
#ifdef glGetTextureLevelParameterfvEXT
glGetTextureLevelParameterfvEXTFunc _glGetTextureLevelParameterfvEXT = NULL;
#endif
#ifdef glGetTextureLevelParameterivEXT
glGetTextureLevelParameterivEXTFunc _glGetTextureLevelParameterivEXT = NULL;
#endif
#ifdef glTextureImage3DEXT
glTextureImage3DEXTFunc _glTextureImage3DEXT = NULL;
#endif
#ifdef glTextureSubImage3DEXT
glTextureSubImage3DEXTFunc _glTextureSubImage3DEXT = NULL;
#endif
#ifdef glCopyTextureSubImage3DEXT
glCopyTextureSubImage3DEXTFunc _glCopyTextureSubImage3DEXT = NULL;
#endif
#ifdef glMultiTexParameterfEXT
glMultiTexParameterfEXTFunc _glMultiTexParameterfEXT = NULL;
#endif
#ifdef glMultiTexParameterfvEXT
glMultiTexParameterfvEXTFunc _glMultiTexParameterfvEXT = NULL;
#endif
#ifdef glMultiTexParameteriEXT
glMultiTexParameteriEXTFunc _glMultiTexParameteriEXT = NULL;
#endif
#ifdef glMultiTexParameterivEXT
glMultiTexParameterivEXTFunc _glMultiTexParameterivEXT = NULL;
#endif
#ifdef glMultiTexImage1DEXT
glMultiTexImage1DEXTFunc _glMultiTexImage1DEXT = NULL;
#endif
#ifdef glMultiTexImage2DEXT
glMultiTexImage2DEXTFunc _glMultiTexImage2DEXT = NULL;
#endif
#ifdef glMultiTexSubImage1DEXT
glMultiTexSubImage1DEXTFunc _glMultiTexSubImage1DEXT = NULL;
#endif
#ifdef glMultiTexSubImage2DEXT
glMultiTexSubImage2DEXTFunc _glMultiTexSubImage2DEXT = NULL;
#endif
#ifdef glCopyMultiTexImage1DEXT
glCopyMultiTexImage1DEXTFunc _glCopyMultiTexImage1DEXT = NULL;
#endif
#ifdef glCopyMultiTexImage2DEXT
glCopyMultiTexImage2DEXTFunc _glCopyMultiTexImage2DEXT = NULL;
#endif
#ifdef glCopyMultiTexSubImage1DEXT
glCopyMultiTexSubImage1DEXTFunc _glCopyMultiTexSubImage1DEXT = NULL;
#endif
#ifdef glCopyMultiTexSubImage2DEXT
glCopyMultiTexSubImage2DEXTFunc _glCopyMultiTexSubImage2DEXT = NULL;
#endif
#ifdef glGetMultiTexImageEXT
glGetMultiTexImageEXTFunc _glGetMultiTexImageEXT = NULL;
#endif
#ifdef glGetMultiTexParameterfvEXT
glGetMultiTexParameterfvEXTFunc _glGetMultiTexParameterfvEXT = NULL;
#endif
#ifdef glGetMultiTexParameterivEXT
glGetMultiTexParameterivEXTFunc _glGetMultiTexParameterivEXT = NULL;
#endif
#ifdef glGetMultiTexLevelParameterfvEXT
glGetMultiTexLevelParameterfvEXTFunc _glGetMultiTexLevelParameterfvEXT = NULL;
#endif
#ifdef glGetMultiTexLevelParameterivEXT
glGetMultiTexLevelParameterivEXTFunc _glGetMultiTexLevelParameterivEXT = NULL;
#endif
#ifdef glMultiTexImage3DEXT
glMultiTexImage3DEXTFunc _glMultiTexImage3DEXT = NULL;
#endif
#ifdef glMultiTexSubImage3DEXT
glMultiTexSubImage3DEXTFunc _glMultiTexSubImage3DEXT = NULL;
#endif
#ifdef glCopyMultiTexSubImage3DEXT
glCopyMultiTexSubImage3DEXTFunc _glCopyMultiTexSubImage3DEXT = NULL;
#endif
#ifdef glBindMultiTextureEXT
glBindMultiTextureEXTFunc _glBindMultiTextureEXT = NULL;
#endif
#ifdef glEnableClientStateIndexedEXT
glEnableClientStateIndexedEXTFunc _glEnableClientStateIndexedEXT = NULL;
#endif
#ifdef glDisableClientStateIndexedEXT
glDisableClientStateIndexedEXTFunc _glDisableClientStateIndexedEXT = NULL;
#endif
#ifdef glMultiTexCoordPointerEXT
glMultiTexCoordPointerEXTFunc _glMultiTexCoordPointerEXT = NULL;
#endif
#ifdef glMultiTexEnvfEXT
glMultiTexEnvfEXTFunc _glMultiTexEnvfEXT = NULL;
#endif
#ifdef glMultiTexEnvfvEXT
glMultiTexEnvfvEXTFunc _glMultiTexEnvfvEXT = NULL;
#endif
#ifdef glMultiTexEnviEXT
glMultiTexEnviEXTFunc _glMultiTexEnviEXT = NULL;
#endif
#ifdef glMultiTexEnvivEXT
glMultiTexEnvivEXTFunc _glMultiTexEnvivEXT = NULL;
#endif
#ifdef glMultiTexGendEXT
glMultiTexGendEXTFunc _glMultiTexGendEXT = NULL;
#endif
#ifdef glMultiTexGendvEXT
glMultiTexGendvEXTFunc _glMultiTexGendvEXT = NULL;
#endif
#ifdef glMultiTexGenfEXT
glMultiTexGenfEXTFunc _glMultiTexGenfEXT = NULL;
#endif
#ifdef glMultiTexGenfvEXT
glMultiTexGenfvEXTFunc _glMultiTexGenfvEXT = NULL;
#endif
#ifdef glMultiTexGeniEXT
glMultiTexGeniEXTFunc _glMultiTexGeniEXT = NULL;
#endif
#ifdef glMultiTexGenivEXT
glMultiTexGenivEXTFunc _glMultiTexGenivEXT = NULL;
#endif
#ifdef glGetMultiTexEnvfvEXT
glGetMultiTexEnvfvEXTFunc _glGetMultiTexEnvfvEXT = NULL;
#endif
#ifdef glGetMultiTexEnvivEXT
glGetMultiTexEnvivEXTFunc _glGetMultiTexEnvivEXT = NULL;
#endif
#ifdef glGetMultiTexGendvEXT
glGetMultiTexGendvEXTFunc _glGetMultiTexGendvEXT = NULL;
#endif
#ifdef glGetMultiTexGenfvEXT
glGetMultiTexGenfvEXTFunc _glGetMultiTexGenfvEXT = NULL;
#endif
#ifdef glGetMultiTexGenivEXT
glGetMultiTexGenivEXTFunc _glGetMultiTexGenivEXT = NULL;
#endif
#ifdef glGetFloatIndexedvEXT
glGetFloatIndexedvEXTFunc _glGetFloatIndexedvEXT = NULL;
#endif
#ifdef glGetDoubleIndexedvEXT
glGetDoubleIndexedvEXTFunc _glGetDoubleIndexedvEXT = NULL;
#endif
#ifdef glGetPointerIndexedvEXT
glGetPointerIndexedvEXTFunc _glGetPointerIndexedvEXT = NULL;
#endif
#ifdef glCompressedTextureImage3DEXT
glCompressedTextureImage3DEXTFunc _glCompressedTextureImage3DEXT = NULL;
#endif
#ifdef glCompressedTextureImage2DEXT
glCompressedTextureImage2DEXTFunc _glCompressedTextureImage2DEXT = NULL;
#endif
#ifdef glCompressedTextureImage1DEXT
glCompressedTextureImage1DEXTFunc _glCompressedTextureImage1DEXT = NULL;
#endif
#ifdef glCompressedTextureSubImage3DEXT
glCompressedTextureSubImage3DEXTFunc _glCompressedTextureSubImage3DEXT = NULL;
#endif
#ifdef glCompressedTextureSubImage2DEXT
glCompressedTextureSubImage2DEXTFunc _glCompressedTextureSubImage2DEXT = NULL;
#endif
#ifdef glCompressedTextureSubImage1DEXT
glCompressedTextureSubImage1DEXTFunc _glCompressedTextureSubImage1DEXT = NULL;
#endif
#ifdef glGetCompressedTextureImageEXT
glGetCompressedTextureImageEXTFunc _glGetCompressedTextureImageEXT = NULL;
#endif
#ifdef glCompressedMultiTexImage3DEXT
glCompressedMultiTexImage3DEXTFunc _glCompressedMultiTexImage3DEXT = NULL;
#endif
#ifdef glCompressedMultiTexImage2DEXT
glCompressedMultiTexImage2DEXTFunc _glCompressedMultiTexImage2DEXT = NULL;
#endif
#ifdef glCompressedMultiTexImage1DEXT
glCompressedMultiTexImage1DEXTFunc _glCompressedMultiTexImage1DEXT = NULL;
#endif
#ifdef glCompressedMultiTexSubImage3DEXT
glCompressedMultiTexSubImage3DEXTFunc _glCompressedMultiTexSubImage3DEXT = NULL;
#endif
#ifdef glCompressedMultiTexSubImage2DEXT
glCompressedMultiTexSubImage2DEXTFunc _glCompressedMultiTexSubImage2DEXT = NULL;
#endif
#ifdef glCompressedMultiTexSubImage1DEXT
glCompressedMultiTexSubImage1DEXTFunc _glCompressedMultiTexSubImage1DEXT = NULL;
#endif
#ifdef glGetCompressedMultiTexImageEXT
glGetCompressedMultiTexImageEXTFunc _glGetCompressedMultiTexImageEXT = NULL;
#endif
#ifdef glNamedProgramStringEXT
glNamedProgramStringEXTFunc _glNamedProgramStringEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameter4dEXT
glNamedProgramLocalParameter4dEXTFunc _glNamedProgramLocalParameter4dEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameter4dvEXT
glNamedProgramLocalParameter4dvEXTFunc _glNamedProgramLocalParameter4dvEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameter4fEXT
glNamedProgramLocalParameter4fEXTFunc _glNamedProgramLocalParameter4fEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameter4fvEXT
glNamedProgramLocalParameter4fvEXTFunc _glNamedProgramLocalParameter4fvEXT = NULL;
#endif
#ifdef glGetNamedProgramLocalParameterdvEXT
glGetNamedProgramLocalParameterdvEXTFunc _glGetNamedProgramLocalParameterdvEXT = NULL;
#endif
#ifdef glGetNamedProgramLocalParameterfvEXT
glGetNamedProgramLocalParameterfvEXTFunc _glGetNamedProgramLocalParameterfvEXT = NULL;
#endif
#ifdef glGetNamedProgramivEXT
glGetNamedProgramivEXTFunc _glGetNamedProgramivEXT = NULL;
#endif
#ifdef glGetNamedProgramStringEXT
glGetNamedProgramStringEXTFunc _glGetNamedProgramStringEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameters4fvEXT
glNamedProgramLocalParameters4fvEXTFunc _glNamedProgramLocalParameters4fvEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameterI4iEXT
glNamedProgramLocalParameterI4iEXTFunc _glNamedProgramLocalParameterI4iEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameterI4ivEXT
glNamedProgramLocalParameterI4ivEXTFunc _glNamedProgramLocalParameterI4ivEXT = NULL;
#endif
#ifdef glNamedProgramLocalParametersI4ivEXT
glNamedProgramLocalParametersI4ivEXTFunc _glNamedProgramLocalParametersI4ivEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameterI4uiEXT
glNamedProgramLocalParameterI4uiEXTFunc _glNamedProgramLocalParameterI4uiEXT = NULL;
#endif
#ifdef glNamedProgramLocalParameterI4uivEXT
glNamedProgramLocalParameterI4uivEXTFunc _glNamedProgramLocalParameterI4uivEXT = NULL;
#endif
#ifdef glNamedProgramLocalParametersI4uivEXT
glNamedProgramLocalParametersI4uivEXTFunc _glNamedProgramLocalParametersI4uivEXT = NULL;
#endif
#ifdef glGetNamedProgramLocalParameterIivEXT
glGetNamedProgramLocalParameterIivEXTFunc _glGetNamedProgramLocalParameterIivEXT = NULL;
#endif
#ifdef glGetNamedProgramLocalParameterIuivEXT
glGetNamedProgramLocalParameterIuivEXTFunc _glGetNamedProgramLocalParameterIuivEXT = NULL;
#endif
#ifdef glTextureParameterIivEXT
glTextureParameterIivEXTFunc _glTextureParameterIivEXT = NULL;
#endif
#ifdef glTextureParameterIuivEXT
glTextureParameterIuivEXTFunc _glTextureParameterIuivEXT = NULL;
#endif
#ifdef glGetTextureParameterIivEXT
glGetTextureParameterIivEXTFunc _glGetTextureParameterIivEXT = NULL;
#endif
#ifdef glGetTextureParameterIuivEXT
glGetTextureParameterIuivEXTFunc _glGetTextureParameterIuivEXT = NULL;
#endif
#ifdef glMultiTexParameterIivEXT
glMultiTexParameterIivEXTFunc _glMultiTexParameterIivEXT = NULL;
#endif
#ifdef glMultiTexParameterIuivEXT
glMultiTexParameterIuivEXTFunc _glMultiTexParameterIuivEXT = NULL;
#endif
#ifdef glGetMultiTexParameterIivEXT
glGetMultiTexParameterIivEXTFunc _glGetMultiTexParameterIivEXT = NULL;
#endif
#ifdef glGetMultiTexParameterIuivEXT
glGetMultiTexParameterIuivEXTFunc _glGetMultiTexParameterIuivEXT = NULL;
#endif
#ifdef glProgramUniform1fEXT
glProgramUniform1fEXTFunc _glProgramUniform1fEXT = NULL;
#endif
#ifdef glProgramUniform2fEXT
glProgramUniform2fEXTFunc _glProgramUniform2fEXT = NULL;
#endif
#ifdef glProgramUniform3fEXT
glProgramUniform3fEXTFunc _glProgramUniform3fEXT = NULL;
#endif
#ifdef glProgramUniform4fEXT
glProgramUniform4fEXTFunc _glProgramUniform4fEXT = NULL;
#endif
#ifdef glProgramUniform1iEXT
glProgramUniform1iEXTFunc _glProgramUniform1iEXT = NULL;
#endif
#ifdef glProgramUniform2iEXT
glProgramUniform2iEXTFunc _glProgramUniform2iEXT = NULL;
#endif
#ifdef glProgramUniform3iEXT
glProgramUniform3iEXTFunc _glProgramUniform3iEXT = NULL;
#endif
#ifdef glProgramUniform4iEXT
glProgramUniform4iEXTFunc _glProgramUniform4iEXT = NULL;
#endif
#ifdef glProgramUniform1fvEXT
glProgramUniform1fvEXTFunc _glProgramUniform1fvEXT = NULL;
#endif
#ifdef glProgramUniform2fvEXT
glProgramUniform2fvEXTFunc _glProgramUniform2fvEXT = NULL;
#endif
#ifdef glProgramUniform3fvEXT
glProgramUniform3fvEXTFunc _glProgramUniform3fvEXT = NULL;
#endif
#ifdef glProgramUniform4fvEXT
glProgramUniform4fvEXTFunc _glProgramUniform4fvEXT = NULL;
#endif
#ifdef glProgramUniform1ivEXT
glProgramUniform1ivEXTFunc _glProgramUniform1ivEXT = NULL;
#endif
#ifdef glProgramUniform2ivEXT
glProgramUniform2ivEXTFunc _glProgramUniform2ivEXT = NULL;
#endif
#ifdef glProgramUniform3ivEXT
glProgramUniform3ivEXTFunc _glProgramUniform3ivEXT = NULL;
#endif
#ifdef glProgramUniform4ivEXT
glProgramUniform4ivEXTFunc _glProgramUniform4ivEXT = NULL;
#endif
#ifdef glProgramUniformMatrix2fvEXT
glProgramUniformMatrix2fvEXTFunc _glProgramUniformMatrix2fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix3fvEXT
glProgramUniformMatrix3fvEXTFunc _glProgramUniformMatrix3fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix4fvEXT
glProgramUniformMatrix4fvEXTFunc _glProgramUniformMatrix4fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix2x3fvEXT
glProgramUniformMatrix2x3fvEXTFunc _glProgramUniformMatrix2x3fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix3x2fvEXT
glProgramUniformMatrix3x2fvEXTFunc _glProgramUniformMatrix3x2fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix2x4fvEXT
glProgramUniformMatrix2x4fvEXTFunc _glProgramUniformMatrix2x4fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix4x2fvEXT
glProgramUniformMatrix4x2fvEXTFunc _glProgramUniformMatrix4x2fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix3x4fvEXT
glProgramUniformMatrix3x4fvEXTFunc _glProgramUniformMatrix3x4fvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix4x3fvEXT
glProgramUniformMatrix4x3fvEXTFunc _glProgramUniformMatrix4x3fvEXT = NULL;
#endif
#ifdef glProgramUniform1uiEXT
glProgramUniform1uiEXTFunc _glProgramUniform1uiEXT = NULL;
#endif
#ifdef glProgramUniform2uiEXT
glProgramUniform2uiEXTFunc _glProgramUniform2uiEXT = NULL;
#endif
#ifdef glProgramUniform3uiEXT
glProgramUniform3uiEXTFunc _glProgramUniform3uiEXT = NULL;
#endif
#ifdef glProgramUniform4uiEXT
glProgramUniform4uiEXTFunc _glProgramUniform4uiEXT = NULL;
#endif
#ifdef glProgramUniform1uivEXT
glProgramUniform1uivEXTFunc _glProgramUniform1uivEXT = NULL;
#endif
#ifdef glProgramUniform2uivEXT
glProgramUniform2uivEXTFunc _glProgramUniform2uivEXT = NULL;
#endif
#ifdef glProgramUniform3uivEXT
glProgramUniform3uivEXTFunc _glProgramUniform3uivEXT = NULL;
#endif
#ifdef glProgramUniform4uivEXT
glProgramUniform4uivEXTFunc _glProgramUniform4uivEXT = NULL;
#endif
#ifdef glNamedBufferDataEXT
glNamedBufferDataEXTFunc _glNamedBufferDataEXT = NULL;
#endif
#ifdef glNamedBufferSubDataEXT
glNamedBufferSubDataEXTFunc _glNamedBufferSubDataEXT = NULL;
#endif
#ifdef glMapNamedBufferEXT
glMapNamedBufferEXTFunc _glMapNamedBufferEXT = NULL;
#endif
#ifdef glUnmapNamedBufferEXT
glUnmapNamedBufferEXTFunc _glUnmapNamedBufferEXT = NULL;
#endif
#ifdef glMapNamedBufferRangeEXT
glMapNamedBufferRangeEXTFunc _glMapNamedBufferRangeEXT = NULL;
#endif
#ifdef glFlushMappedNamedBufferRangeEXT
glFlushMappedNamedBufferRangeEXTFunc _glFlushMappedNamedBufferRangeEXT = NULL;
#endif
#ifdef glNamedCopyBufferSubDataEXT
glNamedCopyBufferSubDataEXTFunc _glNamedCopyBufferSubDataEXT = NULL;
#endif
#ifdef glGetNamedBufferParameterivEXT
glGetNamedBufferParameterivEXTFunc _glGetNamedBufferParameterivEXT = NULL;
#endif
#ifdef glGetNamedBufferPointervEXT
glGetNamedBufferPointervEXTFunc _glGetNamedBufferPointervEXT = NULL;
#endif
#ifdef glGetNamedBufferSubDataEXT
glGetNamedBufferSubDataEXTFunc _glGetNamedBufferSubDataEXT = NULL;
#endif
#ifdef glTextureBufferEXT
glTextureBufferEXTFunc _glTextureBufferEXT = NULL;
#endif
#ifdef glMultiTexBufferEXT
glMultiTexBufferEXTFunc _glMultiTexBufferEXT = NULL;
#endif
#ifdef glNamedRenderbufferStorageEXT
glNamedRenderbufferStorageEXTFunc _glNamedRenderbufferStorageEXT = NULL;
#endif
#ifdef glGetNamedRenderbufferParameterivEXT
glGetNamedRenderbufferParameterivEXTFunc _glGetNamedRenderbufferParameterivEXT = NULL;
#endif
#ifdef glCheckNamedFramebufferStatusEXT
glCheckNamedFramebufferStatusEXTFunc _glCheckNamedFramebufferStatusEXT = NULL;
#endif
#ifdef glNamedFramebufferTexture1DEXT
glNamedFramebufferTexture1DEXTFunc _glNamedFramebufferTexture1DEXT = NULL;
#endif
#ifdef glNamedFramebufferTexture2DEXT
glNamedFramebufferTexture2DEXTFunc _glNamedFramebufferTexture2DEXT = NULL;
#endif
#ifdef glNamedFramebufferTexture3DEXT
glNamedFramebufferTexture3DEXTFunc _glNamedFramebufferTexture3DEXT = NULL;
#endif
#ifdef glNamedFramebufferRenderbufferEXT
glNamedFramebufferRenderbufferEXTFunc _glNamedFramebufferRenderbufferEXT = NULL;
#endif
#ifdef glGetNamedFramebufferAttachmentParameterivEXT
glGetNamedFramebufferAttachmentParameterivEXTFunc _glGetNamedFramebufferAttachmentParameterivEXT = NULL;
#endif
#ifdef glGenerateTextureMipmapEXT
glGenerateTextureMipmapEXTFunc _glGenerateTextureMipmapEXT = NULL;
#endif
#ifdef glGenerateMultiTexMipmapEXT
glGenerateMultiTexMipmapEXTFunc _glGenerateMultiTexMipmapEXT = NULL;
#endif
#ifdef glFramebufferDrawBufferEXT
glFramebufferDrawBufferEXTFunc _glFramebufferDrawBufferEXT = NULL;
#endif
#ifdef glFramebufferDrawBuffersEXT
glFramebufferDrawBuffersEXTFunc _glFramebufferDrawBuffersEXT = NULL;
#endif
#ifdef glFramebufferReadBufferEXT
glFramebufferReadBufferEXTFunc _glFramebufferReadBufferEXT = NULL;
#endif
#ifdef glGetFramebufferParameterivEXT
glGetFramebufferParameterivEXTFunc _glGetFramebufferParameterivEXT = NULL;
#endif
#ifdef glNamedRenderbufferStorageMultisampleEXT
glNamedRenderbufferStorageMultisampleEXTFunc _glNamedRenderbufferStorageMultisampleEXT = NULL;
#endif
#ifdef glNamedRenderbufferStorageMultisampleCoverageEXT
glNamedRenderbufferStorageMultisampleCoverageEXTFunc _glNamedRenderbufferStorageMultisampleCoverageEXT = NULL;
#endif
#ifdef glNamedFramebufferTextureEXT
glNamedFramebufferTextureEXTFunc _glNamedFramebufferTextureEXT = NULL;
#endif
#ifdef glNamedFramebufferTextureLayerEXT
glNamedFramebufferTextureLayerEXTFunc _glNamedFramebufferTextureLayerEXT = NULL;
#endif
#ifdef glNamedFramebufferTextureFaceEXT
glNamedFramebufferTextureFaceEXTFunc _glNamedFramebufferTextureFaceEXT = NULL;
#endif
#ifdef glTextureRenderbufferEXT
glTextureRenderbufferEXTFunc _glTextureRenderbufferEXT = NULL;
#endif
#ifdef glMultiTexRenderbufferEXT
glMultiTexRenderbufferEXTFunc _glMultiTexRenderbufferEXT = NULL;
#endif
#ifdef glProgramUniform1dEXT
glProgramUniform1dEXTFunc _glProgramUniform1dEXT = NULL;
#endif
#ifdef glProgramUniform2dEXT
glProgramUniform2dEXTFunc _glProgramUniform2dEXT = NULL;
#endif
#ifdef glProgramUniform3dEXT
glProgramUniform3dEXTFunc _glProgramUniform3dEXT = NULL;
#endif
#ifdef glProgramUniform4dEXT
glProgramUniform4dEXTFunc _glProgramUniform4dEXT = NULL;
#endif
#ifdef glProgramUniform1dvEXT
glProgramUniform1dvEXTFunc _glProgramUniform1dvEXT = NULL;
#endif
#ifdef glProgramUniform2dvEXT
glProgramUniform2dvEXTFunc _glProgramUniform2dvEXT = NULL;
#endif
#ifdef glProgramUniform3dvEXT
glProgramUniform3dvEXTFunc _glProgramUniform3dvEXT = NULL;
#endif
#ifdef glProgramUniform4dvEXT
glProgramUniform4dvEXTFunc _glProgramUniform4dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix2dvEXT
glProgramUniformMatrix2dvEXTFunc _glProgramUniformMatrix2dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix3dvEXT
glProgramUniformMatrix3dvEXTFunc _glProgramUniformMatrix3dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix4dvEXT
glProgramUniformMatrix4dvEXTFunc _glProgramUniformMatrix4dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix2x3dvEXT
glProgramUniformMatrix2x3dvEXTFunc _glProgramUniformMatrix2x3dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix2x4dvEXT
glProgramUniformMatrix2x4dvEXTFunc _glProgramUniformMatrix2x4dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix3x2dvEXT
glProgramUniformMatrix3x2dvEXTFunc _glProgramUniformMatrix3x2dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix3x4dvEXT
glProgramUniformMatrix3x4dvEXTFunc _glProgramUniformMatrix3x4dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix4x2dvEXT
glProgramUniformMatrix4x2dvEXTFunc _glProgramUniformMatrix4x2dvEXT = NULL;
#endif
#ifdef glProgramUniformMatrix4x3dvEXT
glProgramUniformMatrix4x3dvEXTFunc _glProgramUniformMatrix4x3dvEXT = NULL;
#endif
#ifdef glGetMultisamplefvNV
glGetMultisamplefvNVFunc _glGetMultisamplefvNV = NULL;
#endif
#ifdef glSampleMaskIndexedNV
glSampleMaskIndexedNVFunc _glSampleMaskIndexedNV = NULL;
#endif
#ifdef glTexRenderbufferNV
glTexRenderbufferNVFunc _glTexRenderbufferNV = NULL;
#endif
#ifdef glBindTransformFeedbackNV
glBindTransformFeedbackNVFunc _glBindTransformFeedbackNV = NULL;
#endif
#ifdef glDeleteTransformFeedbacksNV
glDeleteTransformFeedbacksNVFunc _glDeleteTransformFeedbacksNV = NULL;
#endif
#ifdef glGenTransformFeedbacksNV
glGenTransformFeedbacksNVFunc _glGenTransformFeedbacksNV = NULL;
#endif
#ifdef glIsTransformFeedbackNV
glIsTransformFeedbackNVFunc _glIsTransformFeedbackNV = NULL;
#endif
#ifdef glPauseTransformFeedbackNV
glPauseTransformFeedbackNVFunc _glPauseTransformFeedbackNV = NULL;
#endif
#ifdef glResumeTransformFeedbackNV
glResumeTransformFeedbackNVFunc _glResumeTransformFeedbackNV = NULL;
#endif
#ifdef glDrawTransformFeedbackNV
glDrawTransformFeedbackNVFunc _glDrawTransformFeedbackNV = NULL;
#endif
#ifdef glGetPerfMonitorGroupsAMD
glGetPerfMonitorGroupsAMDFunc _glGetPerfMonitorGroupsAMD = NULL;
#endif
#ifdef glGetPerfMonitorCountersAMD
glGetPerfMonitorCountersAMDFunc _glGetPerfMonitorCountersAMD = NULL;
#endif
#ifdef glGetPerfMonitorGroupStringAMD
glGetPerfMonitorGroupStringAMDFunc _glGetPerfMonitorGroupStringAMD = NULL;
#endif
#ifdef glGetPerfMonitorCounterStringAMD
glGetPerfMonitorCounterStringAMDFunc _glGetPerfMonitorCounterStringAMD = NULL;
#endif
#ifdef glGetPerfMonitorCounterInfoAMD
glGetPerfMonitorCounterInfoAMDFunc _glGetPerfMonitorCounterInfoAMD = NULL;
#endif
#ifdef glGenPerfMonitorsAMD
glGenPerfMonitorsAMDFunc _glGenPerfMonitorsAMD = NULL;
#endif
#ifdef glDeletePerfMonitorsAMD
glDeletePerfMonitorsAMDFunc _glDeletePerfMonitorsAMD = NULL;
#endif
#ifdef glSelectPerfMonitorCountersAMD
glSelectPerfMonitorCountersAMDFunc _glSelectPerfMonitorCountersAMD = NULL;
#endif
#ifdef glBeginPerfMonitorAMD
glBeginPerfMonitorAMDFunc _glBeginPerfMonitorAMD = NULL;
#endif
#ifdef glEndPerfMonitorAMD
glEndPerfMonitorAMDFunc _glEndPerfMonitorAMD = NULL;
#endif
#ifdef glGetPerfMonitorCounterDataAMD
glGetPerfMonitorCounterDataAMDFunc _glGetPerfMonitorCounterDataAMD = NULL;
#endif
#ifdef glTessellationFactorAMD
glTessellationFactorAMDFunc _glTessellationFactorAMD = NULL;
#endif
#ifdef glTessellationModeAMD
glTessellationModeAMDFunc _glTessellationModeAMD = NULL;
#endif
#ifdef glProvokingVertexEXT
glProvokingVertexEXTFunc _glProvokingVertexEXT = NULL;
#endif
#ifdef glBlendFuncIndexedAMD
glBlendFuncIndexedAMDFunc _glBlendFuncIndexedAMD = NULL;
#endif
#ifdef glBlendFuncSeparateIndexedAMD
glBlendFuncSeparateIndexedAMDFunc _glBlendFuncSeparateIndexedAMD = NULL;
#endif
#ifdef glBlendEquationIndexedAMD
glBlendEquationIndexedAMDFunc _glBlendEquationIndexedAMD = NULL;
#endif
#ifdef glBlendEquationSeparateIndexedAMD
glBlendEquationSeparateIndexedAMDFunc _glBlendEquationSeparateIndexedAMD = NULL;
#endif
#ifdef glTextureRangeAPPLE
glTextureRangeAPPLEFunc _glTextureRangeAPPLE = NULL;
#endif
#ifdef glGetTexParameterPointervAPPLE
glGetTexParameterPointervAPPLEFunc _glGetTexParameterPointervAPPLE = NULL;
#endif
#ifdef glEnableVertexAttribAPPLE
glEnableVertexAttribAPPLEFunc _glEnableVertexAttribAPPLE = NULL;
#endif
#ifdef glDisableVertexAttribAPPLE
glDisableVertexAttribAPPLEFunc _glDisableVertexAttribAPPLE = NULL;
#endif
#ifdef glIsVertexAttribEnabledAPPLE
glIsVertexAttribEnabledAPPLEFunc _glIsVertexAttribEnabledAPPLE = NULL;
#endif
#ifdef glMapVertexAttrib1dAPPLE
glMapVertexAttrib1dAPPLEFunc _glMapVertexAttrib1dAPPLE = NULL;
#endif
#ifdef glMapVertexAttrib1fAPPLE
glMapVertexAttrib1fAPPLEFunc _glMapVertexAttrib1fAPPLE = NULL;
#endif
#ifdef glMapVertexAttrib2dAPPLE
glMapVertexAttrib2dAPPLEFunc _glMapVertexAttrib2dAPPLE = NULL;
#endif
#ifdef glMapVertexAttrib2fAPPLE
glMapVertexAttrib2fAPPLEFunc _glMapVertexAttrib2fAPPLE = NULL;
#endif
#ifdef glObjectPurgeableAPPLE
glObjectPurgeableAPPLEFunc _glObjectPurgeableAPPLE = NULL;
#endif
#ifdef glObjectUnpurgeableAPPLE
glObjectUnpurgeableAPPLEFunc _glObjectUnpurgeableAPPLE = NULL;
#endif
#ifdef glGetObjectParameterivAPPLE
glGetObjectParameterivAPPLEFunc _glGetObjectParameterivAPPLE = NULL;
#endif
#ifdef glBeginVideoCaptureNV
glBeginVideoCaptureNVFunc _glBeginVideoCaptureNV = NULL;
#endif
#ifdef glBindVideoCaptureStreamBufferNV
glBindVideoCaptureStreamBufferNVFunc _glBindVideoCaptureStreamBufferNV = NULL;
#endif
#ifdef glBindVideoCaptureStreamTextureNV
glBindVideoCaptureStreamTextureNVFunc _glBindVideoCaptureStreamTextureNV = NULL;
#endif
#ifdef glEndVideoCaptureNV
glEndVideoCaptureNVFunc _glEndVideoCaptureNV = NULL;
#endif
#ifdef glGetVideoCaptureivNV
glGetVideoCaptureivNVFunc _glGetVideoCaptureivNV = NULL;
#endif
#ifdef glGetVideoCaptureStreamivNV
glGetVideoCaptureStreamivNVFunc _glGetVideoCaptureStreamivNV = NULL;
#endif
#ifdef glGetVideoCaptureStreamfvNV
glGetVideoCaptureStreamfvNVFunc _glGetVideoCaptureStreamfvNV = NULL;
#endif
#ifdef glGetVideoCaptureStreamdvNV
glGetVideoCaptureStreamdvNVFunc _glGetVideoCaptureStreamdvNV = NULL;
#endif
#ifdef glVideoCaptureNV
glVideoCaptureNVFunc _glVideoCaptureNV = NULL;
#endif
#ifdef glVideoCaptureStreamParameterivNV
glVideoCaptureStreamParameterivNVFunc _glVideoCaptureStreamParameterivNV = NULL;
#endif
#ifdef glVideoCaptureStreamParameterfvNV
glVideoCaptureStreamParameterfvNVFunc _glVideoCaptureStreamParameterfvNV = NULL;
#endif
#ifdef glVideoCaptureStreamParameterdvNV
glVideoCaptureStreamParameterdvNVFunc _glVideoCaptureStreamParameterdvNV = NULL;
#endif
#ifdef glCopyImageSubDataNV
glCopyImageSubDataNVFunc _glCopyImageSubDataNV = NULL;
#endif
#ifdef glUseShaderProgramEXT
glUseShaderProgramEXTFunc _glUseShaderProgramEXT = NULL;
#endif
#ifdef glActiveProgramEXT
glActiveProgramEXTFunc _glActiveProgramEXT = NULL;
#endif
#ifdef glCreateShaderProgramEXT
glCreateShaderProgramEXTFunc _glCreateShaderProgramEXT = NULL;
#endif
#ifdef glMakeBufferResidentNV
glMakeBufferResidentNVFunc _glMakeBufferResidentNV = NULL;
#endif
#ifdef glMakeBufferNonResidentNV
glMakeBufferNonResidentNVFunc _glMakeBufferNonResidentNV = NULL;
#endif
#ifdef glIsBufferResidentNV
glIsBufferResidentNVFunc _glIsBufferResidentNV = NULL;
#endif
#ifdef glMakeNamedBufferResidentNV
glMakeNamedBufferResidentNVFunc _glMakeNamedBufferResidentNV = NULL;
#endif
#ifdef glMakeNamedBufferNonResidentNV
glMakeNamedBufferNonResidentNVFunc _glMakeNamedBufferNonResidentNV = NULL;
#endif
#ifdef glIsNamedBufferResidentNV
glIsNamedBufferResidentNVFunc _glIsNamedBufferResidentNV = NULL;
#endif
#ifdef glGetBufferParameterui64vNV
glGetBufferParameterui64vNVFunc _glGetBufferParameterui64vNV = NULL;
#endif
#ifdef glGetNamedBufferParameterui64vNV
glGetNamedBufferParameterui64vNVFunc _glGetNamedBufferParameterui64vNV = NULL;
#endif
#ifdef glGetIntegerui64vNV
glGetIntegerui64vNVFunc _glGetIntegerui64vNV = NULL;
#endif
#ifdef glUniformui64NV
glUniformui64NVFunc _glUniformui64NV = NULL;
#endif
#ifdef glUniformui64vNV
glUniformui64vNVFunc _glUniformui64vNV = NULL;
#endif
#ifdef glGetUniformui64vNV
glGetUniformui64vNVFunc _glGetUniformui64vNV = NULL;
#endif
#ifdef glProgramUniformui64NV
glProgramUniformui64NVFunc _glProgramUniformui64NV = NULL;
#endif
#ifdef glProgramUniformui64vNV
glProgramUniformui64vNVFunc _glProgramUniformui64vNV = NULL;
#endif
#ifdef glBufferAddressRangeNV
glBufferAddressRangeNVFunc _glBufferAddressRangeNV = NULL;
#endif
#ifdef glVertexFormatNV
glVertexFormatNVFunc _glVertexFormatNV = NULL;
#endif
#ifdef glNormalFormatNV
glNormalFormatNVFunc _glNormalFormatNV = NULL;
#endif
#ifdef glColorFormatNV
glColorFormatNVFunc _glColorFormatNV = NULL;
#endif
#ifdef glIndexFormatNV
glIndexFormatNVFunc _glIndexFormatNV = NULL;
#endif
#ifdef glTexCoordFormatNV
glTexCoordFormatNVFunc _glTexCoordFormatNV = NULL;
#endif
#ifdef glEdgeFlagFormatNV
glEdgeFlagFormatNVFunc _glEdgeFlagFormatNV = NULL;
#endif
#ifdef glSecondaryColorFormatNV
glSecondaryColorFormatNVFunc _glSecondaryColorFormatNV = NULL;
#endif
#ifdef glFogCoordFormatNV
glFogCoordFormatNVFunc _glFogCoordFormatNV = NULL;
#endif
#ifdef glVertexAttribFormatNV
glVertexAttribFormatNVFunc _glVertexAttribFormatNV = NULL;
#endif
#ifdef glVertexAttribIFormatNV
glVertexAttribIFormatNVFunc _glVertexAttribIFormatNV = NULL;
#endif
#ifdef glGetIntegerui64i_vNV
glGetIntegerui64i_vNVFunc _glGetIntegerui64i_vNV = NULL;
#endif
#ifdef glTextureBarrierNV
glTextureBarrierNVFunc _glTextureBarrierNV = NULL;
#endif
#ifdef glBindImageTextureEXT
glBindImageTextureEXTFunc _glBindImageTextureEXT = NULL;
#endif
#ifdef glMemoryBarrierEXT
glMemoryBarrierEXTFunc _glMemoryBarrierEXT = NULL;
#endif
#ifdef glVertexAttribL1dEXT
glVertexAttribL1dEXTFunc _glVertexAttribL1dEXT = NULL;
#endif
#ifdef glVertexAttribL2dEXT
glVertexAttribL2dEXTFunc _glVertexAttribL2dEXT = NULL;
#endif
#ifdef glVertexAttribL3dEXT
glVertexAttribL3dEXTFunc _glVertexAttribL3dEXT = NULL;
#endif
#ifdef glVertexAttribL4dEXT
glVertexAttribL4dEXTFunc _glVertexAttribL4dEXT = NULL;
#endif
#ifdef glVertexAttribL1dvEXT
glVertexAttribL1dvEXTFunc _glVertexAttribL1dvEXT = NULL;
#endif
#ifdef glVertexAttribL2dvEXT
glVertexAttribL2dvEXTFunc _glVertexAttribL2dvEXT = NULL;
#endif
#ifdef glVertexAttribL3dvEXT
glVertexAttribL3dvEXTFunc _glVertexAttribL3dvEXT = NULL;
#endif
#ifdef glVertexAttribL4dvEXT
glVertexAttribL4dvEXTFunc _glVertexAttribL4dvEXT = NULL;
#endif
#ifdef glVertexAttribLPointerEXT
glVertexAttribLPointerEXTFunc _glVertexAttribLPointerEXT = NULL;
#endif
#ifdef glGetVertexAttribLdvEXT
glGetVertexAttribLdvEXTFunc _glGetVertexAttribLdvEXT = NULL;
#endif
#ifdef glVertexArrayVertexAttribLOffsetEXT
glVertexArrayVertexAttribLOffsetEXTFunc _glVertexArrayVertexAttribLOffsetEXT = NULL;
#endif
#ifdef glProgramSubroutineParametersuivNV
glProgramSubroutineParametersuivNVFunc _glProgramSubroutineParametersuivNV = NULL;
#endif
#ifdef glGetProgramSubroutineParameteruivNV
glGetProgramSubroutineParameteruivNVFunc _glGetProgramSubroutineParameteruivNV = NULL;
#endif
#ifdef glUniform1i64NV
glUniform1i64NVFunc _glUniform1i64NV = NULL;
#endif
#ifdef glUniform2i64NV
glUniform2i64NVFunc _glUniform2i64NV = NULL;
#endif
#ifdef glUniform3i64NV
glUniform3i64NVFunc _glUniform3i64NV = NULL;
#endif
#ifdef glUniform4i64NV
glUniform4i64NVFunc _glUniform4i64NV = NULL;
#endif
#ifdef glUniform1i64vNV
glUniform1i64vNVFunc _glUniform1i64vNV = NULL;
#endif
#ifdef glUniform2i64vNV
glUniform2i64vNVFunc _glUniform2i64vNV = NULL;
#endif
#ifdef glUniform3i64vNV
glUniform3i64vNVFunc _glUniform3i64vNV = NULL;
#endif
#ifdef glUniform4i64vNV
glUniform4i64vNVFunc _glUniform4i64vNV = NULL;
#endif
#ifdef glUniform1ui64NV
glUniform1ui64NVFunc _glUniform1ui64NV = NULL;
#endif
#ifdef glUniform2ui64NV
glUniform2ui64NVFunc _glUniform2ui64NV = NULL;
#endif
#ifdef glUniform3ui64NV
glUniform3ui64NVFunc _glUniform3ui64NV = NULL;
#endif
#ifdef glUniform4ui64NV
glUniform4ui64NVFunc _glUniform4ui64NV = NULL;
#endif
#ifdef glUniform1ui64vNV
glUniform1ui64vNVFunc _glUniform1ui64vNV = NULL;
#endif
#ifdef glUniform2ui64vNV
glUniform2ui64vNVFunc _glUniform2ui64vNV = NULL;
#endif
#ifdef glUniform3ui64vNV
glUniform3ui64vNVFunc _glUniform3ui64vNV = NULL;
#endif
#ifdef glUniform4ui64vNV
glUniform4ui64vNVFunc _glUniform4ui64vNV = NULL;
#endif
#ifdef glGetUniformi64vNV
glGetUniformi64vNVFunc _glGetUniformi64vNV = NULL;
#endif
#ifdef glProgramUniform1i64NV
glProgramUniform1i64NVFunc _glProgramUniform1i64NV = NULL;
#endif
#ifdef glProgramUniform2i64NV
glProgramUniform2i64NVFunc _glProgramUniform2i64NV = NULL;
#endif
#ifdef glProgramUniform3i64NV
glProgramUniform3i64NVFunc _glProgramUniform3i64NV = NULL;
#endif
#ifdef glProgramUniform4i64NV
glProgramUniform4i64NVFunc _glProgramUniform4i64NV = NULL;
#endif
#ifdef glProgramUniform1i64vNV
glProgramUniform1i64vNVFunc _glProgramUniform1i64vNV = NULL;
#endif
#ifdef glProgramUniform2i64vNV
glProgramUniform2i64vNVFunc _glProgramUniform2i64vNV = NULL;
#endif
#ifdef glProgramUniform3i64vNV
glProgramUniform3i64vNVFunc _glProgramUniform3i64vNV = NULL;
#endif
#ifdef glProgramUniform4i64vNV
glProgramUniform4i64vNVFunc _glProgramUniform4i64vNV = NULL;
#endif
#ifdef glProgramUniform1ui64NV
glProgramUniform1ui64NVFunc _glProgramUniform1ui64NV = NULL;
#endif
#ifdef glProgramUniform2ui64NV
glProgramUniform2ui64NVFunc _glProgramUniform2ui64NV = NULL;
#endif
#ifdef glProgramUniform3ui64NV
glProgramUniform3ui64NVFunc _glProgramUniform3ui64NV = NULL;
#endif
#ifdef glProgramUniform4ui64NV
glProgramUniform4ui64NVFunc _glProgramUniform4ui64NV = NULL;
#endif
#ifdef glProgramUniform1ui64vNV
glProgramUniform1ui64vNVFunc _glProgramUniform1ui64vNV = NULL;
#endif
#ifdef glProgramUniform2ui64vNV
glProgramUniform2ui64vNVFunc _glProgramUniform2ui64vNV = NULL;
#endif
#ifdef glProgramUniform3ui64vNV
glProgramUniform3ui64vNVFunc _glProgramUniform3ui64vNV = NULL;
#endif
#ifdef glProgramUniform4ui64vNV
glProgramUniform4ui64vNVFunc _glProgramUniform4ui64vNV = NULL;
#endif
#ifdef glVertexAttribL1i64NV
glVertexAttribL1i64NVFunc _glVertexAttribL1i64NV = NULL;
#endif
#ifdef glVertexAttribL2i64NV
glVertexAttribL2i64NVFunc _glVertexAttribL2i64NV = NULL;
#endif
#ifdef glVertexAttribL3i64NV
glVertexAttribL3i64NVFunc _glVertexAttribL3i64NV = NULL;
#endif
#ifdef glVertexAttribL4i64NV
glVertexAttribL4i64NVFunc _glVertexAttribL4i64NV = NULL;
#endif
#ifdef glVertexAttribL1i64vNV
glVertexAttribL1i64vNVFunc _glVertexAttribL1i64vNV = NULL;
#endif
#ifdef glVertexAttribL2i64vNV
glVertexAttribL2i64vNVFunc _glVertexAttribL2i64vNV = NULL;
#endif
#ifdef glVertexAttribL3i64vNV
glVertexAttribL3i64vNVFunc _glVertexAttribL3i64vNV = NULL;
#endif
#ifdef glVertexAttribL4i64vNV
glVertexAttribL4i64vNVFunc _glVertexAttribL4i64vNV = NULL;
#endif
#ifdef glVertexAttribL1ui64NV
glVertexAttribL1ui64NVFunc _glVertexAttribL1ui64NV = NULL;
#endif
#ifdef glVertexAttribL2ui64NV
glVertexAttribL2ui64NVFunc _glVertexAttribL2ui64NV = NULL;
#endif
#ifdef glVertexAttribL3ui64NV
glVertexAttribL3ui64NVFunc _glVertexAttribL3ui64NV = NULL;
#endif
#ifdef glVertexAttribL4ui64NV
glVertexAttribL4ui64NVFunc _glVertexAttribL4ui64NV = NULL;
#endif
#ifdef glVertexAttribL1ui64vNV
glVertexAttribL1ui64vNVFunc _glVertexAttribL1ui64vNV = NULL;
#endif
#ifdef glVertexAttribL2ui64vNV
glVertexAttribL2ui64vNVFunc _glVertexAttribL2ui64vNV = NULL;
#endif
#ifdef glVertexAttribL3ui64vNV
glVertexAttribL3ui64vNVFunc _glVertexAttribL3ui64vNV = NULL;
#endif
#ifdef glVertexAttribL4ui64vNV
glVertexAttribL4ui64vNVFunc _glVertexAttribL4ui64vNV = NULL;
#endif
#ifdef glGetVertexAttribLi64vNV
glGetVertexAttribLi64vNVFunc _glGetVertexAttribLi64vNV = NULL;
#endif
#ifdef glGetVertexAttribLui64vNV
glGetVertexAttribLui64vNVFunc _glGetVertexAttribLui64vNV = NULL;
#endif
#ifdef glVertexAttribLFormatNV
glVertexAttribLFormatNVFunc _glVertexAttribLFormatNV = NULL;
#endif
#ifdef glGenNamesAMD
glGenNamesAMDFunc _glGenNamesAMD = NULL;
#endif
#ifdef glDeleteNamesAMD
glDeleteNamesAMDFunc _glDeleteNamesAMD = NULL;
#endif
#ifdef glIsNameAMD
glIsNameAMDFunc _glIsNameAMD = NULL;
#endif
#ifdef glDebugMessageEnableAMD
glDebugMessageEnableAMDFunc _glDebugMessageEnableAMD = NULL;
#endif
#ifdef glDebugMessageInsertAMD
glDebugMessageInsertAMDFunc _glDebugMessageInsertAMD = NULL;
#endif
#ifdef glDebugMessageCallbackAMD
glDebugMessageCallbackAMDFunc _glDebugMessageCallbackAMD = NULL;
#endif
#ifdef glGetDebugMessageLogAMD
glGetDebugMessageLogAMDFunc _glGetDebugMessageLogAMD = NULL;
#endif
#ifdef glVDPAUInitNV
glVDPAUInitNVFunc _glVDPAUInitNV = NULL;
#endif
#ifdef glVDPAUFiniNV
glVDPAUFiniNVFunc _glVDPAUFiniNV = NULL;
#endif
#ifdef glVDPAURegisterVideoSurfaceNV
glVDPAURegisterVideoSurfaceNVFunc _glVDPAURegisterVideoSurfaceNV = NULL;
#endif
#ifdef glVDPAURegisterOutputSurfaceNV
glVDPAURegisterOutputSurfaceNVFunc _glVDPAURegisterOutputSurfaceNV = NULL;
#endif
#ifdef glVDPAUIsSurfaceNV
glVDPAUIsSurfaceNVFunc _glVDPAUIsSurfaceNV = NULL;
#endif
#ifdef glVDPAUUnregisterSurfaceNV
glVDPAUUnregisterSurfaceNVFunc _glVDPAUUnregisterSurfaceNV = NULL;
#endif
#ifdef glVDPAUGetSurfaceivNV
glVDPAUGetSurfaceivNVFunc _glVDPAUGetSurfaceivNV = NULL;
#endif
#ifdef glVDPAUSurfaceAccessNV
glVDPAUSurfaceAccessNVFunc _glVDPAUSurfaceAccessNV = NULL;
#endif
#ifdef glVDPAUMapSurfacesNV
glVDPAUMapSurfacesNVFunc _glVDPAUMapSurfacesNV = NULL;
#endif
#ifdef glVDPAUUnmapSurfacesNV
glVDPAUUnmapSurfacesNVFunc _glVDPAUUnmapSurfacesNV = NULL;
#endif
#ifdef glTexImage2DMultisampleCoverageNV
glTexImage2DMultisampleCoverageNVFunc _glTexImage2DMultisampleCoverageNV = NULL;
#endif
#ifdef glTexImage3DMultisampleCoverageNV
glTexImage3DMultisampleCoverageNVFunc _glTexImage3DMultisampleCoverageNV = NULL;
#endif
#ifdef glTextureImage2DMultisampleNV
glTextureImage2DMultisampleNVFunc _glTextureImage2DMultisampleNV = NULL;
#endif
#ifdef glTextureImage3DMultisampleNV
glTextureImage3DMultisampleNVFunc _glTextureImage3DMultisampleNV = NULL;
#endif
#ifdef glTextureImage2DMultisampleCoverageNV
glTextureImage2DMultisampleCoverageNVFunc _glTextureImage2DMultisampleCoverageNV = NULL;
#endif
#ifdef glTextureImage3DMultisampleCoverageNV
glTextureImage3DMultisampleCoverageNVFunc _glTextureImage3DMultisampleCoverageNV = NULL;
#endif
#ifdef glSetMultisamplefvAMD
glSetMultisamplefvAMDFunc _glSetMultisamplefvAMD = NULL;
#endif
#ifdef glImportSyncEXT
glImportSyncEXTFunc _glImportSyncEXT = NULL;
#endif
#ifdef glMultiDrawArraysIndirectAMD
glMultiDrawArraysIndirectAMDFunc _glMultiDrawArraysIndirectAMD = NULL;
#endif
#ifdef glMultiDrawElementsIndirectAMD
glMultiDrawElementsIndirectAMDFunc _glMultiDrawElementsIndirectAMD = NULL;
#endif
#ifdef glGenPathsNV
glGenPathsNVFunc _glGenPathsNV = NULL;
#endif
#ifdef glDeletePathsNV
glDeletePathsNVFunc _glDeletePathsNV = NULL;
#endif
#ifdef glIsPathNV
glIsPathNVFunc _glIsPathNV = NULL;
#endif
#ifdef glPathCommandsNV
glPathCommandsNVFunc _glPathCommandsNV = NULL;
#endif
#ifdef glPathCoordsNV
glPathCoordsNVFunc _glPathCoordsNV = NULL;
#endif
#ifdef glPathSubCommandsNV
glPathSubCommandsNVFunc _glPathSubCommandsNV = NULL;
#endif
#ifdef glPathSubCoordsNV
glPathSubCoordsNVFunc _glPathSubCoordsNV = NULL;
#endif
#ifdef glPathStringNV
glPathStringNVFunc _glPathStringNV = NULL;
#endif
#ifdef glPathGlyphsNV
glPathGlyphsNVFunc _glPathGlyphsNV = NULL;
#endif
#ifdef glPathGlyphRangeNV
glPathGlyphRangeNVFunc _glPathGlyphRangeNV = NULL;
#endif
#ifdef glWeightPathsNV
glWeightPathsNVFunc _glWeightPathsNV = NULL;
#endif
#ifdef glCopyPathNV
glCopyPathNVFunc _glCopyPathNV = NULL;
#endif
#ifdef glInterpolatePathsNV
glInterpolatePathsNVFunc _glInterpolatePathsNV = NULL;
#endif
#ifdef glTransformPathNV
glTransformPathNVFunc _glTransformPathNV = NULL;
#endif
#ifdef glPathParameterivNV
glPathParameterivNVFunc _glPathParameterivNV = NULL;
#endif
#ifdef glPathParameteriNV
glPathParameteriNVFunc _glPathParameteriNV = NULL;
#endif
#ifdef glPathParameterfvNV
glPathParameterfvNVFunc _glPathParameterfvNV = NULL;
#endif
#ifdef glPathParameterfNV
glPathParameterfNVFunc _glPathParameterfNV = NULL;
#endif
#ifdef glPathDashArrayNV
glPathDashArrayNVFunc _glPathDashArrayNV = NULL;
#endif
#ifdef glPathStencilFuncNV
glPathStencilFuncNVFunc _glPathStencilFuncNV = NULL;
#endif
#ifdef glPathStencilDepthOffsetNV
glPathStencilDepthOffsetNVFunc _glPathStencilDepthOffsetNV = NULL;
#endif
#ifdef glStencilFillPathNV
glStencilFillPathNVFunc _glStencilFillPathNV = NULL;
#endif
#ifdef glStencilStrokePathNV
glStencilStrokePathNVFunc _glStencilStrokePathNV = NULL;
#endif
#ifdef glStencilFillPathInstancedNV
glStencilFillPathInstancedNVFunc _glStencilFillPathInstancedNV = NULL;
#endif
#ifdef glStencilStrokePathInstancedNV
glStencilStrokePathInstancedNVFunc _glStencilStrokePathInstancedNV = NULL;
#endif
#ifdef glPathCoverDepthFuncNV
glPathCoverDepthFuncNVFunc _glPathCoverDepthFuncNV = NULL;
#endif
#ifdef glPathColorGenNV
glPathColorGenNVFunc _glPathColorGenNV = NULL;
#endif
#ifdef glPathTexGenNV
glPathTexGenNVFunc _glPathTexGenNV = NULL;
#endif
#ifdef glPathFogGenNV
glPathFogGenNVFunc _glPathFogGenNV = NULL;
#endif
#ifdef glCoverFillPathNV
glCoverFillPathNVFunc _glCoverFillPathNV = NULL;
#endif
#ifdef glCoverStrokePathNV
glCoverStrokePathNVFunc _glCoverStrokePathNV = NULL;
#endif
#ifdef glCoverFillPathInstancedNV
glCoverFillPathInstancedNVFunc _glCoverFillPathInstancedNV = NULL;
#endif
#ifdef glCoverStrokePathInstancedNV
glCoverStrokePathInstancedNVFunc _glCoverStrokePathInstancedNV = NULL;
#endif
#ifdef glGetPathParameterivNV
glGetPathParameterivNVFunc _glGetPathParameterivNV = NULL;
#endif
#ifdef glGetPathParameterfvNV
glGetPathParameterfvNVFunc _glGetPathParameterfvNV = NULL;
#endif
#ifdef glGetPathCommandsNV
glGetPathCommandsNVFunc _glGetPathCommandsNV = NULL;
#endif
#ifdef glGetPathCoordsNV
glGetPathCoordsNVFunc _glGetPathCoordsNV = NULL;
#endif
#ifdef glGetPathDashArrayNV
glGetPathDashArrayNVFunc _glGetPathDashArrayNV = NULL;
#endif
#ifdef glGetPathMetricsNV
glGetPathMetricsNVFunc _glGetPathMetricsNV = NULL;
#endif
#ifdef glGetPathMetricRangeNV
glGetPathMetricRangeNVFunc _glGetPathMetricRangeNV = NULL;
#endif
#ifdef glGetPathSpacingNV
glGetPathSpacingNVFunc _glGetPathSpacingNV = NULL;
#endif
#ifdef glGetPathColorGenivNV
glGetPathColorGenivNVFunc _glGetPathColorGenivNV = NULL;
#endif
#ifdef glGetPathColorGenfvNV
glGetPathColorGenfvNVFunc _glGetPathColorGenfvNV = NULL;
#endif
#ifdef glGetPathTexGenivNV
glGetPathTexGenivNVFunc _glGetPathTexGenivNV = NULL;
#endif
#ifdef glGetPathTexGenfvNV
glGetPathTexGenfvNVFunc _glGetPathTexGenfvNV = NULL;
#endif
#ifdef glIsPointInFillPathNV
glIsPointInFillPathNVFunc _glIsPointInFillPathNV = NULL;
#endif
#ifdef glIsPointInStrokePathNV
glIsPointInStrokePathNVFunc _glIsPointInStrokePathNV = NULL;
#endif
#ifdef glGetPathLengthNV
glGetPathLengthNVFunc _glGetPathLengthNV = NULL;
#endif
#ifdef glPointAlongPathNV
glPointAlongPathNVFunc _glPointAlongPathNV = NULL;
#endif
#ifdef glStencilOpValueAMD
glStencilOpValueAMDFunc _glStencilOpValueAMD = NULL;
#endif
#ifdef glGetTextureHandleNV
glGetTextureHandleNVFunc _glGetTextureHandleNV = NULL;
#endif
#ifdef glGetTextureSamplerHandleNV
glGetTextureSamplerHandleNVFunc _glGetTextureSamplerHandleNV = NULL;
#endif
#ifdef glMakeTextureHandleResidentNV
glMakeTextureHandleResidentNVFunc _glMakeTextureHandleResidentNV = NULL;
#endif
#ifdef glMakeTextureHandleNonResidentNV
glMakeTextureHandleNonResidentNVFunc _glMakeTextureHandleNonResidentNV = NULL;
#endif
#ifdef glGetImageHandleNV
glGetImageHandleNVFunc _glGetImageHandleNV = NULL;
#endif
#ifdef glMakeImageHandleResidentNV
glMakeImageHandleResidentNVFunc _glMakeImageHandleResidentNV = NULL;
#endif
#ifdef glMakeImageHandleNonResidentNV
glMakeImageHandleNonResidentNVFunc _glMakeImageHandleNonResidentNV = NULL;
#endif
#ifdef glUniformHandleui64NV
glUniformHandleui64NVFunc _glUniformHandleui64NV = NULL;
#endif
#ifdef glUniformHandleui64vNV
glUniformHandleui64vNVFunc _glUniformHandleui64vNV = NULL;
#endif
#ifdef glProgramUniformHandleui64NV
glProgramUniformHandleui64NVFunc _glProgramUniformHandleui64NV = NULL;
#endif
#ifdef glProgramUniformHandleui64vNV
glProgramUniformHandleui64vNVFunc _glProgramUniformHandleui64vNV = NULL;
#endif
#ifdef glIsTextureHandleResidentNV
glIsTextureHandleResidentNVFunc _glIsTextureHandleResidentNV = NULL;
#endif
#ifdef glIsImageHandleResidentNV
glIsImageHandleResidentNVFunc _glIsImageHandleResidentNV = NULL;
#endif
#ifdef glTexStorageSparseAMD
glTexStorageSparseAMDFunc _glTexStorageSparseAMD = NULL;
#endif
#ifdef glTextureStorageSparseAMD
glTextureStorageSparseAMDFunc _glTextureStorageSparseAMD = NULL;
#endif

void glFuncload()
{
#	ifdef glCullFace
	_glCullFace = (glCullFaceFunc)glGetFunction("glCullFace");
#	endif
#	ifdef glFrontFace
	_glFrontFace = (glFrontFaceFunc)glGetFunction("glFrontFace");
#	endif
#	ifdef glHint
	_glHint = (glHintFunc)glGetFunction("glHint");
#	endif
#	ifdef glLineWidth
	_glLineWidth = (glLineWidthFunc)glGetFunction("glLineWidth");
#	endif
#	ifdef glPointSize
	_glPointSize = (glPointSizeFunc)glGetFunction("glPointSize");
#	endif
#	ifdef glPolygonMode
	_glPolygonMode = (glPolygonModeFunc)glGetFunction("glPolygonMode");
#	endif
#	ifdef glScissor
	_glScissor = (glScissorFunc)glGetFunction("glScissor");
#	endif
#	ifdef glTexParameterf
	_glTexParameterf = (glTexParameterfFunc)glGetFunction("glTexParameterf");
#	endif
#	ifdef glTexParameterfv
	_glTexParameterfv = (glTexParameterfvFunc)glGetFunction("glTexParameterfv");
#	endif
#	ifdef glTexParameteri
	_glTexParameteri = (glTexParameteriFunc)glGetFunction("glTexParameteri");
#	endif
#	ifdef glTexParameteriv
	_glTexParameteriv = (glTexParameterivFunc)glGetFunction("glTexParameteriv");
#	endif
#	ifdef glTexImage1D
	_glTexImage1D = (glTexImage1DFunc)glGetFunction("glTexImage1D");
#	endif
#	ifdef glTexImage2D
	_glTexImage2D = (glTexImage2DFunc)glGetFunction("glTexImage2D");
#	endif
#	ifdef glDrawBuffer
	_glDrawBuffer = (glDrawBufferFunc)glGetFunction("glDrawBuffer");
#	endif
#	ifdef glClear
	_glClear = (glClearFunc)glGetFunction("glClear");
#	endif
#	ifdef glClearColor
	_glClearColor = (glClearColorFunc)glGetFunction("glClearColor");
#	endif
#	ifdef glClearStencil
	_glClearStencil = (glClearStencilFunc)glGetFunction("glClearStencil");
#	endif
#	ifdef glClearDepth
	_glClearDepth = (glClearDepthFunc)glGetFunction("glClearDepth");
#	endif
#	ifdef glStencilMask
	_glStencilMask = (glStencilMaskFunc)glGetFunction("glStencilMask");
#	endif
#	ifdef glColorMask
	_glColorMask = (glColorMaskFunc)glGetFunction("glColorMask");
#	endif
#	ifdef glDepthMask
	_glDepthMask = (glDepthMaskFunc)glGetFunction("glDepthMask");
#	endif
#	ifdef glDisable
	_glDisable = (glDisableFunc)glGetFunction("glDisable");
#	endif
#	ifdef glEnable
	_glEnable = (glEnableFunc)glGetFunction("glEnable");
#	endif
#	ifdef glFinish
	_glFinish = (glFinishFunc)glGetFunction("glFinish");
#	endif
#	ifdef glFlush
	_glFlush = (glFlushFunc)glGetFunction("glFlush");
#	endif
#	ifdef glBlendFunc
	_glBlendFunc = (glBlendFuncFunc)glGetFunction("glBlendFunc");
#	endif
#	ifdef glLogicOp
	_glLogicOp = (glLogicOpFunc)glGetFunction("glLogicOp");
#	endif
#	ifdef glStencilFunc
	_glStencilFunc = (glStencilFuncFunc)glGetFunction("glStencilFunc");
#	endif
#	ifdef glStencilOp
	_glStencilOp = (glStencilOpFunc)glGetFunction("glStencilOp");
#	endif
#	ifdef glDepthFunc
	_glDepthFunc = (glDepthFuncFunc)glGetFunction("glDepthFunc");
#	endif
#	ifdef glPixelStoref
	_glPixelStoref = (glPixelStorefFunc)glGetFunction("glPixelStoref");
#	endif
#	ifdef glPixelStorei
	_glPixelStorei = (glPixelStoreiFunc)glGetFunction("glPixelStorei");
#	endif
#	ifdef glReadBuffer
	_glReadBuffer = (glReadBufferFunc)glGetFunction("glReadBuffer");
#	endif
#	ifdef glReadPixels
	_glReadPixels = (glReadPixelsFunc)glGetFunction("glReadPixels");
#	endif
#	ifdef glGetBooleanv
	_glGetBooleanv = (glGetBooleanvFunc)glGetFunction("glGetBooleanv");
#	endif
#	ifdef glGetDoublev
	_glGetDoublev = (glGetDoublevFunc)glGetFunction("glGetDoublev");
#	endif
#	ifdef glGetError
	_glGetError = (glGetErrorFunc)glGetFunction("glGetError");
#	endif
#	ifdef glGetFloatv
	_glGetFloatv = (glGetFloatvFunc)glGetFunction("glGetFloatv");
#	endif
#	ifdef glGetIntegerv
	_glGetIntegerv = (glGetIntegervFunc)glGetFunction("glGetIntegerv");
#	endif
#	ifdef glGetString
	_glGetString = (glGetStringFunc)glGetFunction("glGetString");
#	endif
#	ifdef glGetTexImage
	_glGetTexImage = (glGetTexImageFunc)glGetFunction("glGetTexImage");
#	endif
#	ifdef glGetTexParameterfv
	_glGetTexParameterfv = (glGetTexParameterfvFunc)glGetFunction("glGetTexParameterfv");
#	endif
#	ifdef glGetTexParameteriv
	_glGetTexParameteriv = (glGetTexParameterivFunc)glGetFunction("glGetTexParameteriv");
#	endif
#	ifdef glGetTexLevelParameterfv
	_glGetTexLevelParameterfv = (glGetTexLevelParameterfvFunc)glGetFunction("glGetTexLevelParameterfv");
#	endif
#	ifdef glGetTexLevelParameteriv
	_glGetTexLevelParameteriv = (glGetTexLevelParameterivFunc)glGetFunction("glGetTexLevelParameteriv");
#	endif
#	ifdef glIsEnabled
	_glIsEnabled = (glIsEnabledFunc)glGetFunction("glIsEnabled");
#	endif
#	ifdef glDepthRange
	_glDepthRange = (glDepthRangeFunc)glGetFunction("glDepthRange");
#	endif
#	ifdef glViewport
	_glViewport = (glViewportFunc)glGetFunction("glViewport");
#	endif
#	ifdef glNewList
	_glNewList = (glNewListFunc)glGetFunction("glNewList");
#	endif
#	ifdef glEndList
	_glEndList = (glEndListFunc)glGetFunction("glEndList");
#	endif
#	ifdef glCallList
	_glCallList = (glCallListFunc)glGetFunction("glCallList");
#	endif
#	ifdef glCallLists
	_glCallLists = (glCallListsFunc)glGetFunction("glCallLists");
#	endif
#	ifdef glDeleteLists
	_glDeleteLists = (glDeleteListsFunc)glGetFunction("glDeleteLists");
#	endif
#	ifdef glGenLists
	_glGenLists = (glGenListsFunc)glGetFunction("glGenLists");
#	endif
#	ifdef glListBase
	_glListBase = (glListBaseFunc)glGetFunction("glListBase");
#	endif
#	ifdef glBegin
	_glBegin = (glBeginFunc)glGetFunction("glBegin");
#	endif
#	ifdef glBitmap
	_glBitmap = (glBitmapFunc)glGetFunction("glBitmap");
#	endif
#	ifdef glColor3b
	_glColor3b = (glColor3bFunc)glGetFunction("glColor3b");
#	endif
#	ifdef glColor3bv
	_glColor3bv = (glColor3bvFunc)glGetFunction("glColor3bv");
#	endif
#	ifdef glColor3d
	_glColor3d = (glColor3dFunc)glGetFunction("glColor3d");
#	endif
#	ifdef glColor3dv
	_glColor3dv = (glColor3dvFunc)glGetFunction("glColor3dv");
#	endif
#	ifdef glColor3f
	_glColor3f = (glColor3fFunc)glGetFunction("glColor3f");
#	endif
#	ifdef glColor3fv
	_glColor3fv = (glColor3fvFunc)glGetFunction("glColor3fv");
#	endif
#	ifdef glColor3i
	_glColor3i = (glColor3iFunc)glGetFunction("glColor3i");
#	endif
#	ifdef glColor3iv
	_glColor3iv = (glColor3ivFunc)glGetFunction("glColor3iv");
#	endif
#	ifdef glColor3s
	_glColor3s = (glColor3sFunc)glGetFunction("glColor3s");
#	endif
#	ifdef glColor3sv
	_glColor3sv = (glColor3svFunc)glGetFunction("glColor3sv");
#	endif
#	ifdef glColor3ub
	_glColor3ub = (glColor3ubFunc)glGetFunction("glColor3ub");
#	endif
#	ifdef glColor3ubv
	_glColor3ubv = (glColor3ubvFunc)glGetFunction("glColor3ubv");
#	endif
#	ifdef glColor3ui
	_glColor3ui = (glColor3uiFunc)glGetFunction("glColor3ui");
#	endif
#	ifdef glColor3uiv
	_glColor3uiv = (glColor3uivFunc)glGetFunction("glColor3uiv");
#	endif
#	ifdef glColor3us
	_glColor3us = (glColor3usFunc)glGetFunction("glColor3us");
#	endif
#	ifdef glColor3usv
	_glColor3usv = (glColor3usvFunc)glGetFunction("glColor3usv");
#	endif
#	ifdef glColor4b
	_glColor4b = (glColor4bFunc)glGetFunction("glColor4b");
#	endif
#	ifdef glColor4bv
	_glColor4bv = (glColor4bvFunc)glGetFunction("glColor4bv");
#	endif
#	ifdef glColor4d
	_glColor4d = (glColor4dFunc)glGetFunction("glColor4d");
#	endif
#	ifdef glColor4dv
	_glColor4dv = (glColor4dvFunc)glGetFunction("glColor4dv");
#	endif
#	ifdef glColor4f
	_glColor4f = (glColor4fFunc)glGetFunction("glColor4f");
#	endif
#	ifdef glColor4fv
	_glColor4fv = (glColor4fvFunc)glGetFunction("glColor4fv");
#	endif
#	ifdef glColor4i
	_glColor4i = (glColor4iFunc)glGetFunction("glColor4i");
#	endif
#	ifdef glColor4iv
	_glColor4iv = (glColor4ivFunc)glGetFunction("glColor4iv");
#	endif
#	ifdef glColor4s
	_glColor4s = (glColor4sFunc)glGetFunction("glColor4s");
#	endif
#	ifdef glColor4sv
	_glColor4sv = (glColor4svFunc)glGetFunction("glColor4sv");
#	endif
#	ifdef glColor4ub
	_glColor4ub = (glColor4ubFunc)glGetFunction("glColor4ub");
#	endif
#	ifdef glColor4ubv
	_glColor4ubv = (glColor4ubvFunc)glGetFunction("glColor4ubv");
#	endif
#	ifdef glColor4ui
	_glColor4ui = (glColor4uiFunc)glGetFunction("glColor4ui");
#	endif
#	ifdef glColor4uiv
	_glColor4uiv = (glColor4uivFunc)glGetFunction("glColor4uiv");
#	endif
#	ifdef glColor4us
	_glColor4us = (glColor4usFunc)glGetFunction("glColor4us");
#	endif
#	ifdef glColor4usv
	_glColor4usv = (glColor4usvFunc)glGetFunction("glColor4usv");
#	endif
#	ifdef glEdgeFlag
	_glEdgeFlag = (glEdgeFlagFunc)glGetFunction("glEdgeFlag");
#	endif
#	ifdef glEdgeFlagv
	_glEdgeFlagv = (glEdgeFlagvFunc)glGetFunction("glEdgeFlagv");
#	endif
#	ifdef glEnd
	_glEnd = (glEndFunc)glGetFunction("glEnd");
#	endif
#	ifdef glIndexd
	_glIndexd = (glIndexdFunc)glGetFunction("glIndexd");
#	endif
#	ifdef glIndexdv
	_glIndexdv = (glIndexdvFunc)glGetFunction("glIndexdv");
#	endif
#	ifdef glIndexf
	_glIndexf = (glIndexfFunc)glGetFunction("glIndexf");
#	endif
#	ifdef glIndexfv
	_glIndexfv = (glIndexfvFunc)glGetFunction("glIndexfv");
#	endif
#	ifdef glIndexi
	_glIndexi = (glIndexiFunc)glGetFunction("glIndexi");
#	endif
#	ifdef glIndexiv
	_glIndexiv = (glIndexivFunc)glGetFunction("glIndexiv");
#	endif
#	ifdef glIndexs
	_glIndexs = (glIndexsFunc)glGetFunction("glIndexs");
#	endif
#	ifdef glIndexsv
	_glIndexsv = (glIndexsvFunc)glGetFunction("glIndexsv");
#	endif
#	ifdef glNormal3b
	_glNormal3b = (glNormal3bFunc)glGetFunction("glNormal3b");
#	endif
#	ifdef glNormal3bv
	_glNormal3bv = (glNormal3bvFunc)glGetFunction("glNormal3bv");
#	endif
#	ifdef glNormal3d
	_glNormal3d = (glNormal3dFunc)glGetFunction("glNormal3d");
#	endif
#	ifdef glNormal3dv
	_glNormal3dv = (glNormal3dvFunc)glGetFunction("glNormal3dv");
#	endif
#	ifdef glNormal3f
	_glNormal3f = (glNormal3fFunc)glGetFunction("glNormal3f");
#	endif
#	ifdef glNormal3fv
	_glNormal3fv = (glNormal3fvFunc)glGetFunction("glNormal3fv");
#	endif
#	ifdef glNormal3i
	_glNormal3i = (glNormal3iFunc)glGetFunction("glNormal3i");
#	endif
#	ifdef glNormal3iv
	_glNormal3iv = (glNormal3ivFunc)glGetFunction("glNormal3iv");
#	endif
#	ifdef glNormal3s
	_glNormal3s = (glNormal3sFunc)glGetFunction("glNormal3s");
#	endif
#	ifdef glNormal3sv
	_glNormal3sv = (glNormal3svFunc)glGetFunction("glNormal3sv");
#	endif
#	ifdef glRasterPos2d
	_glRasterPos2d = (glRasterPos2dFunc)glGetFunction("glRasterPos2d");
#	endif
#	ifdef glRasterPos2dv
	_glRasterPos2dv = (glRasterPos2dvFunc)glGetFunction("glRasterPos2dv");
#	endif
#	ifdef glRasterPos2f
	_glRasterPos2f = (glRasterPos2fFunc)glGetFunction("glRasterPos2f");
#	endif
#	ifdef glRasterPos2fv
	_glRasterPos2fv = (glRasterPos2fvFunc)glGetFunction("glRasterPos2fv");
#	endif
#	ifdef glRasterPos2i
	_glRasterPos2i = (glRasterPos2iFunc)glGetFunction("glRasterPos2i");
#	endif
#	ifdef glRasterPos2iv
	_glRasterPos2iv = (glRasterPos2ivFunc)glGetFunction("glRasterPos2iv");
#	endif
#	ifdef glRasterPos2s
	_glRasterPos2s = (glRasterPos2sFunc)glGetFunction("glRasterPos2s");
#	endif
#	ifdef glRasterPos2sv
	_glRasterPos2sv = (glRasterPos2svFunc)glGetFunction("glRasterPos2sv");
#	endif
#	ifdef glRasterPos3d
	_glRasterPos3d = (glRasterPos3dFunc)glGetFunction("glRasterPos3d");
#	endif
#	ifdef glRasterPos3dv
	_glRasterPos3dv = (glRasterPos3dvFunc)glGetFunction("glRasterPos3dv");
#	endif
#	ifdef glRasterPos3f
	_glRasterPos3f = (glRasterPos3fFunc)glGetFunction("glRasterPos3f");
#	endif
#	ifdef glRasterPos3fv
	_glRasterPos3fv = (glRasterPos3fvFunc)glGetFunction("glRasterPos3fv");
#	endif
#	ifdef glRasterPos3i
	_glRasterPos3i = (glRasterPos3iFunc)glGetFunction("glRasterPos3i");
#	endif
#	ifdef glRasterPos3iv
	_glRasterPos3iv = (glRasterPos3ivFunc)glGetFunction("glRasterPos3iv");
#	endif
#	ifdef glRasterPos3s
	_glRasterPos3s = (glRasterPos3sFunc)glGetFunction("glRasterPos3s");
#	endif
#	ifdef glRasterPos3sv
	_glRasterPos3sv = (glRasterPos3svFunc)glGetFunction("glRasterPos3sv");
#	endif
#	ifdef glRasterPos4d
	_glRasterPos4d = (glRasterPos4dFunc)glGetFunction("glRasterPos4d");
#	endif
#	ifdef glRasterPos4dv
	_glRasterPos4dv = (glRasterPos4dvFunc)glGetFunction("glRasterPos4dv");
#	endif
#	ifdef glRasterPos4f
	_glRasterPos4f = (glRasterPos4fFunc)glGetFunction("glRasterPos4f");
#	endif
#	ifdef glRasterPos4fv
	_glRasterPos4fv = (glRasterPos4fvFunc)glGetFunction("glRasterPos4fv");
#	endif
#	ifdef glRasterPos4i
	_glRasterPos4i = (glRasterPos4iFunc)glGetFunction("glRasterPos4i");
#	endif
#	ifdef glRasterPos4iv
	_glRasterPos4iv = (glRasterPos4ivFunc)glGetFunction("glRasterPos4iv");
#	endif
#	ifdef glRasterPos4s
	_glRasterPos4s = (glRasterPos4sFunc)glGetFunction("glRasterPos4s");
#	endif
#	ifdef glRasterPos4sv
	_glRasterPos4sv = (glRasterPos4svFunc)glGetFunction("glRasterPos4sv");
#	endif
#	ifdef glRectd
	_glRectd = (glRectdFunc)glGetFunction("glRectd");
#	endif
#	ifdef glRectdv
	_glRectdv = (glRectdvFunc)glGetFunction("glRectdv");
#	endif
#	ifdef glRectf
	_glRectf = (glRectfFunc)glGetFunction("glRectf");
#	endif
#	ifdef glRectfv
	_glRectfv = (glRectfvFunc)glGetFunction("glRectfv");
#	endif
#	ifdef glRecti
	_glRecti = (glRectiFunc)glGetFunction("glRecti");
#	endif
#	ifdef glRectiv
	_glRectiv = (glRectivFunc)glGetFunction("glRectiv");
#	endif
#	ifdef glRects
	_glRects = (glRectsFunc)glGetFunction("glRects");
#	endif
#	ifdef glRectsv
	_glRectsv = (glRectsvFunc)glGetFunction("glRectsv");
#	endif
#	ifdef glTexCoord1d
	_glTexCoord1d = (glTexCoord1dFunc)glGetFunction("glTexCoord1d");
#	endif
#	ifdef glTexCoord1dv
	_glTexCoord1dv = (glTexCoord1dvFunc)glGetFunction("glTexCoord1dv");
#	endif
#	ifdef glTexCoord1f
	_glTexCoord1f = (glTexCoord1fFunc)glGetFunction("glTexCoord1f");
#	endif
#	ifdef glTexCoord1fv
	_glTexCoord1fv = (glTexCoord1fvFunc)glGetFunction("glTexCoord1fv");
#	endif
#	ifdef glTexCoord1i
	_glTexCoord1i = (glTexCoord1iFunc)glGetFunction("glTexCoord1i");
#	endif
#	ifdef glTexCoord1iv
	_glTexCoord1iv = (glTexCoord1ivFunc)glGetFunction("glTexCoord1iv");
#	endif
#	ifdef glTexCoord1s
	_glTexCoord1s = (glTexCoord1sFunc)glGetFunction("glTexCoord1s");
#	endif
#	ifdef glTexCoord1sv
	_glTexCoord1sv = (glTexCoord1svFunc)glGetFunction("glTexCoord1sv");
#	endif
#	ifdef glTexCoord2d
	_glTexCoord2d = (glTexCoord2dFunc)glGetFunction("glTexCoord2d");
#	endif
#	ifdef glTexCoord2dv
	_glTexCoord2dv = (glTexCoord2dvFunc)glGetFunction("glTexCoord2dv");
#	endif
#	ifdef glTexCoord2f
	_glTexCoord2f = (glTexCoord2fFunc)glGetFunction("glTexCoord2f");
#	endif
#	ifdef glTexCoord2fv
	_glTexCoord2fv = (glTexCoord2fvFunc)glGetFunction("glTexCoord2fv");
#	endif
#	ifdef glTexCoord2i
	_glTexCoord2i = (glTexCoord2iFunc)glGetFunction("glTexCoord2i");
#	endif
#	ifdef glTexCoord2iv
	_glTexCoord2iv = (glTexCoord2ivFunc)glGetFunction("glTexCoord2iv");
#	endif
#	ifdef glTexCoord2s
	_glTexCoord2s = (glTexCoord2sFunc)glGetFunction("glTexCoord2s");
#	endif
#	ifdef glTexCoord2sv
	_glTexCoord2sv = (glTexCoord2svFunc)glGetFunction("glTexCoord2sv");
#	endif
#	ifdef glTexCoord3d
	_glTexCoord3d = (glTexCoord3dFunc)glGetFunction("glTexCoord3d");
#	endif
#	ifdef glTexCoord3dv
	_glTexCoord3dv = (glTexCoord3dvFunc)glGetFunction("glTexCoord3dv");
#	endif
#	ifdef glTexCoord3f
	_glTexCoord3f = (glTexCoord3fFunc)glGetFunction("glTexCoord3f");
#	endif
#	ifdef glTexCoord3fv
	_glTexCoord3fv = (glTexCoord3fvFunc)glGetFunction("glTexCoord3fv");
#	endif
#	ifdef glTexCoord3i
	_glTexCoord3i = (glTexCoord3iFunc)glGetFunction("glTexCoord3i");
#	endif
#	ifdef glTexCoord3iv
	_glTexCoord3iv = (glTexCoord3ivFunc)glGetFunction("glTexCoord3iv");
#	endif
#	ifdef glTexCoord3s
	_glTexCoord3s = (glTexCoord3sFunc)glGetFunction("glTexCoord3s");
#	endif
#	ifdef glTexCoord3sv
	_glTexCoord3sv = (glTexCoord3svFunc)glGetFunction("glTexCoord3sv");
#	endif
#	ifdef glTexCoord4d
	_glTexCoord4d = (glTexCoord4dFunc)glGetFunction("glTexCoord4d");
#	endif
#	ifdef glTexCoord4dv
	_glTexCoord4dv = (glTexCoord4dvFunc)glGetFunction("glTexCoord4dv");
#	endif
#	ifdef glTexCoord4f
	_glTexCoord4f = (glTexCoord4fFunc)glGetFunction("glTexCoord4f");
#	endif
#	ifdef glTexCoord4fv
	_glTexCoord4fv = (glTexCoord4fvFunc)glGetFunction("glTexCoord4fv");
#	endif
#	ifdef glTexCoord4i
	_glTexCoord4i = (glTexCoord4iFunc)glGetFunction("glTexCoord4i");
#	endif
#	ifdef glTexCoord4iv
	_glTexCoord4iv = (glTexCoord4ivFunc)glGetFunction("glTexCoord4iv");
#	endif
#	ifdef glTexCoord4s
	_glTexCoord4s = (glTexCoord4sFunc)glGetFunction("glTexCoord4s");
#	endif
#	ifdef glTexCoord4sv
	_glTexCoord4sv = (glTexCoord4svFunc)glGetFunction("glTexCoord4sv");
#	endif
#	ifdef glVertex2d
	_glVertex2d = (glVertex2dFunc)glGetFunction("glVertex2d");
#	endif
#	ifdef glVertex2dv
	_glVertex2dv = (glVertex2dvFunc)glGetFunction("glVertex2dv");
#	endif
#	ifdef glVertex2f
	_glVertex2f = (glVertex2fFunc)glGetFunction("glVertex2f");
#	endif
#	ifdef glVertex2fv
	_glVertex2fv = (glVertex2fvFunc)glGetFunction("glVertex2fv");
#	endif
#	ifdef glVertex2i
	_glVertex2i = (glVertex2iFunc)glGetFunction("glVertex2i");
#	endif
#	ifdef glVertex2iv
	_glVertex2iv = (glVertex2ivFunc)glGetFunction("glVertex2iv");
#	endif
#	ifdef glVertex2s
	_glVertex2s = (glVertex2sFunc)glGetFunction("glVertex2s");
#	endif
#	ifdef glVertex2sv
	_glVertex2sv = (glVertex2svFunc)glGetFunction("glVertex2sv");
#	endif
#	ifdef glVertex3d
	_glVertex3d = (glVertex3dFunc)glGetFunction("glVertex3d");
#	endif
#	ifdef glVertex3dv
	_glVertex3dv = (glVertex3dvFunc)glGetFunction("glVertex3dv");
#	endif
#	ifdef glVertex3f
	_glVertex3f = (glVertex3fFunc)glGetFunction("glVertex3f");
#	endif
#	ifdef glVertex3fv
	_glVertex3fv = (glVertex3fvFunc)glGetFunction("glVertex3fv");
#	endif
#	ifdef glVertex3i
	_glVertex3i = (glVertex3iFunc)glGetFunction("glVertex3i");
#	endif
#	ifdef glVertex3iv
	_glVertex3iv = (glVertex3ivFunc)glGetFunction("glVertex3iv");
#	endif
#	ifdef glVertex3s
	_glVertex3s = (glVertex3sFunc)glGetFunction("glVertex3s");
#	endif
#	ifdef glVertex3sv
	_glVertex3sv = (glVertex3svFunc)glGetFunction("glVertex3sv");
#	endif
#	ifdef glVertex4d
	_glVertex4d = (glVertex4dFunc)glGetFunction("glVertex4d");
#	endif
#	ifdef glVertex4dv
	_glVertex4dv = (glVertex4dvFunc)glGetFunction("glVertex4dv");
#	endif
#	ifdef glVertex4f
	_glVertex4f = (glVertex4fFunc)glGetFunction("glVertex4f");
#	endif
#	ifdef glVertex4fv
	_glVertex4fv = (glVertex4fvFunc)glGetFunction("glVertex4fv");
#	endif
#	ifdef glVertex4i
	_glVertex4i = (glVertex4iFunc)glGetFunction("glVertex4i");
#	endif
#	ifdef glVertex4iv
	_glVertex4iv = (glVertex4ivFunc)glGetFunction("glVertex4iv");
#	endif
#	ifdef glVertex4s
	_glVertex4s = (glVertex4sFunc)glGetFunction("glVertex4s");
#	endif
#	ifdef glVertex4sv
	_glVertex4sv = (glVertex4svFunc)glGetFunction("glVertex4sv");
#	endif
#	ifdef glClipPlane
	_glClipPlane = (glClipPlaneFunc)glGetFunction("glClipPlane");
#	endif
#	ifdef glColorMaterial
	_glColorMaterial = (glColorMaterialFunc)glGetFunction("glColorMaterial");
#	endif
#	ifdef glFogf
	_glFogf = (glFogfFunc)glGetFunction("glFogf");
#	endif
#	ifdef glFogfv
	_glFogfv = (glFogfvFunc)glGetFunction("glFogfv");
#	endif
#	ifdef glFogi
	_glFogi = (glFogiFunc)glGetFunction("glFogi");
#	endif
#	ifdef glFogiv
	_glFogiv = (glFogivFunc)glGetFunction("glFogiv");
#	endif
#	ifdef glLightf
	_glLightf = (glLightfFunc)glGetFunction("glLightf");
#	endif
#	ifdef glLightfv
	_glLightfv = (glLightfvFunc)glGetFunction("glLightfv");
#	endif
#	ifdef glLighti
	_glLighti = (glLightiFunc)glGetFunction("glLighti");
#	endif
#	ifdef glLightiv
	_glLightiv = (glLightivFunc)glGetFunction("glLightiv");
#	endif
#	ifdef glLightModelf
	_glLightModelf = (glLightModelfFunc)glGetFunction("glLightModelf");
#	endif
#	ifdef glLightModelfv
	_glLightModelfv = (glLightModelfvFunc)glGetFunction("glLightModelfv");
#	endif
#	ifdef glLightModeli
	_glLightModeli = (glLightModeliFunc)glGetFunction("glLightModeli");
#	endif
#	ifdef glLightModeliv
	_glLightModeliv = (glLightModelivFunc)glGetFunction("glLightModeliv");
#	endif
#	ifdef glLineStipple
	_glLineStipple = (glLineStippleFunc)glGetFunction("glLineStipple");
#	endif
#	ifdef glMaterialf
	_glMaterialf = (glMaterialfFunc)glGetFunction("glMaterialf");
#	endif
#	ifdef glMaterialfv
	_glMaterialfv = (glMaterialfvFunc)glGetFunction("glMaterialfv");
#	endif
#	ifdef glMateriali
	_glMateriali = (glMaterialiFunc)glGetFunction("glMateriali");
#	endif
#	ifdef glMaterialiv
	_glMaterialiv = (glMaterialivFunc)glGetFunction("glMaterialiv");
#	endif
#	ifdef glPolygonStipple
	_glPolygonStipple = (glPolygonStippleFunc)glGetFunction("glPolygonStipple");
#	endif
#	ifdef glShadeModel
	_glShadeModel = (glShadeModelFunc)glGetFunction("glShadeModel");
#	endif
#	ifdef glTexEnvf
	_glTexEnvf = (glTexEnvfFunc)glGetFunction("glTexEnvf");
#	endif
#	ifdef glTexEnvfv
	_glTexEnvfv = (glTexEnvfvFunc)glGetFunction("glTexEnvfv");
#	endif
#	ifdef glTexEnvi
	_glTexEnvi = (glTexEnviFunc)glGetFunction("glTexEnvi");
#	endif
#	ifdef glTexEnviv
	_glTexEnviv = (glTexEnvivFunc)glGetFunction("glTexEnviv");
#	endif
#	ifdef glTexGend
	_glTexGend = (glTexGendFunc)glGetFunction("glTexGend");
#	endif
#	ifdef glTexGendv
	_glTexGendv = (glTexGendvFunc)glGetFunction("glTexGendv");
#	endif
#	ifdef glTexGenf
	_glTexGenf = (glTexGenfFunc)glGetFunction("glTexGenf");
#	endif
#	ifdef glTexGenfv
	_glTexGenfv = (glTexGenfvFunc)glGetFunction("glTexGenfv");
#	endif
#	ifdef glTexGeni
	_glTexGeni = (glTexGeniFunc)glGetFunction("glTexGeni");
#	endif
#	ifdef glTexGeniv
	_glTexGeniv = (glTexGenivFunc)glGetFunction("glTexGeniv");
#	endif
#	ifdef glFeedbackBuffer
	_glFeedbackBuffer = (glFeedbackBufferFunc)glGetFunction("glFeedbackBuffer");
#	endif
#	ifdef glSelectBuffer
	_glSelectBuffer = (glSelectBufferFunc)glGetFunction("glSelectBuffer");
#	endif
#	ifdef glRenderMode
	_glRenderMode = (glRenderModeFunc)glGetFunction("glRenderMode");
#	endif
#	ifdef glInitNames
	_glInitNames = (glInitNamesFunc)glGetFunction("glInitNames");
#	endif
#	ifdef glLoadName
	_glLoadName = (glLoadNameFunc)glGetFunction("glLoadName");
#	endif
#	ifdef glPassThrough
	_glPassThrough = (glPassThroughFunc)glGetFunction("glPassThrough");
#	endif
#	ifdef glPopName
	_glPopName = (glPopNameFunc)glGetFunction("glPopName");
#	endif
#	ifdef glPushName
	_glPushName = (glPushNameFunc)glGetFunction("glPushName");
#	endif
#	ifdef glClearAccum
	_glClearAccum = (glClearAccumFunc)glGetFunction("glClearAccum");
#	endif
#	ifdef glClearIndex
	_glClearIndex = (glClearIndexFunc)glGetFunction("glClearIndex");
#	endif
#	ifdef glIndexMask
	_glIndexMask = (glIndexMaskFunc)glGetFunction("glIndexMask");
#	endif
#	ifdef glAccum
	_glAccum = (glAccumFunc)glGetFunction("glAccum");
#	endif
#	ifdef glPopAttrib
	_glPopAttrib = (glPopAttribFunc)glGetFunction("glPopAttrib");
#	endif
#	ifdef glPushAttrib
	_glPushAttrib = (glPushAttribFunc)glGetFunction("glPushAttrib");
#	endif
#	ifdef glMap1d
	_glMap1d = (glMap1dFunc)glGetFunction("glMap1d");
#	endif
#	ifdef glMap1f
	_glMap1f = (glMap1fFunc)glGetFunction("glMap1f");
#	endif
#	ifdef glMap2d
	_glMap2d = (glMap2dFunc)glGetFunction("glMap2d");
#	endif
#	ifdef glMap2f
	_glMap2f = (glMap2fFunc)glGetFunction("glMap2f");
#	endif
#	ifdef glMapGrid1d
	_glMapGrid1d = (glMapGrid1dFunc)glGetFunction("glMapGrid1d");
#	endif
#	ifdef glMapGrid1f
	_glMapGrid1f = (glMapGrid1fFunc)glGetFunction("glMapGrid1f");
#	endif
#	ifdef glMapGrid2d
	_glMapGrid2d = (glMapGrid2dFunc)glGetFunction("glMapGrid2d");
#	endif
#	ifdef glMapGrid2f
	_glMapGrid2f = (glMapGrid2fFunc)glGetFunction("glMapGrid2f");
#	endif
#	ifdef glEvalCoord1d
	_glEvalCoord1d = (glEvalCoord1dFunc)glGetFunction("glEvalCoord1d");
#	endif
#	ifdef glEvalCoord1dv
	_glEvalCoord1dv = (glEvalCoord1dvFunc)glGetFunction("glEvalCoord1dv");
#	endif
#	ifdef glEvalCoord1f
	_glEvalCoord1f = (glEvalCoord1fFunc)glGetFunction("glEvalCoord1f");
#	endif
#	ifdef glEvalCoord1fv
	_glEvalCoord1fv = (glEvalCoord1fvFunc)glGetFunction("glEvalCoord1fv");
#	endif
#	ifdef glEvalCoord2d
	_glEvalCoord2d = (glEvalCoord2dFunc)glGetFunction("glEvalCoord2d");
#	endif
#	ifdef glEvalCoord2dv
	_glEvalCoord2dv = (glEvalCoord2dvFunc)glGetFunction("glEvalCoord2dv");
#	endif
#	ifdef glEvalCoord2f
	_glEvalCoord2f = (glEvalCoord2fFunc)glGetFunction("glEvalCoord2f");
#	endif
#	ifdef glEvalCoord2fv
	_glEvalCoord2fv = (glEvalCoord2fvFunc)glGetFunction("glEvalCoord2fv");
#	endif
#	ifdef glEvalMesh1
	_glEvalMesh1 = (glEvalMesh1Func)glGetFunction("glEvalMesh1");
#	endif
#	ifdef glEvalPoint1
	_glEvalPoint1 = (glEvalPoint1Func)glGetFunction("glEvalPoint1");
#	endif
#	ifdef glEvalMesh2
	_glEvalMesh2 = (glEvalMesh2Func)glGetFunction("glEvalMesh2");
#	endif
#	ifdef glEvalPoint2
	_glEvalPoint2 = (glEvalPoint2Func)glGetFunction("glEvalPoint2");
#	endif
#	ifdef glAlphaFunc
	_glAlphaFunc = (glAlphaFuncFunc)glGetFunction("glAlphaFunc");
#	endif
#	ifdef glPixelZoom
	_glPixelZoom = (glPixelZoomFunc)glGetFunction("glPixelZoom");
#	endif
#	ifdef glPixelTransferf
	_glPixelTransferf = (glPixelTransferfFunc)glGetFunction("glPixelTransferf");
#	endif
#	ifdef glPixelTransferi
	_glPixelTransferi = (glPixelTransferiFunc)glGetFunction("glPixelTransferi");
#	endif
#	ifdef glPixelMapfv
	_glPixelMapfv = (glPixelMapfvFunc)glGetFunction("glPixelMapfv");
#	endif
#	ifdef glPixelMapuiv
	_glPixelMapuiv = (glPixelMapuivFunc)glGetFunction("glPixelMapuiv");
#	endif
#	ifdef glPixelMapusv
	_glPixelMapusv = (glPixelMapusvFunc)glGetFunction("glPixelMapusv");
#	endif
#	ifdef glCopyPixels
	_glCopyPixels = (glCopyPixelsFunc)glGetFunction("glCopyPixels");
#	endif
#	ifdef glDrawPixels
	_glDrawPixels = (glDrawPixelsFunc)glGetFunction("glDrawPixels");
#	endif
#	ifdef glGetClipPlane
	_glGetClipPlane = (glGetClipPlaneFunc)glGetFunction("glGetClipPlane");
#	endif
#	ifdef glGetLightfv
	_glGetLightfv = (glGetLightfvFunc)glGetFunction("glGetLightfv");
#	endif
#	ifdef glGetLightiv
	_glGetLightiv = (glGetLightivFunc)glGetFunction("glGetLightiv");
#	endif
#	ifdef glGetMapdv
	_glGetMapdv = (glGetMapdvFunc)glGetFunction("glGetMapdv");
#	endif
#	ifdef glGetMapfv
	_glGetMapfv = (glGetMapfvFunc)glGetFunction("glGetMapfv");
#	endif
#	ifdef glGetMapiv
	_glGetMapiv = (glGetMapivFunc)glGetFunction("glGetMapiv");
#	endif
#	ifdef glGetMaterialfv
	_glGetMaterialfv = (glGetMaterialfvFunc)glGetFunction("glGetMaterialfv");
#	endif
#	ifdef glGetMaterialiv
	_glGetMaterialiv = (glGetMaterialivFunc)glGetFunction("glGetMaterialiv");
#	endif
#	ifdef glGetPixelMapfv
	_glGetPixelMapfv = (glGetPixelMapfvFunc)glGetFunction("glGetPixelMapfv");
#	endif
#	ifdef glGetPixelMapuiv
	_glGetPixelMapuiv = (glGetPixelMapuivFunc)glGetFunction("glGetPixelMapuiv");
#	endif
#	ifdef glGetPixelMapusv
	_glGetPixelMapusv = (glGetPixelMapusvFunc)glGetFunction("glGetPixelMapusv");
#	endif
#	ifdef glGetPolygonStipple
	_glGetPolygonStipple = (glGetPolygonStippleFunc)glGetFunction("glGetPolygonStipple");
#	endif
#	ifdef glGetTexEnvfv
	_glGetTexEnvfv = (glGetTexEnvfvFunc)glGetFunction("glGetTexEnvfv");
#	endif
#	ifdef glGetTexEnviv
	_glGetTexEnviv = (glGetTexEnvivFunc)glGetFunction("glGetTexEnviv");
#	endif
#	ifdef glGetTexGendv
	_glGetTexGendv = (glGetTexGendvFunc)glGetFunction("glGetTexGendv");
#	endif
#	ifdef glGetTexGenfv
	_glGetTexGenfv = (glGetTexGenfvFunc)glGetFunction("glGetTexGenfv");
#	endif
#	ifdef glGetTexGeniv
	_glGetTexGeniv = (glGetTexGenivFunc)glGetFunction("glGetTexGeniv");
#	endif
#	ifdef glIsList
	_glIsList = (glIsListFunc)glGetFunction("glIsList");
#	endif
#	ifdef glFrustum
	_glFrustum = (glFrustumFunc)glGetFunction("glFrustum");
#	endif
#	ifdef glLoadIdentity
	_glLoadIdentity = (glLoadIdentityFunc)glGetFunction("glLoadIdentity");
#	endif
#	ifdef glLoadMatrixf
	_glLoadMatrixf = (glLoadMatrixfFunc)glGetFunction("glLoadMatrixf");
#	endif
#	ifdef glLoadMatrixd
	_glLoadMatrixd = (glLoadMatrixdFunc)glGetFunction("glLoadMatrixd");
#	endif
#	ifdef glMatrixMode
	_glMatrixMode = (glMatrixModeFunc)glGetFunction("glMatrixMode");
#	endif
#	ifdef glMultMatrixf
	_glMultMatrixf = (glMultMatrixfFunc)glGetFunction("glMultMatrixf");
#	endif
#	ifdef glMultMatrixd
	_glMultMatrixd = (glMultMatrixdFunc)glGetFunction("glMultMatrixd");
#	endif
#	ifdef glOrtho
	_glOrtho = (glOrthoFunc)glGetFunction("glOrtho");
#	endif
#	ifdef glPopMatrix
	_glPopMatrix = (glPopMatrixFunc)glGetFunction("glPopMatrix");
#	endif
#	ifdef glPushMatrix
	_glPushMatrix = (glPushMatrixFunc)glGetFunction("glPushMatrix");
#	endif
#	ifdef glRotated
	_glRotated = (glRotatedFunc)glGetFunction("glRotated");
#	endif
#	ifdef glRotatef
	_glRotatef = (glRotatefFunc)glGetFunction("glRotatef");
#	endif
#	ifdef glScaled
	_glScaled = (glScaledFunc)glGetFunction("glScaled");
#	endif
#	ifdef glScalef
	_glScalef = (glScalefFunc)glGetFunction("glScalef");
#	endif
#	ifdef glTranslated
	_glTranslated = (glTranslatedFunc)glGetFunction("glTranslated");
#	endif
#	ifdef glTranslatef
	_glTranslatef = (glTranslatefFunc)glGetFunction("glTranslatef");
#	endif
#	ifdef glDrawArrays
	_glDrawArrays = (glDrawArraysFunc)glGetFunction("glDrawArrays");
#	endif
#	ifdef glDrawElements
	_glDrawElements = (glDrawElementsFunc)glGetFunction("glDrawElements");
#	endif
#	ifdef glGetPointerv
	_glGetPointerv = (glGetPointervFunc)glGetFunction("glGetPointerv");
#	endif
#	ifdef glPolygonOffset
	_glPolygonOffset = (glPolygonOffsetFunc)glGetFunction("glPolygonOffset");
#	endif
#	ifdef glCopyTexImage1D
	_glCopyTexImage1D = (glCopyTexImage1DFunc)glGetFunction("glCopyTexImage1D");
#	endif
#	ifdef glCopyTexImage2D
	_glCopyTexImage2D = (glCopyTexImage2DFunc)glGetFunction("glCopyTexImage2D");
#	endif
#	ifdef glCopyTexSubImage1D
	_glCopyTexSubImage1D = (glCopyTexSubImage1DFunc)glGetFunction("glCopyTexSubImage1D");
#	endif
#	ifdef glCopyTexSubImage2D
	_glCopyTexSubImage2D = (glCopyTexSubImage2DFunc)glGetFunction("glCopyTexSubImage2D");
#	endif
#	ifdef glTexSubImage1D
	_glTexSubImage1D = (glTexSubImage1DFunc)glGetFunction("glTexSubImage1D");
#	endif
#	ifdef glTexSubImage2D
	_glTexSubImage2D = (glTexSubImage2DFunc)glGetFunction("glTexSubImage2D");
#	endif
#	ifdef glBindTexture
	_glBindTexture = (glBindTextureFunc)glGetFunction("glBindTexture");
#	endif
#	ifdef glDeleteTextures
	_glDeleteTextures = (glDeleteTexturesFunc)glGetFunction("glDeleteTextures");
#	endif
#	ifdef glGenTextures
	_glGenTextures = (glGenTexturesFunc)glGetFunction("glGenTextures");
#	endif
#	ifdef glIsTexture
	_glIsTexture = (glIsTextureFunc)glGetFunction("glIsTexture");
#	endif
#	ifdef glArrayElement
	_glArrayElement = (glArrayElementFunc)glGetFunction("glArrayElement");
#	endif
#	ifdef glColorPointer
	_glColorPointer = (glColorPointerFunc)glGetFunction("glColorPointer");
#	endif
#	ifdef glDisableClientState
	_glDisableClientState = (glDisableClientStateFunc)glGetFunction("glDisableClientState");
#	endif
#	ifdef glEdgeFlagPointer
	_glEdgeFlagPointer = (glEdgeFlagPointerFunc)glGetFunction("glEdgeFlagPointer");
#	endif
#	ifdef glEnableClientState
	_glEnableClientState = (glEnableClientStateFunc)glGetFunction("glEnableClientState");
#	endif
#	ifdef glIndexPointer
	_glIndexPointer = (glIndexPointerFunc)glGetFunction("glIndexPointer");
#	endif
#	ifdef glInterleavedArrays
	_glInterleavedArrays = (glInterleavedArraysFunc)glGetFunction("glInterleavedArrays");
#	endif
#	ifdef glNormalPointer
	_glNormalPointer = (glNormalPointerFunc)glGetFunction("glNormalPointer");
#	endif
#	ifdef glTexCoordPointer
	_glTexCoordPointer = (glTexCoordPointerFunc)glGetFunction("glTexCoordPointer");
#	endif
#	ifdef glVertexPointer
	_glVertexPointer = (glVertexPointerFunc)glGetFunction("glVertexPointer");
#	endif
#	ifdef glAreTexturesResident
	_glAreTexturesResident = (glAreTexturesResidentFunc)glGetFunction("glAreTexturesResident");
#	endif
#	ifdef glPrioritizeTextures
	_glPrioritizeTextures = (glPrioritizeTexturesFunc)glGetFunction("glPrioritizeTextures");
#	endif
#	ifdef glIndexub
	_glIndexub = (glIndexubFunc)glGetFunction("glIndexub");
#	endif
#	ifdef glIndexubv
	_glIndexubv = (glIndexubvFunc)glGetFunction("glIndexubv");
#	endif
#	ifdef glPopClientAttrib
	_glPopClientAttrib = (glPopClientAttribFunc)glGetFunction("glPopClientAttrib");
#	endif
#	ifdef glPushClientAttrib
	_glPushClientAttrib = (glPushClientAttribFunc)glGetFunction("glPushClientAttrib");
#	endif
#	ifdef glBlendColor
	_glBlendColor = (glBlendColorFunc)glGetFunction("glBlendColor");
#	endif
#	ifdef glBlendEquation
	_glBlendEquation = (glBlendEquationFunc)glGetFunction("glBlendEquation");
#	endif
#	ifdef glDrawRangeElements
	_glDrawRangeElements = (glDrawRangeElementsFunc)glGetFunction("glDrawRangeElements");
#	endif
#	ifdef glTexImage3D
	_glTexImage3D = (glTexImage3DFunc)glGetFunction("glTexImage3D");
#	endif
#	ifdef glTexSubImage3D
	_glTexSubImage3D = (glTexSubImage3DFunc)glGetFunction("glTexSubImage3D");
#	endif
#	ifdef glCopyTexSubImage3D
	_glCopyTexSubImage3D = (glCopyTexSubImage3DFunc)glGetFunction("glCopyTexSubImage3D");
#	endif
#	ifdef glColorTable
	_glColorTable = (glColorTableFunc)glGetFunction("glColorTable");
#	endif
#	ifdef glColorTableParameterfv
	_glColorTableParameterfv = (glColorTableParameterfvFunc)glGetFunction("glColorTableParameterfv");
#	endif
#	ifdef glColorTableParameteriv
	_glColorTableParameteriv = (glColorTableParameterivFunc)glGetFunction("glColorTableParameteriv");
#	endif
#	ifdef glCopyColorTable
	_glCopyColorTable = (glCopyColorTableFunc)glGetFunction("glCopyColorTable");
#	endif
#	ifdef glGetColorTable
	_glGetColorTable = (glGetColorTableFunc)glGetFunction("glGetColorTable");
#	endif
#	ifdef glGetColorTableParameterfv
	_glGetColorTableParameterfv = (glGetColorTableParameterfvFunc)glGetFunction("glGetColorTableParameterfv");
#	endif
#	ifdef glGetColorTableParameteriv
	_glGetColorTableParameteriv = (glGetColorTableParameterivFunc)glGetFunction("glGetColorTableParameteriv");
#	endif
#	ifdef glColorSubTable
	_glColorSubTable = (glColorSubTableFunc)glGetFunction("glColorSubTable");
#	endif
#	ifdef glCopyColorSubTable
	_glCopyColorSubTable = (glCopyColorSubTableFunc)glGetFunction("glCopyColorSubTable");
#	endif
#	ifdef glConvolutionFilter1D
	_glConvolutionFilter1D = (glConvolutionFilter1DFunc)glGetFunction("glConvolutionFilter1D");
#	endif
#	ifdef glConvolutionFilter2D
	_glConvolutionFilter2D = (glConvolutionFilter2DFunc)glGetFunction("glConvolutionFilter2D");
#	endif
#	ifdef glConvolutionParameterf
	_glConvolutionParameterf = (glConvolutionParameterfFunc)glGetFunction("glConvolutionParameterf");
#	endif
#	ifdef glConvolutionParameterfv
	_glConvolutionParameterfv = (glConvolutionParameterfvFunc)glGetFunction("glConvolutionParameterfv");
#	endif
#	ifdef glConvolutionParameteri
	_glConvolutionParameteri = (glConvolutionParameteriFunc)glGetFunction("glConvolutionParameteri");
#	endif
#	ifdef glConvolutionParameteriv
	_glConvolutionParameteriv = (glConvolutionParameterivFunc)glGetFunction("glConvolutionParameteriv");
#	endif
#	ifdef glCopyConvolutionFilter1D
	_glCopyConvolutionFilter1D = (glCopyConvolutionFilter1DFunc)glGetFunction("glCopyConvolutionFilter1D");
#	endif
#	ifdef glCopyConvolutionFilter2D
	_glCopyConvolutionFilter2D = (glCopyConvolutionFilter2DFunc)glGetFunction("glCopyConvolutionFilter2D");
#	endif
#	ifdef glGetConvolutionFilter
	_glGetConvolutionFilter = (glGetConvolutionFilterFunc)glGetFunction("glGetConvolutionFilter");
#	endif
#	ifdef glGetConvolutionParameterfv
	_glGetConvolutionParameterfv = (glGetConvolutionParameterfvFunc)glGetFunction("glGetConvolutionParameterfv");
#	endif
#	ifdef glGetConvolutionParameteriv
	_glGetConvolutionParameteriv = (glGetConvolutionParameterivFunc)glGetFunction("glGetConvolutionParameteriv");
#	endif
#	ifdef glGetSeparableFilter
	_glGetSeparableFilter = (glGetSeparableFilterFunc)glGetFunction("glGetSeparableFilter");
#	endif
#	ifdef glSeparableFilter2D
	_glSeparableFilter2D = (glSeparableFilter2DFunc)glGetFunction("glSeparableFilter2D");
#	endif
#	ifdef glGetHistogram
	_glGetHistogram = (glGetHistogramFunc)glGetFunction("glGetHistogram");
#	endif
#	ifdef glGetHistogramParameterfv
	_glGetHistogramParameterfv = (glGetHistogramParameterfvFunc)glGetFunction("glGetHistogramParameterfv");
#	endif
#	ifdef glGetHistogramParameteriv
	_glGetHistogramParameteriv = (glGetHistogramParameterivFunc)glGetFunction("glGetHistogramParameteriv");
#	endif
#	ifdef glGetMinmax
	_glGetMinmax = (glGetMinmaxFunc)glGetFunction("glGetMinmax");
#	endif
#	ifdef glGetMinmaxParameterfv
	_glGetMinmaxParameterfv = (glGetMinmaxParameterfvFunc)glGetFunction("glGetMinmaxParameterfv");
#	endif
#	ifdef glGetMinmaxParameteriv
	_glGetMinmaxParameteriv = (glGetMinmaxParameterivFunc)glGetFunction("glGetMinmaxParameteriv");
#	endif
#	ifdef glHistogram
	_glHistogram = (glHistogramFunc)glGetFunction("glHistogram");
#	endif
#	ifdef glMinmax
	_glMinmax = (glMinmaxFunc)glGetFunction("glMinmax");
#	endif
#	ifdef glResetHistogram
	_glResetHistogram = (glResetHistogramFunc)glGetFunction("glResetHistogram");
#	endif
#	ifdef glResetMinmax
	_glResetMinmax = (glResetMinmaxFunc)glGetFunction("glResetMinmax");
#	endif
#	ifdef glActiveTexture
	_glActiveTexture = (glActiveTextureFunc)glGetFunction("glActiveTexture");
#	endif
#	ifdef glSampleCoverage
	_glSampleCoverage = (glSampleCoverageFunc)glGetFunction("glSampleCoverage");
#	endif
#	ifdef glCompressedTexImage3D
	_glCompressedTexImage3D = (glCompressedTexImage3DFunc)glGetFunction("glCompressedTexImage3D");
#	endif
#	ifdef glCompressedTexImage2D
	_glCompressedTexImage2D = (glCompressedTexImage2DFunc)glGetFunction("glCompressedTexImage2D");
#	endif
#	ifdef glCompressedTexImage1D
	_glCompressedTexImage1D = (glCompressedTexImage1DFunc)glGetFunction("glCompressedTexImage1D");
#	endif
#	ifdef glCompressedTexSubImage3D
	_glCompressedTexSubImage3D = (glCompressedTexSubImage3DFunc)glGetFunction("glCompressedTexSubImage3D");
#	endif
#	ifdef glCompressedTexSubImage2D
	_glCompressedTexSubImage2D = (glCompressedTexSubImage2DFunc)glGetFunction("glCompressedTexSubImage2D");
#	endif
#	ifdef glCompressedTexSubImage1D
	_glCompressedTexSubImage1D = (glCompressedTexSubImage1DFunc)glGetFunction("glCompressedTexSubImage1D");
#	endif
#	ifdef glGetCompressedTexImage
	_glGetCompressedTexImage = (glGetCompressedTexImageFunc)glGetFunction("glGetCompressedTexImage");
#	endif
#	ifdef glClientActiveTexture
	_glClientActiveTexture = (glClientActiveTextureFunc)glGetFunction("glClientActiveTexture");
#	endif
#	ifdef glMultiTexCoord1d
	_glMultiTexCoord1d = (glMultiTexCoord1dFunc)glGetFunction("glMultiTexCoord1d");
#	endif
#	ifdef glMultiTexCoord1dv
	_glMultiTexCoord1dv = (glMultiTexCoord1dvFunc)glGetFunction("glMultiTexCoord1dv");
#	endif
#	ifdef glMultiTexCoord1f
	_glMultiTexCoord1f = (glMultiTexCoord1fFunc)glGetFunction("glMultiTexCoord1f");
#	endif
#	ifdef glMultiTexCoord1fv
	_glMultiTexCoord1fv = (glMultiTexCoord1fvFunc)glGetFunction("glMultiTexCoord1fv");
#	endif
#	ifdef glMultiTexCoord1i
	_glMultiTexCoord1i = (glMultiTexCoord1iFunc)glGetFunction("glMultiTexCoord1i");
#	endif
#	ifdef glMultiTexCoord1iv
	_glMultiTexCoord1iv = (glMultiTexCoord1ivFunc)glGetFunction("glMultiTexCoord1iv");
#	endif
#	ifdef glMultiTexCoord1s
	_glMultiTexCoord1s = (glMultiTexCoord1sFunc)glGetFunction("glMultiTexCoord1s");
#	endif
#	ifdef glMultiTexCoord1sv
	_glMultiTexCoord1sv = (glMultiTexCoord1svFunc)glGetFunction("glMultiTexCoord1sv");
#	endif
#	ifdef glMultiTexCoord2d
	_glMultiTexCoord2d = (glMultiTexCoord2dFunc)glGetFunction("glMultiTexCoord2d");
#	endif
#	ifdef glMultiTexCoord2dv
	_glMultiTexCoord2dv = (glMultiTexCoord2dvFunc)glGetFunction("glMultiTexCoord2dv");
#	endif
#	ifdef glMultiTexCoord2f
	_glMultiTexCoord2f = (glMultiTexCoord2fFunc)glGetFunction("glMultiTexCoord2f");
#	endif
#	ifdef glMultiTexCoord2fv
	_glMultiTexCoord2fv = (glMultiTexCoord2fvFunc)glGetFunction("glMultiTexCoord2fv");
#	endif
#	ifdef glMultiTexCoord2i
	_glMultiTexCoord2i = (glMultiTexCoord2iFunc)glGetFunction("glMultiTexCoord2i");
#	endif
#	ifdef glMultiTexCoord2iv
	_glMultiTexCoord2iv = (glMultiTexCoord2ivFunc)glGetFunction("glMultiTexCoord2iv");
#	endif
#	ifdef glMultiTexCoord2s
	_glMultiTexCoord2s = (glMultiTexCoord2sFunc)glGetFunction("glMultiTexCoord2s");
#	endif
#	ifdef glMultiTexCoord2sv
	_glMultiTexCoord2sv = (glMultiTexCoord2svFunc)glGetFunction("glMultiTexCoord2sv");
#	endif
#	ifdef glMultiTexCoord3d
	_glMultiTexCoord3d = (glMultiTexCoord3dFunc)glGetFunction("glMultiTexCoord3d");
#	endif
#	ifdef glMultiTexCoord3dv
	_glMultiTexCoord3dv = (glMultiTexCoord3dvFunc)glGetFunction("glMultiTexCoord3dv");
#	endif
#	ifdef glMultiTexCoord3f
	_glMultiTexCoord3f = (glMultiTexCoord3fFunc)glGetFunction("glMultiTexCoord3f");
#	endif
#	ifdef glMultiTexCoord3fv
	_glMultiTexCoord3fv = (glMultiTexCoord3fvFunc)glGetFunction("glMultiTexCoord3fv");
#	endif
#	ifdef glMultiTexCoord3i
	_glMultiTexCoord3i = (glMultiTexCoord3iFunc)glGetFunction("glMultiTexCoord3i");
#	endif
#	ifdef glMultiTexCoord3iv
	_glMultiTexCoord3iv = (glMultiTexCoord3ivFunc)glGetFunction("glMultiTexCoord3iv");
#	endif
#	ifdef glMultiTexCoord3s
	_glMultiTexCoord3s = (glMultiTexCoord3sFunc)glGetFunction("glMultiTexCoord3s");
#	endif
#	ifdef glMultiTexCoord3sv
	_glMultiTexCoord3sv = (glMultiTexCoord3svFunc)glGetFunction("glMultiTexCoord3sv");
#	endif
#	ifdef glMultiTexCoord4d
	_glMultiTexCoord4d = (glMultiTexCoord4dFunc)glGetFunction("glMultiTexCoord4d");
#	endif
#	ifdef glMultiTexCoord4dv
	_glMultiTexCoord4dv = (glMultiTexCoord4dvFunc)glGetFunction("glMultiTexCoord4dv");
#	endif
#	ifdef glMultiTexCoord4f
	_glMultiTexCoord4f = (glMultiTexCoord4fFunc)glGetFunction("glMultiTexCoord4f");
#	endif
#	ifdef glMultiTexCoord4fv
	_glMultiTexCoord4fv = (glMultiTexCoord4fvFunc)glGetFunction("glMultiTexCoord4fv");
#	endif
#	ifdef glMultiTexCoord4i
	_glMultiTexCoord4i = (glMultiTexCoord4iFunc)glGetFunction("glMultiTexCoord4i");
#	endif
#	ifdef glMultiTexCoord4iv
	_glMultiTexCoord4iv = (glMultiTexCoord4ivFunc)glGetFunction("glMultiTexCoord4iv");
#	endif
#	ifdef glMultiTexCoord4s
	_glMultiTexCoord4s = (glMultiTexCoord4sFunc)glGetFunction("glMultiTexCoord4s");
#	endif
#	ifdef glMultiTexCoord4sv
	_glMultiTexCoord4sv = (glMultiTexCoord4svFunc)glGetFunction("glMultiTexCoord4sv");
#	endif
#	ifdef glLoadTransposeMatrixf
	_glLoadTransposeMatrixf = (glLoadTransposeMatrixfFunc)glGetFunction("glLoadTransposeMatrixf");
#	endif
#	ifdef glLoadTransposeMatrixd
	_glLoadTransposeMatrixd = (glLoadTransposeMatrixdFunc)glGetFunction("glLoadTransposeMatrixd");
#	endif
#	ifdef glMultTransposeMatrixf
	_glMultTransposeMatrixf = (glMultTransposeMatrixfFunc)glGetFunction("glMultTransposeMatrixf");
#	endif
#	ifdef glMultTransposeMatrixd
	_glMultTransposeMatrixd = (glMultTransposeMatrixdFunc)glGetFunction("glMultTransposeMatrixd");
#	endif
#	ifdef glBlendFuncSeparate
	_glBlendFuncSeparate = (glBlendFuncSeparateFunc)glGetFunction("glBlendFuncSeparate");
#	endif
#	ifdef glMultiDrawArrays
	_glMultiDrawArrays = (glMultiDrawArraysFunc)glGetFunction("glMultiDrawArrays");
#	endif
#	ifdef glMultiDrawElements
	_glMultiDrawElements = (glMultiDrawElementsFunc)glGetFunction("glMultiDrawElements");
#	endif
#	ifdef glPointParameterf
	_glPointParameterf = (glPointParameterfFunc)glGetFunction("glPointParameterf");
#	endif
#	ifdef glPointParameterfv
	_glPointParameterfv = (glPointParameterfvFunc)glGetFunction("glPointParameterfv");
#	endif
#	ifdef glPointParameteri
	_glPointParameteri = (glPointParameteriFunc)glGetFunction("glPointParameteri");
#	endif
#	ifdef glPointParameteriv
	_glPointParameteriv = (glPointParameterivFunc)glGetFunction("glPointParameteriv");
#	endif
#	ifdef glFogCoordf
	_glFogCoordf = (glFogCoordfFunc)glGetFunction("glFogCoordf");
#	endif
#	ifdef glFogCoordfv
	_glFogCoordfv = (glFogCoordfvFunc)glGetFunction("glFogCoordfv");
#	endif
#	ifdef glFogCoordd
	_glFogCoordd = (glFogCoorddFunc)glGetFunction("glFogCoordd");
#	endif
#	ifdef glFogCoorddv
	_glFogCoorddv = (glFogCoorddvFunc)glGetFunction("glFogCoorddv");
#	endif
#	ifdef glFogCoordPointer
	_glFogCoordPointer = (glFogCoordPointerFunc)glGetFunction("glFogCoordPointer");
#	endif
#	ifdef glSecondaryColor3b
	_glSecondaryColor3b = (glSecondaryColor3bFunc)glGetFunction("glSecondaryColor3b");
#	endif
#	ifdef glSecondaryColor3bv
	_glSecondaryColor3bv = (glSecondaryColor3bvFunc)glGetFunction("glSecondaryColor3bv");
#	endif
#	ifdef glSecondaryColor3d
	_glSecondaryColor3d = (glSecondaryColor3dFunc)glGetFunction("glSecondaryColor3d");
#	endif
#	ifdef glSecondaryColor3dv
	_glSecondaryColor3dv = (glSecondaryColor3dvFunc)glGetFunction("glSecondaryColor3dv");
#	endif
#	ifdef glSecondaryColor3f
	_glSecondaryColor3f = (glSecondaryColor3fFunc)glGetFunction("glSecondaryColor3f");
#	endif
#	ifdef glSecondaryColor3fv
	_glSecondaryColor3fv = (glSecondaryColor3fvFunc)glGetFunction("glSecondaryColor3fv");
#	endif
#	ifdef glSecondaryColor3i
	_glSecondaryColor3i = (glSecondaryColor3iFunc)glGetFunction("glSecondaryColor3i");
#	endif
#	ifdef glSecondaryColor3iv
	_glSecondaryColor3iv = (glSecondaryColor3ivFunc)glGetFunction("glSecondaryColor3iv");
#	endif
#	ifdef glSecondaryColor3s
	_glSecondaryColor3s = (glSecondaryColor3sFunc)glGetFunction("glSecondaryColor3s");
#	endif
#	ifdef glSecondaryColor3sv
	_glSecondaryColor3sv = (glSecondaryColor3svFunc)glGetFunction("glSecondaryColor3sv");
#	endif
#	ifdef glSecondaryColor3ub
	_glSecondaryColor3ub = (glSecondaryColor3ubFunc)glGetFunction("glSecondaryColor3ub");
#	endif
#	ifdef glSecondaryColor3ubv
	_glSecondaryColor3ubv = (glSecondaryColor3ubvFunc)glGetFunction("glSecondaryColor3ubv");
#	endif
#	ifdef glSecondaryColor3ui
	_glSecondaryColor3ui = (glSecondaryColor3uiFunc)glGetFunction("glSecondaryColor3ui");
#	endif
#	ifdef glSecondaryColor3uiv
	_glSecondaryColor3uiv = (glSecondaryColor3uivFunc)glGetFunction("glSecondaryColor3uiv");
#	endif
#	ifdef glSecondaryColor3us
	_glSecondaryColor3us = (glSecondaryColor3usFunc)glGetFunction("glSecondaryColor3us");
#	endif
#	ifdef glSecondaryColor3usv
	_glSecondaryColor3usv = (glSecondaryColor3usvFunc)glGetFunction("glSecondaryColor3usv");
#	endif
#	ifdef glSecondaryColorPointer
	_glSecondaryColorPointer = (glSecondaryColorPointerFunc)glGetFunction("glSecondaryColorPointer");
#	endif
#	ifdef glWindowPos2d
	_glWindowPos2d = (glWindowPos2dFunc)glGetFunction("glWindowPos2d");
#	endif
#	ifdef glWindowPos2dv
	_glWindowPos2dv = (glWindowPos2dvFunc)glGetFunction("glWindowPos2dv");
#	endif
#	ifdef glWindowPos2f
	_glWindowPos2f = (glWindowPos2fFunc)glGetFunction("glWindowPos2f");
#	endif
#	ifdef glWindowPos2fv
	_glWindowPos2fv = (glWindowPos2fvFunc)glGetFunction("glWindowPos2fv");
#	endif
#	ifdef glWindowPos2i
	_glWindowPos2i = (glWindowPos2iFunc)glGetFunction("glWindowPos2i");
#	endif
#	ifdef glWindowPos2iv
	_glWindowPos2iv = (glWindowPos2ivFunc)glGetFunction("glWindowPos2iv");
#	endif
#	ifdef glWindowPos2s
	_glWindowPos2s = (glWindowPos2sFunc)glGetFunction("glWindowPos2s");
#	endif
#	ifdef glWindowPos2sv
	_glWindowPos2sv = (glWindowPos2svFunc)glGetFunction("glWindowPos2sv");
#	endif
#	ifdef glWindowPos3d
	_glWindowPos3d = (glWindowPos3dFunc)glGetFunction("glWindowPos3d");
#	endif
#	ifdef glWindowPos3dv
	_glWindowPos3dv = (glWindowPos3dvFunc)glGetFunction("glWindowPos3dv");
#	endif
#	ifdef glWindowPos3f
	_glWindowPos3f = (glWindowPos3fFunc)glGetFunction("glWindowPos3f");
#	endif
#	ifdef glWindowPos3fv
	_glWindowPos3fv = (glWindowPos3fvFunc)glGetFunction("glWindowPos3fv");
#	endif
#	ifdef glWindowPos3i
	_glWindowPos3i = (glWindowPos3iFunc)glGetFunction("glWindowPos3i");
#	endif
#	ifdef glWindowPos3iv
	_glWindowPos3iv = (glWindowPos3ivFunc)glGetFunction("glWindowPos3iv");
#	endif
#	ifdef glWindowPos3s
	_glWindowPos3s = (glWindowPos3sFunc)glGetFunction("glWindowPos3s");
#	endif
#	ifdef glWindowPos3sv
	_glWindowPos3sv = (glWindowPos3svFunc)glGetFunction("glWindowPos3sv");
#	endif
#	ifdef glGenQueries
	_glGenQueries = (glGenQueriesFunc)glGetFunction("glGenQueries");
#	endif
#	ifdef glDeleteQueries
	_glDeleteQueries = (glDeleteQueriesFunc)glGetFunction("glDeleteQueries");
#	endif
#	ifdef glIsQuery
	_glIsQuery = (glIsQueryFunc)glGetFunction("glIsQuery");
#	endif
#	ifdef glBeginQuery
	_glBeginQuery = (glBeginQueryFunc)glGetFunction("glBeginQuery");
#	endif
#	ifdef glEndQuery
	_glEndQuery = (glEndQueryFunc)glGetFunction("glEndQuery");
#	endif
#	ifdef glGetQueryiv
	_glGetQueryiv = (glGetQueryivFunc)glGetFunction("glGetQueryiv");
#	endif
#	ifdef glGetQueryObjectiv
	_glGetQueryObjectiv = (glGetQueryObjectivFunc)glGetFunction("glGetQueryObjectiv");
#	endif
#	ifdef glGetQueryObjectuiv
	_glGetQueryObjectuiv = (glGetQueryObjectuivFunc)glGetFunction("glGetQueryObjectuiv");
#	endif
#	ifdef glBindBuffer
	_glBindBuffer = (glBindBufferFunc)glGetFunction("glBindBuffer");
#	endif
#	ifdef glDeleteBuffers
	_glDeleteBuffers = (glDeleteBuffersFunc)glGetFunction("glDeleteBuffers");
#	endif
#	ifdef glGenBuffers
	_glGenBuffers = (glGenBuffersFunc)glGetFunction("glGenBuffers");
#	endif
#	ifdef glIsBuffer
	_glIsBuffer = (glIsBufferFunc)glGetFunction("glIsBuffer");
#	endif
#	ifdef glBufferData
	_glBufferData = (glBufferDataFunc)glGetFunction("glBufferData");
#	endif
#	ifdef glBufferSubData
	_glBufferSubData = (glBufferSubDataFunc)glGetFunction("glBufferSubData");
#	endif
#	ifdef glGetBufferSubData
	_glGetBufferSubData = (glGetBufferSubDataFunc)glGetFunction("glGetBufferSubData");
#	endif
#	ifdef glMapBuffer
	_glMapBuffer = (glMapBufferFunc)glGetFunction("glMapBuffer");
#	endif
#	ifdef glUnmapBuffer
	_glUnmapBuffer = (glUnmapBufferFunc)glGetFunction("glUnmapBuffer");
#	endif
#	ifdef glGetBufferParameteriv
	_glGetBufferParameteriv = (glGetBufferParameterivFunc)glGetFunction("glGetBufferParameteriv");
#	endif
#	ifdef glGetBufferPointerv
	_glGetBufferPointerv = (glGetBufferPointervFunc)glGetFunction("glGetBufferPointerv");
#	endif
#	ifdef glBlendEquationSeparate
	_glBlendEquationSeparate = (glBlendEquationSeparateFunc)glGetFunction("glBlendEquationSeparate");
#	endif
#	ifdef glDrawBuffers
	_glDrawBuffers = (glDrawBuffersFunc)glGetFunction("glDrawBuffers");
#	endif
#	ifdef glStencilOpSeparate
	_glStencilOpSeparate = (glStencilOpSeparateFunc)glGetFunction("glStencilOpSeparate");
#	endif
#	ifdef glStencilFuncSeparate
	_glStencilFuncSeparate = (glStencilFuncSeparateFunc)glGetFunction("glStencilFuncSeparate");
#	endif
#	ifdef glStencilMaskSeparate
	_glStencilMaskSeparate = (glStencilMaskSeparateFunc)glGetFunction("glStencilMaskSeparate");
#	endif
#	ifdef glAttachShader
	_glAttachShader = (glAttachShaderFunc)glGetFunction("glAttachShader");
#	endif
#	ifdef glBindAttribLocation
	_glBindAttribLocation = (glBindAttribLocationFunc)glGetFunction("glBindAttribLocation");
#	endif
#	ifdef glCompileShader
	_glCompileShader = (glCompileShaderFunc)glGetFunction("glCompileShader");
#	endif
#	ifdef glCreateProgram
	_glCreateProgram = (glCreateProgramFunc)glGetFunction("glCreateProgram");
#	endif
#	ifdef glCreateShader
	_glCreateShader = (glCreateShaderFunc)glGetFunction("glCreateShader");
#	endif
#	ifdef glDeleteProgram
	_glDeleteProgram = (glDeleteProgramFunc)glGetFunction("glDeleteProgram");
#	endif
#	ifdef glDeleteShader
	_glDeleteShader = (glDeleteShaderFunc)glGetFunction("glDeleteShader");
#	endif
#	ifdef glDetachShader
	_glDetachShader = (glDetachShaderFunc)glGetFunction("glDetachShader");
#	endif
#	ifdef glDisableVertexAttribArray
	_glDisableVertexAttribArray = (glDisableVertexAttribArrayFunc)glGetFunction("glDisableVertexAttribArray");
#	endif
#	ifdef glEnableVertexAttribArray
	_glEnableVertexAttribArray = (glEnableVertexAttribArrayFunc)glGetFunction("glEnableVertexAttribArray");
#	endif
#	ifdef glGetActiveAttrib
	_glGetActiveAttrib = (glGetActiveAttribFunc)glGetFunction("glGetActiveAttrib");
#	endif
#	ifdef glGetActiveUniform
	_glGetActiveUniform = (glGetActiveUniformFunc)glGetFunction("glGetActiveUniform");
#	endif
#	ifdef glGetAttachedShaders
	_glGetAttachedShaders = (glGetAttachedShadersFunc)glGetFunction("glGetAttachedShaders");
#	endif
#	ifdef glGetAttribLocation
	_glGetAttribLocation = (glGetAttribLocationFunc)glGetFunction("glGetAttribLocation");
#	endif
#	ifdef glGetProgramiv
	_glGetProgramiv = (glGetProgramivFunc)glGetFunction("glGetProgramiv");
#	endif
#	ifdef glGetProgramInfoLog
	_glGetProgramInfoLog = (glGetProgramInfoLogFunc)glGetFunction("glGetProgramInfoLog");
#	endif
#	ifdef glGetShaderiv
	_glGetShaderiv = (glGetShaderivFunc)glGetFunction("glGetShaderiv");
#	endif
#	ifdef glGetShaderInfoLog
	_glGetShaderInfoLog = (glGetShaderInfoLogFunc)glGetFunction("glGetShaderInfoLog");
#	endif
#	ifdef glGetShaderSource
	_glGetShaderSource = (glGetShaderSourceFunc)glGetFunction("glGetShaderSource");
#	endif
#	ifdef glGetUniformLocation
	_glGetUniformLocation = (glGetUniformLocationFunc)glGetFunction("glGetUniformLocation");
#	endif
#	ifdef glGetUniformfv
	_glGetUniformfv = (glGetUniformfvFunc)glGetFunction("glGetUniformfv");
#	endif
#	ifdef glGetUniformiv
	_glGetUniformiv = (glGetUniformivFunc)glGetFunction("glGetUniformiv");
#	endif
#	ifdef glGetVertexAttribdv
	_glGetVertexAttribdv = (glGetVertexAttribdvFunc)glGetFunction("glGetVertexAttribdv");
#	endif
#	ifdef glGetVertexAttribfv
	_glGetVertexAttribfv = (glGetVertexAttribfvFunc)glGetFunction("glGetVertexAttribfv");
#	endif
#	ifdef glGetVertexAttribiv
	_glGetVertexAttribiv = (glGetVertexAttribivFunc)glGetFunction("glGetVertexAttribiv");
#	endif
#	ifdef glGetVertexAttribPointerv
	_glGetVertexAttribPointerv = (glGetVertexAttribPointervFunc)glGetFunction("glGetVertexAttribPointerv");
#	endif
#	ifdef glIsProgram
	_glIsProgram = (glIsProgramFunc)glGetFunction("glIsProgram");
#	endif
#	ifdef glIsShader
	_glIsShader = (glIsShaderFunc)glGetFunction("glIsShader");
#	endif
#	ifdef glLinkProgram
	_glLinkProgram = (glLinkProgramFunc)glGetFunction("glLinkProgram");
#	endif
#	ifdef glShaderSource
	_glShaderSource = (glShaderSourceFunc)glGetFunction("glShaderSource");
#	endif
#	ifdef glUseProgram
	_glUseProgram = (glUseProgramFunc)glGetFunction("glUseProgram");
#	endif
#	ifdef glUniform1f
	_glUniform1f = (glUniform1fFunc)glGetFunction("glUniform1f");
#	endif
#	ifdef glUniform2f
	_glUniform2f = (glUniform2fFunc)glGetFunction("glUniform2f");
#	endif
#	ifdef glUniform3f
	_glUniform3f = (glUniform3fFunc)glGetFunction("glUniform3f");
#	endif
#	ifdef glUniform4f
	_glUniform4f = (glUniform4fFunc)glGetFunction("glUniform4f");
#	endif
#	ifdef glUniform1i
	_glUniform1i = (glUniform1iFunc)glGetFunction("glUniform1i");
#	endif
#	ifdef glUniform2i
	_glUniform2i = (glUniform2iFunc)glGetFunction("glUniform2i");
#	endif
#	ifdef glUniform3i
	_glUniform3i = (glUniform3iFunc)glGetFunction("glUniform3i");
#	endif
#	ifdef glUniform4i
	_glUniform4i = (glUniform4iFunc)glGetFunction("glUniform4i");
#	endif
#	ifdef glUniform1fv
	_glUniform1fv = (glUniform1fvFunc)glGetFunction("glUniform1fv");
#	endif
#	ifdef glUniform2fv
	_glUniform2fv = (glUniform2fvFunc)glGetFunction("glUniform2fv");
#	endif
#	ifdef glUniform3fv
	_glUniform3fv = (glUniform3fvFunc)glGetFunction("glUniform3fv");
#	endif
#	ifdef glUniform4fv
	_glUniform4fv = (glUniform4fvFunc)glGetFunction("glUniform4fv");
#	endif
#	ifdef glUniform1iv
	_glUniform1iv = (glUniform1ivFunc)glGetFunction("glUniform1iv");
#	endif
#	ifdef glUniform2iv
	_glUniform2iv = (glUniform2ivFunc)glGetFunction("glUniform2iv");
#	endif
#	ifdef glUniform3iv
	_glUniform3iv = (glUniform3ivFunc)glGetFunction("glUniform3iv");
#	endif
#	ifdef glUniform4iv
	_glUniform4iv = (glUniform4ivFunc)glGetFunction("glUniform4iv");
#	endif
#	ifdef glUniformMatrix2fv
	_glUniformMatrix2fv = (glUniformMatrix2fvFunc)glGetFunction("glUniformMatrix2fv");
#	endif
#	ifdef glUniformMatrix3fv
	_glUniformMatrix3fv = (glUniformMatrix3fvFunc)glGetFunction("glUniformMatrix3fv");
#	endif
#	ifdef glUniformMatrix4fv
	_glUniformMatrix4fv = (glUniformMatrix4fvFunc)glGetFunction("glUniformMatrix4fv");
#	endif
#	ifdef glValidateProgram
	_glValidateProgram = (glValidateProgramFunc)glGetFunction("glValidateProgram");
#	endif
#	ifdef glVertexAttrib1d
	_glVertexAttrib1d = (glVertexAttrib1dFunc)glGetFunction("glVertexAttrib1d");
#	endif
#	ifdef glVertexAttrib1dv
	_glVertexAttrib1dv = (glVertexAttrib1dvFunc)glGetFunction("glVertexAttrib1dv");
#	endif
#	ifdef glVertexAttrib1f
	_glVertexAttrib1f = (glVertexAttrib1fFunc)glGetFunction("glVertexAttrib1f");
#	endif
#	ifdef glVertexAttrib1fv
	_glVertexAttrib1fv = (glVertexAttrib1fvFunc)glGetFunction("glVertexAttrib1fv");
#	endif
#	ifdef glVertexAttrib1s
	_glVertexAttrib1s = (glVertexAttrib1sFunc)glGetFunction("glVertexAttrib1s");
#	endif
#	ifdef glVertexAttrib1sv
	_glVertexAttrib1sv = (glVertexAttrib1svFunc)glGetFunction("glVertexAttrib1sv");
#	endif
#	ifdef glVertexAttrib2d
	_glVertexAttrib2d = (glVertexAttrib2dFunc)glGetFunction("glVertexAttrib2d");
#	endif
#	ifdef glVertexAttrib2dv
	_glVertexAttrib2dv = (glVertexAttrib2dvFunc)glGetFunction("glVertexAttrib2dv");
#	endif
#	ifdef glVertexAttrib2f
	_glVertexAttrib2f = (glVertexAttrib2fFunc)glGetFunction("glVertexAttrib2f");
#	endif
#	ifdef glVertexAttrib2fv
	_glVertexAttrib2fv = (glVertexAttrib2fvFunc)glGetFunction("glVertexAttrib2fv");
#	endif
#	ifdef glVertexAttrib2s
	_glVertexAttrib2s = (glVertexAttrib2sFunc)glGetFunction("glVertexAttrib2s");
#	endif
#	ifdef glVertexAttrib2sv
	_glVertexAttrib2sv = (glVertexAttrib2svFunc)glGetFunction("glVertexAttrib2sv");
#	endif
#	ifdef glVertexAttrib3d
	_glVertexAttrib3d = (glVertexAttrib3dFunc)glGetFunction("glVertexAttrib3d");
#	endif
#	ifdef glVertexAttrib3dv
	_glVertexAttrib3dv = (glVertexAttrib3dvFunc)glGetFunction("glVertexAttrib3dv");
#	endif
#	ifdef glVertexAttrib3f
	_glVertexAttrib3f = (glVertexAttrib3fFunc)glGetFunction("glVertexAttrib3f");
#	endif
#	ifdef glVertexAttrib3fv
	_glVertexAttrib3fv = (glVertexAttrib3fvFunc)glGetFunction("glVertexAttrib3fv");
#	endif
#	ifdef glVertexAttrib3s
	_glVertexAttrib3s = (glVertexAttrib3sFunc)glGetFunction("glVertexAttrib3s");
#	endif
#	ifdef glVertexAttrib3sv
	_glVertexAttrib3sv = (glVertexAttrib3svFunc)glGetFunction("glVertexAttrib3sv");
#	endif
#	ifdef glVertexAttrib4Nbv
	_glVertexAttrib4Nbv = (glVertexAttrib4NbvFunc)glGetFunction("glVertexAttrib4Nbv");
#	endif
#	ifdef glVertexAttrib4Niv
	_glVertexAttrib4Niv = (glVertexAttrib4NivFunc)glGetFunction("glVertexAttrib4Niv");
#	endif
#	ifdef glVertexAttrib4Nsv
	_glVertexAttrib4Nsv = (glVertexAttrib4NsvFunc)glGetFunction("glVertexAttrib4Nsv");
#	endif
#	ifdef glVertexAttrib4Nub
	_glVertexAttrib4Nub = (glVertexAttrib4NubFunc)glGetFunction("glVertexAttrib4Nub");
#	endif
#	ifdef glVertexAttrib4Nubv
	_glVertexAttrib4Nubv = (glVertexAttrib4NubvFunc)glGetFunction("glVertexAttrib4Nubv");
#	endif
#	ifdef glVertexAttrib4Nuiv
	_glVertexAttrib4Nuiv = (glVertexAttrib4NuivFunc)glGetFunction("glVertexAttrib4Nuiv");
#	endif
#	ifdef glVertexAttrib4Nusv
	_glVertexAttrib4Nusv = (glVertexAttrib4NusvFunc)glGetFunction("glVertexAttrib4Nusv");
#	endif
#	ifdef glVertexAttrib4bv
	_glVertexAttrib4bv = (glVertexAttrib4bvFunc)glGetFunction("glVertexAttrib4bv");
#	endif
#	ifdef glVertexAttrib4d
	_glVertexAttrib4d = (glVertexAttrib4dFunc)glGetFunction("glVertexAttrib4d");
#	endif
#	ifdef glVertexAttrib4dv
	_glVertexAttrib4dv = (glVertexAttrib4dvFunc)glGetFunction("glVertexAttrib4dv");
#	endif
#	ifdef glVertexAttrib4f
	_glVertexAttrib4f = (glVertexAttrib4fFunc)glGetFunction("glVertexAttrib4f");
#	endif
#	ifdef glVertexAttrib4fv
	_glVertexAttrib4fv = (glVertexAttrib4fvFunc)glGetFunction("glVertexAttrib4fv");
#	endif
#	ifdef glVertexAttrib4iv
	_glVertexAttrib4iv = (glVertexAttrib4ivFunc)glGetFunction("glVertexAttrib4iv");
#	endif
#	ifdef glVertexAttrib4s
	_glVertexAttrib4s = (glVertexAttrib4sFunc)glGetFunction("glVertexAttrib4s");
#	endif
#	ifdef glVertexAttrib4sv
	_glVertexAttrib4sv = (glVertexAttrib4svFunc)glGetFunction("glVertexAttrib4sv");
#	endif
#	ifdef glVertexAttrib4ubv
	_glVertexAttrib4ubv = (glVertexAttrib4ubvFunc)glGetFunction("glVertexAttrib4ubv");
#	endif
#	ifdef glVertexAttrib4uiv
	_glVertexAttrib4uiv = (glVertexAttrib4uivFunc)glGetFunction("glVertexAttrib4uiv");
#	endif
#	ifdef glVertexAttrib4usv
	_glVertexAttrib4usv = (glVertexAttrib4usvFunc)glGetFunction("glVertexAttrib4usv");
#	endif
#	ifdef glVertexAttribPointer
	_glVertexAttribPointer = (glVertexAttribPointerFunc)glGetFunction("glVertexAttribPointer");
#	endif
#	ifdef glUniformMatrix2x3fv
	_glUniformMatrix2x3fv = (glUniformMatrix2x3fvFunc)glGetFunction("glUniformMatrix2x3fv");
#	endif
#	ifdef glUniformMatrix3x2fv
	_glUniformMatrix3x2fv = (glUniformMatrix3x2fvFunc)glGetFunction("glUniformMatrix3x2fv");
#	endif
#	ifdef glUniformMatrix2x4fv
	_glUniformMatrix2x4fv = (glUniformMatrix2x4fvFunc)glGetFunction("glUniformMatrix2x4fv");
#	endif
#	ifdef glUniformMatrix4x2fv
	_glUniformMatrix4x2fv = (glUniformMatrix4x2fvFunc)glGetFunction("glUniformMatrix4x2fv");
#	endif
#	ifdef glUniformMatrix3x4fv
	_glUniformMatrix3x4fv = (glUniformMatrix3x4fvFunc)glGetFunction("glUniformMatrix3x4fv");
#	endif
#	ifdef glUniformMatrix4x3fv
	_glUniformMatrix4x3fv = (glUniformMatrix4x3fvFunc)glGetFunction("glUniformMatrix4x3fv");
#	endif
#	ifdef glColorMaski
	_glColorMaski = (glColorMaskiFunc)glGetFunction("glColorMaski");
#	endif
#	ifdef glGetBooleani_v
	_glGetBooleani_v = (glGetBooleani_vFunc)glGetFunction("glGetBooleani_v");
#	endif
#	ifdef glGetIntegeri_v
	_glGetIntegeri_v = (glGetIntegeri_vFunc)glGetFunction("glGetIntegeri_v");
#	endif
#	ifdef glEnablei
	_glEnablei = (glEnableiFunc)glGetFunction("glEnablei");
#	endif
#	ifdef glDisablei
	_glDisablei = (glDisableiFunc)glGetFunction("glDisablei");
#	endif
#	ifdef glIsEnabledi
	_glIsEnabledi = (glIsEnablediFunc)glGetFunction("glIsEnabledi");
#	endif
#	ifdef glBeginTransformFeedback
	_glBeginTransformFeedback = (glBeginTransformFeedbackFunc)glGetFunction("glBeginTransformFeedback");
#	endif
#	ifdef glEndTransformFeedback
	_glEndTransformFeedback = (glEndTransformFeedbackFunc)glGetFunction("glEndTransformFeedback");
#	endif
#	ifdef glBindBufferRange
	_glBindBufferRange = (glBindBufferRangeFunc)glGetFunction("glBindBufferRange");
#	endif
#	ifdef glBindBufferBase
	_glBindBufferBase = (glBindBufferBaseFunc)glGetFunction("glBindBufferBase");
#	endif
#	ifdef glTransformFeedbackVaryings
	_glTransformFeedbackVaryings = (glTransformFeedbackVaryingsFunc)glGetFunction("glTransformFeedbackVaryings");
#	endif
#	ifdef glGetTransformFeedbackVarying
	_glGetTransformFeedbackVarying = (glGetTransformFeedbackVaryingFunc)glGetFunction("glGetTransformFeedbackVarying");
#	endif
#	ifdef glClampColor
	_glClampColor = (glClampColorFunc)glGetFunction("glClampColor");
#	endif
#	ifdef glBeginConditionalRender
	_glBeginConditionalRender = (glBeginConditionalRenderFunc)glGetFunction("glBeginConditionalRender");
#	endif
#	ifdef glEndConditionalRender
	_glEndConditionalRender = (glEndConditionalRenderFunc)glGetFunction("glEndConditionalRender");
#	endif
#	ifdef glVertexAttribIPointer
	_glVertexAttribIPointer = (glVertexAttribIPointerFunc)glGetFunction("glVertexAttribIPointer");
#	endif
#	ifdef glGetVertexAttribIiv
	_glGetVertexAttribIiv = (glGetVertexAttribIivFunc)glGetFunction("glGetVertexAttribIiv");
#	endif
#	ifdef glGetVertexAttribIuiv
	_glGetVertexAttribIuiv = (glGetVertexAttribIuivFunc)glGetFunction("glGetVertexAttribIuiv");
#	endif
#	ifdef glVertexAttribI1i
	_glVertexAttribI1i = (glVertexAttribI1iFunc)glGetFunction("glVertexAttribI1i");
#	endif
#	ifdef glVertexAttribI2i
	_glVertexAttribI2i = (glVertexAttribI2iFunc)glGetFunction("glVertexAttribI2i");
#	endif
#	ifdef glVertexAttribI3i
	_glVertexAttribI3i = (glVertexAttribI3iFunc)glGetFunction("glVertexAttribI3i");
#	endif
#	ifdef glVertexAttribI4i
	_glVertexAttribI4i = (glVertexAttribI4iFunc)glGetFunction("glVertexAttribI4i");
#	endif
#	ifdef glVertexAttribI1ui
	_glVertexAttribI1ui = (glVertexAttribI1uiFunc)glGetFunction("glVertexAttribI1ui");
#	endif
#	ifdef glVertexAttribI2ui
	_glVertexAttribI2ui = (glVertexAttribI2uiFunc)glGetFunction("glVertexAttribI2ui");
#	endif
#	ifdef glVertexAttribI3ui
	_glVertexAttribI3ui = (glVertexAttribI3uiFunc)glGetFunction("glVertexAttribI3ui");
#	endif
#	ifdef glVertexAttribI4ui
	_glVertexAttribI4ui = (glVertexAttribI4uiFunc)glGetFunction("glVertexAttribI4ui");
#	endif
#	ifdef glVertexAttribI1iv
	_glVertexAttribI1iv = (glVertexAttribI1ivFunc)glGetFunction("glVertexAttribI1iv");
#	endif
#	ifdef glVertexAttribI2iv
	_glVertexAttribI2iv = (glVertexAttribI2ivFunc)glGetFunction("glVertexAttribI2iv");
#	endif
#	ifdef glVertexAttribI3iv
	_glVertexAttribI3iv = (glVertexAttribI3ivFunc)glGetFunction("glVertexAttribI3iv");
#	endif
#	ifdef glVertexAttribI4iv
	_glVertexAttribI4iv = (glVertexAttribI4ivFunc)glGetFunction("glVertexAttribI4iv");
#	endif
#	ifdef glVertexAttribI1uiv
	_glVertexAttribI1uiv = (glVertexAttribI1uivFunc)glGetFunction("glVertexAttribI1uiv");
#	endif
#	ifdef glVertexAttribI2uiv
	_glVertexAttribI2uiv = (glVertexAttribI2uivFunc)glGetFunction("glVertexAttribI2uiv");
#	endif
#	ifdef glVertexAttribI3uiv
	_glVertexAttribI3uiv = (glVertexAttribI3uivFunc)glGetFunction("glVertexAttribI3uiv");
#	endif
#	ifdef glVertexAttribI4uiv
	_glVertexAttribI4uiv = (glVertexAttribI4uivFunc)glGetFunction("glVertexAttribI4uiv");
#	endif
#	ifdef glVertexAttribI4bv
	_glVertexAttribI4bv = (glVertexAttribI4bvFunc)glGetFunction("glVertexAttribI4bv");
#	endif
#	ifdef glVertexAttribI4sv
	_glVertexAttribI4sv = (glVertexAttribI4svFunc)glGetFunction("glVertexAttribI4sv");
#	endif
#	ifdef glVertexAttribI4ubv
	_glVertexAttribI4ubv = (glVertexAttribI4ubvFunc)glGetFunction("glVertexAttribI4ubv");
#	endif
#	ifdef glVertexAttribI4usv
	_glVertexAttribI4usv = (glVertexAttribI4usvFunc)glGetFunction("glVertexAttribI4usv");
#	endif
#	ifdef glGetUniformuiv
	_glGetUniformuiv = (glGetUniformuivFunc)glGetFunction("glGetUniformuiv");
#	endif
#	ifdef glBindFragDataLocation
	_glBindFragDataLocation = (glBindFragDataLocationFunc)glGetFunction("glBindFragDataLocation");
#	endif
#	ifdef glGetFragDataLocation
	_glGetFragDataLocation = (glGetFragDataLocationFunc)glGetFunction("glGetFragDataLocation");
#	endif
#	ifdef glUniform1ui
	_glUniform1ui = (glUniform1uiFunc)glGetFunction("glUniform1ui");
#	endif
#	ifdef glUniform2ui
	_glUniform2ui = (glUniform2uiFunc)glGetFunction("glUniform2ui");
#	endif
#	ifdef glUniform3ui
	_glUniform3ui = (glUniform3uiFunc)glGetFunction("glUniform3ui");
#	endif
#	ifdef glUniform4ui
	_glUniform4ui = (glUniform4uiFunc)glGetFunction("glUniform4ui");
#	endif
#	ifdef glUniform1uiv
	_glUniform1uiv = (glUniform1uivFunc)glGetFunction("glUniform1uiv");
#	endif
#	ifdef glUniform2uiv
	_glUniform2uiv = (glUniform2uivFunc)glGetFunction("glUniform2uiv");
#	endif
#	ifdef glUniform3uiv
	_glUniform3uiv = (glUniform3uivFunc)glGetFunction("glUniform3uiv");
#	endif
#	ifdef glUniform4uiv
	_glUniform4uiv = (glUniform4uivFunc)glGetFunction("glUniform4uiv");
#	endif
#	ifdef glTexParameterIiv
	_glTexParameterIiv = (glTexParameterIivFunc)glGetFunction("glTexParameterIiv");
#	endif
#	ifdef glTexParameterIuiv
	_glTexParameterIuiv = (glTexParameterIuivFunc)glGetFunction("glTexParameterIuiv");
#	endif
#	ifdef glGetTexParameterIiv
	_glGetTexParameterIiv = (glGetTexParameterIivFunc)glGetFunction("glGetTexParameterIiv");
#	endif
#	ifdef glGetTexParameterIuiv
	_glGetTexParameterIuiv = (glGetTexParameterIuivFunc)glGetFunction("glGetTexParameterIuiv");
#	endif
#	ifdef glClearBufferiv
	_glClearBufferiv = (glClearBufferivFunc)glGetFunction("glClearBufferiv");
#	endif
#	ifdef glClearBufferuiv
	_glClearBufferuiv = (glClearBufferuivFunc)glGetFunction("glClearBufferuiv");
#	endif
#	ifdef glClearBufferfv
	_glClearBufferfv = (glClearBufferfvFunc)glGetFunction("glClearBufferfv");
#	endif
#	ifdef glClearBufferfi
	_glClearBufferfi = (glClearBufferfiFunc)glGetFunction("glClearBufferfi");
#	endif
#	ifdef glGetStringi
	_glGetStringi = (glGetStringiFunc)glGetFunction("glGetStringi");
#	endif
#	ifdef glDrawArraysInstanced
	_glDrawArraysInstanced = (glDrawArraysInstancedFunc)glGetFunction("glDrawArraysInstanced");
#	endif
#	ifdef glDrawElementsInstanced
	_glDrawElementsInstanced = (glDrawElementsInstancedFunc)glGetFunction("glDrawElementsInstanced");
#	endif
#	ifdef glTexBuffer
	_glTexBuffer = (glTexBufferFunc)glGetFunction("glTexBuffer");
#	endif
#	ifdef glPrimitiveRestartIndex
	_glPrimitiveRestartIndex = (glPrimitiveRestartIndexFunc)glGetFunction("glPrimitiveRestartIndex");
#	endif
#	ifdef glGetInteger64i_v
	_glGetInteger64i_v = (glGetInteger64i_vFunc)glGetFunction("glGetInteger64i_v");
#	endif
#	ifdef glGetBufferParameteri64v
	_glGetBufferParameteri64v = (glGetBufferParameteri64vFunc)glGetFunction("glGetBufferParameteri64v");
#	endif
#	ifdef glFramebufferTexture
	_glFramebufferTexture = (glFramebufferTextureFunc)glGetFunction("glFramebufferTexture");
#	endif
#	ifdef glVertexAttribDivisor
	_glVertexAttribDivisor = (glVertexAttribDivisorFunc)glGetFunction("glVertexAttribDivisor");
#	endif
#	ifdef glMinSampleShading
	_glMinSampleShading = (glMinSampleShadingFunc)glGetFunction("glMinSampleShading");
#	endif
#	ifdef glBlendEquationi
	_glBlendEquationi = (glBlendEquationiFunc)glGetFunction("glBlendEquationi");
#	endif
#	ifdef glBlendEquationSeparatei
	_glBlendEquationSeparatei = (glBlendEquationSeparateiFunc)glGetFunction("glBlendEquationSeparatei");
#	endif
#	ifdef glBlendFunci
	_glBlendFunci = (glBlendFunciFunc)glGetFunction("glBlendFunci");
#	endif
#	ifdef glBlendFuncSeparatei
	_glBlendFuncSeparatei = (glBlendFuncSeparateiFunc)glGetFunction("glBlendFuncSeparatei");
#	endif
#	ifdef glActiveTextureARB
	_glActiveTextureARB = (glActiveTextureARBFunc)glGetFunction("glActiveTextureARB");
#	endif
#	ifdef glClientActiveTextureARB
	_glClientActiveTextureARB = (glClientActiveTextureARBFunc)glGetFunction("glClientActiveTextureARB");
#	endif
#	ifdef glMultiTexCoord1dARB
	_glMultiTexCoord1dARB = (glMultiTexCoord1dARBFunc)glGetFunction("glMultiTexCoord1dARB");
#	endif
#	ifdef glMultiTexCoord1dvARB
	_glMultiTexCoord1dvARB = (glMultiTexCoord1dvARBFunc)glGetFunction("glMultiTexCoord1dvARB");
#	endif
#	ifdef glMultiTexCoord1fARB
	_glMultiTexCoord1fARB = (glMultiTexCoord1fARBFunc)glGetFunction("glMultiTexCoord1fARB");
#	endif
#	ifdef glMultiTexCoord1fvARB
	_glMultiTexCoord1fvARB = (glMultiTexCoord1fvARBFunc)glGetFunction("glMultiTexCoord1fvARB");
#	endif
#	ifdef glMultiTexCoord1iARB
	_glMultiTexCoord1iARB = (glMultiTexCoord1iARBFunc)glGetFunction("glMultiTexCoord1iARB");
#	endif
#	ifdef glMultiTexCoord1ivARB
	_glMultiTexCoord1ivARB = (glMultiTexCoord1ivARBFunc)glGetFunction("glMultiTexCoord1ivARB");
#	endif
#	ifdef glMultiTexCoord1sARB
	_glMultiTexCoord1sARB = (glMultiTexCoord1sARBFunc)glGetFunction("glMultiTexCoord1sARB");
#	endif
#	ifdef glMultiTexCoord1svARB
	_glMultiTexCoord1svARB = (glMultiTexCoord1svARBFunc)glGetFunction("glMultiTexCoord1svARB");
#	endif
#	ifdef glMultiTexCoord2dARB
	_glMultiTexCoord2dARB = (glMultiTexCoord2dARBFunc)glGetFunction("glMultiTexCoord2dARB");
#	endif
#	ifdef glMultiTexCoord2dvARB
	_glMultiTexCoord2dvARB = (glMultiTexCoord2dvARBFunc)glGetFunction("glMultiTexCoord2dvARB");
#	endif
#	ifdef glMultiTexCoord2fARB
	_glMultiTexCoord2fARB = (glMultiTexCoord2fARBFunc)glGetFunction("glMultiTexCoord2fARB");
#	endif
#	ifdef glMultiTexCoord2fvARB
	_glMultiTexCoord2fvARB = (glMultiTexCoord2fvARBFunc)glGetFunction("glMultiTexCoord2fvARB");
#	endif
#	ifdef glMultiTexCoord2iARB
	_glMultiTexCoord2iARB = (glMultiTexCoord2iARBFunc)glGetFunction("glMultiTexCoord2iARB");
#	endif
#	ifdef glMultiTexCoord2ivARB
	_glMultiTexCoord2ivARB = (glMultiTexCoord2ivARBFunc)glGetFunction("glMultiTexCoord2ivARB");
#	endif
#	ifdef glMultiTexCoord2sARB
	_glMultiTexCoord2sARB = (glMultiTexCoord2sARBFunc)glGetFunction("glMultiTexCoord2sARB");
#	endif
#	ifdef glMultiTexCoord2svARB
	_glMultiTexCoord2svARB = (glMultiTexCoord2svARBFunc)glGetFunction("glMultiTexCoord2svARB");
#	endif
#	ifdef glMultiTexCoord3dARB
	_glMultiTexCoord3dARB = (glMultiTexCoord3dARBFunc)glGetFunction("glMultiTexCoord3dARB");
#	endif
#	ifdef glMultiTexCoord3dvARB
	_glMultiTexCoord3dvARB = (glMultiTexCoord3dvARBFunc)glGetFunction("glMultiTexCoord3dvARB");
#	endif
#	ifdef glMultiTexCoord3fARB
	_glMultiTexCoord3fARB = (glMultiTexCoord3fARBFunc)glGetFunction("glMultiTexCoord3fARB");
#	endif
#	ifdef glMultiTexCoord3fvARB
	_glMultiTexCoord3fvARB = (glMultiTexCoord3fvARBFunc)glGetFunction("glMultiTexCoord3fvARB");
#	endif
#	ifdef glMultiTexCoord3iARB
	_glMultiTexCoord3iARB = (glMultiTexCoord3iARBFunc)glGetFunction("glMultiTexCoord3iARB");
#	endif
#	ifdef glMultiTexCoord3ivARB
	_glMultiTexCoord3ivARB = (glMultiTexCoord3ivARBFunc)glGetFunction("glMultiTexCoord3ivARB");
#	endif
#	ifdef glMultiTexCoord3sARB
	_glMultiTexCoord3sARB = (glMultiTexCoord3sARBFunc)glGetFunction("glMultiTexCoord3sARB");
#	endif
#	ifdef glMultiTexCoord3svARB
	_glMultiTexCoord3svARB = (glMultiTexCoord3svARBFunc)glGetFunction("glMultiTexCoord3svARB");
#	endif
#	ifdef glMultiTexCoord4dARB
	_glMultiTexCoord4dARB = (glMultiTexCoord4dARBFunc)glGetFunction("glMultiTexCoord4dARB");
#	endif
#	ifdef glMultiTexCoord4dvARB
	_glMultiTexCoord4dvARB = (glMultiTexCoord4dvARBFunc)glGetFunction("glMultiTexCoord4dvARB");
#	endif
#	ifdef glMultiTexCoord4fARB
	_glMultiTexCoord4fARB = (glMultiTexCoord4fARBFunc)glGetFunction("glMultiTexCoord4fARB");
#	endif
#	ifdef glMultiTexCoord4fvARB
	_glMultiTexCoord4fvARB = (glMultiTexCoord4fvARBFunc)glGetFunction("glMultiTexCoord4fvARB");
#	endif
#	ifdef glMultiTexCoord4iARB
	_glMultiTexCoord4iARB = (glMultiTexCoord4iARBFunc)glGetFunction("glMultiTexCoord4iARB");
#	endif
#	ifdef glMultiTexCoord4ivARB
	_glMultiTexCoord4ivARB = (glMultiTexCoord4ivARBFunc)glGetFunction("glMultiTexCoord4ivARB");
#	endif
#	ifdef glMultiTexCoord4sARB
	_glMultiTexCoord4sARB = (glMultiTexCoord4sARBFunc)glGetFunction("glMultiTexCoord4sARB");
#	endif
#	ifdef glMultiTexCoord4svARB
	_glMultiTexCoord4svARB = (glMultiTexCoord4svARBFunc)glGetFunction("glMultiTexCoord4svARB");
#	endif
#	ifdef glLoadTransposeMatrixfARB
	_glLoadTransposeMatrixfARB = (glLoadTransposeMatrixfARBFunc)glGetFunction("glLoadTransposeMatrixfARB");
#	endif
#	ifdef glLoadTransposeMatrixdARB
	_glLoadTransposeMatrixdARB = (glLoadTransposeMatrixdARBFunc)glGetFunction("glLoadTransposeMatrixdARB");
#	endif
#	ifdef glMultTransposeMatrixfARB
	_glMultTransposeMatrixfARB = (glMultTransposeMatrixfARBFunc)glGetFunction("glMultTransposeMatrixfARB");
#	endif
#	ifdef glMultTransposeMatrixdARB
	_glMultTransposeMatrixdARB = (glMultTransposeMatrixdARBFunc)glGetFunction("glMultTransposeMatrixdARB");
#	endif
#	ifdef glSampleCoverageARB
	_glSampleCoverageARB = (glSampleCoverageARBFunc)glGetFunction("glSampleCoverageARB");
#	endif
#	ifdef glCompressedTexImage3DARB
	_glCompressedTexImage3DARB = (glCompressedTexImage3DARBFunc)glGetFunction("glCompressedTexImage3DARB");
#	endif
#	ifdef glCompressedTexImage2DARB
	_glCompressedTexImage2DARB = (glCompressedTexImage2DARBFunc)glGetFunction("glCompressedTexImage2DARB");
#	endif
#	ifdef glCompressedTexImage1DARB
	_glCompressedTexImage1DARB = (glCompressedTexImage1DARBFunc)glGetFunction("glCompressedTexImage1DARB");
#	endif
#	ifdef glCompressedTexSubImage3DARB
	_glCompressedTexSubImage3DARB = (glCompressedTexSubImage3DARBFunc)glGetFunction("glCompressedTexSubImage3DARB");
#	endif
#	ifdef glCompressedTexSubImage2DARB
	_glCompressedTexSubImage2DARB = (glCompressedTexSubImage2DARBFunc)glGetFunction("glCompressedTexSubImage2DARB");
#	endif
#	ifdef glCompressedTexSubImage1DARB
	_glCompressedTexSubImage1DARB = (glCompressedTexSubImage1DARBFunc)glGetFunction("glCompressedTexSubImage1DARB");
#	endif
#	ifdef glGetCompressedTexImageARB
	_glGetCompressedTexImageARB = (glGetCompressedTexImageARBFunc)glGetFunction("glGetCompressedTexImageARB");
#	endif
#	ifdef glPointParameterfARB
	_glPointParameterfARB = (glPointParameterfARBFunc)glGetFunction("glPointParameterfARB");
#	endif
#	ifdef glPointParameterfvARB
	_glPointParameterfvARB = (glPointParameterfvARBFunc)glGetFunction("glPointParameterfvARB");
#	endif
#	ifdef glWeightbvARB
	_glWeightbvARB = (glWeightbvARBFunc)glGetFunction("glWeightbvARB");
#	endif
#	ifdef glWeightsvARB
	_glWeightsvARB = (glWeightsvARBFunc)glGetFunction("glWeightsvARB");
#	endif
#	ifdef glWeightivARB
	_glWeightivARB = (glWeightivARBFunc)glGetFunction("glWeightivARB");
#	endif
#	ifdef glWeightfvARB
	_glWeightfvARB = (glWeightfvARBFunc)glGetFunction("glWeightfvARB");
#	endif
#	ifdef glWeightdvARB
	_glWeightdvARB = (glWeightdvARBFunc)glGetFunction("glWeightdvARB");
#	endif
#	ifdef glWeightubvARB
	_glWeightubvARB = (glWeightubvARBFunc)glGetFunction("glWeightubvARB");
#	endif
#	ifdef glWeightusvARB
	_glWeightusvARB = (glWeightusvARBFunc)glGetFunction("glWeightusvARB");
#	endif
#	ifdef glWeightuivARB
	_glWeightuivARB = (glWeightuivARBFunc)glGetFunction("glWeightuivARB");
#	endif
#	ifdef glWeightPointerARB
	_glWeightPointerARB = (glWeightPointerARBFunc)glGetFunction("glWeightPointerARB");
#	endif
#	ifdef glVertexBlendARB
	_glVertexBlendARB = (glVertexBlendARBFunc)glGetFunction("glVertexBlendARB");
#	endif
#	ifdef glCurrentPaletteMatrixARB
	_glCurrentPaletteMatrixARB = (glCurrentPaletteMatrixARBFunc)glGetFunction("glCurrentPaletteMatrixARB");
#	endif
#	ifdef glMatrixIndexubvARB
	_glMatrixIndexubvARB = (glMatrixIndexubvARBFunc)glGetFunction("glMatrixIndexubvARB");
#	endif
#	ifdef glMatrixIndexusvARB
	_glMatrixIndexusvARB = (glMatrixIndexusvARBFunc)glGetFunction("glMatrixIndexusvARB");
#	endif
#	ifdef glMatrixIndexuivARB
	_glMatrixIndexuivARB = (glMatrixIndexuivARBFunc)glGetFunction("glMatrixIndexuivARB");
#	endif
#	ifdef glMatrixIndexPointerARB
	_glMatrixIndexPointerARB = (glMatrixIndexPointerARBFunc)glGetFunction("glMatrixIndexPointerARB");
#	endif
#	ifdef glWindowPos2dARB
	_glWindowPos2dARB = (glWindowPos2dARBFunc)glGetFunction("glWindowPos2dARB");
#	endif
#	ifdef glWindowPos2dvARB
	_glWindowPos2dvARB = (glWindowPos2dvARBFunc)glGetFunction("glWindowPos2dvARB");
#	endif
#	ifdef glWindowPos2fARB
	_glWindowPos2fARB = (glWindowPos2fARBFunc)glGetFunction("glWindowPos2fARB");
#	endif
#	ifdef glWindowPos2fvARB
	_glWindowPos2fvARB = (glWindowPos2fvARBFunc)glGetFunction("glWindowPos2fvARB");
#	endif
#	ifdef glWindowPos2iARB
	_glWindowPos2iARB = (glWindowPos2iARBFunc)glGetFunction("glWindowPos2iARB");
#	endif
#	ifdef glWindowPos2ivARB
	_glWindowPos2ivARB = (glWindowPos2ivARBFunc)glGetFunction("glWindowPos2ivARB");
#	endif
#	ifdef glWindowPos2sARB
	_glWindowPos2sARB = (glWindowPos2sARBFunc)glGetFunction("glWindowPos2sARB");
#	endif
#	ifdef glWindowPos2svARB
	_glWindowPos2svARB = (glWindowPos2svARBFunc)glGetFunction("glWindowPos2svARB");
#	endif
#	ifdef glWindowPos3dARB
	_glWindowPos3dARB = (glWindowPos3dARBFunc)glGetFunction("glWindowPos3dARB");
#	endif
#	ifdef glWindowPos3dvARB
	_glWindowPos3dvARB = (glWindowPos3dvARBFunc)glGetFunction("glWindowPos3dvARB");
#	endif
#	ifdef glWindowPos3fARB
	_glWindowPos3fARB = (glWindowPos3fARBFunc)glGetFunction("glWindowPos3fARB");
#	endif
#	ifdef glWindowPos3fvARB
	_glWindowPos3fvARB = (glWindowPos3fvARBFunc)glGetFunction("glWindowPos3fvARB");
#	endif
#	ifdef glWindowPos3iARB
	_glWindowPos3iARB = (glWindowPos3iARBFunc)glGetFunction("glWindowPos3iARB");
#	endif
#	ifdef glWindowPos3ivARB
	_glWindowPos3ivARB = (glWindowPos3ivARBFunc)glGetFunction("glWindowPos3ivARB");
#	endif
#	ifdef glWindowPos3sARB
	_glWindowPos3sARB = (glWindowPos3sARBFunc)glGetFunction("glWindowPos3sARB");
#	endif
#	ifdef glWindowPos3svARB
	_glWindowPos3svARB = (glWindowPos3svARBFunc)glGetFunction("glWindowPos3svARB");
#	endif
#	ifdef glVertexAttrib1dARB
	_glVertexAttrib1dARB = (glVertexAttrib1dARBFunc)glGetFunction("glVertexAttrib1dARB");
#	endif
#	ifdef glVertexAttrib1dvARB
	_glVertexAttrib1dvARB = (glVertexAttrib1dvARBFunc)glGetFunction("glVertexAttrib1dvARB");
#	endif
#	ifdef glVertexAttrib1fARB
	_glVertexAttrib1fARB = (glVertexAttrib1fARBFunc)glGetFunction("glVertexAttrib1fARB");
#	endif
#	ifdef glVertexAttrib1fvARB
	_glVertexAttrib1fvARB = (glVertexAttrib1fvARBFunc)glGetFunction("glVertexAttrib1fvARB");
#	endif
#	ifdef glVertexAttrib1sARB
	_glVertexAttrib1sARB = (glVertexAttrib1sARBFunc)glGetFunction("glVertexAttrib1sARB");
#	endif
#	ifdef glVertexAttrib1svARB
	_glVertexAttrib1svARB = (glVertexAttrib1svARBFunc)glGetFunction("glVertexAttrib1svARB");
#	endif
#	ifdef glVertexAttrib2dARB
	_glVertexAttrib2dARB = (glVertexAttrib2dARBFunc)glGetFunction("glVertexAttrib2dARB");
#	endif
#	ifdef glVertexAttrib2dvARB
	_glVertexAttrib2dvARB = (glVertexAttrib2dvARBFunc)glGetFunction("glVertexAttrib2dvARB");
#	endif
#	ifdef glVertexAttrib2fARB
	_glVertexAttrib2fARB = (glVertexAttrib2fARBFunc)glGetFunction("glVertexAttrib2fARB");
#	endif
#	ifdef glVertexAttrib2fvARB
	_glVertexAttrib2fvARB = (glVertexAttrib2fvARBFunc)glGetFunction("glVertexAttrib2fvARB");
#	endif
#	ifdef glVertexAttrib2sARB
	_glVertexAttrib2sARB = (glVertexAttrib2sARBFunc)glGetFunction("glVertexAttrib2sARB");
#	endif
#	ifdef glVertexAttrib2svARB
	_glVertexAttrib2svARB = (glVertexAttrib2svARBFunc)glGetFunction("glVertexAttrib2svARB");
#	endif
#	ifdef glVertexAttrib3dARB
	_glVertexAttrib3dARB = (glVertexAttrib3dARBFunc)glGetFunction("glVertexAttrib3dARB");
#	endif
#	ifdef glVertexAttrib3dvARB
	_glVertexAttrib3dvARB = (glVertexAttrib3dvARBFunc)glGetFunction("glVertexAttrib3dvARB");
#	endif
#	ifdef glVertexAttrib3fARB
	_glVertexAttrib3fARB = (glVertexAttrib3fARBFunc)glGetFunction("glVertexAttrib3fARB");
#	endif
#	ifdef glVertexAttrib3fvARB
	_glVertexAttrib3fvARB = (glVertexAttrib3fvARBFunc)glGetFunction("glVertexAttrib3fvARB");
#	endif
#	ifdef glVertexAttrib3sARB
	_glVertexAttrib3sARB = (glVertexAttrib3sARBFunc)glGetFunction("glVertexAttrib3sARB");
#	endif
#	ifdef glVertexAttrib3svARB
	_glVertexAttrib3svARB = (glVertexAttrib3svARBFunc)glGetFunction("glVertexAttrib3svARB");
#	endif
#	ifdef glVertexAttrib4NbvARB
	_glVertexAttrib4NbvARB = (glVertexAttrib4NbvARBFunc)glGetFunction("glVertexAttrib4NbvARB");
#	endif
#	ifdef glVertexAttrib4NivARB
	_glVertexAttrib4NivARB = (glVertexAttrib4NivARBFunc)glGetFunction("glVertexAttrib4NivARB");
#	endif
#	ifdef glVertexAttrib4NsvARB
	_glVertexAttrib4NsvARB = (glVertexAttrib4NsvARBFunc)glGetFunction("glVertexAttrib4NsvARB");
#	endif
#	ifdef glVertexAttrib4NubARB
	_glVertexAttrib4NubARB = (glVertexAttrib4NubARBFunc)glGetFunction("glVertexAttrib4NubARB");
#	endif
#	ifdef glVertexAttrib4NubvARB
	_glVertexAttrib4NubvARB = (glVertexAttrib4NubvARBFunc)glGetFunction("glVertexAttrib4NubvARB");
#	endif
#	ifdef glVertexAttrib4NuivARB
	_glVertexAttrib4NuivARB = (glVertexAttrib4NuivARBFunc)glGetFunction("glVertexAttrib4NuivARB");
#	endif
#	ifdef glVertexAttrib4NusvARB
	_glVertexAttrib4NusvARB = (glVertexAttrib4NusvARBFunc)glGetFunction("glVertexAttrib4NusvARB");
#	endif
#	ifdef glVertexAttrib4bvARB
	_glVertexAttrib4bvARB = (glVertexAttrib4bvARBFunc)glGetFunction("glVertexAttrib4bvARB");
#	endif
#	ifdef glVertexAttrib4dARB
	_glVertexAttrib4dARB = (glVertexAttrib4dARBFunc)glGetFunction("glVertexAttrib4dARB");
#	endif
#	ifdef glVertexAttrib4dvARB
	_glVertexAttrib4dvARB = (glVertexAttrib4dvARBFunc)glGetFunction("glVertexAttrib4dvARB");
#	endif
#	ifdef glVertexAttrib4fARB
	_glVertexAttrib4fARB = (glVertexAttrib4fARBFunc)glGetFunction("glVertexAttrib4fARB");
#	endif
#	ifdef glVertexAttrib4fvARB
	_glVertexAttrib4fvARB = (glVertexAttrib4fvARBFunc)glGetFunction("glVertexAttrib4fvARB");
#	endif
#	ifdef glVertexAttrib4ivARB
	_glVertexAttrib4ivARB = (glVertexAttrib4ivARBFunc)glGetFunction("glVertexAttrib4ivARB");
#	endif
#	ifdef glVertexAttrib4sARB
	_glVertexAttrib4sARB = (glVertexAttrib4sARBFunc)glGetFunction("glVertexAttrib4sARB");
#	endif
#	ifdef glVertexAttrib4svARB
	_glVertexAttrib4svARB = (glVertexAttrib4svARBFunc)glGetFunction("glVertexAttrib4svARB");
#	endif
#	ifdef glVertexAttrib4ubvARB
	_glVertexAttrib4ubvARB = (glVertexAttrib4ubvARBFunc)glGetFunction("glVertexAttrib4ubvARB");
#	endif
#	ifdef glVertexAttrib4uivARB
	_glVertexAttrib4uivARB = (glVertexAttrib4uivARBFunc)glGetFunction("glVertexAttrib4uivARB");
#	endif
#	ifdef glVertexAttrib4usvARB
	_glVertexAttrib4usvARB = (glVertexAttrib4usvARBFunc)glGetFunction("glVertexAttrib4usvARB");
#	endif
#	ifdef glVertexAttribPointerARB
	_glVertexAttribPointerARB = (glVertexAttribPointerARBFunc)glGetFunction("glVertexAttribPointerARB");
#	endif
#	ifdef glEnableVertexAttribArrayARB
	_glEnableVertexAttribArrayARB = (glEnableVertexAttribArrayARBFunc)glGetFunction("glEnableVertexAttribArrayARB");
#	endif
#	ifdef glDisableVertexAttribArrayARB
	_glDisableVertexAttribArrayARB = (glDisableVertexAttribArrayARBFunc)glGetFunction("glDisableVertexAttribArrayARB");
#	endif
#	ifdef glProgramStringARB
	_glProgramStringARB = (glProgramStringARBFunc)glGetFunction("glProgramStringARB");
#	endif
#	ifdef glBindProgramARB
	_glBindProgramARB = (glBindProgramARBFunc)glGetFunction("glBindProgramARB");
#	endif
#	ifdef glDeleteProgramsARB
	_glDeleteProgramsARB = (glDeleteProgramsARBFunc)glGetFunction("glDeleteProgramsARB");
#	endif
#	ifdef glGenProgramsARB
	_glGenProgramsARB = (glGenProgramsARBFunc)glGetFunction("glGenProgramsARB");
#	endif
#	ifdef glProgramEnvParameter4dARB
	_glProgramEnvParameter4dARB = (glProgramEnvParameter4dARBFunc)glGetFunction("glProgramEnvParameter4dARB");
#	endif
#	ifdef glProgramEnvParameter4dvARB
	_glProgramEnvParameter4dvARB = (glProgramEnvParameter4dvARBFunc)glGetFunction("glProgramEnvParameter4dvARB");
#	endif
#	ifdef glProgramEnvParameter4fARB
	_glProgramEnvParameter4fARB = (glProgramEnvParameter4fARBFunc)glGetFunction("glProgramEnvParameter4fARB");
#	endif
#	ifdef glProgramEnvParameter4fvARB
	_glProgramEnvParameter4fvARB = (glProgramEnvParameter4fvARBFunc)glGetFunction("glProgramEnvParameter4fvARB");
#	endif
#	ifdef glProgramLocalParameter4dARB
	_glProgramLocalParameter4dARB = (glProgramLocalParameter4dARBFunc)glGetFunction("glProgramLocalParameter4dARB");
#	endif
#	ifdef glProgramLocalParameter4dvARB
	_glProgramLocalParameter4dvARB = (glProgramLocalParameter4dvARBFunc)glGetFunction("glProgramLocalParameter4dvARB");
#	endif
#	ifdef glProgramLocalParameter4fARB
	_glProgramLocalParameter4fARB = (glProgramLocalParameter4fARBFunc)glGetFunction("glProgramLocalParameter4fARB");
#	endif
#	ifdef glProgramLocalParameter4fvARB
	_glProgramLocalParameter4fvARB = (glProgramLocalParameter4fvARBFunc)glGetFunction("glProgramLocalParameter4fvARB");
#	endif
#	ifdef glGetProgramEnvParameterdvARB
	_glGetProgramEnvParameterdvARB = (glGetProgramEnvParameterdvARBFunc)glGetFunction("glGetProgramEnvParameterdvARB");
#	endif
#	ifdef glGetProgramEnvParameterfvARB
	_glGetProgramEnvParameterfvARB = (glGetProgramEnvParameterfvARBFunc)glGetFunction("glGetProgramEnvParameterfvARB");
#	endif
#	ifdef glGetProgramLocalParameterdvARB
	_glGetProgramLocalParameterdvARB = (glGetProgramLocalParameterdvARBFunc)glGetFunction("glGetProgramLocalParameterdvARB");
#	endif
#	ifdef glGetProgramLocalParameterfvARB
	_glGetProgramLocalParameterfvARB = (glGetProgramLocalParameterfvARBFunc)glGetFunction("glGetProgramLocalParameterfvARB");
#	endif
#	ifdef glGetProgramivARB
	_glGetProgramivARB = (glGetProgramivARBFunc)glGetFunction("glGetProgramivARB");
#	endif
#	ifdef glGetProgramStringARB
	_glGetProgramStringARB = (glGetProgramStringARBFunc)glGetFunction("glGetProgramStringARB");
#	endif
#	ifdef glGetVertexAttribdvARB
	_glGetVertexAttribdvARB = (glGetVertexAttribdvARBFunc)glGetFunction("glGetVertexAttribdvARB");
#	endif
#	ifdef glGetVertexAttribfvARB
	_glGetVertexAttribfvARB = (glGetVertexAttribfvARBFunc)glGetFunction("glGetVertexAttribfvARB");
#	endif
#	ifdef glGetVertexAttribivARB
	_glGetVertexAttribivARB = (glGetVertexAttribivARBFunc)glGetFunction("glGetVertexAttribivARB");
#	endif
#	ifdef glGetVertexAttribPointervARB
	_glGetVertexAttribPointervARB = (glGetVertexAttribPointervARBFunc)glGetFunction("glGetVertexAttribPointervARB");
#	endif
#	ifdef glIsProgramARB
	_glIsProgramARB = (glIsProgramARBFunc)glGetFunction("glIsProgramARB");
#	endif
#	ifdef glBindBufferARB
	_glBindBufferARB = (glBindBufferARBFunc)glGetFunction("glBindBufferARB");
#	endif
#	ifdef glDeleteBuffersARB
	_glDeleteBuffersARB = (glDeleteBuffersARBFunc)glGetFunction("glDeleteBuffersARB");
#	endif
#	ifdef glGenBuffersARB
	_glGenBuffersARB = (glGenBuffersARBFunc)glGetFunction("glGenBuffersARB");
#	endif
#	ifdef glIsBufferARB
	_glIsBufferARB = (glIsBufferARBFunc)glGetFunction("glIsBufferARB");
#	endif
#	ifdef glBufferDataARB
	_glBufferDataARB = (glBufferDataARBFunc)glGetFunction("glBufferDataARB");
#	endif
#	ifdef glBufferSubDataARB
	_glBufferSubDataARB = (glBufferSubDataARBFunc)glGetFunction("glBufferSubDataARB");
#	endif
#	ifdef glGetBufferSubDataARB
	_glGetBufferSubDataARB = (glGetBufferSubDataARBFunc)glGetFunction("glGetBufferSubDataARB");
#	endif
#	ifdef glMapBufferARB
	_glMapBufferARB = (glMapBufferARBFunc)glGetFunction("glMapBufferARB");
#	endif
#	ifdef glUnmapBufferARB
	_glUnmapBufferARB = (glUnmapBufferARBFunc)glGetFunction("glUnmapBufferARB");
#	endif
#	ifdef glGetBufferParameterivARB
	_glGetBufferParameterivARB = (glGetBufferParameterivARBFunc)glGetFunction("glGetBufferParameterivARB");
#	endif
#	ifdef glGetBufferPointervARB
	_glGetBufferPointervARB = (glGetBufferPointervARBFunc)glGetFunction("glGetBufferPointervARB");
#	endif
#	ifdef glGenQueriesARB
	_glGenQueriesARB = (glGenQueriesARBFunc)glGetFunction("glGenQueriesARB");
#	endif
#	ifdef glDeleteQueriesARB
	_glDeleteQueriesARB = (glDeleteQueriesARBFunc)glGetFunction("glDeleteQueriesARB");
#	endif
#	ifdef glIsQueryARB
	_glIsQueryARB = (glIsQueryARBFunc)glGetFunction("glIsQueryARB");
#	endif
#	ifdef glBeginQueryARB
	_glBeginQueryARB = (glBeginQueryARBFunc)glGetFunction("glBeginQueryARB");
#	endif
#	ifdef glEndQueryARB
	_glEndQueryARB = (glEndQueryARBFunc)glGetFunction("glEndQueryARB");
#	endif
#	ifdef glGetQueryivARB
	_glGetQueryivARB = (glGetQueryivARBFunc)glGetFunction("glGetQueryivARB");
#	endif
#	ifdef glGetQueryObjectivARB
	_glGetQueryObjectivARB = (glGetQueryObjectivARBFunc)glGetFunction("glGetQueryObjectivARB");
#	endif
#	ifdef glGetQueryObjectuivARB
	_glGetQueryObjectuivARB = (glGetQueryObjectuivARBFunc)glGetFunction("glGetQueryObjectuivARB");
#	endif
#	ifdef glDeleteObjectARB
	_glDeleteObjectARB = (glDeleteObjectARBFunc)glGetFunction("glDeleteObjectARB");
#	endif
#	ifdef glGetHandleARB
	_glGetHandleARB = (glGetHandleARBFunc)glGetFunction("glGetHandleARB");
#	endif
#	ifdef glDetachObjectARB
	_glDetachObjectARB = (glDetachObjectARBFunc)glGetFunction("glDetachObjectARB");
#	endif
#	ifdef glCreateShaderObjectARB
	_glCreateShaderObjectARB = (glCreateShaderObjectARBFunc)glGetFunction("glCreateShaderObjectARB");
#	endif
#	ifdef glShaderSourceARB
	_glShaderSourceARB = (glShaderSourceARBFunc)glGetFunction("glShaderSourceARB");
#	endif
#	ifdef glCompileShaderARB
	_glCompileShaderARB = (glCompileShaderARBFunc)glGetFunction("glCompileShaderARB");
#	endif
#	ifdef glCreateProgramObjectARB
	_glCreateProgramObjectARB = (glCreateProgramObjectARBFunc)glGetFunction("glCreateProgramObjectARB");
#	endif
#	ifdef glAttachObjectARB
	_glAttachObjectARB = (glAttachObjectARBFunc)glGetFunction("glAttachObjectARB");
#	endif
#	ifdef glLinkProgramARB
	_glLinkProgramARB = (glLinkProgramARBFunc)glGetFunction("glLinkProgramARB");
#	endif
#	ifdef glUseProgramObjectARB
	_glUseProgramObjectARB = (glUseProgramObjectARBFunc)glGetFunction("glUseProgramObjectARB");
#	endif
#	ifdef glValidateProgramARB
	_glValidateProgramARB = (glValidateProgramARBFunc)glGetFunction("glValidateProgramARB");
#	endif
#	ifdef glUniform1fARB
	_glUniform1fARB = (glUniform1fARBFunc)glGetFunction("glUniform1fARB");
#	endif
#	ifdef glUniform2fARB
	_glUniform2fARB = (glUniform2fARBFunc)glGetFunction("glUniform2fARB");
#	endif
#	ifdef glUniform3fARB
	_glUniform3fARB = (glUniform3fARBFunc)glGetFunction("glUniform3fARB");
#	endif
#	ifdef glUniform4fARB
	_glUniform4fARB = (glUniform4fARBFunc)glGetFunction("glUniform4fARB");
#	endif
#	ifdef glUniform1iARB
	_glUniform1iARB = (glUniform1iARBFunc)glGetFunction("glUniform1iARB");
#	endif
#	ifdef glUniform2iARB
	_glUniform2iARB = (glUniform2iARBFunc)glGetFunction("glUniform2iARB");
#	endif
#	ifdef glUniform3iARB
	_glUniform3iARB = (glUniform3iARBFunc)glGetFunction("glUniform3iARB");
#	endif
#	ifdef glUniform4iARB
	_glUniform4iARB = (glUniform4iARBFunc)glGetFunction("glUniform4iARB");
#	endif
#	ifdef glUniform1fvARB
	_glUniform1fvARB = (glUniform1fvARBFunc)glGetFunction("glUniform1fvARB");
#	endif
#	ifdef glUniform2fvARB
	_glUniform2fvARB = (glUniform2fvARBFunc)glGetFunction("glUniform2fvARB");
#	endif
#	ifdef glUniform3fvARB
	_glUniform3fvARB = (glUniform3fvARBFunc)glGetFunction("glUniform3fvARB");
#	endif
#	ifdef glUniform4fvARB
	_glUniform4fvARB = (glUniform4fvARBFunc)glGetFunction("glUniform4fvARB");
#	endif
#	ifdef glUniform1ivARB
	_glUniform1ivARB = (glUniform1ivARBFunc)glGetFunction("glUniform1ivARB");
#	endif
#	ifdef glUniform2ivARB
	_glUniform2ivARB = (glUniform2ivARBFunc)glGetFunction("glUniform2ivARB");
#	endif
#	ifdef glUniform3ivARB
	_glUniform3ivARB = (glUniform3ivARBFunc)glGetFunction("glUniform3ivARB");
#	endif
#	ifdef glUniform4ivARB
	_glUniform4ivARB = (glUniform4ivARBFunc)glGetFunction("glUniform4ivARB");
#	endif
#	ifdef glUniformMatrix2fvARB
	_glUniformMatrix2fvARB = (glUniformMatrix2fvARBFunc)glGetFunction("glUniformMatrix2fvARB");
#	endif
#	ifdef glUniformMatrix3fvARB
	_glUniformMatrix3fvARB = (glUniformMatrix3fvARBFunc)glGetFunction("glUniformMatrix3fvARB");
#	endif
#	ifdef glUniformMatrix4fvARB
	_glUniformMatrix4fvARB = (glUniformMatrix4fvARBFunc)glGetFunction("glUniformMatrix4fvARB");
#	endif
#	ifdef glGetObjectParameterfvARB
	_glGetObjectParameterfvARB = (glGetObjectParameterfvARBFunc)glGetFunction("glGetObjectParameterfvARB");
#	endif
#	ifdef glGetObjectParameterivARB
	_glGetObjectParameterivARB = (glGetObjectParameterivARBFunc)glGetFunction("glGetObjectParameterivARB");
#	endif
#	ifdef glGetInfoLogARB
	_glGetInfoLogARB = (glGetInfoLogARBFunc)glGetFunction("glGetInfoLogARB");
#	endif
#	ifdef glGetAttachedObjectsARB
	_glGetAttachedObjectsARB = (glGetAttachedObjectsARBFunc)glGetFunction("glGetAttachedObjectsARB");
#	endif
#	ifdef glGetUniformLocationARB
	_glGetUniformLocationARB = (glGetUniformLocationARBFunc)glGetFunction("glGetUniformLocationARB");
#	endif
#	ifdef glGetActiveUniformARB
	_glGetActiveUniformARB = (glGetActiveUniformARBFunc)glGetFunction("glGetActiveUniformARB");
#	endif
#	ifdef glGetUniformfvARB
	_glGetUniformfvARB = (glGetUniformfvARBFunc)glGetFunction("glGetUniformfvARB");
#	endif
#	ifdef glGetUniformivARB
	_glGetUniformivARB = (glGetUniformivARBFunc)glGetFunction("glGetUniformivARB");
#	endif
#	ifdef glGetShaderSourceARB
	_glGetShaderSourceARB = (glGetShaderSourceARBFunc)glGetFunction("glGetShaderSourceARB");
#	endif
#	ifdef glBindAttribLocationARB
	_glBindAttribLocationARB = (glBindAttribLocationARBFunc)glGetFunction("glBindAttribLocationARB");
#	endif
#	ifdef glGetActiveAttribARB
	_glGetActiveAttribARB = (glGetActiveAttribARBFunc)glGetFunction("glGetActiveAttribARB");
#	endif
#	ifdef glGetAttribLocationARB
	_glGetAttribLocationARB = (glGetAttribLocationARBFunc)glGetFunction("glGetAttribLocationARB");
#	endif
#	ifdef glDrawBuffersARB
	_glDrawBuffersARB = (glDrawBuffersARBFunc)glGetFunction("glDrawBuffersARB");
#	endif
#	ifdef glClampColorARB
	_glClampColorARB = (glClampColorARBFunc)glGetFunction("glClampColorARB");
#	endif
#	ifdef glDrawArraysInstancedARB
	_glDrawArraysInstancedARB = (glDrawArraysInstancedARBFunc)glGetFunction("glDrawArraysInstancedARB");
#	endif
#	ifdef glDrawElementsInstancedARB
	_glDrawElementsInstancedARB = (glDrawElementsInstancedARBFunc)glGetFunction("glDrawElementsInstancedARB");
#	endif
#	ifdef glIsRenderbuffer
	_glIsRenderbuffer = (glIsRenderbufferFunc)glGetFunction("glIsRenderbuffer");
#	endif
#	ifdef glBindRenderbuffer
	_glBindRenderbuffer = (glBindRenderbufferFunc)glGetFunction("glBindRenderbuffer");
#	endif
#	ifdef glDeleteRenderbuffers
	_glDeleteRenderbuffers = (glDeleteRenderbuffersFunc)glGetFunction("glDeleteRenderbuffers");
#	endif
#	ifdef glGenRenderbuffers
	_glGenRenderbuffers = (glGenRenderbuffersFunc)glGetFunction("glGenRenderbuffers");
#	endif
#	ifdef glRenderbufferStorage
	_glRenderbufferStorage = (glRenderbufferStorageFunc)glGetFunction("glRenderbufferStorage");
#	endif
#	ifdef glGetRenderbufferParameteriv
	_glGetRenderbufferParameteriv = (glGetRenderbufferParameterivFunc)glGetFunction("glGetRenderbufferParameteriv");
#	endif
#	ifdef glIsFramebuffer
	_glIsFramebuffer = (glIsFramebufferFunc)glGetFunction("glIsFramebuffer");
#	endif
#	ifdef glBindFramebuffer
	_glBindFramebuffer = (glBindFramebufferFunc)glGetFunction("glBindFramebuffer");
#	endif
#	ifdef glDeleteFramebuffers
	_glDeleteFramebuffers = (glDeleteFramebuffersFunc)glGetFunction("glDeleteFramebuffers");
#	endif
#	ifdef glGenFramebuffers
	_glGenFramebuffers = (glGenFramebuffersFunc)glGetFunction("glGenFramebuffers");
#	endif
#	ifdef glCheckFramebufferStatus
	_glCheckFramebufferStatus = (glCheckFramebufferStatusFunc)glGetFunction("glCheckFramebufferStatus");
#	endif
#	ifdef glFramebufferTexture1D
	_glFramebufferTexture1D = (glFramebufferTexture1DFunc)glGetFunction("glFramebufferTexture1D");
#	endif
#	ifdef glFramebufferTexture2D
	_glFramebufferTexture2D = (glFramebufferTexture2DFunc)glGetFunction("glFramebufferTexture2D");
#	endif
#	ifdef glFramebufferTexture3D
	_glFramebufferTexture3D = (glFramebufferTexture3DFunc)glGetFunction("glFramebufferTexture3D");
#	endif
#	ifdef glFramebufferRenderbuffer
	_glFramebufferRenderbuffer = (glFramebufferRenderbufferFunc)glGetFunction("glFramebufferRenderbuffer");
#	endif
#	ifdef glGetFramebufferAttachmentParameteriv
	_glGetFramebufferAttachmentParameteriv = (glGetFramebufferAttachmentParameterivFunc)glGetFunction("glGetFramebufferAttachmentParameteriv");
#	endif
#	ifdef glGenerateMipmap
	_glGenerateMipmap = (glGenerateMipmapFunc)glGetFunction("glGenerateMipmap");
#	endif
#	ifdef glBlitFramebuffer
	_glBlitFramebuffer = (glBlitFramebufferFunc)glGetFunction("glBlitFramebuffer");
#	endif
#	ifdef glRenderbufferStorageMultisample
	_glRenderbufferStorageMultisample = (glRenderbufferStorageMultisampleFunc)glGetFunction("glRenderbufferStorageMultisample");
#	endif
#	ifdef glFramebufferTextureLayer
	_glFramebufferTextureLayer = (glFramebufferTextureLayerFunc)glGetFunction("glFramebufferTextureLayer");
#	endif
#	ifdef glProgramParameteriARB
	_glProgramParameteriARB = (glProgramParameteriARBFunc)glGetFunction("glProgramParameteriARB");
#	endif
#	ifdef glFramebufferTextureARB
	_glFramebufferTextureARB = (glFramebufferTextureARBFunc)glGetFunction("glFramebufferTextureARB");
#	endif
#	ifdef glFramebufferTextureLayerARB
	_glFramebufferTextureLayerARB = (glFramebufferTextureLayerARBFunc)glGetFunction("glFramebufferTextureLayerARB");
#	endif
#	ifdef glFramebufferTextureFaceARB
	_glFramebufferTextureFaceARB = (glFramebufferTextureFaceARBFunc)glGetFunction("glFramebufferTextureFaceARB");
#	endif
#	ifdef glVertexAttribDivisorARB
	_glVertexAttribDivisorARB = (glVertexAttribDivisorARBFunc)glGetFunction("glVertexAttribDivisorARB");
#	endif
#	ifdef glMapBufferRange
	_glMapBufferRange = (glMapBufferRangeFunc)glGetFunction("glMapBufferRange");
#	endif
#	ifdef glFlushMappedBufferRange
	_glFlushMappedBufferRange = (glFlushMappedBufferRangeFunc)glGetFunction("glFlushMappedBufferRange");
#	endif
#	ifdef glTexBufferARB
	_glTexBufferARB = (glTexBufferARBFunc)glGetFunction("glTexBufferARB");
#	endif
#	ifdef glBindVertexArray
	_glBindVertexArray = (glBindVertexArrayFunc)glGetFunction("glBindVertexArray");
#	endif
#	ifdef glDeleteVertexArrays
	_glDeleteVertexArrays = (glDeleteVertexArraysFunc)glGetFunction("glDeleteVertexArrays");
#	endif
#	ifdef glGenVertexArrays
	_glGenVertexArrays = (glGenVertexArraysFunc)glGetFunction("glGenVertexArrays");
#	endif
#	ifdef glIsVertexArray
	_glIsVertexArray = (glIsVertexArrayFunc)glGetFunction("glIsVertexArray");
#	endif
#	ifdef glGetUniformIndices
	_glGetUniformIndices = (glGetUniformIndicesFunc)glGetFunction("glGetUniformIndices");
#	endif
#	ifdef glGetActiveUniformsiv
	_glGetActiveUniformsiv = (glGetActiveUniformsivFunc)glGetFunction("glGetActiveUniformsiv");
#	endif
#	ifdef glGetActiveUniformName
	_glGetActiveUniformName = (glGetActiveUniformNameFunc)glGetFunction("glGetActiveUniformName");
#	endif
#	ifdef glGetUniformBlockIndex
	_glGetUniformBlockIndex = (glGetUniformBlockIndexFunc)glGetFunction("glGetUniformBlockIndex");
#	endif
#	ifdef glGetActiveUniformBlockiv
	_glGetActiveUniformBlockiv = (glGetActiveUniformBlockivFunc)glGetFunction("glGetActiveUniformBlockiv");
#	endif
#	ifdef glGetActiveUniformBlockName
	_glGetActiveUniformBlockName = (glGetActiveUniformBlockNameFunc)glGetFunction("glGetActiveUniformBlockName");
#	endif
#	ifdef glUniformBlockBinding
	_glUniformBlockBinding = (glUniformBlockBindingFunc)glGetFunction("glUniformBlockBinding");
#	endif
#	ifdef glCopyBufferSubData
	_glCopyBufferSubData = (glCopyBufferSubDataFunc)glGetFunction("glCopyBufferSubData");
#	endif
#	ifdef glDrawElementsBaseVertex
	_glDrawElementsBaseVertex = (glDrawElementsBaseVertexFunc)glGetFunction("glDrawElementsBaseVertex");
#	endif
#	ifdef glDrawRangeElementsBaseVertex
	_glDrawRangeElementsBaseVertex = (glDrawRangeElementsBaseVertexFunc)glGetFunction("glDrawRangeElementsBaseVertex");
#	endif
#	ifdef glDrawElementsInstancedBaseVertex
	_glDrawElementsInstancedBaseVertex = (glDrawElementsInstancedBaseVertexFunc)glGetFunction("glDrawElementsInstancedBaseVertex");
#	endif
#	ifdef glMultiDrawElementsBaseVertex
	_glMultiDrawElementsBaseVertex = (glMultiDrawElementsBaseVertexFunc)glGetFunction("glMultiDrawElementsBaseVertex");
#	endif
#	ifdef glProvokingVertex
	_glProvokingVertex = (glProvokingVertexFunc)glGetFunction("glProvokingVertex");
#	endif
#	ifdef glFenceSync
	_glFenceSync = (glFenceSyncFunc)glGetFunction("glFenceSync");
#	endif
#	ifdef glIsSync
	_glIsSync = (glIsSyncFunc)glGetFunction("glIsSync");
#	endif
#	ifdef glDeleteSync
	_glDeleteSync = (glDeleteSyncFunc)glGetFunction("glDeleteSync");
#	endif
#	ifdef glClientWaitSync
	_glClientWaitSync = (glClientWaitSyncFunc)glGetFunction("glClientWaitSync");
#	endif
#	ifdef glWaitSync
	_glWaitSync = (glWaitSyncFunc)glGetFunction("glWaitSync");
#	endif
#	ifdef glGetInteger64v
	_glGetInteger64v = (glGetInteger64vFunc)glGetFunction("glGetInteger64v");
#	endif
#	ifdef glGetSynciv
	_glGetSynciv = (glGetSyncivFunc)glGetFunction("glGetSynciv");
#	endif
#	ifdef glTexImage2DMultisample
	_glTexImage2DMultisample = (glTexImage2DMultisampleFunc)glGetFunction("glTexImage2DMultisample");
#	endif
#	ifdef glTexImage3DMultisample
	_glTexImage3DMultisample = (glTexImage3DMultisampleFunc)glGetFunction("glTexImage3DMultisample");
#	endif
#	ifdef glGetMultisamplefv
	_glGetMultisamplefv = (glGetMultisamplefvFunc)glGetFunction("glGetMultisamplefv");
#	endif
#	ifdef glSampleMaski
	_glSampleMaski = (glSampleMaskiFunc)glGetFunction("glSampleMaski");
#	endif
#	ifdef glBlendEquationiARB
	_glBlendEquationiARB = (glBlendEquationiARBFunc)glGetFunction("glBlendEquationiARB");
#	endif
#	ifdef glBlendEquationSeparateiARB
	_glBlendEquationSeparateiARB = (glBlendEquationSeparateiARBFunc)glGetFunction("glBlendEquationSeparateiARB");
#	endif
#	ifdef glBlendFunciARB
	_glBlendFunciARB = (glBlendFunciARBFunc)glGetFunction("glBlendFunciARB");
#	endif
#	ifdef glBlendFuncSeparateiARB
	_glBlendFuncSeparateiARB = (glBlendFuncSeparateiARBFunc)glGetFunction("glBlendFuncSeparateiARB");
#	endif
#	ifdef glMinSampleShadingARB
	_glMinSampleShadingARB = (glMinSampleShadingARBFunc)glGetFunction("glMinSampleShadingARB");
#	endif
#	ifdef glNamedStringARB
	_glNamedStringARB = (glNamedStringARBFunc)glGetFunction("glNamedStringARB");
#	endif
#	ifdef glDeleteNamedStringARB
	_glDeleteNamedStringARB = (glDeleteNamedStringARBFunc)glGetFunction("glDeleteNamedStringARB");
#	endif
#	ifdef glCompileShaderIncludeARB
	_glCompileShaderIncludeARB = (glCompileShaderIncludeARBFunc)glGetFunction("glCompileShaderIncludeARB");
#	endif
#	ifdef glIsNamedStringARB
	_glIsNamedStringARB = (glIsNamedStringARBFunc)glGetFunction("glIsNamedStringARB");
#	endif
#	ifdef glGetNamedStringARB
	_glGetNamedStringARB = (glGetNamedStringARBFunc)glGetFunction("glGetNamedStringARB");
#	endif
#	ifdef glGetNamedStringivARB
	_glGetNamedStringivARB = (glGetNamedStringivARBFunc)glGetFunction("glGetNamedStringivARB");
#	endif
#	ifdef glBindFragDataLocationIndexed
	_glBindFragDataLocationIndexed = (glBindFragDataLocationIndexedFunc)glGetFunction("glBindFragDataLocationIndexed");
#	endif
#	ifdef glGetFragDataIndex
	_glGetFragDataIndex = (glGetFragDataIndexFunc)glGetFunction("glGetFragDataIndex");
#	endif
#	ifdef glGenSamplers
	_glGenSamplers = (glGenSamplersFunc)glGetFunction("glGenSamplers");
#	endif
#	ifdef glDeleteSamplers
	_glDeleteSamplers = (glDeleteSamplersFunc)glGetFunction("glDeleteSamplers");
#	endif
#	ifdef glIsSampler
	_glIsSampler = (glIsSamplerFunc)glGetFunction("glIsSampler");
#	endif
#	ifdef glBindSampler
	_glBindSampler = (glBindSamplerFunc)glGetFunction("glBindSampler");
#	endif
#	ifdef glSamplerParameteri
	_glSamplerParameteri = (glSamplerParameteriFunc)glGetFunction("glSamplerParameteri");
#	endif
#	ifdef glSamplerParameteriv
	_glSamplerParameteriv = (glSamplerParameterivFunc)glGetFunction("glSamplerParameteriv");
#	endif
#	ifdef glSamplerParameterf
	_glSamplerParameterf = (glSamplerParameterfFunc)glGetFunction("glSamplerParameterf");
#	endif
#	ifdef glSamplerParameterfv
	_glSamplerParameterfv = (glSamplerParameterfvFunc)glGetFunction("glSamplerParameterfv");
#	endif
#	ifdef glSamplerParameterIiv
	_glSamplerParameterIiv = (glSamplerParameterIivFunc)glGetFunction("glSamplerParameterIiv");
#	endif
#	ifdef glSamplerParameterIuiv
	_glSamplerParameterIuiv = (glSamplerParameterIuivFunc)glGetFunction("glSamplerParameterIuiv");
#	endif
#	ifdef glGetSamplerParameteriv
	_glGetSamplerParameteriv = (glGetSamplerParameterivFunc)glGetFunction("glGetSamplerParameteriv");
#	endif
#	ifdef glGetSamplerParameterIiv
	_glGetSamplerParameterIiv = (glGetSamplerParameterIivFunc)glGetFunction("glGetSamplerParameterIiv");
#	endif
#	ifdef glGetSamplerParameterfv
	_glGetSamplerParameterfv = (glGetSamplerParameterfvFunc)glGetFunction("glGetSamplerParameterfv");
#	endif
#	ifdef glGetSamplerParameterIuiv
	_glGetSamplerParameterIuiv = (glGetSamplerParameterIuivFunc)glGetFunction("glGetSamplerParameterIuiv");
#	endif
#	ifdef glQueryCounter
	_glQueryCounter = (glQueryCounterFunc)glGetFunction("glQueryCounter");
#	endif
#	ifdef glGetQueryObjecti64v
	_glGetQueryObjecti64v = (glGetQueryObjecti64vFunc)glGetFunction("glGetQueryObjecti64v");
#	endif
#	ifdef glGetQueryObjectui64v
	_glGetQueryObjectui64v = (glGetQueryObjectui64vFunc)glGetFunction("glGetQueryObjectui64v");
#	endif
#	ifdef glVertexP2ui
	_glVertexP2ui = (glVertexP2uiFunc)glGetFunction("glVertexP2ui");
#	endif
#	ifdef glVertexP2uiv
	_glVertexP2uiv = (glVertexP2uivFunc)glGetFunction("glVertexP2uiv");
#	endif
#	ifdef glVertexP3ui
	_glVertexP3ui = (glVertexP3uiFunc)glGetFunction("glVertexP3ui");
#	endif
#	ifdef glVertexP3uiv
	_glVertexP3uiv = (glVertexP3uivFunc)glGetFunction("glVertexP3uiv");
#	endif
#	ifdef glVertexP4ui
	_glVertexP4ui = (glVertexP4uiFunc)glGetFunction("glVertexP4ui");
#	endif
#	ifdef glVertexP4uiv
	_glVertexP4uiv = (glVertexP4uivFunc)glGetFunction("glVertexP4uiv");
#	endif
#	ifdef glTexCoordP1ui
	_glTexCoordP1ui = (glTexCoordP1uiFunc)glGetFunction("glTexCoordP1ui");
#	endif
#	ifdef glTexCoordP1uiv
	_glTexCoordP1uiv = (glTexCoordP1uivFunc)glGetFunction("glTexCoordP1uiv");
#	endif
#	ifdef glTexCoordP2ui
	_glTexCoordP2ui = (glTexCoordP2uiFunc)glGetFunction("glTexCoordP2ui");
#	endif
#	ifdef glTexCoordP2uiv
	_glTexCoordP2uiv = (glTexCoordP2uivFunc)glGetFunction("glTexCoordP2uiv");
#	endif
#	ifdef glTexCoordP3ui
	_glTexCoordP3ui = (glTexCoordP3uiFunc)glGetFunction("glTexCoordP3ui");
#	endif
#	ifdef glTexCoordP3uiv
	_glTexCoordP3uiv = (glTexCoordP3uivFunc)glGetFunction("glTexCoordP3uiv");
#	endif
#	ifdef glTexCoordP4ui
	_glTexCoordP4ui = (glTexCoordP4uiFunc)glGetFunction("glTexCoordP4ui");
#	endif
#	ifdef glTexCoordP4uiv
	_glTexCoordP4uiv = (glTexCoordP4uivFunc)glGetFunction("glTexCoordP4uiv");
#	endif
#	ifdef glMultiTexCoordP1ui
	_glMultiTexCoordP1ui = (glMultiTexCoordP1uiFunc)glGetFunction("glMultiTexCoordP1ui");
#	endif
#	ifdef glMultiTexCoordP1uiv
	_glMultiTexCoordP1uiv = (glMultiTexCoordP1uivFunc)glGetFunction("glMultiTexCoordP1uiv");
#	endif
#	ifdef glMultiTexCoordP2ui
	_glMultiTexCoordP2ui = (glMultiTexCoordP2uiFunc)glGetFunction("glMultiTexCoordP2ui");
#	endif
#	ifdef glMultiTexCoordP2uiv
	_glMultiTexCoordP2uiv = (glMultiTexCoordP2uivFunc)glGetFunction("glMultiTexCoordP2uiv");
#	endif
#	ifdef glMultiTexCoordP3ui
	_glMultiTexCoordP3ui = (glMultiTexCoordP3uiFunc)glGetFunction("glMultiTexCoordP3ui");
#	endif
#	ifdef glMultiTexCoordP3uiv
	_glMultiTexCoordP3uiv = (glMultiTexCoordP3uivFunc)glGetFunction("glMultiTexCoordP3uiv");
#	endif
#	ifdef glMultiTexCoordP4ui
	_glMultiTexCoordP4ui = (glMultiTexCoordP4uiFunc)glGetFunction("glMultiTexCoordP4ui");
#	endif
#	ifdef glMultiTexCoordP4uiv
	_glMultiTexCoordP4uiv = (glMultiTexCoordP4uivFunc)glGetFunction("glMultiTexCoordP4uiv");
#	endif
#	ifdef glNormalP3ui
	_glNormalP3ui = (glNormalP3uiFunc)glGetFunction("glNormalP3ui");
#	endif
#	ifdef glNormalP3uiv
	_glNormalP3uiv = (glNormalP3uivFunc)glGetFunction("glNormalP3uiv");
#	endif
#	ifdef glColorP3ui
	_glColorP3ui = (glColorP3uiFunc)glGetFunction("glColorP3ui");
#	endif
#	ifdef glColorP3uiv
	_glColorP3uiv = (glColorP3uivFunc)glGetFunction("glColorP3uiv");
#	endif
#	ifdef glColorP4ui
	_glColorP4ui = (glColorP4uiFunc)glGetFunction("glColorP4ui");
#	endif
#	ifdef glColorP4uiv
	_glColorP4uiv = (glColorP4uivFunc)glGetFunction("glColorP4uiv");
#	endif
#	ifdef glSecondaryColorP3ui
	_glSecondaryColorP3ui = (glSecondaryColorP3uiFunc)glGetFunction("glSecondaryColorP3ui");
#	endif
#	ifdef glSecondaryColorP3uiv
	_glSecondaryColorP3uiv = (glSecondaryColorP3uivFunc)glGetFunction("glSecondaryColorP3uiv");
#	endif
#	ifdef glVertexAttribP1ui
	_glVertexAttribP1ui = (glVertexAttribP1uiFunc)glGetFunction("glVertexAttribP1ui");
#	endif
#	ifdef glVertexAttribP1uiv
	_glVertexAttribP1uiv = (glVertexAttribP1uivFunc)glGetFunction("glVertexAttribP1uiv");
#	endif
#	ifdef glVertexAttribP2ui
	_glVertexAttribP2ui = (glVertexAttribP2uiFunc)glGetFunction("glVertexAttribP2ui");
#	endif
#	ifdef glVertexAttribP2uiv
	_glVertexAttribP2uiv = (glVertexAttribP2uivFunc)glGetFunction("glVertexAttribP2uiv");
#	endif
#	ifdef glVertexAttribP3ui
	_glVertexAttribP3ui = (glVertexAttribP3uiFunc)glGetFunction("glVertexAttribP3ui");
#	endif
#	ifdef glVertexAttribP3uiv
	_glVertexAttribP3uiv = (glVertexAttribP3uivFunc)glGetFunction("glVertexAttribP3uiv");
#	endif
#	ifdef glVertexAttribP4ui
	_glVertexAttribP4ui = (glVertexAttribP4uiFunc)glGetFunction("glVertexAttribP4ui");
#	endif
#	ifdef glVertexAttribP4uiv
	_glVertexAttribP4uiv = (glVertexAttribP4uivFunc)glGetFunction("glVertexAttribP4uiv");
#	endif
#	ifdef glDrawArraysIndirect
	_glDrawArraysIndirect = (glDrawArraysIndirectFunc)glGetFunction("glDrawArraysIndirect");
#	endif
#	ifdef glDrawElementsIndirect
	_glDrawElementsIndirect = (glDrawElementsIndirectFunc)glGetFunction("glDrawElementsIndirect");
#	endif
#	ifdef glUniform1d
	_glUniform1d = (glUniform1dFunc)glGetFunction("glUniform1d");
#	endif
#	ifdef glUniform2d
	_glUniform2d = (glUniform2dFunc)glGetFunction("glUniform2d");
#	endif
#	ifdef glUniform3d
	_glUniform3d = (glUniform3dFunc)glGetFunction("glUniform3d");
#	endif
#	ifdef glUniform4d
	_glUniform4d = (glUniform4dFunc)glGetFunction("glUniform4d");
#	endif
#	ifdef glUniform1dv
	_glUniform1dv = (glUniform1dvFunc)glGetFunction("glUniform1dv");
#	endif
#	ifdef glUniform2dv
	_glUniform2dv = (glUniform2dvFunc)glGetFunction("glUniform2dv");
#	endif
#	ifdef glUniform3dv
	_glUniform3dv = (glUniform3dvFunc)glGetFunction("glUniform3dv");
#	endif
#	ifdef glUniform4dv
	_glUniform4dv = (glUniform4dvFunc)glGetFunction("glUniform4dv");
#	endif
#	ifdef glUniformMatrix2dv
	_glUniformMatrix2dv = (glUniformMatrix2dvFunc)glGetFunction("glUniformMatrix2dv");
#	endif
#	ifdef glUniformMatrix3dv
	_glUniformMatrix3dv = (glUniformMatrix3dvFunc)glGetFunction("glUniformMatrix3dv");
#	endif
#	ifdef glUniformMatrix4dv
	_glUniformMatrix4dv = (glUniformMatrix4dvFunc)glGetFunction("glUniformMatrix4dv");
#	endif
#	ifdef glUniformMatrix2x3dv
	_glUniformMatrix2x3dv = (glUniformMatrix2x3dvFunc)glGetFunction("glUniformMatrix2x3dv");
#	endif
#	ifdef glUniformMatrix2x4dv
	_glUniformMatrix2x4dv = (glUniformMatrix2x4dvFunc)glGetFunction("glUniformMatrix2x4dv");
#	endif
#	ifdef glUniformMatrix3x2dv
	_glUniformMatrix3x2dv = (glUniformMatrix3x2dvFunc)glGetFunction("glUniformMatrix3x2dv");
#	endif
#	ifdef glUniformMatrix3x4dv
	_glUniformMatrix3x4dv = (glUniformMatrix3x4dvFunc)glGetFunction("glUniformMatrix3x4dv");
#	endif
#	ifdef glUniformMatrix4x2dv
	_glUniformMatrix4x2dv = (glUniformMatrix4x2dvFunc)glGetFunction("glUniformMatrix4x2dv");
#	endif
#	ifdef glUniformMatrix4x3dv
	_glUniformMatrix4x3dv = (glUniformMatrix4x3dvFunc)glGetFunction("glUniformMatrix4x3dv");
#	endif
#	ifdef glGetUniformdv
	_glGetUniformdv = (glGetUniformdvFunc)glGetFunction("glGetUniformdv");
#	endif
#	ifdef glGetSubroutineUniformLocation
	_glGetSubroutineUniformLocation = (glGetSubroutineUniformLocationFunc)glGetFunction("glGetSubroutineUniformLocation");
#	endif
#	ifdef glGetSubroutineIndex
	_glGetSubroutineIndex = (glGetSubroutineIndexFunc)glGetFunction("glGetSubroutineIndex");
#	endif
#	ifdef glGetActiveSubroutineUniformiv
	_glGetActiveSubroutineUniformiv = (glGetActiveSubroutineUniformivFunc)glGetFunction("glGetActiveSubroutineUniformiv");
#	endif
#	ifdef glGetActiveSubroutineUniformName
	_glGetActiveSubroutineUniformName = (glGetActiveSubroutineUniformNameFunc)glGetFunction("glGetActiveSubroutineUniformName");
#	endif
#	ifdef glGetActiveSubroutineName
	_glGetActiveSubroutineName = (glGetActiveSubroutineNameFunc)glGetFunction("glGetActiveSubroutineName");
#	endif
#	ifdef glUniformSubroutinesuiv
	_glUniformSubroutinesuiv = (glUniformSubroutinesuivFunc)glGetFunction("glUniformSubroutinesuiv");
#	endif
#	ifdef glGetUniformSubroutineuiv
	_glGetUniformSubroutineuiv = (glGetUniformSubroutineuivFunc)glGetFunction("glGetUniformSubroutineuiv");
#	endif
#	ifdef glGetProgramStageiv
	_glGetProgramStageiv = (glGetProgramStageivFunc)glGetFunction("glGetProgramStageiv");
#	endif
#	ifdef glPatchParameteri
	_glPatchParameteri = (glPatchParameteriFunc)glGetFunction("glPatchParameteri");
#	endif
#	ifdef glPatchParameterfv
	_glPatchParameterfv = (glPatchParameterfvFunc)glGetFunction("glPatchParameterfv");
#	endif
#	ifdef glBindTransformFeedback
	_glBindTransformFeedback = (glBindTransformFeedbackFunc)glGetFunction("glBindTransformFeedback");
#	endif
#	ifdef glDeleteTransformFeedbacks
	_glDeleteTransformFeedbacks = (glDeleteTransformFeedbacksFunc)glGetFunction("glDeleteTransformFeedbacks");
#	endif
#	ifdef glGenTransformFeedbacks
	_glGenTransformFeedbacks = (glGenTransformFeedbacksFunc)glGetFunction("glGenTransformFeedbacks");
#	endif
#	ifdef glIsTransformFeedback
	_glIsTransformFeedback = (glIsTransformFeedbackFunc)glGetFunction("glIsTransformFeedback");
#	endif
#	ifdef glPauseTransformFeedback
	_glPauseTransformFeedback = (glPauseTransformFeedbackFunc)glGetFunction("glPauseTransformFeedback");
#	endif
#	ifdef glResumeTransformFeedback
	_glResumeTransformFeedback = (glResumeTransformFeedbackFunc)glGetFunction("glResumeTransformFeedback");
#	endif
#	ifdef glDrawTransformFeedback
	_glDrawTransformFeedback = (glDrawTransformFeedbackFunc)glGetFunction("glDrawTransformFeedback");
#	endif
#	ifdef glDrawTransformFeedbackStream
	_glDrawTransformFeedbackStream = (glDrawTransformFeedbackStreamFunc)glGetFunction("glDrawTransformFeedbackStream");
#	endif
#	ifdef glBeginQueryIndexed
	_glBeginQueryIndexed = (glBeginQueryIndexedFunc)glGetFunction("glBeginQueryIndexed");
#	endif
#	ifdef glEndQueryIndexed
	_glEndQueryIndexed = (glEndQueryIndexedFunc)glGetFunction("glEndQueryIndexed");
#	endif
#	ifdef glGetQueryIndexediv
	_glGetQueryIndexediv = (glGetQueryIndexedivFunc)glGetFunction("glGetQueryIndexediv");
#	endif
#	ifdef glReleaseShaderCompiler
	_glReleaseShaderCompiler = (glReleaseShaderCompilerFunc)glGetFunction("glReleaseShaderCompiler");
#	endif
#	ifdef glShaderBinary
	_glShaderBinary = (glShaderBinaryFunc)glGetFunction("glShaderBinary");
#	endif
#	ifdef glGetShaderPrecisionFormat
	_glGetShaderPrecisionFormat = (glGetShaderPrecisionFormatFunc)glGetFunction("glGetShaderPrecisionFormat");
#	endif
#	ifdef glDepthRangef
	_glDepthRangef = (glDepthRangefFunc)glGetFunction("glDepthRangef");
#	endif
#	ifdef glClearDepthf
	_glClearDepthf = (glClearDepthfFunc)glGetFunction("glClearDepthf");
#	endif
#	ifdef glGetProgramBinary
	_glGetProgramBinary = (glGetProgramBinaryFunc)glGetFunction("glGetProgramBinary");
#	endif
#	ifdef glProgramBinary
	_glProgramBinary = (glProgramBinaryFunc)glGetFunction("glProgramBinary");
#	endif
#	ifdef glProgramParameteri
	_glProgramParameteri = (glProgramParameteriFunc)glGetFunction("glProgramParameteri");
#	endif
#	ifdef glUseProgramStages
	_glUseProgramStages = (glUseProgramStagesFunc)glGetFunction("glUseProgramStages");
#	endif
#	ifdef glActiveShaderProgram
	_glActiveShaderProgram = (glActiveShaderProgramFunc)glGetFunction("glActiveShaderProgram");
#	endif
#	ifdef glCreateShaderProgramv
	_glCreateShaderProgramv = (glCreateShaderProgramvFunc)glGetFunction("glCreateShaderProgramv");
#	endif
#	ifdef glBindProgramPipeline
	_glBindProgramPipeline = (glBindProgramPipelineFunc)glGetFunction("glBindProgramPipeline");
#	endif
#	ifdef glDeleteProgramPipelines
	_glDeleteProgramPipelines = (glDeleteProgramPipelinesFunc)glGetFunction("glDeleteProgramPipelines");
#	endif
#	ifdef glGenProgramPipelines
	_glGenProgramPipelines = (glGenProgramPipelinesFunc)glGetFunction("glGenProgramPipelines");
#	endif
#	ifdef glIsProgramPipeline
	_glIsProgramPipeline = (glIsProgramPipelineFunc)glGetFunction("glIsProgramPipeline");
#	endif
#	ifdef glGetProgramPipelineiv
	_glGetProgramPipelineiv = (glGetProgramPipelineivFunc)glGetFunction("glGetProgramPipelineiv");
#	endif
#	ifdef glProgramUniform1i
	_glProgramUniform1i = (glProgramUniform1iFunc)glGetFunction("glProgramUniform1i");
#	endif
#	ifdef glProgramUniform1iv
	_glProgramUniform1iv = (glProgramUniform1ivFunc)glGetFunction("glProgramUniform1iv");
#	endif
#	ifdef glProgramUniform1f
	_glProgramUniform1f = (glProgramUniform1fFunc)glGetFunction("glProgramUniform1f");
#	endif
#	ifdef glProgramUniform1fv
	_glProgramUniform1fv = (glProgramUniform1fvFunc)glGetFunction("glProgramUniform1fv");
#	endif
#	ifdef glProgramUniform1d
	_glProgramUniform1d = (glProgramUniform1dFunc)glGetFunction("glProgramUniform1d");
#	endif
#	ifdef glProgramUniform1dv
	_glProgramUniform1dv = (glProgramUniform1dvFunc)glGetFunction("glProgramUniform1dv");
#	endif
#	ifdef glProgramUniform1ui
	_glProgramUniform1ui = (glProgramUniform1uiFunc)glGetFunction("glProgramUniform1ui");
#	endif
#	ifdef glProgramUniform1uiv
	_glProgramUniform1uiv = (glProgramUniform1uivFunc)glGetFunction("glProgramUniform1uiv");
#	endif
#	ifdef glProgramUniform2i
	_glProgramUniform2i = (glProgramUniform2iFunc)glGetFunction("glProgramUniform2i");
#	endif
#	ifdef glProgramUniform2iv
	_glProgramUniform2iv = (glProgramUniform2ivFunc)glGetFunction("glProgramUniform2iv");
#	endif
#	ifdef glProgramUniform2f
	_glProgramUniform2f = (glProgramUniform2fFunc)glGetFunction("glProgramUniform2f");
#	endif
#	ifdef glProgramUniform2fv
	_glProgramUniform2fv = (glProgramUniform2fvFunc)glGetFunction("glProgramUniform2fv");
#	endif
#	ifdef glProgramUniform2d
	_glProgramUniform2d = (glProgramUniform2dFunc)glGetFunction("glProgramUniform2d");
#	endif
#	ifdef glProgramUniform2dv
	_glProgramUniform2dv = (glProgramUniform2dvFunc)glGetFunction("glProgramUniform2dv");
#	endif
#	ifdef glProgramUniform2ui
	_glProgramUniform2ui = (glProgramUniform2uiFunc)glGetFunction("glProgramUniform2ui");
#	endif
#	ifdef glProgramUniform2uiv
	_glProgramUniform2uiv = (glProgramUniform2uivFunc)glGetFunction("glProgramUniform2uiv");
#	endif
#	ifdef glProgramUniform3i
	_glProgramUniform3i = (glProgramUniform3iFunc)glGetFunction("glProgramUniform3i");
#	endif
#	ifdef glProgramUniform3iv
	_glProgramUniform3iv = (glProgramUniform3ivFunc)glGetFunction("glProgramUniform3iv");
#	endif
#	ifdef glProgramUniform3f
	_glProgramUniform3f = (glProgramUniform3fFunc)glGetFunction("glProgramUniform3f");
#	endif
#	ifdef glProgramUniform3fv
	_glProgramUniform3fv = (glProgramUniform3fvFunc)glGetFunction("glProgramUniform3fv");
#	endif
#	ifdef glProgramUniform3d
	_glProgramUniform3d = (glProgramUniform3dFunc)glGetFunction("glProgramUniform3d");
#	endif
#	ifdef glProgramUniform3dv
	_glProgramUniform3dv = (glProgramUniform3dvFunc)glGetFunction("glProgramUniform3dv");
#	endif
#	ifdef glProgramUniform3ui
	_glProgramUniform3ui = (glProgramUniform3uiFunc)glGetFunction("glProgramUniform3ui");
#	endif
#	ifdef glProgramUniform3uiv
	_glProgramUniform3uiv = (glProgramUniform3uivFunc)glGetFunction("glProgramUniform3uiv");
#	endif
#	ifdef glProgramUniform4i
	_glProgramUniform4i = (glProgramUniform4iFunc)glGetFunction("glProgramUniform4i");
#	endif
#	ifdef glProgramUniform4iv
	_glProgramUniform4iv = (glProgramUniform4ivFunc)glGetFunction("glProgramUniform4iv");
#	endif
#	ifdef glProgramUniform4f
	_glProgramUniform4f = (glProgramUniform4fFunc)glGetFunction("glProgramUniform4f");
#	endif
#	ifdef glProgramUniform4fv
	_glProgramUniform4fv = (glProgramUniform4fvFunc)glGetFunction("glProgramUniform4fv");
#	endif
#	ifdef glProgramUniform4d
	_glProgramUniform4d = (glProgramUniform4dFunc)glGetFunction("glProgramUniform4d");
#	endif
#	ifdef glProgramUniform4dv
	_glProgramUniform4dv = (glProgramUniform4dvFunc)glGetFunction("glProgramUniform4dv");
#	endif
#	ifdef glProgramUniform4ui
	_glProgramUniform4ui = (glProgramUniform4uiFunc)glGetFunction("glProgramUniform4ui");
#	endif
#	ifdef glProgramUniform4uiv
	_glProgramUniform4uiv = (glProgramUniform4uivFunc)glGetFunction("glProgramUniform4uiv");
#	endif
#	ifdef glProgramUniformMatrix2fv
	_glProgramUniformMatrix2fv = (glProgramUniformMatrix2fvFunc)glGetFunction("glProgramUniformMatrix2fv");
#	endif
#	ifdef glProgramUniformMatrix3fv
	_glProgramUniformMatrix3fv = (glProgramUniformMatrix3fvFunc)glGetFunction("glProgramUniformMatrix3fv");
#	endif
#	ifdef glProgramUniformMatrix4fv
	_glProgramUniformMatrix4fv = (glProgramUniformMatrix4fvFunc)glGetFunction("glProgramUniformMatrix4fv");
#	endif
#	ifdef glProgramUniformMatrix2dv
	_glProgramUniformMatrix2dv = (glProgramUniformMatrix2dvFunc)glGetFunction("glProgramUniformMatrix2dv");
#	endif
#	ifdef glProgramUniformMatrix3dv
	_glProgramUniformMatrix3dv = (glProgramUniformMatrix3dvFunc)glGetFunction("glProgramUniformMatrix3dv");
#	endif
#	ifdef glProgramUniformMatrix4dv
	_glProgramUniformMatrix4dv = (glProgramUniformMatrix4dvFunc)glGetFunction("glProgramUniformMatrix4dv");
#	endif
#	ifdef glProgramUniformMatrix2x3fv
	_glProgramUniformMatrix2x3fv = (glProgramUniformMatrix2x3fvFunc)glGetFunction("glProgramUniformMatrix2x3fv");
#	endif
#	ifdef glProgramUniformMatrix3x2fv
	_glProgramUniformMatrix3x2fv = (glProgramUniformMatrix3x2fvFunc)glGetFunction("glProgramUniformMatrix3x2fv");
#	endif
#	ifdef glProgramUniformMatrix2x4fv
	_glProgramUniformMatrix2x4fv = (glProgramUniformMatrix2x4fvFunc)glGetFunction("glProgramUniformMatrix2x4fv");
#	endif
#	ifdef glProgramUniformMatrix4x2fv
	_glProgramUniformMatrix4x2fv = (glProgramUniformMatrix4x2fvFunc)glGetFunction("glProgramUniformMatrix4x2fv");
#	endif
#	ifdef glProgramUniformMatrix3x4fv
	_glProgramUniformMatrix3x4fv = (glProgramUniformMatrix3x4fvFunc)glGetFunction("glProgramUniformMatrix3x4fv");
#	endif
#	ifdef glProgramUniformMatrix4x3fv
	_glProgramUniformMatrix4x3fv = (glProgramUniformMatrix4x3fvFunc)glGetFunction("glProgramUniformMatrix4x3fv");
#	endif
#	ifdef glProgramUniformMatrix2x3dv
	_glProgramUniformMatrix2x3dv = (glProgramUniformMatrix2x3dvFunc)glGetFunction("glProgramUniformMatrix2x3dv");
#	endif
#	ifdef glProgramUniformMatrix3x2dv
	_glProgramUniformMatrix3x2dv = (glProgramUniformMatrix3x2dvFunc)glGetFunction("glProgramUniformMatrix3x2dv");
#	endif
#	ifdef glProgramUniformMatrix2x4dv
	_glProgramUniformMatrix2x4dv = (glProgramUniformMatrix2x4dvFunc)glGetFunction("glProgramUniformMatrix2x4dv");
#	endif
#	ifdef glProgramUniformMatrix4x2dv
	_glProgramUniformMatrix4x2dv = (glProgramUniformMatrix4x2dvFunc)glGetFunction("glProgramUniformMatrix4x2dv");
#	endif
#	ifdef glProgramUniformMatrix3x4dv
	_glProgramUniformMatrix3x4dv = (glProgramUniformMatrix3x4dvFunc)glGetFunction("glProgramUniformMatrix3x4dv");
#	endif
#	ifdef glProgramUniformMatrix4x3dv
	_glProgramUniformMatrix4x3dv = (glProgramUniformMatrix4x3dvFunc)glGetFunction("glProgramUniformMatrix4x3dv");
#	endif
#	ifdef glValidateProgramPipeline
	_glValidateProgramPipeline = (glValidateProgramPipelineFunc)glGetFunction("glValidateProgramPipeline");
#	endif
#	ifdef glGetProgramPipelineInfoLog
	_glGetProgramPipelineInfoLog = (glGetProgramPipelineInfoLogFunc)glGetFunction("glGetProgramPipelineInfoLog");
#	endif
#	ifdef glVertexAttribL1d
	_glVertexAttribL1d = (glVertexAttribL1dFunc)glGetFunction("glVertexAttribL1d");
#	endif
#	ifdef glVertexAttribL2d
	_glVertexAttribL2d = (glVertexAttribL2dFunc)glGetFunction("glVertexAttribL2d");
#	endif
#	ifdef glVertexAttribL3d
	_glVertexAttribL3d = (glVertexAttribL3dFunc)glGetFunction("glVertexAttribL3d");
#	endif
#	ifdef glVertexAttribL4d
	_glVertexAttribL4d = (glVertexAttribL4dFunc)glGetFunction("glVertexAttribL4d");
#	endif
#	ifdef glVertexAttribL1dv
	_glVertexAttribL1dv = (glVertexAttribL1dvFunc)glGetFunction("glVertexAttribL1dv");
#	endif
#	ifdef glVertexAttribL2dv
	_glVertexAttribL2dv = (glVertexAttribL2dvFunc)glGetFunction("glVertexAttribL2dv");
#	endif
#	ifdef glVertexAttribL3dv
	_glVertexAttribL3dv = (glVertexAttribL3dvFunc)glGetFunction("glVertexAttribL3dv");
#	endif
#	ifdef glVertexAttribL4dv
	_glVertexAttribL4dv = (glVertexAttribL4dvFunc)glGetFunction("glVertexAttribL4dv");
#	endif
#	ifdef glVertexAttribLPointer
	_glVertexAttribLPointer = (glVertexAttribLPointerFunc)glGetFunction("glVertexAttribLPointer");
#	endif
#	ifdef glGetVertexAttribLdv
	_glGetVertexAttribLdv = (glGetVertexAttribLdvFunc)glGetFunction("glGetVertexAttribLdv");
#	endif
#	ifdef glViewportArrayv
	_glViewportArrayv = (glViewportArrayvFunc)glGetFunction("glViewportArrayv");
#	endif
#	ifdef glViewportIndexedf
	_glViewportIndexedf = (glViewportIndexedfFunc)glGetFunction("glViewportIndexedf");
#	endif
#	ifdef glViewportIndexedfv
	_glViewportIndexedfv = (glViewportIndexedfvFunc)glGetFunction("glViewportIndexedfv");
#	endif
#	ifdef glScissorArrayv
	_glScissorArrayv = (glScissorArrayvFunc)glGetFunction("glScissorArrayv");
#	endif
#	ifdef glScissorIndexed
	_glScissorIndexed = (glScissorIndexedFunc)glGetFunction("glScissorIndexed");
#	endif
#	ifdef glScissorIndexedv
	_glScissorIndexedv = (glScissorIndexedvFunc)glGetFunction("glScissorIndexedv");
#	endif
#	ifdef glDepthRangeArrayv
	_glDepthRangeArrayv = (glDepthRangeArrayvFunc)glGetFunction("glDepthRangeArrayv");
#	endif
#	ifdef glDepthRangeIndexed
	_glDepthRangeIndexed = (glDepthRangeIndexedFunc)glGetFunction("glDepthRangeIndexed");
#	endif
#	ifdef glGetFloati_v
	_glGetFloati_v = (glGetFloati_vFunc)glGetFunction("glGetFloati_v");
#	endif
#	ifdef glGetDoublei_v
	_glGetDoublei_v = (glGetDoublei_vFunc)glGetFunction("glGetDoublei_v");
#	endif
#	ifdef glCreateSyncFromCLeventARB
	_glCreateSyncFromCLeventARB = (glCreateSyncFromCLeventARBFunc)glGetFunction("glCreateSyncFromCLeventARB");
#	endif
#	ifdef glDebugMessageControlARB
	_glDebugMessageControlARB = (glDebugMessageControlARBFunc)glGetFunction("glDebugMessageControlARB");
#	endif
#	ifdef glDebugMessageInsertARB
	_glDebugMessageInsertARB = (glDebugMessageInsertARBFunc)glGetFunction("glDebugMessageInsertARB");
#	endif
#	ifdef glDebugMessageCallbackARB
	_glDebugMessageCallbackARB = (glDebugMessageCallbackARBFunc)glGetFunction("glDebugMessageCallbackARB");
#	endif
#	ifdef glGetDebugMessageLogARB
	_glGetDebugMessageLogARB = (glGetDebugMessageLogARBFunc)glGetFunction("glGetDebugMessageLogARB");
#	endif
#	ifdef glGetGraphicsResetStatusARB
	_glGetGraphicsResetStatusARB = (glGetGraphicsResetStatusARBFunc)glGetFunction("glGetGraphicsResetStatusARB");
#	endif
#	ifdef glGetnMapdvARB
	_glGetnMapdvARB = (glGetnMapdvARBFunc)glGetFunction("glGetnMapdvARB");
#	endif
#	ifdef glGetnMapfvARB
	_glGetnMapfvARB = (glGetnMapfvARBFunc)glGetFunction("glGetnMapfvARB");
#	endif
#	ifdef glGetnMapivARB
	_glGetnMapivARB = (glGetnMapivARBFunc)glGetFunction("glGetnMapivARB");
#	endif
#	ifdef glGetnPixelMapfvARB
	_glGetnPixelMapfvARB = (glGetnPixelMapfvARBFunc)glGetFunction("glGetnPixelMapfvARB");
#	endif
#	ifdef glGetnPixelMapuivARB
	_glGetnPixelMapuivARB = (glGetnPixelMapuivARBFunc)glGetFunction("glGetnPixelMapuivARB");
#	endif
#	ifdef glGetnPixelMapusvARB
	_glGetnPixelMapusvARB = (glGetnPixelMapusvARBFunc)glGetFunction("glGetnPixelMapusvARB");
#	endif
#	ifdef glGetnPolygonStippleARB
	_glGetnPolygonStippleARB = (glGetnPolygonStippleARBFunc)glGetFunction("glGetnPolygonStippleARB");
#	endif
#	ifdef glGetnColorTableARB
	_glGetnColorTableARB = (glGetnColorTableARBFunc)glGetFunction("glGetnColorTableARB");
#	endif
#	ifdef glGetnConvolutionFilterARB
	_glGetnConvolutionFilterARB = (glGetnConvolutionFilterARBFunc)glGetFunction("glGetnConvolutionFilterARB");
#	endif
#	ifdef glGetnSeparableFilterARB
	_glGetnSeparableFilterARB = (glGetnSeparableFilterARBFunc)glGetFunction("glGetnSeparableFilterARB");
#	endif
#	ifdef glGetnHistogramARB
	_glGetnHistogramARB = (glGetnHistogramARBFunc)glGetFunction("glGetnHistogramARB");
#	endif
#	ifdef glGetnMinmaxARB
	_glGetnMinmaxARB = (glGetnMinmaxARBFunc)glGetFunction("glGetnMinmaxARB");
#	endif
#	ifdef glGetnTexImageARB
	_glGetnTexImageARB = (glGetnTexImageARBFunc)glGetFunction("glGetnTexImageARB");
#	endif
#	ifdef glReadnPixelsARB
	_glReadnPixelsARB = (glReadnPixelsARBFunc)glGetFunction("glReadnPixelsARB");
#	endif
#	ifdef glGetnCompressedTexImageARB
	_glGetnCompressedTexImageARB = (glGetnCompressedTexImageARBFunc)glGetFunction("glGetnCompressedTexImageARB");
#	endif
#	ifdef glGetnUniformfvARB
	_glGetnUniformfvARB = (glGetnUniformfvARBFunc)glGetFunction("glGetnUniformfvARB");
#	endif
#	ifdef glGetnUniformivARB
	_glGetnUniformivARB = (glGetnUniformivARBFunc)glGetFunction("glGetnUniformivARB");
#	endif
#	ifdef glGetnUniformuivARB
	_glGetnUniformuivARB = (glGetnUniformuivARBFunc)glGetFunction("glGetnUniformuivARB");
#	endif
#	ifdef glGetnUniformdvARB
	_glGetnUniformdvARB = (glGetnUniformdvARBFunc)glGetFunction("glGetnUniformdvARB");
#	endif
#	ifdef glDrawArraysInstancedBaseInstance
	_glDrawArraysInstancedBaseInstance = (glDrawArraysInstancedBaseInstanceFunc)glGetFunction("glDrawArraysInstancedBaseInstance");
#	endif
#	ifdef glDrawElementsInstancedBaseInstance
	_glDrawElementsInstancedBaseInstance = (glDrawElementsInstancedBaseInstanceFunc)glGetFunction("glDrawElementsInstancedBaseInstance");
#	endif
#	ifdef glDrawElementsInstancedBaseVertexBaseInstance
	_glDrawElementsInstancedBaseVertexBaseInstance = (glDrawElementsInstancedBaseVertexBaseInstanceFunc)glGetFunction("glDrawElementsInstancedBaseVertexBaseInstance");
#	endif
#	ifdef glDrawTransformFeedbackInstanced
	_glDrawTransformFeedbackInstanced = (glDrawTransformFeedbackInstancedFunc)glGetFunction("glDrawTransformFeedbackInstanced");
#	endif
#	ifdef glDrawTransformFeedbackStreamInstanced
	_glDrawTransformFeedbackStreamInstanced = (glDrawTransformFeedbackStreamInstancedFunc)glGetFunction("glDrawTransformFeedbackStreamInstanced");
#	endif
#	ifdef glGetInternalformativ
	_glGetInternalformativ = (glGetInternalformativFunc)glGetFunction("glGetInternalformativ");
#	endif
#	ifdef glGetActiveAtomicCounterBufferiv
	_glGetActiveAtomicCounterBufferiv = (glGetActiveAtomicCounterBufferivFunc)glGetFunction("glGetActiveAtomicCounterBufferiv");
#	endif
#	ifdef glBindImageTexture
	_glBindImageTexture = (glBindImageTextureFunc)glGetFunction("glBindImageTexture");
#	endif
#	ifdef glMemoryBarrier
	_glMemoryBarrier = (glMemoryBarrierFunc)glGetFunction("glMemoryBarrier");
#	endif
#	ifdef glTexStorage1D
	_glTexStorage1D = (glTexStorage1DFunc)glGetFunction("glTexStorage1D");
#	endif
#	ifdef glTexStorage2D
	_glTexStorage2D = (glTexStorage2DFunc)glGetFunction("glTexStorage2D");
#	endif
#	ifdef glTexStorage3D
	_glTexStorage3D = (glTexStorage3DFunc)glGetFunction("glTexStorage3D");
#	endif
#	ifdef glTextureStorage1DEXT
	_glTextureStorage1DEXT = (glTextureStorage1DEXTFunc)glGetFunction("glTextureStorage1DEXT");
#	endif
#	ifdef glTextureStorage2DEXT
	_glTextureStorage2DEXT = (glTextureStorage2DEXTFunc)glGetFunction("glTextureStorage2DEXT");
#	endif
#	ifdef glTextureStorage3DEXT
	_glTextureStorage3DEXT = (glTextureStorage3DEXTFunc)glGetFunction("glTextureStorage3DEXT");
#	endif
#	ifdef glDebugMessageControl
	_glDebugMessageControl = (glDebugMessageControlFunc)glGetFunction("glDebugMessageControl");
#	endif
#	ifdef glDebugMessageInsert
	_glDebugMessageInsert = (glDebugMessageInsertFunc)glGetFunction("glDebugMessageInsert");
#	endif
#	ifdef glDebugMessageCallback
	_glDebugMessageCallback = (glDebugMessageCallbackFunc)glGetFunction("glDebugMessageCallback");
#	endif
#	ifdef glGetDebugMessageLog
	_glGetDebugMessageLog = (glGetDebugMessageLogFunc)glGetFunction("glGetDebugMessageLog");
#	endif
#	ifdef glPushDebugGroup
	_glPushDebugGroup = (glPushDebugGroupFunc)glGetFunction("glPushDebugGroup");
#	endif
#	ifdef glPopDebugGroup
	_glPopDebugGroup = (glPopDebugGroupFunc)glGetFunction("glPopDebugGroup");
#	endif
#	ifdef glObjectLabel
	_glObjectLabel = (glObjectLabelFunc)glGetFunction("glObjectLabel");
#	endif
#	ifdef glGetObjectLabel
	_glGetObjectLabel = (glGetObjectLabelFunc)glGetFunction("glGetObjectLabel");
#	endif
#	ifdef glObjectPtrLabel
	_glObjectPtrLabel = (glObjectPtrLabelFunc)glGetFunction("glObjectPtrLabel");
#	endif
#	ifdef glGetObjectPtrLabel
	_glGetObjectPtrLabel = (glGetObjectPtrLabelFunc)glGetFunction("glGetObjectPtrLabel");
#	endif
#	ifdef glClearBufferData
	_glClearBufferData = (glClearBufferDataFunc)glGetFunction("glClearBufferData");
#	endif
#	ifdef glClearBufferSubData
	_glClearBufferSubData = (glClearBufferSubDataFunc)glGetFunction("glClearBufferSubData");
#	endif
#	ifdef glClearNamedBufferDataEXT
	_glClearNamedBufferDataEXT = (glClearNamedBufferDataEXTFunc)glGetFunction("glClearNamedBufferDataEXT");
#	endif
#	ifdef glClearNamedBufferSubDataEXT
	_glClearNamedBufferSubDataEXT = (glClearNamedBufferSubDataEXTFunc)glGetFunction("glClearNamedBufferSubDataEXT");
#	endif
#	ifdef glDispatchCompute
	_glDispatchCompute = (glDispatchComputeFunc)glGetFunction("glDispatchCompute");
#	endif
#	ifdef glDispatchComputeIndirect
	_glDispatchComputeIndirect = (glDispatchComputeIndirectFunc)glGetFunction("glDispatchComputeIndirect");
#	endif
#	ifdef glCopyImageSubData
	_glCopyImageSubData = (glCopyImageSubDataFunc)glGetFunction("glCopyImageSubData");
#	endif
#	ifdef glTextureView
	_glTextureView = (glTextureViewFunc)glGetFunction("glTextureView");
#	endif
#	ifdef glBindVertexBuffer
	_glBindVertexBuffer = (glBindVertexBufferFunc)glGetFunction("glBindVertexBuffer");
#	endif
#	ifdef glVertexAttribFormat
	_glVertexAttribFormat = (glVertexAttribFormatFunc)glGetFunction("glVertexAttribFormat");
#	endif
#	ifdef glVertexAttribIFormat
	_glVertexAttribIFormat = (glVertexAttribIFormatFunc)glGetFunction("glVertexAttribIFormat");
#	endif
#	ifdef glVertexAttribLFormat
	_glVertexAttribLFormat = (glVertexAttribLFormatFunc)glGetFunction("glVertexAttribLFormat");
#	endif
#	ifdef glVertexAttribBinding
	_glVertexAttribBinding = (glVertexAttribBindingFunc)glGetFunction("glVertexAttribBinding");
#	endif
#	ifdef glVertexBindingDivisor
	_glVertexBindingDivisor = (glVertexBindingDivisorFunc)glGetFunction("glVertexBindingDivisor");
#	endif
#	ifdef glVertexArrayBindVertexBufferEXT
	_glVertexArrayBindVertexBufferEXT = (glVertexArrayBindVertexBufferEXTFunc)glGetFunction("glVertexArrayBindVertexBufferEXT");
#	endif
#	ifdef glVertexArrayVertexAttribFormatEXT
	_glVertexArrayVertexAttribFormatEXT = (glVertexArrayVertexAttribFormatEXTFunc)glGetFunction("glVertexArrayVertexAttribFormatEXT");
#	endif
#	ifdef glVertexArrayVertexAttribIFormatEXT
	_glVertexArrayVertexAttribIFormatEXT = (glVertexArrayVertexAttribIFormatEXTFunc)glGetFunction("glVertexArrayVertexAttribIFormatEXT");
#	endif
#	ifdef glVertexArrayVertexAttribLFormatEXT
	_glVertexArrayVertexAttribLFormatEXT = (glVertexArrayVertexAttribLFormatEXTFunc)glGetFunction("glVertexArrayVertexAttribLFormatEXT");
#	endif
#	ifdef glVertexArrayVertexAttribBindingEXT
	_glVertexArrayVertexAttribBindingEXT = (glVertexArrayVertexAttribBindingEXTFunc)glGetFunction("glVertexArrayVertexAttribBindingEXT");
#	endif
#	ifdef glVertexArrayVertexBindingDivisorEXT
	_glVertexArrayVertexBindingDivisorEXT = (glVertexArrayVertexBindingDivisorEXTFunc)glGetFunction("glVertexArrayVertexBindingDivisorEXT");
#	endif
#	ifdef glFramebufferParameteri
	_glFramebufferParameteri = (glFramebufferParameteriFunc)glGetFunction("glFramebufferParameteri");
#	endif
#	ifdef glGetFramebufferParameteriv
	_glGetFramebufferParameteriv = (glGetFramebufferParameterivFunc)glGetFunction("glGetFramebufferParameteriv");
#	endif
#	ifdef glNamedFramebufferParameteriEXT
	_glNamedFramebufferParameteriEXT = (glNamedFramebufferParameteriEXTFunc)glGetFunction("glNamedFramebufferParameteriEXT");
#	endif
#	ifdef glGetNamedFramebufferParameterivEXT
	_glGetNamedFramebufferParameterivEXT = (glGetNamedFramebufferParameterivEXTFunc)glGetFunction("glGetNamedFramebufferParameterivEXT");
#	endif
#	ifdef glGetInternalformati64v
	_glGetInternalformati64v = (glGetInternalformati64vFunc)glGetFunction("glGetInternalformati64v");
#	endif
#	ifdef glInvalidateTexSubImage
	_glInvalidateTexSubImage = (glInvalidateTexSubImageFunc)glGetFunction("glInvalidateTexSubImage");
#	endif
#	ifdef glInvalidateTexImage
	_glInvalidateTexImage = (glInvalidateTexImageFunc)glGetFunction("glInvalidateTexImage");
#	endif
#	ifdef glInvalidateBufferSubData
	_glInvalidateBufferSubData = (glInvalidateBufferSubDataFunc)glGetFunction("glInvalidateBufferSubData");
#	endif
#	ifdef glInvalidateBufferData
	_glInvalidateBufferData = (glInvalidateBufferDataFunc)glGetFunction("glInvalidateBufferData");
#	endif
#	ifdef glInvalidateFramebuffer
	_glInvalidateFramebuffer = (glInvalidateFramebufferFunc)glGetFunction("glInvalidateFramebuffer");
#	endif
#	ifdef glInvalidateSubFramebuffer
	_glInvalidateSubFramebuffer = (glInvalidateSubFramebufferFunc)glGetFunction("glInvalidateSubFramebuffer");
#	endif
#	ifdef glMultiDrawArraysIndirect
	_glMultiDrawArraysIndirect = (glMultiDrawArraysIndirectFunc)glGetFunction("glMultiDrawArraysIndirect");
#	endif
#	ifdef glMultiDrawElementsIndirect
	_glMultiDrawElementsIndirect = (glMultiDrawElementsIndirectFunc)glGetFunction("glMultiDrawElementsIndirect");
#	endif
#	ifdef glGetProgramInterfaceiv
	_glGetProgramInterfaceiv = (glGetProgramInterfaceivFunc)glGetFunction("glGetProgramInterfaceiv");
#	endif
#	ifdef glGetProgramResourceIndex
	_glGetProgramResourceIndex = (glGetProgramResourceIndexFunc)glGetFunction("glGetProgramResourceIndex");
#	endif
#	ifdef glGetProgramResourceName
	_glGetProgramResourceName = (glGetProgramResourceNameFunc)glGetFunction("glGetProgramResourceName");
#	endif
#	ifdef glGetProgramResourceiv
	_glGetProgramResourceiv = (glGetProgramResourceivFunc)glGetFunction("glGetProgramResourceiv");
#	endif
#	ifdef glGetProgramResourceLocation
	_glGetProgramResourceLocation = (glGetProgramResourceLocationFunc)glGetFunction("glGetProgramResourceLocation");
#	endif
#	ifdef glGetProgramResourceLocationIndex
	_glGetProgramResourceLocationIndex = (glGetProgramResourceLocationIndexFunc)glGetFunction("glGetProgramResourceLocationIndex");
#	endif
#	ifdef glShaderStorageBlockBinding
	_glShaderStorageBlockBinding = (glShaderStorageBlockBindingFunc)glGetFunction("glShaderStorageBlockBinding");
#	endif
#	ifdef glTexBufferRange
	_glTexBufferRange = (glTexBufferRangeFunc)glGetFunction("glTexBufferRange");
#	endif
#	ifdef glTextureBufferRangeEXT
	_glTextureBufferRangeEXT = (glTextureBufferRangeEXTFunc)glGetFunction("glTextureBufferRangeEXT");
#	endif
#	ifdef glTexStorage2DMultisample
	_glTexStorage2DMultisample = (glTexStorage2DMultisampleFunc)glGetFunction("glTexStorage2DMultisample");
#	endif
#	ifdef glTexStorage3DMultisample
	_glTexStorage3DMultisample = (glTexStorage3DMultisampleFunc)glGetFunction("glTexStorage3DMultisample");
#	endif
#	ifdef glTextureStorage2DMultisampleEXT
	_glTextureStorage2DMultisampleEXT = (glTextureStorage2DMultisampleEXTFunc)glGetFunction("glTextureStorage2DMultisampleEXT");
#	endif
#	ifdef glTextureStorage3DMultisampleEXT
	_glTextureStorage3DMultisampleEXT = (glTextureStorage3DMultisampleEXTFunc)glGetFunction("glTextureStorage3DMultisampleEXT");
#	endif
#	ifdef glBlendColorEXT
	_glBlendColorEXT = (glBlendColorEXTFunc)glGetFunction("glBlendColorEXT");
#	endif
#	ifdef glPolygonOffsetEXT
	_glPolygonOffsetEXT = (glPolygonOffsetEXTFunc)glGetFunction("glPolygonOffsetEXT");
#	endif
#	ifdef glTexImage3DEXT
	_glTexImage3DEXT = (glTexImage3DEXTFunc)glGetFunction("glTexImage3DEXT");
#	endif
#	ifdef glTexSubImage3DEXT
	_glTexSubImage3DEXT = (glTexSubImage3DEXTFunc)glGetFunction("glTexSubImage3DEXT");
#	endif
#	ifdef glGetTexFilterFuncSGIS
	_glGetTexFilterFuncSGIS = (glGetTexFilterFuncSGISFunc)glGetFunction("glGetTexFilterFuncSGIS");
#	endif
#	ifdef glTexFilterFuncSGIS
	_glTexFilterFuncSGIS = (glTexFilterFuncSGISFunc)glGetFunction("glTexFilterFuncSGIS");
#	endif
#	ifdef glTexSubImage1DEXT
	_glTexSubImage1DEXT = (glTexSubImage1DEXTFunc)glGetFunction("glTexSubImage1DEXT");
#	endif
#	ifdef glTexSubImage2DEXT
	_glTexSubImage2DEXT = (glTexSubImage2DEXTFunc)glGetFunction("glTexSubImage2DEXT");
#	endif
#	ifdef glCopyTexImage1DEXT
	_glCopyTexImage1DEXT = (glCopyTexImage1DEXTFunc)glGetFunction("glCopyTexImage1DEXT");
#	endif
#	ifdef glCopyTexImage2DEXT
	_glCopyTexImage2DEXT = (glCopyTexImage2DEXTFunc)glGetFunction("glCopyTexImage2DEXT");
#	endif
#	ifdef glCopyTexSubImage1DEXT
	_glCopyTexSubImage1DEXT = (glCopyTexSubImage1DEXTFunc)glGetFunction("glCopyTexSubImage1DEXT");
#	endif
#	ifdef glCopyTexSubImage2DEXT
	_glCopyTexSubImage2DEXT = (glCopyTexSubImage2DEXTFunc)glGetFunction("glCopyTexSubImage2DEXT");
#	endif
#	ifdef glCopyTexSubImage3DEXT
	_glCopyTexSubImage3DEXT = (glCopyTexSubImage3DEXTFunc)glGetFunction("glCopyTexSubImage3DEXT");
#	endif
#	ifdef glGetHistogramEXT
	_glGetHistogramEXT = (glGetHistogramEXTFunc)glGetFunction("glGetHistogramEXT");
#	endif
#	ifdef glGetHistogramParameterfvEXT
	_glGetHistogramParameterfvEXT = (glGetHistogramParameterfvEXTFunc)glGetFunction("glGetHistogramParameterfvEXT");
#	endif
#	ifdef glGetHistogramParameterivEXT
	_glGetHistogramParameterivEXT = (glGetHistogramParameterivEXTFunc)glGetFunction("glGetHistogramParameterivEXT");
#	endif
#	ifdef glGetMinmaxEXT
	_glGetMinmaxEXT = (glGetMinmaxEXTFunc)glGetFunction("glGetMinmaxEXT");
#	endif
#	ifdef glGetMinmaxParameterfvEXT
	_glGetMinmaxParameterfvEXT = (glGetMinmaxParameterfvEXTFunc)glGetFunction("glGetMinmaxParameterfvEXT");
#	endif
#	ifdef glGetMinmaxParameterivEXT
	_glGetMinmaxParameterivEXT = (glGetMinmaxParameterivEXTFunc)glGetFunction("glGetMinmaxParameterivEXT");
#	endif
#	ifdef glHistogramEXT
	_glHistogramEXT = (glHistogramEXTFunc)glGetFunction("glHistogramEXT");
#	endif
#	ifdef glMinmaxEXT
	_glMinmaxEXT = (glMinmaxEXTFunc)glGetFunction("glMinmaxEXT");
#	endif
#	ifdef glResetHistogramEXT
	_glResetHistogramEXT = (glResetHistogramEXTFunc)glGetFunction("glResetHistogramEXT");
#	endif
#	ifdef glResetMinmaxEXT
	_glResetMinmaxEXT = (glResetMinmaxEXTFunc)glGetFunction("glResetMinmaxEXT");
#	endif
#	ifdef glConvolutionFilter1DEXT
	_glConvolutionFilter1DEXT = (glConvolutionFilter1DEXTFunc)glGetFunction("glConvolutionFilter1DEXT");
#	endif
#	ifdef glConvolutionFilter2DEXT
	_glConvolutionFilter2DEXT = (glConvolutionFilter2DEXTFunc)glGetFunction("glConvolutionFilter2DEXT");
#	endif
#	ifdef glConvolutionParameterfEXT
	_glConvolutionParameterfEXT = (glConvolutionParameterfEXTFunc)glGetFunction("glConvolutionParameterfEXT");
#	endif
#	ifdef glConvolutionParameterfvEXT
	_glConvolutionParameterfvEXT = (glConvolutionParameterfvEXTFunc)glGetFunction("glConvolutionParameterfvEXT");
#	endif
#	ifdef glConvolutionParameteriEXT
	_glConvolutionParameteriEXT = (glConvolutionParameteriEXTFunc)glGetFunction("glConvolutionParameteriEXT");
#	endif
#	ifdef glConvolutionParameterivEXT
	_glConvolutionParameterivEXT = (glConvolutionParameterivEXTFunc)glGetFunction("glConvolutionParameterivEXT");
#	endif
#	ifdef glCopyConvolutionFilter1DEXT
	_glCopyConvolutionFilter1DEXT = (glCopyConvolutionFilter1DEXTFunc)glGetFunction("glCopyConvolutionFilter1DEXT");
#	endif
#	ifdef glCopyConvolutionFilter2DEXT
	_glCopyConvolutionFilter2DEXT = (glCopyConvolutionFilter2DEXTFunc)glGetFunction("glCopyConvolutionFilter2DEXT");
#	endif
#	ifdef glGetConvolutionFilterEXT
	_glGetConvolutionFilterEXT = (glGetConvolutionFilterEXTFunc)glGetFunction("glGetConvolutionFilterEXT");
#	endif
#	ifdef glGetConvolutionParameterfvEXT
	_glGetConvolutionParameterfvEXT = (glGetConvolutionParameterfvEXTFunc)glGetFunction("glGetConvolutionParameterfvEXT");
#	endif
#	ifdef glGetConvolutionParameterivEXT
	_glGetConvolutionParameterivEXT = (glGetConvolutionParameterivEXTFunc)glGetFunction("glGetConvolutionParameterivEXT");
#	endif
#	ifdef glGetSeparableFilterEXT
	_glGetSeparableFilterEXT = (glGetSeparableFilterEXTFunc)glGetFunction("glGetSeparableFilterEXT");
#	endif
#	ifdef glSeparableFilter2DEXT
	_glSeparableFilter2DEXT = (glSeparableFilter2DEXTFunc)glGetFunction("glSeparableFilter2DEXT");
#	endif
#	ifdef glColorTableSGI
	_glColorTableSGI = (glColorTableSGIFunc)glGetFunction("glColorTableSGI");
#	endif
#	ifdef glColorTableParameterfvSGI
	_glColorTableParameterfvSGI = (glColorTableParameterfvSGIFunc)glGetFunction("glColorTableParameterfvSGI");
#	endif
#	ifdef glColorTableParameterivSGI
	_glColorTableParameterivSGI = (glColorTableParameterivSGIFunc)glGetFunction("glColorTableParameterivSGI");
#	endif
#	ifdef glCopyColorTableSGI
	_glCopyColorTableSGI = (glCopyColorTableSGIFunc)glGetFunction("glCopyColorTableSGI");
#	endif
#	ifdef glGetColorTableSGI
	_glGetColorTableSGI = (glGetColorTableSGIFunc)glGetFunction("glGetColorTableSGI");
#	endif
#	ifdef glGetColorTableParameterfvSGI
	_glGetColorTableParameterfvSGI = (glGetColorTableParameterfvSGIFunc)glGetFunction("glGetColorTableParameterfvSGI");
#	endif
#	ifdef glGetColorTableParameterivSGI
	_glGetColorTableParameterivSGI = (glGetColorTableParameterivSGIFunc)glGetFunction("glGetColorTableParameterivSGI");
#	endif
#	ifdef glPixelTexGenSGIX
	_glPixelTexGenSGIX = (glPixelTexGenSGIXFunc)glGetFunction("glPixelTexGenSGIX");
#	endif
#	ifdef glPixelTexGenParameteriSGIS
	_glPixelTexGenParameteriSGIS = (glPixelTexGenParameteriSGISFunc)glGetFunction("glPixelTexGenParameteriSGIS");
#	endif
#	ifdef glPixelTexGenParameterivSGIS
	_glPixelTexGenParameterivSGIS = (glPixelTexGenParameterivSGISFunc)glGetFunction("glPixelTexGenParameterivSGIS");
#	endif
#	ifdef glPixelTexGenParameterfSGIS
	_glPixelTexGenParameterfSGIS = (glPixelTexGenParameterfSGISFunc)glGetFunction("glPixelTexGenParameterfSGIS");
#	endif
#	ifdef glPixelTexGenParameterfvSGIS
	_glPixelTexGenParameterfvSGIS = (glPixelTexGenParameterfvSGISFunc)glGetFunction("glPixelTexGenParameterfvSGIS");
#	endif
#	ifdef glGetPixelTexGenParameterivSGIS
	_glGetPixelTexGenParameterivSGIS = (glGetPixelTexGenParameterivSGISFunc)glGetFunction("glGetPixelTexGenParameterivSGIS");
#	endif
#	ifdef glGetPixelTexGenParameterfvSGIS
	_glGetPixelTexGenParameterfvSGIS = (glGetPixelTexGenParameterfvSGISFunc)glGetFunction("glGetPixelTexGenParameterfvSGIS");
#	endif
#	ifdef glTexImage4DSGIS
	_glTexImage4DSGIS = (glTexImage4DSGISFunc)glGetFunction("glTexImage4DSGIS");
#	endif
#	ifdef glTexSubImage4DSGIS
	_glTexSubImage4DSGIS = (glTexSubImage4DSGISFunc)glGetFunction("glTexSubImage4DSGIS");
#	endif
#	ifdef glAreTexturesResidentEXT
	_glAreTexturesResidentEXT = (glAreTexturesResidentEXTFunc)glGetFunction("glAreTexturesResidentEXT");
#	endif
#	ifdef glBindTextureEXT
	_glBindTextureEXT = (glBindTextureEXTFunc)glGetFunction("glBindTextureEXT");
#	endif
#	ifdef glDeleteTexturesEXT
	_glDeleteTexturesEXT = (glDeleteTexturesEXTFunc)glGetFunction("glDeleteTexturesEXT");
#	endif
#	ifdef glGenTexturesEXT
	_glGenTexturesEXT = (glGenTexturesEXTFunc)glGetFunction("glGenTexturesEXT");
#	endif
#	ifdef glIsTextureEXT
	_glIsTextureEXT = (glIsTextureEXTFunc)glGetFunction("glIsTextureEXT");
#	endif
#	ifdef glPrioritizeTexturesEXT
	_glPrioritizeTexturesEXT = (glPrioritizeTexturesEXTFunc)glGetFunction("glPrioritizeTexturesEXT");
#	endif
#	ifdef glDetailTexFuncSGIS
	_glDetailTexFuncSGIS = (glDetailTexFuncSGISFunc)glGetFunction("glDetailTexFuncSGIS");
#	endif
#	ifdef glGetDetailTexFuncSGIS
	_glGetDetailTexFuncSGIS = (glGetDetailTexFuncSGISFunc)glGetFunction("glGetDetailTexFuncSGIS");
#	endif
#	ifdef glSharpenTexFuncSGIS
	_glSharpenTexFuncSGIS = (glSharpenTexFuncSGISFunc)glGetFunction("glSharpenTexFuncSGIS");
#	endif
#	ifdef glGetSharpenTexFuncSGIS
	_glGetSharpenTexFuncSGIS = (glGetSharpenTexFuncSGISFunc)glGetFunction("glGetSharpenTexFuncSGIS");
#	endif
#	ifdef glSampleMaskSGIS
	_glSampleMaskSGIS = (glSampleMaskSGISFunc)glGetFunction("glSampleMaskSGIS");
#	endif
#	ifdef glSamplePatternSGIS
	_glSamplePatternSGIS = (glSamplePatternSGISFunc)glGetFunction("glSamplePatternSGIS");
#	endif
#	ifdef glArrayElementEXT
	_glArrayElementEXT = (glArrayElementEXTFunc)glGetFunction("glArrayElementEXT");
#	endif
#	ifdef glColorPointerEXT
	_glColorPointerEXT = (glColorPointerEXTFunc)glGetFunction("glColorPointerEXT");
#	endif
#	ifdef glDrawArraysEXT
	_glDrawArraysEXT = (glDrawArraysEXTFunc)glGetFunction("glDrawArraysEXT");
#	endif
#	ifdef glEdgeFlagPointerEXT
	_glEdgeFlagPointerEXT = (glEdgeFlagPointerEXTFunc)glGetFunction("glEdgeFlagPointerEXT");
#	endif
#	ifdef glGetPointervEXT
	_glGetPointervEXT = (glGetPointervEXTFunc)glGetFunction("glGetPointervEXT");
#	endif
#	ifdef glIndexPointerEXT
	_glIndexPointerEXT = (glIndexPointerEXTFunc)glGetFunction("glIndexPointerEXT");
#	endif
#	ifdef glNormalPointerEXT
	_glNormalPointerEXT = (glNormalPointerEXTFunc)glGetFunction("glNormalPointerEXT");
#	endif
#	ifdef glTexCoordPointerEXT
	_glTexCoordPointerEXT = (glTexCoordPointerEXTFunc)glGetFunction("glTexCoordPointerEXT");
#	endif
#	ifdef glVertexPointerEXT
	_glVertexPointerEXT = (glVertexPointerEXTFunc)glGetFunction("glVertexPointerEXT");
#	endif
#	ifdef glBlendEquationEXT
	_glBlendEquationEXT = (glBlendEquationEXTFunc)glGetFunction("glBlendEquationEXT");
#	endif
#	ifdef glSpriteParameterfSGIX
	_glSpriteParameterfSGIX = (glSpriteParameterfSGIXFunc)glGetFunction("glSpriteParameterfSGIX");
#	endif
#	ifdef glSpriteParameterfvSGIX
	_glSpriteParameterfvSGIX = (glSpriteParameterfvSGIXFunc)glGetFunction("glSpriteParameterfvSGIX");
#	endif
#	ifdef glSpriteParameteriSGIX
	_glSpriteParameteriSGIX = (glSpriteParameteriSGIXFunc)glGetFunction("glSpriteParameteriSGIX");
#	endif
#	ifdef glSpriteParameterivSGIX
	_glSpriteParameterivSGIX = (glSpriteParameterivSGIXFunc)glGetFunction("glSpriteParameterivSGIX");
#	endif
#	ifdef glPointParameterfEXT
	_glPointParameterfEXT = (glPointParameterfEXTFunc)glGetFunction("glPointParameterfEXT");
#	endif
#	ifdef glPointParameterfvEXT
	_glPointParameterfvEXT = (glPointParameterfvEXTFunc)glGetFunction("glPointParameterfvEXT");
#	endif
#	ifdef glPointParameterfSGIS
	_glPointParameterfSGIS = (glPointParameterfSGISFunc)glGetFunction("glPointParameterfSGIS");
#	endif
#	ifdef glPointParameterfvSGIS
	_glPointParameterfvSGIS = (glPointParameterfvSGISFunc)glGetFunction("glPointParameterfvSGIS");
#	endif
#	ifdef glGetInstrumentsSGIX
	_glGetInstrumentsSGIX = (glGetInstrumentsSGIXFunc)glGetFunction("glGetInstrumentsSGIX");
#	endif
#	ifdef glInstrumentsBufferSGIX
	_glInstrumentsBufferSGIX = (glInstrumentsBufferSGIXFunc)glGetFunction("glInstrumentsBufferSGIX");
#	endif
#	ifdef glPollInstrumentsSGIX
	_glPollInstrumentsSGIX = (glPollInstrumentsSGIXFunc)glGetFunction("glPollInstrumentsSGIX");
#	endif
#	ifdef glReadInstrumentsSGIX
	_glReadInstrumentsSGIX = (glReadInstrumentsSGIXFunc)glGetFunction("glReadInstrumentsSGIX");
#	endif
#	ifdef glStartInstrumentsSGIX
	_glStartInstrumentsSGIX = (glStartInstrumentsSGIXFunc)glGetFunction("glStartInstrumentsSGIX");
#	endif
#	ifdef glStopInstrumentsSGIX
	_glStopInstrumentsSGIX = (glStopInstrumentsSGIXFunc)glGetFunction("glStopInstrumentsSGIX");
#	endif
#	ifdef glFrameZoomSGIX
	_glFrameZoomSGIX = (glFrameZoomSGIXFunc)glGetFunction("glFrameZoomSGIX");
#	endif
#	ifdef glTagSampleBufferSGIX
	_glTagSampleBufferSGIX = (glTagSampleBufferSGIXFunc)glGetFunction("glTagSampleBufferSGIX");
#	endif
#	ifdef glDeformationMap3dSGIX
	_glDeformationMap3dSGIX = (glDeformationMap3dSGIXFunc)glGetFunction("glDeformationMap3dSGIX");
#	endif
#	ifdef glDeformationMap3fSGIX
	_glDeformationMap3fSGIX = (glDeformationMap3fSGIXFunc)glGetFunction("glDeformationMap3fSGIX");
#	endif
#	ifdef glDeformSGIX
	_glDeformSGIX = (glDeformSGIXFunc)glGetFunction("glDeformSGIX");
#	endif
#	ifdef glLoadIdentityDeformationMapSGIX
	_glLoadIdentityDeformationMapSGIX = (glLoadIdentityDeformationMapSGIXFunc)glGetFunction("glLoadIdentityDeformationMapSGIX");
#	endif
#	ifdef glReferencePlaneSGIX
	_glReferencePlaneSGIX = (glReferencePlaneSGIXFunc)glGetFunction("glReferencePlaneSGIX");
#	endif
#	ifdef glFlushRasterSGIX
	_glFlushRasterSGIX = (glFlushRasterSGIXFunc)glGetFunction("glFlushRasterSGIX");
#	endif
#	ifdef glFogFuncSGIS
	_glFogFuncSGIS = (glFogFuncSGISFunc)glGetFunction("glFogFuncSGIS");
#	endif
#	ifdef glGetFogFuncSGIS
	_glGetFogFuncSGIS = (glGetFogFuncSGISFunc)glGetFunction("glGetFogFuncSGIS");
#	endif
#	ifdef glImageTransformParameteriHP
	_glImageTransformParameteriHP = (glImageTransformParameteriHPFunc)glGetFunction("glImageTransformParameteriHP");
#	endif
#	ifdef glImageTransformParameterfHP
	_glImageTransformParameterfHP = (glImageTransformParameterfHPFunc)glGetFunction("glImageTransformParameterfHP");
#	endif
#	ifdef glImageTransformParameterivHP
	_glImageTransformParameterivHP = (glImageTransformParameterivHPFunc)glGetFunction("glImageTransformParameterivHP");
#	endif
#	ifdef glImageTransformParameterfvHP
	_glImageTransformParameterfvHP = (glImageTransformParameterfvHPFunc)glGetFunction("glImageTransformParameterfvHP");
#	endif
#	ifdef glGetImageTransformParameterivHP
	_glGetImageTransformParameterivHP = (glGetImageTransformParameterivHPFunc)glGetFunction("glGetImageTransformParameterivHP");
#	endif
#	ifdef glGetImageTransformParameterfvHP
	_glGetImageTransformParameterfvHP = (glGetImageTransformParameterfvHPFunc)glGetFunction("glGetImageTransformParameterfvHP");
#	endif
#	ifdef glColorSubTableEXT
	_glColorSubTableEXT = (glColorSubTableEXTFunc)glGetFunction("glColorSubTableEXT");
#	endif
#	ifdef glCopyColorSubTableEXT
	_glCopyColorSubTableEXT = (glCopyColorSubTableEXTFunc)glGetFunction("glCopyColorSubTableEXT");
#	endif
#	ifdef glHintPGI
	_glHintPGI = (glHintPGIFunc)glGetFunction("glHintPGI");
#	endif
#	ifdef glColorTableEXT
	_glColorTableEXT = (glColorTableEXTFunc)glGetFunction("glColorTableEXT");
#	endif
#	ifdef glGetColorTableEXT
	_glGetColorTableEXT = (glGetColorTableEXTFunc)glGetFunction("glGetColorTableEXT");
#	endif
#	ifdef glGetColorTableParameterivEXT
	_glGetColorTableParameterivEXT = (glGetColorTableParameterivEXTFunc)glGetFunction("glGetColorTableParameterivEXT");
#	endif
#	ifdef glGetColorTableParameterfvEXT
	_glGetColorTableParameterfvEXT = (glGetColorTableParameterfvEXTFunc)glGetFunction("glGetColorTableParameterfvEXT");
#	endif
#	ifdef glGetListParameterfvSGIX
	_glGetListParameterfvSGIX = (glGetListParameterfvSGIXFunc)glGetFunction("glGetListParameterfvSGIX");
#	endif
#	ifdef glGetListParameterivSGIX
	_glGetListParameterivSGIX = (glGetListParameterivSGIXFunc)glGetFunction("glGetListParameterivSGIX");
#	endif
#	ifdef glListParameterfSGIX
	_glListParameterfSGIX = (glListParameterfSGIXFunc)glGetFunction("glListParameterfSGIX");
#	endif
#	ifdef glListParameterfvSGIX
	_glListParameterfvSGIX = (glListParameterfvSGIXFunc)glGetFunction("glListParameterfvSGIX");
#	endif
#	ifdef glListParameteriSGIX
	_glListParameteriSGIX = (glListParameteriSGIXFunc)glGetFunction("glListParameteriSGIX");
#	endif
#	ifdef glListParameterivSGIX
	_glListParameterivSGIX = (glListParameterivSGIXFunc)glGetFunction("glListParameterivSGIX");
#	endif
#	ifdef glIndexMaterialEXT
	_glIndexMaterialEXT = (glIndexMaterialEXTFunc)glGetFunction("glIndexMaterialEXT");
#	endif
#	ifdef glIndexFuncEXT
	_glIndexFuncEXT = (glIndexFuncEXTFunc)glGetFunction("glIndexFuncEXT");
#	endif
#	ifdef glLockArraysEXT
	_glLockArraysEXT = (glLockArraysEXTFunc)glGetFunction("glLockArraysEXT");
#	endif
#	ifdef glUnlockArraysEXT
	_glUnlockArraysEXT = (glUnlockArraysEXTFunc)glGetFunction("glUnlockArraysEXT");
#	endif
#	ifdef glCullParameterdvEXT
	_glCullParameterdvEXT = (glCullParameterdvEXTFunc)glGetFunction("glCullParameterdvEXT");
#	endif
#	ifdef glCullParameterfvEXT
	_glCullParameterfvEXT = (glCullParameterfvEXTFunc)glGetFunction("glCullParameterfvEXT");
#	endif
#	ifdef glFragmentColorMaterialSGIX
	_glFragmentColorMaterialSGIX = (glFragmentColorMaterialSGIXFunc)glGetFunction("glFragmentColorMaterialSGIX");
#	endif
#	ifdef glFragmentLightfSGIX
	_glFragmentLightfSGIX = (glFragmentLightfSGIXFunc)glGetFunction("glFragmentLightfSGIX");
#	endif
#	ifdef glFragmentLightfvSGIX
	_glFragmentLightfvSGIX = (glFragmentLightfvSGIXFunc)glGetFunction("glFragmentLightfvSGIX");
#	endif
#	ifdef glFragmentLightiSGIX
	_glFragmentLightiSGIX = (glFragmentLightiSGIXFunc)glGetFunction("glFragmentLightiSGIX");
#	endif
#	ifdef glFragmentLightivSGIX
	_glFragmentLightivSGIX = (glFragmentLightivSGIXFunc)glGetFunction("glFragmentLightivSGIX");
#	endif
#	ifdef glFragmentLightModelfSGIX
	_glFragmentLightModelfSGIX = (glFragmentLightModelfSGIXFunc)glGetFunction("glFragmentLightModelfSGIX");
#	endif
#	ifdef glFragmentLightModelfvSGIX
	_glFragmentLightModelfvSGIX = (glFragmentLightModelfvSGIXFunc)glGetFunction("glFragmentLightModelfvSGIX");
#	endif
#	ifdef glFragmentLightModeliSGIX
	_glFragmentLightModeliSGIX = (glFragmentLightModeliSGIXFunc)glGetFunction("glFragmentLightModeliSGIX");
#	endif
#	ifdef glFragmentLightModelivSGIX
	_glFragmentLightModelivSGIX = (glFragmentLightModelivSGIXFunc)glGetFunction("glFragmentLightModelivSGIX");
#	endif
#	ifdef glFragmentMaterialfSGIX
	_glFragmentMaterialfSGIX = (glFragmentMaterialfSGIXFunc)glGetFunction("glFragmentMaterialfSGIX");
#	endif
#	ifdef glFragmentMaterialfvSGIX
	_glFragmentMaterialfvSGIX = (glFragmentMaterialfvSGIXFunc)glGetFunction("glFragmentMaterialfvSGIX");
#	endif
#	ifdef glFragmentMaterialiSGIX
	_glFragmentMaterialiSGIX = (glFragmentMaterialiSGIXFunc)glGetFunction("glFragmentMaterialiSGIX");
#	endif
#	ifdef glFragmentMaterialivSGIX
	_glFragmentMaterialivSGIX = (glFragmentMaterialivSGIXFunc)glGetFunction("glFragmentMaterialivSGIX");
#	endif
#	ifdef glGetFragmentLightfvSGIX
	_glGetFragmentLightfvSGIX = (glGetFragmentLightfvSGIXFunc)glGetFunction("glGetFragmentLightfvSGIX");
#	endif
#	ifdef glGetFragmentLightivSGIX
	_glGetFragmentLightivSGIX = (glGetFragmentLightivSGIXFunc)glGetFunction("glGetFragmentLightivSGIX");
#	endif
#	ifdef glGetFragmentMaterialfvSGIX
	_glGetFragmentMaterialfvSGIX = (glGetFragmentMaterialfvSGIXFunc)glGetFunction("glGetFragmentMaterialfvSGIX");
#	endif
#	ifdef glGetFragmentMaterialivSGIX
	_glGetFragmentMaterialivSGIX = (glGetFragmentMaterialivSGIXFunc)glGetFunction("glGetFragmentMaterialivSGIX");
#	endif
#	ifdef glLightEnviSGIX
	_glLightEnviSGIX = (glLightEnviSGIXFunc)glGetFunction("glLightEnviSGIX");
#	endif
#	ifdef glDrawRangeElementsEXT
	_glDrawRangeElementsEXT = (glDrawRangeElementsEXTFunc)glGetFunction("glDrawRangeElementsEXT");
#	endif
#	ifdef glApplyTextureEXT
	_glApplyTextureEXT = (glApplyTextureEXTFunc)glGetFunction("glApplyTextureEXT");
#	endif
#	ifdef glTextureLightEXT
	_glTextureLightEXT = (glTextureLightEXTFunc)glGetFunction("glTextureLightEXT");
#	endif
#	ifdef glTextureMaterialEXT
	_glTextureMaterialEXT = (glTextureMaterialEXTFunc)glGetFunction("glTextureMaterialEXT");
#	endif
#	ifdef glAsyncMarkerSGIX
	_glAsyncMarkerSGIX = (glAsyncMarkerSGIXFunc)glGetFunction("glAsyncMarkerSGIX");
#	endif
#	ifdef glFinishAsyncSGIX
	_glFinishAsyncSGIX = (glFinishAsyncSGIXFunc)glGetFunction("glFinishAsyncSGIX");
#	endif
#	ifdef glPollAsyncSGIX
	_glPollAsyncSGIX = (glPollAsyncSGIXFunc)glGetFunction("glPollAsyncSGIX");
#	endif
#	ifdef glGenAsyncMarkersSGIX
	_glGenAsyncMarkersSGIX = (glGenAsyncMarkersSGIXFunc)glGetFunction("glGenAsyncMarkersSGIX");
#	endif
#	ifdef glDeleteAsyncMarkersSGIX
	_glDeleteAsyncMarkersSGIX = (glDeleteAsyncMarkersSGIXFunc)glGetFunction("glDeleteAsyncMarkersSGIX");
#	endif
#	ifdef glIsAsyncMarkerSGIX
	_glIsAsyncMarkerSGIX = (glIsAsyncMarkerSGIXFunc)glGetFunction("glIsAsyncMarkerSGIX");
#	endif
#	ifdef glVertexPointervINTEL
	_glVertexPointervINTEL = (glVertexPointervINTELFunc)glGetFunction("glVertexPointervINTEL");
#	endif
#	ifdef glNormalPointervINTEL
	_glNormalPointervINTEL = (glNormalPointervINTELFunc)glGetFunction("glNormalPointervINTEL");
#	endif
#	ifdef glColorPointervINTEL
	_glColorPointervINTEL = (glColorPointervINTELFunc)glGetFunction("glColorPointervINTEL");
#	endif
#	ifdef glTexCoordPointervINTEL
	_glTexCoordPointervINTEL = (glTexCoordPointervINTELFunc)glGetFunction("glTexCoordPointervINTEL");
#	endif
#	ifdef glPixelTransformParameteriEXT
	_glPixelTransformParameteriEXT = (glPixelTransformParameteriEXTFunc)glGetFunction("glPixelTransformParameteriEXT");
#	endif
#	ifdef glPixelTransformParameterfEXT
	_glPixelTransformParameterfEXT = (glPixelTransformParameterfEXTFunc)glGetFunction("glPixelTransformParameterfEXT");
#	endif
#	ifdef glPixelTransformParameterivEXT
	_glPixelTransformParameterivEXT = (glPixelTransformParameterivEXTFunc)glGetFunction("glPixelTransformParameterivEXT");
#	endif
#	ifdef glPixelTransformParameterfvEXT
	_glPixelTransformParameterfvEXT = (glPixelTransformParameterfvEXTFunc)glGetFunction("glPixelTransformParameterfvEXT");
#	endif
#	ifdef glGetPixelTransformParameterivEXT
	_glGetPixelTransformParameterivEXT = (glGetPixelTransformParameterivEXTFunc)glGetFunction("glGetPixelTransformParameterivEXT");
#	endif
#	ifdef glGetPixelTransformParameterfvEXT
	_glGetPixelTransformParameterfvEXT = (glGetPixelTransformParameterfvEXTFunc)glGetFunction("glGetPixelTransformParameterfvEXT");
#	endif
#	ifdef glSecondaryColor3bEXT
	_glSecondaryColor3bEXT = (glSecondaryColor3bEXTFunc)glGetFunction("glSecondaryColor3bEXT");
#	endif
#	ifdef glSecondaryColor3bvEXT
	_glSecondaryColor3bvEXT = (glSecondaryColor3bvEXTFunc)glGetFunction("glSecondaryColor3bvEXT");
#	endif
#	ifdef glSecondaryColor3dEXT
	_glSecondaryColor3dEXT = (glSecondaryColor3dEXTFunc)glGetFunction("glSecondaryColor3dEXT");
#	endif
#	ifdef glSecondaryColor3dvEXT
	_glSecondaryColor3dvEXT = (glSecondaryColor3dvEXTFunc)glGetFunction("glSecondaryColor3dvEXT");
#	endif
#	ifdef glSecondaryColor3fEXT
	_glSecondaryColor3fEXT = (glSecondaryColor3fEXTFunc)glGetFunction("glSecondaryColor3fEXT");
#	endif
#	ifdef glSecondaryColor3fvEXT
	_glSecondaryColor3fvEXT = (glSecondaryColor3fvEXTFunc)glGetFunction("glSecondaryColor3fvEXT");
#	endif
#	ifdef glSecondaryColor3iEXT
	_glSecondaryColor3iEXT = (glSecondaryColor3iEXTFunc)glGetFunction("glSecondaryColor3iEXT");
#	endif
#	ifdef glSecondaryColor3ivEXT
	_glSecondaryColor3ivEXT = (glSecondaryColor3ivEXTFunc)glGetFunction("glSecondaryColor3ivEXT");
#	endif
#	ifdef glSecondaryColor3sEXT
	_glSecondaryColor3sEXT = (glSecondaryColor3sEXTFunc)glGetFunction("glSecondaryColor3sEXT");
#	endif
#	ifdef glSecondaryColor3svEXT
	_glSecondaryColor3svEXT = (glSecondaryColor3svEXTFunc)glGetFunction("glSecondaryColor3svEXT");
#	endif
#	ifdef glSecondaryColor3ubEXT
	_glSecondaryColor3ubEXT = (glSecondaryColor3ubEXTFunc)glGetFunction("glSecondaryColor3ubEXT");
#	endif
#	ifdef glSecondaryColor3ubvEXT
	_glSecondaryColor3ubvEXT = (glSecondaryColor3ubvEXTFunc)glGetFunction("glSecondaryColor3ubvEXT");
#	endif
#	ifdef glSecondaryColor3uiEXT
	_glSecondaryColor3uiEXT = (glSecondaryColor3uiEXTFunc)glGetFunction("glSecondaryColor3uiEXT");
#	endif
#	ifdef glSecondaryColor3uivEXT
	_glSecondaryColor3uivEXT = (glSecondaryColor3uivEXTFunc)glGetFunction("glSecondaryColor3uivEXT");
#	endif
#	ifdef glSecondaryColor3usEXT
	_glSecondaryColor3usEXT = (glSecondaryColor3usEXTFunc)glGetFunction("glSecondaryColor3usEXT");
#	endif
#	ifdef glSecondaryColor3usvEXT
	_glSecondaryColor3usvEXT = (glSecondaryColor3usvEXTFunc)glGetFunction("glSecondaryColor3usvEXT");
#	endif
#	ifdef glSecondaryColorPointerEXT
	_glSecondaryColorPointerEXT = (glSecondaryColorPointerEXTFunc)glGetFunction("glSecondaryColorPointerEXT");
#	endif
#	ifdef glTextureNormalEXT
	_glTextureNormalEXT = (glTextureNormalEXTFunc)glGetFunction("glTextureNormalEXT");
#	endif
#	ifdef glMultiDrawArraysEXT
	_glMultiDrawArraysEXT = (glMultiDrawArraysEXTFunc)glGetFunction("glMultiDrawArraysEXT");
#	endif
#	ifdef glMultiDrawElementsEXT
	_glMultiDrawElementsEXT = (glMultiDrawElementsEXTFunc)glGetFunction("glMultiDrawElementsEXT");
#	endif
#	ifdef glFogCoordfEXT
	_glFogCoordfEXT = (glFogCoordfEXTFunc)glGetFunction("glFogCoordfEXT");
#	endif
#	ifdef glFogCoordfvEXT
	_glFogCoordfvEXT = (glFogCoordfvEXTFunc)glGetFunction("glFogCoordfvEXT");
#	endif
#	ifdef glFogCoorddEXT
	_glFogCoorddEXT = (glFogCoorddEXTFunc)glGetFunction("glFogCoorddEXT");
#	endif
#	ifdef glFogCoorddvEXT
	_glFogCoorddvEXT = (glFogCoorddvEXTFunc)glGetFunction("glFogCoorddvEXT");
#	endif
#	ifdef glFogCoordPointerEXT
	_glFogCoordPointerEXT = (glFogCoordPointerEXTFunc)glGetFunction("glFogCoordPointerEXT");
#	endif
#	ifdef glTangent3bEXT
	_glTangent3bEXT = (glTangent3bEXTFunc)glGetFunction("glTangent3bEXT");
#	endif
#	ifdef glTangent3bvEXT
	_glTangent3bvEXT = (glTangent3bvEXTFunc)glGetFunction("glTangent3bvEXT");
#	endif
#	ifdef glTangent3dEXT
	_glTangent3dEXT = (glTangent3dEXTFunc)glGetFunction("glTangent3dEXT");
#	endif
#	ifdef glTangent3dvEXT
	_glTangent3dvEXT = (glTangent3dvEXTFunc)glGetFunction("glTangent3dvEXT");
#	endif
#	ifdef glTangent3fEXT
	_glTangent3fEXT = (glTangent3fEXTFunc)glGetFunction("glTangent3fEXT");
#	endif
#	ifdef glTangent3fvEXT
	_glTangent3fvEXT = (glTangent3fvEXTFunc)glGetFunction("glTangent3fvEXT");
#	endif
#	ifdef glTangent3iEXT
	_glTangent3iEXT = (glTangent3iEXTFunc)glGetFunction("glTangent3iEXT");
#	endif
#	ifdef glTangent3ivEXT
	_glTangent3ivEXT = (glTangent3ivEXTFunc)glGetFunction("glTangent3ivEXT");
#	endif
#	ifdef glTangent3sEXT
	_glTangent3sEXT = (glTangent3sEXTFunc)glGetFunction("glTangent3sEXT");
#	endif
#	ifdef glTangent3svEXT
	_glTangent3svEXT = (glTangent3svEXTFunc)glGetFunction("glTangent3svEXT");
#	endif
#	ifdef glBinormal3bEXT
	_glBinormal3bEXT = (glBinormal3bEXTFunc)glGetFunction("glBinormal3bEXT");
#	endif
#	ifdef glBinormal3bvEXT
	_glBinormal3bvEXT = (glBinormal3bvEXTFunc)glGetFunction("glBinormal3bvEXT");
#	endif
#	ifdef glBinormal3dEXT
	_glBinormal3dEXT = (glBinormal3dEXTFunc)glGetFunction("glBinormal3dEXT");
#	endif
#	ifdef glBinormal3dvEXT
	_glBinormal3dvEXT = (glBinormal3dvEXTFunc)glGetFunction("glBinormal3dvEXT");
#	endif
#	ifdef glBinormal3fEXT
	_glBinormal3fEXT = (glBinormal3fEXTFunc)glGetFunction("glBinormal3fEXT");
#	endif
#	ifdef glBinormal3fvEXT
	_glBinormal3fvEXT = (glBinormal3fvEXTFunc)glGetFunction("glBinormal3fvEXT");
#	endif
#	ifdef glBinormal3iEXT
	_glBinormal3iEXT = (glBinormal3iEXTFunc)glGetFunction("glBinormal3iEXT");
#	endif
#	ifdef glBinormal3ivEXT
	_glBinormal3ivEXT = (glBinormal3ivEXTFunc)glGetFunction("glBinormal3ivEXT");
#	endif
#	ifdef glBinormal3sEXT
	_glBinormal3sEXT = (glBinormal3sEXTFunc)glGetFunction("glBinormal3sEXT");
#	endif
#	ifdef glBinormal3svEXT
	_glBinormal3svEXT = (glBinormal3svEXTFunc)glGetFunction("glBinormal3svEXT");
#	endif
#	ifdef glTangentPointerEXT
	_glTangentPointerEXT = (glTangentPointerEXTFunc)glGetFunction("glTangentPointerEXT");
#	endif
#	ifdef glBinormalPointerEXT
	_glBinormalPointerEXT = (glBinormalPointerEXTFunc)glGetFunction("glBinormalPointerEXT");
#	endif
#	ifdef glFinishTextureSUNX
	_glFinishTextureSUNX = (glFinishTextureSUNXFunc)glGetFunction("glFinishTextureSUNX");
#	endif
#	ifdef glGlobalAlphaFactorbSUN
	_glGlobalAlphaFactorbSUN = (glGlobalAlphaFactorbSUNFunc)glGetFunction("glGlobalAlphaFactorbSUN");
#	endif
#	ifdef glGlobalAlphaFactorsSUN
	_glGlobalAlphaFactorsSUN = (glGlobalAlphaFactorsSUNFunc)glGetFunction("glGlobalAlphaFactorsSUN");
#	endif
#	ifdef glGlobalAlphaFactoriSUN
	_glGlobalAlphaFactoriSUN = (glGlobalAlphaFactoriSUNFunc)glGetFunction("glGlobalAlphaFactoriSUN");
#	endif
#	ifdef glGlobalAlphaFactorfSUN
	_glGlobalAlphaFactorfSUN = (glGlobalAlphaFactorfSUNFunc)glGetFunction("glGlobalAlphaFactorfSUN");
#	endif
#	ifdef glGlobalAlphaFactordSUN
	_glGlobalAlphaFactordSUN = (glGlobalAlphaFactordSUNFunc)glGetFunction("glGlobalAlphaFactordSUN");
#	endif
#	ifdef glGlobalAlphaFactorubSUN
	_glGlobalAlphaFactorubSUN = (glGlobalAlphaFactorubSUNFunc)glGetFunction("glGlobalAlphaFactorubSUN");
#	endif
#	ifdef glGlobalAlphaFactorusSUN
	_glGlobalAlphaFactorusSUN = (glGlobalAlphaFactorusSUNFunc)glGetFunction("glGlobalAlphaFactorusSUN");
#	endif
#	ifdef glGlobalAlphaFactoruiSUN
	_glGlobalAlphaFactoruiSUN = (glGlobalAlphaFactoruiSUNFunc)glGetFunction("glGlobalAlphaFactoruiSUN");
#	endif
#	ifdef glReplacementCodeuiSUN
	_glReplacementCodeuiSUN = (glReplacementCodeuiSUNFunc)glGetFunction("glReplacementCodeuiSUN");
#	endif
#	ifdef glReplacementCodeusSUN
	_glReplacementCodeusSUN = (glReplacementCodeusSUNFunc)glGetFunction("glReplacementCodeusSUN");
#	endif
#	ifdef glReplacementCodeubSUN
	_glReplacementCodeubSUN = (glReplacementCodeubSUNFunc)glGetFunction("glReplacementCodeubSUN");
#	endif
#	ifdef glReplacementCodeuivSUN
	_glReplacementCodeuivSUN = (glReplacementCodeuivSUNFunc)glGetFunction("glReplacementCodeuivSUN");
#	endif
#	ifdef glReplacementCodeusvSUN
	_glReplacementCodeusvSUN = (glReplacementCodeusvSUNFunc)glGetFunction("glReplacementCodeusvSUN");
#	endif
#	ifdef glReplacementCodeubvSUN
	_glReplacementCodeubvSUN = (glReplacementCodeubvSUNFunc)glGetFunction("glReplacementCodeubvSUN");
#	endif
#	ifdef glReplacementCodePointerSUN
	_glReplacementCodePointerSUN = (glReplacementCodePointerSUNFunc)glGetFunction("glReplacementCodePointerSUN");
#	endif
#	ifdef glColor4ubVertex2fSUN
	_glColor4ubVertex2fSUN = (glColor4ubVertex2fSUNFunc)glGetFunction("glColor4ubVertex2fSUN");
#	endif
#	ifdef glColor4ubVertex2fvSUN
	_glColor4ubVertex2fvSUN = (glColor4ubVertex2fvSUNFunc)glGetFunction("glColor4ubVertex2fvSUN");
#	endif
#	ifdef glColor4ubVertex3fSUN
	_glColor4ubVertex3fSUN = (glColor4ubVertex3fSUNFunc)glGetFunction("glColor4ubVertex3fSUN");
#	endif
#	ifdef glColor4ubVertex3fvSUN
	_glColor4ubVertex3fvSUN = (glColor4ubVertex3fvSUNFunc)glGetFunction("glColor4ubVertex3fvSUN");
#	endif
#	ifdef glColor3fVertex3fSUN
	_glColor3fVertex3fSUN = (glColor3fVertex3fSUNFunc)glGetFunction("glColor3fVertex3fSUN");
#	endif
#	ifdef glColor3fVertex3fvSUN
	_glColor3fVertex3fvSUN = (glColor3fVertex3fvSUNFunc)glGetFunction("glColor3fVertex3fvSUN");
#	endif
#	ifdef glNormal3fVertex3fSUN
	_glNormal3fVertex3fSUN = (glNormal3fVertex3fSUNFunc)glGetFunction("glNormal3fVertex3fSUN");
#	endif
#	ifdef glNormal3fVertex3fvSUN
	_glNormal3fVertex3fvSUN = (glNormal3fVertex3fvSUNFunc)glGetFunction("glNormal3fVertex3fvSUN");
#	endif
#	ifdef glColor4fNormal3fVertex3fSUN
	_glColor4fNormal3fVertex3fSUN = (glColor4fNormal3fVertex3fSUNFunc)glGetFunction("glColor4fNormal3fVertex3fSUN");
#	endif
#	ifdef glColor4fNormal3fVertex3fvSUN
	_glColor4fNormal3fVertex3fvSUN = (glColor4fNormal3fVertex3fvSUNFunc)glGetFunction("glColor4fNormal3fVertex3fvSUN");
#	endif
#	ifdef glTexCoord2fVertex3fSUN
	_glTexCoord2fVertex3fSUN = (glTexCoord2fVertex3fSUNFunc)glGetFunction("glTexCoord2fVertex3fSUN");
#	endif
#	ifdef glTexCoord2fVertex3fvSUN
	_glTexCoord2fVertex3fvSUN = (glTexCoord2fVertex3fvSUNFunc)glGetFunction("glTexCoord2fVertex3fvSUN");
#	endif
#	ifdef glTexCoord4fVertex4fSUN
	_glTexCoord4fVertex4fSUN = (glTexCoord4fVertex4fSUNFunc)glGetFunction("glTexCoord4fVertex4fSUN");
#	endif
#	ifdef glTexCoord4fVertex4fvSUN
	_glTexCoord4fVertex4fvSUN = (glTexCoord4fVertex4fvSUNFunc)glGetFunction("glTexCoord4fVertex4fvSUN");
#	endif
#	ifdef glTexCoord2fColor4ubVertex3fSUN
	_glTexCoord2fColor4ubVertex3fSUN = (glTexCoord2fColor4ubVertex3fSUNFunc)glGetFunction("glTexCoord2fColor4ubVertex3fSUN");
#	endif
#	ifdef glTexCoord2fColor4ubVertex3fvSUN
	_glTexCoord2fColor4ubVertex3fvSUN = (glTexCoord2fColor4ubVertex3fvSUNFunc)glGetFunction("glTexCoord2fColor4ubVertex3fvSUN");
#	endif
#	ifdef glTexCoord2fColor3fVertex3fSUN
	_glTexCoord2fColor3fVertex3fSUN = (glTexCoord2fColor3fVertex3fSUNFunc)glGetFunction("glTexCoord2fColor3fVertex3fSUN");
#	endif
#	ifdef glTexCoord2fColor3fVertex3fvSUN
	_glTexCoord2fColor3fVertex3fvSUN = (glTexCoord2fColor3fVertex3fvSUNFunc)glGetFunction("glTexCoord2fColor3fVertex3fvSUN");
#	endif
#	ifdef glTexCoord2fNormal3fVertex3fSUN
	_glTexCoord2fNormal3fVertex3fSUN = (glTexCoord2fNormal3fVertex3fSUNFunc)glGetFunction("glTexCoord2fNormal3fVertex3fSUN");
#	endif
#	ifdef glTexCoord2fNormal3fVertex3fvSUN
	_glTexCoord2fNormal3fVertex3fvSUN = (glTexCoord2fNormal3fVertex3fvSUNFunc)glGetFunction("glTexCoord2fNormal3fVertex3fvSUN");
#	endif
#	ifdef glTexCoord2fColor4fNormal3fVertex3fSUN
	_glTexCoord2fColor4fNormal3fVertex3fSUN = (glTexCoord2fColor4fNormal3fVertex3fSUNFunc)glGetFunction("glTexCoord2fColor4fNormal3fVertex3fSUN");
#	endif
#	ifdef glTexCoord2fColor4fNormal3fVertex3fvSUN
	_glTexCoord2fColor4fNormal3fVertex3fvSUN = (glTexCoord2fColor4fNormal3fVertex3fvSUNFunc)glGetFunction("glTexCoord2fColor4fNormal3fVertex3fvSUN");
#	endif
#	ifdef glTexCoord4fColor4fNormal3fVertex4fSUN
	_glTexCoord4fColor4fNormal3fVertex4fSUN = (glTexCoord4fColor4fNormal3fVertex4fSUNFunc)glGetFunction("glTexCoord4fColor4fNormal3fVertex4fSUN");
#	endif
#	ifdef glTexCoord4fColor4fNormal3fVertex4fvSUN
	_glTexCoord4fColor4fNormal3fVertex4fvSUN = (glTexCoord4fColor4fNormal3fVertex4fvSUNFunc)glGetFunction("glTexCoord4fColor4fNormal3fVertex4fvSUN");
#	endif
#	ifdef glReplacementCodeuiVertex3fSUN
	_glReplacementCodeuiVertex3fSUN = (glReplacementCodeuiVertex3fSUNFunc)glGetFunction("glReplacementCodeuiVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiVertex3fvSUN
	_glReplacementCodeuiVertex3fvSUN = (glReplacementCodeuiVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiVertex3fvSUN");
#	endif
#	ifdef glReplacementCodeuiColor4ubVertex3fSUN
	_glReplacementCodeuiColor4ubVertex3fSUN = (glReplacementCodeuiColor4ubVertex3fSUNFunc)glGetFunction("glReplacementCodeuiColor4ubVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiColor4ubVertex3fvSUN
	_glReplacementCodeuiColor4ubVertex3fvSUN = (glReplacementCodeuiColor4ubVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiColor4ubVertex3fvSUN");
#	endif
#	ifdef glReplacementCodeuiColor3fVertex3fSUN
	_glReplacementCodeuiColor3fVertex3fSUN = (glReplacementCodeuiColor3fVertex3fSUNFunc)glGetFunction("glReplacementCodeuiColor3fVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiColor3fVertex3fvSUN
	_glReplacementCodeuiColor3fVertex3fvSUN = (glReplacementCodeuiColor3fVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiColor3fVertex3fvSUN");
#	endif
#	ifdef glReplacementCodeuiNormal3fVertex3fSUN
	_glReplacementCodeuiNormal3fVertex3fSUN = (glReplacementCodeuiNormal3fVertex3fSUNFunc)glGetFunction("glReplacementCodeuiNormal3fVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiNormal3fVertex3fvSUN
	_glReplacementCodeuiNormal3fVertex3fvSUN = (glReplacementCodeuiNormal3fVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiNormal3fVertex3fvSUN");
#	endif
#	ifdef glReplacementCodeuiColor4fNormal3fVertex3fSUN
	_glReplacementCodeuiColor4fNormal3fVertex3fSUN = (glReplacementCodeuiColor4fNormal3fVertex3fSUNFunc)glGetFunction("glReplacementCodeuiColor4fNormal3fVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiColor4fNormal3fVertex3fvSUN
	_glReplacementCodeuiColor4fNormal3fVertex3fvSUN = (glReplacementCodeuiColor4fNormal3fVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiColor4fNormal3fVertex3fvSUN");
#	endif
#	ifdef glReplacementCodeuiTexCoord2fVertex3fSUN
	_glReplacementCodeuiTexCoord2fVertex3fSUN = (glReplacementCodeuiTexCoord2fVertex3fSUNFunc)glGetFunction("glReplacementCodeuiTexCoord2fVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiTexCoord2fVertex3fvSUN
	_glReplacementCodeuiTexCoord2fVertex3fvSUN = (glReplacementCodeuiTexCoord2fVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiTexCoord2fVertex3fvSUN");
#	endif
#	ifdef glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN
	_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN = (glReplacementCodeuiTexCoord2fNormal3fVertex3fSUNFunc)glGetFunction("glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN
	_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN = (glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN");
#	endif
#	ifdef glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN
	_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN = (glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUNFunc)glGetFunction("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN");
#	endif
#	ifdef glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN
	_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN = (glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUNFunc)glGetFunction("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN");
#	endif
#	ifdef glBlendFuncSeparateEXT
	_glBlendFuncSeparateEXT = (glBlendFuncSeparateEXTFunc)glGetFunction("glBlendFuncSeparateEXT");
#	endif
#	ifdef glBlendFuncSeparateINGR
	_glBlendFuncSeparateINGR = (glBlendFuncSeparateINGRFunc)glGetFunction("glBlendFuncSeparateINGR");
#	endif
#	ifdef glVertexWeightfEXT
	_glVertexWeightfEXT = (glVertexWeightfEXTFunc)glGetFunction("glVertexWeightfEXT");
#	endif
#	ifdef glVertexWeightfvEXT
	_glVertexWeightfvEXT = (glVertexWeightfvEXTFunc)glGetFunction("glVertexWeightfvEXT");
#	endif
#	ifdef glVertexWeightPointerEXT
	_glVertexWeightPointerEXT = (glVertexWeightPointerEXTFunc)glGetFunction("glVertexWeightPointerEXT");
#	endif
#	ifdef glFlushVertexArrayRangeNV
	_glFlushVertexArrayRangeNV = (glFlushVertexArrayRangeNVFunc)glGetFunction("glFlushVertexArrayRangeNV");
#	endif
#	ifdef glVertexArrayRangeNV
	_glVertexArrayRangeNV = (glVertexArrayRangeNVFunc)glGetFunction("glVertexArrayRangeNV");
#	endif
#	ifdef glCombinerParameterfvNV
	_glCombinerParameterfvNV = (glCombinerParameterfvNVFunc)glGetFunction("glCombinerParameterfvNV");
#	endif
#	ifdef glCombinerParameterfNV
	_glCombinerParameterfNV = (glCombinerParameterfNVFunc)glGetFunction("glCombinerParameterfNV");
#	endif
#	ifdef glCombinerParameterivNV
	_glCombinerParameterivNV = (glCombinerParameterivNVFunc)glGetFunction("glCombinerParameterivNV");
#	endif
#	ifdef glCombinerParameteriNV
	_glCombinerParameteriNV = (glCombinerParameteriNVFunc)glGetFunction("glCombinerParameteriNV");
#	endif
#	ifdef glCombinerInputNV
	_glCombinerInputNV = (glCombinerInputNVFunc)glGetFunction("glCombinerInputNV");
#	endif
#	ifdef glCombinerOutputNV
	_glCombinerOutputNV = (glCombinerOutputNVFunc)glGetFunction("glCombinerOutputNV");
#	endif
#	ifdef glFinalCombinerInputNV
	_glFinalCombinerInputNV = (glFinalCombinerInputNVFunc)glGetFunction("glFinalCombinerInputNV");
#	endif
#	ifdef glGetCombinerInputParameterfvNV
	_glGetCombinerInputParameterfvNV = (glGetCombinerInputParameterfvNVFunc)glGetFunction("glGetCombinerInputParameterfvNV");
#	endif
#	ifdef glGetCombinerInputParameterivNV
	_glGetCombinerInputParameterivNV = (glGetCombinerInputParameterivNVFunc)glGetFunction("glGetCombinerInputParameterivNV");
#	endif
#	ifdef glGetCombinerOutputParameterfvNV
	_glGetCombinerOutputParameterfvNV = (glGetCombinerOutputParameterfvNVFunc)glGetFunction("glGetCombinerOutputParameterfvNV");
#	endif
#	ifdef glGetCombinerOutputParameterivNV
	_glGetCombinerOutputParameterivNV = (glGetCombinerOutputParameterivNVFunc)glGetFunction("glGetCombinerOutputParameterivNV");
#	endif
#	ifdef glGetFinalCombinerInputParameterfvNV
	_glGetFinalCombinerInputParameterfvNV = (glGetFinalCombinerInputParameterfvNVFunc)glGetFunction("glGetFinalCombinerInputParameterfvNV");
#	endif
#	ifdef glGetFinalCombinerInputParameterivNV
	_glGetFinalCombinerInputParameterivNV = (glGetFinalCombinerInputParameterivNVFunc)glGetFunction("glGetFinalCombinerInputParameterivNV");
#	endif
#	ifdef glResizeBuffersMESA
	_glResizeBuffersMESA = (glResizeBuffersMESAFunc)glGetFunction("glResizeBuffersMESA");
#	endif
#	ifdef glWindowPos2dMESA
	_glWindowPos2dMESA = (glWindowPos2dMESAFunc)glGetFunction("glWindowPos2dMESA");
#	endif
#	ifdef glWindowPos2dvMESA
	_glWindowPos2dvMESA = (glWindowPos2dvMESAFunc)glGetFunction("glWindowPos2dvMESA");
#	endif
#	ifdef glWindowPos2fMESA
	_glWindowPos2fMESA = (glWindowPos2fMESAFunc)glGetFunction("glWindowPos2fMESA");
#	endif
#	ifdef glWindowPos2fvMESA
	_glWindowPos2fvMESA = (glWindowPos2fvMESAFunc)glGetFunction("glWindowPos2fvMESA");
#	endif
#	ifdef glWindowPos2iMESA
	_glWindowPos2iMESA = (glWindowPos2iMESAFunc)glGetFunction("glWindowPos2iMESA");
#	endif
#	ifdef glWindowPos2ivMESA
	_glWindowPos2ivMESA = (glWindowPos2ivMESAFunc)glGetFunction("glWindowPos2ivMESA");
#	endif
#	ifdef glWindowPos2sMESA
	_glWindowPos2sMESA = (glWindowPos2sMESAFunc)glGetFunction("glWindowPos2sMESA");
#	endif
#	ifdef glWindowPos2svMESA
	_glWindowPos2svMESA = (glWindowPos2svMESAFunc)glGetFunction("glWindowPos2svMESA");
#	endif
#	ifdef glWindowPos3dMESA
	_glWindowPos3dMESA = (glWindowPos3dMESAFunc)glGetFunction("glWindowPos3dMESA");
#	endif
#	ifdef glWindowPos3dvMESA
	_glWindowPos3dvMESA = (glWindowPos3dvMESAFunc)glGetFunction("glWindowPos3dvMESA");
#	endif
#	ifdef glWindowPos3fMESA
	_glWindowPos3fMESA = (glWindowPos3fMESAFunc)glGetFunction("glWindowPos3fMESA");
#	endif
#	ifdef glWindowPos3fvMESA
	_glWindowPos3fvMESA = (glWindowPos3fvMESAFunc)glGetFunction("glWindowPos3fvMESA");
#	endif
#	ifdef glWindowPos3iMESA
	_glWindowPos3iMESA = (glWindowPos3iMESAFunc)glGetFunction("glWindowPos3iMESA");
#	endif
#	ifdef glWindowPos3ivMESA
	_glWindowPos3ivMESA = (glWindowPos3ivMESAFunc)glGetFunction("glWindowPos3ivMESA");
#	endif
#	ifdef glWindowPos3sMESA
	_glWindowPos3sMESA = (glWindowPos3sMESAFunc)glGetFunction("glWindowPos3sMESA");
#	endif
#	ifdef glWindowPos3svMESA
	_glWindowPos3svMESA = (glWindowPos3svMESAFunc)glGetFunction("glWindowPos3svMESA");
#	endif
#	ifdef glWindowPos4dMESA
	_glWindowPos4dMESA = (glWindowPos4dMESAFunc)glGetFunction("glWindowPos4dMESA");
#	endif
#	ifdef glWindowPos4dvMESA
	_glWindowPos4dvMESA = (glWindowPos4dvMESAFunc)glGetFunction("glWindowPos4dvMESA");
#	endif
#	ifdef glWindowPos4fMESA
	_glWindowPos4fMESA = (glWindowPos4fMESAFunc)glGetFunction("glWindowPos4fMESA");
#	endif
#	ifdef glWindowPos4fvMESA
	_glWindowPos4fvMESA = (glWindowPos4fvMESAFunc)glGetFunction("glWindowPos4fvMESA");
#	endif
#	ifdef glWindowPos4iMESA
	_glWindowPos4iMESA = (glWindowPos4iMESAFunc)glGetFunction("glWindowPos4iMESA");
#	endif
#	ifdef glWindowPos4ivMESA
	_glWindowPos4ivMESA = (glWindowPos4ivMESAFunc)glGetFunction("glWindowPos4ivMESA");
#	endif
#	ifdef glWindowPos4sMESA
	_glWindowPos4sMESA = (glWindowPos4sMESAFunc)glGetFunction("glWindowPos4sMESA");
#	endif
#	ifdef glWindowPos4svMESA
	_glWindowPos4svMESA = (glWindowPos4svMESAFunc)glGetFunction("glWindowPos4svMESA");
#	endif
#	ifdef glMultiModeDrawArraysIBM
	_glMultiModeDrawArraysIBM = (glMultiModeDrawArraysIBMFunc)glGetFunction("glMultiModeDrawArraysIBM");
#	endif
#	ifdef glMultiModeDrawElementsIBM
	_glMultiModeDrawElementsIBM = (glMultiModeDrawElementsIBMFunc)glGetFunction("glMultiModeDrawElementsIBM");
#	endif
#	ifdef glColorPointerListIBM
	_glColorPointerListIBM = (glColorPointerListIBMFunc)glGetFunction("glColorPointerListIBM");
#	endif
#	ifdef glSecondaryColorPointerListIBM
	_glSecondaryColorPointerListIBM = (glSecondaryColorPointerListIBMFunc)glGetFunction("glSecondaryColorPointerListIBM");
#	endif
#	ifdef glEdgeFlagPointerListIBM
	_glEdgeFlagPointerListIBM = (glEdgeFlagPointerListIBMFunc)glGetFunction("glEdgeFlagPointerListIBM");
#	endif
#	ifdef glFogCoordPointerListIBM
	_glFogCoordPointerListIBM = (glFogCoordPointerListIBMFunc)glGetFunction("glFogCoordPointerListIBM");
#	endif
#	ifdef glIndexPointerListIBM
	_glIndexPointerListIBM = (glIndexPointerListIBMFunc)glGetFunction("glIndexPointerListIBM");
#	endif
#	ifdef glNormalPointerListIBM
	_glNormalPointerListIBM = (glNormalPointerListIBMFunc)glGetFunction("glNormalPointerListIBM");
#	endif
#	ifdef glTexCoordPointerListIBM
	_glTexCoordPointerListIBM = (glTexCoordPointerListIBMFunc)glGetFunction("glTexCoordPointerListIBM");
#	endif
#	ifdef glVertexPointerListIBM
	_glVertexPointerListIBM = (glVertexPointerListIBMFunc)glGetFunction("glVertexPointerListIBM");
#	endif
#	ifdef glTbufferMask3DFX
	_glTbufferMask3DFX = (glTbufferMask3DFXFunc)glGetFunction("glTbufferMask3DFX");
#	endif
#	ifdef glSampleMaskEXT
	_glSampleMaskEXT = (glSampleMaskEXTFunc)glGetFunction("glSampleMaskEXT");
#	endif
#	ifdef glSamplePatternEXT
	_glSamplePatternEXT = (glSamplePatternEXTFunc)glGetFunction("glSamplePatternEXT");
#	endif
#	ifdef glTextureColorMaskSGIS
	_glTextureColorMaskSGIS = (glTextureColorMaskSGISFunc)glGetFunction("glTextureColorMaskSGIS");
#	endif
#	ifdef glIglooInterfaceSGIX
	_glIglooInterfaceSGIX = (glIglooInterfaceSGIXFunc)glGetFunction("glIglooInterfaceSGIX");
#	endif
#	ifdef glDeleteFencesNV
	_glDeleteFencesNV = (glDeleteFencesNVFunc)glGetFunction("glDeleteFencesNV");
#	endif
#	ifdef glGenFencesNV
	_glGenFencesNV = (glGenFencesNVFunc)glGetFunction("glGenFencesNV");
#	endif
#	ifdef glIsFenceNV
	_glIsFenceNV = (glIsFenceNVFunc)glGetFunction("glIsFenceNV");
#	endif
#	ifdef glTestFenceNV
	_glTestFenceNV = (glTestFenceNVFunc)glGetFunction("glTestFenceNV");
#	endif
#	ifdef glGetFenceivNV
	_glGetFenceivNV = (glGetFenceivNVFunc)glGetFunction("glGetFenceivNV");
#	endif
#	ifdef glFinishFenceNV
	_glFinishFenceNV = (glFinishFenceNVFunc)glGetFunction("glFinishFenceNV");
#	endif
#	ifdef glSetFenceNV
	_glSetFenceNV = (glSetFenceNVFunc)glGetFunction("glSetFenceNV");
#	endif
#	ifdef glMapControlPointsNV
	_glMapControlPointsNV = (glMapControlPointsNVFunc)glGetFunction("glMapControlPointsNV");
#	endif
#	ifdef glMapParameterivNV
	_glMapParameterivNV = (glMapParameterivNVFunc)glGetFunction("glMapParameterivNV");
#	endif
#	ifdef glMapParameterfvNV
	_glMapParameterfvNV = (glMapParameterfvNVFunc)glGetFunction("glMapParameterfvNV");
#	endif
#	ifdef glGetMapControlPointsNV
	_glGetMapControlPointsNV = (glGetMapControlPointsNVFunc)glGetFunction("glGetMapControlPointsNV");
#	endif
#	ifdef glGetMapParameterivNV
	_glGetMapParameterivNV = (glGetMapParameterivNVFunc)glGetFunction("glGetMapParameterivNV");
#	endif
#	ifdef glGetMapParameterfvNV
	_glGetMapParameterfvNV = (glGetMapParameterfvNVFunc)glGetFunction("glGetMapParameterfvNV");
#	endif
#	ifdef glGetMapAttribParameterivNV
	_glGetMapAttribParameterivNV = (glGetMapAttribParameterivNVFunc)glGetFunction("glGetMapAttribParameterivNV");
#	endif
#	ifdef glGetMapAttribParameterfvNV
	_glGetMapAttribParameterfvNV = (glGetMapAttribParameterfvNVFunc)glGetFunction("glGetMapAttribParameterfvNV");
#	endif
#	ifdef glEvalMapsNV
	_glEvalMapsNV = (glEvalMapsNVFunc)glGetFunction("glEvalMapsNV");
#	endif
#	ifdef glCombinerStageParameterfvNV
	_glCombinerStageParameterfvNV = (glCombinerStageParameterfvNVFunc)glGetFunction("glCombinerStageParameterfvNV");
#	endif
#	ifdef glGetCombinerStageParameterfvNV
	_glGetCombinerStageParameterfvNV = (glGetCombinerStageParameterfvNVFunc)glGetFunction("glGetCombinerStageParameterfvNV");
#	endif
#	ifdef glAreProgramsResidentNV
	_glAreProgramsResidentNV = (glAreProgramsResidentNVFunc)glGetFunction("glAreProgramsResidentNV");
#	endif
#	ifdef glBindProgramNV
	_glBindProgramNV = (glBindProgramNVFunc)glGetFunction("glBindProgramNV");
#	endif
#	ifdef glDeleteProgramsNV
	_glDeleteProgramsNV = (glDeleteProgramsNVFunc)glGetFunction("glDeleteProgramsNV");
#	endif
#	ifdef glExecuteProgramNV
	_glExecuteProgramNV = (glExecuteProgramNVFunc)glGetFunction("glExecuteProgramNV");
#	endif
#	ifdef glGenProgramsNV
	_glGenProgramsNV = (glGenProgramsNVFunc)glGetFunction("glGenProgramsNV");
#	endif
#	ifdef glGetProgramParameterdvNV
	_glGetProgramParameterdvNV = (glGetProgramParameterdvNVFunc)glGetFunction("glGetProgramParameterdvNV");
#	endif
#	ifdef glGetProgramParameterfvNV
	_glGetProgramParameterfvNV = (glGetProgramParameterfvNVFunc)glGetFunction("glGetProgramParameterfvNV");
#	endif
#	ifdef glGetProgramivNV
	_glGetProgramivNV = (glGetProgramivNVFunc)glGetFunction("glGetProgramivNV");
#	endif
#	ifdef glGetProgramStringNV
	_glGetProgramStringNV = (glGetProgramStringNVFunc)glGetFunction("glGetProgramStringNV");
#	endif
#	ifdef glGetTrackMatrixivNV
	_glGetTrackMatrixivNV = (glGetTrackMatrixivNVFunc)glGetFunction("glGetTrackMatrixivNV");
#	endif
#	ifdef glGetVertexAttribdvNV
	_glGetVertexAttribdvNV = (glGetVertexAttribdvNVFunc)glGetFunction("glGetVertexAttribdvNV");
#	endif
#	ifdef glGetVertexAttribfvNV
	_glGetVertexAttribfvNV = (glGetVertexAttribfvNVFunc)glGetFunction("glGetVertexAttribfvNV");
#	endif
#	ifdef glGetVertexAttribivNV
	_glGetVertexAttribivNV = (glGetVertexAttribivNVFunc)glGetFunction("glGetVertexAttribivNV");
#	endif
#	ifdef glGetVertexAttribPointervNV
	_glGetVertexAttribPointervNV = (glGetVertexAttribPointervNVFunc)glGetFunction("glGetVertexAttribPointervNV");
#	endif
#	ifdef glIsProgramNV
	_glIsProgramNV = (glIsProgramNVFunc)glGetFunction("glIsProgramNV");
#	endif
#	ifdef glLoadProgramNV
	_glLoadProgramNV = (glLoadProgramNVFunc)glGetFunction("glLoadProgramNV");
#	endif
#	ifdef glProgramParameter4dNV
	_glProgramParameter4dNV = (glProgramParameter4dNVFunc)glGetFunction("glProgramParameter4dNV");
#	endif
#	ifdef glProgramParameter4dvNV
	_glProgramParameter4dvNV = (glProgramParameter4dvNVFunc)glGetFunction("glProgramParameter4dvNV");
#	endif
#	ifdef glProgramParameter4fNV
	_glProgramParameter4fNV = (glProgramParameter4fNVFunc)glGetFunction("glProgramParameter4fNV");
#	endif
#	ifdef glProgramParameter4fvNV
	_glProgramParameter4fvNV = (glProgramParameter4fvNVFunc)glGetFunction("glProgramParameter4fvNV");
#	endif
#	ifdef glProgramParameters4dvNV
	_glProgramParameters4dvNV = (glProgramParameters4dvNVFunc)glGetFunction("glProgramParameters4dvNV");
#	endif
#	ifdef glProgramParameters4fvNV
	_glProgramParameters4fvNV = (glProgramParameters4fvNVFunc)glGetFunction("glProgramParameters4fvNV");
#	endif
#	ifdef glRequestResidentProgramsNV
	_glRequestResidentProgramsNV = (glRequestResidentProgramsNVFunc)glGetFunction("glRequestResidentProgramsNV");
#	endif
#	ifdef glTrackMatrixNV
	_glTrackMatrixNV = (glTrackMatrixNVFunc)glGetFunction("glTrackMatrixNV");
#	endif
#	ifdef glVertexAttribPointerNV
	_glVertexAttribPointerNV = (glVertexAttribPointerNVFunc)glGetFunction("glVertexAttribPointerNV");
#	endif
#	ifdef glVertexAttrib1dNV
	_glVertexAttrib1dNV = (glVertexAttrib1dNVFunc)glGetFunction("glVertexAttrib1dNV");
#	endif
#	ifdef glVertexAttrib1dvNV
	_glVertexAttrib1dvNV = (glVertexAttrib1dvNVFunc)glGetFunction("glVertexAttrib1dvNV");
#	endif
#	ifdef glVertexAttrib1fNV
	_glVertexAttrib1fNV = (glVertexAttrib1fNVFunc)glGetFunction("glVertexAttrib1fNV");
#	endif
#	ifdef glVertexAttrib1fvNV
	_glVertexAttrib1fvNV = (glVertexAttrib1fvNVFunc)glGetFunction("glVertexAttrib1fvNV");
#	endif
#	ifdef glVertexAttrib1sNV
	_glVertexAttrib1sNV = (glVertexAttrib1sNVFunc)glGetFunction("glVertexAttrib1sNV");
#	endif
#	ifdef glVertexAttrib1svNV
	_glVertexAttrib1svNV = (glVertexAttrib1svNVFunc)glGetFunction("glVertexAttrib1svNV");
#	endif
#	ifdef glVertexAttrib2dNV
	_glVertexAttrib2dNV = (glVertexAttrib2dNVFunc)glGetFunction("glVertexAttrib2dNV");
#	endif
#	ifdef glVertexAttrib2dvNV
	_glVertexAttrib2dvNV = (glVertexAttrib2dvNVFunc)glGetFunction("glVertexAttrib2dvNV");
#	endif
#	ifdef glVertexAttrib2fNV
	_glVertexAttrib2fNV = (glVertexAttrib2fNVFunc)glGetFunction("glVertexAttrib2fNV");
#	endif
#	ifdef glVertexAttrib2fvNV
	_glVertexAttrib2fvNV = (glVertexAttrib2fvNVFunc)glGetFunction("glVertexAttrib2fvNV");
#	endif
#	ifdef glVertexAttrib2sNV
	_glVertexAttrib2sNV = (glVertexAttrib2sNVFunc)glGetFunction("glVertexAttrib2sNV");
#	endif
#	ifdef glVertexAttrib2svNV
	_glVertexAttrib2svNV = (glVertexAttrib2svNVFunc)glGetFunction("glVertexAttrib2svNV");
#	endif
#	ifdef glVertexAttrib3dNV
	_glVertexAttrib3dNV = (glVertexAttrib3dNVFunc)glGetFunction("glVertexAttrib3dNV");
#	endif
#	ifdef glVertexAttrib3dvNV
	_glVertexAttrib3dvNV = (glVertexAttrib3dvNVFunc)glGetFunction("glVertexAttrib3dvNV");
#	endif
#	ifdef glVertexAttrib3fNV
	_glVertexAttrib3fNV = (glVertexAttrib3fNVFunc)glGetFunction("glVertexAttrib3fNV");
#	endif
#	ifdef glVertexAttrib3fvNV
	_glVertexAttrib3fvNV = (glVertexAttrib3fvNVFunc)glGetFunction("glVertexAttrib3fvNV");
#	endif
#	ifdef glVertexAttrib3sNV
	_glVertexAttrib3sNV = (glVertexAttrib3sNVFunc)glGetFunction("glVertexAttrib3sNV");
#	endif
#	ifdef glVertexAttrib3svNV
	_glVertexAttrib3svNV = (glVertexAttrib3svNVFunc)glGetFunction("glVertexAttrib3svNV");
#	endif
#	ifdef glVertexAttrib4dNV
	_glVertexAttrib4dNV = (glVertexAttrib4dNVFunc)glGetFunction("glVertexAttrib4dNV");
#	endif
#	ifdef glVertexAttrib4dvNV
	_glVertexAttrib4dvNV = (glVertexAttrib4dvNVFunc)glGetFunction("glVertexAttrib4dvNV");
#	endif
#	ifdef glVertexAttrib4fNV
	_glVertexAttrib4fNV = (glVertexAttrib4fNVFunc)glGetFunction("glVertexAttrib4fNV");
#	endif
#	ifdef glVertexAttrib4fvNV
	_glVertexAttrib4fvNV = (glVertexAttrib4fvNVFunc)glGetFunction("glVertexAttrib4fvNV");
#	endif
#	ifdef glVertexAttrib4sNV
	_glVertexAttrib4sNV = (glVertexAttrib4sNVFunc)glGetFunction("glVertexAttrib4sNV");
#	endif
#	ifdef glVertexAttrib4svNV
	_glVertexAttrib4svNV = (glVertexAttrib4svNVFunc)glGetFunction("glVertexAttrib4svNV");
#	endif
#	ifdef glVertexAttrib4ubNV
	_glVertexAttrib4ubNV = (glVertexAttrib4ubNVFunc)glGetFunction("glVertexAttrib4ubNV");
#	endif
#	ifdef glVertexAttrib4ubvNV
	_glVertexAttrib4ubvNV = (glVertexAttrib4ubvNVFunc)glGetFunction("glVertexAttrib4ubvNV");
#	endif
#	ifdef glVertexAttribs1dvNV
	_glVertexAttribs1dvNV = (glVertexAttribs1dvNVFunc)glGetFunction("glVertexAttribs1dvNV");
#	endif
#	ifdef glVertexAttribs1fvNV
	_glVertexAttribs1fvNV = (glVertexAttribs1fvNVFunc)glGetFunction("glVertexAttribs1fvNV");
#	endif
#	ifdef glVertexAttribs1svNV
	_glVertexAttribs1svNV = (glVertexAttribs1svNVFunc)glGetFunction("glVertexAttribs1svNV");
#	endif
#	ifdef glVertexAttribs2dvNV
	_glVertexAttribs2dvNV = (glVertexAttribs2dvNVFunc)glGetFunction("glVertexAttribs2dvNV");
#	endif
#	ifdef glVertexAttribs2fvNV
	_glVertexAttribs2fvNV = (glVertexAttribs2fvNVFunc)glGetFunction("glVertexAttribs2fvNV");
#	endif
#	ifdef glVertexAttribs2svNV
	_glVertexAttribs2svNV = (glVertexAttribs2svNVFunc)glGetFunction("glVertexAttribs2svNV");
#	endif
#	ifdef glVertexAttribs3dvNV
	_glVertexAttribs3dvNV = (glVertexAttribs3dvNVFunc)glGetFunction("glVertexAttribs3dvNV");
#	endif
#	ifdef glVertexAttribs3fvNV
	_glVertexAttribs3fvNV = (glVertexAttribs3fvNVFunc)glGetFunction("glVertexAttribs3fvNV");
#	endif
#	ifdef glVertexAttribs3svNV
	_glVertexAttribs3svNV = (glVertexAttribs3svNVFunc)glGetFunction("glVertexAttribs3svNV");
#	endif
#	ifdef glVertexAttribs4dvNV
	_glVertexAttribs4dvNV = (glVertexAttribs4dvNVFunc)glGetFunction("glVertexAttribs4dvNV");
#	endif
#	ifdef glVertexAttribs4fvNV
	_glVertexAttribs4fvNV = (glVertexAttribs4fvNVFunc)glGetFunction("glVertexAttribs4fvNV");
#	endif
#	ifdef glVertexAttribs4svNV
	_glVertexAttribs4svNV = (glVertexAttribs4svNVFunc)glGetFunction("glVertexAttribs4svNV");
#	endif
#	ifdef glVertexAttribs4ubvNV
	_glVertexAttribs4ubvNV = (glVertexAttribs4ubvNVFunc)glGetFunction("glVertexAttribs4ubvNV");
#	endif
#	ifdef glTexBumpParameterivATI
	_glTexBumpParameterivATI = (glTexBumpParameterivATIFunc)glGetFunction("glTexBumpParameterivATI");
#	endif
#	ifdef glTexBumpParameterfvATI
	_glTexBumpParameterfvATI = (glTexBumpParameterfvATIFunc)glGetFunction("glTexBumpParameterfvATI");
#	endif
#	ifdef glGetTexBumpParameterivATI
	_glGetTexBumpParameterivATI = (glGetTexBumpParameterivATIFunc)glGetFunction("glGetTexBumpParameterivATI");
#	endif
#	ifdef glGetTexBumpParameterfvATI
	_glGetTexBumpParameterfvATI = (glGetTexBumpParameterfvATIFunc)glGetFunction("glGetTexBumpParameterfvATI");
#	endif
#	ifdef glGenFragmentShadersATI
	_glGenFragmentShadersATI = (glGenFragmentShadersATIFunc)glGetFunction("glGenFragmentShadersATI");
#	endif
#	ifdef glBindFragmentShaderATI
	_glBindFragmentShaderATI = (glBindFragmentShaderATIFunc)glGetFunction("glBindFragmentShaderATI");
#	endif
#	ifdef glDeleteFragmentShaderATI
	_glDeleteFragmentShaderATI = (glDeleteFragmentShaderATIFunc)glGetFunction("glDeleteFragmentShaderATI");
#	endif
#	ifdef glBeginFragmentShaderATI
	_glBeginFragmentShaderATI = (glBeginFragmentShaderATIFunc)glGetFunction("glBeginFragmentShaderATI");
#	endif
#	ifdef glEndFragmentShaderATI
	_glEndFragmentShaderATI = (glEndFragmentShaderATIFunc)glGetFunction("glEndFragmentShaderATI");
#	endif
#	ifdef glPassTexCoordATI
	_glPassTexCoordATI = (glPassTexCoordATIFunc)glGetFunction("glPassTexCoordATI");
#	endif
#	ifdef glSampleMapATI
	_glSampleMapATI = (glSampleMapATIFunc)glGetFunction("glSampleMapATI");
#	endif
#	ifdef glColorFragmentOp1ATI
	_glColorFragmentOp1ATI = (glColorFragmentOp1ATIFunc)glGetFunction("glColorFragmentOp1ATI");
#	endif
#	ifdef glColorFragmentOp2ATI
	_glColorFragmentOp2ATI = (glColorFragmentOp2ATIFunc)glGetFunction("glColorFragmentOp2ATI");
#	endif
#	ifdef glColorFragmentOp3ATI
	_glColorFragmentOp3ATI = (glColorFragmentOp3ATIFunc)glGetFunction("glColorFragmentOp3ATI");
#	endif
#	ifdef glAlphaFragmentOp1ATI
	_glAlphaFragmentOp1ATI = (glAlphaFragmentOp1ATIFunc)glGetFunction("glAlphaFragmentOp1ATI");
#	endif
#	ifdef glAlphaFragmentOp2ATI
	_glAlphaFragmentOp2ATI = (glAlphaFragmentOp2ATIFunc)glGetFunction("glAlphaFragmentOp2ATI");
#	endif
#	ifdef glAlphaFragmentOp3ATI
	_glAlphaFragmentOp3ATI = (glAlphaFragmentOp3ATIFunc)glGetFunction("glAlphaFragmentOp3ATI");
#	endif
#	ifdef glSetFragmentShaderConstantATI
	_glSetFragmentShaderConstantATI = (glSetFragmentShaderConstantATIFunc)glGetFunction("glSetFragmentShaderConstantATI");
#	endif
#	ifdef glPNTrianglesiATI
	_glPNTrianglesiATI = (glPNTrianglesiATIFunc)glGetFunction("glPNTrianglesiATI");
#	endif
#	ifdef glPNTrianglesfATI
	_glPNTrianglesfATI = (glPNTrianglesfATIFunc)glGetFunction("glPNTrianglesfATI");
#	endif
#	ifdef glNewObjectBufferATI
	_glNewObjectBufferATI = (glNewObjectBufferATIFunc)glGetFunction("glNewObjectBufferATI");
#	endif
#	ifdef glIsObjectBufferATI
	_glIsObjectBufferATI = (glIsObjectBufferATIFunc)glGetFunction("glIsObjectBufferATI");
#	endif
#	ifdef glUpdateObjectBufferATI
	_glUpdateObjectBufferATI = (glUpdateObjectBufferATIFunc)glGetFunction("glUpdateObjectBufferATI");
#	endif
#	ifdef glGetObjectBufferfvATI
	_glGetObjectBufferfvATI = (glGetObjectBufferfvATIFunc)glGetFunction("glGetObjectBufferfvATI");
#	endif
#	ifdef glGetObjectBufferivATI
	_glGetObjectBufferivATI = (glGetObjectBufferivATIFunc)glGetFunction("glGetObjectBufferivATI");
#	endif
#	ifdef glFreeObjectBufferATI
	_glFreeObjectBufferATI = (glFreeObjectBufferATIFunc)glGetFunction("glFreeObjectBufferATI");
#	endif
#	ifdef glArrayObjectATI
	_glArrayObjectATI = (glArrayObjectATIFunc)glGetFunction("glArrayObjectATI");
#	endif
#	ifdef glGetArrayObjectfvATI
	_glGetArrayObjectfvATI = (glGetArrayObjectfvATIFunc)glGetFunction("glGetArrayObjectfvATI");
#	endif
#	ifdef glGetArrayObjectivATI
	_glGetArrayObjectivATI = (glGetArrayObjectivATIFunc)glGetFunction("glGetArrayObjectivATI");
#	endif
#	ifdef glVariantArrayObjectATI
	_glVariantArrayObjectATI = (glVariantArrayObjectATIFunc)glGetFunction("glVariantArrayObjectATI");
#	endif
#	ifdef glGetVariantArrayObjectfvATI
	_glGetVariantArrayObjectfvATI = (glGetVariantArrayObjectfvATIFunc)glGetFunction("glGetVariantArrayObjectfvATI");
#	endif
#	ifdef glGetVariantArrayObjectivATI
	_glGetVariantArrayObjectivATI = (glGetVariantArrayObjectivATIFunc)glGetFunction("glGetVariantArrayObjectivATI");
#	endif
#	ifdef glBeginVertexShaderEXT
	_glBeginVertexShaderEXT = (glBeginVertexShaderEXTFunc)glGetFunction("glBeginVertexShaderEXT");
#	endif
#	ifdef glEndVertexShaderEXT
	_glEndVertexShaderEXT = (glEndVertexShaderEXTFunc)glGetFunction("glEndVertexShaderEXT");
#	endif
#	ifdef glBindVertexShaderEXT
	_glBindVertexShaderEXT = (glBindVertexShaderEXTFunc)glGetFunction("glBindVertexShaderEXT");
#	endif
#	ifdef glGenVertexShadersEXT
	_glGenVertexShadersEXT = (glGenVertexShadersEXTFunc)glGetFunction("glGenVertexShadersEXT");
#	endif
#	ifdef glDeleteVertexShaderEXT
	_glDeleteVertexShaderEXT = (glDeleteVertexShaderEXTFunc)glGetFunction("glDeleteVertexShaderEXT");
#	endif
#	ifdef glShaderOp1EXT
	_glShaderOp1EXT = (glShaderOp1EXTFunc)glGetFunction("glShaderOp1EXT");
#	endif
#	ifdef glShaderOp2EXT
	_glShaderOp2EXT = (glShaderOp2EXTFunc)glGetFunction("glShaderOp2EXT");
#	endif
#	ifdef glShaderOp3EXT
	_glShaderOp3EXT = (glShaderOp3EXTFunc)glGetFunction("glShaderOp3EXT");
#	endif
#	ifdef glSwizzleEXT
	_glSwizzleEXT = (glSwizzleEXTFunc)glGetFunction("glSwizzleEXT");
#	endif
#	ifdef glWriteMaskEXT
	_glWriteMaskEXT = (glWriteMaskEXTFunc)glGetFunction("glWriteMaskEXT");
#	endif
#	ifdef glInsertComponentEXT
	_glInsertComponentEXT = (glInsertComponentEXTFunc)glGetFunction("glInsertComponentEXT");
#	endif
#	ifdef glExtractComponentEXT
	_glExtractComponentEXT = (glExtractComponentEXTFunc)glGetFunction("glExtractComponentEXT");
#	endif
#	ifdef glGenSymbolsEXT
	_glGenSymbolsEXT = (glGenSymbolsEXTFunc)glGetFunction("glGenSymbolsEXT");
#	endif
#	ifdef glSetInvariantEXT
	_glSetInvariantEXT = (glSetInvariantEXTFunc)glGetFunction("glSetInvariantEXT");
#	endif
#	ifdef glSetLocalConstantEXT
	_glSetLocalConstantEXT = (glSetLocalConstantEXTFunc)glGetFunction("glSetLocalConstantEXT");
#	endif
#	ifdef glVariantbvEXT
	_glVariantbvEXT = (glVariantbvEXTFunc)glGetFunction("glVariantbvEXT");
#	endif
#	ifdef glVariantsvEXT
	_glVariantsvEXT = (glVariantsvEXTFunc)glGetFunction("glVariantsvEXT");
#	endif
#	ifdef glVariantivEXT
	_glVariantivEXT = (glVariantivEXTFunc)glGetFunction("glVariantivEXT");
#	endif
#	ifdef glVariantfvEXT
	_glVariantfvEXT = (glVariantfvEXTFunc)glGetFunction("glVariantfvEXT");
#	endif
#	ifdef glVariantdvEXT
	_glVariantdvEXT = (glVariantdvEXTFunc)glGetFunction("glVariantdvEXT");
#	endif
#	ifdef glVariantubvEXT
	_glVariantubvEXT = (glVariantubvEXTFunc)glGetFunction("glVariantubvEXT");
#	endif
#	ifdef glVariantusvEXT
	_glVariantusvEXT = (glVariantusvEXTFunc)glGetFunction("glVariantusvEXT");
#	endif
#	ifdef glVariantuivEXT
	_glVariantuivEXT = (glVariantuivEXTFunc)glGetFunction("glVariantuivEXT");
#	endif
#	ifdef glVariantPointerEXT
	_glVariantPointerEXT = (glVariantPointerEXTFunc)glGetFunction("glVariantPointerEXT");
#	endif
#	ifdef glEnableVariantClientStateEXT
	_glEnableVariantClientStateEXT = (glEnableVariantClientStateEXTFunc)glGetFunction("glEnableVariantClientStateEXT");
#	endif
#	ifdef glDisableVariantClientStateEXT
	_glDisableVariantClientStateEXT = (glDisableVariantClientStateEXTFunc)glGetFunction("glDisableVariantClientStateEXT");
#	endif
#	ifdef glBindLightParameterEXT
	_glBindLightParameterEXT = (glBindLightParameterEXTFunc)glGetFunction("glBindLightParameterEXT");
#	endif
#	ifdef glBindMaterialParameterEXT
	_glBindMaterialParameterEXT = (glBindMaterialParameterEXTFunc)glGetFunction("glBindMaterialParameterEXT");
#	endif
#	ifdef glBindTexGenParameterEXT
	_glBindTexGenParameterEXT = (glBindTexGenParameterEXTFunc)glGetFunction("glBindTexGenParameterEXT");
#	endif
#	ifdef glBindTextureUnitParameterEXT
	_glBindTextureUnitParameterEXT = (glBindTextureUnitParameterEXTFunc)glGetFunction("glBindTextureUnitParameterEXT");
#	endif
#	ifdef glBindParameterEXT
	_glBindParameterEXT = (glBindParameterEXTFunc)glGetFunction("glBindParameterEXT");
#	endif
#	ifdef glIsVariantEnabledEXT
	_glIsVariantEnabledEXT = (glIsVariantEnabledEXTFunc)glGetFunction("glIsVariantEnabledEXT");
#	endif
#	ifdef glGetVariantBooleanvEXT
	_glGetVariantBooleanvEXT = (glGetVariantBooleanvEXTFunc)glGetFunction("glGetVariantBooleanvEXT");
#	endif
#	ifdef glGetVariantIntegervEXT
	_glGetVariantIntegervEXT = (glGetVariantIntegervEXTFunc)glGetFunction("glGetVariantIntegervEXT");
#	endif
#	ifdef glGetVariantFloatvEXT
	_glGetVariantFloatvEXT = (glGetVariantFloatvEXTFunc)glGetFunction("glGetVariantFloatvEXT");
#	endif
#	ifdef glGetVariantPointervEXT
	_glGetVariantPointervEXT = (glGetVariantPointervEXTFunc)glGetFunction("glGetVariantPointervEXT");
#	endif
#	ifdef glGetInvariantBooleanvEXT
	_glGetInvariantBooleanvEXT = (glGetInvariantBooleanvEXTFunc)glGetFunction("glGetInvariantBooleanvEXT");
#	endif
#	ifdef glGetInvariantIntegervEXT
	_glGetInvariantIntegervEXT = (glGetInvariantIntegervEXTFunc)glGetFunction("glGetInvariantIntegervEXT");
#	endif
#	ifdef glGetInvariantFloatvEXT
	_glGetInvariantFloatvEXT = (glGetInvariantFloatvEXTFunc)glGetFunction("glGetInvariantFloatvEXT");
#	endif
#	ifdef glGetLocalConstantBooleanvEXT
	_glGetLocalConstantBooleanvEXT = (glGetLocalConstantBooleanvEXTFunc)glGetFunction("glGetLocalConstantBooleanvEXT");
#	endif
#	ifdef glGetLocalConstantIntegervEXT
	_glGetLocalConstantIntegervEXT = (glGetLocalConstantIntegervEXTFunc)glGetFunction("glGetLocalConstantIntegervEXT");
#	endif
#	ifdef glGetLocalConstantFloatvEXT
	_glGetLocalConstantFloatvEXT = (glGetLocalConstantFloatvEXTFunc)glGetFunction("glGetLocalConstantFloatvEXT");
#	endif
#	ifdef glVertexStream1sATI
	_glVertexStream1sATI = (glVertexStream1sATIFunc)glGetFunction("glVertexStream1sATI");
#	endif
#	ifdef glVertexStream1svATI
	_glVertexStream1svATI = (glVertexStream1svATIFunc)glGetFunction("glVertexStream1svATI");
#	endif
#	ifdef glVertexStream1iATI
	_glVertexStream1iATI = (glVertexStream1iATIFunc)glGetFunction("glVertexStream1iATI");
#	endif
#	ifdef glVertexStream1ivATI
	_glVertexStream1ivATI = (glVertexStream1ivATIFunc)glGetFunction("glVertexStream1ivATI");
#	endif
#	ifdef glVertexStream1fATI
	_glVertexStream1fATI = (glVertexStream1fATIFunc)glGetFunction("glVertexStream1fATI");
#	endif
#	ifdef glVertexStream1fvATI
	_glVertexStream1fvATI = (glVertexStream1fvATIFunc)glGetFunction("glVertexStream1fvATI");
#	endif
#	ifdef glVertexStream1dATI
	_glVertexStream1dATI = (glVertexStream1dATIFunc)glGetFunction("glVertexStream1dATI");
#	endif
#	ifdef glVertexStream1dvATI
	_glVertexStream1dvATI = (glVertexStream1dvATIFunc)glGetFunction("glVertexStream1dvATI");
#	endif
#	ifdef glVertexStream2sATI
	_glVertexStream2sATI = (glVertexStream2sATIFunc)glGetFunction("glVertexStream2sATI");
#	endif
#	ifdef glVertexStream2svATI
	_glVertexStream2svATI = (glVertexStream2svATIFunc)glGetFunction("glVertexStream2svATI");
#	endif
#	ifdef glVertexStream2iATI
	_glVertexStream2iATI = (glVertexStream2iATIFunc)glGetFunction("glVertexStream2iATI");
#	endif
#	ifdef glVertexStream2ivATI
	_glVertexStream2ivATI = (glVertexStream2ivATIFunc)glGetFunction("glVertexStream2ivATI");
#	endif
#	ifdef glVertexStream2fATI
	_glVertexStream2fATI = (glVertexStream2fATIFunc)glGetFunction("glVertexStream2fATI");
#	endif
#	ifdef glVertexStream2fvATI
	_glVertexStream2fvATI = (glVertexStream2fvATIFunc)glGetFunction("glVertexStream2fvATI");
#	endif
#	ifdef glVertexStream2dATI
	_glVertexStream2dATI = (glVertexStream2dATIFunc)glGetFunction("glVertexStream2dATI");
#	endif
#	ifdef glVertexStream2dvATI
	_glVertexStream2dvATI = (glVertexStream2dvATIFunc)glGetFunction("glVertexStream2dvATI");
#	endif
#	ifdef glVertexStream3sATI
	_glVertexStream3sATI = (glVertexStream3sATIFunc)glGetFunction("glVertexStream3sATI");
#	endif
#	ifdef glVertexStream3svATI
	_glVertexStream3svATI = (glVertexStream3svATIFunc)glGetFunction("glVertexStream3svATI");
#	endif
#	ifdef glVertexStream3iATI
	_glVertexStream3iATI = (glVertexStream3iATIFunc)glGetFunction("glVertexStream3iATI");
#	endif
#	ifdef glVertexStream3ivATI
	_glVertexStream3ivATI = (glVertexStream3ivATIFunc)glGetFunction("glVertexStream3ivATI");
#	endif
#	ifdef glVertexStream3fATI
	_glVertexStream3fATI = (glVertexStream3fATIFunc)glGetFunction("glVertexStream3fATI");
#	endif
#	ifdef glVertexStream3fvATI
	_glVertexStream3fvATI = (glVertexStream3fvATIFunc)glGetFunction("glVertexStream3fvATI");
#	endif
#	ifdef glVertexStream3dATI
	_glVertexStream3dATI = (glVertexStream3dATIFunc)glGetFunction("glVertexStream3dATI");
#	endif
#	ifdef glVertexStream3dvATI
	_glVertexStream3dvATI = (glVertexStream3dvATIFunc)glGetFunction("glVertexStream3dvATI");
#	endif
#	ifdef glVertexStream4sATI
	_glVertexStream4sATI = (glVertexStream4sATIFunc)glGetFunction("glVertexStream4sATI");
#	endif
#	ifdef glVertexStream4svATI
	_glVertexStream4svATI = (glVertexStream4svATIFunc)glGetFunction("glVertexStream4svATI");
#	endif
#	ifdef glVertexStream4iATI
	_glVertexStream4iATI = (glVertexStream4iATIFunc)glGetFunction("glVertexStream4iATI");
#	endif
#	ifdef glVertexStream4ivATI
	_glVertexStream4ivATI = (glVertexStream4ivATIFunc)glGetFunction("glVertexStream4ivATI");
#	endif
#	ifdef glVertexStream4fATI
	_glVertexStream4fATI = (glVertexStream4fATIFunc)glGetFunction("glVertexStream4fATI");
#	endif
#	ifdef glVertexStream4fvATI
	_glVertexStream4fvATI = (glVertexStream4fvATIFunc)glGetFunction("glVertexStream4fvATI");
#	endif
#	ifdef glVertexStream4dATI
	_glVertexStream4dATI = (glVertexStream4dATIFunc)glGetFunction("glVertexStream4dATI");
#	endif
#	ifdef glVertexStream4dvATI
	_glVertexStream4dvATI = (glVertexStream4dvATIFunc)glGetFunction("glVertexStream4dvATI");
#	endif
#	ifdef glNormalStream3bATI
	_glNormalStream3bATI = (glNormalStream3bATIFunc)glGetFunction("glNormalStream3bATI");
#	endif
#	ifdef glNormalStream3bvATI
	_glNormalStream3bvATI = (glNormalStream3bvATIFunc)glGetFunction("glNormalStream3bvATI");
#	endif
#	ifdef glNormalStream3sATI
	_glNormalStream3sATI = (glNormalStream3sATIFunc)glGetFunction("glNormalStream3sATI");
#	endif
#	ifdef glNormalStream3svATI
	_glNormalStream3svATI = (glNormalStream3svATIFunc)glGetFunction("glNormalStream3svATI");
#	endif
#	ifdef glNormalStream3iATI
	_glNormalStream3iATI = (glNormalStream3iATIFunc)glGetFunction("glNormalStream3iATI");
#	endif
#	ifdef glNormalStream3ivATI
	_glNormalStream3ivATI = (glNormalStream3ivATIFunc)glGetFunction("glNormalStream3ivATI");
#	endif
#	ifdef glNormalStream3fATI
	_glNormalStream3fATI = (glNormalStream3fATIFunc)glGetFunction("glNormalStream3fATI");
#	endif
#	ifdef glNormalStream3fvATI
	_glNormalStream3fvATI = (glNormalStream3fvATIFunc)glGetFunction("glNormalStream3fvATI");
#	endif
#	ifdef glNormalStream3dATI
	_glNormalStream3dATI = (glNormalStream3dATIFunc)glGetFunction("glNormalStream3dATI");
#	endif
#	ifdef glNormalStream3dvATI
	_glNormalStream3dvATI = (glNormalStream3dvATIFunc)glGetFunction("glNormalStream3dvATI");
#	endif
#	ifdef glClientActiveVertexStreamATI
	_glClientActiveVertexStreamATI = (glClientActiveVertexStreamATIFunc)glGetFunction("glClientActiveVertexStreamATI");
#	endif
#	ifdef glVertexBlendEnviATI
	_glVertexBlendEnviATI = (glVertexBlendEnviATIFunc)glGetFunction("glVertexBlendEnviATI");
#	endif
#	ifdef glVertexBlendEnvfATI
	_glVertexBlendEnvfATI = (glVertexBlendEnvfATIFunc)glGetFunction("glVertexBlendEnvfATI");
#	endif
#	ifdef glElementPointerATI
	_glElementPointerATI = (glElementPointerATIFunc)glGetFunction("glElementPointerATI");
#	endif
#	ifdef glDrawElementArrayATI
	_glDrawElementArrayATI = (glDrawElementArrayATIFunc)glGetFunction("glDrawElementArrayATI");
#	endif
#	ifdef glDrawRangeElementArrayATI
	_glDrawRangeElementArrayATI = (glDrawRangeElementArrayATIFunc)glGetFunction("glDrawRangeElementArrayATI");
#	endif
#	ifdef glDrawMeshArraysSUN
	_glDrawMeshArraysSUN = (glDrawMeshArraysSUNFunc)glGetFunction("glDrawMeshArraysSUN");
#	endif
#	ifdef glGenOcclusionQueriesNV
	_glGenOcclusionQueriesNV = (glGenOcclusionQueriesNVFunc)glGetFunction("glGenOcclusionQueriesNV");
#	endif
#	ifdef glDeleteOcclusionQueriesNV
	_glDeleteOcclusionQueriesNV = (glDeleteOcclusionQueriesNVFunc)glGetFunction("glDeleteOcclusionQueriesNV");
#	endif
#	ifdef glIsOcclusionQueryNV
	_glIsOcclusionQueryNV = (glIsOcclusionQueryNVFunc)glGetFunction("glIsOcclusionQueryNV");
#	endif
#	ifdef glBeginOcclusionQueryNV
	_glBeginOcclusionQueryNV = (glBeginOcclusionQueryNVFunc)glGetFunction("glBeginOcclusionQueryNV");
#	endif
#	ifdef glEndOcclusionQueryNV
	_glEndOcclusionQueryNV = (glEndOcclusionQueryNVFunc)glGetFunction("glEndOcclusionQueryNV");
#	endif
#	ifdef glGetOcclusionQueryivNV
	_glGetOcclusionQueryivNV = (glGetOcclusionQueryivNVFunc)glGetFunction("glGetOcclusionQueryivNV");
#	endif
#	ifdef glGetOcclusionQueryuivNV
	_glGetOcclusionQueryuivNV = (glGetOcclusionQueryuivNVFunc)glGetFunction("glGetOcclusionQueryuivNV");
#	endif
#	ifdef glPointParameteriNV
	_glPointParameteriNV = (glPointParameteriNVFunc)glGetFunction("glPointParameteriNV");
#	endif
#	ifdef glPointParameterivNV
	_glPointParameterivNV = (glPointParameterivNVFunc)glGetFunction("glPointParameterivNV");
#	endif
#	ifdef glActiveStencilFaceEXT
	_glActiveStencilFaceEXT = (glActiveStencilFaceEXTFunc)glGetFunction("glActiveStencilFaceEXT");
#	endif
#	ifdef glElementPointerAPPLE
	_glElementPointerAPPLE = (glElementPointerAPPLEFunc)glGetFunction("glElementPointerAPPLE");
#	endif
#	ifdef glDrawElementArrayAPPLE
	_glDrawElementArrayAPPLE = (glDrawElementArrayAPPLEFunc)glGetFunction("glDrawElementArrayAPPLE");
#	endif
#	ifdef glDrawRangeElementArrayAPPLE
	_glDrawRangeElementArrayAPPLE = (glDrawRangeElementArrayAPPLEFunc)glGetFunction("glDrawRangeElementArrayAPPLE");
#	endif
#	ifdef glMultiDrawElementArrayAPPLE
	_glMultiDrawElementArrayAPPLE = (glMultiDrawElementArrayAPPLEFunc)glGetFunction("glMultiDrawElementArrayAPPLE");
#	endif
#	ifdef glMultiDrawRangeElementArrayAPPLE
	_glMultiDrawRangeElementArrayAPPLE = (glMultiDrawRangeElementArrayAPPLEFunc)glGetFunction("glMultiDrawRangeElementArrayAPPLE");
#	endif
#	ifdef glGenFencesAPPLE
	_glGenFencesAPPLE = (glGenFencesAPPLEFunc)glGetFunction("glGenFencesAPPLE");
#	endif
#	ifdef glDeleteFencesAPPLE
	_glDeleteFencesAPPLE = (glDeleteFencesAPPLEFunc)glGetFunction("glDeleteFencesAPPLE");
#	endif
#	ifdef glSetFenceAPPLE
	_glSetFenceAPPLE = (glSetFenceAPPLEFunc)glGetFunction("glSetFenceAPPLE");
#	endif
#	ifdef glIsFenceAPPLE
	_glIsFenceAPPLE = (glIsFenceAPPLEFunc)glGetFunction("glIsFenceAPPLE");
#	endif
#	ifdef glTestFenceAPPLE
	_glTestFenceAPPLE = (glTestFenceAPPLEFunc)glGetFunction("glTestFenceAPPLE");
#	endif
#	ifdef glFinishFenceAPPLE
	_glFinishFenceAPPLE = (glFinishFenceAPPLEFunc)glGetFunction("glFinishFenceAPPLE");
#	endif
#	ifdef glTestObjectAPPLE
	_glTestObjectAPPLE = (glTestObjectAPPLEFunc)glGetFunction("glTestObjectAPPLE");
#	endif
#	ifdef glFinishObjectAPPLE
	_glFinishObjectAPPLE = (glFinishObjectAPPLEFunc)glGetFunction("glFinishObjectAPPLE");
#	endif
#	ifdef glBindVertexArrayAPPLE
	_glBindVertexArrayAPPLE = (glBindVertexArrayAPPLEFunc)glGetFunction("glBindVertexArrayAPPLE");
#	endif
#	ifdef glDeleteVertexArraysAPPLE
	_glDeleteVertexArraysAPPLE = (glDeleteVertexArraysAPPLEFunc)glGetFunction("glDeleteVertexArraysAPPLE");
#	endif
#	ifdef glGenVertexArraysAPPLE
	_glGenVertexArraysAPPLE = (glGenVertexArraysAPPLEFunc)glGetFunction("glGenVertexArraysAPPLE");
#	endif
#	ifdef glIsVertexArrayAPPLE
	_glIsVertexArrayAPPLE = (glIsVertexArrayAPPLEFunc)glGetFunction("glIsVertexArrayAPPLE");
#	endif
#	ifdef glVertexArrayRangeAPPLE
	_glVertexArrayRangeAPPLE = (glVertexArrayRangeAPPLEFunc)glGetFunction("glVertexArrayRangeAPPLE");
#	endif
#	ifdef glFlushVertexArrayRangeAPPLE
	_glFlushVertexArrayRangeAPPLE = (glFlushVertexArrayRangeAPPLEFunc)glGetFunction("glFlushVertexArrayRangeAPPLE");
#	endif
#	ifdef glVertexArrayParameteriAPPLE
	_glVertexArrayParameteriAPPLE = (glVertexArrayParameteriAPPLEFunc)glGetFunction("glVertexArrayParameteriAPPLE");
#	endif
#	ifdef glDrawBuffersATI
	_glDrawBuffersATI = (glDrawBuffersATIFunc)glGetFunction("glDrawBuffersATI");
#	endif
#	ifdef glProgramNamedParameter4fNV
	_glProgramNamedParameter4fNV = (glProgramNamedParameter4fNVFunc)glGetFunction("glProgramNamedParameter4fNV");
#	endif
#	ifdef glProgramNamedParameter4dNV
	_glProgramNamedParameter4dNV = (glProgramNamedParameter4dNVFunc)glGetFunction("glProgramNamedParameter4dNV");
#	endif
#	ifdef glProgramNamedParameter4fvNV
	_glProgramNamedParameter4fvNV = (glProgramNamedParameter4fvNVFunc)glGetFunction("glProgramNamedParameter4fvNV");
#	endif
#	ifdef glProgramNamedParameter4dvNV
	_glProgramNamedParameter4dvNV = (glProgramNamedParameter4dvNVFunc)glGetFunction("glProgramNamedParameter4dvNV");
#	endif
#	ifdef glGetProgramNamedParameterfvNV
	_glGetProgramNamedParameterfvNV = (glGetProgramNamedParameterfvNVFunc)glGetFunction("glGetProgramNamedParameterfvNV");
#	endif
#	ifdef glGetProgramNamedParameterdvNV
	_glGetProgramNamedParameterdvNV = (glGetProgramNamedParameterdvNVFunc)glGetFunction("glGetProgramNamedParameterdvNV");
#	endif
#	ifdef glVertex2hNV
	_glVertex2hNV = (glVertex2hNVFunc)glGetFunction("glVertex2hNV");
#	endif
#	ifdef glVertex2hvNV
	_glVertex2hvNV = (glVertex2hvNVFunc)glGetFunction("glVertex2hvNV");
#	endif
#	ifdef glVertex3hNV
	_glVertex3hNV = (glVertex3hNVFunc)glGetFunction("glVertex3hNV");
#	endif
#	ifdef glVertex3hvNV
	_glVertex3hvNV = (glVertex3hvNVFunc)glGetFunction("glVertex3hvNV");
#	endif
#	ifdef glVertex4hNV
	_glVertex4hNV = (glVertex4hNVFunc)glGetFunction("glVertex4hNV");
#	endif
#	ifdef glVertex4hvNV
	_glVertex4hvNV = (glVertex4hvNVFunc)glGetFunction("glVertex4hvNV");
#	endif
#	ifdef glNormal3hNV
	_glNormal3hNV = (glNormal3hNVFunc)glGetFunction("glNormal3hNV");
#	endif
#	ifdef glNormal3hvNV
	_glNormal3hvNV = (glNormal3hvNVFunc)glGetFunction("glNormal3hvNV");
#	endif
#	ifdef glColor3hNV
	_glColor3hNV = (glColor3hNVFunc)glGetFunction("glColor3hNV");
#	endif
#	ifdef glColor3hvNV
	_glColor3hvNV = (glColor3hvNVFunc)glGetFunction("glColor3hvNV");
#	endif
#	ifdef glColor4hNV
	_glColor4hNV = (glColor4hNVFunc)glGetFunction("glColor4hNV");
#	endif
#	ifdef glColor4hvNV
	_glColor4hvNV = (glColor4hvNVFunc)glGetFunction("glColor4hvNV");
#	endif
#	ifdef glTexCoord1hNV
	_glTexCoord1hNV = (glTexCoord1hNVFunc)glGetFunction("glTexCoord1hNV");
#	endif
#	ifdef glTexCoord1hvNV
	_glTexCoord1hvNV = (glTexCoord1hvNVFunc)glGetFunction("glTexCoord1hvNV");
#	endif
#	ifdef glTexCoord2hNV
	_glTexCoord2hNV = (glTexCoord2hNVFunc)glGetFunction("glTexCoord2hNV");
#	endif
#	ifdef glTexCoord2hvNV
	_glTexCoord2hvNV = (glTexCoord2hvNVFunc)glGetFunction("glTexCoord2hvNV");
#	endif
#	ifdef glTexCoord3hNV
	_glTexCoord3hNV = (glTexCoord3hNVFunc)glGetFunction("glTexCoord3hNV");
#	endif
#	ifdef glTexCoord3hvNV
	_glTexCoord3hvNV = (glTexCoord3hvNVFunc)glGetFunction("glTexCoord3hvNV");
#	endif
#	ifdef glTexCoord4hNV
	_glTexCoord4hNV = (glTexCoord4hNVFunc)glGetFunction("glTexCoord4hNV");
#	endif
#	ifdef glTexCoord4hvNV
	_glTexCoord4hvNV = (glTexCoord4hvNVFunc)glGetFunction("glTexCoord4hvNV");
#	endif
#	ifdef glMultiTexCoord1hNV
	_glMultiTexCoord1hNV = (glMultiTexCoord1hNVFunc)glGetFunction("glMultiTexCoord1hNV");
#	endif
#	ifdef glMultiTexCoord1hvNV
	_glMultiTexCoord1hvNV = (glMultiTexCoord1hvNVFunc)glGetFunction("glMultiTexCoord1hvNV");
#	endif
#	ifdef glMultiTexCoord2hNV
	_glMultiTexCoord2hNV = (glMultiTexCoord2hNVFunc)glGetFunction("glMultiTexCoord2hNV");
#	endif
#	ifdef glMultiTexCoord2hvNV
	_glMultiTexCoord2hvNV = (glMultiTexCoord2hvNVFunc)glGetFunction("glMultiTexCoord2hvNV");
#	endif
#	ifdef glMultiTexCoord3hNV
	_glMultiTexCoord3hNV = (glMultiTexCoord3hNVFunc)glGetFunction("glMultiTexCoord3hNV");
#	endif
#	ifdef glMultiTexCoord3hvNV
	_glMultiTexCoord3hvNV = (glMultiTexCoord3hvNVFunc)glGetFunction("glMultiTexCoord3hvNV");
#	endif
#	ifdef glMultiTexCoord4hNV
	_glMultiTexCoord4hNV = (glMultiTexCoord4hNVFunc)glGetFunction("glMultiTexCoord4hNV");
#	endif
#	ifdef glMultiTexCoord4hvNV
	_glMultiTexCoord4hvNV = (glMultiTexCoord4hvNVFunc)glGetFunction("glMultiTexCoord4hvNV");
#	endif
#	ifdef glFogCoordhNV
	_glFogCoordhNV = (glFogCoordhNVFunc)glGetFunction("glFogCoordhNV");
#	endif
#	ifdef glFogCoordhvNV
	_glFogCoordhvNV = (glFogCoordhvNVFunc)glGetFunction("glFogCoordhvNV");
#	endif
#	ifdef glSecondaryColor3hNV
	_glSecondaryColor3hNV = (glSecondaryColor3hNVFunc)glGetFunction("glSecondaryColor3hNV");
#	endif
#	ifdef glSecondaryColor3hvNV
	_glSecondaryColor3hvNV = (glSecondaryColor3hvNVFunc)glGetFunction("glSecondaryColor3hvNV");
#	endif
#	ifdef glVertexWeighthNV
	_glVertexWeighthNV = (glVertexWeighthNVFunc)glGetFunction("glVertexWeighthNV");
#	endif
#	ifdef glVertexWeighthvNV
	_glVertexWeighthvNV = (glVertexWeighthvNVFunc)glGetFunction("glVertexWeighthvNV");
#	endif
#	ifdef glVertexAttrib1hNV
	_glVertexAttrib1hNV = (glVertexAttrib1hNVFunc)glGetFunction("glVertexAttrib1hNV");
#	endif
#	ifdef glVertexAttrib1hvNV
	_glVertexAttrib1hvNV = (glVertexAttrib1hvNVFunc)glGetFunction("glVertexAttrib1hvNV");
#	endif
#	ifdef glVertexAttrib2hNV
	_glVertexAttrib2hNV = (glVertexAttrib2hNVFunc)glGetFunction("glVertexAttrib2hNV");
#	endif
#	ifdef glVertexAttrib2hvNV
	_glVertexAttrib2hvNV = (glVertexAttrib2hvNVFunc)glGetFunction("glVertexAttrib2hvNV");
#	endif
#	ifdef glVertexAttrib3hNV
	_glVertexAttrib3hNV = (glVertexAttrib3hNVFunc)glGetFunction("glVertexAttrib3hNV");
#	endif
#	ifdef glVertexAttrib3hvNV
	_glVertexAttrib3hvNV = (glVertexAttrib3hvNVFunc)glGetFunction("glVertexAttrib3hvNV");
#	endif
#	ifdef glVertexAttrib4hNV
	_glVertexAttrib4hNV = (glVertexAttrib4hNVFunc)glGetFunction("glVertexAttrib4hNV");
#	endif
#	ifdef glVertexAttrib4hvNV
	_glVertexAttrib4hvNV = (glVertexAttrib4hvNVFunc)glGetFunction("glVertexAttrib4hvNV");
#	endif
#	ifdef glVertexAttribs1hvNV
	_glVertexAttribs1hvNV = (glVertexAttribs1hvNVFunc)glGetFunction("glVertexAttribs1hvNV");
#	endif
#	ifdef glVertexAttribs2hvNV
	_glVertexAttribs2hvNV = (glVertexAttribs2hvNVFunc)glGetFunction("glVertexAttribs2hvNV");
#	endif
#	ifdef glVertexAttribs3hvNV
	_glVertexAttribs3hvNV = (glVertexAttribs3hvNVFunc)glGetFunction("glVertexAttribs3hvNV");
#	endif
#	ifdef glVertexAttribs4hvNV
	_glVertexAttribs4hvNV = (glVertexAttribs4hvNVFunc)glGetFunction("glVertexAttribs4hvNV");
#	endif
#	ifdef glPixelDataRangeNV
	_glPixelDataRangeNV = (glPixelDataRangeNVFunc)glGetFunction("glPixelDataRangeNV");
#	endif
#	ifdef glFlushPixelDataRangeNV
	_glFlushPixelDataRangeNV = (glFlushPixelDataRangeNVFunc)glGetFunction("glFlushPixelDataRangeNV");
#	endif
#	ifdef glPrimitiveRestartNV
	_glPrimitiveRestartNV = (glPrimitiveRestartNVFunc)glGetFunction("glPrimitiveRestartNV");
#	endif
#	ifdef glPrimitiveRestartIndexNV
	_glPrimitiveRestartIndexNV = (glPrimitiveRestartIndexNVFunc)glGetFunction("glPrimitiveRestartIndexNV");
#	endif
#	ifdef glMapObjectBufferATI
	_glMapObjectBufferATI = (glMapObjectBufferATIFunc)glGetFunction("glMapObjectBufferATI");
#	endif
#	ifdef glUnmapObjectBufferATI
	_glUnmapObjectBufferATI = (glUnmapObjectBufferATIFunc)glGetFunction("glUnmapObjectBufferATI");
#	endif
#	ifdef glStencilOpSeparateATI
	_glStencilOpSeparateATI = (glStencilOpSeparateATIFunc)glGetFunction("glStencilOpSeparateATI");
#	endif
#	ifdef glStencilFuncSeparateATI
	_glStencilFuncSeparateATI = (glStencilFuncSeparateATIFunc)glGetFunction("glStencilFuncSeparateATI");
#	endif
#	ifdef glVertexAttribArrayObjectATI
	_glVertexAttribArrayObjectATI = (glVertexAttribArrayObjectATIFunc)glGetFunction("glVertexAttribArrayObjectATI");
#	endif
#	ifdef glGetVertexAttribArrayObjectfvATI
	_glGetVertexAttribArrayObjectfvATI = (glGetVertexAttribArrayObjectfvATIFunc)glGetFunction("glGetVertexAttribArrayObjectfvATI");
#	endif
#	ifdef glGetVertexAttribArrayObjectivATI
	_glGetVertexAttribArrayObjectivATI = (glGetVertexAttribArrayObjectivATIFunc)glGetFunction("glGetVertexAttribArrayObjectivATI");
#	endif
#	ifdef glDepthBoundsEXT
	_glDepthBoundsEXT = (glDepthBoundsEXTFunc)glGetFunction("glDepthBoundsEXT");
#	endif
#	ifdef glBlendEquationSeparateEXT
	_glBlendEquationSeparateEXT = (glBlendEquationSeparateEXTFunc)glGetFunction("glBlendEquationSeparateEXT");
#	endif
#	ifdef glIsRenderbufferEXT
	_glIsRenderbufferEXT = (glIsRenderbufferEXTFunc)glGetFunction("glIsRenderbufferEXT");
#	endif
#	ifdef glBindRenderbufferEXT
	_glBindRenderbufferEXT = (glBindRenderbufferEXTFunc)glGetFunction("glBindRenderbufferEXT");
#	endif
#	ifdef glDeleteRenderbuffersEXT
	_glDeleteRenderbuffersEXT = (glDeleteRenderbuffersEXTFunc)glGetFunction("glDeleteRenderbuffersEXT");
#	endif
#	ifdef glGenRenderbuffersEXT
	_glGenRenderbuffersEXT = (glGenRenderbuffersEXTFunc)glGetFunction("glGenRenderbuffersEXT");
#	endif
#	ifdef glRenderbufferStorageEXT
	_glRenderbufferStorageEXT = (glRenderbufferStorageEXTFunc)glGetFunction("glRenderbufferStorageEXT");
#	endif
#	ifdef glGetRenderbufferParameterivEXT
	_glGetRenderbufferParameterivEXT = (glGetRenderbufferParameterivEXTFunc)glGetFunction("glGetRenderbufferParameterivEXT");
#	endif
#	ifdef glIsFramebufferEXT
	_glIsFramebufferEXT = (glIsFramebufferEXTFunc)glGetFunction("glIsFramebufferEXT");
#	endif
#	ifdef glBindFramebufferEXT
	_glBindFramebufferEXT = (glBindFramebufferEXTFunc)glGetFunction("glBindFramebufferEXT");
#	endif
#	ifdef glDeleteFramebuffersEXT
	_glDeleteFramebuffersEXT = (glDeleteFramebuffersEXTFunc)glGetFunction("glDeleteFramebuffersEXT");
#	endif
#	ifdef glGenFramebuffersEXT
	_glGenFramebuffersEXT = (glGenFramebuffersEXTFunc)glGetFunction("glGenFramebuffersEXT");
#	endif
#	ifdef glCheckFramebufferStatusEXT
	_glCheckFramebufferStatusEXT = (glCheckFramebufferStatusEXTFunc)glGetFunction("glCheckFramebufferStatusEXT");
#	endif
#	ifdef glFramebufferTexture1DEXT
	_glFramebufferTexture1DEXT = (glFramebufferTexture1DEXTFunc)glGetFunction("glFramebufferTexture1DEXT");
#	endif
#	ifdef glFramebufferTexture2DEXT
	_glFramebufferTexture2DEXT = (glFramebufferTexture2DEXTFunc)glGetFunction("glFramebufferTexture2DEXT");
#	endif
#	ifdef glFramebufferTexture3DEXT
	_glFramebufferTexture3DEXT = (glFramebufferTexture3DEXTFunc)glGetFunction("glFramebufferTexture3DEXT");
#	endif
#	ifdef glFramebufferRenderbufferEXT
	_glFramebufferRenderbufferEXT = (glFramebufferRenderbufferEXTFunc)glGetFunction("glFramebufferRenderbufferEXT");
#	endif
#	ifdef glGetFramebufferAttachmentParameterivEXT
	_glGetFramebufferAttachmentParameterivEXT = (glGetFramebufferAttachmentParameterivEXTFunc)glGetFunction("glGetFramebufferAttachmentParameterivEXT");
#	endif
#	ifdef glGenerateMipmapEXT
	_glGenerateMipmapEXT = (glGenerateMipmapEXTFunc)glGetFunction("glGenerateMipmapEXT");
#	endif
#	ifdef glStringMarkerGREMEDY
	_glStringMarkerGREMEDY = (glStringMarkerGREMEDYFunc)glGetFunction("glStringMarkerGREMEDY");
#	endif
#	ifdef glStencilClearTagEXT
	_glStencilClearTagEXT = (glStencilClearTagEXTFunc)glGetFunction("glStencilClearTagEXT");
#	endif
#	ifdef glBlitFramebufferEXT
	_glBlitFramebufferEXT = (glBlitFramebufferEXTFunc)glGetFunction("glBlitFramebufferEXT");
#	endif
#	ifdef glRenderbufferStorageMultisampleEXT
	_glRenderbufferStorageMultisampleEXT = (glRenderbufferStorageMultisampleEXTFunc)glGetFunction("glRenderbufferStorageMultisampleEXT");
#	endif
#	ifdef glGetQueryObjecti64vEXT
	_glGetQueryObjecti64vEXT = (glGetQueryObjecti64vEXTFunc)glGetFunction("glGetQueryObjecti64vEXT");
#	endif
#	ifdef glGetQueryObjectui64vEXT
	_glGetQueryObjectui64vEXT = (glGetQueryObjectui64vEXTFunc)glGetFunction("glGetQueryObjectui64vEXT");
#	endif
#	ifdef glProgramEnvParameters4fvEXT
	_glProgramEnvParameters4fvEXT = (glProgramEnvParameters4fvEXTFunc)glGetFunction("glProgramEnvParameters4fvEXT");
#	endif
#	ifdef glProgramLocalParameters4fvEXT
	_glProgramLocalParameters4fvEXT = (glProgramLocalParameters4fvEXTFunc)glGetFunction("glProgramLocalParameters4fvEXT");
#	endif
#	ifdef glBufferParameteriAPPLE
	_glBufferParameteriAPPLE = (glBufferParameteriAPPLEFunc)glGetFunction("glBufferParameteriAPPLE");
#	endif
#	ifdef glFlushMappedBufferRangeAPPLE
	_glFlushMappedBufferRangeAPPLE = (glFlushMappedBufferRangeAPPLEFunc)glGetFunction("glFlushMappedBufferRangeAPPLE");
#	endif
#	ifdef glProgramLocalParameterI4iNV
	_glProgramLocalParameterI4iNV = (glProgramLocalParameterI4iNVFunc)glGetFunction("glProgramLocalParameterI4iNV");
#	endif
#	ifdef glProgramLocalParameterI4ivNV
	_glProgramLocalParameterI4ivNV = (glProgramLocalParameterI4ivNVFunc)glGetFunction("glProgramLocalParameterI4ivNV");
#	endif
#	ifdef glProgramLocalParametersI4ivNV
	_glProgramLocalParametersI4ivNV = (glProgramLocalParametersI4ivNVFunc)glGetFunction("glProgramLocalParametersI4ivNV");
#	endif
#	ifdef glProgramLocalParameterI4uiNV
	_glProgramLocalParameterI4uiNV = (glProgramLocalParameterI4uiNVFunc)glGetFunction("glProgramLocalParameterI4uiNV");
#	endif
#	ifdef glProgramLocalParameterI4uivNV
	_glProgramLocalParameterI4uivNV = (glProgramLocalParameterI4uivNVFunc)glGetFunction("glProgramLocalParameterI4uivNV");
#	endif
#	ifdef glProgramLocalParametersI4uivNV
	_glProgramLocalParametersI4uivNV = (glProgramLocalParametersI4uivNVFunc)glGetFunction("glProgramLocalParametersI4uivNV");
#	endif
#	ifdef glProgramEnvParameterI4iNV
	_glProgramEnvParameterI4iNV = (glProgramEnvParameterI4iNVFunc)glGetFunction("glProgramEnvParameterI4iNV");
#	endif
#	ifdef glProgramEnvParameterI4ivNV
	_glProgramEnvParameterI4ivNV = (glProgramEnvParameterI4ivNVFunc)glGetFunction("glProgramEnvParameterI4ivNV");
#	endif
#	ifdef glProgramEnvParametersI4ivNV
	_glProgramEnvParametersI4ivNV = (glProgramEnvParametersI4ivNVFunc)glGetFunction("glProgramEnvParametersI4ivNV");
#	endif
#	ifdef glProgramEnvParameterI4uiNV
	_glProgramEnvParameterI4uiNV = (glProgramEnvParameterI4uiNVFunc)glGetFunction("glProgramEnvParameterI4uiNV");
#	endif
#	ifdef glProgramEnvParameterI4uivNV
	_glProgramEnvParameterI4uivNV = (glProgramEnvParameterI4uivNVFunc)glGetFunction("glProgramEnvParameterI4uivNV");
#	endif
#	ifdef glProgramEnvParametersI4uivNV
	_glProgramEnvParametersI4uivNV = (glProgramEnvParametersI4uivNVFunc)glGetFunction("glProgramEnvParametersI4uivNV");
#	endif
#	ifdef glGetProgramLocalParameterIivNV
	_glGetProgramLocalParameterIivNV = (glGetProgramLocalParameterIivNVFunc)glGetFunction("glGetProgramLocalParameterIivNV");
#	endif
#	ifdef glGetProgramLocalParameterIuivNV
	_glGetProgramLocalParameterIuivNV = (glGetProgramLocalParameterIuivNVFunc)glGetFunction("glGetProgramLocalParameterIuivNV");
#	endif
#	ifdef glGetProgramEnvParameterIivNV
	_glGetProgramEnvParameterIivNV = (glGetProgramEnvParameterIivNVFunc)glGetFunction("glGetProgramEnvParameterIivNV");
#	endif
#	ifdef glGetProgramEnvParameterIuivNV
	_glGetProgramEnvParameterIuivNV = (glGetProgramEnvParameterIuivNVFunc)glGetFunction("glGetProgramEnvParameterIuivNV");
#	endif
#	ifdef glProgramVertexLimitNV
	_glProgramVertexLimitNV = (glProgramVertexLimitNVFunc)glGetFunction("glProgramVertexLimitNV");
#	endif
#	ifdef glFramebufferTextureEXT
	_glFramebufferTextureEXT = (glFramebufferTextureEXTFunc)glGetFunction("glFramebufferTextureEXT");
#	endif
#	ifdef glFramebufferTextureLayerEXT
	_glFramebufferTextureLayerEXT = (glFramebufferTextureLayerEXTFunc)glGetFunction("glFramebufferTextureLayerEXT");
#	endif
#	ifdef glFramebufferTextureFaceEXT
	_glFramebufferTextureFaceEXT = (glFramebufferTextureFaceEXTFunc)glGetFunction("glFramebufferTextureFaceEXT");
#	endif
#	ifdef glProgramParameteriEXT
	_glProgramParameteriEXT = (glProgramParameteriEXTFunc)glGetFunction("glProgramParameteriEXT");
#	endif
#	ifdef glVertexAttribI1iEXT
	_glVertexAttribI1iEXT = (glVertexAttribI1iEXTFunc)glGetFunction("glVertexAttribI1iEXT");
#	endif
#	ifdef glVertexAttribI2iEXT
	_glVertexAttribI2iEXT = (glVertexAttribI2iEXTFunc)glGetFunction("glVertexAttribI2iEXT");
#	endif
#	ifdef glVertexAttribI3iEXT
	_glVertexAttribI3iEXT = (glVertexAttribI3iEXTFunc)glGetFunction("glVertexAttribI3iEXT");
#	endif
#	ifdef glVertexAttribI4iEXT
	_glVertexAttribI4iEXT = (glVertexAttribI4iEXTFunc)glGetFunction("glVertexAttribI4iEXT");
#	endif
#	ifdef glVertexAttribI1uiEXT
	_glVertexAttribI1uiEXT = (glVertexAttribI1uiEXTFunc)glGetFunction("glVertexAttribI1uiEXT");
#	endif
#	ifdef glVertexAttribI2uiEXT
	_glVertexAttribI2uiEXT = (glVertexAttribI2uiEXTFunc)glGetFunction("glVertexAttribI2uiEXT");
#	endif
#	ifdef glVertexAttribI3uiEXT
	_glVertexAttribI3uiEXT = (glVertexAttribI3uiEXTFunc)glGetFunction("glVertexAttribI3uiEXT");
#	endif
#	ifdef glVertexAttribI4uiEXT
	_glVertexAttribI4uiEXT = (glVertexAttribI4uiEXTFunc)glGetFunction("glVertexAttribI4uiEXT");
#	endif
#	ifdef glVertexAttribI1ivEXT
	_glVertexAttribI1ivEXT = (glVertexAttribI1ivEXTFunc)glGetFunction("glVertexAttribI1ivEXT");
#	endif
#	ifdef glVertexAttribI2ivEXT
	_glVertexAttribI2ivEXT = (glVertexAttribI2ivEXTFunc)glGetFunction("glVertexAttribI2ivEXT");
#	endif
#	ifdef glVertexAttribI3ivEXT
	_glVertexAttribI3ivEXT = (glVertexAttribI3ivEXTFunc)glGetFunction("glVertexAttribI3ivEXT");
#	endif
#	ifdef glVertexAttribI4ivEXT
	_glVertexAttribI4ivEXT = (glVertexAttribI4ivEXTFunc)glGetFunction("glVertexAttribI4ivEXT");
#	endif
#	ifdef glVertexAttribI1uivEXT
	_glVertexAttribI1uivEXT = (glVertexAttribI1uivEXTFunc)glGetFunction("glVertexAttribI1uivEXT");
#	endif
#	ifdef glVertexAttribI2uivEXT
	_glVertexAttribI2uivEXT = (glVertexAttribI2uivEXTFunc)glGetFunction("glVertexAttribI2uivEXT");
#	endif
#	ifdef glVertexAttribI3uivEXT
	_glVertexAttribI3uivEXT = (glVertexAttribI3uivEXTFunc)glGetFunction("glVertexAttribI3uivEXT");
#	endif
#	ifdef glVertexAttribI4uivEXT
	_glVertexAttribI4uivEXT = (glVertexAttribI4uivEXTFunc)glGetFunction("glVertexAttribI4uivEXT");
#	endif
#	ifdef glVertexAttribI4bvEXT
	_glVertexAttribI4bvEXT = (glVertexAttribI4bvEXTFunc)glGetFunction("glVertexAttribI4bvEXT");
#	endif
#	ifdef glVertexAttribI4svEXT
	_glVertexAttribI4svEXT = (glVertexAttribI4svEXTFunc)glGetFunction("glVertexAttribI4svEXT");
#	endif
#	ifdef glVertexAttribI4ubvEXT
	_glVertexAttribI4ubvEXT = (glVertexAttribI4ubvEXTFunc)glGetFunction("glVertexAttribI4ubvEXT");
#	endif
#	ifdef glVertexAttribI4usvEXT
	_glVertexAttribI4usvEXT = (glVertexAttribI4usvEXTFunc)glGetFunction("glVertexAttribI4usvEXT");
#	endif
#	ifdef glVertexAttribIPointerEXT
	_glVertexAttribIPointerEXT = (glVertexAttribIPointerEXTFunc)glGetFunction("glVertexAttribIPointerEXT");
#	endif
#	ifdef glGetVertexAttribIivEXT
	_glGetVertexAttribIivEXT = (glGetVertexAttribIivEXTFunc)glGetFunction("glGetVertexAttribIivEXT");
#	endif
#	ifdef glGetVertexAttribIuivEXT
	_glGetVertexAttribIuivEXT = (glGetVertexAttribIuivEXTFunc)glGetFunction("glGetVertexAttribIuivEXT");
#	endif
#	ifdef glGetUniformuivEXT
	_glGetUniformuivEXT = (glGetUniformuivEXTFunc)glGetFunction("glGetUniformuivEXT");
#	endif
#	ifdef glBindFragDataLocationEXT
	_glBindFragDataLocationEXT = (glBindFragDataLocationEXTFunc)glGetFunction("glBindFragDataLocationEXT");
#	endif
#	ifdef glGetFragDataLocationEXT
	_glGetFragDataLocationEXT = (glGetFragDataLocationEXTFunc)glGetFunction("glGetFragDataLocationEXT");
#	endif
#	ifdef glUniform1uiEXT
	_glUniform1uiEXT = (glUniform1uiEXTFunc)glGetFunction("glUniform1uiEXT");
#	endif
#	ifdef glUniform2uiEXT
	_glUniform2uiEXT = (glUniform2uiEXTFunc)glGetFunction("glUniform2uiEXT");
#	endif
#	ifdef glUniform3uiEXT
	_glUniform3uiEXT = (glUniform3uiEXTFunc)glGetFunction("glUniform3uiEXT");
#	endif
#	ifdef glUniform4uiEXT
	_glUniform4uiEXT = (glUniform4uiEXTFunc)glGetFunction("glUniform4uiEXT");
#	endif
#	ifdef glUniform1uivEXT
	_glUniform1uivEXT = (glUniform1uivEXTFunc)glGetFunction("glUniform1uivEXT");
#	endif
#	ifdef glUniform2uivEXT
	_glUniform2uivEXT = (glUniform2uivEXTFunc)glGetFunction("glUniform2uivEXT");
#	endif
#	ifdef glUniform3uivEXT
	_glUniform3uivEXT = (glUniform3uivEXTFunc)glGetFunction("glUniform3uivEXT");
#	endif
#	ifdef glUniform4uivEXT
	_glUniform4uivEXT = (glUniform4uivEXTFunc)glGetFunction("glUniform4uivEXT");
#	endif
#	ifdef glDrawArraysInstancedEXT
	_glDrawArraysInstancedEXT = (glDrawArraysInstancedEXTFunc)glGetFunction("glDrawArraysInstancedEXT");
#	endif
#	ifdef glDrawElementsInstancedEXT
	_glDrawElementsInstancedEXT = (glDrawElementsInstancedEXTFunc)glGetFunction("glDrawElementsInstancedEXT");
#	endif
#	ifdef glTexBufferEXT
	_glTexBufferEXT = (glTexBufferEXTFunc)glGetFunction("glTexBufferEXT");
#	endif
#	ifdef glDepthRangedNV
	_glDepthRangedNV = (glDepthRangedNVFunc)glGetFunction("glDepthRangedNV");
#	endif
#	ifdef glClearDepthdNV
	_glClearDepthdNV = (glClearDepthdNVFunc)glGetFunction("glClearDepthdNV");
#	endif
#	ifdef glDepthBoundsdNV
	_glDepthBoundsdNV = (glDepthBoundsdNVFunc)glGetFunction("glDepthBoundsdNV");
#	endif
#	ifdef glRenderbufferStorageMultisampleCoverageNV
	_glRenderbufferStorageMultisampleCoverageNV = (glRenderbufferStorageMultisampleCoverageNVFunc)glGetFunction("glRenderbufferStorageMultisampleCoverageNV");
#	endif
#	ifdef glProgramBufferParametersfvNV
	_glProgramBufferParametersfvNV = (glProgramBufferParametersfvNVFunc)glGetFunction("glProgramBufferParametersfvNV");
#	endif
#	ifdef glProgramBufferParametersIivNV
	_glProgramBufferParametersIivNV = (glProgramBufferParametersIivNVFunc)glGetFunction("glProgramBufferParametersIivNV");
#	endif
#	ifdef glProgramBufferParametersIuivNV
	_glProgramBufferParametersIuivNV = (glProgramBufferParametersIuivNVFunc)glGetFunction("glProgramBufferParametersIuivNV");
#	endif
#	ifdef glColorMaskIndexedEXT
	_glColorMaskIndexedEXT = (glColorMaskIndexedEXTFunc)glGetFunction("glColorMaskIndexedEXT");
#	endif
#	ifdef glGetBooleanIndexedvEXT
	_glGetBooleanIndexedvEXT = (glGetBooleanIndexedvEXTFunc)glGetFunction("glGetBooleanIndexedvEXT");
#	endif
#	ifdef glGetIntegerIndexedvEXT
	_glGetIntegerIndexedvEXT = (glGetIntegerIndexedvEXTFunc)glGetFunction("glGetIntegerIndexedvEXT");
#	endif
#	ifdef glEnableIndexedEXT
	_glEnableIndexedEXT = (glEnableIndexedEXTFunc)glGetFunction("glEnableIndexedEXT");
#	endif
#	ifdef glDisableIndexedEXT
	_glDisableIndexedEXT = (glDisableIndexedEXTFunc)glGetFunction("glDisableIndexedEXT");
#	endif
#	ifdef glIsEnabledIndexedEXT
	_glIsEnabledIndexedEXT = (glIsEnabledIndexedEXTFunc)glGetFunction("glIsEnabledIndexedEXT");
#	endif
#	ifdef glBeginTransformFeedbackNV
	_glBeginTransformFeedbackNV = (glBeginTransformFeedbackNVFunc)glGetFunction("glBeginTransformFeedbackNV");
#	endif
#	ifdef glEndTransformFeedbackNV
	_glEndTransformFeedbackNV = (glEndTransformFeedbackNVFunc)glGetFunction("glEndTransformFeedbackNV");
#	endif
#	ifdef glTransformFeedbackAttribsNV
	_glTransformFeedbackAttribsNV = (glTransformFeedbackAttribsNVFunc)glGetFunction("glTransformFeedbackAttribsNV");
#	endif
#	ifdef glBindBufferRangeNV
	_glBindBufferRangeNV = (glBindBufferRangeNVFunc)glGetFunction("glBindBufferRangeNV");
#	endif
#	ifdef glBindBufferOffsetNV
	_glBindBufferOffsetNV = (glBindBufferOffsetNVFunc)glGetFunction("glBindBufferOffsetNV");
#	endif
#	ifdef glBindBufferBaseNV
	_glBindBufferBaseNV = (glBindBufferBaseNVFunc)glGetFunction("glBindBufferBaseNV");
#	endif
#	ifdef glTransformFeedbackVaryingsNV
	_glTransformFeedbackVaryingsNV = (glTransformFeedbackVaryingsNVFunc)glGetFunction("glTransformFeedbackVaryingsNV");
#	endif
#	ifdef glActiveVaryingNV
	_glActiveVaryingNV = (glActiveVaryingNVFunc)glGetFunction("glActiveVaryingNV");
#	endif
#	ifdef glGetVaryingLocationNV
	_glGetVaryingLocationNV = (glGetVaryingLocationNVFunc)glGetFunction("glGetVaryingLocationNV");
#	endif
#	ifdef glGetActiveVaryingNV
	_glGetActiveVaryingNV = (glGetActiveVaryingNVFunc)glGetFunction("glGetActiveVaryingNV");
#	endif
#	ifdef glGetTransformFeedbackVaryingNV
	_glGetTransformFeedbackVaryingNV = (glGetTransformFeedbackVaryingNVFunc)glGetFunction("glGetTransformFeedbackVaryingNV");
#	endif
#	ifdef glTransformFeedbackStreamAttribsNV
	_glTransformFeedbackStreamAttribsNV = (glTransformFeedbackStreamAttribsNVFunc)glGetFunction("glTransformFeedbackStreamAttribsNV");
#	endif
#	ifdef glUniformBufferEXT
	_glUniformBufferEXT = (glUniformBufferEXTFunc)glGetFunction("glUniformBufferEXT");
#	endif
#	ifdef glGetUniformBufferSizeEXT
	_glGetUniformBufferSizeEXT = (glGetUniformBufferSizeEXTFunc)glGetFunction("glGetUniformBufferSizeEXT");
#	endif
#	ifdef glGetUniformOffsetEXT
	_glGetUniformOffsetEXT = (glGetUniformOffsetEXTFunc)glGetFunction("glGetUniformOffsetEXT");
#	endif
#	ifdef glTexParameterIivEXT
	_glTexParameterIivEXT = (glTexParameterIivEXTFunc)glGetFunction("glTexParameterIivEXT");
#	endif
#	ifdef glTexParameterIuivEXT
	_glTexParameterIuivEXT = (glTexParameterIuivEXTFunc)glGetFunction("glTexParameterIuivEXT");
#	endif
#	ifdef glGetTexParameterIivEXT
	_glGetTexParameterIivEXT = (glGetTexParameterIivEXTFunc)glGetFunction("glGetTexParameterIivEXT");
#	endif
#	ifdef glGetTexParameterIuivEXT
	_glGetTexParameterIuivEXT = (glGetTexParameterIuivEXTFunc)glGetFunction("glGetTexParameterIuivEXT");
#	endif
#	ifdef glClearColorIiEXT
	_glClearColorIiEXT = (glClearColorIiEXTFunc)glGetFunction("glClearColorIiEXT");
#	endif
#	ifdef glClearColorIuiEXT
	_glClearColorIuiEXT = (glClearColorIuiEXTFunc)glGetFunction("glClearColorIuiEXT");
#	endif
#	ifdef glFrameTerminatorGREMEDY
	_glFrameTerminatorGREMEDY = (glFrameTerminatorGREMEDYFunc)glGetFunction("glFrameTerminatorGREMEDY");
#	endif
#	ifdef glBeginConditionalRenderNV
	_glBeginConditionalRenderNV = (glBeginConditionalRenderNVFunc)glGetFunction("glBeginConditionalRenderNV");
#	endif
#	ifdef glEndConditionalRenderNV
	_glEndConditionalRenderNV = (glEndConditionalRenderNVFunc)glGetFunction("glEndConditionalRenderNV");
#	endif
#	ifdef glPresentFrameKeyedNV
	_glPresentFrameKeyedNV = (glPresentFrameKeyedNVFunc)glGetFunction("glPresentFrameKeyedNV");
#	endif
#	ifdef glPresentFrameDualFillNV
	_glPresentFrameDualFillNV = (glPresentFrameDualFillNVFunc)glGetFunction("glPresentFrameDualFillNV");
#	endif
#	ifdef glGetVideoivNV
	_glGetVideoivNV = (glGetVideoivNVFunc)glGetFunction("glGetVideoivNV");
#	endif
#	ifdef glGetVideouivNV
	_glGetVideouivNV = (glGetVideouivNVFunc)glGetFunction("glGetVideouivNV");
#	endif
#	ifdef glGetVideoi64vNV
	_glGetVideoi64vNV = (glGetVideoi64vNVFunc)glGetFunction("glGetVideoi64vNV");
#	endif
#	ifdef glGetVideoui64vNV
	_glGetVideoui64vNV = (glGetVideoui64vNVFunc)glGetFunction("glGetVideoui64vNV");
#	endif
#	ifdef glBeginTransformFeedbackEXT
	_glBeginTransformFeedbackEXT = (glBeginTransformFeedbackEXTFunc)glGetFunction("glBeginTransformFeedbackEXT");
#	endif
#	ifdef glEndTransformFeedbackEXT
	_glEndTransformFeedbackEXT = (glEndTransformFeedbackEXTFunc)glGetFunction("glEndTransformFeedbackEXT");
#	endif
#	ifdef glBindBufferRangeEXT
	_glBindBufferRangeEXT = (glBindBufferRangeEXTFunc)glGetFunction("glBindBufferRangeEXT");
#	endif
#	ifdef glBindBufferOffsetEXT
	_glBindBufferOffsetEXT = (glBindBufferOffsetEXTFunc)glGetFunction("glBindBufferOffsetEXT");
#	endif
#	ifdef glBindBufferBaseEXT
	_glBindBufferBaseEXT = (glBindBufferBaseEXTFunc)glGetFunction("glBindBufferBaseEXT");
#	endif
#	ifdef glTransformFeedbackVaryingsEXT
	_glTransformFeedbackVaryingsEXT = (glTransformFeedbackVaryingsEXTFunc)glGetFunction("glTransformFeedbackVaryingsEXT");
#	endif
#	ifdef glGetTransformFeedbackVaryingEXT
	_glGetTransformFeedbackVaryingEXT = (glGetTransformFeedbackVaryingEXTFunc)glGetFunction("glGetTransformFeedbackVaryingEXT");
#	endif
#	ifdef glClientAttribDefaultEXT
	_glClientAttribDefaultEXT = (glClientAttribDefaultEXTFunc)glGetFunction("glClientAttribDefaultEXT");
#	endif
#	ifdef glPushClientAttribDefaultEXT
	_glPushClientAttribDefaultEXT = (glPushClientAttribDefaultEXTFunc)glGetFunction("glPushClientAttribDefaultEXT");
#	endif
#	ifdef glMatrixLoadfEXT
	_glMatrixLoadfEXT = (glMatrixLoadfEXTFunc)glGetFunction("glMatrixLoadfEXT");
#	endif
#	ifdef glMatrixLoaddEXT
	_glMatrixLoaddEXT = (glMatrixLoaddEXTFunc)glGetFunction("glMatrixLoaddEXT");
#	endif
#	ifdef glMatrixMultfEXT
	_glMatrixMultfEXT = (glMatrixMultfEXTFunc)glGetFunction("glMatrixMultfEXT");
#	endif
#	ifdef glMatrixMultdEXT
	_glMatrixMultdEXT = (glMatrixMultdEXTFunc)glGetFunction("glMatrixMultdEXT");
#	endif
#	ifdef glMatrixLoadIdentityEXT
	_glMatrixLoadIdentityEXT = (glMatrixLoadIdentityEXTFunc)glGetFunction("glMatrixLoadIdentityEXT");
#	endif
#	ifdef glMatrixRotatefEXT
	_glMatrixRotatefEXT = (glMatrixRotatefEXTFunc)glGetFunction("glMatrixRotatefEXT");
#	endif
#	ifdef glMatrixRotatedEXT
	_glMatrixRotatedEXT = (glMatrixRotatedEXTFunc)glGetFunction("glMatrixRotatedEXT");
#	endif
#	ifdef glMatrixScalefEXT
	_glMatrixScalefEXT = (glMatrixScalefEXTFunc)glGetFunction("glMatrixScalefEXT");
#	endif
#	ifdef glMatrixScaledEXT
	_glMatrixScaledEXT = (glMatrixScaledEXTFunc)glGetFunction("glMatrixScaledEXT");
#	endif
#	ifdef glMatrixTranslatefEXT
	_glMatrixTranslatefEXT = (glMatrixTranslatefEXTFunc)glGetFunction("glMatrixTranslatefEXT");
#	endif
#	ifdef glMatrixTranslatedEXT
	_glMatrixTranslatedEXT = (glMatrixTranslatedEXTFunc)glGetFunction("glMatrixTranslatedEXT");
#	endif
#	ifdef glMatrixFrustumEXT
	_glMatrixFrustumEXT = (glMatrixFrustumEXTFunc)glGetFunction("glMatrixFrustumEXT");
#	endif
#	ifdef glMatrixOrthoEXT
	_glMatrixOrthoEXT = (glMatrixOrthoEXTFunc)glGetFunction("glMatrixOrthoEXT");
#	endif
#	ifdef glMatrixPopEXT
	_glMatrixPopEXT = (glMatrixPopEXTFunc)glGetFunction("glMatrixPopEXT");
#	endif
#	ifdef glMatrixPushEXT
	_glMatrixPushEXT = (glMatrixPushEXTFunc)glGetFunction("glMatrixPushEXT");
#	endif
#	ifdef glMatrixLoadTransposefEXT
	_glMatrixLoadTransposefEXT = (glMatrixLoadTransposefEXTFunc)glGetFunction("glMatrixLoadTransposefEXT");
#	endif
#	ifdef glMatrixLoadTransposedEXT
	_glMatrixLoadTransposedEXT = (glMatrixLoadTransposedEXTFunc)glGetFunction("glMatrixLoadTransposedEXT");
#	endif
#	ifdef glMatrixMultTransposefEXT
	_glMatrixMultTransposefEXT = (glMatrixMultTransposefEXTFunc)glGetFunction("glMatrixMultTransposefEXT");
#	endif
#	ifdef glMatrixMultTransposedEXT
	_glMatrixMultTransposedEXT = (glMatrixMultTransposedEXTFunc)glGetFunction("glMatrixMultTransposedEXT");
#	endif
#	ifdef glTextureParameterfEXT
	_glTextureParameterfEXT = (glTextureParameterfEXTFunc)glGetFunction("glTextureParameterfEXT");
#	endif
#	ifdef glTextureParameterfvEXT
	_glTextureParameterfvEXT = (glTextureParameterfvEXTFunc)glGetFunction("glTextureParameterfvEXT");
#	endif
#	ifdef glTextureParameteriEXT
	_glTextureParameteriEXT = (glTextureParameteriEXTFunc)glGetFunction("glTextureParameteriEXT");
#	endif
#	ifdef glTextureParameterivEXT
	_glTextureParameterivEXT = (glTextureParameterivEXTFunc)glGetFunction("glTextureParameterivEXT");
#	endif
#	ifdef glTextureImage1DEXT
	_glTextureImage1DEXT = (glTextureImage1DEXTFunc)glGetFunction("glTextureImage1DEXT");
#	endif
#	ifdef glTextureImage2DEXT
	_glTextureImage2DEXT = (glTextureImage2DEXTFunc)glGetFunction("glTextureImage2DEXT");
#	endif
#	ifdef glTextureSubImage1DEXT
	_glTextureSubImage1DEXT = (glTextureSubImage1DEXTFunc)glGetFunction("glTextureSubImage1DEXT");
#	endif
#	ifdef glTextureSubImage2DEXT
	_glTextureSubImage2DEXT = (glTextureSubImage2DEXTFunc)glGetFunction("glTextureSubImage2DEXT");
#	endif
#	ifdef glCopyTextureImage1DEXT
	_glCopyTextureImage1DEXT = (glCopyTextureImage1DEXTFunc)glGetFunction("glCopyTextureImage1DEXT");
#	endif
#	ifdef glCopyTextureImage2DEXT
	_glCopyTextureImage2DEXT = (glCopyTextureImage2DEXTFunc)glGetFunction("glCopyTextureImage2DEXT");
#	endif
#	ifdef glCopyTextureSubImage1DEXT
	_glCopyTextureSubImage1DEXT = (glCopyTextureSubImage1DEXTFunc)glGetFunction("glCopyTextureSubImage1DEXT");
#	endif
#	ifdef glCopyTextureSubImage2DEXT
	_glCopyTextureSubImage2DEXT = (glCopyTextureSubImage2DEXTFunc)glGetFunction("glCopyTextureSubImage2DEXT");
#	endif
#	ifdef glGetTextureImageEXT
	_glGetTextureImageEXT = (glGetTextureImageEXTFunc)glGetFunction("glGetTextureImageEXT");
#	endif
#	ifdef glGetTextureParameterfvEXT
	_glGetTextureParameterfvEXT = (glGetTextureParameterfvEXTFunc)glGetFunction("glGetTextureParameterfvEXT");
#	endif
#	ifdef glGetTextureParameterivEXT
	_glGetTextureParameterivEXT = (glGetTextureParameterivEXTFunc)glGetFunction("glGetTextureParameterivEXT");
#	endif
#	ifdef glGetTextureLevelParameterfvEXT
	_glGetTextureLevelParameterfvEXT = (glGetTextureLevelParameterfvEXTFunc)glGetFunction("glGetTextureLevelParameterfvEXT");
#	endif
#	ifdef glGetTextureLevelParameterivEXT
	_glGetTextureLevelParameterivEXT = (glGetTextureLevelParameterivEXTFunc)glGetFunction("glGetTextureLevelParameterivEXT");
#	endif
#	ifdef glTextureImage3DEXT
	_glTextureImage3DEXT = (glTextureImage3DEXTFunc)glGetFunction("glTextureImage3DEXT");
#	endif
#	ifdef glTextureSubImage3DEXT
	_glTextureSubImage3DEXT = (glTextureSubImage3DEXTFunc)glGetFunction("glTextureSubImage3DEXT");
#	endif
#	ifdef glCopyTextureSubImage3DEXT
	_glCopyTextureSubImage3DEXT = (glCopyTextureSubImage3DEXTFunc)glGetFunction("glCopyTextureSubImage3DEXT");
#	endif
#	ifdef glMultiTexParameterfEXT
	_glMultiTexParameterfEXT = (glMultiTexParameterfEXTFunc)glGetFunction("glMultiTexParameterfEXT");
#	endif
#	ifdef glMultiTexParameterfvEXT
	_glMultiTexParameterfvEXT = (glMultiTexParameterfvEXTFunc)glGetFunction("glMultiTexParameterfvEXT");
#	endif
#	ifdef glMultiTexParameteriEXT
	_glMultiTexParameteriEXT = (glMultiTexParameteriEXTFunc)glGetFunction("glMultiTexParameteriEXT");
#	endif
#	ifdef glMultiTexParameterivEXT
	_glMultiTexParameterivEXT = (glMultiTexParameterivEXTFunc)glGetFunction("glMultiTexParameterivEXT");
#	endif
#	ifdef glMultiTexImage1DEXT
	_glMultiTexImage1DEXT = (glMultiTexImage1DEXTFunc)glGetFunction("glMultiTexImage1DEXT");
#	endif
#	ifdef glMultiTexImage2DEXT
	_glMultiTexImage2DEXT = (glMultiTexImage2DEXTFunc)glGetFunction("glMultiTexImage2DEXT");
#	endif
#	ifdef glMultiTexSubImage1DEXT
	_glMultiTexSubImage1DEXT = (glMultiTexSubImage1DEXTFunc)glGetFunction("glMultiTexSubImage1DEXT");
#	endif
#	ifdef glMultiTexSubImage2DEXT
	_glMultiTexSubImage2DEXT = (glMultiTexSubImage2DEXTFunc)glGetFunction("glMultiTexSubImage2DEXT");
#	endif
#	ifdef glCopyMultiTexImage1DEXT
	_glCopyMultiTexImage1DEXT = (glCopyMultiTexImage1DEXTFunc)glGetFunction("glCopyMultiTexImage1DEXT");
#	endif
#	ifdef glCopyMultiTexImage2DEXT
	_glCopyMultiTexImage2DEXT = (glCopyMultiTexImage2DEXTFunc)glGetFunction("glCopyMultiTexImage2DEXT");
#	endif
#	ifdef glCopyMultiTexSubImage1DEXT
	_glCopyMultiTexSubImage1DEXT = (glCopyMultiTexSubImage1DEXTFunc)glGetFunction("glCopyMultiTexSubImage1DEXT");
#	endif
#	ifdef glCopyMultiTexSubImage2DEXT
	_glCopyMultiTexSubImage2DEXT = (glCopyMultiTexSubImage2DEXTFunc)glGetFunction("glCopyMultiTexSubImage2DEXT");
#	endif
#	ifdef glGetMultiTexImageEXT
	_glGetMultiTexImageEXT = (glGetMultiTexImageEXTFunc)glGetFunction("glGetMultiTexImageEXT");
#	endif
#	ifdef glGetMultiTexParameterfvEXT
	_glGetMultiTexParameterfvEXT = (glGetMultiTexParameterfvEXTFunc)glGetFunction("glGetMultiTexParameterfvEXT");
#	endif
#	ifdef glGetMultiTexParameterivEXT
	_glGetMultiTexParameterivEXT = (glGetMultiTexParameterivEXTFunc)glGetFunction("glGetMultiTexParameterivEXT");
#	endif
#	ifdef glGetMultiTexLevelParameterfvEXT
	_glGetMultiTexLevelParameterfvEXT = (glGetMultiTexLevelParameterfvEXTFunc)glGetFunction("glGetMultiTexLevelParameterfvEXT");
#	endif
#	ifdef glGetMultiTexLevelParameterivEXT
	_glGetMultiTexLevelParameterivEXT = (glGetMultiTexLevelParameterivEXTFunc)glGetFunction("glGetMultiTexLevelParameterivEXT");
#	endif
#	ifdef glMultiTexImage3DEXT
	_glMultiTexImage3DEXT = (glMultiTexImage3DEXTFunc)glGetFunction("glMultiTexImage3DEXT");
#	endif
#	ifdef glMultiTexSubImage3DEXT
	_glMultiTexSubImage3DEXT = (glMultiTexSubImage3DEXTFunc)glGetFunction("glMultiTexSubImage3DEXT");
#	endif
#	ifdef glCopyMultiTexSubImage3DEXT
	_glCopyMultiTexSubImage3DEXT = (glCopyMultiTexSubImage3DEXTFunc)glGetFunction("glCopyMultiTexSubImage3DEXT");
#	endif
#	ifdef glBindMultiTextureEXT
	_glBindMultiTextureEXT = (glBindMultiTextureEXTFunc)glGetFunction("glBindMultiTextureEXT");
#	endif
#	ifdef glEnableClientStateIndexedEXT
	_glEnableClientStateIndexedEXT = (glEnableClientStateIndexedEXTFunc)glGetFunction("glEnableClientStateIndexedEXT");
#	endif
#	ifdef glDisableClientStateIndexedEXT
	_glDisableClientStateIndexedEXT = (glDisableClientStateIndexedEXTFunc)glGetFunction("glDisableClientStateIndexedEXT");
#	endif
#	ifdef glMultiTexCoordPointerEXT
	_glMultiTexCoordPointerEXT = (glMultiTexCoordPointerEXTFunc)glGetFunction("glMultiTexCoordPointerEXT");
#	endif
#	ifdef glMultiTexEnvfEXT
	_glMultiTexEnvfEXT = (glMultiTexEnvfEXTFunc)glGetFunction("glMultiTexEnvfEXT");
#	endif
#	ifdef glMultiTexEnvfvEXT
	_glMultiTexEnvfvEXT = (glMultiTexEnvfvEXTFunc)glGetFunction("glMultiTexEnvfvEXT");
#	endif
#	ifdef glMultiTexEnviEXT
	_glMultiTexEnviEXT = (glMultiTexEnviEXTFunc)glGetFunction("glMultiTexEnviEXT");
#	endif
#	ifdef glMultiTexEnvivEXT
	_glMultiTexEnvivEXT = (glMultiTexEnvivEXTFunc)glGetFunction("glMultiTexEnvivEXT");
#	endif
#	ifdef glMultiTexGendEXT
	_glMultiTexGendEXT = (glMultiTexGendEXTFunc)glGetFunction("glMultiTexGendEXT");
#	endif
#	ifdef glMultiTexGendvEXT
	_glMultiTexGendvEXT = (glMultiTexGendvEXTFunc)glGetFunction("glMultiTexGendvEXT");
#	endif
#	ifdef glMultiTexGenfEXT
	_glMultiTexGenfEXT = (glMultiTexGenfEXTFunc)glGetFunction("glMultiTexGenfEXT");
#	endif
#	ifdef glMultiTexGenfvEXT
	_glMultiTexGenfvEXT = (glMultiTexGenfvEXTFunc)glGetFunction("glMultiTexGenfvEXT");
#	endif
#	ifdef glMultiTexGeniEXT
	_glMultiTexGeniEXT = (glMultiTexGeniEXTFunc)glGetFunction("glMultiTexGeniEXT");
#	endif
#	ifdef glMultiTexGenivEXT
	_glMultiTexGenivEXT = (glMultiTexGenivEXTFunc)glGetFunction("glMultiTexGenivEXT");
#	endif
#	ifdef glGetMultiTexEnvfvEXT
	_glGetMultiTexEnvfvEXT = (glGetMultiTexEnvfvEXTFunc)glGetFunction("glGetMultiTexEnvfvEXT");
#	endif
#	ifdef glGetMultiTexEnvivEXT
	_glGetMultiTexEnvivEXT = (glGetMultiTexEnvivEXTFunc)glGetFunction("glGetMultiTexEnvivEXT");
#	endif
#	ifdef glGetMultiTexGendvEXT
	_glGetMultiTexGendvEXT = (glGetMultiTexGendvEXTFunc)glGetFunction("glGetMultiTexGendvEXT");
#	endif
#	ifdef glGetMultiTexGenfvEXT
	_glGetMultiTexGenfvEXT = (glGetMultiTexGenfvEXTFunc)glGetFunction("glGetMultiTexGenfvEXT");
#	endif
#	ifdef glGetMultiTexGenivEXT
	_glGetMultiTexGenivEXT = (glGetMultiTexGenivEXTFunc)glGetFunction("glGetMultiTexGenivEXT");
#	endif
#	ifdef glGetFloatIndexedvEXT
	_glGetFloatIndexedvEXT = (glGetFloatIndexedvEXTFunc)glGetFunction("glGetFloatIndexedvEXT");
#	endif
#	ifdef glGetDoubleIndexedvEXT
	_glGetDoubleIndexedvEXT = (glGetDoubleIndexedvEXTFunc)glGetFunction("glGetDoubleIndexedvEXT");
#	endif
#	ifdef glGetPointerIndexedvEXT
	_glGetPointerIndexedvEXT = (glGetPointerIndexedvEXTFunc)glGetFunction("glGetPointerIndexedvEXT");
#	endif
#	ifdef glCompressedTextureImage3DEXT
	_glCompressedTextureImage3DEXT = (glCompressedTextureImage3DEXTFunc)glGetFunction("glCompressedTextureImage3DEXT");
#	endif
#	ifdef glCompressedTextureImage2DEXT
	_glCompressedTextureImage2DEXT = (glCompressedTextureImage2DEXTFunc)glGetFunction("glCompressedTextureImage2DEXT");
#	endif
#	ifdef glCompressedTextureImage1DEXT
	_glCompressedTextureImage1DEXT = (glCompressedTextureImage1DEXTFunc)glGetFunction("glCompressedTextureImage1DEXT");
#	endif
#	ifdef glCompressedTextureSubImage3DEXT
	_glCompressedTextureSubImage3DEXT = (glCompressedTextureSubImage3DEXTFunc)glGetFunction("glCompressedTextureSubImage3DEXT");
#	endif
#	ifdef glCompressedTextureSubImage2DEXT
	_glCompressedTextureSubImage2DEXT = (glCompressedTextureSubImage2DEXTFunc)glGetFunction("glCompressedTextureSubImage2DEXT");
#	endif
#	ifdef glCompressedTextureSubImage1DEXT
	_glCompressedTextureSubImage1DEXT = (glCompressedTextureSubImage1DEXTFunc)glGetFunction("glCompressedTextureSubImage1DEXT");
#	endif
#	ifdef glGetCompressedTextureImageEXT
	_glGetCompressedTextureImageEXT = (glGetCompressedTextureImageEXTFunc)glGetFunction("glGetCompressedTextureImageEXT");
#	endif
#	ifdef glCompressedMultiTexImage3DEXT
	_glCompressedMultiTexImage3DEXT = (glCompressedMultiTexImage3DEXTFunc)glGetFunction("glCompressedMultiTexImage3DEXT");
#	endif
#	ifdef glCompressedMultiTexImage2DEXT
	_glCompressedMultiTexImage2DEXT = (glCompressedMultiTexImage2DEXTFunc)glGetFunction("glCompressedMultiTexImage2DEXT");
#	endif
#	ifdef glCompressedMultiTexImage1DEXT
	_glCompressedMultiTexImage1DEXT = (glCompressedMultiTexImage1DEXTFunc)glGetFunction("glCompressedMultiTexImage1DEXT");
#	endif
#	ifdef glCompressedMultiTexSubImage3DEXT
	_glCompressedMultiTexSubImage3DEXT = (glCompressedMultiTexSubImage3DEXTFunc)glGetFunction("glCompressedMultiTexSubImage3DEXT");
#	endif
#	ifdef glCompressedMultiTexSubImage2DEXT
	_glCompressedMultiTexSubImage2DEXT = (glCompressedMultiTexSubImage2DEXTFunc)glGetFunction("glCompressedMultiTexSubImage2DEXT");
#	endif
#	ifdef glCompressedMultiTexSubImage1DEXT
	_glCompressedMultiTexSubImage1DEXT = (glCompressedMultiTexSubImage1DEXTFunc)glGetFunction("glCompressedMultiTexSubImage1DEXT");
#	endif
#	ifdef glGetCompressedMultiTexImageEXT
	_glGetCompressedMultiTexImageEXT = (glGetCompressedMultiTexImageEXTFunc)glGetFunction("glGetCompressedMultiTexImageEXT");
#	endif
#	ifdef glNamedProgramStringEXT
	_glNamedProgramStringEXT = (glNamedProgramStringEXTFunc)glGetFunction("glNamedProgramStringEXT");
#	endif
#	ifdef glNamedProgramLocalParameter4dEXT
	_glNamedProgramLocalParameter4dEXT = (glNamedProgramLocalParameter4dEXTFunc)glGetFunction("glNamedProgramLocalParameter4dEXT");
#	endif
#	ifdef glNamedProgramLocalParameter4dvEXT
	_glNamedProgramLocalParameter4dvEXT = (glNamedProgramLocalParameter4dvEXTFunc)glGetFunction("glNamedProgramLocalParameter4dvEXT");
#	endif
#	ifdef glNamedProgramLocalParameter4fEXT
	_glNamedProgramLocalParameter4fEXT = (glNamedProgramLocalParameter4fEXTFunc)glGetFunction("glNamedProgramLocalParameter4fEXT");
#	endif
#	ifdef glNamedProgramLocalParameter4fvEXT
	_glNamedProgramLocalParameter4fvEXT = (glNamedProgramLocalParameter4fvEXTFunc)glGetFunction("glNamedProgramLocalParameter4fvEXT");
#	endif
#	ifdef glGetNamedProgramLocalParameterdvEXT
	_glGetNamedProgramLocalParameterdvEXT = (glGetNamedProgramLocalParameterdvEXTFunc)glGetFunction("glGetNamedProgramLocalParameterdvEXT");
#	endif
#	ifdef glGetNamedProgramLocalParameterfvEXT
	_glGetNamedProgramLocalParameterfvEXT = (glGetNamedProgramLocalParameterfvEXTFunc)glGetFunction("glGetNamedProgramLocalParameterfvEXT");
#	endif
#	ifdef glGetNamedProgramivEXT
	_glGetNamedProgramivEXT = (glGetNamedProgramivEXTFunc)glGetFunction("glGetNamedProgramivEXT");
#	endif
#	ifdef glGetNamedProgramStringEXT
	_glGetNamedProgramStringEXT = (glGetNamedProgramStringEXTFunc)glGetFunction("glGetNamedProgramStringEXT");
#	endif
#	ifdef glNamedProgramLocalParameters4fvEXT
	_glNamedProgramLocalParameters4fvEXT = (glNamedProgramLocalParameters4fvEXTFunc)glGetFunction("glNamedProgramLocalParameters4fvEXT");
#	endif
#	ifdef glNamedProgramLocalParameterI4iEXT
	_glNamedProgramLocalParameterI4iEXT = (glNamedProgramLocalParameterI4iEXTFunc)glGetFunction("glNamedProgramLocalParameterI4iEXT");
#	endif
#	ifdef glNamedProgramLocalParameterI4ivEXT
	_glNamedProgramLocalParameterI4ivEXT = (glNamedProgramLocalParameterI4ivEXTFunc)glGetFunction("glNamedProgramLocalParameterI4ivEXT");
#	endif
#	ifdef glNamedProgramLocalParametersI4ivEXT
	_glNamedProgramLocalParametersI4ivEXT = (glNamedProgramLocalParametersI4ivEXTFunc)glGetFunction("glNamedProgramLocalParametersI4ivEXT");
#	endif
#	ifdef glNamedProgramLocalParameterI4uiEXT
	_glNamedProgramLocalParameterI4uiEXT = (glNamedProgramLocalParameterI4uiEXTFunc)glGetFunction("glNamedProgramLocalParameterI4uiEXT");
#	endif
#	ifdef glNamedProgramLocalParameterI4uivEXT
	_glNamedProgramLocalParameterI4uivEXT = (glNamedProgramLocalParameterI4uivEXTFunc)glGetFunction("glNamedProgramLocalParameterI4uivEXT");
#	endif
#	ifdef glNamedProgramLocalParametersI4uivEXT
	_glNamedProgramLocalParametersI4uivEXT = (glNamedProgramLocalParametersI4uivEXTFunc)glGetFunction("glNamedProgramLocalParametersI4uivEXT");
#	endif
#	ifdef glGetNamedProgramLocalParameterIivEXT
	_glGetNamedProgramLocalParameterIivEXT = (glGetNamedProgramLocalParameterIivEXTFunc)glGetFunction("glGetNamedProgramLocalParameterIivEXT");
#	endif
#	ifdef glGetNamedProgramLocalParameterIuivEXT
	_glGetNamedProgramLocalParameterIuivEXT = (glGetNamedProgramLocalParameterIuivEXTFunc)glGetFunction("glGetNamedProgramLocalParameterIuivEXT");
#	endif
#	ifdef glTextureParameterIivEXT
	_glTextureParameterIivEXT = (glTextureParameterIivEXTFunc)glGetFunction("glTextureParameterIivEXT");
#	endif
#	ifdef glTextureParameterIuivEXT
	_glTextureParameterIuivEXT = (glTextureParameterIuivEXTFunc)glGetFunction("glTextureParameterIuivEXT");
#	endif
#	ifdef glGetTextureParameterIivEXT
	_glGetTextureParameterIivEXT = (glGetTextureParameterIivEXTFunc)glGetFunction("glGetTextureParameterIivEXT");
#	endif
#	ifdef glGetTextureParameterIuivEXT
	_glGetTextureParameterIuivEXT = (glGetTextureParameterIuivEXTFunc)glGetFunction("glGetTextureParameterIuivEXT");
#	endif
#	ifdef glMultiTexParameterIivEXT
	_glMultiTexParameterIivEXT = (glMultiTexParameterIivEXTFunc)glGetFunction("glMultiTexParameterIivEXT");
#	endif
#	ifdef glMultiTexParameterIuivEXT
	_glMultiTexParameterIuivEXT = (glMultiTexParameterIuivEXTFunc)glGetFunction("glMultiTexParameterIuivEXT");
#	endif
#	ifdef glGetMultiTexParameterIivEXT
	_glGetMultiTexParameterIivEXT = (glGetMultiTexParameterIivEXTFunc)glGetFunction("glGetMultiTexParameterIivEXT");
#	endif
#	ifdef glGetMultiTexParameterIuivEXT
	_glGetMultiTexParameterIuivEXT = (glGetMultiTexParameterIuivEXTFunc)glGetFunction("glGetMultiTexParameterIuivEXT");
#	endif
#	ifdef glProgramUniform1fEXT
	_glProgramUniform1fEXT = (glProgramUniform1fEXTFunc)glGetFunction("glProgramUniform1fEXT");
#	endif
#	ifdef glProgramUniform2fEXT
	_glProgramUniform2fEXT = (glProgramUniform2fEXTFunc)glGetFunction("glProgramUniform2fEXT");
#	endif
#	ifdef glProgramUniform3fEXT
	_glProgramUniform3fEXT = (glProgramUniform3fEXTFunc)glGetFunction("glProgramUniform3fEXT");
#	endif
#	ifdef glProgramUniform4fEXT
	_glProgramUniform4fEXT = (glProgramUniform4fEXTFunc)glGetFunction("glProgramUniform4fEXT");
#	endif
#	ifdef glProgramUniform1iEXT
	_glProgramUniform1iEXT = (glProgramUniform1iEXTFunc)glGetFunction("glProgramUniform1iEXT");
#	endif
#	ifdef glProgramUniform2iEXT
	_glProgramUniform2iEXT = (glProgramUniform2iEXTFunc)glGetFunction("glProgramUniform2iEXT");
#	endif
#	ifdef glProgramUniform3iEXT
	_glProgramUniform3iEXT = (glProgramUniform3iEXTFunc)glGetFunction("glProgramUniform3iEXT");
#	endif
#	ifdef glProgramUniform4iEXT
	_glProgramUniform4iEXT = (glProgramUniform4iEXTFunc)glGetFunction("glProgramUniform4iEXT");
#	endif
#	ifdef glProgramUniform1fvEXT
	_glProgramUniform1fvEXT = (glProgramUniform1fvEXTFunc)glGetFunction("glProgramUniform1fvEXT");
#	endif
#	ifdef glProgramUniform2fvEXT
	_glProgramUniform2fvEXT = (glProgramUniform2fvEXTFunc)glGetFunction("glProgramUniform2fvEXT");
#	endif
#	ifdef glProgramUniform3fvEXT
	_glProgramUniform3fvEXT = (glProgramUniform3fvEXTFunc)glGetFunction("glProgramUniform3fvEXT");
#	endif
#	ifdef glProgramUniform4fvEXT
	_glProgramUniform4fvEXT = (glProgramUniform4fvEXTFunc)glGetFunction("glProgramUniform4fvEXT");
#	endif
#	ifdef glProgramUniform1ivEXT
	_glProgramUniform1ivEXT = (glProgramUniform1ivEXTFunc)glGetFunction("glProgramUniform1ivEXT");
#	endif
#	ifdef glProgramUniform2ivEXT
	_glProgramUniform2ivEXT = (glProgramUniform2ivEXTFunc)glGetFunction("glProgramUniform2ivEXT");
#	endif
#	ifdef glProgramUniform3ivEXT
	_glProgramUniform3ivEXT = (glProgramUniform3ivEXTFunc)glGetFunction("glProgramUniform3ivEXT");
#	endif
#	ifdef glProgramUniform4ivEXT
	_glProgramUniform4ivEXT = (glProgramUniform4ivEXTFunc)glGetFunction("glProgramUniform4ivEXT");
#	endif
#	ifdef glProgramUniformMatrix2fvEXT
	_glProgramUniformMatrix2fvEXT = (glProgramUniformMatrix2fvEXTFunc)glGetFunction("glProgramUniformMatrix2fvEXT");
#	endif
#	ifdef glProgramUniformMatrix3fvEXT
	_glProgramUniformMatrix3fvEXT = (glProgramUniformMatrix3fvEXTFunc)glGetFunction("glProgramUniformMatrix3fvEXT");
#	endif
#	ifdef glProgramUniformMatrix4fvEXT
	_glProgramUniformMatrix4fvEXT = (glProgramUniformMatrix4fvEXTFunc)glGetFunction("glProgramUniformMatrix4fvEXT");
#	endif
#	ifdef glProgramUniformMatrix2x3fvEXT
	_glProgramUniformMatrix2x3fvEXT = (glProgramUniformMatrix2x3fvEXTFunc)glGetFunction("glProgramUniformMatrix2x3fvEXT");
#	endif
#	ifdef glProgramUniformMatrix3x2fvEXT
	_glProgramUniformMatrix3x2fvEXT = (glProgramUniformMatrix3x2fvEXTFunc)glGetFunction("glProgramUniformMatrix3x2fvEXT");
#	endif
#	ifdef glProgramUniformMatrix2x4fvEXT
	_glProgramUniformMatrix2x4fvEXT = (glProgramUniformMatrix2x4fvEXTFunc)glGetFunction("glProgramUniformMatrix2x4fvEXT");
#	endif
#	ifdef glProgramUniformMatrix4x2fvEXT
	_glProgramUniformMatrix4x2fvEXT = (glProgramUniformMatrix4x2fvEXTFunc)glGetFunction("glProgramUniformMatrix4x2fvEXT");
#	endif
#	ifdef glProgramUniformMatrix3x4fvEXT
	_glProgramUniformMatrix3x4fvEXT = (glProgramUniformMatrix3x4fvEXTFunc)glGetFunction("glProgramUniformMatrix3x4fvEXT");
#	endif
#	ifdef glProgramUniformMatrix4x3fvEXT
	_glProgramUniformMatrix4x3fvEXT = (glProgramUniformMatrix4x3fvEXTFunc)glGetFunction("glProgramUniformMatrix4x3fvEXT");
#	endif
#	ifdef glProgramUniform1uiEXT
	_glProgramUniform1uiEXT = (glProgramUniform1uiEXTFunc)glGetFunction("glProgramUniform1uiEXT");
#	endif
#	ifdef glProgramUniform2uiEXT
	_glProgramUniform2uiEXT = (glProgramUniform2uiEXTFunc)glGetFunction("glProgramUniform2uiEXT");
#	endif
#	ifdef glProgramUniform3uiEXT
	_glProgramUniform3uiEXT = (glProgramUniform3uiEXTFunc)glGetFunction("glProgramUniform3uiEXT");
#	endif
#	ifdef glProgramUniform4uiEXT
	_glProgramUniform4uiEXT = (glProgramUniform4uiEXTFunc)glGetFunction("glProgramUniform4uiEXT");
#	endif
#	ifdef glProgramUniform1uivEXT
	_glProgramUniform1uivEXT = (glProgramUniform1uivEXTFunc)glGetFunction("glProgramUniform1uivEXT");
#	endif
#	ifdef glProgramUniform2uivEXT
	_glProgramUniform2uivEXT = (glProgramUniform2uivEXTFunc)glGetFunction("glProgramUniform2uivEXT");
#	endif
#	ifdef glProgramUniform3uivEXT
	_glProgramUniform3uivEXT = (glProgramUniform3uivEXTFunc)glGetFunction("glProgramUniform3uivEXT");
#	endif
#	ifdef glProgramUniform4uivEXT
	_glProgramUniform4uivEXT = (glProgramUniform4uivEXTFunc)glGetFunction("glProgramUniform4uivEXT");
#	endif
#	ifdef glNamedBufferDataEXT
	_glNamedBufferDataEXT = (glNamedBufferDataEXTFunc)glGetFunction("glNamedBufferDataEXT");
#	endif
#	ifdef glNamedBufferSubDataEXT
	_glNamedBufferSubDataEXT = (glNamedBufferSubDataEXTFunc)glGetFunction("glNamedBufferSubDataEXT");
#	endif
#	ifdef glMapNamedBufferEXT
	_glMapNamedBufferEXT = (glMapNamedBufferEXTFunc)glGetFunction("glMapNamedBufferEXT");
#	endif
#	ifdef glUnmapNamedBufferEXT
	_glUnmapNamedBufferEXT = (glUnmapNamedBufferEXTFunc)glGetFunction("glUnmapNamedBufferEXT");
#	endif
#	ifdef glMapNamedBufferRangeEXT
	_glMapNamedBufferRangeEXT = (glMapNamedBufferRangeEXTFunc)glGetFunction("glMapNamedBufferRangeEXT");
#	endif
#	ifdef glFlushMappedNamedBufferRangeEXT
	_glFlushMappedNamedBufferRangeEXT = (glFlushMappedNamedBufferRangeEXTFunc)glGetFunction("glFlushMappedNamedBufferRangeEXT");
#	endif
#	ifdef glNamedCopyBufferSubDataEXT
	_glNamedCopyBufferSubDataEXT = (glNamedCopyBufferSubDataEXTFunc)glGetFunction("glNamedCopyBufferSubDataEXT");
#	endif
#	ifdef glGetNamedBufferParameterivEXT
	_glGetNamedBufferParameterivEXT = (glGetNamedBufferParameterivEXTFunc)glGetFunction("glGetNamedBufferParameterivEXT");
#	endif
#	ifdef glGetNamedBufferPointervEXT
	_glGetNamedBufferPointervEXT = (glGetNamedBufferPointervEXTFunc)glGetFunction("glGetNamedBufferPointervEXT");
#	endif
#	ifdef glGetNamedBufferSubDataEXT
	_glGetNamedBufferSubDataEXT = (glGetNamedBufferSubDataEXTFunc)glGetFunction("glGetNamedBufferSubDataEXT");
#	endif
#	ifdef glTextureBufferEXT
	_glTextureBufferEXT = (glTextureBufferEXTFunc)glGetFunction("glTextureBufferEXT");
#	endif
#	ifdef glMultiTexBufferEXT
	_glMultiTexBufferEXT = (glMultiTexBufferEXTFunc)glGetFunction("glMultiTexBufferEXT");
#	endif
#	ifdef glNamedRenderbufferStorageEXT
	_glNamedRenderbufferStorageEXT = (glNamedRenderbufferStorageEXTFunc)glGetFunction("glNamedRenderbufferStorageEXT");
#	endif
#	ifdef glGetNamedRenderbufferParameterivEXT
	_glGetNamedRenderbufferParameterivEXT = (glGetNamedRenderbufferParameterivEXTFunc)glGetFunction("glGetNamedRenderbufferParameterivEXT");
#	endif
#	ifdef glCheckNamedFramebufferStatusEXT
	_glCheckNamedFramebufferStatusEXT = (glCheckNamedFramebufferStatusEXTFunc)glGetFunction("glCheckNamedFramebufferStatusEXT");
#	endif
#	ifdef glNamedFramebufferTexture1DEXT
	_glNamedFramebufferTexture1DEXT = (glNamedFramebufferTexture1DEXTFunc)glGetFunction("glNamedFramebufferTexture1DEXT");
#	endif
#	ifdef glNamedFramebufferTexture2DEXT
	_glNamedFramebufferTexture2DEXT = (glNamedFramebufferTexture2DEXTFunc)glGetFunction("glNamedFramebufferTexture2DEXT");
#	endif
#	ifdef glNamedFramebufferTexture3DEXT
	_glNamedFramebufferTexture3DEXT = (glNamedFramebufferTexture3DEXTFunc)glGetFunction("glNamedFramebufferTexture3DEXT");
#	endif
#	ifdef glNamedFramebufferRenderbufferEXT
	_glNamedFramebufferRenderbufferEXT = (glNamedFramebufferRenderbufferEXTFunc)glGetFunction("glNamedFramebufferRenderbufferEXT");
#	endif
#	ifdef glGetNamedFramebufferAttachmentParameterivEXT
	_glGetNamedFramebufferAttachmentParameterivEXT = (glGetNamedFramebufferAttachmentParameterivEXTFunc)glGetFunction("glGetNamedFramebufferAttachmentParameterivEXT");
#	endif
#	ifdef glGenerateTextureMipmapEXT
	_glGenerateTextureMipmapEXT = (glGenerateTextureMipmapEXTFunc)glGetFunction("glGenerateTextureMipmapEXT");
#	endif
#	ifdef glGenerateMultiTexMipmapEXT
	_glGenerateMultiTexMipmapEXT = (glGenerateMultiTexMipmapEXTFunc)glGetFunction("glGenerateMultiTexMipmapEXT");
#	endif
#	ifdef glFramebufferDrawBufferEXT
	_glFramebufferDrawBufferEXT = (glFramebufferDrawBufferEXTFunc)glGetFunction("glFramebufferDrawBufferEXT");
#	endif
#	ifdef glFramebufferDrawBuffersEXT
	_glFramebufferDrawBuffersEXT = (glFramebufferDrawBuffersEXTFunc)glGetFunction("glFramebufferDrawBuffersEXT");
#	endif
#	ifdef glFramebufferReadBufferEXT
	_glFramebufferReadBufferEXT = (glFramebufferReadBufferEXTFunc)glGetFunction("glFramebufferReadBufferEXT");
#	endif
#	ifdef glGetFramebufferParameterivEXT
	_glGetFramebufferParameterivEXT = (glGetFramebufferParameterivEXTFunc)glGetFunction("glGetFramebufferParameterivEXT");
#	endif
#	ifdef glNamedRenderbufferStorageMultisampleEXT
	_glNamedRenderbufferStorageMultisampleEXT = (glNamedRenderbufferStorageMultisampleEXTFunc)glGetFunction("glNamedRenderbufferStorageMultisampleEXT");
#	endif
#	ifdef glNamedRenderbufferStorageMultisampleCoverageEXT
	_glNamedRenderbufferStorageMultisampleCoverageEXT = (glNamedRenderbufferStorageMultisampleCoverageEXTFunc)glGetFunction("glNamedRenderbufferStorageMultisampleCoverageEXT");
#	endif
#	ifdef glNamedFramebufferTextureEXT
	_glNamedFramebufferTextureEXT = (glNamedFramebufferTextureEXTFunc)glGetFunction("glNamedFramebufferTextureEXT");
#	endif
#	ifdef glNamedFramebufferTextureLayerEXT
	_glNamedFramebufferTextureLayerEXT = (glNamedFramebufferTextureLayerEXTFunc)glGetFunction("glNamedFramebufferTextureLayerEXT");
#	endif
#	ifdef glNamedFramebufferTextureFaceEXT
	_glNamedFramebufferTextureFaceEXT = (glNamedFramebufferTextureFaceEXTFunc)glGetFunction("glNamedFramebufferTextureFaceEXT");
#	endif
#	ifdef glTextureRenderbufferEXT
	_glTextureRenderbufferEXT = (glTextureRenderbufferEXTFunc)glGetFunction("glTextureRenderbufferEXT");
#	endif
#	ifdef glMultiTexRenderbufferEXT
	_glMultiTexRenderbufferEXT = (glMultiTexRenderbufferEXTFunc)glGetFunction("glMultiTexRenderbufferEXT");
#	endif
#	ifdef glProgramUniform1dEXT
	_glProgramUniform1dEXT = (glProgramUniform1dEXTFunc)glGetFunction("glProgramUniform1dEXT");
#	endif
#	ifdef glProgramUniform2dEXT
	_glProgramUniform2dEXT = (glProgramUniform2dEXTFunc)glGetFunction("glProgramUniform2dEXT");
#	endif
#	ifdef glProgramUniform3dEXT
	_glProgramUniform3dEXT = (glProgramUniform3dEXTFunc)glGetFunction("glProgramUniform3dEXT");
#	endif
#	ifdef glProgramUniform4dEXT
	_glProgramUniform4dEXT = (glProgramUniform4dEXTFunc)glGetFunction("glProgramUniform4dEXT");
#	endif
#	ifdef glProgramUniform1dvEXT
	_glProgramUniform1dvEXT = (glProgramUniform1dvEXTFunc)glGetFunction("glProgramUniform1dvEXT");
#	endif
#	ifdef glProgramUniform2dvEXT
	_glProgramUniform2dvEXT = (glProgramUniform2dvEXTFunc)glGetFunction("glProgramUniform2dvEXT");
#	endif
#	ifdef glProgramUniform3dvEXT
	_glProgramUniform3dvEXT = (glProgramUniform3dvEXTFunc)glGetFunction("glProgramUniform3dvEXT");
#	endif
#	ifdef glProgramUniform4dvEXT
	_glProgramUniform4dvEXT = (glProgramUniform4dvEXTFunc)glGetFunction("glProgramUniform4dvEXT");
#	endif
#	ifdef glProgramUniformMatrix2dvEXT
	_glProgramUniformMatrix2dvEXT = (glProgramUniformMatrix2dvEXTFunc)glGetFunction("glProgramUniformMatrix2dvEXT");
#	endif
#	ifdef glProgramUniformMatrix3dvEXT
	_glProgramUniformMatrix3dvEXT = (glProgramUniformMatrix3dvEXTFunc)glGetFunction("glProgramUniformMatrix3dvEXT");
#	endif
#	ifdef glProgramUniformMatrix4dvEXT
	_glProgramUniformMatrix4dvEXT = (glProgramUniformMatrix4dvEXTFunc)glGetFunction("glProgramUniformMatrix4dvEXT");
#	endif
#	ifdef glProgramUniformMatrix2x3dvEXT
	_glProgramUniformMatrix2x3dvEXT = (glProgramUniformMatrix2x3dvEXTFunc)glGetFunction("glProgramUniformMatrix2x3dvEXT");
#	endif
#	ifdef glProgramUniformMatrix2x4dvEXT
	_glProgramUniformMatrix2x4dvEXT = (glProgramUniformMatrix2x4dvEXTFunc)glGetFunction("glProgramUniformMatrix2x4dvEXT");
#	endif
#	ifdef glProgramUniformMatrix3x2dvEXT
	_glProgramUniformMatrix3x2dvEXT = (glProgramUniformMatrix3x2dvEXTFunc)glGetFunction("glProgramUniformMatrix3x2dvEXT");
#	endif
#	ifdef glProgramUniformMatrix3x4dvEXT
	_glProgramUniformMatrix3x4dvEXT = (glProgramUniformMatrix3x4dvEXTFunc)glGetFunction("glProgramUniformMatrix3x4dvEXT");
#	endif
#	ifdef glProgramUniformMatrix4x2dvEXT
	_glProgramUniformMatrix4x2dvEXT = (glProgramUniformMatrix4x2dvEXTFunc)glGetFunction("glProgramUniformMatrix4x2dvEXT");
#	endif
#	ifdef glProgramUniformMatrix4x3dvEXT
	_glProgramUniformMatrix4x3dvEXT = (glProgramUniformMatrix4x3dvEXTFunc)glGetFunction("glProgramUniformMatrix4x3dvEXT");
#	endif
#	ifdef glGetMultisamplefvNV
	_glGetMultisamplefvNV = (glGetMultisamplefvNVFunc)glGetFunction("glGetMultisamplefvNV");
#	endif
#	ifdef glSampleMaskIndexedNV
	_glSampleMaskIndexedNV = (glSampleMaskIndexedNVFunc)glGetFunction("glSampleMaskIndexedNV");
#	endif
#	ifdef glTexRenderbufferNV
	_glTexRenderbufferNV = (glTexRenderbufferNVFunc)glGetFunction("glTexRenderbufferNV");
#	endif
#	ifdef glBindTransformFeedbackNV
	_glBindTransformFeedbackNV = (glBindTransformFeedbackNVFunc)glGetFunction("glBindTransformFeedbackNV");
#	endif
#	ifdef glDeleteTransformFeedbacksNV
	_glDeleteTransformFeedbacksNV = (glDeleteTransformFeedbacksNVFunc)glGetFunction("glDeleteTransformFeedbacksNV");
#	endif
#	ifdef glGenTransformFeedbacksNV
	_glGenTransformFeedbacksNV = (glGenTransformFeedbacksNVFunc)glGetFunction("glGenTransformFeedbacksNV");
#	endif
#	ifdef glIsTransformFeedbackNV
	_glIsTransformFeedbackNV = (glIsTransformFeedbackNVFunc)glGetFunction("glIsTransformFeedbackNV");
#	endif
#	ifdef glPauseTransformFeedbackNV
	_glPauseTransformFeedbackNV = (glPauseTransformFeedbackNVFunc)glGetFunction("glPauseTransformFeedbackNV");
#	endif
#	ifdef glResumeTransformFeedbackNV
	_glResumeTransformFeedbackNV = (glResumeTransformFeedbackNVFunc)glGetFunction("glResumeTransformFeedbackNV");
#	endif
#	ifdef glDrawTransformFeedbackNV
	_glDrawTransformFeedbackNV = (glDrawTransformFeedbackNVFunc)glGetFunction("glDrawTransformFeedbackNV");
#	endif
#	ifdef glGetPerfMonitorGroupsAMD
	_glGetPerfMonitorGroupsAMD = (glGetPerfMonitorGroupsAMDFunc)glGetFunction("glGetPerfMonitorGroupsAMD");
#	endif
#	ifdef glGetPerfMonitorCountersAMD
	_glGetPerfMonitorCountersAMD = (glGetPerfMonitorCountersAMDFunc)glGetFunction("glGetPerfMonitorCountersAMD");
#	endif
#	ifdef glGetPerfMonitorGroupStringAMD
	_glGetPerfMonitorGroupStringAMD = (glGetPerfMonitorGroupStringAMDFunc)glGetFunction("glGetPerfMonitorGroupStringAMD");
#	endif
#	ifdef glGetPerfMonitorCounterStringAMD
	_glGetPerfMonitorCounterStringAMD = (glGetPerfMonitorCounterStringAMDFunc)glGetFunction("glGetPerfMonitorCounterStringAMD");
#	endif
#	ifdef glGetPerfMonitorCounterInfoAMD
	_glGetPerfMonitorCounterInfoAMD = (glGetPerfMonitorCounterInfoAMDFunc)glGetFunction("glGetPerfMonitorCounterInfoAMD");
#	endif
#	ifdef glGenPerfMonitorsAMD
	_glGenPerfMonitorsAMD = (glGenPerfMonitorsAMDFunc)glGetFunction("glGenPerfMonitorsAMD");
#	endif
#	ifdef glDeletePerfMonitorsAMD
	_glDeletePerfMonitorsAMD = (glDeletePerfMonitorsAMDFunc)glGetFunction("glDeletePerfMonitorsAMD");
#	endif
#	ifdef glSelectPerfMonitorCountersAMD
	_glSelectPerfMonitorCountersAMD = (glSelectPerfMonitorCountersAMDFunc)glGetFunction("glSelectPerfMonitorCountersAMD");
#	endif
#	ifdef glBeginPerfMonitorAMD
	_glBeginPerfMonitorAMD = (glBeginPerfMonitorAMDFunc)glGetFunction("glBeginPerfMonitorAMD");
#	endif
#	ifdef glEndPerfMonitorAMD
	_glEndPerfMonitorAMD = (glEndPerfMonitorAMDFunc)glGetFunction("glEndPerfMonitorAMD");
#	endif
#	ifdef glGetPerfMonitorCounterDataAMD
	_glGetPerfMonitorCounterDataAMD = (glGetPerfMonitorCounterDataAMDFunc)glGetFunction("glGetPerfMonitorCounterDataAMD");
#	endif
#	ifdef glTessellationFactorAMD
	_glTessellationFactorAMD = (glTessellationFactorAMDFunc)glGetFunction("glTessellationFactorAMD");
#	endif
#	ifdef glTessellationModeAMD
	_glTessellationModeAMD = (glTessellationModeAMDFunc)glGetFunction("glTessellationModeAMD");
#	endif
#	ifdef glProvokingVertexEXT
	_glProvokingVertexEXT = (glProvokingVertexEXTFunc)glGetFunction("glProvokingVertexEXT");
#	endif
#	ifdef glBlendFuncIndexedAMD
	_glBlendFuncIndexedAMD = (glBlendFuncIndexedAMDFunc)glGetFunction("glBlendFuncIndexedAMD");
#	endif
#	ifdef glBlendFuncSeparateIndexedAMD
	_glBlendFuncSeparateIndexedAMD = (glBlendFuncSeparateIndexedAMDFunc)glGetFunction("glBlendFuncSeparateIndexedAMD");
#	endif
#	ifdef glBlendEquationIndexedAMD
	_glBlendEquationIndexedAMD = (glBlendEquationIndexedAMDFunc)glGetFunction("glBlendEquationIndexedAMD");
#	endif
#	ifdef glBlendEquationSeparateIndexedAMD
	_glBlendEquationSeparateIndexedAMD = (glBlendEquationSeparateIndexedAMDFunc)glGetFunction("glBlendEquationSeparateIndexedAMD");
#	endif
#	ifdef glTextureRangeAPPLE
	_glTextureRangeAPPLE = (glTextureRangeAPPLEFunc)glGetFunction("glTextureRangeAPPLE");
#	endif
#	ifdef glGetTexParameterPointervAPPLE
	_glGetTexParameterPointervAPPLE = (glGetTexParameterPointervAPPLEFunc)glGetFunction("glGetTexParameterPointervAPPLE");
#	endif
#	ifdef glEnableVertexAttribAPPLE
	_glEnableVertexAttribAPPLE = (glEnableVertexAttribAPPLEFunc)glGetFunction("glEnableVertexAttribAPPLE");
#	endif
#	ifdef glDisableVertexAttribAPPLE
	_glDisableVertexAttribAPPLE = (glDisableVertexAttribAPPLEFunc)glGetFunction("glDisableVertexAttribAPPLE");
#	endif
#	ifdef glIsVertexAttribEnabledAPPLE
	_glIsVertexAttribEnabledAPPLE = (glIsVertexAttribEnabledAPPLEFunc)glGetFunction("glIsVertexAttribEnabledAPPLE");
#	endif
#	ifdef glMapVertexAttrib1dAPPLE
	_glMapVertexAttrib1dAPPLE = (glMapVertexAttrib1dAPPLEFunc)glGetFunction("glMapVertexAttrib1dAPPLE");
#	endif
#	ifdef glMapVertexAttrib1fAPPLE
	_glMapVertexAttrib1fAPPLE = (glMapVertexAttrib1fAPPLEFunc)glGetFunction("glMapVertexAttrib1fAPPLE");
#	endif
#	ifdef glMapVertexAttrib2dAPPLE
	_glMapVertexAttrib2dAPPLE = (glMapVertexAttrib2dAPPLEFunc)glGetFunction("glMapVertexAttrib2dAPPLE");
#	endif
#	ifdef glMapVertexAttrib2fAPPLE
	_glMapVertexAttrib2fAPPLE = (glMapVertexAttrib2fAPPLEFunc)glGetFunction("glMapVertexAttrib2fAPPLE");
#	endif
#	ifdef glObjectPurgeableAPPLE
	_glObjectPurgeableAPPLE = (glObjectPurgeableAPPLEFunc)glGetFunction("glObjectPurgeableAPPLE");
#	endif
#	ifdef glObjectUnpurgeableAPPLE
	_glObjectUnpurgeableAPPLE = (glObjectUnpurgeableAPPLEFunc)glGetFunction("glObjectUnpurgeableAPPLE");
#	endif
#	ifdef glGetObjectParameterivAPPLE
	_glGetObjectParameterivAPPLE = (glGetObjectParameterivAPPLEFunc)glGetFunction("glGetObjectParameterivAPPLE");
#	endif
#	ifdef glBeginVideoCaptureNV
	_glBeginVideoCaptureNV = (glBeginVideoCaptureNVFunc)glGetFunction("glBeginVideoCaptureNV");
#	endif
#	ifdef glBindVideoCaptureStreamBufferNV
	_glBindVideoCaptureStreamBufferNV = (glBindVideoCaptureStreamBufferNVFunc)glGetFunction("glBindVideoCaptureStreamBufferNV");
#	endif
#	ifdef glBindVideoCaptureStreamTextureNV
	_glBindVideoCaptureStreamTextureNV = (glBindVideoCaptureStreamTextureNVFunc)glGetFunction("glBindVideoCaptureStreamTextureNV");
#	endif
#	ifdef glEndVideoCaptureNV
	_glEndVideoCaptureNV = (glEndVideoCaptureNVFunc)glGetFunction("glEndVideoCaptureNV");
#	endif
#	ifdef glGetVideoCaptureivNV
	_glGetVideoCaptureivNV = (glGetVideoCaptureivNVFunc)glGetFunction("glGetVideoCaptureivNV");
#	endif
#	ifdef glGetVideoCaptureStreamivNV
	_glGetVideoCaptureStreamivNV = (glGetVideoCaptureStreamivNVFunc)glGetFunction("glGetVideoCaptureStreamivNV");
#	endif
#	ifdef glGetVideoCaptureStreamfvNV
	_glGetVideoCaptureStreamfvNV = (glGetVideoCaptureStreamfvNVFunc)glGetFunction("glGetVideoCaptureStreamfvNV");
#	endif
#	ifdef glGetVideoCaptureStreamdvNV
	_glGetVideoCaptureStreamdvNV = (glGetVideoCaptureStreamdvNVFunc)glGetFunction("glGetVideoCaptureStreamdvNV");
#	endif
#	ifdef glVideoCaptureNV
	_glVideoCaptureNV = (glVideoCaptureNVFunc)glGetFunction("glVideoCaptureNV");
#	endif
#	ifdef glVideoCaptureStreamParameterivNV
	_glVideoCaptureStreamParameterivNV = (glVideoCaptureStreamParameterivNVFunc)glGetFunction("glVideoCaptureStreamParameterivNV");
#	endif
#	ifdef glVideoCaptureStreamParameterfvNV
	_glVideoCaptureStreamParameterfvNV = (glVideoCaptureStreamParameterfvNVFunc)glGetFunction("glVideoCaptureStreamParameterfvNV");
#	endif
#	ifdef glVideoCaptureStreamParameterdvNV
	_glVideoCaptureStreamParameterdvNV = (glVideoCaptureStreamParameterdvNVFunc)glGetFunction("glVideoCaptureStreamParameterdvNV");
#	endif
#	ifdef glCopyImageSubDataNV
	_glCopyImageSubDataNV = (glCopyImageSubDataNVFunc)glGetFunction("glCopyImageSubDataNV");
#	endif
#	ifdef glUseShaderProgramEXT
	_glUseShaderProgramEXT = (glUseShaderProgramEXTFunc)glGetFunction("glUseShaderProgramEXT");
#	endif
#	ifdef glActiveProgramEXT
	_glActiveProgramEXT = (glActiveProgramEXTFunc)glGetFunction("glActiveProgramEXT");
#	endif
#	ifdef glCreateShaderProgramEXT
	_glCreateShaderProgramEXT = (glCreateShaderProgramEXTFunc)glGetFunction("glCreateShaderProgramEXT");
#	endif
#	ifdef glMakeBufferResidentNV
	_glMakeBufferResidentNV = (glMakeBufferResidentNVFunc)glGetFunction("glMakeBufferResidentNV");
#	endif
#	ifdef glMakeBufferNonResidentNV
	_glMakeBufferNonResidentNV = (glMakeBufferNonResidentNVFunc)glGetFunction("glMakeBufferNonResidentNV");
#	endif
#	ifdef glIsBufferResidentNV
	_glIsBufferResidentNV = (glIsBufferResidentNVFunc)glGetFunction("glIsBufferResidentNV");
#	endif
#	ifdef glMakeNamedBufferResidentNV
	_glMakeNamedBufferResidentNV = (glMakeNamedBufferResidentNVFunc)glGetFunction("glMakeNamedBufferResidentNV");
#	endif
#	ifdef glMakeNamedBufferNonResidentNV
	_glMakeNamedBufferNonResidentNV = (glMakeNamedBufferNonResidentNVFunc)glGetFunction("glMakeNamedBufferNonResidentNV");
#	endif
#	ifdef glIsNamedBufferResidentNV
	_glIsNamedBufferResidentNV = (glIsNamedBufferResidentNVFunc)glGetFunction("glIsNamedBufferResidentNV");
#	endif
#	ifdef glGetBufferParameterui64vNV
	_glGetBufferParameterui64vNV = (glGetBufferParameterui64vNVFunc)glGetFunction("glGetBufferParameterui64vNV");
#	endif
#	ifdef glGetNamedBufferParameterui64vNV
	_glGetNamedBufferParameterui64vNV = (glGetNamedBufferParameterui64vNVFunc)glGetFunction("glGetNamedBufferParameterui64vNV");
#	endif
#	ifdef glGetIntegerui64vNV
	_glGetIntegerui64vNV = (glGetIntegerui64vNVFunc)glGetFunction("glGetIntegerui64vNV");
#	endif
#	ifdef glUniformui64NV
	_glUniformui64NV = (glUniformui64NVFunc)glGetFunction("glUniformui64NV");
#	endif
#	ifdef glUniformui64vNV
	_glUniformui64vNV = (glUniformui64vNVFunc)glGetFunction("glUniformui64vNV");
#	endif
#	ifdef glGetUniformui64vNV
	_glGetUniformui64vNV = (glGetUniformui64vNVFunc)glGetFunction("glGetUniformui64vNV");
#	endif
#	ifdef glProgramUniformui64NV
	_glProgramUniformui64NV = (glProgramUniformui64NVFunc)glGetFunction("glProgramUniformui64NV");
#	endif
#	ifdef glProgramUniformui64vNV
	_glProgramUniformui64vNV = (glProgramUniformui64vNVFunc)glGetFunction("glProgramUniformui64vNV");
#	endif
#	ifdef glBufferAddressRangeNV
	_glBufferAddressRangeNV = (glBufferAddressRangeNVFunc)glGetFunction("glBufferAddressRangeNV");
#	endif
#	ifdef glVertexFormatNV
	_glVertexFormatNV = (glVertexFormatNVFunc)glGetFunction("glVertexFormatNV");
#	endif
#	ifdef glNormalFormatNV
	_glNormalFormatNV = (glNormalFormatNVFunc)glGetFunction("glNormalFormatNV");
#	endif
#	ifdef glColorFormatNV
	_glColorFormatNV = (glColorFormatNVFunc)glGetFunction("glColorFormatNV");
#	endif
#	ifdef glIndexFormatNV
	_glIndexFormatNV = (glIndexFormatNVFunc)glGetFunction("glIndexFormatNV");
#	endif
#	ifdef glTexCoordFormatNV
	_glTexCoordFormatNV = (glTexCoordFormatNVFunc)glGetFunction("glTexCoordFormatNV");
#	endif
#	ifdef glEdgeFlagFormatNV
	_glEdgeFlagFormatNV = (glEdgeFlagFormatNVFunc)glGetFunction("glEdgeFlagFormatNV");
#	endif
#	ifdef glSecondaryColorFormatNV
	_glSecondaryColorFormatNV = (glSecondaryColorFormatNVFunc)glGetFunction("glSecondaryColorFormatNV");
#	endif
#	ifdef glFogCoordFormatNV
	_glFogCoordFormatNV = (glFogCoordFormatNVFunc)glGetFunction("glFogCoordFormatNV");
#	endif
#	ifdef glVertexAttribFormatNV
	_glVertexAttribFormatNV = (glVertexAttribFormatNVFunc)glGetFunction("glVertexAttribFormatNV");
#	endif
#	ifdef glVertexAttribIFormatNV
	_glVertexAttribIFormatNV = (glVertexAttribIFormatNVFunc)glGetFunction("glVertexAttribIFormatNV");
#	endif
#	ifdef glGetIntegerui64i_vNV
	_glGetIntegerui64i_vNV = (glGetIntegerui64i_vNVFunc)glGetFunction("glGetIntegerui64i_vNV");
#	endif
#	ifdef glTextureBarrierNV
	_glTextureBarrierNV = (glTextureBarrierNVFunc)glGetFunction("glTextureBarrierNV");
#	endif
#	ifdef glBindImageTextureEXT
	_glBindImageTextureEXT = (glBindImageTextureEXTFunc)glGetFunction("glBindImageTextureEXT");
#	endif
#	ifdef glMemoryBarrierEXT
	_glMemoryBarrierEXT = (glMemoryBarrierEXTFunc)glGetFunction("glMemoryBarrierEXT");
#	endif
#	ifdef glVertexAttribL1dEXT
	_glVertexAttribL1dEXT = (glVertexAttribL1dEXTFunc)glGetFunction("glVertexAttribL1dEXT");
#	endif
#	ifdef glVertexAttribL2dEXT
	_glVertexAttribL2dEXT = (glVertexAttribL2dEXTFunc)glGetFunction("glVertexAttribL2dEXT");
#	endif
#	ifdef glVertexAttribL3dEXT
	_glVertexAttribL3dEXT = (glVertexAttribL3dEXTFunc)glGetFunction("glVertexAttribL3dEXT");
#	endif
#	ifdef glVertexAttribL4dEXT
	_glVertexAttribL4dEXT = (glVertexAttribL4dEXTFunc)glGetFunction("glVertexAttribL4dEXT");
#	endif
#	ifdef glVertexAttribL1dvEXT
	_glVertexAttribL1dvEXT = (glVertexAttribL1dvEXTFunc)glGetFunction("glVertexAttribL1dvEXT");
#	endif
#	ifdef glVertexAttribL2dvEXT
	_glVertexAttribL2dvEXT = (glVertexAttribL2dvEXTFunc)glGetFunction("glVertexAttribL2dvEXT");
#	endif
#	ifdef glVertexAttribL3dvEXT
	_glVertexAttribL3dvEXT = (glVertexAttribL3dvEXTFunc)glGetFunction("glVertexAttribL3dvEXT");
#	endif
#	ifdef glVertexAttribL4dvEXT
	_glVertexAttribL4dvEXT = (glVertexAttribL4dvEXTFunc)glGetFunction("glVertexAttribL4dvEXT");
#	endif
#	ifdef glVertexAttribLPointerEXT
	_glVertexAttribLPointerEXT = (glVertexAttribLPointerEXTFunc)glGetFunction("glVertexAttribLPointerEXT");
#	endif
#	ifdef glGetVertexAttribLdvEXT
	_glGetVertexAttribLdvEXT = (glGetVertexAttribLdvEXTFunc)glGetFunction("glGetVertexAttribLdvEXT");
#	endif
#	ifdef glVertexArrayVertexAttribLOffsetEXT
	_glVertexArrayVertexAttribLOffsetEXT = (glVertexArrayVertexAttribLOffsetEXTFunc)glGetFunction("glVertexArrayVertexAttribLOffsetEXT");
#	endif
#	ifdef glProgramSubroutineParametersuivNV
	_glProgramSubroutineParametersuivNV = (glProgramSubroutineParametersuivNVFunc)glGetFunction("glProgramSubroutineParametersuivNV");
#	endif
#	ifdef glGetProgramSubroutineParameteruivNV
	_glGetProgramSubroutineParameteruivNV = (glGetProgramSubroutineParameteruivNVFunc)glGetFunction("glGetProgramSubroutineParameteruivNV");
#	endif
#	ifdef glUniform1i64NV
	_glUniform1i64NV = (glUniform1i64NVFunc)glGetFunction("glUniform1i64NV");
#	endif
#	ifdef glUniform2i64NV
	_glUniform2i64NV = (glUniform2i64NVFunc)glGetFunction("glUniform2i64NV");
#	endif
#	ifdef glUniform3i64NV
	_glUniform3i64NV = (glUniform3i64NVFunc)glGetFunction("glUniform3i64NV");
#	endif
#	ifdef glUniform4i64NV
	_glUniform4i64NV = (glUniform4i64NVFunc)glGetFunction("glUniform4i64NV");
#	endif
#	ifdef glUniform1i64vNV
	_glUniform1i64vNV = (glUniform1i64vNVFunc)glGetFunction("glUniform1i64vNV");
#	endif
#	ifdef glUniform2i64vNV
	_glUniform2i64vNV = (glUniform2i64vNVFunc)glGetFunction("glUniform2i64vNV");
#	endif
#	ifdef glUniform3i64vNV
	_glUniform3i64vNV = (glUniform3i64vNVFunc)glGetFunction("glUniform3i64vNV");
#	endif
#	ifdef glUniform4i64vNV
	_glUniform4i64vNV = (glUniform4i64vNVFunc)glGetFunction("glUniform4i64vNV");
#	endif
#	ifdef glUniform1ui64NV
	_glUniform1ui64NV = (glUniform1ui64NVFunc)glGetFunction("glUniform1ui64NV");
#	endif
#	ifdef glUniform2ui64NV
	_glUniform2ui64NV = (glUniform2ui64NVFunc)glGetFunction("glUniform2ui64NV");
#	endif
#	ifdef glUniform3ui64NV
	_glUniform3ui64NV = (glUniform3ui64NVFunc)glGetFunction("glUniform3ui64NV");
#	endif
#	ifdef glUniform4ui64NV
	_glUniform4ui64NV = (glUniform4ui64NVFunc)glGetFunction("glUniform4ui64NV");
#	endif
#	ifdef glUniform1ui64vNV
	_glUniform1ui64vNV = (glUniform1ui64vNVFunc)glGetFunction("glUniform1ui64vNV");
#	endif
#	ifdef glUniform2ui64vNV
	_glUniform2ui64vNV = (glUniform2ui64vNVFunc)glGetFunction("glUniform2ui64vNV");
#	endif
#	ifdef glUniform3ui64vNV
	_glUniform3ui64vNV = (glUniform3ui64vNVFunc)glGetFunction("glUniform3ui64vNV");
#	endif
#	ifdef glUniform4ui64vNV
	_glUniform4ui64vNV = (glUniform4ui64vNVFunc)glGetFunction("glUniform4ui64vNV");
#	endif
#	ifdef glGetUniformi64vNV
	_glGetUniformi64vNV = (glGetUniformi64vNVFunc)glGetFunction("glGetUniformi64vNV");
#	endif
#	ifdef glProgramUniform1i64NV
	_glProgramUniform1i64NV = (glProgramUniform1i64NVFunc)glGetFunction("glProgramUniform1i64NV");
#	endif
#	ifdef glProgramUniform2i64NV
	_glProgramUniform2i64NV = (glProgramUniform2i64NVFunc)glGetFunction("glProgramUniform2i64NV");
#	endif
#	ifdef glProgramUniform3i64NV
	_glProgramUniform3i64NV = (glProgramUniform3i64NVFunc)glGetFunction("glProgramUniform3i64NV");
#	endif
#	ifdef glProgramUniform4i64NV
	_glProgramUniform4i64NV = (glProgramUniform4i64NVFunc)glGetFunction("glProgramUniform4i64NV");
#	endif
#	ifdef glProgramUniform1i64vNV
	_glProgramUniform1i64vNV = (glProgramUniform1i64vNVFunc)glGetFunction("glProgramUniform1i64vNV");
#	endif
#	ifdef glProgramUniform2i64vNV
	_glProgramUniform2i64vNV = (glProgramUniform2i64vNVFunc)glGetFunction("glProgramUniform2i64vNV");
#	endif
#	ifdef glProgramUniform3i64vNV
	_glProgramUniform3i64vNV = (glProgramUniform3i64vNVFunc)glGetFunction("glProgramUniform3i64vNV");
#	endif
#	ifdef glProgramUniform4i64vNV
	_glProgramUniform4i64vNV = (glProgramUniform4i64vNVFunc)glGetFunction("glProgramUniform4i64vNV");
#	endif
#	ifdef glProgramUniform1ui64NV
	_glProgramUniform1ui64NV = (glProgramUniform1ui64NVFunc)glGetFunction("glProgramUniform1ui64NV");
#	endif
#	ifdef glProgramUniform2ui64NV
	_glProgramUniform2ui64NV = (glProgramUniform2ui64NVFunc)glGetFunction("glProgramUniform2ui64NV");
#	endif
#	ifdef glProgramUniform3ui64NV
	_glProgramUniform3ui64NV = (glProgramUniform3ui64NVFunc)glGetFunction("glProgramUniform3ui64NV");
#	endif
#	ifdef glProgramUniform4ui64NV
	_glProgramUniform4ui64NV = (glProgramUniform4ui64NVFunc)glGetFunction("glProgramUniform4ui64NV");
#	endif
#	ifdef glProgramUniform1ui64vNV
	_glProgramUniform1ui64vNV = (glProgramUniform1ui64vNVFunc)glGetFunction("glProgramUniform1ui64vNV");
#	endif
#	ifdef glProgramUniform2ui64vNV
	_glProgramUniform2ui64vNV = (glProgramUniform2ui64vNVFunc)glGetFunction("glProgramUniform2ui64vNV");
#	endif
#	ifdef glProgramUniform3ui64vNV
	_glProgramUniform3ui64vNV = (glProgramUniform3ui64vNVFunc)glGetFunction("glProgramUniform3ui64vNV");
#	endif
#	ifdef glProgramUniform4ui64vNV
	_glProgramUniform4ui64vNV = (glProgramUniform4ui64vNVFunc)glGetFunction("glProgramUniform4ui64vNV");
#	endif
#	ifdef glVertexAttribL1i64NV
	_glVertexAttribL1i64NV = (glVertexAttribL1i64NVFunc)glGetFunction("glVertexAttribL1i64NV");
#	endif
#	ifdef glVertexAttribL2i64NV
	_glVertexAttribL2i64NV = (glVertexAttribL2i64NVFunc)glGetFunction("glVertexAttribL2i64NV");
#	endif
#	ifdef glVertexAttribL3i64NV
	_glVertexAttribL3i64NV = (glVertexAttribL3i64NVFunc)glGetFunction("glVertexAttribL3i64NV");
#	endif
#	ifdef glVertexAttribL4i64NV
	_glVertexAttribL4i64NV = (glVertexAttribL4i64NVFunc)glGetFunction("glVertexAttribL4i64NV");
#	endif
#	ifdef glVertexAttribL1i64vNV
	_glVertexAttribL1i64vNV = (glVertexAttribL1i64vNVFunc)glGetFunction("glVertexAttribL1i64vNV");
#	endif
#	ifdef glVertexAttribL2i64vNV
	_glVertexAttribL2i64vNV = (glVertexAttribL2i64vNVFunc)glGetFunction("glVertexAttribL2i64vNV");
#	endif
#	ifdef glVertexAttribL3i64vNV
	_glVertexAttribL3i64vNV = (glVertexAttribL3i64vNVFunc)glGetFunction("glVertexAttribL3i64vNV");
#	endif
#	ifdef glVertexAttribL4i64vNV
	_glVertexAttribL4i64vNV = (glVertexAttribL4i64vNVFunc)glGetFunction("glVertexAttribL4i64vNV");
#	endif
#	ifdef glVertexAttribL1ui64NV
	_glVertexAttribL1ui64NV = (glVertexAttribL1ui64NVFunc)glGetFunction("glVertexAttribL1ui64NV");
#	endif
#	ifdef glVertexAttribL2ui64NV
	_glVertexAttribL2ui64NV = (glVertexAttribL2ui64NVFunc)glGetFunction("glVertexAttribL2ui64NV");
#	endif
#	ifdef glVertexAttribL3ui64NV
	_glVertexAttribL3ui64NV = (glVertexAttribL3ui64NVFunc)glGetFunction("glVertexAttribL3ui64NV");
#	endif
#	ifdef glVertexAttribL4ui64NV
	_glVertexAttribL4ui64NV = (glVertexAttribL4ui64NVFunc)glGetFunction("glVertexAttribL4ui64NV");
#	endif
#	ifdef glVertexAttribL1ui64vNV
	_glVertexAttribL1ui64vNV = (glVertexAttribL1ui64vNVFunc)glGetFunction("glVertexAttribL1ui64vNV");
#	endif
#	ifdef glVertexAttribL2ui64vNV
	_glVertexAttribL2ui64vNV = (glVertexAttribL2ui64vNVFunc)glGetFunction("glVertexAttribL2ui64vNV");
#	endif
#	ifdef glVertexAttribL3ui64vNV
	_glVertexAttribL3ui64vNV = (glVertexAttribL3ui64vNVFunc)glGetFunction("glVertexAttribL3ui64vNV");
#	endif
#	ifdef glVertexAttribL4ui64vNV
	_glVertexAttribL4ui64vNV = (glVertexAttribL4ui64vNVFunc)glGetFunction("glVertexAttribL4ui64vNV");
#	endif
#	ifdef glGetVertexAttribLi64vNV
	_glGetVertexAttribLi64vNV = (glGetVertexAttribLi64vNVFunc)glGetFunction("glGetVertexAttribLi64vNV");
#	endif
#	ifdef glGetVertexAttribLui64vNV
	_glGetVertexAttribLui64vNV = (glGetVertexAttribLui64vNVFunc)glGetFunction("glGetVertexAttribLui64vNV");
#	endif
#	ifdef glVertexAttribLFormatNV
	_glVertexAttribLFormatNV = (glVertexAttribLFormatNVFunc)glGetFunction("glVertexAttribLFormatNV");
#	endif
#	ifdef glGenNamesAMD
	_glGenNamesAMD = (glGenNamesAMDFunc)glGetFunction("glGenNamesAMD");
#	endif
#	ifdef glDeleteNamesAMD
	_glDeleteNamesAMD = (glDeleteNamesAMDFunc)glGetFunction("glDeleteNamesAMD");
#	endif
#	ifdef glIsNameAMD
	_glIsNameAMD = (glIsNameAMDFunc)glGetFunction("glIsNameAMD");
#	endif
#	ifdef glDebugMessageEnableAMD
	_glDebugMessageEnableAMD = (glDebugMessageEnableAMDFunc)glGetFunction("glDebugMessageEnableAMD");
#	endif
#	ifdef glDebugMessageInsertAMD
	_glDebugMessageInsertAMD = (glDebugMessageInsertAMDFunc)glGetFunction("glDebugMessageInsertAMD");
#	endif
#	ifdef glDebugMessageCallbackAMD
	_glDebugMessageCallbackAMD = (glDebugMessageCallbackAMDFunc)glGetFunction("glDebugMessageCallbackAMD");
#	endif
#	ifdef glGetDebugMessageLogAMD
	_glGetDebugMessageLogAMD = (glGetDebugMessageLogAMDFunc)glGetFunction("glGetDebugMessageLogAMD");
#	endif
#	ifdef glVDPAUInitNV
	_glVDPAUInitNV = (glVDPAUInitNVFunc)glGetFunction("glVDPAUInitNV");
#	endif
#	ifdef glVDPAUFiniNV
	_glVDPAUFiniNV = (glVDPAUFiniNVFunc)glGetFunction("glVDPAUFiniNV");
#	endif
#	ifdef glVDPAURegisterVideoSurfaceNV
	_glVDPAURegisterVideoSurfaceNV = (glVDPAURegisterVideoSurfaceNVFunc)glGetFunction("glVDPAURegisterVideoSurfaceNV");
#	endif
#	ifdef glVDPAURegisterOutputSurfaceNV
	_glVDPAURegisterOutputSurfaceNV = (glVDPAURegisterOutputSurfaceNVFunc)glGetFunction("glVDPAURegisterOutputSurfaceNV");
#	endif
#	ifdef glVDPAUIsSurfaceNV
	_glVDPAUIsSurfaceNV = (glVDPAUIsSurfaceNVFunc)glGetFunction("glVDPAUIsSurfaceNV");
#	endif
#	ifdef glVDPAUUnregisterSurfaceNV
	_glVDPAUUnregisterSurfaceNV = (glVDPAUUnregisterSurfaceNVFunc)glGetFunction("glVDPAUUnregisterSurfaceNV");
#	endif
#	ifdef glVDPAUGetSurfaceivNV
	_glVDPAUGetSurfaceivNV = (glVDPAUGetSurfaceivNVFunc)glGetFunction("glVDPAUGetSurfaceivNV");
#	endif
#	ifdef glVDPAUSurfaceAccessNV
	_glVDPAUSurfaceAccessNV = (glVDPAUSurfaceAccessNVFunc)glGetFunction("glVDPAUSurfaceAccessNV");
#	endif
#	ifdef glVDPAUMapSurfacesNV
	_glVDPAUMapSurfacesNV = (glVDPAUMapSurfacesNVFunc)glGetFunction("glVDPAUMapSurfacesNV");
#	endif
#	ifdef glVDPAUUnmapSurfacesNV
	_glVDPAUUnmapSurfacesNV = (glVDPAUUnmapSurfacesNVFunc)glGetFunction("glVDPAUUnmapSurfacesNV");
#	endif
#	ifdef glTexImage2DMultisampleCoverageNV
	_glTexImage2DMultisampleCoverageNV = (glTexImage2DMultisampleCoverageNVFunc)glGetFunction("glTexImage2DMultisampleCoverageNV");
#	endif
#	ifdef glTexImage3DMultisampleCoverageNV
	_glTexImage3DMultisampleCoverageNV = (glTexImage3DMultisampleCoverageNVFunc)glGetFunction("glTexImage3DMultisampleCoverageNV");
#	endif
#	ifdef glTextureImage2DMultisampleNV
	_glTextureImage2DMultisampleNV = (glTextureImage2DMultisampleNVFunc)glGetFunction("glTextureImage2DMultisampleNV");
#	endif
#	ifdef glTextureImage3DMultisampleNV
	_glTextureImage3DMultisampleNV = (glTextureImage3DMultisampleNVFunc)glGetFunction("glTextureImage3DMultisampleNV");
#	endif
#	ifdef glTextureImage2DMultisampleCoverageNV
	_glTextureImage2DMultisampleCoverageNV = (glTextureImage2DMultisampleCoverageNVFunc)glGetFunction("glTextureImage2DMultisampleCoverageNV");
#	endif
#	ifdef glTextureImage3DMultisampleCoverageNV
	_glTextureImage3DMultisampleCoverageNV = (glTextureImage3DMultisampleCoverageNVFunc)glGetFunction("glTextureImage3DMultisampleCoverageNV");
#	endif
#	ifdef glSetMultisamplefvAMD
	_glSetMultisamplefvAMD = (glSetMultisamplefvAMDFunc)glGetFunction("glSetMultisamplefvAMD");
#	endif
#	ifdef glImportSyncEXT
	_glImportSyncEXT = (glImportSyncEXTFunc)glGetFunction("glImportSyncEXT");
#	endif
#	ifdef glMultiDrawArraysIndirectAMD
	_glMultiDrawArraysIndirectAMD = (glMultiDrawArraysIndirectAMDFunc)glGetFunction("glMultiDrawArraysIndirectAMD");
#	endif
#	ifdef glMultiDrawElementsIndirectAMD
	_glMultiDrawElementsIndirectAMD = (glMultiDrawElementsIndirectAMDFunc)glGetFunction("glMultiDrawElementsIndirectAMD");
#	endif
#	ifdef glGenPathsNV
	_glGenPathsNV = (glGenPathsNVFunc)glGetFunction("glGenPathsNV");
#	endif
#	ifdef glDeletePathsNV
	_glDeletePathsNV = (glDeletePathsNVFunc)glGetFunction("glDeletePathsNV");
#	endif
#	ifdef glIsPathNV
	_glIsPathNV = (glIsPathNVFunc)glGetFunction("glIsPathNV");
#	endif
#	ifdef glPathCommandsNV
	_glPathCommandsNV = (glPathCommandsNVFunc)glGetFunction("glPathCommandsNV");
#	endif
#	ifdef glPathCoordsNV
	_glPathCoordsNV = (glPathCoordsNVFunc)glGetFunction("glPathCoordsNV");
#	endif
#	ifdef glPathSubCommandsNV
	_glPathSubCommandsNV = (glPathSubCommandsNVFunc)glGetFunction("glPathSubCommandsNV");
#	endif
#	ifdef glPathSubCoordsNV
	_glPathSubCoordsNV = (glPathSubCoordsNVFunc)glGetFunction("glPathSubCoordsNV");
#	endif
#	ifdef glPathStringNV
	_glPathStringNV = (glPathStringNVFunc)glGetFunction("glPathStringNV");
#	endif
#	ifdef glPathGlyphsNV
	_glPathGlyphsNV = (glPathGlyphsNVFunc)glGetFunction("glPathGlyphsNV");
#	endif
#	ifdef glPathGlyphRangeNV
	_glPathGlyphRangeNV = (glPathGlyphRangeNVFunc)glGetFunction("glPathGlyphRangeNV");
#	endif
#	ifdef glWeightPathsNV
	_glWeightPathsNV = (glWeightPathsNVFunc)glGetFunction("glWeightPathsNV");
#	endif
#	ifdef glCopyPathNV
	_glCopyPathNV = (glCopyPathNVFunc)glGetFunction("glCopyPathNV");
#	endif
#	ifdef glInterpolatePathsNV
	_glInterpolatePathsNV = (glInterpolatePathsNVFunc)glGetFunction("glInterpolatePathsNV");
#	endif
#	ifdef glTransformPathNV
	_glTransformPathNV = (glTransformPathNVFunc)glGetFunction("glTransformPathNV");
#	endif
#	ifdef glPathParameterivNV
	_glPathParameterivNV = (glPathParameterivNVFunc)glGetFunction("glPathParameterivNV");
#	endif
#	ifdef glPathParameteriNV
	_glPathParameteriNV = (glPathParameteriNVFunc)glGetFunction("glPathParameteriNV");
#	endif
#	ifdef glPathParameterfvNV
	_glPathParameterfvNV = (glPathParameterfvNVFunc)glGetFunction("glPathParameterfvNV");
#	endif
#	ifdef glPathParameterfNV
	_glPathParameterfNV = (glPathParameterfNVFunc)glGetFunction("glPathParameterfNV");
#	endif
#	ifdef glPathDashArrayNV
	_glPathDashArrayNV = (glPathDashArrayNVFunc)glGetFunction("glPathDashArrayNV");
#	endif
#	ifdef glPathStencilFuncNV
	_glPathStencilFuncNV = (glPathStencilFuncNVFunc)glGetFunction("glPathStencilFuncNV");
#	endif
#	ifdef glPathStencilDepthOffsetNV
	_glPathStencilDepthOffsetNV = (glPathStencilDepthOffsetNVFunc)glGetFunction("glPathStencilDepthOffsetNV");
#	endif
#	ifdef glStencilFillPathNV
	_glStencilFillPathNV = (glStencilFillPathNVFunc)glGetFunction("glStencilFillPathNV");
#	endif
#	ifdef glStencilStrokePathNV
	_glStencilStrokePathNV = (glStencilStrokePathNVFunc)glGetFunction("glStencilStrokePathNV");
#	endif
#	ifdef glStencilFillPathInstancedNV
	_glStencilFillPathInstancedNV = (glStencilFillPathInstancedNVFunc)glGetFunction("glStencilFillPathInstancedNV");
#	endif
#	ifdef glStencilStrokePathInstancedNV
	_glStencilStrokePathInstancedNV = (glStencilStrokePathInstancedNVFunc)glGetFunction("glStencilStrokePathInstancedNV");
#	endif
#	ifdef glPathCoverDepthFuncNV
	_glPathCoverDepthFuncNV = (glPathCoverDepthFuncNVFunc)glGetFunction("glPathCoverDepthFuncNV");
#	endif
#	ifdef glPathColorGenNV
	_glPathColorGenNV = (glPathColorGenNVFunc)glGetFunction("glPathColorGenNV");
#	endif
#	ifdef glPathTexGenNV
	_glPathTexGenNV = (glPathTexGenNVFunc)glGetFunction("glPathTexGenNV");
#	endif
#	ifdef glPathFogGenNV
	_glPathFogGenNV = (glPathFogGenNVFunc)glGetFunction("glPathFogGenNV");
#	endif
#	ifdef glCoverFillPathNV
	_glCoverFillPathNV = (glCoverFillPathNVFunc)glGetFunction("glCoverFillPathNV");
#	endif
#	ifdef glCoverStrokePathNV
	_glCoverStrokePathNV = (glCoverStrokePathNVFunc)glGetFunction("glCoverStrokePathNV");
#	endif
#	ifdef glCoverFillPathInstancedNV
	_glCoverFillPathInstancedNV = (glCoverFillPathInstancedNVFunc)glGetFunction("glCoverFillPathInstancedNV");
#	endif
#	ifdef glCoverStrokePathInstancedNV
	_glCoverStrokePathInstancedNV = (glCoverStrokePathInstancedNVFunc)glGetFunction("glCoverStrokePathInstancedNV");
#	endif
#	ifdef glGetPathParameterivNV
	_glGetPathParameterivNV = (glGetPathParameterivNVFunc)glGetFunction("glGetPathParameterivNV");
#	endif
#	ifdef glGetPathParameterfvNV
	_glGetPathParameterfvNV = (glGetPathParameterfvNVFunc)glGetFunction("glGetPathParameterfvNV");
#	endif
#	ifdef glGetPathCommandsNV
	_glGetPathCommandsNV = (glGetPathCommandsNVFunc)glGetFunction("glGetPathCommandsNV");
#	endif
#	ifdef glGetPathCoordsNV
	_glGetPathCoordsNV = (glGetPathCoordsNVFunc)glGetFunction("glGetPathCoordsNV");
#	endif
#	ifdef glGetPathDashArrayNV
	_glGetPathDashArrayNV = (glGetPathDashArrayNVFunc)glGetFunction("glGetPathDashArrayNV");
#	endif
#	ifdef glGetPathMetricsNV
	_glGetPathMetricsNV = (glGetPathMetricsNVFunc)glGetFunction("glGetPathMetricsNV");
#	endif
#	ifdef glGetPathMetricRangeNV
	_glGetPathMetricRangeNV = (glGetPathMetricRangeNVFunc)glGetFunction("glGetPathMetricRangeNV");
#	endif
#	ifdef glGetPathSpacingNV
	_glGetPathSpacingNV = (glGetPathSpacingNVFunc)glGetFunction("glGetPathSpacingNV");
#	endif
#	ifdef glGetPathColorGenivNV
	_glGetPathColorGenivNV = (glGetPathColorGenivNVFunc)glGetFunction("glGetPathColorGenivNV");
#	endif
#	ifdef glGetPathColorGenfvNV
	_glGetPathColorGenfvNV = (glGetPathColorGenfvNVFunc)glGetFunction("glGetPathColorGenfvNV");
#	endif
#	ifdef glGetPathTexGenivNV
	_glGetPathTexGenivNV = (glGetPathTexGenivNVFunc)glGetFunction("glGetPathTexGenivNV");
#	endif
#	ifdef glGetPathTexGenfvNV
	_glGetPathTexGenfvNV = (glGetPathTexGenfvNVFunc)glGetFunction("glGetPathTexGenfvNV");
#	endif
#	ifdef glIsPointInFillPathNV
	_glIsPointInFillPathNV = (glIsPointInFillPathNVFunc)glGetFunction("glIsPointInFillPathNV");
#	endif
#	ifdef glIsPointInStrokePathNV
	_glIsPointInStrokePathNV = (glIsPointInStrokePathNVFunc)glGetFunction("glIsPointInStrokePathNV");
#	endif
#	ifdef glGetPathLengthNV
	_glGetPathLengthNV = (glGetPathLengthNVFunc)glGetFunction("glGetPathLengthNV");
#	endif
#	ifdef glPointAlongPathNV
	_glPointAlongPathNV = (glPointAlongPathNVFunc)glGetFunction("glPointAlongPathNV");
#	endif
#	ifdef glStencilOpValueAMD
	_glStencilOpValueAMD = (glStencilOpValueAMDFunc)glGetFunction("glStencilOpValueAMD");
#	endif
#	ifdef glGetTextureHandleNV
	_glGetTextureHandleNV = (glGetTextureHandleNVFunc)glGetFunction("glGetTextureHandleNV");
#	endif
#	ifdef glGetTextureSamplerHandleNV
	_glGetTextureSamplerHandleNV = (glGetTextureSamplerHandleNVFunc)glGetFunction("glGetTextureSamplerHandleNV");
#	endif
#	ifdef glMakeTextureHandleResidentNV
	_glMakeTextureHandleResidentNV = (glMakeTextureHandleResidentNVFunc)glGetFunction("glMakeTextureHandleResidentNV");
#	endif
#	ifdef glMakeTextureHandleNonResidentNV
	_glMakeTextureHandleNonResidentNV = (glMakeTextureHandleNonResidentNVFunc)glGetFunction("glMakeTextureHandleNonResidentNV");
#	endif
#	ifdef glGetImageHandleNV
	_glGetImageHandleNV = (glGetImageHandleNVFunc)glGetFunction("glGetImageHandleNV");
#	endif
#	ifdef glMakeImageHandleResidentNV
	_glMakeImageHandleResidentNV = (glMakeImageHandleResidentNVFunc)glGetFunction("glMakeImageHandleResidentNV");
#	endif
#	ifdef glMakeImageHandleNonResidentNV
	_glMakeImageHandleNonResidentNV = (glMakeImageHandleNonResidentNVFunc)glGetFunction("glMakeImageHandleNonResidentNV");
#	endif
#	ifdef glUniformHandleui64NV
	_glUniformHandleui64NV = (glUniformHandleui64NVFunc)glGetFunction("glUniformHandleui64NV");
#	endif
#	ifdef glUniformHandleui64vNV
	_glUniformHandleui64vNV = (glUniformHandleui64vNVFunc)glGetFunction("glUniformHandleui64vNV");
#	endif
#	ifdef glProgramUniformHandleui64NV
	_glProgramUniformHandleui64NV = (glProgramUniformHandleui64NVFunc)glGetFunction("glProgramUniformHandleui64NV");
#	endif
#	ifdef glProgramUniformHandleui64vNV
	_glProgramUniformHandleui64vNV = (glProgramUniformHandleui64vNVFunc)glGetFunction("glProgramUniformHandleui64vNV");
#	endif
#	ifdef glIsTextureHandleResidentNV
	_glIsTextureHandleResidentNV = (glIsTextureHandleResidentNVFunc)glGetFunction("glIsTextureHandleResidentNV");
#	endif
#	ifdef glIsImageHandleResidentNV
	_glIsImageHandleResidentNV = (glIsImageHandleResidentNVFunc)glGetFunction("glIsImageHandleResidentNV");
#	endif
#	ifdef glTexStorageSparseAMD
	_glTexStorageSparseAMD = (glTexStorageSparseAMDFunc)glGetFunction("glTexStorageSparseAMD");
#	endif
#	ifdef glTextureStorageSparseAMD
	_glTextureStorageSparseAMD = (glTextureStorageSparseAMDFunc)glGetFunction("glTextureStorageSparseAMD");
#	endif
}

void glFuncUnload()
{
#	ifdef glCullFace
	_glCullFace = NULL;
#	endif
#	ifdef glFrontFace
	_glFrontFace = NULL;
#	endif
#	ifdef glHint
	_glHint = NULL;
#	endif
#	ifdef glLineWidth
	_glLineWidth = NULL;
#	endif
#	ifdef glPointSize
	_glPointSize = NULL;
#	endif
#	ifdef glPolygonMode
	_glPolygonMode = NULL;
#	endif
#	ifdef glScissor
	_glScissor = NULL;
#	endif
#	ifdef glTexParameterf
	_glTexParameterf = NULL;
#	endif
#	ifdef glTexParameterfv
	_glTexParameterfv = NULL;
#	endif
#	ifdef glTexParameteri
	_glTexParameteri = NULL;
#	endif
#	ifdef glTexParameteriv
	_glTexParameteriv = NULL;
#	endif
#	ifdef glTexImage1D
	_glTexImage1D = NULL;
#	endif
#	ifdef glTexImage2D
	_glTexImage2D = NULL;
#	endif
#	ifdef glDrawBuffer
	_glDrawBuffer = NULL;
#	endif
#	ifdef glClear
	_glClear = NULL;
#	endif
#	ifdef glClearColor
	_glClearColor = NULL;
#	endif
#	ifdef glClearStencil
	_glClearStencil = NULL;
#	endif
#	ifdef glClearDepth
	_glClearDepth = NULL;
#	endif
#	ifdef glStencilMask
	_glStencilMask = NULL;
#	endif
#	ifdef glColorMask
	_glColorMask = NULL;
#	endif
#	ifdef glDepthMask
	_glDepthMask = NULL;
#	endif
#	ifdef glDisable
	_glDisable = NULL;
#	endif
#	ifdef glEnable
	_glEnable = NULL;
#	endif
#	ifdef glFinish
	_glFinish = NULL;
#	endif
#	ifdef glFlush
	_glFlush = NULL;
#	endif
#	ifdef glBlendFunc
	_glBlendFunc = NULL;
#	endif
#	ifdef glLogicOp
	_glLogicOp = NULL;
#	endif
#	ifdef glStencilFunc
	_glStencilFunc = NULL;
#	endif
#	ifdef glStencilOp
	_glStencilOp = NULL;
#	endif
#	ifdef glDepthFunc
	_glDepthFunc = NULL;
#	endif
#	ifdef glPixelStoref
	_glPixelStoref = NULL;
#	endif
#	ifdef glPixelStorei
	_glPixelStorei = NULL;
#	endif
#	ifdef glReadBuffer
	_glReadBuffer = NULL;
#	endif
#	ifdef glReadPixels
	_glReadPixels = NULL;
#	endif
#	ifdef glGetBooleanv
	_glGetBooleanv = NULL;
#	endif
#	ifdef glGetDoublev
	_glGetDoublev = NULL;
#	endif
#	ifdef glGetError
	_glGetError = NULL;
#	endif
#	ifdef glGetFloatv
	_glGetFloatv = NULL;
#	endif
#	ifdef glGetIntegerv
	_glGetIntegerv = NULL;
#	endif
#	ifdef glGetString
	_glGetString = NULL;
#	endif
#	ifdef glGetTexImage
	_glGetTexImage = NULL;
#	endif
#	ifdef glGetTexParameterfv
	_glGetTexParameterfv = NULL;
#	endif
#	ifdef glGetTexParameteriv
	_glGetTexParameteriv = NULL;
#	endif
#	ifdef glGetTexLevelParameterfv
	_glGetTexLevelParameterfv = NULL;
#	endif
#	ifdef glGetTexLevelParameteriv
	_glGetTexLevelParameteriv = NULL;
#	endif
#	ifdef glIsEnabled
	_glIsEnabled = NULL;
#	endif
#	ifdef glDepthRange
	_glDepthRange = NULL;
#	endif
#	ifdef glViewport
	_glViewport = NULL;
#	endif
#	ifdef glNewList
	_glNewList = NULL;
#	endif
#	ifdef glEndList
	_glEndList = NULL;
#	endif
#	ifdef glCallList
	_glCallList = NULL;
#	endif
#	ifdef glCallLists
	_glCallLists = NULL;
#	endif
#	ifdef glDeleteLists
	_glDeleteLists = NULL;
#	endif
#	ifdef glGenLists
	_glGenLists = NULL;
#	endif
#	ifdef glListBase
	_glListBase = NULL;
#	endif
#	ifdef glBegin
	_glBegin = NULL;
#	endif
#	ifdef glBitmap
	_glBitmap = NULL;
#	endif
#	ifdef glColor3b
	_glColor3b = NULL;
#	endif
#	ifdef glColor3bv
	_glColor3bv = NULL;
#	endif
#	ifdef glColor3d
	_glColor3d = NULL;
#	endif
#	ifdef glColor3dv
	_glColor3dv = NULL;
#	endif
#	ifdef glColor3f
	_glColor3f = NULL;
#	endif
#	ifdef glColor3fv
	_glColor3fv = NULL;
#	endif
#	ifdef glColor3i
	_glColor3i = NULL;
#	endif
#	ifdef glColor3iv
	_glColor3iv = NULL;
#	endif
#	ifdef glColor3s
	_glColor3s = NULL;
#	endif
#	ifdef glColor3sv
	_glColor3sv = NULL;
#	endif
#	ifdef glColor3ub
	_glColor3ub = NULL;
#	endif
#	ifdef glColor3ubv
	_glColor3ubv = NULL;
#	endif
#	ifdef glColor3ui
	_glColor3ui = NULL;
#	endif
#	ifdef glColor3uiv
	_glColor3uiv = NULL;
#	endif
#	ifdef glColor3us
	_glColor3us = NULL;
#	endif
#	ifdef glColor3usv
	_glColor3usv = NULL;
#	endif
#	ifdef glColor4b
	_glColor4b = NULL;
#	endif
#	ifdef glColor4bv
	_glColor4bv = NULL;
#	endif
#	ifdef glColor4d
	_glColor4d = NULL;
#	endif
#	ifdef glColor4dv
	_glColor4dv = NULL;
#	endif
#	ifdef glColor4f
	_glColor4f = NULL;
#	endif
#	ifdef glColor4fv
	_glColor4fv = NULL;
#	endif
#	ifdef glColor4i
	_glColor4i = NULL;
#	endif
#	ifdef glColor4iv
	_glColor4iv = NULL;
#	endif
#	ifdef glColor4s
	_glColor4s = NULL;
#	endif
#	ifdef glColor4sv
	_glColor4sv = NULL;
#	endif
#	ifdef glColor4ub
	_glColor4ub = NULL;
#	endif
#	ifdef glColor4ubv
	_glColor4ubv = NULL;
#	endif
#	ifdef glColor4ui
	_glColor4ui = NULL;
#	endif
#	ifdef glColor4uiv
	_glColor4uiv = NULL;
#	endif
#	ifdef glColor4us
	_glColor4us = NULL;
#	endif
#	ifdef glColor4usv
	_glColor4usv = NULL;
#	endif
#	ifdef glEdgeFlag
	_glEdgeFlag = NULL;
#	endif
#	ifdef glEdgeFlagv
	_glEdgeFlagv = NULL;
#	endif
#	ifdef glEnd
	_glEnd = NULL;
#	endif
#	ifdef glIndexd
	_glIndexd = NULL;
#	endif
#	ifdef glIndexdv
	_glIndexdv = NULL;
#	endif
#	ifdef glIndexf
	_glIndexf = NULL;
#	endif
#	ifdef glIndexfv
	_glIndexfv = NULL;
#	endif
#	ifdef glIndexi
	_glIndexi = NULL;
#	endif
#	ifdef glIndexiv
	_glIndexiv = NULL;
#	endif
#	ifdef glIndexs
	_glIndexs = NULL;
#	endif
#	ifdef glIndexsv
	_glIndexsv = NULL;
#	endif
#	ifdef glNormal3b
	_glNormal3b = NULL;
#	endif
#	ifdef glNormal3bv
	_glNormal3bv = NULL;
#	endif
#	ifdef glNormal3d
	_glNormal3d = NULL;
#	endif
#	ifdef glNormal3dv
	_glNormal3dv = NULL;
#	endif
#	ifdef glNormal3f
	_glNormal3f = NULL;
#	endif
#	ifdef glNormal3fv
	_glNormal3fv = NULL;
#	endif
#	ifdef glNormal3i
	_glNormal3i = NULL;
#	endif
#	ifdef glNormal3iv
	_glNormal3iv = NULL;
#	endif
#	ifdef glNormal3s
	_glNormal3s = NULL;
#	endif
#	ifdef glNormal3sv
	_glNormal3sv = NULL;
#	endif
#	ifdef glRasterPos2d
	_glRasterPos2d = NULL;
#	endif
#	ifdef glRasterPos2dv
	_glRasterPos2dv = NULL;
#	endif
#	ifdef glRasterPos2f
	_glRasterPos2f = NULL;
#	endif
#	ifdef glRasterPos2fv
	_glRasterPos2fv = NULL;
#	endif
#	ifdef glRasterPos2i
	_glRasterPos2i = NULL;
#	endif
#	ifdef glRasterPos2iv
	_glRasterPos2iv = NULL;
#	endif
#	ifdef glRasterPos2s
	_glRasterPos2s = NULL;
#	endif
#	ifdef glRasterPos2sv
	_glRasterPos2sv = NULL;
#	endif
#	ifdef glRasterPos3d
	_glRasterPos3d = NULL;
#	endif
#	ifdef glRasterPos3dv
	_glRasterPos3dv = NULL;
#	endif
#	ifdef glRasterPos3f
	_glRasterPos3f = NULL;
#	endif
#	ifdef glRasterPos3fv
	_glRasterPos3fv = NULL;
#	endif
#	ifdef glRasterPos3i
	_glRasterPos3i = NULL;
#	endif
#	ifdef glRasterPos3iv
	_glRasterPos3iv = NULL;
#	endif
#	ifdef glRasterPos3s
	_glRasterPos3s = NULL;
#	endif
#	ifdef glRasterPos3sv
	_glRasterPos3sv = NULL;
#	endif
#	ifdef glRasterPos4d
	_glRasterPos4d = NULL;
#	endif
#	ifdef glRasterPos4dv
	_glRasterPos4dv = NULL;
#	endif
#	ifdef glRasterPos4f
	_glRasterPos4f = NULL;
#	endif
#	ifdef glRasterPos4fv
	_glRasterPos4fv = NULL;
#	endif
#	ifdef glRasterPos4i
	_glRasterPos4i = NULL;
#	endif
#	ifdef glRasterPos4iv
	_glRasterPos4iv = NULL;
#	endif
#	ifdef glRasterPos4s
	_glRasterPos4s = NULL;
#	endif
#	ifdef glRasterPos4sv
	_glRasterPos4sv = NULL;
#	endif
#	ifdef glRectd
	_glRectd = NULL;
#	endif
#	ifdef glRectdv
	_glRectdv = NULL;
#	endif
#	ifdef glRectf
	_glRectf = NULL;
#	endif
#	ifdef glRectfv
	_glRectfv = NULL;
#	endif
#	ifdef glRecti
	_glRecti = NULL;
#	endif
#	ifdef glRectiv
	_glRectiv = NULL;
#	endif
#	ifdef glRects
	_glRects = NULL;
#	endif
#	ifdef glRectsv
	_glRectsv = NULL;
#	endif
#	ifdef glTexCoord1d
	_glTexCoord1d = NULL;
#	endif
#	ifdef glTexCoord1dv
	_glTexCoord1dv = NULL;
#	endif
#	ifdef glTexCoord1f
	_glTexCoord1f = NULL;
#	endif
#	ifdef glTexCoord1fv
	_glTexCoord1fv = NULL;
#	endif
#	ifdef glTexCoord1i
	_glTexCoord1i = NULL;
#	endif
#	ifdef glTexCoord1iv
	_glTexCoord1iv = NULL;
#	endif
#	ifdef glTexCoord1s
	_glTexCoord1s = NULL;
#	endif
#	ifdef glTexCoord1sv
	_glTexCoord1sv = NULL;
#	endif
#	ifdef glTexCoord2d
	_glTexCoord2d = NULL;
#	endif
#	ifdef glTexCoord2dv
	_glTexCoord2dv = NULL;
#	endif
#	ifdef glTexCoord2f
	_glTexCoord2f = NULL;
#	endif
#	ifdef glTexCoord2fv
	_glTexCoord2fv = NULL;
#	endif
#	ifdef glTexCoord2i
	_glTexCoord2i = NULL;
#	endif
#	ifdef glTexCoord2iv
	_glTexCoord2iv = NULL;
#	endif
#	ifdef glTexCoord2s
	_glTexCoord2s = NULL;
#	endif
#	ifdef glTexCoord2sv
	_glTexCoord2sv = NULL;
#	endif
#	ifdef glTexCoord3d
	_glTexCoord3d = NULL;
#	endif
#	ifdef glTexCoord3dv
	_glTexCoord3dv = NULL;
#	endif
#	ifdef glTexCoord3f
	_glTexCoord3f = NULL;
#	endif
#	ifdef glTexCoord3fv
	_glTexCoord3fv = NULL;
#	endif
#	ifdef glTexCoord3i
	_glTexCoord3i = NULL;
#	endif
#	ifdef glTexCoord3iv
	_glTexCoord3iv = NULL;
#	endif
#	ifdef glTexCoord3s
	_glTexCoord3s = NULL;
#	endif
#	ifdef glTexCoord3sv
	_glTexCoord3sv = NULL;
#	endif
#	ifdef glTexCoord4d
	_glTexCoord4d = NULL;
#	endif
#	ifdef glTexCoord4dv
	_glTexCoord4dv = NULL;
#	endif
#	ifdef glTexCoord4f
	_glTexCoord4f = NULL;
#	endif
#	ifdef glTexCoord4fv
	_glTexCoord4fv = NULL;
#	endif
#	ifdef glTexCoord4i
	_glTexCoord4i = NULL;
#	endif
#	ifdef glTexCoord4iv
	_glTexCoord4iv = NULL;
#	endif
#	ifdef glTexCoord4s
	_glTexCoord4s = NULL;
#	endif
#	ifdef glTexCoord4sv
	_glTexCoord4sv = NULL;
#	endif
#	ifdef glVertex2d
	_glVertex2d = NULL;
#	endif
#	ifdef glVertex2dv
	_glVertex2dv = NULL;
#	endif
#	ifdef glVertex2f
	_glVertex2f = NULL;
#	endif
#	ifdef glVertex2fv
	_glVertex2fv = NULL;
#	endif
#	ifdef glVertex2i
	_glVertex2i = NULL;
#	endif
#	ifdef glVertex2iv
	_glVertex2iv = NULL;
#	endif
#	ifdef glVertex2s
	_glVertex2s = NULL;
#	endif
#	ifdef glVertex2sv
	_glVertex2sv = NULL;
#	endif
#	ifdef glVertex3d
	_glVertex3d = NULL;
#	endif
#	ifdef glVertex3dv
	_glVertex3dv = NULL;
#	endif
#	ifdef glVertex3f
	_glVertex3f = NULL;
#	endif
#	ifdef glVertex3fv
	_glVertex3fv = NULL;
#	endif
#	ifdef glVertex3i
	_glVertex3i = NULL;
#	endif
#	ifdef glVertex3iv
	_glVertex3iv = NULL;
#	endif
#	ifdef glVertex3s
	_glVertex3s = NULL;
#	endif
#	ifdef glVertex3sv
	_glVertex3sv = NULL;
#	endif
#	ifdef glVertex4d
	_glVertex4d = NULL;
#	endif
#	ifdef glVertex4dv
	_glVertex4dv = NULL;
#	endif
#	ifdef glVertex4f
	_glVertex4f = NULL;
#	endif
#	ifdef glVertex4fv
	_glVertex4fv = NULL;
#	endif
#	ifdef glVertex4i
	_glVertex4i = NULL;
#	endif
#	ifdef glVertex4iv
	_glVertex4iv = NULL;
#	endif
#	ifdef glVertex4s
	_glVertex4s = NULL;
#	endif
#	ifdef glVertex4sv
	_glVertex4sv = NULL;
#	endif
#	ifdef glClipPlane
	_glClipPlane = NULL;
#	endif
#	ifdef glColorMaterial
	_glColorMaterial = NULL;
#	endif
#	ifdef glFogf
	_glFogf = NULL;
#	endif
#	ifdef glFogfv
	_glFogfv = NULL;
#	endif
#	ifdef glFogi
	_glFogi = NULL;
#	endif
#	ifdef glFogiv
	_glFogiv = NULL;
#	endif
#	ifdef glLightf
	_glLightf = NULL;
#	endif
#	ifdef glLightfv
	_glLightfv = NULL;
#	endif
#	ifdef glLighti
	_glLighti = NULL;
#	endif
#	ifdef glLightiv
	_glLightiv = NULL;
#	endif
#	ifdef glLightModelf
	_glLightModelf = NULL;
#	endif
#	ifdef glLightModelfv
	_glLightModelfv = NULL;
#	endif
#	ifdef glLightModeli
	_glLightModeli = NULL;
#	endif
#	ifdef glLightModeliv
	_glLightModeliv = NULL;
#	endif
#	ifdef glLineStipple
	_glLineStipple = NULL;
#	endif
#	ifdef glMaterialf
	_glMaterialf = NULL;
#	endif
#	ifdef glMaterialfv
	_glMaterialfv = NULL;
#	endif
#	ifdef glMateriali
	_glMateriali = NULL;
#	endif
#	ifdef glMaterialiv
	_glMaterialiv = NULL;
#	endif
#	ifdef glPolygonStipple
	_glPolygonStipple = NULL;
#	endif
#	ifdef glShadeModel
	_glShadeModel = NULL;
#	endif
#	ifdef glTexEnvf
	_glTexEnvf = NULL;
#	endif
#	ifdef glTexEnvfv
	_glTexEnvfv = NULL;
#	endif
#	ifdef glTexEnvi
	_glTexEnvi = NULL;
#	endif
#	ifdef glTexEnviv
	_glTexEnviv = NULL;
#	endif
#	ifdef glTexGend
	_glTexGend = NULL;
#	endif
#	ifdef glTexGendv
	_glTexGendv = NULL;
#	endif
#	ifdef glTexGenf
	_glTexGenf = NULL;
#	endif
#	ifdef glTexGenfv
	_glTexGenfv = NULL;
#	endif
#	ifdef glTexGeni
	_glTexGeni = NULL;
#	endif
#	ifdef glTexGeniv
	_glTexGeniv = NULL;
#	endif
#	ifdef glFeedbackBuffer
	_glFeedbackBuffer = NULL;
#	endif
#	ifdef glSelectBuffer
	_glSelectBuffer = NULL;
#	endif
#	ifdef glRenderMode
	_glRenderMode = NULL;
#	endif
#	ifdef glInitNames
	_glInitNames = NULL;
#	endif
#	ifdef glLoadName
	_glLoadName = NULL;
#	endif
#	ifdef glPassThrough
	_glPassThrough = NULL;
#	endif
#	ifdef glPopName
	_glPopName = NULL;
#	endif
#	ifdef glPushName
	_glPushName = NULL;
#	endif
#	ifdef glClearAccum
	_glClearAccum = NULL;
#	endif
#	ifdef glClearIndex
	_glClearIndex = NULL;
#	endif
#	ifdef glIndexMask
	_glIndexMask = NULL;
#	endif
#	ifdef glAccum
	_glAccum = NULL;
#	endif
#	ifdef glPopAttrib
	_glPopAttrib = NULL;
#	endif
#	ifdef glPushAttrib
	_glPushAttrib = NULL;
#	endif
#	ifdef glMap1d
	_glMap1d = NULL;
#	endif
#	ifdef glMap1f
	_glMap1f = NULL;
#	endif
#	ifdef glMap2d
	_glMap2d = NULL;
#	endif
#	ifdef glMap2f
	_glMap2f = NULL;
#	endif
#	ifdef glMapGrid1d
	_glMapGrid1d = NULL;
#	endif
#	ifdef glMapGrid1f
	_glMapGrid1f = NULL;
#	endif
#	ifdef glMapGrid2d
	_glMapGrid2d = NULL;
#	endif
#	ifdef glMapGrid2f
	_glMapGrid2f = NULL;
#	endif
#	ifdef glEvalCoord1d
	_glEvalCoord1d = NULL;
#	endif
#	ifdef glEvalCoord1dv
	_glEvalCoord1dv = NULL;
#	endif
#	ifdef glEvalCoord1f
	_glEvalCoord1f = NULL;
#	endif
#	ifdef glEvalCoord1fv
	_glEvalCoord1fv = NULL;
#	endif
#	ifdef glEvalCoord2d
	_glEvalCoord2d = NULL;
#	endif
#	ifdef glEvalCoord2dv
	_glEvalCoord2dv = NULL;
#	endif
#	ifdef glEvalCoord2f
	_glEvalCoord2f = NULL;
#	endif
#	ifdef glEvalCoord2fv
	_glEvalCoord2fv = NULL;
#	endif
#	ifdef glEvalMesh1
	_glEvalMesh1 = NULL;
#	endif
#	ifdef glEvalPoint1
	_glEvalPoint1 = NULL;
#	endif
#	ifdef glEvalMesh2
	_glEvalMesh2 = NULL;
#	endif
#	ifdef glEvalPoint2
	_glEvalPoint2 = NULL;
#	endif
#	ifdef glAlphaFunc
	_glAlphaFunc = NULL;
#	endif
#	ifdef glPixelZoom
	_glPixelZoom = NULL;
#	endif
#	ifdef glPixelTransferf
	_glPixelTransferf = NULL;
#	endif
#	ifdef glPixelTransferi
	_glPixelTransferi = NULL;
#	endif
#	ifdef glPixelMapfv
	_glPixelMapfv = NULL;
#	endif
#	ifdef glPixelMapuiv
	_glPixelMapuiv = NULL;
#	endif
#	ifdef glPixelMapusv
	_glPixelMapusv = NULL;
#	endif
#	ifdef glCopyPixels
	_glCopyPixels = NULL;
#	endif
#	ifdef glDrawPixels
	_glDrawPixels = NULL;
#	endif
#	ifdef glGetClipPlane
	_glGetClipPlane = NULL;
#	endif
#	ifdef glGetLightfv
	_glGetLightfv = NULL;
#	endif
#	ifdef glGetLightiv
	_glGetLightiv = NULL;
#	endif
#	ifdef glGetMapdv
	_glGetMapdv = NULL;
#	endif
#	ifdef glGetMapfv
	_glGetMapfv = NULL;
#	endif
#	ifdef glGetMapiv
	_glGetMapiv = NULL;
#	endif
#	ifdef glGetMaterialfv
	_glGetMaterialfv = NULL;
#	endif
#	ifdef glGetMaterialiv
	_glGetMaterialiv = NULL;
#	endif
#	ifdef glGetPixelMapfv
	_glGetPixelMapfv = NULL;
#	endif
#	ifdef glGetPixelMapuiv
	_glGetPixelMapuiv = NULL;
#	endif
#	ifdef glGetPixelMapusv
	_glGetPixelMapusv = NULL;
#	endif
#	ifdef glGetPolygonStipple
	_glGetPolygonStipple = NULL;
#	endif
#	ifdef glGetTexEnvfv
	_glGetTexEnvfv = NULL;
#	endif
#	ifdef glGetTexEnviv
	_glGetTexEnviv = NULL;
#	endif
#	ifdef glGetTexGendv
	_glGetTexGendv = NULL;
#	endif
#	ifdef glGetTexGenfv
	_glGetTexGenfv = NULL;
#	endif
#	ifdef glGetTexGeniv
	_glGetTexGeniv = NULL;
#	endif
#	ifdef glIsList
	_glIsList = NULL;
#	endif
#	ifdef glFrustum
	_glFrustum = NULL;
#	endif
#	ifdef glLoadIdentity
	_glLoadIdentity = NULL;
#	endif
#	ifdef glLoadMatrixf
	_glLoadMatrixf = NULL;
#	endif
#	ifdef glLoadMatrixd
	_glLoadMatrixd = NULL;
#	endif
#	ifdef glMatrixMode
	_glMatrixMode = NULL;
#	endif
#	ifdef glMultMatrixf
	_glMultMatrixf = NULL;
#	endif
#	ifdef glMultMatrixd
	_glMultMatrixd = NULL;
#	endif
#	ifdef glOrtho
	_glOrtho = NULL;
#	endif
#	ifdef glPopMatrix
	_glPopMatrix = NULL;
#	endif
#	ifdef glPushMatrix
	_glPushMatrix = NULL;
#	endif
#	ifdef glRotated
	_glRotated = NULL;
#	endif
#	ifdef glRotatef
	_glRotatef = NULL;
#	endif
#	ifdef glScaled
	_glScaled = NULL;
#	endif
#	ifdef glScalef
	_glScalef = NULL;
#	endif
#	ifdef glTranslated
	_glTranslated = NULL;
#	endif
#	ifdef glTranslatef
	_glTranslatef = NULL;
#	endif
#	ifdef glDrawArrays
	_glDrawArrays = NULL;
#	endif
#	ifdef glDrawElements
	_glDrawElements = NULL;
#	endif
#	ifdef glGetPointerv
	_glGetPointerv = NULL;
#	endif
#	ifdef glPolygonOffset
	_glPolygonOffset = NULL;
#	endif
#	ifdef glCopyTexImage1D
	_glCopyTexImage1D = NULL;
#	endif
#	ifdef glCopyTexImage2D
	_glCopyTexImage2D = NULL;
#	endif
#	ifdef glCopyTexSubImage1D
	_glCopyTexSubImage1D = NULL;
#	endif
#	ifdef glCopyTexSubImage2D
	_glCopyTexSubImage2D = NULL;
#	endif
#	ifdef glTexSubImage1D
	_glTexSubImage1D = NULL;
#	endif
#	ifdef glTexSubImage2D
	_glTexSubImage2D = NULL;
#	endif
#	ifdef glBindTexture
	_glBindTexture = NULL;
#	endif
#	ifdef glDeleteTextures
	_glDeleteTextures = NULL;
#	endif
#	ifdef glGenTextures
	_glGenTextures = NULL;
#	endif
#	ifdef glIsTexture
	_glIsTexture = NULL;
#	endif
#	ifdef glArrayElement
	_glArrayElement = NULL;
#	endif
#	ifdef glColorPointer
	_glColorPointer = NULL;
#	endif
#	ifdef glDisableClientState
	_glDisableClientState = NULL;
#	endif
#	ifdef glEdgeFlagPointer
	_glEdgeFlagPointer = NULL;
#	endif
#	ifdef glEnableClientState
	_glEnableClientState = NULL;
#	endif
#	ifdef glIndexPointer
	_glIndexPointer = NULL;
#	endif
#	ifdef glInterleavedArrays
	_glInterleavedArrays = NULL;
#	endif
#	ifdef glNormalPointer
	_glNormalPointer = NULL;
#	endif
#	ifdef glTexCoordPointer
	_glTexCoordPointer = NULL;
#	endif
#	ifdef glVertexPointer
	_glVertexPointer = NULL;
#	endif
#	ifdef glAreTexturesResident
	_glAreTexturesResident = NULL;
#	endif
#	ifdef glPrioritizeTextures
	_glPrioritizeTextures = NULL;
#	endif
#	ifdef glIndexub
	_glIndexub = NULL;
#	endif
#	ifdef glIndexubv
	_glIndexubv = NULL;
#	endif
#	ifdef glPopClientAttrib
	_glPopClientAttrib = NULL;
#	endif
#	ifdef glPushClientAttrib
	_glPushClientAttrib = NULL;
#	endif
#	ifdef glBlendColor
	_glBlendColor = NULL;
#	endif
#	ifdef glBlendEquation
	_glBlendEquation = NULL;
#	endif
#	ifdef glDrawRangeElements
	_glDrawRangeElements = NULL;
#	endif
#	ifdef glTexImage3D
	_glTexImage3D = NULL;
#	endif
#	ifdef glTexSubImage3D
	_glTexSubImage3D = NULL;
#	endif
#	ifdef glCopyTexSubImage3D
	_glCopyTexSubImage3D = NULL;
#	endif
#	ifdef glColorTable
	_glColorTable = NULL;
#	endif
#	ifdef glColorTableParameterfv
	_glColorTableParameterfv = NULL;
#	endif
#	ifdef glColorTableParameteriv
	_glColorTableParameteriv = NULL;
#	endif
#	ifdef glCopyColorTable
	_glCopyColorTable = NULL;
#	endif
#	ifdef glGetColorTable
	_glGetColorTable = NULL;
#	endif
#	ifdef glGetColorTableParameterfv
	_glGetColorTableParameterfv = NULL;
#	endif
#	ifdef glGetColorTableParameteriv
	_glGetColorTableParameteriv = NULL;
#	endif
#	ifdef glColorSubTable
	_glColorSubTable = NULL;
#	endif
#	ifdef glCopyColorSubTable
	_glCopyColorSubTable = NULL;
#	endif
#	ifdef glConvolutionFilter1D
	_glConvolutionFilter1D = NULL;
#	endif
#	ifdef glConvolutionFilter2D
	_glConvolutionFilter2D = NULL;
#	endif
#	ifdef glConvolutionParameterf
	_glConvolutionParameterf = NULL;
#	endif
#	ifdef glConvolutionParameterfv
	_glConvolutionParameterfv = NULL;
#	endif
#	ifdef glConvolutionParameteri
	_glConvolutionParameteri = NULL;
#	endif
#	ifdef glConvolutionParameteriv
	_glConvolutionParameteriv = NULL;
#	endif
#	ifdef glCopyConvolutionFilter1D
	_glCopyConvolutionFilter1D = NULL;
#	endif
#	ifdef glCopyConvolutionFilter2D
	_glCopyConvolutionFilter2D = NULL;
#	endif
#	ifdef glGetConvolutionFilter
	_glGetConvolutionFilter = NULL;
#	endif
#	ifdef glGetConvolutionParameterfv
	_glGetConvolutionParameterfv = NULL;
#	endif
#	ifdef glGetConvolutionParameteriv
	_glGetConvolutionParameteriv = NULL;
#	endif
#	ifdef glGetSeparableFilter
	_glGetSeparableFilter = NULL;
#	endif
#	ifdef glSeparableFilter2D
	_glSeparableFilter2D = NULL;
#	endif
#	ifdef glGetHistogram
	_glGetHistogram = NULL;
#	endif
#	ifdef glGetHistogramParameterfv
	_glGetHistogramParameterfv = NULL;
#	endif
#	ifdef glGetHistogramParameteriv
	_glGetHistogramParameteriv = NULL;
#	endif
#	ifdef glGetMinmax
	_glGetMinmax = NULL;
#	endif
#	ifdef glGetMinmaxParameterfv
	_glGetMinmaxParameterfv = NULL;
#	endif
#	ifdef glGetMinmaxParameteriv
	_glGetMinmaxParameteriv = NULL;
#	endif
#	ifdef glHistogram
	_glHistogram = NULL;
#	endif
#	ifdef glMinmax
	_glMinmax = NULL;
#	endif
#	ifdef glResetHistogram
	_glResetHistogram = NULL;
#	endif
#	ifdef glResetMinmax
	_glResetMinmax = NULL;
#	endif
#	ifdef glActiveTexture
	_glActiveTexture = NULL;
#	endif
#	ifdef glSampleCoverage
	_glSampleCoverage = NULL;
#	endif
#	ifdef glCompressedTexImage3D
	_glCompressedTexImage3D = NULL;
#	endif
#	ifdef glCompressedTexImage2D
	_glCompressedTexImage2D = NULL;
#	endif
#	ifdef glCompressedTexImage1D
	_glCompressedTexImage1D = NULL;
#	endif
#	ifdef glCompressedTexSubImage3D
	_glCompressedTexSubImage3D = NULL;
#	endif
#	ifdef glCompressedTexSubImage2D
	_glCompressedTexSubImage2D = NULL;
#	endif
#	ifdef glCompressedTexSubImage1D
	_glCompressedTexSubImage1D = NULL;
#	endif
#	ifdef glGetCompressedTexImage
	_glGetCompressedTexImage = NULL;
#	endif
#	ifdef glClientActiveTexture
	_glClientActiveTexture = NULL;
#	endif
#	ifdef glMultiTexCoord1d
	_glMultiTexCoord1d = NULL;
#	endif
#	ifdef glMultiTexCoord1dv
	_glMultiTexCoord1dv = NULL;
#	endif
#	ifdef glMultiTexCoord1f
	_glMultiTexCoord1f = NULL;
#	endif
#	ifdef glMultiTexCoord1fv
	_glMultiTexCoord1fv = NULL;
#	endif
#	ifdef glMultiTexCoord1i
	_glMultiTexCoord1i = NULL;
#	endif
#	ifdef glMultiTexCoord1iv
	_glMultiTexCoord1iv = NULL;
#	endif
#	ifdef glMultiTexCoord1s
	_glMultiTexCoord1s = NULL;
#	endif
#	ifdef glMultiTexCoord1sv
	_glMultiTexCoord1sv = NULL;
#	endif
#	ifdef glMultiTexCoord2d
	_glMultiTexCoord2d = NULL;
#	endif
#	ifdef glMultiTexCoord2dv
	_glMultiTexCoord2dv = NULL;
#	endif
#	ifdef glMultiTexCoord2f
	_glMultiTexCoord2f = NULL;
#	endif
#	ifdef glMultiTexCoord2fv
	_glMultiTexCoord2fv = NULL;
#	endif
#	ifdef glMultiTexCoord2i
	_glMultiTexCoord2i = NULL;
#	endif
#	ifdef glMultiTexCoord2iv
	_glMultiTexCoord2iv = NULL;
#	endif
#	ifdef glMultiTexCoord2s
	_glMultiTexCoord2s = NULL;
#	endif
#	ifdef glMultiTexCoord2sv
	_glMultiTexCoord2sv = NULL;
#	endif
#	ifdef glMultiTexCoord3d
	_glMultiTexCoord3d = NULL;
#	endif
#	ifdef glMultiTexCoord3dv
	_glMultiTexCoord3dv = NULL;
#	endif
#	ifdef glMultiTexCoord3f
	_glMultiTexCoord3f = NULL;
#	endif
#	ifdef glMultiTexCoord3fv
	_glMultiTexCoord3fv = NULL;
#	endif
#	ifdef glMultiTexCoord3i
	_glMultiTexCoord3i = NULL;
#	endif
#	ifdef glMultiTexCoord3iv
	_glMultiTexCoord3iv = NULL;
#	endif
#	ifdef glMultiTexCoord3s
	_glMultiTexCoord3s = NULL;
#	endif
#	ifdef glMultiTexCoord3sv
	_glMultiTexCoord3sv = NULL;
#	endif
#	ifdef glMultiTexCoord4d
	_glMultiTexCoord4d = NULL;
#	endif
#	ifdef glMultiTexCoord4dv
	_glMultiTexCoord4dv = NULL;
#	endif
#	ifdef glMultiTexCoord4f
	_glMultiTexCoord4f = NULL;
#	endif
#	ifdef glMultiTexCoord4fv
	_glMultiTexCoord4fv = NULL;
#	endif
#	ifdef glMultiTexCoord4i
	_glMultiTexCoord4i = NULL;
#	endif
#	ifdef glMultiTexCoord4iv
	_glMultiTexCoord4iv = NULL;
#	endif
#	ifdef glMultiTexCoord4s
	_glMultiTexCoord4s = NULL;
#	endif
#	ifdef glMultiTexCoord4sv
	_glMultiTexCoord4sv = NULL;
#	endif
#	ifdef glLoadTransposeMatrixf
	_glLoadTransposeMatrixf = NULL;
#	endif
#	ifdef glLoadTransposeMatrixd
	_glLoadTransposeMatrixd = NULL;
#	endif
#	ifdef glMultTransposeMatrixf
	_glMultTransposeMatrixf = NULL;
#	endif
#	ifdef glMultTransposeMatrixd
	_glMultTransposeMatrixd = NULL;
#	endif
#	ifdef glBlendFuncSeparate
	_glBlendFuncSeparate = NULL;
#	endif
#	ifdef glMultiDrawArrays
	_glMultiDrawArrays = NULL;
#	endif
#	ifdef glMultiDrawElements
	_glMultiDrawElements = NULL;
#	endif
#	ifdef glPointParameterf
	_glPointParameterf = NULL;
#	endif
#	ifdef glPointParameterfv
	_glPointParameterfv = NULL;
#	endif
#	ifdef glPointParameteri
	_glPointParameteri = NULL;
#	endif
#	ifdef glPointParameteriv
	_glPointParameteriv = NULL;
#	endif
#	ifdef glFogCoordf
	_glFogCoordf = NULL;
#	endif
#	ifdef glFogCoordfv
	_glFogCoordfv = NULL;
#	endif
#	ifdef glFogCoordd
	_glFogCoordd = NULL;
#	endif
#	ifdef glFogCoorddv
	_glFogCoorddv = NULL;
#	endif
#	ifdef glFogCoordPointer
	_glFogCoordPointer = NULL;
#	endif
#	ifdef glSecondaryColor3b
	_glSecondaryColor3b = NULL;
#	endif
#	ifdef glSecondaryColor3bv
	_glSecondaryColor3bv = NULL;
#	endif
#	ifdef glSecondaryColor3d
	_glSecondaryColor3d = NULL;
#	endif
#	ifdef glSecondaryColor3dv
	_glSecondaryColor3dv = NULL;
#	endif
#	ifdef glSecondaryColor3f
	_glSecondaryColor3f = NULL;
#	endif
#	ifdef glSecondaryColor3fv
	_glSecondaryColor3fv = NULL;
#	endif
#	ifdef glSecondaryColor3i
	_glSecondaryColor3i = NULL;
#	endif
#	ifdef glSecondaryColor3iv
	_glSecondaryColor3iv = NULL;
#	endif
#	ifdef glSecondaryColor3s
	_glSecondaryColor3s = NULL;
#	endif
#	ifdef glSecondaryColor3sv
	_glSecondaryColor3sv = NULL;
#	endif
#	ifdef glSecondaryColor3ub
	_glSecondaryColor3ub = NULL;
#	endif
#	ifdef glSecondaryColor3ubv
	_glSecondaryColor3ubv = NULL;
#	endif
#	ifdef glSecondaryColor3ui
	_glSecondaryColor3ui = NULL;
#	endif
#	ifdef glSecondaryColor3uiv
	_glSecondaryColor3uiv = NULL;
#	endif
#	ifdef glSecondaryColor3us
	_glSecondaryColor3us = NULL;
#	endif
#	ifdef glSecondaryColor3usv
	_glSecondaryColor3usv = NULL;
#	endif
#	ifdef glSecondaryColorPointer
	_glSecondaryColorPointer = NULL;
#	endif
#	ifdef glWindowPos2d
	_glWindowPos2d = NULL;
#	endif
#	ifdef glWindowPos2dv
	_glWindowPos2dv = NULL;
#	endif
#	ifdef glWindowPos2f
	_glWindowPos2f = NULL;
#	endif
#	ifdef glWindowPos2fv
	_glWindowPos2fv = NULL;
#	endif
#	ifdef glWindowPos2i
	_glWindowPos2i = NULL;
#	endif
#	ifdef glWindowPos2iv
	_glWindowPos2iv = NULL;
#	endif
#	ifdef glWindowPos2s
	_glWindowPos2s = NULL;
#	endif
#	ifdef glWindowPos2sv
	_glWindowPos2sv = NULL;
#	endif
#	ifdef glWindowPos3d
	_glWindowPos3d = NULL;
#	endif
#	ifdef glWindowPos3dv
	_glWindowPos3dv = NULL;
#	endif
#	ifdef glWindowPos3f
	_glWindowPos3f = NULL;
#	endif
#	ifdef glWindowPos3fv
	_glWindowPos3fv = NULL;
#	endif
#	ifdef glWindowPos3i
	_glWindowPos3i = NULL;
#	endif
#	ifdef glWindowPos3iv
	_glWindowPos3iv = NULL;
#	endif
#	ifdef glWindowPos3s
	_glWindowPos3s = NULL;
#	endif
#	ifdef glWindowPos3sv
	_glWindowPos3sv = NULL;
#	endif
#	ifdef glGenQueries
	_glGenQueries = NULL;
#	endif
#	ifdef glDeleteQueries
	_glDeleteQueries = NULL;
#	endif
#	ifdef glIsQuery
	_glIsQuery = NULL;
#	endif
#	ifdef glBeginQuery
	_glBeginQuery = NULL;
#	endif
#	ifdef glEndQuery
	_glEndQuery = NULL;
#	endif
#	ifdef glGetQueryiv
	_glGetQueryiv = NULL;
#	endif
#	ifdef glGetQueryObjectiv
	_glGetQueryObjectiv = NULL;
#	endif
#	ifdef glGetQueryObjectuiv
	_glGetQueryObjectuiv = NULL;
#	endif
#	ifdef glBindBuffer
	_glBindBuffer = NULL;
#	endif
#	ifdef glDeleteBuffers
	_glDeleteBuffers = NULL;
#	endif
#	ifdef glGenBuffers
	_glGenBuffers = NULL;
#	endif
#	ifdef glIsBuffer
	_glIsBuffer = NULL;
#	endif
#	ifdef glBufferData
	_glBufferData = NULL;
#	endif
#	ifdef glBufferSubData
	_glBufferSubData = NULL;
#	endif
#	ifdef glGetBufferSubData
	_glGetBufferSubData = NULL;
#	endif
#	ifdef glMapBuffer
	_glMapBuffer = NULL;
#	endif
#	ifdef glUnmapBuffer
	_glUnmapBuffer = NULL;
#	endif
#	ifdef glGetBufferParameteriv
	_glGetBufferParameteriv = NULL;
#	endif
#	ifdef glGetBufferPointerv
	_glGetBufferPointerv = NULL;
#	endif
#	ifdef glBlendEquationSeparate
	_glBlendEquationSeparate = NULL;
#	endif
#	ifdef glDrawBuffers
	_glDrawBuffers = NULL;
#	endif
#	ifdef glStencilOpSeparate
	_glStencilOpSeparate = NULL;
#	endif
#	ifdef glStencilFuncSeparate
	_glStencilFuncSeparate = NULL;
#	endif
#	ifdef glStencilMaskSeparate
	_glStencilMaskSeparate = NULL;
#	endif
#	ifdef glAttachShader
	_glAttachShader = NULL;
#	endif
#	ifdef glBindAttribLocation
	_glBindAttribLocation = NULL;
#	endif
#	ifdef glCompileShader
	_glCompileShader = NULL;
#	endif
#	ifdef glCreateProgram
	_glCreateProgram = NULL;
#	endif
#	ifdef glCreateShader
	_glCreateShader = NULL;
#	endif
#	ifdef glDeleteProgram
	_glDeleteProgram = NULL;
#	endif
#	ifdef glDeleteShader
	_glDeleteShader = NULL;
#	endif
#	ifdef glDetachShader
	_glDetachShader = NULL;
#	endif
#	ifdef glDisableVertexAttribArray
	_glDisableVertexAttribArray = NULL;
#	endif
#	ifdef glEnableVertexAttribArray
	_glEnableVertexAttribArray = NULL;
#	endif
#	ifdef glGetActiveAttrib
	_glGetActiveAttrib = NULL;
#	endif
#	ifdef glGetActiveUniform
	_glGetActiveUniform = NULL;
#	endif
#	ifdef glGetAttachedShaders
	_glGetAttachedShaders = NULL;
#	endif
#	ifdef glGetAttribLocation
	_glGetAttribLocation = NULL;
#	endif
#	ifdef glGetProgramiv
	_glGetProgramiv = NULL;
#	endif
#	ifdef glGetProgramInfoLog
	_glGetProgramInfoLog = NULL;
#	endif
#	ifdef glGetShaderiv
	_glGetShaderiv = NULL;
#	endif
#	ifdef glGetShaderInfoLog
	_glGetShaderInfoLog = NULL;
#	endif
#	ifdef glGetShaderSource
	_glGetShaderSource = NULL;
#	endif
#	ifdef glGetUniformLocation
	_glGetUniformLocation = NULL;
#	endif
#	ifdef glGetUniformfv
	_glGetUniformfv = NULL;
#	endif
#	ifdef glGetUniformiv
	_glGetUniformiv = NULL;
#	endif
#	ifdef glGetVertexAttribdv
	_glGetVertexAttribdv = NULL;
#	endif
#	ifdef glGetVertexAttribfv
	_glGetVertexAttribfv = NULL;
#	endif
#	ifdef glGetVertexAttribiv
	_glGetVertexAttribiv = NULL;
#	endif
#	ifdef glGetVertexAttribPointerv
	_glGetVertexAttribPointerv = NULL;
#	endif
#	ifdef glIsProgram
	_glIsProgram = NULL;
#	endif
#	ifdef glIsShader
	_glIsShader = NULL;
#	endif
#	ifdef glLinkProgram
	_glLinkProgram = NULL;
#	endif
#	ifdef glShaderSource
	_glShaderSource = NULL;
#	endif
#	ifdef glUseProgram
	_glUseProgram = NULL;
#	endif
#	ifdef glUniform1f
	_glUniform1f = NULL;
#	endif
#	ifdef glUniform2f
	_glUniform2f = NULL;
#	endif
#	ifdef glUniform3f
	_glUniform3f = NULL;
#	endif
#	ifdef glUniform4f
	_glUniform4f = NULL;
#	endif
#	ifdef glUniform1i
	_glUniform1i = NULL;
#	endif
#	ifdef glUniform2i
	_glUniform2i = NULL;
#	endif
#	ifdef glUniform3i
	_glUniform3i = NULL;
#	endif
#	ifdef glUniform4i
	_glUniform4i = NULL;
#	endif
#	ifdef glUniform1fv
	_glUniform1fv = NULL;
#	endif
#	ifdef glUniform2fv
	_glUniform2fv = NULL;
#	endif
#	ifdef glUniform3fv
	_glUniform3fv = NULL;
#	endif
#	ifdef glUniform4fv
	_glUniform4fv = NULL;
#	endif
#	ifdef glUniform1iv
	_glUniform1iv = NULL;
#	endif
#	ifdef glUniform2iv
	_glUniform2iv = NULL;
#	endif
#	ifdef glUniform3iv
	_glUniform3iv = NULL;
#	endif
#	ifdef glUniform4iv
	_glUniform4iv = NULL;
#	endif
#	ifdef glUniformMatrix2fv
	_glUniformMatrix2fv = NULL;
#	endif
#	ifdef glUniformMatrix3fv
	_glUniformMatrix3fv = NULL;
#	endif
#	ifdef glUniformMatrix4fv
	_glUniformMatrix4fv = NULL;
#	endif
#	ifdef glValidateProgram
	_glValidateProgram = NULL;
#	endif
#	ifdef glVertexAttrib1d
	_glVertexAttrib1d = NULL;
#	endif
#	ifdef glVertexAttrib1dv
	_glVertexAttrib1dv = NULL;
#	endif
#	ifdef glVertexAttrib1f
	_glVertexAttrib1f = NULL;
#	endif
#	ifdef glVertexAttrib1fv
	_glVertexAttrib1fv = NULL;
#	endif
#	ifdef glVertexAttrib1s
	_glVertexAttrib1s = NULL;
#	endif
#	ifdef glVertexAttrib1sv
	_glVertexAttrib1sv = NULL;
#	endif
#	ifdef glVertexAttrib2d
	_glVertexAttrib2d = NULL;
#	endif
#	ifdef glVertexAttrib2dv
	_glVertexAttrib2dv = NULL;
#	endif
#	ifdef glVertexAttrib2f
	_glVertexAttrib2f = NULL;
#	endif
#	ifdef glVertexAttrib2fv
	_glVertexAttrib2fv = NULL;
#	endif
#	ifdef glVertexAttrib2s
	_glVertexAttrib2s = NULL;
#	endif
#	ifdef glVertexAttrib2sv
	_glVertexAttrib2sv = NULL;
#	endif
#	ifdef glVertexAttrib3d
	_glVertexAttrib3d = NULL;
#	endif
#	ifdef glVertexAttrib3dv
	_glVertexAttrib3dv = NULL;
#	endif
#	ifdef glVertexAttrib3f
	_glVertexAttrib3f = NULL;
#	endif
#	ifdef glVertexAttrib3fv
	_glVertexAttrib3fv = NULL;
#	endif
#	ifdef glVertexAttrib3s
	_glVertexAttrib3s = NULL;
#	endif
#	ifdef glVertexAttrib3sv
	_glVertexAttrib3sv = NULL;
#	endif
#	ifdef glVertexAttrib4Nbv
	_glVertexAttrib4Nbv = NULL;
#	endif
#	ifdef glVertexAttrib4Niv
	_glVertexAttrib4Niv = NULL;
#	endif
#	ifdef glVertexAttrib4Nsv
	_glVertexAttrib4Nsv = NULL;
#	endif
#	ifdef glVertexAttrib4Nub
	_glVertexAttrib4Nub = NULL;
#	endif
#	ifdef glVertexAttrib4Nubv
	_glVertexAttrib4Nubv = NULL;
#	endif
#	ifdef glVertexAttrib4Nuiv
	_glVertexAttrib4Nuiv = NULL;
#	endif
#	ifdef glVertexAttrib4Nusv
	_glVertexAttrib4Nusv = NULL;
#	endif
#	ifdef glVertexAttrib4bv
	_glVertexAttrib4bv = NULL;
#	endif
#	ifdef glVertexAttrib4d
	_glVertexAttrib4d = NULL;
#	endif
#	ifdef glVertexAttrib4dv
	_glVertexAttrib4dv = NULL;
#	endif
#	ifdef glVertexAttrib4f
	_glVertexAttrib4f = NULL;
#	endif
#	ifdef glVertexAttrib4fv
	_glVertexAttrib4fv = NULL;
#	endif
#	ifdef glVertexAttrib4iv
	_glVertexAttrib4iv = NULL;
#	endif
#	ifdef glVertexAttrib4s
	_glVertexAttrib4s = NULL;
#	endif
#	ifdef glVertexAttrib4sv
	_glVertexAttrib4sv = NULL;
#	endif
#	ifdef glVertexAttrib4ubv
	_glVertexAttrib4ubv = NULL;
#	endif
#	ifdef glVertexAttrib4uiv
	_glVertexAttrib4uiv = NULL;
#	endif
#	ifdef glVertexAttrib4usv
	_glVertexAttrib4usv = NULL;
#	endif
#	ifdef glVertexAttribPointer
	_glVertexAttribPointer = NULL;
#	endif
#	ifdef glUniformMatrix2x3fv
	_glUniformMatrix2x3fv = NULL;
#	endif
#	ifdef glUniformMatrix3x2fv
	_glUniformMatrix3x2fv = NULL;
#	endif
#	ifdef glUniformMatrix2x4fv
	_glUniformMatrix2x4fv = NULL;
#	endif
#	ifdef glUniformMatrix4x2fv
	_glUniformMatrix4x2fv = NULL;
#	endif
#	ifdef glUniformMatrix3x4fv
	_glUniformMatrix3x4fv = NULL;
#	endif
#	ifdef glUniformMatrix4x3fv
	_glUniformMatrix4x3fv = NULL;
#	endif
#	ifdef glColorMaski
	_glColorMaski = NULL;
#	endif
#	ifdef glGetBooleani_v
	_glGetBooleani_v = NULL;
#	endif
#	ifdef glGetIntegeri_v
	_glGetIntegeri_v = NULL;
#	endif
#	ifdef glEnablei
	_glEnablei = NULL;
#	endif
#	ifdef glDisablei
	_glDisablei = NULL;
#	endif
#	ifdef glIsEnabledi
	_glIsEnabledi = NULL;
#	endif
#	ifdef glBeginTransformFeedback
	_glBeginTransformFeedback = NULL;
#	endif
#	ifdef glEndTransformFeedback
	_glEndTransformFeedback = NULL;
#	endif
#	ifdef glBindBufferRange
	_glBindBufferRange = NULL;
#	endif
#	ifdef glBindBufferBase
	_glBindBufferBase = NULL;
#	endif
#	ifdef glTransformFeedbackVaryings
	_glTransformFeedbackVaryings = NULL;
#	endif
#	ifdef glGetTransformFeedbackVarying
	_glGetTransformFeedbackVarying = NULL;
#	endif
#	ifdef glClampColor
	_glClampColor = NULL;
#	endif
#	ifdef glBeginConditionalRender
	_glBeginConditionalRender = NULL;
#	endif
#	ifdef glEndConditionalRender
	_glEndConditionalRender = NULL;
#	endif
#	ifdef glVertexAttribIPointer
	_glVertexAttribIPointer = NULL;
#	endif
#	ifdef glGetVertexAttribIiv
	_glGetVertexAttribIiv = NULL;
#	endif
#	ifdef glGetVertexAttribIuiv
	_glGetVertexAttribIuiv = NULL;
#	endif
#	ifdef glVertexAttribI1i
	_glVertexAttribI1i = NULL;
#	endif
#	ifdef glVertexAttribI2i
	_glVertexAttribI2i = NULL;
#	endif
#	ifdef glVertexAttribI3i
	_glVertexAttribI3i = NULL;
#	endif
#	ifdef glVertexAttribI4i
	_glVertexAttribI4i = NULL;
#	endif
#	ifdef glVertexAttribI1ui
	_glVertexAttribI1ui = NULL;
#	endif
#	ifdef glVertexAttribI2ui
	_glVertexAttribI2ui = NULL;
#	endif
#	ifdef glVertexAttribI3ui
	_glVertexAttribI3ui = NULL;
#	endif
#	ifdef glVertexAttribI4ui
	_glVertexAttribI4ui = NULL;
#	endif
#	ifdef glVertexAttribI1iv
	_glVertexAttribI1iv = NULL;
#	endif
#	ifdef glVertexAttribI2iv
	_glVertexAttribI2iv = NULL;
#	endif
#	ifdef glVertexAttribI3iv
	_glVertexAttribI3iv = NULL;
#	endif
#	ifdef glVertexAttribI4iv
	_glVertexAttribI4iv = NULL;
#	endif
#	ifdef glVertexAttribI1uiv
	_glVertexAttribI1uiv = NULL;
#	endif
#	ifdef glVertexAttribI2uiv
	_glVertexAttribI2uiv = NULL;
#	endif
#	ifdef glVertexAttribI3uiv
	_glVertexAttribI3uiv = NULL;
#	endif
#	ifdef glVertexAttribI4uiv
	_glVertexAttribI4uiv = NULL;
#	endif
#	ifdef glVertexAttribI4bv
	_glVertexAttribI4bv = NULL;
#	endif
#	ifdef glVertexAttribI4sv
	_glVertexAttribI4sv = NULL;
#	endif
#	ifdef glVertexAttribI4ubv
	_glVertexAttribI4ubv = NULL;
#	endif
#	ifdef glVertexAttribI4usv
	_glVertexAttribI4usv = NULL;
#	endif
#	ifdef glGetUniformuiv
	_glGetUniformuiv = NULL;
#	endif
#	ifdef glBindFragDataLocation
	_glBindFragDataLocation = NULL;
#	endif
#	ifdef glGetFragDataLocation
	_glGetFragDataLocation = NULL;
#	endif
#	ifdef glUniform1ui
	_glUniform1ui = NULL;
#	endif
#	ifdef glUniform2ui
	_glUniform2ui = NULL;
#	endif
#	ifdef glUniform3ui
	_glUniform3ui = NULL;
#	endif
#	ifdef glUniform4ui
	_glUniform4ui = NULL;
#	endif
#	ifdef glUniform1uiv
	_glUniform1uiv = NULL;
#	endif
#	ifdef glUniform2uiv
	_glUniform2uiv = NULL;
#	endif
#	ifdef glUniform3uiv
	_glUniform3uiv = NULL;
#	endif
#	ifdef glUniform4uiv
	_glUniform4uiv = NULL;
#	endif
#	ifdef glTexParameterIiv
	_glTexParameterIiv = NULL;
#	endif
#	ifdef glTexParameterIuiv
	_glTexParameterIuiv = NULL;
#	endif
#	ifdef glGetTexParameterIiv
	_glGetTexParameterIiv = NULL;
#	endif
#	ifdef glGetTexParameterIuiv
	_glGetTexParameterIuiv = NULL;
#	endif
#	ifdef glClearBufferiv
	_glClearBufferiv = NULL;
#	endif
#	ifdef glClearBufferuiv
	_glClearBufferuiv = NULL;
#	endif
#	ifdef glClearBufferfv
	_glClearBufferfv = NULL;
#	endif
#	ifdef glClearBufferfi
	_glClearBufferfi = NULL;
#	endif
#	ifdef glGetStringi
	_glGetStringi = NULL;
#	endif
#	ifdef glDrawArraysInstanced
	_glDrawArraysInstanced = NULL;
#	endif
#	ifdef glDrawElementsInstanced
	_glDrawElementsInstanced = NULL;
#	endif
#	ifdef glTexBuffer
	_glTexBuffer = NULL;
#	endif
#	ifdef glPrimitiveRestartIndex
	_glPrimitiveRestartIndex = NULL;
#	endif
#	ifdef glGetInteger64i_v
	_glGetInteger64i_v = NULL;
#	endif
#	ifdef glGetBufferParameteri64v
	_glGetBufferParameteri64v = NULL;
#	endif
#	ifdef glFramebufferTexture
	_glFramebufferTexture = NULL;
#	endif
#	ifdef glVertexAttribDivisor
	_glVertexAttribDivisor = NULL;
#	endif
#	ifdef glMinSampleShading
	_glMinSampleShading = NULL;
#	endif
#	ifdef glBlendEquationi
	_glBlendEquationi = NULL;
#	endif
#	ifdef glBlendEquationSeparatei
	_glBlendEquationSeparatei = NULL;
#	endif
#	ifdef glBlendFunci
	_glBlendFunci = NULL;
#	endif
#	ifdef glBlendFuncSeparatei
	_glBlendFuncSeparatei = NULL;
#	endif
#	ifdef glActiveTextureARB
	_glActiveTextureARB = NULL;
#	endif
#	ifdef glClientActiveTextureARB
	_glClientActiveTextureARB = NULL;
#	endif
#	ifdef glMultiTexCoord1dARB
	_glMultiTexCoord1dARB = NULL;
#	endif
#	ifdef glMultiTexCoord1dvARB
	_glMultiTexCoord1dvARB = NULL;
#	endif
#	ifdef glMultiTexCoord1fARB
	_glMultiTexCoord1fARB = NULL;
#	endif
#	ifdef glMultiTexCoord1fvARB
	_glMultiTexCoord1fvARB = NULL;
#	endif
#	ifdef glMultiTexCoord1iARB
	_glMultiTexCoord1iARB = NULL;
#	endif
#	ifdef glMultiTexCoord1ivARB
	_glMultiTexCoord1ivARB = NULL;
#	endif
#	ifdef glMultiTexCoord1sARB
	_glMultiTexCoord1sARB = NULL;
#	endif
#	ifdef glMultiTexCoord1svARB
	_glMultiTexCoord1svARB = NULL;
#	endif
#	ifdef glMultiTexCoord2dARB
	_glMultiTexCoord2dARB = NULL;
#	endif
#	ifdef glMultiTexCoord2dvARB
	_glMultiTexCoord2dvARB = NULL;
#	endif
#	ifdef glMultiTexCoord2fARB
	_glMultiTexCoord2fARB = NULL;
#	endif
#	ifdef glMultiTexCoord2fvARB
	_glMultiTexCoord2fvARB = NULL;
#	endif
#	ifdef glMultiTexCoord2iARB
	_glMultiTexCoord2iARB = NULL;
#	endif
#	ifdef glMultiTexCoord2ivARB
	_glMultiTexCoord2ivARB = NULL;
#	endif
#	ifdef glMultiTexCoord2sARB
	_glMultiTexCoord2sARB = NULL;
#	endif
#	ifdef glMultiTexCoord2svARB
	_glMultiTexCoord2svARB = NULL;
#	endif
#	ifdef glMultiTexCoord3dARB
	_glMultiTexCoord3dARB = NULL;
#	endif
#	ifdef glMultiTexCoord3dvARB
	_glMultiTexCoord3dvARB = NULL;
#	endif
#	ifdef glMultiTexCoord3fARB
	_glMultiTexCoord3fARB = NULL;
#	endif
#	ifdef glMultiTexCoord3fvARB
	_glMultiTexCoord3fvARB = NULL;
#	endif
#	ifdef glMultiTexCoord3iARB
	_glMultiTexCoord3iARB = NULL;
#	endif
#	ifdef glMultiTexCoord3ivARB
	_glMultiTexCoord3ivARB = NULL;
#	endif
#	ifdef glMultiTexCoord3sARB
	_glMultiTexCoord3sARB = NULL;
#	endif
#	ifdef glMultiTexCoord3svARB
	_glMultiTexCoord3svARB = NULL;
#	endif
#	ifdef glMultiTexCoord4dARB
	_glMultiTexCoord4dARB = NULL;
#	endif
#	ifdef glMultiTexCoord4dvARB
	_glMultiTexCoord4dvARB = NULL;
#	endif
#	ifdef glMultiTexCoord4fARB
	_glMultiTexCoord4fARB = NULL;
#	endif
#	ifdef glMultiTexCoord4fvARB
	_glMultiTexCoord4fvARB = NULL;
#	endif
#	ifdef glMultiTexCoord4iARB
	_glMultiTexCoord4iARB = NULL;
#	endif
#	ifdef glMultiTexCoord4ivARB
	_glMultiTexCoord4ivARB = NULL;
#	endif
#	ifdef glMultiTexCoord4sARB
	_glMultiTexCoord4sARB = NULL;
#	endif
#	ifdef glMultiTexCoord4svARB
	_glMultiTexCoord4svARB = NULL;
#	endif
#	ifdef glLoadTransposeMatrixfARB
	_glLoadTransposeMatrixfARB = NULL;
#	endif
#	ifdef glLoadTransposeMatrixdARB
	_glLoadTransposeMatrixdARB = NULL;
#	endif
#	ifdef glMultTransposeMatrixfARB
	_glMultTransposeMatrixfARB = NULL;
#	endif
#	ifdef glMultTransposeMatrixdARB
	_glMultTransposeMatrixdARB = NULL;
#	endif
#	ifdef glSampleCoverageARB
	_glSampleCoverageARB = NULL;
#	endif
#	ifdef glCompressedTexImage3DARB
	_glCompressedTexImage3DARB = NULL;
#	endif
#	ifdef glCompressedTexImage2DARB
	_glCompressedTexImage2DARB = NULL;
#	endif
#	ifdef glCompressedTexImage1DARB
	_glCompressedTexImage1DARB = NULL;
#	endif
#	ifdef glCompressedTexSubImage3DARB
	_glCompressedTexSubImage3DARB = NULL;
#	endif
#	ifdef glCompressedTexSubImage2DARB
	_glCompressedTexSubImage2DARB = NULL;
#	endif
#	ifdef glCompressedTexSubImage1DARB
	_glCompressedTexSubImage1DARB = NULL;
#	endif
#	ifdef glGetCompressedTexImageARB
	_glGetCompressedTexImageARB = NULL;
#	endif
#	ifdef glPointParameterfARB
	_glPointParameterfARB = NULL;
#	endif
#	ifdef glPointParameterfvARB
	_glPointParameterfvARB = NULL;
#	endif
#	ifdef glWeightbvARB
	_glWeightbvARB = NULL;
#	endif
#	ifdef glWeightsvARB
	_glWeightsvARB = NULL;
#	endif
#	ifdef glWeightivARB
	_glWeightivARB = NULL;
#	endif
#	ifdef glWeightfvARB
	_glWeightfvARB = NULL;
#	endif
#	ifdef glWeightdvARB
	_glWeightdvARB = NULL;
#	endif
#	ifdef glWeightubvARB
	_glWeightubvARB = NULL;
#	endif
#	ifdef glWeightusvARB
	_glWeightusvARB = NULL;
#	endif
#	ifdef glWeightuivARB
	_glWeightuivARB = NULL;
#	endif
#	ifdef glWeightPointerARB
	_glWeightPointerARB = NULL;
#	endif
#	ifdef glVertexBlendARB
	_glVertexBlendARB = NULL;
#	endif
#	ifdef glCurrentPaletteMatrixARB
	_glCurrentPaletteMatrixARB = NULL;
#	endif
#	ifdef glMatrixIndexubvARB
	_glMatrixIndexubvARB = NULL;
#	endif
#	ifdef glMatrixIndexusvARB
	_glMatrixIndexusvARB = NULL;
#	endif
#	ifdef glMatrixIndexuivARB
	_glMatrixIndexuivARB = NULL;
#	endif
#	ifdef glMatrixIndexPointerARB
	_glMatrixIndexPointerARB = NULL;
#	endif
#	ifdef glWindowPos2dARB
	_glWindowPos2dARB = NULL;
#	endif
#	ifdef glWindowPos2dvARB
	_glWindowPos2dvARB = NULL;
#	endif
#	ifdef glWindowPos2fARB
	_glWindowPos2fARB = NULL;
#	endif
#	ifdef glWindowPos2fvARB
	_glWindowPos2fvARB = NULL;
#	endif
#	ifdef glWindowPos2iARB
	_glWindowPos2iARB = NULL;
#	endif
#	ifdef glWindowPos2ivARB
	_glWindowPos2ivARB = NULL;
#	endif
#	ifdef glWindowPos2sARB
	_glWindowPos2sARB = NULL;
#	endif
#	ifdef glWindowPos2svARB
	_glWindowPos2svARB = NULL;
#	endif
#	ifdef glWindowPos3dARB
	_glWindowPos3dARB = NULL;
#	endif
#	ifdef glWindowPos3dvARB
	_glWindowPos3dvARB = NULL;
#	endif
#	ifdef glWindowPos3fARB
	_glWindowPos3fARB = NULL;
#	endif
#	ifdef glWindowPos3fvARB
	_glWindowPos3fvARB = NULL;
#	endif
#	ifdef glWindowPos3iARB
	_glWindowPos3iARB = NULL;
#	endif
#	ifdef glWindowPos3ivARB
	_glWindowPos3ivARB = NULL;
#	endif
#	ifdef glWindowPos3sARB
	_glWindowPos3sARB = NULL;
#	endif
#	ifdef glWindowPos3svARB
	_glWindowPos3svARB = NULL;
#	endif
#	ifdef glVertexAttrib1dARB
	_glVertexAttrib1dARB = NULL;
#	endif
#	ifdef glVertexAttrib1dvARB
	_glVertexAttrib1dvARB = NULL;
#	endif
#	ifdef glVertexAttrib1fARB
	_glVertexAttrib1fARB = NULL;
#	endif
#	ifdef glVertexAttrib1fvARB
	_glVertexAttrib1fvARB = NULL;
#	endif
#	ifdef glVertexAttrib1sARB
	_glVertexAttrib1sARB = NULL;
#	endif
#	ifdef glVertexAttrib1svARB
	_glVertexAttrib1svARB = NULL;
#	endif
#	ifdef glVertexAttrib2dARB
	_glVertexAttrib2dARB = NULL;
#	endif
#	ifdef glVertexAttrib2dvARB
	_glVertexAttrib2dvARB = NULL;
#	endif
#	ifdef glVertexAttrib2fARB
	_glVertexAttrib2fARB = NULL;
#	endif
#	ifdef glVertexAttrib2fvARB
	_glVertexAttrib2fvARB = NULL;
#	endif
#	ifdef glVertexAttrib2sARB
	_glVertexAttrib2sARB = NULL;
#	endif
#	ifdef glVertexAttrib2svARB
	_glVertexAttrib2svARB = NULL;
#	endif
#	ifdef glVertexAttrib3dARB
	_glVertexAttrib3dARB = NULL;
#	endif
#	ifdef glVertexAttrib3dvARB
	_glVertexAttrib3dvARB = NULL;
#	endif
#	ifdef glVertexAttrib3fARB
	_glVertexAttrib3fARB = NULL;
#	endif
#	ifdef glVertexAttrib3fvARB
	_glVertexAttrib3fvARB = NULL;
#	endif
#	ifdef glVertexAttrib3sARB
	_glVertexAttrib3sARB = NULL;
#	endif
#	ifdef glVertexAttrib3svARB
	_glVertexAttrib3svARB = NULL;
#	endif
#	ifdef glVertexAttrib4NbvARB
	_glVertexAttrib4NbvARB = NULL;
#	endif
#	ifdef glVertexAttrib4NivARB
	_glVertexAttrib4NivARB = NULL;
#	endif
#	ifdef glVertexAttrib4NsvARB
	_glVertexAttrib4NsvARB = NULL;
#	endif
#	ifdef glVertexAttrib4NubARB
	_glVertexAttrib4NubARB = NULL;
#	endif
#	ifdef glVertexAttrib4NubvARB
	_glVertexAttrib4NubvARB = NULL;
#	endif
#	ifdef glVertexAttrib4NuivARB
	_glVertexAttrib4NuivARB = NULL;
#	endif
#	ifdef glVertexAttrib4NusvARB
	_glVertexAttrib4NusvARB = NULL;
#	endif
#	ifdef glVertexAttrib4bvARB
	_glVertexAttrib4bvARB = NULL;
#	endif
#	ifdef glVertexAttrib4dARB
	_glVertexAttrib4dARB = NULL;
#	endif
#	ifdef glVertexAttrib4dvARB
	_glVertexAttrib4dvARB = NULL;
#	endif
#	ifdef glVertexAttrib4fARB
	_glVertexAttrib4fARB = NULL;
#	endif
#	ifdef glVertexAttrib4fvARB
	_glVertexAttrib4fvARB = NULL;
#	endif
#	ifdef glVertexAttrib4ivARB
	_glVertexAttrib4ivARB = NULL;
#	endif
#	ifdef glVertexAttrib4sARB
	_glVertexAttrib4sARB = NULL;
#	endif
#	ifdef glVertexAttrib4svARB
	_glVertexAttrib4svARB = NULL;
#	endif
#	ifdef glVertexAttrib4ubvARB
	_glVertexAttrib4ubvARB = NULL;
#	endif
#	ifdef glVertexAttrib4uivARB
	_glVertexAttrib4uivARB = NULL;
#	endif
#	ifdef glVertexAttrib4usvARB
	_glVertexAttrib4usvARB = NULL;
#	endif
#	ifdef glVertexAttribPointerARB
	_glVertexAttribPointerARB = NULL;
#	endif
#	ifdef glEnableVertexAttribArrayARB
	_glEnableVertexAttribArrayARB = NULL;
#	endif
#	ifdef glDisableVertexAttribArrayARB
	_glDisableVertexAttribArrayARB = NULL;
#	endif
#	ifdef glProgramStringARB
	_glProgramStringARB = NULL;
#	endif
#	ifdef glBindProgramARB
	_glBindProgramARB = NULL;
#	endif
#	ifdef glDeleteProgramsARB
	_glDeleteProgramsARB = NULL;
#	endif
#	ifdef glGenProgramsARB
	_glGenProgramsARB = NULL;
#	endif
#	ifdef glProgramEnvParameter4dARB
	_glProgramEnvParameter4dARB = NULL;
#	endif
#	ifdef glProgramEnvParameter4dvARB
	_glProgramEnvParameter4dvARB = NULL;
#	endif
#	ifdef glProgramEnvParameter4fARB
	_glProgramEnvParameter4fARB = NULL;
#	endif
#	ifdef glProgramEnvParameter4fvARB
	_glProgramEnvParameter4fvARB = NULL;
#	endif
#	ifdef glProgramLocalParameter4dARB
	_glProgramLocalParameter4dARB = NULL;
#	endif
#	ifdef glProgramLocalParameter4dvARB
	_glProgramLocalParameter4dvARB = NULL;
#	endif
#	ifdef glProgramLocalParameter4fARB
	_glProgramLocalParameter4fARB = NULL;
#	endif
#	ifdef glProgramLocalParameter4fvARB
	_glProgramLocalParameter4fvARB = NULL;
#	endif
#	ifdef glGetProgramEnvParameterdvARB
	_glGetProgramEnvParameterdvARB = NULL;
#	endif
#	ifdef glGetProgramEnvParameterfvARB
	_glGetProgramEnvParameterfvARB = NULL;
#	endif
#	ifdef glGetProgramLocalParameterdvARB
	_glGetProgramLocalParameterdvARB = NULL;
#	endif
#	ifdef glGetProgramLocalParameterfvARB
	_glGetProgramLocalParameterfvARB = NULL;
#	endif
#	ifdef glGetProgramivARB
	_glGetProgramivARB = NULL;
#	endif
#	ifdef glGetProgramStringARB
	_glGetProgramStringARB = NULL;
#	endif
#	ifdef glGetVertexAttribdvARB
	_glGetVertexAttribdvARB = NULL;
#	endif
#	ifdef glGetVertexAttribfvARB
	_glGetVertexAttribfvARB = NULL;
#	endif
#	ifdef glGetVertexAttribivARB
	_glGetVertexAttribivARB = NULL;
#	endif
#	ifdef glGetVertexAttribPointervARB
	_glGetVertexAttribPointervARB = NULL;
#	endif
#	ifdef glIsProgramARB
	_glIsProgramARB = NULL;
#	endif
#	ifdef glBindBufferARB
	_glBindBufferARB = NULL;
#	endif
#	ifdef glDeleteBuffersARB
	_glDeleteBuffersARB = NULL;
#	endif
#	ifdef glGenBuffersARB
	_glGenBuffersARB = NULL;
#	endif
#	ifdef glIsBufferARB
	_glIsBufferARB = NULL;
#	endif
#	ifdef glBufferDataARB
	_glBufferDataARB = NULL;
#	endif
#	ifdef glBufferSubDataARB
	_glBufferSubDataARB = NULL;
#	endif
#	ifdef glGetBufferSubDataARB
	_glGetBufferSubDataARB = NULL;
#	endif
#	ifdef glMapBufferARB
	_glMapBufferARB = NULL;
#	endif
#	ifdef glUnmapBufferARB
	_glUnmapBufferARB = NULL;
#	endif
#	ifdef glGetBufferParameterivARB
	_glGetBufferParameterivARB = NULL;
#	endif
#	ifdef glGetBufferPointervARB
	_glGetBufferPointervARB = NULL;
#	endif
#	ifdef glGenQueriesARB
	_glGenQueriesARB = NULL;
#	endif
#	ifdef glDeleteQueriesARB
	_glDeleteQueriesARB = NULL;
#	endif
#	ifdef glIsQueryARB
	_glIsQueryARB = NULL;
#	endif
#	ifdef glBeginQueryARB
	_glBeginQueryARB = NULL;
#	endif
#	ifdef glEndQueryARB
	_glEndQueryARB = NULL;
#	endif
#	ifdef glGetQueryivARB
	_glGetQueryivARB = NULL;
#	endif
#	ifdef glGetQueryObjectivARB
	_glGetQueryObjectivARB = NULL;
#	endif
#	ifdef glGetQueryObjectuivARB
	_glGetQueryObjectuivARB = NULL;
#	endif
#	ifdef glDeleteObjectARB
	_glDeleteObjectARB = NULL;
#	endif
#	ifdef glGetHandleARB
	_glGetHandleARB = NULL;
#	endif
#	ifdef glDetachObjectARB
	_glDetachObjectARB = NULL;
#	endif
#	ifdef glCreateShaderObjectARB
	_glCreateShaderObjectARB = NULL;
#	endif
#	ifdef glShaderSourceARB
	_glShaderSourceARB = NULL;
#	endif
#	ifdef glCompileShaderARB
	_glCompileShaderARB = NULL;
#	endif
#	ifdef glCreateProgramObjectARB
	_glCreateProgramObjectARB = NULL;
#	endif
#	ifdef glAttachObjectARB
	_glAttachObjectARB = NULL;
#	endif
#	ifdef glLinkProgramARB
	_glLinkProgramARB = NULL;
#	endif
#	ifdef glUseProgramObjectARB
	_glUseProgramObjectARB = NULL;
#	endif
#	ifdef glValidateProgramARB
	_glValidateProgramARB = NULL;
#	endif
#	ifdef glUniform1fARB
	_glUniform1fARB = NULL;
#	endif
#	ifdef glUniform2fARB
	_glUniform2fARB = NULL;
#	endif
#	ifdef glUniform3fARB
	_glUniform3fARB = NULL;
#	endif
#	ifdef glUniform4fARB
	_glUniform4fARB = NULL;
#	endif
#	ifdef glUniform1iARB
	_glUniform1iARB = NULL;
#	endif
#	ifdef glUniform2iARB
	_glUniform2iARB = NULL;
#	endif
#	ifdef glUniform3iARB
	_glUniform3iARB = NULL;
#	endif
#	ifdef glUniform4iARB
	_glUniform4iARB = NULL;
#	endif
#	ifdef glUniform1fvARB
	_glUniform1fvARB = NULL;
#	endif
#	ifdef glUniform2fvARB
	_glUniform2fvARB = NULL;
#	endif
#	ifdef glUniform3fvARB
	_glUniform3fvARB = NULL;
#	endif
#	ifdef glUniform4fvARB
	_glUniform4fvARB = NULL;
#	endif
#	ifdef glUniform1ivARB
	_glUniform1ivARB = NULL;
#	endif
#	ifdef glUniform2ivARB
	_glUniform2ivARB = NULL;
#	endif
#	ifdef glUniform3ivARB
	_glUniform3ivARB = NULL;
#	endif
#	ifdef glUniform4ivARB
	_glUniform4ivARB = NULL;
#	endif
#	ifdef glUniformMatrix2fvARB
	_glUniformMatrix2fvARB = NULL;
#	endif
#	ifdef glUniformMatrix3fvARB
	_glUniformMatrix3fvARB = NULL;
#	endif
#	ifdef glUniformMatrix4fvARB
	_glUniformMatrix4fvARB = NULL;
#	endif
#	ifdef glGetObjectParameterfvARB
	_glGetObjectParameterfvARB = NULL;
#	endif
#	ifdef glGetObjectParameterivARB
	_glGetObjectParameterivARB = NULL;
#	endif
#	ifdef glGetInfoLogARB
	_glGetInfoLogARB = NULL;
#	endif
#	ifdef glGetAttachedObjectsARB
	_glGetAttachedObjectsARB = NULL;
#	endif
#	ifdef glGetUniformLocationARB
	_glGetUniformLocationARB = NULL;
#	endif
#	ifdef glGetActiveUniformARB
	_glGetActiveUniformARB = NULL;
#	endif
#	ifdef glGetUniformfvARB
	_glGetUniformfvARB = NULL;
#	endif
#	ifdef glGetUniformivARB
	_glGetUniformivARB = NULL;
#	endif
#	ifdef glGetShaderSourceARB
	_glGetShaderSourceARB = NULL;
#	endif
#	ifdef glBindAttribLocationARB
	_glBindAttribLocationARB = NULL;
#	endif
#	ifdef glGetActiveAttribARB
	_glGetActiveAttribARB = NULL;
#	endif
#	ifdef glGetAttribLocationARB
	_glGetAttribLocationARB = NULL;
#	endif
#	ifdef glDrawBuffersARB
	_glDrawBuffersARB = NULL;
#	endif
#	ifdef glClampColorARB
	_glClampColorARB = NULL;
#	endif
#	ifdef glDrawArraysInstancedARB
	_glDrawArraysInstancedARB = NULL;
#	endif
#	ifdef glDrawElementsInstancedARB
	_glDrawElementsInstancedARB = NULL;
#	endif
#	ifdef glIsRenderbuffer
	_glIsRenderbuffer = NULL;
#	endif
#	ifdef glBindRenderbuffer
	_glBindRenderbuffer = NULL;
#	endif
#	ifdef glDeleteRenderbuffers
	_glDeleteRenderbuffers = NULL;
#	endif
#	ifdef glGenRenderbuffers
	_glGenRenderbuffers = NULL;
#	endif
#	ifdef glRenderbufferStorage
	_glRenderbufferStorage = NULL;
#	endif
#	ifdef glGetRenderbufferParameteriv
	_glGetRenderbufferParameteriv = NULL;
#	endif
#	ifdef glIsFramebuffer
	_glIsFramebuffer = NULL;
#	endif
#	ifdef glBindFramebuffer
	_glBindFramebuffer = NULL;
#	endif
#	ifdef glDeleteFramebuffers
	_glDeleteFramebuffers = NULL;
#	endif
#	ifdef glGenFramebuffers
	_glGenFramebuffers = NULL;
#	endif
#	ifdef glCheckFramebufferStatus
	_glCheckFramebufferStatus = NULL;
#	endif
#	ifdef glFramebufferTexture1D
	_glFramebufferTexture1D = NULL;
#	endif
#	ifdef glFramebufferTexture2D
	_glFramebufferTexture2D = NULL;
#	endif
#	ifdef glFramebufferTexture3D
	_glFramebufferTexture3D = NULL;
#	endif
#	ifdef glFramebufferRenderbuffer
	_glFramebufferRenderbuffer = NULL;
#	endif
#	ifdef glGetFramebufferAttachmentParameteriv
	_glGetFramebufferAttachmentParameteriv = NULL;
#	endif
#	ifdef glGenerateMipmap
	_glGenerateMipmap = NULL;
#	endif
#	ifdef glBlitFramebuffer
	_glBlitFramebuffer = NULL;
#	endif
#	ifdef glRenderbufferStorageMultisample
	_glRenderbufferStorageMultisample = NULL;
#	endif
#	ifdef glFramebufferTextureLayer
	_glFramebufferTextureLayer = NULL;
#	endif
#	ifdef glProgramParameteriARB
	_glProgramParameteriARB = NULL;
#	endif
#	ifdef glFramebufferTextureARB
	_glFramebufferTextureARB = NULL;
#	endif
#	ifdef glFramebufferTextureLayerARB
	_glFramebufferTextureLayerARB = NULL;
#	endif
#	ifdef glFramebufferTextureFaceARB
	_glFramebufferTextureFaceARB = NULL;
#	endif
#	ifdef glVertexAttribDivisorARB
	_glVertexAttribDivisorARB = NULL;
#	endif
#	ifdef glMapBufferRange
	_glMapBufferRange = NULL;
#	endif
#	ifdef glFlushMappedBufferRange
	_glFlushMappedBufferRange = NULL;
#	endif
#	ifdef glTexBufferARB
	_glTexBufferARB = NULL;
#	endif
#	ifdef glBindVertexArray
	_glBindVertexArray = NULL;
#	endif
#	ifdef glDeleteVertexArrays
	_glDeleteVertexArrays = NULL;
#	endif
#	ifdef glGenVertexArrays
	_glGenVertexArrays = NULL;
#	endif
#	ifdef glIsVertexArray
	_glIsVertexArray = NULL;
#	endif
#	ifdef glGetUniformIndices
	_glGetUniformIndices = NULL;
#	endif
#	ifdef glGetActiveUniformsiv
	_glGetActiveUniformsiv = NULL;
#	endif
#	ifdef glGetActiveUniformName
	_glGetActiveUniformName = NULL;
#	endif
#	ifdef glGetUniformBlockIndex
	_glGetUniformBlockIndex = NULL;
#	endif
#	ifdef glGetActiveUniformBlockiv
	_glGetActiveUniformBlockiv = NULL;
#	endif
#	ifdef glGetActiveUniformBlockName
	_glGetActiveUniformBlockName = NULL;
#	endif
#	ifdef glUniformBlockBinding
	_glUniformBlockBinding = NULL;
#	endif
#	ifdef glCopyBufferSubData
	_glCopyBufferSubData = NULL;
#	endif
#	ifdef glDrawElementsBaseVertex
	_glDrawElementsBaseVertex = NULL;
#	endif
#	ifdef glDrawRangeElementsBaseVertex
	_glDrawRangeElementsBaseVertex = NULL;
#	endif
#	ifdef glDrawElementsInstancedBaseVertex
	_glDrawElementsInstancedBaseVertex = NULL;
#	endif
#	ifdef glMultiDrawElementsBaseVertex
	_glMultiDrawElementsBaseVertex = NULL;
#	endif
#	ifdef glProvokingVertex
	_glProvokingVertex = NULL;
#	endif
#	ifdef glFenceSync
	_glFenceSync = NULL;
#	endif
#	ifdef glIsSync
	_glIsSync = NULL;
#	endif
#	ifdef glDeleteSync
	_glDeleteSync = NULL;
#	endif
#	ifdef glClientWaitSync
	_glClientWaitSync = NULL;
#	endif
#	ifdef glWaitSync
	_glWaitSync = NULL;
#	endif
#	ifdef glGetInteger64v
	_glGetInteger64v = NULL;
#	endif
#	ifdef glGetSynciv
	_glGetSynciv = NULL;
#	endif
#	ifdef glTexImage2DMultisample
	_glTexImage2DMultisample = NULL;
#	endif
#	ifdef glTexImage3DMultisample
	_glTexImage3DMultisample = NULL;
#	endif
#	ifdef glGetMultisamplefv
	_glGetMultisamplefv = NULL;
#	endif
#	ifdef glSampleMaski
	_glSampleMaski = NULL;
#	endif
#	ifdef glBlendEquationiARB
	_glBlendEquationiARB = NULL;
#	endif
#	ifdef glBlendEquationSeparateiARB
	_glBlendEquationSeparateiARB = NULL;
#	endif
#	ifdef glBlendFunciARB
	_glBlendFunciARB = NULL;
#	endif
#	ifdef glBlendFuncSeparateiARB
	_glBlendFuncSeparateiARB = NULL;
#	endif
#	ifdef glMinSampleShadingARB
	_glMinSampleShadingARB = NULL;
#	endif
#	ifdef glNamedStringARB
	_glNamedStringARB = NULL;
#	endif
#	ifdef glDeleteNamedStringARB
	_glDeleteNamedStringARB = NULL;
#	endif
#	ifdef glCompileShaderIncludeARB
	_glCompileShaderIncludeARB = NULL;
#	endif
#	ifdef glIsNamedStringARB
	_glIsNamedStringARB = NULL;
#	endif
#	ifdef glGetNamedStringARB
	_glGetNamedStringARB = NULL;
#	endif
#	ifdef glGetNamedStringivARB
	_glGetNamedStringivARB = NULL;
#	endif
#	ifdef glBindFragDataLocationIndexed
	_glBindFragDataLocationIndexed = NULL;
#	endif
#	ifdef glGetFragDataIndex
	_glGetFragDataIndex = NULL;
#	endif
#	ifdef glGenSamplers
	_glGenSamplers = NULL;
#	endif
#	ifdef glDeleteSamplers
	_glDeleteSamplers = NULL;
#	endif
#	ifdef glIsSampler
	_glIsSampler = NULL;
#	endif
#	ifdef glBindSampler
	_glBindSampler = NULL;
#	endif
#	ifdef glSamplerParameteri
	_glSamplerParameteri = NULL;
#	endif
#	ifdef glSamplerParameteriv
	_glSamplerParameteriv = NULL;
#	endif
#	ifdef glSamplerParameterf
	_glSamplerParameterf = NULL;
#	endif
#	ifdef glSamplerParameterfv
	_glSamplerParameterfv = NULL;
#	endif
#	ifdef glSamplerParameterIiv
	_glSamplerParameterIiv = NULL;
#	endif
#	ifdef glSamplerParameterIuiv
	_glSamplerParameterIuiv = NULL;
#	endif
#	ifdef glGetSamplerParameteriv
	_glGetSamplerParameteriv = NULL;
#	endif
#	ifdef glGetSamplerParameterIiv
	_glGetSamplerParameterIiv = NULL;
#	endif
#	ifdef glGetSamplerParameterfv
	_glGetSamplerParameterfv = NULL;
#	endif
#	ifdef glGetSamplerParameterIuiv
	_glGetSamplerParameterIuiv = NULL;
#	endif
#	ifdef glQueryCounter
	_glQueryCounter = NULL;
#	endif
#	ifdef glGetQueryObjecti64v
	_glGetQueryObjecti64v = NULL;
#	endif
#	ifdef glGetQueryObjectui64v
	_glGetQueryObjectui64v = NULL;
#	endif
#	ifdef glVertexP2ui
	_glVertexP2ui = NULL;
#	endif
#	ifdef glVertexP2uiv
	_glVertexP2uiv = NULL;
#	endif
#	ifdef glVertexP3ui
	_glVertexP3ui = NULL;
#	endif
#	ifdef glVertexP3uiv
	_glVertexP3uiv = NULL;
#	endif
#	ifdef glVertexP4ui
	_glVertexP4ui = NULL;
#	endif
#	ifdef glVertexP4uiv
	_glVertexP4uiv = NULL;
#	endif
#	ifdef glTexCoordP1ui
	_glTexCoordP1ui = NULL;
#	endif
#	ifdef glTexCoordP1uiv
	_glTexCoordP1uiv = NULL;
#	endif
#	ifdef glTexCoordP2ui
	_glTexCoordP2ui = NULL;
#	endif
#	ifdef glTexCoordP2uiv
	_glTexCoordP2uiv = NULL;
#	endif
#	ifdef glTexCoordP3ui
	_glTexCoordP3ui = NULL;
#	endif
#	ifdef glTexCoordP3uiv
	_glTexCoordP3uiv = NULL;
#	endif
#	ifdef glTexCoordP4ui
	_glTexCoordP4ui = NULL;
#	endif
#	ifdef glTexCoordP4uiv
	_glTexCoordP4uiv = NULL;
#	endif
#	ifdef glMultiTexCoordP1ui
	_glMultiTexCoordP1ui = NULL;
#	endif
#	ifdef glMultiTexCoordP1uiv
	_glMultiTexCoordP1uiv = NULL;
#	endif
#	ifdef glMultiTexCoordP2ui
	_glMultiTexCoordP2ui = NULL;
#	endif
#	ifdef glMultiTexCoordP2uiv
	_glMultiTexCoordP2uiv = NULL;
#	endif
#	ifdef glMultiTexCoordP3ui
	_glMultiTexCoordP3ui = NULL;
#	endif
#	ifdef glMultiTexCoordP3uiv
	_glMultiTexCoordP3uiv = NULL;
#	endif
#	ifdef glMultiTexCoordP4ui
	_glMultiTexCoordP4ui = NULL;
#	endif
#	ifdef glMultiTexCoordP4uiv
	_glMultiTexCoordP4uiv = NULL;
#	endif
#	ifdef glNormalP3ui
	_glNormalP3ui = NULL;
#	endif
#	ifdef glNormalP3uiv
	_glNormalP3uiv = NULL;
#	endif
#	ifdef glColorP3ui
	_glColorP3ui = NULL;
#	endif
#	ifdef glColorP3uiv
	_glColorP3uiv = NULL;
#	endif
#	ifdef glColorP4ui
	_glColorP4ui = NULL;
#	endif
#	ifdef glColorP4uiv
	_glColorP4uiv = NULL;
#	endif
#	ifdef glSecondaryColorP3ui
	_glSecondaryColorP3ui = NULL;
#	endif
#	ifdef glSecondaryColorP3uiv
	_glSecondaryColorP3uiv = NULL;
#	endif
#	ifdef glVertexAttribP1ui
	_glVertexAttribP1ui = NULL;
#	endif
#	ifdef glVertexAttribP1uiv
	_glVertexAttribP1uiv = NULL;
#	endif
#	ifdef glVertexAttribP2ui
	_glVertexAttribP2ui = NULL;
#	endif
#	ifdef glVertexAttribP2uiv
	_glVertexAttribP2uiv = NULL;
#	endif
#	ifdef glVertexAttribP3ui
	_glVertexAttribP3ui = NULL;
#	endif
#	ifdef glVertexAttribP3uiv
	_glVertexAttribP3uiv = NULL;
#	endif
#	ifdef glVertexAttribP4ui
	_glVertexAttribP4ui = NULL;
#	endif
#	ifdef glVertexAttribP4uiv
	_glVertexAttribP4uiv = NULL;
#	endif
#	ifdef glDrawArraysIndirect
	_glDrawArraysIndirect = NULL;
#	endif
#	ifdef glDrawElementsIndirect
	_glDrawElementsIndirect = NULL;
#	endif
#	ifdef glUniform1d
	_glUniform1d = NULL;
#	endif
#	ifdef glUniform2d
	_glUniform2d = NULL;
#	endif
#	ifdef glUniform3d
	_glUniform3d = NULL;
#	endif
#	ifdef glUniform4d
	_glUniform4d = NULL;
#	endif
#	ifdef glUniform1dv
	_glUniform1dv = NULL;
#	endif
#	ifdef glUniform2dv
	_glUniform2dv = NULL;
#	endif
#	ifdef glUniform3dv
	_glUniform3dv = NULL;
#	endif
#	ifdef glUniform4dv
	_glUniform4dv = NULL;
#	endif
#	ifdef glUniformMatrix2dv
	_glUniformMatrix2dv = NULL;
#	endif
#	ifdef glUniformMatrix3dv
	_glUniformMatrix3dv = NULL;
#	endif
#	ifdef glUniformMatrix4dv
	_glUniformMatrix4dv = NULL;
#	endif
#	ifdef glUniformMatrix2x3dv
	_glUniformMatrix2x3dv = NULL;
#	endif
#	ifdef glUniformMatrix2x4dv
	_glUniformMatrix2x4dv = NULL;
#	endif
#	ifdef glUniformMatrix3x2dv
	_glUniformMatrix3x2dv = NULL;
#	endif
#	ifdef glUniformMatrix3x4dv
	_glUniformMatrix3x4dv = NULL;
#	endif
#	ifdef glUniformMatrix4x2dv
	_glUniformMatrix4x2dv = NULL;
#	endif
#	ifdef glUniformMatrix4x3dv
	_glUniformMatrix4x3dv = NULL;
#	endif
#	ifdef glGetUniformdv
	_glGetUniformdv = NULL;
#	endif
#	ifdef glGetSubroutineUniformLocation
	_glGetSubroutineUniformLocation = NULL;
#	endif
#	ifdef glGetSubroutineIndex
	_glGetSubroutineIndex = NULL;
#	endif
#	ifdef glGetActiveSubroutineUniformiv
	_glGetActiveSubroutineUniformiv = NULL;
#	endif
#	ifdef glGetActiveSubroutineUniformName
	_glGetActiveSubroutineUniformName = NULL;
#	endif
#	ifdef glGetActiveSubroutineName
	_glGetActiveSubroutineName = NULL;
#	endif
#	ifdef glUniformSubroutinesuiv
	_glUniformSubroutinesuiv = NULL;
#	endif
#	ifdef glGetUniformSubroutineuiv
	_glGetUniformSubroutineuiv = NULL;
#	endif
#	ifdef glGetProgramStageiv
	_glGetProgramStageiv = NULL;
#	endif
#	ifdef glPatchParameteri
	_glPatchParameteri = NULL;
#	endif
#	ifdef glPatchParameterfv
	_glPatchParameterfv = NULL;
#	endif
#	ifdef glBindTransformFeedback
	_glBindTransformFeedback = NULL;
#	endif
#	ifdef glDeleteTransformFeedbacks
	_glDeleteTransformFeedbacks = NULL;
#	endif
#	ifdef glGenTransformFeedbacks
	_glGenTransformFeedbacks = NULL;
#	endif
#	ifdef glIsTransformFeedback
	_glIsTransformFeedback = NULL;
#	endif
#	ifdef glPauseTransformFeedback
	_glPauseTransformFeedback = NULL;
#	endif
#	ifdef glResumeTransformFeedback
	_glResumeTransformFeedback = NULL;
#	endif
#	ifdef glDrawTransformFeedback
	_glDrawTransformFeedback = NULL;
#	endif
#	ifdef glDrawTransformFeedbackStream
	_glDrawTransformFeedbackStream = NULL;
#	endif
#	ifdef glBeginQueryIndexed
	_glBeginQueryIndexed = NULL;
#	endif
#	ifdef glEndQueryIndexed
	_glEndQueryIndexed = NULL;
#	endif
#	ifdef glGetQueryIndexediv
	_glGetQueryIndexediv = NULL;
#	endif
#	ifdef glReleaseShaderCompiler
	_glReleaseShaderCompiler = NULL;
#	endif
#	ifdef glShaderBinary
	_glShaderBinary = NULL;
#	endif
#	ifdef glGetShaderPrecisionFormat
	_glGetShaderPrecisionFormat = NULL;
#	endif
#	ifdef glDepthRangef
	_glDepthRangef = NULL;
#	endif
#	ifdef glClearDepthf
	_glClearDepthf = NULL;
#	endif
#	ifdef glGetProgramBinary
	_glGetProgramBinary = NULL;
#	endif
#	ifdef glProgramBinary
	_glProgramBinary = NULL;
#	endif
#	ifdef glProgramParameteri
	_glProgramParameteri = NULL;
#	endif
#	ifdef glUseProgramStages
	_glUseProgramStages = NULL;
#	endif
#	ifdef glActiveShaderProgram
	_glActiveShaderProgram = NULL;
#	endif
#	ifdef glCreateShaderProgramv
	_glCreateShaderProgramv = NULL;
#	endif
#	ifdef glBindProgramPipeline
	_glBindProgramPipeline = NULL;
#	endif
#	ifdef glDeleteProgramPipelines
	_glDeleteProgramPipelines = NULL;
#	endif
#	ifdef glGenProgramPipelines
	_glGenProgramPipelines = NULL;
#	endif
#	ifdef glIsProgramPipeline
	_glIsProgramPipeline = NULL;
#	endif
#	ifdef glGetProgramPipelineiv
	_glGetProgramPipelineiv = NULL;
#	endif
#	ifdef glProgramUniform1i
	_glProgramUniform1i = NULL;
#	endif
#	ifdef glProgramUniform1iv
	_glProgramUniform1iv = NULL;
#	endif
#	ifdef glProgramUniform1f
	_glProgramUniform1f = NULL;
#	endif
#	ifdef glProgramUniform1fv
	_glProgramUniform1fv = NULL;
#	endif
#	ifdef glProgramUniform1d
	_glProgramUniform1d = NULL;
#	endif
#	ifdef glProgramUniform1dv
	_glProgramUniform1dv = NULL;
#	endif
#	ifdef glProgramUniform1ui
	_glProgramUniform1ui = NULL;
#	endif
#	ifdef glProgramUniform1uiv
	_glProgramUniform1uiv = NULL;
#	endif
#	ifdef glProgramUniform2i
	_glProgramUniform2i = NULL;
#	endif
#	ifdef glProgramUniform2iv
	_glProgramUniform2iv = NULL;
#	endif
#	ifdef glProgramUniform2f
	_glProgramUniform2f = NULL;
#	endif
#	ifdef glProgramUniform2fv
	_glProgramUniform2fv = NULL;
#	endif
#	ifdef glProgramUniform2d
	_glProgramUniform2d = NULL;
#	endif
#	ifdef glProgramUniform2dv
	_glProgramUniform2dv = NULL;
#	endif
#	ifdef glProgramUniform2ui
	_glProgramUniform2ui = NULL;
#	endif
#	ifdef glProgramUniform2uiv
	_glProgramUniform2uiv = NULL;
#	endif
#	ifdef glProgramUniform3i
	_glProgramUniform3i = NULL;
#	endif
#	ifdef glProgramUniform3iv
	_glProgramUniform3iv = NULL;
#	endif
#	ifdef glProgramUniform3f
	_glProgramUniform3f = NULL;
#	endif
#	ifdef glProgramUniform3fv
	_glProgramUniform3fv = NULL;
#	endif
#	ifdef glProgramUniform3d
	_glProgramUniform3d = NULL;
#	endif
#	ifdef glProgramUniform3dv
	_glProgramUniform3dv = NULL;
#	endif
#	ifdef glProgramUniform3ui
	_glProgramUniform3ui = NULL;
#	endif
#	ifdef glProgramUniform3uiv
	_glProgramUniform3uiv = NULL;
#	endif
#	ifdef glProgramUniform4i
	_glProgramUniform4i = NULL;
#	endif
#	ifdef glProgramUniform4iv
	_glProgramUniform4iv = NULL;
#	endif
#	ifdef glProgramUniform4f
	_glProgramUniform4f = NULL;
#	endif
#	ifdef glProgramUniform4fv
	_glProgramUniform4fv = NULL;
#	endif
#	ifdef glProgramUniform4d
	_glProgramUniform4d = NULL;
#	endif
#	ifdef glProgramUniform4dv
	_glProgramUniform4dv = NULL;
#	endif
#	ifdef glProgramUniform4ui
	_glProgramUniform4ui = NULL;
#	endif
#	ifdef glProgramUniform4uiv
	_glProgramUniform4uiv = NULL;
#	endif
#	ifdef glProgramUniformMatrix2fv
	_glProgramUniformMatrix2fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix3fv
	_glProgramUniformMatrix3fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix4fv
	_glProgramUniformMatrix4fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix2dv
	_glProgramUniformMatrix2dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix3dv
	_glProgramUniformMatrix3dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix4dv
	_glProgramUniformMatrix4dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x3fv
	_glProgramUniformMatrix2x3fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x2fv
	_glProgramUniformMatrix3x2fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x4fv
	_glProgramUniformMatrix2x4fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x2fv
	_glProgramUniformMatrix4x2fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x4fv
	_glProgramUniformMatrix3x4fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x3fv
	_glProgramUniformMatrix4x3fv = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x3dv
	_glProgramUniformMatrix2x3dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x2dv
	_glProgramUniformMatrix3x2dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x4dv
	_glProgramUniformMatrix2x4dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x2dv
	_glProgramUniformMatrix4x2dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x4dv
	_glProgramUniformMatrix3x4dv = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x3dv
	_glProgramUniformMatrix4x3dv = NULL;
#	endif
#	ifdef glValidateProgramPipeline
	_glValidateProgramPipeline = NULL;
#	endif
#	ifdef glGetProgramPipelineInfoLog
	_glGetProgramPipelineInfoLog = NULL;
#	endif
#	ifdef glVertexAttribL1d
	_glVertexAttribL1d = NULL;
#	endif
#	ifdef glVertexAttribL2d
	_glVertexAttribL2d = NULL;
#	endif
#	ifdef glVertexAttribL3d
	_glVertexAttribL3d = NULL;
#	endif
#	ifdef glVertexAttribL4d
	_glVertexAttribL4d = NULL;
#	endif
#	ifdef glVertexAttribL1dv
	_glVertexAttribL1dv = NULL;
#	endif
#	ifdef glVertexAttribL2dv
	_glVertexAttribL2dv = NULL;
#	endif
#	ifdef glVertexAttribL3dv
	_glVertexAttribL3dv = NULL;
#	endif
#	ifdef glVertexAttribL4dv
	_glVertexAttribL4dv = NULL;
#	endif
#	ifdef glVertexAttribLPointer
	_glVertexAttribLPointer = NULL;
#	endif
#	ifdef glGetVertexAttribLdv
	_glGetVertexAttribLdv = NULL;
#	endif
#	ifdef glViewportArrayv
	_glViewportArrayv = NULL;
#	endif
#	ifdef glViewportIndexedf
	_glViewportIndexedf = NULL;
#	endif
#	ifdef glViewportIndexedfv
	_glViewportIndexedfv = NULL;
#	endif
#	ifdef glScissorArrayv
	_glScissorArrayv = NULL;
#	endif
#	ifdef glScissorIndexed
	_glScissorIndexed = NULL;
#	endif
#	ifdef glScissorIndexedv
	_glScissorIndexedv = NULL;
#	endif
#	ifdef glDepthRangeArrayv
	_glDepthRangeArrayv = NULL;
#	endif
#	ifdef glDepthRangeIndexed
	_glDepthRangeIndexed = NULL;
#	endif
#	ifdef glGetFloati_v
	_glGetFloati_v = NULL;
#	endif
#	ifdef glGetDoublei_v
	_glGetDoublei_v = NULL;
#	endif
#	ifdef glCreateSyncFromCLeventARB
	_glCreateSyncFromCLeventARB = NULL;
#	endif
#	ifdef glDebugMessageControlARB
	_glDebugMessageControlARB = NULL;
#	endif
#	ifdef glDebugMessageInsertARB
	_glDebugMessageInsertARB = NULL;
#	endif
#	ifdef glDebugMessageCallbackARB
	_glDebugMessageCallbackARB = NULL;
#	endif
#	ifdef glGetDebugMessageLogARB
	_glGetDebugMessageLogARB = NULL;
#	endif
#	ifdef glGetGraphicsResetStatusARB
	_glGetGraphicsResetStatusARB = NULL;
#	endif
#	ifdef glGetnMapdvARB
	_glGetnMapdvARB = NULL;
#	endif
#	ifdef glGetnMapfvARB
	_glGetnMapfvARB = NULL;
#	endif
#	ifdef glGetnMapivARB
	_glGetnMapivARB = NULL;
#	endif
#	ifdef glGetnPixelMapfvARB
	_glGetnPixelMapfvARB = NULL;
#	endif
#	ifdef glGetnPixelMapuivARB
	_glGetnPixelMapuivARB = NULL;
#	endif
#	ifdef glGetnPixelMapusvARB
	_glGetnPixelMapusvARB = NULL;
#	endif
#	ifdef glGetnPolygonStippleARB
	_glGetnPolygonStippleARB = NULL;
#	endif
#	ifdef glGetnColorTableARB
	_glGetnColorTableARB = NULL;
#	endif
#	ifdef glGetnConvolutionFilterARB
	_glGetnConvolutionFilterARB = NULL;
#	endif
#	ifdef glGetnSeparableFilterARB
	_glGetnSeparableFilterARB = NULL;
#	endif
#	ifdef glGetnHistogramARB
	_glGetnHistogramARB = NULL;
#	endif
#	ifdef glGetnMinmaxARB
	_glGetnMinmaxARB = NULL;
#	endif
#	ifdef glGetnTexImageARB
	_glGetnTexImageARB = NULL;
#	endif
#	ifdef glReadnPixelsARB
	_glReadnPixelsARB = NULL;
#	endif
#	ifdef glGetnCompressedTexImageARB
	_glGetnCompressedTexImageARB = NULL;
#	endif
#	ifdef glGetnUniformfvARB
	_glGetnUniformfvARB = NULL;
#	endif
#	ifdef glGetnUniformivARB
	_glGetnUniformivARB = NULL;
#	endif
#	ifdef glGetnUniformuivARB
	_glGetnUniformuivARB = NULL;
#	endif
#	ifdef glGetnUniformdvARB
	_glGetnUniformdvARB = NULL;
#	endif
#	ifdef glDrawArraysInstancedBaseInstance
	_glDrawArraysInstancedBaseInstance = NULL;
#	endif
#	ifdef glDrawElementsInstancedBaseInstance
	_glDrawElementsInstancedBaseInstance = NULL;
#	endif
#	ifdef glDrawElementsInstancedBaseVertexBaseInstance
	_glDrawElementsInstancedBaseVertexBaseInstance = NULL;
#	endif
#	ifdef glDrawTransformFeedbackInstanced
	_glDrawTransformFeedbackInstanced = NULL;
#	endif
#	ifdef glDrawTransformFeedbackStreamInstanced
	_glDrawTransformFeedbackStreamInstanced = NULL;
#	endif
#	ifdef glGetInternalformativ
	_glGetInternalformativ = NULL;
#	endif
#	ifdef glGetActiveAtomicCounterBufferiv
	_glGetActiveAtomicCounterBufferiv = NULL;
#	endif
#	ifdef glBindImageTexture
	_glBindImageTexture = NULL;
#	endif
#	ifdef glMemoryBarrier
	_glMemoryBarrier = NULL;
#	endif
#	ifdef glTexStorage1D
	_glTexStorage1D = NULL;
#	endif
#	ifdef glTexStorage2D
	_glTexStorage2D = NULL;
#	endif
#	ifdef glTexStorage3D
	_glTexStorage3D = NULL;
#	endif
#	ifdef glTextureStorage1DEXT
	_glTextureStorage1DEXT = NULL;
#	endif
#	ifdef glTextureStorage2DEXT
	_glTextureStorage2DEXT = NULL;
#	endif
#	ifdef glTextureStorage3DEXT
	_glTextureStorage3DEXT = NULL;
#	endif
#	ifdef glDebugMessageControl
	_glDebugMessageControl = NULL;
#	endif
#	ifdef glDebugMessageInsert
	_glDebugMessageInsert = NULL;
#	endif
#	ifdef glDebugMessageCallback
	_glDebugMessageCallback = NULL;
#	endif
#	ifdef glGetDebugMessageLog
	_glGetDebugMessageLog = NULL;
#	endif
#	ifdef glPushDebugGroup
	_glPushDebugGroup = NULL;
#	endif
#	ifdef glPopDebugGroup
	_glPopDebugGroup = NULL;
#	endif
#	ifdef glObjectLabel
	_glObjectLabel = NULL;
#	endif
#	ifdef glGetObjectLabel
	_glGetObjectLabel = NULL;
#	endif
#	ifdef glObjectPtrLabel
	_glObjectPtrLabel = NULL;
#	endif
#	ifdef glGetObjectPtrLabel
	_glGetObjectPtrLabel = NULL;
#	endif
#	ifdef glClearBufferData
	_glClearBufferData = NULL;
#	endif
#	ifdef glClearBufferSubData
	_glClearBufferSubData = NULL;
#	endif
#	ifdef glClearNamedBufferDataEXT
	_glClearNamedBufferDataEXT = NULL;
#	endif
#	ifdef glClearNamedBufferSubDataEXT
	_glClearNamedBufferSubDataEXT = NULL;
#	endif
#	ifdef glDispatchCompute
	_glDispatchCompute = NULL;
#	endif
#	ifdef glDispatchComputeIndirect
	_glDispatchComputeIndirect = NULL;
#	endif
#	ifdef glCopyImageSubData
	_glCopyImageSubData = NULL;
#	endif
#	ifdef glTextureView
	_glTextureView = NULL;
#	endif
#	ifdef glBindVertexBuffer
	_glBindVertexBuffer = NULL;
#	endif
#	ifdef glVertexAttribFormat
	_glVertexAttribFormat = NULL;
#	endif
#	ifdef glVertexAttribIFormat
	_glVertexAttribIFormat = NULL;
#	endif
#	ifdef glVertexAttribLFormat
	_glVertexAttribLFormat = NULL;
#	endif
#	ifdef glVertexAttribBinding
	_glVertexAttribBinding = NULL;
#	endif
#	ifdef glVertexBindingDivisor
	_glVertexBindingDivisor = NULL;
#	endif
#	ifdef glVertexArrayBindVertexBufferEXT
	_glVertexArrayBindVertexBufferEXT = NULL;
#	endif
#	ifdef glVertexArrayVertexAttribFormatEXT
	_glVertexArrayVertexAttribFormatEXT = NULL;
#	endif
#	ifdef glVertexArrayVertexAttribIFormatEXT
	_glVertexArrayVertexAttribIFormatEXT = NULL;
#	endif
#	ifdef glVertexArrayVertexAttribLFormatEXT
	_glVertexArrayVertexAttribLFormatEXT = NULL;
#	endif
#	ifdef glVertexArrayVertexAttribBindingEXT
	_glVertexArrayVertexAttribBindingEXT = NULL;
#	endif
#	ifdef glVertexArrayVertexBindingDivisorEXT
	_glVertexArrayVertexBindingDivisorEXT = NULL;
#	endif
#	ifdef glFramebufferParameteri
	_glFramebufferParameteri = NULL;
#	endif
#	ifdef glGetFramebufferParameteriv
	_glGetFramebufferParameteriv = NULL;
#	endif
#	ifdef glNamedFramebufferParameteriEXT
	_glNamedFramebufferParameteriEXT = NULL;
#	endif
#	ifdef glGetNamedFramebufferParameterivEXT
	_glGetNamedFramebufferParameterivEXT = NULL;
#	endif
#	ifdef glGetInternalformati64v
	_glGetInternalformati64v = NULL;
#	endif
#	ifdef glInvalidateTexSubImage
	_glInvalidateTexSubImage = NULL;
#	endif
#	ifdef glInvalidateTexImage
	_glInvalidateTexImage = NULL;
#	endif
#	ifdef glInvalidateBufferSubData
	_glInvalidateBufferSubData = NULL;
#	endif
#	ifdef glInvalidateBufferData
	_glInvalidateBufferData = NULL;
#	endif
#	ifdef glInvalidateFramebuffer
	_glInvalidateFramebuffer = NULL;
#	endif
#	ifdef glInvalidateSubFramebuffer
	_glInvalidateSubFramebuffer = NULL;
#	endif
#	ifdef glMultiDrawArraysIndirect
	_glMultiDrawArraysIndirect = NULL;
#	endif
#	ifdef glMultiDrawElementsIndirect
	_glMultiDrawElementsIndirect = NULL;
#	endif
#	ifdef glGetProgramInterfaceiv
	_glGetProgramInterfaceiv = NULL;
#	endif
#	ifdef glGetProgramResourceIndex
	_glGetProgramResourceIndex = NULL;
#	endif
#	ifdef glGetProgramResourceName
	_glGetProgramResourceName = NULL;
#	endif
#	ifdef glGetProgramResourceiv
	_glGetProgramResourceiv = NULL;
#	endif
#	ifdef glGetProgramResourceLocation
	_glGetProgramResourceLocation = NULL;
#	endif
#	ifdef glGetProgramResourceLocationIndex
	_glGetProgramResourceLocationIndex = NULL;
#	endif
#	ifdef glShaderStorageBlockBinding
	_glShaderStorageBlockBinding = NULL;
#	endif
#	ifdef glTexBufferRange
	_glTexBufferRange = NULL;
#	endif
#	ifdef glTextureBufferRangeEXT
	_glTextureBufferRangeEXT = NULL;
#	endif
#	ifdef glTexStorage2DMultisample
	_glTexStorage2DMultisample = NULL;
#	endif
#	ifdef glTexStorage3DMultisample
	_glTexStorage3DMultisample = NULL;
#	endif
#	ifdef glTextureStorage2DMultisampleEXT
	_glTextureStorage2DMultisampleEXT = NULL;
#	endif
#	ifdef glTextureStorage3DMultisampleEXT
	_glTextureStorage3DMultisampleEXT = NULL;
#	endif
#	ifdef glBlendColorEXT
	_glBlendColorEXT = NULL;
#	endif
#	ifdef glPolygonOffsetEXT
	_glPolygonOffsetEXT = NULL;
#	endif
#	ifdef glTexImage3DEXT
	_glTexImage3DEXT = NULL;
#	endif
#	ifdef glTexSubImage3DEXT
	_glTexSubImage3DEXT = NULL;
#	endif
#	ifdef glGetTexFilterFuncSGIS
	_glGetTexFilterFuncSGIS = NULL;
#	endif
#	ifdef glTexFilterFuncSGIS
	_glTexFilterFuncSGIS = NULL;
#	endif
#	ifdef glTexSubImage1DEXT
	_glTexSubImage1DEXT = NULL;
#	endif
#	ifdef glTexSubImage2DEXT
	_glTexSubImage2DEXT = NULL;
#	endif
#	ifdef glCopyTexImage1DEXT
	_glCopyTexImage1DEXT = NULL;
#	endif
#	ifdef glCopyTexImage2DEXT
	_glCopyTexImage2DEXT = NULL;
#	endif
#	ifdef glCopyTexSubImage1DEXT
	_glCopyTexSubImage1DEXT = NULL;
#	endif
#	ifdef glCopyTexSubImage2DEXT
	_glCopyTexSubImage2DEXT = NULL;
#	endif
#	ifdef glCopyTexSubImage3DEXT
	_glCopyTexSubImage3DEXT = NULL;
#	endif
#	ifdef glGetHistogramEXT
	_glGetHistogramEXT = NULL;
#	endif
#	ifdef glGetHistogramParameterfvEXT
	_glGetHistogramParameterfvEXT = NULL;
#	endif
#	ifdef glGetHistogramParameterivEXT
	_glGetHistogramParameterivEXT = NULL;
#	endif
#	ifdef glGetMinmaxEXT
	_glGetMinmaxEXT = NULL;
#	endif
#	ifdef glGetMinmaxParameterfvEXT
	_glGetMinmaxParameterfvEXT = NULL;
#	endif
#	ifdef glGetMinmaxParameterivEXT
	_glGetMinmaxParameterivEXT = NULL;
#	endif
#	ifdef glHistogramEXT
	_glHistogramEXT = NULL;
#	endif
#	ifdef glMinmaxEXT
	_glMinmaxEXT = NULL;
#	endif
#	ifdef glResetHistogramEXT
	_glResetHistogramEXT = NULL;
#	endif
#	ifdef glResetMinmaxEXT
	_glResetMinmaxEXT = NULL;
#	endif
#	ifdef glConvolutionFilter1DEXT
	_glConvolutionFilter1DEXT = NULL;
#	endif
#	ifdef glConvolutionFilter2DEXT
	_glConvolutionFilter2DEXT = NULL;
#	endif
#	ifdef glConvolutionParameterfEXT
	_glConvolutionParameterfEXT = NULL;
#	endif
#	ifdef glConvolutionParameterfvEXT
	_glConvolutionParameterfvEXT = NULL;
#	endif
#	ifdef glConvolutionParameteriEXT
	_glConvolutionParameteriEXT = NULL;
#	endif
#	ifdef glConvolutionParameterivEXT
	_glConvolutionParameterivEXT = NULL;
#	endif
#	ifdef glCopyConvolutionFilter1DEXT
	_glCopyConvolutionFilter1DEXT = NULL;
#	endif
#	ifdef glCopyConvolutionFilter2DEXT
	_glCopyConvolutionFilter2DEXT = NULL;
#	endif
#	ifdef glGetConvolutionFilterEXT
	_glGetConvolutionFilterEXT = NULL;
#	endif
#	ifdef glGetConvolutionParameterfvEXT
	_glGetConvolutionParameterfvEXT = NULL;
#	endif
#	ifdef glGetConvolutionParameterivEXT
	_glGetConvolutionParameterivEXT = NULL;
#	endif
#	ifdef glGetSeparableFilterEXT
	_glGetSeparableFilterEXT = NULL;
#	endif
#	ifdef glSeparableFilter2DEXT
	_glSeparableFilter2DEXT = NULL;
#	endif
#	ifdef glColorTableSGI
	_glColorTableSGI = NULL;
#	endif
#	ifdef glColorTableParameterfvSGI
	_glColorTableParameterfvSGI = NULL;
#	endif
#	ifdef glColorTableParameterivSGI
	_glColorTableParameterivSGI = NULL;
#	endif
#	ifdef glCopyColorTableSGI
	_glCopyColorTableSGI = NULL;
#	endif
#	ifdef glGetColorTableSGI
	_glGetColorTableSGI = NULL;
#	endif
#	ifdef glGetColorTableParameterfvSGI
	_glGetColorTableParameterfvSGI = NULL;
#	endif
#	ifdef glGetColorTableParameterivSGI
	_glGetColorTableParameterivSGI = NULL;
#	endif
#	ifdef glPixelTexGenSGIX
	_glPixelTexGenSGIX = NULL;
#	endif
#	ifdef glPixelTexGenParameteriSGIS
	_glPixelTexGenParameteriSGIS = NULL;
#	endif
#	ifdef glPixelTexGenParameterivSGIS
	_glPixelTexGenParameterivSGIS = NULL;
#	endif
#	ifdef glPixelTexGenParameterfSGIS
	_glPixelTexGenParameterfSGIS = NULL;
#	endif
#	ifdef glPixelTexGenParameterfvSGIS
	_glPixelTexGenParameterfvSGIS = NULL;
#	endif
#	ifdef glGetPixelTexGenParameterivSGIS
	_glGetPixelTexGenParameterivSGIS = NULL;
#	endif
#	ifdef glGetPixelTexGenParameterfvSGIS
	_glGetPixelTexGenParameterfvSGIS = NULL;
#	endif
#	ifdef glTexImage4DSGIS
	_glTexImage4DSGIS = NULL;
#	endif
#	ifdef glTexSubImage4DSGIS
	_glTexSubImage4DSGIS = NULL;
#	endif
#	ifdef glAreTexturesResidentEXT
	_glAreTexturesResidentEXT = NULL;
#	endif
#	ifdef glBindTextureEXT
	_glBindTextureEXT = NULL;
#	endif
#	ifdef glDeleteTexturesEXT
	_glDeleteTexturesEXT = NULL;
#	endif
#	ifdef glGenTexturesEXT
	_glGenTexturesEXT = NULL;
#	endif
#	ifdef glIsTextureEXT
	_glIsTextureEXT = NULL;
#	endif
#	ifdef glPrioritizeTexturesEXT
	_glPrioritizeTexturesEXT = NULL;
#	endif
#	ifdef glDetailTexFuncSGIS
	_glDetailTexFuncSGIS = NULL;
#	endif
#	ifdef glGetDetailTexFuncSGIS
	_glGetDetailTexFuncSGIS = NULL;
#	endif
#	ifdef glSharpenTexFuncSGIS
	_glSharpenTexFuncSGIS = NULL;
#	endif
#	ifdef glGetSharpenTexFuncSGIS
	_glGetSharpenTexFuncSGIS = NULL;
#	endif
#	ifdef glSampleMaskSGIS
	_glSampleMaskSGIS = NULL;
#	endif
#	ifdef glSamplePatternSGIS
	_glSamplePatternSGIS = NULL;
#	endif
#	ifdef glArrayElementEXT
	_glArrayElementEXT = NULL;
#	endif
#	ifdef glColorPointerEXT
	_glColorPointerEXT = NULL;
#	endif
#	ifdef glDrawArraysEXT
	_glDrawArraysEXT = NULL;
#	endif
#	ifdef glEdgeFlagPointerEXT
	_glEdgeFlagPointerEXT = NULL;
#	endif
#	ifdef glGetPointervEXT
	_glGetPointervEXT = NULL;
#	endif
#	ifdef glIndexPointerEXT
	_glIndexPointerEXT = NULL;
#	endif
#	ifdef glNormalPointerEXT
	_glNormalPointerEXT = NULL;
#	endif
#	ifdef glTexCoordPointerEXT
	_glTexCoordPointerEXT = NULL;
#	endif
#	ifdef glVertexPointerEXT
	_glVertexPointerEXT = NULL;
#	endif
#	ifdef glBlendEquationEXT
	_glBlendEquationEXT = NULL;
#	endif
#	ifdef glSpriteParameterfSGIX
	_glSpriteParameterfSGIX = NULL;
#	endif
#	ifdef glSpriteParameterfvSGIX
	_glSpriteParameterfvSGIX = NULL;
#	endif
#	ifdef glSpriteParameteriSGIX
	_glSpriteParameteriSGIX = NULL;
#	endif
#	ifdef glSpriteParameterivSGIX
	_glSpriteParameterivSGIX = NULL;
#	endif
#	ifdef glPointParameterfEXT
	_glPointParameterfEXT = NULL;
#	endif
#	ifdef glPointParameterfvEXT
	_glPointParameterfvEXT = NULL;
#	endif
#	ifdef glPointParameterfSGIS
	_glPointParameterfSGIS = NULL;
#	endif
#	ifdef glPointParameterfvSGIS
	_glPointParameterfvSGIS = NULL;
#	endif
#	ifdef glGetInstrumentsSGIX
	_glGetInstrumentsSGIX = NULL;
#	endif
#	ifdef glInstrumentsBufferSGIX
	_glInstrumentsBufferSGIX = NULL;
#	endif
#	ifdef glPollInstrumentsSGIX
	_glPollInstrumentsSGIX = NULL;
#	endif
#	ifdef glReadInstrumentsSGIX
	_glReadInstrumentsSGIX = NULL;
#	endif
#	ifdef glStartInstrumentsSGIX
	_glStartInstrumentsSGIX = NULL;
#	endif
#	ifdef glStopInstrumentsSGIX
	_glStopInstrumentsSGIX = NULL;
#	endif
#	ifdef glFrameZoomSGIX
	_glFrameZoomSGIX = NULL;
#	endif
#	ifdef glTagSampleBufferSGIX
	_glTagSampleBufferSGIX = NULL;
#	endif
#	ifdef glDeformationMap3dSGIX
	_glDeformationMap3dSGIX = NULL;
#	endif
#	ifdef glDeformationMap3fSGIX
	_glDeformationMap3fSGIX = NULL;
#	endif
#	ifdef glDeformSGIX
	_glDeformSGIX = NULL;
#	endif
#	ifdef glLoadIdentityDeformationMapSGIX
	_glLoadIdentityDeformationMapSGIX = NULL;
#	endif
#	ifdef glReferencePlaneSGIX
	_glReferencePlaneSGIX = NULL;
#	endif
#	ifdef glFlushRasterSGIX
	_glFlushRasterSGIX = NULL;
#	endif
#	ifdef glFogFuncSGIS
	_glFogFuncSGIS = NULL;
#	endif
#	ifdef glGetFogFuncSGIS
	_glGetFogFuncSGIS = NULL;
#	endif
#	ifdef glImageTransformParameteriHP
	_glImageTransformParameteriHP = NULL;
#	endif
#	ifdef glImageTransformParameterfHP
	_glImageTransformParameterfHP = NULL;
#	endif
#	ifdef glImageTransformParameterivHP
	_glImageTransformParameterivHP = NULL;
#	endif
#	ifdef glImageTransformParameterfvHP
	_glImageTransformParameterfvHP = NULL;
#	endif
#	ifdef glGetImageTransformParameterivHP
	_glGetImageTransformParameterivHP = NULL;
#	endif
#	ifdef glGetImageTransformParameterfvHP
	_glGetImageTransformParameterfvHP = NULL;
#	endif
#	ifdef glColorSubTableEXT
	_glColorSubTableEXT = NULL;
#	endif
#	ifdef glCopyColorSubTableEXT
	_glCopyColorSubTableEXT = NULL;
#	endif
#	ifdef glHintPGI
	_glHintPGI = NULL;
#	endif
#	ifdef glColorTableEXT
	_glColorTableEXT = NULL;
#	endif
#	ifdef glGetColorTableEXT
	_glGetColorTableEXT = NULL;
#	endif
#	ifdef glGetColorTableParameterivEXT
	_glGetColorTableParameterivEXT = NULL;
#	endif
#	ifdef glGetColorTableParameterfvEXT
	_glGetColorTableParameterfvEXT = NULL;
#	endif
#	ifdef glGetListParameterfvSGIX
	_glGetListParameterfvSGIX = NULL;
#	endif
#	ifdef glGetListParameterivSGIX
	_glGetListParameterivSGIX = NULL;
#	endif
#	ifdef glListParameterfSGIX
	_glListParameterfSGIX = NULL;
#	endif
#	ifdef glListParameterfvSGIX
	_glListParameterfvSGIX = NULL;
#	endif
#	ifdef glListParameteriSGIX
	_glListParameteriSGIX = NULL;
#	endif
#	ifdef glListParameterivSGIX
	_glListParameterivSGIX = NULL;
#	endif
#	ifdef glIndexMaterialEXT
	_glIndexMaterialEXT = NULL;
#	endif
#	ifdef glIndexFuncEXT
	_glIndexFuncEXT = NULL;
#	endif
#	ifdef glLockArraysEXT
	_glLockArraysEXT = NULL;
#	endif
#	ifdef glUnlockArraysEXT
	_glUnlockArraysEXT = NULL;
#	endif
#	ifdef glCullParameterdvEXT
	_glCullParameterdvEXT = NULL;
#	endif
#	ifdef glCullParameterfvEXT
	_glCullParameterfvEXT = NULL;
#	endif
#	ifdef glFragmentColorMaterialSGIX
	_glFragmentColorMaterialSGIX = NULL;
#	endif
#	ifdef glFragmentLightfSGIX
	_glFragmentLightfSGIX = NULL;
#	endif
#	ifdef glFragmentLightfvSGIX
	_glFragmentLightfvSGIX = NULL;
#	endif
#	ifdef glFragmentLightiSGIX
	_glFragmentLightiSGIX = NULL;
#	endif
#	ifdef glFragmentLightivSGIX
	_glFragmentLightivSGIX = NULL;
#	endif
#	ifdef glFragmentLightModelfSGIX
	_glFragmentLightModelfSGIX = NULL;
#	endif
#	ifdef glFragmentLightModelfvSGIX
	_glFragmentLightModelfvSGIX = NULL;
#	endif
#	ifdef glFragmentLightModeliSGIX
	_glFragmentLightModeliSGIX = NULL;
#	endif
#	ifdef glFragmentLightModelivSGIX
	_glFragmentLightModelivSGIX = NULL;
#	endif
#	ifdef glFragmentMaterialfSGIX
	_glFragmentMaterialfSGIX = NULL;
#	endif
#	ifdef glFragmentMaterialfvSGIX
	_glFragmentMaterialfvSGIX = NULL;
#	endif
#	ifdef glFragmentMaterialiSGIX
	_glFragmentMaterialiSGIX = NULL;
#	endif
#	ifdef glFragmentMaterialivSGIX
	_glFragmentMaterialivSGIX = NULL;
#	endif
#	ifdef glGetFragmentLightfvSGIX
	_glGetFragmentLightfvSGIX = NULL;
#	endif
#	ifdef glGetFragmentLightivSGIX
	_glGetFragmentLightivSGIX = NULL;
#	endif
#	ifdef glGetFragmentMaterialfvSGIX
	_glGetFragmentMaterialfvSGIX = NULL;
#	endif
#	ifdef glGetFragmentMaterialivSGIX
	_glGetFragmentMaterialivSGIX = NULL;
#	endif
#	ifdef glLightEnviSGIX
	_glLightEnviSGIX = NULL;
#	endif
#	ifdef glDrawRangeElementsEXT
	_glDrawRangeElementsEXT = NULL;
#	endif
#	ifdef glApplyTextureEXT
	_glApplyTextureEXT = NULL;
#	endif
#	ifdef glTextureLightEXT
	_glTextureLightEXT = NULL;
#	endif
#	ifdef glTextureMaterialEXT
	_glTextureMaterialEXT = NULL;
#	endif
#	ifdef glAsyncMarkerSGIX
	_glAsyncMarkerSGIX = NULL;
#	endif
#	ifdef glFinishAsyncSGIX
	_glFinishAsyncSGIX = NULL;
#	endif
#	ifdef glPollAsyncSGIX
	_glPollAsyncSGIX = NULL;
#	endif
#	ifdef glGenAsyncMarkersSGIX
	_glGenAsyncMarkersSGIX = NULL;
#	endif
#	ifdef glDeleteAsyncMarkersSGIX
	_glDeleteAsyncMarkersSGIX = NULL;
#	endif
#	ifdef glIsAsyncMarkerSGIX
	_glIsAsyncMarkerSGIX = NULL;
#	endif
#	ifdef glVertexPointervINTEL
	_glVertexPointervINTEL = NULL;
#	endif
#	ifdef glNormalPointervINTEL
	_glNormalPointervINTEL = NULL;
#	endif
#	ifdef glColorPointervINTEL
	_glColorPointervINTEL = NULL;
#	endif
#	ifdef glTexCoordPointervINTEL
	_glTexCoordPointervINTEL = NULL;
#	endif
#	ifdef glPixelTransformParameteriEXT
	_glPixelTransformParameteriEXT = NULL;
#	endif
#	ifdef glPixelTransformParameterfEXT
	_glPixelTransformParameterfEXT = NULL;
#	endif
#	ifdef glPixelTransformParameterivEXT
	_glPixelTransformParameterivEXT = NULL;
#	endif
#	ifdef glPixelTransformParameterfvEXT
	_glPixelTransformParameterfvEXT = NULL;
#	endif
#	ifdef glGetPixelTransformParameterivEXT
	_glGetPixelTransformParameterivEXT = NULL;
#	endif
#	ifdef glGetPixelTransformParameterfvEXT
	_glGetPixelTransformParameterfvEXT = NULL;
#	endif
#	ifdef glSecondaryColor3bEXT
	_glSecondaryColor3bEXT = NULL;
#	endif
#	ifdef glSecondaryColor3bvEXT
	_glSecondaryColor3bvEXT = NULL;
#	endif
#	ifdef glSecondaryColor3dEXT
	_glSecondaryColor3dEXT = NULL;
#	endif
#	ifdef glSecondaryColor3dvEXT
	_glSecondaryColor3dvEXT = NULL;
#	endif
#	ifdef glSecondaryColor3fEXT
	_glSecondaryColor3fEXT = NULL;
#	endif
#	ifdef glSecondaryColor3fvEXT
	_glSecondaryColor3fvEXT = NULL;
#	endif
#	ifdef glSecondaryColor3iEXT
	_glSecondaryColor3iEXT = NULL;
#	endif
#	ifdef glSecondaryColor3ivEXT
	_glSecondaryColor3ivEXT = NULL;
#	endif
#	ifdef glSecondaryColor3sEXT
	_glSecondaryColor3sEXT = NULL;
#	endif
#	ifdef glSecondaryColor3svEXT
	_glSecondaryColor3svEXT = NULL;
#	endif
#	ifdef glSecondaryColor3ubEXT
	_glSecondaryColor3ubEXT = NULL;
#	endif
#	ifdef glSecondaryColor3ubvEXT
	_glSecondaryColor3ubvEXT = NULL;
#	endif
#	ifdef glSecondaryColor3uiEXT
	_glSecondaryColor3uiEXT = NULL;
#	endif
#	ifdef glSecondaryColor3uivEXT
	_glSecondaryColor3uivEXT = NULL;
#	endif
#	ifdef glSecondaryColor3usEXT
	_glSecondaryColor3usEXT = NULL;
#	endif
#	ifdef glSecondaryColor3usvEXT
	_glSecondaryColor3usvEXT = NULL;
#	endif
#	ifdef glSecondaryColorPointerEXT
	_glSecondaryColorPointerEXT = NULL;
#	endif
#	ifdef glTextureNormalEXT
	_glTextureNormalEXT = NULL;
#	endif
#	ifdef glMultiDrawArraysEXT
	_glMultiDrawArraysEXT = NULL;
#	endif
#	ifdef glMultiDrawElementsEXT
	_glMultiDrawElementsEXT = NULL;
#	endif
#	ifdef glFogCoordfEXT
	_glFogCoordfEXT = NULL;
#	endif
#	ifdef glFogCoordfvEXT
	_glFogCoordfvEXT = NULL;
#	endif
#	ifdef glFogCoorddEXT
	_glFogCoorddEXT = NULL;
#	endif
#	ifdef glFogCoorddvEXT
	_glFogCoorddvEXT = NULL;
#	endif
#	ifdef glFogCoordPointerEXT
	_glFogCoordPointerEXT = NULL;
#	endif
#	ifdef glTangent3bEXT
	_glTangent3bEXT = NULL;
#	endif
#	ifdef glTangent3bvEXT
	_glTangent3bvEXT = NULL;
#	endif
#	ifdef glTangent3dEXT
	_glTangent3dEXT = NULL;
#	endif
#	ifdef glTangent3dvEXT
	_glTangent3dvEXT = NULL;
#	endif
#	ifdef glTangent3fEXT
	_glTangent3fEXT = NULL;
#	endif
#	ifdef glTangent3fvEXT
	_glTangent3fvEXT = NULL;
#	endif
#	ifdef glTangent3iEXT
	_glTangent3iEXT = NULL;
#	endif
#	ifdef glTangent3ivEXT
	_glTangent3ivEXT = NULL;
#	endif
#	ifdef glTangent3sEXT
	_glTangent3sEXT = NULL;
#	endif
#	ifdef glTangent3svEXT
	_glTangent3svEXT = NULL;
#	endif
#	ifdef glBinormal3bEXT
	_glBinormal3bEXT = NULL;
#	endif
#	ifdef glBinormal3bvEXT
	_glBinormal3bvEXT = NULL;
#	endif
#	ifdef glBinormal3dEXT
	_glBinormal3dEXT = NULL;
#	endif
#	ifdef glBinormal3dvEXT
	_glBinormal3dvEXT = NULL;
#	endif
#	ifdef glBinormal3fEXT
	_glBinormal3fEXT = NULL;
#	endif
#	ifdef glBinormal3fvEXT
	_glBinormal3fvEXT = NULL;
#	endif
#	ifdef glBinormal3iEXT
	_glBinormal3iEXT = NULL;
#	endif
#	ifdef glBinormal3ivEXT
	_glBinormal3ivEXT = NULL;
#	endif
#	ifdef glBinormal3sEXT
	_glBinormal3sEXT = NULL;
#	endif
#	ifdef glBinormal3svEXT
	_glBinormal3svEXT = NULL;
#	endif
#	ifdef glTangentPointerEXT
	_glTangentPointerEXT = NULL;
#	endif
#	ifdef glBinormalPointerEXT
	_glBinormalPointerEXT = NULL;
#	endif
#	ifdef glFinishTextureSUNX
	_glFinishTextureSUNX = NULL;
#	endif
#	ifdef glGlobalAlphaFactorbSUN
	_glGlobalAlphaFactorbSUN = NULL;
#	endif
#	ifdef glGlobalAlphaFactorsSUN
	_glGlobalAlphaFactorsSUN = NULL;
#	endif
#	ifdef glGlobalAlphaFactoriSUN
	_glGlobalAlphaFactoriSUN = NULL;
#	endif
#	ifdef glGlobalAlphaFactorfSUN
	_glGlobalAlphaFactorfSUN = NULL;
#	endif
#	ifdef glGlobalAlphaFactordSUN
	_glGlobalAlphaFactordSUN = NULL;
#	endif
#	ifdef glGlobalAlphaFactorubSUN
	_glGlobalAlphaFactorubSUN = NULL;
#	endif
#	ifdef glGlobalAlphaFactorusSUN
	_glGlobalAlphaFactorusSUN = NULL;
#	endif
#	ifdef glGlobalAlphaFactoruiSUN
	_glGlobalAlphaFactoruiSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiSUN
	_glReplacementCodeuiSUN = NULL;
#	endif
#	ifdef glReplacementCodeusSUN
	_glReplacementCodeusSUN = NULL;
#	endif
#	ifdef glReplacementCodeubSUN
	_glReplacementCodeubSUN = NULL;
#	endif
#	ifdef glReplacementCodeuivSUN
	_glReplacementCodeuivSUN = NULL;
#	endif
#	ifdef glReplacementCodeusvSUN
	_glReplacementCodeusvSUN = NULL;
#	endif
#	ifdef glReplacementCodeubvSUN
	_glReplacementCodeubvSUN = NULL;
#	endif
#	ifdef glReplacementCodePointerSUN
	_glReplacementCodePointerSUN = NULL;
#	endif
#	ifdef glColor4ubVertex2fSUN
	_glColor4ubVertex2fSUN = NULL;
#	endif
#	ifdef glColor4ubVertex2fvSUN
	_glColor4ubVertex2fvSUN = NULL;
#	endif
#	ifdef glColor4ubVertex3fSUN
	_glColor4ubVertex3fSUN = NULL;
#	endif
#	ifdef glColor4ubVertex3fvSUN
	_glColor4ubVertex3fvSUN = NULL;
#	endif
#	ifdef glColor3fVertex3fSUN
	_glColor3fVertex3fSUN = NULL;
#	endif
#	ifdef glColor3fVertex3fvSUN
	_glColor3fVertex3fvSUN = NULL;
#	endif
#	ifdef glNormal3fVertex3fSUN
	_glNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glNormal3fVertex3fvSUN
	_glNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glColor4fNormal3fVertex3fSUN
	_glColor4fNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glColor4fNormal3fVertex3fvSUN
	_glColor4fNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glTexCoord2fVertex3fSUN
	_glTexCoord2fVertex3fSUN = NULL;
#	endif
#	ifdef glTexCoord2fVertex3fvSUN
	_glTexCoord2fVertex3fvSUN = NULL;
#	endif
#	ifdef glTexCoord4fVertex4fSUN
	_glTexCoord4fVertex4fSUN = NULL;
#	endif
#	ifdef glTexCoord4fVertex4fvSUN
	_glTexCoord4fVertex4fvSUN = NULL;
#	endif
#	ifdef glTexCoord2fColor4ubVertex3fSUN
	_glTexCoord2fColor4ubVertex3fSUN = NULL;
#	endif
#	ifdef glTexCoord2fColor4ubVertex3fvSUN
	_glTexCoord2fColor4ubVertex3fvSUN = NULL;
#	endif
#	ifdef glTexCoord2fColor3fVertex3fSUN
	_glTexCoord2fColor3fVertex3fSUN = NULL;
#	endif
#	ifdef glTexCoord2fColor3fVertex3fvSUN
	_glTexCoord2fColor3fVertex3fvSUN = NULL;
#	endif
#	ifdef glTexCoord2fNormal3fVertex3fSUN
	_glTexCoord2fNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glTexCoord2fNormal3fVertex3fvSUN
	_glTexCoord2fNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glTexCoord2fColor4fNormal3fVertex3fSUN
	_glTexCoord2fColor4fNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glTexCoord2fColor4fNormal3fVertex3fvSUN
	_glTexCoord2fColor4fNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glTexCoord4fColor4fNormal3fVertex4fSUN
	_glTexCoord4fColor4fNormal3fVertex4fSUN = NULL;
#	endif
#	ifdef glTexCoord4fColor4fNormal3fVertex4fvSUN
	_glTexCoord4fColor4fNormal3fVertex4fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiVertex3fSUN
	_glReplacementCodeuiVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiVertex3fvSUN
	_glReplacementCodeuiVertex3fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiColor4ubVertex3fSUN
	_glReplacementCodeuiColor4ubVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiColor4ubVertex3fvSUN
	_glReplacementCodeuiColor4ubVertex3fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiColor3fVertex3fSUN
	_glReplacementCodeuiColor3fVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiColor3fVertex3fvSUN
	_glReplacementCodeuiColor3fVertex3fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiNormal3fVertex3fSUN
	_glReplacementCodeuiNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiNormal3fVertex3fvSUN
	_glReplacementCodeuiNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiColor4fNormal3fVertex3fSUN
	_glReplacementCodeuiColor4fNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiColor4fNormal3fVertex3fvSUN
	_glReplacementCodeuiColor4fNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiTexCoord2fVertex3fSUN
	_glReplacementCodeuiTexCoord2fVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiTexCoord2fVertex3fvSUN
	_glReplacementCodeuiTexCoord2fVertex3fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN
	_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN
	_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN
	_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN = NULL;
#	endif
#	ifdef glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN
	_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN = NULL;
#	endif
#	ifdef glBlendFuncSeparateEXT
	_glBlendFuncSeparateEXT = NULL;
#	endif
#	ifdef glBlendFuncSeparateINGR
	_glBlendFuncSeparateINGR = NULL;
#	endif
#	ifdef glVertexWeightfEXT
	_glVertexWeightfEXT = NULL;
#	endif
#	ifdef glVertexWeightfvEXT
	_glVertexWeightfvEXT = NULL;
#	endif
#	ifdef glVertexWeightPointerEXT
	_glVertexWeightPointerEXT = NULL;
#	endif
#	ifdef glFlushVertexArrayRangeNV
	_glFlushVertexArrayRangeNV = NULL;
#	endif
#	ifdef glVertexArrayRangeNV
	_glVertexArrayRangeNV = NULL;
#	endif
#	ifdef glCombinerParameterfvNV
	_glCombinerParameterfvNV = NULL;
#	endif
#	ifdef glCombinerParameterfNV
	_glCombinerParameterfNV = NULL;
#	endif
#	ifdef glCombinerParameterivNV
	_glCombinerParameterivNV = NULL;
#	endif
#	ifdef glCombinerParameteriNV
	_glCombinerParameteriNV = NULL;
#	endif
#	ifdef glCombinerInputNV
	_glCombinerInputNV = NULL;
#	endif
#	ifdef glCombinerOutputNV
	_glCombinerOutputNV = NULL;
#	endif
#	ifdef glFinalCombinerInputNV
	_glFinalCombinerInputNV = NULL;
#	endif
#	ifdef glGetCombinerInputParameterfvNV
	_glGetCombinerInputParameterfvNV = NULL;
#	endif
#	ifdef glGetCombinerInputParameterivNV
	_glGetCombinerInputParameterivNV = NULL;
#	endif
#	ifdef glGetCombinerOutputParameterfvNV
	_glGetCombinerOutputParameterfvNV = NULL;
#	endif
#	ifdef glGetCombinerOutputParameterivNV
	_glGetCombinerOutputParameterivNV = NULL;
#	endif
#	ifdef glGetFinalCombinerInputParameterfvNV
	_glGetFinalCombinerInputParameterfvNV = NULL;
#	endif
#	ifdef glGetFinalCombinerInputParameterivNV
	_glGetFinalCombinerInputParameterivNV = NULL;
#	endif
#	ifdef glResizeBuffersMESA
	_glResizeBuffersMESA = NULL;
#	endif
#	ifdef glWindowPos2dMESA
	_glWindowPos2dMESA = NULL;
#	endif
#	ifdef glWindowPos2dvMESA
	_glWindowPos2dvMESA = NULL;
#	endif
#	ifdef glWindowPos2fMESA
	_glWindowPos2fMESA = NULL;
#	endif
#	ifdef glWindowPos2fvMESA
	_glWindowPos2fvMESA = NULL;
#	endif
#	ifdef glWindowPos2iMESA
	_glWindowPos2iMESA = NULL;
#	endif
#	ifdef glWindowPos2ivMESA
	_glWindowPos2ivMESA = NULL;
#	endif
#	ifdef glWindowPos2sMESA
	_glWindowPos2sMESA = NULL;
#	endif
#	ifdef glWindowPos2svMESA
	_glWindowPos2svMESA = NULL;
#	endif
#	ifdef glWindowPos3dMESA
	_glWindowPos3dMESA = NULL;
#	endif
#	ifdef glWindowPos3dvMESA
	_glWindowPos3dvMESA = NULL;
#	endif
#	ifdef glWindowPos3fMESA
	_glWindowPos3fMESA = NULL;
#	endif
#	ifdef glWindowPos3fvMESA
	_glWindowPos3fvMESA = NULL;
#	endif
#	ifdef glWindowPos3iMESA
	_glWindowPos3iMESA = NULL;
#	endif
#	ifdef glWindowPos3ivMESA
	_glWindowPos3ivMESA = NULL;
#	endif
#	ifdef glWindowPos3sMESA
	_glWindowPos3sMESA = NULL;
#	endif
#	ifdef glWindowPos3svMESA
	_glWindowPos3svMESA = NULL;
#	endif
#	ifdef glWindowPos4dMESA
	_glWindowPos4dMESA = NULL;
#	endif
#	ifdef glWindowPos4dvMESA
	_glWindowPos4dvMESA = NULL;
#	endif
#	ifdef glWindowPos4fMESA
	_glWindowPos4fMESA = NULL;
#	endif
#	ifdef glWindowPos4fvMESA
	_glWindowPos4fvMESA = NULL;
#	endif
#	ifdef glWindowPos4iMESA
	_glWindowPos4iMESA = NULL;
#	endif
#	ifdef glWindowPos4ivMESA
	_glWindowPos4ivMESA = NULL;
#	endif
#	ifdef glWindowPos4sMESA
	_glWindowPos4sMESA = NULL;
#	endif
#	ifdef glWindowPos4svMESA
	_glWindowPos4svMESA = NULL;
#	endif
#	ifdef glMultiModeDrawArraysIBM
	_glMultiModeDrawArraysIBM = NULL;
#	endif
#	ifdef glMultiModeDrawElementsIBM
	_glMultiModeDrawElementsIBM = NULL;
#	endif
#	ifdef glColorPointerListIBM
	_glColorPointerListIBM = NULL;
#	endif
#	ifdef glSecondaryColorPointerListIBM
	_glSecondaryColorPointerListIBM = NULL;
#	endif
#	ifdef glEdgeFlagPointerListIBM
	_glEdgeFlagPointerListIBM = NULL;
#	endif
#	ifdef glFogCoordPointerListIBM
	_glFogCoordPointerListIBM = NULL;
#	endif
#	ifdef glIndexPointerListIBM
	_glIndexPointerListIBM = NULL;
#	endif
#	ifdef glNormalPointerListIBM
	_glNormalPointerListIBM = NULL;
#	endif
#	ifdef glTexCoordPointerListIBM
	_glTexCoordPointerListIBM = NULL;
#	endif
#	ifdef glVertexPointerListIBM
	_glVertexPointerListIBM = NULL;
#	endif
#	ifdef glTbufferMask3DFX
	_glTbufferMask3DFX = NULL;
#	endif
#	ifdef glSampleMaskEXT
	_glSampleMaskEXT = NULL;
#	endif
#	ifdef glSamplePatternEXT
	_glSamplePatternEXT = NULL;
#	endif
#	ifdef glTextureColorMaskSGIS
	_glTextureColorMaskSGIS = NULL;
#	endif
#	ifdef glIglooInterfaceSGIX
	_glIglooInterfaceSGIX = NULL;
#	endif
#	ifdef glDeleteFencesNV
	_glDeleteFencesNV = NULL;
#	endif
#	ifdef glGenFencesNV
	_glGenFencesNV = NULL;
#	endif
#	ifdef glIsFenceNV
	_glIsFenceNV = NULL;
#	endif
#	ifdef glTestFenceNV
	_glTestFenceNV = NULL;
#	endif
#	ifdef glGetFenceivNV
	_glGetFenceivNV = NULL;
#	endif
#	ifdef glFinishFenceNV
	_glFinishFenceNV = NULL;
#	endif
#	ifdef glSetFenceNV
	_glSetFenceNV = NULL;
#	endif
#	ifdef glMapControlPointsNV
	_glMapControlPointsNV = NULL;
#	endif
#	ifdef glMapParameterivNV
	_glMapParameterivNV = NULL;
#	endif
#	ifdef glMapParameterfvNV
	_glMapParameterfvNV = NULL;
#	endif
#	ifdef glGetMapControlPointsNV
	_glGetMapControlPointsNV = NULL;
#	endif
#	ifdef glGetMapParameterivNV
	_glGetMapParameterivNV = NULL;
#	endif
#	ifdef glGetMapParameterfvNV
	_glGetMapParameterfvNV = NULL;
#	endif
#	ifdef glGetMapAttribParameterivNV
	_glGetMapAttribParameterivNV = NULL;
#	endif
#	ifdef glGetMapAttribParameterfvNV
	_glGetMapAttribParameterfvNV = NULL;
#	endif
#	ifdef glEvalMapsNV
	_glEvalMapsNV = NULL;
#	endif
#	ifdef glCombinerStageParameterfvNV
	_glCombinerStageParameterfvNV = NULL;
#	endif
#	ifdef glGetCombinerStageParameterfvNV
	_glGetCombinerStageParameterfvNV = NULL;
#	endif
#	ifdef glAreProgramsResidentNV
	_glAreProgramsResidentNV = NULL;
#	endif
#	ifdef glBindProgramNV
	_glBindProgramNV = NULL;
#	endif
#	ifdef glDeleteProgramsNV
	_glDeleteProgramsNV = NULL;
#	endif
#	ifdef glExecuteProgramNV
	_glExecuteProgramNV = NULL;
#	endif
#	ifdef glGenProgramsNV
	_glGenProgramsNV = NULL;
#	endif
#	ifdef glGetProgramParameterdvNV
	_glGetProgramParameterdvNV = NULL;
#	endif
#	ifdef glGetProgramParameterfvNV
	_glGetProgramParameterfvNV = NULL;
#	endif
#	ifdef glGetProgramivNV
	_glGetProgramivNV = NULL;
#	endif
#	ifdef glGetProgramStringNV
	_glGetProgramStringNV = NULL;
#	endif
#	ifdef glGetTrackMatrixivNV
	_glGetTrackMatrixivNV = NULL;
#	endif
#	ifdef glGetVertexAttribdvNV
	_glGetVertexAttribdvNV = NULL;
#	endif
#	ifdef glGetVertexAttribfvNV
	_glGetVertexAttribfvNV = NULL;
#	endif
#	ifdef glGetVertexAttribivNV
	_glGetVertexAttribivNV = NULL;
#	endif
#	ifdef glGetVertexAttribPointervNV
	_glGetVertexAttribPointervNV = NULL;
#	endif
#	ifdef glIsProgramNV
	_glIsProgramNV = NULL;
#	endif
#	ifdef glLoadProgramNV
	_glLoadProgramNV = NULL;
#	endif
#	ifdef glProgramParameter4dNV
	_glProgramParameter4dNV = NULL;
#	endif
#	ifdef glProgramParameter4dvNV
	_glProgramParameter4dvNV = NULL;
#	endif
#	ifdef glProgramParameter4fNV
	_glProgramParameter4fNV = NULL;
#	endif
#	ifdef glProgramParameter4fvNV
	_glProgramParameter4fvNV = NULL;
#	endif
#	ifdef glProgramParameters4dvNV
	_glProgramParameters4dvNV = NULL;
#	endif
#	ifdef glProgramParameters4fvNV
	_glProgramParameters4fvNV = NULL;
#	endif
#	ifdef glRequestResidentProgramsNV
	_glRequestResidentProgramsNV = NULL;
#	endif
#	ifdef glTrackMatrixNV
	_glTrackMatrixNV = NULL;
#	endif
#	ifdef glVertexAttribPointerNV
	_glVertexAttribPointerNV = NULL;
#	endif
#	ifdef glVertexAttrib1dNV
	_glVertexAttrib1dNV = NULL;
#	endif
#	ifdef glVertexAttrib1dvNV
	_glVertexAttrib1dvNV = NULL;
#	endif
#	ifdef glVertexAttrib1fNV
	_glVertexAttrib1fNV = NULL;
#	endif
#	ifdef glVertexAttrib1fvNV
	_glVertexAttrib1fvNV = NULL;
#	endif
#	ifdef glVertexAttrib1sNV
	_glVertexAttrib1sNV = NULL;
#	endif
#	ifdef glVertexAttrib1svNV
	_glVertexAttrib1svNV = NULL;
#	endif
#	ifdef glVertexAttrib2dNV
	_glVertexAttrib2dNV = NULL;
#	endif
#	ifdef glVertexAttrib2dvNV
	_glVertexAttrib2dvNV = NULL;
#	endif
#	ifdef glVertexAttrib2fNV
	_glVertexAttrib2fNV = NULL;
#	endif
#	ifdef glVertexAttrib2fvNV
	_glVertexAttrib2fvNV = NULL;
#	endif
#	ifdef glVertexAttrib2sNV
	_glVertexAttrib2sNV = NULL;
#	endif
#	ifdef glVertexAttrib2svNV
	_glVertexAttrib2svNV = NULL;
#	endif
#	ifdef glVertexAttrib3dNV
	_glVertexAttrib3dNV = NULL;
#	endif
#	ifdef glVertexAttrib3dvNV
	_glVertexAttrib3dvNV = NULL;
#	endif
#	ifdef glVertexAttrib3fNV
	_glVertexAttrib3fNV = NULL;
#	endif
#	ifdef glVertexAttrib3fvNV
	_glVertexAttrib3fvNV = NULL;
#	endif
#	ifdef glVertexAttrib3sNV
	_glVertexAttrib3sNV = NULL;
#	endif
#	ifdef glVertexAttrib3svNV
	_glVertexAttrib3svNV = NULL;
#	endif
#	ifdef glVertexAttrib4dNV
	_glVertexAttrib4dNV = NULL;
#	endif
#	ifdef glVertexAttrib4dvNV
	_glVertexAttrib4dvNV = NULL;
#	endif
#	ifdef glVertexAttrib4fNV
	_glVertexAttrib4fNV = NULL;
#	endif
#	ifdef glVertexAttrib4fvNV
	_glVertexAttrib4fvNV = NULL;
#	endif
#	ifdef glVertexAttrib4sNV
	_glVertexAttrib4sNV = NULL;
#	endif
#	ifdef glVertexAttrib4svNV
	_glVertexAttrib4svNV = NULL;
#	endif
#	ifdef glVertexAttrib4ubNV
	_glVertexAttrib4ubNV = NULL;
#	endif
#	ifdef glVertexAttrib4ubvNV
	_glVertexAttrib4ubvNV = NULL;
#	endif
#	ifdef glVertexAttribs1dvNV
	_glVertexAttribs1dvNV = NULL;
#	endif
#	ifdef glVertexAttribs1fvNV
	_glVertexAttribs1fvNV = NULL;
#	endif
#	ifdef glVertexAttribs1svNV
	_glVertexAttribs1svNV = NULL;
#	endif
#	ifdef glVertexAttribs2dvNV
	_glVertexAttribs2dvNV = NULL;
#	endif
#	ifdef glVertexAttribs2fvNV
	_glVertexAttribs2fvNV = NULL;
#	endif
#	ifdef glVertexAttribs2svNV
	_glVertexAttribs2svNV = NULL;
#	endif
#	ifdef glVertexAttribs3dvNV
	_glVertexAttribs3dvNV = NULL;
#	endif
#	ifdef glVertexAttribs3fvNV
	_glVertexAttribs3fvNV = NULL;
#	endif
#	ifdef glVertexAttribs3svNV
	_glVertexAttribs3svNV = NULL;
#	endif
#	ifdef glVertexAttribs4dvNV
	_glVertexAttribs4dvNV = NULL;
#	endif
#	ifdef glVertexAttribs4fvNV
	_glVertexAttribs4fvNV = NULL;
#	endif
#	ifdef glVertexAttribs4svNV
	_glVertexAttribs4svNV = NULL;
#	endif
#	ifdef glVertexAttribs4ubvNV
	_glVertexAttribs4ubvNV = NULL;
#	endif
#	ifdef glTexBumpParameterivATI
	_glTexBumpParameterivATI = NULL;
#	endif
#	ifdef glTexBumpParameterfvATI
	_glTexBumpParameterfvATI = NULL;
#	endif
#	ifdef glGetTexBumpParameterivATI
	_glGetTexBumpParameterivATI = NULL;
#	endif
#	ifdef glGetTexBumpParameterfvATI
	_glGetTexBumpParameterfvATI = NULL;
#	endif
#	ifdef glGenFragmentShadersATI
	_glGenFragmentShadersATI = NULL;
#	endif
#	ifdef glBindFragmentShaderATI
	_glBindFragmentShaderATI = NULL;
#	endif
#	ifdef glDeleteFragmentShaderATI
	_glDeleteFragmentShaderATI = NULL;
#	endif
#	ifdef glBeginFragmentShaderATI
	_glBeginFragmentShaderATI = NULL;
#	endif
#	ifdef glEndFragmentShaderATI
	_glEndFragmentShaderATI = NULL;
#	endif
#	ifdef glPassTexCoordATI
	_glPassTexCoordATI = NULL;
#	endif
#	ifdef glSampleMapATI
	_glSampleMapATI = NULL;
#	endif
#	ifdef glColorFragmentOp1ATI
	_glColorFragmentOp1ATI = NULL;
#	endif
#	ifdef glColorFragmentOp2ATI
	_glColorFragmentOp2ATI = NULL;
#	endif
#	ifdef glColorFragmentOp3ATI
	_glColorFragmentOp3ATI = NULL;
#	endif
#	ifdef glAlphaFragmentOp1ATI
	_glAlphaFragmentOp1ATI = NULL;
#	endif
#	ifdef glAlphaFragmentOp2ATI
	_glAlphaFragmentOp2ATI = NULL;
#	endif
#	ifdef glAlphaFragmentOp3ATI
	_glAlphaFragmentOp3ATI = NULL;
#	endif
#	ifdef glSetFragmentShaderConstantATI
	_glSetFragmentShaderConstantATI = NULL;
#	endif
#	ifdef glPNTrianglesiATI
	_glPNTrianglesiATI = NULL;
#	endif
#	ifdef glPNTrianglesfATI
	_glPNTrianglesfATI = NULL;
#	endif
#	ifdef glNewObjectBufferATI
	_glNewObjectBufferATI = NULL;
#	endif
#	ifdef glIsObjectBufferATI
	_glIsObjectBufferATI = NULL;
#	endif
#	ifdef glUpdateObjectBufferATI
	_glUpdateObjectBufferATI = NULL;
#	endif
#	ifdef glGetObjectBufferfvATI
	_glGetObjectBufferfvATI = NULL;
#	endif
#	ifdef glGetObjectBufferivATI
	_glGetObjectBufferivATI = NULL;
#	endif
#	ifdef glFreeObjectBufferATI
	_glFreeObjectBufferATI = NULL;
#	endif
#	ifdef glArrayObjectATI
	_glArrayObjectATI = NULL;
#	endif
#	ifdef glGetArrayObjectfvATI
	_glGetArrayObjectfvATI = NULL;
#	endif
#	ifdef glGetArrayObjectivATI
	_glGetArrayObjectivATI = NULL;
#	endif
#	ifdef glVariantArrayObjectATI
	_glVariantArrayObjectATI = NULL;
#	endif
#	ifdef glGetVariantArrayObjectfvATI
	_glGetVariantArrayObjectfvATI = NULL;
#	endif
#	ifdef glGetVariantArrayObjectivATI
	_glGetVariantArrayObjectivATI = NULL;
#	endif
#	ifdef glBeginVertexShaderEXT
	_glBeginVertexShaderEXT = NULL;
#	endif
#	ifdef glEndVertexShaderEXT
	_glEndVertexShaderEXT = NULL;
#	endif
#	ifdef glBindVertexShaderEXT
	_glBindVertexShaderEXT = NULL;
#	endif
#	ifdef glGenVertexShadersEXT
	_glGenVertexShadersEXT = NULL;
#	endif
#	ifdef glDeleteVertexShaderEXT
	_glDeleteVertexShaderEXT = NULL;
#	endif
#	ifdef glShaderOp1EXT
	_glShaderOp1EXT = NULL;
#	endif
#	ifdef glShaderOp2EXT
	_glShaderOp2EXT = NULL;
#	endif
#	ifdef glShaderOp3EXT
	_glShaderOp3EXT = NULL;
#	endif
#	ifdef glSwizzleEXT
	_glSwizzleEXT = NULL;
#	endif
#	ifdef glWriteMaskEXT
	_glWriteMaskEXT = NULL;
#	endif
#	ifdef glInsertComponentEXT
	_glInsertComponentEXT = NULL;
#	endif
#	ifdef glExtractComponentEXT
	_glExtractComponentEXT = NULL;
#	endif
#	ifdef glGenSymbolsEXT
	_glGenSymbolsEXT = NULL;
#	endif
#	ifdef glSetInvariantEXT
	_glSetInvariantEXT = NULL;
#	endif
#	ifdef glSetLocalConstantEXT
	_glSetLocalConstantEXT = NULL;
#	endif
#	ifdef glVariantbvEXT
	_glVariantbvEXT = NULL;
#	endif
#	ifdef glVariantsvEXT
	_glVariantsvEXT = NULL;
#	endif
#	ifdef glVariantivEXT
	_glVariantivEXT = NULL;
#	endif
#	ifdef glVariantfvEXT
	_glVariantfvEXT = NULL;
#	endif
#	ifdef glVariantdvEXT
	_glVariantdvEXT = NULL;
#	endif
#	ifdef glVariantubvEXT
	_glVariantubvEXT = NULL;
#	endif
#	ifdef glVariantusvEXT
	_glVariantusvEXT = NULL;
#	endif
#	ifdef glVariantuivEXT
	_glVariantuivEXT = NULL;
#	endif
#	ifdef glVariantPointerEXT
	_glVariantPointerEXT = NULL;
#	endif
#	ifdef glEnableVariantClientStateEXT
	_glEnableVariantClientStateEXT = NULL;
#	endif
#	ifdef glDisableVariantClientStateEXT
	_glDisableVariantClientStateEXT = NULL;
#	endif
#	ifdef glBindLightParameterEXT
	_glBindLightParameterEXT = NULL;
#	endif
#	ifdef glBindMaterialParameterEXT
	_glBindMaterialParameterEXT = NULL;
#	endif
#	ifdef glBindTexGenParameterEXT
	_glBindTexGenParameterEXT = NULL;
#	endif
#	ifdef glBindTextureUnitParameterEXT
	_glBindTextureUnitParameterEXT = NULL;
#	endif
#	ifdef glBindParameterEXT
	_glBindParameterEXT = NULL;
#	endif
#	ifdef glIsVariantEnabledEXT
	_glIsVariantEnabledEXT = NULL;
#	endif
#	ifdef glGetVariantBooleanvEXT
	_glGetVariantBooleanvEXT = NULL;
#	endif
#	ifdef glGetVariantIntegervEXT
	_glGetVariantIntegervEXT = NULL;
#	endif
#	ifdef glGetVariantFloatvEXT
	_glGetVariantFloatvEXT = NULL;
#	endif
#	ifdef glGetVariantPointervEXT
	_glGetVariantPointervEXT = NULL;
#	endif
#	ifdef glGetInvariantBooleanvEXT
	_glGetInvariantBooleanvEXT = NULL;
#	endif
#	ifdef glGetInvariantIntegervEXT
	_glGetInvariantIntegervEXT = NULL;
#	endif
#	ifdef glGetInvariantFloatvEXT
	_glGetInvariantFloatvEXT = NULL;
#	endif
#	ifdef glGetLocalConstantBooleanvEXT
	_glGetLocalConstantBooleanvEXT = NULL;
#	endif
#	ifdef glGetLocalConstantIntegervEXT
	_glGetLocalConstantIntegervEXT = NULL;
#	endif
#	ifdef glGetLocalConstantFloatvEXT
	_glGetLocalConstantFloatvEXT = NULL;
#	endif
#	ifdef glVertexStream1sATI
	_glVertexStream1sATI = NULL;
#	endif
#	ifdef glVertexStream1svATI
	_glVertexStream1svATI = NULL;
#	endif
#	ifdef glVertexStream1iATI
	_glVertexStream1iATI = NULL;
#	endif
#	ifdef glVertexStream1ivATI
	_glVertexStream1ivATI = NULL;
#	endif
#	ifdef glVertexStream1fATI
	_glVertexStream1fATI = NULL;
#	endif
#	ifdef glVertexStream1fvATI
	_glVertexStream1fvATI = NULL;
#	endif
#	ifdef glVertexStream1dATI
	_glVertexStream1dATI = NULL;
#	endif
#	ifdef glVertexStream1dvATI
	_glVertexStream1dvATI = NULL;
#	endif
#	ifdef glVertexStream2sATI
	_glVertexStream2sATI = NULL;
#	endif
#	ifdef glVertexStream2svATI
	_glVertexStream2svATI = NULL;
#	endif
#	ifdef glVertexStream2iATI
	_glVertexStream2iATI = NULL;
#	endif
#	ifdef glVertexStream2ivATI
	_glVertexStream2ivATI = NULL;
#	endif
#	ifdef glVertexStream2fATI
	_glVertexStream2fATI = NULL;
#	endif
#	ifdef glVertexStream2fvATI
	_glVertexStream2fvATI = NULL;
#	endif
#	ifdef glVertexStream2dATI
	_glVertexStream2dATI = NULL;
#	endif
#	ifdef glVertexStream2dvATI
	_glVertexStream2dvATI = NULL;
#	endif
#	ifdef glVertexStream3sATI
	_glVertexStream3sATI = NULL;
#	endif
#	ifdef glVertexStream3svATI
	_glVertexStream3svATI = NULL;
#	endif
#	ifdef glVertexStream3iATI
	_glVertexStream3iATI = NULL;
#	endif
#	ifdef glVertexStream3ivATI
	_glVertexStream3ivATI = NULL;
#	endif
#	ifdef glVertexStream3fATI
	_glVertexStream3fATI = NULL;
#	endif
#	ifdef glVertexStream3fvATI
	_glVertexStream3fvATI = NULL;
#	endif
#	ifdef glVertexStream3dATI
	_glVertexStream3dATI = NULL;
#	endif
#	ifdef glVertexStream3dvATI
	_glVertexStream3dvATI = NULL;
#	endif
#	ifdef glVertexStream4sATI
	_glVertexStream4sATI = NULL;
#	endif
#	ifdef glVertexStream4svATI
	_glVertexStream4svATI = NULL;
#	endif
#	ifdef glVertexStream4iATI
	_glVertexStream4iATI = NULL;
#	endif
#	ifdef glVertexStream4ivATI
	_glVertexStream4ivATI = NULL;
#	endif
#	ifdef glVertexStream4fATI
	_glVertexStream4fATI = NULL;
#	endif
#	ifdef glVertexStream4fvATI
	_glVertexStream4fvATI = NULL;
#	endif
#	ifdef glVertexStream4dATI
	_glVertexStream4dATI = NULL;
#	endif
#	ifdef glVertexStream4dvATI
	_glVertexStream4dvATI = NULL;
#	endif
#	ifdef glNormalStream3bATI
	_glNormalStream3bATI = NULL;
#	endif
#	ifdef glNormalStream3bvATI
	_glNormalStream3bvATI = NULL;
#	endif
#	ifdef glNormalStream3sATI
	_glNormalStream3sATI = NULL;
#	endif
#	ifdef glNormalStream3svATI
	_glNormalStream3svATI = NULL;
#	endif
#	ifdef glNormalStream3iATI
	_glNormalStream3iATI = NULL;
#	endif
#	ifdef glNormalStream3ivATI
	_glNormalStream3ivATI = NULL;
#	endif
#	ifdef glNormalStream3fATI
	_glNormalStream3fATI = NULL;
#	endif
#	ifdef glNormalStream3fvATI
	_glNormalStream3fvATI = NULL;
#	endif
#	ifdef glNormalStream3dATI
	_glNormalStream3dATI = NULL;
#	endif
#	ifdef glNormalStream3dvATI
	_glNormalStream3dvATI = NULL;
#	endif
#	ifdef glClientActiveVertexStreamATI
	_glClientActiveVertexStreamATI = NULL;
#	endif
#	ifdef glVertexBlendEnviATI
	_glVertexBlendEnviATI = NULL;
#	endif
#	ifdef glVertexBlendEnvfATI
	_glVertexBlendEnvfATI = NULL;
#	endif
#	ifdef glElementPointerATI
	_glElementPointerATI = NULL;
#	endif
#	ifdef glDrawElementArrayATI
	_glDrawElementArrayATI = NULL;
#	endif
#	ifdef glDrawRangeElementArrayATI
	_glDrawRangeElementArrayATI = NULL;
#	endif
#	ifdef glDrawMeshArraysSUN
	_glDrawMeshArraysSUN = NULL;
#	endif
#	ifdef glGenOcclusionQueriesNV
	_glGenOcclusionQueriesNV = NULL;
#	endif
#	ifdef glDeleteOcclusionQueriesNV
	_glDeleteOcclusionQueriesNV = NULL;
#	endif
#	ifdef glIsOcclusionQueryNV
	_glIsOcclusionQueryNV = NULL;
#	endif
#	ifdef glBeginOcclusionQueryNV
	_glBeginOcclusionQueryNV = NULL;
#	endif
#	ifdef glEndOcclusionQueryNV
	_glEndOcclusionQueryNV = NULL;
#	endif
#	ifdef glGetOcclusionQueryivNV
	_glGetOcclusionQueryivNV = NULL;
#	endif
#	ifdef glGetOcclusionQueryuivNV
	_glGetOcclusionQueryuivNV = NULL;
#	endif
#	ifdef glPointParameteriNV
	_glPointParameteriNV = NULL;
#	endif
#	ifdef glPointParameterivNV
	_glPointParameterivNV = NULL;
#	endif
#	ifdef glActiveStencilFaceEXT
	_glActiveStencilFaceEXT = NULL;
#	endif
#	ifdef glElementPointerAPPLE
	_glElementPointerAPPLE = NULL;
#	endif
#	ifdef glDrawElementArrayAPPLE
	_glDrawElementArrayAPPLE = NULL;
#	endif
#	ifdef glDrawRangeElementArrayAPPLE
	_glDrawRangeElementArrayAPPLE = NULL;
#	endif
#	ifdef glMultiDrawElementArrayAPPLE
	_glMultiDrawElementArrayAPPLE = NULL;
#	endif
#	ifdef glMultiDrawRangeElementArrayAPPLE
	_glMultiDrawRangeElementArrayAPPLE = NULL;
#	endif
#	ifdef glGenFencesAPPLE
	_glGenFencesAPPLE = NULL;
#	endif
#	ifdef glDeleteFencesAPPLE
	_glDeleteFencesAPPLE = NULL;
#	endif
#	ifdef glSetFenceAPPLE
	_glSetFenceAPPLE = NULL;
#	endif
#	ifdef glIsFenceAPPLE
	_glIsFenceAPPLE = NULL;
#	endif
#	ifdef glTestFenceAPPLE
	_glTestFenceAPPLE = NULL;
#	endif
#	ifdef glFinishFenceAPPLE
	_glFinishFenceAPPLE = NULL;
#	endif
#	ifdef glTestObjectAPPLE
	_glTestObjectAPPLE = NULL;
#	endif
#	ifdef glFinishObjectAPPLE
	_glFinishObjectAPPLE = NULL;
#	endif
#	ifdef glBindVertexArrayAPPLE
	_glBindVertexArrayAPPLE = NULL;
#	endif
#	ifdef glDeleteVertexArraysAPPLE
	_glDeleteVertexArraysAPPLE = NULL;
#	endif
#	ifdef glGenVertexArraysAPPLE
	_glGenVertexArraysAPPLE = NULL;
#	endif
#	ifdef glIsVertexArrayAPPLE
	_glIsVertexArrayAPPLE = NULL;
#	endif
#	ifdef glVertexArrayRangeAPPLE
	_glVertexArrayRangeAPPLE = NULL;
#	endif
#	ifdef glFlushVertexArrayRangeAPPLE
	_glFlushVertexArrayRangeAPPLE = NULL;
#	endif
#	ifdef glVertexArrayParameteriAPPLE
	_glVertexArrayParameteriAPPLE = NULL;
#	endif
#	ifdef glDrawBuffersATI
	_glDrawBuffersATI = NULL;
#	endif
#	ifdef glProgramNamedParameter4fNV
	_glProgramNamedParameter4fNV = NULL;
#	endif
#	ifdef glProgramNamedParameter4dNV
	_glProgramNamedParameter4dNV = NULL;
#	endif
#	ifdef glProgramNamedParameter4fvNV
	_glProgramNamedParameter4fvNV = NULL;
#	endif
#	ifdef glProgramNamedParameter4dvNV
	_glProgramNamedParameter4dvNV = NULL;
#	endif
#	ifdef glGetProgramNamedParameterfvNV
	_glGetProgramNamedParameterfvNV = NULL;
#	endif
#	ifdef glGetProgramNamedParameterdvNV
	_glGetProgramNamedParameterdvNV = NULL;
#	endif
#	ifdef glVertex2hNV
	_glVertex2hNV = NULL;
#	endif
#	ifdef glVertex2hvNV
	_glVertex2hvNV = NULL;
#	endif
#	ifdef glVertex3hNV
	_glVertex3hNV = NULL;
#	endif
#	ifdef glVertex3hvNV
	_glVertex3hvNV = NULL;
#	endif
#	ifdef glVertex4hNV
	_glVertex4hNV = NULL;
#	endif
#	ifdef glVertex4hvNV
	_glVertex4hvNV = NULL;
#	endif
#	ifdef glNormal3hNV
	_glNormal3hNV = NULL;
#	endif
#	ifdef glNormal3hvNV
	_glNormal3hvNV = NULL;
#	endif
#	ifdef glColor3hNV
	_glColor3hNV = NULL;
#	endif
#	ifdef glColor3hvNV
	_glColor3hvNV = NULL;
#	endif
#	ifdef glColor4hNV
	_glColor4hNV = NULL;
#	endif
#	ifdef glColor4hvNV
	_glColor4hvNV = NULL;
#	endif
#	ifdef glTexCoord1hNV
	_glTexCoord1hNV = NULL;
#	endif
#	ifdef glTexCoord1hvNV
	_glTexCoord1hvNV = NULL;
#	endif
#	ifdef glTexCoord2hNV
	_glTexCoord2hNV = NULL;
#	endif
#	ifdef glTexCoord2hvNV
	_glTexCoord2hvNV = NULL;
#	endif
#	ifdef glTexCoord3hNV
	_glTexCoord3hNV = NULL;
#	endif
#	ifdef glTexCoord3hvNV
	_glTexCoord3hvNV = NULL;
#	endif
#	ifdef glTexCoord4hNV
	_glTexCoord4hNV = NULL;
#	endif
#	ifdef glTexCoord4hvNV
	_glTexCoord4hvNV = NULL;
#	endif
#	ifdef glMultiTexCoord1hNV
	_glMultiTexCoord1hNV = NULL;
#	endif
#	ifdef glMultiTexCoord1hvNV
	_glMultiTexCoord1hvNV = NULL;
#	endif
#	ifdef glMultiTexCoord2hNV
	_glMultiTexCoord2hNV = NULL;
#	endif
#	ifdef glMultiTexCoord2hvNV
	_glMultiTexCoord2hvNV = NULL;
#	endif
#	ifdef glMultiTexCoord3hNV
	_glMultiTexCoord3hNV = NULL;
#	endif
#	ifdef glMultiTexCoord3hvNV
	_glMultiTexCoord3hvNV = NULL;
#	endif
#	ifdef glMultiTexCoord4hNV
	_glMultiTexCoord4hNV = NULL;
#	endif
#	ifdef glMultiTexCoord4hvNV
	_glMultiTexCoord4hvNV = NULL;
#	endif
#	ifdef glFogCoordhNV
	_glFogCoordhNV = NULL;
#	endif
#	ifdef glFogCoordhvNV
	_glFogCoordhvNV = NULL;
#	endif
#	ifdef glSecondaryColor3hNV
	_glSecondaryColor3hNV = NULL;
#	endif
#	ifdef glSecondaryColor3hvNV
	_glSecondaryColor3hvNV = NULL;
#	endif
#	ifdef glVertexWeighthNV
	_glVertexWeighthNV = NULL;
#	endif
#	ifdef glVertexWeighthvNV
	_glVertexWeighthvNV = NULL;
#	endif
#	ifdef glVertexAttrib1hNV
	_glVertexAttrib1hNV = NULL;
#	endif
#	ifdef glVertexAttrib1hvNV
	_glVertexAttrib1hvNV = NULL;
#	endif
#	ifdef glVertexAttrib2hNV
	_glVertexAttrib2hNV = NULL;
#	endif
#	ifdef glVertexAttrib2hvNV
	_glVertexAttrib2hvNV = NULL;
#	endif
#	ifdef glVertexAttrib3hNV
	_glVertexAttrib3hNV = NULL;
#	endif
#	ifdef glVertexAttrib3hvNV
	_glVertexAttrib3hvNV = NULL;
#	endif
#	ifdef glVertexAttrib4hNV
	_glVertexAttrib4hNV = NULL;
#	endif
#	ifdef glVertexAttrib4hvNV
	_glVertexAttrib4hvNV = NULL;
#	endif
#	ifdef glVertexAttribs1hvNV
	_glVertexAttribs1hvNV = NULL;
#	endif
#	ifdef glVertexAttribs2hvNV
	_glVertexAttribs2hvNV = NULL;
#	endif
#	ifdef glVertexAttribs3hvNV
	_glVertexAttribs3hvNV = NULL;
#	endif
#	ifdef glVertexAttribs4hvNV
	_glVertexAttribs4hvNV = NULL;
#	endif
#	ifdef glPixelDataRangeNV
	_glPixelDataRangeNV = NULL;
#	endif
#	ifdef glFlushPixelDataRangeNV
	_glFlushPixelDataRangeNV = NULL;
#	endif
#	ifdef glPrimitiveRestartNV
	_glPrimitiveRestartNV = NULL;
#	endif
#	ifdef glPrimitiveRestartIndexNV
	_glPrimitiveRestartIndexNV = NULL;
#	endif
#	ifdef glMapObjectBufferATI
	_glMapObjectBufferATI = NULL;
#	endif
#	ifdef glUnmapObjectBufferATI
	_glUnmapObjectBufferATI = NULL;
#	endif
#	ifdef glStencilOpSeparateATI
	_glStencilOpSeparateATI = NULL;
#	endif
#	ifdef glStencilFuncSeparateATI
	_glStencilFuncSeparateATI = NULL;
#	endif
#	ifdef glVertexAttribArrayObjectATI
	_glVertexAttribArrayObjectATI = NULL;
#	endif
#	ifdef glGetVertexAttribArrayObjectfvATI
	_glGetVertexAttribArrayObjectfvATI = NULL;
#	endif
#	ifdef glGetVertexAttribArrayObjectivATI
	_glGetVertexAttribArrayObjectivATI = NULL;
#	endif
#	ifdef glDepthBoundsEXT
	_glDepthBoundsEXT = NULL;
#	endif
#	ifdef glBlendEquationSeparateEXT
	_glBlendEquationSeparateEXT = NULL;
#	endif
#	ifdef glIsRenderbufferEXT
	_glIsRenderbufferEXT = NULL;
#	endif
#	ifdef glBindRenderbufferEXT
	_glBindRenderbufferEXT = NULL;
#	endif
#	ifdef glDeleteRenderbuffersEXT
	_glDeleteRenderbuffersEXT = NULL;
#	endif
#	ifdef glGenRenderbuffersEXT
	_glGenRenderbuffersEXT = NULL;
#	endif
#	ifdef glRenderbufferStorageEXT
	_glRenderbufferStorageEXT = NULL;
#	endif
#	ifdef glGetRenderbufferParameterivEXT
	_glGetRenderbufferParameterivEXT = NULL;
#	endif
#	ifdef glIsFramebufferEXT
	_glIsFramebufferEXT = NULL;
#	endif
#	ifdef glBindFramebufferEXT
	_glBindFramebufferEXT = NULL;
#	endif
#	ifdef glDeleteFramebuffersEXT
	_glDeleteFramebuffersEXT = NULL;
#	endif
#	ifdef glGenFramebuffersEXT
	_glGenFramebuffersEXT = NULL;
#	endif
#	ifdef glCheckFramebufferStatusEXT
	_glCheckFramebufferStatusEXT = NULL;
#	endif
#	ifdef glFramebufferTexture1DEXT
	_glFramebufferTexture1DEXT = NULL;
#	endif
#	ifdef glFramebufferTexture2DEXT
	_glFramebufferTexture2DEXT = NULL;
#	endif
#	ifdef glFramebufferTexture3DEXT
	_glFramebufferTexture3DEXT = NULL;
#	endif
#	ifdef glFramebufferRenderbufferEXT
	_glFramebufferRenderbufferEXT = NULL;
#	endif
#	ifdef glGetFramebufferAttachmentParameterivEXT
	_glGetFramebufferAttachmentParameterivEXT = NULL;
#	endif
#	ifdef glGenerateMipmapEXT
	_glGenerateMipmapEXT = NULL;
#	endif
#	ifdef glStringMarkerGREMEDY
	_glStringMarkerGREMEDY = NULL;
#	endif
#	ifdef glStencilClearTagEXT
	_glStencilClearTagEXT = NULL;
#	endif
#	ifdef glBlitFramebufferEXT
	_glBlitFramebufferEXT = NULL;
#	endif
#	ifdef glRenderbufferStorageMultisampleEXT
	_glRenderbufferStorageMultisampleEXT = NULL;
#	endif
#	ifdef glGetQueryObjecti64vEXT
	_glGetQueryObjecti64vEXT = NULL;
#	endif
#	ifdef glGetQueryObjectui64vEXT
	_glGetQueryObjectui64vEXT = NULL;
#	endif
#	ifdef glProgramEnvParameters4fvEXT
	_glProgramEnvParameters4fvEXT = NULL;
#	endif
#	ifdef glProgramLocalParameters4fvEXT
	_glProgramLocalParameters4fvEXT = NULL;
#	endif
#	ifdef glBufferParameteriAPPLE
	_glBufferParameteriAPPLE = NULL;
#	endif
#	ifdef glFlushMappedBufferRangeAPPLE
	_glFlushMappedBufferRangeAPPLE = NULL;
#	endif
#	ifdef glProgramLocalParameterI4iNV
	_glProgramLocalParameterI4iNV = NULL;
#	endif
#	ifdef glProgramLocalParameterI4ivNV
	_glProgramLocalParameterI4ivNV = NULL;
#	endif
#	ifdef glProgramLocalParametersI4ivNV
	_glProgramLocalParametersI4ivNV = NULL;
#	endif
#	ifdef glProgramLocalParameterI4uiNV
	_glProgramLocalParameterI4uiNV = NULL;
#	endif
#	ifdef glProgramLocalParameterI4uivNV
	_glProgramLocalParameterI4uivNV = NULL;
#	endif
#	ifdef glProgramLocalParametersI4uivNV
	_glProgramLocalParametersI4uivNV = NULL;
#	endif
#	ifdef glProgramEnvParameterI4iNV
	_glProgramEnvParameterI4iNV = NULL;
#	endif
#	ifdef glProgramEnvParameterI4ivNV
	_glProgramEnvParameterI4ivNV = NULL;
#	endif
#	ifdef glProgramEnvParametersI4ivNV
	_glProgramEnvParametersI4ivNV = NULL;
#	endif
#	ifdef glProgramEnvParameterI4uiNV
	_glProgramEnvParameterI4uiNV = NULL;
#	endif
#	ifdef glProgramEnvParameterI4uivNV
	_glProgramEnvParameterI4uivNV = NULL;
#	endif
#	ifdef glProgramEnvParametersI4uivNV
	_glProgramEnvParametersI4uivNV = NULL;
#	endif
#	ifdef glGetProgramLocalParameterIivNV
	_glGetProgramLocalParameterIivNV = NULL;
#	endif
#	ifdef glGetProgramLocalParameterIuivNV
	_glGetProgramLocalParameterIuivNV = NULL;
#	endif
#	ifdef glGetProgramEnvParameterIivNV
	_glGetProgramEnvParameterIivNV = NULL;
#	endif
#	ifdef glGetProgramEnvParameterIuivNV
	_glGetProgramEnvParameterIuivNV = NULL;
#	endif
#	ifdef glProgramVertexLimitNV
	_glProgramVertexLimitNV = NULL;
#	endif
#	ifdef glFramebufferTextureEXT
	_glFramebufferTextureEXT = NULL;
#	endif
#	ifdef glFramebufferTextureLayerEXT
	_glFramebufferTextureLayerEXT = NULL;
#	endif
#	ifdef glFramebufferTextureFaceEXT
	_glFramebufferTextureFaceEXT = NULL;
#	endif
#	ifdef glProgramParameteriEXT
	_glProgramParameteriEXT = NULL;
#	endif
#	ifdef glVertexAttribI1iEXT
	_glVertexAttribI1iEXT = NULL;
#	endif
#	ifdef glVertexAttribI2iEXT
	_glVertexAttribI2iEXT = NULL;
#	endif
#	ifdef glVertexAttribI3iEXT
	_glVertexAttribI3iEXT = NULL;
#	endif
#	ifdef glVertexAttribI4iEXT
	_glVertexAttribI4iEXT = NULL;
#	endif
#	ifdef glVertexAttribI1uiEXT
	_glVertexAttribI1uiEXT = NULL;
#	endif
#	ifdef glVertexAttribI2uiEXT
	_glVertexAttribI2uiEXT = NULL;
#	endif
#	ifdef glVertexAttribI3uiEXT
	_glVertexAttribI3uiEXT = NULL;
#	endif
#	ifdef glVertexAttribI4uiEXT
	_glVertexAttribI4uiEXT = NULL;
#	endif
#	ifdef glVertexAttribI1ivEXT
	_glVertexAttribI1ivEXT = NULL;
#	endif
#	ifdef glVertexAttribI2ivEXT
	_glVertexAttribI2ivEXT = NULL;
#	endif
#	ifdef glVertexAttribI3ivEXT
	_glVertexAttribI3ivEXT = NULL;
#	endif
#	ifdef glVertexAttribI4ivEXT
	_glVertexAttribI4ivEXT = NULL;
#	endif
#	ifdef glVertexAttribI1uivEXT
	_glVertexAttribI1uivEXT = NULL;
#	endif
#	ifdef glVertexAttribI2uivEXT
	_glVertexAttribI2uivEXT = NULL;
#	endif
#	ifdef glVertexAttribI3uivEXT
	_glVertexAttribI3uivEXT = NULL;
#	endif
#	ifdef glVertexAttribI4uivEXT
	_glVertexAttribI4uivEXT = NULL;
#	endif
#	ifdef glVertexAttribI4bvEXT
	_glVertexAttribI4bvEXT = NULL;
#	endif
#	ifdef glVertexAttribI4svEXT
	_glVertexAttribI4svEXT = NULL;
#	endif
#	ifdef glVertexAttribI4ubvEXT
	_glVertexAttribI4ubvEXT = NULL;
#	endif
#	ifdef glVertexAttribI4usvEXT
	_glVertexAttribI4usvEXT = NULL;
#	endif
#	ifdef glVertexAttribIPointerEXT
	_glVertexAttribIPointerEXT = NULL;
#	endif
#	ifdef glGetVertexAttribIivEXT
	_glGetVertexAttribIivEXT = NULL;
#	endif
#	ifdef glGetVertexAttribIuivEXT
	_glGetVertexAttribIuivEXT = NULL;
#	endif
#	ifdef glGetUniformuivEXT
	_glGetUniformuivEXT = NULL;
#	endif
#	ifdef glBindFragDataLocationEXT
	_glBindFragDataLocationEXT = NULL;
#	endif
#	ifdef glGetFragDataLocationEXT
	_glGetFragDataLocationEXT = NULL;
#	endif
#	ifdef glUniform1uiEXT
	_glUniform1uiEXT = NULL;
#	endif
#	ifdef glUniform2uiEXT
	_glUniform2uiEXT = NULL;
#	endif
#	ifdef glUniform3uiEXT
	_glUniform3uiEXT = NULL;
#	endif
#	ifdef glUniform4uiEXT
	_glUniform4uiEXT = NULL;
#	endif
#	ifdef glUniform1uivEXT
	_glUniform1uivEXT = NULL;
#	endif
#	ifdef glUniform2uivEXT
	_glUniform2uivEXT = NULL;
#	endif
#	ifdef glUniform3uivEXT
	_glUniform3uivEXT = NULL;
#	endif
#	ifdef glUniform4uivEXT
	_glUniform4uivEXT = NULL;
#	endif
#	ifdef glDrawArraysInstancedEXT
	_glDrawArraysInstancedEXT = NULL;
#	endif
#	ifdef glDrawElementsInstancedEXT
	_glDrawElementsInstancedEXT = NULL;
#	endif
#	ifdef glTexBufferEXT
	_glTexBufferEXT = NULL;
#	endif
#	ifdef glDepthRangedNV
	_glDepthRangedNV = NULL;
#	endif
#	ifdef glClearDepthdNV
	_glClearDepthdNV = NULL;
#	endif
#	ifdef glDepthBoundsdNV
	_glDepthBoundsdNV = NULL;
#	endif
#	ifdef glRenderbufferStorageMultisampleCoverageNV
	_glRenderbufferStorageMultisampleCoverageNV = NULL;
#	endif
#	ifdef glProgramBufferParametersfvNV
	_glProgramBufferParametersfvNV = NULL;
#	endif
#	ifdef glProgramBufferParametersIivNV
	_glProgramBufferParametersIivNV = NULL;
#	endif
#	ifdef glProgramBufferParametersIuivNV
	_glProgramBufferParametersIuivNV = NULL;
#	endif
#	ifdef glColorMaskIndexedEXT
	_glColorMaskIndexedEXT = NULL;
#	endif
#	ifdef glGetBooleanIndexedvEXT
	_glGetBooleanIndexedvEXT = NULL;
#	endif
#	ifdef glGetIntegerIndexedvEXT
	_glGetIntegerIndexedvEXT = NULL;
#	endif
#	ifdef glEnableIndexedEXT
	_glEnableIndexedEXT = NULL;
#	endif
#	ifdef glDisableIndexedEXT
	_glDisableIndexedEXT = NULL;
#	endif
#	ifdef glIsEnabledIndexedEXT
	_glIsEnabledIndexedEXT = NULL;
#	endif
#	ifdef glBeginTransformFeedbackNV
	_glBeginTransformFeedbackNV = NULL;
#	endif
#	ifdef glEndTransformFeedbackNV
	_glEndTransformFeedbackNV = NULL;
#	endif
#	ifdef glTransformFeedbackAttribsNV
	_glTransformFeedbackAttribsNV = NULL;
#	endif
#	ifdef glBindBufferRangeNV
	_glBindBufferRangeNV = NULL;
#	endif
#	ifdef glBindBufferOffsetNV
	_glBindBufferOffsetNV = NULL;
#	endif
#	ifdef glBindBufferBaseNV
	_glBindBufferBaseNV = NULL;
#	endif
#	ifdef glTransformFeedbackVaryingsNV
	_glTransformFeedbackVaryingsNV = NULL;
#	endif
#	ifdef glActiveVaryingNV
	_glActiveVaryingNV = NULL;
#	endif
#	ifdef glGetVaryingLocationNV
	_glGetVaryingLocationNV = NULL;
#	endif
#	ifdef glGetActiveVaryingNV
	_glGetActiveVaryingNV = NULL;
#	endif
#	ifdef glGetTransformFeedbackVaryingNV
	_glGetTransformFeedbackVaryingNV = NULL;
#	endif
#	ifdef glTransformFeedbackStreamAttribsNV
	_glTransformFeedbackStreamAttribsNV = NULL;
#	endif
#	ifdef glUniformBufferEXT
	_glUniformBufferEXT = NULL;
#	endif
#	ifdef glGetUniformBufferSizeEXT
	_glGetUniformBufferSizeEXT = NULL;
#	endif
#	ifdef glGetUniformOffsetEXT
	_glGetUniformOffsetEXT = NULL;
#	endif
#	ifdef glTexParameterIivEXT
	_glTexParameterIivEXT = NULL;
#	endif
#	ifdef glTexParameterIuivEXT
	_glTexParameterIuivEXT = NULL;
#	endif
#	ifdef glGetTexParameterIivEXT
	_glGetTexParameterIivEXT = NULL;
#	endif
#	ifdef glGetTexParameterIuivEXT
	_glGetTexParameterIuivEXT = NULL;
#	endif
#	ifdef glClearColorIiEXT
	_glClearColorIiEXT = NULL;
#	endif
#	ifdef glClearColorIuiEXT
	_glClearColorIuiEXT = NULL;
#	endif
#	ifdef glFrameTerminatorGREMEDY
	_glFrameTerminatorGREMEDY = NULL;
#	endif
#	ifdef glBeginConditionalRenderNV
	_glBeginConditionalRenderNV = NULL;
#	endif
#	ifdef glEndConditionalRenderNV
	_glEndConditionalRenderNV = NULL;
#	endif
#	ifdef glPresentFrameKeyedNV
	_glPresentFrameKeyedNV = NULL;
#	endif
#	ifdef glPresentFrameDualFillNV
	_glPresentFrameDualFillNV = NULL;
#	endif
#	ifdef glGetVideoivNV
	_glGetVideoivNV = NULL;
#	endif
#	ifdef glGetVideouivNV
	_glGetVideouivNV = NULL;
#	endif
#	ifdef glGetVideoi64vNV
	_glGetVideoi64vNV = NULL;
#	endif
#	ifdef glGetVideoui64vNV
	_glGetVideoui64vNV = NULL;
#	endif
#	ifdef glBeginTransformFeedbackEXT
	_glBeginTransformFeedbackEXT = NULL;
#	endif
#	ifdef glEndTransformFeedbackEXT
	_glEndTransformFeedbackEXT = NULL;
#	endif
#	ifdef glBindBufferRangeEXT
	_glBindBufferRangeEXT = NULL;
#	endif
#	ifdef glBindBufferOffsetEXT
	_glBindBufferOffsetEXT = NULL;
#	endif
#	ifdef glBindBufferBaseEXT
	_glBindBufferBaseEXT = NULL;
#	endif
#	ifdef glTransformFeedbackVaryingsEXT
	_glTransformFeedbackVaryingsEXT = NULL;
#	endif
#	ifdef glGetTransformFeedbackVaryingEXT
	_glGetTransformFeedbackVaryingEXT = NULL;
#	endif
#	ifdef glClientAttribDefaultEXT
	_glClientAttribDefaultEXT = NULL;
#	endif
#	ifdef glPushClientAttribDefaultEXT
	_glPushClientAttribDefaultEXT = NULL;
#	endif
#	ifdef glMatrixLoadfEXT
	_glMatrixLoadfEXT = NULL;
#	endif
#	ifdef glMatrixLoaddEXT
	_glMatrixLoaddEXT = NULL;
#	endif
#	ifdef glMatrixMultfEXT
	_glMatrixMultfEXT = NULL;
#	endif
#	ifdef glMatrixMultdEXT
	_glMatrixMultdEXT = NULL;
#	endif
#	ifdef glMatrixLoadIdentityEXT
	_glMatrixLoadIdentityEXT = NULL;
#	endif
#	ifdef glMatrixRotatefEXT
	_glMatrixRotatefEXT = NULL;
#	endif
#	ifdef glMatrixRotatedEXT
	_glMatrixRotatedEXT = NULL;
#	endif
#	ifdef glMatrixScalefEXT
	_glMatrixScalefEXT = NULL;
#	endif
#	ifdef glMatrixScaledEXT
	_glMatrixScaledEXT = NULL;
#	endif
#	ifdef glMatrixTranslatefEXT
	_glMatrixTranslatefEXT = NULL;
#	endif
#	ifdef glMatrixTranslatedEXT
	_glMatrixTranslatedEXT = NULL;
#	endif
#	ifdef glMatrixFrustumEXT
	_glMatrixFrustumEXT = NULL;
#	endif
#	ifdef glMatrixOrthoEXT
	_glMatrixOrthoEXT = NULL;
#	endif
#	ifdef glMatrixPopEXT
	_glMatrixPopEXT = NULL;
#	endif
#	ifdef glMatrixPushEXT
	_glMatrixPushEXT = NULL;
#	endif
#	ifdef glMatrixLoadTransposefEXT
	_glMatrixLoadTransposefEXT = NULL;
#	endif
#	ifdef glMatrixLoadTransposedEXT
	_glMatrixLoadTransposedEXT = NULL;
#	endif
#	ifdef glMatrixMultTransposefEXT
	_glMatrixMultTransposefEXT = NULL;
#	endif
#	ifdef glMatrixMultTransposedEXT
	_glMatrixMultTransposedEXT = NULL;
#	endif
#	ifdef glTextureParameterfEXT
	_glTextureParameterfEXT = NULL;
#	endif
#	ifdef glTextureParameterfvEXT
	_glTextureParameterfvEXT = NULL;
#	endif
#	ifdef glTextureParameteriEXT
	_glTextureParameteriEXT = NULL;
#	endif
#	ifdef glTextureParameterivEXT
	_glTextureParameterivEXT = NULL;
#	endif
#	ifdef glTextureImage1DEXT
	_glTextureImage1DEXT = NULL;
#	endif
#	ifdef glTextureImage2DEXT
	_glTextureImage2DEXT = NULL;
#	endif
#	ifdef glTextureSubImage1DEXT
	_glTextureSubImage1DEXT = NULL;
#	endif
#	ifdef glTextureSubImage2DEXT
	_glTextureSubImage2DEXT = NULL;
#	endif
#	ifdef glCopyTextureImage1DEXT
	_glCopyTextureImage1DEXT = NULL;
#	endif
#	ifdef glCopyTextureImage2DEXT
	_glCopyTextureImage2DEXT = NULL;
#	endif
#	ifdef glCopyTextureSubImage1DEXT
	_glCopyTextureSubImage1DEXT = NULL;
#	endif
#	ifdef glCopyTextureSubImage2DEXT
	_glCopyTextureSubImage2DEXT = NULL;
#	endif
#	ifdef glGetTextureImageEXT
	_glGetTextureImageEXT = NULL;
#	endif
#	ifdef glGetTextureParameterfvEXT
	_glGetTextureParameterfvEXT = NULL;
#	endif
#	ifdef glGetTextureParameterivEXT
	_glGetTextureParameterivEXT = NULL;
#	endif
#	ifdef glGetTextureLevelParameterfvEXT
	_glGetTextureLevelParameterfvEXT = NULL;
#	endif
#	ifdef glGetTextureLevelParameterivEXT
	_glGetTextureLevelParameterivEXT = NULL;
#	endif
#	ifdef glTextureImage3DEXT
	_glTextureImage3DEXT = NULL;
#	endif
#	ifdef glTextureSubImage3DEXT
	_glTextureSubImage3DEXT = NULL;
#	endif
#	ifdef glCopyTextureSubImage3DEXT
	_glCopyTextureSubImage3DEXT = NULL;
#	endif
#	ifdef glMultiTexParameterfEXT
	_glMultiTexParameterfEXT = NULL;
#	endif
#	ifdef glMultiTexParameterfvEXT
	_glMultiTexParameterfvEXT = NULL;
#	endif
#	ifdef glMultiTexParameteriEXT
	_glMultiTexParameteriEXT = NULL;
#	endif
#	ifdef glMultiTexParameterivEXT
	_glMultiTexParameterivEXT = NULL;
#	endif
#	ifdef glMultiTexImage1DEXT
	_glMultiTexImage1DEXT = NULL;
#	endif
#	ifdef glMultiTexImage2DEXT
	_glMultiTexImage2DEXT = NULL;
#	endif
#	ifdef glMultiTexSubImage1DEXT
	_glMultiTexSubImage1DEXT = NULL;
#	endif
#	ifdef glMultiTexSubImage2DEXT
	_glMultiTexSubImage2DEXT = NULL;
#	endif
#	ifdef glCopyMultiTexImage1DEXT
	_glCopyMultiTexImage1DEXT = NULL;
#	endif
#	ifdef glCopyMultiTexImage2DEXT
	_glCopyMultiTexImage2DEXT = NULL;
#	endif
#	ifdef glCopyMultiTexSubImage1DEXT
	_glCopyMultiTexSubImage1DEXT = NULL;
#	endif
#	ifdef glCopyMultiTexSubImage2DEXT
	_glCopyMultiTexSubImage2DEXT = NULL;
#	endif
#	ifdef glGetMultiTexImageEXT
	_glGetMultiTexImageEXT = NULL;
#	endif
#	ifdef glGetMultiTexParameterfvEXT
	_glGetMultiTexParameterfvEXT = NULL;
#	endif
#	ifdef glGetMultiTexParameterivEXT
	_glGetMultiTexParameterivEXT = NULL;
#	endif
#	ifdef glGetMultiTexLevelParameterfvEXT
	_glGetMultiTexLevelParameterfvEXT = NULL;
#	endif
#	ifdef glGetMultiTexLevelParameterivEXT
	_glGetMultiTexLevelParameterivEXT = NULL;
#	endif
#	ifdef glMultiTexImage3DEXT
	_glMultiTexImage3DEXT = NULL;
#	endif
#	ifdef glMultiTexSubImage3DEXT
	_glMultiTexSubImage3DEXT = NULL;
#	endif
#	ifdef glCopyMultiTexSubImage3DEXT
	_glCopyMultiTexSubImage3DEXT = NULL;
#	endif
#	ifdef glBindMultiTextureEXT
	_glBindMultiTextureEXT = NULL;
#	endif
#	ifdef glEnableClientStateIndexedEXT
	_glEnableClientStateIndexedEXT = NULL;
#	endif
#	ifdef glDisableClientStateIndexedEXT
	_glDisableClientStateIndexedEXT = NULL;
#	endif
#	ifdef glMultiTexCoordPointerEXT
	_glMultiTexCoordPointerEXT = NULL;
#	endif
#	ifdef glMultiTexEnvfEXT
	_glMultiTexEnvfEXT = NULL;
#	endif
#	ifdef glMultiTexEnvfvEXT
	_glMultiTexEnvfvEXT = NULL;
#	endif
#	ifdef glMultiTexEnviEXT
	_glMultiTexEnviEXT = NULL;
#	endif
#	ifdef glMultiTexEnvivEXT
	_glMultiTexEnvivEXT = NULL;
#	endif
#	ifdef glMultiTexGendEXT
	_glMultiTexGendEXT = NULL;
#	endif
#	ifdef glMultiTexGendvEXT
	_glMultiTexGendvEXT = NULL;
#	endif
#	ifdef glMultiTexGenfEXT
	_glMultiTexGenfEXT = NULL;
#	endif
#	ifdef glMultiTexGenfvEXT
	_glMultiTexGenfvEXT = NULL;
#	endif
#	ifdef glMultiTexGeniEXT
	_glMultiTexGeniEXT = NULL;
#	endif
#	ifdef glMultiTexGenivEXT
	_glMultiTexGenivEXT = NULL;
#	endif
#	ifdef glGetMultiTexEnvfvEXT
	_glGetMultiTexEnvfvEXT = NULL;
#	endif
#	ifdef glGetMultiTexEnvivEXT
	_glGetMultiTexEnvivEXT = NULL;
#	endif
#	ifdef glGetMultiTexGendvEXT
	_glGetMultiTexGendvEXT = NULL;
#	endif
#	ifdef glGetMultiTexGenfvEXT
	_glGetMultiTexGenfvEXT = NULL;
#	endif
#	ifdef glGetMultiTexGenivEXT
	_glGetMultiTexGenivEXT = NULL;
#	endif
#	ifdef glGetFloatIndexedvEXT
	_glGetFloatIndexedvEXT = NULL;
#	endif
#	ifdef glGetDoubleIndexedvEXT
	_glGetDoubleIndexedvEXT = NULL;
#	endif
#	ifdef glGetPointerIndexedvEXT
	_glGetPointerIndexedvEXT = NULL;
#	endif
#	ifdef glCompressedTextureImage3DEXT
	_glCompressedTextureImage3DEXT = NULL;
#	endif
#	ifdef glCompressedTextureImage2DEXT
	_glCompressedTextureImage2DEXT = NULL;
#	endif
#	ifdef glCompressedTextureImage1DEXT
	_glCompressedTextureImage1DEXT = NULL;
#	endif
#	ifdef glCompressedTextureSubImage3DEXT
	_glCompressedTextureSubImage3DEXT = NULL;
#	endif
#	ifdef glCompressedTextureSubImage2DEXT
	_glCompressedTextureSubImage2DEXT = NULL;
#	endif
#	ifdef glCompressedTextureSubImage1DEXT
	_glCompressedTextureSubImage1DEXT = NULL;
#	endif
#	ifdef glGetCompressedTextureImageEXT
	_glGetCompressedTextureImageEXT = NULL;
#	endif
#	ifdef glCompressedMultiTexImage3DEXT
	_glCompressedMultiTexImage3DEXT = NULL;
#	endif
#	ifdef glCompressedMultiTexImage2DEXT
	_glCompressedMultiTexImage2DEXT = NULL;
#	endif
#	ifdef glCompressedMultiTexImage1DEXT
	_glCompressedMultiTexImage1DEXT = NULL;
#	endif
#	ifdef glCompressedMultiTexSubImage3DEXT
	_glCompressedMultiTexSubImage3DEXT = NULL;
#	endif
#	ifdef glCompressedMultiTexSubImage2DEXT
	_glCompressedMultiTexSubImage2DEXT = NULL;
#	endif
#	ifdef glCompressedMultiTexSubImage1DEXT
	_glCompressedMultiTexSubImage1DEXT = NULL;
#	endif
#	ifdef glGetCompressedMultiTexImageEXT
	_glGetCompressedMultiTexImageEXT = NULL;
#	endif
#	ifdef glNamedProgramStringEXT
	_glNamedProgramStringEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameter4dEXT
	_glNamedProgramLocalParameter4dEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameter4dvEXT
	_glNamedProgramLocalParameter4dvEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameter4fEXT
	_glNamedProgramLocalParameter4fEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameter4fvEXT
	_glNamedProgramLocalParameter4fvEXT = NULL;
#	endif
#	ifdef glGetNamedProgramLocalParameterdvEXT
	_glGetNamedProgramLocalParameterdvEXT = NULL;
#	endif
#	ifdef glGetNamedProgramLocalParameterfvEXT
	_glGetNamedProgramLocalParameterfvEXT = NULL;
#	endif
#	ifdef glGetNamedProgramivEXT
	_glGetNamedProgramivEXT = NULL;
#	endif
#	ifdef glGetNamedProgramStringEXT
	_glGetNamedProgramStringEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameters4fvEXT
	_glNamedProgramLocalParameters4fvEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameterI4iEXT
	_glNamedProgramLocalParameterI4iEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameterI4ivEXT
	_glNamedProgramLocalParameterI4ivEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParametersI4ivEXT
	_glNamedProgramLocalParametersI4ivEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameterI4uiEXT
	_glNamedProgramLocalParameterI4uiEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParameterI4uivEXT
	_glNamedProgramLocalParameterI4uivEXT = NULL;
#	endif
#	ifdef glNamedProgramLocalParametersI4uivEXT
	_glNamedProgramLocalParametersI4uivEXT = NULL;
#	endif
#	ifdef glGetNamedProgramLocalParameterIivEXT
	_glGetNamedProgramLocalParameterIivEXT = NULL;
#	endif
#	ifdef glGetNamedProgramLocalParameterIuivEXT
	_glGetNamedProgramLocalParameterIuivEXT = NULL;
#	endif
#	ifdef glTextureParameterIivEXT
	_glTextureParameterIivEXT = NULL;
#	endif
#	ifdef glTextureParameterIuivEXT
	_glTextureParameterIuivEXT = NULL;
#	endif
#	ifdef glGetTextureParameterIivEXT
	_glGetTextureParameterIivEXT = NULL;
#	endif
#	ifdef glGetTextureParameterIuivEXT
	_glGetTextureParameterIuivEXT = NULL;
#	endif
#	ifdef glMultiTexParameterIivEXT
	_glMultiTexParameterIivEXT = NULL;
#	endif
#	ifdef glMultiTexParameterIuivEXT
	_glMultiTexParameterIuivEXT = NULL;
#	endif
#	ifdef glGetMultiTexParameterIivEXT
	_glGetMultiTexParameterIivEXT = NULL;
#	endif
#	ifdef glGetMultiTexParameterIuivEXT
	_glGetMultiTexParameterIuivEXT = NULL;
#	endif
#	ifdef glProgramUniform1fEXT
	_glProgramUniform1fEXT = NULL;
#	endif
#	ifdef glProgramUniform2fEXT
	_glProgramUniform2fEXT = NULL;
#	endif
#	ifdef glProgramUniform3fEXT
	_glProgramUniform3fEXT = NULL;
#	endif
#	ifdef glProgramUniform4fEXT
	_glProgramUniform4fEXT = NULL;
#	endif
#	ifdef glProgramUniform1iEXT
	_glProgramUniform1iEXT = NULL;
#	endif
#	ifdef glProgramUniform2iEXT
	_glProgramUniform2iEXT = NULL;
#	endif
#	ifdef glProgramUniform3iEXT
	_glProgramUniform3iEXT = NULL;
#	endif
#	ifdef glProgramUniform4iEXT
	_glProgramUniform4iEXT = NULL;
#	endif
#	ifdef glProgramUniform1fvEXT
	_glProgramUniform1fvEXT = NULL;
#	endif
#	ifdef glProgramUniform2fvEXT
	_glProgramUniform2fvEXT = NULL;
#	endif
#	ifdef glProgramUniform3fvEXT
	_glProgramUniform3fvEXT = NULL;
#	endif
#	ifdef glProgramUniform4fvEXT
	_glProgramUniform4fvEXT = NULL;
#	endif
#	ifdef glProgramUniform1ivEXT
	_glProgramUniform1ivEXT = NULL;
#	endif
#	ifdef glProgramUniform2ivEXT
	_glProgramUniform2ivEXT = NULL;
#	endif
#	ifdef glProgramUniform3ivEXT
	_glProgramUniform3ivEXT = NULL;
#	endif
#	ifdef glProgramUniform4ivEXT
	_glProgramUniform4ivEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix2fvEXT
	_glProgramUniformMatrix2fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix3fvEXT
	_glProgramUniformMatrix3fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix4fvEXT
	_glProgramUniformMatrix4fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x3fvEXT
	_glProgramUniformMatrix2x3fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x2fvEXT
	_glProgramUniformMatrix3x2fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x4fvEXT
	_glProgramUniformMatrix2x4fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x2fvEXT
	_glProgramUniformMatrix4x2fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x4fvEXT
	_glProgramUniformMatrix3x4fvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x3fvEXT
	_glProgramUniformMatrix4x3fvEXT = NULL;
#	endif
#	ifdef glProgramUniform1uiEXT
	_glProgramUniform1uiEXT = NULL;
#	endif
#	ifdef glProgramUniform2uiEXT
	_glProgramUniform2uiEXT = NULL;
#	endif
#	ifdef glProgramUniform3uiEXT
	_glProgramUniform3uiEXT = NULL;
#	endif
#	ifdef glProgramUniform4uiEXT
	_glProgramUniform4uiEXT = NULL;
#	endif
#	ifdef glProgramUniform1uivEXT
	_glProgramUniform1uivEXT = NULL;
#	endif
#	ifdef glProgramUniform2uivEXT
	_glProgramUniform2uivEXT = NULL;
#	endif
#	ifdef glProgramUniform3uivEXT
	_glProgramUniform3uivEXT = NULL;
#	endif
#	ifdef glProgramUniform4uivEXT
	_glProgramUniform4uivEXT = NULL;
#	endif
#	ifdef glNamedBufferDataEXT
	_glNamedBufferDataEXT = NULL;
#	endif
#	ifdef glNamedBufferSubDataEXT
	_glNamedBufferSubDataEXT = NULL;
#	endif
#	ifdef glMapNamedBufferEXT
	_glMapNamedBufferEXT = NULL;
#	endif
#	ifdef glUnmapNamedBufferEXT
	_glUnmapNamedBufferEXT = NULL;
#	endif
#	ifdef glMapNamedBufferRangeEXT
	_glMapNamedBufferRangeEXT = NULL;
#	endif
#	ifdef glFlushMappedNamedBufferRangeEXT
	_glFlushMappedNamedBufferRangeEXT = NULL;
#	endif
#	ifdef glNamedCopyBufferSubDataEXT
	_glNamedCopyBufferSubDataEXT = NULL;
#	endif
#	ifdef glGetNamedBufferParameterivEXT
	_glGetNamedBufferParameterivEXT = NULL;
#	endif
#	ifdef glGetNamedBufferPointervEXT
	_glGetNamedBufferPointervEXT = NULL;
#	endif
#	ifdef glGetNamedBufferSubDataEXT
	_glGetNamedBufferSubDataEXT = NULL;
#	endif
#	ifdef glTextureBufferEXT
	_glTextureBufferEXT = NULL;
#	endif
#	ifdef glMultiTexBufferEXT
	_glMultiTexBufferEXT = NULL;
#	endif
#	ifdef glNamedRenderbufferStorageEXT
	_glNamedRenderbufferStorageEXT = NULL;
#	endif
#	ifdef glGetNamedRenderbufferParameterivEXT
	_glGetNamedRenderbufferParameterivEXT = NULL;
#	endif
#	ifdef glCheckNamedFramebufferStatusEXT
	_glCheckNamedFramebufferStatusEXT = NULL;
#	endif
#	ifdef glNamedFramebufferTexture1DEXT
	_glNamedFramebufferTexture1DEXT = NULL;
#	endif
#	ifdef glNamedFramebufferTexture2DEXT
	_glNamedFramebufferTexture2DEXT = NULL;
#	endif
#	ifdef glNamedFramebufferTexture3DEXT
	_glNamedFramebufferTexture3DEXT = NULL;
#	endif
#	ifdef glNamedFramebufferRenderbufferEXT
	_glNamedFramebufferRenderbufferEXT = NULL;
#	endif
#	ifdef glGetNamedFramebufferAttachmentParameterivEXT
	_glGetNamedFramebufferAttachmentParameterivEXT = NULL;
#	endif
#	ifdef glGenerateTextureMipmapEXT
	_glGenerateTextureMipmapEXT = NULL;
#	endif
#	ifdef glGenerateMultiTexMipmapEXT
	_glGenerateMultiTexMipmapEXT = NULL;
#	endif
#	ifdef glFramebufferDrawBufferEXT
	_glFramebufferDrawBufferEXT = NULL;
#	endif
#	ifdef glFramebufferDrawBuffersEXT
	_glFramebufferDrawBuffersEXT = NULL;
#	endif
#	ifdef glFramebufferReadBufferEXT
	_glFramebufferReadBufferEXT = NULL;
#	endif
#	ifdef glGetFramebufferParameterivEXT
	_glGetFramebufferParameterivEXT = NULL;
#	endif
#	ifdef glNamedRenderbufferStorageMultisampleEXT
	_glNamedRenderbufferStorageMultisampleEXT = NULL;
#	endif
#	ifdef glNamedRenderbufferStorageMultisampleCoverageEXT
	_glNamedRenderbufferStorageMultisampleCoverageEXT = NULL;
#	endif
#	ifdef glNamedFramebufferTextureEXT
	_glNamedFramebufferTextureEXT = NULL;
#	endif
#	ifdef glNamedFramebufferTextureLayerEXT
	_glNamedFramebufferTextureLayerEXT = NULL;
#	endif
#	ifdef glNamedFramebufferTextureFaceEXT
	_glNamedFramebufferTextureFaceEXT = NULL;
#	endif
#	ifdef glTextureRenderbufferEXT
	_glTextureRenderbufferEXT = NULL;
#	endif
#	ifdef glMultiTexRenderbufferEXT
	_glMultiTexRenderbufferEXT = NULL;
#	endif
#	ifdef glProgramUniform1dEXT
	_glProgramUniform1dEXT = NULL;
#	endif
#	ifdef glProgramUniform2dEXT
	_glProgramUniform2dEXT = NULL;
#	endif
#	ifdef glProgramUniform3dEXT
	_glProgramUniform3dEXT = NULL;
#	endif
#	ifdef glProgramUniform4dEXT
	_glProgramUniform4dEXT = NULL;
#	endif
#	ifdef glProgramUniform1dvEXT
	_glProgramUniform1dvEXT = NULL;
#	endif
#	ifdef glProgramUniform2dvEXT
	_glProgramUniform2dvEXT = NULL;
#	endif
#	ifdef glProgramUniform3dvEXT
	_glProgramUniform3dvEXT = NULL;
#	endif
#	ifdef glProgramUniform4dvEXT
	_glProgramUniform4dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix2dvEXT
	_glProgramUniformMatrix2dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix3dvEXT
	_glProgramUniformMatrix3dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix4dvEXT
	_glProgramUniformMatrix4dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x3dvEXT
	_glProgramUniformMatrix2x3dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix2x4dvEXT
	_glProgramUniformMatrix2x4dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x2dvEXT
	_glProgramUniformMatrix3x2dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix3x4dvEXT
	_glProgramUniformMatrix3x4dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x2dvEXT
	_glProgramUniformMatrix4x2dvEXT = NULL;
#	endif
#	ifdef glProgramUniformMatrix4x3dvEXT
	_glProgramUniformMatrix4x3dvEXT = NULL;
#	endif
#	ifdef glGetMultisamplefvNV
	_glGetMultisamplefvNV = NULL;
#	endif
#	ifdef glSampleMaskIndexedNV
	_glSampleMaskIndexedNV = NULL;
#	endif
#	ifdef glTexRenderbufferNV
	_glTexRenderbufferNV = NULL;
#	endif
#	ifdef glBindTransformFeedbackNV
	_glBindTransformFeedbackNV = NULL;
#	endif
#	ifdef glDeleteTransformFeedbacksNV
	_glDeleteTransformFeedbacksNV = NULL;
#	endif
#	ifdef glGenTransformFeedbacksNV
	_glGenTransformFeedbacksNV = NULL;
#	endif
#	ifdef glIsTransformFeedbackNV
	_glIsTransformFeedbackNV = NULL;
#	endif
#	ifdef glPauseTransformFeedbackNV
	_glPauseTransformFeedbackNV = NULL;
#	endif
#	ifdef glResumeTransformFeedbackNV
	_glResumeTransformFeedbackNV = NULL;
#	endif
#	ifdef glDrawTransformFeedbackNV
	_glDrawTransformFeedbackNV = NULL;
#	endif
#	ifdef glGetPerfMonitorGroupsAMD
	_glGetPerfMonitorGroupsAMD = NULL;
#	endif
#	ifdef glGetPerfMonitorCountersAMD
	_glGetPerfMonitorCountersAMD = NULL;
#	endif
#	ifdef glGetPerfMonitorGroupStringAMD
	_glGetPerfMonitorGroupStringAMD = NULL;
#	endif
#	ifdef glGetPerfMonitorCounterStringAMD
	_glGetPerfMonitorCounterStringAMD = NULL;
#	endif
#	ifdef glGetPerfMonitorCounterInfoAMD
	_glGetPerfMonitorCounterInfoAMD = NULL;
#	endif
#	ifdef glGenPerfMonitorsAMD
	_glGenPerfMonitorsAMD = NULL;
#	endif
#	ifdef glDeletePerfMonitorsAMD
	_glDeletePerfMonitorsAMD = NULL;
#	endif
#	ifdef glSelectPerfMonitorCountersAMD
	_glSelectPerfMonitorCountersAMD = NULL;
#	endif
#	ifdef glBeginPerfMonitorAMD
	_glBeginPerfMonitorAMD = NULL;
#	endif
#	ifdef glEndPerfMonitorAMD
	_glEndPerfMonitorAMD = NULL;
#	endif
#	ifdef glGetPerfMonitorCounterDataAMD
	_glGetPerfMonitorCounterDataAMD = NULL;
#	endif
#	ifdef glTessellationFactorAMD
	_glTessellationFactorAMD = NULL;
#	endif
#	ifdef glTessellationModeAMD
	_glTessellationModeAMD = NULL;
#	endif
#	ifdef glProvokingVertexEXT
	_glProvokingVertexEXT = NULL;
#	endif
#	ifdef glBlendFuncIndexedAMD
	_glBlendFuncIndexedAMD = NULL;
#	endif
#	ifdef glBlendFuncSeparateIndexedAMD
	_glBlendFuncSeparateIndexedAMD = NULL;
#	endif
#	ifdef glBlendEquationIndexedAMD
	_glBlendEquationIndexedAMD = NULL;
#	endif
#	ifdef glBlendEquationSeparateIndexedAMD
	_glBlendEquationSeparateIndexedAMD = NULL;
#	endif
#	ifdef glTextureRangeAPPLE
	_glTextureRangeAPPLE = NULL;
#	endif
#	ifdef glGetTexParameterPointervAPPLE
	_glGetTexParameterPointervAPPLE = NULL;
#	endif
#	ifdef glEnableVertexAttribAPPLE
	_glEnableVertexAttribAPPLE = NULL;
#	endif
#	ifdef glDisableVertexAttribAPPLE
	_glDisableVertexAttribAPPLE = NULL;
#	endif
#	ifdef glIsVertexAttribEnabledAPPLE
	_glIsVertexAttribEnabledAPPLE = NULL;
#	endif
#	ifdef glMapVertexAttrib1dAPPLE
	_glMapVertexAttrib1dAPPLE = NULL;
#	endif
#	ifdef glMapVertexAttrib1fAPPLE
	_glMapVertexAttrib1fAPPLE = NULL;
#	endif
#	ifdef glMapVertexAttrib2dAPPLE
	_glMapVertexAttrib2dAPPLE = NULL;
#	endif
#	ifdef glMapVertexAttrib2fAPPLE
	_glMapVertexAttrib2fAPPLE = NULL;
#	endif
#	ifdef glObjectPurgeableAPPLE
	_glObjectPurgeableAPPLE = NULL;
#	endif
#	ifdef glObjectUnpurgeableAPPLE
	_glObjectUnpurgeableAPPLE = NULL;
#	endif
#	ifdef glGetObjectParameterivAPPLE
	_glGetObjectParameterivAPPLE = NULL;
#	endif
#	ifdef glBeginVideoCaptureNV
	_glBeginVideoCaptureNV = NULL;
#	endif
#	ifdef glBindVideoCaptureStreamBufferNV
	_glBindVideoCaptureStreamBufferNV = NULL;
#	endif
#	ifdef glBindVideoCaptureStreamTextureNV
	_glBindVideoCaptureStreamTextureNV = NULL;
#	endif
#	ifdef glEndVideoCaptureNV
	_glEndVideoCaptureNV = NULL;
#	endif
#	ifdef glGetVideoCaptureivNV
	_glGetVideoCaptureivNV = NULL;
#	endif
#	ifdef glGetVideoCaptureStreamivNV
	_glGetVideoCaptureStreamivNV = NULL;
#	endif
#	ifdef glGetVideoCaptureStreamfvNV
	_glGetVideoCaptureStreamfvNV = NULL;
#	endif
#	ifdef glGetVideoCaptureStreamdvNV
	_glGetVideoCaptureStreamdvNV = NULL;
#	endif
#	ifdef glVideoCaptureNV
	_glVideoCaptureNV = NULL;
#	endif
#	ifdef glVideoCaptureStreamParameterivNV
	_glVideoCaptureStreamParameterivNV = NULL;
#	endif
#	ifdef glVideoCaptureStreamParameterfvNV
	_glVideoCaptureStreamParameterfvNV = NULL;
#	endif
#	ifdef glVideoCaptureStreamParameterdvNV
	_glVideoCaptureStreamParameterdvNV = NULL;
#	endif
#	ifdef glCopyImageSubDataNV
	_glCopyImageSubDataNV = NULL;
#	endif
#	ifdef glUseShaderProgramEXT
	_glUseShaderProgramEXT = NULL;
#	endif
#	ifdef glActiveProgramEXT
	_glActiveProgramEXT = NULL;
#	endif
#	ifdef glCreateShaderProgramEXT
	_glCreateShaderProgramEXT = NULL;
#	endif
#	ifdef glMakeBufferResidentNV
	_glMakeBufferResidentNV = NULL;
#	endif
#	ifdef glMakeBufferNonResidentNV
	_glMakeBufferNonResidentNV = NULL;
#	endif
#	ifdef glIsBufferResidentNV
	_glIsBufferResidentNV = NULL;
#	endif
#	ifdef glMakeNamedBufferResidentNV
	_glMakeNamedBufferResidentNV = NULL;
#	endif
#	ifdef glMakeNamedBufferNonResidentNV
	_glMakeNamedBufferNonResidentNV = NULL;
#	endif
#	ifdef glIsNamedBufferResidentNV
	_glIsNamedBufferResidentNV = NULL;
#	endif
#	ifdef glGetBufferParameterui64vNV
	_glGetBufferParameterui64vNV = NULL;
#	endif
#	ifdef glGetNamedBufferParameterui64vNV
	_glGetNamedBufferParameterui64vNV = NULL;
#	endif
#	ifdef glGetIntegerui64vNV
	_glGetIntegerui64vNV = NULL;
#	endif
#	ifdef glUniformui64NV
	_glUniformui64NV = NULL;
#	endif
#	ifdef glUniformui64vNV
	_glUniformui64vNV = NULL;
#	endif
#	ifdef glGetUniformui64vNV
	_glGetUniformui64vNV = NULL;
#	endif
#	ifdef glProgramUniformui64NV
	_glProgramUniformui64NV = NULL;
#	endif
#	ifdef glProgramUniformui64vNV
	_glProgramUniformui64vNV = NULL;
#	endif
#	ifdef glBufferAddressRangeNV
	_glBufferAddressRangeNV = NULL;
#	endif
#	ifdef glVertexFormatNV
	_glVertexFormatNV = NULL;
#	endif
#	ifdef glNormalFormatNV
	_glNormalFormatNV = NULL;
#	endif
#	ifdef glColorFormatNV
	_glColorFormatNV = NULL;
#	endif
#	ifdef glIndexFormatNV
	_glIndexFormatNV = NULL;
#	endif
#	ifdef glTexCoordFormatNV
	_glTexCoordFormatNV = NULL;
#	endif
#	ifdef glEdgeFlagFormatNV
	_glEdgeFlagFormatNV = NULL;
#	endif
#	ifdef glSecondaryColorFormatNV
	_glSecondaryColorFormatNV = NULL;
#	endif
#	ifdef glFogCoordFormatNV
	_glFogCoordFormatNV = NULL;
#	endif
#	ifdef glVertexAttribFormatNV
	_glVertexAttribFormatNV = NULL;
#	endif
#	ifdef glVertexAttribIFormatNV
	_glVertexAttribIFormatNV = NULL;
#	endif
#	ifdef glGetIntegerui64i_vNV
	_glGetIntegerui64i_vNV = NULL;
#	endif
#	ifdef glTextureBarrierNV
	_glTextureBarrierNV = NULL;
#	endif
#	ifdef glBindImageTextureEXT
	_glBindImageTextureEXT = NULL;
#	endif
#	ifdef glMemoryBarrierEXT
	_glMemoryBarrierEXT = NULL;
#	endif
#	ifdef glVertexAttribL1dEXT
	_glVertexAttribL1dEXT = NULL;
#	endif
#	ifdef glVertexAttribL2dEXT
	_glVertexAttribL2dEXT = NULL;
#	endif
#	ifdef glVertexAttribL3dEXT
	_glVertexAttribL3dEXT = NULL;
#	endif
#	ifdef glVertexAttribL4dEXT
	_glVertexAttribL4dEXT = NULL;
#	endif
#	ifdef glVertexAttribL1dvEXT
	_glVertexAttribL1dvEXT = NULL;
#	endif
#	ifdef glVertexAttribL2dvEXT
	_glVertexAttribL2dvEXT = NULL;
#	endif
#	ifdef glVertexAttribL3dvEXT
	_glVertexAttribL3dvEXT = NULL;
#	endif
#	ifdef glVertexAttribL4dvEXT
	_glVertexAttribL4dvEXT = NULL;
#	endif
#	ifdef glVertexAttribLPointerEXT
	_glVertexAttribLPointerEXT = NULL;
#	endif
#	ifdef glGetVertexAttribLdvEXT
	_glGetVertexAttribLdvEXT = NULL;
#	endif
#	ifdef glVertexArrayVertexAttribLOffsetEXT
	_glVertexArrayVertexAttribLOffsetEXT = NULL;
#	endif
#	ifdef glProgramSubroutineParametersuivNV
	_glProgramSubroutineParametersuivNV = NULL;
#	endif
#	ifdef glGetProgramSubroutineParameteruivNV
	_glGetProgramSubroutineParameteruivNV = NULL;
#	endif
#	ifdef glUniform1i64NV
	_glUniform1i64NV = NULL;
#	endif
#	ifdef glUniform2i64NV
	_glUniform2i64NV = NULL;
#	endif
#	ifdef glUniform3i64NV
	_glUniform3i64NV = NULL;
#	endif
#	ifdef glUniform4i64NV
	_glUniform4i64NV = NULL;
#	endif
#	ifdef glUniform1i64vNV
	_glUniform1i64vNV = NULL;
#	endif
#	ifdef glUniform2i64vNV
	_glUniform2i64vNV = NULL;
#	endif
#	ifdef glUniform3i64vNV
	_glUniform3i64vNV = NULL;
#	endif
#	ifdef glUniform4i64vNV
	_glUniform4i64vNV = NULL;
#	endif
#	ifdef glUniform1ui64NV
	_glUniform1ui64NV = NULL;
#	endif
#	ifdef glUniform2ui64NV
	_glUniform2ui64NV = NULL;
#	endif
#	ifdef glUniform3ui64NV
	_glUniform3ui64NV = NULL;
#	endif
#	ifdef glUniform4ui64NV
	_glUniform4ui64NV = NULL;
#	endif
#	ifdef glUniform1ui64vNV
	_glUniform1ui64vNV = NULL;
#	endif
#	ifdef glUniform2ui64vNV
	_glUniform2ui64vNV = NULL;
#	endif
#	ifdef glUniform3ui64vNV
	_glUniform3ui64vNV = NULL;
#	endif
#	ifdef glUniform4ui64vNV
	_glUniform4ui64vNV = NULL;
#	endif
#	ifdef glGetUniformi64vNV
	_glGetUniformi64vNV = NULL;
#	endif
#	ifdef glProgramUniform1i64NV
	_glProgramUniform1i64NV = NULL;
#	endif
#	ifdef glProgramUniform2i64NV
	_glProgramUniform2i64NV = NULL;
#	endif
#	ifdef glProgramUniform3i64NV
	_glProgramUniform3i64NV = NULL;
#	endif
#	ifdef glProgramUniform4i64NV
	_glProgramUniform4i64NV = NULL;
#	endif
#	ifdef glProgramUniform1i64vNV
	_glProgramUniform1i64vNV = NULL;
#	endif
#	ifdef glProgramUniform2i64vNV
	_glProgramUniform2i64vNV = NULL;
#	endif
#	ifdef glProgramUniform3i64vNV
	_glProgramUniform3i64vNV = NULL;
#	endif
#	ifdef glProgramUniform4i64vNV
	_glProgramUniform4i64vNV = NULL;
#	endif
#	ifdef glProgramUniform1ui64NV
	_glProgramUniform1ui64NV = NULL;
#	endif
#	ifdef glProgramUniform2ui64NV
	_glProgramUniform2ui64NV = NULL;
#	endif
#	ifdef glProgramUniform3ui64NV
	_glProgramUniform3ui64NV = NULL;
#	endif
#	ifdef glProgramUniform4ui64NV
	_glProgramUniform4ui64NV = NULL;
#	endif
#	ifdef glProgramUniform1ui64vNV
	_glProgramUniform1ui64vNV = NULL;
#	endif
#	ifdef glProgramUniform2ui64vNV
	_glProgramUniform2ui64vNV = NULL;
#	endif
#	ifdef glProgramUniform3ui64vNV
	_glProgramUniform3ui64vNV = NULL;
#	endif
#	ifdef glProgramUniform4ui64vNV
	_glProgramUniform4ui64vNV = NULL;
#	endif
#	ifdef glVertexAttribL1i64NV
	_glVertexAttribL1i64NV = NULL;
#	endif
#	ifdef glVertexAttribL2i64NV
	_glVertexAttribL2i64NV = NULL;
#	endif
#	ifdef glVertexAttribL3i64NV
	_glVertexAttribL3i64NV = NULL;
#	endif
#	ifdef glVertexAttribL4i64NV
	_glVertexAttribL4i64NV = NULL;
#	endif
#	ifdef glVertexAttribL1i64vNV
	_glVertexAttribL1i64vNV = NULL;
#	endif
#	ifdef glVertexAttribL2i64vNV
	_glVertexAttribL2i64vNV = NULL;
#	endif
#	ifdef glVertexAttribL3i64vNV
	_glVertexAttribL3i64vNV = NULL;
#	endif
#	ifdef glVertexAttribL4i64vNV
	_glVertexAttribL4i64vNV = NULL;
#	endif
#	ifdef glVertexAttribL1ui64NV
	_glVertexAttribL1ui64NV = NULL;
#	endif
#	ifdef glVertexAttribL2ui64NV
	_glVertexAttribL2ui64NV = NULL;
#	endif
#	ifdef glVertexAttribL3ui64NV
	_glVertexAttribL3ui64NV = NULL;
#	endif
#	ifdef glVertexAttribL4ui64NV
	_glVertexAttribL4ui64NV = NULL;
#	endif
#	ifdef glVertexAttribL1ui64vNV
	_glVertexAttribL1ui64vNV = NULL;
#	endif
#	ifdef glVertexAttribL2ui64vNV
	_glVertexAttribL2ui64vNV = NULL;
#	endif
#	ifdef glVertexAttribL3ui64vNV
	_glVertexAttribL3ui64vNV = NULL;
#	endif
#	ifdef glVertexAttribL4ui64vNV
	_glVertexAttribL4ui64vNV = NULL;
#	endif
#	ifdef glGetVertexAttribLi64vNV
	_glGetVertexAttribLi64vNV = NULL;
#	endif
#	ifdef glGetVertexAttribLui64vNV
	_glGetVertexAttribLui64vNV = NULL;
#	endif
#	ifdef glVertexAttribLFormatNV
	_glVertexAttribLFormatNV = NULL;
#	endif
#	ifdef glGenNamesAMD
	_glGenNamesAMD = NULL;
#	endif
#	ifdef glDeleteNamesAMD
	_glDeleteNamesAMD = NULL;
#	endif
#	ifdef glIsNameAMD
	_glIsNameAMD = NULL;
#	endif
#	ifdef glDebugMessageEnableAMD
	_glDebugMessageEnableAMD = NULL;
#	endif
#	ifdef glDebugMessageInsertAMD
	_glDebugMessageInsertAMD = NULL;
#	endif
#	ifdef glDebugMessageCallbackAMD
	_glDebugMessageCallbackAMD = NULL;
#	endif
#	ifdef glGetDebugMessageLogAMD
	_glGetDebugMessageLogAMD = NULL;
#	endif
#	ifdef glVDPAUInitNV
	_glVDPAUInitNV = NULL;
#	endif
#	ifdef glVDPAUFiniNV
	_glVDPAUFiniNV = NULL;
#	endif
#	ifdef glVDPAURegisterVideoSurfaceNV
	_glVDPAURegisterVideoSurfaceNV = NULL;
#	endif
#	ifdef glVDPAURegisterOutputSurfaceNV
	_glVDPAURegisterOutputSurfaceNV = NULL;
#	endif
#	ifdef glVDPAUIsSurfaceNV
	_glVDPAUIsSurfaceNV = NULL;
#	endif
#	ifdef glVDPAUUnregisterSurfaceNV
	_glVDPAUUnregisterSurfaceNV = NULL;
#	endif
#	ifdef glVDPAUGetSurfaceivNV
	_glVDPAUGetSurfaceivNV = NULL;
#	endif
#	ifdef glVDPAUSurfaceAccessNV
	_glVDPAUSurfaceAccessNV = NULL;
#	endif
#	ifdef glVDPAUMapSurfacesNV
	_glVDPAUMapSurfacesNV = NULL;
#	endif
#	ifdef glVDPAUUnmapSurfacesNV
	_glVDPAUUnmapSurfacesNV = NULL;
#	endif
#	ifdef glTexImage2DMultisampleCoverageNV
	_glTexImage2DMultisampleCoverageNV = NULL;
#	endif
#	ifdef glTexImage3DMultisampleCoverageNV
	_glTexImage3DMultisampleCoverageNV = NULL;
#	endif
#	ifdef glTextureImage2DMultisampleNV
	_glTextureImage2DMultisampleNV = NULL;
#	endif
#	ifdef glTextureImage3DMultisampleNV
	_glTextureImage3DMultisampleNV = NULL;
#	endif
#	ifdef glTextureImage2DMultisampleCoverageNV
	_glTextureImage2DMultisampleCoverageNV = NULL;
#	endif
#	ifdef glTextureImage3DMultisampleCoverageNV
	_glTextureImage3DMultisampleCoverageNV = NULL;
#	endif
#	ifdef glSetMultisamplefvAMD
	_glSetMultisamplefvAMD = NULL;
#	endif
#	ifdef glImportSyncEXT
	_glImportSyncEXT = NULL;
#	endif
#	ifdef glMultiDrawArraysIndirectAMD
	_glMultiDrawArraysIndirectAMD = NULL;
#	endif
#	ifdef glMultiDrawElementsIndirectAMD
	_glMultiDrawElementsIndirectAMD = NULL;
#	endif
#	ifdef glGenPathsNV
	_glGenPathsNV = NULL;
#	endif
#	ifdef glDeletePathsNV
	_glDeletePathsNV = NULL;
#	endif
#	ifdef glIsPathNV
	_glIsPathNV = NULL;
#	endif
#	ifdef glPathCommandsNV
	_glPathCommandsNV = NULL;
#	endif
#	ifdef glPathCoordsNV
	_glPathCoordsNV = NULL;
#	endif
#	ifdef glPathSubCommandsNV
	_glPathSubCommandsNV = NULL;
#	endif
#	ifdef glPathSubCoordsNV
	_glPathSubCoordsNV = NULL;
#	endif
#	ifdef glPathStringNV
	_glPathStringNV = NULL;
#	endif
#	ifdef glPathGlyphsNV
	_glPathGlyphsNV = NULL;
#	endif
#	ifdef glPathGlyphRangeNV
	_glPathGlyphRangeNV = NULL;
#	endif
#	ifdef glWeightPathsNV
	_glWeightPathsNV = NULL;
#	endif
#	ifdef glCopyPathNV
	_glCopyPathNV = NULL;
#	endif
#	ifdef glInterpolatePathsNV
	_glInterpolatePathsNV = NULL;
#	endif
#	ifdef glTransformPathNV
	_glTransformPathNV = NULL;
#	endif
#	ifdef glPathParameterivNV
	_glPathParameterivNV = NULL;
#	endif
#	ifdef glPathParameteriNV
	_glPathParameteriNV = NULL;
#	endif
#	ifdef glPathParameterfvNV
	_glPathParameterfvNV = NULL;
#	endif
#	ifdef glPathParameterfNV
	_glPathParameterfNV = NULL;
#	endif
#	ifdef glPathDashArrayNV
	_glPathDashArrayNV = NULL;
#	endif
#	ifdef glPathStencilFuncNV
	_glPathStencilFuncNV = NULL;
#	endif
#	ifdef glPathStencilDepthOffsetNV
	_glPathStencilDepthOffsetNV = NULL;
#	endif
#	ifdef glStencilFillPathNV
	_glStencilFillPathNV = NULL;
#	endif
#	ifdef glStencilStrokePathNV
	_glStencilStrokePathNV = NULL;
#	endif
#	ifdef glStencilFillPathInstancedNV
	_glStencilFillPathInstancedNV = NULL;
#	endif
#	ifdef glStencilStrokePathInstancedNV
	_glStencilStrokePathInstancedNV = NULL;
#	endif
#	ifdef glPathCoverDepthFuncNV
	_glPathCoverDepthFuncNV = NULL;
#	endif
#	ifdef glPathColorGenNV
	_glPathColorGenNV = NULL;
#	endif
#	ifdef glPathTexGenNV
	_glPathTexGenNV = NULL;
#	endif
#	ifdef glPathFogGenNV
	_glPathFogGenNV = NULL;
#	endif
#	ifdef glCoverFillPathNV
	_glCoverFillPathNV = NULL;
#	endif
#	ifdef glCoverStrokePathNV
	_glCoverStrokePathNV = NULL;
#	endif
#	ifdef glCoverFillPathInstancedNV
	_glCoverFillPathInstancedNV = NULL;
#	endif
#	ifdef glCoverStrokePathInstancedNV
	_glCoverStrokePathInstancedNV = NULL;
#	endif
#	ifdef glGetPathParameterivNV
	_glGetPathParameterivNV = NULL;
#	endif
#	ifdef glGetPathParameterfvNV
	_glGetPathParameterfvNV = NULL;
#	endif
#	ifdef glGetPathCommandsNV
	_glGetPathCommandsNV = NULL;
#	endif
#	ifdef glGetPathCoordsNV
	_glGetPathCoordsNV = NULL;
#	endif
#	ifdef glGetPathDashArrayNV
	_glGetPathDashArrayNV = NULL;
#	endif
#	ifdef glGetPathMetricsNV
	_glGetPathMetricsNV = NULL;
#	endif
#	ifdef glGetPathMetricRangeNV
	_glGetPathMetricRangeNV = NULL;
#	endif
#	ifdef glGetPathSpacingNV
	_glGetPathSpacingNV = NULL;
#	endif
#	ifdef glGetPathColorGenivNV
	_glGetPathColorGenivNV = NULL;
#	endif
#	ifdef glGetPathColorGenfvNV
	_glGetPathColorGenfvNV = NULL;
#	endif
#	ifdef glGetPathTexGenivNV
	_glGetPathTexGenivNV = NULL;
#	endif
#	ifdef glGetPathTexGenfvNV
	_glGetPathTexGenfvNV = NULL;
#	endif
#	ifdef glIsPointInFillPathNV
	_glIsPointInFillPathNV = NULL;
#	endif
#	ifdef glIsPointInStrokePathNV
	_glIsPointInStrokePathNV = NULL;
#	endif
#	ifdef glGetPathLengthNV
	_glGetPathLengthNV = NULL;
#	endif
#	ifdef glPointAlongPathNV
	_glPointAlongPathNV = NULL;
#	endif
#	ifdef glStencilOpValueAMD
	_glStencilOpValueAMD = NULL;
#	endif
#	ifdef glGetTextureHandleNV
	_glGetTextureHandleNV = NULL;
#	endif
#	ifdef glGetTextureSamplerHandleNV
	_glGetTextureSamplerHandleNV = NULL;
#	endif
#	ifdef glMakeTextureHandleResidentNV
	_glMakeTextureHandleResidentNV = NULL;
#	endif
#	ifdef glMakeTextureHandleNonResidentNV
	_glMakeTextureHandleNonResidentNV = NULL;
#	endif
#	ifdef glGetImageHandleNV
	_glGetImageHandleNV = NULL;
#	endif
#	ifdef glMakeImageHandleResidentNV
	_glMakeImageHandleResidentNV = NULL;
#	endif
#	ifdef glMakeImageHandleNonResidentNV
	_glMakeImageHandleNonResidentNV = NULL;
#	endif
#	ifdef glUniformHandleui64NV
	_glUniformHandleui64NV = NULL;
#	endif
#	ifdef glUniformHandleui64vNV
	_glUniformHandleui64vNV = NULL;
#	endif
#	ifdef glProgramUniformHandleui64NV
	_glProgramUniformHandleui64NV = NULL;
#	endif
#	ifdef glProgramUniformHandleui64vNV
	_glProgramUniformHandleui64vNV = NULL;
#	endif
#	ifdef glIsTextureHandleResidentNV
	_glIsTextureHandleResidentNV = NULL;
#	endif
#	ifdef glIsImageHandleResidentNV
	_glIsImageHandleResidentNV = NULL;
#	endif
#	ifdef glTexStorageSparseAMD
	_glTexStorageSparseAMD = NULL;
#	endif
#	ifdef glTextureStorageSparseAMD
	_glTextureStorageSparseAMD = NULL;
#	endif
}

#endif
