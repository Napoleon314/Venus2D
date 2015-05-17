////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeObject.h
//  Version:     v1.00
//  Created:     5/12/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#define VeSerializableObject(t)																\
	VE_FORCE_INLINE VeBinaryIStream& operator >> (VeBinaryIStream& kIn, t& kObj)			\
	{																						\
		VE_ASSERT(VeIsKindOf(VeObject, &kObj));												\
		kObj.From(kIn);																		\
		return kIn;																			\
	}																						\
	VE_FORCE_INLINE VeBinaryOStream& operator << (VeBinaryOStream& kOut, const t& kObj)		\
	{																						\
		VE_ASSERT(VeIsKindOf(VeObject, &kObj));												\
		kObj.To(kOut);																		\
		return kOut;																		\
	}

class VE_POWER_API VeObject : public VeRefObject
{
	VeDeclareRootRTTI(VeObject);
public:
	VeObject();

	virtual ~VeObject();

	const VeChar8* GetTypeName() const;

	virtual const VeChar8* ToString() const;

	virtual void From(VeBinaryIStream& kIn) = 0;

	virtual void To(VeBinaryOStream& kOut) const = 0;

	virtual void From(VeXMLElement* pkElement) {}

	virtual VeObject* Clone() const { return NULL; }

	static const VeChar8* ToString(const VeObject& kObj);

	static const VeChar8* TypeName();

};

VeSmartPointer(VeObject);

VeSerializableObject(VeObject);
