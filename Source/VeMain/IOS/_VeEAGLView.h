////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeEAGLView.h
//  Version:     v1.00
//  Created:     27/11/2012 by Napoleon
//  Compilers:   Xcode Obj-c
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#import <UIKit/UIKit.h>

@interface VeEAGLView : UIView <UITextInput>
{
@public
    EAGLContext* m_pkContext;
    BOOL m_bIsUseUITextField;
@private
    NSString* m_pkMarkedText;
    CGRect m_kCaretRect;
    CGRect m_kOriginalRect;
    NSNotification* m_pkKeyboardShowNotification;
    BOOL m_bIsKeyboardShown;
}

@property(nonatomic, readonly) UITextPosition *beginningOfDocument;
@property(nonatomic, readonly) UITextPosition *endOfDocument;
@property(nonatomic, assign) id<UITextInputDelegate> inputDelegate;
@property(nonatomic, readonly) UITextRange *markedTextRange;
@property (nonatomic, copy) NSDictionary *markedTextStyle;
@property(readwrite, copy) UITextRange *selectedTextRange;
@property(nonatomic, readonly) id<UITextInputTokenizer> tokenizer;
@property(nonatomic, readonly, getter = isKeyboardShown) BOOL isKeyboardShown;
@property(nonatomic, copy) NSNotification* keyboardShowNotification;

+ (id) viewWithFrame:(CGRect)frame;

@end
