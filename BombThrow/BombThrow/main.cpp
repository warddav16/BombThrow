
#include "Windows.h"
#include "GraphicsManager.h"

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

    RegisterClassEx(&wc);

    RECT wr = {0, 0, 800, 600};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    hWnd = CreateWindowEx(NULL,
                          (LPCWSTR)"WindowClass",
                          (LPCWSTR)"Our First Direct3D Program",
                          WS_OVERLAPPEDWINDOW,
                          300,
                          300,
                          wr.right - wr.left,
                          wr.bottom - wr.top,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, iCmdshow);

	//Storing values to reduce lookup times
	GraphicsManager& graphicsManager = GraphicsManager::Instance();

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
			//Update physics
			//Do collisions

			//Render
			graphicsManager.Update();

			//Swap buffers
			graphicsManager.SwapBuffers();
		}
	}

	//Close down managers
	graphicsManager.Shutdown();

	return message.wParam;
}