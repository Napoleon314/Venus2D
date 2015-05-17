////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIText.cpp
//  Version:     v1.00
//  Created:     18/7/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"

//--------------------------------------------------------------------------
VeImplementRTTI(VeSimpleText, VeSceneNode2D);
//--------------------------------------------------------------------------
VeSimpleText::VeSimpleText(const VeChar8* pcFont) : m_f32LineWidth(0)
	, m_f32LineSpace(0), m_eType(CENTER_CENTER), m_f32Bias(0)
	, m_f32Offset(0), m_f32ShadowBias(0), m_bDirty(false)
{
	m_kColor = VeColor::WHITE;
	m_spFont = VeLoadFontSync(pcFont, g_pResourceManager->GetDefaultGroupName());
	m_spNode = VE_NEW VeSceneNode2D;
	AttachChild(m_spNode);
}
//--------------------------------------------------------------------------
VeSimpleText::VeSimpleText(const VeFontPtr& spFont) : m_f32LineWidth(0)
	, m_f32LineSpace(0), m_eType(CENTER_CENTER), m_f32Bias(0)
	, m_f32Offset(0), m_f32ShadowBias(0), m_bDirty(false)
{
	m_kColor = VeColor::WHITE;
	m_spFont = spFont;
	m_spNode = VE_NEW VeSceneNode2D;
	AttachChild(m_spNode);
}
//--------------------------------------------------------------------------
const VeFontPtr& VeSimpleText::GetFont()
{
	return m_spFont;
}
//--------------------------------------------------------------------------
VeFloat32 VeSimpleText::GetOffset()
{
	return m_f32Offset;
}
//--------------------------------------------------------------------------
const VeVector2D& VeSimpleText::GetSize()
{
	UpdateText();
	return m_kSize;
}
//--------------------------------------------------------------------------
void VeSimpleText::SetText(const VeChar8* pcText)
{
	VE_ASSERT(pcText);
	if(m_kText != pcText)
	{
		m_kText = pcText;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeSimpleText::GetText()
{
	return m_kText;
}
//--------------------------------------------------------------------------
void VeSimpleText::SetLine(VeFloat32 f32Width, VeFloat32 f32Space)
{
	if(m_f32LineWidth != f32Width)
	{
		m_f32LineWidth = f32Width;
		m_bDirty = true;
	}
	if(m_f32LineSpace != f32Space)
	{
		m_f32LineSpace = f32Space;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
void VeSimpleText::SetType(AlignType eType, const VeColor& kColor,
	VeFloat32 f32Bias, VeFloat32 f32Offset)
{
	if(m_eType != eType)
	{
		m_eType = eType;
		m_bDirty = true;
	}
	if(m_kColor != kColor)
	{
		m_kColor = kColor;
		m_bDirty = true;
	}
	if(m_f32Bias != f32Bias)
	{
		m_f32Bias = f32Bias;
		m_bDirty = true;
	}
	if(m_f32Offset != f32Offset)
	{
		m_f32Offset = f32Offset;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
void VeSimpleText::SetShadowType(const VeColor& kColor, VeFloat32 f32Bias,
	const VeVector2D& kOffset)
{
	if(m_kShadowColor != kColor)
	{
		m_kShadowColor = kColor;
		m_bDirty = true;
	}
	if(m_f32ShadowBias != f32Bias)
	{
		m_f32ShadowBias = f32Bias;
		m_bDirty = true;
	}
	if(m_kShadowOffset != kOffset)
	{
		m_kShadowOffset = kOffset;
		m_bDirty = true;
	}
}
//--------------------------------------------------------------------------
void VeSimpleText::Visit(VeRenderQueue& kQueue)
{
	UpdateText();
	VeSceneNode2D::Visit(kQueue);
}
//--------------------------------------------------------------------------
void VeSimpleText::UpdateText()
{
	if(m_bDirty)
	{
		m_kSize = VeVector2D::ZERO;
		m_spNode->DetachAllChildren();
		VeVector<VeChar16> kCharList;
		const VeChar8* pcTemp = m_kText;
		while(pcTemp)
		{
			VeInt32 i32Char;
			VeInt32 i32Count = VeUTF8ToUnicode(pcTemp, i32Char);
			if(i32Count > 0 && i32Count < 4)
			{
				kCharList.PushBack(i32Char);
			}
			else if(!i32Count)
			{
				break;
			}
			pcTemp += i32Count;
		}
		VeVector2D kPos;
		for(VeUInt32 i(0); i < kCharList.Size(); ++i)
		{
			if(kCharList[i] == L'\n')
			{
				kPos.x = 0;
				kPos.y += m_spFont->m_u32CharSize + m_f32LineSpace;
				continue;
			}
			VeSceneNode2DPtr spNode = VE_NEW VeSceneNode2D;
			VeSingleCharPtr spChar = VE_NEW VeSingleChar;
			spChar->SetChar(kCharList[i], m_spFont);
			spChar->SetBias(m_f32Bias);
			if(m_f32LineWidth && (kPos.x + spChar->GetPixelWidth()) > m_f32LineWidth)
			{
				kPos.x = 0;
				kPos.y += m_spFont->m_u32CharSize + m_f32LineSpace;
			}
			spNode->SetPosition(kPos);
			spNode->SetMulColor(m_kColor);
			spNode->AttachRenderable(spChar);
			m_spNode->AttachChild(spNode);

			if(m_kShadowColor.a)
			{
				VeSceneNode2DPtr spNodeShadow = VE_NEW VeSceneNode2D;
				VeSingleCharPtr spCharShadow = VE_NEW VeSingleChar;
				spCharShadow->SetChar(kCharList[i], m_spFont);
				spCharShadow->SetBias(m_f32ShadowBias);
				spNodeShadow->SetPosition(kPos + m_kShadowOffset);
				spNodeShadow->SetMulColor(m_kShadowColor);
				spNodeShadow->AttachRenderable(spCharShadow);
				spNodeShadow->SetZOrder(-1.0f);
				m_spNode->AttachChild(spNodeShadow);
			}

			kPos.x += spChar->GetPixelWidth() + m_f32Offset;
		}
		m_kSize.x = m_kSize.y ? m_f32LineWidth : kPos.x - m_f32Offset;
		m_kSize.y = VeFloat32(kPos.y + m_spFont->m_u32CharSize);

		VeVector2D kNodeOffset;
		if((m_eType & 0xf) == 2)
		{
			kNodeOffset.y = -m_kSize.y * 0.5f;
		}
		else if((m_eType & 0xf) == 3)
		{
			kNodeOffset.y = -m_kSize.y;
		}
		if((m_eType & 0xf0) == 0x20)
		{
			kNodeOffset.x = -m_kSize.x * 0.5f;
		}
		else if((m_eType & 0xf0) == 0x30)
		{
			kNodeOffset.x = -m_kSize.x;
		}
		m_spNode->SetPosition(kNodeOffset);

		m_bDirty = false;
	}
}
//--------------------------------------------------------------------------
VeImplementLuaExport(VeSimpleText)
{
	Module() [
		Class< VeSimpleText, Base<VeSceneNode2D> >().
			Def(ConstructorNew<const VeChar8*>()).
			Def("SetText", &VeSimpleText::SetText).
			Def("GetText", &VeSimpleText::GetText).
			Def("SetType", &VeSimpleText::SetType).
			Def("SetShadowType", &VeSimpleText::SetShadowType)
	];
}
//--------------------------------------------------------------------------
namespace VeLuaBind
{
	VeLuaClassEnumFuncImpl(VeSimpleText, AlignType);
}
//--------------------------------------------------------------------------
VeLuaClassEnumImpl(VeSimpleText, AlignType)
{
	VeLuaClassEnumBase(VeSimpleText, AlignType);
	VeLuaClassEnumSlot(VeSimpleText, AlignType, LEFT_TOP, "lt");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, LEFT_CENTER, "lc");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, LEFT_BOTTOM, "lb");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, CENTER_TOP, "ct");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, CENTER_CENTER, "cc");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, CENTER_BOTTOM, "cb");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, RIGHT_TOP, "rt");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, RIGHT_CENTER, "rc");
	VeLuaClassEnumSlot(VeSimpleText, AlignType, RIGHT_BOTTOM, "rb");
}
//--------------------------------------------------------------------------
