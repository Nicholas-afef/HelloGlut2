#include "TextureBuffer.h"
#include "imports/stb_image/stb_image.h"

TextureBuffer::TextureBuffer(const std::string& path)
    :textureBufferId(0), filePath(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0){
   
    //load our image using the imported stbi_image.h
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);

    //generate our texture buffer
    glGenTextures(1, &textureBufferId);
    glBindTexture(GL_TEXTURE_2D, textureBufferId);

    //assign default texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    bind();

    if (localBuffer) {
        stbi_image_free(localBuffer);
    }
}

TextureBuffer::~TextureBuffer() {
    glDeleteTextures(1, &textureBufferId);
}

void TextureBuffer::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureBufferId);
}

void TextureBuffer::unbind() const {
    glBindBuffer(GL_TEXTURE_BUFFER, 0);
}

