#pragma once

#include <vector>
#include <string>

/** Forward Declarations */
namespace DX
{
	class StepTimer;
	class DeviceResources;
}

namespace Engine
{
	class GameObject
	{
	public:
		explicit GameObject( );
		virtual ~GameObject();

		void Start();
		void Render();
		void Update(DX::StepTimer const& timer);
		void SetParent(GameObject* i_newParent);
		inline const GameObject* GetParent() const { return m_parent; }


	private:
		virtual void doStart() = 0;
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual void doRender() = 0;
		virtual void doLateRender() = 0;


		void addChild(GameObject* i_gameObj);
		void removeChild(GameObject* i_gameObj);


	private:
		GameObject*											m_parent;
		std::vector<GameObject*>							m_children;
	};
}

