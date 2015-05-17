////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMaterialManager.inl
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeMaterial::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE bool VeMaterial::NeedClear()
{
	return m_bNeedClear;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMaterialManager::SetMaterial(const VeChar8* pcName,
	const VeMaterialPtr& spMaterial)
{
	VeStringMap<VeUInt32>::iterator it = m_kMaterialMap.Find(pcName);
	if(it)
	{
		VeMaterialPtr& spMat = m_kMaterialSet[*it];
		if(spMat && (spMat != spMaterial))
		{
			spMat->Clear();
		}
		spMat = spMaterial;
	}
	else
	{
		m_kMaterialMap[pcName] = m_kMaterialSet.Size();
		m_kMaterialSet.PushBack(spMaterial);
	}
}
//--------------------------------------------------------------------------
VE_INLINE const VeMaterialPtr& VeMaterialManager::GetMaterial(
	const VeChar8* pcName)
{
	VeStringMap<VeUInt32>::iterator it = m_kMaterialMap.Find(pcName);
	return it ? m_kMaterialSet[*it] : VeMaterialPtr::ms_NULL;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMaterialManager::RemoveMaterial(const VeChar8* pcName)
{
	VeStringMap<VeUInt32>::iterator it = m_kMaterialMap.Find(pcName);
	if(it)
	{
		if((*it) < (m_kMaterialSet.Size() - 1))
		{
			VeMaterialPtr spMaterial = m_kMaterialSet.Back();
			m_kMaterialMap[spMaterial->GetName()] = *it;
			m_kMaterialSet[*it]->Clear();
			m_kMaterialSet[*it] = spMaterial;
		}
		m_kMaterialMap.Remove(pcName);
		m_kMaterialSet.PopBack();
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeRenderNode* VeMaterialManager::GetRenderNode(
	const VeChar8* pcName)
{
	VeStringMap<VeUInt32>::iterator it = m_kRenderNodeMap.Find(pcName);
	return it ? m_kRenderNodeSet[*it] : NULL;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMaterialManager::AddMat(const VeChar8* pcName,
	VeMaterial::Material* pkMat)
{
	VE_ASSERT(!m_kMatMap.Find(pcName));
	m_kMatMap[pcName] = pkMat;
}
//--------------------------------------------------------------------------
VE_INLINE void VeMaterialManager::DelMat(const VeChar8* pcName)
{
	VE_ASSERT(m_kMatMap.Find(pcName));
	m_kMatMap.Remove(pcName);
}
//--------------------------------------------------------------------------
VE_INLINE VeMaterial::Material* VeMaterialManager::GetMat(
	const VeChar8* pcName)
{
	VeStringMap<VeMaterial::Material*>::iterator it = m_kMatMap.Find(pcName);
	return it ? *it : NULL;
}
//--------------------------------------------------------------------------
