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

	void AddComponent(Component*);

	template<typename T>
	inline T* GetComponent()
	{
		for (Component* c : m_components)
		{
			if (typeid(T) == typeid(*c))
				return (T*)c;
		}

		return nullptr;
	}

	//void RemoveComponent(Component*);
	void AddChild(GameObject*);
	void RemoveChild(GameObject*);
	void SetParent(GameObject*);

	Vector4 GetPos();
	Vector4 GetUP();
	Vector4 GetForward();
	Vector4 GetRight();
	Matrix4x4 GetWorldTransform(){ return m_worldTransform; }

	void SetPos(float x, float y, float z);
	void SetWorldMatrix(Matrix4x4& mat);

	void MoveForward(float dis);
	void MoveBackward(float dis);
	void MoveRight(float dis);
	void MoveLeft(float dis);
	void MoveUp(float dis);
	void MoveDown(float dis);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void Update();

	GameObject();
	GameObject(float posX, float posY, float posZ);
	GameObject(Matrix4x4& mat);
	~GameObject();

	void setEnabled(bool e){ m_enabled = e; }
	bool isEnabled(){ return m_enabled; }

private:
	bool m_enabled = true;
	std::vector<Component*> m_components;
	Matrix4x4 m_worldTransform;
};

