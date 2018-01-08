#pragma once
#include "Engine\GameObject.h"
#include "Engine\RenderObject.h"
#include "Engine\PhysicsObject.h"

class Ball: public Engine::Physics::PhysicsObject
{
public:
	Ball();
	~Ball();

protected:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:
	void OnCollision(Engine::Physics::PhysicsObject& other, const Engine::Physics::ContactPoint& p) override;


private:
	Engine::RenderObject	m_sphere;
};

