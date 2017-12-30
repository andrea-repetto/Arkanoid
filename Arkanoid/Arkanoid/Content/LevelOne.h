#pragma once
#include "Engine/SceneController.h"
#include "Wall.h"

class LevelOne : public Engine::SceneController
{
public:
	explicit LevelOne();
	virtual ~LevelOne();




private:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;

	void doRender() override;


private:
	Wall		m_Wall;

};

