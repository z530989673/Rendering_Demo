#pragma once
#include "Component.h"
#include "Includes.h"
#include <D3D11Renderer.h>
#include "Engine/Effect.h"
#include "Engine/EffectManager.h"
#include "Engine/LightManager.h"

class Effect;

class RenderingComponent :
	public Component
{
protected:
	Effect* m_relatedEffect = nullptr;

	virtual void PrepareGPUBuffer();
public:
	bool isStatic = false;
	UINT stride,offset = 0; // for vertexbuffer
	ID3D11Buffer* m_indexBufferGPU;
	ID3D11Buffer* m_VertexBufferGPU;

	std::vector<UINT> m_indexBufferCPU;
	std::vector<Vector3> m_positionBufferCPU;
	std::vector<Vector3> m_normalBufferCPU;
	std::vector<Vector2> m_texCoordBufferCPU;
	//std::vector<Vector4> m_colorBufferCPU;
	//std::vector<Vector3> m_tangentBufferCPU;

	virtual void Draw();
	void Prepare();
	void SetEffect(Effect*);
	static RenderingComponent* CreateStandardBox();

	RenderingComponent();
	~RenderingComponent();
};

