////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeViewController.mm
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
#import "_VeViewController.h"
#import <QuartzCore/QuartzCore.h>

@implementation VeViewController

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    //return UIInterfaceOrientationIsLandscape( interfaceOrientation );
    return YES;
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAll;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    ((VeIOS*)g_pDevice)->Active();
    ((VeIOS*)g_pDevice)->Show();
}

- (void)viewWillDisappear:(BOOL)animated
{
    ((VeIOS*)g_pDevice)->Hide();
    ((VeIOS*)g_pDevice)->Inactive();
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}


- (void)dealloc
{
    [super dealloc];
}

@end
