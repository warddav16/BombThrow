#include "IRendererManager.h"

#include <fstream>

using std::ofstream;

IRendererManager::IRendererManager(void)
{
}


IRendererManager::~IRendererManager(void)
{
}

void IRendererManager::OutputShaderErrorMessage(const char* errorMessage, const WCHAR* shaderFilename)
{
	ofstream fout;

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(unsigned long i=0; errorMessage[i] != '\0'; i++)
	{
		fout << errorMessage[i];
	}

	// Close the file.
	fout.close();

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(m_hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}