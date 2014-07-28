#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "IRendererManager.h"

class DX11Manager : public IRendererManager
{
public:
	DX11Manager(void);
	virtual ~DX11Manager(void);

	virtual void StartWindow(HWND hwnd, int width, int height, bool fullscreen);
	virtual void CloseWindow();
	virtual void RenderFrame();
	virtual void SwapBuffers();

private:
	IDXGISwapChain* m_swapchain;             
	ID3D11Device* m_dev;                     
	ID3D11DeviceContext* m_devcon;
};

