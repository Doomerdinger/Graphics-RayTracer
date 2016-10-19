#pragma once
#include "Ray.h"
#include "obj_parser.h"

class Primitive
{
protected:
	/// <summary>
	/// The material of this primitive. It is a pointer because many primitives
	/// may use the same material, so a pointer allows us to only need one copy.
	/// </summary>
	obj_material* mat;


	/// <summary>
	/// Vector representing the minimum x,y,z values that this primitive occupies.
	///	Has a defualt value of (0,0,0)
	/// </summary>
	Vector3 minBound = Vector3(0, 0, 0);

	/// <summary>
	/// Vector representing the maximum x,y,z values that this primitive occupies.
	///	Has a defualt value of (0,0,0)
	/// </summary>
	Vector3 maxBound = Vector3(0,0,0);
public:
	//Primitive();
	//~Primitive();
	/// Gets the normal Ray of this primitive. Should be normalized.

	/// <summary>
	/// Gets a directional Ray with an origin at the specified point, and a direction which makes
	/// the ray normal to the surface of this primitive.
	/// </summary>
	/// <param name="point">The origin point of the Ray.</param>
	/// <returns>The ray representing the normal from the given point to his primitive.</returns>
	virtual Ray getNormal(Vector3 point) = 0;

	/// <summary>
	/// Checks to see if the given ray intersects this primitive.
	/// </summary>
	/// <param name="r">The ray that we want being checked to see if it intersects with this primitive</param>
	/// <returns>
	/// If there is an intersection, then the (notw: this is positive) distance from the origin of the
	/// given ray and the intersection is returned. Otherwise a negative value is returned.
	/// </returns>
	virtual float intersects(Ray r) = 0;

	/// <summary>
	/// Gets the minimum bound of this primitive.
	/// </summary>
	/// <returns>A Vector3 representing the minimum bound of this primitive</returns>
	Vector3 getMinBound() const
	{
		return this->minBound;
	}

	/// <summary>
	/// Gets the maximum bound of this primitive.
	/// </summary>
	/// <returns>A Vector3 representing the maximum bound of this primitive</returns>
	Vector3 getMaxBound() const
	{
		return this->maxBound;
	}

	/// <summary>
	/// Gets a pointer to the material of this primitive.
	/// </summary>
	/// <returns>A pointer to the material of this primitive</returns>
	obj_material* getMaterial() const
	{
		return this->mat;
	}
};