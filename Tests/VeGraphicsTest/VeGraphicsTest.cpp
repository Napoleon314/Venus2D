////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Test Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeGraphicsTest.cpp
//  Version:     v1.00
//  Created:     27/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeGraphicsTest.h"

VeInt32 TestCFunc(VeInt32 i)
{
	VE_LOG_I("luabind debug", "TestCFunc(%d)", i);
	return i;
}

VeInt32 TestCFunc(VeInt32 i, VeInt32 j)
{
	VE_LOG_I("luabind debug", "TestCFunc(%d,%d)", i, j);
	return i;
}

VeInt32 TestClassFunc(VeInt32 i)
{
	VE_LOG_I("luabind debug", "TestClassFunc(%d)", i);
	return i;
}

//--------------------------------------------------------------------------
VeGraphicsTest::VeGraphicsTest()
{
	m_kAniDelegate.Set(this, &VeGraphicsTest::OnCallback);
}
//--------------------------------------------------------------------------
VeGraphicsTest::~VeGraphicsTest()
{

}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnInit()
{
	VeTextTablePtr spTable = VeLoadTextTableSync("text.txt", "Scripts");

	m_spTestSound = VeLoadSimpleSoundSync("stereo.ogg", "Sound");

	VeLoadRenderFrameSync("test_frame.[frm]", "Scripts");
	VeVector<const VeChar8*> kUnitArray;
	kUnitArray.PushBack("test");
	g_pRenderFrameManager->Update("default", kUnitArray);

	VeLoadTextureAtlasSync("test-hd.xml", "Textures");

	//VeTextureResourcePtr spTex = VeLoadTextureSync("logo2.png", "Textures");

	VeSceneNode2DPtr spRoot = g_pSceneManager->GetRootNode2D();
	////spRoot->SetMulColor(1,1,1,0.5f);
	//spRoot->SetAddColor(0.3f, 0.0f, 0.0f);
	//VeSprite2DPtr spSprite = VE_NEW VeSprite2D("expression_1_01.png");
	//spRoot->AttachRenderable(spSprite);
	////spSprite->SetAnchor(0,0);
	////spRoot->SetRotate(VE_MATH_2_PI_F);
	////spRoot->SetScale(2.0f, 2.0f);
	//spRoot->SetPosition(200,200);
	////spSprite->SetColor(1.0f,1.0f,1.0,0.5f);

	////m_spAnimation = VE_NEW VeMorphManual2D(spRoot);

	////VeQuaternion kQuat;
	////kQuat.FromAngleAxis(1.0f, VeVector3D::UNIT_Y);
	////spRoot->SetRotate(1.0f);

	//

	//m_spNode = VE_NEW VeSceneNode2D;
	//spRoot->AttachChild(m_spNode);
	//m_spNode->SetPosition(80, 0);

	//VeSprite2DPtr spSprite2 = VE_NEW VeSprite2D("expression_1_02.png");
	//m_spNode->AttachRenderable(spSprite2);

	//VeSceneNode2DPtr spNode2 = VE_NEW VeSceneNode2D;
	//m_spNode->AttachChild(spNode2);
	//spNode2->SetPosition(80, 0);

	//VeSprite2DPtr spSprite3 = VE_NEW VeSprite2D("expression_1_03.png");
	//spNode2->AttachRenderable(spSprite3);

	//VeBoundingBox2D kBox(VeVector2D(-40,-40), VeVector2D(40,40));
	//VeSquareFramePtr spFrame = VE_NEW VeSquareFrame(kBox);
	//spNode2->AttachRenderable(spFrame);
	//spFrame = VE_NEW VeSquareFrame(kBox);
	//m_spNode->AttachRenderable(spFrame);
	//VeSquarePtr spSquare = VE_NEW VeSquare(kBox);
	//spRoot->AttachRenderable(spSquare);

	//m_spNodeText = VE_NEW VeSceneNode2D;
	//spRoot->AttachChild(m_spNodeText);
	//m_spNodeText->SetPosition(g_pRenderer->GetWidthF() * 0.5f, g_pRenderer->GetHeightF() * 0.5f);
	////pkNodeText->SetScale(2.0f);

	//VeFontPtr spTestFont = VeLoadFontSync("black.kfont", "Fonts");

	

	//m_spNodeText->RunAction(VeRepeatForever::Create(VeSequence::Create(VeScaleTo2D::Create(0.5f, 2.0f, 2.0f, VeTweenEasing::TYPE_QUAD_IN_OUT), VeScaleTo2D::Create(0.5f, 1.0f, 1.0f, VeTweenEasing::TYPE_QUAD_IN_OUT), NULL)));



	//m_spNodeText->SetScale(2.0f);
	//m_spNodeText->SetRotate(1.0f);

	//VeSingleCharPtr spText = VE_NEW VeSingleChar();
	//spText->SetChar(L'H', spTestFont);
	////spText->SetBias(-0.5f);
	//m_spNodeText->AttachRenderable(spText);

	/*VeSingleCharPtr spText2 = VE_NEW VeSingleChar();
	spText2->SetChar(L'b', spTestFont);
	spText2->SetBias(-0.5f);
	m_spNodeText->AttachRenderable(spText2);*/
	//VeSprite2DPtr spSprite5 = VE_NEW VeSprite2D("expression_1_02.png");
	//pkNodeText->AttachRenderable(spSprite5);

	//g_pLua->DoFileSync(VE_DIR("Lua/startup.lua"));

	//VeSizeT aaa = BaseClassBias<TestClass, TestBase1>();

	//VeInt32 a,b,c;
	//g_pLua->CallFunction("Test(ii)iii", 2, 3, &a,&b,&c);
	//g_pLua->CallFunction("Print(s)", "Test");

	//VeLuaCall(a, b, c, "Test", 2, 3);
	//VeLuaCall(a, b, c, "Test2");

	//VeLuaBind::MakeFuncFormat();
	//g_pLua->CallFunction("Print(s)", VeLuaBind::TypeToCName(VeLuaBind::MakeFuncFormat(&Test)));
	/*using namespace VeLuaBind;
	Module() [
		Def("TestCFunc", (VeInt32(*)(VeInt32))&TestCFunc),
			Def("TestCFunc", (VeInt32(*)(VeInt32,VeInt32))&TestCFunc)
	];
	VeLuaCall<void>("TestRun");
	VeInt32 i32Value = VeLuaCall<VeInt32>("TestCFunc", 4);
	VE_LOG_I("luabind debug", "Value %d", i32Value);
	i32Value = VeLuaCall<VeInt32>("TestCFunc", 3, 5);
	VE_LOG_I("luabind debug", "Value %d", i32Value);
	i32Value = VeLuaCall<VeInt32>("TestFunc", 3, 5);
	VE_LOG_I("luabind debug", "Value %d", i32Value);
	VE_ASSERT(g_pLua->GetTop() == 0);*/

	VeDragonBones::SetTexScale(2.0);
	VeLoadTextureAtlasSync("card_001.xml", "Textures");
	VeLoadTextureAtlasSync("card_002.xml", "Textures");
	VeLoadTextureAtlasSync("card_003.xml", "Textures");
	VeLoadTextureAtlasSync("card_Weapons_01.xml", "Textures");
	VeLoadTextureAtlasSync("card_Weapons_02.xml", "Textures");
	VeLoadTextureAtlasSync("eff_01.xml", "Textures");
	VeLoadTextureAtlasSync("eff_02.xml", "Textures");
	VeLoadDragonBonesSync("c04_001.xml", "Animation");
	//VeLoadDragonBonesSync("test.xml", "Animation");
	//VeLoadDragonBonesSync("ui_create_ani_1.xml", "Animation");

	VeDragonBonesEntityPtr spNode = VE_NEW VeDragonBonesEntity("c04_001.xml");

	spNode->SetZOrder(3.0f);
	spNode->SetPosition(g_pRenderer->GetWidthF() * 0.5f, g_pRenderer->GetHeightF() * 0.35f);
	g_pSceneManager->GetRootNode2D()->AttachChild(spNode);
	
	spNode->Play("lv4wait", 0.0f, 0.0f);

	/*VeSimpleTextPtr spText = VE_NEW VeSimpleText(spTestFont);
	spText->SetText("Hello World!");
	spText->SetLine(0, 0);
	spText->SetType(VeSimpleText::CENTER_CENTER, VeColor::WHITE, -0.5f, 0);
	spText->SetShadowType(VeColor(0,0,0,0.5f), 1.0f, VeVector2D(3.0f, 3.0f));
	
	spNode->GetBone("ui_create_title_0")->AttachChild(spText);*/

	

	
	//m_spNodeText->AttachChild(spText);

	//VeSimpleTextPtr spText2 = VE_NEW VeSimpleText(spTestFont);
	//spText2->SetText("Hello World!");
	//spText2->SetType(VeSimpleText::CENTER_CENTER, VeColor::WHITE, -0.5f, 0);
	//spText2->SetShadowType(VeColor(0,0,0,0.5f), 1.0f, VeVector2D(3.0f, 3.0f));
	//spText2->SetPosition(g_pRenderer->GetWidthF() * 0.5f, g_pRenderer->GetHeightF() * 0.5f);
	//m_spNodeText->AttachChild(spText2);

	//spNode->Play("Weapons_r", "01", 0.0f, 0.0f);
	//spNode->Play("Weapons_l", "01", 0.0f, 0.0f);
	//spNode->Play("eff_fly0", "stand", 0.0f, 0.0f);
	//spNode->Play("eff_fire0", "stand", 0.0f, 0.0f);

	//spNode->Play("eff_shield_0", "stand", 0.0f, 0.0f);

	//g_pClientManager->AddClient(VE_NEW VeClientBase("Test"));
	//g_pClientManager->Connect("Test", "127.0.0.1", 62001, "null", true);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnTerm()
{

}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnBufferResized(VeUInt32 u32Width, VeUInt32 u32Height)
{
	VeDebugOutput("OnBufferResized: %dx%d", u32Width, u32Height);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnUpdate()
{
	/*static VeAngle s_kAngle;
	VeFloat32 f32Delta = g_pTime->GetDeltaTime();
	s_kAngle += f32Delta;
	g_pSceneManager->GetRootNode2D()->SetRotate(s_kAngle);
	m_spNode->SetRotate(s_kAngle);*/

	/*static VeFloat32 s_f32Scale = 0.5f;
	VeFloat32 f32Delta = g_pTime->GetDeltaTime();
	s_f32Scale += f32Delta * 0.5f;
	m_spNodeText->SetScale(s_f32Scale);*/
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnKeyPressed(VeKeyboard::InputKey eKey)
{
	if(eKey == VeKeyboard::KEY_F4)
	{
		QuitApp();
	}
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnKeyReleased(VeKeyboard::InputKey eKey)
{
	if(eKey == VeKeyboard::KEY_C)
	{
		g_pMouse->SetCursorPosF(0.5f, 0.5f);
	}
	else if(eKey == VeKeyboard::KEY_H)
	{
		g_pMouse->SetHide(!g_pMouse->GetStateFlag(VeMouse::CUR_HIDE));
	}
	else if(eKey == VeKeyboard::KEY_L)
	{
		g_pMouse->SetLock(!g_pMouse->GetStateFlag(VeMouse::CUR_LOCK));
	}
	else if(eKey == VeKeyboard::KEY_R)
	{
		//m_spAnimation->MoveBy(0.5f, VeVector2D(50, 50), VeTweenEasing::TYPE_SINE_IN_OUT);
		//m_spAnimation->ScaleBy(0.5f, VeVector2D(2.0f, 2.0f), VeTweenEasing::TYPE_LINEAR);
		//m_spAnimation->RotateBy(0.5f, 8.0f, VeTweenEasing::TYPE_LINEAR);
		//m_spAnimation->ColorBy(0.5f, VeColor(1.0f, 1.0f, 1.0f, 0.8f), VeTweenEasing::TYPE_LINEAR);
	}
	else if(eKey == VeKeyboard::KEY_B)
	{
		//m_spAnimation->MoveBy(0.5f, VeVector2D(-50, -50), VeTweenEasing::TYPE_SINE_IN_OUT);
		//m_spAnimation->ScaleTo(0.5f, VeVector2D(1.0f, 1.0f), VeTweenEasing::TYPE_SINE_IN_OUT);
		//m_spAnimation->RotateTo(0.5f, 0.0f, VeTweenEasing::TYPE_SINE_IN_OUT);
		//m_spAnimation->ColorTo(0.5f, VeColor(1.0f, 1.0f, 1.0f, 0.0f), VeTweenEasing::TYPE_SINE_IN_OUT);
	}
#if defined(VE_PLATFORM_PC)
	else if(eKey == VeKeyboard::KEY_U)
	{
		g_pRenderer->ResizeWindow(1024, 768);
	}
	else if(eKey == VeKeyboard::KEY_I)
	{
		g_pRenderer->ResizeWindow(800, 600);
	}
	else if(VE_MASK_HAS_ALL(g_pKeyboard->GetModifiers(), VeKeyboard::CTRL) && eKey == VeKeyboard::KEY_F)
	{
		//g_pRenderer->SetFullScreen(!g_pStartConfig->IsFullScreen());
	}
#elif defined(VE_PLATFORM_MOBILE_SIM)
	else if(eKey == VeKeyboard::KEY_U)
	{
		g_pRenderer->ResizeWindow(1024, 768);
	}
	else if(eKey == VeKeyboard::KEY_I)
	{
		g_pRenderer->ResizeWindow(960, 640);
	}
#endif
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnMousePressed(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y)
{
	VeDebugOutput("MouseButton%d:Pressed Pos:%d,%d", eBtn, x, y);
	g_pAudioSystem->Play(m_spTestSound);

	//g_pAudioSystem->Play(m_spTestMusic);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnMouseReleased(VeMouse::State eBtn, VeUInt16 x, VeUInt16 y)
{
	VeDebugOutput("MouseButton%d:Released Pos:%d,%d", eBtn, x, y);
	//m_spTestMusic->Stop();

	//VeFiniteTimeActionPtr spAction = VeRotateBy2D::Create(1.0f, VE_MATH_PI_F);
	//g_pSceneManager->GetRootNode2D()->RunAction(
	//	VeSequence::Create(VeRotateTo2D::Create(1.0f, VE_MATH_PI_F), spAction, spAction->Reverse(), spAction, spAction->Reverse(), NULL));
	//g_pSceneManager->GetRootNode2D()->RunAction(VeRepeatForever::Create(VeRotateBy2D::Create(1.0f, VE_MATH_PI_F)));
	//g_pSceneManager->GetRootNode2D()->RunAction(VeMoveBy2D::Create(0.5f, 100, 100));
	/*g_pSceneManager->GetRootNode2D()->RunAction(VeSpawn::Create(
		VeMoveBy2D::Create(1.0f, 100, 100),
		VeMoveBy2D::Create(1.0f, 100, 100),
		VeRotateBy2D::Create(1.0f, VE_MATH_PI_F),
		NULL));*/
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnCursorMove(VeUInt16 x, VeUInt16 y)
{
	//VeDebugOutput("CursorMove:%d,%d", x, y);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnMouseMove(VeUInt32 u32OffsetX, VeUInt32 u32OffsetY, VeUInt32 u32OffsetZ)
{
	//VeDebugOutput("MouseMove:%d,%d, %d", u32OffsetX, u32OffsetY, u32OffsetZ);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnJoyStickPressed(VeUInt32 u32Button)
{
	VeDebugOutput("OnJoyStickPressed: %d", u32Button);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnJoyStickReleased(VeUInt32 u32Button)
{
	VeDebugOutput("OnJoyStickReleased: %d", u32Button);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnJoyStickAxisChanged(VeUInt32 u32Axis, VeUInt32 u32Value)
{
	VeDebugOutput("Axis%dChanged: %d", u32Axis, u32Value);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnTouchBegan(VeUInt32 u32Time, VeUInt32 id, VeFloat32 x, VeFloat32 y)
{
    VeDebugOutput("OnTouchBegan[time:%d,id:%d,x:%.0f,y:%.0f]", u32Time, id, x, y);
    g_pAudioSystem->Play(m_spTestSound);
    
    //g_pAudioSystem->Play(m_spTestMusic);
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnTouchEnded(VeUInt32 u32Time, VeUInt32 id, VeFloat32 x, VeFloat32 y)
{
    VeDebugOutput("OnTouchEnded[time:%d,id:%d,x:%.0f,y:%.0f]", u32Time, id, x, y);
    //m_spTestMusic->Stop();
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnTouchMoved(VeUInt32 u32Time, VeVector<VeInputMessage::TouchPointParam>& kParams)
{
    for(VeVector<VeInputMessage::TouchPointParam>::iterator it = kParams.Begin(); it != kParams.End(); ++it)
    {
        VeDebugOutput("OnTouchMoved[time:%d,id:%d,x:%.0f,y:%.0f]", u32Time, it->id, it->x, it->y);
    }
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnTouchCancelled(VeUInt32 u32Time, VeVector<VeInputMessage::TouchPointParam>& kParams)
{
    for(VeVector<VeInputMessage::TouchPointParam>::iterator it = kParams.Begin(); it != kParams.End(); ++it)
    {
        VeDebugOutput("OnTouchCancelled[time:%d,id:%d,x:%.0f,y:%.0f]", u32Time, it->id, it->x, it->y);
    }
}
//--------------------------------------------------------------------------
void VeGraphicsTest::OnCallback()
{
	VeDebugOutput("Callback");
}
//--------------------------------------------------------------------------
