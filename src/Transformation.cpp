#include "Transformation.h"


Transformation::Transformation() {
	//all transformations start as the identity matrix
	tMatrix = glm::mat4(1.0f);
}

void Transformation::translate(glm::vec3 translator) {
	tMatrix = glm::translate(tMatrix, translator);
}

void Transformation::rotate(float angle, glm::vec3 axisOfRotation){
	glm::vec3 rVec = glm::normalize(axisOfRotation);
	angle = glm::pi<float>() * (angle / 180.0);
	tMatrix = glm::rotate(tMatrix, glm::radians(angle), rVec);
}

void Transformation::scale(float scalar) {
	tMatrix = glm::scale(tMatrix, glm::vec3(scalar));
}

glm::mat4 Transformation::getMatrix() {
	return tMatrix;
}