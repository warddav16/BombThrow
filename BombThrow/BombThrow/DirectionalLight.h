#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(GameObject* gO);

	~DirectionalLight();
private:
	DirectionalLight();

	D3DXVECTOR4 m_diffuseColor;
};

