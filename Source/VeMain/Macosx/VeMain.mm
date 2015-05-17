////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMain.mm
//  Version:     v1.00
//  Created:     17/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#import <Cocoa/Cocoa.h>
#include "VeMainPCH.h"

extern VeStartParams g_kParams;

VeInt32 VeStartEngine(VeStartParams& kParams)
{
    g_kParams = kParams;
    return NSApplicationMain(kParams.m_iArgc, NULL);
}
