////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTextTable.cpp
//  Version:     v1.00
//  Created:     18/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeTextTable.inl"
#endif

extern "C"
{
#	include <lua.h>
#	include <lauxlib.h>
#	include <lualib.h>
}

//--------------------------------------------------------------------------
VeChar8* RemoveQuote(VeChar8* pcStr)
{
	VeSizeT stLen = VeStrlen(pcStr);
	if(*pcStr == '\"')
	{
		pcStr[stLen - 1] = '\0';
		return pcStr + 1;
	}
	else
	{
		return pcStr;
	}
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeTextTable, VeResource);
//--------------------------------------------------------------------------
VeTextTable::VeTextTable(const VeChar8* pcName, const VeChar8* pcGroup)
	: VeResource(TEXT_TABLE, pcName, pcGroup)
{

}
//--------------------------------------------------------------------------
VeTextTable::~VeTextTable()
{
	Unload();
}
//--------------------------------------------------------------------------
VeUInt32 VeTextTable::GetRowIndex(const VeChar8* pcName)
{
	VeUInt32* pu32Iter = m_kStrMap.Find(pcName);
	return pu32Iter ? *pu32Iter : VE_INFINITE;
}
//--------------------------------------------------------------------------
VeUInt32 VeTextTable::GetRowIndex(VeInt32 i32Index)
{
	VeUInt32* pu32Iter = m_kIntMap.Find(i32Index);
	return pu32Iter ? *pu32Iter : VE_INFINITE;
}
//--------------------------------------------------------------------------
VeUInt32 VeTextTable::GetColIndex(const VeChar8* pcName)
{
	VeUInt32* pu32Iter = m_kFieldMap.Find(pcName);
	return pu32Iter ? *pu32Iter : VE_INFINITE;
}
//--------------------------------------------------------------------------
VeTextTable::Field* VeTextTable::GetField(VeUInt32 u32Index)
{
	return u32Index < m_kFieldMap.Size() ? (&m_kFieldArray[u32Index]) : NULL; 
}
//--------------------------------------------------------------------------
const VeChar8* VeTextTable::GetStr(VeUInt32 u32Row, VeUInt32 u32Col)
{
	const VeVector<Value>* pkRow = Get(u32Row);
	return (pkRow && (u32Col < pkRow->Size())) ? (*pkRow)[u32Col].GetStr() : "";
}
//--------------------------------------------------------------------------
VeInt32 VeTextTable::GetInt(VeUInt32 u32Row, VeUInt32 u32Col)
{
	const VeVector<Value>* pkRow = Get(u32Row);
	return (pkRow && (u32Col < pkRow->Size())) ? (*pkRow)[u32Col].GetInt() : 0;
}
//--------------------------------------------------------------------------
const VeVector<VeTextTable::Value>* VeTextTable::Get(VeUInt32 u32Row)
{
	return u32Row < m_kData.Size() ? &(m_kData[u32Row]) : NULL;
}
//--------------------------------------------------------------------------
VeTextTable::State VeTextTable::LoadImpl(const VeMemoryIStreamPtr& spStream)
{
	return LOADED;
}
//--------------------------------------------------------------------------
void VeTextTable::UnloadImpl()
{

}
//--------------------------------------------------------------------------
bool VeTextTable::HasProcess()
{
	return true;
}
//--------------------------------------------------------------------------
void VeTextTable::LoadProcess(const VeMemoryIStreamPtr& spStream)
{
	VeChar8* pcData = (VeChar8*)(void*)(*spStream->GetBlob());
	if(VeByte(pcData[0]) == 0xEF && VeByte(pcData[1]) == 0xBB
		&& VeByte(pcData[2]) == 0xBF)
	{
		ParseUTF8(pcData + 3);
	}
	else if(VeByte(pcData[0]) == 0xFF && VeByte(pcData[1]) == 0xFE)
	{
		ParseUnicode16((VeChar16*)(pcData + 2));
	}
	spStream->Finish();
}
//--------------------------------------------------------------------------
void VeTextTable::ParseUTF8(const VeChar8* pcData)
{
	VeVector<VeChar8> kBuffer;
	pcData += StrLine(kBuffer, pcData);
	VeChar8* pcContent;
	VeChar8* pcTemp = VeStrtok(&kBuffer[0], "\t", &pcContent);
	while(pcTemp)
	{
		m_kFieldArray.Increase();
		pcTemp = RemoveQuote(pcTemp);
		VeChar8* pcCont;
		VeStrtok(pcTemp, "(", &pcCont);
		m_kFieldArray.Back().m_kName = VeStrtok(NULL, ",", &pcCont);
		m_kFieldArray.Back().m_eType = TypeLua::ToEnum(VeStrtok(NULL, ")", &pcCont), TYPE_STR);
		m_kFieldMap[m_kFieldArray.Back().m_kName] = m_kFieldArray.Size() - 1;
		pcTemp = VeStrtok(NULL, "\t", &pcContent);
	}

	Type eType = m_kFieldArray.Front().m_eType;

	while(*pcData) 
	{
		pcData += StrLine(kBuffer, pcData);
		pcTemp = VeStrtok(&kBuffer[0], "\t", &pcContent);
		if(pcTemp)
		{
			pcTemp = RemoveQuote(pcTemp);
			m_kData.Increase();
			VeVector<Value>& kRow = m_kData.Back();
			if(eType == TYPE_INT)
			{
				kRow.Increase();
				VeInt32 i32Index = VeAtoi(pcTemp);
				kRow.Back().Set(i32Index);
				m_kIntMap[i32Index] = m_kData.Size() - 1;
			}
			else
			{
				VE_ASSERT(eType == TYPE_STR);
				kRow.Increase();
				kRow.Back().Set(pcTemp);
				m_kStrMap[pcTemp] = m_kData.Size() - 1;
			}

			pcTemp = VeStrtok(NULL, "\t", &pcContent);
			while(pcTemp)
			{
				pcTemp = RemoveQuote(pcTemp);
				if(eType == TYPE_INT)
				{
					kRow.Increase();
					kRow.Back().Set(VeAtoi(pcTemp));
				}
				else
				{
					VE_ASSERT(eType == TYPE_STR);
					kRow.Increase();
					kRow.Back().Set(pcTemp);
				}
				pcTemp = VeStrtok(NULL, "\t", &pcContent);
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeTextTable::ParseUnicode16(const VeChar16* pcData)
{
	VeVector<VeChar8> kBuffer;
	pcData = (const VeChar16*)((const VeUInt16*)pcData + StrLine(kBuffer, pcData));
	VeChar8* pcContent;
	VeChar8* pcTemp = VeStrtok(&kBuffer[0], "\t", &pcContent);
	while(pcTemp)
	{
		m_kFieldArray.Increase();
		pcTemp = RemoveQuote(pcTemp);
		VeChar8* pcCont;
		VeStrtok(pcTemp, "(", &pcCont);
		Field& kField = m_kFieldArray.Back();
		kField.m_kName = VeStrtok(pcCont, ",", &pcCont);
		kField.m_eType = TypeLua::ToEnum(VeStrtok(NULL, ")", &pcCont), TYPE_STR);
		m_kFieldMap[kField.m_kName] = m_kFieldArray.Size() - 1;
		pcTemp = VeStrtok(NULL, "\t", &pcContent);
	}

	Type eIndexType = m_kFieldArray.Front().m_eType;
	while(*(VeUInt16*)pcData)
	{
		pcData = (const VeChar16*)((const VeUInt16*)pcData + StrLine(kBuffer, pcData));
		pcTemp = VeStrtok(&kBuffer[0], "\t", &pcContent);
		if(pcTemp)
		{
			pcTemp = RemoveQuote(pcTemp);
			m_kData.Increase();
			VeVector<Value>& kRow = m_kData.Back();
			if(eIndexType == TYPE_INT)
			{
				kRow.Increase();
				VeInt32 i32Index = VeAtoi(pcTemp);
				kRow.Back().Set(i32Index);
				m_kIntMap[i32Index] = m_kData.Size() - 1;
			}
			else
			{
				VE_ASSERT(eIndexType == TYPE_STR);
				kRow.Increase();
				kRow.Back().Set(pcTemp);
				m_kStrMap[pcTemp] = m_kData.Size() - 1;
			}
			pcTemp = VeStrtok(NULL, "\t", &pcContent);
			VeUInt32 i(0);
			while(pcTemp)
			{
				Type eType = m_kFieldArray[++i].m_eType;
				pcTemp = RemoveQuote(pcTemp);
				if(eType == TYPE_INT)
				{
					kRow.Increase();
					kRow.Back().Set(VeAtoi(pcTemp));
				}
				else
				{
					VE_ASSERT(eType == TYPE_STR);
					kRow.Increase();
					kRow.Back().Set(pcTemp);
				}
				pcTemp = VeStrtok(NULL, "\t", &pcContent);
			}
		}

	}
}
//--------------------------------------------------------------------------
VeUInt32 VeTextTable::StrLine(VeVector<VeChar8>& kDst, const VeChar8* pcSrc)
{
	kDst.Clear();
	const VeChar8* pcPointer = pcSrc;
	while(true)
	{
		switch(*pcPointer)
		{
		case '\\':
			switch(*(pcPointer+1))
			{
			case 'a':
				kDst.PushBack('\a');
				pcPointer += 2;
				break;
			case 'b':
				kDst.PushBack('\b');
				pcPointer += 2;
				break;
			case 'f':
				kDst.PushBack('\f');
				pcPointer += 2;
				break;
			case 'n':
				kDst.PushBack('\n');
				pcPointer += 2;
				break;
			case 'r':
				kDst.PushBack('\r');
				pcPointer += 2;
				break;
			case 't':
				kDst.PushBack('\t');
				pcPointer += 2;
				break;
			case 'v':
				kDst.PushBack('\v');
				pcPointer += 2;
				break;
			case '\\':
				kDst.PushBack('\\');
				pcPointer += 2;
				break;
			case '\'':
				kDst.PushBack('\'');
				pcPointer += 2;
				break;
			case '\"':
				kDst.PushBack('\"');
				pcPointer += 2;
				break;
			default:
				kDst.PushBack('\\');
				++pcPointer;
				break;
			}
			break;
		case '\r':
			kDst.PushBack('\0');
			if(*(pcPointer + 1) == '\n') pcPointer += 2;
			else ++pcPointer;
			return VeUInt32(pcPointer - pcSrc);
		case '\n':
			kDst.PushBack('\0');
			++pcPointer;
			return VeUInt32(pcPointer - pcSrc);
		case '\0':
			kDst.PushBack('\0');
			return VeUInt32(pcPointer - pcSrc);
		default:
			kDst.PushBack(*pcPointer);
			++pcPointer;
			break;
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeUInt32 VeTextTable::StrLine(VeVector<VeChar8>& kDst,
	const VeChar16* pcSrc)
{
	kDst.Clear();
	const VeUInt16* pcPointer = (VeUInt16*)pcSrc;
	while(true)
	{
		switch(VeUInt16(*pcPointer))
		{
		case 0x5C:
			switch(*(pcPointer+1))
			{
			case 0x61:
				kDst.PushBack('\a');
				pcPointer += 2;
				break;
			case 0x62:
				kDst.PushBack('\b');
				pcPointer += 2;
				break;
			case 0x66:
				kDst.PushBack('\f');
				pcPointer += 2;
				break;
			case 0x6E:
				kDst.PushBack('\n');
				pcPointer += 2;
				break;
			case 0x72:
				kDst.PushBack('\r');
				pcPointer += 2;
				break;
			case 0x74:
				kDst.PushBack('\t');
				pcPointer += 2;
				break;
			case 0x76:
				kDst.PushBack('\v');
				pcPointer += 2;
				break;
			case 0x5C:
				kDst.PushBack('\\');
				pcPointer += 2;
				break;
			case 0x27:
				kDst.PushBack('\'');
				pcPointer += 2;
				break;
			case 0x22:
				kDst.PushBack('\"');
				pcPointer += 2;
				break;
			default:
				kDst.PushBack('\\');
				++pcPointer;
				break;
			}
			break;
		case 0x0D:
			kDst.PushBack('\0');
			if(*(pcPointer + 1) == 0x0A) pcPointer += 2;
			else ++pcPointer;
			return VeUInt32(pcPointer - (VeUInt16*)pcSrc);
		case 0x0A:
			kDst.PushBack('\0');
			++pcPointer;
			return VeUInt32(pcPointer - (VeUInt16*)pcSrc);
		case 0x00:
			kDst.PushBack('\0');
			return VeUInt32(pcPointer - (VeUInt16*)pcSrc);
		default:
			AddUnicode16(kDst, *pcPointer);
			++pcPointer;
			break;
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
void VeTextTable::AddUnicode16(VeVector<VeChar8>& kDst,
	const VeChar16 c16Char)
{
	if(VeUInt16(c16Char) <= 0x7F)
	{
		kDst.PushBack((VeChar8)c16Char);
	}
	else if(VeUInt16(c16Char) <= 0x7FF)
	{
		kDst.PushBack((VeChar8)((VeUInt16(c16Char) >> 6) | 0xC0));
		kDst.PushBack((VeChar8)((VeUInt16(c16Char) | 0x80) & 0xBF));
	}
	else
	{
		kDst.PushBack((VeChar8)((VeUInt16(c16Char) >> 12) | 0xE0));
		kDst.PushBack((VeChar8)(((VeUInt16(c16Char) >> 6) | 0x80) & 0xBF));
		kDst.PushBack((VeChar8)((VeUInt16(c16Char) | 0x80) & 0xBF));
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeTextTable::GetStr(const VeChar8* pcTable,
	const VeChar8* pcRow, const VeChar8* pcCol)
{
	VeTextTablePtr spTable = VeGetTextTable(pcTable, g_pResourceManager->GetDefaultGroupName());
	if(spTable && spTable->GetState() == VeResource::LOADED)
	{
		return spTable->GetStr(pcRow, pcCol);
	}
	else
	{
		return "";
	}
}
//--------------------------------------------------------------------------
VeResource* VeTextTable::CreateResource(const VeChar8* pcName,
	const VeChar8* pcGroup)
{
	return VE_NEW VeTextTable(pcName, pcGroup);
}
//--------------------------------------------------------------------------
void GetRowStr(lua_State* pkState, const VeChar8* pcTable, const VeChar8* pcRow)
{
	VeTextTablePtr spTable = VeGetTextTable(pcTable, g_pResourceManager->GetDefaultGroupName());
	if(spTable && spTable->GetState() == VeResource::LOADED)
	{
		const VeVector<VeTextTable::Value>* pkRow = spTable->Get(pcRow);
		if(pkRow)
		{
			VeLuaBind::NewTable(pkState);
			for(VeUInt32 i(0); i < pkRow->Size(); ++i)
			{
				if(i < spTable->GetField().Size())
				{
					const VeTextTable::Field& kField = spTable->GetField()[i];
					const VeTextTable::Value& kValue = (*pkRow)[i];
					lua_pushstring(pkState, kField.m_kName);
					if(kField.m_eType == VeTextTable::TYPE_INT)
					{
						lua_pushnumber(pkState, kValue.GetInt());
					}
					else
					{
						lua_pushstring(pkState, kValue.GetStr());
					}
					lua_rawset(pkState, -3);
					if(kField.m_eType == VeTextTable::TYPE_INT)
					{
						lua_pushnumber(pkState, kValue.GetInt());
					}
					else
					{
						lua_pushstring(pkState, kValue.GetStr());
					}
					lua_rawseti(pkState, -2, i + 1);
				}
			}
			VeLuaBind::ManualReturn(1);

		}
		else
		{
			VeLuaBind::ManualReturn(0);
		}
	}
}
//--------------------------------------------------------------------------
void GetRowInt(lua_State* pkState, const VeChar8* pcTable, VeInt32 i32Row)
{
	VeTextTablePtr spTable = VeGetTextTable(pcTable, g_pResourceManager->GetDefaultGroupName());
	if(spTable && spTable->GetState() == VeResource::LOADED)
	{
		const VeVector<VeTextTable::Value>* pkRow = spTable->GetFromIndex(i32Row);
		if(pkRow)
		{
			VeLuaBind::NewTable(pkState);
			for(VeUInt32 i(0); i < pkRow->Size(); ++i)
			{
				if(i < spTable->GetField().Size())
				{
					const VeTextTable::Field& kField = spTable->GetField()[i];
					const VeTextTable::Value& kValue = (*pkRow)[i];
					lua_pushstring(pkState, kField.m_kName);
					if(kField.m_eType == VeTextTable::TYPE_INT)
					{
						lua_pushnumber(pkState, kValue.GetInt());
					}
					else
					{
						lua_pushstring(pkState, kValue.GetStr());
					}
					lua_rawset(pkState, -3);
					if(kField.m_eType == VeTextTable::TYPE_INT)
					{
						lua_pushnumber(pkState, kValue.GetInt());
					}
					else
					{
						lua_pushstring(pkState, kValue.GetStr());
					}
					lua_rawseti(pkState, -2, i + 1);
				}
			}
			VeLuaBind::ManualReturn(1);

		}
		else
		{
			VeLuaBind::ManualReturn(0);
		}
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeTextTable)
{
	Module() [
		Class<VeTextTable>() [
			Def("GetRow", &GetRowStr),
			Def("GetRow", &GetRowInt)
		]
	];
}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeTextTable, Type);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeTextTable, Type)
{
	VeLuaClassEnumBase(VeTextTable, Type);
	VeLuaClassEnumSlot(VeTextTable, Type, TYPE_INT, "int");
	VeLuaClassEnumSlot(VeTextTable, Type, TYPE_STR, "str");
}
//--------------------------------------------------------------------------
VeTextTable::Value::Value() : m_eType(TYPE_MAX), m_i32Int(0)
{

}
//--------------------------------------------------------------------------
VeTextTable::Value::~Value()
{
	if(m_eType == TYPE_STR && m_pcStr)
	{
		VeFree(m_pcStr);
		m_pcStr = NULL;
	}
}
//--------------------------------------------------------------------------
void VeTextTable::Value::Set(const VeChar8* pcStr)
{
	VeSizeT stLen = VeStrlen(pcStr);
	if(m_eType == TYPE_STR && m_pcStr)
	{
		m_pcStr = (VeChar8*)VeRealloc(m_pcStr, stLen + 1);
	}
	else
	{
		m_pcStr = VeAlloc(VeChar8, stLen + 1);
	}
	VeMemcpy(m_pcStr, pcStr, stLen);
	m_pcStr[stLen] = 0;
	m_eType = TYPE_STR;
}
//--------------------------------------------------------------------------
void VeTextTable::Value::Set(VeInt32 i32Int)
{
	if(m_eType == TYPE_STR && m_pcStr)
	{
		VeFree(m_pcStr);
	}
	m_i32Int = i32Int;
	m_eType = TYPE_INT;
}
//--------------------------------------------------------------------------
VeInt32 VeTextTable::Value::GetInt() const
{
	return m_eType == TYPE_INT ? m_i32Int : 0;
}
//--------------------------------------------------------------------------
const VeChar8* VeTextTable::Value::GetStr() const
{
	return m_eType == TYPE_STR ? m_pcStr : "";
}
//--------------------------------------------------------------------------
