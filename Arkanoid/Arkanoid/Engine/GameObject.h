#pragma once

#include <vector>
#include <string>
#include <DirectXMath.h>

/** Forward Declarations */
namespace DX
{
	class StepTimer;
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


		inline DirectX::XMFLOAT3 GetLocalTransform() const { return m_localTransform; }
		inline DirectX::XMFLOAT3 GetLocalScale() const { return m_localScale; }
		inline DirectX::XMFLOAT3 GetLocalRotationYawPitchRoll() const { return m_localRotationYawPitchRoll; }

		DirectX::XMFLOAT3 GetGlobalTransform() const ;
		DirectX::XMFLOAT3 GetGlobalScale() const;
		DirectX::XMFLOAT3 GetGlobalRotationYawPitchRoll() const;
		
		inline void SetLocalTransform(DirectX::XMFLOAT3& transform) { m_localTransform = transform; }
		inline void SetLocalScale(DirectX::XMFLOAT3& scale) { m_localScale = scale; }
		inline void SetLocalRotationYawPitchRoll(DirectX::XMFLOAT3& rotationYawPitchRoll) { m_localRotationYawPitchRoll = rotationYawPitchRoll; }
			

	private:
		virtual void doStart() = 0;
		virtual void doUpdate(DX::StepTimer const& timer) = 0;
		virtual void doRender() = 0;

	private:
		GameObject*				m_parent;
		DirectX::XMFLOAT3		m_localTransform;
		DirectX::XMFLOAT3		m_localRotationYawPitchRoll;
		DirectX::XMFLOAT3		m_localScale;

	};
}

