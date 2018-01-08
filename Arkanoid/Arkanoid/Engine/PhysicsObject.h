#pragma once
#include "GameObject.h"
#include <vector>
namespace Engine
{
	namespace Physics
	{
		/* Box used for collision detecton and resolution */
		/* 1.0f is default bounding box dimension, you can adjust it by changing the scale parameter */
		struct BoundingBox
		{
			DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT3 scale;

			BoundingBox()
				: center(0.0f,0.0f,0.0f)
				, scale(1.0f, 1.0f, 1.0f)
			{}

			BoundingBox(DirectX::XMFLOAT3 i_center, DirectX::XMFLOAT3 i_scale)
				: center(i_center)
				, scale(i_scale)
			{}
		};

		struct ContactPoint
		{
			DirectX::XMFLOAT3 normal;
		};

		class Octree;

		

		class PhysicsObject : public GameObject
		{
		public:
			PhysicsObject();
			explicit PhysicsObject(int ID);
			~PhysicsObject();

			inline const DirectX::XMFLOAT3& GetVelocity() const { return m_velocity; }
			inline void SetVelocity(const DirectX::XMFLOAT3& velocity) { m_velocity = velocity; }

			//inline BoundingBox GetBoundingBox() const { return m_BoundingBox; }
			BoundingBox GetWorldBoundingBox() const;
			inline void SetBoundingBox(const BoundingBox& bb) { m_BoundingBox = bb; }

			inline void EnableCollisionDetection(bool value) { m_CollisionDetection = value; }
			inline bool IsCollisionDetectionEnabled() const { return m_CollisionDetection; }

			void CollisionTest(PhysicsObject& other);

			//typedef void(*OnCollisionDetected)(PhysicsObject& caller, PhysicsObject& other);		//registerable event

			//void RegisterCollisionListener(OnCollisionDetected onCollisionListener);
			//void DeleteCollisionListener(OnCollisionDetected onCollisionListener);

		protected:
			void doStart() override;
			void doUpdate(DX::StepTimer const& timer) override;
			void doRender() override;

		private:

			void CollisionDetected(PhysicsObject& other, const ContactPoint& p );
			virtual void OnCollision(PhysicsObject& other, const ContactPoint& p);

		private:
			DirectX::XMFLOAT3	m_velocity;
			bool				m_CollisionDetection;
			BoundingBox			m_BoundingBox;


			//std::vector<OnCollisionDetected> m_RegisteredCollisionListener;
			
			static std::vector<PhysicsObject*> PhysicsObjectsList;
		};
	}
}

