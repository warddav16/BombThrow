#include "Renderer.h"

#include "GameObject.h"

Renderer::Renderer(GameObject* gO) : ComponentBase(gO)
{
	gO->SetRenderer(this);
}


Renderer::~Renderer(void)
{
}
