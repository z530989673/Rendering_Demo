#pragma once
#include "Effect.h"
#include "Components/RenderingComponent.h"
#include "Components/CameraComponent.h"
#include "Includes.h"

class Effect;
class RenderingComponent;
class CameraComponent;

class EffectManager
{
public:
	static EffectManager* Instance() {
		if (m_instance == nullptr)
			m_instance = new EffectManager();
		return m_instance;
	}

	Effect* defaultEffect;
	
	std::vector<Effect*>* GetRenderingEffects(){ return &m_renderingEffects; }

	void AddToDefaultEffect(RenderingComponent*);

	void AddRenderingEffect(Effect*);
	void RemoveRenderingEffect(Effect*);

	void DrawEffects(CameraComponent*);


	~EffectManager();

private:
	static EffectManager* m_instance;
	std::vector<Effect*> m_renderingEffects;
	EffectManager();
};

