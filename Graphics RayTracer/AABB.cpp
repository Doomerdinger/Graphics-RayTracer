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
	//float xInver = 1.0 / r.getDirection()[0];
	//float yInver = 1.0 / r.getDirection()[1];
	//float zInver = 1.0 / r.getDirection()[2];
	Vector3 invDir = r.getInverseDirection();

	float txmin = (this->minBound[0] - r.getOrigin()[0]) * invDir[0];
	float txmax = (this->maxBound[0] - r.getOrigin()[0]) * invDir[0];
	float tymin = (this->minBound[1] - r.getOrigin()[1]) * invDir[1];
	float tymax = (this->maxBound[1] - r.getOrigin()[1]) * invDir[1];
	float tzmin = (this->minBound[2] - r.getOrigin()[2]) * invDir[2];
	float tzmax = (this->maxBound[2] - r.getOrigin()[2]) * invDir[2];

	//float txmin = (this->min[0] - r.getOrigin()[0]) * xInver;
	//float txmax = (this->max[0] - r.getOrigin()[0]) * xInver;
	//float tymin = (this->min[1] - r.getOrigin()[1]) * yInver;
	//float tymax = (this->max[1] - r.getOrigin()[1]) * yInver;
	//float tzmin = (this->min[2] - r.getOrigin()[2]) * zInver;
	//float tzmax = (this->max[2] - r.getOrigin()[2]) * zInver;

	//float tmin = fmaxf(fmaxf(fminf(txmin, txmax), fminf(tymin, tymax)), fminf(tzmin, tzmax));

	if ((txmin < 0.0f && txmax < 0.0f) || (tymin < 0.0f && tymax < 0.0f) || (tzmin < 0.0f && tzmax < 0.0f)) return -2;
	float tmax = fminf(fminf(fmaxf(txmin, txmax), fmaxf(tymin, tymax)), fmaxf(tzmin, tzmax));

	//float tmax = fmaxf(txmin, txmax);
	//if (tmax < 0) return -2;
	//tmax = fminf(tmax, fmaxf(tymin, tymax));
	//if (tmax < 0) return -2;
	//tmax = fminf(tmax, fmaxf(tzmin, tzmax));
	//if (tmax < 0) return -2;

	//float tmin = fminf(txmin, txmax);
	//if (tmin > tmax) return -3;
	//if (tmin < 0) return tmax;
	//tmin = fmaxf(tmin, fminf(tymin, tymax));
	//if (tmin > tmax) return -3;
	//if (tmin < 0) return tmax;
	//tmin = fmaxf(tmin, fminf(tzmin, tzmax));
	//if (tmin > tmax) return -3;
	//if (tmin < 0) return tmax;
	//return tmin;

	//if(tmax < 0)
	//{
	//	return -2;
	//}
	if ((txmin < 0.0f || txmax < 0.0f) && (tymin < 0.0f || tymax < 0.0f) && (tzmin < 0.0f || tzmax < 0.0f)) return tmax;
	//if (tmin < 0)
	//{
	//	return tmax;
	//}
	float tmin = fmaxf(fmaxf(fminf(txmin, txmax), fminf(tymin, tymax)), fminf(tzmin, tzmax));
	if (tmin > tmax)
	{
		return -3;
	}
	return tmin;
}

Ray AABB::getNormal(Vector3 point)
{
	//TODO Make this right.
	return Ray(Vector3(1, 1, 1), point);
}

