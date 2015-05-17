////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUIScrollView.h
//  Version:     v1.00
//  Created:     14/1/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeUIScrollView : public VeUIWidget
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUIScrollView);
public:
	VeUIScrollView();

	virtual ~VeUIScrollView();

	void SetTop();

	virtual void From(VeBinaryIStream& kIn);

	virtual void To(VeBinaryOStream& kOut) const;

	virtual void From(VeXMLElement* pkElement);

	virtual bool OnPress(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnHoldDragMove(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnRelease(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void OnCancel(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual void Visit(VeRenderQueue& kQueue);

	static VeUIWidgetPtr Create();

protected:
	void UpdateInnerBounding();

	void UpdateInnerVisible();

	void UpdateScrollBar();

	void Reset();

	void OnStart(const VeVector2D& kPos);

	void OnEnd();

	void OnBarShow();

	void OnBarHide();

	VeFloat32 m_f32Threshold;
	VeFloat32 m_f32Rate;
	VeFloat32 m_f32VelMax;
	VeFloat32 m_f32Friction;
	VeFloat32 m_f32Damping;
	VeSceneNode2DPtr m_spInner;
	VeUIBarVertPtr m_spBar;
	VeUIWidgetPtr m_spHoldWidget;
	VeFloat32 m_f32MoveBottom;
	VeFloat32 m_f32MoveTop;
	VeFloat32 m_f32ScrollBarLen;
	VeVector2D m_kStart;
	VeVector2D m_kPre;
	VeFloat32 m_f32Velocity;
	VeFloat32 m_f32InnerNodeStart;
	VeFloat32 m_f32RollBackTime;
	VeFloat32 m_f32RollBackPosY;
	bool m_bTouched;
	bool m_bScroll;
	bool m_bRollBack;

};
