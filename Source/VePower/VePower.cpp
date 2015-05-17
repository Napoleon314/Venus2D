////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VePowerDefines.cpp
//  Version:     v1.00
//  Created:     5/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerPCH.h"

//--------------------------------------------------------------------------
#ifdef VE_DEBUG
//--------------------------------------------------------------------------
void VeAssert(const VeChar8* pcMessage, const VeChar8* pcSourceFile, VeInt32 iSourceLine, const VeChar8* pcFunction)
{
#   ifdef VE_PLATFORM_ANDROID
	__android_log_print(ANDROID_LOG_ERROR, "Assertion failed", "%s, file %s, line %d, function %s", pcMessage, pcSourceFile, iSourceLine, pcFunction);
	*(int*)0 = 0;
#   else
	printf("Assertion failed\n%s\nfile %s\nline %d\nfunction %s\n", pcMessage, pcSourceFile, iSourceLine, pcFunction);
	VeAbort();
#   endif
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
bool VeEnclosePoints(const VePoint* pkPoints, VeInt32 i32Count,
	const VeRect* pkClip, VeRect* pkResult)
{
	VeInt32 minx = 0;
	VeInt32 miny = 0;
	VeInt32 maxx = 0;
	VeInt32 maxy = 0;
	VeInt32 x, y, i;
	if(!pkPoints)
	{
		return false;
	}
	if(i32Count < 1)
	{
		return false;
	}
	if(pkClip)
	{
		bool added = false;
		const VeInt32 clip_minx = pkClip->x;
		const VeInt32 clip_miny = pkClip->y;
		const VeInt32 clip_maxx = pkClip->x+pkClip->w-1;
		const VeInt32 clip_maxy = pkClip->y+pkClip->h-1;
		if(VeRectEmpty(pkClip))
		{
			return false;
		}
		for(i = 0; i < i32Count; ++i)
		{
			x = pkPoints[i].x;
			y = pkPoints[i].y;
			if(x < clip_minx || x > clip_maxx || y < clip_miny || y > clip_maxy)
			{
				continue;
			}
			if(!added)
			{
				if(pkResult == NULL)
				{
					return true;
				}
				minx = maxx = x;
				miny = maxy = y;
				added = true;
				continue;
			}
			if(x < minx)
			{
				minx = x;
			}
			else if(x > maxx)
			{
				maxx = x;
			}
			if(y < miny)
			{
				miny = y;
			}
			else if(y > maxy)
			{
				maxy = y;
			}
		}
		if(!added)
		{
			return false;
		}
	}
	else
	{
		if(pkResult == NULL)
		{
			return true;
		}
		minx = maxx = pkPoints[0].x;
		miny = maxy = pkPoints[0].y;
		for (i = 1; i < i32Count; ++i)
		{
			x = pkPoints[i].x;
			y = pkPoints[i].y;

			if(x < minx)
			{
				minx = x;
			}
			else if (x > maxx)
			{
				maxx = x;
			}
			if(y < miny)
			{
				miny = y;
			}
			else if(y > maxy)
			{
				maxy = y;
			}
		}
	}
	if(pkResult)
	{
		pkResult->x = minx;
		pkResult->y = miny;
		pkResult->w = (maxx-minx)+1;
		pkResult->h = (maxy-miny)+1;
	}
	return true;
}
//--------------------------------------------------------------------------
void VeConsoleInit(bool bLuaDebug)
{
	VE_NEW VeGlobalStringTable();
	VE_NEW VeAllocatorManager();
	VePowerExport();
	VeLogger::SetLog(bLuaDebug
		? VeLogger::OUTPUT_LUASTUDIO
		: VeLogger::OUTPUT_CONSOLE);
	VE_NEW VeLua(bLuaDebug);
	VE_NEW VeTime();
	VE_NEW VeResourceManager();
	VE_NEW VeURL();
	VE_NEW VeServerManager();
	VE_NEW VeClientManager();
}
//--------------------------------------------------------------------------
void VeConsoleTerm()
{
	VeClientManager::Destory();
	VeServerManager::Destory();
	VeLua::Destory();
	VeURL::Destory();
	VeResourceManager::Destory();
	VeTime::Destory();
	VeLogger::SetLog(VeLogger::OUTPUT_MAX);
	VeAllocatorManager::Destory();
	VeGlobalStringTable::Destory();
#	ifdef VE_MEM_DEBUG
	_VeMemoryExit();
#	endif
}
//--------------------------------------------------------------------------
void VePowerExport()
{
	VeLuaExport(VeAngle);
	VeLuaExport(VeColor);
	VeLuaExport(VeVector2D);
	VeLuaExport(VeVector3D);
	VeLuaExport(VeVector4D);
	VeLuaExport(VeLine2D);
	VeLuaExport(VeQuaternion);
	VeLuaExport(VeMatrix);
	VeLuaExport(VeBoundingBox2D);
	VeLuaExport(VeTransform2D);
	VeLuaExport(VeTime);
	VeLuaExport(VeDirectory);
	VeLuaExportEnum(VeDirectory::Type);
	VeLuaExport(VeTextTable);
	VeLuaExportEnum(VeTextTable::Type);
	VeLuaExport(VeResourceManager);
	VeLuaExport(VeResource);
	VeLuaExportEnum(VeResource::Type);
	VeLuaExport(VeClient);
	VeLuaExportEnum(VeClient::DisconnectType);
	VeLuaExport(VeNetEntity);
	VeLuaExportEnum(VeNetEntity::Type);
	VeLuaExportEnum(VeNetEntity::Store);
	VeLuaExportEnum(VeNetEntity::ValueType);
	VeLuaExportEnum(VeNetEntity::ArrayFunc);
	VeLuaExport(VeLua);
	VeLuaExport(VeLuaSyncSignal);
	VeLuaExport(VeLuaSyncHolder);
}
//--------------------------------------------------------------------------
