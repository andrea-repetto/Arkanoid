#pragma once
#include "Engine\GameEngine.h"
#include "Engine\RenderObject.h"
#include "Engine\PhysicsObject.h"

class PlayerController : public Engine::Physics::PhysicsObject
{
public:
	PlayerController();
	~PlayerController();

	void SetLocalPlayerBounds(float leftBound, float rightBound);

protected:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:

	float GetMovementDirectionFromInput();

	bool CheckIfPlayerCanMove(float moveInputDirection);

private:
	Engine::RenderObject	m_Body;
	Engine::RenderObject	m_LeftHead;
	Engine::RenderObject	m_RightHead;

	float m_LeftBound;
	float m_RightBound;
};

