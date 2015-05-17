////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeIOS.cpp
//  Version:     v1.00
//  Created:     27/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "../VeMainPCH.h"
#include "_VeIOS.h"
#import <UIKit/UIKit.h>
#import "_VeEAGLView.h"
#import "_VeViewController.h"

//--------------------------------------------------------------------------
struct DisplayData : public VeRefObject
{
    DisplayData(UIScreen *uiscreen, CGFloat scale)
    {
        this->uiscreen = uiscreen;
        [this->uiscreen retain];
        this->scale = scale;
    }
    
    virtual ~DisplayData()
    {
        [this->uiscreen release];
    }
    
    UIScreen *uiscreen;
    CGFloat scale;
};
//--------------------------------------------------------------------------
struct DisplayModeData : public VeRefObject
{
    DisplayModeData(UIScreenMode *uiscreenmode, CGFloat scale)
    {
        this->uiscreenmode = uiscreenmode;
        [this->uiscreenmode retain];
        this->scale = scale;
    }
    
    virtual ~DisplayModeData()
    {
        [this->uiscreenmode release];
    }
    
    UIScreenMode *uiscreenmode;
    CGFloat scale;
};


struct WindowData : public VeRefObject
{
    UIWindow* m_pkUIWindow;
    VeViewController* m_pkViewController;
};
//--------------------------------------------------------------------------
static VE_BOOL s_bSupportsMultipleDisplays = VE_FALSE;
//--------------------------------------------------------------------------
static VE_BOOL UIKit_IsDisplayLandscape(UIScreen *uiscreen)
{
    if(uiscreen == [UIScreen mainScreen])
    {
        return UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation]);
    }
    else
    {
        CGSize size = [uiscreen bounds].size;
        return (size.width > size.height);
    }
}
//--------------------------------------------------------------------------
static void UIKit_AddDisplay(VeIOS* pkDevice, UIScreen *uiscreen)
{
    CGSize size = [uiscreen bounds].size;
    
    if(UIKit_IsDisplayLandscape(uiscreen) != (size.width > size.height))
    {
        CGFloat height = size.width;
        size.width = size.height;
        size.height = height;
    }
    
    CGFloat scale;
    if([UIScreen instancesRespondToSelector:@selector(scale)])
    {
        scale = [uiscreen scale];
    }
    else
    {
        scale = 1.0f;
    }
    
    VeDevice::VideoDisplay kDisplay;
    VeDevice::DisplayMode kMode;
    kMode.m_u32Format = VE_PIXELFORMAT_ABGR8888;
    kMode.w = (int)(size.width * scale);
    kMode.h = (int)(size.height * scale);
    
    UIScreenMode *uiscreenmode = nil;
    if(s_bSupportsMultipleDisplays)
    {
        uiscreenmode = [uiscreen currentMode];
    }
    
    kMode.m_spDriverData = VE_NEW DisplayModeData(uiscreenmode, scale);
    kDisplay.m_kDesktopMode = kMode;
    kDisplay.m_kCurrentMode = kMode;
    kDisplay.m_spDriverData = VE_NEW DisplayData(uiscreen, scale);
    pkDevice->AddDisplay(kDisplay);
}
//--------------------------------------------------------------------------
static void UIKit_AddSingleDisplayMode(VeDevice::VideoDisplay& kDisplay,
    int w, int h, UIScreenMode *uiscreenmode, CGFloat scale)
{
    VeDevice::DisplayMode kMode;
    kMode.m_u32Format = VE_PIXELFORMAT_ABGR8888;
    kMode.m_i32RefreshRate = 0;
    kMode.w = w;
    kMode.h = h;
    kMode.m_spDriverData = VE_NEW DisplayModeData(uiscreenmode, scale);
    kDisplay.m_kDisplayModes[kMode.GetValue()] = kMode;
}
//--------------------------------------------------------------------------
static void UIKit_AddDisplayMode(VeDevice::VideoDisplay& kDisplay,
    int w, int h, CGFloat scale, UIScreenMode *uiscreenmode, BOOL addRotation)
{
    UIKit_AddSingleDisplayMode(kDisplay, w, h, uiscreenmode, scale);
    if(addRotation)
    {
        UIKit_AddSingleDisplayMode(kDisplay, h, w, uiscreenmode, scale);
    }
}
//--------------------------------------------------------------------------
static void SetupWindowData(VeIOS* pkDevice, VeDevice::Window* pkWindow,
    UIWindow *uiwindow, VE_BOOL bCreated)
{
    VeDevice::VideoDisplay* pkDisplay = pkDevice->GetDisplayForWindow(pkWindow);
    DisplayModeData* pkDisplayModeData = (DisplayModeData*)(VeRefObject*)pkDisplay->m_kCurrentMode.m_spDriverData;
    DisplayData* pkDisplayData = (DisplayData*)(VeRefObject*)pkDisplay->m_spDriverData;
    WindowData* pkData = VE_NEW WindowData();
    
    pkData->m_pkUIWindow = uiwindow;
    
    {
        pkWindow->x = 0;
        pkWindow->y = 0;
        
        CGRect bounds;
        if(pkWindow->m_u32Flags & (VeDevice::WINDOW_FULLSCREEN | VeDevice::WINDOW_BORDERLESS))
        {
            bounds = [pkDisplayData->uiscreen bounds];
        }
        else
        {
            bounds = [pkDisplayData->uiscreen applicationFrame];
        }
        
        VeInt32 width = (int)(bounds.size.width * pkDisplayModeData->scale);
        VeInt32 height = (int)(bounds.size.height * pkDisplayModeData->scale);
        
        if(UIKit_IsDisplayLandscape(pkDisplayData->uiscreen) != (width > height))
        {
            VeExchangeXor(width, height);
        }
        pkWindow->w = width;
        pkWindow->h = height;
    }
    
    pkWindow->m_spDriverData = pkData;
    
    pkWindow->m_u32Flags &= ~VeDevice::WINDOW_HIDDEN;
    
    if(pkDisplayData->uiscreen == [UIScreen mainScreen])
    {
        pkWindow->m_u32Flags |= VeDevice::WINDOW_INPUT_FOCUS;
    }
    else
    {
        pkWindow->m_u32Flags &= ~VeDevice::WINDOW_RESIZABLE;
        pkWindow->m_u32Flags &= ~VeDevice::WINDOW_INPUT_FOCUS;
        pkWindow->m_u32Flags |= VeDevice::WINDOW_BORDERLESS;
    }
    
    VeEAGLView* pkView = [VeEAGLView viewWithFrame:[uiwindow bounds]];
    
    pkData->m_pkViewController = [[VeViewController alloc] initWithNibName:nil bundle:nil];
    pkData->m_pkViewController.wantsFullScreenLayout = YES;
    pkData->m_pkViewController.view = pkView;
    
    [uiwindow setRootViewController:pkData->m_pkViewController];
}
//--------------------------------------------------------------------------
void VeIOS::AddDisplay(VideoDisplay& kDisplay)
{
    m_kDisplays.PushBack(kDisplay);
}
//--------------------------------------------------------------------------
VeIOS::VeIOS(VeStartParams& kParams) : VeDevice(TYPE_IOS, kParams)
{
    m_kDeviceID = [[[[UIDevice currentDevice] identifierForVendor] UUIDString] UTF8String];
    m_kDeviceName = [[UIDevice currentDevice].name UTF8String];
    NSString* pkLan = [[NSLocale preferredLanguages] objectAtIndex:0];
    if(![pkLan compare:@"zh-Hans"])
    {
        m_eLanguage = ZH_CN;
    }
    else if(![pkLan compare:@"zh-Hant"])
    {
        m_eLanguage = ZH_TW;
    }
    else
    {
        m_eLanguage = EN_US;
    }
}
//--------------------------------------------------------------------------
VeIOS::~VeIOS()
{
    
}
//--------------------------------------------------------------------------
void VeIOS::_Init()
{
    InitDisplayModes();
}
//--------------------------------------------------------------------------
void VeIOS::_Term()
{
    TermDisplayModes();
}
//--------------------------------------------------------------------------
void VeIOS::_GetDisplayModes(VideoDisplay& kDisplay)
{
    DisplayData* pkData = (DisplayData*)(VeRefObject*)kDisplay.m_spDriverData;
    
    VE_BOOL isLandscape = UIKit_IsDisplayLandscape(pkData->uiscreen);
    VE_BOOL addRotation = (pkData->uiscreen == [UIScreen mainScreen]);
    
    if(s_bSupportsMultipleDisplays)
    {
        for(UIScreenMode *uimode in [pkData->uiscreen availableModes])
        {
            CGSize size = [uimode size];
            int w = (int)size.width;
            int h = (int)size.height;
            
            if(isLandscape != (w > h))
            {
                int tmp = w;
                w = h;
                h = tmp;
            }
            
            UIKit_AddDisplayMode(kDisplay, w, h, pkData->scale, uimode, addRotation);
            
            if(pkData->scale != 1.0f)
            {
                UIKit_AddDisplayMode(kDisplay, (int)(size.width / pkData->scale),
                    (int)(size.height / pkData->scale), 1.0f, uimode, addRotation);
            }
        }
    }
    else
    {
        const CGSize size = [pkData->uiscreen bounds].size;
        int w = (int)size.width;
        int h = (int)size.height;
        
        if(isLandscape != (w > h))
        {
            VeExchangeXor(w, h);
        }
        UIKit_AddDisplayMode(kDisplay, w, h, 1.0f, nil, addRotation);
    }
}
//--------------------------------------------------------------------------
void VeIOS::_CreateWindow(Window* pkWindow)
{
    VideoDisplay* pkDisplay = GetDisplayForWindow(pkWindow);
    VE_ASSERT(pkDisplay);
    DisplayData* pkData = (DisplayData*)(VeRefObject*)pkDisplay->m_spDriverData;
    const BOOL external = ([UIScreen mainScreen] != pkData->uiscreen);
    
    if(s_bSupportsMultipleDisplays)
    {
        const CGSize origsize = [[pkData->uiscreen currentMode] size];
        if((origsize.width == 0.0f) && (origsize.height == 0.0f))
        {
            if(pkDisplay->m_kDisplayModes.Size() == 0)
            {
                _GetDisplayModes(*pkDisplay);
            }
            
            const DisplayMode* pkBestmode(NULL);
            for(VeInt32 i = pkDisplay->m_kDisplayModes.Size(); i >= 0; --i)
            {
                const DisplayMode* pkMode = &pkDisplay->m_kDisplayModes[i];
                if((pkMode->w >= pkWindow->w) && (pkMode->h >= pkWindow->h))
                    pkBestmode = pkMode;
            }
            
            if(pkBestmode)
            {
                DisplayModeData* pkModedata = (DisplayModeData*)(VeRefObject*)pkBestmode->m_spDriverData;
                [pkData->uiscreen setCurrentMode:pkModedata->uiscreenmode];
                pkDisplay->m_kCurrentMode = *pkBestmode;
            }
        }
    }
    
    if(pkData->uiscreen == [UIScreen mainScreen])
    {
        pkWindow->m_u32Flags &= ~WINDOW_FULLSCREEN;
        pkWindow->m_u32Flags &= ~WINDOW_BORDERLESS;
        [UIApplication sharedApplication].statusBarHidden = YES;
    }
    
    if(!(pkWindow->m_u32Flags & WINDOW_RESIZABLE))
    {
        if(pkWindow->w > pkWindow->h)
        {
            if(!UIKit_IsDisplayLandscape(pkData->uiscreen))
            {
                [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight animated:NO];
            }
        }
        else if(pkWindow->w < pkWindow->h)
        {
            if(UIKit_IsDisplayLandscape(pkData->uiscreen))
            {
                [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationPortrait animated:NO];
            }
        }
    }
    
    UIWindow *uiwindow = [UIWindow alloc];
    uiwindow = [uiwindow initWithFrame:[pkData->uiscreen bounds]];
   
    if(external)
    {
        [uiwindow setScreen:pkData->uiscreen];
    }
    
    SetupWindowData(this, pkWindow, uiwindow, VE_TRUE);
}
//--------------------------------------------------------------------------
void VeIOS::_DestoryWindow(Window* pkWindow)
{
    WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
    if(pkData)
    {
        [pkData->m_pkViewController release];
        [pkData->m_pkUIWindow release];
    }
}
//--------------------------------------------------------------------------
void VeIOS::_ShowWindow(Window* pkWindow)
{
    WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
    [pkData->m_pkUIWindow makeKeyAndVisible];
}
//--------------------------------------------------------------------------
void VeIOS::_HideWindow(Window* pkWindow)
{
    WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
    pkData->m_pkUIWindow.hidden = YES;
}
//--------------------------------------------------------------------------
void VeIOS::_PumpEvents()
{
    const CFTimeInterval seconds = 0.000002;
    
    SInt32 result;
    do
    {
        result = CFRunLoopRunInMode(kCFRunLoopDefaultMode, seconds, TRUE);
    }
    while(result == kCFRunLoopRunHandledSource);
    
    do
    {
        result = CFRunLoopRunInMode((CFStringRef)UITrackingRunLoopMode, seconds, TRUE);
    }
    while(result == kCFRunLoopRunHandledSource);
}
//--------------------------------------------------------------------------
void VeIOS::InitDisplayModes()
{
    s_bSupportsMultipleDisplays = [UIScreen instancesRespondToSelector:@selector(currentMode)];
    UIKit_AddDisplay(this, [UIScreen mainScreen]);
    if(s_bSupportsMultipleDisplays)
    {
        for(UIScreen *uiscreen in [UIScreen screens])
        {
            if(uiscreen != [UIScreen mainScreen])
            {
                UIKit_AddDisplay(this, uiscreen);
            }
        }
    }
}
//--------------------------------------------------------------------------
void VeIOS::TermDisplayModes()
{
    m_kDisplays.Clear();
}
//--------------------------------------------------------------------------
void VeIOS::Show()
{
    VeDevice::Show();
}
//--------------------------------------------------------------------------
void VeIOS::Hide()
{
    VeDevice::Hide();
}
//--------------------------------------------------------------------------
void VeIOS::Active()
{
    VeDevice::Active();
}
//--------------------------------------------------------------------------
void VeIOS::Inactive()
{
    VeDevice::Inactive();
}
//--------------------------------------------------------------------------
void VeIOS::_EnableIME(Window* pkWindow)
{
    WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
    [pkData->m_pkViewController.view becomeFirstResponder];
}
//--------------------------------------------------------------------------
void VeIOS::_DisableIME(Window* pkWindow)
{
    WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
    [pkData->m_pkViewController.view resignFirstResponder];
}
//--------------------------------------------------------------------------
