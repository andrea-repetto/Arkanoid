#pragma once
#include "Engine\GameObject.h"
#include "Engine\RenderObject.h"
#include "Engine\PhysicsObject.h"

class Ball: public Engine::GameObject
{
public:
	Ball();
	~Ball();

private:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:
	Engine::RenderObject	m_sphere;
	Engine::Physics::PhysicsObject   m_Physics;
};

