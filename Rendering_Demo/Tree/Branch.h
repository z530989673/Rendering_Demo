#pragma once
#include "TreeNode.h"
class Branch :
	public TreeNode
{
public:
	Branch();
	~Branch();

	virtual NODE_TYPE GetNodeType() { return NODE_BRANCH; }
};

