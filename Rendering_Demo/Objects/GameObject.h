#pragma once
#include "Includes.h"
#include "Components/Component.h"
#include <DirectXMath.h>
using namespace DirectX;

class Component;

class GameObject
{
public:
	XMFLOAT4X4 worldMX;

	static GameObject* ROOTNODE;
	GameObject* parent;
	std::vector<GameObject*> children;

	void AddComponent(Component*);
	//void RemoveComponent(Component*);
	void AddChild(GameObject*);
	void RemoveChild(GameObject*);

	void Update();

	GameObject();
	~GameObject();

private:
	std::vector<Component*> m_components;
};

