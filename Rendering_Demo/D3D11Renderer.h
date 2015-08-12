#pragma once

#include <d3d11.h>
#include <Includes.h>
#include <Engine/EffectManager.h>
#include <Engine/CameraManager.h>
#include <Components/RenderingComponent.h>
#include <Components/CameraComponent.h>
#include <Engine/Game.h>

#include <Basic/RenderTexture.h>

class RenderTexture;

class D3D11Renderer
{
public:
	static D3D11Renderer* Instance() { 
		if (_instance == nullptr)
			_instance = new D3D11Renderer();
		return _instance;
	}

	~D3D11Renderer();

	void Draw();
	HRESULT Init(HWND g_hWnd);
	void CleanupDevice();

	ID3D11Device* GetD3DDevice() { return m_pd3dDevice; }
	ID3D11DeviceContext* GetD3DContext() { return m_pDeviceContext; }
	float GetAspectRatio() { return m_aspectRatio; }

private:
	D3D11Renderer();
	static D3D11Renderer* _instance;

	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice = NULL;
	ID3D11DeviceContext*    m_pDeviceContext = NULL;
	IDXGISwapChain*         m_pSwapChain = NULL;
	ID3D11RenderTargetView* m_pRenderTargetView = NULL;
	ID3D11Texture2D*        m_pDepthStencil = NULL;
	ID3D11DepthStencilView* m_pDepthStencilView = NULL;
	ID3D11SamplerState*     m_pSamplerLinear = NULL;
	float					m_aspectRatio;
};

