////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeTextTable.h
//  Version:     v1.00
//  Created:     18/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeTextTable : public VeResource
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeTextTable);
public:
	enum Type
	{
		TYPE_INT,
		TYPE_STR,
		TYPE_MAX
	};
	VeLuaClassEnumDef(Type);

	struct Field
	{
		VeString m_kName;
		Type m_eType;
	};

	struct VE_POWER_API Value
	{
		Value();

		~Value();

		void Set(const VeChar8* pcStr);

		void Set(VeInt32 i32Int);

		VeInt32 GetInt() const;

		const VeChar8* GetStr() const;

		Type m_eType;
		union
		{
			VeInt32 m_i32Int;
			VeChar8* m_pcStr;
		};
	};

	VeTextTable(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeTextTable();

	VE_INLINE const VeChar8* GetStr(const VeChar8* pcRow, const VeChar8* pcCol);

	VE_INLINE VeInt32 GetInt(const VeChar8* pcRow, const VeChar8* pcCol);

	VE_INLINE const VeVector<Field>& GetField() const;

	VE_INLINE Field* GetField(const VeChar8* pcCol);

	VE_INLINE const VeVector<Value>* Get(const VeChar8* pcRow);

	VE_INLINE const VeVector<Value>* GetFromIndex(VeInt32 i32Index);

	VeUInt32 GetRowIndex(const VeChar8* pcName);

	VeUInt32 GetRowIndex(VeInt32 i32Index);

	VeUInt32 GetColIndex(const VeChar8* pcName);

	Field* GetField(VeUInt32 u32Index);

	const VeChar8* GetStr(VeUInt32 u32Row, VeUInt32 u32Col);

	VeInt32 GetInt(VeUInt32 u32Row, VeUInt32 u32Col);

	const VeVector<Value>* Get(VeUInt32 u32Row);

	static VeUInt32 StrLine(VeVector<VeChar8>& kDst, const VeChar8* pcSrc);

	static VeUInt32 StrLine(VeVector<VeChar8>& kDst, const VeChar16* pcSrc);

	static void AddUnicode16(VeVector<VeChar8>& kDst, const VeChar16 c16Char);

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

	static const VeChar8* GetStr(const VeChar8* pcTable, const VeChar8* pcRow, const VeChar8* pcCol);

protected:
	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	virtual bool HasProcess();

	virtual void LoadProcess(const VeMemoryIStreamPtr& spStream);

	void ParseUTF8(const VeChar8* pcData);

	void ParseUnicode16(const VeChar16* pcData);

	VeStringMap<VeUInt32> m_kFieldMap;
	VeVector<Field> m_kFieldArray;
	VeStringMap<VeUInt32> m_kStrMap;
	VeHashMap<VeInt32,VeUInt32> m_kIntMap;
	VeVector< VeVector<Value> > m_kData;

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_POWER_API, VeTextTable, Type);
}

VeSmartPointer(VeTextTable);

#define VeGetTextTable(name,group) VeDynamicCast(VeTextTable,VeGetResource(VeResource::TEXT_TABLE,name,group))

#define VeLoadTextTable(name,group,async) VeDynamicCast(VeTextTable,VeLoadResource(VeResource::TEXT_TABLE,name,group,async))

#define VeLoadTextTableSync(name,group) VeLoadTextTable(name,group,false)

#define VeLoadTextTableAsync(name,group) VeLoadTextTable(name,group,true)

#ifndef VE_NO_INLINE
#	include "VeTextTable.inl"
#endif
