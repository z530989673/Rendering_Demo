#pragma once

#include <vector>
#include <assert.h>
#include <algorithm>
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

#define MAX_LIGHT_NUM 8

__declspec(align(16)) struct Light
{
	enum LIGHTTYPE
	{
		None = 0,
		Directional,
		Point,
		Spot,
	};
	XMVECTOR Color;
	XMVECTOR Position;
	XMVECTOR Direction;
	XMVECTOR X_SpotAngleAndY_AttenuationAndZ_LightType;
};


__declspec(align(16)) struct PERCAMERA_CONSTANT_BUFFER
{
	XMMATRIX View;
	XMMATRIX Projection;
	XMMATRIX ViewProj;
	XMVECTOR EyePosition;
	XMVECTOR AmbientLightColor;
};

__declspec(align(16)) struct PEROBJ_CONSTANT_BUFFER
{
	XMMATRIX World;
	XMMATRIX WorldViewProj;
	XMMATRIX WorldViewInvTranspose;
	XMMATRIX WorldInvTranspose;
	XMMATRIX WorldView;
	Light	 Lights[MAX_LIGHT_NUM];
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
#else
#define HR(x) x
#endif
