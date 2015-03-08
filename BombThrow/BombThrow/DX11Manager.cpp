#include "DX11Manager.h"

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include "GraphicsManager.h"

using std::list;
using std::vector;

DX11Manager::DX11Manager(void)
{
}


DX11Manager::~DX11Manager(void)
{
}

void DX11Manager::StartWindow(HWND hwnd, int width, int height, bool fullscreen)
{
	DXGI_SWAP_CHAIN_DESC scd;

	m_screenDepth = 1000.0f;
	m_screenNear = .1f;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    scd.OutputWindow = hwnd;                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = !fullscreen;                             // windowed/full-screen mode
	m_width = width;
	m_height = height;
	m_fullscreen = fullscreen;
	m_hwnd = hwnd;

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &m_swapChain,
                                  &m_device,
                                  NULL,
                                  &m_deviceContext);

	if(!InitDx3d())
	{
		MessageBox(hwnd, L"Crashed", L"Error", MB_OK);
	}
}

void DX11Manager::CloseWindow()
{
	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	if(m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}

	if(m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}

	if(m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}

	if(m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}

	if(m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}

	if(m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}

	if(m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	if(m_device)
	{
		m_device->Release();
		m_device = 0;
	}

	if(m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}

	if (m_additiveBlendState)
	{
		m_additiveBlendState->Release();
		m_additiveBlendState = 0;
	}

	if(m_deferredBuffers)
	{
		delete m_deferredBuffers;
	}

	if(m_orthoWindow)
	{
		delete m_orthoWindow;
	}

	if(m_ambientLightShader)
	{
		delete m_ambientLightShader;
	}
}

void DX11Manager::RenderFrame(list<GameObject*> gameObjects)
{
	// Render the scene into the deferred textures
	this->RenderToTextures(gameObjects);

	float color[4];
	color[0]=0;
	color[1]=0.3;
	color[2]=0.f;
	color[3]=0;

	// Clear the back buffer.
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
    
	// Clear the depth buffer.
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Turn off the ZBuffer to do 2D rendering lighting pass
	this->SetZBuffer(false);

	// Put the window into the pipeline to be rendered. 
	// For the rest of the frame, all lighting shader operations will be performed on this mesh (which is the size of the window)
	m_orthoWindow->Render(m_deviceContext);

	// Do the lighting pass with the on the window model
	this->LightingPass();

	// Set the Z Buffer back to true for the next pass
	this->SetZBuffer(true);
	this->SetBlendStateNoBlend();
}

void DX11Manager::SwapBuffers()	
{
	if(m_vsync_enabled)
	{
		// Lock to screen refresh rate.
		m_swapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_swapChain->Present(0, 0);
	}
}

void DX11Manager::RenderToTextures(list<GameObject*> gameObjects)
{
	D3DXMATRIX world = m_worldMatrix;
	D3DXMATRIX proj = m_projectionMatrix;

	D3DXMATRIX viewMatrix = GraphicsManager::Instance().GetCamera()->GetViewMatrix();

	// Set the render buffers to be the render target.
	m_deferredBuffers->SetRenderTargets(m_deviceContext);

	// Clear the render buffers.
	m_deferredBuffers->ClearRenderTargets(m_deviceContext);


	// Render our scene
	list<GameObject*>::iterator iter = gameObjects.begin();
	for(; iter != gameObjects.end(); iter++)
	{
		if((*iter)->GetRenderer() != NULL)
		{
			(*iter)->GetRenderer()->Render(m_deviceContext, world, viewMatrix, proj);
		}
	}
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	m_deviceContext->RSSetViewports(1, &m_viewport);
}

void DX11Manager::LightingPass()
{
	D3DXMATRIX world = m_worldMatrix;
	D3DXMATRIX ortho = m_orthoMatrix;

	D3DXMATRIX viewMatrix; //Needs to come from camera
	///TEST///---------------------------------------------------------------------------
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = 0;
	position.y = 0;
	position.z = -10.0f;
	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = 0;
	yaw   = 0;
	roll  = 0;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);
	///END_TEST///---------------------------------------------------------------------------
	
	// Ambient Pass
	m_ambientLightShader->SetShaderParameters(m_deviceContext, world, viewMatrix, ortho, m_deferredBuffers->GetTextures());
	// Set the vertex input layout.
	m_deviceContext->IASetInputLayout(m_ambientLightShader->GetInputLayout());

	// Set the vertex and pixel shaders that will be used to render.
	m_deviceContext->VSSetShader(m_ambientLightShader->GetVertexShader(), NULL, 0);
	m_deviceContext->PSSetShader(m_ambientLightShader->GetPixelShader(), NULL, 0);

	// Set the sampler state in the pixel shader.
	ID3D11SamplerState* sampleState = m_ambientLightShader->GetSampleState();
	m_deviceContext->PSSetSamplers(0, 1, &sampleState);

	// Render the geometry.
	m_deviceContext->DrawIndexed(m_orthoWindow->GetIndexCount(), 0, 0);
	this->SetBlendStateAddidativeBlend();

	// Lighting pass
	vector<Light*>::iterator lightIter = GraphicsManager::Instance().GetLights()->begin();
	for (; lightIter != GraphicsManager::Instance().GetLights()->end(); ++lightIter)
	{
		(*lightIter)->ApplyLight(m_deviceContext, world, viewMatrix, ortho, m_deferredBuffers->GetTextures());
		// Render the geometry.
		m_deviceContext->DrawIndexed(m_orthoWindow->GetIndexCount(), 0, 0);
	}
}

