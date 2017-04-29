#include "GameObject.h"

GameObject* GameObject::ROOTNODE = new GameObject();

void GameObject::SetPos(float x, float y, float z)
{
	m_worldTransform(3, 0) = x;
	m_worldTransform(3, 1) = y;
	m_worldTransform(3, 2) = z;
}

void GameObject::SetWorldMatrix(Matrix4x4& mat)
{
	m_worldTransform = mat;
}

Vector4 GameObject::GetPos()
{
	return m_worldTransform.GetColumn(3);
}

Vector4 GameObject::GetUP()
{
	return m_worldTransform.GetColumn(1);
}

Vector4 GameObject::GetForward()
{
	return m_worldTransform.GetColumn(2);
}

Vector4 GameObject::GetRight()
{
	return m_worldTransform.GetColumn(0);
}

void GameObject::RotateX(float angle)
{
	m_worldTransform *= Matrix4x4::FromRotationMatrix(Matrix4x4::RotationX(angle));
}

void GameObject::RotateY(float angle)
{
	Vector4 pos = m_worldTransform.GetColumn(3);
	m_worldTransform = Matrix4x4::FromRotationMatrix(Matrix4x4::RotationY(angle)) * m_worldTransform;
	m_worldTransform(0, 3) = pos(0);
	m_worldTransform(1, 3) = pos(1);
	m_worldTransform(2, 3) = pos(2);
}

void GameObject::RotateZ(float angle)
{
	m_worldTransform *= Matrix4x4::FromRotationMatrix(Matrix4x4::RotationZ(angle));
}

void GameObject::MoveForward(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform(i, 3) += dis * m_worldTransform(i, 2);
}

void GameObject::MoveBackward(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform(i, 3) -= dis * m_worldTransform(i, 2);
}

void GameObject::MoveRight(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform(i, 3) += dis * m_worldTransform(i, 0);
}

void GameObject::MoveLeft(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform(i, 3) -= dis * m_worldTransform(i, 0);
}

void GameObject::MoveUp(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform(i, 3) += dis * m_worldTransform(i, 1);
}
void GameObject::MoveDown(float dis)
{
	for (int i = 0; i < 3; i++)
		m_worldTransform(i, 3) -= dis * m_worldTransform(i, 1);
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
	m_worldTransform = Matrix4x4::Identity();
}

GameObject::GameObject(float posX, float posY, float posZ)
{
	m_worldTransform = Matrix4x4::Identity();
	SetPos(posX, posY, posZ);
}

GameObject::GameObject(Matrix4x4& mat)
{
	m_worldTransform = mat;
}

GameObject::~GameObject()
{
}
