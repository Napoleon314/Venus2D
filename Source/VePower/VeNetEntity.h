////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeEntity.h
//  Version:     v1.00
//  Created:     6/11/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace RakNet
{
	class RakPeerInterface;
	struct Packet;
	class BitStream;
}

VeSmartPointer(VeNetEntity);

class VE_POWER_API VeNetEntity : public VeRefObject
{
	VeDeclareLuaExport(VeNetEntity);
public:
	enum Type
	{
		TYPE_GLOBAL,
		TYPE_PROPERTY,
		TYPE_GROUP,
		TYPE_MAX
	};
	VeLuaClassEnumDef(Type);

	enum Store
	{
		STORE_STANDARD,
		STORE_MEDIUM,
		STORE_FASTEST,
		STORE_MAX
	};
	VeLuaClassEnumDef(Store);

	enum ValueType
	{
		VALUE_AUTO,
		VALUE_VeUInt8,
		VALUE_VeUInt16,
		VALUE_VeUInt32,
		VALUE_VeUInt64,
		VALUE_VeInt8,
		VALUE_VeInt16,
		VALUE_VeInt32,
		VALUE_VeInt64,
		VALUE_VeFloat32,
		VALUE_VeFloat64,
		VALUE_VeString,
		VALUE_TYPE_MAX
	};
	VeLuaClassEnumDef(ValueType);

	enum ArrayFunc
	{
		ARRAY_SIZE,
		ARRAY_FRONT,
		ARRAY_BACK,
		ARRAY_PUSHBACK,
		ARRAY_POPBACK,
		ARRAY_DELETE,
		ARRAY_CLEAR,
		ARRAY_MAX
	};
	VeLuaClassEnumDef(ArrayFunc);

	struct KeyMap : public VeRefObject
	{
		enum Type
		{
			TYPE_STRING,
			TYPE_INTEGER,
			TYPE_MAX
		};

		virtual ~KeyMap() {}

		virtual Type GetType() const = 0;
	};

	typedef VePointer<KeyMap> KeyMapPtr;

	struct StrMap : public KeyMap
	{
		StrMap(VeUInt32 u32TableSize) : m_kMap(u32TableSize) {}

		virtual ~StrMap() {}

		virtual Type GetType() const
		{
			return TYPE_STRING;
		}

		VeStringMap<VeUInt32> m_kMap;
	};

	struct IntMap : public KeyMap
	{
		IntMap(VeUInt32 u32TableSize) : m_kMap(u32TableSize) {}

		virtual ~IntMap() {}

		virtual Type GetType() const
		{
			return TYPE_INTEGER;
		}

		VeHashMap<VeInt64,VeUInt32> m_kMap;
	};

	struct Property : public VeRefObject
	{
		enum Type
		{
			TYPE_VALUE,
			TYPE_ENUM,
			TYPE_STRUCT,
			TYPE_ARRAY,
			TYPE_MAX
		};

		enum Flag
		{
			FLAG_CLIENT,
			FLAG_DATABASE,
			FLAG_MAX
		};

		Property() : m_u32Flag(0), m_u16Index(0), m_u16Client(0), m_u16Database(0) {}

		virtual ~Property() {}

		void SetFlag(Flag eFlag, bool bEnable)
		{
			if(eFlag < FLAG_MAX)
			{
				if(bEnable)
				{
					VE_MASK_ADD(m_u32Flag, VE_MASK(eFlag));
				}
				else
				{
					VE_MASK_DEL(m_u32Flag, VE_MASK(eFlag));
				}
			}
		}

		bool HasFlag(Flag eFlag)
		{
			if(eFlag < FLAG_MAX)
			{
				return VE_MASK_HAS_ALL(m_u32Flag, VE_MASK(eFlag));
			}
			return false;
		}

		virtual Type GetType() const = 0;

		VeString m_kField;
		VeString m_kName;
		VeUInt32 m_u32Flag;
		VeUInt16 m_u16Index;
		VeUInt16 m_u16Client;
		VeUInt16 m_u16Database;
		
	};

	typedef VePointer<Property> PropertyPtr;

	struct Value : public Property
	{
		Value() : m_eType(VALUE_TYPE_MAX), m_i64Default(0) {}

		virtual ~Value()
		{
			if(m_eType == VALUE_VeString && m_pbyBuffer) VeFree(m_pbyBuffer);
		}

		virtual Type GetType() const { return TYPE_VALUE; }

