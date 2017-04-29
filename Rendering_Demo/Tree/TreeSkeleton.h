#pragma once

#include "includes.h"

class TreeBone;

class TreeSkeleton
{
public:
	TreeSkeleton();
	~TreeSkeleton();

private:
	TreeBone* m_pRootBone;
	int m_iSize;
};

