#pragma once

#include "Windows.h"
#include "GameObject.h"

class IRendererManager;

/*
Graphics Manager : Overhead view of running graphics. Delegates tasks to the chosen rendermanager
*/

class GraphicsManager
{
public:
	~GraphicsManager(void);

	static GraphicsManager& Instance()
	{
		static GraphicsManager instance;
		return instance; //Fancy singleton pattern
	}
	void Startup(HWND hwnd);
	void Shutdown();
	void Update(std::list<GameObject*> gameObjects);
	void SwapBuffers();

private:
	GraphicsManager(void);
	GraphicsManager(GraphicsManager const&);
	void operator=(GraphicsManager const&);

private:
	IRendererManager* m_renderManager;
};

