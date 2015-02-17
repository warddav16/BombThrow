#pragma once

#include <list>

class CustomBehavior;
class Renderer;
class Transform;
class Camera;
class Light;

class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	void Update(float delta);

	CustomBehavior* AddBehavior(CustomBehavior* newBehavior);

	Renderer* GetRenderer() { return m_renderer; }
	void SetRenderer(Renderer* renderer) { m_renderer = renderer; }

	Transform* GetTransform() { return m_transform; }

	Camera* GetCamera() { return m_camera; }
	void SetCamera(Camera* cam) { m_camera = cam; }

	Light* GetLight() { return m_light; }
	void SetLight(Light* light) { m_light = light; }

private:
	std::list<CustomBehavior*> m_components;

	Renderer* m_renderer;
	Transform* m_transform;
	Camera* m_camera;
	Light* m_light;
};

