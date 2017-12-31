#include "pch.h"
#include "Side.h"

using namespace Engine;
using namespace DirectX;

Side::Side()
	: GameObject()
	, m_rectSide(GameEngine::Instance()->GetSquareMeshData())
{
	m_rectSide.SetParent(this);
	m_rectSide.SetMaterial(Engine::Material(1.0f, 1.0f, 1.0f));
}


Side::~Side()
{
}


void Side::doStart()
{
	m_rectSide.Start();
}

void Side::doUpdate(DX::StepTimer const& timer)
{
	m_rectSide.Update(timer);
}

void Side::doRender()
{
	m_rectSide.Render();
}
