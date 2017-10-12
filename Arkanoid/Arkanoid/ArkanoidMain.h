#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\SceneOne.h"

// Renders Direct3D content on the screen.
namespace Arkanoid
{
	class ArkanoidMain
	{
	public:
		ArkanoidMain();
		void CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void Update();
		bool Render();

		void OnWindowSizeChanged();
		void OnSuspending();
		void OnResuming();
		void OnDeviceRemoved();

	private:
		// TODO: Replace with your own content renderers.
		std::unique_ptr<SceneOne> m_sceneRenderer;

		// Rendering loop timer.
		DX::StepTimer m_timer;
	};
}