#pragma once
#include <d3d11.h>
#include <Modules/RenderingModule.h>
#include "Includes.h"
#include "D3D11Renderer.h"

#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

class Effect
{
protected:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11GeometryShader* m_geometryShader;
	ID3D11HullShader* m_hullShader;
	ID3D11DomainShader* m_domainShader;
	ID3D11ComputeShader* m_computeShader;

	ID3DBlob *m_vsBlob;
	ID3DBlob *m_psBlob;
	ID3DBlob *m_gsBlob;
	ID3DBlob *m_hsBlob;
	ID3DBlob *m_dsBlob;
	ID3DBlob *m_csBlob;

	ID3D11InputLayout* m_inputLayout;
	std::vector<D3D11_INPUT_ELEMENT_DESC> m_vertexDesc;
	ID3D11ShaderResourceView** m_shaderResources;
	ID3D11ShaderResourceView** m_outputShaderResources;
	ID3D11UnorderedAccessView** m_unorderedAccessViews;

	void ReadShaderFile(std::wstring filename, ID3DBlob **blob, char* target, char* entryPoint = "main");
public:
	std::vector<RenderingModule*> m_renderingModule;

	Effect();
	Effect(const std::wstring& vsPath,
		const std::wstring& psPath,
		const std::wstring& gsPath,
		const std::wstring& hsPath,
		const std::wstring& dsPath,
		const std::wstring& csPath);
	virtual ~Effect();


};

