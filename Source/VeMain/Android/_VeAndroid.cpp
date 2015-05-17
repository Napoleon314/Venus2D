////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeWindows.cpp
//  Version:     v1.00
//  Created:     17/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "../VeMainPCH.h"
#include "../_VeRendererGLES2.h"
#include "_VeAndroid.h"

//--------------------------------------------------------------------------
static pthread_key_t s_iKey(0);
//--------------------------------------------------------------------------
VeAndroid::VeAndroid(VeStartParams& kParams)
	: VeDevice(TYPE_ANDROID, kParams), m_joClassLoader(0)
	, m_jfuncLoadClass(0), m_bWindowInit(false)
{
	pthread_key_create(&s_iKey, NULL);
}
//--------------------------------------------------------------------------
VeAndroid::~VeAndroid()
{

}
//--------------------------------------------------------------------------
void VeAndroid::_Init()
{
	m_kParams.m_pkAppState->userData = this;
	m_kParams.m_pkAppState->onAppCmd = HandleCommand;
	m_kParams.m_pkAppState->onInputEvent = HandleInput;
	SetAssetManager(m_kParams.m_pkAppState->activity->assetManager);
	JNIEnv* jni = GetJNIEnv();
	VE_ASSERT(jni);
	jclass activityClass = jni->FindClass("android/app/NativeActivity");
	VE_ASSERT(activityClass);
	jmethodID getClassLoader = jni->GetMethodID(activityClass,"getClassLoader", "()Ljava/lang/ClassLoader;");
	VE_ASSERT(getClassLoader);
	m_joClassLoader = jni->CallObjectMethod(m_kParams.m_pkAppState->activity->clazz, getClassLoader);
	VE_ASSERT(m_joClassLoader);
	jclass classLoader = jni->FindClass("java/lang/ClassLoader");
	VE_ASSERT(classLoader);
	m_jfuncLoadClass = jni->GetMethodID(classLoader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	VE_ASSERT(m_jfuncLoadClass);
	if(m_joClassLoader && m_jfuncLoadClass)
	{
		VE_LOG_I("JNI", "JNI is initialized successful");
	}

	JniMethodInfo kInfo;

	GetStaticMethodInfo(kInfo,
		"com/VenusIE/Venus3D/VeActivity",
		"jni_GetDeviceID", "()Ljava/lang/String;");
	m_kDeviceID = GetString((jstring)kInfo.m_pkEnv->CallStaticObjectMethod(kInfo.m_iClassID, kInfo.m_iMethodID));
	kInfo.m_pkEnv->DeleteLocalRef(kInfo.m_iClassID);

	GetStaticMethodInfo(kInfo,
		"com/VenusIE/Venus3D/VeActivity",
		"jni_GetDeviceName", "()Ljava/lang/String;");
	m_kDeviceName = GetString((jstring)kInfo.m_pkEnv->CallStaticObjectMethod(kInfo.m_iClassID, kInfo.m_iMethodID));
	kInfo.m_pkEnv->DeleteLocalRef(kInfo.m_iClassID);

	GetStaticMethodInfo(kInfo,
		"com/VenusIE/Venus3D/VeActivity",
		"jni_GetLanguage", "()Ljava/lang/String;");
	VeString kLanguage = GetString((jstring)kInfo.m_pkEnv->CallStaticObjectMethod(kInfo.m_iClassID, kInfo.m_iMethodID));
	kInfo.m_pkEnv->DeleteLocalRef(kInfo.m_iClassID);
	m_eLanguage = LanguageLua::ToEnum(kLanguage, EN_US);
}
//--------------------------------------------------------------------------
void VeAndroid::_Term()
{
	ClearJNIEnv();
}
//--------------------------------------------------------------------------
void VeAndroid::_CreateWindow(Window* pkWindow)
{
	while(!m_bWindowInit)
	{
		VeInt32 i32Events;
		struct android_poll_source* pkSource;
		VeInt32 i32Ident = ALooper_pollAll(-1, NULL, &i32Events, (void**)&pkSource);
		if(i32Ident >= 0 && pkSource)
		{
			pkSource->process(m_kParams.m_pkAppState, pkSource);
		}
	}
}
//--------------------------------------------------------------------------
void VeAndroid::_DestoryWindow(Window* pkWindow)
{

}
//--------------------------------------------------------------------------
void VeOnTouchBegan(VeInt32 id, VeFloat32 x, VeFloat32 y)
{
	VeUInt32 u32Time = g_pTime->GetTimeUInt();
	VeInputManager::TouchPointParam* pkParam(NULL);
	g_pInputManager->GetSingle(pkParam);
	pkParam->x = x;
	pkParam->y = y;
	pkParam->id = id;
	g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_BEGAN, u32Time, pkParam);
}
//--------------------------------------------------------------------------
void VeOnTouchEnded(VeInt32 id, VeFloat32 x, VeFloat32 y)
{
	VeUInt32 u32Time = g_pTime->GetTimeUInt();
	VeInputManager::TouchPointParam* pkParam(NULL);
	g_pInputManager->GetSingle(pkParam);
	pkParam->x = x;
	pkParam->y = y;
	pkParam->id = id;
	g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_ENDED, u32Time, pkParam);
}
//--------------------------------------------------------------------------
void VeOnTouchMoved(VeVector<VeInputManager::TouchPointParam>* pkTouchPointList)
{
	VeUInt32 u32Time = g_pTime->GetTimeUInt();
	g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_MOVED, u32Time, pkTouchPointList);
}
//--------------------------------------------------------------------------
void VeOnTouchCancelled(VeVector<VeInputManager::TouchPointParam>* pkTouchPointList)
{
	VeUInt32 u32Time = g_pTime->GetTimeUInt();
	g_pInputManager->AppendMessage(VeInputMessage::DT_TOUCH, VeInputMessage::TIT_CANCELLED, u32Time, pkTouchPointList);
}
//--------------------------------------------------------------------------
static void DebugOutputCmd(int32_t i32Command)
{
	switch(i32Command)
	{
	case APP_CMD_INPUT_CHANGED:
		VeDebugOutput("APP_CMD_INPUT_CHANGED");
		break;
	case APP_CMD_INIT_WINDOW:
		VeDebugOutput("APP_CMD_INIT_WINDOW");
		break;
	case APP_CMD_TERM_WINDOW:
		VeDebugOutput("APP_CMD_TERM_WINDOW");
		break;
	case APP_CMD_WINDOW_RESIZED:
		VeDebugOutput("APP_CMD_WINDOW_RESIZED");
		break;
	case APP_CMD_WINDOW_REDRAW_NEEDED:
		VeDebugOutput("APP_CMD_WINDOW_REDRAW_NEEDED");
		break;
	case APP_CMD_CONTENT_RECT_CHANGED:
		VeDebugOutput("APP_CMD_CONTENT_RECT_CHANGED");
		break;
	case APP_CMD_GAINED_FOCUS:
		VeDebugOutput("APP_CMD_GAINED_FOCUS");
		break;
	case APP_CMD_LOST_FOCUS:
		VeDebugOutput("APP_CMD_LOST_FOCUS");
		break;
	case APP_CMD_CONFIG_CHANGED:
		VeDebugOutput("APP_CMD_CONFIG_CHANGED");
		break;
	case APP_CMD_LOW_MEMORY:
		VeDebugOutput("APP_CMD_LOW_MEMORY");
		break;
	case APP_CMD_START:
		VeDebugOutput("APP_CMD_START");
		break;
	case APP_CMD_RESUME:
		VeDebugOutput("APP_CMD_RESUME");
		break;
	case APP_CMD_SAVE_STATE:
		VeDebugOutput("APP_CMD_SAVE_STATE");
		break;
	case APP_CMD_PAUSE:
		VeDebugOutput("APP_CMD_PAUSE");
		break;
	case APP_CMD_STOP:
		VeDebugOutput("APP_CMD_STOP");
		break;
	case APP_CMD_DESTROY:
		VeDebugOutput("APP_CMD_DESTROY");
		break;
	default:
		VE_ASSERT(!"Error!");
		break;
	}
}
//--------------------------------------------------------------------------
void VeAndroid::HandleCommand(struct android_app* pkAppState, int32_t i32Command)
{
	DebugOutputCmd(i32Command);
	switch(i32Command)
	{
	case APP_CMD_INIT_WINDOW:
		if(pkAppState->window)
		{
			if(((VeAndroid*)g_pDevice)->m_bWindowInit)
			{
				((VeRendererGLES2*)g_pRenderer)->Restore();
			}
			else
			{
				((VeAndroid*)g_pDevice)->m_bWindowInit = true;
			}
			((VeAndroid*)g_pDevice)->Show();
		}
		break;
	case APP_CMD_TERM_WINDOW:
		((VeAndroid*)g_pDevice)->Hide();
		((VeRendererGLES2*)g_pRenderer)->Lost();
		break;
	case APP_CMD_GAINED_FOCUS:
		((VeAndroid*)g_pDevice)->Active();
		break;
	case APP_CMD_LOST_FOCUS:
		((VeAndroid*)g_pDevice)->Inactive();
		break;
	case APP_CMD_CONFIG_CHANGED:
		//s_bChangeSurface = true;
		break;
	case APP_CMD_LOW_MEMORY:
		break;
	case APP_CMD_DESTROY:
		g_pApplication->QuitApp();
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
int32_t VeAndroid::HandleInput(struct android_app* pkAppState, AInputEvent* pkEvent)
{
	int32_t i32Type = AInputEvent_getType(pkEvent);
	if(i32Type == AINPUT_EVENT_TYPE_KEY)
	{
		VE_LOG_I("lua", "key %d", AKeyEvent_getAction(pkEvent));
		return VE_FALSE;
	}
	else if(i32Type == AINPUT_EVENT_TYPE_MOTION)
	{
		VeInt32 i32Action = AMotionEvent_getAction(pkEvent);
		if(i32Action == AMOTION_EVENT_ACTION_DOWN)
		{
			VeOnTouchBegan(AMotionEvent_getPointerId(pkEvent, 0), AMotionEvent_getX(pkEvent, 0), AMotionEvent_getY(pkEvent, 0));
			return VE_TRUE;
		}
		else if((i32Action & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_POINTER_DOWN)
		{
			VeInt32 i32Index = (i32Action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
			VeOnTouchBegan(AMotionEvent_getPointerId(pkEvent, i32Index), AMotionEvent_getX(pkEvent, i32Index), AMotionEvent_getY(pkEvent, i32Index));
			return VE_TRUE;
		}
		else if(i32Action == AMOTION_EVENT_ACTION_UP)
		{
			VeOnTouchEnded(AMotionEvent_getPointerId(pkEvent, 0), AMotionEvent_getX(pkEvent, 0), AMotionEvent_getY(pkEvent, 0));
			return VE_TRUE;
		}
		else if((i32Action & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_POINTER_UP)
		{
			VeInt32 i32Index = (i32Action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
			VeOnTouchEnded(AMotionEvent_getPointerId(pkEvent, i32Index), AMotionEvent_getX(pkEvent, i32Index), AMotionEvent_getY(pkEvent, i32Index));
			return VE_TRUE;
		}
		else if(i32Action == AMOTION_EVENT_ACTION_MOVE)
		{
			VeSizeT stPointerCount = AMotionEvent_getPointerCount(pkEvent);
			VeVector<VeInputManager::TouchPointParam>* pkParams = g_pInputManager->GetList<VeInputManager::TouchPointParam>();
			(*pkParams).Resize(stPointerCount);
			for(VeSizeT i(0); i < stPointerCount; ++i)
			{
				VeInputManager::TouchPointParam& kParam = (*pkParams)[i];
				kParam.id = AMotionEvent_getPointerId(pkEvent, i);
				kParam.x = AMotionEvent_getX(pkEvent, i);
				kParam.y = AMotionEvent_getY(pkEvent, i);
			}
			VeOnTouchMoved(pkParams);
			return VE_TRUE;
		}
		else if(i32Action == AMOTION_EVENT_ACTION_CANCEL)
		{
			VeSizeT stPointerCount = AMotionEvent_getPointerCount(pkEvent);
			VeVector<VeInputManager::TouchPointParam>* pkParams = g_pInputManager->GetList<VeInputManager::TouchPointParam>();
			(*pkParams).Resize(stPointerCount);
			for(VeSizeT i(0); i < stPointerCount; ++i)
			{
				VeInputManager::TouchPointParam& kParam = (*pkParams)[i];
				kParam.id = AMotionEvent_getPointerId(pkEvent, i);
				kParam.x = AMotionEvent_getX(pkEvent, i);
				kParam.y = AMotionEvent_getY(pkEvent, i);
			}
			VeOnTouchCancelled(pkParams);
			return VE_TRUE;
		}
	}
	return VE_FALSE;
}
//--------------------------------------------------------------------------
ANativeWindow* VeAndroid::GetWindow()
{
	return m_kParams.m_pkAppState->window;
}
//--------------------------------------------------------------------------
void VeAndroid::_PumpEvents()
{
	VeInt32 i32Events;
	struct android_poll_source* pkSource;
	while(ALooper_pollAll(g_pRenderer->IsInited() ? 0 : -1, NULL, &i32Events, (void**)&pkSource) >= 0)
	{
		if(pkSource)
		{
			pkSource->process(m_kParams.m_pkAppState, pkSource);
		}
	}
}
//--------------------------------------------------------------------------
void VeAndroid::_EnableIME(Window* pkWindow)
{
	JniMethodInfo kInfo;
	GetMethodInfo(kInfo,
		"com/VenusIE/Venus3D/VeActivity",
		"jni_EnableIME", "()V");
	kInfo.m_pkEnv->CallVoidMethod(m_kParams.m_pkAppState->activity->clazz, kInfo.m_iMethodID);
	kInfo.m_pkEnv->DeleteLocalRef(kInfo.m_iClassID);
}
//--------------------------------------------------------------------------
void VeAndroid::_DisableIME(Window* pkWindow)
{
	JniMethodInfo kInfo;
	GetMethodInfo(kInfo,
		"com/VenusIE/Venus3D/VeActivity",
		"jni_DisableIME", "()V");
	kInfo.m_pkEnv->CallVoidMethod(m_kParams.m_pkAppState->activity->clazz, kInfo.m_iMethodID);
	kInfo.m_pkEnv->DeleteLocalRef(kInfo.m_iClassID);
	/*JniMethodInfo kInfo;
	GetStaticMethodInfo(kInfo,
		"com/VenusIE/Venus3D/VeActivity",
		"jni_DisableIME", "()V");
	kInfo.m_pkEnv->CallStaticObjectMethod(kInfo.m_iClassID, kInfo.m_iMethodID);
	kInfo.m_pkEnv->DeleteLocalRef(kInfo.m_iClassID);*/
}
//--------------------------------------------------------------------------
JNIEnv* VeAndroid::CacheJNIEnv()
{
	JNIEnv* pkEnv(NULL);
	jint iRet = GetJavaVM()->GetEnv((void**)&pkEnv, JNI_VERSION_1_6);
	switch(iRet)
	{
	case JNI_OK:
		pthread_setspecific(s_iKey, pkEnv);
		break;
	case JNI_EDETACHED:
		if(GetJavaVM()->AttachCurrentThread(&pkEnv, NULL) < 0)
		{
			VE_LOG_E("JNI", "Failed to get the environment using AttachCurrentThread");
			pkEnv = NULL;
		}
		else
		{
			pthread_setspecific(s_iKey, pkEnv);
		}
		break;
	case JNI_EVERSION:
		VE_LOG_E("JNI", "JNI interface version 1.6 not supported");
	default:
		VE_LOG_E("JNI", "Failed to get the environment using GetEnv()");
		pkEnv = NULL;
		break;
	}
	return pkEnv;
}
//--------------------------------------------------------------------------
jclass VeAndroid::GetClassID(const VeChar8* pcClass)
{
	if(!pcClass) return NULL;
	JNIEnv* pkEnv = GetJNIEnv();
	jstring jstrClass = pkEnv->NewStringUTF(pcClass);
	jclass jclsRes = (jclass)pkEnv->CallObjectMethod(m_joClassLoader,
		m_jfuncLoadClass, jstrClass);
	if(!jclsRes)
	{
		VE_LOG_E("JNI", "Classloader failed to find class of %s", pcClass);
		pkEnv->ExceptionClear();
	}
	pkEnv->DeleteLocalRef(jstrClass);
	return jclsRes;
}
//--------------------------------------------------------------------------
JavaVM* VeAndroid::GetJavaVM()
{
	VE_ASSERT(m_kParams.m_pkAppState->activity->vm);
	return m_kParams.m_pkAppState->activity->vm;
}
//--------------------------------------------------------------------------
JNIEnv* VeAndroid::GetJNIEnv()
{
	JNIEnv* pkEnv = (JNIEnv*)pthread_getspecific(s_iKey);
	if(!pkEnv)
	{
		pkEnv = CacheJNIEnv();
	}
	return pkEnv;
}
//--------------------------------------------------------------------------
void VeAndroid::ClearJNIEnv()
{
	GetJavaVM()->DetachCurrentThread();
	pthread_setspecific(s_iKey, 0);
}
//--------------------------------------------------------------------------
VeString VeAndroid::GetString(jstring jstrContent)
{
	VeChar8 acBuffer[1024];
	JNIEnv* pkEnv = GetJNIEnv();
	jclass clsstring = pkEnv->FindClass("java/lang/String");
	jstring strencode = pkEnv->NewStringUTF("utf-8");
	jmethodID mid = pkEnv->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)pkEnv->CallObjectMethod(jstrContent, mid, strencode);
	jsize alen = pkEnv->GetArrayLength(barr);
	jbyte* ba = pkEnv->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		VE_ASSERT(alen < 1024);
		VeMemcpy(acBuffer, ba, alen);
		acBuffer[alen] = 0;
	}
	pkEnv->ReleaseByteArrayElements(barr, ba, 0);
	return acBuffer;
}
//--------------------------------------------------------------------------
void VeAndroid::GetStaticMethodInfo(JniMethodInfo& kOut,
	const VeChar8* pcClass, const VeChar8* pcMethod,
	const VeChar8* pcParamCode)
{
	VE_ASSERT(pcClass && pcMethod && pcParamCode);
	kOut.m_pkEnv = GetJNIEnv();
	VE_ASSERT(kOut.m_pkEnv);
	kOut.m_iClassID = GetClassID(pcClass);
	VE_ASSERT(kOut.m_iClassID);
	kOut.m_iMethodID = kOut.m_pkEnv->GetStaticMethodID(kOut.m_iClassID, pcMethod, pcParamCode);
	VE_ASSERT(kOut.m_iMethodID);
}
//--------------------------------------------------------------------------
void VeAndroid::GetMethodInfo(JniMethodInfo& kOut, const VeChar8* pcClass,
	const VeChar8* pcMethod, const VeChar8* pcParamCode)
{
	VE_ASSERT(pcClass && pcMethod && pcParamCode);
	kOut.m_pkEnv = GetJNIEnv();
	VE_ASSERT(kOut.m_pkEnv);
	kOut.m_iClassID = GetClassID(pcClass);
	VE_ASSERT(kOut.m_iClassID);
	kOut.m_iMethodID = kOut.m_pkEnv->GetMethodID(kOut.m_iClassID, pcMethod, pcParamCode);
	VE_ASSERT(kOut.m_iMethodID);
}
//--------------------------------------------------------------------------
