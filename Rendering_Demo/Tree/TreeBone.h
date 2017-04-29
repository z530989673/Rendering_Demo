#pragma once

#include "Includes.h"

class TreeBone
{
public:
	TreeBone();
	~TreeBone();

	void SetPos(Vector3 pos) { m_vLocalPos = pos; }

private:
	TreeBone* m_pParent = NULL;
	TreeBone* m_pChild = NULL;

	Vector3 m_vLocalPos = Vector3(0,0,0);
};

