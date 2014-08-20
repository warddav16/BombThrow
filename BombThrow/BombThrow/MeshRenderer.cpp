#include "MeshRenderer.h"

#include "GameObject.h"
#include "DX11Manager.h"

using std::vector;

MeshRenderer::MeshRenderer(GameObject* gO) : Renderer(gO)
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
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

	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
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

void MeshRenderer::Init(ID3D11Device* device)
{
	if(m_mesh == 0)
	{
		return;
	}

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;


	unsigned long* indices = new unsigned long[m_mesh->GetIndexCount()];
	if(!indices)
	{
		return;
	}

	for(int i=0; i<m_mesh->GetIndexCount(); ++i)
	{
		indices[i] = i;
	}


	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Mesh::Vertex) * m_mesh->GetVertexCount();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = &(m_mesh->GetVertices()[0]);
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	if(!device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer))
	{
		return;
	}


	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_mesh->GetIndexCount();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	if(!device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer))
	{
		return;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.

	delete [] indices;
	indices = 0;
}

void MeshRenderer::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(Mesh::Vertex); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_shader->SetShaderParameters(deviceContext, world, view, projection, m_textures[0]->GetTexture());

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