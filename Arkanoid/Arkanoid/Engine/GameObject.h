#pragma once

#include <vector>
#include <string>
#include <DirectXMath.h>

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


		inline DirectX::XMFLOAT3 GetLocalTransform() const { return m_localTransform; }
		inline DirectX::XMFLOAT3 GetGlobalTransform() const { return m_globalTransform; }
		inline DirectX::XMFLOAT3 GetLocalScale() const { return m_localScale; }
		inline DirectX::XMFLOAT3 GetGlobalScale() const { return m_globalScale; }
		inline DirectX::XMFLOAT3 GetLocalRotationYawPitchRoll() const { return m_localRotationYawPitchRoll; }
		inline DirectX::XMFLOAT3 GetGlobalRotationYawPitchRoll() const { return m_globalRotationYawPitchRoll; }
		
		void SetLocalTransform(DirectX::XMFLOAT3& transform );
		void SetLocalScale(DirectX::XMFLOAT3& scale );
		void SetLocalRotationYawPitchRoll(DirectX::XMFLOAT3& rotationYawPitchRoll );
			

	private:
		virtual void doStart() = 0;
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual bool doRender() = 0;

	private:
		GameObject*				m_parent;
		DirectX::XMFLOAT3		m_localTransform;
		DirectX::XMFLOAT3		m_globalTransform;
		DirectX::XMFLOAT3		m_localRotationYawPitchRoll;
		DirectX::XMFLOAT3		m_globalRotationYawPitchRoll;
		DirectX::XMFLOAT3		m_localScale;
		DirectX::XMFLOAT3		m_globalScale;

		

	};
}

