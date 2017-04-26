#pragma once

#include "Includes.h"

class TreeBone
{
public:
	TreeBone();
	~TreeBone();

private:
	TreeBone* m_pParent = NULL;
	TreeBone* m_pChild = NULL;

	Vector3 m_vLocalPos = Vector3(0,0,0);
	Vector3 m_vLocalScale = Vector3(0, 0, 0);
	Quaternion m_qLocalRot = Quaternion(0,0,0,1);
};

