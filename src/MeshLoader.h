#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class MeshLoader{
private:
	std::vector<float> vertexBuffer;
	std::vector<unsigned int> indexBuffer;
	std::string file;
public:
	MeshLoader(const std::string&, int);
	~MeshLoader();

	void reload(const std::string&);
	void load2dFile();
	void load3dFile();
	float* getVertexBuffer();
	unsigned int* getIndexBuffer();
	int vertexBufferSize();
	int indexBufferSize();
	void toString();
};

