#include "pch.h"
#include "PhysicsObject.h"
#include "Physics\Octree.h"
#include <cmath>
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

	float elapsedSeconds = static_cast<float>(timer.GetElapsedSeconds());

	pos.x += m_velocity.x * elapsedSeconds;
	pos.y += m_velocity.y * elapsedSeconds;
	pos.z += m_velocity.z * elapsedSeconds;

	SetLocalPosition(pos);

}

void PhysicsObject::doRender()
{

}


void PhysicsObject::CollisionDetected(PhysicsObject& other, const ContactPoint& p)
{
	/* Find where is located collision */
	DirectX::XMFLOAT3 velocity = GetVelocity();
	DirectX::XMVECTOR n = DirectX::XMLoadFloat3(&p.normal);
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&velocity);

	DirectX::XMVECTOR dotProdVector = DirectX::XMVector3Dot(v, n);
	DirectX::XMFLOAT3 dotProdFloat;
	DirectX::XMStoreFloat3(
		&dotProdFloat,
		dotProdVector
	);

	DirectX::XMVECTOR proj = DirectX::XMVectorScale(n, 2 * dotProdFloat.x);

	DirectX::XMVECTOR res = DirectX::XMVectorSubtract(v, proj);
	DirectX::XMFLOAT3 newVel;
	DirectX::XMStoreFloat3(
		&newVel,
		res
	);

	SetVelocity(newVel);
	

	//for (size_t idx = 0; idx < m_RegisteredCollisionListener.size(); ++idx)
	//{
		//m_RegisteredCollisionListener[idx](*this, other);
	//}
}

/**
* LIMITATION: works only with CollisionBox aligned to default XYZ axes. (no rotation)
*/
void PhysicsObject::CollisionTest(PhysicsObject& other)
{
	DirectX::XMFLOAT3 pos = GetLocalPosition();
	BoundingBox myBB = GetWorldBoundingBox();
	BoundingBox othBB = other.GetWorldBoundingBox();

	float maxLowerX = fmaxf((myBB.center.x - myBB.scale.x / 2.0f), (othBB.center.x - othBB.scale.x / 2.0f));
	float minUpperX = fminf((myBB.center.x + myBB.scale.x / 2.0f), (othBB.center.x + othBB.scale.x / 2.0f));
	float overlapLenX = minUpperX - maxLowerX;

	float maxLowerY = fmaxf((myBB.center.y - myBB.scale.y / 2.0f), (othBB.center.y - othBB.scale.y / 2.0f));
	float minUpperY = fminf((myBB.center.y + myBB.scale.y / 2.0f), (othBB.center.y + othBB.scale.y / 2.0f));
	float overlapLenY = minUpperY - maxLowerY;

	float maxLowerZ = fmaxf((myBB.center.z - myBB.scale.z / 2.0f), (othBB.center.z - othBB.scale.z / 2.0f));
	float minUpperZ = fminf((myBB.center.z + myBB.scale.z / 2.0f), (othBB.center.z + othBB.scale.z / 2.0f));
	float overlapLenZ = minUpperZ - maxLowerZ;


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


	if (!isNotOverlappingOnXAxis && !isNotOverlappingOnYAxis && !isNotOverlappingOnZAxis) //if Collision detected
	{
		//detect collision point (face normal)
		ContactPoint p;

		if (overlapLenX > overlapLenY && overlapLenX >= overlapLenZ) //Max overlap on X axes
		{
			if (myBB.center.y < othBB.center.y) //collision is above
			{
				p.normal = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);
			}
			else
			{
				p.normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
			}
		}
		else if (overlapLenY > overlapLenX && overlapLenY > overlapLenZ) //Max overlap on Y axes
		{
			if (myBB.center.x < othBB.center.x) //collision is above
			{
				p.normal = DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f);
			}
			else
			{
				p.normal = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
			}
		}
		else //Max overlap on Z axes
		{
			if (myBB.center.z < othBB.center.z) //collision is above
			{
				p.normal = DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f);
			}
			else
			{
				p.normal = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
			}
		}

		CollisionDetected(other, p);
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

	result.scale.x *= globalScale.x * GetLocalScale().x;
	result.scale.y *= globalScale.y * GetLocalScale().y;
	result.scale.z *= globalScale.z * GetLocalScale().z;

	result.center.x += globalPosition.x;
	result.center.y += globalPosition.y;
	result.center.z += globalPosition.z;

	return result;
}

/**
void PhysicsObject::RegisterCollisionListener(OnCollisionDetected onCollisionListener)
{
	m_RegisteredCollisionListener.push_back(onCollisionListener);
}

void PhysicsObject::DeleteCollisionListener(OnCollisionDetected onCollisionListener)
{
	for (size_t idx = 0; idx < m_RegisteredCollisionListener.size(); ++idx)
	{
		if (m_RegisteredCollisionListener[idx] == onCollisionListener)
		{
			m_RegisteredCollisionListener.erase(m_RegisteredCollisionListener.begin() + idx);
			return;
		}
	}
}
*/

/*
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