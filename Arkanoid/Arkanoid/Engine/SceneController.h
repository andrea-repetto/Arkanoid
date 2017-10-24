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
		virtual void doRender() = 0;

	private:
		
	};
}

