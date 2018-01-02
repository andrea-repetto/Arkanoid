#pragma once

#include <vector>

namespace Engine
{
	namespace Physics
	{
		class PhysicsObject;

		struct Bounds
		{
			Bounds()
				: x(0.0f)
				, y(0.0f)
				, width(0.0f)
				, heigth(0.0f)
			{

			}

			Bounds(
				float i_x,
				float i_y,
				float i_width,
				float i_heigth)
				: x(i_x)
				, y(i_y)
				, width(i_width)
				, heigth(i_heigth)
			{

			}

			float x;
			float y;
			float width;
			float heigth;
		};

		class QuadTree
		{

		public:
			explicit QuadTree(int level, Bounds bounds);
			~QuadTree();

			void Clear();

		private:
			void split();

		private:
			static const int MAX_LEVEL;

			enum
			{
				NODES_NUMBER = 4
			};

			int m_Level;
			std::vector<const PhysicsObject*> m_Objects;
			Bounds m_Bounds;
			QuadTree*				m_Nodes[NODES_NUMBER];
			

		};
	}
}

