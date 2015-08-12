#include "GameObject.h"

GameObject* GameObject::ROOTNODE = new GameObject();

XMFLOAT4 GameObject::GetPos()
{
	return XMFLOAT4(&m_worldTransform.m[3][0]);
}

XMFLOAT4 GameObject::GetUP()
{
	return XMFLOAT4(&m_worldTransform.m[1][0]);
}

XMFLOAT4 GameObject::GetForward()
{
	return XMFLOAT4(&m_worldTransform.m[2][0]);
}

XMFLOAT4 GameObject::GetRight()
{
	return XMFLOAT4(&m_worldTransform.m[0][0]);
}

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
	XMStoreFloat4x4(&m_worldTransform, XMMatrixIdentity());
}


GameObject::~GameObject()
{
}
