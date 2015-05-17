////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeDevice.h
//  Version:     v1.00
//  Created:     17/3/2014 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#define VE_WINDOWPOS_UNDEFINED_MASK    0x1FFF0000
#define VE_WINDOWPOS_UNDEFINED_DISPLAY(X)  (VE_WINDOWPOS_UNDEFINED_MASK|(X))
#define VE_WINDOWPOS_UNDEFINED         VE_WINDOWPOS_UNDEFINED_DISPLAY(0)
#define VE_WINDOWPOS_ISUNDEFINED(X)    \
	(((X)&0xFFFF0000) == VE_WINDOWPOS_UNDEFINED_MASK)

#define VE_WINDOWPOS_CENTERED_MASK    0x2FFF0000
#define VE_WINDOWPOS_CENTERED_DISPLAY(X)  (VE_WINDOWPOS_CENTERED_MASK|(X))
#define VE_WINDOWPOS_CENTERED         VE_WINDOWPOS_CENTERED_DISPLAY(0)
#define VE_WINDOWPOS_ISCENTERED(X)    \
	(((X)&0xFFFF0000) == VE_WINDOWPOS_CENTERED_MASK)

enum
{
	VE_PIXELTYPE_UNKNOWN,
	VE_PIXELTYPE_INDEX1,
	VE_PIXELTYPE_INDEX4,
	VE_PIXELTYPE_INDEX8,
	VE_PIXELTYPE_PACKED8,
	VE_PIXELTYPE_PACKED16,
	VE_PIXELTYPE_PACKED32,
	VE_PIXELTYPE_ARRAYU8,
	VE_PIXELTYPE_ARRAYU16,
	VE_PIXELTYPE_ARRAYU32,
	VE_PIXELTYPE_ARRAYF16,
	VE_PIXELTYPE_ARRAYF32
};

enum
{
	VE_BITMAPORDER_NONE,
	VE_BITMAPORDER_4321,
	VE_BITMAPORDER_1234
};

enum
{
	VE_PACKEDORDER_NONE,
	VE_PACKEDORDER_XRGB,
	VE_PACKEDORDER_RGBX,
	VE_PACKEDORDER_ARGB,
	VE_PACKEDORDER_RGBA,
	VE_PACKEDORDER_XBGR,
	VE_PACKEDORDER_BGRX,
	VE_PACKEDORDER_ABGR,
	VE_PACKEDORDER_BGRA
};

enum
{
	VE_ARRAYORDER_NONE,
	VE_ARRAYORDER_RGB,
	VE_ARRAYORDER_RGBA,
	VE_ARRAYORDER_ARGB,
	VE_ARRAYORDER_BGR,
	VE_ARRAYORDER_BGRA,
	VE_ARRAYORDER_ABGR
};

enum
{
	VE_PACKEDLAYOUT_NONE,
	VE_PACKEDLAYOUT_332,
	VE_PACKEDLAYOUT_4444,
	VE_PACKEDLAYOUT_1555,
	VE_PACKEDLAYOUT_5551,
	VE_PACKEDLAYOUT_565,
	VE_PACKEDLAYOUT_8888,
	VE_PACKEDLAYOUT_2101010,
	VE_PACKEDLAYOUT_1010102
};

#define VE_DEFINE_PIXELFOURCC(A, B, C, D) VE_MAKE_ID(A, B, C, D)

#define VE_DEFINE_PIXELFORMAT(type, order, layout, bits, bytes) \
	((1 << 28) | ((type) << 24) | ((order) << 20) | ((layout) << 16) | \
	((bits) << 8) | ((bytes) << 0))

#define VE_PIXELFLAG(X)    (((X) >> 28) & 0x0F)
#define VE_PIXELTYPE(X)    (((X) >> 24) & 0x0F)
#define VE_PIXELORDER(X)   (((X) >> 20) & 0x0F)
#define VE_PIXELLAYOUT(X)  (((X) >> 16) & 0x0F)
#define VE_BITSPERPIXEL(X) (((X) >> 8) & 0xFF)
#define VE_BYTESPERPIXEL(X) \
	(VE_ISPIXELFORMAT_FOURCC(X) ? \
	((((X) == VE_PIXELFORMAT_YUY2) || \
	((X) == VE_PIXELFORMAT_UYVY) || \
	((X) == VE_PIXELFORMAT_YVYU)) ? 2 : 1) : (((X) >> 0) & 0xFF))

