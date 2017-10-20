#pragma once
#include "Engine/SceneController.h"

namespace Engine
{
	class Square;
}

class LevelOne : public Engine::SceneController
{
public:
	explicit LevelOne();
	virtual ~LevelOne();




private:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;

	bool doRender() override;


private:
	class Engine::Square* m_square;
};

