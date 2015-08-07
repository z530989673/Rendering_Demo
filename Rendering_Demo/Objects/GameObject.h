#pragma once
#include "Includes.h"
#include "Components/Component.h"

class Component;

class GameObject
{
public:
	static GameObject* ROOTNODE;
	GameObject* parent;
	std::vector<GameObject*> children;

	void addComponent(Component*);
	//void removeComponent(Component*);
	//void addChild(GameObject*);
	//void removeChild(GameObject*);

	void update();

	GameObject();
	~GameObject();

private:
	std::vector<Component*> m_components;
};

