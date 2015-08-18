#pragma once

#include <Components/RenderingComponent.h>
#include "Engine/Layout.h"
#include <Components/CameraComponent.h>
#include "Includes.h"
#include "D3D11Renderer.h"

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

class Layout;
class RenderingComponent;
class CameraComponent;

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

	Layout* m_inputLayout;
	std::vector<RenderingComponent*> m_renderingComponents;

	ID3D11Buffer* m_perObjectCB;
	PERCAMERA_CONSTANT_BUFFER m_perObjConstantBuffer;

	virtual void BindShaderResource() {}
	virtual void UnBindShaderResource();
	virtual void Start();   // create input Layout
	void ReadShaderFile(std::wstring filename, ID3DBlob **blob, char* target, char* entryPoint = "main");

public:
	void PrepareVertexBuffer(RenderingComponent*,UINT&);
	void AddRenderingComponent(RenderingComponent*);
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
