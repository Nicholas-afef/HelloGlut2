#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &bufferId);
}

void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void VertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