#define VE_ISPIXELFORMAT_INDEXED(format)   \
	(!VE_ISPIXELFORMAT_FOURCC(format) && \
	((VE_PIXELTYPE(format) == VE_PIXELTYPE_INDEX1) || \
	(VE_PIXELTYPE(format) == VE_PIXELTYPE_INDEX4) || \
	(VE_PIXELTYPE(format) == VE_PIXELTYPE_INDEX8)))

#define VE_ISPIXELFORMAT_ALPHA(format)   \
	(!VE_ISPIXELFORMAT_FOURCC(format) && \
	((VE_PIXELORDER(format) == VE_PACKEDORDER_ARGB) || \
	(VE_PIXELORDER(format) == VE_PACKEDORDER_RGBA) || \
	(VE_PIXELORDER(format) == VE_PACKEDORDER_ABGR) || \
	(VE_PIXELORDER(format) == VE_PACKEDORDER_BGRA)))

#define VE_ISPIXELFORMAT_FOURCC(format)    \
	((format) && (VE_PIXELFLAG(format) != 1))

#define VE_FULLSCREEN_VISIBLE(W) \
	(((W)->m_u32Flags & WINDOW_FULLSCREEN) && \
	((W)->m_u32Flags & WINDOW_SHOWN) && \
	!((W)->m_u32Flags & WINDOW_MINIMIZED))

enum
{
	VE_PIXELFORMAT_UNKNOWN,
	VE_PIXELFORMAT_INDEX1LSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX1, VE_BITMAPORDER_4321, 0,
	1, 0),
	VE_PIXELFORMAT_INDEX1MSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX1, VE_BITMAPORDER_1234, 0,
	1, 0),
	VE_PIXELFORMAT_INDEX4LSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX4, VE_BITMAPORDER_4321, 0,
	4, 0),
	VE_PIXELFORMAT_INDEX4MSB =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX4, VE_BITMAPORDER_1234, 0,
	4, 0),
	VE_PIXELFORMAT_INDEX8 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_INDEX8, 0, 0, 8, 1),
	VE_PIXELFORMAT_RGB332 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED8, VE_PACKEDORDER_XRGB,
	VE_PACKEDLAYOUT_332, 8, 1),
	VE_PIXELFORMAT_RGB444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XRGB,
	VE_PACKEDLAYOUT_4444, 12, 2),
	VE_PIXELFORMAT_RGB555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XRGB,
	VE_PACKEDLAYOUT_1555, 15, 2),
	VE_PIXELFORMAT_BGR555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XBGR,
	VE_PACKEDLAYOUT_1555, 15, 2),
	VE_PIXELFORMAT_ARGB4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ARGB,
	VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_RGBA4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_RGBA,
	VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_ABGR4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ABGR,
	VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_BGRA4444 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_BGRA,
	VE_PACKEDLAYOUT_4444, 16, 2),
	VE_PIXELFORMAT_ARGB1555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ARGB,
	VE_PACKEDLAYOUT_1555, 16, 2),
	VE_PIXELFORMAT_RGBA5551 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_RGBA,
	VE_PACKEDLAYOUT_5551, 16, 2),
	VE_PIXELFORMAT_ABGR1555 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_ABGR,
	VE_PACKEDLAYOUT_1555, 16, 2),
	VE_PIXELFORMAT_BGRA5551 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_BGRA,
	VE_PACKEDLAYOUT_5551, 16, 2),
	VE_PIXELFORMAT_RGB565 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XRGB,
	VE_PACKEDLAYOUT_565, 16, 2),
	VE_PIXELFORMAT_BGR565 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED16, VE_PACKEDORDER_XBGR,
	VE_PACKEDLAYOUT_565, 16, 2),
	VE_PIXELFORMAT_RGB24 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_ARRAYU8, VE_ARRAYORDER_RGB, 0,
	24, 3),
	VE_PIXELFORMAT_BGR24 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_ARRAYU8, VE_ARRAYORDER_BGR, 0,
	24, 3),
	VE_PIXELFORMAT_RGB888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_XRGB,
	VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_RGBX8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_RGBX,
	VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_BGR888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_XBGR,
	VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_BGRX8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_BGRX,
	VE_PACKEDLAYOUT_8888, 24, 4),
	VE_PIXELFORMAT_ARGB8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_ARGB,
	VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_RGBA8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_RGBA,
	VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_ABGR8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_ABGR,
	VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_BGRA8888 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_BGRA,
	VE_PACKEDLAYOUT_8888, 32, 4),
	VE_PIXELFORMAT_ARGB2101010 =
	VE_DEFINE_PIXELFORMAT(VE_PIXELTYPE_PACKED32, VE_PACKEDORDER_ARGB,
	VE_PACKEDLAYOUT_2101010, 32, 4),

	VE_PIXELFORMAT_YV12 =
	VE_DEFINE_PIXELFOURCC('Y', 'V', '1', '2'),
	VE_PIXELFORMAT_IYUV =
	VE_DEFINE_PIXELFOURCC('I', 'Y', 'U', 'V'),
	VE_PIXELFORMAT_YUY2 =
	VE_DEFINE_PIXELFOURCC('Y', 'U', 'Y', '2'),
	VE_PIXELFORMAT_UYVY =
	VE_DEFINE_PIXELFOURCC('U', 'Y', 'V', 'Y'),
	VE_PIXELFORMAT_YVYU =
	VE_DEFINE_PIXELFOURCC('Y', 'V', 'Y', 'U')
};

