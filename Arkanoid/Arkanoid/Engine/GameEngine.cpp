#include "pch.h"
#include "GameEngine.h"


using namespace Engine;

GameEngine* GameEngine::s_Instance = nullptr;

GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}



GameEngine* GameEngine::Instance()
{
	if (!s_Instance)
	{
		s_Instance = new GameEngine();
	}

	return s_Instance;
}

void GameEngine::Initialize(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	m_deviceResources = deviceResources;
}


