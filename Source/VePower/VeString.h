////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeString.h
//  Version:     v1.00
//  Created:     10/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <wchar.h>
#include <stdlib.h>
#include "VeVector.h"

#define VE_MAX_FORMAT_SIZE (4096)

#define VeStrlen strlen
#define VeStrcmp strcmp
#define VeStrncmp strncmp
#define VeStrpbrk strpbrk
#define VeStrchr strchr
#define VeStrstr strstr
#define VeStrrchr strrchr
#define VeWcslen wcslen
#define VeWcscmp wcscmp
#define VeWcspbrk wcspbrk
#define VeWcschr wcschr
#define VeWcsstr wcsstr
#define VeWcsrchr wcsrchr

VE_POWER_API void VeStrToLower(VeChar8* pcDst, VeSizeT stDstSize, const VeChar8* pcSrc);

VE_POWER_API void VeStrToSupper(VeChar8* pcDst, VeSizeT stDstSize, const VeChar8* pcSrc);

#define VeIsAlpha isalpha
#define VeIsSpace isspace
#define VeIsAlnum isalnum
#define VeToLower tolower
#define VeToSupper toupper

#define VE_STR(str) #str

#define VeAtof atof
#define VeAtoi atoi
#define VeWtof(s) wcstod(s,NULL)
#define VeWtoi(s) wcstol(s,NULL,0)

VE_POWER_API VeUInt32 VeAtoui(const VeChar8* pcStr);

VE_POWER_API VeInt32 VeStricmp(const VeChar8* dst, const VeChar8* src);

VE_POWER_API VeInt32 VeStrnicmp(const VeChar8* dst, const VeChar8* src, VeInt32 count);

VE_POWER_API VeChar8* VeStrcpy(VeChar8* pcDest, VeSizeT stDestSize, const VeChar8* pcSrc);

VE_POWER_API VeChar8* VeStrncpy(VeChar8* pcDest, VeSizeT stDestSize, const VeChar8* pcSrc, VeSizeT stCount);

VE_POWER_API VeChar8* VeStrcat(VeChar8* pcDest, VeSizeT stDestSize, const VeChar8* pcSrc);

VE_POWER_API VeChar8* VeStrtok(VeChar8* pcString, const VeChar8* pcDelimit, VeChar8** ppcContext);

VE_POWER_API VeChar8* VeStrline(VeChar8* pcString, VeChar8** ppcContext);

VE_POWER_API VeChar8* VeStrBetween(VeChar8* pcString, const VeChar8* pcBefore, const VeChar8* pcAfter);

VE_POWER_API VeChar8* VeStrContent(VeChar8* pcString);

VE_POWER_API VeInt32 VeSprintf(VeChar8* pcDest, VeSizeT stDestSize, const VeChar8* pcFormat, ...);

VE_POWER_API VeInt32 VeVsprintf(VeChar8* pcDest, VeSizeT stDestSize, const VeChar8* pcFormat, va_list kArgs);

VE_POWER_API VeInt32 VeSnprintf(VeChar8* pcDest, VeSizeT stDestSize, VeSizeT stCount, const VeChar8* pcFormat, ...);

VE_POWER_API VeInt32 VeVsnprintf(VeChar8* pcDest, VeSizeT stDestSize, VeSizeT stCount, const VeChar8* pcFormat, va_list kArgs);

VE_POWER_API VeInt32 VeMemcpy(void* pvDest, VeSizeT stDestSize, const void* pvSrc, VeSizeT stCount);

VE_POWER_API VeInt32 VeMemcpy(void* pvDest, const void* pvSrc, VeSizeT stCount);

VE_POWER_API VeInt32 VeMemmove(void* pvDest, VeSizeT stDestSize, const void* pvSrc, VeSizeT stCount);

VE_POWER_API VeInt32 VeWStricmp(const VeChar16* dst, const VeChar16* src);

VE_POWER_API VeInt32 VeWStrnicmp(const VeChar16* dst, const VeChar16* src, VeInt32 count);

VE_POWER_API VeChar16* VeWStrcpy(VeChar16* pkDest, VeSizeT stDestSize, const VeChar16* pkSrc);

