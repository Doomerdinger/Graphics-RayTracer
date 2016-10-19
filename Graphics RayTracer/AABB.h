#pragma once
#include "Primitive.h"
/// <summary>
/// Defines an AABB (Axis Aligned Bounding Box).
/// </summary>
/// <seealso cref="Primitive" />
class AABB :
	public Primitive
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="AABB"/> class.
	/// The min and max bounds are both (0,0,0). Mat is not set.
	/// This constuctor shouldn't be used explicitly.
	/// </summary>
	AABB();

	/// <summary>
	/// Initializes a new instance of the <see cref="AABB"/> class.
	/// </summary>
	/// <param name="min">The minimum bound for this AABB.</param>
	/// <param name="max">The maximum bound for this AABB.</param>
	AABB(Vector3 min, Vector3 max);
	~AABB();

	/// <summary>
	/// See <see cref="Primitive.intersects"/>
	/// </summary>
	float intersects(Ray r) override;

	/// <summary>
	/// See <see cref="Primitive.getNormal"/>
	/// </summary>
	Ray getNormal(Vector3 point) override;
};