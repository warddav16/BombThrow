#include "daviDsTestFactory.h"

#include "CubeFactory.h"
#include "DebugCameraFactory.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "GraphicsManager.h"

daviDsTestFactory::daviDsTestFactory(void)
{
}


daviDsTestFactory::~daviDsTestFactory(void)
{
}

void daviDsTestFactory::Setup()
{
	CubeFactory cubeFactory;
	GameObject* cube = cubeFactory.Setup();

	GameObjectManager::Instance().AddGameObject(cube);

	DebugCameraFactory camFactory;
	GameObject* cam = camFactory.Setup();

	GameObjectManager::Instance().AddGameObject(cam);
	GraphicsManager::Instance().SetCamera(cam->GetCamera());
}