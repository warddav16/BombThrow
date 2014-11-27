#pragma once

#include "GameObject.h"

class DebugCameraFactory
{
public:
	DebugCameraFactory(void);
	~DebugCameraFactory(void);

	GameObject* Setup();
};

