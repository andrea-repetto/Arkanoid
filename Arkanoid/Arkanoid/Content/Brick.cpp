#include "pch.h"
#include "Brick.h"

using namespace Engine;
using namespace DirectX;

Brick::Brick()
	: GameObject()
	, m_rectBrick(GameEngine::Instance()->GetSquareMeshData())
{
	m_rectBrick.SetParent(this);
	m_rectBrick.SetLocalScale(XMFLOAT3(1.0f, 0.5f, 0.25f));
}


Brick::~Brick()
{
}


Engine::Material Brick::GetMaterial() const
{
	return m_rectBrick.GetMaterial();
}


void Brick::SetMaterial(const Engine::Material& material)
{
	m_rectBrick.SetMaterial(material);
}

float Brick::GetWidth()
{
	return m_rectBrick.GetLocalScale().x * GetLocalScale().x;
}

float Brick::GetHeight()
{
	return m_rectBrick.GetLocalScale().y * GetLocalScale().y;
}

void Brick::doStart() 
{
	m_rectBrick.Start();
}

void Brick::doUpdate(DX::StepTimer const& timer)
{
	m_rectBrick.Update(timer);
}

void Brick::doRender()
{
	m_rectBrick.Render();
}
