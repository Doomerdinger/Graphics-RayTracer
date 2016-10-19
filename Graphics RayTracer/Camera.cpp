#include "Camera.h"

Camera::Camera()
{
	this->position = Vector3(0, 0, 0);
	this->lookPoint = Vector3(0, 0, 1);
	this->up = Vector3(0, 1, 0);
}

Camera::Camera(Vector3 pos, Vector3 look, Vector3 up)
{
	this->position = pos;
	this->lookPoint = look;
	this->up = up.normalize();
}

Camera::~Camera()
{
}

Vector3 Camera::getLookPoint() const
{
	return this->lookPoint;
}

Vector3 Camera::getLookVec() const
{
	return (this->lookPoint - this->position);
}

Vector3 Camera::getPosVec() const
{
	return this->position;
}

Vector3 Camera::getUpVec() const
{
	return this->up;
}

