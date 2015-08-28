#pragma once
#include "Components\Component.h"
#include "Components\RenderingComponent.h"
#include "Includes.h"

class RenderingComponent;

class LightComponent :
	public Component
{
public:
	bool isStatic = false;

	bool CheckIfWithinRange(RenderingComponent*);
	Light& GetLight(){ return m_light; };

	LightComponent(XMFLOAT4 pos, Light::LIGHTTYPE type, XMFLOAT4 dir, bool isCastingShadow = true, XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, float range = 100.0f, float spotAngle = XM_PIDIV2, float attenuation = 0);
	LightComponent();
	~LightComponent();

private:
	Light m_light;
	float m_range;
	bool m_isCastingShadow;
};

