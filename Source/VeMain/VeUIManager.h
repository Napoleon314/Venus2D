////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIManager.h
//  Version:     v1.00
//  Created:     6/2/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeUIScene : public VeResource
{
	VeDeclareRTTI;
public:
	VeUIScene(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeUIScene();

	static VeResource* CreateResource(const VeChar8* pcName, const VeChar8* pcGroup);

protected:
	friend class VeUIManager;

	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	virtual bool HasProcess();

	virtual void LoadProcess(const VeMemoryIStreamPtr& spStream);

	virtual State AllWaitResLoaded();

	VeXMLDocument m_kDoc;
	VeVector<VeResourcePtr> m_kResArray;

};

VeSmartPointer(VeUIScene);

#define VeGetUIScene(name,group) VeDynamicCast(VeUIScene,VeGetResource(VeResource::UI_SCENE,name,group))

#define VeLoadUIScene(name,group,async) VeDynamicCast(VeUIScene,VeLoadResource(VeResource::UI_SCENE,name,group,async))

#define VeLoadUISceneSync(name,group) VeLoadUIScene(name,group,false)

#define VeLoadUISceneAsync(name,group) VeLoadUIScene(name,group,true)

class VE_MAIN_API VeUIManager : public VeSingleton<VeUIManager>
{
	VeDeclareLuaExport(VeUIManager);
public:
	typedef VeUIWidgetPtr (*CreateFunc)();

	struct Template : public VeRefObject
	{
		Template(VeXMLElement* pkElement)
			: m_pkElement(pkElement)
		{

		}

		virtual ~Template()
		{
			VE_SAFE_DELETE(m_pkElement);
		}

		VeXMLElement* m_pkElement;
	};

	typedef VePointer<Template> TemplatePtr;

	VeUIManager();

	virtual ~VeUIManager();

	VE_INLINE const VeUILayoutPtr& GetMainLayout();

	void Init();

	void Term();

	void SetMainLayout(const VeChar8* pcName);

	void SetMainLayout(VeUILayout* pkLayout);

	void PushLayout(const VeChar8* pcName, VeFloat32 f32ZOrder);

	void PushLayout(VeUILayout* pkLayout, VeFloat32 f32ZOrder);

	void PopLayout();

	void PopLayout(VeFloat32 f32ZOrder);

	void PopAllLayouts();

	void PopAllLayouts(VeFloat32 f32ZOrder);

	void AddWidget(const VeUIWidgetPtr& spWidget);

	void DelWidget(const VeChar8* pcName);

	VeUIWidget* FindWidget(const VeChar8* pcName);

	void AddScene(const VeUIScenePtr& spScene);

	void DelScene(const VeChar8* pcName);

	void Load(VeXMLElement* pkUIScene);

	void Unload(VeXMLElement* pkUIScene);

	void LoadTemplate(VeXMLElement* pkTemplate);

	void UnloadTemplate(VeXMLElement* pkTemplate);

	VeUIWidgetPtr CreateWidget(VeXMLElement* pkWidget, VeUILayout* pkLayout = NULL);

	VeUIWidgetPtr CreateTemplate(VeXMLElement* pkWidget, VeUILayout* pkLayout = NULL);

	void RegisterCreateFunc(const VeChar8* pcName, CreateFunc pfuncCreate);

	template<class T>
	void RegisterCreate()
	{
		RegisterCreateFunc(T::ms_RTTI.GetName(), T::Create);
	}

protected:
	void DelName(VeUIWidget& kWidget);

	VeDeclInputDelegate(VeUIManager, InputCallback);

	VeStringMap<CreateFunc> m_kWidgetFactory;
	VeStringMap<VeUIScenePtr> m_kUISceneMap;
	VeStringMap<TemplatePtr> m_kTemplateMap;
	VeStringMap<VeUInt32> m_kWidgetMap;
	VeVector<VeUIWidgetPtr> m_kWidgetArray;
	VeUILayoutPtr m_spMainLayout;
	VeUILayoutPtr m_spActive;

};

#define g_pUIManager VeUIManager::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeUIManager.inl"
#endif
