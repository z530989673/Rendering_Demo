#pragma once
#include "Effect.h"
#include "Components/RenderingComponent.h"
#include "Includes.h"

class Effect;
class RenderingComponent;

class EffectManager
{
public:
	static EffectManager* Instance() {
		if (_instance == nullptr)
			_instance = new EffectManager();
		return _instance;
	}

	Effect* defaultEffect;
	
	std::vector<Effect*> GetRenderingEffects(){ return m_renderingEffects; }

	void SetDefaultEffect(RenderingComponent*);

	void AddRenderingEffect(Effect*);
	void RemoveRenderingEffect(Effect*);

	~EffectManager();

private:
	static EffectManager* _instance;
	std::vector<Effect*> m_renderingEffects;
	EffectManager();
};

