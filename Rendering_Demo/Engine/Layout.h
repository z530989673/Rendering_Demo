#pragma once
#include "Components/RenderingComponent.h"
#include <d3d11.h>
#include "Includes.h"
#include "D3D11Renderer.h"

class RenderingComponent;

class Layout
{
public:
	ID3D11InputLayout* m_inputLayout;
	Layout();

	void SetLayout();
	virtual void PrepareVertexBuffer(RenderingComponent*) = 0;
	virtual ~Layout();
};


class BasicLayout : 
	public Layout
{
public:
	BasicLayout(ID3DBlob *vsBlob);
	~BasicLayout();
	void PrepareVertexBuffer(RenderingComponent*);
};
