////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeResource.inl
//  Version:     v1.00
//  Created:     14/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeResource::GetGroup()
{
	return m_spGroup ? m_spGroup->GetName() : NULL;
}
//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeResource::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VE_INLINE VeResource::Type VeResource::GetType()
{
	return m_eType;
}
//--------------------------------------------------------------------------
VE_INLINE VeResource::State VeResource::GetState()
{
	return m_eState;
}
//--------------------------------------------------------------------------
VE_INLINE void VeResource::AddLoadDelegate(LoadDelegate& kDelegate)
{
	if(m_eState == LOADED)
	{
		kDelegate.Callback(this);
	}
	else
	{
		m_kLoadEvent.AddDelegate(kDelegate);
	}
}
//--------------------------------------------------------------------------
VE_INLINE bool VeResource::IsFreeListEnable()
{
	return m_kFreeNode.m_tContent ? true : false;
}
//--------------------------------------------------------------------------
