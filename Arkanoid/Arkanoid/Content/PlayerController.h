#pragma once
#include "Engine\GameEngine.h"
#include "Engine\RenderObject.h"
#include "Engine\PhysicsObject.h"

class PlayerController : public Engine::GameObject
{
public:
	PlayerController();
	~PlayerController();

private:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

	float GetMovementDirectionFromInput();

private:
	Engine::RenderObject	m_Body;
	Engine::RenderObject	m_LeftHead;
	Engine::RenderObject	m_RightHead;
	Engine::PhysicsObject   m_Physics;
};

