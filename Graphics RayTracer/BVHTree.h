#pragma once
#include "Primitive.h"
#include <vector>

/// <summary>
/// Defines a BVHTree (bounding volume hierarchy tree). This is used to structure the
/// primitive data, primarily to make intersection checking faster.
/// </summary>
class BVHTree
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="BVHTree"/> class.
	/// </summary>
	/// <param name="initialPrimSize">Amount of memory to reserve in the initial primitive std::vector.</param>
	BVHTree(int initialPrimSize);
	~BVHTree();

	/// <summary>
	/// Adds the given prim to this tree node, and reevaluates the bounds of this tree node.
	/// </summary>
	/// <param name="p">The primitive to be added.</param>
	void addPrimToBounds(Primitive* p);

	/// <summary>
	/// Splits this node into two sub nodes, with the primitives
	/// being put in either the left or right sub node. If every primitive
	/// goes to a single sub node, one is removed and given to the other sub node.
	/// No data is removed from this node, it is just constructing its children.
	/// </summary>
	void split();

	/// <summary>
	/// Checks to see if the given Ray intersects this node. If it does, then it checks to see
	/// if the Ray intesects either its left or right nodes (if any), recursively, until a node is found
	/// with only one primitive, at which point the primitive's intersects function is called and
	/// that result is returned. Additionally, Primitive pointer passed in is set to the
	/// of the the primitive that was hit.
	/// </summary>
	/// <param name="r">The ray that will be checked for intersection.</param>
	/// <param name="p">A pointer to a primitive. If one is hit, this pointer will be directed at it.</param>
	/// <returns>Distance to the interesected primitive. Negative value if no intersection is found.</returns>
	float intersects(Ray r, Primitive*& p) const;

	/// <summary>
	/// Gets the minimum bounds of this BVHTree node. 
	/// </summary>
	/// <returns>Vctor3 representing the minimum bounds (x,y,z)</returns>
	Vector3 getMinBound() const;

	/// <summary>
	/// Gets the maximum bounds of this BVHTree node. 
	/// </summary>
	/// <returns>Vctor3 representing the maximum bounds (x,y,z)</returns>
	Vector3 getMaxBound() const;


	/// <summary>
	/// Gets the size of this BVHTree node and its children, recursivly. 1 for every node.
	/// </summary>
	/// <returns>Size of this tree. (1 + number of subnodes)</returns>
	int getSize() const;

private:
	BVHTree* leftNode;
	BVHTree* rightNode;
	Vector3 minBound;
	Vector3 maxBound;
	std::vector<Primitive*> prims;
};