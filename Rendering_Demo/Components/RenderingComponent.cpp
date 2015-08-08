#include "RenderingComponent.h"

void RenderingComponent::PrepareGPUBuffer()
{
	//create vertex buffer
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(XMFLOAT3) * m_positionBufferCPU.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vInitData;
	ZeroMemory(&vInitData, sizeof(vInitData));
	vInitData.pSysMem = &m_positionBufferCPU[0];
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateBuffer(&vbd, &vInitData, &m_VertexBufferGPU));

	//create index buffer
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * m_indexBufferCPU.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA iInitData;
	ZeroMemory(&iInitData, sizeof(iInitData));
	iInitData.pSysMem = &m_indexBufferCPU[0];
	HR(D3D11Renderer::Instance()->GetD3DDevice()->CreateBuffer(&ibd, &iInitData, &m_indexBufferGPU));

	
}

void RenderingComponent::Draw()
{
	D3D11Renderer::Instance()->GetD3DContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(XMFLOAT3);
	UINT offset = 0;

	D3D11Renderer::Instance()->GetD3DContext()->IASetVertexBuffers(0, 1, &m_VertexBufferGPU, &stride, &offset);

	D3D11Renderer::Instance()->GetD3DContext()->IASetIndexBuffer(m_indexBufferGPU, DXGI_FORMAT_R32_UINT, 0);

	relatedEffect->UpdateConstantBuffer(this);

	D3D11Renderer::Instance()->GetD3DContext()->DrawIndexed(m_indexBufferCPU.size(), 0, 0);
}

void RenderingComponent::Prepare()
{
	if (relatedEffect == NULL)
		EffectManager::Instance()->SetDefaultEffect(this);

	PrepareGPUBuffer();
}

RenderingComponent::RenderingComponent()
{
	m_positionBufferCPU =
	{
		XMFLOAT3(-1.0f, 1.0f, -1.0f), 
		XMFLOAT3(1.0f, 1.0f, -1.0f),
		XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3(-1.0f, 1.0f, 1.0f),
		XMFLOAT3(-1.0f, -1.0f, -1.0f),
		XMFLOAT3(1.0f, -1.0f, -1.0f),
		XMFLOAT3(1.0f, -1.0f, 1.0f),
		XMFLOAT3(-1.0f, -1.0f, 1.0f),
	};

	m_indexBufferCPU =
	{
		3, 1, 0,
		2, 1, 3,

		0, 5, 4,
		1, 5, 0,

		3, 4, 7,
		0, 4, 3,

		1, 6, 5,
		2, 6, 1,

		2, 7, 6,
		3, 7, 2,

		6, 4, 5,
		7, 4, 6,
	};

	EffectManager::Instance()->SetDefaultEffect(this);
}


RenderingComponent::~RenderingComponent()
{
	ReleaseCOM(m_indexBufferGPU);
	ReleaseCOM(m_VertexBufferGPU);
}