		VePair<VeUInt32,VeUInt32> m_kIndex;
		ValueType m_eType;
		union
		{
			VeUInt64 m_u64Default;
			VeInt64 m_i64Default;
			VeFloat64 m_f64Default;
			VeByte* m_pbyBuffer;
		};
		KeyMapPtr m_spKeyMap;
	};

	struct EnumDesc
	{
		VeStringMap<VeUInt8> m_kStrToInt;
		VeVector<VeString> m_kIntToStr;
	};

	struct Enum : public Property
	{
		Enum(const EnumDesc& kEnum) : m_kDesc(kEnum) {}

		virtual Type GetType() const { return TYPE_ENUM; }

		const EnumDesc& m_kDesc;
		VePair<VeUInt32,VeUInt32> m_kIndex;
		VeUInt8 m_u8Default;
	};

	struct Struct : public Property
	{
		virtual Type GetType() const { return TYPE_STRUCT; }

		VeStringMap<VeUInt32> m_kNameMap;
		VeVector<PropertyPtr> m_kProperties;
	};

	struct Array : public Property
	{
		Array() : m_u32Table(0) {}

		virtual Type GetType() const { return TYPE_ARRAY; }

		VeUInt32 m_u32Table;
		PropertyPtr m_spContent;
	};

	struct DataHolder;
	struct Data;

	struct LuaSupport : VeRefObject
	{
		LuaSupport(DataHolder* pkHolder) : m_pkParent(pkHolder) {}

		DataHolder* m_pkParent;
	};

	typedef VePointer<LuaSupport> LuaSupportPtr;

	struct Data : public VeRefObject
	{
		enum Type
		{
			TYPE_VALUE,
			TYPE_ENUM,
			TYPE_STRUCT,
			TYPE_ARRAY,
			TYPE_ENTITY,
			TYPE_MAX
		};

		Data() : m_u32Index(0), m_pkObject(NULL), m_pkHolder(NULL)
		{
			m_kDirtyNode.m_tContent = this;
		}

		virtual ~Data() {}

		virtual Type GetType() const = 0;

		void NotifyDirty()
		{
			if(m_pkHolder && (!m_kDirtyNode.IsAttach()))
			{
				m_pkHolder->NotifyDirty(m_kDirtyNode);
			}
		}

		VeUInt32 m_u32Index;
		VeRefObject* m_pkObject;
		DataHolder* m_pkHolder;
		VeRefNode<Data*> m_kDirtyNode;
	};

	typedef VePointer<Data> DataPtr;

	struct DataValue : public Data
	{
		DataValue() : m_u64Value(0) {}

		virtual ~DataValue()
		{
			if(((Property*)m_pkObject)->GetType() == Property::TYPE_VALUE)
			{
				if(((Value*)m_pkObject)->m_eType == VALUE_VeString && m_pbyBuffer)
				{
					VeFree(m_pbyBuffer);
				}
			}
		}

		virtual Type GetType() const
		{
			return TYPE_VALUE;
		}

		union
		{
			VeUInt64 m_u64Value;
			VeInt64 m_i64Value;
			VeFloat64 m_f64Value;
			VeByte* m_pbyBuffer;
		};
	};

	typedef VePointer<DataValue> DataValuePtr;

	struct DataEnum : public Data
	{
		DataEnum() : m_u8Value(0) {}

		virtual ~DataEnum() {}

		virtual Type GetType() const
		{
			return TYPE_ENUM;
		}

		VeUInt8 m_u8Value;
	};

	typedef VePointer<DataEnum> DataEnumPtr;

	struct DataHolder : public Data
	{
		virtual ~DataHolder()
		{
			if(m_spLuaSupport)
			{
				m_spLuaSupport->m_pkParent = NULL;
				m_spLuaSupport = NULL;
			}
		}

		virtual void NotifyDirty(VeRefNode<Data*>& kNode) = 0;

		LuaSupportPtr m_spLuaSupport;
		
	};

	typedef VePointer<DataHolder> DataHolderPtr;

	struct DataArray : public DataHolder
	{
		DataArray() {}

		virtual ~DataArray() {}

		virtual Type GetType() const
		{
			return TYPE_ARRAY;
		}

		virtual void NotifyDirty(VeRefNode<Data*>& kNode)
		{
			Data::NotifyDirty();
		}

		VeVector< VePair<VeUInt32,DataPtr> > m_kDataArray;

	};

	typedef VePointer<DataArray> DataArrayPtr;

	struct DataContainer : public DataHolder
	{
		virtual ~DataContainer() {}
		
