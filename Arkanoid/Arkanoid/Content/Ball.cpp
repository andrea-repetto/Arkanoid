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

	DirectX::XMFLOAT3 zAxes(0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR zAxesVector = DirectX::XMLoadFloat3(&zAxes);

	DirectX::XMFLOAT3 yAxes(0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR yAxesVector = DirectX::XMLoadFloat3(&yAxes);

	DirectX::XMVECTOR xDir = DirectX::XMVector3Dot(v, xAxesVector);
	DirectX::XMFLOAT3 xDirFloat;
	DirectX::XMStoreFloat3(
		&xDirFloat,
		xDir
	);

	
	DirectX::XMFLOAT3 newVel = velocity;


	// Bouncing handling 
	if (other->GetID() == GameData::ID_PLAYER)
	{
		float distance = fabs(other->GetGlobalPosition().x - GetGlobalPosition().x);
		float maxDistance = 2.0f;
		float maxDegree = 0.1f;
		float minDegree = 0.8f;

		//(distance, degree) (x, y)
		float finalDegree = ((distance - maxDistance) / (0 - maxDistance))*maxDegree - ((distance) / (0 - maxDistance))*minDegree;


		DirectX::XMVECTOR rotQuat = DirectX::XMQuaternionRotationAxis(zAxesVector, finalDegree);

		if (other->GetGlobalPosition().x < GetGlobalPosition().x)
		{
			rotQuat = DirectX::XMQuaternionRotationAxis(zAxesVector, -1.0f*finalDegree);
		}

		DirectX::XMVECTOR resultVector = XMVector3Rotate(n, rotQuat);

		resultVector = DirectX::XMVectorScale(resultVector, 5.0f);
		

		DirectX::XMStoreFloat3(
			&newVel,
			resultVector
		);
		
	}
	else
	{
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
	}
	

	/* BRICK hit handling */
	if (other->GetID() == GameData::ID_BRICK)
	{
		Brick* brick = reinterpret_cast<Brick*>(other);
		brick->Hit();
	}

	SetVelocity(newVel);
}


