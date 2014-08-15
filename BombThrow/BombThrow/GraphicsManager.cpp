#include "GraphicsManager.h"

#include "DX11Manager.h"

using std::list;

const int RESOLUTION_WIDTH = 640;
const int RESOLUTION_HEIGHT = 480;
const bool IS_FULL_SCREEN = false;

GraphicsManager::GraphicsManager(void)
{
	m_renderManager = new DX11Manager();
}


GraphicsManager::~GraphicsManager(void)
{
}

void GraphicsManager::Startup(HWND hwnd)
{
	m_renderManager->StartWindow(hwnd, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, IS_FULL_SCREEN);
}

void GraphicsManager::Shutdown()
{
	m_renderManager->CloseWindow();
	m_renderManager->RemoveAllCurrentRenderers();
}

void GraphicsManager::Update(list<GameObject*> gameObjects)
{
	m_renderManager->RenderFrame(gameObjects);
}

void GraphicsManager::SwapBuffers()
{
	m_renderManager->SwapBuffers();
}