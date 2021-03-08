#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class View{
private:
	glm::vec3 position;
	glm::vec3 pointVector;
	glm::vec3 upVector;
	float pitch, yaw;
	float sensitivity;
public:
	View();
	void setCamera(glm::vec3 const&, glm::vec3 const&, glm::vec3 const&);
	void setPosition(glm::vec3 const&);
	void setPointVector(glm::vec3 const&);
	void setUpVector(glm::vec3 const&);
	glm::mat4 getView();
	void calcDirections(float, float);
	void moveForward(float speed);
	void moveBackward(float speed);
	void moveLeft(float speed);
	void moveRight(float speed);
	void moveUp(float speed);
	void moveDown(float speed);
};

