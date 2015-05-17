////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeNetwork.cpp
//  Version:     v1.00
//  Created:     24/10/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

using namespace RakNet;

//--------------------------------------------------------------------------
void RakNet::Write(BitStream& kOut, const VeChar8* pcStr,
	VeUInt32 u32Len)
{
	VeUInt8 u8Len = (u32Len <= 255) ? u32Len : 255;
	kOut.Write(u8Len);
	if(u8Len)
	{
		kOut.WriteAlignedBytes((const VeUInt8*)pcStr, u8Len);
	}
}
//--------------------------------------------------------------------------
void RakNet::Write(BitStream& kOut, const VeString& kStr)
{
	Write(kOut, kStr, kStr.Length());
}
//--------------------------------------------------------------------------
bool RakNet::Read(BitStream& kIn, VeChar8* pcStr)
{
	VeUInt8 u8Len;
	bool bRes = kIn.Read(u8Len);
	if(bRes)
	{
		if(u8Len)
		{
			bRes = kIn.ReadAlignedBytes((VeUInt8*)pcStr, u8Len);
		}
		if(bRes)
		{
			pcStr[u8Len] = 0;
		}
	}
	return bRes;
}
//--------------------------------------------------------------------------
bool RakNet::Read(BitStream& kIn, VeString& kStr)
{
	VeUInt8 u8Len;
	bool bRes = kIn.Read(u8Len);
	if(bRes)
	{
		VeByte abyBuffer[256];
		if(u8Len)
		{
			bRes = kIn.ReadAlignedBytes(abyBuffer, u8Len);
		}
		if(bRes)
		{
			abyBuffer[u8Len] = 0;
			kStr = (const VeChar8*)abyBuffer;
		}
		
	}
	return bRes;
}
//--------------------------------------------------------------------------
