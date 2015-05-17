////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeEAGLView.mm
//  Version:     v1.00
//  Created:     27/11/2012 by Napoleon
//  Compilers:   Xcode Obj-c
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#import "_VeEAGLView.h"
#import <QuartzCore/QuartzCore.h>
#include "../VeMainPCH.h"
#include "../_VeRendererGLES2.h"

VeEAGLView* g_pkView = NULL;
static VeVector<VeVector2D> s_kTouchCache;

void VeRenderbufferStorageLayer()
{
    VE_ASSERT(g_pkView);
    [g_pkView->m_pkContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)g_pkView.layer];
}

void VeGLESPresent()
{
    VE_ASSERT(g_pkView);
    [g_pkView->m_pkContext presentRenderbuffer:GL_RENDERBUFFER];
}

@implementation VeEAGLView

@synthesize isKeyboardShown=m_bIsKeyboardShown;
@synthesize keyboardShowNotification = m_pkKeyboardShowNotification;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
    return [[[self alloc] initWithFrame:frame] autorelease];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if(self)
    {
        g_pkView = self;
        if([self respondsToSelector:@selector(setContentScaleFactor:)])
		{
			self.contentScaleFactor = [[UIScreen mainScreen] scale];
		}
        [self setMultipleTouchEnabled:TRUE];
        CAEAGLLayer* pkLayer = (CAEAGLLayer*)self.layer;
        pkLayer.opaque = YES;
        pkLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
            [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
            kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        m_pkContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if(!m_pkContext || ![EAGLContext setCurrentContext:m_pkContext])
        {
            [self release];
            return nil;
        }
    }
    return self;
}

- (void) layoutSubviews
{
    [EAGLContext setCurrentContext:m_pkContext];
    if(g_pRenderer->IsInited())
    {
        ((VeRendererGLES2*)g_pRenderer)->OnBufferRestorage();
    }
}

- (void)dealloc
{
    [EAGLContext setCurrentContext:nil];
    [m_pkContext release];
    [super dealloc];
}

#pragma mark CCEAGLView - Touch Delegate

-(void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    VeUInt32 u32Time = g_pTime->GetTimeUInt();
    for(UITouch* touch in touches)
    {
        bool bNeedAppend = true;
        for(VeUInt32 i(0); i < s_kTouchCache.Size(); ++i)
        {
            VeVector2D& kVector = s_kTouchCache[i];
            if(kVector.x < 0)
            {
                VeInputManager::TouchPointParam* pkParam(NULL);
                g_pInputManager->GetSingle(pkParam);
                pkParam->x = [touch locationInView:self].x * self.contentScaleFactor;
                pkParam->y = [touch locationInView:self].y * self.contentScaleFactor;
                pkParam->id = i;
                g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_BEGAN, u32Time, pkParam);
                kVector.x = pkParam->x;
                kVector.y = pkParam->y;
                bNeedAppend = false;
                break;
            }
        }
        if(bNeedAppend)
        {
            VeInputManager::TouchPointParam* pkParam(NULL);
            g_pInputManager->GetSingle(pkParam);
            pkParam->x = [touch locationInView:self].x * self.contentScaleFactor;
            pkParam->y = [touch locationInView:self].y * self.contentScaleFactor;
            pkParam->id = s_kTouchCache.Size();
            g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_BEGAN, u32Time, pkParam);
            s_kTouchCache.PushBack(VeVector2D(pkParam->x, pkParam->y));
        }
    }
}

-(void)touchesMoved:(NSSet*)touches withEvent:(UIEvent *)event
{
    VeUInt32 u32Time = g_pTime->GetTimeUInt();
    VeVector<VeInputManager::TouchPointParam>* pkParams = g_pInputManager->GetList<VeInputManager::TouchPointParam>();
    pkParams->Clear();
    
    for(UITouch* touch in touches)
    {
        for(VeUInt32 i(0); i < s_kTouchCache.Size(); ++i)
        {
            VeVector2D& kVector = s_kTouchCache[i];
            if(VeAlmostEqual(kVector, VeVector2D([touch previousLocationInView:self].x * self.contentScaleFactor, [touch previousLocationInView:self].y * self.contentScaleFactor), 10 * self.contentScaleFactor))
            {
                VeInputManager::TouchPointParam kParam =
                {
                    VeFloat32([touch locationInView:self].x * self.contentScaleFactor),
                    VeFloat32([touch locationInView:self].y * self.contentScaleFactor),
                    i
                };
                kVector.x = kParam.x;
                kVector.y = kParam.y;
                pkParams->PushBack(kParam);
                break;
            }
        }
    }
    
    g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_MOVED, u32Time, pkParams);
}

