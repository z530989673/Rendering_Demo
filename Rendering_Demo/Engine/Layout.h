#pragma once
#include "Components/RenderingComponent.h"
#include "Includes.h"
#include "D3D11Renderer.h"

class RenderingComponent;

class Layout
{
public:
	ID3D11InputLayout* m_inputLayout;
	Layout();

	void SetLayout();
	virtual void CreateLayout(ID3DBlob*) = 0;
	virtual void PrepareVertexBuffer(RenderingComponent*, UINT&) = 0;
	virtual ~Layout();
};


class BasicLayout : 
	public Layout
{
public:
	BasicLayout();
	~BasicLayout();
	void CreateLayout(ID3DBlob*);
	void PrepareVertexBuffer(RenderingComponent*, UINT&);
};

class StandardLayout :
	public Layout
{
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 texCoord;
		XMFLOAT3 normal;
	};
public:
	StandardLayout();
	~StandardLayout();
	void CreateLayout(ID3DBlob*);
	void PrepareVertexBuffer(RenderingComponent*, UINT&);
};
