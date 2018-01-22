#include "pch.h"
#include "Ball.h"
#include "GameIDs.h"
#include "Brick.h"
#include <iostream>
#include <cmath>


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


void Ball::OnCollision(Physics::PhysicsObject* other, const Physics::ContactPoint& p)
{
	Physics::PhysicsObject::OnCollision(other, p);
	DirectX::XMFLOAT3 velocity = GetVelocity();
	DirectX::XMVECTOR n = DirectX::XMLoadFloat3(&p.normal);
	DirectX::XMVECTOR v = DirectX::XMLoadFloat3(&velocity);


	DirectX::XMFLOAT3 xAxes(1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR xAxesVector = DirectX::XMLoadFloat3(&xAxes);

	DirectX::XMVECTOR xDir = DirectX::XMVector3Dot(v, xAxesVector);
	DirectX::XMFLOAT3 xDirFloat;
	DirectX::XMStoreFloat3(
		&xDirFloat,
		xDir
	);
	DirectX::XMFLOAT3 newVel = velocity;


	DirectX::XMVECTOR dotProdVector = DirectX::XMVector3Dot(v, n);
	DirectX::XMFLOAT3 dotProdFloat;
	DirectX::XMStoreFloat3(
		&dotProdFloat,
		dotProdVector
	);

	DirectX::XMVECTOR proj = DirectX::XMVectorScale(n, 2.0f * dotProdFloat.x);

	DirectX::XMVECTOR res = DirectX::XMVectorSubtract(v, proj);

	DirectX::XMStoreFloat3(
		&newVel,
		res
	);

	/* Bouncing handling */
	if (other->GetID() == GameData::ID_PLAYER)
	{
		if (xDirFloat.x > 0 && GetGlobalPosition().x < other->GetGlobalPosition().x ||
			xDirFloat.x < 0 && GetGlobalPosition().x > other->GetGlobalPosition().x)
		{
			res = DirectX::XMVectorScale(res, -1.0f);
			
			dotProdVector = DirectX::XMVector3Dot(res, n);
			
			DirectX::XMStoreFloat3(
				&dotProdFloat,
				dotProdVector
			);

			proj = DirectX::XMVectorScale(n, 2 * dotProdFloat.x);

			res = DirectX::XMVectorSubtract(res, proj);
			
			DirectX::XMStoreFloat3(
				&newVel,
				res
			);

		}
	}
	

	/* BRICK hit handling */
	if (other->GetID() == GameData::ID_BRICK)
	{
		Brick* brick = reinterpret_cast<Brick*>(other);
		brick->Hit();
	}

	SetVelocity(newVel);
}


