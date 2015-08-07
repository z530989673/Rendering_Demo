#include "GameObject.h"

GameObject* GameObject::ROOTNODE = new GameObject();

void GameObject::addComponent(Component* m)
{
	m_components.push_back(m);

	m->gameObject = this;
}

void GameObject::update()
{
	for (auto component : m_components)
		component->update();

	for (auto child : children)
		child->update();
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
