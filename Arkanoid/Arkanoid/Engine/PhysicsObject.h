#pragma once
#include "GameObject.h"
#include "Physics\Collider.h"
#include <vector>
namespace Engine
{
	namespace Physics
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


			void SetColliderBounds(float x, float y, float width, float height);

			inline void EnableCollisionDetection(bool value) { m_CollisionDetection = value; }
			inline bool IsCollisionDetectionEnabled() const { return m_CollisionDetection; }
			

			void CollisionDetection();

		private:
			DirectX::XMFLOAT3	m_velocity;
			Collider			m_Collider;
			bool				m_CollisionDetection;

			
			//static std::vector<PhysicsObject*> PhysicsObjectsList;
		};
	}
}

