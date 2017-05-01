#pragma once

#include "Includes.h"

#include "RootNode.h"

class Tree
{
public:
	Tree();
	~Tree();

private:
	RootNode* m_pRoot;
};