		virtual void NotifyDirty(VeRefNode<Data*>& kNode)
		{
			m_kDirtyList.AttachBack(kNode);
			Data::NotifyDirty();
		}

		VeVector<DataPtr> m_kDataArray;
		VeRefList<Data*> m_kDirtyList;
	};

	typedef VePointer<DataContainer> DataContainerPtr;

	struct DataStruct : public DataContainer
	{
		virtual Type GetType() const
		{
			return TYPE_STRUCT;
		}
	};

	typedef VePointer<DataStruct> DataStructPtr;

	struct DataEntity : public DataContainer
	{
		DataEntity() : m_i32Ref(0)
		{
			m_kNode.m_tContent = this;
		}

		virtual ~DataEntity()
		{
			ReleaseLuaData(g_pLua->GetLua(), *this);
		}

		virtual Type GetType() const
		{
			return TYPE_ENTITY;
		}

		VeRefNode<DataEntity*> m_kNode;
		VeInt32 m_i32Ref;
	};

	typedef VePointer<DataEntity> DataEntityPtr;

	struct TableInfoDB
	{
		TableInfoDB() : m_u32Reference(0), m_bNeedToLink(false) {}

		TableInfoDB& operator = (const TableInfoDB& kCopy)
		{
			m_kName = kCopy.m_kName;
			m_u32Reference = kCopy.m_u32Reference;
			m_bNeedToLink = kCopy.m_bNeedToLink;
			return *this;
		}

		VeString m_kName;
		VeUInt32 m_u32Reference;
		bool m_bNeedToLink;
	};

	struct RpcFunc
	{
		RpcFunc() : m_u32Index(0), m_i32FuncRef(0) {}

		RpcFunc& operator = (const RpcFunc& kFunc)
		{
			return *this;
		}

		VeString m_kName;
		VeUInt32 m_u32Index;
		VeInt32 m_i32FuncRef;
		VeVector<PropertyPtr> m_kInParams;
		VeVector<PropertyPtr> m_kOutParams;
	};

	VeNetEntity();

	virtual ~VeNetEntity();

	static DataPtr CreateData(Property& kProperty);

	static DataPtr CreateData(Value& kValue);

	static DataPtr CreateData(Enum& kEnum);

	static DataPtr CreateData(Struct& kStruct);

	static DataPtr CreateData(Array& kArray);

	static VeSizeT ToString(VeChar8* pcDesc, Data& kData);

	static VeSizeT ToString(VeChar8* pcDesc, DataValue& kData);

	static VeSizeT ToString(VeChar8* pcDesc, DataEnum& kData);

	static VeSizeT ToString(VeChar8* pcDesc, DataStruct& kData);

	static VeSizeT ToString(VeChar8* pcDesc, DataArray& kData);

	static VeSizeT ToString(VeChar8* pcDesc, DataEntity& kData);

	static bool Write(RakNet::BitStream& kOut, lua_State* pkState, const VeNetEntity::Value& kType);

	static bool Write(RakNet::BitStream& kOut, lua_State* pkState, const VeNetEntity::Enum& kType);

	static bool Write(RakNet::BitStream& kOut, lua_State* pkState, const VeNetEntity::Struct& kType);

	static bool Write(RakNet::BitStream& kOut, lua_State* pkState, const VeNetEntity::Array& kType);

	static bool Write(RakNet::BitStream& kOut, lua_State* pkState, const VeNetEntity::Property& kType);

	static void Write(RakNet::BitStream& kOut, const VeNetEntity::Value& kType);

	static void Write(RakNet::BitStream& kOut, const VeNetEntity::Enum& kType);

	static void Write(RakNet::BitStream& kOut, const VeNetEntity::Struct& kType);

	static void Write(RakNet::BitStream& kOut, const VeNetEntity::Array& kType);

	static void Write(RakNet::BitStream& kOut, const VeNetEntity::Property& kType);

	static bool Write(RakNet::BitStream& kOut, lua_State* pkState, const VeVector<VeNetEntity::PropertyPtr>& kInParams);

	static VeInt32 RetParam(lua_State* pkState, RakNet::BitStream& kIn, const VeNetEntity::Value& kType);

	static VeInt32 RetParam(lua_State* pkState, RakNet::BitStream& kIn, const VeNetEntity::Enum& kType);

	static VeInt32 RetParam(lua_State* pkState, RakNet::BitStream& kIn, const VeNetEntity::Struct& kType);

