#include "Shader.h"


#pragma once
class DeferredShader : public Shader
{
public:
	DeferredShader(void);
	~DeferredShader(void);

	virtual void LoadShaderParameters(ID3D11Device* device, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer);
	virtual void SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
					     D3DXMATRIX projectionMatrix, Texture** textures);

	virtual char* GetVertexFunctionName() { return "DeferredVertexShader"; }
	virtual char* GetPixelFunctionName() { return "DeferredPixelShader"; }
};

