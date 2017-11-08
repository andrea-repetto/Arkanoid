#pragma once
#include "GameObject.h"
namespace Engine
{
	class PhysicsObject : public GameObject
	{
	public:
		PhysicsObject();
		~PhysicsObject();

		inline const DirectX::XMFLOAT3& GetVelocity() const { return m_velocity; }
		inline void SetVelocity(const DirectX::XMFLOAT3& velocity) { m_velocity = velocity; }

	private:
		void doStart() override;
		void doUpdate(DX::StepTimer const& timer) override;
		void doRender() override;



	private:
		DirectX::XMFLOAT3	m_velocity;
	};
}

