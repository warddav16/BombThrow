#pragma once

#include "ComponentBase.h"

class GameObject;

class Renderer : public ComponentBase
{
public:
	Renderer(GameObject* gO);
	virtual ~Renderer(void);

	virtual void Render()=0;

private:
	Renderer(void);
	Renderer(Renderer const&) {}
	void operator=(Renderer const&) {}
};

