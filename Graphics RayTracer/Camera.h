#pragma once
#include "GenVector.h"

/// <summary>
/// Defines the camera. This is where the scene is being looked at from.
/// </summary>
class Camera
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Camera"/> class.
	/// The position, lookPoint, and up vectors are initialized to 
	/// (0, 0, 0), (0, 0, 1), (0, 1, 0) respectively.
	/// </summary>
	Camera();

	/// <summary>
	/// Initializes a new instance of the <see cref="Camera"/> class.
	/// </summary>
	/// <param name="pos">The position of the camera.</param>
	/// <param name="look">The direction that the camera is looking.</param>
	/// <param name="up">The direction that is up, relative to the camera.</param>
	Camera(Vector3 pos, Vector3 look, Vector3 up);
	~Camera();

	/// <summary>
	/// Gets the point where this camera is looking.
	/// </summary>
	/// <returns>The look point of this camera</returns>
	Vector3 getLookPoint();

	/// <summary>
	/// Gets the look vector of this camera.
	/// </summary>
	/// <returns>The vector that represents the direction this camera is looking. Not nessecarily normalized.</returns>
	Vector3 getLookVec();

	/// <summary>
	/// Gets the position of this camera.
	/// </summary>
	/// <returns>The position vector (x,y,z) of this camera</returns>
	Vector3 getPosVec();

	/// <summary>
	/// Gets the up vector of this camera.
	/// </summary>
	/// <returns>The normalized directional vector indicating which direction is up relative to this camera.</returns>
	Vector3 getUpVec();

private:
	/// <summary>
	/// The look point that this camera is looking at.
	/// </summary>
	Vector3 lookPoint;

	/// <summary>
	/// The position that this camera is at.
	/// </summary>
	Vector3 position;

	/// <summary>
	/// The vector representing the direction that is up relative to this camera.
	/// </summary>
	Vector3 up;
};

