#pragma once

#include "GameObject.h"
namespace Engine
{
	class SceneController : public GameObject
	{
	public:
		explicit SceneController();
		virtual ~SceneController();
		
		void OnWindowResizeEvent();


	private:
		void doRender() override;
		void doLateRender() override;
		virtual void doOnWindowsResizeEvent() = 0;

	private:
		
	};
}

