#include "View.h"

View::View(){
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	pointVector = glm::vec3(1.0, 0.0, 0.0);
	upVector = glm::vec3(0.0, 1.0, 0.0);
	pitch = 0.0f;
	yaw = 0.0f;
	sensitivity = 0.1f;
}

glm::vec3 View::getPosition() {
	return position;
}

void View::setCamera(glm::vec3 const& pos, glm::vec3 const& point, glm::vec3 const& up){
	position = pos;
	pointVector = point;
	upVector = up;
}

void View::setPosition(glm::vec3 const& pos){
	position = pos;
}

void View::setPointVector(glm::vec3 const& point){
	pointVector = point;
}

void View::setUpVector(glm::vec3 const& up){
	upVector = up;
}

glm::mat4 View::getView(){
	//position = position in 3d-space
	//point vector is a normalized vector pointing in a direction at our position
	return glm::lookAt(position, (position + pointVector), upVector);
}

void View::calcDirections(float xOffset, float yOffset) {
	pitch += yOffset * sensitivity;
	yaw += xOffset * sensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	if (yaw >= 360) {
		yaw -= 360;
	}
	if (yaw < 0) {
		yaw += 360;
	}
	
	pointVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	pointVector.y = sin(glm::radians(pitch));
	pointVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//upVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch + 90));
	//upVector.y = sin(glm::radians(pitch + 90));
	//upVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch + 90));
	pointVector = glm::normalize(pointVector);
	//upVector = glm::normalize(upVector);
}

void View::moveForward(float speed) {
	position.x += pointVector.x * speed;
	position.z += pointVector.z * speed;
}

void View::moveBackward(float speed){
	position.x -= pointVector.x * speed;
	position.z -= pointVector.z * speed;
}

void View::moveLeft(float speed){
	glm::vec3 orthPoint = cross(pointVector, upVector);
	position.x -= orthPoint.x * speed;
	position.z -= orthPoint.z * speed;
}

void View::moveRight(float speed){
	glm::vec3 orthPoint = cross(pointVector, upVector);
	position.x += orthPoint.x * speed;
	position.z += orthPoint.z * speed;
}

void View::moveUp(float speed) {
	position.y += speed;
}

void View::moveDown(float speed) {
	position.y -= speed;
}

