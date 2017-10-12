#include "pch.h"
#include "SceneOne.h"
#include "../Engine/Camera.h"
#include "../Engine/Square.h"

using namespace Arkanoid;

SceneOne::SceneOne()
	: m_loadingComplete(false)
	, m_Camera( new Engine::Camera() )
	, m_Square( new Engine::Square() )
{

	ZeroMemory(&m_constantBufferData, sizeof(m_constantBufferData));

}


SceneOne::~SceneOne()
{
	delete m_Square;
	delete m_Camera;
}

void SceneOne::CreateDeviceDependentResources()
{

}

void SceneOne::CreateWindowSizeDependentResources()
{
	m_Camera->CreateWindowSizeDependentResources();
}

void SceneOne::Update(DX::StepTimer const& timer)
{
	m_Square->Update(timer);
}

bool SceneOne::Render()
{
	if (!m_loadingComplete)
	{
		return false;
	}

	m_Square->Render();

	return true;
}
