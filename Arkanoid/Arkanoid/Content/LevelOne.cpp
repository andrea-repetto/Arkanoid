#include "pch.h"
#include "LevelOne.h"
#include "Engine\Square.h"

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


void LevelOne::doOnWindowsResizeEvent()
{

}

void LevelOne::doStart()
{

}

void LevelOne::doUpdate(DX::StepTimer const& timer)
{

}
