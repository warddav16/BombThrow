
#include "Windows.h"
#include "GraphicsManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	//Windows crap
	bool shouldContinue = true;
	MSG message;

	//Storing values to reduce lookup times
	GraphicsManager& graphicsManager = GraphicsManager::Instance();

	//Startup Managers
	graphicsManager.Startup();
	
	//DA GAME LOOP AHH
	while(shouldContinue) 
	{
		if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		if(message.message == WM_QUIT)
		{
			shouldContinue = false;
		}
		else
		{
			//Update game objects
			//Update physics
			//Do collisions

			//Render
			graphicsManager.Update();

			//Swap buffers
			graphicsManager.SwapBuffers();
		}
	}

	//Close down managers
}