////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIText.h
//  Version:     v1.00
//  Created:     18/7/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeSimpleText : public VeSceneNode2D
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeSimpleText);
public:
	enum AlignType
	{
		LEFT_TOP		= 0x11,
		LEFT_CENTER		= 0x12,
		LEFT_BOTTOM		= 0x13,

		CENTER_TOP		= 0x21,
		CENTER_CENTER	= 0x22,
		CENTER_BOTTOM	= 0x23,

		RIGHT_TOP		= 0x31,
		RIGHT_CENTER	= 0x32,
		RIGHT_BOTTOM	= 0x33,
	};
	VeLuaClassEnumDef(AlignType);

	VeSimpleText(const VeChar8* pcFont);

	VeSimpleText(const VeFontPtr& spFont);

	const VeFontPtr& GetFont();

	VeFloat32 GetOffset();

	const VeVector2D& GetSize();

	void SetText(const VeChar8* pcText);

	const VeChar8* GetText();

	void SetLine(VeFloat32 f32Width, VeFloat32 f32Space);

	void SetType(AlignType eType, const VeColor& kColor, VeFloat32 f32Bias, VeFloat32 f32Offset);

	void SetShadowType(const VeColor& kColor, VeFloat32 f32Bias, const VeVector2D& kOffset);

	virtual void Visit(VeRenderQueue& kQueue);

protected:
	void UpdateText();

	VeFontPtr m_spFont;
	VeString m_kText;
	VeFloat32 m_f32LineWidth;
	VeFloat32 m_f32LineSpace;
	AlignType m_eType;
	VeColor m_kColor;
	VeFloat32 m_f32Bias;
	VeFloat32 m_f32Offset;
	VeColor m_kShadowColor;
	VeFloat32 m_f32ShadowBias;
	VeVector2D m_kShadowOffset;
	VeSceneNode2DPtr m_spNode;
	VeVector2D m_kSize;
	bool m_bDirty;

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_MAIN_API, VeSimpleText, AlignType);
}

VeSmartPointer(VeSimpleText);
