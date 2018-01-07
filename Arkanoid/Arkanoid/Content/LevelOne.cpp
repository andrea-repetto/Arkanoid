#include "pch.h"
#include "LevelOne.h"
#include "Engine\Square.h"
#include "Engine\GameEngine.h"
#include "Engine\PhysicsObject.h"

using namespace Engine;
using namespace DirectX;

LevelOne::LevelOne()
	: SceneController(Physics::BoundingBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(30.0f,30.0f,30.0f)))
{
	/* Brick wall */
	m_Wall.SetParent(this);
	m_Wall.SetLocalPosition(XMFLOAT3(0.0f, 4.0f, -5.0f));

	m_Ball.SetParent(this);
	m_Ball.SetLocalScale(XMFLOAT3(0.2f, 0.2f, 0.2f));
	m_Ball.SetLocalPosition(XMFLOAT3(0.0f, 0.0f, -5.0f));

	
	/* level Sides */
	
	m_UpSide.SetParent(this);
	m_UpSide.SetLocalPosition(XMFLOAT3(0.0f, 7.0f, -5.0f));
	m_UpSide.SetLocalScale(XMFLOAT3(20.0f, 0.5f, 0.25f));

	//m_DownSide.SetParent(this); 
	m_LeftSide.SetParent(this);
	m_LeftSide.SetLocalPosition(XMFLOAT3(-10.0f, 0.0f, -5.0f));
	m_LeftSide.SetLocalScale(XMFLOAT3(0.5f, 20.5f, 0.25f));
	m_RightSide.SetParent(this);
	m_RightSide.SetLocalPosition(XMFLOAT3(10.0f, 0.0f, -5.0f));
	m_RightSide.SetLocalScale(XMFLOAT3(0.5f, 20.5f, 0.25f));

	m_Player.SetParent(this);
	m_Player.SetLocalPosition(XMFLOAT3(0.0f, -6.0f, -5.0f));
	m_Player.SetLocalPlayerBounds(
	m_LeftSide.GetLocalPosition().x + m_LeftSide.GetLocalScale().x,
	m_RightSide.GetLocalPosition().x - m_RightSide.GetLocalScale().x);
	
	//Test
//	Physics::PhysicsObject::OnCollisionDetected listener = &(LevelOne::Test);

//	m_Ball.RegisterCollisionListener(listener);

}


LevelOne::~LevelOne()
{

	
}


void LevelOne::doStart()
{
	m_Wall.Start();
	m_Ball.Start();

	m_UpSide.Start();
	//m_DownSide.Start();
	m_LeftSide.Start();
	m_RightSide.Start();
	m_Player.Start();

	
}

void LevelOne::doUpdate(DX::StepTimer const& timer)
{
	SceneController::doUpdate(timer);

	m_Wall.Update(timer);
	m_Ball.Update(timer);
	m_UpSide.Update(timer);
	//m_DownSide.Update(timer);
	m_LeftSide.Update(timer);
	m_RightSide.Update(timer);
	m_Player.Update(timer);
	
}

void LevelOne::doRender()
{
	m_Wall.Render();
	m_Ball.Render();

	m_UpSide.Render();
	//m_DownSide.Render();
	m_LeftSide.Render();
	m_RightSide.Render();
	m_Player.Render();
	

}

void LevelOne::Test(Physics::PhysicsObject& caller, Physics::PhysicsObject& other)
{
	DirectX::XMFLOAT3 vel = caller.GetVelocity();
	//provvisorio
	vel = DirectX::XMFLOAT3(
		vel.x,
		vel.y*(-1.0f),
		vel.z
	);

	caller.SetVelocity(vel);
}
