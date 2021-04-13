#pragma once

#include<GL/glew.h>
#include <iostream>
#include <vector>

class IndexBuffer{
private:
	unsigned int indexBufferId;
	unsigned int count;
public:
	IndexBuffer(const unsigned int*, unsigned int, const std::vector<unsigned int>&);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	unsigned int getId() const;
};

