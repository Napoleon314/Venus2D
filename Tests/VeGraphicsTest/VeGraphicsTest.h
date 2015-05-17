////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Test Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeGraphicsTest.h
//  Version:     v1.00
//  Created:     27/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include <VeMainPCH.h>

class VeGraphicsTest : public VeApplication
{
public:
	typedef VeMemberDelegate<VeGraphicsTest,void> AniDelegate;

	VeGraphicsTest();

	~VeGraphicsTest();

	virtual void OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height);

	virtual void OnInit();

	virtual void OnTerm();

	virtual void OnUpdate();

	virtual void OnKeyPressed(VeKeyboard::InputKey eKey);

	virtual void OnKeyReleased(VeKeyboard::InputKey eKey);

	virtual void OnMousePressed(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y);

	virtual void OnMouseReleased(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y);

	virtual void OnCursorMove(VeUInt16 x, VeUInt16 y);

	virtual void OnMouseMove(VeUInt32 u32OffsetX, VeUInt32 u32OffsetY, VeUInt32 u32OffsetZ);

	virtual void OnJoyStickPressed(VeUInt32 u32Button);

	virtual void OnJoyStickReleased(VeUInt32 u32Button);

	virtual void OnJoyStickAxisChanged(VeUInt32 u32Axis, VeUInt32 u32Value);
    
    virtual void OnTouchBegan(VeUInt32 u32Time, VeUInt32 id, VeFloat32 x, VeFloat32 y);
    
    virtual void OnTouchEnded(VeUInt32 u32Time, VeUInt32 id, VeFloat32 x, VeFloat32 y);
    
    virtual void OnTouchMoved(VeUInt32 u32Time, VeVector<VeInputMessage::TouchPointParam>& kParams);
    
    virtual void OnTouchCancelled(VeUInt32 u32Time, VeVector<VeInputMessage::TouchPointParam>& kParams);

protected:
	VeSimpleSoundPtr m_spTestSound;
	//VeMusicPlayerPtr m_spTestMusic;
	VeSceneNode2DPtr m_spNode;
	VeSceneNode2DPtr m_spNodeText;
	AniDelegate m_kAniDelegate;
	void OnCallback();

};
