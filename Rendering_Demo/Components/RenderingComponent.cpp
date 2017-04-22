#include "RenderingComponent.h"

void RenderingComponent::PrepareGPUBuffer()
{
	m_relatedEffect->PrepareVertexBuffer(this,stride);

	//create index buffer
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * (UINT)m_indexBufferCPU.size();
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

	D3D11Renderer::Instance()->GetD3DContext()->IASetVertexBuffers(0, 1, &m_VertexBufferGPU, &stride, &offset);

	D3D11Renderer::Instance()->GetD3DContext()->IASetIndexBuffer(m_indexBufferGPU, DXGI_FORMAT_R32_UINT, 0);

	LightManager::Instance()->BindLights(this);

	D3D11Renderer::Instance()->UpdatePerObjectCB(this);

	D3D11Renderer::Instance()->GetD3DContext()->DrawIndexed((UINT)m_indexBufferCPU.size(), 0, 0);
}

void RenderingComponent::Prepare()
{
	if (m_relatedEffect == NULL)
		EffectManager::Instance()->SetEffect(this, EffectManager::Instance()->defaultEffect);

	PrepareGPUBuffer();
}

void RenderingComponent::SetEffect(Effect* eff)
{
	if (m_relatedEffect != nullptr){
		m_relatedEffect->RemoveRenderingComponent(this);
	}

	m_relatedEffect = eff;
}

RenderingComponent::RenderingComponent()
{
}


RenderingComponent::~RenderingComponent()
{
	ReleaseCOM(m_indexBufferGPU);
	ReleaseCOM(m_VertexBufferGPU);
}


RenderingComponent* RenderingComponent::CreateStandardBox()
{
	RenderingComponent* box = new RenderingComponent();

	box->m_positionBufferCPU =
	{
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(1.0f, 1.0f, -1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
		Vector3(1.0f, -1.0f, 1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, 1.0f, -1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(1.0f, -1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
	};

	box->m_normalBufferCPU =
	{
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f),
		Vector3(-1.0f, 0.0f, 0.0f),
		Vector3(-1.0f, 0.0f, 0.0f),
		Vector3(-1.0f, 0.0f, 0.0f),
		Vector3(-1.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(0.0f, 0.0f, 1.0f),
	};

	box->m_texCoordBufferCPU = 
	{
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f),
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f),
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f),
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f),
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f),
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Vector2(0.0f, 1.0f),
	};

	box->m_indexBufferCPU =
	{
		3, 1, 0,
		2, 1, 3,
		6, 4, 5,
		7, 4, 6,
		11, 9, 8,
		10, 9, 11,
		14, 12, 13,
		15, 12, 14,
		19, 17, 16,
		18, 17, 19,
		22, 20, 21,
		23, 20, 22
	};

	EffectManager::Instance()->SetEffect(box, EffectManager::Instance()->defaultEffect);

	return box;
}