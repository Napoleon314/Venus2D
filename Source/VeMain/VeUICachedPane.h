////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeUICachedPane.h
//  Version:     v1.00
//  Created:     5/12/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

class VE_MAIN_API VeUICachedPanel : public VeUIWidget, public VeRenderFrameManager::RenderTask
{
	VeDeclareRTTI;
	VeDeclareLuaRttiExport(VeUICachedPanel);
public:
	class RtRepainter : public VeUIWidget::Repainter
	{
	public:
		RtRepainter(VeUICachedPanel* pkParent);

		virtual void Notify();

		VeUICachedPanel* m_pkParent;

	};

	typedef VePointer<RtRepainter> RtRepainterPtr;

	VeUICachedPanel();

	virtual ~VeUICachedPanel();

	virtual void AttachChild(VeSceneNode* pkChild);

	virtual void OnShow();

	virtual void OnHide();

	virtual void Render();

	virtual VeUIWidget* PressEvent(VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual VeUIWidget* ReleaseEvent(VeUIWidgetPtr& spHold, VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	virtual VeUIWidget* CurMoveEvent(VeUIWidgetPtr& spCursor, VeUInt32 u32Time, VeUInt32 u32Type, const VeVector2D& kPos);

	static VeUIWidgetPtr Create();

protected:
	VeRefNode<VeRenderFrameManager::RenderTask*> m_kNode;
	const VeChar8* m_pcRenderTarget;
	VeRenderNode* m_pkRenderTarget;
	VeRenderNode* m_pkClear;
	VeRenderNode* m_pkDraw2DRoot;
	VeSceneNode2DPtr m_spRootNode2D;
	VeRenderQueue m_kRenderQueue;
	RtRepainterPtr m_spRtRepainter;

#ifdef VE_ENABLE_DEVICE_LOST

	typedef VeMemberDelegate<VeUICachedPanel,void> RestoreDelegate;

	void OnRestore();

	RestoreDelegate m_kRestoreDelegate;

#endif

};
