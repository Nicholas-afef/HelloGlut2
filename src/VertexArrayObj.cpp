#include "VertexArrayObj.h"

VertexArrayObj::VertexArrayObj(MeshLoader& meshes):
	vbo(meshes.getVertexData(), meshes.vertexDataSize()), 
	ibo(meshes.getIndexData(), meshes.indexDataSize(), meshes.getIndexOffsetData()){

	glGenVertexArrays(1, &vao);
	bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo.getId());//Position Buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.getId());
}

VertexArrayObj::~VertexArrayObj(){
	vbo.~VertexBuffer();
	ibo.~IndexBuffer();
	glDeleteVertexArrays(1,&vao);
}

void VertexArrayObj::bind(){
	glBindVertexArray(vao);
}

void VertexArrayObj::unbind(){
	glBindVertexArray(0);
}

unsigned int VertexArrayObj::getIboId() {
	return ibo.getId();
}

unsigned int VertexArrayObj::getVboId() {
	return vbo.getId();
}