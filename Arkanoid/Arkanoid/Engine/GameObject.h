#pragma once

#include <vector>

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
		GameObject();
		virtual ~GameObject();

		void Render();
		void Update(DX::StepTimer const& timer);
		void SetParent(GameObject* i_newParent);
		inline const GameObject* GetParent() const { return m_parent; }



	private:
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual void doRender() = 0;


		void addChild(GameObject* i_gameObj);
		void removeChild(GameObject* i_gameObj);


	private:
		GameObject* m_parent;
		std::vector<GameObject*> m_children;
	};
}

