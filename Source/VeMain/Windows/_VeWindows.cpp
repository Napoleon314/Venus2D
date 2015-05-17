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
#include "_VeWindows.h"

//--------------------------------------------------------------------------
struct DisplayData : public VeRefObject
{
	VeChar8 m_acDeviceName[32];
};
//--------------------------------------------------------------------------
struct DisplayModeData : public VeRefObject
{
	DEVMODEA m_kDeviceMode;
	VeFloat32 m_f32ScaleX;
	VeFloat32 m_f32ScaleY;
};
//--------------------------------------------------------------------------
struct WindowData : public VeRefObject
{
	VeDevice::Window* m_pkWindow;
	HWND m_hWnd;
	HDC m_hHdc;
	HDC m_hMdc;
	HIMC m_hImc;
	HBITMAP m_hHbm;
	WNDPROC m_pfuncWndProc;
	VE_BOOL m_bCreated;
	WPARAM m_u32MouseButtonFlags;
	VE_BOOL m_bExpectedResize;
	VE_BOOL m_bInTitleClick;
	VE_BOOL m_bInModalLoop;
};
//--------------------------------------------------------------------------
HWND VeWindows::GetWindowHandle()
{
	if(m_pkWindow)
	{
		WindowData* pkData = (WindowData*)(VeRefObject*)m_pkWindow->m_spDriverData;
		if(pkData)
		{
			return pkData->m_hWnd;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------------
VE_BOOL VeWindows::GetDisplayMode(LPCSTR deviceName, DWORD index,
	VeDevice::DisplayMode* pkMode)
{
	DisplayModeData* pkData;
	DEVMODEA kDevMode;
	HDC hHdc;

	kDevMode.dmSize = sizeof(kDevMode);
	kDevMode.dmDriverExtra = 0;
	if(!EnumDisplaySettings(deviceName, index, &kDevMode)) return VE_FALSE;

	pkData = VE_NEW DisplayModeData;
	if (!pkData) return VE_FALSE;

	pkData->m_kDeviceMode = kDevMode;
	pkData->m_kDeviceMode.dmFields =
		(DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY |
		DM_DISPLAYFLAGS);
	pkData->m_f32ScaleX = 1.0f;
	pkData->m_f32ScaleY = 1.0f;

	pkMode->m_u32Format = VeRenderer::FMT_UNKNOWN;
	pkMode->w = kDevMode.dmPelsWidth;
	pkMode->h = kDevMode.dmPelsHeight;
	pkMode->m_i32RefreshRate = kDevMode.dmDisplayFrequency;
	pkMode->m_spDriverData = pkData;

	if (index == ENUM_CURRENT_SETTINGS
		&& (hHdc = CreateDC(deviceName, NULL, NULL, NULL)) != NULL)
	{
			char bmi_data[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
			LPBITMAPINFO bmi;
			HBITMAP hbm;
			int logical_width = GetDeviceCaps( hHdc, HORZRES );
			int logical_height = GetDeviceCaps( hHdc, VERTRES );

			pkData->m_f32ScaleX = (float)logical_width / kDevMode.dmPelsWidth;
			pkData->m_f32ScaleY = (float)logical_height / kDevMode.dmPelsHeight;
			pkMode->w = logical_width;
			pkMode->h = logical_height;

			VeZeroMemory(bmi_data, sizeof(bmi_data));
			bmi = (LPBITMAPINFO) bmi_data;
			bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

			hbm = CreateCompatibleBitmap(hHdc, 1, 1);
			GetDIBits(hHdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
			GetDIBits(hHdc, hbm, 0, 1, NULL, bmi, DIB_RGB_COLORS);
			DeleteObject(hbm);
			DeleteDC(hHdc);
			if (bmi->bmiHeader.biCompression == BI_BITFIELDS) {
				switch (*(VeUInt32 *) bmi->bmiColors) {
				case 0x00FF0000:
					pkMode->m_u32Format = VE_PIXELFORMAT_RGB888;
					break;
				case 0x000000FF:
					pkMode->m_u32Format = VE_PIXELFORMAT_BGR888;
					break;
				case 0xF800:
					pkMode->m_u32Format = VE_PIXELFORMAT_RGB565;
					break;
				case 0x7C00:
					pkMode->m_u32Format = VE_PIXELFORMAT_RGB555;
					break;
				}
			} else if (bmi->bmiHeader.biBitCount == 8) {
				pkMode->m_u32Format = VE_PIXELFORMAT_INDEX8;
			} else if (bmi->bmiHeader.biBitCount == 4) {
				pkMode->m_u32Format = VE_PIXELFORMAT_INDEX4LSB;
			}
	}
	else
	{
		if ((kDevMode.dmFields & DM_BITSPERPEL) == DM_BITSPERPEL) {
			switch (kDevMode.dmBitsPerPel) {
			case 32:
				pkMode->m_u32Format = VE_PIXELFORMAT_RGB888;
				break;
			case 24:
				pkMode->m_u32Format = VE_PIXELFORMAT_RGB24;
				break;
			case 16:
				pkMode->m_u32Format = VE_PIXELFORMAT_RGB565;
				break;
			case 15:
				pkMode->m_u32Format = VE_PIXELFORMAT_RGB555;
				break;
			case 8:
				pkMode->m_u32Format = VE_PIXELFORMAT_INDEX8;
				break;
			case 4:
				pkMode->m_u32Format = VE_PIXELFORMAT_INDEX4LSB;
				break;
			}
		}
	}
	return VE_TRUE;
}
//--------------------------------------------------------------------------
VE_BOOL VeWindows::AddDisplay(LPSTR DeviceName)
{
	VeDevice::VideoDisplay kDisplay;
	DisplayData* pkDisplayData;
	VeDevice::DisplayMode kMode;
	DISPLAY_DEVICE kDevice;
	if(!GetDisplayMode(DeviceName, ENUM_CURRENT_SETTINGS, &kMode))
	{
		return VE_FALSE;
	}
	pkDisplayData = VE_NEW DisplayData;
	if(!pkDisplayData)
	{
		return VE_FALSE;
	}
	VeStrcpy(pkDisplayData->m_acDeviceName, DeviceName);
	
	kDevice.cb = sizeof(kDevice);
	if (EnumDisplayDevices(DeviceName, 0, &kDevice, 0))
	{
		kDisplay.m_kName = kDevice.DeviceString;
	}
	kDisplay.m_kDesktopMode = kMode;
	kDisplay.m_kCurrentMode = kMode;
	kDisplay.m_spDriverData = pkDisplayData;
	m_kDisplays.PushBack(kDisplay);
	return VE_TRUE;
}
//--------------------------------------------------------------------------
#define STYLE_BASIC         (WS_VISIBLE | WS_CLIPCHILDREN)
#define STYLE_FULLSCREEN    (WS_POPUP)
#define STYLE_BORDERLESS    (WS_POPUP)
#define STYLE_NORMAL        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
#define STYLE_RESIZABLE     (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define STYLE_MASK          (STYLE_FULLSCREEN | STYLE_BORDERLESS | STYLE_NORMAL | STYLE_RESIZABLE)
//--------------------------------------------------------------------------
VeDWord VeWindows::GetWindowStyle(Window* pkWindow)
{
	DWORD dwStyle = 0;
	if(pkWindow->m_u32Flags & WINDOW_FULLSCREEN)
	{
		dwStyle |= STYLE_FULLSCREEN;
	}
	else
	{
		if(pkWindow->m_u32Flags & WINDOW_BORDERLESS)
		{
			dwStyle |= STYLE_BORDERLESS;
		}
		else
		{
			dwStyle |= STYLE_NORMAL;
		}
		if(pkWindow->m_u32Flags & WINDOW_RESIZABLE)
		{
			dwStyle |= STYLE_RESIZABLE;
		}
	}
	return dwStyle;
}
//--------------------------------------------------------------------------
LRESULT CALLBACK VeWindows::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam,
	LPARAM lParam)
{
	if(((VeWindows*)g_pDevice)->IMEHandleMessage(hWnd, uMessage, wParam, lParam))
		return 0;

	switch(uMessage)
	{
	case WM_SHOWWINDOW:
		{
			if(wParam) ((VeWindows*)g_pDevice)->Show();
			else ((VeWindows*)g_pDevice)->Hide();
		}
		break;
	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_MAXIMIZED:
			((VeWindows*)g_pDevice)->Active();
			g_pRenderer->ResizeBuffer(LOWORD(lParam), HIWORD(lParam));
			break;
		case SIZE_RESTORED:
			((VeWindows*)g_pDevice)->Active();
			g_pRenderer->ResizeBuffer(LOWORD(lParam), HIWORD(lParam));
			break;
		case SIZE_MINIMIZED:
			((VeWindows*)g_pDevice)->Inactive();
			break;
		default:
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
		}
		break;
	case WM_ACTIVATE:
		if(LOWORD(wParam) != WA_INACTIVE)
		{
			((VeWindows*)g_pDevice)->Active();
		}
		else if(LOWORD(wParam) == WA_INACTIVE)
		{
			((VeWindows*)g_pDevice)->Inactive();
		}
		break;
	case WM_LBUTTONDOWN:
		g_pMouse->ProcessButtonDown(VeMouse::BTN_BUTTON0, lParam);
		break;
	case WM_RBUTTONDOWN:
		g_pMouse->ProcessButtonDown(VeMouse::BTN_BUTTON1, lParam);
		break;
	case WM_MBUTTONDOWN:
		g_pMouse->ProcessButtonDown(VeMouse::BTN_BUTTON2, lParam);
		break;
	case WM_LBUTTONUP:
		g_pMouse->ProcessButtonUp(VeMouse::BTN_BUTTON0, lParam);
		break;
	case WM_RBUTTONUP:
		g_pMouse->ProcessButtonUp(VeMouse::BTN_BUTTON1, lParam);
		break;
	case WM_MBUTTONUP:
		g_pMouse->ProcessButtonUp(VeMouse::BTN_BUTTON2, lParam);
		break;
	case WM_MOUSEMOVE:
		g_pMouse->ProcessCursorMove(lParam);
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		g_pKeyboard->OnKeyUp(VeKeyboard::TranslateKey(wParam));
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		g_pKeyboard->OnKeyDown(VeKeyboard::TranslateKey(wParam));
		break;
	case WM_CLOSE:
		g_pApplication->QuitApp();
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------------------------------
VeWindows::VeWindows(VeStartParams& kParams)
	: VeDevice(TYPE_WINDOWS, kParams)
{

}
//--------------------------------------------------------------------------
VeWindows::~VeWindows()
{

}
//--------------------------------------------------------------------------
void VeWindows::_Init()
{
	InitDisplayModes();
}
//--------------------------------------------------------------------------
void VeWindows::_Term()
{
	TermDisplayModes();
}
//--------------------------------------------------------------------------
void VeWindows::_CreateWindow(Window* pkWindow)
{
	WNDCLASSEXA kClass;
	kClass.cbSize = sizeof(WNDCLASSEXA);
	kClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	kClass.lpfnWndProc = WndProc;
	kClass.cbClsExtra = 0;
	kClass.cbWndExtra = 0;
	kClass.hInstance = m_kParams.m_hInstance;
	kClass.hIcon = 0;
	kClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	kClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	kClass.lpszMenuName = NULL;
	kClass.lpszClassName = m_kParams.m_pcAppName;
	kClass.hIconSm = 0;
	VE_ASSERT_NOT_EQ(RegisterClassExA(&kClass), VE_FALSE);
	HWND hWnd;
	RECT kRect;
	DWORD dwStyle = STYLE_BASIC;
	VeInt32 x, y;
	VeInt32 w, h;
	dwStyle |= GetWindowStyle(pkWindow);
	kRect.left = pkWindow->x;
	kRect.top = pkWindow->y;
	kRect.right = pkWindow->x + pkWindow->w;
	kRect.bottom = pkWindow->y + pkWindow->h;
	AdjustWindowRectEx(&kRect, dwStyle, FALSE, 0);
	x = kRect.left;
	y = kRect.top;
	w = (kRect.right - kRect.left);
	h = (kRect.bottom - kRect.top);
	hWnd = CreateWindowA(m_kParams.m_pcAppName, "", dwStyle, x, y, w, h, NULL, NULL,
		m_kParams.m_hInstance, NULL);
	VE_ASSERT(hWnd);
	_PumpEvents();
	SetupWindowData(pkWindow, hWnd, VE_TRUE);
	_DisableIME(pkWindow);
}
//--------------------------------------------------------------------------
void VeWindows::_DestoryWindow(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	if(pkData)
	{
		_EnableIME(pkWindow);
		ReleaseDC(pkData->m_hWnd, pkData->m_hHdc);
		if(pkData->m_bCreated)
		{
			DestroyWindow(pkData->m_hWnd);
		}
		else
		{
			if(pkData->m_pfuncWndProc != NULL)
			{
#				ifdef GWLP_WNDPROC
				SetWindowLongPtr(pkData->m_hWnd, GWLP_WNDPROC, (LONG_PTR)pkData->m_pfuncWndProc);
#				else
				SetWindowLong(pkData->m_hWnd, GWL_WNDPROC, (LONG_PTR)pkData->m_pfuncWndProc);
#				endif
			}
		}
		pkWindow->m_spDriverData = NULL;
	}

	WNDCLASSEXA kClass;
	if(GetClassInfoExA(m_kParams.m_hInstance, m_kParams.m_pcAppName, &kClass))
	{
		UnregisterClass(m_kParams.m_pcAppName, m_kParams.m_hInstance);
	}
}
//--------------------------------------------------------------------------
void VeWindows::_SetWindowTitle(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	VeUInt32 u32Len = MultiByteToWideChar(CP_UTF8, 0, pkWindow->m_kTitle, -1, NULL, 0);
	VeChar16* wszGBK = VeAlloc(VeChar16, u32Len + 1);
	VeZeroMemory(wszGBK, sizeof(VeChar16) * (u32Len + 1));
	MultiByteToWideChar(CP_UTF8, 0, pkWindow->m_kTitle, -1, wszGBK, u32Len);
	u32Len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	VeChar8* szGBK = VeAlloc(VeChar8, u32Len + 1);
	VeZeroMemory(szGBK, sizeof(VeChar8) * (u32Len + 1));
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, u32Len, NULL, NULL);
	SetWindowText(pkData->m_hWnd, szGBK);
	VeFree(wszGBK);
	VeFree(szGBK);
}
//--------------------------------------------------------------------------
void VeWindows::_SetWindowPosition(Window* pkWindow)
{
	SetWindowPositionInternal(pkWindow, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOACTIVATE);
}
//--------------------------------------------------------------------------
void VeWindows::_SetWindowSize(Window* pkWindow)
{
	SetWindowPositionInternal(pkWindow, SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOACTIVATE);
}
//--------------------------------------------------------------------------
void VeWindows::_ShowWindow(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	::ShowWindow(pkData->m_hWnd, SW_HIDE);
}
//--------------------------------------------------------------------------
void VeWindows::_HideWindow(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	::ShowWindow(pkData->m_hWnd, SW_SHOW);
}
//--------------------------------------------------------------------------
void VeWindows::_RaiseWindow(Window* pkWindow)
{
	SetWindowPositionInternal(pkWindow, SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOSIZE);
}
//--------------------------------------------------------------------------
void VeWindows::_MaximizeWindow(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	pkData->m_bExpectedResize = TRUE;
	::ShowWindow(pkData->m_hWnd, SW_MAXIMIZE);
	pkData->m_bExpectedResize = FALSE;
}
//--------------------------------------------------------------------------
void VeWindows::_MinimizeWindow(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	::ShowWindow(pkData->m_hWnd, SW_MINIMIZE);
}
//--------------------------------------------------------------------------
void VeWindows::_RestoreWindow(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	pkData->m_bExpectedResize = TRUE;
	::ShowWindow(pkData->m_hWnd, SW_RESTORE);
	pkData->m_bExpectedResize = FALSE;
}
//--------------------------------------------------------------------------
void VeWindows::_SetWindowBordered(Window* pkWindow, bool bBordered)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	DWORD dwStyle = GetWindowLong(pkData->m_hWnd, GWL_STYLE);
	if(bBordered)
	{
		dwStyle &= ~STYLE_BORDERLESS;
		dwStyle |= STYLE_NORMAL;
	}
	else
	{
		dwStyle &= ~STYLE_NORMAL;
		dwStyle |= STYLE_BORDERLESS;
	}
	SetWindowLong(pkData->m_hWnd, GWL_STYLE, dwStyle);
	SetWindowPositionInternal(pkWindow, SWP_NOCOPYBITS | SWP_FRAMECHANGED | SWP_NOREPOSITION | SWP_NOZORDER |SWP_NOACTIVATE | SWP_NOSENDCHANGING);
}
//--------------------------------------------------------------------------
void VeWindows::_SetWindowFullscreen(Window* pkWindow,
	VideoDisplay* pkDisplay, bool bFullscreen)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	HWND hWnd = pkData->m_hWnd;
	RECT kRect;
	VeRect kBounds;
	DWORD dwStyle;
	HWND hTop;
	BOOL bMenu;
	VeInt32 x, y;
	VeInt32 w, h;
	if((pkWindow->m_u32Flags & (WINDOW_FULLSCREEN | WINDOW_INPUT_FOCUS))
		== (WINDOW_FULLSCREEN | WINDOW_INPUT_FOCUS))
	{
		hTop = HWND_TOPMOST;
	}
	else
	{
		hTop = HWND_NOTOPMOST;
	}
	dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	dwStyle &= ~STYLE_MASK;
	dwStyle |= GetWindowStyle(pkWindow);
	_GetDisplayBounds(*pkDisplay, kBounds);
	if(bFullscreen)
	{
		x = kBounds.x;
		y = kBounds.y;
		w = kBounds.w;
		h = kBounds.h;
	}
	else
	{
		kRect.left = 0;
		kRect.top = 0;
		kRect.right = pkWindow->m_kWindowed.w;
		kRect.bottom = pkWindow->m_kWindowed.h;
		bMenu = (dwStyle & WS_CHILDWINDOW) ? FALSE : (GetMenu(hWnd) != NULL);
		AdjustWindowRectEx(&kRect, dwStyle, bMenu, 0);
		w = (kRect.right - kRect.left);
		h = (kRect.bottom - kRect.top);
		x = pkWindow->m_kWindowed.x + kRect.left;
		y = pkWindow->m_kWindowed.y + kRect.top;
	}
	SetWindowLong(hWnd, GWL_STYLE, dwStyle);
	pkData->m_bExpectedResize = TRUE;
	SetWindowPos(hWnd, hTop, x, y, w, h, SWP_NOCOPYBITS | SWP_NOACTIVATE);
	pkData->m_bExpectedResize = FALSE;
}
//--------------------------------------------------------------------------
bool VeWindows::_SetWindowGammaRamp(Window* pkWindow,
	const VeUInt16* pu16Ramp)
{
	VideoDisplay* pkDisplay = GetDisplayForWindow(pkWindow);
	VE_ASSERT(pkDisplay);
	DisplayData* pkData = (DisplayData*)(VeRefObject*)(pkDisplay->m_spDriverData);
	HDC hHdc;
	BOOL bSucceeded = FALSE;
	hHdc = CreateDC(pkData->m_acDeviceName, NULL, NULL, NULL);
	if(hHdc)
	{
		bSucceeded = SetDeviceGammaRamp(hHdc, (LPVOID)pu16Ramp);
		DeleteDC(hHdc);
	}
	return bSucceeded ? true : false;
}
//--------------------------------------------------------------------------
bool VeWindows::_GetWindowGammaRamp(Window* pkWindow,
	VeUInt16* pu16Ramp)
{
	VideoDisplay* pkDisplay = GetDisplayForWindow(pkWindow);
	VE_ASSERT(pkDisplay);
	DisplayData* pkData = (DisplayData*)(VeRefObject*)(pkDisplay->m_spDriverData);
	HDC hHdc;
	BOOL bSucceeded = FALSE;
	hHdc = CreateDC(pkData->m_acDeviceName, NULL, NULL, NULL);
	if(hHdc)
	{
		bSucceeded = GetDeviceGammaRamp(hHdc, (LPVOID)pu16Ramp);
		DeleteDC(hHdc);
	}
	return bSucceeded ? true : false;
}
//--------------------------------------------------------------------------
void VeWindows::_SetWindowGrab(Window* pkWindow, bool bGrabbed)
{

}
//--------------------------------------------------------------------------
void VeWindows::_PumpEvents()
{
    MSG kMessage;
    while(PeekMessage(&kMessage, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&kMessage);
		DispatchMessage(&kMessage);
    }
}
//--------------------------------------------------------------------------
void VeWindows::_EnableIME(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	if(pkData->m_hImc)
	{
		ImmAssociateContext(pkData->m_hWnd, pkData->m_hImc);
		ImmReleaseContext(pkData->m_hWnd, pkData->m_hImc);
		pkData->m_hImc = NULL;
	}
}
//--------------------------------------------------------------------------
void VeWindows::_DisableIME(Window* pkWindow)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	if(!pkData->m_hImc)
	{
		pkData->m_hImc = ImmGetContext(pkData->m_hWnd);
		ImmAssociateContext(pkData->m_hWnd, NULL);
	}
}
//--------------------------------------------------------------------------
bool VeWindows::IMEHandleMessage(HWND hWnd, UINT uMessage, WPARAM wParam,
	LPARAM& lParam)
{
	bool bRes(false);

	switch(uMessage)
	{
	case WM_INPUTLANGCHANGE:
		break;
	case WM_IME_SETCONTEXT:
		//lParam = 0;
		break;
	case WM_IME_COMPOSITION:
		{
			HIMC hImc = ImmGetContext(hWnd);
			if(hImc)
			{
				LONG lRet;
				VeChar16 szCompStr[VE_UINT8_MAX];
				if(lParam & GCS_RESULTSTR)
				{
					lRet = ImmGetCompositionStringW(hImc, GCS_RESULTSTR, szCompStr, VE_UINT8_MAX) / sizeof(VeChar16);
					szCompStr[lRet] = 0;
					m_kInputMethodEvent.Callback(szCompStr, VeUInt32(lRet));
					bRes = true;
				}
				ImmReleaseContext(hWnd, hImc);
			}
		}
		break;
	case WM_CHAR:
		{
			VeChar16 acChar[2] = { (VeChar16)wParam, L'\0' };
			m_kInputMethodEvent.Callback(acChar, 1);
			bRes = true;
		}
		break;
	default:
		break;
	}
	return bRes;
}
//--------------------------------------------------------------------------
void VeWindows::InitDisplayModes()
{
	DISPLAY_DEVICE kDevice;
	kDevice.cb = sizeof(DISPLAY_DEVICE);
	for(VeInt32 i32Pass(0); i32Pass < 2; ++i32Pass)
	{
		for(VeDWord i(0); ; ++i)
		{
			VeChar8 acDeviceName[32];
			if(!EnumDisplayDevicesA(NULL, i, &kDevice, 0)) 
				break;
			if(!(kDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP))
				continue;
			if(i32Pass == 0)
			{
				if(!(kDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
					continue;
			}
			else
			{
				if(kDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
					continue;
			}
			VeStrcpy(acDeviceName, kDevice.DeviceName);
			VeDWord dwCount(0);
			for(VeDWord j(0); ; ++j)
			{
				if(!EnumDisplayDevices(acDeviceName, j, &kDevice, 0))
					break;
				if(!(kDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP))
					continue;
				if(i32Pass == 0)
				{
					if(!(kDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
						continue;
				}
				else
				{
					if(kDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
						continue;
				}
				dwCount += AddDisplay(kDevice.DeviceName);
			}
			if(dwCount == 0)
			{
				AddDisplay(acDeviceName);
			}
		}
	}
	VE_ASSERT(m_kDisplays.Size());
}
//--------------------------------------------------------------------------
void VeWindows::TermDisplayModes()
{
	m_kDisplays.Clear();
}
//--------------------------------------------------------------------------
void VeWindows::_GetDisplayBounds(VideoDisplay& kDisplay, VeRect& kRect)
{
	DisplayModeData* pkData = (DisplayModeData*)(VeRefObject*)(kDisplay.m_kCurrentMode.m_spDriverData);
	kRect.x = (VeInt32)VeCeilf(pkData->m_kDeviceMode.dmPosition.x * pkData->m_f32ScaleX);
	kRect.y = (VeInt32)VeCeilf(pkData->m_kDeviceMode.dmPosition.y * pkData->m_f32ScaleY);
	kRect.w = (VeInt32)VeCeilf(pkData->m_kDeviceMode.dmPelsWidth * pkData->m_f32ScaleX);
	kRect.h = (VeInt32)VeCeilf(pkData->m_kDeviceMode.dmPelsHeight * pkData->m_f32ScaleY);
}
//--------------------------------------------------------------------------
void VeWindows::_GetDisplayModes(VideoDisplay& kDisplay)
{
	DisplayData* pkData = (DisplayData*)(VeRefObject*)(kDisplay.m_spDriverData);
	DisplayMode kMode;
	for(VeDWord i(0); ; ++i)
	{
		if(!GetDisplayMode(pkData->m_acDeviceName, i, &kMode))
		{
			break;
		}
		if(VE_ISPIXELFORMAT_INDEXED(kMode.m_u32Format))
		{
			continue;
		}
		if(kMode.m_u32Format != VE_PIXELFORMAT_UNKNOWN)
		{
			kDisplay.m_kDisplayModes[kMode.GetValue()] = kMode;
		}
	}
}
//--------------------------------------------------------------------------
void VeWindows::SetupWindowData(Window* pkWindow, HWND hWnd,
	VE_BOOL bCreated)
{
	WindowData* pkData = VE_NEW WindowData();
	pkData->m_pkWindow = pkWindow;
	pkData->m_hWnd = hWnd;
	pkData->m_hHdc = GetDC(hWnd);
	pkData->m_hImc = NULL;
	pkData->m_bCreated = bCreated;
	pkData->m_u32MouseButtonFlags = 0;

	pkWindow->m_spDriverData = pkData;

#	ifdef GWLP_WNDPROC
	pkData->m_pfuncWndProc = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_WNDPROC);
	if(pkData->m_pfuncWndProc == VeWindows::WndProc)
	{
		pkData->m_pfuncWndProc = NULL;
	}
	else
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)VeWindows::WndProc);
	}
#	else
	pkData->m_pfuncWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
	if(pkData->m_pfuncWndProc == VeWindows::WndProc)
	{
		pkData->m_pfuncWndProc = NULL;
	}
	else
	{
		SetWindowLong(hWnd, GWL_WNDPROC, (LONG_PTR)VeWindows::WndProc);
	}
#	endif

	{
		RECT kRect;
		if(GetClientRect(hWnd, &kRect))
		{
			int w = kRect.right;
			int h = kRect.bottom;
			if ((pkWindow->w && pkWindow->w != w) || (pkWindow->h && pkWindow->h != h))
			{
				SetWindowPositionInternal(pkWindow, SWP_NOCOPYBITS | SWP_NOZORDER | SWP_NOACTIVATE);
			}
			else
			{
				pkWindow->w = w;
				pkWindow->h = h;
			}
		}
	}
	{
		POINT kPoint;
		kPoint.x = 0;
		kPoint.y = 0;
		if(ClientToScreen(hWnd, &kPoint))
		{
			pkWindow->x = kPoint.x;
			pkWindow->y = kPoint.y;
		}
	}
	{
		DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
		if(dwStyle & WS_VISIBLE)
		{
			pkWindow->m_u32Flags |= WINDOW_SHOWN;
		}
		else
		{
			pkWindow->m_u32Flags &= ~WINDOW_SHOWN;
		}
		if(dwStyle & (WS_BORDER | WS_THICKFRAME))
		{
			pkWindow->m_u32Flags &= ~WINDOW_BORDERLESS;
		}
		else
		{
			pkWindow->m_u32Flags |= WINDOW_BORDERLESS;
		}
		if(dwStyle & WS_THICKFRAME)
		{
			pkWindow->m_u32Flags |= WINDOW_RESIZABLE;
		} else
		{
			pkWindow->m_u32Flags &= ~WINDOW_RESIZABLE;
		}
#		ifdef WS_MAXIMIZE
		if(dwStyle & WS_MAXIMIZE)
		{
			pkWindow->m_u32Flags |= WINDOW_MAXIMIZED;
		}
		else
#		endif
		{
			pkWindow->m_u32Flags &= ~WINDOW_MAXIMIZED;
		}
#		ifdef WS_MINIMIZE
		if(dwStyle & WS_MINIMIZE)
		{
			pkWindow->m_u32Flags |= WINDOW_MINIMIZED;
		}
		else
#		endif
		{
			pkWindow->m_u32Flags &= ~WINDOW_MINIMIZED;
		}
	}
	if(GetFocus() == hWnd)
	{
		pkWindow->m_u32Flags |= WINDOW_INPUT_FOCUS;
		//SetKeyboardFocus(data->window);
		if(pkWindow->m_u32Flags & WINDOW_INPUT_GRABBED)
		{
			RECT kRect;
			GetClientRect(hWnd, &kRect);
			ClientToScreen(hWnd, (LPPOINT) & kRect);
			ClientToScreen(hWnd, (LPPOINT) & kRect + 1);
			ClipCursor(&kRect);
		}
	}
}
//--------------------------------------------------------------------------
void VeWindows::SetWindowPositionInternal(Window* pkWindow,
	VeUInt32 u32Flags)
{
	WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	HWND hWnd = pkData->m_hWnd;
	RECT kRect;
	DWORD dwStyle;
	HWND hTop;
	BOOL bMenu;
	VeInt32 x, y;
	VeInt32 w, h;
	if((pkWindow->m_u32Flags & (WINDOW_FULLSCREEN | WINDOW_INPUT_FOCUS)) == (WINDOW_FULLSCREEN | WINDOW_INPUT_FOCUS))
	{
		hTop = HWND_TOPMOST;
	}
	else
	{
		hTop = HWND_NOTOPMOST;
	}
	dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	kRect.left = 0;
	kRect.top = 0;
	kRect.right = pkWindow->w;
	kRect.bottom = pkWindow->h;
	bMenu = (dwStyle & WS_CHILDWINDOW) ? FALSE : (GetMenu(hWnd) != NULL);
	AdjustWindowRectEx(&kRect, dwStyle, bMenu, 0);
	w = (kRect.right - kRect.left);
	h = (kRect.bottom - kRect.top);
	x = pkWindow->x + kRect.left;
	y = pkWindow->y + kRect.top;
	pkData->m_bExpectedResize = TRUE;
	SetWindowPos(hWnd, hTop, x, y, w, h, u32Flags);
	pkData->m_bExpectedResize = FALSE;
}
//--------------------------------------------------------------------------
void VeWindows::UpdateClipCursor(Window* pkWindow)
{
	//WindowData* pkData = (WindowData*)(VeRefObject*)pkWindow->m_spDriverData;
	//SDL_Mouse *mouse = SDL_GetMouse();

	///* Don't clip the cursor while we're in the modal resize or move loop */
	//if (data->in_title_click || data->in_modal_loop) {
	//	ClipCursor(NULL);
	//	return;
	//}

	//if ((mouse->relative_mode || (window->flags & SDL_WINDOW_INPUT_GRABBED)) &&
	//	(window->flags & SDL_WINDOW_INPUT_FOCUS)) {
	//		if (mouse->relative_mode && !mouse->relative_mode_warp) {
	//			LONG cx, cy;
	//			RECT rect;
	//			GetWindowRect(data->hwnd, &rect);

	//			cx = (rect.left + rect.right) / 2;
	//			cy = (rect.top + rect.bottom) / 2;

	//			/* Make an absurdly small clip rect */
	//			rect.left = cx - 1;
	//			rect.right = cx + 1;
	//			rect.top = cy - 1;
	//			rect.bottom = cy + 1;

	//			ClipCursor(&rect);
	//		} else {
	//			RECT rect;
	//			if (GetClientRect(data->hwnd, &rect) && !IsRectEmpty(&rect)) {
	//				ClientToScreen(data->hwnd, (LPPOINT) & rect);
	//				ClientToScreen(data->hwnd, (LPPOINT) & rect + 1);
	//				ClipCursor(&rect);
	//			}
	//		}
	//} else {
	//	ClipCursor(NULL);
	//}
}
//--------------------------------------------------------------------------
