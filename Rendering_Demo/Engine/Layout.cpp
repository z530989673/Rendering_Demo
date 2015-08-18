#include "Layout.h"

void Layout::SetLayout()
{
	D3D11Renderer::Instance()->GetD3DContext()->IASetInputLayout(m_inputLayout);
}

Layout::Layout()
{
}


Layout::~Layout()
{
	ReleaseCOM(m_inputLayout);
}

void BasicLayout::PrepareVertexBuffer(RenderingComponent* rc)
{
	//create vertex buffer
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(XMFLOAT3) * rc->m_positionBufferCPU.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vInitData;
	ZeroMemory(&vInitData, sizeof(vInitData));
	vInitData.pSysMem = &rc->m_positionBufferCPU[0];
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateBuffer(&vbd, &vInitData, &rc->m_VertexBufferGPU));
}

BasicLayout::BasicLayout(ID3DBlob *vsBlob)
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(), &m_inputLayout));
}


BasicLayout::~BasicLayout()
{	
}