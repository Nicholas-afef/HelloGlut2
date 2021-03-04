#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Transformation{
private:
	glm::mat4 tMatrix;
public:
	Transformation();
	void translate(glm::vec3);
	void rotate(float, glm::vec3);
	void scale(float);
	glm::mat4 getMatrix();
};

