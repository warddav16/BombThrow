#include "Shader.h"


#pragma once
class AmbientLightShader : public Shader
{
public:
	AmbientLightShader(void);
	~AmbientLightShader(void);

	virtual void LoadShaderParameters(ID3D11Device* device, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer);
	virtual void SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
		D3DXMATRIX projectionMatrix, D3DXMATRIX invProj, Texture** textures);

	virtual char* GetVertexFunctionName() { return "AmbientVertexShader"; }
	virtual char* GetPixelFunctionName() { return "AmbientPixelShader"; }
};

