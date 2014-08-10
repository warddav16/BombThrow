#include "GameObject.h"

#include "CustomBehavior.h"

using std::list;

GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

void GameObject::Update(float delta)
{
	list<CustomBehavior*>::iterator iter = m_components.begin();
	for(; iter != m_components.end(); iter++)
	{
		(*iter)->Update(delta);
	}
}

CustomBehavior* GameObject::AddBehavior(CustomBehavior* newBehavior) 
{
	m_components.push_back(newBehavior);
	return newBehavior;
}