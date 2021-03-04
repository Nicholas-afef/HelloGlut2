#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class MeshLoader{
private:
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	std::string file;
public:
	MeshLoader(const std::string&, int);
	~MeshLoader();

	void reload(const std::string&);
	void load2dFile();
	void load3dFile();
	float* getVertexData();
	unsigned int* getIndexData();
	int vertexDataSize();
	int indexDataSize();
	void toString();
};