void DX11Manager::SetZBuffer(bool toSet)
{
	if(toSet)
	{
		m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	}
	else
	{
		m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);
	}
}

void DX11Manager::SetBlendStateAddidativeBlend()
{
	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_deviceContext->OMSetBlendState(m_additiveBlendState, blendFactor, 0xffffffff);
}

void DX11Manager::SetBlendStateNoBlend()
{
	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_deviceContext->OMSetBlendState(m_noBlendBlendState, blendFactor, 0xffffffff);
}

///////////////////
/// Setup Stuff ///
///////////////////


bool DX11Manager::InitDx3d(void)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, i, numerator, denominator, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_BLEND_DESC addidativeBlendDesc;
	D3D11_BLEND_DESC noBlendDesc;
	float fieldOfView, screenAspect;

	// Create a DirectX graphics interface factory.
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if(FAILED(result))
	{
		return false;
	}

	// Use the factory to create an adapter for the primary graphics interface (video card).
	result = factory->EnumAdapters(0, &adapter);
	if(FAILED(result))
	{
		return false;
	}

	// Enumerate the primary adapter output (monitor).
	result = adapter->EnumOutputs(0, &adapterOutput);
	if(FAILED(result))
	{
		return false;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];
	if(!displayModeList)
	{
		return false;
	}

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if(FAILED(result))
	{
		return false;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for(i=0; i<numModes; i++)
	{
		if(displayModeList[i].Width == (unsigned int)m_width)
		{
			if(displayModeList[i].Height == (unsigned int)m_height)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	result = adapter->GetDesc(&adapterDesc);
	if(FAILED(result))
	{
		return false;
	}

	// Store the dedicated video card memory in megabytes.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if(error != 0)
	{
		return false;
	}

	// Release the display mode list.
	delete [] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = 0;

	// Release the adapter.
	adapter->Release();
	adapter = 0;

	// Release the factory.
	factory->Release();
	factory = 0;

	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = m_width;
	swapChainDesc.BufferDesc.Height = m_height;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if(m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = m_hwnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if(m_fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	// Create the swap chain, Direct3D device, and Direct3D device context.
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, 
					       D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);
	if(FAILED(result))
	{
		return false;
	}

	// Get the pointer to the back buffer.
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if(FAILED(result))
	{
		return false;
	}

	// Create the render target view with the back buffer pointer.
	result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	if(FAILED(result))
	{
		return false;
	}

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();
	backBufferPtr = 0;

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = m_width;
	depthBufferDesc.Height = m_height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if(FAILED(result))
	{
		return false;
	}

	// Set the depth stencil state.
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if(FAILED(result))
	{
		return false;
	}

	// Clear the second depth stencil state before setting the parameters.
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is 
	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
	depthDisabledStencilDesc.DepthEnable = false;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the state using the device.
	result = m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_depthDisabledStencilState);
	if (FAILED(result))
	{
		return false;
	}

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if(FAILED(result))
	{
		return false;
	}

	// Now set the rasterizer state.
	m_deviceContext->RSSetState(m_rasterState);


	// Set up add blend state
	addidativeBlendDesc.AlphaToCoverageEnable = false;
	addidativeBlendDesc.IndependentBlendEnable = false;
	addidativeBlendDesc.RenderTarget[0].BlendEnable = TRUE;
	addidativeBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	addidativeBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	addidativeBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	addidativeBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	addidativeBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	addidativeBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	addidativeBlendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	result = m_device->CreateBlendState(&addidativeBlendDesc, &m_additiveBlendState);
	if (FAILED(result))
	{
		return false;
	}

	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;;
	

	// Set up no add blend state
	noBlendDesc.AlphaToCoverageEnable = false;
	noBlendDesc.IndependentBlendEnable = false;
	noBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	noBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	noBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	noBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	noBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	noBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	noBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	noBlendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	result = m_device->CreateBlendState(&noBlendDesc, &m_noBlendBlendState);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the viewport for rendering.
	m_viewport.Width = (float)m_width;
	m_viewport.Height = (float)m_height;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;

	// Create the viewport.
	m_deviceContext->RSSetViewports(1, &m_viewport);

	// Setup the projection matrix.
	fieldOfView = (float)D3DX_PI / 4.0f;
	screenAspect = (float)m_width / (float)m_height;

	// Create the projection matrix for 3D rendering.
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, m_screenNear, m_screenDepth);

	// Initialize the world matrix to the identity matrix.
	D3DXMatrixIdentity(&m_worldMatrix);

	// Create an orthographic projection matrix for 2D rendering.
	D3DXMatrixOrthoLH(&m_orthoMatrix, (float)m_width, (float)m_height, m_screenNear, m_screenDepth);

	// Create the deferred shader buffers
	m_deferredBuffers = new DeferredBuffers(m_device, m_width, m_height, m_screenDepth, m_screenNear);
	//Create the ortho window used for deferred rendering
	m_orthoWindow = new OrthoWindow(m_device, m_width, m_height);
	// Create Light Shaders to use
	m_ambientLightShader = new AmbientLightShader();
	this->LoadShader(L"AmbientLight.vs", L"AmbientLight.ps", m_ambientLightShader);

	return true;
}


//////////////////////
/// Creating Stuff ///
//////////////////////


Texture* DX11Manager::CreateTexture(const char* fileName)
{
	ID3D11ShaderResourceView* textureResource = 0;
	Texture* texture = new Texture();
	wchar_t wtext[150];
	mbstowcs(wtext, fileName, strlen(fileName)+1);//Plus null
	LPWSTR ptr = wtext;
	D3DX11CreateShaderResourceViewFromFile(m_device, ptr, NULL, NULL, &textureResource, NULL);
	texture->SetTexture(textureResource);
	return texture;
}

void DX11Manager::LoadShader(const WCHAR* vsFileName, const WCHAR* psFileName, Shader* shader)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;

	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the vertex shader code.
	result = D3DX11CompileFromFile(vsFileName, NULL, NULL, shader->GetVertexFunctionName(), "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
				       &vertexShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage((char*)errorMessage->GetBufferPointer(), vsFileName);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(m_hwnd, vsFileName, L"Missing Shader File", MB_OK);
		}

		return ;
	}

	// Compile the pixel shader code.
	result = D3DX11CompileFromFile(psFileName, NULL, NULL, shader->GetPixelFunctionName(), "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
				       &pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage((char*)errorMessage->GetBufferPointer(), psFileName);
		}
		// If there was nothing in the error message then it simply could not find the file itself.
		else
		{
			MessageBox(m_hwnd, psFileName, L"Missing Shader File", MB_OK);
		}

		return ;
	}

	// Create the vertex shader from the buffer.
	ID3D11VertexShader* vertexShader = 0;
	ID3D11PixelShader* pixelShader = 0;
	result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
	if(FAILED(result))
	{
		return ;
	}

	shader->SetVertexShader(vertexShader);

	// Create the pixel shader from the buffer.
	result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);
	if(FAILED(result))
	{
		return ;
	}

	shader->SetPixelShader(pixelShader);

	shader->LoadShaderParameters(m_device, vertexShaderBuffer, pixelShaderBuffer);

	if(pixelShaderBuffer)
	{
		pixelShaderBuffer->Release();
		pixelShaderBuffer = 0;
	}
	if(vertexShaderBuffer)
	{
		vertexShaderBuffer->Release();
		vertexShaderBuffer = 0;
	}
	if(errorMessage)
	{
		errorMessage->Release();
		errorMessage = 0;
	}
}

