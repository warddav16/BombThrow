#include "Shader.h"
#include "PointLight.h"

#pragma once
class PointLightShader : public Shader
{
public:
	struct LightBufferType
	{
		D3DXVECTOR4 lightPos;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR4 specularColor;
		D3DXVECTOR4 cameraPos;
		float specularPower;
		float radius;
		float padding[2];
	};

	PointLightShader(PointLight* pL);
	~PointLightShader();

	virtual void LoadShaderParameters(ID3D11Device* device, ID3D10Blob* vertexShaderBuffer, ID3D10Blob* pixelShaderBuffer);
	virtual void SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
		D3DXMATRIX projectionMatrix, Texture** textures);

	virtual char* GetVertexFunctionName() { return "PointLightVertexShader"; }
	virtual char* GetPixelFunctionName() { return "PointLightPixelShader"; }

private:
	PointLightShader();

	PointLight* m_pointLight;
	ID3D11Buffer* m_lightBuffer;
};

