#include "Sphere.h"
#include <math.h>

Sphere::Sphere()
{
	this->center = Vector3(0, 0, 0);
	this->radius = 5;
}

Sphere::Sphere(Vector3 c, Vector3 up, obj_material* mat)
{
	this->center = c;
	this->radius = up.length();
	this->mat = mat;
	this->minBound = Vector3(-1 * this->radius, -1 * this->radius, -1 * this->radius);
	this->maxBound = Vector3(this->radius, this->radius, this->radius);
}

Sphere::~Sphere()
{
}

float Sphere::intersects(Ray r)
{
	Vector3 d = r.getDirection();
	Vector3 e = r.getOrigin();
	//TODO: Should this be an int, rounding is fine?
	float t = ((d.dot(e - this->center)) * (d.dot(e - this->center))) -
		(d.dot(d)) * ((e - this->center).dot(e - this->center) - (this->radius * this->radius));
	//sqrt(pow(d * (e - this->center), 2) -)

	//float a = (r.getDirection().dot(r.getDirection()));
	//float b = 2 * r.getDirection().dot(r.getOrigin() - this->center);
	//float c = (r.getOrigin() - this->center).dot(r.getOrigin() - this->center) - (this->radius * this->radius);

	//float discrim = (b * b - 4 * a * c);

	//if (discrim < 0.0f) //Doesn't intersect
	//{
	//	printf("NO");
	//	return -1;
	//}
	//if ((-1 * b - discrim) / (2 * a) < 0.0f)
	//	return (-1 * b + discrim) / (2 * a) < 0.0f;
	//return (-1 * b - discrim) / (2 * a) < 0.0f;

	if (t < 0.0f) //Doesn't intersect.
		return -1;
	float quadMinus = (-1 * (d.dot(e - this->center)) - sqrt(t)) / (d.dot(d));
	if (quadMinus < 0.0)
		return (-1 * (d.dot(e - this->center)) + sqrt(t)) / (d.dot(d));
	return quadMinus;


	//if (t > 0.0f) //Intersects once.
	//return -1 * (d.dot(e - this->center);
	// TODO: Do something with double intersection
	//if (t == 0.0f) //Intersects twice.
}

Ray Sphere::getNormal(Vector3 point)
{
	return Ray((point - this->center).normalize(), point);
}

