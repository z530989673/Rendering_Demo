#include "CameraManager.h"

CameraManager* CameraManager::m_instance = nullptr;

GameObject* CameraManager::CreateCamera(XMFLOAT4 pos, XMFLOAT4 target, XMFLOAT4 up, float fov, float np, float fp)
{
	GameObject* camera = new GameObject();
	CameraComponent* cc = new CameraComponent(pos, target, up, fov, np, fp);
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
