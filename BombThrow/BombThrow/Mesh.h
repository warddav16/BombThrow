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

	Mesh(void);
	Mesh(const char* fileName);
	~Mesh(void);

	void LoadObj(const char* fileName);

	const std::vector<Vertex*> GetVertices() { return m_vertices; }
	const int GetVertexCount() { return m_vertexCount; }
	const int GetIndexCount() { return m_indexCount; }

private:
	std::vector<Vertex*> m_vertices;

	int m_vertexCount;
	int m_indexCount;
};

