#include "LightManager.h"

LightManager* LightManager::m_instance = nullptr;

GameObject* LightManager::CreateLight(Vector4 pos, Light::LIGHTTYPE type, Vector4 dir, bool isCastingShadow, Vector4 color, float range, float spotAngle, float attenuation)
{
	GameObject* light = new GameObject();
	LightComponent* lc = new LightComponent(pos, type, dir, isCastingShadow, color, range, spotAngle, attenuation);

	light->AddComponent(lc);
	light->SetParent(GameObject::ROOTNODE);

	m_lights.push_back(lc);

	return light;
}

void LightManager::BindLights(RenderingComponent* rc)
{
	vector<LightComponent*> current;
	for (LightComponent* lc : m_lights)
	{
		if (lc->CheckIfWithinRange(rc))
		{
			current.push_back(lc);
		}
	}

	D3D11Renderer::Instance()->UpdateLights(current);
}

LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}
