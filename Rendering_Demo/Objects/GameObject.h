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

	XMFLOAT4 GetPos();
	XMFLOAT4 GetUP();
	XMFLOAT4 GetForward();
	XMFLOAT4 GetRight();
	XMFLOAT4X4 GetWorldTransform(){ return m_worldTransform; }

	void SetPos(float x, float y, float z);
	void SetWorldMatrix(XMMATRIX& mat);

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
	GameObject(XMMATRIX& mat);
	~GameObject();

	void setEnabled(bool e){ m_enabled = e; }
	bool isEnabled(){ return m_enabled; }

private:
	bool m_enabled = true;
	std::vector<Component*> m_components;
	XMFLOAT4X4 m_worldTransform;
};

