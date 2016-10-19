#pragma once
#include "Camera.h"
#include "Ray.h"
/// <summary>
/// A class that generates rays from a given camera to a given point
/// in a specified "field" that is set in front of the camera.
/// </summary>
class RayGenerator
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="RayGenerator"/> class.
	/// </summary>
	/// <param name="c">The camera this generator will utilize.</param>
	/// <param name="resX">The x resolution of the viewing plane.</param>
	/// <param name="resY">The y resolution of the viewing plane.</param>
	RayGenerator(Camera c, int resX, int resY);
	~RayGenerator();

	/// <summary>
	/// Gets the ray at the given x,y coord in the viewing plane, from the camera.
	/// </summary>
	/// <param name="x">The desired x coord.</param>
	/// <param name="y">The desired y coord.</param>
	/// <returns></returns>
	Ray getRay(float x, float y);

private:
	/// <summary>
	/// The camera that this generator utilizes.
	/// </summary>
	Camera cam;

	/// <summary>
	/// The inverse of the x resolution. It is better to store this, as division is costly
	/// and we only ever use the resolution of x to divide.
	/// </summary>
	float inverseResX;

	/// <summary>
	/// The inverse of the y resolution. It is better to store this, as division is costly
	/// and we only ever use the resolution of y to divide.
	/// </summary>
	float inverseResY;
};

