#include "Effect.h"
#include "D3DCompiler.h"


Effect::Effect()
{
}

Effect::Effect(const std::wstring& vsPath,
	const std::wstring& psPath,
	const std::wstring& gsPath = L"",
	const std::wstring& hsPath = L"",
	const std::wstring& dsPath = L"",
	const std::wstring& csPath = L"") :
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
}

void Effect::ReadShaderFile(std::wstring filename, ID3DBlob **blob, char* target, char* entryPoint) {
	HRESULT hr;
	hr = D3DCompileFromFile(
		filename.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		target,
		D3DCOMPILE_DEBUG,
		0,
		blob,
		nullptr
		);
	HR(hr);
}

Effect::~Effect()
{
	SafeDeleteArray(m_shaderResources);
	ReleaseCOM(m_vertexShader);
	ReleaseCOM(m_pixelShader);
	ReleaseCOM(m_geometryShader);
	ReleaseCOM(m_hullShader);
	ReleaseCOM(m_domainShader);
	ReleaseCOM(m_computeShader);
}
