#include "DebugCameraFactory.h"

#include "Camera.h"
#include "Transform.h"

DebugCameraFactory::DebugCameraFactory(void)
{
}


DebugCameraFactory::~DebugCameraFactory(void)
{
}

GameObject* DebugCameraFactory::Setup()
{
	GameObject* cam =  new GameObject();

	Camera* camera = new Camera(cam);

	cam->GetTransform()->SetPosition(D3DXVECTOR3(0,0,-10));

	return cam;
}