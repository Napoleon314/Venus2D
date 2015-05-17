////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeResource.h
//  Version:     v1.00
//  Created:     8/11/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeResourceGroup : public VeRefObject
{
public:
	VeResourceGroup(const VeChar8* pcName);

	~VeResourceGroup();

	const VeChar8* GetName();

	bool SetWriteDirectory(const VeChar8* pcName);

	bool PushReadDirectoryBack(const VeChar8* pcName);

	bool PushReadDirectoryFront(const VeChar8* pcName);

	void PopBackReadDirectory();

	void PopFrontReadDirectory();

	void Clear();

	VeUInt32 ReadDirNum();

	bool CanWrite();

protected:
	friend class VeResource;
	const VeFixedString m_kName;
	VeList<VeDirectory*> m_kReadDirectories;
	VeDirectory* m_pkWriteDirectory;

};

VeSmartPointer(VeResourceGroup);
VeSmartPointer(VeResource);

class VE_POWER_API VeResource : public VeBackgroundTask
{
	VeDeclareRootRTTI(VeResource);
	VeDeclareLuaRttiExport(VeResource);
public:

	enum Type
	{
		TEXT_TABLE,
		VERTEX_SHADER,
		PIXEL_SHADER,
		TEXTURE,
		TEXTURE_ATLAS,
		RENDER_FRAME,
		MATERIAL,
		DRAGON_BONES,
		FONT,
		UI_SCENE,
		SIMPLE_SOUND,
		TYPE_NUM
	};
	VeLuaClassEnumDef(Type);

	enum State
	{
		UNLOADED,
		LOADING,
		LOADED,
		INVALID
	};

	typedef VeMemberDelegate<VeResource, const VeMemoryIStreamPtr&> ReadDelegate;

	typedef VeEvent<const VeResourcePtr&> LoadEvent;
	typedef VeAbstractDelegate<const VeResourcePtr&> LoadDelegate;

	VeResource(Type eType, const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeResource();

	virtual void IncRefCount();

	virtual void DecRefCount();

	virtual bool LoadNow();

	virtual bool Load();

	virtual void Unload();

	virtual const VeChar8* GetLoadName();
	
	void SetGroup(const VeChar8* pcGroup);

	VE_INLINE const VeChar8* GetGroup();

	VE_INLINE const VeChar8* GetName();

	VE_INLINE Type GetType();

	VE_INLINE State GetState();

	VE_INLINE void AddLoadDelegate(LoadDelegate& kDelegate);

	VE_INLINE bool IsFreeListEnable();

	void SetFreeListEnable(bool bEnable);

	static Type StrToType(const VeChar8* pcName, Type eDefault);

protected:
	friend class VeResourceManager;

	void Wait(VeResource* pkRes);

	virtual void AsyncReadCallback(const VeMemoryIStreamPtr& spData);

	virtual void WaitResLoaded(VeResource* pkRes);

	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream) { return LOADED; }

	virtual void UnloadImpl() {}

	virtual State AllWaitResLoaded() { return LOADED; }

	virtual bool HasProcess() { return false; }

	virtual void LoadProcess(const VeMemoryIStreamPtr& spStream) {}

	virtual void DoBackgroundTask(VeBackgroundTaskQueue& kMgr);

	virtual void DoMainThreadTask(VeBackgroundTaskQueue& kMgr);

	virtual void TermRender() {}

	void AfterProcess();

	void ProcessEnd();

	const Type m_eType;
	VeFixedString m_kName;
	VeResourceGroupPtr m_spGroup;
	volatile State m_eState;
	ReadDelegate m_kReadDelegate;
	VeList<VeResource*> m_kTickWaitList;
	VeUInt32 m_u32WaitNumber;
	LoadEvent m_kLoadEvent;
	VeRefNode<VeResource*> m_kFreeNode;
	VeFloat32 m_f32FreeTime;

private:
	VeMemoryIStreamPtr m_spData;
	
};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_POWER_API, VeResource, Type);
}

#define VeDeclLoadResDelegate(class,name) \
	void name(const VeResourcePtr&); \
	VeMemberDelegate<class,const VeResourcePtr&> m_k##name

#define VeImplLoadResDelegate(class,name,res) \
	void class::name(const VeResourcePtr& res)

#ifndef VE_NO_INLINE
#	include "VeResource.inl"
#endif
