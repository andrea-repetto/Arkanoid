#include "pch.h"
#include "PhysicsObject.h"

using namespace Engine;

PhysicsObject::PhysicsObject()
	: m_velocity(0,0,0)
{
}


PhysicsObject::~PhysicsObject()
{
}



void PhysicsObject::doStart()
{

}

void PhysicsObject::doUpdate(DX::StepTimer const& timer)
{
	DirectX::XMFLOAT3 pos = GetLocalPosition();

	pos.x += m_velocity.x * timer.GetElapsedSeconds();
	pos.y += m_velocity.y * timer.GetElapsedSeconds();
	pos.z += m_velocity.z * timer.GetElapsedSeconds();

	SetLocalPosition(pos);
}

void PhysicsObject::doRender()
{

}
