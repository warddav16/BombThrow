#pragma once

#include "Windows.h"
#include "GameObject.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

#include <d3d11.h>
#include <d3dx11tex.h>

class IRendererManager;

/*
Graphics Manager : Overhead view of running graphics. Delegates tasks to the chosen rendermanager
*/

class GraphicsManager
{
public:
	~GraphicsManager(void);

	static GraphicsManager& Instance()
	{
		static GraphicsManager instance;
		return instance; //Fancy singleton pattern
	}
	void Startup(HWND hwnd);
	void Shutdown();
	void Update(std::list<GameObject*> gameObjects);
	void SwapBuffers();
	Mesh* LoadMesh(const char* fileName);
	Texture* CreateTexture(const char* fileName);
	void LoadShader(const WCHAR* vsFileName, const WCHAR* psFileName, Shader* shader);
	Camera* GetCamera() { return m_camera; }
	void SetCamera(Camera* cam) { m_camera = cam; }

private:
	GraphicsManager(void);
	GraphicsManager(GraphicsManager const&);
	void operator=(GraphicsManager const&);

private:
	IRendererManager* m_renderManager;
	Camera* m_camera;
};

