#include "pch.h"
#include "PlayerController.h"
#include "Common\Keyboard.h"
#include "GameIDs.h"

using namespace Engine;
using namespace DirectX;

PlayerController::PlayerController()
	: Physics::PhysicsObject(GameData::ID_PLAYER)
	, m_Body(GameEngine::Instance()->GetCilinderMeshData())
	, m_LeftHead(GameEngine::Instance()->GetSphereMeshData())
	, m_RightHead(GameEngine::Instance()->GetSphereMeshData())
	, m_LeftBound(-1.0f)
	, m_RightBound(1.0f)
{
	m_Body.SetParent(this);
	m_LeftHead.SetParent(this);
	m_RightHead.SetParent(this);

	m_Body.SetLocalScale(XMFLOAT3(.3f, 3.0f, .3f));
	m_Body.SetLocalRotationYawPitchRoll(XMFLOAT3(1.57f, 0.0f, 0.0f));
	m_Body.SetMaterial(Engine::Material(1.0f, 1.0f, 1.0f));

	m_LeftHead.SetLocalScale(XMFLOAT3(.3f, .3f, .3f));
	m_LeftHead.SetLocalPosition(XMFLOAT3(-1.5f, 0.0f, 0.0f));

	m_RightHead.SetLocalScale(XMFLOAT3(.3f, .3f, .3f));
	m_RightHead.SetLocalPosition(XMFLOAT3(1.5f, 0.0f, 0.0f));

	Physics::BoundingBox bb(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(4.f, .5f, .3f));
	SetBoundingBox(bb);
	
}


PlayerController::~PlayerController()
{
}

void PlayerController::doStart()
{
	Physics::PhysicsObject::doStart();
	m_Body.Start();
	m_LeftHead.Start();
	m_RightHead.Start();
}

void PlayerController::doUpdate(DX::StepTimer const& timer)
{
	Physics::PhysicsObject::doUpdate(timer);
	float moveDir = GetMovementDirectionFromInput();
	float moveSpeed = CheckIfPlayerCanMove(moveDir) ? 15.0f : 0.0f;

	SetVelocity(XMFLOAT3(moveDir*moveSpeed, 0.0f, 0.0f));

	m_Body.Update(timer);
	m_LeftHead.Update(timer);
	m_RightHead.Update(timer);
}

void PlayerController::doRender()
{
	m_Body.Render();
	m_LeftHead.Render();
	m_RightHead.Render();
}

float PlayerController::GetMovementDirectionFromInput()
{
	auto kb = Keyboard::Get().GetState();

	if (kb.A)
	{
		return -1.0f;
	}
	else if (kb.D)
	{
		return 1.0f;
	}
	
	return 0.0f;
}

void PlayerController::SetLocalPlayerBounds(float leftBound, float rightBound)
{
	m_LeftBound = leftBound;
	m_RightBound = rightBound;
}


bool PlayerController::CheckIfPlayerCanMove(float moveInputDirection)
{
	float currentXPosition = m_Body.GetGlobalPosition().x;
	float halfBodyOffset = m_RightHead.GetLocalPosition().x + m_RightHead.GetLocalScale().x/2.0f;

	if ((currentXPosition - halfBodyOffset) < m_LeftBound && moveInputDirection < 1.0f)
	{
		return false;
	}
	else if ((currentXPosition + halfBodyOffset) > m_RightBound && moveInputDirection > -1.0f)
	{
		return false;
	}

	return true;
}