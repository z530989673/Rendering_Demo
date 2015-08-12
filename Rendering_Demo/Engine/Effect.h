#pragma once
#include <d3d11.h>
#include <Components/RenderingComponent.h>
#include <Components/CameraComponent.h>
#include "Includes.h"
#include "D3D11Renderer.h"
#include <DirectXMath.h>

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

class RenderingComponent;
class CameraComponent;

using namespace DirectX;

struct PEROBJ_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProj;
	XMMATRIX WorldViewInvTranspose;
	XMMATRIX WorldInvTranspose;
	XMMATRIX WorldView;
	XMMATRIX World;
	XMMATRIX ViewProj;
	XMMATRIX ShadowTransform;
	XMMATRIX View;
	XMMATRIX Projection;
};

class Effect
{
protected:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11HullShader* m_hullShader;
	ID3D11DomainShader* m_domainShader;
	ID3D11ComputeShader* m_computeShader;

	//should be loaded from resource manager!!!!!
	ID3DBlob *m_vsBlob;
	ID3DBlob *m_psBlob;
	ID3DBlob *m_gsBlob;
	ID3DBlob *m_hsBlob;
	ID3DBlob *m_dsBlob;
	ID3DBlob *m_csBlob;

	ID3D11InputLayout* m_inputLayout;
	std::vector<RenderingComponent*> m_renderingComponents;

	ID3D11Buffer* m_perObjectCB;
	PEROBJ_CONSTANT_BUFFER m_perObjConstantBuffer;

	virtual void BindConstantBuffer();
	virtual void BindShaderResource() {}
	virtual void UnBindConstantBuffer();
	virtual void UnBindShaderResource();
	virtual void Start();   // create input Layout
	void ReadShaderFile(std::wstring filename, ID3DBlob **blob, char* target, char* entryPoint = "main");

public:
	virtual void UpdateConstantBuffer(RenderingComponent*);
	void AddRenderingComponent(RenderingComponent*);
	void UpdateViewAndProjection(CameraComponent*);
	std::vector<RenderingComponent*>* GetRenderingComponents(){ return &m_renderingComponents; }

	Effect(const std::wstring& vsPath,
		const std::wstring& psPath,
		const std::wstring& gsPath = L"",
		const std::wstring& hsPath = L"",
		const std::wstring& dsPath = L"",
		const std::wstring& csPath = L"");
	virtual void BindEffect();
	virtual void UnBindEffect();

	virtual ~Effect();

private:
	Effect();
};

class DefaultEffect :
	public Effect
{
	DefaultEffect(const std::wstring& vsPath,
		const std::wstring& psPath,
		const std::wstring& gsPath = L"",
		const std::wstring& hsPath = L"",
		const std::wstring& dsPath = L"",
		const std::wstring& csPath = L"");
};
