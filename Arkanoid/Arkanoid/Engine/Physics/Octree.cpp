#include "pch.h"
#include "Octree.h"

using namespace Engine::Physics;

Octree::Octree(BoundingBox boundingBox)
	: m_BoundingBox(boundingBox)
{
	for (int idx = 0; idx < 8; ++idx)
	{
		m_Children[idx] = nullptr;
	}
}


Octree::~Octree()
{
	for (int idx = 0; idx < 8; ++idx)
	{
		delete m_Children[idx];
	}
}


void Octree::Clear()
{
	m_PhysicsObjectList.clear();

	for (int idx = 0; idx < 8; ++idx)
	{
		m_Children[idx]->Clear();
	}
}


//static
Octree* Octree::BuildOctree(BoundingBox max, BoundingBox min)
{
	//TODO add assert

	Octree* root = new Octree(max);

	RecursiveCreateChildren(*root, min);

	return root;
}

void Octree::RecursiveCreateChildren(Octree& parent, BoundingBox min)
{
	/* half parent scale sizes */
	DirectX::XMFLOAT3 halfPS = DirectX::XMFLOAT3(
		parent.m_BoundingBox.scale.x / 2.0f,
		parent.m_BoundingBox.scale.y / 2.0f,
		parent.m_BoundingBox.scale.z / 2.0f
	);

	if (halfPS.x > min.scale.x)
	{
		DirectX::XMFLOAT3 pC = parent.m_BoundingBox.center;

		parent.m_Children[FRONT_UPPER_LEFT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x - halfPS.x, pC.y + halfPS.y, pC.z + halfPS.z), halfPS));
		parent.m_Children[FRONT_UPPER_RIGHT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x + halfPS.x, pC.y + halfPS.y, pC.z + halfPS.z), halfPS));
		parent.m_Children[FRONT_DOWN_LEFT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x - halfPS.x, pC.y - halfPS.y, pC.z + halfPS.z), halfPS));
		parent.m_Children[FRONT_DOWN_RIGHT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x + halfPS.x, pC.y - halfPS.y, pC.z + halfPS.z), halfPS));
		parent.m_Children[BACK_UPPER_LEFT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x - halfPS.x, pC.y + halfPS.y, pC.z - halfPS.z), halfPS));
		parent.m_Children[BACK_UPPER_RIGHT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x + halfPS.x, pC.y + halfPS.y, pC.z - halfPS.z), halfPS));
		parent.m_Children[BACK_DOWN_LEFT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x - halfPS.x, pC.y - halfPS.y, pC.z - halfPS.z), halfPS));
		parent.m_Children[BACK_DOWN_RIGHT] = new Octree(BoundingBox(DirectX::XMFLOAT3(pC.x + halfPS.x, pC.y - halfPS.y, pC.z - halfPS.z), halfPS));

		/* Recurions call */
		RecursiveCreateChildren(*parent.m_Children[FRONT_UPPER_LEFT], min);
		RecursiveCreateChildren(*parent.m_Children[FRONT_UPPER_RIGHT], min);
		RecursiveCreateChildren(*parent.m_Children[FRONT_DOWN_LEFT], min);
		RecursiveCreateChildren(*parent.m_Children[FRONT_DOWN_RIGHT], min);
		RecursiveCreateChildren(*parent.m_Children[BACK_UPPER_LEFT], min);
		RecursiveCreateChildren(*parent.m_Children[BACK_UPPER_RIGHT], min);
		RecursiveCreateChildren(*parent.m_Children[BACK_DOWN_LEFT], min);
		RecursiveCreateChildren(*parent.m_Children[BACK_DOWN_RIGHT], min);
	}
	
}

