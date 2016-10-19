#include "Triangle.h"


Triangle::Triangle()
{
	this->a = Vector3(0, 1, 0);
	this->b = Vector3(1, 0, 0);
	this->c = Vector3(-1, 0, 0);
}

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c, obj_material* mat)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->normal = ((a - b).cross(b - c)).normalize();
	this->mat = mat;
	this->minBound = Vector3(
		fminf(fminf(this->a[0], this->b[0]), this->c[0]),
		fminf(fminf(this->a[1], this->b[1]), this->c[1]),
		fminf(fminf(this->a[2], this->b[2]), this->c[2])
	);
	this->maxBound = Vector3(
		fmaxf(fmaxf(this->a[0], this->b[0]), this->c[0]),
		fmaxf(fmaxf(this->a[1], this->b[1]), this->c[1]),
		fmaxf(fmaxf(this->a[2], this->b[2]), this->c[2])
	);
	//if (mat == NULL)
	//{
	//	printf("NULL");
	//}
	//printf(mat->name);
	//if (mat->texture_filename[0] == '\0')
	//{
	//	printf("NULL");
	//}
}

Triangle::~Triangle()
{
}

float Triangle::intersects(Ray r)
{
	// TODO : Do something if the ray doesn't hit the plane
	if ((r.getDirection().dot(this->normal)) != 0.0f) //Check to see if it intersects at all
	{
		float t = ((this->a - r.getOrigin()).dot(this->normal)) / (r.getDirection().dot(this->normal));
		//if (t >= 0.0f) //It hits the plane in front of the camera, check if triangle is hit.
		//{
		Vector3 hitpt = r.getOrigin() + (t * r.getDirection());
		if (((this->b - this->a).cross(hitpt - a)).dot(this->normal) > 0.0f)
		{
			//printf("Hit the tri!1");
			//printf("%.1f %.1f %.1f\n", hitpt.c[0], hitpt.c[1], hitpt.c[2]);
			//printf("%.1f \n", ((this->c - this->b).cross(hitpt - b)).dot(this->normal));
			if (((this->c - this->b).cross(hitpt - b)).dot(this->normal) > 0.0f)
			{
				//printf("Hit the tri!2");
				if (((this->a - this->c).cross(hitpt - c)).dot(this->normal) > 0.0f)
				{
					//printf("Hit the tri!3");
					return t;
				}
			}
		}
		//}
	}

	return -1;
}

Ray Triangle::getNormal(Vector3 point)
{
	return Ray((this->a - this->c).cross(this->b - this->c).normalize(), point);
	//return Ray((this->c.cross(this->a)).normalize(), point);
}

