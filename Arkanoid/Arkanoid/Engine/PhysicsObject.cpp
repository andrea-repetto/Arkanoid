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

	pos.x += m_velocity.x * timer.GetElapsedSeconds();
	pos.y += m_velocity.y * timer.GetElapsedSeconds();
	pos.z += m_velocity.z * timer.GetElapsedSeconds();

	SetLocalPosition(pos);


}

void PhysicsObject::doRender()
{

}


void PhysicsObject::CollisionDetection()
{

}