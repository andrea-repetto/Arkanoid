#pragma once

#include "GameObject.h"

#include <vector>
namespace Engine
{
	class SceneController : public GameObject
	{
	public:
		explicit SceneController();
		virtual ~SceneController();
		
		void OnWindowResizeEvent();
		void RunCollisionDetection();


	private:
		virtual void doRender() = 0;

	private:
		
		
	};
}

