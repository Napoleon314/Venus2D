////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeDragonBones.inl
//  Version:     v1.00
//  Created:     17/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeDragonBonesEntity::GetArmatureIndex(
	const VeChar8* pcName)
{
	VE_ASSERT(pcName);
	const VeUInt32* pu32Index = m_kArmatureMap.Find(pcName);
	return pu32Index ? *pu32Index : VE_INFINITE;
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeDragonBonesEntity::GetArmatureSize()
{
	return m_kArmatureMap.Size();
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeDragonBonesEntity::GetAnimationIndex(
	const VeChar8* pcName, VeUInt32 u32Armature)
{
	if(u32Armature < GetArmatureSize())
	{
		const VeUInt32* pu32Index = m_kArmatureList[u32Armature]->m_pkRes->m_kAnimationMap.Find(pcName);
		return pu32Index ? *pu32Index : VE_INFINITE;
	}
	else
	{
		return VE_INFINITE;
	}
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeDragonBonesEntity::GetAnimationSize(
	VeUInt32 u32Armature)
{
	if(u32Armature < GetArmatureSize())
	{
		return m_kArmatureList[u32Armature]->m_pkRes->m_kAnimationList.Size();
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------------------------------
VE_INLINE void VeDragonBonesEntity::RegisterListener(Delegate& kDelegate)
{
	m_kEvent.AddDelegate(kDelegate);
}
//--------------------------------------------------------------------------
VE_INLINE void VeDragonBonesEntity::UnregisterListener(Delegate& kDelegate)
{
	m_kEvent.DelDelegate(kDelegate);
}
//--------------------------------------------------------------------------
