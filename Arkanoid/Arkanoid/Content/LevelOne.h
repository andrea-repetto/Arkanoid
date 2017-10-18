#pragma once
#include "Engine/SceneController.h"

class LevelOne : public Engine::SceneController
{
public:
	explicit LevelOne();
	virtual ~LevelOne();


private:
	void doOnWindowsResizeEvent() override;
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;
};

