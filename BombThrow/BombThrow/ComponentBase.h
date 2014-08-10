#pragma once

class GameObject;

class ComponentBase
{
public:
	ComponentBase(GameObject* gO);

	virtual ~ComponentBase(void);

	GameObject* getGameObject() { return m_gameObject; }

protected:
	ComponentBase(void) {}
	ComponentBase(ComponentBase const&) {}
	void operator=(ComponentBase const&) {}

	GameObject* m_gameObject;
};

