////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTextTable.inl
//  Version:     v1.00
//  Created:     18/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE const VeChar8* VeTextTable::GetStr(const VeChar8* pcRow,
	const VeChar8* pcCol)
{
	return GetStr(GetRowIndex(pcRow), GetColIndex(pcCol));
}
//--------------------------------------------------------------------------
VE_INLINE VeInt32 VeTextTable::GetInt(const VeChar8* pcRow,
	const VeChar8* pcCol)
{
	return GetInt(GetRowIndex(pcRow), GetColIndex(pcCol));
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector<VeTextTable::Field>& VeTextTable::GetField() const
{
	return m_kFieldArray;
}
//--------------------------------------------------------------------------
VE_INLINE VeTextTable::Field* VeTextTable::GetField(const VeChar8* pcCol)
{
	return GetField(GetColIndex(pcCol));
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector<VeTextTable::Value>* VeTextTable::Get(
	const VeChar8* pcRow)
{
	return Get(GetRowIndex(pcRow));
}
//--------------------------------------------------------------------------
VE_INLINE const VeVector<VeTextTable::Value>* VeTextTable::GetFromIndex(
	VeInt32 i32Index)
{
	return Get(GetRowIndex(i32Index));
}
//--------------------------------------------------------------------------
