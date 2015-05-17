////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeGLShell.h
//  Version:     v1.00
//  Created:     17/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

@interface VeGLView : NSView
{
	NSOpenGLPixelFormat* m_pkPixelFormat;
    NSOpenGLContext* m_pkGLContext;
	CVDisplayLinkRef m_hDisplayLink;
	BOOL m_bIsAnimating;
}

- (id) initWithFrame:(NSRect)frameRect;

- (void) drawView;

- (void) startAnimation;

- (void) stopAnimation;

@end
