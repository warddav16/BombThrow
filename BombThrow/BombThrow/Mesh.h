#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

#include <vector>

class Mesh
{
public:

	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct FaceIndexStructure
	{
		int vertIndex[4];
		int textureIndex[4];
		int normalIndex[4];
	};

	Mesh(void);
	Mesh(const char* fileName);
	~Mesh(void);

	void LoadObj(const char* fileName);

	const std::vector<Vertex*> GetVertices() { return m_vertices; }
	const int GetVertexCount() { return m_vertexCount; }
	const int GetIndexCount() { return m_indexCount; }

	ID3D11Buffer* GetVertexBuffer() { return m_vertexBuffer; }
	void SetVertexBuffer(ID3D11Buffer* vertexBuffer) { m_vertexBuffer = vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return m_indexBuffer; }
	void SetIndexBuffer(ID3D11Buffer* indexBuffer) { m_indexBuffer = indexBuffer; }

private:
	std::vector<Vertex*> m_vertices;

	int m_vertexCount;
	int m_indexCount;

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
};

