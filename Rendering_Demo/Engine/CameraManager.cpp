#include "CameraManager.h"

CameraManager* CameraManager::m_instance = nullptr;


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
