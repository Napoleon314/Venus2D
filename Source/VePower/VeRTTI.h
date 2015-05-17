////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeRTTI.h
//  Version:     v1.00
//  Created:     29/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_POWER_API VeRTTI : public VeMemObject
{
public:
	VeRTTI(const VeChar8* pcName, const VeRTTI* pkBaseRTTI);

	const VeChar8* GetName() const;

	const VeRTTI* GetBaseRTTI() const;

protected:
	const VeChar8* m_pcName;
	const VeRTTI* m_pkBaseRTTI;
};

#define VeDeclareRootRTTI(classname) \
	public: \
		static const VeRTTI ms_RTTI; \
		virtual const VeRTTI* GetRTTI() const {return &ms_RTTI;} \
		static bool IsExactKindOf(const VeRTTI* pkRTTI, const classname* pkObject) \
		{ \
			if (!pkObject) \
			{ \
				return false; \
			} \
			return pkObject->IsExactKindOf(pkRTTI); \
		} \
		bool IsExactKindOf(const VeRTTI* pkRTTI) const \
		{ \
			return (GetRTTI() == pkRTTI); \
		} \
		static bool IsKindOf(const VeRTTI* pkRTTI, const classname* pkObject) \
		{ \
			if (!pkObject) \
			{ \
				return false; \
			} \
			return pkObject->IsKindOf(pkRTTI); \
		} \
		bool IsKindOf(const VeRTTI* pkRTTI) const \
		{ \
			const VeRTTI* pkTmp = GetRTTI(); \
			while (pkTmp) \
			{ \
				if (pkTmp == pkRTTI) \
				{ \
					return true; \
				} \
				pkTmp = pkTmp->GetBaseRTTI(); \
			} \
			return false; \
		} \
		static classname* VerifyStaticCastDebug(const VeRTTI* pkRTTI, const classname* pkObject) \
		{ \
			if (!pkObject) \
			{ \
				return NULL; \
			} \
			classname* pkDynamicCast = DynamicCast(pkRTTI, pkObject); \
			VE_ASSERT("VeVerifyStaticCast() caught an invalid type cast." \
				"Check callstack for invalid object typecast assumption." \
				&& pkDynamicCast); \
			return pkDynamicCast; \
		} \
		static classname* DynamicCast(const VeRTTI* pkRTTI, const classname* pkObject) \
		{ \
			if (!pkObject) \
			{ \
				return NULL; \
			} \
			return pkObject->DynamicCast(pkRTTI); \
		} \
		classname* DynamicCast(const VeRTTI* pkRTTI) const \
		{ \
			return (IsKindOf(pkRTTI) ? (classname*) this : 0 ); \
		}

#define VeDeclareRTTI \
	public: \
		static const VeRTTI ms_RTTI; \
		virtual const VeRTTI* GetRTTI() const {return &ms_RTTI;}

#define VeImplementRootRTTI(rootclassname) \
	const VeRTTI rootclassname::ms_RTTI(#rootclassname, 0)

#define VeImplementRTTI(classname, baseclassname) \
	const VeRTTI classname::ms_RTTI(#classname, &baseclassname::ms_RTTI)

#define VeIsExactKindOf(classname, pkObject) \
	classname::IsExactKindOf(&classname::ms_RTTI, pkObject)

#define VeIsKindOf(classname, pkObject) \
	classname::IsKindOf(&classname::ms_RTTI, pkObject)

#define VeStaticCast(classname, pkObject) ((classname*)pkObject)

#ifdef VE_DEBUG

#	define VeVerifyStaticCast(classname, pkObject) \
		((classname*)classname::VerifyStaticCastDebug(&classname::ms_RTTI, pkObject))

#else

#	define VeVerifyStaticCast(classname, pkObject) ((classname*)(pkObject))

#endif

#define VeDynamicCast(classname, pkObject) \
	((classname*)classname::DynamicCast(&classname::ms_RTTI, pkObject))
