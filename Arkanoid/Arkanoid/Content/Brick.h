#pragma once
#include "Engine\GameObject.h"
#include "Engine\RenderObject.h"
#include "Engine\PhysicsObject.h"

class Brick : public Engine::Physics::PhysicsObject 
{
public:
	Brick();
	virtual ~Brick();

	Engine::Material GetMaterial() const;
	void SetMaterial(const Engine::Material& material);

	float GetWidth();
	float GetHeight();

protected:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:
	Engine::RenderObject	m_rectBrick;
};

