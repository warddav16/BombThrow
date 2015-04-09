#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(GameObject* gO);
	virtual ~PointLight();

	float GetSpecularPower() { return m_specularPower; }
	void SetSpecularPower(float specPow) { m_specularPower = specPow; }
	D3DXVECTOR4 GetSpecularColor() { return m_specularColor; }
	void SetSpecularColor(D3DXVECTOR4 spec) { m_specularColor = spec; }
	float GetRadius() { return m_radius; }
	void SetRadius(float r) { m_radius = r; }

private:
	PointLight();
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;
	float m_radius;
};

