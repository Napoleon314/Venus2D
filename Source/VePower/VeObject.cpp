////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeObject.cpp
//  Version:     v1.00
//  Created:     5/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
VeImplementRootRTTI(VeObject);
//--------------------------------------------------------------------------
VeObject::VeObject()
{

}
//--------------------------------------------------------------------------
VeObject::~VeObject()
{

}
//--------------------------------------------------------------------------
const VeChar8* VeObject::GetTypeName() const
{
	return GetRTTI()->GetName();
}
//--------------------------------------------------------------------------
const VeChar8* VeObject::ToString() const
{
	return GetTypeName();
}
//--------------------------------------------------------------------------
const VeChar8* VeObject::ToString(const VeObject& kObj)
{
	return kObj.ToString();
}
//--------------------------------------------------------------------------
const VeChar8* VeObject::TypeName()
{
	return ms_RTTI.GetName();
}
//--------------------------------------------------------------------------
