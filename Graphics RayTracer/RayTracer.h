#pragma
#include "obj_parser.h"
#include "GenVector.h"


/// <summary>
/// A structure to hold information about a pointLight.
/// </summary>
typedef struct pointLight
{
	obj_material* mat;
	Vector3 pos;
	pointLight(Vector3 p, obj_material* mt)
	{
		this->mat = mt;
		this->pos = p;
	};
};