#pragma once
#include <d3d11.h>
#include <D3D11Renderer.h>
#include "Includes.h"

class RenderTexture
{
public:
	unsigned int width;
	unsigned int height;
	float clearColor[4];
	RenderTexture(unsigned int w, unsigned int h);
	~RenderTexture();

	ID3D11Texture2D* GetTexture()
	{ 
		ID3D11Resource* rt;
		m_pRenderTargetView->GetResource(&rt);
		return (ID3D11Texture2D*)rt;
	}

	ID3D11Texture2D* GetDepthTexture(){ return m_pDepthStencil; }

	void CleanBuffer();
	void SetRenderTarget();

private:
	ID3D11Texture2D*        m_pRenderTarget = NULL;
	ID3D11RenderTargetView* m_pRenderTargetView = NULL;
	ID3D11Texture2D*        m_pDepthStencil = NULL;
	ID3D11DepthStencilView* m_pDepthStencilView = NULL;
};

