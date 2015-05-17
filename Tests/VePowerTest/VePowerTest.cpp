////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Test Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VePowerTest.cpp
//  Version:     v1.00
//  Created:     27/8/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VePowerTest.h"

void TestVector()
{
	VeVector<VeInt32> kVector;

	VeVector<VeInt32> kVector2;
	kVector2.PushBack(10);
	kVector2.PushBack(11);
	kVector2.PushBack(13);

	kVector.Insert(kVector.Begin(), kVector2.Begin(), kVector2.Last());

	kVector.PushBack(1);
	kVector.PushBack(2);
	kVector.PushBack(3);
	kVector.PushBack(4);
	kVector.PushBack(5);
	kVector.PushBack(6);

	for(VeVector<VeInt32>::iterator it = kVector.Begin(); it < kVector.End(); ++it)
	{
		VE_LOG_I("VectorTest", "%d", *it);
	}

	kVector.Erase(kVector.Begin() + 1, kVector.Begin() + 5);

	for(VeVector<VeInt32>::iterator it = kVector.Begin(); it < kVector.End(); ++it)
	{
		VE_LOG_I("VectorTest", "%d", *it);
	}
}

void PrintIntList(VeList<VeInt32>& kList)
{
	for(VeList<VeInt32>::iterator it = kList.Begin(); it != kList.End(); ++it)
	{
		VE_LOG_I("ListTest", "%d", *it);
		if(it.IsLast())
		{
			VE_LOG_I("ListTest", "Iter Last");
		}
	}

	for(VeList<VeInt32>::iterator it = kList.Last(); it != kList.End(); --it)
	{
		VE_LOG_I("ListTest", "%d", *it);
		if(it.IsFirst())
		{
			VE_LOG_I("ListTest", "Iter First");
		}
	}
}

void TestList()
{
	VeList<VeInt32> kList;

	kList.PushBack(7);
	kList.PushBack(10);
	kList.PushBack(5);

	kList.PushFront(8);
	kList.PushFront(6);
	kList.PushFront(9);
	
	PrintIntList(kList);

	kList.Erase(++(kList.Begin()), ++++++(kList.Begin()));

	kList.Insert(++kList.Begin(), 3, 88);

	PrintIntList(kList);
}

void TestHashMap()
{
	VeHashMap<VeInt32, VeInt32> kMap;
	kMap[5] = 10;
	kMap[10] = 1;
	kMap[8] = 2;

	kMap.Insert(0, 8);
	kMap.Insert(0, 11);
	kMap.Insert(0, 10, false);

	kMap.Insert(32, 77);
	kMap[32] = 40;

	VeInt32* pi32Res;

	pi32Res = kMap.Find(5);
	if(pi32Res) VE_LOG_I("MapTest", "5: %d", *pi32Res);
	pi32Res = kMap.Find(8);
	if(pi32Res) VE_LOG_I("MapTest", "8: %d", *pi32Res);
	pi32Res = kMap.Find(10);
	if(pi32Res) VE_LOG_I("MapTest", "10: %d", *pi32Res);
	pi32Res = kMap.Find(0);
	if(pi32Res) VE_LOG_I("MapTest", "0: %d", *pi32Res);
	pi32Res = kMap.Find(32);
	if(pi32Res) VE_LOG_I("MapTest", "32: %d", *pi32Res);
}

void TestTreeMap()
{
	VeTreeMap<VeInt32, VeInt32> kMap;
	//kMap.Insert(5, 8);
	//kMap.Insert(5, 11);
	//kMap.Insert(4, 12);
	//kMap.Insert(3, 7);
	//kMap.Insert(7, 9);
	kMap[100] = 0;
	kMap[90] = 1;
	kMap[80] = 2;
	kMap[70] = 3;
	kMap[75] = 4;
	kMap[110] = 5;
	kMap[105] = 6;
	//kMap[5] = 11;
	//kMap[4] = 12;
	//kMap[3] = 7;
	//kMap[7] = 9;

	VeTreeMap<VeInt32, VeInt32>::iterator it = kMap.Find(110);
	kMap.Erase(it);

	for(VeTreeMap<VeInt32, VeInt32>::iterator iter = kMap.Begin(); iter != kMap.End(); ++iter)
	{
		VE_LOG_I("TreeMapTest", "%d: %d", iter->m_tFirst, iter->m_tSecond);
	}
}

void TestMap()
{
	VeMap<VeUInt32, VeString> kMap;
	VeVector<VeUInt32> kKey;
	for(VeUInt32 i(0); i < 30; ++i)
	{
		kKey.PushBack(VeRand());
	}

	for(VeUInt32 i(0); i < kKey.Size(); ++i)
	{
		kMap.Insert(kKey[i], "test");
	}

	VeUInt32 u32Last(0);
	for(VeMap<VeUInt32, VeString>::iterator it = kMap.Begin(); it != kMap.End(); ++it)
	{
		VE_ASSERT(u32Last < it->m_tFirst);
		u32Last = it->m_tFirst;
		VE_LOG_I("MapTest", "%d", it->m_tFirst);
		it->m_tSecond = "Test2";
	}
	//kMap[15724] = "best";
	
	//kMap.Clear();*/
	kMap.Print();
	/*VeMap<VeUInt32, VeString>::const_iterator itFind = kMap.Find(41);
	itFind = kMap.Erase(itFind);
	kMap.Print();
	itFind = kMap.Find(18467);
	itFind = kMap.Erase(itFind);
	kMap.Print();*/

	for(VeUInt32 i(0); i < kKey.Size(); ++i)
	{
		VeMap<VeUInt32, VeString>::const_iterator itFind = kMap.Find(kKey[i]);
		kMap.Erase(itFind);
		kMap.Print();
	}
}

