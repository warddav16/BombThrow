#include "Mesh.h"

#include <fstream>

using std::ifstream;
using std::vector;

Mesh::Mesh(void)
{
	m_indexCount = 0;
	m_vertexCount = 0;
}


Mesh::~Mesh(void)
{
	for(vector<Mesh::Vertex*>::iterator iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		delete (*iter);
	}

	m_vertices.clear();
}

Mesh::Mesh(const char* fileName)
{
	this->LoadObj(fileName);
}

void Mesh::LoadObj(const char* fileName) 
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(fileName);
	
	// If it could not open the file then exit.
	if(fin.fail())
	{
		return;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	m_vertices.reserve(m_indexCount);

	// Read up to the beginning of the data.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for(i=0; i<m_vertexCount; i++)
	{
		m_vertices[i] = new Mesh::Vertex();
		fin >> m_vertices[i]->position.x >> m_vertices[i]->position.y >> m_vertices[i]->position.z;
		fin >> m_vertices[i]->texture.x >> m_vertices[i]->texture.y;
		fin >> m_vertices[i]->normal.x >> m_vertices[i]->normal.y >> m_vertices[i]->normal.z;
	}

	// Close the model file.
	fin.close();

	return;
}