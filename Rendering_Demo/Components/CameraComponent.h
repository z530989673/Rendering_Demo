#pragma once
#include "Components\Component.h"
#include "D3D11Renderer.h"
#include "Includes.h"
#include "Basic/RenderTexture.h"

class RenderTexture;

class CameraComponent :
	public Component
{
public:
	XMFLOAT4X4	m_proj;
	XMFLOAT4X4	m_view;
	XMVECTOR	m_eyePos;
	CameraComponent();
	CameraComponent(XMFLOAT4 pos, XMFLOAT4 target, XMFLOAT4 up,float fov,float np,float fp);
	RenderTexture* GetRenderTarget(){ return m_renderTarget; }
	void setRenderTarget(RenderTexture* value){ m_renderTarget = value; }
	void Bind();

private:
	RenderTexture* m_renderTarget;

	~CameraComponent();
};

