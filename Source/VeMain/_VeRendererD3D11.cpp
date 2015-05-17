////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   _VeRendererD3D11.cpp
//  Version:     v1.00
//  Created:     29/9/2012 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeMainPCH.h"
#include "_VeRendererD3D11.h"
#if defined(VE_PLATFORM_WIN)
#	include "Windows/_VeWindows.h"
#endif

//--------------------------------------------------------------------------
#ifdef VE_ENABLE_D3D11
//--------------------------------------------------------------------------
#define DXGI_LIB_NAME "dxgi.dll"
#define D3D11_LIB_NAME "d3d11.dll"
//--------------------------------------------------------------------------
typedef HRESULT (WINAPI * LPCREATEDXGIFACTORY)(REFIID, void **);
typedef HRESULT (WINAPI * LPD3D11CREATEDEVICE)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT32, D3D_FEATURE_LEVEL*, UINT, UINT32, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
//--------------------------------------------------------------------------
static VeSharedLib* s_pkDXGI = NULL;
static VeSharedLib* s_pkD3D11 = NULL;
static LPCREATEDXGIFACTORY s_pfuncCreateDXGIFactory = NULL;
static LPD3D11CREATEDEVICE s_pfuncD3D11CreateDevice = NULL;
//--------------------------------------------------------------------------
void VeRendererD3D11::Create()
{
	if(!GetSingletonPtr())
	{
		VeSharedLib* pkDXGI = VE_NEW VeSharedLib(DXGI_LIB_NAME);
		VeSharedLib* pkD3D11 = VE_NEW VeSharedLib(D3D11_LIB_NAME);
		if(pkDXGI->Load() && pkD3D11->Load())
		{
			s_pfuncCreateDXGIFactory = (LPCREATEDXGIFACTORY)pkDXGI->GetProc("CreateDXGIFactory1");
			s_pfuncD3D11CreateDevice = (LPD3D11CREATEDEVICE)pkD3D11->GetProc("D3D11CreateDevice");
			if(s_pfuncCreateDXGIFactory && s_pfuncD3D11CreateDevice)
			{
				VeRendererD3D11* pkRenderer = VE_NEW VeRendererD3D11();
				pkRenderer->m_pkLibDXGI = pkDXGI;
				pkRenderer->m_pkLibD3D11 = pkD3D11;
				return;
			}
		}
		VE_SAFE_DELETE(pkD3D11);
		VE_SAFE_DELETE(pkDXGI);
	}
}
//--------------------------------------------------------------------------
VeRendererD3D11::VeRendererD3D11()
	: m_pkLibDXGI(NULL), m_pkLibD3D11(NULL), m_pkDXGIFactory(NULL)
	, m_pkDevice(NULL), m_pkImmediateContext(NULL), m_pkSwapChain(NULL)
	, m_eCurrentLevel(D3D_FEATURE_LEVEL_11_0), m_bFullScreen(FALSE), m_u32Sync(0)
{

}
//--------------------------------------------------------------------------
VeRendererD3D11::~VeRendererD3D11()
{
	VE_ASSERT(m_kAdapterList.Empty());
	s_pfuncCreateDXGIFactory = NULL;
	s_pfuncD3D11CreateDevice = NULL;
	VE_ASSERT(m_pkLibD3D11);
	m_pkLibD3D11->Unload();
	VE_SAFE_DELETE(m_pkLibD3D11);
	VE_ASSERT(m_pkLibDXGI);
	m_pkLibDXGI->Unload();
	VE_SAFE_DELETE(m_pkLibDXGI);
}
//--------------------------------------------------------------------------
VeRenderer::API VeRendererD3D11::GetAPI()
{
	return API_D3D11;
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererD3D11::CheckCapability(Capability eCap)
{
	switch(eCap)
	{
	case CAP_DEPTH_TEX:
		return VE_TRUE;
	case CAP_ANISOTROPIC:
		return VE_TRUE;
	case CAP_MULTI_SAMPLE:
		return VE_TRUE;
	case CAP_DRAW_INSTANCE:
		return VE_TRUE;
	default:
		return 0;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::Init()
{
	VE_ASSERT(!m_bInited);

	VE_ASSERT_EQ(s_pfuncCreateDXGIFactory(__uuidof(IDXGIFactory1), (LPVOID*)&m_pkDXGIFactory), S_OK);

	VeUInt32 i(0);
	IDXGIAdapter1* pkAdapter;
	while(m_pkDXGIFactory->EnumAdapters1(i, &pkAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		m_kAdapterList.Resize(i + 1);
		m_kAdapterList[i].m_pkDXGIAdapter = pkAdapter;
		VeUInt32 j(0);
		IDXGIOutput* pkOutput;
		while(pkAdapter->EnumOutputs(j, &pkOutput) != DXGI_ERROR_NOT_FOUND)
		{
			m_kAdapterList[i].m_kOutputList.Resize(j + 1);
			Output& kOutput = m_kAdapterList[i].m_kOutputList[j];
			kOutput.m_pkDXGIOutput = pkOutput;
			VeVector<DXGI_MODE_DESC> m_kDesc;
			UINT uiNum;
			pkOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_SCALING, &uiNum, NULL);
			if(uiNum)
			{
				m_kDesc.Resize(uiNum);
				pkOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_SCALING, &uiNum, m_kDesc.Begin());
				kOutput.m_kC8R8ModeDefault = m_kDesc.Back();
				kOutput.m_kC8R8ModeDefault.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
				kOutput.m_kC8R8ModeDefault.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				for(VeUInt32 i(0); i < m_kDesc.Size(); ++i)
				{
					DXGI_MODE_DESC& kDesc = m_kDesc[i];
					Output::Mode kValue(kDesc.RefreshRate.Numerator / kDesc.RefreshRate.Denominator, VePair<VeUInt32,VeUInt32>(kDesc.Width, kDesc.Height));
					kOutput.m_kC8R8ModeSet.Insert(kValue);
				}
			}
			pkOutput->GetDisplayModeList(DXGI_FORMAT_R10G10B10A2_UNORM, DXGI_ENUM_MODES_SCALING, &uiNum, NULL);
			if(uiNum)
			{
				m_kDesc.Resize(uiNum);
				pkOutput->GetDisplayModeList(DXGI_FORMAT_R10G10B10A2_UNORM, DXGI_ENUM_MODES_SCALING, &uiNum, m_kDesc.Begin());
				kOutput.m_kC10R2ModeDefault = m_kDesc.Back();
				kOutput.m_kC10R2ModeDefault.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
				kOutput.m_kC10R2ModeDefault.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				for(VeUInt32 i(0); i < m_kDesc.Size(); ++i)
				{
					DXGI_MODE_DESC& kDesc = m_kDesc[i];
					Output::Mode kValue(kDesc.RefreshRate.Numerator / kDesc.RefreshRate.Denominator, VePair<VeUInt32,VeUInt32>(kDesc.Width, kDesc.Height));
					kOutput.m_kC10R2ModeSet.Insert(kValue);
				}
			}
			++j;
		}
		++i;
	}
	VE_ASSERT(m_kAdapterList.Size());

	VeUInt32 u32Flag(0);
	if(g_pDevice->ReadConfig("video", "debug", false))
		u32Flag |= D3D11_CREATE_DEVICE_DEBUG;

	D3D_FEATURE_LEVEL aeFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};
	VeUInt32 u32NumFeatureLevels = ARRAYSIZE(aeFeatureLevels);

	VeUInt32 u32Adapter = g_pDevice->ReadConfig("video", "adapter", 0);
	Adapter& kAdapterForUse = (m_kAdapterList.Size() > u32Adapter) ? m_kAdapterList[u32Adapter] : m_kAdapterList.Back();

	VE_ASSERT_EQ(s_pfuncD3D11CreateDevice(kAdapterForUse.m_pkDXGIAdapter, D3D_DRIVER_TYPE_UNKNOWN
		, NULL, u32Flag, aeFeatureLevels, u32NumFeatureLevels, D3D11_SDK_VERSION, &m_pkDevice
		, &m_eCurrentLevel, &m_pkImmediateContext), S_OK);

	DXGI_FORMAT eFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	if(g_pDevice->ReadConfig("video", "hdpi", true)) DXGI_FORMAT_R10G10B10A2_UNORM;

	DXGI_SWAP_CHAIN_DESC kDesc;
	VeZeroMemory(&kDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	kDesc.BufferCount = VE_D3D11_BUFFER_COUNT;
	kDesc.BufferDesc.Width = 0;
	kDesc.BufferDesc.Height = 0;
	kDesc.BufferDesc.Format = eFormat;
	kDesc.BufferDesc.RefreshRate.Numerator = g_pDevice->ReadConfig("video", "adapter", 60);
	kDesc.BufferDesc.RefreshRate.Denominator = 1;
	kDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	kDesc.OutputWindow = ((VeWindows*)g_pDevice)->GetWindowHandle();
	kDesc.SampleDesc.Count = 1;
	kDesc.SampleDesc.Quality = 0;
	kDesc.Windowed = TRUE;
	VE_ASSERT_EQ(m_pkDXGIFactory->CreateSwapChain(m_pkDevice, &kDesc, &m_pkSwapChain), S_OK);
	m_u32Sync = g_pDevice->ReadConfig("video", "sync", true) ? 1 : 0;

	InitGlobal();

	/*if(!g_bMaximized)
	{
		UpdateFullScreen();
	}*/
	UpdateBufferSize();
	VE_ASSERT_EQ(m_pkDXGIFactory->MakeWindowAssociation(((VeWindows*)g_pDevice)->GetWindowHandle(), DXGI_MWA_NO_ALT_ENTER), S_OK);
	ResetStateCache();
	m_bInited = true;
}
//--------------------------------------------------------------------------
void VeRendererD3D11::Term()
{
	VE_ASSERT(m_bInited);
	m_bInited = false;
	//if(m_bFullScreen) VE_ASSERT_EQ(m_pkSwapChain->SetFullscreenState(FALSE, NULL), S_OK);
	m_kAdapterList.Clear();
	TermGlobal();
	VE_SAFE_RELEASE(m_pkSwapChain);
	VE_SAFE_RELEASE(m_pkImmediateContext);
	VE_SAFE_RELEASE(m_pkDevice);
	VE_SAFE_RELEASE(m_pkDXGIFactory);
	/*if(g_bFullscreenInactive)
	{
		g_pStartConfig->SetFullScreen(true);
		g_bFullscreenInactive = false;
	}*/
}
//--------------------------------------------------------------------------
void VeRendererD3D11::GetMatrixPerspectiveFov(VeFloat32* pf32OutMat4x4,
	VeFloat32 fov, VeFloat32 znear, VeFloat32 zfar)
{
	VeMatrixPerspectiveFovLH_DX(pf32OutMat4x4, fov,
		GetHeightF() * GetInvWidthF(), znear, zfar);
}
//--------------------------------------------------------------------------
void VeRendererD3D11::Render()
{
	VeFloat32 af32Clear[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	m_pkImmediateContext->ClearRenderTargetView(m_spBackBufferRTV->m_pkRenderTargetView, af32Clear);
}
//--------------------------------------------------------------------------
void VeRendererD3D11::Present()
{
	m_pkSwapChain->Present(m_u32Sync, 0);
}
//--------------------------------------------------------------------------
void VeRendererD3D11::SetFullScreen(bool bEnable)
{
	/*bool bFullscreen = g_pStartConfig->IsFullScreen();
	if(bFullscreen != bEnable)
	{
		g_pStartConfig->SetFullScreen(bEnable);
		UpdateFullScreen();
	}*/
}
//--------------------------------------------------------------------------
//void VeRendererD3D11::SetDisplay(Display& kDisplay)
//{
	/*g_pStartConfig->SetWinStyle(kDisplay.m_eWinStyle);
	g_pStartConfig->SetResolution(kDisplay.m_u32Width, kDisplay.m_u32Height);
	g_pStartConfig->SetFormat(kDisplay.m_eFormat);
	g_pStartConfig->SetFullScreen(kDisplay.m_bFullscreen ? true : false);
	g_pStartConfig->SetOutput(kDisplay.m_u32Output);
	g_pStartConfig->SetRefreshRate(kDisplay.m_u32RefreshRate);
	UpdateFullScreen();*/
//}
//--------------------------------------------------------------------------
void VeRendererD3D11::ResizeWindow(VeUInt32 u32Width, VeUInt32 u32Height)
{
	/*if(!m_bFullScreen)
	{
		VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
		if(kResolution.m_u32Width != u32Width || kResolution.m_u32Height != u32Height)
		{
			g_pStartConfig->SetResolution(u32Width, u32Height);
			kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
			DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
			VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
			switch(eStyle)
			{
			case VeStringParser::STYLE_FIXED:
				dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
				break;
			case VeStringParser::STYLE_VARIBLE:
				dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
				break;
			case VeStringParser::STYLE_POPUP:
				dwStyle |= WS_POPUP;
				break;
			}
			RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
			AdjustWindowRect(&kRect, dwStyle, FALSE);
			VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
			VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
			switch(eDock)
			{
			case VeStringParser::DOCK_DEFAULT:
				break;
			case VeStringParser::DOCK_CORNER:
				i32Left = 0;
				i32Top = 0;
				break;
			case VeStringParser::DOCK_CENTER:
				{
					VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
					VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
					i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
					i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
				}
				break;
			}
			SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
			SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
				SWP_NOZORDER | SWP_NOACTIVATE);
			ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
		}
	}*/
}
//--------------------------------------------------------------------------
void VeRendererD3D11::ResizeBuffer(VeUInt32 u32Width, VeUInt32 u32Height)
{
	if(m_pkSwapChain)
	{
		if(GetWidth() != u32Width || GetHeight() != u32Height)
		{
			VE_SAFE_RELEASE(m_spBackBufferTEX->m_pkTexture2D);
			VE_SAFE_RELEASE(m_spBackBufferRTV->m_pkRenderTargetView);
			DXGI_FORMAT eFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
			if(g_pDevice->ReadConfig("video", "hdpi", true)) DXGI_FORMAT_R10G10B10A2_UNORM;
			VE_ASSERT_EQ(m_pkSwapChain->ResizeBuffers(VE_D3D11_BUFFER_COUNT, 0, 0, eFormat, 0), S_OK);
			UpdateBufferSize();
		}
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::OnActive()
{
	/*if(g_bFullscreenInactive)
	{
		SetFullScreen(true);
		g_bFullscreenInactive = false;
	}*/
}
//--------------------------------------------------------------------------
void VeRendererD3D11::OnInactive()
{
	/*if(m_bFullScreen)
	{
		g_bFullscreenInactive = true;
		SetFullScreen(false);
	}*/
}
//--------------------------------------------------------------------------
void VeRendererD3D11::UpdateBufferSize()
{
	if((!m_spBackBufferTEX->m_pkTexture2D))
	{
		VE_ASSERT(!m_spBackBufferRTV->m_pkRenderTargetView);
		VE_ASSERT_EQ(m_pkSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_spBackBufferTEX->m_pkTexture2D), S_OK);
		VE_ASSERT_EQ(m_pkDevice->CreateRenderTargetView(m_spBackBufferTEX->m_pkTexture2D, NULL, &m_spBackBufferRTV->m_pkRenderTargetView), S_OK);
		ResetStateCache();
		D3D11_TEXTURE2D_DESC kDesc;
		m_spBackBufferTEX->m_pkTexture2D->GetDesc(&kDesc);
		if(kDesc.Width != GetWidth() || kDesc.Height != GetHeight())
		{
			SetScreenSize(kDesc.Width, kDesc.Height);
			g_pApplication->OnBufferResized(GetWidth(), GetHeight());
		}
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::UpdateFullScreen()
{
	/*VeStringParser::Resolution kResolution = g_pStartConfig->GetConfig("Resolution", kResolution);
	VeUInt32 u32RefreshRate = g_pStartConfig->GetRefreshRate();
	DXGI_FORMAT eFormat = (g_pStartConfig->GetFormat() == VeStringParser::FMT_C8A8) ? DXGI_FORMAT_R8G8B8A8_UNORM : DXGI_FORMAT_R10G10B10A2_UNORM;
	bool bRefreshRateChanged(false), bResolutionChanged(false), bFormatChanged(false);

	if(g_pStartConfig->IsFullScreen())
	{
		Output::Mode kMode(u32RefreshRate, VePair<VeUInt32,VeUInt32>(kResolution.m_u32Width, kResolution.m_u32Height));
		VeUInt32 u32Adapter = g_pStartConfig->GetAdapter();
		VeUInt32 u32Output = g_pStartConfig->GetOutput();
		Adapter& kAdapterForUse = (m_kAdapterList.Size() > u32Adapter) ? m_kAdapterList[u32Adapter] : m_kAdapterList.Back();
		Output& kOutput = (kAdapterForUse.m_kOutputList.Size() > u32Output) ? kAdapterForUse.m_kOutputList[u32Output] : kAdapterForUse.m_kOutputList.Back();
		bool bNeedChangeMode(true);
		if(!g_pStartConfig->IsMaxScreen())
		{	
			if(eFormat == DXGI_FORMAT_R8G8B8A8_UNORM)
			{
				if(kOutput.m_kC8R8ModeSet.Find(kMode))
					bNeedChangeMode = false;
			}
			else if(eFormat == DXGI_FORMAT_R10G10B10A2_UNORM)
			{
				if(kOutput.m_kC10R2ModeSet.Find(kMode))
					bNeedChangeMode = false;
			}
		}
		if(bNeedChangeMode)
		{
			DXGI_MODE_DESC& kModeDefault = (eFormat == DXGI_FORMAT_R8G8B8A8_UNORM) ? kOutput.m_kC8R8ModeDefault : kOutput.m_kC10R2ModeDefault;
			kResolution.m_u32Width = kModeDefault.Width;
			kResolution.m_u32Height = kModeDefault.Height;
			u32RefreshRate = (VeUInt32)VeFloor(VeFloat64(kModeDefault.RefreshRate.Numerator) / VeFloat64(kModeDefault.RefreshRate.Denominator) + 0.5);
		}
	}

	DXGI_SWAP_CHAIN_DESC kDesc;
	VE_ASSERT_EQ(m_pkSwapChain->GetDesc(&kDesc), S_OK);
	if(u32RefreshRate != (kDesc.BufferDesc.RefreshRate.Numerator / kDesc.BufferDesc.RefreshRate.Denominator))
	{
		bRefreshRateChanged = true;
	}
	if(kResolution.m_u32Width != kDesc.BufferDesc.Width || kResolution.m_u32Height != kDesc.BufferDesc.Height)
	{
		bResolutionChanged = true;
	}
	if(eFormat != kDesc.BufferDesc.Format)
	{
		bFormatChanged = true;
	}

	if(g_pStartConfig->IsFullScreen())
	{
		if(m_bFullScreen)
		{
			if(bResolutionChanged)
			{
				VE_ASSERT_EQ(m_pkSwapChain->SetFullscreenState(FALSE, NULL), S_OK);
				SetWindowPos(g_hWindow, HWND_TOPMOST, 0, 0, kResolution.m_u32Width, kResolution.m_u32Height, SWP_NOACTIVATE);
				ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
			}
			if(bRefreshRateChanged || bFormatChanged)
			{
				DXGI_MODE_DESC kModeDesc;
				VeZeroMemory(&kModeDesc, sizeof(DXGI_MODE_DESC));
				kModeDesc.Width = kResolution.m_u32Width;
				kModeDesc.Height = kResolution.m_u32Height;
				kModeDesc.RefreshRate.Numerator = u32RefreshRate;
				kModeDesc.RefreshRate.Denominator = 1;
				kModeDesc.Format = eFormat;
				VE_ASSERT_EQ(m_pkSwapChain->ResizeTarget(&kModeDesc), S_OK);
			}
			BOOL bFullScreen;
			IDXGIOutput* pkOutputPre;
			VE_ASSERT_EQ(m_pkSwapChain->GetFullscreenState(&bFullScreen, &pkOutputPre), S_OK);
			VeUInt32 u32Adapter = g_pStartConfig->GetAdapter();
			VeUInt32 u32Output = g_pStartConfig->GetOutput();
			Adapter& kAdapterForUse = (m_kAdapterList.Size() > u32Adapter) ? m_kAdapterList[u32Adapter] : m_kAdapterList.Back();
			IDXGIOutput* pkOutput = (kAdapterForUse.m_kOutputList.Size() > u32Output) ? kAdapterForUse.m_kOutputList[u32Output].m_pkDXGIOutput : kAdapterForUse.m_kOutputList.Back().m_pkDXGIOutput;
			if((!bFullScreen) || (pkOutputPre != pkOutput))
			{
				VE_ASSERT_EQ(m_pkSwapChain->SetFullscreenState(TRUE, pkOutput), S_OK);
			}
			VE_SAFE_RELEASE(pkOutputPre);
		}
		else
		{
			g_bFullscreen = true;
			DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN | WS_POPUP;
			SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
			SetWindowPos(g_hWindow, HWND_TOPMOST, 0, 0, kResolution.m_u32Width, kResolution.m_u32Height, SWP_NOACTIVATE);
			SetWindowPos(g_hWindow, 0, 0,0, 0,0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
			if(bResolutionChanged)
			{
				ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
			}
			if(bRefreshRateChanged || bFormatChanged)
			{
				DXGI_MODE_DESC kModeDesc;
				VeZeroMemory(&kModeDesc, sizeof(DXGI_MODE_DESC));
				kModeDesc.Width = kResolution.m_u32Width;
				kModeDesc.Height = kResolution.m_u32Height;
				kModeDesc.RefreshRate.Numerator = u32RefreshRate;
				kModeDesc.RefreshRate.Denominator = 1;
				kModeDesc.Format = eFormat;
				VE_ASSERT_EQ(m_pkSwapChain->ResizeTarget(&kModeDesc), S_OK);
			}
			VeUInt32 u32Adapter = g_pStartConfig->GetAdapter();
			VeUInt32 u32Output = g_pStartConfig->GetOutput();
			Adapter& kAdapterForUse = (m_kAdapterList.Size() > u32Adapter) ? m_kAdapterList[u32Adapter] : m_kAdapterList.Back();
			IDXGIOutput* pkOutput = (kAdapterForUse.m_kOutputList.Size() > u32Output) ? kAdapterForUse.m_kOutputList[u32Output].m_pkDXGIOutput : kAdapterForUse.m_kOutputList.Back().m_pkDXGIOutput;
			VE_ASSERT_EQ(m_pkSwapChain->SetFullscreenState(TRUE, pkOutput), S_OK);
			m_bFullScreen = VE_TRUE;
		}
	}
	else if(m_bFullScreen)
	{
		g_bFullscreen = false;
		VE_ASSERT_EQ(m_pkSwapChain->SetFullscreenState(FALSE, NULL), S_OK);
		DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
		VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
		switch(eStyle)
		{
		case VeStringParser::STYLE_FIXED:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			break;
		case VeStringParser::STYLE_VARIBLE:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
			break;
		case VeStringParser::STYLE_POPUP:
			dwStyle |= WS_POPUP;
			break;
		}
		RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
		AdjustWindowRect(&kRect, dwStyle, FALSE);
		VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
		VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
		switch(eDock)
		{
		case VeStringParser::DOCK_DEFAULT:
			break;
		case VeStringParser::DOCK_CORNER:
			i32Left = 0;
			i32Top = 0;
			break;
		case VeStringParser::DOCK_CENTER:
			{
				VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
				VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
				i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
				i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
			}
			break;
		}
		SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
		SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
			SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
		m_bFullScreen = VE_FALSE;
	}
	else if(bResolutionChanged)
	{
		DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
		VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
		switch(eStyle)
		{
		case VeStringParser::STYLE_FIXED:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			break;
		case VeStringParser::STYLE_VARIBLE:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
			break;
		case VeStringParser::STYLE_POPUP:
			dwStyle |= WS_POPUP;
			break;
		}
		RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
		AdjustWindowRect(&kRect, dwStyle, FALSE);
		VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
		VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
		switch(eDock)
		{
		case VeStringParser::DOCK_DEFAULT:
			break;
		case VeStringParser::DOCK_CORNER:
			i32Left = 0;
			i32Top = 0;
			break;
		case VeStringParser::DOCK_CENTER:
			{
				VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
				VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
				i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
				i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
			}
			break;
		}
		SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
		SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
			SWP_NOZORDER | SWP_NOACTIVATE);
		ResizeBuffer(kResolution.m_u32Width, kResolution.m_u32Height);
	}
	else
	{
		DWORD dwPreStyle = GetWindowLong(g_hWindow, GWL_STYLE);
		DWORD dwStyle = WS_VISIBLE | WS_CLIPCHILDREN;
		VeStringParser::WinStyle eStyle = g_pStartConfig->GetConfig("WinStyle", VeStringParser::STYLE_FIXED);
		switch(eStyle)
		{
		case VeStringParser::STYLE_FIXED:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
			break;
		case VeStringParser::STYLE_VARIBLE:
			dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
			break;
		case VeStringParser::STYLE_POPUP:
			dwStyle |= WS_POPUP;
			break;
		}
		if(dwStyle != dwPreStyle)
		{
			RECT kRect = { 0, 0, kResolution.m_u32Width, kResolution.m_u32Height };
			AdjustWindowRect(&kRect, dwStyle, FALSE);
			VeInt32 i32Left(CW_USEDEFAULT), i32Top(CW_USEDEFAULT);
			VeStringParser::WinDock eDock = g_pStartConfig->GetConfig("WinDock", VeStringParser::DOCK_DEFAULT);
			switch(eDock)
			{
			case VeStringParser::DOCK_DEFAULT:
				break;
			case VeStringParser::DOCK_CORNER:
				i32Left = 0;
				i32Top = 0;
				break;
			case VeStringParser::DOCK_CENTER:
				{
					VeInt32 i32ScreenW = GetSystemMetrics(SM_CXSCREEN);
					VeInt32 i32ScreenH = GetSystemMetrics(SM_CYSCREEN);
					i32Left = ((i32ScreenW - kResolution.m_u32Width) >> 1) + kRect.left;
					i32Top = ((i32ScreenH - kResolution.m_u32Height) >> 1) + kRect.top;
				}
				break;
			}
			SetWindowLong(g_hWindow, GWL_STYLE, dwStyle);
			SetWindowPos(g_hWindow, HWND_NOTOPMOST, i32Left, i32Top, kRect.right - kRect.left, kRect.bottom - kRect.top,
				SWP_NOZORDER | SWP_NOACTIVATE);
		}
	}*/
}
//--------------------------------------------------------------------------
ID3D11Device* VeRendererD3D11::GetDevice()
{
	return m_pkDevice;
}
//--------------------------------------------------------------------------
ID3D11DeviceContext* VeRendererD3D11::GetImmediateContext()
{
	return m_pkImmediateContext;
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererD3D11::GetMultisampleLevelCount()
{
	return m_kSampleDescArray.Size();
}
//--------------------------------------------------------------------------
void VeRendererD3D11::EnumMultisampleLevel(VeUInt32 u32Index, VeUInt32& u32Count, VeUInt32& u32Quality)
{
	VE_ASSERT(u32Index < m_kSampleDescArray.Size());
	DXGI_SAMPLE_DESC& kDesc = m_kSampleDescArray[u32Index];
	u32Count = kDesc.Count;
	u32Quality = kDesc.Quality;
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateVertexShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROVertexShaderPtr* pspShader)
{
	VeROVertexShaderPtr spShader;
	GetRenderObject(pcName, spShader);
	if(!spShader)
	{
		spShader = VE_NEW VeROVertexShaderD3D11(pcName);
		AddObject(spShader);
	}
	kStream >> (*spShader);
	if(pspShader)
	{
		*pspShader = spShader;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreatePixelShader(const VeChar8* pcName, VeBinaryIStream& kStream, VeROPixelShaderPtr* pspShader)
{
	VeROPixelShaderPtr spShader;
	GetRenderObject(pcName, spShader);
	if(!spShader)
	{
		spShader = VE_NEW VeROPixelShaderD3D11(pcName);
		AddObject(spShader);
	}
	kStream >> (*spShader);
	if(pspShader)
	{
		*pspShader = spShader;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateBlendState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBlendStatePtr* pspBlendState)
{
	VeROBlendStatePtr spBlendState;
	GetRenderObject(pcName, spBlendState);
	if(!spBlendState)
	{
		spBlendState = VE_NEW VeROBlendStateD3D11(pcName);
		AddObject(spBlendState);
	}
	kStream >> (*spBlendState);
	if(pspBlendState)
	{
		*pspBlendState = spBlendState;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateDepthStencilState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRODepthStencilStatePtr* pspDepthStencilState)
{
	VeRODepthStencilStatePtr spDepthStencilState;
	GetRenderObject(pcName, spDepthStencilState);
	if(!spDepthStencilState)
	{
		spDepthStencilState = VE_NEW VeRODepthStencilStateD3D11(pcName);
		AddObject(spDepthStencilState);
	}
	kStream >> (*spDepthStencilState);
	if(pspDepthStencilState)
	{
		*pspDepthStencilState = spDepthStencilState;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateInputLayout(const VeChar8* pcName, VeBinaryIStream& kStream, VeROInputLayoutPtr* pspLayout)
{
	VeROInputLayoutPtr spLayout;
	GetRenderObject(pcName, spLayout);
	if(!spLayout)
	{
		spLayout = VE_NEW VeROInputLayoutD3D11(pcName);
		AddObject(spLayout);
	}
	kStream >> (*spLayout);
	if(pspLayout)
	{
		*pspLayout = spLayout;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateRasterizerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeRORasterizeStatePtr* pspRasterizeState)
{
	VeRORasterizeStatePtr spRSState;
	GetRenderObject(pcName, spRSState);
	if(!spRSState)
	{
		spRSState = VE_NEW VeRORasterizeStateD3D11(pcName);
		AddObject(spRSState);
	}
	kStream >> (*spRSState);
	if(pspRasterizeState)
	{
		*pspRasterizeState = spRSState;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateBuffer(const VeChar8* pcName, VeBinaryIStream& kStream, VeROBufferPtr* pspBuffer)
{
	VeROBufferPtr spBuffer;
	GetRenderObject(pcName, spBuffer);
	if(!spBuffer)
	{
		spBuffer = VE_NEW VeROBufferD3D11(pcName);
		AddObject(spBuffer);
	}
	kStream >> (*spBuffer);
	if(pspBuffer)
	{
		*pspBuffer = spBuffer;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateSamplerState(const VeChar8* pcName, VeBinaryIStream& kStream, VeROSamplerStatePtr* pspSamplerState)
{
	VeROSamplerStatePtr spSampler;
	GetRenderObject(pcName, spSampler);
	if(!spSampler)
	{
		spSampler = VE_NEW VeROSamplerStateD3D11(pcName);
		AddObject(spSampler);
	}
	kStream >> (*spSampler);
	if(pspSamplerState)
	{
		*pspSamplerState = spSampler;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateTexture2D(const VeChar8* pcName, VeBinaryIStream& kStream, VeROTexture2DPtr* pspTexture)
{
	VeROTexture2DPtr spTexture;
	GetRenderObject(pcName, spTexture);
	if(!spTexture)
	{
		spTexture = VE_NEW VeROTexture2DD3D11(pcName);
		AddObject(spTexture);
	}
	kStream >> (*spTexture);
	if(pspTexture)
	{
		*pspTexture = spTexture;
	}
}
//--------------------------------------------------------------------------
bool VeRendererD3D11::CreateProcessByType(VeRenderProcess::Type eType, const VeChar8* pcName, VeBinaryIStream& kStream, VeRenderProcessPtr* pspProcess)
{
	switch(eType)
	{
	case VeRenderProcess::TYPE_MSAA_RESOLVE:
		{
			VeMSAAResolveD3D11Ptr spMSAAProcess = VE_NEW VeMSAAResolveD3D11(pcName);
			bool bRes = spMSAAProcess->Update(kStream);
			if(bRes)
			{
				AddProcess(VeSmartPointerCast(VeMSAAResolveD3D11, spMSAAProcess));
				if(pspProcess)
				{
					*pspProcess = VeSmartPointerCast(VeMSAAResolveD3D11, spMSAAProcess);
				}
			}
			return bRes;
		}
	default:
		break;
	}
	return false;
}
//--------------------------------------------------------------------------
bool VeRendererD3D11::MapRes(const VeRenderObjectPtr& spObject,
	VeUInt32 u32SubResource, Map eType, VE_BOOL bSync,
	MappedSubresource* pkMapped)
{
	VE_ASSERT(pkMapped);
	ID3D11Resource* pkResource(NULL);
	switch(spObject->GetType())
	{
	case VeRenderObject::TYPE_BUFFER:
		pkResource = VeDynamicCast(VeROBufferD3D11, (VeRenderObject*)spObject)->m_pkBuffer;
		break;
	default:
		break;
	}
	if(pkResource)
	{
		return SUCCEEDED(m_pkImmediateContext->Map(pkResource, u32SubResource,
			(D3D11_MAP)eType, bSync ? 0 : D3D11_MAP_FLAG_DO_NOT_WAIT,
			(D3D11_MAPPED_SUBRESOURCE*)pkMapped));
	}
	else
	{
		return VeRenderer::MapRes(spObject, u32SubResource, eType, bSync,
			pkMapped);
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::UnMapRes(const VeRenderObjectPtr& spObject,
	VeUInt32 u32SubResource, MapWriteRange kRange)
{
	ID3D11Resource* pkResource(NULL);
	switch(spObject->GetType())
	{
	case VeRenderObject::TYPE_BUFFER:
		pkResource = VeDynamicCast(VeROBufferD3D11, (VeRenderObject*)spObject)->m_pkBuffer;
		break;
	default:
		break;
	}
	if(pkResource)
	{
		m_pkImmediateContext->Unmap(pkResource, u32SubResource);
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::Render(VeRenderNode* pkNode)
{
	VE_ASSERT(pkNode);
	if(pkNode->m_pkRenderable)
	{
		pkNode->m_pkRenderable->BeforeRender();
	}
	if(pkNode->m_spData)
	{
		VeRefList<VeRenderTick*>& kTickList = pkNode->m_spData->m_kTickList;
		kTickList.BeginIterator();
		while(!kTickList.IsEnd())
		{
			VeRenderTick* pkTick = kTickList.GetIterNode()->m_tContent;
			kTickList.Next();
			PushTick(pkTick);
		}

		VeRefList<VeRenderCall*>& kCallList = pkNode->m_spData->m_kCallList;
		if(kCallList.Size())
		{
			bool bNeedFlush(true);
			FlushRenderTarget();
			kCallList.BeginIterator();
			while(!kCallList.IsEnd())
			{
				VeRenderCall* pkCall = kCallList.GetIterNode()->m_tContent;
				kCallList.Next();
				if(bNeedFlush && pkCall->GetType())
				{
					FlushStates();
					bNeedFlush = false;
				}
				Call(pkCall);
			}
		}

		pkNode->m_kRenderChildren.BeginIterator();
		while(!pkNode->m_kRenderChildren.IsEnd())
		{
			VeRenderNode* pkNodeIter = pkNode->m_kRenderChildren.GetIterNode()->m_tContent;
			pkNode->m_kRenderChildren.Next();
			Render(pkNodeIter);
			pkNodeIter->Detach();
		}

		kTickList.BeginIterator();
		while(!kTickList.IsEnd())
		{
			VeRenderTick* pkTick = kTickList.GetIterNode()->m_tContent;
			kTickList.Next();
			PopTick(pkTick);
		}
	}
	else
	{
		pkNode->m_kRenderChildren.BeginIterator();
		while(!pkNode->m_kRenderChildren.IsEnd())
		{
			VeRenderNode* pkNodeIter = pkNode->m_kRenderChildren.GetIterNode()->m_tContent;
			pkNode->m_kRenderChildren.Next();
			Render(pkNodeIter);
			pkNodeIter->Detach();
		}
	}
	VE_ASSERT(pkNode->m_kRenderChildren.Empty());
}
//--------------------------------------------------------------------------
void VeRendererD3D11::Process(const VeRenderProcessPtr& spProcess)
{
	VE_ASSERT(spProcess);
	switch(spProcess->GetType())
	{
	case VeRenderProcess::TYPE_MSAA_RESOLVE:
		{
			VeMSAAResolveD3D11* pkProcess = (VeMSAAResolveD3D11*)(VeRenderProcess*)spProcess;
			D3D11_TEXTURE2D_DESC kDesc;
			for(VeUInt32 i(0); i < pkProcess->m_kResolveLinks.Size(); ++i)
			{
				VePair<ID3D11Texture2D*,ID3D11Texture2D*>& kResolve = pkProcess->m_kResolveLinks[i];
				kResolve.m_tFirst->GetDesc(&kDesc);
				m_pkImmediateContext->ResolveSubresource(kResolve.m_tFirst, D3D11CalcSubresource(0, 0, 1),
					kResolve.m_tSecond, D3D11CalcSubresource(0, 0, 1), kDesc.Format);
			}
		}
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::PushTick(VeRenderTick* pkTick)
{
	VE_ASSERT(pkTick);
	switch(pkTick->GetType())
	{
	case VeRenderTick::IA_INDEX_BUFFER:
		m_kIndexBufferStack.Resize(m_kIndexBufferStack.Size() + 1);
		if((((VeIAIndexBuffer*)pkTick)->m_spBuffer))
		{
			m_kIndexBufferStack.Back().m_pkBuffer = ((VeROBufferD3D11*)(VeROBuffer*)(((VeIAIndexBuffer*)pkTick)->m_spBuffer))->m_pkBuffer;
			m_kIndexBufferStack.Back().m_eFormat = (DXGI_FORMAT)(((VeIAIndexBuffer*)pkTick)->m_u32Format);
		}
		else
		{
			m_kIndexBufferStack.Back().m_pkBuffer = NULL;
			m_kIndexBufferStack.Back().m_eFormat = DXGI_FORMAT_UNKNOWN;
		}
		break;
	case VeRenderTick::IA_INPUT_LAYOUT:
		m_kInputLayoutStack.PushBack(((VeROInputLayoutD3D11*)(VeROInputLayout*)(((VeIAInputLayout*)pkTick)->m_spInputLayout))->m_pkInputLayout);
		break;
	case VeRenderTick::IA_PRIMITIVE_TOPOLOGY:
		m_kTopologyStack.PushBack((D3D11_PRIMITIVE_TOPOLOGY)(((VeIAPrimitiveTopology*)pkTick)->m_eTopology));
		break;
	case VeRenderTick::IA_VERTEX_BUFFER:
		{
			VeIAVertexBuffer* pkBuffer = (VeIAVertexBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_VERTEX_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			VeVector<VertexBufferForSet>& kStack = m_akVertexBufferStack[u32Slot];
			kStack.Resize(kStack.Size() + 1);
			kStack.Back().m_pkBuffer = ((VeROBufferD3D11*)(VeROBuffer*)(pkBuffer->m_spBuffer))->m_pkBuffer;
			kStack.Back().m_uiStride = pkBuffer->m_u32Stride;
			m_u32VertexBufferChangeMin = VE_MIN(m_u32VertexBufferChangeMin, u32Slot);
			m_u32VertexBufferChangeMax = (m_u32VertexBufferChangeMax == D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32VertexBufferChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::VS_CONSTANT_BUFFER:
		{
			VeVSCBuffer* pkBuffer = (VeVSCBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_CONSTANT_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			VeVector<ID3D11Buffer*>& kStack = m_akVSCBufferStack[u32Slot];
			kStack.PushBack(((VeROBufferD3D11*)(VeROBuffer*)(pkBuffer->m_spBuffer))->m_pkBuffer);
			m_u32VSChangeCBufferMin = VE_MIN(m_u32VSChangeCBufferMin, u32Slot);
			m_u32VSChangeCBufferMax = (m_u32VSChangeCBufferMax == D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32VSChangeCBufferMax, u32Slot);
		}
		break;
	case VeRenderTick::VS_SAMPLER:
		break;
	case VeRenderTick::VS_SHADER:
		m_kVertexShaderStack.PushBack(((VeROVertexShaderD3D11*)(VeROVertexShader*)(((VeVSShader*)pkTick)->m_spShader))->m_pkShader);
		break;
	case VeRenderTick::VS_SHADER_RESOURCE:
		break;
	case VeRenderTick::HS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::HS_SAMPLER:
		break;
	case VeRenderTick::HS_SHADER:
		break;
	case VeRenderTick::HS_SHADER_RESOURCE:
		break;
	case VeRenderTick::DS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::DS_SAMPLER:
		break;
	case VeRenderTick::DS_SHADER:
		break;
	case VeRenderTick::DS_SHADER_RESOURCE:
		break;
	case VeRenderTick::GS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::GS_SAMPLER:
		break;
	case VeRenderTick::GS_SHADER:
		break;
	case VeRenderTick::GS_SHADER_RESOURCE:
		break;
	case VeRenderTick::SO_TARGET:
		break;
	case VeRenderTick::RS_SCISSOR_RECT:
		{
			VeRSScissorRectTick* pkScissorTick = ((VeRSScissorRectTick*)pkTick);
			VeUInt32 u32Slot = pkScissorTick->m_u32Slot;
			VeVector<D3D11_RECT>& kStack = m_akScissorRectStack[u32Slot];
			kStack.Resize(kStack.Size() + 1);
			kStack.Back().left = pkScissorTick->m_i16Left;
			kStack.Back().top = pkScissorTick->m_i16Top;
			kStack.Back().right = pkScissorTick->m_i16Left + pkScissorTick->m_i16Width;
			kStack.Back().bottom = pkScissorTick->m_i16Top + pkScissorTick->m_i16Height;
			m_u32ScissorRectChangeMax = (m_u32ScissorRectChangeMax == D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) ? u32Slot : VE_MAX(m_u32ScissorRectChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::RS_STATE:
		{
			VeRSState* pkRSStateTick = ((VeRSState*)pkTick);
			if(pkRSStateTick->m_spState)
			{
				m_kRasterizerStateStack.PushBack(((VeRORasterizeStateD3D11*)(VeRORasterizeState*)(pkRSStateTick->m_spState))->m_pkRasterizerState);
			}
			else
			{
				m_kRasterizerStateStack.PushBack(NULL);
			}
		}
		break;
	case VeRenderTick::RS_VIEWPORT:
		{
			VeRSViewportTick* pkViewportTick = ((VeRSViewportTick*)pkTick);
			VeUInt32 u32Slot = pkViewportTick->m_u32Slot;
			VeVector<VeVector4D>& kStack = m_akViewportStack[u32Slot];
			kStack.PushBack(pkViewportTick->m_kViewport);
			m_u32ViewportChangeMax = (m_u32ViewportChangeMax == D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) ? u32Slot : VE_MAX(m_u32ViewportChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::PS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::PS_SAMPLER:
		{
			VePSSampler* pkSampler = (VePSSampler*)pkTick;
			VeUInt32 u32Slot = pkSampler->m_u32Slot;
			m_akPSSamplerStack[u32Slot].PushBack(((VeROSamplerStateD3D11*)(VeROSamplerState*)(pkSampler->m_spSampler))->m_pkSamplerState);
			m_u32PSChangeSamplerMin = VE_MIN(m_u32PSChangeSamplerMin, u32Slot);
			m_u32PSChangeSamplerMax = (m_u32PSChangeSamplerMax == VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32PSChangeSamplerMax, u32Slot);
		}
		break;
	case VeRenderTick::PS_SHADER:
		m_kPixelShaderStack.PushBack(((VeROPixelShaderD3D11*)(VeROPixelShader*)(((VePSShader*)pkTick)->m_spShader))->m_pkShader);
		break;
	case VeRenderTick::PS_SHADER_RESOURCE:
		{
			VePSShaderResource* pkShaderResource = (VePSShaderResource*)pkTick;
			VeUInt32 u32Slot = pkShaderResource->m_u32Slot;
			m_akPSShaderResourceViewStack[u32Slot].PushBack((VeROShaderResourceViewD3D11*)(VeROShaderResourceView*)(pkShaderResource->m_spShaderResourceView));
			m_u32PSChangeSRVMin = VE_MIN(m_u32PSChangeSRVMin, u32Slot);
			m_u32PSChangeSRVMax = (m_u32PSChangeSRVMax == VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32PSChangeSRVMax, u32Slot);
		}
		break;
	case VeRenderTick::OM_BLEND_STATE:
		{
			VeOMBlendStateTick* pkBlendStateTick = (VeOMBlendStateTick*)pkTick;
			m_kBlendStateStack.Resize(m_kBlendStateStack.Size() + 1);
			m_kBlendStateStack.Back().m_pkBlendState = pkBlendStateTick->m_spBlendState ? ((VeROBlendStateD3D11*)(VeROBlendState*)(pkBlendStateTick->m_spBlendState))->m_pkBlendState : NULL;
			VeCrazyCopy(m_kBlendStateStack.Back().m_af32Factor, pkBlendStateTick->m_af32Factor, sizeof(m_kBlendStateStack.Back().m_af32Factor));
			m_kBlendStateStack.Back().m_uiSampleMask = pkBlendStateTick->m_u32SampleMask;
			m_bBlendStateChange = VE_TRUE;
		}
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_STATE:
		{
			VeOMDepthStencilStateTick* pkDepthStencilTick = (VeOMDepthStencilStateTick*)pkTick;
			m_kDepthStencilStateStack.Resize(m_kDepthStencilStateStack.Size() + 1);
			m_kDepthStencilStateStack.Back().m_pkDepthStencilState = pkDepthStencilTick->m_spDepthStencilState ? ((VeRODepthStencilStateD3D11*)(VeRODepthStencilState*)(pkDepthStencilTick->m_spDepthStencilState))->m_pkDepthStencilState : NULL;
			m_kDepthStencilStateStack.Back().m_uiStencilRef = pkDepthStencilTick->m_u32StencilRef;
			m_bDepthStencilStateChange = VE_TRUE;
		}
		break;
	case VeRenderTick::OM_RENDER_TARGET_VIEW:
		{
			VeOMRenderTargetViewTick* pkRTVTick = (VeOMRenderTargetViewTick*)pkTick;
			VeUInt32 u32Slot = pkRTVTick->m_u32Slot;
			VeVector<VeRORenderTargetViewD3D11*>& kStack = m_akRenderTargetViewStack[u32Slot];
			kStack.PushBack((VeRORenderTargetViewD3D11*)(VeRORenderTargetView*)(((VeOMRenderTargetViewTick*)pkTick)->m_spRenderTarget));
			m_u32RenderTargetViewChangeMax = (m_u32RenderTargetViewChangeMax == D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) ? u32Slot : VE_MAX(m_u32RenderTargetViewChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_VIEW:
		{
			VeOMDepthStencilViewTick* pkDSVTick = (VeOMDepthStencilViewTick*)pkTick;
			m_kDepthStencilViewStack.PushBack((VeRODepthStencilViewD3D11*)(VeRODepthStencilView*)((pkDSVTick)->m_spDepthStencil));
		}
		break;
	case VeRenderTick::OM_UNORDERED_ACCESS_VIEW:
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::PopTick(VeRenderTick* pkTick)
{
	VE_ASSERT(pkTick);
	switch(pkTick->GetType())
	{
	case VeRenderTick::IA_INDEX_BUFFER:
		m_kIndexBufferStack.PopBack();
		break;
	case VeRenderTick::IA_INPUT_LAYOUT:
		m_kInputLayoutStack.PopBack();
		break;
	case VeRenderTick::IA_PRIMITIVE_TOPOLOGY:
		m_kTopologyStack.PopBack();
		break;
	case VeRenderTick::IA_VERTEX_BUFFER:
		{
			VeIAVertexBuffer* pkBuffer = (VeIAVertexBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_VERTEX_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			m_akVertexBufferStack[u32Slot].PopBack();
			m_u32VertexBufferChangeMin = VE_MIN(m_u32VertexBufferChangeMin, u32Slot);
			m_u32VertexBufferChangeMax = (m_u32VertexBufferChangeMax == D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32VertexBufferChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::VS_CONSTANT_BUFFER:
		{
			VeVSCBuffer* pkBuffer = (VeVSCBuffer*)pkTick;
			VE_ASSERT(VE_MASK_HAS_ANY(pkBuffer->m_spBuffer->GetBindFlag(), BIND_CONSTANT_BUFFER));
			VeUInt32 u32Slot = pkBuffer->m_u32Slot;
			m_akVSCBufferStack[u32Slot].PopBack();
			m_u32VSChangeCBufferMin = VE_MIN(m_u32VSChangeCBufferMin, u32Slot);
			m_u32VSChangeCBufferMax = (m_u32VSChangeCBufferMax == D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32VSChangeCBufferMax, u32Slot);
		}
		break;
	case VeRenderTick::VS_SAMPLER:
		break;
	case VeRenderTick::VS_SHADER:
		m_kVertexShaderStack.PopBack();
		break;
	case VeRenderTick::VS_SHADER_RESOURCE:
		break;
	case VeRenderTick::HS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::HS_SAMPLER:
		break;
	case VeRenderTick::HS_SHADER:
		break;
	case VeRenderTick::HS_SHADER_RESOURCE:
		break;
	case VeRenderTick::DS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::DS_SAMPLER:
		break;
	case VeRenderTick::DS_SHADER:
		break;
	case VeRenderTick::DS_SHADER_RESOURCE:
		break;
	case VeRenderTick::GS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::GS_SAMPLER:
		break;
	case VeRenderTick::GS_SHADER:
		break;
	case VeRenderTick::GS_SHADER_RESOURCE:
		break;
	case VeRenderTick::SO_TARGET:
		break;
	case VeRenderTick::RS_SCISSOR_RECT:
		{
			VeRSScissorRectTick* pkScissorTick = ((VeRSScissorRectTick*)pkTick);
			VeUInt32 u32Slot = pkScissorTick->m_u32Slot;
			m_akScissorRectStack[u32Slot].PopBack();
			m_u32ScissorRectChangeMax = (m_u32ScissorRectChangeMax == D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) ? u32Slot : VE_MAX(m_u32ScissorRectChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::RS_STATE:
		m_kRasterizerStateStack.PopBack();
		break;
	case VeRenderTick::RS_VIEWPORT:
		{
			VeRSViewportTick* pkViewportTick = ((VeRSViewportTick*)pkTick);
			VeUInt32 u32Slot = pkViewportTick->m_u32Slot;
			m_akViewportStack[u32Slot].PopBack();
			m_u32ViewportChangeMax = (m_u32ViewportChangeMax == D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) ? u32Slot : VE_MAX(m_u32ViewportChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::PS_CONSTANT_BUFFER:
		break;
	case VeRenderTick::PS_SAMPLER:
		{
			VePSSampler* pkSampler = (VePSSampler*)pkTick;
			VeUInt32 u32Slot = pkSampler->m_u32Slot;
			m_akPSSamplerStack[u32Slot].PopBack();
			m_u32PSChangeSamplerMin = VE_MIN(m_u32PSChangeSamplerMin, u32Slot);
			m_u32PSChangeSamplerMax = (m_u32PSChangeSamplerMax == VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32PSChangeSamplerMax, u32Slot);
		}
		break;
	case VeRenderTick::PS_SHADER:
		m_kPixelShaderStack.PopBack();
		break;
	case VeRenderTick::PS_SHADER_RESOURCE:
		{
			VePSShaderResource* pkShaderResource = (VePSShaderResource*)pkTick;
			VeUInt32 u32Slot = pkShaderResource->m_u32Slot;
			m_akPSShaderResourceViewStack[u32Slot].PopBack();
			m_u32PSChangeSRVMin = VE_MIN(m_u32PSChangeSRVMin, u32Slot);
			m_u32PSChangeSRVMax = (m_u32PSChangeSRVMax == VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT) ? u32Slot : VE_MAX(m_u32PSChangeSRVMax, u32Slot);
		}
		break;
	case VeRenderTick::OM_BLEND_STATE:
		m_kBlendStateStack.PopBack();
		m_bBlendStateChange = VE_TRUE;
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_STATE:
		m_kDepthStencilStateStack.PopBack();
		m_bDepthStencilStateChange = VE_TRUE;
		break;
	case VeRenderTick::OM_RENDER_TARGET_VIEW:
		{
			VeOMRenderTargetViewTick* pkRTVTick = (VeOMRenderTargetViewTick*)pkTick;
			VeUInt32 u32Slot = pkRTVTick->m_u32Slot;
			m_akRenderTargetViewStack[u32Slot].PopBack();
			m_u32RenderTargetViewChangeMax = (m_u32RenderTargetViewChangeMax == D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT) ? u32Slot : VE_MAX(m_u32RenderTargetViewChangeMax, u32Slot);
		}
		break;
	case VeRenderTick::OM_DEPTH_STENCIL_VIEW:
		{
			m_kDepthStencilViewStack.PopBack();
		}
		break;
	case VeRenderTick::OM_UNORDERED_ACCESS_VIEW:
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
struct VeD3D11Color
{
	FLOAT m_afFloat[4];
};
//--------------------------------------------------------------------------
void VeRendererD3D11::Call(VeRenderCall* pkCall)
{
	switch(pkCall->GetType())
	{
	case VeRenderCall::CLEAR:
		{
			VeClearCall* pkClearCall = (VeClearCall*)pkCall;
			if(pkClearCall->m_bClearColor)
			{
				for(VeUInt32 i(0); i < pkClearCall->m_kColorArray.Size(); ++i)
				{
					if(m_apkCurRenderTargetViews[i])
					{
						VeColor& kColor = pkClearCall->m_kColorArray[i];
						m_pkImmediateContext->ClearRenderTargetView(m_apkCurRenderTargetViews[i], ((VeD3D11Color*)&kColor)->m_afFloat);
					}
				}
			}
			if(m_pkCurDepthStencilView)
			{
				UINT uiFlag(0);
				if(pkClearCall->m_bClearDepth) uiFlag |= D3D11_CLEAR_DEPTH;
				if(pkClearCall->m_bClearStencil) uiFlag |= D3D11_CLEAR_STENCIL;
				if(uiFlag)
				{
					m_pkImmediateContext->ClearDepthStencilView(m_pkCurDepthStencilView, uiFlag, pkClearCall->m_f32Depth, pkClearCall->m_u8Stencil);
				}
				
			}
		}
		break;
	case VeRenderCall::DRAW:
		m_pkImmediateContext->Draw(
			((VeDrawCall*)pkCall)->m_kDraw.m_u32VertexCount,
			((VeDrawCall*)pkCall)->m_kDraw.m_u32StartVertexLocation);
		break;
	case VeRenderCall::DRAW_INDEXED:
		m_pkImmediateContext->DrawIndexed(
			((VeDrawCall*)pkCall)->m_kDrawIndexed.m_u32IndexCount,
			((VeDrawCall*)pkCall)->m_kDrawIndexed.m_u32StartIndexLocation,
			((VeDrawCall*)pkCall)->m_kDrawIndexed.m_i32BaseVertexLocation);
		break;
	case VeDrawCall::DRAW_INSTANCED:
		m_pkImmediateContext->DrawInstanced(
			((VeDrawCall*)pkCall)->m_kDrawInstanced.m_u32VertexCountPerInstance,
			((VeDrawCall*)pkCall)->m_kDrawInstanced.m_u32InstanceCount,
			((VeDrawCall*)pkCall)->m_kDrawInstanced.m_u32StartVertexLocation,
			((VeDrawCall*)pkCall)->m_kDrawInstanced.m_u32StartInstanceLocation);
		break;
	case VeDrawCall::DRAW_INDEXED_INSTANCED:
		m_pkImmediateContext->DrawIndexedInstanced(
			((VeDrawCall*)pkCall)->m_kDrawIndexedInstanced.m_u32IndexCountPerInstance,
			((VeDrawCall*)pkCall)->m_kDrawIndexedInstanced.m_u32InstanceCount,
			((VeDrawCall*)pkCall)->m_kDrawIndexedInstanced.m_u32StartIndexLocation,
			((VeDrawCall*)pkCall)->m_kDrawIndexedInstanced.m_i32BaseVertexLocation,
			((VeDrawCall*)pkCall)->m_kDrawIndexedInstanced.m_u32StartInstanceLocation);
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::FlushRenderTarget()
{
	bool bChangeViews = false;
	ID3D11DepthStencilView* pkDepthView(NULL);
	if(m_kDepthStencilViewStack.Size())
	{
		VeRODepthStencilViewD3D11* pkDSV = m_kDepthStencilViewStack.Back();
		if(pkDSV->m_spShaderResourceView && pkDSV->m_spShaderResourceView->m_u64Active != VeUInt64(-1))
		{
			SetNull(pkDSV->m_spShaderResourceView);
		}
		pkDepthView = pkDSV->m_pkDepthStencilView;
	}
	if(pkDepthView != m_pkCurDepthStencilView)
	{
		m_pkCurDepthStencilView = pkDepthView;
		bChangeViews = true;
	}
	if(m_u32RenderTargetViewChangeMax < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
	{
		for(VeUInt32 i(0); i <= m_u32RenderTargetViewChangeMax + 1; ++i)
		{
			VeVector<VeRORenderTargetViewD3D11*>& kStack = m_akRenderTargetViewStack[i];
			if(kStack.Size())
			{
				VeRORenderTargetViewD3D11* pkRTV = kStack.Back();
				if(pkRTV->m_spShaderResourceView && pkRTV->m_spShaderResourceView->m_u64Active != VeUInt64(-1))
				{
					SetNull(pkRTV->m_spShaderResourceView);
				}
				if(m_apkCurRenderTargetViews[i] != pkRTV->m_pkRenderTargetView)
				{
					m_apkCurRenderTargetViews[i] = pkRTV->m_pkRenderTargetView;
					pkRTV->m_u32Active = i;
					bChangeViews = true;
				}
			}
			else if(m_u32ActiveRenderTargetCount != i)
			{
				m_u32ActiveRenderTargetCount = i;
				bChangeViews = true;
				break;
			}
		}
		m_u32RenderTargetViewChangeMax = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	}
	if(bChangeViews)
	{
		m_pkImmediateContext->OMSetRenderTargets(m_u32ActiveRenderTargetCount, m_apkCurRenderTargetViews, m_pkCurDepthStencilView);
	}
}
//--------------------------------------------------------------------------
void VeRendererD3D11::FlushStates()
{
	if(m_kVertexShaderStack.Size() && m_kVertexShaderStack.Back() != m_pkCurVertexShader)
	{
		m_pkCurVertexShader = m_kVertexShaderStack.Back();
		m_pkImmediateContext->VSSetShader(m_pkCurVertexShader, NULL, 0);
	}

	if(m_kPixelShaderStack.Size() && m_kPixelShaderStack.Back() != m_pkCurPixelShader)
	{
		m_pkCurPixelShader = m_kPixelShaderStack.Back();
		m_pkImmediateContext->PSSetShader(m_pkCurPixelShader, NULL, 0);
	}
	
	ID3D11RasterizerState* pkRSState = m_kRasterizerStateStack.Size() ? m_kRasterizerStateStack.Back() : NULL;
	if(pkRSState != m_pkCurRasterizerState)
	{
		m_pkImmediateContext->RSSetState(pkRSState);
		m_pkCurRasterizerState = pkRSState;
	}

	if(m_u32VSChangeCBufferMax < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT)
	{
		VE_ASSERT(m_u32VSChangeCBufferMin <= m_u32VSChangeCBufferMax);
		UINT uiStartSlot = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
		UINT uiEndSlot = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
		for(VeUInt32 i(m_u32VSChangeCBufferMin); i <= m_u32VSChangeCBufferMax; ++i)
		{
			bool bChange(false);
			VeVector<ID3D11Buffer*>& kStack = m_akVSCBufferStack[i];
			ID3D11Buffer* pkBuffer = kStack.Size() ? kStack.Back() : NULL;
			if(pkBuffer != m_apkCurVSCBuffers[i])
			{
				m_apkCurVSCBuffers[i] = pkBuffer;
				bChange = true;
			}
			if(bChange)
			{
				if(uiStartSlot == D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT)
				{
					uiStartSlot = i;
					uiEndSlot = i;
				}
				else
				{
					uiEndSlot = i;
				}
			}
		}
		if(uiStartSlot < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT)
		{
			m_pkImmediateContext->VSSetConstantBuffers(uiStartSlot, uiEndSlot - uiStartSlot + 1, m_apkCurVSCBuffers + uiStartSlot);
		}
		m_u32VSChangeCBufferMin = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
		m_u32VSChangeCBufferMax = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	}

	if(m_u32PSChangeSamplerMax < VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
	{
		VE_ASSERT(m_u32PSChangeSamplerMin <= m_u32PSChangeSamplerMax);
		UINT uiStartSlot = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
		UINT uiEndSlot = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
		for(VeUInt32 i(m_u32PSChangeSamplerMin); i <= m_u32PSChangeSamplerMax; ++i)
		{
			bool bChange(false);
			VeVector<ID3D11SamplerState*>& kStack = m_akPSSamplerStack[i];
			ID3D11SamplerState* pkSampler = kStack.Size() ? kStack.Back() : NULL;
			if(pkSampler != m_apkCurPSSamplers[i])
			{
				m_apkCurPSSamplers[i] = pkSampler;
				bChange = true;
			}
			if(bChange)
			{
				if(uiStartSlot == VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
				{
					uiStartSlot = i;
					uiEndSlot = i;
				}
				else
				{
					uiEndSlot = i;
				}
			}
		}
		if(uiStartSlot < VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
		{
			m_pkImmediateContext->PSSetSamplers(uiStartSlot, uiEndSlot - uiStartSlot + 1, m_apkCurPSSamplers + uiStartSlot);
		}
		m_u32PSChangeSamplerMin = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
		m_u32PSChangeSamplerMax = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
	}

	if(m_u32PSChangeSRVMax < VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
	{
		VE_ASSERT(m_u32PSChangeSRVMin <= m_u32PSChangeSRVMax);
		UINT uiStartSlot = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
		UINT uiEndSlot = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
		for(VeUInt32 i(m_u32PSChangeSRVMin); i <= m_u32PSChangeSRVMax; ++i)
		{
			bool bChange(false);
			VeVector<VeROShaderResourceViewD3D11*>& kStack = m_akPSShaderResourceViewStack[i];
			ID3D11ShaderResourceView* pkView(NULL);
			VeROShaderResourceViewD3D11* pkSRV(NULL);
			if(kStack.Size())
			{
				pkSRV = kStack.Back();
				if(pkSRV->m_spRenderTargetView && pkSRV->m_spRenderTargetView->m_u32Active != VeUInt32(-1))
				{
					SetNull(pkSRV->m_spRenderTargetView);
				}
				if(pkSRV->m_spDepthStencilView && pkSRV->m_spDepthStencilView->m_pkDepthStencilView == m_pkCurDepthStencilView)
				{
					SetNull(pkSRV->m_spDepthStencilView);
				}
				pkView = pkSRV->m_pkShaderResourceView;
			}
			if(pkView != m_apkCurPSShaderResourceViews[i])
			{
				m_apkCurPSShaderResourceViews[i] = pkView;
				if(pkSRV)
				{
					pkSRV->m_au8Active[VeRenderer::PIXEL_SHADER] = i;
				}
				bChange = true;
			}
			if(bChange)
			{
				if(uiStartSlot == VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
				{
					uiStartSlot = i;
					uiEndSlot = i;
				}
				else
				{
					uiEndSlot = i;
				}
			}
		}
		if(uiStartSlot < VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT)
		{
			m_pkImmediateContext->PSSetShaderResources(uiStartSlot, uiEndSlot - uiStartSlot + 1, m_apkCurPSShaderResourceViews + uiStartSlot);
		}
		m_u32PSChangeSRVMin = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
		m_u32PSChangeSRVMax = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
	}

	if(m_bBlendStateChange && m_kBlendStateStack.Size())
	{
		BlendStateForSet& kLast = m_kBlendStateStack.Back();
		bool bChange(false);
		if(m_kCurBlendState.m_pkBlendState != kLast.m_pkBlendState)
		{
			m_kCurBlendState.m_pkBlendState = kLast.m_pkBlendState;
			bChange = true;
		}
		if(m_kCurBlendState.m_pkBlendState)
		{
			for(VeUInt32 i(0); i < 4; ++i)
			{
				if(m_kCurBlendState.m_af32Factor[i] != kLast.m_af32Factor[i])
				{
					m_kCurBlendState.m_af32Factor[i] = kLast.m_af32Factor[i];
					bChange = true;
				}
			}
			if(m_kCurBlendState.m_uiSampleMask != kLast.m_uiSampleMask)
			{
				m_kCurBlendState.m_uiSampleMask = kLast.m_uiSampleMask;
				bChange = true;
			}
		}
		if(bChange)
		{
			m_pkImmediateContext->OMSetBlendState(m_kCurBlendState.m_pkBlendState, m_kCurBlendState.m_af32Factor, m_kCurBlendState.m_uiSampleMask);
		}
		m_bBlendStateChange = VE_FALSE;
	}

	if(m_bDepthStencilStateChange && m_kDepthStencilStateStack.Size())
	{
		DepthStencilStateForSet& kLast = m_kDepthStencilStateStack.Back();
		bool bChange(false);
		if(m_kCurDepthStencilState.m_pkDepthStencilState != kLast.m_pkDepthStencilState)
		{
			m_kCurDepthStencilState.m_pkDepthStencilState = kLast.m_pkDepthStencilState;
			bChange = true;
		}
		if(m_kCurDepthStencilState.m_pkDepthStencilState)
		{
			if(m_kCurDepthStencilState.m_uiStencilRef != kLast.m_uiStencilRef)
			{
				m_kCurDepthStencilState.m_uiStencilRef = kLast.m_uiStencilRef;
				bChange = true;
			}
		}
		if(bChange)
		{
			m_pkImmediateContext->OMSetDepthStencilState(m_kCurDepthStencilState.m_pkDepthStencilState, m_kCurDepthStencilState.m_uiStencilRef);
		}
		m_bDepthStencilStateChange = VE_FALSE;
	}

	if(m_kInputLayoutStack.Size() && m_kInputLayoutStack.Back() != m_pkCurInputLayout)
	{
		m_pkCurInputLayout = m_kInputLayoutStack.Back();
		m_pkImmediateContext->IASetInputLayout(m_pkCurInputLayout);
	}


	if(m_kTopologyStack.Size() && m_kTopologyStack.Back() != m_eCurTopology)
	{
		m_eCurTopology = m_kTopologyStack.Back();
		m_pkImmediateContext->IASetPrimitiveTopology(m_eCurTopology);
	}

	if(m_kIndexBufferStack.Size())
	{
		IndexBufferForSet& kCurrentIB = m_kIndexBufferStack.Back();
		bool bChange = false;
		if(m_pkCurIndexBuffer != kCurrentIB.m_pkBuffer)
		{
			m_pkCurIndexBuffer = kCurrentIB.m_pkBuffer;
			bChange = true;
		}
		if(m_eCurIndexBufferFormat != kCurrentIB.m_eFormat)
		{
			m_eCurIndexBufferFormat = kCurrentIB.m_eFormat;
			bChange = true;
		}
		if(bChange)
		{
			m_pkImmediateContext->IASetIndexBuffer(m_pkCurIndexBuffer, m_eCurIndexBufferFormat, 0);
		}
	}
	else if(m_pkCurIndexBuffer)
	{
		m_pkImmediateContext->IASetIndexBuffer(NULL, DXGI_FORMAT_UNKNOWN, 0);
		m_pkCurIndexBuffer = NULL;
		m_eCurIndexBufferFormat = DXGI_FORMAT_UNKNOWN;
	}

	if(m_u32VertexBufferChangeMax < D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT)
	{
		VE_ASSERT(m_u32VertexBufferChangeMin <= m_u32VertexBufferChangeMax);
		UINT uiStartSlot = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
		UINT uiEndSlot = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
		for(VeUInt32 i(m_u32VertexBufferChangeMin); i <= m_u32VertexBufferChangeMax; ++i)
		{
			bool bChange(false);
			VeVector<VertexBufferForSet>& kStack = m_akVertexBufferStack[i];
			if(kStack.Size())
			{
				VertexBufferForSet& kVertexBuffer = kStack.Back();
				if(kVertexBuffer.m_pkBuffer != m_apkCurVertexBuffers[i])
				{
					m_apkCurVertexBuffers[i] = kVertexBuffer.m_pkBuffer;
					bChange = true;
				}
				if(kVertexBuffer.m_uiStride != m_auiCurVertexBufferStrides[i])
				{
					m_auiCurVertexBufferStrides[i] = kVertexBuffer.m_uiStride;
					bChange = true;
				}
			}
			else if(m_apkCurVertexBuffers[i])
			{
				m_apkCurVertexBuffers[i] = NULL;
				bChange = true;
			}
			if(bChange)
			{
				if(uiStartSlot == D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT)
				{
					uiStartSlot = i;
					uiEndSlot = i;
				}
				else
				{
					uiEndSlot = i;
				}
			}
		}
		if(uiStartSlot < D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT)
		{
			m_pkImmediateContext->IASetVertexBuffers(uiStartSlot, uiEndSlot - uiStartSlot + 1, m_apkCurVertexBuffers + uiStartSlot, m_auiCurVertexBufferStrides + uiStartSlot, m_auiCurVertexBufferOffsets + uiStartSlot);
		}
		m_u32VertexBufferChangeMin = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
		m_u32VertexBufferChangeMax = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	}

	if(m_u32ViewportChangeMax < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
	{
		bool bChange(false);
		for(VeUInt32 i(0); i <= m_u32ViewportChangeMax + 1; ++i)
		{
			VeVector<VeVector4D>& kStack = m_akViewportStack[i];
			if(kStack.Size())
			{
				VeVector4D& kViewport = kStack.Back();
				
				if(kViewport.x != m_akCurViewports[i].TopLeftX)
				{
					m_akCurViewports[i].TopLeftX = kViewport.x;
					bChange = true;
				}
				if(kViewport.y != m_akCurViewports[i].TopLeftY)
				{
					m_akCurViewports[i].TopLeftY = kViewport.y;
					bChange = true;
				}
				if(kViewport.z != m_akCurViewports[i].Width)
				{
					m_akCurViewports[i].Width = kViewport.z;
					bChange = true;
				}
				if(kViewport.w != m_akCurViewports[i].Height)
				{
					m_akCurViewports[i].Height = kViewport.w;
					bChange = true;
				}
			}
			else if(m_u32ActiveViewportCount != i)
			{
				m_u32ActiveViewportCount = i;
				bChange = true;
				break;
			}
		}

		if(bChange)
		{
			m_pkImmediateContext->RSSetViewports(m_u32ActiveViewportCount, m_akCurViewports);
		}
		m_u32ViewportChangeMax = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	}

	if(m_u32ScissorRectChangeMax < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
	{
		bool bChange(false);
		for(VeUInt32 i(0); i <= m_u32ScissorRectChangeMax + 1; ++i)
		{
			VeVector<D3D11_RECT>& kStack = m_akScissorRectStack[i];
			if(kStack.Size())
			{
				D3D11_RECT& kRect = kStack.Back();
				if(kRect.left != m_akCurScissorRects[i].left)
				{
					m_akCurScissorRects[i].left = kRect.left;
					bChange = true;
				}
				if(kRect.top != m_akCurScissorRects[i].top)
				{
					m_akCurScissorRects[i].top = kRect.top;
					bChange = true;
				}
				if(kRect.right != m_akCurScissorRects[i].right)
				{
					m_akCurScissorRects[i].right = kRect.right;
					bChange = true;
				}
				if(kRect.bottom != m_akCurScissorRects[i].bottom)
				{
					m_akCurScissorRects[i].bottom = kRect.bottom;
					bChange = true;
				}
			}
			else if(m_u32ActiveScissorRectCount != i)
			{
				m_u32ActiveScissorRectCount = i;
				bChange = true;
				break;
			}
		}
		if(bChange)
		{
			m_pkImmediateContext->RSSetScissorRects(m_u32ActiveScissorRectCount, m_akCurScissorRects);
		}
		m_u32ScissorRectChangeMax = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	}

	bool bChangeViews = false;
	ID3D11DepthStencilView* pkDepthView(NULL);
	if(m_kDepthStencilViewStack.Size())
	{
		VeRODepthStencilViewD3D11* pkDSV = m_kDepthStencilViewStack.Back();
		if(pkDSV->m_spShaderResourceView && pkDSV->m_spShaderResourceView->m_u64Active != VeUInt64(-1))
		{
			SetNull(pkDSV->m_spShaderResourceView);
		}
		pkDepthView = pkDSV->m_pkDepthStencilView;
	}
	if(pkDepthView != m_pkCurDepthStencilView)
	{
		m_pkCurDepthStencilView = pkDepthView;
		bChangeViews = true;
	}
	if(m_u32RenderTargetViewChangeMax < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT)
	{
		for(VeUInt32 i(0); i <= m_u32RenderTargetViewChangeMax + 1; ++i)
		{
			VeVector<VeRORenderTargetViewD3D11*>& kStack = m_akRenderTargetViewStack[i];
			if(kStack.Size())
			{
				VeRORenderTargetViewD3D11* pkRTV = kStack.Back();
				if(pkRTV->m_spShaderResourceView && pkRTV->m_spShaderResourceView->m_u64Active != VeUInt64(-1))
				{
					SetNull(pkRTV->m_spShaderResourceView);
				}
				if(m_apkCurRenderTargetViews[i] != pkRTV->m_pkRenderTargetView)
				{
					m_apkCurRenderTargetViews[i] = pkRTV->m_pkRenderTargetView;
					pkRTV->m_u32Active = i;
					bChangeViews = true;
				}
			}
			else if(m_u32ActiveRenderTargetCount != i)
			{
				m_u32ActiveRenderTargetCount = i;
				bChangeViews = true;
				break;
			}
		}
		m_u32RenderTargetViewChangeMax = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
	}
	if(bChangeViews)
	{
		m_pkImmediateContext->OMSetRenderTargets(m_u32ActiveRenderTargetCount, m_apkCurRenderTargetViews, m_pkCurDepthStencilView);
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeRendererD3D11::GetShaderName()
{
	return "hlsl";
}
//--------------------------------------------------------------------------
const VeChar8* VeRendererD3D11::GetShaderProfile()
{
	if(m_eCurrentLevel == D3D_FEATURE_LEVEL_11_0)
	{
		return "5_0";
	}
	else
	{
		return "4_0";
	}
}
//--------------------------------------------------------------------------
const VeChar8* VeRendererD3D11::GetSemanticName(Semantic eSemantic)
{
	switch(eSemantic)
	{
	case SE_POSITION:
		return "POSITION";
	case SE_NORMAL:
		return "NORMAL";
	case SE_COLOR:
		return "COLOR";
	case SE_TEXCOORD:
		return "TEXCOORD";
	case SE_TANGENT:
		return "TANGENT";
	case SE_BINORMAL:
		return "BINORMAL";
	case SE_BLENDINDICES:
		return "BLENDINDICES";
	case SE_BLENDWEIGHT:
		return "BLENDWEIGHT";
	}
	return "TEXCOORD";
}
//--------------------------------------------------------------------------
void VeRendererD3D11::InitGlobal()
{
	UINT uiNum;
	UINT uiCount(2);
	m_pkDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, uiCount, &uiNum);
	while(uiNum)
	{
		for(VeUInt32 i(0); i < uiNum; ++i)
		{
			DXGI_SAMPLE_DESC kDesc = { uiCount, i };
			m_kSampleDescArray.PushBack(kDesc);
		}
		uiCount <<= 1;
		m_pkDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, uiCount, &uiNum);
	}
	m_spBackBufferTEX = VE_NEW VeROTexture2DD3D11("back_buffer");
	AddObject(VeSmartPointerCast(VeRenderObject, m_spBackBufferTEX));
	m_spBackBufferRTV = VE_NEW VeRORenderTargetViewD3D11("back_buffer");
	AddObject(VeSmartPointerCast(VeRenderObject, m_spBackBufferRTV));
}
//--------------------------------------------------------------------------
void VeRendererD3D11::TermGlobal()
{
	m_kSampleDescArray.Clear();
	for(VeVector<VeRenderObjectPtr>::iterator it = m_kObjectArray.Begin(); it != m_kObjectArray.End(); ++it)
	{
		(*it)->OnClear();
	}
	m_kObjectArray.Clear();
	for(VeUInt32 i(0); i < VeRenderObject::TYPE_MAX; ++i)
	{
		m_akObjectMap[i].Clear();
	}
	for(VeVector<VeRenderProcessPtr>::iterator it = m_kProcessArray.Begin(); it != m_kProcessArray.End(); ++it)
	{
		(*it)->OnDel();
	}
	m_kProcessMap.Clear();
	m_kProcessArray.Clear();
	m_kNodeDataMap.Clear();
	m_kNodeDataArray.Clear();

	m_spBackBufferTEX = NULL;
	m_spBackBufferRTV = NULL;
}
//--------------------------------------------------------------------------
void VeRendererD3D11::ResetStateCache()
{
	m_kVertexShaderStack.Clear();
	m_pkCurVertexShader = NULL;
	m_kPixelShaderStack.Clear();
	m_pkCurPixelShader = NULL;
	m_kBlendStateStack.Clear();
	VeZeroMemory(&m_kCurBlendState, sizeof(m_kCurBlendState));
	m_kCurBlendState.m_uiSampleMask = 0xffffffff;
	m_bBlendStateChange = FALSE;
	m_kDepthStencilStateStack.Clear();
	VeZeroMemory(&m_kCurDepthStencilState, sizeof(m_kCurDepthStencilState));
	m_bDepthStencilStateChange = FALSE;
	m_kInputLayoutStack.Clear();
	m_pkCurInputLayout = NULL;
	m_kRasterizerStateStack.Clear();
	m_pkCurRasterizerState = NULL;
	m_kTopologyStack.Clear();
	m_eCurTopology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	m_kIndexBufferStack.Clear();
	m_pkCurIndexBuffer = NULL;
	m_eCurIndexBufferFormat = DXGI_FORMAT_UNKNOWN;

	for(VeUInt32 i(0); i < D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT; ++i)
	{
		m_akVertexBufferStack[i].Clear();
	}
	VeZeroMemory(m_apkCurVertexBuffers, sizeof(m_apkCurVertexBuffers));
	VeZeroMemory(m_auiCurVertexBufferStrides, sizeof(m_auiCurVertexBufferStrides));
	VeZeroMemory(m_auiCurVertexBufferOffsets, sizeof(m_auiCurVertexBufferOffsets));
	m_u32VertexBufferChangeMin = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
	m_u32VertexBufferChangeMax = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;

	for(VeUInt32 i(0); i < D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
	{
		m_akVSCBufferStack[i].Clear();
	}
	VeZeroMemory(m_apkCurVSCBuffers, sizeof(m_apkCurVSCBuffers));
	m_u32VSChangeCBufferMin = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;
	m_u32VSChangeCBufferMax = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;

	for(VeUInt32 i(0); i < VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
	{
		m_akPSSamplerStack[i].Clear();
	}
	VeZeroMemory(m_apkCurPSSamplers, sizeof(m_apkCurPSSamplers));
	m_u32PSChangeSamplerMin = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
	m_u32PSChangeSamplerMax = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

	for(VeUInt32 i(0); i < VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
	{
		m_akPSShaderResourceViewStack[i].Clear();
	}
	VeZeroMemory(m_apkCurPSShaderResourceViews, sizeof(m_apkCurPSShaderResourceViews));
	m_u32PSChangeSRVMin = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;
	m_u32PSChangeSRVMax = VE_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

	for(VeUInt32 i(0); i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
	{
		m_akViewportStack[i].Clear();
	}
	VeZeroMemory(m_akCurViewports, sizeof(m_akCurViewports));
	for(VeUInt32 i(0); i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
	{
		m_akCurViewports[i].MinDepth = 0.0f;
		m_akCurViewports[i].MaxDepth = 1.0f;
	}
	m_u32ActiveViewportCount = 0;
	m_u32ViewportChangeMax = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;

	for(VeUInt32 i(0); i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
	{
		m_akScissorRectStack[i].Clear();
	}
	VeZeroMemory(m_akCurScissorRects, sizeof(m_akCurScissorRects));
	m_u32ActiveScissorRectCount = 0;
	m_u32ScissorRectChangeMax = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;

	for(VeUInt32 i(0); i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
	{
		m_akRenderTargetViewStack[i].Clear();
	}
	m_kDepthStencilViewStack.Clear();
	VeZeroMemory(m_apkCurRenderTargetViews, sizeof(m_apkCurRenderTargetViews));
	m_pkCurDepthStencilView = NULL;
	m_u32ActiveRenderTargetCount = 0;
	m_u32RenderTargetViewChangeMax = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
}
//--------------------------------------------------------------------------
void VeRendererD3D11::SetNull(const VeRODepthStencilViewD3D11Ptr& spDepthStencilView)
{
	VE_ASSERT(m_pkCurDepthStencilView == spDepthStencilView->m_pkDepthStencilView);
	m_pkCurDepthStencilView = NULL;
	m_pkImmediateContext->OMSetRenderTargets(m_u32ActiveRenderTargetCount, m_apkCurRenderTargetViews, m_pkCurDepthStencilView);
}
//--------------------------------------------------------------------------
void VeRendererD3D11::SetNull(const VeRORenderTargetViewD3D11Ptr& spRenderTargetView)
{
	if(m_apkCurRenderTargetViews[spRenderTargetView->m_u32Active] == spRenderTargetView->m_pkRenderTargetView)
	{
		m_apkCurRenderTargetViews[spRenderTargetView->m_u32Active] = NULL;
		m_pkImmediateContext->OMSetRenderTargets(m_u32ActiveRenderTargetCount, m_apkCurRenderTargetViews, m_pkCurDepthStencilView);
		if(spRenderTargetView->m_u32Active == (m_u32ActiveRenderTargetCount - 1))
		{
			--m_u32ActiveRenderTargetCount;
		}
	}
	spRenderTargetView->m_u32Active = VeUInt32(-1);
}
//--------------------------------------------------------------------------
void VeRendererD3D11::SetNull(const VeROShaderResourceViewD3D11Ptr& spShaderResourceView)
{
	{
		VeUInt8 u8Active = spShaderResourceView->m_au8Active[VeRenderer::PIXEL_SHADER];
		if(u8Active != 0xFF && m_apkCurPSShaderResourceViews[u8Active] == spShaderResourceView->m_pkShaderResourceView)
		{
			m_apkCurPSShaderResourceViews[u8Active] = NULL;
			m_pkImmediateContext->PSSetShaderResources(u8Active, 1, m_apkCurPSShaderResourceViews + u8Active);
		}
	}
	spShaderResourceView->m_u64Active = VeUInt64(-1);
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateRenderObjects()
{
	VeMemoryOStream kStream;
	VeFixedString kName;

	kStream << VeUInt16(VE_FALSE);
	kStream << VeUInt16(1);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VeRenderer::BLEND_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::COLOR_WRITE_ENABLE_ALL);
	g_pRenderer->CreateBlendState("blend_alpha", kStream);
	kStream.Reset();

	kStream << VeUInt16(VE_FALSE);
	kStream << VeUInt16(1);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::COLOR_WRITE_ENABLE_ALL);
	g_pRenderer->CreateBlendState("blend_add", kStream);
	kStream.Reset();

	kStream << VeUInt16(VE_FALSE);
	kStream << VeUInt16(1);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::BLEND_ONE);
	kStream << VeUInt8(VeRenderer::BLEND_INV_SRC_ALPHA);
	kStream << VeUInt8(VeRenderer::BLEND_OP_ADD);
	kStream << VeUInt8(VeRenderer::COLOR_WRITE_ENABLE_ALL);
	g_pRenderer->CreateBlendState("blend_alpha_mul", kStream);
	kStream.Reset();

	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VeRenderer::COMPARISON_ALWAYS);
	kStream << VeUInt8(VE_FALSE);
	g_pRenderer->CreateDepthStencilState("no_depth", kStream);
	kStream.Reset();

	kStream << VeUInt8(VeRenderer::FILL_SOLID);
	kStream << VeUInt8(VeRenderer::CULL_NONE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VeRenderer::DBIAS_NONE);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	g_pRenderer->CreateRasterizerState("draw_2d", kStream);
	kStream.Reset();

	kStream << VeUInt8(VeRenderer::FILL_SOLID);
	kStream << VeUInt8(VeRenderer::CULL_NONE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VeRenderer::DBIAS_NONE);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VE_TRUE);
	kStream << VeUInt8(VE_FALSE);
	kStream << VeUInt8(VE_FALSE);
	g_pRenderer->CreateRasterizerState("draw_2d_clip", kStream);
	kStream.Reset();

	kStream << VeUInt8(VeRenderer::FILTER_MIN_MAG_LINEAR_MIP_POINT);
	kStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
	kStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
	kStream << VeUInt8(VeRenderer::TEXTURE_ADDRESS_CLAMP);
	kStream << VeUInt16(16);
	kStream << VeUInt16(VeRenderer::COMPARISON_NEVER);
	kStream << 0.0f;
	kStream << -VE_MAXFLOAT_F;
	kStream << VE_MAXFLOAT_F;
	kStream << VeColor::BLACK;
	g_pRenderer->CreateSamplerState("tri_linear", kStream);
	kStream.Reset();

	kStream << VeUInt32(16);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(1);
	kStream << VeUInt32(16);
	kStream << VeUInt32(16);
	kStream << GetInvWidthF();
	kStream << GetInvHeightF();
	kStream << 1000.0f;
	kStream << (GetHeightF() * GetInvWidthF());
	g_pRenderer->CreateBuffer("screen_params", kStream);
	kStream.Reset();

	kName = "draw_sprite_base";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeByte(VeRenderer::SE_POSITION);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R32G32_FLOAT);
	kStream << VeByte(0);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	g_pRenderer->CreateInputLayout("draw_sprite_base", kStream);
	kStream.Reset();

	kName = "draw_color_shape";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeByte(VeRenderer::SE_POSITION);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R32G32_FLOAT);
	kStream << VeByte(0);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	g_pRenderer->CreateInputLayout("draw_color_shape", kStream);
	kStream.Reset();

	kName = "draw_text";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(1);
	kStream << VeByte(VeRenderer::SE_POSITION);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::FMT_R32G32_FLOAT);
	kStream << VeByte(0);
	kStream << VeByte(0);
	kStream << VeByte(VeRenderer::PER_VERTEX_DATA);
	kStream << VeUInt16(0);
	g_pRenderer->CreateInputLayout("draw_text", kStream);
	kStream.Reset();

	VeFloat32 af32Buffer[8] = { 0,0,1,0,0,1,1,1 };
	kStream << VeUInt32(sizeof(af32Buffer));
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kStream << VeByte(VeRenderer::BIND_VERTEX_BUFFER);
	kStream << VeByte(0);
	kStream << VeByte(1);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	kStream.Write(af32Buffer, sizeof(af32Buffer));
	g_pRenderer->CreateBuffer("quad_vb", kStream);
	kStream.Reset();

	kStream << VeUInt32(sizeof(VeUInt16) * 6);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kStream << VeByte(VeRenderer::BIND_INDEX_BUFFER);
	kStream << VeByte(0);
	kStream << VeByte(1);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	{
		VeUInt16 au16Quad[6] = { 0,1,2,2,1,3 };
		kStream.AddBlob(au16Quad, VeInt32(sizeof(au16Quad)));
	}
	g_pRenderer->CreateBuffer("quad_ib", kStream);
	kStream.Reset();

	kStream << VeUInt32(sizeof(VeUInt16) * 8);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DEFAULT);
	kStream << VeByte(VeRenderer::BIND_INDEX_BUFFER);
	kStream << VeByte(0);
	kStream << VeByte(1);
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	{
		VeUInt16 au16Quad[8] = { 0,1,1,3,3,2,2,0 };
		kStream.AddBlob(au16Quad, VeInt32(sizeof(au16Quad)));
	}
	g_pRenderer->CreateBuffer("square_frame_ib", kStream);
	kStream.Reset();

	kStream << VeUInt32(80 * VE_MAX_COMBINED_SPRITE);
	kStream << VeUInt16(0);
	kStream << VeUInt16(0);
	kStream << VeByte(VeRenderer::USAGE_DYNAMIC);
	kStream << VeByte(VeRenderer::BIND_CONSTANT_BUFFER);
	kStream << VeByte(VeRenderer::CPU_ACCESS_WRITE);
	kStream << VeByte(0);
	g_pRenderer->CreateBuffer("quad_cb", kStream);
}
//--------------------------------------------------------------------------
void VeRendererD3D11::CreateNodeDatas()
{
	VeMemoryOStream kStream;
	VeFixedString kName;

	kStream << VeUInt32(3);
	kStream << VeRenderTick::VS_CONSTANT_BUFFER;
	kName = "screen_params";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeRenderTick::OM_DEPTH_STENCIL_STATE;
	kName = "no_depth";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeRenderTick::RS_STATE;
	kName = "draw_2d";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_root", kStream);
	kStream.Reset();

	kStream << VeUInt32(7);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_sprite_base";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(8);
	kStream << VeUInt32(0);
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "quad_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeRenderTick::PS_SAMPLER;
	kName = "tri_linear";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_sprite", kStream);
	kStream.Reset();

	kStream << VeUInt32(6);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_color_shape";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_LINELIST;
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(8);
	kStream << VeUInt32(0);
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "square_frame_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_square_frame", kStream);
	kStream.Reset();

	kStream << VeUInt32(6);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_color_shape";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(8);
	kStream << VeUInt32(0);
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "quad_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_square", kStream);
	kStream.Reset();

	kStream << VeUInt32(8);
	kStream << VeRenderTick::VS_SHADER;
	kName = "draw_text";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::PS_SHADER;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_INPUT_LAYOUT;
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderTick::IA_PRIMITIVE_TOPOLOGY;
	kStream << VeIAPrimitiveTopology::TOPOLOGY_TRIANGLELIST;
	kStream << VeRenderTick::IA_VERTEX_BUFFER;
	kName = "quad_vb";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt16(0);
	kStream << VeUInt16(8);
	kStream << VeUInt32(0);
	kStream << VeRenderTick::IA_INDEX_BUFFER;
	kName = "quad_ib";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeRenderer::FMT_R16_UINT;
	kStream << VeRenderTick::PS_SAMPLER;
	kName = "tri_linear";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << VeUInt32(0);
	kStream << VeRenderTick::OM_BLEND_STATE;
	kName = "blend_alpha";
	kStream.AppendStringAligned4(kName, kName.GetLength());
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0;
	kStream << 0xffffffff;
	kStream << VeUInt32(0);
	g_pRenderer->CreateRenderNodeData("draw_2d_text", kStream);
	kStream.Reset();
}
//--------------------------------------------------------------------------
VeRendererD3D11::Output::Output() : m_pkDXGIOutput(NULL)
{

}
//--------------------------------------------------------------------------
VeRendererD3D11::Output::~Output()
{
	VE_SAFE_RELEASE(m_pkDXGIOutput);
}
//--------------------------------------------------------------------------
VeUInt32 VeRendererD3D11::Output::KeyToHashCode(const VePair<VeUInt32,VePair<VeUInt32,VeUInt32>>& kKey, VeUInt32 u32TableSize)
{
	return (kKey.m_tFirst * kKey.m_tSecond.m_tFirst * kKey.m_tSecond.m_tSecond) % u32TableSize;
}
//--------------------------------------------------------------------------
VeRendererD3D11::Adapter::Adapter() : m_pkDXGIAdapter(NULL)
{

}
//--------------------------------------------------------------------------
VeRendererD3D11::Adapter::~Adapter()
{
	VE_SAFE_RELEASE(m_pkDXGIAdapter);
}
//--------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------
