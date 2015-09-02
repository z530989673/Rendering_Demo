#include "GameObject.h"

GameObject* GameObject::ROOTNODE = new GameObject();

void GameObject::setPos(float x, float y, float z)
{
	m_worldTransform.m[3][0] = x;
	m_worldTransform.m[3][1] = y;
	m_worldTransform.m[3][2] = z;
}

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

void GameObject::MoveForward(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform.m[3][i] += dis * m_worldTransform.m[2][i];
}

void GameObject::MoveBackward(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform.m[3][i] -= dis * m_worldTransform.m[2][i];
}

void GameObject::MoveRight(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform.m[3][i] += dis * m_worldTransform.m[0][i];
}

void GameObject::MoveLeft(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform.m[3][i] -= dis * m_worldTransform.m[0][i];
}

void GameObject::MoveUp(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform.m[3][i] += dis * m_worldTransform.m[1][i];
}
void GameObject::MoveDown(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform.m[3][i] -= dis * m_worldTransform.m[1][i];
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

void GameObject::SetParent(GameObject* go)
{
	if (parent != nullptr)
		this->parent->RemoveChild(this);

	go->AddChild(this);

	this->parent = go;
}

void GameObject::AddComponent(Component* m)
{
	m_components.push_back(m);

	m->gameObject = this;
}

void GameObject::Update()
{
	for (Component* component : m_components)
		component->Update();

	for (GameObject* child : children)
		child->Update();
}

GameObject::GameObject()
{
	XMStoreFloat4x4(&m_worldTransform, XMMatrixIdentity());
}


GameObject::~GameObject()
{
}
