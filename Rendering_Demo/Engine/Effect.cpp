#include "Effect.h"
#include "D3DCompiler.h"

Effect::Effect()
{
}

Effect::Effect(const std::wstring& vsPath,
	const std::wstring& psPath,
	const std::wstring& gsPath,
	const std::wstring& hsPath,
	const std::wstring& dsPath,
	const std::wstring& csPath) :
	m_vertexShader(0),
	m_pixelShader(0),
	m_geometryShader(0),
	m_hullShader(0),
	m_domainShader(0),
	m_computeShader(0),
	m_vsBlob(0),
	m_psBlob(0),
	m_gsBlob(0),
	m_hsBlob(0),
	m_dsBlob(0),
	m_csBlob(0)
{
	// Add error checking
	HRESULT hr;

	if (vsPath.length()) {
		ReadShaderFile(vsPath, &m_vsBlob, "vs_5_0");
		hr = D3D11Renderer::Instance()->GetD3DDevice()->CreateVertexShader(
			m_vsBlob->GetBufferPointer(),
			m_vsBlob->GetBufferSize(),
			nullptr,
			&m_vertexShader
			);
		HR(hr);
	}

	if (psPath.length()) {
		ReadShaderFile(psPath, &m_psBlob, "ps_5_0");
		hr = D3D11Renderer::Instance()->GetD3DDevice()->CreatePixelShader(
			m_psBlob->GetBufferPointer(),
			m_psBlob->GetBufferSize(),
			nullptr,
			&m_pixelShader
			);
		HR(hr);
	}

	if (gsPath.length()) {
		ReadShaderFile(gsPath, &m_gsBlob, "gs_5_0");
		hr = D3D11Renderer::Instance()->GetD3DDevice()->CreateGeometryShader(
			m_gsBlob->GetBufferPointer(),
			m_gsBlob->GetBufferSize(),
			nullptr,
			&m_geometryShader
			);
		HR(hr);
	}

	if (hsPath.length()) {
		ReadShaderFile(hsPath, &m_hsBlob, "hs_5_0");
		hr = D3D11Renderer::Instance()->GetD3DDevice()->CreateHullShader(
			m_hsBlob->GetBufferPointer(),
			m_hsBlob->GetBufferSize(),
			nullptr,
			&m_hullShader
			);
		HR(hr);
	}

	if (dsPath.length()) {
		ReadShaderFile(dsPath, &m_dsBlob, "ds_5_0");
		hr = D3D11Renderer::Instance()->GetD3DDevice()->CreateDomainShader(
			m_dsBlob->GetBufferPointer(),
			m_dsBlob->GetBufferSize(),
			nullptr,
			&m_domainShader
			);
		HR(hr);
	}

	if (csPath.length()) {
		ReadShaderFile(csPath, &m_csBlob, "cs_5_0");
		hr = D3D11Renderer::Instance()->GetD3DDevice()->CreateComputeShader(
			m_csBlob->GetBufferPointer(),
			m_csBlob->GetBufferSize(),
			nullptr,
			&m_computeShader
			);
		HR(hr);
	}

	// Create the per object buffer.
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(PEROBJ_CONSTANT_BUFFER);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &m_perObjConstantBuffer;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateBuffer(&cbDesc, &InitData,
		&m_perObjectCB));

	Start();
}

void Effect::AddRenderingComponent(RenderingComponent* rc)
{
	if (std::find(m_renderingComponents.begin(), m_renderingComponents.end(), rc) == m_renderingComponents.end())
	{
		m_renderingComponents.push_back(rc);
	}
}

void Effect::ReadShaderFile(std::wstring filename, ID3DBlob **blob, char* target, char* entryPoint) {
	HRESULT hr;
	ID3DBlob* errMsg;
	hr = D3DCompileFromFile(
		filename.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		target,
		D3DCOMPILE_DEBUG,
		0,
		blob,
		&errMsg
		);
#ifdef DEBUG
	if (errMsg)
	{
		Debug::Log((char*)errMsg->GetBufferPointer());
		errMsg->Release();
	}
#endif
	HR(hr);
}