class VE_MAIN_API VeDevice : public VeSingleton<VeDevice>
{
	VeDeclareLuaExport(VeDevice);
public:
	enum Type
	{
		TYPE_WINDOWS,
		TYPE_MOBSIM,
		TYPE_LINUX,
		TYPE_MACOSX,
		TYPE_IOS,
		TYPE_ANDROID,
		TYPE_NONE,
		TYPE_ALL
	};
	VeLuaClassEnumDef(Type);

	enum Language
	{
		EN_US,
		ZH_CN,
		ZH_TW,
		LAN_MAX
	};
	VeLuaClassEnumDef(Language);

	enum WindowFlags
	{
		WINDOW_FULLSCREEN = 0x00000001,
		WINDOW_OPENGL = 0x00000002,
		WINDOW_SHOWN = 0x00000004,
		WINDOW_HIDDEN = 0x00000008,
		WINDOW_BORDERLESS = 0x00000010,
		WINDOW_RESIZABLE = 0x00000020,
		WINDOW_MINIMIZED = 0x00000040,
		WINDOW_MAXIMIZED = 0x00000080,
		WINDOW_INPUT_GRABBED = 0x00000100,
		WINDOW_INPUT_FOCUS = 0x00000200,
		WINDOW_MOUSE_FOCUS = 0x00000400,
		WINDOW_FULLSCREEN_DESKTOP = ( WINDOW_FULLSCREEN | 0x00001000 ),
		WINDOW_FOREIGN = 0x00000800,
		WINDOW_ALLOW_HIGHDPI = 0x00002000
	};

	enum WindowEventID
	{
		WINDOWEVENT_NONE,
		WINDOWEVENT_SHOWN,
		WINDOWEVENT_HIDDEN,
		WINDOWEVENT_EXPOSED,
		WINDOWEVENT_MOVED,
		WINDOWEVENT_RESIZED,
		WINDOWEVENT_SIZE_CHANGED,
		WINDOWEVENT_MINIMIZED,
		WINDOWEVENT_MAXIMIZED,
		WINDOWEVENT_RESTORED,
		WINDOWEVENT_ENTER,
		WINDOWEVENT_LEAVE,
		WINDOWEVENT_FOCUS_GAINED,
		WINDOWEVENT_FOCUS_LOST,
		WINDOWEVENT_CLOSE
	};

	struct DisplayMode
	{
		DisplayMode() : m_u32Format(0), w(0), h(0), m_i32RefreshRate(0) {}

		DisplayMode& operator = (const DisplayMode& kCopy)
		{
			m_u32Format = kCopy.m_u32Format;
			w = kCopy.w;
			h = kCopy.h;
			m_i32RefreshRate = kCopy.m_i32RefreshRate;
			m_spDriverData = kCopy.m_spDriverData;
			return *this;
		}

		VeUInt64 GetValue()
		{
			VeUInt32 hParam = VeUInt16(w) << 16 | VeUInt16(h) << 16;
			VeUInt32 lParam = VE_BITSPERPIXEL(m_u32Format) << 24
				| VE_BITSPERPIXEL(m_u32Format) << 16
				| VeUInt16(m_i32RefreshRate);
			return VeUInt64(hParam) << 32 | VeUInt64(lParam);
		}

		VeUInt32 m_u32Format;
		VeInt32 w, h;
		VeInt32 m_i32RefreshRate;
		VePointer<VeRefObject> m_spDriverData;
	};

