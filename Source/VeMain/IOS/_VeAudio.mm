////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeAudio.mm
//  Version:     v1.00
//  Created:     27/11/2013 by Napoleon
//  Compilers:   Xcode Obj-c
//  Description:
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#import <AudioToolbox/AudioToolbox.h>

#include "../VeMainPCH.h"

//--------------------------------------------------------------------------
void VeAudioInterruptionListener(void* pvData, UInt32 u32State)
{
    if(u32State == kAudioSessionBeginInterruption)
	{
        g_pAudioSystem->OnStartInterruption();
	}
	else if(u32State == kAudioSessionEndInterruption)
	{
		g_pAudioSystem->OnEndInterruption();
	}
}
//--------------------------------------------------------------------------
void VeInitAudio()
{
   VE_ASSERT_EQ(AudioSessionInitialize(NULL, NULL, VeAudioInterruptionListener, NULL), VE_S_OK);
}
//--------------------------------------------------------------------------
