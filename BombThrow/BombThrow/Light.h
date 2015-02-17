#include "ComponentBase.h"
#include "Shader.h"

#pragma once
class Light : public ComponentBase
{
public:
	virtual ~Light();

	void ApplyLight(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
		D3DXMATRIX projectionMatrix, Texture** textures);

protected:
	Light(void);
	Light(Light const&);
	void operator=(Light const&);
	Light(GameObject* gO);
	Shader* m_lightShader;
};

