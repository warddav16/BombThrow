#pragma once

#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <vector>

class GameObject;

class MeshRenderer : public Renderer
{
public:
	MeshRenderer(GameObject* gO);
	~MeshRenderer(void);

	virtual void Render(ID3D11DeviceContext*);

public:
	Mesh* GetMesh() { return m_mesh; }
	void SetMesh(Mesh* mesh) { m_mesh = mesh; }
	void AddTexture(Texture* texture) { m_textures.push_back(texture); }
	Texture* GetTexture(int n) { return m_textures[n]; }

	void Init(ID3D11Device* );

private:
	MeshRenderer(void);
	MeshRenderer(MeshRenderer const&) {}
	void operator=(MeshRenderer const&) {}

private:
	std::vector<Texture*> m_textures;
	Mesh* m_mesh;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
};

