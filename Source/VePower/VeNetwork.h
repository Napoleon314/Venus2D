////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeNetwork.h
//  Version:     v1.00
//  Created:     24/10/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace RakNet
{
	class BitStream;

	VE_POWER_API void Write(BitStream& kOut, const VeChar8* pcStr, VeUInt32 u32Len);

	VE_POWER_API void Write(BitStream& kOut, const VeString& kStr);

	VE_POWER_API bool Read(BitStream& kIn, VeChar8* pcStr);

	VE_POWER_API bool Read(BitStream& kIn, VeString& kStr);

}
