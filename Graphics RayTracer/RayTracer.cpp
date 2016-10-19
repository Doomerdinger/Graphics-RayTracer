//Hard code resolution for now
#define RES 1000
#define _USE_MATH_DEFINES

#include "RayTracer.h"
#include "GenVector.h"
#include "simplePNG.h"
#include "Buffer.h"
#include "objLoader.h"
#include "RayGenerator.h"
#include <math.h>
#include <vector>
#include "Primitive.h"
#include "Sphere.h"
#include "Triangle.h"
#include "BVHTree.h"

using namespace std;

//There has to be some amount of jitter to calculations, or things won't end up right.
#define JITTER_AMOUNT 0.0001f * (RES / 100)

// Author: Alec Tiefenthal

/// <summary>
/// Returns the Vector3 representtaion of an obj_vector.
/// </summary>
/// <param name="objVec">The object vector that you want to convert to a Vector3.</param>
/// <returns>A Vector3 representation of the objVec</returns>
Vector3 objToGenVec(obj_vector const* objVec)
{
	Vector3 v;
	v[0] = objVec->e[0];
	v[1] = objVec->e[1];
	v[2] = objVec->e[2];
	return v;
}

/// <summary>
/// Returns the Vector3 representtaion of an array of doubles.
/// </summary>
/// <param name="objVec">The array that you want to convert to a Vector3. Assumed to be of length 3.</param>
/// <returns>A Vector3 representation of the objVec</returns>
Vector3 arrayToGenVec(double arr[])
{
	Vector3 v;
	v[0] = arr[0];
	v[1] = arr[1];
	v[2] = arr[2];
	return v;
}

/// <summary>
/// Sets the values of a material to default values.
/// </summary>
/// <param name="mtl">The material whos values you want to change to the defualt values.</param>
void set_def_mat(obj_material* mtl)
{
	mtl->amb[0] = 0.2;
	mtl->amb[1] = 0.2;
	mtl->amb[2] = 0.2;
	mtl->diff[0] = 0.8;
	mtl->diff[1] = 0.8;
	mtl->diff[2] = 0.8;
	mtl->spec[0] = 1.0;
	mtl->spec[1] = 1.0;
	mtl->spec[2] = 1.0;
	mtl->reflect = 0.0;
	mtl->trans = 1;
	mtl->glossy = 98;
	mtl->shiny = 0;
	mtl->refract_index = 1;
	mtl->texture_filename[0] = '\0';
}


/// <summary>
/// Gets the base color of given primitive at the point that it is struck
/// by the given camRay. This is a computation of the color of the item,
/// and the summation of the light hitting it from all of the given point lights.
/// This function is what renders shadows and base lighting, no reflections.
/// </summary>
/// <param name="tree">The BVHTree used to check for Ray collisions with primitives.</param>
/// <param name="pointLights">The vector conaining all of the point lights.</param>
/// <param name="camRay">The ray currently being shot out from the camera.</param>
/// <param name="dist">The distance from the origin of the camRay to the primitive being hit.</param>
/// <param name="closest">The closest primitive that is struct by the camRay.</param>
/// <returns>The vector representing the color of the point hit.</returns>
Vector3 getBaseColor(BVHTree const& tree, std::vector<pointLight*> pointLights, Ray camRay, float dist, Primitive* closest)
{
	Vector3 colorVec = Vector3(0.0f, 0.0f, 0.0f);
	//for (int i = 0; i < objData->lightPointCount; i++)
	for (size_t i = 0; i < pointLights.size(); i++)
	{
		Vector3 hitPoint = camRay.getOrigin() + camRay.getDirection() * dist;
		Vector3 norm = closest->getNormal(hitPoint).getDirection();
		Vector3 toLight = pointLights[i]->pos - hitPoint;
		float distanceFromLight = toLight.length();
		toLight.normalize();

		Vector3 ambMat = arrayToGenVec(closest->getMaterial()->amb);
		Vector3 ambLight = arrayToGenVec(pointLights[i]->mat->amb);
		Vector3 amb = (ambMat * ambLight);

		Ray rayToLight = Ray(toLight, hitPoint + (JITTER_AMOUNT * norm));

		Primitive* tempClose;
		float hitDist = tree.intersects(rayToLight, tempClose);

		 //if the primitive is in shadow, render it accordingly
		if (hitDist > 0.0f && hitDist < distanceFromLight)
		{
			colorVec = colorVec + amb;
		}
		else
		{
			// not in shadow
			// surface diffuse reflectance * (tolight dot normal) * light intensity
			Vector3 difMat = arrayToGenVec(closest->getMaterial()->diff);
			Vector3 difLight = arrayToGenVec(pointLights[i]->mat->diff);
			Vector3 dif = difMat * fmaxf(toLight.dot(norm), 0.0f) * (difLight);

			Vector3 specMat = arrayToGenVec(closest->getMaterial()->spec);
			Vector3 specLight = arrayToGenVec(pointLights[i]->mat->spec);
			Vector3 specRefl = 2 * fmaxf(toLight.dot(norm), 0.0f) * norm - toLight;
			Vector3 toView = (camRay.getOrigin() - hitPoint).normalize();
			Vector3 spec = specMat * pow(fmaxf(toView.dot(specRefl), 0.0f), closest->getMaterial()->shiny) * (specLight);
			colorVec = colorVec + (amb + spec + dif);
		}
	}

	return colorVec;
}


