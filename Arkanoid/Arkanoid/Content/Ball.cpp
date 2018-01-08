#include "pch.h"
#include "Ball.h"
#include "GameIDs.h"
#include <iostream>

using namespace Engine;
using namespace DirectX;

Ball::Ball()
	: Physics::PhysicsObject(GameData::ID_BALL)
	, m_sphere(GameEngine::Instance()->GetSphereMeshData())
{
	m_sphere.SetParent(this);
	EnableCollisionDetection(true);

	SetVelocity(XMFLOAT3(-2.0f, 8.0f, 0.0f));
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

	

	if (other.GetID() == GameData::ID_PLAYER)
	{
		newVel.x *= 0.8f;
		newVel.y *= 0.8f;
		newVel.z *= 0.8f;
	}
	else
	{
		newVel.x *= 1.2f;
		newVel.y *= 1.2f;
		newVel.z *= 1.2f;
	}

	SetVelocity(newVel);
}


