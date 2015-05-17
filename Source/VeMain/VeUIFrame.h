////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIFrame.h
//  Version:     v1.00
//  Created:     7/7/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeUIFrame : public VeSceneNode2D
{
	VeDeclareRTTI;
	VeDeclareLuaExport(VeUIFrame);
public:
	enum PosType
	{
		POS_LEFT_TOP,
		POS_RIGHT_TOP,
		POS_LEFT_BOTTOM,
		POS_RIGHT_BOTTOM,
		POS_TOP_BAR,
		POS_LEFT_BAR,
		POS_RIGHT_BAR,
		POS_BOTTOM_BAR,
		POS_CENTER_QUAD,
		POS_NUM
	};

	VeUIFrame();

	virtual ~VeUIFrame();

	VE_INLINE VeFloat32 GetWidth();

	VE_INLINE VeFloat32 GetHeight();

	VE_INLINE void SetSize(VeFloat32 f32Width, VeFloat32 f32Height);

	void SetFrame(const VeChar8* apcSlot[]);

protected:
	void UpdateSize();

	VeFloat32 m_f32Width;
	VeFloat32 m_f32Height;
	struct
	{
		VeSceneNode2DPtr m_spNode;
		VeSprite2DPtr m_spSprite;
	} m_akPos[POS_NUM];

};

VeSmartPointer(VeUIFrame);

class VE_MAIN_API VeUIBarHoriz : public VeSceneNode2D
{
	VeDeclareRTTI;
	VeDeclareLuaExport(VeUIBarHoriz);
public:
	enum PosType
	{
		POS_LEFT,
		POS_RIGHT,
		POS_CENTER,
		POS_NUM
	};

	VeUIBarHoriz();

	virtual ~VeUIBarHoriz();

	VE_INLINE VeFloat32 GetWidth();

	VE_INLINE void SetWidth(VeFloat32 f32Width);

	void SetFrame(const VeChar8* apcSlot[]);

protected:
	void UpdateSize();

	VeFloat32 m_f32Width;
	struct
	{
		VeSceneNode2DPtr m_spNode;
		VeSprite2DPtr m_spSprite;
	} m_akPos[POS_NUM];

};

VeSmartPointer(VeUIBarHoriz);

class VE_MAIN_API VeUIBarVert : public VeSceneNode2D
{
	VeDeclareRTTI;
	VeDeclareLuaExport(VeUIBarVert);
public:
	enum PosType
	{
		POS_TOP,
		POS_BOTTOM,
		POS_CENTER,
		POS_NUM
	};

	VeUIBarVert();

	virtual ~VeUIBarVert();

	VE_INLINE VeFloat32 GetWidth();

	VE_INLINE VeFloat32 GetHeight();

	VE_INLINE void SetHeight(VeFloat32 f32Height);

	void SetFrame(const VeChar8* apcSlot[]);

	void SetColor(const VeColor& kColor);

protected:
	void UpdateSize();

	VeFloat32 m_f32Height;
	struct
	{
		VeSceneNode2DPtr m_spNode;
		VeSprite2DPtr m_spSprite;
	} m_akPos[POS_NUM];

};

VeSmartPointer(VeUIBarVert);

#ifndef VE_NO_INLINE
#	include "VeUIFrame.inl"
#endif
