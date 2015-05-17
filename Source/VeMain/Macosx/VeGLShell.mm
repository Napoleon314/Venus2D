////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeGLShell.mm
//  Version:     v1.00
//  Created:     17/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#import "VeGLShell.h"
#include "VeMainPCH.h"

@implementation VeGLView

static CVReturn VeDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    g_pApplication->Update();
    [(VeGLView*)displayLinkContext drawView];
    return kCVReturnSuccess;
}

- (id) initWithFrame:(NSRect)frameRect
{
    NSOpenGLPixelFormatAttribute kAttribs[] =
    {
        kCGLPFAAccelerated,
		kCGLPFANoRecovery,
		kCGLPFADoubleBuffer,
		kCGLPFAColorSize, 24,
        kCGLPFAAlphaSize, 8,
		kCGLPFADepthSize, 24,
        kCGLPFAStencilSize, 8,
		0
    };
    
    m_pkPixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:kAttribs];
    VE_ASSERT(m_pkPixelFormat);
    m_pkGLContext = [[NSOpenGLContext alloc] initWithFormat:m_pkPixelFormat shareContext:nil];
    
    if(self = [super initWithFrame:frameRect])
    {
        VeInit();
        
		[m_pkGLContext makeCurrentContext];
        GLint iSwapInt = 1;
		[m_pkGLContext setValues:&iSwapInt forParameter:NSOpenGLCPSwapInterval];
		
		CVDisplayLinkCreateWithActiveCGDisplays(&m_hDisplayLink);
        CVDisplayLinkSetOutputCallback(m_hDisplayLink, &VeDisplayLinkCallback, self);
        CGLContextObj pkCglContext = (CGLContextObj)[m_pkGLContext CGLContextObj];
        CGLPixelFormatObj pkCglPixelFormat = (CGLPixelFormatObj)[m_pkPixelFormat CGLPixelFormatObj];
        CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(m_hDisplayLink, pkCglContext, pkCglPixelFormat);
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(reshape)
                                                     name:NSViewGlobalFrameDidChangeNotification
                                                   object:self];
        
        g_pRenderer->Init();
        g_pApplication->Init();
        
        [self startAnimation];
    }
    
	return self;
}

- (void) lockFocus
{
	[super lockFocus];
	if([m_pkGLContext view] != self) [m_pkGLContext setView:self];
}

- (void) reshape
{
    CGLLockContext((CGLContextObj)[m_pkGLContext CGLContextObj]);
    [m_pkGLContext update];
	CGLUnlockContext((CGLContextObj)[m_pkGLContext CGLContextObj]);
}

- (void) drawRect:(NSRect)dirtyRect
{
    if(!CVDisplayLinkIsRunning(m_hDisplayLink)) [self drawView];
}

- (void) drawView
{
	CGLLockContext((CGLContextObj)[m_pkGLContext CGLContextObj]);
	[m_pkGLContext makeCurrentContext];
    g_pApplication->Render();
	[m_pkGLContext flushBuffer];
	CGLUnlockContext((CGLContextObj)[m_pkGLContext CGLContextObj]);
}

- (void) startAnimation
{
    if(m_hDisplayLink && !CVDisplayLinkIsRunning(m_hDisplayLink)) CVDisplayLinkStart(m_hDisplayLink);
}

- (void) stopAnimation
{
	if (m_hDisplayLink && CVDisplayLinkIsRunning(m_hDisplayLink)) CVDisplayLinkStop(m_hDisplayLink);
}

- (void) dealloc
{
    g_pApplication->Term();
    g_pRenderer->Term();
    
	CVDisplayLinkStop(m_hDisplayLink);
	CVDisplayLinkRelease(m_hDisplayLink);
	[m_pkGLContext release];
	[m_pkPixelFormat release];
	[[NSNotificationCenter defaultCenter] removeObserver:self
													name:NSViewGlobalFrameDidChangeNotification
												  object:self];
	VeTerm();
	[super dealloc];
}

@end