	static VeInt32 RetParam(lua_State* pkState, RakNet::BitStream& kIn, const VeNetEntity::Array& kType);

	static VeInt32 RetParam(lua_State* pkState, RakNet::BitStream& kIn, const VeNetEntity::Property& kType);

	static VeInt32 RetParam(lua_State* pkState, RakNet::BitStream& kIn, const VeVector<VeNetEntity::PropertyPtr>& kOutParams);

	static VeInt32 RetParam(lua_State* pkState, const VeNetEntity::Value& kType);

	static VeInt32 RetParam(lua_State* pkState, const VeNetEntity::Enum& kType);

	static VeInt32 RetParam(lua_State* pkState, const VeNetEntity::Struct& kType);

	static VeInt32 RetParam(lua_State* pkState, const VeNetEntity::Array& kType);

	static VeInt32 RetParam(lua_State* pkState, const VeNetEntity::Property& kType);

	static VeInt32 RetParam(lua_State* pkState, const VeVector<VeNetEntity::PropertyPtr>& kOutParams);

	static void ReleaseLuaData(lua_State* pkState, DataEntity& kEntity);

	static void Write(RakNet::BitStream& kOut, const Data& kData);

	static void Write(RakNet::BitStream& kOut, const DataValue& kData);

	static void Write(RakNet::BitStream& kOut, const DataEnum& kData);

	static void Write(RakNet::BitStream& kOut, const DataStruct& kData);

	static void Write(RakNet::BitStream& kOut, const DataArray& kData);

	static void Write(RakNet::BitStream& kOut, const DataEntity& kData);

	static void Write(RakNet::BitStream& kOut, const DataEntity& kData, Property::Flag eFlag);

	static void WriteUpdate(RakNet::BitStream& kOut, const Data& kData);

	static void WriteUpdate(RakNet::BitStream& kOut, const DataStruct& kData);

	static void WriteUpdate(RakNet::BitStream& kOut, const DataEntity& kData, Property::Flag eFlag);

	static void Read(RakNet::BitStream& kIn, Data& kData);

	static void Read(RakNet::BitStream& kIn, DataValue& kData);

	static void Read(RakNet::BitStream& kIn, DataEnum& kData);

	static void Read(RakNet::BitStream& kIn, DataArray& kData);

	static void Read(RakNet::BitStream& kIn, DataContainer& kData);

	static void ReadUpdate(RakNet::BitStream& kIn, Data& kData);

	static void ReadUpdate(RakNet::BitStream& kIn, DataContainer& kData);

	static DataPtr CreateData(RakNet::BitStream& kStream, Value& kValue);
	
	static DataPtr CreateData(RakNet::BitStream& kStream, Enum& kEnum);

	static DataPtr CreateData(RakNet::BitStream& kStream, Struct& kStruct);

	static DataPtr CreateData(RakNet::BitStream& kStream, Array& kArray);

	static DataPtr CreateData(RakNet::BitStream& kStream, Property& kProperty);

	static void ClearDirty(Data& kData);

	static void ClearDirty(DataArray& kData);

	static void ClearDirty(DataContainer& kData);

	static void ClearDirty(DataEntity& kData);

	static void Set(Data& kDsc, Data& kSrc);

	static void Set(DataValue& kDsc, DataValue& kSrc);

	static void Set(DataEnum& kDsc, DataEnum& kSrc);

	static void Set(DataStruct& kDsc, DataStruct& kSrc);

	static void Set(DataArray& kDsc, DataArray& kSrc);

	static void SetParam(lua_State* pkState, Data& kData);

	static void SetParam(lua_State* pkState, DataValue& kData);

	static void SetParam(lua_State* pkState, DataEnum& kData);

	static void SetParam(lua_State* pkState, DataStruct& kData);

	static void SetParam(lua_State* pkState, DataArray& kData);

	static VeInt32 DataIndex(lua_State* pkState);

	static VeInt32 DataNewIndex(lua_State* pkState);

	static VeInt32 DataArrayPushBack(lua_State* pkState);

	static VeInt32 DataArrayPopBack(lua_State* pkState);

	static VeInt32 DataArrayDelete(lua_State* pkState);

	static VeInt32 DataArrayClear(lua_State* pkState);

	static VeInt32 DataIndexArray(lua_State* pkState);

	static VeInt32 DataNewIndexArray(lua_State* pkState);

	static VeInt32 NoWriteNewIndex(lua_State* pkState);

	static VeInt32 DestructorData(lua_State* pkState);

