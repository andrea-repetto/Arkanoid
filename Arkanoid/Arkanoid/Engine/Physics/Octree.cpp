#include "pch.h"
#include "Octree.h"

using namespace Engine::Physics;

std::vector<PhysicsObject*>	Octree::AllPhysicsObjList;

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
		if(m_Children[idx] != nullptr)
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

void Octree::RegisterPhysicsObj(PhysicsObject& phyObj)
{
	AllPhysicsObjList.push_back(&phyObj);
}

void Octree::DeregisterPhysicsObj(PhysicsObject& phyObj)
{
	for (int idx = 0; idx < AllPhysicsObjList.size(); ++idx)
	{
		if (AllPhysicsObjList[idx] == &phyObj)
		{
			AllPhysicsObjList.erase(AllPhysicsObjList.begin() + idx);
			return;
		}
	}
}

void Octree::UpdateOctree(Octree& root)
{
	root.Clear();
	for (int idx = 0; idx < AllPhysicsObjList.size(); ++idx)
	{
		root.Insert(*AllPhysicsObjList[idx]);
	}
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

void Octree::Insert(PhysicsObject& phyObj)
{
	if (m_Children[0] != nullptr)
	{
		int index = GetIndex(phyObj);

		if (index != PARENT_NODE)
		{
			m_Children[index]->Insert(phyObj);
			return;
		}
	}

	m_PhysicsObjectList.push_back(&phyObj);

}

/**
* Determine in wich Octree child must be located the object.
* 
*/
int Octree::GetIndex(PhysicsObject& phyObj)
{
	BoundingBox bb = phyObj.GetBoundingBox();
	DirectX::XMFLOAT3 objPos = phyObj.GetGlobalPosition();

	/* Bounding Box world position */
	DirectX::XMFLOAT3 bbPos = DirectX::XMFLOAT3(
		objPos.x + bb.center.x,
		objPos.y + bb.center.y,
		objPos.z + bb.center.z
	);

	boolean isUpper = (bbPos.y + bb.scale.y / 2.0f) > m_BoundingBox.center.y &&
		(bbPos.y - bb.scale.y / 2.0f) > m_BoundingBox.center.y;

	boolean isDown = (bbPos.y + bb.scale.y / 2.0f) < m_BoundingBox.center.y &&
		(bbPos.y - bb.scale.y / 2.0f) < m_BoundingBox.center.y;

	boolean isRight = (bbPos.x + bb.scale.x / 2.0f) > m_BoundingBox.center.x &&
		(bbPos.x - bb.scale.x / 2.0f) > m_BoundingBox.center.x;

	boolean isLeft = (bbPos.x + bb.scale.x / 2.0f) < m_BoundingBox.center.x &&
		(bbPos.x - bb.scale.x / 2.0f) < m_BoundingBox.center.x;

	boolean isFront = (bbPos.z + bb.scale.z / 2.0f) > m_BoundingBox.center.z &&
		(bbPos.z - bb.scale.z / 2.0f) > m_BoundingBox.center.z;

	boolean isBack = (bbPos.z + bb.scale.z / 2.0f) < m_BoundingBox.center.z &&
		(bbPos.z - bb.scale.z / 2.0f) < m_BoundingBox.center.z;

	if (isUpper && isFront && isLeft) return FRONT_UPPER_LEFT;

	if (isUpper && isFront && isRight) return FRONT_UPPER_RIGHT;

	if (isDown && isFront && isLeft) return FRONT_DOWN_LEFT;

	if (isDown && isFront && isRight) return FRONT_DOWN_RIGHT;

	if (isUpper && isBack && isLeft) return BACK_UPPER_LEFT;

	if (isUpper && isBack && isRight) return BACK_UPPER_RIGHT;

	if (isDown && isBack && isLeft) return BACK_DOWN_LEFT;

	if (isDown && isBack && isRight) return BACK_DOWN_RIGHT;

	return PARENT_NODE;
}

