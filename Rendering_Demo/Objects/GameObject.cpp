#include "GameObject.h"

GameObject* GameObject::ROOTNODE = new GameObject();


void GameObject::RemoveChild(GameObject* go)
{
	if (go->parent == this)
	{
		children.erase(std::remove(children.begin(), children.end(), go), children.end());
		go->parent = nullptr;
	}
}

void GameObject::AddChild(GameObject* go)
{
	go->parent = this;
	if (std::find(children.begin(), children.end(), go) == children.end())
	{
		children.push_back(go);
	}
}

void GameObject::AddComponent(Component* m)
{
	m_components.push_back(m);

	m->gameObject = this;
}

void GameObject::Update()
{
	for (auto component : m_components)
		component->Update();

	for (auto child : children)
		child->Update();
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
