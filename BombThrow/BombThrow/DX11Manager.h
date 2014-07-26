#pragma once

#include "IRendererManager.h"

class DX11Manager : public IRendererManager
{
public:
	DX11Manager(void);
	virtual ~DX11Manager(void);

	virtual void StartWindow(int width, int height, bool fullscreen);
	virtual void CloseWindow();
	virtual void RenderFrame();
	virtual void SwapBuffers();
};

