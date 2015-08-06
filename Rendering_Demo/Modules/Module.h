#pragma once
#include "Objects/GameObject.h"

class GameObject;

class Module
{
public:
	GameObject* gameObject;

	virtual void update() = 0;

	Module();
	~Module();
};

