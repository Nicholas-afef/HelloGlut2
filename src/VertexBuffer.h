#pragma once
#include<GL/glew.h>
#include <iostream>
class VertexBuffer {
private:
	unsigned int vertexBufferId;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int getId() const;
};