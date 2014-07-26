#include "GraphicsManager.h"

#include "DX11Manager.h"

const int RESOLUTION_WIDTH = 600;
const int RESOLUTION_HEIGHT = 900;
const bool IS_FULL_SCREEN = false;

GraphicsManager::GraphicsManager(void)
{
	m_renderManager = new DX11Manager();
}


GraphicsManager::~GraphicsManager(void)
{
}

void GraphicsManager::Startup()
{
	m_renderManager->StartWindow(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, IS_FULL_SCREEN);
}

void GraphicsManager::Shutdown()
{
	m_renderManager->CloseWindow();
	m_renderManager->RemoveAllCurrentRenderers();
}

void GraphicsManager::Update()
{
	m_renderManager->RenderFrame();
}

void GraphicsManager::SwapBuffers()
{
	m_renderManager->SwapBuffers();
}