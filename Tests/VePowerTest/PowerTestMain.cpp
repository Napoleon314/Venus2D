////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Test Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   PowerTestMain.cpp
//  Version:     v1.00
//  Created:     9/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#ifdef VE_PLATFORM_WIN
#include <vld.h>
#endif
#include <VeMainPCH.h>
#include "VePowerTest.h"

VE_MAIN_FUNCTION
{
	VeStartParams kParams;
	VE_FILL_START_PARAMS(kParams, VE_TEXT("VePowerTest"));
	VE_NEW VePowerTest();
	return VeStartEngine(kParams);
}
