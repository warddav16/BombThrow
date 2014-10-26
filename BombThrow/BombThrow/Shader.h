#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

#include "Texture.h"

class MeshRenderer;

class Shader
{
public:
	
	virtual ~Shader(void);

	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	virtual void LoadShaderParameters(ID3D11Device* device, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer) = 0;
	virtual void SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
					     D3DXMATRIX projectionMatrix, Texture** texture) = 0;
	virtual char* GetVertexFunctionName() = 0;
	virtual char* GetPixelFunctionName() = 0;

	ID3D11VertexShader* GetVertexShader() { return m_vertexShader; }
	void SetVertexShader(ID3D11VertexShader* vertexShader) { m_vertexShader = vertexShader; }
	ID3D11PixelShader* GetPixelShader() { return m_pixelShader; }
	void SetPixelShader(ID3D11PixelShader* pixelShader) { m_pixelShader = pixelShader; }
	ID3D11SamplerState* GetSampleState() { return m_sampleState; }
	void SetSampleState(ID3D11SamplerState* sampler) { m_sampleState = sampler; }
	ID3D11InputLayout* GetInputLayout() { return m_layout; }
	void SetMatrixBuffer(ID3D11Buffer* matrixBuffer) { m_matrixBuffer = matrixBuffer; }

protected:
	Shader(void);
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
};

