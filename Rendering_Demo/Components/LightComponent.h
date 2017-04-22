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

	LightComponent(Vector4 pos, Light::LIGHTTYPE type, Vector4 dir, bool isCastingShadow, Vector4 color, float range, float spotAngle, float attenuation);
	LightComponent();
	~LightComponent();

private:
	Light m_light;
	float m_range;
	bool m_isCastingShadow;
};

