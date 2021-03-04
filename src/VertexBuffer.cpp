#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    std::cout << "vertexBuffer size: " << size << std::endl;
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &vertexBufferId);
}

void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
}

void VertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
