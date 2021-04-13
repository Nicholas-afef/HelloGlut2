#include "MeshLoader.h"
#include <map>

MeshLoader::MeshLoader(const std::string& f, int dimension){
	//define a file f (our mesh file) and load it. Dimension signifies the type of object we're loading
	vertexOffsets.push_back(0);
	indexCounts.push_back(0);
	if (dimension == 2) {
		load2dFile(f);
	}
	else if (dimension == 3) {
		load3dFile(f);
	}
}

MeshLoader::~MeshLoader(){
	//clear our buffers
	vertexData.clear();
	indexData.clear();
}

void MeshLoader::load2dFile(const std::string& file){
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
			vertexData.push_back(fmodf(x,2) / 2);
			vertexData.push_back(fmodf(y,2) / 2);
		}
		if (line.c_str()[0] == 'f') {
			int x, y, z;
			sscanf_s(line.c_str(), "f\t%d\t%d\t%d", &x, &y, &z);
			indexData.push_back(x-1 + vertexOffsets.back());
			indexData.push_back(y-1 + vertexOffsets.back());
			indexData.push_back(z-1 + vertexOffsets.back());
			std::cout << "f " << x << " " << y << " " << z << std::endl;
		}
	}
	//these next two lines accomplish some important book-keeping for later
	//vertex counts stores the number of vertices for our loaded object. this is so when we load the next object, its index starts at the next set of vertices
	vertexOffsets.push_back((vertexData.size() / 4));
	//the index buffer offsets are used for draw calls to determine the indices required for a particular draw call
	//we could perform one big drawcall, but by tracking the offsets, we should be able to perform matrix operations on individual draw calls.
	indexCounts.push_back(indexData.size());
	std::cout << "object loaded successfully" << std::endl;
	std::cout << "object vertices: " << vertexData.size() << "\t";
	std::cout << "object Indices: " << indexData.size() << std::endl;
}

void MeshLoader::load3dFile(const std::string& file) {
	//load a series of vertices and indices into our vectors from the provided .obj files
	//this is the 3d version of this function. its almost identical but has one more variable in vertices
	files.push_back(file);
	std::ifstream filestream(file);
	std::string line;
	while (std::getline(filestream, line)) {
		if (line.c_str()[0] == 'v' && line.c_str()[1] != 't') {
			float x, y, z, tX, tY;
			sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);
			//add our vertex position data
			vertexData.push_back(x);
			vertexData.push_back(y);
			vertexData.push_back(z);

			//init our vertex normals here and recalc them later
			vertexData.push_back(0);
			vertexData.push_back(0);
			vertexData.push_back(0);

			//add our texture information to our object's data
			tX = fmodf(abs(x), 1);
			tY = fmodf(abs(y), 1);
			vertexData.push_back(tX);
			vertexData.push_back(tY);
			//std::cout << "v " << x << " " << y << " " << z << " vt " << tX << " " << tY << std::endl;
		}
		if (line.c_str()[0] == 'f') {
			unsigned int x, y, z;
			sscanf_s(line.c_str(), "f\t%d\t%d\t%d", &x, &y, &z);
			x = x - 1 + vertexOffsets.back();
			y = y - 1 + vertexOffsets.back();
			z = z - 1 + vertexOffsets.back();
			indexData.push_back(x);
			indexData.push_back(y);
			indexData.push_back(z);
			//std::cout << "f " << x << " " << y << " " << z << std::endl;
		}
	}
	//these next two lines accomplish some important book-keeping for later
	//vertex counts stores the number of vertices for our loaded object. this is so when we load the next object, its index starts at the next set of vertices
	vertexOffsets.push_back((vertexData.size() / 8));
	//the index buffer offsets are used for draw calls to determine the indices required for a particular draw call
	//we could perform one big drawcall, but by tracking the offsets, we should be able to perform matrix operations on individual draw calls.
	indexCounts.push_back(indexData.size() - indexCounts.back());
	std::cout << "object loaded successfully" << std::endl;
	std::cout << "current total vertices: " << (vertexData.size() / sizeof(float)) << std::endl;
	std::cout << "current total Indices: " << indexCounts.back()<< std::endl;
	std::cout << "object vertex count: " << vertexOffsets.back() << std::endl;
	std::cout << "object index count: " << indexCounts.back() << std::endl;
}


float* MeshLoader::getVertexData(){
	return vertexData.data();
}

unsigned int* MeshLoader::getIndexData(){
	return indexData.data();
}

std::vector<unsigned int>& MeshLoader::getIndexOffsetData() {
	return indexCounts;
}

int MeshLoader::getOffsetPosition(unsigned int obj) {
	return indexCounts[obj] * sizeof(unsigned int);
}

int MeshLoader::vertexDataSize(){
	//returns the size of the vertex data vector in bytes
	return vertexData.size() * sizeof(float);
}

