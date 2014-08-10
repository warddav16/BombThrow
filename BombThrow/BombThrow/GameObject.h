#pragma once

#include <list>

class CustomBehavior;

class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	void Update(float delta);

	CustomBehavior* AddBehavior(CustomBehavior* newBehavior);

private:
	std::list<CustomBehavior*> m_components;
};

