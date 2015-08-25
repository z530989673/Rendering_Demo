#include "D3D11Renderer.h"

D3D11Renderer* D3D11Renderer::_instance = nullptr;

// Create Direct3D device and swap chain
HRESULT D3D11Renderer::Init(HWND g_hWnd)
{
	HRESULT hr = S_OK;

	RECT rc = Game::Instance()->GetScreenRect();
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	m_aspectRatio = width / (float)height;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pDeviceContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	HR( m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer));


	HR(m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView));
	pBackBuffer->Release();

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
	HR(m_pd3dDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	HR(m_pd3dDevice->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView));

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pDeviceContext->RSSetViewports(1, &vp);


	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(m_pd3dDevice->CreateSamplerState(&sampDesc, &m_pSamplerLinear));

	m_perCameraCB = new PERCAMERA_CONSTANT_BUFFER();
	m_perObjCB = new PEROBJ_CONSTANT_BUFFER();

	// Create the per camera buffer.
	D3D11_BUFFER_DESC cbCameraDesc;
	cbCameraDesc.ByteWidth = sizeof(PERCAMERA_CONSTANT_BUFFER);
	cbCameraDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbCameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbCameraDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbCameraDesc.MiscFlags = 0;
	cbCameraDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitCameraData;
	InitCameraData.pSysMem = m_perCameraCB;
	InitCameraData.SysMemPitch = 0;
	InitCameraData.SysMemSlicePitch = 0;

	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateBuffer(&cbCameraDesc, &InitCameraData,
		&m_perCameraCBGPU));

	// Create the per object buffer.
	D3D11_BUFFER_DESC cbObjDesc;
	cbObjDesc.ByteWidth = sizeof(PEROBJ_CONSTANT_BUFFER);
	cbObjDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbObjDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbObjDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbObjDesc.MiscFlags = 0;
	cbObjDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitObjData;
	InitObjData.pSysMem = m_perObjCB;
	InitObjData.SysMemPitch = 0;
	InitObjData.SysMemSlicePitch = 0;

	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateBuffer(&cbObjDesc, &InitObjData,
		&m_perObjCBGPU));

	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_perCameraCBGPU);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_perCameraCBGPU);

	m_pDeviceContext->VSSetConstantBuffers(1, 1, &m_perObjCBGPU);
	m_pDeviceContext->PSSetConstantBuffers(1, 1, &m_perObjCBGPU);

	return S_OK;
}

// Clean up the objects we've created
void D3D11Renderer::CleanupDevice()
{
	if (m_pDeviceContext) m_pDeviceContext->ClearState();

	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pSwapChain) m_pSwapChain->Release();
	if (m_pDeviceContext) m_pDeviceContext->Release();
	if (m_pd3dDevice) m_pd3dDevice->Release();
}

// Render the frame
void D3D11Renderer::Draw()
{
	ID3D11SamplerState* samplerState[] = { m_pSamplerLinear, };
	UINT samplerStateSize = ARRAYSIZE(samplerState);
	m_pDeviceContext->PSSetSamplers(0, samplerStateSize, samplerState);
	m_pDeviceContext->VSSetSamplers(0, samplerStateSize, samplerState);
	m_pDeviceContext->DSSetSamplers(0, samplerStateSize, samplerState);
	m_pDeviceContext->HSSetSamplers(0, samplerStateSize, samplerState);
	m_pDeviceContext->GSSetSamplers(0, samplerStateSize, samplerState);
	m_pDeviceContext->CSSetSamplers(0, samplerStateSize, samplerState);

	std::vector<CameraComponent*>* cameras = CameraManager::Instance()->getAllCameras();

	for (CameraComponent* cc : *cameras)
	{
		if (!cc->isEnabled())
			continue;

		if (cc != CameraManager::Instance()->GetMainCamera() && cc->GetRenderTarget() != nullptr)
		{
			cc->Bind();
			UpdatePerCameraCB(cc);
			EffectManager::Instance()->DrawEffects();
		}
	}

	if (CameraManager::Instance()->GetMainCamera()->isEnabled())
	{
		float ClearColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
		m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
		CameraComponent* mainCamera = CameraManager::Instance()->GetMainCamera();
		UpdatePerCameraCB(mainCamera);
		EffectManager::Instance()->DrawEffects();
	}

	m_pSwapChain->Present(0, 0);
}


void D3D11Renderer::UpdatePerCameraCB(CameraComponent* cc)
{
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_perCameraCBGPU);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_perCameraCBGPU);

	m_perCameraCB->View = XMMatrixTranspose(XMLoadFloat4x4(&cc->m_view));
	m_perCameraCB->Projection = XMMatrixTranspose(XMLoadFloat4x4(&cc->m_proj));
	m_perCameraCB->EyePosition = cc->m_eyePos;
	//m_perCameraCB->ViewProj = m_perCameraCB->View * m_perCameraCB->Projection;


	D3D11_MAPPED_SUBRESOURCE ms;
	D3D11Renderer::Instance()->GetD3DContext()->Map(m_perCameraCBGPU, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, m_perCameraCB, sizeof(PERCAMERA_CONSTANT_BUFFER));
	D3D11Renderer::Instance()->GetD3DContext()->Unmap(m_perCameraCBGPU, NULL);
}

void D3D11Renderer::UpdatePerObjectCB(RenderingComponent* rc)
{
	m_perObjCB->World = XMMatrixTranspose(XMLoadFloat4x4(&rc->gameObject->GetWorldTransform()));

	D3D11_MAPPED_SUBRESOURCE ms;
	D3D11Renderer::Instance()->GetD3DContext()->Map(m_perObjCBGPU, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, m_perObjCB, sizeof(PEROBJ_CONSTANT_BUFFER));
	D3D11Renderer::Instance()->GetD3DContext()->Unmap(m_perObjCBGPU, NULL);
}

D3D11Renderer::D3D11Renderer()
{
}


D3D11Renderer::~D3D11Renderer()
{
}
