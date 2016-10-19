#include "Ray.h"


Ray::Ray(Vector3 dir, Vector3 orig)
{
	this->direction = dir.normalize();
	this->origin = orig;

	// The inverses of the direction are computed and stored, as division is
	// a costly operation and these inverses are used over and over, better to 
	// store them instead of recomputing them.
	this->inverseDir = 1.0f / this->direction;
}


Ray::~Ray()
{
}

Vector3 Ray::getDirection() const
{
	return this->direction;
}

Vector3 Ray::getOrigin() const
{
	return this->origin;
}

Vector3 Ray::getInverseDirection() const
{
	return this->inverseDir;
}

