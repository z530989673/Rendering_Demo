#pragma once
#include "Objects/GameObject.h"
#include "Includes.h"

class GameObject;

class Component
{
public:
	GameObject* gameObject;

	virtual void Update(){};

	void setEnabled(bool e){ m_enabled = e; }
	bool isEnabled();

	Component();
	~Component();

private:
		bool m_enabled = true;

};

