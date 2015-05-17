////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeMain.cpp
//  Version:     v1.00
//  Created:     13/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"

//--------------------------------------------------------------------------
void VeStartEngine(VeStartParams& kParams)
{
	VE_NEW VeGlobalStringTable();
	VE_NEW VeAllocatorManager();
	VeDevice::CreateDevice(kParams);
	g_pDevice->Start();
	VeDevice::Destory();
	VeAllocatorManager::Destory();
	VeGlobalStringTable::Destory();
#	ifdef VE_MEM_DEBUG
	_VeMemoryExit();
#	endif
}
//--------------------------------------------------------------------------
void VeMainExport()
{
	VeLuaExport(VeDevice);
	VeLuaExportEnum(VeDevice::Type);
    VeLuaExportEnum(VeDevice::Language);
	VeLuaExport(VeRenderFrameManager);
	VeLuaExport(VeSceneRenderable);
	VeLuaExport(VeSceneRenderable2D);
	VeLuaExportEnum(VeSceneRenderable2D::BlendFunc);
	VeLuaExport(VeSprite2D);
	VeLuaExport(VeSquareFrame);
	VeLuaExport(VeSquare);
	VeLuaExport(VeSceneNode);
	VeLuaExport(VeSceneNode2D);
	VeLuaExport(VeSceneManager);
	VeLuaExport(VeTweenEasing);
	VeLuaExportEnum(VeTweenEasing::Type);
	VeLuaExport(VeAction);
	VeLuaExport(VeFiniteTimeAction);
	VeLuaExport(VeActionInterval);
	VeLuaExport(VeSequence);
	VeLuaExport(VeRepeat);
	VeLuaExport(VeRepeatForever);
	VeLuaExport(VeSpawn);
	VeLuaExport(VeRotateTo2D);
	VeLuaExport(VeRotateBy2D);
	VeLuaExport(VeMoveTo2D);
	VeLuaExport(VeMoveBy2D);
	VeLuaExport(VeScaleTo2D);
	VeLuaExport(VeScaleBy2D);
	VeLuaExport(VeMulColorTo2D);
	VeLuaExport(VeMulColorBy2D);
	VeLuaExport(VeAddColorTo2D);
	VeLuaExport(VeAddColorBy2D);
	VeLuaExport(VeDelayTime);
	VeLuaExport(VeActionInstant);
	VeLuaExport(VeChangeVisibleMask);
	VeLuaExport(VeToggleVisibility);
	VeLuaExport(VeUIManager);
	VeLuaExport(VeUIWidget);
	VeLuaExportEnum(VeUIWidget::EventType);
	VeLuaExportEnum(VeUIWidget::NodeType);
	VeLuaExport(VeUILayout);
	VeLuaExport(VeUISquare);
	VeLuaExport(VeUIImage);
	VeLuaExport(VeUIDragonBones);
	VeLuaExport(VeUIAlertFrame);
	VeLuaExport(VeUIAlertBarHoriz);
	VeLuaExport(VeUITextLabel);
	VeLuaExport(VeUIButton);
	VeLuaExport(VeUICheckButton);
	VeLuaExport(VeUIRadioArea);
	VeLuaExport(VeUIPageView);
	VeLuaExport(VeUICachedPanel);
	VeLuaExport(VeInputManager);
	VeLuaExport(VeDragonBonesEntity);
	VeLuaExport(VeSimpleText);
	VeLuaExportEnum(VeSimpleText::AlignType);
	VeLuaExport(VeMusicPlayer);
	VeLuaExport(VeAudioSystem);
}
//--------------------------------------------------------------------------
