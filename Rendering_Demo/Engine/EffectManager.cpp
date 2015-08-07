#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager()
{
	defaultEffect = new Effect(L"Shaders/Default_VS.hlsl", L"Shaders/Default_PS.hlsl");
	AddRenderingEffect(defaultEffect);
}

void EffectManager::SetDefaultEffect(RenderingComponent* rc)
{
	rc->relatedEffect = defaultEffect;
	defaultEffect->AddRenderingComponent(rc);
}

void EffectManager::AddRenderingEffect(Effect* value)
{
	if (std::find(m_renderingEffects.begin(), m_renderingEffects.end(), value) == m_renderingEffects.end())
	{
		m_renderingEffects.push_back(value);
	}
}

void EffectManager::RemoveRenderingEffect(Effect* value)
{
	m_renderingEffects.erase(std::remove(m_renderingEffects.begin(), m_renderingEffects.end(), value), m_renderingEffects.end());
}

EffectManager::~EffectManager()
{
	SafeDelete(defaultEffect);
}
