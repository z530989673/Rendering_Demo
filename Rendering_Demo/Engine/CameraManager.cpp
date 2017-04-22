#include "CameraManager.h"

CameraManager* CameraManager::m_instance = nullptr;

GameObject* CameraManager::CreateCamera(Vector3 pos, Vector3 target, Vector3 up, float fov, float np, float fp)
{
	Matrix4x4 view = Matrix4x4::LookAt(target, pos, up);
	Matrix4x4 viewInv = view.Inverse();

	GameObject* camera = new GameObject(viewInv);
	CameraComponent* cc = new CameraComponent(view, fov, np, fp);
	camera->AddComponent(cc);
	camera->SetParent(GameObject::ROOTNODE);

	return camera;
}

void CameraManager::SetMainCamera(CameraComponent* cc)
{
	m_mainCamera = cc;
}

CameraComponent* CameraManager::GetMainCamera()
{
	if (m_mainCamera != nullptr)
		return m_mainCamera;
	else
		return m_defalutCamera;
}

CameraManager::CameraManager()
{
	m_defalutCamera = new CameraComponent();
	m_cameras.push_back(m_defalutCamera);
}


CameraManager::~CameraManager()
{
}
