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

	LightComponent(XMFLOAT4 pos, Light::LIGHTTYPE type, XMFLOAT4 dir, bool isCastingShadow, XMFLOAT4 color, float range, float spotAngle, float attenuation);
	LightComponent();
	~LightComponent();

private:
	Light m_light;
	float m_range;
	bool m_isCastingShadow;
};

