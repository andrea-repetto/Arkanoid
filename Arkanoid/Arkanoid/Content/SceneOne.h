#pragma once

//#include "..\Common\DeviceResources.h"
#include "ShaderStructures.h"
#include "..\Common\StepTimer.h"

namespace Engine
{
	class Square;
	class Camera;
}

namespace Arkanoid
{
	class SceneOne
	{
	public:
		SceneOne();
		~SceneOne();

		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void Update(DX::StepTimer const& timer);
		bool Render();

	private:
		bool	m_loadingComplete;
		Engine::Square* m_Square;
		Engine::Camera* m_Camera;

		ModelViewProjectionConstantBuffer					m_constantBufferData;

	};
}

