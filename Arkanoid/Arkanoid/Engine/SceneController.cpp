#include "pch.h"
#include "SceneController.h"

using namespace Engine;

SceneController::SceneController()
	: GameObject()
{
}


SceneController::~SceneController()
{
}

void SceneController::OnWindowResizeEvent()
{
	doOnWindowsResizeEvent();
}
