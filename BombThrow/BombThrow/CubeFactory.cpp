#include "CubeFactory.h"

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
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

	//Mesh* mesh = new Mesh("Models/Cube.obj");
	//meshRenderer->SetMesh(mesh);

	//Texture* texture  = GraphicsManager::Instance().CreateTexture("someFileName");
	//meshRenderer->AddTexture(texture);

	return cube;
}