VE_POWER_API VeChar16* VeWStrncpy(VeChar16* pkDest, VeSizeT stDestSize, const VeChar16* pkSrc, VeSizeT stCount);

VE_POWER_API VeChar16* VeWStrcat(VeChar16* pkDest, VeSizeT stDestSize, const VeChar16* pkSrc);

VE_POWER_API VeChar16* VeWStrtok(VeChar16* pkString, const VeChar16* pkDelimit, VeChar16** ppkContext);

VE_POWER_API VeInt32 VeWSprintf(VeChar16* pkDest, VeSizeT stDestSize, const VeChar16* pkFormat, ...);

VE_POWER_API VeInt32 VeUTF8ToUnicode(const VeChar8* pcUTF8, VeInt32& i32Unicode);

template<VeInt32 size>
VeChar8* VeStrcpy(VeChar8(&pcDest)[size], const VeChar8* pcSrc)
{
	return VeStrcpy(pcDest, size, pcSrc);
}

template<VeInt32 size>
VeInt32 VeSprintf(VeChar8(&pcDest)[size], const VeChar8* pcFormat, ...)
{
	VE_ASSERT(pcFormat);
	va_list kArgs;
	va_start(kArgs, pcFormat);
	int iRet = VeVsprintf(pcDest, size, pcFormat, kArgs);
	va_end(kArgs);
	return iRet;
}

#ifdef VE_UNICODE
#	define VeTStricmp		VeWStricmp
#	define VeTStrnicmp		VeWStrnicmp
#	define VeTStrcpy		VeWStrcpy
#	define VeTStrncpy		VeWStrncpy
#	define VeTStrcat		VeWStrcat
#	define VeTStrtok		VeWStrtok
#	define VeTSprintf		VeWSprintf
#else
#	define VeTStricmp		VeStricmp
#	define VeTStrnicmp		VeStrnicmp
#	define VeTStrcpy		VeStrcpy
#	define VeTStrncpy		VeStrncpy
#	define VeTStrcat		VeStrcat
#	define VeTStrtok		VeStrtok
#	define VeTSprintf		VeSprintf
#endif

class VeFixedString;
class VeVector2D;
class VeVector3D;
class VeVector4D;
class VeColor;

class VE_POWER_API VeString : public VeMemObject
{
public:
	VeString(VeUInt32 u32Length = 225);

	VeString(VeChar8 c8Char, VeUInt32 u32Length = 1);

	VeString(const VeChar8* pc8Str);

	VeString(const VeChar8* pc8Str, VeUInt32 u32Length);

	VeString(const VeString& kString);

	VeString(const VeFixedString& kStr);

	~VeString();

	VeUInt32 Length() const;

	bool IsEmpty() const;

	void Empty(); 

	VeChar8 GetAt(VeUInt32 u32Index) const;

	void SetAt(VeUInt32 u32Index, VeChar8 c);

	VeInt32 Compare(const VeChar8* pc8String) const;

	VeInt32 CompareNoCase(const VeChar8* pc8String) const;

	bool Equals(const VeChar8* pc8Str) const;

	bool EqualsNoCase(const VeChar8* pc8Str) const;

	VeString GetSubstring(VeUInt32 u32Begin, VeUInt32 u32End) const;

	VeString GetSubstring(VeUInt32 u32Begin, const VeChar8* pc8Delimeters) const;

	VeUInt32 Find(VeChar8 c, VeUInt32 u32Start = 0) const;

	VeUInt32 Find(const VeChar8* pc8Str, VeUInt32 u32Start = 0) const;

	bool Contains(const VeChar8* pc8Str) const;

	bool ContainsNoCase(const VeChar8* pc8Str) const;

	VeUInt32 FindReverse(VeChar8 c) const;

	VeUInt32 FindReverse(VeChar8 c, VeUInt32 u32StartIdx) const;

	VeUInt32 FindOneOf(const VeChar8* pc8Str, VeUInt32 u32Start = 0) const;

