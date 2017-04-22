#pragma once

#include <vector>
#include <assert.h>
#include <algorithm>
#include <d3d11.h>
#include <DirectXMath.h>

#include "mathfu/vector.h"
#include "mathfu/matrix.h"

using namespace DirectX;
using namespace std;
using namespace mathfu;

#define MAX_LIGHT_NUM 8

#define Vector3 Vector<float, 3>
#define Vector4 Vector<float, 4>
#define Matrix4x4 Matrix<float, 4, 4>

struct Light
{
	enum LIGHTTYPE
	{
		None = 0,
		Directional,
		Point,
		Spot,
	};
	Vector4 Color;
	Vector4 Position;
	Vector4 Direction;
	Vector4 X_SpotAngleAndY_AttenuationAndZ_LightType;
};


struct PERCAMERA_CONSTANT_BUFFER
{
	Matrix4x4 View;
	Matrix4x4 Projection;
	Matrix4x4 ViewProj;
	Vector4 EyePosition;
	Vector4 AmbientLightColor;
};

struct PEROBJ_CONSTANT_BUFFER
{
	Matrix4x4 World;
	Matrix4x4 WorldViewProj;
	Matrix4x4 WorldViewInvTranspose;
	Matrix4x4 WorldInvTranspose;
	Matrix4x4 WorldView;
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
