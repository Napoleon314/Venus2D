////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTemplate.h
//  Version:     v1.00
//  Created:     26/11/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class CLS, class MEM>
static CLS& VeRefCast(MEM CLS::*OFFSET, const MEM& tChild)
{
	return *(CLS*)(void*)((VeSizeT)(&tChild) - (VeSizeT)(&((*(const CLS*)0).*OFFSET)));
}
