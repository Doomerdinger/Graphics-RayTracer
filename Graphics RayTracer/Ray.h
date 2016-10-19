#pragma once
#include "GenVector.h"
/// <summary>
/// Defines the Ray object, which is just a ray in 3d space. It has an origin and a direction. No magnitude.
/// </summary>
class Ray
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Ray"/> class.
	/// </summary>
	/// <param name="dir">The direction (x,y,z) of this Ray. Does not have to be normalized.</param>
	/// <param name="orig">The origin (x,y,z) of this Ray, its starting point.</param>
	Ray(Vector3 dir, Vector3 orig);
	~Ray();
	
	/// <summary>
	/// Gets the directional vector of this ray. It is normalized.
	/// </summary>
	/// <returns>The normalized directional vector of this ray.</returns>
	Vector3 getDirection() const;

	/// <summary>
	/// Gets the origin vector of this ray.
	/// </summary>
	/// <returns>The origin vector of this ray.</returns>
	Vector3 getOrigin() const;

	/// <summary>
	/// Gets the inverse of the directional vector of this ray.
	/// This value is stored to speed up AABB intersection calculations, as division is a costly operator.
	/// </summary>
	/// <returns>The inverse of the directional vector of this ray.</returns>
	Vector3 getInverseDirection() const;

private:
	/// <summary>
	/// The vector that indicates the direction of this ray. Should be normalized.
	/// </summary>
	Vector3 direction;

	/// <summary>
	/// The origin of this ray.
	/// </summary>
	Vector3 origin;

	/// <summary>
	/// The inverse of the directional vector of this ray.
	/// This value is stored to speed up AABB intersection calculations, as division is a costly operator,
	/// and is needed multiple times for the same ray.
	/// </summary>
	Vector3 inverseDir;
};

