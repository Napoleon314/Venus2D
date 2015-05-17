////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Test Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   GraphicsTestMain.cpp
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#if defined(VE_PLATFORM_WIN)// || defined(VE_PLATFORM_MOBILE_SIM)
#	include <vld.h>
#endif
#include <VeMainPCH.h>
#include "VeGraphicsTest.h"

void VeMain(VeStartParams& kParams)
{
	VE_NEW VeGraphicsTest();
	VeStartEngine(kParams);
}

VE_ENTRY_FUNCTION;
