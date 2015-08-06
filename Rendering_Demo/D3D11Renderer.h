#pragma once

#include <d3d11.h>

class D3D11Renderer
{
public:
	static D3D11Renderer* Instance() { 
		if (_instance != nullptr)
			return _instance;
		else
			return new D3D11Renderer();
	}

	~D3D11Renderer();

	void Draw();
	HRESULT InitDevice(HWND g_hWnd);
	void CleanupDevice();

	ID3D11Device* GetD3DDevice() { return m_pd3dDevice; }

private:
	D3D11Renderer();
	static D3D11Renderer* _instance;

	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice = NULL;
	ID3D11DeviceContext*    m_pImmediateContext = NULL;
	IDXGISwapChain*         m_pSwapChain = NULL;
	ID3D11RenderTargetView* m_pRenderTargetView = NULL;
};

