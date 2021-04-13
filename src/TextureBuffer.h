#pragma once
#include<GL/glew.h>
#include<iostream>
class TextureBuffer{
private:
	unsigned int textureBufferId;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bitsPerPixel;
public:
	TextureBuffer();
	TextureBuffer(const std::string& path);
	~TextureBuffer();
	void loadTexture(const std::string&);
	void bind(unsigned int slot = 0) const;
	void unbind() const;

	inline int getWidth() const { return width; }
};