	struct Window : public VeMemObject
	{
		Window() : x(0), y(0), w(0), h(0), m_i32MinWidth(0), m_i32MinHeight(0)
			,m_i32MaxWidth(0), m_i32MaxHeight(0), m_u32Flags(0), m_u32LastFullscreenFlags(0)
			, m_f32Brightness(0), m_pu16Gamma(NULL), m_pu16SavedGamma(NULL) {}

		VeString m_kTitle;
		VeInt32 x, y;
		VeInt32 w, h;
		VeInt32 m_i32MinWidth, m_i32MinHeight;
		VeInt32 m_i32MaxWidth, m_i32MaxHeight;
		VeUInt32 m_u32Flags;
		VeUInt32 m_u32LastFullscreenFlags;
		VeRect m_kWindowed;
		DisplayMode m_kFullscreenMode;
		VeFloat32 m_f32Brightness;
		VeUInt16* m_pu16Gamma;
		VeUInt16* m_pu16SavedGamma;
		VePointer<VeRefObject> m_spDriverData;
	};

	struct VideoDisplay
	{
		VideoDisplay() : m_pkFullscreenWindow(NULL) {}

		VideoDisplay& operator = (const VideoDisplay& kCopy)
		{
			m_kName = kCopy.m_kName;
			m_kDisplayModes = kCopy.m_kDisplayModes;
			m_kDesktopMode = kCopy.m_kDesktopMode;
			m_kCurrentMode = kCopy.m_kCurrentMode;
			m_pkFullscreenWindow = kCopy.m_pkFullscreenWindow;
			m_spDriverData = kCopy.m_spDriverData;
			return *this;
		}

		VeString m_kName;
		VeMap<VeUInt64,DisplayMode> m_kDisplayModes;
		DisplayMode m_kDesktopMode;
		DisplayMode m_kCurrentMode;
		Window* m_pkFullscreenWindow;
		VePointer<VeRefObject> m_spDriverData;
	};

	typedef VeEvent<const VeChar16*,VeUInt32> InputMethodEvent;

	typedef VeAbstractDelegate<const VeChar16*,VeUInt32> InputMethodDelegate;

	VeDevice(Type eType, VeStartParams& kParams);

	virtual ~VeDevice();

	VE_INLINE Type GetType();

	VE_INLINE VeUInt32 GetMask();

	VE_INLINE const VeChar8* GetName();

	VE_INLINE const VeStartParams& GetStartParams();

	VE_INLINE bool IsInited();

	VE_INLINE bool IsLuaDebug();

	VE_INLINE const VeChar8* GetDeviceID();

	VE_INLINE const VeChar8* GetDeviceName();

	VE_INLINE void SetLanguage(Language eLan);

	VE_INLINE Language GetLanguage();

	VE_INLINE void SetTransField(const VeChar8* pcName);

	VE_INLINE const VeChar8* GetTransField();

	const VeChar8* Translate(const VeChar8* pcKey);

	static void CreateDevice(VeStartParams& kParams);

	template<class T>
	T ReadConfig(const VeChar8* pcGroup, const VeChar8* pcName, T tDefault, bool bWrite = true)
	{
		VeString& kConfig = GetConfig(pcGroup, pcName);
		T tRes(tDefault);
		if(kConfig.Length())
		{
			kConfig.To(tRes);
		}
		if(bWrite) kConfig = VeString::From(tRes);
		return tRes;
	}

	template<class T>
	void WriteConfig(const VeChar8* pcGroup, const VeChar8* pcName, T tVal)
	{
		GetConfig(pcGroup, pcName) = VeString::From(tVal);
	}

	VeString& GetConfig(const VeChar8* pcGroup, const VeChar8* pcName);

	void SaveConfig();

	void Start();
	
	void Init();

	void Term();

	void CreateRenderWindowConfig();

	void DestoryRenderWindowConfig();

	void CreateRenderWindow(const VeChar8* pcTitle,
		VeInt32 x, VeInt32 y, VeInt32 w, VeInt32 h, VeUInt32 u32Flags);

	void CreateRenderWindow(const void* pvData);

	void DestoryRenderWindow();

	void SetWindowTitle(const VeChar8* pcTitle);

	const VeChar8* GetWindowTitle();

	void SetWindowPosition(VeInt32 x, VeInt32 y);

	void GetWindowPosition(VeInt32& x, VeInt32& y);

	void SetWindowFullscreen(VeUInt32 u32Flags);

	void ShowWindow();

	void HideWindow();

	void MaximizeWindow();

	void MinimizeWindow();

	bool IsDesktop();
    
