#include "GameObject.h"

GameObject GameObject::ROOTNODE;

void GameObject::addModule(Module* m)
{
	m_modules.push_back(m);

	m->gameObject = this;
}

void GameObject::update()
{
	for (auto module : m_modules)
		module->update();

	for (auto child : children)
		child->update();
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}
