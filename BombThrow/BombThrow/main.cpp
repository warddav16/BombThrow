
#include "Windows.h"
#include "GraphicsManager.h"
#include "GameObjectManager.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	//Windows crap
	bool shouldContinue = true;
	MSG message;

	HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"BomberThrow";

    RegisterClassEx(&wc);

    RECT wr = {0, 0, 800, 600};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx(NULL,
                          L"BomberThrow",    // name of the window class
                          L"BomberThrow",   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          300,    // x-position of the window
                          300,    // y-position of the window
                          500,    // width of the window
                          400,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    ShowWindow(hWnd, iCmdshow);

	//Storing values to reduce lookup times
	GraphicsManager& graphicsManager = GraphicsManager::Instance();
	GameObjectManager& gameObjectManager = GameObjectManager::Instance();
	

	//Startup Managers
	graphicsManager.Startup(hWnd);
	
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
			gameObjectManager.Update(0);

			//Update physics
			//Do collisions

			//Render
			graphicsManager.Update(gameObjectManager.GetGameObjects());

			//Swap buffers
			graphicsManager.SwapBuffers();
		}
	}

	//Close down managers
	graphicsManager.Shutdown();

	return message.wParam;
}