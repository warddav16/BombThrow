#pragma once

/*
Inherited classes of RendererManager will be used to actually hold and render scene data. This class is a base class to be used by GraphicsManager for abstraction purposes
*/
#include <vector>

#include "Windows.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture.h"


class IRendererManager
{
public:
	
	virtual ~IRendererManager(void);

	virtual void StartWindow(HWND hwnd, int width, int height, bool fullscreen) = 0;
	virtual void CloseWindow() = 0;
	virtual void RenderFrame(std::list<GameObject*> gameObjects) = 0;
	virtual void SwapBuffers() = 0;
	virtual Texture* CreateTexture(const char* fileName) = 0;

	void AddRenderer(Renderer* renderer) { m_renderers.push_back( renderer ); }
	void RemoveAllCurrentRenderers() { m_renderers.clear(); }

protected:
	IRendererManager(void);
	std::vector<Renderer*> m_renderers;
};