	VeString Mid(VeUInt32 u32Begin, VeUInt32 u32Count = VE_INFINITE) const;

	VeString Left(VeUInt32 u32Count) const;

	VeString Right(VeUInt32 u32Count) const;

	void Replace(const VeChar8* pcWhatToReplace , const VeChar8* pcReplaceWith);

	void Insert(const VeChar8* pcInsertString, VeUInt32 u32Index);

	void RemoveRange(VeUInt32 u32StartIdx, VeUInt32 u32NumChars);

	void Format(const VeChar8* pcFormatString ...);

	void ToUpper();

	void ToLower();

	void Reverse();

	void TrimLeft(VeChar8 c = ' ');

	void TrimRight(VeChar8 c = ' ');

	void Concatenate(const VeChar8* pcStr);

	void Concatenate(VeChar8 ch);

	bool ToBool(bool& b) const;

	bool To(bool& b) const;

	bool ToFloat(VeFloat32& f) const;

	bool To(VeFloat32& f) const;

	bool ToInt(VeInt32& i) const;

	bool To(VeInt32& i) const;
	
	bool To(VeInt16& i) const;
	
	bool To(VeInt8& i) const;

	bool ToUInt(VeUInt32& ui) const;

	bool To(VeUInt32& ui) const;
	
	bool To(VeUInt16& ui) const;
	
	bool To(VeUInt8& ui) const;

	bool ToVector2D(VeVector2D& kVec) const;

	bool To(VeVector2D& kVec) const;

	bool ToVector3D(VeVector3D& kVec) const;
	
	bool To(VeVector3D& kVec) const;

	bool ToVector4D(VeVector4D& kVec) const;

	bool To(VeVector4D& kVec) const;

	bool ToRGBA(VeColor& kColor) const;

	bool To(VeColor& kColor) const;

	bool ToBoundingBox2D(VeBoundingBox2D& kBox) const;

	bool To(VeBoundingBox2D& kBox) const;

	static VeString FromBool(bool b);

	static VeString From(bool b);

	static VeString FromFloat(VeFloat32 f);

	static VeString From(VeFloat32 f);

	static VeString FromInt(VeInt32 i);

	static VeString From(VeInt32 i);

	static VeString From(VeInt16 i);

	static VeString From(VeInt8 i);

	static VeString FromUInt(VeUInt32 ui);

	static VeString From(VeUInt32 ui);

	static VeString From(VeUInt16 ui);

	static VeString From(VeUInt8 ui);

	static VeString FromVector2D(VeVector2D& kPt);

	static VeString From(VeVector2D& kPt);

	static VeString FromVector3D(VeVector3D& kPt);

	static VeString From(VeVector3D& kPt);

	static VeString FromVector4D(VeVector4D& kPt);

	static VeString From(VeVector4D& kPt);

	static VeString FromRGBA(VeColor& kColor);

	static VeString From(VeColor& kColor);

	static VeUInt32 CalculateHash(const VeChar8* pcString);

	static VeUInt32 KeyToHashCode(const VeChar8* pcString, VeUInt32 u32TableSize);

	VeUInt32 GetHashCode() const;

	operator const VeChar8* () const;

	VeChar8* GetString();

	VeString& operator = (VeString& stringSrc);

	VeString& operator = (const VeChar8* psz);

	VeString& operator = (const VeFixedString& kString);

	VeString& operator = (VeChar8 ch);

	VeString& operator += (VeString& string);

	VeString& operator += (VeChar8 ch);

	VeString& operator += (const VeChar8* pcString);

	VeString& operator += (const VeFixedString& kString);

	friend VeString VE_POWER_API operator + (const VeString& string1, const VeString& string2);

	friend VeString VE_POWER_API operator + (const VeString& string, VeChar8 ch);

	friend VeString VE_POWER_API operator + (VeChar8 ch, const VeString& string);

	friend VeString VE_POWER_API operator + (const VeString& string, const VeChar8* lpsz);

	friend VeString VE_POWER_API operator + (const VeString& string, const VeFixedString& kString2);

	friend VeString VE_POWER_API operator + (const VeChar8* lpsz, const VeString& string);

