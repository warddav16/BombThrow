#pragma once

#include "ComponentBase.h"

#include <d3d11.h>

class GameObject;

class Renderer : public ComponentBase
{
public:
	Renderer(GameObject* gO);
	virtual ~Renderer(void);

	virtual void Render(ID3D11DeviceContext*) = 0;

protected:
	Renderer(void);
	Renderer(Renderer const&) {}
	void operator=(Renderer const&) {}
};

