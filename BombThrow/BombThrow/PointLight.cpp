#include "PointLight.h"
#include "PointLightShader.h"

PointLight::PointLight(GameObject* gO) : Light(gO)
{
	m_lightShader = new PointLightShader(this);
}


PointLight::~PointLight()
{
}