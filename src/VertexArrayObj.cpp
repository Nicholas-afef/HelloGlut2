#include "VertexArrayObj.h"

VertexArrayObj::VertexArrayObj(const void* vboData, unsigned int vboSize, const unsigned int* iboData, int iboSize):
	vbo(vboData, vboSize), ibo(iboData, iboSize){
	glGenVertexArrays(1, &vao);
	bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo.getId());//Position Buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
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