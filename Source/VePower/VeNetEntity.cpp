////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeNetEntity.cpp
//  Version:     v1.00
//  Created:     6/11/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"
#ifdef VE_NO_INLINE
#	include "VeNetEntity.inl"
#endif

extern "C"
{
#	include <lua.h>
#	include <lauxlib.h>
#	include <lualib.h>
}

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

using namespace RakNet;

//--------------------------------------------------------------------------
VeNetEntity::VeNetEntity()
	: m_u32Index(0), m_eType(TYPE_MAX), m_eStore(STORE_MAX)
	, m_i32UpdateFunc(0)
{

}
//--------------------------------------------------------------------------
VeNetEntity::~VeNetEntity()
{

}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(Property& kProperty)
{
	switch(kProperty.GetType())
	{
	case Property::TYPE_VALUE:
		return CreateData((Value&)kProperty);
	case Property::TYPE_ENUM:
		return CreateData((Enum&)kProperty);
	case Property::TYPE_STRUCT:
		return CreateData((Struct&)kProperty);
	case Property::TYPE_ARRAY:
		return CreateData((Array&)kProperty);
	default:
		break;
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(Value& kValue)
{
	DataValue* pkData = VE_NEW DataValue;
	pkData->m_pkObject = &kValue;
	if(kValue.m_eType < VALUE_VeInt8)
	{
		pkData->m_u64Value = kValue.m_u64Default;
	}
	else if(kValue.m_eType < VALUE_VeFloat32)
	{
		pkData->m_i64Value = kValue.m_i64Default;
	}
	else if(kValue.m_eType < VALUE_VeString)
	{
		pkData->m_f64Value = kValue.m_f64Default;
	}
	else
	{
		VE_ASSERT(kValue.m_eType == VALUE_VeString);
		VeUInt16 u16Len = *(VeUInt16*)(kValue.m_pbyBuffer);
		pkData->m_pbyBuffer = VeAlloc(VeByte, u16Len + 3);
		*(VeUInt16*)pkData->m_pbyBuffer = u16Len;
		VeMemcpy(pkData->m_pbyBuffer + 2, kValue.m_pbyBuffer + 2, u16Len + 1);
	}
	return pkData;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(Enum& kEnum)
{
	DataEnum* pkData = VE_NEW DataEnum;
	pkData->m_pkObject = &kEnum;
	pkData->m_u8Value = kEnum.m_u8Default;
	return pkData;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(Struct& kStruct)
{
	DataStruct* pkStruct = VE_NEW DataStruct;
	pkStruct->m_pkObject = &kStruct;
	for(VeUInt32 i(0); i < kStruct.m_kProperties.Size(); ++i)
	{
		DataPtr spData = CreateData(*kStruct.m_kProperties[i]);
		VE_ASSERT(spData);
		spData->m_u32Index = i;
		spData->m_pkHolder = pkStruct;
		pkStruct->m_kDataArray.PushBack(spData);
	}
	return pkStruct;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(Array& kArray)
{
	DataArray* pkArray = VE_NEW DataArray;
	pkArray->m_pkObject = &kArray;
	return pkArray;
}
//--------------------------------------------------------------------------
VeSizeT VeNetEntity::ToString(VeChar8* pcDesc, Data& kData)
{
	switch(kData.GetType())
	{
	case Data::TYPE_VALUE:
		return ToString(pcDesc, (DataValue&)kData);
	case Data::TYPE_ENUM:
		return ToString(pcDesc, (DataEnum&)kData);
	case Data::TYPE_STRUCT:
		return ToString(pcDesc, (DataStruct&)kData);
	case Data::TYPE_ARRAY:
		return ToString(pcDesc, (DataArray&)kData);
	case Data::TYPE_ENTITY:
		return ToString(pcDesc, (DataEntity&)kData);
	default:
		break;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeSizeT VeNetEntity::ToString(VeChar8* pcDesc, DataValue& kData)
{
	VeChar8* pcPointer = pcDesc;
	Value& kValue = *(Value*)kData.m_pkObject;
	if(kValue.m_eType < VALUE_VeInt8)
	{
		pcPointer += VeSprintf(pcPointer, 256, "%llu", kData.m_u64Value);
	}
	else if(kValue.m_eType < VALUE_VeFloat32)
	{
		pcPointer += VeSprintf(pcPointer, 256, "%ll", kData.m_i64Value);
	}
	else if(kValue.m_eType < VALUE_VeString)
	{
		pcPointer += VeSprintf(pcPointer, 256, "%f", kData.m_f64Value);
	}
	else if(kValue.m_eType == VALUE_VeString)
	{
		pcPointer += VeSprintf(pcPointer, 256, "\"%s\"", kData.m_pbyBuffer + 2);
	}
	return pcPointer - pcDesc;
}
//--------------------------------------------------------------------------
VeSizeT VeNetEntity::ToString(VeChar8* pcDesc, DataEnum& kData)
{
	VeChar8* pcPointer = pcDesc;
	Enum& kEnum = (Enum&)*kData.m_pkObject;
	if(kData.m_u8Value < kEnum.m_kDesc.m_kIntToStr.Size())
	{
		pcPointer += VeSprintf(pcPointer, 256, "%s", (const VeChar8*)(kEnum.m_kDesc.m_kIntToStr[kData.m_u8Value]));
	}
	return pcPointer - pcDesc;
}
//--------------------------------------------------------------------------
VeSizeT VeNetEntity::ToString(VeChar8* pcDesc, DataStruct& kData)
{
	VeChar8* pcPointer = pcDesc;
	pcPointer += VeSprintf(pcPointer, 256, "{");
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		if(i) pcPointer += VeSprintf(pcPointer, 256, ",");
		pcPointer += ToString(pcPointer, *kData.m_kDataArray[i]);
	}
	pcPointer += VeSprintf(pcPointer, 256, "}");
	return pcPointer - pcDesc;
}
//--------------------------------------------------------------------------
VeSizeT VeNetEntity::ToString(VeChar8* pcDesc, DataArray& kData)
{
	VeChar8* pcPointer = pcDesc;
	pcPointer += VeSprintf(pcPointer, 256, "[");
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		if(i) pcPointer += VeSprintf(pcPointer, 256, ",");
		pcPointer += ToString(pcPointer, *kData.m_kDataArray[i].m_tSecond);
	}
	pcPointer += VeSprintf(pcPointer, 256, "]");
	return pcPointer - pcDesc;
}
//--------------------------------------------------------------------------
VeSizeT VeNetEntity::ToString(VeChar8* pcDesc, DataEntity& kData)
{
	VeChar8* pcPointer = pcDesc;
	VeNetEntity& kEntity = *(VeNetEntity*)kData.m_pkObject;
	pcPointer += VeSprintf(pcPointer, 256, "%s(", (const VeChar8*)kEntity.m_kName);
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		if(i) pcPointer += VeSprintf(pcPointer, 256, ",");
		pcPointer += ToString(pcPointer, *kData.m_kDataArray[i]);
		
	}
	pcPointer += VeSprintf(pcPointer, 256, ")");
	return pcPointer - pcDesc;
}
//--------------------------------------------------------------------------
bool VeNetEntity::Write(BitStream& kOut, lua_State* pkState,
	const Value& kType)
{
	switch(kType.m_eType)
	{
	case VALUE_VeUInt8:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeUInt8(lua_tounsigned(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeUInt16:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeUInt16(lua_tounsigned(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeUInt32:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeUInt32(lua_tounsigned(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeUInt64:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeUInt64(lua_tonumber(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeInt8:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeInt8(lua_tointeger(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeInt16:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeInt16(lua_tointeger(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeInt32:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeInt32(lua_tointeger(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeInt64:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeInt64(lua_tonumber(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeFloat32:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeFloat32(lua_tonumber(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeFloat64:
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			kOut.Write(VeFloat64(lua_tonumber(pkState, -1)));
			return true;
		}
		break;
	case VALUE_VeString:
		if(lua_type(pkState, -1) == LUA_TSTRING)
		{
			VeSizeT stLen;
			const VeChar8* pcStr = lua_tolstring(pkState, -1, &stLen);
			stLen = VE_MIN(stLen, 255);
			::Write(kOut, pcStr, VeUInt32(stLen));
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeNetEntity::Write(BitStream& kOut, lua_State* pkState,
	const Enum& kType)
{
	VeInt32 i32Type = lua_type(pkState, -1);
	if(i32Type == LUA_TNUMBER)
	{
		VeUInt8 u8Value = (VeUInt8)lua_tounsigned(pkState, -1);
		if(u8Value < kType.m_kDesc.m_kIntToStr.Size())
		{
			kOut.Write(u8Value);
			return true;
		}
	}
	else if(i32Type == LUA_TSTRING)
	{
		const VeChar8* pcValue = lua_tostring(pkState, -1);
		const VeUInt8* pu8Iter = kType.m_kDesc.m_kStrToInt.Find(pcValue);
		if(pu8Iter)
		{
			kOut.Write(*pu8Iter);
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeNetEntity::Write(BitStream& kOut, lua_State* pkState,
	const Struct& kType)
{
	if(lua_type(pkState, -1) != LUA_TTABLE) return false;
	for(VeUInt32 i(0); i < kType.m_kProperties.Size(); ++i)
	{
		lua_rawgeti(pkState, -1, i + 1);
		if(lua_type(pkState, -1) == LUA_TNIL)
		{
			Write(kOut, *kType.m_kProperties[i]);
			lua_pop(pkState, 1);
			break;
		}
		else
		{
			bool bRes = Write(kOut, pkState, *kType.m_kProperties[i]);
			lua_pop(pkState, 1);
			if(!bRes) return false;
		}
	}
	return true;
}
//--------------------------------------------------------------------------
bool VeNetEntity::Write(BitStream& kOut, lua_State* pkState,
	const Array& kType)
{
	if(lua_type(pkState, -1) != LUA_TTABLE) return false;
	VeUInt32 n(0);
	while(true)
	{
		lua_rawgeti(pkState, -1, ++n);
		VeInt32 i32Type = lua_type(pkState, -1);
		lua_pop(pkState, 1);
		if(i32Type == LUA_TNIL) break;
	}
	kOut.Write(VeUInt16(n-1));
	for(VeUInt32 i(1); i < n; ++i)
	{
		lua_rawgeti(pkState, -1, i);
		bool bRes = Write(kOut, pkState, *kType.m_spContent);
		lua_pop(pkState, 1);
		if(!bRes) return false;
	}
	return true;
}
//--------------------------------------------------------------------------
bool VeNetEntity::Write(BitStream& kOut, lua_State* pkState,
	const Property& kType)
{
	switch(kType.GetType())
	{
	case Property::TYPE_VALUE:
		return Write(kOut, pkState, (const Value&)kType);
	case Property::TYPE_ENUM:
		return Write(kOut, pkState, (const Enum&)kType);
	case Property::TYPE_STRUCT:
		return Write(kOut, pkState, (const Struct&)kType);
	case Property::TYPE_ARRAY:
		return Write(kOut, pkState, (const Array&)kType);
	default:
		VE_ASSERT(!"Unknown error!");
		break;
	}
	return false;
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(BitStream& kOut, const Value& kType)
{
	switch(kType.m_eType)
	{
	case VALUE_VeUInt8:
		kOut.Write(VeUInt8(kType.m_u64Default));
		break;
	case VALUE_VeUInt16:
		kOut.Write(VeUInt16(kType.m_u64Default));
		break;
	case VALUE_VeUInt32:
		kOut.Write(VeUInt32(kType.m_u64Default));
		break;
	case VALUE_VeUInt64:
		kOut.Write(kType.m_u64Default);
		break;
	case VALUE_VeInt8:
		kOut.Write(VeInt8(kType.m_i64Default));
		break;
	case VALUE_VeInt16:
		kOut.Write(VeInt16(kType.m_i64Default));
		break;
	case VALUE_VeInt32:
		kOut.Write(VeInt32(kType.m_i64Default));
		break;
	case VALUE_VeInt64:
		kOut.Write(kType.m_i64Default);
		break;
	case VALUE_VeFloat32:
		kOut.Write(VeFloat32(kType.m_f64Default));
		break;
	case VALUE_VeFloat64:
		kOut.Write(kType.m_f64Default);
		break;
	case VALUE_VeString:
		::Write(kOut, (const VeChar8*)kType.m_pbyBuffer + 2, (VeUInt32)VeStrlen((const VeChar8*)kType.m_pbyBuffer + 2));
		break;
	default:
		VE_ASSERT(!"Unknown error!");
		break;
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(BitStream& kOut, const Enum& kType)
{
	VE_ASSERT(kType.m_u8Default < kType.m_kDesc.m_kIntToStr.Size());
	kOut.Write(kType.m_u8Default);
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(BitStream& kOut, const Struct& kType)
{
	for(VeUInt32 i(0); kType.m_kProperties.Size(); ++i)
	{
		Write(kOut, *kType.m_kProperties[i]);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(BitStream& kOut, const Array& kType)
{
	kOut.Write(VeUInt16(0));
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(BitStream& kOut, const Property& kType)
{
	switch(kType.GetType())
	{
	case Property::TYPE_VALUE:
		Write(kOut, (const Value&)kType);
		break;
	case Property::TYPE_ENUM:
		Write(kOut, (const Enum&)kType);
		break;
	case Property::TYPE_STRUCT:
		Write(kOut, (const Struct&)kType);
		break;
	case Property::TYPE_ARRAY:
		Write(kOut, (const Array&)kType);
		break;
	default:
		VE_ASSERT(!"Unknown error!");
		break;
	}
}
//--------------------------------------------------------------------------
bool VeNetEntity::Write(BitStream& kOut, lua_State* pkState,
	const VeVector<PropertyPtr>& kInParams)
{
	VeInt32 i32Num = lua_gettop(pkState);
	for(VeUInt32 i(0); i < kInParams.Size(); ++i)
	{
		const Property& kProp = *kInParams[i];
		if(VeInt32(i) < i32Num)
		{
			lua_pushvalue(pkState, i + 1);
			if(!Write(kOut, pkState, kProp))
			{
				lua_settop(pkState, i32Num);
				return false;
			}
			lua_settop(pkState, i32Num);
		}
		else
		{
			Write(kOut, kProp);
		}
	}
	return true;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, BitStream& kIn,
	const Value& kType)
{
	switch(kType.m_eType)
	{
	case VALUE_VeUInt8:
		{
			VeUInt8 u8Value;
			if(kIn.Read(u8Value))
			{
				lua_pushunsigned(pkState, u8Value);
				return 1;
			}
		}
		break;
	case VALUE_VeUInt16:
		{
			VeUInt16 u16Value;
			if(kIn.Read(u16Value))
			{
				lua_pushunsigned(pkState, u16Value);
				return 1;
			}
		}
		break;
	case VALUE_VeUInt32:
		{
			VeUInt32 u32Value;
			if(kIn.Read(u32Value))
			{
				lua_pushunsigned(pkState, u32Value);
				return 1;
			}
		}
		break;
	case VALUE_VeUInt64:
		{
			VeUInt64 u64Value;
			if(kIn.Read(u64Value))
			{
				lua_pushnumber(pkState, (VeFloat64)u64Value);
				return 1;
			}
		}
		break;
	case VALUE_VeInt8:
		{
			VeInt8 i8Value;
			if(kIn.Read(i8Value))
			{
				lua_pushinteger(pkState, i8Value);
				return 1;
			}
		}
		break;
	case VALUE_VeInt16:
		{
			VeInt16 i16Value;
			if(kIn.Read(i16Value))
			{
				lua_pushinteger(pkState, i16Value);
				return 1;
			}
		}
		break;
	case VALUE_VeInt32:
		{
			VeInt32 i32Value;
			if(kIn.Read(i32Value))
			{
				lua_pushinteger(pkState, i32Value);
				return 1;
			}
		}
		break;
	case VALUE_VeInt64:
		{
			VeInt64 i64Value;
			if(kIn.Read(i64Value))
			{
				lua_pushnumber(pkState, (VeFloat64)i64Value);
				return 1;
			}
		}
		break;
	case VALUE_VeFloat32:
		{
			VeFloat32 f32Value;
			if(kIn.Read(f32Value))
			{
				lua_pushnumber(pkState, f32Value);
				return 1;
			}
		}
		break;
	case VALUE_VeFloat64:
		{
			VeFloat64 f64Value;
			if(kIn.Read(f64Value))
			{
				lua_pushnumber(pkState, f64Value);
				return 1;
			}
		}
		break;
	case VALUE_VeString:
		{
			VeString kStr;
			if(RakNet::Read(kIn, kStr))
			{
				lua_pushlstring(pkState, kStr, kStr.Length());
				return 1;
			}
		}
		break;
	default:
		break;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, BitStream& kIn,
	const Enum& kType)
{
	VeUInt8 u8Value;
	if(kIn.Read(u8Value))
	{
		if(u8Value < kType.m_kDesc.m_kIntToStr.Size())
		{
			lua_pushlstring(pkState, kType.m_kDesc.m_kIntToStr[u8Value], kType.m_kDesc.m_kIntToStr[u8Value].Length());
			return 1;
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, BitStream& kIn,
	const Struct& kType)
{
	VeInt32 i32Top = lua_gettop(pkState);
	lua_newtable(pkState);
	for(VeUInt32 i(0); i < kType.m_kProperties.Size(); ++i)
	{
		if(RetParam(pkState, kIn, *kType.m_kProperties[i]) == 1)
		{
			lua_pushvalue(pkState, -1);
			lua_rawseti(pkState, -3, i + 1);
			lua_pushlstring(pkState, kType.m_kProperties[i]->m_kName, kType.m_kProperties[i]->m_kName.Length());
			lua_pushvalue(pkState, -2);
			lua_rawset(pkState, -4);
			lua_pop(pkState, 1);
		}
		else
		{
			lua_settop(pkState, i32Top);
			return 0;
		}
	}
	i32Top = lua_gettop(pkState);
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, BitStream& kIn,
	const Array& kType)
{
	VeUInt16 u16Num;
	if(!kIn.Read(u16Num)) return 0;
	VeInt32 i32Top = lua_gettop(pkState);
	lua_newtable(pkState);
	for(VeUInt16 i(0); i < u16Num; ++i)
	{
		if(RetParam(pkState, kIn, *kType.m_spContent) == 1)
		{
			lua_rawseti(pkState, -2, i + 1);
		}
		else
		{
			lua_settop(pkState, i32Top);
			return 0;
		}
	}
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, BitStream& kIn,
	const Property& kType)
{
	switch(kType.GetType())
	{
	case Property::TYPE_VALUE:
		return RetParam(pkState, kIn, (const Value&)kType);
	case Property::TYPE_ENUM:
		return RetParam(pkState, kIn, (const Enum&)kType);
	case Property::TYPE_STRUCT:
		return RetParam(pkState, kIn, (const Struct&)kType);
	case Property::TYPE_ARRAY:
		return RetParam(pkState, kIn, (const Array&)kType);
	default:
		VE_ASSERT(!"Unknown error!");
		break;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, RakNet::BitStream& kOut,
	const VeVector<PropertyPtr>& kOutParams)
{
	VeInt32 i32Ret(0);
	for(VeUInt32 i(0); i < kOutParams.Size(); ++i)
	{
		i32Ret += RetParam(pkState, kOut, *kOutParams[i]);
	}
	return i32Ret;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, const Value& kType)
{
	switch(kType.m_eType)
	{
	case VALUE_VeUInt8:
		lua_pushunsigned(pkState, VeUInt8(kType.m_u64Default));
		break;
	case VALUE_VeUInt16:
		lua_pushunsigned(pkState, VeUInt16(kType.m_u64Default));
		break;
	case VALUE_VeUInt32:
		lua_pushunsigned(pkState, VeUInt32(kType.m_u64Default));
		break;
	case VALUE_VeUInt64:
		lua_pushnumber(pkState, (VeFloat64)kType.m_u64Default);
		break;
	case VALUE_VeInt8:
		lua_pushinteger(pkState, VeInt8(kType.m_i64Default));
		break;
	case VALUE_VeInt16:
		lua_pushinteger(pkState, VeInt16(kType.m_i64Default));
		break;
	case VALUE_VeInt32:
		lua_pushinteger(pkState, VeInt32(kType.m_i64Default));
		break;
	case VALUE_VeInt64:
		lua_pushnumber(pkState, (VeFloat64)kType.m_i64Default);
		break;
	case VALUE_VeFloat32:
		lua_pushnumber(pkState, VeFloat32(kType.m_f64Default));
		break;
	case VALUE_VeFloat64:
		lua_pushnumber(pkState, kType.m_f64Default);
		break;
	case VALUE_VeString:
		lua_pushlstring(pkState, (const VeChar8*)kType.m_pbyBuffer + 2, *(VeUInt16*)kType.m_pbyBuffer);
		break;
	default:
		VE_ASSERT(!"Unknown error!");
		break;
	}
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, const Enum& kType)
{
	VE_ASSERT(kType.m_u8Default < kType.m_kDesc.m_kIntToStr.Size());
	lua_pushstring(pkState, kType.m_kDesc.m_kIntToStr[kType.m_u8Default]);
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, const Struct& kType)
{
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, const Array& kType)
{
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, const Property& kType)
{
	switch(kType.GetType())
	{
	case Property::TYPE_VALUE:
		return RetParam(pkState, (const Value&)kType);
	case Property::TYPE_ENUM:
		return RetParam(pkState, (const Enum&)kType);
	case Property::TYPE_STRUCT:
		return RetParam(pkState, (const Struct&)kType);
	case Property::TYPE_ARRAY:
		return RetParam(pkState, (const Array&)kType);
	default:
		VE_ASSERT(!"Unknown error!");
		break;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState,
	const VeVector<PropertyPtr>& kOutParams)
{
	VeInt32 i32Ret(0);
	for(VeUInt32 i(0); i < kOutParams.Size(); ++i)
	{
		i32Ret += RetParam(pkState, *kOutParams[i]);
	}
	return i32Ret;
}
//--------------------------------------------------------------------------
void VeNetEntity::ReleaseLuaData(lua_State* pkState, DataEntity& kEntity)
{
	if(kEntity.m_i32Ref)
	{
		luaL_unref(pkState, LUA_REGISTRYINDEX, kEntity.m_i32Ref);
		kEntity.m_i32Ref = 0;
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(RakNet::BitStream& kOut, const Data& kData)
{
	switch(kData.GetType())
	{
	case Data::TYPE_VALUE:
		return Write(kOut, (const DataValue&)kData);
	case Data::TYPE_ENUM:
		return Write(kOut, (const DataEnum&)kData);
	case Data::TYPE_STRUCT:
		return Write(kOut, (const DataStruct&)kData);
	case Data::TYPE_ARRAY:
		return Write(kOut, (const DataArray&)kData);
	default:
		break;
	}
	VE_ASSERT(!"Write Data error");
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(RakNet::BitStream& kOut, const DataValue& kData)
{
	const Value& kValue = (const Value&)*kData.m_pkObject;
	switch(kValue.m_eType)
	{
	case VALUE_AUTO:
		kOut.Write(VeUInt32(kData.m_u64Value));
		break;
	case VALUE_VeUInt8:
		kOut.Write(VeUInt8(kData.m_u64Value));
		break;
	case VALUE_VeUInt16:
		kOut.Write(VeUInt16(kData.m_u64Value));
		break;
	case VALUE_VeUInt32:
		kOut.Write(VeUInt32(kData.m_u64Value));
		break;
	case VALUE_VeUInt64:
		kOut.Write(VeUInt64(kData.m_u64Value));
		break;
	case VALUE_VeInt8:
		kOut.Write(VeInt8(kData.m_u64Value));
		break;
	case VALUE_VeInt16:
		kOut.Write(VeInt16(kData.m_u64Value));
		break;
	case VALUE_VeInt32:
		kOut.Write(VeInt32(kData.m_u64Value));
		break;
	case VALUE_VeInt64:
		kOut.Write(VeInt64(kData.m_u64Value));
		break;
	case VALUE_VeFloat32:
		kOut.Write(VeFloat32(kData.m_f64Value));
		break;
	case VALUE_VeFloat64:
		kOut.Write(VeFloat64(kData.m_f64Value));
		break;
	case VALUE_VeString:
		kOut.Write(*(VeUInt16*)kData.m_pbyBuffer);
		if(*(VeUInt16*)kData.m_pbyBuffer)
		{
			kOut.WriteAlignedBytes(kData.m_pbyBuffer + 2, *(VeUInt16*)kData.m_pbyBuffer);
		}
		break;
	default:
		VE_ASSERT(!"Write DataValue error");
		break;
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(RakNet::BitStream& kOut, const DataEnum& kData)
{
	kOut.Write(kData.m_u8Value);
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(RakNet::BitStream& kOut, const DataStruct& kData)
{
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		VE_ASSERT(kData.m_kDataArray[i]);
		Write(kOut, *kData.m_kDataArray[i]);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(RakNet::BitStream& kOut, const DataArray& kData)
{
	kOut.Write(VeUInt16(kData.m_kDataArray.Size()));
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		VE_ASSERT(kData.m_kDataArray[i].m_tSecond);
		Write(kOut, *kData.m_kDataArray[i].m_tSecond);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(RakNet::BitStream& kOut, const DataEntity& kData)
{
	const VeNetEntity& kEntity = (const VeNetEntity&)*(kData.m_pkObject);
	VE_ASSERT(kEntity.m_u32Index < VE_UINT16_MAX);
	kOut.Write(VeUInt16(kEntity.m_u32Index));
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		VE_ASSERT(kData.m_kDataArray[i]);
		Write(kOut, *kData.m_kDataArray[i]);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Write(RakNet::BitStream& kOut, const DataEntity& kData,
	Property::Flag eFlag)
{
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		VE_ASSERT(kData.m_kDataArray[i]);
		Property& kProp = *(Property*)kData.m_kDataArray[i]->m_pkObject;
		if(kProp.HasFlag(eFlag))
		{
			Write(kOut, *kData.m_kDataArray[i]);
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::WriteUpdate(BitStream& kOut, const Data& kData)
{
	switch(kData.GetType())
	{
	case Data::TYPE_VALUE:
		Write(kOut, (const DataValue&)kData);
		break;
	case Data::TYPE_ENUM:
		Write(kOut, (const DataEnum&)kData);
		break;
	case Data::TYPE_STRUCT:
		WriteUpdate(kOut, (const DataStruct&)kData);
		break;
	case Data::TYPE_ARRAY:
		Write(kOut, (const DataArray&)kData);
		break;
	default:
		VE_ASSERT(!"Error write update data");
		break;
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::WriteUpdate(BitStream& kOut,
	const DataStruct& kData)
{
	kOut.Write(VeUInt16(kData.m_kDirtyList.Size()));
	kData.m_kDirtyList.BeginIterator();
	while(!kData.m_kDirtyList.IsEnd())
	{
		const Data* pkData = kData.m_kDirtyList.GetIterNode()->m_tContent;
		kData.m_kDirtyList.Next();
		kOut.Write(VeUInt16(pkData->m_u32Index));
		WriteUpdate(kOut, *pkData);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::WriteUpdate(BitStream& kOut,
	const DataEntity& kData, Property::Flag eFlag)
{
	VeVector<const Data*> kUpdate;
	kData.m_kDirtyList.BeginIterator();
	while(!kData.m_kDirtyList.IsEnd())
	{
		const Data* pkData = kData.m_kDirtyList.GetIterNode()->m_tContent;
		kData.m_kDirtyList.Next();
		Property& kProp = *(Property*)pkData->m_pkObject;
		if(kProp.HasFlag(eFlag))
		{
			kUpdate.PushBack(pkData);
		}
	}

	kOut.Write(VeUInt16(kUpdate.Size()));
	for(VeVector<const Data*>::iterator it = kUpdate.Begin(); it != kUpdate.End(); ++it)
	{
		if(eFlag == Property::FLAG_CLIENT)
		{
			kOut.Write(((Property*)(*it)->m_pkObject)->m_u16Client);
		}
		else
		{
			VE_ASSERT(eFlag == Property::FLAG_DATABASE);
			kOut.Write(((Property*)(*it)->m_pkObject)->m_u16Database);
		}		
		WriteUpdate(kOut, **it);
	}
	kUpdate.Clear();
}
//--------------------------------------------------------------------------
void VeNetEntity::Read(BitStream& kIn, Data& kData)
{
	switch(kData.GetType())
	{
	case Data::TYPE_VALUE:
		Read(kIn, (DataValue&)kData);
		break;
	case Data::TYPE_ENUM:
		Read(kIn, (DataEnum&)kData);
		break;
	case Data::TYPE_STRUCT:
		Read(kIn, (DataStruct&)kData);
		break;
	case Data::TYPE_ARRAY:
		Read(kIn, (DataArray&)kData);
		break;
	default:
		VE_ASSERT(!"Error write update data");
		break;
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Read(BitStream& kIn, DataValue& kData)
{
	Value& kValue = *(Value*)kData.m_pkObject;
	switch(kValue.m_eType)
	{
	case VALUE_AUTO:
		VE_ASSERT_EQ(kIn.Read(*(VeUInt32*)&kData.m_u64Value), true);
		break;
	case VALUE_VeUInt8:
		VE_ASSERT_EQ(kIn.Read(*(VeUInt8*)&kData.m_u64Value), true);
		break;
	case VALUE_VeUInt16:
		VE_ASSERT_EQ(kIn.Read(*(VeUInt16*)&kData.m_u64Value), true);
		break;
	case VALUE_VeUInt32:
		VE_ASSERT_EQ(kIn.Read(*(VeUInt32*)&kData.m_u64Value), true);
		break;
	case VALUE_VeUInt64:
		VE_ASSERT_EQ(kIn.Read(*(VeUInt64*)&kData.m_u64Value), true);
		break;
	case VALUE_VeInt8:
		VE_ASSERT_EQ(kIn.Read(*(VeInt8*)&kData.m_i64Value), true);
		break;
	case VALUE_VeInt16:
		VE_ASSERT_EQ(kIn.Read(*(VeInt16*)&kData.m_i64Value), true);
		break;
	case VALUE_VeInt32:
		VE_ASSERT_EQ(kIn.Read(*(VeInt32*)&kData.m_i64Value), true);
		break;
	case VALUE_VeInt64:
		VE_ASSERT_EQ(kIn.Read(*(VeInt64*)&kData.m_i64Value), true);
		break;
	case VALUE_VeFloat32:
		VE_ASSERT_EQ(kIn.Read(*(VeFloat32*)&kData.m_f64Value), true);
		break;
	case VALUE_VeFloat64:
		VE_ASSERT_EQ(kIn.Read(*(VeFloat64*)&kData.m_f64Value), true);
		break;
	case VALUE_VeString:
		{
			VeUInt16 u16Len;
			VE_ASSERT_EQ(kIn.Read(u16Len), true);
			kData.m_pbyBuffer = (VeByte*)VeRealloc(kData.m_pbyBuffer, u16Len + 3);
			*(VeUInt16*)kData.m_pbyBuffer = u16Len;
			if(u16Len) VE_ASSERT_EQ(kIn.ReadAlignedBytes(kData.m_pbyBuffer + 2, u16Len), true);
			kData.m_pbyBuffer[u16Len + 2] = 0;
		}
		break;
	default:
		VE_ASSERT(!"Error write update value");
		break;
	}
	kData.NotifyDirty();
}
//--------------------------------------------------------------------------
void VeNetEntity::Read(BitStream& kIn, DataEnum& kData)
{
	VE_ASSERT_EQ(kIn.Read(kData.m_u8Value), true);
	kData.NotifyDirty();
}
//--------------------------------------------------------------------------
void VeNetEntity::Read(BitStream& kIn, DataArray& kData)
{
	VeUInt16 u16Size;
	VE_ASSERT_EQ(kIn.Read(u16Size), true);
	kData.m_kDataArray.Resize(u16Size);
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		kData.m_kDataArray[i].m_tFirst = 0;
		kData.m_kDataArray[i].m_tSecond = CreateData(*((Array*)kData.m_pkObject)->m_spContent);
		Read(kIn, *kData.m_kDataArray[i].m_tSecond);
	}
	kData.Data::NotifyDirty();
}
//--------------------------------------------------------------------------
void VeNetEntity::Read(BitStream& kIn, DataContainer& kData)
{
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		Read(kIn, *kData.m_kDataArray[i]);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::ReadUpdate(BitStream& kIn, Data& kData)
{
	switch(kData.GetType())
	{
	case Data::TYPE_VALUE:
		Read(kIn, (DataValue&)kData);
		break;
	case Data::TYPE_ENUM:
		Read(kIn, (DataEnum&)kData);
		break;
	case Data::TYPE_STRUCT:
		ReadUpdate(kIn, (DataStruct&)kData);
		break;
	case Data::TYPE_ARRAY:
		Read(kIn, (DataArray&)kData);
		break;
	default:
		VE_ASSERT(!"Error write update data");
		break;
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::ReadUpdate(BitStream& kIn, DataContainer& kData)
{
	VeUInt16 u16Size;
	VE_ASSERT_EQ(kIn.Read(u16Size), true);
	for(VeUInt32 i(0); i < u16Size; ++i)
	{
		VeUInt16 u16Index;
		VE_ASSERT_EQ(kIn.Read(u16Index), true);
		VE_ASSERT(u16Index < kData.m_kDataArray.Size());
		ReadUpdate(kIn, *kData.m_kDataArray[u16Index]);
	}
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(BitStream& kStream,
	Value& kValue)
{
	DataValuePtr spValue = VE_NEW DataValue;
	spValue->m_pkObject = &kValue;
	switch(kValue.m_eType)
	{
	case VALUE_AUTO:
		{
			VeUInt32 u32Data;
			if(!kStream.Read(u32Data)) return NULL;
			spValue->m_u64Value = u32Data;
		}
		break;
	case VALUE_VeUInt8:
		{
			VeUInt8 u8Data;
			if(!kStream.Read(u8Data)) return NULL;
			spValue->m_u64Value = u8Data;
		}
		break;
	case VALUE_VeUInt16:
		{
			VeUInt16 u16Data;
			if(!kStream.Read(u16Data)) return NULL;
			spValue->m_u64Value = u16Data;
		}
		break;
	case VALUE_VeUInt32:
		{
			VeUInt32 u32Data;
			if(!kStream.Read(u32Data)) return NULL;
			spValue->m_u64Value = u32Data;
		}
		break;
	case VALUE_VeUInt64:
		{
			VeUInt64 u64Data;
			if(!kStream.Read(u64Data)) return NULL;
			spValue->m_u64Value = u64Data;
		}
		break;
	case VALUE_VeInt8:
		{
			VeInt8 i8Data;
			if(!kStream.Read(i8Data)) return NULL;
			spValue->m_i64Value = i8Data;
		}
		break;
	case VALUE_VeInt16:
		{
			VeInt16 i16Data;
			if(!kStream.Read(i16Data)) return NULL;
			spValue->m_i64Value = i16Data;
		}
		break;
	case VALUE_VeInt32:
		{
			VeInt32 i32Data;
			if(!kStream.Read(i32Data)) return NULL;
			spValue->m_i64Value = i32Data;
		}
		break;
	case VALUE_VeInt64:
		{
			VeInt8 i64Data;
			if(!kStream.Read(i64Data)) return NULL;
			spValue->m_i64Value = i64Data;
		}
		break;
	case VALUE_VeFloat32:
		{
			VeFloat32 f32Data;
			if(!kStream.Read(f32Data)) return NULL;
			spValue->m_f64Value = f32Data;
		}
		break;
	case VALUE_VeFloat64:
		{
			VeFloat64 f64Data;
			if(!kStream.Read(f64Data)) return NULL;
			spValue->m_f64Value = f64Data;
		}
		break;
	case VALUE_VeString:
		{
			VeUInt16 u16Len;
			if(!kStream.Read(u16Len)) return NULL;
			spValue->m_pbyBuffer = VeAlloc(VeByte, u16Len + 3);
			*(VeUInt16*)spValue->m_pbyBuffer = u16Len;
			if(u16Len)
			{
				if(!kStream.ReadAlignedBytes(spValue->m_pbyBuffer + 2, u16Len)) return NULL;
			}
			spValue->m_pbyBuffer[u16Len + 2] = 0;
		}
		break;
	default:
		return NULL;
	}
	return spValue;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(BitStream& kStream,
	Enum& kEnum)
{
	DataEnumPtr spEnum = VE_NEW DataEnum;
	spEnum->m_pkObject = &kEnum;
	if(!kStream.Read(spEnum->m_u8Value)) return NULL;
	if(spEnum->m_u8Value >= kEnum.m_kDesc.m_kIntToStr.Size()) return NULL;
	return spEnum;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(BitStream& kStream,
	Struct& kStruct)
{
	DataStructPtr spStruct = VE_NEW DataStruct;
	spStruct->m_pkObject = &kStruct;
	for(VeUInt32 i(0); i < kStruct.m_kProperties.Size(); ++i)
	{
		DataPtr spData = CreateData(kStream, *kStruct.m_kProperties[i]);
		VE_ASSERT(spData);
		spData->m_u32Index = i;
		spData->m_pkHolder = spStruct;
		spStruct->m_kDataArray.PushBack(spData);
	}
	return spStruct;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(BitStream& kStream,
	Array& kArray)
{
	DataArrayPtr spArray = VE_NEW DataArray;
	spArray->m_pkObject = &kArray;
	VeUInt16 u16ArrayNum;
	if(!kStream.Read(u16ArrayNum)) return NULL;
	for(VeUInt16 i(0); i < u16ArrayNum; ++i)
	{
		spArray->m_kDataArray.Increase();
		VePair<VeUInt32,DataPtr>& kNew = spArray->m_kDataArray.Back();
		kNew.m_tFirst = 0;
		kNew.m_tSecond = CreateData(kStream, *kArray.m_spContent);
		VE_ASSERT(kNew.m_tSecond);
		kNew.m_tSecond->m_u32Index = i;
		kNew.m_tSecond->m_pkHolder = spArray;
	}
	return spArray;
}
//--------------------------------------------------------------------------
VeNetEntity::DataPtr VeNetEntity::CreateData(BitStream& kStream,
	Property& kProperty)
{
	switch(kProperty.GetType())
	{
	case Property::TYPE_VALUE:
		return CreateData(kStream, (Value&)kProperty);
	case Property::TYPE_ENUM:
		return CreateData(kStream, (Enum&)kProperty);
	case Property::TYPE_STRUCT:
		return CreateData(kStream, (Struct&)kProperty);
	case Property::TYPE_ARRAY:
		return CreateData(kStream, (Array&)kProperty);
	default:
		break;
	}
	return NULL;
}
//--------------------------------------------------------------------------
void VeNetEntity::ClearDirty(Data& kData)
{
	switch(kData.GetType())
	{
	case Data::TYPE_STRUCT:
		ClearDirty((DataStruct&)kData);
		break;
	case Data::TYPE_ARRAY:
		ClearDirty((DataArray&)kData);
		break;
	default:
		break;
	}
	kData.m_kDirtyNode.Detach();
}
//--------------------------------------------------------------------------
void VeNetEntity::ClearDirty(DataArray& kData)
{
	for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
	{
		ClearDirty(*kData.m_kDataArray[i].m_tSecond);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::ClearDirty(DataContainer& kData)
{
	kData.m_kDirtyList.BeginIterator();
	while(!kData.m_kDirtyList.IsEnd())
	{
		Data* pkData = kData.m_kDirtyList.GetIterNode()->m_tContent;
		kData.m_kDirtyList.Next();
		ClearDirty(*pkData);
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::ClearDirty(DataEntity& kData)
{
	ClearDirty((DataContainer&)kData);
	kData.m_kDirtyNode.Detach();
}
//--------------------------------------------------------------------------
void VeNetEntity::Set(Data& kDsc, Data& kSrc)
{
	if(kDsc.GetType() == kSrc.GetType())
	{
		switch(kDsc.GetType())
		{
		case Data::TYPE_VALUE:
			Set((DataValue&)kDsc, (DataValue&)kSrc);
			break;
		case Data::TYPE_ENUM:
			Set((DataEnum&)kDsc, (DataEnum&)kSrc);
			break;
		case Data::TYPE_STRUCT:
			Set((DataStruct&)kDsc, (DataStruct&)kSrc);
			break;
		case Data::TYPE_ARRAY:
			Set((DataArray&)kDsc, (DataArray&)kSrc);
			break;
		default:
			break;
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Set(DataValue& kDsc, DataValue& kSrc)
{
	Value& kValueDsc = *(Value*)kDsc.m_pkObject;
	Value& kValueSrc = *(Value*)kSrc.m_pkObject;
	if(kValueDsc.m_eType == kValueSrc.m_eType)
	{
		if(kValueDsc.m_eType == VALUE_VeString)
		{
			if(VeStrcmp((const VeChar8*)kDsc.m_pbyBuffer + 2, (const VeChar8*)kSrc.m_pbyBuffer + 2))
			{
				VeUInt16 u16Len = *(VeUInt16*)kSrc.m_pbyBuffer;
				kDsc.m_pbyBuffer = (VeByte*)VeRealloc(kDsc.m_pbyBuffer, u16Len + 3);
				*(VeUInt16*)kDsc.m_pbyBuffer = u16Len;
				VeMemcpy(kDsc.m_pbyBuffer + 2, kSrc.m_pbyBuffer + 2, u16Len + 1);
				kDsc.NotifyDirty();
			}
		}
		else if(kDsc.m_u64Value != kSrc.m_u64Value)
		{
			kDsc.m_u64Value = kSrc.m_u64Value;
			kDsc.NotifyDirty();
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Set(DataEnum& kDsc, DataEnum& kSrc)
{
	Enum& kEnum = *(Enum*)kDsc.m_pkObject;
	if(kDsc.m_u8Value != kSrc.m_u8Value
		&& kSrc.m_u8Value < kEnum.m_kDesc.m_kIntToStr.Size())
	{
		kDsc.m_u8Value = kSrc.m_u8Value;
		kDsc.NotifyDirty();
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Set(DataStruct& kDsc, DataStruct& kSrc)
{
	if(kDsc.m_kDataArray.Size() == kSrc.m_kDataArray.Size())
	{
		for(VeUInt32 i(0); i < kDsc.m_kDataArray.Size(); ++i)
		{
			Set(*kDsc.m_kDataArray[i], *kSrc.m_kDataArray[i]);
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::Set(DataArray& kDsc, DataArray& kSrc)
{
	kDsc.m_kDataArray.Clear();
	for(VeUInt32 i(0); i < kSrc.m_kDataArray.Size(); ++i)
	{
		kDsc.m_kDataArray.Increase();
		VePair<VeUInt32,DataPtr>& kNew = kDsc.m_kDataArray.Back();
		kNew.m_tFirst = 0;
		kNew.m_tSecond = CreateData(*((Array*)kDsc.m_pkObject)->m_spContent);
		VE_ASSERT(kNew.m_tSecond);
		kNew.m_tSecond->m_u32Index = kDsc.m_kDataArray.Size() - 1;
		kNew.m_tSecond->m_pkHolder = &kDsc;
		Set(*kNew.m_tSecond, *kSrc.m_kDataArray[i].m_tSecond);
	}
	kDsc.Data::NotifyDirty();
}
//--------------------------------------------------------------------------
void VeNetEntity::SetParam(lua_State* pkState, Data& kData)
{
	switch(kData.GetType())
	{
	case Data::TYPE_VALUE:
		SetParam(pkState, (DataValue&)kData);
		break;
	case Data::TYPE_ENUM:
		SetParam(pkState, (DataEnum&)kData);
		break;
	case Data::TYPE_STRUCT:
		SetParam(pkState, (DataStruct&)kData);
		break;
	case Data::TYPE_ARRAY:
		SetParam(pkState, (DataArray&)kData);
		break;
	default:
		VeDebugOutput("Error to modify %s as %s\n",
			lua_tostring(pkState, -2), lua_tostring(pkState, -1));
		break;
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::SetParam(lua_State* pkState, DataValue& kData)
{
	Value& kValue = (Value&)*kData.m_pkObject;
	if(kValue.m_eType == VALUE_AUTO)
	{
		VeDebugOutput("Error to modify %s as %s to auto value\n",
			lua_tostring(pkState, -2), lua_tostring(pkState, -1));
	}
	else if(kValue.m_eType < VALUE_VeInt8)
	{
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			VeUInt64 u64New = (VeUInt64)lua_tonumber(pkState, -1);
			if(u64New != kData.m_u64Value)
			{
				kData.m_u64Value = u64New;
				kData.NotifyDirty();
			}
		}
	}
	else if(kValue.m_eType < VALUE_VeFloat32)
	{
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			VeInt64 i64New = (VeInt64)lua_tonumber(pkState, -1);
			if(i64New != kData.m_i64Value)
			{
				kData.m_i64Value = i64New;
				kData.NotifyDirty();
			}
		}
	}
	else if(kValue.m_eType < VALUE_VeString)
	{
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			VeFloat64 f64New = lua_tonumber(pkState, -1);
			if(f64New != kData.m_f64Value)
			{
				kData.m_f64Value = f64New;
				kData.NotifyDirty();
			}
		}
	}
	else if(kValue.m_eType == VALUE_VeString)
	{
		if(lua_type(pkState, -1) == LUA_TSTRING)
		{
			VeSizeT stLen(0);
			const VeChar8* pcValue = lua_tolstring(pkState, -1, &stLen);
			stLen = VE_MIN(stLen, 255);
			if(VeStrncmp(pcValue, (const VeChar8*)(kData.m_pbyBuffer + 2), stLen))
			{
				kData.m_pbyBuffer = (VeByte*)VeRealloc(kData.m_pbyBuffer, stLen + 3);
				*(VeUInt16*)kData.m_pbyBuffer = (VeUInt16)stLen;
				VeMemcpy(kData.m_pbyBuffer + 2, pcValue, stLen + 1);
				kData.NotifyDirty();
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::SetParam(lua_State* pkState, DataEnum& kData)
{
	Enum& kEnum = (Enum&)*kData.m_pkObject;
	VeUInt32 u32Type = lua_type(pkState, -1);
	if(u32Type == LUA_TNUMBER)
	{
		VeUInt32 u32Value = (VeUInt32)lua_tonumber(pkState, -1);
		if(u32Value < kEnum.m_kDesc.m_kIntToStr.Size())
		{
			if(u32Value != kData.m_u8Value)
			{
				kData.m_u8Value = u32Value;
				kData.NotifyDirty();
			}
		}
		else
		{
			VeDebugOutput("Error to modify %s as %s to enum\n",
				lua_tostring(pkState, -2), lua_tostring(pkState, -1));
		}
	}
	else if(u32Type == LUA_TSTRING)
	{
		const VeUInt8* pu8Iter = kEnum.m_kDesc.m_kStrToInt.Find(lua_tostring(pkState, -1));
		if(pu8Iter)
		{
			if(*pu8Iter != kData.m_u8Value)
			{
				kData.m_u8Value = *pu8Iter;
				kData.NotifyDirty();
			}
		}
		else
		{
			VeDebugOutput("Error to modify %s as %s to enum\n",
				lua_tostring(pkState, -2), lua_tostring(pkState, -1));
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::SetParam(lua_State* pkState, DataStruct& kData)
{
	VeUInt32 u32Type = lua_type(pkState, -1);
	if(u32Type == LUA_TTABLE)
	{
		for(VeUInt32 i(0); i < kData.m_kDataArray.Size(); ++i)
		{
			lua_rawgeti(pkState, -1, i + 1);
			SetParam(pkState, *kData.m_kDataArray[i]);
			lua_pop(pkState, 1);
		}
	}
	else if(u32Type == LUA_TUSERDATA)
	{
		LuaSupport* pkSupport = *(LuaSupport**)lua_touserdata(pkState, -1);
		if(pkSupport->m_pkParent && pkSupport->m_pkParent->GetType() == Data::TYPE_STRUCT)
		{
			Set(kData, *(DataStruct*)pkSupport->m_pkParent);
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntity::SetParam(lua_State* pkState, DataArray& kData)
{
	VeUInt32 u32Type = lua_type(pkState, -1);
	if(u32Type == LUA_TTABLE)
	{
		kData.m_kDataArray.Clear();
		VeUInt32 n(0);
		while(true)
		{
			lua_rawgeti(pkState, -1, ++n);
			if(lua_type(pkState, -1) == LUA_TNIL)
			{
				lua_pop(pkState, 1);
				break;
			}
			else
			{
				kData.m_kDataArray.Increase();
				VePair<VeUInt32,DataPtr>& kNew = kData.m_kDataArray.Back();
				kNew.m_tFirst = 0;
				kNew.m_tSecond = CreateData(*((Array*)kData.m_pkObject)->m_spContent);
				VE_ASSERT(kNew.m_tSecond);
				kNew.m_tSecond->m_u32Index = kData.m_kDataArray.Size() - 1;
				kNew.m_tSecond->m_pkHolder = &kData;
				SetParam(pkState, *kNew.m_tSecond);
				lua_pop(pkState, 1);
			}
		}
		kData.Data::NotifyDirty();
	}
	else if(u32Type == LUA_TUSERDATA)
	{
		LuaSupport* pkSupport = *(LuaSupport**)lua_touserdata(pkState, -1);
		if(pkSupport->m_pkParent && pkSupport->m_pkParent->GetType() == Data::TYPE_ARRAY)
		{
			Set(kData, *(DataArray*)pkSupport->m_pkParent);
		}
	}
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataIndex(lua_State* pkState)
{
	LuaSupport* pkSupport = *(LuaSupport**)lua_touserdata(pkState, -2);
	if(pkSupport->m_pkParent)
	{
		VeUInt32 u32Index(VE_INFINITE);
		if(lua_type(pkState, -1) == LUA_TSTRING)
		{
			const VeChar8* pcName = lua_tostring(pkState, -1);
			if(pkSupport->m_pkParent->GetType() == Data::TYPE_ENTITY)
			{
				VeUInt32* pu32Iter = ((VeNetEntity*)(pkSupport->m_pkParent->m_pkObject))->m_kNameMap.Find(pcName);
				if(pu32Iter)
				{
					u32Index = *pu32Iter;
				}
			}
			else
			{
				VE_ASSERT(pkSupport->m_pkParent->GetType() == Data::TYPE_STRUCT);
				VeUInt32* pu32Iter = ((Struct*)(pkSupport->m_pkParent->m_pkObject))->m_kNameMap.Find(pcName);
				if(pu32Iter)
				{
					u32Index = *pu32Iter;
				}
			}
		}
		else
		{
			u32Index = (VeUInt32)lua_tonumber(pkState, -1);
		}
		if(u32Index < ((DataContainer*)pkSupport->m_pkParent)->m_kDataArray.Size())
		{
			bool bWrite = lua_toboolean(pkState, lua_upvalueindex(1)) ? true : false;
			return RetParam(pkState, *((DataContainer*)pkSupport->m_pkParent)->m_kDataArray[u32Index], bWrite);
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataNewIndex(lua_State* pkState)
{
	LuaSupport* pkSupport = *(LuaSupport**)lua_touserdata(pkState, -3);
	if(pkSupport->m_pkParent)
	{
		VeUInt32 u32Index(VE_INFINITE);
		if(lua_type(pkState, -2) == LUA_TSTRING)
		{
			const VeChar8* pcName = lua_tostring(pkState, -2);
			if(pkSupport->m_pkParent->GetType() == Data::TYPE_ENTITY)
			{
				VeUInt32* pu32Iter = ((VeNetEntity*)(pkSupport->m_pkParent->m_pkObject))->m_kNameMap.Find(pcName);
				if(pu32Iter)
				{
					u32Index = *pu32Iter;
				}
			}
			else
			{
				VE_ASSERT(pkSupport->m_pkParent->GetType() == Data::TYPE_STRUCT);
				VeUInt32* pu32Iter = ((Struct*)(pkSupport->m_pkParent->m_pkObject))->m_kNameMap.Find(pcName);
				if(pu32Iter)
				{
					u32Index = *pu32Iter;
				}
			}
		}
		else
		{
			u32Index = (VeUInt32)lua_tonumber(pkState, -2);
		}
		if(u32Index && u32Index < ((DataContainer*)pkSupport->m_pkParent)->m_kDataArray.Size())
		{
			SetParam(pkState, *((DataContainer*)pkSupport->m_pkParent)->m_kDataArray[u32Index]);
			return 0;
		}
	}
	VeDebugOutput("Error to modify %s as %s\n", lua_tostring(pkState, -2), lua_tostring(pkState, -1));
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataArrayPushBack(lua_State* pkState)
{
	LuaSupport* pkSupport = (LuaSupport*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkSupport->m_pkParent)
	{
		VE_ASSERT(pkSupport->m_pkParent->GetType() == Data::TYPE_ARRAY);
		DataArray& kData = *(DataArray*)pkSupport->m_pkParent;
		kData.m_kDataArray.Increase();
		VePair<VeUInt32,DataPtr>& kNew = kData.m_kDataArray.Back();
		kNew.m_tFirst = 0;
		kNew.m_tSecond = CreateData(*((Array*)kData.m_pkObject)->m_spContent);
		VE_ASSERT(kNew.m_tSecond);
		SetParam(pkState, *kNew.m_tSecond);
		kNew.m_tSecond->m_u32Index = kData.m_kDataArray.Size() - 1;
		kNew.m_tSecond->m_pkHolder = &kData;
		kData.Data::NotifyDirty();
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataArrayPopBack(lua_State* pkState)
{
	LuaSupport* pkSupport = (LuaSupport*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkSupport->m_pkParent)
	{
		VE_ASSERT(pkSupport->m_pkParent->GetType() == Data::TYPE_ARRAY);
		DataArray& kData = *(DataArray*)pkSupport->m_pkParent;
		kData.m_kDataArray.PopBack();
		kData.Data::NotifyDirty();
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataArrayDelete(lua_State* pkState)
{
	LuaSupport* pkSupport = (LuaSupport*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkSupport->m_pkParent)
	{
		VE_ASSERT(pkSupport->m_pkParent->GetType() == Data::TYPE_ARRAY);
		if(lua_type(pkState, -1) == LUA_TNUMBER)
		{
			DataArray& kData = *(DataArray*)pkSupport->m_pkParent;
			VeUInt32 u32Index = (VeUInt32)lua_tonumber(pkState, -1);
			if(u32Index < kData.m_kDataArray.Size())
			{
				kData.m_kDataArray.Erase(&kData.m_kDataArray[u32Index]);
				while(u32Index  < kData.m_kDataArray.Size())
				{
					kData.m_kDataArray[u32Index].m_tSecond->m_u32Index = u32Index;
                    ++u32Index;
				}
				kData.Data::NotifyDirty();
			}
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataArrayClear(lua_State* pkState)
{
	LuaSupport* pkSupport = (LuaSupport*)lua_touserdata(pkState, lua_upvalueindex(1));
	if(pkSupport->m_pkParent)
	{
		VE_ASSERT(pkSupport->m_pkParent->GetType() == Data::TYPE_ARRAY);
		DataArray& kData = *(DataArray*)pkSupport->m_pkParent;
		if(kData.m_kDataArray.Size())
		{
			kData.m_kDataArray.Clear();
			kData.Data::NotifyDirty();
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataIndexArray(lua_State* pkState)
{
	LuaSupport* pkSupport = *(LuaSupport**)lua_touserdata(pkState, -2);
	if(pkSupport->m_pkParent)
	{
		VE_ASSERT(pkSupport->m_pkParent->GetType() == Data::TYPE_ARRAY);
		DataArray& kArray = *(DataArray*)pkSupport->m_pkParent;
		bool bWrite = lua_toboolean(pkState, lua_upvalueindex(1)) ? true : false;
		if(lua_type(pkState, -1) == LUA_TSTRING)
		{
			const VeChar8* pcName = lua_tostring(pkState, -1);
			switch(ArrayFuncLua::ToEnum(pcName, ARRAY_MAX))
			{
			case ARRAY_SIZE:
				lua_pushinteger(pkState, kArray.m_kDataArray.Size());
				return 1;
			case ARRAY_FRONT:
				if(kArray.m_kDataArray.Size())
				{
					RetParam(pkState, *(kArray.m_kDataArray.Front().m_tSecond), bWrite);
					return 1;
				}
				break;
			case ARRAY_BACK:
				if(kArray.m_kDataArray.Size())
				{
					RetParam(pkState, *(kArray.m_kDataArray.Back().m_tSecond), bWrite);
					return 1;
				}
				break;
			case ARRAY_PUSHBACK:
				if(bWrite)
				{
					lua_pushlightuserdata(pkState, pkSupport);
					lua_pushcclosure(pkState, &DataArrayPushBack, 1);
					return 1;
				}
				break;
			case ARRAY_POPBACK:
				if(bWrite)
				{
					lua_pushlightuserdata(pkState, pkSupport);
					lua_pushcclosure(pkState, &DataArrayPopBack, 1);
					return 1;
				}
				break;
			case ARRAY_DELETE:
				if(bWrite)
				{
					lua_pushlightuserdata(pkState, pkSupport);
					lua_pushcclosure(pkState, &DataArrayDelete, 1);
					return 1;
				}
				break;
			case ARRAY_CLEAR:
				if(bWrite)
				{
					lua_pushlightuserdata(pkState, pkSupport);
					lua_pushcclosure(pkState, &DataArrayClear, 1);
					return 1;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			VeUInt32 u32Index = (VeUInt32)lua_tounsigned(pkState, -1);
			if(u32Index) u32Index -= 1;
			if(u32Index < kArray.m_kDataArray.Size())
			{
				return RetParam(pkState, *kArray.m_kDataArray[u32Index].m_tSecond, bWrite);
			}
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DataNewIndexArray(lua_State* pkState)
{
	VeNetEntity::LuaSupport* pkSupport = *(VeNetEntity::LuaSupport**)lua_touserdata(pkState, -3);
	if(pkSupport->m_pkParent)
	{
		VE_ASSERT(pkSupport->m_pkParent->GetType() == VeNetEntity::Data::TYPE_ARRAY);
		VeNetEntity::DataArray& kArray = *(VeNetEntity::DataArray*)pkSupport->m_pkParent;
		if(lua_type(pkState, -2) == LUA_TSTRING)
		{
			const VeChar8* pcName = lua_tostring(pkState, -2);
			switch(ArrayFuncLua::ToEnum(pcName, ARRAY_MAX))
			{
			case ARRAY_FRONT:
				if(kArray.m_kDataArray.Size())
				{
					SetParam(pkState, *kArray.m_kDataArray.Front().m_tSecond);
				}
				break;
			case ARRAY_BACK:
				if(kArray.m_kDataArray.Size())
				{
					SetParam(pkState, *kArray.m_kDataArray.Back().m_tSecond);
				}
				break;
			default:
				break;
			}
		}
		else
		{
			VeUInt32 u32Index = (VeUInt32)lua_tonumber(pkState, -2);
			if(u32Index) u32Index -= 1;
			if(u32Index < kArray.m_kDataArray.Size())
			{
				SetParam(pkState, *kArray.m_kDataArray[u32Index].m_tSecond);
			}
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::NoWriteNewIndex(lua_State* pkState)
{
	VeDebugOutput("Error to modify %s as %s\n",
		lua_tostring(pkState, -2), lua_tostring(pkState, -1));
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::DestructorData(lua_State* pkState)
{
	LuaSupport* pkSupport = *(LuaSupport**)lua_touserdata(pkState, -1);
	pkSupport->DecRefCount();
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::PrintData(lua_State* pkState)
{
	LuaSupport* pkSupport = *(LuaSupport**)lua_touserdata(pkState, -1);
	if(pkSupport->m_pkParent)
	{
		VeChar8 acBuffer[4096];
		VeChar8* pcPointer(acBuffer);
		pcPointer += ToString(pcPointer, *pkSupport->m_pkParent);
		VeLuaBind::RetParam(pkState, acBuffer);
		return 1;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, Data& kData,
	bool bEnableWrite)
{
	switch(kData.GetType())
	{
	case Data::TYPE_VALUE:
		return RetParam(pkState, (DataValue&)kData);
	case Data::TYPE_ENUM:
		return RetParam(pkState, (DataEnum&)kData);
	case Data::TYPE_STRUCT:
		return RetParam(pkState, (DataStruct&)kData, bEnableWrite);
	case Data::TYPE_ARRAY:
		return RetParam(pkState, (DataArray&)kData, bEnableWrite);
	default:
		break;
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, DataValue& kData)
{
	Value& kValue = (Value&)*kData.m_pkObject;
	if(kValue.m_eType < VALUE_VeInt8)
	{
		return VeLuaBind::RetParam(pkState, kData.m_u64Value);
	}
	else if(kValue.m_eType < VALUE_VeFloat32)
	{
		return VeLuaBind::RetParam(pkState, kData.m_i64Value);
	}
	else if(kValue.m_eType < VALUE_VeString)
	{
		return VeLuaBind::RetParam(pkState, kData.m_f64Value);
	}
	else if(kValue.m_eType == VALUE_VeString)
	{
		return VeLuaBind::RetParam(pkState, (const VeChar8*)(kData.m_pbyBuffer + 2));
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, DataEnum& kData)
{
	Enum& kEnum = (Enum&)*kData.m_pkObject;
	if(kData.m_u8Value < kEnum.m_kDesc.m_kIntToStr.Size())
	{
		return VeLuaBind::RetParam(pkState, (const VeChar8*)(kEnum.m_kDesc.m_kIntToStr[kData.m_u8Value]));
	}
	return 0;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, DataContainer& kData,
	bool bEnableWrite)
{
	if(!kData.m_spLuaSupport)
	{
		kData.m_spLuaSupport = VE_NEW VeNetEntity::LuaSupport(&kData);
	}
	void* pvData = lua_newuserdata(pkState, sizeof(VeNetEntity::LuaSupport*));
	kData.m_spLuaSupport->IncRefCount();
	*(VeNetEntity::LuaSupport**)pvData = kData.m_spLuaSupport;
	lua_newtable(pkState);
	lua_pushstring(pkState, "__index");
	lua_pushboolean(pkState, bEnableWrite ? 1 : 0);
	lua_pushcclosure(pkState, &DataIndex, 1);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__newindex");
	if(bEnableWrite)
	{
		lua_pushcfunction(pkState, &DataNewIndex);
	}
	else
	{
		lua_pushcfunction(pkState, &NoWriteNewIndex);
	}
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__gc");
	lua_pushcfunction(pkState, &DestructorData);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__tostring");
	lua_pushcfunction(pkState, &PrintData);
	lua_rawset(pkState, -3);
	lua_setmetatable(pkState, -2);
	return 1;
}
//--------------------------------------------------------------------------
VeInt32 VeNetEntity::RetParam(lua_State* pkState, DataArray& kData,
	bool bEnableWrite)
{
	if(!kData.m_spLuaSupport)
	{
		kData.m_spLuaSupport = VE_NEW LuaSupport(&kData);
	}
	void* pvData = lua_newuserdata(pkState, sizeof(LuaSupport*));
	kData.m_spLuaSupport->IncRefCount();
	*(LuaSupport**)pvData = kData.m_spLuaSupport;
	lua_newtable(pkState);
	lua_pushstring(pkState, "__index");
	lua_pushboolean(pkState, bEnableWrite ? 1 : 0);
	lua_pushcclosure(pkState, &DataIndexArray, 1);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__newindex");
	if(bEnableWrite)
	{
		lua_pushcfunction(pkState, &DataNewIndexArray);
	}
	else
	{
		lua_pushcfunction(pkState, &NoWriteNewIndex);
	}
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__gc");
	lua_pushcfunction(pkState, &DestructorData);
	lua_rawset(pkState, -3);
	lua_pushstring(pkState, "__tostring");
	lua_pushcfunction(pkState, &PrintData);
	lua_rawset(pkState, -3);
	lua_setmetatable(pkState, -2);
	return 1;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeNetEntity)
{

}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeNetEntity, Type);
	VeLuaClassEnumFuncImpl(VeNetEntity, Store);
	VeLuaClassEnumFuncImpl(VeNetEntity, ValueType);
	VeLuaClassEnumFuncImpl(VeNetEntity, ArrayFunc);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeNetEntity, Type)
{
	VeLuaClassEnumBase(VeNetEntity, Type);
	VeLuaClassEnumSlot(VeNetEntity, Type, TYPE_GLOBAL, "global");
	VeLuaClassEnumSlot(VeNetEntity, Type, TYPE_PROPERTY, "property");
	VeLuaClassEnumSlot(VeNetEntity, Type, TYPE_GROUP, "group");
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeNetEntity, Store)
{
	VeLuaClassEnumBase(VeNetEntity, Store);
	VeLuaClassEnumSlot(VeNetEntity, Store, STORE_STANDARD, "standard");
	VeLuaClassEnumSlot(VeNetEntity, Store, STORE_MEDIUM, "medium");
	VeLuaClassEnumSlot(VeNetEntity, Store, STORE_FASTEST, "fastest");
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeNetEntity, ValueType)
{
	VeLuaClassEnumBase(VeNetEntity, ValueType);
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_AUTO, "auto");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeUInt8, "uint8");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeUInt16, "uint16");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeUInt32, "uint32");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeUInt64, "uint64");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeInt8, "int8");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeInt16, "int16");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeInt32, "int32");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeInt64, "int64");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeFloat32, "float");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeFloat64, "double");
	VeLuaClassEnumSlot(VeNetEntity, ValueType, VALUE_VeString, "string");
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeNetEntity, ArrayFunc)
{
	VeLuaClassEnumBase(VeNetEntity, ArrayFunc);
	VeLuaClassEnumSlot(VeNetEntity, ArrayFunc, ARRAY_SIZE, "size");
	VeLuaClassEnumSlot(VeNetEntity, ArrayFunc, ARRAY_FRONT, "front");
	VeLuaClassEnumSlot(VeNetEntity, ArrayFunc, ARRAY_BACK, "back");
	VeLuaClassEnumSlot(VeNetEntity, ArrayFunc, ARRAY_PUSHBACK, "push_back");
	VeLuaClassEnumSlot(VeNetEntity, ArrayFunc, ARRAY_POPBACK, "pop_back");
	VeLuaClassEnumSlot(VeNetEntity, ArrayFunc, ARRAY_DELETE, "delete");
	VeLuaClassEnumSlot(VeNetEntity, ArrayFunc, ARRAY_CLEAR, "clear");
}
//--------------------------------------------------------------------------
VeNetEntityManager::VeNetEntityManager(Type eType) : m_eType(eType)
{

}
//--------------------------------------------------------------------------
VeNetEntityManager::~VeNetEntityManager()
{

}
//--------------------------------------------------------------------------
void VeNetEntityManager::LoadConfig(VeXMLElement* pkRoot)
{
	if(pkRoot)
	{
		VeXMLElement* pkTemp(NULL);

		pkTemp = pkRoot->FirstChildElement("enums");
		if(pkTemp)
		{
			pkTemp = pkTemp->FirstChildElement();
			while(pkTemp)
			{
				LoadEnum(pkTemp);
				pkTemp = pkTemp->NextSiblingElement();
			}
		}

		pkTemp = pkRoot->FirstChildElement("structs");
		if(pkTemp)
		{
			pkTemp = pkTemp->FirstChildElement();
			while(pkTemp)
			{
				LoadStruct(pkTemp);
				pkTemp = pkTemp->NextSiblingElement();
			}
		}

		pkTemp = pkRoot->FirstChildElement("entities");
		if(pkTemp)
		{
			pkTemp = pkTemp->FirstChildElement();
			while(pkTemp)
			{
				LoadEntity(pkTemp);
				pkTemp = pkTemp->NextSiblingElement();
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntityManager::LoadEnum(VeXMLElement* pkEnum)
{
	if(!m_kEnumMap.Find(pkEnum->Value()))
	{
		VeNetEntity::EnumDesc& kDesc = m_kEnumMap[pkEnum->Value()];
		VeXMLElement* pkTemp = pkEnum->FirstChildElement();
		while(pkTemp)
		{
			kDesc.m_kStrToInt[pkTemp->Value()] = kDesc.m_kIntToStr.Size();
			kDesc.m_kIntToStr.PushBack(pkTemp->Value());
			if(kDesc.m_kIntToStr.Size() <= 0xff)
			{
				pkTemp = pkTemp->NextSiblingElement();
			}
			else
			{
				break;
			}
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntityManager::LoadStruct(VeXMLElement* pkStruct)
{
	if(!m_kStructMap.Find(pkStruct->Value()))
	{
		VeVector<PropertyDesc>& kVec = m_kStructMap[pkStruct->Value()];
		VeXMLElement* pkTemp = pkStruct->FirstChildElement();
		while(pkTemp)
		{
			kVec.Increase();
			PropertyDesc& kDesc = kVec.Back();
			kDesc.m_kName = pkTemp->Value();
			kDesc.m_kType = pkTemp->Attribute("type");
			kDesc.m_kDefault = pkTemp->Attribute("default");
			kDesc.m_bArray = pkTemp->Attribute("array", false);
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntityManager::LoadEntity(VeXMLElement* pkEntity)
{
	if(!m_kEntityMap.Find(pkEntity->Value()))
	{
		m_kEntityArray.Increase();
		m_kEntityMap[pkEntity->Value()] = m_kEntityArray.Size() - 1;
		VeNetEntityPtr& spEntity = m_kEntityArray.Back();
		spEntity = VE_NEW VeNetEntity();
		spEntity->m_kName = pkEntity->Value();
		spEntity->m_u32Index = m_kEntityArray.Size() - 1;
		spEntity->m_eType = VeNetEntity::TypeLua::ToEnum(pkEntity->Attribute("type"), VeNetEntity::TYPE_MAX);
		VeXMLElement* pkProperties = pkEntity->FirstChildElement("properties");
		if(pkProperties)
		{
			spEntity->m_eStore = VeNetEntity::StoreLua::ToEnum(pkProperties->Attribute("store"), VeNetEntity::STORE_STANDARD);
			spEntity->m_f32Period = pkProperties->Attribute("period", 0.0f);
			spEntity->m_u32TabSize = pkProperties->Attribute("tab_size", VeUInt32(32));
			VeXMLElement* pkTemp = pkProperties->FirstChildElement();
			while(pkTemp)
			{
				LoadProperty(spEntity, pkTemp);
				pkTemp = pkTemp->NextSiblingElement();
			}
			VeUInt16 u16Database(0), u16Client(0);
			for(VeUInt32 i(0); i < spEntity->m_kProperties.Size(); ++i)
			{
				VeNetEntity::Property& kProp = *spEntity->m_kProperties[i];
				if(kProp.HasFlag(VeNetEntity::Property::FLAG_CLIENT))
				{
					kProp.m_u16Client = u16Client++;
				}
				else
				{
					kProp.m_u16Client = VE_UINT16_MAX;
				}
				if(kProp.HasFlag(VeNetEntity::Property::FLAG_DATABASE))
				{
					kProp.m_u16Database = u16Database++;
				}
				else
				{
					kProp.m_u16Database = VE_UINT16_MAX;
				}
				if(GetType() == TYPE_CLIENT)
				{
					spEntity->m_kNameMap[kProp.m_kName] = kProp.m_u16Client;
				}
			}
		}
		if(m_eType != TYPE_DATABASE)
		{
			VeXMLElement* pkBase = pkEntity->FirstChildElement("base");
			if(pkBase)
			{
				VeXMLElement* pkTemp = pkBase->FirstChildElement();
				while(pkTemp)
				{
					LoadBaseFunc(spEntity, pkTemp);
					pkTemp = pkTemp->NextSiblingElement();
				}
			}
			VeXMLElement* pkClient = pkEntity->FirstChildElement("client");
			if(pkClient)
			{
				VeXMLElement* pkTemp = pkClient->FirstChildElement();
				while(pkTemp)
				{
					LoadClientFunc(spEntity, pkTemp);
					pkTemp = pkTemp->NextSiblingElement();
				}
			}
		}
		if(spEntity->m_eType != VeNetEntity::TYPE_GLOBAL && m_eType == TYPE_CLIENT)
		{
			spEntity->m_i32UpdateFunc = g_pLua->Ref(spEntity->m_kName + ".update");
			VE_ASSERT(spEntity->m_i32UpdateFunc > 0);
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntityManager::LoadProperty(const VeNetEntityPtr& spEntity,
	VeXMLElement* pkProperty)
{
	PropertyDesc kDesc;
	kDesc.m_kName = pkProperty->Value();
	kDesc.m_kType = pkProperty->Attribute("type");
	kDesc.m_kDefault = pkProperty->Attribute("default");
	kDesc.m_bArray = pkProperty->Attribute("array", false);
	VeNetEntity::PropertyPtr spProperty;
	if(!spProperty) spProperty = CreateValue(kDesc);
	if(!spProperty) spProperty = CreateEnum(kDesc);
	if(!spProperty) spProperty = CreateStruct(kDesc);
	if(spProperty)
	{
		spProperty->SetFlag(VeNetEntity::Property::FLAG_CLIENT, pkProperty->Attribute("client", true));
		spProperty->SetFlag(VeNetEntity::Property::FLAG_DATABASE, pkProperty->Attribute("database", true));
		VeUInt32* pu32Iter = spEntity->m_kNameMap.Find(spProperty->m_kName);
		if(!pu32Iter)
		{
			if(GetType() != TYPE_CLIENT && spEntity->m_kProperties.Empty() && spEntity->m_eType != VeNetEntity::TYPE_GLOBAL)
			{
				VE_ASSERT(spProperty->GetType() == VeNetEntity::Property::TYPE_VALUE);
				VeNetEntity::Value& kValue = (VeNetEntity::Value&)*spProperty;
				if(kValue.m_eType < VeNetEntity::VALUE_VeFloat32)
				{
					kValue.m_spKeyMap = VE_NEW VeNetEntity::IntMap(spEntity->m_u32TabSize);
				}
				else if(kValue.m_eType == VeNetEntity::VALUE_VeString)
				{
					kValue.m_spKeyMap = VE_NEW VeNetEntity::StrMap(spEntity->m_u32TabSize);
				}
				VE_ASSERT(kValue.m_spKeyMap);
			}
			spProperty->m_u16Index = spEntity->m_kProperties.Size();
			spEntity->m_kNameMap[spProperty->m_kName] = spProperty->m_u16Index;
			spEntity->m_kProperties.PushBack(spProperty);
		}
	}
}
//--------------------------------------------------------------------------
void VeNetEntityManager::LoadBaseFunc(const VeNetEntityPtr& spEntity,
	VeXMLElement* pkFunc)
{
	VE_ASSERT(spEntity);
	spEntity->m_kBaseFuncMap[pkFunc->Value()] = spEntity->m_kBaseFuncArray.Size();
	spEntity->m_kBaseFuncArray.Increase();
	VeNetEntity::RpcFunc& kNew = spEntity->m_kBaseFuncArray.Back();
	kNew.m_kName = pkFunc->Value();
	kNew.m_u32Index = spEntity->m_kBaseFuncArray.Size() - 1;
	VeXMLElement* pkIn = pkFunc->FirstChildElement("in");
	if(pkIn)
	{
		VeXMLElement* pkTemp = pkIn->FirstChildElement();
		while(pkTemp)
		{
			PropertyDesc kDesc;
			kDesc.m_kName = pkTemp->Value();
			kDesc.m_kType = pkTemp->Attribute("type");
			kDesc.m_kDefault = pkTemp->Attribute("default");
			kDesc.m_bArray = pkTemp->Attribute("array", false);
			VeNetEntity::PropertyPtr spProperty;
			if(!spProperty) spProperty = CreateValue(kDesc);
			if(!spProperty) spProperty = CreateEnum(kDesc);
			if(!spProperty) spProperty = CreateStruct(kDesc);
			if(spProperty)
			{
				kNew.m_kInParams.PushBack(spProperty);
			}
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
	VeXMLElement* pkOut = pkFunc->FirstChildElement("out");
	if(pkOut)
	{
		VeXMLElement* pkTemp = pkOut->FirstChildElement();
		while(pkTemp)
		{
			PropertyDesc kDesc;
			kDesc.m_kName = pkTemp->Value();
			kDesc.m_kType = pkTemp->Attribute("type");
			kDesc.m_kDefault = pkTemp->Attribute("default");
			kDesc.m_bArray = pkTemp->Attribute("array", false);
			VeNetEntity::PropertyPtr spProperty;
			if(!spProperty) spProperty = CreateValue(kDesc);
			if(!spProperty) spProperty = CreateEnum(kDesc);
			if(!spProperty) spProperty = CreateStruct(kDesc);
			if(spProperty)
			{
				kNew.m_kOutParams.PushBack(spProperty);
			}
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
	if(GetType() == TYPE_BASE)
	{
		kNew.m_i32FuncRef = g_pLua->Ref(spEntity->m_kName + "." + kNew.m_kName);
		VE_ASSERT(kNew.m_i32FuncRef > 0);
	}
}
//--------------------------------------------------------------------------
void VeNetEntityManager::LoadClientFunc(const VeNetEntityPtr& spEntity,
	VeXMLElement* pkFunc)
{
	VE_ASSERT(spEntity);
	spEntity->m_kClientFuncMap[pkFunc->Value()] = spEntity->m_kClientFuncArray.Size();
	spEntity->m_kClientFuncArray.Increase();
	VeNetEntity::RpcFunc& kNew = spEntity->m_kClientFuncArray.Back();
	kNew.m_kName = pkFunc->Value();
	kNew.m_u32Index = spEntity->m_kClientFuncArray.Size() - 1;
	VeXMLElement* pkIn = pkFunc->FirstChildElement("in");
	if(pkIn)
	{
		VeXMLElement* pkTemp = pkIn->FirstChildElement();
		while(pkTemp)
		{
			PropertyDesc kDesc;
			kDesc.m_kName = pkTemp->Value();
			kDesc.m_kType = pkTemp->Attribute("type");
			kDesc.m_kDefault = pkTemp->Attribute("default");
			kDesc.m_bArray = pkTemp->Attribute("array", false);
			VeNetEntity::PropertyPtr spProperty;
			if(!spProperty) spProperty = CreateValue(kDesc);
			if(!spProperty) spProperty = CreateEnum(kDesc);
			if(!spProperty) spProperty = CreateStruct(kDesc);
			if(spProperty)
			{
				kNew.m_kInParams.PushBack(spProperty);
			}
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
	VeXMLElement* pkOut = pkFunc->FirstChildElement("out");
	if(pkOut)
	{
		VeXMLElement* pkTemp = pkOut->FirstChildElement();
		while(pkTemp)
		{
			PropertyDesc kDesc;
			kDesc.m_kName = pkTemp->Value();
			kDesc.m_kType = pkTemp->Attribute("type");
			kDesc.m_kDefault = pkTemp->Attribute("default");
			kDesc.m_bArray = pkTemp->Attribute("array", false);
			VeNetEntity::PropertyPtr spProperty;
			if(!spProperty) spProperty = CreateValue(kDesc);
			if(!spProperty) spProperty = CreateEnum(kDesc);
			if(!spProperty) spProperty = CreateStruct(kDesc);
			if(spProperty)
			{
				kNew.m_kOutParams.PushBack(spProperty);
			}
			pkTemp = pkTemp->NextSiblingElement();
		}
	}
	if(GetType() == TYPE_CLIENT)
	{
		kNew.m_i32FuncRef = g_pLua->Ref(spEntity->m_kName + "." + kNew.m_kName);
		VE_ASSERT(kNew.m_i32FuncRef > 0);
	}
}
//--------------------------------------------------------------------------
VeNetEntity::PropertyPtr VeNetEntityManager::CreateValue(
	PropertyDesc& kDesc, const VeChar8* pcField)
{
	VeNetEntity::ValueType eType = VeNetEntity::ValueTypeLua::ToEnum(
		kDesc.m_kType, VeNetEntity::VALUE_TYPE_MAX);
	if(eType < VeNetEntity::VALUE_TYPE_MAX)
	{
		VeNetEntity::Value* pkValue = VE_NEW VeNetEntity::Value;
		pkValue->m_kField = pcField;
		pkValue->m_kName = kDesc.m_kName;
		pkValue->m_eType = eType;
		switch(eType)
		{
		case VeNetEntity::VALUE_VeString:
			{
				VeUInt32 u32Len = (VeUInt32)VE_MIN(kDesc.m_kDefault.Length(), 255);
				pkValue->m_pbyBuffer = VeAlloc(VeByte, u32Len + 3);
				*(VeUInt16*)(pkValue->m_pbyBuffer) = 255;
				VeMemcpy(pkValue->m_pbyBuffer + 2, kDesc.m_kDefault.GetString(), u32Len + 1);
			}
			break;
		case VeNetEntity::VALUE_VeFloat32:
		case VeNetEntity::VALUE_VeFloat64:
			pkValue->m_f64Default = VeAtof(kDesc.m_kDefault);
			break;
		default:
			pkValue->m_i64Default = (VeInt64)VeAtoi(kDesc.m_kDefault);
			break;
		}
		if(kDesc.m_bArray)
		{
			VeNetEntity::Array* pkArray = VE_NEW VeNetEntity::Array;
			pkArray->m_kField = pkValue->m_kField;
			pkArray->m_kName = pkValue->m_kName;
			pkArray->m_spContent = pkValue;
			return pkArray;
		}
		else
		{
			return pkValue;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeNetEntity::PropertyPtr VeNetEntityManager::CreateEnum(
	PropertyDesc& kDesc, const VeChar8* pcField)
{
	VeNetEntity::EnumDesc* pkIter = m_kEnumMap.Find(kDesc.m_kType);
	if(pkIter)
	{
		VeNetEntity::Enum* pkEnum = VE_NEW VeNetEntity::Enum(*pkIter);
		pkEnum->m_kField = pcField;
		pkEnum->m_kName = kDesc.m_kName;
		const VeUInt8* pu8Iter = pkEnum->m_kDesc.m_kStrToInt.Find(kDesc.m_kDefault);
		pkEnum->m_u8Default = pu8Iter ? (*pu8Iter) : 0;
		if(kDesc.m_bArray)
		{
			VeNetEntity::Array* pkArray = VE_NEW VeNetEntity::Array;
			pkArray->m_kField = pkEnum->m_kField;
			pkArray->m_kName = pkEnum->m_kName;
			pkArray->m_spContent = pkEnum;
			return pkArray;
		}
		else
		{
			return pkEnum;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeNetEntity::PropertyPtr VeNetEntityManager::CreateStruct(
	PropertyDesc& kDesc, const VeChar8* pcField)
{
	VeVector<PropertyDesc>* pkIter = m_kStructMap.Find(kDesc.m_kType);
	if(pkIter)
	{
		VeNetEntity::Struct* pkStruct = VE_NEW VeNetEntity::Struct;
		pkStruct->m_kField = pcField;
		pkStruct->m_kName = kDesc.m_kName;
		VeString kFieldInner = pkStruct->m_kField.Length()
			? pkStruct->m_kField + "_" + pkStruct->m_kName : pkStruct->m_kName;
		for(VeVector<PropertyDesc>::iterator it = pkIter->Begin();
			it != pkIter->End(); ++it)
		{
			VeNetEntity::PropertyPtr spProperty;
			if(!spProperty) spProperty = CreateValue(*it, kFieldInner);
			if(!spProperty) spProperty = CreateEnum(*it, kFieldInner);
			if(!spProperty) spProperty = CreateStruct(*it, kFieldInner);
			if(spProperty)
			{
				VeUInt32* pu32Iter = pkStruct->m_kNameMap.Find(spProperty->m_kName);
				if(!pu32Iter)
				{
					pkStruct->m_u16Index = pkStruct->m_kProperties.Size();
					pkStruct->m_u16Client = pkStruct->m_u16Index;
					pkStruct->m_u16Database = pkStruct->m_u16Index;
					pkStruct->m_kNameMap[spProperty->m_kName] = pkStruct->m_u16Index;
					pkStruct->m_kProperties.PushBack(spProperty);
				}
			}
		}
		if(kDesc.m_bArray)
		{
			VeNetEntity::Array* pkArray = VE_NEW VeNetEntity::Array;
			pkArray->m_kField = pkStruct->m_kField;
			pkArray->m_kName = pkStruct->m_kName;
			pkArray->m_spContent = pkStruct;
			return pkArray;
		}
		else
		{
			return pkStruct;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
VeUInt32 VeNetEntityManager::GetEntityIndex(const VeChar8* pcName)
{
	VeUInt32* pu32Iter = m_kEntityMap.Find(pcName);
	return pu32Iter ? *pu32Iter : GetEntityNum();
}
//--------------------------------------------------------------------------
const VeChar8* VeNetEntityManager::GetEntityName(VeUInt32 u32Index)
{
	return u32Index < m_kEntityArray.Size() ? (const VeChar8*)(m_kEntityArray[u32Index]->m_kName) : (const VeChar8*)NULL;
}
//--------------------------------------------------------------------------
VeNetEntityPtr VeNetEntityManager::GetEntity(const VeChar8* pcName)
{
	VeUInt32* pu32Iter = m_kEntityMap.Find(pcName);
	if(pu32Iter)
	{
		VE_ASSERT((*pu32Iter) < m_kEntityArray.Size());
		return m_kEntityArray[*pu32Iter];
	}
	else
	{
		return NULL;
	}
}
//--------------------------------------------------------------------------
VeNetEntityPtr VeNetEntityManager::GetEntity(VeUInt32 u32Index)
{
	return u32Index < m_kEntityArray.Size() ? m_kEntityArray[u32Index] : NULL;
}
//--------------------------------------------------------------------------
VeEntityManagerClient::VeEntityManagerClient()
	: VeNetEntityManager(TYPE_CLIENT)
{

}
//--------------------------------------------------------------------------
VeEntityManagerClient::~VeEntityManagerClient()
{

}
//--------------------------------------------------------------------------
void VeEntityManagerClient::ClearEntities()
{
	for(VeUInt32 i(0); i < m_kEntityArray.Size(); ++i)
	{
		m_kEntityArray[i]->m_kDataArray.Clear();
	}
}
//--------------------------------------------------------------------------