	friend VeString VE_POWER_API operator + (const VeFixedString& kString, const VeString& string);

	friend bool VE_POWER_API operator == (const VeString& s1, const VeString& s2);

	friend bool VE_POWER_API operator == (const VeString& s1, const VeChar8* s2);

	friend bool VE_POWER_API operator == (const VeString& s1, const VeFixedString& s2);

	friend bool VE_POWER_API operator == (const VeChar8* s1, const VeString& s2);

	friend bool VE_POWER_API operator == (const VeFixedString& s1, const VeString& s2);

	friend bool VE_POWER_API operator != (const VeString& s1, const VeString& s2);

	friend bool VE_POWER_API operator != (const VeString& s1, const VeChar8* s2);

	friend bool VE_POWER_API operator != (const VeString& s1, const VeFixedString& s2);

	friend bool VE_POWER_API operator != (const VeChar8* s1, const VeString& s2);

	friend bool VE_POWER_API operator != (const VeFixedString& s1, const VeString& s2);

	friend bool VE_POWER_API operator < (const VeString& s1, const VeString& s2);

	friend bool VE_POWER_API operator < (const VeString& s1, const VeChar8* s2);

	friend bool VE_POWER_API operator < (const VeString& s1, const VeFixedString& s2);

	friend bool VE_POWER_API operator < (const VeChar8* s1, const VeString& s2);

	friend bool VE_POWER_API operator < (const VeFixedString& s1, const VeString& s2);

	friend bool VE_POWER_API operator > (const VeString& s1, const VeString& s2);

	friend bool VE_POWER_API operator > (const VeString& s1, const VeChar8* s2);

	friend bool VE_POWER_API operator > (const VeString& s1, const VeFixedString& s2);

	friend bool VE_POWER_API operator > (const VeChar8* s1, const VeString& s2);

	friend bool VE_POWER_API operator > (const VeFixedString& s1, const VeString& s2);

	friend bool VE_POWER_API operator <= (const VeString& s1, const VeString& s2);

	friend bool VE_POWER_API operator <= (const VeString& s1, const VeChar8* s2);

	friend bool VE_POWER_API operator <= (const VeString& s1, const VeFixedString& s2);

	friend bool VE_POWER_API operator <= (const VeChar8* s1, const VeString& s2);

	friend bool VE_POWER_API operator <= (const VeFixedString& s1, const VeString& s2);

	friend bool VE_POWER_API operator >= (const VeString& s1, const VeString& s2);

	friend bool VE_POWER_API operator >= (const VeString& s1, const VeChar8* s2);

	friend bool VE_POWER_API operator >= (const VeString& s1, const VeFixedString& s2);
	
	friend bool VE_POWER_API operator >= (const VeChar8* s1, const VeString& s2);

	friend bool VE_POWER_API operator >= (const VeFixedString& s1, const VeString& s2);

	friend bool VE_POWER_API IsTrue(VeString strStr);

	VeChar8* MakeExternalCopy();

protected:
	typedef VeChar8* StringHandle;
	StringHandle m_hHandle;

	static StringHandle Allocate(VeUInt32 u32StrLength);

	static StringHandle AllocateAndCopy(const VeChar8* pcString);

	static StringHandle AllocateAndCopyHandle(StringHandle hHandle);

	static void Deallocate(StringHandle& hHandle);

	static void IncRefCount(StringHandle& hHandle);

    static void DecRefCount(StringHandle& hHandle);

    static void Swap(StringHandle& hHandle, const VeChar8* pcNewValue);
    
	static VeChar8* GetString(const StringHandle& hHandle);

	static VeUInt32 GetLength(const StringHandle& hHandle);
	
	static VeUInt32 GetRefCount(const StringHandle& hHandle);

    static VeUInt32 GetAllocationSize(const StringHandle& hHandle);
    
	static VeUInt32 GetBufferSize(const StringHandle& hHandle);

	static void SetLength(const StringHandle& hHandle, VeUInt32 u32Length);

	static VeChar8* GetRealBufferStart(const StringHandle& hHandle);