	static VeInt32 PrintData(lua_State* pkState);

	static VeInt32 RetParam(lua_State* pkState, Data& kData, bool bEnableWrite);

	static VeInt32 RetParam(lua_State* pkState, DataValue& kData);

	static VeInt32 RetParam(lua_State* pkState, DataEnum& kData);

	static VeInt32 RetParam(lua_State* pkState, DataContainer& kData, bool bEnableWrite);

	static VeInt32 RetParam(lua_State* pkState, DataArray& kData, bool bEnableWrite);

	VeString m_kName;
	VeUInt32 m_u32Index;
	Type m_eType;
	Store m_eStore;
	VeFloat32 m_f32Period;
	VeUInt32 m_u32TabSize;
	VeStringMap<VeUInt32> m_kNameMap;
	VeVector<PropertyPtr> m_kProperties;
	VeVector<TableInfoDB> m_kTableArray;
	VeVector<DataEntityPtr> m_kDataArray;
	VeRefList<DataEntity*> m_kFreeList;
	VeStringMap<VeUInt32> m_kBaseFuncMap;
	VeVector<RpcFunc> m_kBaseFuncArray;
	VeStringMap<VeUInt32> m_kClientFuncMap;
	VeVector<RpcFunc> m_kClientFuncArray;
	VeInt32 m_i32UpdateFunc;

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_POWER_API, VeNetEntity, Type);
	VeLuaClassEnumFuncDef(VE_POWER_API, VeNetEntity, Store);
	VeLuaClassEnumFuncDef(VE_POWER_API, VeNetEntity, ValueType);
	VeLuaClassEnumFuncDef(VE_POWER_API, VeNetEntity, ArrayFunc);
}

class VE_POWER_API VeNetEntityManager : public VeRefObject
{
public:
	enum Type
	{
		TYPE_DATABASE,
		TYPE_BASE,
		TYPE_CLIENT
	};

	struct PropertyDesc
	{
		PropertyDesc() : m_bArray(false) {}

		PropertyDesc& operator = (const PropertyDesc& kDesc)
		{
			m_kName = kDesc.m_kName;
			m_kType = kDesc.m_kType;
			m_kDefault = kDesc.m_kDefault;
			m_bArray = kDesc.m_bArray;
			return *this;
		}

		VeString m_kName;
		VeString m_kType;
		VeString m_kDefault;
		bool m_bArray;
	};

	VeNetEntityManager(Type eType);

	virtual ~VeNetEntityManager();

	VE_INLINE Type GetType();

	VE_INLINE VeUInt32 GetEntityNum();

	void LoadConfig(VeXMLElement* pkRoot);

	void LoadEnum(VeXMLElement* pkEnum);

	void LoadStruct(VeXMLElement* pkStruct);

	void LoadEntity(VeXMLElement* pkEntity);

	void LoadProperty(const VeNetEntityPtr& spEntity, VeXMLElement* pkProperty);

	void LoadBaseFunc(const VeNetEntityPtr& spEntity, VeXMLElement* pkFunc);

	void LoadClientFunc(const VeNetEntityPtr& spEntity, VeXMLElement* pkFunc);

	VeUInt32 GetEntityIndex(const VeChar8* pcName);
	
	const VeChar8* GetEntityName(VeUInt32 u32Index);

	VeNetEntityPtr GetEntity(const VeChar8* pcName);

	VeNetEntityPtr GetEntity(VeUInt32 u32Index);

protected:
	VeNetEntity::PropertyPtr CreateValue(PropertyDesc& kDesc, const VeChar8* pcField = "");

	VeNetEntity::PropertyPtr CreateEnum(PropertyDesc& kDesc, const VeChar8* pcField = "");

	VeNetEntity::PropertyPtr CreateStruct(PropertyDesc& kDesc, const VeChar8* pcField = "");

	const Type m_eType;
	VeStringMap<VeNetEntity::EnumDesc> m_kEnumMap;
	VeStringMap< VeVector<PropertyDesc> > m_kStructMap;
	VeStringMap<VeUInt32> m_kEntityMap;
	VeVector<VeNetEntityPtr> m_kEntityArray;

};

VeSmartPointer(VeNetEntityManager);

class VeEntityManagerClient : public VeNetEntityManager
{
public:
	VeEntityManagerClient();

	virtual ~VeEntityManagerClient();

	void ClearEntities();

};

#ifndef VE_NO_INLINE
#	include "VeNetEntity.inl"
#endif
