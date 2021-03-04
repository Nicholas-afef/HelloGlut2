#include "MeshLoader.h"

MeshLoader::MeshLoader(const std::string& f, int dimension){
	//define a file f (our mesh file) and load it. Dimension signifies the type of object we're loading
	file = f;
	if (dimension == 2) {
		load2dFile();
	}
	else if (dimension == 3) {
		load3dFile();
	}
}

MeshLoader::~MeshLoader(){
	//clear our buffers
	vertexData.clear();
	indexData.clear();
}

void MeshLoader::load2dFile(){
	//load a series of vertices and indices into our vectors from the provided .obj files
	//this is the 2d version of this function
	std::ifstream filestream(file);
	std::string line;
	while (std::getline(filestream, line)) {
		if (line.c_str()[0] == 'v') {
			float x, y;
			sscanf_s(line.c_str(), "v %f %f", &x, &y);
			vertexData.push_back(x);
			vertexData.push_back(y);
			std::cout << "v " << x << " " << y << std::endl;
		}
		if (line.c_str()[0] == 'f') {
			int x, y, z;
			sscanf_s(line.c_str(), "f\t%d\t%d\t%d", &x, &y, &z);
			indexData.push_back(x);
			indexData.push_back(y);
			indexData.push_back(z);
			std::cout << "f " << x << " " << y << " " << z << std::endl;
		}
	}
}

void MeshLoader::load3dFile() {
	//load a series of vertices and indices into our vectors from the provided .obj files
	//this is the 3d version of this function. its almost identical but has one more variable in vertices
	std::ifstream filestream(file);
	std::string line;
	while (std::getline(filestream, line)) {
		if (line.c_str()[0] == 'v') {
			float x, y, z;
			sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);
			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);
			std::cout << "v " << x << " " << y << " " << z << std::endl;
		}
		if (line.c_str()[0] == 'f') {
			unsigned int x, y, z;
			sscanf_s(line.c_str(), "f\t%d\t%d\t%d", &x, &y, &z);
			indexData.push_back(x);
			indexData.push_back(y);
			indexData.push_back(z);
			std::cout << "f " << x << " " << y << " " << z << std::endl;
		}
	}
	std::cout << "object loaded successfully" << std::endl;
	std::cout << "object vertices: " << vertexData.size() << "\t";
	std::cout << "object Indices: " << indexData.size() << std::endl;
}


float* MeshLoader::getVertexData(){
	return vertexData.data();
}

unsigned int* MeshLoader::getIndexData(){
	return indexData.data();
}

int MeshLoader::vertexDataSize(){
	//returns the size of the vertex data vector in bytes
	return vertexData.size() * sizeof(float);
}

int MeshLoader::indexDataSize(){
	//returns the size of the index data vector in bytes
	return indexData.size();
}


void MeshLoader::reload(const std::string& f) {
	//annihilate the previous object and load a new mesh file
	vertexData.clear();
	indexData.clear();
	file = f;
	load2dFile();
}

void MeshLoader::toString() {
	std::cout << vertexDataSize() << std::endl;
	std::cout << indexDataSize() << std::endl;
}


