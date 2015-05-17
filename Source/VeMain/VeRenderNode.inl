////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRenderNode.inl
//  Version:     v1.00
//  Created:     7/12/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeRenderTick::Type VeRenderTick::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE VeRenderCall::Type VeRenderCall::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE void VeDrawCall::SetType(Type eType)
{
	VE_ASSERT(eType);
	m_eType = eType;
}
//--------------------------------------------------------------------------
VE_INLINE void VeRenderNodeData::AddRenderTick(VeRenderTick& kTick)
{
	m_kTickList.AttachBack(kTick);
}
//--------------------------------------------------------------------------
VE_INLINE void VeRenderNodeData::AddRenderCall(VeRenderCall& kCall)
{
	m_kCallList.AttachBack(kCall);
}
//--------------------------------------------------------------------------
VE_INLINE void VeRenderNode::SetName(const VeChar8* pcName)
{
	m_kName = pcName;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeRenderNode::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE void VeRenderNode::SetData(const VeRenderNodeDataPtr& spData)
{
	m_spData = spData;
}
//--------------------------------------------------------------------------
VE_INLINE const VeRenderNodeDataPtr& VeRenderNode::GetData()
{
	return m_spData;
}
//--------------------------------------------------------------------------
VE_INLINE void VeRenderNode::SetParent(VeRenderNode* pkParent)
{
	m_pkParent = pkParent;
}
//--------------------------------------------------------------------------
VE_INLINE VeRenderNode* VeRenderNode::GetParent()
{
	return m_pkParent;
}
//--------------------------------------------------------------------------
VE_INLINE void VeRenderNode::SetPriority(VeUInt32 u32Priority)
{
	m_u32Priority = u32Priority;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeRenderNode::GetPriority()
{
	return m_u32Priority;
}
//--------------------------------------------------------------------------
VE_INLINE VeRenderProcess::Type VeRenderProcess::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeRenderProcess::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
