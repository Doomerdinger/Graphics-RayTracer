#pragma once
#include "Primitive.h"
/// <summary>
/// Defines a Triangle object.
/// </summary>
/// <seealso cref="Primitive" />
class Triangle :
	public Primitive
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Triangle"/> class.
	/// The min and max bounds are both (0,0,0) and the points a,b,c are set to
	/// (0, 1, 0), (1, 0, 0), (-1, 0, 0) respectively. Material is not set.
	/// </summary>
	Triangle();

	Triangle(Vector3 a, Vector3 b, Vector3 c, obj_material* mat);
	~Triangle();
	float intersects(Ray r) override;
	Ray getNormal(Vector3 point) override;

private:
	Vector3 a;
	Vector3 b;
	Vector3 c;
	Vector3 normal;
};