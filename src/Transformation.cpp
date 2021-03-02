#include "Transformation.h"


Transformation::Transformation() {
	//all transformations start as the identity matrix
	tMatrix = glm::mat4(1.0f);
}

void Transformation::translate(float tX, float tY, float tZ) {
	tMatrix = glm::translate(tMatrix, glm::vec3(tX, tY, tZ));
}

void Transformation::rotate(float angle, float xVec, float yVec, float zVec){
	glm::vec3 rVec = glm::normalize(glm::vec3(xVec, yVec, zVec));
	angle = glm::pi<float>() * (angle / 180);
	tMatrix = glm::rotate(tMatrix, glm::radians(angle), rVec);
}

void Transformation::scale(float scalar) {
	tMatrix = glm::scale(tMatrix, glm::vec3(scalar));
}

glm::mat4 Transformation::getMatrix() {
	return tMatrix;
}