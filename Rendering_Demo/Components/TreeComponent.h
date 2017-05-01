#pragma once
#include "Components\RenderingComponent.h"
#include "Tree\Tree.h"

class TreeComponent :
	public RenderingComponent
{
public:
	TreeComponent();
	~TreeComponent();

private:
	Tree* m_pTree;
};