Mesh* DX11Manager::LoadMesh(const char* fileName)
{
	Mesh* mesh = new Mesh(fileName);

	if(mesh == 0)
	{
		return NULL;
	}

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	Mesh::Vertex* vertices = new Mesh::Vertex[mesh->GetVertexCount()];
	if(!vertices)
	{
		return false;
	}

	unsigned long* indices = new unsigned long[mesh->GetIndexCount()];
	if(!indices)
	{
		return NULL;
	}

	// Load the vertex array and index array with data.
	for(int i=0; i<mesh->GetVertexCount(); i++)
	{
		vertices[i].position = D3DXVECTOR3(mesh->GetVertices()[i]->position.x, 
			mesh->GetVertices()[i]->position.y, mesh->GetVertices()[i]->position.z);
		vertices[i].texture = D3DXVECTOR2(mesh->GetVertices()[i]->texture.x, 
			mesh->GetVertices()[i]->texture.y);
		vertices[i].normal = D3DXVECTOR3(mesh->GetVertices()[i]->normal.x, 
			mesh->GetVertices()[i]->normal.y, mesh->GetVertices()[i]->normal.z);

		indices[i] = i;
	}



	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Mesh::Vertex) * mesh->GetVertexCount();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	ID3D11Buffer* vertexBuffer = 0;
	HRESULT result = m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if(FAILED(result))
	{
		return NULL;
	}
	
	mesh->SetVertexBuffer(vertexBuffer);


	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * mesh->GetIndexCount();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	ID3D11Buffer* indexBuffer;
	result = m_device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if(FAILED(result))
	{
		return NULL;
	}

	mesh->SetIndexBuffer(indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return mesh;
}