    VideoDisplay* GetDisplayForWindow(Window* pkWindow);
    
    void EnableIME(InputMethodDelegate& kDelegate);
    
    void DisableIME();

#ifdef VE_PLATFORM_ANDROID

    struct JniMethodInfo
    {
        JNIEnv*		m_pkEnv;
        jclass		m_iClassID;
        jmethodID	m_iMethodID;
    };

    virtual JavaVM* GetJavaVM() = 0;

	virtual JNIEnv* GetJNIEnv() = 0;

	virtual void ClearJNIEnv() = 0;

	virtual VeString GetString(jstring jstrContent) = 0;

	virtual void GetStaticMethodInfo(JniMethodInfo& kOut, const VeChar8* pcClass,
		const VeChar8* pcMethod, const VeChar8* pcParamCode) = 0;

	virtual void GetMethodInfo(JniMethodInfo& kOut, const VeChar8* pcClass,
			const VeChar8* pcMethod, const VeChar8* pcParamCode) = 0;

#endif

protected:
	friend class VeInputManager;

	virtual void _Init() = 0;

	virtual void _Term() = 0;

	virtual void _GetDisplayBounds(VideoDisplay& kDisplay, VeRect& kRect);

	virtual void _GetDisplayModes(VideoDisplay& kDisplay) = 0;

	virtual void _CreateWindow(Window* pkWindow) = 0;

	virtual void _DestoryWindow(Window* pkWindow) = 0;

	virtual void _SetWindowTitle(Window* pkWindow) = 0;

	virtual void _SetWindowPosition(Window* pkWindow) = 0;

	virtual void _SetWindowSize(Window* pkWindow) = 0;

	virtual void _SetWindowMinimumSize(Window* pkWindow) = 0;

	virtual void _SetWindowMaximumSize(Window* pkWindow) = 0;

	virtual void _ShowWindow(Window* pkWindow) = 0;

	virtual void _HideWindow(Window* pkWindow) = 0;

	virtual void _RaiseWindow(Window* pkWindow) = 0;

	virtual void _MaximizeWindow(Window* pkWindow) = 0;

	virtual void _MinimizeWindow(Window* pkWindow) = 0;

	virtual void _RestoreWindow(Window* pkWindow) = 0;

	virtual void _SetWindowBordered(Window* pkWindow, bool bBordered) = 0;

	virtual void _SetWindowFullscreen(Window* pkWindow, VideoDisplay* pkDisplay, bool bFullscreen) = 0;

	virtual bool _SetWindowGammaRamp(Window* pkWindow, const VeUInt16* pu16Ramp) = 0;

	virtual bool _GetWindowGammaRamp(Window* pkWindow, VeUInt16* pu16Ramp) = 0;

	virtual void _SetWindowGrab(Window* pkWindow, bool bGrabbed) = 0;

	virtual void _PumpEvents() = 0;

	virtual void _EnableIME(Window* pkWindow) = 0;

	virtual void _DisableIME(Window* pkWindow) = 0;

	VeInt32 GetWindowDisplayIndex(Window* pkWindow);

	VeInt32 GetIndexOfDisplay(VideoDisplay* pkDisplay);

	void GetDisplayBounds(VeInt32 i32Index, VeRect& kRect);

	void UpdateFullscreenMode(Window* pkWindow, bool bFullscreen);

	void FinishWindowCreation(Window* pkWindow, VeUInt32 u32Flags);

	void ParseCmdLine();

	void LoadConfig();

	void Active();

	void Inactive();

	void Show();

	void Hide();

	VeDeclWriteDelegate(VeDevice, OnConfigSaved);

	const Type m_eType;
	VeStartParams m_kParams;
	VeString m_kVideoGroup;
	VeMap<VeString, VeMap<VeString,VeString> > m_kConfigMap;

	VeVector<VideoDisplay> m_kDisplays;
	Window* m_pkWindow;
	
	InputMethodEvent m_kInputMethodEvent;

	VeString m_kDeviceID;
	VeString m_kDeviceName;
	Language m_eLanguage;
	VeString m_kTransField;

	bool m_bInited;
	bool m_bLuaDebug;

};

namespace VeLuaBind
{
	VeLuaClassEnumFuncDef(VE_MAIN_API, VeDevice, Type);
	VeLuaClassEnumFuncDef(VE_MAIN_API, VeDevice, Language);
}

#define g_pDevice VeDevice::GetSingletonPtr()

#ifndef VE_NO_INLINE
#	include "VeDevice.inl"
#endif
