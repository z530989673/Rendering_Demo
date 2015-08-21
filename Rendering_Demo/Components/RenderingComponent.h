#pragma once
#include "Component.h"
#include "Includes.h"
#include <D3D11Renderer.h>
#include "Engine/Effect.h"
#include "Engine/EffectManager.h"

using namespace DirectX;

class Effect;

class RenderingComponent :
	public Component
{
protected:

	virtual void PrepareGPUBuffer();
public:
<<<<<<< HEAD
	bool isStatic = false;
	UINT stride,offset = 0; // for vertexbuffer
=======
>>>>>>> 4c046093f0e972224c47fe76e93febecd3fdfb0f
	ID3D11Buffer* m_indexBufferGPU;
	ID3D11Buffer* m_VertexBufferGPU;

	std::vector<UINT> m_indexBufferCPU;
	std::vector<XMFLOAT3> m_positionBufferCPU;
	//std::vector<XMFLOAT3> m_normalBufferCPU;
	//std::vector<XMFLOAT2> m_texUVBufferCPU;
	//std::vector<XMFLOAT4> m_colorBufferCPU;
	//std::vector<XMFLOAT3> m_tangentBufferCPU;

	Effect* m_relatedEffect;

	virtual void Draw();
	void Prepare();

	RenderingComponent();
	~RenderingComponent();
};

