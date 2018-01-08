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

	SetVelocity(XMFLOAT3(-2.0f, 8.0f, 0.0f));

	//Physics::BoundingBox b(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.2f, 0.2f));
	//SetBoundingBox(b);
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


void Ball::OnCollision(Physics::PhysicsObject& other, const Physics::ContactPoint& p)
{
	//Calculate bouncing
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
}


