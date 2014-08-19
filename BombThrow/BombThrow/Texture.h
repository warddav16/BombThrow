#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>


class Texture
{
public:
	Texture(void);
	Texture(const char* fileName, ID3D11Device* device);
	virtual ~Texture(void);

	ID3D11ShaderResourceView* GetTexture() { m_texture; }
	void LoadFile(const char* fileName, ID3D11Device* device);

private:
	ID3D11ShaderResourceView* m_texture;
};

