#pragma once
#include "Component.h"
#include "Engine/InputManager.h"
#include "Basic/Timer.h"

#include "Debugging/Debug.h"

class ControllerComponent :
	public Component
{
public:
	float m_moveSpeed = 1.0f;
	float rotateSpeed = 0.4f;
	void Update();
	ControllerComponent();
	~ControllerComponent();
};

