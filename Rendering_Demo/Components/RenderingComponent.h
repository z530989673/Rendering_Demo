#pragma once
#include "Component.h"
#include "Includes.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <D3D11Renderer.h>
#include "Engine/Effect.h"
#include "Engine/EffectManager.h"

using namespace DirectX;

class Effect;

class RenderingComponent :
	public Component
{
protected:
	ID3D11Buffer* m_indexBufferGPU;
	ID3D11Buffer* m_VertexBufferGPU;

	virtual void PrepareGPUBuffer();
public:
	std::vector<UINT> m_indexBufferCPU;
	std::vector<XMFLOAT3> m_positionBufferCPU;
	//std::vector<XMFLOAT3> m_normalBufferCPU;
	//std::vector<XMFLOAT2> m_texUVBufferCPU;
	//std::vector<XMFLOAT4> m_colorBufferCPU;
	//std::vector<XMFLOAT3> m_tangentBufferCPU;
	//ID3D11ShaderResourceView* m_diffuseMapSRV;
	//ID3D11ShaderResourceView* m_normalMapSRV;
	//ID3D11ShaderResourceView* m_bumpMapSRV;

	Effect* relatedEffect;

	virtual void Draw();
	void Prepare();

	RenderingComponent();
	~RenderingComponent();
};
