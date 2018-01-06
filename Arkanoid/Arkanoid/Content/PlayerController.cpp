#include "pch.h"
#include "PlayerController.h"
#include "Common\Keyboard.h"

using namespace Engine;
using namespace DirectX;

PlayerController::PlayerController()
	: GameObject()
	, m_Body(GameEngine::Instance()->GetCilinderMeshData())
	, m_LeftHead(GameEngine::Instance()->GetSphereMeshData())
	, m_RightHead(GameEngine::Instance()->GetSphereMeshData())
	, m_LeftBound(-1.0f)
	, m_RightBound(1.0f)
{
	m_Physics.SetParent(this);
	m_Body.SetParent(&m_Physics);
	m_LeftHead.SetParent(&m_Physics);
	m_RightHead.SetParent(&m_Physics);

	m_Body.SetLocalScale(XMFLOAT3(.3f, 3.0f, .3f));
	m_Body.SetLocalRotationYawPitchRoll(XMFLOAT3(1.57f, 0.0f, 0.0f));
	m_Body.SetMaterial(Engine::Material(1.0f, 1.0f, 1.0f));

	m_LeftHead.SetLocalScale(XMFLOAT3(.3f, .3f, .3f));
	m_LeftHead.SetLocalPosition(XMFLOAT3(-1.5f, 0.0f, 0.0f));

	m_RightHead.SetLocalScale(XMFLOAT3(.3f, .3f, .3f));
	m_RightHead.SetLocalPosition(XMFLOAT3(1.5f, 0.0f, 0.0f));

	Physics::BoundingBox bb(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(3.3f, .3f, .3f));
	m_Physics.SetBoundingBox(bb);

	
}


PlayerController::~PlayerController()
{
}

void PlayerController::doStart()
{
	m_Physics.Start();
	m_Body.Start();
	m_LeftHead.Start();
	m_RightHead.Start();
}

void PlayerController::doUpdate(DX::StepTimer const& timer)
{
	float moveDir = GetMovementDirectionFromInput();
	float moveSpeed = CheckIfPlayerCanMove(moveDir) ? 15.0f : 0.0f;

	m_Physics.SetVelocity(XMFLOAT3(moveDir*moveSpeed, 0.0f, 0.0f));

	m_Physics.Update(timer);
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