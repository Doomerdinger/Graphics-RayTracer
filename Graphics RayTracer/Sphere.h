#pragma once
#include "Primitive.h"
/// <summary>
/// Defines a sphere object.
/// </summary>
/// <seealso cref="Primitive" />
class Sphere :
	public Primitive
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Sphere"/> class.
	/// The center is set to (0,0,0) and the radius is set to 5.
	/// This constuctor shouldn't be used explicitly.
	/// </summary>
	Sphere();

	/// <summary>
	/// Initializes a new instance of the <see cref="Sphere"/> class, with the given properties.
	/// </summary>
	/// <param name="c">The coordinates of the center of the sphere (x,y,z) represented by a Vector3.</param>
	/// <param name="up">A Vector3 representing which direction is up.</param>
	/// <param name="mat">A pointer to the material of this sphere.</param>
	Sphere(Vector3 c, Vector3 up, obj_material* mat);
	~Sphere();

	/// <summary>
	/// The intersection of the sphere is based on the surface of the sphere 
	/// which is calculated from the center and radius.
	/// <seealso cref="Primitive.intersects" />
	float intersects(Ray r) override;

	/// <summary>
	/// The normal of the sphere is just the direction from the ray origin to
	/// the center of the sphere.
	/// <seealso cref="Primitive.getNormal" />
	Ray getNormal(Vector3 point) override;

private:
	/// <summary>
	/// The center of the sphere represented by a Vector3 (x,y,z).
	/// </summary>
	Vector3 center;

	/// <summary>
	/// The radius of the sphere.
	/// </summary>
	float radius;
};