void Effect::UpdateConstantBuffer(RenderingComponent* rc)
{
	m_perObjConstantBuffer.World = XMMatrixTranspose(XMLoadFloat4x4(&rc->gameObject->GetWorldTransform()));

	//m_perObjConstantBuffer.ViewProj = m_perObjConstantBuffer.View * m_perObjConstantBuffer.Projection;
	//m_perObjConstantBuffer.WorldView = m_perObjConstantBuffer.World * m_perObjConstantBuffer.View;
	//m_perObjConstantBuffer.WorldViewProj = m_perObjConstantBuffer.WorldView * m_perObjConstantBuffer.Projection;

	D3D11_MAPPED_SUBRESOURCE ms;
	D3D11Renderer::Instance()->GetD3DContext()->Map(m_perObjectCB, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, &m_perObjConstantBuffer, sizeof(PEROBJ_CONSTANT_BUFFER));
	D3D11Renderer::Instance()->GetD3DContext()->Unmap(m_perObjectCB, NULL);
}

void Effect::BindConstantBuffer()
{
	D3D11Renderer::Instance()->GetD3DContext()->VSSetConstantBuffers(0, 1, &m_perObjectCB);
	D3D11Renderer::Instance()->GetD3DContext()->PSSetConstantBuffers(0, 1, &m_perObjectCB);
}

void Effect::UnBindConstantBuffer()
{
	D3D11Renderer::Instance()->GetD3DContext()->VSSetConstantBuffers(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->PSSetConstantBuffers(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->HSSetConstantBuffers(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->DSSetConstantBuffers(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->GSSetConstantBuffers(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->CSSetConstantBuffers(0, 0, nullptr);
}

void Effect::UnBindShaderResource()
{
	D3D11Renderer::Instance()->GetD3DContext()->VSSetShaderResources(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->PSSetShaderResources(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->HSSetShaderResources(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->DSSetShaderResources(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->GSSetShaderResources(0, 0, nullptr);
	D3D11Renderer::Instance()->GetD3DContext()->CSSetShaderResources(0, 0, nullptr);
}

void Effect::Start()
{
	int index = 0;
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateInputLayout(layout, numElements, m_vsBlob->GetBufferPointer(),
		m_vsBlob->GetBufferSize(), &m_inputLayout));
}

void Effect::UpdateViewAndProjection(CameraComponent* cc)
{
	m_perObjConstantBuffer.View = XMMatrixTranspose(XMLoadFloat4x4(&cc->m_view));
	m_perObjConstantBuffer.Projection = XMMatrixTranspose(XMLoadFloat4x4(&cc->m_proj));

}

void Effect::BindEffect() {
	//set shader
	D3D11Renderer::Instance()->GetD3DContext()->VSSetShader(m_vertexShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->PSSetShader(m_pixelShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->GSSetShader(m_geometryShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->HSSetShader(m_hullShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->DSSetShader(m_domainShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->CSSetShader(m_computeShader, 0, 0);

	//set InputLayout
	D3D11Renderer::Instance()->GetD3DContext()->IASetInputLayout(m_inputLayout);

	BindConstantBuffer();
	BindShaderResource();
}

void Effect::UnBindEffect() {
	//set shader
	D3D11Renderer::Instance()->GetD3DContext()->VSSetShader(nullptr, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->PSSetShader(nullptr, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->GSSetShader(nullptr, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->HSSetShader(nullptr, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->DSSetShader(nullptr, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->CSSetShader(nullptr, 0, 0);

	UnBindConstantBuffer();
	UnBindShaderResource();
}

Effect::~Effect()
{
	ReleaseCOM(m_vertexShader);
	ReleaseCOM(m_pixelShader);
	ReleaseCOM(m_geometryShader);
	ReleaseCOM(m_hullShader);
	ReleaseCOM(m_domainShader);
	ReleaseCOM(m_computeShader);
	ReleaseCOM(m_inputLayout);
	ReleaseCOM(m_perObjectCB);
}
