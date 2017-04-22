#include "CameraComponent.h"


void CameraComponent::Update()
{
	Matrix4x4 worldMat = gameObject->GetWorldTransform();
	m_eyePos.x = worldMat(0, 3);
	m_eyePos.y = worldMat(1, 3);
	m_eyePos.z = worldMat(2, 3);
	m_view = worldMat.Inverse();
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
	m_eyePos = Vector3(0.0f, 0.0f, -2.0f);
	Vector3 target = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	m_view = Matrix4x4::LookAt(target, m_eyePos, up);
	m_proj = Matrix4x4::Perspective(XM_PIDIV2, D3D11Renderer::Instance()->GetAspectRatio(), 0.01f, 100.0f, -1);
}

CameraComponent::CameraComponent(Vector3 pos, Vector3 target, Vector3 up, float fov, float np, float fp)
{
	m_eyePos = pos;
	m_view = Matrix4x4::LookAt(target, m_eyePos, up);
	m_proj = Matrix4x4::Perspective(fov, D3D11Renderer::Instance()->GetAspectRatio(), np, fp, -1);
}

CameraComponent::CameraComponent(Matrix4x4& view, float fov, float np, float fp)
{
	m_view = view;
	Matrix4x4 a = view.Inverse();
	float x = 0, y = 0, z = 0;
	for (int i = 0; i < 3; i++)
	{
		x -= m_view(i, 3) * m_view(i, 0);
		y -= m_view(i, 3) * m_view(i, 1);
		z -= m_view(i, 3) * m_view(i, 2);
	}
	m_eyePos.x = x;
	m_eyePos.y = y;
	m_eyePos.z = z;
	m_proj = Matrix4x4::Perspective(fov, D3D11Renderer::Instance()->GetAspectRatio(), np, fp, -1);
}

CameraComponent::~CameraComponent()
{
}
