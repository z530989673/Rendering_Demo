#include "TreeNode.h"



TreeNode::TreeNode()
{
}


TreeNode::~TreeNode()
{
}

void TreeNode::AddChild(TreeNode* child)
{
	m_pChildren.push_back(child);
	if (child->GetParent() != NULL)
		child->GetParent()->RemoveChild(child);
	
	child->SetParent(this);
}

void TreeNode::RemoveChild(TreeNode* child)
{
	if (child->m_pParent == this)
		m_pChildren.erase(remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
}
