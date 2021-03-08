#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Model{
private:
	glm::vec3 translate;
	float rotAngle;
	glm::vec3 axisOfRotation;
	float scalar;
public:
	Model();
	void setPosition(glm::vec3);
	void setAngle(float);
	void setAxisOfRotation(glm::vec3);
	void setScalar(float);
	glm::mat4 getModel();
	void rotateObject(float);
};

