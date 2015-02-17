#pragma once

#include "GameObject.h"

class PointLightFactory
{
public:
	PointLightFactory();
	~PointLightFactory();

	GameObject* Setup();
};

