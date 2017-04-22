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

#define MAX_LIGHT_NUM 8

struct Light
{
	float4 Color;		//only xyz
	float4 Position;	//only xyz
	float4 Direction;	//only xyz
	float4 X_SpotAngleAndY_AttenuationAndZ_LightType;
};

cbuffer cbPerCamera : register(b0) {
	matrix gView;
	matrix gProjection; 
	matrix gViewProj;
	float4 EyePosition;
	float4 AmbientLightColor;
}

cbuffer cbPerObject : register(b1) {
	matrix gWorld;
	matrix gWorldViewProj;
	matrix gWorldViewInvTranspose;
	matrix gWorldInvTranspose;
	matrix gWorldView;
	Light	 Lights[MAX_LIGHT_NUM];
};

struct STANDARD_VS_IN
{
	float4 Pos		: POSITION;
	float2 TexCoord : TEXCOORD0;
	float4 Normal	: NORMAL0; 
};

struct STANDARD_PS_IN
{
	float4 Pos		: SV_POSITION;
	float4 WorldPos : POSITION;
	float3 Normal	: Normal0;
	float2 TexCoord	: TEXCOORD0;
};

struct SCREEN_VS_IN
{
    float4 Pos : POSITION;
    float2 TexCoord : TEXCOORD0;
};

struct SCREEN_PS_IN
{
    float4 Pos : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};


#endif
