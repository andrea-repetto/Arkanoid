#include "pch.h"
#include "SceneController.h"

using namespace Engine;

SceneController::SceneController(
	const std::string& name,
	const std::shared_ptr<DX::DeviceResources>& deviceResources
)
	: GameObject( name, deviceResources )
{
}


SceneController::~SceneController()
{
}

void SceneController::OnWindowResizeEvent()
{
	doOnWindowsResizeEvent();
}
