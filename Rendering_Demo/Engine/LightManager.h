#pragma once
#include "Components/LightComponent.h"

class LightComponent;

class LightManager
{
public:
	static LightManager* Instance() {
		if (m_instance == nullptr)
			m_instance = new LightManager();
		return m_instance;
	}

	~LightManager();

private:
	static LightManager* m_instance;
	LightManager();
};

