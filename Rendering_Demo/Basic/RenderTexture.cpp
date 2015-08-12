#include "RenderTexture.h"

void RenderTexture::SetRenderTarget()
{
	D3D11Renderer::Instance()->GetD3DContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
}

void RenderTexture::CleanBuffer()
{
	D3D11Renderer::Instance()->GetD3DContext()->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	D3D11Renderer::Instance()->GetD3DContext()->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

RenderTexture::RenderTexture(unsigned int w, unsigned int h):
	width(w),
	height(h)
{
	clearColor[0] = 0.2f;
	clearColor[1] = 0.2f;
	clearColor[2] = 0.2f;
	clearColor[3] = 1.0f;
	D3D11_TEXTURE2D_DESC descRenderTarget;
	ZeroMemory(&descRenderTarget, sizeof(descRenderTarget));
	descRenderTarget.Width = width;
	descRenderTarget.Height = height;
	descRenderTarget.MipLevels = 1;
	descRenderTarget.ArraySize = 1;
	descRenderTarget.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	descRenderTarget.SampleDesc.Count = 1;
	descRenderTarget.SampleDesc.Quality = 0;
	descRenderTarget.Usage = D3D11_USAGE_DEFAULT;
	descRenderTarget.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	descRenderTarget.CPUAccessFlags = 0;
	descRenderTarget.MiscFlags = 0;
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateTexture2D(&descRenderTarget, NULL, &m_pRenderTarget));

	D3D11_RENDER_TARGET_VIEW_DESC descRTV;
	ZeroMemory(&descRTV, sizeof(descRTV));
	descRTV.Format = descRenderTarget.Format;
	descRTV.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	descRTV.Texture2D.MipSlice = 0;
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateRenderTargetView(m_pRenderTarget, &descRTV, &m_pRenderTargetView));

	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView));
}


RenderTexture::~RenderTexture()
{
}
