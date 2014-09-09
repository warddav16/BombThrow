#include "MeshRenderer.h"

#include "GameObject.h"
#include "DX11Manager.h"

using std::vector;

MeshRenderer::MeshRenderer(GameObject* gO) : Renderer(gO)
{
	m_mesh = 0;
	m_shader = 0;
}


MeshRenderer::~MeshRenderer(void)
{
	if(m_mesh)
	{
		delete m_mesh;
		m_mesh = 0;
	}

	if(m_shader)
	{
		delete m_shader;
		m_shader = 0;
	}

	for(vector<Texture*>::iterator iter = m_textures.begin(); iter != m_textures.end(); iter++)
	{
		delete (*iter);
	}

	m_textures.clear();
}

void MeshRenderer::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(Mesh::Vertex); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexBuffer = m_mesh->GetVertexBuffer();
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* indexBuffer = m_mesh->GetIndexBuffer();
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_shader->SetShaderParameters(deviceContext, world, view, projection, this);

	// Set the vertex input layout.
	deviceContext->IASetInputLayout(m_shader->GetInputLayout());

	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_shader->GetVertexShader(), NULL, 0);
	deviceContext->PSSetShader(m_shader->GetPixelShader(), NULL, 0);

	// Set the sampler state in the pixel shader.
	ID3D11SamplerState* sampleState = m_shader->GetSampleState();
	deviceContext->PSSetSamplers(0, 1, &sampleState);

	// Render the triangle.
	deviceContext->DrawIndexed(m_mesh->GetIndexCount(), 0, 0);

	return;
}