#include "CameraComponent.h"


void CameraComponent::Update()
{
	XMMATRIX worldMat = XMLoadFloat4x4(&gameObject->GetWorldTransform());
	m_eyePos.x = gameObject->GetWorldTransform()._41;
	m_eyePos.y = gameObject->GetWorldTransform()._42;
	m_eyePos.z = gameObject->GetWorldTransform()._43;
	XMStoreFloat4x4(&m_view, XMMatrixInverse(NULL, worldMat));
}

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
	XMStoreFloat4x4(&m_proj, XMMatrixPerspectiveFovLH(fov, D3D11Renderer::Instance()->GetAspectRatio(), np, fp));
}

CameraComponent::CameraComponent(XMMATRIX& view, float fov, float np, float fp)
{
	XMStoreFloat4x4(&m_view, view);
	float x = 0, y = 0, z = 0;
	for (int i = 0; i < 3; i++)
	{
		x -= m_view.m[3][i] * m_view.m[0][i];
		y -= m_view.m[3][i] * m_view.m[1][i];
		z -= m_view.m[3][i] * m_view.m[2][i];
	}
	m_eyePos.x = x;
	m_eyePos.y = y;
	m_eyePos.z = z;
	XMStoreFloat4x4(&m_proj, XMMatrixPerspectiveFovLH(fov, D3D11Renderer::Instance()->GetAspectRatio(), np, fp));
}

CameraComponent::~CameraComponent()
{
}
