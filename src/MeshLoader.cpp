#include "MeshLoader.h"

MeshLoader::MeshLoader(const std::string& f, int dimension){
	file = f;
	if (dimension == 2) {
		load2dFile();
	}
	else if (dimension == 3) {
		load3dFile();
	}
}

MeshLoader::~MeshLoader(){
	vertexBuffer.clear();
	indexBuffer.clear();
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
			vertexBuffer.push_back(x);
			vertexBuffer.push_back(y);
			std::cout << "v " << x << " " << y << std::endl;
		}
		if (line.c_str()[0] == 'f') {
			int x, y, z;
			sscanf_s(line.c_str(), "f\t%d\t%d\t%d", &x, &y, &z);
			indexBuffer.push_back(x);
			indexBuffer.push_back(y);
			indexBuffer.push_back(z);
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
			vertexBuffer.push_back(x);
			vertexBuffer.push_back(y);
			vertexBuffer.push_back(z);
			std::cout << "v " << x << " " << y << " " << z << std::endl;
		}
		if (line.c_str()[0] == 'f') {
			unsigned int x, y, z;
			sscanf_s(line.c_str(), "f\t%d\t%d\t%d", &x, &y, &z);
			indexBuffer.push_back(x);
			indexBuffer.push_back(y);
			indexBuffer.push_back(z);
			std::cout << "f " << x << " " << y << " " << z << std::endl;
		}
	}
	std::cout << "object loaded successfully" << std::endl;
	std::cout << "object vertices: " << vertexBuffer.size() << "\t";
	std::cout << "object Indices: " << indexBuffer.size();
}


float* MeshLoader::getVertexBuffer(){
	return vertexBuffer.data();
}

unsigned int* MeshLoader::getIndexBuffer(){
	return indexBuffer.data();
}

int MeshLoader::vertexBufferSize(){
	return vertexBuffer.size() * sizeof(float);
}

int MeshLoader::indexBufferSize(){
	return indexBuffer.size();
}

void MeshLoader::reload(const std::string& f) {
	//annihilate the previous object and load a new mesh file
	vertexBuffer.clear();
	indexBuffer.clear();
	file = f;
	load2dFile();
}

void MeshLoader::toString() {
	std::cout << vertexBufferSize() << std::endl;
	std::cout << indexBufferSize() << std::endl;
}
