////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMaterialManager.cpp
//  Version:     v1.00
//  Created:     13/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeMaterialManager.inl"
#endif

//--------------------------------------------------------------------------
VeMaterial::VeMaterial(const VeChar8* pcName) : m_kName(pcName),
	m_bNeedClear(false)
{
	
}
//--------------------------------------------------------------------------
VeMaterial::~VeMaterial()
{

}
//--------------------------------------------------------------------------
bool VeMaterial::Update(VeBinaryIStream& kStream)
{
	Clear();
	VeUInt32 u32Temp;
	kStream >> u32Temp;
	if(u32Temp != VE_MAKE_ID('V', 'M', 'A', 'T')) return false;
	VeUInt32 u32PlatformCount;
	kStream >> u32PlatformCount;
	for(VeUInt32 i(0); i < u32PlatformCount; ++i)
	{
		kStream >> u32Temp;
		bool bSupport = VE_MASK_HAS_ANY(u32Temp, VE_PLATFORM_MASK);
		kStream >> u32Temp;
		if(bSupport)
		{
			UpdatePlatform(kStream);
		}
		else
		{
			kStream.Skip(u32Temp);
		}
	}
	m_bNeedClear = true;
	return true;
}
//--------------------------------------------------------------------------
bool VeMaterial::UpdateXML(VeBinaryIStream& kStream, bool bSync)
{
	Clear();
	VeXMLDocument kDoc;
	kStream >> kDoc;
	VE_ASSERT(!kDoc.Error());
	VeXMLElement* pkRoot = kDoc.RootElement();
	VE_ASSERT(pkRoot);
	VeXMLElement* pkPlatform = pkRoot->FirstChildElement("Platform");
	while(pkPlatform)
	{
		if(pkPlatform->Attribute(VE_PLATFORM_NAME_LITE, true))
		{
			VeXMLElement* pkRenderObject = pkPlatform->FirstChildElement("RenderObject");
			if(pkRenderObject)
			{
				VeXMLElement* pkObject = pkRenderObject->FirstChildElement();
				while(pkObject)
				{
					VeRenderObjectPtr spRenderObj;
					VE_ASSERT_EQ(g_pRenderer->CreateRenderObject(pkObject, &spRenderObj), true);
					VE_ASSERT(spRenderObj);
					m_kRenderObjectArray.PushBack(spRenderObj);
					pkObject = pkObject->NextSiblingElement();
				}
			}
			VeXMLElement* pkNodeData = pkPlatform->FirstChildElement("NodeData");
			if(pkNodeData)
			{
				VeXMLElement* pkData = pkNodeData->FirstChildElement();
				while(pkData)
				{
					VeRenderNodeDataPtr spRenderNodeData;
					VE_ASSERT_EQ(g_pRenderer->CreateRenderNodeData(pkData, &spRenderNodeData), true);
					VE_ASSERT(spRenderNodeData);
					m_kRenderNodeDataArray.PushBack(spRenderNodeData);
					pkData = pkData->NextSiblingElement();
				}
			}
			VeXMLElement* pkNode = pkPlatform->FirstChildElement("Node");
			if(pkNode)
			{
				pkNode = pkNode->FirstChildElement();
				while(pkNode)
				{
					const VeChar8* pcName = pkNode->Value();
					const VeChar8* pcParent = pkNode->GetAttribute("parent");
					pcParent = pcParent ? pcParent : "";
					const VeChar8* pcData = pkNode->GetAttribute("data");
					pcData = pcData ? pcData : "";
					m_kNodeArray.Resize(m_kNodeArray.Size()+1);
					m_kNodeArray.Back().m_kName = pcName;
					m_kNodeArray.Back().m_kDataName = pcData;
					m_kNodeArray.Back().m_kParentName = pcParent;
					g_pMaterialManager->CreateRenderNode(pcName, pcData, pcParent);
					pkNode = pkNode->NextSiblingElement();
				}
			}
		}
		pkPlatform = pkPlatform->NextSiblingElement("Platform");
	}
	m_bNeedClear = true;
	return true;
}
//--------------------------------------------------------------------------
void VeMaterial::Clear()
{
	for(VeVector<VeRenderObjectPtr>::iterator it = m_kRenderObjectArray.Begin();
		it != m_kRenderObjectArray.End(); ++it)
	{
		if(g_pRenderer)
		{
			g_pRenderer->DelObject(*it);
		}
	}
	m_kRenderObjectArray.Clear();
	for(VeVector<VeRenderNodeDataPtr>::iterator it = m_kRenderNodeDataArray.Begin();
		it != m_kRenderNodeDataArray.End(); ++it)
	{
		if(g_pRenderer)
		{
			g_pRenderer->DelNodeData(*it);
		}
	}
	m_kRenderNodeDataArray.Clear();
	for(VeVector<Node>::iterator it = m_kNodeArray.Begin();
		it != m_kNodeArray.End(); ++it)
	{
		g_pMaterialManager->DestoryRenderNode(it->m_kName);
	}

	/*for(VeVector<Material>::iterator it = m_kMaterialArray.Begin();
	it != m_kMaterialArray.End(); ++it)
	{
	g_pMaterialManager->DelMat(it->m_kName);
	}
	m_kMaterialArray.Clear();*/
	m_bNeedClear = false;
}
//--------------------------------------------------------------------------
void VeMaterial::UpdatePlatform(VeBinaryIStream& kStream)
{
	VeUInt32 u32Temp;
	kStream >> u32Temp;
	for(VeUInt32 i(0); i < u32Temp; ++i)
	{
		VeRenderObjectPtr spRenderObj;
		VE_ASSERT_EQ(g_pRenderer->CreateRenderObject(kStream, &spRenderObj), true);
		VE_ASSERT(spRenderObj);
		m_kRenderObjectArray.PushBack(spRenderObj);
	}
	kStream >> u32Temp;
	for(VeUInt32 i(0); i < u32Temp; ++i)
	{
		VeStringA kName;
		kStream.GetStringAligned4(kName);
		VeRenderNodeDataPtr spNodeData;
		VE_ASSERT_EQ(g_pRenderer->CreateRenderNodeData(kName, kStream, &spNodeData), true);
		VE_ASSERT(spNodeData);
		m_kRenderNodeDataArray.PushBack(spNodeData);
	}
	kStream >> u32Temp;
	for(VeUInt32 i(0); i < u32Temp; ++i)
	{
		VeStringA kName;
		VeStringA kData;
		VeStringA kParent;
		kStream.GetStringAligned4(kName);
		kStream.GetStringAligned4(kData);
		kStream.GetStringAligned4(kParent);
		m_kNodeArray.Resize(m_kNodeArray.Size()+1);
		m_kNodeArray.Back().m_kName = kName;
		m_kNodeArray.Back().m_kDataName = kData;
		m_kNodeArray.Back().m_kParentName = kParent;
		g_pMaterialManager->CreateRenderNode(kName, kData, kParent);
	}
	kStream >> u32Temp;
	for(VeUInt32 i(0); i < u32Temp; ++i)
	{
		m_kMaterialArray.Resize(m_kMaterialArray.Size()+1);
		Material& kMat = m_kMaterialArray.Back();
		VeStringA kTemp;
		kStream.GetStringAligned4(kTemp);
		kMat.m_kName = kTemp;
		VeUInt32 u32Count;
		kStream >> u32Count;
		for(VeUInt32 j(0); j < u32Count; ++j)
		{
			kStream.GetStringAligned4(kTemp);
			kMat.m_kRenderNodeArray.PushBack(
				g_pMaterialManager->GetRenderNode(kTemp));
		}
		g_pMaterialManager->AddMat(kMat.m_kName, &kMat);
	}
}
//--------------------------------------------------------------------------
VeMaterialManager::VeMaterialManager()
{
	g_pResourceManager->SetResourceCreateFunction(VeResource::MATERIAL,
		VeMaterialResource::Create);
}
//--------------------------------------------------------------------------
VeMaterialManager::~VeMaterialManager()
{
	for(VeVector<VeRenderNode*>::iterator it = m_kRenderNodeSet.Begin();
		it != m_kRenderNodeSet.End(); ++it)
	{
		delete *it;
	}
	m_kRenderNodeSet.Clear();
	m_kRenderNodeMap.Clear();
	for(VeVector<VeMaterialPtr>::iterator it = m_kMaterialSet.Begin();
		it != m_kMaterialSet.End(); ++it)
	{
		(*it)->Clear();
	}
	m_kMaterialSet.Clear();
	m_kMaterialMap.Clear();
}
//--------------------------------------------------------------------------
void VeMaterialManager::LoadShaderList(const VeChar8* pcPath)
{
	VeResourceGroupPtr spShaderGroup = VE_NEW VeResourceGroup("Shaders");
	VE_ASSERT(spShaderGroup);
	spShaderGroup->PushReadDirectoryBack(pcPath);
	VeXMLDocument kDoc;
	{
		VeDirectory* pkDir = g_pResourceManager->CreateDir(pcPath);
		VE_ASSERT(pkDir);
		VeBinaryIStreamPtr spStream = pkDir->OpenSync("ShaderList.xml");
		(*spStream) >> kDoc;
		VE_ASSERT(!kDoc.Error());
		g_pResourceManager->DestoryDir(pkDir);
	}
	VeXMLElement* pkRoot = kDoc.RootElement();
	if(pkRoot)
	{
		VeXMLElement* pkPlatform = pkRoot->FirstChildElement("Platform");
		while(pkPlatform)
		{
			if(pkPlatform->Attribute(VE_PLATFORM_NAME_LITE, true))
			{
				VeXMLElement* pkVertexShader = pkPlatform->FirstChildElement("VertexShader");
				if(pkVertexShader)
				{
					VeXMLElement* pkShader = pkVertexShader->FirstChildElement();
					while(pkShader)
					{
						VE_ASSERT_NOT_EQ(VeLoadVertexShaderSync(pkShader->Value(), "Shaders"), NULL);
						pkShader = pkShader->NextSiblingElement();
					}
				}
				VeXMLElement* pkPixelShader = pkPlatform->FirstChildElement("PixelShader");
				if(pkPixelShader)
				{
					
					VeXMLElement* pkShader = pkPixelShader->FirstChildElement();
					while(pkShader)
					{
						VE_ASSERT_NOT_EQ(VeLoadPixelShaderSync(pkShader->Value(), "Shaders"), NULL);
						pkShader = pkShader->NextSiblingElement();
					}
				}
			}
			pkPlatform = pkPlatform->NextSiblingElement("Platform");
		}
	}
}
//--------------------------------------------------------------------------
VeRenderNode* VeMaterialManager::CreateRenderNode(const VeChar8* pcName,
	const VeChar8* pcData, const VeChar8* pcParent)
{
	VeRenderNode* pkNode = VE_NEW VeRenderNode(pcData);
	pkNode->SetName(pcName);
	VeStringMap<VeUInt32>::iterator it = m_kRenderNodeMap.Find(pcParent);
	if(it)
	{
		pkNode->SetParent(m_kRenderNodeSet[*it]);
	}
	VE_ASSERT(!m_kRenderNodeMap.Find(pcName));
	m_kRenderNodeMap[pcName] = m_kRenderNodeSet.Size();
	m_kRenderNodeSet.PushBack(pkNode);
	return pkNode;
}
//--------------------------------------------------------------------------
void VeMaterialManager::DestoryRenderNode(const VeChar8* pcName)
{
	VeStringMap<VeUInt32>::iterator it = m_kRenderNodeMap.Find(pcName);
	if(it)
	{
		VE_SAFE_DELETE(m_kRenderNodeSet[*it]);
		if((*it) < (m_kRenderNodeSet.Size() - 1))
		{
			VeRenderNode* pkNode = m_kRenderNodeSet.Back();
			m_kRenderNodeMap[pkNode->m_kName] = *it;
			m_kRenderNodeSet[*it] = pkNode;
		}
		m_kRenderNodeMap.Remove(pcName);
		m_kRenderNodeSet.PopBack();
	}
}
//--------------------------------------------------------------------------
