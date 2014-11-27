#pragma once
#include "ComponentBase.h"

#include <d3d11.h>
#include <d3dx10math.h>

class Camera : ComponentBase
{
public:
	Camera(GameObject* gO);
	~Camera(void);

	D3DXMATRIX GetViewMatrix();

private:
	Camera(void) {}
};

