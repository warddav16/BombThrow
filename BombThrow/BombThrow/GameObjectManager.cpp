#include "GameObjectManager.h"

using std::list;

GameObjectManager::GameObjectManager(void)
{
}


GameObjectManager::~GameObjectManager(void)
{
	list<GameObject*>::iterator iter = m_gameObjects.begin();
	for(; iter != m_gameObjects.end(); iter++)
	{
		delete (*iter);
	}

	m_gameObjects.clear();
}


void GameObjectManager::Update(float delta)
{
	list<GameObject*>::iterator iter = m_gameObjects.begin();
	for(; iter != m_gameObjects.end(); iter++)
	{
		(*iter)->Update(delta);
	}
}
