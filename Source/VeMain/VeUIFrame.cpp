////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIFrame.cpp
//  Version:     v1.00
//  Created:     7/7/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#ifdef VE_NO_INLINE
#	include "VeUIFrame.inl"
#endif

//--------------------------------------------------------------------------
VeImplementRTTI(VeUIFrame, VeSceneNode2D);
//--------------------------------------------------------------------------
VeUIFrame::VeUIFrame() : m_f32Width(0), m_f32Height(0)
{
	for(VeUInt32 i(0); i < POS_NUM; ++i)
	{
		m_akPos[i].m_spNode = VE_NEW VeSceneNode2D;
		m_akPos[i].m_spSprite = VE_NEW VeSprite2D;
		m_akPos[i].m_spNode->AttachRenderable(m_akPos[i].m_spSprite);
		AttachChild(m_akPos[i].m_spNode);
	}
}
//--------------------------------------------------------------------------
VeUIFrame::~VeUIFrame()
{

}
//--------------------------------------------------------------------------
void VeUIFrame::SetFrame(const VeChar8* apcSlot[])
{
	m_akPos[POS_CENTER_QUAD].m_spSprite->SetFrameName(apcSlot[POS_CENTER_QUAD]);
	m_akPos[POS_CENTER_QUAD].m_spSprite->SetAnchor(0.5f, 0.5f, 0.0f, 0.0f, false);

	if(VeStricmp(apcSlot[POS_LEFT_TOP], "rt") == 0)
	{
		m_akPos[POS_LEFT_TOP].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_TOP]);
		m_akPos[POS_LEFT_TOP].m_spSprite->SetAnchor(0.0f, 1.0f);
		m_akPos[POS_LEFT_TOP].m_spNode->SetScale(-1.0f, 1.0f);
	}
	else if(VeStricmp(apcSlot[POS_LEFT_TOP], "lb") == 0)
	{
		m_akPos[POS_LEFT_TOP].m_spSprite->SetFrameName(apcSlot[POS_LEFT_BOTTOM]);
		m_akPos[POS_LEFT_TOP].m_spSprite->SetAnchor(1.0f, 0.0f);
		m_akPos[POS_LEFT_TOP].m_spNode->SetScale(1.0f, -1.0f);
	}
	else if(VeStricmp(apcSlot[POS_LEFT_TOP], "rb") == 0)
	{
		m_akPos[POS_LEFT_TOP].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_BOTTOM]);
		m_akPos[POS_LEFT_TOP].m_spSprite->SetAnchor(0.0f, 0.0f);
		m_akPos[POS_LEFT_TOP].m_spNode->SetScale(-1.0f, -1.0f);
	}
	else
	{
		m_akPos[POS_LEFT_TOP].m_spSprite->SetFrameName(apcSlot[POS_LEFT_TOP]);
		m_akPos[POS_LEFT_TOP].m_spSprite->SetAnchor(1.0f, 1.0f);
		m_akPos[POS_LEFT_TOP].m_spNode->SetScale(1.0f, 1.0f);
	}

	if(VeStricmp(apcSlot[POS_RIGHT_TOP], "lt") == 0)
	{
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetFrameName(apcSlot[POS_LEFT_TOP]);
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetAnchor(1.0f, 1.0f);
		m_akPos[POS_RIGHT_TOP].m_spNode->SetScale(-1.0f, 1.0f);
	}
	else if(VeStricmp(apcSlot[POS_RIGHT_TOP], "rb") == 0)
	{
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_BOTTOM]);
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetAnchor(0.0f, 0.0f);
		m_akPos[POS_RIGHT_TOP].m_spNode->SetScale(1.0f, -1.0f);
	}
	else if(VeStricmp(apcSlot[POS_RIGHT_TOP], "lb") == 0)
	{
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetFrameName(apcSlot[POS_LEFT_BOTTOM]);
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetAnchor(1.0f, 0.0f);
		m_akPos[POS_RIGHT_TOP].m_spNode->SetScale(-1.0f, -1.0f);
	}
	else
	{
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_TOP]);
		m_akPos[POS_RIGHT_TOP].m_spSprite->SetAnchor(0.0f, 1.0f);
		m_akPos[POS_RIGHT_TOP].m_spNode->SetScale(1.0f, 1.0f);
	}

	if(VeStricmp(apcSlot[POS_LEFT_BOTTOM], "lt") == 0)
	{
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_LEFT_TOP]);
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetAnchor(1.0f, 1.0f);
		m_akPos[POS_LEFT_BOTTOM].m_spNode->SetScale(1.0f, -1.0f);
	}
	else if(VeStricmp(apcSlot[POS_LEFT_BOTTOM], "rb") == 0)
	{
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_BOTTOM]);
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetAnchor(1.0f, 0.0f);
		m_akPos[POS_LEFT_BOTTOM].m_spNode->SetScale(-1.0f, 1.0f);
	}
	else if(VeStricmp(apcSlot[POS_LEFT_BOTTOM], "rt") == 0)
	{
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_TOP]);
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetAnchor(0.0f, 1.0f);
		m_akPos[POS_LEFT_BOTTOM].m_spNode->SetScale(-1.0f, -1.0f);
	}
	else
	{
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_LEFT_BOTTOM]);
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->SetAnchor(1.0f, 0.0f);
		m_akPos[POS_LEFT_BOTTOM].m_spNode->SetScale(1.0f, 1.0f);
	}

	if(VeStricmp(apcSlot[POS_RIGHT_BOTTOM], "lb") == 0)
	{
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_LEFT_BOTTOM]);
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetAnchor(1.0f, 0.0f);
		m_akPos[POS_RIGHT_BOTTOM].m_spNode->SetScale(-1.0f, 1.0f);
	}
	else if(VeStricmp(apcSlot[POS_RIGHT_BOTTOM], "rt") == 0)
	{
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_TOP]);
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetAnchor(0.0f, 1.0f);
		m_akPos[POS_RIGHT_BOTTOM].m_spNode->SetScale(1.0f, -1.0f);
	}
	else if(VeStricmp(apcSlot[POS_RIGHT_BOTTOM], "lt") == 0)
	{
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_LEFT_TOP]);
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetAnchor(1.0f, 1.0f);
		m_akPos[POS_RIGHT_BOTTOM].m_spNode->SetScale(-1.0f, -1.0f);
	}
	else
	{
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_BOTTOM]);
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->SetAnchor(0.0f, 0.0f);
		m_akPos[POS_RIGHT_BOTTOM].m_spNode->SetScale(1.0f, 1.0f);
	}

	if(VeStricmp(apcSlot[POS_TOP_BAR], "b") == 0)
	{
		m_akPos[POS_TOP_BAR].m_spSprite->SetFrameName(apcSlot[POS_BOTTOM_BAR]);
		m_akPos[POS_TOP_BAR].m_spSprite->SetAnchor(0.5f, 0.0f, 0.0f, 0.0f, false);
		m_akPos[POS_TOP_BAR].m_spNode->SetScaleY(-1.0f);
	}
	else
	{
		m_akPos[POS_TOP_BAR].m_spSprite->SetFrameName(apcSlot[POS_TOP_BAR]);
		m_akPos[POS_TOP_BAR].m_spSprite->SetAnchor(0.5f, 1.0f, 0.0f, 0.0f, false);
		m_akPos[POS_TOP_BAR].m_spNode->SetScaleY(1.0f);
	}
	
	if(VeStricmp(apcSlot[POS_BOTTOM_BAR], "t") == 0)
	{
		m_akPos[POS_BOTTOM_BAR].m_spSprite->SetFrameName(apcSlot[POS_TOP_BAR]);
		m_akPos[POS_BOTTOM_BAR].m_spSprite->SetAnchor(0.5f, 1.0f, 0.0f, 0.0f, false);
		m_akPos[POS_BOTTOM_BAR].m_spNode->SetScaleY(-1.0f);
	}
	else
	{
		m_akPos[POS_BOTTOM_BAR].m_spSprite->SetFrameName(apcSlot[POS_BOTTOM_BAR]);
		m_akPos[POS_BOTTOM_BAR].m_spSprite->SetAnchor(0.5f, 0.0f, 0.0f, 0.0f, false);
		m_akPos[POS_BOTTOM_BAR].m_spNode->SetScaleY(1.0f);
	}

	if(VeStricmp(apcSlot[POS_LEFT_BAR], "r") == 0)
	{
		m_akPos[POS_LEFT_BAR].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_BAR]);
		m_akPos[POS_LEFT_BAR].m_spSprite->SetAnchor(0.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_LEFT_BAR].m_spNode->SetScaleX(-1.0f);
	}
	else
	{
		m_akPos[POS_LEFT_BAR].m_spSprite->SetFrameName(apcSlot[POS_LEFT_BAR]);
		m_akPos[POS_LEFT_BAR].m_spSprite->SetAnchor(1.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_LEFT_BAR].m_spNode->SetScaleX(1.0f);
	}

	if(VeStricmp(apcSlot[POS_RIGHT_BAR], "l") == 0)
	{
		m_akPos[POS_RIGHT_BAR].m_spSprite->SetFrameName(apcSlot[POS_LEFT_BAR]);
		m_akPos[POS_RIGHT_BAR].m_spSprite->SetAnchor(1.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_RIGHT_BAR].m_spNode->SetScaleX(-1.0f);
	}
	else
	{
		m_akPos[POS_RIGHT_BAR].m_spSprite->SetFrameName(apcSlot[POS_RIGHT_BAR]);
		m_akPos[POS_RIGHT_BAR].m_spSprite->SetAnchor(0.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_RIGHT_BAR].m_spNode->SetScaleX(1.0f);
	}
}
//--------------------------------------------------------------------------
void VeUIFrame::UpdateSize()
{
	VeFloat32 f32LeftEdge = (VeFloat32)VE_MAX(m_akPos[POS_LEFT_TOP].m_spSprite->GetWidth(),
		m_akPos[POS_LEFT_BOTTOM].m_spSprite->GetWidth());
	VeFloat32 f32RightEdge = (VeFloat32)VE_MAX(m_akPos[POS_RIGHT_TOP].m_spSprite->GetWidth(),
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->GetWidth());
	VeFloat32 f32TopEdge = (VeFloat32)VE_MAX(m_akPos[POS_LEFT_TOP].m_spSprite->GetHeight(),
		m_akPos[POS_RIGHT_TOP].m_spSprite->GetHeight());
	VeFloat32 f32BottomEdge = (VeFloat32)VE_MAX(m_akPos[POS_LEFT_BOTTOM].m_spSprite->GetHeight(),
		m_akPos[POS_RIGHT_BOTTOM].m_spSprite->GetHeight());

	VeFloat32 f32MinW = f32LeftEdge + f32RightEdge;
	VeFloat32 f32MinH = f32TopEdge + f32BottomEdge;

	m_f32Width = VE_MAX(m_f32Width, f32MinW);
	m_f32Height = VE_MAX(m_f32Height, f32MinH);

	VeFloat32 f32CenterW = m_f32Width - f32MinW;
	VeFloat32 f32CenterH = m_f32Height - f32MinH;

	m_akPos[POS_CENTER_QUAD].m_spNode->SetScale(f32CenterW, f32CenterH);
	
	m_akPos[POS_LEFT_TOP].m_spNode->SetPosition(-f32CenterW * 0.5f, -f32CenterH * 0.5f);
	m_akPos[POS_RIGHT_TOP].m_spNode->SetPosition(f32CenterW * 0.5f, -f32CenterH * 0.5f);
	m_akPos[POS_LEFT_BOTTOM].m_spNode->SetPosition(-f32CenterW * 0.5f, f32CenterH * 0.5f);
	m_akPos[POS_RIGHT_BOTTOM].m_spNode->SetPosition(f32CenterW * 0.5f, f32CenterH * 0.5f);

	m_akPos[POS_TOP_BAR].m_spNode->SetPosition(0.0f, -f32CenterH * 0.5f);
	m_akPos[POS_TOP_BAR].m_spNode->SetScaleX(f32CenterW);

	m_akPos[POS_BOTTOM_BAR].m_spNode->SetPosition(0.0f, f32CenterH * 0.5f);
	m_akPos[POS_BOTTOM_BAR].m_spNode->SetScaleX(f32CenterW);

	m_akPos[POS_LEFT_BAR].m_spNode->SetPosition(-f32CenterW * 0.5f, 0.0f);
	m_akPos[POS_LEFT_BAR].m_spNode->SetScaleY(f32CenterH);

	m_akPos[POS_RIGHT_BAR].m_spNode->SetPosition(f32CenterW * 0.5f, 0.0f);
	m_akPos[POS_RIGHT_BAR].m_spNode->SetScaleY(f32CenterH);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIFrame)
{
	Module() [
		Class<VeUIFrame>()
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIBarHoriz, VeSceneNode2D);
//--------------------------------------------------------------------------
VeUIBarHoriz::VeUIBarHoriz()
{
	for(VeUInt32 i(0); i < POS_NUM; ++i)
	{
		m_akPos[i].m_spNode = VE_NEW VeSceneNode2D;
		m_akPos[i].m_spSprite = VE_NEW VeSprite2D;
		m_akPos[i].m_spNode->AttachRenderable(m_akPos[i].m_spSprite);
		AttachChild(m_akPos[i].m_spNode);
	}
}
//--------------------------------------------------------------------------
VeUIBarHoriz::~VeUIBarHoriz()
{

}
//--------------------------------------------------------------------------
void VeUIBarHoriz::SetFrame(const VeChar8* apcSlot[])
{
	m_akPos[POS_CENTER].m_spSprite->SetFrameName(apcSlot[POS_CENTER]);
	m_akPos[POS_CENTER].m_spSprite->SetAnchor(0.5f, 0.5f, 0.0f, 0.0f, false);

	if(VeStricmp(apcSlot[POS_LEFT], "r") == 0)
	{
		m_akPos[POS_LEFT].m_spSprite->SetFrameName(apcSlot[POS_RIGHT]);
		m_akPos[POS_LEFT].m_spSprite->SetAnchor(0.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_LEFT].m_spNode->SetScaleX(-1.0f);
	}
	else
	{
		m_akPos[POS_LEFT].m_spSprite->SetFrameName(apcSlot[POS_LEFT]);
		m_akPos[POS_LEFT].m_spSprite->SetAnchor(1.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_LEFT].m_spNode->SetScaleX(1.0f);
	}

	if(VeStricmp(apcSlot[POS_RIGHT], "l") == 0)
	{
		m_akPos[POS_RIGHT].m_spSprite->SetFrameName(apcSlot[POS_LEFT]);
		m_akPos[POS_RIGHT].m_spSprite->SetAnchor(1.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_RIGHT].m_spNode->SetScaleX(-1.0f);
	}
	else
	{
		m_akPos[POS_RIGHT].m_spSprite->SetFrameName(apcSlot[POS_RIGHT]);
		m_akPos[POS_RIGHT].m_spSprite->SetAnchor(0.0f, 0.5f, 0.0f, 0.0f, false);
		m_akPos[POS_RIGHT].m_spNode->SetScaleX(1.0f);
	}
}
//--------------------------------------------------------------------------
void VeUIBarHoriz::UpdateSize()
{
	VeFloat32 f32LeftEdge = (VeFloat32)m_akPos[POS_LEFT].m_spSprite->GetWidth();
	VeFloat32 f32RightEdge = (VeFloat32)m_akPos[POS_RIGHT].m_spSprite->GetWidth();

	VeFloat32 f32MinW = f32LeftEdge + f32RightEdge;

	m_f32Width = VE_MAX(m_f32Width, f32MinW);

	VeFloat32 f32CenterW = m_f32Width - f32MinW;

	m_akPos[POS_CENTER].m_spNode->SetScaleX(f32CenterW);
	m_akPos[POS_LEFT].m_spNode->SetPosition(-f32CenterW * 0.5f, 0.0f);
	m_akPos[POS_RIGHT].m_spNode->SetPosition(f32CenterW * 0.5f, 0.0f);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIBarHoriz)
{
	Module() [
		Class<VeUIBarHoriz>()
	];
}
//--------------------------------------------------------------------------
VeImplementRTTI(VeUIBarVert, VeSceneNode2D);
//--------------------------------------------------------------------------
VeUIBarVert::VeUIBarVert()
{
	for(VeUInt32 i(0); i < POS_NUM; ++i)
	{
		m_akPos[i].m_spNode = VE_NEW VeSceneNode2D;
		m_akPos[i].m_spSprite = VE_NEW VeSprite2D;
		m_akPos[i].m_spNode->AttachRenderable(m_akPos[i].m_spSprite);
		AttachChild(m_akPos[i].m_spNode);
	}
}
//--------------------------------------------------------------------------
VeUIBarVert::~VeUIBarVert()
{

}
//--------------------------------------------------------------------------
void VeUIBarVert::SetFrame(const VeChar8* apcSlot[])
{
	m_akPos[POS_CENTER].m_spSprite->SetFrameName(apcSlot[POS_CENTER]);
	m_akPos[POS_CENTER].m_spSprite->SetAnchor(0.5f, 0.5f, 0.0f, 0.0f, false);

	if(VeStricmp(apcSlot[POS_TOP], "b") == 0)
	{
		m_akPos[POS_TOP].m_spSprite->SetFrameName(apcSlot[POS_BOTTOM]);
		m_akPos[POS_TOP].m_spSprite->SetAnchor(0.5f, 0.0f, 0.0f, 0.0f, false);
		m_akPos[POS_TOP].m_spNode->SetScaleY(-1.0f);
	}
	else
	{
		m_akPos[POS_TOP].m_spSprite->SetFrameName(apcSlot[POS_TOP]);
		m_akPos[POS_TOP].m_spSprite->SetAnchor(0.5f, 1.0f, 0.0f, 0.0f, false);
		m_akPos[POS_TOP].m_spNode->SetScaleY(1.0f);
	}

	if(VeStricmp(apcSlot[POS_BOTTOM], "t") == 0)
	{
		m_akPos[POS_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_TOP]);
		m_akPos[POS_BOTTOM].m_spSprite->SetAnchor(0.5f, 1.0f, 0.0f, 0.0f, false);
		m_akPos[POS_BOTTOM].m_spNode->SetScaleY(-1.0f);
	}
	else
	{
		m_akPos[POS_BOTTOM].m_spSprite->SetFrameName(apcSlot[POS_BOTTOM]);
		m_akPos[POS_BOTTOM].m_spSprite->SetAnchor(0.5f, 0.0f, 0.0f, 0.0f, false);
		m_akPos[POS_BOTTOM].m_spNode->SetScaleY(1.0f);
	}
}
//--------------------------------------------------------------------------
void VeUIBarVert::UpdateSize()
{
	VeFloat32 f32TopEdge = (VeFloat32)m_akPos[POS_TOP].m_spSprite->GetWidth();
	VeFloat32 f32BottomEdge = (VeFloat32)m_akPos[POS_BOTTOM].m_spSprite->GetWidth();

	VeFloat32 f32MinH = f32TopEdge + f32BottomEdge;

	m_f32Height = VE_MAX(m_f32Height, f32MinH);

	VeFloat32 f32CenterH = m_f32Height - f32MinH;

	m_akPos[POS_CENTER].m_spNode->SetScaleY(f32CenterH);
	m_akPos[POS_TOP].m_spNode->SetPosition(0.0f, -f32CenterH * 0.5f);
	m_akPos[POS_BOTTOM].m_spNode->SetPosition(0.0f, f32CenterH * 0.5f);
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeUIBarVert)
{
	Module() [
		Class<VeUIBarVert>()
	];
}
//--------------------------------------------------------------------------
void VeUIBarVert::SetColor(const VeColor& kColor)
{
	m_akPos[POS_TOP].m_spNode->SetMulColor(kColor);
	m_akPos[POS_BOTTOM].m_spNode->SetMulColor(kColor);
	m_akPos[POS_CENTER].m_spNode->SetMulColor(kColor);
}
//--------------------------------------------------------------------------
