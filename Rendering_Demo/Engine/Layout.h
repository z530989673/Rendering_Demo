#pragma once
#include "Components/RenderingComponent.h"
<<<<<<< HEAD
=======
#include <d3d11.h>
>>>>>>> 4c046093f0e972224c47fe76e93febecd3fdfb0f
#include "Includes.h"
#include "D3D11Renderer.h"

class RenderingComponent;

class Layout
{
public:
	ID3D11InputLayout* m_inputLayout;
	Layout();

	void SetLayout();
<<<<<<< HEAD
	virtual void PrepareVertexBuffer(RenderingComponent*, UINT&) = 0;
=======
	virtual void PrepareVertexBuffer(RenderingComponent*) = 0;
>>>>>>> 4c046093f0e972224c47fe76e93febecd3fdfb0f
	virtual ~Layout();
};


class BasicLayout : 
	public Layout
{
public:
	BasicLayout(ID3DBlob *vsBlob);
	~BasicLayout();
<<<<<<< HEAD
	void PrepareVertexBuffer(RenderingComponent*, UINT&);
=======
	void PrepareVertexBuffer(RenderingComponent*);
>>>>>>> 4c046093f0e972224c47fe76e93febecd3fdfb0f
};
