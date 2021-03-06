#include "daviDsTestFactory.h"

#include "CubeFactory.h"
#include "DebugCameraFactory.h"
#include "PointLightFactory.h"
#include "FloorFactory.h"

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

	PointLightFactory pointLightFactory;
	GameObject* pointLight = pointLightFactory.Setup();

	GameObjectManager::Instance().AddGameObject(pointLight);

	FloorFactory floorFactory;
	GameObject* floor = floorFactory.Setup();
	GameObjectManager::Instance().AddGameObject(floor);
}