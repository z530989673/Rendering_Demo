#include "EffectManager.h"

//temp
#include "CameraManager.h"

EffectManager* EffectManager::m_instance = nullptr;

void EffectManager::DrawEffects()
{
	for (Effect* eff : m_renderingEffects)
	{
		eff->BindEffect();

		std::vector<RenderingComponent*>* renderingComponents = eff->GetRenderingComponents();
		for (RenderingComponent* rc : *renderingComponents)
			rc->Draw();

		eff->UnBindEffect();
	}
}

EffectManager::EffectManager()
{
	defaultEffect = new Effect(L"Shaders/Default_VS.hlsl", L"Shaders/Default_PS.hlsl");
	AddRenderingEffect(defaultEffect);
}

void EffectManager::SetEffect(RenderingComponent* rc, Effect* eff)
{
	rc->SetEffect(eff);
	eff->AddRenderingComponent(rc);
}

void EffectManager::UnSetEffect(RenderingComponent* rc)
{
	rc->SetEffect(defaultEffect);
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
