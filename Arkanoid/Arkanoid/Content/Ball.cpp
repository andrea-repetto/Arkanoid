#include "pch.h"
#include "Ball.h"

using namespace Engine;
using namespace DirectX;

Ball::Ball()
	: Physics::PhysicsObject()
	, m_sphere(GameEngine::Instance()->GetSphereMeshData())
{
	m_sphere.SetParent(this);
	EnableCollisionDetection(true);

	SetVelocity(XMFLOAT3(0.0f, 4.0f, 0.0f));
}


Ball::~Ball()
{
}



void Ball::doStart()
{
	Physics::PhysicsObject::doStart();
	m_sphere.Start();
}

void Ball::doUpdate(DX::StepTimer const& timer)
{
	Physics::PhysicsObject::doUpdate(timer);
	m_sphere.Update(timer);
}

void Ball::doRender()
{
	m_sphere.Render();
}


