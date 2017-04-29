#pragma once
#include "TreeNode.h"
class RootNode :
	public TreeNode
{
public:
	RootNode();
	~RootNode();

	virtual NODE_TYPE GetNodeType() { return NODE_ROOT; }
};

