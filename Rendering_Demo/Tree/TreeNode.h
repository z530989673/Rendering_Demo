#pragma once

#include "includes.h"
#include "TreeSkeleton.h"

enum NODE_TYPE
{
	NODE_BASE = 0,
	NODE_ROOT,
	NODE_TRUNK,
	NODE_BRANCH,
	NODE_LEAF,
};

class TreeNode
{
public:
	TreeNode();
	~TreeNode();

	virtual NODE_TYPE GetNodeType() { return NODE_BASE;}

	void AddChild(TreeNode* child);
	void RemoveChild(TreeNode* child);
	TreeNode* GetParent() { return m_pParent; };
	void SetParent(TreeNode* parent) { m_pParent = parent; };

private:
	TreeSkeleton* m_Skeleton = NULL;
	TreeNode* m_pParent = NULL;
	vector<TreeNode*> m_pChildren;
};

