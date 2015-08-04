#pragma once

#include <d3d11.h>
#include <d3dx11.h>

class D3D11Render
{
public:
	D3D11Render();
	~D3D11Render();

	void Render();

	HRESULT InitDevice(HWND g_hWnd);
	void CleanupDevice();

private:

	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           g_pd3dDevice = NULL;
	ID3D11DeviceContext*    g_pImmediateContext = NULL;
	IDXGISwapChain*         g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;
};

