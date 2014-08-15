#pragma once

#include <list>

#include "GameObject.h"

class GameObjectManager
{
public:
	~GameObjectManager(void);

	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		return instance; //Fancy singleton pattern
	}

	void Update(float delta);

	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }

private:
	GameObjectManager(void);
	GameObjectManager(GameObjectManager const&) {}
	void operator=(GameObjectManager const&) {}

	std::list<GameObject*> m_gameObjects;
};

