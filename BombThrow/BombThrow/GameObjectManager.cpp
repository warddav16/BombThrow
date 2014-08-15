#include "GameObjectManager.h"

using std::list;

GameObjectManager::GameObjectManager(void)
{
}


GameObjectManager::~GameObjectManager(void)
{
	list<GameObject*>::iterator iter;
	for(; iter != m_gameObjects.end(); iter++)
	{
		delete (*iter);
	}

	m_gameObjects.clear();
}


void GameObjectManager::Update(float delta)
{
	list<GameObject*>::iterator iter;
	for(; iter != m_gameObjects.end(); iter++)
	{
		(*iter)->Update(delta);
	}
}
