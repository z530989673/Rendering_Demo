#pragma once
#include "Components/LightComponent.h"
#include "Components/RenderingComponent.h"
#include "Objects/GameObject.h"
#include "D3D11Renderer.h"
#include "Includes.h"

class LightComponent;
class RenderingComponent;

class LightManager
{
public:
	static LightManager* Instance() {
		if (m_instance == nullptr)
			m_instance = new LightManager();
		return m_instance;
	}

	GameObject* CreateLight(XMFLOAT4 pos, Light::LIGHTTYPE type, XMFLOAT4 dir, bool isCastingShadow = true, XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, float range = 100.0f, float spotAngle = XM_PIDIV2, float attenuation = 0);
	void BindLights(RenderingComponent*);
	void SetAmbientLightColor(float r, float g, float b){ m_ambientLightColor = XMVectorSet(r, g, b, 1.0f);  }
	XMVECTOR& GetAmbientLightColor(){ return m_ambientLightColor; }

	~LightManager();

private:
	static LightManager* m_instance;
	vector<LightComponent*> m_lights;
	XMVECTOR m_ambientLightColor;

	LightManager();
};

