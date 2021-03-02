#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Transformation{
private:
	glm::mat4 tMatrix;
public:
	Transformation();
	void translate(float, float, float);
	void rotate(float, float, float, float);
	void scale(float);
	glm::mat4 getMatrix();
};

