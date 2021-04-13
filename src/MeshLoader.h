#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class MeshLoader{
private:
	std::vector<float> vertexData;
	std::vector<unsigned int> indexData;
	std::vector<std::string> files;
	std::vector<unsigned int> indexCounts;
	std::vector<unsigned int> vertexOffsets;
	std::vector<glm::vec3> surfaceNormals;

public:
	MeshLoader(const std::string&, int);
	~MeshLoader();

	void load2dFile(const std::string&);
	void load3dFile(const std::string&);
	float* getVertexData();
	unsigned int* getIndexData();
	std::vector<unsigned int>& getIndexOffsetData();
	int getOffsetPosition(unsigned int);
	int vertexDataSize();
	int indexDataSize();
	void toString();
	void printVertexData();
	void printIndexData();
	void calcSurfaceNormals();
	void calcVertexNormals();
};

