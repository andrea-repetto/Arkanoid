#include "pch.h"
#include "LevelOne.h"
#include "Engine\Square.h"
#include "Engine\GameEngine.h"

using namespace Engine;
using namespace DirectX;

LevelOne::LevelOne()
	: SceneController()
{
	m_Wall.SetParent(this);
	m_Wall.SetLocalPosition(XMFLOAT3(0.0f, 5.0f, 0.0f));

}


LevelOne::~LevelOne()
{


}


void LevelOne::doStart()
{
	m_Wall.Start();
}

void LevelOne::doUpdate(DX::StepTimer const& timer)
{
	m_Wall.Update(timer);
}

void LevelOne::doRender()
{
	m_Wall.Render();

}
