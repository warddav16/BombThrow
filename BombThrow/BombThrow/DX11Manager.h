#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "IRendererManager.h"
#include "GameObject.h"
#include "DeferredBuffers.h"
#include "OrthoWindow.h"
#include "AmbientLightShader.h"

class DX11Manager : public IRendererManager
{
public:
	DX11Manager(void);
	virtual ~DX11Manager(void);

	virtual void StartWindow(HWND hwnd, int width, int height, bool fullscreen);
	virtual void CloseWindow();
	virtual void RenderFrame(std::list<GameObject*> gameObjects);
	virtual void SwapBuffers();
	virtual Mesh* LoadMesh(const char* fileName);
	virtual Texture* CreateTexture(const char* fileName);
	virtual void LoadShader(const WCHAR* vsFileName, const WCHAR* psFileName, Shader* shader);
	bool InitDx3d(void);

private:
	void RenderToTextures(std::list<GameObject*> gameObjects);
	void LightingPass();
	void SetZBuffer(bool toSet);
	void SetBlendStateAddidativeBlend();
	void SetBlendStateNoBlend();

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
	ID3D11DepthStencilState* m_depthDisabledStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	ID3D11BlendState* m_additiveBlendState;
	ID3D11BlendState* m_noBlendBlendState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
	D3D11_VIEWPORT m_viewport;

	DeferredBuffers* m_deferredBuffers;
	OrthoWindow* m_orthoWindow;
	AmbientLightShader* m_ambientLightShader;

	float m_screenNear;
	float m_screenDepth;
};

