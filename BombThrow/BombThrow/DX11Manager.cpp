#include "DX11Manager.h"



#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")


DX11Manager::DX11Manager(void)
{
}


DX11Manager::~DX11Manager(void)
{
}

void DX11Manager::StartWindow(HWND hwnd, int width, int height, bool fullscreen)
{
	DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    scd.OutputWindow = hwnd;                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = fullscreen;                                    // windowed/full-screen mode

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &m_swapchain,
                                  &m_dev,
                                  NULL,
                                  &m_devcon);
}

void DX11Manager::CloseWindow()
{
	m_swapchain->Release();
    m_dev->Release();
    m_devcon->Release();
}

void DX11Manager::RenderFrame()
{

}

void DX11Manager::SwapBuffers()	
{

}