/// <summary>
/// Calculates all colors.
/// </summary>
/// <param name="xRes">The resolution of the image in the x direction.</param>
/// <param name="yRes">The resolution of the image in the y direction.</param>
/// <param name="vectorBuffer">A buffer containing the vectors (unconverted color data) for the image. This is later used to convert to the actual RGB colors.</param>
/// <param name="camera">The Camera that holds data concerning the viewpoint.</param>
/// <param name="pointLights">The A vector of all of the point lights to be considered for the lighting calculation.</param>
/// <param name="tree">The BCHTree that contains all the primitives to be used for lighting collision pourposes..</param>
/// <returns>A float value representing the maximum output vector value. This is used later so that the values can be scaled down
/// between 0 and 1, then to 0-255.</returns>
float calcAllColors(int xRes, int yRes, Buffer<Vector3>& vectorBuffer, Camera const& camera, vector<pointLight*> const& pointLights, BVHTree const& tree)
{
	RayGenerator generator = RayGenerator(camera, xRes, yRes);

	float maxComp = 1.0f;
	for (int y = 0; y < yRes; y++)
	{
		for (int x = 0; x < xRes; x++)
		{
			Ray r = generator.getRay(x, y);
			Vector3 v = Vector3(0, 0, 0);

			Primitive* closest = nullptr;

			float minDist = tree.intersects(r, closest);

			if (minDist > 0.0f)
			{
				v = getBaseColor(tree, pointLights, r, minDist, closest);
				//TODO: More reflections.

				if (closest->getMaterial()->reflect > 0.0)
				{
					float reflAmt = (closest->getMaterial()->reflect);
					//Trace the ray back to see if it hits something. Reflect.
					Vector3 hitPoint = r.getOrigin() + r.getDirection() * minDist;
					Vector3 norm = closest->getNormal(hitPoint).getDirection();
					Vector3 refl = r.getDirection().reflect(norm);
					r = Ray(refl, hitPoint + (JITTER_AMOUNT * norm));

					closest = nullptr;
					minDist = tree.intersects(r, closest);

					if (minDist > 0.0f)
					{
						Vector3 reflCol = getBaseColor(tree, pointLights, r, minDist, closest) * reflAmt;
						v = v + reflCol;
					}
				}

				if (v[v.maxMagnitudeComponent()] > maxComp)
				{
					maxComp = fabs(v[v.maxMagnitudeComponent()]);
				}
			}
			vectorBuffer.at(x, y) = v;
		}
	}
	return maxComp;
}