int MeshLoader::indexDataSize(){
	//returns the size of the index data vector in bytes
	return indexData.size();
}

void MeshLoader::toString() {
	std::cout << vertexDataSize() << std::endl;
	std::cout << indexDataSize() << std::endl;
}

void MeshLoader::printVertexData() {
	for (unsigned int x = 0; x < vertexData.size(); x+=8) {
		std::cout << "Vertex #" << (x / 8) << " ";
		std::cout << "v " << vertexData[x] << " " << vertexData[x+1] << " " << vertexData[x+2];
		std::cout << " n " << vertexData[x + 3] << " " << vertexData[x + 4] << " " << vertexData[x + 5];
		std::cout << " vt " << vertexData[x + 6] << " " << vertexData[x + 7] << std::endl;
	}
}
void MeshLoader::printIndexData() {
	for (unsigned int x = 0; x < indexData.size(); x += 3) {
		std::cout << "f " << indexData[x] << " " << indexData[x + 1] << " " << indexData[x + 2] << std::endl;
	}
}
void MeshLoader::calcSurfaceNormals() {
	std::cout << "calculating surface normals..." << std::endl;
	for (unsigned int x = 0; x < indexData.size(); x += 3) {
		//define our 3 vertices based on their x, y, z coordinates
		glm::vec3 vA(vertexData.at(indexData[x] * 8), vertexData.at((indexData[x] * 8) + 1), vertexData.at((indexData[x] * 8) + 2));
		glm::vec3 vB(vertexData.at(indexData[x+1] * 8), vertexData.at((indexData[x+1] * 8) + 1), vertexData.at((indexData[x+1] * 8) + 2));
		glm::vec3 vC(vertexData.at(indexData[x+2] * 8), vertexData.at((indexData[x+2] * 8) + 1), vertexData.at((indexData[x+2] * 8) + 2));

		//calculate their respective vectors
		glm::vec3 u = vB - vA;
		glm::vec3 v = vC - vA;
		//std::cout << "{" << u.x << " " << u.y << u.z << "} X {" << v.x << " " << v.y << " " << v.z << std::endl;
		//insert a surface normal for our triangle
		surfaceNormals.push_back(glm::normalize(glm::cross(u, v)));
	}
}

void MeshLoader::calcVertexNormals() {
	//This function calculates the average of the surface normals of all given indices to generate vertexNormals
	std::cout << "calculating vertex normals..." << std::endl;
	std::map<int, unsigned int> counts;
	//this is sneaky, but gets around it->first being uninitialized
	counts.insert(std::pair<int, unsigned int>(-1, -1));
	unsigned int targ;
	assert((indexData.size() / 3) == surfaceNormals.size());
	for (unsigned int i = 0; i < indexData.size(); ++i) {
		//map algorithm Source: Effective STL by Scott Meyers
		targ = indexData[i];
		std::map<int, unsigned int>::iterator it = counts.lower_bound(targ);
		if (it != counts.end() && !(counts.key_comp()(targ, it->first))) {
			//if vertex in map, increment its count by 1
			it->second += 1;
		}
		else {
			//insert vertex into map
			counts.insert(it, std::pair<int, unsigned int>(targ, 1));
		}
		//add the surface normals of the index to the vertex normals
		//std::cout << "index " << i << " Norms{" << surfaceNormals[i/3].x << " " << surfaceNormals[i/3].y << " " << surfaceNormals[i/3].z << "}" << std::endl;
		vertexData[(targ * 8) + 3] += surfaceNormals.at(i / 3).x;
		vertexData[(targ * 8) + 4] += surfaceNormals.at(i / 3).y;
		vertexData[(targ * 8) + 5] += surfaceNormals.at(i / 3).z;
	}

	for (unsigned int x = 0; x < vertexData.size(); x++) {
		//this amount can never be 0, if it was, it simply wouldn't be in the map
		if (counts[x] != 0) {
			//this if statement was apparently necessary to account for unused vertices...
			float val = 1.0f / counts[x];
			glm::vec3 vNormal(vertexData[(x * 8) + 3], vertexData[(x * 8) + 4], vertexData[(x * 8) + 5]);
			//average our sum by dividing the summed vNormal by the number of surface normals adjacent to the given vertice
			//std::cout << "vnorms{" << vNormal.x << " " << vNormal.y << " " << vNormal.z << "} / " << val << std::endl;
			vNormal = vNormal * val;
			std::cout << "normal " << x << " --- " << vNormal.x << " " << vNormal.y << " " << vNormal.z << std::endl;
			//set our vertex normals data;
			vertexData[(x * 8) + 3] = vNormal.x;
			vertexData[(x * 8) + 4] = vNormal.y;
			vertexData[(x * 8) + 5] = vNormal.z;
		}
	}
}


