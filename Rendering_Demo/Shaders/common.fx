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

cbuffer cbPerObject : register(b0) {
	matrix gWorldViewProj;
	matrix gWorldViewInvTranspose;
	matrix gWorldInvTranspose;
	matrix gWorldView;
	matrix gWorld;
	matrix gViewProj;
	matrix gShadowTransform;
	matrix gView;
	matrix gProjection;
};

#endif
