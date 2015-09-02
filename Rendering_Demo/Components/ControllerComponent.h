#pragma once
#include "Component.h"
#include "Engine/InputManager.h"
#include "Basic/Timer.h"

#include "Debugging/Debug.h"

class ControllerComponent :
	public Component
{
public:
	float m_speed = 1.0f;
	void Update();
	ControllerComponent();
	~ControllerComponent();
};

