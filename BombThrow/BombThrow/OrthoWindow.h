
#include <d3d11.h>
#include <d3dx10math.h>


#pragma once
class OrthoWindow
{
private:

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	OrthoWindow(ID3D11Device* device, int width, int height);
	OrthoWindow(const OrthoWindow&);
	~OrthoWindow();

	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount() { return m_indexCount; }

private:
	bool InitializeBuffers(ID3D11Device*, int, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
};
