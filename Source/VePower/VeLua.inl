////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeLua.inl
//  Version:     v1.00
//  Created:     26/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE bool VeLua::IsDebug()
{
	return m_bDebug ? true : false;
}
//--------------------------------------------------------------------------
VE_INLINE lua_State* VeLua::GetLua()
{
	return m_pkLua;
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeLua::GetTop()
{
	return GetTop(m_pkLua);
}
//--------------------------------------------------------------------------
VE_INLINE void VeLua::SetTop(VeInt32 i32Value)
{
	return SetTop(m_pkLua, i32Value);
}
//--------------------------------------------------------------------------
VE_INLINE VeUInt32 VeLua::GetLoadTaskNum()
{
	return m_kTaskList.Size();
}
//--------------------------------------------------------------------------
