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
	Matrix4x4	m_proj;
	Matrix4x4	m_view;
	Vector3	m_eyePos;
	CameraComponent();
	CameraComponent(Vector3 pos, Vector3 target, Vector3 up, float fov, float np, float fp);
	CameraComponent(Matrix4x4& view, float fov, float np, float fp);
	RenderTexture* GetRenderTarget(){ return m_renderTarget; }
	void setRenderTarget(RenderTexture* value){ m_renderTarget = value; }
	void Bind();

	virtual void Update() override;

private:
	RenderTexture* m_renderTarget;

	~CameraComponent();
};

