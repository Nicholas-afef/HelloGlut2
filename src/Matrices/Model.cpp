#include "Model.h"

Model::Model(){
	translate = glm::vec3(0.0f, 0.0f, 0.0f);
	rotAngle = 0.0f;
	axisOfRotation = glm::vec3(1.0f, 1.0f, 1.0f);
	scalar = 1;
}

void Model::setPosition(glm::vec3 pos){
	translate = pos;
}

void Model::setAngle(float theta) {
	rotAngle = theta;
}

void Model::setAxisOfRotation(glm::vec3 aor){
	axisOfRotation = aor;
}

void Model::setScalar(float s){
	scalar = s;
}

glm::mat4 Model::getModel(){
	glm::mat4 matrix(1.0f);
	matrix = glm::scale(matrix, glm::vec3(scalar));
	matrix = glm::rotate(matrix, glm::radians(rotAngle), axisOfRotation);
	matrix = glm::translate(matrix, translate);
	return matrix;
}

void Model::rotateObject(float theta) {
	if (rotAngle >= 360.0f) {
		rotAngle -= 360.0f;
	}
	if (rotAngle < 0.0f) {
		rotAngle += 360.0f;
	}
	rotAngle += theta;
}
