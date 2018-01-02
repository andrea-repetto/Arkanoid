#include "pch.h"
#include "Collider.h"
#include "../PhysicsObject.h" //TO FIX

using namespace Engine::Physics;

Collider::Collider()
	: Collider(nullptr)
{
}

Collider::Collider(PhysicsObject* owner)
	: m_Owner(owner)
	, m_X(0.0f)
	, m_Y(0.0f)
	, m_Width(1.0f)
	, m_Height(1.0f)

{
}


Collider::~Collider()
{
}


void Collider::SetBounds(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}