	static bool ValidateString(const StringHandle& hHandle);

	static VeUInt32 GetBestBufferSize(VeUInt32 u32ReqSize);

	bool Resize(VeUInt32 u32Delta);

	void SetBuffer(StringHandle& hHandle);

	void CalcLength();

	void CopyOnWrite(bool bForceCopy = false);

	void CopyOnWriteAndResize(VeUInt32 u32SizeDelta, bool bForceCopy = false);

	VeChar8* ConsumeWhitespace(const VeChar8* pcStr, VeUInt32 u32Length) const;

	void Format(const VeChar8* pcFmt, va_list argPtr);

};

class VE_POWER_API VeFixedString : public VeMemObject
{
public:
	typedef VeChar8* StringHandle;

	VeFixedString();
	
	VeFixedString(const VeChar8* pcString);

	VeFixedString(const VeFixedString& kString);
	
	~VeFixedString();

	operator const VeChar8* () const;

	bool Exists() const;

	VeFixedString& operator = (const VeFixedString& kString);

	VeFixedString& operator = (const VeChar8* pcString);

	VeUInt32 GetLength() const;

	VeUInt32 GetRefCount() const;

	bool Equals(const VeChar8* pcStr) const;

	bool EqualsNoCase(const VeChar8* pcStr) const;

	bool Contains(const VeChar8* pcStr) const;

	bool ContainsNoCase(const VeChar8* pcStr) const;

	bool operator == (const VeFixedString& s) const;

	bool operator != (const VeFixedString& s) const;

	bool operator == (const VeChar8* s) const;

	bool operator != (const VeChar8* s) const;

	friend VE_POWER_API bool operator == (const VeChar8* s1, const VeFixedString& s2);

	friend VE_POWER_API bool operator != (const VeChar8* s1, const VeFixedString& s2);

protected:
	StringHandle m_kHandle;

};

#define VE_NUM_GLOBAL_STRING_HASH_BUCKETS 512
#define VE_NUM_ENTRIES_PER_BUCKET_RESERVE 16

class VE_POWER_API VeGlobalStringTable : public VeSingleton<VeGlobalStringTable>
{
public:
	enum
	{
		GSTABLE_LEN_MASK        = 0x0000FFFF,
		GSTABLE_LEN_SHIFT       = 0,
		GSTABLE_HASH_MASK       = 0xFFFF0000,
		GSTABLE_HASH_SHIFT      = 16
	};

	typedef VeChar8* StringHandle;

	VeGlobalStringTable();

	~VeGlobalStringTable();

	const StringHandle AddString(const VeChar8* pcString);

	VeUInt32 GetNumString();

	VeUInt32 GetBucketSize(VeUInt32 uiWhichBucket);

	VeUInt32 GetTotalNumberOfBuckets();

	VeUInt32 GetMaxBucketSize();

protected:
	friend class VeFixedString;

	const StringHandle FindString(const VeChar8* pcString, VeUInt32 u32Len, VeUInt32 u32Hash);

	void InsertString(const StringHandle& kHandle, VeUInt32 u32Hash);

	void RemoveString(const StringHandle& kHandle, VeUInt32 u32Hash);

	static VeChar8* GetRealBufferStart(const StringHandle& kHandle);

	static VeUInt32 HashFunction(const VeChar8* pcKey, VeUInt32 u32Len);

	static void IncRefCount(StringHandle& kHandle);

	static void DecRefCount(StringHandle& kHandle);

	static const VeChar8* GetString(const StringHandle& kHandle);

	static VeUInt32 GetLength(const StringHandle& kHandle);

	static VeUInt32 GetHashValue(const StringHandle& kHandle);

	static VeUInt32 GetRefCount(const StringHandle& kHandle);

	static bool ValidateString(const StringHandle& kHandle);

	VeUInt32 m_u32NumStrings;
	VeVector<StringHandle> m_kHashArray[VE_NUM_GLOBAL_STRING_HASH_BUCKETS];
	VeThread::Mutex m_kMutex;

};

#define g_pStringTable VeGlobalStringTable::GetSingletonPtr()
