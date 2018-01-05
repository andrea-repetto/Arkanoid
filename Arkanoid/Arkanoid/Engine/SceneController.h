#pragma once

#include "GameObject.h"
#include "Engine\Physics\Octree.h"
#include "PhysicsObject.h"
#include <vector>
namespace Engine
{
	class SceneController : public GameObject
	{
	public:
		SceneController();
		explicit SceneController( Physics::BoundingBox levelSize );
		virtual ~SceneController();
		
		void OnWindowResizeEvent();
		void RunCollisionDetection();


	private:
		virtual void doRender() = 0;

	private:
		Physics::Octree			*m_Octree;
		
	};
}

