#ifndef __COMMON__
#define __COMMON__

Texture2D		gDiffuseMap		:	register(t0);
Texture2D		gNormalMap		:	register(t1);
Texture2D		gBumpMap		:	register(t2);
Texture2D		gShadowMap		:	register(t3);
TextureCube		gCubeMap		:	register(t4);
Texture2D		gHeightMap		:	register(t5);
Texture2DArray	gLayerMapArray	:	register(t6);
Texture2D		gBlendMap		:	register(t7);

SamplerState samLinear : register( s0 );

struct Light
{
	float4 Color;		//only xyz
	float4 Position;	//only xyz
	float4 Direction;	//only xyz
	float4 X_SpotAngleAndY_AttenuationAndZ_LightType;
};

cbuffer cbPerCamera : register(cb0) {
	matrix gView;
	matrix gProjection; 
	matrix gViewProj;
	float4 EyePosition;
}

cbuffer cbPerObject : register(cb1) {
	matrix gWorldViewProj;
	matrix gWorldViewInvTranspose;
	matrix gWorldInvTranspose;
	matrix gWorldView;
	matrix gWorld;
	Light	 Lights[8];
};

struct SCREEN_VS_IN
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

<<<<<<< HEAD
=======

struct SCREEN_VS_IN
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

>>>>>>> 4c046093f0e972224c47fe76e93febecd3fdfb0f
struct SCREEN_PS_IN
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};


#endif
