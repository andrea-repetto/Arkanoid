#include "pch.h"
#include "LevelOne.h"
#include "Engine\Square.h"
#include "Engine\GameEngine.h"

using namespace Engine;

LevelOne::LevelOne()
{

	m_square = new Square();
	m_square->SetParent(this);


}


LevelOne::~LevelOne()
{
	delete m_square;

}


void LevelOne::doStart()
{
	m_square->Start();
}

void LevelOne::doUpdate(DX::StepTimer const& timer)
{
	m_square->Update(timer);
}

bool LevelOne::doRender()
{
	m_square->Render();

	return true;
}
