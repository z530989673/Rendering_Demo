#pragma once
#include "Objects/GameObject.h"

class GameObject;

class Component
{
public:
	GameObject* gameObject;

	virtual void update(){};

	Component();
	~Component();
};

