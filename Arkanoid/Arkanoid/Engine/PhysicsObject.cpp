#include "pch.h"
#include "PhysicsObject.h"
#include "Physics\Octree.h"

using namespace Engine::Physics;

//std::vector<PhysicsObject*> PhysicsObject::PhysicsObjectsList;

PhysicsObject::PhysicsObject()
	: GameObject()
	, m_velocity(0,0,0)
	, m_CollisionDetection(false)
{
	Octree::RegisterPhysicsObj(*this);
}


PhysicsObject::~PhysicsObject()
{
	Octree::DeregisterPhysicsObj(*this);
}


void PhysicsObject::doStart()
{

}

void PhysicsObject::doUpdate(DX::StepTimer const& timer)
{
	DirectX::XMFLOAT3 pos = GetLocalPosition();

	if (m_CollisionDetection)
	{
		CollisionDetection();
	}

	float elapsedSeconds = static_cast<float>(timer.GetElapsedSeconds());

	pos.x += m_velocity.x * elapsedSeconds;
	pos.y += m_velocity.y * elapsedSeconds;
	pos.z += m_velocity.z * elapsedSeconds;

	SetLocalPosition(pos);


}

void PhysicsObject::doRender()
{

}


void PhysicsObject::CollisionDetection()
{

}


void PhysicsObject::CollisionTest(PhysicsObject& other)
{
	DirectX::XMFLOAT3 pos = GetLocalPosition();
	BoundingBox myBB = GetWorldBoundingBox();
	BoundingBox othBB = other.GetWorldBoundingBox();

	bool isNotOverlappingOnXAxis = 
		((myBB.center.x - myBB.scale.x / 2.0f) < (othBB.center.x - othBB.scale.x / 2.0f) && 
		(myBB.center.x + myBB.scale.x / 2.0f) < (othBB.center.x - othBB.scale.x / 2.0f)) ||
		((myBB.center.x - myBB.scale.x / 2.0f) > (othBB.center.x + othBB.scale.x / 2.0f) &&
		(myBB.center.x + myBB.scale.x / 2.0f) > (othBB.center.x + othBB.scale.x / 2.0f));

	bool isNotOverlappingOnYAxis =
		((myBB.center.y - myBB.scale.y / 2.0f) < (othBB.center.y - othBB.scale.y / 2.0f) &&
		(myBB.center.y + myBB.scale.y / 2.0f) < (othBB.center.y - othBB.scale.y / 2.0f)) ||
			((myBB.center.y - myBB.scale.y / 2.0f) > (othBB.center.y + othBB.scale.y / 2.0f) &&
		(myBB.center.y + myBB.scale.y / 2.0f) > (othBB.center.y + othBB.scale.y / 2.0f));

	bool isNotOverlappingOnZAxis =
		((myBB.center.z - myBB.scale.z / 2.0f) < (othBB.center.z - othBB.scale.z / 2.0f) &&
		(myBB.center.z + myBB.scale.z / 2.0f) < (othBB.center.z - othBB.scale.z / 2.0f)) ||
			((myBB.center.z - myBB.scale.z / 2.0f) > (othBB.center.z + othBB.scale.z / 2.0f) &&
		(myBB.center.z + myBB.scale.z / 2.0f) > (othBB.center.z + othBB.scale.z / 2.0f));


	if (!isNotOverlappingOnXAxis && !isNotOverlappingOnYAxis && !isNotOverlappingOnZAxis)
	{
		//Collision detected
		m_velocity = DirectX::XMFLOAT3(
			m_velocity.x,
			m_velocity.y*(-1.0f),
			m_velocity.z
		);
	}
}


BoundingBox PhysicsObject::GetWorldBoundingBox() const
{
	DirectX::XMFLOAT3 globalScale(1.0f, 1.0f, 1.0f);
	DirectX::XMFLOAT3 globalPosition = GetGlobalPosition();

	BoundingBox result = m_BoundingBox;
	if (m_parent)
	{
		globalScale = m_parent->GetGlobalScale();
		//globalPosition = m_parent->GetGlobalPosition();
	}

	result.scale.x *= globalScale.x;
	result.scale.y *= globalScale.y;
	result.scale.z *= globalScale.z;

	result.center.x += globalPosition.x;
	result.center.y += globalPosition.y;
	result.center.z += globalPosition.z;

	return result;
}
/**
void PhysicsObject::NotyfyCollisionDetected(PhysicsObject& other)
{
	//provvisorio
	m_velocity = DirectX::XMFLOAT3(
		m_velocity.x,
		m_velocity.y*(-1.0f),
		m_velocity.z
	);
}
*/