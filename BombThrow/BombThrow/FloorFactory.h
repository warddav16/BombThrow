#pragma once
#include "GameObject.h"

class FloorFactory
{
public:
	FloorFactory();
	~FloorFactory();

	GameObject *Setup();
};

