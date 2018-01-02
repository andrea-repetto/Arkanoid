#pragma once

namespace Engine
{
	namespace Physics
	{
		class PhysicsObject;

		class Collider
		{
		public:
			Collider();
			explicit Collider(PhysicsObject* m_Owner);
			~Collider();

			void SetBounds(float x, float y, float width, float height);

			inline float GetX() const { return m_X; }
			inline float GetY() const { return m_Y; }
			inline float GetWidth() const { return m_Width; }
			inline float GetHeight() const { return m_Height; }

		private:
			PhysicsObject*		m_Owner;
			float				m_X;
			float				m_Y;
			float				m_Width;
			float				m_Height;
			
		};
	}
}

