#pragma once
#include "componentbase.h"


class CustomBehavior : public ComponentBase
{
public:
	CustomBehavior(GameObject* gO);

	virtual ~CustomBehavior(void);

	virtual void Update(float delta) = 0;

private:
	CustomBehavior(void) {}
	CustomBehavior(CustomBehavior const&) {}
	void operator=(CustomBehavior const&) {}
};

