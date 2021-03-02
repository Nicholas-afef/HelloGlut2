#pragma once
#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Matrix.h"

class ShaderHandler {
private:
	unsigned int program;
	std::string vertexShader;
	std::string fragmentShader;
	static std::string parseShader(const std::string&);
public:
	ShaderHandler();
	~ShaderHandler();
	unsigned int compileShader(unsigned int, const std::string&);
	unsigned int createShader();
	unsigned int getProgram();
	void useShader();
	void setBool(const std::string&, bool) const;
	void setInt(const std::string&, int) const;
	void setUni4f(const std::string&, float,float,float,float) const;
	void setMatrix(const std::string&, Matrix);
	void setMatrix(const std::string&, float*);
};
#endif // !SHADERHANDLER_H