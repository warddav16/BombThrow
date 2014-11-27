#include "GameObject.h"

#include "CustomBehavior.h"
#include "Renderer.h"
#include "Transform.h"
#include "Camera.h"

using std::list;

GameObject::GameObject(void)
{
	m_transform = new Transform(this);
	m_renderer = NULL;
	m_camera = NULL;
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

	if(m_camera != NULL)
	{
		delete m_camera;
	}

	if(m_transform != NULL)
	{
		delete m_transform;
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