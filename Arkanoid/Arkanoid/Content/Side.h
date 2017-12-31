#pragma once
#include "Engine\GameObject.h"
#include "Engine\RenderObject.h"

class Side : public Engine::GameObject
{
public:
	Side();
	~Side();

private:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
	void doRender() override;

private:
	Engine::RenderObject	m_rectSide;
};

