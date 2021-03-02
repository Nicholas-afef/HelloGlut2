#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int c) {
    count = c;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &bufferId);
}

void IndexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void IndexBuffer::unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}