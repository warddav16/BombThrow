#include "CubeFactory.h"

#include "Mesh.h"
#include "Texture.h"
#include "DeferredShader.h"
#include "MeshRenderer.h"
#include "GraphicsManager.h"
#include "FreeFormController.h"

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

	Shader* shader = new DeferredShader();
	GraphicsManager::Instance().LoadShader(L"Deferred.vs", L"Deferred.ps", shader);
	meshRenderer->SetShader(shader);
	//cube->AddBehavior(new FreeFormController(cube));

	return cube;
}