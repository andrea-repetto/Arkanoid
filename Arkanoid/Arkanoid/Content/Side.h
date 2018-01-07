#pragma once
#include "Engine\GameObject.h"
#include "Engine\RenderObject.h"
#include "Engine\PhysicsObject.h"

class Side : public Engine::Physics::PhysicsObject
{
public:
	Side();
	~Side();

protected:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:
	Engine::RenderObject	m_rectSide;
};

