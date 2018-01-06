#include "pch.h"
#include "Ball.h"

using namespace Engine;
using namespace DirectX;

Ball::Ball()
	: GameObject()
	, m_sphere(GameEngine::Instance()->GetSphereMeshData())
{
	m_sphere.SetParent(this);
	m_Physics.SetParent(this);
	m_Physics.EnableCollisionDetection(true);
}


Ball::~Ball()
{
}



void Ball::doStart()
{
	m_sphere.Start();
}

void Ball::doUpdate(DX::StepTimer const& timer)
{
	m_sphere.Update(timer);
}

void Ball::doRender()
{
	m_sphere.Render();
}

