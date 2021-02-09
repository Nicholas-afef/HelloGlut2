#pragma once
#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class ShaderHandler {
private:
	unsigned int program;
	std::string vertexShader;
	std::string fragmentShader;
	static std::string parseShader(const std::string&);
public:
	ShaderHandler();
	unsigned int compileShader(unsigned int, const std::string&);
	unsigned int createShader();
	unsigned int getProgram();
};
#endif // !SHADERHANDLER_H