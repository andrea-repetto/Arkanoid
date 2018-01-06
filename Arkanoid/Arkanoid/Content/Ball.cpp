#include "pch.h"
#include "Ball.h"

using namespace Engine;
using namespace DirectX;

Ball::Ball()
	: GameObject()
	, m_sphere(GameEngine::Instance()->GetSphereMeshData())
{
	m_Physics.SetParent(this);
	m_sphere.SetParent(&m_Physics);
	m_Physics.EnableCollisionDetection(true);

	m_Physics.SetVelocity(XMFLOAT3(0.0f, 4.0f, 0.0f));
}


Ball::~Ball()
{
}



void Ball::doStart()
{
	m_sphere.Start();
	m_Physics.Start();
}

void Ball::doUpdate(DX::StepTimer const& timer)
{
	m_sphere.Update(timer);
	m_Physics.Update(timer);
}

void Ball::doRender()
{
	m_sphere.Render();
}

