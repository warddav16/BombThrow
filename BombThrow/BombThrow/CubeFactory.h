
#include "GameObject.h"
#include <d3d11.h>
#include <d3dx11tex.h>

#pragma once
class CubeFactory
{
public:
	CubeFactory(void);
	~CubeFactory(void);

	GameObject* Setup(); //Returns a cube gameobject
};

