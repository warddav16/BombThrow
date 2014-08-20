#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

class Shader
{
public:
	Shader(void);
	~Shader(void);

	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	void LoadShaders(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
					   D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);

	ID3D11VertexShader* GetVertexShader() { return m_vertexShader; }
	ID3D11PixelShader* GetPixelShader() { return m_pixelShader; }
	ID3D11SamplerState* GetSampleState() { return m_sampleState; }
	ID3D11InputLayout* GetInputLayout() { return m_layout; }

private:
	void Shader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
};

