#include "ComponentBase.h"

#include "GameObject.h"

ComponentBase::ComponentBase(GameObject* gO)
{
	m_gameObject = gO;
}


ComponentBase::~ComponentBase(void)
{
}
