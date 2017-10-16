#pragma once

#include "GameObject.h"
namespace Engine
{
	class SceneController : GameObject
	{
	public:
		SceneController();
		virtual ~SceneController();
		
		void OnWindowResizeEvent();


	private:
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual void doRender() = 0;
		virtual void doOnWindowsResizeEvent() = 0;

	};
}

