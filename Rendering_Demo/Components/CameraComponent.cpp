#include "CameraComponent.h"

void CameraComponent::Bind()
{
	if (m_renderTarget)
	{
		m_renderTarget->SetRenderTarget();
		m_renderTarget->CleanBuffer();
	}
}

CameraComponent::CameraComponent()
{
	m_eyePos = XMFLOAT4(0.0f, 0.0f, -2.0f, 0.0f);
	XMVECTOR target = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&m_view, XMMatrixLookAtLH(XMLoadFloat4(&m_eyePos), target, up));
	XMStoreFloat4x4(&m_proj, XMMatrixPerspectiveFovLH(XM_PIDIV2, D3D11Renderer::Instance()->GetAspectRatio(), 0.01f, 100.0f));
}

CameraComponent::CameraComponent(XMFLOAT4 pos, XMFLOAT4 target, XMFLOAT4 up, float fov, float np, float fp)
{
	m_eyePos = pos;
	XMStoreFloat4x4(&m_view, XMMatrixLookAtLH(XMLoadFloat4(&pos), XMLoadFloat4(&target), XMLoadFloat4(&up)));
	XMStoreFloat4x4(&m_proj, XMMatrixPerspectiveFovLH(fov, D3D11Renderer::Instance()->GetAspectRatio(), 0.01f, 100.0f));
}


CameraComponent::~CameraComponent()
{
}
