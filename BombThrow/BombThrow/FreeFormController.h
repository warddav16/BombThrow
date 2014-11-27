#pragma once
#include "CustomBehavior.h"

class FreeFormController : public CustomBehavior
{
public:
	FreeFormController(GameObject* gO);
	~FreeFormController(void);

	virtual void Update(float delta);
};

