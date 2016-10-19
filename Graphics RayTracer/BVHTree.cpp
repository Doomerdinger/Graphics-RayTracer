#include "BVHTree.h"
#include "AABB.h"


BVHTree::BVHTree(int initialPrimSize): leftNode(nullptr), rightNode(nullptr)
{
	this->prims = std::vector<Primitive*>();
	this->prims.reserve(initialPrimSize);
}

BVHTree::~BVHTree()
{
	if (this->rightNode != nullptr)
		delete(this->rightNode);
	if (this->leftNode != nullptr)
		delete(this->leftNode);
}

void BVHTree::addPrimToBounds(Primitive* p)
{
	if (this->prims.size() == 0)
	{
		this->maxBound = p->getMaxBound();
		this->minBound = p->getMinBound();
	}
	else
	{
		Vector3 pMaxBounds = p->getMaxBound();
		Vector3 pMinBounds = p->getMinBound();

		this->maxBound[0] = fmaxf(this->maxBound[0], pMaxBounds[0]);
		this->maxBound[1] = fmaxf(this->maxBound[1], pMaxBounds[1]);
		this->maxBound[2] = fmaxf(this->maxBound[2], pMaxBounds[2]);

		this->minBound[0] = fminf(this->minBound[0], pMinBounds[0]);
		this->minBound[1] = fminf(this->minBound[1], pMinBounds[1]);
		this->minBound[2] = fminf(this->minBound[2], pMinBounds[2]);
	}
	this->prims.push_back(p);
}

void BVHTree::split()
{
	if (this->prims.size() <= 1)
	{
		return;
	}

	Vector3 boundDist = this->maxBound - this->minBound;
	int maxComp = boundDist.maxComponent();
	Vector3 average = (this->maxBound + this->minBound) / 2.0f;

	std::vector<Primitive*> leftvec;
	std::vector<Primitive*> rightvec;

	for (size_t i = 0; i < this->prims.size(); i++)
	{
		Vector3 primAvg = (prims[i]->getMaxBound() + prims[i]->getMinBound()) / 2.0f;
		if (primAvg[maxComp] < average[maxComp])
		{
			leftvec.push_back(prims[i]);
		}
		else
		{
			rightvec.push_back(prims[i]);
		}
	}

	if (leftvec.size() == this->prims.size())
	{
		rightvec.push_back(leftvec.back());
		leftvec.pop_back();
	}
	else if (rightvec.size() == this->prims.size())
	{
		leftvec.push_back(rightvec.back());
		rightvec.pop_back();
	}

	this->rightNode = new BVHTree(this->prims.size());
	this->leftNode = new BVHTree(this->prims.size());

	for (size_t i = 0; i < rightvec.size(); i++)
		this->rightNode->addPrimToBounds(rightvec[i]);

	for (size_t i = 0; i < leftvec.size(); i++)
		this->leftNode->addPrimToBounds(leftvec[i]);

	this->rightNode->split();
	this->leftNode->split();
}

float BVHTree::intersects(Ray r, Primitive*& p) const
{
	if (this->prims.size() == 0)
		return -1.0f;

	// If this node only has 1 primitive, then check if the ray intersects it.
	if (this->prims.size() == 1)
	{
		float hit = this->prims[0]->intersects(r);
		if (hit > 0.0f)
		{
			p = this->prims[0];
			return hit;
		}
		else
		{
			return -1.0f;
		}
	}

	//Check to see if the ray intersects the bounding box defined by this BVHTree node
	AABB bounds = AABB(this->minBound, this->maxBound); // TODO: Could store this, not sure its worth it.

	float dist = bounds.intersects(r);

	// Doesn't hit
	if (dist <= 0.0f)
	{
		return -4;
	}

	// Hits, so now we have to 
	Primitive* tempLeft = nullptr;
	Primitive* tempRight = nullptr;


	float lft = this->leftNode->intersects(r, tempLeft);
	float rght = this->rightNode->intersects(r, tempRight);

	// Check various collision cases.
	if (lft > 0.0f && rght > 0.0f)
	{
		if (lft < rght)
		{
			p = tempLeft;
			return lft;
		}
		else
		{
			p = tempRight;
			return rght;
		}
	}
	else if (lft > 0.0f)
	{
		p = tempLeft;
		return lft;
	}
	else if (rght > 0.0f)
	{
		p = tempRight;
		return rght;
	}
	else
	{
		//Was in the overall box, but not in the leftNode or rightNode.
		//Its a miss, return -1
		return -1.0f;
	}
}

Vector3 BVHTree::getMinBound() const
{
	return this->minBound;
}

Vector3 BVHTree::getMaxBound() const
{
	return this->maxBound;
}

int BVHTree::getSize() const
{
	if (this->prims.size() == 1)
	{
		return 1;
	}

	return (1 + this->leftNode->getSize() + this->rightNode->getSize());
}

