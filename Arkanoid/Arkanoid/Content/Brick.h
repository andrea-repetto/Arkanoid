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

	inline int GetLife() const { return m_Life; }
	inline void SetLife(int life) { m_Life = life; }

	void Hit();

protected:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:
	Engine::RenderObject	m_rectBrick;
	int m_Life;
};