-(void)touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
    VeUInt32 u32Time = g_pTime->GetTimeUInt();
    for(UITouch* touch in touches)
    {
        for(VeUInt32 i(0); i < s_kTouchCache.Size(); ++i)
        {
            VeVector2D& kVector = s_kTouchCache[i];
            if(VeAlmostEqual(kVector, VeVector2D([touch previousLocationInView:self].x * self.contentScaleFactor, [touch previousLocationInView:self].y * self.contentScaleFactor), 10 * self.contentScaleFactor))
            {
                VeInputManager::TouchPointParam* pkParam(NULL);
                g_pInputManager->GetSingle(pkParam);
                pkParam->x = [touch locationInView:self].x * self.contentScaleFactor;
                pkParam->y = [touch locationInView:self].y * self.contentScaleFactor;
                pkParam->id = i;
                g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_ENDED, u32Time, pkParam);
                kVector.x = -1;
                break;
            }
        }
    }
}

-(void)touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
    VeUInt32 u32Time = g_pTime->GetTimeUInt();
    VeVector<VeInputManager::TouchPointParam>* pkParams = g_pInputManager->GetList<VeInputManager::TouchPointParam>();
    pkParams->Clear();
    
    for(UITouch* touch in touches)
    {
        for(VeUInt32 i(0); i < s_kTouchCache.Size(); ++i)
        {
            VeVector2D& kVector = s_kTouchCache[i];
            if(VeAlmostEqual(kVector, VeVector2D([touch previousLocationInView:self].x * self.contentScaleFactor, [touch previousLocationInView:self].y * self.contentScaleFactor), 10 * self.contentScaleFactor))
            {
                VeInputManager::TouchPointParam kParam =
                {
                    VeFloat32([touch locationInView:self].x * self.contentScaleFactor),
                    VeFloat32([touch locationInView:self].y * self.contentScaleFactor),
                    i
                };
                pkParams->PushBack(kParam);
                break;
            }
        }
    }
    
    s_kTouchCache.Clear();
    g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_CANCELLED, u32Time, pkParams);
}

#pragma mark - UIView - Responder

- (BOOL)canBecomeFirstResponder
{
    if(nil != m_pkMarkedText)
    {
        [m_pkMarkedText release];
        m_pkMarkedText = nil;
    }
    if (m_bIsUseUITextField)
    {
        return NO;
    }
    return YES;
}

- (BOOL)becomeFirstResponder
{
    m_bIsUseUITextField = NO;
    return [super becomeFirstResponder];
}

- (BOOL)resignFirstResponder
{
    m_bIsUseUITextField = YES;
    return [super resignFirstResponder];
}

#pragma mark - UIKeyInput protocol

- (BOOL)hasText
{
    return NO;
}

- (void)insertText:(NSString *)text
{
    if(nil != m_pkMarkedText)
    {
        [m_pkMarkedText release];
        m_pkMarkedText = nil;
    }
    const VeChar8* pcText = [text cStringUsingEncoding:NSUTF8StringEncoding];
    VeDebugOutput(pcText);
}

- (void)deleteBackward
{
    if(nil != m_pkMarkedText)
    {
        [m_pkMarkedText release];
        m_pkMarkedText = nil;
    }
}

#pragma mark - UITextInputTrait protocol

-(UITextAutocapitalizationType) autocapitalizationType
{
    return UITextAutocapitalizationTypeWords;
}

#pragma mark - UITextInput protocol

#pragma mark UITextInput - properties

@synthesize beginningOfDocument;
@synthesize endOfDocument;
@synthesize inputDelegate;
@synthesize markedTextRange;
@synthesize markedTextStyle;
// @synthesize selectedTextRange;       // must implement
@synthesize tokenizer;

/* Text may have a selection, either zero-length (a caret) or ranged.  Editing operations are
 * always performed on the text from this selection.  nil corresponds to no selection. */
- (void)setSelectedTextRange:(UITextRange *)aSelectedTextRange;
{
    VeDebugOutput("UITextRange:setSelectedTextRange");
}

- (UITextRange *)selectedTextRange;
{
    return [[[UITextRange alloc] init] autorelease];
}

#pragma mark UITextInput - Replacing and Returning Text

- (NSString *)textInRange:(UITextRange *)range;
{
    VeDebugOutput("textInRange");
    return @"";
}
- (void)replaceRange:(UITextRange *)range withText:(NSString *)theText;
{
    VeDebugOutput("replaceRange");
}

#pragma mark UITextInput - Working with Marked and Selected Text

/* If text can be selected, it can be marked. Marked text represents provisionally
 * inserted text that has yet to be confirmed by the user.  It requires unique visual
 * treatment in its display.  If there is any marked text, the selection, whether a
 * caret or an extended range, always resides within.
 *
 * Setting marked text either replaces the existing marked text or, if none is present,
 * inserts it from the current selection. */

- (void)setMarkedTextRange:(UITextRange *)markedTextRange;
{
    VeDebugOutput("setMarkedTextRange");
}

