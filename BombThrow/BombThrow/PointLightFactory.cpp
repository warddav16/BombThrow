#include "PointLightFactory.h"

#include "PointLight.h"
#include "Transform.h"
#include "FreeFormController.h"

PointLightFactory::PointLightFactory()
{
}


PointLightFactory::~PointLightFactory()
{
}

GameObject* PointLightFactory::Setup()
{
	GameObject* lightObject = new GameObject();
	lightObject->GetTransform()->SetPosition(D3DXVECTOR3(1.5f, 5, 0));

	PointLight* pointLight = new PointLight(lightObject); 
	lightObject->SetLight(pointLight);
	pointLight->SetDiffuse(D3DXVECTOR4(1, 1, 1, 0));
	pointLight->SetSpecularColor(D3DXVECTOR4(1, 1, 1, 0));
	pointLight->SetSpecularPower(1.f);
	pointLight->SetRadius(15.f);

	lightObject->SetLight(pointLight);

	return lightObject;
}
