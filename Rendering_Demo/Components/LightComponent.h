#pragma once
#include "Components\Component.h"
#include "Includes.h"

class LightComponent :
	public Component
{
public:
	bool isStatic = false;

	LightComponent();
	~LightComponent();

private:

};

