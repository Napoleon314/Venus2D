////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeAppDelegate.mm
//  Version:     v1.00
//  Created:     27/11/2012 by Napoleon
//  Compilers:   Xcode Obj-c
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "../VeMainPCH.h"
#include "_VeIOS.h"
#import "_VeAppDelegate.h"

//--------------------------------------------------------------------------
static VeStartParams s_kParams = { "Venus3D", NULL, "startup.cfg", "file#", NULL, "file#Lua/startup.lua" };
//--------------------------------------------------------------------------
extern void VeMain(VeStartParams& kParams);
//--------------------------------------------------------------------------
int main(int iArgc, char* apcArgv[])
{
    VeInt32 i32Res(0);
    @autoreleasepool
    {
        VeChar8 acCmd[256];
        VeZeroMemory(acCmd, 256);
        VeUInt32 u32Pos(0);
        for(VeUInt32 i(1); i < iArgc; ++i)
        {
            u32Pos += VeSprintf(acCmd + u32Pos, 256 - u32Pos, u32Pos ? " %s" : "%s", apcArgv[i]);
        }
        s_kParams.m_pcCmdLine = acCmd;
        i32Res = UIApplicationMain(iArgc, apcArgv, nil, NSStringFromClass([VeAppDelegate class]));
    }
    return i32Res;
}
//--------------------------------------------------------------------------

@implementation VeAppDelegate

+ (id) sharedAppDelegate
{
    return [[UIApplication sharedApplication] delegate];
}

+ (NSString *)getAppDelegateClassName
{
    return @"VeAppDelegate";
}

- (void)postFinishLaunch
{
    VeMain(s_kParams);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [[NSFileManager defaultManager] changeCurrentDirectoryPath: [[NSBundle mainBundle] resourcePath]];
    [self performSelector:@selector(postFinishLaunch) withObject:nil afterDelay:0.0];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    if(g_pDevice)
    {
        ((VeIOS*)g_pDevice)->Hide();
        ((VeIOS*)g_pDevice)->Inactive();
    }
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    if(g_pDevice)
    {
        ((VeIOS*)g_pDevice)->Active();
        ((VeIOS*)g_pDevice)->Show();
    }
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    //[m_pkViewController stopAnimation];
    g_pApplication->QuitApp();
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application
{
    // Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
}

- (void)dealloc
{
    [super dealloc];
}

@end
