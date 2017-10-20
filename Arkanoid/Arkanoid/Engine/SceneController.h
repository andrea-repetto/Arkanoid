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
		bool doRender() override;
		bool doLateRender() override;

	private:
		
	};
}

