#pragma once

#include <vector>
#include <assert.h>
#include <algorithm>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Light
{
	enum LIGHTTYPE
	{
		None = 0,
		Point = 1,
		Spot = 2,
		Directional = 3
	};
	XMVECTOR Color;
	XMVECTOR Position;
	XMVECTOR Direction;
	XMVECTOR X_SpotAngleAndY_AttenuationAndZ_LightType;
};


struct PERCAMERA_CONSTANT_BUFFER
{
	XMMATRIX View;
	XMMATRIX Projection;
	XMMATRIX ViewProj;
	XMVECTOR EyePosition;
};

struct PEROBJ_CONSTANT_BUFFER
{
	XMMATRIX World;
	XMMATRIX WorldViewProj;
	XMMATRIX WorldViewInvTranspose;
	XMMATRIX WorldInvTranspose;
	XMMATRIX WorldView;
	Light	 Lights[8];
};


#ifdef DEBUG
#include "Debugging/Debug.h"
#endif // DEBUG


#define SafeDelete(x)	\
{						\
	if (x)				\
		delete (x);		\
	x = 0;				\
}

#define SafeDeleteArray(x)	\
{							\
	if (x)					\
		delete[] (x);		\
	x = 0;					\
}

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x) assert(SUCCEEDED(x))
#endif
#endif
