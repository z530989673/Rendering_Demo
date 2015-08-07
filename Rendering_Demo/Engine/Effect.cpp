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

	CreateInputLayout();
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

void Effect::CreateInputLayout()
{
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

void Effect::Prepare() {
	//set shader
	D3D11Renderer::Instance()->GetD3DContext()->VSSetShader(m_vertexShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->PSSetShader(m_pixelShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->GSSetShader(m_geometryShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->HSSetShader(m_hullShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->DSSetShader(m_domainShader, 0, 0);
	D3D11Renderer::Instance()->GetD3DContext()->CSSetShader(m_computeShader, 0, 0);

	//set InputLayout
	D3D11Renderer::Instance()->GetD3DContext()->IASetInputLayout(m_inputLayout);
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
}
