#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArrayObj{
private:
	VertexBuffer vbo;
	IndexBuffer ibo;
	unsigned int vao;
public:
	VertexArrayObj(const void*, unsigned int, const unsigned int* , int);
	~VertexArrayObj();

	void bind();
	void unbind();
	unsigned int getIboId();
	unsigned int getVboId();
};

