#include "pch.h"
#include "Brick.h"

using namespace Engine;
using namespace DirectX;

Brick::Brick()
	: GameObject()
	, m_rectBrick(GameEngine::Instance()->GetSquareMeshData())
{
	m_Physics.SetParent(this);
	m_rectBrick.SetParent(&m_Physics);
	XMFLOAT3 scale(1.0f, 0.5f, 0.25f);
	m_rectBrick.SetLocalScale(scale);
	Physics::BoundingBox b(XMFLOAT3(0.0f, 0.0f, 0.0f),scale);
	m_Physics.SetBoundingBox(b);
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
