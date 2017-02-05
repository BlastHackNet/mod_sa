/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "main.h"

#pragma data_seg( ".d3d9_shared" )
proxyIDirect3D9 *pDirect3D9 = NULL;
#pragma data_seg()
proxyIDirect3D9::proxyIDirect3D9 ( IDirect3D9 *pOriginal )
{
	//Log("proxyIDirect3D9 constructor called. Original IDirect3D9 interface address is 0x%p.", pOriginal);
	origIDirect3D9 = pOriginal;

	// to allow computers with Aero to disable so the window doesn't get minimized by
	// other windows switching off Aero.
	// we don't need this since there is fix for windows aero
	// Sleep(1000);
}

proxyIDirect3D9::~proxyIDirect3D9 ( void )
{
	//Log("proxyIDirect3D9 destructor called.");
	origIDirect3D9 = NULL;
}

HRESULT __stdcall proxyIDirect3D9::QueryInterface ( REFIID riid, void **ppvObj )
{
	HRESULT hRes;

	*ppvObj = NULL;
	hRes = origIDirect3D9->QueryInterface( riid, ppvObj );
	if ( hRes == NOERROR )
		*ppvObj = this;

	return hRes;
}

ULONG __stdcall proxyIDirect3D9::AddRef ( void )
{
	return origIDirect3D9->AddRef();
}

ULONG __stdcall proxyIDirect3D9::Release ( void )
{
	ULONG	count = origIDirect3D9->Release();

	if ( count == 0 )
	{
		pDirect3D9 = NULL;
		delete( this );
	}

	return count;
}

HRESULT __stdcall proxyIDirect3D9::RegisterSoftwareDevice ( void *pInitializeFunction )
{
	return origIDirect3D9->RegisterSoftwareDevice( pInitializeFunction );
}

UINT __stdcall proxyIDirect3D9::GetAdapterCount ( void )
{
	return origIDirect3D9->GetAdapterCount();
}

HRESULT __stdcall proxyIDirect3D9::GetAdapterIdentifier ( UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 *pIdentifier )
{
	return origIDirect3D9->GetAdapterIdentifier( Adapter, Flags, pIdentifier );
}

UINT __stdcall proxyIDirect3D9::GetAdapterModeCount ( UINT Adapter, D3DFORMAT Format )
{
	return origIDirect3D9->GetAdapterModeCount( Adapter, Format );
}

HRESULT __stdcall proxyIDirect3D9::EnumAdapterModes ( UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE *pMode )
{
	return origIDirect3D9->EnumAdapterModes( Adapter, Format, Mode, pMode );
}

HRESULT __stdcall proxyIDirect3D9::GetAdapterDisplayMode ( UINT Adapter, D3DDISPLAYMODE *pMode )
{
	return origIDirect3D9->GetAdapterDisplayMode( Adapter, pMode );
}

HRESULT __stdcall proxyIDirect3D9::CheckDeviceType ( UINT iAdapter, D3DDEVTYPE DevType, D3DFORMAT DisplayFormat,
													 D3DFORMAT BackBufferFormat, BOOL bWindowed )
{
	return origIDirect3D9->CheckDeviceType( iAdapter, DevType, DisplayFormat, BackBufferFormat, bWindowed );
}

HRESULT __stdcall proxyIDirect3D9::CheckDeviceFormat ( UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat,
													   DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat )
{
	return origIDirect3D9->CheckDeviceFormat( Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat );
}

HRESULT __stdcall proxyIDirect3D9::CheckDeviceMultiSampleType ( UINT Adapter, D3DDEVTYPE DeviceType,
																D3DFORMAT SurfaceFormat, BOOL Windowed,
																D3DMULTISAMPLE_TYPE MultiSampleType,
																DWORD *pQualityLevels )
{
	return origIDirect3D9->CheckDeviceMultiSampleType( Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType,
													   pQualityLevels );
}

HRESULT __stdcall proxyIDirect3D9::CheckDepthStencilMatch ( UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat,
															D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat )
{
	return origIDirect3D9->CheckDepthStencilMatch( Adapter, DeviceType, AdapterFormat, RenderTargetFormat,
												   DepthStencilFormat );
}

HRESULT __stdcall proxyIDirect3D9::CheckDeviceFormatConversion ( UINT Adapter, D3DDEVTYPE DeviceType,
																 D3DFORMAT SourceFormat, D3DFORMAT TargetFormat )
{
	return origIDirect3D9->CheckDeviceFormatConversion( Adapter, DeviceType, SourceFormat, TargetFormat );
}

HRESULT __stdcall proxyIDirect3D9::GetDeviceCaps ( UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps )
{
	return origIDirect3D9->GetDeviceCaps( Adapter, DeviceType, pCaps );
}

HMONITOR __stdcall proxyIDirect3D9::GetAdapterMonitor ( UINT Adapter )
{
	return origIDirect3D9->GetAdapterMonitor( Adapter );
}

HRESULT __stdcall proxyIDirect3D9::CreateDevice ( UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow,
												  DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters,
												  IDirect3DDevice9 **ppReturnedDeviceInterface )
{
	HRESULT hRes;

	ulFullScreenRefreshRate = pPresentationParameters->FullScreen_RefreshRateInHz;

	if ( set.window_mode && *(byte*)0x746225 != 0x90)
	{
		int x, y;
		x = GetSystemMetrics( SM_CXSCREEN );
		y = GetSystemMetrics( SM_CYSCREEN );
		SetWindowLong( pPresentationParameters->hDeviceWindow, GWL_STYLE, WS_POPUP );
		MoveWindow( pPresentationParameters->hDeviceWindow, (x / 2) - (pPresentationParameters->BackBufferWidth / 2),
					(y / 2) - (pPresentationParameters->BackBufferHeight / 2), pPresentationParameters->BackBufferWidth,
					pPresentationParameters->BackBufferHeight, TRUE );

		pPresentationParameters->Windowed = true;
		pPresentationParameters->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}

	hRes = origIDirect3D9->CreateDevice( Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters,
										 ppReturnedDeviceInterface );

	if ( hRes == D3D_OK )
		*ppReturnedDeviceInterface = new proxyIDirect3DDevice9( *ppReturnedDeviceInterface );

	// according to Ant docs, this is where it should be, but we're not doing it here
	/*if (!set.use_old_menu)
	{
		TwInit(TW_DIRECT3D9, ppReturnedDeviceInterface);
	}*/

	return hRes;
}
