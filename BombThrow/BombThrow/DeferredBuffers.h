#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>

#include "Texture.h"

const int BUFFER_COUNT = 3;

class DeferredBuffers
{
public:
	DeferredBuffers(ID3D11Device* device, int textureWidth, int textureHeight, float screenDepth, float screenNear);
	~DeferredBuffers(void);

	void SetRenderTargets(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargets(ID3D11DeviceContext* deviceContext);
	Texture** GetTextures() { return m_textures; }
	ID3D11DepthStencilView* GetDepthBuffer() { return m_depthStencilView; }


private:
	DeferredBuffers(void);

	ID3D11Texture2D* m_renderTargetTextureArray[BUFFER_COUNT];
	ID3D11RenderTargetView* m_renderTargetViewArray[BUFFER_COUNT];
	Texture* m_textures[BUFFER_COUNT];
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D11_VIEWPORT m_viewport;
	int m_textureWidth, m_textureHeight;
};

