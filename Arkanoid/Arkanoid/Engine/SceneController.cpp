#include "pch.h"
#include "SceneController.h"
#include "GameEngine.h"
#include "Camera.h"

using namespace Engine;

SceneController::SceneController()
	: SceneController(Physics::BoundingBox())
{
	
}

SceneController::SceneController(Physics::BoundingBox levelSize)
	: GameObject()
	, m_Octree(Physics::Octree::BuildOctree(levelSize, Physics::BoundingBox()))
{

}

void SceneController::doUpdate(DX::StepTimer const& timer)
{
	RunCollisionDetection();
}


SceneController::~SceneController()
{
	delete m_Octree;
}

void SceneController::OnWindowResizeEvent()
{
	GameEngine::Instance()->GetActiveCamera()->CreateWindowSizeDependentResources();
}


void SceneController::RunCollisionDetection()
{
	Physics::Octree::UpdateOctree(*m_Octree);
	Physics::Octree::RunCollisionDetection(*m_Octree);
}