class VeTestThread : public VeThread
{
public:
	VeTestThread()
	{

	}

	void Run()
	{
		for(VeUInt32 i(0); i < 100; ++i)
		{
			VE_LOG_I("VenusThread", "TestThread: %d", i);
		}
	}

	Event m_kEvent;

};

void TestThread()
{
	VeTestThread kThread;
	kThread.Start();
	VeThread::Join(kThread);

	for(VeUInt32 i(0); i < 100; ++i)
	{
		VE_LOG_I("VenusThread", "MainThread: %d", i);
	}
	kThread.Start();

	VeSleep(5000);
}

void TestString()
{
	VeString kVecStr = "0.5f,0.8f";
	VeVector2D kVec2D;
	kVecStr.ToVector2D(kVec2D);
	VeDebugOutput(VeString::From(kVec2D));

	VeDebugOutput("Number is %d", VeWtoi(L"65536"));
}

void ReadCallback(const VeMemoryIStreamPtr& spData)
{
    if(spData)
    {
        VeDebugOutput((const VeChar8*)spData->GetData());
        spData->Finish();
    }
}

void WriteCallback(VeResult eRes)
{
	if(VE_SUCCEEDED(eRes))
	{
		VeDebugOutput("Write async succeed");
	}
	else
	{
		VeDebugOutput("Write async failed");
	}
}

VeDirectory::ReadFuncDelegate g_kReadDelegate(ReadCallback);

VeDirectory::WriteFuncDelegate g_kWriteDelegate(WriteCallback);

VeDirectory::ReadFuncDelegate g_kZipReadDelegate(ReadCallback);

VeDirectory::ReadFuncDelegate g_kURLDelegate(ReadCallback);

void TestFileStream()
{
	/*VeString kSrc = "HelloWorld!";
	VeFileOStreamPtr spTestO = VE_NEW VeFileOStream("Test.bin");
	(*spTestO) << kSrc;
	spTestO = NULL;
	VeFileIStreamPtr spTestI = VE_NEW VeFileIStream("Test.bin");
	VeString kDst;
	(*spTestI) >> kDst;
	VeDebugOutputString(kDst);
	spTestI->Finish();
	spTestI = NULL;*/
    
    //FILE* pkFile = fopen("Test.txt", "wb");
    
#if defined(VE_PLATFORM_ANDROID)
#	define START_DIR "/sdcard/VenusDevelop"
#	define ZIP_FILE "/sdcard/VenusDevelop/Test.zip"
#elif defined(VE_PLATFORM_IOS)
#	define START_DIR "../Documents"
#	define ZIP_FILE "Test.zip"
#else
#	define START_DIR "."
#	define ZIP_FILE "Test.zip"
#endif

	VeFileDir kDir(START_DIR);

	if(kDir.Change("Test"))
	{
		VeDebugOutput("Change To Test Dir");
		VeMemoryOStreamPtr spTestContent = VE_NEW VeMemoryOStream();
		spTestContent->Write("Hello World!", (VeInt32)VeStrlen("Hello World!"));
		kDir.WriteAsync("Test.txt", spTestContent, g_kWriteDelegate);
	}

	kDir.ReadAsync("Test.txt", g_kReadDelegate);

	VeZipPtr spZip = g_pResourceManager->GetZip(ZIP_FILE);
    if(spZip)
    {
    	VeDebugOutput("Has zip");
        VeZipDir kZipDir("Test", spZip);
        kZipDir.ReadAsync("Test.txt", g_kZipReadDelegate);
    }
}

void TestURLStream()
{
	VeChar8 acBuffer[2048];
	VeURLDir kDir("http://112.65.18.2:3141");
	VeBinaryIStreamPtr spStream = kDir.OpenSync("Test.txt");
	VeInt32 i32Length = spStream->RemainingLength();
	spStream->Read(acBuffer, i32Length);
	acBuffer[i32Length] = 0;
	VeDebugOutput(acBuffer);
	spStream->Finish();

	kDir.ReadAsync("Test.txt", g_kURLDelegate);
}

void TestMath()
{
	VeVector4D kName(0.1f,0.2f,0.3f,0.4f);
	VeZero4f(kName);
	VE_LOG_I("Venus3D", "%f,%f,%f,%f", kName.x, kName.y, kName.z, kName.w);
}

VePowerTest::VePowerTest()
{

}

void VePowerTest::OnInit()
{
	VeDebugOutput("VeSizeT Has %d Bytes", sizeof(VeSizeT));
	VeDebugOutput("VeSizeT& Has %d Bytes", sizeof(VeSizeT&));
	VeDebugOutput("VeSizeT* Has %d Bytes", sizeof(VeSizeT*));
	TestVector();
	TestList();
	TestHashMap();
	TestTreeMap();
	TestMap();
	//TestThread();
	TestString();
	//TestFileStream();
	//TestURLStream();
	TestMath();
}

void VePowerTest::OnTerm()
{

}

void VePowerTest::OnUpdate()
{

}

void VePowerTest::OnKeyPressed(VeKeyboard::InputKey eKey)
{
	if(eKey == VeKeyboard::KEY_F4)
	{
		QuitApp();
	}
}

void VePowerTest::OnKeyReleased(VeKeyboard::InputKey eKey)
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
		g_pRenderer->SetFullScreen(!g_pStartConfig->IsFullScreen());
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
