#pragma once
#include "Components/CameraComponent.h"
#include "Objects/GameObject.h"
#include "Includes.h"

class CameraComponent;

class CameraManager
{
public:
	static CameraManager* Instance() {
		if (m_instance == nullptr)
			m_instance = new CameraManager();
		return m_instance;
	}

	void SetMainCamera(CameraComponent*);
	GameObject* CreateCamera(XMFLOAT4 pos, XMFLOAT4 target, XMFLOAT4 up, float fov, float np, float fp);
	CameraComponent* GetMainCamera();
	std::vector<CameraComponent*>* getAllCameras(){ return &m_cameras; }

	~CameraManager();

private:
	static CameraManager* m_instance;
	CameraComponent* m_mainCamera;
	CameraComponent* m_defalutCamera;
	std::vector<CameraComponent*> m_cameras;
	CameraManager();
};

