#include "Light.h"
#include "GraphicsManager.h"

Light::Light(GameObject* gO) : ComponentBase(gO)
{
	GraphicsManager::Instance().AddLight(this);
}


Light::~Light()
{
	if (m_lightShader)
		delete m_lightShader;
}

void Light::ApplyLight(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
	D3DXMATRIX projectionMatrix, Texture** textures)
{
	// Ambient Pass
	m_lightShader->SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, textures);
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_lightShader->GetInputLayout());

	// Set the vertex and pixel shaders that will be used to render.
	deviceContext->VSSetShader(m_lightShader->GetVertexShader(), NULL, 0);
	deviceContext->PSSetShader(m_lightShader->GetPixelShader(), NULL, 0);

	// Set the sampler state in the pixel shader.
	ID3D11SamplerState* sampleState = m_lightShader->GetSampleState();
	deviceContext->PSSetSamplers(0, 1, &sampleState);
}
