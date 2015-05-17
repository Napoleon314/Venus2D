////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMaterialResource.h
//  Version:     v1.00
//  Created:     2/1/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeMaterialResource : public VeResource
{
public:
	VeMaterialResource(const VeChar8* pcName, const VeChar8* pcGroup);

	virtual ~VeMaterialResource();

	virtual State LoadImpl(const VeMemoryIStreamPtr& spStream);

	virtual void UnloadImpl();

	VE_INLINE const VeMaterialPtr& GetMaterial();

	VE_INLINE void DetachMaterial();

	static VeResource* Create(const VeChar8* pcName, const VeChar8* pcGroup);

protected:
	VeMaterialPtr m_spMaterial;

};

VeSmartPointer(VeMaterialResource);

#define VeGetMaterial(name,group) VeSmartPointerCast(VeMaterialResource,VeGetResource(VeResource::MATERIAL,name,group))

#define VeLoadMaterial(name,group,async) VeSmartPointerCast(VeMaterialResource,VeLoadResource(VeResource::MATERIAL,name,group,async))

#define VeLoadMaterialSync(name,group) VeLoadMaterial(name,group,false)

#define VeLoadMaterialAsync(name,group) VeLoadMaterial(name,group,true)

#ifndef VE_NO_INLINE
#	include "VeMaterialResource.inl"
#endif
