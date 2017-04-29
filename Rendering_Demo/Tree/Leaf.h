#pragma once
#include "TreeNode.h"
class Leaf :
	public TreeNode
{
public:
	Leaf();
	~Leaf();

	virtual NODE_TYPE GetNodeType() { return NODE_LEAF; }
};

