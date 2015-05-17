////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeString.cpp
//  Version:     v1.00
//  Created:     10/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
VeUInt32 VeAtoui(const VeChar8* pcStr)
{
	VeUInt32 u32Res(0);
	if(pcStr)
	{
		VeChar8 acBuffer[32];
		VeStrToLower(acBuffer, 32, pcStr);
		VeUInt32 u32Len = (VeUInt32)VeStrlen(pcStr);
		if(u32Len > 2 && pcStr[0] == '0' && pcStr[1] == 'x')
		{
			VeUInt32 u32End(2);
			for(; u32End < u32Len; ++u32End)
			{
				if(pcStr[u32End] >= '0' && pcStr[u32End] <= '9')
				{
					continue;
				}
				else if(pcStr[u32End] >= 'a' && pcStr[u32End] <= 'f')
				{
					continue;
				}
				else
				{
					break;
				}
			}
			for(VeUInt32 i(0); i < (u32End - 2); ++i)
			{
				VeChar8 cVal = pcStr[u32End - 1 - i];
				if(cVal >= '0' && cVal <= '9')
				{
					u32Res |= (cVal - '0') << (i << 2);
				}
				else if(cVal >= 'a' && cVal <= 'f')
				{
					u32Res |= (cVal - 'a' + 0xa) << (i << 2);
				}
			}
		}
		else if(u32Len > 1 && pcStr[0] == '0')
		{

		}
		else
		{
			u32Res = VeAtoi(pcStr);
		}
	}
	return u32Res;
}
//--------------------------------------------------------------------------
void VeStrToLower(VeChar8* pcDst, VeSizeT stDstSize, const VeChar8* pcSrc)
{
	VeSizeT i;
	for(i = 0; i < (stDstSize - 1); ++i)
	{
		VeChar8 cChar = pcSrc[i];
		if(cChar)
		{
			pcDst[i] = (cChar >= 'A' && cChar <= 'Z') ? cChar + 0x20 : cChar;
		}
		else
		{
			break;
		}
	}
	pcDst[i] = 0;
}
//--------------------------------------------------------------------------
void VeStrToSupper(VeChar8* pcDst, VeSizeT stDstSize, const VeChar8* pcSrc)
{
	VeSizeT i;
	for(i = 0; i < (stDstSize - 1); ++i)
	{
		VeChar8 cChar = pcSrc[i];
		if(cChar)
		{
			pcDst[i] = (cChar >= 'a' && cChar <= 'z') ? cChar - 0x20 : cChar;
		}
		else
		{
			break;
		}
	}
	pcDst[i] = 0;
}
//--------------------------------------------------------------------------
VeInt32 VeStricmp(const VeChar8* dst, const VeChar8* src)
{
	VE_ASSERT(dst && src);
	VeInt32 f,l;
	do
	{
		if(((f = (VeUInt8)(*(dst++))) >= 'A') && (f <= 'Z') )
			f -= ('A' - 'a');

		if(((l = (VeUInt8)(*(src++))) >= 'A') && (l <= 'Z'))
			l -= ('A' - 'a');
	}
	while(f && (f == l));
	return(f - l);
}
//--------------------------------------------------------------------------
VeInt32 VeStrnicmp(const VeChar8* dst, const VeChar8* src, VeInt32 count)
{
	VE_ASSERT(dst && src);
	VeInt32 f,l;
	if(count)
	{
		do
		{
			if(((f = (VeUInt8)(*(dst++))) >= 'A') && (f <= 'Z'))
				f -= 'A' - 'a';

			if(((l = (VeUInt8)(*(src++))) >= 'A') && (l <= 'Z'))
				l -= 'A' - 'a';
		}
		while(--count && f && (f == l));

		return(f - l);
	}

	return(0);
}
//--------------------------------------------------------------------------
VeChar8* VeStrcpy(VeChar8* pcDest, VeSizeT stDestSize, const VeChar8* pcSrc)
{
#if _MSC_VER >= 1400

	strcpy_s(pcDest, stDestSize, pcSrc);
	return pcDest;

#else // #if _MSC_VER >= 1400

	VE_ASSERT(stDestSize != 0);
	VeSizeT stSrcLen = VeStrlen(pcSrc);
	VE_ASSERT(stDestSize > stSrcLen);
	VeSizeT stWrite;
	if (stDestSize <= stSrcLen) // stDestSize < stSrcLen + 1
		stWrite = stDestSize;
	else 
		stWrite = stSrcLen + 1;
	VeChar8 *pcResult = strncpy(pcDest, pcSrc, stWrite);
	pcResult[stDestSize - 1] = 0;
	return pcResult;

#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeChar8* VeStrncpy(VeChar8* pcDest, VeSizeT stDestSize,
	const VeChar8* pcSrc, VeSizeT stCount)
{
#if _MSC_VER >= 1400

	strncpy_s(pcDest, stDestSize, pcSrc, stCount);
	return pcDest;

#else // #if _MSC_VER >= 1400

	VE_ASSERT(pcDest != 0 && stDestSize != 0);
	VE_ASSERT(stCount < stDestSize || stCount == VE_SIZET_MAX);

	if (stCount >= stDestSize)
	{
		if (stCount != VE_SIZET_MAX)
		{
			pcDest[0] = 0;
			return pcDest;
		}
		else
		{
			stCount = stDestSize - 1;
		}
	}

	VeChar8* pcResult = strncpy(pcDest, pcSrc, stCount);
	pcResult[stCount] = 0;

	return pcResult;

#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeChar8* VeStrcat(VeChar8* pcDest, VeSizeT stDestSize, const VeChar8* pcSrc)
{
#if _MSC_VER >= 1400

	strcat_s(pcDest, stDestSize, pcSrc);
	return pcDest;

#else // #if _MSC_VER >= 1400

#ifdef VE_DEBUG
	VeSizeT stSrcLen = VeStrlen(pcSrc);
#endif
	VeSizeT stDestLen = VeStrlen(pcDest);
	VE_ASSERT(stSrcLen + stDestLen <= stDestSize - 1);
	VeSizeT stWrite = stDestSize - 1 - stDestLen;
	VeChar8* pcResult = strncat(pcDest, pcSrc, stWrite);
	pcResult[stDestSize - 1] = 0;
	return pcResult;

#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeChar8* VeStrtok(VeChar8* pcString, const VeChar8* pcDelimit,
	VeChar8** ppcContext)
{
	VeChar8* pcStrStart = pcString;
	if((!pcStrStart) && ppcContext)
	{
		pcStrStart = *ppcContext;
	}
	if(pcStrStart)
	{
		VeSizeT stLen = VeStrlen(pcDelimit);
		VeChar8* pcTemp = VeStrstr(pcStrStart, pcDelimit);
		if(pcTemp)
		{
			*pcTemp = '\0';
			if(ppcContext) *ppcContext = pcTemp += stLen;
			return pcStrStart;
		}
		else if(*pcStrStart)
		{
			if(ppcContext) *ppcContext = NULL;
			return pcStrStart;
		}
		else
		{
			if(ppcContext) *ppcContext = NULL;
			return NULL;
		}
	}
	return NULL;

//#if _MSC_VER >= 1400
//
//	return strtok_s(pcString, pcDelimit, ppcContext);
//
//#else // #if _MSC_VER >= 1400
//
//	VeChar8* pcContext = strtok(pcString, pcDelimit);
//	if(ppcContext)
//	{
//		if(pcContext && (*pcContext))
//		{
//			*ppcContext = pcContext + VeStrlen(pcContext) + 1;
//		}
//		else
//		{
//			*ppcContext = NULL;
//		}
//	}
//	return pcContext;
//
//#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeChar8* VeStrline(VeChar8* pcString, VeChar8** ppcContext)
{
	VE_ASSERT(ppcContext);
	if(!pcString) pcString = *ppcContext;
	VeChar8* pcRes = pcString;
	*ppcContext = NULL;
	if(pcString)
	{
		while(*pcString)
		{
			if(*pcString != '\r' && *pcString != '\n')
			{
				++pcString;
			}
			else
			{
				*pcString = '\0';
				do 
				{
					++pcString;
				}
				while (*pcString == '\r' || *pcString == '\n');
				if(*pcString)
				{
					*ppcContext = pcString;
					break;
				}
			}
		}
	}
	return pcRes;
}
//--------------------------------------------------------------------------
VeChar8* VeStrBetween(VeChar8* pcString, const VeChar8* pcBefore,
	const VeChar8* pcAfter)
{
	VeChar8* pcTemp = VeStrstr(pcString, pcBefore);
	if(!pcBefore) return NULL;
	pcString = pcTemp + VeStrlen(pcBefore);
	pcTemp = VeStrstr(pcString, pcAfter);
	if(!pcTemp) return NULL;
	*pcTemp = '\0';
	return pcString;
}
//--------------------------------------------------------------------------
VeChar8* VeStrContent(VeChar8* pcString)
{
	while((*pcString) > 0 && (*pcString) < 0x21) ++pcString;
	VeChar8* pcEnd = pcString + VeStrlen(pcString);
	while(*(--pcEnd) < 0x21) *pcEnd = '\0';
	return pcString;
}
//--------------------------------------------------------------------------
VeInt32 VeSprintf(VeChar8* pcDest, VeSizeT stDestSize,
	const VeChar8* pcFormat, ...)
{
	VE_ASSERT(pcFormat);

	va_list kArgs;
	va_start(kArgs, pcFormat);
	int iRet = VeVsprintf(pcDest, stDestSize, pcFormat, kArgs);
	va_end(kArgs);

	return iRet;
}
//--------------------------------------------------------------------------
VeInt32 VeVsprintf(VeChar8* pcDest, VeSizeT stDestSize,
	const VeChar8* pcFormat, va_list kArgs)
{
	return VeVsnprintf(pcDest, stDestSize, VE_SIZET_MAX, pcFormat, kArgs);
}
//--------------------------------------------------------------------------
VeInt32 VeSnprintf(VeChar8* pcDest, VeSizeT stDestSize, VeSizeT stCount,
	const VeChar8* pcFormat, ...)
{
	VE_ASSERT(pcFormat);

	va_list kArgs;
	va_start(kArgs, pcFormat);
	VeInt32 iRet = VeVsnprintf(pcDest, stDestSize, stCount, pcFormat, kArgs);
	va_end(kArgs);

	return iRet;
}
//--------------------------------------------------------------------------
VeInt32 VeVsnprintf(VeChar8* pcDest, VeSizeT stDestSize, VeSizeT stCount,
	const VeChar8* pcFormat, va_list kArgs)
{
	if (stDestSize == 0)
	{
		return 0;
	}

	VE_ASSERT(pcDest);
	VE_ASSERT(stCount < stDestSize || stCount == VE_SIZET_MAX);
	VE_ASSERT(pcFormat);

	pcDest[0] = 0;

	bool bTruncate = (stCount == VE_SIZET_MAX);

#if _MSC_VER >= 1400
	int iRet = vsnprintf_s(pcDest, stDestSize, stCount, pcFormat, kArgs);
#else
	if (bTruncate)
	{
		stCount = stDestSize - 1;
	}
	int iRet = vsnprintf(pcDest, stCount, pcFormat, kArgs);
#endif

	if (iRet == -1 && !bTruncate)
	{
		iRet = (int)stCount;
	}

#if _MSC_VER >= 1400

#else
	if (iRet == -1)
	{
		pcDest[stDestSize - 1] = 0;
	}
	else
	{
		pcDest[iRet] = 0;
	}
#endif

	return iRet;
}
//--------------------------------------------------------------------------
VeInt32 VeMemcpy(void* pvDest, VeSizeT stDestSize, const void* pvSrc,
	VeSizeT stCount)
{
	VeInt32 iRet = 0;

#if _MSC_VER >= 1400
	iRet = memcpy_s(pvDest, stDestSize, pvSrc, stCount);
#else // #if _MSC_VER >= 1400
	if (stDestSize < stCount)
		iRet = -1;
	else
		memcpy(pvDest, pvSrc, stCount);
#endif // #if _MSC_VER >= 1400

	VE_ASSERT(iRet != -1);
	return iRet;
}
//--------------------------------------------------------------------------
VeInt32 VeMemcpy(void* pvDest, const void* pvSrc, VeSizeT stCount)
{
	return VeMemcpy(pvDest, stCount, pvSrc, stCount);
}
//--------------------------------------------------------------------------
VeInt32 VeMemmove(void* pvDest, VeSizeT stDestSize, const void* pvSrc,
	VeSizeT stCount)
{
	VeInt32 iRet = 0;

#if _MSC_VER >= 1400
	iRet = memmove_s(pvDest, stDestSize, pvSrc, stCount);
#else // #if _MSC_VER >= 1400
	if (stDestSize < stCount)
		iRet = -1;
	else
		memmove(pvDest, pvSrc, stCount);
#endif // #if _MSC_VER >= 1400

	VE_ASSERT(iRet != -1);
	return iRet;
}
//--------------------------------------------------------------------------
VeInt32 VeWStricmp(const VeChar16* dst, const VeChar16* src)
{
	VE_ASSERT(dst && src);
	VeInt32 f,l;
	do
	{
		if(((f = (VeUInt16)(*(dst++))) >= 'A') && (f <= 'Z') )
			f -= ('A' - 'a');

		if(((l = (VeUInt16)(*(src++))) >= 'A') && (l <= 'Z'))
			l -= ('A' - 'a');
	}
	while(f && (f == l));
	return(f - l);
}
//--------------------------------------------------------------------------
VeInt32 VeWStrnicmp(const VeChar16* dst, const VeChar16* src, VeInt32 count)
{
	VE_ASSERT(dst && src);
	VeInt32 f,l;
	if(count)
	{
		do
		{
			if(((f = (VeUInt16)(*(dst++))) >= 'A') && (f <= 'Z'))
				f -= 'A' - 'a';

			if(((l = (VeUInt16)(*(src++))) >= 'A') && (l <= 'Z'))
				l -= 'A' - 'a';
		}
		while(--count && f && (f == l));

		return(f - l);
	}

	return(0);
}
//--------------------------------------------------------------------------
VeChar16* VeWStrcpy(VeChar16* pkDest, VeSizeT stDestSize,
	const VeChar16* pkSrc)
{
#if _MSC_VER >= 1400
	wcscpy_s((wchar_t *)pkDest, stDestSize, (const wchar_t *)pkSrc);
	return pkDest;
#else // #if _MSC_VER >= 1400
	VE_ASSERT(stDestSize != 0);

	VeSizeT stSrcLen = wcslen(pkSrc);
	VE_ASSERT(stDestSize > stSrcLen); // > because need null character

	VeSizeT stWrite;

	if (stDestSize <= stSrcLen) // stDestSize < stSrcLen + 1
		stWrite = stDestSize;
	else 
		stWrite = stSrcLen + 1;

	VeChar16* pkResult = wcsncpy(pkDest, pkSrc, stWrite);
	pkResult[stDestSize - 1] = 0;
	return pkResult;
#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeChar16* VeWStrncpy(VeChar16* pkDest, VeSizeT stDestSize,
	const VeChar16* pkSrc, VeSizeT stCount)
{
#if _MSC_VER >= 1400
	wcsncpy_s((wchar_t *)pkDest, stDestSize, (const wchar_t *)pkSrc, stCount);
	return pkDest;
#else // #if _MSC_VER >= 1400
	VE_ASSERT(pkDest != 0 && stDestSize != 0);
	VE_ASSERT(stCount < stDestSize || stCount == VE_SIZET_MAX);

	if (stCount >= stDestSize)
	{
		if (stCount != VE_SIZET_MAX)
		{
			pkDest[0] = 0;
			return pkDest;
		}
		else
		{
			stCount = stDestSize - 1;
		}
	}

	VeChar16* pkResult = wcsncpy(pkDest, pkSrc, stCount);
	pkResult[stCount] = 0;

	return pkResult;
#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeChar16* VeWStrcat(VeChar16* pkDest, VeSizeT stDestSize,
	const VeChar16* pkSrc)
{
#if _MSC_VER >= 1400
	wcscat_s((wchar_t *)pkDest, stDestSize, (const wchar_t *)pkSrc);
	return pkDest;
#else // #if _MSC_VER >= 1400
#ifdef VE_DEBUG
	VeSizeT stSrcLen = wcslen(pkSrc);
#endif
	VeSizeT stDestLen = wcslen(pkDest);
	VE_ASSERT(stSrcLen + stDestLen <= stDestSize - 1);

	VeSizeT stWrite = stDestSize - 1 - stDestLen;  

	VeChar16* pkResult = wcsncat(pkDest, pkSrc, stWrite);
	pkResult[stDestSize - 1] = 0;
	return pkResult;

#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeChar16* VeWStrtok(VeChar16* pkString, const VeChar16* pkDelimit,
	VeChar16** ppkContext)
{
#if _MSC_VER >= 1400
	return (VeChar16 *)wcstok_s((VeChar16 *)pkString,
		(const VeChar16 *)pkDelimit, (VeChar16 **)ppkContext);
#else // #if _MSC_VER >= 1400
	return wcstok(pkString, pkDelimit, ppkContext);
#endif // #if _MSC_VER >= 1400
}
//--------------------------------------------------------------------------
VeInt32 VeWSprintf(VeChar16* pkDest, VeSizeT stDestSize,
	const VeChar16* pkFormat, ...)
{
	if (stDestSize == 0)
		return 0;

	va_list kArgs;
	va_start(kArgs, pkFormat);

#if _MSC_VER >= 1400
	VeInt32 iRet = vswprintf_s((VeChar16 *)pkDest, stDestSize,
		(const VeChar16 *)pkFormat, kArgs);
#else // #if _MSC_VER >= 1400
	VeInt32 iRet = vswprintf(pkDest, stDestSize, pkFormat, kArgs);

	if (iRet >= 0 && ((VeUInt32)iRet == stDestSize - 1) &&
		pkDest[stDestSize - 1] != 0)
	{
		iRet = -1;
	}
#endif // #if _MSC_VER >= 1400

	va_end(kArgs);
	pkDest[stDestSize - 1] = 0;

	return iRet;
}
//--------------------------------------------------------------------------
VeInt32 VeUTF8ToUnicode(const VeChar8* pcUTF8, VeInt32& i32Unicode)
{
	VeInt32 i32Res(0);
	if(*pcUTF8)
	{
		if(VeUInt8(*pcUTF8) >= 0xfc)
		{
			i32Unicode = (pcUTF8[0] & 0x01) << 30;
			i32Unicode |= (pcUTF8[1] & 0x3f) << 24;
			i32Unicode |= (pcUTF8[2] & 0x3f) << 18;
			i32Unicode |= (pcUTF8[3] & 0x3f) << 12;
			i32Unicode |= (pcUTF8[4] & 0x3f) << 6;
			i32Unicode |= (pcUTF8[5] & 0x3f);  
			i32Res = 6;
		}
		else if(VeUInt8(*pcUTF8) >= 0xf8)
		{
			i32Unicode = (pcUTF8[0] & 0x03) << 24;
			i32Unicode |= (pcUTF8[1] & 0x3f) << 18;
			i32Unicode |= (pcUTF8[2] & 0x3f) << 12;
			i32Unicode |= (pcUTF8[3] & 0x3f) << 6;
			i32Unicode |= (pcUTF8[4] & 0x3f);
			i32Res = 5;
		}
		else if(VeUInt8(*pcUTF8) >= 0xf0)
		{
			i32Unicode = (pcUTF8[0] & 0x07) << 18;
			i32Unicode |= (pcUTF8[1] & 0x3f) << 12;
			i32Unicode |= (pcUTF8[2] & 0x3f) << 6;
			i32Unicode |= (pcUTF8[3] & 0x3f);
			i32Res = 4;
		}
		else if(VeUInt8(*pcUTF8) >= 0xe0)
		{
			i32Unicode = (pcUTF8[0] & 0x0f) << 12;
			i32Unicode |= (pcUTF8[1] & 0x3f) << 6;
			i32Unicode |= (pcUTF8[2] & 0x3f);
			i32Res = 3;
		}
		else if(VeUInt8(*pcUTF8) >= 0xc0)
		{
			i32Unicode = (pcUTF8[0] & 0x1f) << 6;
			i32Unicode |= (pcUTF8[1] & 0x3f);
			i32Res = 2;
		}
		else
		{
			i32Unicode = pcUTF8[0];
			i32Res = 1;
		}
	}
	return i32Res;
}
//--------------------------------------------------------------------------
#define VE_BUFFER_SIZE_IDX		0
#define VE_REF_COUNT_IDX		1
#define VE_STRING_LENGTH_IDX	2
#define VE_HEADER_OFFSET		(3*sizeof(VeUInt32))
//--------------------------------------------------------------------------
VeString::StringHandle VeString::Allocate(VeUInt32 u32StrLength)
{
	if(u32StrLength == 0) u32StrLength = 1;

	VeUInt32 u32BufferSize = u32StrLength * sizeof(VeChar8)
		+ VE_HEADER_OFFSET + sizeof(VeChar8);
	u32BufferSize = GetBestBufferSize(u32BufferSize);

	VeChar8* pcBuffer = VeAlloc(VeChar8, u32BufferSize);
	VeUInt32* pu32Buffer = (VeUInt32*)pcBuffer;
	pu32Buffer[VE_BUFFER_SIZE_IDX] = u32BufferSize;
	pu32Buffer[VE_REF_COUNT_IDX] = 1;
	pu32Buffer[VE_STRING_LENGTH_IDX] = 0;
	return pcBuffer + VE_HEADER_OFFSET;
}
//--------------------------------------------------------------------------
VeString::StringHandle VeString::AllocateAndCopy(const VeChar8* pcString)
{
	if(pcString == NULL) return NULL;

	VeUInt32 u32Length = (VeUInt32)VeStrlen(pcString);
	StringHandle hHandle = Allocate(u32Length);
	
	if(hHandle == NULL) return NULL;

	VeCrazyCopy(hHandle, pcString, u32Length + 1);
	VE_ASSERT(VeStrcmp(hHandle, pcString) == 0);

	VeUInt32* pu32Buffer = (VeUInt32*)GetRealBufferStart(hHandle);
	pu32Buffer[VE_STRING_LENGTH_IDX] = u32Length;
	return hHandle;
}
//--------------------------------------------------------------------------
VeString::StringHandle VeString::AllocateAndCopyHandle(
	StringHandle hHandle)
{
	if(hHandle == NULL) return NULL;
	VeUInt32 u32Length = GetLength(hHandle);
	VeUInt32 u32BufferSize = GetAllocationSize(hHandle);
	VeChar8* pcBuffer = VeAlloc(VeChar8, u32BufferSize);
	VeUInt32* pu32Buffer = (VeUInt32*)pcBuffer;
	pu32Buffer[VE_BUFFER_SIZE_IDX] = u32BufferSize;
	pu32Buffer[VE_REF_COUNT_IDX] = 1;
	pu32Buffer[VE_STRING_LENGTH_IDX] = u32Length;
	StringHandle kNewHandle = pcBuffer + VE_HEADER_OFFSET;
	VeCrazyCopy(kNewHandle, hHandle, u32Length + 1);
	VE_ASSERT(VeStrcmp(kNewHandle, hHandle) == 0);
	return kNewHandle;
}
//--------------------------------------------------------------------------
void VeString::Deallocate(StringHandle& hHandle)
{
	if(hHandle)
	{
		VeChar8* pcMem = GetRealBufferStart(hHandle); 
		VeFree(pcMem);
		hHandle = NULL;
	}
}
//--------------------------------------------------------------------------
void VeString::IncRefCount(StringHandle& hHandle)
{
	if(hHandle == NULL) return;
	VE_ASSERT(ValidateString(hHandle));
	VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
	VeAtomicIncrement32(pu32Mem[VE_REF_COUNT_IDX]);
}
//--------------------------------------------------------------------------
void VeString::DecRefCount(StringHandle& hHandle)
{
	if(hHandle == NULL) return;
	VE_ASSERT(ValidateString(hHandle));
	VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
	VeAtomicDecrement32(pu32Mem[VE_REF_COUNT_IDX]);
	if(pu32Mem[VE_REF_COUNT_IDX] == 0) Deallocate(hHandle);
	hHandle = NULL;
}
//--------------------------------------------------------------------------
void VeString::Swap(StringHandle& hHandle, const VeChar8* pcNewValue)
{
	if(pcNewValue == NULL)
	{
		DecRefCount(hHandle);
		return;
	}

	if(hHandle == NULL)
	{
		hHandle = AllocateAndCopy(pcNewValue);
		return;
	}

	VE_ASSERT(ValidateString(hHandle));
	VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
	VeAtomicDecrement32(pu32Mem[VE_REF_COUNT_IDX]);

	if(pu32Mem[VE_REF_COUNT_IDX] == 0)
	{
		VeUInt32 u32Length = (VeUInt32)VeStrlen(pcNewValue);
		if(pu32Mem[VE_BUFFER_SIZE_IDX] >= (u32Length + 1 + VE_HEADER_OFFSET))
		{
			pu32Mem[VE_REF_COUNT_IDX] = 1;
		}
		else
		{
			Deallocate(hHandle);
			hHandle = Allocate(u32Length);
			pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
		}

		VeCrazyCopy(hHandle, pcNewValue, u32Length + 1);
		VE_ASSERT(VeStrcmp(hHandle, pcNewValue) == 0);

		pu32Mem[VE_STRING_LENGTH_IDX] = u32Length;
	}
	else
	{
		hHandle = AllocateAndCopy(pcNewValue);
	}
}
//--------------------------------------------------------------------------
VeChar8* VeString::GetString(const StringHandle& hHandle)
{
	VE_ASSERT(ValidateString(hHandle));
	return hHandle;
}
//--------------------------------------------------------------------------
VeUInt32 VeString::GetLength(const StringHandle& hHandle)
{
	if(hHandle == NULL)
	{
		return 0;
	}
	else
	{
		VE_ASSERT(ValidateString(hHandle));
		VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
		return pu32Mem[VE_STRING_LENGTH_IDX];
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeString::GetRefCount(const StringHandle& hHandle)
{
	if(hHandle == NULL)
	{
		return 0;
	}
	else
	{
		VE_ASSERT(ValidateString(hHandle));
		VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
		return pu32Mem[VE_REF_COUNT_IDX];
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeString::GetAllocationSize(const StringHandle& hHandle)
{
	if(hHandle == NULL)
	{
		return 0;
	}
	else
	{
		VE_ASSERT(ValidateString(hHandle));
		VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
		return pu32Mem[VE_BUFFER_SIZE_IDX];
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeString::GetBufferSize(const StringHandle& hHandle)
{
	if(hHandle == NULL)
	{
		return 0;
	}
	else
	{
		VE_ASSERT(ValidateString(hHandle));
		VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
		return pu32Mem[VE_BUFFER_SIZE_IDX] - VE_HEADER_OFFSET;
	}
}
//--------------------------------------------------------------------------
void VeString::SetLength(const StringHandle& hHandle, VeUInt32 u32Length)
{
	if(hHandle == NULL) return;
	VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
	pu32Mem[VE_STRING_LENGTH_IDX] = u32Length;
	VE_ASSERT(pu32Mem[VE_STRING_LENGTH_IDX] < pu32Mem[VE_BUFFER_SIZE_IDX]);
}
//--------------------------------------------------------------------------
VeChar8* VeString::GetRealBufferStart(const StringHandle& hHandle)
{
	VE_ASSERT(hHandle);
	return hHandle - VE_HEADER_OFFSET;
}
//--------------------------------------------------------------------------
bool VeString::ValidateString(const StringHandle& hHandle)
{
	if(hHandle == NULL) return true;
	VeUInt32* pu32Mem = (VeUInt32*)GetRealBufferStart(hHandle);
	VeUInt32 u32Length = pu32Mem[VE_STRING_LENGTH_IDX];
	if(u32Length == (VeUInt32)VeStrlen(hHandle)) return true;
	else return false;
}
//--------------------------------------------------------------------------
VeUInt32 VeString::GetBestBufferSize(VeUInt32 u32ReqSize)
{
	if (u32ReqSize < 32)
		return 32;
	else if (u32ReqSize < 64)
		return 64;
	else if (u32ReqSize < 128)
		return 128;
	else if (u32ReqSize < 256)
		return 255;
	else if (u32ReqSize < 512)
		return 512;
	else if (u32ReqSize < 1024)
		return 1024;
	else 
		return ((u32ReqSize + 0xF) >> 4) << 4;
}
//--------------------------------------------------------------------------
VeString::VeString(VeUInt32 u32Length)
{
	m_hHandle = Allocate(u32Length);
	m_hHandle[0] = 0;
	CalcLength();
}
//--------------------------------------------------------------------------
VeString::VeString(VeChar8 c8Char, VeUInt32 u32Length)
{
	m_hHandle = Allocate(u32Length);
	VeMemorySet(m_hHandle, c8Char, u32Length);
	m_hHandle[u32Length] = 0;
	CalcLength();
}
//--------------------------------------------------------------------------
VeString::VeString(const VeChar8* pc8Str)
{
	m_hHandle = AllocateAndCopy(pc8Str);
	CalcLength();
}
//--------------------------------------------------------------------------
VeString::VeString(const VeChar8* pc8Str, VeUInt32 u32Length)
{
	m_hHandle = Allocate(u32Length);
	VeCrazyCopy(m_hHandle, pc8Str, u32Length);
	m_hHandle[u32Length] = 0;
	CalcLength();
}
//--------------------------------------------------------------------------
VeString::VeString(const VeString& kString)
{
	m_hHandle = kString.m_hHandle;
	IncRefCount(m_hHandle);
}
//--------------------------------------------------------------------------
VeString::VeString(const VeFixedString& kStr)
{
	m_hHandle = AllocateAndCopy((const VeChar8*)kStr);
	CalcLength();
}
//--------------------------------------------------------------------------
VeString::~VeString()
{
	DecRefCount(m_hHandle);
}
//--------------------------------------------------------------------------
bool VeString::Resize(VeUInt32 u32Delta)
{
	VeUInt32 u32NewStringLength = Length() + u32Delta;
	if(((u32NewStringLength + 1) * sizeof(VeChar8)) >
		GetBufferSize(m_hHandle))
	{
		StringHandle kNewHandle = Allocate(u32NewStringLength);
		VeUInt32 u32EndLoc = Length();
		VeCrazyCopy(kNewHandle, m_hHandle, Length() * sizeof(VeChar8));
		kNewHandle[u32EndLoc] = 0;
		DecRefCount(m_hHandle);
		m_hHandle = kNewHandle;
		CalcLength();
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------------
void VeString::SetBuffer(StringHandle& hHandle)
{
	if(hHandle == m_hHandle) return;
	DecRefCount(m_hHandle);
	IncRefCount(hHandle);
	m_hHandle = hHandle;
}
//--------------------------------------------------------------------------
void VeString::CalcLength()
{
	if(m_hHandle == NULL) return;
	SetLength(m_hHandle, (VeUInt32)VeStrlen(m_hHandle));
}
//--------------------------------------------------------------------------
void VeString::CopyOnWrite(bool bForceCopy)
{
	if((GetRefCount(m_hHandle) > 1) || bForceCopy)
	{
		StringHandle hHandle = m_hHandle;
		m_hHandle = AllocateAndCopyHandle(m_hHandle);
		DecRefCount(hHandle);
	}
}
//--------------------------------------------------------------------------
void VeString::CopyOnWriteAndResize(VeUInt32 u32SizeDelta, bool bForceCopy)
{
	if(Resize(u32SizeDelta)) return;

	if(GetRefCount(m_hHandle) > 1 || bForceCopy)
	{
		StringHandle kHandle = m_hHandle;
		m_hHandle = AllocateAndCopyHandle(m_hHandle);
		DecRefCount(kHandle);
	}
}
//--------------------------------------------------------------------------
VeChar8* VeString::ConsumeWhitespace(const VeChar8* pcStr,
	VeUInt32 u32Length) const
{
	bool bContinue = true;
	VeUInt32 u32Idx;
	for(u32Idx = 0; u32Idx < u32Length && bContinue; u32Idx++)
	{
		if(pcStr[u32Idx] != '\t' && pcStr[u32Idx] != ' ')
			bContinue = false;
	}
	return (VeChar8*)pcStr + u32Idx - 1;
}
//--------------------------------------------------------------------------
void VeString::Format(const VeChar8* pcFmt, va_list argPtr)
{
	VeChar8 acBuffer[VE_MAX_FORMAT_SIZE];
	VeInt32 i32NumChars = VeVsprintf(acBuffer, VE_MAX_FORMAT_SIZE,
		pcFmt, argPtr);
	VE_ASSERT(i32NumChars >= 0);
	if((VeUInt32)i32NumChars >= GetBufferSize(m_hHandle))
	{
		Deallocate(m_hHandle);
		m_hHandle = Allocate(i32NumChars + 1);
	}
	VeCrazyCopy(m_hHandle, acBuffer, i32NumChars);
	m_hHandle[i32NumChars] = 0;
}
//--------------------------------------------------------------------------
void VeString::Format( const VeChar8* pcFormatString ... )
{
	CopyOnWrite(true);
	va_list argList;
	va_start(argList, pcFormatString);
	Format(pcFormatString, argList);
	va_end(argList);
}
//--------------------------------------------------------------------------
VeUInt32 VeString::Length() const
{
	return GetLength(m_hHandle);
}
//--------------------------------------------------------------------------
bool VeString::IsEmpty() const
{
	return Length() == 0;
}
//--------------------------------------------------------------------------
void VeString::Empty()
{
	DecRefCount(m_hHandle);
}
//--------------------------------------------------------------------------
VeChar8 VeString::GetAt(VeUInt32 u32Index) const
{
	VeChar8 c;
	if (u32Index >= Length())
		c = 0;
	else
		c = GetString(m_hHandle)[u32Index];
	return c;
}
//--------------------------------------------------------------------------
void VeString::SetAt(VeUInt32 u32Index, VeChar8 c)
{
	if(u32Index >= Length()) return;

	CopyOnWrite();
	GetString(m_hHandle)[u32Index] = c;
	if(c == 0)
	{
		SetLength(m_hHandle, u32Index);
	}
}
//--------------------------------------------------------------------------
VeInt32 VeString::Compare(const VeChar8* pc8String) const
{
	if(pc8String == NULL && m_hHandle == NULL)
		return 0;
	else if(pc8String == NULL)
		return GetString(m_hHandle)[0];
	else if (m_hHandle == NULL)
		return -pc8String[0];
	return VeStrcmp(GetString(m_hHandle), pc8String);
}
//--------------------------------------------------------------------------
VeInt32 VeString::CompareNoCase(const VeChar8* pc8String) const
{
	if(pc8String == NULL && m_hHandle == (StringHandle) NULL)
		return 0;
	else if (pc8String == NULL)
		return GetString(m_hHandle)[0];
	else if (m_hHandle == (StringHandle) NULL)
		return -pc8String[0];
	return VeStricmp(GetString(m_hHandle), pc8String);
}
//--------------------------------------------------------------------------
bool VeString::Equals(const VeChar8* pc8Str) const
{
	if(pc8Str == NULL)
		return m_hHandle == (StringHandle)NULL;
	else if(VeStrlen(pc8Str) != Length())
		return false;

	return Compare(pc8Str) == 0;
}
//--------------------------------------------------------------------------
bool VeString::EqualsNoCase(const VeChar8* pc8Str) const
{
	if(pc8Str == NULL)
		return m_hHandle == NULL;
	else if(VeStrlen(pc8Str) != Length())
		return false;
	return CompareNoCase(pc8Str) == 0;
}
//--------------------------------------------------------------------------
VeString VeString::GetSubstring(VeUInt32 u32Begin, VeUInt32 u32End) const
{
	if (u32Begin < u32End && u32Begin < Length()
		&& u32End <= Length() && m_hHandle != NULL)
	{
		VeString kString((u32End - u32Begin + 2));
		VeStrncpy(kString.m_hHandle,
			kString.GetBufferSize(kString.m_hHandle) - 1,
			GetString(m_hHandle) + u32Begin, u32End - u32Begin);
		kString.m_hHandle[u32End - u32Begin] = 0;
		kString.CalcLength();
		return kString;
	}
	else
	{
		return (const VeChar8*)NULL;
	}
}
//--------------------------------------------------------------------------
VeString VeString::GetSubstring(VeUInt32 u32Begin,
	const VeChar8* pc8Delimeters) const
{
	if (u32Begin < Length() && m_hHandle != NULL && pc8Delimeters != NULL)
	{
		VeChar8* pcStr = VeStrpbrk(GetString(m_hHandle)
			+ u32Begin, pc8Delimeters);
		if (pcStr == NULL)
			return (const VeChar8*)NULL;
		else
			return GetSubstring(u32Begin,
			(VeUInt32)(pcStr - GetString(m_hHandle)));
	}
	else
	{
		return (const VeChar8*)NULL;
	}
}
//--------------------------------------------------------------------------
VeUInt32 VeString::Find(VeChar8 c, VeUInt32 u32Start) const
{
	if (u32Start >= Length())
		return VE_INFINITE;

	VeChar8* pcStr = VeStrchr(GetString(m_hHandle) + u32Start, c);
	if (pcStr == NULL)
		return VE_INFINITE;

	VeInt32 iReturn = (VeInt32)(pcStr - GetString(m_hHandle));
	if (iReturn < 0)
		return VE_INFINITE;
	else
		return (VeUInt32)iReturn;
}
//--------------------------------------------------------------------------
VeUInt32 VeString::Find(const VeChar8* pc8Str, VeUInt32 u32Start) const
{
	if (u32Start >= Length())
		return VE_INFINITE;
	if (pc8Str == NULL || pc8Str[0] == 0)
		return VE_INFINITE;
	VeChar8* pcSubStr = VeStrstr(GetString(m_hHandle) + u32Start, pc8Str);
	if (pcSubStr == NULL)
		return VE_INFINITE;

	VeInt32 iReturn = (VeInt32)(pcSubStr - GetString(m_hHandle));
	if (iReturn < 0)
		return VE_INFINITE;
	else
		return (VeUInt32)iReturn;
}
//--------------------------------------------------------------------------
bool VeString::Contains(const VeChar8* pc8Str) const
{
	return Find(pc8Str) != VE_INFINITE;
}
//--------------------------------------------------------------------------
bool VeString::ContainsNoCase(const VeChar8* pc8Str) const
{
	if (m_hHandle == pc8Str && pc8Str != NULL)
		return true;

	if (pc8Str == NULL || m_hHandle == NULL)
		return false;

	const VeChar8* pcMyString = (const VeChar8*) m_hHandle;
	VeSizeT stOtherLength = VeStrlen(pc8Str);
	for (VeUInt32 uiMyIdx = 0; uiMyIdx < Length(); uiMyIdx++)
	{
		if (VeStrnicmp(&pcMyString[uiMyIdx], pc8Str,
			(VeInt32)stOtherLength) == 0)
			return true;
	}
	return false;
}
//--------------------------------------------------------------------------
VeUInt32 VeString::FindReverse(VeChar8 c) const
{
	if (m_hHandle == NULL)
		return VE_INFINITE;

	VeChar8* pcStr = VeStrrchr(GetString(m_hHandle), c);
	if (pcStr == NULL)
		return VE_INFINITE;
	else if (c == 0)
		return VE_INFINITE;
	VeInt32 iReturn = (VeInt32)(pcStr - GetString(m_hHandle));
	if (iReturn < 0)
		return VE_INFINITE;
	else
		return (VeUInt32) iReturn;
}
//--------------------------------------------------------------------------
VeUInt32 VeString::FindReverse(VeChar8 c, VeUInt32 u32StartIdx) const
{
	if (m_hHandle == NULL || c == 0)
		return VE_INFINITE;

	if (u32StartIdx >= Length())
		u32StartIdx = Length() - 1;

	const VeChar8* pcValue = GetString(m_hHandle);
	while (u32StartIdx != VE_INFINITE)
	{
		if (pcValue[u32StartIdx] == c)
			return u32StartIdx;
		--u32StartIdx;
	}

	 return VE_INFINITE;
}
//--------------------------------------------------------------------------
VeUInt32 VeString::FindOneOf(const VeChar8* pc8Str, VeUInt32 uiIndex) const
{
	if (pc8Str == NULL || pc8Str == 0 || m_hHandle == NULL)
		return VE_INFINITE;
	VeChar8* pcSubStr = VeStrpbrk(GetString(m_hHandle) + uiIndex, pc8Str);
	if (pcSubStr == NULL)
		return VE_INFINITE;
	VeInt32 iReturn = (VeInt32)(pcSubStr - GetString(m_hHandle));
	if (iReturn < 0)
		return VE_INFINITE;
	else
		return (VeUInt32) iReturn;
}
//--------------------------------------------------------------------------
VeString VeString::Mid(VeUInt32 u32Begin, VeUInt32 u32Count) const
{
	VeUInt32 u32End = u32Begin + u32Count;
	if (u32End > Length() || u32Count == VE_INFINITE)
		u32End = Length();
	if (u32Begin < u32End && u32Begin < Length() && 
		u32End <= Length())
	{
		VeString kString(u32End - u32Begin + 2);
		VeStrncpy(kString.m_hHandle,
			kString.GetBufferSize(kString.m_hHandle) - 1,
			GetString(m_hHandle) + u32Begin, u32End - u32Begin);
		kString.m_hHandle[u32End - u32Begin] = 0;
		kString.CalcLength();
		return kString;
	}
	else
	{
		return (const VeChar8*)NULL;
	}
}
//--------------------------------------------------------------------------
VeString VeString::Left(VeUInt32 u32Count) const
{
	VeUInt32 u32Begin = 0;
	VeUInt32 u32End = u32Begin + u32Count;
	if (u32End > Length())
		u32End = Length();
	if (u32Begin < u32End && u32Begin < Length() && 
		u32End <= Length())
	{
		VeString kString(u32End - u32Begin + 2);
		VeStrncpy(kString.m_hHandle,
			kString.GetBufferSize(kString.m_hHandle) - 1,
			GetString(m_hHandle) + u32Begin, u32End - u32Begin);
		kString.m_hHandle[u32End - u32Begin] = 0;
		kString.CalcLength();
		return kString;
	}
	else
	{
		return (const VeChar8*)NULL;
	}
}
//--------------------------------------------------------------------------
VeString VeString::Right(VeUInt32 u32Count) const
{
	VeUInt32 uiEnd = Length();
	VeInt32 iBegin = uiEnd - u32Count;
	VeUInt32 uiBegin = 0;

	if (iBegin > 0)
		uiBegin = (VeUInt32) iBegin;

	if (uiEnd > Length())
		uiEnd = Length();
	if (uiBegin < uiEnd && uiBegin < Length() && 
		uiEnd <= Length())
	{
		VeString kString(uiEnd - uiBegin + 2);
		VeStrncpy(kString.m_hHandle,
			kString.GetBufferSize(kString.m_hHandle) - 1,
			GetString(m_hHandle) + uiBegin, uiEnd - uiBegin);
		kString.m_hHandle[uiEnd - uiBegin] = 0;
		kString.CalcLength();
		return kString;
	}
	else
	{
		return (const VeChar8*)NULL;
	}
}
//--------------------------------------------------------------------------
void VeString::Replace(const VeChar8* pcWhatToReplace,
	const VeChar8* pcReplaceWith)
{
	if (pcWhatToReplace == NULL || pcReplaceWith == NULL)
		return;

	VeUInt32 stWhatToReplaceLength = (VeUInt32)VeStrlen(pcWhatToReplace);
	VeUInt32 stReplaceWithLength = (VeUInt32)VeStrlen(pcReplaceWith);
	VeUInt32 uiOccuranceCount = 0;
	VeUInt32 uiOriginalLength = Length();

	VeUInt32 ui = 0;
	for (; ui < uiOriginalLength && ui != VE_INFINITE;)
	{
		ui = Find(pcWhatToReplace, ui);
		if (ui != VE_INFINITE)
		{
			uiOccuranceCount++;
			ui = (VeUInt32)(ui + stWhatToReplaceLength);
		}
	}

	if (uiOccuranceCount == 0)
		return;

	VeUInt32 uiNumCharsToReplace = 
		uiOccuranceCount * stWhatToReplaceLength;
	VeUInt32 uiNumCharsNeededToReplace = 
		uiOccuranceCount * stReplaceWithLength;
	VeUInt32 uiSizeNeeded = 
		uiOriginalLength - uiNumCharsToReplace + uiNumCharsNeededToReplace;

	if (uiSizeNeeded > uiOriginalLength)
		CopyOnWriteAndResize(uiSizeNeeded - uiOriginalLength);
	else
		CopyOnWrite();

	for(ui = 0; ui < uiSizeNeeded && uiOccuranceCount > 0; uiOccuranceCount--)
	{
		VeChar8* pcStart = VeStrstr(m_hHandle + ui, pcWhatToReplace);
		VE_ASSERT(pcStart != NULL);
		VeChar8* pcEnd = pcStart + stReplaceWithLength;

		VeUInt32 u32Size = (VeUInt32)VeStrlen(pcStart
			+ stWhatToReplaceLength) + 1;

		VeMemmove(pcStart + stReplaceWithLength, u32Size, pcStart
			+ stWhatToReplaceLength, u32Size);
		VeMemcpy(pcStart, pcReplaceWith, stReplaceWithLength);
		ui = (VeUInt32)(pcEnd - m_hHandle);
	}

	m_hHandle[uiSizeNeeded] = 0;

	CalcLength();
}
//--------------------------------------------------------------------------
void VeString::Insert(const VeChar8* pcInsertString, VeUInt32 u32Index)
{
	if(pcInsertString == NULL)
		return;

	VeUInt32 stOriginalLength = Length();
	VeUInt32 stIndex = u32Index;
	VeUInt32 stInsertLength = (VeUInt32)VeStrlen(pcInsertString);

#if defined(VE_DEBUG)
	const VeChar8* pcOriginalString = GetString(m_hHandle);
	VE_ASSERT(!(pcInsertString >= pcOriginalString && 
		pcInsertString <= pcOriginalString + stOriginalLength));
#endif

	if (stIndex >= stOriginalLength)
	{
		Concatenate(pcInsertString);
		return;
	}

	VeUInt32 stNewSize = stInsertLength + stOriginalLength + 1;

	CopyOnWriteAndResize(stInsertLength);
	VeChar8* pcBuffer = GetString(m_hHandle);
	VeMemmove(&pcBuffer[stIndex + stInsertLength], 
		stNewSize - stIndex - stInsertLength,
		&pcBuffer[stIndex], stOriginalLength - stIndex + 1);
	VeMemmove(&pcBuffer[stIndex], stNewSize - stIndex,
		pcInsertString, stInsertLength);
	CalcLength();
}
//--------------------------------------------------------------------------
void VeString::RemoveRange(VeUInt32 u32StartIdx, VeUInt32 u32NumChars)
{
	VeUInt32 uiEnd = Length();
	if (u32StartIdx >= uiEnd)
		return;

	if (u32StartIdx + u32NumChars > uiEnd)
		u32NumChars = uiEnd - u32StartIdx;

	CopyOnWrite();
	VeChar8* pcBuffer = GetString(m_hHandle);
	VeMemmove(&pcBuffer[u32StartIdx], uiEnd - u32StartIdx + 1,
		&pcBuffer[u32StartIdx + u32NumChars], 
		uiEnd - u32StartIdx - u32NumChars + 1);
	CalcLength();
}
//--------------------------------------------------------------------------
void VeString::ToUpper()
{
	if (m_hHandle == NULL)
		return;

	CopyOnWrite();
	for ( VeUInt32 ui = 0; ui < Length() ; ui++)
	{
		VeChar8 c = GetString(m_hHandle)[ui];
		if ( ('a' <= c) && (c <= 'z') )
			GetString(m_hHandle)[ui] -= 'a' - 'A';
	}
}
//--------------------------------------------------------------------------
void VeString::ToLower()
{
	if (m_hHandle == NULL)
		return;

	CopyOnWrite();
	for ( VeUInt32 ui = 0; ui < Length() ; ui++)
	{
		VeChar8 c = GetString(m_hHandle)[ui];
		if ( ('A' <= c) && (c <= 'Z') )
			GetString(m_hHandle)[ui] -= 'A' - 'a';
	}
}
//--------------------------------------------------------------------------
void VeString::Reverse()
{
	if (Length() < 2)
		return;

	CopyOnWrite();
	VeUInt32 uiEnd = Length() - 1;
	for (VeUInt32 uiBegin = 0; uiBegin < uiEnd; 
		uiBegin++, uiEnd--)
	{
		VeChar8 c = GetString(m_hHandle)[uiBegin];
		GetString(m_hHandle)[uiBegin] = GetString(m_hHandle)[uiEnd];
		GetString(m_hHandle)[uiEnd] = c;
	}
}
//--------------------------------------------------------------------------
void VeString::TrimLeft(VeChar8 c)
{
	if ( c == 0 || m_hHandle == NULL)
		return;

	CopyOnWrite();
	VeUInt32 uiTrimCount = 0;
	bool bContinue = true;
	for (VeUInt32 ui = 0; 
		ui < Length() && bContinue; ui++)
	{
		if (GetString(m_hHandle)[ui] == c)
			uiTrimCount++;
		else
			bContinue = false;
	}

	if (uiTrimCount > 0)
	{
		VeUInt32 u32Size = Length() - uiTrimCount + 1;
		VeMemmove(GetString(m_hHandle), u32Size, GetString(m_hHandle)
			+ uiTrimCount, u32Size);
		CalcLength();
	}
}
//--------------------------------------------------------------------------
void VeString::TrimRight(VeChar8 c)
{
	if (c == 0 || m_hHandle == NULL)
		return;

	CopyOnWrite();
	VeUInt32 uiTrimCount = 0;
	bool bContinue = true;
	for(VeInt32 i = Length() - 1; i >= 0 && bContinue; i--)
	{
		if (GetString(m_hHandle)[i] == c)
			uiTrimCount++;
		else
			bContinue = false;
	}

	if (uiTrimCount > 0)
	{
		VeChar8* pcStr = GetString(m_hHandle) + Length() - uiTrimCount;
		pcStr[0] = 0;
		CalcLength();
	}
}
//--------------------------------------------------------------------------
void VeString::Concatenate(const VeChar8* pcStr)
{
	if (pcStr == NULL)
		return;

	VeUInt32 stLen = (VeUInt32)VeStrlen(pcStr);
	if (stLen > 0)
	{
		StringHandle kHandle = m_hHandle;
		bool bInternalIncrementRefCount = false;
		if (pcStr == GetString(m_hHandle))
		{
			IncRefCount(kHandle);
			CopyOnWriteAndResize(stLen, true);
			bInternalIncrementRefCount = true;
		}
		else
		{
			CopyOnWriteAndResize(stLen, false);
		}

		VeStrcpy(GetString(m_hHandle) + Length(), stLen + 1, pcStr);
		CalcLength();
		if (bInternalIncrementRefCount)
			DecRefCount(kHandle);
	}
}
//--------------------------------------------------------------------------
void VeString::Concatenate(VeChar8 ch)
{
	CopyOnWriteAndResize(1);
	VeUInt32 stLength = Length();

	m_hHandle[stLength] = ch;
	m_hHandle[stLength+1] = 0;
	CalcLength();
}
//--------------------------------------------------------------------------
bool VeString::ToBool(bool& b) const
{
	VeChar8* pcStr = ConsumeWhitespace(GetString(m_hHandle), Length());

	if(VeStrlen(pcStr) < 4)
	{
		return false;
	}
	else if(VeStrnicmp(pcStr, "true", 4) == 0)
	{
		b = true;
		return true;
	}
	else if(VeStrnicmp(pcStr, "false", 4) == 0)
	{
		b = false;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeString::To(bool& b) const
{
	return ToBool(b);
}
//--------------------------------------------------------------------------
bool VeString::ToFloat(VeFloat32& f) const
{
	VeChar8* pcString = GetString(m_hHandle);
	if(pcString == NULL)
		return false;
	f = (VeFloat32)VeAtof(pcString);
	if(f == 0)
	{
		if(FindOneOf("-0") != VE_INFINITE)
			return true;
		else
			return false;
	}
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeFloat32& f) const
{
	return ToFloat(f);
}
//--------------------------------------------------------------------------
bool VeString::ToInt(VeInt32& i) const
{
	VeChar8* pcString = GetString(m_hHandle);

	if(pcString == NULL)
		return false;

	i = VeAtoi(pcString);
	if(i == 0)
	{
		if(FindOneOf("-0") != VE_INFINITE)
			return true;
		else
			return false;
	}
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeInt32& i) const
{
	return ToInt(i);
}
//--------------------------------------------------------------------------
bool VeString::To(VeInt16& i) const
{
	VeInt32 iTemp = 0;
	bool bResult = ToInt(iTemp);
	i = (VeInt16)iTemp;
	return bResult;
}
//--------------------------------------------------------------------------
bool VeString::To(VeInt8& i) const
{
	VeInt32 iTemp = 0;
	bool bResult = ToInt(iTemp);
	i = (VeInt8)iTemp;
	return bResult;
}
//--------------------------------------------------------------------------
bool VeString::ToUInt(VeUInt32& ui) const
{
	VeChar8* pcString = GetString(m_hHandle);

	if(pcString == NULL)
		return false;

	ui = VeAtoui(pcString);
	if(ui == 0)
	{
		if(FindOneOf("-0") != VE_INFINITE)
			return true;
		else
			return false;
	}
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeUInt32& ui) const
{
	return ToUInt(ui);
}
//--------------------------------------------------------------------------
bool VeString::To(VeUInt16& ui) const
{
	VeUInt32 iTemp = 0;
	bool bResult = ToUInt(iTemp);
	ui = (VeUInt16)iTemp;
	return bResult;
}
//--------------------------------------------------------------------------
bool VeString::To(VeUInt8& ui) const
{
	VeUInt32 iTemp = 0;
	bool bResult = ToUInt(iTemp);
	ui = (VeUInt8)iTemp;
	return bResult;
}
//--------------------------------------------------------------------------
bool VeString::ToVector2D(VeVector2D& kVec) const
{
	const VeChar8 acSeps [] = ",";
	VeChar8* pcContext;
	StringHandle kHandle = AllocateAndCopyHandle(m_hHandle);
	VeString kString(VeStrtok(GetString(kHandle), acSeps, &pcContext));
	if(!kString.ToFloat(kVec.x))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString2(VeStrtok(NULL, acSeps, &pcContext));
	if(!kString2.ToFloat(kVec.y))
	{
		Deallocate(kHandle);
		return false;
	}

	Deallocate(kHandle);
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeVector2D& kVec) const
{
	return ToVector2D(kVec);
}
//--------------------------------------------------------------------------
bool VeString::ToVector3D(VeVector3D& kVec) const
{
	const VeChar8 acSeps [] = ",";
	VeChar8* pcContext;
	StringHandle kHandle = AllocateAndCopyHandle(m_hHandle);
	VeString kString(VeStrtok(GetString(kHandle), acSeps, &pcContext));
	if(!kString.ToFloat(kVec.x))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString2(VeStrtok(NULL, acSeps, &pcContext));
	if (!kString2.ToFloat(kVec.y))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString3(VeStrtok(NULL, acSeps, &pcContext));
	if (!kString3.ToFloat(kVec.z))
	{
		Deallocate(kHandle);
		return false;
	}

	Deallocate(kHandle);
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeVector3D& kVec) const
{
	return ToVector3D(kVec);
}
//--------------------------------------------------------------------------
bool VeString::ToVector4D(VeVector4D& kVec) const
{
	const VeChar8 acSeps [] = ",";
	VeChar8* pcContext;
	StringHandle kHandle = AllocateAndCopyHandle(m_hHandle);
	VeString kString(VeStrtok(GetString(kHandle), acSeps, &pcContext));
	if (!kString.ToFloat(kVec.x))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString2(VeStrtok(NULL, acSeps, &pcContext));
	if (!kString2.ToFloat(kVec.y))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString3(VeStrtok(NULL, acSeps, &pcContext));
	if (!kString3.ToFloat(kVec.z))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString4(VeStrtok(NULL, acSeps, &pcContext));
	if (!kString4.ToFloat(kVec.w))
	{
		Deallocate(kHandle);
		return false;
	}

	Deallocate(kHandle);
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeVector4D& kVec) const
{
	return ToVector4D(kVec);
}
//--------------------------------------------------------------------------
bool VeString::ToRGBA(VeColor& kColor) const
{
	const VeChar8 acSeps [] = ",";
	StringHandle kHandle = AllocateAndCopyHandle(m_hHandle);
	VeChar8* pcContext;

	VeString kString(VeStrtok(GetString(kHandle), acSeps, &pcContext));
	if(!kString.ToFloat(kColor.r))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString2(VeStrtok(NULL, acSeps, &pcContext));
	if(!kString2.ToFloat(kColor.g))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString3(VeStrtok(NULL, acSeps, &pcContext));
	if(!kString3.ToFloat(kColor.b))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString4(VeStrtok(NULL, acSeps, &pcContext));
	if(!kString4.ToFloat(kColor.a))
	{
		Deallocate(kHandle);
		return false;
	}

	Deallocate(kHandle);
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeColor& kColor) const
{
	return ToRGBA(kColor);
}
//--------------------------------------------------------------------------
bool VeString::ToBoundingBox2D(VeBoundingBox2D& kBox) const
{
	const VeChar8 acSeps [] = ",";
	StringHandle kHandle = AllocateAndCopyHandle(m_hHandle);
	VeChar8* pcContext;

	VeString kString(VeStrtok(GetString(kHandle), acSeps, &pcContext));
	if(!kString.ToFloat(kBox.m_kMin.x))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString2(VeStrtok(NULL, acSeps, &pcContext));
	if(!kString2.ToFloat(kBox.m_kMin.y))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString3(VeStrtok(NULL, acSeps, &pcContext));
	if(!kString3.ToFloat(kBox.m_kMax.x))
	{
		Deallocate(kHandle);
		return false;
	}

	VeString kString4(VeStrtok(NULL, acSeps, &pcContext));
	if(!kString4.ToFloat(kBox.m_kMax.y))
	{
		Deallocate(kHandle);
		return false;
	}

	Deallocate(kHandle);
	return true;
}
//--------------------------------------------------------------------------
bool VeString::To(VeBoundingBox2D& kBox) const
{
	return ToBoundingBox2D(kBox);
}
//--------------------------------------------------------------------------
VeString VeString::FromBool(bool b)
{
	if(b)
		return VeString("true");
	else
		return VeString("false");
}
//--------------------------------------------------------------------------
VeString VeString::From(bool b)
{
	return FromBool(b);
}
//--------------------------------------------------------------------------
VeString VeString::FromFloat(VeFloat32 f)
{
	VeChar8 acString[50];
	VeSprintf(acString, "%f", f);
	VeString kString(acString);
	return kString;
}
//--------------------------------------------------------------------------
VeString VeString::From(VeFloat32 f)
{
	return FromFloat(f);
}
//--------------------------------------------------------------------------
VeString VeString::FromInt(VeInt32 i)
{
	VeChar8 acString[32];
	VeSprintf(acString, "%d", i);
	return VeString(acString);
}
//--------------------------------------------------------------------------
VeString VeString::From(VeInt32 i)
{
	return FromInt(i);
}
//--------------------------------------------------------------------------
VeString VeString::From(VeInt16 i)
{
	return FromInt(i);
}
//--------------------------------------------------------------------------
VeString VeString::From(VeInt8 i)
{
	return FromInt(i);
}
//--------------------------------------------------------------------------
VeString VeString::FromUInt(VeUInt32 ui)
{
	VeChar8 acString[32];
	VeSprintf(acString, "%d", ui);
	return VeString(acString);
}
//--------------------------------------------------------------------------
VeString VeString::From(VeUInt32 ui)
{
	return FromUInt(ui);
}
//--------------------------------------------------------------------------
VeString VeString::From(VeUInt16 ui)
{
	return FromUInt(ui);
}
//--------------------------------------------------------------------------
VeString VeString::From(VeUInt8 ui)
{
	return FromUInt(ui);
}
//--------------------------------------------------------------------------
VeString VeString::FromVector2D(VeVector2D& kPt)
{
	VeChar8 acString[128];
	VeSprintf(acString, "%f,%f", kPt.x, kPt.y);
	VeString kString(acString);
	return kString;
}
//--------------------------------------------------------------------------
VeString VeString::From(VeVector2D& kPt)
{
	return FromVector2D(kPt);
}
//--------------------------------------------------------------------------
VeString VeString::FromVector3D(VeVector3D& kPt)
{
	VeChar8 acString[128];
	VeSprintf(acString, "%f,%f,%f", kPt.x, kPt.y, kPt.z);
	VeString kString(acString);
	return kString;
}
//--------------------------------------------------------------------------
VeString VeString::From(VeVector3D& kPt)
{
	return FromVector3D(kPt);
}
//--------------------------------------------------------------------------
VeString VeString::FromVector4D(VeVector4D& kPt)
{
	VeChar8 acString[128];
	VeSprintf(acString, "%f,%f,%f,%f", kPt.x, kPt.y, kPt.z, kPt.w);
	VeString kString(acString);
	return kString;
}
//--------------------------------------------------------------------------
VeString VeString::From(VeVector4D& kPt)
{
	return FromVector4D(kPt);
}
//--------------------------------------------------------------------------
VeString VeString::FromRGBA(VeColor& kColor)
{
	VeChar8 acString[160];
	VeSprintf(acString, "%f,%f,%f,%f)", kColor.r, kColor.g, kColor.b, kColor.a);
	VeString kString(acString);
	return kString;
}
//--------------------------------------------------------------------------
VeString VeString::From(VeColor& kColor)
{
	return FromRGBA(kColor);
}
//--------------------------------------------------------------------------
VeUInt32 VeString::CalculateHash(const VeChar8* pcString)
{
	VeUInt32 u32Hash = 0;

	while(*pcString)
	{
		u32Hash = (*pcString++) + (u32Hash << 6) + (u32Hash << 16) - u32Hash;
	}

	return (u32Hash & 0x7FFFFFFF);
}
//--------------------------------------------------------------------------
VeUInt32 VeString::KeyToHashCode(const VeChar8* pcString, VeUInt32 u32TableSize)
{
	return CalculateHash(pcString) % u32TableSize;
}
//--------------------------------------------------------------------------
VeUInt32 VeString::GetHashCode() const
{
	return CalculateHash(GetString(m_hHandle));
}
//--------------------------------------------------------------------------
VeString::operator const VeChar8*() const
{
	return GetString(m_hHandle);
}
//--------------------------------------------------------------------------
VeChar8* VeString::GetString()
{
	return GetString(m_hHandle);
}
//--------------------------------------------------------------------------
VeString& VeString::operator = (VeString& stringSrc)
{
	SetBuffer(stringSrc.m_hHandle);
	return *this;
}
//--------------------------------------------------------------------------
VeString& VeString::operator = (const VeChar8* psz)
{
	if(psz == GetString(m_hHandle))
		return *this;

	Swap(m_hHandle, psz);
	return *this;
}
//--------------------------------------------------------------------------
VeString& VeString::operator = (const VeFixedString& kString)
{
	return VeString::operator = ((const VeChar8*)kString);
}
//--------------------------------------------------------------------------
VeString& VeString::operator = (VeChar8 ch)
{
	VeChar8 acString[2];
	acString[0] = ch;
	acString[1] = '\0';
	return VeString::operator = ((const VeChar8*)acString);
}
//--------------------------------------------------------------------------
VeString& VeString::operator += (VeString& string)
{
	Concatenate(string);
	return *this;
}
//--------------------------------------------------------------------------
VeString& VeString::operator += (VeChar8 ch)
{
	Concatenate(ch);
	return *this;
}
//--------------------------------------------------------------------------
VeString& VeString::operator += (const VeChar8* pcString)
{
	Concatenate(pcString);
	return *this;
}
//--------------------------------------------------------------------------
VeString& VeString::operator += (const VeFixedString& kString)
{
	Concatenate((const VeChar8*)kString);
	return *this;
}
//--------------------------------------------------------------------------
VeString operator + (const VeString& string1, const VeString& string2)
{
	VeString kString(string1);
	kString.Concatenate(string2);
	return kString;
}
//--------------------------------------------------------------------------
VeString operator + (const VeString& string, VeChar8 ch)
{
	VeString kString(string);
	kString.Concatenate(ch);
	return kString;
}
//--------------------------------------------------------------------------
VeString operator + (VeChar8 ch, const VeString& string)
{
	VeString kString(ch);
	kString.Concatenate(string);
	return kString;
}
//--------------------------------------------------------------------------
VeString operator + (const VeString& string, const VeChar8* lpsz)
{
	VeString kString(string);
	kString.Concatenate(lpsz);
	return kString;
}
//--------------------------------------------------------------------------
VeString operator + (const VeString& string, const VeFixedString& kString2)
{
	VeString kString(string);
	kString.Concatenate((const VeChar8*)kString2);
	return kString;
}
//--------------------------------------------------------------------------
VeString operator + (const VeChar8* lpsz, const VeString& string)
{
	VeString kString(lpsz);
	kString.Concatenate(string);
	return kString;
}
//--------------------------------------------------------------------------
VeString operator + (const VeFixedString& kStr, const VeString& string)
{
	VeString kString((const VeChar8*)kStr);
	kString.Concatenate(string);
	return kString;
}
//--------------------------------------------------------------------------
bool operator == (const VeString& s1, const VeString& s2)
{
	return s1.Compare(s2) == 0;
}
//--------------------------------------------------------------------------
bool operator == (const VeString& s1, const VeChar8* s2)
{
	return s1.Compare(s2) == 0;
}
//--------------------------------------------------------------------------
bool operator == (const VeString& s1, const VeFixedString& s2)
{
	return s1.Compare((const VeChar8*)s2) == 0;
}
//--------------------------------------------------------------------------
bool operator == (const VeChar8* s1, const VeString& s2)
{
	return s2.Compare(s1) == 0;
}
//--------------------------------------------------------------------------
bool operator == (const VeFixedString& s1, const VeString& s2)
{
	return s2.Compare((const VeChar8*)s1) == 0;
}
//--------------------------------------------------------------------------
bool operator != (const VeString& s1, const VeString& s2)
{
	return s1.Compare(s2) != 0;
}
//--------------------------------------------------------------------------
bool operator != (const VeString& s1, const VeChar8* s2)
{
	return s1.Compare(s2) != 0;
}
//--------------------------------------------------------------------------
bool operator != (const VeString& s1, const VeFixedString& s2)
{
	return s1.Compare((const VeChar8*)s2) != 0;
}
//--------------------------------------------------------------------------
bool operator != (const VeChar8* s1, const VeString& s2)
{
	return s2.Compare(s1) != 0;
}
//--------------------------------------------------------------------------
bool operator != (const VeFixedString& s1, const VeString& s2)
{
	return s2.Compare((const VeChar8*)s1) != 0;
}
//--------------------------------------------------------------------------
bool operator < (const VeString& s1, const VeString& s2)
{
	return s1.Compare(s2) < 0;
}
//--------------------------------------------------------------------------
bool operator < (const VeString& s1, const VeChar8* s2)
{
	return s1.Compare(s2) < 0;
}
//--------------------------------------------------------------------------
bool operator < (const VeString& s1, const VeFixedString& s2)
{
	return s1.Compare((const VeChar8*)s2) < 0;
}
//--------------------------------------------------------------------------
bool operator < (const VeChar8* s1, const VeString& s2)
{
	return s2.Compare(s1) > 0;
}
//--------------------------------------------------------------------------
bool operator < (const VeFixedString& s1, const VeString& s2)
{
	return s2.Compare((const VeChar8*)s1) > 0;
}
//--------------------------------------------------------------------------
bool operator > (const VeString& s1, const VeString& s2)
{
	return s1.Compare(s2) > 0;
}
//--------------------------------------------------------------------------
bool operator > (const VeString& s1, const VeChar8* s2)
{
	return s1.Compare(s2) > 0;
}
//--------------------------------------------------------------------------
bool operator > (const VeString& s1, const VeFixedString& s2)
{
	return s1.Compare((const VeChar8*)s2) > 0; 
}
//--------------------------------------------------------------------------
bool operator > (const VeChar8* s1, const VeString& s2)
{
	return s2.Compare(s1) < 0;
}
//--------------------------------------------------------------------------
bool operator > (const VeFixedString& s1, const VeString& s2)
{
	return s2.Compare((const VeChar8*)s1) < 0; 
}
//--------------------------------------------------------------------------
bool operator <= (const VeString& s1, const VeString& s2)
{
	return s1.Compare(s2) <= 0;
}
//--------------------------------------------------------------------------
bool operator <= (const VeString& s1, const VeChar8* s2)
{
	return s1.Compare(s2) <= 0;
}
//--------------------------------------------------------------------------
bool operator <= (const VeString& s1, const VeFixedString& s2)
{
	return s1.Compare((const VeChar8*)s2) <= 0;
}
//--------------------------------------------------------------------------
bool operator <= (const VeChar8* s1, const VeString& s2)
{
	return s2.Compare(s1) >= 0;
}
//--------------------------------------------------------------------------
bool operator <= (const VeFixedString& s1, const VeString& s2)
{
	return s2.Compare((const VeChar8*)s1) >= 0;
}
//--------------------------------------------------------------------------
bool operator >= (const VeString& s1, const VeString& s2)
{
	return s1.Compare(s2) >= 0;
}
//--------------------------------------------------------------------------
bool operator >= (const VeString& s1, const VeChar8* s2)
{
	return s1.Compare(s2) >= 0;
}
//--------------------------------------------------------------------------
bool operator >= (const VeString& s1, const VeFixedString& s2)
{
	return s1.Compare((const VeChar8*)s2) >= 0;
}
//--------------------------------------------------------------------------
bool operator >= (const VeChar8* s1, const VeString& s2)
{
	return s2.Compare(s1) <= 0; 
}
//--------------------------------------------------------------------------
bool operator >= (const VeFixedString& s1, const VeString& s2)
{
	return s2.Compare((const VeChar8*)s1) <= 0;
}
//--------------------------------------------------------------------------
bool IsTrue(VeString strStr)
{
	bool b = false;
	if(strStr.ToBool(b))
		return b;

	VE_ASSERT(strStr.ToBool(b));
	return false;
}
//--------------------------------------------------------------------------
VeChar8* VeString::MakeExternalCopy()
{
	VeUInt32 uiSize = Length() + 1;
	VeChar8* pcStr = VeAlloc(VeChar8, uiSize);
	VeStrcpy(pcStr, uiSize, GetString(m_hHandle));
	return pcStr;
}
//--------------------------------------------------------------------------
VeGlobalStringTable::VeGlobalStringTable() : m_u32NumStrings(0)
{

}
//--------------------------------------------------------------------------
VeGlobalStringTable::~VeGlobalStringTable()
{

}
//--------------------------------------------------------------------------
const VeGlobalStringTable::StringHandle VeGlobalStringTable::AddString(
	const VeChar8* pcString)
{
	if(!pcString) return NULL;
	VeSizeT stStrLen = VeStrlen(pcString);
	VeUInt32 u32Hash = HashFunction(pcString, (VeUInt32)stStrLen);
	VE_ASSERT(stStrLen < 65536 && u32Hash < VE_NUM_GLOBAL_STRING_HASH_BUCKETS);
	StringHandle kHandle = FindString(pcString, (VeUInt32)stStrLen, u32Hash);
	if(kHandle)
	{
		IncRefCount(kHandle);
	}
	else
	{
		VeUInt32 u32AllocLen = VeUInt32(stStrLen) + 2 * sizeof(VeUInt32) + sizeof(VeChar8);
		if(u32AllocLen % sizeof(VeUInt32) != 0)
		{
			u32AllocLen += sizeof(VeUInt32) - (u32AllocLen % sizeof(VeUInt32));
		}
		void* pvMem = VeMalloc(u32AllocLen);
		VeChar8* pcMem = (VeChar8*)pvMem + 2 * sizeof(VeUInt32);
		kHandle = pcMem;
		VeUInt32* pu32Mem = (VeUInt32*)pvMem;
		pu32Mem[0] = 2;
		pu32Mem[1] = (VeUInt32(stStrLen) << GSTABLE_LEN_SHIFT) | ((u32Hash << GSTABLE_HASH_SHIFT) & GSTABLE_HASH_MASK);
		VeMemcpy(pcMem, pcString, stStrLen + 1);
		InsertString(kHandle, u32Hash);
	}
	return kHandle;
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::GetNumString()
{
	return m_u32NumStrings;
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::GetBucketSize(VeUInt32 uiWhichBucket)
{
	VE_ASSERT(uiWhichBucket < VE_NUM_GLOBAL_STRING_HASH_BUCKETS);
	return m_kHashArray[uiWhichBucket].Size();
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::GetTotalNumberOfBuckets()
{
	return VE_NUM_GLOBAL_STRING_HASH_BUCKETS;
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::GetMaxBucketSize()
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	VeUInt32 u32Size = 0;
	for(VeUInt32 i = 0; i < VE_NUM_GLOBAL_STRING_HASH_BUCKETS; ++i)
	{
		u32Size = VE_MAX(u32Size, m_kHashArray[i].Size());
	}
	return u32Size;
}
//--------------------------------------------------------------------------
const VeGlobalStringTable::StringHandle VeGlobalStringTable::FindString(
	const VeChar8* pcString, VeUInt32 u32Len, VeUInt32 u32Hash)
{
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	VeVector<StringHandle>& kStrArray = m_kHashArray[u32Hash];
	for(VeUInt32 i(0); i < kStrArray.Size(); ++i)
	{
		StringHandle kPossibleMatchString = kStrArray[i];
		if(kPossibleMatchString == pcString || (GetString(kPossibleMatchString) && 
			GetLength(kPossibleMatchString) == u32Len && VeStrcmp(GetString(kPossibleMatchString), pcString) == 0))
		{
			return kPossibleMatchString;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
void VeGlobalStringTable::InsertString(const StringHandle& kHandle,
	VeUInt32 u32Hash)
{
	VE_ASSERT(kHandle && ValidateString(kHandle));
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	m_kHashArray[u32Hash].PushBack(kHandle);
	++m_u32NumStrings;
}
//--------------------------------------------------------------------------
void VeGlobalStringTable::RemoveString(const StringHandle& kHandle,
	VeUInt32 u32Hash)
{
	const VeChar8* pcString = GetString(kHandle);
	VE_AUTO_LOCK_MUTEX(m_kMutex);
	VeVector<StringHandle>& kStrArray = m_kHashArray[u32Hash];
	for(VeUInt32 i(0); i < kStrArray.Size(); ++i)
	{
		if(kStrArray[i] == pcString)
		{
			VeUInt32* pkMem = (VeUInt32*)GetRealBufferStart(kHandle);
			VE_ASSERT(GetRefCount(kHandle) > 0);
			if(VeAtomicDecrement32(pkMem[0]) == 0)
			{
				VE_ASSERT(!GetRefCount(kHandle));
				VeFree(GetRealBufferStart(kHandle));
				if(i < (kStrArray.Size() - 1))
				{
					kStrArray[i] = kStrArray.Back();
				}
				kStrArray.PopBack();
				--m_u32NumStrings;
			}
			break;
		}
	}
}
//--------------------------------------------------------------------------
VeChar8* VeGlobalStringTable::GetRealBufferStart(const StringHandle& kHandle)
{
	VE_ASSERT(kHandle);
	return ((VeChar8*)kHandle - 2 * sizeof(VeUInt32));
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::HashFunction(
	const VeChar8* pcKey, VeUInt32 u32Len)
{
	VeUInt32 u32Hash = 0;
	VeUInt32 u32Unroll = (VeUInt32)(u32Len & ~0x3);
	for(VeUInt32 ui = 0; ui < u32Unroll; ui += 4)
	{
		VeUInt32 uiHash0 = *pcKey;
		u32Hash = (u32Hash << 5) + u32Hash + uiHash0;
		VeUInt32 uiHash1 = *(pcKey + 1);
		u32Hash = (u32Hash << 5) + u32Hash + uiHash1;
		VeUInt32 uiHash2 = *(pcKey + 2);
		u32Hash = (u32Hash << 5) + u32Hash + uiHash2;
		VeUInt32 uiHash3 = *(pcKey + 3);
		u32Hash = (u32Hash << 5) + u32Hash + uiHash3;
		pcKey += 4;
	}
	while(*pcKey)
		u32Hash = (u32Hash << 5) + u32Hash + *pcKey++;
	return u32Hash % VE_NUM_GLOBAL_STRING_HASH_BUCKETS;
}
//--------------------------------------------------------------------------
void VeGlobalStringTable::IncRefCount(StringHandle& kHandle)
{
	if(kHandle)
	{
		VE_ASSERT(ValidateString(kHandle));
		VeUInt32* pkMem = (VeUInt32*)GetRealBufferStart(kHandle);
		VeAtomicIncrement32(pkMem[0]);
	}
}
//--------------------------------------------------------------------------
void VeGlobalStringTable::DecRefCount(StringHandle& kHandle)
{
	if(kHandle)
	{
		VE_ASSERT(ValidateString(kHandle));
		VeUInt32* pkMem = (VeUInt32*)GetRealBufferStart(kHandle);
		VeUInt32 u32Hash = GetHashValue(kHandle);
		if(VeAtomicDecrement32(pkMem[0]) == 1)
		{
			VeGlobalStringTable::GetSingleton().RemoveString(kHandle, u32Hash);
		}
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeGlobalStringTable::GetString(const StringHandle& kHandle)
{
	VE_ASSERT(kHandle && ValidateString(kHandle));
	return (const VeChar8*)kHandle;
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::GetLength(const StringHandle& kHandle)
{
	VE_ASSERT(kHandle && ValidateString(kHandle));
	VeUInt32* pkMem = (VeUInt32*)GetRealBufferStart(kHandle);
	return (pkMem[1] & GSTABLE_LEN_MASK) >> GSTABLE_LEN_SHIFT;
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::GetHashValue(const StringHandle& kHandle)
{
	VE_ASSERT(kHandle && ValidateString(kHandle));
	VeUInt32* pkMem = (VeUInt32*)GetRealBufferStart(kHandle);
	return (pkMem[1] & GSTABLE_HASH_MASK) >> GSTABLE_HASH_SHIFT;
}
//--------------------------------------------------------------------------
VeUInt32 VeGlobalStringTable::GetRefCount(const StringHandle& kHandle)
{
	VE_ASSERT(kHandle && ValidateString(kHandle));
	VeUInt32* pkMem = (VeUInt32*)GetRealBufferStart(kHandle);
	return pkMem[0];
}
//--------------------------------------------------------------------------
bool VeGlobalStringTable::ValidateString(const StringHandle& kHandle)
{
	if(!kHandle) return true;
	VeUInt32* pkMem = (VeUInt32*)GetRealBufferStart(kHandle);
	VeUInt32 u32Length = (pkMem[1] & GSTABLE_LEN_MASK) >> GSTABLE_LEN_SHIFT;
	return u32Length == VeStrlen((const VeChar8*)kHandle);
}
//--------------------------------------------------------------------------
VeFixedString::VeFixedString()
{
	m_kHandle = NULL;
}
//--------------------------------------------------------------------------
VeFixedString::VeFixedString(const VeChar8* pcString)
{
	m_kHandle = g_pStringTable->AddString(pcString);
}
//--------------------------------------------------------------------------
VeFixedString::VeFixedString(const VeFixedString& kString)
{
	VeGlobalStringTable::IncRefCount((VeGlobalStringTable::StringHandle&)kString.m_kHandle);
	m_kHandle = kString.m_kHandle;
}
//--------------------------------------------------------------------------
VeFixedString::~VeFixedString()
{
	VeGlobalStringTable::DecRefCount(m_kHandle);
}
//--------------------------------------------------------------------------
VeFixedString::operator const VeChar8* () const
{
	return m_kHandle;
}
//--------------------------------------------------------------------------
bool VeFixedString::Exists() const
{
	return m_kHandle ? true : false;
}
//--------------------------------------------------------------------------
VeFixedString& VeFixedString::operator = (const VeFixedString& kString)
{
	if(m_kHandle != kString.m_kHandle)
	{
		VeGlobalStringTable::StringHandle kHandle = kString.m_kHandle;
		VeGlobalStringTable::IncRefCount(kHandle);
		VeGlobalStringTable::DecRefCount(m_kHandle);
		m_kHandle = kHandle;
	}
	return *this;
}
//--------------------------------------------------------------------------
VeFixedString& VeFixedString::operator = (const VeChar8* pcString)
{
	if(m_kHandle != pcString)
	{
		VeGlobalStringTable::StringHandle kHandle = m_kHandle;
		m_kHandle = g_pStringTable->AddString(pcString);
		VeGlobalStringTable::DecRefCount(kHandle);
	}
	return *this;
}
//--------------------------------------------------------------------------
VeUInt32 VeFixedString::GetLength() const
{
	return VeGlobalStringTable::GetLength(m_kHandle);
}
//--------------------------------------------------------------------------
VeUInt32 VeFixedString::GetRefCount() const
{
	return VeGlobalStringTable::GetRefCount(m_kHandle);
}
//--------------------------------------------------------------------------
bool VeFixedString::Equals(const VeChar8* pcStr) const
{
	if(m_kHandle == pcStr)
		return true;

	if(pcStr == NULL || m_kHandle == NULL)
		return false;

	return VeStrcmp((const VeChar8*)m_kHandle, pcStr) == 0;
}
//--------------------------------------------------------------------------
bool VeFixedString::EqualsNoCase(const VeChar8* pcStr) const
{
	if(m_kHandle == pcStr)
		return true;

	if(pcStr == NULL || m_kHandle == NULL)
		return false;

	return VeStricmp((const VeChar8*) m_kHandle, pcStr) == 0;
}
//--------------------------------------------------------------------------
bool VeFixedString::Contains(const VeChar8* pcStr) const
{
	if(m_kHandle == pcStr && pcStr != NULL)
		return true;

	if(pcStr == NULL || m_kHandle == NULL || pcStr[0] == '\0' || m_kHandle[0] == '\0')
	{
		return false;
	}

	return VeStrstr((const VeChar8*)m_kHandle, pcStr) != NULL;
}
//--------------------------------------------------------------------------
bool VeFixedString::ContainsNoCase(const VeChar8* pcStr) const
{
	if(m_kHandle == pcStr && pcStr != NULL)
		return true;

	if(pcStr == NULL || m_kHandle == NULL || pcStr[0] == '\0' || m_kHandle[0] == '\0')
	{
		return false;
	}

	const VeChar8* pcMyString = m_kHandle;
	VeUInt32 u32OtherLength = (VeUInt32)VeStrlen(pcStr);
	for(VeUInt32 uiMyIdx = 0; uiMyIdx < GetLength(); uiMyIdx++)
	{
		if(VeStrnicmp(&pcMyString[uiMyIdx], pcStr, u32OtherLength) == 0)
			return true;
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeFixedString::operator == (const VeFixedString& s) const
{
	return Equals(s);
}
//--------------------------------------------------------------------------
bool VeFixedString::operator != (const VeFixedString& s) const
{
	return !Equals(s);
}
//--------------------------------------------------------------------------
bool VeFixedString::operator==(const VeChar8* s) const
{
	return Equals(s);
}
//--------------------------------------------------------------------------
bool VeFixedString::operator!=(const VeChar8* s) const
{
	return !Equals(s);
}
//--------------------------------------------------------------------------
bool operator == (const VeChar8* s1, const VeFixedString& s2)
{
	return s2.Equals(s1);
}
//--------------------------------------------------------------------------
bool operator != (const VeChar8* s1, const VeFixedString& s2)
{
	return !(s2.Equals(s1));
}
//--------------------------------------------------------------------------
