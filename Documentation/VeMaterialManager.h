////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMaterialManager.h
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeMaterial : public VeRefObject
{
public:
	struct Node
	{
		VeFixedStringA m_kName;
		VeFixedStringA m_kDataName;
		VeFixedStringA m_kParentName;
	};

	struct Material
	{
		VeFixedStringA m_kName;
		VeVector<VeRenderNode*> m_kRenderNodeArray;
	};

	VeMaterial(const VeChar8* pcName);

	~VeMaterial();

	VE_INLINE const VeChar8* GetName();

	VE_INLINE bool NeedClear();

	bool Update(VeBinaryIStream& kStream);

	bool UpdateXML(VeBinaryIStream& kStream, bool bSync);

	void Clear();

protected:
	void UpdatePlatform(VeBinaryIStream& kStream);

	const VeFixedStringA m_kName;
	VeVector<VeRenderObjectPtr> m_kRenderObjectArray;
	VeVector<VeRenderNodeDataPtr> m_kRenderNodeDataArray;
	VeVector<Node> m_kNodeArray;
	VeVector<Material> m_kMaterialArray;
	bool m_bNeedClear;

};

VeSmartPointer(VeMaterial);

class VE_MAIN_API VeMaterialManager : public VeSingleton<VeMaterialManager>
{
public:
	VeMaterialManager();

	~VeMaterialManager();
	
	void LoadShaderList(const VeChar8* pcPath);

	VE_INLINE void SetMaterial(const VeChar8* pcName, const VeMaterialPtr& spMaterial);

	VE_INLINE const VeMaterialPtr& GetMaterial(const VeChar8* pcName);

	VE_INLINE void RemoveMaterial(const VeChar8* pcName);

	VeRenderNode* CreateRenderNode(const VeChar8* pcName, const VeChar8* pcData, const VeChar8* pcParent);

	void DestoryRenderNode(const VeChar8* pcName);

	VE_INLINE VeRenderNode* GetRenderNode(const VeChar8* pcName);

	VE_INLINE void AddMat(const VeChar8* pcName, VeMaterial::Material* pkMat);

	VE_INLINE void DelMat(const VeChar8* pcName);

	VE_INLINE VeMaterial::Material* GetMat(const VeChar8* pcName);

protected:
	VeStringMap<VeUInt32> m_kRenderNodeMap;
	VeVector<VeRenderNode*> m_kRenderNodeSet;
	VeStringMap<VeUInt32> m_kMaterialMap;
	VeVector<VeMaterialPtr> m_kMaterialSet;
	VeStringMap<VeMaterial::Material*> m_kMatMap;

};

#define g_pMaterialManager VeMaterialManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeMaterialManager.inl"
#endif
