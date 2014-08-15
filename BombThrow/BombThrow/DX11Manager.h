#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "IRendererManager.h"
#include "GameObject.h"

class DX11Manager : public IRendererManager
{
public:
	DX11Manager(void);
	virtual ~DX11Manager(void);

	virtual void StartWindow(HWND hwnd, int width, int height, bool fullscreen);
	virtual void CloseWindow();
	virtual void RenderFrame(std::list<GameObject*> gameObjects);
	virtual void SwapBuffers();
	bool InitDx3d(void);

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
	
	int m_width;
	int m_height;
	bool m_fullscreen;
	HWND m_hwnd;
	float m_screenNear;
	float m_screenDepth;
};

