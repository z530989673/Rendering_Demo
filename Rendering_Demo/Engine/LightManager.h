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

	GameObject* CreateLight(Vector4 pos, Light::LIGHTTYPE type, Vector4 dir, bool isCastingShadow = true, Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, float range = 100.0f, float spotAngle = XM_PIDIV2, float attenuation = 2);
	void BindLights(RenderingComponent*);
	void SetAmbientLightColor(float r, float g, float b){ m_ambientLightColor = Vector4(r, g, b, 1.0f); }
	Vector4 GetAmbientLightColor(){ return m_ambientLightColor; }

	~LightManager();

private:
	static LightManager* m_instance;
	vector<LightComponent*> m_lights;
	Vector4 m_ambientLightColor;

	LightManager();
};

