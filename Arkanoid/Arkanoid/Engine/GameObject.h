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
		GameObject( 
			const std::string& name,
			const std::shared_ptr<DX::DeviceResources>& deviceResources
		);
		virtual ~GameObject();

		void Start();
		void Render();
		void Update(DX::StepTimer const& timer);
		void SetParent(GameObject* i_newParent);
		inline const GameObject* GetParent() const { return m_parent; }
		inline const std::string& GetName() const { return m_name;  }

	protected:
		inline const std::shared_ptr<DX::DeviceResources>& deviceResources() const { return m_deviceResources; }

	private:
		virtual void doStart() = 0;
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual void doRender() = 0;
		virtual void doLateRender() = 0;


		void addChild(GameObject* i_gameObj);
		void removeChild(GameObject* i_gameObj);


	private:
		std::string											m_name;
		std::shared_ptr<DX::DeviceResources>				m_deviceResources;
		GameObject*											m_parent;
		std::vector<GameObject*>							m_children;
	};
}

