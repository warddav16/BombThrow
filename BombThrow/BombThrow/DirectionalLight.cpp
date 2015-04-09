#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(GameObject* gO) : Light(gO)
{
	m_lightShader = NULL;
}



DirectionalLight::~DirectionalLight()
{
}
