#include "Mesh.h"

#include <fstream>

using std::vector;
using std::wifstream;

Mesh::Mesh(void)
{
	m_indexCount = 0;
	m_vertexCount = 0;
}


Mesh::~Mesh(void)
{
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

	for(vector<Mesh::Vertex*>::iterator iter = m_vertices.begin(); iter != m_vertices.end(); iter++)
	{
		delete (*iter);
	}

	m_vertices.clear();
}

Mesh::Mesh(const char* fileName)
{
	m_indexCount = 0;
	m_vertexCount = 0;
	this->LoadObj(fileName);
}

void Mesh::LoadObj(const char* fileName) 
{
	wifstream fileIn (fileName);
	unsigned short checkChar;

	vector<D3DXVECTOR3> vertexPos;
	vector<D3DXVECTOR2> uvThings;
	vector<D3DXVECTOR3> normals;
	vector<FaceIndexStructure> faces;

	while(fileIn)
	{			
		checkChar = fileIn.get();	//Get next char

		switch (checkChar)
		{		
		case '#':
			checkChar = fileIn.get();
			while(checkChar != '\n')
				checkChar = fileIn.get();
			break;
		case 'v':	//Get Vertex Descriptions
			checkChar = fileIn.get();
			if(checkChar == ' ')	//v - vert position
			{
				float vz, vy, vx;
				fileIn >> vx >> vy >> vz;	//Store the next three types

				D3DXVECTOR3 vertPos( vx, vy, vz * -1.0f);
				vertexPos.push_back(vertPos); //Assuming right-hand coordinate system obj
					
			}
			if(checkChar == 't')	//vt - vert tex coords
			{			
				float vtcu, vtcv;
				fileIn >> vtcu >> vtcv;		//Store next two types

				D3DXVECTOR2 uv(vtcu, 1.0f-vtcv);

				uvThings.push_back(uv);	//Assuming right-hand coordinate system obj
			}
			if(checkChar == 'n')	//vn - vert normal
			{
				float vnx, vny, vnz;
				fileIn >> vnx >> vny >> vnz;	//Store next three types

				D3DXVECTOR3 theNormal( vnx, vny, vnz * -1.0f );

				normals.push_back(theNormal);	//Invert the Z axis
			}
			break;
		case 'f':
			checkChar = fileIn.get();
			if(checkChar == ' ')	//v - vert position
			{
				FaceIndexStructure face;
				fileIn >> face.vertIndex[0];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.textureIndex[0];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.normalIndex[0];

				checkChar = fileIn.get(); // ' '

				fileIn >> face.vertIndex[1];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.textureIndex[1];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.normalIndex[1];

				checkChar = fileIn.get(); // ' '

				fileIn >> face.vertIndex[2];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.textureIndex[2];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.normalIndex[2];

				fileIn >> face.vertIndex[3];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.textureIndex[3];
				checkChar = fileIn.get(); // '/'
				fileIn >> face.normalIndex[3];

				faces.push_back(face);
			}
			break;
		default:				
			break;
		}
	}

	vector<FaceIndexStructure>::iterator iter = faces.begin();
	for(; iter != faces.end(); iter++)
	{
		for(int i=0; i<4; ++i)
		{
			Vertex* vert = new Vertex();
			vert->position = vertexPos[iter->vertIndex[i]-1];
			vert->texture = uvThings[iter->textureIndex[i]-1];
			vert->normal = normals[iter->normalIndex[i]-1];
			m_vertices.push_back(vert);
			m_vertexCount++;
			m_indexCount++;
		}
	}


	return;
}