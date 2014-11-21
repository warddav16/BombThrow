#include "GameObject.h"

#include "CustomBehavior.h"
#include "Renderer.h"
#include "Transform.h"

using std::list;

GameObject::GameObject(void)
{
	m_transform = new Transform();
}


GameObject::~GameObject(void)
{
	list<CustomBehavior*>::iterator iter = m_components.begin();
	for(; iter != m_components.end(); iter++)
	{
		delete (*iter);
	}

	m_components.clear();

	if(m_renderer != NULL)
	{
		delete m_renderer;
	}
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