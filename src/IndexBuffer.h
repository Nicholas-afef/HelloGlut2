#pragma once

#include<GL/glew.h>
#include <iostream>

class IndexBuffer{
private:
	unsigned int indexBufferId;
	unsigned int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	unsigned int getId() const;
};