- (UITextRange *)markedTextRange;
{
    VeDebugOutput("markedTextRange");
    return nil; // Nil if no marked text.
}

- (void)setMarkedTextStyle:(NSDictionary *)markedTextStyle;
{
    VeDebugOutput("setMarkedTextStyle");
    
}

- (NSDictionary *)markedTextStyle;
{
    VeDebugOutput("markedTextStyle");
    return nil;
}

- (void)setMarkedText:(NSString *)markedText selectedRange:(NSRange)selectedRange;
{
    VeDebugOutput("setMarkedText");
    if(markedText == m_pkMarkedText)
    {
        return;
    }
    if(nil != m_pkMarkedText)
    {
        [m_pkMarkedText release];
    }
    m_pkMarkedText = markedText;
    [m_pkMarkedText retain];
}

- (void)unmarkText;
{
    VeDebugOutput("unmarkText");
    if(nil == m_pkMarkedText)
    {
        return;
    }
    const VeChar8* pcText = [m_pkMarkedText cStringUsingEncoding:NSUTF8StringEncoding];
    VeDebugOutput(pcText);
    [m_pkMarkedText release];
    m_pkMarkedText = nil;
}

#pragma mark Methods for creating ranges and positions.

- (UITextRange *)textRangeFromPosition:(UITextPosition *)fromPosition toPosition:(UITextPosition *)toPosition;
{
    VeDebugOutput("textRangeFromPosition");
    return nil;
}

- (UITextPosition *)positionFromPosition:(UITextPosition *)position offset:(NSInteger)offset;
{
    VeDebugOutput("positionFromPosition");
    return nil;
}

- (UITextPosition *)positionFromPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction offset:(NSInteger)offset;
{
    VeDebugOutput("positionFromPosition");
    return nil;
}

/* Simple evaluation of positions */
- (NSComparisonResult)comparePosition:(UITextPosition *)position toPosition:(UITextPosition *)other;
{
    VeDebugOutput("comparePosition");
    return (NSComparisonResult)0;
}

- (NSInteger)offsetFromPosition:(UITextPosition *)from toPosition:(UITextPosition *)toPosition;
{
    VeDebugOutput("offsetFromPosition");
    return 0;
}

- (UITextPosition *)positionWithinRange:(UITextRange *)range farthestInDirection:(UITextLayoutDirection)direction;
{
    VeDebugOutput("positionWithinRange");
    return nil;
}

- (UITextRange *)characterRangeByExtendingPosition:(UITextPosition *)position inDirection:(UITextLayoutDirection)direction;
{
    VeDebugOutput("characterRangeByExtendingPosition");
    return nil;
}

#pragma mark Writing direction

- (UITextWritingDirection)baseWritingDirectionForPosition:(UITextPosition *)position inDirection:(UITextStorageDirection)direction;
{
    VeDebugOutput("baseWritingDirectionForPosition");
    return UITextWritingDirectionNatural;
}

- (void)setBaseWritingDirection:(UITextWritingDirection)writingDirection forRange:(UITextRange *)range;
{
    VeDebugOutput("setBaseWritingDirection");
}

#pragma mark Geometry

/* Geometry used to provide, for example, a correction rect. */
- (CGRect)firstRectForRange:(UITextRange *)range;
{
    VeDebugOutput("firstRectForRange");
    return CGRectNull;
}

- (CGRect)caretRectForPosition:(UITextPosition *)position;
{
    VeDebugOutput("caretRectForPosition");
    return m_kCaretRect;
}

#pragma mark Hit testing

/* JS - Find the closest position to a given point */
- (UITextPosition *)closestPositionToPoint:(CGPoint)point;
{
    VeDebugOutput("closestPositionToPoint");
    return nil;
}

- (UITextPosition *)closestPositionToPoint:(CGPoint)point withinRange:(UITextRange *)range;
{
    VeDebugOutput("closestPositionToPoint");
    return nil;
}

- (UITextRange *)characterRangeAtPoint:(CGPoint)point;
{
    VeDebugOutput("characterRangeAtPoint");
    return nil;
}

- (NSArray *)selectionRectsForRange:(UITextRange *)range
{
    VeDebugOutput("selectionRectsForRange");
    return nil;
}

#pragma mark - UIKeyboard notification

- (void)onUIKeyboardNotification:(NSNotification *)notif;
{
    const VeChar8* pkNotification = [notif.name cStringUsingEncoding:NSUTF8StringEncoding];
    VeDebugOutput(pkNotification);
    
}

-(void) doAnimationWhenKeyboardMoveWithDuration:(float)duration distance:(float)dis
{
    VeDebugOutput("%f", dis);
}


-(void) doAnimationWhenAnotherEditBeClicked
{
    if (self.keyboardShowNotification != nil)
    {
        [[NSNotificationCenter defaultCenter]postNotification:self.keyboardShowNotification];
    }
}

@end
