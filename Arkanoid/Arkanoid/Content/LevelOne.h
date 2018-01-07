#pragma once
#include "Engine/SceneController.h"
#include "Wall.h"
#include "Side.h"
#include "PlayerController.h"
#include "Ball.h"

class LevelOne : public Engine::SceneController
{
public:
	explicit LevelOne();
	virtual ~LevelOne();

protected:
	void doStart() override;
	void doUpdate(DX::StepTimer const& timer) override;

	void doRender() override;

private:
	Wall		m_Wall;
	Ball		m_Ball;
	
	Side		m_UpSide;
	Side		m_DownSide;
	Side		m_LeftSide;
	Side		m_RightSide;
	PlayerController m_Player;


private:
	static void Test(Engine::Physics::PhysicsObject& caller, Engine::Physics::PhysicsObject& other);
	


};

