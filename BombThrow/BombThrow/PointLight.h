#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(GameObject* gO);
	virtual ~PointLight();

	D3DXVECTOR4 GetDiffuse() { return m_diffuseColor; }
	void SetDiffuse(D3DXVECTOR4 diff) { m_diffuseColor = diff; }
	float GetSpecularPower() { return m_specularPower; }
	void SetSpecularPower(float specPow) { m_specularPower = specPow; }
	D3DXVECTOR4 GetSpecularColor() { return m_specularColor; }
	void SetSpecularColor(D3DXVECTOR4 spec) { m_specularColor = spec; }

private:
	PointLight();

	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;
};

