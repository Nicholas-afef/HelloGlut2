#pragma once
#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class ShaderHandler {
	friend class Controls;
	/*		The shader handler is response for creating and transmitting data 
		to and from our shaders. It does this by updating uniforms and at times
		calculating necessary matrices to send to the shader.
	*/
private:
	unsigned int shaderProgram;
	std::string vertexShader;
	std::string fragmentShader;
	static std::string parseShader(const std::string&);
	glm::mat4 translator, rotator, scalar, view, perspective;
public:
	ShaderHandler* shaderHandler;
	ShaderHandler(std::string, std::string);
	~ShaderHandler();
	unsigned int compileShader(unsigned int, const std::string&);
	unsigned int createShader();
	unsigned int getProgram();
	void useShader();
	void setBool(const std::string&, bool) const;
	void setUni1i(const std::string&, int) const;
	void setUni1f(const std::string&, float) const;
	void setUni3f(const std::string&, glm::vec3) const;
	void setUni3f(const std::string&, float, float, float) const;
	void setUni4f(const std::string&, float,float,float,float) const;
	void setMat4f(const std::string& name, glm::mat4 matrix);
};
#endif // !SHADERHANDLER_H