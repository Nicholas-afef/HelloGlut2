#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Perspective{
private:
	float angle;
	float nearPlane;
	float farPlane;
public:
	Perspective();
	void setAngle(float);
	void setNear(float);
	void setFar(float);
	glm::mat4 getPerspective(float);
	void changeAngle(float);
	void moveNearPlane(float);
	void moveFarPlane(float);
};

