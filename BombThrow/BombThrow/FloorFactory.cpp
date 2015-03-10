#include "FloorFactory.h"
#include "MeshRenderer.h"
#include "GraphicsManager.h"
#include "Texture.h"
#include "DeferredShader.h"
#include "Transform.h"

FloorFactory::FloorFactory()
{
}


FloorFactory::~FloorFactory()
{
}

GameObject* FloorFactory::Setup()
{
	GameObject* cube = new GameObject();
	MeshRenderer* meshRenderer = new MeshRenderer(cube);
	cube->GetTransform()->SetPosition(D3DXVECTOR3(0.f, - 1.5f, 0.f));
	cube->GetTransform()->SetScale(D3DXVECTOR3(8.f, .5f, 8.f));

	Mesh* mesh = GraphicsManager::Instance().LoadMesh("Models/fancycube.obj");
	meshRenderer->SetMesh(mesh);

	Texture* texture = GraphicsManager::Instance().CreateTexture("Textures/testTexture.dds");
	meshRenderer->AddTexture(texture);

	Shader* shader = new DeferredShader();
	GraphicsManager::Instance().LoadShader(L"Deferred.vs", L"Deferred.ps", shader);
	meshRenderer->SetShader(shader);

	return cube;
}