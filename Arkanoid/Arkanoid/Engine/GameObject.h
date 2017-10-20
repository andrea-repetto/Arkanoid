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
		bool Render();
		void Update(DX::StepTimer const& timer);
		void SetParent(GameObject* i_newParent);
		inline const GameObject* GetParent() const { return m_parent; }


		
		

	private:
		virtual void doStart() = 0;
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual bool doRender() = 0;

	private:
		GameObject*											m_parent;

	};
}

