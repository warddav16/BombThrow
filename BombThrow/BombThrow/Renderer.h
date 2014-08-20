#pragma once

#include "ComponentBase.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

class GameObject;

class Renderer : public ComponentBase
{
public:
	Renderer(GameObject* gO);
	virtual ~Renderer(void);

	virtual void Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)=0;

protected:
	Renderer(void);
	Renderer(Renderer const&) {}
	void operator=(Renderer const&) {}
};

