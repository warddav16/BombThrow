#pragma once

#include <list>

class CustomBehavior;
class Renderer;

class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	void Update(float delta);

	CustomBehavior* AddBehavior(CustomBehavior* newBehavior);

	Renderer* GetRenderer() { return m_renderer; }
	void SetRenderer(Renderer* renderer) { m_renderer = renderer; }

private:
	std::list<CustomBehavior*> m_components;

	Renderer* m_renderer;
};

