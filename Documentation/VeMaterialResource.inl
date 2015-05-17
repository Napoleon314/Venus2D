////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMaterialResource.inl
//  Version:     v1.00
//  Created:     2/1/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
const VeMaterialPtr& VeMaterialResource::GetMaterial()
{
	return m_spMaterial;
}
//--------------------------------------------------------------------------
void VeMaterialResource::DetachMaterial()
{
	m_spMaterial = NULL;
}
//--------------------------------------------------------------------------
