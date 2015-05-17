////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderResource.cpp
//  Version:     v1.00
//  Created:     8/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeMaterialResource.inl"
#endif

//--------------------------------------------------------------------------
VeMaterialResource::VeMaterialResource(const VeChar8* pcName,
	const VeChar8* pcGroup) : VeResource(MATERIAL, pcName, pcGroup)
{

}
//--------------------------------------------------------------------------
VeMaterialResource::~VeMaterialResource()
{
	Unload();
}
//--------------------------------------------------------------------------
VeResource::State VeMaterialResource::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	bool bSync = m_eState == VeResource::UNLOADED;
	m_spMaterial = VE_NEW VeMaterial(m_kName);
	if(VeStrstr(m_kName, ".["))
	{
		m_spMaterial->UpdateXML(*spStream, bSync);
	}
	else
	{
		m_spMaterial->Update(*spStream);
	}
	g_pMaterialManager->SetMaterial(m_kName, m_spMaterial);
	return VeResource::LOADED;
}
//--------------------------------------------------------------------------
void VeMaterialResource::UnloadImpl()
{
	if(m_spMaterial && m_spMaterial->NeedClear())
	{
		m_spMaterial->Clear();
		g_pMaterialManager->RemoveMaterial(m_kName);		
		m_spMaterial = NULL;
	}
}
//--------------------------------------------------------------------------
VeResource* VeMaterialResource::Create(const VeChar8* pcName,
	const VeChar8* pcGroup)
{
	return VE_NEW VeMaterialResource(pcName, pcGroup);
}
//--------------------------------------------------------------------------
