#include "CubeFactory.h"

#include "Mesh.h"
#include "Texture.h"
#include "TextureShader.h"
#include "MeshRenderer.h"
#include "GraphicsManager.h"


CubeFactory::CubeFactory(void)
{
}


CubeFactory::~CubeFactory(void)
{
}

//Gameobject included in .h
//Returns a new created cube
GameObject* CubeFactory::Setup()
{
	GameObject* cube =  new GameObject();
	MeshRenderer* meshRenderer = new MeshRenderer(cube);

	Mesh* mesh = GraphicsManager::Instance().LoadMesh("Models/davidcube.obj");
	meshRenderer->SetMesh(mesh);

	Texture* texture  = GraphicsManager::Instance().CreateTexture("Textures/testTexture.dds");
	meshRenderer->AddTexture(texture);

	Shader* shader = new TextureShader();
	GraphicsManager::Instance().LoadShader(L"TextureShaderUnlit.vs", L"TextureShaderUnlit.ps", shader);
	meshRenderer->SetShader(shader);

	return cube;
}