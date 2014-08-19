#include "Texture.h"

#include "DX11Manager.h"

Texture::Texture(void)
{
	m_texture = 0;
}

Texture::Texture(const char* fileName, ID3D11Device* device)
{
	this->LoadFile(fileName, device);
}


Texture::~Texture(void)
{
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}

void Texture::LoadFile(const char* fileName, ID3D11Device* device)
{
	//TODO: Find a better way to share the device
	D3DX11CreateShaderResourceViewFromFile(device, (LPCWSTR)fileName, NULL, NULL, &m_texture, NULL);
}
