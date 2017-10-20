#include "pch.h"
#include "SceneController.h"
#include "GameEngine.h"
#include "Camera.h"

using namespace Engine;

SceneController::SceneController()
	: GameObject( )
{
}


SceneController::~SceneController()
{
}

void SceneController::OnWindowResizeEvent()
{
	GameEngine::Instance()->GetActiveCamera()->CreateWindowSizeDependentResources();
}


