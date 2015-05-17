////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRTTI.cpp
//  Version:     v1.00
//  Created:     29/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
VeRTTI::VeRTTI(const VeChar8* pcName, const VeRTTI* pkBaseRTTI)
	: m_pcName(pcName), m_pkBaseRTTI(pkBaseRTTI)
{

}
//--------------------------------------------------------------------------
const VeChar8* VeRTTI::GetName() const
{
	return m_pcName;
}
//--------------------------------------------------------------------------
const VeRTTI* VeRTTI::GetBaseRTTI() const
{
	return m_pkBaseRTTI;
}
//--------------------------------------------------------------------------
