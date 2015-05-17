////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeDirectory.cpp
//  Version:     v1.00
//  Created:     6/10/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
bool VeWildNameMatch(const VeChar8* pcName, const VeChar8* pcPattern)
{
	bool bRes;
	while(*pcName)
	{
		if(*pcPattern == '*')
		{
			while((*pcPattern == '*') || (*pcPattern == '?')) ++pcPattern;
			if (!*pcPattern) return true;
			while (*pcName && (*pcName != *pcPattern)) ++pcName; 
			if(!*pcName) return false;
			bRes = VeWildNameMatch(pcName, pcPattern);
			while((!bRes) && (*(pcName + 1)) && (*pcName == *pcPattern))
				bRes = VeWildNameMatch(++pcName, pcPattern);
			return bRes;
		}
		else
		{
			if((*pcName == *pcPattern) || ('?' == *pcPattern))
			{ 
				return VeWildNameMatch(++pcName, ++pcPattern);
			}
			else
			{
				return false;
			}
		}
	}
	return (*pcPattern) ? (*pcPattern == '*') && (*(pcPattern + 1) == 0) : true;
}
//--------------------------------------------------------------------------
VeDirectory::VeDirectory(const VeChar8* pcName) : m_kName(pcName)
{
	VE_ASSERT(pcName[VeStrlen(pcName) - 1] != '/');
}
//--------------------------------------------------------------------------
VeDirectory::~VeDirectory()
{

}
//--------------------------------------------------------------------------
const VeChar8* VeDirectory::GetName()
{
	return m_kName;
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeDirectory)
{

}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeDirectory, Type);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeDirectory, Type)
{
	VeLuaClassEnumBase(VeDirectory, Type);
	VeLuaClassEnumSlot(VeDirectory, Type, TYPE_FILE, "file");
	VeLuaClassEnumSlot(VeDirectory, Type, TYPE_ZIP, "zip");
	VeLuaClassEnumSlot(VeDirectory, Type, TYPE_ASSET, "asset");
	VeLuaClassEnumSlot(VeDirectory, Type, TYPE_URL, "url");
}
//--------------------------------------------------------------------------
