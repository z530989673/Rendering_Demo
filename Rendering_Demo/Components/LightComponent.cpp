#include "LightComponent.h"


bool LightComponent::CheckIfWithinRange(RenderingComponent* rc)
{
	//temp
	return true;
}

LightComponent::LightComponent(Vector4 pos, Light::LIGHTTYPE type, Vector4 dir, bool isCastingShadow, Vector4 color, float range, float spotAngle, float attenuation) :
m_range(range),
m_isCastingShadow(isCastingShadow)
{
	m_light.Position = pos;
	m_light.Color = color;
	m_light.Direction = dir;
	Vector4 misc = Vector4(spotAngle, attenuation, (float)type, 0.0f);
	m_light.X_SpotAngleAndY_AttenuationAndZ_LightType = misc;

}

LightComponent::LightComponent()
{
}


LightComponent::~LightComponent()
{
}
