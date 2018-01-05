#include "pch.h"
#include "PhysicsObject.h"

using namespace Engine::Physics;

//std::vector<PhysicsObject*> PhysicsObject::PhysicsObjectsList;

PhysicsObject::PhysicsObject()
	: GameObject()
	, m_velocity(0,0,0)
	, m_CollisionDetection(false)
{
	//PhysicsObjectsList.push_back(this);
}


PhysicsObject::~PhysicsObject()
{
	/* Remove element from physcs object list */
	/**
	for (int idx = 0; idx < PhysicsObjectsList.size(); ++idx)
	{
		if (PhysicsObjectsList[idx] == this)
		{
			PhysicsObjectsList.erase(PhysicsObjectsList.begin() + idx);
			return;
		}
	}
	*/
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