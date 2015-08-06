#pragma once
#include "Includes.h"
#include "Modules/Module.h"

class Module;

class GameObject
{
public:
	static GameObject ROOTNODE;
	GameObject* parent;
	std::vector<GameObject*> children;

	void addModule(Module*);
	//void removeModule(Module*);
	//void addChild(GameObject*);
	//void removeChild(GameObject*);

	void update();

	GameObject();
	~GameObject();

private:
		std::vector<Module*> m_modules;
};

