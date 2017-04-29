#pragma once
#include "TreeNode.h"
class Trunk :
	public TreeNode
{
public:
	Trunk();
	~Trunk();

	virtual NODE_TYPE GetNodeType() { return NODE_TRUNK; }
};

