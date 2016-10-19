#include "AABB.h"
#include <math.h>

AABB::AABB()
{
}

AABB::AABB(Vector3 min, Vector3 max)
{
	this->minBound = min;
	this->maxBound = max;
}

AABB::~AABB()
{
}

float AABB::intersects(Ray r)
{
	Vector3 invDir = r.getInverseDirection();

	float txmin = (this->minBound[0] - r.getOrigin()[0]) * invDir[0];
	float txmax = (this->maxBound[0] - r.getOrigin()[0]) * invDir[0];
	float tymin = (this->minBound[1] - r.getOrigin()[1]) * invDir[1];
	float tymax = (this->maxBound[1] - r.getOrigin()[1]) * invDir[1];
	float tzmin = (this->minBound[2] - r.getOrigin()[2]) * invDir[2];
	float tzmax = (this->maxBound[2] - r.getOrigin()[2]) * invDir[2];

	//The statements are done in this order to try and cut down on runtime.
	if ((txmin < 0.0f && txmax < 0.0f) || (tymin < 0.0f && tymax < 0.0f) || (tzmin < 0.0f && tzmax < 0.0f)) return -2;
	float tmax = fminf(fminf(fmaxf(txmin, txmax), fmaxf(tymin, tymax)), fmaxf(tzmin, tzmax));

	if ((txmin < 0.0f || txmax < 0.0f) && (tymin < 0.0f || tymax < 0.0f) && (tzmin < 0.0f || tzmax < 0.0f)) return tmax;

	float tmin = fmaxf(fmaxf(fminf(txmin, txmax), fminf(tymin, tymax)), fminf(tzmin, tzmax));
	if (tmin > tmax)
	{
		return -1; //Could be any negative value.
	}
	return tmin;
}

Ray AABB::getNormal(Vector3 point)
{
	// TODO: Fix this
	// This currently isn't used in the code, and shouldn't really ever have to be.
	return Ray(Vector3(1, 1, 1), point);
}

