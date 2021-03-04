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
#include "Transformation.h"

class ShaderHandler {
	/*		The shader handler is response for creating and transmitting data 
		to and from our shaders. It does this by updating uniforms and at times
		calculating necessary matrices to send to the shader.
	*/
private:
	unsigned int shaderProgram;
	std::string vertexShader;
	std::string fragmentShader;
	static std::string parseShader(const std::string&);
	glm::mat4 translator, rotator, scalar, view;
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
	void setTranslate(glm::vec3);
	void setScale(float);
	void setRotate(float angle, glm::vec3 axisOfRotation);
	void updateModelView();
	void setView(glm::vec3 position, glm::vec3 nVec, glm::vec3 upVec);
	void setPerspective(float angle, float screenWidth, float screenHeight, float near, float far);
};
#endif // !SHADERHANDLER_H