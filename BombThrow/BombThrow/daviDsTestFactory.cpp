#include "daviDsTestFactory.h"

#include "CubeFactory.h"
#include "GameObject.h"
#include "GameObjectManager.h"

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
}