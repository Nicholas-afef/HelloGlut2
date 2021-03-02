#pragma once

#include<GL/glew.h>

class IndexBuffer{
private:
	unsigned int bufferId;
	unsigned int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
};

