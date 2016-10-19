#include "RayGenerator.h"


RayGenerator::RayGenerator(Camera c, int resX, int resY)
{
	this->inverseResX = 1.0 / float(resX);
	this->inverseResY = 1.0 / float(resY);
	this->cam = c;
}

RayGenerator::~RayGenerator()
{
}

Ray RayGenerator::getRay(float x, float y) const
{
	Vector3 centerPoint = cam.getLookPoint();
	Vector3 upDir = cam.getUpVec();
	Vector3 rightDir = cam.getLookVec().normalize().cross(upDir);

	//l/r/t/b dist = length look vec?
	float xpercent = -cam.getLookVec().length() + (2.0f * cam.getLookVec().length()) * (x + 0.5f) * this->inverseResX;
	float ypercent = -cam.getLookVec().length() + (2.0f * cam.getLookVec().length()) * (y + 0.5f) * this->inverseResY;

	Vector3 rayPoint = centerPoint + (rightDir * xpercent) - (upDir * ypercent);
	return Ray((rayPoint - cam.getPosVec()).normalize(), cam.getPosVec());
}