int main(int argc, char** argv)
{
	int resX = RES;
	int resY = RES;
	if (argc == 5)
	{
		resX = atoi(argv[3]);
		resY = atoi(argv[4]);
	}
	else if (argc != 3)
	{
		printf("Invalid number of arguments.");
		printf("NumArgs: %d", argc);
		return -1;
	}
	//load camera data
	objLoader objData = objLoader();
	objData.load(argv[1]);

	vector<Primitive*> prims = vector<Primitive*>();
	prims.reserve(objData.sphereCount + objData.faceCount);

	obj_material* default_mat = new obj_material;
	set_def_mat(default_mat);

	// Create all the sphere objects from loaded data and add them to the vector of primitives.
	for (int i = 0; i < objData.sphereCount; i++)
	{
		obj_material* mat = default_mat;
		if (objData.sphereList[i]->material_index != -1)
			mat = objData.materialList[objData.sphereList[i]->material_index];
		Sphere* s = new Sphere(objToGenVec(objData.vertexList[objData.sphereList[i]->pos_index]),
		                       objToGenVec(objData.normalList[objData.sphereList[i]->up_normal_index]), mat);
		prims.push_back(s);
	}

	// Create all the triangle objects from loaded data and add them to the vector of primitives.
	for (int i = 0; i < objData.faceCount; i++)
	{
		if (objData.faceList[i]->vertex_count == 3) //Make sure it is a triangle
		{
			obj_material* mat = default_mat;
			if (objData.faceList[i]->material_index != -1)
				mat = objData.materialList[objData.faceList[i]->material_index];
			Triangle* t = new Triangle(objToGenVec(objData.vertexList[objData.faceList[i]->vertex_index[0]]),
			                           objToGenVec(objData.vertexList[objData.faceList[i]->vertex_index[1]]),
			                           objToGenVec(objData.vertexList[objData.faceList[i]->vertex_index[2]]), mat);
			prims.push_back(t);
		}
	}

	vector<pointLight*> pointLights = vector<pointLight*>();
	pointLights.reserve(objData.lightPointCount);
	// Create all the light objects from loaded data and add them to the vector of lights.
	for (int i = 0; i < objData.lightPointCount; i++)
	{
		pointLight* p = new pointLight(objToGenVec(objData.vertexList[objData.lightPointList[i]->pos_index]),
		                               objData.materialList[objData.lightPointList[i]->material_index]);
		pointLights.push_back(p);
	}

	// Begin creating the BVHTree
	BVHTree tree = BVHTree(prims.size());

	for (int i = 0; i < prims.size(); i++)
	{
		tree.addPrimToBounds(prims[i]);
	}
	tree.split();

	Vector3 look = objToGenVec(objData.vertexList[objData.camera->camera_look_point_index]);
	Vector3 pos = objToGenVec(objData.vertexList[objData.camera->camera_pos_index]);
	Vector3 up = objToGenVec(objData.normalList[objData.camera->camera_up_norm_index]);
	Buffer<Color> colorBuffer = Buffer<Color>(resX, resY);

	Buffer<Vector3> vectorBuffer = Buffer<Vector3>(resX, resY);

	float maxComp = calcAllColors(resX, resY, vectorBuffer, Camera(pos, look, up), pointLights, tree);
	printf("Max: %f", maxComp);
	for (int y = 0; y < resY; y++)
		for (int x = 0; x < resX; x++)
			colorBuffer.at(x, y) = (vectorBuffer.at(x, y) / maxComp) * 255.0f;

	simplePNG_write(argv[2], colorBuffer.getWidth(), colorBuffer.getHeight(), (unsigned char*)&colorBuffer.at(0, 0));

	// Technically I don't need to do this, as the OS should free all the memory
	// once the program terminates, but in case I make this not in main
	// later I'll free everything.
	for (size_t i = 0; i < prims.size(); i++)
	{
		delete prims[i];
	}
	for (size_t i = 0; i < pointLights.size(); i++)
	{
		delete pointLights[i];
	}
	delete default_mat;
	return 0;
}

